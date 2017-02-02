

#ifndef __BST_CORE_SCHEDULER_H__
#define __BST_CORE_SCHEDULER_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_CORE_PTask.h"
#include "BST_OS_Timer.h"
#include "BST_OS_Thread.h"
#include "BST_OS_Sync.h"
#include "BST_SRV_AsEvnt.h"

#if(BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BST_TASK_SYS_BASE_TIMELEN       (( BST_TASK_SYS_TICKS )* \
                                        BST_OS_MS_IN_S*BST_OS_S_IN_MIN )//2 minuts
#define BST_TASK_SYS_RETRY_TIMELEN      (( 5 )*BST_OS_MS_IN_S )         //5 Second

#define BST_TASK_RELATIVE_RATE          ( 10 )

#define BST_TASK_ABSLT_TIME_MS          ( 60000 )
#define BST_TASK_DELAY_TIME_MS          ( 30000 ) /*poor������������ʱʱ��*/

#define BST_TASK_IsNearEnough(rm,cyc)   ( ((rm) <= \
                                          ((cyc) * BST_TASK_RELATIVE_RATE )/100 )\
                                        &&( (rm)<BST_TASK_ABSLT_TIME_MS ) )

#define BST_TASK_RRC_SEND_TIMER         ( BST_OS_TIMER_PRECISION * 2 )

/* Thread ���ֵĳ��� */
#define BST_BLOCKED_THREAD_LEN          ( 25 )

#define BST_CORE_IS_S2T_CMD(cmd)        ( (cmd)<BST_SRV_T2S_TSK_ATTACH )

#define BST_CORE_INVALID_CYC            ( 0U )

#define BST_CORE_MAX_CYC_ERRNO          ( 2U )

#define BST_CORE_NO_ERR_BIT             ( 0xFFFFU )

#define BST_CORE_IsRuningDetector( ptask )\
     (   BST_SRV_CHbDetector::GetInstance()->IsTask( ptask ) \
     && BST_SRV_CHbDetector::GetInstance()->IsRuning() )

#define BST_CORE_MARK_CYC_BIT(flgs,cyc) \
    if( (cyc) <= BST_SRV_DTC_MAX_LEN )  \
    {                                   \
        (flgs) |= (0x01U<<(cyc));       \
    }

#define BST_CORE_CLR_CYC_BIT(flgs,cyc)  \
    if( (cyc) <= BST_SRV_DTC_MAX_LEN )  \
    {                                   \
        (flgs) &= (~(0x01U<<(cyc)));    \
    }

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/
enum BST_SRV_SCHD_EVEN{
    BST_SRV_S2T_EXE_COMAND,     /*schd֪ͨtask ִ����������*/
    BST_SRV_S2T_ERR_CLOSED,     /*schd֪ͨtask socket���쳣�ر���*/
    BST_SRV_S2T_CYC_UPDATE,     /*schd֪ͨtask ���ڱ�����*/
    BST_SRV_T2S_TSK_ATTACH,     /*task֪ͨschd �����񴴽�������*/
    BST_SRV_T2S_TSK_DETACH,     /*task֪ͨschd ����ȥ����*/
    BST_SRV_T2S_ACK_RESULT,     /*task֪ͨschd ֪�ᵱǰ����ִ�н��*/
    BST_SRV_T2S_RUN_STOPED,     /*task֪ͨschd ����ֹͣ(��̽����)*/
    BST_SRV_T2S_RUN_RESUME,     /*task֪ͨschd ����ָ�(��̽����)*/
    BST_SRV_T2S_DEF_DETCET,     /*task֪ͨschd ����̽��������ID*/
    BST_SRV_SCHD_EVEN_BUTT
};
typedef BST_UINT16  BST_SRV_DET_STATE_ENUM_UINT16;

enum BST_APP_SEND_STATE_ENUM{
    /**BST_APP_SEND_STATE_FIRST
    ��״̬��Task�Լ�����.�������״μ��뵽ͳһ�����������棬��һ�η���Ϊ��״̬��
    ��Ϊδ�����������ڣ���˳ɹ�/ʧ�ܽ������ACK��SCHD��
    */
    BST_APP_SEND_STATE_FIRST,

    /**BST_APP_SEND_STATE_BLOCK
    �����ô�����BLOCK��������������ڳ�����Ԥ��ʱ�䣬��˳ɹ������ͳ�ƣ�ʧ�ܲ�����ͳ�ơ�
    */
    BST_APP_SEND_STATE_BLOCK,

    /**BST_APP_SEND_STATE_NORM
    �����շ������������ڴ������Դ�������Ӧ�óɹ��յ�һ��������Ӧ������״̬
    */
    BST_APP_SEND_STATE_NORM,

    BST_APP_SEND_STATE_BUTT
};
typedef BST_UINT8   BST_APP_SEND_STATE_ENUM_UNIT8;

enum BST_CORE_SCHD_ACK_ENUM{
    BST_CORE_SCHD_ACK_SUC,
    BST_CORE_SCHD_ACK_ERR,
    BST_CORE_SCHD_ACK_BUTT
};
typedef BST_UINT8   BST_CORE_SCHD_ACK_ENUM_UINT8;
/*****************************************************************************
  5 ��/�ṹ����
*****************************************************************************/
typedef struct
{
    NODE                                node;
    BST_CORE_CPTask                    *pcTask;         /* ������� */
    BST_UINT32                          ulLastSendTime; /* �ϴ���������ʱ�䣨MS�� */
    BST_APP_SEND_STATE_ENUM_UNIT8       enSendState;    /* ��ǰ����״̬ */
    BST_CORE_SCHD_ACK_ENUM_UINT8        enLastErrType;  /* �ϴ�����ʧ��ԭ�� */
    BST_UINT16                          usSelfCyc;      /* �������������ڣ�������ϵͳ̽��TICKS��
                                                           ��������CYC�����������ɹ��󣬸�Ϊ���������ڣ���С1*/
}BST_CORE_PTASK_NODE_STRU;

class BST_CTaskSchdler
    : BST_SRV_CAsRcver, BST_OS_CTimerCb
{
BST_PUBLIC:
    BST_VOID            Attach( BST_CORE_CPTask    *pC_PTask );
    BST_VOID            Detach( BST_CORE_CPTask    *pC_PTask );
    BST_VOID            Suspend( BST_VOID );
    static              BST_CTaskSchdler *GetInstance( BST_VOID );
    static              BST_CORE_CPTask  *GetPtaskIns( BST_UINT16 usProcId, BST_UINT16 usTaskId );
    BST_VOID            AckSendResult   ( BST_CORE_CPTask *pcPTask, BST_UINT16 ucResult );
    BST_VOID            TaskStarted     ( BST_CORE_CPTask *pcPTask );
    BST_VOID            TaskStoped      ( BST_CORE_CPTask *pcPTask );
    BST_VOID            DefineDetector  ( BST_CORE_CPTask *pcPTask );
    BST_VOID            onDetFinished   ( BST_UINT8 ucLongestCyc );

BST_PRIVATE:
                        BST_CTaskSchdler( BST_VOID );

    virtual            ~BST_CTaskSchdler( BST_VOID );

    BST_VOID            TimerExpired(
        BST_OS_TIMERID_T    ulId,
        BST_VOID* pvPara );

    BST_VOID            ScheduleTask( BST_CORE_PTASK_NODE_STRU *pTaskItem );

    BST_UINT32          NearRrcTrig(
        BST_UINT32 const        ulSysTimerRemainMs );

    BST_VOID            AsEventCallback(
        BST_AS_EVT_ENUM_UINT32  enEvent,
        BST_UINT32              ulLength,
        BST_VOID               *pvData );

    BST_VOID            LinkStateChgProc(
        BST_AS_NET_RANK_ENUM_UINT32 enNetRank );

    BST_CORE_PTASK_NODE_STRU* GetTaskItem( BST_CORE_CPTask *pcPTask );

    BST_UINT16          GetErrorCycle(
        const BST_UINT16    usErrorMsg );

    BST_UINT16          GetTaskCycle(
        BST_CORE_PTASK_NODE_STRU *pstTaskItem );

    BST_VOID            ProcAckSuc(
        BST_CORE_PTASK_NODE_STRU *pstTaskItem );

    BST_VOID            ProcAckErr(
        BST_CORE_PTASK_NODE_STRU *pstTaskItem );

    BST_VOID            ProcFinish( BST_VOID );
    BST_VOID            ScheduleBlockedTask( BST_VOID );
    BST_AS_NET_RANK_ENUM_UINT32     m_enLinkStaRank;
    BST_OS_TIMERID_T                m_ulTimerId;
    BST_OS_TIMERID_T                m_ulDelayTimerId;
    BST_UINT16                      m_usSysTickMax;         /* ����ϵͳ����������󹫱�����1*2*3*4... */
    BST_UINT16                      m_usSysTickCnt;         /* ԭ m_ulSystemTick����m_ulSysTickMax���� */
    BST_UINT16                      m_usSendingCnt;         /* ��¼�����������ȣ��������˶��ٸ���������*/
    BST_UINT16                      m_usCalledBitRecord;    /* ��¼�����������ȣ����ļ������ڱ����� 0001 0110��ʾ������Ϊ1,2,4��Tick�����񱻵����� */
    BST_UINT32                      m_ulRrcState;
};

/*****************************************************************************
  6 UNION����
*****************************************************************************/


/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  8 ��������
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if(BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif

#endif
