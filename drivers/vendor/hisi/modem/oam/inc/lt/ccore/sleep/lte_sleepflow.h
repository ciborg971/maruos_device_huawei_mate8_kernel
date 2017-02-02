
#ifndef __LTE_SLEEPFLOW_H__
#define __LTE_SLEEPFLOW_H__


#if __cplusplus
extern "C"
{
#endif

#include "product_config.h"


#if defined (CHIP_BB_HI6210)
#define MSP_IN_V9R1
#else
#undef MSP_IN_V9R1
#endif

#include "mdrv.h"
#include "vos.h"
#include <VosPidDef.h>
#include <RfNvId.h>
#include <PhyNvDefine.h>
#include <msp_diag.h>
#include <TLPhyInterface.h>
#include <msp_nv_id.h>
#include <msp_nv_def.h>
#include <mdrv_dsp.h>
#ifndef MSP_IN_V9R1
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <soc_memmap_comm.h>
#include <hi_bbp_ltedrx.h>
#else
#include "NVIM_Interface.h"
#include <NvIdList.h>
#endif

/* Ŀǰ�汾���ᳬ��4ͨ�� */
#define MSP_SLEEP_CHAN_NUM          3

/* Ŀǰ�汾���ᳬ��2TCXO */
#define MSP_SLEEP_TCXO_NUM          2

#define MSP_PWR_SYSTEM_RUN          (1<<0)      /*��ǰDSP״̬ΪRUN*/
#define MSP_PWR_HALT_INT            (1<<1)      /*��־��ǰ��halt�жϵ������ҶԴ��жϻ�û�д������*/
#define MSP_PWR_FORCE_AWAKE         (1<<2)      /*��־��ǰ��ǿ�ƻ�������*/
#define MSP_PWR_WAIT_RESUMER        (1<<3)      /*��־��ǰ�Ѿ���ɻ��Ѳ������ȴ�DSP�ָ����*/
#define MSP_PWR_WAKEUP              (1<<4)      /*��־�Ƿ���wakeup�ж���Ӧ*/

/*���ڿ�ά�ɲ�*/
#define MSP_CREATE_TASK_SEM_FAIL    (1<<10)      /*��־��ʼ��ʱ��ʼ��˯��������ź���ʧ��*/
#define MSP_CREATE_TASK_FAIL        (1<<11)      /*��־��ʼ��ʱ����˯������ʧ��*/
#define MSP_INT_CONNECT_FAIL        (1<<12)      /*��־��ʼ��ʱ�ҽ��ж�ʧ��*/
#define MSP_INT_ENABLE_FAIL         (1<<13)      /*��־��ʼ��ʱʹ���ж�ʧ��*/
#define MSP_READ_NV_FAIL            (1<<14)      /*��־��ʼ��ʱ��ȡNVʧ��*/
#define MSP_DFS_REQUEST_FAIL        (1<<15)      /*��־��ʼ��ʱ����DFS��ƵIDʧ��*/
#define MSP_DFS_HALT_UPDATE_FAIL    (1<<16)      /*��־��Halt�ж���ͶƱDFSʧ��*/
#define MSP_DFS_RUN_UPDATE_FAIL     (1<<17)       /*��־��RUN DSPʱͶƱDFSʧ��*/
#define MSP_DFS_HW_UPDATE_FAIL      (1<<18)       /*��־��PS���õĽӿ���ͶƱDFSʧ��*/
#define MSP_REPEAT_HALT_ERROR       (1<<19)       /*��¼DSP�ظ�����halt�ж�*/
#define MSP_CREATE_TCXO0_SEM_FAIL   (1<<20)      /*��־��ʼ��ʱ��ʼ��˯��������ź���ʧ��*/
#define MSP_CREATE_TCXO1_SEM_FAIL   (1<<21)      /*��־��ʼ��ʱ��ʼ��˯��������ź���ʧ��*/


#define MSP_SLEEP_TASK_PRI          (2)         /*�������ȼ�*/
#define MSP_EXC_TASK_PRI            (63)       /*�������ȼ�*/
#define WAIT_FOR_EVER               (0)
#define SLEEP_RECORD_NUM            (100)
#define MSP_SLEEP_ERROR             (-1)

/* sleepģ����ϢID */
#define ID_MSG_SLEEP_WAKEUP_SLICE_MNTN      0xf000f001


typedef struct
{
    VOS_MSG_HEADER                     /*VOSͷ */
    VOS_UINT32      ulMsgId;
    
    VOS_UINT32      ulHalt;
    VOS_UINT32      ulSleepStart;
    VOS_UINT32      ulSleepEnd;
    VOS_UINT32      ulWakeup;
    VOS_UINT32      ulForceAwake;
    VOS_UINT32      ulWakeupStart;
    VOS_UINT32      ulAwake_CB_0;
    VOS_UINT32      ulAwake_CB_1;
    VOS_UINT32      ulFORCE_AWAKE_INNER_0;
    VOS_UINT32      ulHWPOWERUP_0;
    VOS_UINT32      ulHWPOWERUP_1;
    VOS_UINT32      ulHWPOWERUP_2;
    VOS_UINT32      ulHWPOWERUP_3;
    VOS_UINT32      ulHWPOWERUP_4;
    VOS_UINT32      ulHWPOWERUP_5;
    VOS_UINT32      ulHWPOWERUP_6;
    VOS_UINT32      ulHWPOWERUP_7;
    VOS_UINT32      ulHWPOWERUP_8;
    VOS_UINT32      ulHWPOWERUP_9;
    VOS_UINT32      ulHWPOWERUP_MAX;
    VOS_UINT32      ulFORCE_AWAKE_INNER_1;
    VOS_UINT32      ulWakeupEnd;
    VOS_UINT32      ulResume;
}MSP_SLEEP_MNTN_MSG_STRU;

#ifndef MSP_IN_V9R1
/* �����õĹ����ڴ�
#define DEBUG_TIMESTAMP_ADDR        (SHM_TIMESTAMP_ADDR + 0x200)
#define DEBUG_FOR_DSP_ADDR          (SHM_TIMESTAMP_ADDR + 0x8)
*/
#else

typedef struct
{
    VOS_UINT8 ucABBSwitch; /*��Ӧģʽʹ�õ�ABB����ͨ����0 ͨ��0, 1: ͨ��1, 2: ͬʱʹ������ͨ��*/
    VOS_UINT8 ucRFSwitch;  /*��Ӧģʽʹ�õ�RF����ͨ����0 ͨ��0, 1: ͨ��1, 2: ͬʱʹ������ͨ��*/
    VOS_UINT8 ucTCXOSwitch; /*��Ӧģʽʹ�õ�TCXO ID 0 TCXO0, 1: TCXO1*/
    VOS_UINT8 reserve;
}NV_TLMODE_BASIC_PARA_STRU;

typedef struct
{
    NV_TLMODE_BASIC_PARA_STRU stModeBasicParam[2];/*�±�Ϊ0:LTE, 1:TDS*/
}NV_TLMODE_CHAN_PARA_STRU;

/* drx delay flag */
typedef struct
{
    VOS_UINT8         lpm3_flag;         /* 0x11 ����lpm3 */
    VOS_UINT8         lpm3_0;            /* 1��delay,�����ر�delay */
    VOS_UINT8         lpm3_1;
    VOS_UINT8         lpm3_2;
    VOS_UINT8         lpm3_3;
    VOS_UINT8         lpm3_4;
    VOS_UINT8         lpm3_5;
    VOS_UINT8         drv_flag;          /* 0x22 ����drv */
    VOS_UINT8         drv_0;             /* 1��delay,�����ر�delay */
    VOS_UINT8         drv_1;
    VOS_UINT8         drv_2;
    VOS_UINT8         drv_3;
    VOS_UINT8         drv_4;
    VOS_UINT8         drv_5;
    VOS_UINT8         msp_flag;          /* 0x33 ����msp */
    VOS_UINT8         msp_0;             /* 1��delay,�����ر�delay */
    VOS_UINT8         msp_1;
    VOS_UINT8         msp_2;
    VOS_UINT8         msp_3;
    VOS_UINT8         msp_4;
}DRV_DRX_DELAY_STRU;

#endif
/*��ά�ɲ��ڴ����*/
/*��ǰ��״̬��*/
#define MSP_EXC_PWR_STATUS_OFFSET                   ((VOS_UINT)(g_msp_pwrctrl.dump_base))
#define MSP_EXC_PWR_STATUS_SIZE                     (0x4)
/*DSP��˯ǳ˯��־*/
#define MSP_EXC_SLEEP_FLAG_OFFSET                   (MSP_EXC_PWR_STATUS_OFFSET + MSP_EXC_PWR_STATUS_SIZE)
#define MSP_EXC_SLEEP_FLAG_SIZE                     (0x4)

#define MSP_EXC_FORBID_DSP_SLEEP_OFFSET             (MSP_EXC_SLEEP_FLAG_OFFSET + MSP_EXC_SLEEP_FLAG_SIZE)
#define MSP_EXC_FORBID_DSP_SLEEP_SIZE               (0x4)

#define MSP_EXC_DSP_STATE_OFFSET                    (MSP_EXC_FORBID_DSP_SLEEP_OFFSET + MSP_EXC_FORBID_DSP_SLEEP_SIZE)
#define MSP_EXC_DSP_STATE_SIZE                      (0x4)
/*ʱ����м�¼*/
#define MSP_EXC_RECORED_TIME_OFFSET                 (MSP_EXC_DSP_STATE_OFFSET + MSP_EXC_DSP_STATE_SIZE)
#define MSP_EXC_RECORED_TIME_SIZE                   (MSP_EXC_STATE_SLICE_OFFSET - MSP_EXC_RECORED_TIME_OFFSET)
/*״̬��¼*/
#define MSP_EXC_STATE_SLICE_OFFSET                  (MSP_EXC_END_OFFSET - MSP_EXC_STATE_SLICE_SIZE)
#define MSP_EXC_STATE_SLICE_SIZE                    (200)

#define MSP_EXC_END_OFFSET                          (MSP_EXC_PWR_STATUS_OFFSET + (g_msp_pwrctrl.dump_len))


typedef struct
{
    VOS_UINT32 ulTime;
    char acType[16];
} SLEEP_TIME_STRU;


typedef struct
{
    VOS_UINT32  ulCount;
    SLEEP_TIME_STRU astRecord[SLEEP_RECORD_NUM];
} TLSLEEP_RECORD_STRU;

/*�������̼�¼*/
typedef enum tagDRX_STATE_SLICE
{
    DRX_HALT_INT = 0,               /* ��¼DRX halt�ж�*/
    DRX_SLEEP_TASK = 1,             /* ��¼DRX ����˯������ʼִ��˯�߲��� */
    SLEEP_TASK_NOT_NEED_DEAL = 2,   /* ��¼ͬʱ�յ�˯�߻�������Sleep�������ٴ��� ������ֱ�ӻָ�*/
    DSP_DEEP_SLEEP_COUNT = 3,       /* DSP��˯��¼*/
    DSP_LIGHT_SLEEP_COUNT =4,       /* DSPǳ˯��¼*/
    STORE_DSP_TCM_FAIL = 5,         /* ��¼����EDMAͨ������DSP TCMʧ�� */
    SLEEP_VOTE_UNLOCK = 6,          /* ��¼ͶƱ˯�ߵĴ���*/
    DRX_INVALID_WAKEUP_INT = 7,     /* ��¼��Ч�Ļ����ж� */
    DRX_WAKEUP_INT = 8,             /* ��¼DRX����wakeup�����ж� */
    RESTORE_DSP_TCM_FAIL = 9,       /* ��¼����EDMAͨ���ָ�DSP TCMʧ�� */
    DRX_FORCE_AWAKE_API = 10,       /* ��¼DRXǿ�ƻ������̽ӿڵ��� */
    DRX_FORCE_AWAKE_NOT_DEAL = 11,  /* ��¼�Ѿ��л��Ѳ�������Ҫ��Ӧ���Ѳ���*/
    DRX_FORCE_AWAKE_RUN_RETURN = 12,/* ��¼�յ�ǿ�ƻ���ʱDSP�Ѿ�RUN*/
    DRX_FAIL_WAIT_TCXO_SEM = 13,    /* �ȴ�TCXO�ȶ�����10ms*/
    RESUME_NOTIFY_MAILBOX = 14,     /* ��¼RSUME�ж���֪ͨ���� DSP�Ѿ�ǿ�ƻ���*/
    DRX_RESUME_INT = 15,            /* ��¼DRX ���ѻָ�����ж� */
    DRX_CHECK_DSP_STATUS = 16,      /* ��¼DRX������ѯ��ǰDSP��״̬�Ľӿڱ����� */
    DSP_SLEEP_FLAG_ERROR = 17,      /* ��¼DSP��˯ǳ˯��־����*/
    DRX_HALT_RESUME_CONFLICT = 18,  /* ��¼DSP˯�߻����ж�ͬʱ���������δ���*/

    DRX_SLAVE_WAKE_INT,             /* ��¼LTE��Ϊ��ģ�յ���ģ�����ж�*/
    
    DRX_SLEEP_START,                /* ��¼��ʼִ��˯�ߵ�ʱ�� */
    DRX_SLEEP_END,                  /* ��¼����ִ��˯�ߵ�ʱ��*/
    
    DRX_WAKEUP_START,               /* ��¼��ʼִ�л��ѵ�ʱ��*/
    DRX_WAKEUP_END,                 /* ��¼����ִ�л��ѵ�ʱ��*/

    DRX_STATE_BUTTON = 25
}DRX_STATE_SLICE;

typedef struct
{
    VOS_UINT32 ulCount;              /* ��¼�����Ĵ��� */
    VOS_UINT32 ulSlice;              /* ��¼������Sliceֵ */
}SLEEP_RECORD_STRU;

/*****************************************************************************
 �ṹ��    : SLEEP_NV_DRX_RESUME_TIME_STRU
 �ṹ˵��  : ���̼�¼��չ��Ԫ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAbbPwrRsmTime;                        /* ABB AD/DA���ֲ��ֵ�Դ�ȶ�ʱ��,��λus */
    VOS_UINT32                          ulRfPwrRsmTime;                         /* RF ģ�����Դ�ȶ�ʱ��,��λus */
    VOS_UINT32                          ulAntSwitchPwrRsmTime;                  /* ���߿��ص�Դ�ȶ�ʱ��,��λus */
    VOS_UINT32                          ulAbbWpllRsmTime;                       /* ABB WPLL�ȶ�ʱ��,��λus */
    VOS_UINT32                          ulAbbGpllRsmTime;                       /* ABB GPLL�ȶ�ʱ�� ,��λus*/
    VOS_UINT32                          ulBbpPllRsmTime;                        /* SOC BBP PLL�ȶ�ʱ��,��λus */
    VOS_UINT32                          ulReserved1;                            /* �����ֶ� */
    VOS_UINT32                          ulSysProtectTime;                       /* ϵͳ�ָ�����ʱ�� */
    VOS_UINT32                          ulTcxoRsmTime;                          /* TCXO�ȶ�ʱ��,��λus */
    VOS_UINT32                          ulDcxoRsmTime;                          /* DCXO�ȶ�ʱ��,��λus */
    VOS_UINT32                          ulSlowToMcpuRsmTime;                    /* ��SLOW��MCPU�ϵ�ָ�ʱ��,��λus */
    VOS_UINT32                          ulWphyRsmTime;                          /* W����㻽�ѻָ�ʱ��,��λus */
    VOS_UINT32                          ulGphyRsmTime;                          /* G����㻽�ѻָ�ʱ��,��λus */
    VOS_UINT32                          ulTaskSwitchTime;                       /* ����ϵͳ�����л�ʱ��,��λus */
    VOS_UINT32                          ulPaPwrRsmTime;                         /* PA��Դ�ȶ�ʱ��,��λus */
}WG_DRX_RESUME_TIME_STRU;

typedef struct TLMODE_CHANNEL_tag
{
    VOS_UINT16              abb_channel_id;
    VOS_UINT16              rf_channel_id;
    VOS_UINT16              tcxo_id;
    VOS_UINT16              rf_clk_id;
#ifdef CONFIG_PASwitch_V7R5
    VOS_UINT16              pa_switch_id;
    VOS_UINT16              reserved[3];
#else
    VOS_UINT16              reserved[4];
#endif
}TLMODE_CHANNEL_STRU;

typedef struct
{
    VOS_UINT32 ulSlice;              /* ��¼������Sliceֵ */
    VOS_UINT32 ulState;              /* ������״̬ */
}DRX_RECORD_STRU;

typedef struct
{
    VOS_UINT32      maxNum;
    VOS_UINT32      front;
    VOS_UINT32      rear;
    VOS_UINT32      num;
    DRX_RECORD_STRU data[1];
} drx_queue_t;
typedef enum tagDspState
{
    ENUM_DSP_IS_SLEEP = 0,          /*DSP�Ѿ�ͶƱ˯��*/
    ENUM_DSP_IS_RUN = 1,            /*MSP�Ѿ�����DSP*/
}DspState;
typedef enum tagPowerUpDownDsp
{
    ENUM_YES_UP_DOWN_DSP = 0,          /*0:�������µ�DSP*/
    ENUM_NO_UP_DOWN_DSP = 1,           /*1:���������µ�DSP*/
    ENUM_UP_DOWN_DSP_BUTT,
}PowerUpDownDsp;
typedef enum tagVoteSleep
{
    ENUM_YES_VOTE_SLEEP = 0,          /*0:ͶƱ����˯��*/
    ENUM_NO_VOTE_SLEEP = 1,           /*1:��ͶƱ����˯��*/
    ENUM_VOTE_SLEEP_BUTT,
}VoteSleep;
typedef enum DSP_HALT_MARK
{
    FIRST_HALT_INT = 0,    /*��־û�й�DSP˯���ж�*/
    HAD_HALT_INT = 1,   /*��־�й�DSP ˯���ж�*/
    DSP_HALT_BUTT,
}DSP_HALT_MARK_ENUM;


typedef struct
{
    VOS_UINT32 timeOut;                   /*����DSP�ĳ�ʱʱ������,Ĭ��Ϊ45*/
    VOS_UINT32 timeTaskId;                /*���������id*/
    VOS_UINT32 ulReadMark;                /* ��־�쳣��¼�����ֵ�Ƿ�ȡ����,1:��ʾ������û�ж��� 0:��ʾ���ݱ���ȫ���ߣ���������д��*/
    VOS_SEM    time_sem;                  /*�����ź���,���ڻ���������쳣��Ϣд���ļ�ϵͳ*/
    VOS_UINT32 current_count;                  /*��¼��ǰ��¼�˶��ٴ��쳣��Ϣ*/
    VOS_UINT32 ulTime[100];               /* ��¼�쳣��ʱ����Ϣ */
}DRX_OVERTIME_STRU;

struct msp_power_control
{
    VOS_UINT32                  pwr_status;             /*msp���ֵ�״̬��Ϣ*/
    VOS_SEM                     task_sem;               /*�����ź���*/
    VOS_SEM                     SleepTcxoSem[2];        /* TCXO�ȶ��ź��� 0:��ӦTCXO0,1 ��ӦTCXO1*/
    VOS_UINT32                  RttIsSleepValue;        /*��¼��LSLEEP_RttIsSleep��ѯʱ���ص�ֵ*/
    VOS_INT32                  	LteIntTimer;        	/*LTE timer int*/
    VOS_UINT32                  LteIntTimerFail;        /*LTE timer int fail cnt*/
    VOS_UINT32                  ForbidDspSleepValue;    /*��¼˯��ʱ��ѯ�Ƿ����˯��ʱ���ص�ֵ*/
    DSP_HALT_MARK_ENUM          DspHaltIntMark;             /*��־�Ƿ��й�DSP˯���ж�*/
    VOS_UINT32                  task_id;
    VOS_CHAR *                  dump_base;              /*���ڿ�ά�ɲ�Ļ���ַ*/
    VOS_UINT                    dump_len;               /*���ڿ�ά�ɲ�ĳ���*/
    DspState *                  dsp_state;               /*���ڿ�ά�ɲ�Ļ���ַ*/
    VOS_UINT32                  print_ctrl;             /*dbug ��ӡ����*/
    drx_queue_t*                time_queue_record;        /*����ʱʱ���¼*/
    VOS_UINT32                  dbg_time_record[100];        /*����ʱʱ���¼*/
    DRX_OVERTIME_STRU           exc_overtime;           /*��¼��ʱʱ��ʱ�䣬������mspExcTask�����¼���ļ�ϵͳ*/
    SLEEP_RECORD_STRU*           DrxStateSlice;         /*��¼�����еĸ����׶ε���Ϣ*/
    VOS_UINT32                  DrxStateEnd;            /*DrxStateSlice�Ľ�����ַ*/
    TLMODE_CHANNEL_STRU         tlmode_channel[2];      /*���ڽ���֧��T/Lģ���룬0-LTE;1-TDS*/
    NV_TL_DRX_RESUME_TIME_STRU  SleepDrxResumeTime;     /*NV*/
	LPHY_RTT_LPC_MODE_ENUM      dsp_sleep_flag;         /*DSP��˯ǳ˯��־,1 ǳ˯ 2 ��˯*/
    VOS_UINT32                  SleepRecordFlag;        /*���ؼ�¼sleepTimeRecord*/
    TLSLEEP_RECORD_STRU         SleepTimeRecord;        /*��¼��ά�ɲ���Ϣ�Ľṹ�壬*/
};
struct msp_delay_control
{
    VOS_UINT32            delay_control;                /*ÿһ��bit��������һ���ط��Ƿ�delay*/
    VOS_UINT32            delay_ms;                     /*��Ҫdelay����ms*/
};
#define DELAY_CTRL_BEFOR_WAKE               (1<<0)
#define DELAY_CTRL_AFTER_WAKE               (1<<1)
#define DELAY_CTRL_BEFOR_SLEEP              (1<<2)
#define DELAY_CTRL_AFTER_SLEEP              (1<<3)

struct msp_hids_control
{
    VOS_UINT32            print_control;                /*�����Ƿ��ӡ��hids*/
    VOS_UINT32            PrintVErrorNo;                /*print���صĴ�����*/
};

typedef struct
{
    VOS_UINT32 ulLightSleepFlag;    /*DSP��˯ǳ˯�ı�־*/
    VOS_UINT32 ulTdsPreSfn;         /*DSP����������*/
    VOS_UINT32 ulRfTime;            /*RF�ȶ�ʱ����Ҫ1ms*/
    VOS_UINT32 dspState;            /*DSP��˯�߻����ѣ�0:˯ 1:��*/
    VOS_UINT32 dspTime;            	/*DSP��Ӧ��dspState���ʱ���*/
    VOS_UINT32 ulReserved[3];
}RTT_SLEEP_INFO_STRU;

typedef enum tagSLEEP_TIME_RECORD
{
    /*˯�߹���*/
    TLSLEEP_DSPHALTISR_0 = 0,

    TLSLEEP_RTTSLEEP_INNER_0,
    TLSLEEP_RTTSLEEP_INNER_1,

    TLSLEEP_HWPOWERDOWN_0,
    TLSLEEP_HWPOWERDOWN_1,
    TLSLEEP_HWPOWERDOWN_2 = 5,
    TLSLEEP_HWPOWERDOWN_3,
    TLSLEEP_HWPOWERDOWN_4,
    TLSLEEP_HWPOWERDOWN_5,
    TLSLEEP_HWPOWERDOWN_6,
    TLSLEEP_HWPOWERDOWN_7 = 10,
    TLSLEEP_HWPOWERDOWN_8,
    TLSLEEP_HWPOWERDOWN_9,
    TLSLEEP_HWPOWERDOWN_MAX,

    TLSLEEP_RTTSLEEP_INNER_2,
    TLSLEEP_RTTSLEEP_INNER_MAX = 15,
    
    TLSLEEP_SLEEP_CB_0,
    TLSLEEP_SLEEP_CB_1,

    /*���ѹ���*/
    TLSLEEP_AWAKEISR_0,
    TLSLEEP_AWAKEISR_1,
    TLSLEEP_AWAKEISR_MAX = 20,

    TLSLEEP_FORCE_AWAKE_INNER_0,

    TLSLEEP_AWAKE_CB_0,
    TLSLEEP_AWAKE_CB_1,

    TLSLEEP_OPENTCXO_0,
    TLSLEEP_OPENTCXO_1 = 25,
    TLSLEEP_OPENTCXO_2,
    TLSLEEP_OPENTCXO_3,
    TLSLEEP_OPENTCXO_MAX,

    TLSEEP_HWPOWERUP_0,
    TLSEEP_HWPOWERUP_1 = 30,
    TLSEEP_HWPOWERUP_2,
    TLSEEP_HWPOWERUP_3,
    TLSEEP_HWPOWERUP_4,
    TLSEEP_HWPOWERUP_5,
    TLSEEP_HWPOWERUP_6 = 35,
    TLSEEP_HWPOWERUP_7,
    TLSEEP_HWPOWERUP_8,
    TLSEEP_HWPOWERUP_9,
    TLSEEP_HWPOWERUP_MAX,

    TLSLEEP_FORCE_AWAKE_INNER_1 = 40,
    TLSLEEP_FORCE_AWAKE_INNER_2,
    TLSLEEP_FORCE_AWAKE_INNER_MAX,

    TLSLEEP_DSPRESUMERISR_0,
    TLSLEEP_DSPRESUMERISR_MAX,

    TLSLEEP_TIME_RECORD_MAX,

}EN_SLEEP_TIME_RECORD;

#define  set_power_status_bit(bit)           (g_msp_pwrctrl.pwr_status = g_msp_pwrctrl.pwr_status | bit )
#define  clear_power_status_bit(bit)         (g_msp_pwrctrl.pwr_status = g_msp_pwrctrl.pwr_status & (~bit) )
#define  read_power_status_bit(bit)          (g_msp_pwrctrl.pwr_status & (bit))
#define  msp_set_error_bit(lock_flag, bit )\
do{\
    lock_flag = VOS_SplIMP();\
    set_power_status_bit(bit);\
    VOS_Splx(lock_flag);\
}while(0)
#define  mspsleep_print_error(fmt,...)      (vos_printf("[msp sleep]: <%s> <%d>"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  mspsleep_print_debug(fmt,...)\
do{\
    if(g_msp_pwrctrl.print_ctrl)\
    {\
        vos_printf("[msp sleep]: <%s> <%d>"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__);\
    }\
}while(0);

#ifndef MSP_IN_V9R1
#define  mspsleep_print_info(fmt,...)\
do\
{\
    if(1 == g_msp_hidsctrl.print_control)\
    {\
        g_msp_hidsctrl.PrintVErrorNo = DIAG_LogReport(DIAG_GEN_LOG_MODULE(0, 0, 1), MSP_PID_DRX, (VOS_CHAR*)__FILE__, __LINE__,""fmt"\n", ##__VA_ARGS__);\
    }\
}while(0)
#define TLSLEEP_DFS_BUS_150M           (0)
#define TLSLEEP_DFS_DDR_120M           (120000)
#define TLSLEEP_DFS_DDR_150M           (0)
#define TLSLEEP_DFS_DDR_240M           (240000)
#define TLSLEEP_DFS_CCPU_600M          (0)

#define TLSLEEP_DFS_BUS_75M            (0)
#define TLSLEEP_DFS_DDR_75M            (0)
#define TLSLEEP_DFS_CCPU_150M          (0)

#define TLSLEEP_DfsQosRequest(qos_id, req_value, req_id)            mdrv_pm_dfs_qos_get(qos_id, req_value, req_id)
#define TLSLEEP_DfsQosRelease(qos_id, req_id)                       (0)
#define TLSLEEP_DfsQosUpdate(qos_id, req_id, req_value)             mdrv_pm_dfs_qos_update(qos_id, req_id, req_value)
#else
#define  mspsleep_print_info(fmt,...)
/*��DFSͶƱ V9R1��Ҫ V7R2 ����Ҫ*/

#define TLSLEEP_DFS_BUS_150M            (150000)
#define TLSLEEP_DFS_DDR_150M            (150000)
#define TLSLEEP_DFS_CCPU_600M           (600000)

#define TLSLEEP_DFS_BUS_75M             (75000)
#define TLSLEEP_DFS_DDR_75M             (75000)
#define TLSLEEP_DFS_CCPU_150M           (150000)

#define TLSLEEP_DfsQosRequest(qos_id, req_value, req_id)           mdrv_pm_dfs_qos_get(qos_id, req_value, req_id)
#define TLSLEEP_DfsQosRelease(qos_id, req_id)                      mdrv_pm_dfs_qos_put(qos_id, req_id)
#define TLSLEEP_DfsQosUpdate(qos_id, req_id, req_value)            mdrv_pm_dfs_qos_update(qos_id, req_id, req_value)
#endif
#define TLSLEEP_GetTime(ulIndex)        (g_msp_pwrctrl.SleepTimeRecord.astRecord[ulIndex].ulTime)
#define TLSLEEP_GetType(ulIndex)        (g_msp_pwrctrl.SleepTimeRecord.astRecord[ulIndex].acType)

VOS_VOID TLSLEEP_ActivateHw(PWC_COMM_MODE_E modeId);
VOS_VOID TLSLEEP_TimeRecord(char * cString);
VOS_VOID TLSLEEP_StateRecord(DRX_STATE_SLICE state);
VOS_VOID TLSLEEP_PllEnable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule);
VOS_VOID TLSLEEP_PllDisable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule);
VOS_VOID TLSLEEP_PwrctrlUp(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule);
VOS_VOID TLSLEEP_PwrctrlDown(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule);
VOS_VOID TLSLEEP_TCXO0_IsrProc( VOS_VOID );
VOS_VOID TLSLEEP_TCXO1_IsrProc( VOS_VOID );
VOS_VOID TLSLEEP_MasterAwakeSlave(VOS_VOID);
VOS_VOID TLSLEEP_OpenTCXO(VOS_VOID );
VOS_VOID TLSLEEP_CloseTCXO(VOS_VOID );
VOS_INT32 TLSLEEP_RttForceAwake_Inner(VOS_VOID);
VOS_VOID TLSLEEP_RttSleep_Inner(VOS_VOID);
VOS_VOID TLSLEEP_SleepTask(VOS_UINT32 Para0, VOS_UINT32 Para1,VOS_UINT32 Para2, VOS_UINT32 Para3 );
VOS_VOID TLSLEEP_SetChanel(NV_TLMODE_BASIC_PARA_STRU astChan[2]);
VOS_VOID TLSLEEP_RttForceAwake(VOS_VOID);
VOS_VOID TLSLEEP_DebugRecordTime(VOS_VOID);
VOS_INT32 TLSLEEP_HwPowerUp(PWC_COMM_MODE_E modeId);
VOS_INT32 TLSLEEP_HwPowerDown(PWC_COMM_MODE_E modeId);
VOS_VOID TLSLEEP_DspHaltIsr(VOS_UINT param);
VOS_VOID TLSLEEP_DspResumeIsr(VOS_UINT param);
VOS_BOOL TLSLEEP_RttIsSleep(VOS_VOID);
VOS_INT TLSLEEP_AwakeIsr(VOS_INT enMode);
VOS_VOID TLSLEEP_ResumeDsp(VOS_VOID);
VOS_VOID TLSLEEP_DelayMs(VOS_UINT delay_ms, VOS_UINT flag);
VOS_VOID TLSLEEP_ShowStat(VOS_UINT32 ulIndex);
VOS_UINT32 TLSLEEP_Init(VOS_VOID);
VOS_VOID TLSLEEP_ShowDebugTime(VOS_INT mode);
VOS_UINT32 TLSLEEP_GetPreSfn(VOS_VOID);
VOS_VOID TLSLEEP_RunDsp(VOS_VOID);
VOS_VOID TLSLEEP_ExcTimeTask(VOS_UINT32 Para0, VOS_UINT32 Para1, VOS_UINT32 Para2, VOS_UINT32 Para3);
#if (FEATURE_MULTI_CHANNEL == FEATURE_ON)
VOS_VOID TLSLEEP_EnableRFTCXO(VOS_VOID );
VOS_VOID TLSLEEP_DisableRFTCXO(VOS_VOID );
#endif
VOS_VOID TLSLEEP_PWRCTRL_PWRUP(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enModemId);
VOS_VOID TLSLEEP_PWRCTRL_PWRDOWN(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enModemId);
VOS_VOID TLSLEEP_ShowSleepSwitch(VOS_VOID);

VOS_VOID TLSLEEP_ReportMntn(VOS_VOID);
VOS_VOID TLSLEEP_GetChannelInfo(VOS_VOID);


#ifdef __cplusplus
}
#endif


#endif /* __LTE_SLEEPFLOW_H__ */

