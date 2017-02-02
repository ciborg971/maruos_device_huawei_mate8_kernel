/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

******************************************************************************
  �� �� ��   : NasCcMsgEncDec.h
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2006��8��25��
  ����޸�   :
  ��������   : �ṩCC�տ���Ϣ�����Ľӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��8��28��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __NAS_CC_MSG_ENCDEC_H__
#define __NAS_CC_MSG_ENCDEC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "NasCcCommon.h"
#include "NasMsgEncDec.h"
#include "NasCcAirMsg.h"


#pragma pack(4)

/*****************************************************************************
  2 ���Ͷ���
*****************************************************************************/

typedef struct
{
    VOS_BOOL                            bOpCodePresent;
    NAS_SS_COMPONET_TYPE_TAG_ENUM_U8    ucCompType;
    VOS_UINT8                           ucInvokeID;
    NAS_SS_OPERATION_ENUM_U8            enOpCode;
    VOS_UINT8                           ucParamOffset;
}NAS_CC_FACILITY_INFO_STRU;


/*****************************************************************************
  3 �ӿں�������
*****************************************************************************/
VOS_VOID NAS_CC_EncodeMsg(
    const NAS_CC_AIR_MSG_UNION          *punMsg,
    VOS_UINT8                           *pucRawData,
    VOS_UINT8                           *pucLength
);

NAS_PROTOCOL_ERR_ENUM_U8 NAS_CC_DecodeMsg(
    const VOS_UINT8                     *pucRawData,
    VOS_UINT8                           ucLength,
    NAS_CC_AIR_MSG_UNION                *punMsg
);

VOS_UINT8 NAS_CC_GetFacilityInfo(
    const VOS_UINT8                     *paucFacility,
    NAS_CC_FACILITY_INFO_STRU           *pstFacilityInfo
);

VOS_VOID  NAS_CC_FillAirMsgHeader(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           ucMsgType,
    NAS_AIR_MSG_HDR_STRU                *pstHeader
);



#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* __NAS_CC_MSG_ENCDEC_H__ */

