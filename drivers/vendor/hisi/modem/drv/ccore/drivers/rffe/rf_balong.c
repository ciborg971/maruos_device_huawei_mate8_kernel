/*************************************************************************
*   ��Ȩ����(C) 1987-2020, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  rf_power.c
*
*   ��    �� :  zuofenghua
*
*   ��    �� :  ���ڹ�����Ƶ��������
*
*   �޸ļ�¼ :  2015��3��23��  v1.00  zuofenghua  ����
*
*************************************************************************/
#include <product_config.h>
#include <osl_sem.h>
#include <bsp_rf_balong.h>
#include <bsp_dpm.h>
#include <bsp_hardtimer.h>
#include <bsp_pmu.h>
#include <rf_power.h>
#include <rf_anten_cfg.h>
#include <rf_mipi_cfg.h>

#define SEM_RFIC 0
#define SEM_FEM  1
#define SEM_PA   2
#define SEM_NUM  3

typedef struct{
    u64   vote[RF_PWR_CHN_NUM];
    u32   pwron_cnt[RF_PWR_CHN_NUM];
    u32   pwroff_cnt[RF_PWR_CHN_NUM];
    u32   true_pwron_cnt[RF_PWR_CHN_NUM];
    u32   true_pwroff_cnt[RF_PWR_CHN_NUM];
    u32   true_alloff_cnt;
    u32   pwron_time_stamp[RF_PWR_CHN_NUM];
    u32   pwroff_time_stamp[RF_PWR_CHN_NUM];
    u32   true_pwron_time_stamp[RF_PWR_CHN_NUM];
    u32   true_pwroff_time_stamp[RF_PWR_CHN_NUM];
    u32   true_alloff_time_stamp;
    u32   resume_time_stamp;
    u32   complete_timestamp;
    u32   suspend_late_timestamp;
    u32   reserved;
}RFFE_MIPI_ANTEN_CFG_S;

RFFE_MIPI_ANTEN_CFG_S rffe_cfg;

osl_sem_id rf_pwr_sem[SEM_NUM];
#ifndef CONFIG_PA_RF

s32 mdrv_pmu_check_pastar(PWC_COMM_MODEM_E modem_id)
{
    return 0;
}


s32 mdrv_pmu_set_voltage( EM_MODEM_CONSUMER_ID_E consumer_id, u32 voltage_mv )
{
    return 0;/*Austin ��׮*/
    //return balong_rfpower_set_voltage(consumer_id, voltage_mv);
}
s32 mdrv_pmu_get_voltage( EM_MODEM_CONSUMER_ID_E consumer_id, u32 *voltage_mv )
{
    int ret =  balong_rfpower_get_voltage(consumer_id);

    if(RFFE_ERROR == ret){
       rf_print_error("rf ger voltage fail!consumer id is %d,ret is %d\n",consumer_id, ret);
       return ret;
    }

    *voltage_mv = (u32)ret / 1000;

    return RFFE_OK;
}

/*****************************************************************************
 �� �� ��  : mdrv_pmu_list_voltage
 ��������  : ͨ��ģ���ȡ��ѹ���÷�Χ�ӿڴ�׮
 �������  : consumer_id     �û�id
             list            ��ѹ��Χ����
             size            �����С
 �������  : ��
 �� �� ֵ  : 0          ��ȡ�ɹ�
             else       ��ȡʧ��
*****************************************************************************/
s32 mdrv_pmu_list_voltage(EM_MODEM_CONSUMER_ID_E consumer_id,u16 **list, u32 *size)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : mdrv_pmu_enable_apt
 ��������  : ͨ��ģ��ʹ��APT�ӿڴ�׮
 �������  : modem_id       ����
             mode_id        ͨ��ģʽ
 �������  : ��
 �� �� ֵ  : 0         ���óɹ�
             else      ����ʧ��
*****************************************************************************/
s32 mdrv_pmu_enable_apt(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : mdrv_pmu_disable_apt
 ��������  : ͨ��ģ��ȥʹ��APT�ӿڴ�׮
 �������  : modem_id       ����
             mode_id        ͨ��ģʽ
 �������  : ��
 �� �� ֵ  : 0         ���óɹ�
             else      ����ʧ��
*****************************************************************************/
s32 mdrv_pmu_disable_apt(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : mdrv_pmu_get_aptstatus
 ��������  : ͨ��ģ���ȡ��ǰAPT״̬�ӿڴ�׮
 �������  : modem_id       ����
             mode_id        ͨ��ģʽ
 �������  : ��
 �� �� ֵ  : 1     APTʹ��
                        0    APTδʹ��
                       -1    ��ȡʧ��
*****************************************************************************/
s32 mdrv_pmu_get_aptstatus(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return 0;
}

/*****************************************************************************
 �� �� ��  : mdrv_pmu_set_modem_mode
 ��������  : ͨ��ģ������Gģ��Wģ�ӿڴ�׮
 �������  : modem_id       ����
             mode_id        ͨ��ģʽ
 �������  : ��
 �� �� ֵ  : 0         ���óɹ�
             else      ����ʧ��
*****************************************************************************/
s32 mdrv_pmu_set_modem_mode(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id)
{
    return 0;
}

/*****************************************************************************
* �� ��    : bsp_pa_power_up
* �� ��    : PA �ϵ�ӿ�
* �� ��    : ��
* �� ��    :
* �� ��    : ��
* �� ��    : pa��Դ����״̬
* ˵ ��    :
*****************************************************************************/
int bsp_pa_power_up(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return balong_pa_power_on(mode, modem, chn);
}

/*****************************************************************************
* �� ��    : bsp_pa_power_down
* �� ��    : PA �µ��׮
* �� ��    : ��
* �� ��    :
* �� ��    : ��
* �� ��    : pa ��Դ����״̬
* ˵ ��    :
****************************************************************/
int bsp_pa_power_down(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return balong_pa_power_off(mode, modem, chn);
}

/*****************************************************************************
* �� ��    : bsp_rfic_power_down
* �� ��    : RF �µ��׮
* �� ��    : ��
* �� ��    :
* �� ��    : ��
* �� ��    : rf��Դ����״̬
* ˵ ��    :
*****************************************************************************/
int bsp_rfic_power_down(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return balong_rfic_power_off(mode, modem, chn);
}

/*****************************************************************************
 ����    : bsp_rfic_power_up
 ����    : RFIC �ϵ�
 ����    : ��
 ���    : ��
 ����     : rf�ϵ��Ƿ�ɹ���0Ϊ�ɹ�,1Ϊʧ��
*****************************************************************************/
int bsp_rfic_power_up(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return balong_rfic_power_on(mode, modem, chn);
}

/*****************************************************************************
 ����    : bsp_rfclk_enable
 ����    : ��RFIC ʱ��buffer
 ����    : ��
 ���    : ��
 ����     : rf�ϵ��Ƿ�ɹ���0Ϊ�ɹ�,1Ϊʧ��
*****************************************************************************/
int bsp_rfclk_enable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return balong_rfclk_enable(mode, modem, chn);
}

/*****************************************************************************
 ����    : bsp_rfic_power_up
 ����    : �ر�RFIC ʱ��buffer
 ����    : ��
 ���    : ��
 ����    : rf�ϵ��Ƿ�ɹ���0Ϊ�ɹ�,1Ϊʧ��
*****************************************************************************/
int bsp_rfclk_disable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return balong_rfclk_disable(mode, modem, chn);
}


int bsp_fem_power_down(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    int ret        = 0;

    osl_sem_down(&rf_pwr_sem[SEM_FEM]);

    ret = balong_fem_power_off(mode, modem, chn);
    if(ret){
        rf_print_error("rfic power down faild\n");
        ret = RFFE_ERROR;
    }

    osl_sem_up(&rf_pwr_sem[SEM_FEM]);

    return ret;
}

/*****************************************************************************
 ����    : bsp_fem_power_up
 ����    : RF �ϵ��׮
 ����    : ��
 ���    : ��
 ����    : rf��Դ����״̬
*****************************************************************************/
int bsp_fem_power_up(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    int ret = 0;

    osl_sem_down(&rf_pwr_sem[SEM_FEM]);

    ret = balong_fem_power_on(mode, modem, chn);

    osl_sem_up(&rf_pwr_sem[SEM_FEM]);

    return ret;
}

/*****************************************************************************
 �� �� ��  : bsp_rfic_power_status
 ��������  : RF��Դ״̬��ѯ��׮
 �������  :
 �������  :
 �� �� ֵ  : rf��Դ����״̬
*****************************************************************************/
PWC_COMM_STATUS_E bsp_rfic_power_status(PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    int ret = balong_rfic_power_status(modem, chn);

    if(0 == ret)
        return PWRCTRL_COMM_OFF;
    else if(1 == ret)
        return PWRCTRL_COMM_ON;
    else
        return PWC_COMM_STATUS_BUTT;

}

/*****************************************************************************
 �� �� ��  :bsp_pa_power_status
 ��������  :RF��Դ״̬��ѯ��׮
 �������  :
 �������  :
 �� �� ֵ  : pa��Դ����״̬
*****************************************************************************/
PWC_COMM_STATUS_E bsp_pa_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    int ret = balong_pa_power_status(mode, modem, chn);

    if(0 == ret)
        return PWRCTRL_COMM_OFF;
    else if(1 == ret)
        return PWRCTRL_COMM_ON;
    else
        return PWC_COMM_STATUS_BUTT;
}

/*****************************************************************************
 �� �� ��  :bsp_pa_power_status
 ��������  :RF��Դ״̬��ѯ��׮
 �������  :
 �������  :
 �� �� ֵ  : pa��Դ����״̬
*****************************************************************************/
PWC_COMM_STATUS_E bsp_fem_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    int ret = balong_fem_power_status(modem, chn);

    if(0 == ret)
        return PWRCTRL_COMM_OFF;
    else if(1 == ret)
        return PWRCTRL_COMM_ON;
    else
        return PWC_COMM_STATUS_BUTT;
}

/*****************************************************************************
 ����    : bsp_rffe_cfg_in_power_on
 ����    : ����ʱmipi���߿�����
 ����    : ��
 ���    : ��
 ����     : mipi�����Ƿ�ɹ���0Ϊ�ɹ�,1Ϊʧ��
*****************************************************************************/
int bsp_rffe_cfg_on_power_up(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    unsigned int  vote_bit = 0;
    unsigned int  first_on = 0;
    int           ret      = 0;

    vote_bit = RF_PWR_MODE_NUM*modem + mode;

    /*����fem�Ĺ��磬����ʹ�����ź���*/
    osl_sem_down(&rf_pwr_sem[SEM_FEM]);

    first_on = !rffe_cfg.vote[chn];
    rffe_cfg.vote[chn] |= (u64)1 << vote_bit;
    if(first_on){
        ret  = balong_rf_config_by_mipi_modem_on((u32)chn);
        ret |= balong_rf_config_anten_poweron((u32)chn);

        rffe_cfg.true_pwron_cnt[chn]++;
        rffe_cfg.true_pwron_time_stamp[chn] = bsp_get_slice_value();
    }
    rffe_cfg.pwron_cnt[chn]++;
    rffe_cfg.pwron_time_stamp[chn] = bsp_get_slice_value();

    osl_sem_up(&rf_pwr_sem[SEM_FEM]);

    return ret;
}

/*****************************************************************************
 ����    : bsp_rffe_cfg_on_power_down
 ����    : ����ʱmipi���߿�����
 ����    : ��
 ���    : ��
 ����     : mipi�����Ƿ�ɹ���0Ϊ�ɹ�,1Ϊʧ��
*****************************************************************************/
int bsp_rffe_cfg_on_power_down(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    u64  cur_state  = 0;
    u32  vote_bit   = 0;
    int  ret        = 0;
    int  power_flag = 0;

    vote_bit = RF_PWR_MODE_NUM * modem + mode;

    osl_sem_down(&rf_pwr_sem[SEM_FEM]);

    cur_state      = rffe_cfg.vote[chn];
    rffe_cfg.vote[chn] &= ~((u64)1 << vote_bit);

    if((0 == rffe_cfg.vote[chn]) && cur_state){
        ret = balong_rf_config_by_mipi_modem_off(chn);
        ret |= balong_rf_config_anten_poweroff(chn);

        rffe_cfg.true_pwroff_cnt[chn]++;
        rffe_cfg.true_pwroff_time_stamp[chn] = bsp_get_slice_value();
    }

    power_flag = balong_fem_power_status(modem, chn);
    if(!power_flag){
        ret  = balong_rf_config_by_mipi_allmodem_off();
        ret |= balong_rf_config_anten_allpoweroff();
        rffe_cfg.true_alloff_cnt++;
        rffe_cfg.true_alloff_time_stamp = bsp_get_slice_value();
    }
    rffe_cfg.pwroff_cnt[chn]++;
    rffe_cfg.pwroff_time_stamp[chn] = bsp_get_slice_value();

    osl_sem_up(&rf_pwr_sem[SEM_FEM]);

    return ret;

}

int mdrv_rffe_cfg_on_power_up(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return bsp_rffe_cfg_on_power_up(mode, modem, chn);
}

int mdrv_rffe_cfg_on_power_down(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return bsp_rffe_cfg_on_power_down(mode, modem, chn);
}

#endif
#ifdef CONFIG_CCORE_PM
extern int bsp_rf_resume_early(struct dpm_device *dev);
extern int bsp_rf_complete(struct dpm_device *dev);
extern int bsp_rf_suspend_late(struct dpm_device *dev);

static struct dpm_device g_rf_dpm_device={
    .device_name = "rf_dpm",
    .prepare = NULL,
    .suspend_early= NULL,
    .suspend = NULL,
    .suspend_late = bsp_rf_suspend_late,
    .resume_early = bsp_rf_resume_early,
    .resume = NULL,
    .resume_late = NULL,
    .complete = bsp_rf_complete,
};

/*resume*/
int bsp_rf_resume_early(struct dpm_device *dev)
{
    int ret = 0;

    ret  = balong_rf_power_resume();
    if(ret){
        rf_print_error("rffe power resume error!ret %d\n",ret);
    }
    rffe_cfg.resume_time_stamp = bsp_get_slice_value();
    return ret;
}

/*complete*/
int bsp_rf_complete(struct dpm_device *dev)
{
    int ret = 0;
    u32 time_stamp = 0;

    do{
        time_stamp = bsp_get_slice_value();
        udelay(5);        
    }while(get_timer_slice_delta(rffe_cfg.resume_time_stamp , time_stamp) < 5);

    ret = balong_rf_config_by_mipi_resume();
    if(ret){
        rf_print_error("rffe resume mipi config error!ret %d\n",ret);
    }
    rffe_cfg.complete_timestamp = bsp_get_slice_value();
    return ret;
}


/*suspend*/
int bsp_rf_suspend_late(struct dpm_device *dev)
{
    int ret = 0;

    ret = balong_rf_power_suspend();
    if(ret){
        rf_print_error("rffe power suspend error!ret is %d\n",ret);
    }
    rffe_cfg.suspend_late_timestamp = bsp_get_slice_value();
    return ret;
}

#endif

/*todo :������*/
int bsp_rffe_init(void)
{
    int ret = 0;
    int i   = 0;

    for(i = 0; i < SEM_NUM; i++){
        osl_sem_init(1, &rf_pwr_sem[i]);
    }

    /*�����ʼ��*/
    ret  = balong_rf_power_init();
    if(ret){
        rf_print_error("rf power init fail,ret = %d\n",ret);
    }

    udelay(200);

    /*MIPI���ó�ʼ��*/
    ret = balong_rf_config_by_mipi_init();
    if(ret){
        rf_print_error("rf power init fail,ret = %d\n",ret);
    }

    /*��Ƶ�߿����ó�ʼ��*/
    ret = balong_rf_config_anten_init();
    if(ret){
        rf_print_error("rf ant(gpio) init fail,ret = %d\n",ret);
    }

    /*ע��dpm �ص�*/
#ifdef CONFIG_CCORE_PM
    ret = bsp_device_pm_add(&g_rf_dpm_device);
    if(ret){
        rf_print_error("rffe add dpm device fail,ret = %d\n",ret);
    }
#endif

    rf_print_error("bsp rf init end,ret is %d\n",ret);
    return ret;
}

/*help��Ϣ*/

/*����ͶƱ��ѯ*/

/*��ǰ��Դ״̬��ѯ(���ء���ѹ)*/

/*dts���ò�ѯ*/
