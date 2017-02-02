


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEmmPubUInclude.h"
#ifdef PS_ITT_PC_TEST_NAS
#include    "NasEmmLppMsgProc.h"
#endif
/*lint -e766*/
/*#include "TlPsDrv.h"*/
/*end*/
/*lint +e766*/

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMPUBUCNMSGDECODE_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMPUBUCNMSGDECODE_C
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


NAS_EMM_DECODE_MSG_IE_INFO_STRU  g_astCnTauAcpIEList[] =
{
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_T3412_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_GUTI_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_TAI_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_EPSBTXT_STUS_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_LAI_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_MSID_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_EMMCAU_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_AUCRESERVE_IE_ITEM(3),NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_T3402_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_T3423_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_PLMNLIST_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_EMERGENCYLIST_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_EPSNETFEATURE_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_AUCRESERVE_IE_ITEM(3),NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_UPDTAERSLT_IE_ITEM,NAS_EMM_DECODE_IE_O)

};
NAS_EMM_DECODE_MSG_IE_INFO_STRU  g_astCnAttachAcpIEList[] =
{
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_GUTI_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_LAI_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_MSID_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_EMMCAU_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_AUCRESERVE_IE_ITEM(3),NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_T3402_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_T3423_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_PLMNLIST_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_EMERGENCYLIST_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_EPSNETFEATURE_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_AUCRESERVE_IE_ITEM(3),NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_UPDTAERSLT_IE_ITEM,NAS_EMM_DECODE_IE_O)

};

NAS_EMM_DECODE_MSG_IE_INFO_STRU  g_astCnAttachRejIEList[] =
{
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_ESMMSGCON_IE_ITEM,NAS_EMM_DECODE_IE_O),
    NAS_EMM_DECODE_MSG_IE_ITEM(NAS_EMM_MSG_T3402_2_IE_ITEM,NAS_EMM_DECODE_IE_O)
};

/*�������ܻ�ʹ�ã��ݱ���,��ע�͵�*/
/*NAS_EMM_DECODE_MSG_INFO_STRU g_astCnMsgList[] =
{
    NAS_EMM_DECODE_MSG_ITEM(NAS_EMM_CN_MT_ATTACH_ACP,g_astCnAttachAcpIEList,NAS_EMM_CN_ATTACH_ACP_STR),
    NAS_EMM_DECODE_MSG_ITEM(NAS_EMM_CN_MT_TAU_ACP,g_astCnTauAcpIEList,NAS_EMM_CN_TAU_ACP_STR)
};*/

NAS_EMM_DECODE_MSG_FUNS_STRU g_astEmmCnMsgFuns[] =
{
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_ATTACH_ACP,NAS_EMM_DecodeCnAttachAcpMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_ATTACH_REJ,NAS_EMM_DecodeCnAttachRejMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_DETACH_REQ_MT,NAS_EMM_DecodeCnDetachReqMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_DETACH_ACP_MO,NAS_EMM_DecodeCnDetachAcpMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_GUTI_CMD,NAS_EMM_DecodeCnGUTICmdMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_IDEN_REQ,NAS_EMM_DecodeCnIdenReqMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_SER_REJ,NAS_EMM_DecodeCnSerRejMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_TAU_ACP,NAS_EMM_DecodeCnTAUAcpMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_TAU_REJ,NAS_EMM_DecodeCnTAURejMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_AUTH_REQ,NAS_EMM_DecodeCnAuthReqMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_AUTH_REJ,NAS_EMM_DecodeCnAuthRejMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_SMC_CMD,NAS_EMM_DecodeCnSecurModeCtrlMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_EMM_INFO,NAS_EMM_DecodeCnEmmInfoMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_EMM_STATUS,NAS_EMM_DecodeCnEmmStatusMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_DOWNLINK_NAS_TRANSPORT,NAS_EMM_DecodeCnDownlinkNasTransportMsg),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_CS_SER_NOTIFICATION,NAS_EMM_DecodeCnCsSerNotification),
    NAS_EMM_DECODE_MSG_FUN_ITEM(NAS_EMM_CN_MT_DOWNLINK_GENERIC_NAS_TRANSPORT,NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg)
};
VOS_UINT32 g_ulSizeof_g_astEmmCnMsgFuns = sizeof(g_astEmmCnMsgFuns);

/*zhuyqEncode*/
/*
NAS_EMM_CN_MSGCON_STRU                  g_stAirMsgEncode;
*/

/*****************************************************************************
  3 Function
*****************************************************************************/

/*lint -e72*/
/*lint -e960*/
/*lint -e961*/
VOS_UINT32  NAS_EMM_DecodeCnMsg( MsgBlock        *pOsaMsg,
                                    NAS_EMM_CN_MSG_STRU      *pstCnMsgStru)/*lint  -e818*/
{
    VOS_UINT8                           *pRcvMsg            = NAS_EMM_NULL_PTR;
    VOS_UINT32                           ulIndex            = NAS_EMM_NULL;
    VOS_UINT32                           ulRslt             = NAS_EMM_NULL;
    LRRC_LMM_DATA_IND_STRU                *pstTmpRcvMsg       = NAS_EMM_NULL_PTR;
    LRRC_LNAS_MSG_STRU                    *pstNasRcvMsg       = NAS_EMM_NULL_PTR;
    VOS_UINT8                            ucPD               = NAS_EMM_NULL;
    VOS_UINT8                            ucSecHeadTp        = NAS_EMM_NULL;
    VOS_UINT8                            ucMsgType          = NAS_EMM_NULL;
    NAS_EMM_DECODE_CN_MSG_HEADER_STRU    *pstCnMsgHeaer     = \
                                        (NAS_EMM_DECODE_CN_MSG_HEADER_STRU *)pstCnMsgStru;
    VOS_UINT32                           i                  = 0;
    VOS_UINT32                           ulMsgNum           = g_ulSizeof_g_astEmmCnMsgFuns/
                                                            sizeof(NAS_EMM_DECODE_MSG_FUNS_STRU);

    /* �ж���ڲ����Ƿ�Ϸ�*/
    if( NAS_EMM_NULL_PTR == pOsaMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnMsg:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnMsg_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /*�ṹ����Ϣ��ȡ����Ϣ��*/
    pstTmpRcvMsg = (LRRC_LMM_DATA_IND_STRU*)pOsaMsg;
    pstNasRcvMsg = &(pstTmpRcvMsg->stNasMsg);
    pRcvMsg      = pstTmpRcvMsg->stNasMsg.aucNasMsg;

    /*ȡ��PD*/
    ucPD = pRcvMsg[ulIndex]& EMM_CN_MSG_PDMASK;

    /*�ж�PD�Ƿ����Э��Ҫ��GMM��ϢΪ0x07*/
    if(EMM_CN_MSG_PD_EMM != ucPD)
    {
        /* �׳���ά�ɲ� */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_PD_IE, EMM_CN_MSG_PD_INVALID, ucPD);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnMsg:WARNING:NAS->EMM MSG PD is wrong");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnMsg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }
    /*ȡ��Security header type*/
    ucSecHeadTp = (VOS_UINT8)((pRcvMsg[ulIndex]& NAS_EMM_HIGH_HALF_BYTE_F)
                >>NAS_EMM_MOVEMENT_4_BITS);

    /*�ж�Security header type�Ƿ����Э��*/
    if((ucSecHeadTp > NAS_EMM_MSG_SEC_TYPE_NAS)
        &&(ucSecHeadTp < NAS_EMM_MSG_SEC_TYPE_SERREQ))
    {
        /* �׳���ά�ɲ� */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_SEC_HEAD_TYPE_IE, EMM_CN_MSG_SEC_HEAD_TYPE_INVALID, ucSecHeadTp);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnMsg:WARNING:NAS->EMM MSG Security header type is wrong");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnMsg_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }
    if(ucSecHeadTp > NAS_EMM_MSG_SEC_TYPE_SERREQ)
    {
        ucSecHeadTp = NAS_EMM_MSG_SEC_TYPE_SERREQ;
    }

    /*����PD��Security header type*/
    ulIndex++;

    /*��2���ֽ�Ϊ��Ϣ���ͣ�ȡ��*/
    ucMsgType = pRcvMsg[ulIndex];

    pstCnMsgHeaer->ucPd = ucPD;
    pstCnMsgHeaer->ucSecurityHeadType = ucSecHeadTp;
    pstCnMsgHeaer->ucMt = ucMsgType;

    for(i = 0;i < ulMsgNum;i++)
    {
        if(g_astEmmCnMsgFuns[i].enMsgTp == ucMsgType)
        {
            break;
        }
    }

    if(i >= ulMsgNum)
    {
        /* �׳���ά�ɲ� */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_MSG_TYPE_IE, EMM_CN_MSG_MSG_TYPE_INVALID, ucMsgType);
        /*��ӡ������Ϣ*/
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnMsg:WARNING:NAS->EMM MSG Type not assigned ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnMsg_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_FAIL;
    }
    if(NAS_EMM_NULL_PTR != g_astEmmCnMsgFuns[i].pDecodeMsgFun)
    {
        ulRslt = g_astEmmCnMsgFuns[i].pDecodeMsgFun(pstNasRcvMsg, ulIndex, pstCnMsgStru);
    }
    else
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsg:g_astEmmCnMsgFuns[i].pDecodeMsgFun is null ");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    return ulRslt;
}
VOS_VOID  NAS_EMM_DecodeCnMsgIEOptListCalcLen
(
    VOS_UINT8                                   *pTmpRcvMsg,
    NAS_EMM_DECODE_IE_INFO_STRU                 stIEInfo,
    VOS_UINT32                                  *pulIndexNoIEI,
    VOS_UINT32                                  *pulIELen,
    VOS_UINT32                                  *pulIndex
)
{
    VOS_UINT32      ulIndexNoIEI      = *pulIndexNoIEI;          /*��Ԫ(��ȥIEI)��λ��      */
    VOS_UINT32      ulIELen           = NAS_EMM_NULL;          /*��Ԫ����                 */

    /*�����а���L��ʱ�򣬳�����Ҫ���¼������*/
    if(NAS_EMM_DECODE_IE_FORMAT_L== \
                (NAS_EMM_DECODE_IE_FORMAT_L&stIEInfo.ucIEFormat))
    {
        if (NAS_RELEASE_R11)
        {
            /* �����ѡ��Ԫ�ĸ�ʽ��TLV_E����LV_E��L��ռ�������ֽ� */
            if ((NAS_EMM_DECODE_IE_FORMAT_TLV_E == stIEInfo.ucIEFormat) ||
                (NAS_EMM_DECODE_IE_FORMAT_LV_E == stIEInfo.ucIEFormat))
            {
                ulIELen = (pTmpRcvMsg[(*pulIndex)+ \
                              ((NAS_EMM_DECODE_IE_FORMAT_T&stIEInfo.ucIEFormat)/ \
                              NAS_EMM_DECODE_IE_FORMAT_T)]<< NAS_EMM_MOVEMENT_8_BITS)
                            | pTmpRcvMsg[(*pulIndex)+ \
                                          ((NAS_EMM_DECODE_IE_FORMAT_T&stIEInfo.ucIEFormat)/ \
                                          NAS_EMM_DECODE_IE_FORMAT_T) + 1];

                /* ����L������ֽ� */
                ulIELen = ulIELen + 2;
                /*����IEI���ֽ�, (ulIndexNoIEI - ulIndex) ΪIEI���ֽ�*/
                ulIELen = ulIELen + (ulIndexNoIEI - (*pulIndex));
            }
            else
            {
                /*����L��λ��ȡ�ó���,����Ĭ��L���������ֽ���,������������ȡ*/
                ulIELen = pTmpRcvMsg[(*pulIndex)+ \
                          ((NAS_EMM_DECODE_IE_FORMAT_T&stIEInfo.ucIEFormat)/ \
                          NAS_EMM_DECODE_IE_FORMAT_T)];

                /*����L�����ֽ�*/
                ulIELen++;
                /*����IEI���ֽ�, (ulIndexNoIEI - ulIndex) ΪIEI���ֽ�*/
                ulIELen = ulIELen + (ulIndexNoIEI - (*pulIndex));
            }
        }
        else
        {
            /*����L��λ��ȡ�ó���,����Ĭ��L���������ֽ���,������������ȡ*/
            ulIELen = pTmpRcvMsg[(*pulIndex)+ \
                      ((NAS_EMM_DECODE_IE_FORMAT_T&stIEInfo.ucIEFormat)/ \
                      NAS_EMM_DECODE_IE_FORMAT_T)];

            /*����L�����ֽ�*/
            ulIELen++;
            /*����IEI���ֽ�, (ulIndexNoIEI - ulIndex) ΪIEI���ֽ�*/
            ulIELen = ulIELen + (ulIndexNoIEI - (*pulIndex));
        }
        *pulIELen += ulIELen;
    }

}


VOS_UINT32  NAS_EMM_DecodeCnMsgIEOptList(
                                            NAS_EMM_DECODE_IELIST_PARA_STRU *pstIEOptParaList,
                                            VOS_UINT32  *pulSum
                                          )
{
    /*��������������Ķ���             */
    VOS_UINT8                           *pTmpRcvMsg;
    VOS_UINT32                          *pTmpCnMsgOpt;
    VOS_UINT32                          ulTmpOptPos;
    VOS_VOID                            *pstCnMsgStruIE;
    NAS_EMM_DECODE_MSG_IE_INFO_STRU     *pstMsgIETable;

    /*����Ϊ���������Ķ��弰��ʼ��     */
    VOS_UINT32      ulIESum           = NAS_EMM_NULL;          /*������Ԫ��������         */
    VOS_UINT32      ulOptBit          = NAS_EMM_BIT_SLCT;      /*��ѡ��bitλ��Ӧ����ֵ    */
    VOS_UINT32      ulIndex           = NAS_EMM_NULL;          /*��¼��ǰ��Ԫ�Ŀ�ʼλ��   */
    VOS_UINT32      ulIndexNoIEI      = NAS_EMM_NULL;          /*��Ԫ(��ȥIEI)��λ��      */
    VOS_UINT32      ulIELen           = NAS_EMM_NULL;          /*��Ԫ����                 */
    VOS_UINT32      ulIEI             = NAS_EMM_NULL;          /*��Ԫ���ͱ���             */
    VOS_UINT32      ulRslt            = NAS_EMM_FAIL;
    VOS_UINT32      i                 = NAS_EMM_NULL;
    VOS_UINT32      ulDecodedIE       = NAS_EMM_NULL;
    VOS_UINT32      ulDecodingIE      = NAS_EMM_BIT_SLCT;

    /* �ж���������Ƿ�Ϸ�*/
    ulRslt = NAS_EMM_DecodeCnMsgIEOptListParaChk(pstIEOptParaList);
    if( NAS_EMM_FAIL == ulRslt)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEList:ERROR: some input pointer is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptList_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }
    /*�������Ĳ�����ʼ��*/
    pTmpRcvMsg          = pstIEOptParaList->pRcvMsg;
    pTmpCnMsgOpt        = pstIEOptParaList->pCnMsgOpt;
    *pulSum             = NAS_EMM_NULL;

    /*ѭ��������Ԫ*/
    while(ulIndex < pstIEOptParaList->ulLength)
    {
        ulIESum         = NAS_EMM_NULL;
        pstMsgIETable   = pstIEOptParaList->pstCnMsgInfo->pastMsgIETable;
        pstCnMsgStruIE  = pstIEOptParaList->pstCnMsgStru;
        ulIndexNoIEI    = ulIndex;
        ulTmpOptPos     = pstIEOptParaList->ulOptPos;
        ulDecodingIE    = pstIEOptParaList->ulOptPos;/*��¼���ڽ����Ԫ */

        /*ѭ������Ԫ��Ϣ���в���ƥ����*/
        for (i = 0; i < pstIEOptParaList->pstCnMsgInfo->ucMsgIETableSize; i++)
        {
             /*�����Ԫ������*/
            ulIEI = pTmpRcvMsg[ulIndex] & pstMsgIETable->stIEInfo.ucIEBits;
            ulIEI = ulIEI >> pstMsgIETable->stIEInfo.ucIEBitsMove;

            if(pstMsgIETable->stIEInfo.ucIEI != ulIEI)
            {
                /*�ṹ��ָ�롢��Ԫ�б���ѡ��λ��ƽ��*/
                pstCnMsgStruIE = (VOS_UINT8 *)pstCnMsgStruIE
                                         + pstMsgIETable->stIEInfo.usIEStructSize;
                pstMsgIETable++;
                ulTmpOptPos++;
                ulDecodingIE = ulDecodingIE << 1;
                continue;
            }

            break;
        }
        /*�޷�ʶ���յ���NAS��Ϣ�е���Ԫ,Ҳ�޷�֪�����������ĳ���,��ѡ��Ԫ��Ӱ��
          ��������,���տ���ϳ�ԭ��,������ʱ���ս���ɹ����� */
        if (i >= pstIEOptParaList->pstCnMsgInfo->ucMsgIETableSize)
        {
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnMsgIEList:(WARN): some Option IEI in Msg is not exist!");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnMsgIEOptList_ENUM,LNAS_FUNCTION_LABEL1);
            return NAS_EMM_SUCC;
        }

        /*�����ȥIEI���λ��,������Ԫ����*/
        /*lint -e961*/
        ulIndexNoIEI = ulIndexNoIEI + pstMsgIETable->stIEInfo.ucIEBits/NAS_EMM_DECODE_OCTET_USE_8_BITS;
        /*lint +961*/
        ulIELen      = pstMsgIETable->stIEInfo.ucIELen;

        /*�����а���L��ʱ�򣬳�����Ҫ���¼������*/
        NAS_EMM_DecodeCnMsgIEOptListCalcLen(pTmpRcvMsg,pstMsgIETable->stIEInfo,&ulIndexNoIEI,&ulIELen,&ulIndex);


        /*�����������,���سɹ�����ԭ����һ��*/
        if(pstIEOptParaList->ulLength < (ulIndex + ulIELen))
        {
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnMsgIEList:WARN: exceed length!");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnMsgIEOptList_ENUM,LNAS_FUNCTION_LABEL2);
            return NAS_EMM_SUCC;
        }

        /*(1)��麯��ָ���Ƿ����,���������,��������*/
        /*(2)�Լ��������Ԫ֮ǰû�⵽��,��ִ�н��룬�������� */
        if ((NAS_EMM_NULL != pstMsgIETable->stIEInfo.pfIEDecodeFun)
            && ((ulDecodingIE | ulDecodedIE) != ulDecodedIE))
        {

            ulRslt = pstMsgIETable->stIEInfo.pfIEDecodeFun(pTmpRcvMsg+ulIndexNoIEI,
                                                            &ulIESum,
                                                            pstCnMsgStruIE,
                                                            pstIEOptParaList->pstCnMsgInfo->ucMsgType
                                                           );
            if(NAS_EMM_FAIL == ulRslt)
            {
                /* ��ѡ��Ԫ����ʧ�ܣ����ǲ��Կ�ʱ�����ؽ���ʧ�ܣ������տ���ϳ�ԭ�������ÿ�ѡ��Ԫ����������ʣ����Ԫ */
                if(PS_SUCC == LPS_OM_IsTestMode())
                {
                    NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEList:(ERROR): IE content error");
                    TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptList_ENUM,LNAS_ERROR);
                    return NAS_EMM_FAIL;
                }
                else
                {
                    /*������Ԫ */
                    ulIESum = ulIELen;
                    /*����ƽ��*/
                    ulIndex += ulIESum;
                    /*�������ܳ��� */
                    *pulSum = ulIndex;
                    continue;
                }
            }

            /*��д��־λ��δ��д��Ĭ��ΪNAS_EMM_BIT_NO_SLCT*/
            ulOptBit = NAS_EMM_BIT_SLCT;

            /*��¼�ѽ���Ԫ */
            ulDecodedIE |= (ulOptBit << (ulTmpOptPos - 1));

            NAS_EMM_DecodeCnMsgIEEdianChk(&ulTmpOptPos,NAS_EMM_MSG_IE_OPT_BITS);
            ulOptBit = NAS_EMM_BIT_SLCT;
            ulOptBit = ulOptBit << ulTmpOptPos;
            *pTmpCnMsgOpt = *pTmpCnMsgOpt | ulOptBit;

            /*����ƽ��*/
            ulIndex = ulIndexNoIEI + ulIESum;

        }
        else
        {
            /*������Ԫ */
            ulIESum = ulIELen;

            /*����ƽ��*/
            ulIndex += ulIESum;

        }
        /*�������ܳ��� */
        *pulSum = ulIndex;
    }

    return NAS_EMM_SUCC;
}
VOS_UINT32 NAS_EMM_DecodeCnMsgIEOptListParaChk(
                           NAS_EMM_DECODE_IELIST_PARA_STRU *pstIEOptParaList
                                                                   )
{
    VOS_UINT32 ulRslt;
    ulRslt = NAS_EMM_FAIL;
    if(NAS_EMM_NULL_PTR == pstIEOptParaList)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEOptListParaChk:ERROR: pstIEOptParaList is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptListParaChk_ENUM,LNAS_NULL_PTR);
        return ulRslt;
    }
    if(NAS_EMM_NULL_PTR == pstIEOptParaList->pRcvMsg)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEOptListParaChk:ERROR: pstIEOptParaList->pRcvMsg is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptListParaChk_ENUM,LNAS_FUNCTION_LABEL1);
        return ulRslt;
    }
    if(NAS_EMM_NULL_PTR == pstIEOptParaList->pCnMsgOpt)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEOptListParaChk:ERROR: pstIEOptParaList->pCnMsgOpt is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptListParaChk_ENUM,LNAS_FUNCTION_LABEL2);
        return ulRslt;
    }
    if(NAS_EMM_NULL_PTR == pstIEOptParaList->pstCnMsgStru)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEOptListParaChk:ERROR: pstIEOptParaList->pstCnMsgStru is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptListParaChk_ENUM,LNAS_FUNCTION_LABEL3);
        return ulRslt;
    }
    if(NAS_EMM_NULL_PTR == pstIEOptParaList->pstCnMsgInfo)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEOptListParaChk:ERROR: pstIEOptParaList->pstCnMsgInfo is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptListParaChk_ENUM,LNAS_FUNCTION_LABEL4);
        return ulRslt;
    }
    if(NAS_EMM_NULL_PTR == pstIEOptParaList->pstCnMsgInfo->pastMsgIETable)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnMsgIEOptListParaChk:ERROR: pstIEOptParaList->pstCnMsgInfo->pastMsgIETable is null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnMsgIEOptListParaChk_ENUM,LNAS_FUNCTION_LABEL5);
        return ulRslt;
    }
    ulRslt = NAS_EMM_SUCC;
    return ulRslt;

}

VOS_VOID  NAS_EMM_DecodeCnMsgIEEdianChk(

                                            VOS_UINT32  *pulOptpos,
                                            VOS_UINT8   ucOptbits
                                          )
{
    if(PS_TRUE == NAS_EMM_DecodeIsLittleEdian())
    {
        *pulOptpos = ((*pulOptpos - NAS_EMM_AD_MOVEMENT_1_BIT) % ucOptbits);
    }
    else
    {
        *pulOptpos = (ucOptbits - (*pulOptpos% ucOptbits)) ;
    }
}

VOS_UINT32 NAS_EMM_DecodeIsLittleEdian(VOS_VOID)
{
    NAS_EMM_DECODE_EDIAN_UION unNasEdian;
    unNasEdian.ulMember = 1;
    if(1 == unNasEdian.aucMember[0])
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }
}


NAS_EMM_CN_CAUSE_ENUM_UINT8  NAS_EMM_DecodeCnEmmCause(VOS_UINT8  ucEMMCau)
{
    if (   ((NAS_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS <= ucEMMCau) && (ucEMMCau <= NAS_LMM_CAUSE_ILLEGAL_UE))
        || ((NAS_LMM_CAUSE_IMEI_NOT_ACCEPTED <= ucEMMCau) && (ucEMMCau <= NAS_LMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED))
        || ((NAS_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG <= ucEMMCau) && (ucEMMCau <= NAS_LMM_CAUSE_MSG_NOT_COMPATIBLE))
        || (NAS_LMM_CAUSE_SERVER_NETWORK_FAILURE == ucEMMCau))
    {
        /* xiongxianghui00253310 modify for ftmerrlog begin */
        #if (FEATURE_PTM == FEATURE_ON)
        NAS_EMM_GetFtmInfoCnRej() = ucEMMCau;
        #endif
        /* xiongxianghui00253310 modify for ftmerrlog end   */

        return ucEMMCau;
    }
    else
    {
        /* xiongxianghui00253310 modify for ftmerrlog begin */
        #if (FEATURE_PTM == FEATURE_ON)
        NAS_EMM_GetFtmInfoCnRej() = NAS_LMM_CAUSE_PROTOCOL_ERROR;
        #endif
        /* xiongxianghui00253310 modify for ftmerrlog end   */

        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_DecodeCnEmmCause: The CnEmmCause is undefine in protocol 24301 !  ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnEmmCause_ENUM,LNAS_NO_CAUSE);
        return NAS_LMM_CAUSE_PROTOCOL_ERROR;
    }

}




VOS_UINT32  NAS_EMM_DecodeCnAttachAcpMsgNasMsg(
                                        LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                        VOS_UINT8                  *pucRcvCnNasMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT8                           ucEPSAttRslt        = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;
    NAS_EMM_DECODE_IELIST_PARA_STRU     stIEOptParaList={NAS_EMM_NULL};
    NAS_EMM_DECODE_MSG_INFO_STRU        stCnAttachAcp = \
                                        NAS_EMM_DECODE_MSG_ITEM(NAS_EMM_CN_MT_ATTACH_ACP,\
                                                                g_astCnAttachAcpIEList,\
                                                                NAS_EMM_CN_ATTACH_ACP_STR);

    NAS_LMM_MEM_SET(&stIEOptParaList, 0, sizeof(NAS_EMM_DECODE_IELIST_PARA_STRU));

    ulMsgSize  = pRcvMsg->ulNasMsgSize;
    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*������Ϣ����*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*������Ϣ����*/
    ulIndex++;

    /*ȡ��EPS attach result*/
    ucEPSAttRslt = (pTmpRcvMsg[ulIndex] & NAS_EMM_LOW_HALF_BYTE_F);

    /*�ж�EPS attach result�Ƿ����Э��Ҫ��*/
    if((VOS_NULL != ucEPSAttRslt)&&(ucEPSAttRslt <= NAS_EMM_CN_ATT_RST_VAL_MAX))
    {
        pstCnMsgStruIE->uCnMsgStru.stAttAcp.ucAttachRst = ucEPSAttRslt;
    }
    else
    {
        /* �׳���ά�ɲ� */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_ATTRSLT_IE, EMM_CN_MSG_IE_ATTRSLT_INVALID, ucEPSAttRslt);
        /*��ӡ������Ϣ*/
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnAttachAcpMsg:WARNING:NAS->EMM MSG AttachRst not assigned ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnAttachAcpMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*����EPS attach result*/
    ulIndex++;

    (VOS_VOID)NAS_EMM_DecodeTimer((pTmpRcvMsg+ulIndex),
                                 &ulSum,
                                 &(pstCnMsgStruIE->uCnMsgStru.stAttAcp.stT3412Value),
                                 NAS_EMM_CN_MT_BUTT);

    ulIndex = ulIndex + ulSum;

    /*��������0*/
    ulSum = NAS_EMM_NULL;

    if(NAS_EMM_FAIL == NAS_EMM_DecodeTai((pTmpRcvMsg+ulIndex),
                                         &ulSum,
                                         &(pstCnMsgStruIE->uCnMsgStru.stAttAcp.stTaiList),
                                         NAS_EMM_CN_MT_BUTT))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnAttachAcpMsg:WARNING:NAS->EMM MSG TAI decode error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnAttachAcpMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL2);

        return NAS_EMM_FAIL;
    }
    /*����Tai*/
    ulIndex = ulIndex + ulSum;

    /*��������0*/
    ulSum = NAS_EMM_NULL;

    if(NAS_EMM_FAIL == NAS_EMM_DecodeMsgCon((pTmpRcvMsg+ulIndex),
                                                &ulSum,
                                                &(pstCnMsgStruIE->uCnMsgStru.stAttAcp.stMsgCon)))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnAttachAcpMsg:WARNING:NAS->EMM MSG MsId decode error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnAttachAcpMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_FAIL;
    }
    /*����ESM message container*/
    ulIndex = ulIndex + ulSum;
    /*ѭ�������������*/
    stIEOptParaList.pRcvMsg = pTmpRcvMsg+ulIndex;
    stIEOptParaList.ulLength = ulMsgSize-(ulIndex + ulLength);
    stIEOptParaList.pCnMsgOpt = NAS_EMM_DECODE_BUFFER_MSG_OPT(pstCnMsgStruIE);
    stIEOptParaList.ulOptPos = 1;
    stIEOptParaList.pstCnMsgStru = &(pstCnMsgStruIE->uCnMsgStru.stAttAcp.stGuti);
    stIEOptParaList.pstCnMsgInfo = &stCnAttachAcp;
    if(NAS_EMM_FAIL == NAS_EMM_DecodeCnMsgIEOptList(&stIEOptParaList,&ulSum))
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnAttachAcpMsg:OPT IE Decode ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnAttachAcpMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL4);
        return NAS_EMM_FAIL;
    }

    return NAS_EMM_SUCC;
}



VOS_UINT32  NAS_EMM_DecodeCnAttachAcpMsg(LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT32                          ulRet;

    ulRet = NAS_EMM_DecodeCnAttachAcpMsgNasMsg( pRcvMsg,
                                                pRcvMsg->aucNasMsg,
                                                ulLength,
                                                pstCnMsgStru);

    return ulRet;
}


VOS_UINT32  NAS_EMM_DecodeCnAttachRejMsgNasMsg(
                                        LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                        VOS_UINT8                  *pucRcvCnNasMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT32                          ulRcvNwMsgLen       = NAS_EMM_NULL;
    VOS_UINT8                           ulEsmCause          = NAS_EMM_NULL;
    VOS_UINT32                          ulRet;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    NAS_EMM_DECODE_IELIST_PARA_STRU     stIEOptParaList={NAS_EMM_NULL};
    NAS_EMM_DECODE_MSG_INFO_STRU        stCnAttachRej = \
                                        NAS_EMM_DECODE_MSG_ITEM(NAS_EMM_CN_MT_ATTACH_REJ,\
                                                                g_astCnAttachRejIEList,\
                                                                NAS_EMM_CN_ATTACH_REJ_STR);

    ulMsgSize  = pRcvMsg->ulNasMsgSize;
    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*������Ϣ����*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*������Ϣ����*/
    ulIndex++;

    /* Э��24301   9.9.3.9�ڵ�Table 9.9.3.9.1���������Ǳ�������ԭ��ֵ����Ϊ#111���� */
    /*���EMM cause*/
    pstCnMsgStruIE->uCnMsgStru.stAttRej.ucCause = NAS_EMM_DecodeCnEmmCause(pTmpRcvMsg[ulIndex]);

    /*����EMM cause*/
    ulIndex++;

    if (NAS_RELEASE_R11)
    {
        /*�ѽ������Ϣ���Ⱥͷ���������Ϣ�������Ƚϣ��жϽ����Ƿ����*/
        if(ulMsgSize < (ulIndex + ulLength + pTmpRcvMsg[ulIndex+1] + 1))
        {
            return NAS_EMM_SUCC;
        }
        /*ѭ�������������*/
        stIEOptParaList.pRcvMsg = pTmpRcvMsg+ulIndex;
        stIEOptParaList.ulLength = ulMsgSize-(ulIndex + ulLength);
        stIEOptParaList.pCnMsgOpt = NAS_EMM_DECODE_BUFFER_MSG_OPT(pstCnMsgStruIE);
        stIEOptParaList.ulOptPos = 1;
        stIEOptParaList.pstCnMsgStru = &(pstCnMsgStruIE->uCnMsgStru.stAttRej.stMsgCon);
        stIEOptParaList.pstCnMsgInfo = &stCnAttachRej;
        if(NAS_EMM_FAIL == NAS_EMM_DecodeCnMsgIEOptList(&stIEOptParaList,&ulSum))
        {
            NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnAttachRejMsg:OPT IE Decode ERR!");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnAttachRejMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL1);
            return NAS_EMM_FAIL;
        }

        if(NAS_EMM_BIT_SLCT == pstCnMsgStruIE->uCnMsgStru.stAttRej.ucBitOpMsgCon)
        {
            /*����ESM Cause*/
            ulRcvNwMsgLen = pstCnMsgStruIE->uCnMsgStru.stAttRej.stMsgCon.ulMsgLen;
            ulRet = NAS_ESM_DecodeNwEsmMsgGetEsmCause((VOS_UINT8  *)(pstCnMsgStruIE->uCnMsgStru.stAttRej.stMsgCon.aucMsg), ulRcvNwMsgLen, &ulEsmCause);
            if(NAS_EMM_SUCC == ulRet)
            {
                pstCnMsgStru->uCnMsgStru.stAttRej.ucEsmCause = ulEsmCause;
            }
        }
    }
    else
    {
        /*�����Ϣ���ܳ��ȴ����Ѿ��ӵļ�����Ϣͷ���ȼ���1������������TL����TV������������ѡ��Ԫ*/
         while(ulMsgSize >= (ulIndex + ulLength + 1))
         {
             if(NAS_EMM_MSG_CON_IEI == pTmpRcvMsg[ulIndex])
             {
                  /*�ж��Ƿ񳬳�*/
                 if(ulMsgSize < (ulIndex + ulLength + pTmpRcvMsg[ulIndex+1] + 1))
                 {
                     return NAS_EMM_SUCC;
                 }

                /*����ESM message container�ֽ�*/
                ulIndex++;

                 if(NAS_EMM_FAIL == NAS_EMM_DecodeMsgCon((pTmpRcvMsg+ulIndex),
                                                         &ulSum,
                                                         &(pstCnMsgStruIE->uCnMsgStru.stAttRej.stMsgCon)))
                 {

                     NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnAttachAcpMsg:WARNING:NAS->EMM MSG MsId decode error!");
                     TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnAttachRejMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL2);
                     return NAS_EMM_FAIL;
                 }

                 pstCnMsgStruIE->uCnMsgStru.stAttRej.ucBitOpMsgCon = NAS_EMM_BIT_SLCT;
                 ulRcvNwMsgLen = pstCnMsgStruIE->uCnMsgStru.stAttRej.stMsgCon.ulMsgLen;
                 ulRet = NAS_ESM_DecodeNwEsmMsgGetEsmCause((VOS_UINT8  *)(pstCnMsgStruIE->uCnMsgStru.stAttRej.stMsgCon.aucMsg), ulRcvNwMsgLen, &ulEsmCause);
                 if(NAS_EMM_SUCC == ulRet)
                 {
                     pstCnMsgStru->uCnMsgStru.stAttRej.ucEsmCause = ulEsmCause;
                 }
                 /*����ESM message container*/

                 ulIndex += ulSum;
             }
             else if(NAS_EMM_MSG_T3346_IEI == pTmpRcvMsg[ulIndex])
             {
                 /*�ж��Ƿ񳬳�*/
                 if(ulMsgSize < (ulIndex + ulLength + pTmpRcvMsg[ulIndex+1] + 1))
                 {
                     return NAS_EMM_SUCC;
                 }

                 /*������ʱ������������*/
                 ulIndex += 3;
             }
             else if(NAS_EMM_MSG_EXT_3402_IEI == pTmpRcvMsg[ulIndex])
             {
                 /*�ж��Ƿ񳬳�*/
                 if(ulMsgSize < (ulIndex + ulLength + pTmpRcvMsg[ulIndex+1] + 1))
                 {
                     return NAS_EMM_SUCC;
                 }

                 /*������ʱ������������*/
                 ulIndex += 3;
             }
             else if(NAS_EMM_MSG_EXTENDED_EMM_CAUSE == ((pTmpRcvMsg[ulIndex])& NAS_EMM_CN_HIGH_4_BIT))
             {
                 pstCnMsgStruIE->uCnMsgStru.stAttRej.ucBitOpExtCause = NAS_EMM_BIT_SLCT;
                 pstCnMsgStruIE->uCnMsgStru.stAttRej.ucExtendedEmmCause = (pTmpRcvMsg[ulIndex]) & 0x01;
                 ulIndex++;
             }
             else
             {
                 return NAS_EMM_SUCC;
             }
         }

    }

    return NAS_EMM_SUCC;
}




VOS_UINT32  NAS_EMM_DecodeCnAttachRejMsg(LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT32                          ulRet;

    ulRet = NAS_EMM_DecodeCnAttachRejMsgNasMsg( pRcvMsg,
                                                pRcvMsg->aucNasMsg,
                                                ulLength,
                                                pstCnMsgStru);

    return ulRet;
}


VOS_UINT32  NAS_EMM_DecodeCnDetachAcpMsg(
                                        LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    /*������Ϣ����*/
    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulLength;
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    return NAS_EMM_SUCC;
}
VOS_UINT32  NAS_EMM_DecodeCnDetachReqMsgNasMsg(
                                        LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                        VOS_UINT8                  *pucRcvCnNasMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT8                           ucDetachType        = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    ulMsgSize  = pRcvMsg->ulNasMsgSize;
    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*������Ϣ����*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*������Ϣ����*/
    ulIndex++;

    ucDetachType = pTmpRcvMsg[ulIndex] & NAS_EMM_LOW_HALF_BYTE_F;
    if((NAS_EMM_DETACH_TYPE_MT_REATTACH != ucDetachType)
        &&(NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH != ucDetachType)
        &&(NAS_EMM_DETACH_TYPE_MT_IMSI_DETACH != ucDetachType)
        &&(NAS_EMM_DETACH_TYPE_MT_RESERVED1 != ucDetachType)
        &&(NAS_EMM_DETACH_TYPE_MT_RESERVED2 != ucDetachType))
    {
        ucDetachType = NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH;
    }
    pstCnMsgStruIE->uCnMsgStru.stDetachReq.ucDetType = ucDetachType;

    /*����ucDetachType*/
    ulIndex++;

    /*�ѽ������Ϣ���Ⱥͷ���������Ϣ�������Ƚϣ��жϽ����Ƿ����*/
    if(ulMsgSize < (ulIndex + ulLength + 2))
    {
        return NAS_EMM_SUCC;
    }

    if(NAS_EMM_MSG_EMMCAU_IEI == pTmpRcvMsg[ulIndex])
    {
        pstCnMsgStruIE->uCnMsgStru.stDetachReq.ucBitOpCause = NAS_EMM_BIT_SLCT;

        /*����IEI*/
        ulIndex++;

        pstCnMsgStruIE->uCnMsgStru.stDetachReq.ucEmmCause = NAS_EMM_DecodeCnEmmCause(pTmpRcvMsg[ulIndex]);
    }

    return NAS_EMM_SUCC;
}
VOS_UINT32  NAS_EMM_DecodeCnDetachReqMsg(LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT32                          ulRet;
    NAS_EMM_DETACH_TYPE_MT_ENUM_UINT8   ucCnDetType;

    ulRet = NAS_EMM_DecodeCnDetachReqMsgNasMsg( pRcvMsg,
                                                pRcvMsg->aucNasMsg,
                                                ulLength,
                                                pstCnMsgStru);
    /*���������DETACH��������RESERVED1,RESERVED2��Ŀǰ��Ϊ
      REATTACH-NOT-REQUIRED���ʹ���Ϊ�˱�֤������չ����ʱ������״̬������*/
    ucCnDetType = pstCnMsgStru->uCnMsgStru.stDetachReq.ucDetType;
    if((NAS_EMM_DETACH_TYPE_MT_RESERVED1 == ucCnDetType)
      ||(NAS_EMM_DETACH_TYPE_MT_RESERVED2 == ucCnDetType))
    {
        pstCnMsgStru->uCnMsgStru.stDetachReq.ucDetType = NAS_EMM_DETACH_TYPE_MT_NOT_REATTACH;
    }

    return ulRet;
}


VOS_UINT32  NAS_EMM_DecodeCnGUTICmdMsgNasMsg(
                                        LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                        VOS_UINT8                  *pucRcvCnNasMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    ulMsgSize  = pRcvMsg->ulNasMsgSize;
    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*������Ϣ����*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*������Ϣ����*/
    ulIndex++;

    /*GUTI�Ǳ�ѡ����*/
    if(NAS_EMM_FAIL == NAS_EMM_DecodeGuti((pTmpRcvMsg+ulIndex),
                                         &ulSum,
                                         &(pstCnMsgStruIE->uCnMsgStru.stGutiReaCmd.stGuti),
                                         NAS_EMM_CN_MT_BUTT))
    {
        /*��ӡ������Ϣ*/
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnGUTICmdMsg:WARNING:NAS->EMM MSG GUTI decode error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnGUTICmdMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*����GUTI*/
    ulIndex = ulIndex + ulSum;

    /*�ѽ������Ϣ���Ⱥͷ���������Ϣ�������Ƚϣ��жϽ����Ƿ����*/
    if(ulMsgSize < (ulIndex + ulLength + pTmpRcvMsg[ulIndex+1] + 1))
    {
        return NAS_EMM_SUCC;
    }

    /*�ж�TAI�Ƿ����*/
    if(NAS_EMM_MSG_TAI_IEI == pTmpRcvMsg[ulIndex])
    {
        /*����TAI IEI�ֽ�*/
        ulIndex++;

        /*��������0*/
        ulSum = NAS_EMM_NULL;

        if(NAS_EMM_FAIL == NAS_EMM_DecodeTai((pTmpRcvMsg+ulIndex),
                                            &ulSum,
                                            &(pstCnMsgStruIE->uCnMsgStru.stGutiReaCmd.stTaiList),
                                            NAS_EMM_CN_MT_BUTT))
        {
            /* ��ѡ��Ԫ����ʧ�ܣ����ǲ��Կ�ʱ�����ؽ���ʧ�ܣ������տ���ϳ�ԭ�򷵻ؽ���ɹ� */
            if(PS_SUCC == LPS_OM_IsTestMode())
            {
                /*��ӡ������Ϣ*/
                NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnGUTICmdMsg:WARNING:NAS->EMM MSG TAI decode error!");
                TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnGUTICmdMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL2);
                return NAS_EMM_FAIL;
            }
            else
            {
                return NAS_EMM_SUCC;
            }
        }

        pstCnMsgStruIE->uCnMsgStru.stGutiReaCmd.ucBitOpTaiList = NAS_EMM_BIT_SLCT;

        /*����TAI*/
    }

    return NAS_EMM_SUCC;
}



VOS_UINT32  NAS_EMM_DecodeCnGUTICmdMsg(LRRC_LNAS_MSG_STRU            *pRcvMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT32                          ulRet;

    ulRet = NAS_EMM_DecodeCnGUTICmdMsgNasMsg(   pRcvMsg,
                                                pRcvMsg->aucNasMsg,
                                                ulLength,
                                                pstCnMsgStru);

    return ulRet;
}


VOS_UINT32  NAS_EMM_DecodeCnIdenReqMsg(
                                    LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                    VOS_UINT32                  ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT8                           ulTypeId            = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    /*������Ϣ����*/
    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulLength;
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*������Ϣ����*/
    ulIndex++;

    /*ȡ��type of identity*/
    ulTypeId = pTmpRcvMsg[ulIndex] & NAS_EMM_LOW_3_BITS_F;

    /*����type of identity:24008-930 10.5.5.9 ȡֵ��Χ[0,7],��1,2,3,4��ֵ��ΪIMSI����*/
    pstCnMsgStruIE->uCnMsgStru.stIdenReq.ucIdenType = ulTypeId;

    return NAS_EMM_SUCC;
}



VOS_UINT32  NAS_EMM_DecodeCnSerRejMsgNasMsg(
                                        LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                        VOS_UINT8                  *pucRcvCnNasMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;

    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    ulMsgSize  = pRcvMsg->ulNasMsgSize;
    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*������Ϣ����*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*������Ϣ����*/
    ulIndex++;

    pstCnMsgStruIE->uCnMsgStru.stSerRej.ucEMMCause = NAS_EMM_DecodeCnEmmCause(pTmpRcvMsg[ulIndex]);

    ulIndex++;

    /*�ѽ������Ϣ���Ⱥͷ���������Ϣ�������Ƚϣ��жϽ����Ƿ����*/
    if(ulMsgSize < (ulIndex + ulLength + 2))
    {
        return NAS_EMM_SUCC;
    }

    /*�ж�T3442�Ƿ����*/
    if(NAS_EMM_MSG_T3442_IEI == pTmpRcvMsg[ulIndex])
    {
        pstCnMsgStruIE->uCnMsgStru.stSerRej.ucBitOpT3442 = NAS_EMM_BIT_SLCT;

        /*����T3442 IEI�ֽ�*/
        ulIndex++;

        (VOS_VOID)NAS_EMM_DecodeTimer((pTmpRcvMsg+ulIndex),
                                         &ulSum,
                                         &(pstCnMsgStruIE->uCnMsgStru.stSerRej.stT3442),
                                         NAS_EMM_CN_MT_BUTT);

    }

    return NAS_EMM_SUCC;
}
VOS_UINT32  NAS_EMM_DecodeCnSerRejMsg(LRRC_LNAS_MSG_STRU             *pRcvMsg,
                                    VOS_UINT32                      ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru)
{
    VOS_UINT32                          ulRet;

    ulRet = NAS_EMM_DecodeCnSerRejMsgNasMsg(    pRcvMsg,
                                                pRcvMsg->aucNasMsg,
                                                ulLength,
                                                pstCnMsgStru);

    return ulRet;
}
/*****************************************************************************
 Function Name   : NAS_EMM_VerifyEpsUpdateRslt
 Description     : ��֤EPS Update Result��Ԫ�Ƿ�Ϸ�

                   0   0   0       TA updated
                   0   0   1       combined TA/LA updated
                   1   0   0       TA updated and ISR activated (NOTE)
                   1   0   1       combined TA/LA updated and ISR activated (NOTE)
                   All other values are reserved

 Input           : ucEPSUpdateRslt----------EPS Update Result
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-08-23  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_VerifyEpsUpdateRslt
(
    VOS_UINT8                           ucEPSUpdateRslt
)
{
    if (NAS_EMM_EPS_UPDATE_RST_TA_UPDATED == ucEPSUpdateRslt)
    {
        return NAS_EMM_SUCC;
    }

    if (NAS_EMM_EPS_UPDATE_RST_COMBINED_TA_LA_UPDATED == ucEPSUpdateRslt)
    {
        return NAS_EMM_SUCC;
    }

    if (NAS_EMM_EPS_UPDATE_RST_TA_UPDATED_AND_ISR == ucEPSUpdateRslt)
    {
        return NAS_EMM_SUCC;
    }

    if (NAS_EMM_EPS_UPDATE_RST_COMBINED_TA_LA_UPDATED_AND_ISR == ucEPSUpdateRslt)
    {
        return NAS_EMM_SUCC;
    }

    return NAS_EMM_FAIL;
}

VOS_UINT32  NAS_EMM_DecodeCnTAUAcpMsgNasMsg(
                                        LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                        VOS_UINT8                  *pucRcvCnNasMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT8                           ucEPSUpdateRslt     = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;
    NAS_EMM_DECODE_MSG_INFO_STRU        stCnTauAcp = \
                                        NAS_EMM_DECODE_MSG_ITEM(NAS_EMM_CN_MT_TAU_ACP,\
                                                                g_astCnTauAcpIEList,\
                                                                NAS_EMM_CN_TAU_ACP_STR);
    NAS_EMM_DECODE_IELIST_PARA_STRU     stIEOptParaList = {NAS_EMM_NULL};

    NAS_LMM_MEM_SET(&stIEOptParaList, 0, sizeof(NAS_EMM_DECODE_IELIST_PARA_STRU));


    ulMsgSize  = pRcvMsg->ulNasMsgSize;
    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*������Ϣ����*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*������Ϣ����*/
    ulIndex++;

    /*ȡ��EPS attach result*/
    ucEPSUpdateRslt = pTmpRcvMsg[ulIndex]&NAS_EMM_LOW_3_BITS_F;

    /*�ж�EPS update result�Ƿ����Э��Ҫ��*/
    if(NAS_EMM_SUCC == NAS_EMM_VerifyEpsUpdateRslt(ucEPSUpdateRslt))
    {
        pstCnMsgStruIE->uCnMsgStru.stTauAcp.ucEPSupdataRst = ucEPSUpdateRslt;
    }
    else
    {
        /* �׳���ά�ɲ� */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_TAURSLT_IE, EMM_CN_MSG_IE_TAURSLT_INVALID, ucEPSUpdateRslt);
        /*��ӡ������Ϣ*/
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnTAUAcpMsg:WARNING:NAS->EMM MSG update Rslt not assigned ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnTAUAcpMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*����EPS update result*/
    ulIndex++;

    /*ѭ�������������*/
    stIEOptParaList.pRcvMsg = pTmpRcvMsg+ulIndex;
    stIEOptParaList.ulLength = ulMsgSize-( ulIndex + ulLength );
    stIEOptParaList.pCnMsgOpt = NAS_EMM_DECODE_BUFFER_MSG_OPT(pstCnMsgStruIE);
    stIEOptParaList.ulOptPos = 1;
    stIEOptParaList.pstCnMsgStru = &(pstCnMsgStruIE->uCnMsgStru.stTauAcp.stT3412);
    stIEOptParaList.pstCnMsgInfo = &stCnTauAcp;
    if(NAS_EMM_FAIL == NAS_EMM_DecodeCnMsgIEOptList(&stIEOptParaList,&ulSum))
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeCnTAUAcpMsg:OPT IE Decode ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeCnTAUAcpMsgNasMsg_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }
    return NAS_EMM_SUCC;
}



VOS_UINT32  NAS_EMM_DecodeCnTAUAcpMsg(LRRC_LNAS_MSG_STRU             *pRcvMsg,
                                    VOS_UINT32                      ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru)
{
    VOS_UINT32                          ulRet;

    ulRet = NAS_EMM_DecodeCnTAUAcpMsgNasMsg(    pRcvMsg,
                                                pRcvMsg->aucNasMsg,
                                                ulLength,
                                                pstCnMsgStru);

    return ulRet;
}


VOS_UINT32  NAS_EMM_DecodeCnTAURejMsg(
                                    LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                    VOS_UINT32                  ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;

    NAS_EMM_CN_MSG_STRU   *pstCnMsgStruIE  = pstCnMsgStru;

    /*������Ϣ����*/
    ulMsgSize  = pRcvMsg->ulNasMsgSize;
    pTmpRcvMsg =  pRcvMsg->aucNasMsg + ulLength;
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*������Ϣ����*/
    ulIndex++;

    pstCnMsgStruIE->uCnMsgStru.stTauRej.ucEMMCause = NAS_EMM_DecodeCnEmmCause(pTmpRcvMsg[ulIndex]);

    /*����EMM cause*/
    ulIndex++;

    /*�����Ϣ���ܳ��ȴ����Ѿ��ӵļ�����Ϣͷ���ȼ���1������������TL����TV������������ѡ��Ԫ*/
    while(ulMsgSize >= (ulIndex + ulLength + 1))
    {
        if(NAS_EMM_MSG_T3346_IEI == pTmpRcvMsg[ulIndex])
        {
            /*�ж��Ƿ񳬳�*/
            if(ulMsgSize < (ulIndex + ulLength + pTmpRcvMsg[ulIndex+1] + 1))
            {
                return NAS_EMM_SUCC;
            }

            /*����T3346�ֽ�*/
            ulIndex++;

            if(NAS_EMM_FAIL == NAS_EMM_DecodeTimer2((pTmpRcvMsg+ulIndex),
                                                        &ulSum,
                                                        &(pstCnMsgStruIE->uCnMsgStru.stTauRej.stT3346),
                                                        NAS_EMM_CN_MT_TAU_REJ))
            {
                /*��ӡ������Ϣ*/
                NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnTAURejMsg:WARNING:NAS->EMM MSG MsId decode error!");
                TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnTAURejMsg_ENUM,LNAS_FUNCTION_LABEL1);
                return NAS_EMM_SUCC;
            }
            /* �������Я��T3346,����ʱ��Ϊ0������Ϊ����Я����T3346 */
            /* 24304 5.5.1.2.5 If the T3346 value IE is present in the ATTACH REJECT message and the
            value indicates that this timer is neither zero nor deactivated,*/
            if ((0 != pstCnMsgStruIE->uCnMsgStru.stTauRej.stT3346.ucTimerVal) &&
                (NAS_EMM_TIMER_DEACTIVATE != pstCnMsgStruIE->uCnMsgStru.stTauRej.stT3346.ucUnit))
            {
                pstCnMsgStruIE->uCnMsgStru.stTauRej.ucBitOpT3346 = NAS_EMM_BIT_SLCT;
            }

            /*������ǰ3346�Ľ����ֽ�*/
            ulIndex += ulSum;
        }
        else if(NAS_EMM_MSG_EXTENDED_EMM_CAUSE == ((pTmpRcvMsg[ulIndex])& NAS_EMM_CN_HIGH_4_BIT))
        {
            pstCnMsgStruIE->uCnMsgStru.stTauRej.ucBitOpExtCause = NAS_EMM_BIT_SLCT;
            pstCnMsgStruIE->uCnMsgStru.stTauRej.ucEmmExtCause = (pTmpRcvMsg[ulIndex]) & 0x01;
            ulIndex++;
        }
        else
        {
            return NAS_EMM_SUCC;
        }
    }
    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnAuthReqMsgNasMsg
 Description     :
 Input           : LRRC_LNAS_MSG_STRU                    *pRcvMsg
                   VOS_UINT8                           *pucRcvCnNasMsg
                   VOS_UINT32                          ulLength
                   NAS_EMM_CN_MSG_STRU                 *pstCnMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.luojian      2009-4-2  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnAuthReqMsgNasMsg
(
    LRRC_LNAS_MSG_STRU                    *pRcvMsg,
    VOS_UINT8                           *pucRcvCnNasMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    (VOS_VOID)pRcvMsg;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_DecodeCnAuthReqMsgNasMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnAuthReqMsgNasMsg_ENUM,LNAS_ENTRY);

    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*������Ϣ����*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

     /*������Ϣ����*/
    ulIndex++;

    /* ȡKSIλ */
    pstCnMsgStruIE->uCnMsgStru.stAuthReq.ucKsi = pTmpRcvMsg[ulIndex++];

    /* ȡRand */
    NAS_LMM_MEM_CPY( pstCnMsgStruIE->uCnMsgStru.stAuthReq.aucRand,
                      &pTmpRcvMsg[ulIndex],
                      NAS_EMM_SECU_AUTH_RAND_LEN);

    ulIndex                             += NAS_EMM_SECU_AUTH_RAND_LEN;

    /*ȡauth�ĳ���*/
    pstCnMsgStruIE->uCnMsgStru.stAuthReq.ulAutnLen = pTmpRcvMsg[ulIndex];

    /* ����autn���� */
    ulIndex++;

    /* ȡAuth */
    NAS_LMM_MEM_CPY( pstCnMsgStruIE->uCnMsgStru.stAuthReq.aucAutn,
                      &pTmpRcvMsg[ulIndex],
                      pstCnMsgStruIE->uCnMsgStru.stAuthReq.ulAutnLen);

    return NAS_EMM_SUCC;
}

VOS_UINT32  NAS_EMM_DecodeCnAuthReqMsg
(
    LRRC_LNAS_MSG_STRU                    *pRcvMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          ulRet;

    ulRet = NAS_EMM_DecodeCnAuthReqMsgNasMsg( pRcvMsg,
                                              pRcvMsg->aucNasMsg,
                                              ulLength,
                                              pstCnMsgStru);

    return ulRet;
}

VOS_UINT32  NAS_EMM_DecodeCnAuthRejMsg(
                                    LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                    VOS_UINT32                  ulLength,
                                    NAS_EMM_CN_MSG_STRU            *pstCnMsgStru)
{
    /* ����Ҫ������,ֻ��ͷ�� */

    (VOS_VOID)ulLength;
    (VOS_VOID)pRcvMsg;
    (VOS_VOID)pstCnMsgStru;

    return NAS_EMM_SUCC;
}
VOS_UINT32  NAS_EMM_DecodeCnSecurModeCtrlMsgNasMsg
(
    LRRC_LNAS_MSG_STRU                    *pRcvMsg,
    VOS_UINT8                           *pucRcvCnNasMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    VOS_UINT8                           ucImeisvIei         = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;

    /* ��ӡ����ú����� INFO_LEVEL */
    NAS_EMM_PUBU_LOG_INFO( "NAS_EMM_DecodeCnSecurModeCtrlMsgNasMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnSecurModeCtrlMsgNasMsg_ENUM,LNAS_ENTRY);
    ulMsgSize  = pRcvMsg->ulNasMsgSize;

    pTmpRcvMsg = pucRcvCnNasMsg + ulLength;

    /*������Ϣ����*/
    ucMsgType = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*������Ϣ����*/
    ulIndex++;

    /* ȡ security algorithms */
    pstCnMsgStruIE->uCnMsgStru.stSecurModeCtrl.ucSelAlgrthm
                                        = pTmpRcvMsg[ulIndex++];

    /* ȡEPS��KSI */
    pstCnMsgStruIE->uCnMsgStru.stSecurModeCtrl.ucKSIasme
                                        = pTmpRcvMsg[ulIndex++] & NAS_EMM_LOW_3_BITS_F;

    /* ȡUE�İ�ȫ���� */
    pstCnMsgStruIE->uCnMsgStru.stSecurModeCtrl.stReSecurityCapa.ucLen
                                        = pTmpRcvMsg[ulIndex++];
    pstCnMsgStruIE->uCnMsgStru.stSecurModeCtrl.stReSecurityCapa.pucValue
                                        = &pTmpRcvMsg[ulIndex];

    ulIndex += pstCnMsgStruIE->uCnMsgStru.stSecurModeCtrl.stReSecurityCapa.ucLen;

    if(ulMsgSize <= (ulIndex + ulLength))
    {
        return NAS_EMM_SUCC;
    }

    ucImeisvIei = (pTmpRcvMsg[ulIndex] & NAS_EMM_HIGH_HALF_BYTE_F) >> NAS_EMM_MOVEMENT_4_BITS;

    if(NAS_EMM_MSG_KSI_IMEISV_IEI == ucImeisvIei)
    {
        /* ȡ�Ƿ���ҪImeisv */
        pstCnMsgStruIE->uCnMsgStru.stSecurModeCtrl.ucImeisvRsq = pTmpRcvMsg[ulIndex] & NAS_EMM_LOW_3_BITS_F;
    }
    return NAS_EMM_SUCC;
}
VOS_UINT32  NAS_EMM_DecodeCnSecurModeCtrlMsg
(
    LRRC_LNAS_MSG_STRU                    *pRcvMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                 *pstCnMsgStru
)
{
    VOS_UINT32                          ulRet;

    ulRet = NAS_EMM_DecodeCnSecurModeCtrlMsgNasMsg( pRcvMsg,
                                              pRcvMsg->aucNasMsg,
                                              ulLength,
                                              pstCnMsgStru);

    return ulRet;
}

VOS_UINT32 NAS_EMM_DecodeType1Tai(VOS_UINT32 *pulTaiLength,
                                        VOS_UINT32  ulTaiNumSum,
                                        VOS_UINT8  *pucTaiInfo,
                                        NAS_EMM_TA_LIST_STRU   *pstTaiStru
)
{
    VOS_UINT8                          *pucTmpMsg           = pucTaiInfo;
    VOS_UINT32                          i                   = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulTaiNum            = NAS_EMM_NULL;
    VOS_UINT32                          ulTotalTaiNum       = ulTaiNumSum;
    VOS_UINT32                          ulRst;
    NAS_MM_TA_STRU                      stTmpTa;
    NAS_EMM_TA_LIST_STRU               *pstTmpTaiStru       = pstTaiStru;

    /*ȡ��Tai����,00000��Ӧ1������Ӧ��+1*/
    ulTaiNum  = ((VOS_UINT32)(pucTmpMsg[ulSum]&NAS_EMM_CN_LOW_5_BIT))+1;

    /*����TAI����*/
    ulSum++;

    stTmpTa.stPlmnId.aucPlmnId[0] = pucTmpMsg[ulSum++];
    stTmpTa.stPlmnId.aucPlmnId[1] = pucTmpMsg[ulSum++];
    stTmpTa.stPlmnId.aucPlmnId[2] = pucTmpMsg[ulSum++];
    stTmpTa.stTac.ucTac = pucTmpMsg[ulSum++];
    stTmpTa.stTac.ucTacCnt = pucTmpMsg[ulSum++];

    for(i = 0; i < ulTaiNum;i++)
    {
        NAS_LMM_PlmnCpy( &(pstTmpTaiStru->astTa[ulTotalTaiNum].stPlmnId),
                        &(stTmpTa.stPlmnId));
        pstTmpTaiStru->astTa[ulTotalTaiNum].stTac.ucTac
            = stTmpTa.stTac.ucTac;
        pstTmpTaiStru->astTa[ulTotalTaiNum].stTac.ucTacCnt
            = stTmpTa.stTac.ucTacCnt;

        ulRst = NAS_LMM_TaIncrease(&stTmpTa.stTac);
        if(NAS_LMM_SUCC != ulRst)
        {
            NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeType1Tai: NAS_LMM_TaIncrease error!");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeType1Tai_ENUM,LNAS_FUNCTION_LABEL1);
        }

        ulTotalTaiNum++;

        if (ulTotalTaiNum >= NAS_EMM_TA_MAX_TAC_MUN)
        {
            break;
        }
    }

    *pulTaiLength = ulSum;

    return (ulTotalTaiNum - ulTaiNumSum);
}



VOS_UINT32 NAS_EMM_DecodeType0Tai(VOS_UINT32 *pulTaiLength,
                                        VOS_UINT32  ulTaiNumSum,
                                        VOS_UINT8  *pucTaiInfo,
                                        NAS_EMM_TA_LIST_STRU   *pstTaiStru
)
{
    VOS_UINT8                          *pucTmpMsg           = pucTaiInfo;
    VOS_UINT32                          i                   = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulTaiNum            = NAS_EMM_NULL;
    VOS_UINT32                          ulTotalTaiNum       = ulTaiNumSum;
    NAS_MM_TA_STRU                      stTmpTa;
    NAS_EMM_TA_LIST_STRU               *pstTmpTaiStru       = pstTaiStru;

    /*ȡ��Tai����,00000��Ӧ1������Ӧ��+1*/
    ulTaiNum  = ((VOS_UINT32)(pucTmpMsg[ulSum]&NAS_EMM_CN_LOW_5_BIT))+1;

    /*����TAI����*/
    ulSum++;

    stTmpTa.stPlmnId.aucPlmnId[0] = pucTmpMsg[ulSum++];
    stTmpTa.stPlmnId.aucPlmnId[1] = pucTmpMsg[ulSum++];
    stTmpTa.stPlmnId.aucPlmnId[2] = pucTmpMsg[ulSum++];

    for(i = 0; i < ulTaiNum;i++)
    {
        NAS_LMM_PlmnCpy( &(pstTmpTaiStru->astTa[ulTotalTaiNum].stPlmnId),
                        &(stTmpTa.stPlmnId));

        pstTmpTaiStru->astTa[ulTotalTaiNum].stTac.ucTac
            = pucTmpMsg[ulSum++];
        pstTmpTaiStru->astTa[ulTotalTaiNum].stTac.ucTacCnt
            = pucTmpMsg[ulSum++];

        ulTotalTaiNum++;

        if (ulTotalTaiNum >= NAS_EMM_TA_MAX_TAC_MUN)
        {
            break;
        }
    }

    *pulTaiLength = ulSum;

    return (ulTotalTaiNum - ulTaiNumSum);
}



VOS_UINT32 NAS_EMM_DecodeType2Tai(VOS_UINT32 *pulTaiLength,
                                        VOS_UINT32  ulTaiNumSum,
                                        VOS_UINT8  *pucTaiInfo,
                                        NAS_EMM_TA_LIST_STRU   *pstTaiStru
)
{
    VOS_UINT8                          *pucTmpMsg           = pucTaiInfo;
    VOS_UINT32                          i                   = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulTaiNum            = NAS_EMM_NULL;
    VOS_UINT32                          ulTotalTaiNum       = ulTaiNumSum;
    NAS_EMM_TA_LIST_STRU               *pstTmpTaiStru       = pstTaiStru;

    /*ȡ��Tai����,00000��Ӧ1������Ӧ��+1*/
    ulTaiNum  = ((VOS_UINT32)(pucTmpMsg[ulSum]&NAS_EMM_CN_LOW_5_BIT))+1;

    /*����TAI����*/
    ulSum++;

    for(i = 0; i < ulTaiNum;i++)
    {
        pstTmpTaiStru->astTa[ulTotalTaiNum].stPlmnId.aucPlmnId[0]
            = pucTmpMsg[ulSum++];
        pstTmpTaiStru->astTa[ulTotalTaiNum].stPlmnId.aucPlmnId[1]
            = pucTmpMsg[ulSum++];
        pstTmpTaiStru->astTa[ulTotalTaiNum].stPlmnId.aucPlmnId[2]
            = pucTmpMsg[ulSum++];
        pstTmpTaiStru->astTa[ulTotalTaiNum].stTac.ucTac
            = pucTmpMsg[ulSum++];
        pstTmpTaiStru->astTa[ulTotalTaiNum].stTac.ucTacCnt
            = pucTmpMsg[ulSum++];

        ulTotalTaiNum++;

        if (ulTotalTaiNum >= NAS_EMM_TA_MAX_TAC_MUN)
        {
            break;
        }
    }

    *pulTaiLength = ulSum;

    return (ulTotalTaiNum - ulTaiNumSum);
}


VOS_UINT32  NAS_EMM_DecodeTai(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstTaiStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulTaiLength         = NAS_EMM_NULL;
    VOS_UINT32                          ulIeLen             = NAS_EMM_NULL;
    VOS_UINT32                          ulTaiNum            = NAS_EMM_NULL;
    VOS_UINT32                          ulTotalTaiNum       = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;
    VOS_UINT8                           ucListType          = NAS_EMM_NULL;
    NAS_EMM_TA_LIST_STRU               *pstTmpTaiStru       = (NAS_EMM_TA_LIST_STRU *)pstTaiStru;

    (VOS_VOID)enMsgTp;


    /*��ڲ������*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeTai:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeTai_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /*�����һ������ΪTAI���ȣ���鳤��*/
    ulIeLen = pucTmpMsg[ulSum];

    if((NAS_EMM_CN_MAX_TAI_LIST_LEN < ulIeLen )||(NAS_EMM_CN_MIN_TAI_LIST_LEN > ulIeLen))
    {
        /* �׳���ά�ɲ� */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_TAI_IE, EMM_CN_MSG_IE_LEN_INVALID, ulIeLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeTai:ERROR:TAI list length error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeTai_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*����TAI����*/
    ulSum++;

    pstTmpTaiStru->ulTaNum = 0;

    /*ָ��TA List���׵�ַ*/
    pucTmpMsg = pucTmpMsg + ulSum;

    while(ulSum < ulIeLen)
    {
        pucTmpMsg = pucTmpMsg + ulTaiLength;

        /*ȡ��Type of list*/
        ucListType = (VOS_UINT8)((pucTmpMsg[0]&NAS_EMM_CN_HIGH_3_BIT)
                    >>NAS_EMM_MOVEMENT_5_BITS);

        if (ulTotalTaiNum >= NAS_EMM_TA_MAX_TAC_MUN)
        {
            break;
        }

        /*����Type of list�洢TAC*/
        if((NAS_EMM_TA_LIST_1 == ucListType))
        {
            ulTaiNum = NAS_EMM_DecodeType1Tai(&ulTaiLength,ulTotalTaiNum,pucTmpMsg,pstTaiStru);
        }
        else if(NAS_EMM_TA_LIST_0 == ucListType)
        {
            ulTaiNum = NAS_EMM_DecodeType0Tai(&ulTaiLength,ulTotalTaiNum,pucTmpMsg,pstTaiStru);
        }
        else if(NAS_EMM_TA_LIST_2 == ucListType)
        {
            ulTaiNum = NAS_EMM_DecodeType2Tai(&ulTaiLength,ulTotalTaiNum,pucTmpMsg,pstTaiStru);
        }
        else
        {
            /* �׳���ά�ɲ� */
            NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_TAI_IE, EMM_CN_MSG_IE_TAILIST_TYPE_INVALID, ucListType);
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeTai:ERROR:TAI list decode error!");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeTai_ENUM,LNAS_FUNCTION_LABEL2);
            return NAS_EMM_FAIL;
        }

        ulSum = ulSum + ulTaiLength;
        ulTotalTaiNum = ulTotalTaiNum + ulTaiNum;
    }

    pstTmpTaiStru->ulTaNum = ulTotalTaiNum;

    /*��¼����*/
    *pulIndex = ulIeLen + 1;

    return NAS_EMM_SUCC;
}

VOS_UINT32  NAS_EMM_DecodeGuti(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstGutiStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT32                          ulGutiLen           = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;
    VOS_UINT8                           ucEPSIdType         = NAS_EMM_NULL;
    NAS_EMM_GUTI_STRU                  *pstTmpGutiStru      = (NAS_EMM_GUTI_STRU *)pstGutiStru;

    (VOS_VOID)enMsgTp;


    /*��ڲ������*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeTai:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeGuti_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /*�����һ������ΪGuti���ȣ���鳤��*/
    if((NAS_EMM_NULL == pucTmpMsg[ulSum])
        ||(pucTmpMsg[ulSum] > NAS_EMM_CN_GUTI_MAX_LEN))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeGuti:ERROR:Guti length error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeGuti_ENUM,LNAS_FUNCTION_LABEL1);
        /* �׳���ά�ɲ� */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_GUTI_IE, EMM_CN_MSG_IE_LEN_INVALID, pucTmpMsg[ulSum]);
        return NAS_EMM_FAIL;
    }
    else
    {
        /*����GUTI���ݳ���*/
        ulGutiLen = pucTmpMsg[ulSum];
        pstTmpGutiStru->stGutiHead.ucLenth = (VOS_UINT8)ulGutiLen;
    }

    /*��������*/
    ulSum++;

    /*��3�ֽڵ�3ΪEPSIdType*/
    ucEPSIdType = pucTmpMsg[ulSum] & NAS_EMM_LOW_3_BITS_F;

    if(NAS_EMM_CN_EPS_TYPE_GUTI == ucEPSIdType)
    {
        /*����ucOeToi*/
        pstTmpGutiStru->stGutiHead.ucOeToi = pucTmpMsg[ulSum++];

        /*����PLMN*/
        pstTmpGutiStru->stPlmnId.aucPlmnId[0] = pucTmpMsg[ulSum++];
        pstTmpGutiStru->stPlmnId.aucPlmnId[1] = pucTmpMsg[ulSum++];
        pstTmpGutiStru->stPlmnId.aucPlmnId[2] = pucTmpMsg[ulSum++];

        /*����Group ID*/
        pstTmpGutiStru->stMmeGroupId.ucGroupId = pucTmpMsg[ulSum++];
        pstTmpGutiStru->stMmeGroupId.ucGroupIdCnt = pucTmpMsg[ulSum++];

        /*����MME Code*/
        pstTmpGutiStru->stMmeCode.ucMmeCode = pucTmpMsg[ulSum++];

        /*����M-TMSI*/
        pstTmpGutiStru->stMTmsi.ucMTmsi = pucTmpMsg[ulSum++];
        pstTmpGutiStru->stMTmsi.ucMTmsiCnt1 = pucTmpMsg[ulSum++];
        pstTmpGutiStru->stMTmsi.ucMTmsiCnt2 = pucTmpMsg[ulSum++];
        pstTmpGutiStru->stMTmsi.ucMTmsiCnt3 = pucTmpMsg[ulSum++];
    }
    else
    {
        /* �׳���ά�ɲ� */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_GUTI_IE, EMM_CN_MSG_IE_TYPE_INVALID, ucEPSIdType);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeGuti:ERROR:GUTI error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeGuti_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }

    /*��¼����*/
    *pulIndex = ulSum;
    return NAS_EMM_SUCC;
}
VOS_UINT32  NAS_EMM_DecodeLai(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstLaiStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;
    NAS_EMM_LA_STRU                    *pstTmpLaiStru       = (NAS_EMM_LA_STRU *)pstLaiStru;


    (VOS_VOID)enMsgTp;

    /*��ڲ������*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeLai:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeLai_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }
    pstTmpLaiStru->stPlmnId.aucPlmnId[0] = pucTmpMsg[ulSum++];
    pstTmpLaiStru->stPlmnId.aucPlmnId[1] = pucTmpMsg[ulSum++];
    pstTmpLaiStru->stPlmnId.aucPlmnId[2] = pucTmpMsg[ulSum++];
    pstTmpLaiStru->stLac.ucLac    = pucTmpMsg[ulSum++];
    pstTmpLaiStru->stLac.ucLacCnt = pucTmpMsg[ulSum++];

    /*��¼����*/
    *pulIndex = ulSum;

    return NAS_EMM_SUCC;
}


VOS_UINT32  NAS_EMM_DecodeMsId(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstMsIdStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT32                          ulMsIdLen           = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;

    NAS_EMM_MSID_STRU                  *pstTmpMsIdStru      = (NAS_EMM_MSID_STRU  *)pstMsIdStru;

    (VOS_VOID)enMsgTp;


    /*ȡ������*/
    ulMsIdLen = pucTmpMsg[0];

    /*�жϳ����Ƿ����Э��*/
    if((ulMsIdLen < NAS_EMM_CN_MSID_MIN_LEN)
        ||(ulMsIdLen > NAS_EMM_CN_MSID_MAX_LEN))
    {
        /* �׳���ά�ɲ� */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_MSID_IE, EMM_CN_MSG_IE_LEN_INVALID, ulMsIdLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeMsId:WARNING:Length Err. ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeMsId_ENUM,LNAS_ERROR);
        return NAS_EMM_FAIL;
    }

    NAS_LMM_MEM_CPY(pstTmpMsIdStru->aucMsId,pucTmpMsg,(ulMsIdLen+1));


    /*��¼����*/
    *pulIndex = ulMsIdLen + 1;

    return NAS_EMM_SUCC;
}



VOS_UINT32  NAS_EMM_DecodePlmnList(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstPlmnListStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT32                          i                   = NAS_EMM_NULL;
    VOS_UINT32                          ulPlmnLen           = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;
    NAS_EMM_PLMN_LIST_STRU             *pstTmpPlmnListStru  = (NAS_EMM_PLMN_LIST_STRU *)pstPlmnListStru;

    (VOS_VOID)enMsgTp;

    /*��ڲ������*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodePlmnList:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodePlmnList_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /*ȡ������*/
    ulPlmnLen = pucTmpMsg[ulSum];

    /*�жϳ����Ƿ����Э��*/
    if((ulPlmnLen < NAS_EMM_CN_PLMNLIST_MIN_LEN)||(ulPlmnLen > NAS_EMM_CN_PLMNLIST_MAX_LEN))
    {
        /* �׳���ά�ɲ� */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_PLMNLIST_IE, EMM_CN_MSG_IE_LEN_INVALID, ulPlmnLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodePlmnList:ERROR:Eplmn List length error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodePlmnList_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*����PLMN�̶�����Ϊ3���ɵõ�PLMN����*/
    if(NAS_EMM_NULL != (ulPlmnLen%NAS_EMM_CN_PLMNLIST_MIN_LEN))
    {
        /* �׳���ά�ɲ� */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_PLMNLIST_IE, EMM_CN_MSG_IE_LEN_INVALID, ulPlmnLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodePlmnList:ERROR:Eplmn List length error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodePlmnList_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }
    else
    {
        pstTmpPlmnListStru->ulPlmnNum = ulPlmnLen/NAS_EMM_CN_PLMNLIST_MIN_LEN;
    }

    /*��������*/
    ulSum++;

    for(i = 0; i < pstTmpPlmnListStru->ulPlmnNum; i++)
    {
        pstTmpPlmnListStru->astPlmnId[i].aucPlmnId[0] = pucTmpMsg[ulSum++];
        pstTmpPlmnListStru->astPlmnId[i].aucPlmnId[1] = pucTmpMsg[ulSum++];
        pstTmpPlmnListStru->astPlmnId[i].aucPlmnId[2] = pucTmpMsg[ulSum++];
    }

    /*��¼����*/
    *pulIndex = ulSum;

    return NAS_EMM_SUCC;
}


VOS_UINT32  NAS_EMM_VerifyEmergencyNumListLen
(
    VOS_UINT8                          *pRcvMsg
)
{
    VOS_UINT8                           ucTotalLen          = NAS_EMM_NULL;
    VOS_UINT8                           ucTmpLen            = NAS_EMM_NULL;
    VOS_UINT8                           ucEmerNumLen        = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;

    /*ȡ������*/
    ucTotalLen = pucTmpMsg[ulSum];

    /*�жϳ����Ƿ����Э��*/
    if((ucTotalLen < NAS_EMM_CN_EMERGENCYLIST_MIN_LEN)||(ucTotalLen > NAS_EMM_CN_EMERGENCYLIST_MAX_LEN))
    {
        /* �׳���ά�ɲ� */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_EMERGENCYLIST_IE, EMM_CN_MSG_IE_LEN_INVALID, ucTotalLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_VerifyEmergencyNumListLen:ERROR:<MIN LEN or >MAX LEN!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_VerifyEmergencyNumListLen_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*��������*/
    ulSum++;

    while (ucTotalLen > ucTmpLen)
    {
        /* Length of Emergency Number information */
        ucEmerNumLen = pucTmpMsg[ulSum++];

        /* �ۻ����н���������ĳ��� */
        ucTmpLen = ucTmpLen + ucEmerNumLen + 1;

        ulSum += ucEmerNumLen;
    }

    if (ucTotalLen != ucTmpLen)
    {
        /* �׳���ά�ɲ� */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_EMERGENCYLIST_IE, EMM_CN_MSG_IE_LEN_INVALID, ucTmpLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_VerifyEmergencyNumListLen:ERROR:Emergency List length error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_VerifyEmergencyNumListLen_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }

    return NAS_EMM_SUCC;
}
VOS_UINT32  NAS_EMM_DecodeEmergencyNumList
(
    VOS_UINT8   *pRcvMsg,
    VOS_UINT32  *pulIndex,
    VOS_VOID    *pstEmergencyListStru,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp
)
{
    VOS_UINT8                           ucTotalLen          = NAS_EMM_NULL;
    VOS_UINT8                           ucTmpLen            = NAS_EMM_NULL;
    VOS_UINT8                           ucEmerNumLen        = NAS_EMM_NULL;
    VOS_UINT8                           ucEmerNumAmout      = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulLoop              = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;
    NAS_LMM_EMERGENCY_NUM_LIST_STRU    *pstTmpEmergencyListStru  = (NAS_LMM_EMERGENCY_NUM_LIST_STRU *)pstEmergencyListStru;
    LMM_MM_EMERGENCY_NUM_STRU          *pstEmergencyNum     = VOS_NULL_PTR;

    (VOS_VOID)enMsgTp;

    /*��ڲ������*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeEmergencyNumList:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeEmergencyNumList_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /*ȡ������*/
    ucTotalLen = pucTmpMsg[ulSum];

    /*�жϳ����Ƿ����Э��*/
    if (NAS_EMM_FAIL == NAS_EMM_VerifyEmergencyNumListLen(pucTmpMsg))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeEmergencyNumList:NAS_EMM_VerifyEmergencyNumListLen FAIL!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeEmergencyNumList_ENUM,LNAS_FAIL);
        /*��������*/
        ulSum++;
        ulSum += ucTotalLen;
        /*��¼����*/
        *pulIndex = ulSum;
        return NAS_EMM_SUCC;
    }

    /*��������*/
    ulSum++;

    while (ucTotalLen > ucTmpLen)
    {
        /* Length of Emergency Number information */
        ucEmerNumLen = pucTmpMsg[ulSum++];

        pstEmergencyNum = &pstTmpEmergencyListStru->astEmergencyNumList[ucEmerNumAmout];

        /* ��ȥCATAGORY�ĳ��� */
        pstEmergencyNum->ucEmcNumLen = ucEmerNumLen - 1;
        pstEmergencyNum->ucCategory = pucTmpMsg[ulSum++] & 0x1f;
        for (ulLoop = NAS_EMM_NULL; ulLoop < pstEmergencyNum->ucEmcNumLen; ulLoop++)
        {
            pstEmergencyNum->aucEmcNum[ulLoop] = pucTmpMsg[ulSum++];
        }

        /* ��������������1 */
        ucEmerNumAmout++;

        /* �ۻ����н���������ĳ��� */
        ucTmpLen = ucTmpLen + ucEmerNumLen + 1;
    }

    pstTmpEmergencyListStru->ucEmergencyNumAmount = ucEmerNumAmout;

    /*��¼����*/
    *pulIndex = ulSum;

    return NAS_EMM_SUCC;
}
VOS_UINT32  NAS_EMM_DecodeEpsNetFeatureSupport
(
    VOS_UINT8   *pRcvMsg,
    VOS_UINT32  *pulIndex,
    VOS_VOID    *pucNetFeature,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp
)
{
    VOS_UINT32                          ulNetFeatureLen     = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;
    VOS_UINT8                          *pucTmpNetFeature    = (VOS_UINT8 *)pucNetFeature;

    (VOS_VOID)enMsgTp;

    /*��ڲ������*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeEpsNetFeatureSupport:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeEpsNetFeatureSupport_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    /*ȡ������*/
    ulNetFeatureLen = pucTmpMsg[ulSum];

    /*�жϳ����Ƿ����Э��*/
    if(ulNetFeatureLen != NAS_EMM_CN_EPS_NET_FEATURE_LEN)
    {
        /* �׳���ά�ɲ� */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_EPSNETFEATURE_IE, EMM_CN_MSG_IE_LEN_INVALID, ulNetFeatureLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeEpsNetFeatureSupport:ERROR:EPS NET Feature length error!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeEpsNetFeatureSupport_ENUM,LNAS_ERROR);
        return NAS_EMM_FAIL;
    }

    /*��������*/
    ulSum++;

    *pucTmpNetFeature                   = pucTmpMsg[ulSum];

    ulSum ++;

    /*��¼����*/
    *pulIndex = ulSum;

    return NAS_EMM_SUCC;
}


VOS_UINT32  NAS_EMM_DecodeAdditionalUpdateRslt
(
    VOS_UINT8   *pRcvMsg,
    VOS_UINT32  *pulIndex,
    VOS_VOID    *pulUpRslt,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp
)
{
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  *pulTmpAddUpRslt =
                    (NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32 *)pulUpRslt;

    (VOS_VOID)enMsgTp;

    /*��ڲ������*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeAdditionalUpdateRslt:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeAdditionalUpdateRslt_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    pucTmpMsg[ulSum] = (pucTmpMsg[ulSum]& NAS_EMM_LOW_2_BITS_F);

    if (NAS_EMM_NULL == pucTmpMsg[ulSum])
    {
        *pulTmpAddUpRslt = NAS_LMM_ADDITIONAL_UPDATE_NO_INFO;
    }
    else if (0x01 == pucTmpMsg[ulSum])
    {
        *pulTmpAddUpRslt = NAS_LMM_ADDITIONAL_UPDATE_CSFB_NOT_PREFERED;
    }
    else if (0x02 == pucTmpMsg[ulSum])
    {
        *pulTmpAddUpRslt = NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY;
    }
    else
    {
        *pulTmpAddUpRslt = NAS_LMM_ADDITIONAL_UPDATE_BUTT;
    }

    ulSum ++;

    /*��¼����*/
    *pulIndex = ulSum;

    return NAS_EMM_SUCC;
}



VOS_UINT32  NAS_EMM_DecodeMsgCon(VOS_UINT8  *pRcvMsg,
                                        VOS_UINT32  *ulIndex,
                                    NAS_EMM_CN_MSGCON_STRU   *pstMsgConStru)
{
    VOS_UINT32                          i                   = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgConLen         = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulSum1               = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;

    NAS_EMM_CN_MSGCON_STRU             *pstTmpMsgConStru    = pstMsgConStru;

    /*��ڲ������*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeMsgCon:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeMsgCon_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }
    ulSum1 = ulSum+1;

    /*ȡ������*/
    ulMsgConLen = (pucTmpMsg[ulSum]<< NAS_EMM_MOVEMENT_8_BITS)
            | pucTmpMsg[ulSum1];

    ulSum++;

    if(NAS_EMM_NULL == ulMsgConLen)
    {
        /* �׳���ά�ɲ� */
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_ESMMSG_IE, EMM_CN_MSG_IE_LEN_INVALID, ulMsgConLen);
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeMsgCon:ERROR: No ESM Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeMsgCon_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }
    pstTmpMsgConStru->ulMsgLen = ulMsgConLen;

    /*�����������ȵ�3���ֽ�*/
    ulSum++;

    for(i = 0; i < ulMsgConLen; i++)
    {
        pstTmpMsgConStru->aucMsg[i] = pucTmpMsg[ulSum++];
    }

    *ulIndex = ulSum;

    return NAS_EMM_SUCC;
}


VOS_UINT32  NAS_EMM_DecodeEsmMsgCon
(
    VOS_UINT8   *pRcvMsg,
    VOS_UINT32  *pulIndex,
    VOS_VOID    *pulUpRslt,
    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp
)
{
    VOS_UINT32                          i                   = NAS_EMM_NULL;
    VOS_UINT32                          ulMsgConLen         = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT32                          ulSum1              = NAS_EMM_NULL;
    VOS_UINT8                          *pucTmpMsg           = pRcvMsg;

    NAS_EMM_CN_MSGCON_STRU             *pstTmpMsgConStru    = (NAS_EMM_CN_MSGCON_STRU *)pulUpRslt;

    (VOS_VOID)enMsgTp;

    /*��ڲ������*/
    if( NAS_EMM_NULL_PTR == pucTmpMsg)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeEsmMsgCon:ERROR: No Msg!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeEsmMsgCon_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    ulSum1 = ulSum+1;

    /*ȡ������*/
    ulMsgConLen = (pucTmpMsg[ulSum]<< NAS_EMM_MOVEMENT_8_BITS)
            | pucTmpMsg[ulSum1];

    ulSum++;

    if(NAS_EMM_NULL == ulMsgConLen)
    {
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_ESMMSG_IE, EMM_CN_MSG_IE_LEN_INVALID, ulMsgConLen);
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeEsmMsgCon_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }
    pstTmpMsgConStru->ulMsgLen = ulMsgConLen;

    /*�����������ȵ�3���ֽ�*/
    ulSum++;

    for(i = 0; i < ulMsgConLen; i++)
    {
        pstTmpMsgConStru->aucMsg[i] = pucTmpMsg[ulSum++];
    }

    /*��¼����*/
    *pulIndex = ulSum;

    return NAS_EMM_SUCC;
}



VOS_UINT32  NAS_EMM_DecodeTimer2(
                                        VOS_UINT8   *pucRcvMsg,
                                        VOS_UINT32  *pulIndex,
                                        VOS_VOID    *pulUpRslt,
                                        NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT32                          ulSum;
    VOS_UINT8                          *pucTmpMsg;
    VOS_UINT8                           ucTimeGap;
    NAS_EMM_TIMER_STRU                 *pstTmpTimer;
    VOS_UINT32                          ulMsgConLen;

    (VOS_VOID)enMsgTp;

    if((VOS_NULL == pucRcvMsg) ||
        (VOS_NULL == pulIndex) ||
        (VOS_NULL == pulUpRslt))
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeTimer2: input pointer is NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeTimer2_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    pucTmpMsg                           = pucRcvMsg;
    pstTmpTimer                         = (NAS_EMM_TIMER_STRU *)pulUpRslt;
    ulSum                               = NAS_EMM_NULL;

    /*ȡ����Ϣ����*/
    ulMsgConLen = pucTmpMsg[ulSum];

    /*������Ϣ����*/
    ulSum++;

    if(NAS_EMM_NULL == ulMsgConLen)
    {
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_TIMER2_IE, EMM_CN_MSG_IE_LEN_INVALID, ulMsgConLen);
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeTimer2_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*��ʱ�Ȳ����泤����Ϣ��������Ҫ�����*/

    /*ȡ��Timer unitֵ*/
    ucTimeGap = (VOS_UINT8)((pucTmpMsg[ulSum] & NAS_EMM_CN_HIGH_3_BIT)
                            >>NAS_EMM_MOVEMENT_5_BITS);

    if((ucTimeGap > NAS_EMM_TIMER_UNIT_6MINUTES) &&
       (ucTimeGap < NAS_EMM_TIMER_DEACTIVATE))
    {
        ucTimeGap = NAS_EMM_TIMER_UNIT_1MINUTE;
    }

    /*�������*/
    pstTmpTimer->ucUnit     = ucTimeGap;
    pstTmpTimer->ucTimerVal = pucTmpMsg[ulSum++] & NAS_EMM_CN_LOW_5_BIT;

    *pulIndex = ulSum;
    return NAS_EMM_SUCC;
}
VOS_UINT32  NAS_EMM_DecodeTimer(
                                    VOS_UINT8   *pucRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstTimer,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT32                          ulSum;
    VOS_UINT8                          *pucTmpMsg;
    VOS_UINT8                           ucTimeGap;
    NAS_EMM_TIMER_STRU                 *pstTmpTimer;

    (VOS_VOID)enMsgTp;

    if((VOS_NULL == pucRcvMsg) ||
        (VOS_NULL == pulIndex) ||
        (VOS_NULL == pstTimer))
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DecodeTimer: input pointer is NULL !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DecodeTimer_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    pucTmpMsg                           = pucRcvMsg;
    pstTmpTimer                         = (NAS_EMM_TIMER_STRU *)pstTimer;

    ulSum                               = NAS_EMM_NULL;
    /*ucTimeGap                           = NAS_EMM_NULL;*/


    /*ȡ��Timer unitֵ*/
    ucTimeGap = (VOS_UINT8)((pucTmpMsg[ulSum] & NAS_EMM_CN_HIGH_3_BIT)
                            >>NAS_EMM_MOVEMENT_5_BITS);

    if((ucTimeGap > NAS_EMM_TIMER_UNIT_6MINUTES) &&
       (ucTimeGap < NAS_EMM_TIMER_DEACTIVATE))
    {
        ucTimeGap = NAS_EMM_TIMER_UNIT_1MINUTE;
    }

    /*�������*/
    pstTmpTimer->ucUnit     = ucTimeGap;
    pstTmpTimer->ucTimerVal = pucTmpMsg[ulSum++] & NAS_EMM_CN_LOW_5_BIT;

    *pulIndex = ulSum;
    return NAS_EMM_SUCC;
}

VOS_UINT32  NAS_EMM_DecodeBearerTxtStus(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstBTxtStus,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    VOS_UINT8                          *pTmpRcvMsg          = pRcvMsg;
    VOS_UINT32                          ulEpsbIdNum         = NAS_EMM_NULL;
    VOS_UINT32                          i                   = NAS_EMM_NULL;
    VOS_UINT32                          ulSum               = NAS_EMM_NULL;
    VOS_UINT16                          usEPSstatus         = NAS_EMM_NULL;
    NAS_EMM_EPS_BEARER_STATUS_STRU      *pstTmpBTxtStus     = (NAS_EMM_EPS_BEARER_STATUS_STRU *)pstBTxtStus;

    (VOS_VOID)enMsgTp;

    /*����EPS bearer context �����ֽ�*/
    ulSum++;

    /*ȡ�ó��ص�16λ��.������EPS bearer context*/
    usEPSstatus = pTmpRcvMsg[ulSum++] & NAS_EMM_CN_HIGH_3_BIT;
    usEPSstatus = (VOS_UINT16)(usEPSstatus |
                               ((pTmpRcvMsg[ulSum++] << NAS_EMM_MOVEMENT_8_BITS)));

    /*24.301  9.9.2.1.1
       EBI(0) - EBI(4):
       Bits 0 to 4 of octet 3 are spare and shall be coded as zero.
       -------------------------------------------------------------------------------
        (BIT8)|   (BIT7)|   (BIT6)|   (BIT5)|   (BIT4)|   (BIT3)|   (BIT2)|   (BIT1)
       -------------------------------------------------------------------------------
        EBI 8)|   EBI 7)|   EBI 6)|   EBI 5)|   EBI 4)|   EBI 3)|  EBI  2)|   EBI 1
       -------------------------------------------------------------------------------
        EBI 15|   EBI 14|   EBI 13|   EBI 12|   EBI 11|   EBI 10|  EBI  9)|   EBI 8
       -------------------------------------------------------------------------------*/
    for(i = 5; i < (EMM_ESM_MAX_EPS_BEARER_NUM + 5); i++)
    {
        if(1 == ((usEPSstatus >> i) & 1))
        {
            pstTmpBTxtStus->aulEsmEpsId[ulEpsbIdNum] = i;
            NAS_EMM_PUBU_LOG2_INFO("i = , ID=", i,pstTmpBTxtStus->aulEsmEpsId[ulEpsbIdNum]);
            TLPS_PRINT2LAYER_INFO2(NAS_EMM_DecodeBearerTxtStus_ENUM,LNAS_FUNCTION_LABEL1,
                                        i,pstTmpBTxtStus->aulEsmEpsId[ulEpsbIdNum]);
            ulEpsbIdNum++;
        }

    }

    pstTmpBTxtStus->ulEpsIdNum  = ulEpsbIdNum;

    NAS_EMM_PUBU_LOG1_INFO("NUM = ", pstTmpBTxtStus->ulEpsIdNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_DecodeBearerTxtStus_ENUM,LNAS_FUNCTION_LABEL2,pstTmpBTxtStus->ulEpsIdNum);

    *pulIndex = ulSum;
    return NAS_EMM_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeEmmCau
 Description     : EmmCau��Ԫ��������
 Input           : pRcvMsg
                   ulIndex
                   pstCnMsgStru
                   enMsgTp
 Output          : pstCnMsgStru pulIndex
 Return          : �����Ƿ�ɹ�
 History         :
    1.shiconyong      2009-9-28  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeEmmCau(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstCnMsgStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    NAS_EMM_CN_CAUSE_ENUM_UINT8 *pucEmmCau = (NAS_EMM_CN_CAUSE_ENUM_UINT8*)pstCnMsgStru;

    (VOS_VOID)enMsgTp;

    *pulIndex = 1;
    *pucEmmCau = NAS_EMM_DecodeCnEmmCause(pRcvMsg[0]);
    return NAS_EMM_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeKSIasme
 Description     : KSIasme��Ԫ��������
 Input           : pRcvMsg
                   ulIndex
                   pstCnMsgStru
                   enMsgTp
 Output          : pstCnMsgStru pulIndex
 Return          : �����Ƿ�ɹ�
 History         :
    1.shiconyong      2009-10-22  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeKSIasme(
                                    VOS_UINT8   *pRcvMsg,
                                    VOS_UINT32  *pulIndex,
                                    VOS_VOID    *pstCnMsgStru,
                                    NAS_EMM_CN_MSG_TYPE_ENUM_UINT8  enMsgTp)
{
    NAS_EMM_CN_KSIASME_UINT8 *pucKSIasme = (NAS_EMM_CN_KSIASME_UINT8*)pstCnMsgStru;

    (VOS_VOID)enMsgTp;

    *pulIndex = 1;
    *pucKSIasme = pRcvMsg[0] & NAS_EMM_DECODE_OCTET_USE_LOW_4_BITS;
    return NAS_EMM_SUCC;
}


VOS_UINT32  NAS_EMM_DecodeNwName(
                                        NAS_EMM_CN_NETWORK_NAME_STRU   *pstNwName,
                                        VOS_UINT8                      *pTmpRcvMsg,
                                        VOS_UINT32                     *pulIndex)
{
    VOS_UINT32                          ulIndex = (*pulIndex);

    /*���ش洢�ĳ���ֻ���������Ʊ�������ݣ�������CodeScheme����Ԫ����Ҫ��ȥ1*/
    pstNwName->ucMsgLen                = pTmpRcvMsg[ulIndex]-NAS_EMM_MOVEMENT_1_BYTE;

    /*��������*/
    ulIndex++;

    pstNwName->ucNumOfSpareInLastByte  = ((pTmpRcvMsg[ulIndex]) & NAS_EMM_LOW_3_BITS_F);
    pstNwName->ucAddCI                 = (((pTmpRcvMsg[ulIndex]) & NAS_EMM_FOURTH_BITS_F) >> NAS_EMM_MOVEMENT_3_BITS);
    pstNwName->ucCodingScheme          = (((pTmpRcvMsg[ulIndex]) & NAS_EMM_HIGH_3_BITS_F) >> NAS_EMM_MOVEMENT_4_BITS);

    if (NAS_EMM_CODESCHM_RESERVED <= pstNwName->ucCodingScheme)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeNwName: Coding Scheme is out of range!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeNwName_ENUM,LNAS_FUNCTION_LABEL1);
    }

    /*����Code Scheme����Ԫ*/
    ulIndex++;

    /* �����ı����� */
    NAS_LMM_MEM_CPY(                       pstNwName->aucMsg,
                                          &(pTmpRcvMsg[ulIndex]),
                                          (pstNwName->ucMsgLen));

    *pulIndex = ulIndex + pstNwName->ucMsgLen;

    return NAS_EMM_SUCC;
}


VOS_UINT32  NAS_EMM_DecodeTimeZone(
                                        NAS_EMM_CN_TIMEZONE_STRU       *pstTimeZone,
                                        VOS_UINT8                      *pTmpRcvMsg,
                                        VOS_UINT32                     *pulIndex)
{
    VOS_UINT32                          ulIndex = (*pulIndex);

    pstTimeZone->ucTimeZone    = ((pTmpRcvMsg[ulIndex]& NAS_EMM_LOW_3_BITS_F) * 10)
                               +((pTmpRcvMsg[ulIndex]& NAS_EMM_HIGH_HALF_BYTE_F)>>NAS_EMM_MOVEMENT_4_BITS);

    /* ��ʱ�����н��� */
    if (pTmpRcvMsg[ulIndex] & NAS_EMM_FOURTH_BITS_F)
    {
        pstTimeZone->enPosNegTimeZone = NAS_LMM_TIMEZONE_NAGETIVE;
    }
    else
    {
        pstTimeZone->enPosNegTimeZone = NAS_LMM_TIMEZONE_POSITIVE;
    }

    *pulIndex = ++ulIndex;

    return NAS_EMM_SUCC;
}
VOS_UINT32  NAS_EMM_DecodeLocalTimeZone(
                                        NAS_EMM_CN_TIMEZONE_UNITIME_STRU *pstLocalTZ,
                                        VOS_UINT8                        *pTmpRcvMsg,
                                        VOS_UINT32                       *pulIndex)
{
    VOS_UINT32                          ulIndex = (*pulIndex);

    pstLocalTZ->ucYear    = (VOS_UINT8 )NAS_EMM_DECODE_LOCAL_TIME(pTmpRcvMsg[ulIndex]);
    ulIndex++;

    pstLocalTZ->ucMonth   = (VOS_UINT8 )NAS_EMM_DECODE_LOCAL_TIME(pTmpRcvMsg[ulIndex]);
    ulIndex++;

    pstLocalTZ->ucDay     = (VOS_UINT8 )NAS_EMM_DECODE_LOCAL_TIME(pTmpRcvMsg[ulIndex]);
    ulIndex++;

    pstLocalTZ->ucHour    = (VOS_UINT8 )NAS_EMM_DECODE_LOCAL_TIME(pTmpRcvMsg[ulIndex]);
    ulIndex++;

    pstLocalTZ->ucMinute  = (VOS_UINT8 )NAS_EMM_DECODE_LOCAL_TIME(pTmpRcvMsg[ulIndex]);
    ulIndex++;

    pstLocalTZ->ucSecond  = (VOS_UINT8 )NAS_EMM_DECODE_LOCAL_TIME(pTmpRcvMsg[ulIndex]);
    ulIndex++;

    (VOS_VOID)NAS_EMM_DecodeTimeZone(&(pstLocalTZ->stTimeZone),
                                     pTmpRcvMsg,
                                     &ulIndex);

    *pulIndex = ulIndex;

    return NAS_EMM_SUCC;
}


VOS_UINT32  NAS_EMM_DecodeDaylight(
                                        NAS_LMM_DAYLIGHT_SAVE_TIME_ENUM_UINT8       *pstDaylight,
                                        VOS_UINT8                      *pTmpRcvMsg,
                                        VOS_UINT32                     *pulIndex)
{
    VOS_UINT32                          ulIndex = (*pulIndex);

    /* ��ʱ�����н��� */
    if ((pTmpRcvMsg[ulIndex] & NAS_EMM_LOW_2_BITS_F) < NAS_LMM_DAYLIGHT_BUTT)
    {
        *pstDaylight = pTmpRcvMsg[ulIndex];
    }
    else
    {
        /*���������������򲻸���ԭ��ֵ*/
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_DAYLIGHT_IE, EMM_CN_MSG_IE_TYPE_INVALID, (pTmpRcvMsg[ulIndex] & NAS_EMM_LOW_2_BITS_F));
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeDaylight_ENUM,LNAS_FUNCTION_LABEL1);
    }

    *pulIndex = ++ulIndex;

    return NAS_EMM_SUCC;
}



VOS_UINT32  NAS_EMM_DecodeCnEmmInfoMsg(LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                                      VOS_UINT32                 ulLength,
                                                      NAS_EMM_CN_MSG_STRU       *pstCnMsgStru)
{
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStruIE      = pstCnMsgStru;
    VOS_UINT32                          ulCnFullNameLen     = NAS_EMM_NULL;
    VOS_UINT32                          ulCnShortNameLen     = NAS_EMM_NULL;



    NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnEmmInfoMsg is enter! ");
    TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnEmmInfoMsg_ENUM,LNAS_ENTRY);

    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulLength;
    ulMsgSize  = pRcvMsg->ulNasMsgSize;

    /*������Ϣ����*/
    ucMsgType  = pTmpRcvMsg[ulIndex];
    pstCnMsgStruIE->ulCnMsgType = ucMsgType;

    /*������Ϣ����*/
    ulIndex++;

    /*�ж��Ƿ��Ѿ�����*/
    if (ulMsgSize <= (ulIndex + ulLength))
    {
        return NAS_EMM_SUCC;
    }

    /* �������������� */
    if (NAS_EMM_CN_FULL_NAME == pTmpRcvMsg[ulIndex])
    {
        /*����Network IEI�ֽ�*/
        ulIndex++;

        /*�жϳ����Ƿ�Ϸ�,NAS_EMM_IE_L_LENGTH��ʶ������Ԫ�� 1 BYTE*/
        if (ulMsgSize < (pTmpRcvMsg[ulIndex] + ulIndex + ulLength + NAS_EMM_IE_L_LENGTH))
        {
            return NAS_EMM_SUCC;
        }

        /* ���� Full Name ��ʶ */
        pstCnMsgStruIE->uCnMsgStru.stEmmInfo.bitOpFullName = NAS_EMM_BIT_SLCT;

        /* �Ϻ�Ҫ��ֻ�ṩ�����·�����������˲���Э�����룬�������������������40�ֽ� */
        if((MMC_LMM_MAX_OPER_LONG_NAME_LEN-1) <= pTmpRcvMsg[ulIndex])
        {

            /* ����Ԫ���ȴ��ڵ���39�����ܹ�ֻ����40�ֽ�(�����˳���) */
            ulCnFullNameLen = MMC_LMM_MAX_OPER_LONG_NAME_LEN;
        }
        else
        {
            /* �������ܳ���ҪΪ��Ԫ���ȼ�1 */
            ulCnFullNameLen = pTmpRcvMsg[ulIndex]+1;
        }

        NAS_LMM_MEM_CPY(pstCnMsgStruIE->uCnMsgStru.stEmmInfo.aucOperatorNameLong,
                        &pTmpRcvMsg[ulIndex],
                        ulCnFullNameLen);

        /* ����Full name��Ԫ */
        ulIndex += pTmpRcvMsg[ulIndex]+1;


        NAS_EMM_PUBU_LOG_INFO("Full NetName: ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnEmmInfoMsg_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                            pstCnMsgStru->uCnMsgStru.stEmmInfo.aucOperatorNameLong,
                            ulCnFullNameLen);




    }

    /*�ж��Ƿ��Ѿ�����*/
    if (ulMsgSize <= (ulIndex + ulLength))
    {
        return NAS_EMM_SUCC;
    }

    /* ���������� */
    if(NAS_EMM_CN_SHORT_NAME == pTmpRcvMsg[ulIndex])
    {
        /*����Network IEI�ֽ�*/
        ulIndex++;

        /*�жϳ����Ƿ�Ϸ�,NAS_EMM_IE_L_LENGTH��ʶ������Ԫ�� 1 BYTE*/
        /*lint -e961*/
        if (ulMsgSize < (pTmpRcvMsg[ulIndex] + ulIndex + ulLength + NAS_EMM_IE_L_LENGTH))
        {
        /*lint +e961*/
            return NAS_EMM_SUCC;
        }

        /* ����ShortName��ʶ */
        pstCnMsgStruIE->uCnMsgStru.stEmmInfo.bitOpShortName = NAS_EMM_BIT_SLCT;

        /* �Ϻ�Ҫ��ֻ�ṩ�����·�����������˲���Э�����룬�������������������36�ֽ� */
        if((MMC_LMM_MAX_OPER_SHORT_NAME_LEN-1) <= pTmpRcvMsg[ulIndex])
        {
            /* ����Ԫ���ȴ��ڵ���35�����ܹ�ֻ����36�ֽ�(�����˳���) */
            ulCnShortNameLen = MMC_LMM_MAX_OPER_SHORT_NAME_LEN;
        }
        else
        {
            /* �������ܳ���ҪΪ��Ԫ���ȼ�1 */
            ulCnShortNameLen = pTmpRcvMsg[ulIndex]+1;
        }

        NAS_LMM_MEM_CPY(pstCnMsgStruIE->uCnMsgStru.stEmmInfo.aucOperatorNameShort,
                        &pTmpRcvMsg[ulIndex],
                        ulCnShortNameLen);

        /* ����Short name��Ԫ */
        ulIndex += pTmpRcvMsg[ulIndex]+1;


        NAS_EMM_PUBU_LOG_INFO("Full NetName: ");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnEmmInfoMsg_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                            pstCnMsgStru->uCnMsgStru.stEmmInfo.aucOperatorNameShort,
                            ulCnShortNameLen);




    }

    /*�ж��Ƿ��Ѿ�����*/
    if (ulMsgSize <= (ulIndex + ulLength))
    {
        return NAS_EMM_SUCC;
    }

    /* ���뱾��ʱ�� */
    if (NAS_EMM_LOCAL_TIME_ZONE == pTmpRcvMsg[ulIndex])
    {
        /*�жϳ����Ƿ�Ϸ�*/
        if (ulMsgSize < (ulIndex + ulLength + NAS_EMM_TIMEZONE_LEN))
        {
            return NAS_EMM_SUCC;
        }

        /* ���ñ�ʶλ */
        pstCnMsgStruIE->uCnMsgStru.stEmmInfo.bitOpLocTimeZone            = NAS_EMM_BIT_SLCT;

        /*���� IEI�ֽ�*/
        ulIndex++;

        /*����*//*Э�����Ϊ����Ϊ15���ӣ�GCF����Ϊ1Сʱ,����������*/
        (VOS_VOID)NAS_EMM_DecodeTimeZone(&(pstCnMsgStruIE->uCnMsgStru.stEmmInfo.stLocTimeZone),
                                         pTmpRcvMsg,
                                         &ulIndex);
    }

    if (ulMsgSize <= (ulIndex + ulLength))
    {
        return NAS_EMM_SUCC;
    }

    NAS_EMM_PUBU_LOG_INFO("TIMEZONE: ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnEmmInfoMsg_ENUM,LNAS_FUNCTION_LABEL3);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                       (VOS_UINT8 *)&(pstCnMsgStru->uCnMsgStru.stEmmInfo.stLocTimeZone),
                       sizeof(NAS_EMM_CN_TIMEZONE_STRU));

    /* ���뱾��ʱ�� */
    if(NAS_EMM_UNIVTIME_LOCALTIMEZONE == pTmpRcvMsg[ulIndex])
    {
        /*�жϳ����Ƿ�Ϸ�*/
        if (ulMsgSize < (ulIndex + ulLength + NAS_EMM_TIME_TIMEZONE_LEN))
        {
            return NAS_EMM_SUCC;
        }

        /*���� IEI�ֽ�*/
        ulIndex++;

        /*����֧��LocTimeZone*/
        pstCnMsgStruIE->uCnMsgStru.stEmmInfo.bitOpUniTimeLocTimeZone     = NAS_EMM_BIT_SLCT;

        /*��ÿ�����Ը�ֵ*/
        (VOS_VOID)NAS_EMM_DecodeLocalTimeZone(&(pstCnMsgStruIE->uCnMsgStru.stEmmInfo.stTimeZoneAndTime),
                                              pTmpRcvMsg,
                                              &ulIndex);

    }

    NAS_EMM_PUBU_LOG_INFO("TIMEZONE_UNITIME: ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnEmmInfoMsg_ENUM,LNAS_FUNCTION_LABEL4);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                       (VOS_UINT8 *)&(pstCnMsgStru->uCnMsgStru.stEmmInfo.stTimeZoneAndTime),
                       sizeof(NAS_EMM_CN_TIMEZONE_UNITIME_STRU));

    if (ulMsgSize < (ulIndex + ulLength + NAS_EMM_DAYLIGHTTIME))
    {
        return NAS_EMM_SUCC;
    }

    /* ����Daylightʱ�� */
    if(NAS_EMM_CN_DAYLIGHT_SAVE_TIME == pTmpRcvMsg[ulIndex])
    {
        /*���� IEI�ֽ�*/
        ulIndex++;

        /*���� Length �ֽ�*/
        ulIndex++;

        /*���ñ�ʶ*/
        pstCnMsgStruIE->uCnMsgStru.stEmmInfo.bitOpDaylightTime = NAS_EMM_BIT_SLCT;

        (VOS_VOID)NAS_EMM_DecodeDaylight(&(pstCnMsgStruIE->uCnMsgStru.stEmmInfo.enDaylightSavingTime),
                                         pTmpRcvMsg,
                                         &ulIndex);
    }

    NAS_EMM_PUBU_LOG_INFO("DAYLIGHT: ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnEmmInfoMsg_ENUM,LNAS_FUNCTION_LABEL5);
    /*lint -e961*/
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                       (VOS_UINT8 *)&(pstCnMsgStru->uCnMsgStru.stEmmInfo.enDaylightSavingTime),
                       sizeof(NAS_LMM_DAYLIGHT_SAVE_TIME_ENUM_UINT8));
    /*lint +e961*/

    return NAS_EMM_SUCC;
}


VOS_UINT32  NAS_EMM_DecodeCnEmmStatusMsg(LRRC_LNAS_MSG_STRU           *pRcvMsg,
                                                         VOS_UINT32                  ulLength,
                                                         NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    VOS_UINT8                           ucMsgType           = NAS_EMM_NULL;

    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulLength;

    /*������Ϣ����*/
    ucMsgType  = pTmpRcvMsg[ulIndex];
    pstCnMsgStru->ulCnMsgType = ucMsgType;

    /*������Ϣ����*/
    ulIndex++;

    pstCnMsgStru->uCnMsgStru.stEmmStatus.ucEmmCause = pTmpRcvMsg[ulIndex];

    return NAS_EMM_SUCC;

}
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnDownlinkNasTransportMsg
 Description     : ����downlink nas transport��Ϣ��������ʱֻ֧��sms����
 Input           : pRcvMsg
 Output          : pstCnMsgStru
 Return          : �����Ƿ�ɹ�
 History         :
    1.FTY       2011-11-16  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnDownlinkNasTransportMsg(LRRC_LNAS_MSG_STRU          *pRcvMsg,
                                        VOS_UINT32                  ulLength,
                                        NAS_EMM_CN_MSG_STRU        *pstCnMsgStru)
{
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;

    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulLength;

    /*������Ϣ����*/
    pstCnMsgStru->ulCnMsgType  = pTmpRcvMsg[ulIndex];

    /*������Ϣ����*/
    ulIndex++;

    /*��ȡSMS��Ϣ����*/
    pstCnMsgStru->uCnMsgStru.stDownlinkNasTransport.ucDownlinkNasTransportLen = pTmpRcvMsg[ulIndex];

    /*����SMS��Ϣ����*/
    ulIndex++;

    /*��ȡSMS��Ϣ*/
    NAS_LMM_MEM_CPY( pstCnMsgStru->uCnMsgStru.stDownlinkNasTransport.aucDownlinkNasTransportMsg,
                    &(pTmpRcvMsg[ulIndex]),
                    pstCnMsgStru->uCnMsgStru.stDownlinkNasTransport.ucDownlinkNasTransportLen);

    return NAS_EMM_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCli
 Description     : ����CLI��Ԫ
 Input           : pRcvMsg
                   ulLength
 Output          : pstCsSerNotifications
                   pulIndex
 Return          : �����Ƿ�ɹ�
 History         :
    1.lihong00150010       2012-02-22  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCli
(
    LRRC_LNAS_MSG_STRU                  *pRcvMsg,
    VOS_UINT32                           ulLength,
    VOS_UINT32                          *pulIndex,
    NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU *pstCsSerNotification
)
{
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT8                          *pTmpRcvMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT32                          ulDecodedLenBefore  = ulLength + (*pulIndex);

    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulDecodedLenBefore;
    ulMsgSize  = pRcvMsg->ulNasMsgSize;

    /*����Network IEI�ֽ�*/
    ulIndex++;

    /* �ж�CLI�ĳ���λ�ڡ�1-12�� */
    if ((pTmpRcvMsg[ulIndex] < NAS_EMM_CLI_MIN_LEN)
        || (pTmpRcvMsg[ulIndex] > NAS_EMM_CLI_MAX_LEN))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCli:CLI LEN Illegal!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCli_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /*�жϳ����Ƿ�Ϸ�*/
    if (ulMsgSize < (pTmpRcvMsg[ulIndex] + ulIndex + ulDecodedLenBefore + NAS_EMM_IE_L_LENGTH))
    {
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_CLI_IE, EMM_CN_MSG_IE_LEN_INVALID, ulMsgSize);
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCli_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }

    pstCsSerNotification->bitOpCli = NAS_EMM_BIT_SLCT;
    pstCsSerNotification->ucCliLength = pTmpRcvMsg[ulIndex++];
    NAS_LMM_MEM_CPY(pstCsSerNotification->aucCliValue,
                    &pTmpRcvMsg[ulIndex],
                    pstCsSerNotification->ucCliLength);
    ulIndex += pstCsSerNotification->ucCliLength;
    *pulIndex = *pulIndex + ulIndex;

    return NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_EMM_DecodeLcsClientId
 Description     : ����LCS CLIENT IDENTIFIER��Ԫ
 Input           : pRcvMsg
                   ulLength
 Output          : pstCsSerNotifications
                   pulIndex
 Return          : �����Ƿ�ɹ�
 History         :
    1.lihong00150010       2012-02-22  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeLcsClientId
(
    LRRC_LNAS_MSG_STRU                  *pRcvMsg,
    VOS_UINT32                           ulLength,
    VOS_UINT32                          *pulIndex,
    NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU *pstCsSerNotification
)
{
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT8                          *pTmpRcvMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT32                          ulDecodedLenBefore  = ulLength + (*pulIndex);

    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulDecodedLenBefore;
    ulMsgSize  = pRcvMsg->ulNasMsgSize;

    /*����Network IEI�ֽ�*/
    ulIndex++;

    /* �ж�CLI�ĳ���λ�ڡ�1-255�� */
    if (pTmpRcvMsg[ulIndex] < NAS_EMM_LCS_CLIENT_ID_MIN_LEN)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeLcsClientId:LCS CLIENT ID Illegal!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeLcsClientId_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SUCC;
    }

    /*�жϳ����Ƿ�Ϸ�*/
    if (ulMsgSize < (pTmpRcvMsg[ulIndex] + ulIndex + ulDecodedLenBefore + NAS_EMM_IE_L_LENGTH))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeLcsClientId:LCS CLIENT ID is too long!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeLcsClientId_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_SUCC;
    }

    pstCsSerNotification->bitOpLcsClientId = NAS_EMM_BIT_SLCT;
    pstCsSerNotification->ucLcsClientIdLen = pTmpRcvMsg[ulIndex++];
    NAS_LMM_MEM_CPY(pstCsSerNotification->aucLcsClientId,
                    &pTmpRcvMsg[ulIndex],
                    pstCsSerNotification->ucLcsClientIdLen);
    ulIndex += pstCsSerNotification->ucLcsClientIdLen;
    *pulIndex = *pulIndex + ulIndex;

    return NAS_EMM_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_EMM_DecodeCnCsSerNotification
 Description     : ����CS SERVICE NOTIFICATION��Ϣ
 Input           : pRcvMsg
 Output          : pstCnMsgStru
 Return          : �����Ƿ�ɹ�
 History         :
    1.lihong00150010       2012-02-21  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_DecodeCnCsSerNotification
(
    LRRC_LNAS_MSG_STRU                 *pRcvMsg,
    VOS_UINT32                          ulLength,
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStru
)
{
    VOS_UINT32                          ulMsgSize           = NAS_EMM_NULL;
    VOS_UINT32                          ulIndex             = NAS_EMM_NULL;
    VOS_UINT8                          *pTmpRcvMsg          = NAS_EMM_NULL;
    NAS_EMM_CN_CS_SER_NOTIFICAIOTN_STRU *pstCsSerNotification = VOS_NULL_PTR;

    pTmpRcvMsg = pRcvMsg->aucNasMsg + ulLength;
    ulMsgSize  = pRcvMsg->ulNasMsgSize;

    /* ������Ϣ���� */
    pstCnMsgStru->ulCnMsgType  = pTmpRcvMsg[ulIndex];

    /* ������Ϣ���� */
    ulIndex++;

    pstCsSerNotification = &pstCnMsgStru->uCnMsgStru.stCsSerNotification;

    pstCsSerNotification->ucPagingIdenity = pTmpRcvMsg[ulIndex++] & NAS_EMM_BIT_1;

    /* �ж��Ƿ��Ѿ�����,CLI��СΪ3 */
    if (ulMsgSize <= (ulIndex + ulLength + 2))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnCsSerNotification:CLI IE LEN <=2!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnCsSerNotification_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_SUCC;
    }

    /* �ж��Ƿ�Я��CLI */
    if (NAS_EMM_MSG_CLI_IEI == pTmpRcvMsg[ulIndex])
    {
        if (NAS_EMM_FAIL == NAS_EMM_DecodeCli(  pRcvMsg, ulLength,
                                                &ulIndex, pstCsSerNotification))
        {
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnCsSerNotification:NAS_EMM_DecodeCli failed!");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnCsSerNotification_ENUM,LNAS_FUNCTION_LABEL2);
            return NAS_EMM_SUCC;
        }
    }

    /* �ж��Ƿ��Ѿ�����,SS CODE��СΪ2 */
    if (ulMsgSize <= (ulIndex + ulLength + 1))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnCsSerNotification:SS code IE LEN <=1!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnCsSerNotification_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_SUCC;
    }

    /* �ж��Ƿ�Я��SS COE */
    if (NAS_EMM_MSG_SS_CODE_IEI == pTmpRcvMsg[ulIndex])
    {
        /*����Network IEI�ֽ�*/
        ulIndex++;

        pstCsSerNotification->bitOpSsCode = NAS_EMM_BIT_SLCT;
        pstCsSerNotification->ucSsCodeValue = pTmpRcvMsg[ulIndex++];
    }

    /* �ж��Ƿ��Ѿ�����,LCS INDICATOR��СΪ2 */
    if (ulMsgSize <= (ulIndex + ulLength + 1))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnCsSerNotification:LCS INDICATOR IE LEN <=1!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnCsSerNotification_ENUM,LNAS_FUNCTION_LABEL4);
        return NAS_EMM_SUCC;
    }

    /* �ж��Ƿ�Я��LCS INDICATOR */
    if (NAS_EMM_MSG_LCS_INDICATOR_IEI == pTmpRcvMsg[ulIndex])
    {
        /*����Network IEI�ֽ�*/
        ulIndex++;

        pstCsSerNotification->bitOpLcsIndicator = NAS_EMM_BIT_SLCT;
        pstCsSerNotification->ucLcsIndicatorValue = pTmpRcvMsg[ulIndex++];
    }

    /* �ж��Ƿ��Ѿ�����,LCS CLIENT ID��СΪ3 */
    if (ulMsgSize <= (ulIndex + ulLength + 2))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnCsSerNotification:LCS CLIENT ID IE LEN <=2!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnCsSerNotification_ENUM,LNAS_FUNCTION_LABEL5);
        return NAS_EMM_SUCC;
    }

    /* �ж��Ƿ�Я��LCS CLIENT ID */
    if (NAS_EMM_MSG_LCS_CLIENT_ID_IEI == pTmpRcvMsg[ulIndex])
    {
        if (NAS_EMM_FAIL == NAS_EMM_DecodeLcsClientId(  pRcvMsg, ulLength,
                                                        &ulIndex, pstCsSerNotification))
        {
            NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnCsSerNotification:NAS_EMM_DecodeLcsClientId failed!");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnCsSerNotification_ENUM,LNAS_FUNCTION_LABEL6);
            return NAS_EMM_SUCC;
        }
    }

    return NAS_EMM_SUCC;
}


VOS_UINT32 NAS_EMM_DecodeGenericMessageContainer(VOS_UINT8 *pucMsgBuf,
                                                 VOS_UINT32 *pulLength,
                                                 NAS_EMM_GENERIC_MESSAGE_CONTAINER_STRU *pstDstMsgStrct)
{
    VOS_UINT32 ulIndex = 0;

    if ((VOS_NULL_PTR == pucMsgBuf) || (VOS_NULL_PTR == pstDstMsgStrct))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeGenericMessageContainer: invalid parameter");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeGenericMessageContainer_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    *pulLength = 0;

    /* save generic message container contents length */
    pstDstMsgStrct->usMsgLen = (pucMsgBuf[ulIndex] << NAS_EMM_MOVEMENT_8_BITS) + pucMsgBuf[ulIndex + 1];
    ulIndex += 2;

    if (pstDstMsgStrct->usMsgLen > NAS_EMM_CN_MSGCON_MAX_LEN)
    {
        pstDstMsgStrct->usMsgLen = NAS_EMM_CN_MSGCON_MAX_LEN;
    }

    /* save generic message container content */
    NAS_LMM_MEM_CPY(pstDstMsgStrct->aucMsg, pucMsgBuf + ulIndex, pstDstMsgStrct->usMsgLen);
    ulIndex += pstDstMsgStrct->usMsgLen;

    *pulLength = ulIndex;

    return NAS_EMM_SUCC;
}


VOS_UINT32 NAS_EMM_DecodeAdditionalInfo(VOS_UINT8 *pucMsgBuf,
                                        VOS_UINT32 *pulLength,
                                        NAS_EMM_ADDITIONAL_INFOR_STRU *pstDstMsgStrct)
{
    VOS_UINT32 ulIndex = 0;

    if ((VOS_NULL_PTR == pucMsgBuf) || (VOS_NULL_PTR == pstDstMsgStrct))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeAdditionalInfo: invalid parameter");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeAdditionalInfo_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    *pulLength = 0;

    /* save Additional Information length */
    pstDstMsgStrct->ucMsgLen = pucMsgBuf[ulIndex];
    ulIndex++;

    NAS_LMM_MEM_CPY(pstDstMsgStrct->aucMsg, pucMsgBuf + ulIndex, pstDstMsgStrct->ucMsgLen);
    ulIndex += pstDstMsgStrct->ucMsgLen;

    *pulLength = ulIndex;

    return NAS_EMM_SUCC;
}
/*lint +e961*/
/*lint +e960*/
/*lint +e72*/

VOS_UINT32  NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg
(
    LRRC_LNAS_MSG_STRU                 *pstRcvMsg,
    VOS_UINT32                          ulIndex,
    NAS_EMM_CN_MSG_STRU                *pstCnMsgStru
)
{
    NAS_EMM_CN_DOWNLINK_GENERIC_NAS_TRANSPORT_STRU *pstDstMsgStruct = VOS_NULL_PTR;
    VOS_UINT32 ulEleLen = 0;
    VOS_UINT32 ulRet = NAS_EMM_SUCC;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg: entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg_ENUM,LNAS_ENTRY);

    if ((VOS_NULL_PTR == pstRcvMsg) || (VOS_NULL_PTR == pstCnMsgStru))
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg: invalid parameter");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg_ENUM,LNAS_NULL_PTR);
        return NAS_EMM_FAIL;
    }

    pstDstMsgStruct = &pstCnMsgStru->uCnMsgStru.stDownlinkGenericNasTransport;

    /* save and skip message type */
    pstCnMsgStru->ulCnMsgType  = pstRcvMsg->aucNasMsg[ulIndex];
    ulIndex++;

    /* Generic message container type */
    pstDstMsgStruct->ucContainerType = pstRcvMsg->aucNasMsg[ulIndex];
    ulIndex++;

    /* check length */
    if ((ulIndex + 3) > pstRcvMsg->ulNasMsgSize)
    {
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_GENERIC_MSG_CONT_IE, EMM_CN_MSG_IE_LEN_INVALID, pstRcvMsg->ulNasMsgSize);
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_FAIL;
    }

    /* decode Generic message container */
    ulRet = NAS_EMM_DecodeGenericMessageContainer(pstRcvMsg->aucNasMsg + ulIndex,
                                                 &ulEleLen,
                                                 &pstDstMsgStruct->stContainer);
    if (NAS_EMM_FAIL == ulRet)
    {
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg: decode GMC fail");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_FAIL;
    }
    ulIndex += ulEleLen;

    if (ulIndex > pstRcvMsg->ulNasMsgSize)
    {
        NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_GENERIC_MSG_CONT_IE, EMM_CN_MSG_IE_LEN_INVALID, ulIndex);
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_DecodeCnDownlinkGenericNasTransportMsg_ENUM,LNAS_FUNCTION_LABEL3);
        ulRet = NAS_EMM_FAIL;
    }
    else if (((pstRcvMsg->ulNasMsgSize - ulIndex) >= 3) &&
             (NAS_EMM_ADDITIONAL_INFO_IEI == pstRcvMsg->aucNasMsg[ulIndex]))
    {
        /* skip Additional information IEI */
        ulIndex++;

        /* decode Additional information */
        ulRet = NAS_EMM_DecodeAdditionalInfo(pstRcvMsg->aucNasMsg + ulIndex,
                                             &ulEleLen,
                                             &pstDstMsgStruct->stAdditionalInfo);
        if ((NAS_EMM_SUCC == ulRet) && ((ulIndex + ulEleLen) <= pstRcvMsg->ulNasMsgSize))
        {
            pstDstMsgStruct->bitOpAdditionalInfo = 1;
        }
        else
        {
            /* �׳���ά�ɲ� */
            NAS_LMM_SndOmLogCnMsgDecodeFail(NAS_EMM_CN_MSG_ADDITIONAL_IE, EMM_CN_MSG_IE_ADDITONAL_INFO_TOO_SHORT, (ulIndex + ulEleLen));
            ulRet = NAS_EMM_FAIL;
        }
    }
    else
    {
        /* loosely-input principle, we consider it as success case */
        ulRet = NAS_EMM_SUCC;
    }

    /* The following code is used for ST */
#ifdef PS_ITT_PC_TEST_NAS
    if (NAS_EMM_SUCC == ulRet)
    {
        NAS_EMM_UPLINK_GENERIC_NAS_TRANSPORT_STRU stUplinkMsg = {0};

        stUplinkMsg.ucContainerType     = pstDstMsgStruct->ucContainerType;
        stUplinkMsg.stContainer         = pstDstMsgStruct->stContainer;
        stUplinkMsg.bitOpAdditionalInfo = pstDstMsgStruct->bitOpAdditionalInfo;
        stUplinkMsg.stAdditionalInfo    = pstDstMsgStruct->stAdditionalInfo;

 //       NAS_EMM_SendMrrcDataReq_UplinkGenericNasTransport(&stUplinkMsg);
    }
#endif

    return ulRet;
}
VOS_VOID NAS_LMM_SndOmLogCnMsgDecodeFail
(
    NAS_EMM_CN_MSG_IE_TYPE_ENUM_UINT32                  enIeType,
    NAS_EMM_CN_MSG_DECODE_FAIL_CAUSE_ENUM_UINT32        enCause,
    VOS_UINT32                                          ulValue
)
{
    NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SndOmLogStateChange: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SndOmLogCnMsgDecodeFail_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET(pstMsg, 0, sizeof(NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = ID_NAS_LMM_OM_LOG_CN_MSG_DECODE_FAIL;
    pstMsg->enIeType = enIeType;
    pstMsg->enCause = enCause;
    pstMsg->ulValue = ulValue;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}


/*lint +e818*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

