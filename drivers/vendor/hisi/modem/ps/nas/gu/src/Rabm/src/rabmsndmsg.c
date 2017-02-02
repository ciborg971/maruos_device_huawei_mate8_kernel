
#include "rabminclude.h"
#include "AtRabmInterface.h"
#include "NasRabmMain.h"

#include "CdsRabmInterface.h"
#include "NasUtranCtrlInterface.h"
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_RABM_SNDMSG_C

VOS_UINT32                              g_ulNasRabmStubRlcSduSize = 144;

extern VOS_UINT32 RLC_GetRbMaxUpPduSize(VOS_UINT8 ucRbId, VOS_UINT32 ulPduSize, VOS_UINT8 ucCrcSize);

extern MN_CLIENT_ID_T MN_GetRealClientId(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulPid
);


VOS_VOID RABM_SndRabReestReq()
{
    GMMRABM_REESTABLISH_REQ_STRU *pSndMsg;
    VOS_UINT8  ucRrcCause;
    VOS_UINT8  ucTraClass;
    VOS_UINT8  i;
    VOS_UINT16                          usPdpContextStatus = 0;
    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    VOS_UINT16  usUplinkDataStatus = 0;
    #endif

    pSndMsg = (GMMRABM_REESTABLISH_REQ_STRU *)
                PS_ALLOC_MSG(WUEPS_PID_RABM, sizeof(GMMRABM_REESTABLISH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pSndMsg)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR, "RABM_SndRabReestReq:ERROR:Alloc msg fail!");
        return;
    }

    ucRrcCause = GMM_RABM_RRC_EST_CAUSE_ORG_BG_CALL;                            /* ��ʼ��RRC����ԭ��                        */
    for(i = 0; i < RABM_PS_MAX_ENT_NUM; i++)
    {
        if(RABM_NULL != g_aRabmPsEnt[i].ucState)
        {                                                                       /* ʵ��״̬Ϊ����                           */
            ucTraClass = (g_aRabmPsEnt[i].QoS.aucQosValue[3] & NAS_RABM_QOS_TRAFFIC_CLASS_MASK)
                            >> NAS_RABM_QOS_TRAFFIC_CLASS_BIT_OFFSET;           /* ���Traffic Class                        */
            if(( ucTraClass < ucRrcCause ) && ( 0 != ucTraClass ))
            {                                                                   /* RRC���ӽ��������ȼ����ڳ�ʼ�����ȼ�      */
                ucRrcCause = ucTraClass;                                        /* ����RRC���ӽ��������ȼ�                  */
            }

            usPdpContextStatus |= (VOS_UINT16)((VOS_UINT32)0x1 << (i + RABM_NSAPI_OFFSET));

            #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
            if (RABM_NSAPI_ACTIVE_NO_RAB == g_aRabmPsEnt[i].ucState)            /*ʵ��״̬Ϊ����δ��RAB                     */
            {
                usUplinkDataStatus |= (VOS_UINT16)((VOS_UINT32)0x1 << (i + RABM_NSAPI_OFFSET));         /*ʵ��ÿһλ��Ϊ1Ϊÿ��PDP�ؽ�RAB           */
            }
            #endif
        }
    }
    pSndMsg->ulRrcEstCause = ucRrcCause;

    pSndMsg->usPdpContextStatus = usPdpContextStatus;

    #if(PS_UE_REL_VER >= PS_PTL_VER_R7)
    pSndMsg->usUplinkDataStatus = usUplinkDataStatus;
    #endif

    pSndMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid = WUEPS_PID_RABM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_GMM;
    pSndMsg->MsgHeader.ulMsgName = ID_RABM_GMM_REESTABLISH_REQ;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pSndMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "RABM_SndRabReestReq():WARNING:SEND MSG FIAL");
    }

    return;
}
VOS_VOID RABM_SndPdcpDataReq(
                         VOS_UINT8  ucEntId,
                         TAFRABM_PS_DATA_REQ_STRU  *pData
                         )
{
    VOS_UINT32     ulDataLen;
    VOS_UINT8      ucRbId;

    ucRbId = g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[0];                          /* ���RB ID                                */

    ulDataLen = TTF_MemGetLen(WUEPS_PID_RABM, pData->pData);

    if ( 0 == ulDataLen )
    {
        return;
    }

    NAS_UTRANCTRL_RABM_AdaptPdcpDataReq(ucRbId, pData->pData, ulDataLen * 8);
    return;
}
VOS_VOID RABM_SndRrcQosUpdReq(
    VOS_UINT8                           ucEntId                                 /* RABMʵ��ID                               */
)
{
    QOS_INFO_STRU  *pQos = RABM_POINTER_NULL;

    pQos = (QOS_INFO_STRU *)RABM_Malloc(sizeof(QOS_INFO_STRU));
    if (VOS_NULL_PTR == pQos)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR, "RABM_SndRrcQosUpdReq:ERROR:Alloc mem fail!");
        return;
    }

    RABM_Memset((VOS_VOID *)pQos,0,sizeof(QOS_INFO_STRU));

    pQos->ulRabCnt = 1;                                                         /* ����RAB �ĸ���                           */
    pQos->aRab[0].ulRabId = g_aRabmPsEnt[ucEntId].RabInfo.ucRabId;              /* ����RAB ID                               */
    pQos->aRab[0].ulPppValid = g_aRabmPsEnt[ucEntId].ucPppFlg;                  /* ����PPP��־                              */
    pQos->aRab[0].ulDeliveryErrSdu = g_aRabmPsEnt[ucEntId].QoS.aucQosValue[3] & NAS_RABM_QOS_DELIVERY_ERRORNEOUS_SDU_MASK; /* ����Error SDU Delivery                   */
    pQos->aRab[0].ulCnDomainId = RABM_CN_PS;

    if(AS_SUCCESS != g_RabmRrcImportFunc.RrRabmRabQosUpdate(pQos))
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "RABM_SndRrcQosUpdReq:WARNING:g_RabmRrcImportFunc.RrRabmRabQosUpdate execute fail!");
    }
    RABM_Free(pQos);
    return;
}
VOS_VOID RABM_SndTafPsDataInd(
                          VOS_UINT8                  ucEntId,                       /* RAB ID����Ӧ��NSAPI����                  */
                          PDCP_RABM_DATA_BUF_STRU  *pRcvMsg                       /* ����ָ��                                 */
                          )
{
    ST_APP_RABM_DATA  PsDataInd;                                                /* ����ֲ��ṹ�����                       */

    PsDataInd.ucDomain  = D_RABM_PS_DOMAIN;                                     /* ��д��ֵ                                 */
    PsDataInd.ucRabId   = (VOS_UINT8)(ucEntId + RABM_NSAPI_OFFSET);                 /* ����RAB ID����Ӧ��NSAPI                  */
    PsDataInd.ulDataLen = pRcvMsg->ulDataLen;                                   /* �������ݳ���                             */
    PsDataInd.pucData   = pRcvMsg->pucData;                                     /* ��������                                 */

    Api_AppRabmDataInd( &PsDataInd );
}
VOS_VOID RABM_SndRrcRabRsp(
                       VOS_UINT8  ucRabNum,                                         /* Ӧ����Ϣ�а�����RB����                   */
                       RRRABM_RAB_IND_STRU  *pMsg                               /* Ŀǰ�������Ϣ                           */
                       )
{
    RAB_RSP_INFO_STRU   *pSndMsg = RABM_POINTER_NULL;
    VOS_UINT8               i;
    VOS_UINT8               ucEntId;
    VOS_UINT32               ulResult;
    VOS_UINT8               ucErrorSdu;

    ulResult = AS_RAB_RSP_OK;
    if( 0 == ucRabNum )
    {
        ulResult = AS_RAB_RSP_NG;
    }

    pSndMsg = (RAB_RSP_INFO_STRU *)RABM_Malloc(sizeof(RAB_RSP_INFO_STRU));
    if (VOS_NULL_PTR == pSndMsg)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR, "RABM_SndRrcRabRsp:ERROR:Alloc msg fail!");
        return;
    }

    RABM_Memset((VOS_VOID *)pSndMsg,0,sizeof(RAB_RSP_INFO_STRU));

    pSndMsg->ulRabCnt = ucRabNum;
    for(i = 0; i< pSndMsg->ulRabCnt; i++)
    {
        if(RABM_CN_PS == pMsg->aRabInfo[i].ulCnDomainId)
        {
            pSndMsg->aRabInfo[i].ulCnDomainId  = RABM_CN_PS;
            pSndMsg->aRabInfo[i].ulRabId = pMsg->aRabInfo[i].ulRabId;
            ucEntId = (VOS_UINT8)((pMsg->aRabInfo[i].ulRabId & 0x0f)
                - RABM_NSAPI_OFFSET);
            if(RABM_TC_STATE_NULL == g_aRabmPsEnt[ucEntId].ucState)
            {                                                                   /* TC�Ѿ�����                               */
                pSndMsg->aRabInfo[i].ulDeliveryErrSdu =
                    RABM_ERROR_SDU_DELIVERY_NO_DET;
                pSndMsg->aRabInfo[i].ulPppValid = WUEPS_FALSE;
            }
            else
            {
                pSndMsg->aRabInfo[i].ulPppValid = g_aRabmPsEnt[ucEntId].ucPppFlg; /* ��ֵppp��־                              */
                ucErrorSdu = g_aRabmPsEnt[ucEntId].QoS.aucQosValue[3] & NAS_RABM_QOS_DELIVERY_ERRORNEOUS_SDU_MASK;     /* ���error sdu delivery��Ϣ               */
                if((0 == ucErrorSdu) || (0x07 == ucErrorSdu))
                {
                    pSndMsg->aRabInfo[i].ulDeliveryErrSdu =
                        RABM_ERROR_SDU_DELIVERY_NO_DET;                         /* ��ֵerror sdu delivery��Ϣ               */
                }
                else
                {
                    pSndMsg->aRabInfo[i].ulDeliveryErrSdu = ucErrorSdu;
                }
            }
        }
        else
        {
            pSndMsg->aRabInfo[i].ulCnDomainId  = RABM_CN_CS;
            pSndMsg->aRabInfo[i].ulRabId = pMsg->aRabInfo[i].ulRabId;
            pSndMsg->aRabInfo[i].ulDeliveryErrSdu =
                RABM_ERROR_SDU_DELIVERY_NO_DET;
            pSndMsg->aRabInfo[i].ulPppValid = WUEPS_TRUE;
        }
    }
    pSndMsg->ulOpId = pMsg->ulOpId;

    if(AS_SUCCESS != g_RabmRrcImportFunc.RrRabmRabInfoRsp(ulResult,pSndMsg))
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "RABM_SndRrcRabRsp:WARNING:g_RabmRrcImportFunc.RrRabmRabInfoRsp execute fail!");
    }
    RABM_Free(pSndMsg);
    return;
}

/*******************************************************************************
  Module:   RABM_SndSmDeactReq
  Function: ֪ͨSM��Ӧ��NSAPI��RAB�Ѿ��ͷ�
  Input:    VOS_UINT8   ucNsapi           Network service access point identifier
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1. ��־��      2003.12.11   �¹�����
      2.  ��    ��   : 2006��10��21��
          ��    ��   : luojian id:60022475
          �޸�����   : ����PS_ALLOC_MSG������Ϣ��ʱ����ĳ���Ӧ��ȥVOS
          ��Ϣͷ�ĳ��ȣ����ⵥ��:A32D06583
*******************************************************************************/
VOS_VOID RABM_SndSmDeactReq(
                        VOS_UINT8  ucNsapi                                          /* Network service access point identifier  */
                        )
{
    RABMSM_DEACTIVATE_REQ_STRU *pSndMsg = RABM_POINTER_NULL;

    pSndMsg = (RABMSM_DEACTIVATE_REQ_STRU *)
                PS_ALLOC_MSG(WUEPS_PID_RABM, sizeof(RABMSM_DEACTIVATE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pSndMsg)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR, "RABM_SndSmDeactReq:ERROR:Alloc msg fail!");
        return;
    }

    pSndMsg->ulNsapi = ucNsapi;

    pSndMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid = WUEPS_PID_RABM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_SM;
    pSndMsg->MsgHeader.ulMsgName = RABMSM_DEACTIVATE_REQ;

    PS_SEND_MSG(WUEPS_PID_RABM, pSndMsg);

    return;
}

/*******************************************************************************
  Module:   RABM_SndCcSyncInd
  Function: ֪ͨCC RAB�Ѿ��������ͷ�
  Input:    VOS_UINT8   ucResult           ���:�������ͷ�
            VOS_UINT32   ulSi               �������ͷ�rab��stream id
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1. ��־��      2003.12.11   �¹�����
      2. ��    ��   : 2006��10��21��
         ��    ��   : luojian id:60022475
         �޸�����   : ����PS_ALLOC_MSG������Ϣ��ʱ����ĳ���Ӧ��ȥVOS
         ��Ϣͷ�ĳ��ȣ����ⵥ��:A32D06583
*******************************************************************************/
VOS_VOID RABM_SndCcSyncInd(
                       VOS_UINT8  ucResult,                                         /* ���:�������ͷ�                          */
                       VOS_UINT32  ulSi                                              /* �������ͷ�rab��stream id                 */
                       )
{
    RABMCC_SYNC_IND_STRU *pSndMsg = RABM_POINTER_NULL;

    pSndMsg = ( RABMCC_SYNC_IND_STRU * )
                PS_ALLOC_MSG(WUEPS_PID_RABM, sizeof(RABMCC_SYNC_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pSndMsg)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR, "RABM_SndCcSyncInd:ERROR:Alloc msg fail!");
        return;
    }

    pSndMsg->ulSi = ulSi;
    pSndMsg->ulResult = ucResult;

    pSndMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid = WUEPS_PID_RABM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_CC;
    pSndMsg->MsgHeader.ulMsgName = RABMCC_SYNC_IND;

    PS_SEND_MSG(WUEPS_PID_RABM, pSndMsg);
    return;
}



VOS_VOID RABM_SndCallSyncInd(
    VOS_UINT32                          ulResult,
    RAB_INFO_STRU                       *pRabInfo
)
{
    RABM_CALL_SYNC_IND_STRU *pSndMsg = RABM_POINTER_NULL;
    VOS_UINT8               ucLoop;

    pSndMsg = ( RABM_CALL_SYNC_IND_STRU * )
                PS_ALLOC_MSG(WUEPS_PID_RABM, sizeof(RABM_CALL_SYNC_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pSndMsg)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR, "RABM_SndCallSyncInd:ERROR:Alloc msg fail!");
        return;
    }

    pSndMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid = WUEPS_PID_RABM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_TAF;
    pSndMsg->MsgHeader.ulMsgName = RABM_CALL_SYNC_IND;

    /* ��д��ǰ��Rab״̬��RabId��RbId */
    pSndMsg->ulRabState = ulResult;
    pSndMsg->ulRabId    = pRabInfo->ulRabId;
    if (pRabInfo->ulRbNum <= RABM_CALL_MAX_RB_NUM_PER_RAB)
    {
        pSndMsg->ulRbNum = pRabInfo->ulRbNum;
    }
    else
    {
        pSndMsg->ulRbNum = RABM_CALL_MAX_RB_NUM_PER_RAB;
    }

    /* ��ǰ��RbId�����ж��������Ŀǰ�Ĵ���ʱ������ */
    for(ucLoop = 0; ucLoop < pSndMsg->ulRbNum; ucLoop++)
    {
        pSndMsg->aulRbId[ucLoop] = pRabInfo->aulRbId[ucLoop];
    }


    PS_SEND_MSG(WUEPS_PID_RABM, pSndMsg);
    return;
}



VOS_VOID RABM_SndTafCsDataInd(
                          RLC_RABM_CS_DATA_IND_STRU      *pRcvMsg,                   /* ����ָ��                                 */
                          VOS_UINT8                     ucEntId                     /* CS��RABMʵ������                         */
                          )
{
    ST_APP_RABM_DATA   CsDataInd;                                               /* ����ֲ��ṹ�����                       */

    CsDataInd.ucDomain  = D_RABM_CS_DOMAIN;                                     /* ��д��ֵ                                 */
    CsDataInd.ucRabId   = g_aRabmCsEnt[ucEntId].ucSi;                           /* ����RAB ID����Ӧ��SI                     */
    CsDataInd.ulDataLen = (VOS_UINT32)(pRcvMsg->usDataBitLen);                  /* �������ݳ���(bit����)                    */
    CsDataInd.pucData   = pRcvMsg->pucData;                                     /* ��������                                 */

    Api_AppRabmDataInd( &CsDataInd );                                           /* ��APP����CS������                        */
}

/*******************************************************************************
  Module:   RABM_SndTcTestCnf
  Function: ֪ͨtc�Ѿ�����/ȥ������Ի�
  Input:    TCRABM_TEST_CNF_STRU *pSndMsg
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   ��־��      2004.05.09   �¹�����
*******************************************************************************/
VOS_VOID RABM_SndTcTestCnf(
                       TCRABM_TEST_CNF_STRU  *pSndMsg
                       )
{
    pSndMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid = WUEPS_PID_RABM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_TC;
    pSndMsg->MsgHeader.ulMsgName = TCRABM_TEST_CNF;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pSndMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "RABM_SndTcTestCnf():WARNING:SEND MSG FIAL");
    }

    return;
}


VOS_VOID RABM_SndTcTestLoopCnf()
{
    TCRABM_TEST_LOOP_CNF_STRU  *pSndMsg;

    pSndMsg = (TCRABM_TEST_LOOP_CNF_STRU *)
                PS_ALLOC_MSG(WUEPS_PID_RABM, sizeof(TCRABM_TEST_LOOP_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pSndMsg)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR, "RABM_SndTcTestLoopCnf:ERROR:Alloc msg fail!");
        return;
    }

    pSndMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid = WUEPS_PID_RABM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_TC;
    pSndMsg->MsgHeader.ulMsgName = TCRABM_TEST_LOOP_CNF;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pSndMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "RABM_SndTcTestLoopCnf():WARNING:SEND MSG FIAL");
    }
    return;
}


VOS_VOID RABM_SndTcPsData_Mode_I_Handling(
    VOS_UINT8                           ucEntId,
    PDCP_RABM_TC_DATA_STRU             *pData
)
{
    TTF_MEM_ST                         *pstDataMem;
    VOS_UINT8                          *pucData;
    VOS_UINT8                           ucSpare;
    VOS_UINT32                          i;
    VOS_UINT8                           ucData;
    VOS_UINT16                          usSuffix;
    VOS_UINT32                          ulDataAddLen;
    VOS_UINT32                          ulDataBitLen;
    VOS_UINT16                          usMaxSduSize;
    VOS_UINT8                           ucGcfFlg;

    ulDataAddLen = 0;
    ulDataBitLen = pData->ulDataBitLen;

    if (VOS_FALSE == g_RabmTcInf.aRbInf[ucEntId].bRlcSduSizeValid)
    {
        /* ��ʾ�������ݳ�����Ч��ֱ�ӷ��أ����Դ�ӡ�쳣 */
        NAS_WARNING_LOG(WUEPS_PID_RABM, "RABM_SndTcPsData_Mode_I_Handling:WARNING:ulRlcSduSize is invalid!");
        return;
    }

    ucGcfFlg = ((NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())
                && (g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize == g_ulNasRabmStubRlcSduSize)) ? VOS_TRUE : VOS_FALSE;

    if ((0 == g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize) || (VOS_TRUE == ucGcfFlg))
    {
        usMaxSduSize = (VOS_UINT16)((ulDataBitLen + 7) / 8);

        pstDataMem = TTF_MemBlkAlloc(WUEPS_PID_RABM,
                                TTF_MEM_POOL_ID_UL_RLC_SDU,
                                usMaxSduSize);
        if (VOS_NULL_PTR == pstDataMem)
        {
            NAS_ERROR_LOG(WUEPS_PID_RABM, "RABM_SndTcPsData_Mode_I_Handling:ERROR:TcTest pSendPsData Error!");
            return;
        }

        pucData = pstDataMem->pData;

        /* ���������ݳ�����ͬ */
        (VOS_VOID)TTF_MemGet(WUEPS_PID_RABM, pData->pstDataMem, 0, pucData, usMaxSduSize);

        /* ����used���� */
        pstDataMem->usUsed  = usMaxSduSize;

        NAS_UTRANCTRL_RABM_AdaptPdcpDataReq(pData->ucRbId, pstDataMem, ulDataBitLen);

    }
    else
    {
        usMaxSduSize = (VOS_UINT16)((g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize + 7) / 8);

        pstDataMem = TTF_MemBlkAlloc(WUEPS_PID_RABM,
                                 TTF_MEM_POOL_ID_UL_RLC_SDU,
                                 usMaxSduSize);
        if (VOS_NULL_PTR == pstDataMem)
        {
            NAS_ERROR_LOG(WUEPS_PID_RABM, "RABM_SndTcPsData_Mode_I_Handling:ERROR:TcTest pSendPsData Error!");
            return;
        }

        pucData = pstDataMem->pData;

        if (ulDataBitLen == g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize)
        {
            /* ����g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize���ȵ����� */
            (VOS_VOID)TTF_MemGet(WUEPS_PID_RABM, pData->pstDataMem, 0,
                       pucData, usMaxSduSize);
        }
        else if (ulDataBitLen > g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize)
        {
            /* ����g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize���ȵ����� */
            (VOS_VOID)TTF_MemGet(WUEPS_PID_RABM, pData->pstDataMem, 0,
                       pucData, usMaxSduSize);
        }
        else
        {
            /* ʹ��PDCP�ϱ�������ѭ�������g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize���� */
            ucSpare = (VOS_UINT8)(ulDataBitLen % 8);                            /* ���bitֵ                                */
            if (0 == ucSpare)
            {
                for (i = 1; (ulDataBitLen * i) <= g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize; i++)
                {                                                               /* �����������                             */
                    if (1 == i)
                    {
                        (VOS_VOID)TTF_MemGet(WUEPS_PID_RABM,
                            pData->pstDataMem,
                            0,
                            pucData + (((ulDataBitLen + 7) / 8) * (i - 1)),
                            (VOS_UINT16)((ulDataBitLen + 7) / 8) );
                    }
                    else
                    {
                        (VOS_VOID)mdrv_memcpy(pucData + (((ulDataBitLen + 7) / 8) * (i - 1)),
                                    pucData,
                                    (VOS_UINT16)((ulDataBitLen + 7) / 8));
                    }

                    ulDataAddLen += ulDataBitLen;
                }

                if (ulDataAddLen < g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize)
                {                                                               /* �Ѿ��ϳɵ����ݳ���С���������ݳ���       */
                    (VOS_VOID)mdrv_memcpy(pucData + ((ulDataAddLen + 7) / 8),
                                pucData,
                                (VOS_UINT16)(((g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize - ulDataAddLen) + 7) / 8));
                }
            }
            else
            {
                (VOS_VOID)TTF_MemGet(WUEPS_PID_RABM,
                    pData->pstDataMem,
                    0,
                    pucData,
                    (VOS_UINT16)(ulDataBitLen / 8) );

                usSuffix    = (VOS_UINT16)(((ulDataBitLen + 7) / 8) - 1);       /* ������ݵ��±�                           */
                ucData      = pucData[usSuffix];
                ucData     |= (pucData[0] >> ucSpare);                          /* �������                                 */
                ulDataAddLen   = ulDataBitLen;

                for (i = ulDataBitLen;i < g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize; )
                {
                    *((pucData + ((ulDataAddLen + 7) / 8)) -1) = ucData;        /* �����������                             */
                    usSuffix = (VOS_UINT16)(((ulDataAddLen % ulDataBitLen) + 7) / 8);
                    ucData = (VOS_UINT8)((VOS_UINT32)(pucData[usSuffix]) << (8 - ucSpare));
                    if (usSuffix == (((ulDataBitLen + 7) - 8) / 8))
                    {                                                           /* �Ѿ������յ����ݵ�ĩβ                   */
                        ulDataAddLen = ulDataBitLen;                            /* ���³�ʼ�����ݳ���                       */
                        usSuffix = (VOS_UINT16)(((ulDataAddLen % ulDataBitLen)
                                    + 7) / 8);
                    }
                    else
                    {
                        usSuffix = (VOS_UINT16)((((ulDataAddLen % ulDataBitLen)
                                    + 7) / 8) +1);
                    }

                    ucData |= pucData[usSuffix] >> ucSpare;
                    i += 8;
                    ulDataAddLen += 8;
                }
            }
        }

        ucSpare = (VOS_UINT8)(g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize % 8);

        if (0 != ucSpare)
        {
            pucData[((g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize + 7) / 8)-1]
                &= (VOS_INT8)((VOS_UINT32)0xff << (8-ucSpare));
        }

        /* ����used���� */
        pstDataMem->usUsed = usMaxSduSize;

        NAS_UTRANCTRL_RABM_AdaptPdcpDataReq(pData->ucRbId,
                                            pstDataMem,
                                            g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize);
    }

    return;
}
VOS_VOID RABM_SndTcPsData_Mode_II_Handling(
    VOS_UINT8                           ucEntId,
    PDCP_RABM_TC_DATA_STRU             *pData
)
{
    TTF_MEM_ST                         *pstDataMem;
    VOS_UINT8                          *pucData;
    VOS_UINT32                          ulDataBitLen;
    VOS_UINT32                          ulMaxDataLen;
    VOS_UINT32                          ulCrc;
    VOS_UINT32                          ulCrcTmp;
    VOS_UINT16                          usCrcTmp;
    VOS_UINT8                           ucSpare;
    VOS_UINT16                          usDataIndex;


    ulDataBitLen = 0;


    /*��ȡ�ʵ������л��ر��ĳ��ȣ���λ:Bit*/
    NAS_UTRANCTRL_RABM_GetRbSuitableUlPduSize( pData->ucRbId,
                                              pData->ulDataBitLen,
                                              pData->stCrcInfo.ucCrcBitLen,
                                              &ulDataBitLen );

    if ( ( pData->stCrcInfo.ucCrcBitLen != 0 ) && ( pData->stCrcInfo.ucCrcBitLen != 8 )
      && ( pData->stCrcInfo.ucCrcBitLen != 12 ) && ( pData->stCrcInfo.ucCrcBitLen != 16 )
      && ( pData->stCrcInfo.ucCrcBitLen != 24 ) )
    {
        RABM_LOG_WARNING( "\n RABM_SndTcPsData:Crc Length Error! \r" );

        pstDataMem = TTF_MemBlkAlloc(WUEPS_PID_RABM,
                                TTF_MEM_POOL_ID_UL_RLC_SDU,
                                (VOS_UINT16)((ulDataBitLen + 7) / 8));
        if (VOS_NULL_PTR == pstDataMem)
        {
            NAS_ERROR_LOG(WUEPS_PID_RABM, "RABM_SndTcPsData_Mode_II_Handling:ERROR:TcTest pSendPsData Error!");
            return;
        }

        pucData = pstDataMem->pData;

        if (pData->ulDataBitLen <= ulDataBitLen)
        {
            (VOS_VOID)TTF_MemGet(WUEPS_PID_RABM,
                pData->pstDataMem,
                0,
                pucData,
                (VOS_UINT16)((pData->ulDataBitLen + 7) / 8));
        }
        else
        {
            (VOS_VOID)TTF_MemGet(WUEPS_PID_RABM,
                pData->pstDataMem,
                0,
                pucData,
                (VOS_UINT16)((ulDataBitLen + 7) / 8));
        }

        NAS_UTRANCTRL_RABM_AdaptPdcpDataReq(pData->ucRbId,
                                           pstDataMem,
                                           ulDataBitLen);

    }
    else if ( pData->stCrcInfo.ucCrcBitLen == 0 )
    {

        pstDataMem = TTF_MemBlkAlloc(WUEPS_PID_RABM,
                                TTF_MEM_POOL_ID_UL_RLC_SDU,
                                (VOS_UINT16)((ulDataBitLen + 7) / 8));
        if (VOS_NULL_PTR == pstDataMem)
        {
            NAS_ERROR_LOG(WUEPS_PID_RABM, "RABM_SndTcPsData_Mode_II_Handling:ERROR:TcTest pSendPsData Error!");
            return;
        }

        pucData = pstDataMem->pData;

        if (pData->ulDataBitLen <= ulDataBitLen)
        {
            (VOS_VOID)TTF_MemGet(WUEPS_PID_RABM,
                pData->pstDataMem,
                0,
                pucData,
                (VOS_UINT16)((pData->ulDataBitLen + 7) / 8));
        }
        else
        {
            (VOS_VOID)TTF_MemGet(WUEPS_PID_RABM,
                pData->pstDataMem,
                0,
                pucData,
                (VOS_UINT16)((ulDataBitLen + 7) / 8));
        }

        NAS_UTRANCTRL_RABM_AdaptPdcpDataReq(pData->ucRbId,
                                           pstDataMem,
                                           ulDataBitLen);

    }
    else
    {
        if ( (VOS_UINT32)( pData->ulDataBitLen + pData->stCrcInfo.ucCrcBitLen ) <= ulDataBitLen )
        {
            ulMaxDataLen = ulDataBitLen;
        }
        else
        {
            ulMaxDataLen = pData->ulDataBitLen + pData->stCrcInfo.ucCrcBitLen;
        }

        pstDataMem = TTF_MemBlkAlloc(WUEPS_PID_RABM,
                                TTF_MEM_POOL_ID_UL_RLC_SDU,
                                (VOS_UINT16)((ulMaxDataLen + 7) / 8));
        if (VOS_NULL_PTR == pstDataMem)
        {
            NAS_ERROR_LOG(WUEPS_PID_RABM, "RABM_SndTcPsData_Mode_II_Handling:ERROR:TcTest pSendPsData Error!");
            return;
        }

        pucData = pstDataMem->pData;

        PS_NAS_MEM_SET(pucData, 0, (ulMaxDataLen + 7) / 8);

        (VOS_VOID)TTF_MemGet(WUEPS_PID_RABM,
            pData->pstDataMem,
            0,
            pucData,
            (VOS_UINT16)((pData->ulDataBitLen + 7) / 8));

        ucSpare = (VOS_UINT8)(pData->ulDataBitLen % 8);

        /*��ȡCRC*/
        ulCrc = 0;
        switch(pData->stCrcInfo.ucCrcBitLen)
        {
            case 0:
                ulCrc = 0;
                break;
            case 8:
                ulCrc = pData->stCrcInfo.aucCrc[0];
                break;
            case 12:
                ulCrc |= ((VOS_UINT32)pData->stCrcInfo.aucCrc[0] << 4) & 0x0FF0;
                ulCrc |= ((VOS_UINT32)pData->stCrcInfo.aucCrc[1] >> 4) & 0x000F;
                break;
            case 16:
                ulCrc |= ((VOS_UINT32)pData->stCrcInfo.aucCrc[0] << 8) & 0xFF00;
                ulCrc |= (VOS_UINT32)pData->stCrcInfo.aucCrc[1];
                break;
            case 24:
                ulCrc |= (VOS_UINT32)pData->stCrcInfo.aucCrc[0] << 16;
                ulCrc |= (VOS_UINT32)pData->stCrcInfo.aucCrc[1] << 8;
                ulCrc |= (VOS_UINT32)pData->stCrcInfo.aucCrc[2];
                break;
            default:
                break;
        }

        if ( 0 == ucSpare )
        {
            usDataIndex = (VOS_UINT16)(pData->ulDataBitLen / 8);
            switch ( pData->stCrcInfo.ucCrcBitLen )
            {
                case 8:
                    pucData[usDataIndex] = (VOS_UINT8)ulCrc;
                    break;
                case 12:
                    pucData[usDataIndex] = (VOS_UINT8)( ulCrc >> 4 );
                    pucData[usDataIndex + 1] = (VOS_UINT8)( ulCrc << 4 );
                    break;
                case 16:
                    pucData[usDataIndex] = (VOS_UINT8)( ulCrc >> 8 );
                    pucData[usDataIndex + 1] = (VOS_UINT8)ulCrc;
                    break;
                case 24:
                    pucData[usDataIndex] = (VOS_UINT8)( ulCrc >> 16 );
                    pucData[usDataIndex + 1] = (VOS_UINT8)( ulCrc >> 8 );
                    pucData[usDataIndex + 2] = (VOS_UINT8)ulCrc;
                    break;
                default:
                    break;
            }
        }
        else
        {
            usDataIndex = (VOS_UINT16)(pData->ulDataBitLen / 8);
            switch ( pData->stCrcInfo.ucCrcBitLen )
            {
                case 8:
                    ulCrc &= 0x000000ff;
                    usCrcTmp = (VOS_UINT16)( ( ulCrc << ( 8 - ucSpare ) ) );
                    pucData[usDataIndex] &= (VOS_UINT8)((VOS_UINT32)0Xff << ( 8 - ucSpare ));
                    pucData[usDataIndex] |= (VOS_UINT8)( usCrcTmp >> 8 );
                    pucData[usDataIndex + 1] = (VOS_UINT8)( usCrcTmp );
                    break;
                case 12:
                    ulCrc &= 0x00000fff;
                    if ( ucSpare <= 4 )
                    {
                        usCrcTmp = (VOS_UINT16)( ulCrc << ( 4 - ucSpare ) );
                        pucData[usDataIndex] &= (VOS_UINT8)((VOS_UINT32)0xff << ( 8 - ucSpare ));
                        pucData[usDataIndex] |= (VOS_UINT8)( usCrcTmp >> 8 );
                        pucData[usDataIndex + 1] = (VOS_UINT8)( usCrcTmp );
                    }
                    else
                    {
                        ulCrcTmp = ulCrc << ( 12 - ucSpare );
                        pucData[usDataIndex] &= (VOS_UINT8)((VOS_UINT32)0xff << ( 8 - ucSpare ));
                        pucData[usDataIndex] |= (VOS_UINT8)( ulCrcTmp >> 16 );
                        pucData[usDataIndex + 1] = (VOS_UINT8)( ulCrcTmp >> 8 );
                        pucData[usDataIndex + 2] = (VOS_UINT8)( ulCrcTmp );
                    }
                    break;
                case 16:
                    ulCrc &= 0x0000ffff;
                    ulCrcTmp = ulCrc << ( 8 - ucSpare );
                    pucData[usDataIndex] &= (VOS_UINT8)((VOS_UINT32)0xff << ( 8 - ucSpare ));
                    pucData[usDataIndex] |= (VOS_UINT8)( ulCrcTmp >> 16 );
                    pucData[usDataIndex + 1] = (VOS_UINT8)( ulCrcTmp >> 8 );
                    pucData[usDataIndex + 2] = (VOS_UINT8)( ulCrcTmp );
                    break;
                case 24:
                    ulCrc &= 0x00ffffff;
                    ulCrcTmp = ulCrc << ( 8 - ucSpare );
                    pucData[usDataIndex] &= (VOS_UINT8)((VOS_UINT32)0xff << ( 8 - ucSpare ));
                    pucData[usDataIndex] |= (VOS_UINT8)( ulCrcTmp >> 24 );
                    pucData[usDataIndex + 1] = (VOS_UINT8)( ulCrcTmp >> 16 );
                    pucData[usDataIndex + 2] = (VOS_UINT8)( ulCrcTmp >> 8 );
                    pucData[usDataIndex + 3] = (VOS_UINT8)( ulCrcTmp );
                    break;
                default:
                    break;
            }
        }

        NAS_UTRANCTRL_RABM_AdaptPdcpDataReq(pData->ucRbId,
                                           pstDataMem,
                                           ulDataBitLen);
    }

    return;
}
VOS_VOID RABM_SndTcPsData(
                      VOS_UINT8                 ucEntId,
                      PDCP_RABM_TC_DATA_STRU    *pData
                      )
{
    if ( TC_MODE_1 == g_RabmTcInf.ucTestLoopMode )
    {
        RABM_SndTcPsData_Mode_I_Handling(ucEntId, pData);
    }
    else if ( TC_MODE_2 == g_RabmTcInf.ucTestLoopMode )
    {
        RABM_SndTcPsData_Mode_II_Handling(ucEntId, pData);
    }
    else
    {
        PS_NAS_LOG1(WUEPS_PID_RABM, VOS_NULL,  PS_LOG_LEVEL_ERROR, "RABM_SndTcPsData:ERROR:ucTestLoopMode Error!", g_RabmTcInf.ucTestLoopMode);
        return;
    }

    return;
}


VOS_UINT32  Rabm_CrcCalculate( VOS_UCHAR *pTransferBlock,
                                       VOS_UINT32 TbSize, VOS_UINT8 CrcLen)
{
    VOS_UINT16  usLoop;
    VOS_UINT32  ulPoly,ulCrc = 0;
    VOS_UINT8   ucCrc_8;
    VOS_UINT16  usCrc_12,usCrc_16;
    VOS_UINT32  ulCrc_24;
    VOS_UCHAR   *pucData, ucCycle;

    switch( CrcLen )
    {
        case 0:
            return ulCrc;
        case 8:
            ulPoly  = 0xd9;
            ucCrc_8 = 0;
            pucData = pTransferBlock;
            ucCycle = 0x80;
            for ( usLoop = 0; usLoop < TbSize; usLoop++ )
            {
                if ( ( usLoop != 0 ) && ( (usLoop % 8) == 0 ) )
                {
                    ucCycle = 0x80;
                    pucData++;
                }

                if ( ( ucCrc_8 & 0x01 ) == 1 )
                {
                    ucCrc_8 >>= 1;
                    ucCrc_8 ^= (VOS_UINT8)ulPoly;
                }
                else
                {
                    ucCrc_8 >>= 1;
                }

                if( ( *pucData & ucCycle ) != 0 )
                {
                    ucCrc_8 ^= (VOS_UINT8)ulPoly;
                }

                ucCycle >>= 1;
            }
            ulCrc = ( VOS_UINT32 )ucCrc_8;
            break;
        case 12:
            ulPoly   = 0xf01;
            usCrc_12 = 0;
            pucData  = pTransferBlock;
            ucCycle  = 0x80;
            for ( usLoop = 0; usLoop < TbSize; usLoop++ )
            {
                if ( ( usLoop != 0 ) && ( (usLoop % 8) == 0 ) )
                {
                    ucCycle = 0x80;
                    pucData++;
                }

                if ( ( usCrc_12 & 0x0001 ) == 1 )
                {
                    usCrc_12 >>= 1;
                    usCrc_12 ^= (VOS_UINT16)ulPoly;
                }
                else
                {
                    usCrc_12 >>= 1;
                }

                if( ( *pucData & ucCycle ) != 0 )
                {
                    usCrc_12 ^= (VOS_UINT16)ulPoly;
                }

                ucCycle >>= 1;
            }
            ulCrc = ( VOS_UINT32 )usCrc_12;
            break;
        case 16:
            ulPoly   = 0x8408;
            usCrc_16 = 0;
            pucData  = pTransferBlock;
            ucCycle  = 0x80;
            for ( usLoop = 0; usLoop < TbSize; usLoop++ )
            {
                if ( ( usLoop != 0 ) && ( (usLoop % 8) == 0 ) )
                {
                    ucCycle = 0x80;
                    pucData++;
                }

                if ( ( usCrc_16 & 0x0001 ) == 1 )
                {
                    usCrc_16 >>= 1;
                    usCrc_16 ^= (VOS_UINT16)ulPoly;
                }
                else
                {
                    usCrc_16 >>= 1;
                }

                if( ( *pucData & ucCycle ) != 0 )
                {
                    usCrc_16 ^= (VOS_UINT16)ulPoly;
                }

                ucCycle >>= 1;
            }
            ulCrc = ( VOS_UINT32 )usCrc_16;
            break;
        case 24:
            ulPoly   = 0xc60001;
            ulCrc_24 = 0;
            pucData  = pTransferBlock;
            ucCycle  = 0x80;
            for ( usLoop = 0; usLoop < TbSize; usLoop++ )
            {
                if ( ( usLoop != 0 ) && ( (usLoop % 8) == 0 ) )
                {
                    ucCycle = 0x80;
                    pucData++;
                }

                if ( ( ulCrc_24 & 0x00000001 ) == 1 )
                {
                    ulCrc_24 >>= 1;
                    ulCrc_24 ^= ulPoly;
                }
                else
                {
                    ulCrc_24 >>= 1;
                }

                if( ( *pucData & ucCycle ) != 0 )
                {
                    ulCrc_24 ^= ulPoly;
                }

                ucCycle >>= 1;
            }
            ulCrc = ( VOS_UINT32 )ulCrc_24;
            break;
        default:
            break;
    }
    return ulCrc;
}

/*******************************************************************************
  Module:   RABM_SndTcCsData_Mode_I_Handling
  Function: RABM_SndTcCsData �����Ӷ�: TC_MODE_1����
  Input:    VOS_UINT8                       ucEntId
            RABMRLC_CS_DATA_IND_STRU    *pData
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   ŷ����      2009.06.15   �¹�����
*******************************************************************************/
VOS_VOID RABM_SndTcCsData_Mode_I_Handling(
                      VOS_UINT8                  ucEntId,
                      RLC_RABM_CS_DATA_IND_STRU *pData
                      )
{
    VOS_INT8                       *pcData = RABM_POINTER_NULL;
    VOS_UINT32                      ulDataLen;
    VOS_UINT8                       ucSpare;
    VOS_UINT8                       ucData;
    VOS_UINT16                      usSuffix;
    VOS_UINT32                      i;

    ucSpare = (VOS_UINT8)(pData->usDataBitLen & 8);                                    /* ���bitֵ                                */
    ulDataLen = 0;

    if (VOS_FALSE == g_RabmTcInf.aRbInf[ucEntId].bRlcSduSizeValid)
    {
        /*��ʾ�������ݳ�����Ч��ֱ�ӷ��أ����Դ�ӡ�쳣*/
        NAS_WARNING_LOG(WUEPS_PID_RABM, "RABM_SndTcCsData_Mode_I_Handling:WARNING:ulRlcSduSize is invalid!");
        return;
    }

    if (0 == g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize)
    {
        pcData = (VOS_INT8 *)VOS_MemAlloc(WUEPS_PID_RABM, BLOCK_MEM_PT,
                        (pData->usDataBitLen + 7) >> 3);

        if(RABM_POINTER_NULL == pcData)
        {
            NAS_ERROR_LOG(WUEPS_PID_RABM, "RABM_SndTcCsData_Mode_I_Handling:ERROR:TcTest pSendCsData Error!");
            return;
        }
        PS_NAS_MEM_CPY(pcData, pData->pucData, (pData->usDataBitLen + 7) >> 3);       /* ���������ݳ�����ͬ                       */

        (VOS_VOID)NAS_CsDomainDataReq((VOS_INT8)(g_RabmTcInf.aRbInf[ucEntId].ucRbId),
                            (VOS_UINT32)pData->usDataBitLen,
                            (VOS_UINT8 *)pcData);

        PS_RABM_MEM_FREE(pcData);
    }
    else
    {
        pcData = (VOS_INT8 *)VOS_MemAlloc(WUEPS_PID_RABM, BLOCK_MEM_PT,
                        (g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize + 7) >> 3);

        if(RABM_POINTER_NULL == pcData)
        {
            PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL,  PS_LOG_LEVEL_ERROR, "RABM_SndTcCsData:ERROR:TcTest pSendCsData Error!");
            return;
        }

        if(pData->usDataBitLen >= g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize)
        {
            PS_NAS_MEM_CPY(pcData, pData->pucData,
                (g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize + 7) >> 3);           /* ��������                                 */
        }
        else
        {
            if(0 == ucSpare)
            {
                for(i = 1; (pData->usDataBitLen * i) <=
                        g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize; i++)
                {                                                               /* �����������                             */
                    PS_NAS_MEM_CPY(
                        (pcData + (((pData->usDataBitLen + 7) / 8) * (i - 1))),
                        pData->pucData,
                        (pData->usDataBitLen + 7) / 8);                            /* ��������                                 */
                    ulDataLen += pData->usDataBitLen;
                }

                if(ulDataLen < g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize)
                {                                                               /* �Ѿ��ϳɵ����ݳ���С���������ݳ���       */
                    PS_NAS_MEM_CPY((pcData + ((ulDataLen + 7) / 8)),
                        pData->pucData,
                        ((g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize
                                - ulDataLen) + 7) / 8);                          /* ��������                                 */
                }
            }
            else
            {
                PS_NAS_MEM_CPY(pcData, pData->pucData, pData->usDataBitLen / 8);                                      /* ��������                                 */
                usSuffix    = (VOS_UINT8)(((pData->usDataBitLen + 7) / 8) - 1);             /* ������ݵ��±�                           */
                ucData      = pData->pucData[usSuffix];
                ucData     |= pData->pucData[0] >> ucSpare;                         /* �������                                 */
                ulDataLen   = pData->usDataBitLen;

                for(i = pData->usDataBitLen;i < g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize; )
                {
                    *((pcData + ((ulDataLen + 7) / 8)) -1) = (VOS_INT8)ucData;                 /* �����������                             */
                    usSuffix = (VOS_UINT16)(((ulDataLen % pData->usDataBitLen) + 7) / 8);
                    ucData = (VOS_UINT8)((VOS_UINT32)pData->pucData[usSuffix] << (8-ucSpare));
                    if(usSuffix == (((pData->usDataBitLen + 7) - 8) / 8))
                    {                                                           /* �Ѿ������յ����ݵ�ĩβ                   */
                        ulDataLen = pData->usDataBitLen;                           /* ���³�ʼ�����ݳ���                       */
                        usSuffix = (VOS_UINT16)(((ulDataLen % pData->usDataBitLen)
                                    + 7) / 8);
                    }
                    else
                    {
                        usSuffix = (VOS_UINT16)((((ulDataLen % pData->usDataBitLen)
                                    + 7) / 8) +1);
                    }

                    ucData |= pData->pucData[usSuffix] >> ucSpare;
                    i += 8;
                    ulDataLen += 8;
                }
            }
        }

        ucSpare = (VOS_UINT8)(g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize % 8);

        if(0 != ucSpare)
        {
            pcData[((g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize + 7) / 8)-1]
                &= (VOS_INT8)((VOS_UINT32)0xff << (8-ucSpare));
        }

        (VOS_VOID)NAS_CsDomainDataReq((VOS_INT8)(g_RabmTcInf.aRbInf[ucEntId].ucRbId),
                             g_RabmTcInf.aRbInf[ucEntId].ulRlcSduSize,
                             (VOS_UINT8 *)pcData);

        PS_RABM_MEM_FREE(pcData);

    }

    return;
}


VOS_VOID RABM_SndTcCsData_Mode_II_Handling(
                      VOS_UINT8                  ucEntId,
                      RLC_RABM_CS_DATA_IND_STRU *pData
                      )
{
    VOS_UINT32                      ulDataLen;
    VOS_UINT8                       ucSpare;
    VOS_UINT8                      *pucData = RABM_POINTER_NULL;
    VOS_UINT16                      usCrcTmp;
    VOS_UINT32                      ulMaxDataLen,ulCrc,ulCrcTmp;
    VOS_UINT16                      usDataIndex;

    ucSpare = (VOS_UINT8)(pData->usDataBitLen & 8);                                    /* ���bitֵ                                */
    ulDataLen = 0;

    NAS_UTRANCTRL_RABM_GetRbSuitableUlPduSize(g_RabmTcInf.aRbInf[ucEntId].ucRbId,
                                             (VOS_UINT32)pData->usDataBitLen,
                                              pData->stCrcInfo.ucCrcBitLen,
                                              &ulDataLen);

    if ( ( pData->stCrcInfo.ucCrcBitLen != 0 ) && ( pData->stCrcInfo.ucCrcBitLen != 8 )
        && ( pData->stCrcInfo.ucCrcBitLen != 12 ) && ( pData->stCrcInfo.ucCrcBitLen != 16 )
        && ( pData->stCrcInfo.ucCrcBitLen != 24 ) )
    {
        RABM_LOG_WARNING( "\n RABM_SndTcCsData:Crc Length Error! \r" );

        pucData = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_RABM, BLOCK_MEM_PT,
                        (ulDataLen + 7) / 8);

        if(RABM_POINTER_NULL == pucData)
        {
            RABM_LOG_WARNING( "\n [Error]TcTest pSendCsData Error! \r" );
            return;
        }

        if(pData->usDataBitLen != 0)
        {
            if ( pData->usDataBitLen <= ulDataLen )
            {
                PS_NAS_MEM_CPY( pucData, pData->pucData, ( pData->usDataBitLen + 7 ) / 8 );
            }
            else
            {
                PS_NAS_MEM_CPY( pucData, pData->pucData, ( ulDataLen + 7 ) / 8 );
            }
        }

        (VOS_VOID)NAS_CsDomainDataReq((VOS_INT8)(g_RabmTcInf.aRbInf[ucEntId].ucRbId), ulDataLen, pucData);
        PS_RABM_MEM_FREE(pucData);

        return;
    }
    else if ( pData->stCrcInfo.ucCrcBitLen == 0 )
    {
        pucData = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_RABM, BLOCK_MEM_PT,
                        (ulDataLen + 7) / 8);

        if(RABM_POINTER_NULL == pucData)
        {
            RABM_LOG_WARNING( "\n [Error]TcTest pSendCsData Error! \r" );
            return;
        }

        if(pData->usDataBitLen != 0)
        {
            if ( pData->usDataBitLen <= ulDataLen )
            {
                PS_NAS_MEM_CPY( pucData, pData->pucData, ( pData->usDataBitLen + 7 ) / 8 );
            }
            else
            {
                PS_NAS_MEM_CPY( pucData, pData->pucData, ( ulDataLen + 7 ) / 8 );
            }
        }

        (VOS_VOID)NAS_CsDomainDataReq((VOS_INT8)(g_RabmTcInf.aRbInf[ucEntId].ucRbId), ulDataLen, pucData);
        PS_RABM_MEM_FREE(pucData);
        return;
    }
    else
    {
        if ( (VOS_UINT32)( pData->usDataBitLen + pData->stCrcInfo.ucCrcBitLen ) <= ulDataLen )
        {
            ulMaxDataLen = ulDataLen;
        }
        else
        {
            ulMaxDataLen = pData->usDataBitLen + pData->stCrcInfo.ucCrcBitLen;
        }

        pucData = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_RABM, BLOCK_MEM_PT,
                        (ulMaxDataLen + 7) / 8);

        if(RABM_POINTER_NULL == pucData)
        {
            RABM_LOG_WARNING( "\n [Error]TcTest pSendCsData Error! \r" );
            return;
        }
        PS_NAS_MEM_SET( pucData, 0, ( ulMaxDataLen + 7 ) / 8 );

        if(pData->usDataBitLen != 0)
        {
            PS_NAS_MEM_CPY( pucData, pData->pucData, ( pData->usDataBitLen + 7 ) / 8 );
        }

        ucSpare = ( VOS_UINT8 )( pData->usDataBitLen % 8 );

        /*��ȡCRC*/
        ulCrc = 0;
        switch(pData->stCrcInfo.ucCrcBitLen)
        {
            case 0:
                ulCrc = 0;
                break;
            case 8:
                ulCrc = pData->stCrcInfo.aucCrc[0];
                break;
            case 12:
                ulCrc |= ((VOS_UINT32)pData->stCrcInfo.aucCrc[0] << 4) & 0x0FF0;
                ulCrc |= ((VOS_UINT32)pData->stCrcInfo.aucCrc[1] >> 4) & 0x000F;
                break;
            case 16:
                ulCrc |= ((VOS_UINT32)pData->stCrcInfo.aucCrc[0] << 8) & 0xFF00;
                ulCrc |= (VOS_UINT32)pData->stCrcInfo.aucCrc[1];
                break;
            case 24:
                ulCrc |= (VOS_UINT32)pData->stCrcInfo.aucCrc[0] << 16;
                ulCrc |= (VOS_UINT32)pData->stCrcInfo.aucCrc[1] << 8;
                ulCrc |= (VOS_UINT32)pData->stCrcInfo.aucCrc[2];
                break;
            default:
                break;
        }

        if ( 0 == ucSpare )
        {
            usDataIndex = pData->usDataBitLen / 8;
            switch ( pData->stCrcInfo.ucCrcBitLen )
            {
                case 8:
                    pucData[usDataIndex] = (VOS_UINT8)ulCrc;
                    break;
                case 12:
                    pucData[usDataIndex] = (VOS_UINT8)( ulCrc >> 4 );
                    pucData[usDataIndex + 1] = (VOS_UINT8)( ulCrc << 4 );
                    break;
                case 16:
                    pucData[usDataIndex] = (VOS_UINT8)( ulCrc >> 8 );
                    pucData[usDataIndex + 1] = (VOS_UINT8)ulCrc;
                    break;
                case 24:
                    pucData[usDataIndex] = (VOS_UINT8)( ulCrc >> 16 );
                    pucData[usDataIndex + 1] = (VOS_UINT8)( ulCrc >> 8 );
                    pucData[usDataIndex + 2] = (VOS_UINT8)ulCrc;
                    break;
                default:
                    break;
            }
        }
        else
        {
            usDataIndex = pData->usDataBitLen / 8;
            switch ( pData->stCrcInfo.ucCrcBitLen )
            {
                case 8:
                    ulCrc &= 0x000000ff;
                    usCrcTmp = (VOS_UINT16)( ( ulCrc << ( 8 - ucSpare ) ) );
                    pucData[usDataIndex] &= (VOS_UINT8)((VOS_UINT32)0Xff << ( 8 - ucSpare ));
                    pucData[usDataIndex] |= (VOS_UINT8)( usCrcTmp >> 8 );
                    pucData[usDataIndex + 1] = (VOS_UINT8)( usCrcTmp );
                    break;
                case 12:
                    ulCrc &= 0x00000fff;
                    if ( ucSpare <= 4 )
                    {
                        usCrcTmp = (VOS_UINT16)( ulCrc << ( 4 - ucSpare ) );
                        pucData[usDataIndex] &= (VOS_UINT8)((VOS_UINT32)0xff << ( 8 - ucSpare ));
                        pucData[usDataIndex] |= (VOS_UINT8)( usCrcTmp >> 8 );
                        pucData[usDataIndex + 1] = (VOS_UINT8)( usCrcTmp );
                    }
                    else
                    {
                        ulCrcTmp = ulCrc << ( 12 - ucSpare );
                        pucData[usDataIndex] &= (VOS_UINT8)((VOS_UINT32)0xff << ( 8 - ucSpare ));
                        pucData[usDataIndex] |= (VOS_UINT8)( ulCrcTmp >> 16 );
                        pucData[usDataIndex + 1] = (VOS_UINT8)( ulCrcTmp >> 8 );
                        pucData[usDataIndex + 2] = (VOS_UINT8)( ulCrcTmp );
                    }
                    break;
                case 16:
                    ulCrc &= 0x0000ffff;
                    ulCrcTmp = ulCrc << ( 8 - ucSpare );
                    pucData[usDataIndex] &= (VOS_UINT8)((VOS_UINT32)0xff << ( 8 - ucSpare ));
                    pucData[usDataIndex] |= (VOS_UINT8)( ulCrcTmp >> 16 );
                    pucData[usDataIndex + 1] = (VOS_UINT8)( ulCrcTmp >> 8 );
                    pucData[usDataIndex + 2] = (VOS_UINT8)( ulCrcTmp );
                    break;
                case 24:
                    ulCrc &= 0x00ffffff;
                    ulCrcTmp = ulCrc << ( 8 - ucSpare );
                    pucData[usDataIndex] &= (VOS_UINT8)((VOS_UINT32)0xff << ( 8 - ucSpare ));
                    pucData[usDataIndex] |= (VOS_UINT8)( ulCrcTmp >> 24 );
                    pucData[usDataIndex + 1] = (VOS_UINT8)( ulCrcTmp >> 16 );
                    pucData[usDataIndex + 2] = (VOS_UINT8)( ulCrcTmp >> 8 );
                    pucData[usDataIndex + 3] = (VOS_UINT8)( ulCrcTmp );
                    break;
                default:
                    break;
            }
        }
        (VOS_VOID)NAS_CsDomainDataReq( (VOS_INT8)(g_RabmTcInf.aRbInf[ucEntId].ucRbId), ulDataLen, pucData);
        PS_RABM_MEM_FREE(pucData);
    }

    return;
}


VOS_VOID RABM_SndTcCsData(
                      VOS_UINT8 ucEntId,
                      RLC_RABM_CS_DATA_IND_STRU *pData
                      )
{
    if ( g_RabmTcInf.ucTestLoopMode == TC_MODE_1 )
    {
        RABM_SndTcCsData_Mode_I_Handling(ucEntId, pData);
    }
    else
    {
        RABM_SndTcCsData_Mode_II_Handling(ucEntId, pData);
    }

    return;
}


VOS_VOID RABM_SndTcRabInd(
                      VOS_UINT8  ucEndId,
                      VOS_UINT8  ucSetUpFlg
                      )
{
    TCRABM_RAB_IND_STRU         *pSndMsg;

    pSndMsg = (TCRABM_RAB_IND_STRU *)
                PS_ALLOC_MSG(WUEPS_PID_RABM, sizeof(TCRABM_RAB_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pSndMsg)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR, "RABM_SndTcRabInd:ERROR:Alloc msg fail!");
        return;
    }

    pSndMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid = WUEPS_PID_RABM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_TC;
    pSndMsg->MsgHeader.ulMsgName = TCRABM_RAB_IND;

    pSndMsg->ulRabChangeType = ucSetUpFlg;                                      /* ��������                                 */
    pSndMsg->RabInfo.ulCnDomainId = g_RabmTcInf.aRbInf[ucEndId].ucDomain;       /* CN DOMAIN                                */
    pSndMsg->RabInfo.ulRabId = g_RabmTcInf.aRbInf[ucEndId].ucRabId;             /* RAB ID                                   */
    pSndMsg->RabInfo.ulRbId = g_RabmTcInf.aRbInf[ucEndId].ucRbId;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pSndMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "RABM_SndTcRabInd():WARNING:SEND MSG FIAL");
    }
    return;
}

/*******************************************************************************
  Module:   RABM_SndTafStatusInd
  Function: ֪ͨAPP������ֹͣ���ݴ���
  Input:    VOS_UINT8                   ucNsapiOrSi     RAB ID����Ӧ��NSAPI��SI
            VOS_UINT8                   ucStatusFlg     ֹͣ��ʼ�������ݱ�־
            VOS_UINT8                   ucCause         ��ʼ�������ݵ�ԭ��
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   ��־��   2005.01.07   �¹�����
*******************************************************************************/
VOS_VOID RABM_SndTafStatusInd(
                          VOS_UINT8 ucNsapiOrSi,                                    /* RAB ID����Ӧ��NSAPI��SI                  */
                          VOS_UINT8 ucStatusFlg,                                    /* ֹͣ��ʼ�������ݱ�־                   */
                          VOS_UINT8 ucCause                                         /* ��ʼ�������ݵ�ԭ��                       */
                          )
{
    ST_APP_RABM_STATUS   TafStatusInd;                                          /* ����ֲ��ṹ�����                       */

    TafStatusInd.ucDomain     = D_RABM_PS_DOMAIN;                               /* ��д��ֵ                                 */
    TafStatusInd.ucRabId      = ucNsapiOrSi;                                    /* ����RAB ID����Ӧ��NSAPI��SI              */
    TafStatusInd.ucStatus     = ucStatusFlg;                                    /* ����ֹͣ��ʼ�������ݱ�־               */
    TafStatusInd.ucStartCause = ucCause;                                        /* ���濪ʼ�������ݵ�ԭ��                   */

    Api_AppRabmStatusInd( &TafStatusInd );                                      /* ֪ͨAPP������ֹͣ���ݴ���                */
}

/*******************************************************************************
  Module:   RABM_SndTafInActNsapiInd
  Function: ֪ͨAPPָ����NSAPIû�м���
  Input:    VOS_UINT8                   ucNsapi     RAB ID����Ӧ��NSAPI
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   ��־��   2005.01.07   �¹�����
*******************************************************************************/
VOS_VOID RABM_SndTafInActNsapiInd( VOS_UINT8 ucNsapi )
{
    ST_APP_RABM_ERROR   TafInActNsapiInd;                                       /* ����ֲ��ṹ�����                       */

    TafInActNsapiInd.ucDomain  = D_RABM_PS_DOMAIN;                               /* ��д��ֵ                                 */
    TafInActNsapiInd.ucRabId   = ucNsapi;                                         /* ����RAB ID����Ӧ��NSAPI                  */
    TafInActNsapiInd.ucErrType = TAF_DATA_CAUSE_LOWLAYER_INDICATION;

    Api_AppRabmErrInd( &TafInActNsapiInd );                                     /* ֪ͨAPPָ����NSAPIû�м���               */
}

/*******************************************************************************
  Module:   RABM_SndTafInActSiInd
  Function: ֪ͨAPPָ����SIû�м���
  Input:    VOS_UINT8                   ucSi        RAB ID����Ӧ��SI
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   ��־��   2005.01.06   �¹�����
*******************************************************************************/
VOS_VOID RABM_SndTafInActSiInd( VOS_UINT8 ucSi )
{
    ST_APP_RABM_ERROR   TafInActSiInd;                                          /* ����ֲ��ṹ�����                       */

    TafInActSiInd.ucDomain  = D_RABM_CS_DOMAIN;                                  /* ��д��ֵ                                 */
    TafInActSiInd.ucRabId   = ucSi;                                               /* ����RAB ID����Ӧ��SI                     */
    TafInActSiInd.ucErrType = TAF_DATA_CAUSE_LOWLAYER_INDICATION;

    Api_AppRabmErrInd( &TafInActSiInd );                                        /* ֪ͨAPPָ����SIû�м���                  */
}

VOS_VOID RABM_SndGmmRabRelInd( VOS_VOID )
{
    GMMRABM_RAB_REL_IND_STRU    *pSndMsg;

    pSndMsg = (GMMRABM_RAB_REL_IND_STRU *)
                PS_ALLOC_MSG(WUEPS_PID_RABM, sizeof(GMMRABM_RAB_REL_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pSndMsg)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR, "RABM_SndGmmRabRelInd:ERROR:Alloc msg fail!");
        return;
    }

    pSndMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid = WUEPS_PID_RABM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_GMM;
    pSndMsg->MsgHeader.ulMsgName = ID_RABM_GMM_RAB_REL_IND;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pSndMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "RABM_SndGmmRabRelInd():WARNING:SEND MSG FIAL");
    }
    return;
}


VOS_VOID NAS_RABM_SndGmmRbSetupInd(VOS_VOID)
{
    GMMRABM_RAB_SETUP_IND_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (GMMRABM_RAB_SETUP_IND_STRU *)
                PS_ALLOC_MSG(WUEPS_PID_RABM, sizeof(GMMRABM_RAB_SETUP_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_RABM_SndGmmRbSetupInd:ERROR:Alloc msg fail!");
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid     = WUEPS_PID_RABM;
    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulMsgName       = ID_RABM_GMM_RAB_SETUP_IND;
    pstMsg->MsgHeader.ulLength        = sizeof(GMMRABM_RAB_SETUP_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_SndGmmRbSetupInd():WARNING:SEND MSG FIAL");
    }

    return;
}


VOS_VOID NAS_RABM_SendApsSysChgInd(
    VOS_UINT32                          ulMsgId
)
{
    RABM_APS_SYS_CHANGE_MSG            *pstSysChgInd;

    pstSysChgInd = (RABM_APS_SYS_CHANGE_MSG*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_RABM,
                            sizeof(RABM_APS_SYS_CHANGE_MSG));
    if (VOS_NULL_PTR == pstSysChgInd)
    {
        NAS_ERROR_LOG1(WUEPS_PID_RABM,
            "NAS_RABM_SendApsSysChgInd: Memory alloc failed, MsgID:", ulMsgId);
        return;
    }

    /* ��д��Ϣͷ */
    pstSysChgInd->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSysChgInd->ulReceiverPid   = WUEPS_PID_TAF;
    pstSysChgInd->ulMsgType       = ulMsgId;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pstSysChgInd))
    {
        NAS_ERROR_LOG1(WUEPS_PID_RABM,
            "NAS_RABM_SendApsSysChgInd: Send message failed, MsgID:", ulMsgId);
    }

    return;
}


VOS_VOID  NAS_RABM_SndCdsFreeBuffDataInd(VOS_UINT8 ucRabId)
{
    CDS_RABM_FREE_BUFF_DATA_IND_STRU    *pstMsg;

    pstMsg = (CDS_RABM_FREE_BUFF_DATA_IND_STRU*)PS_ALLOC_MSG(WUEPS_PID_RABM,
                             sizeof(CDS_RABM_FREE_BUFF_DATA_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndCdsFreeBuffDataInd:ERROR:Alloc Mem Fail.");
        return;
    }

    /* ��Ϣ��ֵ */
    pstMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid       = UEPS_PID_CDS;
    pstMsg->enMsgID             = ID_RABM_CDS_FREE_BUFF_DATA_IND;
    pstMsg->ucRabId             = ucRabId;

    PS_MEM_SET(pstMsg->aucReserved, 0, 3);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_SndCdsFreeBuffDataInd():WARNING:SEND MSG FIAL");
    }
    return;
}


VOS_VOID  NAS_RABM_SndCdsSendBuffDataInd(
    VOS_UINT8                                               ucRabId,
    CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_ENUM_UINT32        enSndBuffDataAllowedType
)
{
    CDS_RABM_SEND_BUFF_DATA_IND_STRU    *pstMsg;

    pstMsg = (CDS_RABM_SEND_BUFF_DATA_IND_STRU*)PS_ALLOC_MSG(WUEPS_PID_RABM,
                             sizeof(CDS_RABM_SEND_BUFF_DATA_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndCdsSendBuffDataInd:ERROR:Alloc Mem Fail.");
        return;
    }

    /* ��Ϣ��ֵ */
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_CDS;
    pstMsg->enMsgId                     = ID_RABM_CDS_SEND_BUFF_DATA_IND;
    pstMsg->enSndBuffDataAllowedType    = enSndBuffDataAllowedType;
    pstMsg->ucRabId                     = ucRabId;

    PS_MEM_SET(pstMsg->aucReserved, 0, 3);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_SndCdsSendBuffDataInd():WARNING:SEND MSG FIAL");
    }

    return;
}


VOS_VOID  NAS_RABM_SndCdsQosFcRabCreateInd(
    VOS_UINT8                           ucRabId,
    QCI_TYPE_ENUM_UINT8                 enQci
)
{
    QOS_FC_RAB_CREATE_IND_STRU         *pstMsg;

    pstMsg = (QOS_FC_RAB_CREATE_IND_STRU*)PS_ALLOC_MSG(WUEPS_PID_RABM,
                             sizeof(QOS_FC_RAB_CREATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndCdsQosFcRabCreateInd:ERROR:Alloc Mem Fail.");
        return;
    }

    /* ��Ϣ��ֵ */
    pstMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid       = UEPS_PID_CDS;
    pstMsg->enMsgId             = ID_QOS_FC_RABM_RAB_CREATE_IND;

    pstMsg->ucRabId             = ucRabId;

    /* Ŀǰ��֧��Second Pdp��ucLinkRabId����PDP��ͬ */
    pstMsg->ucLinkRabId         = ucRabId;
    pstMsg->enQci               = enQci;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_SndCdsQosFcRabCreateInd():WARNING:SEND MSG FIAL");
    }
    return;
}
VOS_VOID  NAS_RABM_SndCdsQosFcRabReleaseInd(
    VOS_UINT8                           ucRabId
)
{
    QOS_FC_RAB_RELEASE_IND_STRU        *pstMsg;

    pstMsg = (QOS_FC_RAB_RELEASE_IND_STRU*)PS_ALLOC_MSG(WUEPS_PID_RABM,
                             sizeof(QOS_FC_RAB_RELEASE_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndCdsQosFcRabReleaseInd:ERROR:Alloc Mem Fail.");
        return;
    }

    /* ��Ϣ��ֵ */
    pstMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid       = UEPS_PID_CDS;
    pstMsg->enMsgId             = ID_QOS_FC_RABM_RAB_RELEASE_IND;
    pstMsg->ucRabId             = ucRabId;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_SndCdsQosFcRabReleaseInd():WARNING:SEND MSG FIAL");
    }
    return;
}




VOS_VOID NAS_RABM_SndAtReleaseRrcCnf(
    VOS_UINT16                          usClientId,                             /* AT����Ϣ��RABM������ClientId */
    VOS_UINT8                           ucOpId,                                 /* AT����Ϣ��RABM������OpId */
    VOS_UINT32                          ulRslt
)
{
    /* ��AT�������ý�� */
    VOS_UINT32                          ulRet;                                  /* �������VOS���ͺ����ķ���ֵ */
    RABM_AT_RELEASE_RRC_CNF_STRU       *pstMsg = VOS_NULL_PTR;                  /* ����ԭ������ָ�� */

    /* �����ڴ�  */
    pstMsg = (RABM_AT_RELEASE_RRC_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                              sizeof(RABM_AT_RELEASE_RRC_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtReleaseRrcCnf:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH, 0x00, (sizeof(RABM_AT_RELEASE_RRC_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��ز��� */
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_AT;
    pstMsg->stMsgHeader.ulLength          = sizeof(RABM_AT_RELEASE_RRC_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = ID_RABM_AT_SET_RELEASE_RRC_CNF;
    pstMsg->ulRslt                        = ulRslt;
    pstMsg->usClientId                    = usClientId;
    pstMsg->ucOpId                        = ucOpId;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG(WUEPS_PID_RABM, pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtReleaseRrcCnf:ERROR:PS_SEND_MSG ");
        return ;
    }

    return ;
}

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
VOS_VOID NAS_RABM_SndAtSetVoicePreferParaCnf(
    MN_CLIENT_ID_T                      usClientId,                             /* AT����Ϣ��RABM������ClientId */
    MN_OPERATION_ID_T                   ucOpId,                                 /* AT����Ϣ��RABM������OpId */
    AT_RABM_PARA_SET_RSLT_ENUM_UINT32   enRslt
)
{
    /* ��AT�������ý�� */
    VOS_UINT32                                              ulRet;                        /* �������VOS���ͺ����ķ���ֵ */
    RABM_AT_SET_VOICEPREFER_PARA_CNF_STRU                  *pstMsg = VOS_NULL_PTR;        /* ����ԭ������ָ�� */

    /* �����ڴ�  */
    pstMsg = (RABM_AT_SET_VOICEPREFER_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RABM_AT_SET_VOICEPREFER_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtSetVoicePreferParaCnf:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* ��д��ز��� */
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_AT;
    pstMsg->stMsgHeader.ulLength          = sizeof(RABM_AT_SET_VOICEPREFER_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = ID_RABM_AT_SET_VOICEPREFER_PARA_CNF;
    pstMsg->enRslt                        = enRslt;
    pstMsg->usClientId                    = usClientId;
    pstMsg->ucOpId                        = ucOpId;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG(WUEPS_PID_RABM, pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtSetVoicePreferParaCnf:ERROR:PS_SEND_MSG ");
        return;
    }

    return;
}
VOS_VOID NAS_RABM_SndAtQryVoicePreferParaCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT32                           ulRslt
)
{
    /* ��AT���Ͳ�ѯ��� */
    VOS_UINT32                                              ulRet;                        /* �������VOS���ͺ����ķ���ֵ */
    RABM_AT_QRY_VOICEPREFER_PARA_CNF_STRU                  *pstMsg = VOS_NULL_PTR;        /* ����ԭ������ָ�� */

    /* �����ڴ�  */
    pstMsg = (RABM_AT_QRY_VOICEPREFER_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RABM_AT_QRY_VOICEPREFER_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtQryVoicePreferParaCnf:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* ��д��ز��� */
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_AT;
    pstMsg->stMsgHeader.ulLength          = sizeof(RABM_AT_QRY_VOICEPREFER_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName         = ID_RABM_AT_QRY_VOICEPREFER_PARA_CNF;
    pstMsg->usClientId                    = usClientId;
    pstMsg->ucOpId                        = ucOpId;
    pstMsg->ulRslt                        = ulRslt;


    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG(WUEPS_PID_RABM, pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtQryVoicePreferParaCnf:ERROR:PS_SEND_MSG ");
        return;
    }

    return;
}
VOS_VOID NAS_RABM_SndAtVoicePreferActStatus(VOS_UINT32 ulVpStatus)
{
    /* ��AT���Ͳ�ѯ��� */
    VOS_UINT32                                              ulRet;                        /* �������VOS���ͺ����ķ���ֵ */
    RABM_AT_VOICEPREFER_STATUS_REPORT_STRU                 *pstMsg = VOS_NULL_PTR;        /* ����ԭ������ָ�� */
    MN_CLIENT_ID_T                                          usClientId;

    usClientId = MN_GetRealClientId(MN_CLIENT_ALL, WUEPS_PID_RABM);

    /* �����ڴ�  */
    pstMsg = (RABM_AT_VOICEPREFER_STATUS_REPORT_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RABM_AT_VOICEPREFER_STATUS_REPORT_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtVoicePreferActStatus:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* ��д��ز��� */
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_AT;
    pstMsg->stMsgHeader.ulLength          = sizeof(RABM_AT_VOICEPREFER_STATUS_REPORT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = ID_RABM_AT_VOICEPREFER_STATUS_REPORT;
    pstMsg->usClientId                    = usClientId;
    pstMsg->ucOpId                        = 0;
    pstMsg->ulVpStatus                    = ulVpStatus;


    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG(WUEPS_PID_RABM, pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndAtVoicePreferActStatus:ERROR:PS_SEND_MSG ");
        return;
    }

    return;
}
VOS_VOID  NAS_RABM_SndCdsVoicePreferActInd(VOS_UINT32 ulVpInd)
{
    RABM_CDS_VOICEPREFER_ACT_IND_STRU   *pstMsg = VOS_NULL_PTR;

    pstMsg = (RABM_CDS_VOICEPREFER_ACT_IND_STRU*)PS_ALLOC_MSG(WUEPS_PID_RABM,
                             sizeof(RABM_CDS_VOICEPREFER_ACT_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndCdsVoicePreferActInd:ERROR:Alloc Mem Fail.");
        return;
    }

    /* ��Ϣ��ֵ */
    pstMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid       = UEPS_PID_CDS;
    pstMsg->enMsgId             = ID_RABM_CDS_VOICEPREFER_ACT_IND;
    pstMsg->ulVoicePreferActInd = ulVpInd;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_RABM, pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_RABM, "NAS_RABM_SndCdsVoicePreferActInd:WARNING:SEND MSG FIAL");
    }

    return;
}

VOS_VOID NAS_RABM_SndWasVoicePreferStartReq(VOS_VOID)
{
    VOS_UINT32                          ulRet;                              /* �������VOS���ͺ����ķ���ֵ */
    RRRABM_VOICEPREFER_START_REQ_STRU  *pstMsg = VOS_NULL_PTR;             /* ����ԭ������ָ�� */

    /* �����ڴ�  */
    pstMsg = (RRRABM_VOICEPREFER_START_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RRRABM_VOICEPREFER_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasVpActivateInd:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* ��д��ز��� */
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_WRR;
    pstMsg->MsgHeader.ulLength          = sizeof(RRRABM_VOICEPREFER_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = RRRABM_VOICEPREFER_START_REQ;

    PS_MEM_SET(pstMsg->aucReserve1,0x00,sizeof(pstMsg->aucReserve1));

    /* ����VOS����ԭ�� */
     ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_RABM, (struct MsgCB **)&pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasVpActivateInd:ERROR:PS_SEND_MSG ");
        return ;
    }

    return;
}


VOS_VOID NAS_RABM_SndWasVoicePreferStopReq(VOS_VOID)
{
    VOS_UINT32                          ulRet;                              /* �������VOS���ͺ����ķ���ֵ */
    RRRABM_VOICEPREFER_STOP_REQ_STRU    *pstMsg = VOS_NULL_PTR;             /* ����ԭ������ָ�� */

    /* �����ڴ�  */
    pstMsg = (RRRABM_VOICEPREFER_STOP_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(RRRABM_VOICEPREFER_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstMsg )
    {
        /* �ڴ�����ʧ�� */
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasVpActivateInd:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* ��д��ز��� */
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_WRR;
    pstMsg->MsgHeader.ulLength          = sizeof(RRRABM_VOICEPREFER_STOP_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = RRRABM_VOICEPREFER_STOP_REQ;

    PS_MEM_SET(pstMsg->aucReserve1,0x00,sizeof(pstMsg->aucReserve1));

    /* ����VOS����ԭ�� */
     ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_RABM, (struct MsgCB **)&pstMsg);
    if ( VOS_OK != ulRet )
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM, "NAS_RABM_SndWasVpActivateInd:ERROR:PS_SEND_MSG ");
        return ;
    }

    return;
}

VOS_VOID NAS_RABM_SendVpActIndToOtherModule(VOS_UINT32 ulVpActInd)
{
    /* �ϱ���AT */
    NAS_RABM_SndAtVoicePreferActStatus(ulVpActInd);

    /* �ϱ���CDS */
    NAS_RABM_SndCdsVoicePreferActInd(ulVpActInd);
    /* �ϱ���WRR */

    if (VOS_TRUE == ulVpActInd)
    {
        NAS_RABM_SndWasVoicePreferStartReq();
    }
    else
    {
        NAS_RABM_SndWasVoicePreferStopReq();
    }

    return;
}


#endif
/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

