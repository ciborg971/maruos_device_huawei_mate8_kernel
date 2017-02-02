/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXsmsSndAt.h
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��10��31��
  ��������   : TafXsmsSndAt.cͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

#ifndef _TAF_XSMS_SND_AT_H_
#define _TAF_XSMS_SND_AT_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafAppXsmsInterface.h"
#include "TafXsmsDecode.h"
#include "TafXsmsStkInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 TAF_XSMS_MsgInitInd(VOS_UINT32 ulTotalNum);

extern VOS_UINT32 TAF_XSMS_MsgSubmitCnf(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulRslt
);
extern VOS_UINT32 TAF_XSMS_MsgWriteCnf(VOS_UINT16 usClientId,  VOS_UINT8 ucOpId, VOS_UINT32 ulRslt, VOS_UINT32 ulIndex);

extern VOS_UINT32 TAF_XSMS_MsgDeleteCnf(VOS_UINT16 usClientId, VOS_UINT8 ucOpId, VOS_UINT32 ulRslt);

extern VOS_UINT32 TAF_XSMS_MsgSubmitSuccInd(VOS_UINT32 ulMr);

extern VOS_UINT32 TAF_XSMS_MsgDeliveryInd(TAF_XSMS_MESSAGE_STRU *pstDeliveryMsg);

extern VOS_UINT32 TAF_XSMS_MsgUimFullInd(VOS_VOID);

extern VOS_UINT32 TAF_XSMS_SmsEventCallBack(
    TAF_XSMS_APP_MSG_TYPE_ENUM_UINT32  enEventType,
    TAF_XSMS_APP_AT_EVENT_INFO_STRU   *pstEvent);
extern VOS_UINT32 TAF_XSMS_MsgSubmitFailInd(VOS_UINT32 ulCourceCode);
extern VOS_UINT32 TAF_XSMS_SetAPFullCnf(VOS_UINT16 usClientId, VOS_UINT8 ucOpId, VOS_UINT32 ulRslt);
extern VOS_UINT32 TAF_XSMS_SendStkRsltInd(
            VOS_UINT32                          ulSendRslt,
            VOS_UINT32                          ulCauseCode
);

extern VOS_VOID TAF_XSMS_StkMsgSubmitCnf(VOS_UINT32 ulRet);
extern VOS_VOID TAF_XSMS_SendStkCATPTMsg(VOS_UINT32 ulLen,
                                                    VOS_UINT8 *pucTpdu,
                                                    TAF_XSMS_MESSAGE_STRU *pst1XSms);

extern VOS_VOID TAF_XSMS_SendXpdsGpsSms(
    TAF_XSMS_ADDR_STRU                 *pstXsmsAddr,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucData
);

#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
