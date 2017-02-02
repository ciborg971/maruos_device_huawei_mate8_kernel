

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasCcInclude.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif


#define    THIS_FILE_ID        PS_FILE_ID_NASCC_AIRMSGSEND_C

/*lint -save -e958 */

/*****************************************************************************
  2 ����ʵ��
*****************************************************************************/
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
)
{
    NAS_IE_SET_PRESENT(pstCauseIe);


    pstCauseIe->IsExist = VOS_TRUE;

    /* Set octet3 to 0xe0:
           Coding standard: GSM
           Location :       User
           No extended octet
    */
    NAS_IE_SET_OCTET(pstCauseIe, Octet3, 0xe0);

    pstCauseIe->Octet4.CauseValue = enCauseVal;
    pstCauseIe->Octet4.Ext = NAS_CC_IE_NO_EXT;

    NAS_IE_SET_LAST_OCTET_OFFSET(pstCauseIe, Octet4);
}


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
  2.��    ��   : 2015��4��2��
    ��    ��   : w00316404
    �޸�����   : clean coverity
*****************************************************************************/
VOS_VOID  NAS_CC_SendConnectAck(
    VOS_UINT8                           ucTi
)
{
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;
    NAS_CC_MSG_CONNECT_ACK_STRU         stConn;

    /* Added by w00316404 for clean coverity, 2015-4-2, begin */
    ucLen = 0;
    /* Added by w00316404 for clean coverity, 2015-4-2, begin */
    
    PS_MEM_SET(&stConn, 0, sizeof(stConn));

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_CONNECT_ACK, &stConn.stHeader);

    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stConn, aucData, &ucLen);

    NAS_CC_SendMmccDataReq(ucTi, aucData, ucLen);
}



VOS_VOID  NAS_CC_SendDisconnect(
    VOS_UINT8                           ucTi,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal
)
{
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;
    NAS_CC_MSG_DISCONNECT_MO_STRU       stDisc;
    NAS_CC_ENTITY_ID_T                  entityId;


    ucLen = 0;

    PS_MEM_SET(&stDisc, 0, sizeof(stDisc));

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_DISCONNECT, &stDisc.stHeader);
    NAS_CC_FillCauseIe(enCauseVal, &stDisc.stCause);

    entityId = NAS_CC_GetEntityByTi(ucTi);

    /* �ж�UUS1�Ƿ񼤻� */
    NAS_CC_GetMsgUus1Info(entityId,NAS_CC_MSG_DISCONNECT,&stDisc.stUserUser);

    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stDisc, aucData, &ucLen);

    NAS_CC_SendMmccDataReq(ucTi, aucData, ucLen);
}
VOS_VOID  NAS_CC_SendRelease(
    VOS_UINT8                           ucTi,
    VOS_BOOL                            bCausePresent,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal,
    VOS_BOOL                            bCause2Present,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause2Val
)
{
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;
    NAS_CC_MSG_RELEASE_MO_STRU          stRel;
    NAS_CC_ENTITY_ID_T                  entityId;


    ucLen = 0;
    PS_MEM_SET(&stRel, 0, sizeof(stRel));

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_RELEASE, &stRel.stHeader);
    if (bCausePresent)
    {
        NAS_CC_FillCauseIe(enCauseVal, &stRel.stCause);
    }

    if (bCause2Present)
    {
        NAS_CC_FillCauseIe(enCause2Val, &stRel.stCause2);
    }

    entityId = NAS_CC_GetEntityByTi(ucTi);

    /* �ж�UUS1�Ƿ񼤻� */
    NAS_CC_GetMsgUus1Info(entityId,NAS_CC_MSG_RELEASE,&stRel.stUserUser);

    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stRel, aucData, &ucLen);

    NAS_CC_SendMmccDataReq(ucTi, aucData, ucLen);
}
VOS_VOID  NAS_CC_SendReleaseComplete(
    VOS_UINT8                           ucTi,
    VOS_BOOL                            bCausePresent,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal
)
{
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;
    NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU stRelCom;
    NAS_CC_ENTITY_ID_T                  entityId;


    ucLen = 0;
    PS_MEM_SET(&stRelCom, 0, sizeof(stRelCom));

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_RELEASE_COMPLETE, &stRelCom.stHeader);
    if (bCausePresent)
    {
        NAS_CC_FillCauseIe(enCauseVal, &stRelCom.stCause);
    }

    entityId = NAS_CC_GetEntityByTi(ucTi);

    /* ��ȡ������Ϣ */
    NAS_CC_GetMsgUus1Info(entityId,NAS_CC_MSG_RELEASE_COMPLETE,&stRelCom.stUserUser);

    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stRelCom, aucData, &ucLen);

    NAS_CC_SendMmccDataReq(ucTi, aucData, ucLen);
}
VOS_VOID  NAS_CC_SendStartDtmf(
    VOS_UINT8                           ucTi,
    VOS_UINT8                           ucKey
)
{
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;
    NAS_CC_MSG_START_DTMF_STRU          stStartDtmf;


    ucLen = 0;
    PS_MEM_SET(&stStartDtmf, 0, sizeof(stStartDtmf));

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_START_DTMF, &stStartDtmf.stHeader);
    stStartDtmf.stKeypadFacility.IsExist = VOS_TRUE;
    stStartDtmf.stKeypadFacility.KeypadInfo = ucKey;

    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stStartDtmf, aucData, &ucLen);

    NAS_CC_SendMmccDataReq(ucTi, aucData, ucLen);
}



VOS_VOID  NAS_CC_SendStopDtmf(
    VOS_UINT8                           ucTi
)
{
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;
    NAS_CC_MSG_STOP_DTMF_STRU           stStopDtmf;


    ucLen = 0;

    PS_MEM_SET(&stStopDtmf, 0, sizeof(stStopDtmf));

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_STOP_DTMF, &stStopDtmf.stHeader);

    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stStopDtmf, aucData, &ucLen);

    NAS_CC_SendMmccDataReq(ucTi, aucData, ucLen);
}




VOS_VOID  NAS_CC_SendStatus(
    VOS_UINT8                           ucTi,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCauseVal
)
{
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;
    NAS_CC_MSG_STATUS_STRU              stStatus;

    NAS_CC_CALL_STATE_ENUM_U8           enCallState;
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldState;
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyState;

    NAS_CC_ENTITY_ID_T  entityId = NAS_CC_GetEntityByTi(ucTi);

    ucLen = 0;

    if (entityId != NAS_CC_INVALID_ENTITY_ID)
    {
        enCallState = NAS_CC_GetCallState(entityId);
        enHoldState = NAS_CC_GetHoldAuxState(entityId);
        enMptyState = NAS_CC_GetMptyAuxState(entityId);
    }
    else
    {
        enCallState = NAS_CC_CALL_STATE_U0;
        enHoldState = NAS_CC_HOLD_AUX_S_IDLE;
        enMptyState = NAS_CC_MPTY_AUX_S_IDLE;
    }

    PS_MEM_SET(&stStatus, 0, sizeof(stStatus));

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_STATUS, &stStatus.stHeader);
    stStatus.stCallState.IsExist = VOS_TRUE;
    stStatus.stCallState.CodingStd = NAS_CC_CODING_GSM;
    stStatus.stCallState.CallState = enCallState;

    /*
    [9.3.27.1 Auxiliary states]
    The information element is included if and only if the call state is "active"
    or "mobile originating modify" and any auxiliary state is different from "idle".
    */
    if (((NAS_CC_CALL_STATE_U10 == enCallState)
       || (NAS_CC_CALL_STATE_U26 == enCallState))
     && ((NAS_CC_HOLD_AUX_S_IDLE != enHoldState)
       || (NAS_CC_MPTY_AUX_S_IDLE != enMptyState)))
    {
        stStatus.stAuxState.IsExist = VOS_TRUE;
        stStatus.stAuxState.HoldAuxState = enHoldState;
        stStatus.stAuxState.MptyAuxState = enMptyState;
        stStatus.stAuxState.Ext = NAS_CC_IE_NO_EXT;
    }

    NAS_CC_FillCauseIe(enCauseVal, &stStatus.stCause);

    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stStatus, aucData, &ucLen);

    NAS_CC_SendMmccDataReq(ucTi, aucData, ucLen);
}


 VOS_VOID NAS_CC_SendMmccStartCcReq(
             VOS_UINT8                           ucTi
)
{
    NAS_CC_MSG_START_CC_STRU            stStartCc;
    VOS_UINT8                           aucData[NAS_CC_MAX_AIR_MSG_LEN];
    VOS_UINT8                           ucLen;


    ucLen = 0;
    PS_MEM_SET(&stStartCc,0,sizeof(stStartCc));

    /* ��дstart cc ��Ϣͷ */
    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_START_CC, &stStartCc.stHeader);

    /* ����start cc��Ϣ */
    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stStartCc,aucData,&ucLen);

    /* ����MMCC_START_CCԭ�ｫ��Ϣ�������� */
    NAS_CC_SendMmccStartCc(ucTi, aucData, ucLen);

}

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

