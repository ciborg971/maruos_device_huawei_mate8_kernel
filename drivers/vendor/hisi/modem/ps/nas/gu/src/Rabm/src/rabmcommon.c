
#include "rabminclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_RABM_COMMON_C



/*******************************************************************************
  Module:   RABM_SaveData
  Function: ��������
  Input:    RABM_DATA_SAVE_STRU    *pSaveDataPtr     �������ݵ�����ָ��
            VOS_VOID                   *pMsg             �����������
            VOS_UINT8                  ucMsgType         ��Ϣ����
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1. ��־��      2003.12.11   �¹�����
*******************************************************************************/
VOS_VOID RABM_SaveData(
                   RABM_DATA_SAVE_STRU  *pSaveDataPtr,                          /* �������ݵ�����ָ��                       */
                   VOS_VOID  *pMsg,                                                 /* �����������                             */
                   VOS_UINT8 ucMsgType                                              /* ��Ϣ����                                 */
                   )
{
    RABM_DATA_LINK_STRU  *pTemp1 = RABM_POINTER_NULL;
    RABM_DATA_LINK_STRU  *pTemp2 = RABM_POINTER_NULL;

    VOS_VOID           *pSaveMsg = RABM_POINTER_NULL;
    VOS_UINT32         ulDataLen = 0;

    if ( RABM_UPLINK == ucMsgType )
    {                                                                           /* ����������ݵĳ���                       */
        ulDataLen = ((TAFRABM_PS_DATA_REQ_STRU *)pMsg)->MsgHeader.ulLength + VOS_MSG_HEAD_LENGTH;
    }
    else
    {                                                                           /* ����������ݵĳ���                       */
        ulDataLen = sizeof(PDCP_RABM_DATA_BUF_STRU);
    }

    pSaveMsg = RABM_Malloc(ulDataLen);
    if(VOS_NULL_PTR == pSaveMsg)
    {
        return;
    }

    PS_NAS_MEM_CPY(pSaveMsg, pMsg, ulDataLen);                                     /* �������                                 */


    if(0 == pSaveDataPtr->ucNum)
    {                                                                           /* �������еĵ�һ������                     */
        pSaveDataPtr->Data.pData = pSaveMsg;                                    /* �洢������Ϣ                             */
        pSaveDataPtr->Data.pNxt = RABM_POINTER_NULL;                            /* ��ʼ������ָ��                           */
    }
    else if(1 == pSaveDataPtr->ucNum)
    {
        pSaveDataPtr->Data.pNxt = (RABM_DATA_LINK_STRU *)
                                       RABM_Malloc(sizeof(RABM_DATA_LINK_STRU));
        pSaveDataPtr->Data.pNxt->pData = pSaveMsg;                              /* �洢������Ϣ                             */
        pSaveDataPtr->Data.pNxt->pNxt = RABM_POINTER_NULL;
    }
    else
    {
        pTemp1 = pSaveDataPtr->Data.pNxt;
        pTemp2 = pTemp1;

        if(0xff != pSaveDataPtr->ucNum)
        {
            for( ; ; )
            {                                                                   /* ��������β                               */
                if(RABM_POINTER_NULL != pTemp1->pNxt)
                {
                    pTemp1 = pTemp2->pNxt;
                }
                else
                {
                    break;
                }
                pTemp2 = pTemp1;
            }
            pTemp1->pNxt = (RABM_DATA_LINK_STRU *)
                RABM_Malloc(sizeof(RABM_DATA_LINK_STRU));
            pTemp1->pNxt->pData = pSaveMsg;                                     /* �洢������Ϣ                             */
            pTemp1->pNxt->pNxt = RABM_POINTER_NULL;                             /* ��ʼ������ָ��                           */
        }
        else
        {
            /*�ͷ��������ݵ��㿽���ڴ�*/
            if (RABM_UPLINK == ucMsgType)
            {
                TTF_MemFree(WUEPS_PID_RABM, ((TAFRABM_PS_DATA_REQ_STRU *)pMsg)->pData);
            }

            RABM_Free(pSaveMsg);
            return;
        }
    }
    pSaveDataPtr->ucNum++;                                                      /* ���»�������ݸ���                       */
}
VOS_VOID RABM_ComSaveRabPara(
                         RRRABM_RAB_IND_STRU  *pMsg                             /* Ŀǰ�������Ϣ                           */
                         )
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    VOS_UINT8                           ucEntId = 0xff;
    VOS_UINT8                           ucTcFlg = RABM_FALSE;
    VOS_UINT16                          k;
    VOS_UINT8                           ucChgMask;

    for(i = 0; i < pMsg->ulRabCnt; i++)
    {
        if(RABM_CN_PS == pMsg->aRabInfo[i].ulCnDomainId)
        {                                                                       /* ��PS���RAB                              */
            if ( VOS_TRUE == gRabm2GTo3GDataResume )
            {
                /*��λ2G��3G�л�ʹ�õ������ָ���־:*/
                gRabm2GTo3GDataResume = VOS_FALSE;

                /*��PDCP����2G��3G�л��������ָ�ָʾ:*/
                NAS_RabmSndPdcpDataResumeInd(pMsg);
            }

            if ( (RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
              && ((pMsg->aRabInfo[i].ulRabId & 0x0f) < RABM_NSAPI_OFFSET) )
            {
                ucEntId = (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId & 0x0f);
            }
            else
            {
                if ((pMsg->aRabInfo[i].ulRabId & 0x0f) < RABM_NSAPI_OFFSET)
                {
                   continue;
                }

                ucEntId = (VOS_UINT8)
                ((pMsg->aRabInfo[i].ulRabId & 0x0f) - RABM_NSAPI_OFFSET);       /* ���PS���RABMʵ��ID                     */
            }

            switch(g_aRabmPsEnt[ucEntId].ucState)
            {                                                                   /* ����ʵ��״̬����Ӧ����                   */
            case RABM_NULL:
                break;
            case RABM_NSAPI_ACTIVE_PENDING:
                if(RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
                {
                    Rabm_TcInfSave(pMsg, i);
                }
                RABM_SetWState(ucEntId, RABM_ACT_PENDING_WITH_RAB);             /* �ı�ʵ���״̬                           */
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_ComSaveRabPara:NORMAL:RABM state: RABM_NSAPI_ACTIVE_PENDING ==> RABM_ACT_PENDING_WITH_RAB");
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);                         /* ����RAB ID                               */
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);                         /* ����RB�ĸ���                             */

                for ( j = 0 ; j < g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum ; j++ )
                {
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);                  /* ����RB ID                                */

                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbTxMode[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aenUlRlcMode[j]);             /* ����RB �Ĵ���ģʽ */
                }

                /*��ʱRAB_MAP���ʵ�岢δ�������������RAB_MAP�е�ucAsId*/
                break;
            case RABM_NSAPI_ACTIVE_NO_RAB:
                if(RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
                {
                    Rabm_TcInfSave(pMsg, i);
                }
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);                         /* ����RAB ID                               */
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);                         /* ����RB�ĸ���                             */

                for ( j = 0 ; j < g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum ; j++ )
                {
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);                  /* ����RB ID                                */
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbTxMode[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aenUlRlcMode[j]);             /* ����RB �Ĵ���ģʽ */
                }


                RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_WITH_RAB);            /* �ı�ʵ���״̬                           */
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_ComSaveRabPara:NORMAL:RABM state: RABM_NSAPI_ACTIVE_NO_RAB ==> RABM_NSAPI_ACTIVE_WITH_RAB");

                /*����RAB_MAP���е�ucAsId*/
                ucChgMask = 0;
                ucChgMask |= RAB_MAP_CHG_MASK_AS_ID;
                RABM_ChgRabMap(ucEntId + RABM_NSAPI_OFFSET,
                               ucChgMask,
                               g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[0],
                               VOS_NULL_PTR,
                               VOS_NULL_PTR);

                if (VOS_TRUE == NAS_RABM_GetWPsEntRabReestFlg(ucEntId))
                {
                    /* ֹͣRB����������ʱ�� */
                    NAS_RABM_StopReestRabPendingTmr(ucEntId + RABM_NSAPI_OFFSET);

                    /* ���RABMʵ����ؽ���ʶ */
                    NAS_RABM_ClearWPsEntRabReestFlg(ucEntId);

                    g_aRabmPsEnt[ucEntId].ucStpFlg = RABM_FALSE;
                    RABM_SaveDataProcess(ucEntId, RABM_UPLINK);                 /* ���������������                       */

                    /* ֪ͨCDS���ͻ������� */
                    NAS_RABM_SndCdsSendBuffDataInd(ucEntId + RABM_NSAPI_OFFSET,
                                                   CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC);
                }
                break;
            case RABM_ACT_PENDING_WITH_RAB:
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);                         /* ����RAB ID                               */
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);                         /* ����RB�ĸ���                             */

                for ( j = 0 ; j < g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum ; j++ )
                {
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[j] =
                            (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);              /* ����RB ID                                */
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbTxMode[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aenUlRlcMode[j]);             /* ����RB �Ĵ���ģʽ */
                }

                /*��ʱRAB_MAP���ʵ�岢δ�������������RAB_MAP�е�ucAsId*/
                break;
            case RABM_NSAPI_ACTIVE_WITH_RAB:
            case RABM_DATA_TRANSFER_STOP:
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);                         /* ����RAB ID                               */
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);                         /* ����RB�ĸ���                             */

                for ( j = 0 ; j < g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum ; j++ )
                {
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[j] =
                            (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);              /* ����RB ID                                */
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbTxMode[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aenUlRlcMode[j]);             /* ����RB �Ĵ���ģʽ */
                }

                /*����RAB_MAP���е�ucAsId*/
                ucChgMask = 0;
                ucChgMask |= RAB_MAP_CHG_MASK_AS_ID;
                RABM_ChgRabMap(ucEntId + RABM_NSAPI_OFFSET,
                               ucChgMask,
                               g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[0],
                               VOS_NULL_PTR,
                               VOS_NULL_PTR);
                break;
            case RABM_TC_STATE_NULL:
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);                         /* ����RAB ID                               */
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);                         /* ����RB�ĸ���                             */

                for ( j = 0 ; j < pMsg->aRabInfo[i].ulRbNum ; j++ )
                {
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);              /* ����RB ID                                */
                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbTxMode[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aenUlRlcMode[j]);             /* ����RB �Ĵ���ģʽ */
                }
                Rabm_TcInfSave(pMsg, i);
                break;
            default:
                break;
            }

            if(RABM_NSAPI_ACTIVE_WITH_RAB == g_aRabmPsEnt[ucEntId].ucState)
            {
                if(0 != g_aRabmPsEnt[ucEntId].DlDataSave.ucNum)
                {                                                               /* �л������������                         */
                    RABM_SaveDataProcess(ucEntId,RABM_DOWNLINK);                /* ���������������                       */
                }
            }
        }
        else
        {
            if( NAS_RRC_RAB_SETUP_SUCCESS == pMsg->ulRabChangeType )
            {

                ucTcFlg = RABM_FALSE;
                for( j = 0; j < RABM_CS_MAX_ENT_NUM; j++ )
                {
                    for( k = 0; k < 256; k++ )
                    {
                        if ( g_aucSiMapEnt[k] == j )
                        {
                            break;
                        }
                    }

                    if( k < 256 )
                    {
                        continue;
                    }
                    if( RABM_NULL == g_aRabmCsEnt[j].ucState)
                    {
                        g_aucSiMapEnt[pMsg->aRabInfo[i].ulRabId] = j;
                        break;
                    }
                    else if(RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
                    {
                        Rabm_TcInfSave(pMsg, i);
                        ucTcFlg = RABM_TRUE;
                        break;
                    }
                    else
                    {
                    }
                }
                if(RABM_TRUE == ucTcFlg)
                {
                    g_aucSiMapEnt[pMsg->aRabInfo[i].ulRabId] = j;
                    ucEntId = g_aucSiMapEnt[pMsg->aRabInfo[i].ulRabId];
                    g_aRabmCsEnt[ucEntId].RabInfo.ucRabId = (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);
                    g_aRabmCsEnt[ucEntId].RabInfo.ucRbNum = (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);
                    for(j = 0; j < pMsg->aRabInfo[i].ulRbNum; j++)
                    {
                        g_aRabmCsEnt[ucEntId].RabInfo.aucRbId[j] = (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);
                        g_aRabmCsEnt[ucEntId].RabInfo.aucRbTxMode[j] = (VOS_UINT8)(pMsg->aRabInfo[i].aenUlRlcMode[j]);
                    }
                    continue;
                }
                if( RABM_CS_MAX_ENT_NUM == j )
                {
                    PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "RABM_ComSaveRabPara:WARNING:Exceed RABM_CS_MAX_ENT_NUM!");
                    return;
                }
            }
            ucEntId = g_aucSiMapEnt[pMsg->aRabInfo[i].ulRabId];

            for(j = 0; j < pMsg->aRabInfo[i].ulRbNum; j++)
            {
                g_aRabmCsEnt[ucEntId].RabInfo.aucRbTxMode[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aenUlRlcMode[j]);
            }
            switch(g_aRabmCsEnt[ucEntId].ucState)
            {
            case RABM_NULL:
                g_aRabmCsEnt[ucEntId].ucState = RABM_SI_ACTIVE_WITH_RAB;
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_ComSaveRabPara:NORMAL:RABM state: RABM_NULL ==> RABM_SI_ACTIVE_WITH_RAB");
                g_aRabmCsEnt[ucEntId].ucSi = (VOS_UINT8)pMsg->aRabInfo[i].ulRabId;  /* �洢SI                                   */

                RABM_SndCcSyncInd(RABMCC_RAB_ACTIVE, pMsg->aRabInfo[i].ulRabId);/* ֪ͨcc                                   */

                RABM_SndCallSyncInd(RABMCALL_RAB_ACTIVE, &pMsg->aRabInfo[i]);   /* ֪ͨCALL */
                g_aRabmCsEnt[ucEntId].RabInfo.ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);                         /* ����RAB ID                               */
                g_aRabmCsEnt[ucEntId].RabInfo.ucRbNum =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);                         /* ����RB�ĸ���                             */
                for(j = 0; j < g_aRabmCsEnt[ucEntId].RabInfo.ucRbNum; j++)
                {                                                               /* ����RB ID                                */
                    g_aRabmCsEnt[ucEntId].RabInfo.aucRbId[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);
                }
                break;

            case RABM_SI_ACTIVE_WITH_RAB:
                g_aRabmCsEnt[ucEntId].RabInfo.ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId);                         /* ����RAB ID                               */
                g_aRabmCsEnt[ucEntId].RabInfo.ucRbNum =
                    (VOS_UINT8)(pMsg->aRabInfo[i].ulRbNum);                         /* ����RB�ĸ���                             */
                for(j = 0; j < g_aRabmCsEnt[ucEntId].RabInfo.ucRbNum; j++)
                {                                                               /* ����RB ID                                */
                    g_aRabmCsEnt[ucEntId].RabInfo.aucRbId[j] =
                        (VOS_UINT8)(pMsg->aRabInfo[i].aulRbId[j]);
                }
                break;
            default:
                break;
            }
        }
    }

    return;
}
VOS_VOID RABM_ComRlsRabReource(
    RRRABM_RAB_IND_STRU                 *pMsg                                   /* Ŀǰ�������Ϣ                           */
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucEntId;
    VOS_UINT8                           ucChgMask;
    VOS_UINT8                           ucSndGmmRabRlsIndFlg = VOS_FALSE;

    for(i = 0; i < pMsg->ulRabCnt; i++)
    {
        if(RABM_CN_PS == pMsg->aRabInfo[i].ulCnDomainId)
        {                                                                       /* ��PS���RAB                              */
            if ( (RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
              && ((pMsg->aRabInfo[i].ulRabId & 0x0f) < RABM_NSAPI_OFFSET) )
            {
                ucEntId = (VOS_UINT8)(pMsg->aRabInfo[i].ulRabId & 0x0f);
            }
            else
            {
                if ((pMsg->aRabInfo[i].ulRabId & 0x0f) < RABM_NSAPI_OFFSET)
                {
                    continue;
                }

                ucEntId = (VOS_UINT8)
                    ((pMsg->aRabInfo[i].ulRabId & 0x0f) - RABM_NSAPI_OFFSET);       /* ���PS���RABMʵ��ID                     */
            }

            switch(g_aRabmPsEnt[ucEntId].ucState)
            {
            case RABM_NULL:
            case RABM_NSAPI_ACTIVE_PENDING:
            case RABM_NSAPI_ACTIVE_NO_RAB:
                break;
            case RABM_NSAPI_ACTIVE_WITH_RAB:
            case RABM_DATA_TRANSFER_STOP:

                if ( ( (g_aRabmPsEnt[ucEntId].QoS.aucQosValue[3] & NAS_RABM_QOS_TRAFFIC_CLASS_MASK) == RABM_CONVERSATION_CLASS)
                  || ( (g_aRabmPsEnt[ucEntId].QoS.aucQosValue[3] & NAS_RABM_QOS_TRAFFIC_CLASS_MASK) == RABM_STREAM_CLASS) )
                {                                                               /* ��ʵʱҵ��                               */
                    RABM_SndSmDeactReq((VOS_UINT8)(ucEntId + RABM_NSAPI_OFFSET));   /* ֪ͨSM                                   */
                }
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId = 0xff;                   /* ��ʼ��RAB IDΪ��Ч                       */
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum = 0;                      /* ��ʼ��RB�ĸ���Ϊ0                        */

                RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_NO_RAB);

                /*����RAB_MAP���е�ucAsId*/
                ucChgMask = 0;
                ucChgMask |= RAB_MAP_CHG_MASK_AS_ID;

                RABM_ChgRabMap(ucEntId + RABM_NSAPI_OFFSET,
                               ucChgMask,
                               g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[0],
                               VOS_NULL_PTR,
                               VOS_NULL_PTR);
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_ComRlsRabReource:NORMAL:RABM state = RABM_NSAPI_ACTIVE_NO_RAB");

                /* ��λucSndGmmRabRlsIndFlg��� */
                ucSndGmmRabRlsIndFlg = VOS_TRUE;
                break;
            case RABM_ACT_PENDING_WITH_RAB:
                RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_PENDING);             /* �ı�ʵ���״̬                           */
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_ComRlsRabReource:NORMAL:RABM state: RABM_ACT_PENDING_WITH_RAB ==> RABM_NSAPI_ACTIVE_PENDING");
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId = 0xff;                   /* ��ʼ��RAB IDΪ��Ч                       */
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum = 0;                      /* ��ʼ��RB�ĸ���Ϊ0                        */

                /*����RAB_MAP���е�ucAsId*/
                ucChgMask = 0;
                ucChgMask |= RAB_MAP_CHG_MASK_AS_ID;

                RABM_ChgRabMap(ucEntId + RABM_NSAPI_OFFSET,
                               ucChgMask,
                               g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[0],
                               VOS_NULL_PTR,
                               VOS_NULL_PTR);

                /* ��λucSndGmmRabRlsIndFlg��� */
                ucSndGmmRabRlsIndFlg = VOS_TRUE;
                break;
            case RABM_TC_STATE_NULL:
                break;
            default:
                break;
            }
            g_aRabmPsEnt[ucEntId].ucStpFlg = RABM_FALSE;
            if(0 != g_aRabmPsEnt[ucEntId].DlDataSave.ucNum)
            {
                /* �ͷŴ洢����������                       */
                RABM_RelSaveData(&g_aRabmPsEnt[ucEntId].DlDataSave, RABM_DOWNLINK);
            }

            if(RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
            {
                RABM_TcInfRls(pMsg, i);
            }
        }
        else
        {                                                                       /* ��CS���RAB                              */
            if(RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
            {
                RABM_TcInfRls(pMsg, i);
            }
            ucEntId = g_aucSiMapEnt[pMsg->aRabInfo[i].ulRabId];
            if(0xFF == ucEntId)
            {
                continue;
            }

            g_aucSiMapEnt[pMsg->aRabInfo[i].ulRabId] = 0xFF;
            switch(g_aRabmCsEnt[ucEntId].ucState)
            {
            case RABM_NULL:
                break;
            case RABM_SI_ACTIVE_WITH_RAB:
                g_aRabmCsEnt [ucEntId].ucState = RABM_NULL;                     /* �ı�ʵ���״̬                           */
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_ComRlsRabReource:NORMAL:RABM state: RABM_SI_ACTIVE_WITH_RAB ==> RABM_NULL ");
                g_aRabmCsEnt [ucEntId].RabInfo.ucRabId = 0xff;                  /* ��ʼ��RAB IDΪ��Ч                       */
                g_aRabmCsEnt [ucEntId].RabInfo.ucRbNum = 0;                     /* ��ʼ��RB�ĸ���Ϊ0                        */
                RABM_SndCcSyncInd(RABMCC_RAB_INACTIVE,
                    pMsg->aRabInfo[i].ulRabId);                                 /* ֪ͨCC��Ӧ����Ϣ                         */
                break;
            default:
                break;
            }
        }
    }

    if (VOS_TRUE == ucSndGmmRabRlsIndFlg)
    {
        /* ��GMM����RAB�ͷ�ָʾ */
        RABM_SndGmmRabRelInd();
    }
}

/*******************************************************************************
  Module:   RABM_RelSaveData
  Function: �ͷŻ��������
  Input:    RABM_DATA_SAVE_STRU      *pLink             �洢�����׵�ַ
            VOS_UINT8                    ucMsgType          ��Ϣ����
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1. ��־��      2003.12.11   �¹�����
*******************************************************************************/
VOS_VOID RABM_RelSaveData(
                      RABM_DATA_SAVE_STRU  *pLink,                              /* �洢�����׵�ַ                           */
                      VOS_UINT8                ucMsgType                            /* ��Ϣ����                                 */
                      )
{
    RABM_DATA_LINK_STRU *pTemp1 = RABM_POINTER_NULL;
    VOS_UINT8    i;

    pTemp1 = pLink->Data.pNxt;
    for( i = 0; i < pLink->ucNum; i++ )
    {
        if ( RABM_DOWNLINK == ucMsgType )
        {                                                                       /* �������������                           */
            RABM_PdcpFree(((PDCP_RABM_DATA_BUF_STRU *)
                    pLink->Data.pData)->pucData);
        }
        else
        {
            /*�ͷ��㿽���ڴ��:*/
            TTF_MemFree(WUEPS_PID_RABM, ((TAFRABM_PS_DATA_REQ_STRU *)
                    pLink->Data.pData)->pData);
        }

        RABM_PdcpFree(pLink->Data.pData);                                       /* �ͷ���Ϣ                                 */

        if(RABM_POINTER_NULL != pTemp1)
        {                                                                       /* ��������ݲ�Ϊ0                          */
            pLink->Data.pData = pTemp1->pData;                                  /* ���»��������                           */
            pLink->Data.pNxt = pTemp1->pNxt;                                    /* ���»������������                       */
            RABM_Free(pTemp1);                                                  /* �ͷ�����ڵ�                             */
        }
        pTemp1 = pLink->Data.pNxt;                                              /* ����ָ��λ��                             */
    }
    pLink->ucNum = 0;

    return;
}


VOS_VOID Rabm_TcInfSave(
                    RRRABM_RAB_IND_STRU  *pMsg,
                    VOS_UINT8  ucRabId
                    )
{
    VOS_UINT8    i,j;
    VOS_UINT8    ucFlag = RABM_FALSE;

    if(0 == g_RabmTcInf.ucLbCnt)
    {                                                                           /* TC����Ϣ�в�����RB��Ϣ                   */
        for(i = 0; i < pMsg->aRabInfo[ucRabId].ulRbNum; i++)
        {
            if(g_RabmTcInf.aRbInf[i].ucEstFlg == RABM_FALSE)
            {
                g_RabmTcInf.aRbInf[i].ucEstFlg = RABM_TRUE;                     /* ��־��RB����                             */
                if(RRC_NAS_CS_DOMAIN == pMsg->aRabInfo[ucRabId].ulCnDomainId)
                {
                    g_RabmTcInf.aRbInf[i].ucDomain = RABM_CN_CS;
                }
                else
                {
                    g_RabmTcInf.aRbInf[i].ucDomain = RABM_CN_PS;
                }
                g_RabmTcInf.aRbInf[i].ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[ucRabId].ulRabId);                   /* ��¼RAB ID                               */
                g_RabmTcInf.aRbInf[i].ucRbId =
                    (VOS_UINT8)(pMsg->aRabInfo[ucRabId].aulRbId[i]);
                ucFlag = RABM_TRUE;
                RABM_SndTcRabInd(i, TC_RAB_SETUP);                                      /* ֪ͨTC�½�����RB��Ϣ                     */
                g_RabmTcInf.ucLbCnt++;
            }
        }
    }
    else
    {
        for(i = 0; i < pMsg->aRabInfo[ucRabId].ulRbNum; i++)
        {
            for(j = 0; j < g_RabmTcInf.ucLbCnt; j++)
            {
                if ((VOS_UINT8)(pMsg->aRabInfo[ucRabId].aulRbId[i])
                                  == g_RabmTcInf.aRbInf[j].ucRbId)
                {
                    break;
                }
            }
            if((g_RabmTcInf.ucLbCnt == j) && (g_RabmTcInf.ucLbCnt < TC_LB_MAX_RBNUM))
            {
                g_RabmTcInf.aRbInf[j].ucEstFlg = RABM_TRUE;                     /* ��־��RB����                             */
                if(RRC_NAS_CS_DOMAIN == pMsg->aRabInfo[ucRabId].ulCnDomainId)
                {
                    g_RabmTcInf.aRbInf[j].ucDomain = RABM_CN_CS;
                }
                else
                {
                    g_RabmTcInf.aRbInf[j].ucDomain = RABM_CN_PS;
                }
                g_RabmTcInf.aRbInf[j].ucRabId =
                    (VOS_UINT8)(pMsg->aRabInfo[ucRabId].ulRabId);                   /* ��¼RAB ID                               */
                g_RabmTcInf.aRbInf[j].ucRbId =
                    (VOS_UINT8)(pMsg->aRabInfo[ucRabId].aulRbId[i]);
                g_RabmTcInf.ucLbCnt++;
                /*��TC�ϱ�RAB INFO*/
                RABM_SndTcRabInd(j, TC_RAB_SETUP);                                      /* ֪ͨTC�½�����RB��Ϣ                     */
            }
        }
    }

    /* RAB���� */
    if(RABM_FALSE == ucFlag)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Rabm_TcInfSave:WARNING:Rabm_TcInfSave no rab setup ");
    }

    return;
}
VOS_VOID RABM_TcInfRls(
                   RRRABM_RAB_IND_STRU  *pMsg,
                   VOS_UINT8  ucRabId
                   )
{
    VOS_UINT8    i;

    if(pMsg->aRabInfo[ucRabId].ulRbNum > 1)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "RABM_TcInfRls:WARNING:RRC->RABM(TC) RAB contains more than one RB!");
        return;
    }

    for(i = 0; i < TC_LB_MAX_RBNUM; i++)
    {
        if(g_RabmTcInf.aRbInf[i].ucRbId ==
            (VOS_UINT8)(pMsg->aRabInfo[ucRabId].aulRbId[0]))
        {
            if(RABM_TRUE == g_RabmTcInf.aRbInf[i].ucEstFlg)
            {
                g_RabmTcInf.aRbInf[i].ucEstFlg = RABM_FALSE;                    /* ��־��RB������                           */
                RABM_SndTcRabInd(i, TC_RAB_RELEASE);                            /* ֪ͨTC��RB�ͷ�                           */

                /*�޵� GCF����:7.2.3.36�������·���CLOSE UP TEST LOOP��ָʾ��LB����Ϊ0��
                    ��ʵ�ʽ�����RAB��һ�£����»���ʧ�ܡ�Ϊ�˹�ܸ����⣬�����¼��:*/
                if (0 != g_RabmTcInf.ucLbCnt)
                {
                    g_RabmTcInf.ucLbCnt--;
                }
                break;
            }
        }
    }
    return;
}

/*******************************************************************************
  Module:   RABM_TcRbStatus
  Function: ��¼RAB����Ϣ
  Input:    RRRABM_STATUS_IND_STRU      *pMsg
            VOS_UINT8                       ucRabId
            VOS_UINT8                       ucRelFlg
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1. ��־��      2003.12.11   �¹�����
*******************************************************************************/
VOS_VOID RABM_TcRbStatus(
                     RRRABM_STATUS_IND_STRU  *pMsg,
                     VOS_UINT8  ucRabId,
                     VOS_UINT8  ucRelFlg
                     )
{
    VOS_UINT8    i;

    for(i = 0; i < TC_LB_MAX_RBNUM; i++)
    {
        if(g_RabmTcInf.aRbInf[i].ucRabId ==
            (VOS_UINT8)(pMsg->aRab[ucRabId].ulRabId))
        {
            if(TC_RAB_RELEASE == ucRelFlg)
            {
                g_RabmTcInf.aRbInf[i].ucEstFlg = RABM_FALSE;                    /* ��־��RB������                           */
            }
            else
            {
                g_RabmTcInf.aRbInf[i].ucEstFlg = RABM_TRUE;                     /* ��־��RB����                             */
            }
            RABM_SndTcRabInd(i, ucRelFlg);                                      /* ֪ͨTC��RBֹͣ/����                      */
            break;
        }
    }
    return;
}
RABM_RAB_STATUS_ENUM_UINT32 NAS_RABM_GetGRabIdStatus(
    VOS_UINT32                          ulEntId
)
{
    VOS_UINT8                           ucState;
    RABM_RAB_STATUS_ENUM_UINT32         enRabStatus;

    ucState = NAS_RABM_GetGPsEntState(ulEntId);

    switch (ucState)
    {
        case RABM_2G_NULL:
            enRabStatus = RABM_RAB_STATUS_FAIL;
            break;
        case RABM_NSAPI_OK_TRANSMODE_NO:
            enRabStatus = RABM_RAB_STATUS_SUSPEND;
            break;
        case RABM_DATA_TRANS_READY:
            enRabStatus = RABM_RAB_STATUS_ACTIVE;
            break;
        case RABM_ROUT_AREA_UPDATE:
            enRabStatus = RABM_RAB_STATUS_SUSPEND;
            break;
        case RABM_DATA_TRANS_STOP:
            enRabStatus = RABM_RAB_STATUS_SUSPEND;
            break;
        default:
            enRabStatus = RABM_RAB_STATUS_FAIL;
            break;
    }

    return enRabStatus;

}



RABM_RAB_STATUS_ENUM_UINT32 NAS_RABM_GetWRabIdStatus(
    VOS_UINT32                          ulEntId
)
{
    VOS_UINT8                           ucState;
    RABM_RAB_STATUS_ENUM_UINT32         enRabStatus;

    ucState = NAS_RABM_GetWPsEntState(ulEntId);

    switch (ucState)
    {
        case RABM_NULL:
            enRabStatus = RABM_RAB_STATUS_FAIL;
            break;
        case RABM_NSAPI_ACTIVE_PENDING:
            enRabStatus = RABM_RAB_STATUS_FAIL;
            break;
        case RABM_NSAPI_ACTIVE_NO_RAB:
            enRabStatus = RABM_RAB_STATUS_IDLE;
            break;
        case RABM_NSAPI_ACTIVE_WITH_RAB:
            enRabStatus = RABM_RAB_STATUS_ACTIVE;
            break;
        case RABM_DATA_TRANSFER_STOP:
            enRabStatus = RABM_RAB_STATUS_SUSPEND;
            break;
        case RABM_ACT_PENDING_WITH_RAB:
            enRabStatus = RABM_RAB_STATUS_FAIL;
            break;
        default:
            enRabStatus = RABM_RAB_STATUS_FAIL;
            break;
    }

    return enRabStatus;

}


RABM_RAB_STATUS_ENUM_UINT32 NAS_RABM_GetRabIdStatus(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          ulEntId;
    RABM_RAB_STATUS_ENUM_UINT32         enRabStatus;
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* ��ʼ�� */
    enRabStatus = RABM_RAB_STATUS_FAIL;

    /* �ж�RABID�Ƿ���Ч */
    if ((ucRabId < NAS_RABM_RAB_ID_MIN) || (ucRabId > NAS_RABM_RAB_ID_MAX))
    {
        return enRabStatus;
    }

    /* ��ȡ��ǰ��ϵͳģʽ */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();
    ulEntId          = ucRabId - RABM_NSAPI_OFFSET;

    if (NAS_MML_NET_RAT_TYPE_GSM == enCurrentSysMode)
    {
        enRabStatus = NAS_RABM_GetGRabIdStatus(ulEntId);
    }

    if (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrentSysMode)
    {
        enRabStatus = NAS_RABM_GetWRabIdStatus(ulEntId);
    }

    return enRabStatus;
}
VOS_UINT32 NAS_RABM_GetDefaultRabId(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                          *pucDeftRabId
)
{
    VOS_UINT8                           ucLinkdRabId = RAB_MAP_INVALID_RAB_ID;

    if (VOS_NULL_PTR == pucDeftRabId)
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_GetDefaultRabId: pucDeftRabId is NULL!");
        return PS_FAIL;
    }

    if (!RAB_MAP_RAB_IS_VALID(ucRabId))
    {
        NAS_ERROR_LOG1(WUEPS_PID_RABM,
            "NAS_RABM_GetDefaultRabId: ucRabId is invalid! <ucRabId>", ucRabId);
        return PS_FAIL;
    }

    if (PS_TRUE != g_astRabMap[ucRabId].enucExistInd)
    {
        NAS_ERROR_LOG1(WUEPS_PID_RABM,
            "NAS_RABM_GetDefaultRabId: RAB MAP Not Exist! <ucRabId>", ucRabId);
        return PS_FAIL;
    }

    ucLinkdRabId = g_astRabMap[ucRabId].ucLinkdRabId;

    if (!RAB_MAP_RAB_IS_VALID(ucLinkdRabId))
    {
        NAS_ERROR_LOG1(WUEPS_PID_RABM,
            "NAS_RABM_GetDefaultRabId: Linked RABID is invalid! <ucLinkdRabId>", ucLinkdRabId);
        return PS_FAIL;
    }

    *pucDeftRabId = ucLinkdRabId;

    return PS_SUCC ;
}


VOS_VOID NAS_RABM_UL_DataReq (
    CDS_RABM_TRANS_DATA_STRU           *pstUlData
)
{
    /* ����RABM API  ������������ */
    RABM_SendUlData(pstUlData->ucRabId, pstUlData->pstSdu);

    return;
}
VOS_UINT32 NAS_RABM_DL_DataInd(
    VOS_UINT8                           ucRabId,
    TTF_MEM_ST                         *pstData
)
{
    VOS_UINT32                  ulDataLen;
    CDS_RABM_TRANS_DATA_STRU    stCdsDlData;
    VOS_UINT16                  usModemid;

    /* ��ֵ */
    ulDataLen = TTF_MemGetLen(WUEPS_PID_RABM, pstData);

    stCdsDlData.ucRabId     = ucRabId;
    stCdsDlData.pstSdu      = pstData;
    stCdsDlData.ulSduLen    = ulDataLen;

    stCdsDlData.aucRev[0]   = 0;
    stCdsDlData.aucRev[1]   = 0;
    stCdsDlData.aucRev[2]   = 0;

    usModemid = VOS_GetModemIDFromPid(WUEPS_PID_RABM);

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_RABM_GetCurrentSysMode())
    {
        /* ����UMTS CDS API�ӿڷ����������� */
        CDS_UMTS_DL_DataInd(&stCdsDlData, usModemid);
    }
    else
    {
        /* ����GPRS CDS API�ӿڷ����������� */
        CDS_GSM_DL_DataInd(&stCdsDlData, usModemid);
    }

    return VOS_OK;
}
QCI_TYPE_ENUM_UINT8 NAS_RABM_QosParaTransferToQci(
    VOS_UINT8                           ucTrafficClass,
    VOS_UINT8                           ucTransDelay,
    VOS_UINT8                           ucTraffHandlPrior,
    VOS_UINT8                           ucSrcStatisticsDescriptor,
    VOS_UINT8                           ucSignallingIndication
)
{
    QCI_TYPE_ENUM_UINT8                 enQci;

    /* ת������μ�: 23.401
       Annex E (normative):
        Mapping between EPS and Release 99 QoS parameters
        QCI    Traffic_Class  Traffic_Handling_Priority Signalling_Indication  Src_Stats_Descriptor
         1     Conversational          NA                       NA                  SPEECH
         2     Conversational          NA                       NA                    NA
         3     Conversational          NA                       NA                   Unknown
         4     Streaming               NA                       NA                   Unknown
         5     Interactive              1                       YES                  Unknown
         6     Interactive              1                       NO                    NA
         7     Interactive              2                       NO                    NA
         8     Interactive              3                       NO                    NA
         9     Background              NA                       NA                    NA
    */
    /* ����QOS trafficClass������ȡQCI */
    if (NAS_RABM_QOS_TRAFFIC_CLASS_CONVERSATIONAL == ucTrafficClass)
    {
        if (NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_SPEECH == ucSrcStatisticsDescriptor)
        {
            enQci       = QCI_TYPE_QCI1_GBR;
        }
        else if (ucTransDelay >= NAS_RABM_QOS_TRANSFER_DELAY_150MS)
        {
            enQci       = QCI_TYPE_QCI2_GBR;
        }
        else
        {
            enQci       = QCI_TYPE_QCI3_GBR;
        }
    }
    else if (NAS_RABM_QOS_TRAFFIC_CLASS_STREAMING == ucTrafficClass)
    {
        enQci       = QCI_TYPE_QCI4_GBR;
    }
    else if (NAS_RABM_QOS_TRAFFIC_CLASS_INTERACTIVE == ucTrafficClass)
    {
        if (NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_1 == ucTraffHandlPrior)
        {
            if (NAS_RABM_QOS_SIGNAL_IND_OPTIMISE == ucSignallingIndication)
            {
                enQci       = QCI_TYPE_QCI5_NONGBR;
            }
            else
            {
                enQci       = QCI_TYPE_QCI6_NONGBR;
            }
        }
        else if (NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_2 == ucTraffHandlPrior)
        {
            enQci       = QCI_TYPE_QCI7_NONGBR;
        }
        else
        {
            enQci       = QCI_TYPE_QCI8_NONGBR;
        }
    }
    else
    {
        enQci       = QCI_TYPE_QCI9_NONGBR;
    }

    return enQci;
}
QCI_TYPE_ENUM_UINT8 NAS_RABM_GetQciFromQos(
    VOS_UINT32                      ulQosLength,
    VOS_UINT8                      *pQosValue
)
{
    QCI_TYPE_ENUM_UINT8                 enQci;
    VOS_UINT8                           ucTrafficClass;
    VOS_UINT8                           ucTransDelay;
    VOS_UINT8                           ucTraffHandlPrior;
    VOS_UINT8                           ucSrcStatisticsDescriptor;
    VOS_UINT8                           ucSignallingIndication;


    /* ��ʼ�� */
    enQci          = QCI_TYPE_QCI9_NONGBR;

    /* ��ȡQOS��trafficClass���� */
    if (ulQosLength < NAS_RABM_QOS_TRAFFIC_CLASS_BYTE_OFFSET)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_RABM_GetQciFromQos:WARNING:QOS too short!");
        return enQci;
    }

    if (ulQosLength > NAS_RABM_QOS_TRAFFIC_CLASS_BYTE_OFFSET)
    {
        ucTrafficClass = (pQosValue[NAS_RABM_QOS_TRAFFIC_CLASS_BYTE_OFFSET] & NAS_RABM_QOS_TRAFFIC_CLASS_MASK)
                                        >> NAS_RABM_QOS_TRAFFIC_CLASS_BIT_OFFSET;
    }
    else
    {
        ucTrafficClass = NAS_RABM_QOS_TRAFFIC_CLASS_BACKGROUND;
    }

    /* ��ȡQOS��Transfer Delay���� */
    if (ulQosLength > NAS_RABM_QOS_TRANSFER_DELAY_BYTE_OFFSET)
    {
        ucTransDelay = (pQosValue[NAS_RABM_QOS_TRANSFER_DELAY_BYTE_OFFSET] & NAS_RABM_QOS_TRANSFER_DELAY_MASK)
                                        >> NAS_RABM_QOS_TRANSFER_DELAY_BIT_OFFSET;
    }
    else
    {
        ucTransDelay = 0;
    }

    /* ��ȡQOS��Traffic Handling Priority���� */
    if (ulQosLength > NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_BYTE_OFFSET)
    {
        ucTraffHandlPrior = pQosValue[NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_BYTE_OFFSET]
                                        & NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_MASK;
    }
    else
    {
        ucTraffHandlPrior = NAS_RABM_QOS_TRAFFIC_HANDLING_PRIORITY_1;
    }

    /* ��ȡQOS��Source Statistics Descriptor���� */
    if (ulQosLength > NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_BYTE_OFFSET)
    {
        ucSrcStatisticsDescriptor = pQosValue[NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_BYTE_OFFSET]
                                        & NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_MASK;
    }
    else
    {
        ucSrcStatisticsDescriptor = NAS_RABM_QOS_SRC_STATS_DESCRIPTOR_UNKNOWN;
    }

    /* Signalling-Indication ��ֵֻȡ���ֽڵĵ�5λ */
    if (ulQosLength > NAS_RABM_QOS_SIGNAL_IND_BYTE_OFFSET)
    {
        ucSignallingIndication = (pQosValue[NAS_RABM_QOS_SIGNAL_IND_BYTE_OFFSET] & NAS_RABM_QOS_SIGNAL_IND_MASK)
                                        >> NAS_RABM_QOS_SIGNAL_IND_BIT_OFFSET;
    }
    else
    {
        ucSignallingIndication = NAS_RABM_QOS_SIGNAL_IND_NOT_OPTIMISE;
    }

    enQci = NAS_RABM_QosParaTransferToQci(ucTrafficClass,
                                          ucTransDelay,
                                          ucTraffHandlPrior,
                                          ucSrcStatisticsDescriptor,
                                          ucSignallingIndication);
    return enQci;
}




VOS_VOID NAS_RABM_SetFinIpInRdFlag(VOS_UINT32 ulFlag)
{
    GMM_RABM_NET_RAT_ENUM_UINT32        enCurrentSysMode;

    /* ��ȡ��ǰ��ϵͳģʽ */
    enCurrentSysMode = NAS_RABM_GetCurrentSysMode();

    switch (enCurrentSysMode)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_UTRANCTRL_RABM_SetFinIpInRdFlag(ulFlag);
            break;

        default:
            break;
    }

    return;
}
VOS_VOID NAS_RABM_StartReestRabPendingTmr(VOS_UINT8 ucRabId)
{
    RABM_ENTITY_PS_STRU                *pstWPsEnt;

    pstWPsEnt = NAS_RABM_GetWPsEntAddr(ucRabId - RABM_NSAPI_OFFSET);

    if (VOS_OK != NAS_StartRelTimer(&(pstWPsEnt->hRabPendingTmrHdl),
                                    WUEPS_PID_RABM,
                                    NAS_RABM_GET_RAB_PENDING_TMR_LEN(),
                                    ucRabId,
                                    RABM_TIMER_RAB_REESTABLISH_PENDING,
                                    VOS_RELTIMER_NOLOOP))
    {
        NAS_ERROR_LOG(WUEPS_PID_RABM,
            "NAS_RABM_StartReestRabPendingTmr: Start timer failed.");
        pstWPsEnt->hRabPendingTmrHdl = VOS_NULL_PTR;
    }

    return;
}


VOS_VOID NAS_RABM_StopReestRabPendingTmr(VOS_UINT8 ucRabId)
{
    RABM_ENTITY_PS_STRU                *pstWPsEnt;

    pstWPsEnt = NAS_RABM_GetWPsEntAddr(ucRabId - RABM_NSAPI_OFFSET);

    if (VOS_NULL_PTR != pstWPsEnt->hRabPendingTmrHdl)
    {
        if (VOS_OK != NAS_StopRelTimer(WUEPS_PID_RABM,
                                       RABM_TIMER_RAB_REESTABLISH_PENDING,
                                       &(pstWPsEnt->hRabPendingTmrHdl)))
        {
            NAS_ERROR_LOG(WUEPS_PID_RABM,
                "NAS_RABM_StopReestRabPendingTmr: Stop timer failed.");
            pstWPsEnt->hRabPendingTmrHdl = VOS_NULL_PTR;
        }
    }

    return;
}

/*lint +e958*/


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

