
#ifndef  MN_CALL_SEND_CC_H
#define  MN_CALL_SEND_CC_H


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "MnCallApi.h"
#include "MnCallMnccProc.h"
#include "MnCallFacilityDecode.h"
#include "MnCallBcProc.h"
#include "MnCallCtx.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ��������
*****************************************************************************/


/*****************************************************************************
  3���Ͷ���
*****************************************************************************/


/*****************************************************************************
  4 �궨��
*****************************************************************************/


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/
VOS_UINT32  MN_CALL_SendMnccPrimitive(MsgBlock * pMsg);


VOS_UINT32  MN_CALL_SendCcSetupReq(
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd,
    const NAS_CC_IE_BC_STRU            *pstBc1,
    const NAS_CC_IE_BC_STRU            *pstBc2,
    const MN_CALL_MGMT_STRU            *pstCallInfo
);

/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcEmergSetupReq
 ��������  : ����MNCC_EMERG_SETUP_REQԭ��
 �������  : CallId        - ���е�ID
             ucCategory    - ������������
             pstBc         - Bear capability (��ѡ)
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͳɹ�, VOS_ERR - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcEmergSetupReq(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           *pucCategory
);


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcCallConfReq
 ��������  : ����MNCC_CALL_CONF_REQԭ��
 �������  : CallId        - ���е�ID
             ucRepeatInd   - Repeat Indicator, ���pstBc2Ϊ�ոò�����������
             pstBc1        - Bear capability 1 (��ѡ)
             pstBc2        - Bear capability 2 (��ѡ), ���pstBc1Ϊ�ոò�����������
             Cause         - ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͳɹ�, VOS_ERR - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcCallConfReq(
    MN_CALL_ID_T                        CallId,
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd,
    const NAS_CC_IE_BC_STRU             *pstBc1,
    const NAS_CC_IE_BC_STRU             *pstBc2,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
);


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcDiscReq
 ��������  : ����MNCC_DISC_REQԭ��(��Я��Facility)
 �������  : CallId        - ���е�ID
             Cause         - �Ҷϵ�ԭ��
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͳɹ�, VOS_ERR - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcDiscReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
);


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcRelReq
 ��������  : ����MNCC_REL_REQԭ��(��Я��Facility)
 �������  : CallId        - ���е�ID
             Cause         - �Ҷϵ�ԭ��
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͳɹ�, VOS_ERR - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcRelReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
);


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcRejReq
 ��������  : ����MNCC_REJ_REQԭ��
 �������  : CallId        - ���е�ID
             Cause         - �ܾ���ԭ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_SendCcRejReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
);


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcSetupRsp
 ��������  : ����MNCC_SETUP_RESԭ��
 �������  : CallId - ���е�ID
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͳɹ�, VOS_ERR - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcSetupRsp(
    MN_CALL_ID_T                        callId
);


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcHoldReq
 ��������  : ����MNCC_HOLD_REQԭ��
 �������  : CallId - ���е�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_SendCcHoldReq(
    MN_CALL_ID_T                        callId
);


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcRetrieveReq
 ��������  : ����MNCC_RETRIEVE_REQԭ��
 �������  : CallId - ���е�ID
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͳɹ�, VOS_ERR - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_SendCcRetrieveReq(
    MN_CALL_ID_T                        callId
);


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcSimpleFacility
 ��������  : ���ͼ򵥵�MNCC_FACILITY_REQԭ��(��Operation Code֮��û����������)
 �������  : CallId - ���е�ID
             OpCode - Operation Code
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͳɹ�, VOS_ERR - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_SendCcSimpleFacility(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_OPERATION_CODE_T         opCode
);


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcStartDtmfReq
 ��������  : ����MNCC_START_DTMF_REQԭ��
 �������  : CallId - ���е�ID
             ucKey  - Ҫ���͵�DTMF����
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͳɹ�, VOS_ERR - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcStartDtmfReq(
    MN_CALL_ID_T                        callId,
    VOS_INT8                            cKey
);


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcStopDtmfReq
 ��������  : ����MNCC_STOP_DTMF_REQԭ��
 �������  : CallId - ���е�ID
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͳɹ�, VOS_ERR - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcStopDtmfReq(
    MN_CALL_ID_T                        callId
);

/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcAlertReq
 ��������  : ����MNCC_ALERT_REQԭ��
 �������  : CallId        - ���е�ID
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͳɹ�, VOS_ERR - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_SendCcAlertReq(
    MN_CALL_ID_T                        callId
);


/*****************************************************************************
 �� �� ��  : MN_CALL_SendCcDeflectFacility
 ��������  : ����MNCC_DISC_REQԭ��, ����Я���������ƫתҵ���Facility IE
 �������  : CallId      - ���е�ID
             pstRedirNum - ƫת����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_SendCcDeflectFacility(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstRedirNum
);


VOS_VOID  MN_CALL_SendCcActCcbsReq(
    MN_CALL_ID_T                        callId
);


VOS_UINT32  MN_CALL_SendCcEstCnfReq(
    MN_CALL_ID_T                        callId,
    MN_CALL_REP_IND_ENUM_U8             enRepeatInd,
    const NAS_CC_IE_BC_STRU             *pstBc1,
    const NAS_CC_IE_BC_STRU             *pstBc2,
    MN_CALL_CC_CAUSE_ENUM_U8            enCause
);


VOS_UINT32  MN_CALL_SendCcbsSetupReq(
    MN_CALL_ID_T                        callId
);

VOS_UINT32  MN_CALL_SendCcBufferedEmgSetupReq(
    MNCC_REQ_PRIM_MSG_STRU             *pstBufferdEmgSetupMsg
);

VOS_UINT32  MN_CALL_SendCcBufferedSetupReq(
    MNCC_REQ_PRIM_MSG_STRU             *pstBufferdSetupMsg
);


#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID  TAF_CALL_SendCcSrvccCallInfoNtf(
    VOS_UINT8                           ucCallNum,
    MNCC_ENTITY_STATUS_STRU            *pstEntitySta
);
#endif
VOS_VOID TAF_CALL_ProcCallStatusFail(
    VOS_UINT8                           ucCallId,
    MN_CALL_STATE_ENUM_U8               enCallState
);
VOS_VOID TAF_CALL_SendCcCallStatusNty(
    VOS_UINT8                           ucCallId,
    MNCC_CALL_STATUS_ENUM_UINT8         enCallStatus
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

#endif /* MN_CALL_SEND_CC_H */


