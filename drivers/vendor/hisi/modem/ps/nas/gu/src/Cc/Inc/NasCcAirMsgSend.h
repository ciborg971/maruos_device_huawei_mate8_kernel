
#ifndef  NAS_CC_AIRMSG_SEND_H
#define  NAS_CC_AIRMSG_SEND_H

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
#include "NasCcIe.h"


/*****************************************************************************
  2 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_CC_SendConnectAck
 ��������  : ����Connect acknowladge��Ϣ
 �������  : ucTi - Transaction ID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_CC_SendConnectAck(
    VOS_UINT8                           ucTi
);


/*****************************************************************************
 �� �� ��  : NAS_CC_SendDisconnect
 ��������  : ����Disconnect��Ϣ
 �������  : ucTi       - Transaction ID
             enCauseVal - �Ҷϵ�ԭ��ֵ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_CC_SendDisconnect(
    VOS_UINT8                           ucTi,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal
);


/*****************************************************************************
 �� �� ��  : NAS_CC_SendRelease
 ��������  : ����Release��Ϣ
 �������  : ucTi          - Transaction ID
             bCausePresent - �Ƿ���release��Ϣ��Я��ԭ��
             enCauseVal    - �Ҷϵ�ԭ��ֵ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_CC_SendRelease(
    VOS_UINT8                           ucTi,
    VOS_BOOL                            bCausePresent,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal,
    VOS_BOOL                            bCause2Present,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause2Val
);


/*****************************************************************************
 �� �� ��  : NAS_CC_SendReleaseComplete
 ��������  : ����release complete��Ϣ
 �������  : ucTi          - Transaction ID
             bCausePresent - �Ƿ���release complete��Ϣ��Я��ԭ��
             enCauseVal    - �Ҷϵ�ԭ��ֵ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_CC_SendReleaseComplete(
    VOS_UINT8                           ucTi,
    VOS_BOOL                            bCausePresent,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal
);


/*****************************************************************************
 �� �� ��  : NAS_CC_SendStartDtmf
 ��������  : ����Start Dtmf��Ϣ
 �������  : ucTi  - Transaction ID
              ucKey - Ҫ���͵�DTMF�ַ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_CC_SendStartDtmf(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           ucKey
);


/*****************************************************************************
 �� �� ��  : NAS_CC_SendStopDtmf
 ��������  : ����Stop Dtmf��Ϣ
 �������  : ucTi  - Transaction ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_CC_SendStopDtmf(
    VOS_UINT8                           ucTi
);


/*****************************************************************************
 �� �� ��  : NAS_CC_SendStatus
 ��������  : ����status��Ϣ
 �������  : ucTi          - Transaction ID
             enCauseVal    - ����status��ԭ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_CC_SendStatus(
    VOS_UINT8                           ucTi,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal
);

/*****************************************************************************
 �� �� ��  : NAS_CC_FillCauseIe
 ��������  :
 �������  : enCauseVal - ԭ��ֵ
 �������  : pstCauseIe - ��õ�Cause IE
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_CC_FillCauseIe(
    NAS_CC_CAUSE_VALUE_ENUM_U32          enCauseVal,
    NAS_CC_IE_CAUSE_STRU                *pstCauseIe
);

/*****************************************************************************
 �� �� ��  : NAS_CC_SendMmccStartCcReq
 ��������  : ����start cc��Ϣ
 �������  : ucTi - Transaction ID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   :
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_CC_SendMmccStartCcReq(
      VOS_UINT8                           ucTi
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

#endif /* NAS_CC_AIRMSG_SEND_H */

