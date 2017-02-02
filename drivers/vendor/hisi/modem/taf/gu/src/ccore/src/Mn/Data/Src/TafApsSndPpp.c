

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafApsApi.h"
#include  "MnApsComm.h"
#include  "Taf_Aps.h"
#include  "TafLog.h"
#include  "TafApsCtx.h"
#include  "TafApsComFunc.h"
#include  "TafApsDecode.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include  "taf_aps_ppp_pif.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_PPP_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)


VOS_VOID  TAF_APS_SndPppActReq(
    VOS_UINT8                           ucPdpId
)
{
    APS_PPP_ACT_REQ_STRU               *pstPppActReq;

    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
    TAF_APS_AUTH_INFO_STRU              stAuthInfo;
    VOS_UINT32                          ulResult;

    /* ��ȡ��Ϣ���� */
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    pstAppMsg       = (TAF_PS_MSG_STRU*)(pstEntryMsg->aucEntryMsgBuffer);
    pstCallOrigReq  = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    pstPppActReq    = (APS_PPP_ACT_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_ACT_REQ_STRU));

    if (VOS_NULL_PTR == pstPppActReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppActReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPppActReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_ACT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPppActReq->ulReceiverPid = MSPS_PID_PPPC;
    pstPppActReq->enMsgId       = ID_APS_PPP_ACT_REQ;

    pstPppActReq->ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);

    pstPppActReq->enPdnType     = TAF_APS_GetPdpEntDialPdpType(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* Ŀǰֻ��1X��HRPDģʽ����ҪAPS֪ͨPPPģ�飬��ǰ�Ľ���ģʽ */
    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        pstPppActReq->enMode            = TAF_APS_PPP_RAT_MODE_1X;
    }
    else
    {
        pstPppActReq->enMode            = TAF_APS_PPP_RAT_MODE_HRPD;
    }

    switch(pstEntryMsg->ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ):
            VOS_StrNCpy((VOS_CHAR*)pstPppActReq->aucUserName,
                        (VOS_CHAR*)pstCallOrigReq->stDialParaInfo.aucUserName,
                        TAF_APS_PPP_MAX_AUTHDATA_USERNAME_LEN);

            VOS_StrNCpy((VOS_CHAR*)pstPppActReq->aucPassword,
                        (VOS_CHAR*)pstCallOrigReq->stDialParaInfo.aucPassWord,
                        TAF_APS_PPP_MAX_AUTHDATA_PASSWORD_LEN);

            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ):

            pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU *)(pstAppMsg->aucContent);
            PS_MEM_SET(&stAuthInfo, 0, sizeof(TAF_APS_AUTH_INFO_STRU));

            /* MODEM����ʱ��ֻ֧��PAP���͵ļ�Ȩ */
            if ((VOS_TRUE == pstPppDialOrigReq->stPppDialParaInfo.bitOpPppConfigInfo)
             && (TAF_PDP_AUTH_TYPE_PAP == pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthType))
            {
                ulResult = TAF_APS_DecodePapInfo(&stAuthInfo,
                                                 pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthContent.stPapContent.aucPapReqBuf,
                                                 pstPppDialOrigReq->stPppDialParaInfo.stPppReqConfigInfo.stAuth.enAuthContent.stPapContent.usPapReqLen);

                if (VOS_OK == ulResult)
                {
                    PS_MEM_CPY(pstPppActReq->aucUserName,
                               stAuthInfo.unAuthParam.stPapParam.aucUsername,
                               stAuthInfo.unAuthParam.stPapParam.ucUsernameLen);

                    PS_MEM_CPY(pstPppActReq->aucPassword,
                               stAuthInfo.unAuthParam.stPapParam.aucPassword,
                               stAuthInfo.unAuthParam.stPapParam.ucPasswordLen);
                }
            }

            break;

        default:
            break;
    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstPppActReq);

}
VOS_VOID  TAF_APS_SndPppDeactReq(
    VOS_UINT8                           ucPdpId
)
{
    APS_PPP_DEACT_REQ_STRU             *pstPppDeactReq;

    pstPppDeactReq = (APS_PPP_DEACT_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_DEACT_REQ_STRU));

    if (VOS_NULL_PTR == pstPppDeactReq)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppDeactReq: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPppDeactReq + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_DEACT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPppDeactReq->ulReceiverPid = MSPS_PID_PPPC;
    pstPppDeactReq->enMsgId       = ID_APS_PPP_DEACT_REQ;

    pstPppDeactReq->ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);


    /* Ŀǰֻ��1X��HRPDģʽ����ҪAPS֪ͨPPPģ�飬��ǰ�Ľ���ģʽ */
    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        pstPppDeactReq->enMode          = TAF_APS_PPP_RAT_MODE_1X;
    }
    else
    {
        pstPppDeactReq->enMode          = TAF_APS_PPP_RAT_MODE_HRPD;
    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstPppDeactReq);

}
VOS_VOID  TAF_APS_SndPppDeactInd(
    VOS_UINT8                           ucPdpId
)
{
    APS_PPP_DEACT_IND_STRU             *pstPppDeactInd;

    pstPppDeactInd = (APS_PPP_DEACT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_DEACT_IND_STRU));

    if (VOS_NULL_PTR == pstPppDeactInd)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppDeactInd: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPppDeactInd + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_DEACT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPppDeactInd->ulReceiverPid = MSPS_PID_PPPC;
    pstPppDeactInd->enMsgId       = ID_APS_PPP_DEACT_IND;

    pstPppDeactInd->ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);

    /* Ŀǰֻ��1X��HRPDģʽ����ҪAPS֪ͨPPPģ�飬��ǰ�Ľ���ģʽ */
    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        pstPppDeactInd->enMode          = TAF_APS_PPP_RAT_MODE_1X;
    }
    else
    {
        pstPppDeactInd->enMode          = TAF_APS_PPP_RAT_MODE_HRPD;
    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstPppDeactInd);

}

/* Added by y00314741 for CDMA Iteration 11, 2015-3-27, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_SndPppModeChangeNotify
 ��������  : ֪ͨPPPģ��PPPģʽ�ı�֪ͨ
 �������  : ucPdpId
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��27��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_APS_SndPppModeChangeNotify(
    VOS_UINT8                           ucPdpId
)
{
    APS_PPP_MODE_CHANGE_NTF_STRU       *pstPppModeChangeNty;

    pstPppModeChangeNty = (APS_PPP_MODE_CHANGE_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_MODE_CHANGE_NTF_STRU));

    if (VOS_NULL_PTR == pstPppModeChangeNty)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppModeChangeNotify: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPppModeChangeNty + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_MODE_CHANGE_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPppModeChangeNty->ulReceiverPid = MSPS_PID_PPPC;
    pstPppModeChangeNty->enMsgId       = ID_APS_PPP_MODE_CHANGE_NTF;
    pstPppModeChangeNty->usOpId        = 0;
    pstPppModeChangeNty->ucPdnId       = TAF_APS_GetPdpEntCdataPdnId(ucPdpId);

    /* Ŀǰֻ��1X��HRPDģʽ����ҪAPS֪ͨPPPģ�飬��ǰ�Ľ���ģʽ */
    if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        pstPppModeChangeNty->enMode = TAF_APS_PPP_RAT_MODE_1X;
    }
    else
    {
        pstPppModeChangeNty->enMode = TAF_APS_PPP_RAT_MODE_HRPD;
    }

    PS_SEND_MSG(WUEPS_PID_TAF, pstPppModeChangeNty);

}
/* Added by y00314741 for CDMA Iteration 11, 2015-3-27, end */

/* Added by y00314741 for CDMA Iteration 15, 2015-7-1, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_SndPppModeChangeNotify
 ��������  : ֪ͨPPPģ��AT���õĲ���ģʽ
 �������  : ucPdpId
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��01��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_APS_SndPppDialModeNotify(
    VOS_UINT16                          usClientId
)
{
    APS_PPP_DIAL_MODE_NTF_STRU         *pstDialModeNty;

    pstDialModeNty = (APS_PPP_DIAL_MODE_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_PPP_DIAL_MODE_NTF_STRU));

    if (VOS_NULL_PTR == pstDialModeNty)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndPppDialModeNotify: Memory alloc failed");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstDialModeNty + VOS_MSG_HEAD_LENGTH, 0,
                sizeof(APS_PPP_DIAL_MODE_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    pstDialModeNty->ulReceiverPid        = MSPS_PID_PPPC;
    pstDialModeNty->enMsgId              = ID_APS_PPP_DIAL_MODE_NTF;
    pstDialModeNty->usOpId               = 0;
    pstDialModeNty->usClientId           = usClientId;
    pstDialModeNty->enDialMode           = (VOS_UINT8)TAF_APS_GetFsmCtxCdataDialMode();

    PS_SEND_MSG(WUEPS_PID_TAF, pstDialModeNty);

}
/* Added by y00314741 for CDMA Iteration 15, 2015-7-1, end */

#endif






#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
