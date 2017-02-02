
/******************************************************************************

                  ��Ȩ���� (C), 2011-2031, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : RttHifiAgentInteface.h
  �� �� ��   : ����
  ��    ��   : jiangtao 00348559
  ��������   : 2015.5.24
  ����޸�   :
  ��������   : 
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015.5.23
    ��    ��   : jiangtao 00348559
    �޸�����   : created

******************************************************************************/

#ifndef __RTT_HIFI_AGENT_INTERFACE_H__
#define __RTT_HIFI_AGENT_INTERFACE_H__

#ifndef LPS_RTT
#include "vos.h"
#else
#define VOS_MSG_HEADER
#endif
/*****************************************************************************
  1 header file include
*****************************************************************************/
//#include "mdrv_mailbox.h"
//#include "mdrv.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 macro definition
*****************************************************************************/
#define MBX_MSG_HEADER_LEN_IN_8BIT    (8)//sizeof(UINT32)*2
#define VOICE_DATA_LEN_IN_16BIT_MAX   (40)
/*****************************************************************************
  3 enum definition
*****************************************************************************/
/*****************************************************************************
agent msg type
*****************************************************************************/
enum RTT_HIFI_AGENT_MSGTYPE_ENUM
{
    /*TPHY-->HIFI voice */
    EN_TPHY_TO_HIFI_VOICE_IND = 0, 
    /* HIFI-->TPHY voice*/
    EN_HIFI_AGENT_TO_TPHY_MSG_BASE = 32,
    EN_HIFI_TO_TPHY_VOICE_IND             = 32
};
typedef VOS_UINT32 RTT_HIFI_AGENT_MSGTYPE_ENUM_UINT32;

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/
/*****************************************************************************
 
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulSenderCpuId;
    VOS_UINT32 ulSenderPid;
    VOS_UINT32 ulReceiverCpuId;
    VOS_UINT32 ulReceiverPid;
    VOS_UINT32 ulLength;
}VOS_MSG_HEADER_STRU;

typedef struct
{
    VOS_MSG_HEADER_STRU  stVosMsgHeader ;
    UINT16                             ausVoiceData[VOICE_DATA_LEN_IN_16BIT_MAX];
}TPHY_VOICE_MSG_STRU;

typedef struct
{
    VOS_MSG_HEADER
    RTT_HIFI_AGENT_MSGTYPE_ENUM_UINT32     enMsgType;       
    VOS_UINT32                                                ulMsgLen;      /* valid length of VoiceMsg , in '2byte'*/
    TPHY_VOICE_MSG_STRU                               stVoiceMsg;    
}TPHY_TO_HIFI_VOICE_IND_STRU;

typedef struct
{
    RTT_HIFI_AGENT_MSGTYPE_ENUM_UINT32     enMsgType;       
    VOS_UINT32                                                ulMsgLen;      /* valid length of VoiceMsg , in '2byte'*/
    TPHY_VOICE_MSG_STRU                               stVoiceMsg;    
}HIFI_TO_TPHY_VOICE_IND_STRU;



/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/



/*****************************************************************************
  10 ��������
*****************************************************************************/
//VOS_UINT32 RTTHIFIAGENT_Init();
//VOS_VOID RTTHIFIAGENT_MbxCb(MAILBOX_INT_TYPE_E enIntType);
//VOS_UINT32 RTTHIFIAGENT_IccCb(VOS_UINT32 ulChanID, VOS_INT32 slSize);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif /* __cplusplus */

#endif /* __RTT_HIFI_AGENT_INTERFACE_H__*/

