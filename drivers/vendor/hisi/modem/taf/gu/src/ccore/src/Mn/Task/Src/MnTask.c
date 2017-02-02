

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"
#include "vos.h"
#include "Taf_Tafm_Remote.h"
#include "UsimPsInterface.h"
#include "Ssa_Define.h"
#include "MnCall.h"
#include "Taf_Aps.h"
/* ɾ��ExtAppMmcInterface.h*/
#include "TafMmcInterface.h"
#include "MnMsgExt.h"
#include "UsimPsInterface.h"
#include "MnComm.h"
#include "siapppih.h"
#include "MnCallTimer.h"
#include "RabmTafInterface.h"
#include "MmaAppLocal.h"
#include "TafDrvAgentMain.h"
#include "MnCallReqProc.h"
#include "TafApsMain.h"
#include "MnCallCtx.h"
#include "MnCallProcNvim.h"

#include "NasUtranCtrlCommFunc.h"
#include "NasUtranCtrlInterface.h"

#include "TafMtaMain.h"

#include "TafSdcCtx.h"
#include "TafSpmMain.h"
#include "MnMsgSmCommProc.h"

#include "NasUsimmApi.h"

#include "TafCbaProcUsim.h"

#include "MnCallImsaProc.h"
#include "TafMntn.h"

#include "TafCsCallMain.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "xcc_taf_pif.h"
#include "TafXCallMain.h"
#include "TafXpdsMain.h"
#endif


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

extern VOS_VOID R_ITF_InitFlowCtrl(VOS_VOID);


#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_TASK_C

VOS_VOID MN_MSG_RecurDataRestore(
    struct MsgCB                        *pstAppMsg
);

extern VOS_UINT32 TAF_XSMS_PidInit(enum VOS_INIT_PHASE_DEFINE  ip);
extern VOS_VOID TAF_XSMS_PidMsgProc(MsgBlock* pstMsg);

VOS_UINT8                               g_ucMnOmConnectFlg       = VOS_FALSE;   /* UE��PC���ߵ����ӱ�־, VOS_TRUE: ������; VOS_FALSE: δ���� */
VOS_UINT8                               g_ucMnOmPcRecurEnableFlg = VOS_FALSE;   /* PC�������õķ���NAS PC�ط���Ϣ��ʹ�ܱ�־ */
MN_STK_MSG_FUNC_MAP_STRU                g_astTafStkMsgFuncMap[] =
{
    {STK_MSG_SEND_REQ,         MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT, MN_MSG_ProcAppSend},
    {STK_CALL_START_DTMF_REQ,  MN_CALL_APP_START_DTMF_REQ,        TAF_CALL_RcvStartDtmfReq},
    {STK_CALL_STOP_DTMF_REQ,   MN_CALL_APP_STOP_DTMF_REQ,         TAF_CALL_RcvStopDtmfReq},
    {STK_CALL_CALLORIG_REQ,    MN_CALL_APP_ORIG_REQ,              MN_CALL_StkCallOrigReqProc},
    {STK_CALL_SUPS_CMD_REQ,    MN_CALL_APP_SUPS_CMD_REQ,          MN_CALL_CallSupsCmdReqProc},
    {STK_SS_REGISTERSS_REQ,    TAF_MSG_REGISTERSS_MSG,            MN_SndAppMsgToSs},
    {STK_SS_ERASESS_REQ,       TAF_MSG_ERASESS_MSG,               MN_SndAppMsgToSs},
    {STK_SS_ACTIVATESS_REQ,    TAF_MSG_ACTIVATESS_MSG,            MN_SndAppMsgToSs},
    {STK_SS_DEACTIVATESS_REQ,  TAF_MSG_DEACTIVATESS_MSG,          MN_SndAppMsgToSs},
    {STK_SS_INTERROGATESS_REQ, TAF_MSG_INTERROGATESS_MSG,         MN_SndAppMsgToSs},
    {STK_SS_REGPWD_REQ,        TAF_MSG_REGPWD_MSG,                MN_SndAppMsgToSs},
    {STK_SS_USSD_REQ,          TAF_MSG_PROCESS_USS_MSG,           MN_SndAppMsgToSs},
    {SI_STK_ENVELOPE_CNF,    SI_STK_ENVELOPE_CNF,              TAF_ProcStkEnvelopeCnf}
};

/*****************************************************************************
   2 ����ʵ��
*****************************************************************************/


VOS_UINT32  MN_Init(enum VOS_INIT_PHASE_DEFINE  ip)
{
    TAF_SDC_CTX_STRU                    *pstSdcCtx = VOS_NULL_PTR;

    switch( ip )
    {
    case VOS_IP_INITIAL:

        NAS_PIHAPI_RegCardRefreshIndMsg(WUEPS_PID_TAF);

        pstSdcCtx = TAF_SDC_GetSdcCtx();
        TAF_SDC_InitCtx(TAF_SDC_INIT_CTX_STARTUP, pstSdcCtx);

        /* ��ʼ��CCA */
        MN_CALL_Init(MN_CALL_POWER_STATE_ON);

        /* ��ʼ��SMA */
        MN_MSG_Init();

        /* ��ʼ��APS */
        Aps_Init();

        TAF_SPM_Init();

        /* ��ʼ��SSA */
        SSA_Init();
        /* ��ʼ��GNA */

        /* �Ѿ���lijun,hefeng,xiamiaofangȷ�ϣ�����ɾ�����س�ʼ�� */

        TAF_CSCALL_Init(TAF_CSCALL_INIT_TYPE_STARTUP);

        break;

    default:
        break;
    }

    return VOS_OK;
}

VOS_VOID Taf_ProcCallCtrlAllowNoModification(struct MsgCB * pstMsg)
{
/*
    switch ��������
        case ����:
        if (�ҵ�����CCA_CALL_CTRL_PROCEEDING״̬�ĺ���ʵ��)
        {
            ��Call Control״̬����ΪCCA_CALL_CTRL_END
            ����Cca_CallOrigReqProc
        }
        break;

        #if 0
        case ����ҵ��:
        ����
        break;

        case ����:
        ����
        break;
        #endif

        default:
        break;
*/
}


VOS_VOID Taf_ProcCallCtrlNotAllow(struct MsgCB * pstMsg)
{
/*
    switch ��������
        case ����:
            �����Ӧ��CCA״̬��:
            �ϱ��¼�������ֵΪTAF_ERR_CALL_CONTROL_REJECTED
            break;

        case ����ҵ��:
        case USSDҵ��:
            �����Ӧ��SSA״̬��
            �ϱ��¼�������ֵΪTAF_ERR_CALL_CONTROL_REJECTED
            break;

        case ����:
            �����Ӧ��APS״̬��
            �ϱ��¼�������ֵΪTAF_ERR_CALL_CONTROL_REJECTED
            break;

        default:
            break;

*/

}

VOS_VOID Taf_ProcCallCtrlAllowWithModification(struct MsgCB * pstMsg)
{

/*
    ��������ת������

    switch ��������
        case ����:
            if (�ҵ�����CCA_CALL_CTRL_PROCEEDING״̬�ĺ���ʵ��)
            {
                ���¶�Ӧʵ���״̬��Ϣ
                ����Cca_CallOrigReqProc
            }
            break;

        case ����ҵ��:
        case USSDҵ��:
            if (֮ǰ�Ĳ����ǲ�����SSA�����Call control����)
            {
                ��ն�Ӧ�������ʵ���״̬(CCA����APS)
            }

            ���ù���������(MMI�ִ������������ú�����ʵ�ַ�ʽ����,
                             ��CCA������ɺ�����ȷ��)
            ����SSA�Ľӿ�(�˴�����Ҫ�����°��SSA��ʵ�ַ�ʽ��ȷ��)
            break;

        case ����:
            ����APS��PDP����ӿ�(�˴�����Ҫ�����°��APS��ʵ�ַ�ʽ��ȷ��)
            break;

        default:
            break;

    �ϱ��¼�����֪Ӧ������call control��ԭ�򣬺��з����˸ı�

*/
}

/*****************************************************************************
 �� �� ��  : Taf_ProcSimaMsg
 ��������  : ��������Sima����Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��10��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  Taf_ProcSimaMsg (struct MsgCB * pstMsg)
{
/*
    switch (��������)
        #ifdef hw_feature_call_control
        case ����Ϊcall control:
        {
            switch (result)
            {
                case �������޸�:
                    ����Taf_ProcCallCtrlAllowNoModification
                    break;

                case ������:
                    ����Taf_ProcCallCtrlNotAllow
                    break;

                case �����޸�:
                    ����Taf_ProcCallCtrlAllowWithModification
                    break;

                default:
                    break;
            }
        }
        break;
        #endif

        default:
        break;

*/
}


VOS_VOID  MN_ProcTimerMsg (struct MsgCB * pstMsg)
{
    REL_TIMER_MSG * pstTmrMsg = (REL_TIMER_MSG *)pstMsg;

    switch (pstTmrMsg->ulName & MN_TIMER_CLASS_MASK)
    {
    case MN_TIMER_CLASS_CCA:
    case MN_TIMER_CLASS_XCALL:
        TAF_CSCALL_ProcTimerOutMsg((REL_TIMER_MSG *)pstMsg);
        break;

    case MN_TIMER_CLASS_MSG:
        /* ����SMA�Ķ�ʱ����Ϣ������ */
        MN_MSG_ProcTimeoutMsg((REL_TIMER_MSG *)pstMsg);
        break;

    case MN_TIMER_CLASS_SSA:
        /* ����SSA�Ķ�ʱ����Ϣ������ */
        break;

    case MN_TIMER_CLASS_MMA:
        /* ����MMA�Ķ�ʱ����Ϣ������ */
        break;

    case MN_TIMER_CLASS_APS:
        TAF_APS_ProcMsg(pstMsg);
        break;

    default:
        MN_ERR_LOG("MN_ProcTimerMsg: Unknown timer class.");
        break;
    }
}

/* ɾ��ԭ MN_GetUsimMsgClient�ӿں��� */


VOS_UINT32 MN_GetUsimMsgServerType(struct MsgCB * pstMsg)
{
    VOS_UINT32                          ulServerType;
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */

    /*��USIM��������Ϣ�г�ȡҵ������,����FDN IND��Ϣ��Ҫ MSG �� CALLģ�鴦��*/
    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
        /* �޸���FDN���ظ��Ľṹ,SSʹ��client ID,CALL/MSG��Ҫʹ��client ID�ж� */
        case SI_PB_EVENT_FDNCHECK_CNF:
            ulServerType  = TAF_SERVICE_TYPE_UNASSIGNED;
            break;

        case USIMM_READFILE_CNF:
            ulServerType  = TAF_SERVICE_TYPE_UNASSIGNED;
            break;

        case SI_STK_ENVELOPE_CNF:
            /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
            pstEnvelope = (SI_STK_ENVELOPEDWON_CNF_STRU *)pstMsg;
            if (SI_STK_ENVELOPE_CALLCRTL == pstEnvelope->enEnvelopeType)
            /* Modified by h00313353 for iteration 9, 2015-2-13, end */
            {
                ulServerType  = TAF_SERVICE_TYPE_CALL;
            }
            else
            {
                ulServerType  = TAF_SERVICE_TYPE_MSG;
            }
            break;
        default:
            ulServerType  = TAF_SERVICE_TYPE_MSG;
            break;
    }
    return ulServerType;
}

VOS_VOID  MN_ProcUsimMsg (struct MsgCB * pstMsg)
{
    VOS_UINT32                          ulServerType;

    ulServerType = MN_GetUsimMsgServerType(pstMsg);

    /* ����ulClient��USIM��Ϣ�ַ�����ҵ����Ŀǰ������ҵ����ģ�� */
    switch(ulServerType)
    {
        case TAF_SERVICE_TYPE_MSG:
            MN_MSG_DispatchUsimMsg(pstMsg);
            break;

        case TAF_SERVICE_TYPE_CALL:
            TAF_CSCALL_ProcUsimMsg(pstMsg);
            break;

        case TAF_SERVICE_TYPE_UNASSIGNED:
            MN_MSG_DispatchUsimMsg(pstMsg);
            TAF_CSCALL_ProcUsimMsg(pstMsg);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            TAF_APS_ProcUsimMsg(pstMsg);
#endif
            break;

        default:
            MN_WARN_LOG("MN_ProcUsimMsg: Rcv Invalid ulClient.");
            break;

    }
    return;
}
VOS_VOID  MN_ProcPihMsg (struct MsgCB * pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    if (USIMM_STKREFRESH_IND == pstMsgHeader->ulMsgName)
    {
        /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
        TAF_CBA_ProcRefreshInd((USIMM_STKREFRESH_IND_STRU *)pstMsgHeader);
        MN_MSG_RcvUsimRefreshInd((USIMM_STKREFRESH_IND_STRU *)pstMsgHeader);
        /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    }

    return;
}


VOS_VOID  MN_ProcMmcMsg (struct MsgCB * pstMsg)
{
    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
        case TAFMMC_CBS_NO_NETWORK_IND:
        case TAFMMC_CBS_CURR_NET_MODE_IND:
            TAF_CBA_MsgProc(pstMsg);
            break;
#endif

        case TAFMMC_APS_SERVICE_STATE_IND:
            TAF_APS_ProcMsg(pstMsg);
            break;

        default:
            MN_WARN_LOG("MN_ProcMmcMsg:Rcv Invalid Msg Type");
            break;
    }
}


VOS_VOID  MN_ProcOmMsg (struct MsgCB * pstMsg)
{
    ID_NAS_OM_INQUIRE_STRU              *pstOmInquire;

    pstOmInquire = (ID_NAS_OM_INQUIRE_STRU *)pstMsg;

    switch ( pstOmInquire->ulMsgId)
    {
        case ID_NAS_OM_SET_CODEC_TYPE_REQUIRE :
        case ID_NAS_OM_CODEC_TYPE_INQUIRE :
            MN_CALL_ProcOmMsg(pstMsg);
            break;
        case ID_NAS_OM_SET_DSFLOW_RPT_REQ :
            TAF_APS_ProcMsg(pstMsg);
            break;
        default:
            MN_NORM_LOG("MN_CALL_ProcOmMsg:wrong PrimId!");
            break;
    }

    return;
}

/* begin V7R1 PhaseI Modify */

VOS_VOID MN_ProcUsimStatus(
    struct MsgCB                        * pstMsg
)
{
    MNPH_USIM_STATUS_IND_STRU           *pstUsimStatus;
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();

    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSS_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMS_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSP_ID, VOS_TRUE);
    MN_MSG_SetSmsFileRefreshFlag(USIMM_USIM_EFSMSR_ID, VOS_TRUE);

    pstUsimStatus = (MNPH_USIM_STATUS_IND_STRU *)pstMsg;
    MN_MSG_CfgDataInit(pstUsimStatus->enUsimStatus);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

    TAF_CBA_MsgProc(pstMsg);

#endif

    if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucAlsSupportFlg )
    {
        MN_CALL_LineInfo(pstUsimStatus->enUsimStatus);
    }

    /* ��PID init��ȡ�����ؽ�nv��ʱ���ж��Ƿ��ǲ��Կ�������������ʱ�����⵼���жϽ������
       ���������ʱ�ٶ�����һ�ζ�ȡNV�ĺ������ں������ж��Ƿ��ǲ��Կ� */
    MN_CALL_ReadCallRedialCfgNvim();

    /* Added by n00355355 for User_Exp_Improve, 2015-8-24, begin */
    MN_CALL_ReadCallRedialCmSrvRejCfgNvim();
    /* Added by n00355355 for User_Exp_Improve, 2015-8-24, end */

    /* ��PID init��ȡss�ؽ�nv��ʱ���ж��Ƿ��ǲ��Կ�������������ʱ������usimδ��ʼ����������usim�ӿ�
       ��ȡ�Ƿ��ǲ��Կ����ز�׼�����жϽ���������������ʱ�ٶ�����һ�ζ�ȡNV�ĺ�����
       �ں������ж��Ƿ��ǲ��Կ� */
    TAF_SSA_ReadSsRetryCfgNvim();

    /* Added by n00355355 for User_Exp_Improve, 2015-8-24, begin */
    TAF_SSA_ReadSsRetryCmSrvRejCfgNvim();
    /* Added by n00355355 for User_Exp_Improve, 2015-8-24, end */

}
/* end V7R1 PhaseI Modify */

#ifndef __PS_WIN32_RECUR__
VOS_VOID TAF_RcvMmaOmMaintainInfoInd(
    struct MsgCB                       *pstMsg
)
{
    MMCM_OM_MAINTAIN_INFO_IND_STRU     *pstOmMaintainInfo;

    pstOmMaintainInfo = (MMCM_OM_MAINTAIN_INFO_IND_STRU*)pstMsg;

    /* ����ȫ�ֱ�����ֵ */
    g_ucMnOmConnectFlg       = pstOmMaintainInfo->ucOmConnectFlg;
    g_ucMnOmPcRecurEnableFlg = pstOmMaintainInfo->ucOmPcRecurEnableFlg;

    if ( (VOS_TRUE == g_ucMnOmConnectFlg)
      && (VOS_TRUE == g_ucMnOmPcRecurEnableFlg) )
    {
        NAS_MSG_SndOutsideContextData_Part1();
        NAS_MSG_SndOutsideContextData_Part2();
        NAS_MSG_SndOutsideContextData_Part3();
    }
}
#endif
VOS_VOID  MN_ProcMmaMsg (
    struct MsgCB                        *pstMsg
)
{
    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
/* begin V7R1 PhaseI Modify */
    case MN_USIM_STATUS_IND:
        MN_ProcUsimStatus(pstMsg);
        break;

#ifndef __PS_WIN32_RECUR__
        case MMCM_OM_MAINTAIN_INFO_IND:
            TAF_RcvMmaOmMaintainInfoInd(pstMsg);

            break;
#endif
/* end V7R1 PhaseI Modify */

        case ID_MMA_MSG_CS_SERVICE_CHANGE_NOTIFY:
            TAF_MSG_RcvMmaCsServiceChangeNotify(pstMsg);
            break;

        case MMA_TAF_POWER_OFF_IND:
            Aps_PowerOff();
            TAF_CSCALL_ProcMmaMsg(pstMsg);
            break;

        case ID_MMA_TAF_POWER_ON_IND:

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            TAF_APS_ProcMsg(pstMsg);
#endif

            TAF_CSCALL_ProcMmaMsg(pstMsg);
            break;

        case ID_MMA_APS_EPDSZID_INFO_IND:

            TAF_APS_ProcMsg(pstMsg);
            break;

        case ID_MMA_TAF_1X_SERVICE_STATUS_IND:
            TAF_CSCALL_ProcMmaMsg(pstMsg);
            TAF_APS_ProcMsg(pstMsg);

            break;

        case ID_MMA_APS_CL_SERVICE_STATUS_IND:
            TAF_APS_ProcMsg(pstMsg);
            break;

        default:
            MN_WARN_LOG("MN_ProcMmaMsg:Rcv Invalid Msg Type");
            break;
    }
}
VOS_VOID  MN_SndAppMsgToSs (struct MsgCB *pstMsg)
{
    MN_APP_REQ_MSG_STRU                *pstSsMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulMsgLen;
    MN_APP_REQ_MSG_STRU                *pstAppMsg = VOS_NULL_PTR;

    pstAppMsg   = (MN_APP_REQ_MSG_STRU *)pstMsg;
    ulMsgLen    = pstAppMsg->ulLength;

    /* ������Ϣ */
    pstSsMsg = (MN_APP_REQ_MSG_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF, ulMsgLen);

    if (VOS_NULL_PTR == pstSsMsg)
    {
        MN_WARN_LOG("MN_SndAppMsgToSs: alloc msg fail!");

        return;
    }

    PS_MEM_CPY( ((VOS_UINT8 *)pstSsMsg + VOS_MSG_HEAD_LENGTH), ((VOS_UINT8 *)pstAppMsg+ VOS_MSG_HEAD_LENGTH), ulMsgLen);

    /* �����Ϣͷ */
    pstSsMsg->ulReceiverPid = WUEPS_PID_SS;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstSsMsg);

    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_SndAppMsgToSs: send msg fail!");
        return;
    }

    return;
}



VOS_VOID TAF_ProcStkEnvelopeCnf(struct MsgCB * pstMsg)
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    SI_STK_ENVELOPEDWON_CNF_STRU       *pstEnvelope = VOS_NULL_PTR;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */

    pstEnvelope = (SI_STK_ENVELOPEDWON_CNF_STRU *)pstMsg;

    /* Modified by h00313353 for iteration 9, 2015-2-13, begin */
    if (SI_STK_ENVELOPE_CALLCRTL != pstEnvelope->enEnvelopeType)
    /* Modified by h00313353 for iteration 9, 2015-2-13, end */
    {
        MN_MSG_RcvUsimEnvelopeCnf(pstMsg);
    }

    return;
}


VOS_VOID MN_DispatchStkMsg(struct MsgCB * pstMsg)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulFuncNum;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    TAF_STK_MSG_FUNC_MAP                pStkMsgFunc = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    ulFuncNum = sizeof(g_astTafStkMsgFuncMap) / sizeof(g_astTafStkMsgFuncMap[0]);

    for (ulLoop = 0; ulLoop < ulFuncNum; ulLoop ++ )
    {
        if (pstMsgHeader->ulMsgName == g_astTafStkMsgFuncMap[ulLoop].ulMsgName)
        {
            pStkMsgFunc             = g_astTafStkMsgFuncMap[ulLoop].pStkMsgFunc;

            /*
                 �����������������ԴPID����STK��ҵ������ṹ��AT��һ�£���Ϣ����һ�£�
                 ��Ϊ�������жϵ���Ϣ������AT����Ϣ�������ｫSTK����Ϣ������ΪAPP����Ϣ��
              */
            pstMsgHeader->ulMsgName = g_astTafStkMsgFuncMap[ulLoop].ulAppMsgName;
            break;
        }
    }

    if (VOS_NULL_PTR == pStkMsgFunc)
    {
        MN_WARN_LOG("MN_DispatchStkMsg: Invalid Msg Name");
        return;
    }

    pStkMsgFunc(pstMsg);

    return;

}


VOS_VOID  MN_DispatchTafMsg (struct MsgCB * pstMsg)
{
    /* TAF->TAF����Ϣ����һ��ͳһ�Ľṹ��,ȡ����Ϣ�ֶ� */
    TAF_INTERNAL_MSG_STRU              *pstTafMsg = VOS_NULL_PTR;

    pstTafMsg = (TAF_INTERNAL_MSG_STRU *)pstMsg;

    switch (pstTafMsg->ulMsgId & ID_TAF_MNTN_MSG_MASK)
    {
        /* ����APS API����Ϣ����APS���� */
        case ID_TAF_APS_INTERNAL_BASE:
            TAF_APS_ProcMsg(pstMsg);
            break;

        /* ���͸�MSG����Ϣ��MSG���� */
        /* Ŀǰֻ��ID_TAF_SPM_SMMA_REQ,MSG�ȷ��͵�SPM������ѡ��,��ѡ��֮���ٵ�MSG���� */
        case ID_TAF_MSG_INTERNAL_BASE:
            TAF_MSG_ProcTafMsg(pstMsg);
            break;

        case ID_TAF_CALL_INTERNAL_BASE:
            TAF_CALL_ProcTafMsg(pstMsg);
            break;

        /* ������Ϣ����Ҫ���� */
        default:
            MN_NORM_LOG("MN_DispatchTafMsg: Unknown message type.");
            break;
    }

    return;
}
VOS_VOID  MN_DispatchAppMsg (struct MsgCB * pstMsg)
{
    MN_APP_REQ_MSG_STRU * pstAppMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    switch (pstAppMsg->usMsgName & MN_APP_MSG_CLASS_MASK)
    {
    case MN_APP_MSG_CLASS_CALL:
        TAF_CSCALL_ProcAppReqMsg(pstMsg);
        break;

    case MN_APP_MSG_CLASS_MSG:
        /* ����SMA API����Ϣ������SMA���� */
        MN_MSG_ProcAppReqMsg(pstAppMsg);
        break;

    case MN_APP_MSG_CLASS_SSA:
        /* ����SSA API����Ϣ������SSA���� */
        MN_SndAppMsgToSs(pstMsg);
        break;

    case MN_APP_MSG_CLASS_MMA:
        /* ����MMA API����Ϣ������MMA���� */
        break;

    /* �Ƶ�MN_DispatchTafMsg�д��� */

    case MN_APP_MSG_CLASS_QRY:
        /* AT��MNģ����ѯ���������Ϣ */

        break;

    default:
        MN_ERR_LOG("MN_DispatchAppMsg: Unknown message type.");
        break;
    }
}
VOS_VOID  MN_DispatchRabmMsg (
    VOS_VOID                            *pstMsg
)
{
    MN_RABM_IND_MSG_STRU                *pstRabmMsg;

    pstRabmMsg = (MN_RABM_IND_MSG_STRU *)pstMsg;

    /* ����RABM������Ϣ��APS��CALL����ģ����д�����MsgName��ȡֵ��Χ
       ��RABM��CALL֮��Ķ����ʱ����������������������ԭ�к������� */
    if (pstRabmMsg->usMsgName > RABM_CALL_MSG_CLASS_BASE)
    {
        MN_CALL_ProcRabmCallPrimitive(pstRabmMsg);
        return;
    }

    TAF_APS_ProcMsg((struct MsgCB *)pstMsg);

}

#if (FEATURE_IMS == FEATURE_ON)

VOS_VOID MN_DispatchImsaMsg (
    VOS_VOID                           *pMsg
)
{
    MSG_HEADER_STRU                   *pstImsaMsg = VOS_NULL_PTR;

    pstImsaMsg = (MSG_HEADER_STRU *)pMsg;

    switch (pstImsaMsg->ulMsgName & TAF_IMSA_MSG_MASK)
    {
        case TAF_MSG_IMSA_MSG_BASE:
            /* ��������IMSA��SMS��MSG */
            TAF_MSG_ProcImsaMsg(pstImsaMsg);
            break;

        case TAF_CALL_IMSA_MSG_BASE:
            TAF_CALL_ProcImsaMsg(pstImsaMsg);
            break;

        default:
            break;
    }
}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID  MN_DispatchXccMsg (struct MsgCB * pstMsg)
{
    /* XCC->TAF����Ϣ����һ��ͳһ�Ľṹ��,ȡ����Ϣ�ֶ� */
    MSG_HEADER_STRU                    *pstTafMsg = VOS_NULL_PTR;

    pstTafMsg = (MSG_HEADER_STRU *)pstMsg;

    switch (pstTafMsg->ulMsgName & TAF_XCC_TAF_MSG_MASK)
    {
        /* ����APS API����Ϣ����APS���� */
        case TAF_XCC_APS_MSG_BASE:
            TAF_APS_ProcMsg(pstMsg);
            break;

        case TAF_XCC_XCALL_MSG_BASE:
            TAF_XCALL_ProcXccMsg(pstMsg);
            break;

        /* ������Ϣ����Ҫ���� */
        default:
            MN_NORM_LOG("MN_DispatchXccMsg: Unknown message type.");
            break;
    }

    return;
}
#endif


VOS_VOID  MN_DispatchMsg (struct MsgCB * pstMsg)
{
    struct MsgCB                      *pstSrcMsg = VOS_NULL_PTR;
    struct MsgCB                      *pstDestMsg = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    if (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
    {
        /* svlte���Կ���ʱ��modem1�����յ�usim0����Ϣ����Ҫ����Ϣ��send pid����ת�� */
        pstMsg->ulSenderPid = TAF_SDC_ConvertOamSendPid(pstMsg->ulSenderPid);
    }


    /* ֧��TD-SCDMA����ʱ�������Ϣ�������䴦�� */
    if ( VOS_TRUE == NAS_UTRANCTRL_MsgProc(pstMsg, &pstDestMsg) )
    {
        /* ��Ϣ��UTRANCTRLģ�鴦����ɣ�ֱ�ӷ��أ�������������� */
        return;
    }

    pstSrcMsg = pstDestMsg;

    if (VOS_TRUE == TAF_SPM_MsgProc(pstSrcMsg, &pstDestMsg))
    {
        /* ��Ϣ��SPMģ�鴦�����,ֱ�ӷ���,����Ҫ����������� */
        return;
    }

    /* �滻��Ϣָ�� */
    switch (pstDestMsg->ulSenderPid)
    {
    case VOS_PID_TIMER:
        MN_ProcTimerMsg(pstDestMsg);
        break;

    case UEPS_PID_CST:
        MN_CALL_ProcCstCallPrimitive(pstDestMsg);
        break;

    case MAPS_STK_PID:
        MN_DispatchStkMsg(pstDestMsg);
        break;

    case WUEPS_PID_TAF:
        MN_DispatchTafMsg(pstDestMsg);
        break;

    case WUEPS_PID_AT:
        MN_DispatchAppMsg(pstDestMsg);
        break;

    case WUEPS_PID_CC:
        MN_CALL_ProcMnccPrimMsg(pstDestMsg);
        break;

    case WUEPS_PID_MMC:
        MN_ProcMmcMsg(pstDestMsg);
        break;

    case WUEPS_PID_MMA:
        MN_ProcMmaMsg(pstDestMsg);
        break;

    case WUEPS_PID_MM:
        break;

    case WUEPS_PID_SS:
        break;

    case WUEPS_PID_SMS:
        MN_MSG_ProcSmsMsg((VOS_VOID*)pstDestMsg);
        break;

#if (FEATURE_IMS == FEATURE_ON)
    case PS_PID_IMSA:
        MN_DispatchImsaMsg((VOS_VOID*)pstDestMsg);
        break;
#endif

    case WUEPS_PID_SM:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

#if (FEATURE_ON == FEATURE_LTE)
    case PS_PID_ESM:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

    case MSP_L4_L4A_PID:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

#endif

    case WUEPS_PID_RABM:
        MN_DispatchRabmMsg(pstDestMsg);
        break;

    case UEPS_PID_SN:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

    case WUEPS_PID_USIM:
    case MAPS_PB_PID:
        MN_ProcUsimMsg(pstDestMsg);
        break;
    case MAPS_PIH_PID:
        MN_ProcPihMsg(pstDestMsg);
        break;

    case MSP_PID_DIAG_APP_AGENT:
        MN_ProcOmMsg(pstDestMsg);
        break;

    case WUEPS_PID_VC:
         TAF_CSCALL_ProcVcMsg(pstDestMsg);
        break;


#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    case UEPS_PID_GAS:
    case WUEPS_PID_BMC:
#if (FEATURE_ON == FEATURE_LTE)
    case PS_PID_ERRC:
#endif
    case WUEPS_PID_WRR:
        TAF_CBA_MsgProc(pstDestMsg);
        break;

#endif

    case UEPS_PID_NDCLIENT:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

    case ACPU_PID_TAFAGENT:
        TAF_APS_ProcMsg(pstDestMsg);
        break;


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    case UEPS_PID_XCC:
        MN_DispatchXccMsg(pstMsg);
        break;

    case MSPS_PID_PPPC:
        TAF_APS_ProcMsg(pstDestMsg);
        break;

    case UEPS_PID_CDS:
        TAF_APS_ProcMsg(pstDestMsg);
        break;


    case UEPS_PID_XREG:
        TAF_APS_ProcMsg(pstDestMsg);
        break;
    case UEPS_PID_HSM:
        TAF_APS_ProcMsg(pstMsg);
        break;

    /* Added by y00314741 for CDMA Iteration 15, 2015-6-8, begin */
    case UEPS_PID_DHCP:
        TAF_APS_ProcMsg(pstMsg);
        break;

    case UEPS_PID_EHSM:
        TAF_APS_ProcMsg(pstMsg);
        break;
    /* Added by y00314741 for CDMA Iteration 15, 2015-6-8, end */
#endif
    default:
        MN_ERR_LOG1("MN_DispatchMsg: Unknown message sender, SenderPid, ", (VOS_INT32)pstMsg->ulSenderPid);
        break;
    }
}


/*****************************************************************************
 �� �� ��  : WuepsTafFidInit
 ��������  : ��ʼ��TAF FID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��10��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
/* Deleted by wx270776 for OM�ں�, 2015-7-16, begin */
/* Deleted by wx270776 for OM�ں�, 2015-7-16, end */

extern VOS_UINT32 WuepsVCPidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_VOID  APP_VC_MsgProc(MsgBlock* pMsg);

#if (VOS_WIN32 == VOS_OS_VER)
extern VOS_VOID   At_MsgProc(MsgBlock* pMsg);
extern VOS_UINT32 At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
#endif


VOS_UINT32 WuepsTafFidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{

    VOS_UINT32 ulRslt = VOS_OK;

    switch( ip )
    {
        case   VOS_IP_LOAD_CONFIG:
            /* Deleted by wx270776 for OM�ں�, 2015-7-16, begin */

            /* Deleted by wx270776 for OM�ں�, 2015-7-16, end */

            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_TAF,
                                        (Init_Fun_Type) MN_Init,
                                        (Msg_Fun_Type) MN_DispatchMsg  );
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_VC,
                                         (Init_Fun_Type)WuepsVCPidInit,
                                         (Msg_Fun_Type)APP_VC_MsgProc  );
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_DRV_AGENT,
                                         (Init_Fun_Type)DRVAGENT_Init,
                                         (Msg_Fun_Type)DRVAGENT_DispatchMsg  );
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            /* Added by h00300778 for 1XSMS Project��2014-11-02,  Begin*/
            ulRslt = VOS_RegisterPIDInfo(UEPS_PID_XSMS,
                                         (Init_Fun_Type)TAF_XSMS_PidInit,
                                         (Msg_Fun_Type)TAF_XSMS_PidMsgProc);

            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }
            #endif
            /* Added by h00300778 for 1XSMS Project��2014-11-02,  End*/

            #if (VOS_WIN32 == VOS_OS_VER)
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_AT,
                                         (Init_Fun_Type)At_PidInit,
                                         (Msg_Fun_Type)At_MsgProc);

            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }
            #endif


            ulRslt = VOS_RegisterMsgTaskPrio(WUEPS_FID_TAF, VOS_PRIORITY_M5);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterPIDInfo(UEPS_PID_MTA,
                                        (Init_Fun_Type)TAF_MTA_InitPid,
                                        (Msg_Fun_Type)TAF_MTA_ProcMsg );
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))
            ulRslt = VOS_RegisterPIDInfo(UEPS_PID_XPDS,
                                        (Init_Fun_Type)TAF_XPDS_InitPid,
                                        (Msg_Fun_Type)TAF_XPDS_MsgProc );
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }
#endif
            break;

        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
    }

    return VOS_OK;
}


#ifdef  __cplusplus
#if  __cplusplus
}
#endif
#endif

