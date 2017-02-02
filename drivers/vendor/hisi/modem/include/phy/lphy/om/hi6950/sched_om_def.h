

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/

/************************************************************
                               �궨��
************************************************************/

/************************************************************
                             ���ݽṹ����
************************************************************/

/************************************************************
                             �ӿں�������
 ************************************************************/

#ifndef __SCHED_OM_DEF_H__
#define __SCHED_OM_DEF_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/************************************************************
                           1. REQ����Ͷ�Ӧ�����ݽṹ����
************************************************************/
typedef enum __LPHY_REQ_MSGID_SCHED__
{
    LPHY_REQ_SCHED_RESERVED            = OM_CMD_ID(LPHY_SCHED_MID, OM_TYPE_REQ, 0x0),
    LPHY_REQ_RPT_SCHED_SYM_TIME
}LPHY_REQ_MSGID_SCHED_ENUM;

typedef struct __LPHY_REQ_RPT_SCHED_SYM_TIME_STRU__
{
    OM_REQ_ENABLE_ENUM_UINT16       enEnaRpt;
}LPHY_REQ_RPT_SCHED_SYM_TIME_STRU;

/************************************************************
                           2. CNF���ݽṹ����
************************************************************/
typedef enum __LPHY_CNF_MSGID_SCHED__
{
    LPHY_CNF_SCHED_RESERVED            = OM_CMD_ID(LPHY_SCHED_MID, OM_TYPE_CNF, 0x0),
}LPHY_CNF_MSGID_SCHED_ENUM;


/************************************************************
                           3. Ind���ݽṹ����
************************************************************/
typedef enum __LPHY_IND_MSGID_SCHED__
{
    LPHY_IND_SCHED_RESERVED            = OM_CMD_ID(LPHY_SCHED_MID, OM_TYPE_IND, 0x0),
}LPHY_IND_MSGID_SCHED_ENUM;

/************************************************************
                           4. TRACE���ݽṹ����
************************************************************/
typedef enum __LPHY_TRACE_SCHED__
{
    LPHY_TRACE_SCHED_RESERVED         =  OM_CMD_ID(LPHY_SCHED_MID, OM_TYPE_TRACE, 0x0),
    LPHY_TRACE_SCHED_TASK_LOG_IN,
    LPHY_TRACE_SCHED_TASK_LOG_OUT,
}LPHY_TRACE_SCHED_ENUM;

typedef enum
{
    CDRX_PRESYNC_TASK = 0,
    CDRX_AUTO_GAP_ANR_TASK,
    CDRX_MAC_FORCE_TASK,
    CDRX_PAGING_TASK,
    CDRX_SPS_TASK,
    CDRX_ANR_DEMOD_TASK,
    CDRX_SYSINFO_TASK,
    CDRX_INTRA_MEAS_TASK,
    CDRX_NONINTRA_MEAS_TASK,
    CDRX_SCELL_MEAS_TASK,
    CDRX_SRCH_TASK,
    CDRX_SCHED_TASK_BUTT,
    CDRX_INVALID_TASK = 0xffff,
}SCHED_CDRX_TASK_ENUM;
typedef UINT16 SCHED_CDRX_TASK_ENUM_UINT16;

typedef enum
{
    IDRX_NEIGHBORCELL_SYSINFO            = 0,
    IDRX_PRESYNC_TASK,
    IDRX_PAGING_TASK,
    IDRX_MAINCELL_SYSINFO,
    IDRX_INTRA_MEAS_TASK,    /*ͬƵ����*/
    IDRX_NONINTRA_MEAS_TASK,/*��ϵͳ����Ƶ����*/
    IDRX_BGS_TASK,
    IDRX_SCHED_TASK_BUTT,
    IDRX_INVALID_TASK = 0xffff,
}SCHED_IDRX_TASK_ENUM;
typedef UINT16 SCHED_IDRX_TASK_ENUM_UINT16;

typedef enum
{
    PRESYNC_TASK,
    PAGING_TASK,
    MAC_FORCE_TASK,/*����������뷢��ǿ�ƻ��ѣ��Լ�SR�����*/
    AUTO_GAP_ANR_TASK,
    SPS_TASK,
    CDRX_ANR_TASK,
    SRCH_TASK,

    MAINCELL_SYSINFO,
    NEIGHBORCELL_SYSINFO,
    PCELL_INTRA_MEAS_TASK,
    PCELL_NONINTRA_MEAS_TASK,
    SCELL_MEAS_TASK,
    IDLE_BGS_TASK,
    SCHED_TASK_BUTT,
}SCHED_TASK_ENUM;
typedef UINT16 SCHED_TASK_ENUM_UINT16;

typedef enum
{
    TASK_LOG_OUT = 0,       /*������Ч���߱���hold*/
    TASK_HOLD,              /*����hold*/
    TASK_LOG_IN,            /*������������*/
}SCHED_TASK_STATUS_ENUM;
typedef UINT16 SCHED_TASK_STATUS_ENUM_UINT16;
#if 0
typedef enum
{
    TASK_PRIORITY_LEVEL_1 = 1,
    TASK_PRIORITY_LEVEL_2,
    TASK_PRIORITY_LEVEL_3,
    TASK_PRIORITY_LEVEL_4,
    TASK_PRIORITY_LEVEL_5,
    TASK_PRIORITY_LEVEL_6,
    TASK_PRIORITY_LEVEL_7,
    TASK_PRIORITY_LEVEL_8,
    TASK_PRIORITY_LEVEL_BUTT,
}SCHED_TASK_PRIORITY_ENUM;
typedef UINT16 SCHED_TASK_PRIORITY_ENUM_UINT16;
#endif

typedef enum
{
    TASK_BUILD_SUCC = 0,
    TASK_BUILD_FAILED,
}SCHED_TASK_BUILD_QUERY_ENUM;
typedef UINT16 SCHED_TASK_BUILD_QUERY_ENUM_UINT16;

typedef struct
{
    //SCHED_TASK_ENUM_UINT16          enTaskType;         /*����*/
    SCHED_TASK_STATUS_ENUM_UINT16   enTaskStatus;       /*״̬*/
    //SCHED_TASK_PRIORITY_ENUM_UINT16 enTaskPriority;     /*���ȼ�*/
    UINT16                          usReserved;
    UINT32                          ulOtherTaskBitmap;  /*�Ƿ��ͻ*/
}SCHED_TASK_INFO_STRU;

typedef struct __LPHY_TRACE_SCHED_TASK_LOG_IN_STRU__
{
    UINT16                             usSysFrameNum;
    UINT16                             usSubFrameNum;
    SCHED_TASK_BUILD_QUERY_ENUM_UINT16 enTaskBuildQuery;
    SCHED_TASK_ENUM_UINT16             enApplyedTaskType;
    SCHED_TASK_ENUM_UINT16             enHighestTaskType;
    UINT16                             usReserved;
    SCHED_TASK_INFO_STRU               astSchedTaskInfo[SCHED_TASK_BUTT];
}LPHY_TRACE_SCHED_TASK_LOG_IN_STRU;

typedef struct __LPHY_TRACE_SCHED_TASK_LOG_OUT_STRU__
{
    UINT16                             usSysFrameNum;
    UINT16                             usSubFrameNum;
    SCHED_TASK_ENUM_UINT16             enApplyedTaskType;
    SCHED_TASK_ENUM_UINT16             enHighestRunTaskType;
    SCHED_TASK_ENUM_UINT16             enHighestHoldTaskType;
    UINT16                             usReserved;
    SCHED_TASK_INFO_STRU               astSchedTaskInfo[SCHED_TASK_BUTT];
}LPHY_TRACE_SCHED_TASK_LOG_OUT_STRU;


/************************************************************
                           5. SG ���ݽṹ����, �㷨��Ҫ��ͼ��
************************************************************/

#define MAX_SYMBOL_INT_USED		3
#define MAX_SYMBOL_FUNC_NUM		32


typedef enum __LPHY_SG_MSGID_SCHED__
{
    LPHY_SG_SCHED_RESERVED            = OM_CMD_ID(LPHY_SCHED_MID, OM_TYPE_SG, 0x0),
    LPHY_SG_SCHED_SYM_TIME,
    LPHY_SG_SCHED_CORE_COUNTER,
    LPHY_SG_SCHED_FUNC_CORE_COUNTER,
}LPHY_SG_MSGID_SCHED_ENUM;

typedef struct __LPHY_SG_SCHED_SYM_TIME_STRU__
{
    UINT32    ulSymStartTime[MAX_SYMBOL_INT_USED];      /*��ʾÿ�����ŵ���ʼʱ��ͽ���ʱ�䣬��λΪ0.25Ts*/
    UINT32    ulSymEndTime[MAX_SYMBOL_INT_USED];        /*��ʾÿ�����ŵ���ʼʱ��ͽ���ʱ�䣬��λΪ0.25Ts*/
}LPHY_SG_SCHED_SYM_TIME_STRU;

typedef struct __LPHY_SG_SCHED_CORE_COUNTER_STRU__
{
    UINT32   ulDuration[MAX_SYMBOL_INT_USED];
}LPHY_SG_SCHED_CORE_COUNTER_STRU;

#if 0
typedef struct __LPHY_SG_SCHED_FUNC_CORE_COUNTER_1_STRU__
{
    UINT32  ulFuncCounter0[12];
    UINT32  ulFuncCounter1[12];
    UINT32  ulFuncCounter2[12];
    UINT32  ulFuncCounter3[12];
    UINT32  ulFuncCounter4[12];
    UINT32  ulFuncCounter5[12];
    UINT32  ulFuncCounter6[12];
    UINT32  ulFuncCounter7[12];
    UINT32  ulFuncCounter8[12];
    UINT32  ulFuncCounter9[12];
    UINT32  ulFuncCounter10[12];
    UINT32  ulFuncCounter11[12];
    UINT32  ulFuncCounter12[12];
    UINT32  ulFuncCounter13[12];
}LPHY_SG_SCHED_FUNC_CORE_COUNTER_1_STRU;
#endif

typedef struct __LPHY_SG_SCHED_FUNC_CORE_COUNTER_STRU__
{
    UINT32  ulFuncCounter[MAX_SYMBOL_INT_USED][MAX_SYMBOL_FUNC_NUM];
}LPHY_SG_SCHED_FUNC_CORE_COUNTER_STRU;


/************************************************************
                           6. ERROR ���ݽṹ����
************************************************************/
typedef enum __LPHY_ERROR_SCHED__
{
    LPHY_ERROR_SCHED_RESERVED         =  OM_CMD_ID(LPHY_SCHED_MID, OM_TYPE_ERROR, 0x0),
}LPHY_ERROR_SCHED_ENUM;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __SCHED_OM_DEF_H__ */
