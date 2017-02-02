
#include "SmInclude.h"
#include "Taf_Common.h"
#include "mdrv.h"
#include "NVIM_Interface.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SM_RCVGMM_C

extern VOS_UINT8* SM_GetSystemAppConfigAddr(VOS_VOID);


/*******************************************************************************
  Module:      SM_ComSaveTICheck
  Function:    �洢Transaction identifier
  Input:       VOS_UINT8                              *tempMsg     ������Ϣ
               VOS_UINT32                              *ulSum       ������
               SM_NW_MSG_STRU                     *pMsgIE      ���ݽṹָ��
  Output:      VOS_VOID
  NOTE:
  Return:      SM_RETURN_OK
               SM_RETURN_NG
  History:
      1.  ��־��      2003.12.08   �¹�����
*******************************************************************************/
VOS_UINT8 SM_ComSaveTICheck(
                       VOS_UINT8                              ucMsgType,
                       VOS_UINT8                              **tempMsg,            /* ������Ϣ                                 */
                       VOS_UINT32                              *ulSum,               /* ������                                   */
                       SM_NW_MSG_STRU                     *pMsgIE               /* ���ݽṹָ��                             */
                      )
{
    VOS_UINT8    ucRet;

    ucRet = SM_RETURN_OK;
    if(0x70 == (0x70 & (**tempMsg)))
    {                                                                           /* TI����չλ                               */
        pMsgIE->ucTi = **tempMsg & 0x80;                                        /* �洢TI Flag                              */
        (*tempMsg)++;                                                           /* ����ָ��ƫ�Ƶĳ���                       */
        *ulSum += 1;                                                            /* ��������1                                */
        pMsgIE->ucTi = (**tempMsg & 0x7f) | (pMsgIE->ucTi & 0x80);              /* �洢Transaction identifier               */
        (*tempMsg)++;                                                           /* ����ָ��ƫ�Ƶĳ���                       */
        *ulSum += 1;                                                            /* ��������1                                */
        pMsgIE->ucTiFlg = pMsgIE->ucTi & 0x80;
    }
    else
    {                                                                           /* TI����չ                                 */
        pMsgIE->ucTi = **tempMsg;                                               /* ��ÿտ���Ϣ�еĵ�һ�ֽ�                 */
        pMsgIE->ucTiFlg = pMsgIE->ucTi & 0x80;                                  /* �洢TI Flag                              */
        if(0x80 == (pMsgIE->ucTi & 0x80))
        {
            pMsgIE->ucTi = (pMsgIE->ucTi & 0x80) | ((pMsgIE->ucTi>>4) & 0x07);  /* TIΪָ��ĵ�7��6��5λ��ֵ                */
        }
        else
        {
            pMsgIE->ucTi = pMsgIE->ucTi >> 4;                                   /* TIΪָ��ĵ�7��6��5λ��ֵ                */
        }
        (*tempMsg)++;                                                           /* ����ָ��ƫ�Ƶĳ���                       */
        *ulSum += 1;                                                            /* ��������1                                */
    }

    switch(ucMsgType)
    {
    case SM_REQ_PDP_CONTEXT_ACT:
        if( 0x80 == pMsgIE->ucTiFlg )
        {
            ucRet = SM_RETURN_NG;

            PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                    "SM_ComSaveTICheck:WARNING:NW->SM: Invalid transaction identifier value !");

        }
        break;
    case SM_ACT_PDP_CONTEXT_ACC:
    case SM_ACT_PDP_CONTEXT_REJ:
    case SM_DEACT_PDP_CONTEXT_REQ:
    case SM_DEACT_PDP_CONTEXT_ACC:
    case SM_MOD_PDP_CONTEXT_REQ_N2M:
    case SM_MOD_PDP_CONTEXT_ACC_N2M:
    case SM_MOD_PDP_CONTEXT_REJ:
    case SM_ACT_SEC_PDP_CONTEXT_ACC:
    case SM_ACT_SEC_PDP_CONTEXT_REJ:
        if(0xff != g_TiMapToNsapi[pMsgIE->ucTi])
        {
            if((( 1 == (pMsgIE->ucTiFlg >> 7 ))
                  &&( SM_TI_NET_ORG == g_SmEntity.
                  aPdpCntxtList[g_TiMapToNsapi[pMsgIE->ucTi]].ucTiFlg ))
                || (( 0 == (pMsgIE->ucTiFlg >> 7 ))
                   &&( SM_TI_MS_ORG == g_SmEntity.
                   aPdpCntxtList[g_TiMapToNsapi[pMsgIE->ucTi]].ucTiFlg )))
            {
                SM_SndStatusMsg(pMsgIE->ucTi,TAF_SM_REJ_CAUSE_PROTOCOL_ERR);    /* cause:protocol errors                    */
                ucRet = SM_RETURN_NG;

            }
        }
        break;
    default :
        break;
    }
    return ucRet;
}


VOS_VOID NAS_SM_ComSaveLlcSapi(
    VOS_UINT8                           **ppucMsg,
    VOS_UINT32                          *pulSum
)
{
    /* ��Ϣָ��ָ��IEI�ĺ�һλ�������¼����� */
    (*ppucMsg)++;
    *pulSum += 1;

    /* ��Ч��ʶ����Ϊ��Ч����ȡSAPI���ݴ浽g_aucSapi[0][1]λ�� */
    g_aucSapi[0][0] = 1;
    g_aucSapi[0][1] = 0x0F & (**ppucMsg);

    /* ��Ϣָ�����һλ�������¼����� */
    (*ppucMsg)++;
    *pulSum += 1;
}

#if (FEATURE_ON == FEATURE_IPV6)
VOS_VOID NAS_SM_ComSaveSmCauseTwo(
    VOS_UINT32                          ulPduLen,
    VOS_UINT8                         **ppucMsg,
    VOS_UINT32                         *pulSum,
    SM_MSG_IE_COMMON_STRU              *pstIE

)
{
    /*----------------------------------------------------------------------
       8   7   6   5   4   3   2   1
       SM cause 2 IEI                  octet 1
       Length of SM cause 2 contents   octet 2
       SM cause 2 value                octet 3
    ----------------------------------------------------------------------*/
    /*----------------------------------------------------------------------
      A SM cause 2 value is coded as octet 2 of the SM cause information element.
    ----------------------------------------------------------------------*/

    /* ��Ϣָ��ָ��IEI�ĺ�һλ�������¼����� */
    (*ppucMsg)++;
    *pulSum += 1;

    /* ��������������Ϣ���ȣ�ֱ�ӷ��� */
    if (*pulSum < ulPduLen)
    {
        /* ��ȡIE���Ⱥ�����ָ�� */
        pstIE->ucLen  = **ppucMsg;
        pstIE->pValue = *ppucMsg + 1;

        /* ������Ϣָ��ƫ�ƺͼ����� */
        *ppucMsg      += pstIE->ucLen + 1;
        *pulSum       += pstIE->ucLen + 1;

        /* ��������������Ϣ���ȣ���ո�IE���� */
        if (*pulSum > ulPduLen)
        {
            pstIE->ucLen = 0;
        }
    }

}
#endif
VOS_UINT32 NAS_SM_ComProcUnknowIE(
    VOS_UINT32                          ulPduLen,
    VOS_UINT8                           **ppucMsg,
    VOS_UINT32                          *pulSum
)
{
    VOS_UINT32                          ullen;

    if (0x00 == ((**ppucMsg) & 0xF0))
    {
        /*----------------------------------------------------------------------
          An IE is encoded as 'comprehension required' if bits 5, 6, 7 and 8 of
          its IEI are set to zero. Refer to section 8.5 in TS 24.008
        ----------------------------------------------------------------------*/
        return SM_RETURN_NG;
    }
    else
    {
        /*---------------------------------------------------------
          Ignore unknown IE. Refer to section 11.2.4 in TS 24.007
        ---------------------------------------------------------*/
        if (0x80 == ((**ppucMsg) & 0x80))
        {
            /*----------------------------------------------------------------
              A 1 valued bit 8 indicates that the whole IE is one octet long
            ----------------------------------------------------------------*/
            (*ppucMsg)++;                                                       /* ����ָ��ƫ�Ƶĳ���                       */
            *pulSum += 1;                                                       /* ��������1                                */
        }
        else
        {
            /*------------------------------------------------------------------
              A 0 valued bit 8 indicates that the following octet is a length
              octet
            ------------------------------------------------------------------*/
            (*ppucMsg)++;                                                       /* ����ָ��ƫ�Ƶĳ���,ָ��IEI�ĺ�һλ       */
            *pulSum += 1;                                                       /* ��������1                                */

            if (*pulSum < ulPduLen)
            {                                                                   /* ������С����Ϣ����                       */
                ullen = *pulSum + **ppucMsg + 1;
                if (ullen <= ulPduLen)
                {
                    *pulSum     += **ppucMsg + 1;                               /* ���¼���������                           */
                    *ppucMsg    += **ppucMsg + 1;                               /* ����ָ��ƫ�Ƶĳ���                       */
                }
            }
        }
    }

    return SM_RETURN_OK;
}
VOS_VOID NAS_SM_ComSaveIEValue(
    VOS_UINT32                          ulPduLen,
    VOS_UINT8                           **ppucMsg,
    VOS_UINT32                          *pulSum,
    SM_MSG_IE_COMMON_STRU               *pstIE
)
{
    /* ��Ϣָ��ָ��IEI�ĺ�һλ�������¼����� */
    (*ppucMsg)++;
    *pulSum += 1;

    /* ��������������Ϣ���ȣ�ֱ�ӷ��� */
    if (*pulSum < ulPduLen)
    {
        /* ��ȡIE���Ⱥ�����ָ�� */
        pstIE->ucLen  = **ppucMsg;
        pstIE->pValue = *ppucMsg + 1;

        /* ������Ϣָ��ƫ�ƺͼ����� */
        *ppucMsg    += pstIE->ucLen + 1;
        *pulSum     += pstIE->ucLen + 1;

        /* ��������������Ϣ���ȣ���ո�IE���� */
        if (*pulSum > ulPduLen)
        {
            pstIE->ucLen = 0;
        }
    }
}

/*******************************************************************************
  Module:      SM_ComOptionalCheck
  Function:    ��Ϣ��Optional��ļ��洢
  Input:       VOS_UINT8                        *tempMsg     ������Ϣ
               VOS_UINT32                       ulSmPduLen   ������Ϣ����
               VOS_UINT32                       *ulSum       ������
               SM_NW_MSG_STRU                   *pMsgIE      ���ݽṹָ��
  Output:      VOS_UINT32                       ucRet
  NOTE:
  Return:      VOS_VOID
  History:
      1.  ��־��      2003.12.08   �¹�����
*******************************************************************************/
VOS_UINT32 SM_ComOptionalCheck(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          ulSmPduLen,
    VOS_UINT32                          *pulSum,
    SM_NW_MSG_STRU                      *pMsgIE
)
{
    VOS_UINT32                          ucRet;                                  /* ���巵��ֵ                               */

    ucRet = SM_RETURN_OK;                                                       /* �÷���ֵΪ�ɹ�                           */

    for ( ; *pulSum < ulSmPduLen; )
    {                                                                           /* ѭ��option��,�ﵽָ����Ϣ����ʱ����      */
        if (NAS_SM_IEI_NEW_RADIO_PRIORITY == ((*pucMsg) >> 4))
        {
            /*-------------------------------------------------
               8     7     6     5  |   4  |   3     2     1
              -----------------------------------------------
               Radio priority IEI   |   0  |  Radio priority
                                    | spare|   level value
            -------------------------------------------------*/
            pMsgIE->ucRadioPri = (*pucMsg) & 0x07;                              /* �洢Radio priority                       */
            pucMsg++;                                                           /* ����ָ��ƫ�Ƶĳ���                       */
            *pulSum += 1;                                                       /* ��������1                                */
        }
        else if (NAS_SM_IEI_TEARDOWN_INDICATOR == ((*pucMsg) & 0xF0))
        {
            /*--------------------------------------------------
               8     7     6     5  |   4     3     2  |   1
              -----------------------------------------------
               Tear down indicator  |   0     0     0  |  TDI
                       IEI          |       spare      | flag
            --------------------------------------------------*/
            pMsgIE->ucTdi = (*pucMsg) & 0x01;                                   /* �洢Tear down indicator                  */
            pucMsg++;                                                           /* ����ָ��ƫ�Ƶĳ���                       */
            *pulSum += 1;                                                       /* ��������1                                */
        }
        else
        {
            switch (*pucMsg)
            {                                                                   /* �ж�IEI                                  */
                case NAS_SM_IEI_PDP_ADDRESS:
                    NAS_SM_ComSaveIEValue(ulSmPduLen, &pucMsg, pulSum, &(pMsgIE->PdpAddr));
                    break;

                case NAS_SM_IEI_PROTOCOL_CFG_OPTIONS:
                    NAS_SM_ComSaveIEValue(ulSmPduLen, &pucMsg, pulSum, &(pMsgIE->ProCnfgOpt));
                    break;

                case NAS_SM_IEI_PACKET_FLOW_ID:
                    NAS_SM_ComSaveIEValue(ulSmPduLen, &pucMsg, pulSum, &(pMsgIE->Pfi));
                    break;

                case NAS_SM_IEI_ACCESS_POINT_NAME:
                    NAS_SM_ComSaveIEValue(ulSmPduLen, &pucMsg, pulSum, &(pMsgIE->Apn));
                    break;

                case NAS_SM_IEI_NEW_QOS:
                    NAS_SM_ComSaveIEValue(ulSmPduLen, &pucMsg, pulSum, &(pMsgIE->Qos));
                    break;

                case NAS_SM_IEI_REQUEST_LLC_SAPI:
                    NAS_SM_ComSaveLlcSapi(&pucMsg, pulSum);
                    break;

#if (FEATURE_ON == FEATURE_IPV6)
                case NAS_SM_IEI_CAUSE_TWO:
                    NAS_SM_ComSaveSmCauseTwo(ulSmPduLen, &pucMsg, pulSum, &(pMsgIE->stSmCauseTwo));
                    break;
#endif

                default:
                    ucRet = NAS_SM_ComProcUnknowIE(ulSmPduLen, &pucMsg, pulSum);
                    if (SM_RETURN_NG == ucRet)
                    {
                        return ucRet;
                    }
                    break;
            }
        }
    }

    return ucRet;
}

/*******************************************************************************
  Module:      SM_ComActPdpCntxtAccCheck
  Function:    ���洢���෢��MS��ACTIVATE PDP CONTEXT ACCEPT��Ϣ�Ĵ���
  Input:       VOS_UINT8   *pMsg                      ������Ϣ
               VOS_UINT32   ulSmPduLen                 ������Ϣ����
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  ��־��      2003.12.08   �¹�����
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComActPdpCntxtAccCheck(
    VOS_UINT8                 *pMsg,             /* ������Ϣ */
    VOS_UINT32                ulSmPduLen         /* ������Ϣ���� */
)
{
    SM_NW_MSG_STRU                         *pMsgIE;                             /* ����ָ��                                 */
    VOS_UINT8                              *tempMsg;                            /* ����ֲ�ָ��                             */
    VOS_UINT32                              ulSum;                              /* ���������                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* �����ڴ�                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComActPdpCntxtAccCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet((VOS_VOID *)pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum   = 0;                                                                /* ��������ʼֵ��0                          */
    tempMsg = pMsg;                                                             /* ָ��������Ϣ                             */


    if ( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        if ( SM_RETURN_NG == SM_ComSaveTICheck(SM_ACT_PDP_CONTEXT_ACC,
            &tempMsg, &ulSum, pMsgIE))
        {                                                                       /* ���ú����洢Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* �ͷ�������ڴ�                           */
            return SM_NULL;                                                     /* ����SM_NULL                              */
        }
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");

        return SM_NULL;                                                         /* ����SM_NULL                              */
    }

    ulSum   ++;
    tempMsg ++;                                                                 /*ֻ����MSG TYPE,������SAPI*/
    g_aucSapi[0][0] = 1;                                                        /*��Ч��ʶ����Ϊ��Ч*/
    g_aucSapi[0][1] = 0x0F & (*tempMsg);                                        /*��ȡSAPI,�� �ݴ浽g_aucSapi[0][1]λ��*/
    ulSum   ++;
    tempMsg ++;

    if ( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        pMsgIE->Qos.ucLen = *(tempMsg);                                         /* �洢Negotiated QoS�ĳ���                 */
        pMsgIE->Qos.pValue = tempMsg + 1;                                       /* �洢Negotiated QoS��ָ��                 */
        tempMsg += pMsgIE->Qos.ucLen + 1;                                       /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum += pMsgIE->Qos.ucLen + 1;                                         /* ���¼���������                           */
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");

        return SM_NULL;                                                         /* ����SM_NULL                              */
    }

    if ( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        pMsgIE->ucRadioPri=0x07 & (*tempMsg);                                   /* �洢Radio priority                       */
        tempMsg++;                                                              /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum++;                                                                /* ��������1                                */
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }

    if ( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        if (SM_RETURN_OK != SM_ComOptionalCheck(tempMsg, ulSmPduLen, &ulSum, pMsgIE))               /* ���ú����洢Option��IE                   */
        {
            SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
            SM_Free(pMsgIE);                                                    /* �ͷ�������ڴ�                           */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActPdpCntxtAccCheck:WARNING:Unknown IE encoded as comprehension required!");
            return SM_NULL;                                                     /* ����SM_NULL                              */
        }
    }

    return pMsgIE;                                                              /* ���ش洢�Ľṹ��ָ��                     */
}

/*******************************************************************************
  Module:      SM_ComActPdpCntxtRejCheck
  Function:    ���洢���෢��MS��ACTIVATE PDP CONTEXT REJECT��Ϣ�Ĵ���
  Input:       VOS_UINT8   *pMsg                      ������Ϣ
               VOS_UINT32   ulSmPduLen                 ������Ϣ����
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  ��־��      2003.12.08   �¹�����
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComActPdpCntxtRejCheck(
                                             VOS_UINT8   *pMsg,                     /* ������Ϣ                                 */
                                             VOS_UINT32   ulSmPduLen                 /* ������Ϣ����                             */
                                             )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* ����ָ��                                 */
    VOS_UINT8                              *tempMsg;                                /* ����ֲ�ָ��                             */
    VOS_UINT32                              ulSum;                                   /* ���������                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* �����ڴ�                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComActPdpCntxtRejCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */
    tempMsg = pMsg;                                                             /* ָ��������Ϣ                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        if(SM_RETURN_NG == SM_ComSaveTICheck(SM_ACT_PDP_CONTEXT_REJ
            ,&tempMsg, &ulSum, pMsgIE))
        {                                                                       /* ���ú����洢Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* �ͷ�������ڴ�                           */
            return SM_NULL;                                                     /* ����SM_NULL                              */
        }
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActPdpCntxtRejCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* ����IE"��Ϣ����",����ָ��ƫ��,��������1  */
    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        pMsgIE->SmCause = *(tempMsg);                                           /* �洢SM cause                             */
        tempMsg++;                                                              /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum++;                                                                /* ��������1                                */
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActPdpCntxtRejCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        (VOS_VOID)SM_ComOptionalCheck(tempMsg, ulSmPduLen, &ulSum, pMsgIE);               /* ���ú����洢Option��IE                   */
    }

    return pMsgIE;                                                              /* ���ش洢�Ľṹ��ָ��                     */
}

/*******************************************************************************
  Module:      SM_ComReqPdpCntxtActMsgCheck
  Function:    ���洢���෢��MS��REQUEST PDP CONTEXT ACTIVATION��Ϣ�Ĵ���
  Input:       VOS_UINT8   *pMsg                      ������Ϣ
               VOS_UINT32   ulSmPduLen                 ������Ϣ����
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  ��־��      2003.12.08   �¹�����
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComReqPdpCntxtActMsgCheck(
                                                     VOS_UINT8   *pMsg,             /* ������Ϣ                                 */
                                                     VOS_UINT32   ulSmPduLen         /* ������Ϣ����                             */
                                                )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* ����ָ��                                 */
    VOS_UINT8                              *tempMsg;                                /* ����ֲ�ָ��                             */
    VOS_UINT32                              ulSum;                                   /* ���������                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* �����ڴ�                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComReqPdpCntxtActMsgCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */
    tempMsg = pMsg;                                                             /* ָ��������Ϣ                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        if(SM_RETURN_NG == SM_ComSaveTICheck(SM_REQ_PDP_CONTEXT_ACT,
            &tempMsg, &ulSum, pMsgIE))
        {                                                                       /* ���ú����洢Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* �ͷ�������ڴ�                           */
            return SM_NULL;                                                     /* ����SM_NULL                              */
        }
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComReqPdpCntxtActMsgCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* ����IE"С������",����ָ��ƫ��,��������1  */
    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        if( 0x02 == *tempMsg )
        {                                                                       /* ����Ϊ0                                  */
            pMsgIE->PdpAddr.ucLen = 2;                                          /* ���ȸ�ֵ                                 */
            pMsgIE->PdpAddr.pValue= tempMsg + 1;                                /* �洢PDP address��ָ��                    */
            tempMsg += 3;                                                       /* ����ָ��ƫ�Ƶĳ���                       */
            ulSum += 3;                                                         /* ���¼�����                               */
        }
        else
        {
            pMsgIE->PdpAddr.ucLen = *tempMsg;                                   /* �洢Offered PDP address�ĳ���            */
            pMsgIE->PdpAddr.pValue= tempMsg + 1;                                /* �洢Offered PDP address��ָ��            */
            tempMsg += pMsgIE->PdpAddr.ucLen + 1;                               /* ����ָ��ƫ�Ƶĳ���                       */
            ulSum += pMsgIE->PdpAddr.ucLen + 1;                                 /* ���¼���������                           */
        }
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComReqPdpCntxtActMsgCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        (VOS_VOID)SM_ComOptionalCheck(tempMsg, ulSmPduLen, &ulSum, pMsgIE);               /* ���ú����洢Option��IE                   */
    }
    else if( ulSum > ulSmPduLen )
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComReqPdpCntxtActMsgCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    else
    {
    }

    return pMsgIE;                                                              /* ���ش洢�Ľṹ��ָ��                     */
}

/*******************************************************************************
  Module:      SM_ComModifyPdpCntxtAccCheck
  Function:    ���洢���෢��MS��MODIFY PDP CONTEXT ACCEPT��Ϣ�Ĵ���
  Input:       VOS_UINT8   *pMsg                      ������Ϣ
               VOS_UINT32   ulSmPduLen                 ������Ϣ����
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  ��־��      2003.12.08   �¹�����
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComModifyPdpCntxtAccCheck(
                                                     VOS_UINT8   *pMsg,             /* ������Ϣ                                 */
                                                     VOS_UINT32   ulSmPduLen         /* ������Ϣ����                             */
                                               )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* ����ָ��                                 */
    VOS_UINT8                              *tempMsg;                                /* ����ֲ�ָ��                             */
    VOS_UINT32                              ulSum;                                   /* ���������                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* �����ڴ�                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComModifyPdpCntxtAccCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */
    tempMsg = pMsg;                                                             /* ָ��������Ϣ                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        if(SM_RETURN_NG
            == SM_ComSaveTICheck(SM_MOD_PDP_CONTEXT_ACC_N2M,&tempMsg, &ulSum,
            pMsgIE))
        {                                                                       /* ���ú����洢Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* �ͷ�������ڴ�                           */
            return SM_NULL;                                                     /* ����SM_NULL                              */
        }
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* ����IE"��Ϣ����",����ָ��ƫ��,��������1  */
    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        (VOS_VOID)SM_ComOptionalCheck(tempMsg, ulSmPduLen, &ulSum, pMsgIE);               /* ���ú����洢Option��IE                   */
    }
    else if( ulSum > ulSmPduLen )
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    else
    {
    }

    return pMsgIE;                                                              /* ���ش洢�Ľṹ��ָ��                     */
}

/*******************************************************************************
  Module:      SM_ComModifyPdpCntxtReqCheck
  Function:    ���洢���෢��MS��MODIFY PDP CONTEXT REQUEST��Ϣ�Ĵ���
  Input:       VOS_UINT8   *pMsg                      ������Ϣ
               VOS_UINT32   ulSmPduLen                 ������Ϣ����
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  ��־��      2003.12.08   �¹�����
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComModifyPdpCntxtReqCheck(
                                                     VOS_UINT8   *pMsg,             /* ������Ϣ                                 */
                                                     VOS_UINT32   ulSmPduLen         /* ������Ϣ����                             */
                                               )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* ����ָ��                                 */
    VOS_UINT8                              *tempMsg;                                /* ����ֲ�ָ��                             */
    VOS_UINT32                              ulSum;                                   /* ���������                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* �����ڴ�                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComModifyPdpCntxtReqCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */
    tempMsg = pMsg;                                                             /* ָ��������Ϣ                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        if(SM_RETURN_NG
            == SM_ComSaveTICheck(SM_MOD_PDP_CONTEXT_REQ_N2M, &tempMsg, &ulSum,
            pMsgIE))
        {                                                                       /* ���ú����洢Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* �ͷ�������ڴ�                           */
            return SM_NULL;                                                     /* ����SM_NULL                              */
        }
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtReqCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* ����IE"��Ϣ����",����ָ��ƫ��,��������1  */
    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        pMsgIE->ucRadioPri=0x07 & (*tempMsg);                                   /* �洢Radio priority                       */
        tempMsg++;                                                              /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum++;                                                                /* ��������1                                */
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtReqCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }

    g_aucSapi[0][0] = 1;
    g_aucSapi[0][1] = 0x0F & (*tempMsg);                      /*��ȡSAPI*/

    if( (SM_SAPI_NOT_ASSIGN != g_aucSapi[0][1]) && (SM_SAPI_3 != g_aucSapi[0][1])
         && (SM_SAPI_5 != g_aucSapi[0][1]) && (SM_SAPI_9 != g_aucSapi[0][1])
         && (SM_SAPI_11 != g_aucSapi[0][1]))
    {
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtReqCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }

    ulSum += 1;
    tempMsg += 1;                                                               /* ����IE"LLC SAPI",����ָ��ƫ��,��������1  */

    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        pMsgIE->Qos.ucLen = *(tempMsg);                                         /* �洢New QoS�ĳ���                        */
        pMsgIE->Qos.pValue=(tempMsg + 1);                                       /* �洢New QoS��ָ��                        */
        tempMsg += pMsgIE->Qos.ucLen + 1;                                       /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum += pMsgIE->Qos.ucLen + 1;                                         /* ���¼���������                           */
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtReqCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        if(SM_RETURN_OK != SM_ComOptionalCheck(tempMsg, ulSmPduLen, &ulSum, pMsgIE))            /* ���ú����洢Option��IE                   */
        {
            SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
            SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtReqCheck:WARNING:Unknown IE encoded as comprehension required!");
            return SM_NULL;                                                         /* ����SM_NULL                              */
        }
    }
    else if( ulSum > ulSmPduLen )
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtReqCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    else
    {
    }

    return pMsgIE;                                                              /* ���ش洢�Ľṹ��ָ��                     */
}

/*******************************************************************************
  Module:      SM_ComActSecPdpCntxtAccCheck
  Function:    ���洢���෢��MS��ACTIVATE SECONDARY PDP CONTEXT ACCEPT��Ϣ
  Input:       VOS_UINT8   *pMsg                      ������Ϣ
               VOS_UINT32   ulSmPduLen                 ������Ϣ����
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  ��־��      2003.12.08   �¹�����
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComActSecPdpCntxtAccCheck(
                                                     VOS_UINT8   *pMsg,             /* ������Ϣ                                 */
                                                     VOS_UINT32   ulSmPduLen         /* ������Ϣ����                             */
                                               )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* ����ָ��                                 */
    VOS_UINT8                              *tempMsg;                                /* ����ֲ�ָ��                             */
    VOS_UINT32                              ulSum;                                   /* ���������                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* �����ڴ�                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComActSecPdpCntxtAccCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */
    tempMsg = pMsg;                                                             /* ָ��������Ϣ                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        if(SM_RETURN_NG
            == SM_ComSaveTICheck(SM_ACT_SEC_PDP_CONTEXT_ACC, &tempMsg, &ulSum,
            pMsgIE))
        {                                                                       /* ���ú����洢Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* �ͷ�������ڴ�                           */
            return SM_NULL;                                                     /* ����SM_NULL                              */
        }
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActSecPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }

    ulSum++;                                        /* ����IE"��Ϣ����"*/
    tempMsg++;                                      /* ����IE"��Ϣ����"*/

    g_aucSapi[0][0] = 1;
    g_aucSapi[0][1] = 0x0F & (*tempMsg);

    ulSum++;                                        /* ������ "SAPI"��ָ������*/
    tempMsg++;                                      /* ������ "SAPI"��ָ������*/

    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        pMsgIE->Qos.ucLen = *(tempMsg);                                         /* �洢Negotiated QoS�ĳ���                 */
        pMsgIE->Qos.pValue = (tempMsg + 1);                                     /* �洢Negotiated QoS��ָ��                 */
        tempMsg += pMsgIE->Qos.ucLen + 1;                                       /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum += pMsgIE->Qos.ucLen + 1;                                         /* ���¼���������                           */
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActSecPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        pMsgIE->ucRadioPri=0x07 & (* tempMsg);                                  /* �洢Radio priority                       */
        tempMsg++;                                                              /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum++;                                                                /* ��������1                                */
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActSecPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        (VOS_VOID)SM_ComOptionalCheck(tempMsg, ulSmPduLen, &ulSum, pMsgIE);               /* ���ú����洢Option��IE                   */
    }

    return pMsgIE;                                                              /* ���ش洢�Ľṹ��ָ��                     */
}
/*lint -e438 -e830*/
/*******************************************************************************
  Module:      SM_ComActSecPdpCntxtRejCheck
  Function:    ���洢���෢��MS��ACTIVATE SECONDARY PDP CONTEXT REJECT��Ϣ
  Input:       VOS_UINT8   *pMsg                      ������Ϣ
               VOS_UINT32   ulSmPduLen                 ������Ϣ����
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  ��־��      2003.12.08   �¹�����
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComActSecPdpCntxtRejCheck(
                                                     VOS_UINT8   *pMsg,             /* ������Ϣ                                 */
                                                     VOS_UINT32   ulSmPduLen         /* ������Ϣ����                             */
                                               )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* ����ָ��                                 */
    VOS_UINT8                              *tempMsg;                                /* ����ֲ�ָ��                             */
    VOS_UINT32                              ulSum;                                   /* ���������                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* �����ڴ�                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComActSecPdpCntxtRejCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */
    tempMsg = pMsg;                                                             /* ָ��������Ϣ                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        if(SM_RETURN_NG
            == SM_ComSaveTICheck(SM_ACT_SEC_PDP_CONTEXT_REJ, &tempMsg, &ulSum,
            pMsgIE))
        {                                                                       /* ���ú����洢Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* �ͷ�������ڴ�                           */
            return SM_NULL;                                                     /* ����SM_NULL                              */
        }
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActSecPdpCntxtRejCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* ����IE"��Ϣ����",����ָ��ƫ��,��������1  */
    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        pMsgIE->SmCause = *(tempMsg);                                           /* �洢SM cause                             */
        tempMsg++;                                                              /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum++;                                                                /* ��������1                                */
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComActSecPdpCntxtRejCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }

    return pMsgIE;                                                              /* ���ش洢�Ľṹ��ָ��                     */
}

/*******************************************************************************
  Module:      SM_ComModifyPdpCntxtRejCheck
  Function:    ���洢���෢��MS��MODIFY PDP CONTEXT REJECT��Ϣ�Ĵ���
  Input:       VOS_UINT8   *pMsg                      ������Ϣ
               VOS_UINT32   ulSmPduLen                 ������Ϣ����
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  ��־��      2003.12.08   �¹�����
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComModifyPdpCntxtRejCheck(
                                                     VOS_UINT8   *pMsg,             /* ������Ϣ                                 */
                                                     VOS_UINT32   ulSmPduLen         /* ������Ϣ����                             */
                                               )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* ����ָ��                                 */
    VOS_UINT8                              *tempMsg;                                /* ����ֲ�ָ��                             */
    VOS_UINT32                              ulSum;                                   /* ���������                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* �����ڴ�                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComModifyPdpCntxtRejCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */
    tempMsg = pMsg;                                                             /* ָ��������Ϣ                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        if(SM_RETURN_NG == SM_ComSaveTICheck(SM_MOD_PDP_CONTEXT_REJ,
            &tempMsg, &ulSum,pMsgIE))
        {                                                                       /* ���ú����洢Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* �ͷ�������ڴ�                           */
            return SM_NULL;                                                     /* ����SM_NULL                              */
        }
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtRejCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* ����IE"��Ϣ����",����ָ��ƫ��,��������1  */
    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        pMsgIE->SmCause = *(tempMsg);                                           /* �洢SM cause                             */
        tempMsg++;                                                              /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum++;                                                                /* ��������1                                */
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_SndStatusMsg(pMsgIE->ucTi, TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE);   /* cause:Invalid mandatory information      */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComModifyPdpCntxtRejCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }

    return pMsgIE;                                                              /* ���ش洢�Ľṹ��ָ��                     */
}

/*******************************************************************************
  Module:      SM_ComDeActPdpCntxtReqCheck
  Function:    ���洢���෢��MS��DEACTIVATE PDP CONTEXT REQUEST��Ϣ�Ĵ���
  Input:       VOS_UINT8   *pMsg                      ������Ϣ
               VOS_UINT32   ulSmPduLen                 ������Ϣ����
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  ��־��      2003.12.08   �¹�����
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComDeActPdpCntxtReqCheck(
                                                     VOS_UINT8   *pMsg,             /* ������Ϣ                                 */
                                                     VOS_UINT32   ulSmPduLen         /* ������Ϣ����                             */
                                              )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* ����ָ��                                 */
    VOS_UINT8                              *tempMsg;                                /* ����ֲ�ָ��                             */
    VOS_UINT32                              ulSum;                                   /* ���������                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* �����ڴ�                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComDeActPdpCntxtReqCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */
    tempMsg = pMsg;                                                             /* ָ��������Ϣ                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        if(SM_RETURN_NG
            == SM_ComSaveTICheck(SM_DEACT_PDP_CONTEXT_REQ,&tempMsg, &ulSum,
            pMsgIE))
        {                                                                       /* ���ú����洢Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* �ͷ�������ڴ�                           */
            return SM_NULL;                                                     /* ����SM_NULL                              */
        }
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComDeActPdpCntxtReqCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* ����IE"��Ϣ����",����ָ��ƫ��,��������1  */
    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        pMsgIE->SmCause = *(tempMsg);                                           /* �洢SM cause                             */
        tempMsg++;                                                              /* ����ָ��ƫ�Ƶĳ���                       */
        ulSum++;                                                                /* ��������1                                */
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComDeActPdpCntxtReqCheck:WARNING:NW->SM Invalid mandatory information!");
        pMsgIE->SmCause = TAF_SM_REJ_CAUSE_INVALID_MANDATORY_IE;
    }
    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        (VOS_VOID)SM_ComOptionalCheck(tempMsg, ulSmPduLen, &ulSum, pMsgIE);               /* ���ú����洢Option��IE                   */
    }

    return pMsgIE;                                                              /* ���ش洢�Ľṹ��ָ��                     */
}

/*******************************************************************************
  Module:      SM_ComDeActPdpCntxtAccCheck
  Function:    ���洢���෢��MS��DEACTIVATE PDP CONTEXT ACCEPT��Ϣ�Ĵ���
  Input:       VOS_UINT8   *pMsg                      ������Ϣ
               VOS_UINT32   ulSmPduLen                 ������Ϣ����
  Output:      VOS_VOID
  NOTE:
  Return:      SM_NW_MSG_STRU    *pMsgIE
  History:
      1.  ��־��      2003.12.08   �¹�����
*******************************************************************************/
SM_NW_MSG_STRU    *SM_ComDeActPdpCntxtAccCheck(
                                                     VOS_UINT8   *pMsg,             /* ������Ϣ                                 */
                                                     VOS_UINT32   ulSmPduLen         /* ������Ϣ����                             */
                                              )
{
    SM_NW_MSG_STRU                     *pMsgIE;                                 /* ����ָ��                                 */
    VOS_UINT8                              *tempMsg;                                /* ����ֲ�ָ��                             */
    VOS_UINT32                              ulSum;                                   /* ���������                               */

    pMsgIE = (SM_NW_MSG_STRU *)SM_Malloc(sizeof(SM_NW_MSG_STRU));               /* �����ڴ�                                 */
    if ( VOS_NULL_PTR == pMsgIE )
    {
        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "SM_ComDeActPdpCntxtAccCheck:ERROR:Alloc memory fail!" );
        return SM_NULL;
    }

    SM_MemSet(pMsgIE, 0, sizeof(SM_NW_MSG_STRU));
    ulSum = 0;                                                                  /* ��������ʼֵ��0                          */
    tempMsg = pMsg;                                                             /* ָ��������Ϣ                             */

    if( ulSum < ulSmPduLen )
    {                                                                           /* ������С����Ϣ����                       */
        if(SM_RETURN_NG
            == SM_ComSaveTICheck(SM_DEACT_PDP_CONTEXT_ACC,&tempMsg, &ulSum,
            pMsgIE))
        {                                                                       /* ���ú����洢Transaction identifier       */
            SM_Free(pMsgIE);                                                    /* �ͷ�������ڴ�                           */
            return SM_NULL;                                                     /* ����SM_NULL                              */
        }
    }
    else
    {                                                                           /* ��Ϣ���ȴ���                             */
        SM_Free(pMsgIE);                                                        /* �ͷ�������ڴ�                           */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ComDeActPdpCntxtAccCheck:WARNING:NW->SM Invalid mandatory information!");
        return SM_NULL;                                                         /* ����SM_NULL                              */
    }
    ulSum += 1;
    tempMsg += 1;                                                               /* ����IE"��Ϣ����",����ָ��ƫ��,��������1  */

    return pMsgIE;                                                              /* ���ش洢�Ľṹ��ָ��                     */
}
/*lint +e438 +e830*/


VOS_UINT32 NAS_SM_ComMsgCheck(
    VOS_UINT8                           ucMsgType,
    VOS_UINT32                          ulPduLen,
    VOS_UINT8                           *pucMsg,
    SM_NW_MSG_STRU                      **ppstMsgIe
)
{
    VOS_UINT32                           ucStatus;

    ucStatus    = VOS_FALSE;
    *ppstMsgIe  = VOS_NULL_PTR;

    switch( ucMsgType )
    {
        case SM_REQ_PDP_CONTEXT_ACT:
            *ppstMsgIe = SM_ComReqPdpCntxtActMsgCheck(pucMsg, ulPduLen);
            break;

        case SM_ACT_PDP_CONTEXT_ACC:
            *ppstMsgIe = SM_ComActPdpCntxtAccCheck(pucMsg, ulPduLen);
            break;

        case SM_ACT_PDP_CONTEXT_REJ:
            *ppstMsgIe = SM_ComActPdpCntxtRejCheck(pucMsg, ulPduLen);
            break;

        case SM_ACT_SEC_PDP_CONTEXT_ACC:
            *ppstMsgIe = SM_ComActSecPdpCntxtAccCheck(pucMsg, ulPduLen);
            break;

        case SM_ACT_SEC_PDP_CONTEXT_REJ:
            *ppstMsgIe = SM_ComActSecPdpCntxtRejCheck(pucMsg, ulPduLen);
            break;

        case SM_MOD_PDP_CONTEXT_REQ_N2M:
            *ppstMsgIe = SM_ComModifyPdpCntxtReqCheck(pucMsg, ulPduLen);
            break;

        case SM_MOD_PDP_CONTEXT_ACC_N2M:
            *ppstMsgIe = SM_ComModifyPdpCntxtAccCheck(pucMsg, ulPduLen);
            break;

        case SM_MOD_PDP_CONTEXT_REJ:
            *ppstMsgIe = SM_ComModifyPdpCntxtRejCheck(pucMsg, ulPduLen);
            break;

        case SM_DEACT_PDP_CONTEXT_REQ:
            *ppstMsgIe = SM_ComDeActPdpCntxtReqCheck(pucMsg, ulPduLen);
            break;

        case SM_DEACT_PDP_CONTEXT_ACC:
            *ppstMsgIe = SM_ComDeActPdpCntxtAccCheck(pucMsg, ulPduLen);
            break;

        case SM_STATUS:
        default:
            /* SM_STATUS��Ϣ������������Ϣ����Ҫ��飬ֱ���ü��״̬ΪVOS_TRUE */
            ucStatus = VOS_TRUE;
            break;
    }

    if (VOS_NULL_PTR != *ppstMsgIe)
    {
        ucStatus = VOS_TRUE;
    }

    return ucStatus;
}
VOS_UINT32 NAS_SM_ValidNasMsg(
    GMMSM_DATA_IND_STRU                 *pRcvMsg,
    VOS_UINT8                           *pucMsgType,
    VOS_UINT8                           *pucTi
)
{
    GMMSM_DATA_IND_STRU                 *pGmmDataInd;

    pGmmDataInd = ( GMMSM_DATA_IND_STRU*) pRcvMsg;

    /* �����Ϣ�����Ƿ���� */
    /*--------------------------------------------------------------------------
      A L3 protocol may define that bits 5 to 8 of octet 1 of a standard L3
      message of the protocol contains the transaction identifier (TI). The
      extended TI shall not be used unless TI values of 7 or greater are needed.
      Refer to section 11.2.3.1.3 in TS 24.007
    --------------------------------------------------------------------------*/
    if (((0x70 == (pGmmDataInd->SmMsg.aucNasMsg[0] & 0x70))
     && (2 == pGmmDataInd->SmMsg.ulNasMsgSize))
     || (2 > pGmmDataInd->SmMsg.ulNasMsgSize))
    {
        NAS_WARNING_LOG(WUEPS_PID_SM,
            "NAS_SM_ValidNasMsg:WARNING:NW->SM Message type non-existent or not implemented!");
        return VOS_FALSE;
    }

    if (0x70 == (pGmmDataInd->SmMsg.aucNasMsg[0] & 0x70))
    {
        /* ���TI��չ��־λ��EXT flag (bit 8 of octet 2) Ĭ��ֵΪ"1" */
        if (0x80 != (pGmmDataInd->SmMsg.aucNasMsg[1] & 0x80))
        {
            NAS_WARNING_LOG(WUEPS_PID_SM,
                "NAS_SM_ValidNasMsg:WARNING:NW->SM Invalid transaction identifier value!");
            return VOS_FALSE;
        }

        /* ��ȡ��Ϣ���ͺ�TIֵ */
        /*-------------------------------------------------------------------
          Where the extended TI is used, the TI IE includes a second octet.
          The TI value in the first octet is ignored, and the TI value is
          encoded in bits 7-1 of the second octet.
          Refer to section 11.2.3.1.3 in TS 24.007
        -------------------------------------------------------------------*/
        *pucMsgType  = pGmmDataInd->SmMsg.aucNasMsg[2];
        *pucTi       = (pGmmDataInd->SmMsg.aucNasMsg[1] & 0x7F)
                     | (pGmmDataInd->SmMsg.aucNasMsg[0] & 0x80);

        /* ��¼TI����չ��־ */
        g_ucTiExt   = VOS_TRUE;
    }
    else
    {
        /* ��ȡ��Ϣ���ͺ�TIֵ */
        *pucMsgType  = pGmmDataInd->SmMsg.aucNasMsg[1];
        *pucTi       = (pGmmDataInd->SmMsg.aucNasMsg[0] & 0xF0) >> 4;
        *pucTi       = ((*pucTi & 0x08) << 4) | (*pucTi & 0x07);
    }

    return VOS_TRUE;
}


VOS_VOID NAS_SM_RcvGmmSmDataInd(
    GMMSM_DATA_IND_STRU                 *pstRcvMsg
)
{
    VOS_UINT8                           ucMsgType;
    VOS_UINT8                           ucTi;
    VOS_UINT32                          ucStatus;
    GMMSM_DATA_IND_STRU                 *pstGmmDataInd;
    SM_NW_MSG_STRU                      *pstMsgIe;

    pstGmmDataInd = (GMMSM_DATA_IND_STRU*)pstRcvMsg;
    pstMsgIe      = VOS_NULL_PTR;

    /* ���L3��Ϣ������ȡSM��Ϣ���ͺ�TI */
    ucStatus = NAS_SM_ValidNasMsg(pstGmmDataInd, &ucMsgType, &ucTi);
    if (VOS_FALSE == ucStatus)
    {
        NAS_WARNING_LOG(WUEPS_PID_SM,
            "NAS_SM_RcvGmmSmDataInd:WARNING: Invalid message type or transaction identifier!");
        return;
    }

    /*Report DL message*/
    SM_ReportN2MOtaMsg(ucMsgType, &(pstGmmDataInd->SmMsg));


    /* ���洢���෢��MS����Ϣ */
    ucStatus = NAS_SM_ComMsgCheck(ucMsgType,
                            pstGmmDataInd->SmMsg.ulNasMsgSize,
                            pstGmmDataInd->SmMsg.aucNasMsg,
                            &pstMsgIe);
    if (VOS_TRUE == ucStatus)
    {
        switch( ucMsgType )
        {
            case SM_REQ_PDP_CONTEXT_ACT:
                SM_RcvNwReqPdpCntxtActMsg(pstMsgIe);
                break;

            case SM_ACT_PDP_CONTEXT_ACC:
                SM_RcvNwActPdpCntxtAccMsg(pstMsgIe);
                break;

            case SM_ACT_PDP_CONTEXT_REJ:
                SM_RcvNwActPdpCntxtRejMsg(pstMsgIe);
                break;

            case SM_ACT_SEC_PDP_CONTEXT_ACC:
                SM_RcvNwActSecPdpCntxtAccMsg(pstMsgIe);
                break;

            case SM_ACT_SEC_PDP_CONTEXT_REJ:
                SM_RcvNwActSecPdpCntxtRejMsg(pstMsgIe);
                break;

            case SM_MOD_PDP_CONTEXT_REQ_N2M:
                SM_RcvNwModifyPdpCntxtReqMsg(pstMsgIe);
                break;

            case SM_MOD_PDP_CONTEXT_ACC_N2M:
                SM_RcvNwModifyPdpCntxtAccMsg(pstMsgIe);
                break;

            case SM_MOD_PDP_CONTEXT_REJ:
                SM_RcvNwModifyPdpCntxtRejMsg(pstMsgIe);
                break;

            case SM_DEACT_PDP_CONTEXT_REQ:
                SM_RcvNwDeActPdpCntxtReqMsg(pstMsgIe);
                break;

            case SM_DEACT_PDP_CONTEXT_ACC:
                SM_RcvNwDeActPdpCntxtAccMsg(pstMsgIe);
                break;

            case SM_STATUS:
                SM_RcvStatusMsg(pstGmmDataInd);
                break;

            default:
                /* cause: "message type non-existent" */
                SM_SndStatusMsg(ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_EXIT);
                NAS_WARNING_LOG(WUEPS_PID_SM,
                    "NAS_SM_RcvGmmSmDataInd:WARNING: NW->SM Message type non-existent or not implemented!");
                break;
        }
    }
}
VOS_VOID SM_RcvGmmSmEstabishCnf(
    GMMSM_ESTABLISH_CNF_STRU           *pRcvMsg                                 /* ���յ�����Ϣ                             */
)
{
    VOS_UINT8                           i;
    MSG_HEADER_STRU                    *pHoldMsg;
    GMMSM_DATA_REQ_STRU                *ptemp = SM_NULL;                        /* ��ʱ��Ϣָ��                             */
    VOS_UINT32                          ulTimerLen = 0;
    VOS_UINT8                           ucTimerType = 0;
    VOS_UINT8                           ucExpireTimes;
    VOS_UINT8                           ucAddrIndex;

    SM_TimerStop(SM_REGISTER_TIMER_ID);                                         /* ֹͣע�ᱣ��Timer                        */
    if( GMM_SM_EST_SUCCESS == pRcvMsg->ulEstResult )
    {                                                                           /* ע��ɹ�                                 */
        g_SmEntity.ucRegisterFlg = SM_PS_REGISTERED;                            /* �趨ע���־Ϊ�Ѿ�ע��                   */
        for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
        {
            if( SM_NULL != g_SmEntity.aHoldMsg[i].pHoldRcvMsg )
            {                                                                   /* ���ڻ�����Ϣ                             */
                pHoldMsg = (MSG_HEADER_STRU *)g_SmEntity.aHoldMsg[i].pHoldRcvMsg;
                switch( pHoldMsg->ulMsgName )
                {                                                               /* ��Ϣ����                                 */
                case ID_SMREG_PDP_ACTIVATE_REQ:
                    NAS_SM_ProcTafPdpActiveReq((SMREG_PDP_ACTIVATE_REQ_STRU *)pHoldMsg);
                    break;
                case ID_SMREG_PDP_DEACTIVATE_REQ:
                    NAS_SM_ProcTafPdpDeActiveReq((SMREG_PDP_DEACTIVATE_REQ_STRU *)pHoldMsg);
                    break;
                default:
                    PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvGmmSmEstabishCnf:WARNING:SM: Message type non-existent!");
                   break;
                }

                SM_Free(g_SmEntity.aHoldMsg[i].pHoldRcvMsg);                    /* �ͷű�����Ϣ                             */
                g_SmEntity.aHoldMsg[i].pHoldRcvMsg = SM_NULL;                   /* ���������Ϣ��                           */
            }
            else if (SM_NULL != g_SmEntity.aPdpCntxtList[i].pHoldSndMsg)
            {
                ptemp = (GMMSM_DATA_REQ_STRU *)g_SmEntity.aPdpCntxtList[i].pHoldSndMsg;
                if ( SM_ACT_PDP_CONTEXT_REQ == *( (ptemp->SmMsg.aucNasMsg) + sizeof(VOS_UINT8)) )
                {
                    /* ������ڻ����SM_ACT_PDP_CONTEXT_REQ��Ϣ�����ʾ֮ǰ�����˼���������յ�GMMȥע����Ϣ��
                       ��ʱģ���յ�GMMSM_REL_IND��Ϣ���д���*/
                    if (SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[i].ucState)
                    {
                        SM_T3380Expire(i);
                        ucTimerType = SM_TIMER_TYPE_T3380;
                        ulTimerLen  = SM_T3380_LENGTH;
                        /* ����ʱ�������ڿ���״̬������Ҫ�����������Ա����¼�ʱ */
                        if (SM_TIMER_STA_ON == g_SmEntity.aPdpCntxtList[i].TimerInfo.ucTimerStaFlg)
                        {
                            /* ����ucExpireTimes,����ucExpireTimes�Ѿ��ڳ�ʱ���������ۼ��ˣ�����ֻ���漴�ɣ������ۼ� */
                            ucExpireTimes = g_SmEntity.aPdpCntxtList[i].TimerInfo.ucExpireTimes;

                            /* ֹͣ��������Ӧ��ʱ�� */
                            SM_TimerStop(i);
                            SM_TimerStart(i, ulTimerLen, ucTimerType);

                            /* �ָ�ucExpireTimes */
                            g_SmEntity.aPdpCntxtList[i].TimerInfo.ucExpireTimes = ucExpireTimes;
                        }
                    }
                }
            }
            else
            {
                break;
            }
        }
    }
    else
    {                                                                           /* ע��ʧ��                                 */
        NAS_MNTN_RecordPdpActiveFail(NAS_MNTN_ACTIVE_FAIL_TYPE_PS_SERVICE_UNAVAILABLE,
                                     0,                                         /* �˴����ܲ���Ψһ����һ��PDP�����ģ�����ֵ��Ч */
                                     NAS_MNTN_SM_REJ_CAUSE_INVALID,
                                     g_SmEntity.ucRegisterFlg);

        g_SmEntity.ucRegisterFlg = SM_PS_NOTREGISTER;                           /* �趨ע���־Ϊû��ע��                   */
        for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
        {
            if( SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[i].ucState )
            {
                ucAddrIndex = g_SmEntity.aPdpCntxtList[i].ucAddrIndex;
                SM_ComClearPdpCntxt(i);
                SM_SndTafSmPdpActivateRej(
                    g_SmEntity.aPdpCntxtList[i].ucCr,
                    NAS_SM_MapGmmCause(pRcvMsg->enCause),
                    VOS_NULL_PTR);

                SM_SndRabmSmDeactivateInd(1,&i);
                SM_ComClearPdpAddrApn(ucAddrIndex);
                g_SmEntity.aPdpCntxtList[i].ucState = SM_PDP_INACTIVE;
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucCr] = 0xFF;
                g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucTi] = 0xFF;
            }
            else if( SM_NULL != g_SmEntity.aHoldMsg[i].pHoldRcvMsg )
            {                                                                   /* ���ڻ�����Ϣ                             */
                pHoldMsg = (MSG_HEADER_STRU *)g_SmEntity.aHoldMsg[i].pHoldRcvMsg;
                switch( pHoldMsg->ulMsgName )
                {                                                               /* ��Ϣ����                                 */
                case ID_SMREG_PDP_ACTIVATE_REQ:
                    SM_SndTafSmPdpActivateRej(
                        ((SMREG_PDP_ACTIVATE_REQ_STRU *)pHoldMsg)->ucConnectId,
                        NAS_SM_MapGmmCause(pRcvMsg->enCause),
                        VOS_NULL_PTR);                                          /* �ؾܾ���Ϣ                               */
                    break;
                case ID_SMREG_PDP_DEACTIVATE_REQ:
                    SM_SndTafSmPdpDeActInd (
                        ((SMREG_PDP_DEACTIVATE_REQ_STRU *)pHoldMsg)->ucConnectId,
                        NAS_SM_MapGmmCause(pRcvMsg->enCause),
                        SM_FALSE);                                              /* �ؾܾ���Ϣ                               */
                    break;
                default:
                    break;
                }

                SM_ComClearPdpCntxt(i);                                         /* �������PDPʵ��Ĵ���                    */
                SM_Free(g_SmEntity.aHoldMsg[i].pHoldRcvMsg);                    /* �ͷű�����Ϣ                             */
                g_SmEntity.aHoldMsg[i].pHoldRcvMsg = SM_NULL;                   /* ���������Ϣ                             */
            }
            else
            {

            }
        }

        NAS_SM_EndSession();

    }

    return;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID NAS_SM_ProcGmmLteMoDetachInd(VOS_VOID)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo = VOS_NULL_PTR;
    VOS_UINT8                           i;

    if (SM_PS_REGISTERED == NAS_SM_GET_REGISTER_FLG())
    {
        NAS_SM_SET_REGISTER_FLG(SM_PS_NOTREGISTER);

        for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
        {
            pstPdpCtxInfo = NAS_SM_GetPdpCtxInfoAddr(i);
            if (SM_PDP_ACTIVE_PENDING == pstPdpCtxInfo->ucState)
            {
                /* ֪ͨTAFģ��PDP����ʧ�� */
                SM_SndTafSmPdpActivateRej(pstPdpCtxInfo->ucCr,
                                          SM_TAF_CAUSE_GMM_PS_DETACH,
                                          VOS_NULL_PTR);

                /* SMʵ��״̬��ΪINACTIVE */
                pstPdpCtxInfo->ucState = SM_PDP_INACTIVE;

                /* ���TI, CR��NSAPI��ӳ�� */
                NAS_SM_ClearNsapiToTiMap(pstPdpCtxInfo->ucTi);
                NAS_SM_ClearNsapiToCrMap(pstPdpCtxInfo->ucCr);

                /* �����Ӧ��PDPʵ����Ϣ */
                SM_ComClearPdpCntxt(i);
                SM_ComDelNsapiFromAddr(pstPdpCtxInfo->ucAddrIndex, i);

                /* ֪ͨRABM���³���״̬ */
                SM_SndRabmSmDeactivateInd(1,&i);

                /* ֪ͨGMM����PDP״̬ */
                NAS_SM_SndGmmPdpStatusInd();
            }
        }

        NAS_SM_EndSession();
    }
    else
    {
       ;
    }

    return;
}
#endif


VOS_VOID SM_RcvGmmSmStatusInd(GMMSM_STATUS_IND_STRU *pRcvMsg)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucNsapiNum;
    VOS_UINT8                           aucNspaiList[SM_MAX_NSAPI_NUM];
    VOS_UINT8                           ucActPending;                           /* �յ�ȥע����Ϣʱ��ʹ�øñ������洦��SM_PDP_ACTIVE_PENDING״̬��PDP�ĸ��� */
    VOS_UINT8                           ucAddrIndex;

    ucNsapiNum = 0;
    ucActPending = 0;

#if (FEATURE_ON == FEATURE_LTE)
    if ( (GMM_SM_STATUS_DETACHED == pRcvMsg->ulGmmStatus )
      && (GMM_SM_CAUSE_LTE_MO_DETACH == pRcvMsg->enCause) )
    {
        NAS_SM_ProcGmmLteMoDetachInd();
        return;
    }
#endif

    if ( (GMM_SM_STATUS_DETACHED == pRcvMsg->ulGmmStatus )
      || (GMM_SM_SER_REJ_CAUSE_PDP_NOEXIT == pRcvMsg->ulGmmStatus) )
    {                                                                           /* ״̬Ϊdetached                           */
        SM_TimerStop(SM_REGISTER_TIMER_ID);                                     /* ֹͣע�ᱣ��Timer                        */

        if (GMM_SM_STATUS_DETACHED == pRcvMsg->ulGmmStatus)
        {
            g_SmEntity.ucRegisterFlg = SM_PS_NOTREGISTER;                       /* �趨ע���־Ϊû��ע��                   */
        }
        else
        {
            g_SmEntity.ucRegisterFlg = SM_PS_REGISTERED;                        /* �趨ע���־Ϊû��ע��                   */
        }

        g_SmPdpAddrApn.usPdpAddrFlg = 0;                                        /* ���usPdpAddrFlg                         */
        SM_MemSet(g_TiMapToNsapi, (VOS_CHAR)0xff, 256);                                   /* ��ʼ��g_TiMapToNsapi[]                   */
        SM_MemSet(g_CrMapToNsapi, (VOS_CHAR)0xff, 256);                                   /* ��ʼ��g_CrMapToNsapi[]                   */

        for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
        {
            if (SM_PDP_INACTIVE != g_SmEntity.aPdpCntxtList[i].ucState)
            {                                                                   /* ��ǰ��״̬ΪSM_PDP_INACTIVE              */
                if ( (SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[i].ucState)
                  && (GMM_SM_STATUS_DETACHED == pRcvMsg->ulGmmStatus) )
                {
                    ucActPending++;
                    ucAddrIndex = g_SmEntity.aPdpCntxtList[i].ucAddrIndex;

                    /*��forѭ��֮ǰ�Ѿ�������ȫ�ֱ���ͳһ����һ�Σ��ڸ÷�֧���軹ԭ��Щȫ�ֱ�����ֵ*/
                    g_SmPdpAddrApn.usPdpAddrFlg |= (VOS_UINT16)((VOS_UINT32)0x0001<<ucAddrIndex);
                    g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucTi] = i;
                    g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucCr] = i;
                }
                else
                {
                    SM_TimerStop(i);
                    SM_SndTafSmPdpDeActInd(
                        g_SmEntity.aPdpCntxtList[i].ucCr,
                        NAS_SM_MapGmmCause(pRcvMsg->enCause),
                        SM_FALSE);                                                  /* ��TAF����ȥ��������                      */
                    aucNspaiList[ucNsapiNum] = i;                                   /* ��¼ȥ�����NSAPI                        */
                    ucNsapiNum++;                                                   /* ȥ����NSAPI������1                       */

                    SM_ComClearPdpCntxt(i);                                         /* �������PDPʵ��Ĵ���                    */

                    SM_ComDelNsapiFromAddr(g_SmEntity.aPdpCntxtList[i].ucAddrIndex, i);

                    g_SmEntity.aPdpCntxtList[i].ucState = SM_PDP_INACTIVE;          /* ״̬�л���SM_PDP_INACTIVE                */

                    PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvGmmSmStatusInd:NORMAL:SM state = SM_PDP_INACTIVE");

                    NAS_SM_SndGmmPdpStatusInd();
                }
            }

            if (SM_NULL != g_SmEntity.aHoldMsg[i].pHoldRcvMsg)
            {
                SM_Free(g_SmEntity.aHoldMsg[i].pHoldRcvMsg);
                g_SmEntity.aHoldMsg[i].pHoldRcvMsg = SM_NULL;
            }
        }
        if (ucNsapiNum > 0)
        {
            SM_SndRabmSmDeactivateInd (ucNsapiNum, aucNspaiList);               /* ֪ͨRABMȥ��������Nsapi                  */
        }

        if (ucActPending > 0)
        {
            NAS_SM_SndGmmEstablishReq();                                            /* ��ע������                               */
            SM_TimerStart(SM_REGISTER_TIMER_ID,SM_T0001_LENGTH
                ,SM_TIMER_TYPE_T0001);                                          /* ����ע�ᱣ��Timer                        */
            g_SmEntity.ucRegisterFlg = SM_PS_REGISTERING;
        }
        else
        {
            if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg )
            {
                NAS_SM_SndGmmPdpDeactivatedInd();                                   /* ��GMM����GMMSM_PDP_DEACTIVATED_IND��Ϣ�����浱ǰPDP״̬ */
            }
        }

        NAS_SM_EndSession();

    }
    else
    {
        g_SmEntity.ucRegisterFlg = SM_PS_REGISTERED;                            /* �趨ע���־Ϊ�Ѿ�ע��                   */

        SM_TimerStop(SM_REGISTER_TIMER_ID);
    }
    return;
}



VOS_VOID SM_RcvGmmSmServiceRej(GMMSM_SERVICE_REJ_STRU  *pRcvMsg)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucPdpUpdateFlg;

    ucPdpUpdateFlg = VOS_FALSE;

    for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
    {
        if(SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[i].ucState)
        {                                                                       /* ��ǰ��״̬ΪSM_PDP_ACTIVE_PENDING */
            ucAddrIndex = g_SmEntity.aPdpCntxtList[i].ucAddrIndex;

            SM_SndTafSmPdpActivateRej(
                g_SmEntity.aPdpCntxtList[i].ucCr,
                NAS_SM_MapGmmCause(pRcvMsg->enCause),
                VOS_NULL_PTR);

            SM_ComClearPdpCntxt(i);                                             /* �������PDPʵ��Ĵ��� */
            SM_SndRabmSmDeactivateInd(1, &i);
            ucPdpUpdateFlg = VOS_TRUE;
            SM_ComClearPdpAddrApn(ucAddrIndex);                                 /* ���Addr Apnʵ��                         */
            g_SmEntity.aPdpCntxtList[i].ucState = SM_PDP_INACTIVE;              /* ״̬�л���SM_PDP_INACTIVE */
            g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucCr]=0xff;              /* ά��g_CrMapToNsapi */
            g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucTi]=0xff;              /* ά��g_TiMapToNsapi */
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvGmmSmServiceRej:NORMAL:SM state = SM_PDP_INACTIVE");
        }
        else if(SM_PDP_MODIFY_PENDING == g_SmEntity.aPdpCntxtList[i].ucState)
        {
            /* �ͷű��ݵ���Ϣ */
            SM_Free(g_SmEntity.aPdpCntxtList[i].pHoldSndMsg);
            g_SmEntity.aPdpCntxtList[i].pHoldSndMsg = SM_NULL;

            /* ֹͣ��ʵ���TIMER */
            SM_TimerStop(i);

            /* ��TAF�ؾܾ���Ϣ */
            SM_SndTafSmPdpModifyRej(
                NAS_SM_MapGmmCause(pRcvMsg->enCause),
                g_SmEntity.aPdpCntxtList[i].ucCr);

            /* ״̬�л���SM_PDP_ACTIVE */
            g_SmEntity.aPdpCntxtList[i].ucState = SM_PDP_ACTIVE;
        }
        else
        {
            ;
        }
    }

    if ((VOS_TRUE == ucPdpUpdateFlg) && (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg))
    {
        NAS_SM_SndGmmPdpDeactivatedInd();                                       /* ��GMM����GMMSM_PDP_DEACTIVATED_IND��Ϣ�����浱ǰPDP״̬ */
    }

    NAS_SM_EndSession();


    return;
}
VOS_VOID SM_RcvGmmSysInfoInd(GMMSM_SYS_INFO_IND_STRU *pRcvMsg)
{
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucPdpStatusFlag;

    ucPdpStatusFlag = VOS_FALSE;

    switch (pRcvMsg->ucSgsnRelVer)
    {
        case GMMSM_SGSN_RELEASE98_OR_OLDER:
            if (GMMSM_SGSN_RELEASE99_ONWARDS == g_SmSgsnVersion)
            {
                for(ucCntxtIndex = 0; ucCntxtIndex < SM_MAX_NSAPI_NUM; ucCntxtIndex++)
                {
                    if (SM_PDP_INACTIVE != g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
                    {
                        if ( ( (g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi & 0x7F) >= 0x7)
                            || ( (0 == g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue[5])
                              && (0 == g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue[6]) ) )
                        {
                            /* ִ�б���ȥ������� */
                            ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;
                            if( SM_PDP_INACTIVE_PENDING
                                == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
                            {                                                                   /* ״̬ΪSM_PDP_INACTIVE_PENDING            */
                                NAS_SM_NORM_LOG("SM_RcvGmmSysInfoInd:NORMAL:SM state: SM_PDP_INACTIVE_PENDING ==> SM_PDP_INACTIVE ");
                                SM_TimerStop(ucCntxtIndex);                                     /* ֹͣT3390                                */
                                SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);    /* �ͷű��ݵ���Ϣ                           */
                                g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
                                SM_SndTafSmPdpDeActCnf(g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);          /* ��TAF����Ӧ��Ϣ                          */
                                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                                    = SM_PDP_INACTIVE;                                          /* ״̬�л���SM_PDP_INACTIVE                */
                                ucPdpStatusFlag = VOS_TRUE;
                            }
                            else
                            {
                                NAS_SM_NORM_LOG("SM_RcvGmmSysInfoInd:NORMAL: SM state = SM_PDP_INACTIVE");
                                SM_SndRabmSmDeactivateInd (1, &ucCntxtIndex);                   /* ֪ͨRABMȥ����Nsapi                      */
                                SM_SndTafSmPdpDeActInd(
                                    g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                                    SM_TAF_CAUSE_SM_SGSN_VER_PRE_R99,
                                    SM_FALSE);                                                  /* ֪ͨTAFȥ����                            */
                                SM_ComClearPdpCntxt(ucCntxtIndex);                              /* �ͷ�ʵ��                                 */
                                SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);               /* ��PDP Addr and Apnʵ����ɾ��Nsapi        */
                                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                                    = SM_PDP_INACTIVE;                                          /* ״̬�л���SM_PDP_INACTIVE                */

                                NAS_SM_SndGmmPdpStatusInd();
                                ucPdpStatusFlag = VOS_TRUE;
                            }
                            g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xFF;                                /* ά��g_TiMapToNsapi                       */
                            g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xFF; /* ά��g_CrMapToNsapi                       */
                        }
                    }
                }

                if ((VOS_TRUE == ucPdpStatusFlag) && (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg))
                {
                    NAS_SM_SndGmmPdpDeactivatedInd();                           /* ��GMM����GMMSM_PDP_DEACTIVATED_IND��Ϣ�����浱ǰPDP״̬ */
                }
            }

            NAS_SM_EndSession();

            /* ����SGSN�汾��Ϣ */
            g_SmSgsnVersion = GMMSM_SGSN_RELEASE98_OR_OLDER;
            break;
        case GMMSM_SGSN_RELEASE99_ONWARDS:
            /* ����SGSN�汾��Ϣ */
            g_SmSgsnVersion = GMMSM_SGSN_RELEASE99_ONWARDS;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvGmmSysInfoInd:WARNING:ucSgsnRelVer is abnormal!");
            break;
    }

    return;
}



VOS_VOID SM_RcvGmmSmPdpStatusInd(GMMSM_PDP_STATUS_IND_STRU *pRcvMsg)
{
    VOS_UINT8       i;
    VOS_UINT32      ulPdpContextStatus;
    VOS_UINT8       ucPdpStatusFlag;

    ucPdpStatusFlag = VOS_FALSE;

    for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
    {
        ulPdpContextStatus = pRcvMsg->aucPdpContextStatus[i];

        if ( 0 == ulPdpContextStatus )  /*����ָʾPDP context״̬ΪINACTIVE*/
        {
            if( (SM_PDP_INACTIVE != g_SmEntity.aPdpCntxtList[i].ucState)
                 && (SM_PDP_ACTIVE_PENDING != g_SmEntity.aPdpCntxtList[i].ucState) )
            {                                                                   /* ��ǰ��״̬����SM_PDP_INACTIVE              */
                SM_TimerStop(i);
                SM_SndTafSmPdpDeActInd(
                    g_SmEntity.aPdpCntxtList[i].ucCr,
                    NAS_SM_MapGmmCause(pRcvMsg->enCause),
                    SM_FALSE);                                                  /* ��TAF����ȥ��������                      */
                SM_ComClearPdpCntxt(i);                                         /* �������PDPʵ��Ĵ���                    */
                SM_ComDelNsapiFromAddr(g_SmEntity.aPdpCntxtList[i].ucAddrIndex, i);
                SM_SndRabmSmDeactivateInd(1,&i);
                g_SmEntity.aPdpCntxtList[i].ucState = SM_PDP_INACTIVE;          /* ״̬�л���SM_PDP_INACTIVE                */

                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvGmmSmPdpStatusInd:NORMAL:SM state = SM_PDP_INACTIVE");

                g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucTi] = 0xff;        /* ά��g_TiMapToNsapi                       */
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[i].ucCr] = 0xff;        /* ά��g_CrMapToNsapi                       */

                ucPdpStatusFlag = VOS_TRUE;
            }
        }
        else
        {
            if( SM_PDP_INACTIVE == g_SmEntity.aPdpCntxtList[i].ucState)
            {
                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                      "SM_RcvGmmSmPdpStatusInd:WARNING:SM state = SM_PDP_INACTIVE,But Network Indicate PDP STATUS = ACTIVE!!");
            }
            else if( SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[i].ucState)
            {
                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                      "SM_RcvGmmSmPdpStatusInd:WARNING:SM state = SM_PDP_ACTIVE_PENDING,But Network Indicate PDP STATUS = ACTIVE!!");
            }
            else
            {
            }
        }

    }

    if( VOS_TRUE == ucPdpStatusFlag )
    {
        NAS_SM_SndGmmPdpStatusInd();
        NAS_SM_SndGmmPdpDeactivatedInd();
    }

    NAS_SM_EndSession();

    return;
}


VOS_VOID SM_RcvGmmRelInd(GMMSM_REL_IND_STRU *pRcvMsg)
{
    VOS_UINT8           ucCntxtIndex;
    VOS_UINT32          ulTimerLen = 0;
    VOS_UINT8           ucTimerType = 0;
    VOS_UINT8           ucFlag;
    VOS_UINT8           ucExpireTimes;

    /* �յ�GMMSM_REL_IND��Ϣ����֮��ͬ�ڳ�ʱ��Ϣ������Ӧ����(ע��:��Ҫ������ʱ��)
        ���������ط���Ϣ�����ۼ�ucExpireTimes�Ļ�������������£��п��ܵ�����ѭ��:
        PDP���������͸������PS�������ӱ��ͷ� */
    for(ucCntxtIndex = 0; ucCntxtIndex < SM_MAX_NSAPI_NUM; ucCntxtIndex++)
    {
        ucFlag = VOS_FALSE;

        switch(g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
        {
            case SM_PDP_ACTIVE_PENDING:
                SM_T3380Expire(ucCntxtIndex);
                ucTimerType = SM_TIMER_TYPE_T3380;
                ulTimerLen  = SM_T3380_LENGTH;
                ucFlag = VOS_TRUE;
                break;
            case SM_PDP_MODIFY_PENDING:
                SM_T3381Expire(ucCntxtIndex);
                ucTimerType = SM_TIMER_TYPE_T3381;
                ulTimerLen  = SM_T3381_LENGTH;
                ucFlag = VOS_TRUE;
                break;
            case SM_PDP_INACTIVE_PENDING:
                SM_T3390Expire(ucCntxtIndex);
                ucTimerType = SM_TIMER_TYPE_T3390;
                ulTimerLen  = SM_T3390_LENGTH;
                ucFlag = VOS_TRUE;
                break;
            default :
                /* ����״̬�£����账�����Ϣ */
                break;
        }

        if (VOS_TRUE == ucFlag)
        {
            /* ����ʱ�������ڿ���״̬������Ҫ�����������Ա����¼�ʱ */
            if (SM_TIMER_STA_ON == g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucTimerStaFlg)
            {
                /* ����ucExpireTimes,����ucExpireTimes�Ѿ��ڳ�ʱ���������ۼ��ˣ�����ֻ���漴�ɣ������ۼ� */
                ucExpireTimes = g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes;

                /* ֹͣ��������Ӧ��ʱ�� */
                SM_TimerStop(ucCntxtIndex);
                SM_TimerStart(ucCntxtIndex, ulTimerLen, ucTimerType);

                /* �ָ�ucExpireTimes */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes = ucExpireTimes;
            }
        }
    }
}
VOS_VOID SM_RcvNwReqPdpCntxtActMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8       i;
    VOS_UINT8       ucCollisionFlg;
    VOS_UINT8       ucPdpActiveFlg;
    VOS_UINT8       ucTi;
    VOS_UINT8       ucCntxtIndex;
    VOS_UINT8       ucCntxtIndex2;
    VOS_UINT8       ucApnAddrFlg = SM_FALSE;  /*A32D00461,zzy,pclint*/                                                  /* ��ʶ�Ƿ���APN&PDP addr��ͻ               */
    VOS_UINT8       ucCollisionFlg2;                                                /* ��ʶ�Ƿ����Ѵ��ڵ�APN&PDP addr��ͬ       */
    VOS_UINT8       ucCntxtIndex3;                                                  /* ����ucCollisionFlg2ָʾ��ͻ��Ӧʵ������  */
    VOS_UINT8       ucAddrIndex;
    VOS_UINT8       ucInitType;

    ucTi                = (VOS_UINT8)(pMsgIe->ucTi & 0x7F);                         /* ȡTI��ʵ��ֵ                             */
    ucCollisionFlg      = SM_FALSE;                                             /* ��ʼ��ΪFalse                            */
    ucPdpActiveFlg      = SM_FALSE;                                             /* ��ʼ��ΪFalse                            */
    ucCntxtIndex        = SM_MAX_NSAPI_NUM;
    ucCollisionFlg2     = SM_FALSE;                                             /* ��ʼ��Ϊ��Чֵ                           */
    ucCntxtIndex2       = SM_MAX_NSAPI_NUM;                                     /* ��ʼ��Ϊ��Чֵ                           */
    ucCntxtIndex3       = SM_MAX_NSAPI_NUM;                                     /* ��ʼ��Ϊ��Чֵ                           */
    ucAddrIndex         = SM_MAX_NSAPI_NUM;                                     /* ��ʼ��Ϊ��Чֵ                           */

    ucInitType = ACTIVE_REQUEST_INIT_TYPE_MT;
    NAS_EventReport(WUEPS_PID_SM,
                    NAS_OM_EVENT_PDP_ACTIVE_REQ,
                    (VOS_VOID *)&ucInitType,
                    NAS_OM_EVENT_PDP_ACTIVE_REQ_LEN);
    if( pMsgIe->PdpAddr.ucLen > 2 )
    {                                                                           /* PDP addrΪ��̬��ַ                       */
        for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
        {
            if( SM_PDP_ACTIVE_PENDING == g_SmEntity.aPdpCntxtList[i].ucState)
            {                                                                   /* ��ǰ��״̬ΪSM_PDP_ACTIVE_PENDING        */
                if(0 == pMsgIe->Apn.ucLen)
                {
                    SM_SndReqPdpActRejMsg(SM_NULL, ucTi);                       /* �ؾܾ���Ϣ                               */
                    ucCollisionFlg = SM_TRUE;                                   /* �趨ucCollisionFlgΪTrue                 */
                    break;
                }
                ucCollisionFlg = SM_RcvNwReqPdpCnxtActMsg_S01(pMsgIe, i, ucTi);
                if(SM_TRUE == ucCollisionFlg)
                {
                    break;
                }
            }
            else if( SM_PDP_INACTIVE == g_SmEntity.aPdpCntxtList[i].ucState )
            {                                                                   /* ״̬ΪSM_PDP_INACTIVE                    */
                ucCntxtIndex = i;
                break;
            }
            else
            {                                                                   /* ״̬ΪSM_PDP_ACTIVE                      */
                if(pMsgIe->ucTi == g_SmEntity.aPdpCntxtList[i].ucTi )
                {                                                               /* ָ����Ti���ʵ���Ti��ͬ                 */
                    ucPdpActiveFlg = SM_TRUE;                                   /* ucPdpActiveFlg�趨ΪTrue                 */
                    ucCntxtIndex2 = i;                                          /* ��¼ʵ�������                           */
                }
                else
                {
                    ucCollisionFlg2
                        = SM_RcvNwReqPdpCnxtActMsg_S01(pMsgIe, i, ucTi);        /* �Ƚ�APN&PDP addr�Ƿ�����ͻ             */
                    if( SM_TRUE == ucCollisionFlg2 )
                    {                                                           /* ������ͻ                                 */
                        ucApnAddrFlg = SM_TRUE;                                 /* ucApnAddrFlg�趨Ϊ������ͻ               */
                        ucCntxtIndex3 = i;                                      /* ��¼ʵ�������                           */
                    }
                }
            }
        }
        if( SM_FALSE == ucCollisionFlg )
        {                                                                       /* û�з�����ͻ                             */
            if( (SM_TRUE == ucPdpActiveFlg) || (SM_TRUE == ucApnAddrFlg) )
            {                                                                   /* ����״̬                                 */
                if( (SM_TRUE == ucPdpActiveFlg) && (SM_TRUE == ucApnAddrFlg) && (ucCntxtIndex2 < SM_MAX_NSAPI_NUM))
                {                                                               /* Ti��ʹ����APN&PDP addr����һ��PDP
                                                                                 * context ��ͬ�����                       */
                    ucAddrIndex
                        = g_SmEntity.aPdpCntxtList[ucCntxtIndex2].ucAddrIndex;
                    SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex2);               /* ֪ͨRABMȥ����Nsapi                      */
                    SM_SndTafSmPdpDeActInd(
                                g_SmEntity.aPdpCntxtList[ucCntxtIndex2].ucCr,
                                SM_TAF_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED,
                                SM_FALSE);                                      /* ֪ͨTAFȥ����                            */
                    SM_ComClearPdpCntxt(ucCntxtIndex2);
                    SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex2);
                    g_SmEntity.aPdpCntxtList[ucCntxtIndex2].ucState
                        = SM_PDP_INACTIVE;                                      /* ״̬�л���SM_PDP_INACTIVE                */

                    PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, ":NORMAL: SM state = SM_PDP_INACTIVE");
                    g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex2].ucTi]
                         = 0xFF;
                    g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex2].ucCr]
                         = 0xFF;

                    NAS_SM_SndGmmPdpStatusInd();

                    SM_RcvNwReqPdpCnxtActMsg_S02(pMsgIe, ucCntxtIndex3);
                }
                else
                {
                    if(SM_TRUE == ucApnAddrFlg)
                    {
                        ucCntxtIndex2 = ucCntxtIndex3;
                    }
                    SM_RcvNwReqPdpCnxtActMsg_S02(pMsgIe, ucCntxtIndex2);
                }
            }
            else
            {
                if( SM_MAX_NSAPI_NUM == ucCntxtIndex )
                {                                                               /* ���û���ҵ�                             */
                    SM_SndReqPdpActRejMsg(SM_NULL,ucTi);                        /* �ؾܾ���Ϣ                               */
                }
                else
                {
                    SM_RcvNwReqPdpCnxtActMsg_S00(pMsgIe,ucCntxtIndex);          /* SM_PDP_INACTIVE״̬���մ���Ϣ�Ĵ���      */
                }
            }
        }
        else
        {   /*�ն˷����ն��Ѿ�ʹ�øò���������PDP���������ACT_PENDING״̬,
            ������������ļ���ָʾ*/
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "SM_RcvNwReqPdpCntxtActMsg Discard ACT_IND_MSG ");
        }
    }
    else
    {                                                                           /* ��̬��ַ                                 */
        if( 0xFF == g_TiMapToNsapi[pMsgIe->ucTi] )
        {                                                                       /* ״̬ΪSM_PDP_INACTIVE                    */
            for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
            {
                if( SM_PDP_INACTIVE == g_SmEntity.aPdpCntxtList[i].ucState )
                {                                                               /* ��ǰ��״̬ΪSM_PDP_ACTIVE_PENDING        */
                    SM_RcvNwReqPdpCnxtActMsg_S00(pMsgIe, i);
                    break;
                }
            }
            if( SM_MAX_NSAPI_NUM == i )
            {                                                                   /* ���û���ҵ�                             */
                SM_SndReqPdpActRejMsg(SM_NULL, ucTi);                           /* �ؾܾ���Ϣ                               */
            }
        }
        else
        {
            SM_RcvNwReqPdpCnxtActMsg_S02(pMsgIe, g_TiMapToNsapi[pMsgIe->ucTi]);
        }
    }
    SM_Free(pMsgIe);                                                            /* �ͷ��ڴ�                                 */
    return;
}


VOS_VOID SM_RcvNwActPdpCntxtAccMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucAddrIndex;
    VOS_BOOL                            bResult;

    ucCntxtIndex        = g_TiMapToNsapi[pMsgIe->ucTi];                         /* ����TI��ȡucCntxtIndex                   */
    if ( 0xFF == ucCntxtIndex )
    {                                                                           /* ״̬ΪSM_PDP_INACTIVE                    */
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE);             /* ��network��SM STATUS��Ϣ#98             */

        NAS_SM_SndGmmPdpDeactivatedInd();
    }
    else if ( SM_PDP_ACTIVE_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {
        SM_TimerStop(ucCntxtIndex);                                             /* ֹͣT3380                                */
        SM_Free( g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg );          /* �ͷű��ݵ���Ϣ                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucRadioPri = pMsgIe->ucRadioPri; /* �洢ucRadioPri                           */
        if (0 != pMsgIe->PdpAddr.ucLen)
        {                                                                       /* ����PDP addr                             */
            ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;   /* ���addr����                             */
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.ulAddrLength
                = pMsgIe->PdpAddr.ucLen;                                        /* �洢PDP addr����                         */
            SM_MemCpy(
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.aucAddrValue,
                pMsgIe->PdpAddr.pValue,
                pMsgIe->PdpAddr.ucLen);                                         /* �洢PDP addr                             */
        }

        g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength
            = (pMsgIe->Qos.ucLen <= sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue)) ?
              (pMsgIe->Qos.ucLen) : (sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue));
        PS_MEM_CPY(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                   pMsgIe->Qos.pValue,
                   g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength);     /* ����Qos                                  */
        SM_SndRabmSmActivateInd(ucCntxtIndex, RABMSM_ACT_MSG_2);                /* ֪ͨRABM����Nsapi                        */
        SM_SndTafSmPdpActivateCnf(pMsgIe, ucCntxtIndex);                        /* ��TAF����Ӧ��Ϣ                          */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;         /* ״̬�л���SM_PDP_ACTIVE                  */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwActPdpCntxtAccMsg:NORMAL: SM state: SM_PDP_ACTIVE_PENDING ==> SM_PDP_ACTIVE");
        NAS_SM_SndGmmPdpStatusInd();
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_ACTIVE_SUCC,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }
    else
    {
        /*���ݴ��ʶΪ��Ч*/
        g_aucSapi[0][0] = 0;

        /* ��network��SM STATUS��Ϣ#98 */
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE);

        if (SM_PDP_ACTIVE == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
        {
            ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;

            bResult = NAS_SM_ComparePdpAddr(&pMsgIe->PdpAddr,
                                            &g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo);
            if (VOS_FALSE == bResult)
            {
                /*----------------------------------------------------------------
                  �յ��ظ��� PDP Activate Accept ��Ϣ����ʱ����ҵ���Ѿ�ʹ�õ�һ
                  ����Ϣ�е� PDP Address����������ܻ�ʹ�ô���Ϣ�е� PDP Address��
                  PPPģ���NDISģ����PC���Э��һ����ɾͲ������ٴ�Э�̣��п���
                  ��������ҵ�񲻿��ã�Ψһ�Ľ���취�Ǳ���ȥ����� PDP
                ----------------------------------------------------------------*/
                SM_SndTafSmPdpDeActInd(
                    g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                    SM_TAF_CAUSE_SM_NW_MSG_NOT_COMPATIBLE,
                    SM_FALSE);

                /* ���PDPʵ�� */
                SM_ComClearPdpCntxt(ucCntxtIndex);
                SM_ComDelNsapiFromAddr(ucAddrIndex, ucCntxtIndex);
                SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex);
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;

                NAS_NORMAL_LOG(WUEPS_PID_SM,
                    "SM_RcvNwActPdpCntxtAccMsg:NORMAL:SM state = SM_PDP_INACTIVE");

                g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xFF;
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xFF;

                NAS_SM_SndGmmPdpStatusInd();
                NAS_SM_SndGmmPdpDeactivatedInd();
            }
        }
    }

    NAS_SM_EndSession();

    SM_Free(pMsgIe);
    return;
}
VOS_VOID SM_RcvNwActPdpCntxtRejMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8                           ucCntxtIndex;
    VOS_UINT8                           ucAddrIndex;
    SM_OCT_VARY_STRU                   *pProtCfgOpt;

    ucCntxtIndex        = g_TiMapToNsapi[pMsgIe->ucTi];                         /* ����TI��ȡucCntxtIndex                   */
    pProtCfgOpt         = SM_NULL;
    if( 0xFF == ucCntxtIndex )
    {                                                                           /* ״̬ΪSM_PDP_INACTIVE                    */
         SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_INVALID_TI);            /* ��network��SM STATUS��Ϣ#81              */
    }
    else if( SM_PDP_ACTIVE_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {
        NAS_MNTN_RecordPdpActiveFail(NAS_MNTN_ACTIVE_FAIL_TYPE_ACTIVE_REJECT,
                                     ucCntxtIndex,
                                     pMsgIe->SmCause,
                                     g_SmEntity.ucRegisterFlg);

        ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;       /* ���ucAddrIndex                          */
        SM_ComClearPdpCntxt(ucCntxtIndex);                                      /* �ͷ�ʵ��                                 */
        if( 0 != pMsgIe->ProCnfgOpt.ucLen )
        {                                                                       /* ��������                                 */
            pProtCfgOpt = (SM_OCT_VARY_STRU*)(&pMsgIe->ProCnfgOpt);
        }

        SM_SndTafSmPdpActivateRej(
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
            NAS_SM_MapSmNWCause(pMsgIe->SmCause),
            pProtCfgOpt );

        SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex);                            /* ֪ͨRABMȥ����                           */
        SM_ComClearPdpAddrApn(ucAddrIndex);                                     /* ���Addr Apnʵ��                         */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;       /* ״̬�л���SM_PDP_INACTIVE                */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwActPdpCntxtRejMsg:NORMAL:SM state: SM_PDP_ACTIVE_PENDING ==> SM_PDP_INACTIVE");
        g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xff;     /* ά��g_CrMapToNsapi                       */
        g_TiMapToNsapi[pMsgIe->ucTi] = 0xff;                                    /* ά��g_TiMapToNsapi                       */
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_ACTIVE_FAIL,
                        (VOS_VOID *)&(pMsgIe->SmCause),
                        NAS_OM_EVENT_PDP_ACTIVE_FAIL_LEN);
        if (SM_PS_REGISTERED == g_SmEntity.ucRegisterFlg)
        {
            NAS_SM_SndGmmPdpDeactivatedInd();                                   /* ��GMM����GMMSM_PDP_DEACTIVATED_IND��Ϣ�����浱ǰPDP״̬ */
        }

    }
    else
    {
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE);               /* ��network��SM STATUS��Ϣ#98              */
    }

    NAS_SM_EndSession();

    SM_Free(pMsgIe);
    return;
}
VOS_VOID SM_RcvNwActSecPdpCntxtAccMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8                           ucCntxtIndex;

    ucCntxtIndex = g_TiMapToNsapi[pMsgIe->ucTi];                                /* ����TI��ȡucCntxtIndex                   */

    if( 0xFF == ucCntxtIndex )
    {                                                                           /* ״̬ΪSM_PDP_INACTIVE                    */
         g_aucSapi[0][0] = 0;
         SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_INVALID_TI);            /* ��network��SM STATUS��Ϣ#81              */
         NAS_SM_SndGmmPdpDeactivatedInd();
    }
    else if( SM_PDP_ACTIVE_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {
        NAS_SM_NORM_LOG("SM_RcvNwActSecPdpCntxtAccMsg: SM state: SM_PDP_ACTIVE_PENDING ==> SM_PDP_ACTIVE");

        SM_TimerStop(ucCntxtIndex);                                             /* ֹͣT3380                                */
        SM_Free( g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg );          /* �ͷű��ݵ���Ϣ                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucRadioPri = pMsgIe->ucRadioPri; /* �洢ucRadioPri                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength
            = (pMsgIe->Qos.ucLen <= sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue)) ?
              (pMsgIe->Qos.ucLen) : (sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue));
        PS_MEM_CPY(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                   pMsgIe->Qos.pValue,
                   g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength);     /* ����Qos                                  */
        SM_SndRabmSmActivateInd(ucCntxtIndex, RABMSM_ACT_MSG_2);                /* ֪ͨRABM����Nsapi                        */
        SM_SndTafSmPdpActSecCnf(pMsgIe,ucCntxtIndex);                           /* ��TAF����Ӧ��Ϣ                          */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;         /* ״̬�л���SM_PDP_ACTIVE                  */

        NAS_SM_SndGmmPdpStatusInd();
    }
    else
    {
        g_aucSapi[0][0] = 0;
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE); /* ��network��SM STATUS��Ϣ#98              */
    }

    NAS_SM_EndSession();

    SM_Free(pMsgIe);                                                            /* �ͷ��ڴ�                                 */
    return;
}


VOS_VOID SM_RcvNwActSecPdpCntxtRejMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8       i,j;
    VOS_UINT8       ucCntxtIndex;
    VOS_UINT8       ucAddrIndex;

    ucCntxtIndex        = g_TiMapToNsapi[pMsgIe->ucTi];                         /* ����TI��ȡucCntxtIndex                   */

    if( 0xFF == ucCntxtIndex )
    {                                                                           /* ״̬ΪSM_PDP_INACTIVE                    */
         SM_SndStatusMsg(pMsgIe->ucTi,TAF_SM_REJ_CAUSE_INVALID_TI);             /* ��network��SM STATUS��Ϣ#81              */
    }
    else if( SM_PDP_ACTIVE_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {                                                                           /* ״̬ΪSM_PDP_ACTIVE_PENDING              */
        ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;       /* ���ucAddrIndex                          */
        SM_ComClearPdpCntxt(ucCntxtIndex);                                      /* �ͷ�ʵ��                                 */
        SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex);                            /* ֪ͨRABMȥ����                           */

        SM_SndTafSmPdpActSecRej(
          g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
          NAS_SM_MapSmNWCause(pMsgIe->SmCause));                           /* ��TAF�ؾܾ���Ϣ                          */

        for(i=0; i<g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt; i++)
        {                                                                       /* ����Nsapi�б�                            */
            if( g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[i]
                == ucCntxtIndex)
            {                                                                   /* Ϊ�ܾ���Nsapi                            */
                for( j = i; j
                   < (g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt-1);j++)
                {
                    g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[j]
                      =g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[j+1];  /* ���¶�Ӧ��nsapi                          */
                }
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt--;          /* Nsapi�ĸ�����1                           */
                break;
            }
        }
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;       /* ״̬�л���SM_PDP_INACTIVE                */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwActSecPdpCntxtRejMsg:NORMAL:SM state: SM_PDP_ACTIVE_PENDING ==> SM_PDP_INACTIVE");
        g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xff;     /* ά��g_CrMapToNsapi                       */
        g_TiMapToNsapi[pMsgIe->ucTi] = 0xff;                                    /* ά��g_TiMapToNsapi                       */
    }
    else
    {
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE);              /* ��network��SM STATUS��Ϣ#98              */
    }

    NAS_SM_EndSession();

    SM_Free(pMsgIe);
    return;
}


VOS_VOID SM_RcvNwModifyPdpCntxtReqMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8               ucCntxtIndex;
    VOS_UINT8               ucAddrIndex;

    ucCntxtIndex        = g_TiMapToNsapi[pMsgIe->ucTi];                         /* ����TI��ȡucCntxtIndex                   */

    if( 0xFF == ucCntxtIndex )
    {                                                                           /* ״̬ΪSM_PDP_INACTIVE                    */
         g_aucSapi[0][0] = 0;
         SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_INVALID_TI);            /* ��network��SM STATUS��Ϣ#81              */
    }
    else
    {
        ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;       /* ���Addr Index                           */
        if( SM_PDP_MODIFY_PENDING
            == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
        {                                                                       /* ״̬ΪSM_PDP_MODIFY_PENDING              */
            SM_SndTafSmPdpModifyRej(SM_TAF_CAUSE_SM_MODIFY_COLLISION,
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);                                /* ֪ͨTaf�ܾ��޸�                          */

            SM_TimerStop(ucCntxtIndex);                                         /* ֹͣT3381                                */
            SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);        /* �ͷű��ݵ���Ϣ                           */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;     /* ״̬�л���SM_PDP_ACTIVE                  */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwModifyPdpCntxtReqMsg:NORMAL:SM state: SM_PDP_MODIFY_PENDING ==> SM_PDP_ACTIVE");
        }
        if( SM_PDP_ACTIVE == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
        {                                                                       /* ��ǰ״̬ΪSM_PDP_ACTIVE                  */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength
                = (pMsgIe->Qos.ucLen <= sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue)) ?
                  (pMsgIe->Qos.ucLen) : (sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue));
            PS_MEM_CPY(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                       pMsgIe->Qos.pValue,
                       g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength); /* ����Qos                                  */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucRadioPri
                = pMsgIe->ucRadioPri;                                           /* �洢ucRadioPri                           */
            if( 0 != pMsgIe->PdpAddr.ucLen )
            {                                                                   /* Ҫ����PdpAddr                            */
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo
                    .ulAddrLength = pMsgIe->PdpAddr.ucLen;                      /* �趨����                                 */
                SM_MemCpy(
                    g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.aucAddrValue,
                    pMsgIe->PdpAddr.pValue,
                    pMsgIe->PdpAddr.ucLen);                                     /* �洢PdpAddr                              */
            }

            NAS_SM_BeginSession();

            SM_SndTafSmPdpModifyInd(pMsgIe, ucCntxtIndex);                      /* ֪ͨTAF�޸�����                          */
            SM_TimerStart(ucCntxtIndex,SM_T0003_LENGTH,SM_TIMER_TYPE_T0003);    /* ����Network����PDP context Modify����
                                                                                 * Timer                                    */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_NW_MODIFY;  /* ״̬�л���SM_PDP_NW_MODIFY               */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwModifyPdpCntxtReqMsg:NORMAL: SM state: SM_PDP_ACTIVE ==> SM_PDP_NW_MODIFY");
        }
        else if(SM_PDP_NW_MODIFY
            == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
        {                                                                       /* ��ǰ״̬ΪSM_PDP_NW_MODIIFY              */
        }
        else
        {
            g_aucSapi[0][0] = 0;

            SM_SndStatusMsg(pMsgIe->ucTi,TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE); /* ��network��SM STATUS��Ϣ#98              */
        }
    }
    SM_Free(pMsgIe);                                                            /* �ͷ��ڴ�                                 */
    return;
}


VOS_VOID SM_RcvNwModifyPdpCntxtAccMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8               ucCntxtIndex;

    ucCntxtIndex        = g_TiMapToNsapi[pMsgIe->ucTi];                         /* ����TI��ȡucCntxtIndex                   */

    if( 0xFF == ucCntxtIndex )
    {                                                                           /* ״̬ΪSM_PDP_INACTIVE                    */
         g_aucSapi[0][0] = 0;
         SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_INVALID_TI);            /* ��network��SM STATUS��Ϣ#81              */
    }
    else if( SM_PDP_MODIFY_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {
        SM_TimerStop(ucCntxtIndex);                                             /* ֹͣT3380                                */
        SM_Free( g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg );          /* �ͷű��ݵ���Ϣ                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
        if( 0 != pMsgIe->ucRadioPri )
        {                                                                       /* ����ucRadioPri                           */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucRadioPri
                = pMsgIe->ucRadioPri;                                           /* �洢ucRadioPri                           */
        }
        if( 0 != pMsgIe->Qos.ucLen )
        {                                                                       /* ��Ϣ�д���Qos                            */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength
                = (pMsgIe->Qos.ucLen <= sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue)) ?
                  (pMsgIe->Qos.ucLen) : (sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue));
            PS_MEM_CPY(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
                       pMsgIe->Qos.pValue,
                       g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength); /* ����Qos                                  */
        }
        SM_SndRabmSmModifyInd(ucCntxtIndex);                                    /* ֪ͨ�޸�Nsapi                            */
        SM_SndTafSmPdpModifyCnf(pMsgIe, ucCntxtIndex);                          /* ��TAF����Ӧ��Ϣ                          */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;         /* ״̬�л���SM_PDP_ACTIVE                  */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwModifyPdpCntxtAccMsg:NORMAL:SM state: SM_PDP_MODIFY_PENDING ==> SM_PDP_ACTIVE");
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_CONTEXT_MODIFY_SUCC,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);

        /* ����pdp�������޸ĳɹ�����֪ͨGMM */
        NAS_SM_SndGmmPdpModifyInd(ucCntxtIndex + SM_NSAPI_OFFSET);
    }
    else
    {
        g_aucSapi[0][0] = 0;
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE);               /* ��network��SM STATUS��Ϣ#98              */
    }

    NAS_SM_EndSession();

    SM_Free(pMsgIe);
    return;
}


VOS_VOID SM_RcvNwModifyPdpCntxtRejMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8       ucCntxtIndex;

    ucCntxtIndex        = g_TiMapToNsapi[pMsgIe->ucTi];                         /* ����TI��ȡucCntxtIndex                   */

    if( 0xFF == ucCntxtIndex )
    {                                                                           /* ״̬ΪSM_PDP_INACTIVE                    */
         SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_INVALID_TI);            /* ��network��SM STATUS��Ϣ#81              */
    }
    else if( SM_PDP_MODIFY_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {                                                                           /* ״̬ΪSM_PDP_MODIFY_PENDING              */
        SM_TimerStop(ucCntxtIndex);                                             /* ֹͣT3381                                */
        SM_Free( g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg );          /* �ͷű��ݵ���Ϣ                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;

        SM_SndTafSmPdpModifyRej(NAS_SM_MapSmNWCause(pMsgIe->SmCause),
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;         /* ״̬�л���SM_PDP_ACTIVE                  */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwModifyPdpCntxtRejMsg:NORMAL:SM state: SM_PDP_MODIFY_PENDING ==> SM_PDP_ACTIVE");
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_CONTEXT_MODIFY_FAIL,
                        (VOS_VOID *)&(pMsgIe->SmCause),
                        NAS_OM_EVENT_PDP_CONTEXT_MODIFY_FAIL_LEN);
    }
    else
    {
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE);               /* ��network��SM STATUS��Ϣ#98              */
    }

    NAS_SM_EndSession();

    SM_Free(pMsgIe);                                                            /* �ͷ��ڴ�                                 */
    return;
}
VOS_VOID SM_RcvNwDeActPdpCntxtReqMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8               i;
    VOS_UINT8               ucCntxtIndex;
    VOS_UINT8               ucAddrIndex;
    VOS_UINT8               ucLinkNsapi;
    VOS_UINT8               ucInitType;
    /* Deleted by wx270776 for OM�ں�, 2015-7-23, begin */

    /* Deleted by wx270776 for OM�ں�, 2015-7-23, end */

    ucCntxtIndex = g_TiMapToNsapi[pMsgIe->ucTi];                                /* ����TI��ȡucCntxtIndex                   */

    if( 0xFF == ucCntxtIndex )
    {                                                                           /* ״̬ΪSM_PDP_INACTIVE                    */
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_INVALID_TI);
    }
    else
    {
        ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;       /* ���Addr Index                           */
        NAS_SM_BeginSession();
        SM_SndPdpDeActAccMsg(ucCntxtIndex);                                     /* ��network��ACCEPT��Ϣ                    */
        if( SM_TRUE == pMsgIe->ucTdi )
        {                                                                       /* ����Tear down indicator IE���� requested */
            if( SM_PDP_INACTIVE_PENDING
                == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
            {                                                                   /* ״̬ΪSM_PDP_INACTIVE_PENDING            */
                NAS_SM_NORM_LOG("SM_RcvNwDeActPdpCntxtReqMsg: SM state: SM_PDP_INACTIVE_PENDING ==> SM_PDP_INACTIVE");
                SM_TimerStop(ucCntxtIndex);                                     /* ֹͣT3390                                */
                SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);    /* �ͷű��ݵ���Ϣ                           */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                    = SM_PDP_INACTIVE;                                          /* ״̬�л���SM_PDP_INACTIVE                */

                g_TiMapToNsapi[pMsgIe->ucTi] = 0xFF;                            /* ά��g_TiMapToNsapi                       */
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr]
                    = 0xFF;                                                     /* ά��g_CrMapToNsapi                       */
            }

            SM_SndRabmSmDeactivateInd(
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt,
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi);             /* ֪ͨRABMȥ����Nsapi�б�:                 */
            SM_SndTafSmPdpDeActInd(
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                NAS_SM_MapSmNWCause(pMsgIe->SmCause),
                SM_TRUE);

            /* ��ɫͨ�� */
            /* Deleted by wx270776 for OM�ں�, 2015-7-23, begin */
            /* Deleted by wx270776 for OM�ں�, 2015-7-23, end */

            for(i=0;i<g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt;i++)
            {                                                                   /* Nsapi�б�                                */
                ucLinkNsapi
                    = g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[i];     /* ���ucLinkNsapi                          */
                SM_ComClearPdpCntxt(ucLinkNsapi);                               /* �ͷ�ʵ��                                 */
                g_SmEntity.aPdpCntxtList[ucLinkNsapi].ucState
                    = SM_PDP_INACTIVE;                                          /* ״̬�л���SM_PDP_INACTIVE                */

                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwDeActPdpCntxtReqMsg:NORMAL: SM state = SM_PDP_INACTIVE");
                g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucLinkNsapi].ucTi]
                    = 0xFF;                                                     /* ά��g_TiMapToNsapi                       */
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucLinkNsapi].ucCr]
                    = 0xFF;                                                     /* ά��g_CrMapToNsapi                       */
            }

            SM_ComClearPdpAddrApn(ucAddrIndex);                                 /* ���Addr Apnʵ��                         */
            NAS_SM_SndGmmPdpStatusInd();
        }
        else
        {                                                                       /* ������Tear down IE����not requested      */
            if( SM_PDP_INACTIVE_PENDING
                == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
            {                                                                   /* ״̬ΪSM_PDP_INACTIVE_PENDING            */
                NAS_SM_NORM_LOG("SM_RcvNwDeActPdpCntxtReqMsg:NORMAL:SM state: SM_PDP_INACTIVE_PENDING ==> SM_PDP_INACTIVE ");

                SM_TimerStop(ucCntxtIndex);                                     /* ֹͣT3390                                */
                SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);    /* �ͷű��ݵ���Ϣ                           */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
                SM_SndTafSmPdpDeActCnf(g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);          /* ��TAF����Ӧ��Ϣ                          */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                    = SM_PDP_INACTIVE;                                          /* ״̬�л���SM_PDP_INACTIVE                */

            }
            else
            {
                NAS_SM_NORM_LOG("SM_RcvNwDeActPdpCntxtReqMsg:NORMAL: SM state = SM_PDP_INACTIVE");

                SM_SndRabmSmDeactivateInd (1, &ucCntxtIndex);                   /* ֪ͨRABMȥ����Nsapi                      */
                SM_SndTafSmPdpDeActInd(
                    g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                    NAS_SM_MapSmNWCause(pMsgIe->SmCause),
                    SM_FALSE);

                /* ��ɫͨ�� */
                /* Deleted by wx270776 for OM�ں�, 2015-7-23, begin */
                /* Deleted by wx270776 for OM�ں�, 2015-7-23, end */
                SM_ComClearPdpCntxt(ucCntxtIndex);                              /* �ͷ�ʵ��                                 */
                SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);               /* ��PDP Addr and Apnʵ����ɾ��Nsapi        */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                    = SM_PDP_INACTIVE;                                          /* ״̬�л���SM_PDP_INACTIVE                */

                NAS_SM_SndGmmPdpStatusInd();
            }
            g_TiMapToNsapi[pMsgIe->ucTi] = 0xFF;                                /* ά��g_TiMapToNsapi                       */
            g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xFF; /* ά��g_CrMapToNsapi                       */
        }
        ucInitType = DEACTIVE_REQUEST_INIT_TYPE_MT;
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_DEACTIVE_REQ,
                        (VOS_VOID *)&ucInitType,
                        NAS_OM_EVENT_PDP_DEACTIVE_REQ_LEN);
        NAS_SM_SndGmmPdpDeactivatedInd();
        NAS_SM_EndSession();
    }

    SM_Free(pMsgIe);                                                            /* �ͷ��ڴ�                                 */
    return;
}


VOS_VOID SM_RcvNwDeActPdpCntxtAccMsg(SM_NW_MSG_STRU *pMsgIe)
{
    VOS_UINT8                           ucCntxtIndex;

    ucCntxtIndex = g_TiMapToNsapi[pMsgIe->ucTi];                                /* ����TI��ȡucCntxtIndex                   */

    if( 0xFF == ucCntxtIndex )
    {                                                                           /* ״̬ΪSM_PDP_INACTIVE                    */
         SM_SndStatusMsg(pMsgIe->ucTi,TAF_SM_REJ_CAUSE_INVALID_TI);             /* ��network��SM STATUS��Ϣ#81              */
    }
    else if( SM_PDP_INACTIVE_PENDING
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
    {                                                                           /* ״̬ΪSM_PDP_INACTIVE_PENDING            */
        SM_TimerStop(ucCntxtIndex);                                             /* ֹͣT3390                                */
        SM_Free( g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg );          /* �ͷű��ݵ���Ϣ                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
        SM_SndTafSmPdpDeActCnf(g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;       /* ״̬�л���SM_PDP_INACTIVE                */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwDeActPdpCntxtAccMsg:NORMAL:SM state: SM_PDP_INACTIVE_PENDING ==> SM_PDP_INACTIVE");
        g_TiMapToNsapi[pMsgIe->ucTi] = 0xff;                                    /* ά��g_TiMapToNsapi                       */
        g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xff;     /* ά��g_CrMapToNsapi                       */

        NAS_SM_SndGmmPdpStatusInd();

        /* ��GMM����GMMSM_PDP_DEACTIVATED_IND��Ϣ�����浱ǰPDP״̬ */
        NAS_SM_SndGmmPdpDeactivatedInd();
    }
    else
    {
        SM_SndStatusMsg(pMsgIe->ucTi, TAF_SM_REJ_CAUSE_MSGTYPE_NOT_COMP_WITH_STATE);               /* ��network��SM STATUS��Ϣ#98              */
    }

    NAS_SM_EndSession();

    SM_Free(pMsgIe);
    return;
}

/*******************************************************************************
  Module:   SM_ComFindNullAddrApn
  Function: ����δʹ�õ�Addr �� Apn������
  Input:    VOS_VOID
  Output:   VOS_VOID
  NOTE:
  Return:   ucAddrIndex
  History:
      1.   ֣ ΰ   2003.12.10   �¹�����
*******************************************************************************/
VOS_UINT8 SM_ComFindNullAddrApn()
{
    VOS_UINT8            i;

    for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
    {                                                                           /* �������е�Addr �� Apnʵ��                */
        if( 0 == (g_SmPdpAddrApn.usPdpAddrFlg & (VOS_UINT16)((VOS_UINT32)0x0001 << i)))
        {                                                                       /* ��Ӧ������û��ʹ��                       */
            return i;                                                           /* ����Addr �� Apn������                    */
        }
    }
    return SM_MAX_NSAPI_NUM;                                                    /* ������Ч��û��δʹ�õ�����               */
}


VOS_VOID SM_ComClearPdpCntxt(
     VOS_UINT8                          ucCntxtIndex                            /* PDPcontextʵ�������                     */
 )
{
    VOS_UINT8    ucAddrIndex;

    SM_TimerStop(ucCntxtIndex);                                                 /* ֹͣ��ʵ���Timer                        */
    ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;
    if(0 == g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt)
    {                                                                           /* ucNsapiCnt�ĸ���Ϊ0                      */
        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.ulApnLength = 0;        /* ��ʼ��������Ϣ                           */
        PS_MEM_SET(g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue,
                   0x00,
                   sizeof(g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue));
    }

    g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.ulQosLength = 0;
    PS_MEM_SET(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue,
               0x00,
               sizeof(g_SmEntity.aPdpCntxtList[ucCntxtIndex].QoS.aucQosValue));

    if( SM_NULL != g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg )
    {                                                                           /* ���ڻ�����ط���Ϣ                       */
        SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);            /* �ͷŻ�����ط���Ϣ                       */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
    }


    PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_ComClearPdpCntxt:NORMAL: Destroy SM entity(index):", ucCntxtIndex);

    return;
}


VOS_VOID SM_ComClearPdpAddrApn(
    VOS_UINT8                           ucAddrIndex                             /* PDPAddrʵ�������                        */
)
{
    VOS_UINT32                          ulTmp = 1;

    g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.ulApnLength = 0;
    PS_MEM_SET(g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue,
               0x00,
               sizeof(g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue));

    g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.ulAddrLength = 0;      /* ���PdpAddrInfo����                      */
    g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt = 0;                    /* nsapi������0                             */
    g_SmPdpAddrApn.usPdpAddrFlg &= ( ~ (ulTmp << ucAddrIndex));

    return;
}

/*******************************************************************************
  Module:   SM_ComDelNsapiFromAddr
  Function: PDP Addr and Apnʵ����ɾ��Nsapi
  Input:    VOS_UINT8          ucAddrIndex
            VOS_UINT8          ucNsapi
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   ֣ ΰ   2003.12.10   �¹�����
*******************************************************************************/
VOS_VOID SM_ComDelNsapiFromAddr(
                            VOS_UINT8          ucAddrIndex,                         /* PDP Addr and Apnʵ�������               */
                            VOS_UINT8          ucNsapi                              /* Ҫɾ����NSAPI                            */
                            )
{
    VOS_UINT8        i;
    VOS_UINT8        j;

    for(i = 0;i< g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt;i++)
    {                                                                           /* ����Nsapi�б�                            */
        if(g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[i] == ucNsapi)
        {                                                                       /* �ҵ�ָ����Nsapi                          */
            for(j = i; j
                < (g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt-1); j++ )
            {
                g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[j]
                    = g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[j+1];   /* ɾ��ָ����Nsapi                          */
            }
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt--;              /* NSAPI������1                             */
            break;
        }
    }
    if( 0 == g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt )
    {                                                                           /* ucNsapiCnt�ĸ���Ϊ0                      */
        SM_ComClearPdpAddrApn(ucAddrIndex);                                     /* ���Addr��Apnʵ��                        */
    }
    return;
}

/*******************************************************************************
  Module:   SM_RcvNwReqPdpCnxtActMsg_S00
  Function: SM_PDP_INACTIVE״̬���յ�REQUEST PDP CONTEXT ACTIVATION��Ϣ�Ĵ���
  Input:    SM_NW_MSG_STRU    *pMsgIe            �յ�����Ϣ
            VOS_UINT8             ucCntxtIndex       PDP context������
  Output:   VOS_VOID
  NOTE:     8-0
  Return:   VOS_VOID
  History:
      1.   ֣ ΰ   2003.12.10   �¹�����
*******************************************************************************/
VOS_VOID SM_RcvNwReqPdpCnxtActMsg_S00(
                                  SM_NW_MSG_STRU                *pMsgIe,        /* �յ�����Ϣ                               */
                                  VOS_UINT8                         ucCntxtIndex    /* PDP context������                        */
                                 )
{
    VOS_UINT16                  i;      /*A32D00461,zzy,pclint*/
    VOS_UINT8                   ucCr;
    VOS_UINT8                   ucTi;

    ucTi = (VOS_UINT8)(pMsgIe->ucTi & 0x7F);                                        /* ȡTI��ʵ��ֵ                             */
    ucCr = 0xff;

    for( i = 0; i <= (SM_MAX_NSAPI_NUM - 1);    i++ )
    {                                                                           /* ����MT���̵�CR                           */
        if( 0xff == g_CrMapToNsapi[i] )
        {                                                                       /* ����û��ʹ�õ�CR                         */
            ucCr = (VOS_UINT8)i;        /*A32D00461,zzy,pclint*/                                                   /* ��ȡCR                                   */
            break;
        }
    }
    if( 0xFF != ucCr )
    {                                                                           /* ���� CR�ɹ�                              */
        PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwReqPdpCnxtActMsg_S00:NORMAL: Create SM entity(index):", ucCntxtIndex);
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTiFlg = SM_TI_NET_ORG;         /* �趨ʵ��ķ����־ NET����               */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi = ucTi;                     /* �洢TI                                   */
        g_TiMapToNsapi[pMsgIe->ucTi]= ucCntxtIndex;                             /* ά��Ti��NSAPI��ӳ��                      */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr = ucCr;                     /* �洢CR                                   */
        g_CrMapToNsapi[ucCr] = ucCntxtIndex;                                    /* ά��Cr��NSAPI��ӳ��                      */

        SM_SndTafSmPdpActivateInd(pMsgIe, ucCntxtIndex);                        /* �����е�TAF���ͼ�������                  */
    }
    else
    {
        SM_SndReqPdpActRejMsg(SM_NULL, ucTi);                                   /* �ؾܾ���Ϣ                               */
    }

    return;
}
VOS_UINT8 SM_RcvNwReqPdpCnxtActMsg_S01(
    SM_NW_MSG_STRU                     *pMsgIe,             /* �յ�����Ϣ                               */
    VOS_UINT8                           ucCntxtIndex,       /* PDP context������                        */
    VOS_UINT8                           ucTi                /* ����Ti                                   */
)
{
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucResult1;
    VOS_UINT8                           ucResult2;

    ucResult1   = 0xFF;
    ucResult2   = 0xFF;
    ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;

    if(( 0 != pMsgIe->Apn.ucLen )
        &&( pMsgIe->Apn.ucLen
        == g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.ulApnLength)
        &&( pMsgIe->PdpAddr.ucLen
        == g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.ulAddrLength))
    {                                                                           /* �ܹ��Ƚ�PDP type, PDP address and APN    */
        ucResult1 = SM_MemCmp(
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue,
            pMsgIe->Apn.pValue,
            pMsgIe->Apn.ucLen);                                                 /* �����ڴ�ȽϺ���                         */
        ucResult2 = SM_MemCmp(
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.aucAddrValue,
            pMsgIe->PdpAddr.pValue,
            pMsgIe->PdpAddr.ucLen);                                             /* �����ڴ�ȽϺ���                         */
        if(( 0 == ucResult1 )
            &&( 0 == ucResult2 ))
        {                                                                       /* PDP type, PDP address and APN��ͬ        */
            return SM_TRUE;
        }
    }

    return SM_FALSE;
}
VOS_VOID SM_RcvNwReqPdpCnxtActMsg_S02(
    SM_NW_MSG_STRU                     *pMsgIe,
    VOS_UINT8                           ucCntxtIndex
)
{
    VOS_UINT8               i;
    VOS_UINT8               ucAddrIndex;
    VOS_UINT8               ucLinkIndex;

    VOS_UINT8                   ucResult1;
    VOS_UINT8                   ucResult2;

    ucResult1   = 0xFF;
    ucResult2   = 0xFF;

    if ( ucCntxtIndex >= SM_MAX_NSAPI_NUM )
    {
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_RcvNwReqPdpCnxtActMsg_S02:WARNING:ucCntxtIndex >= SM_MAX_NSAPI_NUM ");
        return;    /*A32D00461,zzy,pclint*/
    }
    ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;

    if(( 0 != pMsgIe->Apn.ucLen )
        &&( pMsgIe->Apn.ucLen
        == g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.ulApnLength)
        &&( pMsgIe->PdpAddr.ucLen > 2 )
        &&( pMsgIe->PdpAddr.ucLen
        == g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.ulAddrLength))
    {                                                                           /* �ܹ��Ƚ�PDP type, PDP address and APN    */
        ucResult1 = SM_MemCmp(
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpApn.aucApnValue,
            pMsgIe->Apn.pValue,
            pMsgIe->Apn.ucLen);                                                 /* �����ڴ�ȽϺ���                         */
        ucResult2 = SM_MemCmp(
            g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].PdpAddrInfo.aucAddrValue,
            pMsgIe->PdpAddr.pValue,
            pMsgIe->PdpAddr.ucLen);                                             /* �����ڴ�ȽϺ���                         */
        if(( 0 == ucResult1 )
            &&( 0 == ucResult2 ))
        {                                                                       /* PDP type, PDP address and APN��ͬ        */
            SM_SndRabmSmDeactivateInd(
                        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt,
                        g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi);     /* ֪ͨRABMȥ����Nsapi�б�:                 */
            for(i = 0;i < g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].ucNsapiCnt;
                i++)
            {                                                                   /* Nsapi�б�                                */
                ucLinkIndex
                     = g_SmPdpAddrApn.aPdpAddrlist[ucAddrIndex].aucNsapi[i];

                SM_SndTafSmPdpDeActInd(
                        g_SmEntity.aPdpCntxtList[ucLinkIndex].ucCr,
                        SM_TAF_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED,
                        SM_TRUE);                                               /* ֪ͨTAFȥ����                            */

                SM_ComClearPdpCntxt( ucLinkIndex );                             /* �ͷ�ʵ��                                 */
                g_SmEntity.aPdpCntxtList[ucLinkIndex].ucState
                    = SM_PDP_INACTIVE;                                          /* ״̬�л���SM_PDP_INACTIVE                */

                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwReqPdpCnxtActMsg_S02:NORMAL: SM state = SM_PDP_INACTIVE");
                g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucLinkIndex].ucTi]
                    = 0xFF;
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucLinkIndex].ucCr]
                    = 0xFF;
            }
            SM_ComClearPdpAddrApn(ucAddrIndex);                                 /* ���Addr Apnʵ��                         */
        }
        else
        {
            SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex);                        /* ֪ͨRABMȥ����Nsapi�б�:                 */
            SM_SndTafSmPdpDeActInd(
                        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                        SM_TAF_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED,
                        SM_FALSE);

            SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);
            SM_ComClearPdpCntxt( ucCntxtIndex );                                /* �ͷ�ʵ��                                 */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;   /* ״̬�л���SM_PDP_INACTIVE                */

            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwReqPdpCnxtActMsg_S02:NORMAL: SM state = SM_PDP_INACTIVE");
            g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xFF;
            g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xFF;
        }
    }
    else
    {
        if( SM_PDP_INACTIVE_PENDING
            == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
        {
            SM_TimerStop(ucCntxtIndex);                                         /* ֹͣT3390                                */
            SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);        /* �ͷű��ݵ���Ϣ                           */
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
            SM_SndTafSmPdpDeActCnf(g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);              /* ��TAF����Ӧ��Ϣ                          */
        }
        else
        {
            SM_SndRabmSmDeactivateInd (1, &ucCntxtIndex);                       /* ֪ͨRABMȥ����Nsapi                      */
            SM_SndTafSmPdpDeActInd(
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                SM_TAF_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED,
                SM_FALSE);
            SM_ComClearPdpCntxt(ucCntxtIndex);
            SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);
        }
        g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xFF;
        g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xFF;
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;       /* ״̬�л���SM_PDP_INACTIVE                */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvNwReqPdpCnxtActMsg_S02:NORMAL: SM state = SM_PDP_INACTIVE");
    }

    SM_RcvNwReqPdpCnxtActMsg_S00(pMsgIe,ucCntxtIndex);                          /* ������SM_PDP_INACTIVE״̬�Ĵ���          */
    NAS_SM_SndGmmPdpStatusInd();

    return;
}
VOS_BOOL NAS_SM_ComparePdpAddr(
    SM_MSG_IE_COMMON_STRU              *pstReqPdpAddr,
    SM_PDP_ADDR_STRU                   *pstExistPdpAddr
)
{
    if ( (pstReqPdpAddr->ucLen > 2)
      && (pstReqPdpAddr->ucLen == pstExistPdpAddr->ulAddrLength) )
    {
/*lint -e961*/
        if (!VOS_MemCmp(pstReqPdpAddr->pValue, pstExistPdpAddr->aucAddrValue, pstExistPdpAddr->ulAddrLength))
        {
            return VOS_TRUE;
        }
/*lint +e961*/
    }

    return VOS_FALSE;
}


VOS_VOID NAS_SM_RcvGmmSigConnInd(
    GMMSM_SIG_CONN_IND_STRU            *pstSigConnInd
)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo;
    VOS_UINT32                          ulTimerLen = 0;
    VOS_UINT8                           ucTimerType = 0;
    VOS_UINT8                           ucTmrReStartFlg;
    VOS_UINT8                           ucExpireTimes;
    VOS_UINT8                           i;

    for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
    {
        /* ��ȡPDPʵ����Ϣ */
        pstPdpCtxInfo   = NAS_SM_GetPdpCtxInfoAddr(i);

        /* ���ö�ʱ��������ʶ */
        ucTmrReStartFlg = VOS_FALSE;

        switch (pstPdpCtxInfo->ucState)
        {
            case SM_PDP_ACTIVE_PENDING:
                ucTimerType     = SM_TIMER_TYPE_T3380;
                ulTimerLen      = SM_T3380_LENGTH;
                ucTmrReStartFlg = VOS_TRUE;
                break;

            case SM_PDP_MODIFY_PENDING:
                ucTimerType     = SM_TIMER_TYPE_T3381;
                ulTimerLen      = SM_T3381_LENGTH;
                ucTmrReStartFlg = VOS_TRUE;
                break;

            case SM_PDP_INACTIVE_PENDING:
                ucTimerType     = SM_TIMER_TYPE_T3390;
                ulTimerLen      = SM_T3390_LENGTH;
                ucTmrReStartFlg = VOS_TRUE;
                break;

            default :
                break;
        }

        if (VOS_TRUE == ucTmrReStartFlg)
        {
            /* ����ʱ�������ڿ���״̬������Ҫ�����������Ա����¼�ʱ */
            if (SM_TIMER_STA_ON == pstPdpCtxInfo->TimerInfo.ucTimerStaFlg)
            {
                /* ����ucExpireTimes, ��ʱ��������ָ� */
                ucExpireTimes = pstPdpCtxInfo->TimerInfo.ucExpireTimes;

                /* ֹͣ��������Ӧ��ʱ�� */
                SM_TimerStop(i);
                SM_TimerStart(i, ulTimerLen, ucTimerType);

                /* �ָ�ucExpireTimes */
                pstPdpCtxInfo->TimerInfo.ucExpireTimes = ucExpireTimes;
            }
        }
    }
}

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
