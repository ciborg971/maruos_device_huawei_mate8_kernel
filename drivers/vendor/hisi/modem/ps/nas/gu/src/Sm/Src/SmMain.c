
#include "SmInclude.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "NasSmMultiMode.h"
#endif
#include "NVIM_Interface.h"
#include "MnComm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SM_MAIN_C


VOS_UINT8      g_ucSmSystemAppConfigAddr;

VOS_UINT8      g_ucSmTimerFiveExpireFlag = VOS_FALSE;

NAS_SM_GMM_ERR_CODE_MAP_STRU            g_astNasSmGmmErrCodeMapTbl[] =
{
    { SM_TAF_CAUSE_GMM_GPRS_NOT_SUPPORT,                    GMM_SM_CAUSE_GPRS_NOT_SUPPORT               },
    { SM_TAF_CAUSE_GMM_ATTACH_MAX_TIMES,                    GMM_SM_CAUSE_ATTACH_MAX_TIMES               },
    { SM_TAF_CAUSE_GMM_FORBID_LA,                           GMM_SM_CAUSE_FORBID_LA                      },
    { SM_TAF_CAUSE_GMM_AUTHENTICATION_FAIL,                 GMM_SM_CAUSE_AUTHENTICATION_FAIL            },
    { SM_TAF_CAUSE_GMM_AUTHENTICATION_REJ,                  GMM_SM_CAUSE_AUTHENTICATION_REJ             },
    { SM_TAF_CAUSE_GMM_PS_DETACH,                           GMM_SM_CAUSE_PS_DETACH                      },
    { SM_TAF_CAUSE_GMM_RRC_EST_FAIL,                        GMM_SM_CAUSE_RRC_EST_FAIL                   },
    { SM_TAF_CAUSE_GMM_ACCESS_BARRED,                       GMM_SM_CAUSE_ACCESS_BARRED                  },
    { SM_TAF_CAUSE_GMM_SIM_PS_DOMAIN_REG_INVALID,           GMM_SM_CAUSE_SIM_PS_DOMAIN_REG_INVALID      },
    { SM_TAF_CAUSE_GMM_T3310_EXPIRED,                       GMM_SM_CAUSE_T3310_EXPIRED                  },
    { SM_TAF_CAUSE_GMM_T3317_EXPIRED,                       GMM_SM_CAUSE_T3317_EXPIRED                  },
    { SM_TAF_CAUSE_GMM_TIMER_SIGNALING_PROTECT_EXPIRED,     GMM_SM_CAUSE_TIMER_SIGNALING_PROTECT_EXPIRED},
    { SM_TAF_CAUSE_GMM_STARTUP,                             GMM_SM_CAUSE_STARTUP                        },
    { SM_TAF_CAUSE_GMM_NULL,                                GMM_SM_CAUSE_NULL                           },
    { SM_TAF_CAUSE_GMM_RESET,                               GMM_SM_CAUSE_GMM_RESET                      },
    { SM_TAF_CAUSE_GMM_RAU_ACCEPT,                          GMM_SM_CAUSE_RAU_ACCEPT                     },
    { SM_TAF_CAUSE_GMM_SERVICE_ACCEPT,                      GMM_SM_CAUSE_SERVICE_ACCEPT                 },
    { SM_TAF_CAUSE_GMM_UNKNOWN,                             GMM_SM_CAUSE_UNKNOWN                        },

    { SM_TAF_CAUSE_GMM_NW_IMSI_UNKNOWN_IN_HLR,              GMM_SM_CAUSE_IMSI_UNKNOWN_IN_HLR            },
    { SM_TAF_CAUSE_GMM_NW_ILLEGAL_MS,                       GMM_SM_CAUSE_ILLEGAL_MS                     },
    { SM_TAF_CAUSE_GMM_NW_IMSI_NOT_ACCEPTED,                GMM_SM_CAUSE_IMSI_NOT_ACCEPTED              },
    { SM_TAF_CAUSE_GMM_NW_ILLEGAL_ME,                       GMM_SM_CAUSE_ILLEGAL_ME                     },
    { SM_TAF_CAUSE_GMM_NW_GPRS_SERV_NOT_ALLOW,              GMM_SM_CAUSE_GPRS_SERV_NOT_ALLOW            },
    { SM_TAF_CAUSE_GMM_NW_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW, GMM_SM_CAUSE_GPRS_SERV_AND_NON_GPRS_SERV_NOT_ALLOW },
    { SM_TAF_CAUSE_GMM_NW_MS_ID_NOT_DERIVED,                 GMM_SM_CAUSE_MS_ID_NOT_DERIVED             },
    { SM_TAF_CAUSE_GMM_NW_IMPLICIT_DETACHED,                 GMM_SM_CAUSE_IMPLICIT_DETACHED             },
    { SM_TAF_CAUSE_GMM_NW_PLMN_NOT_ALLOW,                    GMM_SM_CAUSE_PLMN_NOT_ALLOW                },
    { SM_TAF_CAUSE_GMM_NW_LA_NOT_ALLOW,                      GMM_SM_CAUSE_LA_NOT_ALLOW                  },
    { SM_TAF_CAUSE_GMM_NW_ROAMING_NOT_ALLOW_IN_LA,           GMM_SM_CAUSE_ROAMING_NOT_ALLOW_IN_LA       },
    { SM_TAF_CAUSE_GMM_NW_GPRS_SERV_NOT_ALLOW_IN_PLMN,       GMM_SM_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN   },
    { SM_TAF_CAUSE_GMM_NW_NO_SUITABL_CELL,                   GMM_SM_CAUSE_NO_SUITABL_CELL               },
    { SM_TAF_CAUSE_GMM_NW_MSC_UNREACHABLE,                   GMM_SM_CAUSE_MSC_UNREACHABLE               },
    { SM_TAF_CAUSE_GMM_NW_NETWORK_FAILURE,                   GMM_SM_CAUSE_NETWORK_FAILURE               },
    { SM_TAF_CAUSE_GMM_NW_MAC_FAILURE,                       GMM_SM_CAUSE_MAC_FAILURE                   },
    { SM_TAF_CAUSE_GMM_NW_SYNCH_FAILURE,                     GMM_SM_CAUSE_SYNCH_FAILURE                 },
    { SM_TAF_CAUSE_GMM_NW_PROCEDURE_CONGESTION,              GMM_SM_CAUSE_PROCEDURE_CONGESTION          },
    { SM_TAF_CAUSE_GMM_NW_GSM_AUT_UNACCEPTABLE,              GMM_SM_CAUSE_GSM_AUT_UNACCEPTABLE          },
    { SM_TAF_CAUSE_GMM_NW_NOT_AUTHORIZED_FOR_THIS_CSG,       GMM_SM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG   },
    { SM_TAF_CAUSE_GMM_NW_NO_PDP_CONTEXT_ACT,                GMM_SM_CAUSE_NO_PDP_CONTEXT_ACT            },
    { SM_TAF_CAUSE_GMM_NW_RETRY_UPON_ENTRY_CELL,             GMM_SM_CAUSE_RETRY_UPON_ENTRY_CELL         },
    { SM_TAF_CAUSE_GMM_NW_SEMANTICALLY_INCORRECT_MSG,        GMM_SM_CAUSE_SEMANTICALLY_INCORRECT_MSG    },
    { SM_TAF_CAUSE_GMM_NW_INVALID_MANDATORY_INF,             GMM_SM_CAUSE_INVALID_MANDATORY_INF         },
    { SM_TAF_CAUSE_GMM_NW_MSG_NONEXIST_NOTIMPLEMENTE,        GMM_SM_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE    },
    { SM_TAF_CAUSE_GMM_NW_MSG_TYPE_NOT_COMPATIBLE,           GMM_SM_CAUSE_MSG_TYPE_NOT_COMPATIBLE       },
    { SM_TAF_CAUSE_GMM_NW_IE_NONEXIST_NOTIMPLEMENTED,        GMM_SM_CAUSE_IE_NONEXIST_NOTIMPLEMENTED    },
    { SM_TAF_CAUSE_GMM_NW_CONDITIONAL_IE_ERROR,              GMM_SM_CAUSE_CONDITIONAL_IE_ERROR          },
    { SM_TAF_CAUSE_GMM_NW_MSG_NOT_COMPATIBLE,                GMM_SM_CAUSE_MSG_NOT_COMPATIBLE            },
    { SM_TAF_CAUSE_GMM_NW_PROTOCOL_ERROR,                    GMM_SM_CAUSE_PROTOCOL_ERROR                }
};

NAS_MNTN_SM_INFO_STRU                   g_stNasMntnErrorlogSm;

/*******************************************************************************
  Module:      SM_ReportN2MOtaMsg
  Function:    ��trace�й�ȡSM�Ŀտ���Ϣ
  Input:       VOS_UINT8       ucMsgType   SM msg type
               NAS_MSG_STRU*   pNasMsg     SM�տ���Ϣ
  NOTE:
  Return:      VOS_VOID
  History:
      1. ³��    2009.07.11   �¹�����
*******************************************************************************/
VOS_VOID SM_ReportN2MOtaMsg(VOS_UINT8 ucMsgType, NAS_MSG_STRU *pNasMsg)
{
    NAS_OTA_MSG_ID_ENUM_UINT16 usNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_ReportN2MOtaMsg:NORMAL: msg type is ", ucMsgType);

    switch(ucMsgType)
    {
        case SM_REQ_PDP_CONTEXT_ACT:
            usNasOtaMsyId = NAS_OTA_MSG_REQ_PDP_CONTEXT_ACT;
            break;

        case SM_ACT_PDP_CONTEXT_ACC:
            usNasOtaMsyId = NAS_OTA_MSG_ACT_PDP_CONTEXT_ACC;
            break;

        case SM_ACT_PDP_CONTEXT_REJ:
            usNasOtaMsyId = NAS_OTA_MSG_ACT_PDP_CONTEXT_REJ;
            break;

        case SM_ACT_SEC_PDP_CONTEXT_ACC:
            usNasOtaMsyId = NAS_OTA_MSG_ACT_SEC_PDP_CONTEXT_ACC;
            break;

        case SM_ACT_SEC_PDP_CONTEXT_REJ:
            usNasOtaMsyId = NAS_OTA_MSG_ACT_SEC_PDP_CONTEXT_REJ;
            break;

        case SM_MOD_PDP_CONTEXT_REQ_N2M:
            usNasOtaMsyId = NAS_OTA_MSG_MOD_PDP_CONTEXT_REQ_N2M;
            break;

        case SM_MOD_PDP_CONTEXT_ACC_N2M:
            usNasOtaMsyId = NAS_OTA_MSG_MOD_PDP_CONTEXT_ACC_N2M;
            break;

        case SM_MOD_PDP_CONTEXT_REJ:
            usNasOtaMsyId = NAS_OTA_MSG_MOD_PDP_CONTEXT_REJ;
            break;

        case SM_DEACT_PDP_CONTEXT_REQ:
            usNasOtaMsyId = NAS_OTA_MSG_DEACT_PDP_CONTEXT_NET_REQ;
            break;

        case SM_DEACT_PDP_CONTEXT_ACC:
            usNasOtaMsyId = NAS_OTA_MSG_DEACT_PDP_CONTEXT_ACC;
            break;

        case SM_STATUS:
            usNasOtaMsyId = NAS_OTA_MSG_SM_STATUS;
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "SM_ReportN2MOtaMsg:WARNING: invalid msg type!");
            /*������SM�Ŀտ���Ϣ������trace����ʾ*/
            return;
    }

    NAS_SendAirMsgToOM(WUEPS_PID_SM, usNasOtaMsyId, NAS_OTA_DIRECTION_DOWN, pNasMsg->ulNasMsgSize + 4, (VOS_UINT8*)pNasMsg);
}


#ifdef __PS_WIN32_RECUR__
VOS_VOID NAS_SM_Restore_SmEntity(SM_ENTITY_STRU  *pSmEntity)
{
    int i;

    for (i = 0; i < SM_MAX_NSAPI_NUM; i++)
    {
        pSmEntity->aHoldMsg[i].pHoldRcvMsg = g_SmEntity.aHoldMsg[i].pHoldRcvMsg;
        pSmEntity->aPdpCntxtList[i].pHoldSndMsg = g_SmEntity.aPdpCntxtList[i].pHoldSndMsg;
    }

    PS_MEM_CPY(&g_SmEntity, pSmEntity, sizeof(SM_ENTITY_STRU));

    return;
}


VOS_VOID NAS_SM_Restore_SmPdpAddrApn(SM_PDP_ADDR_AND_APN_STRU  *pSmPdpAddrApn)
{
    PS_MEM_CPY(&g_SmPdpAddrApn, pSmPdpAddrApn, sizeof(SM_PDP_ADDR_AND_APN_STRU));

    return;
}



VOS_UINT32 NAS_SM_RestoreContextData(struct MsgCB * pMsg)
{
    NAS_SM_SDT_MSG_ST                      *pRcvMsgCB;
    NAS_SM_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;

    pRcvMsgCB     = (NAS_SM_SDT_MSG_ST *)pMsg;

    if (EVT_NAS_SM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY == pRcvMsgCB->usMsgID)
    {
        pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

        g_ucTiExt = pstOutsideCtx->pc_g_ucTiExt;
        PS_MEM_CPY(g_TiMapToNsapi, pstOutsideCtx->pc_g_TiMapToNsapi, 256);
        PS_MEM_CPY(g_CrMapToNsapi, pstOutsideCtx->pc_g_CrMapToNsapi, 256);
        PS_MEM_CPY(g_aucSapi, pstOutsideCtx->pc_g_aucSapi, (SM_MAX_NSAPI_NUM + SM_NSAPI_OFFSET)*2);

        NAS_SM_Restore_SmEntity(&pstOutsideCtx->pc_g_SmEntity);
        NAS_SM_Restore_SmPdpAddrApn(&pstOutsideCtx->pc_g_SmPdpAddrApn);

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM: NAS_SM_RestoreContextData - data is restored.");
    }
    return SM_TRUE;
}
#endif


VOS_VOID NAS_SM_SndOutsideContextData()
{
    NAS_SM_SDT_MSG_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_SM_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;

    pSndMsgCB = (NAS_SM_SDT_MSG_ST *)PS_ALLOC_MSG(WUEPS_PID_SM, sizeof(NAS_SM_SDT_MSG_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_SM_SndOutsideContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;

    pstOutsideCtx->pc_g_ucTiExt = g_ucTiExt;
    PS_MEM_CPY(pstOutsideCtx->pc_g_TiMapToNsapi, g_TiMapToNsapi, 256);
    PS_MEM_CPY(pstOutsideCtx->pc_g_CrMapToNsapi, g_CrMapToNsapi, 256);
    PS_MEM_CPY(pstOutsideCtx->pc_g_aucSapi, g_aucSapi, (SM_MAX_NSAPI_NUM + SM_NSAPI_OFFSET)*2);

    PS_MEM_CPY(&pstOutsideCtx->pc_g_SmEntity, &g_SmEntity, sizeof(SM_ENTITY_STRU));
    PS_MEM_CPY(&pstOutsideCtx->pc_g_SmPdpAddrApn, &g_SmPdpAddrApn, sizeof(SM_PDP_ADDR_AND_APN_STRU));

    pSndMsgCB->ulReceiverPid = WUEPS_PID_SM;
    pSndMsgCB->ulSenderPid   = WUEPS_PID_SM;
    pSndMsgCB->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength      = sizeof(NAS_SM_OUTSIDE_RUNNING_CONTEXT_ST) + 4;
    pSndMsgCB->usMsgID       = EVT_NAS_SM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;
    pSndMsgCB->usReserved    = 0;

    DIAG_TraceReport(pSndMsgCB);
    PS_FREE_MSG(WUEPS_PID_SM, pSndMsgCB);

    return;
}


VOS_VOID Sm_TaskEntry( struct MsgCB* pMsg )
{
    MSG_HEADER_STRU         *pHeader;                                           /* ������Ϣͷָ��                           */
    REL_TIMER_MSG           *pTimer;                                            /* ����TIMER��Ϣָ��                        */

    pHeader = (MSG_HEADER_STRU *) pMsg;                                         /* ��ȡ��Ϣͷָ��                           */
    pTimer  = (REL_TIMER_MSG *) pMsg;                                           /* ��ȡTIMER��Ϣָ��                        */

    if ( VOS_PID_TIMER == pMsg->ulSenderPid)
    {                                                                       /* �����TIMER��Ϣ                          */
        SM_RcvTimerMsgDistr( pTimer->ulPara );                              /* TIMER�����Ϣ�ַ�����                    */
    }
    else
    {
        switch(pHeader->ulSenderPid)
        {
        case MSP_PID_DIAG_APP_AGENT:
            /*SM_AgentMsgDistr( ( VOS_VOID * )pMsg );*/                         /* AGENTԭ��ַ�                            */
            Sm_OmQuery( ( VOS_VOID * )pMsg );
            break;
        case WUEPS_PID_TAF:/*Modified by Jim for prj*/
            NAS_SM_RcvTafMsg( pHeader );                                      /* TAFԭ��ַ�                              */
            break;
        case WUEPS_PID_GMM:
            SM_GmmMsgDistr( ( VOS_VOID * )pMsg );                               /* GMMԭ��ַ�                              */
            break;
        case WUEPS_PID_RABM:
            SM_RabmMsgDistr( ( VOS_VOID * )pMsg );                              /* RABMԭ��ַ�                             */
            break;
        case WUEPS_PID_ADMIN:
            break;
#ifdef __PS_WIN32_RECUR__
        case WUEPS_PID_SM:
            NAS_SM_RestoreContextData(pMsg);
            break;
#endif
        default:
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING, "LogRecord_Timer_HW:WARNING:SM: SenderPid error!");
            break;
        }
    }

#ifndef __PS_WIN32_RECUR__
    NAS_SM_SndOutsideContextData();
#endif
}
VOS_UINT8* SM_GetSystemAppConfigAddr(VOS_VOID)
{
    return &g_ucSmSystemAppConfigAddr;
}


VOS_VOID  SM_ReadSystemAppConfigNV(VOS_VOID)
{
    VOS_UINT8                                      *pucSystemAppConfig;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU                 stSysAppConfig;


    stSysAppConfig.usSysAppConfigType= SYSTEM_APP_BUTT;


    /* ��ȡ�������Ե�NV�����ĵ�ַ */
    pucSystemAppConfig                  = SM_GetSystemAppConfigAddr();


    /*��ȡʧ�ܰ�Ĭ��ֵ���� */
    if (VOS_OK != NV_Read(en_NV_Item_System_APP_Config,&stSysAppConfig,sizeof(VOS_UINT16)))
    {
        *pucSystemAppConfig  = SYSTEM_APP_MP;
        return;
    }

    if ( SYSTEM_APP_ANDROID < stSysAppConfig.usSysAppConfigType)
    {
        *pucSystemAppConfig  = SYSTEM_APP_MP;
    }
    else
    {
        *pucSystemAppConfig  = (VOS_UINT8)stSysAppConfig.usSysAppConfigType;
    }

    return;
}


VOS_VOID SM_Init()
{
    SM_ENTITY_STRU                     *pstSmEntity     = VOS_NULL_PTR;
    SM_PDP_ADDR_AND_APN_STRU           *pstSmPdpAddrApn = VOS_NULL_PTR;
    VOS_UINT8                          *pucTiMapToNsapi = VOS_NULL_PTR;
    VOS_UINT8                          *pucCrMapToNsapi = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstSmEntity     = NAS_SM_GetSmEntity();
    pstSmPdpAddrApn = NAS_SM_GetSmPdpAddrApn();
    pucTiMapToNsapi = NAS_SM_GetTiMapToNsapi();
    pucCrMapToNsapi = NAS_SM_GetCrMapToNsapi();

    SM_MemSet((VOS_VOID *)pstSmEntity,0, sizeof(SM_ENTITY_STRU));
    SM_MemSet(pstSmPdpAddrApn, 0, sizeof(SM_PDP_ADDR_AND_APN_STRU));
    SM_MemSet(pucTiMapToNsapi, (VOS_CHAR)0xFF, 256);
    SM_MemSet(pucCrMapToNsapi, (VOS_CHAR)0xFF, 256);

    SM_MemSet(&g_stNasMntnErrorlogSm, 0, sizeof(g_stNasMntnErrorlogSm));

    NAS_SM_SetTiExt(SM_FALSE);                                                  /* ��ʼ��TIû����չ��־                     */

    SM_ReadSystemAppConfigNV();

    /*��ʼ�����SAPI������*/
    for(i = 0; i < (SM_MAX_NSAPI_NUM + SM_NSAPI_OFFSET) ; i++)
    {
        NAS_SM_GetSapi(i)[0] = 0;
    }

    /* ��ʼ��SGSN�汾��ϢΪ"R99���Ժ�汾" */
    NAS_SM_SetSmSgsnVersion(GMMSM_SGSN_RELEASE99_ONWARDS);

    return;
}
VOS_VOID NAS_SM_RcvTafMsg(
    MSG_HEADER_STRU                    *pMsg
)
{
    switch (pMsg->ulMsgName)
    {
        case ID_SMREG_PDP_ACTIVATE_REQ:
            NAS_SM_RcvTafPdpCnxtActReq((SMREG_PDP_ACTIVATE_REQ_STRU*)pMsg);
            break;

        case ID_SMREG_PDP_ACTIVATE_REJ_RSP:
            NAS_SM_RcvTafPdpCnxtActRejRsp((SMREG_PDP_ACTIVATE_REJ_RSP_STRU*)pMsg);
            break;

        case ID_SMREG_PDP_MODIFY_REQ:
            NAS_SM_RcvTafPdpCntxtModifyReq((SMREG_PDP_MODIFY_REQ_STRU*)pMsg);
            break;

        case ID_SMREG_PDP_DEACTIVATE_REQ:
            NAS_SM_RcvTafPdpCnxtDeActReq((SMREG_PDP_DEACTIVATE_REQ_STRU*)pMsg);
            break;

        case ID_SMREG_PDP_ACTIVATE_SEC_REQ:
            NAS_SM_RcvTafPdpCnxtActSecReq((SMREG_PDP_ACTIVATE_SEC_REQ_STRU*)pMsg);
            break;

        case ID_SMREG_PDP_MODIFY_RSP:
            NAS_SM_RcvTafPdpModifyRsp((SMREG_PDP_MODIFY_RSP_STRU*)pMsg);
            break;

        case ID_SMREG_PDP_MODIFY_REJ_RSP:
            NAS_SM_RcvTafPdpModifyRejRsp((SMREG_PDP_MODIFY_REJ_RSP_STRU*)pMsg);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case ID_SMREG_BEARER_ACTIVATE_IND:
            NAS_SM_RcvTafBearerActivateInd((SMREG_BEARER_ACTIVATE_IND_STRU*)pMsg);
            break;

        case ID_SMREG_BEARER_MODIFY_IND:
            NAS_SM_RcvTafBearerModifyInd((SMREG_BEARER_MODIFY_IND_STRU*)pMsg);
            break;

        case ID_SMREG_BEARER_DEACTIVATE_IND:
            NAS_SM_RcvTafBearerDeactivateInd((SMREG_BEARER_DEACTIVATE_IND_STRU*)pMsg);
            break;
#endif
        case ID_SMREG_PDP_ABORT_REQ:
            NAS_SM_RcvTafPdpAbortReq((SMREG_PDP_ABORT_REQ_STRU*)pMsg);
            break;

        case ID_SMREG_PDP_LOCAL_DEACTIVATE_REQ:
            NAS_SM_RcvTafPdpLocalDeactivateReq((SMREG_PDP_LOCAL_DEACTIVATE_REQ_STRU*)pMsg);
            break;

        default:
            NAS_NORMAL_LOG(WUEPS_PID_SM, "SM_TafMsgDistr:WARNING:SM: Message type non-existent !");
            break;
    }

    return;
}


VOS_VOID SM_GmmMsgDistr(
    VOS_VOID                            *pRcvMsg
)
{
    MSG_HEADER_STRU                     *pstGmmMsg;

    pstGmmMsg = (MSG_HEADER_STRU*)pRcvMsg;

    switch( pstGmmMsg->ulMsgName )
    {
        case GMMSM_ESTABLISH_CNF:
            NAS_NORMAL_LOG(WUEPS_PID_SM, "\n GMM->SM: GMMSM_ESTABLISH_CNF\r");
            SM_RcvGmmSmEstabishCnf ((GMMSM_ESTABLISH_CNF_STRU*)pRcvMsg);
            break;

        case GMMSM_DATA_IND:
            NAS_SM_RcvGmmSmDataInd((GMMSM_DATA_IND_STRU*)pRcvMsg);
            break;

        case GMMSM_STATUS_IND:
            SM_RcvGmmSmStatusInd ((GMMSM_STATUS_IND_STRU*)pRcvMsg);
            break;

        case GMMSM_SERVICE_REJ:
            SM_RcvGmmSmServiceRej((GMMSM_SERVICE_REJ_STRU*)pRcvMsg);

            break;

        case GMMSM_SYS_INFO_IND:
            SM_RcvGmmSysInfoInd((GMMSM_SYS_INFO_IND_STRU *)pRcvMsg);
            break;

        case GMMSM_PDP_STATUS_IND:
            SM_RcvGmmSmPdpStatusInd((GMMSM_PDP_STATUS_IND_STRU *)pRcvMsg);
            break;

        case GMMSM_REL_IND:
            SM_RcvGmmRelInd((GMMSM_REL_IND_STRU *)pRcvMsg);
            break;

        case GMMSM_SIG_CONN_IND:
            NAS_SM_RcvGmmSigConnInd((GMMSM_SIG_CONN_IND_STRU *)pRcvMsg);
            break;

        default:
            NAS_NORMAL_LOG(WUEPS_PID_SM, "SM_GmmMsgDistr:WARNING:NW->SM Message name non-existent!");
            break;
    }

    /* ��ʼ��TIû����չ��־ */
    g_ucTiExt = SM_FALSE;

    return;
}
VOS_VOID SM_RcvStatusMsg(GMMSM_DATA_IND_STRU *pGmmDataInd)
{
    VOS_UINT8       ucTi;
    VOS_UINT8       ucSmCause;
    VOS_UINT8       ucCntxtIndex;
    VOS_UINT8       ucAddrIndex;


    if( 0x70 ==(pGmmDataInd->SmMsg.aucNasMsg[0] & 0x70) )
    {
        ucTi = (pGmmDataInd->SmMsg.aucNasMsg[1] & 0x7F)
            | (pGmmDataInd->SmMsg.aucNasMsg[0] & 0x80);                         /* ��ȡTiֵ                                 */
        ucSmCause = pGmmDataInd->SmMsg.aucNasMsg[3];
    }
    else
    {
        ucTi = ((pGmmDataInd->SmMsg.aucNasMsg[0] & 0x70)>>4)
                | (pGmmDataInd->SmMsg.aucNasMsg[0] & 0x80);                     /* ��ȡTiֵ                                 */
        ucSmCause = pGmmDataInd->SmMsg.aucNasMsg[2];

        if (SM_NW2UE_STATUS_CAUSE_TI_INVALID == ucSmCause)
        {   /*�����緢����״̬�����ԭ����TI�Ƿ�*/
            /*�����緢��TIǰ������緢��TI��Ҫ�ı�ʶ*/
            ucTi |= 0x80;
        }
    }

    ucCntxtIndex  = g_TiMapToNsapi[ucTi];                                       /* ����TI��ȡucCntxtIndex                   */
    if( 0xFF == ucCntxtIndex )
    {                                                                           /* ��ȥ����״̬                             */

        PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                "SM_RcvStatusMsg:WARNING:NW->SM: PdpContext non-existent!");
    }
    else
    {
        ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;
        switch( g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState )
        {                                                                       /* ��Ϣ����                                 */
        case SM_PDP_ACTIVE_PENDING:
            if ( (TAF_SM_REJ_CAUSE_INVALID_TI == ucSmCause)                     /* #81 invalid transaction identifier value*/
              || (TAF_SM_REJ_CAUSE_MSGTYPE_NOT_EXIT == ucSmCause) )
            {                                                                   /* #97 "message type non-existent or not im
                                                                                 * plemented".                              */
                SM_ComClearPdpCntxt(ucCntxtIndex);                              /* �ͷ�ʵ��                                 */

                SM_SndTafSmPdpDeActInd(
                      g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                      NAS_SM_MapSmNWCause(ucSmCause),
                      SM_FALSE);
                SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex);                            /* ֪ͨRABMȥ����                           */
                SM_ComClearPdpAddrApn(ucAddrIndex);                                     /* ���Addr Apnʵ��                         */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;       /* ״̬�л���SM_PDP_INACTIVE                */

                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_RcvStatusMsg:NORMAL:SM state: SM_PDP_ACTIVE_PENDING ==> SM_PDP_INACTIVE");
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xff;     /* ά��g_CrMapToNsapi                       */
                g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xff;     /* ά��g_TiMapToNsapi                       */
                NAS_EventReport(WUEPS_PID_SM,
                                NAS_OM_EVENT_PDP_ACTIVE_FAIL,
                                (VOS_VOID *)&(ucSmCause),
                                NAS_OM_EVENT_PDP_ACTIVE_FAIL_LEN);

                /* ��GMM����GMMSM_PDP_DEACTIVATED_IND��Ϣ�����浱ǰPDP״̬ */
                NAS_SM_SndGmmPdpDeactivatedInd();
            }
            break;
        case SM_PDP_INACTIVE_PENDING:
            if ( (TAF_SM_REJ_CAUSE_INVALID_TI == ucSmCause)                     /* #81 "invalid transaction identifier value" or #97 "Message type non-existent or not implemented"*/
              || (TAF_SM_REJ_CAUSE_MSGTYPE_NOT_EXIT == ucSmCause) )
            {
                SM_TimerStop(ucCntxtIndex);                                     /* ֹͣT3390                                */
                SM_Free( g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg );  /* �ͷű��ݵ���Ϣ                           */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
                SM_SndTafSmPdpDeActInd(
                  g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                  NAS_SM_MapSmNWCause(ucSmCause),
                  SM_FALSE);
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                    = SM_PDP_INACTIVE;                                          /* ״̬�л���SM_PDP_INACTIVE                */

                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                    "SM_RcvStatusMsg:NORMAL:SM state: SM_PDP_INACTIVE_PENDING ==> SM_PDP_INACTIVE");

                NAS_SM_SndGmmPdpStatusInd();
                NAS_SM_SndGmmPdpDeactivatedInd();                               /* ��GMM����GMMSM_PDP_DEACTIVATED_IND��Ϣ�����浱ǰPDP״̬ */
                g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xff;
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xff;
            }
            break;
        case SM_PDP_MODIFY_PENDING:
            if( TAF_SM_REJ_CAUSE_INVALID_TI == ucSmCause)
            {                                                                   /* #81 "invalid transaction identifier value" */
                SM_SndRabmSmDeactivateInd (1, &ucCntxtIndex);                   /* ֪ͨRABMȥ����Nsapi                      */
                SM_SndTafSmPdpDeActInd(
                    g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                    NAS_SM_MapSmNWCause(ucSmCause),
                    SM_FALSE);
                SM_ComClearPdpCntxt(ucCntxtIndex);
                SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
                    = SM_PDP_INACTIVE;                                          /* ״̬�л���SM_PDP_INACTIVE                */

                PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                        "SM_RcvStatusMsg:NORMAL:SM state: SM_PDP_MODIFY_PENDING ==> SM_PDP_INACTIVE");

                NAS_SM_SndGmmPdpStatusInd();
                NAS_SM_SndGmmPdpDeactivatedInd();                               /* ��GMM����GMMSM_PDP_DEACTIVATED_IND��Ϣ�����浱ǰPDP״̬ */
                g_TiMapToNsapi[ucTi] = 0xFF;
                g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xFF;
            }
            else
            {                                                                   /* #97,#96                                  */
                SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);    /* �ͷű��ݵ���Ϣ                           */
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;
                SM_TimerStop(ucCntxtIndex);                                     /* ֹͣT3381                                */
                SM_SndTafSmPdpModifyRej(
                    NAS_SM_MapSmNWCause(ucSmCause),
                    g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE; /* ״̬�л���SM_PDP_ACTIVE                  */

                PS_NAS_LOG( WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                        "SM_RcvStatusMsg:NORMAL:SM state: SM_PDP_MODIFY_PENDING ==> SM_PDP_ACTIVE");
            }
            break;
        case SM_PDP_ACTIVE:
        case SM_PDP_NW_MODIFY:
            break;
        default:
            break;
        }
    }

    NAS_SM_EndSession();

    return;
}

/*******************************************************************************
  Module:   SM_RabmMsgDistr
  Function: RABM ��Ϣ�ַ�����
  Input:    VOS_VOID    *pRcvMsg           �յ�����Ϣ
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   ֣ ΰ   2003.12.11   �¹�����
*******************************************************************************/
VOS_VOID SM_RabmMsgDistr(
                    VOS_VOID            *pRcvMsg                                    /* ���յ�����Ϣ                             */
                    )
{
    MSG_HEADER_STRU     *pNasMsg;                                               /* ����NAS��Ϣָ��                          */

    pNasMsg = (MSG_HEADER_STRU *)pRcvMsg;
    switch(pNasMsg->ulMsgName)
    {                                                                           /* ��Ϣ����                                 */
    case RABMSM_DEACTIVATE_REQ:

        PS_NAS_LOG1(        WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                        "\n RABMSM_DEACTIVATE_REQ: ulNsapi = %ld\r",
            (VOS_INT32)(( (RABMSM_DEACTIVATE_REQ_STRU *)pRcvMsg) -> ulNsapi));

        SM_RcvRabmDeActReq ((RABMSM_DEACTIVATE_REQ_STRU *)pNasMsg);
        break;
    case RABMSM_ACTIVATE_RSP:
        break;
    default:
        break;
    }
    return;
}

/*******************************************************************************
  Module:   SM_RcvTimerMsgDistr
  Function: Timer��Ϣ�ķַ�����
  Input:    VOS_UINT8   ucTimerId
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   ֣ ΰ   2003.12.09   �¹�����
*******************************************************************************/
VOS_VOID SM_RcvTimerMsgDistr(
                        VOS_UINT32            ulTimerId                              /* Timer Id                                 */
                        )
{
    if( SM_REGISTER_TIMER_ID == ulTimerId )
    {
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_RcvTimerMsgDistr:INFO:SM TimerExpire: RegisterProtectTimer");

        SM_RegisterProtectTimerExpire((VOS_UINT8)ulTimerId);
    }
    else
    {
        switch(g_SmEntity.aPdpCntxtList[ulTimerId].TimerInfo.ucTimerType)
        {
        case SM_TIMER_TYPE_T3380:
            if( SM_PDP_ACTIVE_PENDING ==
                g_SmEntity.aPdpCntxtList[ulTimerId].ucState )
            {
                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_RcvTimerMsgDistr:INFO:SM TimerExpire(EntityIndex): T3380", (VOS_INT32)ulTimerId);

                SM_T3380Expire((VOS_UINT8)ulTimerId);
            }
            break;
        case SM_TIMER_TYPE_T3381:
            if( SM_PDP_MODIFY_PENDING ==
                g_SmEntity.aPdpCntxtList[ulTimerId].ucState )
            {
                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_RcvTimerMsgDistr:INFO:SM TimerExpire(EntityIndex): T3381", (VOS_INT32)ulTimerId);

                SM_T3381Expire ((VOS_UINT8)ulTimerId);
            }
            break;
        case SM_TIMER_TYPE_T3390:
            if( SM_PDP_INACTIVE_PENDING ==
                g_SmEntity.aPdpCntxtList[ulTimerId].ucState)
            {
                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_RcvTimerMsgDistr:INFO: SM TimerExpire(EntityIndex): T3390", (VOS_INT32)ulTimerId);

                SM_T3390Expire ((VOS_UINT8)ulTimerId);
            }
            break;
        case SM_TIMER_TYPE_T0003:
            SM_TimerStop((VOS_UINT8)ulTimerId);                                     /* ֹͣTimer                                */
            if( SM_PDP_NW_MODIFY
                == g_SmEntity.aPdpCntxtList[ulTimerId].ucState )
            {
                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_RcvTimerMsgDistr:INFO: SM TimerExpire(EntityIndex): T0003", (VOS_INT32)ulTimerId);

                SM_NwModifyProtectTimerExpire((VOS_UINT8)ulTimerId);
            }
            break;
        default:
            break;
        }
    }
    return;
}


VOS_VOID SM_T3380Expire(VOS_UINT8 ucCntxtIndex)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCntxt = VOS_NULL_PTR;
    GMMSM_DATA_REQ_STRU                *pstHoldMsg  = VOS_NULL_PTR;
    VOS_UINT8                           ucAddrIndex;
    VOS_UINT8                           ucCause;

    NAS_TIMER_EventReport(SM_TIMER_TYPE_T3380, WUEPS_PID_SM, NAS_OM_EVENT_TIMER_OPERATION_EXPIRED);

    pstPdpCntxt = NAS_SM_GetPdpCtxInfoAddr(ucCntxtIndex);
    pstHoldMsg  = (GMMSM_DATA_REQ_STRU *)pstPdpCntxt->pHoldSndMsg;

    ucAddrIndex = g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex;

    g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes++;           /* ��ʱ�Ĵ�����1                            */

    if( SM_MAX_EXPIRE_TIMES
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes)
    {                                                                           /* �ﵽ���Ĵ���(SM_MAX_EXPIRE_TIMES)      */
        NAS_MNTN_RecordPdpActiveFail(NAS_MNTN_ACTIVE_FAIL_TYPE_ACTIVE_TIMEOUT,
                                     ucCntxtIndex,
                                     NAS_MNTN_SM_REJ_CAUSE_INVALID,
                                     g_SmEntity.ucRegisterFlg);

        if( SM_ACT_PDP_CONTEXT_REQ
            == *( (pstHoldMsg->SmMsg.aucNasMsg) + sizeof(VOS_UINT8)) )
        {                                                                       /* PDP context activation����               */
            SM_SndTafSmPdpActivateRej(
                g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
                SM_TAF_CAUSE_SM_MAX_TIME_OUT,
                VOS_NULL_PTR );
        }
        else if( SM_ACT_SEC_PDP_CONTEXT_REQ
            == *( (pstHoldMsg->SmMsg.aucNasMsg) + sizeof(VOS_UINT8)) )
        {                                                                       /* Secondary PDP context activation����     */
            SM_SndTafSmPdpActSecRej(
               g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
               SM_TAF_CAUSE_SM_MAX_TIME_OUT);
        }
        else
        {
        }

        /* T3380 5�γ�ʱ��ֹͣ��ʱ��ʱ�����Ͷ�ʱ��ֹͣ�¼� */
        g_ucSmTimerFiveExpireFlag = VOS_TRUE;
        SM_ComClearPdpCntxt(ucCntxtIndex);                                      /* �ͷ�ʵ��                                 */
        g_ucSmTimerFiveExpireFlag = VOS_FALSE;

        SM_SndRabmSmDeactivateInd(1, &ucCntxtIndex);                            /* ֪ͨRABMȥ����                           */
        SM_ComDelNsapiFromAddr(ucAddrIndex,ucCntxtIndex);
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;       /* ״̬�л���SM_PDP_INACTIVE                */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_T3380Expire:NORMAL:SM state: SM_PDP_ACTIVE_PENDING ==> SM_PDP_INACTIV");
        g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr]=0xff;       /* ά��g_CrMapToNsapi                       */
        g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi]=0xff;       /* ά��g_TiMapToNsapi                       */

        /* 5�μ��ʱ��֪ͨGMM��ֹ���洦������ */
        NAS_SM_SndGmmPdpStatusInd();
        NAS_SM_SndGmmPdpDeactivatedInd();                                       /* ��GMM����GMMSM_PDP_DEACTIVATED_IND��Ϣ�����浱ǰPDP״̬ */

        NAS_SM_EndSession();

        ucCause = NAS_OM_SM_REJ_CAUSE_TIMER_TIMEOUT;
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_ACTIVE_FAIL,
                        (VOS_VOID *)&ucCause,
                        NAS_OM_EVENT_PDP_ACTIVE_FAIL_LEN);
    }
    else
    {
        NAS_TIMER_EventReport(SM_TIMER_TYPE_T3380, WUEPS_PID_SM, NAS_OM_EVENT_TIMER_OPERATION_START);

        NAS_SM_BeginSession();

        /* ���ͻ������Ϣ */
        NAS_SM_SndPdpCntxtHoldMsg(pstPdpCntxt);

        /* ��ά�ɲ���Ϣ */
        SM_ReportM2NOtaMsg(&(pstHoldMsg->SmMsg));
    }

    return;
}


VOS_VOID SM_T3381Expire(VOS_UINT8 ucCntxtIndex)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCntxt = VOS_NULL_PTR;
    GMMSM_DATA_REQ_STRU                *pstHoldMsg  = VOS_NULL_PTR;
    VOS_UINT8                           ucCause;

    NAS_TIMER_EventReport(SM_TIMER_TYPE_T3381, WUEPS_PID_SM, NAS_OM_EVENT_TIMER_OPERATION_EXPIRED);

    pstPdpCntxt = NAS_SM_GetPdpCtxInfoAddr(ucCntxtIndex);
    pstHoldMsg  = (GMMSM_DATA_REQ_STRU *)pstPdpCntxt->pHoldSndMsg;

    g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes++;           /* ��ʱ�Ĵ�����1                            */

    if( SM_MAX_EXPIRE_TIMES
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes)
    {                                                                           /* �ﵽ���Ĵ���(SM_MAX_EXPIRE_TIMES)      */
        SM_Free(g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg);            /* �ͷű��ݵ���Ϣ                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;

        /* T3381 5�γ�ʱ��ֹͣ��ʱ��ʱ�����Ͷ�ʱ��ֹͣ�¼� */
        g_ucSmTimerFiveExpireFlag = VOS_TRUE;
        SM_TimerStop(ucCntxtIndex);                                             /* ֹͣT3381                                */
        g_ucSmTimerFiveExpireFlag = VOS_FALSE;
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_ACTIVE;         /* ״̬�л���SM_PDP_ACTIVE                  */

        SM_SndTafSmPdpModifyRej(
            SM_TAF_CAUSE_SM_MAX_TIME_OUT,
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr);

        NAS_SM_EndSession();

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_T3381Expire:NORMAL:SM state: SM_PDP_MODIFY_PENDING ==> SM_PDP_ACTIVE");
        ucCause = NAS_OM_SM_REJ_CAUSE_TIMER_TIMEOUT;
        NAS_EventReport(WUEPS_PID_SM,
                        NAS_OM_EVENT_PDP_CONTEXT_MODIFY_FAIL,
                        (VOS_VOID *)&ucCause,
                        NAS_OM_EVENT_PDP_CONTEXT_MODIFY_FAIL_LEN);
    }
    else
    {
        NAS_TIMER_EventReport(SM_TIMER_TYPE_T3381, WUEPS_PID_SM, NAS_OM_EVENT_TIMER_OPERATION_START);

        NAS_SM_BeginSession();

        /* ���ͻ������Ϣ */
        NAS_SM_SndPdpCntxtHoldMsg(pstPdpCntxt);

        /* ��ά�ɲ���Ϣ */
        SM_ReportM2NOtaMsg(&(pstHoldMsg->SmMsg));
    }

    return;
}


VOS_VOID SM_T3390Expire(VOS_UINT8 ucCntxtIndex)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCntxt = VOS_NULL_PTR;
    GMMSM_DATA_REQ_STRU                *pstHoldMsg  = VOS_NULL_PTR;

    NAS_TIMER_EventReport(SM_TIMER_TYPE_T3390, WUEPS_PID_SM, NAS_OM_EVENT_TIMER_OPERATION_EXPIRED);

    pstPdpCntxt = NAS_SM_GetPdpCtxInfoAddr(ucCntxtIndex);
    pstHoldMsg  = (GMMSM_DATA_REQ_STRU *)pstPdpCntxt->pHoldSndMsg;

    g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes++;           /* ��ʱ�Ĵ�����1                            */

    if( SM_MAX_EXPIRE_TIMES
        == g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes)
    {                                                                           /* �ﵽ���Ĵ���(SM_MAX_EXPIRE_TIMES)      */
        /* T3390 5�γ�ʱ��ֹͣ��ʱ��ʱ�����Ͷ�ʱ��ֹͣ�¼� */
        g_ucSmTimerFiveExpireFlag = VOS_TRUE;
        SM_TimerStop(ucCntxtIndex);                                             /* ֹͣT3390                                */
        g_ucSmTimerFiveExpireFlag = VOS_FALSE;

        SM_Free( g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg );          /* �ͷű��ݵ���Ϣ                           */
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].pHoldSndMsg = SM_NULL;

        SM_SndTafSmPdpDeActInd(
            g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
            SM_TAF_CAUSE_SM_MAX_TIME_OUT,
            SM_FALSE);                                                          /* ֪ͨTAFȥ����                            */

        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState = SM_PDP_INACTIVE;       /* ״̬�л���SM_PDP_INACTIVE                */

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SM_T3390Expire:NORMAL:SM state: SM_PDP_INACTIVE_PENDING ==> SM_PDP_INACTIVE ");
        g_TiMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucTi] = 0xff;
        g_CrMapToNsapi[g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr] = 0xff;

        NAS_SM_SndGmmPdpStatusInd();

        /* ��GMM����GMMSM_PDP_DEACTIVATED_IND��Ϣ�����浱ǰPDP״̬ */
        NAS_SM_SndGmmPdpDeactivatedInd();

        NAS_SM_EndSession();

    }
    else
    {
        NAS_TIMER_EventReport(SM_TIMER_TYPE_T3390, WUEPS_PID_SM, NAS_OM_EVENT_TIMER_OPERATION_START);

        NAS_SM_BeginSession();

        /* ���ͻ������Ϣ */
        NAS_SM_SndPdpCntxtHoldMsg(pstPdpCntxt);

        /* ��ά�ɲ���Ϣ */
        SM_ReportM2NOtaMsg(&(pstHoldMsg->SmMsg));
    }

    return;
}


VOS_VOID SM_RegisterProtectTimerExpire(VOS_UINT8 ucCntxtIndex)
{
    VOS_UINT8                           i;
    MSG_HEADER_STRU                    *pHoldMsg;

    SM_TimerStop(SM_REGISTER_TIMER_ID);                                         /* ֹͣע�ᱣ��Timer                        */

    if (SM_PS_REGISTERING != g_SmEntity.ucRegisterFlg)
    {
        return;
    }

    g_SmEntity.ucRegisterFlg = SM_PS_NOTREGISTER;                               /* �趨ע���־Ϊû��ע��                   */

    for( i = 0; i < SM_MAX_NSAPI_NUM; i++ )
    {
        if( SM_NULL != g_SmEntity.aHoldMsg[i].pHoldRcvMsg )
        {                                                                       /* ���ڻ�����Ϣ                             */
            pHoldMsg = (MSG_HEADER_STRU *)g_SmEntity.aHoldMsg[i].pHoldRcvMsg;
            switch( pHoldMsg->ulMsgName )
            {                                                                   /* ��Ϣ����                                 */
            case ID_SMREG_PDP_ACTIVATE_REQ:
                SM_SndTafSmPdpActivateRej(
                    ((SMREG_PDP_ACTIVATE_REQ_STRU *)pHoldMsg)->ucConnectId,
                    SM_TAF_CAUSE_SM_CONN_ESTABLISH_MAX_TIME_OUT,
                    VOS_NULL_PTR);
                break;
            case ID_SMREG_PDP_DEACTIVATE_REQ:
                SM_SndTafSmPdpDeActInd (
                    ((SMREG_PDP_DEACTIVATE_REQ_STRU *)pHoldMsg)->ucConnectId,
                    SM_TAF_CAUSE_SM_CONN_ESTABLISH_MAX_TIME_OUT,
                    SM_FALSE);

                NAS_SM_SndGmmPdpStatusInd();
                break;
            default:
                break;
            }

            SM_ComClearPdpCntxt(i);                                             /* �������PDPʵ��Ĵ���                    */
            SM_Free(g_SmEntity.aHoldMsg[i].pHoldRcvMsg);                        /* �ͷű�����Ϣ                             */
            g_SmEntity.aHoldMsg[i].pHoldRcvMsg = SM_NULL;                       /* ���������Ϣ                             */
        }
        else
        {
            break;
        }
    }

    NAS_SM_SndGmmPdpDeactivatedInd();

    NAS_SM_EndSession();


    return;
}
VOS_VOID SM_NwModifyProtectTimerExpire(VOS_UINT8 ucCntxtIndex)
{
    NAS_SM_NORM_LOG("SM_NwModifyProtectTimerExpire: SM_PDP_NW_MODIFY ==> SM_PDP_INACTIVE_PENDING");

    SM_ComClearPdpCntxt(ucCntxtIndex);                                          /* ���ʵ��                                 */
    SM_ComDelNsapiFromAddr(
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucAddrIndex,
        ucCntxtIndex);                                                          /* ά��Addr��Apnʵ��                        */
    SM_SndRabmSmDeactivateInd(1,&ucCntxtIndex);                                 /* ֪ͨRABM                                 */

    SM_SndTafSmPdpDeActInd(
        g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucCr,
        SM_TAF_CAUSE_SM_MAX_TIME_OUT,
        SM_FALSE);

    NAS_SM_BeginSession();

    SM_SndPdpDeActReqMsg(SM_NULL, ucCntxtIndex);                                /* ����ȥ������Ϣ                           */
    g_SmEntity.aPdpCntxtList[ucCntxtIndex].TimerInfo.ucExpireTimes = 0;         /* Timer ��ʱ������0                        */
    SM_TimerStart(ucCntxtIndex,SM_T3390_LENGTH,SM_TIMER_TYPE_T3390);            /* ����T3390                                */
    g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState
        = SM_PDP_INACTIVE_PENDING;                                              /* ״̬�л���SM_PDP_INACTIVE_PENDING        */

    NAS_SM_SndGmmPdpStatusInd();
    return;
}
VOS_VOID SM_TimerStart(
                   VOS_UINT8        ucEntId,                                        /* Timer ID Ϊʵ�������                    */
                   VOS_UINT32        ulTimerLen,                                     /* Timer��ʱ��                              */
                   VOS_UINT8        ucTimerType
                   )
{
    if( SM_REGISTER_TIMER_ID == ucEntId )
    {
        if (VOS_OK !=
            NAS_StartRelTimer(&g_SmEntity.ulRegTimerID,WUEPS_PID_SM,ulTimerLen,(VOS_UINT32)ucTimerType,(VOS_UINT32)ucEntId,VOS_RELTIMER_LOOP))
        {
              PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,"start reltimer error");
        }

        g_SmEntity.ucRegTimerSta = SM_TIMER_STA_ON;


        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStart:INFO:SM TimerStart: RegisterProtectTimer");

    }
    else
    {
        if (VOS_OK != NAS_StartRelTimer(&g_SmEntity.
            aPdpCntxtList[ucEntId].TimerInfo.TimerId,WUEPS_PID_SM,ulTimerLen,(VOS_UINT32)ucTimerType,(VOS_UINT32)ucEntId,VOS_RELTIMER_LOOP))
        {
              PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,"start reltimer error");
        }

        g_SmEntity.aPdpCntxtList[ucEntId].TimerInfo.ucTimerType
            = ucTimerType;
        g_SmEntity.aPdpCntxtList[ucEntId].TimerInfo.ucTimerStaFlg
            = SM_TIMER_STA_ON;

        g_SmEntity.aPdpCntxtList[ucEntId].TimerInfo.ucExpireTimes = 0;

        switch( ucTimerType )
        {
        case SM_TIMER_TYPE_T3380    :

            PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStart:INFO:SM TimerStart(EntityIndex): T3380", ucEntId);
            break;
        case SM_TIMER_TYPE_T3381    :

            PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStart:INFO:SM TimerStart(EntityIndex): T3381", ucEntId);

            break;
        case SM_TIMER_TYPE_T3390    :

            PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStart:INFO:SM TimerStart(EntityIndex): T3390", ucEntId);

            break;
        case SM_TIMER_TYPE_T0001    :

            PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStart:INFO:SM TimerStart(EntityIndex): T0001", ucEntId);

            break;
        case SM_TIMER_TYPE_T0002    :

            PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStart:INFO:SM TimerStart(EntityIndex): T0002", ucEntId);

            break;
        case SM_TIMER_TYPE_T0003    :

            PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStart:INFO:SM TimerStart(EntityIndex): T0003", ucEntId);

            break;
        default :
            break;
        }

    }
    return;
}

/*******************************************************************************
  Module:   SM_TimerStop
  Function: ֹͣTimer
  Input:    VOS_UINT8   ucTimerId
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   ֣ ΰ   2003.12.09   �¹�����
*******************************************************************************/
VOS_VOID SM_TimerStop(
                   VOS_UINT8        ucEntId                                         /* Timer ID Ϊʵ�������                    */
                  )
{
    if( SM_REGISTER_TIMER_ID == ucEntId )
    {
        if( SM_TIMER_STA_ON == g_SmEntity.ucRegTimerSta )
        {
            if (VOS_OK != NAS_StopRelTimer(WUEPS_PID_SM, ucEntId, &g_SmEntity.ulRegTimerID))
            {
                PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO: SM TimerStop fail");
            }

            g_SmEntity.ucRegTimerSta = SM_TIMER_STA_OFF;


            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO: SM TimerStop: RegisterProtectTimer");

        }
    }
    else
    {
        if( SM_TIMER_STA_ON
            == g_SmEntity.aPdpCntxtList[ucEntId].TimerInfo.ucTimerStaFlg )
        {
            if (VOS_OK != NAS_StopRelTimer(WUEPS_PID_SM, g_SmEntity.aPdpCntxtList[ucEntId].TimerInfo.ucTimerType, &g_SmEntity
                .aPdpCntxtList[ucEntId].TimerInfo.TimerId))
             {
                 PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO: SM TimerStop fail");
             }
            g_SmEntity.aPdpCntxtList[ucEntId].TimerInfo.ucTimerStaFlg
                = SM_TIMER_STA_OFF;

            switch( g_SmEntity.aPdpCntxtList[ucEntId].TimerInfo.ucTimerType )
            {
            case SM_TIMER_TYPE_T3380    :

                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO:SM TimerStop(EntityIndex): T3380", ucEntId);
                break;
            case SM_TIMER_TYPE_T3381    :

                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO:SM TimerStop(EntityIndex): T3381", ucEntId);

                break;
            case SM_TIMER_TYPE_T3390    :

                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO:SM TimerStop(EntityInde): T3390", ucEntId);
                break;
            case SM_TIMER_TYPE_T0001    :

                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO:SM TimerStop(EntityInde): T0001", ucEntId);
                break;
            case SM_TIMER_TYPE_T0002    :

                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO:SM TimerStop(EntityIndex): T0002", ucEntId);
                break;
            case SM_TIMER_TYPE_T0003    :

                PS_NAS_LOG1(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_INFO, "SM_TimerStop:INFO:SM TimerStop(EntityIndex): T0003", ucEntId);
                break;
            default :
                break;
            }
        }
    }
    return;
}


/*******************************************************************************
  Module:   SM_MemCmp
  Function: �Ƚ��ڴ�
  Input:    VOS_UINT8   *p1
            VOS_UINT8   *p2
            VOS_UINT16  length
  Output:   VOS_VOID
  NOTE:
  Return:   SM_FALSE:  �ڴ����
            SM_TRUE:   �ڴ治���
  History:
      1.   ��־��      2003.12.26   �¹�����
*******************************************************************************/
VOS_UINT8 SM_MemCmp(VOS_UINT8 *p1, VOS_UINT8 *p2, VOS_UINT32 ulLength)
{
    for(; ulLength > 0; ulLength--)
    {
        if(*p1 != *p2)
        {
            return SM_TRUE;
        }
        p1++;
        p2++;
    }
    return SM_FALSE;
}

/******************************************************************************
 * �������� �� WuepsSmPidInit
 * �������� �� WUEPS SM PID�ĳ�ʼ������
 * ����˵�� �� ��
 * ��    ע ��
 * �� �� ֵ �� VOS_UINT32 ��ʼ�������
 *             0  : �ɹ�
 *             ��0: ʧ��
 *
 * �����ʷ ��
 *           No.  ����      ���                                    ��   ��
 *           1    ��־��    �½�                                   2005.02.24
 *****************************************************************************/
VOS_UINT32 WuepsSmPidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
    case VOS_IP_LOAD_CONFIG:
        SM_Init();                                                          /* ��ʼ��                                   */
        break;
    case VOS_IP_FARMALLOC:
    case VOS_IP_INITIAL:
    case VOS_IP_ENROLLMENT:
    case VOS_IP_LOAD_DATA:
    case VOS_IP_FETCH_DATA:
    case VOS_IP_STARTUP:
    case VOS_IP_RIVAL:
    case VOS_IP_KICKOFF:
    case VOS_IP_STANDBY:
    case VOS_IP_BROADCAST_STATE:
    case VOS_IP_RESTART:
    case VOS_IP_BUTT:
        break;
    default:
        break;
    }

    return VOS_OK;
}
VOS_VOID  Sm_PowerOff(VOS_VOID)
{
    NAS_SM_PDP_CONTEXT_INFO_STRU       *pstPdpCtxInfo;
    NAS_SM_PDP_ADDR_INFO_STRU          *pstPdpAddrInfo;
    VOS_UINT8                           ucCntxtIndex;

    /*�رչ��ö�ʱ��:*/
    SM_TimerStop(SM_REGISTER_TIMER_ID);

    for (ucCntxtIndex = 0; ucCntxtIndex < SM_MAX_NSAPI_NUM; ucCntxtIndex++)
    {
        pstPdpCtxInfo  = NAS_SM_GetPdpCtxInfoAddr(ucCntxtIndex);
        pstPdpAddrInfo = NAS_SM_GetPdpAddrInfoAddr(ucCntxtIndex);

        /* �ͷŻ������Ϣ */
        if (VOS_NULL_PTR != pstPdpCtxInfo->pHoldSndMsg)
        {
            SM_Free(pstPdpCtxInfo->pHoldSndMsg);
            pstPdpCtxInfo->pHoldSndMsg = VOS_NULL_PTR;
        }

        /* �ͷ�QOS��Ϣ */
        pstPdpCtxInfo->QoS.ulQosLength = 0;
        PS_MEM_SET(pstPdpCtxInfo->QoS.aucQosValue,
                   0x00,
                   sizeof(pstPdpCtxInfo->QoS.aucQosValue));

        /* �ͷ�APN��Ϣ */
        pstPdpAddrInfo->PdpApn.ulApnLength = 0;
        PS_MEM_SET(pstPdpAddrInfo->PdpApn.aucApnValue,
                   0x00,
                   sizeof(pstPdpAddrInfo->PdpApn.aucApnValue));

        /* �ͷ�PS��δע�᳡���·���PDP������������Ļ��� */
        if (VOS_NULL_PTR != g_SmEntity.aHoldMsg[ucCntxtIndex].pHoldRcvMsg)
        {
            SM_Free(g_SmEntity.aHoldMsg[ucCntxtIndex].pHoldRcvMsg);
            g_SmEntity.aHoldMsg[ucCntxtIndex].pHoldRcvMsg = VOS_NULL_PTR;
        }
    }

    /*���ó�ʼ������:*/
    SM_Init();

    NAS_SM_EndSession();

    return;
}
VOS_UINT16 NAS_SM_CalcMaxSduSize(
    VOS_UINT8                           *pucQos,
    VOS_UINT8                           ucCurrOctet
)
{
    VOS_UINT16                          usMaxSduSize;
    VOS_UINT8                           ucQosOctet;

    ucQosOctet = *(pucQos + ucCurrOctet);



    if ((ucQosOctet >= 1) && (ucQosOctet <= 150))
    {
        usMaxSduSize = ucQosOctet * 10;
    }
    else if (151 == ucQosOctet)
    {
        usMaxSduSize = 1502;
    }
    else if (152 == ucQosOctet)
    {
        usMaxSduSize = 1510;
    }
    else if (153 == ucQosOctet)
    {
        usMaxSduSize = 1520;
    }
    else
    {
        usMaxSduSize = ucQosOctet;
    }

    return usMaxSduSize;
}


VOS_UINT32 NAS_SM_CalcQosBitRate(
    VOS_UINT8                           *pucQos,
    VOS_UINT8                           ucCurrOctetIndex,
    VOS_UINT8                           ucExtOctetIndex,
    VOS_UINT8                           ucBitRateType,
    VOS_UINT32                          ulQosLen
)
{
    VOS_UINT32                          ulQosBitRate;
    VOS_UINT8                           ucQosOctet;
    VOS_UINT8                           *pucBitRate;

    ucQosOctet = *(pucQos + ucCurrOctetIndex);

    /*--------------------------------------------------------------------------
      Maximum(Guaranteed) bit rate for uplink, octet 8(12)
      Maximum(Guaranteed) bit rate for downlink, octet 9(13)
      8 7 6 5 4 3 2 1
      In MS to network direction:
      0 0 0 0 0 0 0 0       Subscribed maximum bit rate
      In network to MS direction:
      0 0 0 0 0 0 0 0       Reserved
      In MS to network direction and in network to MS direction:
      0 0 0 0 0 0 0 1(1)    The maximum(guaranteed) bit rate is
      0 0 1 1 1 1 1 1(63)   binary coded in 8 bits, using a granularity of 1 kbps
                            giving a range of values from 1 kbps to 63 kbps in 1 kbps increments.

      0 1 0 0 0 0 0 0(64)   The maximumv(guaranteed) bit rate is
      0 1 1 1 1 1 1 1(127)  64 kbps + ((the binary coded value in 8 bits �C01000000) * 8 kbps)
                            giving a range of values from 64 kbps to 568 kbps in 8 kbps increments.

      1 0 0 0 0 0 0 0(128)  The maximum(guaranteed) bit rate is
      1 1 1 1 1 1 1 0(254)  576 kbps + ((the binary coded value in 8 bits �C10000000) * 64 kbps)
                            giving a range of values from 576 kbps to 8640 kbps in 64 kbps increments.

      1 1 1 1 1 1 1 1(255)  0kbps

      If the sending entity wants to indicate a Maximum(Guaranteed) bit rate higher
      than 8640 kbps, it shall set octet to '11111110', i.e. 8640 kbps, and
      shall encode the value for the Maximum(Guaranteed) bit rate in extended octet.
    --------------------------------------------------------------------------*/
    if (ucQosOctet <= 63)
    {
        ulQosBitRate = ucQosOctet;
    }
    else if ((ucQosOctet >= 64) && (ucQosOctet <= 127))
    {
        ulQosBitRate = 64 + ((ucQosOctet - 64) * 8);
    }
    else if ((ucQosOctet >= 128) && (ucQosOctet < 254))
    {
        ulQosBitRate = 576 + ((ucQosOctet - 128) * 64);
    }
    else if (254 == ucQosOctet)
    {
        #if(PS_UE_REL_VER < PS_PTL_VER_R7)
        ulQosBitRate = 576 + ((ucQosOctet - 128) * 64);
        #else
        if (((NAS_SM_QOS_BIT_RATE_TYPE_DL == ucBitRateType) && (ulQosLen < 14))
         || ((NAS_SM_QOS_BIT_RATE_TYPE_UL == ucBitRateType) && (ulQosLen < 16)))
        {
            ulQosBitRate = 576 + ((ucQosOctet - 128) * 64);
        }
        else
        {
            /*pucBitRate ָ��Maximum(Guaranteed) bit rate (extended)*/
            pucBitRate = pucQos + ucExtOctetIndex;

            /*------------------------------------------------------------------
              Maximum(Guaranteed) bit rate for uplink (extended), octet 17(18)
              Maximum(Guaranteed) bit rate for downlink (extended), octet 15(16)
              8 7 6 5 4 3 2 1
              In MS to network direction and in network to MS direction:
              0 0 0 0 0 0 0 0   Use the value indicated by the Maximum(Guaranteed)
                                bit rate for downlink in octet 8(12).

              For all other values: Ignore the value indicated by the Maximum(Guaranteed)
              bit rate for uplink in octet 8(12)/downlink in octet 9(13) and use the following value:
              0 0 0 0 0 0 0 1(1)    The maximum(guaranteed) bit rate is
              0 1 0 0 1 0 1 0(74)   8600 kbps + ((the binary coded value in 8 bits) * 100 kbps),
                                    giving a range of values from 8700 kbps to 16000 kbps in 100 kbps increments.

              0 1 0 0 1 0 1 1(75)   The maximum(guaranteed) bit rate is
              1 0 1 1 1 0 1 0(186)  16 Mbps + ((the binary coded value in 8 bits - 01001010) * 1 Mbps),
                                    giving a range of values from 17 Mbps to 128 Mbps in 1 Mbps increments.

              1 0 1 1 1 0 1 1(187)  The maximum(guaranteed) bit rate is
              1 1 1 1 1 0 1 0(250)  128 Mbps + ((the binary coded value in 8 bits - 10111010) * 2 Mbps),
                                    giving a range of values from 130 Mbps to 256 Mbps in 2 Mbps increments.
            --------------------------------------------------------------------*/
            if (*pucBitRate <= 74)
            {
                ulQosBitRate = 8600 + (*pucBitRate * 100);
            }
            else if (*pucBitRate <= 186)
            {
                ulQosBitRate = 16000 + ((*pucBitRate - 74) * 1000);
            }
            else if (*pucBitRate <= 250)
            {
                ulQosBitRate = 128000 + ((*pucBitRate - 186) * 2000);
            }
            else
            {
                ulQosBitRate = 256000;
            }
        }
        #endif
    }
    else
    {
        ulQosBitRate = 0;
    }

    return ulQosBitRate;
}


VOS_UINT16 NAS_SM_CalcTransDelay(
    VOS_UINT8                           *pucQos,
    VOS_UINT8                           ucCurrOctet
)
{
    VOS_UINT16                          usTransDelay;
    VOS_UINT8                           ucQosOctet;

    ucQosOctet = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_TRANSFER_DELAY_MASK) >> 2;


    if ((ucQosOctet >= 1) && (ucQosOctet <= 15))
    {
        usTransDelay = ucQosOctet;
    }
    else if ((ucQosOctet >= 16) && (ucQosOctet <= 31))
    {
        usTransDelay = 200 + ((ucQosOctet - 16) * 50);
    }
    else if ((ucQosOctet >= 32) && (ucQosOctet <= 62))
    {
        usTransDelay = 1000 + ((ucQosOctet - 32) * 100);

    }
    else
    {
        usTransDelay = 63;
    }

    return usTransDelay;
}


VOS_VOID NAS_SM_FillQos(
    NAS_QOS_IND_STRUCT                  *pMsg,
    VOS_UINT8                           *pucQos,
    VOS_UINT32                          ulQosLen
)
{
    VOS_UINT8                           ucCurrOctet;

    ucCurrOctet = 0;

    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
    /* Octet 3 of Qos struct. Refer to sction 10.5.6 in TS 24.008 */
    pMsg->enDelayClass           = (*(pucQos) & NAS_SM_QOS_DELAY_CLASS_MASK) >> 3;
    pMsg->enReliabilityClass     = (*(pucQos) & NAS_SM_QOS_RELIABILITY_CLASS_MASK);

    ucCurrOctet++;

    /* Octet 4 */
    pMsg->enPeakThrough          = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_PEAK_THROUGHPUT_MASK) >> 4;
    pMsg->enPrecedenceClass      = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_PRECEDENCE_CLASS_MASK);

    ucCurrOctet++;

    /* Octet 5 */
    pMsg->enMeanThrough          = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_MEAN_THROUGHPUT_MASK);

    ucCurrOctet++;

    /* Octet 6 */
    pMsg->enTrafficClass         = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_TRAFFIC_CLASS_MASK) >> 5;
    pMsg->enDeliverOrder         = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_DELIVERY_ORDER_MASK) >> 3;
    pMsg->enDeliverOfErrSdu      = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_DELIVERY_ERRORNEOUS_SDU_MASK);

    ucCurrOctet++;

    /* Octet 7 */
    pMsg->usMaximSduSize         = NAS_SM_CalcMaxSduSize(pucQos, ucCurrOctet);

    ucCurrOctet++;

    /*--------------------------------------------------------------------------
      Octet 8
      Maximum bit rate for uplink ��չ�ֽ�λ��Qos���������еĵ�14���ֽڣ�
      ���� Maximum bit rate for uplink ʱ��Ҫ����չ�ֽڵ�ֵ���ǽ�ȥ��
    ---------------------------------------------------------------------------*/
    pMsg->ulMaxBitRateUl         = NAS_SM_CalcQosBitRate(pucQos,
                                                    ucCurrOctet,
                                                    14,
                                                    NAS_SM_QOS_BIT_RATE_TYPE_UL,
                                                    ulQosLen);

    ucCurrOctet++;

    /*--------------------------------------------------------------------------
      Octet 9
      Maximum bit rate for downlink ��չ�ֽ�λ��Qos���������еĵ�12���ֽڣ�
      ���� Maximum bit rate for downlink ʱ��Ҫ����չ�ֽڵ�ֵ���ǽ�ȥ��
    ---------------------------------------------------------------------------*/
    pMsg->ulMaxBitRateDl         = NAS_SM_CalcQosBitRate(pucQos,
                                                    ucCurrOctet,
                                                    12,
                                                    NAS_SM_QOS_BIT_RATE_TYPE_DL,
                                                    ulQosLen);

    ucCurrOctet++;

    /* Octet 10 */
    pMsg->enResidualBer          = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_RESIDUAL_BER_MASK) >> 4;
    pMsg->enSduErrRatio          = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_SDU_ERROR_RATIO_MASK);

    ucCurrOctet++;

    /* Octet 11 */
    pMsg->usTransDelay           = NAS_SM_CalcTransDelay(pucQos, ucCurrOctet);
    pMsg->enTraffHandlPrior      = (*(pucQos + ucCurrOctet) & NAS_SM_QOS_TRAFFIC_HANDLING_PRIORITY_MASK);
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */

    ucCurrOctet++;

    /*--------------------------------------------------------------------------
      Octet 12
      Guaranteed bit rate for uplink ��չ�ֽ�λ��Qos���������еĵ�15���ֽڣ�
      ���� Guaranteed bit rate for uplink ʱ��Ҫ����չ�ֽڵ�ֵ���ǽ�ȥ��
    ---------------------------------------------------------------------------*/
    pMsg->ulGuarantBitRateUl     = NAS_SM_CalcQosBitRate(pucQos,
                                                    ucCurrOctet,
                                                    15,
                                                    NAS_SM_QOS_BIT_RATE_TYPE_UL,
                                                    ulQosLen);

    ucCurrOctet++;

    /*--------------------------------------------------------------------------
      Octet 13
      Guaranteed bit rate for downlink ��չ�ֽ�λ��Qos���������еĵ�13���ֽڣ�
      ���� Guaranteed bit rate for uplink ʱ��Ҫ����չ�ֽڵ�ֵ���ǽ�ȥ��
    ---------------------------------------------------------------------------*/
    pMsg->ulGuarantBitRateDl     = NAS_SM_CalcQosBitRate(pucQos,
                                                    ucCurrOctet,
                                                    13,
                                                    NAS_SM_QOS_BIT_RATE_TYPE_UL,
                                                    ulQosLen);
}


VOS_UINT32 NAS_SM_FindCurrPdpId(
    VOS_UINT8                           *pucNSAPI
)
{
    VOS_UINT32                          ulIndex;

    *pucNSAPI = 0;

    for (ulIndex = 0; ulIndex < SM_MAX_NSAPI_NUM; ulIndex++)
    {
        if ((SM_PDP_ACTIVE == g_SmEntity.aPdpCntxtList[ulIndex].ucState)
         || (SM_PDP_MODIFY_PENDING == g_SmEntity.aPdpCntxtList[ulIndex].ucState)
         || (SM_PDP_NW_MODIFY == g_SmEntity.aPdpCntxtList[ulIndex].ucState))
        {
            /* ��ǰ�汾ֻ֧��һ��PDP�������ucNSAPI��ֵӦ����Ψһ�� */
            *pucNSAPI = (VOS_UINT8)ulIndex + SM_NSAPI_OFFSET;
            break;
        }
    }

    if ((0 != *pucNSAPI)
     && (0 != g_SmEntity.aPdpCntxtList[*pucNSAPI - SM_NSAPI_OFFSET].QoS.ulQosLength))
    {
        return VOS_TRUE;
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_SM_FindCurrPdpId:WARNING: length of QoS is 0!");
        return VOS_FALSE;
    }
}
VOS_VOID Sm_FillQosInfo(
    NAS_QOS_IND_STRUCT                 *pMsg
)
{
    VOS_UINT8                          *pucQosvalue;
    VOS_UINT32                          ulQosLength;
    VOS_UINT32                          ulStatus;

    if (VOS_NULL_PTR == pMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_SM, "Sm_FillQosInfo: Wrong Parameter,Null pointer!");
        return;
    }

    /* ��ȡ��ǰPDP��ID�����ж���Qos�Ƿ���Ч */
    ulStatus = NAS_SM_FindCurrPdpId(&(pMsg->ucNSAPI));

    if (VOS_TRUE == ulStatus)
    {
        pucQosvalue = g_SmEntity.aPdpCntxtList[pMsg->ucNSAPI - SM_NSAPI_OFFSET].QoS.aucQosValue;
        ulQosLength = g_SmEntity.aPdpCntxtList[pMsg->ucNSAPI - SM_NSAPI_OFFSET].QoS.ulQosLength;

        NAS_SM_FillQos(pMsg, pucQosvalue, ulQosLength);
    }

    return;
}
VOS_VOID NAS_SM_FillPDPContextInfo(
    NAS_OM_PDP_CONTEXT_IND_STRU        *pstPdpCntxt
)
{
    VOS_UINT8                           ucCntxtIndex;

    if (VOS_NULL_PTR == pstPdpCntxt)
    {
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
            "NAS_SM_FillPDPContextInfo:Wrong Parameter,Null pointer!");
        return;
    }

    /* Deleted by wx270776 for OM�ں�, 2015-7-14, begin */
    /* ɾ��PS_MEM_SET���ڵ���ǰ�Ѿ���ʼ������ */
    /* Deleted by wx270776 for OM�ں�, 2015-7-14, end */

    /*��ѯPDP��ǰ״̬�Ƿ��Ǵ��ڼ���״̬*/
    for (ucCntxtIndex = 0; ucCntxtIndex < SM_MAX_NSAPI_NUM; ucCntxtIndex++)
    {
        if ( (SM_PDP_ACTIVE         == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
          || (SM_PDP_MODIFY_PENDING == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
          || (SM_PDP_NW_MODIFY      == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState) )
        {
            Aps_GetPdpContextInfo(ucCntxtIndex + SM_NSAPI_OFFSET,
                                  &(pstPdpCntxt->astPdpContext[pstPdpCntxt->ulPdpCnt]));

            pstPdpCntxt->ulPdpCnt++;
        }
    }

    return;
}


VOS_UINT32 NAS_SM_CheckPdpActiveState()
{
    VOS_UINT32                          ucCntxtIndex;

    /*��ѯPDP��ǰ״̬�Ƿ��Ǵ��ڼ���״̬*/
    for (ucCntxtIndex = 0; ucCntxtIndex < SM_MAX_NSAPI_NUM; ucCntxtIndex++)
    {
        if ((SM_PDP_ACTIVE == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
         || (SM_PDP_MODIFY_PENDING == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState)
         || (SM_PDP_NW_MODIFY == g_SmEntity.aPdpCntxtList[ucCntxtIndex].ucState))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/* Added by wx270776 for OM�ں�, 2015-7-21, begin */
/*****************************************************************************
 �� �� ��  : NAS_SM_SndOmQosIndMsg
 ��������  : ����OM�Ĳ�ѯ��Ϣ͸����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ulRet: ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��7��21��
   ��    ��   : wx270776
   �޸�����   : OM�ں�
 2.��    ��   : 2015��9��17��
   ��    ��   : zwx247453
   �޸�����   : Dallas�Ĵ�����ԭ���ϱ���BBP������Ŀ
*****************************************************************************/
VOS_UINT32 NAS_SM_SndOmQosIndMsg(VOS_VOID)
{
    NAS_QOS_IND_STRUCT                  stNasQosInd;
    DIAG_TRANS_IND_STRU                 stDiagTransInd;
    VOS_UINT32                          ulRet;

    /* ��ʼ�� */
    PS_MEM_SET(&stNasQosInd, 0x00, sizeof(NAS_QOS_IND_STRUCT));

    /* �����Ϣ���� */
    Sm_FillQosInfo(&stNasQosInd);
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
    stNasQosInd.enPrimId            = ID_NAS_OM_QOS_CONFIRM;
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */
    stNasQosInd.usToolsId           = 0;

    stDiagTransInd.ulModule         = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(WUEPS_PID_SM), DIAG_MODE_UMTS);;
    stDiagTransInd.ulPid            = WUEPS_PID_SM;
    stDiagTransInd.ulMsgId          = ID_NAS_OM_QOS_CONFIRM;
    stDiagTransInd.ulLength         = sizeof(NAS_QOS_IND_STRUCT);
    stDiagTransInd.pData            = &stNasQosInd;

    /* ������Ϣ */
    ulRet = DIAG_TransReport(&stDiagTransInd);
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_SM_SndOmQosIndMsg:WARNING: Send msg fail.");
    }

    return ulRet;

}


/*****************************************************************************
 �� �� ��  : NAS_SM_SndOmPdpCtxIndMsg
 ��������  : ����OM�Ĳ�ѯ��Ϣ͸����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ulRet: ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��7��21��
   ��    ��   : wx270776
   �޸�����   : OM�ں�
 2.��    ��   : 2015��9��17��
   ��    ��   : zwx247453
   �޸�����   : Dallas�Ĵ�����ԭ���ϱ���BBP������Ŀ
*****************************************************************************/
VOS_UINT32 NAS_SM_SndOmPdpCtxIndMsg(VOS_VOID)
{
    NAS_OM_PDP_CONTEXT_IND_STRU        *pstNasOmPdpCtxInd = VOS_NULL_PTR;
    DIAG_TRANS_IND_STRU                 stDiagTransInd;
    VOS_UINT32                          ulRet;

    /* �����ڴ� */
    pstNasOmPdpCtxInd = (NAS_OM_PDP_CONTEXT_IND_STRU*)PS_MEM_ALLOC(WUEPS_PID_SM, sizeof(NAS_OM_PDP_CONTEXT_IND_STRU));
    if (VOS_NULL_PTR == pstNasOmPdpCtxInd)
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_SM_SndOmPdpCtxIndMsg:PS_MEM_ALLOC fail.");
        return VOS_ERR;
    }

    /* ��ʼ�� */
    PS_MEM_SET(pstNasOmPdpCtxInd, 0x00, sizeof(NAS_OM_PDP_CONTEXT_IND_STRU));

    /*��ȡ��Ӧ��PDP�����ĵ�IEֵ*/
    NAS_SM_FillPDPContextInfo(pstNasOmPdpCtxInd);
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, begin */
    pstNasOmPdpCtxInd->enPrimId     = ID_NAS_OM_PDP_CONTEXT_CONFIRM;
    /* Modified by zwx247453 for �Ĵ����ϱ�, 2015-09-17, end */
    pstNasOmPdpCtxInd->usToolsId    = 0;

    stDiagTransInd.ulModule         = DIAG_GEN_MODULE(VOS_GetModemIDFromPid(WUEPS_PID_SM), DIAG_MODE_UMTS);;
    stDiagTransInd.ulPid            = WUEPS_PID_SM;
    stDiagTransInd.ulMsgId          = ID_NAS_OM_PDP_CONTEXT_CONFIRM;
    stDiagTransInd.ulLength         = sizeof(NAS_OM_PDP_CONTEXT_IND_STRU);
    stDiagTransInd.pData            = pstNasOmPdpCtxInd;

    /* ������Ϣ */
    ulRet = DIAG_TransReport(&stDiagTransInd);
    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_SM, "NAS_SM_SndOmPdpCtxIndMsg:WARNING: Send msg fail.");
    }

    PS_MEM_FREE(WUEPS_PID_SM, pstNasOmPdpCtxInd);

    return ulRet;

}
/* Added by wx270776 for OM�ں�, 2015-7-21, end */

VOS_VOID Sm_OmQuery(
    VOS_VOID                           *pMsg
)
{
    /* Modified by wx270776 for OM�ں�, 2015-7-1, begin */
    ID_NAS_OM_INQUIRE_STRU             *pOmMsg;
    NAS_QOS_STRUCT                     *pQosMsg;
    VOS_UINT32                          ulRet;
    NAS_OM_PDP_CONTEXT_STRU            *pPDPCntxtMsg;                          /*����PDP�����ĵĿ�ά�ɲ�*/
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulSndOmRet;

    pOmMsg = (ID_NAS_OM_INQUIRE_STRU *)pMsg;

    switch (pOmMsg->ulMsgId)
    {
    case ID_NAS_OM_QOS_INQUIRE:
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "Sm_OmQuery:receive om message!");

        /* 1. ��OM����IND��Ϣ */
        ulSndOmRet = NAS_SM_SndOmQosIndMsg();

        /* 2. �򹤾߲�ظ�CNF��Ϣ */
        /* ������Ϣ */
        ulMsgLen = sizeof(NAS_QOS_STRUCT) - VOS_MSG_HEAD_LENGTH;

        pQosMsg = (NAS_QOS_STRUCT *)PS_ALLOC_MSG(WUEPS_PID_SM, ulMsgLen);
        if (VOS_NULL_PTR == pQosMsg)
        {
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Sm_OmQuery:Error: Memory Allocate fail!");

            return;
        }

        /* ��ʼ�� */
        PS_MEM_SET((VOS_UINT8*)pQosMsg + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLen);

        /* ��д��Ϣ���� */
        pQosMsg->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
        pQosMsg->ulMsgId          = ID_NAS_OM_QOS_CONFIRM;
        pQosMsg->usOriginalId     = pOmMsg->usOriginalId;
        pQosMsg->usTerminalId     = pOmMsg->usTerminalId;
        pQosMsg->ulTimeStamp      = pOmMsg->ulTimeStamp;
        pQosMsg->ulSN             = pOmMsg->ulSN;
        pQosMsg->enResult         = ulSndOmRet;

        /* ������Ϣ */
        ulRet = PS_SEND_MSG(WUEPS_PID_SM, pQosMsg);
        if (VOS_OK != ulRet)
        {
            MN_WARN_LOG("NAS_MMC_SndOmOtaCnf:WARNING: Send msg fail.");
        }
        else
        {
            MN_INFO_LOG("NAS_MMC_SndOmOtaCnf:ID_NAS_OM_QOS_CONFIRM has been sent.");
        }

        break;

    /*����PDP�����ĵĿ�ά�ɲ�*/
    case ID_NAS_OM_PDP_CONTEXT_INQUIRE:

        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "Sm_OmQuery:receive om message ID_NAS_OM_PDP_CONTEXT_INQUIRE!");

        /* 1. ��OM����IND��Ϣ */
        ulSndOmRet = NAS_SM_SndOmPdpCtxIndMsg();

        /* 2. �򹤾߲�ظ�CNF��Ϣ */
        /* ������Ϣ */
        ulMsgLen     = sizeof(NAS_OM_PDP_CONTEXT_STRU) - VOS_MSG_HEAD_LENGTH;

        pPDPCntxtMsg = (NAS_OM_PDP_CONTEXT_STRU *)PS_ALLOC_MSG(WUEPS_PID_SM, ulMsgLen);
        if (VOS_NULL_PTR == pPDPCntxtMsg)
        {
            PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Sm_OmQuery:Error: Memory Allocate NAS_PDP_CONTEXT_STRU fail!");

            return;
        }

        /* ��ʼ�� */
        PS_MEM_SET((VOS_UINT8*)pPDPCntxtMsg + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLen);

        /* ��д��Ϣ���� */
        pPDPCntxtMsg->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
        pPDPCntxtMsg->ulMsgId          = ID_NAS_OM_PDP_CONTEXT_CONFIRM;
        pPDPCntxtMsg->usOriginalId     = pOmMsg->usOriginalId;
        pPDPCntxtMsg->usTerminalId     = pOmMsg->usTerminalId;
        pPDPCntxtMsg->ulTimeStamp      = pOmMsg->ulTimeStamp;
        pPDPCntxtMsg->ulSN             = pOmMsg->ulSN;
        pPDPCntxtMsg->enResult         = ulSndOmRet;

        /* ������Ϣ */
        ulRet = PS_SEND_MSG(WUEPS_PID_SM, pPDPCntxtMsg);
        if (VOS_OK != ulRet)
        {
            MN_WARN_LOG("NAS_MMC_SndOmOtaCnf:WARNING: Send msg fail.");
        }
        else
        {
            MN_INFO_LOG("NAS_MMC_SndOmOtaCnf:ID_NAS_OM_PDP_CONTEXT_CONFIRM has been sent.");
        }

        break;

    default:
        PS_NAS_LOG(WUEPS_PID_SM, VOS_NULL, PS_LOG_LEVEL_NORMAL,
                "Sm_OmQuery:wrong PrimId!");
        break;
    }

    /* Modified by wx270776 for OM�ں�, 2015-7-1, end */
}
SM_TAF_CAUSE_ENUM_UINT16 NAS_SM_MapGmmCause(
    GMM_SM_CAUSE_ENUM_UINT16            enGmmCause
)
{
    NAS_SM_GMM_ERR_CODE_MAP_STRU       *pstGmmErrMapTblPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulGmmErrMapTblSize;
    VOS_UINT32                          ulCnt;

    pstGmmErrMapTblPtr = NAS_SM_GET_GMM_ERR_CODE_MAP_TBL_PTR();
    ulGmmErrMapTblSize = NAS_SM_GET_GMM_ERR_CODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulGmmErrMapTblSize; ulCnt++)
    {
        if (pstGmmErrMapTblPtr[ulCnt].enGmmCause == enGmmCause)
        {
            return pstGmmErrMapTblPtr[ulCnt].enSmCuase;
        }
    }

    return SM_TAF_CAUSE_GMM_UNKNOWN;
}

/* Added by w00316404 for Update SM protocol, 2015-08-24, Begin */
/*****************************************************************************
 �� �� ��  : NAS_SM_MapSmNWCause
 ��������  : ��SM NW�Ĵ��������ƫ�Ƶõ�SM�Ĵ�����
 �������  : ucSmCause - SM NW�Ĵ�����
 �������  : ��
 �� �� ֵ  : SM_TAF_CAUSE_ENUM_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��24��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
SM_TAF_CAUSE_ENUM_UINT16 NAS_SM_MapSmNWCause(VOS_UINT8 ucSmCause)
{
    SM_TAF_CAUSE_ENUM_UINT16            usSmCause;

    usSmCause = NAS_SM_TRANS_SM_NW_CAUSE(ucSmCause);

    /* # 95: - 111: protocol errors. */
    if ( (SM_TAF_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE <= usSmCause)
      && (SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED       >= usSmCause))
    {
        usSmCause = SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED;
    }

    return usSmCause;
}
/* Added by w00316404 for Update SM protocol, 2015-08-24, End */

/*lint +e958*/



#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
