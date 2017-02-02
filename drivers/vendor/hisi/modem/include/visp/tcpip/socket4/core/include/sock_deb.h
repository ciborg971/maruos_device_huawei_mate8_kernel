/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_deb.h
*
*  Project Code: VISP1.5
*   Module Name: socket4   
*  Date Created: 2006-4-29
*        Author: l(48769)
*   Description: socket debug  definition
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-04-27   l(48769)        ���ݱ�̹淶�����ļ����й淶������
*
*******************************************************************************/
#ifndef        _SOCK_DEB_H
#define        _SOCK_DEB_H

#ifdef    __cplusplus
extern    "C"{
#endif


#define SOCK_MAXFILTNUM     5
#define SOCK_FILTOK         0
#define SOCK_FILTINUSE      1
#define SOCK_FILTTOOMUCH    2
#define SOCK_FILTNOTFOUND   3
#define SOCK_FILTNONE       4
#define SOCK_FILTADD        5
#define SOCK_FILTNULLPOINTER 6 /* pointer argument is NULL */
#define SOCK_PARAINVAILED   7
#define SOCK_INCOMPATIBLE   8

#define SOCK_FILT_PERMIT   0  /* ���Ϲ���������������ͨ�� */
#define SOCK_FILT_DENY     1  /* �����Ϲ��������������˲�ͨ�� */

#define SOCKID_ANY (FILENUM + 1)
#define TASKID_ANY 0xFFFFFFFF

#define SOCK_DBUG_OFF 0
#define SOCK_DBUG_ON  1

#define SOCK_LOG_OFF 0
#define SOCK_LOG_ON  1
#define SOCK_LOG_DEFAULT SOCK_LOG_ON

#define ASYNWAKEUP_OK  0  
#define ASYNWAKEUP_ERR 1 /* д�첽��Ϣʧ�� */

/* added by mayun */
typedef struct tagSOCKDBUGFILT
{
    ULONG   ulTaskId;        /* ����û����õĹ��������е�����ID   */
    ULONG   ulSockId;        /* ����û����õĹ��������е��׽ӿں� */
}SOCKDBUGFILT_S;

typedef struct tagSOCKDBUGFILTRD
{        
    SOCKDBUGFILT_S stSockDbugFilt[SOCK_MAXFILTNUM];
    ULONG          ulFiltCnt;       /* ��ǰ���������ĸ��� */
}SOCKDBUGFILTRD_S;

extern VOID SOCK_ApiErrorOutput(SOCKET_S *pSocket, const CHAR *fmt , LONG lError);
extern VOID SOCK_AsynErrorToLog(SOCKET_S *pSocket, LONG iEventType, LONG iError, ULONG ulFlag);
extern VOID SOCK_AsynOutput(SOCKET_S *pSocket, LONG iEventType, LONG iError, ULONG ulFlag);
extern VOID SOCK_DbugInfoOutput(SOCKET_S *pSocket, CHAR *szInfo);
extern CHAR *SOCK_SprintAsynMsg(LONG lAsynMsg, CHAR *pRet, INT32 iRetLen);
extern CHAR *SOCK_SprintSockPair(INPCB_S *pINPCB, CHAR *pRet, INT32 iSockPairLen);

ULONG SOCK_SetEnableStatus(ULONG iFamily, ULONG ulIsenable);
ULONG SOCK_GetEnableStatus(ULONG iFamily, ULONG* pulIsenable);
ULONG SOCK_ClassifyDbugFilt(SOCKDBUGFILTRD_S *pstDbugFiltRd, ULONG ulTaskId, ULONG ulSockId);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif
