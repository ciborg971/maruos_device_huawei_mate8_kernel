
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CmmcaPktMgmt.h"
#include "CmmcaCtx.h"
#include "CmmcaTimerMgmt.h"

#include "CbpaPsInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_CMMCA_PKT_MGMT_C

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
const CMMCA_PKT_ERR_CODE_MAP_TBL_STRU  g_astCmmcaErrCodeMapTbl[] =
{
    { TAF_PS_CAUSE_SUCCESS,                                             CMMCA_RAT_MMC_PKT_ERRCODE_NOERROR                                        },
    { TAF_PS_CAUSE_INVALID_PARAMETER,                                   CMMCA_RAT_MMC_PKT_ERRCODE_INVILID_PARA                                   },
    { TAF_PS_CAUSE_CID_INVALID,                                         CMMCA_RAT_MMC_PKT_ERRCODE_INVILID_CID                                    },
    { TAF_PS_CAUSE_SIM_INVALID,                                         CMMCA_RAT_MMC_PKT_ERRCODE_SIM_INVILID                                    },

    { TAF_PS_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING,                   CMMCA_RAT_MMC_PKT_ERRCODE_NW_OPERATOR_DETERMINED_BARRING,                },
    { TAF_PS_CAUSE_SM_NW_INSUFFICIENT_RESOURCES,                        CMMCA_RAT_MMC_PKT_ERRCODE_NW_INSUFFICIENT_RESOURCES,                     },
    { TAF_PS_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN,                         CMMCA_RAT_MMC_PKT_ERRCODE_NW_MISSING_OR_UKNOWN_APN,                      },
    { TAF_PS_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE,                      CMMCA_RAT_MMC_PKT_ERRCODE_NW_UNKNOWN_PDP_ADDR_OR_TYPE,                   },
    { TAF_PS_CAUSE_SM_NW_USER_AUTHENTICATION_FAIL ,                     CMMCA_RAT_MMC_PKT_ERRCODE_NW_USER_AUTHENTICATION_FAIL ,                  },
    { TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_BY_GGSN_SGW_OR_PGW,        CMMCA_RAT_MMC_PKT_ERRCODE_NW_ACTIVATION_REJECTED_BY_GGSN,     },
    { TAF_PS_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED,               CMMCA_RAT_MMC_PKT_ERRCODE_NW_ACTIVATION_REJECTED_UNSPECIFIED,            },
    { TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED,                  CMMCA_RAT_MMC_PKT_ERRCODE_NW_SERVICE_OPTION_NOT_SUPPORTED,               },
    { TAF_PS_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED,              CMMCA_RAT_MMC_PKT_ERRCODE_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED,           },
    { TAF_PS_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER,                 CMMCA_RAT_MMC_PKT_ERRCODE_NW_SERVICE_OPTION_TEMP_OUT_ORDER,              },
    { TAF_PS_CAUSE_SM_NW_NSAPI_ALREADY_USED,                            CMMCA_RAT_MMC_PKT_ERRCODE_NW_NSAPI_ALREADY_USED,                         },
    { TAF_PS_CAUSE_SM_NW_REGULAR_DEACTIVATION,                          CMMCA_RAT_MMC_PKT_ERRCODE_NW_REGULAR_DEACTIVATION,                       },
    { TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED,                              CMMCA_RAT_MMC_PKT_ERRCODE_NW_QOS_NOT_ACCEPTED,                           },
    { TAF_PS_CAUSE_SM_NW_NETWORK_FAILURE,                               CMMCA_RAT_MMC_PKT_ERRCODE_NW_NETWORK_FAILURE,                            },
    { TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_TFT,                           CMMCA_RAT_MMC_PKT_ERRCODE_NW_SEMANTIC_ERR_IN_TFT,                        },
    { TAF_PS_CAUSE_SM_NW_SYNTACTIC_ERR_IN_TFT,                          CMMCA_RAT_MMC_PKT_ERRCODE_NW_SYNTACTIC_ERR_IN_TFT,                       },
    { TAF_PS_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT,                            CMMCA_RAT_MMC_PKT_ERRCODE_NW_UKNOWN_PDP_CONTEXT,                         },
    { TAF_PS_CAUSE_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER,                 CMMCA_RAT_MMC_PKT_ERRCODE_NW_SEMANTIC_ERR_IN_PACKET_FILTER,              },
    { TAF_PS_CAUSE_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER,               CMMCA_RAT_MMC_PKT_ERRCODE_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER,            },
    { TAF_PS_CAUSE_SM_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED,             CMMCA_RAT_MMC_PKT_ERRCODE_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED,          },
    { TAF_PS_CAUSE_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED,                  CMMCA_RAT_MMC_PKT_ERRCODE_NW_LAST_PDN_DISCONN_NOT_ALLOWED,               },
    { TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED,                    CMMCA_RAT_MMC_PKT_ERRCODE_NW_PDP_TYPE_IPV4_ONLY_ALLOWED,                 },
    { TAF_PS_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED,                    CMMCA_RAT_MMC_PKT_ERRCODE_NW_PDP_TYPE_IPV6_ONLY_ALLOWED,                 },
    { TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED,              CMMCA_RAT_MMC_PKT_ERRCODE_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED,           },
    { TAF_PS_CAUSE_SM_NW_INFORMATION_NOT_RECEIVED,                      CMMCA_RAT_MMC_PKT_ERRCODE_NW_INFORMATION_NOT_RECEIVED,                   },
    { TAF_PS_CAUSE_SM_NW_PDN_CONNECTION_DOES_NOT_EXIST,                 CMMCA_RAT_MMC_PKT_ERRCODE_NW_PDN_CONNECTION_DOES_NOT_EXIST,              },
    { TAF_PS_CAUSE_SM_NW_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED,     CMMCA_RAT_MMC_PKT_ERRCODE_NW_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED,  },
    { TAF_PS_CAUSE_SM_NW_COLLISION_WITH_NW_INITIATED_REQUEST,           CMMCA_RAT_MMC_PKT_ERRCODE_NW_COLLISION_WITH_NW_INITIATED_REQUEST,        },
    { TAF_PS_CAUSE_SM_NW_UNSUPPORTED_QCI_VALUE,                         CMMCA_RAT_MMC_PKT_ERRCODE_NW_UNSUPPORTED_QCI_VALUE,                      },
    { TAF_PS_CAUSE_SM_NW_INVALID_TI,                                    CMMCA_RAT_MMC_PKT_ERRCODE_NW_INVALID_TI,                                 },
    { TAF_PS_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE,                CMMCA_RAT_MMC_PKT_ERRCODE_NW_SEMANTICALLY_INCORRECT_MESSAGE,             },
    { TAF_PS_CAUSE_SM_NW_INVALID_MANDATORY_INFO,                        CMMCA_RAT_MMC_PKT_ERRCODE_NW_INVALID_MANDATORY_INFO,                     },
    { TAF_PS_CAUSE_SM_NW_MSG_TYPE_NON_EXISTENT,                         CMMCA_RAT_MMC_PKT_ERRCODE_NW_MSG_TYPE_NON_EXISTENT,                      },
    { TAF_PS_CAUSE_SM_NW_MSG_TYPE_NOT_COMPATIBLE,                       CMMCA_RAT_MMC_PKT_ERRCODE_NW_MSG_TYPE_NOT_COMPATIBLE,                    },
    { TAF_PS_CAUSE_SM_NW_IE_NON_EXISTENT,                               CMMCA_RAT_MMC_PKT_ERRCODE_NW_IE_NON_EXISTENT,                            },
    { TAF_PS_CAUSE_SM_NW_CONDITIONAL_IE_ERR,                            CMMCA_RAT_MMC_PKT_ERRCODE_NW_CONDITIONAL_IE_ERR,                         },
    { TAF_PS_CAUSE_SM_NW_MSG_NOT_COMPATIBLE,                            CMMCA_RAT_MMC_PKT_ERRCODE_NW_MSG_NOT_COMPATIBLE,                         },
    { TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED,                      CMMCA_RAT_MMC_PKT_ERRCODE_NW_PROTOCOL_ERR_UNSPECIFIED,                   },
    { TAF_PS_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE,                  CMMCA_RAT_MMC_PKT_ERRCODE_NW_APN_RESTRICTION_INCOMPATIBLE,               },

    { TAF_PS_CAUSE_GMM_PS_DETACH,                                       CMMCA_RAT_MMC_PKT_ERRCODE_PS_DETACH                                      },
    { TAF_PS_CAUSE_GMM_DETACH_NOT_REATTACH,                             CMMCA_RAT_MMC_PKT_ERRCODE_DETACH_NOT_REATTACH                            }

};

/* g_astCmmcaErrCodeMapTbl��Item���� */
const VOS_UINT32 g_ulCmmcaErrCodeMapTblSize  = sizeof(g_astCmmcaErrCodeMapTbl) / sizeof(g_astCmmcaErrCodeMapTbl[0]);

/* APS��Ϣ������ */
const CMMCA_PKT_EVT_FUNC_TBL_STRU       g_astCmmcaPktPsEvtFuncTbl[] =
{
    /* ���������� */
    {ID_EVT_TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF,
        CMMCA_PKT_RcvTafPsEvtSetPrimPdpContextInfoCnf},

    /* ��Ȩ�ظ� */
    {ID_EVT_TAF_PS_SET_AUTHDATA_INFO_CNF,
        CMMCA_PKT_RcvTafSetPdnPcoAuthCnf},

    /* PS CALL */
    {ID_EVT_TAF_PS_CALL_ORIG_CNF,
        CMMCA_PKT_RcvTafPsEvtCallOrigCnf},
    {ID_EVT_TAF_PS_CALL_END_CNF,
        CMMCA_PKT_RcvTafPsEvtCallEndCnf},
    {ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF,
        CMMCA_PKT_RcvTafPsEvtPdpActivateCnf},
    {ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ,
        CMMCA_PKT_RcvTafPsEvtPdpActivateRej},
    {ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_IND,
        CMMCA_PKT_RcvTafPsEvtPdpActivateInd},
    {ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND,
        CMMCA_PKT_RcvTafPsEvtPdpModifyInd},
    {ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF,
        CMMCA_PKT_RcvTafPsEvtPdpDeactivateCnf},
    {ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND,
        CMMCA_PKT_RcvTafPsEvtPdpDeactivateInd},
    {ID_EVT_TAF_PS_CALL_PDP_IPV6_INFO_IND,
        CMMCA_PKT_RcvTafPsEvtPdpIpv6InfoInd},
};

/* g_astCmmcaPktPsEvtFuncTbl��Item���� */
const VOS_UINT32 g_ulCmmcaPktPsEvtFuncTblSize  = sizeof(g_astCmmcaPktPsEvtFuncTbl) / sizeof(g_astCmmcaPktPsEvtFuncTbl[0]);


/*****************************************************************************
  3 ��������
*****************************************************************************/


VOS_VOID CMMCA_PKT_RcvCmmcSetPdnTabReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd = VOS_NULL_PTR;
    CMMCA_MMC_RAT_SET_PDN_TAB_REQ_STRU  stSetPdnTabReq;
    CMMCA_PKT_PDN_TAB_BUFF_ITEM_STRU    stPdnTabBuffItem;
    TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpCtxInfo;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucOpId;

    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stSetPdnTabReq, 0, sizeof(CMMCA_MMC_RAT_SET_PDN_TAB_REQ_STRU));

    PS_MEM_SET(&stPdnTabBuffItem, 0, sizeof(CMMCA_PKT_PDN_TAB_BUFF_ITEM_STRU));

    PS_MEM_SET(&stPdpCtxInfo, 0, sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));

    /* ���ý���������CMD���������ɶ�Ӧ�����ݽṹ�����������ѱ�֤��������Ч�� */
    ulRslt = CMMCA_ParseSetPdnTabReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                     pstDataInd->aucData,
                                     &stSetPdnTabReq);

    if (VOS_OK != ulRslt)
    {
        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_PKT_SndSetPdnRsp(CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_FAIL);
        return;
    }

    /* û��Ҫ���õ�PDN������ֱ�ӷ���SUCC */
    if (0 == stSetPdnTabReq.ulTotalNum)
    {
        /* ֱ�ӻ�RSP(SUCC) */
        CMMCA_PKT_SndSetPdnRsp(CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_SUCC);

        return;
    }

    ucOpId = CMMCA_OPID_INVILID_VALUE;

    /* ����OP ID */
    CMMCA_AssignOpid(&ucOpId);

    /* ����PDN TABLE�Ĳ��� */
    stPdnTabBuffItem.enCmdId    = ID_CMMCA_MMC_RAT_PDN_TABLE_SETUP_REQ;
    stPdnTabBuffItem.ucCurIndex = 0;
    stPdnTabBuffItem.ucTotalNum = (VOS_UINT8)stSetPdnTabReq.ulTotalNum;
    PS_MEM_CPY(stPdnTabBuffItem.astPdnInfo,
               stSetPdnTabReq.astPdnInfo,
               sizeof(CMMCA_PDN_INFO_STRU) * stSetPdnTabReq.ulTotalNum);

    ulRslt = CMMCA_SaveItemInCmdBufferQueue(ucOpId, (VOS_UINT8 *)(&stPdnTabBuffItem), sizeof(CMMCA_PKT_PDN_TAB_BUFF_ITEM_STRU));
    if (VOS_OK != ulRslt)
    {
        CMMCA_PKT_SndSetPdnRsp(CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_FAIL);
        return;
    }

    /* ��table index=0��ʼ���ã�������� */
    CMMCA_PKT_BuildPrimPdpContextInfo(&(stSetPdnTabReq.astPdnInfo[0]), &stPdpCtxInfo);

    /* ����TAF_PS_SetPrimPdpContextInfo������������ */
    ulRslt = TAF_PS_SetPrimPdpContextInfo(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpId, &stPdpCtxInfo);

    if (VOS_OK != ulRslt)
    {
        CMMCA_DelItemInCmdBufferQueue(ucOpId);

        CMMCA_PKT_SndSetPdnRsp(CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_FAIL);
        return;
    }

    return;
}


VOS_UINT32 CMMCA_PKT_RcvCmmcDefaultBearConnReq_PreProc(
    CBPCA_DATA_IND_MSG_STRU                     *pstDataInd,
    CMMCA_MMC_RAT_DEFAULT_BEAR_CONN_REQ_STRU    *pstDefBearConnReq,
    VOS_UINT8                                   *pucPdnEntityIndex
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRslt;
    CMMCA_CONN_STATUS_ENUM_UINT8        enCurConnStatus;

    /* ���ý���������CMD���������ɶ�Ӧ�����ݽṹ�����������ѱ�֤��������Ч�� */
    ulRslt = CMMCA_ParseDefaultBearConnReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                           pstDataInd->aucData,
                                           pstDefBearConnReq);

    if (VOS_OK != ulRslt)
    {
        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_PKT_SndDefaultBearConnRsp(pstDefBearConnReq->ucPdnId,
                                        CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                        CMMCA_RAT_MMC_PKT_ERRCODE_INVILID_PARA);
        return VOS_TRUE;
    }

    ucIndex = CMMCA_PKT_FindPdnConnEntityIndex(pstDefBearConnReq->ucPdnId);

    /* �����PDN ID��Ӧ��ʵ�岻���� */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucIndex)
    {
        /* ����һ���µ�ʵ�� */
        CMMCA_PKT_AssignPdnConnEntity(pstDefBearConnReq->ucPdnId, pucPdnEntityIndex);

        /* û�з��䵽ʵ�� */
        if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == *pucPdnEntityIndex)
        {
            /* ֱ�ӻ�RSP(FAIL) */
            CMMCA_PKT_SndDefaultBearConnRsp(pstDefBearConnReq->ucPdnId,
                                            CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                            CMMCA_RAT_MMC_PKT_ERRCODE_INVILID_PARA);
            return VOS_TRUE;
        }
        /* ���䵽һ���µ�ʵ��,Ԥ�������,���𲦺� */
        else
        {
            /* ����PDNʵ���index */
            CMMCA_PKT_SavePdnConnEntityIndex(pstDefBearConnReq->ucPdnId, *pucPdnEntityIndex);

            CMMCA_PKT_SetUserPdnType(*pucPdnEntityIndex, pstDefBearConnReq->enPdnType);

            CMMCA_PKT_SetPdnRequestType(*pucPdnEntityIndex, pstDefBearConnReq->enRequestType);

            return VOS_FALSE;
        }
    }
    /* �����PDN ID��Ӧ��ʵ����� */
    else
    {
        enCurConnStatus = CMMCA_PKT_GetConnStatus(ucIndex);

        /* �����ǰ���Ӵ���CONNED״̬��ֱ�ӻظ�RSP(SUCC) */
        if (CMMCA_CONN_STATUS_CONNED == enCurConnStatus)
        {
            CMMCA_PKT_SndDefaultBearConnRsp(pstDefBearConnReq->ucPdnId,
                                            CMMCA_RAT_MMC_BEAR_CONN_RESULT_SUCC,
                                            CMMCA_RAT_MMC_PKT_ERRCODE_NOERROR);

            return VOS_TRUE;
        }

        /* �����ǰ���Ӵ���CONNING��INTERNAL DISCING״̬�����Ա��ε�REQ */
        if ((CMMCA_CONN_STATUS_CONNING == enCurConnStatus)
         || (CMMCA_CONN_STATUS_INTERNAL_DISCING == enCurConnStatus))
        {
            return VOS_TRUE;
        }

        /* �����ǰ���Ӵ���DISCING״̬��ֱ�ӻظ�RSP(FAIL, Errcode:conn is releasing) */
        if (CMMCA_CONN_STATUS_DISCING == enCurConnStatus)
        {
            CMMCA_PKT_SndDefaultBearConnRsp(pstDefBearConnReq->ucPdnId,
                                            CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                            CMMCA_RAT_MMC_PKT_ERRCODE_CONN_IS_RELEASING);
            return VOS_TRUE;
        }

        *pucPdnEntityIndex = ucIndex;

        /* ���𲦺����� */
        return VOS_FALSE;
    }

}
VOS_VOID CMMCA_PKT_RcvCmmcDefaultBearConnReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU                     *pstDataInd = VOS_NULL_PTR;
    TAF_PS_DIAL_PARA_STRU                        stDialPara;
    CMMCA_MMC_RAT_DEFAULT_BEAR_CONN_REQ_STRU     stDefBearConnReq;
    VOS_UINT8                                    ucPdnEntityIndex;
    VOS_UINT32                                   ulRslt;

    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    ucPdnEntityIndex = CMMCA_PDN_CONN_ENTITY_INDEX_INVALID;

    PS_MEM_SET(&stDefBearConnReq, 0, sizeof(CMMCA_MMC_RAT_DEFAULT_BEAR_CONN_REQ_STRU));

    PS_MEM_SET(&stDialPara, 0, sizeof(TAF_PS_DIAL_PARA_STRU));

    /* ���ý���������CMD���������ɶ�Ӧ�����ݽṹ�����������ѱ�֤��������Ч�� */
    ulRslt = CMMCA_PKT_RcvCmmcDefaultBearConnReq_PreProc(pstDataInd, &stDefBearConnReq, &ucPdnEntityIndex);

    /* Ԥ�������,�����㷢�𲦺� */
    if (VOS_TRUE == ulRslt)
    {
        return;
    }

    /* ��ȡSDF�����������ڶ�Ӧ��ʵ���� */
    ulRslt = CMMCA_PKT_ProcSdfPara(stDefBearConnReq.ucPdnId, ucPdnEntityIndex);

    if (VOS_OK != ulRslt)
    {
        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_PKT_SndDefaultBearConnRsp(stDefBearConnReq.ucPdnId,
                                        CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                        CMMCA_RAT_MMC_PKT_ERRCODE_INVILID_PARA);

        /* ���ʵ�弰ӳ���ϵ */
        CMMCA_PKT_FreePdnConnEntity(stDefBearConnReq.ucPdnId);

        return;
    }

    /* ��ѡ���SDF����ת���ɲ��Ų�����ʽ */
    CMMCA_PKT_GetDialParaFromSdfPara(ucPdnEntityIndex, &stDialPara);

    /* ���PDN Request Type */
    stDialPara.bitOpReqType     = VOS_TRUE;

    if (CMMCA_PDN_REQUEST_TYPE_INITIAL == stDefBearConnReq.enRequestType)
    {
        stDialPara.enPdpRequestType = TAF_PDP_REQUEST_TYPE_INITIAL;
    }
    else
    {
        stDialPara.enPdpRequestType = TAF_PDP_REQUEST_TYPE_HANDOVER;
    }

    /* ����API�ӿ�TAF_PS_CallOrig����APS�������� */
    if (VOS_OK == TAF_PS_CallOrig(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, &stDialPara))
    {
        /* ���µ�CONNING״̬ */
        CMMCA_PKT_SetConnStatus(ucPdnEntityIndex, CMMCA_CONN_STATUS_CONNING);

        /* �����û����������PDN���� */
        CMMCA_PKT_SetUserPdnType(ucPdnEntityIndex, stDefBearConnReq.enPdnType);

        /* �����û����������PDN�������� */
        CMMCA_PKT_SetPdnRequestType(ucPdnEntityIndex, stDefBearConnReq.enRequestType);
    }
    else
    {
        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_PKT_SndDefaultBearConnRsp(stDefBearConnReq.ucPdnId,
                                        CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                        CMMCA_RAT_MMC_PKT_ERRCODE_UNKNOWN);


        /* ���ʵ�弰ӳ���ϵ */
        CMMCA_PKT_FreePdnConnEntity(stDefBearConnReq.ucPdnId);
    }

    return;
}
VOS_VOID CMMCA_PKT_RcvCmmcBearDiscReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU            *pstDataInd = VOS_NULL_PTR;
    CMMCA_MMC_RAT_BEAR_DISC_REQ_STRU    stDiscReq;
    VOS_UINT32                          ulRslt;
    CMMCA_CONN_STATUS_ENUM_UINT8        enCurConnStatus;
    VOS_UINT8                           ucPdnEntityIndex;

    pstDataInd = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    PS_MEM_SET(&stDiscReq, 0 , sizeof(CMMCA_MMC_RAT_BEAR_DISC_REQ_STRU));

    /* ���ý���������CMD���������ɶ�Ӧ�����ݽṹ�����������ѱ�֤��������Ч�� */
    ulRslt = CMMCA_ParseBearDiscReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                    pstDataInd->aucData,
                                    &stDiscReq);

    if (VOS_OK != ulRslt)
    {
        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_PKT_SndBearDiscRsp(stDiscReq.ucPdnId, CMMCA_RAT_MMC_RESULT_FAIL);
        return;
    }

    /* Ŀǰֻ֧��default���أ�dedicated���أ�ֱ�ӷ���RSP(FAIL) */
    if (VOS_TRUE != stDiscReq.ucIsDefaultBearer)
    {
        CMMCA_PKT_SndBearDiscRsp(stDiscReq.ucPdnId, CMMCA_RAT_MMC_RESULT_FAIL);
        return;
    }

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(stDiscReq.ucPdnId);

    /* ʵ�岻���� */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        /* ֱ�ӻظ�RSP(SUCC) */
        CMMCA_PKT_SndBearDiscRsp(stDiscReq.ucPdnId, CMMCA_RAT_MMC_RESULT_SUCC);

        return;
    }

    enCurConnStatus = CMMCA_PKT_GetConnStatus(ucPdnEntityIndex);

    /* �����ǰ���Ӵ���DISCING��INTERNAL DISCING״̬�����Ա��ε�REQ */
    if ((CMMCA_CONN_STATUS_DISCING == enCurConnStatus)
     || (CMMCA_CONN_STATUS_INTERNAL_DISCING == enCurConnStatus))
    {
        return;
    }

    /* �����ǰ���Ӵ���CONNING����CONNED״̬��ֹͣ�ȴ�IPV6������ʱ��������Ͽ��������� */
    CMMCA_StopTimer(WUEPS_PID_CMMCA, TI_CMMCA_WAIT_IPV6_RA_INFO);

    if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, stDiscReq.ucPdnId))
    {
        /* ��������״̬ΪDISCING */
        CMMCA_PKT_SetConnStatus(ucPdnEntityIndex, CMMCA_CONN_STATUS_DISCING);
    }
    else
    {
        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_PKT_SndBearDiscRsp(stDiscReq.ucPdnId, CMMCA_RAT_MMC_RESULT_FAIL);
    }

    return;
}
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtSetPrimPdpContextInfoCnf(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU   *pstSetPdpCtxInfoCnf = VOS_NULL_PTR;
    CMMCA_PKT_PDN_TAB_BUFF_ITEM_STRU            *pstPdnTabBuffItem  = VOS_NULL_PTR;
    CMMCA_CMD_BUFFER_STRU                       *pstCmdBuff  = VOS_NULL_PTR;
    TAF_PDP_PRIM_CONTEXT_EXT_STRU                stPdpCtxInfo;
    VOS_UINT32                                   ulRslt;

    pstSetPdpCtxInfoCnf  = (TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_CNF_STRU*)pEvtInfo;

    PS_MEM_SET(&stPdpCtxInfo, 0, sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));

    pstCmdBuff = CMMCA_GetItemFromCmdBufferQueue(pstSetPdpCtxInfoCnf->stCtrl.ucOpId);

    if (VOS_NULL_PTR == pstCmdBuff)
    {
        return VOS_ERR;
    }

    /* �������ʧ�ܣ�ֱ�Ӹ��ϲ㷵������ʧ�� */
    if (TAF_PS_CAUSE_SUCCESS != pstSetPdpCtxInfoCnf->enCause)
    {
        CMMCA_PKT_SndSetPdnRsp(CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_FAIL);

        CMMCA_DelItemInCmdBufferQueue(pstSetPdpCtxInfoCnf->stCtrl.ucOpId);

        return VOS_ERR;
    }

    pstPdnTabBuffItem = (CMMCA_PKT_PDN_TAB_BUFF_ITEM_STRU *)pstCmdBuff->pucMsgInfo;

    /* ������óɹ����жϵ�ǰPdnId�Ƿ�ΪPDN table�����һ������������һ��PdnId�����ϲ㷵�����óɹ� */
    if ((pstPdnTabBuffItem->ucTotalNum -1 ) == pstPdnTabBuffItem->ucCurIndex )
    {
        CMMCA_PKT_SndSetPdnRsp(CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_SUCC);

        CMMCA_DelItemInCmdBufferQueue(pstSetPdpCtxInfoCnf->stCtrl.ucOpId);

        return VOS_OK;
    }

    /* ���򣬴ӱ���Ĳ�����ȡ����һ��PdnId����Ϣ������API�ӿ�TAF_PS_SetPrimPdpContextInfo���ã�OPIDʹ�ñ���� */
    pstPdnTabBuffItem->ucCurIndex++;

    CMMCA_PKT_BuildPrimPdpContextInfo(&(pstPdnTabBuffItem->astPdnInfo[pstPdnTabBuffItem->ucCurIndex]),
                                      &stPdpCtxInfo);

    ulRslt = TAF_PS_SetPrimPdpContextInfo(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, pstSetPdpCtxInfoCnf->stCtrl.ucOpId, &stPdpCtxInfo);

    if (VOS_OK != ulRslt)
    {
        CMMCA_PKT_SndSetPdnRsp(CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_FAIL);

        CMMCA_DelItemInCmdBufferQueue(pstSetPdpCtxInfoCnf->stCtrl.ucOpId);

        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtCallOrigCnf(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_ORIG_CNF_STRU          *pstCallOrigCnf  = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnEntityIndex;
    VOS_UINT8                           ucErrCode;

    pstCallOrigCnf  = (TAF_PS_CALL_ORIG_CNF_STRU*)pEvtInfo;

    /* Pdn Id��Ч�Լ�� */
    if (!CMMCA_IS_VALID_PDN_ID(pstCallOrigCnf->ucCid))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtCallOrigCnf: Pdn Id is Invalid!");
        return VOS_ERR;
    }

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(pstCallOrigCnf->ucCid);

    /* ʵ�岻���� */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtCallOrigCnf: Not Find Entity!");
        return VOS_ERR;
    }

    /* ����CONNING״̬����ֱ���˳� */
    if (CMMCA_CONN_STATUS_CONNING != CMMCA_PKT_GetConnStatus(ucPdnEntityIndex))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtCallOrigCnf: Not CONNING state!");
        return VOS_ERR;
    }

    /* APS���سɹ���ֱ���˳����ȴ������� */
    if (TAF_PS_CAUSE_SUCCESS == pstCallOrigCnf->enCause)
    {
        return VOS_OK;
    }

    /* ��APS�Ĵ�����ת����CMMC�Ĵ����� */
    ucErrCode = CMMCA_PKT_TransferErrCode(pstCallOrigCnf->enCause);

    /* ��RSP(FAIL) */
    CMMCA_PKT_SndDefaultBearConnRsp(pstCallOrigCnf->ucCid,
                                    CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                    ucErrCode);

    /* ���ʵ�弰ӳ���ϵ */
    CMMCA_PKT_FreePdnConnEntity(pstCallOrigCnf->ucCid);

    return VOS_OK;
}
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtCallEndCnf(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_END_CNF_STRU           *pstCallEndCnf  = VOS_NULL_PTR;
    CMMCA_CONN_STATUS_ENUM_UINT8        enCurConnStatus;
    VOS_UINT8                           ucPdnEntityIndex;

    pstCallEndCnf  = (TAF_PS_CALL_END_CNF_STRU*)pEvtInfo;

    /* Pdn Id��Ч�Լ�� */
    if (!CMMCA_IS_VALID_PDN_ID(pstCallEndCnf->ucCid))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtCallEndCnf: Pdn Id is Invalid!");
        return VOS_ERR;
    }

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(pstCallEndCnf->ucCid);

    /* ʵ�岻���� */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtCallEndCnf: Not Find Entity!");
        return VOS_ERR;
    }

    enCurConnStatus = CMMCA_PKT_GetConnStatus(ucPdnEntityIndex);

    /* ����DISCING��INTERNAL DISCING״̬����ֱ���˳� */
    if ((CMMCA_CONN_STATUS_DISCING != enCurConnStatus)
     && (CMMCA_CONN_STATUS_INTERNAL_DISCING != enCurConnStatus))
    {
        return VOS_ERR;
    }

    /* APS���سɹ���ֱ���˳����ȴ�ȥ������ */
    if (TAF_PS_CAUSE_SUCCESS == pstCallEndCnf->enCause)
    {
        return VOS_OK;
    }
    else
    {
        /* ĿǰAPSֻ��pdp id��Ӧʵ�岻���ڻ���Client Id��һ��ʱ�ظ�ʧ�� */
        CMMCA_ERROR1_LOG("CMMCA_PKT_RcvTafPsEvtCallEndCnf: End fail, enCause is ", pstCallEndCnf->enCause);

        return VOS_ERR;
    }
}
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpActivateCnf(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf = VOS_NULL_PTR;
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnConnEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnEntityIndex;

    /* ��ʼ�� */
    pstPdpActivateCnf                   = (TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU*)pEvtInfo;

    /* Pdn Id��Ч�Լ�� */
    if (!CMMCA_IS_VALID_PDN_ID(pstPdpActivateCnf->ucCid))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtPdpActivateCnf: Pdn Id is Invalid!");
        return VOS_ERR;
    }

    /* Ŀǰֻ֧��ȱʡ���أ������ר�г��أ������� */
    if (VOS_TRUE == pstPdpActivateCnf->bitOpLinkdRabId)
    {
        return VOS_ERR;
    }

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(pstPdpActivateCnf->ucCid);

    /* ʵ�岻���� */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return VOS_ERR;
    }

    /* ��ǰ����CONNING״̬����ֱ���˳� */
    if (CMMCA_CONN_STATUS_CONNING != CMMCA_PKT_GetConnStatus(ucPdnEntityIndex))
    {
        return VOS_ERR;
    }

    /* ����PDP��Ϣ */
    pstPdnConnEntity                    = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex);

    CMMCA_PKT_SavePdpInfo(&(pstPdnConnEntity->stPdpInfo), pstPdpActivateCnf);

    /* ����PDP���ͷֱ���*/
    switch (pstPdpActivateCnf->stPdpAddr.enPdpType)
    {
        case TAF_PDP_IPV4:
            CMMCA_PKT_ProcIpv4ActCnf(ucPdnEntityIndex, pstPdpActivateCnf);
            break;

        case TAF_PDP_IPV6:
            CMMCA_PKT_ProcIpv6ActCnf(pstPdpActivateCnf);
            break;

        case TAF_PDP_IPV4V6:
            CMMCA_PKT_ProcIpv4v6ActCnf(pstPdpActivateCnf);
            break;

        default:
            break;
    }

    return VOS_OK;
}
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpActivateRej(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU  *pstPdpActivateRej = VOS_NULL_PTR;
    VOS_UINT8                           ucPdnEntityIndex;
    VOS_UINT8                           ucErrCode;

    /* ��ʼ�� */
    pstPdpActivateRej  = (TAF_PS_CALL_PDP_ACTIVATE_REJ_STRU*)pEvtInfo;

    /* Pdn Id��Ч�Լ�� */
    if (!CMMCA_IS_VALID_PDN_ID(pstPdpActivateRej->ucCid))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtPdpActivateRej: Pdn Id is Invalid!");
        return VOS_ERR;
    }

    ucPdnEntityIndex   = CMMCA_PKT_FindPdnConnEntityIndex(pstPdpActivateRej->ucCid);

    /* ʵ�岻���� */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return VOS_ERR;
    }

    /* ��ǰ����CONNING״̬����ֱ���˳� */
    if (CMMCA_CONN_STATUS_CONNING != CMMCA_PKT_GetConnStatus(ucPdnEntityIndex))
    {
        return VOS_ERR;
    }

    /* ��APS�Ĵ�����ת����CMMC�Ĵ����룬IPV4V6��Ҫ���⴦�� */
    if ((CMMCA_IP_TYPE_IPV4V6 == CMMCA_PKT_GetUserPdnType(ucPdnEntityIndex))
      && (CMMCA_IP_TYPE_IPV4V6 != pstPdpActivateRej->enPdpType)
      && (VOS_TRUE == pstPdpActivateRej->bitOpCauseEx)
      && (TAF_PS_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED == pstPdpActivateRej->enCauseEx))
    {
        ucErrCode = CMMCA_PKT_TransferErrCode(pstPdpActivateRej->enCauseEx);
    }
    else
    {
        ucErrCode = CMMCA_PKT_TransferErrCode(pstPdpActivateRej->enCause);
    }

    /* ���ϲ�ظ�RSP(FAIL, ERR CODE) */
    CMMCA_PKT_SndDefaultBearConnRsp(pstPdpActivateRej->ucCid,
                                    CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                    ucErrCode);

    /* ���ʵ�弰ӳ���ϵ */
    CMMCA_PKT_FreePdnConnEntity(pstPdpActivateRej->ucCid);

    return VOS_OK;
}
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpActivateInd(
    VOS_VOID                           *pEvtInfo
)
{
    /* reserved */
    return VOS_OK;
}
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpModifyInd(
    VOS_VOID                           *pEvtInfo
)
{
    /* reserved */
    return VOS_OK;
}
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpDeactivateCnf(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU    *pstPdpDeactivateCnf = VOS_NULL_PTR;
    CMMCA_CONN_STATUS_ENUM_UINT8            enCurConnStatus;
    VOS_UINT8                               ucPdnEntityIndex;

    /* ��ʼ�� */
    pstPdpDeactivateCnf = (TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU*)pEvtInfo;

    /* Pdn Id��Ч�Լ�� */
    if (!CMMCA_IS_VALID_PDN_ID(pstPdpDeactivateCnf->ucCid))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtPdpDeactivateCnf: Pdn Id is Invalid!");
        return VOS_ERR;
    }

    ucPdnEntityIndex    = CMMCA_PKT_FindPdnConnEntityIndex(pstPdpDeactivateCnf->ucCid);

    /* ʵ�岻���� */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return VOS_ERR;
    }

    /* ��ǰ����DISCING����INTERNAL DISCING״̬����ֱ���˳� */
    enCurConnStatus                     = CMMCA_PKT_GetConnStatus(ucPdnEntityIndex);

    if ((CMMCA_CONN_STATUS_DISCING != enCurConnStatus)
     && (CMMCA_CONN_STATUS_INTERNAL_DISCING != enCurConnStatus))
    {
        return VOS_ERR;
    }

    /* ������ڲ�ȥ���˵����RA��ʱ���µģ���Ҫ�ؼ����RSP������ȥ�����RSP */
    if (CMMCA_CONN_STATUS_DISCING == enCurConnStatus)
    {
        CMMCA_PKT_SndBearDiscRsp(pstPdpDeactivateCnf->ucCid, CMMCA_RAT_MMC_RESULT_SUCC);
    }
    else
    {
        CMMCA_PKT_SndDefaultBearConnRsp(pstPdpDeactivateCnf->ucCid,
                                        CMMCA_RAT_MMC_BEAR_CONN_RESULT_FAIL,
                                        CMMCA_RAT_MMC_PKT_ERRCODE_WATI_IPV6_RA_EXP);
    }

    /* ���ʵ�弰ӳ���ϵ */
    CMMCA_PKT_FreePdnConnEntity(pstPdpDeactivateCnf->ucCid);

    return VOS_OK;
}


VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpDeactivateInd(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU    *pstPdpDeactivateInd = VOS_NULL_PTR;
    VOS_UINT8                               ucPdnEntityIndex;

    /* ��ʼ�� */
    pstPdpDeactivateInd = (TAF_PS_CALL_PDP_DEACTIVATE_IND_STRU*)pEvtInfo;

    /* Pdn Id��Ч�Լ�� */
    if (!CMMCA_IS_VALID_PDN_ID(pstPdpDeactivateInd->ucCid))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtPdpDeactivateInd: Pdn Id is Invalid!");
        return VOS_ERR;
    }

    ucPdnEntityIndex    = CMMCA_PKT_FindPdnConnEntityIndex(pstPdpDeactivateInd->ucCid);

    /* ʵ�岻���� */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return VOS_ERR;
    }

    /* �ϱ�����ȥ����ָʾ */
    CMMCA_PKT_SndBearDiscInd(pstPdpDeactivateInd->ucCid);

    /* ���ʵ�弰ӳ���ϵ */
    CMMCA_PKT_FreePdnConnEntity(pstPdpDeactivateInd->ucCid);

    return VOS_OK;
}
VOS_UINT32 CMMCA_PKT_RcvTafPsEvtPdpIpv6InfoInd(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_IPV6_INFO_IND_STRU          *pstPsIpv6InfoInd = VOS_NULL_PTR;
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnEntityAddr = VOS_NULL_PTR;
    VOS_UINT8                           aucIpv6LanAddr[CMMCA_IPV6_ADDR_LEN];
    VOS_UINT8                           ucPdnEntityIndex;

    /* ��ʼ�� */
    pstPsIpv6InfoInd     = (TAF_PS_IPV6_INFO_IND_STRU*)pEvtInfo;

    PS_MEM_SET(aucIpv6LanAddr, 0, CMMCA_IPV6_ADDR_LEN);

    /* Pdn Id��Ч�Լ�� */
    if (!CMMCA_IS_VALID_PDN_ID(pstPsIpv6InfoInd->ucCid))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTafPsEvtPdpIpv6InfoInd: Pdn Id is Invalid!");
        return VOS_ERR;
    }

    /* ���û��Я��ǰ׺��Ϣ����ֱ���˳� */
    if (0 == pstPsIpv6InfoInd->stIpv6RaInfo.ulPrefixNum)
    {
        return VOS_ERR;
    }

    ucPdnEntityIndex     = CMMCA_PKT_FindPdnConnEntityIndex(pstPsIpv6InfoInd->ucCid);

    /* �Ҳ���PDN��Ӧ��ʵ�� */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return VOS_ERR;
    }

    pstPdnEntityAddr = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex);

    /* �����ǰ���Ӵ���CONN״̬�������������� */
    if (CMMCA_CONN_STATUS_CONNED == CMMCA_PKT_GetConnStatus(ucPdnEntityIndex))
    {
        /* ����IPV6 RA INFO*/
        CMMCA_PKT_SaveIpv6RaInfo(&(pstPdnEntityAddr->stPdpInfo), pstPsIpv6InfoInd);
    }

    /* �����ǰ���Ӵ���CONNING״̬�����������ģ���֪ͨ�ϲ���ؼ���ɹ� */
    if (CMMCA_CONN_STATUS_CONNING == CMMCA_PKT_GetConnStatus(ucPdnEntityIndex))
    {
        /* ֹͣ������ʱ�� */
        CMMCA_StopTimer(WUEPS_PID_CMMCA, TI_CMMCA_WAIT_IPV6_RA_INFO);

        /* ����IPV6 RA INFO*/
        CMMCA_PKT_SaveIpv6RaInfo(&(pstPdnEntityAddr->stPdpInfo), pstPsIpv6InfoInd);

        /* ����IPV6ȫ�ֵ�ַ */
        CMMCA_PKT_GenIpv6LanAddrWithRadomIID(pstPsIpv6InfoInd->stIpv6RaInfo.astPrefixList[0].aucPrefix,
                                             pstPsIpv6InfoInd->stIpv6RaInfo.astPrefixList[0].ulBitPrefixLen/8,
                                             aucIpv6LanAddr);

        /* ����IPv6ȫ�ֵ�ַ */
        PS_MEM_CPY(pstPdnEntityAddr->stPdpInfo.stPdpAddr.aucIpV6Addr, aucIpv6LanAddr, TAF_IPV6_ADDR_LEN);

        /* ����״̬ΪCONN */
        CMMCA_PKT_SetConnStatus(ucPdnEntityIndex, CMMCA_CONN_STATUS_CONNED);

        /* ֪ͨ�ϲ���ؼ���ɹ� */
        CMMCA_PKT_SndDefaultBearConnRsp(pstPsIpv6InfoInd->ucCid,
                                        CMMCA_RAT_MMC_BEAR_CONN_RESULT_SUCC,
                                        CMMCA_RAT_MMC_PKT_ERRCODE_NOERROR);
    }

    return VOS_OK;
}
VOS_VOID CMMCA_PKT_RcvTafPsEvt(
    TAF_PS_EVT_STRU                    *pstEvt
)
{
    CMMCA_PKT_PS_EVT_FUNC               pPsEvtFunc = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRslt;

    /* ���g_astCmmcaPktPsEvtFuncTbl */
    for (ulIndex = 0; ulIndex < g_ulCmmcaPktPsEvtFuncTblSize; ulIndex++)
    {
        if (pstEvt->ulEvtId == g_astCmmcaPktPsEvtFuncTbl[ulIndex].ulEvtId)
        {
            pPsEvtFunc = g_astCmmcaPktPsEvtFuncTbl[ulIndex].pPsEvtFunc;

            break;
        }
    }

    if (VOS_NULL_PTR == pPsEvtFunc)
    {
        CMMCA_ERROR_LOG("CMMCA_PKT_RcvTafPsEvt: Not find msg proc func");
        return;
    }
    else
    {
        ulRslt = pPsEvtFunc(pstEvt->aucContent);

        if (VOS_OK != ulRslt)
        {
            CMMCA_ERROR_LOG("CMMCA_PKT_RcvTafPsEvt: msg proc func fail");
        }
    }

    return;
}
VOS_VOID CMMCA_PKT_RcvTiWaitIpv6RaExp(
    REL_TIMER_MSG                      *pstTiMsg
)
{
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucPdnEntityIndex;
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnConnEntity = VOS_NULL_PTR;

    ucPdnId = (VOS_UINT8)pstTiMsg->ulPara;

    /* Pdn Id��Ч�Լ�� */
    if (!CMMCA_IS_VALID_PDN_ID(ucPdnId))
    {
        CMMCA_WARNING_LOG("CMMCA_PKT_RcvTiWaitIpv6RaExp: Pdn Id is Invalid!");
        return;
    }

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(ucPdnId);

    /* ��Ӧ��ʵ�岻���� */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return;
    }

    /* ��ǰ����CONNING״̬����ֱ���˳� */
    if (CMMCA_CONN_STATUS_CONNING != CMMCA_PKT_GetConnStatus(ucPdnEntityIndex))
    {
        return;
    }

    pstPdnConnEntity = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex);

    if (VOS_TRUE != pstPdnConnEntity->stPdpInfo.bitOpPdpAddr)
    {
        return;
    }

    /* �����IPV6 ONLY, ��Ҫ����Ӧ�ĳ���ȥ���Ȼ����ϲ��ϱ�RSP(FAIL, ERRCODE(CMMCA_RAT_MMC_PKT_ERRCODE_WATI_IPV6_RA_EXP)) */
    if (CMMCA_IP_TYPE_IPV6 == pstPdnConnEntity->stPdpInfo.stPdpAddr.enIpType)
    {
        if (VOS_OK == TAF_PS_CallEnd(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, ucPdnId))
        {
            /* ��������״̬ΪINTERNAL DISCING */
            CMMCA_PKT_SetConnStatus(ucPdnEntityIndex, CMMCA_CONN_STATUS_INTERNAL_DISCING);
        }
        else
        {
            CMMCA_ERROR_LOG("CMMCA_PKT_RcvTiWaitIpv6RaExp: End call fail");
        }
    }

    /* �����IPV4V6, ���ϲ��ϱ�RSP(SUCC, ERRCODE(CMMCA_RAT_MMC_PKT_ERRCODE_WATI_IPV6_RA_EXP)) */
    if (CMMCA_IP_TYPE_IPV4V6 == pstPdnConnEntity->stPdpInfo.stPdpAddr.enIpType)
    {
        /* ��RSP�ɹ�����ԭ��ֵ��RA��ʱ */
        CMMCA_PKT_SndDefaultBearConnRsp(ucPdnId,
                                        CMMCA_RAT_MMC_BEAR_CONN_RESULT_SUCC,
                                        CMMCA_RAT_MMC_PKT_ERRCODE_WATI_IPV6_RA_EXP);

        /* ��������״̬ΪCONN */
        CMMCA_PKT_SetConnStatus(ucPdnEntityIndex, CMMCA_CONN_STATUS_CONNED);
    }

    return;
}


VOS_VOID CMMCA_PKT_ProcIpv4ActCnf(
    VOS_UINT8                           ucPdnEntityIndex,
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf
)
{
    /* ��������״̬ΪCONN */
    CMMCA_PKT_SetConnStatus(ucPdnEntityIndex, CMMCA_CONN_STATUS_CONNED);

    /* ���ϲ�ظ�RSP(SUCC) */
    CMMCA_PKT_SndDefaultBearConnRsp(pstPdpActivateCnf->ucCid,
                                    CMMCA_RAT_MMC_BEAR_CONN_RESULT_SUCC,
                                    CMMCA_RAT_MMC_PKT_ERRCODE_NOERROR);

    return;
}


VOS_VOID CMMCA_PKT_ProcIpv6ActCnf(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf
)
{
    /* ������ȡRA�ı�����ʱ������ȡ��RA���������״̬�����ϲ�ظ�RSP */
    CMMCA_StartTimer(WUEPS_PID_CMMCA,
                     TI_CMMCA_WAIT_IPV6_RA_INFO,
                     TI_CMMCA_WAIT_IPV6_RA_INFO_LEN,
                     pstPdpActivateCnf->ucCid);

    return;
}
VOS_VOID CMMCA_PKT_ProcIpv4v6ActCnf(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstPdpActivateCnf
)
{
    /* ������ȡRA�ı�����ʱ������ȡ��RA���������״̬�����ϲ�ظ�RSP */
    CMMCA_StartTimer(WUEPS_PID_CMMCA,
                     TI_CMMCA_WAIT_IPV6_RA_INFO,
                     TI_CMMCA_WAIT_IPV6_RA_INFO_LEN,
                     pstPdpActivateCnf->ucCid);

    return;
}
VOS_VOID CMMCA_PKT_BuildPrimPdpContextInfo(
    CMMCA_PDN_INFO_STRU               *pstPdnInfo,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU     *pstPdpCtxInfo
)
{
    /* ���CID */
    pstPdpCtxInfo->ucCid     = pstPdnInfo->ucPdnId;

    /* �������ֻ��PDNid��PDN TYPE��APN��Ϊ�գ���ɾ������ */
    if ((0 == pstPdnInfo->ucApnLen)
     && (0 == pstPdnInfo->enPdnType))
    {
        pstPdpCtxInfo->ucDefined = VOS_FALSE;
    }
    else
    {
        pstPdpCtxInfo->ucDefined = VOS_TRUE;

        /* PDN TYPE */
        if (CMMCA_IS_VALID_PDN_TYPE(pstPdnInfo->enPdnType))
        {
            pstPdpCtxInfo->bitOpPdpType = VOS_TRUE;
            pstPdpCtxInfo->enPdpType    = pstPdnInfo->enPdnType;
        }

        /* APN */
        if (0 != pstPdnInfo->ucApnLen)
        {
            pstPdpCtxInfo->bitOpApn = VOS_TRUE;
            PS_MEM_CPY(pstPdpCtxInfo->aucApn, pstPdnInfo->aucApn, pstPdnInfo->ucApnLen);
        }
    }

    return;
}


VOS_VOID CMMCA_PKT_FillDefaultBearConnSuccPara(
    VOS_UINT8                                   ucPdnEntityIndex,
    CMMCA_RAT_MMC_PKT_ERRCODE_UINT8             enErrCode,
    CMMCA_RAT_MMC_DEFAULT_BEAR_CONN_CNF_STRU   *pstDefaultBearConnCnf
)
{
    VOS_UINT8                           ucRabId;
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnConnEntity = VOS_NULL_PTR;

    pstPdnConnEntity = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex);

    ucRabId = pstPdnConnEntity->stPdpInfo.ucRabId;

    /* Bear Id */
    pstDefaultBearConnCnf->ucBearerId   = 0xF0 | ucRabId;

    /* Addr */
    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.bitOpPdpAddr)
    {
        pstDefaultBearConnCnf->enPdnType    = pstPdnConnEntity->stPdpInfo.stPdpAddr.enIpType;

        PS_MEM_CPY(pstDefaultBearConnCnf->aucIpv4Addr,
                   pstPdnConnEntity->stPdpInfo.stPdpAddr.aucIpV4Addr,
                   CMMCA_IPV4_ADDR_LEN);

        PS_MEM_CPY(pstDefaultBearConnCnf->aucIpv6Addr,
                   pstPdnConnEntity->stPdpInfo.stPdpAddr.aucIpV6Addr,
                   CMMCA_IPV6_ADDR_LEN);

        /* IPV4V6��RA��ʱʱ��Ҫ���⴦��*/
        if (CMMCA_IP_TYPE_IPV4V6 == pstPdnConnEntity->stPdpInfo.stPdpAddr.enIpType)
        {
            if (CMMCA_RAT_MMC_PKT_ERRCODE_WATI_IPV6_RA_EXP == enErrCode)
            {
                pstDefaultBearConnCnf->enPdnType = CMMCA_IP_TYPE_IPV4;

                PS_MEM_SET(pstDefaultBearConnCnf->aucIpv6Addr, 0, CMMCA_IPV6_ADDR_LEN);
            }
        }
    }

    /* IPV4 DNS */
    pstDefaultBearConnCnf->ucDns4Num = 0;

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv4Dns.bitOpPriDns)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucDns4Addr[pstDefaultBearConnCnf->ucDns4Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv4Dns.aucPriDns,
                   CMMCA_IPV4_ADDR_LEN);

        pstDefaultBearConnCnf->ucDns4Num++;
    }

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv4Dns.bitOpSecDns)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucDns4Addr[pstDefaultBearConnCnf->ucDns4Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv4Dns.aucSecDns,
                   CMMCA_IPV4_ADDR_LEN);

        pstDefaultBearConnCnf->ucDns4Num++;
    }

    /* IPV4 PCSCF*/
    pstDefaultBearConnCnf->ucPcscf4Num = 0;

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv4Pcscf.bitOpPrimPcscfAddr)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucPcscf4Addr[pstDefaultBearConnCnf->ucPcscf4Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv4Pcscf.aucPrimPcscfAddr,
                   CMMCA_IPV4_ADDR_LEN);

        pstDefaultBearConnCnf->ucPcscf4Num++;
    }

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv4Pcscf.bitOpSecPcscfAddr)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucPcscf4Addr[pstDefaultBearConnCnf->ucPcscf4Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv6Pcscf.aucSecPcscfAddr,
                   CMMCA_IPV4_ADDR_LEN);

        pstDefaultBearConnCnf->ucPcscf4Num++;
    }

    /* Gate Way */
    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpGateWay.bitOpGateWayAddr)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucRouteAddr,
                   pstPdnConnEntity->stPdpInfo.stPdpGateWay.aucGateWayAddr,
                   CMMCA_IPV4_ADDR_LEN);
    }

    /* IPV6 DNS */
    pstDefaultBearConnCnf->ucDns6Num = 0;

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv6Dns.bitOpPriDns)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucDns6Addr[pstDefaultBearConnCnf->ucDns6Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv6Dns.aucPriDns,
                   CMMCA_IPV6_ADDR_LEN);

        pstDefaultBearConnCnf->ucDns6Num++;
    }

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv6Dns.bitOpSecDns)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucDns6Addr[pstDefaultBearConnCnf->ucDns6Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv6Dns.aucSecDns,
                   CMMCA_IPV6_ADDR_LEN);

        pstDefaultBearConnCnf->ucDns6Num++;
    }

    /* IPV6 PCSCF*/
    pstDefaultBearConnCnf->ucPcscf6Num = 0;

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv6Pcscf.bitOpPrimPcscfAddr)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucPcscf6Addr[pstDefaultBearConnCnf->ucPcscf6Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv6Pcscf.aucPrimPcscfAddr,
                   CMMCA_IPV6_ADDR_LEN);

        pstDefaultBearConnCnf->ucPcscf6Num++;
    }

    if (VOS_TRUE == pstPdnConnEntity->stPdpInfo.stPdpIpv6Pcscf.bitOpSecPcscfAddr)
    {
        PS_MEM_CPY(pstDefaultBearConnCnf->aucPcscf6Addr[pstDefaultBearConnCnf->ucPcscf6Num],
                   pstPdnConnEntity->stPdpInfo.stPdpIpv6Pcscf.aucSecPcscfAddr,
                   CMMCA_IPV6_ADDR_LEN);

        pstDefaultBearConnCnf->ucPcscf6Num++;
    }


    /* Interface Id */
    PS_MEM_CPY(pstDefaultBearConnCnf->aucIp6InterfaceId,
               pstPdnConnEntity->stPdpInfo.aucPdpIpv6IfId,
               CMMCA_IPV6_INTERFACE_ID_BYTE_LEN);

    return;
}
VOS_VOID CMMCA_PKT_BuildDefaultBearConnRsp(
    VOS_UINT8                                   ucPdnId,
    CMMCA_RAT_MMC_BEAR_CONN_RESULT_ENUM_UINT8   enRslt,
    CMMCA_RAT_MMC_PKT_ERRCODE_UINT8             enErrCode,
    CMMCA_RAT_MMC_DEFAULT_BEAR_CONN_CNF_STRU   *pstDefaultBearConnCnf
)
{
    VOS_UINT8                           ucPdnEntityIndex;

    pstDefaultBearConnCnf->ucPdnId             = ucPdnId;

    /* BearIdΪ0xf0 | RabId����ʼ��Ϊ0xf0 */
    pstDefaultBearConnCnf->ucBearerId          = 0xf0;
    pstDefaultBearConnCnf->enRslt              = enRslt;
    pstDefaultBearConnCnf->enErrCode           = enErrCode;
    pstDefaultBearConnCnf->enSelBearerCtrlMode = CMMCA_PDN_SEL_BEARER_CTRL_MODE_NW_AND_UE;

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(ucPdnId);

    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return;
    }

    /* �ɹ���Ҫ�����������*/
    if (CMMCA_RAT_MMC_BEAR_CONN_RESULT_SUCC == enRslt)
    {
        CMMCA_PKT_FillDefaultBearConnSuccPara(ucPdnEntityIndex, enErrCode, pstDefaultBearConnCnf);
    }
    else
    {
        /* ���PDN id��Ӧ��ʵ�������IP��ַ��ʹ�������ı����PDN TYPE������ʹ���ϲ����������� */
        if (VOS_TRUE == CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex)->stPdpInfo.bitOpPdpAddr)
        {
            pstDefaultBearConnCnf->enPdnType = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex)->stPdpInfo.stPdpAddr.enIpType;
        }
        else
        {
            pstDefaultBearConnCnf->enPdnType = CMMCA_PKT_GetUserPdnType(ucPdnEntityIndex);
        }
    }

    return;
}
VOS_VOID CMMCA_PKT_SndSetPdnRsp(
    CMMCA_RAT_MMC_PDN_TAB_SET_RESULT_ENUM_UINT8    enRslt
)
{
    CMMCA_RAT_MMC_SET_PDN_TAB_CNF_STRU  stSetPdnTabCnf;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_SET_PDN_TAB_RSP_LEN);

    if (VOS_NULL_PTR == pucCmdData)
    {
        return;
    }

    PS_MEM_SET(&stSetPdnTabCnf, 0, sizeof(CMMCA_RAT_MMC_SET_PDN_TAB_CNF_STRU));

    stSetPdnTabCnf.enRslt = enRslt;

    /* ����CMMCA_PackSetPdnTabRsp�����PDN���ûظ���Ϣ */
    ulRslt = CMMCA_PackSetPdnTabRsp(&stSetPdnTabCnf, CMMCA_CMD_SET_PDN_TAB_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ����CBPCA_SndDataToCbpca����������cbpca */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_SET_PDN_TAB_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}
VOS_VOID  CMMCA_PKT_SndDefaultBearConnRsp(
    VOS_UINT8                                   ucPdnId,
    CMMCA_RAT_MMC_BEAR_CONN_RESULT_ENUM_UINT8   enRslt,
    CMMCA_RAT_MMC_PKT_ERRCODE_UINT8             enErrCode
)
{
    CMMCA_RAT_MMC_DEFAULT_BEAR_CONN_CNF_STRU    stDefaultBearConnCnf;
    VOS_UINT8                                  *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                                  ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_DEFAULT_BEAR_CONN_RSP_LEN);

    if (VOS_NULL_PTR == pucCmdData)
    {
        return;
    }

    PS_MEM_SET(&stDefaultBearConnCnf, 0, sizeof(CMMCA_RAT_MMC_DEFAULT_BEAR_CONN_CNF_STRU));

    /* ����CMMCA_PKT_BuildDefaultBearConnRsp���켤������ظ��Ĳ��� */
    CMMCA_PKT_BuildDefaultBearConnRsp(ucPdnId, enRslt, enErrCode, &stDefaultBearConnCnf);

    /* ����CMMCA_PackDefaultBearConnRsp�����Ĭ�ϳ��ؼ���ظ���Ϣ */
    ulRslt = CMMCA_PackDefaultBearConnRsp(&stDefaultBearConnCnf, CMMCA_CMD_DEFAULT_BEAR_CONN_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ����CBPCA_SndDataToCbpca����������cbpca */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_DEFAULT_BEAR_CONN_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}


VOS_VOID CMMCA_PKT_SndBearDiscRsp(
    VOS_UINT8                           ucPdnId,
    CMMCA_RAT_MMC_RESULT_ENUM_UINT8     enRslt
)
{
    /* ���� CMMCA_RAT_MMC_BEAR_DISC_CNF_STRU */
    CMMCA_RAT_MMC_BEAR_DISC_CNF_STRU    stBearDiscCnf;
    VOS_UINT8                           ucPdnEntityIndex;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    stBearDiscCnf.ucPdnId    = ucPdnId;
    stBearDiscCnf.enRslt     = enRslt;
    stBearDiscCnf.ucBearerId = 0xf0;

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(ucPdnId);

    /* �����Pdn Idʵ���ѷ��� */
    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID != ucPdnEntityIndex)
    {
        ucRabId = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex)->stPdpInfo.ucRabId;
        stBearDiscCnf.ucBearerId = 0xf0 | ucRabId;
    }

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_BEAR_DISC_RSP_LEN);

    if (VOS_NULL_PTR == pucCmdData)
    {
        return;
    }

    /* ����CMMCA_PackBearDiscRsp�������������Ϣ */
    ulRslt = CMMCA_PackBearDiscRsp(&stBearDiscCnf, CMMCA_CMD_BEAR_DISC_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ����CBPCA_SndDataToCbpca���������ݸ�CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_BEAR_DISC_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}
VOS_VOID CMMCA_PKT_SndBearDiscInd(
    VOS_UINT8                           ucPdnId
)
{
    CMMCA_RAT_MMC_BEAR_DISC_IND_STRU    stBearDiscInd;
    VOS_UINT8                           ucPdnEntityIndex;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    ucPdnEntityIndex = CMMCA_PKT_FindPdnConnEntityIndex(ucPdnId);

    if (CMMCA_PDN_CONN_ENTITY_INDEX_INVALID == ucPdnEntityIndex)
    {
        return;
    }

    ucRabId = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex)->stPdpInfo.ucRabId;

    /* ����CMMCA_RAT_MMC_BEAR_DISC_IND_STRU */
    stBearDiscInd.ucPdnId    = ucPdnId;
    stBearDiscInd.ucBearerId = 0xf0 | ucRabId;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_BEAR_DISC_IND_LEN);

    if (VOS_NULL_PTR == pucCmdData)
    {
        return;
    }

    /* ����CMMCA_PackBearDiscInd�������������Ϣ */
    ulRslt = CMMCA_PackBearDiscInd(&stBearDiscInd, CMMCA_CMD_BEAR_DISC_IND_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ����CBPCA_SndDataToCbpca���������ݸ�CPBCA */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_BEAR_DISC_IND_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}


VOS_UINT32 CMMCA_PKT_FindSelSdfPara(
    VOS_UINT8                           ucPdnId,
    VOS_UINT32                          ulSdfNum,
    TAF_SDF_PARA_STRU                  *pstSdfPara,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          i;

    if (0 == ulSdfNum)
    {
        return VOS_ERR;
    }

    for (i = 0; i < ulSdfNum; i++)
    {
        if (ucPdnId != pstSdfPara[i].ucCid)
        {
            continue;
        }

        /* PDN TYPE */
        if (VOS_TRUE != pstSdfPara[i].bitOpPdnType)
        {
            continue;
        }

        if ((pstSdfPara[i].enPdnType < TAF_PDP_IPV4)
         || (pstSdfPara[i].enPdnType > TAF_PDP_IPV4V6))
        {
            continue;
        }

        /* APN */
        if (VOS_TRUE != pstSdfPara[i].bitOpApn)
        {
            continue;
        }

        *pulIndex = i;

        return VOS_OK;
    }

    return VOS_ERR;
}


VOS_VOID CMMCA_PKT_SaveSelSdfPara(
    VOS_UINT8                           ucPdnEntityIndex,
    TAF_SDF_PARA_STRU                  *pstSdfPara
)
{
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnConnEntity = VOS_NULL_PTR;

    pstPdnConnEntity = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex);

    PS_MEM_SET(&(pstPdnConnEntity->stSelSdfPara), 0x0, sizeof(CMMCA_SEL_SDF_PARA_STRU));

    /* Cid */
    pstPdnConnEntity->stSelSdfPara.ucCid                    = pstSdfPara->ucCid;

    /* Linked Cid */
    pstPdnConnEntity->stSelSdfPara.bitOpLinkdCid            = pstSdfPara->bitOpLinkdCid;
    pstPdnConnEntity->stSelSdfPara.ucLinkdCid               = pstSdfPara->ucLinkdCid;

    /* Pdn Type */
    pstPdnConnEntity->stSelSdfPara.bitOpPdnType             = pstSdfPara->bitOpPdnType;
    pstPdnConnEntity->stSelSdfPara.enPdnType                = pstSdfPara->enPdnType;

    /* Apn */
    pstPdnConnEntity->stSelSdfPara.bitOpApn = pstSdfPara->bitOpApn;
    PS_MEM_CPY(&(pstPdnConnEntity->stSelSdfPara.stApnInfo),
               &pstSdfPara->stApnInfo,
               sizeof(TAF_PDP_APN_STRU));

    /* Auth */
    pstPdnConnEntity->stSelSdfPara.bitOpGwAuthInfo = pstSdfPara->bitOpGwAuthInfo;
    PS_MEM_CPY(&(pstPdnConnEntity->stSelSdfPara.stGwAuthInfo),
               &pstSdfPara->stGwAuthInfo,
               sizeof(TAF_GW_AUTH_STRU));

    return;
}
VOS_UINT32 CMMCA_PKT_ProcSdfPara(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                           ucPdnEntityIndex
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulSelSdfIndex;
    TAF_SDF_PARA_QUERY_INFO_STRU       *pstSdfQueryInfo = VOS_NULL_PTR;

    pstSdfQueryInfo = (TAF_SDF_PARA_QUERY_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));

    if (VOS_NULL_PTR == pstSdfQueryInfo)
    {
        return VOS_ERR;
    }

    PS_MEM_SET(pstSdfQueryInfo, 0x0, sizeof(TAF_SDF_PARA_QUERY_INFO_STRU));

    /* ����API�ӿ�TAF_PS_GetCidSdfParaInfo��ȡ����NV���е�SDF������Ϣ */
    ulRslt = TAF_PS_GetCidSdfParaInfo(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, 0, pstSdfQueryInfo);
    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pstSdfQueryInfo);

        return VOS_ERR;
    }

    /* �ӻ�ȡ���б���ѡ���Ӧ��SDF���� */
    ulSelSdfIndex = 0;

    ulRslt = CMMCA_PKT_FindSelSdfPara(ucPdnId,
                                      pstSdfQueryInfo->ulSdfNum,
                                      pstSdfQueryInfo->astSdfPara,
                                      &ulSelSdfIndex);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pstSdfQueryInfo);

        return VOS_ERR;
    }

    /* �洢ѡ���SDF���� */
    CMMCA_PKT_SaveSelSdfPara(ucPdnEntityIndex, &(pstSdfQueryInfo->astSdfPara[ulSelSdfIndex]));

    PS_MEM_FREE(WUEPS_PID_CMMCA, pstSdfQueryInfo);

    return VOS_OK;
}
VOS_VOID CMMCA_PKT_GetDialParaFromSdfPara(
    VOS_UINT8                           ucPdnEntityIndex,
    TAF_PS_DIAL_PARA_STRU              *pstDialPara
)
{
    CMMCA_PDN_CONN_ENTITY_STRU         *pstPdnConnEntity = VOS_NULL_PTR;

    PS_MEM_SET(pstDialPara, 0, sizeof(TAF_PS_DIAL_PARA_STRU));

    pstPdnConnEntity = CMMCA_PKT_GetPdnEntityAddr(ucPdnEntityIndex);

    pstDialPara->ucCid                  = pstPdnConnEntity->stSelSdfPara.ucCid;
    pstDialPara->enPdpType              = pstPdnConnEntity->stSelSdfPara.enPdnType;

    /* ��ֵAPN��Ϣ */
    if (VOS_TRUE == pstPdnConnEntity->stSelSdfPara.bitOpApn)
    {
        pstDialPara->bitOpApn = VOS_TRUE;

        /* ����APN����û�г����ֶΣ�����Ϊ���ַ�����ʽ�����ڽ�β����'\0' */
        PS_MEM_CPY(pstDialPara->aucApn,
                   pstPdnConnEntity->stSelSdfPara.stApnInfo.aucValue,
                   pstPdnConnEntity->stSelSdfPara.stApnInfo.ucLength);
    }

    /* ��ֵ��Ȩ���� */
    if (VOS_TRUE == pstPdnConnEntity->stSelSdfPara.bitOpGwAuthInfo)
    {
        pstDialPara->bitOpAuthType      = VOS_TRUE;
        pstDialPara->enAuthType         = pstPdnConnEntity->stSelSdfPara.stGwAuthInfo.enAuthType;

        if (0 != pstPdnConnEntity->stSelSdfPara.stGwAuthInfo.ucUserNameLen)
        {
            pstDialPara->bitOpUserName  = VOS_TRUE;

            /* �����û�������û�г����ֶΣ�����Ϊ���ַ�����ʽ�����ڽ�β����'\0' */
            PS_MEM_CPY(pstDialPara->aucUserName,
                       pstPdnConnEntity->stSelSdfPara.stGwAuthInfo.aucUserName,
                       pstPdnConnEntity->stSelSdfPara.stGwAuthInfo.ucUserNameLen);
        }

        if (0 != pstPdnConnEntity->stSelSdfPara.stGwAuthInfo.ucPwdLen)
        {
            pstDialPara->bitOpPassWord  = VOS_TRUE;

            /* �����������û�г����ֶΣ�����Ϊ���ַ�����ʽ�����ڽ�β����'\0' */
            PS_MEM_CPY(pstDialPara->aucPassWord,
                       pstPdnConnEntity->stSelSdfPara.stGwAuthInfo.aucPwd,
                       pstPdnConnEntity->stSelSdfPara.stGwAuthInfo.ucPwdLen);
        }
    }

    return;
}
VOS_VOID CMMCA_PKT_GenIpv6LanAddrWithRadomIID(
    VOS_UINT8                          *pucPrefix,
    VOS_UINT32                          ulPrefixByteLen,
    VOS_UINT8                          *pucIpv6LanAddr
)
{
    VOS_UINT32                         *paulAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulTick;

    paulAddr = (VOS_UINT32 *)pucIpv6LanAddr;

    if (ulPrefixByteLen > CMMCA_IPV6_PREFIX_BYTE_LEN)
    {
        CMMCA_ERROR_LOG("CMMCA_PKT_GenIpv6LanAddrWithRadomIID: Prefix Len > 8");
        return;
    }

    /* ����IPv6��ַǰ׺ */
    PS_MEM_CPY(pucIpv6LanAddr, pucPrefix, ulPrefixByteLen);

    ulTick = VOS_GetTick();

    /* �ڽ���PC����ʱ����ʹ�����ֵ */
#if (VOS_WIN32 == VOS_OS_VER)
    paulAddr[2] = 0xFFFFFFFF;

    paulAddr[3] = 0xFFFFFFFF;

#else
    VOS_SetSeed(ulTick);
    paulAddr[2] = VOS_Rand(0xFFFFFFFF);

    VOS_SetSeed(ulTick + 10);
    paulAddr[3] = VOS_Rand(0xFFFFFFFF);

#endif

    *(VOS_UINT8 *)(&paulAddr[2]) &= ~0x02;

    return;
}


CMMCA_RAT_MMC_PKT_ERRCODE_UINT8 CMMCA_PKT_TransferErrCode(
    TAF_PS_CAUSE_ENUM_UINT32            enCause
)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < g_ulCmmcaErrCodeMapTblSize; ulIndex++)
    {
        if (enCause == g_astCmmcaErrCodeMapTbl[ulIndex].enCause)
        {
            return g_astCmmcaErrCodeMapTbl[ulIndex].enErrCode;
        }
    }

    return CMMCA_RAT_MMC_PKT_ERRCODE_UNKNOWN;
}


VOS_VOID CMMCA_PKT_SndSetPdnPcoAuthRsp(
    CMMCA_SET_PDN_PCO_AUTH_RESULT_ENUM_UINT8        enRslt
)
{
    VOS_UINT8                          *pucCmdData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pucCmdData = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, CMMCA_CMD_SET_PND_PCO_AUTH_RSP_LEN);
    if (VOS_NULL_PTR == pucCmdData)
    {
        return;
    }

    /* ����CMMCA_PackSetPdnTabRsp�����PDN���ûظ���Ϣ */
    ulRslt = CMMCA_PackSetPdnPcoAuthRsp(enRslt, CMMCA_CMD_SET_PND_PCO_AUTH_RSP_LEN, pucCmdData);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ����CBPCA_SndDataToCbpca����������cbpca */
    ulRslt = CBPCA_SndDataToCbpca(WUEPS_PID_CMMCA, CMMCA_CBPCA_DATA_REQ, pucCmdData, CMMCA_CMD_SET_PND_PCO_AUTH_RSP_LEN);

    if (VOS_OK != ulRslt)
    {
        PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

        return;
    }

    /* ��Ϣ���ͽ������ͷ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_CMMCA, pucCmdData);

    return;
}
VOS_UINT32 CMMCA_PKT_RcvTafSetPdnPcoAuthCnf(
    VOS_VOID                           *pEvtInfo
)
{
    TAF_PS_SET_AUTHDATA_INFO_CNF_STRU  *pstSetPdnPcoAuthCnf = VOS_NULL_PTR;

    pstSetPdnPcoAuthCnf  = (TAF_PS_SET_AUTHDATA_INFO_CNF_STRU*)pEvtInfo;

    if (TAF_PS_CAUSE_SUCCESS == pstSetPdnPcoAuthCnf->enCause)
    {
        CMMCA_PKT_SndSetPdnPcoAuthRsp(CMMCA_SET_PDN_PCO_AUTH_RESULT_SUCC);
    }
    else
    {
        CMMCA_PKT_SndSetPdnPcoAuthRsp(CMMCA_SET_PDN_PCO_AUTH_RESULT_FAIL);
    }

    return VOS_OK;
}


VOS_VOID CMMCA_PKT_RcvCmmcSetPdnPcoAuthReq(
    VOS_VOID                           *pMsg
)
{
    CBPCA_DATA_IND_MSG_STRU                *pstDataInd      = VOS_NULL_PTR;
    TAF_AUTHDATA_EXT_STRU                   stAuthdataExt;
    VOS_UINT32                              ulRslt;
    VOS_UINT8                               ucOpid;

    /* ��ʼ�� */
    PS_MEM_SET(&stAuthdataExt, 0x0, sizeof(TAF_AUTHDATA_EXT_STRU));

    /* �ο�VIA�ӿ��ĵ���������Ϣ */
    pstDataInd      = (CBPCA_DATA_IND_MSG_STRU *)pMsg;

    /* ����������ת�� */
    ulRslt = CMMCA_ParseSetPdnPcoAuthReq((VOS_UINT16)(pstDataInd->ulDataLen),
                                         pstDataInd->aucData,
                                         &stAuthdataExt);
    if (VOS_ERR == ulRslt)
    {
        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_PKT_SndSetPdnPcoAuthRsp(CMMCA_SET_PDN_PCO_AUTH_RESULT_FAIL);
        return;
    }

    /* ����OPID */
    ucOpid = 0x0;
    CMMCA_AssignOpid(&ucOpid);

    /* ����APS�ĺ���������Ϣ */
    ulRslt = TAF_PS_SetAuthDataInfo(WUEPS_PID_CMMCA, CMMCA_CLIENT_ID, ucOpid, &stAuthdataExt);
    if (VOS_OK != ulRslt)
    {
        /* ֱ�ӻ�RSP(FAIL) */
        CMMCA_PKT_SndSetPdnPcoAuthRsp(CMMCA_SET_PDN_PCO_AUTH_RESULT_FAIL);
        return;
    }

    return;
}



#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

