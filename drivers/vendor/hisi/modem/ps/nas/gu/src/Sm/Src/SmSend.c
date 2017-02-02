/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SmSend.c
  Description  :
  Function List:
              1.  SM_ComGetTI
              2.  SM_SndPdpActReqMsg
              3.  SM_SndReqPdpActRejMsg
              4.  SM_SndPdpDeActReqMsg
              5.  SM_SndPdpModAccMsg
              6.  SM_SndPdpModReqMsg
              7.  SM_SndPdpActSecReqMsg
              8.  SM_SndPdpDeActAccMsg
              9.  NAS_SM_SndGmmPdpStatusInd
             10.  NAS_SM_SndGmmEstablishReq
             11.  SM_SndTafSmPdpMsg
             12.  SM_SndTafSmPdpActivateRej
             13.  SM_SndTafSmPdpActivateInd
             14.  SM_SndTafSmPdpActivateCnf
             15.  SM_SndTafSmPdpDeActCnf
             16.  SM_SndTafSmPdpDeActInd
             17.  SM_SndTafSmPdpModifyInd
             18.  SM_SndTafSmPdpModifyCnf
             19.  SM_SndTafSmPdpModifyRej
             20.  SM_SndTafSmPdpActSecCnf
             21.  SM_SndTafSmPdpActSecRej
             22.  SM_SndRabmSmActivateInd
             23.  SM_SndRabmSmModifyInd
             24.  SM_SndRabmSmDeactivateInd
             25.  SM_SndNwStatusMsg
             26.  SM_MemFree
             27.  SM_GetMostHighPri
             28.  SM_SndTafMsg
             29.  SM_SndStatusMsg
  History:
      1.   ��־��      2003.12.09   �¹�����
*******************************************************************************/
#include "SmInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SM_SEND_C


/*******************************************************************************
  Module:      SM_ReportM2NOtaMsg
  Function:    ��trace�й�ȡSM�Ŀտ���Ϣ
  Input:       NAS_MSG_STRU*   pNasMsg   SM�տ���Ϣ
  NOTE:
  Return:      VOS_VOID
  History:
      1. ³��    2009.07.11   �¹�����
*******************************************************************************/
VOS_VOID SM_ReportM2NOtaMsg(NAS_MSG_STRU *pNasMsg)
{
    NAS_OTA_MSG_ID_ENUM_UINT16 usNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;
    VOS_UINT8            ucMsgType;

    /*TI���Ȳ�ͬ��msg type��aucNasMsg��indexҲ��һ��*/
    if((pNasMsg->aucNasMsg[0]&0x70)==0x70 )
    {
        ucMsgType = pNasMsg->aucNasMsg[2];
    }
    else
    {
        ucMsgType = pNasMsg->aucNasMsg[1];
    }

    PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_ReportM2NOtaMsg:NORMAL: msg type is", ucMsgType);

    switch(ucMsgType)
    {
        case SM_ACT_PDP_CONTEXT_REQ:
            usNasOtaMsyId = NAS_OTA_MSG_ACT_PDP_CONTEXT_REQ;
            break;

        case SM_REQ_PDP_CONTEXT_REJ:
            usNasOtaMsyId = NAS_OTA_MSG_REQ_PDP_CONTEXT_REJ;
            break;

        case SM_DEACT_PDP_CONTEXT_REQ:
            usNasOtaMsyId = NAS_OTA_MSG_DEACT_PDP_CONTEXT_REQ;
            break;

        case SM_DEACT_PDP_CONTEXT_ACC:
            usNasOtaMsyId = NAS_OTA_MSG_DEACT_PDP_CONTEXT_MS_ACC;
            break;

        case SM_MOD_PDP_CONTEXT_ACC_M2N:
            usNasOtaMsyId = NAS_OTA_MSG_MOD_PDP_CONTEXT_ACC_M2N;
            break;

        case SM_MOD_PDP_CONTEXT_REQ_M2N:
            usNasOtaMsyId = NAS_OTA_MSG_MOD_PDP_CONTEXT_REQ_M2N;
            break;

        case SM_ACT_SEC_PDP_CONTEXT_REQ:
            usNasOtaMsyId = NAS_OTA_MSG_ACT_SEC_PDP_CONTEXT_REQ;
            break;

        case SM_STATUS:
            usNasOtaMsyId = NAS_OTA_MSG_SM_MS_STATUS;
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ReportM2NOtaMsg:WARNING: Invalid Msg id");
            /*������SM�Ŀտ���Ϣ����trace�в���ʾ*/
            return;
    }

    NAS_SendAirMsgToOM(WUEPS_PID_SM, usNasOtaMsyId, NAS_OTA_DIRECTION_UP, pNasMsg->ulNasMsgSize + 4, (VOS_UINT8*)pNasMsg);
}

/*******************************************************************************
  Module:      SM_ComGetTI
  Function:    ȡ��Transaction identifier
  Input:       VOS_UINT8                  ucSMIndex        SM����
               VOS_UINT8                  *pTemp           �洢TI��ָ��
               VOS_UINT32                  *ulSum           ������
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  ��־��      2003.12.08   �¹�����
*******************************************************************************/
VOS_VOID SM_ComGetTI(
                       VOS_UINT8                  ucSMIndex,                        /* SM����                                   */
                       VOS_UINT8                  **pTemp,                          /* �洢TI��ָ��                             */
                       VOS_UINT32                  *ulSum                            /* ������                                   */
                )
{
    VOS_UINT8           ucTi;                                                       /* ������ʱ����                             */

    if(SM_TI_NET_ORG != g_SmEntity.aPdpCntxtList[ucSMIndex].ucTiFlg)
    {                                                                           /* ���������γɵ����                       */
        if(0x80 == (g_SmEntity.aPdpCntxtList[ucSMIndex].ucTi & 0x80))
        {
            ucTi = g_SmEntity.aPdpCntxtList[ucSMIndex].ucTi & 0x7f;             /* ȡ��Transaction identifier               */
        }
        else
        {
            ucTi = g_SmEntity.aPdpCntxtList[ucSMIndex].ucTi & 0x07;             /* ȡ��Transaction identifier               */
        }
    }
    else
    {
        ucTi = g_SmEntity.aPdpCntxtList[ucSMIndex].ucTi;                        /* ȡ��Transaction identifier               */
    }
    if( ucTi < 0x07 )
    {                                                                           /* TIռ��1/2�ֽڣ�TI����չ                  */
        if( g_SmEntity.aPdpCntxtList[ucSMIndex].ucTiFlg
            == SM_TI_NET_ORG )
        {                                                                       /* �����γ�                                 */
            **pTemp = ((ucTi << 4) & 0x70) | 0x80;                              /* ���TI,Ti Flag��1                        */
            **pTemp = (**pTemp) | NAS_PD_SM;                                    /* �趨PD                                   */
        }
        else
        {                                                                       /* MS�γ�                                   */
            **pTemp = (ucTi << 4) & 0x70;                                       /* ���TI,Ti Flag��0                        */
            **pTemp = (**pTemp) | NAS_PD_SM;                                    /* �趨PD                                   */
        }
        (*pTemp)++;                                                             /* ����ָ��ƫ�Ƶĳ���                       */
        *ulSum += 1;                                                            /* ��������1                                */
    }
    else
    {                                                                           /* TIռ��3/2�ֽڣ�TI����չ                  */
        if( SM_TI_NET_ORG == g_SmEntity.aPdpCntxtList[ucSMIndex].ucTiFlg )
        {                                                                       /* �����γ�                                 */
            **pTemp = 0xF0;                                                     /* Ti Flag��1                               */
            **pTemp = (**pTemp) | NAS_PD_SM;                                    /* �趨PD                                   */
            (*pTemp)++;                                                         /* ����ָ��ƫ�Ƶĳ���                       */
            **pTemp = ucTi | 0x80;                                              /* ���TI                                   */
        }
        else
        {                                                                       /* MS�γ�                                   */
            **pTemp = 0x70;                                                     /* Ti Flag��0                               */
            **pTemp = (**pTemp) | NAS_PD_SM;                                    /* �趨PD                                   */
            (*pTemp)++;                                                         /* ����ָ��ƫ�Ƶĳ���                       */
            **pTemp = ucTi | 0x80;                                              /* ���TI                                   */
        }
        (*pTemp)++;                                                             /* ����ָ��ƫ�Ƶĳ���                       */
        *ulSum += 2;                                                            /* ��������2                                */
    }
    return;
}

/*lint -e438 -e830*/

VOS_VOID SM_SndPdpActReqMsg(
   SMREG_PDP_ACTIVATE_REQ_STRU         *pMsgIE,
   VOS_UINT8                            ucSMIndex
)
{
    VOS_UINT8           *pTemp;                                                 /* ����UCHAR����ʱָ��                      */
    VOS_UINT8           *pSendMsg;                                              /* ����UCHAR��ָ��                          */
    VOS_UINT32           ulSum;                                                 /* ���������                               */
    VOS_UINT8            ucInitType;

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                         /* ��������ڴ�                             */
    if(VOS_NULL_PTR == pTemp)
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndPdpActReqMsg:ERROR: alloc msg fail!\r");
        return;
    }
    pSendMsg = pTemp;                                                           /* ָ����ʱָ��                             */
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */

    SM_ComGetTI(ucSMIndex, &pTemp, &ulSum);                                     /* ���ú����洢TI��TI Flag                  */
    *pTemp = SM_ACT_PDP_CONTEXT_REQ;                                            /* �����Ϣ���ͣ�����ָ��ƫ�Ƶĳ���         */
    pTemp++;                                                                    /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += 1;                                                                 /* ��������1                                */
    *pTemp = ucSMIndex + SM_NSAPI_OFFSET;                                       /* Requested NSAPI��ֵ,����ָ��ƫ�Ƶĳ���   */
    pTemp++;                                                                    /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += 1;                                                                 /* ��������1                                */

    if (pMsgIE->bitOpSapi)
    {
        *pTemp = pMsgIE->ucSapi;                                                /*V200�м���ʱ�����SAPIһ��Ϊ3*/
    }
    else
    {
        *pTemp = SM_SAPI_NOT_ASSIGN;                                           /* Requested LLC SAPI��ֵ����ָ��ƫ�Ƶĳ��� */
    }

    pTemp++;                                                                    /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += 1;                                                                 /* ��������1                                */

    *pTemp = (VOS_UINT8)(pMsgIE->stReqQos.ulQosLen);                            /* ���Requested QoS����                    */

    pTemp++;                                                                    /* ����ָ��ƫ�Ƶĳ���                       */
    SM_MemCpy(pTemp,
        (const VOS_VOID *)pMsgIE->stReqQos.aucQos, pMsgIE->stReqQos.ulQosLen);  /* ���Requested QoS����                    */

    pTemp += pMsgIE->stReqQos.ulQosLen;                                         /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += pMsgIE->stReqQos.ulQosLen + 1;                                     /* ���¼�����                               */

    *pTemp = (VOS_UINT8)(pMsgIE->stReqPdpAddr.ulPdpAddrLen);                    /* ���Requested PDP address����            */

    pTemp++;                                                                    /* ����ָ��ƫ�Ƶĳ���                       */
    SM_MemCpy(pTemp, pMsgIE->stReqPdpAddr.aucPdpAddr,
              pMsgIE->stReqPdpAddr.ulPdpAddrLen);                               /* ���Requested PDP address����            */
    pTemp += pMsgIE->stReqPdpAddr.ulPdpAddrLen;                                 /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += pMsgIE->stReqPdpAddr.ulPdpAddrLen + 1;                             /* ���¼�����                               */
    if( SM_TRUE == pMsgIE->bitOpAcsPointName )
    {                                                                           /* Access point name����                    */
        *pTemp = 0x28;                                                          /* ���IEI                                  */
        pTemp++;                                                                /* ����ָ��ƫ�Ƶĳ���                       */
        *pTemp = (VOS_UINT8)(pMsgIE->stAcsPointName.ulApnLen);                  /* ���Access point name����                */
        SM_MemCpy((pTemp + 1), pMsgIE->stAcsPointName.aucApnAddr,
            pMsgIE->stAcsPointName.ulApnLen);                                   /* ���Access point name����                */
        pTemp += pMsgIE->stAcsPointName.ulApnLen + 1;                           /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum += pMsgIE->stAcsPointName.ulApnLen + 2;                           /* ���¼�����                               */
    }
    if( SM_TRUE == pMsgIE->bitOpProtCfgOpt )
    {                                                                           /* Protocol configuration options����       */
        *pTemp = 0x27;                                                          /* ���IEI                                  */
        pTemp++;                                                                /* ����ָ��ƫ�Ƶĳ���                       */
        *pTemp = (VOS_UINT8)(pMsgIE->stProtCfgOpt.ulPcoLen);                    /* ���Protocol configuration options����   */
        SM_MemCpy(pTemp + 1, pMsgIE->stProtCfgOpt.aucProtCfgOpt,
            pMsgIE->stProtCfgOpt.ulPcoLen);                                     /* ���Protocol configuration options����   */
        pTemp += pMsgIE->stProtCfgOpt.ulPcoLen + 1;                             /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum += pMsgIE->stProtCfgOpt.ulPcoLen + 2;                             /* ���¼�����                               */
    }

    SM_SndTafMsg(pSendMsg, ucSMIndex,ulSum,SM_GetMostHighPri(), SM_TRUE);       /* �������͵Ŀտ���Ϣ���͸�GMM              */
    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->NW: Activate PDP context request\r");
    ucInitType = ACTIVE_REQUEST_INIT_TYPE_MO;
    NAS_EventReport(WUEPS_PID_SM,
                    NAS_OM_EVENT_PDP_ACTIVE_REQ,
                    (VOS_VOID *)&ucInitType,
                    NAS_OM_EVENT_PDP_ACTIVE_REQ_LEN);

    return;
}
/*lint +e438 +e830*/

/*lint -e438 -e830*/

VOS_VOID SM_SndReqPdpActRejMsg(
                       SMREG_PDP_ACTIVATE_REJ_RSP_STRU   *pMsgIE,               /* ��Ϣָ��                                 */
                       VOS_UINT8                          ucTi                  /* Transaction identifier                   */
                          )
{
    VOS_UINT8           *pTemp;                                                 /* ����UCHAR����ʱָ��                      */
    VOS_UINT8           *pSendMsg;                                              /* ����UCHAR��ָ��                          */
    VOS_UINT32           ulSum;                                                 /* ���������                               */
    VOS_UINT8            ucSmCause;

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                         /* ��������ڴ�                             */
    if ( VOS_NULL_PTR == pTemp )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndReqPdpActRejMsg:ERROR:Alloc msg fail!" );
        return;
    }

    pSendMsg = pTemp;                                                           /* ָ����ʱָ��                             */
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */

    if( SM_INVALID_NSAPI != g_TiMapToNsapi[ucTi] )
    {                                                                           /* ʵ�����                                 */
        SM_ComGetTI(g_TiMapToNsapi[ucTi], &pTemp, &ulSum);                      /* ���ú����洢TI��TI Flag                  */
    }
    else
    {                                                                           /* ʵ�岻����                               */
        if( ucTi < 0x07 )
        {                                                                       /* TIռ��1/2�ֽ�                            */
            *pTemp = ((ucTi << 4) & 0x70) | 0x80;                               /* ���TI,Ti Flag��1                        */
            *pTemp = *pTemp | NAS_PD_SM;                                        /* �趨PD                                   */
            pTemp++;                                                            /* ����ָ��ƫ�Ƶĳ���                       */
            ulSum += 1;                                                         /* ��������1                                */
        }
        else
        {                                                                       /* TIռ��3/2�ֽ�                            */
            *pTemp = 0xF0;                                                      /* Ti Flag��1                               */
            *pTemp = *pTemp | NAS_PD_SM;                                        /* �趨PD                                   */
            pTemp++;                                                            /* ����ָ��ƫ�Ƶĳ���                       */
            *pTemp = ucTi | 0x80;                                               /* ���TI                                   */
            pTemp++;                                                            /* ����ָ��ƫ�Ƶĳ���                       */
            ulSum += 2;                                                         /* ��������2                                */
        }
    }
    *pTemp = SM_REQ_PDP_CONTEXT_REJ;                                            /* �����Ϣ���ͣ�����ָ��ƫ�Ƶĳ���         */
    pTemp++;                                                                    /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += 1;                                                                 /* ��������1                                */
    if( SM_NULL != pMsgIE )
    {                                                                           /* ��Ϣ��Ϊ��                               */
        *pTemp = NAS_SM_TRANS_TAF_CAUSE(pMsgIE->enCause);                                             /* ���SM cause                             */
        pTemp++;                                                                /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum += 1;                                                             /* ��������1                                */
    }
    else
    {
        *pTemp = TAF_SM_REJ_CAUSE_INSUFF_RESOURCE;                              /* ���SM cause                             */
        ulSum += 1;                                                             /* ��������1                                */
    }

    SM_SndTafMsg(pSendMsg, g_TiMapToNsapi[ucTi], ulSum, SM_GetMostHighPri(),
        SM_FALSE);                                                              /* �������͵Ŀտ���Ϣ���͸�GMM              */

    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->NW: Request PDP context activation reject\r");
    if( SM_NULL != pMsgIE )
    {
        ucSmCause = NAS_SM_TRANS_TAF_CAUSE(pMsgIE->enCause);

        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_ACTIVE_FAIL,
                        (VOS_VOID *)&ucSmCause,
                        NAS_OM_EVENT_PDP_ACTIVE_FAIL_LEN);
    }

    return;
}
/*lint +e438 +e830*/

/*lint -e438 -e830*/

VOS_VOID SM_SndPdpDeActReqMsg(
                       SMREG_PDP_DEACTIVATE_REQ_STRU *pMsgIE,                      /* ��Ϣָ��                                 */
                       VOS_UINT8                      ucSMIndex                     /* SM����                                   */
                         )
{
    VOS_UINT8           *pTemp;                                                     /* ����UCHAR����ʱָ��                      */
    VOS_UINT8           *pSendMsg;                                                  /* ����UCHAR��ָ��                          */
    VOS_UINT32           ulSum;                                                      /* ���������                               */
    VOS_UINT8            ucInitType;

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                             /* ��������ڴ�                             */
    if ( VOS_NULL_PTR == pTemp )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndPdpDeActReqMsg:ERROR:Alloc msg fail!" );
        return;
    }

    pSendMsg = pTemp;                                                           /* ָ����ʱָ��                             */
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */

    SM_ComGetTI(ucSMIndex, &pTemp, &ulSum);                                     /* ���ú����洢TI��TI Flag                  */
    *pTemp = SM_DEACT_PDP_CONTEXT_REQ;                                          /* �����Ϣ���ͣ�����ָ��ƫ�Ƶĳ���         */
    pTemp++;                                                                    /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += 1;                                                                 /* ��������1                                */
    if( SM_NULL != pMsgIE )
    {                                                                           /* ��Ϣ��Ϊ��                               */
        *pTemp = NAS_SM_TRANS_TAF_CAUSE(pMsgIE->enCause);                                             /* ���SM cause                             */
        pTemp++;                                                                /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum += 1;                                                             /* ��������1                                */
        if( SM_TRUE == pMsgIE->bitOpTearDownInd )
        {                                                                       /* Tear down indicator����                  */
            /* 0:tear down not requested;1:tear down requested.
               0ʱ����Ҫ����IE*/
            if (0 != (pMsgIE->ucTearDownInd ))
            {
                *pTemp = 0x90 | (pMsgIE->ucTearDownInd);                        /* ���IEI,TDI flag                         */
                pTemp++;                                                            /* ����ָ��ƫ�Ƶĳ���                       */
                ulSum += 1;                                                         /* ��������1                                */
            }
        }
    }
    else
    {
        *pTemp = TAF_SM_REJ_CAUSE_INSUFF_RESOURCE;                              /* ���SM cause                             */
        ulSum += 1;                                                             /* ��������1                                */
    }

    SM_SndTafMsg(pSendMsg, ucSMIndex, ulSum,
                GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL, SM_TRUE);                   /* �������͵Ŀտ���Ϣ���͸�GMM              */

    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->NW: Deactivate PDP context request\r");
    ucInitType = DEACTIVE_REQUEST_INIT_TYPE_MO;
    NAS_EventReport(WUEPS_PID_SM,
                    NAS_OM_EVENT_PDP_DEACTIVE_REQ,
                    (VOS_VOID *)&ucInitType,
                    NAS_OM_EVENT_PDP_DEACTIVE_REQ_LEN);

    return;
}
/*lint +e438 +e830*/

/*lint -e438 -e830*/
/*******************************************************************************
  Module:      SM_SndPdpModAccMsg
  Function:    ��TAF����SM��TAFSM_PDP_MODIFY_RSP��Ϣת��������������
  Input:       SMREG_PDP_MODIFY_RSP_STRU     *pMsgIE          ��Ϣָ��
               VOS_UINT8                      ucSMIndex        SM����
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  ��־��      2003.12.09   �¹�����
*******************************************************************************/
VOS_VOID SM_SndPdpModAccMsg(
                       SMREG_PDP_MODIFY_RSP_STRU  *pMsgIE,                      /* ��Ϣָ��                                 */
                       VOS_UINT8                   ucSMIndex                    /* SM����                                   */
                       )
{
    VOS_UINT8           *pTemp;                                                 /* ����UCHAR����ʱָ��                      */
    VOS_UINT8           *pSendMsg;                                              /* ����UCHAR��ָ��                          */
    VOS_UINT32           ulSum;                                                 /* ���������                               */

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                         /* ��������ڴ�                             */
    if ( VOS_NULL_PTR == pTemp )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndPdpModAccMsg:ERROR:Alloc msg fail!" );
        return;
    }
    pSendMsg = pTemp;                                                           /* ָ����ʱָ��                             */
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */

    SM_ComGetTI(ucSMIndex, &pTemp, &ulSum);                                     /* ���ú����洢TI��TI Flag                  */
    *pTemp = SM_MOD_PDP_CONTEXT_ACC_M2N;                                        /* �����Ϣ���ͣ�����ָ��ƫ�Ƶĳ���         */
    pTemp++;                                                                    /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += 1;                                                                 /* ��������1                                */

    SM_SndTafMsg(pSendMsg,ucSMIndex, ulSum,
                GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL, SM_FALSE);                  /* �������͵Ŀտ���Ϣ���͸�GMM              */

    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->NW: Modify PDP context accept (MS to network direction)\r");
    NAS_EventReport(WUEPS_PID_SM,
                    NAS_OM_EVENT_PDP_CONTEXT_MODIFY_SUCC,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    return;
}
/*lint +e438 +e830*/

/*lint -e438 -e830*/

VOS_VOID NAS_SM_SndPdpModRejMsg(
    SMREG_PDP_MODIFY_REJ_RSP_STRU      *pstMsgIE,
    VOS_UINT8                           ucSMIndex
)
{
    VOS_UINT8                           *pucTemp;
    VOS_UINT8                           *pucSendMsg;
    VOS_UINT32                          ulSum;

    pucTemp = (VOS_UINT8*)SM_Malloc(SM_MAX_SND_MSG_LEN);                        /* ��������ڴ�                             */
    if (VOS_NULL_PTR == pucTemp)
    {
        NAS_ERROR_LOG(WUEPS_PID_SM, "NAS_SM_SndPdpModRejMsg:ERROR:Alloc msg fail!\r\n");
        return;
    }

    pucSendMsg  = pucTemp;                                                      /* ָ����ʱָ��                             */
    ulSum       = 0;                                                            /* ��������ʼֵ��0                          */

    SM_ComGetTI(ucSMIndex, &pucTemp, &ulSum);                                   /* ���ú����洢TI��TI Flag                  */
    *pucTemp = SM_MOD_PDP_CONTEXT_REJ;                                          /* �����Ϣ���ͣ�����ָ��ƫ�Ƶĳ���         */
    pucTemp++;                                                                  /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += 1;                                                                 /* ��������1                                */

    if (VOS_NULL_PTR != pstMsgIE)
    {
        *pucTemp = NAS_SM_TRANS_TAF_CAUSE(pstMsgIE->enCause);                                         /* ���SM cause                             */
        pucTemp++;                                                              /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum += 1;                                                             /* ��������1                                */
    }
    else
    {
        *pucTemp = TAF_SM_REJ_CAUSE_INSUFF_RESOURCE;                            /* ���SM cause                             */
        ulSum += 1;                                                             /* ��������1                                */
    }

    SM_SndTafMsg(pucSendMsg, ucSMIndex, ulSum,
                GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL, SM_FALSE);                  /* �������͵Ŀտ���Ϣ���͸�GMM              */

    NAS_NORMAL_LOG(WUEPS_PID_SM,
        "NAS_SM_SndPdpModRejMsg: SM->NW: Modify PDP context reject\r\n");

    NAS_EventReport(WUEPS_PID_SM,
                    NAS_OM_EVENT_PDP_CONTEXT_MODIFY_FAIL,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    return;
}
/*lint +e438 +e830*/

/*lint -e438 -e830*/
/*******************************************************************************
  Module:      SM_SndPdpModReqMsg
  Function:    ��TAF����SM��TAFSM_PDP_MODIFY_REQ��Ϣת��������������
  Input:       SMREG_PDP_MODIFY_REQ_STRU    *pMsgIE           ��Ϣָ��
               VOS_UINT8                     ucSMIndex        SM����
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  ��־��      2003.12.09   �¹�����
*******************************************************************************/
VOS_VOID SM_SndPdpModReqMsg(
                       SMREG_PDP_MODIFY_REQ_STRU *pMsgIE,                       /* ��Ϣָ��                                 */
                       VOS_UINT8                  ucSMIndex                     /* SM����                                   */
                       )
{
    VOS_UINT8           *pTemp;                                                 /* ����UCHAR����ʱָ��                      */
    VOS_UINT8           *pSendMsg;                                              /* ����UCHAR��ָ��                          */
    VOS_UINT32           ulSum;                                                 /* ���������                               */
    VOS_UINT8            ucInitType;

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                         /* ��������ڴ�                             */
    if(VOS_NULL_PTR == pTemp)
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndPdpModReqMsg:ERROR: alloc msg fail!\r");
        return;
    }
    pSendMsg = pTemp;                                                           /* ָ����ʱָ��                             */
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */

    SM_ComGetTI(ucSMIndex, &pTemp, &ulSum);                                     /* ���ú����洢TI��TI Flag                  */
    *pTemp = SM_MOD_PDP_CONTEXT_REQ_M2N;                                        /* �����Ϣ���ͣ�����ָ��ƫ�Ƶĳ���         */
    pTemp++;                                                                    /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += 1;                                                                 /* ��������1                                */
    *pTemp         = 0x32;                                                      /* ��дRequested LLC SAPI��IEI              */

    if ( pMsgIE->bitOpSapi)
    {
        *( pTemp + 1 ) = pMsgIE->ucSapi;
    }
    else
    {
        *( pTemp + 1 ) = SM_SAPI_NOT_ASSIGN;                                    /* ��дRequested LLC SAPI��VALUE            */
    }


    pTemp += 2;                                                                 /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += 2;                                                                 /* ��������1                                */
    if( SM_TRUE == pMsgIE->bitOpRequestedNewQos )
    {                                                                           /* Requested new QoS����                    */
        *pTemp = 0x30;                                                          /* ���IEI                                  */
        pTemp++;                                                                /* ����ָ��ƫ�Ƶĳ���                       */
        *pTemp = (VOS_UINT8)(pMsgIE->stRequestedNewQos.ulQosLen);               /* ���Requested new QoS����                */
        SM_MemCpy(pTemp+1, pMsgIE->stRequestedNewQos.aucQos,
            pMsgIE->stRequestedNewQos.ulQosLen);                                /* ���Requested new QoS����                */
        pTemp += pMsgIE->stRequestedNewQos.ulQosLen + 1;                        /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum += pMsgIE->stRequestedNewQos.ulQosLen + 2;                        /* ���¼�����                               */
    }
    if( SM_TRUE == pMsgIE->bitOpNewtft )
    {                                                                           /* New TFT����                              */
        *pTemp = 0x31;                                                          /* ���IEI                                  */
        pTemp++;                                                                /* ����ָ��ƫ�Ƶĳ���                       */
        *pTemp = (VOS_UINT8)(pMsgIE->stNewtft.ulTftLen);                        /* ���New TFT����                          */
        SM_MemCpy(pTemp + 1,
                  pMsgIE->stNewtft.aucNewtft,
                  pMsgIE->stNewtft.ulTftLen);                                   /* ���New TFT����                          */
        pTemp += pMsgIE->stNewtft.ulTftLen + 1;                                 /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum += pMsgIE->stNewtft.ulTftLen + 2;                                 /* ���¼�����                               */
    }

    SM_SndTafMsg(pSendMsg, ucSMIndex,ulSum,
                GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL, SM_TRUE);                   /* �������͵Ŀտ���Ϣ���͸�GMM              */

    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->NW: Modify PDP context request (MS to network direction)\r");
    ucInitType = MODIFY_REQUEST_INIT_TYPE_MO;
    NAS_EventReport(WUEPS_PID_SM,
                    NAS_OM_EVENT_PDP_CONTEXT_MODIFY_REQ,
                    (VOS_VOID *)&ucInitType,
                    NAS_OM_EVENT_PDP_CONTEXT_MODIFY_REQ_LEN);

    return;
}
/*lint +e438 +e830*/

/*lint -e438 -e830*/
/*******************************************************************************
  Module:      SM_SndPdpActSecReqMsg
  Function:    ��TAF����SM��TAFSM_PDP_ACTIVATE_SEC_REQ��Ϣת��������������
  Input:       SMREG_PDP_ACTIVATE_SEC_REQ_STRU  *pMsgIE          ��Ϣָ��
               VOS_UINT8                         ucSMIndex        SM����
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  ��־��      2003.12.09   �¹�����
      2.  CBJ      2005.02.18   modify
*******************************************************************************/
VOS_VOID SM_SndPdpActSecReqMsg(
                       SMREG_PDP_ACTIVATE_SEC_REQ_STRU     *pMsgIE,                       /* ��Ϣָ��                                 */
                       VOS_UINT8                            ucSMIndex                     /* SM����                                   */
                          )
{
    VOS_UINT8           *pTemp;                                                 /* ����UCHAR����ʱָ��                      */
    VOS_UINT8           *pSendMsg;                                              /* ����UCHAR��ָ��                          */
    VOS_UINT32           ulSum;                                                 /* ���������                               */
    VOS_UINT8           ucTi;
    VOS_UINT8           ucTiIndex;

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                         /* ��������ڴ�                             */
    if(VOS_NULL_PTR == pTemp)
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndPdpActSecReqMsg:ERROR: alloc msg fail!\r");
        return;
    }
    pSendMsg = pTemp;                                                           /* ָ����ʱָ��                             */
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */

    SM_ComGetTI(ucSMIndex, &pTemp, &ulSum);                                     /* ���ú����洢TI��TI Flag                  */
    *pTemp = SM_ACT_SEC_PDP_CONTEXT_REQ;                                        /* �����Ϣ���ͣ�����ָ��ƫ�Ƶĳ���         */
    pTemp++;                                                                    /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += 1;                                                                 /* ��������1                                */
    *pTemp = ucSMIndex + SM_NSAPI_OFFSET;                                       /* Requested NSAPI��ֵ,����ָ��ƫ�Ƶĳ���   */
    pTemp++;                                                                    /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += 1;                                                                 /* ��������1                                */

    if ( pMsgIE->bitOpSapi)
    {
        *pTemp = pMsgIE->ucSapi;
    }
    else
    {
        *pTemp = SM_SAPI_NOT_ASSIGN;                                            /* Requested LLC SAPI��ֵ����ָ��ƫ�Ƶĳ��� */
    }

    pTemp++;                                                                    /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += 1;                                                                 /* ��������1                                */

    *pTemp = (VOS_UINT8)(pMsgIE->stRequestedQos.ulQosLen);                      /* ���Requested QoS����                    */

    SM_MemCpy(pTemp + 1,
            pMsgIE->stRequestedQos.aucQos, pMsgIE->stRequestedQos.ulQosLen);    /* ���Requested QoS����                    */
    pTemp += pMsgIE->stRequestedQos.ulQosLen + 1;                               /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += pMsgIE->stRequestedQos.ulQosLen + 1;                               /* ���¼�����                               */
    ucTi = g_SmEntity.aPdpCntxtList[pMsgIE->ucPrimNsapi
        - SM_NSAPI_OFFSET].ucTi & 0x7f;                                         /* ȡ��Transaction identifier               */
    ucTiIndex = g_SmEntity.aPdpCntxtList[pMsgIE->ucPrimNsapi
        - SM_NSAPI_OFFSET].ucTi;                                                /* ���g_TiMapToNsapi���±�                 */
    if( ucTi < 0x07 )
    {                                                                           /* Linked TIռ��2�ֽ�                       */
        *pTemp = 1;                                                             /* Linked TI���ȸ�Ϊ1                       */
        pTemp++;                                                                /* ����ָ��ƫ�Ƶĳ���                       */
        if( SM_TI_NET_ORG
             == g_SmEntity.aPdpCntxtList[g_TiMapToNsapi[ucTiIndex]].ucTiFlg )
        {                                                                       /* �����γ�                                 */
            *pTemp = ((ucTi << 4) & 0x70) | 0x80;                               /* ���TI,Ti Flag��1                        */
        }
        else
        {                                                                       /* MS�γ�                                   */
            *pTemp = (ucTi << 4) & 0x70;                                        /* ���TI,Ti Flag��0                        */
        }
        pTemp++;                                                                /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum += 2;                                                             /* ��������2                                */
    }
    else
    {                                                                           /* Linked TIռ��3�ֽ�                       */
        *pTemp = 2;                                                             /* Linked TI���ȸ�Ϊ2                       */
        pTemp++;                                                                /* ����ָ��ƫ�Ƶĳ���                       */
        if( SM_TI_NET_ORG
             == g_SmEntity.aPdpCntxtList[g_TiMapToNsapi[ucTiIndex]].ucTiFlg )
        {                                                                       /* �����γ�                                 */
            *pTemp = 0xF0;                                                      /* Ti Flag��1                               */
            pTemp++;                                                            /* ����ָ��ƫ�Ƶĳ���                       */
            *pTemp = ucTi|0x80;                                                 /* ���TI                                   */
        }
        else
        {                                                                       /* MS�γ�                                   */
            *pTemp = 0x70;                                                      /* Ti Flag��0                               */
            pTemp++;                                                            /* ����ָ��ƫ�Ƶĳ���                       */
            *pTemp = ucTi|0x80;                                                 /* ���TI                                   */
        }
        pTemp++;                                                                /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum += 3;                                                             /* ��������3                                */
    }
    if( SM_TRUE == pMsgIE->bitOpTft )
    {                                                                           /* TFT����                                  */
        *pTemp = 0x36;                                                          /* ���IEI                                  */
        pTemp++;                                                                /* ����ָ��ƫ�Ƶĳ���                       */
        *pTemp = (VOS_UINT8)(pMsgIE->stTft.ulTftLen);                           /* ���TFT����                              */
        SM_MemCpy(pTemp + 1, pMsgIE->stTft.aucNewtft, pMsgIE->stTft.ulTftLen);  /* ���TFT����                              */
        pTemp += pMsgIE->stTft.ulTftLen + 1;                                    /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum += pMsgIE->stTft.ulTftLen + 2;                                    /* ���¼�����                               */
    }

    SM_SndTafMsg(pSendMsg, ucSMIndex, ulSum, SM_GetMostHighPri(), SM_TRUE);     /* �������͵Ŀտ���Ϣ���͸�GMM              */

    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->NW: Activate Secondary PDP Context Request\r");

    return;
}
/*lint +e438 +e830*/

/*lint -e438 -e830*/
/*******************************************************************************
  Module:      SM_SndPdpDeActAccMsg
  Function:    ����DEACTIVATE PDP CONTEXT ACCEPT��GMM
  Input:       VOS_UINT8      ucSMIndex        SM����
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  ��־��      2003.12.09   �¹�����
*******************************************************************************/
VOS_VOID SM_SndPdpDeActAccMsg(VOS_UINT8   ucSMIndex)
{
    VOS_UINT8           *pTemp;                                                 /* ����UCHAR����ʱָ��                      */
    VOS_UINT8           *pSendMsg;                                              /* ����UCHAR��ָ��                          */
    VOS_UINT32           ulSum;                                                 /* ���������                               */

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                         /* ��������ڴ�                             */
    if(VOS_NULL_PTR == pTemp)
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndPdpDeActAccMsg:ERROR: alloc msg fail!\r");
        return;
    }
    pSendMsg = pTemp;                                                           /* ָ����ʱָ��                             */
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */

    SM_ComGetTI(ucSMIndex, &pTemp, &ulSum);                                     /* ���ú����洢TI��TI Flag                  */
    *pTemp = SM_DEACT_PDP_CONTEXT_ACC;                                          /* �����Ϣ���ͣ�����ָ��ƫ�Ƶĳ���         */
    pTemp++;                                                                    /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += 1;                                                                 /* ��������1                                */

    SM_SndTafMsg(pSendMsg, ucSMIndex,
                ulSum,GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL, SM_FALSE);            /* �������͵Ŀտ���Ϣ���͸�GMM              */

    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->NW: Deactivate PDP context accept\r");

    return;
}
/*lint +e438 +e830*/


VOS_VOID SM_SndTafSmPdpActivateRej(
                               VOS_UINT8                        ucCr,                           /* Call Reference                           */
                               SM_TAF_CAUSE_ENUM_UINT16         enCause,                        /* ����ԭ��                                 */
                               SM_OCT_VARY_STRU                *pProtCfgOpt                     /* Protocol configuration options           */
                              )
{
    SMREG_PDP_ACTIVATE_REJ_STRU        *pActRejMsg = VOS_NULL_PTR;              /* ����TAF�ṹָ��                          */

    pActRejMsg = (SMREG_PDP_ACTIVATE_REJ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_ACTIVATE_REJ_STRU));
    if ( VOS_NULL_PTR == pActRejMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpActivateRej:ERROR:Alloc msg fail!" );
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pActRejMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_ACTIVATE_REJ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pActRejMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pActRejMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pActRejMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_ACTIVATE_REJ;

    pActRejMsg->ucConnectId = ucCr;                                             /* �趨CR                                   */

    pActRejMsg->enCause = enCause;                                              /* ��д����SmCause                          */
    if( (SM_NULL == pProtCfgOpt) || (0 == pProtCfgOpt->ulCnt) )
    {                                                                           /* ProtCfgOpt�����ڳ���Ϊ0                  */
        pActRejMsg->bitOpProtCfgOpt = 0;                                        /* ��Ϊ������                               */
    }
    else
    {
        pActRejMsg->bitOpProtCfgOpt = 1;                                        /* ��Ϊ����                                 */

        pActRejMsg->stProtCfgOpt.ulPcoLen = pProtCfgOpt->ulCnt;                 /* ��¼ProtCfgOpt����                       */

        SM_MemCpy(pActRejMsg->stProtCfgOpt.aucProtCfgOpt,
                  pProtCfgOpt->pOcts,
                  pProtCfgOpt->ulCnt);                                          /* ��¼ProtCfgOpt����                       */
    }
    if( 0xFF == g_CrMapToNsapi[ucCr] )
    {                                                                           /* NsapiֵΪ0xFF                            */
        pActRejMsg->bitOpNsapi = 0;                                             /* ��Ϊ������                               */
    }
    else
    {
        pActRejMsg->bitOpNsapi = 1;                                             /* ��Ϊ����                                 */

        pActRejMsg->ucNsapi = g_CrMapToNsapi[ucCr] + SM_NSAPI_OFFSET;           /* ��¼Nsapi                                */
    }

    /* ��дT3380��ʱ���� */
    pActRejMsg->ucExpiredCount
        = g_SmEntity.aPdpCntxtList[g_CrMapToNsapi[ucCr]].TimerInfo.ucExpireTimes;


    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pActRejMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpActivateRej:WARNING:Send msg fail!" );
    }

    return;
}

/*******************************************************************************
  Module:      SM_SndTafSmPdpActivateInd
  Function:    ���ɺͷ���TAFSM_PDP_ACTIVATE_IND��Ϣ
  Input:       SM_NW_MSG_STRU   *pMsgIe         �յ�����Ϣ
               VOS_UINT8            ucCnxtIndex     Context����
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  ��־��      2003.12.10   �¹�����
*******************************************************************************/
VOS_VOID SM_SndTafSmPdpActivateInd(
                               SM_NW_MSG_STRU   *pMsgIe,                        /* �յ�����Ϣ                               */
                               VOS_UINT8            ucCnxtIndex                     /* Context����                              */
                              )
{
    SMREG_PDP_ACTIVATE_IND_STRU        *pActIndMsg = VOS_NULL_PTR;              /* ����TAF�ṹָ��                          */

    pActIndMsg = (SMREG_PDP_ACTIVATE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_ACTIVATE_IND_STRU));
    if ( VOS_NULL_PTR == pActIndMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpActivateInd:ERROR:Alloc msg fail!" );
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pActIndMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_ACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pActIndMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pActIndMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pActIndMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_ACTIVATE_IND;

    pActIndMsg->ucConnectId = g_SmEntity.aPdpCntxtList[ucCnxtIndex].ucCr;       /* �趨CR                                   */

    pActIndMsg->stOfferPdpAddr.ulPdpAddrLen = pMsgIe->PdpAddr.ucLen;            /* ��¼OfferPdpAddr����                     */

    SM_MemCpy(pActIndMsg->stOfferPdpAddr.aucPdpAddr,
              pMsgIe->PdpAddr.pValue,
              ( VOS_UINT32 )pMsgIe->PdpAddr.ucLen);                             /* ��¼OfferPdpAddr����                     */

    if( 0 == pMsgIe->Apn.ucLen )
    {                                                                           /* pAcsPointName����Ϊ0                     */
        pActIndMsg->bitOpAcsPointName = 0;                                      /* ��Ϊ������                               */
    }
    else
    {
        pActIndMsg->bitOpAcsPointName = 1;                                      /* ��Ϊ����                                 */

        pActIndMsg->stAcsPointName.ulApnLen = pMsgIe->Apn.ucLen;                /* ��¼pAcsPointName����                    */
        SM_MemCpy(pActIndMsg->stAcsPointName.aucApnAddr,
                  pMsgIe->Apn.pValue,
                  ( VOS_UINT32 )pMsgIe->Apn.ucLen );                            /* ��¼pAcsPointName����                    */
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pActIndMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpActivateInd:WARNING:Send msg fail!" );
    }

    return;
}
VOS_VOID SM_SndTafSmPdpActivateCnf(
                               SM_NW_MSG_STRU   *pMsgIe,                        /* �յ�����Ϣ                               */
                               VOS_UINT8         ucCnxtIndex                    /* Context����                              */
                              )
{
    SMREG_PDP_ACTIVATE_CNF_STRU        *pActCnfMsg = VOS_NULL_PTR;              /* ����TAF�ṹָ��                          */
    VOS_UINT8                           ucCr;

    pActCnfMsg = (SMREG_PDP_ACTIVATE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_ACTIVATE_CNF_STRU));
    if ( VOS_NULL_PTR == pActCnfMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpActivateCnf:ERROR:Alloc msg fail!" );
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pActCnfMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_ACTIVATE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pActCnfMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pActCnfMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pActCnfMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_ACTIVATE_CNF;

    ucCr = g_SmEntity.aPdpCntxtList[ucCnxtIndex].ucCr;
    pActCnfMsg->ucConnectId        = ucCr;                                      /* �趨CR                                   */
    pActCnfMsg->stMsgHdr.ulMsgName = ID_SMREG_PDP_ACTIVATE_CNF;                 /* �趨��Ϣ����                             */

    pActCnfMsg->stNegoQos.ulQosLen = pMsgIe->Qos.ucLen;                         /* �洢Qos����                              */

    SM_MemCpy(pActCnfMsg->stNegoQos.aucQos,
              pMsgIe->Qos.pValue,
              ( VOS_UINT32 )pMsgIe->Qos.ucLen);                                 /* �洢Qos����                              */

    if( 0 == pMsgIe->PdpAddr.ucLen )
    {                                                                           /* PdpAddr����Ϊ0                           */
        pActCnfMsg->bitOpPdpAddr = 0;                                           /* ��Ϊ������                               */
    }
    else
    {
        pActCnfMsg->bitOpPdpAddr = 1;                                           /* ��Ϊ����                                 */

        pActCnfMsg->stPdpAddr.ulPdpAddrLen = pMsgIe->PdpAddr.ucLen;             /* �洢PdpAddr����                          */

        SM_MemCpy(pActCnfMsg->stPdpAddr.aucPdpAddr,
                  pMsgIe->PdpAddr.pValue,
                  ( VOS_UINT32 )pMsgIe->PdpAddr.ucLen);                         /* �洢PdpAddr����                          */
    }

    if( 0 == pMsgIe->ProCnfgOpt.ucLen )
    {                                                                           /* ProtCfgOpt����Ϊ0                        */
        pActCnfMsg->bitOpProtCfgOpt = 0;                                        /* ��Ϊ������                               */
    }
    else
    {
        pActCnfMsg->bitOpProtCfgOpt = 1;                                        /* ��Ϊ����                                 */

        pActCnfMsg->stProtCfgOpt.ulPcoLen = pMsgIe->ProCnfgOpt.ucLen;           /* ��¼ProtCfgOpt����                       */

        SM_MemCpy(pActCnfMsg->stProtCfgOpt.aucProtCfgOpt,
                  pMsgIe->ProCnfgOpt.pValue,
                  ( VOS_UINT32 )pMsgIe->ProCnfgOpt.ucLen);                      /* ��¼ProtCfgOpt����                       */
    }
    if( 0 == pMsgIe->Pfi.ucLen )
    {                                                                           /* PacketFlowId����Ϊ0                      */
        pActCnfMsg->bitOpPacketFlowId = 0;                                      /* ��Ϊ������                               */
    }
    else
    {
        pActCnfMsg->bitOpPacketFlowId = 1;                                      /* ��Ϊ����                                 */

        pActCnfMsg->stPacketFlowId.ulPFILen = pMsgIe->Pfi.ucLen;                /* ��¼PacketFlowId����                     */

        SM_MemCpy(&pActCnfMsg->stPacketFlowId.ucPacketFlowId,
            pMsgIe->Pfi.pValue, ( VOS_UINT32 )pMsgIe->Pfi.ucLen);               /* ��¼PacketFlowId����                     */
    }
    pActCnfMsg->bitOpNsapi = 1;                                                 /* ��Ϊ����                                 */

    pActCnfMsg->ucNsapi = (ucCnxtIndex + SM_NSAPI_OFFSET);                      /* ��¼Nsapi                                */

    /*����TAF���͵���Ϣ�и�ֵ������Ϣ:*/
    if (g_aucSapi[0][0])
    {
        /*���ݴ��SAPI�������͸�APS*/
        pActCnfMsg->bitOpSapi = 1;
        pActCnfMsg->ucSapi    = g_aucSapi[0][1];
        g_aucSapi[0][0]       = 0;                                              /*���ݴ��ʶΪ��Ч*/
    }

    pActCnfMsg->bitOpRadioPriority = 1;
    pActCnfMsg->ucRadioPriority    = pMsgIe->ucRadioPri;

#if (FEATURE_ON == FEATURE_IPV6)
    if (0 == pMsgIe->stSmCauseTwo.ucLen)
    {
        pActCnfMsg->bitOpSmCause = VOS_FALSE;
    }
    else
    {
        pActCnfMsg->bitOpSmCause = VOS_TRUE;

        pActCnfMsg->enCause = NAS_SM_MapSmNWCause(*(pMsgIe->stSmCauseTwo.pValue));    /* ��¼SmCause                              */
    }
#endif

    pActCnfMsg->stTransId.ucTiFlag = NAS_SM_GetPdpTiFlg(ucCnxtIndex);

    if (SM_TI_NET_ORG != NAS_SM_GetPdpTiFlg(ucCnxtIndex))
    {
        if (0x80 == (NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x80))
        {
            pActCnfMsg->stTransId.ucTiValue
                = NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x7F;
        }
        else
        {
            pActCnfMsg->stTransId.ucTiValue
                = NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x07;
        }
    }
    else
    {
        pActCnfMsg->stTransId.ucTiValue
            = NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x7F;
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pActCnfMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpActivateCnf:WARNING:Send msg fail!" );
    }

    return;
}

/*******************************************************************************
  Module:      SM_SndTafSmPdpDeActCnf
  Function:    ���ɺͷ���TAFSM_PDP_DEACTIVATE_CNF��Ϣ
  Input:       VOS_UINT8           ucCr              Call Reference
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  ��־��      2003.12.10   �¹�����
*******************************************************************************/
VOS_VOID SM_SndTafSmPdpDeActCnf(
                            VOS_UINT8           ucCr                                /* Call Reference                           */
                           )
{
    SMREG_PDP_DEACTIVATE_CNF_STRU      *pstDeactCnfMsg = VOS_NULL_PTR;          /* ����TAF�ṹָ��                          */

    pstDeactCnfMsg = (SMREG_PDP_DEACTIVATE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_DEACTIVATE_CNF_STRU));
    if ( VOS_NULL_PTR == pstDeactCnfMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpDeActCnf:ERROR:Alloc msg fail!" );
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstDeactCnfMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_DEACTIVATE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstDeactCnfMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstDeactCnfMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pstDeactCnfMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_DEACTIVATE_CNF;

    pstDeactCnfMsg->ucConnectId = ucCr;                                         /* �趨CR                                   */

    if( 0xFF == g_CrMapToNsapi[ucCr] )
    {                                                                           /* NsapiֵΪ0xFF                            */
        pstDeactCnfMsg->bitOpNsapi = 0;                                         /* ��Ϊ������                               */
    }
    else
    {
        pstDeactCnfMsg->bitOpNsapi = 1;                                         /* ��Ϊ����                                 */

        pstDeactCnfMsg->ucNsapi = g_CrMapToNsapi[ucCr] + SM_NSAPI_OFFSET;       /* ��¼Nsapi                                */
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pstDeactCnfMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpDeActCnf:WARNING:Send msg fail!" );
    }

    return;
}
VOS_VOID SM_SndTafSmPdpDeActInd(
    VOS_UINT8                           ucCr,                                   /* Call Reference                           */
    SM_TAF_CAUSE_ENUM_UINT16            enCause,
    VOS_UINT8                           ucTdi                                   /* Tear down indicator                      */
)
{
    SMREG_PDP_DEACTIVATE_IND_STRU        *pDeactIndMsg = VOS_NULL_PTR;          /* ����TAF�ṹָ��                          */

    pDeactIndMsg = (SMREG_PDP_DEACTIVATE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_DEACTIVATE_IND_STRU));
    if ( VOS_NULL_PTR == pDeactIndMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpDeActInd:ERROR:Alloc msg fail!" );
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pDeactIndMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_DEACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pDeactIndMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pDeactIndMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pDeactIndMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_DEACTIVATE_IND;

    pDeactIndMsg->ucConnectId = ucCr;                                           /* �趨CR                                   */

    pDeactIndMsg->enCause  = enCause;                                           /* �趨SmCause                              */

    if( SM_TRUE == ucTdi )
    {                                                                           /* Tear down indicatorΪ1                   */
        pDeactIndMsg->bitOpTearDownInd = 1;                                     /* ��Ϊ����                                 */

        pDeactIndMsg->ucTearDownInd = ucTdi;                                    /* TearDownInd��ֵ                          */
    }
    else
    {
        pDeactIndMsg->bitOpTearDownInd = 0;                                     /* ��Ϊ������                               */
    }

    if( 0xFF == g_CrMapToNsapi[ucCr] )
    {                                                                           /* NsapiֵΪ0xFF                            */
        pDeactIndMsg->bitOpNsapi = 0;                                           /* ��Ϊ������                               */
    }
    else
    {
        pDeactIndMsg->bitOpNsapi = 1;                                           /* ��Ϊ����                                 */

        pDeactIndMsg->ucNsapi = g_CrMapToNsapi[ucCr]+SM_NSAPI_OFFSET;           /* ��¼Nsapi                                */
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pDeactIndMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpDeActInd:WARNING:Send msg fail!" );
    }

    return;
}

/*******************************************************************************
  Module:      SM_SndTafSmPdpModifyInd
  Function:    ���ɺͷ���TAFSM_PDP_MODIFY_IND��Ϣ
  Input:       SM_NW_MSG_STRU   *pMsgIe         �յ�����Ϣ
               VOS_UINT8            ucCnxtIndex     Context����
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  ��־��      2003.12.10   �¹�����
*******************************************************************************/
VOS_VOID SM_SndTafSmPdpModifyInd(
                               SM_NW_MSG_STRU   *pMsgIe,                        /* �յ�����Ϣ                               */
                               VOS_UINT8            ucCnxtIndex                     /* Context����                              */
                            )
{
    SM_NW_MSG_STRU                     *pRcvMsgIe;
    SMREG_PDP_MODIFY_IND_STRU          *pModIndMsg = VOS_NULL_PTR;              /* ����TAF�ṹָ��                          */
    VOS_UINT8                           ucCr;
    VOS_UINT8                           ucInitType;

    pRcvMsgIe = pMsgIe;

    pModIndMsg = (SMREG_PDP_MODIFY_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_MODIFY_IND_STRU));
    if ( VOS_NULL_PTR == pModIndMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpModifyInd:ERROR:Alloc msg fail!" );
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pModIndMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_MODIFY_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pModIndMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pModIndMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pModIndMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_MODIFY_IND;

    ucCr = g_SmEntity.aPdpCntxtList[ucCnxtIndex].ucCr;
    pModIndMsg->ucConnectId = ucCr;                                             /* �趨CR                                   */

    pModIndMsg->stNewQos.ulQosLen = pRcvMsgIe->Qos.ucLen;                       /* �洢NewQos����                           */

    SM_MemCpy(pModIndMsg->stNewQos.aucQos,
              pRcvMsgIe->Qos.pValue,
              (VOS_UINT32)pRcvMsgIe->Qos.ucLen);                                /* �洢NewQos����                           */

    if( 0 == pRcvMsgIe->PdpAddr.ucLen )
    {                                                                           /* PdpAddr����Ϊ0                           */
        pModIndMsg->bitOpPdpAddr = 0;                                           /* ��Ϊ������                               */
    }
    else
    {
        pModIndMsg->bitOpPdpAddr = 1;                                           /* ��Ϊ����                                 */

        pModIndMsg->stPdpAddr.ulPdpAddrLen = pRcvMsgIe->PdpAddr.ucLen;          /* �洢PdpAddr����                          */

        SM_MemCpy(pModIndMsg->stPdpAddr.aucPdpAddr,
                  pRcvMsgIe->PdpAddr.pValue,
                  (VOS_UINT32)pRcvMsgIe->PdpAddr.ucLen);                        /* �洢PdpAddr����                          */

    }

    if( 0 == pRcvMsgIe->Pfi.ucLen )
    {                                                                           /* PacketFlowId����Ϊ0                      */
        pModIndMsg->bitOpPacketFlowId = 0;                                      /* ��Ϊ������                               */
    }
    else
    {
        pModIndMsg->bitOpPacketFlowId = 1;                                      /* ��Ϊ����                                 */

        pModIndMsg->stPacketFlowId.ulPFILen = pRcvMsgIe->Pfi.ucLen;             /* ��¼PacketFlowId����                     */

        SM_MemCpy(&pModIndMsg->stPacketFlowId.ucPacketFlowId,
                  pRcvMsgIe->Pfi.pValue,
                  (VOS_UINT32)pRcvMsgIe->Pfi.ucLen);                            /* ��¼PacketFlowId����                     */

    }
    if( 0xFF == ucCnxtIndex )
    {                                                                           /* NsapiֵΪ0xFF                            */
        pModIndMsg->bitOpNsapi = 0;                                             /* ��Ϊ������                               */
    }
    else
    {
        pModIndMsg->bitOpNsapi = 1;                                             /* ��Ϊ����                                 */

        pModIndMsg->ucNsapi = ucCnxtIndex + SM_NSAPI_OFFSET;                    /* ��¼Nsapi                                */
    }

    /*SAPI*/
    if (g_aucSapi[0][0])
    {
        pModIndMsg->bitOpSapi = 1;
        pModIndMsg->ucSapi  = g_aucSapi[0][1];
        g_aucSapi[0][0] = 0;
    }
    else
    {
        pModIndMsg->bitOpSapi = 0;
    }

    /*Radio Priority*/
    pModIndMsg->bitOpRadioPriority = 1;
    pModIndMsg->ucRadioPriority    = pRcvMsgIe->ucRadioPri;
#if (FEATURE_ON == FEATURE_IPV6)
    pModIndMsg->bitOpSpare       = 0;
#else
    pModIndMsg->bitOpSpare       = 0;
#endif
    if (ucCnxtIndex < SM_MAX_NSAPI_NUM)
    {
        if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pModIndMsg))
        {
            PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "SM_SndTafSmPdpModifyInd:WARNING:Send msg fail!" );
        }

        ucInitType = MODIFY_REQUEST_INIT_TYPE_MT;
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_CONTEXT_MODIFY_REQ,
                        (VOS_VOID *)&ucInitType,
                        NAS_OM_EVENT_PDP_CONTEXT_MODIFY_REQ_LEN);
    }
    else
    {
        PS_FREE_MSG(WUEPS_PID_SM, pModIndMsg);
    }
    return;
}

/*******************************************************************************
  Module:      SM_SndTafSmPdpModifyCnf
  Function:    ���ɺͷ���TAFSM_PDP_MODIFY_CNF��Ϣ
  Input:       SM_NW_MSG_STRU   *pMsgIe         �յ�����Ϣ
               VOS_UINT8            ucCnxtIndex     Context����
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  ��־��      2003.12.10   �¹�����
*******************************************************************************/
VOS_VOID SM_SndTafSmPdpModifyCnf(
                               SM_NW_MSG_STRU   *pMsgIe,                        /* �յ�����Ϣ                               */
                               VOS_UINT8            ucCnxtIndex                     /* Context����                              */
                            )
{
    SMREG_PDP_MODIFY_CNF_STRU          *pModCnfMsg = VOS_NULL_PTR;              /* ����TAF�ṹָ��                          */
    VOS_UINT8                           ucCr;

    pModCnfMsg = (SMREG_PDP_MODIFY_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_MODIFY_CNF_STRU));
    if ( VOS_NULL_PTR == pModCnfMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpModifyCnf:ERROR:Alloc msg fail!" );
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pModCnfMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_MODIFY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pModCnfMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pModCnfMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pModCnfMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_MODIFY_CNF;

    ucCr = g_SmEntity.aPdpCntxtList[ucCnxtIndex].ucCr;
    pModCnfMsg->ucConnectId = ucCr;                                                       /* �趨CR                                   */

    if( 0 == pMsgIe->Qos.ucLen )
    {                                                                           /* NegotiatedQos����Ϊ0                     */
        pModCnfMsg->bitOpNegotiatedQos = 0;                                     /* ��Ϊ������                               */
    }
    else
    {
        pModCnfMsg->bitOpNegotiatedQos = 1;                                     /* ��Ϊ����                                 */

        pModCnfMsg->stNegotiatedQos.ulQosLen = pMsgIe->Qos.ucLen;               /* �洢NegotiatedQos����                    */

        SM_MemCpy(pModCnfMsg->stNegotiatedQos.aucQos,
                  pMsgIe->Qos.pValue,
                  (VOS_UINT32)pMsgIe->Qos.ucLen);                               /* �洢NegotiatedQos����                    */
    }
    if( 0 == pMsgIe->Pfi.ucLen )
    {                                                                           /* PacketFlowId����Ϊ0                      */
        pModCnfMsg->bitOpPacketFlowId = 0;                                      /* ��Ϊ������                               */
    }
    else
    {
        pModCnfMsg->bitOpPacketFlowId = 1;                                      /* ��Ϊ����                                 */

        pModCnfMsg->stPacketFlowId.ulPFILen = pMsgIe->Pfi.ucLen;                /* ��¼PacketFlowId����                     */

        SM_MemCpy(&pModCnfMsg->stPacketFlowId.ucPacketFlowId,
                  pMsgIe->Pfi.pValue,
                  (VOS_UINT32)pMsgIe->Pfi.ucLen);                               /* ��¼PacketFlowId����                     */
    }
    if( 0xFF == ucCnxtIndex )
    {                                                                           /* NsapiֵΪ0xFF                            */
        pModCnfMsg->bitOpNsapi = 0;                                             /* ��Ϊ������                               */
    }
    else
    {
        pModCnfMsg->bitOpNsapi = 1;                                             /* ��Ϊ����                                 */

        pModCnfMsg->ucNsapi = (ucCnxtIndex + SM_NSAPI_OFFSET);                  /* ��¼Nsapi                                */
    }

    /*SAPI*/
    if (g_aucSapi[0][0])
    {
        pModCnfMsg->bitOpSapi = 1;
        pModCnfMsg->ucSapi    = g_aucSapi[0][1];
        g_aucSapi[0][0] = 0;
    }
    else
    {
        pModCnfMsg->bitOpSapi = 0;
    }

    /*Radio Priority*/
    pModCnfMsg->bitOpRadioPriority = 1;
    pModCnfMsg->ucRadioPriority    = pMsgIe->ucRadioPri;
    pModCnfMsg->bitOpSpare         =  0;

    if (ucCnxtIndex < SM_MAX_NSAPI_NUM)
    {
        if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pModCnfMsg))
        {
            PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "SM_SndTafSmPdpModifyCnf:WARNING:Send msg fail!" );
        }
    }
    else
    {
        PS_FREE_MSG(WUEPS_PID_SM, pModCnfMsg);
    }

    return;
}


VOS_VOID SM_SndTafSmPdpModifyRej(
    SM_TAF_CAUSE_ENUM_UINT16   enCause,
    VOS_UINT8                  ucCr                              /* Call Reference                           */
)
{
    SMREG_PDP_MODIFY_REJ_STRU          *pModRejMsg = VOS_NULL_PTR;

    pModRejMsg = (SMREG_PDP_MODIFY_REJ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_MODIFY_REJ_STRU));
    if ( VOS_NULL_PTR == pModRejMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpModifyRej:ERROR:Alloc msg fail!" );
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pModRejMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_MODIFY_REJ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pModRejMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pModRejMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pModRejMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_MODIFY_REJ;

    pModRejMsg->ucConnectId = ucCr;                                             /* �趨CR                                   */

    pModRejMsg->enCause     = enCause;                                          /* �趨SmCause                              */

    if( 0xFF == g_CrMapToNsapi[ucCr] )
    {                                                                           /* NsapiֵΪ0xFF                            */
        pModRejMsg->bitOpNsapi = 0;                                             /* ��Ϊ������                               */
    }
    else
    {
        pModRejMsg->bitOpNsapi = 1;                                             /* ��Ϊ����                                 */

        pModRejMsg->ucNsapi = g_CrMapToNsapi[ucCr]+SM_NSAPI_OFFSET;             /* ��¼Nsapi                                */
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pModRejMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpModifyRej:WARNING:Send msg fail!" );
    }

    return;
}

/*******************************************************************************
  Module:      SM_SndTafSmPdpActSecCnf
  Function:    ���ɺͷ���TAFSM_PDP_ACTIVATE_SEC_CNF��Ϣ
  Input:       SM_NW_MSG_STRU   *pMsgIe         �յ�����Ϣ
               VOS_UINT8            ucCnxtIndex     Context����
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  ��־��      2003.12.10   �¹�����
*******************************************************************************/
VOS_VOID SM_SndTafSmPdpActSecCnf(
    SM_NW_MSG_STRU                     *pMsgIe,                                 /* �յ�����Ϣ                               */
    VOS_UINT8                           ucCnxtIndex                             /* Context����                              */
)
{
    SMREG_PDP_ACTIVATE_SEC_CNF_STRU    *pActSecCnfMsg = VOS_NULL_PTR;           /* ����TAF�ṹָ��                          */
    VOS_UINT8                 ucCr;

    if (ucCnxtIndex >= SM_MAX_NSAPI_NUM)
    {
        return;
    }

    pActSecCnfMsg = (SMREG_PDP_ACTIVATE_SEC_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_ACTIVATE_SEC_CNF_STRU));
    if ( VOS_NULL_PTR == pActSecCnfMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpActSecCnf:ERROR:Alloc msg fail!" );
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pActSecCnfMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_ACTIVATE_SEC_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pActSecCnfMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pActSecCnfMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pActSecCnfMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_ACTIVATE_SEC_CNF;

    ucCr = g_SmEntity.aPdpCntxtList[ucCnxtIndex].ucCr;
    pActSecCnfMsg->ucConnectId = ucCr;                                          /* �趨CR                                   */

    pActSecCnfMsg->stNegotiatedQos.ulQosLen = pMsgIe->Qos.ucLen;                /* �洢NegotiatedQos����                    */

    SM_MemCpy(pActSecCnfMsg->stNegotiatedQos.aucQos,
              pMsgIe->Qos.pValue,
              ( VOS_UINT32 )pMsgIe->Qos.ucLen);                                 /* �洢NegotiatedQos����                    */

    pActSecCnfMsg->bitOpNsapi = 1;                                              /* ��Ϊ����                                 */

    pActSecCnfMsg->ucNsapi = (ucCnxtIndex + SM_NSAPI_OFFSET);                   /* ��¼Nsapi                                */

    if( 0 == pMsgIe->Pfi.ucLen )
    {                                                                           /* PacketFlowId����Ϊ0                      */
        pActSecCnfMsg->bitOpPacketFlowId = 0;                                   /* ��Ϊ������                               */
    }
    else
    {
        pActSecCnfMsg->bitOpPacketFlowId = 1;                                   /* ��Ϊ����                                 */

        pActSecCnfMsg->stPacketFlowId.ulPFILen = pMsgIe->Pfi.ucLen;             /* ��¼PacketFlowId����                     */

        SM_MemCpy(&pActSecCnfMsg->stPacketFlowId.ucPacketFlowId,
                  pMsgIe->Pfi.pValue,
                  (VOS_UINT32)pMsgIe->Pfi.ucLen);                               /* ��¼PacketFlowId����                     */
    }

    /*SAPI*/
    if (g_aucSapi[0][0])
    {
        pActSecCnfMsg->bitOpSapi = 1;
        pActSecCnfMsg->ucSapi    = g_aucSapi[0][1];
        g_aucSapi[0][0] = 0;
    }
    else
    {
        pActSecCnfMsg->bitOpSapi = 0;
    }

    /*Radio Priority*/
    pActSecCnfMsg->bitOpRadioPriority = 1;
    pActSecCnfMsg->ucRadioPriority    = pMsgIe->ucRadioPri;
    pActSecCnfMsg->bitOpSpare         = 0;

    pActSecCnfMsg->stTransId.ucTiFlag = NAS_SM_GetPdpTiFlg(ucCnxtIndex);

    if (SM_TI_NET_ORG != NAS_SM_GetPdpTiFlg(ucCnxtIndex))
    {
        if (0x80 == (NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x80))
        {
            pActSecCnfMsg->stTransId.ucTiValue
                = NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x7F;
        }
        else
        {
            pActSecCnfMsg->stTransId.ucTiValue
                = NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x07;
        }
    }
    else
    {
        pActSecCnfMsg->stTransId.ucTiValue
            = NAS_SM_GetPdpTiValue(ucCnxtIndex) & 0x7F;
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pActSecCnfMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpActSecCnf:WARNING:Send msg fail!" );
    }

    return;
}
VOS_VOID SM_SndTafSmPdpActSecRej(
                               VOS_UINT8                    ucCr,               /* Call Reference                           */
                               SM_TAF_CAUSE_ENUM_UINT16     enCause             /* ����ԭ��                                 */
                            )
{
    SMREG_PDP_ACTIVATE_SEC_REJ_STRU     *pActSecRejMsg = VOS_NULL_PTR;          /* ����TAF�ṹָ��                          */

    pActSecRejMsg = (SMREG_PDP_ACTIVATE_SEC_REJ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_SM,
                                                            sizeof(SMREG_PDP_ACTIVATE_SEC_REJ_STRU));
    if ( VOS_NULL_PTR == pActSecRejMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndTafSmPdpActSecRej:ERROR:Alloc msg fail!" );
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pActSecRejMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SMREG_PDP_ACTIVATE_SEC_REJ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pActSecRejMsg->stMsgHdr.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pActSecRejMsg->stMsgHdr.ulReceiverPid   = WUEPS_PID_TAF;
    pActSecRejMsg->stMsgHdr.ulMsgName       = ID_SMREG_PDP_ACTIVATE_SEC_REJ;

    pActSecRejMsg->ucConnectId = ucCr;                                          /* �趨CR                                   */

    pActSecRejMsg->enCause = enCause;                                           /* ��д����SmCause                          */

    if( 0xFF == g_CrMapToNsapi[ucCr] )
    {                                                                           /* NsapiֵΪ0xFF                            */
        pActSecRejMsg->bitOpNsapi = 0;                                          /* ��Ϊ������                               */
    }
    else
    {
        pActSecRejMsg->bitOpNsapi = 1;                                          /* ��Ϊ����                                 */

        pActSecRejMsg->ucNsapi  = (g_CrMapToNsapi[ucCr] + SM_NSAPI_OFFSET);     /* ��¼Nsapi                                */
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM, pActSecRejMsg))
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_SndTafSmPdpActSecRej:WARNING:Send msg fail!" );
    }

    return;
}
VOS_VOID SM_SndRabmSmActivateInd(
    VOS_UINT8                           ucCntxtIndex,
    VOS_UINT8                           ucActMsgType
)
{
    RABMSM_ACTIVATE_IND_STRU           *pSndMsg = VOS_NULL_PTR;                 /* ������Ϣָ��                             */
    VOS_UINT8                           ucPDPAddrIndex;
    VOS_UINT8                           ucAddrIndex;

    ucAddrIndex = NAS_SM_GetPdpAddrIndex(ucCntxtIndex);

    pSndMsg = (RABMSM_ACTIVATE_IND_STRU *)
        PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_SM,
        sizeof(RABMSM_ACTIVATE_IND_STRU));                                      /* �����ڴ�                                 */
    if ( VOS_NULL_PTR == pSndMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndRabmSmActivateInd:ERROR:Alloc msg fail!" );
        return;
    }

    /* ��ʼ����Ϣ���� */
    PS_MEM_SET((VOS_CHAR *)pSndMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(RABMSM_ACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pSndMsg->ulNsapi = ucCntxtIndex + SM_NSAPI_OFFSET;                          /* ��дNsapi                                */

    /* ��дLinked NSAPI */
    pSndMsg->ulLinkdNsapi = NAS_SM_GetPdpLinkedNsapi(ucAddrIndex);

    ucPDPAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;        /* ����PDP Addr����                         */
    if( 0x00 == (0x0F & (g_SmPdpAddrApn.aPdpAddrlist[ucPDPAddrIndex]
                          .PdpAddrInfo.aucAddrValue[0])) )
    {                                                                           /* PDP type organisationΪ0000              */
        pSndMsg->ulPppFlag = RABM_SM_PPP_PROT;                                  /* ����PPPЭ��                              */
    }
    else
    {
        pSndMsg->ulPppFlag = RABM_SM_IP_PROT;                                   /* ����IPЭ��                               */
    }

    pSndMsg->Qos.ulLength = g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength; /* ��дQos����                              */
    PS_MEM_CPY(pSndMsg->Qos.aucQosValue,
               g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
               g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength);

    if (RABMSM_ACT_MSG_1 == ucActMsgType )
    {
        pSndMsg->ulActMsgType   = RABMSM_ACT_MSG_1;
    }
    else
    {
        pSndMsg->ulActMsgType   = RABMSM_ACT_MSG_2;
    }

    pSndMsg->MsgHeader.ulMsgName   = RABMSM_ACTIVATE_IND;
    pSndMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid = WUEPS_PID_SM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_RABM;


    PS_NAS_LOG1( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n ID_SM_RABM_ACTIVATE_IND: ulNsapi = %ld\r",
            (VOS_INT32)(pSndMsg->ulNsapi));

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM,pSndMsg))                          /* ������Ϣ���ͺ���                         */
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "SM_SndRabmSmActivateInd():WARNING:SEND MSG FIAL");
    }

    return;
}
VOS_VOID SM_SndRabmSmModifyInd(
    VOS_UINT8                           ucCntxtIndex                            /* PDP context������                        */
)
{
    RABMSM_MODIFY_IND_STRU             *pSndMsg = VOS_NULL_PTR;                 /* ������Ϣָ��                             */

    pSndMsg = (RABMSM_MODIFY_IND_STRU *)
                PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_SM,
                sizeof(RABMSM_MODIFY_IND_STRU));                                /* �����ڴ�                                 */
    if ( VOS_NULL_PTR == pSndMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndRabmSmModifyInd:ERROR:Alloc msg fail!" );
        return;
    }

    /* ��ʼ����Ϣ���� */
    PS_MEM_SET((VOS_CHAR *)pSndMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(RABMSM_MODIFY_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pSndMsg->ulNsapi = ucCntxtIndex + SM_NSAPI_OFFSET;                          /* ��дNsapi                                */
    pSndMsg->Qos.ulLength = g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength; /* ��дQos����                              */
    PS_MEM_CPY(pSndMsg->Qos.aucQosValue,
               g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
               g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength);

    pSndMsg->MsgHeader.ulMsgName   = RABMSM_MODIFY_IND;
    pSndMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid = WUEPS_PID_SM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_RABM;

    PS_NAS_LOG1( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "\n SM->RABM: RABMSM_MODIFY_IND: ulNsapi = %ld\r",
            (VOS_INT32)(pSndMsg->ulNsapi));

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM,pSndMsg))                                          /* ������Ϣ���ͺ���                         */
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "SM_SndRabmSmModifyInd():WARNING:SEND MSG FIAL");
    }

    return;
}
VOS_VOID SM_SndRabmSmDeactivateInd(
VOS_UINT8                               ucCnt,                                  /* ȥ����NSAPI�ĸ���                        */
VOS_UINT8                              *pucNsapi                                /* Nsapi���б�                              */
)
{
    RABMSM_DEACTIVATE_IND_STRU         *pSndMsg = VOS_NULL_PTR;                 /* ������Ϣָ��                             */
    VOS_UINT8                           i;                                      /* ѭ������                                 */

    pSndMsg = (RABMSM_DEACTIVATE_IND_STRU *)
                PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_SM,
                sizeof(RABMSM_DEACTIVATE_IND_STRU));                            /* �����ڴ�                                 */
    if ( VOS_NULL_PTR == pSndMsg )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndRabmSmDeactivateInd:ERROR:Alloc msg fail!" );
        return;
    }

    /* ��ʼ����Ϣ���� */
    PS_MEM_SET((VOS_CHAR *)pSndMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(RABMSM_DEACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pSndMsg->ulDeactiveNum = ucCnt;                                             /* ��дȥ����NSAPI�ĸ���                    */
    for( i = 0; i < ucCnt; i++ )
    {                                                                           /* ����ucCnt                                */
        pSndMsg->aulNsapiList[i] = pucNsapi[i] + SM_NSAPI_OFFSET;               /* ��дNsapi                                */
    }

    pSndMsg->MsgHeader.ulMsgName   = RABMSM_DEACTIVATE_IND;
    pSndMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid = WUEPS_PID_SM;
    pSndMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid = WUEPS_PID_RABM;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM,pSndMsg))                                          /* ������Ϣ���ͺ���                         */
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "SM_SndRabmSmDeactivateInd():WARNING:SEND MSG FIAL");
    }

    PS_NAS_LOG(     WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "\n SM->RABM: RABMSM_DEACTIVATE_IND\r");

    return;
}

/*lint -e438 -e830*/

VOS_VOID SM_SndNwStatusMsg(
                       VOS_UINT8                    ucTi,                           /* TI                                       */
                       VOS_UINT8                    ucSmCause                       /* SM cause                                 */
                     )
{
    VOS_UINT8           *pTemp;                                                     /* ����UCHAR����ʱָ��                      */
    VOS_UINT8           *pSendMsg;                                                  /* ����UCHAR��ָ��                          */
    VOS_UINT32           ulSum;                                                      /* ���������                               */
    VOS_UINT8            ucTiBak = ucTi;
    GMMSM_DATA_REQ_STRU    *pDataReq = SM_NULL;

    pTemp = (VOS_UINT8 *)SM_Malloc(SM_MAX_SND_MSG_LEN);                             /* ��������ڴ�                             */
    if ( VOS_NULL_PTR == pTemp )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndNwStatusMsg:ERROR:Alloc mem fail!" );
        return;
    }

    pSendMsg = pTemp;                                                           /* ָ����ʱָ��                             */
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */

    if(SM_FALSE == g_ucTiExt )
    {
        ucTi = ((ucTi & 0x80) >> 4) | (ucTi & 0x07);
    }
    if((TAF_SM_REJ_CAUSE_MSGTYPE_NOT_EXIT != ucSmCause)
        && (TAF_SM_REJ_CAUSE_PROTOCOL_ERR != ucSmCause ))
    {
        if( 0xFF != g_TiMapToNsapi[ucTiBak] )
        {                                                                       /* ʵ�����                                 */
            SM_ComGetTI(g_TiMapToNsapi[ucTiBak], &pTemp, &ulSum);                  /* ���ú����洢TI��TI Flag                  */
        }
        else
        {                                                                       /* ʵ�岻����                               */
            if( SM_FALSE == g_ucTiExt )
            {                                                                   /* TIռ��1/2�ֽ�                            */
                /*Ϊ�˰�NET->MS����� TI_FLAG ת����MS->NET����� TI_FLAG,
                ��BIT8�������1*/
                if (TAF_SM_REJ_CAUSE_INVALID_TI == ucSmCause)
                {
                    ucTi = ucTi ^ 0x08;
                }

                *pTemp = (ucTi << 4) & 0xF0;                                    /* ���TI                                   */
                *pTemp = *pTemp | NAS_PD_SM;                                    /* �趨PD                                   */
                pTemp++;                                                        /* ����ָ��ƫ�Ƶĳ���                       */
                ulSum += 1;                                                     /* ��������1                                */
            }
            else
            {                                                                   /* TIռ��3/2�ֽ�                            */
                /*Ϊ�˰�NET->MS����� TI_FLAG ת����MS->NET����� TI_FLAG,
                ��BIT8�������1*/
                if (TAF_SM_REJ_CAUSE_INVALID_TI == ucSmCause)
                {
                    ucTi = ucTi ^ 0x80;
                }

                *pTemp = 0x70;                                                  /* ����Ti��չλ                             */
                *pTemp = (VOS_UINT8)(*pTemp | (ucTi & 0x80));                       /* Ti Flag��1                               */
                *pTemp = *pTemp | NAS_PD_SM;                                    /* �趨PD                                   */
                pTemp++;                                                        /* ����ָ��ƫ�Ƶĳ���                       */
                *pTemp = ucTi|0x80;                                             /* ���TI                                   */
                pTemp++;                                                        /* ����ָ��ƫ�Ƶĳ���                       */
                ulSum += 2;                                                     /* ��������2                                */
            }
        }
    }
    else
    {                                                                           /* ʵ�岻����                               */
        if( SM_FALSE == g_ucTiExt )
        {                                                                       /* TIռ��1/2�ֽ�                            */
            /*Ϊ�˰�NET->MS����� TI_FLAG ת����MS->NET����� TI_FLAG,
            ��BIT8�������1*/
            ucTi = ucTi ^ 0x08;

            *pTemp = (ucTi << 4) & 0xF0;                                        /* ���TI,Ti Flag��1                        */
            *pTemp = (*pTemp) | NAS_PD_SM;                                      /* �趨PD                                   */
            pTemp++;                                                            /* ����ָ��ƫ�Ƶĳ���                       */
            ulSum += 1;                                                         /* ��������1                                */
        }
        else
        {                                                                       /* TIռ��3/2�ֽ�                            */
            /*Ϊ�˰�NET->MS����� TI_FLAG ת����MS->NET����� TI_FLAG,
            ��BIT8�������1*/
            ucTi = ucTi ^ 0x80;

            *pTemp = 0x70;                                                      /* ����Ti��չλ                             */
            *pTemp = *pTemp | (ucTi & 0x80);                                    /* Ti Flag��1                               */
            *pTemp = (*pTemp) | NAS_PD_SM;                                      /* �趨PD                                   */
            pTemp++;                                                            /* ����ָ��ƫ�Ƶĳ���                       */
            *pTemp = ucTi | 0x80;                                               /* ���TI                                   */
            pTemp++;                                                            /* ����ָ��ƫ�Ƶĳ���                       */
            ulSum += 2;                                                         /* ��������2                                */
        }
    }
    *pTemp = SM_STATUS;                                                         /* �����Ϣ���ͣ�����ָ��ƫ�Ƶĳ���         */
    pTemp++;                                                                    /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += 1;                                                                 /* ��������1                                */
    *pTemp = ucSmCause;                                                         /* Sm Cause                                 */
    pTemp++;                                                                    /* ����ָ��ƫ�Ƶĳ���                       */
    ulSum += 1;                                                                 /* ��������1                                */

    pDataReq = (GMMSM_DATA_REQ_STRU *)
                PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_SM,
                sizeof(GMMSM_DATA_REQ_STRU));
    if ( VOS_NULL_PTR == pDataReq )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_SndNwStatusMsg:ERROR:Alloc msg fail!" );
        SM_Free(pSendMsg);
        return;
    }

    pDataReq->MsgHeader.ulMsgName   = GMMSM_DATA_REQ;
    pDataReq->ulEstCause = GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL;

    pDataReq->SmMsg.ulNasMsgSize = ulSum;
    SM_MemCpy(pDataReq->SmMsg.aucNasMsg, pSendMsg, ulSum);
    pDataReq->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pDataReq->MsgHeader.ulSenderPid = WUEPS_PID_SM;
    pDataReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pDataReq->MsgHeader.ulReceiverPid = WUEPS_PID_GMM;

    SM_ReportM2NOtaMsg(&(pDataReq->SmMsg));


    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM,pDataReq))                          /* ������Ϣ���ͺ���                         */
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "SM_SndNwStatusMsg():WARNING:SEND MSG FIAL");
    }

    PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
            "SM->NW: SM Status\r");

    SM_Free(pSendMsg);                                                          /* �ͷ��ڴ�                                 */
    return;
}
/*lint +e438 +e830*/


VOS_UINT8 SM_GetMostHighPri(VOS_VOID)
{
    VOS_UINT8   i;
    VOS_UINT8   ucPriority;
    VOS_UINT8   ucTempPri;

    ucPriority = GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL;                            /* ��ʼ�����ȼ�                             */
    for(i = 0; i < SM_MAX_NSAPI_NUM; i++)
    {
        if (SM_PDP_INACTIVE != g_SmEntity.aPdpCntxtList[i].ucState)
        {
            ucTempPri = (g_SmEntity.aPdpCntxtList[i].QoS.aucQosValue[3] & NAS_SM_QOS_TRAFFIC_CLASS_MASK) >> 5;
            if(0 != ucTempPri)
            {                                                                   /* ���Ǳ�������Subscribed Traffic Class     */
                if(ucPriority > ucTempPri)
                {                                                               /* ���ȼ����ڳ�ʼ�����ȼ�                   */
                    ucPriority = ucTempPri;
                }
            }
        }
    }

#if(PS_UE_REL_VER >= PS_PTL_VER_R6)
    if (NAS_Common_Get_Supported_3GPP_Version(SM_MM_COM_SRVDOMAIN_PS) >= PS_PTL_VER_R6)
    {
        if (GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL == ucPriority)
        {
            ucPriority = GMM_SM_RRC_EST_CAUSE_ORG_ST_CALL;
        }
    }
#endif

    return ucPriority;
}
VOS_UINT32   SM_GetCr(VOS_UINT8 ucNsapi, VOS_UINT8 *pucCr)
{
    if(VOS_NULL_PTR == pucCr)
    {
        return VOS_ERR;
    }

    if((SM_NSAPI_MIN_VALUE > ucNsapi) || (SM_NSAPI_MAX_VALUE < ucNsapi))
    {
        return VOS_ERR;
    }

    if(SM_PDP_ACTIVE != g_SmEntity.aPdpCntxtList[ucNsapi - SM_NSAPI_OFFSET].ucState)
    {
        return VOS_ERR;
    }

    *pucCr = g_SmEntity.aPdpCntxtList[ucNsapi - SM_NSAPI_OFFSET].ucCr;
    return VOS_OK;
}



VOS_VOID SM_FillMsgData(VOS_VOID *pMsgContent,VOS_VOID *pData,VOS_UINT32 ulLen)
{
    SM_MemCpy(pMsgContent, pData, ulLen);
}



VOS_UINT32   SM_IsActivePending(VOS_UINT8 ucNsapi)
{
    if((SM_NSAPI_MIN_VALUE > ucNsapi) || (SM_NSAPI_MAX_VALUE < ucNsapi))
    {
        return VOS_ERR;
    }

    if(SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[ucNsapi - SM_NSAPI_OFFSET].ucState)
    {
        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}



VOS_UINT32   SM_RabmGetFirstActIndMsgInfo(
    VOS_UINT8                           ucNsapi,
    RABMSM_ACTIVATE_IND_STRU           *pActivateInd
)
{
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucPDPAddrIndex;

    if (VOS_NULL_PTR == pActivateInd)
    {
        return VOS_ERR;
    }

    if ((SM_NSAPI_MIN_VALUE > ucNsapi) || (SM_NSAPI_MAX_VALUE < ucNsapi))
    {
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ���� */
    PS_MEM_SET((VOS_CHAR *)pActivateInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(RABMSM_ACTIVATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    ucCntxtIndex = ucNsapi - SM_NSAPI_OFFSET;

    ucPDPAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;
    if (0x00 == (0x0F & (g_SmPdpAddrApn.aPdpAddrlist[ucPDPAddrIndex].PdpAddrInfo.aucAddrValue[0])))
    {
        pActivateInd->ulPppFlag = RABM_SM_PPP_PROT;
    }
    else
    {
        pActivateInd->ulPppFlag = RABM_SM_IP_PROT;
    }

    pActivateInd->Qos.ulLength = g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength;

    PS_MEM_CPY(pActivateInd->Qos.aucQosValue,
               g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
               g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength);

    return VOS_OK;
}
VOS_UINT32 NAS_SM_IsPdpCntxtValid(NAS_SM_PDP_CONTEXT_INFO_STRU *pstPdpCntxt)
{
    if (VOS_NULL_PTR == pstPdpCntxt)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


VOS_VOID SM_SndTafMsg(
                  VOS_UINT8             *pSendMsg,                                  /* ��Ϣ���ݵ���ʱָ��                       */
                  VOS_UINT8             ucSMIndex,                                  /* SM����                                   */
                  VOS_UINT32             ulSum,                                      /* ��Ϣ�ĳ���                               */
                  VOS_UINT8             ucCause,                                    /* rrc���ӽ���ԭ��                          */
                  VOS_UINT8             ucSaveFlg
                  )
{
    GMMSM_DATA_REQ_STRU    *pDataReq = SM_NULL;                                 /* ��Ϣָ��                                 */

    VOS_UINT32                   Messagelen;
    if(ulSum > 4)
    {
        pDataReq = (GMMSM_DATA_REQ_STRU *)
            PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_SM,
            (sizeof(GMMSM_DATA_REQ_STRU) + ulSum) - 4);
        if (VOS_NULL_PTR == pDataReq)
        {
            PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "\n SM_SndTafMsg : Sm_AllocMsg FAIL 1 !!\r");
            return;
        }

        Messagelen= (sizeof(GMMSM_DATA_REQ_STRU) + ulSum) - 4;
    }
    else
    {
        pDataReq = (GMMSM_DATA_REQ_STRU *)
            PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_SM,
            sizeof(GMMSM_DATA_REQ_STRU));
        if (VOS_NULL_PTR == pDataReq)
        {
            PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "\n SM_SndTafMsg : Sm_AllocMsg FAIL 2 !!\r");
            return;
        }

        Messagelen = sizeof(GMMSM_DATA_REQ_STRU);
    }

    pDataReq->MsgHeader.ulMsgName   = GMMSM_DATA_REQ;
    pDataReq->SmMsg.ulNasMsgSize    = ulSum;
    pDataReq->ulEstCause = ucCause;

    SM_FillMsgData(pDataReq->SmMsg.aucNasMsg, pSendMsg, ulSum);

    SM_Free(pSendMsg);

    pDataReq->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pDataReq->MsgHeader.ulSenderPid = WUEPS_PID_SM;
    pDataReq->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pDataReq->MsgHeader.ulReceiverPid = WUEPS_PID_GMM;


    if(SM_TRUE == ucSaveFlg)
    {
        g_SmEntity.aPdpCntxtList[ucSMIndex].pHoldSndMsg =(VOS_VOID *)
            SM_Malloc(Messagelen);
        SM_MemCpy(g_SmEntity.aPdpCntxtList[ucSMIndex].pHoldSndMsg,pDataReq,
            Messagelen);                                     /* ���ݷ��͵���Ϣ                           */
        g_SmEntity.aPdpCntxtList[ucSMIndex].ulHoldLen =
            Messagelen;                                      /* ���ݷ��͵���Ϣ����                       */

    }
    SM_ReportM2NOtaMsg(&(pDataReq->SmMsg));


    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SM,pDataReq))                          /* ������Ϣ���ͺ���                         */
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "SM_SndTafMsg():WARNING:SEND MSG FIAL");
    }

    return;
}
VOS_VOID SM_SndStatusMsg( VOS_UINT8 ucTi, VOS_UINT8  ucSmCause )
{
    NAS_SM_BeginSession();

    SM_SndNwStatusMsg(ucTi, ucSmCause);

    NAS_SM_EndSession();

    return;
}


VOS_VOID NAS_SM_SndGmmEstablishReq(VOS_VOID)
{
    GMMSM_ESTABLISH_REQ_STRU           *pstMsg = VOS_NULL_PTR;

    /* ����OSA��Ϣ */
    pstMsg = (GMMSM_ESTABLISH_REQ_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(
                                            sizeof(GMMSM_ESTABLISH_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndGmmEstablishReq: Alloc MSG failed.");
        return;
    }

    /* �����Ϣ���� */
    PS_MEM_SET(NAS_SM_GET_MSG_ENTITY(pstMsg), 0x00, NAS_SM_GET_MSG_LENGTH(pstMsg));

    /* ��д��Ϣͷ */
    NAS_SM_CFG_GMM_MSG_HDR(pstMsg, GMMSM_ESTABLISH_REQ);

    /* ������Ϣ */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}


VOS_VOID NAS_SM_SndGmmPdpDeactivatedInd(VOS_VOID)
{
    GMMSM_PDP_DEACTIVATED_IND_STRU     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    /* ����OSA��Ϣ */
    pstMsg = (GMMSM_PDP_DEACTIVATED_IND_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(
                                                    sizeof(GMMSM_PDP_DEACTIVATED_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndGmmPdpDeactivatedInd: Alloc MSG failed.");
        return;
    }

    /* �����Ϣ���� */
    PS_MEM_SET(NAS_SM_GET_MSG_ENTITY(pstMsg), 0x00, NAS_SM_GET_MSG_LENGTH(pstMsg));

    /* ��д��Ϣͷ */
    NAS_SM_CFG_GMM_MSG_HDR(pstMsg, GMMSM_PDP_DEACTIVATED_IND);

    /* ��д��Ϣ���� */
    for (ulIndex = 0; ulIndex < SM_MAX_NSAPI_NUM; ulIndex++)
    {
        if ((SM_PDP_ACTIVE == g_SmEntity.aPdpCntxtList[ulIndex].ucState)
         || (SM_PDP_MODIFY_PENDING == g_SmEntity.aPdpCntxtList[ulIndex].ucState)
         || (SM_PDP_NW_MODIFY == g_SmEntity.aPdpCntxtList[ulIndex].ucState))
        {
            pstMsg->ulPdpContextStatus
                |= (VOS_UINT32)0x00000001 << (ulIndex + SM_NSAPI_OFFSET);
        }
    }

    /* ������Ϣ */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}
VOS_VOID NAS_SM_SndGmmAbortReq(VOS_VOID)
{
    GMMSM_ABORT_REQ_STRU               *pstMsg = VOS_NULL_PTR;

    /* ����OSA��Ϣ */
    pstMsg = (GMMSM_ABORT_REQ_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(
                                        sizeof(GMMSM_ABORT_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndGmmAbortReq: Alloc MSG failed.");
        return;
    }

    /* �����Ϣ���� */
    PS_MEM_SET(NAS_SM_GET_MSG_ENTITY(pstMsg), 0x00, NAS_SM_GET_MSG_LENGTH(pstMsg));

    /* ��д��Ϣͷ */
    NAS_SM_CFG_GMM_MSG_HDR(pstMsg, GMMSM_ABORT_REQ);

    /* ������Ϣ */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}


VOS_VOID NAS_SM_SndGmmPdpModifyInd(VOS_UINT8 ucNsapi)
{
    GMMSM_PDP_MODIFY_IND_STRU              *pstMsg = VOS_NULL_PTR;

    /* ����OSA��Ϣ */
    pstMsg = (GMMSM_PDP_MODIFY_IND_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(
                                            sizeof(GMMSM_PDP_MODIFY_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndGmmPdpModifyInd: Alloc MSG failed.");
        return;
    }

    /* �����Ϣ���� */
    PS_MEM_SET(NAS_SM_GET_MSG_ENTITY(pstMsg), 0x00, NAS_SM_GET_MSG_LENGTH(pstMsg));

    /* ��д��Ϣͷ */
    NAS_SM_CFG_GMM_MSG_HDR(pstMsg, GMMSM_PDP_MODIFY_IND);

    /* ��д��Ϣ���� */
    pstMsg->ucNsapi = ucNsapi;

    /* ������Ϣ */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}



VOS_VOID NAS_SM_SndGmmPdpStatusInd(VOS_VOID)
{
    GMMSM_PDP_STATUS_IND_STRU          *pstMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucState;
    VOS_UINT8                           i;

    /* ����OSA��Ϣ */
    pstMsg = (GMMSM_PDP_STATUS_IND_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(
                                            sizeof(GMMSM_PDP_STATUS_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndGmmPdpStatusInd: Alloc MSG failed.");
        return;
    }

    /* �����Ϣ���� */
    PS_MEM_SET(NAS_SM_GET_MSG_ENTITY(pstMsg), 0x00, NAS_SM_GET_MSG_LENGTH(pstMsg));

    /* ��д��Ϣͷ */
    NAS_SM_CFG_GMM_MSG_HDR(pstMsg, GMMSM_PDP_STATUS_IND);

    /* ��д��Ϣ���� */
    for ( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
    {
        ucState = NAS_SM_GET_PDP_STATE(i);

        if ( (SM_PDP_MODIFY_PENDING == ucState)
          || (SM_PDP_ACTIVE == ucState)
          || (SM_PDP_NW_MODIFY == ucState) )
        {
            pstMsg->aucPdpContextStatus[i] = GMMSM_PDP_STATE_ACTIVE;
        }
        else if (SM_PDP_ACTIVE_PENDING == ucState)
        {
            pstMsg->aucPdpContextStatus[i] = GMMSM_PDP_STATE_ACTIVE_PENDING;
        }
        else if (SM_PDP_INACTIVE_PENDING == ucState)
        {
            pstMsg->aucPdpContextStatus[i] = GMMSM_PDP_STATE_INACTIVE_PENDING;
        }
        else
        {
            pstMsg->aucPdpContextStatus[i] = GMMSM_PDP_STATE_INACTIVE;
        }
    }

    /* ������Ϣ */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}


VOS_VOID NAS_SM_SndPdpCntxtHoldMsg(NAS_SM_PDP_CONTEXT_INFO_STRU *pstPdpCntxt)
{
    MSG_HEADER_STRU                    *pstMsg = VOS_NULL_PTR;

    /* ��������� */
    if (PS_FALSE == NAS_SM_IsPdpCntxtValid(pstPdpCntxt))
    {
        NAS_SM_WARN_LOG("NAS_SM_SndPdpCntxtHoldMsg: PDP context is not valid.");
        return;
    }

    /* ����OSA��Ϣ */
    pstMsg = (MSG_HEADER_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(pstPdpCntxt->ulHoldLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndPdpCntxtHoldMsg: Alloc MSG failed.");
        return;
    }

    /* ������Ϣ */
    PS_MEM_CPY(pstMsg, pstPdpCntxt->pHoldSndMsg, pstPdpCntxt->ulHoldLen);

    /* ������Ϣ */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}


VOS_VOID NAS_SM_SndGmmBeginSessionNotify(GMMSM_SESSION_TYPE_ENUM_UINT8 enSessionType)
{
    GMMSM_BEGIN_SESSION_NOTIFY_STRU    *pstMsg = VOS_NULL_PTR;

    /* ����OSA��Ϣ */
    pstMsg = (GMMSM_BEGIN_SESSION_NOTIFY_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(
                                                    sizeof(GMMSM_BEGIN_SESSION_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndGmmBeginSessionNotify: Alloc MSG failed.");
        return;
    }

    /* �����Ϣ���� */
    PS_MEM_SET(NAS_SM_GET_MSG_ENTITY(pstMsg), 0x00, NAS_SM_GET_MSG_LENGTH(pstMsg));

    /* ��д��Ϣͷ */
    NAS_SM_CFG_GMM_MSG_HDR(pstMsg, GMMSM_BEGIN_SESSION_NOTIFY);

    /* ��д��Ϣ���� */
    pstMsg->enSessionType = enSessionType;

    /* ������Ϣ */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}
VOS_VOID NAS_SM_SndGmmEndSessionNotify(GMMSM_SESSION_TYPE_ENUM_UINT8 enSessionType)
{
    GMMSM_END_SESSION_NOTIFY_STRU      *pstMsg = VOS_NULL_PTR;

    /* ����OSA��Ϣ */
    pstMsg = (GMMSM_END_SESSION_NOTIFY_STRU *)NAS_SM_ALLOC_MSG_WITH_HDR(
                                                    sizeof(GMMSM_END_SESSION_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_SM_ERR_LOG("NAS_SM_SndGmmEndSessionNotify: Alloc MSG failed.");
        return;
    }

    /* �����Ϣ���� */
    PS_MEM_SET(NAS_SM_GET_MSG_ENTITY(pstMsg), 0x00, NAS_SM_GET_MSG_LENGTH(pstMsg));

    /* ��д��Ϣͷ */
    NAS_SM_CFG_GMM_MSG_HDR(pstMsg, GMMSM_END_SESSION_NOTIFY);

    /* ��д��Ϣ���� */
    pstMsg->enSessionType = enSessionType;

    /* ������Ϣ */
    NAS_SM_SEND_MSG(pstMsg);
    return;
}



/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

