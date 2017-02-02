/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnCallReqProc.h
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2007��8��22��
  ����޸�   : 2007��8��22��
  ��������   : Ӧ��������ģ��Ľӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��8��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�
******************************************************************************/
#ifndef  MN_CALL_REQ_PROC_H
#define  MN_CALL_REQ_PROC_H


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "MnCallApi.h"
#include "MnCallBcProc.h"

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
/*****************************************************************************
 �� �� ��  : MN_CALL_CallOrigReqProc
 ��������  : ��������Ӧ�ò����������
             �ú�������鵱ǰ״̬�Ƿ�������һ�����У����Ҽ����еĺ�����ȷ��
             �ú����Ƿ������Լ��Ƿ��ǽ������к��롣���ͨ������CC����
             MNCC_SETUP_REQ��MNCC_EMERG_SETUP_REQԭ�﷢��һ�����л�������С�
 �������  : clientId    - ����������Client��ID
             opId        - Operation ID, ��ʶ���β���
             callId      - �������еĺ���ID������Ψһ�ı�ʶ�������
             pstOrigParm - ����������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_CallOrigReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    MN_CALL_ORIG_PARAM_STRU             *pstOrigParm
);


VOS_UINT32 MN_CALL_InternalCallEndReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_END_PARAM_STRU       *pstEndParm
);


VOS_VOID  MN_CALL_CallEndReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        uccallId,
    const MN_CALL_END_PARAM_STRU        *pstEndParm
);

/*****************************************************************************
 �� �� ��  : MN_CALL_CallAnswerReqProc
 ��������  : ��������Ӧ�ò��Ӧ������
             �ú�������鵱ǰ״̬�Ƿ��������һ�����磬���ͨ������CC����
             MNCC_SETUP_RESԭ���������
 �������  : clientId    - ����������Client��ID
             opId        - Operation ID, ��ʶ���β���
             callId      - ��Ҫ�����ĺ��е�ID
             pstAnsParam - Ӧ��������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_CallAnswerReqProc(
    MN_CLIENT_ID_T                      ucClientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_ANS_PARAM_STRU        *pstAnsParam
);


VOS_VOID  MN_CALL_CallSupsCmdReqProc(struct MsgCB *pstCallSups);


VOS_UINT32  MN_CALL_BuildNormalCallReqProc(MN_CALL_ID_T callId);


VOS_UINT32 MN_CALL_GetMoCallBc(
    MN_CALL_ID_T                        CallId,
    NAS_CC_IE_BC_STRU                  *pstBc1,
    NAS_CC_IE_BC_STRU                  *pstBc2,
    MN_CALL_REP_IND_ENUM_U8            *penBcRepeatInd
);


VOS_VOID MN_CALL_ReportEccNumList(VOS_VOID);


VOS_VOID MN_CALL_StkCallOrigReqProc(struct MsgCB * pstMsg);



TAF_CS_CAUSE_ENUM_UINT32 MN_CALL_GetEndCause(
    TAF_CS_CAUSE_ENUM_UINT32            enEndCause,
    MN_CALL_STATE_ENUM_U8               enCallState
);

VOS_VOID TAF_CALL_RelIncomingOrWaitingCall(
    VOS_UINT8                           ucCallId,
    MN_CALL_STATE_ENUM_U8               enCallState
);

VOS_VOID TAF_CALL_RelRedialingCall(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU      *pstCallSupsParam    
);


VOS_UINT32 MN_CALL_MakeNewCall(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_ID_T                       *pNewCallId
);


VOS_VOID  MN_CALL_RcvAtCssnSetReq(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_SET_CSSN_REQ_STRU          *pstSetCssnReq
);
/*****************************************************************************
 �� �� ��  : MN_CALL_GetEccNumList
 ��������  : ��ȡ�����������б�
 �������  : ��
 �������  : pstEccNumInfo
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID MN_CALL_GetEccNumList(MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo);

/*****************************************************************************
 �� �� ��  : MN_CALL_RcvAtXlemaReq
 ��������  : �����������ѯ����
 �������  :
 �������  : ��
 �� �� ֵ  : ��

*****************************************************************************/
VOS_VOID MN_CALL_RcvAtXlemaReq(MN_CALL_APP_REQ_MSG_STRU            *pstCallMsg);


VOS_VOID  TAF_CALL_RcvStartDtmfReq(struct MsgCB * pstMsgSend);

VOS_VOID  TAF_CALL_RcvStopDtmfReq(struct MsgCB * pstStopDtmf);

#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_CALL_RcvQryEcallInfoReq(MN_CALL_QRY_ECALL_INFO_REQ_STRU *pstQryEcallInfoReq);

VOS_VOID TAF_CALL_EcallSupsCmdRelReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
);
#endif

VOS_VOID MN_CALL_CallSupsCmdRelAllCallReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
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

#endif /* MN_CALL_REQ_PROC_H */

