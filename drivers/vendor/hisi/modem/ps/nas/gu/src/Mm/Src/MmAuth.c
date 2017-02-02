

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "MM_Inc.h"
#include "MmAuth.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_MM_AUTH_C


/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/

VOS_VOID MM_GsmAuthProc()
{

    /* ��Ȩ��Ӧ��Ϣ�ṹ */
    MM_MSG_AUTHENTICATION_RSP_STRU      stMsg;

    /* ����Ȩ�������(Rand,Cksn)���浽ȫ�ֱ����� */
    PS_MEM_CPY(g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
               g_MmMsgAuthReq.MmIeRAND.aucRandValue,
               16 * sizeof(VOS_UINT8)
               );


    /* ��ʼ�� Msg ���� */
    PS_MEM_SET(&stMsg, 0, sizeof(MM_MSG_AUTHENTICATION_RSP_STRU));

    /* �ɵ� Rand ��Ч */
    if (MM_AUTHEN_RAND_PRESENT == g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg)
    {
        if ((MM_FALSE == Mm_ComRandJudge()))  /* ��ǰ RAND ��ɵ���ͬ */
        {
            NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_NORMAL,
                    "MM_AuthProc: NORMAL: Rand same as the rand of last auth.");

            /* �ж�ǰ���� RAND �Ƿ���ͬ */
            if (MM_AUTHEN_RAND_DIFFER == g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat)
            {
                g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat  = MM_AUTHEN_RAND_REPEAT;
            }
            /* RES �� SRES ����,���ұ��μ�Ȩ�������ϴ���ͬ */
            else if ((MM_AUTHEN_RES_PRESENT == g_MmGlobalInfo.AuthenCtrlInfo.ucSresFlg)
                    && (AUTHENTICATION_REQ_GSM_CHALLENGE == g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType))
            {
                /* ֱ�ӽ��ϴε� SRES ���͵������ */
                PS_MEM_CPY(stMsg.MmIeAuthRspPara.aucSgnfcntRES,
                    g_MmGlobalInfo.AuthenCtrlInfo.aucRes, 4);

                NAS_MML_SetSimCsSecurityCksn(g_MmMsgAuthReq.MmIeCKSN.ucCksn);

                /* ����AUTHENTICATION RESPONSE */
                Mm_ComMsgAuthRspSnd(&stMsg);

                return;
            }
            else
            {

            }
        }
        else
        {
            /* ���� RAND ���ϴβ�ͬ��������Ӧ��־ */
            g_MmGlobalInfo.AuthenCtrlInfo.ucRandRepeat      = MM_AUTHEN_RAND_REPEAT;
        }
    }

    /* ���浱ǰ RAND */
    PS_MEM_CPY(
                g_MmGlobalInfo.AuthenCtrlInfo.aucOldRand,
                g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
                16 * sizeof(VOS_UINT8)
                );

    /* ���� RAND ���ڱ�ʶ�����RES���ڱ�־ */
    g_MmGlobalInfo.AuthenCtrlInfo.ucRandFlg  = MM_AUTHEN_RAND_PRESENT;
    g_MmGlobalInfo.AuthenCtrlInfo.ucResFlg   = MM_AUTHEN_RES_ABSENT;
    g_MmGlobalInfo.AuthenCtrlInfo.ucSresFlg  = MM_AUTHEN_RES_ABSENT;

    if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
    {

        /* ���ú��� MM_UsimGsmAuth ���д��� */
        MM_UsimGsmAuth();
    }
    else if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {

        /* ���ú��� MM_SimAuth ���д��� */
        MM_SimAuth();
    }
    else /* �쳣���, ��Ȩ���󱻶��� */
    {
        NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_ERROR,
                    "MM_AuthProc: ERROR: Sim type is unexpeted!");
    }

    return;
}
VOS_VOID MM_UsimGsmAuth()
{

    /* ���� GSM ��Ȩ���� */
    MM_SndGsmAuthenReq();

    return;
}
VOS_VOID MM_SimAuth()
{
    /* 24.008 If a SIM is inserted in the MS, the MS shall ignore
       the Authentication Parameter AUTN IE if included in the
       AUTHENTICATION REQUEST message and shall proceed as in
       case of a GSM authentication challenge */
    /* ���� GSM ��Ȩ���� */
    MM_SndGsmAuthenReq();

    return;
}
VOS_VOID MM_SndGsmAuthenReq()
{
    VOS_UINT8        ucTempOpId = 0;

    /* ����ȫ�ֱ�־,��ʾ�ȴ����� USIM/SIM ����Ȩ��Ӧ */
    g_MmGlobalInfo.ucRcvAgentFlg |= MM_RCV_AUTH_CNF_FLG;


    ucTempOpId = g_MmGlobalInfo.AuthenCtrlInfo.ucOpId;

    g_MmGlobalInfo.AuthenCtrlInfo.ucOpId = (VOS_UINT8)((ucTempOpId) % 255);
    g_MmGlobalInfo.AuthenCtrlInfo.ucOpId++;



    /* �� SIM/USIM ������ GSM ���ͼ�Ȩ���� */
    NAS_USIMMAPI_AuthReq(WUEPS_PID_MM,
                    AUTHENTICATION_REQ_GSM_CHALLENGE,
                    g_MmGlobalInfo.AuthenCtrlInfo.aucCurRand,
                    VOS_NULL,
                    g_MmGlobalInfo.AuthenCtrlInfo.ucOpId
                    );

    NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_NORMAL,
                    "MM_SndGsmAuthenReq: NORMAL: Send GSM CHALLENGE Auth Req!");

    g_MmGlobalInfo.AuthenCtrlInfo.ucLastAuthType = AUTHENTICATION_REQ_GSM_CHALLENGE;

    /* �������� TIMER */
    Mm_TimerStart(MM_TIMER_PROTECT_AGENT);

    return;
}


VOS_VOID MM_RcvSimAuthCnf(VOS_VOID* pMsg)
{
    /* ���� USIM/SIM ���͵ļ�Ȩ��Ӧ */
    if (MM_TRUE == MM_RcvGsmAuthenticationCnf(pMsg)) /* ���ռ�Ȩ��Ӧ���� */
    {
        /* ֹͣ������ʱ�� */
        Mm_TimerStop(MM_TIMER_PROTECT_AGENT);

        /* �Լ�Ȩ������� */
        if (AGENT_AUTH_RST_SUCCESS == g_AgentUsimAuthCnf.ucCheckRst)
        {
            /* ��Ȩ�ɹ����� */
            Mm_ComAuthenRcvUsimCnfSuccess();
        }
        else
        {
            /* ��Ȩʧ�ܴ��� */
            MM_HandleGsmAuthenFail();

        }
    }
    else /* �쳣������� */
    {
        MM_HandleGsmAuthenFail();

        NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_ERROR,
                    "MM_RcvSimAuthCnf: ERROR: Rcv Gsm Auth cnf error!");
    }

    return;
}
VOS_UINT8 MM_RcvGsmAuthenticationCnf(VOS_VOID* pMsg)
{
    /* �����Ȩǰ�õ�ȫ�ֱ�־ ucRcvAgentFlg */
    if (MM_RCV_AUTH_CNF_FLG
        != ( MM_RCV_AUTH_CNF_FLG & g_MmGlobalInfo.ucRcvAgentFlg))
    {
        /* �����ϲ㴦�� */
        NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_ERROR,
                    "MM_RcvGsmAuthenticationCnf: ERROR: Auth cnf is unexpected!");

        return MM_FALSE;
    }
    else
    {
        g_MmGlobalInfo.ucRcvAgentFlg &= ~MM_RCV_AUTH_CNF_FLG;
    }

    /* �� USIM/SIM �ļ�Ȩ��Ϣд��ȫ�ֱ��� g_AgentUsimAuthCnf �� */
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    Mm_Com_UsimAuthenticationCnfChgFormat((USIMM_AUTHENTICATION_CNF_STRU *)pMsg);
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */

    /* ���� g_AgentUsimAuthCnf �еļ�Ȩ��� */
    if (AGENT_AUTH_RST_SUCCESS == g_AgentUsimAuthCnf.ucCheckRst) /* ��Ȩ�ɹ� */
    {
        /* ���� SRES ���� */
        PS_MEM_CPY(g_MmGlobalInfo.AuthenCtrlInfo.aucRes,
                    g_AgentUsimAuthCnf.aucResponse, 4);

        /* ���� SRES ���ڱ�־ */
        g_MmGlobalInfo.AuthenCtrlInfo.ucSresFlg = MM_AUTHEN_RES_PRESENT;

        g_MmGlobalInfo.AuthenCtrlInfo.ucExtRspLength = 0;

        /* g_AgentUsimAuthCnf.ucKcLength Ϊ�� */
        if (MM_CONST_NUM_0 == g_AgentUsimAuthCnf.ucKcLength)
        {
            /* �쳣����������ϲ㴦�� */
            NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_ERROR,
                    "MM_RcvGsmAuthenticationCnf: ERROR: Sim didn't return Kc at GSM Auth!");

            return MM_FALSE;
        }
        else
        {
            /* �� KC ���浽ȫ�ֱ��� */
            NAS_MML_SetSimCsSecurityGsmKc(g_AgentUsimAuthCnf.aucKc);
        }

        /* ���ú��� NAS_MML_SecContext2GTO3G ��� IK��CK */
        NAS_MML_SecContext2GTO3G(g_AgentUsimAuthCnf.aucIntegrityKey, g_AgentUsimAuthCnf.aucCipheringKey,
                                 g_AgentUsimAuthCnf.aucKc);

        /* �� IK��CK �洢��ȫ�ֱ����� */
        NAS_MML_SetSimCsSecurityUmtsCk(g_AgentUsimAuthCnf.aucCipheringKey);
        NAS_MML_SetSimCsSecurityUmtsIk(g_AgentUsimAuthCnf.aucIntegrityKey);

        NAS_MML_SetSimCsSecurityCksn(g_MmMsgAuthReq.MmIeCKSN.ucCksn);

    }

    return MM_TRUE;
}
VOS_VOID MM_HandleGsmAuthenFail()
{

    /*MM_MSG_AUTHENTICATION_FAIL_STRU     stMsg;

    VOS_MemSet(&stMsg, 0, sizeof(MM_MSG_AUTHENTICATION_FAIL_STRU));

    stMsg.MmIeRejCause.ucRejCause = NAS_MML_REG_FAIL_CAUSE_PROTOCOL_ERROR;

    Mm_ComMsgAuthFailSnd(&stMsg);*/     /* ���� AUTHENTICATION FAILURE ��Ϣ */

    NAS_LOG(WUEPS_PID_MM, MM_AUTH, PS_LOG_LEVEL_WARNING,
                    "MM_HandleGsmAuthenFail: WARNING: Gsm Auth Fail!");

    return;
}



#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
