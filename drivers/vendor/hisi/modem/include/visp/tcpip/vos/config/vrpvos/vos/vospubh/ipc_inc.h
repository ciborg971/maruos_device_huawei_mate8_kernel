/************************************************************************
 *                                                                      *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/03/25                                      *
 *  Author:                                                             *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:                                                           *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *                                                                      *
 ************************************************************************/

/*#if( VRP_MODULE_TEMPLETE == VRP_YES )*/
#ifndef	_IPC_INC_H_
#define	_IPC_INC_H_

#ifndef VOS_INCLUDE_IPC
#define VOS_INCLUDE_IPC     VOS_NO
#endif

#ifdef	__cplusplus
extern "C"{
#endif

/* define a macro for debug and stat of IPC RPC VP */
#define  VOS_IPC_DEBUGANDSTAT           VRP_YES

/* 
 * Added by Pradeep Shastry for IPC Checksum Calculation, HA_IPC_DEBUG macro
 * is used for main and I/O boards and HA_IPC_INCLUDE_CHECKSUM is used only for 
 * main board.
 */

#if (VRP_YES == VRP_VERSION_5)

#if (VRP_YES == VRP_PRODUCT_8070)
#define HA_IPC_DEBUG           VRP_YES
#endif

#if ((VRP_YES == VRP_PRODUCT_WVRP) && (VRP_YES == VRP_DISTRIBUTED))
#define HA_IPC_DEBUG           VRP_YES
#endif

#endif

#if ((VRP_YES == VRP_MODULE_HA_SLAVE2MAIN) && (VRP_YES == HA_IPC_DEBUG))
#define HA_IPC_INCLUDE_CHECKSUM             VRP_YES
#endif


/*
the following two parameter can be configured
*/
/*#define IPC_NODE_TOTAL_NUMBER			(4*5)*/ /*��ҪΪ4�ı������Է����ֽڶ���*/
#if (VRP_PRODUCT_GSR != VRP_YES)
    /*BYDD001520 begin,anhongjie 2003-12-15*/ 
    #if(VRP_CENTERALIZATION == VRP_YES)
        #define IPC_NODE_TOTAL_NUMBER			1	/*����ʽ������ֻ���ڰ���IPC,���ڵ��Ϊ1*/
    #else
        #define IPC_NODE_TOTAL_NUMBER			VRP_MAX_BOARD_NUM	/* mod by wuxiaoqian 2k/10/05*/
    #endif
    /*BYDD001520 end,anhongjie 2003-12-15*/ 
#else
#define IPC_NODE_TOTAL_NUMBER			19	/* mod by wuxiaoqian 2k/10/05*/
#endif

#if(VRP_PRODUCT_GSR == VRP_YES )
#define IPC_CHANNEL_TOTAL_NUMBER		/*(8*10)*/256
#define IPC_GROUP_TOTAL_NUMBER			(8*10)
#else
/* Increased to 85, after NE80 code sync.{B02D21 smk1 problem} 
   by satya 2004-08-17 */
#if (VRP_YES == VRP_VERSION_5)
#define IPC_CHANNEL_TOTAL_NUMBER		((8*10)+5) 
#define IPC_GROUP_TOTAL_NUMBER			((8*10)+5)
#else
#define IPC_CHANNEL_TOTAL_NUMBER		(8*10)
#define IPC_GROUP_TOTAL_NUMBER			(8*10)
#endif
#endif

#if (VRP_PRODUCT_GSR == VRP_YES)
extern ULONG SRM_GetMaxSlot(ULONG ulBoardType);
extern ULONG SRM_GetProductType(VOID);

#define IPC_LPUNODE_FOR_NE80VER24S   SRM_GetMaxSlot(3)
#define IPC_NODE_FOR_NE80VER24S      IPC_LPUNODE_FOR_NE80VER24S + (SRM_GetProductType() == 3 ? 1 : 2)
#endif

#define IPC_FRAGMENT					1

#define IPC_MEMORY_USER_INFO			0x12345678
#if (VRP_YES == VRP_VERSION_5)
/*
 * Added by Pradeep Shastry 2003/25/09 for notification to multiple applications
 */
#define IPC_MAX_REGISTER_ITEM       128

#endif


extern ULONG g_ulSelfNode;
#define IPC_SELF_NODE_ID		g_ulSelfNode
extern ULONG DRV_GetPhySlot(void);

#if (VRP_PRODUCT_GSR == VRP_YES)
/*cxx*/
#define IPC_EV_RECEIVE				0x0100
#define VP_EV_RECEIVE               0x0200
#define MPU_A                       MPUA    
#define MPU_B                       MPUB
#define IPC_LPU_NODE_TOTAL_NUMBER   16
#define IPC_RECV_QUE_LEN            2000
/*end cxx*/

typedef struct tagMacHead  /*add by ctx*/
{
	UCHAR   ucReserve[20];
	UCHAR	ucSrcMacAddr[6];
	UCHAR	ucDstMacAddr[6];
	USHORT	usLength;
	USHORT	usProtocol;
}SMacHead;
#endif

typedef struct tagIPC_MessageCommon
{
#if (VRP_PRODUCT_GSR == VRP_YES)
    SMacHead sMacHead;
#endif
	UCHAR ucMemoryId;/*no change, to transmit this element, the only meaning is to occupy place, when transmit, need not reassign value, intr, drv*/
	UCHAR ucIsSynSend;/*no change, intr*/

	UCHAR ucIsLastFragment;/*no change, frg*/
	
	UCHAR ucMessageType;/*no change, syn request, syn ack, data with ack, pure ack, que*/
	USHORT usSourceNodeId;/*no change,intr*/
	USHORT usSourceChannelId;/*no change,intr*/
	USHORT usDestinationNodeId;/*change, intr, que*/
	USHORT usDestinationChannelId;/*no change, intr*/
	USHORT usAckNumber;/*change, que*/
	USHORT usSendSequenceNumber;/*change, que*/
	ULONG ulDataLength;/*no change, intr*/
#if (VRP_PRODUCT_GSR == VRP_YES)
	UCHAR ucReserved[28];   /*add by ctx*/
#endif
    /*
     * Added by Pradeep Shastry, for IPC Checksum calculation. This part of the code should
     * there for both main and I/O boards.
     */
#if (VRP_YES == HA_IPC_DEBUG)
    ULONG ulIPCCksum;
#endif
}IPC_MESSAGE_COMMON_S;/*20 bytes, 11 elements*/


typedef struct tagIPC_SendMessage
{
	/*for send status*/
	ULONG ulSemphoreId;/*no change, intr*/
	USHORT usDestinationNodeTotalNumber;/*no change, intr*/
	USHORT usResponseNodeNumber;/*modified by notify, intr*/
	UCHAR ucSendStatusToDestinationNode[IPC_NODE_TOTAL_NUMBER];/* 4 * N set by send finish notify, intr*/
	struct tagIPC_SendMessage * pstOriginalSendMessage;/*only used when need fragment and in the last fragment, frg*/
	ULONG ulDestinationNodeId;/*no change, when multicast, group id, intr*/

	/*for transmit*/
	IPC_MESSAGE_COMMON_S stMessageCommon;
	
}IPC_SEND_MESSAGE_S;

typedef struct tagIPC_ReceiveMessage
{
	IPC_MESSAGE_COMMON_S stMessageCommon;
}IPC_RECEIVE_MESSAGE_S;


/*------------------------------------------------------------------------*/
/*                          �� �� �� �� ��                                */
/*------------------------------------------------------------------------*/
/* ��Ϣͷ��С - size of message envolope */
#define IPC_SEND_MESSAGE_HEAD_SIZE			sizeof(IPC_SEND_MESSAGE_S)
#define IPC_RECEIVE_MESSAGE_HEAD_SIZE		sizeof(IPC_RECEIVE_MESSAGE_S)
#define IPC_COMMON_MESSAGE_HEAD_SIZE		sizeof(IPC_MESSAGE_COMMON_S)

/* �����ݻ�ȡ��Ϣͷ */
#define IPC_GET_COMMON_MESSAGE_HEAD(p)	\
		((IPC_MESSAGE_COMMON_S *)((ULONG)(p) - IPC_COMMON_MESSAGE_HEAD_SIZE))
#define IPC_GET_RECEIVE_MESSAGE_HEAD(p)	\
		((IPC_RECEIVE_MESSAGE_S *)((ULONG)(p) - IPC_RECEIVE_MESSAGE_HEAD_SIZE))
#define IPC_GET_SEND_MESSAGE_HEAD(p)	\
		((IPC_SEND_MESSAGE_S *)((ULONG)(p) - IPC_SEND_MESSAGE_HEAD_SIZE))

/* ��Ϣ�ڴ���Դ - source of memory */
#define IPC_MEMORY_SOURCE_VOS_SEND			0x00000001
#define IPC_MEMORY_SOURCE_DRIVER_RECEIVE	0x00000002


/* ֪ͨIPCͨ����ʹ������Ϣ���ͳɹ���ʧ���Լ���Ϣ���� */
typedef VOID (*IPC_NOTIFY_FUNC)
(
    ULONG ulFlag,       /* ��Ϣ��־����ʾ��Ϣ���ͳɹ���ʧ�ܻ���յ���Ϣ   */
    ULONG ulSrcChID,    /* IPCͨ����                                      */
    ULONG ulDstNode,    /* Ŀ�Ľڵ�ţ����鲥����ʱ��ʾ�鲥��ID           */
    ULONG ulDstChID,    /* Ŀ��ͨ����									  */
    VOID *pData,        /* ���ͻ���յ�������                             */
    ULONG ulLen         /* ���ݳ���                                       */
);

/* ���Ѿ�ע��Ĺ���ʵ�屨��ڵ�״̬�ĸı� */
typedef VOID (*IPC_REPORT_FUNC)
(
    ULONG ulNode,       /* �ڵ�ID                                         */
	ULONG ulQueueId,    /* ���к�(���ͻ���ն���)                         */
    ULONG ulStatus      /* �ڵ�״̬                                       */
);

/* IPC�ײ㷢�ͺ��� */
typedef ULONG (*IPC_SEND_FUNC)
(
    VOID *pData,        /* ����ָ��                                       */
    ULONG ulLen,        /* ���ݳ���                                       */
    ULONG ulDstNode,    /* Ŀ�Ľڵ��                                     */
    ULONG ulFlag        /* �������ͣ���ʱ���ã�                           */
);

/* IPC�ײ���պ��� */
typedef ULONG (*IPC_RECV_FUNC)
(
    VOID *pData         /* ����ָ��                                       */
);

/* IPC�ײ��ڴ��ͷź��� */
typedef VOID (*IPC_FREE_FUNC)
(
     VOID *pData        /* ����ָ��                                       */
);

/* IPC������Ϣ�ɹ�/ʧ�ܻ���յ���Ϣʱ��֪ͨ��ʽ */
#define		IPC_NOTI_VIA_NONE	0x00000000
#define     IPC_NOTI_VIA_QUEUE  0x00000001      /* ͨ����Ϣ֪ͨ           */
#define     IPC_NOTI_VIA_FUNC   0x00000002      /* ͨ���ص�����֪ͨ       */

/* ��Ϣ����ģʽ�� */
#define     IPC_MSG_TM_ASYNC    0x00000000      /* �첽����               */
#define     IPC_MSG_TM_SYNC     0x00000004      /* ͬ������               */
#define     IPC_MSG_TM_MULTI    0x00000010      /* �鲥                   */
#define     IPC_MSG_TM_BROAD    0x00000020      /* �㲥                   */
#if (VRP_PRODUCT_GSR == VRP_YES)
#define     IPC_MSG_TM_MULTI2   0x00000080      /* added by wht, 2001/08*/
#endif
#define		IPC_PRI1			0x00010000
#define		IPC_PRI2			0x00020000
#define		IPC_PRI3			0x00030000
#define		IPC_PRI4			0x00040000


/* ��ϢĿ��ڵ㡢ͨ���Լ�Դ�ڵ㡢ͨ���� */
/* ��ϢĿ��ڵ㡢ͨ���Լ�Դ�ڵ㡢ͨ���� */
#define		IPC_GET_SOURCE_NODEID(p)\
	(IPC_GET_COMMON_MESSAGE_HEAD(p)->usSourceNodeId)

#define		IPC_GET_SOURCE_CHANNELID(p)\
	(IPC_GET_COMMON_MESSAGE_HEAD(p)->usSourceChannelId)
	
#define		IPC_GET_DESTINATION_NODEID(p)\
	(IPC_GET_COMMON_MESSAGE_HEAD(p)->usDestinationNodeId)
	
#define		IPC_GET_DESTINATION_CHANNELID(p)\
	(IPC_GET_COMMON_MESSAGE_HEAD(p)->usDestinationChannelId)


/* ��Ϣ״̬������֪ͨIPCͨ����ʹ���� */
#define     IPC_NOTI_FLG_RXDATA			0x00000001      /* �յ���Ϣ               */
#define     IPC_NOTI_FLG_SEND_FINISH	0x00000002      /* �������               */

/* ״̬������, �����ڵ�ķ���״̬ */
#define IPC_SEND_STS_FAL			0x00000002			/* ���ͳɹ�		*/
#define IPC_SEND_STS_SUCC			0x00000001			/* ����ʧ��		*/
#define IPC_SEND_STS_NULL			0x00000000			/* û����˽ڵ㷢�� */


/**************************************************************************/
/*                      �� �� �� �� �� �� ��                              */
/*------------------------------------------------------------------------*/
/*                                                                        */
/*  IPC_Init            ��ʼ��IPC                                         */
/*  IPC_RegReport       ע��IPC���淽ʽ                                   */
/*  IPC_Create          ����IPCͨ��                                       */
/*  IPC_Delete          ɾ��IPCͨ��                                       */
/*  IPC_AllocMsg        ������Ϣ�ڴ�                                      */
/*  IPC_FreeMsg         �ͷ���Ϣ�ڴ�                                      */
/*  IPC_Send            ������Ϣ                                          */
/*	IPC_GetSendStatus	��ȡ����״̬									  */
/*  IPC_CreateGroup     �����鲥��                                        */
/*  IPC_JoinGroup       �����鲥��                                        */
/*  IPC_LeaveGroup      �뿪�鲥��                                        */
/*  IPC_DeleteGroup     ɾ���鲥��                                        */
/*  IPC_AddDriver       ע����������                                      */
/*                                                                        */
/**************************************************************************/
/* ��ʼ��IPC */
ULONG IPC_Init ( );                 /* ���أ�0�ɹ�������Ϊ������          */

/* ע��IPC���淽ʽ */
ULONG IPC_RegReport                 /* ���أ�0�ɹ�������Ϊ������          */
(
    ULONG           ulFlag,         /* ���淽ʽ                           */
    ULONG           ulQueueID,      /* ����ID                             */
    IPC_REPORT_FUNC pfReport        /* �ص�����                           */
);

/* ����IPCͨ�� */
ULONG IPC_Create                    /* ���أ�0�ɹ�������Ϊ������          */
(
    ULONG           ulIpcChID,     /* ����IPCͨ��ID                      */
    ULONG           ulFlag,         /* ֪ͨ��ʽ                           */
    ULONG           ulQueueID,      /* ����ID                             */
    IPC_NOTIFY_FUNC pfNotify        /* �ص�����                           */
);

/* ɾ��IPCͨ�� */
ULONG IPC_Delete                    /* ���أ�0�ɹ�������Ϊ������          */
(
    ULONG   ulIpcChID               /* IPCͨ��ID                          */
);

/* ������Ϣ�ڴ� */
VOID *IPC_AllocMsg                  /* ���أ���ַָ�룬0ʧ��              */
(
    ULONG   ulSize,                 /* �ڴ��С                           */
    ULONG   ulUserInfo              /* �û���Ϣ                           */
);

/* �ͷ���Ϣ�ڴ� */
VOID IPC_FreeMsg                    /* ���أ���                           */
(
    VOID    *pData                  /* ����ָ��                           */
);

/* ������Ϣ */
ULONG IPC_Send                      /* ���أ�0�ɹ�������Ϊ������          */
(
    ULONG   ulIpcChId,              /* IPCͨ��ID                          */
    ULONG   ulDstNode,              /* Ŀ�Ľڵ��                         */
    ULONG   ulDstIpcChId,           /* Ŀ��ʵ���                         */
    ULONG   ulMode,                 /* ����ģʽ                           */
    VOID    *pMsg,                  /* ��Ϣ����ָ��                       */
    ULONG   ulLen,                  /* ��Ϣ���ݳ���                       */
    ULONG   ulUserInfo              /* �û���Ϣ                           */
);

/* ��ȡ����״̬ */
ULONG IPC_GetSendStatus 
( 
	UCHAR ucSendStatus[],			/* ����״̬����                       */
	VOID* pMsg						/* ��Ϣ����ָ��                       */
 );

/* �����鲥�� */
ULONG IPC_CreateGroup               /* ���أ�0�ɹ�������Ϊ������          */
(
    ULONG   *pulGroupID             /* �����鲥��ID                       */
);

/* �����鲥�� */
ULONG IPC_JoinGroup                 /* ���أ�0�ɹ�������Ϊ������          */
(
    ULONG   ulGroupID,              /* �鲥��ID                           */
    ULONG   ulDstNode
);

/* �˳�һ���鲥�� */
ULONG IPC_LeaveGroup                /* ���أ�0�ɹ�������Ϊ������          */
(
    ULONG ulGroupID,                /* �鲥��ID                           */
    ULONG ulDstNode                 /* Ŀ��ʵ�����ڽڵ�                   */
);

/* ɾ���鲥�� */
ULONG IPC_DeleteGroup               /* ���أ�0�ɹ�������Ϊ������          */
(
    ULONG ulGroupID                 /* �鲥��ID                           */
);

/* ����IPC�ײ�ӿ� */
ULONG IPC_AddDriver                 /* ���أ�0�ɹ�������Ϊ������          */
(
    ULONG           ulNode,         /* �ڵ��                             */
    IPC_RECV_FUNC  *ppfRcvFunc,     /* �洢���պ���ָ��                   */
    IPC_SEND_FUNC   pfSdnFunc,      /* ���ͺ���ָ��                       */
    IPC_FREE_FUNC   pfFreeFunc,     /* �ڴ��ͷź���ָ��                   */
    ULONG           ulMaxMTU        /* ������ݳ���                       */
);

/* �õ�IPC���Ͷ��е�ǰ���õĿ��г��� */
ULONG IPC_GetQueFreeLength(ULONG ulDstNode, ULONG ulDstIpcChId, ULONG ulMode);

#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */
#endif	/* end of _TEMPLETE_H_ */

/*#endif*/	/* end of VRP_MODULE_TEMPLETE */

/* end of templete.h */
