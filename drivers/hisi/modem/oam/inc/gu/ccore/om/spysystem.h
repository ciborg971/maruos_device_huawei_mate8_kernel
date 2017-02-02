

#ifndef __SPYSYSTEM_H__
#define __SPYSYSTEM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define SPY_INFO_LOG(string)                PS_LOG(WUEPS_PID_SPY, 0, PS_PRINT_INFO,     string)
#define SPY_NORMAL_LOG(string)              PS_LOG(WUEPS_PID_SPY, 0, PS_PRINT_NORMAL,   string)
#define SPY_WARNING_LOG(string)             PS_LOG(WUEPS_PID_SPY, 0, PS_PRINT_WARNING,  string)
#define SPY_ERROR_LOG(string)               PS_LOG(WUEPS_PID_SPY, 0, PS_PRINT_ERROR,    string)

#define SPY_INFO1_LOG(string, para1)        PS_LOG1(WUEPS_PID_SPY, 0, PS_PRINT_INFO,   string, para1)
#define SPY_NORMAL1_LOG(string, para1)      PS_LOG1(WUEPS_PID_SPY, 0, PS_PRINT_NORMAL, string, para1)
#define SPY_WARNING1_LOG(string, para1)     PS_LOG1(WUEPS_PID_SPY, 0, PS_PRINT_WARNING,string, para1)
#define SPY_ERROR1_LOG(string, para1)       PS_LOG1(WUEPS_PID_SPY, 0, PS_PRINT_ERROR,  string, para1)

#define SAR_NORMAL_LOG(string)              PS_LOG(WUEPS_PID_SAR, 0, PS_PRINT_NORMAL,   string)
#define SAR_WARNING_LOG(string)             PS_LOG(WUEPS_PID_SAR, 0, PS_PRINT_WARNING,  string)
#define SAR_ERROR_LOG(string)               PS_LOG(WUEPS_PID_SAR, 0, PS_PRINT_ERROR,    string)


#define SPY_TEMP_THRESHOLD_PARA_CHANGE      1          /* ��Ҫ���¸ò��� */
#define SPY_TEMP_THRESHOLD_PARA_UNCHANGE    0          /* ������¸ò���*/

#define SPY_TEMP_THRESHOLD_PARA_INVALID     0xFFFFFFFF /*��Ч����ֵ��ʹ��λ��ֵ*/

/*�����˼������Ķ�ʱ��ʱ��*/
#define SPY_TIMER_LEN                       1000

/*�������ض�ʱ��ʱ��*/
#define SPY_FLOW_CTRL_TIMER_LEN  \
        (g_stTempProtectNv.stTempCtrlPara.ulWaitTimer * 1000)

/*�������ض�ʱ������*/
#define TIMER_FLOWCTRL                      2
/*�����˸�����ص��ͶƱֵ*/
#define SPY_VOTE_POWEROFF                   (-5)    /*��ǰ��Ҫ�µ�*/
#define SPY_VOTE_SOFTDOWN                   (-4)    /*��ǰ��Ҫ��ػ�*/
#define SPY_VOTE_QOSDOWN                    (-3)
#define SPY_VOTE_TEMPWAIT                   (-1)    /*��ǰ��Ҫ�����¶ȵ��ں�ĵȴ�*/
#define SPY_VOTE_RESUME                     (1)     /*��ǰ��Ҫ����*/
#define SPY_VOTE_NOMAL                      (255)   /*��ǰ����Ҫ����*/


#define SPY_TEMP_MAX_INTERVAL               5

/*������ADC��Ӧ�ĵ�ѹֵ*/
#define SPY_BATTERY_MAX_VOLT                4200
#define SPY_BATTERY_MIN_VOLT                3400


#define GET_TEMP_INTERVAL(oldTemp, newTemp) \
        ((oldTemp > newTemp)? (oldTemp - newTemp):(newTemp - oldTemp))

#define SPY_GET_LOW_RATE(A,B) (((A)<(B))?(A):(B))
#define SPY_GET_MAX_RATE(A,B) (((A)>(B))?(A):(B))

#define TEMP_CLOSE_ITEM                     0x01
#define TEMP_ALARM_ITEM                     0x02
#define TEMP_RESUME_ITEM                    0x04
#define TEMP_POWEROFF_ITEM                  0x08
#define TEMP_ALL_ITEM                       0x0F

#define USIM_TEMP_TABLE_LEN                 19

#define SPY_QOS_CHANGED_FLAG                1
#define SPY_QOS_UNCHANGED_FLAG              0

#define TEMP_CLOSE_ADC_COUNT  \
        g_stTempProtectNv.stTempCtrlPara.ucTempCloseCount

#define TEMP_ALARM_ADC_COUNT  \
        g_stTempProtectNv.stTempCtrlPara.ucTempOverCount

#define TEMP_POWEROFF_ADC_COUNT \
        g_stTempProtectNv.stTempCtrlPara.ucTempPowerOffCount

#define TEMP_RESUME_ADC_COUNT \
        g_stTempProtectNv.stTempCtrlPara.ucTempRsumeCount

#define TEMP_CLOSE_THRESHOLD  \
        g_stTempProtectNv.lCloseAdcThreshold

#define TEMP_ALARM_THRESHOLD  \
        g_stTempProtectNv.lAlarmAdcThreshold

#define TEMP_POWEROFF_THRESHOLD  \
        g_stTempProtectNv.lPowerOffThreshold

#define TEMP_RESUME_THRESHOLD \
        g_stTempProtectNv.lResumeAdcThreshold

#define TEMP_SIM_POWEROFF_THRESHOLD \
        g_stTempProtectNv.lSIMPowerOffThreshold

#define TEMP_CLOSE_TIMER_LEN  \
        (g_stTempProtectNv.stTempCtrlPara.ulWaitTimer)

#define TEMP_ALARM_TIMER_LEN  \
        g_stTempProtectNv.stTempCtrlPara.ulAlarmTimer

#if (RAT_MODE != RAT_GU)
/* SPYͳ�Ƶ�����Ϣ���غ� */
#define SPY_STATISTICS_DEBUG
#endif

#define SPY_SAR_ANTEN_STATUS_IND        0x0001

#define SPY_TEMP_PARA_SIZE              (16)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*������ͶƱ����� */
enum SPY_VOTERESULT_ENUM
{
    SPY_VOTERESULT_NULL          =0,    /*��ǰ����Ҫ����*/
    SPY_VOTERESULT_DEFQOS        =1,    /*��ǰ��Ҫ�ָ�Qos���û�ԭʼֵ*/
    SPY_VOTERESULT_PSON          =2,    /*��ǰ��Ҫ����*/
    SPY_VOTERESULT_DOWNQOS       =3,     /*��ǰ��Ҫ���������µ�*/
    SPY_VOTERESULT_PSOFF,                /*��ǰ��Ҫ��ػ�*/
    SPY_VOTERESULT_POWEROFF,             /*��ǰ��Ҫ�µ�*/
    SPY_VOTERESULT_BUTT
};

typedef VOS_UINT32  SPY_VOTERESULT_ENUM_UINT32;

/*������ϵͳ״̬*/
enum SPY_STATE_ENUM
{
    SPY_STATE_NORMAL            =0, /*��ǰ��������̬*/
    SPY_STATE_QOS               =1, /*��ǰ���ڵ���Qos��״̬*/
    SPY_STATE_PSOFF             =2, /*��ǰ���ڹػ�״̬*/
    SPY_STATE_BUTT
};

typedef VOS_UINT32 SPY_STATE_ENUM_UINT32;

/*�����˵�ǰCPU����״̬*/
enum CHECKCPU_STATE_ENUM
{
    SPY_CHECKCPUSTART           =0,   /*��ʼ��ѯCPUռ���ʣ���Ҫ��¼��ʼֵ*/
    SPY_CHECKCPUALREAD          =1,   /*�Ѿ���ʼ��ѯCPUռ���ʣ���Ҫ������һ�μ�¼��ֵ�ͱ��β�ѯ�Ĳ����CPUռ����*/
    SPY_CHECKCPU_BUTT
};
typedef VOS_UINT32 CHECKCPU_STATE_ENUM_UINT32;

enum SPY_EVENT_NAME_ENUM
{
    SPY_EVENT_TEMP_OVER_HIGH = 1,
    SPY_EVENT_TEMP_RESUME,
    SPY_EVENT_CPU_OVER_HIGH,
    SPY_EVENT_CPU_LOW,
    SPY_EVENT_VOTE_RESULT,
    SPY_EVENT_DFS_CHANGED,             /* ��Ƶ�¼� */
    SPY_EVENT_BUTT
};
typedef VOS_UINT32 SPY_EVENT_NAME_ENUM_UINT32;

enum TEMP_ENABLE_ENUM
{
    TEMP_CLOSE_STATE = 0,
    TEMP_ENABLE_STATE,
    TEMP_ENABLE_BUTT
};
typedef VOS_UINT32 TEMP_ENABLE_ENUM_UINT32;


enum TMEP_STATE_ENUM
{
    TEMP_NORMAL_STATE = 0,
    TEMP_WAIT_STATE,
    TEMP_STATE_BUTT
};
typedef VOS_UINT32 TEMP_STATE_ENUM_UINT32;

/*SIM�¶ȱ仯���ޱ��*/
enum SIM_TEMP_FLAG_ENUM
{
    SIM_TEMP_LOW_FLAG   =0,
    SIM_TEMP_HIGH_FLAG  =1,
    SIM_TEMP_FLAG_BUTT
};

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/

/*������ͨ����Ϣ�ṹ*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;      /* ��Ϣ���� */
    VOS_UINT32                  ulResult;
    VOS_INT32                   lAntenStatus;   /* ����״̬ */
    MODEM_ID_ENUM_UINT16        enModemID;      /* ��ID */
    VOS_UINT16                  usRsv;
}SPY_MSG_STRU;

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/



/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*������ϵͳ��ǰ״̬*/
typedef struct
{
    VOS_UINT32                  ulCurPSStatus;      /*��ǰϵͳ�Ŀ���״̬*/
}SPY_SYSCUR_STATUS;

typedef struct
{
    TEMP_ENABLE_ENUM_UINT32     enTempEnable;           /*��ǰϵͳ�¶ȼ��ʼ�ܿ���*/
    TEMP_STATE_ENUM_UINT32      enTempState;           /*��ǰϵͳ״̬����a)������*/
    VOS_UINT32                  ulTempCloseCount;      /*�ػ��¶ȼ�����*/
    VOS_UINT32                  ulTempAlarmCount;      /*�澯�¶ȼ�����*/
    VOS_UINT32                  ulTempPowerOffCount;   /*�µ��¶ȼ�����*/
    VOS_UINT32                  ulTempResumeCount;     /*�����¶ȼ�����*/
    VOS_UINT32                  ulTempWaitTimeLen;     /*��ϵͳ״̬�仯ʱ����Ҫ�ȴ���ʱ�䳤��*/
    VOS_UINT32                  ulBatteryTempAlarmCount ; /*���ڼ�¼��ǰ�ĵ�س������޴���*/
    VOS_INT                     lOldTemperature;       /*��һ�β�ѯ�����¶�*/
}SPY_TEMP_STATE_CTRL_STRU;

typedef struct
{
    VOS_UINT16                  usMinADC;/*3.4 V��ѹʱ��ADCֵ*/
    VOS_UINT16                  usMaxADC;/* 4.2 V��ѹʱ��ADCֵ*/
}NVIM_Battery_STRU;

typedef struct
{
    VOS_UINT32      ulFlag;
    VOS_INT32       lTempThreshold;
    VOS_UINT32      ulMaxNum;
}NVIM_E5_TEMP_PROTECT_STRU;

#ifdef SPY_STATISTICS_DEBUG
typedef struct
{
    VOS_UINT32                          ulFlowCtrlDownNum;
    VOS_UINT32                          ulFlowCtrlUpNum;
    VOS_UINT32                          ulSoftPowerOffNum;
    VOS_UINT32                          ulSoftPowerOnNum;
    VOS_UINT32                          ulPowerOffNum;
}SPY_STATISTICS_INFO_STRU;

#define SPY_RECORD_NUM 100
typedef struct
{
    VOS_UINT32      ulTime;
    VOS_CHAR        acType[16];
} SPY_TIME_STRU;
typedef struct
{
    VOS_UINT32      ulCount;
    SPY_TIME_STRU   astRecord[SPY_RECORD_NUM];
} SPY_RECORD_STRU;
#endif


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
extern SPY_TEMP_STATE_CTRL_STRU        g_stTempStateCtrl; /*���浱ǰ�¶ȱ���ģ���״̬*/

extern HTIMER                          g_stSpyFlowCtrlTimer;

/*****************************************************************************
  10 ��������
*****************************************************************************/

extern VOS_UINT8 MMA_GetCurrentPhoneMode(VOS_VOID);

extern VOS_UINT32 SHPA_GetRateType(MODEM_ID_ENUM_UINT16 enModemID);

extern VOS_VOID Spy_ReportEvent(SPY_EVENT_NAME_ENUM_UINT32 enEventId, VOS_INT lSimTemp);

extern VOS_UINT32 Spy_SarMsgProc(MsgBlock *pMsg);

extern VOS_UINT32 Spy_SoftPowerOff(VOS_VOID);

extern VOS_UINT32 Spy_SysCtrlCmd(VOS_UINT8 usOpId, VOS_UINT16 usClientId, VOS_UINT32 ulMode, MODEM_ID_ENUM_UINT16 enModemID);

extern VOS_VOID Spy_SendAntenStatusToLte(MODEM_ID_ENUM_UINT16 enModemID, VOS_INT32 lAntenStatus);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif




