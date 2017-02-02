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
 
#include	"vrpcfg.h"

#ifndef _MBUF_TR_H_
#define _MBUF_TR_H_

#ifdef	__cplusplus
extern "C"{
#endif
 
/************************************************************************

	                         private section

  �벻Ҫʹ�ñ����ֵĶ���

*************************************************************************/


#define MBUF_TR_MAX_RECEIVER_NUMBER 50
#define MBUF_TR_MBUF_TAG_LENGTH ( sizeof(MBUF_S) - sizeof(MBUF_DATABLOCKDESCRIPTOR_S) )
#define MBUF_TR_CHANNEL_NAME "MBUF"
#define MBUF_TR_INIT_MESSAGE_BUFFER_LENGTH 100000

/*CPCI_SEND_MTU 1700*/
#define MBUF_TR_LOW_LEVEL_MTU 1700

#define MBUF_TR_TYPE_NOT_NEAT 0
#define MBUF_TR_TYPE_NEAT 1

#define MBUF_TR_VP_CHANNEL_ID 1

#define	MBUF_TR_RESERVE_HEAD_SPACE 100

typedef struct tagMBUF_TR_Message
{
	USHORT usType;/*��NeatSend�����Ļ���Send������*/
	ULONG ulReceiverId;/*�����ߵ�ID*/
	ULONG ulAttachMessage;/*�û�����NeatSend��Send��ulAttachMessage*/
	UCHAR ucMBufTagA[MBUF_TR_MBUF_TAG_LENGTH];/*mbuf��tag������*/
}MBUF_TR_MESSAGE_S;/*message transmit format*/

/* dengyiou 2004-01-31 for performance optimization */
/* ��¼IP_TR��USER TAGѹ����Ϣ��ע��:���ȱ�����4������������������ */
typedef struct tagIP_TR_CompressMessage
{    
	ULONG ulFlag[2];       /* ÿһλ��¼һ��ULONG�Ƿ�ѹ��. 0:δѹ��;1:ѹ�� */	
    ULONG ulLen;           /* ѹ����ĳ��� */
    ULONG ulQueId;         /* ����Ŀ�İ��Ҫ��Ķ���ID.�Ժ����USER TAG����������������������ȥ���� */
}IP_TR_COMPRESSMESSAGE_S;

typedef struct tagIP_TR_Message
{    
	ULONG ulType;       /* ��ӦMBUF_Sͷ��stDataBlockDescriptor��ulType */	
    MBUF_USERTAGDATA_S stUserTagData;    
    ULONG ulMBufType;/*0 IP, 1 MPLS*/
}IP_TR_MESSAGE_S;
typedef struct tagMBUF_TR_DataBlockInfo
{
	/*5 item*/
	ULONG ulType;
	ULONG ulOption;
	ULONG ulOffset;
	ULONG ulDataLength;
	ULONG ulDataBlockLength;
}MBUF_TR_DATA_BLOCK_INFO_S;

typedef struct tagMBUF_TR_ReceiverInfo
{
	/*���ֲ����ظ������ֵ���Ч������4���ַ���
	��4���ַ��������ַ�������������0������
	������0��������0֮����ַ���ȫ���洢Ϊ0��
	���磺�ַ���"T1"��ϵͳ�еĴ洢����"T1\0\0"��
	�ַ���"TEST"��ϵͳ�еĴ洢����"TEST"��
	���洢�ַ�����0������־��*/
	CHAR cReceiverQueueNameA[4];
	/*���ö��н��գ���Ŷ��е�ID��
	���򣬴��0����ʾ����*/
	ULONG ulReceiverQueueId;
	/*���յĻص������������ΪNULL�����ʾ
	�ûص�����֪ͨ�û������򣬱�ʾ�ö���֪ͨ�û�*/
	VOID (* pfReceiverNotifyFunction)(MBUF_S * pstMBuf, ULONG ulAttachMessage);
	/*0 �� 1�� 0 ��ʾ����δʹ�ã�1 ��ʾ������ʹ��*/
	ULONG ulInUse;
}MBUF_TR_RECEIVER_INFO_S;


typedef struct tagMBUF_TR_Info
{
	/*��ʼ��ʱ��VP_AllocMsg������ڴ棬��������mbuf*/
	MBUF_TR_MESSAGE_S * pstMessageBuffer;
	/*pstMessageBuffer�ڴ�ĳ���*/
	ULONG ulMessageBufferLength;
	/*ע��ĸ��������ߵ���Ϣ*/
	MBUF_TR_RECEIVER_INFO_S stReceiverInfoA[MBUF_TR_MAX_RECEIVER_NUMBER];
}MBUF_TR_INFO_S;

/*private function*/
VOID MBUF_TR_Receive(ULONG ulReceiverChannelId, ULONG ulSourceBoardId, ULONG ulSourceVpChannelId,
					  VOID * pReceiveDataBuffer, ULONG ulReceiveDataLength);


/*********************************************************************************
                   
					 
					   public section
	����������û����õĲ���

*********************************************************************************/

#define MBUF_TR_OK 0
#define MBUF_TR_ERROR_ALLOC_MEMORY 1
#define MBUF_TR_ERROR_VP_CREATE 2
#define MBUF_TR_ERROR_NULL_PIONTER 3
#define MBUF_TR_ERROR_DUP_QUEUE_NAME 4
#define MBUF_TR_ERROR_RECEIVER_FULL 5
#define MBUF_TR_ERROR_GET_QUEUE_ID 6
#define MBUF_TR_ERROR_NO_THIS_RECEIVER 7
#define MBUF_TR_ERROR_PARAMETER			8
#define MBUF_TR_DUP_REGISTER			9

#define CPCI_SEND_MTU              1700 /* bytes */
/**************************************************
     define a macro for debug and stat of mbuf_tr
     
**************************************************/
#define MBUF_TR_DBGANDSTAT           VRP_NO

ULONG MBUF_TR_Init();
VOID MBUF_TR_Exit();

ULONG MBUF_TR_RegisterReceiver(ULONG ulReceiverId, CHAR cReceiverQueueNameA[4], 
							   VOID (* pfReceiverNotifyFunction)(MBUF_S * pstMBuf, ULONG ulAttachMessage) );

VOID MBUF_TR_Send(MBUF_S * pstMBuf, ULONG ulReceiverBoardId, 
				  ULONG ulReceiverId, ULONG ulAttachMessage);
VOID MBUF_TR_NeatSend(MBUF_S * pstMBuf, ULONG ulReceiverBoardId, 
				  ULONG ulReceiverId, ULONG ulAttachMessage);

#if( VRP_OPTIM_VP == VRP_YES )
VOID IP_TR_Send( MBUF_S * pstMBuf, ULONG ulReceiverBoardId, ULONG ulReceiverId, ULONG ulPacketQueId );
#endif
#if(VRP_MODULE_IP_MPLS_SOFTFW == VRP_YES)
VOID MPLS_TR_Send( MBUF_S * pstMBuf,ULONG ulReceiverBoardId );
#endif



#ifdef	__cplusplus
}
#endif	/* end of __cplusplus */

#endif /* end of _MBUF_TR_H_*/

