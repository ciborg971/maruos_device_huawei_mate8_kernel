

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmIden.h"
#include    "NasLmmPubMInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMIDEN_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMIDEN_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_EMM_IdenInit
 Discription    : IDENģ���ʼ������
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968 2008-10-16  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_IdenInit(VOS_VOID)
{
    /*IDENĿǰû����Ҫ��ʼ������Ϣ,��ʱΪ��*/

    return;
}
VOS_VOID  NAS_EMM_FreeIdenDyn( VOS_VOID )
{
    /*IDENĿǰΪ��*/

    return;
}
/*lint -e960*/
VOS_UINT32 NAS_EMM_AnyStateMsgIdenReq(VOS_UINT32  ulMsgId,
                                      VOS_VOID   *pMsgStru)
{

    NAS_EMM_IDEN_REQ_STRU              *pstIdenReqMsg;
    NAS_EMM_MRRC_DATA_REQ_STRU         *pstIdenRspMsg = NAS_EMM_NULL_PTR;
    VOS_UINT8                           ucIdenType;
    VOS_UINT32                          ulDataReqLenNoHeader;

    (VOS_VOID)ulMsgId;

    /*��ȡ�տ���Ϣ���ṹת�� */
    pstIdenReqMsg = (NAS_EMM_IDEN_REQ_STRU*)pMsgStru;
    ucIdenType    = pstIdenReqMsg->ucIdenType;

    /*����С��Ϣ���ȣ�������Ϣ�ڴ�,��Ҫ�ǿ��Ƿ�����пռ�*/
    pstIdenRspMsg = (NAS_EMM_MRRC_DATA_REQ_STRU *)NAS_LMM_MEM_ALLOC( \
                                                NAS_EMM_INTRA_MSG_MAX_SIZE);
    if(NAS_EMM_NULL_PTR == pstIdenRspMsg)
    {
        NAS_EMM_IDEN_ERROR_LOG("NAS_EMM_AnyStateMsgIdenReq: Alloc Msg Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AnyStateMsgIdenReq_ENUM,LNAS_NULL_PTR);
        return NAS_LMM_MSG_HANDLED;
    }

    /*���ݽ����������ȡ������������ʶ�����*/
    NAS_EMM_IdenTypeGet(ucIdenType, &(pstIdenRspMsg->stNasMsg));

    /*�ڲ���Ϣ���ȼ���*/
    ulDataReqLenNoHeader = NAS_EMM_CountMrrcDataReqLen( \
                                        pstIdenRspMsg->stNasMsg.ulNasMsgSize);

    if ( NAS_EMM_INTRA_MSG_MAX_SIZE < ulDataReqLenNoHeader )
    {
        /* ��ӡ������Ϣ */
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_AnyStateMsgIdenReq, Size error");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_AnyStateMsgIdenReq_ENUM,LNAS_ERROR);
        NAS_LMM_MEM_FREE(pstIdenRspMsg);
        return NAS_LMM_MSG_HANDLED;
    }

    /*���VOS��Ϣͷ,NAS_EMM_MRRC_DATA_REQ_STRU */
    NAS_EMM_INTRA_MSG_HEADER(pstIdenRspMsg, ulDataReqLenNoHeader);

    /*�����ϢID    */
    pstIdenRspMsg->ulMsgId              = ID_NAS_LMM_INTRA_MRRC_DATA_REQ;

    /*�����Ϣ����*/
    pstIdenRspMsg->enEstCaue            = LRRC_LNAS_EST_CAUSE_MO_SIGNALLING;
    pstIdenRspMsg->enCallType           = LRRC_LNAS_CALL_TYPE_ORIGINATING_SIGNALLING;
    pstIdenRspMsg->enEmmMsgType         = NAS_EMM_MSG_IDEN_RSP;

    pstIdenRspMsg->enDataCnf            = LRRC_LMM_DATA_CNF_NEED;

    /*�տ���Ϣ�ϱ� IDEN RSP*/
    /*lint -e961*/
    NAS_LMM_SendOmtAirMsg(NAS_EMM_OMT_AIR_MSG_UP, NAS_EMM_IDEN_RSP,  (NAS_MSG_STRU*)&(pstIdenRspMsg->stNasMsg));
    /*lint +e961*/

    /*�ؼ��¼��ϱ� IDEN RSP*/
    NAS_LMM_SendOmtKeyEvent(         EMM_OMT_KE_IDEN_RSP);

    /* ��MRRC����MRRC_DATA_REQ */
    NAS_EMM_SndUplinkNasMsg(             pstIdenRspMsg);

    NAS_LMM_MEM_FREE(pstIdenRspMsg);

    return NAS_LMM_MSG_HANDLED;
}
/*****************************************************************************
 Function Name  : NAS_EMM_CompCnIdenRsp
 Discription    : ��CN NAS��Ϣͷ��ֵ
 Input          : ��Ϣ
 Output         : None
 Return         : None
 History:
     1.   zangyalan 57968  2008-09-09  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_CompCnIdenRsp( LRRC_LNAS_MSG_STRU *pNasMsg)
{
    /*IDEN RSP��CN��Ϣͷ��ֵ*/
    pNasMsg->aucNasMsg[0]   = EMM_CN_MSG_PD_EMM;
    pNasMsg->aucNasMsg[0]  |= NAS_EMM_CN_MSG_SE_EMM;
    pNasMsg->aucNasMsg[1]   = NAS_EMM_CN_MT_IDEN_RSP;

    return;
}
VOS_UINT32  NAS_EMM_GetTmsiStatus(VOS_VOID)
{
    NAS_GUMM_INFO_STRU                  stGuInfo;
    stGuInfo.u.ulTmsiStatus           = MMC_LMM_TMSI_STATUS_INVALID;
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /* ��ȡTMSI״̬ʧ��*/
    if (MMC_LMM_FAIL == NAS_EMM_GetGuInfo(NAS_GUMM_TMSI_STATUS, &stGuInfo))
    {
        NAS_EMM_IDEN_NORMAL_LOG("NAS_EMM_GetTmsi: GetGuInfo FAIL .");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AnyStateMsgIdenReq_ENUM,LNAS_FAIL);
        return NAS_EMM_FAIL;
    }

    /* TMSI״̬��Ч*/
    if (MMC_LMM_TMSI_STATUS_INVALID == stGuInfo.u.ulTmsiStatus)
    {
        NAS_EMM_IDEN_NORMAL_LOG("NAS_EMM_GetTmsi: TMSI status invalid .");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_AnyStateMsgIdenReq_ENUM,LNAS_END);
        return NAS_EMM_FAIL;
    }

    /*PC REPLAY MODIFY BY LEILI END*/
    return NAS_EMM_SUCC;

}

/* lihong00150010 emergency tau&service begin */

VOS_VOID NAS_EMM_IdenImsi
(
    LRRC_LNAS_MSG_STRU                     *pNasMsg,
    VOS_UINT32                             *ulMsgLen
)
{
    /*����޿����߿���Ч���򷵻�NO IDENTITY*/
    if ((NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
        || (NAS_LMM_SIM_INVALID == NAS_LMM_GetPsSimValidity()))
    {
        /*No Identityʱ����Ϊ3���ֽ� */
        pNasMsg->aucNasMsg[2]         = NAS_EMM_NO_IDENTITY_LEN;
        pNasMsg->aucNasMsg[3]         = (NAS_EMM_ODD_BIT<<3) | (NAS_EMM_MOBILE_ID_NONE);

        *ulMsgLen += (NAS_EMM_NO_IDENTITY_LEN + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);

        return;
    }

    NAS_LMM_MEM_CPY(&pNasMsg->aucNasMsg[2],
                     &NAS_EMM_IDEN_IMSI_GLOBAL(0),
                     (NAS_EMM_IDEN_IMSI_GLOBAL(0) + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN));

    *ulMsgLen += (NAS_EMM_IDEN_IMSI_GLOBAL(0) + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);

    return;
}
/* lihong00150010 emergency tau&service end */

/*****************************************************************************
 Function Name  : NAS_EMM_IdenImei
 Discription    : ��ȡImei
 Input          : ��Ϣ
 Output         : None
 Return         : None
 History:
     1.   zangyalan 57968  2008-09-09  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_IdenImei(LRRC_LNAS_MSG_STRU *pNasMsg)
{

    NAS_LMM_MEM_CPY(&pNasMsg->aucNasMsg[2],
                    &NAS_EMM_IDEN_IMEI_GLOBAL(0),
                     NAS_EMM_IDEN_IMEI_GLOBAL(0) + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);

    return;
}
/*****************************************************************************
 Function Name  : NAS_EMM_IdenImeisv
 Discription    : ��ȡImeiSV
 Input          : ��Ϣ
 Output         : None
 Return         : None
 History:
     1.   zangyalan 57968  2008-09-09  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_IdenImeisv(LRRC_LNAS_MSG_STRU *pNasMsg)
{

    NAS_LMM_MEM_CPY(&pNasMsg->aucNasMsg[2],
                     &NAS_EMM_IDEN_IMEISV_GLOBAL(0),
                      NAS_EMM_IDEN_IMEISV_GLOBAL(0) + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);

    return;
}

VOS_VOID  NAS_EMM_EncodeTmsi
(
    LRRC_LNAS_MSG_STRU  *pNasMsg,
    VOS_UINT32          *ulMsgLen
)
{
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30 ,begin */
    VOS_UINT8 *pucTmsi  = VOS_NULL_PTR;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30 ,end */

    NAS_EMM_IDEN_INFO_LOG("NAS_EMM_EncodeTmsi   is  entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeTmsi_ENUM,LNAS_ENTRY);

    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30 ,begin */
    pucTmsi  = NAS_EMM_GetUeIdTmsi();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30 ,end */

    /* �����ȡTMSIʧ�ܻ���TMSI��Ч */
    if(NAS_EMM_FAIL ==  NAS_EMM_GetTmsiStatus())
    {
        /*No Identityʱ����Ϊ3���ֽ� */
        pNasMsg->aucNasMsg[2]         = NAS_EMM_NO_IDENTITY_LEN;
        pNasMsg->aucNasMsg[3]         = (NAS_EMM_ODD_BIT<<3) | (NAS_EMM_MOBILE_ID_NONE);

        *ulMsgLen += (NAS_EMM_NO_IDENTITY_LEN + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);
    }
    else
    {
        /* ��ȡTMSI�ɹ�����Ч */
        /* ���� */
        pNasMsg->aucNasMsg[2]         = NAS_EMM_TMSI_LEN;

        /* Identity digit 1 | O/D | Type of identity ��ռ1���ֽ� */
        /* 24008,  10.5.1.4��:
              if the mobile identity is TMSI/P-TMSI/M-TMSI,
              then bit5 to bit8 of octet 3 are code as "1111" */
        pNasMsg->aucNasMsg[3]         = ((NAS_EMM_EVEN_BIT<<3) | (NAS_EMM_MOBILE_ID_TMSI))|0xF0;

        /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30 ,begin */
        /* ����TMSI��ֵ������Ϊ4�ֽ� */
        NAS_LMM_MEM_CPY(&pNasMsg->aucNasMsg[4],
                       pucTmsi,
                       NAS_EMM_TMSI_LEN -1);    //lint !e419 !e826 !e950
        /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30 ,end */

        *ulMsgLen += (NAS_EMM_TMSI_LEN + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);

         /* ��ӡ��ȡ����TMSIֵ */
        NAS_EMM_IDEN_NORMAL_LOG("NAS_EMM_GetTmsi: TMSI value is :");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_EncodeTmsi_ENUM,LNAS_EMM_TMSI_NUMBER);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30 ,begin */
        NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                       pucTmsi,
                       NAS_EMM_TMSI_LEN -1);
        /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30 ,end */
    }

    return;

}
/*lint +e960*/

VOS_VOID NAS_EMM_IdenTypeGet(VOS_UINT8 ucIdenType, LRRC_LNAS_MSG_STRU *pNasMsg)
{
    VOS_UINT32              ulIndex         = 0;
    LRRC_LNAS_MSG_STRU       *pTempNasMsg     =pNasMsg;

    pTempNasMsg->aucNasMsg[ulIndex]     = EMM_CN_MSG_PD_EMM;
    pTempNasMsg->aucNasMsg[ulIndex++]  |= NAS_EMM_CN_MSG_SE_EMM;
    pTempNasMsg->aucNasMsg[ulIndex++]   = NAS_EMM_CN_MT_IDEN_RSP;

    /* lihong00150010 emergency tau&service begin */
    switch (ucIdenType)
    {
        case    NAS_EMM_MOBILE_ID_IMSI:           /*��ȡIMSI*/
                NAS_EMM_IdenImsi(pTempNasMsg, &ulIndex);

                break;

        case    NAS_EMM_MOBILE_ID_IMEI:           /*��ȡIMEI*/
                NAS_EMM_IdenImei(pTempNasMsg);

                ulIndex += (NAS_EMM_IMEI_LEN + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);
                break;

        case    NAS_EMM_MOBILE_ID_IMEISV:         /*��ȡIMEISV*/
                NAS_EMM_IdenImeisv(pTempNasMsg);

                ulIndex += (NAS_EMM_IMEISV_LEN + NAS_EMM_MOBILE_IDENTITY_CONTENTS_LEN);
                break;

        case    NAS_EMM_MOBILE_ID_TMSI:           /*��ȡTMSI*/
                NAS_EMM_EncodeTmsi(pTempNasMsg, &ulIndex);

                break;

        default:
                NAS_EMM_IdenImsi(pTempNasMsg, &ulIndex);       /*others��ΪIMSI����*/

                break;
    }

    pTempNasMsg->ulNasMsgSize = ulIndex;
    /* lihong00150010 emergency tau&service end */
    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

/* end of ��ϵͳ+ģ��+�ļ���.c */
