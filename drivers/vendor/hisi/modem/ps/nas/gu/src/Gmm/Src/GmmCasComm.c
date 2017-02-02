

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasSuspend.h"
#include "GmmCasSend.h"
#include "GmmCasComm.h"
#include "GmmCasMain.h"
#include "GmmCasGsm.h"
#include "GmmMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "NasCommDef.h"
#include "NasGmmProcLResult.h"
#endif
#include "NasUsimmApi.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASCOMM_C

/* ENd:   Added by liurui id:40632, 2006/7/26   PN:A32D03975 */

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/*lint -save -e958 */

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/*---------------3.1 GMM CAS ͨ�ù��̴���   -------------*/
/*=======================================================*/

/*****************************************************************************
 Prototype      : GMM_IsCasGsmMode
 Description    : �жϵ�ǰ����ģʽ�Ƿ�GSM����
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   : GMM_TRUE       GSM�������
                  GMM_FALSE      ��GSM�������
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT8 GMM_IsCasGsmMode (VOS_VOID)
{
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        return GMM_TRUE;
    }
    else
    {
        return GMM_FALSE;
    }
}

/*****************************************************************************
 Prototype      : GMM_IsLastRand
 Description    : �ж��´��RAND���ϴμ�¼ֵ�Ƿ����
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT8 GMM_IsLastRand(VOS_VOID)
{
    VOS_UINT8   i;
    VOS_UINT8   ucRel = GMM_TRUE;

    for (i=0; i<GMM_MAX_SIZE_RAND; i++)
    {
        if (g_GmmAuthenCtrl.aucRandSav[i]
           != g_GmmAuthenCtrl.aucRand[i])
        {
            ucRel = GMM_FALSE;
            break;
        }
    }

    return ucRel;
}


VOS_VOID GMM_InitCasGlobalVariable (VOS_VOID)
{
    /* GMM CASȫ�ֽṹ�������� */
    Gmm_MemSet(&gstGmmCasGlobalCtrl, 0, sizeof(GMM_CAS_CTRL_STRU));
    Gmm_MemSet(&gstGmmCasMsgBuf,     0, sizeof(GMM_CAS_MSG_BUFFER_STRU));
    Gmm_MemSet(&gstGmmSuspendCtrl,   0, sizeof(GMM_SUSPEND_CTRL_STRU));


    /* �趨��ʼֵ */
    gstGmmCasGlobalCtrl.ucGmmCasState       = GMM_CAS_WCDMA_AS;
    gstGmmCasGlobalCtrl.ucGmmCasPreState    = GMM_CAS_WCDMA_AS;
    gstGmmCasGlobalCtrl.GmmSrvState         = GMM_IU_PMM_DETACHED;
    gstGmmCasGlobalCtrl.ucBufMsgResFlg      = GMM_FALSE;             /* ���û����Ҫ�ָ��Ĺ�����Ϣ */
    gstGmmCasGlobalCtrl.ucReadyTimerNgtFlg  = GMM_FALSE;             /*��ǿ�Э��ready timer*/
    gstGmmCasGlobalCtrl.ucRauCmpFlg         = GMM_FALSE;             /*��ǲ��ܷ���RAU CMP��Ϣ*/
    gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg = GMM_FALSE;
    gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg = GMM_FALSE;

    gstGmmCasGlobalCtrl.ucRabmResumeFlg     = GMM_TRUE;              /*���RABM RAU���������*/
    gstGmmCasGlobalCtrl.ulReadyTimerValue   = 44000;                 /* 44 s*/
    gstGmmCasGlobalCtrl.ucReadyTimerChgFlg  = VOS_FALSE;
    /* ��ʼ��ϵͳTLLIֵ */
    gstGmmCasGlobalCtrl.ulTLLI              = 0xffffffff;            /* ��ЧTLLIֵ */
    gstGmmCasGlobalCtrl.ulOldTLLI           = 0xffffffff;            /* ��ЧTLLIֵ */
    gstGmmCasGlobalCtrl.ucflgTLLI           = GMM_INVALID_TLLI;      /* ��TLLI��Ч��־ */
    gstGmmCasGlobalCtrl.ucTlliAssignFlg     = GMM_FALSE;             /* δ���TLLIָ�� */
    gstGmmCasGlobalCtrl.enRaPrioLevFosSms   = GMM_RA_PRIO_LEV_1;

    g_GmmGlobalCtrl.ulGmmAttachFlg          = GMM_FALSE;

    gstGmmSuspendCtrl.ucSuspendCause        = MMC_SUSPEND_CAUSE_BUTT;

    NAS_GMM_SetLmmSecInfoFlg(VOS_FALSE);

    return;
}


VOS_VOID GMM_CasRcvUsimCnfUmtsSucc(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    NAS_MSG_STRU *pNasMsg;                                  /* ����ָ��NAS��Ϣ��ָ��*/

    NAS_MML_SetSimPsSecurityCksn(g_GmmAuthenCtrl.ucCksnSav);            /* �ݴ���Ϣ�е�CKSN����ȫ�ֱ����е�CKSN                         */

    /* ��¼CKֵ��ȫ�ֱ�����, �����׸������ֽ� */
    Gmm_MemCpy(NAS_MML_GetSimPsSecurityUmtsCk(),
            &(pAuthCnf->aucCK[1]), 16 );                          /* ����ȫ�ֱ����е�Ck*/

    /* ��¼IKֵ��ȫ�ֱ����У������׸������ֽ� */
    Gmm_MemCpy(NAS_MML_GetSimPsSecurityUmtsIk(),
            &(pAuthCnf->aucIK[1]), 16 );                          /* ����ȫ�ֱ����е�Ik*/

    /* ���㱣��GSM Kc */
    /*modify,sunxibo,2006-02-24,itt begin*/
    if (0 == pAuthCnf->aucGsmKc[0]) /* check Kc length */
    {
        NAS_MML_SecContext3GTO2G(NAS_MML_GetSimPsSecurityUmtsIk(),
                                 NAS_MML_GetSimPsSecurityUmtsCk(),
                                 NAS_MML_GetSimPsSecurityGsmKc());
    }
    else
    {
        /* skip the first length byte */
        Gmm_MemCpy(NAS_MML_GetSimPsSecurityGsmKc(),
                &(pAuthCnf->aucGsmKc[1]), 8 );                        /* ����ȫ�ֱ����е�GSM Kc*/
    }
    /*modify,sunxibo,2006-02-24,itt end*/


    /* ����CK,IK,Kcֵ��SIM�� */
    /* BEGIN: Modified by liurui id:40632, 2006/6/29   PN:A32D04514 */
    /* Modified by h00313353 for iteration 9, 2015-2-26, begin */
    if (MMC_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {/* 3G USIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYSPS_ID);    /* ����SIM�е�CKSN,Ck,IK*/
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKCGPRS_ID);   /* ����SIM�е�GSM CKSN,Kc*/
    }
    else
    {/* 2G SIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKCGPRS_ID);   /* ����SIM�е�GSM CKSN,Kc*/
    }
    /* Modified by h00313353 for iteration 9, 2015-2-26, end */
    /* END:   Modified by liurui id:40632, 2006/6/29   PN:A32D04514 */

    /* ��¼RES */
    GMM_SaveAuthenResult(pAuthCnf);

    /* ֪ͨMMCʵ���Ȩ�����Ϣ */
    Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_SECURITY_KEY); /* ����RRMM_NAS_INFO_CHANGE_REQ*/

    /* �޸ļ�Ȩ���̵ı�־�� */
    Gmm_Start_StopedRetransmissionTimer();                  /* ���ڱ�ֹͣ��retransmission timer�������� */
    g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;                  /* GMM Authentication attempt counter��0    */
    g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;

    /* ��д��Ȩ��Ӧ��Ϣ */
    pNasMsg = Gmm_AuthenAndCipherResponseMsgMake(
            GMM_AUTH_AND_CIPH_RES_NEEDED);                  /* ����A&C RESPONSE*/

    /* ����GMM��Ϣ */
    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ComGprsCipherHandle();
    }

    /* RANDֵ�Ƚϸ��� */
    GMM_UpdateAuthenCtrlFlg();

    return;
}


VOS_VOID GMM_CasRcvUsimCnfGsmSucc(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    NAS_MSG_STRU *pNasMsg;                                  /* ����ָ��NAS��Ϣ��ָ��*/

    NAS_MML_SetSimPsSecurityCksn(g_GmmAuthenCtrl.ucCksnSav);            /* �ݴ���Ϣ�е�CKSN����ȫ�ֱ����е�CKSN                                 */


    /* ��¼Kcֵ��ȫ�ֱ�����, �����׸������ֽ�COPY */
    Gmm_MemCpy(NAS_MML_GetSimPsSecurityGsmKc(),
            &(pAuthCnf->aucGsmKc[1]), 8 );                        /* ����ȫ�ֱ����е�GSM Kc*/


    /* ����IK,CK */
    /*modify,sunxibo,2006-02-24,itt begin*/
    NAS_MML_SecContext2GTO3G(NAS_MML_GetSimPsSecurityUmtsIk(),
                             NAS_MML_GetSimPsSecurityUmtsCk(),
                             NAS_MML_GetSimPsSecurityGsmKc());

    /*Gmm_MemCpy(g_GmmGlobalCtrl.PsSecutityInfo.aucCk,
            pAuthCnf->aucCK, 16 );*/                          /* ����ȫ�ֱ����е�Ck*/

    /*Gmm_MemCpy(g_GmmGlobalCtrl.PsSecutityInfo.aucIk,
            pAuthCnf->aucIK, 16 );*/                          /* ����ȫ�ֱ����е�Ik*/
    /*modify,sunxibo,2006-02-24,itt end*/

    /* ����Kc,IK,CKֵ��SIM�� */
    /* BEGIN: Modified by liurui id:40632, 2006/6/29   PN:A32D04514 */
    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    /* Modified by h00313353 for iteration 9, 2015-2-26, begin */
    {/* 3G USIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKEYSPS_ID);    /* ����SIM�е�CKSN,Ck,IK*/
        Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFKCGPRS_ID);   /* ����SIM�е�GSM CKSN,Kc*/
    }
    else
    {/* 2G SIM */
        Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFKCGPRS_ID);   /* ����SIM�е�GSM CKSN,Kc*/
    }
    /* Modified by h00313353 for iteration 9, 2015-2-26, end */
    /* END:   Modified by liurui id:40632, 2006/6/29   PN:A32D04514 */

    /* ��¼SRES */
    GMM_SaveAuthenResult(pAuthCnf);

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_ComGprsCipherHandle();
    }

    Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_SECURITY_KEY); /* ����RRMM_NAS_INFO_CHANGE_REQ*/

    /* ��д��Ȩ��Ӧ��Ϣ */
    pNasMsg = Gmm_AuthenAndCipherResponseMsgMake(
            GMM_AUTH_AND_CIPH_RES_NEEDED);                  /* ����A&C RESPONSE*/

    /* ����GMM��Ϣ */
    Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

    /* RANDֵ�Ƚϸ��� */
    GMM_UpdateAuthenCtrlFlg();

    return;
}
VOS_VOID GMM_CasRcvUsimCnfFailUmts(
    USIMM_TELECOM_AUTH_CNF_STRU        *pAuthCnf,
    USIMM_AUTH_RESULT_ENUM_UINT32       enResult
)
{
    NAS_MSG_STRU    *pNasMsg;

    g_GmmAuthenCtrl.ucAuthenAttmptCnt++;                    /* GMM Authentication attempt counter��1    */

    /* �жϼ�Ȩ���Դ��� */
    if (GMM_AUTHEN_ATTEMPT_MAX_CNT == g_GmmAuthenCtrl.ucAuthenAttmptCnt)
    {/* ���������� */

        if (USIMM_AUTH_MAC_FAILURE == enResult)
        {
            /*�����Ȩʧ�ܵĴ�����*/
            NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_MAC_FAILURE);
        }
        else
        {
            /*�����Ȩʧ�ܵĴ�����*/
            NAS_GMM_SetAttach2DetachErrCode(GMM_SM_CAUSE_SYNCH_FAILURE);
        }

        /* ��Ȩʧ�ܴ����������� */
        Gmm_AuCntFail();
        return;
    }

    /* Failure ������� */
    if (USIMM_AUTH_MAC_FAILURE == enResult)
    {/* MAC failure */
        Gmm_Au_MacAutnWrong(NAS_MML_REG_FAIL_CAUSE_MAC_FAILURE);
    }
    else
    {/* SQN failure */
        /* AUTHENTICATION AND CIPHERING FAILURE���� */
        pNasMsg = Gmm_AuthenAndCipherFailureMsgMake(
                            NAS_MML_REG_FAIL_CAUSE_SYNCH_FAILURE,
                            pAuthCnf->aucAuts[0],
                            &(pAuthCnf->aucAuts[1]));

        /* ���÷��ͺ��� */
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

        Gmm_TimerStop(GMM_TIMER_T3316);                                         /* ֹͣT3316                                */

        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                            /* ��"RES���ڱ�־ "��Ϊ0                    */
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                            /* ��"RAND���ڱ�־ "��Ϊ0                   */

        if (GMM_AUTHEN_REJ_CAUSE_SYNC_FAIL == g_GmmAuthenCtrl.ucLastFailCause)
        {/* �ϴμ�Ȩʧ��ԭ��ֵ��ͬ��ʧ�� */
            g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;          /* GMM Authentication attempt counter��0 */
            g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;

            Gmm_TimerStop(GMM_TIMER_T3320);                 /* ͣT3320 */

            NAS_GMM_SndGasGprsAuthFailNotifyReq();

            Gmm_SndRrmmRelReq(RRC_CELL_BARRED);             /* ����RRMM_ABORT_REQ(RRC connection) */

            Gmm_Start_StopedRetransmissionTimer();          /* ���ڱ�ֹͣ��retransmission timer�������� */
        }
        else
        {/* �ϴμ�Ȩʧ��ԭ��ֵ����ͬ��ʧ�� */
            g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_SYNC_FAIL;
            Gmm_TimerStop(GMM_TIMER_T3318);                 /* ͣT3318(���������) */
            Gmm_TimerStart(GMM_TIMER_T3320);                /* ��T3320 */
            Gmm_Stop_RetransmissionTimer();                 /* ֹͣ�������е�retransmission timer */
        }
    }
    return;
}


VOS_VOID GMM_CasRcvUsimCnfFailGsm(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    /* BEGIN: Modified by liurui id:40632, 2006/4/11   PN:A32D03039 */
    /*NAS_MSG_STRU    *pNasMsg;*/

    GMM_LOG_WARN("GSM authentication failure for unacceptable reason by MS!");
    /* ֱ�ӷ��ͼ�Ȩ��Ӧ��Ϣ������ */
    /*modify,sunxibo,2006-03-02,itt begin*/
    /*pNasMsg = GMM_MakeAuthenAndCipherResponseMsgGsm
                (GMM_AUTH_AND_CIPH_RES_UNNEEDED);*/
    /*pNasMsg = Gmm_AuthenAndCipherFailureMsgMake(*/
    /*                                    NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR,*/
    /*                                    0,*/
    /*                                    VOS_NULL_PTR);*/
    /*modify,sunxibo,2006-03-02,itt end*/
    /* ����GMM��Ϣ */
    /*Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH,pNasMsg);*/
    /* END:   Modified by liurui id:40632, 2006/4/11   PN:A32D03039 */

    return;
}

/*****************************************************************************
 Prototype      : GMM_ExecLlgmmStatusIndCause
 Description    : ��������LL_GMM_STATUS_IND_MSG��Ϣ�е�ԭ��ֵ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_ExecLlgmmStatusIndCause(VOS_UINT16 usCause)
{
    switch (usCause)
    {
        case LL_GMM_STA_CAUSE_UNSOLICITED_UA_RSP:           /* unsolicited UA response */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_UNSOLICITED_DM_RSP:           /* unsolicited DM response */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RETRANS_SABM_N200:            /* SABM�����ط�N200�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RETRANS_DISC_N200:            /* DISC�����ط�N200�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RETRANS_XID_CMD_N200:         /* XID�����ظ�N200�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_INQUIRY_PEER_BUSY_N200:       /* ��ѯ�Է��Ƿ���æ״̬����N200�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_LLC_INIT_RE_EST:              /* LLC����ABM�ؽ� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_PEER_INIT_RE_EST:             /* �Զ˷���ABM�ؽ� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_FRAME_REJ_CONDITION:          /* ��⵽֡�ܾ����� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_RECV_FRMR_RSP:                /* ���յ�FRMR��Ӧ */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status mistake!");
            break;

        case LL_GMM_STA_CAUSE_GMM_ASSIGN_FAIL:              /* TLLIָ��ʧ�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC ASSIGN command failed!");
            break;

        case LL_GMM_STA_CAUSE_GMM_TRIGGER_FAIL:             /* LLC֡���ʹ�������ʧ�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC TRIGGER command failed!");
            break;

        case LL_GMM_STA_CAUSE_GMM_SUSPEND_FAIL:             /* LLC����ʧ�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC SUSPEND command failed!");
            break;

        case LL_GMM_STA_CAUSE_GMM_RESUME_FAIL:              /* LLC�ָ�ʧ�� */
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC RESUME command failed!");
            break;

        default :
            GMM_LOG_WARN("GMM_ExecLlgmmStatusIndCause():Warning: LLC link status alert undefined!");
            break;
    }

    return;
}


VOS_UINT32 GMM_SaveGsmSysInfoIndMsgPara(MMCGMM_GSM_SYS_INFO_IND_ST *pSysInfo)
{
    GMM_RAI_STRU                *pRaiTemp  = VOS_NULL_PTR;
    VOS_UINT8                    ucNetMod  = g_GmmGlobalCtrl.ucNetMod;
    MMCGMM_GSM_SYS_INFO_IND_ST  *ptr;
    VOS_UINT8                   *pucRaiChgFlg;
    VOS_UINT16                   usCellIdNew;
    VOS_UINT8                    ucCsAttachAllow;

    GMM_RAI_STRU                 stAttempUpdateRaiInfo;
    GMM_RAI_STRU                 stOldRai;
    NAS_MML_RAI_STRU            *pstAttemptUpdateRaiInfo = VOS_NULL_PTR;

    gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg         = GMM_FALSE;
    gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg         = GMM_FALSE;
    gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg   = GMM_FALSE;

    pucRaiChgFlg = &gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg;

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));

    if (VOS_NULL_PTR == pRaiTemp)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "GMM_SaveGsmSysInfoIndMsgPara:ERROR: MALLOC FAIL!");
        return GMM_FAILURE;                                                     /* ����                                     */
    }
    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    /* ��дRAC */
    pRaiTemp->ucRac = pSysInfo->ucRac;
    /* ��дLAC */
    pRaiTemp->Lai.aucLac[1] = (VOS_UINT8)pSysInfo->usLac;                       /* LAC */
    pRaiTemp->Lai.aucLac[0] = (VOS_UINT8)(pSysInfo->usLac >> 8);
    /* ��дPLMN */
    pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
        (VOS_UINT8)(pSysInfo->stPlmnId.ulMcc & 0x0F);                           /* MCC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMcc >> 8) & 0x0F);                    /* MCC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMcc >> 16) & 0x0F);                   /* MCC Digit 3                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
        (VOS_UINT8)(pSysInfo->stPlmnId.ulMnc & 0x0F);                           /* MNC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMnc >> 8) & 0x0F);                    /* MNC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
        (VOS_UINT8)((pSysInfo->stPlmnId.ulMnc >> 16) & 0x0F);                   /* MNC Digit 3                              */
    pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                                          /* MNC Degit count                          */

    if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
    {
        pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                                      /* MNC Degit count                          */
    }

    PS_MEM_SET(&stAttempUpdateRaiInfo, 0, sizeof(stAttempUpdateRaiInfo));
    pstAttemptUpdateRaiInfo = NAS_GMM_GetAttemptUpdateRaiInfo();

    NAS_GMM_ConvertPlmnIdToGmmFormat(&pstAttemptUpdateRaiInfo->stLai.stPlmnId, &stAttempUpdateRaiInfo.Lai.PlmnId);
    stAttempUpdateRaiInfo.Lai.aucLac[0] = pstAttemptUpdateRaiInfo->stLai.aucLac[0];
    stAttempUpdateRaiInfo.Lai.aucLac[1] = pstAttemptUpdateRaiInfo->stLai.aucLac[1];
    stAttempUpdateRaiInfo.ucRac         = pstAttemptUpdateRaiInfo->ucRac;

    stOldRai = g_GmmGlobalCtrl.SysInfo.Rai;
    if (VOS_TRUE == NAS_GMM_IsNeedUseAttemptUpdateRaiInfo(pRaiTemp, &stAttempUpdateRaiInfo))
    {
        stOldRai = stAttempUpdateRaiInfo;
    }

    if (GMM_FALSE == Gmm_Com_CmpRai(pRaiTemp, &stOldRai, pSysInfo->ucNetworkOperationMode))
    {                                                                           /* ����RAI�Ƿ�仯��־                      */
        gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = GMM_TRUE;
        gstGmmCasGlobalCtrl.ucSysRauFlg             = GMM_TRUE;
    }
    if (GMM_FALSE == Gmm_Compare_Lai(&pRaiTemp->Lai, &stOldRai.Lai))
    {                                                                           /* ����LAI�Ƿ�仯��־                      */
        gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg = GMM_TRUE;
    }

    /* GPRS֧��ָʾ */
    g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_SUPPORT_GPRS;

    if (0 == pSysInfo->ucGprsSupportInd)
    {
        g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_NOT_SUPPORT_GPRS;
    }

    usCellIdNew = pSysInfo->usCellId;

    if (usCellIdNew != g_GmmGlobalCtrl.SysInfo.usGsmCellId)
    {
        g_GmmGlobalCtrl.SysInfo.usGsmCellId = usCellIdNew;
        gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg = GMM_TRUE;             /* ��С����־ */
    }
    else
    {
        gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg = GMM_FALSE;
    }

    if (0 != pSysInfo->ucNetworkOperationMode)
    {/* ����ģʽ��Ч */
        ucNetMod = pSysInfo->ucNetworkOperationMode;
    }

    if ((g_GmmGlobalCtrl.SysInfo.ucNtType
        != NAS_MML_GetCurrNetRatType())
      &&(GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState))
    {/* ��ϵͳ��С����ϵͳ��Ϣ����Ч���� */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "GMM_SaveGsmSysInfoIndMsgPara:WARNING: Inter-System information cannot be handled in the GMM STATE!");
    }
    /* ==>A32D12706 */
    if ((g_GmmGlobalCtrl.SysInfo.ucNetMod != ucNetMod)
        && (0 != g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
    /* <==A32D12706 */
    {/* ����ģʽ��� */

        if ((GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucLaiChgFlg)
         || (GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg))
        {
            /*add by hanlufeng 41410 for A32D13172 BEGIN*/
            g_GmmRauCtrl.ucT3330outCnt = 0;
            /*add by hanlufeng 41410 for A32D13172 END*/

            if ((NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode()))
            {                                                                       /* �û�ģʽΪA,�����Ѿ�ע��                 */
                if (GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState)
                {
                    /* ����ϵͳ������̵ȴ�С��ϵͳ��Ϣ״̬ */
                    /* ͬϵͳ��С��ϵͳ��Ϣ���� */
                    Gmm_ComNetModeChangeGsm(pSysInfo);                              /* ��������ģʽ�任�Ĺ�������               */
                    Gmm_MemFree(pRaiTemp);

                    /*���С������ģʽ�ı䣬GMM_RcvGasSysInfoInd���������ߵ�����ָ�����û���Ĵ���
                      �����ڴ˴����Ӵ���
                    */
                    if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
                    {
                        if (GMM_SUSPEND_LLC_FOR_RAU != (GMM_SUSPEND_LLC_FOR_RAU & gstGmmCasGlobalCtrl.ucSuspendLlcCause))
                        {
                            GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);
                            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
                        }
                        else
                        {
                            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_SUSPEND_LLC_FOR_RAU;
                        }
                    }

                    if (0 == pSysInfo->ucGprsSupportInd)
                    {
                         NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
                    }

                    /* �յ�Gģϵͳ��Ϣ, ָʾRABM��ǰϵͳģʽ, �����Ƿ�֧��GPRS, �����ָ�RABM */
                    if ((VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
                     || (0 == pSysInfo->ucGprsSupportInd)
                     || (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg))
                    {
                        /* ��֧��GPRS��PS bar����û��ָ�ɲ�2, ����RABM, bRatChangeFlgΪFALSE
                           û��ָ�ɲ�2ʱ���������RABM��RABM����SN�������ݣ�SN�ᷢ�͵�LLC��
                           ��LLC��δָ������½��յ����ݻ��ͷ��ڴ浼�½������,��������С���Ὣ��Ϣ���й��� */
                        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                                    VOS_FALSE,
                                                    VOS_TRUE,
                                                    VOS_TRUE);
                    }
                    else
                    {
                        /* ֧��GPRS, �ָ�RABM, bRatChangeFlgΪFALSE */
                        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                                    VOS_FALSE,
                                                    VOS_FALSE,
                                                    VOS_TRUE);
                    }

                    return GMM_FAILURE;
                }
            }
        }

        gstGmmSuspendCtrl.ucNetModeChange = GMM_CasGetNetChgType(ucNetMod);
    }
    else
    {
        /* ����ģʽû�б��������ԭ������ģʽ��Ч */
        gstGmmSuspendCtrl.ucNetModeChange = GMM_NETMODE_CHG_NULL;
                    /*= GMM_CasGetNetChgTypeByGsm(ucNetMod);*/
    }

    /* ɾ����2Gϵͳ��ϢucDrxTimerMax��ֵ��DrxLen*/

    if (GMM_TRUE == gstGmmCasGlobalCtrl.TempMsgPara.ucGsmCellChgFlg)
    {
        if (GMM_TRUE == *pucRaiChgFlg)
        {
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
        }
        else
        {
            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_TRUE;
        }
    }
    else
    {
        gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
    }

    if (GMM_TRUE == *pucRaiChgFlg)
    {/* RA�ı� */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {/* �����������ڽ����������� */
            if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            {/* GMM_REGISTERED_INITIATED״̬ */
                ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                if (VOS_NULL_PTR == ptr)
                {
                    Gmm_MemFree(pRaiTemp);
                    return GMM_FAILURE;
                }
                Gmm_MemCpy(ptr, pSysInfo,
                           sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach = (VOS_UINT32)ptr;   /* �洢��Ϣ�׵�ַ�� ulMsgAddrForAttach      */
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_ATTACH;/* ����Ϣ������־                           */
                Gmm_MemFree(pRaiTemp);
                return GMM_FAILURE;
            }
            else if ((GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
                     || (GMM_ROUTING_AREA_UPDATING_INITIATED
                     == g_GmmGlobalCtrl.ucState)
                     || (GMM_SERVICE_REQUEST_INITIATED
                     == g_GmmGlobalCtrl.ucState)
                     || (GMM_REGISTERED_IMSI_DETACH_INITIATED
                     == g_GmmGlobalCtrl.ucState))
            {
                ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                if (VOS_NULL_PTR == ptr)
                {
                    Gmm_MemFree(pRaiTemp);
                    return GMM_FAILURE;
                }
                Gmm_MemCpy(ptr, pSysInfo,
                           sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)ptr;      /* �洢��Ϣ�׵�ַ�� ulMsgAddrForRau         */
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;   /* ����Ϣ������־                           */
                Gmm_MemFree(pRaiTemp);

                if (0 == pSysInfo->ucGprsSupportInd)
                {
                     NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
                }

                return GMM_FAILURE;
            }
            else
            {
            }
        }
    }

    if ((MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
        && (0 != pSysInfo->ucGprsSupportInd))
    {
        Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* �洢ϵͳ��Ϣ�е�RAI                      */
        if (GMM_RAU_NORMAL_CS_UPDATED == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = GMM_TRUE;
        }
    }
    else
    {
        /* ��ȡCS ATTACH Allow��־ */
        ucCsAttachAllow                             = NAS_MML_GetCsAttachAllowFlg();
        gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = GMM_FALSE;
        gstGmmCasGlobalCtrl.ucSysRauFlg             = GMM_FALSE;
        if ((MMCGMM_GSM_NO_FORBIDDEN == pSysInfo->ulForbiddenFlg)
            || (MMCGMM_GSM_FORBIDDEN_PLMN_FOR_GPRS == pSysInfo->ulForbiddenFlg))
        {
            if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
             && (VOS_TRUE == ucCsAttachAllow))
            {
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_RAU_NORMAL_CS_UPDATED;
            }
        }
    }

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* ����ģʽ                                 */
    if (g_GmmGlobalCtrl.ucNetMod != ucNetMod)
    {
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                    /* ����ģʽ                                 */
    }

    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfo->ulForbiddenFlg;   /* PLMN�Ƿ��ֹ                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* ��ϵͳ��Ϣ��Ч��־                       */

    Gmm_MemFree(pRaiTemp);
    return GMM_SUCCESS;
}

/*****************************************************************************
 Prototype      : GMM_CharToUlong
 Description    : �ֽ�����ת����ULONG��
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_CharToUlong(VOS_UINT32 *ulDst, VOS_UINT8 *pucSrc)
{
    VOS_UINT32  ulResult;

    ulResult  = 0;
    /*lint -e701 -e961*/
    /* BEGIN: Modified by liurui id:40632, 2006/3/4   PN:A32D02287*/
    ulResult += (*(pucSrc++) << 24);
    ulResult += (*(pucSrc++) << 16);
    ulResult += (*(pucSrc++) << 8);
    ulResult += (*(pucSrc) );
    /* END:   Modified by liurui id:40632, 2006/3/4 */
    /*lint +e701 +e961*/
    *ulDst = ulResult;
    return;
}

/*****************************************************************************
 Prototype      : GMM_CreateNewTlli
 Description    : �����µ�TLLIֵ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function

  2.Date        : 2015-07-23
    Author      : wx270776
    Modification: OM Migration
*****************************************************************************/
VOS_VOID GMM_CreateNewTlli(VOS_UINT32 *pulTmsi, VOS_UINT8 ucType)
{
    VOS_UINT32  ulTLLI;
    VOS_UINT32  ulHead5;

    /* BEGIN: Modified by liurui id:40632, 2006/3/4   PN:A32D02287*/
    ulTLLI   = *pulTmsi;                /* �õ�PTMSIֵ */
    ulHead5  = ulTLLI >> 27;            /* ȡ��TLLI�ı�־ͷ */
    ulHead5 &= 0x07;                    /* �����Ч����λ */
    /* END:   Modified by liurui id:40632, 2006/3/4 */

    /*��дTLLIֵ�ĸ�5λֵ*/
    switch (ucType)
    {
        case GMM_RANDOM_TLLI:
            ulHead5  = 0x0f;            /* 5λֵ�� 01111 */
            /* Modified by wx270776 for OM�ں�, 2015-7-23, begin */
            ulTLLI   = VOS_GetSlice();   /* ȡϵͳʱ������Ϊα����� */
            /* Modified by wx270776 for OM�ں�, 2015-7-23, end */
            break;

        case GMM_LOCAL_TLLI:
            ulHead5 |= 0x18;            /* 5λֵ�� 11XXX */
            break;

        case GMM_FOREIGN_TLLI:
            ulHead5 |= 0x10;            /* 5λֵ�� 10XXX */
            break;

        case GMM_AUXILIARY_TLLI:
            /* modify,sunxibo,2006-02-20,itt begin*/
            ulHead5 = 0x0e;            /* 5λֵ�� 01110 */
            /* modify,sunxibo,2006-02-20,itt end*/
            break;

        default :                       /* ����,�ο�3GPP TS23.003���� */
            ulHead5  = 0x00;            /* 5λֵ�� 00000 */
            break;
    }

    /*��дTLLIֵ�ĵ�27λֵ*/
    ulHead5 = ulHead5 << 27;
    /* BEGIN: Modified by liurui id:40632, 2006/3/4   PN:A32D02287*/
    ulTLLI &= 0x07ffffff;               /* �����5λ */
    /* END:   Modified by liurui id:40632, 2006/3/4 */
    ulTLLI += ulHead5;                  /* ��TTLLIֵ */

    *pulTmsi = ulTLLI;                  /* ���ؽ�� */
    return;
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_GMM_UseGutiDerivedPtmsi ( VOS_VOID )
{
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulGetGutiRst;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT32                          ulRslt;

    /* ���£�Э��������b)��d) ����VOS_TRUE,�������� VOS_FALSE
    4.7.1.4.1   Radio resource sublayer address handling (A/Gb mode only)

    For an MS supporting S1 mode, the following five cases can be distinguished:
    a)  the TIN indicates "P-TMSI" or "RAT related TMSI" and the MS holds a valid P-TMSI and a RAI;
    b)  the TIN indicates "GUTI" and the MS holds a valid GUTI;
    c)  the TIN is deleted and the MS holds a valid P-TMSI and RAI;
    d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; or
    e)  none of the previous cases is fulfilled.

    In case b), the MS shall derive a P-TMSI from the GUTI and
                then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.
    In case d) the MS shall derive a P-TMSI from the GUTI and then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.

    In case a) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case c) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case e) the MS shall proceed as as specified for case ii) above.
    */

    /* ��ȡ��ǰGU��p-Tmsi��ȡֵ */
    ucUeIdMask          = NAS_GMM_GetUeIdMask();

    /* ��ȡ��ǰ��Tinֵ��Mapped P-Tmsi�Ƿ���ȷ */
    ulGetGutiRst        = NAS_GMM_MapPtmsiFromGUTI();
    enTinType           = NAS_MML_GetTinType();

    if (VOS_OK == ulGetGutiRst)
    {
        /* b)  the TIN indicates "GUTI" and the MS holds a valid GUTI; */
        if (NAS_MML_TIN_TYPE_GUTI == enTinType)
        {
            ulRslt = VOS_TRUE;
        }
        /* d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; */
        else if ( (NAS_MML_TIN_TYPE_INVALID == enTinType)
               && (GMM_UEID_P_TMSI != (ucUeIdMask & GMM_UEID_P_TMSI) ))
        {
            ulRslt = VOS_TRUE;
        }
        else
        {
            ulRslt = VOS_FALSE;
        }
    }
    else
    {
        ulRslt = VOS_FALSE;
    }

    return ulRslt;

}

#endif


VOS_UINT32 NAS_GMM_GetPTmsiForTLLI(
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN]
)
{
    VOS_UINT8                          *pucPtmsiAddr        = VOS_NULL_PTR;
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulLocalPtmsiFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulGetGutiRst;
    VOS_UINT8                          *pucMappedPtmsiAddr  = VOS_NULL_PTR;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT32                          ulRslt;

    VOS_UINT32                          ulIsSupportLteCap;
#endif

    /*
    4.7.1.4.1   Radio resource sublayer address handling (A/Gb mode only)
    This subclause describes how the RR addressing is managed by GMM.
    For the detailed coding of the different TLLI types and how a TLLI can be derived from a P-TMSI, see 3GPP TS 23.003 [10].
    For an MS not supporting S1 mode, two cases can be distinguished:
    -   a valid P-TMSI is available in the MS; or
    -   no valid P-TMSI is available in the MS.
    i)   valid P-TMSI available
        If the MS has stored a valid P-TMSI, the MS shall derive a foreign TLLI from that P-TMSI and shall use it for transmission of the:
    -   ATTACH REQUEST message of any GPRS combined/non-combined attach procedure; other GMM messages sent during this procedure shall be transmitted using the same foreign TLLI until the ATTACH ACCEPT message or the ATTACH REJECT message is received; and
    -   ROUTING AREA UPDATE REQUEST message of a combined/non-combined RAU procedure if the MS has entered a new routing area, or if the GPRS update status is not equal to GU1 UPDATED. Other GMM messages sent during this procedure shall be transmitted using the same foreign TLLI, until the ROUTING AREA UPDATE ACCEPT message or the ROUTING AREA UPDATE REJECT message is received.
        After a successful GPRS attach or routing area update procedure, independent whether a new P-TMSI is assigned, if the MS has stored a valid P-TMSI then the MS shall derive a local TLLI from the stored P-TMSI and shall use it for addressing at lower layers.
    NOTE 1: Although the MS derives a local TLLI for addressing at lower layers, the network should not assume that it will receive only LLC frames using a local TLLI. Immediately after the successful GPRS attach or routing area update procedure, the network must be prepared to continue accepting LLC frames from the MS still using the foreign TLLI.
    ii) no valid P-TMSI available
        When the MS has not stored a valid P-TMSI, i.e. the MS is not attached to GPRS, the MS shall use a randomly selected random TLLI for transmission of the:
    -   ATTACH REQUEST message of any combined/non-combined GPRS attach procedure.
        The same randomly selected random TLLI value shall be used for all message retransmission attempts and for the cell updates within one attach attempt.
        Upon receipt of an ATTACH REQUEST message, the network shall assign a P-TMSI to the MS. The network derives a local TLLI from the assigned P-TMSI, and transmits the assigned P-TMSI to the MS.
        Upon receipt of the assigned P-TMSI, the MS shall derive the local TLLI from this P-TMSI and shall use it for addressing at lower layers.
    NOTE 2: Although the MS derives a local TLLI for addressing at lower layers, the network should not assume that it will receive only LLC frames using a local TLLI. Immediately after the successful GPRS attach, the network must be prepared to continue accepting LLC frames from the MS still using the random TLLI.
    In both cases the MS shall acknowledge the reception of the assigned P-TMSI to the network. After receipt of the acknowledgement, the network shall use the local TLLI for addressing at lower layers.


    For an MS supporting S1 mode, the following five cases can be distinguished:
    a)  the TIN indicates "P-TMSI" or "RAT related TMSI" and the MS holds a valid P-TMSI and a RAI;
    b)  the TIN indicates "GUTI" and the MS holds a valid GUTI;
    c)  the TIN is deleted and the MS holds a valid P-TMSI and RAI;
    d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; or
    e)  none of the previous cases is fulfilled.

    In case a) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case b), the MS shall derive a P-TMSI from the GUTI and
                then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.
    In case c) the MS shall derive a foreign TLLI from the P-TMSI and proceed as specified for case i) above.
    In case d) the MS shall derive a P-TMSI from the GUTI and then a foreign TLLI from this P-TMSI and proceed as specified for case i) above.
    In case e) the MS shall proceed as as specified for case ii) above.
    */

    /* ȡ�ô洢PTMSI���ݵĵ�ַ */
    pucPtmsiAddr        = NAS_MML_GetUeIdPtmsi();

    ucUeIdMask          = NAS_GMM_GetUeIdMask();

    /* �ж�GUPTMSI�Ƿ���Ч��VOS_TRUE:��Ч;VOS_FALSE:��Ч; */
    if ( GMM_UEID_P_TMSI == (ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);

        ulLocalPtmsiFlg = VOS_TRUE;
    }
    else
    {
        ulLocalPtmsiFlg = VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    /* ��ʼ����ǰ��P-Tmsi�Ĵ��ڱ�־ */
    ulRslt              = VOS_TRUE;

    /* ��ȡ��ǰ��Tinֵ��Mapped P-Tmsi */
    ulGetGutiRst        = NAS_GMM_MapPtmsiFromGUTI();
    enTinType           = NAS_MML_GetTinType();

    /* ȡ�ô洢PTMSI���ݵĵ�ַ */
    pucMappedPtmsiAddr  = NAS_GMM_GetMappedPtmsiAddr();

    /* reference to 24.008 4.7.1.4.1 */
    ulIsSupportLteCap = NAS_MML_IsSupportLteCapability();

    /* syscfg���ò�֧��L����L �Ѿ�disable�������guti�л�ȡptimsi */
    if (VOS_FALSE == ulIsSupportLteCap)
    {
        if (VOS_TRUE == ulLocalPtmsiFlg)
        {
            PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
        }
        else
        {
            ulRslt = VOS_FALSE;
        }

        return ulRslt;
    }

    /* a)  the TIN indicates "P-TMSI" or "RAT related TMSI" and the MS holds a valid P-TMSI and a RAI; */
    if ( ( (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType)
        || (NAS_MML_TIN_TYPE_PTMSI  == enTinType))
      && (VOS_TRUE == ulLocalPtmsiFlg))
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /* b)  the TIN indicates "GUTI" and the MS holds a valid GUTI; */
    else if ((NAS_MML_TIN_TYPE_GUTI == enTinType)
          && (VOS_OK == ulGetGutiRst) )
    {
        PS_MEM_CPY(aucPtmsi, pucMappedPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /* c)  the TIN is deleted and the MS holds a valid P-TMSI and RAI; */
    else if ((NAS_MML_TIN_TYPE_INVALID == enTinType)
          && (VOS_TRUE == ulLocalPtmsiFlg))
    {
        PS_MEM_CPY(aucPtmsi, pucPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /* d)  the TIN is deleted and the MS holds a valid GUTI, but no valid P-TMSI and RAI; */
    else if ((NAS_MML_TIN_TYPE_INVALID == enTinType)
          && (VOS_FALSE == ulLocalPtmsiFlg)
          && (VOS_OK == ulGetGutiRst))
    {
        PS_MEM_CPY(aucPtmsi, pucMappedPtmsiAddr, NAS_MML_MAX_PTMSI_LEN);
    }
    /*e)  none of the previous cases is fulfilled.*/
    else
    {
        ulRslt = VOS_FALSE;
    }

    return ulRslt;

#else

    /* LTE����ʱ��ֻ��Ҫ�ж� GU P-Tmsi�Ƿ���Ч */
    return ulLocalPtmsiFlg;
#endif

}
VOS_VOID GMM_UpdateSysTlli(GMM_TLLI_TYPE TlliType)
{
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN];

    /* ��ڲ������ */
    if ( (GMM_RANDOM_TLLI != TlliType)
      && (GMM_FOREIGN_TLLI != TlliType)
      && (GMM_LOCAL_TLLI != TlliType) )
    {
        GMM_LOG_ERR("GMM_UpdateSysTlli():Error: TlliType is not correct.");
        return;
    }

    /* ��ʼ�� */
    PS_MEM_SET(aucPtmsi, 0, sizeof(aucPtmsi));

    /* û�д�����Ч��PTMSI, ����RANDOM TLLI */
    if (VOS_FALSE == NAS_GMM_GetPTmsiForTLLI(aucPtmsi))
    {
        GMM_CreateNewTlli(&gstGmmCasGlobalCtrl.ulTLLI, GMM_RANDOM_TLLI);

        gstGmmCasGlobalCtrl.ucflgTLLI = GMM_RANDOM_TLLI;

        return;
    }

    /* �����µ�TLLIֵ */
    GMM_CharToUlong(&gstGmmCasGlobalCtrl.ulTLLI, aucPtmsi);


    GMM_CreateNewTlli(&gstGmmCasGlobalCtrl.ulTLLI, TlliType);

    gstGmmCasGlobalCtrl.ucflgTLLI = TlliType;

    return;
}


VOS_UINT32 GMM_GetPtmsiFromMsgIe(VOS_UINT8 *pData)
{
    VOS_UINT32  ulNewTlli = 0;
    VOS_UINT32  ulRslt;

    /* �ж�IE���������Ƿ���Ч */
    if ( (5 != *(pData))                                    /*����ֵ�Ƿ�*/
      || (0x04 != (*(pData+1) & 0x07) )                     /*���Ͳ�ƥ��*/
        )
    {/* ������Ч */
        GMM_LOG_WARN("GMM_GetPtmsiFromMsgIe:WARNING: Wrong length or type in IE data");
        return GMM_FALSE;
    }

    /* ����GMMϵͳ��������PTMSIֵ */
    NAS_MML_SetUeIdPtmsi((pData + 2));
    g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI;

    GMM_CharToUlong(&ulNewTlli,
                    NAS_MML_GetUeIdPtmsi());  /*�����µ�TLLIֵ*/

    /* ����local TLLIֵ */
    GMM_CreateNewTlli(&ulNewTlli, GMM_LOCAL_TLLI);          /*����TLLI*/

    /* ָ��new TLLI */
    ulRslt = GMM_AssignNewTlli(ulNewTlli, GMM_LOCAL_TLLI);
    if (GMM_FALSE == ulRslt)
    {
        GMM_LOG_WARN("GMM_GetPtmsiFromMsgIe():Error: new TLLI assigned failed!");
    }

#if (FEATURE_ON == FEATURE_PTM)
    /* ���̲˵��򿪺�PTMSI�����ı���Ҫ�ϱ���OM */
    NAS_GMM_SndAcpuOmChangePtmsi();
#endif

    return GMM_TRUE;
}


VOS_VOID GMM_FreeOldTlli(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    VOS_UINT32               ulRet;

    /* ֪ͨLLC�ͷ�old TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_UNASSIGN);
    if (VOS_NULL_PTR == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_FreeOldTlli():Error: making LLC message wrongly!");
        return;
    }
    /* ����ԭ�ﵽLLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* ֪ͨGRR�ͷ�old TLLI */
    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_OLD_TLLI);
        if (VOS_NULL_PTR == pGasAssignMsg)
        {
            GMM_LOG_ERR("GMM_FreeOldTlli():Error: making GAS message wrongly!");
            return;
        }
        /* ����ԭ�ﵽGRR */
        ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
        if (VOS_OK != ulRet)
        {
            GMM_LOG_ERR("GMM_FreeOldTlli():Error: Send msg fail!");
        }
    }
    return;
}


VOS_VOID GMM_FreeSysTlli(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    VOS_UINT32               ulRet;

    /* ֪ͨLLC�ͷ�old TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_UNASSIGN_SYS);
    if (VOS_NULL_PTR == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_FreesSysTlli():Error: making LLC message wrongly!");
        return;
    }
    /* ����ԭ�ﵽLLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* ��TLLIδָ���־ */
    gstGmmCasGlobalCtrl.ucTlliAssignFlg = GMM_FALSE;

    if (GMM_NOT_SUSPEND_LLC != gstGmmCasGlobalCtrl.ucSuspendLlcCause)
    {

        GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);                               /* �ָ�LLC���ݴ��� */
        gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_NOT_SUSPEND_LLC;
    }

    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_FreesSysTlli():Error: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_AssignNewTlli
 Description    : ָ��new TLLI
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-08
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_AssignNewTlli(VOS_UINT32 ulNewTlli, VOS_UINT8 ucType)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    VOS_UINT32               ulRet;

    /* �滻ϵͳĬ��TLLI */
    gstGmmCasGlobalCtrl.ulOldTLLI = gstGmmCasGlobalCtrl.ulTLLI;
    gstGmmCasGlobalCtrl.ulTLLI    = ulNewTlli;

    gstGmmCasGlobalCtrl.ucflgTLLI = ucType;             /* �޸�TLLI���ͱ�־ */

    /* ֪ͨLLCָ��new TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_MODIFY);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignNewTlli():Error: making LLC message wrongly!");
        return GMM_FALSE;
    }
    /* ����ԭ�ﵽLLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* ֪ͨGRRָ��new TLLI */
    pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_NEW_TLLI);
    if (VOS_NULL == pGasAssignMsg)
    {
        GMM_LOG_ERR("GMM_AssignNewTlli():Error: making GAS message wrongly!");
        return GMM_FALSE;
    }
    /* ����ԭ�ﵽGRR */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignNewTlli():Error: Send msg fail!");
    }

    return GMM_TRUE;
}

/* BEGIN: Added by liurui id:40632, 2006/5/20   PN:A32D03865 */
/*****************************************************************************
 Prototype      : GMM_AssignModifyTlli
 Description    : �޸�TLLI
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2006-05-20
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_UINT32 GMM_AssignModifyTlli(VOS_UINT32 ulNewTlli, VOS_UINT8 ucType)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    VOS_UINT32               ulRet;

    /* �滻ϵͳĬ��TLLI */
    gstGmmCasGlobalCtrl.ulTLLI    = ulNewTlli;

    gstGmmCasGlobalCtrl.ucflgTLLI = ucType;             /* �޸�TLLI���ͱ�־ */

    /* ֪ͨLLCָ��new TLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_MODIFY);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignModifyTlli():Error: making LLC message wrongly!");
        return GMM_FALSE;
    }
    /* ����ԭ�ﵽLLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);

    /* ֪ͨGRRָ��new TLLI */
    pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_NEW_TLLI);
    if (VOS_NULL == pGasAssignMsg)
    {
        GMM_LOG_ERR("GMM_AssignModifyTlli():Error: making GAS message wrongly!");
        return GMM_FALSE;
    }
    /* ����ԭ�ﵽGRR */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignModifyTlli():Error: Send msg fail!");
    }

    return GMM_TRUE;
}
/* END:   Added by liurui id:40632, 2006/5/20   PN:A32D03865 */

VOS_VOID GMM_AssignSysTlli(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    GRRGMM_ASSIGN_REQ_ST    *pGasAssignMsg;
    GMM_OP_TLLI              TlliOpMode;
    VOS_UINT32               ulRet;

    /* �ж�TLLI�������� */
    if (GMM_FALSE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
    {
        TlliOpMode = GMM_OP_TLLI_ASSIGN;                    /* ����ָ��TLLI */
    }
    else
    {
        TlliOpMode = GMM_OP_TLLI_SYNC;                      /* ͬ����ǰTLLI */
    }

    /* ֪ͨLLCͬ��ϵͳTLLI */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(TlliOpMode);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignSysTlli():Error: making LLC message wrongly!");
        return;
    }
    /* ����ԭ�ﵽLLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);
    if (GMM_OP_TLLI_ASSIGN == TlliOpMode)
    {
        gstGmmCasGlobalCtrl.ucTlliAssignFlg = GMM_TRUE;     /* TLLIָ����ɱ�־ */

        /* �ָ�RABM, bRatChangeFlgΪFALSE */
        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_GSM,
                                    VOS_FALSE,
                                    VOS_FALSE,
                                    VOS_TRUE);
    }

    /* ֪ͨGRRָ��new TLLI */
    pGasAssignMsg = GMM_MakeGrrmmAssignReqMsg(GMM_GRR_NEW_TLLI);
    if (VOS_NULL == pGasAssignMsg)
    {
        GMM_LOG_ERR("GMM_AssignSysTlli():Error: making GAS message wrongly!");
        return;
    }
    /* ����ԭ�ﵽGRR */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pGasAssignMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignSysTlli():Error: Send msg fail!");
    }

    return;
}


VOS_VOID GMM_AssignGsmKc(VOS_VOID)
{
    LL_GMM_ASSIGN_REQ_MSG   *pAssignReqMsg;
    VOS_UINT32               ulRet;

    /* ֪ͨLLCָ��Kc�ͼ����㷨 */
    pAssignReqMsg = GMM_MakeLlgmmAssignReqMsg(GMM_OP_TLLI_KC);
    if (VOS_NULL == pAssignReqMsg)
    {
        GMM_LOG_ERR("GMM_AssignGsmKc():Error: making LLC message wrongly!");
        return;
    }
    /* ���ü����㷨�Ѿ�ָ�� */
    gstGmmCasGlobalCtrl.ucGprsCipherAssign = VOS_TRUE;

    /* ����ԭ�ﵽLLC */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pAssignReqMsg);
    if (VOS_OK != ulRet)
    {
        GMM_LOG_ERR("GMM_AssignGsmKc():Error: Send msg fail!");
    }
    return;
}
VOS_VOID GMM_SaveAuthenResult(USIMM_TELECOM_AUTH_CNF_STRU *pAuthCnf)
{
    VOS_UINT8   i;
    VOS_UINT8  *pucAuthRes;

    pucAuthRes = &(pAuthCnf->aucAuthRes[0]);

    /* ����GSM��Ȩ��� */
    if (GMM_UMTS_AUTHEN_UNSUPPORTED == g_GmmAuthenCtrl.ucUmtsAuthFlg)
    {
        g_GmmAuthenCtrl.ucResExtLen = 0;                    /* û����չ���� */
        for (i=1; i<5; i++)
        {
            if (i > *(pucAuthRes))
            {
                g_GmmAuthenCtrl.aucRes[i-1] = 0xFF;         /* �����Чֵ */
            }
            else
            {
                g_GmmAuthenCtrl.aucRes[i-1] = *((pucAuthRes + i));
            }
        }
        return;
    }

    /* ����RES�Ļ������� */
    if (4 > *(pucAuthRes))
    {
        Gmm_MemCpy(g_GmmAuthenCtrl.aucRes,
                   (pucAuthRes + 1),
                  *(pucAuthRes) );                          /* ����RES */

        for ( i=*(pucAuthRes); i<4; i++ )
        {
            g_GmmAuthenCtrl.aucRes[i] = 0xFF;
        }

        g_GmmAuthenCtrl.ucResExtLen = 0;                    /* ��RES(EXTERN)�ĳ��ȣ�0:aucResExt������   */
    }
    else
    {
        Gmm_MemCpy(g_GmmAuthenCtrl.aucRes,
                (pucAuthRes + 1), 4 );                      /* ����RES */
        g_GmmAuthenCtrl.ucResExtLen =
               *(pucAuthRes) - 4;                           /* ��RES(EXTERN)�ĳ��ȣ�0:aucResExt������   */
    }

    /* ����RES��չ���� */
    if (0 < g_GmmAuthenCtrl.ucResExtLen)
    {
        if (12 < g_GmmAuthenCtrl.ucResExtLen)
        {
            g_GmmAuthenCtrl.ucResExtLen = 12;               /* ������Ч��RES Extension���� */
        }
        Gmm_MemCpy(g_GmmAuthenCtrl.aucResExt,
               (pucAuthRes + 5),
               g_GmmAuthenCtrl.ucResExtLen );               /* ����RES Extension */
    }

    return;
}
VOS_VOID GMM_UpdateAuthenCtrlFlg(VOS_VOID)
{
    VOS_UINT8   i;

    if (GMM_FALSE == g_GmmAuthenCtrl.ucResStoredFlg)
    {                                                       /* ��ʧ���ڴ�Ϊ��*/
        g_GmmAuthenCtrl.ucRandStoredFlg = GMM_TRUE;
        g_GmmAuthenCtrl.ucResStoredFlg  = GMM_TRUE;         /* �趨��ʧ���ڴ治Ϊ��*/

        for (i=0; i<GMM_MAX_SIZE_RAND; i++)
        {                                                   /* ������һ�ε�RANDֵ*/
            g_GmmAuthenCtrl.aucRand[i] = g_GmmAuthenCtrl.aucRandSav[i];
        }
        Gmm_TimerStart(GMM_TIMER_T3316);                    /* ����T3316*/
    }
    else
    {                                                       /* ��ʧ���ڴ治Ϊ��*/
        for (i=0; i<GMM_MAX_SIZE_RAND; i++)
        {                                                   /* ������һ�ε�RANDֵ*/
            g_GmmAuthenCtrl.aucRand[i] = g_GmmAuthenCtrl.aucRandSav[i];
        }

        Gmm_TimerStart(GMM_TIMER_T3316);                    /* ����T3316*/
    }

    return;
}
VOS_VOID GMM_RcvGsmPagingAtRegNmlServ(GRRMM_PAGING_IND_ST *pMsg)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    enRatType;


    if (GAS_IMSI == pMsg->ucMSIDType)
    {/* Ѱ��������ΪIMSI */
        if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        {                                                                       /* ����������                               */
            g_GmmAttachCtrl.ucPagingWithImsiFlg = GMM_TRUE;                     /* ����������IMSIѰ��������ATTACH         */
        }
        Gmm_PagingInd_common();
    }
    else
    {
        /* ���յ�PAGING INDʱ������READY״̬�����յ�LLC INFOMʱ���� */

        if ( 0 == gstGmmCasGlobalCtrl.ulReadyTimerValue )
        {
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }


        enRatType   = NAS_MML_GetCurrNetRatType();
        if ((GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
         && (gstGmmCasGlobalCtrl.ucLastDataSender != enRatType)
#if (FEATURE_ON == FEATURE_LTE)
         && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
         )
        {
            GMM_LOG_INFO("GMM_RcvGsmPagingAtRegNmlServ:Inter System change, Exec select RAU.");
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
            return;
        }

        GMM_SndLlcTriggerReq(LL_GMM_TRIG_CAUSE_PAG_RSP);
    /*}*/
    /* END:   Modified by liurui id:40632, 2006/4/25   PN:A32D03000 */
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_RcvGsmPagingAtDeregInit
 Description    : ��GMM_DEREGISTERED_INITIATED״̬��
                   ����GRRMM_PAGING_IND��Ϣ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :

 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-03
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_RcvGsmPagingAtDeregInit(GRRMM_PAGING_IND_ST *pMsg)
{
    GRRMM_PAGING_IND_ST    *pMsgHold;

    if (GAS_IMSI == pMsg->ucMSIDType)
    {/* Ѱ��������ΪIMSI */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {                                                                       /* �����������ڽ�����������                 */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_PAGING;    /* ����Ϣ������ı�־                       */
            pMsgHold = (GRRMM_PAGING_IND_ST *)Gmm_MemMalloc(sizeof(GRRMM_PAGING_IND_ST));
            if (VOS_NULL_PTR == pMsgHold)
            {
                return;
            }
            Gmm_MemCpy(pMsgHold, pMsg, sizeof(GRRMM_PAGING_IND_ST));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging = (VOS_UINT32)pMsgHold;  /* ����RRMM_PAGING _IND�׵�ַ               */
        }
        else
        {                                                                       /* �������û�������һ�û������             */
            if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
                == (g_GmmReqCnfMng.ucCnfMask
                & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
            {                                                                   /* �ȴ���Ȩ��Ӧ                             */
                Gmm_TimerStop(GMM_TIMER_PROTECT);                               /* ͣ������ʱ��                             */
                g_GmmReqCnfMng.ucCnfMask
                    &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                  /* ���ԭ��ȴ���־                         */
            }
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED); /* ����״̬��ΪGU2                          */
            Gmm_DelPsLocInfoUpdateUsim();
            Gmm_SndMmcLocalDetachInd(NAS_MML_REG_FAIL_CAUSE_NTDTH_IMSI);

            if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            {
                Gmm_RcvDetachAcceptMsg_DeregInit();
            }
            else
            {
                Gmm_RcvDetachAcceptMsg_RegImsiDtchInit();
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                Gmm_Attach_Prepare();                                           /* ȫ�ֱ�������������Ϊattach����׼��     */
                Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
            }
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_RcvGsmPagingAtRauInit
 Description    : ��GMM_ROUTING_AREA_UPDATING_INITIATED״̬��
                   ����GRRMM_PAGING_IND��Ϣ
                  HSS 4100 V200R001 ����
 Input          :
 Output         :
 Return Value   :

 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-03
    Author      : Roger Leo
    Modification: Created function
*****************************************************************************/
VOS_VOID GMM_RcvGsmPagingAtRauInit(GRRMM_PAGING_IND_ST *pMsg)
{
    GRRMM_PAGING_IND_ST    *pMsgHold;

    if (GAS_IMSI == pMsg->ucMSIDType)
    {/* Ѱ��������ΪIMSI */
        if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
            && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
        {                                                                       /* �����������ڽ�����������                 */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_PAGING;    /* ����Ϣ������ı�־                       */
            pMsgHold = (GRRMM_PAGING_IND_ST *)Gmm_MemMalloc(sizeof(GRRMM_PAGING_IND_ST));
            if (VOS_NULL_PTR == pMsgHold)
            {
                  return;
            }
            Gmm_MemCpy(pMsgHold, pMsg, sizeof(GRRMM_PAGING_IND_ST));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging = (VOS_UINT32)pMsgHold;       /* ����RRMM_PAGING _IND�׵�ַ              */
        }
        else
        {                                                                       /* �������û�������һ�û������             */
            Gmm_TimerStop(GMM_TIMER_T3330);                                     /* ͣT3330                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* ֹͣT3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* ֹͣT3320                                */

            Gmm_PagingInd_common();
        }
    }

    return;
}


VOS_VOID GMM_RcvGsmPaging_RegPlmnSrch(GRRMM_PAGING_IND_ST *pMsg)
{
    if (GAS_IMSI != pMsg->ucMSIDType)
    {
        Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_PAGING);

        g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_PAGING;
    }

    return;
}


VOS_UINT8 GMM_AuthType(VOS_UINT8 ucAutnFlag)
{
    VOS_UINT8                               usAuthTypeRet;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8         enCurRat;

    usAuthTypeRet = GMM_AUTH_FAILURE;
    enCurRat = NAS_MML_GetCurrNetRatType();
    switch (enCurRat)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:/*��UMTS������*/
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {   /*��������USIM��*/
                if (GMM_TRUE == ucAutnFlag)
                {
                    usAuthTypeRet = GMM_AUTH_UMTS;                      /*UMTS��Ȩ*/
                }
                else
                {
                    usAuthTypeRet = GMM_AUTH_GSM_AUTH_UNACCEPTABLE;     /*GSM authentication unacceptable*/
                }
            }
            else
            {
                if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
                {   /*��������SIM��*/
                    if (GMM_TRUE == ucAutnFlag)
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM��Ȩ*/
                    }
                    else
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM��Ȩ*/
                    }
                }
            }
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {   /*��������USIM��*/
                if (GMM_TRUE == ucAutnFlag)
                {
                    usAuthTypeRet = GMM_AUTH_UMTS;          /*UMTS��Ȩ*/
                }
                else
                {
                    usAuthTypeRet = GMM_AUTH_GSM;           /*GSM��Ȩ*/
                }
            }
            else
            {
                if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
                {   /*��������SIM��*/
                    if (GMM_TRUE == ucAutnFlag)
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM��Ȩ*/
                    }
                    else
                    {
                        usAuthTypeRet = GMM_AUTH_GSM;       /*GSM��Ȩ*/
                    }
                }
            }
            break;

        default:
            break;
    }

    /* ϵͳ���������UMTS��Ȩ */
    /*modify,sunxibo,2006-02-21,itt begin*/
    if ((GMM_FALSE == g_GmmAuthenCtrl.ucUmtsAuthFlg) && (GMM_AUTH_UMTS == usAuthTypeRet))
    /*modify,sunxibo,2006-02-21,itt end*/
    {
        usAuthTypeRet = GMM_AUTH_FAILURE;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvAuthenAndCipherRequestMsg:WARNING: perform the GSM authentication challenge");
    }

    return usAuthTypeRet;
}



VOS_VOID NAS_GMM_RauCompleteHandling( VOS_VOID )
{
    NAS_MSG_STRU                            *pSendNasMsg;
    GMM_MSG_RESOLVE_STRU                    stAttachAcceptIe;
    NAS_MSG_FOR_PCLINT_STRU                 stNasMsg;

    Gmm_MemSet(&stAttachAcceptIe, 0, sizeof(GMM_MSG_RESOLVE_STRU));
    Gmm_MemSet(&stNasMsg, 0, sizeof(NAS_MSG_STRU));

    /* ����RAU complete��Ϣ */
    if (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg)
    {
        gstGmmCasGlobalCtrl.ucRauCmpFlg = VOS_FALSE;
        pSendNasMsg = Gmm_RoutingAreaUpdateCompleteMsgMake();

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pSendNasMsg);



        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            /* ֻ��ǰ����й�RAU suspend���˴�resume�������� */
            if (GMM_SUSPEND_LLC_FOR_RAU == (gstGmmCasGlobalCtrl.ucSuspendLlcCause & GMM_SUSPEND_LLC_FOR_RAU))
            {
                gstGmmCasGlobalCtrl.ucSuspendLlcCause &= ~GMM_SUSPEND_LLC_FOR_RAU;

                if (GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
                {
                    GMM_SndLlcResumeReq(LL_GMM_RESUME_TYPE_ALL);                             /* �ָ�LLC���ݴ��� */
                }
            }

            gstGmmCasGlobalCtrl.ucCellUpdateFlg = GMM_FALSE;
            GMM_InitCellUpdate(GMM_FALSE);                                                   /* С�����£���Ч�µ�READY TIMER */
        }


        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
        g_GmmRauCtrl.ucPeriodicRauFlg = GMM_FALSE;
        NAS_INFO_LOG(WUEPS_PID_GMM, "NAS_GMM_RauCompleteHandling:INFO: specific procedure ended");
    }

    /* RABM����RSP��Ϣ�����¼������:
       1��NORMAL RAU�ɹ�
       2��ϵͳ����ѡ/�л��ɹ�
       3��ϵͳ����ѡ/�л�ʧ��

       GMM��ATTEMP COUNTER����5����������¼������:
       1��RAUʧ��
       2������RAUʧ��
       3������RAUֻ��PS�ɹ�
       ����GMM��֪ͨMM/MMCע����ʱ,Ӧ��ֻ���ڵ��������֪ͨ�ɹ�,
       �����������Ӧ��֪ͨʧ��,������Ϊ���յ�ע����ʱ�Ѿ�֪ͨ,���Դ˴���������*/
    if (5 <= g_GmmRauCtrl.ucRauAttmptCnt)
    {
        if ((GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState)
         || ( (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
           && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == gstGmmSuspendCtrl.ucPreState)))
        {
            NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_PS_ONLY,
                                           NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE,
                                           &stNasMsg,
                                           &stAttachAcceptIe);

            /* ��MMC����PSע���� */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                         NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE);

            /*  �¼��ϱ� */
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_RAU_SUCC,
                            VOS_NULL_PTR,
                            NAS_OM_EVENT_NO_PARA);
        }
    }

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_LOG_INFO("GMM_RauSuccessInterSys:Gmm rau success for intersystem change.");

        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;

        GMM_ResumeSuccess();
    }

    /*����follow on ������������¼� */
    NAS_GMM_HandleDelayedEvent();
}


/*****************************************************************************
  �� �� ��  : NAS_GMM_GetGmmCasGlobalCtrl
  ��������  : ��ȡȫ�ֱ���gstGmmCasGlobalCtrl�ĵ�ַ
  �������  : ��
  �������  : ��
  �� �� ֵ  : GMM_CAS_CTRL_STRU*
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���
*****************************************************************************/
GMM_CAS_CTRL_STRU* NAS_GMM_GetGmmCasGlobalCtrl(VOS_VOID)
{
    return &(gstGmmCasGlobalCtrl);
}

/*****************************************************************************
  �� �� ��  : NAS_GMM_GetMui
  ��������  : ��ȡȫ�ֱ���usMui��ֵ
  �������  : ��
  �������  : ��
  �� �� ֵ  : VOS_UINT16
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���
*****************************************************************************/
VOS_UINT16 NAS_GMM_GetMui(VOS_VOID)
{
    return (NAS_GMM_GetGmmCasGlobalCtrl()->usMui);
}

/*****************************************************************************
  �� �� ��  : NAS_GMM_IncreaseMui
  ��������  : usMui����
  �������  : ��
  �������  : ��
  �� �� ֵ  : VOS_UINT16
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���
*****************************************************************************/
VOS_UINT16 NAS_GMM_IncreaseMui(VOS_VOID)
{
    return ((NAS_GMM_GetGmmCasGlobalCtrl()->usMui)++);
}

/*****************************************************************************
  �� �� ��  : NAS_GMM_GetPowerOffDetachPsMui
  ��������  : ��ȡȫ�ֱ���usPowerOffDetachPsMui��ֵ
  �������  : ��
  �������  : ��
  �� �� ֵ  : VOS_UINT16
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���
*****************************************************************************/
VOS_UINT16 NAS_GMM_GetPowerOffDetachPsMui(VOS_VOID)
{
    return (NAS_GMM_GetGmmCasGlobalCtrl()->usPowerOffDetachPsMui);
}

/*****************************************************************************
  �� �� ��  : NAS_GMM_SetPowerOffDetachPsMui
  ��������  : ����usPowerOffDetachPsMui��ֵ
  �������  : VOS_UINT16                usMui
  �������  : ��
  �� �� ֵ  : ��
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_SetPowerOffDetachPsMui(
    VOS_UINT16                          usMui
)
{
    NAS_GMM_GetGmmCasGlobalCtrl()->usPowerOffDetachPsMui = usMui;

    return;
}

/*****************************************************************************
  �� �� ��  : NAS_GMM_IsPowerOffPsDetachMsg
  ��������  : �ж��Ƿ���PS�ػ�DETACH��Ϣ
  �������  : ��
  �������  : ��
  �� �� ֵ  : VOS_TRUE: �ǹػ�PS DETACH��Ϣ
              VOS_FALSE:
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsPowerOffPsDetachMsg(
    NAS_MSG_STRU                       *pstNasL3Msg
)
{
    VOS_UINT32                          ulUsimMMApiIsTestCard;
    ulUsimMMApiIsTestCard             = NAS_USIMMAPI_IsTestCard();

    /* �����ǰ�ǹػ����̣���Я��NeedCnf��־ */
    if ( (GMM_MSG_LEN_DETACH_REQUEST    <= pstNasL3Msg->ulNasMsgSize)
      && (GMM_PD_GMM                    == pstNasL3Msg->aucNasMsg[0])
      && (GMM_MSG_DETACH_REQUEST        == pstNasL3Msg->aucNasMsg[1])
      && ((GMM_GPRS_DETACH_POWEROFF     == pstNasL3Msg->aucNasMsg[2])
       || (GMM_COMBINED_DETACH_POWEROFF == pstNasL3Msg->aucNasMsg[2]))
      && (VOS_FALSE                     == ulUsimMMApiIsTestCard    ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
  �� �� ��  : NAS_GMM_GetCiphInd
  ��������  : ��ȡCiphInd
  �������  : ��
  �������  : ��
  �� �� ֵ  : VOS_UINT8
  ���ú���  :
  ��������  :

  �޸���ʷ  :
1.��    ��  : 2015��4��7��
  ��    ��  : wx270776
  �޸�����  : �����ɺ���:ԭ���߼����к�����װ
*****************************************************************************/
VOS_UINT8 NAS_GMM_GetCiphInd(
    NAS_MSG_STRU                       *pstNasL3Msg
)
{
    VOS_UINT8                           ucCiphInd;

    if (VOS_FALSE == gstGmmCasGlobalCtrl.ucGprsCipher)
    {
        ucCiphInd = 0;
    }
    else
    {
        if (GMM_PD_GMM == pstNasL3Msg->aucNasMsg[0])
        {
            switch(pstNasL3Msg->aucNasMsg[1])
            {
                case 0x01:
                case 0x04:
                case 0x12:
                case 0x13:
                case 0x14:
                case 0x1c:
                case 0x15:
                case 0x16:
                case 0x08:
                case 0x0B:
                    ucCiphInd = 0;
                    break;

                default:
                    ucCiphInd = 1;
                    break;
            }
        }
        else
        {
             ucCiphInd = 1;
        }
    }

    return ucCiphInd;
}

/*lint -restore */
#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
