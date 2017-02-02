

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "NasCcInclude.h"
#include "NasMmlCtx.h"
#include "MnCall.h"
#include "NasCcCtx.h"
#include "NasCcProcNvim.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


#define THIS_FILE_ID PS_FILE_ID_NASCC_MMNC_PROC_C

/*****************************************************************************
  2 ��������
*****************************************************************************/
/* ���뻺�棬���ڴ�ű������ɵĿտ���Ϣ���� */
LOCAL NAS_CC_AIR_MSG_BUF_STRU  f_stCcEncodeBuf;

NAS_CC_UUS1_INFO_STRU    f_astUus1MsgBuf[NAS_CC_MAX_UUIE_MSG_NUM];

/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

LOCAL VOS_VOID  NAS_CC_ProcMnccEmergSetupReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_BC_PARAMS_STRU               stBcParams;

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_EMERGENCY_SETUP,
                            &pstMsg->unParam.stEmerg.stHeader);

    NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0_1);

    /* ����redial��� */
    NAS_CC_SendMmccEstReq(ucTi, MMCC_EMERGENCY_CALL,MMCC_CALL_MODE_SPEECH,
                          MMCC_NO_CALL_PRIORITY, pstMsg->ucRedialFlg);

    NAS_CC_StartTimer(entityId, TI_NAS_CC_T303, 0);

    /* ����emergency setup��Ϣ������ */
    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stEmerg,
                     g_stNasCcBufferedSetupMsg.aucBuf,
                     (VOS_UINT8 *)&g_stNasCcBufferedSetupMsg.ulLen);

    NAS_CC_INFO_LOG("NAS_CC_ProcMnccEmergSetupReq: ChangeCallState to U0_1");

    /* ��¼���е�һЩ���� */
    stBcParams.enItc = pstMsg->unParam.stEmerg.stBC.Octet3.InfoTransCap;
    NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_1, &stBcParams);
}


/*****************************************************************************
 �� �� ��  : NAS_CC_ProcMnccCallConfReq
 ��������  : ����MNCC_CALL_CONF_REQԭ��
 �������  : pstMsg      - �����ϲ��MNCCԭ����Ϣ
              entityId    - �����ԭ���CCʵ���ID
              ucTi        - CCʵ���Ӧ��transaction ID
              enCurrState - CCʵ�嵱ǰ�ĺ���״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccCallConfReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_BC_PARAMS_STRU               stBcParams;

    if (NAS_CC_CALL_STATE_U6 == enCurrState)
    {
        /* ��дcall confirm��Ϣͷ */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_CALL_CNF, &pstMsg->unParam.stCallCnf.stHeader);

        /* ����call confirm��Ϣ */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stCallCnf,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* ����MMCC_DATA_REQԭ�ｫ��Ϣ�������� */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_INFO_LOG("NAS_CC_ProcMnccCallConfReq: ChangeCallState to U9");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U9);

        NAS_CC_UpdateCallId(entityId, pstMsg->ucCallId);

        /* ���BC�ı䣬��Ҫ�����ѱ���ĳ����������� */
        if (pstMsg->unParam.stCallCnf.stBC1.IsExist)
        {
            stBcParams.enItc = pstMsg->unParam.stCallCnf.stBC1.Octet3.InfoTransCap;
            NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_1, &stBcParams);
            if (pstMsg->unParam.stCallCnf.stBC2.IsExist)
            {
                stBcParams.enItc = pstMsg->unParam.stCallCnf.stBC2.Octet3.InfoTransCap;
                NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_2, &stBcParams);
            }
        }

        /* �ŵ��Ѿ���������,��Ҫ���õ�ǰʹ�ô��ŵ���ÿһ������ʵ��.
           ���������д���ʱ,ԭ���ĺ��б��ͷź�,�ͶϿ��ŵ�
           CC�ں��н�����ʱ��,������˱�־*/
        if (VOS_TRUE == NAS_CC_IsAttachUserConn())
        {
            NAS_CC_SetUserConnEntity(entityId);
        }
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccCallConfReq: bad state.", enCurrState);
    }
}


LOCAL VOS_VOID  NAS_CC_ProcMnccCcEstCnfReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    if (NAS_CC_CALL_STATE_U0_4 == enCurrState)
    {
        /* ��дcc establishment cnf��Ϣͷ */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_CC_EST_CNF,
                                &pstMsg->unParam.stCcEstCnf.stHeader);

        /* ����cc establishment cnf��Ϣ */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stCcEstCnf,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* ����MMCC_DATA_REQԭ�ｫ��Ϣ�������� */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_StartTimer(entityId, TI_NAS_CC_T335, 0);

        NAS_CC_INFO_LOG("NAS_CC_ProcMnccCcEstCnfReq: ChangeCallState to U0.5");

        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0_5);

        NAS_CC_UpdateCallId(entityId, pstMsg->ucCallId);

    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccCcEstCnfReq: bad state.", enCurrState);
    }
}
LOCAL VOS_VOID  NAS_CC_ProcMnccCcbsSetupReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_BC_PARAMS_STRU               stBcParams;

    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_SETUP, &pstMsg->unParam.stSetup.stHeader);
    NAS_CC_StartTimer(entityId, TI_NAS_CC_T303, 0);

    /* �˴����������Ŀ��������NAS_CC_GetMsgUus1Info��ʹ�õ����º��ITC  */
    /* ��¼���еĳ����������� */
    stBcParams.enItc = pstMsg->unParam.stSetup.stBC1.Octet3.InfoTransCap;
    NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_1, &stBcParams);
    if (pstMsg->unParam.stSetup.stBC2.IsExist)
    {
        stBcParams.enItc = pstMsg->unParam.stSetup.stBC2.Octet3.InfoTransCap;
        NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_2, &stBcParams);
    }

    /* �ж�UUS1�Ƿ񼤻� */
    NAS_CC_GetMsgUus1Info(entityId,
                          NAS_CC_MSG_SETUP,
                          &pstMsg->unParam.stSetup.stUserUser);

    /* ����setup��Ϣ������ */
    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stSetup,
                     g_stNasCcBufferedSetupMsg.aucBuf,
                     (VOS_UINT8 *)&g_stNasCcBufferedSetupMsg.ulLen);

    NAS_CC_SendMmccDataReq(ucTi, g_stNasCcBufferedSetupMsg.aucBuf,
                           g_stNasCcBufferedSetupMsg.ulLen);

    NAS_CC_INFO_LOG("NAS_CC_ProcMnccCcbsSetupReq: ChangeCallState to U1");
    NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U1);


}


VOS_BOOL NAS_CC_IsNeedCreateEntity(
    MNCC_PRIM_NAME_ENUM_U16             enPrimName,
    VOS_UINT8                           ucTi,
    NAS_CC_ENTITY_ID_T                  *pentityId
)
{
    VOS_BOOL                            bIsCreateEntity;

    bIsCreateEntity = VOS_TRUE;

    /* CCBS��ʱ�յ�Setup��Ϣʱ����Ҫ����Entity,�����������Ҫ���� */
    if (enPrimName == MNCC_SETUP_REQ)
    {
        *pentityId = NAS_CC_GetEntityByTi(ucTi);
        if (NAS_CC_INVALID_ENTITY_ID != *pentityId)
        {
            bIsCreateEntity = VOS_FALSE;
        }
    }
    return bIsCreateEntity;
}
VOS_UINT32 NAS_CC_GetCallMode(
    NAS_CC_MSG_SETUP_MO_STRU            *pstSetup
)
{
    if ( ( NAS_CC_ITC_SPEECH == pstSetup->stBC1.Octet3.InfoTransCap )
      || ( NAS_CC_ITC_AUXILIARY_SPEECH == pstSetup->stBC1.Octet3.InfoTransCap ))
    {
        return MMCC_CALL_MODE_SPEECH;
    }
    else
    {
        if ( ( NAS_CC_ITC_UDI == pstSetup->stBC1.Octet3.InfoTransCap )
          && ( NAS_CC_IE_EXT  == pstSetup->stBC1.Octet5.Ext )
          && ( NAS_CC_OTHER_RA_H223_H245 == pstSetup->stBC1.Octet5a.OtherRA ))
        {
            return MMCC_CALL_MODE_VIDEO;
        }
    }
    return MMCC_CALL_MODE_OTHER;
}


LOCAL VOS_VOID  NAS_CC_ProcMnccSetupReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_BC_PARAMS_STRU               stBcParams;
    VOS_UINT32                          ulCallMode;
    NAS_CC_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = NAS_CC_GetCustomCfgInfo();


    if ( (NAS_CC_CALL_STATE_U0_6 == enCurrState)
       &&(NAS_CC_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg))
    {
        NAS_CC_ProcMnccCcbsSetupReq(pstMsg,entityId,ucTi,enCurrState);
        return;
    }


    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_SETUP, &pstMsg->unParam.stSetup.stHeader);

    /* ��ȡ��ǰ����ģʽ */
    ulCallMode = NAS_CC_GetCallMode(&pstMsg->unParam.stSetup);

    /* �˴����������Ŀ��������NAS_CC_GetMsgUus1Info��ʹ�õ����º��ITC,���ܷ��ں���  */

    /* ��¼���еĳ����������� */
    stBcParams.enItc = pstMsg->unParam.stSetup.stBC1.Octet3.InfoTransCap;
    NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_1, &stBcParams);
    if (pstMsg->unParam.stSetup.stBC2.IsExist)
    {
        stBcParams.enItc = pstMsg->unParam.stSetup.stBC2.Octet3.InfoTransCap;
        NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_2, &stBcParams);
    }

    NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0_1);

    /* ����redial��� */
    NAS_CC_SendMmccEstReq(ucTi, MMCC_MO_NORMAL_CALL,ulCallMode,MMCC_NO_CALL_PRIORITY, pstMsg->ucRedialFlg);

    NAS_CC_StartTimer(entityId, TI_NAS_CC_T303, 0);

    /* �ж�UUS1�Ƿ񼤻� */
    NAS_CC_GetMsgUus1Info(entityId,
                          NAS_CC_MSG_SETUP,
                          &(pstMsg->unParam.stSetup.stUserUser));

    /* ����setup��Ϣ������ */
    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stSetup,
                     g_stNasCcBufferedSetupMsg.aucBuf,
                     (VOS_UINT8 *)&g_stNasCcBufferedSetupMsg.ulLen);

    NAS_CC_INFO_LOG("NAS_CC_ProcMnccSetupReq: ChangeCallState to U0_1");

    /* �ŵ��Ѿ���������,��Ҫ���õ�ǰʹ�ô��ŵ���ÿһ������ʵ��.
       ���������д���ʱ,ԭ���ĺ��б��ͷź�,�ͶϿ��ŵ�
       CC�ں��н�����ʱ��,������˱�־*/
    if (VOS_TRUE == NAS_CC_IsAttachUserConn())
    {
        NAS_CC_SetUserConnEntity(entityId);
    }


}


/*****************************************************************************
 �� �� ��  : NAS_CC_ProcMnccAlertReq
 ��������  : ����MNCC_ALERT_REQԭ��
 �������  : pstMsg      - �����ϲ��MNCCԭ����Ϣ
              entityId    - �����ԭ���CCʵ���ID
              ucTi        - CCʵ���Ӧ��transaction ID
              enCurrState - CCʵ�嵱ǰ�ĺ���״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccAlertReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    if (NAS_CC_CALL_STATE_U9 == enCurrState)
    {
        /* ��дalerting��Ϣͷ */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_ALERTING, &pstMsg->unParam.stAlert.stHeader);


        /* �ж�UUS1�Ƿ񼤻� */
        NAS_CC_GetMsgUus1Info(entityId,
                              NAS_CC_MSG_ALERTING,
                              &(pstMsg->unParam.stAlert.stUserUser));

        /* ����alerting��Ϣ */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stAlert,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* ����MMCC_DATA_REQԭ�ｫ��Ϣ�������� */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_INFO_LOG("NAS_CC_ProcMnccAlertReq: ChangeCallState to U7");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U7);

        /* �ŵ��Ѿ���������,��Ҫ���õ�ǰʹ�ô��ŵ���ÿһ������ʵ��.
           ���������д���ʱ,ԭ���ĺ��б��ͷź�,�ͶϿ��ŵ�
           CC�ں��н�����ʱ��,������˱�־*/
        if (VOS_TRUE == NAS_CC_IsAttachUserConn())
        {
            NAS_CC_SetUserConnEntity(entityId);
        }
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccAlertReq: bad state.", enCurrState);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_ProcMnccSetupRsp
 ��������  : ����MNCC_SETUP_RESԭ��
 �������  : pstMsg      - �����ϲ��MNCCԭ����Ϣ
              entityId    - �����ԭ���CCʵ���ID
              ucTi        - CCʵ���Ӧ��transaction ID
              enCurrState - CCʵ�嵱ǰ�ĺ���״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccSetupRsp(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_BC_PARAMS_STRU               stBcParams;

    if ((NAS_CC_CALL_STATE_U9 == enCurrState)
      ||(NAS_CC_CALL_STATE_U7 == enCurrState))
    {
        /* ��дconnect��Ϣͷ */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_CONNECT, &pstMsg->unParam.stConn.stHeader);

        /* �ж�UUS1�Ƿ񼤻� */
        NAS_CC_GetMsgUus1Info(entityId,NAS_CC_MSG_CONNECT,&(pstMsg->unParam.stConn.stUserUser));

        /* ����connect��Ϣ */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stConn,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* ����MMCC_DATA_REQԭ�ｫ��Ϣ�������� */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_StartTimer(entityId, TI_NAS_CC_T313, 0);

        /*
        [5.2.2.9 User connection attachment during a mobile terminating call]
        For speech calls: The mobile station shall attach the user connection
        at latest when sending the connect message.
        */
        NAS_CC_GetBcParams(entityId, NAS_CC_BC_PARAM_CURR, &stBcParams);
        if ( (NAS_CC_ITC_SPEECH == stBcParams.enItc)
          || (NAS_CC_ITC_AUXILIARY_SPEECH == stBcParams.enItc))
        {
            NAS_CC_AttachUserConn(entityId, NAS_CC_ITC_SPEECH);
        }

        NAS_CC_INFO_LOG("NAS_CC_ProcMnccSetupRsp: ChangeCallState to U8");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U8);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccSetupRsp: bad state.", enCurrState);
    }
}



LOCAL VOS_VOID  NAS_CC_ProcMnccDiscReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = NAS_CC_GetCustomCfgInfo();

    if ((NAS_CC_CALL_STATE_U0 == enCurrState)
      ||(NAS_CC_CALL_STATE_U11 == enCurrState)
      ||(NAS_CC_CALL_STATE_U19 == enCurrState))
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccDiscReq: bad state.", enCurrState);
        return;
    }

    NAS_CC_StopAllTimer(entityId);

    switch (enCurrState)
    {
        case NAS_CC_CALL_STATE_U0_1:
            /* MM���ӻ�δ�����ɹ���ֱ���ͷ�MM���� */
            NAS_CC_SendMmccAbortReq(ucTi);
            NAS_CC_SendMnccMsg(entityId, MNCC_REL_CNF, VOS_NULL_PTR, 0);
            NAS_CC_INFO_LOG1("NAS_CC_ProcMnccDiscReq: ChangeCallState to U0, current state:", enCurrState);
            NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
            break;

        case NAS_CC_CALL_STATE_U12:
            /* disconnect indication״̬�������緢��release��Ϣ */
            NAS_CC_SendRelease(ucTi, VOS_FALSE, 0, VOS_FALSE, 0);
            NAS_CC_StartTimer(entityId, TI_NAS_CC_T308, NAS_CC_T308_FIRST);
            NAS_CC_INFO_LOG1("NAS_CC_ProcMnccDiscReq: ChangeCallState to U19, current state:", enCurrState);
            NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U19);
            break;

        case NAS_CC_CALL_STATE_U0_6:
            if (NAS_CC_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
            {
                /*�û��ܾ��غ�������release complete��Ϣ*/
                NAS_CC_SendReleaseComplete(ucTi, VOS_TRUE, NAS_CC_CAUSE_17);
                NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);
                NAS_CC_SendMnccMsg(entityId, MNCC_REL_CNF, VOS_NULL_PTR, 0);
                NAS_CC_INFO_LOG1("NAS_CC_ProcMnccDiscReq: ChangeCallState to U0, current state:", enCurrState);
                NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
            }

            break;

        default:
            /* �Ͽ��û�����(TBD) */

            /* ��дdisconnect��Ϣͷ */
            NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_DISCONNECT, &pstMsg->unParam.stDisc.stHeader);

            /* �ж�UUS1�Ƿ񼤻� */
            NAS_CC_GetMsgUus1Info(entityId,NAS_CC_MSG_DISCONNECT,&(pstMsg->unParam.stDisc.stUserUser));

            /* ����disconnect��Ϣ */
            NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stDisc,
                             f_stCcEncodeBuf.aucBuf,
                             (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

            /* ����MMCC_DATA_REQԭ�ｫ��Ϣ�������� */
            NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

            NAS_CC_StartTimer(entityId,
                              TI_NAS_CC_T305,
                              pstMsg->unParam.stDisc.stCause.Octet4.CauseValue);
            NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U11);
    }

/*
���迼�ǵ�:
In the "mobile terminating call confirmed" state or the "call received" state,
if the user of a mobile station is User Determined User Busy then a DISCONNECT
message shall be sent with cause #17 "user busy". In the "mobile terminating call
confirmed" state, if the user of a mobile station wishes to reject the call then
a DISCONNECT message shall be sent with cause #21 "call rejected".
*/
}


/*****************************************************************************
 �� �� ��  : NAS_CC_ProcMnccRelReq
 ��������  : ����MNCC_REL_REQԭ��
 �������  : pstMsg      - �����ϲ��MNCCԭ����Ϣ
              entityId    - �����ԭ���CCʵ���ID
              ucTi        - CCʵ���Ӧ��transaction ID
              enCurrState - CCʵ�嵱ǰ�ĺ���״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccRelReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    if (NAS_CC_CALL_STATE_U12 == enCurrState)
    {
        NAS_CC_StopAllTimer(entityId);

        /* ��дrelease��Ϣͷ */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_RELEASE, &pstMsg->unParam.stRel.stHeader);

        /* �ж�UUS1�Ƿ񼤻� */
        NAS_CC_GetMsgUus1Info(entityId,NAS_CC_MSG_RELEASE,&(pstMsg->unParam.stRel.stUserUser));

        /* ����release��Ϣ */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stRel,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* ����MMCC_DATA_REQԭ�ｫ��Ϣ�������� */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_StartTimer(entityId, TI_NAS_CC_T308, NAS_CC_T308_FIRST);
        NAS_CC_INFO_LOG("NAS_CC_ProcMnccRelReq ChangeCallState to U19");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U19);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccRelReq: bad state.", enCurrState);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_ProcMnccRejReq
 ��������  : ����MNCC_REJ_REQԭ��
 �������  : pstMsg      - �����ϲ��MNCCԭ����Ϣ
              entityId    - �����ԭ���CCʵ���ID
              ucTi        - CCʵ���Ӧ��transaction ID
              enCurrState - CCʵ�嵱ǰ�ĺ���״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccRejReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    if (NAS_CC_CALL_STATE_U6 == enCurrState)
    {
        NAS_CC_StopAllTimer(entityId);

        /* ��дrelease complete��Ϣͷ */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_RELEASE_COMPLETE, &pstMsg->unParam.stRelComp.stHeader);

        /* �ж�UUS1�Ƿ񼤻� */
        NAS_CC_GetMsgUus1Info(entityId,NAS_CC_MSG_RELEASE_COMPLETE,&(pstMsg->unParam.stRelComp.stUserUser));

        /* ����release complete��Ϣ */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stRelComp,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* ����MMCC_DATA_REQԭ�ｫ��Ϣ�������� */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);

        NAS_CC_INFO_LOG("NAS_CC_ProcMnccRelReq ChangeCallState to U0");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccRejReq: bad state.", enCurrState);
    }
}



LOCAL VOS_VOID  NAS_CC_ProcMnccFacilityReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{

    NAS_SS_OPERATION_ENUM_U8            enOperation;
    NAS_CC_FACILITY_INFO_STRU           stFacInfo;
    VOS_UINT32                          ulResult;


    enOperation = NAS_SS_OPERATION_BUTT;

    (VOS_VOID)NAS_CC_GetFacilityInfo(pstMsg->unParam.stFac.stFacility.aucFacility, &stFacInfo);

    /* ȡ��facility�е�ss operation code */
    if (stFacInfo.bOpCodePresent)
    {
        enOperation = stFacInfo.enOpCode;
    }
    else
    {
        if (VOS_ERR == NAS_CC_RestoreSsOperation(entityId,
                                      stFacInfo.ucInvokeID,
                                      &enOperation))
        {
            NAS_CC_ERR_LOG("NAS_CC_ProcMnccFacilityReq: Unknown invoke ID.");
        }
    }

    /*
    ����MPTY��������Ҫ�������Ƿ�����Ȼ��ı���Ӱ���ʵ��״̬����������ʱ��
    */
    switch (enOperation)
    {
    case NAS_SS_OPERATION_BUILD_MPTY:
    case NAS_SS_OPERATION_HOLD_MPTY:
    case NAS_SS_OPERATION_RETRIEVE_MPTY:
    case NAS_SS_OPERATION_SPLIT_MPTY:
        if (NAS_SS_OPERATION_HOLD_MPTY == enOperation)
        {
            ulResult = NAS_CC_CheckSsSwitchHoldAllowed();
        }
        else if (NAS_SS_OPERATION_RETRIEVE_MPTY == enOperation)
        {
            ulResult = NAS_CC_CheckSsSwitchRetrieveAllowed();
        }
        else
        {
            ulResult = VOS_OK;
        }

        if ( (NAS_CC_CheckMptyOperation(entityId, enOperation) == VOS_OK)
          && (VOS_OK == ulResult) )
        {
            NAS_CC_HandleMptyEvent(entityId, NAS_CC_MPTY_EVT_INVOKE, enOperation);

            NAS_CC_SetSsSwitchInvokeId(VOS_TRUE, stFacInfo.ucInvokeID);

            NAS_CC_StartTimer(entityId, TI_NAS_CC_MPTY, stFacInfo.ucInvokeID);
            NAS_CC_StoreSsOperation(entityId, stFacInfo.ucInvokeID, enOperation);
        }
        else
        {
            NAS_CC_SendMnccMsg(entityId,
                               MNCC_FACILITY_LOCAL_REJ,
                               &stFacInfo.ucInvokeID,
                               sizeof(stFacInfo.ucInvokeID));
            return;
        }
        break;

    case NAS_SS_OPERATION_EXPLICIT_CT:
    /* �˴�Ŀǰû�н���CC״̬�ļ�飬�Ժ���Ҫ���� */
        NAS_CC_StartTimer(entityId, TI_NAS_CC_ECT, stFacInfo.ucInvokeID);
        NAS_CC_StoreSsOperation(entityId, stFacInfo.ucInvokeID, enOperation);
        break;
    default:
        break;
    }

    /* ��дfacility��Ϣͷ */
    NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_FACILITY, &pstMsg->unParam.stFac.stHeader);

    /* ����facility��Ϣ */
    NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stFac,
                     f_stCcEncodeBuf.aucBuf,
                     (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

    /* ����MMCC_DATA_REQԭ�ｫ��Ϣ�������� */
    NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);
}



LOCAL VOS_VOID  NAS_CC_ProcMnccHoldReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldState = NAS_CC_GetHoldAuxState(entityId);
    NAS_CC_CAUSE_VALUE_ENUM_U32          enCause;
    VOS_UINT32                          ulResult;

    if ((NAS_CC_CALL_STATE_U10 == enCurrState)
     || (NAS_CC_CALL_STATE_U26 == enCurrState))
    {
        ulResult = NAS_CC_CheckSsSwitchHoldAllowed();

        if ( (NAS_CC_HOLD_AUX_S_IDLE == enHoldState)
          && (VOS_OK == ulResult) )
        {
            NAS_AIR_MSG_HDR_STRU  stHeader;

            /* ��дhold��Ϣͷ */
            NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_HOLD, &stHeader);

            /* ����hold��Ϣ */
            NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stHeader,
                             f_stCcEncodeBuf.aucBuf,
                             (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

            /* ����MMCC_DATA_REQԭ�ｫ��Ϣ�������� */
            NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

            NAS_CC_StartTimer(entityId, TI_NAS_CC_HOLD, 0);

            NAS_CC_INFO_LOG("NAS_CC_ProcMnccHoldReq ChangeHoldAuxState to HOLD_REQ");
            NAS_CC_ChangeHoldAuxState(entityId, NAS_CC_HOLD_AUX_S_HOLD_REQ);

            NAS_CC_SetSsSwitchHoldInfo(entityId, NAS_CC_SS_SWITCH_WAIT_CNF, NAS_CC_CAUSE_NULL);

            return;
        }
        else
        {
            NAS_CC_ERR_LOG1("NAS_CC_ProcMnccHoldReq: bad hold state.", enHoldState);
        }
    }

    NAS_CC_ERR_LOG1("NAS_CC_ProcMnccHoldReq: bad state.", enCurrState);

    /* �ڶϿ��������յ�HOLD������ʹ��һ���ض�ԭ��ֵ��MNCALL�ڴ���HOLD REJʱ��
       ����Ǹ�ԭ��ֵ���򲻸��´���ԭ��ֵ */
    if ((NAS_CC_CALL_STATE_U11 == enCurrState)
     || (NAS_CC_CALL_STATE_U12 == enCurrState))
    {
        enCause = NAS_CC_CAUSE_CC_INTER_ERR_HOLD_REJ_IN_DISC_STATE;
    }
    else
    {
        enCause = NAS_CC_CAUSE_111;
    }

    NAS_CC_SendMnccMsg(entityId,
                       MNCC_HOLD_REJ,
                       &enCause,
                       sizeof(enCause));

    return;
}



LOCAL VOS_VOID  NAS_CC_ProcMnccRetrieveReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldState = NAS_CC_GetHoldAuxState(entityId);
    NAS_AIR_MSG_HDR_STRU                stHeader;
    VOS_UINT32                          ulResult;
    NAS_CC_CAUSE_VALUE_ENUM_U32          enCause;

    if ((NAS_CC_CALL_STATE_U10 == enCurrState)
     || (NAS_CC_CALL_STATE_U26 == enCurrState))
    {
        ulResult = NAS_CC_CheckSsSwitchRetrieveAllowed();

        if ( (NAS_CC_HOLD_AUX_S_CALL_HELD == enHoldState)
          && (VOS_OK == ulResult) )
        {
            /* ��дretrieve��Ϣͷ */
            NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_RETRIEVE, &stHeader);

            /* ����retrieve��Ϣ */
            NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&stHeader,
                             f_stCcEncodeBuf.aucBuf,
                             (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

            /* ����MMCC_DATA_REQԭ�ｫ��Ϣ�������� */
            NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

            NAS_CC_StartTimer(entityId, TI_NAS_CC_HOLD, 0);

            NAS_CC_INFO_LOG("NAS_CC_ProcMnccRetrieveReq ChangeHoldAuxState to RETRIEVE_REQ");
            NAS_CC_ChangeHoldAuxState(entityId, NAS_CC_HOLD_AUX_S_RETRIEVE_REQ);

            NAS_CC_SetSsSwitchRetrieveInfo(entityId, NAS_CC_SS_SWITCH_WAIT_CNF, NAS_CC_CAUSE_NULL);

            return;
        }
        else
        {
            NAS_CC_ERR_LOG1("NAS_CC_ProcMnccRetrieveReq: bad hold state.", enHoldState);
        }
    }

    NAS_CC_ERR_LOG1("NAS_CC_ProcMnccRetrieveReq: bad state.", enCurrState);
    enCause = NAS_CC_CAUSE_111;
    NAS_CC_SendMnccMsg(entityId,
                       MNCC_RETRIEVE_REJ,
                       &enCause,
                       sizeof(enCause));

    return;

}
LOCAL VOS_VOID  NAS_CC_ProcMnccStartDtmfReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_CAUSE_VALUE_ENUM_U32          cause;
    NAS_CC_DTMF_STATE_ENUM              enDtmfState = NAS_CC_GetDtmfState(entityId);

    /* �Ƿ���DTMF�������ڽ��� */
    if ((enDtmfState != NAS_CC_DTMF_S_IDLE)
     && (enDtmfState != NAS_CC_DTMF_S_START_REJ))
    {
        /* ����DTMF���� */
        NAS_CC_QueueDtmfReq(entityId,
                            NAS_CC_DTMF_START_REQ,
                            pstMsg->unParam.stStartDtmf.stKeypadFacility.KeypadInfo);
        return;
    }

    /*
    3GPP 24.008 5.5.7 DTMF protocol control procedure

    The mobile station shall be capable of transmitting DTMF messages if and
    only if the mobile station has the user connection for speech attached and
    an appropriate channel is available.
    */
    if (NAS_CC_IsTchAvailable(NAS_CC_ITC_SPEECH))
    {
        /* ��дstart dtmf��Ϣͷ */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_START_DTMF, &pstMsg->unParam.stStartDtmf.stHeader);

        /* ����start dtmf��Ϣ */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stStartDtmf,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* ����MMCC_DATA_REQԭ�ｫ��Ϣ�������� */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_StartTimer(entityId, TI_NAS_CC_T336, 0);
        NAS_CC_INFO_LOG("NAS_CC_ProcMnccStartDtmfReq ChangeDtmfState to START_REQ");
        NAS_CC_ChangeDtmfState(entityId, NAS_CC_DTMF_S_START_REQ);
    }
    else
    {
        /* ����MNCC_START_DTMF_REJԭ�� */
        cause = NAS_CC_CAUSE_111;
        NAS_CC_SendMnccMsg(entityId, MNCC_START_DTMF_REJ, &cause, sizeof(cause));
        NAS_CC_ERR_LOG("NAS_CC_ProcMnccStartDtmfReq: No appropriate channel.");

    }
}



LOCAL VOS_VOID  NAS_CC_ProcMnccStopDtmfReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    NAS_CC_CAUSE_VALUE_ENUM_U32          cause;
    NAS_CC_DTMF_STATE_ENUM              enDtmfState = NAS_CC_GetDtmfState(entityId);

    if (NAS_CC_DTMF_S_START_REJ == enDtmfState)
    {
        NAS_CC_SendMnccMsg(entityId, MNCC_STOP_DTMF_CNF, VOS_NULL_PTR, 0);
        return;
    }

    /* �Ƿ���DTMF�������ڽ��� */
    if (enDtmfState != NAS_CC_DTMF_S_START_REQ)
    {
        if (enDtmfState != NAS_CC_DTMF_S_IDLE)
        {
            /* ����DTMF���� */
            NAS_CC_QueueDtmfReq(entityId,
                                NAS_CC_DTMF_STOP_REQ,
                                0);
            return;
        }

        if (NAS_CC_IsTchAvailable(NAS_CC_ITC_SPEECH))
        {
            NAS_CC_SendStopDtmf(ucTi);

            NAS_CC_StartTimer(entityId, TI_NAS_CC_T337, 0);
            NAS_CC_INFO_LOG("NAS_CC_ProcMnccStopDtmfReq ChangeDtmfState to STOP_REQ");
            NAS_CC_ChangeDtmfState(entityId, NAS_CC_DTMF_S_STOP_REQ);
        }
        else
        {
            cause = NAS_CC_CAUSE_111;
            NAS_CC_SendMnccMsg(entityId, MNCC_STOP_DTMF_CNF, &cause, sizeof(cause));
            NAS_CC_ERR_LOG("NAS_CC_ProcMnccStopDtmfReq: No appropriate channel.");
        }
    }
    else
    {
       /* ����DTMF���� */
        NAS_CC_QueueDtmfReq(entityId,
                            NAS_CC_DTMF_STOP_REQ,
                            0);
        return;
    }

}


/*****************************************************************************
 �� �� ��  : NAS_CC_ProcMnccModifyReq
 ��������  : ����MNCC_MODIFY_REQԭ��
 �������  : pstMsg      - �����ϲ��MNCCԭ����Ϣ
              entityId    - �����ԭ���CCʵ���ID
              ucTi        - CCʵ���Ӧ��transaction ID
              enCurrState - CCʵ�嵱ǰ�ĺ���״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccModifyReq(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    if (NAS_CC_CALL_STATE_U10 == enCurrState)
    {
        /* ��дmodify��Ϣͷ */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_MODIFY, &pstMsg->unParam.stModify.stHeader);

        /* ����modify��Ϣ */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stModify,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* ����MMCC_DATA_REQԭ�ｫ��Ϣ�������� */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_StartTimer(entityId, TI_NAS_CC_T323, 0);
        NAS_CC_INFO_LOG("NAS_CC_ProcMnccModifyReq ChangeCallState to U26");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U26);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccModifyReq: bad state.", enCurrState);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_ProcMnccModifyRes
 ��������  : ����MNCC_MODIFY_RESԭ��
 �������  : pstMsg      - �����ϲ��MNCCԭ����Ϣ
              entityId    - �����ԭ���CCʵ���ID
              ucTi        - CCʵ���Ӧ��transaction ID
              enCurrState - CCʵ�嵱ǰ�ĺ���״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccModifyRes(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    if (NAS_CC_CALL_STATE_U27 == enCurrState)
    {
        /* ��дmodify complete��Ϣͷ */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_MODIFY_COMPLETE, &pstMsg->unParam.stModifyRes.stHeader);

        /* ����modify complete��Ϣ */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stModifyRes,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* ����MMCC_DATA_REQԭ�ｫ��Ϣ�������� */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_INFO_LOG("NAS_CC_ProcMnccModifyRes ChangeCallState to U10");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U10);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccModifyRes: bad state.", enCurrState);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_ProcMnccModifyRej
 ��������  : ����MNCC_MODIFY_REJԭ��
 �������  : pstMsg      - �����ϲ��MNCCԭ����Ϣ
              entityId    - �����ԭ���CCʵ���ID
              ucTi        - CCʵ���Ӧ��transaction ID
              enCurrState - CCʵ�嵱ǰ�ĺ���״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��14��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ProcMnccModifyRej(
    MNCC_REQ_PRIM_MSG_STRU              *pstMsg,
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucTi,
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState
)
{
    if (NAS_CC_CALL_STATE_U27 == enCurrState)
    {
        /* ��дmodify reject��Ϣͷ */
        NAS_CC_FillAirMsgHeader(ucTi, NAS_CC_MSG_MODIFY_REJ, &pstMsg->unParam.stModifyRej.stHeader);

        /* ����modify reject��Ϣ */
        NAS_CC_EncodeMsg((NAS_CC_AIR_MSG_UNION *)&pstMsg->unParam.stModifyRej,
                         f_stCcEncodeBuf.aucBuf,
                         (VOS_UINT8 *)&f_stCcEncodeBuf.ulLen);

        /* ����MMCC_DATA_REQԭ�ｫ��Ϣ�������� */
        NAS_CC_SendMmccDataReq(ucTi, f_stCcEncodeBuf.aucBuf, f_stCcEncodeBuf.ulLen);

        NAS_CC_INFO_LOG("NAS_CC_ProcMnccModifyRej ChangeCallState to U10");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U10);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_ProcMnccModifyRej: bad state.", enCurrState);
    }
}
VOS_UINT32  NAS_CC_GetEntityId(
    MNCC_REQ_PRIM_MSG_STRU             *pstMsg,
    NAS_CC_ENTITY_ID_T                 *pulEntityId,
    VOS_UINT8                          *pucTi
)
{
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState;
    VOS_BOOL                            bIsCreateEntity;
    NAS_CC_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;
    NAS_CC_CALL_TYPE_ENUM_U8            enCallType;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = NAS_CC_GetCustomCfgInfo();


    /* ����SETUP��EMERGENCY SETUP������Ҫ�Ƚ���CCʵ�� */
    if ((pstMsg->enPrimName != MNCC_SETUP_REQ)
     && (pstMsg->enPrimName != MNCC_EMERG_SETUP_REQ))
    {
        if (MNCC_DISC_REQ == pstMsg->enPrimName)
        {
            *pulEntityId = NAS_CC_GetEntityByCallId(pstMsg->ucCallId);
            *pucTi       = NAS_CC_GetEntityTi(*pulEntityId);
        }
        else
        {
            *pucTi = pstMsg->ucTi;
            *pulEntityId = NAS_CC_GetEntityByTi(*pucTi);
        }
    }
    else
    {
        if ( MNCC_SETUP_REQ == pstMsg->enPrimName )
        {
            enCallType = NAS_CC_CALL_TYPE_MO_NORMAL_CALL;
        }
        else
        {
            enCallType = NAS_CC_CALL_TYPE_EMERGENCY_CALL;
        }

        if (NAS_CC_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
        {
            bIsCreateEntity = VOS_TRUE;
            *pucTi          = pstMsg->ucTi;
            bIsCreateEntity = NAS_CC_IsNeedCreateEntity(pstMsg->enPrimName, *pucTi, pulEntityId);
            enCurrState     = NAS_CC_CALL_STATE_U0;
            if (VOS_TRUE != bIsCreateEntity)
            {
                enCurrState = NAS_CC_GetCallState(*pulEntityId);
            }

            /* ȡ�õ�ǰ����״̬, ֻ����U0.6״̬�Ų���ҪcreateEntity */
            if (NAS_CC_CALL_STATE_U0_6 != enCurrState)
            {
                bIsCreateEntity = VOS_TRUE;
            }

            if (VOS_TRUE == bIsCreateEntity)
            {
                if (NAS_CC_CreateEntity(enCallType, pstMsg->ucCallId, NAS_CC_INVALID_TI_VALUE,
                                        pulEntityId) != VOS_OK)
                {
                    NAS_CC_ERR_LOG("NAS_CC_GetEntityId: Fail to create entity.");
                    return VOS_ERR;
                }

                *pucTi = NAS_CC_GetEntityTi(*pulEntityId);
            }
        }
        else
        {
            if (NAS_CC_CreateEntity(enCallType, pstMsg->ucCallId, NAS_CC_INVALID_TI_VALUE,
                                    pulEntityId) != VOS_OK)
            {
                NAS_CC_ERR_LOG("NAS_CC_GetEntityId: Fail to create entity.");
                return VOS_ERR;
            }

            *pucTi = NAS_CC_GetEntityTi(*pulEntityId);
        }
    }

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_IMS)


LOCAL VOS_VOID  NAS_CC_ProcMnccSrvccCallInfoNtf(
    MNCC_SRVCC_CALL_INFO_NOTIFY_STRU   *pstSrvccCallInfoNtf
)
{
    VOS_UINT8                           aucTi[MNCC_MAX_ENTITY_NUM];
    VOS_UINT8                           ucTiNum;

    PS_MEM_SET(aucTi, 0x00, sizeof(aucTi));

    /* ���SRVCC��������CALL NUMΪ0Ҳ��Ҫ֪ͨMMģ�� */
    /* ����CCʵ����Ϣ */
    NAS_CC_CreateCcEntityWithCallEntityInfo((VOS_VOID*)pstSrvccCallInfoNtf);

    /* ����֪ͨMMģ���TI������Ϣ */
    NAS_CC_GetEntityTiInfo(&ucTiNum, aucTi);

    /* ֪ͨMMģ��MMCC_SRVCC_CALL_INFO_NOTIFY��Ϣ */
    NAS_CC_SendMmccSrvccCallInfoNtf(ucTiNum, aucTi);


    return;
}
#endif



VOS_VOID NAS_CC_ProcMnccCallStatusNtf(
    MNCC_CALL_STATUS_NTY_STRU          *pstCallStatusNty
)
{
    /* ֪ͨMMģ��MMCC_CALL_STATUS_NTY��Ϣ */
    NAS_CC_SendMmccCallStatusNty(pstCallStatusNty->enCallStatus);

    return;

}


VOS_VOID  NAS_CC_ProcMnccPrimitive(VOS_VOID *pMsg)
{
    NAS_CC_ENTITY_ID_T                  ulEntityId;
    VOS_UINT8                           ucTi;
    NAS_CC_CALL_STATE_ENUM_U8           enCurrState;
    MNCC_REQ_PRIM_MSG_STRU             *pstMsg;
    NAS_CC_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = NAS_CC_GetCustomCfgInfo();


    pstMsg = (MNCC_REQ_PRIM_MSG_STRU *)pMsg;

    /*��ȡCCʵ��ID*/
    if (VOS_OK != NAS_CC_GetEntityId(pstMsg, &ulEntityId, &ucTi))
    {
        return;
    }

    /* ȡ�õ�ǰ����״̬ */
    enCurrState = NAS_CC_GetCallState(ulEntityId);
    if ( NAS_CC_CALL_STATE_BUTT == enCurrState )
    {
        NAS_CC_ERR_LOG("NAS_CC_GetCallState: NAS_CC_CALL_STATE_BUTT.");
    }

    NAS_CC_INFO_LOG4("NAS_CC_ProcMnccPrimitive: enPrimName, entityId, ucTi, enCurrState",
                      pstMsg->enPrimName, (VOS_INT32)ulEntityId, ucTi, enCurrState);

    /* ��MNCCԭ��ַ����������� */
    switch (pstMsg->enPrimName)
    {
        case MNCC_SETUP_REQ:
/*PC�طŵ���ȫ�ֱ���ʹ��*/
#ifndef __PS_WIN32_RECUR__
            NAS_CC_SndOutsideContextData();
#endif
            NAS_CC_ProcMnccSetupReq(pstMsg, ulEntityId, ucTi, enCurrState);

            break;

        case MNCC_EMERG_SETUP_REQ:
/*PC�طŵ���ȫ�ֱ���ʹ��*/
#ifndef __PS_WIN32_RECUR__
            NAS_CC_SndOutsideContextData();
#endif
            NAS_CC_ProcMnccEmergSetupReq(pstMsg, ulEntityId, ucTi, enCurrState);

            break;

        case MNCC_SETUP_RES:
            NAS_CC_ProcMnccSetupRsp(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_CALL_CONF_REQ:
            NAS_CC_ProcMnccCallConfReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_ALERT_REQ:
            NAS_CC_ProcMnccAlertReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_DISC_REQ:
            NAS_CC_ProcMnccDiscReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_REL_REQ:
            NAS_CC_ProcMnccRelReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_REJ_REQ:
            NAS_CC_ProcMnccRejReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_FACILITY_REQ:
            NAS_CC_ProcMnccFacilityReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_HOLD_REQ:
            NAS_CC_ProcMnccHoldReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_RETRIEVE_REQ:
            NAS_CC_ProcMnccRetrieveReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_START_DTMF_REQ:
            NAS_CC_ProcMnccStartDtmfReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_STOP_DTMF_REQ:
            NAS_CC_ProcMnccStopDtmfReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_MODIFY_REQ:
            NAS_CC_ProcMnccModifyReq(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_MODIFY_RES:
            NAS_CC_ProcMnccModifyRes(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_MODIFY_REJ_REQ:
            NAS_CC_ProcMnccModifyRej(pstMsg, ulEntityId, ucTi, enCurrState);
            break;

        case MNCC_EST_CNF_REQ:
             if (NAS_CC_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
             {
                 NAS_CC_ProcMnccCcEstCnfReq(pstMsg, ulEntityId, ucTi, enCurrState);
             }
             break;

#if (FEATURE_ON == FEATURE_IMS)
        case MNCC_SRVCC_CALL_INFO_NOTIFY:
            NAS_CC_ProcMnccSrvccCallInfoNtf((MNCC_SRVCC_CALL_INFO_NOTIFY_STRU *)(&pstMsg->unParam.stSrvccCallInfoNtf));
            break;
#endif

        case MNCC_CALL_STATUS_NTY:
            NAS_CC_ProcMnccCallStatusNtf((MNCC_CALL_STATUS_NTY_STRU *)(&pstMsg->unParam.stCallStatusNtf));
            break;

        default:
            NAS_CC_ERR_LOG1("NAS_CC_ProcMnccPrimitive: Unknown MNCC primitive.",
                        pstMsg->enPrimName);
            break;

    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_ActUus1Info
 ��������  : ����UUS1�����Ϣ�����UUS1��Ϣ
 �������  : enMsgType   :�輤�����Ϣ����
             pstUuieInfo :����UUIE����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��27��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_CC_ActUus1Info(
    NAS_CC_MSG_TYPE_ENUM_U8             enMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUuieInfo
)
{
    VOS_UINT32                          i;

    /* Ѱ�� �����б����ĸ���Ϣ��UUIE��Ϣ */
    for ( i = 0 ; i < NAS_CC_MAX_UUIE_MSG_NUM ; i++ )
    {
        if ( enMsgType == f_astUus1MsgBuf[i].enMsgType)
        {
            break;
        }
    }

    /* ����������Ѿ����ڸ���Ϣ,��ֱ����UUIE�����滻 */
    if ( i < NAS_CC_MAX_UUIE_MSG_NUM )
    {
        PS_MEM_CPY(&(f_astUus1MsgBuf[i].stUuieInfo),
                   pstUuieInfo,
                   sizeof(f_astUus1MsgBuf[i].stUuieInfo));

        return VOS_OK;
    }

    /* ��������в����ڸ���Ϣ,�����һ������λ�ô������Ϣ */
    for ( i = 0 ; i < NAS_CC_MAX_UUIE_MSG_NUM ; i++ )
    {
        if ( VOS_FALSE == f_astUus1MsgBuf[i].stUuieInfo.IsExist )
        {
            break;
        }
    }

    /* �ҵ�����λ��ֱ���滻 */
    if ( i < NAS_CC_MAX_UUIE_MSG_NUM )
    {
        f_astUus1MsgBuf[i].enMsgType = enMsgType;
        PS_MEM_CPY(&(f_astUus1MsgBuf[i].stUuieInfo),
                           pstUuieInfo,
                           sizeof(f_astUus1MsgBuf[i].stUuieInfo));

        return VOS_OK;
    }

    /* δ�ҵ�����λ��,���س���,ʵ���ϲ������ߵ��˴� */
    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_DeactUus1Info
 ��������  : ȥ����UUS1��Ϣ
 �������  : enMsgType   :�輤�����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��27��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_CC_DeactUus1Info(
    NAS_CC_MSG_TYPE_ENUM_U8             enMsgType
)
{
    VOS_UINT32                          i;

    /* Ѱ�� �����б����ĸ���Ϣ��UUIE��Ϣ */
    for ( i = 0 ; i < NAS_CC_MAX_UUIE_MSG_NUM ; i++ )
    {
        if ( enMsgType == f_astUus1MsgBuf[i].enMsgType)
        {
            break;
        }
    }

    /* ����������Ѿ����ڸ���Ϣ,��ֱ�����ø�ֵ�����ڷ��سɹ� */
    if ( i < NAS_CC_MAX_UUIE_MSG_NUM )
    {
        f_astUus1MsgBuf[i].stUuieInfo.IsExist = VOS_FALSE;
    }

    /* ��������в����ڸ���Ϣ,��ֱ�ӷ��سɹ�*/
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_GetMsgUus1Info
 ��������  : �жϸ�����Ϣ�Ƿ񼤻�UUS1��Ϣ
 �������  : entityId       :�����ԭ���CCʵ���ID
             enMsgType      :   ��Ϣ����
 �������  : pstUuieInfo    :   ����Ϣ��UUIE����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��27��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��4��10��
    ��    ��   : h00313353
    �޸�����   : SysCfg�ع�
*****************************************************************************/
VOS_VOID  NAS_CC_GetMsgUus1Info(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_MSG_TYPE_ENUM_U8             enMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUuieInfo
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrMode;
    VOS_UINT32                          i;
    NAS_CC_BC_PARAMS_STRU               stBcParams;

    PS_MEM_SET(pstUuieInfo,0x00,sizeof(NAS_CC_IE_USER_USER_STRU));

    /* ��֧��Gģ��UUS1����ʽ���� */
    enCurrMode = NAS_MML_GetCurrNetRatType();
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    if ( NAS_MML_NET_RAT_TYPE_GSM == enCurrMode )
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    {
        return;
    }

    /*  ��ȡ��ǰ�绰����,���������� */
    NAS_CC_GetBcParams(entityId, NAS_CC_BC_PARAM_CURR, &stBcParams);

    if ( ( NAS_CC_ITC_SPEECH != stBcParams.enItc )
      && ( NAS_CC_ITC_AUXILIARY_SPEECH != stBcParams.enItc ))
    {
        return;
    }

    /* �����б��и���Ϣ�Ƿ񼤻� */
    for ( i = 0 ; i < NAS_CC_MAX_UUIE_MSG_NUM ; i++ )
    {
        if ( ( enMsgType == f_astUus1MsgBuf[i].enMsgType)
          && (VOS_TRUE == f_astUus1MsgBuf[i].stUuieInfo.IsExist))
        {
            break;
        }
    }

    /* �������Ϣ�Ѿ������ȡUUIE��Ϣ */
    if ( i < NAS_CC_MAX_UUIE_MSG_NUM )
    {
        PS_MEM_CPY(pstUuieInfo,
                   &(f_astUus1MsgBuf[i].stUuieInfo),
                   sizeof(f_astUus1MsgBuf[i].stUuieInfo));
    }

    return;

}


/*****************************************************************************
 �� �� ��  : NAS_CC_GetAllUus1Info
 ��������  : ��ȡ���м���UUS1��Ϣ
 �������  : ��
 �������  : pulActNum      :�Ѽ���UUS1����
             pstUus1Info    :�Ѽ���UUS1�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��28��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_CC_GetAllUus1Info(
    VOS_UINT32                          *pulActNum,
    NAS_CC_UUS1_INFO_STRU               *pstUus1Info
)
{
    VOS_UINT32                          i;

    *pulActNum = 0;
    for ( i = 0 ; i < NAS_CC_MAX_UUIE_MSG_NUM ; i++ )
    {
        if ( VOS_TRUE == f_astUus1MsgBuf[i].stUuieInfo.IsExist )
        {
            (*pulActNum)++;
            pstUus1Info->enMsgType = f_astUus1MsgBuf[i].enMsgType;
            PS_MEM_CPY(&(pstUus1Info->stUuieInfo),
                       &(f_astUus1MsgBuf[i].stUuieInfo),
                       sizeof(f_astUus1MsgBuf[i].stUuieInfo));
            pstUus1Info++;
        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_CC_InitUus1Info
 ��������  : ��ʼ��UUS1��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��16��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_CC_InitUus1Info( VOS_VOID )
{
    VOS_UINT32                          i;

    PS_MEM_SET(f_astUus1MsgBuf, 0x00, sizeof(f_astUus1MsgBuf));

    /* ���UUIE��Ϣ */
    for ( i = 0 ; i < NAS_CC_MAX_UUIE_MSG_NUM ; i++ )
    {
        f_astUus1MsgBuf[i].stUuieInfo.IsExist = VOS_FALSE;
    }

    /* ��������в����ڸ���Ϣ,��ֱ�ӷ��سɹ�*/
    return;
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

