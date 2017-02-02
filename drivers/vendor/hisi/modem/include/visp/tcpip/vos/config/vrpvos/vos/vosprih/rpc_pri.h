/************************************************************************
 *                                                                      *
 *                          rpc_pri.H									*
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/06/14                                      *
 *  Author:             19742                                                *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:                                                           *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *             Copyright 2000 - 2002 HuaWei Tech, Inc.                  *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  ������������������ݣ�                                              *
 *    1�����ͷ�ļ����ĸ�ģ����ĸ�ͷ�ļ���                             *
 *    2�����ͷ�ļ��ж���������Щ���������ݣ���                         *
 *    3��ʲô����C�ļ���Ҫ������ͷ�ļ���                                *
 *    4����ͷ�ļ���Ӧ���ĵ������ơ�                                       *
 *                                                                      *
 ************************************************************************/

/*#if( VRP_MODULE_TEMPLETE == VRP_YES )*/

#ifndef _RPC_PRI_H_
#define _RPC_PRI_H_


#ifdef	__cplusplus
extern "C"{
#endif


#define IPC_RPC_MODULE			0x10000011


#define IPC_RPC_TOTAL_MODULECB_NUMBER		100
#define	IPC_RPC_MAX_PEND_MESSAGE			1000
#if VRP_OPTIM_TASK == VRP_YES
#define IPC_RPC_MS_PER_TICK					200
#else
#define IPC_RPC_MS_PER_TICK					10
#endif

#define IPC_RPC_MAX_RCVQUELEN				1000
#if (VRP_PRODUCT_GSR == VRP_YES)
#define	IPC_RPC_RESENDTIMES					10
#endif

#define IPC_RPC_SUCCESS				0
#define ERR_IPC_RPC_INIT			1
#define ERR_IPC_RPC_NOMEM			2
#define ERR_IPC_RPC_TIMEOUT			3
#define ERR_IPC_RPC_TOMANYMSG		4
#define ERR_IPC_RPC_MDLCB			5

#if (VRP_PRODUCT_GSR == VRP_YES)
/* added by wht, 2001/10/19 */
#define ERR_IPC_SND_FAIL             6
#endif

/****************************************************
*				RPC ��Ϣͷ							*
****************************************************/
typedef struct tagIPC_RPC_MESSAGE_HEAD
{
	USHORT	usMessageType;			/* ��Ϣ����		*/
	USHORT	usPriority;				/* ���ȼ�		*/
	ULONG	ulSrcModuleID;			/* ����ģ��ID	*/
	ULONG	ulDstModuleID;			/* Ŀ��ģ��ID	*/
	ULONG	ulSequence;				/* ���			*/
}IPC_RPC_MESSAGE_HEAD_S;

#define	IPC_RPC_MESSAGE_TYPE_SEND			0x0001
#define	IPC_RPC_MESSAGE_TYPE_REPLY			0x0002
#define	IPC_RPC_MESSAGE_ERR_NULL			0x0003	
#define	IPC_RPC_MESSAGE_ERR_DSTMDL			0x0004	

#define IPC_RPC_GET_MESSAGE_HEAD(p) \
	(IPC_RPC_MESSAGE_HEAD_S*)((UCHAR*)p-sizeof(IPC_RPC_MESSAGE_HEAD_S))
/****************************************************
*				RPC ��Ϣ���ƿ�						*
****************************************************/
typedef struct tagIPC_RPC_MESSAGE_CB
{
#if (VRP_PRODUCT_GSR == VRP_YES)    
	ULONG	ulSrcModuleId;			/* ����RPS����ʱ��Դģ���,
									   ������ӿڰ�ͨ�ŵ�����.
									   added by huangmq */
#endif

	ULONG	ulSequence;				/* ��Ϣ�����				*/
	ULONG	ulSendType;				/* ͬ��ȡ or �첽ȡ			*/
#define	IPC_RPC_SEND_TYPE_SYNC			0
#define	IPC_RPC_SEND_TYPE_ASYNC			1
	ULONG	ulMillSec;				/* ��ʱ���ĳ߶�				*/
	LONG	lRunOut;				/* ���µĳ�ʱʱ��			*/
	IPC_RPC_MESSAGE_HEAD_S	*pMsg;	/* ��Ϣָ��					*/
	ULONG	ulDstNode;				/* Ŀ�Ľڵ�(��) 2k/11/08	*/
	
	IPC_RPC_SENDFINISH_NOTIFY	pfSendFinish;
									/* �첽ȡ���ͽ���֪ͨ����	*/
	ULONG	ulSendLen;				/* ������Ϣ�ĳ���,�첽ȡ	*/
	ULONG	ulSavedData;			/* �û���ʱ���������(����ʱ��),�첽ȡ*/

	ULONG	ulSemphoreID;			/* �ź���					*/

	IPC_RPC_MESSAGE_HEAD_S	*pReceiveMsg; 
									/* ���յ�����Ϣ,ͬ��ȡ		*/
	ULONG	ulReceiveDataLen;		/* ���յ����ݵĳ���,ͬ��ȡ	*/

	struct tagIPC_RPC_MESSAGE_CB	*pstNext;	/* ��һ����Ϣ	*/
	struct tagIPC_RPC_MESSAGE_CB	*pstPrev;	/* ��һ����Ϣ	*/
}IPC_RPC_MESSAGE_CB_S;


/****************************************************
*				RPC ģ��ص����ƿ�						*
****************************************************/
typedef struct tagIPC_RPC_MODULE_CB
{
	ULONG	ulStatus;				/* ʹ��״̬		*/
	ULONG	ulModuleID;				/* ģ��ID		*/
	IPC_RPC_RECEIVE_NOTIFY	pfReceiveNotify;	/* ���ջص����� */
}IPC_RPC_MODULE_CB_S;

#define	IPC_RPC_MODULE_CB_STS_NULL		0x00000000
#define	IPC_RPC_MODULE_CB_STS_USED		0x00000001

/****************************************************
*				RPC ˽�к���(�ڲ�ʹ��)				*
****************************************************/
VOID IPC_RPC_Notify_Func ( ULONG ulFlag, ULONG ulChID, ULONG ulDstNode,
					ULONG ulDstChannelId, VOID *pData, ULONG ulLen);
VOID IPC_RPC_ReceiveReply(IPC_RPC_MESSAGE_HEAD_S *pstRPCMsg, ULONG ulRPCDataLen);
VOID IPC_RPC_Callback(IPC_RPC_MESSAGE_HEAD_S *pstRPCMsg, ULONG ulRPCDataLen,
					  ULONG ulSrcNode);
VOID IPC_RPC_SendCallFinish(IPC_RPC_MESSAGE_HEAD_S *pstRPCMsg, ULONG ulDstNode, ULONG ulIPCLen);
VOID IPC_RPC_SendReplyFinish(IPC_RPC_MESSAGE_HEAD_S *pstRPCMsg, ULONG ulDstNode);
VOID IPC_RPC_ReplyTask(ULONG ulArg1, ULONG ulArg2, ULONG ulArg3, ULONG ulArg4);

ULONG IPC_RPC_InsMsg(IPC_RPC_MESSAGE_CB_S *pMsg);
ULONG IPC_RPC_ExtrMsg(IPC_RPC_MESSAGE_CB_S *pMsg);
VOID IPC_RPC_PassTime(ULONG ulMillSec);
VOID IPC_RPC_TimerTask(ULONG ulArg1,ULONG ulArg2,ULONG ulArg3,ULONG ulArg4);
VOID IPC_RPC_Notify(IPC_RPC_MESSAGE_HEAD_S *pstRPCMsg, ULONG ulRPCDataLen,
					  ULONG ulSrcNode);

VOID IPC_RPC_SyncDealWithIPCSendFail(ULONG ulMsgSequence);/* wuxiaoqian, 2k/11/08*/
VOID IPC_RPC_AsyncDealWithIPCSendFail(ULONG ulMsgSequence);/* wuxiaoqian, 2k/11/08*/

/*
 * Added by Pradeep Shastry for defect BYAD08176 2003-02-19
 * Change the mechanism for main task same as IO i.e create two events one for message and 
 * other one for timer. 200ms timer is created during RUNINDICATION event and each timer expery
 * queue an event and read the event during task entry. Similarly when RPC message is received
 * queue an event and read it in the task entry.
 */

#if (VRP_YES == VRP_VERSION_5)
#define VRP_RPCQ_EVT_TIMER      0x0004
#define VRP_RPCQ_EVT_MESSAGE    0x0008

extern ULONG ulVRPTID_SOCK;
extern ULONG ulSOCKTmrQueID;
extern ULONG gulSockRunReady;

#define VRP_RPC_DELAY_COUNT     100
VOID IPC_RPC_TimerCallback (VOID *pData);
#endif


#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif	/* end of _RPC_PRI_H_ */
