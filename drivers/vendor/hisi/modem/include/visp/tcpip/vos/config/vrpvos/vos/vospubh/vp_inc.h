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
#ifndef _VP_INC_H_
#define _VP_INC_H_
#ifdef	__cplusplus
extern "C"{
#endif

#define		VP_SUCCESS						0x00000000

#define		ERR_VP_BASE						0x10000000
#define		ERR_VP_CH_STS					ERR_VP_BASE+1
#define		ERR_VP_DRV_MTU					ERR_VP_BASE+2
#define		ERR_VP_DRV_STS					ERR_VP_BASE+3
#define		VP_ERROR_MESSAGE_TOO_LONG		ERR_VP_BASE+4
#define		VP_ERROR_NO_MEMORY				ERR_VP_BASE+5
#define		VP_ERROR_DRV_SEND_FAIL			ERR_VP_BASE+6
#define		VP_ERROR_PARA					ERR_VP_BASE+7

#if (VRP_PRODUCT_GSR == VRP_YES)
#define VP_EV_RECEIVE               0x0200
#endif

/* VPͨ�����սӿ� */
typedef VOID (*VP_NOTIFY_FUNC)
(
	ULONG ulChID,		/* VPͨ����			*/
	ULONG ulSrcNodeID,	/* Դ�ڵ�ID			*/
	ULONG ulSrcVpChID,	/* ԴVPͨ����		*/
	VOID  *pData,		/* ���յ�������		*/
	ULONG ulLen			/* ���ݳ���			*/
 );


/* VP�Ͳ���պ��� */
typedef ULONG (*VP_RECV_FUNC)
(
	VOID *pData		/* ����ָ��				*/
);

/* VP�Ͳ㷢�ͺ��� */
typedef ULONG (*VP_SEND_FUNC)
(
	VOID *pData,		/* ����ָ��				*/
	ULONG ulLen,		/* ���ݳ���				*/
	ULONG ulDstNode,	/* Ŀ�Ľڵ�				*/
	ULONG ulFlag		/* ��������(��ʱ����)	*/
);

/* VP�Ͳ��ڴ��ͷź��� */
typedef VOID (*VP_FREE_FUNC)
(
	VOID *pData			/* ����ָ��			*/
);

ULONG VP_Init();
ULONG VP_Create(ULONG ulVpChID, VP_NOTIFY_FUNC pfReceive);
ULONG VP_Delete(ULONG ulVpChID);
VOID * VP_AllocMsg(ULONG ulSize, ULONG ulUserInfo);
VOID VP_FreeMsg(VOID *pData);

ULONG VP_AddDriver( VP_RECV_FUNC * ppfRevFunc,
				   VP_SEND_FUNC pfSdnFunc,
				   VP_FREE_FUNC pfFreeFunc,
				   ULONG		ulMaxMTU
				   );

ULONG VP_Send(ULONG ulLocalVpChannelId, ULONG ulDestNodeId, ULONG ulDstVpChannelId,
                VOID *pData, ULONG ulLength);

#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */
#endif

/*#endif*/	/* end of VRP_MODULE_TEMPLETE */

/* end of templete.h */
