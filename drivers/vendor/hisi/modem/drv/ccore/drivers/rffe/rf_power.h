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

#ifndef __RF_POWER_H__
#define __RF_POWER_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif            /* __cplusplus */

#include <product_config.h>
#include <osl_spinlock.h>
#include <osl_types.h>
#include <osl_sem.h>
#include <bsp_rf_balong.h>

#define PA_PWR_NUM  2 /*ÿ��pa��·��Դ*/
#define RF_PWR_NUM  4 /*ÿ��RF��·��Դ*/
#define FEM_PWR_NUM 1 /*ÿ��fem 1 ·��Դ*/
#define RF_CLK_NUM  2 /*pmu��rfclk buffer�ṩ��ʱ��*/

#define RF_PWR_SEM_FULL   1/*�ź�����ʼ��*/
#define RF_PWR_SEM_EMPUTY 0

#define RF_PWR_MODE_NUM  6
#define RF_PWR_MODEM_NUM PWC_COMM_MODEM_BUTT
#define RF_PWR_CHN_NUM   PWC_COMM_CHANNEL_BUTT

#define NV_PWC_ALLWAYS_ON 1

/*****************���Ͷ���begin*********************/
/*��������ö��*/
typedef enum PWR_CONSUMER{
    RF_VIO = 0,    /*[00] 1.8v��ʼ���򿪣�suspend close,resume open*/
    RFIC0_ANALOG0, /*[01] 1.29v*/
    RFIC0_ANALOG1, /*[02] 1.85v,*/
    RFIC0_ANALOG2, /*[03] 2.4v ״̬������*/
    RFIC0_DIGITAL, /*[04] ��������,all ways on*/
    RFIC1_ANALOG0, /*[05] k3v5�գ�v7r5 LDO22, 1.29v*/
    RFIC1_ANALOG1, /*[06] 1.85v,*/
    RFIC1_ANALOG2, /*[07] 2.4v ״̬������*/
    RFIC1_DIGITAL, /*[08] ��������,all ways on*/
    RFIC2_ANALOG0, /*[09]1.29v*/
    RFIC2_ANALOG1, /*[10]1.85v,*/
    RFIC2_ANALOG2, /*[11]2.4v ״̬������*/
    RFIC2_DIGITAL, /*[12]��������,all ways on*/
    TULPA0_VBIAS,  /*[13]vbat �������,LDO23,״̬��; etmodulator mipi�ӿ���vccһ��*/
    TULPA0_VCC,    /*[14]vbat �������,dcdc gpio (chip back),etmodulator mipi�ӿ���dspȷ��*/
    TULPA1_VBIAS,  /*[15]austin���ã�v7r5��TUL PA0һ��,ldo23?����*/
    TULPA1_VCC,    /*[16]austin���ã�v7r5��TUL PA0һ��*/
    TULPA2_VBIAS,  /*[17]vbat*/
    TULPA2_VCC,    /*[18]vbat*/
    GPA0_VBIAS,    /*[19]vbat*/
    GPA0_VCC,      /*[20]vbat (CHIPBACK),����DCDC*/
    GPA1_VBIAS,    /*[21]vbat*/
    GPA1_VCC,      /*[22]vbat(CHIPBACK),����DCDC*/
    GPA2_VBIAS,    /*[23]vbat*/
    GPA2_VCC,      /*[24]vbat(CHIPBACK),����DCDC*/
    FEM_VCC,       /*[25]LDO14,˫modem�ػ��رգ�����Ҫ��������modem*/   
    PWR_CONSUMER_NUM,/*[26]*/
}RFFE_POWER_ID_E;

/*debug info*/
struct onoff_detail{
    u64 vote;
	u32 hw_stat;
    unsigned int on_cnt[PWC_COMM_MODE_BUTT];
    unsigned int off_cnt[PWC_COMM_MODE_BUTT];
    unsigned int on_stamp[PWC_COMM_MODE_BUTT];
    unsigned int off_stamp[PWC_COMM_MODE_BUTT];
    unsigned int true_on_cnt[PWC_COMM_MODE_BUTT];
    unsigned int true_off_cnt[PWC_COMM_MODE_BUTT];
    unsigned int true_on_stamp[PWC_COMM_MODE_BUTT];
    unsigned int true_off_stamp[PWC_COMM_MODE_BUTT];
};

/*enum debug info*/
typedef enum pwr_dbg{
    PWR_RFIC = 0,
    PWR_FEM,
    PWR_PA,
    CLK_RFIC,
    PWR_DBG_NUM
}PWR_DBG_E;

/*debug info*/
struct rf_pwr_clk_debug{
	struct onoff_detail info[PWC_COMM_CHANNEL_BUTT];
};
/*dts���ñ���Ϣ*/
struct pwr_base_info {
    const char * name;       /*regulator node name*/
    unsigned int pwr_id;
    unsigned int init_on;    /*init power on*/
    unsigned int dpm_off;    /*dpm power off*/
    unsigned int disable_off;/*power off interface disable*/
    osl_sem_id   sem;

    u64          vote;
    unsigned int voltage;
    unsigned int valid;
    struct regulator *regu;
};

/*rf clk info*/
struct clk_base_info{
    osl_sem_id  sem;
    u64         vote;
};
#ifdef CONFIG_RFFE_POWER
int balong_rfpower_set_voltage( EM_MODEM_CONSUMER_ID_E consumer_id, u32 voltage_mv );


int balong_rfpower_get_voltage( EM_MODEM_CONSUMER_ID_E consumer_id);


int balong_pa_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

int balong_pa_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);


int balong_pa_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);


int balong_rfic_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);


int balong_rfic_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);


int balong_rfic_power_status(PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);


int balong_fem_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);


int balong_fem_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);


int balong_fem_power_status(PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);


int balong_rf_power_resume(void);


int balong_rf_power_suspend(void);


int balong_rf_power_init(void);


int balong_rfclk_enable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);


int balong_rfclk_disable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn);

#else

static inline int balong_rfpower_set_voltage( EM_MODEM_CONSUMER_ID_E consumer_id, u32 voltage_mv )
{
    return RFFE_OK;
}


static inline int balong_rfpower_get_voltage( EM_MODEM_CONSUMER_ID_E consumer_id)
{
    return RFFE_OK;
}


static inline int balong_pa_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return RFFE_OK;
}



static inline int balong_pa_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return RFFE_OK;
}


static inline int balong_pa_power_status(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 1;
}



static inline int balong_rfic_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return RFFE_OK;
}


static inline int balong_rfic_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return RFFE_OK;
}


static inline int balong_rfic_power_status(PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 1;
}


static inline int balong_fem_power_on(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return RFFE_OK;
}


static inline int balong_fem_power_off(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return RFFE_OK;
}


static inline int balong_fem_power_status(PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 1;
}


static inline int balong_rf_power_resume(void)
{
    return RFFE_OK;
}

static inline int balong_rf_power_suspend(void)
{
    return RFFE_OK;
}

/*debug*/

static inline int balong_rf_power_init(void)
{
    return RFFE_OK;
}


int balong_rfclk_enable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 0;
}


int balong_rfclk_disable(PWC_COMM_MODE_E mode, PWC_COMM_MODEM_E modem, PWC_COMM_CHANNEL_E chn)
{
    return 0;
}
#endif

/*****************���Ͷ���over*********************/

#ifdef __cplusplus /* __cplusplus */
}
#endif             /* __cplusplus */

#endif             /*  __RF_POWER_H__ */

