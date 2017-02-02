/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_timer.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP PKT
*  Date Created: 2008-06-02
*        Author: lishenchuan
*   Description: PTP PKTģ�麯��ͷ�ļ�����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-06-02      Lishenchuan       Create
*
*******************************************************************************/

#ifndef _PTP_TIMER_H_
#define _PTP_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif


/*PTP����ʱ����ʱ����65ms,��ʱ�޸ģ�������Ҫ�����ڲ�Ʒ�������ܽ������*/
#define PTP_BASE_TIMER_LEN          70

/*PTP�߼���ʱ�������*/
#define PTP_LOGIC_TIMER_LEN         15000


/*�߼���ʱ��������ָ��*/
typedef ULONG (*PTP_FUNC_LOGIC_TIMER)(VOID *pArg);

/*PTP�߼���ʱ�������ݽṹ*/
typedef struct tagPTP_LOGIC_TIMER_S
{
    UINTPTR ulTimerId;             /*�߼���ʱ��ID*/
    ULONG ulPeriod;                /*��ʱ������*/
    ULONG ulEndTimeHigh;           /*Ann���Ͷ�ʱ���ĳ�ʱʱ���HIGHλ*/
    ULONG ulEndTimeLow;        /*Ann���Ͷ�ʱ���ĳ�ʱʱ���LOWλ*/
    VOID  *pArg;                   /*�ص������Ĳ���*/
    PTP_FUNC_LOGIC_TIMER pfFunc;   /*�߼���ʱ��������*/
    struct tagPTP_LOGIC_TIMER_S *pstNext; /*��ʱ��������ʱ��˳������ʱ���С����*/
    struct tagPTP_LOGIC_TIMER_S *pstPrev;
}PTP_LOGIC_TIMER_S;


/*PTP�߼���ʱ��ͷ�ڵ�����ݽṹ��ͷ�ڵ�ֱ�Ӳ��ã��洢��Ч����*/
typedef struct tagPTP_LOGIC_TIMER_H_S
{
    ULONG ulTimerNumber;
    PTP_LOGIC_TIMER_S stLogicTimer;
}PTP_LOGIC_TIMER_H_S;

ULONG PTP_CreateLogicTimer(ULONG ulPeriod,PTP_FUNC_LOGIC_TIMER pfFunc, VOID* pArg,ULONG* pulTimerId);
ULONG PTP_DeleteLogicTimer(ULONG ulTimerId);
ULONG PTP_ResetLogicTimer(ULONG ulTimerId);
VOID PTP_LogicTimerProc();

ULONG PTP_ProcAnnReqQueryTimerOut(VOID *pArg);
ULONG PTP_ProcAnnCancelQueryTimerOut(VOID *pArg);
ULONG PTP_ProcDelayRespQueryTimerOut(VOID *pArg);
ULONG PTP_ProcSyncReqQueryTimerOut(VOID *pArg);
ULONG PTP_ProcDelayRespCancelQueryTimerOut(VOID *pArg);
ULONG PTP_ProcSyncCancelQueryTimerOut(VOID *pArg);
ULONG PTP_ProcMDelayRespCancelQueryTimerOut(VOID *pArg);
VOID PTP_BaseTimerProc(VOID *pArg);
ULONG PTP_ProcAnnSndTimerOut(VOID *pArg);
ULONG PTP_DelAllTimerRes(VOID);
ULONG PTP_DelUniMasterTabTimerRes(VOID);
ULONG PTP_DelUniMasterNodeTimerRes(PTP_UNI_MASTER_NODE_S *pstUniMaster);
ULONG PTP_DelUniSlaveTabTimerRes(PTP_PORT_S *pstPtpPort);
ULONG PTP_DelUniSlaveNodeTimerRes(PTP_UNI_SLAVE_NODE_S *pstUniSlave);
ULONG PTP_ProcAnnMultiRecvTimerOut(VOID * pArg);
ULONG PTP_ProcAnnRecvTimerOut(VOID *pArg);
ULONG PTP_ProcMSyncCancelQueryTimerOut(VOID *pArg);
ULONG PTP_ProcMAnnCancelQueryTimerOut(VOID *pArg);
ULONG PTP_ProcLiveSndTimerOut(VOID *pArg);
ULONG PTP_ProcLiveRcvTimerOut(VOID *pArg);
ULONG PTP_SlaveSyncDurationTimerOut(VOID *pArg);
ULONG PTP_SlaveDelayDurationTimerOut(VOID *pArg);

/*Added by wangchengyang-xujun62830-57575 for VISPV1R8C01-201, 2009/5/11 */
ULONG PTP_AcceptMasterDetect(VOID *pArg);
/* End of Added by wangchengyang-xujun62830-57575, 2009/5/11 */

ULONG PTP_ProcMulticastAnnSndTimerOut(VOID *pArg);
ULONG PTP_ProcUnicastAnnSndTimerOut(VOID *pArg);

ULONG PTP_UpdateTimerValue(ULONG ulTimerId, ULONG ulValue);

/*Add End*/

ULONG PTP_SlaveAnnDurationTimerOut(VOID *pArg);

extern ULONG PTP_DelUniMasterCancelTimer(PTP_UNI_MASTER_NODE_S *pstUniMaster);

extern ULONG PTP_MasterSyncDurationTimerOut(VOID *pArg);
extern ULONG PTP_MasterDleayDurationTimerOut(VOID *pArg);

VOID PTP_PrintDebug(ULONG ulDebugType, CHAR *pcDebugMsg);

/*******************************************************************************
*    Func Name: PTP_DelUniMasterAnnTimer
* Date Created: 2012-01-12
*       Author: guo00178934
*  Description: ɾ������Master��Annc��ض�ʱ��
*        Input: PTP_UNI_MASTER_NODE_S *pstUniMaster:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-01-12   guo00178934             Create
*
*******************************************************************************/
ULONG PTP_DelUniMasterAnncTimer(PTP_UNI_MASTER_NODE_S *pstUniMaster);

#ifdef __cplusplus
}
#endif

#endif
