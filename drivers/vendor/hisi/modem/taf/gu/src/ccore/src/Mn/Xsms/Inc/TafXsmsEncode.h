/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXsmsEncode.h
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��10��31��s
  ��������   : TafXsmsEncode.cͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

#ifndef _TAF_XSMS_ENCODE_H_
#define _TAF_XSMS_ENCODE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafXsmsDecode.h"
#include  "TafAppXsmsInterface.h"
#include  "TafXsmsInterMsg.h"


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
extern VOS_VOID TAF_XSMS_ReplaceMessageID(
    TAF_XSMS_MESSAGE_STRU              *pucBDStru,
    VOS_UINT16                          usMessageId
);

extern VOS_VOID TAF_XSMS_FillTeleserviceID(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
);

extern VOS_VOID TAF_XSMS_FillServiceCategory(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
);

extern VOS_VOID TAF_XSMS_FillAddress(
    TAF_XSMS_ADDR_STRU                 *pstAddr,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucLen
);

extern VOS_VOID TAF_XSMS_FillSubAddress(
    TAF_XSMS_SUB_ADDR_STRU             *pstSubAddr,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos,
    VOS_UINT8                           enStates
);

extern VOS_VOID TAF_XSMS_FillBearerReplyOpiton(
    VOS_UINT8                           ucBearReplySeqNum,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
);

extern VOS_VOID TAF_XSMS_FillBearerData(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
);

extern VOS_UINT32 TAF_XSMS_GetP2PDBMStru(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT16                          usMessageIdentifier,
    VOS_UINT8                           ucBearerReplyOptionSeq,
    VOS_UINT8                           enStates,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDBMStru,
    VOS_UINT32                          ulIsReplySeqNeed
);


extern VOS_UINT32 TAF_XSMS_GetAckDBMStru(
    TAF_XSMS_ADDR_STRU                 *pstAddrStru,
    TAF_XSMS_CAUSE_CODE_STRU           *pstCauseCodeStru,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDBMStru
);

extern VOS_UINT32 TAF_XSMS_EncodeBearDataStruToP2PRaw(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucEncodedLen,
    VOS_UINT8                           ucBearerReplyOptionSeq,
    VOS_UINT16                          usMessageIdentifier,
    VOS_UINT8                           enStates,
    VOS_UINT32                          ulIsReplySeqNeeded
);

extern VOS_UINT32 TAF_XSMS_EncodeBearDataStruToSimRaw(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                           ucBearerReplyOptionSeq,
    VOS_UINT8                          *pucEncodedLen,
    VOS_UINT8                           enStates,
    VOS_UINT32                          ulIsReplySeqNeeded
);

extern VOS_UINT32 TAF_XSMS_EncodeAckMsg(
    TAF_XSMS_ADDR_STRU                 *pstDestAddr,
    TAF_XSMS_CAUSE_CODE_STRU           *pstCauseCode,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucCodedLen
);

extern VOS_VOID TAF_XSMS_EncodeAuth(
    TAF_XSMS_ADDR_STRU                 *pstDestinationAddr,
    VOS_UINT8                          *pucAuthData
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

