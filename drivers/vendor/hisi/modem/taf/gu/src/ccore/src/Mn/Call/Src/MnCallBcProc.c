
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallBcProc.h"
#include "MnCallMsgDef.h"
#include "MnComm.h"
#include "NasIeUtil.h"
#include "MnCallMgmt.h"
#include "MnCallApi.h"

#include "MnCall.h"
#include "NVIM_Interface.h"
#include "MnCallCtx.h"
#include "MnCallProcNvim.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
  2 �꣬�ṹ�ͱ�������
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_BC_PROC_C
/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/


/* BC�ֶ�ֵ��������������BC�ֶ�����ж��ٸ�ֵ */
#define MN_CALL_BC_FLD_VAL_MAX_NUM      14



/* BC�ֶ����ƶ��� */
typedef enum
{
     MN_CALL_BC_FLD_RCR        =  0,                                            /* Radio channel requirement */
     MN_CALL_BC_FLD_CODING_STD,                                                 /* Coding standard  1*/
     MN_CALL_BC_FLD_TRANS_MOD,                                                  /* Transfer mode  2*/
     MN_CALL_BC_FLD_ITC,                                                        /* Information transfer capability 3*/
     MN_CALL_BC_FLD_CODING,                                                     /* Coding 4*/
     MN_CALL_BC_FLD_CTM,                                                        /* CTM 5*/
     MN_CALL_BC_FLD_SPCH_VER_IND,                                               /* Speech version indication 6*/
     MN_CALL_BC_FLD_COMPRESS,                                                   /* Compression 7*/
     MN_CALL_BC_FLD_STRUCTURE,                                                  /* Structure 8*/
     MN_CALL_BC_FLD_DUPL_MODE,                                                  /* Duplex mode 9*/
     MN_CALL_BC_FLD_CONFIGUR,                                                   /* Configuration 10*/
     MN_CALL_BC_FLD_NIRR,                                                       /* NIRR 11*/
     MN_CALL_BC_FLD_ESTABLI,                                                    /* Establishment 12*/
     MN_CALL_BC_FLD_ACCESS_ID,                                                  /* Access identity 13*/
     MN_CALL_BC_FLD_RA,                                                         /* Rate adaption 14*/
     MN_CALL_BC_FLD_SIGNAL,                                                     /* Signalling accesss protocol 15*/
     MN_CALL_BC_FLD_OTHER_ITC,                                                  /* Other ITC 16*/
     MN_CALL_BC_FLD_ORA,                                                        /* Ohter rate adaption 17*/
     MN_CALL_BC_FLD_HDR_NO_HDR,                                                 /* Rate adaption header/no header 18*/
     MN_CALL_BC_FLD_MULTI_FRAME,                                                /* Multiple frame establishment support 19*/
     MN_CALL_BC_FLD_MODE,                                                       /* Mode of operation 20*/
     MN_CALL_BC_FLD_LLI,                                                        /* Logical link identifier negotiation 21*/
     MN_CALL_BC_FLD_ASSIGNOR,                                                   /* Assignor/Assignee 22*/
     MN_CALL_BC_FLD_INB_NEG,                                                    /* In band/Out band negotiation 23*/
     MN_CALL_BC_FLD_LAYER1_ID,                                                  /* Layer 1 indenetity 24*/
     MN_CALL_BC_FLD_UIL1P,                                                      /* User information layer 1 protocol 25*/
     MN_CALL_BC_FLD_SYNC_ASYNC,                                                 /* Synchronous/asynchronous 26*/
     MN_CALL_BC_FLD_N_STOP_BIT,                                                 /* Number of stop bits 27*/
     MN_CALL_BC_FLD_NEGOTIATION,                                                /* Negotiation 28*/
     MN_CALL_BC_FLD_N_DATA_BIT,                                                 /* Number of data bits 29*/
     MN_CALL_BC_FLD_USER_RATE,                                                  /* User rate 30*/
     MN_CALL_BC_FLD_INTMD_RATE,                                                 /* Intermediate rate 31*/
     MN_CALL_BC_FLD_NIC_ON_TX,                                                  /* Network independent clock on Tx 32*/
     MN_CALL_BC_FLD_NIC_ON_RX,                                                  /* Network independent clock on Rx 33*/
     MN_CALL_BC_FLD_PARITY,                                                     /* Parity information 34*/
     MN_CALL_BC_FLD_CE,                                                         /* Connection element 35*/
     MN_CALL_BC_FLD_MODEM_TYPE,                                                 /* Modem type 36*/
     MN_CALL_BC_FLD_OMT,                                                        /* Other modem type 37*/
     MN_CALL_BC_FLD_FNUR,                                                       /* Fixed network user rate 38*/
     MN_CALL_BC_FLD_ACC,                                                        /* Acceptable channel codings 39*/
     MN_CALL_BC_FLD_MAX_TCH,                                                    /* Maximum number of traffic channels 40*/
     MN_CALL_BC_FLD_UIMI,                                                       /* User initiated modification indication 41*/
     MN_CALL_BC_FLD_WAIUR,                                                      /* Wanted air interface user rate 42*/
     MN_CALL_BC_FLD_EXT_ACC,                                                    /* Acceptable channel coding extended 43*/
     MN_CALL_BC_FLD_ASYM_IND,                                                   /* Channel coding asymmetry indication 44*/
     MN_CALL_BC_FLD_LAYER2_ID,                                                  /* Layer 2 identity 45*/
     MN_CALL_BC_FLD_UIL2P,                                                      /* User information layer 2 protocol 46*/
     MN_CALL_BC_NUM_OF_FIELD                                                    /* Number of BC fields, should be 47*/
} MN_CALL_BC_FLD_NAME_ENUM;

typedef enum
{
    MN_CALL_VAR_PARM_MT,                                    /* ���صĿɱ����ΪModem type */
    MN_CALL_VAR_PARM_OMT,                                   /* ���صĿɱ����ΪOther modem type */
    MN_CALL_VAR_PARM_RA,                                    /* ���صĿɱ����ΪRate adaption */
    MN_CALL_VAR_PARM_ORA,                                   /* ���صĿɱ����ΪOther rate adaption */
    MN_CALL_VAR_PARM_NO_OUTPUT,                             /* �ɱ����û��� */
    MN_CALL_VAR_PARM_ERROR                                  /* �������� */
} MN_CALL_VAR_PARM_ENUM;



/* Structure of supported speech versions */
typedef struct
{
    VOS_UINT8  ucCnt;
    VOS_UINT8  aucVers[MN_CALL_BC_MAX_SPH_VER_NUM];
} MN_CALL_BC_SPEECH_VERS_STRU;

/* BC�ֶ���Ϣ�Ľṹ
   ucFixedVal - �趨��ֵ����ЩBC�ֶ��ڹ���ʱ���Ǹ�������������仯�ģ�
                �����ڱ���ʱ���ʼ��ʱ���Ѿ����õġ�
   ucNumOfVals - ���ֶ�֧�ֵ�ֵ�ĸ�����0��ʾ����Ҫ�Ը��ֶ������
   aucSupptVals - ���ֶ�����֧�ֵ�ֵ                               */
typedef struct
{
    VOS_UINT8  ucFixedVal;
    VOS_UINT8  ucNumOfVals;
    VOS_UINT8  aucSupptVals[MN_CALL_BC_FLD_VAL_MAX_NUM];
} MN_CALL_BC_FIELD_INFO_STRU;



LOCAL MN_CALL_UMTS_CODEC_TYPE_STRU  f_stMnCallUmtsCodecTypes;

/* Supported speech versions */
LOCAL MN_CALL_BC_SPEECH_VERS_STRU   f_stMnCallSphVers;

/* BC field informations list */
LOCAL MN_CALL_BC_FIELD_INFO_STRU    f_astMnCallBcFldInfo[MN_CALL_BC_NUM_OF_FIELD] = {
/* | Fixed value                    | NSVs |  Support values         | */
    {MN_CALL_BC_VAL_RCR_DUAL_FR,    0,        {0}                             },/* Radio channel requirement 0*/
    {MN_CALL_BC_VAL_CODSTD_GSM,     1,        {MN_CALL_BC_VAL_CODSTD_GSM}     },/* Coding standard 1*/
    {MN_CALL_BC_VAL_TM_CIRCUIT,     1,        {MN_CALL_BC_VAL_TM_CIRCUIT}     },/* Transfer mode 2*/
    {0,                             6,        {MN_CALL_BC_VAL_ITC_SPEECH,
                                               MN_CALL_BC_VAL_ITC_UDI,
                                               MN_CALL_BC_VAL_ITC_3D1K,
                                               MN_CALL_BC_VAL_ITC_FAX,
                                               MN_CALL_BC_VAL_ITC_OTHER,
                                               MN_CALL_BC_VAL_ITC_AUX_SPEECH} },/* Information transfer capability 3*/
    {MN_CALL_BC_VAL_CODING_EXT_ITC, 1,        {MN_CALL_BC_VAL_CODING_EXT_ITC} },/* Coding 4*/
    {MN_CALL_BC_VAL_CTM_N_SUPPORT,  1,        {MN_CALL_BC_VAL_CTM_N_SUPPORT}  },/* CTM 5*/
    {0,                             0,        {0}                             },/* Speech version indication 6*/

    /*In case of a Mobile Terminated Call, if the SETUP message does not contain
    a BC-IE, the MS shall behave as if the DC is set to "data compression not
    possible".If a sending entity, based on an earlier version of the protocol,
    sends a SETUP message containing "DC.. compression possible/ allowed" instead
    of the default value "NO.. compression  not possible/allowed"as defined in
    Table B.5 then the receiving MS or the receiving network may ignore the DC
    value and may return either "NO.. compression  not possible/allowed" or
    "DC.. compression possible/allowed" in the CALL CONF/CALL PROC message.*/
    {MN_CALL_BC_VAL_COMP_NOT_ALLOW, 2,        {MN_CALL_BC_VAL_COMP_NOT_ALLOW,
                                               MN_CALL_BC_VAL_COMP_ALLOW } },/* Compression 7*/
    {0,                             2,        {MN_CALL_BC_VAL_STRUCT_SDU,
                                               MN_CALL_BC_VAL_STRUCT_UNSTRU}  },/* Structure 8*/
    {MN_CALL_BC_FLD_DUPL_MODE,      2,        {MN_CALL_BC_VAL_DUPLMOD_HALF,
                                               MN_CALL_BC_VAL_DUPLMOD_FULL}   },/* Duplex mode 9*/
    {MN_CALL_BC_VAL_CONFIGUR_PTP,   1,        {MN_CALL_BC_VAL_CONFIGUR_PTP}   },/* Configuration 10*/
    {0,                             2,        {MN_CALL_BC_VAL_NIRR_NO_MEAN,
                                               MN_CALL_BC_VAL_NIRR_6K}        },/* NIRR 11*/
    {MN_CALL_BC_VAL_ESTABLI_DEMAND, 1,        {MN_CALL_BC_VAL_ESTABLI_DEMAND} },/* Establishment 12*/
    {MN_CALL_BC_VAL_ACCESS_ID_OCT,  1,        {MN_CALL_BC_VAL_ACCESS_ID_OCT}  },/* Access identity 13*/
    {MN_CALL_BC_VAL_RA_NO,          4,        {MN_CALL_BC_VAL_RA_NO,
                                               MN_CALL_BC_VAL_RA_V110,
                                               MN_CALL_BC_VAL_RA_X31,
                                               MN_CALL_BC_VAL_RA_OTHER}       },/* Rate adaption 14*/
    {MN_CALL_BC_VAL_SIGNAL_I440,    1,        {MN_CALL_BC_VAL_SIGNAL_I440}    },/* Signalling accesss protocol 15*/
    {MN_CALL_BC_VAL_OTHITC_RDI,     1,        {MN_CALL_BC_VAL_OTHITC_RDI}     },/* Other ITC 16*/
    {MN_CALL_BC_VAL_ORA_V120,       3,        {MN_CALL_BC_VAL_ORA_V120,
                                               MN_CALL_BC_VAL_ORA_H223_245,
                                               MN_CALL_BC_VAL_ORA_PIAFS}      },/* Ohter rate adaption 17*/
    {MN_CALL_BC_VAL_RA_HDR_INCLUD,  0,        {0}                             },/* Rate adaption header/no header 18*/
    {MN_CALL_BC_VAL_MF_SUPPT,       0,        {0}                             },/* Multiple frame establishment support 19*/
    {MN_CALL_BC_VAL_PROT_SENSI_MODE,0,        {0}                             },/* Mode of operation 20*/
    {MN_CALL_BC_VAL_LLI_DEFAULT,    0,        {0}                             },/* Logical link identifier negotiation 21*/
    {MN_CALL_BC_VAL_DEF_ASSIGNEE,   0,        {0}                             },/* Assignor/Assignee 22*/
    {MN_CALL_BC_VAL_INBNEG_INB,     0,        {0}                             },/* In band/Out band negotiation 23*/
    {MN_CALL_BC_VAL_L1_ID_OCT,      1,        {MN_CALL_BC_VAL_L1_ID_OCT}      },/* Layer 1 indenetity 24*/
    {MN_CALL_BC_VAL_UIL1P_DEFAULT,  1,        {MN_CALL_BC_VAL_UIL1P_DEFAULT}  },/* User information layer 1 protocol 25*/
    {0,                             0,        {0}                             },/* Synchronous/asynchronous 26*/
    {MN_CALL_BC_VAL_NSB_1BIT,       0,        {0}                             },/* Number of stop bits 27*/
    {MN_CALL_BC_VAL_NEG_NO_IBN,     1,        {MN_CALL_BC_VAL_NEG_NO_IBN}     },/* Negotiation 28*/
    {MN_CALL_BC_VAL_NDB_8BIT,       0,        {0}                             },/* Number of data bits 29*/
    {MN_CALL_BC_VAL_UR_9K6,         5,        {MN_CALL_BC_VAL_UR_300,
                                               MN_CALL_BC_VAL_UR_1K2,
                                               MN_CALL_BC_VAL_UR_2K4,
                                               MN_CALL_BC_VAL_UR_4K8,
                                               MN_CALL_BC_VAL_UR_9K6}         },/* User rate 30*/
    {0,                             2,        {MN_CALL_BC_VAL_IR_8K,
                                               MN_CALL_BC_VAL_IR_16K}         },/* Intermediate rate 31*/
    {MN_CALL_BC_VAL_NICTX_N_SUPPT,  1,        {MN_CALL_BC_VAL_NICTX_N_SUPPT}  },/* Network independent clock on Tx 32*/
    {MN_CALL_BC_VAL_NICRX_N_SUPPT,  1,        {MN_CALL_BC_VAL_NICRX_N_SUPPT}  },/* Network independent clock on Rx 33*/
    {MN_CALL_BC_VAL_PARITY_NONE,    5,        {MN_CALL_BC_VAL_PARITY_ODD,
                                               MN_CALL_BC_VAL_PARITY_EVEN,
                                               MN_CALL_BC_VAL_PARITY_NONE,
                                               MN_CALL_BC_VAL_PARITY_FORCE_0,
                                               MN_CALL_BC_VAL_PARITY_FORCE_1} },/* Parity information 34*/
    {0,                             0,        {0}                             },/* Connection element 35*/
    {0,                             7,        {MN_CALL_BC_VAL_MT_NONE,
                                               MN_CALL_BC_VAL_MT_V21,
                                               MN_CALL_BC_VAL_MT_V22,
                                               MN_CALL_BC_VAL_MT_V22BIS,
                                               MN_CALL_BC_VAL_MT_V26,
                                               MN_CALL_BC_VAL_MT_V32,
                                               MN_CALL_BC_VAL_MT_AUTOBAUD}    },/* Modem type 36*/
    {MN_CALL_BC_VAL_OMT_NONE,       2,        {MN_CALL_BC_VAL_OMT_NONE,
                                               MN_CALL_BC_VAL_OMT_V34}        },/* Other modem type 37*/
    {MN_CALL_BC_VAL_FNUR_NA,        6,        {MN_CALL_BC_VAL_FNUR_NA,
                                               MN_CALL_BC_VAL_FNUR_9K6,
                                               MN_CALL_BC_VAL_FNUR_14K4,
                                               MN_CALL_BC_VAL_FNUR_19K2,
                                               MN_CALL_BC_VAL_FNUR_28K8,
                                               MN_CALL_BC_VAL_FNUR_64K }      },/* Fixed network user rate 38*/
    {0,                             0,        {0}                             },/* Acceptable channel codings 39*/
    {MN_CALL_BC_VAL_MTCH_1,         1,        {0}                             },/* Maximum number of traffic channels 40*/
    {MN_CALL_BC_VAL_UIMI_NA,        0,        {0}                             },/* User initiated modification indication 41*/
    {MN_CALL_BC_VAL_WAIUR_NA,       1,        {0}                             },/* Wanted air interface user rate 42*/
    {0,                             0,        {0}                             },/* Acceptable channel coding extended 43*/
    {0,                             0,        {0}                             },/* Channel coding asymmetry indication 44*/
    {MN_CALL_BC_VAL_L2_ID_OCT,      1,        {MN_CALL_BC_VAL_L2_ID_OCT}      },/* Layer 2 identity 45*/
    {MN_CALL_BC_VAL_UIL2P_DC1_DC3,  2,        {MN_CALL_BC_VAL_UIL2P_DC1_DC3,
                                               MN_CALL_BC_VAL_UIL2P_COPNOFLCT}} /* User information layer 2 protocol 46*/
};

/*lint -e961*/

/* ���BC��һ���ֶ� */
#define MN_CALL_BC_CHECK_FIELD(name, val)  \
        if (VOS_FALSE == MN_CALL_BcIsValueSupported((name), (val))) \
        { \
            return VOS_ERR; \
        }

/* ȡ��BC������Ϊ�̶�ֵ���ֶε�ֵ */
#define MN_CALL_BC_FIXED_FLD_VAL(name)  \
    f_astMnCallBcFldInfo[(name)].ucFixedVal
/*lint +e961*/

/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/




VOS_UINT32  MN_CALL_IsCodecTypeValid(
    VOS_UINT8                           ucCodecType
)
{
    if ( ( MN_CALL_BC_VAL_SPH_VER_FR_1 != ucCodecType )
      && ( MN_CALL_BC_VAL_SPH_VER_FR_2 != ucCodecType )
      && ( MN_CALL_BC_VAL_SPH_VER_FR_3 != ucCodecType )
      && ( MN_CALL_BC_VAL_SPH_VER_HR_1 != ucCodecType )
      && ( MN_CALL_BC_VAL_SPH_VER_HR_3 != ucCodecType )
      && ( MN_CALL_BC_VAL_SPH_VER_FR_5 != ucCodecType ))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



VOS_UINT32  MN_CALL_IsUmtsCodecTypeValid(
    VOS_UINT8                           ucUmtsCodecType
)
{
    if ( ( MN_CALL_UMTS_CODEC_TYPE_AMR != ucUmtsCodecType )
      && ( MN_CALL_UMTS_CODEC_TYPE_AMR2 != ucUmtsCodecType )
      && ( MN_CALL_UMTS_CODEC_TYPE_AMRWB != ucUmtsCodecType ))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_VOID  MN_CALL_GsmCapaProcInit( VOS_VOID )
{
    /* ��ʼ����������汾�б� */
    MN_CALL_NIMV_ITEM_CODEC_TYPE_STRU   stCodecType;
    VOS_UINT32                          ulDefaultValue;
    VOS_UINT32                          i;


    PS_MEM_SET(&stCodecType, 0x00, sizeof(stCodecType));

    ulDefaultValue          = VOS_FALSE;
    if ( NV_OK != NV_Read(en_NV_Item_MED_CODEC_TYPE,
                         &stCodecType,
                          sizeof(stCodecType)))
    {
        ulDefaultValue = VOS_TRUE;
    }

    /* ���NVIM�еĲ����Ƿ�Ϸ�,���Ϸ���ʹ��Ĭ��ֵ,�����Ƿ�Խ�� */
    if ( stCodecType.ucCodecTypeNum > MN_CALL_BC_MAX_SPH_VER_NUM )
    {
        ulDefaultValue = VOS_TRUE;
        stCodecType.ucCodecTypeNum = MN_CALL_BC_MAX_SPH_VER_NUM;
    }

    f_stMnCallSphVers.ucCnt = 0;

    /* ����Ƿ����ظ�����ͳ�����Χ��codec����*/
    for ( i = 0; i < stCodecType.ucCodecTypeNum; i++ )
    {
        if ( VOS_FALSE == MN_CALL_IsCodecTypeValid(stCodecType.aucCodecType[i]) )
        {
            ulDefaultValue = VOS_TRUE;
            break;
        }


        /* ��NVIM�е������������뵽�ڴ��� */
        f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt] = stCodecType.aucCodecType[i];
        f_stMnCallSphVers.ucCnt++;
    }

    /* �˴���ʾ��Ҫʹ��Ĭ��ֵ */
    if ( VOS_TRUE == ulDefaultValue )
    {
        /*lint -e961*/
        f_stMnCallSphVers.ucCnt  = 0;
        f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++] = MN_CALL_BC_VAL_SPH_VER_FR_3;
        f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++] = MN_CALL_BC_VAL_SPH_VER_HR_3;
        f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++] = MN_CALL_BC_VAL_SPH_VER_FR_2;
        f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++] = MN_CALL_BC_VAL_SPH_VER_FR_1;
        f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++] = MN_CALL_BC_VAL_SPH_VER_HR_1;
        f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++] = MN_CALL_BC_VAL_SPH_VER_FR_5;
        /*lint +e961*/
    }
}
VOS_VOID  MN_CALL_UmtsCapaProcInit( VOS_VOID )
{
    MN_CALL_UMTS_CODEC_TYPE_STRU        stCodecType;
    VOS_UINT32                          ulDefaultValue;
    VOS_UINT32                          i;

    PS_MEM_SET(&stCodecType, 0x00, sizeof(stCodecType));

    ulDefaultValue          = VOS_FALSE;
    if ( NV_OK != NV_Read(en_NV_Item_UMTS_CODEC_TYPE,
                         &stCodecType,
                          sizeof(stCodecType)))
    {
        ulDefaultValue = VOS_TRUE;
    }

    /* ���NVIM�еĲ����Ƿ�Ϸ�,���Ϸ���ʹ��Ĭ��ֵ,�����Ƿ�Խ�� */
    if ( stCodecType.ucCnt > MN_CALL_MAX_UMTS_CODEC_TYPE_NUM )
    {
        ulDefaultValue = VOS_TRUE;
        stCodecType.ucCnt = MN_CALL_MAX_UMTS_CODEC_TYPE_NUM;
    }

    f_stMnCallUmtsCodecTypes.ucCnt = 0;

    /* ����Ƿ����ظ�����ͳ�����Χ��codec����*/
    for ( i = 0; i < stCodecType.ucCnt; i++ )
    {
        if ( VOS_FALSE == MN_CALL_IsUmtsCodecTypeValid(stCodecType.aucUmtsCodec[i]) )
        {
            ulDefaultValue = VOS_TRUE;
            break;
        }


        /* ��NVIM�е������������뵽�ڴ��� */
        f_stMnCallUmtsCodecTypes.aucUmtsCodec[f_stMnCallUmtsCodecTypes.ucCnt]= stCodecType.aucUmtsCodec[i];
        f_stMnCallUmtsCodecTypes.ucCnt++;
    }


    if ( VOS_TRUE == ulDefaultValue )
    {
        f_stMnCallUmtsCodecTypes.ucCnt = 0;
        /*lint -e961*/
        f_stMnCallUmtsCodecTypes.aucUmtsCodec[f_stMnCallUmtsCodecTypes.ucCnt++] = MN_CALL_UMTS_CODEC_TYPE_AMR;
        f_stMnCallUmtsCodecTypes.aucUmtsCodec[f_stMnCallUmtsCodecTypes.ucCnt++] = MN_CALL_UMTS_CODEC_TYPE_AMR2;
        /*lint +e961*/
    }
}





VOS_VOID MN_CALL_CapaProcInit()
{
    MN_CALL_GsmCapaProcInit();

    MN_CALL_UmtsCapaProcInit();

    return;

} /* MN_CALL_CapaProcInit */



VOS_UINT32 MN_CALL_ConfigGsmCapaProc(
    NAS_OM_GSM_CODEC_CONFIG_ENUM_U8     enCapaConfig
)
{
    VOS_UINT32 ulRlst;

    if ((enCapaConfig < NAS_OM_GSM_CODEC_FR)
     || (enCapaConfig > NAS_OM_GSM_CODEC_FR_EFR_HR_AMR))
    {
        return VOS_ERR;
    }

    /*
    HR   ->  MN_CALL_BC_VAL_SPH_VER_HR_1  MN_CALL_BC_VAL_SPH_VER_HR_3
    FR   ->  MN_CALL_BC_VAL_SPH_VER_FR_1
    EFR  ->  MN_CALL_BC_VAL_SPH_VER_FR_2
    AMR-FR/AMR-HR -> MN_CALL_BC_VAL_SPH_VER_FR_3
    */
    ulRlst = VOS_OK;
    /*lint -e961*/
    switch ( enCapaConfig )
    {
        case NAS_OM_GSM_CODEC_FR :
            f_stMnCallSphVers.ucCnt = 0;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_FR_1;
            break;

        case NAS_OM_GSM_CODEC_FR_HR :
            f_stMnCallSphVers.ucCnt = 0;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_FR_1;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_HR_1;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_HR_3;
            break;

        case NAS_OM_GSM_CODEC_FR_EFR :
            f_stMnCallSphVers.ucCnt = 0;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_FR_2;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_FR_1;
            break;

        case NAS_OM_GSM_CODEC_FR_AMR :
            f_stMnCallSphVers.ucCnt = 0;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_FR_3;
            f_stMnCallSphVers.aucVers[f_stMnCallSphVers.ucCnt++]
                    = MN_CALL_BC_VAL_SPH_VER_FR_1;
            break;

        case NAS_OM_GSM_CODEC_FR_EFR_HR_AMR :
            MN_CALL_CapaProcInit();
            break;

        default:
            MN_WARN_LOG1("MN_CALL_ConfigGsmCapaProc:Invalid Para",enCapaConfig);
            ulRlst = VOS_ERR;
            break;
    }
    /*lint +e961*/

    return ulRlst;
}


NAS_OM_CURR_CODEC_TYPE_ENUM_U8  MN_CALL_ConvertMnCodecToOmCodec(
    MN_CALL_CODEC_TYPE_ENUM_U8          enCodecType
)
{
    NAS_OM_CURR_CODEC_TYPE_ENUM_U8      enCurrentOmCodecType;

    switch ( enCodecType )
    {
        case MN_CALL_CODEC_TYPE_AMR :
            enCurrentOmCodecType = NAS_OM_CODEC_TYPE_AMR;
            break;

        case MN_CALL_CODEC_TYPE_EFR :
            enCurrentOmCodecType = NAS_OM_CODEC_TYPE_EFR;
            break;

        case MN_CALL_CODEC_TYPE_FR :
            enCurrentOmCodecType = NAS_OM_CODEC_TYPE_FR;
            break;

        case MN_CALL_CODEC_TYPE_HR :
            enCurrentOmCodecType = NAS_OM_CODEC_TYPE_HR;
            break;

        case MN_CALL_CODEC_TYPE_AMR2 :
            enCurrentOmCodecType = NAS_OM_CODEC_TYPE_AMR2;
            break;

        case MN_CALL_CODEC_TYPE_AMRWB:
            enCurrentOmCodecType = NAS_OM_CODEC_TYPE_AMRWB;
            break;


        default:
            enCurrentOmCodecType = NAS_OM_CODEC_TYPE_BUTT;
            break;
    }

    return enCurrentOmCodecType;
}


NAS_OM_GSM_CODEC_CONFIG_ENUM_U8  MN_CALL_ConvertSpeechVers(VOS_VOID )
{
    VOS_UINT32                          i = 0;
    NAS_OM_GSM_CODEC_CONFIG_ENUM_U8     enGsmCodecConfig;

    /*
    HR   ->  MN_CALL_BC_VAL_SPH_VER_HR_1  MN_CALL_BC_VAL_SPH_VER_HR_3
    FR   ->  MN_CALL_BC_VAL_SPH_VER_FR_1
    EFR  ->  MN_CALL_BC_VAL_SPH_VER_FR_2
    AMR-FR -> MN_CALL_BC_VAL_SPH_VER_FR_3
    */

    enGsmCodecConfig = 0;
    for ( i = 0 ; i < f_stMnCallSphVers.ucCnt ; i++ )
    {
        if ( (MN_CALL_BC_VAL_SPH_VER_HR_1 == f_stMnCallSphVers.aucVers[i])
          || (MN_CALL_BC_VAL_SPH_VER_HR_3 == f_stMnCallSphVers.aucVers[i]))
        {
            enGsmCodecConfig |= NAS_OM_CODEC_TYPE_HR;
        }
        else if ( MN_CALL_BC_VAL_SPH_VER_FR_1  == f_stMnCallSphVers.aucVers[i] )
        {
            enGsmCodecConfig |= NAS_OM_CODEC_TYPE_FR;
        }
        else if ( MN_CALL_BC_VAL_SPH_VER_FR_2 == f_stMnCallSphVers.aucVers[i] )
        {
            enGsmCodecConfig |= NAS_OM_CODEC_TYPE_EFR;
        }
        else if ( MN_CALL_BC_VAL_SPH_VER_FR_5 == f_stMnCallSphVers.aucVers[i] )
        {
            enGsmCodecConfig |= NAS_OM_CODEC_TYPE_AMRWB;
        }
        else
        {
            enGsmCodecConfig |= NAS_OM_CODEC_TYPE_AMR;
        }

    }

    return enGsmCodecConfig;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_BcIsValueSupported
 ��������  : �ж�ĳ��BC�ֶ��Ƿ�֧��ĳ���ض���ֵ
 �������  : enFldName - �ֶ�����
              ucValue   - ��Ҫ�жϵ�ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE��ʾ֧�֣�VOS_FALSE��ʾ��֧��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��12��1��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_CALL_BcIsValueSupported(
    MN_CALL_BC_FLD_NAME_ENUM            enFldName,
    VOS_UINT8                           ucValue
)
{
    VOS_UINT32 i;

    if (MN_CALL_BC_NUM_OF_FIELD <= enFldName)
    {
        /* �ֶ������� */
        return VOS_FALSE;
    }

    if (0 == f_astMnCallBcFldInfo[enFldName].ucNumOfVals)
    {
        /* ucNumOfValsΪ0��ʾ����Ҫ�Ը��ֶν��м�飬
           ֱ�ӷ��سɹ� */
        return VOS_TRUE;
    }

    /* �鿴�����ucValue�Ƿ��ڶ����ֵ���� */
    for (i=0; i<f_astMnCallBcFldInfo[enFldName].ucNumOfVals; i++)
    {
        if (ucValue == f_astMnCallBcFldInfo[enFldName].aucSupptVals[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

} /* MN_CALL_BcIsValueSupported */



MN_CALL_VAR_PARM_ENUM  MN_CALL_GetInfoFromBstSpeed(
    MN_CALL_BST_SPEED_ENUM_UINT8        enSpeed,
    VOS_UINT8                           *pucUserRate,
    VOS_UINT8                           *pucFnur,
    VOS_UINT8                           *pucVarParm
)
{
    switch(enSpeed)
    {
    case MN_CALL_BST_SPD_300_V110:
    case MN_CALL_BST_SPD_300_V21:
        *pucUserRate = MN_CALL_BC_VAL_UR_300;
        *pucFnur = MN_CALL_BC_VAL_FNUR_NA;
        break;

    case MN_CALL_BST_SPD_1K2_V110:
    case MN_CALL_BST_SPD_1K2_V120:
    case MN_CALL_BST_SPD_1K2_V22:
        *pucUserRate = MN_CALL_BC_VAL_UR_1K2;
        *pucFnur = MN_CALL_BC_VAL_FNUR_NA;
        break;

    case MN_CALL_BST_SPD_2K4_V110:
    case MN_CALL_BST_SPD_2K4_V120:
    case MN_CALL_BST_SPD_2K4_V22BIS:
    case MN_CALL_BST_SPD_2K4_V26TER:
        *pucUserRate = MN_CALL_BC_VAL_UR_2K4;
        *pucFnur = MN_CALL_BC_VAL_FNUR_NA;
        break;

    case MN_CALL_BST_SPD_4K8_V110:
    case MN_CALL_BST_SPD_4K8_V120:
    case MN_CALL_BST_SPD_4K8_V32:
        *pucUserRate = MN_CALL_BC_VAL_UR_4K8;
        *pucFnur = MN_CALL_BC_VAL_FNUR_NA;
        break;

    case MN_CALL_BST_SPD_9K6_V110:
    case MN_CALL_BST_SPD_9K6_V120:
    case MN_CALL_BST_SPD_9K6_V32:
    case MN_CALL_BST_SPD_9K6_V34:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_9K6;
        break;

    case MN_CALL_BST_SPD_14K4_V110:
    case MN_CALL_BST_SPD_14K4_V120:
    case MN_CALL_BST_SPD_14K4_V34:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_14K4;
        break;

    case MN_CALL_BST_SPD_19K2_V110:
    case MN_CALL_BST_SPD_19K2_V120:
    case MN_CALL_BST_SPD_19K2_V34:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_19K2;
        break;

    case MN_CALL_BST_SPD_28K8_V110:
    case MN_CALL_BST_SPD_28K8_V120:
    case MN_CALL_BST_SPD_28K8_V34:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_28K8;
        break;

    case MN_CALL_BST_SPD_38K4_V110:
    case MN_CALL_BST_SPD_38K4_V120:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_38K4;
        break;

    case MN_CALL_BST_SPD_48K_V110:
    case MN_CALL_BST_SPD_48K_V120:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_48K;
        break;

    case MN_CALL_BST_SPD_56K_FTM:
    case MN_CALL_BST_SPD_56K_BT:
    case MN_CALL_BST_SPD_56K_V120:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_56K;
        break;

    case MN_CALL_BST_SPD_64K_MULTI:
    case MN_CALL_BST_SPD_64K_FTM:
    case MN_CALL_BST_SPD_64K_BT:
    case MN_CALL_BST_SPD_64K_PIAFS:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_64K;
        break;

    case MN_CALL_BST_SPD_33K6_V34:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_33K6;
        break;

    case MN_CALL_BST_SPD_32K_PIAFS:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_32K;
        break;

    case MN_CALL_BST_SPD_AUTOBAUD:
        *pucUserRate = MN_CALL_BC_VAL_UR_9K6;
        *pucFnur = MN_CALL_BC_VAL_FNUR_28K8;
        break;

    default:
        return MN_CALL_VAR_PARM_ERROR;
    }

    if (MN_CALL_BST_SPD_AUTOBAUD == enSpeed)
    {
        *pucVarParm = MN_CALL_BC_VAL_MT_AUTOBAUD;
        return MN_CALL_VAR_PARM_MT;
    }
    else if (MN_CALL_BST_SPD_300_V21 == enSpeed)
    {
        *pucVarParm = MN_CALL_BC_VAL_MT_V21;
        return MN_CALL_VAR_PARM_MT;
    }
    else if (MN_CALL_BST_SPD_1K2_V22 == enSpeed)
    {
        *pucVarParm = MN_CALL_BC_VAL_MT_V22;
        return MN_CALL_VAR_PARM_MT;
    }
    else if (MN_CALL_BST_SPD_2K4_V22BIS == enSpeed)
    {
        *pucVarParm = MN_CALL_BC_VAL_MT_V22BIS;
        return MN_CALL_VAR_PARM_MT;
    }
    else if (MN_CALL_BST_SPD_2K4_V26TER == enSpeed)
    {
        *pucVarParm = MN_CALL_BC_VAL_MT_V26;
        return MN_CALL_VAR_PARM_MT;
    }
    else if ((MN_CALL_BST_SPD_4K8_V32 == enSpeed) ||
        (MN_CALL_BST_SPD_9K6_V32 == enSpeed))
    {
        *pucVarParm = MN_CALL_BC_VAL_MT_V32;
        return MN_CALL_VAR_PARM_MT;
    }
    else if ((enSpeed >= MN_CALL_BST_SPD_9K6_V34) &&
        (enSpeed <= MN_CALL_BST_SPD_33K6_V34))
    {
        *pucVarParm = MN_CALL_BC_VAL_OMT_V34;
        return MN_CALL_VAR_PARM_OMT;
    }
    else if ((enSpeed >= MN_CALL_BST_SPD_1K2_V120) &&
        (enSpeed <= MN_CALL_BST_SPD_56K_V120))
    {
        *pucVarParm = MN_CALL_BC_VAL_ORA_V120;
        return MN_CALL_VAR_PARM_ORA;
    }
    else if ((enSpeed >= MN_CALL_BST_SPD_300_V110) &&
        (enSpeed <= MN_CALL_BST_SPD_48K_V110))
    {
        *pucVarParm = MN_CALL_BC_VAL_RA_V110;
        return MN_CALL_VAR_PARM_RA;
    }
    else if ((MN_CALL_BST_SPD_56K_FTM == enSpeed) ||
        (MN_CALL_BST_SPD_64K_FTM == enSpeed))
    {
        *pucVarParm = MN_CALL_BC_VAL_RA_X31;
        return MN_CALL_VAR_PARM_RA;
    }
    else if((MN_CALL_BST_SPD_56K_BT == enSpeed) ||
        (MN_CALL_BST_SPD_64K_BT == enSpeed))
    {
        return MN_CALL_VAR_PARM_NO_OUTPUT;
    }
    else if((MN_CALL_BST_SPD_32K_PIAFS == enSpeed) ||
        (MN_CALL_BST_SPD_64K_PIAFS == enSpeed))
    {
        *pucVarParm = MN_CALL_BC_VAL_ORA_PIAFS;
        return MN_CALL_VAR_PARM_ORA;
    }
    #if 0
    else if((MN_CALL_BST_SPD_32K_PIAFS == enSpeed) ||
        (MN_CALL_BST_SPD_64K_PIAFS == enSpeed))
    {
        *pucVarParm = MN_CALL_BC_VAL_ORA_PIAFS;
        return MN_CALL_VAR_PARM_ORA;
    }
    #endif
    else /* 64k multimedia */
    {
        *pucVarParm = MN_CALL_BC_VAL_ORA_H223_245;
        return MN_CALL_VAR_PARM_ORA;
    }

} /* MN_CALL_CcaGetInfoFromBstSpeed */
/*****************************************************************************
 �� �� ��  : TAF_CALL_GetRealSpeechVers
 ��������  : �����ʵ��SpeechVers
 �������  : bIsSupportTTYModeFlg   --�Ƿ�֧��TTY MODE
 �������  : pstSpeechVers
 �� �� ֵ  : VOS_VOID

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_CALL_GetRealSpeechVers(
    VOS_BOOL                            bIsSupportTTYModeFlg,
    MN_CALL_BC_SPEECH_VERS_STRU        *pstSpeechVers
)
{
    VOS_UINT32                          i;

    if (VOS_FALSE == bIsSupportTTYModeFlg)
    {
        PS_MEM_CPY(pstSpeechVers,&f_stMnCallSphVers,sizeof(MN_CALL_BC_SPEECH_VERS_STRU));
        return;
    }

    pstSpeechVers->ucCnt = 0;

    for (i = 0; i < f_stMnCallSphVers.ucCnt; i++)
    {
        if (MN_CALL_BC_VAL_SPH_VER_FR_5 == f_stMnCallSphVers.aucVers[i])
        {
            continue;
        }

        pstSpeechVers->aucVers[pstSpeechVers->ucCnt] = f_stMnCallSphVers.aucVers[i];
        pstSpeechVers->ucCnt++;
    }

    return;
}


VOS_UINT32  MN_CALL_BuildBcForSpeech(
    NAS_CC_IE_BC_STRU                   *pstBc,
    MN_CALL_DIR_ENUM_U8                 enCallDir,
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucExtVal;
    NAS_CC_IE_BC_OCTET3B_STRU           *pstOctet3x = VOS_NULL_PTR;
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* Added by w00316404 for TTY MODE, 2015-02-07 Begin */
    VOS_BOOL                            bIsSupportTTYModeFlg;
    MN_CALL_BC_SPEECH_VERS_STRU         stSpeechVers;

    bIsSupportTTYModeFlg                = TAF_CALL_IsSupportTTYMode();
    PS_MEM_SET(&stSpeechVers, 0x00, sizeof(MN_CALL_BC_SPEECH_VERS_STRU));
    /* Added by w00316404 for TTY MODE, 2015-02-07 end */

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();

    if (f_stMnCallSphVers.ucCnt > MN_CALL_BC_MAX_SPH_VER_NUM)
    {
        MN_ERR_LOG("f_stMnCallSphVers.ucCnt > MN_CALL_BC_MAX_SPH_VER_NUM");
        return VOS_ERR;
    }

    /* ���ô���BC���� */
    NAS_IE_SET_PRESENT(pstBc);

    /* ��дBC������Octet 3*/
    if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucAlsSupportFlg )
    {

        if ( ( MN_CALL_ALS_LINE_NO_2 == MN_CALL_GetAlsLineInfo() )
          && ( MN_CALL_DIR_MT != enCallDir )
          && ( MN_CALL_TYPE_EMERGENCY != enCallType ) )
        {
            /*ITC��Ҫ���ݵ�ǰʹ�õ���·�Ž��и�ֵ,��·1ʱITCȡֵspeech,��·2ʱȡ
              ֵAuxiliary speech*/
            pstBc->Octet3.InfoTransCap = NAS_CC_ITC_AUXILIARY_SPEECH;
        }
        else
        {
            pstBc->Octet3.InfoTransCap = NAS_CC_ITC_SPEECH;
        }
    }
    else
    {
        pstBc->Octet3.InfoTransCap = NAS_CC_ITC_SPEECH;
    }

    pstBc->Octet3.TransferMode = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_TRANS_MOD);
    pstBc->Octet3.CodingStd = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_CODING_STD);
    pstBc->Octet3.RadioChReq = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_RCR);

    /* Modified by w00316404 for TTY MODE, 2015-02-07 Begin */
    /* ֧��TTYģʽʱ����֧��AMRWB������� */
    TAF_CALL_GetRealSpeechVers(bIsSupportTTYModeFlg, &stSpeechVers);

    if (stSpeechVers.ucCnt > 0)
    {
        /* ��Ҫ��BC���г�speech version */
        pstBc->Octet3.Ext = MN_CALL_BC_VAL_EXT_EXTEND;
        /* ����û���趨EXT�ĺ궨�壬��ʱ��0��1����ʾ */
        for (i=0; i < stSpeechVers.ucCnt; i++)
        {
            if (0 == i)
            {
                /* Octet3a�ĸ�ֵ */
                pstBc->Octet3a.SpeechVer = stSpeechVers.aucVers[i];
                pstBc->Octet3a.Spare = 0;
                pstBc->Octet3a.Ctm = ((VOS_TRUE == bIsSupportTTYModeFlg) ? NAS_CC_CTM_TEXT_SUPPORTED : NAS_CC_CTM_TEXT_NOT_SUPPORTED);
                pstBc->Octet3a.Coding= 0;

                /* ������û�к������ݣ��趨ext��ֵ */
                ucExtVal = (stSpeechVers.ucCnt > 1) ? MN_CALL_BC_VAL_EXT_EXTEND : MN_CALL_BC_VAL_EXT_NO_EXT;
                pstBc->Octet3a.Ext = ucExtVal;
                pstOctet3x = (NAS_CC_IE_BC_OCTET3B_STRU*)&pstBc->Octet3a;
            }
            else
            {
                /* Octet3a֮��Octet3x(x=b,c,d,e)�ĸ�ֵ��*/
                pstOctet3x = ((NAS_CC_IE_BC_OCTET3B_STRU*)(&pstBc->Octet3b) + i) - 1;
                pstOctet3x->SpeechVer = stSpeechVers.aucVers[i];
                pstOctet3x->Spare = 0;
                pstOctet3x->Coding= 0;

                /* ������û�к������ݣ��趨ext��ֵ */
                ucExtVal = (stSpeechVers.ucCnt == (i + 1)) ? MN_CALL_BC_VAL_EXT_NO_EXT : MN_CALL_BC_VAL_EXT_EXTEND ;
                pstOctet3x->Ext = ucExtVal;

            }
        }
        pstBc->LastOctOffset = ((VOS_UINT8)((VOS_UINT32)pstOctet3x - (VOS_UINT32)pstBc) - 1);
    }
    else
    {
        /* ����Ҫ��BC���г�speech version */
        pstBc->Octet3.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
        NAS_IE_SET_LAST_OCTET_OFFSET(pstBc, Octet3);
    }
    /* Modified by w00316404 for TTY MODE, 2015-02-07 end */

    /* ����ҵ���BC������û��4~7�Ŀ�ѡ�ֽ� */
    /* ���ṹ�ǽṹ�� */

    return VOS_OK;

} /* MN_CALL_BuildBcForSpeech */

/*****************************************************************************
 �� �� ��  : MN_CALL_GetWaiurFromFunr
 ��������  : ��ȡ��ǰ������Ҫ�Ŀտ��û����ʣ�
 �������  : NULL
 �������  : NULL
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��7��10��
    ��    ��   : ��ӳ��62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_CALL_GetWaiurFromFunr(
    VOS_UINT32                          ulFnur
)
{
    VOS_UINT32                          ulWaiur;

    switch (ulFnur)
    {
    case MN_CALL_BC_VAL_FNUR_9K6:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_9K6;
        break;

    case MN_CALL_BC_VAL_FNUR_14K4:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_14K4;
        break;

    case MN_CALL_BC_VAL_FNUR_19K2:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_19K2;
        break;

    case MN_CALL_BC_VAL_FNUR_28K8:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_28K8;
        break;

    case MN_CALL_BC_VAL_FNUR_38K4:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_38K4;
        break;

    case MN_CALL_BC_VAL_FNUR_48K:/*GSM only*/
        ulWaiur = MN_CALL_BC_VAL_WAIUR_9K6;
        break;

    case MN_CALL_BC_VAL_FNUR_56K:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_57K6;
        break;

    case MN_CALL_BC_VAL_FNUR_64K:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_NA; /* !!Currently,inavailable; */
        break;

    case MN_CALL_BC_VAL_FNUR_33K6:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_38K4;
        break;

    case MN_CALL_BC_VAL_FNUR_32K:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_38K4;
        break;

    default:
        ulWaiur = MN_CALL_BC_VAL_WAIUR_NA;
        break;
    }

    return ulWaiur;
}




VOS_UINT32  MN_CALL_BuildBcForData(
    MN_CALL_TA_MODE_ENUM_UINT8          enTaMode,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfg,
    NAS_CC_IE_BC_STRU                   *pstBc
)
{
    VOS_UINT8                           ucUserRate;
    VOS_UINT8                           ucFnur;
    VOS_UINT8                           ucVarParm;
    MN_CALL_VAR_PARM_ENUM               enVarParmType;

    /* Get information from +CBST parmameter */
    enVarParmType = MN_CALL_GetInfoFromBstSpeed
        (pstDataCfg->enSpeed, &ucUserRate, &ucFnur, &ucVarParm);

    if (MN_CALL_VAR_PARM_ERROR == enVarParmType)
    {
        MN_ERR_LOG("Failed to get info from +CBST parmameter.");
        return VOS_ERR;
    }

    /* ITC */
    if (MN_CALL_TA_MODE_FAX_CLASS1 == enTaMode)
    {
        pstBc->Octet3.InfoTransCap = NAS_CC_ITC_FAX;
    }
    else
    {
        if ((MN_CALL_CSD_NAME_ASYNC_UDI == pstDataCfg->enName)
         || (MN_CALL_CSD_NAME_SYNC_UDI == pstDataCfg->enName))
        {
            if ((MN_CALL_VAR_PARM_MT == enVarParmType)
             || (MN_CALL_VAR_PARM_OMT == enVarParmType))
            {
                pstBc->Octet3.InfoTransCap = NAS_CC_ITC_3D1K;
            }
            else
            {
                pstBc->Octet3.InfoTransCap = NAS_CC_ITC_UDI;
            }
        }
        else
        {
            pstBc->Octet3.InfoTransCap = NAS_CC_ITC_OTHER;
        }
    }
    pstBc->Octet3.TransferMode = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_TRANS_MOD);
    pstBc->Octet3.CodingStd = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_CODING_STD);
    pstBc->Octet3.RadioChReq = NAS_CC_RADIO_CH_FULL_RATE;
    /* No Octet 3a for data call */
    pstBc->Octet3.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;

    /* Octet 4 */
    pstBc->Octet4.Establishment   = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_ESTABLI);
    pstBc->Octet4.Nirr      = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_NIRR);
    pstBc->Octet4.Configuation  = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_CONFIGUR);
    pstBc->Octet4.DuplexMode  = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_DUPL_MODE);
    if (MN_CALL_CSD_CE_NT == pstDataCfg->enConnElem)
    {
        pstBc->Octet4.Structure = NAS_CC_STRUCTURE_STRUCTERD;
    }
    else
    {
        pstBc->Octet4.Structure = NAS_CC_STRUCTURE_UNSTRUCTURED;
    }
    pstBc->Octet4.Compression  = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_COMPRESS);
    pstBc->Octet4.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;

    /* Octet 5 */
    pstBc->Octet5.SigAccProtocol   = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_SIGNAL);
    if (MN_CALL_VAR_PARM_RA == enVarParmType)
    {
        pstBc->Octet5.RateAdaption = ucVarParm;
    }
    else if (MN_CALL_VAR_PARM_ORA == enVarParmType)
    {
        pstBc->Octet5.RateAdaption = MN_CALL_BC_VAL_RA_OTHER;
    }
    else
    {
        pstBc->Octet5.RateAdaption = MN_CALL_BC_VAL_RA_NO;
    }
    pstBc->Octet5.AccessId = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_ACCESS_ID);

    /* If RA is other RA or ITC is other ITC, Octet 5a shall be included */
    if ((NAS_CC_RATE_ADAPTION_OTHER == pstBc->Octet5.RateAdaption)
     || (NAS_CC_ITC_OTHER == pstBc->Octet3.InfoTransCap))
    {
        pstBc->Octet5.Ext = MN_CALL_BC_VAL_EXT_EXTEND;
        pstBc->Octet5a.OtherITC = NAS_CC_OTHER_ITC_RDI;
        if(MN_CALL_VAR_PARM_ORA == enVarParmType)
        {
            pstBc->Octet5a.OtherRA = ucVarParm;
        }
        else
        {
            pstBc->Octet5a.OtherRA = NAS_CC_OTHER_RA_V120;
        }
        pstBc->Octet5a.Spare = 0;

        /* If ORA is V.120, Octet 5b shall be included */
        if ((NAS_CC_RATE_ADAPTION_OTHER == pstBc->Octet5.RateAdaption)
         && (NAS_CC_OTHER_RA_V120 == pstBc->Octet5a.OtherRA))
        {
            pstBc->Octet5a.Ext          = MN_CALL_BC_VAL_EXT_EXTEND;

            pstBc->Octet5b.Spare        = 0;
            pstBc->Octet5b.InOutBandNeg = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_INB_NEG);
            pstBc->Octet5b.Assignore    = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_ASSIGNOR);
            pstBc->Octet5b.LLI          = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_LLI);
            pstBc->Octet5b.OpMode       = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_MODE);
            pstBc->Octet5b.MultiFrame   = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_MULTI_FRAME);
            pstBc->Octet5b.Header       = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_HDR_NO_HDR);
            pstBc->Octet5b.Ext        = MN_CALL_BC_VAL_EXT_NO_EXT;
        }
        else
        {
            pstBc->Octet5a.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
        }
    }
    else
    {
        pstBc->Octet5.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
    }

    /* Octet 6 */
    if ((MN_CALL_CSD_NAME_ASYNC_UDI == pstDataCfg->enName)
     || (MN_CALL_CSD_NAME_ASYNC_RDI == pstDataCfg->enName))
    {
        pstBc->Octet6.SyncAsync = NAS_CC_ASYNC;
    }
    else if ((MN_CALL_CSD_NAME_SYNC_UDI == pstDataCfg->enName)
          || (MN_CALL_CSD_NAME_SYNC_RDI == pstDataCfg->enName))
    {
        pstBc->Octet6.SyncAsync = NAS_CC_SYNC;
    }
    else
    {
        MN_ERR_LOG("Bad name parmameter of CBST setting.");
        return VOS_ERR;
    }
    pstBc->Octet6.UserInfoL1 = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_UIL1P);
    pstBc->Octet6.Layer1Id   = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_LAYER1_ID);
    pstBc->Octet6.Ext = MN_CALL_BC_VAL_EXT_EXTEND;

    /* Octet 6a */
    pstBc->Octet6a.UserRate         = ucUserRate;
    pstBc->Octet6a.NumOfDataBits    = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_N_DATA_BIT);
    pstBc->Octet6a.Negotiation      = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_NEGOTIATION);
    pstBc->Octet6a.NumOfStopBits    = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_N_STOP_BIT);
    pstBc->Octet6a.Ext              = MN_CALL_BC_VAL_EXT_EXTEND;

    /* Octet 6b */
    pstBc->Octet6b.ParityInfo   = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_PARITY);
    pstBc->Octet6b.RxNIC        = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_NIC_ON_RX);
    pstBc->Octet6b.TxNIC        = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_NIC_ON_TX);
    if (NAS_CC_USER_RATE_9600 == pstBc->Octet6a.UserRate)
    {
        pstBc->Octet6b.InterRate = NAS_CC_INTER_RATE_16K;
    }
    else
    {
        pstBc->Octet6b.InterRate = NAS_CC_INTER_RATE_8K;
    }
    pstBc->Octet6b.Ext       = MN_CALL_BC_VAL_EXT_EXTEND;

    /* Octet 6c */
    /* Modem type */
    if (MN_CALL_VAR_PARM_MT == enVarParmType)
    {
        pstBc->Octet6c.ModemType = ucVarParm;
    }
    else if(MN_CALL_VAR_PARM_OMT == enVarParmType)
    {
        /* When the MT indicates "autobauding" , "modem for
        undefined interface" or "none", the OMT shall be set
        to "no other modem type". Any other values of the MT
        is overridden by the OMT value. (27.001) */
        pstBc->Octet6c.ModemType = MN_CALL_BC_VAL_MT_V21;
    }
    else
    {
        pstBc->Octet6c.ModemType = MN_CALL_BC_VAL_MT_NONE;
    }

    /* Connection element */
    if (MN_CALL_CSD_CE_T == pstDataCfg->enConnElem)
    {
        pstBc->Octet6c.ConnElement = NAS_CC_CONNECTION_T;
    }
    else if(MN_CALL_CSD_CE_NT == pstDataCfg->enConnElem)
    {
        pstBc->Octet6c.ConnElement = NAS_CC_CONNECTION_NT;
    }
    else if(MN_CALL_CSD_CE_BOTH_T == pstDataCfg->enConnElem)
    {
        pstBc->Octet6c.ConnElement = NAS_CC_CONNECTION_BOTH_T;
    }
    else
    {
        pstBc->Octet6c.ConnElement = NAS_CC_CONNECTION_BOTH_NT;
    }
    pstBc->Octet6c.Ext = MN_CALL_BC_VAL_EXT_EXTEND;

    /* Octet 6d */
    pstBc->Octet6d.FNUR = ucFnur;
    if (MN_CALL_VAR_PARM_OMT == enVarParmType)
    {
        pstBc->Octet6d.OtherModemType = ucVarParm;
    }
    else
    {
        pstBc->Octet6d.OtherModemType = NAS_CC_OTHER_MODEM_NONE;
    }
    pstBc->Octet6d.Ext = MN_CALL_BC_VAL_EXT_EXTEND;

    /* ���ҵ����Fax��Modem type��Other modem type����Ϊnone */
    if (NAS_CC_ITC_FAX == pstBc->Octet3.InfoTransCap)
    {
        pstBc->Octet6c.ModemType      = MN_CALL_BC_VAL_MT_NONE;
        pstBc->Octet6d.OtherModemType = MN_CALL_BC_VAL_OMT_NONE;
    }

    /* Octet 6e */
    pstBc->Octet6e.MaxTchNum = NAS_CC_MAX_1TCH;
    pstBc->Octet6e.TchF96    = NAS_CC_TCH_F9_6_NOT_ACCEPTABLE;
    pstBc->Octet6e.TchF144   = NAS_CC_TCH_F14_4_NOT_ACCEPTABLE;
    pstBc->Octet6e.Ext       = MN_CALL_BC_VAL_EXT_EXTEND;

    /* Octet 6f */
    if (MN_CALL_CSD_CE_T == pstDataCfg->enConnElem)
    {
        /* This parameter shall be included only for
        non-transparent services and in case the
        parameter 'fixed network user rate' is included. (27.001) */
        pstBc->Octet6f.WAIUR = NAS_CC_WAIUR_NONE;
    }
    else
    {
        /* This parameter has to be included if EDGE channel coding(s)
        are included in Acceptable channel codings. (27.001) */

        /* Ŀǰֻ֧��һ��TCH���ò���������ΪNot applicable */
        if ((MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6c.Ext)
         && (NAS_CC_FNUR_NONE != pstBc->Octet6d.FNUR))
        {
            /*lint -e522*/
            pstBc->Octet6f.WAIUR = MN_CALL_GetWaiurFromFunr((pstBc->Octet6d.FNUR));
            /*lint +e522*/
        }
        else
        {
            pstBc->Octet6f.WAIUR = NAS_CC_WAIUR_9600;
        }
    }

    pstBc->Octet6f.UIMI = NAS_CC_UIMI_NONE;
    /* Octet 6g�ݲ���д, only for EDGE */
    pstBc->Octet6f.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;

    /* The MS is not allowed to indicate support of both transparent
    and non transparent, if the MS also requests out-band flow control,
    i.e. it does not indicate a layer 2 protocol. (27.001)*/
    if (NAS_CC_CONNECTION_T != pstBc->Octet6c.ConnElement)
    {
        NAS_IE_SET_LAST_OCTET_OFFSET(pstBc, Octet7);
        pstBc->Octet7.UserInfoL2 = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_UIL2P);
        pstBc->Octet7.Layer2Id = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_LAYER2_ID);
        pstBc->Octet7.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
    }
    else
    {
        /* ��Я��octet 7������ʹ��ITU-T V.42 out-band���ط�ʽ */
        NAS_IE_SET_LAST_OCTET_OFFSET(pstBc, Octet6f);
    }

    NAS_IE_SET_OCTET(pstBc, IsExist, 1);

    return VOS_OK;

} /* MN_CALL_BuildBcForData */



VOS_UINT32  MN_CALL_BuildBcOfSetup(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_MODE_ENUM_U8                enCallMode,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfg,
    NAS_CC_IE_BC_STRU                   *pstBc1,
    NAS_CC_IE_BC_STRU                   *pstBc2
)
{
    VOS_UINT32                          ulBcCnt = 0;
    VOS_UINT32                          ulRes;

    /* �����һ��BC���� */
    switch(enCallType)
    {
    case MN_CALL_TYPE_VOICE:
#if (FEATURE_ON == FEATURE_ECALL)
    case MN_CALL_TYPE_TEST:
    case MN_CALL_TYPE_RECFGURATION:
#endif
        /* �����������е�BC���� */
        ulRes = MN_CALL_BuildBcForSpeech(pstBc1,MN_CALL_DIR_MO,MN_CALL_TYPE_VOICE);
        break;

    case MN_CALL_TYPE_EMERGENCY:
#if (FEATURE_ON == FEATURE_ECALL)
    case MN_CALL_TYPE_MIEC:
    case MN_CALL_TYPE_AIEC:
#endif
        /* ����������е�BC���� */
        ulRes = MN_CALL_BuildBcForSpeech(pstBc1,MN_CALL_DIR_MO,MN_CALL_TYPE_EMERGENCY);
        break;

    case MN_CALL_TYPE_CS_DATA:
    case MN_CALL_TYPE_VIDEO:
    case MN_CALL_TYPE_VIDEO_TX:
    case MN_CALL_TYPE_VIDEO_RX:
        /* �������ݵ�BC���� */
        ulRes = MN_CALL_BuildBcForData(MN_CALL_TA_MODE_DATA, pstDataCfg, pstBc1);
        break;

    case MN_CALL_TYPE_FAX:
        /* ���촫���BC���� */
        ulRes = MN_CALL_BuildBcForData(MN_CALL_TA_MODE_FAX_CLASS1, pstDataCfg, pstBc1);
        break;
    /*���� MN_CALL_TYPE_VIDEO ����δ���*/
    default:
        ulRes = VOS_ERR;
        break;
    }

    if (ulRes != VOS_OK)
    {
        return 0;
    }

    ulBcCnt++;

    if (MN_CALL_MODE_AVF == enCallMode)
    {
        /* ����ڶ���BC���� */
        if (MN_CALL_TYPE_VOICE == enCallType)
        {
            /* ��һ����������������������ڹ���FAX��BC���� */
            ulRes = MN_CALL_BuildBcForData(MN_CALL_TYPE_FAX, pstDataCfg, pstBc2);
        }
        else
        {
            /* ��һ������������ݲ��������ڹ����������е�BC���� */
            ulRes = MN_CALL_BuildBcForSpeech(pstBc2,MN_CALL_DIR_MO,MN_CALL_TYPE_VOICE);
        }

        if (ulRes != VOS_OK)
        {
            return 0;
        }

        ulBcCnt++;
    }

    return ulBcCnt;

} /* MN_CALL_BuildBcOfSetup */


/*****************************************************************************
 �� �� ��  : MN_CALL_BcCompChkOct3
 ��������  : ��BC������Octet3, 3a��3b etc���м����Լ��
 �������  : pstBc - Ҫ����BC����
 �������  : ��
 �� �� ֵ  : VOS_OK  - �����Լ��ͨ��
             VOS_ERR - �����Լ��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��12��1��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_BcCompChkOct3(
    const NAS_CC_IE_BC_STRU             *pstBc
)
{
    /* ���Octet 3 */
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_ITC, pstBc->Octet3.InfoTransCap);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_TRANS_MOD, pstBc->Octet3.TransferMode);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_CODING_STD, pstBc->Octet3.CodingStd);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_RCR, pstBc->Octet3.RadioChReq);

    /* ����Э�飬����Octet 3a */

    /* ���ͨ�� */
    return VOS_OK;

} /* MN_CALL_BcCompChkOct3 */


/*****************************************************************************
 �� �� ��  : MN_CALL_BcCompChkOct4
 ��������  : ��BC������Octet4���м����Լ��
 �������  : pstBc - Ҫ����BC����
 �������  : ��
 �� �� ֵ  : VOS_OK  - �����Լ��ͨ��
             VOS_ERR - �����Լ��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��12��1��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_BcCompChkOct4(
    const NAS_CC_IE_BC_STRU             *pstBc
)
{
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_ESTABLI, pstBc->Octet4.Establishment);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_NIRR, pstBc->Octet4.Nirr);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_CONFIGUR, pstBc->Octet4.Configuation);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_DUPL_MODE, pstBc->Octet4.DuplexMode);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_STRUCTURE, pstBc->Octet4.Structure);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_COMPRESS, pstBc->Octet4.Compression);

    /* Octet 4��Ext�ֶο϶�Ϊ1 */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet4.Ext)
    {
        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }

} /* MN_CALL_BcCompChkOct4 */


/*****************************************************************************
 �� �� ��  : MN_CALL_BcCompChkOct5
 ��������  : ��BC������Octet5, 5a, 5b���м����Լ��
 �������  : pstBc - Ҫ����BC����
 �������  : ��
 �� �� ֵ  : VOS_OK  - �����Լ��ͨ��
             VOS_ERR - �����Լ��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��12��1��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_BcCompChkOct5(
    const NAS_CC_IE_BC_STRU             *pstBc
)
{
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_SIGNAL, pstBc->Octet5.SigAccProtocol);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_RA, pstBc->Octet5.RateAdaption);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_ACCESS_ID, pstBc->Octet5.AccessId);

    /* ���Octet 5a����, ��Ҫ���5a */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet5.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_ORA, pstBc->Octet5a.OtherRA);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_OTHER_ITC, pstBc->Octet5a.OtherITC);
    }
    else
    {
        /* ���ITC��RAΪOther����Octet 5a�����ڽ����¼��ʧ�� */
        if ((NAS_CC_ITC_OTHER== pstBc->Octet3.InfoTransCap)
         || (NAS_CC_RATE_ADAPTION_OTHER == pstBc->Octet5.RateAdaption))
        {
            return VOS_ERR;
        }
        else
        {
            /* �����������سɹ� */
            return VOS_OK;
        }
    }

    /* ���Octet 5b����, ��Ҫ���5b */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet5a.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_INB_NEG, pstBc->Octet5b.InOutBandNeg);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_ASSIGNOR, pstBc->Octet5b.Assignore);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_LLI, pstBc->Octet5b.LLI);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_MODE, pstBc->Octet5b.OpMode);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_MULTI_FRAME, pstBc->Octet5b.MultiFrame);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_HDR_NO_HDR, pstBc->Octet5b.Header);
    }
    else
    {
        /* ���RAΪV120����Octet 5b�����ڽ����¼��ʧ�� */
        if ((NAS_CC_RATE_ADAPTION_OTHER == pstBc->Octet5.RateAdaption)
         && (NAS_CC_OTHER_RA_V120 == pstBc->Octet5a.OtherRA))
        {
            return VOS_ERR;
        }
        else
        {
            /* �����������سɹ� */
            return VOS_OK;
        }
    }

    return VOS_OK;

} /* MN_CALL_BcCompChkOct5 */


/*****************************************************************************
 �� �� ��  : MN_CALL_BcCompChkOct6
 ��������  : ��BC������Octet6, 6a, 6b, 6c, 6d, 6e, 6f, 6g���м����Լ��
 �������  : pstBc - Ҫ����BC����
 �������  : ��
 �� �� ֵ  : VOS_OK  - �����Լ��ͨ��
             VOS_ERR - �����Լ��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��12��1��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_BcCompChkOct6(
    const NAS_CC_IE_BC_STRU             *pstBc
)
{
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_SYNC_ASYNC, pstBc->Octet6.SyncAsync);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_UIL1P, pstBc->Octet6.UserInfoL1);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_LAYER1_ID, pstBc->Octet6.Layer1Id);

    /* ���Octet 6a����, ��Ҫ���6a */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_USER_RATE, pstBc->Octet6a.UserRate);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_N_DATA_BIT, pstBc->Octet6a.NumOfDataBits);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_NEGOTIATION, pstBc->Octet6a.Negotiation);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_N_STOP_BIT, pstBc->Octet6a.NumOfStopBits);
    }
    else
    {
        /* ���Octet 6���ڣ���Octet 6a������� */
        return VOS_ERR;
    }

    /* ���Octet 6b����, ��Ҫ���6b */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6a.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_PARITY, pstBc->Octet6b.ParityInfo);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_NIC_ON_RX, pstBc->Octet6b.RxNIC);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_NIC_ON_TX, pstBc->Octet6b.TxNIC);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_INTMD_RATE, pstBc->Octet6b.InterRate);
    }
    else
    {
        /* ���Octet 6���ڣ���Octet 6b������� */
        return VOS_ERR;
    }

    /* ���Octet 6c����, ��Ҫ���6c */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6b.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_MODEM_TYPE, pstBc->Octet6c.ModemType);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_CE, pstBc->Octet6c.ConnElement);

        /* ͬ����͸������ģʽ����ȷ��֧�ֵ� */
        if ((NAS_CC_CONNECTION_NT == pstBc->Octet6c.ConnElement)
         && (NAS_CC_SYNC == pstBc->Octet6.SyncAsync))
        {
            return VOS_ERR;
        }
    }
    else
    {
        /* ���Octet 6���ڣ���Octet 6c������� */
        return VOS_ERR;
    }

    /* ���Octet 6d����, ��Ҫ���6d */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6c.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_FNUR, pstBc->Octet6d.FNUR);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_OMT, pstBc->Octet6d.OtherModemType);
    }
    else
    {
        /* �����������سɹ� */
        return VOS_OK;
    }

    /* ���Octet 6e����, ��Ҫ���6e */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6d.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_MAX_TCH, pstBc->Octet6e.MaxTchNum);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_ACC, NAS_IE_GET_OCTET(pstBc,Octet6e));
    }
    else
    {
        /* �����������سɹ� */
        return VOS_OK;
    }

    /* ���Octet 6f����, ��Ҫ���6f */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6e.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_WAIUR, pstBc->Octet6f.WAIUR);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_UIMI, pstBc->Octet6f.UIMI);
    }
    else
    {
        /* �����������سɹ� */
        return VOS_OK;
    }

    /* ���Octet 6g����, ��Ҫ���6g */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet6f.Ext)
    {
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_ASYM_IND, pstBc->Octet6g.CCAI);
        MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_EXT_ACC, NAS_IE_GET_OCTET(pstBc,Octet6g));
    }
    else
    {
        /* �����������سɹ� */
        return VOS_OK;
    }

    return VOS_OK;

} /* MN_CALL_BcCompChkOct6 */


/*****************************************************************************
 �� �� ��  : MN_CALL_BcCompChkOct7
 ��������  : ��BC������Octet7���м����Լ��
 �������  : pstBc - Ҫ����BC����
 �������  : ��
 �� �� ֵ  : VOS_OK  - �����Լ��ͨ��
             VOS_ERR - �����Լ��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��12��1��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_BcCompChkOct7(
    const NAS_CC_IE_BC_STRU             *pstBc
)
{
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_UIL2P, pstBc->Octet7.UserInfoL2);
    MN_CALL_BC_CHECK_FIELD(MN_CALL_BC_FLD_LAYER2_ID, pstBc->Octet7.Layer2Id);
    /* Octet 7��Ext�ֶο϶�Ϊ1 */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBc->Octet7.Ext)
    {
        return VOS_ERR;
    }
    else
    {
        return VOS_OK;
    }

} /* MN_CALL_BcCompChkOct7 */



VOS_UINT32  MN_CALL_BcCompChk(
    const NAS_CC_IE_BC_STRU            *pstBc
)
{
    if (VOS_NULL_PTR == pstBc)
    {
        return VOS_ERR;
    }

    /* ���Octet3, 3a, 3b etc */
    if (VOS_ERR == MN_CALL_BcCompChkOct3(pstBc))
    {
        return VOS_ERR;
    }

    /* ���Octet 4 */
    if (pstBc->LastOctOffset >
            ((VOS_UINT32)(&pstBc->Octet4) - (VOS_UINT32)(&pstBc->Octet3)))
    {
        if (VOS_ERR == MN_CALL_BcCompChkOct4(pstBc))
        {
            return VOS_ERR;
        }
    }
    else
    {
        /* ���ڷ��������У�Octet 4�����ڽ����¼��ʧ�� */
        if ( (pstBc->Octet3.InfoTransCap != MN_CALL_BC_VAL_ITC_SPEECH)
          && (pstBc->Octet3.InfoTransCap != MN_CALL_BC_VAL_ITC_AUX_SPEECH) )
        {
            return VOS_ERR;
        }
    }

    /* ���Octet 5 */
    if (pstBc->LastOctOffset >
            ((VOS_UINT32)(&pstBc->Octet5) - (VOS_UINT32)(&pstBc->Octet3)))
    {
        if (VOS_ERR == MN_CALL_BcCompChkOct5(pstBc))
        {
            return VOS_ERR;
        }
    }
    else
    {
        /* ���ڷ��������У�Octet 5�����ڽ����¼��ʧ�� */
        if ( (pstBc->Octet3.InfoTransCap != MN_CALL_BC_VAL_ITC_SPEECH)
          && (pstBc->Octet3.InfoTransCap != MN_CALL_BC_VAL_ITC_AUX_SPEECH))
        {
            return VOS_ERR;
        }
    }

    /* ���Octet 6 */
    if (pstBc->LastOctOffset >
            ((VOS_UINT32)(&pstBc->Octet6) - (VOS_UINT32)(&pstBc->Octet3)))
    {
        if (VOS_ERR == MN_CALL_BcCompChkOct6(pstBc))
        {
            return VOS_ERR;
        }
    }
    else
    {
        /* ���ڷ��������У�Octet 6�����ڽ����¼��ʧ�� */
        if ( (pstBc->Octet3.InfoTransCap != MN_CALL_BC_VAL_ITC_SPEECH)
          && (pstBc->Octet3.InfoTransCap != MN_CALL_BC_VAL_ITC_AUX_SPEECH))
        {
            return VOS_ERR;
        }
    }

    /* ���Octet 7 */
    if (pstBc->LastOctOffset >
            ((VOS_UINT32)(&pstBc->Octet7) - (VOS_UINT32)(&pstBc->Octet3)))
    {
        if (VOS_ERR == MN_CALL_BcCompChkOct7(pstBc))
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;

} /* MN_CALL_BcCompChk */

/*****************************************************************************
 �� �� ��  : MN_CALL_NegotSpeechBcForCallConf
 ��������  : Э����������SETUP��Ϣ�е�BC�������õ�CALL CONFIRM��Ϣ��Ҫ��BC������
 �������  : pstBcOfSetup - ��ǰ���õĳ���ҵ�����ͣ���SETUP��Ϣ�ĺ�������ΪVOICEʱ�ò����������ԡ�
             pstBcOfConf     - SETUP��Ϣ�е�BC����
 �������  : pstBcOfConf     - Э�̺��BC����
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��29��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��2��15��
    ��    ��   : w00316404
    �޸�����   : ֧��TTY MODE������£��޸�CTM��־λ
*****************************************************************************/
VOS_VOID  MN_CALL_NegotSpeechBcForCallConf(
    NAS_CC_IE_BC_STRU                   *pstBcOfSetup,
    NAS_CC_IE_BC_STRU                   *pstBcOfConf
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucExtVal;
    NAS_CC_IE_BC_OCTET3B_STRU           *pstOctet3x;
    /* Added by w00316404 for TTY MODE, 2015-02-07 Begin */
    VOS_BOOL                            bIsSupportTTYModeFlg;
    MN_CALL_BC_SPEECH_VERS_STRU         stSpeechVers;

    bIsSupportTTYModeFlg                = TAF_CALL_IsSupportTTYMode();
    PS_MEM_SET(&stSpeechVers, 0x00, sizeof(MN_CALL_BC_SPEECH_VERS_STRU));
    /* Added by w00316404 for TTY MODE, 2015-02-07 end */

    pstOctet3x = VOS_NULL_PTR;
    /* ��BC����������֧�ֵ�speech version */

    /* Modified by w00316404 for TTY MODE, 2015-02-07 Begin */
    /* ֧��TTYģʽʱ����֧��AMRWB������� */
    TAF_CALL_GetRealSpeechVers(bIsSupportTTYModeFlg, &stSpeechVers);

    if (stSpeechVers.ucCnt > 0)
    {
        /* ��Ҫ��BC���г�speech version */
        pstBcOfConf->Octet3.Ext = MN_CALL_BC_VAL_EXT_EXTEND;

        for (i=0; i<stSpeechVers.ucCnt; i++)
        {
            /* Modified by w00316404 for TTY MODE, 2015-02-07 Begin */
            /* ֧��TTYģʽʱ����֧��AMRWB������� */
            if ( (VOS_TRUE == bIsSupportTTYModeFlg)
              && (stSpeechVers.aucVers[i] == MN_CALL_BC_VAL_SPH_VER_FR_5) )
            {
                continue;
            }
            if (0 == i )
            {
                /* Octet3a�ĸ�ֵ */
                pstBcOfConf->Octet3a.SpeechVer = stSpeechVers.aucVers[i];
                pstBcOfConf->Octet3a.Spare = 0;
                pstBcOfConf->Octet3a.Ctm = ((VOS_TRUE == bIsSupportTTYModeFlg) ? NAS_CC_CTM_TEXT_SUPPORTED : NAS_CC_CTM_TEXT_NOT_SUPPORTED);
                pstBcOfConf->Octet3a.Coding = 0;

                /* ������û�к������ݣ��趨ext��ֵ */
                ucExtVal = (stSpeechVers.ucCnt > 1)?
                            MN_CALL_BC_VAL_EXT_EXTEND: MN_CALL_BC_VAL_EXT_NO_EXT;
                pstBcOfConf->Octet3a.Ext = ucExtVal;
                /* Modify by w00316404 for TTY MODE, 2015-02-07 end */
            }
            else
            {
                /* Octet3a֮��Octet3x(x=b,c,d,e)�ĸ�ֵ��*/
                pstOctet3x = ((NAS_CC_IE_BC_OCTET3B_STRU*)(&pstBcOfConf->Octet3b) + i) - 1;
                pstOctet3x->SpeechVer = stSpeechVers.aucVers[i];
                pstOctet3x->Spare = 0;
                pstOctet3x->Coding = 0;

                /* ������û�к������ݣ��趨ext��ֵ */
                ucExtVal = (stSpeechVers.ucCnt == (i + 1))?
                            MN_CALL_BC_VAL_EXT_NO_EXT: MN_CALL_BC_VAL_EXT_EXTEND;
                pstOctet3x->Ext = ucExtVal;

            }
        }
        pstBcOfConf->LastOctOffset = ((VOS_UINT8)((VOS_UINT32)pstOctet3x
                    - (VOS_UINT32)pstBcOfConf) - 1);
    }
    else
    {
        /* ����Ҫ��BC���г�speech version */
        pstBcOfConf->Octet3.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
    }

}

/*****************************************************************************
 �� �� ��  : MN_CALL_NegotUIL2PForCallConf
 ��������  : Э�����ݺ���SETUP��Ϣ�е�BC������UIL2P���õ�CALL CONFIRM��Ϣ��Ҫ��BC������UIL2P��
 �������  : pstBcOfSetup - ��ǰ���õĳ���ҵ�����ͣ���SETUP��Ϣ�ĺ�������ΪVOICEʱ�ò����������ԡ�
             pstBcOfConf     - SETUP��Ϣ�е�BC����
 �������  : pstBcOfConf     - Э�̺��BC����
 �� �� ֵ  : VOS_TRUE ��ʾCALL CONF��Ϣ����ҪЯ����BC������
             VOS_FALSE ��ʾCALL CONF��Ϣ�в���ҪЯ����BC������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��29��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_NegotUIL2PForCallConf(
    NAS_CC_IE_BC_STRU                   *pstBcOfSetup,
    NAS_CC_IE_BC_STRU                   *pstBcOfConf
)
{
    VOS_UINT32                          ulIncBc;

    ulIncBc = VOS_FALSE;
    /* Э��UIL2P */
    if (NAS_CC_CONNECTION_T == pstBcOfSetup->Octet6c.ConnElement)
    {
        /* ��Я��octet 7������ʹ��ITU-T V.42 out-band���ط�ʽ */
        if (pstBcOfSetup->LastOctOffset >
              ((VOS_UINT32)&pstBcOfSetup->Octet7 - (VOS_UINT32)&pstBcOfSetup->Octet3))
        {
            NAS_IE_SET_LAST_OCTET_OFFSET(pstBcOfConf, Octet6);
            ulIncBc = VOS_TRUE;
        }
        else
        {
            ulIncBc = VOS_TRUE;
        }
    }
    else
    {
        if (pstBcOfSetup->LastOctOffset <
              ((VOS_UINT32)&pstBcOfSetup->Octet7 - (VOS_UINT32)&pstBcOfSetup->Octet3))
        {
            NAS_IE_SET_LAST_OCTET_OFFSET(pstBcOfConf, Octet7);
            pstBcOfConf->Octet7.UserInfoL2
                        = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_UIL2P);
            pstBcOfConf->Octet7.Layer2Id
                        = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_LAYER2_ID);
            pstBcOfConf->Octet7.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
            ulIncBc = VOS_TRUE;
        }
        else
        {
            if(NAS_CC_L2_PROTOCOL_ISO6429 != pstBcOfSetup->Octet7.UserInfoL2)
            {
                pstBcOfConf->Octet7.UserInfoL2
                        = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_UIL2P);
                pstBcOfConf->Octet7.Layer2Id
                        = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_LAYER2_ID);
                pstBcOfConf->Octet7.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
                ulIncBc = VOS_TRUE;
            }
        }
    }
    return ulIncBc;
}


VOS_UINT32  MN_CALL_NegotBcForCallConf(
    NAS_CC_IE_BC_STRU                   *pstBcOfSetup,
    NAS_CC_IE_BC_STRU                   *pstBcOfConf
)
{
    VOS_UINT32                          ulIncBc;

    PS_MEM_CPY(pstBcOfConf, pstBcOfSetup, sizeof(NAS_CC_IE_BC_STRU));

    /* Э������ҵ���BC���� */
    if ( (MN_CALL_BC_VAL_ITC_SPEECH == pstBcOfSetup->Octet3.InfoTransCap)
       ||(MN_CALL_BC_VAL_ITC_AUX_SPEECH == pstBcOfSetup->Octet3.InfoTransCap) )
    {
        /* BC shall be included if the "radio channel requirement" of
        the MS is other than "full rate support only mobile station" */
        pstBcOfConf->Octet3.RadioChReq = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_RCR);
        MN_CALL_NegotSpeechBcForCallConf(pstBcOfSetup,pstBcOfConf);
        return VOS_TRUE;
    }

    /* Э������ҵ���BC���� */
    ulIncBc = VOS_FALSE;
    /* Э��Number of data bits */
    if (pstBcOfSetup->Octet6a.NumOfDataBits != MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_N_DATA_BIT))
    {
        pstBcOfConf->Octet6a.NumOfDataBits = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_N_DATA_BIT);
        ulIncBc = VOS_TRUE;
    }

    /* Э��Number of stop bits */
    if (pstBcOfSetup->Octet6a.NumOfStopBits != MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_N_STOP_BIT))
    {
        pstBcOfConf->Octet6a.NumOfStopBits = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_N_STOP_BIT);
        ulIncBc = VOS_TRUE;
    }

    /* Э��Parity */
    if (pstBcOfSetup->Octet6b.ParityInfo != MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_PARITY))
    {
        pstBcOfConf->Octet6b.ParityInfo = MN_CALL_BC_FIXED_FLD_VAL(MN_CALL_BC_FLD_PARITY);
        ulIncBc = VOS_TRUE;
    }

    /* Э��Connection element���˴���ԭ���ķ�����ͬ */
    if ((NAS_CC_CONNECTION_BOTH_T == pstBcOfSetup->Octet6c.ConnElement)
     || (NAS_CC_CONNECTION_T == pstBcOfSetup->Octet6c.ConnElement))
    {

        pstBcOfConf->Octet6c.ConnElement = NAS_CC_CONNECTION_T;
        pstBcOfConf->Octet4.Structure = NAS_CC_STRUCTURE_UNSTRUCTURED;
        ulIncBc = VOS_TRUE;
    }
    else
    {
        pstBcOfConf->Octet6c.ConnElement = NAS_CC_CONNECTION_NT;
        pstBcOfConf->Octet4.Structure = NAS_CC_STRUCTURE_STRUCTERD;
    }

    /* Э��Intermediate rate */
    if (NAS_CC_NIRR_ENABLE == pstBcOfSetup->Octet4.Nirr)
    {
        pstBcOfConf->Octet4.Nirr = NAS_CC_NIRR_DISABLE;
        pstBcOfConf->Octet6b.InterRate = NAS_CC_INTER_RATE_16K;
        ulIncBc = VOS_TRUE;
    }

    /* Э��Modem type ... �ݲ�Э�� */
    if (MN_CALL_BC_VAL_EXT_EXTEND == pstBcOfSetup->Octet6c.Ext)
    {
        /* BC shall be included if bc received in the SETUP message
        included the "fixed network user rate" parameter. (24.008) */
        ulIncBc = VOS_TRUE;

        /* ֪ͨ��������֧��9.6��14.4���ֱ��뷽ʽ�����1��TCH */
        pstBcOfConf->Octet6e.TchF48    = NAS_CC_TCH_F4_8_NOT_ACCEPTABLE;
        pstBcOfConf->Octet6e.TchF96    = NAS_CC_TCH_F9_6_ACCEPTABLE;
        pstBcOfConf->Octet6e.TchF144   = NAS_CC_TCH_F9_6_ACCEPTABLE;
        pstBcOfConf->Octet6e.MaxTchNum = NAS_CC_MAX_1TCH;

        /* UIMI shall be included by the MS only in case
        it was received from the network. (27.001)*/
        if ((MN_CALL_BC_VAL_EXT_EXTEND == pstBcOfSetup->Octet6d.Ext)
         && (MN_CALL_BC_VAL_EXT_EXTEND == pstBcOfSetup->Octet6e.Ext))
        {
            pstBcOfConf->Octet6f.UIMI     = NAS_CC_UIMI_NONE;
            pstBcOfConf->Octet6f.WAIUR  = MN_CALL_BC_VAL_WAIUR_NA;
            pstBcOfConf->Octet6f.Ext    = MN_CALL_BC_VAL_EXT_NO_EXT;
        }
        else
        {
            pstBcOfConf->Octet6d.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
            pstBcOfConf->Octet6e.Ext = MN_CALL_BC_VAL_EXT_NO_EXT;
        }
    }

    ulIncBc = MN_CALL_NegotUIL2PForCallConf(pstBcOfSetup,pstBcOfConf);

    return ulIncBc;

} /* MN_CALL_NegotBcForCallConf */

VOS_UINT32  MN_CALL_BuildBcForSns(
    MN_CALL_SNS_MODE_ENUM_UINT8         enSnsMode,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfg,
    NAS_CC_IE_BC_STRU                   *pstBc1,
    NAS_CC_IE_BC_STRU                   *pstBc2,
    VOS_UINT8                           *pucBcRepInd
)
{
    VOS_UINT32                          ulRslt1,ulRslt2;
    *pucBcRepInd = 0;
    switch(enSnsMode)
    {
    case MN_CALL_SNS_MODE_VOICE:
        if (VOS_OK == MN_CALL_BuildBcForSpeech(pstBc1,MN_CALL_DIR_MT,MN_CALL_TYPE_VOICE))
        {
            return 1;
        }
        else
        {
            return 0;
        }

    case MN_CALL_SNS_MODE_ALTER_VF_V_FIRST:
        ulRslt1 = MN_CALL_BuildBcForSpeech(pstBc1,MN_CALL_DIR_MT,MN_CALL_TYPE_VOICE);
        ulRslt2 = MN_CALL_BuildBcForData(MN_CALL_TA_MODE_FAX_CLASS1, pstDataCfg, pstBc2);
        if ((VOS_OK == ulRslt1) && (VOS_OK == ulRslt2))
        {
            *pucBcRepInd = MN_CALL_REP_IND_ALTER;
            return 2;
        }
        else
        {
            return 0;
        }

    case MN_CALL_SNS_MODE_FAX:
        if (VOS_OK == MN_CALL_BuildBcForData(MN_CALL_TA_MODE_FAX_CLASS1, pstDataCfg, pstBc1))
        {
            return 1;
        }
        else
        {
            return 0;
        }

    case MN_CALL_SNS_MODE_DATA:
        if (VOS_OK == MN_CALL_BuildBcForData(MN_CALL_TA_MODE_DATA, pstDataCfg, pstBc1))
        {
            return 1;
        }
        else
        {
            return 0;
        }

    case MN_CALL_SNS_MODE_ALTER_VF_F_FIRST:
        ulRslt1 = MN_CALL_BuildBcForSpeech(pstBc2,MN_CALL_DIR_MT,MN_CALL_TYPE_VOICE);
        ulRslt2 = MN_CALL_BuildBcForData(MN_CALL_TA_MODE_FAX_CLASS1, pstDataCfg, pstBc1);
        if ((VOS_OK == ulRslt1) && (VOS_OK == ulRslt2))
        {
            *pucBcRepInd = MN_CALL_REP_IND_ALTER;
            return 2;
        }
        else
        {
            return 0;
        }

    default:
        return 0;
    }

} /* MN_CALL_BuildBcForSns */





VOS_VOID  MN_CALL_FillGsmSupCodecList(
    MN_CALL_SUPPORT_CODEC_UNION        *punCodecList
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < f_stMnCallSphVers.ucCnt ; i++ )
    {
        switch ( f_stMnCallSphVers.aucVers[i])
        {
            case MN_CALL_BC_VAL_SPH_VER_FR_1 :
                punCodecList->stSupportCodec.CodecType_GSMFR        = VOS_TRUE;
                break;

            case MN_CALL_BC_VAL_SPH_VER_FR_2 :
                punCodecList->stSupportCodec.CodecType_GSMEFR       = VOS_TRUE;
                break;

            case MN_CALL_BC_VAL_SPH_VER_FR_3 :
                punCodecList->stSupportCodec.CodecType_GSMFRAMR     = VOS_TRUE;
                break;

            case MN_CALL_BC_VAL_SPH_VER_HR_1 :
                punCodecList->stSupportCodec.CodecType_GSMHR        = VOS_TRUE;
                break;

            case MN_CALL_BC_VAL_SPH_VER_HR_3 :
                punCodecList->stSupportCodec.CodecType_GSMHRAMR     = VOS_TRUE;
                break;

            case MN_CALL_BC_VAL_SPH_VER_FR_5 :
                /* Modified by w00316404 for TTY MODE, 2015-02-07 Begin */
                if (VOS_FALSE == TAF_CALL_IsSupportTTYMode())
                {
                    punCodecList->stSupportCodec.CodecType_GSMFRAMRWB   = VOS_TRUE;
                }
                /* Modified by w00316404 for TTY MODE, 2015-02-07 end */
                break;
            default:
                MN_INFO_LOG("MN_CALL_FillGsmSupCodecList: invalid speech version");
                break;
        }
    }
}


VOS_VOID  MN_CALL_FillUmtsSupCodecList(
    MN_CALL_SUPPORT_CODEC_UNION        *punCodecList
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < f_stMnCallUmtsCodecTypes.ucCnt ; i++ )
    {
        switch ( f_stMnCallUmtsCodecTypes.aucUmtsCodec[i])
        {
            case MN_CALL_UMTS_CODEC_TYPE_AMR :
                punCodecList->stSupportCodec.CodecType_UMTSAMR     = VOS_TRUE;
                break;

            case MN_CALL_UMTS_CODEC_TYPE_AMR2 :
                punCodecList->stSupportCodec.CodecType_UMTSAMR2     = VOS_TRUE;
                break;

            case MN_CALL_UMTS_CODEC_TYPE_AMRWB :
                /* Modified by w00316404 for TTY MODE, 2015-02-07 Begin */
                if (VOS_FALSE == TAF_CALL_IsSupportTTYMode())
                {
                    punCodecList->stSupportCodec.CodecType_UMTSAMRWB   = VOS_TRUE;
                }
                /* Modified by w00316404 for TTY MODE, 2015-02-07 end */
                break;
            default:
                MN_INFO_LOG("MN_CALL_FillUmtsSupCodecList: invalid speech version");
                break;
        }
    }
}


/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
