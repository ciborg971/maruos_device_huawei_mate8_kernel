/************************************************************************
 *                                                                      *
 *                          rpc_inc.H									*
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

#ifndef _RPC_INC_H_
#define _RPC_INC_H_


#ifdef	__cplusplus
extern "C"{
#endif

/****************************************************
*				RPC ���ջص�����						*
****************************************************/
typedef VOID (*IPC_RPC_RECEIVE_NOTIFY)
(
		ULONG ulSrcNode,				/* Դ�ڵ�ID			*/
		ULONG ulSrcModuleID,			/* Դģ��ID			*/
		VOID *pReceiveData,				/* ���յ�����		*/
		ULONG ulReceiveDataLen,			/* �������ݵĳ���	*/
		VOID **ppSendData,				/* ���͵�����		*/
		ULONG *pulSendDataLen			/* �������ݵĳ���	*/
);

/****************************************************
*			RPC ���ͽ���(�ɹ�/��ʱ)�ص�����			*
****************************************************/
typedef VOID (*IPC_RPC_SENDFINISH_NOTIFY)
(
	ULONG ulFlag,
#define IPC_RPC_MESSAGE_ERR_TIMEOUT		0		/* ���ͳ�ʱ				*/
#define	IPC_RPC_MESSAGE_ERR_MDLCB		1		/* ���շ�û��ע��		*/
#define IPC_RPC_MESSAGE_NULL			2		/* ���շ�û��Ӧ����Ϣ��	*/
#define IPC_RPC_MESSAGE_SUCC			3		/* ���յ�Ӧ����Ϣ		*/
	ULONG ulSrcModuleID,		/* Դģ��ID			*/
	ULONG ulDstNode,			/* Ŀ�Ľڵ�ID		*/
	ULONG ulDstModuleID,		/* Ŀ��ģ��ID		*/
	VOID *pSendData,			/* ��������			*/
	ULONG ulSendLen,			/* �������ݳ���		*/
	ULONG ulTimeOut,			/* ��ʱʱ�䣨ms��	*/
	VOID *pReceiveData,			/* ��������ָ��		*/
	ULONG ulReceiveLen,			/* �������ݳ���		*/
	ULONG ulSavedData			/* �û���ʱ���������(����ʱ��)	*/
);

/****************************************************
*				RPC ��ʼ��							*
****************************************************/
ULONG IPC_RPC_Init();


/****************************************************
*				RPC�첽ȡ���ú���					*
****************************************************/
ULONG IPC_RPC_AsyncCall
(
	ULONG ulSrcModuleID,		/* Դģ��ID			*/
	ULONG ulDstNode,			/* Ŀ�Ľڵ�ID		*/
	ULONG ulDstModuleID,		/* Ŀ��ģ��ID		*/
	ULONG ulPriority,			/* �������ȼ�		*/
	VOID *pSendData,			/* ��������			*/
	ULONG ulSendLen,			/* �������ݳ���		*/
	IPC_RPC_SENDFINISH_NOTIFY pfSendFinish,
								/* �첽ȡ���ͽ���֪ͨ����	*/
	ULONG ulTimeOut,			/* ��ʱʱ�䣨ms��	*/
	ULONG ulSavedData			/* �û���ʱ���������(����ʱ��)	*/
);


/****************************************************
*				RPCͬ��ȡ���ú���					*
****************************************************/
ULONG IPC_RPC_SyncCall
(
	ULONG ulSrcModuleID,		/* Դģ��ID			*/
	ULONG ulDstNode,			/* Ŀ�Ľڵ�ID		*/
	ULONG ulDstModuleID,		/* Ŀ��ģ��ID		*/
	ULONG ulPriority,			/* �������ȼ�		*/
	VOID *pSendData,			/* ��������			*/
	ULONG ulSendLen,			/* �������ݳ���		*/
	VOID **ppReceiveData,		/* ��������ָ��		*/
	ULONG *ulReceiveLen,		/* �������ݳ���		*/
	ULONG ulTimeOut				/* ��ʱʱ�䣨ms��	*/
);

/****************************************************
*			RPC ��Ϣ���亯��(����ӿ�)				*
****************************************************/
VOID *IPC_RPC_AllocMsg
(
	ULONG ulSize,				/* �������ĳߴ�		*/
	ULONG ulUserInfo			/* �û���Ϣ			*/
);

/****************************************************
*			RPC ��Ϣ�ͷź���(����ӿ�)				*
****************************************************/
VOID IPC_RPC_FreeMsg
(
	VOID *pData					/* �ͷŵ�����ָ��	*/
);

/****************************************************
*			RPC ģ��ע��(����ӿ�)					*
****************************************************/
ULONG IPC_RPC_Register
(
	ULONG ulModuleID,			/* ���������ģ��ID	*/
	IPC_RPC_RECEIVE_NOTIFY pfReceiveNotify
								/* ���յ���Ϣ����õĺ��� */
);

#if (VRP_VERSION_5 == VRP_YES)
/****************************************************
*           RPC Setting Message Len in the Header   *
****************************************************/
/* 2003-07-30 Pradeep Shastry for HA Framework */
VOID IPC_RPC_SetMsgLen
(
    VOID *pRPCSendMsg,
    ULONG ulMsgLen
);
#endif

#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif	/* end of _RPC_PRI_H_ */
