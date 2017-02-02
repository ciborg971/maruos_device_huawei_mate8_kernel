#ifndef  __TDS_DRX_OM_DEF_H_______
#define  __TDS_DRX_OM_DEF_H_______

#include "type_define.h"
#include "om_base_def.h"

typedef enum TDS_DRX_OM_REQ_MSGID
{
    TPHY_REQ_DRX_CLKMEASSTAT = OM_TCMD_ID(TPHY_DRX_MID, OM_TYPE_REQ, 0x0),
    TPHY_REQ_DRX_IDLESLEEPPARA = OM_TCMD_ID(TPHY_DRX_MID, OM_TYPE_REQ, 0x1),
    TPHY_REQ_DRX_IDLEDETAILINFO = OM_TCMD_ID(TPHY_DRX_MID, OM_TYPE_REQ, 0x2),
}TDS_DRX_OM_REQ_MSGID_ENUM;

typedef enum TDS_DRX_OM_RPT_IND
{
    TPHY_DRX_REPORT_CLKMEASSTAT_IND =  OM_TCMD_ID(TPHY_DRX_MID, OM_TYPE_TRACE, 0x0),

    TPHY_DRX_REPORT_IDLESLEEPPARA_IND =  OM_TCMD_ID(TPHY_DRX_MID, OM_TYPE_TRACE, 0x1),

    TPHY_DRX_REPORT_IDLEDETAILINFO_IND =  OM_TCMD_ID(TPHY_DRX_MID, OM_TYPE_TRACE, 0x2),

}TDS_DRX_OM_RPT_ENUM;


typedef struct
{
    UINT32 ulClkMeasStatEnable;
}TPHY_DRX_REQ_CLKMEASSTAT_STRU;


typedef struct
{
    UINT32 ulIdleSleepParaEnable;

}TPHY_DRX_REQ_IDLESLEEPPARA_STRU;

typedef struct
{
    UINT32 ulIdleDetailInfoEnable;

}TPHY_DRX_REQ_IDLEDETAILINFO_STRU;

/*****************************************************************************
 �ṹ��    :TDS_DRX_OM_SLEEP_TIME_STRU
 Э����  :
 �ṹ˵��  :TDS DRX˯��ʱ��������Ϣ
*****************************************************************************/
typedef struct
{
    UINT32 ulToatalSleepChipTime;
    UINT32 ulToatalSleep32kTime;
    UINT32 ulWakeup32kTime;
    UINT32 ulSwitch32kTime;
    UINT32 ulSleepReadyChipTime;
    UINT32 ulPreWakeSfnNum;
}TDS_DRX_SLEEP_TIME_STRU;

typedef struct
{
    UINT16 usSfn;
    UINT16 usChipNum;
    TDS_DRX_SLEEP_TIME_STRU stTdsDrxSleepPara;
}TDS_DRX_OM_SLEEP_TIME_STRU;

typedef enum
{
    TDS_OM_PICH_TASK = 0,
    TDS_OM_PCH_TASK,
    TDS_OM_ENERGY_MEAS_TASK,
    TDS_OM_CELL_SEARCH_TASK,
    TDS_OM_CLK_MEAS_TASK,
    TDS_OM_PRESYNC_TASK,
    TDS_OM_SYSINFO_TASK,
    TDS_OM_DRX_MAX_TASK,
} TDS_DRX_OM_TASK_ENUM;
typedef UINT16 TDS_DRX_OM_TASK_ENUM_UINT16;

typedef enum
{
    TDS_OM_TASK_START,
    TDS_OM_TASK_END,
    TDS_OM_TASK_TYPE_NUM,
}TDS_DRX_OM_TASK_OP_TYPE;
typedef UINT16 TDS_DRX_OM_TASK_OP_TYPE_UINT16;

typedef enum
{
    DRX_OM_WAKE_UP_STATE,
    DRX_OM_DSP_OK_STATE,
    DRX_OM_NORMAL_WORKING_STATE,
    DRX_OM_PRE_SLEEP_READY_STATE,
    DRX_OM_SLEEP_ENABLE_STATE,
    DRX_OM_STATE_NUM,
}TDS_DRX_OM_STATE_ENUM;
typedef UINT16 TDS_DRX_OM_STATE_ENUM_UINT16;

typedef struct
{
    UINT16 usSfn;
    UINT16 usChipNum;
}TDS_DRX_OM_TIME_STRU;
/*****************************************************************************
 �ṹ��    :TDS_DRX_TASK_INFO_STRU
 Э����  :
 �ṹ˵��  :TDS IDLE̬������Ϣ
*****************************************************************************/
typedef struct
{
    TDS_DRX_OM_TASK_ENUM_UINT16 usTaskId;
    UINT16 usTaskEnterNum;          /*Task ִ�д���*/
    TDS_DRX_OM_TIME_STRU stOpTypeTime[TDS_OM_TASK_TYPE_NUM];    /*��¼���µ�����ʼ����ʱ��*/
}TDS_DRX_TASK_INFO_STRU;

/*****************************************************************************
 �ṹ��    :TDS_DRX_IDLE_STATE_INFO_STRU
 Э����  :
 �ṹ˵��  :TDS IDLE DRX״̬��Ϣ
*****************************************************************************/
typedef struct
{
    TDS_DRX_OM_STATE_ENUM_UINT16 usDrxOmState;
    UINT16 usStateNum;      /*�ϱ�������State�������*/
    TDS_DRX_OM_TIME_STRU stStateTime;     /*��¼���µ�state��ʼʱ��*/
}TDS_DRX_IDLE_STATE_INFO_STRU;

/*****************************************************************************
 �ṹ��    :TDS_DRX_PRESYNC_INFO_STRU
 Э����  :
 �ṹ˵��  :TDS ��ʱԤͬ����Ϣ
*****************************************************************************/
typedef struct
{
    UINT16 usPresyncNum;    /*�ϱ�������presync����*/
    UINT16 usRsvd;
    TDS_DRX_OM_TIME_STRU stPresyncStartTime;    /*��¼���µ�presync��ʼʱ��*/
}TDS_DRX_PRESYNC_INFO_STRU;

/*****************************************************************************
 �ṹ��    :TDS_DRX_OM_CLK_MEAS_INFO_STRU
 Э����  :
 �ṹ˵��  :TDS ʱ�Ӳ�����Ϣ
*****************************************************************************/
typedef struct
{
    UINT16 usClkMeasNum;    /*�ϱ�������clkmeas����*/
    UINT16 usRsvd;
    TDS_DRX_OM_TIME_STRU stClkMeasStartTime;    /*��¼���µ�clkmeas��ʼʱ��*/
}TDS_DRX_OM_CLK_MEAS_INFO_STRU;
/*****************************************************************************
 �ṹ��    :TDS_DRX_OM_DETAIL_INFO_STRU
 Э����  :
 �ṹ˵��  :TDS IDLE̬��ϸ������Ϣ
*****************************************************************************/
typedef struct
{
    TDS_DRX_OM_TIME_STRU stRptTime;
    TDS_DRX_TASK_INFO_STRU stTdsDrxTaskInfo[TDS_OM_DRX_MAX_TASK];
    TDS_DRX_IDLE_STATE_INFO_STRU stTdsDrxStateInfo[DRX_OM_STATE_NUM];
    TDS_DRX_PRESYNC_INFO_STRU stPresyncInfo;
    TDS_DRX_OM_CLK_MEAS_INFO_STRU stClkMeasInfo;
}TDS_DRX_OM_DETAIL_INFO_STRU;


/*****************************************************************************
 �ṹ��    :TDS_DRX_OM_CLK_MEAS_STRU
 Э����  :
 �ṹ˵��  :TDS DRX OMʱ�Ӳ��������ṹ
*****************************************************************************/
typedef struct
{
    UINT32 ulClkMeasCounter;
    UINT16 usClkMeasInt;
    UINT16 usClkMeasFrac;
    UINT16 usClkMeasValid;
    UINT16 usClkMeasState;
    UINT16 usClkMeasParaIndex;
    UINT16 usLastClkMeasSfn;
} TDS_DRX_OM_CLK_MEAS_STRU;

#endif /* __TDS_DRX_OM_DEF_H_______ */



