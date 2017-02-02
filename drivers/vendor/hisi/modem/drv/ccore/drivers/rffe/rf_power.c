/*************************************************************************
*   版权所有(C) 1987-2020, 深圳华为技术有限公司.
*
*   文 件 名 :  rf_power.c
*
*   作    者 :  zuofenghua
*
*   描    述 :  用于管理射频器件供电
*
*   修改记录 :  2015年3月23日  v1.00  zuofenghua  创建
*
*************************************************************************/
#include <securec.h>
#include <osl_malloc.h>
#include <osl_sem.h>
#include <osl_thread.h>
#include <of.h>
#include <mdrv_pmu.h>
#include <drv_nv_def.h>
#include <drv_nv_id.h>
#include <bsp_nvim.h>
#include <bsp_regulator.h>
#include <bsp_pmu.h>
#include <bsp_hardtimer.h>
#include <bsp_version.h>
#include <bsp_dump.h>
#include <bsp_pm_om.h>
#include <rf_balong.h>
#include <rf_power.h>

struct pwr_base_info    rfpwr_info[PWR_CONSUMER_NUM];
struct clk_base_info    rfclk_info[RF_CLK_NUM];
struct rf_pwr_clk_debug *rfdbg_om_info;
ST_PWC_SWITCH_STRU      g_pm_nv_switch;

static RFFE_POWER_ID_E balong_get_rffe_powerid(EM_MODEM_CONSUMER_ID_E consumer_id)
{
    switch(consumer_id)
    {
        case MODEM_PA0:
            return TULPA0_VCC;
        case MODEM_PA1:
            return TULPA1_VCC;
        case MODEM_RFIC0_ANALOG0:
            return RFIC0_ANALOG0;

        case MODEM_RFIC1_ANALOG0:
            return RFIC1_ANALOG0;

        case MODEM_RFIC0_ANALOG1:
            return RFIC0_ANALOG1;

        case MODEM_RFIC1_ANALOG1:
            return RFIC1_ANALOG1;

        case MODEM_FEM0:
        case MODEM_FEM1:
            return FEM_VCC;

        case MODEM_PA_VBIAS0:/*todo: 当前pa 的consumer id中没有GPA,需要区分*/
            return TULPA0_VBIAS;
        case MODEM_PA_VBIAS1:
            return TULPA1_VBIAS;

        default:
            return PWR_CONSUMER_NUM;
    }
}
static int balong_rf_regulator_enable(u32 pwr_id)
{
    if(!rfpwr_info[pwr_id].valid ){

        return RFFE_OK;
    }
    if(!rfpwr_info[pwr_id].regu){
        rf_print_error("power id [%d] regulator pointor is null ,\
            please check dts!\n",pwr_id);
        return RFFE_ERROR;
    }
    return regulator_enable(rfpwr_info[pwr_id].regu);
}

static int balong_rf_regulator_disable(u32 pwr_id)
{
    if(!rfpwr_info[pwr_id].valid || rfpwr_info[pwr_id].disable_off){
        return RFFE_OK;
    }
    if(!rfpwr_info[pwr_id].regu){
        rf_print_error("power id [%d] regulator pointor is null ,\
            please check dts!\n",pwr_id);
        return RFFE_ERROR;
    }
    return regulator_disable(rfpwr_info[pwr_id].regu);
}
static int balong_rf_regulator_get_status(u32 pwr_id)
{
    if(!rfpwr_info[pwr_id].valid){
        return 1;/*如果没有,表示此路电源不需要软件控制*/
    }

    if(!rfpwr_info[pwr_id].regu){
        rf_print_error("power id [%d] regulator pointor is null ,\
            please check dts!\n",pwr_id);
        return 0;
    }
    return regulator_is_enabled(rfpwr_info[pwr_id].regu);

}
static int balong_rf_regulator_disable_local(u32 pwr_id)
{

    if(!rfpwr_info[pwr_id].valid){
        return RFFE_OK;
    }
    if(!rfpwr_info[pwr_id].regu){
        rf_print_error("power id [%d] regulator pointor is null ,\
            please check dts!\n",pwr_id);
        return RFFE_ERROR;
    }
    return regulator_disable(rfpwr_info[pwr_id].regu);
}


int balong_rfpower_set_voltage( EM_MODEM_CONSUMER_ID_E consumer_id, u32 voltage_mv )
{
    RFFE_POWER_ID_E pwr_id =  balong_get_rffe_powerid(consumer_id);

    if(PWR_CONSUMER_NUM == pwr_id)
    {
        rf_print_error("power id get fail,consumerid is %d,pwr_id is%d\n",consumer_id, pwr_id);
        return RFFE_ERROR;
    }

    if(rfpwr_info[pwr_id].regu){
        rf_print_error("regulator pointor is null ,consumerid %d,pwr_id is %d\n",consumer_id, pwr_id);
        return RFFE_ERROR;
    }
    return regulator_set_voltage(rfpwr_info[pwr_id].regu, (int)voltage_mv , (int)voltage_mv);
}


int balong_rfpower_get_voltage( EM_MODEM_CONSUMER_ID_E consumer_id)
{
    RFFE_POWER_ID_E pwr_id =  balong_get_rffe_powerid(consumer_id);
    if(PWR_CONSUMER_NUM == pwr_id)
    {
        rf_print_error("power id get fail,consumerid is %d,pwr_id is%d\n",consumer_id, pwr_id);
        return RFFE_ERROR;
    }

    if(rfpwr_info[pwr_id].regu){
        rf_print_error("regulator pointor is null ,consumerid %d,pwr_id is %d\n",consumer_id, pwr_id);
        return RFFE_ERROR;
    }

    return regulator_get_voltage(rfpwr_info[pwr_id].regu);
}

static void balong_rfpoweron_debuginfo_add(PWR_DBG_E dbg_id, PWC_COMM_CHANNEL_E chn,
                                                  PWC_COMM_MODE_E mode,
                                                  u32 pwr_id, u32 pwr_num)
{
    u32 i;
    rfdbg_om_info[dbg_id].info[chn].vote    = rfpwr_info[pwr_id].vote;
    rfdbg_om_info[dbg_id].info[chn].on_cnt[mode]++;
    rfdbg_om_info[dbg_id].info[chn].on_stamp[mode] = bsp_get_slice_value();
    for(i = 0; i < pwr_num; i++){
        rfdbg_om_info[dbg_id].info[chn].hw_stat|= (u32)!!balong_rf_regulator_get_status(pwr_id+i) << i;
    }

}

static void balong_rfpoweroff_debuginfo_add(PWR_DBG_E dbg_id, PWC_COMM_CHANNEL_E chn,
                                                  PWC_COMM_MODE_E mode,
                                                  u32 pwr_id, u32 pwr_num)
{
    u32 i;
    rfdbg_om_info[dbg_id].info[chn].vote    = rfpwr_info[pwr_id].vote;
    rfdbg_om_info[dbg_id].info[chn].off_cnt[mode]++;
    rfdbg_om_info[dbg_id].info[chn].off_stamp[mode] = bsp_get_slice_value();
    for(i = 0; i < pwr_num; i++){
        rfdbg_om_info[dbg_id].info[chn].hw_stat|= (u32)!!balong_rf_regulator_get_status(pwr_id+i) << i;
    }

}


int balong_pa_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id1  = 0;
    unsigned int  pwr_id2  = 0;
    unsigned int  vote_bit = 0;
    unsigned int  first_on = 0;
    int           ret      = 0;

    /*get pwr id*/
    if(PWC_COMM_MODE_GSM == mode){
        pwr_id1 = GPA0_VBIAS + chn * PA_PWR_NUM;
        pwr_id2 = GPA0_VCC   + chn * PA_PWR_NUM;
    }
    else{
        pwr_id1 = TULPA0_VBIAS + chn * PA_PWR_NUM;
        pwr_id2 = TULPA0_VCC   + chn * PA_PWR_NUM;
    }
    if((PWR_CONSUMER_NUM <= pwr_id1) || (PWR_CONSUMER_NUM <= pwr_id2))
    {
        return RFFE_ERROR;
    }

    /*get vote bit*/
    vote_bit = RF_PWR_MODE_NUM*modem + mode;

    osl_sem_down(&rfpwr_info[pwr_id1].sem);

    first_on = !rfpwr_info[pwr_id1].vote;
    rfpwr_info[pwr_id1].vote |= (u64)1 << vote_bit;
    if(first_on){/*only first power on ,config pmu register*/
        ret  = balong_rf_regulator_enable(pwr_id1);
        ret |= balong_rf_regulator_enable(pwr_id2);
        rfdbg_om_info[PWR_PA].info[chn].true_on_cnt[mode]++;
        rfdbg_om_info[PWR_PA].info[chn].true_on_stamp[mode] = bsp_get_slice_value();
    }

    balong_rfpoweron_debuginfo_add(PWR_PA, chn, mode, pwr_id1, 2);
    osl_sem_up(&rfpwr_info[pwr_id1].sem);

    return ret;
}
int balong_pa_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    u32  pwr_id1   = 0;
    u32  pwr_id2   = 0;
    u32  vote_bit  = 0;
    u64  cur_state = 0;
    int  ret       = 0;

    if(PWC_COMM_MODE_GSM == mode){
        pwr_id1 = GPA0_VBIAS + chn * PA_PWR_NUM;
        pwr_id2 = GPA0_VCC   + chn * PA_PWR_NUM;
    }
    else{
        pwr_id1 = TULPA0_VBIAS + chn * PA_PWR_NUM;
        pwr_id2 = TULPA0_VCC   + chn * PA_PWR_NUM;
    }
    if((PWR_CONSUMER_NUM <= pwr_id1) || (PWR_CONSUMER_NUM <= pwr_id2))
    {
        return RFFE_ERROR;
    }


    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_pa_pd){

        return RFFE_OK;
    }
    vote_bit = RF_PWR_MODE_NUM*modem + mode;

    osl_sem_down(&rfpwr_info[pwr_id1].sem);

    /*当前状态为开，电源才可以关闭,防止重复开*/
    cur_state = rfpwr_info[pwr_id1].vote;
    rfpwr_info[pwr_id1].vote &= ~((u64)1 << vote_bit);

    if((0 == rfpwr_info[pwr_id1].vote) && cur_state){
        ret  = balong_rf_regulator_disable(pwr_id1);
        ret |= balong_rf_regulator_disable(pwr_id2);
        rfdbg_om_info[PWR_PA].info[chn].true_off_cnt[mode]++;
        rfdbg_om_info[PWR_PA].info[chn].true_off_stamp[mode] = bsp_get_slice_value();
    }
    balong_rfpoweroff_debuginfo_add(PWR_PA, chn, mode, pwr_id1, 2);

    osl_sem_up(&rfpwr_info[pwr_id1].sem);

    return ret;

}
int balong_pa_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id1 = 0;
    int           status  = 0;

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_pa_pd){
        return 1;
    }
    if(PWC_COMM_MODE_GSM == mode){
        pwr_id1 = GPA0_VBIAS + chn * PA_PWR_NUM;
    }
    else{
        pwr_id1 = TULPA0_VBIAS + chn * PA_PWR_NUM;
    }
    if((PWR_CONSUMER_NUM <= pwr_id1))
    {
        return RFFE_ERROR;
    }


    osl_sem_down(&rfpwr_info[pwr_id1].sem);

    status = !!rfpwr_info[pwr_id1].vote;

    osl_sem_up(&rfpwr_info[pwr_id1].sem);

    return status;
}


int balong_pa_power_hw_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id1 = 0;
    unsigned int  pwr_id2 = 0;
    int           status  = 0;
    int           status1  = 0;
    int           status2  = 0;

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_pa_pd){
        return 1;
    }
    if(PWC_COMM_MODE_GSM == mode){
        pwr_id1 = GPA0_VBIAS + chn * PA_PWR_NUM;
        pwr_id2 = GPA0_VCC   + chn * PA_PWR_NUM;
    }
    else{
        pwr_id1 = TULPA0_VBIAS + chn * PA_PWR_NUM;
        pwr_id2 = TULPA0_VCC   + chn * PA_PWR_NUM;
    }
    if((PWR_CONSUMER_NUM <= pwr_id1))
    {
        return RFFE_ERROR;
    }


    osl_sem_down(&rfpwr_info[pwr_id1].sem);

    status1 = !!balong_rf_regulator_get_status(pwr_id1);
    status2 = !!balong_rf_regulator_get_status(pwr_id2);

    osl_sem_up(&rfpwr_info[pwr_id1].sem);

    status = (status1 & status2);

    return status ;
}


int balong_rfic_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id1  = 0;
    unsigned int  pwr_id2  = 0;
    unsigned int  pwr_id3  = 0;
    unsigned int  pwr_id4  = 0;
    unsigned int  vote_bit = 0;
    unsigned int  first_on = 0;
    int           ret      = 0;

    pwr_id1 = RFIC0_ANALOG0 + chn * RF_PWR_NUM;
    pwr_id2 = RFIC0_ANALOG1 + chn * RF_PWR_NUM;
    pwr_id3 = RFIC0_ANALOG2 + chn * RF_PWR_NUM;
    pwr_id4 = RFIC0_DIGITAL + chn * RF_PWR_NUM;
    if((PWR_CONSUMER_NUM <= pwr_id1) || (PWR_CONSUMER_NUM <= pwr_id2))
    {
        return RFFE_ERROR;
    }

    vote_bit = RF_PWR_MODE_NUM*modem + mode;

    osl_sem_down(&rfpwr_info[pwr_id1].sem);

    first_on = !rfpwr_info[pwr_id1].vote;
    rfpwr_info[pwr_id1].vote |= (u64)1 << vote_bit;
    if(first_on){
        ret  = balong_rf_regulator_enable(pwr_id1);
        ret |= balong_rf_regulator_enable(pwr_id2);
        ret |= balong_rf_regulator_enable(pwr_id3);
        ret |= balong_rf_regulator_enable(pwr_id4);
        rfdbg_om_info[PWR_RFIC].info[chn].true_on_cnt[mode]++;
        rfdbg_om_info[PWR_RFIC].info[chn].true_on_stamp[mode] = bsp_get_slice_value();
        
    }
    balong_rfpoweron_debuginfo_add(PWR_RFIC, chn, mode, pwr_id1, 4);

    osl_sem_up(&rfpwr_info[pwr_id1].sem);

    return ret;
}


int balong_rfic_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    u32  pwr_id1   = 0;
    u32  pwr_id2   = 0;
    u32  pwr_id3   = 0;
    u32  pwr_id4   = 0;
    u32  vote_bit  = 0;
    u64  cur_state = 0;
    int  ret       = 0;

    pwr_id1 = RFIC0_ANALOG0 + chn * RF_PWR_NUM;
    pwr_id2 = RFIC0_ANALOG1 + chn * RF_PWR_NUM;
    pwr_id3 = RFIC0_ANALOG2 + chn * RF_PWR_NUM;
    pwr_id4 = RFIC0_DIGITAL + chn * RF_PWR_NUM;
    if((PWR_CONSUMER_NUM <= pwr_id1) || (PWR_CONSUMER_NUM <= pwr_id2))
    {
        return RFFE_ERROR;
    }

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_rfic_pd){

        return RFFE_OK;
    }

    vote_bit = RF_PWR_MODE_NUM*modem + mode;

    osl_sem_down(&rfpwr_info[pwr_id1].sem);

    /*当前状态为开，电源才可以关闭,防止重复关闭*/
    cur_state = rfpwr_info[pwr_id1].vote;
    rfpwr_info[pwr_id1].vote &= ~((u64)1 << vote_bit);
    if((0 == rfpwr_info[pwr_id1].vote) && cur_state){
        ret  = balong_rf_regulator_disable(pwr_id1);
        ret |= balong_rf_regulator_disable(pwr_id2);
        ret |= balong_rf_regulator_disable(pwr_id3);
        ret |= balong_rf_regulator_disable(pwr_id4);
        rfdbg_om_info[PWR_RFIC].info[chn].true_off_cnt[mode]++;
        rfdbg_om_info[PWR_RFIC].info[chn].true_off_stamp[mode] = bsp_get_slice_value();
        
    }
    balong_rfpoweroff_debuginfo_add(PWR_RFIC, chn, mode, pwr_id1, 4);
    osl_sem_up(&rfpwr_info[pwr_id1].sem);

    return ret;
}
int balong_rfic_power_status(PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id  = 0;
    int           status  = 0;

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_rfic_pd){
        return 1;
    }

    pwr_id = RFIC0_ANALOG0 + chn * RF_PWR_NUM;
    if(PWR_CONSUMER_NUM <= pwr_id)
    {
        return RFFE_ERROR;
    }

    osl_sem_down(&rfpwr_info[pwr_id].sem);

    status = !!rfpwr_info[pwr_id].vote;

    osl_sem_up(&rfpwr_info[pwr_id].sem);

    return status;
}


int balong_rfic_power_hw_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id1  = 0;
    unsigned int  pwr_id2  = 0;
    unsigned int  pwr_id3  = 0;
    unsigned int  pwr_id4  = 0;
    int  status = 0;

    pwr_id1 = RFIC0_ANALOG0 + chn * RF_PWR_NUM;
    pwr_id2 = RFIC0_ANALOG1 + chn * RF_PWR_NUM;
    pwr_id3 = RFIC0_ANALOG2 + chn * RF_PWR_NUM;
    pwr_id4 = RFIC0_DIGITAL + chn * RF_PWR_NUM;
    if((PWR_CONSUMER_NUM <= pwr_id1) || (PWR_CONSUMER_NUM <= pwr_id2))
    {
        return RFFE_ERROR;
    }

    osl_sem_down(&rfpwr_info[pwr_id1].sem);

    status  = balong_rf_regulator_get_status(pwr_id1);
    status &= balong_rf_regulator_get_status(pwr_id2);
    status &= balong_rf_regulator_get_status(pwr_id3);
    status &= balong_rf_regulator_get_status(pwr_id4);

    osl_sem_up(&rfpwr_info[pwr_id1].sem);

    return status;
}


int balong_fem_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id   = 0;
    unsigned int  vote_bit = 0;
    unsigned int  first_on = 0;
    int           ret      = 0;

    pwr_id = FEM_VCC ;/*fem不区分channel信息*/

    vote_bit = RF_PWR_MODE_NUM*PWC_COMM_MODEM_BUTT*chn + RF_PWR_MODE_NUM*modem +mode;

    osl_sem_down(&rfpwr_info[pwr_id].sem);

    first_on = !rfpwr_info[pwr_id].vote;
    rfpwr_info[pwr_id].vote |= (u64)1 << vote_bit;
    if(first_on){
        ret = balong_rf_regulator_enable(pwr_id);
        rfdbg_om_info[PWR_FEM].info[chn].true_off_cnt[mode]++;
        rfdbg_om_info[PWR_FEM].info[chn].true_off_stamp[mode] = bsp_get_slice_value();
        
    }
    balong_rfpoweroff_debuginfo_add(PWR_FEM, chn, mode, pwr_id, 1);
    osl_sem_up(&rfpwr_info[pwr_id].sem);

    return ret;
}
int balong_fem_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    u32  pwr_id    = 0;
    u32  vote_bit  = 0;
    u64  cur_state = 0;
    int  ret       = 0;

    pwr_id = FEM_VCC;
    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_fem_pd){

        return RFFE_OK;
    }

    vote_bit = RF_PWR_MODE_NUM*PWC_COMM_MODEM_BUTT*chn + RF_PWR_MODE_NUM*modem +mode;

    osl_sem_down(&rfpwr_info[pwr_id].sem);

    /*当前状态为开，电源才可以关闭,防止重复关闭*/
    cur_state = rfpwr_info[pwr_id].vote;

    rfpwr_info[pwr_id].vote &= ~((u64)1 << vote_bit);
    if((0 == rfpwr_info[pwr_id].vote) && cur_state){
        ret = balong_rf_regulator_disable(pwr_id);
        rfdbg_om_info[PWR_FEM].info[chn].true_on_cnt[mode]++;
        rfdbg_om_info[PWR_FEM].info[chn].true_on_stamp[mode] = bsp_get_slice_value();
        
    }
    balong_rfpoweron_debuginfo_add(PWR_FEM, chn, mode, pwr_id, 1);
    osl_sem_up(&rfpwr_info[pwr_id].sem);

    return ret;
}
int balong_fem_power_status(PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id  = 0;
    int           ret     = 0;

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_fem_pd){
        return 1;
    }

    pwr_id = FEM_VCC;

    osl_sem_down(&rfpwr_info[pwr_id].sem);

    ret = !!rfpwr_info[pwr_id].vote;

    osl_sem_up(&rfpwr_info[pwr_id].sem);

    return ret;
}


int balong_fem_power_hw_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  pwr_id   = 0;
    int           status      = 0;

    pwr_id = FEM_VCC ;/*fem不区分channel信息*/

    osl_sem_down(&rfpwr_info[pwr_id].sem);

    status = balong_rf_regulator_get_status(pwr_id);

    osl_sem_up(&rfpwr_info[pwr_id].sem);

    return status;
}
int balong_rfclk_enable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  first_on = 0;
    unsigned int  vote_bit = 0;

    if(chn >= RF_CLK_NUM){
        rf_print_error("chn id is invalid ,chn is %d,max is surport %d\n",chn, RF_CLK_NUM);
        return RFFE_ERROR;
    }

    vote_bit = RF_PWR_MODE_NUM*modem + mode;
    osl_sem_down(&rfclk_info[chn].sem);

    first_on = !rfclk_info[chn].vote;

    rfclk_info[chn].vote |= (u64)1 << vote_bit;

    if(first_on){
        bsp_pmu_rfclk_enable(chn);
        rfdbg_om_info[CLK_RFIC].info[chn].true_on_cnt[mode]++;
        rfdbg_om_info[CLK_RFIC].info[chn].true_on_stamp[mode] = bsp_get_slice_value();
          
    }
    
    rfdbg_om_info[CLK_RFIC].info[chn].vote    = rfclk_info[chn].vote;
    rfdbg_om_info[CLK_RFIC].info[chn].on_cnt[mode]++;
    rfdbg_om_info[CLK_RFIC].info[chn].on_stamp[mode] = bsp_get_slice_value();    

    osl_sem_up(&rfclk_info[chn].sem);

    return RFFE_OK;
}


int balong_rfclk_disable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    u64           cur_state = 0;
    unsigned int  vote_bit  = 0;

    if(chn >= RF_CLK_NUM){
        rf_print_error("chn id is invalid ,chn is %d,max is surport %d\n",chn, RF_CLK_NUM);
        return RFFE_ERROR;
    }

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_rfclk_pd){

        return RFFE_OK;
    }

    vote_bit = RF_PWR_MODE_NUM*modem + mode;
    osl_sem_down(&rfclk_info[chn].sem);

    cur_state = rfclk_info[chn].vote;

    rfclk_info[chn].vote &= ~((u64)1 << vote_bit);

    if(cur_state && (0 == rfclk_info[chn].vote)){
        bsp_pmu_rfclk_disable(chn);
        rfdbg_om_info[CLK_RFIC].info[chn].true_off_cnt[mode]++;
        rfdbg_om_info[CLK_RFIC].info[chn].true_off_stamp[mode] = bsp_get_slice_value();
              
    }
        
    rfdbg_om_info[CLK_RFIC].info[chn].vote    = rfclk_info[chn].vote;
    rfdbg_om_info[CLK_RFIC].info[chn].off_cnt[mode]++;
    rfdbg_om_info[CLK_RFIC].info[chn].off_stamp[mode] = bsp_get_slice_value();    
    osl_sem_up(&rfclk_info[chn].sem);

    return RFFE_OK;
}


int balong_rf_power_resume(void)
{
    int ret    = RFFE_OK;
    int pwr_id = 0;

    for(pwr_id = 0; pwr_id < PWR_CONSUMER_NUM; pwr_id++ ){
        if(rfpwr_info[pwr_id].init_on){
            ret |=balong_rf_regulator_enable(pwr_id);
        }
    }
    return ret;
}

int balong_rf_power_suspend(void)
{
    int ret    = RFFE_OK;
    int pwr_id = 0;

    for(pwr_id = 0; pwr_id < PWR_CONSUMER_NUM; pwr_id++ ){
        if(rfpwr_info[pwr_id].dpm_off){
            ret |=balong_rf_regulator_disable_local(pwr_id);
        }
    }
    return ret;
}

/*RFIC_VCC_OCP*/
void balong_rffe_ocp_handler(int volt_id)
{
    rf_print_error("RFIC volt ocp,%d!\n",volt_id);
}

void balong_rf_power_debug_init(void)
{
    u32 dbg_len = PWR_DBG_NUM * sizeof(struct rf_pwr_clk_debug);

    /*可维可测初始化*/
    rfdbg_om_info = bsp_pm_dump_get(PM_OM_RFFE, dbg_len);
    if(NULL == rfdbg_om_info)
    {
        rf_print_error("pm_dump malloc failed,malloc myself!\n");
        rfdbg_om_info = malloc(dbg_len);
        if(NULL == rfdbg_om_info){
            rf_print_error("pm_dump malloc memory fail!\n");
            return ;
        }
    }
    (void)memset_s(rfdbg_om_info, dbg_len, 0, dbg_len);

}
int balong_rf_power_dts_init(void)
{
    int          ret = 0;
    unsigned int id  = 0;
    struct device_node *dev_node   = NULL;
    struct device_node *child_node = NULL;
    const char         *name       ="hisilicon,rfpower_balong";

    /*get dts info*/
    dev_node = of_find_compatible_node(NULL, NULL, name);
    if(NULL == dev_node)
    {
        rf_print_error("rf power device node not found!\n");
        return RFFE_ERROR;
    }

    for_each_child_of_node(dev_node, child_node)
    {
        ret = of_property_read_u32_index(child_node, "pwr_id", 0, &id);
        if(ret)
        {
            rf_print_error("get rf pwr id fail\n");
            return RFFE_ERROR;
        }
        if(id >= PWR_CONSUMER_NUM){
            rf_print_error("rf pwr id err,please check dts!id is %d\n",id);
            break;
        }

        rfpwr_info[id].pwr_id = id;

        ret = of_property_read_u32_index(child_node, "valid", 0, &rfpwr_info[id].valid);

        if(rfpwr_info[id].valid){

            ret = of_property_read_string_index(child_node,"regulator_name",0,&rfpwr_info[id].name);
            if(ret)
            {
                rf_print_error("get rf regulator_name fail\n");
                return RFFE_ERROR;
            }
            ret |= of_property_read_u32_index(child_node, "init_on", 0, &rfpwr_info[id].init_on);

            ret |= of_property_read_u32_index(child_node, "dpm_off", 0, &rfpwr_info[id].dpm_off);

            ret |= of_property_read_u32_index(child_node, "voltage", 0, &rfpwr_info[id].voltage);

            ret |= of_property_read_u32_index(child_node, "disable_off", 0, &rfpwr_info[id].disable_off);
            if(ret)
            {
                rf_print_error("rf power get consumer dts information fail, id is %d!\n",id);
                return RFFE_ERROR;
            }

        }
    }

    return RFFE_OK;
}
int balong_rf_power_init(void)
{
    int          ret = 0;
    unsigned int id  = 0;

    /*get nv info*/
    ret = bsp_nvm_read(NV_ID_DRV_NV_PWC_SWITCH, (u8 *)(&g_pm_nv_switch), sizeof(ST_PWC_SWITCH_STRU));/*lint !e713*/
    if(ret)
    {
        rf_print_error("NV_ID_DRV_NV_PWC_SWITCH:D10B read fail!,ret:%d\n",ret);
    }

    /*get dts info and volt init*/
    ret = balong_rf_power_dts_init();
    if(ret)
    {
        rf_print_error("balong_rf_power_dts_init fail!,ret:%d\n",ret);
        return RFFE_ERROR;
    }

    /*volt init*/
    for(id = 0; id < PWR_CONSUMER_NUM; id++){
        if(rfpwr_info[id].valid){
            rfpwr_info[id].regu = regulator_get(NULL,(char *)rfpwr_info[id].name);
            
            /*初始化配置电压*/
            if((NULL != rfpwr_info[id].regu ) && rfpwr_info[id].voltage){
                ret = regulator_set_voltage(rfpwr_info[id].regu, (int)rfpwr_info[id].voltage, (int)rfpwr_info[id].voltage);
                if(ret)
                {
                    rf_print_error("rf power set voltage faild! power id is %d\n",id);
                    return RFFE_ERROR;
                }
            }
            
            /*打开需始化就需要打开的电源*/
            if(rfpwr_info[id].init_on){
                ret = balong_rf_regulator_enable(id);
                if(ret)
                {
                    rf_print_error("rf power enable faild! power id is %d\n",id);
                    return RFFE_ERROR;
                }
            }
            
            /*注册ocp异常处理*/
            ret |= bsp_pmu_ocp_register((int)rfpwr_info[id].regu->id,balong_rffe_ocp_handler);
            if(0 != ret)
            {
                rf_print_error("pmu ocp register error.\n");
                //return RFFE_ERROR;
            }
            
        }
        /*初始化信号量*/
        osl_sem_init(RF_PWR_SEM_FULL, &rfpwr_info[id].sem);


    }

    /*rfclk init*/
    for(id = 0; id < RF_CLK_NUM; id++){
        osl_sem_init(RF_PWR_SEM_FULL, &rfclk_info[id].sem);
    }


    /*debug info init*/
    balong_rf_power_debug_init();

    /*TUL pa volt is enable depands on nv */
    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_pa_pd){
        ret |= balong_rf_regulator_enable(TULPA0_VCC);
        ret |= balong_rf_regulator_enable(TULPA1_VCC);
        ret |= balong_rf_regulator_enable(TULPA2_VCC);
    }

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_rfic_pd){
        ret |= balong_rf_regulator_enable(RFIC0_ANALOG0);
        ret |= balong_rf_regulator_enable(RFIC0_ANALOG1);
        ret |= balong_rf_regulator_enable(RFIC1_ANALOG0);
        ret |= balong_rf_regulator_enable(RFIC1_ANALOG1);
        ret |= balong_rf_regulator_enable(RFIC2_ANALOG0);
        ret |= balong_rf_regulator_enable(RFIC2_ANALOG1);
        udelay(200);
    }

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_fem_pd){
        ret |= balong_rf_regulator_enable(FEM_VCC);
    }

    if (NV_PWC_ALLWAYS_ON == g_pm_nv_switch.drx_rfclk_pd){
        bsp_pmu_rfclk_enable(0);
        bsp_pmu_rfclk_enable(1);
    }

    return ret;
}

int balong_rfpower_vote_get(PWR_DBG_E consumer, PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    u32 pwr_id    = 0;
    u32 vote_bit  = 0;
    u64 vote_lock = 0;

    switch (consumer){
        case PWR_RFIC:
            vote_bit = RF_PWR_MODE_NUM*modem + mode;
            pwr_id   = RFIC0_ANALOG0 + chn * RF_PWR_NUM;
            break;
        case PWR_PA:
            vote_bit = RF_PWR_MODE_NUM*modem + mode;
            if(PWC_COMM_MODE_GSM == mode){
                pwr_id = GPA0_VBIAS + chn * PA_PWR_NUM;
            }
            else{
                pwr_id = TULPA0_VBIAS + chn * PA_PWR_NUM;
            }
            break;
        case PWR_FEM:
            vote_bit = RF_PWR_MODE_NUM*PWC_COMM_MODEM_BUTT*chn + RF_PWR_MODE_NUM*modem +mode;
            pwr_id   = FEM_VCC;
            break;
        default:
            break;
    }

    vote_lock = ((u64)1 << vote_bit) & (rfpwr_info[pwr_id].vote);

    return !!vote_lock;
}

void balong_rfpower_print_mode_info(int mode, char *name)
{
    switch(mode){
        case PWC_COMM_MODE_GSM:
            memcpy_s(name, 32, "GSM",4);
            break;
        case PWC_COMM_MODE_TDS:
            memcpy_s(name, 32, "TDS",4);
            break;
        case PWC_COMM_MODE_LTE:
            memcpy_s(name, 32, "LTE",4);
            break;
        case PWC_COMM_MODE_WCDMA:
            memcpy_s(name, 32, "WCDMA",6);
            break;
        case PWC_COMM_MODE_CDMA_1X:
            memcpy_s(name, 32, "CDMA_1X",8);
            break;
        case PWC_COMM_MODE_CDMA_HRPD:
            memcpy_s(name, 32, "CDMA_HRPD",10);
            break;
        default:
            return ;
    }
    return ;
}

void balong_rfpower_debug_unit(PWR_DBG_E id)
{
    int chn   = 0;
    int mode  = 0;
    u32 vote_low = 0;
    u32 vote_high= 0;
    char consumer[32];

    rf_print_dbg("%-15s%-10s%-16s", \
    "mode", "chn", "vote");
    rf_print_dbg("%-10s%-10s%-10s%-10s%-10s", \
       "hwstat","on_cnt","off_cnt", "on_time", "off_time");
    rf_print_dbg("%-10s%-10s%-10s%-10s\n", \
        "t_on_cnt","t_off_cnt", "t_on_time", "t_off_time");
    for(mode = 0; mode < RF_PWR_MODE_NUM; mode++){
        balong_rfpower_print_mode_info(mode, consumer);        
        for(chn = 0; chn < RF_PWR_CHN_NUM; chn++){
            vote_low  = (u32)rfdbg_om_info[id].info[chn].vote;
            vote_high = (u32)(rfdbg_om_info[id].info[chn].vote >> 32);
            rf_print_dbg("%-15s%-10d%8x%-08x",consumer, chn, vote_high, vote_low);
            rf_print_dbg("%-10x%-10x%-10x%-10x%-10x", \
                    
                rfdbg_om_info[id].info[chn].hw_stat ,
                    rfdbg_om_info[id].info[chn].on_cnt[mode],
                    rfdbg_om_info[id].info[chn].off_cnt[mode],
                    rfdbg_om_info[id].info[chn].on_stamp[mode],
                    rfdbg_om_info[id].info[chn].off_stamp[mode]);
                    //rfdbg_om_info[id].info[chn].hw_stat
            rf_print_dbg("%-10x%-10x%-10x%-10x\n", \
                    rfdbg_om_info[id].info[chn].true_on_cnt[mode],
                    rfdbg_om_info[id].info[chn].true_off_cnt[mode],
                    rfdbg_om_info[id].info[chn].true_on_stamp[mode],
                    rfdbg_om_info[id].info[chn].true_off_stamp[mode]);
                osl_task_delay(2);
            }
        }
}
void balong_rfpower_debug_help(void)
{
    rf_print_dbg("PWR_DBG_E id is RFIC--0,FEM--1,PA--2,RFCLK--3\n");
    rf_print_dbg("PWC_COMM_MODE_E is G--0,W----1,L---2,T------3\n");
    rf_print_dbg("check vote and timestamp: balong_rfpower_debug_unit(PWR_DBG_E id)\n");
    rf_print_dbg("open tulpa :balong_pa_power_on(mode, modem, chn)\n");
    rf_print_dbg("open rfic  :balong_rfic_power_on(mode, modem, chn)\n");
    rf_print_dbg("open fem   :balong_fem_power_on(mode, modem, chn)\n");
    rf_print_dbg("open rfclk :balong_rfclk_enable(mode, modem, chn)\n");
    rf_print_dbg("close tulpa:balong_pa_power_off(mode, modem, chn)\n");
    rf_print_dbg("close rfic :balong_rfic_power_off(mode, modem, chn)\n");
    rf_print_dbg("close fem  :balong_fem_power_off(mode, modem, chn)\n");
    rf_print_dbg("close rfclk:balong_rfclk_disable(mode, modem, chn)\n");
    return ;
}


