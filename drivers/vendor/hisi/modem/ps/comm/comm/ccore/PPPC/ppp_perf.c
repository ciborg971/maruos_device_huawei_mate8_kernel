/************************************************************************
*                                                                      *
*                             ppp_perf.c                               *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2013/04/17                                      *
*  Author:             wangyong                                        *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPPģ������ͳ��                                 *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
*  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
*                      ALL RIGHTS RESERVED                             *
*                                                                      *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_PERF_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/



/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */


VOID PPP_PerfStatisticByReleaseCode(PPPINFO_S *pstPppInfo)
{
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = NULL;
    ULONG ulResult = 0;

    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(1 == 0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_ERROR,
                     "\r\n [ppp]PPP_PerfStatisticByReleaseCode:  pstPppInfo=NULL!");
        return;
    }

    /*��ȡrp������*/
    ulResult = (ULONG)SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, (VOID**)&pstRpContext);
    if ((SDB_SUCCESS != ulResult) || (NULL == pstRpContext))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_PerfStatisticByReleaseCode: User %u isn't exist!", pstPppInfo->ulRPIndex);
        PPP_DBG_ERR_CNT(PPP_PHERR_540);
        return;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_PerfStatisticByReleaseCode: User [%u] ulReleaseCode [%u]!",
                 pstPppInfo->ulRPIndex, pstRpContext->ulReleaseCode);

    switch (pstRpContext->ulReleaseCode)
    {
        case AM_RELCODE_LAP_ALLOC_FAIL:
        case AM_RELCODE_LAP_NO_FREE_IP:                  /* û�п��е�ַ */
        case AM_RELCODE_LAP_CONFLICT:                    /* ��̬��ַ��ͻ */
        case AM_RELCODE_LAP_RECYLE:                      /* ��ַ���� */
            PPP_DBG_OK_CNT(PPP_PHOK_1208);
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_IPCP_ALLOC_IP_FAIL);
            break;
        default:
            PPP_DBG_OK_CNT(PPP_PHOK_1209);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                         "\r\n PPP_PerfStatisticByReleaseCode: User [%u] ulReleaseCode [%u] err!",
                         pstPppInfo->ulRPIndex, pstRpContext->ulReleaseCode);
            break;
    }

    return;
}


#define ___PPP_HSGW___

VOID SNMP_LCPPhaseProcForEhrpd(PPPINFO_S *pstPppInfo)
{
    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(1 == 0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_ERROR,
                     "\r\n [ppp]SNMP_LCPPhaseProcForEhrpd:  pstPppInfo=NULL!");
        return;
    }
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]SNMP_LCPPhaseProcForEhrpd:  Enter!ucFSMFailType[%u]", pstPppInfo->ucFSMFailType);

    switch(pstPppInfo->ucFSMFailType)
    {
        case FSM_ALARM_LCP_NEGOFAIL:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_LCP_NEGO_FAIL,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_LCP_NEGOFAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1210);
            break;
        }

        case FSM_ALARM_LCP_MS_NO_RSP:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_LCP_NO_RESPONSE,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
			PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_LCP_MS_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1211);
            break;
        }

        case FSM_ALARM_LCP_PCF_RELEASE:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_LCP_REL_A10,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_LCP_PCF_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1212);
            break;
        }

        case FSM_ALARM_LCP_MS_RELEASE:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_LCP_MS_TERM,
                                           pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                           1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_LCP_MS_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1213);
            break;
        }
        case FSM_ALARM_LCP_OTHER:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_LCP_OTHER,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_LCP_OTHER);
            PPP_DBG_OK_CNT(PPP_PHOK_1214);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_541);

            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                             "\r\n[SNMP_LCPPhaseProcForEhrpd]:LCP failtype = %u, bReNego = %u, bIpcpSucFlag = %u"
                             ", bIPTech = %u, bAuthClient = %u, bAuthServer = %u, bPppMode = %u",
                             pstPppInfo->ucFSMFailType,
                             pstPppInfo->bReNego,
                             pstPppInfo->bIpcpSucFlag,
                             pstPppInfo->bIPTech,
                             pstPppInfo->bAuthClient,
                             pstPppInfo->bAuthServer,
                             pstPppInfo->bPppMode);
            break;
        }
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1215);
#if 0
    A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_REQ_NUM,
                                    pstPppInfo->ulPcfIP,
                                    A11_PERF_OPERATOR_PLUS,
                                    1);
#endif
    if (VOS_TRUE != pstPppInfo->bIpcpSucFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1216);
#if 0
        A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_INIT_CONNCET_REQ_NUM,
                                        pstPppInfo->ulPcfIP,
                                        A11_PERF_OPERATOR_PLUS,
                                        1);
#endif
    }

    return;
}

VOID SNMP_AuthPhaseProcForEhrpd(PPPINFO_S *pstPppInfo)
{
    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(1 == 0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_ERROR,
                     "\r\n [ppp]SNMP_AuthPhaseProcForEhrpd:  pstPppInfo=NULL!");
        return;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]SNMP_AuthPhaseProcForEhrpd:  Enter!ucFSMFailType[%u]", pstPppInfo->ucFSMFailType);
    switch(pstPppInfo->ucFSMFailType)
    {
        case FSM_ALARM_AUTH_PCF_RELEASE:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_AUTH_REL_A10,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_AUTH_PCF_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1217);
            break;
        }

        case FSM_ALARM_AUTH_MS_NO_RSP:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_AUTH_MS_NO_REPONSE,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_AUTH_MS_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1218);
            break;
        }

        case FSM_ALARM_AUTH_MS_RELEASE:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_AUTH_MS_TERM,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_AUTH_MS_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1219);
            break;
        }
        case FSM_ALARM_AUTH_AAA_NO_RSP:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_AUTH_AAA_NO_REPONSE,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_AUTH_AAA_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1220);
            break;
        }
        case FSM_ALARM_AUTH_OTHER:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_AUTH_OTHER,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_AUTH_OTHER);
            PPP_DBG_OK_CNT(PPP_PHOK_1221);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_542);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                             "\r\n[SNMP_AuthPhaseProcForEhrpd]:AUTH failtype = %u, bReNego = %u, bIpcpSucFlag = %u"
                             ", bIPTech = %u, bAuthClient = %u, bAuthServer = %u, bPppMode = %u",
                             pstPppInfo->ucFSMFailType,
                             pstPppInfo->bReNego,
                             pstPppInfo->bIpcpSucFlag,
                             pstPppInfo->bIPTech,
                             pstPppInfo->bAuthClient,
                             pstPppInfo->bAuthServer,
                             pstPppInfo->bPppMode);
            return;
        }
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1222);
#if 0
    A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_REQ_NUM,
                                    pstPppInfo->ulPcfIP,
                                    A11_PERF_OPERATOR_PLUS,
                                    1);
#endif
    if (VOS_TRUE != pstPppInfo->bIpcpSucFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1223);
#if 0
        A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_INIT_CONNCET_REQ_NUM,
                                        pstPppInfo->ulPcfIP,
                                        A11_PERF_OPERATOR_PLUS,
                                        1);
#endif
    }


    return;
}


VOID SNMP_GetFailReasonByReleaseCode(ULONG ulReleaseCode, UCHAR *pucFailType)
{
    if ( NULL == pucFailType )
    {
        return;
    }

    switch ( ulReleaseCode )
    {

        case AM_RELCODE_PDN_PCRF_ACT_FAIL :
            *pucFailType = FSM_ALARM_EHRPD_VSNCP_PCRF_FAIL;
            break;

        case AM_RELCODE_PDN_PCRF_ACT_TIMOUT :
            *pucFailType = FSM_ALARM_EHRPD_VSNCP_PCRF_NO_RSP;
            break;

        case AM_RELCODE_PDN_PCRF_UPD_FAIL :
        case AM_RELCODE_PDN_PCRF_UPD_TIMOUT :
        case AM_RELCODE_PDN_PCRF_REL :
            *pucFailType = FSM_ALARM_EHRPD_VSNCP_PCRF_OTHER;
            break;

        case AM_RELCODE_PMIPV6_LMA_TOUT :
            *pucFailType = FSM_ALARM_EHRPD_VSNCP_PGW_NO_RSP;
            break;

        case AM_RELCODE_PMIPV6_LMA_FAIL :
            *pucFailType = FSM_ALARM_EHRPD_VSNCP_PGW_FAIL;
            break;

        case AM_RELCODE_PMIPV6_LMA_CHECK_ERR :
        case AM_RELCODE_PMIPV6_LIFE_TOUT :
        case AM_RELCODE_PMIPV6_PGW_REL_NORMAL :
        case AM_RELCODE_PMIPV6_PGW_REL_SAME_HAND :
        case AM_RELCODE_PMIPV6_PGW_REL_DIFF_HAND :
        case AM_RELCODE_PMIPV6_PGW_REL_UNKNOWN_HAND :
            *pucFailType = FSM_ALARM_EHRPD_VSNCP_PGW_OTHER;
            break;

        default:
            break;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]SNMP_GetFailReasonByReleaseCode: ulReleaseCode=%u, FailType=%d ", ulReleaseCode, *pucFailType);

    return;
}


VOID SNMP_VSNCPPhaseProc(PPPINFO_S *pstPppInfo)
{
    if(NULL == pstPppInfo)
    {
        VOS_DBGASSERT(1 == 0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_ERROR,
                     "\r\n [ppp]SNMP_VSNCPPhaseProc:  pstPppInfo=NULL!");
        return;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]SNMP_VSNCPPhaseProc:  Enter!ucFSMFailType[%u]", pstPppInfo->ucFSMFailType);
    switch(pstPppInfo->ucFSMFailType)
    {
        case FSM_ALARM_EHRPD_VSNCP_MS_NO_RSP:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_VSNCP_MS_NO_RESPONSE,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_MS_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1224);
            break;
        }

        case FSM_ALARM_EHRPD_VSNCP_PCF_RELEASE:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_VSNCP_REL_A10,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PCF_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1225);
            break;
        }

        case FSM_ALARM_EHRPD_VSNCP_MS_RELEASE:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_VSNCP_MS_TERM,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_MS_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1226);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_NEGOFAIL:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_VSNCP_NEGO_FAIL,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_NEGOFAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1227);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_OTHER:
        {
#if 0
            A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_FAIL_FOR_VSNCP_OTHER,
                                            pstPppInfo->ulPcfIP,
                                            A11_PERF_OPERATOR_PLUS,
                                            1);
#endif
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_OTHER);
            PPP_DBG_OK_CNT(PPP_PHOK_1228);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_PCRF_FAIL:
        {
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PCRF_FAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1460);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_PCRF_NO_RSP:
        {
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PCRF_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1461);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_PCRF_OTHER:
        {
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PCRF_OTHER);
            PPP_DBG_OK_CNT(PPP_PHOK_1462);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_PGW_FAIL:
        {
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PGW_FAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1463);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_PGW_NO_RSP:
        {
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PGW_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1464);
            break;
        }
        case FSM_ALARM_EHRPD_VSNCP_PGW_OTHER:
        {
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_EHRPD_VSNCP_PGW_OTHER);
            PPP_DBG_OK_CNT(PPP_PHOK_1465);
            break;
        }

        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_543);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                         "\r\n[SNMP_VSNCPPhaseProc]:IPCP failtype = %u, bReNego = %u, bIpcpSucFlag = %u"
                         ", bIPTech = %u, bAuthClient = %u, bAuthServer = %u, bPppMode = %u",
                         pstPppInfo->ucFSMFailType,
                         pstPppInfo->bReNego,
                         pstPppInfo->bIpcpSucFlag,
                         pstPppInfo->bIPTech,
                         pstPppInfo->bAuthClient,
                         pstPppInfo->bAuthServer,
                         pstPppInfo->bPppMode);

            break;
        }
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1229);
#if 0
    A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_CONNCET_REQ_NUM,
                                    pstPppInfo->ulPcfIP,
                                    A11_PERF_OPERATOR_PLUS,
                                    1);
#endif
    if (VOS_TRUE != pstPppInfo->bIpcpSucFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1230);
#if 0
        A11_OM_HSGWPerfStatisticPCFUnit(PERF_TYPE_EHRPD_PCF_PPP_INIT_CONNCET_REQ_NUM,
                                        pstPppInfo->ulPcfIP,
                                        A11_PERF_OPERATOR_PLUS,
                                        1);
#endif
    }

    return;
}


/*CR-0000060209*/
VOID SNMP_EhrpdUserDeaProc(SDB_PDSN_RP_CONTEXT_S * pstRpContext)
{
    PPPINFO_S *pstPppInfo = NULL;
    UCHAR eAlarmCode = FSM_ALARM_NULL;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]SNMP_EhrpdUserDeaProc:  Enter!");

    if ( NULL == pstRpContext )
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_ERROR,
                     "\r\n [ppp]SNMP_EhrpdUserDeaProc:  rpcontext null");
        return;
    }

    if ( (USM_STATE_ACTIVE <= pstRpContext->ucUsmState) || (VOS_TRUE != pstRpContext->beHRPDMode) )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_544);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_ERROR,
                     "\r\n [ppp]SNMP_EhrpdUserDeaProc:  ucUsmState=%d!", pstRpContext->ucUsmState);
        return;
    }

    /*����ȥ��ԭ��ֵ��ʱ���ȡ�ϱ�SNMP�澯ֵ*/
    GETPPPINFOPTRBYRP(pstPppInfo, pstRpContext->ulRpIndex);
    if (NULL == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_ERROR,
                     "\r\n User ppp %d doesn't exist!",
                     pstRpContext->ulRpIndex);
        return;
    }
    /* ����ȥ��ԭ��ֵ��ȡ �澯ԭ��ֵ */
    SNMP_GetFailReasonByReleaseCode(pstRpContext->ulReleaseCode, &eAlarmCode);
    /* ��������ͳ��ȥ��ԭ�� */
    if ( FSM_ALARM_NULL != eAlarmCode )
    {
        SNMP_SetFailReason(pstPppInfo, (FSM_ALARM_CODE_E)eAlarmCode);
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]SNMP_EhrpdUserDeaProc: ulReleaseCode = %u, AlarmCode = %d!",
                   pstRpContext->ulReleaseCode, eAlarmCode);
    return;
}


VOID SNMP_SetFailReasonForEhrpd(PPPINFO_S * pstPppInfo, FSM_ALARM_CODE_E enFailType)
{
    if (NULL == pstPppInfo)
    {
        return;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n SNMP_SetFailReasonForEhrpd: bPhaseFlag = %u, old FailType = %u, new FailType = %u",
                 pstPppInfo->bPhaseFlag,
                 pstPppInfo->ucFSMFailType,
                 enFailType);

    if ((PPP_SNMP_PERF_PHASE_LCP == pstPppInfo->bPhaseFlag)
        && (FSM_ALARM_LCP_NEGOFAIL != pstPppInfo->ucFSMFailType))
    {
        return;
    }
    else if ((PPP_SNMP_PERF_PHASE_AUTH == pstPppInfo->bPhaseFlag)
            && (FSM_ALARM_AUTH_OTHER != pstPppInfo->ucFSMFailType))
    {
        return;
    }
    else if ((PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag)
            && (FSM_ALARM_EHRPD_VSNCP_NEGOFAIL != pstPppInfo->ucFSMFailType))
    {
        return;
    }
    else if (PPP_SNMP_PERF_PHASE_SUCCESS== pstPppInfo->bPhaseFlag)
    {
        if (FSM_ALARM_NULL != enFailType)
        {
            return;
        }
    }

    if (VOS_OK != SNMP_CheckPhaseAndFailType(pstPppInfo->bPhaseFlag, enFailType))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_546);
        return;
    }

    pstPppInfo->ucFSMFailType = (UCHAR)enFailType;
    return;
}


#define ___PPP_PDSN___

VOID SNMP_LCPPhaseProc(PPPINFO_S *pstPppInfo)
{

    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(1 == 0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n [ppp]SNMP_LCPPhaseProc:  pstPppInfo=NULL!");
        return;
    }
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]SNMP_LCPPhaseProc:  Enter!ucFSMFailType[%u]", pstPppInfo->ucFSMFailType);

    if (PDSN_PPP_IPTYE_IPV6 == pstPppInfo->ucIpCapability)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_547);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n [ppp]SNMP_LCPPhaseProc:  pstPppInfo->ucIpCapability is single ipv6 !");
        return;
    }

    if (g_aulDoStatiscTime[0] + g_aulNoStatiscTime[0] >= 10)
    {
        g_aulDoStatiscTime[0] = 0;
        g_aulNoStatiscTime[0] = 0;
    }

    switch(pstPppInfo->ucFSMFailType)
    {
        case FSM_ALARM_LCP_NEGOFAIL:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_DISAGREEMENT,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_DISAGREEMENT,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_LCP_NEGOFAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1238);
            break;
        }

        case FSM_ALARM_LCP_MS_NO_RSP:
        {
            if (VOS_TRUE != pstPppInfo->bRecvLcpMsgFlag)
            {
                PPP_DBG_OK_CNT(PPP_PHOK_1239);
                return;
            }

            /*���ӱ�־�жϣ����δ�յ���LCP��Ϣ����ͳ��ʧ��*/
            if (0 == g_ulSoftPara585)
            {
                A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_MS_NO_RSP,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_MS_NO_RSP,
                                  PERF_ADD);
                PPP_DBG_OK_CNT(PPP_PHOK_1240);
            }
            else
            {
                if (g_aulNoStatiscTime[0] < g_ulSoftPara585)
                {
                    g_aulNoStatiscTime[0]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                      PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE,
                                      PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE,
                                      PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1241);
                }
                else
                {
                    g_aulDoStatiscTime[0]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                      PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_MS_NO_RSP,
                                      PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_MS_NO_RSP,
                                      PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1242);
                }
            }

            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_LCP_MS_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1243);
            break;
        }

        case FSM_ALARM_LCP_PCF_RELEASE:
        {
            if (0 == g_ulSoftPara585)
            {
                A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_PCF_RELEASE,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_PCF_RELEASE,
                                  PERF_ADD);
                PPP_DBG_OK_CNT(PPP_PHOK_1244);
            }
            else
            {
                if (g_aulNoStatiscTime[0] < g_ulSoftPara585)
                {
                    g_aulNoStatiscTime[0]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                      PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE,
                                      PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE,
                                      PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1245);
                }
                else
                {
                    g_aulDoStatiscTime[0]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_PCF_RELEASE,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_PCF_RELEASE,
                                  PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1246);
                }
            }

            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_LCP_PCF_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1247);
            break;
        }

        case FSM_ALARM_LCP_MS_RELEASE:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt, \
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE, \
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_LCP_MS_RELEASE,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_LCP_MS_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1248);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_548);

            if (0 == g_ulPppDBGStatisc[PPP_PHERR_548]%100)
            {
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                                 "\r\n[SNMP_LCPPhaseProc]:LCP failtype = %u, bReNego = %u, bIpcpSucFlag = %u"
                                 ", bIPTech = %u, bAuthClient = %u, bAuthServer = %u, bPppMode = %u",
                                 pstPppInfo->ucFSMFailType,
                                 pstPppInfo->bReNego,
                                 pstPppInfo->bIpcpSucFlag,
                                 pstPppInfo->bIPTech,
                                 pstPppInfo->bAuthClient,
                                 pstPppInfo->bAuthServer,
                                 pstPppInfo->bPppMode);
            }
            /*End of liushuang*/
            break;
        }
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1249);

    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                          PERF_TYPE_1X_PPP_NEGOTIATIONS,
                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS, PERF_ADD);
    if (VOS_TRUE != pstPppInfo->bIpcpSucFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1250);
        A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                              PERF_TYPE_1X_PPP_FIRST_NEGOTIATIONS,
                              PERF_TYPE_EVDO_PPP_FIRST_NEGOTIATIONS, PERF_ADD);
    }

    return;
}

VOID SNMP_AuthPhaseProc(PPPINFO_S *pstPppInfo)
{

    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(1 == 0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n [ppp]SNMP_AuthPhaseProc:  pstPppInfo=NULL!");
        return;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]SNMP_AuthPhaseProc:  Enter!ucFSMFailType[%u]", pstPppInfo->ucFSMFailType);

    if (PDSN_PPP_IPTYE_IPV6 == pstPppInfo->ucIpCapability)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_549);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n [ppp]SNMP_AuthPhaseProc:  pstPppInfo->ucIpCapability is single ipv6 !");
        return;
    }

    if (g_aulDoStatiscTime[1] + g_aulNoStatiscTime[1] >= 10)
    {
        g_aulDoStatiscTime[1] = 0;
        g_aulNoStatiscTime[1] = 0;
    }

    switch(pstPppInfo->ucFSMFailType)
    {
        case FSM_ALARM_AUTH_PCF_RELEASE:
        {
            if (0 == g_ulSoftPara586)
            {
                A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                      PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_PCF_RELEASE,
                                      PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_PCF_RELEASE, PERF_ADD);
                PPP_DBG_OK_CNT(PPP_PHOK_1251);
            }
            else
            {
                if (g_aulNoStatiscTime[1] < g_ulSoftPara586)
                {
                    g_aulNoStatiscTime[1]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE,
                                          PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1252);
                }
                else
                {
                    g_aulDoStatiscTime[1]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_PCF_RELEASE,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_PCF_RELEASE, PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1253);
                }
            }

            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_AUTH_PCF_RELEASE);
            PPP_DBG_OK_CNT(PPP_PHOK_1254);
            break;
        }

        case FSM_ALARM_AUTH_MS_NO_RSP:
        {
            if (0 == g_ulSoftPara586)
            {
                A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                      PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_MS_NO_RSP,
                                      PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_MS_NO_RSP, PERF_ADD);
                PPP_DBG_OK_CNT(PPP_PHOK_1255);
            }
            else
            {
                if (g_aulNoStatiscTime[1] < g_ulSoftPara586)
                {
                    g_aulNoStatiscTime[1]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE,
                                          PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1256);
                }
                else
                {
                    g_aulDoStatiscTime[1]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_MS_NO_RSP,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_MS_NO_RSP, PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1257);
                }
            }

            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_AUTH_MS_NO_RSP);

            PPP_DBG_OK_CNT(PPP_PHOK_1258);
            break;
        }

        case FSM_ALARM_AUTH_MS_RELEASE:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt, \
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE, \
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_MS_RELEASE,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_AUTH_MS_RELEASE);

            PPP_DBG_OK_CNT(PPP_PHOK_1259);
            break;
        }

        case FSM_ALARM_AUTH_ERROR_ACCOUNT:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_ERROR_ACCOUNT,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_ERROR_ACCOUNT,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
            PPP_DBG_OK_CNT(PPP_PHOK_1260);
            break;
        }

        case FSM_ALARM_AUTH_AAA_NO_RSP:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_AAA_NO_RSP,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_AAA_NO_RSP,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_AUTH_AAA_NO_RSP);
            PPP_DBG_OK_CNT(PPP_PHOK_1261);
            break;
        }
        case FSM_ALARM_AUTH_OTHER:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_AUTH_OTHER,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_AUTH_OTHER,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_AUTH_OTHER);
            PPP_DBG_OK_CNT(PPP_PHOK_1262);
            break;
        }

        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_550);

            if (0 == g_ulPppDBGStatisc[PPP_PHERR_550]%100)
            {
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                                 "\r\n[ppp_patch]:AUTH failtype = %u, bReNego = %u, bIpcpSucFlag = %u"
                                 ", bIPTech = %u, bAuthClient = %u, bAuthServer = %u, bPppMode = %u",
                                 pstPppInfo->ucFSMFailType,
                                 pstPppInfo->bReNego,
                                 pstPppInfo->bIpcpSucFlag,
                                 pstPppInfo->bIPTech,
                                 pstPppInfo->bAuthClient,
                                 pstPppInfo->bAuthServer,
                                 pstPppInfo->bPppMode);
            }
            return;
        }
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1263);

    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                          PERF_TYPE_1X_PPP_NEGOTIATIONS,
                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS, PERF_ADD);
    if (VOS_TRUE !=  pstPppInfo->bIpcpSucFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1264);
        A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                              PERF_TYPE_1X_PPP_FIRST_NEGOTIATIONS,
                              PERF_TYPE_EVDO_PPP_FIRST_NEGOTIATIONS, PERF_ADD);
    }


    return;
}
VOID SNMP_IPCPPhaseProc(PPPINFO_S *pstPppInfo)
{


    if(NULL == pstPppInfo)
    {
        VOS_DBGASSERT(1 == 0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n [ppp]SNMP_IPCPPhaseProc:  pstPppInfo=NULL!");
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n [ppp]SNMP_IPCPPhaseProc:  pstPppInfo=NULL!");
        return;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]SNMP_IPCPPhaseProc:   Enter!ucFSMFailType[%u]", pstPppInfo->ucFSMFailType);

    if (PDSN_PPP_IPTYE_IPV6 == pstPppInfo->ucIpCapability)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_551);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n [ppp]SNMP_IPCPPhaseProc:  pstPppInfo->ucIpCapability is single ipv6 !");
        return;
    }

    if (g_aulDoStatiscTime[2] + g_aulNoStatiscTime[2] >= 10)
    {
        g_aulDoStatiscTime[2] = 0;
        g_aulNoStatiscTime[2] = 0;
    }

    switch(pstPppInfo->ucFSMFailType)
    {
        case FSM_ALARM_IPCP_MS_NO_RSP:
        {
            if (0 == g_ulSoftPara587)
            {
                A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                      PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_NO_RSP,
                                      PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_NO_RSP,
                                      PERF_ADD);
                PPP_DBG_OK_CNT(PPP_PHOK_1265);
            }
            else
            {
                if (g_aulNoStatiscTime[2] < g_ulSoftPara587)
                {
                    g_aulNoStatiscTime[2]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
                                          PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1266);
                }
                else
                {
                    g_aulDoStatiscTime[2]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_NO_RSP,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_NO_RSP,
                                          PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1267);
                }
            }

            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_IPCP_MS_NO_RSP);

            PPP_DBG_OK_CNT(PPP_PHOK_1268);
            break;
        }

        case FSM_ALARM_IPCP_PCF_RELEASE:
        {
            if (0 == g_ulSoftPara587)
            {
                A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                      PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_PCF_RELEASE,
                                      PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_PCF_RELEASE, PERF_ADD);
                PPP_DBG_OK_CNT(PPP_PHOK_1269);
            }
            else
            {
                if (g_aulNoStatiscTime[2] < g_ulSoftPara587)
                {
                    g_aulNoStatiscTime[2]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
                                          PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1270);
                }
                else
                {
                    g_aulDoStatiscTime[2]++;
                    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                          PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_PCF_RELEASE,
                                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_PCF_RELEASE, PERF_ADD);
                    PPP_DBG_OK_CNT(PPP_PHOK_1271);
                }
            }

            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_IPCP_PCF_RELEASE);

            PPP_DBG_OK_CNT(PPP_PHOK_1272);
            break;
        }

        case FSM_ALARM_IPCP_MS_RELEASE:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_IPCP_MS_RELEASE);

            PPP_DBG_OK_CNT(PPP_PHOK_1273);
            break;
        }
        case FSM_ALARM_IPCP_NEGOFAIL:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_DISAGREEMENT,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_DISAGREEMENT,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_IPCP_NEGOFAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1274);
            break;
        }
        case FSM_ALARM_IPCP_ALLOC_IP_FAIL:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_IP,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_IP,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_IPCP_ALLOC_IP_FAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1275);

            break;
        }
        case FSM_ALARM_IPCP_OTHER:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_OTHER,
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_OTHER,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_IPCP_OTHER);
            PPP_DBG_OK_CNT(PPP_PHOK_1276);
            break;
        }

        case FSM_ALARM_IPCP_PCRF_FAIL:
        {
            A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt, \
                                  PERF_TYPE_1X_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE, \
                                  PERF_TYPE_EVDO_PPP_NEGOTIATIONS_FAIL_IPCP_MS_RELEASE,
                                  PERF_ADD);
            PPP_InsertAlarm(pstPppInfo, FSM_ALARM_IPCP_PCRF_FAIL);
            PPP_DBG_OK_CNT(PPP_PHOK_1277);
            break;
        }
        default:
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_552);

            if (0 == g_ulPppDBGStatisc[PPP_PHERR_552]%100)
            {
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                             "\r\n[SNMP_IPCPPhaseProc]:IPCP failtype = %u, bReNego = %u, bIpcpSucFlag = %u"
                             ", bIPTech = %u, bAuthClient = %u, bAuthServer = %u, bPppMode = %u",
                             pstPppInfo->ucFSMFailType,
                             pstPppInfo->bReNego,
                             pstPppInfo->bIpcpSucFlag,
                             pstPppInfo->bIPTech,
                             pstPppInfo->bAuthClient,
                             pstPppInfo->bAuthServer,
                             pstPppInfo->bPppMode);
            }
            /*End of liushuang*/
            break;
        }
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1278);

    A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                          PERF_TYPE_1X_PPP_NEGOTIATIONS,
                          PERF_TYPE_EVDO_PPP_NEGOTIATIONS, PERF_ADD);
    if (VOS_TRUE !=  pstPppInfo->bIpcpSucFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1279);
        A11_SNMP_PERFSTATISCS(pstPppInfo->usPcfIndex, pstPppInfo->ucServiceOpt,
                              PERF_TYPE_1X_PPP_FIRST_NEGOTIATIONS,
                              PERF_TYPE_EVDO_PPP_FIRST_NEGOTIATIONS, PERF_ADD);
    }

    return;
}

VOID SNMP_TerminatePhaseProc(PPPINFO_S *pstPppInfo)
{
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n [ppp]SNMP_TerminatePhaseProc:  Enter!");

    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(1 == 0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_ERROR,
                     "\r\n [ppp]SNMP_TerminatePhaseProc:  pstPppInfo=NULL!");
        return;
    }
    if (pstPppInfo->bEhrpdUser)
    {
        if (PPP_SNMP_PERF_PHASE_LCP == pstPppInfo->bPhaseFlag)
        {
            SNMP_LCPPhaseProcForEhrpd(pstPppInfo);
        }
        else if (PPP_SNMP_PERF_PHASE_AUTH == pstPppInfo->bPhaseFlag)
        {
            SNMP_AuthPhaseProcForEhrpd(pstPppInfo);
        }
        else if (PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag)
        {
            SNMP_VSNCPPhaseProc(pstPppInfo);
        }
    }
    else
    {
        if (PPP_SNMP_PERF_PHASE_LCP == pstPppInfo->bPhaseFlag)
        {
            SNMP_LCPPhaseProc(pstPppInfo);
        }
        else if (PPP_SNMP_PERF_PHASE_AUTH == pstPppInfo->bPhaseFlag)
        {
            SNMP_AuthPhaseProc(pstPppInfo);
        }
        else if (PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag)
        {
            SNMP_IPCPPhaseProc(pstPppInfo);
        }
    }
    return;
}


ULONG SNMP_CheckPhaseAndFailType(UCHAR ucPhase, UCHAR ucFailType)
{
    ULONG ulResult = VOS_ERR;

    if (0 == ucPhase)
    {
        switch (ucFailType)
        {
            case FSM_ALARM_LCP_MS_NO_RSP:
            case FSM_ALARM_LCP_MS_RELEASE:
            case FSM_ALARM_LCP_PCF_RELEASE:
            case FSM_ALARM_LCP_NEGOFAIL:
            case FSM_ALARM_LCP_OTHER:
            case FSM_ALARM_EHRPD_LCP_MS_NO_RSP:
            case FSM_ALARM_EHRPD_LCP_MS_RELEASE:
            case FSM_ALARM_EHRPD_LCP_PCF_RELEASE:
            case FSM_ALARM_EHRPD_LCP_NEGOFAIL:
            case FSM_ALARM_EHRPD_LCP_OTHER:
                ulResult = VOS_OK;
                break;
            default:
                break;
        }
    }
    else if (1 == ucPhase)
    {
        switch (ucFailType)
        {
            case FSM_ALARM_AUTH_ERROR_ACCOUNT:
            case FSM_ALARM_AUTH_AAA_NO_RSP:
            case FSM_ALARM_AUTH_MS_NO_RSP:
            case FSM_ALARM_AUTH_MS_RELEASE:
            case FSM_ALARM_AUTH_PCF_RELEASE:
            case FSM_ALARM_AUTH_OTHER:
            case FSM_ALARM_EHRPD_AUTH_AAA_NO_RSP:
            case FSM_ALARM_EHRPD_AUTH_MS_NO_RSP:
            case FSM_ALARM_EHRPD_AUTH_MS_RELEASE:
            case FSM_ALARM_EHRPD_AUTH_PCF_RELEASE:
            case FSM_ALARM_EHRPD_AUTH_OTHER:
                ulResult = VOS_OK;
                break;
            default:
                break;
        }
    }
    else if (2 == ucPhase)
    {
        switch (ucFailType)
        {
            case FSM_ALARM_IPCP_MS_NO_RSP:
            case FSM_ALARM_IPCP_MS_RELEASE:
            case FSM_ALARM_IPCP_PCF_RELEASE:
            case FSM_ALARM_IPCP_NEGOFAIL:
            case FSM_ALARM_IPCP_ALLOC_IP_FAIL:
            case FSM_ALARM_IPCP_OTHER:
            case FSM_ALARM_EHRPD_VSNCP_MS_NO_RSP:
            case FSM_ALARM_EHRPD_VSNCP_MS_RELEASE:
            case FSM_ALARM_EHRPD_VSNCP_PCF_RELEASE:
            case FSM_ALARM_EHRPD_VSNCP_NEGOFAIL:
            case FSM_ALARM_EHRPD_VSNCP_OTHER:
            case FSM_ALARM_EHRPD_VSNCP_PCRF_FAIL:
            case FSM_ALARM_EHRPD_VSNCP_PCRF_NO_RSP:
            case FSM_ALARM_EHRPD_VSNCP_PCRF_OTHER:
            case FSM_ALARM_EHRPD_VSNCP_PGW_FAIL:
            case FSM_ALARM_EHRPD_VSNCP_PGW_NO_RSP:
            case FSM_ALARM_EHRPD_VSNCP_PGW_OTHER:
                ulResult = VOS_OK;
                break;
            default:
                break;
        }
    }

    return ulResult;
}



VOID SNMP_SetFailReason(PPPINFO_S * pstPppInfo, FSM_ALARM_CODE_E enFailType)
{
    if (NULL == pstPppInfo)
    {
        return;
    }

    if (pstPppInfo->bEhrpdUser)
    {
        SNMP_SetFailReasonForEhrpd(pstPppInfo, enFailType);
        return;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\nSNMP_SetFailReason: bPhaseFlag = %u, old FailType = %u, new FailType = %u",
                 pstPppInfo->bPhaseFlag,
                 pstPppInfo->ucFSMFailType,
                 enFailType);

    if ((PPP_SNMP_PERF_PHASE_LCP == pstPppInfo->bPhaseFlag)
        && (FSM_ALARM_LCP_NEGOFAIL != pstPppInfo->ucFSMFailType))
    {
        return;
    }
    else if ((PPP_SNMP_PERF_PHASE_AUTH == pstPppInfo->bPhaseFlag)
            && (FSM_ALARM_AUTH_OTHER != pstPppInfo->ucFSMFailType))
    {
        return;
    }
    else if ((PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag)
            && (FSM_ALARM_IPCP_NEGOFAIL != pstPppInfo->ucFSMFailType))
    {
        return;
    }
    else if (PPP_SNMP_PERF_PHASE_SUCCESS == pstPppInfo->bPhaseFlag)
    {
        if (FSM_ALARM_NULL != enFailType)
        {
            return;
        }
    }

    if (VOS_OK != SNMP_CheckPhaseAndFailType(pstPppInfo->bPhaseFlag, enFailType))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_553);
        return;
    }

    pstPppInfo->ucFSMFailType = (UCHAR)enFailType;
    return;
}

VOID SNMP_SetDefaultFailTypeByPhase(PPPINFO_S * pstPppInfo)
{
    if (NULL == pstPppInfo)
    {
        return;
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\nSNMP_SetDefaultFailTypeByPhase: bPhaseFlag = %u",
                 pstPppInfo->bPhaseFlag);

    if  (PPP_SNMP_PERF_PHASE_LCP == pstPppInfo->bPhaseFlag)
    {
        pstPppInfo->ucFSMFailType = (UCHAR)FSM_ALARM_LCP_NEGOFAIL;
    }
    else if (PPP_SNMP_PERF_PHASE_AUTH == pstPppInfo->bPhaseFlag)
    {
        pstPppInfo->ucFSMFailType = (UCHAR)FSM_ALARM_AUTH_OTHER;
    }
    else if (PPP_SNMP_PERF_PHASE_NET == pstPppInfo->bPhaseFlag)
    {
        if (pstPppInfo->bEhrpdUser)
        {
            pstPppInfo->ucFSMFailType = (UCHAR)FSM_ALARM_EHRPD_VSNCP_NEGOFAIL;
        }
        else
        {
            pstPppInfo->ucFSMFailType = (UCHAR)FSM_ALARM_IPCP_NEGOFAIL;
        }
    }
    else
    {
        pstPppInfo->ucFSMFailType = (UCHAR)FSM_ALARM_NULL;
    }

    return;
}

VOS_UINT32 PerfSetFamPerfCounterByAddress(VOS_UINT32 *pCounterAddress, VOS_UINT32 udwOpType, VOS_UINT32 udwValue)
{
    if ((PPP_PERF_ADD == udwOpType) || (IPV6_ADD == udwOpType))
    {
        *pCounterAddress += udwValue;
    }
    else if ((IPV6_SUB == udwOpType) || (PPP_PERF_SUB == udwOpType))
    {
        *pCounterAddress -= udwValue;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : PPP_PerfInc
 ��������  : PPP����ͳ������
 �������  : VOS_SIZE_T ulPerfCounter
             VOS_UINT32 ulPerfType
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��6��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_PerfInc(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType, UCHAR ucEhrpdMode)
{
    ULONG ulRet = 0;

    if (VOS_TRUE == ucEhrpdMode)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1280);
        return;
    }

    ulRet = (ULONG)PerfSetFamPerfCounterByAddress(pulPerfCounter, PPP_PERF_ADD, 1);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_554);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                      "\r\n[PERF] %s: set fam perf counter fail! ulPerfType is %lu, ulPerfCounter is %lx.",
                      (CHAR *)(__FUNCTION__), ulPerfType, *pulPerfCounter);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_PerfDec
 ��������  : PPP����ͳ��
 �������  : VOS_SIZE_T ulPerfCounter
             VOS_UINT32 ulPerfType
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��6��
    ��    ��   : luofang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID PPP_PerfDec(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType, UCHAR ucEhrpdMode)
{
    ULONG ulRet = 0;

    if (VOS_TRUE == ucEhrpdMode)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1281);
        return;
    }

    ulRet = (ULONG)PerfSetFamPerfCounterByAddress(pulPerfCounter, PPP_PERF_SUB, 1);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_555);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                      "\r\n[PERF] %s: set fam perf counter fail! ulPerfType is %lu, ulPerfCounter is %lx.",
                      (CHAR *)(__FUNCTION__), ulPerfType, *pulPerfCounter);
    }

    return;
}


VOID IPV6_PerfInc(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType)
{
    (VOS_VOID)PerfSetFamPerfCounterByAddress(pulPerfCounter, IPV6_ADD, 1);

    return;
}


VOID IPV6_PerfDec(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType)
{
    (VOS_VOID)PerfSetFamPerfCounterByAddress(pulPerfCounter, IPV6_SUB, 1);

    return;
}

VOID A11_ReqNumSubProc(PPPINFO_S *pstPppInfo)
{
    if (NULL == pstPppInfo)
    {
        return;
    }

    if (pstPppInfo->bEhrpdUser)
    {
        return;
    }

    if ((0 == pstPppInfo->bPppSuccess)) /* �ñ�־������ʾ�Ƿ���Ҫ��1:��PPP�ɹ�����Ҫ�ټ������Ѿ���������Ҫ�ټ� */
    {
#if 0
        A11_OM_PerfStatisticCMUnit((ULONG)PERF_TYPE_PDSN_SESSION_ACTIV_REQ, A11_PERF_OPERATOR_SUB);
        A11_OM_PerfStatisticVPDSNUnit((ULONG)PERF_TYPE_VPDSN_SM_ACTIV_REQ, A11_PERF_OPERATOR_SUB);
#endif
        pstPppInfo->bPppSuccess = 1;
        PPP_DBG_OK_CNT(PPP_PHOK_1282);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1283);
    }

    return;
}


#define ___PPP_SNMP_ALARM____
ULONG InsertAlarmLink(PPPA11_AlarmLink_S *pstAlarmLink)
{
    PPPA11_AlarmLink_NODE_S *pstNode = NULL;

    if (g_stPppA11AlarmLink.ulAlarmCount >= PPP_A11_ALARM_MAX_NUM)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]InsertAlarmLink:  g_stPppA11AlarmLink.ulAlarmCount=%d is over 500!",
                     g_stPppA11AlarmLink.ulAlarmCount);
        PPP_DBG_OK_CNT(PPP_PHOK_1284);
        return VOS_OK;
    }

    pstNode = (PPPA11_AlarmLink_NODE_S *)PPP_Malloc(sizeof(PPPA11_AlarmLink_NODE_S));
    if (NULL == pstNode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_556);
        VOS_DBGASSERT(1 == 0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]InsertAlarmLink:  call PPP_Malloc failed!");
        return VOS_ERR;
    }

    VOS_MemSet(pstNode, 0, sizeof(PPPA11_AlarmLink_NODE_S));
    /* ��ֵ��pstNode */
    (VOID)VOS_MemCpy(&(pstNode->stNodeInfo), pstAlarmLink, sizeof(PPPA11_AlarmLink_S));
    pstNode->pNext = NULL;

    if (NULL == g_stPppA11AlarmLink.pHead)
    {
        /*�����һ�����*/
        g_stPppA11AlarmLink.pHead = pstNode;
        g_stPppA11AlarmLink.pEnd = pstNode;
    }
    else
    {
        /*�������������뵽��һ��λ��*/
        (g_stPppA11AlarmLink.pEnd)->pNext = pstNode;
        g_stPppA11AlarmLink.pEnd = pstNode;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_1285);
    g_stPppA11AlarmLink.ulAlarmCount++;

    return VOS_OK;
}
ULONG DeleteAlarmLink(PPPA11_AlarmLink_S *pstNodeInfo)
{
    PPPA11_AlarmLink_NODE_S *pstNode = NULL;

    if (NULL == pstNodeInfo)
    {
        VOS_DBGASSERT(1 == 0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]DeleteAlarmLink:  pstNodeInfo=NULL!");
        PPP_DBG_ERR_CNT(PPP_PHERR_557);
        return VOS_ERR;
    }

    pstNode = g_stPppA11AlarmLink.pHead;
    if(NULL == pstNode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_558);
        VOS_DBGASSERT(1 == 0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]DeleteAlarmLink:  g_stPppA11AlarmLink.ulAlarmCount=!0 but g_stPppA11AlarmLink.pHead=NULL!");
        return VOS_ERR;
    }

    if (pstNode == g_stPppA11AlarmLink.pEnd)
    {
        g_stPppA11AlarmLink.pHead = NULL;
        g_stPppA11AlarmLink.pEnd = NULL;
    }
    else
    {
        g_stPppA11AlarmLink.pHead = pstNode->pNext;
    }
    if (g_stPppA11AlarmLink.ulAlarmCount > 0)
    {
        g_stPppA11AlarmLink.ulAlarmCount--;
    }

    pstNode->pNext = NULL;

    (VOID)VOS_MemCpy(pstNodeInfo, &(pstNode->stNodeInfo), sizeof(PPPA11_AlarmLink_S));
    (VOID)PPP_Free(pstNode);
    pstNode = NULL;

    PPP_DBG_OK_CNT(PPP_PHOK_1286);
    return VOS_OK;
}

VOID PPP_A11_GetBSIDFromBCD(UCHAR *pucDst, const UCHAR *pucSrc, ULONG ulLength)
{
    UCHAR aucTmp[PPP_A11_ALARM_BSID_LENGTH + 1] = {0};
    ULONG i = 0;

    if ( NULL == pucSrc || NULL == pucDst )
    {
        return;
    }

    if (ulLength > PPP_A11_ALARM_BSID_BCD_LEN)
    {
        ulLength = PPP_A11_ALARM_BSID_BCD_LEN;
    }

    for (i = 0; i < ulLength; i++)
    {
        if ( i * 2 <= PPP_A11_ALARM_BSID_LENGTH  )
        {
            VOS_sprintf((VOS_INT8 *)(aucTmp + i * 2), "%02X\0", *(pucSrc + i));
        }
    }

    VOS_MemCpy(pucDst, aucTmp, PPP_A11_ALARM_BSID_LENGTH);

    return;
}


VOID PPP_InsertAlarm(PPPINFO_S *pstPppInfo, UCHAR enRetType)
{
    PPPA11_AlarmLink_S stAlarmLink = {0};
    ULONG ulRetVal = VOS_OK;
    ULONG ulTimeInSecHigh = 0;
    ULONG ulTimeInSecLow = 0;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL;
    UCHAR aucSubnet[A11_SUBNET_LENGTH + 1] = {0};

    if (0 == M_SPM_PDSN_SNMP_ACCESS_FUNCTION)  /* ���δ����*/
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1288);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n [ppp]PPP_InsertAlarm:  M_SPM_PDSN_SNMP_ACCESS_FUNCTION=0");
        return;
    }

    if(NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_561);
        VOS_DBGASSERT(1 == 0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_InsertAlarm:  pstPppInfo=NULL!");
        return;
    }

    ulRetVal = SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, &pstRpContext);
    if ((VOS_OK != ulRetVal) || (NULL == pstRpContext))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_562);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_InsertAlarm:  SDB_GetRpContextByIndex fail[%u][%u]!",
                     pstPppInfo->ulRPIndex, ulRetVal);
        return;
    }

    stAlarmLink.ulPDSNIP = g_ulA11RpifIp;
    stAlarmLink.ulPcfIP = pstPppInfo->ulPcfIP;
#if 0
    /* ��ȫ���� IMSI ���� */
    A11_EncryptImsiToString(&(pstPppInfo->stIMSI), stAlarmLink.ucIMSI);
    if (VOS_OK == A11_TmSince1970(&ulTimeInSecHigh, &ulTimeInSecLow))
    {
        stAlarmLink.ulTimestamp = ulTimeInSecLow;
    }
    else
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_InsertAlarm: VOS_TmSince1970 error.");
    }
#endif
    stAlarmLink.ucErrorCode = (UCHAR)enRetType;
    if (VOS_TRUE == pstRpContext->bBsidFlag)
    {
        PPP_A11_GetBSIDFromBCD(stAlarmLink.ucBSID, pstRpContext->ucBsId, PPP_A11_ALARM_BSID_BCD_LEN);
    }
    else
    {
        (VOID)VOS_MemCpy(stAlarmLink.ucBSID, "NULL", sizeof("NULL"));
    }

    if (0 != pstRpContext->aucSubnet[0])
    {
        (VOID)VOS_MemCpy(aucSubnet, pstRpContext->aucSubnet, A11_SUBNET_LENGTH);
        A11_4BitsToString((UCHAR *)aucSubnet, stAlarmLink.aucSubnet, PPP_A11_ALARM_SUBNET_LENGTH);
    }
    else
    {
        (VOID)VOS_MemCpy(stAlarmLink.aucSubnet, "NULL", sizeof("NULL"));
    }

    ulRetVal = InsertAlarmLink(&stAlarmLink);
    if (ulRetVal != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_563);
        VOS_DBGASSERT(1 == 0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_InsertAlarm:  InsertAlarmLink return err");
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1289);

    return;
}


ULONG PPP_A11_AlarmToFamEx(PPPA11_AlarmLink_S stAlarmReport)
{
    ULONG ulRetCode = VOS_ERR;
    VOID* pPara[7] = {0};
    UCHAR ParaLength[7] = {0};

    /*���ò�������*/
    ParaLength[0] = 4;
    ParaLength[1] = 4;
    ParaLength[2] = sizeof(stAlarmReport.ucIMSI);
    ParaLength[3] = 1;
    ParaLength[4] = 4;
    ParaLength[5] = sizeof(stAlarmReport.ucBSID);
    ParaLength[6] = sizeof(stAlarmReport.aucSubnet);

    /*���ò���ֵ*/
    pPara[0] = (VOID*)(&(stAlarmReport.ulPDSNIP));
    pPara[1] = (VOID*)(&(stAlarmReport.ulPcfIP));
    pPara[2] = (VOID*)(stAlarmReport.ucIMSI);
    pPara[3] = (VOID*)(&(stAlarmReport.ucErrorCode));
    pPara[4] = (VOID*)(&(stAlarmReport.ulTimestamp));
    pPara[5] = (VOID*)(stAlarmReport.ucBSID);
    pPara[6] = (VOID*)(stAlarmReport.aucSubnet);

    ulRetCode = (ULONG)AlarmToFamEx(ALM_GetAlmSlotCpuID(),
                                    (ULONG)MID_PPPC,
                                    (ULONG)M_ALM_USERACCESS_FAILURE_ALARM,
                                    M_ALM_TYPE_EVENT,
                                    7,
                                    ParaLength,
                                    pPara);
    if (VOS_OK != ulRetCode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_564);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_A11_AlarmToFamEx:  call AlarmToFamEx err: %d!",
                     ulRetCode);
        return VOS_ERR;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1290);

    return VOS_OK;
}

VOID PPP_A11_AlarmProc(VOID)
{
    PPPA11_AlarmLink_S stAlarmReport = {0};
    ULONG ulRetCode  = VOS_ERR;

    VOS_MemSet(&stAlarmReport, 0, sizeof(PPPA11_AlarmLink_S));
    if (0 == g_stPppA11AlarmLink.ulAlarmCount)
    {
        return;
    }

    ulRetCode = DeleteAlarmLink(&stAlarmReport);
    if (VOS_ERR == ulRetCode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_565);
        VOS_DBGASSERT(1 == 0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_A11_AlarmProc:  DeleteAlarmLink return err!");
        return;
    }

    ulRetCode = PPP_A11_AlarmToFamEx(stAlarmReport);
    if (VOS_ERR == ulRetCode)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_566);
        VOS_DBGASSERT(1 == 0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n [ppp]PPP_A11_AlarmProc:  PPP_A11_AlarmToFamEx return err!");
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_1291);

    return;
}


 VOS_VOID IPV6_PerfStatistic(ULONG ulMsgType)
 {
     switch (ulMsgType)
     {
         /*ipv6cpЭ�̳��Դ���*/
         case IPV6_IPV6CP_ATTEMPT:
         {
             IPV6_PerfInc( g_stIpv6PerfStatistic.ulIpv6CpNegoAttempt, PERF_TYPE_PPPC_IPV6CP_NEGO_REQ_NUM );
             g_aulIpv6Cnt[E_IPV6_PERF_STATIC_NEGO_ATTEMPT]++;
             break;
         }

         /*ipv6cpЭ�̳ɹ�����*/
         case IPV6_IPV6CP_SUCC:
         {
             IPV6_PerfInc( g_stIpv6PerfStatistic.ulIpv6CpNegoSucc, PERF_TYPE_PPPC_IPV6CP_NEGO_SUCC_NUM );
             g_aulIpv6Cnt[E_IPV6_PERF_STATIC_NEGO_SUCCESS]++;
             break;
         }

         default:
             break;

     }

     return;

 }


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
