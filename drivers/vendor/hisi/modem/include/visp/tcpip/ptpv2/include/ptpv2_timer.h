/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_timer.h
*
*  Project Code:
*   Module Name: PTPV2 timer
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifndef _PTPV2_TIMER_h_
#define _PTPV2_TIMER_h_

#ifdef __cplusplus
extern "C" {
#endif

/*PTPV2����ʱ����ʱ����70ms����ȡֵ��������ֱ��Ӱ��*/
#define PTPV2_BASE_TIMER_LEN      70

#define PTPV2_WANRING_TIMER_INTERVAL   30000   /*30��ѡ����Դ�ϱ��澯*/

/*�߼���ʱ�����������*/
#define PTPV2_LOGIC_TIMER_MAX_NUM    256

/*�߼���ʱ��������ָ��*/
typedef ULONG (*PTPV2_FUNC_LOGIC_TIMER)(VOID* pArg);

/*PTP�߼���ʱ�������ݽṹ*/
typedef struct tagPTPV2_LOGIC_TIMER_S
{
    DLL_NODE_S stDllNode;           /*���ڽ��Ĵ洢*/
    ULONG ulTimerId;                /*�߼���ʱ��ID*/
    ULONG ulPeriod;                 /*��ʱ������*/
    ULONG ulEndTimeHigh;            /*Ann���Ͷ�ʱ���ĳ�ʱʱ���HIGHλ*/
    ULONG ulEndTimeLow;             /*Ann���Ͷ�ʱ���ĳ�ʱʱ���LOWλ*/
    VOID* pArg;                     /*�ص������Ĳ���*/
    PTPV2_FUNC_LOGIC_TIMER pfFunc;  /*�߼���ʱ��������*/
    ULONG ulDelFlag;                /*��ʱ��ɾ����ǣ�PTPV2_TIMER_DELETEΪ��Ҫɾ����PTPV2_TIMER_NOT_DELETEΪ����ɾ��*/
} PTPV2_LOGIC_TIMER_S;

/*******************************************************************************
*    Func Name: PTPV2_CreateLogicTimer
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description: ����PTPV2 �߼���ʱ��
*        Input: ULONG ulPeriod:
*               PTPV2_FUNC_LOGIC_TIMER pfFunc:
*               VOID* pArg:
*               ULONG* pulTimerId:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_CreateLogicTimer(ULONG ulPeriod, PTPV2_FUNC_LOGIC_TIMER pfFunc, VOID* pArg, ULONG* pulTimerId);

ULONG PTPV2_ResetLogicTimer(ULONG ulTimerId);

/*******************************************************************************
*    Func Name: PTPV2_DeleteLogicTimer
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description: ɾ��PTP �߼���ʱ��
*        Input: ULONG ulTimerId:��ʱ��Id
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_DeleteLogicTimer(ULONG ulTimerId);

/*******************************************************************************
*    Func Name: PTPV2_BaseTimerProc
* Date Created: 2014-03-14
*       Author: luogaowei & dutianyi61496
*  Description: PTPV2�Ļ���ʱ��
*        Input: VOID* pArg:
*       Output:
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-14   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
VOID PTPV2_BaseTimerProc(VOID* pArg);

ULONG PTPV2_AnnSndTimerOut(VOID* pArg);

/*******************************************************************************
*    Func Name: PTPV2_AnnRcvTimerOut
* Date Created: 2014-03-15
*       Author: luogaowei & dutianyi61496
*  Description:  announce���ն�ʱ��������
*        Input: VOID* pArg:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-15   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_AnnRcvTimerOut(VOID* pArg);

ULONG PTPV2_CreateWarningTimer();

ULONG PTPV2_DeleteWarningTimer();

VOID PTPV2_TimerPrint(PTPV2_LOGIC_TIMER_S *pstLogicTimer);

#ifdef __cplusplus
}
#endif   /* end of __cplusplus */

#endif   /* end of _PTPV2_TIMER_h_ */

