

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"
#include    "NasLmmPubMOm.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMNWMSGDECODE_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMNWMSGDECODE_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
NAS_ESM_MSG_IE_STRU                     g_ActDefltEpsbReq[] = {
{NAS_ESM_MSG_EPS_QOS_IEI,    0x00, NAS_MSG_FORMAT_LV,  1, 2, 14, NAS_ESM_DecodeNwSdfQosValue   },
{NAS_ESM_MSG_APN_IEI,        0x00, NAS_MSG_FORMAT_LV,  1, 2, 101,NAS_ESM_DecodeNwAPNValue      },
{NAS_ESM_MSG_PDN_IEI,        0x00, NAS_MSG_FORMAT_LV,  1, 6, 14, NAS_ESM_DecodeNwPDNValue      },
{NAS_ESM_MSG_TI_IEI,         0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 4 , NAS_ESM_DecodeTransactionId   },
{NAS_ESM_MSG_NQOS_IEI,       0xFF, NAS_MSG_FORMAT_TLV, 2, 14,22, NAS_ESM_DecodeNegotiatedQos   },
{NAS_ESM_MSG_NLS_IEI,        0xFF, NAS_MSG_FORMAT_TV,  1, 2, 2,  NAS_ESM_DecodeLlcSapi         },
{NAS_ESM_MSG_RADIO_PRIO_IEI, 0xF0, NAS_MSG_FORMAT_TV,  1, 1, 1,  NAS_ESM_DecodeRadioPriority   },
{NAS_ESM_MSG_PFI_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 3,  NAS_ESM_DecodePacketFlowId    },
{NAS_ESM_MSG_APN_AMBR_IEI,   0xFF, NAS_MSG_FORMAT_TLV, 2, 4, 8,  NAS_ESM_DecodeNwApnAmbrValue  },
{NAS_ESM_MSG_ESM_CAU_IEI,    0xFF, NAS_MSG_FORMAT_TV,  1, 2, 2,  NAS_ESM_DecodeEsmCause        },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,NAS_ESM_DecodeNwPco           }
};
#define  ACT_DEFLT_EPSB_REQ_MSG_IE_NUM  (sizeof(g_ActDefltEpsbReq)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_ActDedictEpsbReq[] = {
{NAS_ESM_MSG_EPS_QOS_IEI,    0x00, NAS_MSG_FORMAT_LV,  1, 2, 14, NAS_ESM_DecodeNwSdfQosValue   },
{NAS_ESM_MSG_TFT_IEI,        0xFF, NAS_MSG_FORMAT_LV,  1, 2, 256,NAS_ESM_DecodeNwTftValue      },
{NAS_ESM_MSG_TI_IEI,         0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 4,  NAS_ESM_DecodeTransactionId   },
{NAS_ESM_MSG_NQOS_IEI,       0xFF, NAS_MSG_FORMAT_TLV, 2,14, 22, NAS_ESM_DecodeNegotiatedQos   },
{NAS_ESM_MSG_NLS_IEI,        0xFF, NAS_MSG_FORMAT_TV,  1, 2, 2,  NAS_ESM_DecodeLlcSapi         },
{NAS_ESM_MSG_RADIO_PRIO_IEI, 0xF0, NAS_MSG_FORMAT_TV,  1, 1, 1,  NAS_ESM_DecodeRadioPriority   },
{NAS_ESM_MSG_PFI_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 3,  NAS_ESM_DecodePacketFlowId    },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,VOS_NULL_PTR                  }
};
#define  ACT_DEDICT_EPSB_REQ_MSG_IE_NUM (sizeof(g_ActDedictEpsbReq)/sizeof(NAS_ESM_MSG_IE_STRU))


NAS_ESM_MSG_IE_STRU                     g_ModEpsbReq[] = {
{NAS_ESM_MSG_EPS_QOS_IEI,    0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 15, NAS_ESM_DecodeNwSdfQosValue   },
{NAS_ESM_MSG_TFT_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 257,NAS_ESM_DecodeNwTftValue      },
{NAS_ESM_MSG_NQOS_IEI,       0xFF, NAS_MSG_FORMAT_TLV, 2,14, 22, NAS_ESM_DecodeNegotiatedQos   },
{NAS_ESM_MSG_NLS_IEI,        0xFF, NAS_MSG_FORMAT_TV,  1, 2, 2,  NAS_ESM_DecodeLlcSapi         },
{NAS_ESM_MSG_RADIO_PRIO_IEI, 0xF0, NAS_MSG_FORMAT_TV,  1, 1, 1,  NAS_ESM_DecodeRadioPriority   },
{NAS_ESM_MSG_PFI_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 3,  NAS_ESM_DecodePacketFlowId    },
{NAS_ESM_MSG_APN_AMBR_IEI,   0xFF, NAS_MSG_FORMAT_TLV, 2, 4, 8,  NAS_ESM_DecodeNwApnAmbrValue  },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,NAS_ESM_DecodeNwPco           }
};
#define  MOD_EPSB_REQ_MSG_IE_NUM (sizeof(g_ModEpsbReq)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_BearerResAllocRej[] = {
{NAS_ESM_MSG_ESM_CAU_IEI,    0x00, NAS_MSG_FORMAT_V,   0, 1, 1,  NAS_ESM_DecodeEsmCause        },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,VOS_NULL_PTR        }
};
#define  BEARER_RES_ALLOC_REJ_MSG_IE_NUM (sizeof(g_BearerResAllocRej)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_BearerResModRej[] = {
{NAS_ESM_MSG_ESM_CAU_IEI,    0x00, NAS_MSG_FORMAT_V,   0, 1, 1,  NAS_ESM_DecodeEsmCause        },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,VOS_NULL_PTR        }
};
#define  BEARER_RES_MOD_REJ_MSG_IE_NUM (sizeof(g_BearerResModRej)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_DeactEpsbReq[] = {
{NAS_ESM_MSG_ESM_CAU_IEI,    0x00, NAS_MSG_FORMAT_V,   0, 1, 1,  NAS_ESM_DecodeEsmCause        },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,VOS_NULL_PTR        }
};
#define  DEACT_EPSB_REQ_MSG_IE_NUM  (sizeof(g_DeactEpsbReq)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_PdnConRej[] = {
{NAS_ESM_MSG_ESM_CAU_IEI,    0x00, NAS_MSG_FORMAT_V,   0, 1, 1,  NAS_ESM_DecodeEsmCause        },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,VOS_NULL_PTR        }
};
#define  PDN_CON_REJ_MSG_IE_NUM  (sizeof(g_PdnConRej)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_PdnDisConRej[] = {
{NAS_ESM_MSG_ESM_CAU_IEI,    0x00, NAS_MSG_FORMAT_V,   0, 1, 1,  NAS_ESM_DecodeEsmCause        },
{NAS_ESM_MSG_PCO_IEI,        0xFF, NAS_MSG_FORMAT_TLV, 2, 3, 253,VOS_NULL_PTR        }
};
#define  PDN_DISCON_REJ_MSG_IE_NUM (sizeof(g_PdnDisConRej)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_EsmStatus[] = {
{NAS_ESM_MSG_ESM_CAU_IEI,    0x00, NAS_MSG_FORMAT_V,   0, 1, 1,  NAS_ESM_DecodeEsmCause        }
};
#define  ESM_STATUS_MSG_IE_NUM  (sizeof(g_EsmStatus)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_MSG_IE_STRU                     g_EsmNotification[] = {
{NAS_ESM_MSG_NI_IEI,         0x00, NAS_MSG_FORMAT_LV,  1, 2, 2,  NAS_ESM_DecodeNotificationIndicator}
};
#define  ESM_NOTIFICATION_MSG_IE_NUM  (sizeof(g_EsmNotification)/sizeof(NAS_ESM_MSG_IE_STRU))

NAS_ESM_DECODE_TABLE_STRU               g_EsmDecodeTable[] = {
{NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_REQ,  0, ESM_ACT_DEFLT_EPS_BEARER_CNTXT_REQ,
 ACT_DEFLT_EPSB_REQ_MSG_IE_NUM,                      g_ActDefltEpsbReq                      },

{NAS_ESMCN_MSG_TYPE_ACT_DEDICTD_EPS_BEARER_CNTXT_REQ,1, ESM_ACT_DEDICT_EPS_BEARER_CNTXT_REQ,
 ACT_DEDICT_EPSB_REQ_MSG_IE_NUM,                     g_ActDedictEpsbReq                     },

{NAS_ESMCN_MSG_TYPE_MOD_EPS_BEARER_CNTXT_REQ,        0, ESM_MOD_EPS_BEARER_CNTXT_REQ,
 MOD_EPSB_REQ_MSG_IE_NUM,                            g_ModEpsbReq                           },

{NAS_ESMCN_MSG_TYPE_DEACT_EPS_BEARER_CNTXT_REQ,      0, ESM_DEACT_EPS_BEARER_CNTXT_REQ,
 DEACT_EPSB_REQ_MSG_IE_NUM,                          g_DeactEpsbReq                         },

{NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REJ,                 0, ESM_PDN_CONNECT_REJ,
 PDN_CON_REJ_MSG_IE_NUM,                             g_PdnConRej                            },

{NAS_ESMCN_MSG_TYPE_PDN_DISCONNECT_REJ,              0, ESM_PDN_DISCONNECT_REJ,
 PDN_DISCON_REJ_MSG_IE_NUM,                          g_PdnDisConRej                         },

{NAS_ESMCN_MSG_TYPE_BEARER_RES_ALLOC_REJ,            0, ESM_BEARER_RESOUCE_ALLOC_REJ,
 BEARER_RES_ALLOC_REJ_MSG_IE_NUM,                    g_BearerResAllocRej                    },

{NAS_ESMCN_MSG_TYPE_BEARER_RES_MOD_REJ,              0, ESM_BEARER_RESOUCE_MOD_REJ,
 BEARER_RES_MOD_REJ_MSG_IE_NUM,                      g_BearerResModRej                      },

{NAS_ESMCN_MSG_TYPE_ESM_INFORMATION_REQ,             0, ESM_INFO_REQ,
 0,                                                  VOS_NULL_PTR                           },

{NAS_ESMCN_MSG_TYPE_ESM_STATUS,                      0, ESM_STUS_MT,
 ESM_STATUS_MSG_IE_NUM,                              g_EsmStatus                            },

{NAS_ESMCN_MSG_TYPE_ESM_NOTIFICATION,                0, ESM_NOTIFICATION_MT,
 ESM_NOTIFICATION_MSG_IE_NUM,                        g_EsmNotification                      }
};

#define g_EsmDecodeTableSize (sizeof(g_EsmDecodeTable)/sizeof(NAS_ESM_DECODE_TABLE_STRU))

NAS_ESM_DECODE_QOSRATE_TABLE_STRU       g_EsmDecodeQosRateTable[] =
{
    {NAS_ESM_QOS_OFFSET_ULMAXRATE,                  NAS_ESM_SdfQosUlMaxRateTran},
    {NAS_ESM_QOS_OFFSET_DLMAXRATE,                  NAS_ESM_SdfQosDlMaxRateTran},
    {NAS_ESM_QOS_OFFSET_ULGMAXRATE,                 NAS_ESM_SdfQosUlGMaxRateTran},
    {NAS_ESM_QOS_OFFSET_DLGMAXRATE,                 NAS_ESM_SdfQosDlGMaxRateTran},
    {NAS_ESM_QOS_OFFSET_ULMAXRATE_EXT,              NAS_ESM_SdfQosUlMaxRateExtTran},
    {NAS_ESM_QOS_OFFSET_DLMAXRATE_EXT,              NAS_ESM_SdfQosDlMaxRateExtTran},
    {NAS_ESM_QOS_OFFSET_ULGMAXRATE_EXT,             NAS_ESM_SdfQosUlGMaxRateExtTran},
    {NAS_ESM_QOS_OFFSET_DLGMAXRATE_EXT,             NAS_ESM_SdfQosDlGMaxRateExtTran},
    {NAS_ESM_QOS_OFFSET_ULMAXRATE_EXT_2,            NAS_ESM_SdfQosUlMaxRateExt2Tran},
    {NAS_ESM_QOS_OFFSET_DLMAXRATE_EXT_2,            NAS_ESM_SdfQosDlMaxRateExt2Tran},
    {NAS_ESM_QOS_OFFSET_ULGMAXRATE_EXT_2,           NAS_ESM_SdfQosUlGMaxRateExt2Tran},
    {NAS_ESM_QOS_OFFSET_DLGMAXRATE_EXT_2,           NAS_ESM_SdfQosDlGMaxRateExt2Tran}
};
#define g_EsmDecodeQosRateTableSize (sizeof(g_EsmDecodeQosRateTable)/sizeof(NAS_ESM_DECODE_QOSRATE_TABLE_STRU))

NAS_ESM_PF_CONPONET_TYPE_LEN_TABLE_STRU       g_EsmPFComponentTypeLenTable[] =
{
    {NAS_ESM_TFT_PF_COP_TYPE_IPV4_ADDR,                   8},
    {NAS_ESM_TFT_PF_COP_TYPE_IPV6_ADDR,                  32},
#if (FEATURE_ON == FEATURE_LTE_NAS_R11)
    {NAS_ESM_TFT_PF_COP_TYPE_IPV4_LOCAL_ADDR,             8},
    {NAS_ESM_TFT_PF_COP_TYPE_IPV6_LOCAL_ADDR,            17},
#endif
    {NAS_ESM_TFT_PF_COP_TYPE_PROTOCOL_ID,                 1},
    {NAS_ESM_TFT_PF_COP_TYPE_SINGLE_LOCAL_PORT,           2},
    {NAS_ESM_TFT_PF_COP_TYPE_LOCAL_PORT_RANGE,            4},
    {NAS_ESM_TFT_PF_COP_TYPE_SINGLE_REMOTE_PORT,          2},
    {NAS_ESM_TFT_PF_COP_TYPE_REMOTE_PORT_RANGE,           4},
    {NAS_ESM_TFT_PF_COP_TYPE_SPI,                         4},
    {NAS_ESM_TFT_PF_COP_TYPE_TOS,                         2},
    {NAS_ESM_TFT_PF_COP_TYPE_FLOW_LABLE,                  3}
};
#define g_EsmPFComponentTypeLenTableSize (sizeof(g_EsmPFComponentTypeLenTable)/sizeof(NAS_ESM_PF_CONPONET_TYPE_LEN_TABLE_STRU))

NAS_ESM_DECODE_ADD_FILTER_TFT_TABLE_STRU  g_EsmDecodeAddFilterTftTable[] =
{
#if (FEATURE_ON == FEATURE_LTE_NAS_R11)
    {NAS_ESM_TFT_PF_COP_TYPE_IPV4_LOCAL_ADDR    , NAS_ESM_TFT_DecodePfCopTypeIpv4LocalAddr    },
    {NAS_ESM_TFT_PF_COP_TYPE_IPV6_LOCAL_ADDR    , NAS_ESM_TFT_DecodePfCopTypeIpv6LocalAddr    },
#endif
    {NAS_ESM_TFT_PF_COP_TYPE_IPV4_ADDR          , NAS_ESM_TFT_DecodePfCopTypeIpv4Addr         },
    {NAS_ESM_TFT_PF_COP_TYPE_IPV6_ADDR          , NAS_ESM_TFT_DecodePfCopTypeIpv6Addr         },
    {NAS_ESM_TFT_PF_COP_TYPE_PROTOCOL_ID        , NAS_ESM_TFT_DecodePfCopTypeProtocolId       },
    {NAS_ESM_TFT_PF_COP_TYPE_SINGLE_LOCAL_PORT  , NAS_ESM_TFT_DecodePfCopTypeSingleLocalPort  },
    {NAS_ESM_TFT_PF_COP_TYPE_LOCAL_PORT_RANGE   , NAS_ESM_TFT_DecodePfCopTypeLocalPortRange   },
    {NAS_ESM_TFT_PF_COP_TYPE_SINGLE_REMOTE_PORT , NAS_ESM_TFT_DecodePfCopTypeSingleRemotePort },
    {NAS_ESM_TFT_PF_COP_TYPE_REMOTE_PORT_RANGE  , NAS_ESM_TFT_DecodePfCopTypeRemotePortRange  },
    {NAS_ESM_TFT_PF_COP_TYPE_SPI                , NAS_ESM_TFT_DecodePfCopTypeSpi              },
    {NAS_ESM_TFT_PF_COP_TYPE_TOS                , NAS_ESM_TFT_DecodePfCopTypeTos              },
    {NAS_ESM_TFT_PF_COP_TYPE_FLOW_LABLE         , NAS_ESM_TFT_DecodePfCopTypeFlowLable        }
};

const VOS_UINT32 g_EsmDecodeAddFilterTftTableSize =
              (sizeof(g_EsmDecodeAddFilterTftTable)/sizeof(NAS_ESM_DECODE_ADD_FILTER_TFT_TABLE_STRU));



#if (VOS_OS_VER == VOS_WIN32)
NAS_ESM_OM_CN_MSG_IE_PRINT_STR_STRU  g_EsmDecodeFailIePrintTable[] =
{
    {NAS_ESM_CN_MSG_PDN_IE              , "NAS_ESM_CN_MSG_PDN_IE"},
    {NAS_ESM_CN_MSG_TFT_IE              , "NAS_ESM_CN_MSG_TFT_IE"},
    {NAS_ESM_CN_MSG_EPS_QOS_IE          , "NAS_ESM_CN_MSG_EPS_QOS_IE"},
    {NAS_ESM_CN_MSG_APN_IE              , "NAS_ESM_CN_MSG_APN_IE"},
    {NAS_ESM_CN_MSG_PCO_IE              , "NAS_ESM_CN_MSG_PCO_IE"},
    {NAS_ESM_CN_MSG_ESM_CAUSE_IE        , "NAS_ESM_CN_MSG_ESM_CAUSE_IE"},
    {NAS_ESM_CN_MSG_NQOS_IE             , "NAS_ESM_CN_MSG_NQOS_IE"},
    {NAS_ESM_CN_MSG_TI_IE               , "NAS_ESM_CN_MSG_TI_IE"},
    {NAS_ESM_CN_MSG_NLS_IE              , "NAS_ESM_CN_MSG_NLS_IE"},
    {NAS_ESM_CN_MSG_PFI_IE              , "NAS_ESM_CN_MSG_PFI_IE"},
    {NAS_ESM_CN_MSG_RADIO_PRIO_IE       , "NAS_ESM_CN_MSG_RADIO_PRIO_IE"},
    {NAS_ESM_CN_MSG_APN_AMBR_IE         , "NAS_ESM_CN_MSG_APN_AMBR_IE"},
    {NAS_ESM_CN_MSG_EPSBID_IE           , "NAS_ESM_CN_MSG_EPSBID_IE"},
    {NAS_ESM_CN_MSG_PTI_IE              , "NAS_ESM_CN_MSG_PTI_IE"},
    {NAS_ESM_CN_MSG_LINKED_EPSBID_IE    , "NAS_ESM_CN_MSG_LINKED_EPSBID_IE"},
    {NAS_ESM_CN_MSG_MSG_TYPE_IE         , "NAS_ESM_CN_MSG_MSG_TYPE_IE"},
    {NAS_ESM_CN_MSG_IE_NOIE             , "NAS_ESM_CN_MSG_IE_NOIE"},
    {NAS_ESM_CN_MSG_MANDAN_IE           , "NAS_ESM_CN_MSG_MANDAN_IE"},
    {NAS_ESM_CN_MSG_OPTION_IE           , "NAS_ESM_CN_MSG_OPTION_IE"}
};

const VOS_UINT32 g_EsmDecodeFailIePrintTableSize =
              (sizeof(g_EsmDecodeFailIePrintTable)/sizeof(NAS_ESM_OM_CN_MSG_IE_PRINT_STR_STRU));

NAS_ESM_OM_DECODE_CN_MSG_FAIL_CAUSE_PRINT_STR_STRU  g_EsmDecodeFailCausePrintTable[] =
{
    {ESM_DECODE_CN_MSG_IE_LEN_INVALID                       , "ESM_DECODE_CN_MSG_IE_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_IE_TYPE_INVALID                      , "ESM_DECODE_CN_MSG_IE_TYPE_INVALID"},
    {ESM_DECODE_CN_MSG_PD_INVALID                           , "ESM_DECODE_CN_MSG_PD_INVALID"},
    {ESM_DECODE_CN_MSG_MSG_TYPE_INVALID                     , "ESM_DECODE_CN_MSG_MSG_TYPE_INVALID"},
    {ESM_DECODE_CN_MSG_NOT_PARA_LIST_ID                     , "ESM_DECODE_CN_MSG_NOT_PARA_LIST_ID"},
    {ESM_DECODE_CN_MSG_TAD_TYPE_INVALID                     , "ESM_DECODE_CN_MSG_TAD_TYPE_INVALID"},
    {ESM_DECODE_CN_MSG_PF_NUM_INVALID                       , "ESM_DECODE_CN_MSG_PF_NUM_INVALID"},
    {ESM_DECODE_CN_MSG_SAME_PF_ID                           , "ESM_DECODE_CN_MSG_SAME_PF_ID"},
    {ESM_DECODE_CN_MSG_SAME_PF_PRECEDENCE                   , "ESM_DECODE_CN_MSG_SAME_PF_PRECEDENCE"},
    {ESM_DECODE_CN_MSG_SIGLE_PORT_AND_PORT_RANGE_COEXIST    , "ESM_DECODE_CN_MSG_SIGLE_PORT_AND_PORT_RANGE_COEXIST"},
    {ESM_DECODE_CN_MSG_IP_LEN_INVALID                       , "ESM_DECODE_CN_MSG_IP_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_BCM_TYPE_INVALID                     , "ESM_DECODE_CN_MSG_BCM_TYPE_INVALID"},
    {ESM_DECODE_CN_MSG_PCO_CONFIG_PROTOCOL_INVALID          , "ESM_DECODE_CN_MSG_PCO_CONFIG_PROTOCOL_INVALID"},
    {ESM_DECODE_CN_MSG_IP_TYPE_INVALID                      , "ESM_DECODE_CN_MSG_IP_TYPE_INVALID"},
    {ESM_DECODE_CN_MSG_QOS_RATE_0                           , "ESM_DECODE_CN_MSG_QOS_RATE_0"},
    {ESM_DECODE_CN_MSG_PF_ITEM_TYPE_INVALID                 , "ESM_DECODE_CN_MSG_PF_ITEM_TYPE_INVALID"},
    {ESM_DECODE_CN_MSG_APN_CHARACTER_INVALID                , "ESM_DECODE_CN_MSG_APN_CHARACTER_INVALID"},
    {ESM_DECODE_CN_MSG_PARA_LIST_ID_INVALID                 , "ESM_DECODE_CN_MSG_PARA_LIST_ID_INVALID"},
    {ESM_DECODE_CN_MSG_IPV4_LEN_INVALID                     , "ESM_DECODE_CN_MSG_IPV4_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_IPV6_LEN_INVALID                     , "ESM_DECODE_CN_MSG_IPV6_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_BCM_LEN_INVALID                      , "ESM_DECODE_CN_MSG_BCM_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_IPCP_LEN_INVALID                     , "ESM_DECODE_CN_MSG_IPCP_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_IPCP_PRI_DNS_LEN_INVALID             , "ESM_DECODE_CN_MSG_IPCP_PRI_DNS_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_IPCP_SEC_DNS_LEN_INVALID             , "ESM_DECODE_CN_MSG_IPCP_SEC_DNS_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_IPCP_OTHER_LEN_INVALID               , "ESM_DECODE_CN_MSG_IPCP_OTHER_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_LEN_INVALID                          , "ESM_DECODE_CN_MSG_LEN_INVALID"},
    {ESM_DECODE_CN_MSG_ESM_MSG_PD_INVALID                   , "ESM_DECODE_CN_MSG_ESM_MSG_PD_INVALID"},
    {ESM_DECODE_CN_MSG_ESM_MSG_TYPE_INVALID                 , "ESM_DECODE_CN_MSG_ESM_MSG_TYPE_INVALID"}
};

const VOS_UINT32 g_EsmDecodeFailCausePrintTableSize =
              (sizeof(g_EsmDecodeFailCausePrintTable)/sizeof(NAS_ESM_OM_DECODE_CN_MSG_FAIL_CAUSE_PRINT_STR_STRU));
#endif






/*****************************************************************************
  3 Function
*****************************************************************************/

VOS_UINT32  NAS_ESM_CheckIeLen
(
    const NAS_ESM_MSG_IE_STRU          *pstEsmMsgIe,
    VOS_UINT16                          usIeLen,
    VOS_UINT16                         *pusIeValueLen
)
{
    VOS_UINT16                          usFormatLen = NAS_ESM_NULL;
    VOS_UINT16                          usMinLen = pstEsmMsgIe->usMinLen;
    VOS_UINT16                          usMaxLen = pstEsmMsgIe->usMaxLen;

    usFormatLen = pstEsmMsgIe->ucFormatLen;

    /* ����ֻ�а���Type��Ԫ ,��Ҫ��1 */
    if (0xf0 == pstEsmMsgIe->ucMask)
    {
        *pusIeValueLen = 1;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    /* ����û�г���ָʾ����Ԫ����Э��涨������д*/
    if ((NAS_MSG_FORMAT_TV == pstEsmMsgIe->enType)
     || (NAS_MSG_FORMAT_V == pstEsmMsgIe->enType))
    {
        *pusIeValueLen = usMinLen - usFormatLen;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    *pusIeValueLen = usIeLen;

    /* ���ں��г���ָʾ����Ԫ����Э��涨���Ƚ��м��*/
    if ((usMinLen > (usIeLen + usFormatLen)) || (usMaxLen < (usIeLen + usFormatLen)))
    {
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeMandatoryIei
(
    const NAS_ESM_MSG_IE_STRU           *pstEsmMsgIe,
    VOS_UINT16                          *pulSum,
    const VOS_UINT8                     *pucRcvNwMsg,
    VOS_UINT32                           ulRemainLen,
    NAS_ESM_NW_MSG_STRU                 *pstNwMsgRecord
)
{
    VOS_UINT16                          usIeValueLen = 0;
    NAS_ESM_CAUSE_ENUM_UINT8            enRst;

    /* ��ѡ��Ԫ�����Ǳ���� */
    if (VOS_NULL_PTR == pstEsmMsgIe->pfDecodeFun)
    {
        return NAS_ESM_CAUSE_FEATURE_NOT_SUPPORTED;
    }

    /* У����Ԫ�����Ƿ�Ϸ���������IE Value���� */
    if (NAS_ESM_CAUSE_SUCCESS != NAS_ESM_CheckIeLen(pstEsmMsgIe,
                                                    pucRcvNwMsg[*pulSum],
                                                    &usIeValueLen))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_MANDAN_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        pstEsmMsgIe->ucIei);
        return NAS_ESM_CAUSE_INVALID_MANDATORY_INFORMATION;
    }

    /* ʣ��δ���볤��С��Ҫ�������Ԫ���ȣ�����ʧ�� */
    if ((usIeValueLen + pstEsmMsgIe->ucFormatLen) > ulRemainLen)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_MANDAN_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        pstEsmMsgIe->ucIei);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    if (NAS_MSG_FORMAT_LV == pstEsmMsgIe->enType)
    {
        /* ����L */
        *pulSum = *pulSum + 1;
    }

    /* ���������Ԫ */
    enRst = pstEsmMsgIe->pfDecodeFun(usIeValueLen,&pucRcvNwMsg[*pulSum],pstNwMsgRecord);

    if (NAS_ESM_CAUSE_SUCCESS == enRst)
    {
        *pulSum += usIeValueLen;
    }

    return enRst;
}
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeOptinalIei
(
    const NAS_ESM_MSG_IE_STRU           *pstEsmMsgIe,
    VOS_UINT16                          *pulSum,
    const VOS_UINT8                     *pucRcvNwMsg,
    VOS_UINT32                           ulRemainLen,
    NAS_ESM_NW_MSG_STRU                 *pstNwMsgRecord
)
{
    VOS_UINT16                          usIeValueLen = 0;
    VOS_UINT16                          usIeLen      = 0;
    NAS_ESM_CAUSE_ENUM_UINT8            enRst;

    if (pstEsmMsgIe->ucIei != (pucRcvNwMsg[*pulSum] & pstEsmMsgIe->ucMask))
    {
        /* ���Դ���Ԫ */
        return NAS_ESM_CAUSE_ERROR;
    }
    else
    {
        /* ��ͨ��������Type�ֶ� */
        if (0xF0 != pstEsmMsgIe->ucMask)
        {
            *pulSum = *pulSum + 1;
        }
    }

    /* У����Ԫ�����Ƿ�Ϸ���������IE Value���� */
    if (NAS_ESM_CAUSE_SUCCESS != NAS_ESM_CheckIeLen(pstEsmMsgIe,
                                                    pucRcvNwMsg[*pulSum],
                                                    &usIeValueLen))
    {
        *pulSum = *pulSum + 1 + usIeValueLen;
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_OPTION_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        pstEsmMsgIe->ucIei);
         return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    if (NAS_MSG_FORMAT_TLV == pstEsmMsgIe->enType)
    {
        /* ����L */
        *pulSum = *pulSum + 1;
    }

    /* ����������Ԫ����(�����T��L��Ҳ����T��L�ĳ���) */
    if (0xF0 != pstEsmMsgIe->ucMask)
    {
        usIeLen = usIeValueLen + pstEsmMsgIe->ucFormatLen;
    }
    else
    {
        usIeLen = usIeValueLen;
    }

    /* ʣ��δ���볤��С��Ҫ�������Ԫ���ȣ�����ʧ�� */
    if (usIeLen > ulRemainLen)
    {
        *pulSum  += usIeValueLen;
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_OPTION_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        pstEsmMsgIe->ucIei);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    /* ����Ҫ�Ŀ�ѡ��Ԫ����ֱ������ */
    if (VOS_NULL_PTR == pstEsmMsgIe->pfDecodeFun)
    {
        *pulSum  += usIeValueLen;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    /* ���������Ԫ */
    enRst = pstEsmMsgIe->pfDecodeFun(usIeValueLen,&pucRcvNwMsg[*pulSum],pstNwMsgRecord);

    /*if (NAS_ESM_CAUSE_SUCCESS == enRst)
    {
        *pulSum += usIeValueLen;
    }*/
    *pulSum += usIeValueLen;

    return enRst;
}


/*lint -e960*/
/*lint -e961*/
NAS_ESM_CAUSE_ENUM_UINT8    NAS_ESM_DecodeNwMsgIei
(
    VOS_UINT8                           ucIeMaxNum,
    VOS_UINT32                          ulRemainMsgLen,
    VOS_UINT32                         *pulDecodeMsgLen,
    const VOS_UINT8                    *pucRcvNwMsg,
    const NAS_ESM_MSG_IE_STRU          *pstEsmMsgIe,
    NAS_ESM_NW_MSG_STRU                *pstNwMsgRecord
)
{
    VOS_UINT16                          ulSum  = NAS_ESM_NULL;
    VOS_UINT8                           ucLoop = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enDecodeRst;

    VOS_UINT32                          ulDecodedIE = NAS_ESM_NULL;    /*��¼�Ѿ������Ԫ */
    VOS_UINT32                          ulDecodingIE = NAS_ESM_BIT_0;  /*��¼���ڽ����Ԫ */
    VOS_UINT32                          ulTmpPos    = NAS_ESM_BIT_0;
    VOS_UINT16                          usIeValueLen = NAS_ESM_NULL;  /*��������ԪIEI�ĳ��� */
    VOS_UINT16                          usIeLen      = NAS_ESM_NULL; /*��������Ԫ�ܳ��� */

    /* ѭ��������ѡ��Ԫ */
    while ((NAS_ESM_IsMandatoryIei(pstEsmMsgIe[ucLoop].enType)) && (ulRemainMsgLen > ulSum))
    {
        enDecodeRst = NAS_ESM_DecodeMandatoryIei(&pstEsmMsgIe[ucLoop],
                                                 &ulSum,
                                                 pucRcvNwMsg,
                                                 ulRemainMsgLen - ulSum,
                                                 pstNwMsgRecord);

        if (NAS_ESM_CAUSE_SUCCESS != enDecodeRst)
        {
            *pulDecodeMsgLen = ulSum;

            if (NAS_ESM_CAUSE_PROTOCOL_ERROR == enDecodeRst)
            {
                enDecodeRst = NAS_ESM_CAUSE_INVALID_MANDATORY_INFORMATION;
            }

            return enDecodeRst;
        }

        ucLoop++;
    }

    /* ѭ��������ѡ��Ԫ */
    while (ulRemainMsgLen > ulSum)
    {
        ulDecodingIE = NAS_ESM_BIT_0;
        ulTmpPos    = NAS_ESM_BIT_0;

        for (ucLoop = 0; ucLoop < ucIeMaxNum; ucLoop++)
        {

            /*ֻҪ��Ԫ�Ѿ����⵽��,ֱ��������Ԫ */
            if (((ulDecodingIE | ulDecodedIE) == ulDecodedIE)&&
                ((pstEsmMsgIe + ucLoop)->ucIei == (pucRcvNwMsg[ulSum] & (pstEsmMsgIe+ucLoop)->ucMask)))
            {
                /* У����Ԫ�����Ƿ�Ϸ���������Ϸ�ֱ�ӷ��أ�ֹͣ���� */
                if (NAS_ESM_CAUSE_SUCCESS != NAS_ESM_CheckIeLen(&pstEsmMsgIe[ucLoop],
                                                                pucRcvNwMsg[ulSum + 1],
                                                                &usIeValueLen))
                {
                    *pulDecodeMsgLen = ulSum;
                    return NAS_ESM_SUCCESS;
                }

                /*������������Ԫ���ܳ��� */
                usIeLen = (0xF0 != (pstEsmMsgIe+ucLoop)->ucMask)
                                ? (usIeValueLen + (pstEsmMsgIe+ucLoop)->ucFormatLen)
                                : (usIeValueLen);

                /*����ֱ��ƽ�� */
                ulSum += usIeLen;

                NAS_ESM_LOG1("NAS_ESM_DecodeNwMsgIei  skip repeated IEI: ", (pstEsmMsgIe+ucLoop)->ucIei);
                TLPS_PRINT2LAYER_INFO1(NAS_ESM_DecodeNwMsgIei_ENUM, 1, (pstEsmMsgIe+ucLoop)->ucIei);
                break;

            }

            /*��¼���ڽ����Ԫ */
            ulDecodingIE = ulDecodingIE << 1;

            /*������Ԫ */
            enDecodeRst = NAS_ESM_DecodeOptinalIei(&pstEsmMsgIe[ucLoop],
                                                   &ulSum,
                                                   pucRcvNwMsg,
                                                   ulRemainMsgLen - ulSum,
                                                   pstNwMsgRecord);


            if (NAS_ESM_CAUSE_SUCCESS != enDecodeRst)
            {
                continue;
            }

            /*��¼�Ѿ������Ԫ */
            ulDecodedIE |=  (ulTmpPos << ucLoop);

            break;
        }
        /*�޷�ʶ���յ���NAS��Ϣ�е���Ԫ,Ҳ�޷�֪�����������ĳ���,��ѡ��Ԫ����ʧ��
         ����Ӱ����������,���԰��ս���ɹ����� */
        if (ucLoop >= ucIeMaxNum)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_DecodeNwMsgIei :(WARN)Some IEI not specified!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeNwMsgIei_ENUM, 2);
            *pulDecodeMsgLen = ulSum;
            return NAS_ESM_CAUSE_SUCCESS;
        }
    }
    *pulDecodeMsgLen = ulSum;

    return NAS_ESM_CAUSE_SUCCESS;

}


VOS_VOID NAS_ESM_GetDecodeTableIndex( NAS_ESMCN_MSG_TYPE_ENUM_UINT8 enMsgType, VOS_UINT32 *pulIndex )
{
    VOS_UINT32                     ulLoop = NAS_ESM_NULL;

    for (ulLoop = 0; ulLoop < g_EsmDecodeTableSize; ulLoop++)
    {
        if (enMsgType == g_EsmDecodeTable[ulLoop].enMsgTyep)
        {
            break;
        }
    }

    *pulIndex = ulLoop;

     return;
}


NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeNwMsgValue
(
    VOS_UINT8                           *pucMsg,
    VOS_UINT32                          *pulDecodeLen,
    VOS_UINT32                          *pulDecodeTableIndex,
    NAS_ESM_NW_MSG_STRU                 *pstMsgIE
)
{
    VOS_UINT32                          ulIndex = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause      =  NAS_ESM_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum           =  NAS_ESM_NULL;
    VOS_UINT32                          ulUnDecodeMsgLen = *pulDecodeLen;
    VOS_UINT32                          ulDecodeMsgLen  = NAS_ESM_NULL;
    VOS_UINT8*                          pucTmpMsg       =  pucMsg;
    NAS_ESM_NW_MSG_STRU                *pstTmpMsgIE     =  pstMsgIE;
    NAS_ESMCN_MSG_TYPE_ENUM_UINT8       enMsgType;

    /* ��ȡ������Ϣ���� */
    enMsgType = pucTmpMsg[ulSum];

    /* ������Ϣ���͵õ����������*/
    NAS_ESM_GetDecodeTableIndex(enMsgType,&ulIndex);

    /* ���ڽ�����е���Ϣ����ֱ�ӷ��ش��� */
    if (ulIndex >= g_EsmDecodeTableSize)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_IE_NOIE,
                                        ESM_DECODE_CN_MSG_ESM_MSG_TYPE_INVALID,
                                        enMsgType);
        TLPS_PRINT2LAYER_INFO(NAS_ESM_DecodeNwMsgValue_ENUM, LNAS_MSG_INVALID);
        return NAS_ESM_CAUSE_MESSAGE_TYPE_NON_EXIST_OR_NOT_IMPLEMENTED;
    }

    *pulDecodeTableIndex = ulIndex;

    /*������Ϣ����*/
    pstTmpMsgIE->enEsmCnMsgType = enMsgType;

    /*����Message type*/
    ulSum++;
    ulUnDecodeMsgLen--;

    if (g_EsmDecodeTable[ulIndex].ulWithLinkEpsb)
    {
        /*��¼Linked EPS bearer identity*/
        pstTmpMsgIE->ucLinkedEpsbId     = pucTmpMsg[ulSum++] & NAS_ESM_MSG_LOW_BIT;
        pstTmpMsgIE->bitOpLinkedEpsbId  = NAS_ESM_OP_TRUE;
        ulUnDecodeMsgLen--;
    }

    /* û�ж����������Ϣֻ�����ѽ��빫����Ϣ����ʱ�Ѿ�������� */
    if (VOS_NULL_PTR == g_EsmDecodeTable[ulIndex].pstEsmMsgIE)
    {
        *pulDecodeLen = ulSum;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    /* ���ù������뺯�� */
    enEsmCause = NAS_ESM_DecodeNwMsgIei(g_EsmDecodeTable[ulIndex].ucMsgTableSize,
                                       ulUnDecodeMsgLen,
                                       &ulDecodeMsgLen,
                                       pucTmpMsg+ulSum,
                                       g_EsmDecodeTable[ulIndex].pstEsmMsgIE,
                                       pstTmpMsgIE);

    *pulDecodeLen = ulSum + ulDecodeMsgLen;
    return enEsmCause;

}


NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNwMsg(VOS_UINT8 *pucMsg,
                                         VOS_UINT32 *pulMsgLen,
                                         NAS_ESM_NW_MSG_STRU *pstMsgIE)
{
    VOS_UINT8                          *pucTmpMsg           = pucMsg;
    VOS_UINT8                           ucTmpBearerId       = NAS_ESM_NULL;
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_NULL;
    VOS_UINT32                          ulUnDecodeMsgLength = *pulMsgLen;
    VOS_UINT32                          ulMsgLenTmp         = NAS_ESM_NULL;
    NAS_ESM_NW_MSG_STRU                *pstTmpMsgIE         = pstMsgIE;
    VOS_UINT32                          ulIndex             = NAS_ESM_NULL;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_DecodeNwMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DecodeNwMsg_ENUM, LNAS_ENTRY);

    /*��ڲ������(pucMsg)*/
    if(ulUnDecodeMsgLength < NAS_ESM_MSG_MIN_LEN)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_IE_NOIE,
                                        ESM_DECODE_CN_MSG_LEN_INVALID,
                                        ulUnDecodeMsgLength);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodeNwMsg_ENUM, LNAS_MSG_INVALID, 1);
        return NAS_ESM_CAUSE_MSG_TOO_SHORT;
    }

    /*�ж�Protocol discriminator*/
    if(NAS_ESM_MSG_PD != (pucTmpMsg[ulSum] & NAS_ESM_MSG_LOW_BIT))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_IE_NOIE,
                                        ESM_DECODE_CN_MSG_ESM_MSG_PD_INVALID,
                                        ulUnDecodeMsgLength);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodeNwMsg_ENUM, LNAS_MSG_INVALID, 1);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    /*��¼ucEPSBearerID*/
    /*��Ԫ���,ȡ��Ϣ��һ�ֽ��е�5-8λΪpulEpsbId
    ���ж��Ƿ����Э�飬0000-0100ΪЭ�鱣����*/
    ucTmpBearerId = (pucTmpMsg[ulSum] >> NAS_ESM_MOVEMENT_4_BITS)& NAS_ESM_MSG_LOW_BIT;

    /*����pulEpsbId*/
    pstTmpMsgIE->ucEpsbId = ucTmpBearerId;


    /*����Protocol discriminator��EPS bearer identity*/
    ulSum++;

    /*����PTI������Procedure transaction identifier��Ԫ*/
    pstTmpMsgIE->ucPti = pucTmpMsg[ulSum];

    /*����PTI*/
    ulSum++;

    *pulMsgLen = ulSum;
    ulUnDecodeMsgLength -= NAS_ESM_SUM_LEN_OF_PD_EBI_PTI;
    ulMsgLenTmp = ulUnDecodeMsgLength;

    enEsmCause = NAS_ESM_DecodeNwMsgValue(pucMsg + ulSum,&ulMsgLenTmp,&ulIndex,pstTmpMsgIE);

    *pulMsgLen = *pulMsgLen + ulMsgLenTmp;

    if (NAS_ESM_CAUSE_MESSAGE_TYPE_NON_EXIST_OR_NOT_IMPLEMENTED != enEsmCause)
    {
        NAS_ESM_SndAirMsgReportInd(pucMsg,*pulMsgLen,
                                   NAS_ESM_AIR_MSG_DIR_ENUM_DOWN,
                                   g_EsmDecodeTable[ulIndex].enAirMsgId);
    }

    return enEsmCause;

}

VOS_UINT32 NAS_ESM_DecodeNwEsmMsgGetEsmCause(VOS_UINT8 *pucMsg,
                                         VOS_UINT32 ulMsgLen,
                                         VOS_UINT8 *enEsmCause)
{
    VOS_UINT8                          *pucTmpMsg           = pucMsg;
    VOS_UINT8                           ucTmpBearerId       = NAS_ESM_NULL;
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    VOS_UINT32                          ulUnDecodeMsgLength = ulMsgLen;
    VOS_UINT32                          ulMsgLenTmp         = NAS_ESM_NULL;
    NAS_ESM_NW_MSG_STRU                *pstTmpMsgIE;
    VOS_UINT32                          ulIndex             = NAS_ESM_NULL;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_DecodeNwEsmMsgGetEsmCause is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DecodeNwEsmMsgGetEsmCause_ENUM, LNAS_ENTRY);

    /*��ڲ������(pucMsg)*/
    if(ulUnDecodeMsgLength < NAS_ESM_MSG_MIN_LEN)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_ESM_CAUSE_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        ulUnDecodeMsgLength);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodeNwEsmMsgGetEsmCause_ENUM, LNAS_MSG_INVALID, 1);
        return VOS_ERR;
    }

    /*�ж�Protocol discriminator*/
    if(NAS_ESM_MSG_PD != (pucTmpMsg[ulSum] & NAS_ESM_MSG_LOW_BIT))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_ESM_CAUSE_IE,
                                        ESM_DECODE_CN_MSG_PD_INVALID,
                                        (pucTmpMsg[ulSum] & NAS_ESM_MSG_LOW_BIT));
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodeNwEsmMsgGetEsmCause_ENUM, LNAS_MSG_INVALID, 2);
        return VOS_ERR;
    }
    pstTmpMsgIE = (VOS_VOID *)NAS_ESM_MEM_ALLOC(sizeof(NAS_ESM_NW_MSG_STRU));
    if (VOS_NULL_PTR == pstTmpMsgIE)
    {
        NAS_ESM_ERR_LOG(" NAS_ESM_DecodeNwEsmMsgGetEsmCause: MSG ALLOC VOS_NULL_PTR  Null!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_DecodeNwEsmMsgGetEsmCause_ENUM, LNAS_NULL_PTR);
        return VOS_ERR;
    }
    NAS_ESM_MEM_SET(pstTmpMsgIE,0,sizeof(NAS_ESM_NW_MSG_STRU));

    if( ulUnDecodeMsgLength > ESM_MAX_MSG_CONTAINER_CNTNTS_LEN )
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_ESM_CAUSE_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        ulUnDecodeMsgLength);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodeNwEsmMsgGetEsmCause_ENUM, LNAS_MSG_INVALID, 3);
        ulUnDecodeMsgLength = ESM_MAX_MSG_CONTAINER_CNTNTS_LEN;
    }

    /*��¼ucEPSBearerID*/
    /*��Ԫ���,ȡ��Ϣ��һ�ֽ��е�5-8λΪpulEpsbId
    ���ж��Ƿ����Э�飬0000-0100ΪЭ�鱣����*/
    ucTmpBearerId = (pucTmpMsg[ulSum] >> NAS_ESM_MOVEMENT_4_BITS)& NAS_ESM_MSG_LOW_BIT;

    /*����pulEpsbId*/
    pstTmpMsgIE->ucEpsbId = ucTmpBearerId;


    /*����Protocol discriminator��EPS bearer identity*/
    ulSum++;

    /*����PTI������Procedure transaction identifier��Ԫ*/
    pstTmpMsgIE->ucPti = pucTmpMsg[ulSum];

    /*����PTI*/
    ulSum++;

    ulUnDecodeMsgLength -= NAS_ESM_SUM_LEN_OF_PD_EBI_PTI;
    ulMsgLenTmp = ulUnDecodeMsgLength;

    if(NAS_ESM_CAUSE_SUCCESS == NAS_ESM_DecodeNwMsgValue(pucMsg + ulSum,&ulMsgLenTmp,&ulIndex,pstTmpMsgIE))
    {   if(NAS_ESM_OP_TRUE == pstTmpMsgIE->bitOpEsmCause)
        {
            *enEsmCause = pstTmpMsgIE->enEsmCau;
        }
        NAS_ESM_MEM_FREE(pstTmpMsgIE);
        return VOS_OK;
    }
    else
    {
        NAS_ESM_MEM_FREE(pstTmpMsgIE);
        return VOS_ERR;
    }
}


NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeTftNoOperation
(
    NAS_ESM_NW_MSG_STRU                *pstMsgIE,
    VOS_UINT8                          *pucMsg
)
{
    VOS_UINT8                           ucCnt       = NAS_ESM_NULL;
    VOS_UINT8                          *pTmp        = pucMsg;
    NAS_ESM_CONTEXT_TFT_STRU           *pstTftInfo  = VOS_NULL_PTR;

    if (pTmp[NAS_ESM_PARAMETER_ID_OFFSET] != NAS_ESM_TFT_PARA_LIST_ID)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_PARA_LIST_ID_INVALID,
                                        pTmp[NAS_ESM_PARAMETER_ID_OFFSET]);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeTftNoOperation_ENUM, LNAS_MSG_INVALID);
        return NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT;
    }

    /*����NO OPERATION*/
    pstMsgIE->stTadInfo.enTftOpType = NAS_ESM_TFT_OP_TYPE_NO_OP;
    pstMsgIE->stTadInfo.ucSdfPfNum  = pTmp[NAS_ESM_PARAMETER_LEN_OFFSET];

    for (ucCnt = NAS_ESM_NULL; ucCnt < pstMsgIE->stTadInfo.ucSdfPfNum; ucCnt++)
    {
        pstTftInfo = &pstMsgIE->stTadInfo.astSdfPfInfo[ucCnt];
        pstTftInfo->ucNwPacketFilterId = (pTmp[NAS_ESM_PARAMETER_LEN_OFFSET + 1 + ucCnt])
                                        &(NAS_ESM_MSG_LOW_BIT);
    }

    return NAS_ESM_CAUSE_SUCCESS;
}
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeTftDeleteFilter
(
    NAS_ESM_NW_MSG_STRU                *pstMsgIE,
    VOS_UINT8                          *pucMsg
)
{
    VOS_UINT8                           ucCnt       = NAS_ESM_NULL;
    VOS_UINT8                           ucPfNum     = NAS_ESM_NULL;
    VOS_UINT8                          *pTmp        = pucMsg;
    NAS_ESM_CONTEXT_TFT_STRU           *pstTftInfo  = VOS_NULL_PTR;

    /*��ȡpacket filter����*/
    ucPfNum = pTmp[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_LOW_BIT;

    /* OCTET4 Packet filter identifier 1 */
    for (ucCnt = NAS_ESM_NULL; ucCnt < ucPfNum; ucCnt++)
    {
        pstTftInfo = &pstMsgIE->stTadInfo.astSdfPfInfo[ucCnt];
        pstTftInfo->ucNwPacketFilterId = (pTmp[NAS_ESM_PACKET_FILTER_ID_OFFSET + ucCnt])&(NAS_ESM_MSG_LOW_BIT);
    }

    pstMsgIE->stTadInfo.enTftOpType = NAS_ESM_TFT_OP_TYPE_DELETE_FILTER;
    pstMsgIE->stTadInfo.ucSdfPfNum = ucPfNum;

    return NAS_ESM_CAUSE_SUCCESS;
}

NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeFilterContent
(
    NAS_ESM_NW_MSG_STRU           *pstMsgIE,
    VOS_UINT8                     *pucMsg,
    VOS_UINT8                      ucToDecodePfNum
)
{
    VOS_UINT8                           ucTad       = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause  = NAS_ESM_CAUSE_SUCCESS;
    VOS_UINT8                          *pTmp        = pucMsg;

    /*��ȡTFT������*/
    ucTad = pTmp[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_HIGH_BIT;

    switch(ucTad)
    {
        case NAS_ESM_TFT_ADD_FILTER:
        case NAS_ESM_TFT_CREATE_TFT:
        case NAS_ESM_TFT_REPLACE_FILTER:
            enEsmCause = NAS_ESM_DecodeTftAddFilter(pstMsgIE, pTmp, ucToDecodePfNum);
            break;
        case NAS_ESM_TFT_NO_OPERATION:
            enEsmCause = NAS_ESM_DecodeTftNoOperation(pstMsgIE, pTmp);
            break;
        case NAS_ESM_TFT_DELETE_TFT:
            pstMsgIE->stTadInfo.enTftOpType = NAS_ESM_TFT_OP_TYPE_DELETE_TFT;
            enEsmCause = NAS_ESM_CAUSE_SUCCESS;
            break;
        case NAS_ESM_TFT_DELETE_FILTER:
            enEsmCause = NAS_ESM_DecodeTftDeleteFilter(pstMsgIE, pTmp);
            break;
        default:
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_DECODE_CN_MSG_TAD_TYPE_INVALID,
                                            ucTad);
            return NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT;
    }

    return enEsmCause;
}
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeTftAddFilter
(
    NAS_ESM_NW_MSG_STRU                *pstMsgIE,
    VOS_UINT8                          *pTmp,
    VOS_UINT8                           ucToDecodePfNum
)
{
    VOS_UINT8                     ucPfNum     = NAS_ESM_NULL;
    VOS_UINT8                     ucTad       = NAS_ESM_NULL;
    VOS_UINT8                     ucLoop      = NAS_ESM_NULL;
    VOS_UINT8                     *pucTmp     = VOS_NULL_PTR;
    VOS_UINT8                     ucPfLength  = NAS_ESM_NULL;
    NAS_ESM_CONTEXT_TFT_STRU      stTftInfo;
    NAS_ESM_CAUSE_ENUM_UINT8      enEsmCause  = NAS_ESM_CAUSE_SUCCESS;

    if (ucToDecodePfNum < 1)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_PF_NUM_INVALID,
                                        ucToDecodePfNum);
        return NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER;
    }

    /*��ȡTFT������*/
    ucTad = (pTmp[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_HIGH_3_BIT)
                                                    >> NAS_ESM_MOVEMENT_5_BITS;

    pucTmp = &(pTmp[NAS_ESM_PACKET_FILTER_ID_OFFSET]);

    /* ��������packet filter */
    for ( ucLoop = 0; ucLoop < ucToDecodePfNum; ucLoop++ )
    {
        NAS_ESM_MEM_SET(&stTftInfo, 0, sizeof(NAS_ESM_CONTEXT_TFT_STRU));
        /* ���뵱ǰpacket filter */
        enEsmCause = NAS_ESM_DecodeAddOneFilterTFT(&stTftInfo, pucTmp, &ucPfLength);

        if (NAS_ESM_CAUSE_SUCCESS == enEsmCause)
        {
            NAS_ESM_MEM_CPY(&pstMsgIE->stTadInfo.astSdfPfInfo[ucPfNum++], &stTftInfo, sizeof(NAS_ESM_CONTEXT_TFT_STRU));
        }

        /* ��ָ��ָ����һ��packet filter����ʼλ�� */
        pucTmp = pucTmp + ucPfLength + NAS_ESM_PACKET_FILTER_LEN_OFFSET;
    }


    if (ucPfNum < 1)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_PF_NUM_INVALID,
                                        ucPfNum);
        return NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER;
    }

    /* ����������packet filter�ĸ��� */
    pstMsgIE->stTadInfo.enTftOpType = ucTad;
    pstMsgIE->stTadInfo.ucSdfPfNum = ucPfNum;

    return NAS_ESM_CAUSE_SUCCESS;
}
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateTftLenAddFilter
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT8                           ucTftLength,
    VOS_UINT8                          *pucToDecodePfNum
)
{
    VOS_UINT8                           ucPfNum         = NAS_ESM_NULL;
    VOS_UINT8                           ucLoop          = NAS_ESM_NULL;
    VOS_UINT8                           ucAllPfLength   = NAS_ESM_NULL;
    VOS_UINT8                           ucPrePfLength   = NAS_ESM_NULL;
    VOS_UINT8                          *pTmp            = pucMsg;
    VOS_UINT8                          *pucTemp         = VOS_NULL_PTR;

    *pucToDecodePfNum = 0;

    /*��ȡpacket filter����*/
    ucPfNum = pTmp[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_LOW_BIT;

    if(ucPfNum == NAS_ESM_NULL)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_PF_NUM_INVALID,
                                        ucPfNum);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateTftLenAddFilter_ENUM, LNAS_MSG_INVALID, 1);
        return NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT;
    }

    /* �жϳ����Ƿ�Ϸ� */
    if(ucTftLength < (NAS_ESM_TAD_BYTE + NAS_ESM_SUM_LEN_OF_PFID_PRECEDENCE_LEN))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        ucTftLength);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateTftLenAddFilter_ENUM, LNAS_MSG_INVALID, 2);
        return NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT;
    }

    pucTemp = &(pTmp[NAS_ESM_PACKET_FILTER_LEN_OFFSET]);

    /* ��ȡ����packet filter��ռ���ֽ��� */
    ucPrePfLength = pTmp[NAS_ESM_PACKET_FILTER_LEN_OFFSET];
    ucAllPfLength = ucPrePfLength + (NAS_ESM_TAD_BYTE + NAS_ESM_SUM_LEN_OF_PFID_PRECEDENCE_LEN);
    if (ucAllPfLength <= ucTftLength)
    {
        (*pucToDecodePfNum) ++;
    }
    else
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        ucTftLength);
        return NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT;
    }

    for ( ucLoop = 1; ucLoop < ucPfNum; ucLoop++ )
    {
        /* �жϳ����Ƿ�Ϸ� */
        if ((ucAllPfLength + NAS_ESM_SUM_LEN_OF_PFID_PRECEDENCE_LEN) > ucTftLength)
        {
            break;
        }

        /* �ۼ���һ��packet filter�ĳ��� */
        ucAllPfLength = ucAllPfLength +
                        pucTemp[ucPrePfLength + NAS_ESM_SUM_LEN_OF_PFID_PRECEDENCE_LEN]
                        + NAS_ESM_SUM_LEN_OF_PFID_PRECEDENCE_LEN;
        if (ucAllPfLength <= ucTftLength)
        {
           (*pucToDecodePfNum) ++;
        }

        /* ��ָ��ָ����һ��packet filter�ĳ�����Ԫ��λ�� */
        pucTemp = &(pucTemp[ucPrePfLength + NAS_ESM_SUM_LEN_OF_PFID_PRECEDENCE_LEN]);

        /* ������һ��packet filter�ĳ�����Ԫ��ֵ */
        ucPrePfLength = *pucTemp;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateTftLenNoOperation
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT8                           ucTftLength
)
{
    VOS_UINT8                           *pTmp       = pucMsg;
    VOS_UINT8                            ucPfNum    = NAS_ESM_NULL;

    /*��ȡpacket filter����*/
    ucPfNum = pTmp[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_LOW_BIT;

    if((pTmp[NAS_ESM_PARAMETER_LEN_OFFSET] != (ucTftLength - (NAS_ESM_PARAMETER_LEN_OFFSET + 1)))
        ||( NAS_ESM_NULL != ucPfNum))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidateTftLenNoOperation:NW->SM TFT Length Error!");
        if (NAS_ESM_NULL != ucPfNum)
        {
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_DECODE_CN_MSG_PF_NUM_INVALID,
                                            ucPfNum);
        }
        else
        {
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                            pTmp[NAS_ESM_PARAMETER_LEN_OFFSET]);
        }
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateTftLenNoOperation_ENUM, LNAS_MSG_INVALID);
        return NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateTftLenDeleteTft
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT8                           ucTftLength
)
{
    VOS_UINT8                            ucPfNum    = NAS_ESM_NULL;
    VOS_UINT8                           *pTmp       = pucMsg;

    (VOS_VOID)ucTftLength;

    /*��ȡpacket filter����*/
    ucPfNum = pTmp[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_LOW_BIT;

    if(ucPfNum != NAS_ESM_NULL)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_PF_NUM_INVALID,
                                        ucPfNum);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ValidateTftLenDeleteTft_ENUM, LNAS_MSG_INVALID);
        return NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateTftLenDeleteFilter
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT8                           ucTftLength
)
{
    VOS_UINT8                            ucPfNum    = NAS_ESM_NULL;
    VOS_UINT8                           *pTmp       = pucMsg;

    /*��ȡpacket filter����*/
    ucPfNum = pTmp[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_LOW_BIT;

    if(ucPfNum == NAS_ESM_NULL)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_PF_NUM_INVALID,
                                        ucPfNum);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateTftLenDeleteFilter_ENUM, LNAS_MSG_INVALID, 1);
        return NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT;
    }

    if (ucTftLength != (ucPfNum + 1))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        ucTftLength);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateTftLenDeleteFilter_ENUM, LNAS_MSG_INVALID, 2);
        return NAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateTftLen
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT8                           ucTftLength,
    VOS_UINT8                          *pucToDecodePfNum
)
{
    VOS_UINT8                           ucTad       = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause  = NAS_ESM_CAUSE_SUCCESS;

    /*��ȡTFT������*/
    ucTad = pucMsg[NAS_ESM_TAD_PFNUM_OFFSET] & NAS_ESM_MSG_HIGH_BIT;

    switch(ucTad)
    {
        case NAS_ESM_TFT_ADD_FILTER:
        case NAS_ESM_TFT_CREATE_TFT:
        case NAS_ESM_TFT_REPLACE_FILTER:
            enEsmCause = NAS_ESM_ValidateTftLenAddFilter(pucMsg, ucTftLength, pucToDecodePfNum);
            break;
        case NAS_ESM_TFT_NO_OPERATION:

            enEsmCause = NAS_ESM_ValidateTftLenNoOperation(pucMsg, ucTftLength);
            break;
        case NAS_ESM_TFT_DELETE_TFT:

            enEsmCause = NAS_ESM_ValidateTftLenDeleteTft(pucMsg, ucTftLength);
            break;
        case NAS_ESM_TFT_DELETE_FILTER:

            enEsmCause = NAS_ESM_ValidateTftLenDeleteFilter(pucMsg, ucTftLength);
            break;
        default:
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_DECODE_CN_MSG_TAD_TYPE_INVALID,
                                            ucTad);
            return NAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT;
    }

    return enEsmCause;
}
VOS_UINT32 NAS_ESM_IsExistSamePfIdInTft
(
    VOS_UINT32                          ulPfNum,
    const NAS_ESM_CONTEXT_TFT_STRU     *pstTFT
)
{
    VOS_UINT32                          ulCnt1 = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt2 = NAS_ESM_NULL;

    for (ulCnt1 = NAS_ESM_NULL;ulCnt1 < ulPfNum;ulCnt1++)
    {
        for (ulCnt2 = ulCnt1 + 1 ;ulCnt2 < ulPfNum;ulCnt2++)
        {
            if (pstTFT[ulCnt1].ucNwPacketFilterId == pstTFT[ulCnt2].ucNwPacketFilterId)
            {
                return NAS_ESM_SUCCESS;
            }
        }
    }

    return NAS_ESM_FAILURE;
}
/*****************************************************************************
 Function Name   : NAS_ESM_ValidateTftIeAfterDecode
 Description     : TFT�������֮�����϶�������TFT��Ԫ���кϷ��Լ��
 Input           : None
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-6-7  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateTftIeAfterDecode
(
    const NAS_ESM_NW_MSG_STRU          *pstMsgIE
)
{
    VOS_UINT32                          ulRslt        = NAS_ESM_FAILURE;
    VOS_UINT32                          ulCnt         = NAS_ESM_NULL;
    const NAS_ESM_CONTEXT_TFT_STRU     *pstTmpTftInfo = VOS_NULL_PTR;

    /* ���TFT��Ԫ�е�packet filter id�Ƿ����ظ� */
    ulRslt = NAS_ESM_IsExistSamePfIdInTft(pstMsgIE->stTadInfo.ucSdfPfNum,
                                          pstMsgIE->stTadInfo.astSdfPfInfo);
    if (NAS_ESM_SUCCESS == ulRslt)
    {
        /*������Ϣ���ʧ��*/
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                        ESM_DECODE_CN_MSG_SAME_PF_ID,
                                        pstMsgIE->stTadInfo.ucSdfPfNum);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateTftIeAfterDecode_ENUM, LNAS_MSG_INVALID, 1);
        return NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER;
    }

    /* ��TAD��ΪCREATE_TFT��ADD_FILTER��REPLACE_FILTER������TFT��Ԫ�е����ȼ�
       �Ƿ����ظ� */
    if ((NAS_ESM_TFT_OP_TYPE_CREATE_TFT == pstMsgIE->stTadInfo.enTftOpType)
        || (NAS_ESM_TFT_OP_TYPE_ADD_FILTER == pstMsgIE->stTadInfo.enTftOpType)
        || (NAS_ESM_TFT_OP_TYPE_REPLACE_FILTER == pstMsgIE->stTadInfo.enTftOpType))
    {
        /* ���TFT��Ԫ�е�precedence �Ƿ����ظ� */
        ulRslt = NAS_ESM_IsExistSamePrecedenceInTft(pstMsgIE->stTadInfo.ucSdfPfNum,
                                                    pstMsgIE->stTadInfo.astSdfPfInfo);
        if (NAS_ESM_SUCCESS == ulRslt)
        {
            /*������Ϣ���ʧ��*/
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_DECODE_CN_MSG_SAME_PF_PRECEDENCE,
                                            pstMsgIE->stTadInfo.ucSdfPfNum);
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateTftIeAfterDecode_ENUM, LNAS_MSG_INVALID, 2);
            return NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER;
        }
    }

    /* �������ͬʱ���ö˿ںźͶ˿ڷ�Χ�Ĵ��� */
    for (ulCnt = NAS_ESM_NULL; ulCnt < pstMsgIE->stTadInfo.ucSdfPfNum ; ulCnt++)
    {
        pstTmpTftInfo = &pstMsgIE->stTadInfo.astSdfPfInfo[ulCnt];

        if(((NAS_ESM_OP_TRUE == pstTmpTftInfo->bitOpLocalPortRange)
            && (NAS_ESM_OP_TRUE == pstTmpTftInfo->bitOpSingleLocalPort))
         || ((NAS_ESM_OP_TRUE == pstTmpTftInfo->bitOpSingleRemotePort)
            && (NAS_ESM_OP_TRUE == pstTmpTftInfo->bitOpRemotePortRange)))
        {
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_TFT_IE,
                                            ESM_DECODE_CN_MSG_SIGLE_PORT_AND_PORT_RANGE_COEXIST,
                                            pstMsgIE->stTadInfo.ucSdfPfNum);
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateTftIeAfterDecode_ENUM, LNAS_MSG_INVALID, 3);
            return NAS_ESM_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER;
        }
    }

    return NAS_ESM_CAUSE_SUCCESS;
}
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeNwTftValue
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause        = NAS_ESM_CAUSE_SUCCESS;
    VOS_UINT32                          ulSum             = NAS_ESM_NULL;
    const VOS_UINT8                    *pucTmpMsg         = pucMsg;
    VOS_UINT8                          *pTmp              = VOS_NULL_PTR;
    VOS_UINT8                           ucToDecodePfNum;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_DecodeNwTftValue is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DecodeNwTftValue_ENUM, LNAS_ENTRY);

    pTmp     = (VOS_UINT8*) &(pucTmpMsg[ulSum]);

    /* ���TAD����PF�����Ĵ������*/
    enEsmCause = NAS_ESM_ValidateTftLen(pTmp,(VOS_UINT8)usMsgLen,&ucToDecodePfNum);
    if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
    {
        /*������Ϣ���ʧ��*/
        NAS_ESM_WARN_LOG( "NAS_ESM_DecodeNwTftValue:NAS_ESM_ValidateTftLen failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeNwTftValue_ENUM, LNAS_MSG_INVALID);
        return enEsmCause;
    }


    /* ����TAD����������TFT */
    enEsmCause = NAS_ESM_DecodeFilterContent(pstMsgIE, pTmp, ucToDecodePfNum);
    if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
    {
        /*������Ϣ���ʧ��*/
        NAS_ESM_WARN_LOG( "NAS_ESM_DecodeEsmTft:NAS_ESM_DecodeFilterContent run Err!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodeNwTftValue_ENUM, LNAS_FAIL, 1);
        return enEsmCause;
    }
    enEsmCause = NAS_ESM_ValidateTftIeAfterDecode(pstMsgIE);
    if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
    {
        /*������Ϣ���ʧ��*/
        NAS_ESM_WARN_LOG( "NAS_ESM_DecodeEsmTft:NAS_ESM_ValidateTftIeAfterDecode failed!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodeNwTftValue_ENUM, LNAS_FAIL, 2);
        return enEsmCause;
    }

    pstMsgIE->bitOpTadInfo = NAS_ESM_OP_TRUE;

    return NAS_ESM_CAUSE_SUCCESS;
}

VOS_VOID  NAS_ESM_EpsQosRateDecodeLowByte
(
    VOS_UINT8                           ucLow,
    VOS_UINT32                         *pulRate32
)
{
    if (NAS_ESM_EPS_QOS_NULL_RATE2 == ucLow)
    {
        *pulRate32 = NAS_ESM_NULL;
        return;
    }

    /* �ж�ucLow�ĵ�8λ�Ƿ�Ϊ0 */
    if (NAS_ESM_NULL != (ucLow >> NAS_ESM_MOVEMENT_7_BITS))
    {
        *pulRate32 = ((ucLow - (1 << NAS_ESM_MOVEMENT_7_BITS)) *
                        NAS_ESM_QOS_RATE_GRANULARITY_64KB) + NAS_ESM_QOS_RATE_576KB;
        return;
    }

    /* �ж�ucLow�ĵ�7λ�Ƿ�Ϊ0 */
    if (NAS_ESM_NULL != (ucLow >> NAS_ESM_MOVEMENT_6_BITS))
    {
        *pulRate32 = ((ucLow - (1 << NAS_ESM_MOVEMENT_6_BITS)) *
                        NAS_ESM_QOS_RATE_GRANULARITY_8KB) + NAS_ESM_QOS_RATE_64KB;
        return;
    }

    *pulRate32 = ucLow;
}

VOS_VOID  NAS_ESM_EpsQosRateDecodeHighByte
(
    VOS_UINT8                           ucHigh,
    VOS_UINT32                         *pulRate32
)
{
    /* ��01001010�Ƚ� */
    if (ucHigh <= NAS_ESM_QOS_RATE_RANGE_16000KB_GRANULARITY_64KB)
    {
        *pulRate32 = (ucHigh * NAS_ESM_QOS_RATE_GRANULARITY_100KB) +
                                                NAS_ESM_QOS_RATE_8600KB;
        return;
    }

    /* ��10111010�Ƚ� */
    if (ucHigh <= NAS_ESM_QOS_RATE_RANGE_128MB_GRANULARITY_1MB)
    {
        *pulRate32 = ((ucHigh - NAS_ESM_QOS_RATE_RANGE_16000KB_GRANULARITY_64KB)
                        * NAS_ESM_QOS_RATE_GRANULARITY_1MB) + NAS_ESM_QOS_RATE_16MB;
        return;
    }

    /* ��11111010�Ƚ� */
    if (ucHigh <= NAS_ESM_QOS_RATE_RANGE_256MB_GRANULARITY_2MB)
    {
        *pulRate32 = ((ucHigh - NAS_ESM_QOS_RATE_RANGE_128MB_GRANULARITY_1MB)
                        * NAS_ESM_QOS_RATE_GRANULARITY_2MB) + NAS_ESM_QOS_RATE_128MB;
        return;
    }

    *pulRate32 = NAS_ESM_QOS_RATE_256MB;
}
VOS_VOID  NAS_ESM_EpsQosRateDecodeThirdByte
(
    VOS_UINT8                           ucThird,
    VOS_UINT32                         *pulRate32
)
{
    /* ��0011 1101�Ƚ� */
    if (ucThird <= NAS_ESM_QOS_RATE_RANGE_500MB_GRANULARITY_4MB)
    {
        *pulRate32 = (ucThird*NAS_ESM_QOS_RATE_GRANULARITY_4MB) + NAS_ESM_QOS_RATE_256MB;
        return;
    }

    /* ��1010 0001�Ƚ� */
    if (ucThird <= NAS_ESM_QOS_RATE_RANGE_1500MB_GRANULARITY_10MB)
    {
        *pulRate32 = ((ucThird - NAS_ESM_QOS_RATE_RANGE_500MB_GRANULARITY_4MB)
                        * NAS_ESM_QOS_RATE_GRANULARITY_10MB) + NAS_ESM_QOS_RATE_500MB;
        return;
    }

    /* ��1111 0110 �Ƚ� */
    if (ucThird <= NAS_ESM_QOS_RATE_RANGE_10GB_GRANULARITY_100MB)
    {
        *pulRate32 = ((ucThird - NAS_ESM_QOS_RATE_RANGE_1500MB_GRANULARITY_10MB)
                        * NAS_ESM_QOS_RATE_GRANULARITY_100MB)+ NAS_ESM_QOS_RATE_1500MB;
        return;
    }

    *pulRate32 = NAS_ESM_QOS_RATE_10GB;
}
VOS_VOID  NAS_ESM_EpsQosRateDecodeTo32
(
    VOS_UINT32                          ulRate32,
    VOS_UINT32                         *pulRate32
)
{
    VOS_UINT8                           ucThird = NAS_ESM_NULL;
    VOS_UINT8                           ucHigh = NAS_ESM_NULL;
    VOS_UINT8                           ucLow  = NAS_ESM_NULL;

    if (NAS_ESM_NULL == ulRate32)
    {
        *pulRate32 = NAS_ESM_NULL;
        return;
    }

    ucThird = (VOS_UINT8)((ulRate32 & NAS_ESM_THIRD_BYTE) >> NAS_ESM_MOVEMENT_16_BITS);
    ucHigh = (VOS_UINT8)((ulRate32 & NAS_ESM_HIGH_BYTE) >> NAS_ESM_MOVEMENT_8_BITS);
    ucLow = (VOS_UINT8)(ulRate32 & NAS_ESM_LOW_BYTE);

    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        /* �ж�16~23λ�Ƿ�Ϊ0 */
        if (NAS_ESM_NULL == ucThird)
        {
            /* �жϸ�8λ�Ƿ�Ϊ0 */
            if (NAS_ESM_NULL == ucHigh)
            {
                NAS_ESM_EpsQosRateDecodeLowByte(ucLow, pulRate32);
            }
            else
            {
                NAS_ESM_EpsQosRateDecodeHighByte(ucHigh, pulRate32);
            }
        }
        else
        {
            NAS_ESM_EpsQosRateDecodeThirdByte(ucThird, pulRate32);
        }
    }
    else
    {
        if (NAS_ESM_NULL == ucHigh)
        {
            NAS_ESM_EpsQosRateDecodeLowByte(ucLow, pulRate32);
        }
        else
        {
            NAS_ESM_EpsQosRateDecodeHighByte(ucHigh, pulRate32);
        }
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodePcoIpItem
 Description     : ����PCO��Ԫ�е�IP���P-CSCF IPV4 ADDRESS��P-CSCF IPV6
                   ADDRESS��DNS SERVER IPV4 ADDRESS,DNS SERVER IPV6 ADDRESS
                   ��
 Input           : None
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-6-13  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoIpItem
(
    const VOS_UINT8                     *pucMsg,
    NAS_ESM_CONTEXT_IP_ADDR_STRU        *pstIpAddr
)
{
    VOS_UINT8                           ucItemLen = NAS_ESM_NULL;
    VOS_UINT32                          ulSum     = NAS_ESM_NULL;

    /* ��¼������IP��� */
    ucItemLen = pucMsg[ulSum++];

    if (ucItemLen == APP_MAX_IPV4_ADDR_LEN)
    {
        pstIpAddr->ucIpType = NAS_ESM_PDN_IPV4;

        NAS_ESM_MEM_CPY(pstIpAddr->aucIpV4Addr,
                        &pucMsg[ulSum],
                        APP_MAX_IPV4_ADDR_LEN);
    }
    else if (ucItemLen == APP_MAX_IPV6_ADDR_LEN)
    {
        pstIpAddr->ucIpType = NAS_ESM_PDN_IPV6;

        NAS_ESM_MEM_CPY(pstIpAddr->aucIpV6Addr,
                        &pucMsg[ulSum],
                        APP_MAX_IPV6_ADDR_LEN);
    }
    else
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DecodePcoIpItem:IP address length is illegal");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodePcoIpItem_ENUM, LNAS_PARAM_INVALID);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodePcoIpv4Item
 Description     : ����PCO��Ԫ�е�IP���P-CSCF IPV4 ADDRESS��P-CSCF IPV6
                   ADDRESS��DNS SERVER IPV4 ADDRESS,DNS SERVER IPV6 ADDRESS
                   ��
 Input           : None
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-6-13  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoIpv4Item
(
    const VOS_UINT8                     *pucMsg,
    NAS_ESM_IPV4_ADDR_STRU              *pstIpAddr
)
{
    VOS_UINT8                           ucItemLen = NAS_ESM_NULL;
    VOS_UINT32                          ulSum     = NAS_ESM_NULL;

    /* ��¼������IP��� */
    ucItemLen = pucMsg[ulSum++];

    if (ucItemLen == APP_MAX_IPV4_ADDR_LEN)
    {
        NAS_ESM_MEM_CPY(pstIpAddr->aucIpV4Addr,
                        &pucMsg[ulSum],
                        APP_MAX_IPV4_ADDR_LEN);
    }
    else
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_IPV4_LEN_INVALID,
                                        ucItemLen);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodePcoIpv4Item_ENUM, LNAS_PARAM_INVALID);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodePcoIpv6Item
 Description     : ����PCO��Ԫ�е�IP���P-CSCF IPV6 ADDRESS��DNS SERVER IPV6 ADDRESS
                   ��
 Input           : None
 Output          : None
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-6-13  Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoIpv6Item
(
    const VOS_UINT8                     *pucMsg,
    NAS_ESM_IPV6_ADDR_STRU              *pstIpAddr
)
{
    VOS_UINT8                           ucItemLen = NAS_ESM_NULL;
    VOS_UINT32                          ulSum     = NAS_ESM_NULL;

    /* ��¼������IP��� */
    ucItemLen = pucMsg[ulSum++];

    if (ucItemLen == APP_MAX_IPV6_ADDR_LEN)
    {
        NAS_ESM_MEM_CPY(pstIpAddr->aucIpV6Addr,
                        &pucMsg[ulSum],
                        APP_MAX_IPV6_ADDR_LEN);
    }
    else
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_IPV6_LEN_INVALID,
                                        ucItemLen);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodePcoIpv6Item_ENUM, LNAS_PARAM_INVALID);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoIpv6Dns
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_PCO_STRU           *pstPco,
    VOS_UINT32                         *pulSum,
    const NAS_ESM_IPV6_ADDR_STRU             *pstEmptyIpv6Addr
)
{
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_CAUSE_SUCCESS;

    /* DNS SERVER�洢���������������� */
    if (pstPco->ucIpv6DnsSerNum >= NAS_ESM_MAX_DNS_SERVER_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
        *pulSum = *pulSum + ulSum;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    enEsmCause = NAS_ESM_DecodePcoIpv6Item( &pucTmpMsg[ulSum],
                                            &pstPco->astIpv6DnsServer[pstPco->ucIpv6DnsSerNum]);
    if (NAS_ESM_CAUSE_SUCCESS == enEsmCause)
    {
        /* �����ȡ��IPv6 DNS����Ϊȫ�㣬���������޴�DNS��������DNS���� */
        if (NAS_ESM_MEM_CMP(&pstPco->astIpv6DnsServer[pstPco->ucIpv6DnsSerNum],
                            pstEmptyIpv6Addr,
                            sizeof(NAS_ESM_IPV6_ADDR_STRU)))
        {
            pstPco->ucIpv6DnsSerNum++;
        }
    }

    ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);

    *pulSum = *pulSum + ulSum;

    return NAS_ESM_CAUSE_SUCCESS;
}

NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoIpv4Dns
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_PCO_STRU           *pstPco,
    VOS_UINT32                         *pulSum,
    const NAS_ESM_IPV4_ADDR_STRU             *pstEmptyIpv4Addr
)
{
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_CAUSE_SUCCESS;

    /* DNS SERVER�洢���������������� */
    if (pstPco->ucIpv4DnsSerNum >= NAS_ESM_MAX_DNS_SERVER_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
        *pulSum += ulSum;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    enEsmCause = NAS_ESM_DecodePcoIpv4Item(&pucTmpMsg[ulSum], &pstPco->astIpv4DnsServer[pstPco->ucIpv4DnsSerNum]);
    if (NAS_ESM_CAUSE_SUCCESS == enEsmCause)
    {
        /* �����ȡ��IPv4 DNS����Ϊȫ�㣬���������޴�DNS��������DNS���� */
        if (NAS_ESM_MEM_CMP(&pstPco->astIpv4DnsServer[pstPco->ucIpv4DnsSerNum],
                            pstEmptyIpv4Addr,
                            sizeof(NAS_ESM_IPV4_ADDR_STRU)))
        {
            pstPco->ucIpv4DnsSerNum++;
        }
    }

    ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
    *pulSum += ulSum;
    return NAS_ESM_CAUSE_SUCCESS;
}


NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoIpv4Pcscf
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_PCO_STRU           *pstPco,
    VOS_UINT32                         *pulSum,
    const NAS_ESM_IPV4_ADDR_STRU             *pstEmptyIpv4Addr
)
{
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_CAUSE_SUCCESS;

    /* P-CSCF�洢���������������� */
    if (pstPco->ucIpv4PcscfNum >= NAS_ESM_MAX_PCSCF_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
        *pulSum += ulSum;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    enEsmCause = NAS_ESM_DecodePcoIpv4Item(&pucTmpMsg[ulSum], &pstPco->astIpv4Pcscf[pstPco->ucIpv4PcscfNum]);
    if (NAS_ESM_CAUSE_SUCCESS == enEsmCause)
    {
        /* lihong00150010 ims begin */
        /* �����ȡ��IPv4 P-CSCF����Ϊȫ�㣬���������޴�P-CSCF��������P-CSCF���� */
        if (NAS_ESM_MEM_CMP(&pstPco->astIpv4Pcscf[pstPco->ucIpv4PcscfNum],
                            pstEmptyIpv4Addr,
                            sizeof(NAS_ESM_IPV4_ADDR_STRU)))
        {
            pstPco->ucIpv4PcscfNum++;
        }
        /* lihong00150010 ims end */
    }

    ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
    *pulSum += ulSum;
    return NAS_ESM_CAUSE_SUCCESS;
}

NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoIpv6Pcscf
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_PCO_STRU           *pstPco,
    VOS_UINT32                         *pulSum,
    const NAS_ESM_IPV6_ADDR_STRU             *pstEmptyIpv6Addr
)
{
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_CAUSE_SUCCESS;

    /* P-CSCF�洢���������������� */
    if (pstPco->ucIpv6PcscfNum >= NAS_ESM_MAX_PCSCF_NUM)
    {
        ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
        *pulSum += ulSum;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    enEsmCause = NAS_ESM_DecodePcoIpv6Item(&pucTmpMsg[ulSum], &pstPco->astIpv6Pcscf[pstPco->ucIpv6PcscfNum]);
    if (NAS_ESM_CAUSE_SUCCESS == enEsmCause)
    {
        /* lihong00150010 ims begin */
        /* �����ȡ��IPv4 P-CSCF����Ϊȫ�㣬���������޴�P-CSCF��������P-CSCF���� */
        if (NAS_ESM_MEM_CMP(&pstPco->astIpv6Pcscf[pstPco->ucIpv6PcscfNum],
                            pstEmptyIpv6Addr,
                            sizeof(NAS_ESM_IPV6_ADDR_STRU)))
        {
            pstPco->ucIpv6PcscfNum++;
        }
        /* lihong00150010 ims end */
    }

    ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
    *pulSum += ulSum;
    return NAS_ESM_CAUSE_SUCCESS;
}

NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeLocalAddress
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_PCO_STRU           *pstPco,
    VOS_UINT32                         *pulSum
)
{
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;

    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_DecodeLocalAddress enter");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_DecodeLocalAddress_ENUM, LNAS_ENTRY);
        NAS_ESM_GetNwLocalIpSupFlag() = NAS_ESM_NW_LOCAL_IP_CAP_SUPPORT;

        ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
    }
    else
    {
        /* ������������ */
        ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
    }

    *pulSum += ulSum;

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodePcoBcm
 Description     : ����PCO��Ԫ�е�BCM
 Input           : pucMsg
 Output          : pstPco
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-04-27  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_DecodePcoBcm
(
    const VOS_UINT8                     *pucMsg,
    NAS_ESM_CONTEXT_PCO_STRU            *pstPco
)
{
    VOS_UINT8                           ucItemLen = NAS_ESM_NULL;
    VOS_UINT32                          ulSum     = NAS_ESM_NULL;

    /* ��¼������IP��� */
    ucItemLen = pucMsg[ulSum++];

    /* Э��涨BCM�����ݳ���Ϊ1������Ϊ1������Դ��� */
    if (1 != ucItemLen)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_BCM_LEN_INVALID,
                                        ucItemLen);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodePcoBcm_ENUM, LNAS_MSG_INVALID, 1);
        return ;
    }

    /* Э��涨BCM�ĺϷ�ֵΪSM_ESM_BCM_MS_ONLY��SM_ESM_BCM_MS_NW */
    if ((SM_ESM_BCM_MS_ONLY!= pucMsg[ulSum]) && (SM_ESM_BCM_MS_NW != pucMsg[ulSum]))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_BCM_TYPE_INVALID,
                                        pucMsg[ulSum]);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_DecodePcoBcm_ENUM, LNAS_MSG_INVALID, 2);
        return ;
    }

    pstPco->enBcm       = pucMsg[ulSum];
    pstPco->bitOpBcm    = NAS_ESM_OP_TRUE;
}
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidateIpcpLen
(
    const VOS_UINT8                    *pucMsg
)
{
    VOS_UINT8                           ucTmpLength         = NAS_ESM_NULL;
    const VOS_UINT8                    *pucTmpMsg           = pucMsg;
    VOS_UINT8                           ucSum               = NAS_ESM_NULL;

    /* ��ȡ�ܳ��� */
    ucTmpLength |= (VOS_UINT8)((pucTmpMsg[2] << 8));
    ucTmpLength |= pucTmpMsg[3];

    /* �ж��Ƿ���Զ�ȡ���� */
    if (ucTmpLength < (ucSum + NAS_ESM_IPCP_PACKET_HEAD_LEN))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_IPCP_LEN_INVALID,
                                        ucTmpLength);
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateIpcpLen_ENUM, LNAS_MSG_INVALID, 1);

        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    /* ����IPCP��ͷ���� */
    ucSum += NAS_ESM_IPCP_PACKET_HEAD_LEN;

    /* ͳ�����еĳ��� */
    while (ucTmpLength > ucSum)
    {
        /* �ж��Ƿ���Զ�ȡ���� */
        if (ucTmpLength < ((ucSum + NAS_ESM_IPCP_OPTION_HEAD_LEN) - 1))
        {
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                            ESM_DECODE_CN_MSG_IPCP_LEN_INVALID,
                                            ucTmpLength);
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateIpcpLen_ENUM, LNAS_MSG_INVALID, 2);

            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }

        /* �жϳ��Ȳ���Ϊ0��������ѭ�� */
        if (NAS_ESM_NULL == pucTmpMsg[(ucSum + NAS_ESM_IPCP_OPTION_HEAD_LEN) - 1])
        {
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                            ESM_DECODE_CN_MSG_IPCP_LEN_INVALID,
                                            pucTmpMsg[(ucSum + NAS_ESM_IPCP_OPTION_HEAD_LEN) - 1]);
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidateIpcpLen_ENUM, LNAS_MSG_INVALID, 3);

            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
        ucSum += pucTmpMsg[(ucSum + NAS_ESM_IPCP_OPTION_HEAD_LEN) -1];
    }

    /* �ж��ܳ����Ƿ���� */
    if (ucTmpLength != ucSum)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_IPCP_LEN_INVALID,
                                        ucTmpLength);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_IsIpcpTypeValid
 Description     : �ж�IPCP�����Ƿ�Ϸ�
 Input           : ucIpcpType       -- IPCP����
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-09-13  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_ESM_IsIpcpTypeValid
(
    VOS_UINT8                          ucIpcpType
)
{
    if((ucIpcpType == NAS_ESM_IPCP_OPTIONS_PRI_DNS_ADDR)
       ||(ucIpcpType == NAS_ESM_IPCP_OPTIONS_SEC_DNS_ADDR))
    {
        return NAS_ESM_SUCCESS;
    }

    return NAS_ESM_FAILURE;
}


VOS_UINT8 NAS_ESM_CheckIpv4AddrIsEmpty(const NAS_ESM_IPV4_ADDR_STRU *pstIpAddr)
{
    if ( (0 == pstIpAddr->aucIpV4Addr[0])
        && (0 == pstIpAddr->aucIpV4Addr[1])
        && (0 == pstIpAddr->aucIpV4Addr[2])
        && (0 == pstIpAddr->aucIpV4Addr[3]))
    {
        return PS_TRUE;
    }

    return PS_FALSE;

}

VOS_VOID NAS_ESM_OptimizeDnsServer
(
    NAS_ESM_CONTEXT_PCO_STRU            *pstPco
)
{
    VOS_UINT8          ucPriDnsNoExist = PS_TRUE;
    VOS_UINT8          ucSecDnsNoExist = PS_TRUE;

    ucPriDnsNoExist = NAS_ESM_CheckIpv4AddrIsEmpty(&(pstPco->astIpv4DnsServer[0]));
    ucSecDnsNoExist = NAS_ESM_CheckIpv4AddrIsEmpty(&(pstPco->astIpv4DnsServer[1]));

    if ((PS_TRUE == ucPriDnsNoExist) && (PS_FALSE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 1;
        NAS_ESM_MEM_CPY((VOS_VOID*)&(pstPco->astIpv4DnsServer[0]),
                        (VOS_VOID*)&(pstPco->astIpv4DnsServer[1]),
                        sizeof(NAS_ESM_IPV4_ADDR_STRU));
        return;
    }

    if ((PS_FALSE == ucPriDnsNoExist) && (PS_TRUE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 1;
        return;
    }

    if ((PS_TRUE == ucPriDnsNoExist) && (PS_TRUE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 0;
        return;
    }

    if ((PS_FALSE == ucPriDnsNoExist) && (PS_FALSE == ucSecDnsNoExist))
    {
        pstPco->ucIpv4DnsSerNum = 2;
        return;
    }

}


NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeIpcpOptionContent
(
    const VOS_UINT8                     *pucMsg,
    VOS_UINT32                          *pulSum,
    NAS_ESM_CONTEXT_PCO_STRU            *pstPco

)
{
    const VOS_UINT8                    *pucTmpMsg           = pucMsg;
    NAS_ESM_CAUSE_ENUM_UINT8            enRslt;
    VOS_UINT32                          ulOptionLen = NAS_ESM_NULL;
    VOS_UINT32                          ulTempSum = *pulSum;


    NAS_ESM_INFO_LOG1("NAS_ESM_DecodeIpcpOptionContent:configure-type:", pucMsg[*pulSum]);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_DecodeIpcpOptionContent_ENUM, LNAS_ENTRY, pucMsg[*pulSum]);

    /* ��鵱ǰ�Ŀ�ѡ���ܳ�����ȷ */
    enRslt = NAS_ESM_ValidateIpcpLen(pucMsg + ulTempSum);
    if (NAS_ESM_CAUSE_SUCCESS != enRslt)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_DecodeIpcpOptionContent:Lenth is illegal!");
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_DecodeIpcpOptionContent_ENUM, LNAS_MSG_INVALID, 1);

        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }


    /*�����IPCP option���� */
    ulOptionLen |= (VOS_UINT8)((pucTmpMsg[ulTempSum + 2] << 8));
    ulOptionLen |= pucTmpMsg[ulTempSum + 3];


    /* ����ͷ���ṹ */
    ulTempSum += NAS_ESM_IPCP_PACKET_HEAD_LEN;

    while (ulTempSum < (*pulSum + ulOptionLen))
    {
        switch (pucTmpMsg[ulTempSum])
        {
            /* ������DNS Server��Ϣ */
            case NAS_ESM_IPCP_OPTIONS_PRI_DNS_ADDR:

                /*����type�ֽ�*/
                ulTempSum++;

                /* �жϳ����Ƿ�Ϸ� */
                if (NAS_ESM_IPCP_OPTION_DNS_LEN != pucTmpMsg[ulTempSum])
                {
                    NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                                    ESM_DECODE_CN_MSG_IPCP_PRI_DNS_LEN_INVALID,
                                                    pucTmpMsg[ulTempSum]);
                    TLPS_PRINT2LAYER_INFO1(NAS_ESM_DecodeIpcpOptionContent_ENUM, LNAS_MSG_INVALID, 2);
                    *pulSum = ulTempSum;
                    return NAS_ESM_CAUSE_PROTOCOL_ERROR;
                }

                /*����length�ֽ�*/
                ulTempSum++;

                NAS_ESM_MEM_CPY((VOS_VOID*)pstPco->astIpv4DnsServer[0].aucIpV4Addr,
                                    (VOS_VOID*)&pucTmpMsg[ulTempSum],
                                    APP_MAX_IPV4_ADDR_LEN);


                /* ����IP��ַ */
                ulTempSum += APP_MAX_IPV4_ADDR_LEN;

                break;


            case NAS_ESM_IPCP_OPTIONS_SEC_DNS_ADDR:

                /*����type�ֽ�*/
                ulTempSum++;

                /* �жϳ����Ƿ�Ϸ� */
                if (NAS_ESM_IPCP_OPTION_DNS_LEN != pucTmpMsg[ulTempSum])
                {
                    NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                                    ESM_DECODE_CN_MSG_IPCP_SEC_DNS_LEN_INVALID,
                                                    pucTmpMsg[ulTempSum]);
                    TLPS_PRINT2LAYER_INFO1(NAS_ESM_DecodeIpcpOptionContent_ENUM, LNAS_MSG_INVALID, 3);
                    *pulSum = ulTempSum;
                    return NAS_ESM_CAUSE_PROTOCOL_ERROR;
                }

                /*����length�ֽ�*/
                ulTempSum++;

                NAS_ESM_MEM_CPY((VOS_VOID*)pstPco->astIpv4DnsServer[1].aucIpV4Addr,
                                                    (VOS_VOID*)&pucTmpMsg[ulTempSum],
                                                    APP_MAX_IPV4_ADDR_LEN);


                /* ����IP��ַ */
                ulTempSum += APP_MAX_IPV4_ADDR_LEN;

                break;

            default:
                /* �жϳ��Ȳ���Ϊ0��������ѭ�� */
                if (NAS_ESM_NULL == pucTmpMsg[ulTempSum + 1])
                {
                    *pulSum = ulTempSum;
                    NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                                    ESM_DECODE_CN_MSG_IPCP_OTHER_LEN_INVALID,
                                                    pucTmpMsg[ulTempSum + 1]);
                    return NAS_ESM_CAUSE_PROTOCOL_ERROR;
                }

                /* ������Ԫ���� */
                ulTempSum += pucTmpMsg[ulTempSum + 1];

                break;
        }
    }
    *pulSum = ulTempSum;
    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeIpcpContent
 Description     : ����IPCP������
IPCP
 0                   1                   2                   3
 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
|     Code      |  Identifier   |            Length             |
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| Options ...
+-+-+-+-+

IP:
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |     Type      |    Length     |           IP-Address
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
         IP-Address (cont)       |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

DNS Server Address
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |     Type      |    Length     |      Primary-NBNS-Address
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    Primary-NBNS-Address (cont)  |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

NBNS Server Address
  0                   1                   2                   3
  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 |     Type      |    Length     |      Secondary-NBNS-Address
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   Secondary-NBNS-Address (cont) |
 +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunbing49683      2010-7-15  Draft Enact
    2.yangfan00159566   2011-6-2   Modify

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeIpcpContent
(
    const VOS_UINT8                     *pucMsg,
    NAS_ESM_CONTEXT_PCO_STRU            *pstPco
)
{
    NAS_ESM_CAUSE_ENUM_UINT8            enRslt              = NAS_ESM_CAUSE_ERROR;
    VOS_UINT8                           ucTmpLength         = NAS_ESM_NULL;
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    const VOS_UINT8                    *pucTmpMsg           = pucMsg;

    /* ��ȡlength�� */
    ucTmpLength = pucTmpMsg[ulSum++];



    /* �ж��ܳ����Ƿ�Ϸ� */
    if (ucTmpLength < NAS_ESM_IPCP_PACKET_HEAD_LEN)
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_IPCP_LEN_INVALID,
                                        ucTmpLength);
        TLPS_PRINT2LAYER_INFO(NAS_ESM_DecodeIpcpContent_ENUM, LNAS_MSG_INVALID);

        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    while (ucTmpLength > (ulSum -1))
    {
        enRslt = NAS_ESM_DecodeIpcpOptionContent(pucTmpMsg, &ulSum, pstPco);
        if (NAS_ESM_CAUSE_SUCCESS != enRslt)
        {
            return enRslt;
        }
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ValidatePcoLen
 Description     : �ж�PCO��Ԫ���ȵĺϷ���
 Input           : pucMsg      -- �տ���Ϣ����
                   ucPcoLength -- PCO�ṹ����
 Output          : usDecodeLen -- Ҫ����ĳ���
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.lihong00150010      2010-09-13  Draft Enact
    2.chengmin00285307    2015-03-19  Mod For M Project

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_ValidatePcoLen
(
    const VOS_UINT8                    *pucMsg,
    VOS_UINT8                           ucPcoLength,
    VOS_UINT16                         *pusDecodeLen
)
{
    VOS_UINT8                           ucAllPcoLength  = NAS_ESM_NULL;
    VOS_UINT8                           ucPrePcoLength  = NAS_ESM_NULL;
    const VOS_UINT8                    *pTmp            = pucMsg;
    const VOS_UINT8                    *pucTemp         = VOS_NULL_PTR;

    /* ���PCO����Ϊ0���򷵻�ʧ�� */
    if (NAS_ESM_NULL == ucPcoLength)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidatePcoLen:Pco length is 0!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidatePcoLen_ENUM, LNAS_MSG_INVALID, 1);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    /* ���PCO��Ԫֻ��������Э����򷵻سɹ� */
    if (NAS_ESM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL == ucPcoLength)
    {
        *pusDecodeLen = NAS_ESM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL;
        return NAS_ESM_CAUSE_SUCCESS;
    }

    /* �жϳ����Ƿ�Ϸ� */
    if(ucPcoLength < (NAS_ESM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL + NAS_ESM_SUM_LEN_OF_ID_LEN))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ValidatePcoLen:Pco length is between (1,4)!");
        TLPS_PRINT2LAYER_WARNING1(NAS_ESM_ValidatePcoLen_ENUM, LNAS_MSG_INVALID, 2);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    pucTemp = &(pTmp[NAS_ESM_PCO_ITEM_LEN_OFFSET]);

    /* ��ȡ����packet filter��ռ���ֽ��� */
    ucPrePcoLength = pTmp[NAS_ESM_PCO_ITEM_LEN_OFFSET];
    ucAllPcoLength = ucPrePcoLength + (NAS_ESM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL
                                                    + NAS_ESM_SUM_LEN_OF_ID_LEN);
    /*���˴�����Ϊ�ɽ����ĳ���Ϊ1����������CONFIGURATION PROTOCOL*/
    *pusDecodeLen = NAS_ESM_PCO_LEN_ONLY_CONFIGURAION_PROTOCOL;

    while (ucPcoLength >= ucAllPcoLength)
    {
         *pusDecodeLen = ucAllPcoLength;
         /* �жϳ����Ƿ�Ϸ� */
         if ((ucAllPcoLength + NAS_ESM_SUM_LEN_OF_ID_LEN) > ucPcoLength)
         {
             break;
         }

         /* �ۼ���һ��ĳ��� */
         ucAllPcoLength =   ucAllPcoLength +
                            pucTemp[ucPrePcoLength + NAS_ESM_SUM_LEN_OF_ID_LEN]
                            + NAS_ESM_SUM_LEN_OF_ID_LEN;

         /* ��ָ��ָ����һ��ĳ�����Ԫ��λ�� */
         pucTemp = &(pucTemp[ucPrePcoLength + NAS_ESM_SUM_LEN_OF_ID_LEN]);

         /* ������һ��ĳ�����Ԫ��ֵ */
         ucPrePcoLength = *pucTemp;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodePcoContent
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    VOS_UINT32                          ulSum               = NAS_ESM_NULL;
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_CAUSE_SUCCESS;
    const VOS_UINT8                    *pucTmpMsg           = pucMsg;
    NAS_ESM_CONTEXT_PCO_STRU           *pstPco              = &pstMsgIE->stPcoInfo;
    VOS_UINT16                          usPcoItemId         = NAS_ESM_NULL;
    /* lihong00150010 ims begin */
    NAS_ESM_IPV6_ADDR_STRU              stEmptyIpv6Addr;
    NAS_ESM_IPV4_ADDR_STRU              stEmptyIpv4Addr;
    /* lihong00150010 ims end */

    PS_MEM_SET(&stEmptyIpv6Addr, 0, sizeof(NAS_ESM_IPV6_ADDR_STRU));
    PS_MEM_SET(&stEmptyIpv4Addr, 0, sizeof(NAS_ESM_IPV4_ADDR_STRU));
    /* ���PCO�����ѹرգ���ֱ������PCO���ݲ����سɹ� */
    if (NAS_ESM_PCO_OFF  == NAS_ESM_GetPcoFlag())
    {
        NAS_ESM_NORM_LOG("NAS_ESM_DecodePcoContent:PCO fuction is closed!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_DecodePcoContent_ENUM, 1);

        return NAS_ESM_SUCCESS;
    }

    /* �ж�PCOЯ����Э���Ƿ���ȷ */
    if (NAS_ESM_PCO_CONFIG_PROTOCOL != (pucTmpMsg[ulSum++] & NAS_ESM_HIGH_5_BIT_MASK))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_PCO_CONFIG_PROTOCOL_INVALID,
                                        (pucTmpMsg[ulSum-1] & NAS_ESM_HIGH_5_BIT_MASK));
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodePcoContent_ENUM, LNAS_MSG_INVALID);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    NAS_ESM_MEM_SET(&stEmptyIpv6Addr, NAS_ESM_NULL, sizeof(NAS_ESM_IPV6_ADDR_STRU));
    NAS_ESM_MEM_SET(&stEmptyIpv4Addr, NAS_ESM_NULL, sizeof(NAS_ESM_IPV4_ADDR_STRU));

    /* ��һ����PCO��Я���ĸ������� */
    while (usMsgLen > ulSum)
    {
        usPcoItemId = ((VOS_UINT16)pucTmpMsg[ulSum++] << NAS_ESM_MOVEMENT_8_BITS);
        usPcoItemId = usPcoItemId | (pucTmpMsg[ulSum++]);

        switch (usPcoItemId)
        {
            case NAS_ESM_PCO_ITEM_TYPE_DNS_SERVER_IPV6:
                enEsmCause= NAS_ESM_DecodePcoIpv6Dns(&pucTmpMsg[ulSum],
                                                    pstPco,
                                                    &ulSum,
                                                    &stEmptyIpv6Addr);

                if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
                {
                    return enEsmCause;
                }
                break;
            case NAS_ESM_PCO_ITEM_TYPE_PCSCF_IPV4:

                enEsmCause = NAS_ESM_DecodePcoIpv4Pcscf(&pucTmpMsg[ulSum],
                                                        pstPco,
                                                        &ulSum,
                                                        &stEmptyIpv4Addr);
                if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
                {
                    return enEsmCause;
                }
                break;
            case NAS_ESM_PCO_ITEM_TYPE_BCM:
                NAS_ESM_DecodePcoBcm(&pucTmpMsg[ulSum], pstPco);
                ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
                break;

            case NAS_ESM_PCO_ITEM_TYPE_DNS_SERVER_IPV4:

                enEsmCause = NAS_ESM_DecodePcoIpv4Dns(&pucTmpMsg[ulSum],
                                                        pstPco,
                                                        &ulSum,
                                                        &stEmptyIpv4Addr);
                if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
                {
                    return enEsmCause;
                }
                break;

            case NAS_ESM_PCO_ITEM_TYPE_IPCP:
                /*LV��ʽ����*/
                (VOS_VOID)NAS_ESM_DecodeIpcpContent(&pucTmpMsg[ulSum],pstPco);
                ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
                break;

            /* lihong00150010 ims begin */
            case NAS_ESM_PCO_ITEM_TYPE_PCSCF_IPV6:

                enEsmCause = NAS_ESM_DecodePcoIpv6Pcscf(&pucTmpMsg[ulSum],
                                                        pstPco,
                                                        &ulSum,
                                                        &stEmptyIpv6Addr);
                if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
                {
                    return enEsmCause;
                }
                break;
            case NAS_ESM_PCO_ITEM_TYPE_IM_CN_SIGNAL_FLAG:
                pstPco->bitOpImsCnSignalFlag = NAS_ESM_OP_TRUE;
                pstPco->enImsCnSignalFlag = APP_ESM_PDP_FOR_IMS_CN_SIG_ONLY;
                ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
                break;
            /* lihong00150010 ims end */
            case NAS_ESM_PCO_ITEM_TYPE_LOCAL_ADDRESS:
                (VOS_VOID)NAS_ESM_DecodeLocalAddress(&pucTmpMsg[ulSum],
                                                    pstPco,
                                                    &ulSum);
                break;
            default:

                /* ������������ */
                ulSum += (pucTmpMsg[ulSum] + NAS_ESM_LEN_IE_OCTETS);
                break;
        }
    }
    /*���µ���DNS */
    NAS_ESM_OptimizeDnsServer(pstPco);


    return NAS_ESM_CAUSE_SUCCESS;
}
/*lint -e415 -e416 -e661 -e662*/
NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeNwPco
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    NAS_ESM_CAUSE_ENUM_UINT8            enEsmCause          = NAS_ESM_CAUSE_SUCCESS;
    VOS_UINT16                          usDecodeLen;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_DecodeNwPco is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DecodeNwPco_ENUM, LNAS_ENTRY);

    enEsmCause = NAS_ESM_ValidatePcoLen(pucMsg,(VOS_UINT8)usMsgLen,&usDecodeLen);
    if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
    {
        /*������Ϣ���ʧ��*/
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PCO_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        usMsgLen);
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeNwPco_ENUM, LNAS_FAIL);
        return enEsmCause;
    }

    enEsmCause = NAS_ESM_DecodePcoContent(usDecodeLen, pucMsg, pstMsgIE);
    if (NAS_ESM_CAUSE_SUCCESS != enEsmCause)
    {
        return enEsmCause;
    }

    pstMsgIE->bitOpPco = NAS_ESM_OP_TRUE;

    return NAS_ESM_CAUSE_SUCCESS;
}/*lint +e415 +e416 +e661 +e662*/


NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNwPDNValue
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    VOS_UINT32                          ulSum            = NAS_ESM_NULL;
    const VOS_UINT8                    *pucTmpMsg        = pucMsg;
    NAS_ESM_CONTEXT_IP_ADDR_STRU       *pstPDNInfo       = &pstMsgIE->stPdnAddrInfo;

    (VOS_VOID)usMsgLen;



    /*�ڴ�ռ��ʼ��*/
    NAS_ESM_MEM_SET((VOS_VOID*)pstPDNInfo, 0, sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

    /*����PDN��ַ����*/
    pstPDNInfo->ucIpType = pucTmpMsg[ulSum++];

    switch(pstPDNInfo->ucIpType)
    {
        /*�����IPV4���͵�ַ���򱣴棬IPV4��ַ��4���ֽ�*/
        case NAS_ESM_PDN_IPV4:
            NAS_ESM_MEM_CPY(pstPDNInfo->aucIpV4Addr, &pucTmpMsg[ulSum], APP_MAX_IPV4_ADDR_LEN);
            break;

        /*�����IPV6���͵�ַ���򱣴棬IPV4��ַ��16���ֽ�,����*/
        case NAS_ESM_PDN_IPV6:
            /*���IPV6��ʽ�ĵ�ַ*/
            NAS_ESM_MEM_CPY(pstPDNInfo->aucIpV6Addr + NAS_ESM_IPV6_IF_OFFSET, \
                            &pucTmpMsg[ulSum], NAS_ESM_IPV6_IF_LEN);
            break;

        /*���֧��IPV4��IPV6��ַ����λ���棬����*/
        case NAS_ESM_PDN_IPV4_IPV6:
            /*���δ��IPV4��IPV6��ַ*/
            NAS_ESM_MEM_CPY(pstPDNInfo->aucIpV6Addr + NAS_ESM_IPV6_IF_OFFSET, \
                &pucTmpMsg[ulSum], NAS_ESM_IPV6_IF_LEN);
            NAS_ESM_MEM_CPY(pstPDNInfo->aucIpV4Addr, &pucTmpMsg[ulSum+NAS_ESM_IPV6_IF_LEN], APP_MAX_IPV4_ADDR_LEN);

            break;
        default:
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_PDN_IE,
                                            ESM_DECODE_CN_MSG_IP_TYPE_INVALID,
                                            pstPDNInfo->ucIpType);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeNwPDNValue_ENUM, LNAS_PARAM_INVALID);
            NAS_ESM_MEM_SET((VOS_VOID*)pstPDNInfo,
                             0,
                             sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    pstMsgIE->bitOpPdnAddr  = NAS_ESM_OP_TRUE;

    return NAS_ESM_CAUSE_SUCCESS;
}
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNwAPNValue
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    VOS_UINT32                          ulRslt           = NAS_ESM_CAUSE_SUCCESS;
    const VOS_UINT8                    *pucTmpMsg        = pucMsg;
    NAS_ESM_CONTEXT_APN_STRU            stTmpAPNInfo;

    /*��¼APN�ĳ���,����APN�ĳ���*/
    stTmpAPNInfo.ucApnLen = (VOS_UINT8)((usMsgLen)&0xFF);

    NAS_ESM_MEM_CPY(    stTmpAPNInfo.aucApnName,
                        &pucTmpMsg[0],
                        stTmpAPNInfo.ucApnLen);

    /* ����APN */
    ulRslt = NAS_ESM_ApnReverseTransformation(&pstMsgIE->stApnInfo, &stTmpAPNInfo);

    if(NAS_ESM_SUCCESS != ulRslt)
    {
        /*��ӡ�쳣��Ϣ*/
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    pstMsgIE->bitOpApn = NAS_ESM_OP_TRUE;

    return NAS_ESM_CAUSE_SUCCESS;
}
VOS_VOID NAS_ESM_SdfQosUlMaxRateTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulULMaxRateTmp   = NAS_ESM_NULL;

    ulULMaxRateTmp = *pucTmpMsg;
    (*pulIndex)++;
    NAS_ESM_EpsQosRateDecodeTo32(ulULMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulULMaxRate);
}
VOS_VOID NAS_ESM_SdfQosDlMaxRateTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulDLMaxRateTmp   = NAS_ESM_NULL;

    ulDLMaxRateTmp = *pucTmpMsg;
    (*pulIndex)++;
    NAS_ESM_EpsQosRateDecodeTo32(ulDLMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulDLMaxRate);
}
VOS_VOID NAS_ESM_SdfQosUlGMaxRateTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulULGMaxRateTmp   = NAS_ESM_NULL;

    ulULGMaxRateTmp = *pucTmpMsg;
    (*pulIndex)++;
    NAS_ESM_EpsQosRateDecodeTo32(ulULGMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulULGMaxRate);
}
VOS_VOID NAS_ESM_SdfQosDlGMaxRateTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulDLGMaxRateTmp   = NAS_ESM_NULL;

    ulDLGMaxRateTmp = *pucTmpMsg;
    (*pulIndex)++;
    NAS_ESM_EpsQosRateDecodeTo32(ulDLGMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulDLGMaxRate);
}
VOS_VOID NAS_ESM_SdfQosUlMaxRateExtTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulULMaxRateTmp   = NAS_ESM_NULL;

    ulULMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_8_BITS;
    (*pulIndex)++;
    if (NAS_ESM_NULL != ulULMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulULMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulULMaxRate);
    }
}

VOS_VOID NAS_ESM_SdfQosDlMaxRateExtTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulDLMaxRateTmp   = NAS_ESM_NULL;

    ulDLMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_8_BITS;
    (*pulIndex)++;

    if (NAS_ESM_NULL != ulDLMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulDLMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulDLMaxRate);
    }
}
VOS_VOID NAS_ESM_SdfQosUlGMaxRateExtTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulULGMaxRateTmp   = NAS_ESM_NULL;

    ulULGMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_8_BITS;
    (*pulIndex)++;
    if (NAS_ESM_NULL != ulULGMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulULGMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulULGMaxRate);
    }
}
VOS_VOID NAS_ESM_SdfQosDlGMaxRateExtTran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulDLGMaxRateTmp   = NAS_ESM_NULL;

    ulDLGMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_8_BITS;
    (*pulIndex)++;
    if (NAS_ESM_NULL != ulDLGMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulDLGMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulDLGMaxRate);
    }
}
VOS_VOID NAS_ESM_SdfQosUlMaxRateExt2Tran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulULMaxRateTmp   = NAS_ESM_NULL;

    ulULMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_16_BITS;
    (*pulIndex)++;
    if (NAS_ESM_NULL != ulULMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulULMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulULMaxRate);
    }
}

VOS_VOID NAS_ESM_SdfQosDlMaxRateExt2Tran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulDLMaxRateTmp   = NAS_ESM_NULL;

    ulDLMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_16_BITS;
    (*pulIndex)++;

    if (NAS_ESM_NULL != ulDLMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulDLMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulDLMaxRate);
    }
}
VOS_VOID NAS_ESM_SdfQosUlGMaxRateExt2Tran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulULGMaxRateTmp   = NAS_ESM_NULL;

    ulULGMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_16_BITS;
    (*pulIndex)++;
    if (NAS_ESM_NULL != ulULGMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulULGMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulULGMaxRate);
    }
}
VOS_VOID NAS_ESM_SdfQosDlGMaxRateExt2Tran
(
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulDLGMaxRateTmp   = NAS_ESM_NULL;

    ulDLGMaxRateTmp |= ((VOS_UINT32)*pucTmpMsg) << NAS_ESM_MOVEMENT_16_BITS;
    (*pulIndex)++;
    if (NAS_ESM_NULL != ulDLGMaxRateTmp)
    {
        NAS_ESM_EpsQosRateDecodeTo32(ulDLGMaxRateTmp, &pstTmpSdfQosInfo->stQosInfo.ulDLGMaxRate);
    }
}
VOS_VOID NAS_ESM_TFT_DecodePfCopTypeIpv4LocalAddr
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
#if (FEATURE_ON == FEATURE_LTE_NAS_R11)
    NAS_ESM_DecodeIpv4LocalAddr(pstTFTInfo, pucTFTMsg, pucCnt);
#endif
    return;
}


VOS_VOID NAS_ESM_TFT_DecodePfCopTypeIpv6LocalAddr
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
#if (FEATURE_ON == FEATURE_LTE_NAS_R11)
    NAS_ESM_DecodeIpv6LocalAddr(pstTFTInfo, pucTFTMsg, pucCnt);
#endif
    return;
}


VOS_VOID NAS_ESM_TFT_DecodePfCopTypeIpv4Addr
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpRmtIpv4AddrAndMask = NAS_ESM_OP_TRUE;
    pstTFTInfo->aucRmtIpv4Address[0]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv4Address[1]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv4Address[2]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv4Address[3]    = pucTFTMsg[(*pucCnt)++];

    pstTFTInfo->aucRmtIpv4Mask[0]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv4Mask[1]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv4Mask[2]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv4Mask[3]       = pucTFTMsg[(*pucCnt)++];
    return;

}


VOS_VOID NAS_ESM_TFT_DecodePfCopTypeIpv6Addr
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpRmtIpv6AddrAndMask = NAS_ESM_OP_TRUE;
    pstTFTInfo->aucRmtIpv6Address[0]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[1]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[2]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[3]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[4]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[5]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[6]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[7]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[8]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[9]    = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[10]   = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[11]   = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[12]   = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[13]   = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[14]   = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Address[15]   = pucTFTMsg[(*pucCnt)++];

    pstTFTInfo->aucRmtIpv6Mask[0]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[1]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[2]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[3]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[4]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[5]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[6]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[7]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[8]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[9]       = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[10]      = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[11]      = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[12]      = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[13]      = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[14]      = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->aucRmtIpv6Mask[15]      = pucTFTMsg[(*pucCnt)++];

    return;
}


VOS_VOID NAS_ESM_TFT_DecodePfCopTypeProtocolId
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpProtocolId = NAS_ESM_OP_TRUE;
    pstTFTInfo->ucProtocolId    = pucTFTMsg[(*pucCnt)++];

    return;
}


VOS_VOID NAS_ESM_TFT_DecodePfCopTypeSingleLocalPort
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpSingleLocalPort = NAS_ESM_OP_TRUE;
    pstTFTInfo->usSingleLcPort       = (VOS_UINT16)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->usSingleLcPort      |= pucTFTMsg[(*pucCnt)++];

    return;
}


VOS_VOID NAS_ESM_TFT_DecodePfCopTypeLocalPortRange
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpLocalPortRange = NAS_ESM_OP_TRUE;
    pstTFTInfo->usLcPortLowLimit    = (VOS_UINT16)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->usLcPortLowLimit   |= pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->usLcPortHighLimit   = (VOS_UINT16)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->usLcPortHighLimit  |= pucTFTMsg[(*pucCnt)++];

    return;
}


VOS_VOID NAS_ESM_TFT_DecodePfCopTypeSingleRemotePort
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpSingleRemotePort = NAS_ESM_OP_TRUE;
    pstTFTInfo->usSingleRmtPort       = (VOS_UINT16)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->usSingleRmtPort      |= pucTFTMsg[(*pucCnt)++];

    return;
}


VOS_VOID NAS_ESM_TFT_DecodePfCopTypeRemotePortRange
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpRemotePortRange  = NAS_ESM_OP_TRUE;
    pstTFTInfo->usRmtPortLowLimit     = (VOS_UINT16)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->usRmtPortLowLimit    |= pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->usRmtPortHighLimit    = (VOS_UINT16)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->usRmtPortHighLimit   |= pucTFTMsg[(*pucCnt)++];

    return;
}


VOS_VOID NAS_ESM_TFT_DecodePfCopTypeSpi
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpSecuParaIndex = NAS_ESM_OP_TRUE;

    /*lint -e701*/
    pstTFTInfo->ulSecuParaIndex    = (VOS_UINT32)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_24_BITS);
    /*lint +e701*/

    pstTFTInfo->ulSecuParaIndex   |= (pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_16_BITS);
    pstTFTInfo->ulSecuParaIndex   |= (pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->ulSecuParaIndex   |=  pucTFTMsg[(*pucCnt)++];

    return;
}


VOS_VOID NAS_ESM_TFT_DecodePfCopTypeTos
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpTypeOfService  = NAS_ESM_OP_TRUE;
    pstTFTInfo->ucTypeOfService     = pucTFTMsg[(*pucCnt)++];
    pstTFTInfo->ucTypeOfServiceMask = pucTFTMsg[(*pucCnt)++];

    return;
}


VOS_VOID NAS_ESM_TFT_DecodePfCopTypeFlowLable
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucCnt
)
{
    pstTFTInfo->bitOpFlowLabelType = NAS_ESM_OP_TRUE;
    pstTFTInfo->ulFlowLabelType    = (VOS_UINT32)(pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_16_BITS);
    pstTFTInfo->ulFlowLabelType   |= (pucTFTMsg[(*pucCnt)++] << NAS_ESM_MOVEMENT_8_BITS);
    pstTFTInfo->ulFlowLabelType   |= pucTFTMsg[(*pucCnt)++];

    return;
}



NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_SdfQosRateTran
(
    VOS_UINT8                           ucTmpLength,
    const VOS_UINT8                    *pucTmpMsg,
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          ulSum            = NAS_ESM_NULL;
    VOS_UINT8                           ucCnt            = NAS_ESM_NULL;
    NAS_ESM_DECODE_QOSRATE_FUN          pDecodeRateActFun;

    ulSum = ucTmpLength - 1;

    for (ucCnt = 0; ucCnt < g_EsmDecodeQosRateTableSize; ucCnt++ )
    {
        if (ucTmpLength == g_EsmDecodeQosRateTable[ucCnt].enQosRate)
        {
            pDecodeRateActFun = g_EsmDecodeQosRateTable[ucCnt].pfDecodeFun;

            /* �д����� */
            if (VOS_NULL_PTR != pDecodeRateActFun)
            {
                (pDecodeRateActFun)(&pucTmpMsg[ulSum],pstTmpSdfQosInfo,pulIndex);
            }
            return NAS_ESM_CAUSE_SUCCESS;
        }
    }

    NAS_ESM_WARN_LOG("NAS_ESM_SdfQosRateTran:WARNING:Illegal Qos Offset!");
    TLPS_PRINT2LAYER_WARNING(NAS_ESM_SdfQosRateTran_ENUM, LNAS_MSG_INVALID);
    return NAS_ESM_CAUSE_PROTOCOL_ERROR;

}
VOS_VOID NAS_ESM_MapNwQciToStandardQci
(
    NAS_ESM_CONTEXT_LTE_QOS_STRU               *pstQosInfo,
    VOS_UINT8                                   ucQosLength
)
{
    if ((pstQosInfo->ucNwQCI >= NAS_ESM_QCI_TYPE_QCI1_GBR)
     && (pstQosInfo->ucNwQCI <= NAS_ESM_QCI_TYPE_QCI9_NONGBR))
    {
        /* ���QCI��1~9֮����ô�����QCI���Ǳ�׼��QCI */
        pstQosInfo->stQosInfo.ucQCI = pstQosInfo->ucNwQCI;
    }
    else if (NAS_ESM_QOS_LEN_ONLY_QCI == ucQosLength)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_MapNwQciToStandardQci:network QCI is NO_GBR QCI.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_MapNwQciToStandardQci_ENUM, 1);

        /* ���Qos�ĳ��� ����3����ô����QCI��NO_GBR��QOS */
        pstQosInfo->stQosInfo.ucQCI = NAS_ESM_QCI_TYPE_QCI6_NONGBR;
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_MapNwQciToStandardQci:network QCI is GBR QCI.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_MapNwQciToStandardQci_ENUM, 2);
        pstQosInfo->stQosInfo.ucQCI = NAS_ESM_QCI_TYPE_QCI2_GBR;
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_CheckNwSdfQosLen
 Description     : ��֤QOS ���ȵĺϷ���
 Input           : VOS_UINT32 ulMsgLen
 Output          : VOS_UINT32 *ulDecodeLen
 Return          : NAS_ESM_CAUSE_ENUM_UINT8

 History         :
    1.chengmin00285307 2015-3-25 Draft Enact

*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_CheckNwSdfQosLen
(
    VOS_UINT16                           usMsgLen,
    VOS_UINT16                          *ulDecodeLen
)
{
    /* �ǲ��Կ�����Ҫ�ϸ��鳤��*/
    if (PS_SUCC == LPS_OM_IsTestMode())
    {
        if ((usMsgLen != NAS_ESM_QOS_LEN_ONLY_QCI)
            && (usMsgLen != NAS_ESM_QOS_LEN_NO_EXT)
            && (usMsgLen != NAS_ESM_QOS_LEN_ALL_QOS)
            && (usMsgLen != NAS_ESM_QOS_LEN_ALL_WITH_EXT2))
        {
            /*������Ϣ���ʧ��*/
            NAS_ESM_WARN_LOG( "NAS_ESM_CheckNwSdfQosLen:QOS length is not 1,5,9,13.");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_CheckNwSdfQosLen_ENUM, LNAS_PARAM_INVALID);
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
        *ulDecodeLen = usMsgLen;
    }
    else
    {
        if (usMsgLen >= NAS_ESM_QOS_LEN_ALL_WITH_EXT2)
        {
            *ulDecodeLen = NAS_ESM_QOS_LEN_ALL_WITH_EXT2;
        }
        else if (usMsgLen >= NAS_ESM_QOS_LEN_ALL_QOS)
        {
            *ulDecodeLen = NAS_ESM_QOS_LEN_ALL_QOS;
        }
        else if (usMsgLen >= NAS_ESM_QOS_LEN_NO_EXT)
        {
            *ulDecodeLen = NAS_ESM_QOS_LEN_NO_EXT;
        }
        else if (usMsgLen >= NAS_ESM_QOS_LEN_ONLY_QCI)
        {
            *ulDecodeLen = NAS_ESM_QOS_LEN_ONLY_QCI;
        }
        else/*����С��1*/
        {
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
    }
    return NAS_ESM_CAUSE_SUCCESS;
}
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNwSdfQosValue
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    VOS_UINT32                          ulSum            = NAS_ESM_NULL;
    VOS_UINT8                           ucCnt            = NAS_ESM_NULL;
    const VOS_UINT8                    *pucTmpMsg        = pucMsg;
    NAS_ESM_CONTEXT_LTE_QOS_STRU       *pstTmpSdfQosInfo = VOS_NULL_PTR;
    VOS_UINT16                           ucLoop;

    if (NAS_ESM_CAUSE_SUCCESS != NAS_ESM_CheckNwSdfQosLen(usMsgLen, &ucLoop))
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_EPS_QOS_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        usMsgLen);
        return NAS_ESM_CAUSE_PROTOCOL_ERROR;
    }

    pstTmpSdfQosInfo = &pstMsgIE->stSdfQosInfo;

    pstTmpSdfQosInfo->ucNwQCI = pucTmpMsg[ulSum++];

    NAS_ESM_MapNwQciToStandardQci(pstTmpSdfQosInfo,(VOS_UINT8)ucLoop);

    pucTmpMsg = pucTmpMsg + ulSum;

    ulSum = 0;

    /* ��GBR QOS ����ULMaxRate��DLMaxRateʱ*/
    /* �����ǲ���ͬʱΪ0�����򷵻ش���*/
    if(ucLoop > 2)
    {
        if (NAS_ESM_QOS_IS_NULL_RATE(pucTmpMsg[ulSum])
         && NAS_ESM_QOS_IS_NULL_RATE(pucTmpMsg[ulSum+1])
         && (PS_TRUE == NAS_ESM_IsGbrBearer(pstTmpSdfQosInfo->stQosInfo.ucQCI)))
        {
            NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_EPS_QOS_IE,
                                            ESM_DECODE_CN_MSG_QOS_RATE_0,
                                            pstTmpSdfQosInfo->stQosInfo.ucQCI);
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeNwSdfQosValue_ENUM, LNAS_PARAM_INVALID);
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
    }

    for(ucCnt = 1; ucCnt < ucLoop; ucCnt++)
    {
        (VOS_VOID)NAS_ESM_SdfQosRateTran(ucCnt,pucTmpMsg,pstTmpSdfQosInfo,&ulSum);
    }

    pstMsgIE->bitOpEpsQos = NAS_ESM_OP_TRUE;

    return NAS_ESM_CAUSE_SUCCESS;

}


NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_CheckNwApnAmbr
(
    VOS_UINT16                           ulMsgLen,
    VOS_UINT16                          *ulDecodeLen
)
{
    /* �ǲ��Կ�����Ҫ�ϸ��鳤��*/
    if (PS_SUCC == LPS_OM_IsTestMode())
    {
        /*�ж�APN AMBR�����Ƿ����Э��*/
        if ((ulMsgLen != NAS_ESM_APN_AMBR_LEN_NO_EXT)
         && (ulMsgLen != NAS_ESM_APN_AMBR_LEN_EXT1)
         && (ulMsgLen != NAS_ESM_APN_AMBR_LEN_EXT2))
        {
            /*������Ϣ���ʧ��*/
            NAS_ESM_WARN_LOG( "NAS_ESM_CheckNwApnAmbr:APN AMBR decode Err!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_CheckNwApnAmbr_ENUM, LNAS_PARAM_INVALID, 1);
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
        *ulDecodeLen = ulMsgLen;
    }
    else
    {
        if (ulMsgLen >= NAS_ESM_APN_AMBR_LEN_EXT2)
        {
            *ulDecodeLen = NAS_ESM_APN_AMBR_LEN_EXT2;
        }
        else if (ulMsgLen >= NAS_ESM_APN_AMBR_LEN_EXT1)
        {
            *ulDecodeLen = NAS_ESM_APN_AMBR_LEN_EXT1;
        }
        else if (ulMsgLen >= NAS_ESM_APN_AMBR_LEN_NO_EXT)
        {
            *ulDecodeLen = NAS_ESM_APN_AMBR_LEN_NO_EXT;
        }
        else
        {
            /*������Ϣ���ʧ��*/
            NAS_ESM_WARN_LOG( "NAS_ESM_CheckNwApnAmbr:APN AMBR decode Err!");
            TLPS_PRINT2LAYER_WARNING1(NAS_ESM_CheckNwApnAmbr_ENUM, LNAS_PARAM_INVALID, 2);
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
    }
    return NAS_ESM_CAUSE_SUCCESS;
}


NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeNwApnAmbrValue
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    VOS_UINT32                          ulSum  = NAS_ESM_NULL;
    VOS_UINT16                          usLoop;
    NAS_ESM_CAUSE_ENUM_UINT8            enRslt              = NAS_ESM_CAUSE_SUCCESS;
    NAS_ESM_CONTEXT_APN_AMBR_STRU      *pstApnAmbrInfo      = &pstMsgIE->stApnAmbrInfo;
    VOS_UINT16                          ulToDecodeLen;

    enRslt = NAS_ESM_CheckNwApnAmbr(usMsgLen,&ulToDecodeLen);

    if ( NAS_ESM_CAUSE_SUCCESS != enRslt )
    {
        NAS_ESM_SndOmLogCnMsgDecodeFail(NAS_ESM_CN_MSG_APN_AMBR_IE,
                                        ESM_DECODE_CN_MSG_IE_LEN_INVALID,
                                        usMsgLen);
        return enRslt;
    }

    for(usLoop = 0; usLoop < ulToDecodeLen; usLoop++)
    {
        switch(usLoop)
        {
            case NAS_ESM_APN_AMBR_OFFSET_DLRATE:
                pstApnAmbrInfo->ucDLApnAmbr = pucMsg[ulSum++];
                break;
            case NAS_ESM_APN_AMBR_OFFSET_ULRATE:
                pstApnAmbrInfo->ucULApnAmbr = pucMsg[ulSum++];
                break;
            case NAS_ESM_APN_AMBR_OFFSET_DLEXT1:
                pstApnAmbrInfo->bitOpDLApnAmbrExt = NAS_ESM_OP_TRUE;
                pstApnAmbrInfo->ucDLApnAmbrExt = pucMsg[ulSum++];
                break;
            case NAS_ESM_APN_AMBR_OFFSET_ULEXT1:
                pstApnAmbrInfo->bitOpULApnAmbrExt = NAS_ESM_OP_TRUE;
                pstApnAmbrInfo->ucULApnAmbrExt = pucMsg[ulSum++];
                break;
            case NAS_ESM_APN_AMBR_OFFSET_DLEXT2:
                pstApnAmbrInfo->bitOpDLApnAmbrExt2 = NAS_ESM_OP_TRUE;
                pstApnAmbrInfo->ucDLApnAmbrExt2 = pucMsg[ulSum++];
                break;
            case NAS_ESM_APN_AMBR_OFFSET_ULEXT2:
                pstApnAmbrInfo->bitOpULApnAmbrExt2 = NAS_ESM_OP_TRUE;
                pstApnAmbrInfo->ucULApnAmbrExt2 = pucMsg[ulSum++];
                break;

            default:
                NAS_ESM_WARN_LOG("NAS_ESM_DecodeNwApnAmbrValue:WARNING:Illegal APN-AMBR Offset!");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeNwApnAmbrValue_ENUM, LNAS_MSG_INVALID);
                return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }
    }

    pstMsgIE->bitOpApnAmbr = NAS_ESM_OP_TRUE;

    return NAS_ESM_CAUSE_SUCCESS;
}


NAS_ESM_CAUSE_ENUM_UINT8  NAS_ESM_DecodeEsmCause
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    (VOS_VOID)usMsgLen;
    pstMsgIE->bitOpEsmCause = NAS_ESM_OP_TRUE;
    pstMsgIE->enEsmCau      = pucMsg[0];

    /* xiongxianghui00253310 modify for ftmerrlog begin */
    #if (FEATURE_PTM == FEATURE_ON)
    NAS_ESM_GetFtmInfoEsmCause() = pstMsgIE->enEsmCau;
    #endif
    /* xiongxianghui00253310 modify for ftmerrlog end  */

    return NAS_ESM_CAUSE_SUCCESS;
}



NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeAddOneFilterTFTCheckItemLen
(
    VOS_UINT8                     ucItemId,
    VOS_UINT8                     usMsgLen
)
{
    VOS_UINT16                usLoop;
    VOS_UINT8                 ucLen = NAS_ESM_NULL;

    if (usMsgLen < 1)
    {
        return NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER;
    }


    for (usLoop=0; usLoop<g_EsmPFComponentTypeLenTableSize; ++usLoop)
    {
        if (ucItemId == g_EsmPFComponentTypeLenTable[usLoop].ucType)
        {
            ucLen = g_EsmPFComponentTypeLenTable[usLoop].ucLen;
            break;
        }
    }

    if (ucLen == NAS_ESM_NULL || ucLen+1 > usMsgLen)
    {
        return NAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}




#if (FEATURE_ON == FEATURE_LTE_NAS_R11)
VOS_VOID NAS_ESM_DecodeIpv4LocalAddr
(
    NAS_ESM_CONTEXT_TFT_STRU            *pstTFTInfo,
    const VOS_UINT8                     *pTmp,
    VOS_UINT8                           *pucIndex
)
{
    VOS_UINT8                          ucCnt = *pucIndex;

    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
            NAS_ESM_WARN_LOG("NAS_ESM_DecodeIpv4LocalAddr- DECODE!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeIpv4LocalAddr_ENUM, LNAS_ENTRY);
            pstTFTInfo->bitOpLocalIpv4AddrAndMask = NAS_ESM_OP_TRUE;
            pstTFTInfo->aucLocalIpv4Addr[0] = pTmp[ucCnt++ ];
            pstTFTInfo->aucLocalIpv4Addr[1] = pTmp[ucCnt++ ];
            pstTFTInfo->aucLocalIpv4Addr[2] = pTmp[ucCnt++ ];
            pstTFTInfo->aucLocalIpv4Addr[3] = pTmp[ucCnt++ ];

            pstTFTInfo->aucLocalIpv4Mask[0] = pTmp[ucCnt++ ];
            pstTFTInfo->aucLocalIpv4Mask[1] = pTmp[ucCnt++ ];
            pstTFTInfo->aucLocalIpv4Mask[2] = pTmp[ucCnt++ ];
            pstTFTInfo->aucLocalIpv4Mask[3] = pTmp[ucCnt++ ];

        *pucIndex = ucCnt;


    }
    else
    {
        pstTFTInfo->bitOpLocalIpv4AddrAndMask = NAS_ESM_OP_FALSE;
        /* ������Ǹ�R11�汾������Я���˸���Ԫ����ֱ������ */
        ucCnt = ucCnt + 8;
        *pucIndex = ucCnt;
    }
    return;
}
VOS_VOID NAS_ESM_DecodeIpv6LocalAddr
(
    NAS_ESM_CONTEXT_TFT_STRU            *pstTFTInfo,
    const VOS_UINT8                     *pTmp,
    VOS_UINT8                           *pucIndex
)
{
    VOS_UINT8                          ucCnt = *pucIndex;
    VOS_UINT8                          ucIndex;

    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DecodeIpv6LocalAddr DECODE!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeIpv6LocalAddr_ENUM, LNAS_ENTRY);
            pstTFTInfo->bitOpLocalIpv6AddrAndMask = NAS_ESM_OP_TRUE;
            for (ucIndex = 0; ucIndex < NAS_ESM_IP_ADDR_LEN_IPV6; ucIndex++)
            {
                pstTFTInfo->aucLocalIpv6Addr[ucIndex] = pTmp[ucCnt];
                ucCnt++;
            }
            pstTFTInfo->ucLocalIpv6Prefix = pTmp[ucCnt++];

        *pucIndex = ucCnt;

    }
    else
    {
        pstTFTInfo->bitOpLocalIpv6AddrAndMask = NAS_ESM_OP_FALSE;
         /* ������Ǹ�R11�汾������Я���˸���Ԫ����ֱ������ */
        ucCnt = ucCnt + 17;
        *pucIndex = ucCnt;
    }
    return;
}
#endif
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeAddOneFilterTFT
(
    NAS_ESM_CONTEXT_TFT_STRU           *pstTFTInfo,
    const VOS_UINT8                    *pucTFTMsg,
    VOS_UINT8                          *pucLength
)
{
    VOS_UINT8                           ucCnt       = NAS_ESM_NULL;
    VOS_UINT8                           ucTmp       = NAS_ESM_NULL;
    VOS_UINT8                           ucLength    = NAS_ESM_NULL;
    const VOS_UINT8                    *pTmp        = pucTFTMsg;

    VOS_UINT32                          ulIndex     = 0;
    NAS_ESM_TFT_PF_COP_TYPE_ENUM_ENUM8  enTftPfCopType = NAS_ESM_TFT_PF_COP_TYPE_BUTT;

    /*�ж���Ϣ���ݵĺϷ��ԣ�������Ϸ������˳�;
      pTmp[3]    = filter1�е�����4��components�ĳ��Ⱥ�
                 = TFT����������ֽ���- TFT����ǰ��4������ֽ���*/
    /* �ж�TFT�Ƿ���uplink only */
    ucTmp = (pTmp[ucCnt] >> NAS_ESM_MOVEMENT_4_BITS) & NAS_ESM_LOW_2_BIT_MASK;

    /* OCTET4 Packet filter identifier 1 */
    pstTFTInfo->ucNwPacketFilterId = (pTmp[ucCnt])&(NAS_ESM_MSG_LOW_BIT);

    /* ��ȡPF�ķ��� */
    pstTFTInfo->enDirection      = ucTmp;

    /* �����R11�汾����Ҫ����PF�ķ���
       24301 CR1937R4(Rel-11): 6.4.2.3
       The UE shall treat any packet filter without explicit direction as being bi-directional. */
    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        /* �ж��Ƿ�δָ������ǰ���&����ֻȡ�˵�2λ����ֵ֤�������0x03 */
        if(APP_ESM_TRANSFER_DIRECTION_PRE_REL7_TFT_FILTER == ucTmp)
        {
            pstTFTInfo->enDirection = APP_ESM_TRANSFER_DIRECTION_UPLINK_DOWNLINK;
        }
    }

    /* OCTET5 ,Packet filter evaluation precedence 1 */
    ucCnt = ucCnt + 1;
    pstTFTInfo->ucPrecedence = pTmp[ucCnt++];

    /* ȡ��Length of Pactket fileter contents1*/
    ucLength = pTmp[ucCnt++];


    while(ucLength > (ucCnt - NAS_ESM_PACKET_FILTER_LEN_OFFSET))
    {
        /*���ȡ���ĳ��Ȳ���������ֱ�ӷ��أ�������п��ܲȺ�����ڴ�*/
        if (NAS_ESM_CAUSE_SUCCESS != NAS_ESM_DecodeAddOneFilterTFTCheckItemLen(pTmp[ucCnt],
                                                                               ucLength-(ucCnt - NAS_ESM_PACKET_FILTER_LEN_OFFSET)))
        {
            *pucLength = ucLength;
            return NAS_ESM_CAUSE_SUCCESS;
        }

        /* ��ȡ��ǰTftPfCopType */
        enTftPfCopType = pTmp[ucCnt++];

        /* ɨ��������ҵ���Ӧ��͵������� */
        for(ulIndex = 0; ulIndex < g_EsmDecodeAddFilterTftTableSize; ulIndex++)
        {
            if(enTftPfCopType == g_EsmDecodeAddFilterTftTable[ulIndex].enTftPfCopType)
            {
                g_EsmDecodeAddFilterTftTable[ulIndex].pfDecodeFun(pstTFTInfo, pTmp, &ucCnt);
                break;
            }
        }

        /* δ�ҵ���ӦTftPfCopType��ǰ�����������Ч������Ĳ�Ҫ�ˣ������������ */
        if(ulIndex >= g_EsmDecodeAddFilterTftTableSize)
        {
            NAS_ESM_WARN_LOG("NAS_ESM_DecodeAddOneFilterTFT:WARNING:NW->SM Invalid mandatory information1!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeAddOneFilterTFT_ENUM, LNAS_MSG_INVALID);
            break;
        }
    }

    /* �����ĳ��Ȼ���Ҫ������෢��Ϊ׼����������������Ԫ����Ҫ���� */
    *pucLength = ucLength;
    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeLlcSapi
 Description     : LLC SAPI���� (�Ϸ�����GUģ��SM����)
 Input           :  VOS_UINT16             usMsgLen
                    VOS_UINT8             *pucMsg
 Output          :  NAS_ESM_NW_MSG_STRU   *pstMsgIE
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-04-26  Draft Enact
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeLlcSapi
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    /*
    8   7   6   5   4   3   2   1
    LLC SAPI IEI
    0   0   0   0   LLC SAPI value
    */

    (VOS_VOID)usMsgLen;
    pstMsgIE->bitOpLlcSapi  = NAS_ESM_OP_TRUE;
    pstMsgIE->ucLlcSapi     = (pucMsg[0] & NAS_ESM_MSG_LOW_BIT);
    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodePacketFlowId
 Description     : Packet Flow Identifier���� (�Ϸ�����GUģ��SM����)
 Input           :  VOS_UINT16             usMsgLen
                    VOS_UINT8             *pucMsg
 Output          :  NAS_ESM_NW_MSG_STRU   *pstMsgIE
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-04-26  Draft Enact
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodePacketFlowId
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    /*
    8   7   6   5   4   3   2   1
    Packet Flow Identifier IEI
    Length of Packet Flow Identifier IE
    0   Packet Flow Identifier value
    */

    (VOS_VOID)usMsgLen;
    pstMsgIE->bitOpPacketFlowId = NAS_ESM_OP_TRUE;
    pstMsgIE->ucPacketFlowId    = (pucMsg[0] & 0x7f);
    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeRadioPriority
 Description     : Radio Priority����
 Input           :  VOS_UINT16             usMsgLen
                    VOS_UINT8             *pucMsg
 Output          :  NAS_ESM_NW_MSG_STRU   *pstMsgIE
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-04-27  Draft Enact
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeRadioPriority
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    /*
    8       7       6       5       4       3       2       1
    Radio priority IEI              0       Radio priority level value
    */

    (VOS_VOID)usMsgLen;
    pstMsgIE->bitOpRadioPriority    = NAS_ESM_OP_TRUE;
    pstMsgIE->ucRadioPriority       = (pucMsg[0] & 0x07);

    /* �������λ�ڡ�1,4��,����Ϊ��4 */
    if ((NAS_ESM_RADIO_PRIORITY_LEVEL1 > pstMsgIE->ucRadioPriority)
        || (NAS_ESM_RADIO_PRIORITY_LEVEL4 < pstMsgIE->ucRadioPriority))
    {
        pstMsgIE->ucRadioPriority = NAS_ESM_RADIO_PRIORITY_LEVEL4;
    }

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeTransactionId
 Description     : Transaction identifier����
 Input           :  VOS_UINT16             usMsgLen
                    VOS_UINT8             *pucMsg
 Output          :  NAS_ESM_NW_MSG_STRU   *pstMsgIE
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-04-27  Draft Enact
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeTransactionId
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    VOS_UINT8                           ucTiValue = NAS_ESM_NULL;

    /*
    8       7       6       5       4       3       2       1
    Linked TI IEI
    Length of Linked TI IE
    TI flag TI value                0       0       0       0
    1       TI value
    */

    /* Э��涨��һ�ֽ��е�TI VALUE��С��7����TIֵ�Ե�һ�ֽ��е�TI VALUEΪ׼��
       ����һ�ֽ��е�TI VALUEΪ7���������ڵڶ��ֽڣ�TIֵ�Եڶ��ֽ��е�TIֵ
       Ϊ׼�����Ե�һ�ֽ��е�TIֵ */

    /* ��ȡ��һ�ֽ��е�TI VALUE */
    ucTiValue = (pucMsg[0] & 0x70) >> NAS_ESM_MOVEMENT_4_BITS;

    /* �����һ�ֽ��е�TI VALUEΪ7���������ڵڶ��ֽڣ�����Ϊ����Ԫ����
       ���Դ���Ԫ */
    if (7 == ucTiValue)
    {
        if (1 == usMsgLen)
        {
            /*������Ϣ���ʧ��*/
            NAS_ESM_WARN_LOG( "NAS_ESM_DecodeTransactionId:len error!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_DecodeTransactionId_ENUM, LNAS_MSG_INVALID);
            return NAS_ESM_CAUSE_PROTOCOL_ERROR;
        }

        /* TIֵ��Ϊ�ڶ��ֽ��е�TI VALUE */
        pstMsgIE->stTransId.ucTiValue = (pucMsg[1] & 0x7f);
    }
    else
    {
        /* TIֵ��Ϊ��һ�ֽ��е�TI VALUE */
        pstMsgIE->stTransId.ucTiValue  = ucTiValue;
    }

    pstMsgIE->stTransId.ucTiFlag    = (pucMsg[0] & 0x80) >> NAS_ESM_MOVEMENT_7_BITS;
    pstMsgIE->bitOpTransId          = NAS_ESM_OP_TRUE;

    return NAS_ESM_CAUSE_SUCCESS;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DecodeNegotiatedQos
 Description     : Negotiated Qos����(����ȡ��GUģ)
 Input           :  VOS_UINT16             usMsgLen
                    VOS_UINT8             *pucMsg
 Output          :  NAS_ESM_NW_MSG_STRU   *pstMsgIE
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2011-04-27  Draft Enact
*****************************************************************************/
NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNegotiatedQos
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    VOS_UINT32                          ulSum            = NAS_ESM_NULL;
    const VOS_UINT8                    *pucTmpMsg        = pucMsg;
    NAS_ESM_CONTEXT_QOS_STRU           *pstTmpPdpQosInfo = VOS_NULL_PTR;

    pstTmpPdpQosInfo = &pstMsgIE->stCntxtQosInfo;

    pstTmpPdpQosInfo->ucDelayClass  = (pucTmpMsg[ulSum] & NAS_ESM_PDP_QOS_DELAY_CLASS) >> NAS_ESM_MOVEMENT_3_BITS;
    pstTmpPdpQosInfo->ucReliabClass = (pucTmpMsg[ulSum++] & NAS_ESM_PDP_QOS_RELIABILITY_CLASS);

    pstTmpPdpQosInfo->ucPeakThrough          = (pucTmpMsg[ulSum] & NAS_ESM_PDP_QOS_PEAK_THROUGHPUT) >> NAS_ESM_MOVEMENT_4_BITS;
    pstTmpPdpQosInfo->ucPrecedenceClass      = (pucTmpMsg[ulSum++] & NAS_ESM_PDP_QOS_PRECEDENCE_CLASS);

    pstTmpPdpQosInfo->ucMeanThrough          = (pucTmpMsg[ulSum++] & NAS_ESM_PDP_QOS_MEAN_THROUGHPUT);

    if (usMsgLen > 3)
    {
        pstTmpPdpQosInfo->ucTrafficClass     = (pucTmpMsg[ulSum] & NAS_ESM_PDP_QOS_TRAFFIC_CLASS)>>5;
        pstTmpPdpQosInfo->ucDeliverOrder     = (pucTmpMsg[ulSum] & NAS_ESM_PDP_QOS_DELIVERY_ORDER)>>3;
        pstTmpPdpQosInfo->ucDeliverOfErrSdu  = (pucTmpMsg[ulSum++] & NAS_ESM_PDP_QOS_DELIVERY_ERRORNEOUS_SDU);
    }

    if (usMsgLen > 4)
    {
        pstTmpPdpQosInfo->ucMaximSduSize     = pucTmpMsg[ulSum++];
    }

    if (usMsgLen > 5)
    {
        pstTmpPdpQosInfo->ucMaxBitRateForUp  = pucTmpMsg[ulSum++];
    }

    if (usMsgLen > 6)
    {
        pstTmpPdpQosInfo->ucMaxBitRateForDown = pucTmpMsg[ulSum++];;
    }

    if (usMsgLen > 7)
    {
        pstTmpPdpQosInfo->ucResidualBer      = (pucTmpMsg[ulSum] & NAS_ESM_PDP_QOS_RESIDUAL_BER) >> NAS_ESM_MOVEMENT_4_BITS;
        pstTmpPdpQosInfo->ucSduErrRatio      = (pucTmpMsg[ulSum++] & NAS_ESM_PDP_QOS_SDU_ERROR_RATIO);
    }

    if (usMsgLen > 8)
    {
        pstTmpPdpQosInfo->ucTransDelay           = (pucTmpMsg[ulSum] & NAS_ESM_PDP_QOS_TRANSFER_DELAY) >> NAS_ESM_MOVEMENT_2_BITS;
        pstTmpPdpQosInfo->ucTraffHandlPrior      = (pucTmpMsg[ulSum++] & NAS_ESM_PDP_QOS_TRAFFIC_HANDLING_PRIORITY);
    }

    if (usMsgLen > 9)
    {
        pstTmpPdpQosInfo->ucGuarantBitRateForUp  = pucTmpMsg[ulSum++];
    }

    if (usMsgLen > 10)
    {
       pstTmpPdpQosInfo->ucGuarantBitRateForDown = pucTmpMsg[ulSum++];
    }

    if (usMsgLen > 11)
    {
        pstTmpPdpQosInfo->ucSrcStatisticsDescriptor = (pucTmpMsg[ulSum] & NAS_ESM_PDP_QOS_SSD);

        /* Signalling-Indication ��ֵֻȡ���ֽڵĵ�5λ */
        pstTmpPdpQosInfo->ucSignallingIndication    = ((pucTmpMsg[ulSum++] & NAS_ESM_PDP_QOS_SIGNALLING_INDICATION) >> NAS_ESM_MOVEMENT_4_BITS);
    }

    if (usMsgLen > 12)
    {
        pstTmpPdpQosInfo->ucMaxBitRateForDownExt    = pucTmpMsg[ulSum++];
    }

    if (usMsgLen > 13)
    {
        pstTmpPdpQosInfo->ucGuarantBitRateForDownExt = pucTmpMsg[ulSum++];
    }

    if (usMsgLen > 14)
    {
        pstTmpPdpQosInfo->ucMaxBitRateForUpExt     = pucTmpMsg[ulSum++];
    }

    if (usMsgLen > 15)
    {
        pstTmpPdpQosInfo->ucGuarantBitRateForUpExt = pucTmpMsg[ulSum++];
    }

    if(NAS_RELEASE_R11)
    {
        if (usMsgLen > 16)
        {
            pstTmpPdpQosInfo->ucMaxBitRateForDownExt_2 = pucTmpMsg[ulSum++];
            pstTmpPdpQosInfo->ucGuarantBitRateForDownExt_2 = pucTmpMsg[ulSum++];
        }

        if(usMsgLen > 18)
        {
            pstTmpPdpQosInfo->ucMaxBitRateForUpExt_2 = pucTmpMsg[ulSum++];
            pstTmpPdpQosInfo->ucGuarantBitRateForUpExt_2 = pucTmpMsg[ulSum++];
        }
    }

    pstMsgIE->bitOpNegQos = NAS_ESM_OP_TRUE;
    return NAS_ESM_CAUSE_SUCCESS;
}
/*lint +e961*/
/*lint +e960*/

NAS_ESM_CAUSE_ENUM_UINT8 NAS_ESM_DecodeNotificationIndicator
(
    VOS_UINT16                          usMsgLen,
    const VOS_UINT8                    *pucMsg,
    NAS_ESM_NW_MSG_STRU                *pstMsgIE
)
{
    NAS_ESM_NOTIFICATION_IND_STRU   *pstNotificationInd = VOS_NULL_PTR;
    (VOS_VOID)usMsgLen;

    pstMsgIE->bitOpNotificationInd = NAS_ESM_OP_TRUE;
    pstNotificationInd = &pstMsgIE->stNotificationInd;

    pstNotificationInd->ucValue = pucMsg[0];

    return  NAS_ESM_CAUSE_SUCCESS;
}


VOS_VOID NAS_ESM_SndOmLogCnMsgDecodeFail
(
    NAS_ESM_CN_MSG_IE_TYPE_ENUM_UINT32                  enIeType,
    NAS_ESM_DECODE_CN_MSG_FAIL_CAUSE_ENUM_UINT32        enCause,
    VOS_UINT32                                          ulValue
)
{
    NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL_STRU      *pstMsg                         = VOS_NULL_PTR;
#if (VOS_OS_VER == VOS_WIN32)
    VOS_CHAR                                     acPrintStr[MAX_PRINT_CHAR_NUM] = {0};
    VOS_CHAR                                     acValue[MAX_PRINT_CHAR_NUM]    = {0};
#endif

    pstMsg = (NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_SndOmLogCnMsgDecodeFail: mem alloc fail!.");
        return;
    }

    NAS_ESM_MEM_SET(pstMsg, 0, sizeof(NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_ESM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_ESM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_ESM_OM_LOG_DECODE_CN_MSG_FAIL;
    pstMsg->enIeType                    = enIeType;
    pstMsg->enCause                     = enCause;
    pstMsg->ulValue                     = ulValue;

#if (VOS_OS_VER == VOS_WIN32)
    VOS_StrCpy(acPrintStr, "CN MSG Decode Fail, Fail IE:");
    VOS_StrCat(acPrintStr, g_EsmDecodeFailIePrintTable[enIeType-1].aucPrintStr);
    VOS_StrCat(acPrintStr, ", Fail Cause:");
    VOS_StrCat(acPrintStr, g_EsmDecodeFailCausePrintTable[enCause-1].aucPrintStr);
    VOS_sprintf(acValue, ", Value:%d", ulValue);
    VOS_StrCat(acPrintStr, acValue);
    NAS_ESM_ERR_LOG(acPrintStr);
#endif

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_ESM_MEM_FREE(pstMsg);
    return;
}





#ifdef __cplusplus
    #if __cplusplus
                                                }
    #endif
#endif

