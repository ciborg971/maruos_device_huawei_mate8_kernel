/*************************************************************************
*   ��Ȩ����(C) 1987-2020, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  rf_mipi_cfg.c
*
*   ��    �� :  zuofenghua
*
*   ��    �� :  ͨ��mipi�ӿڶ���Ƶ�������п���
*
*   �޸ļ�¼ :  2015��3��23��  v1.00  zuofenghua  ����
*
*************************************************************************/
#include <stdio.h>
#include <string.h>
#include <securec.h>
#include <osl_malloc.h>
#include <osl_types.h>
#include <osl_sem.h>
#include <osl_thread.h>
#include <RfNvId.h>
#include <drv_nv_def.h>
#include <mdrv_anten.h>
#include <mdrv_gpio.h>
#include <hi_anten.h>
#include <bsp_nvim.h>
#include <bsp_mipi.h>
#include <bsp_rf_balong.h>
#include <bsp_pinctrl.h>
#include <bsp_gpio.h>
#include <bsp_hardtimer.h>
#include <bsp_om.h>
#include <bsp_icc.h>
#include <bsp_version.h>
#include <bsp_bbp.h>
#include <rf_anten_cfg.h>
#include <rf_mipi_cfg.h>


/*��Ƶ�ܽ���GPIO��ŵĶ�Ӧ��ϵ*/
NV_FEMPIN_TO_GPIO_STRU     g_rfpin2gpio;

/*��Ƶ�ܽſ��ػ�����*/
RFFE_PIN_ALL_CFG g_anten_info;

/*todo:����debug��Ϣ*/
FEMIO_CALLINFO_S g_femio_debug[16]; 

/*gpio��mipiͨ�ýӿڿ�����Ϣ*/
NV_FEM_GPIO_MIPI_CTRL_STRU g_femio_info; 

/*������������״̬��Ϣ*/
RF_ANTEN_DETECT_GPIO_STRU g_anten_status;

/*���߲�μ����Ϣ*/
ANTEN_DETECT_INFO g_detect;

/*�������ߡ���������*/
RF_ANT_SHARE_STRU g_ant_share;

/*TDSL_GSM���濹����ʹ�ܱ���*/
RF_NV_GSM_GPIO_ABBTX_FUNC_SEL g_tdsl_gsm_interference;

/*TDSL_GSM����������ñ���*/
RF_NV_GSM_GPIO_ABBTX_CFG   g_tdsl_gsm_config;

int balong_rf_pin_set_mux(struct pinctrl * pctrl, unsigned int gpio_num, unsigned int mux)
{
    if(CHIP_K3V5 == bsp_get_version_info()->chip_type){

        if(ANT_FUNCTION == mux){
        
            if((gpio_num >= 91) && (gpio_num <= 111)){
                mux = 2;
            }
            else mux = 1;
        }
    }
    if(NULL == pctrl){
        rf_print_error("pctrl is null ,gpio is %d,mux is %d\n",gpio_num, mux);
    }
    bsp_pinctrl_mux_set(pctrl, mux);

    return 0;
}
unsigned int balong_rf_pin_to_gpio(unsigned int pin)
{

    if(pin >= FEM_PIN_MAX){        
        rf_print_error("para error, pin = %d.\n", pin);
        return GPIO_NUM_INVAILId;
    }

    return g_rfpin2gpio.cfg[pin];
}


int balong_rf_config_anten_pin(u32 pin_mask, u32 pin_value , u32 pin_func)
{
    u32 i;
    int ret          = 0;
    u32 level        = 0;
    u32 gpio_num     = 0;
    ANT_PIN_FUNC mux;
    struct pinctrl *pctrl = NULL;

    for(i = 0 ; i < FEM_PIN_MAX ; i++){
        if((pin_mask & ((u32)1<<i))){

            /*ͨ��rfpin��Ż�ȡ��gpio���*/
            gpio_num = balong_rf_pin_to_gpio(i);            
            if(GPIO_NUM_INVAILId == gpio_num){
                rf_print_error("get gpio num is error %d!\n",gpio_num);
                return RFFE_ERROR;
            }

            /*ֻ�йܽŸ���Ϊgpio�ģ������õ�ƽ*/
            if(~pin_func & ((u32)1<<i)){

                /*����GPIO �����ƽֵ*/
                level = !!(pin_value &((u32)1<<i));
                bsp_gpio_direction_output(gpio_num, level);
            }

            /*���ùܽŸ���*/
            pctrl = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio_num);
            mux   = (ANT_PIN_FUNC)!!(pin_func & ((u32)1<<i));
            ret   = balong_rf_pin_set_mux(pctrl, gpio_num, mux);
            if(ret){
                rf_print_error("set pin mux error! gpio num=%d,mux=%d\n", gpio_num, mux);
            }
        }
    }

    return ret;
}



int balong_rf_config_anten_common(RFFE_PIN_STRU * pin_info)
{
    int ret        = RFFE_OK;
    u32 mask       = 0;
    u32 level      = 0;
    u32 mux        = 0;

    if(NULL == pin_info){
        rf_print_error("para is NULL !\n");
        return RFFE_ERROR;
    }

    mask = pin_info->mask;
    if (mask){        
        level = pin_info->level;        
        mux   = pin_info->mux;
        
        /*���ùܽŵ�ƽ�͸���*/
        ret   = balong_rf_config_anten_pin(mask, level, mux);
        if(ret){
            rf_print_error("rf config anten pin output value error!,ret %d,mask %d\n",ret,mask);
        }
        
    }

    return ret;
}
int balong_rf_config_anten_poweron(u32 modem_id)
{
    int ret        = RFFE_OK;

    if (!g_anten_info.valid){
        return ret;
    }

    if (NV_BALONG_MODEM_NUM <= modem_id){
        rf_print_error("para error,modem id is %d ,nv surport max is %d\n",modem_id, NV_BALONG_MODEM_NUM);
        return RFFE_ERROR;
    }

    ret = balong_rf_config_anten_common(&g_anten_info.modem_pwron[modem_id]);
    if(ret){
        rf_print_error("set ant pin config at modem [%d] power on fail!\n",modem_id);
    }

    return ret;
}


int balong_rf_config_anten_poweroff(u32 modem_id)
{
    int ret = RFFE_OK;

    if (!g_anten_info.valid){
        return ret;
    }

    if (NV_BALONG_MODEM_NUM <= modem_id){
        rf_print_error("para error,modem id is %d ,nv surport max is %d\n",modem_id, NV_BALONG_MODEM_NUM);
        return RFFE_ERROR;
    }

    ret = balong_rf_config_anten_common(&g_anten_info.modem_pwroff[modem_id]);
    if(ret){
        rf_print_error("set ant pin config at modem [%d] power off fail!\n",modem_id);
    }

    return ret;
}


int balong_rf_config_anten_allpoweroff( void )
{
    int ret = RFFE_OK;
 
    if (!g_anten_info.valid){
        return ret;
    }

    ret = balong_rf_config_anten_common(&g_anten_info.allmodem_pwroff);
    if(ret){
        rf_print_error("set ant pin config at all modem power off fail!ret is %d\n",ret);
    }

    return ret;
}

void balong_anten_event_report_oam(void *para)
{
    struct anten_msg_stru msg = {0, 0};
    /*lint -save -e716*/
    /* coverity[no_escape] */
    while(1)
    {
        osl_sem_down(&g_detect.sem_id);
        
        msg = *((struct anten_msg_stru*)para);

        rf_print_info("anten modem_id = %d,status = %d.\n", msg.modem_id, msg.status);

        if(msg.modem_id < PWC_COMM_MODEM_BUTT && (NULL != g_detect.routine[msg.modem_id]))
        {
            (void) (*(g_detect.routine[msg.modem_id]))();
        }
    }
    /*lint -restore */

}
int balong_anten_data_receive(void)
{    
    int len = 0;

    struct anten_msg_stru msg = {0};
    u32 channel_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_ANTEN;
      
    len = bsp_icc_read(channel_id, (u8*)&msg, sizeof(struct anten_msg_stru));
    if(len != (int)sizeof(struct anten_msg_stru))
    {
        rf_print_error("read len(%x) != expected len(%x).\n", len, sizeof(struct anten_msg_stru));
        return RFFE_ERROR;
    }
    
    g_detect.msg.modem_id = msg.modem_id;
    g_detect.msg.status   = msg.status;

    osl_sem_up(&g_detect.sem_id);

    return RFFE_OK;
}

/*****************************************************************************
 * �� �� : bsp_anten_init *
 * ����  : ���߲�κ˼�ͨ�ţ�C�˳�ʼ������
 *
 * ����  : ��
 * ���  : ��
 *
 * �� �� : ANTAN_OK:    �����ɹ�
 *                ANTAN_ERROR: ����ʧ��
 *****************************************************************************/
s32 balong_anten_detect_init(void)
{
    int ret = 0;
    u32 task_id = 0;
    u32 chan_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_ANTEN;

    memset_s(&g_detect, sizeof(ANTEN_DETECT_INFO), 0, sizeof(ANTEN_DETECT_INFO));
    osl_sem_init(0, &g_detect.sem_id);
    
    ret = osl_task_init("anten_task", ANTEN_TASK_PRIORITY , ANTEN_TASK_STACK_SIZE, (OSL_TASK_FUNC)balong_anten_event_report_oam, &g_detect.msg, &task_id);

    ret |= bsp_icc_event_register(chan_id, (read_cb_func)balong_anten_data_receive, NULL, NULL, NULL);
    if(0 != ret)
    {
        rf_print_error("register is error.\n");
        return RFFE_ERROR;
    }    

    rf_print_info("anten init ok,task id is %d.\n", task_id);

    return RFFE_OK;
}


/*****************************************************************************
 * �� �� : balong_tdsl_gsm_interference_init *
 * ����  : �����������߻������Σ�C�˳�ʼ������
 *
 * ����  : ��
 * ���  : ��
 *
 * �� �� : 0:    �����ɹ�
 *                1:    ����ʧ��
 *****************************************************************************/
s32 balong_tdsl_gsm_interference_init(void)
{
#ifdef HI_PHONE_ANTEN
    int   index = g_tdsl_gsm_interference.abb_tx_index;
    int   ret = 0;
    u32 ctu_base   = (u32)bsp_bbp_part_addr_get(BBP_CTU);

    if(0 == ctu_base){
        rf_print_error("ctu base get error!\n");
        return RFFE_ERROR;
    }

    /*lint -save -e506 -e774*//* coverity[result_independent_of_operands] */
    if(g_tdsl_gsm_interference.gpio_and_or_en && (0xffff  != HI_BBPCOMMON_CPU_ANTPA_MODE_SEL)){
        writel(g_tdsl_gsm_config.gpio_and_or_cfg, ctu_base + HI_BBPCOMMON_CPU_ANTPA_MODE_SEL);
    }
    /*lint -restore*/
    if(index){/*index Ϊ0ʱ������Ҫ�������*/
        writel(g_tdsl_gsm_config.abb_tx_cfg[index -1].abb0_tx_reg, ctu_base + HI_BBPCOMMON_CPU_ABB0_CH_TX_MASK_SEL);
        writel(g_tdsl_gsm_config.abb_tx_cfg[index -1].abb1_tx_reg, ctu_base + HI_BBPCOMMON_CPU_ABB1_CH_TX_MASK_SEL);
    }
    return ret;
#else
    return 0;
#endif
}
void balong_fem_io_debuginfo_add(void* caller,u32 para1,u32 para2,u32 para3,int ret)
{
    u32 i = para1%FEM_IO_CFG_MAX;
    g_femio_debug[i].caller_addr = (u32) caller;
    g_femio_debug[i].para1       = para1;
    g_femio_debug[i].para2       = para2;
    g_femio_debug[i].para3       = para3;
    g_femio_debug[i].timestamp   = bsp_get_slice_value();
    g_femio_debug[i].ret         = ret;
}


static int balong_fem_iocfg_group_mipi(u32 nv_index)
{
    int ret      = 0;
    int max_bytes= 0;

    max_bytes = sizeof(g_femio_info.cfg[nv_index].mipi_ctrl) / sizeof(u32);
    ret = balong_rf_mipi_write((RF_NV_MIPI_CMD_STRU *)g_femio_info.cfg[nv_index].mipi_ctrl.MipiCmd,\
                               (RF_NV_MIPI_BYTE_DATA_STRU*)g_femio_info.cfg[nv_index].mipi_ctrl.MipiData, \
                               g_femio_info.cfg[nv_index].mipi_ctrl.CmdValidCnt, \
                               max_bytes);
    return ret;
}


static int balong_fem_iocfg_group_gpio(u32 nv_index, u32 mux)
{
    u32 i;
    int ret;
    u32 pin_mask  = 0;
    u32 pin_value = 0;
    u32 gpio_num  = 0;
    struct pinctrl* pctrl = NULL;

    if((nv_index >= FEM_IO_CFG_MAX) || (mux >= ANT_FUNC_BUTT)){
        rf_print_error("para error ! nv index is %d,mux is %d\n", nv_index, mux);
        return -1;
    }

    pin_mask  = g_femio_info.cfg[nv_index].gpio_ctrl.mask;
    pin_value = g_femio_info.cfg[nv_index].gpio_ctrl.level;

    for(i=0; i<FEM_PIN_MAX; i++){
        if(pin_mask & ((u32)1 << i)){
            gpio_num = balong_rf_pin_to_gpio(i);
            if(GPIO_NUM_INVAILId == gpio_num){
                rf_print_error("get gpio num is error %d!\n",gpio_num);
                return -1;
            }
            /*get pin mux*/
            pctrl = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio_num);

            /*if pin is gpio function,set direction and pin level*/
            if(0 == mux){
                pin_value = (u32)!!(pin_value & ((u32)1<<i));
                bsp_pinctrl_gpio_modify(pctrl, GPIO_OUTPUT, pin_value);                
                bsp_gpio_direction_output(gpio_num, pin_value);
            }

            /*set pin mux*/
            ret  |= bsp_pinctrl_mux_modify(pctrl, mux);
            ret   = balong_rf_pin_set_mux(pctrl, gpio_num, mux);
            if(ret){
                rf_print_error("set pin mux error! gpio num=%d,mux=%d\n",gpio_num,mux);
                return ret;
            }

        }
    }

    return 0;
}
static int balong_fem_iocfg_group_gpio_mipi_with_nv(u32 nv_index, u32 mux)
{
    FEMIO_CTRL_MODE type = FEMIO_CTRL_TOP;
    int ret = 0;

    if(nv_index >= FEM_IO_CFG_MAX){
        rf_print_error("para is error, nv_index = %d\n", nv_index);
        return -1;
    }

    if(mux > 1){
        rf_print_error("para is error, mux = %d\n", mux);
        return -1;
    }

    type = g_femio_info.cfg[nv_index].mode;
    switch (type){
        case FEMIO_CTRL_TOP:
            ret = 0;
            break;
        case GPIO_ONLY:/*����GPIO*/
            ret =  balong_fem_iocfg_group_gpio(nv_index,mux);
            break;
        case MIPI_ONLY:/*����MIPI*/
            ret = balong_fem_iocfg_group_mipi(nv_index);
            break;
        case GPIO_MIPI:
            ret =  balong_fem_iocfg_group_gpio(nv_index,mux);
            ret |= balong_fem_iocfg_group_mipi(nv_index);
            break;
        default:
            rf_print_error("para is error, type = %d\n", type);
            ret = -1;
            break;
    }
    return ret;
}

static int balong_fem_iocfg_gpio_no_nv(u32 gpio, u32 mux, u32 value)
{
    int ret = RFFE_OK;
    struct pinctrl *pctrl = NULL;

    if(mux >= MODEM_PIN_MUX_BUTT){
        rf_print_error("mux para error,mux is :%d\n",mux);
        return RFFE_ERROR;
    }

    if(MODEM_PIN_MUX_GPIO == mux){
        bsp_gpio_direction_output(gpio,value);
    }

    pctrl = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio);
    ret = balong_rf_pin_set_mux(pctrl, gpio, mux);
    if(ret){
        rf_print_error("set rf pin mux error!gpio = %d\n",gpio);
    }

    return ret;
}


static int balong_fem_iocfg_gpio_with_resume(u32 gpio, u32 mux, u32 value)
{
    int ret = RFFE_OK;
    struct pinctrl *pctrl = NULL;

    if(mux >= MODEM_PIN_MUX_BUTT){
        rf_print_error("mux para error,mux is :%d\n",mux);
        return RFFE_ERROR;
    }

    /*get pinctrl node*/
    pctrl = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio);

    /*set gpio config*/
    if(MODEM_PIN_MUX_GPIO == mux){
        bsp_gpio_direction_output(gpio,value);
        ret = bsp_pinctrl_gpio_modify(pctrl, GPIO_OUTPUT, value);
        if(ret){
            rf_print_error("modify gpio error!\n");
            return RFFE_ERROR;
        }
    }

    /*set pin mux*/
    ret   = balong_rf_pin_set_mux(pctrl, gpio, mux);
    if(ret){
        rf_print_error("set rf pin mux error!gpio = %d\n",gpio);
        return RFFE_ERROR;
    }

    /*change pin mux dts*/
    ret = bsp_pinctrl_mux_modify(pctrl, mux);
    if(ret){
        rf_print_error("modify pin mux dts error!gpio = %d\n",gpio);
    }

    return ret;
}


int bsp_fem_ioctrl(FEMIO_CTRL_TYPE ctrl_type, unsigned int para1, unsigned int para2, unsigned int para3)
{
    int ret = 0;
    switch(ctrl_type)
    {
        case CFG_RFFE_GROUP_GPIO_MIPI:
            ret = balong_fem_iocfg_group_gpio_mipi_with_nv(para1, para2);
            break;

        case CFG_RFFE_SET_PIN_NO_NV:
            ret = balong_fem_iocfg_gpio_no_nv(para1, para2,para3);
            break;

        case CFG_RFFE_SET_PIN_WITH_RESUEM:
            ret = balong_fem_iocfg_gpio_with_resume(para1, para2,para3);
			break;

        default:
            ret = -1;
            break;
    }

    
    /*lint -save -e718 -e746 -e628 -e64*/
    balong_fem_io_debuginfo_add(__builtin_return_address(0),para1,para2,para3,ret);    
    /*lint -save restore*/

    return ret;
}


int bsp_anten_get_lockstate(PWC_COMM_MODEM_E modem_id, unsigned int *status)
{
    int value = 0;
    u32 gpio = 0;

    if(NULL == status || (modem_id >= RF_ANTEN_NUM))
    {
        rf_print_error("para is error, modem id = %d, status = 0x%x.\n", modem_id, status);
        return RFFE_ERROR;
    }

    gpio  = g_anten_status.anten[modem_id];
    if(ANT_DETECT_STUB_GPIO == gpio){
        *status = 1;
        return RFFE_OK;
    }

    value = bsp_gpio_get_value(gpio);/* [false alarm]:����Fortify���� */
    if(GPIO_ERROR == value)
    {
        rf_print_error("bsp_gpio_get_value is fail, value = %d.\n", value);
        return RFFE_ERROR;
    }

    *status = (unsigned int)value;

    return RFFE_OK;
}
int bsp_anten_set_outer_rfswitch(unsigned int status)
{   
    unsigned int i          = 0;
    unsigned int rf_pin     = 0;
    unsigned int gpio_num   = 0;
    unsigned int gpio_value = 0;
    unsigned int cnt        = 0;
    int          ret        = 0;
    struct pinctrl *pctrl   = NULL;

    cnt = g_ant_share.outside.num;
    if(OUTER_RFSWITCH_ON == status){

        for( i = 0 ; i < cnt ; i++ )
        {
            rf_pin     = g_ant_share.outside.gpio[i].rf_pin;
            gpio_value = g_ant_share.outside.gpio[i].gpio_level;
            gpio_num   = balong_rf_pin_to_gpio(rf_pin);
            pctrl      = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio_num);
            ret = balong_rf_pin_set_mux(pctrl , gpio_num, GPIO_FUNCTION);
            bsp_gpio_direction_output(gpio_num, gpio_value);
        }
    }
    else if(OUTER_RFSWITCH_OFF == status){
        for( i = 0 ; i < cnt ; i++ )
        {
            rf_pin     = g_ant_share.outside.gpio[i].rf_pin;

            gpio_num   = balong_rf_pin_to_gpio(rf_pin);
            pctrl      = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio_num);
            ret        = balong_rf_pin_set_mux(pctrl, gpio_num ,ANT_FUNCTION);
        }
    }
    else
    {
        rf_print_error("para error, status=%d.\n", status);            
        ret = RFFE_ERROR;
    }

    return ret;
}

int bsp_anten_get_outer_rfswitch(unsigned int *status)
{
    unsigned int i      = 0;
    unsigned int func   = 0;
    unsigned int gpio   = 0;
    unsigned int cnt    = 0;
    int          ret    = 0;
    struct pinctrl *pctrl = NULL;

    if(NULL == status)
    {
        rf_print_error("para error,status is NULL!\n");
        return RFFE_ERROR;
    }

  
    cnt = g_ant_share.outside.num;
    for( i = 0 ; i < cnt ; i++ )
    {
        gpio  = balong_rf_pin_to_gpio(g_ant_share.outside.gpio[i].rf_pin);
        pctrl = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio);
        ret   = bsp_pinctrl_mux_get(pctrl);

        if(-1 == ret)
        {
            rf_print_error("pinctrl get mux error!\n");
            return ret;

        }        

        func |= (u32)ret;
    }
    
    if(0 == func)
    {
        *status = OUTER_RFSWITCH_ON;
    }
    else
    {
        *status = OUTER_RFSWITCH_OFF;
    }

    return 0;
}


int bsp_anten_set_mode(GPIO_ANT_MODESET_E mode)
{
    unsigned int i     = 0;
    unsigned int gpio  = 0;
    unsigned int value = 0;
    unsigned int cnt   = 0;
    int          ret   = RFFE_OK; 
    struct pinctrl * pctrl = NULL;

    cnt = g_ant_share.inside.num;

    if(ANT_LTE == mode)
    {
        for( i = 0 ; i < cnt ; i++ )
        {
            /*��ȡgpio���*/
            gpio  = balong_rf_pin_to_gpio(g_ant_share.inside.gpio[i].rf_pin);
            value = g_ant_share.inside.gpio[i].gpio_level;

            /*�ܽŸ���Ϊgpio ����*/
            pctrl = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio);
            ret   = balong_rf_pin_set_mux(pctrl , gpio, GPIO_FUNCTION);

            /*����gpio�����ƽֵ*/
            bsp_gpio_direction_output(gpio, value);    

            /*����dts normal����*/
            bsp_pinctrl_mux_modify(pctrl, GPIO_FUNCTION);
            bsp_pinctrl_gpio_modify(pctrl,GPIO_OUTPUT, value);

        }
    }
    else if(ANT_GSM == mode)
    {
        for( i = 0 ; i < cnt ; i++ )
        {
            
            /*��ȡgpio���*/
            gpio  = balong_rf_pin_to_gpio(g_ant_share.inside.gpio[i].rf_pin);

            /*�ܽŸ���Ϊ�߿ع���*/
            pctrl = bsp_pinctrl_get(MODEM_PIN_NORMAL, gpio);
            ret   = balong_rf_pin_set_mux(pctrl, gpio, ANT_FUNCTION);

            /*����dts normal����*/
            bsp_pinctrl_mux_modify(pctrl, ANT_FUNCTION);

        }
    }
    else
    {
        rf_print_error("para error, mode=%d.\n", mode);
        ret = RFFE_ERROR;
    }

    return ret;
}
void bsp_anten_int_install(PWC_COMM_MODEM_E modem_id, void* routine,int para)
{
    if(NULL == routine || (modem_id >= PWC_COMM_MODEM_BUTT))
    {
        rf_print_error("para is error, modem_id = %d, routine = 0x%x, para = %d.\n", modem_id, routine, para);
        return ;
    }
    g_detect.routine[modem_id] = (ANTEN_FUNCPTR)routine;
}


int balong_rf_config_anten_init(void)
{
    int ret = 0;
    
    (void)memset_s((void*)&g_rfpin2gpio, sizeof(NV_FEMPIN_TO_GPIO_STRU), 0, sizeof(NV_FEMPIN_TO_GPIO_STRU));
    (void)memset_s((void*)&g_anten_info, sizeof(RFFE_PIN_ALL_CFG), 0, sizeof(RFFE_PIN_ALL_CFG));

    /*nv 18002 femio ͨ�����ýӿ�*/
    ret = (int)bsp_nvm_read(en_NV_Item_FEM_GPIO_MIPI_CTRL, (u8*)&g_femio_info, sizeof(NV_FEM_GPIO_MIPI_CTRL_STRU));
    if (ret !=  0){
        rf_print_error("anten_gpio read NV=0x%x, ret = %d \n",en_NV_Item_FEM_GPIO_MIPI_CTRL, ret);
    }

    /*nv 18003 rfpin2gpio info init*/
    ret = (int)bsp_nvm_read(en_NV_Item_FEM_PIN_TO_GPIO,(u8*)&g_rfpin2gpio,sizeof(NV_FEMPIN_TO_GPIO_STRU));
    if (ret !=  0)
    {
        rf_print_error("rf_anten read NV=0x%x, ret = %d \n",en_NV_Item_FEM_PIN_TO_GPIO, ret);
    }

    /*nv 18009 anten pin config nv info init*/
    ret = (int)bsp_nvm_read(en_NV_Item_RF_GPIO_INIT,(u8*)&g_anten_info,sizeof(RFFE_PIN_ALL_CFG));
    if (ret !=  0)
    {
        rf_print_error("anten pin config read NV=0x%x, ret = %d \n",en_NV_Item_RF_GPIO_INIT, ret);
    }

    
    /*nv 18010 Get ANTEN NV data by id.*/
    ret = (int)bsp_nvm_read(en_NV_Item_RF_ANT_DETECT,(u8*)&g_anten_status,sizeof(RF_ANTEN_DETECT_GPIO_STRU));
    if (ret !=  0)
    {
        rf_print_error("anten_gpio read NV=0x%x, ret = %d \n",en_NV_Item_RF_ANT_DETECT, ret);
    }

    
    /*nv 18011 Get SHARED ANTEN NV data by id.*/
    ret = (int)bsp_nvm_read(en_NV_Item_ANT_SHARE_CONFIG,(u8*)&g_ant_share,sizeof(RF_ANT_SHARE_STRU));
    if (ret !=  0)
    {
        rf_print_error("anten_gpio read NV=0x%x, ret = %d \n",en_NV_Item_ANT_SHARE_CONFIG, ret);
    }


    /*nv 18000 get gpio and abb tx config by id*/
    ret = (int)bsp_nvm_read(en_NV_Item_GSM_GPIO_FUNC_SEL,(u8*)&g_tdsl_gsm_interference,sizeof(RF_NV_GSM_GPIO_ABBTX_FUNC_SEL));
    if (ret !=  0)
    {
        rf_print_error("rffe anten read NV=0x%x, ret = %d \n",en_NV_Item_GSM_GPIO_FUNC_SEL, ret);
    }

    /*nv 18020 get tdsl&gsm interfernce config*/
    ret = (int)bsp_nvm_read(en_NV_Item_GSM_GPIO_FUNC_CFG,(u8*)&g_tdsl_gsm_config,sizeof(RF_NV_GSM_GPIO_ABBTX_CFG));
    if (ret !=  0)
    {
        rf_print_error("rffe anten read NV=0x%x, ret = %d \n",en_NV_Item_GSM_GPIO_FUNC_CFG, ret);
    }

    /*���߻��������ʼ��*/
    ret = balong_tdsl_gsm_interference_init();
    if (ret !=  0)
    {
        rf_print_error("rffe tdsl gsm interference init fail, ret = %d \n",ret);
    }
    
    /*���߲�μ���ʼ��*/
    ret = balong_anten_detect_init();
    if(ret)
    {
        rf_print_error("balong_anten_detect_init fail \n");
    }

    /*�������߳�ʼ��ΪLTE */
    ret = bsp_anten_set_mode(ANT_LTE);
    if(ret){
        rf_print_error("bsp_anten_set_mode_init fail ,ret = %d\n",ret);
    }
    return ret;
}


