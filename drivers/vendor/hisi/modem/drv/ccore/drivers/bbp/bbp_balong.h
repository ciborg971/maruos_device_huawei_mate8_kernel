
/*lint -save -e656 -e959*/
#ifndef __BBP_BALONG_H__
#define __BBP_BALONG_H__

#include "osl_types.h"
#include "osl_bio.h"
#include <osl_spinlock.h>

#include "mdrv_public.h"
#include "mdrv_pm.h"
#include "drv_nv_def.h"

#include "bsp_memmap.h"
#include "bsp_om.h"
#include "bsp_bbp.h"
#include "bsp_clk.h"
#include "hi_bbp.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
    BBP_BASE_APB = 0,
    BBP_BASE_DRX,
    BBP_BASE_BUTT
}BBP_BASE_ID_E;

#define BBP_PWC_NULL 0xff
#define BBP_PWC_ALWAYSON 0xee
#define BBP_PWR_DEPENDENT 0xffff

typedef enum{
    BBP_INT_LTETF,
    BBP_INT_TDSTF,
    BBP_INT_BUTT
}BBP_INT_ID_E;
typedef enum{
    BBP_VOTE_UNLOCK = 0,
    BBP_VOTE_LOCK = 1,
}BBP_VOTE_LOCK_E;
typedef enum{
    BBP_VOTE_PWR,
    BBP_VOTE_CLK,
    BBP_VOTE_PLL,
    BBP_VOTE__BUTT
}BBP_VOTE_ID_E;

/*ʱ�������*/
#if 0
typedef enum{
    BBP_STAMP_LTETF,
    BBP_STAMP_TDSTF = BBP_STAMP_LTETF + 8,
    BBP_STAMP_SUSPEND = BBP_STAMP_TDSTF + 8,
    BBP_STAMP_RESUME = BBP_STAMP_SUSPEND + 5,
    BBP_STAMP_PWRON = BBP_STAMP_RESUME + 5,
    BBP_STAMP_PWROFF = BBP_STAMP_PWRON + BBP_VOTE_PWR_NUM,
    BBP_STAMP_CLKON = BBP_STAMP_PWROFF + BBP_VOTE_PWR_NUM,
    BBP_STAMP_CLKOFF = BBP_STAMP_CLKON + BBP_VOTE_CLK_NUM,
    BBP_STAMP_PLLON = BBP_STAMP_CLKOFF + BBP_VOTE_CLK_NUM,
    BBP_STAMP_PLLOFF,
    BBP_STAMP_BUTT
}BBP_STAMP_E;
#endif

typedef enum{
    BBP_STAMP_LTETF,
    BBP_STAMP_TDSTF,
    BBP_STAMP_PWRON,
    BBP_STAMP_PWROFF,
    BBP_STAMP_CLKON,
    BBP_STAMP_CLKOFF,
    BBP_STAMP_PLLON,
    BBP_STAMP_PLLOFF,
    BBP_STAMP_SUSPEND,
    BBP_STAMP_RESUME,
    BBP_STAMP_BUTT
}BBP_STAMP_E;
typedef enum{
    BBP_LOG_INFO,/*����*/
    BBP_LOG_ACTUAL/*ʵ�ʲ����˵�/��/pll*/
}BBP_LOG_TYPE_E;
typedef enum{
    BBP_LOG_POWERON = 0,
    BBP_LOG_POWEROFF,
    BBP_LOG_CLKON,
    BBP_LOG_CLKOFF,
    BBP_LOG_PLLON,
    BBP_LOG_PLLOFF,
    BBP_LOG_OTHERS
}BBP_LOG_ID_E;
struct bbp_pwc_infolog
{
    unsigned int ops_id;
    unsigned int   act_module;       /*��¼ʵ�ֿ��ز��������*/
    unsigned int   act_modem;       /*��¼ʵ�ֿ��ز����Ŀ�(�������Ǹ���)*/
    unsigned int   act_mode;       /*��¼ʵ�ֿ��ز�����ģ*/
    unsigned int   task_id;
};
struct bbp_pwc_actlog
{
    u32 ops_id;
    u32 pwc_id;
    u64 vote_lock; /*��ǰͶƱ���*/
    unsigned int   act_module;       /*��¼ʵ�ֿ��ز��������*/
    unsigned int   act_modem;       /*��¼ʵ�ֿ��ز����Ŀ�(�������Ǹ���)*/
    unsigned int   act_mode;       /*��¼ʵ�ֿ��ز�����ģ*/
    unsigned int   task_id;
};
struct bbp_part_info
{
    const char *name;/*��������*/
    u32 id;
    u32 reg_base; /*�Ĵ�����ַ*/
    u32 reg_phyaddr; /*�Ĵ��������ַ*/
    u32 size;
};
struct bbp_vote_info
{
    u32 id; /*���ĸ�pwr����clk���е�ͶƱ*/
    int   status;               /*��ǰʵ�ʵĿ���״̬*/
    u64   lock;                 /*��¼ͶƱ���,��ͬbit����ͬģ*/
    unsigned int   enable_vote[BBP_MODULE_NUM][BBP_MODEM_NUM][BBP_MODE_NUM];      /*��¼��ģ�Ŀ�ͶƱ����*/
    unsigned int   disable_vote[BBP_MODULE_NUM][BBP_MODEM_NUM][BBP_MODE_NUM];     /*��¼��ģ�Ĺ�ͶƱ����*/
    unsigned int   enable_actual;        /*��¼��ʵ���Ĵ���*/
    unsigned int   disable_actual;       /*��¼��ʵ�صĴ���*/
    unsigned int   enable_module;       /*��¼ʵ�ֿ����������*/
    unsigned int   disable_module;       /*��¼ʵ�ֹز��������*/
    unsigned int   enable_modem;       /*��¼ʵ�ֿ������Ŀ�(�������Ǹ���)*/
    unsigned int   disable_modem;       /*��¼ʵ�ֹز����Ŀ�(�������Ǹ���)*/
    unsigned int   enable_mode;       /*��¼ʵ�ֿ�������ģ*/
    unsigned int   disable_mode;       /*��¼ʵ�ֹز�����ģ*/
};
struct bbp_cri_ctrl/*clk,rst,iso���ýṹ��*/
{
    u32 en_reg;
    u32 dis_reg;
    u32 state_reg;
    u32 en_bit;
    u32 dis_bit;
    u32 state_bit;
};

struct bbp_mos_ctrl /*cmos���ýṹ��*/
{
    u32 en_reg;
    u32 dis_reg;
    u32 rdy_reg;
    u32 state_reg;
    u32 en_bit;
    u32 dis_bit;
    u32 rdy_bit;
    u32 state_bit;
};

typedef void (*bbpintfunc)(void);
/*�ж���ؽṹ��*/
struct bbp_int_info
{
    unsigned int irq;/* �жϺ�*/
    u32 cnt;/* �жϼ���*/
    bbpintfunc func;/*�жϴ�����*/
};

typedef enum{
    SOC_TO_BBP= 0,
    BBP_TO_SOC = 1,
}BBP_DMA_TYPE;
/*bbp�͹�����ؽṹ��*/
struct bbp_reg_save
{
    u32 reg_start;/*��Ҫ����ļĴ���Ƭ�ϵ���ʼ��ַ*/
    u32 size;    /* ��Ҫ�洢�������Ĵ����ռ��С����λΪbyte */
};

struct bbp_dpm_info
{
    ST_PWC_SWITCH_STRU pwc_nv;/*�͹����ӵ翪�ؿ���*/
    u32 enable_dma;      /*0:memcpy��ʽ;1:dma��ʽ*/
    u32 dma_chan;       /*ʹ�õ�dmaͨ����*/
    u32 pwr_default;    /*����Ĭ�����µ������0-ʲôҲ������1-�ϵ翪�ӣ�2-�µ����*/
    char * ctu_save_addr; /*bbc�����ַ*/
    u32 ctu_save_size; /*bbc�����С*/
    u32 irm_data;         /*����irm����*/
    u32 ckg_bypass_data;  /*����ckg_bypass ����*/
    u32 bbc_reset;        /*����bbc����ʱ�Ӻ͸�λ���ؿ��ƣ��������ȥ��*/
    struct bbp_reg_save regsave_list;/*�Ĵ����ָ��б�*/
};
struct bbp_pwr_ctrl
{
    struct bbp_cri_ctrl clk_ctrl;
    struct bbp_cri_ctrl rst_ctrl;
    struct bbp_cri_ctrl iso_ctrl;
    struct bbp_mos_ctrl mos_ctrl;
};
struct bbp_pwr_list_cfg
{
    u32 pwc_pwr[BBP_VOTE_PWR_NUM];/*pwr_id*/
};
struct bbp_pm_pwr_info
{
    const char   *name;            /*bbpģʽ��Ӧ��*/
    u32 pwr_id;
    u32 repair_id;                 /*��Ӧ��Ҫrepair��mem id*/
    struct bbp_cri_ctrl clk_ctrl;
    struct bbp_cri_ctrl rst_ctrl;
    struct bbp_cri_ctrl iso_ctrl;
    struct bbp_mos_ctrl mos_ctrl;
    spinlock_t  spinlock;
};
struct bbp_pwr_info{
    struct bbp_pwr_list_cfg pwr_list[BBP_MODULE_NUM][BBP_MODEM_NUM][BBP_MODE_NUM];
    struct bbp_pm_pwr_info pwr_act[BBP_PWR_NUM];
};
struct bbp_clk_list_cfg
{
     u32 pwc_clk[BBP_VOTE_CLK_NUM];/*clk_id*/
};
struct bbp_pm_clk_info
{
    const char   *name;            /*bbp clk��Ӧ��*/
    u32 clk_id;
    struct bbp_cri_ctrl clk_ctrl;    /*�����Ӳ���*/
    struct bbp_cri_ctrl rst_ctrl;
    spinlock_t  spinlock;
};
struct bbp_clk_info{
    struct bbp_clk_list_cfg clk_list[BBP_MODULE_NUM][BBP_MODEM_NUM][BBP_MODE_NUM];
    struct bbp_pm_clk_info clk_act[BBP_CLK_NUM];
    u32 rst_flag;/*ʹ��clkʱ�Ƿ�Ҳ�⸴λ*/
};
struct bbp_clksrc_dbg{
    u32 channel_id;
    u32 timestamp;
    u32 reg_act;
};
/*gbbp clksrc*/
struct bbp_clksrc{
    struct bbp_clksrc_dbg dbg_ctrl;
};
/*������ؽṹ��*/
struct bbp_debug_info
{
    u32 time_debug;             /*bbp���ֵ�ʱ��ͳ�Ƶ��Կ���*/
    u32 pwc_debug;              /*�͹��ĵ��Կ���*/
    struct bbp_pwc_actlog pwc_log;
    u32 timing_err;             /*��ȡtimingʧ�ܵĴ���*/
};
/*��ά�ɲ���ؽṹ��*/
typedef enum{
    BBP_LTEINT_EN_IN,          /*0*/
    BBP_LTEINT_EN_CLS,         /*1*/
    BBP_LTEINT_EN_UNMASK,      /*2*/
    BBP_LTEINT_DIS_IN,         /*3*/
    BBP_LTEINT_DIS_MASK,       /*4*/
    BBP_LTEINT_HANDLE_FUNC,    /*7*/
    BBP_LTEINT_CLEAR_IN,       /*8*/
    BBP_LTEINT_CLEAR_CLS,      /*9*/
    BBP_LTEINT_BUTT
}BBP_LTEINTSTAMP_E;
typedef enum{
    BBP_TDSINT_EN_IN,          /*0*/
    BBP_TDSINT_EN_CLS,         /*1*/
    BBP_TDSINT_EN_UNMASK,      /*2*/
    BBP_TDSINT_DIS_IN,         /*3*/
    BBP_TDSINT_DIS_MASK,       /*4*/
    BBP_TDSINT_CLEAR_IN,       /*5*/
    BBP_TDSINT_CLEAR_CLS,      /*6*/
    BBP_TDSINT_HANDLE_FUNC,    /*8*/
    BBP_TDSINT_BUTT
}BBP_TDSINTSTAMP_E;
typedef enum{
    BBP_PREPAIR_IN,            /*0*/
    BBP_PREPAIR_END,           /*3*/
    BBP_SUSPEND_IN,            /*4*/
    BBP_SUSPEND_BBCRST,        /*4*/
    BBP_SUSPEND_END,           /*8*/
    BBP_SUSPEND_BUTT
}BBP_SUSPENDSTAMP_E;
typedef enum{
    BBP_RESUME_IN,             /*0*/
    BBP_RESUME_BBCUNRST,
    BBP_RESUME_END,            /*3*/
    BBP_COMPLETE_IN,           /*4*/
    BBP_COMPLETE_END,          /*7*/
    BBP_RESUME_BUTT
}BBP_RESUMESTAMP_E;
typedef enum{
    BBP_DMATRAN_IN,             /*0*/
    BBP_DMATRAN_CLKEN,         /*2*/
    BBP_DMATRAN_ADDR,         /*2*/
    BBP_DMATRAN_END,
    BBP_DMAFINISH_IN,
    BBP_DMAFINISH_BUSY,
    BBP_DMAFINISH_END,            /*3*/
    BBP_DMACONFIG,
    BBP_DMA_BUTT
}BBP_DMASTAMP_E;

struct bbp_om_info
{
    /*ʱ����ռ�*/
    u32 stamp_ltetf[BBP_LTEINT_BUTT];
    u32 stamp_tdstf[BBP_TDSINT_BUTT];
    u32 stamp_pwron[BBP_VOTE_PWR_NUM];
    u32 stamp_pwroff[BBP_VOTE_PWR_NUM];
    u32 stamp_clkon[BBP_VOTE_CLK_NUM];
    u32 stamp_clkoff[BBP_VOTE_CLK_NUM];
    u32 stamp_pllon[1];
    u32 stamp_plloff[1];
    u32 stamp_suspend[BBP_SUSPEND_BUTT];
    u32 stamp_resume[BBP_RESUME_BUTT];
    u32 stamp_dma[BBP_DMA_BUTT];

    struct bbp_vote_info pwr[BBP_VOTE_PWR_NUM]; /*pwrͶƱ�ռ�*/
    struct bbp_vote_info clk[BBP_VOTE_CLK_NUM]; /*clkͶƱ�ռ�*/
    struct bbp_vote_info pll;/*pllͶƱ�ռ�*/
};

/*���bug*/
struct bbp_bug{
    u32 dma_clk_bug;/*�Ƿ����dma����lte clk��bug*/
    u32 dma_clk_flag;/*dma�Ƿ����lbbp clk*/
};

struct bbp_info
{
    struct bbp_part_info part[BBP_PART_BUTT];   /*��part��Ϣ*/
    struct bbp_pwr_info pwr;        /*����Դ�������Ϣ*/
    struct bbp_clk_info clk;        /*��ʱ�������Ϣ*/
    struct bbp_int_info bbpint[BBP_INT_BUTT];      /*�ж����*/
    struct bbp_dpm_info dpm;                        /*�͹������*/
    struct bbp_debug_info dbg;                      /*�������*/
    struct bbp_om_info *om;                      /*��ά�ɲ����*/
    struct bbp_om_info ominfo;  /*dump�ռ����ʧ��ʱ��¼���ÿռ�*/
    struct bbp_bug bug;
    struct bbp_clksrc clksrc[PWC_COMM_MODEM_BUTT]; /*gclk src sel*/
 };

/* ����ֵ���� */
typedef enum
{
    BBP_ERR_PARAM_NULL = -0xF000,
    BBP_ERR_PARAM_INVALID,
    BBP_ERR_TIME_OUT,
    BBP_ERR_UNKNOWN,
    BBP_ERR = -1,
    BBP_OK = 0
} EM_BBP_RET;

typedef enum
{
    PWC_OFF = 0,
    PWC_ON = 1,
    PWC_BUTT
}PWC_STATUS_E;

#define BBP_POWER_CTRL_VOTE_INIT  (unsigned char)(0<<PWC_COMM_MODE_WCDMA \
                                                | 0<<PWC_COMM_MODE_GSM \
                                                | 0<<PWC_COMM_MODE_LTE \
                                                | 0<<PWC_COMM_MODE_TDS)
#define BBP_DMA_LEN_BIT_OFFSET    0
#define BBP_DMA_FAST_BIT_OFFSET    16

#define BBP_DMA_ALL_DATA_BIT_OFFSET 20
#define BBP_DMA_FAST_SOFT_BIT_OFFSET 24
#define BBP_DMA_ENABLE_BIT_OFFSET 28

#define BBP_IRM_SAVE_OFFSET 0xa000
#define WAKEUP_INT_CLEAR_TIMEOUT 8

#define  BBP_TASK_STK_SIZE            (0x1000)

#define  bbp_print_error(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_BBP, "[bbp]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  bbp_print_info(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_BBP, "[bbp]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  bbp_print_debug(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_BBP, "[bbp]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

/*ģ���Լ����ƵĴ�ӡ�����Լ��Ĵ�ӡ���ؿ���*/

/*��������*/
/*�����ʹ��*/
void bbp_int_ltetf_regcb(bbpintfunc pfunc);
void bbp_int_ltetf_clear(void);
int bbp_int_ltetf_enable(void);
void bbp_int_ltetf_disable(void);
void bbp_int_tdstf_regcb(bbpintfunc pfunc);
int bbp_int_tdstf_enable(void);
void bbp_int_tdstf_disable(void);
void bbp_int_wakeup_enable(PWC_COMM_MODE_E mode);
void bbp_int_wakeup_disable(PWC_COMM_MODE_E mode);
void bbp_int_wakeup_clear(PWC_COMM_MODE_E mode);
int bbp_int_timer_init(PWC_COMM_MODE_E mode);
u16 bbp_get_lte_sysframe(void);
u16 bbp_get_lte_subframe(void);
u16 bbp_get_tds_subframe(void);
u16 bbp_set_tds_subframe_offset(u16 sf_offset);
u32 bbp_get_tds_sleeptime(void);
unsigned int bbp_get_tds_clkswitch(void);
u32 bbp_get_wakeup_time(PWC_COMM_MODE_E mode);
u32 bbp_get_gubbp_wakeup_status(void);
int bbp_get_meansflag(PWC_COMM_MODE_E enCommMode);
int bbp_lps_get_ta(void);
int bbp_get_timing_val(BBP_TIMING_STRU *pstTiming);
int bbp_gbbp_select_clksrc (PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel);

int bbp_power_up(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);
int bbp_power_down(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);
int bbp_power_status(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);
int bbp_clk_enable(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);
int bbp_clk_disable(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);

void* bbp_part_addr_get(BBP_PART_ID_E part_id);
int bbp_init(void);

/*����ʵ��ʹ��*/
int bbp_dts_init(void);
unsigned int bbp_pwrctrl_is_enabled(u32 pwr_id);
void bbp_pwrctrl_enable(u32 pwr_id);
void bbp_pwrctrl_disable(u32 pwr_id);
unsigned int bbp_clkctrl_is_enabled(u32 clk_id);
void bbp_clkctrl_enable(u32 clk_id);
void bbp_clkctrl_disable(u32 clk_id);
unsigned int bbp_rstctrl_is_enabled(u32 clk_id);
void bbp_rstctrl_enable(u32 clk_id);
void bbp_rstctrl_disable(u32 clk_id);
/*���Ժ���ʹ��*/
void bbp_dma_tran(struct bbp_dma_cfg dma_config);
void bbp_dma_finish(struct bbp_dma_cfg dma_config);
void bbp_poweron(void);
void bbp_poweroff(void);

int bbp_clk_status(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);
/*debug use*/
unsigned int bbp_pwr_rst_status(u32 pwr_id);
unsigned int bbp_pwr_iso_status(u32 pwr_id);
unsigned int bbp_pwr_clk_status(u32 pwr_id);
unsigned int bbp_pwr_cmos_status(u32 pwr_id);
void bbp_disable(u32 clk_id);

int bbp_clkctrl_status(u32 enClkId);
int bbp_rstctrl_status(u32 enClkId);

#ifdef __cplusplus
}
#endif

#endif
/*lint -restore*/