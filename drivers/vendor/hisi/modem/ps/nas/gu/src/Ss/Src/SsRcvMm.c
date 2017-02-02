/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsRcvMm.c
  Description  : ����MM��Ϣ�Ĵ���
  Function List:
      1.  Ss_CheckAirMsg               �տ���Ϣ���
      2.  Ss_RcvMmssEstCnf             ����MMSS_EST_CNF�Ĵ���
      3.  Ss_RcvMmssEstInd             ����MMSS_EST_IND�Ĵ���
      4.  Ss_RcvMmssDataInd            ����MMSS_DATA_IND�Ĵ���
      5.  Ss_RcvMmssRelInd             ����MMSS_REL_IND�Ĵ���
      6.  Ss_RcvMmMsg                  �ַ�MM��Ϣ
  History:
      1.  ��־�� 2004.03.08   �°�����
*******************************************************************************/

#include "SsInclude.h"
#include "NasOmInterface.h"
#include "NasUsimmApi.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SS_RCVMM_C

/*lint -save -e958 */

VOS_VOID NAS_SS_ReportN2MOtaMsg(
    SS_MSG_STRU                        *pNasMsg
)
{

    NAS_OTA_MSG_ID_ENUM_UINT16          enNasOtaMsyId;
    VOS_UINT8                           ucMsgType;

    enNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    /* Message Type�ֶ�����Ϣ�е�����λ�� */
    ucMsgType = pNasMsg->aucSsMsg[1];

    SS_NORM_LOG1("NAS_SS_ReportN2MOtaMsg: [Msgtype] ", pNasMsg->aucSsMsg[1]);

    /* ��NAS���пտ���ϢID���ϱ���OM����ϢID��Ӧ����ͨ��OM���й�ȡ��ʾ */
    switch(ucMsgType)
    {
        case SS_MSG_REGISTER:
            enNasOtaMsyId = NAS_OTA_MSG_SS_REGISTER_DOWN;
            break;
        case SS_MSG_FACILITY:
            enNasOtaMsyId = NAS_OTA_MSG_SS_FACILITY_DOWN;
            break;
        case SS_MSG_RELCMPL:
            enNasOtaMsyId = NAS_OTA_MSG_SS_RELCMPL_DOWN;
            break;
        default:
            break;
    }

    if (NAS_OTA_MSG_ID_BUTT == enNasOtaMsyId)
    {
          SS_WARN_LOG1("NAS_SS_ReportN2MOtaMsg: invalid msg type!", enNasOtaMsyId);
          /* ������SSģ��Ŀտ���Ϣ������trace����ʾ */
          return;
    }

    /*�ϱ��տ���Ϣ��OM*/
    NAS_SendAirMsgToOM(WUEPS_PID_SS,
                       enNasOtaMsyId,
                       NAS_OTA_DIRECTION_DOWN,
                       pNasMsg->ulSsMsgSize + 4,
                       (VOS_UINT8 *)pNasMsg);

    return;
}

/***********************************************************************
*  MODULE   : Ss_CheckAirMsg
*  FUNCTION : �տ���Ϣ���
*  INPUT    : VOS_VOID      *pMsg       ��ǰ�������Ϣ
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_UINT8     ucResult    WUEPS_TRUE:  ���ͨ��
*                                   WUEPS_FALSE: ���δͨ��
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-08  �°�����
************************************************************************/

VOS_UINT8 Ss_CheckAirMsg(
                     VOS_VOID *pMsg
                     )
{
    VOS_UINT8                   ucResult;                                           /* ������Ϣ����Ƿ�ɹ���־                 */
    MMSS_DATA_IND_STRU      *pDataInd;                                          /* ����ָ��MMSS_DATA_IND���͵���Ϣ          */

    ucResult = WUEPS_TRUE;                                                      /* ��ʼ��Ϊ�ɹ�                             */
    pDataInd = (MMSS_DATA_IND_STRU*)pMsg;                                       /* ��ȡMMSS_DATA_IND_STRU��Ϣָ��           */
    if( pDataInd->SsMsg.ulSsMsgSize < 2 )
    {                                                                           /* ��Ϣ����                                 */
        ucResult = WUEPS_FALSE;                                                 /* ���ؼ��ʧ��                             */
    }
    else if(( SS_MSG_REGISTER == pDataInd->SsMsg.aucSsMsg[1] )
        && ( pDataInd->ulTi > SS_MT_ENTITY_NUM ))
    {                                                                           /* REGISTER��TI FLAGΪ1                     */
        ucResult = WUEPS_FALSE;                                                 /* ���ؼ��ʧ��                             */
    }
    else
    {
    }
    return ucResult;
}



VOS_VOID Ss_RcvMmssEstCnf(
                      VOS_VOID *pMsg
                      )
{
    MMSS_EST_CNF_STRU   *pEstCnf;                                               /* ����ָ��MMSS_EST_CNF��Ϣ��ָ��           */
    VOS_UINT8                  ucTi;                                                /* ���ڻ�ȡTI                               */
    ST_SSP_MSG           stSsMsg;

    pEstCnf = (MMSS_EST_CNF_STRU *)pMsg;                                        /* ��ȡָ��MMSS_EST_CNF��Ϣ��ָ��           */
    ucTi = ( VOS_UINT8 )( pEstCnf->ulTi );                                          /* ȡ��TI                                   */

    if( 0x07 != ( ucTi & 0x07 ))
    {                                                                           /* TI��ӦΪ��111��                            */
        if( SS_S_CONNECT_PEND == g_SsEntity[ucTi].ucState )
        {                                                                       /* �ж��Ƿ��ǽ�����                         */
            if( MMSS_EST_SUCCESS == pEstCnf->ulResult )
            {                                                                   /* �жϽ����Ƿ�ɹ�                         */
                Ss_SndRegister( ucTi );                                         /* ����DR(REGISTER)ԭ��                     */

                NAS_SS_ChangeSsState(ucTi, SS_S_CONNECTED);

                stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;

                if (stSsMsg.ucCr >= TAF_MT_MIN_CR)
                {
                    stSsMsg.ucCr -= 120;                                        /*Cr��ΧΪ128-134ʱ����Ҫת����TI:8-14*/
                }

                stSsMsg.SspmsgCore.ucChoice = SSA_SS_CS_CONN_IND;

                PS_MEM_SET(&(stSsMsg.SspmsgCore.u.stCsConnInd), 0, sizeof(SSA_SS_CS_CONN_IND_STRU));
                stSsMsg.SspmsgCore.u.stCsConnInd.enConnState = SSA_SS_CS_CONN_STATE_PRESENT;
                SSA_DealMsgFromSS(&stSsMsg);

                SS_NORM_LOG(
                    "\n SS state: SS_S_CONNECT_PEND ==> SS_S_CONNECTED \r" );
            }

            /* mm����ظ�est cnf���Ϊʧ�ܣ��ó���mmͳһͨ��mmss rel ind��Ϣ�ظ� */
        }
    }
}


VOS_UINT32 LCS_RcvMmlcsMsg(
    VOS_UINT8                           ucTi,
    VOS_VOID                           *pAirMsg
)
{
    VOS_UINT8                          *pucRcvMsg;
    ST_SSP_IES_CAUSE                    stCause;
    VOS_UINT8                          *pucDestMsg;
    VOS_UINT8                           ucMsgTi;
    VOS_UINT32                          ulCodeLen;          /* ����󳤶� */

    pucRcvMsg       = (VOS_UINT8 *)pAirMsg;
    ulCodeLen       = 0;
    ucMsgTi         = GET_MSG_TI(ucTi);
    PS_MEM_SET(&stCause, 0, sizeof(stCause));

    /* �ж������LCS��Ϣ������VOS_ERR */
    if (LCS_MM_IE_PD_LOCATION_SRVC != (pucRcvMsg[0] & 0x0f))
    {
        return VOS_ERR;
    }

    /* ��REGISTER��Ϣ����������ֱ�ӷ���VOS_OK */
    if (LCS_MSG_REGISTER != pucRcvMsg[1])
    {
        return VOS_OK;
    }

    /* ������Ӫ��Ҫ�󣬵�UE��֧��LCS����ʱ����Ҫ�ظ�RELCOMP(#69) */
    /* ��дCause�� */
    stCause.ulCnt       = 2;

    /* ��дcoding standard */
    stCause.Cause[0]    = LCS_CAUSE_CODING_STANDARD_GSM;

    /* ��дԭ��ֵ(#69) */
    stCause.Cause[1]    = LCS_CAUSE_FACILITY_NOT_IMPLEMENTED;

    /* ����RELCOMPLETE��Ϣ�ڴ�ռ� */
    pucDestMsg = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_SS, SS_MAX_MSG_LEN);
    if ( VOS_NULL_PTR == pucDestMsg)
    {
        return VOS_ERR;
    }
    PS_MEM_SET(pucDestMsg, 0, SS_MAX_MSG_LEN);

    /* ����PD��TI�ֽ� */
    *(pucDestMsg + ulCodeLen) = (VOS_UINT8)(NAS_PD_LS | ( ucMsgTi << 4 ));

    /* ���±����ĳ��� */
    ulCodeLen++;

    /* ������Ϣ���� */
    *(pucDestMsg + ulCodeLen) = LCS_MSG_RELCMPL;

    /* ���±����ĳ��� */
    ulCodeLen++;

    /* ����ָ��IE���ڱ�־ */
    *(pucDestMsg + ulCodeLen) = LCS_IEICAUSE;

    /* ���±����ĳ��� */
    ulCodeLen++;

    /* ��дCAUSE���� */
    *(pucDestMsg + ulCodeLen) = (VOS_UINT8)stCause.ulCnt;

    /* ���±����ĳ��� */
    ulCodeLen++;

    /* ��дCAUSEֵ */
    PS_MEM_CPY(pucDestMsg + ulCodeLen, stCause.Cause, stCause.ulCnt);

    /* ���±����ĳ��� */
    ulCodeLen += stCause.ulCnt;

    /* ����MMSS_DATA_REQ */
    Ss_SndMmssDataReq(ucTi, pucDestMsg, ulCodeLen);

    /* �ͷŸ���Ϣ */
    PS_MEM_FREE(WUEPS_PID_SS, pucDestMsg);

    return VOS_OK;
}



VOS_VOID Ss_RcvMmssEstInd(
                      VOS_VOID *pMsg
                      )
{
    MMSS_EST_IND_STRU      *pEstInd;                                            /* ����ָ��MMSS_EST_IND��Ϣ��ָ��           */
    VOS_UINT8                  *pAirMsg;                                            /* ����ָ��տ���Ϣ��ָ��                   */
    VOS_UINT32                  ulMsgSize;                                           /* ����տ���Ϣ����                         */
    VOS_UINT8                  ucTi;                                                /* ���ڻ�ȡTI                               */
    VOS_UINT8                  ucCr;                                                /* ���ڻ�ȡCR                               */

    ST_SSP_MSG                          stSsMsg;

    pEstInd = ( MMSS_EST_IND_STRU *)pMsg;                                       /* ��ȡMMSS_EST_IND��Ϣָ��                 */
    pAirMsg = pEstInd->SsMsg.aucSsMsg;                                          /* ȡ�ÿտ���Ϣ                             */
    ulMsgSize = pEstInd->SsMsg.ulSsMsgSize;                                     /* ȡ�ÿտ���Ϣ�ó���                       */
    ucTi = ( VOS_UINT8 )( pEstInd->ulTi );                                          /* ȡ��TI                                   */

    if (VOS_OK == LCS_RcvMmlcsMsg(ucTi, pAirMsg))
    {
        Ss_SndMmssRelReq(ucTi);                                                 /* ��MM����MMSS_REL_REQԭ��ͷ�MM����     */
        return;
    }

    /* VSIM��MODEM��NAS��VSIM���Կ��ش򿪣���ܾ����緢���SSҵ�� */
    if (VOS_TRUE == NAS_VSIM_IsRequireVsimCtrl())
    {
        Ss_SndMmssRelReq(ucTi);                                                 
        return;
    }

    if( 0x07 != ( ucTi & 0x07 ))
    {                                                                           /* TI��ӦΪ��111�� */
        if( WUEPS_TRUE == Ss_CheckAirMsg( pMsg ))
        {                                                                       /* ͨ���˿տ���Ϣ���                       */
            /* ͨ��OM��ȡSS�տ���Ϣ */
            NAS_SS_ReportN2MOtaMsg(&pEstInd->SsMsg);

            switch( pAirMsg[1] )
            {                                                                   /* ���տ���Ϣ���ͷַ�                       */
            case SS_MSG_REGISTER:                                               /* REGISTER                                 */
                if( SS_NONE_CR != ( ucCr = Ss_EntityBuildCr( ucTi )))
                {                                                               /* �½�һ��CR                               */
                        Ss_EntityCreat( ucTi, ucCr);                                    /* ����TI��Ӧ��SSʵ��                       */
                    Ss_RcvRegister( pAirMsg, ulMsgSize, ucTi );                 /* ���ö�REGISTER��Ϣ�Ĵ���                 */
                }


                NAS_SS_ChangeSsState(ucTi, SS_S_CONNECTED);

                stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;

                if (stSsMsg.ucCr >= TAF_MT_MIN_CR)
                {
                    stSsMsg.ucCr -= 120;                                        /*Cr��ΧΪ128-134ʱ����Ҫת����TI:8-14*/
                }

                stSsMsg.SspmsgCore.ucChoice = SSA_SS_CS_CONN_IND;

                PS_MEM_SET(&(stSsMsg.SspmsgCore.u.stCsConnInd), 0, sizeof(SSA_SS_CS_CONN_IND_STRU));
                stSsMsg.SspmsgCore.u.stCsConnInd.enConnState = SSA_SS_CS_CONN_STATE_PRESENT;
                SSA_DealMsgFromSS(&stSsMsg);

                break;
            default:                                                            /* �����տ���Ϣ                             */
                Ss_RcvUnknownAirMsg( ucTi );                                    /* ���öԲ���ʶ��Ŀտ���Ϣ�Ĵ���           */
                break;
            }
        }
    }
}



VOS_VOID Ss_RcvMmssDataInd(
                       VOS_VOID *pMsg
                       )
{
    MMSS_DATA_IND_STRU      *pDataInd;                                          /* ����ָ��MMSS_DATA_IND��Ϣ��ָ��          */
    VOS_UINT8                  *pAirMsg;                                            /* ����ָ��տ���Ϣ��ָ��                   */
    VOS_UINT32                  ulMsgSize;                                           /* ����տ���Ϣ����                         */
    VOS_UINT8                  ucTi;                                                /* ���ڻ�ȡTI                               */

    ST_SSP_MSG                          stSsMsg;

    pDataInd = ( MMSS_DATA_IND_STRU *)pMsg;                                     /* ��ȡMMSS_DATA_IND��Ϣָ��                */
    pAirMsg = pDataInd->SsMsg.aucSsMsg;                                         /* ȡ�ÿտ���Ϣ                             */
    ulMsgSize = pDataInd->SsMsg.ulSsMsgSize;                                    /* ȡ�ÿտ���Ϣ�ó���                       */
    ucTi = ( VOS_UINT8 )( pDataInd->ulTi );                                         /* ȡ��TI                                   */

    if (VOS_OK == LCS_RcvMmlcsMsg(ucTi, pAirMsg))
    {
        return;
    }

    if( 0x07 != ( ucTi & 0x07 ))
    {                                                                           /* TI��ӦΪ��111�� */
        if( WUEPS_TRUE == Ss_CheckAirMsg( pMsg ))
        {                                                                       /* ͨ���˿տ���Ϣ���                       */
            /* ͨ��OM��ȡSS�տ���Ϣ */
            NAS_SS_ReportN2MOtaMsg(&pDataInd->SsMsg);


            NAS_SS_ChangeSsState(ucTi, SS_S_CONNECTED);

            stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;

            if (stSsMsg.ucCr >= TAF_MT_MIN_CR)
            {
                stSsMsg.ucCr -= 120;                                        /*Cr��ΧΪ128-134ʱ����Ҫת����TI:8-14*/
            }

            stSsMsg.SspmsgCore.ucChoice = SSA_SS_CS_CONN_IND;

            PS_MEM_SET(&(stSsMsg.SspmsgCore.u.stCsConnInd), 0, sizeof(SSA_SS_CS_CONN_IND_STRU));
            stSsMsg.SspmsgCore.u.stCsConnInd.enConnState = SSA_SS_CS_CONN_STATE_PRESENT;
            SSA_DealMsgFromSS(&stSsMsg);

            switch(pAirMsg[1])
            {                                                                   /* ���տ���Ϣ���ͷַ�                       */
            case SS_MSG_FACILITY:                                               /* FACILITY                                 */
                Ss_RcvFacility( pAirMsg, ulMsgSize, ucTi );                     /* ���ö�FACILITY��Ϣ�Ĵ���                 */
                break;
            case SS_MSG_RELCMPL:                                                /* RELCMPL                                  */
                Ss_RcvRelCmpl( pAirMsg, ulMsgSize, ucTi );                      /* ���ö�RELCMPL��Ϣ�Ĵ���                  */
                break;
            case SS_MSG_REGISTER:                                               /* REGISTER�����䶪��                       */
                break;
            default:                                                            /* �����տ���Ϣ                             */
                Ss_RcvUnknownAirMsg( ucTi );                                    /* ���öԲ���ʶ��Ŀտ���Ϣ�Ĵ���           */
                break;
            }
        }
    }
}


VOS_VOID TAF_SS_ConvertMmssRelCauseToSsassCause(
    NAS_MMCM_REL_CAUSE_ENUM_UINT32      enMmssRelCause,
    SSA_SS_REL_CAUSE_ENUM_UINT32       *penSsCause
)
{
    /* Ŀǰmmss rel cause ��ss ssa rel causeƫ������ͬ��ֱ�Ӹ�ֵ
       ����mmss rel cause����ԭ��ֵ��Ҫͬʱ��ss ssa rel cause���� */
       
    *penSsCause = enMmssRelCause;

    return;
}

VOS_VOID Ss_RcvMmssRelInd(
                      VOS_VOID *pMsg
                      )
{
    MMSS_REL_IND_STRU       *pRelInd;                                           /* ����ָ��MMSS_REL_IND��Ϣ��ָ��           */
    VOS_UINT8                   ucTi;                                               /* ���ڻ�ȡTI                               */
    ST_SSP_MSG               stSsMsg;

    SSA_SS_REL_CAUSE_ENUM_UINT32        enSsCause;

    pRelInd = ( MMSS_REL_IND_STRU *)pMsg;                                       /* ��ȡMMSS_REL_IND��Ϣָ��                 */
    ucTi = ( VOS_UINT8 )( pRelInd->ulTi );                                          /* ȡ��TI                                   */

    TAF_SS_ConvertMmssRelCauseToSsassCause(pRelInd->enMmssRelCause, &enSsCause);

    if( 0x07 != ( ucTi & 0x07 ))
    {                                                                           /* TI��ӦΪ��111�� */
        if ( SS_S_CONNECTED == g_SsEntity[ucTi].ucState )
        {                                                                       /* �ж��Ƿ��������                         */
            stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;                                   /* ����CR                                   */
            if (stSsMsg.ucCr >= TAF_MT_MIN_CR)
            {
                stSsMsg.ucCr -= 120;                                            /*Cr��ΧΪ128-134ʱ����Ҫת����TI:8-14*/
            }
            stSsMsg.SspmsgCore.ucChoice = D_SMC_END_IND;                            /* ������Ϣѡ��                             */

            Ss_MemSet( &(stSsMsg.SspmsgCore.u.EndInd), 0, sizeof( ST_END_IND ));    /* ����Ϣ�ռ�����                           */

            Ss_EntityClear( ucTi );
            SSA_DealMsgFromSS(&stSsMsg);
        }
        else if (SS_S_CONNECT_PEND == g_SsEntity[ucTi].ucState)
        {
            stSsMsg.ucCr = g_SsEntity[ucTi].ucCr;                                   /* ����CR                                   */
            if (stSsMsg.ucCr >= TAF_MT_MIN_CR)
            {
                stSsMsg.ucCr -= 120;                                            /*Cr��ΧΪ128-134ʱ����Ҫת����TI:8-14*/
            }
            stSsMsg.SspmsgCore.ucChoice = D_SMC_END_IND;                            /* ������Ϣѡ��                             */

            Ss_MemSet( &(stSsMsg.SspmsgCore.u.EndInd), 0, sizeof( ST_END_IND ));    /* ����Ϣ�ռ�����                           */

            stSsMsg.SspmsgCore.u.EndInd.OP_Cause = 1;
            stSsMsg.SspmsgCore.u.EndInd.Cause.ulCnt = 2;

            stSsMsg.SspmsgCore.u.EndInd.Cause.Cause[0] = 0x60;
            stSsMsg.SspmsgCore.u.EndInd.Cause.Cause[1] = SS_CAUSE_NORMAL_UNSPECIFIED;
            stSsMsg.SspmsgCore.u.EndInd.enSsaSsRelCause = enSsCause;

            SSA_DealMsgFromSS(&stSsMsg);
            Ss_EntityClear( ucTi );

            Ss_DeleteRegister(ucTi);
        }
        else
        {

        }
    }
}

/***********************************************************************
*  MODULE   : Ss_RcvMmMsg
*  FUNCTION : �ַ�MM��Ϣ
*  INPUT    : VOS_VOID      *pMsg   ��ǰ�������Ϣ
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-08  �°�����
************************************************************************/

VOS_VOID Ss_RcvMmMsg(
                 VOS_VOID *pMsg
                 )
{
    MSG_HEADER_STRU*        pMsgHeader;

    pMsgHeader = (MSG_HEADER_STRU *)pMsg;                                       /* �õ���Ϣͷ                               */

    switch( pMsgHeader->ulMsgName )
    {                                                                           /* ����Ϣ���ͽ��зַ�                       */
    case MMSS_EST_CNF:                                                          /* MMSS_EST_CNF                             */
        Ss_RcvMmssEstCnf(pMsg);                                                 /* ���� MMSS_EST_CNF ��Ϣ������           */
        break;
    case MMSS_EST_IND:                                                          /* MMSS_EST_IND                             */
        Ss_RcvMmssEstInd(pMsg);                                                 /* ���� MMSS_EST_IND ��Ϣ������           */
        break;
    case MMSS_DATA_IND:                                                         /* MMSS_DATA_IND                            */
        Ss_RcvMmssDataInd(pMsg);                                                /* ���� MMSS_DATA_IND ��Ϣ������          */
        break;
    case MMSS_REL_IND:                                                          /* MMSS_REL_IND                             */
        Ss_RcvMmssRelInd(pMsg);                                                 /* ���� MMSS_REL_IND ��Ϣ������           */
        break;
    default:                                                                    /* ����MM��Ϣ                               */
        SS_WARN_LOG( "\n [Error]MM->SS MsgName Error! \r" );
        break;
    }
}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

