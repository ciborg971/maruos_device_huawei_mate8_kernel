



/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#define TAF_NEED_TAF_TAFM_LOCAL_INC 1


#include "TafClientApi.h"
#include "MnComm.h"
#include "Nasrrcinterface.h"
#include "UsimPsInterface.h"
#include "UsimPsApi.h"
#include "PsCommonDef.h"
#include "NVIM_Interface.h"
#include "rfa.h"
/*#include "LightLED.h"
 */
#include "mdrv.h"

#include "NasMmlLib.h"
#include "siappstk.h"

#include "MmaAppLocal.h"
#include "NasComm.h"
#include "NVIM_Interface.h"

#include "ScInterface.h"

#include "MnErrorCode.h"

#include "TafApsComFunc.h"
#include "GasNvInterface.h"

#if ( FEATURE_ON == FEATURE_LTE )
#include "LPsNvInterface.h"
#include "LNvCommon.h"
#endif


#ifdef NAS_STUB
#include "usimmbase.h"
#endif
#include "TafMmaProcNvim.h"
#include "TafMmaMain.h"
#include "TafMmaPreProcAct.h"
#include "TafMmaMntn.h"


#if ( FEATURE_ON == FEATURE_LTE )
#include "gen_msg.h"
#include "msp_errno.h"
#include "v_lib.h"
#include "msp_nvim.h"
#endif

#if (VOS_WIN32 == VOS_OS_VER)
#include "nvim_fileoperateinterface.h"
#endif

#include "TafApsProcNvim.h"

#include "TafSdcCtx.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "TafMmaNetworkNameTbl.h"

#include "NasUsimmApi.h"

#include "TafStdlib.h"

#include "Taf_Status.h"

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
#include "MtcMmaInterface.h"
#endif
#include "TafMmaSndTaf.h"
#include "TafMmaSndInternalMsg.h"

#include "TafMmaSndApp.h"

#include "TafMmaProcUsim.h"

#include "TafMmaInterface.h"

#include "TafMmaSndMscc.h"
#include "TafLog.h"

#include "UsimPsInterface.h"

#include "TafMmaComFunc.h"
/* added by wx270776 for OM�ں�, 2015-08-21, begin */
#include "OmApi.h"
/* added by wx270776 for OM�ں�, 2014-08-21, end */


#if (FEATURE_ON == FEATURE_BASTET)
#include "MmaBastetInterface.h"
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_MMA_APPLOCAL_C





/* Modified by wx270776 for OM�ں�, 2015-7-17, begin */
VOS_UINT8                 g_ucMmaOmConnectFlg = VOS_FALSE;                      /* �Ƿ�����PC��������, VOS_TRUE: ������; VOS_FALSE: δ����.
                                                                                   Ĭ��δ���� */
VOS_UINT8                 g_ucMmaOmPcRecurEnableFlg  = VOS_FALSE;               /* ��ǰPC�����Ƿ�ʹ����NAS��PC�ط���Ϣ�ķ���, VOS_TRUE: ʹ��; VOS_FASLE: δʹ��
                                                                                   Ĭ��ʹ��PC�ط� */
/* Modified by wx270776 for OM�ں�, 2015-7-17, end */


VOS_UINT32                g_ucUsimHotOutFlag;
VOS_UINT32                g_ucUsimHotInFlag;



/* USIM���Ȳ�εĿ�ά�ɲ���� */
VOS_UINT32                       g_ulUsimHotOutCount = 0;
VOS_UINT32                       g_ulUsimHotInCount  = 0;



/*APSģ��USIM��س�ʼ������*/
extern TAF_UINT32   At_HexAlpha2AsciiString(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst,TAF_UINT8 *pucSrc,TAF_UINT16 usSrcLen);
extern VOS_VOID     SHPA_ActivateHw(VOS_VOID);
extern VOS_VOID     SHPA_DeactivateHw(VOS_VOID);





/* �������ӿ��ɵ������ṩ*.o�ļ����˴������� */
extern int VerifySL(char* UnlockCode, char* Key);


/*****************************************************************************
   2 ȫ�ֱ�������ͺ�
****************************************************************************/
#define MMA_REPORT_HEAD                 8 /*TAF_MSG_HEADER + QUERY_TYPE + INFO_LEN*/
#define MMA_PARA_LEN_POSITION           4
#define MMA_PH_PIN_TI                   2
#define MN_MMA_MAX_UPLMN_NUM            (100)
#define MMA_PLMN_ID_LEN                 (6)


TAF_MMA_GLOBAL_VALUE_ST                 gstMmaValue;
MMA_UE_FORB_BAND_ST                     gstMmaForbBand;
MMA_TIMER_ST                            g_MmaSimTimer[TAF_SIM_TIMER_NUM];
MMA_TI_TABLE                            gastMmaTiTab[MMA_MAX_TI];
MMA_INTERNAL_TIMER_ST                   gstMmaInternalTimer;


VOS_UINT8                               g_aucMmaImei[TAF_PH_IMEI_LEN-1]={0};
extern STATUS_CONTEXT_STRU              g_StatusContext;
/* ɾ��gstMmaInitialTimer */
VOS_BOOL                                f_bGetRecRange = VOS_FALSE;

TAF_MMA_LOCATION_STATUS_EVENT_INFO_STRU g_stMmsStkLocStaSysInfo;

MMA_TIMER_ST                            g_MmaTimerforPcReplay;

MMA_TIMER_ST                            g_stPhPhResetTimer;

MMA_TIMER_ST                            g_stPhPinOperTimer;


MMA_TIMER_ST                            g_stPowerDownDelayTimer;

MMA_TIMER_ST                            g_stNetScanProtectTimer;
MMA_TIMER_ST                            g_stAbortNetScanProtectTimer;

/* ��¼PIN��ǰ�������  */
TAF_PH_PIN_CNF_STRU                     g_stPhPinCnf;

MMA_DEACT_SIM_WHEN_POWEROFF_ENUM_UINT8  g_ucMmaDeactSimWhenPoweroff;

MMA_CIPHER_INFO_STRU                    g_stMmaCipherInfo = {0};


ENUM_SYSTEM_APP_CONFIG_TYPE_U16         g_usMmaAppConfigSupportType = SYSTEM_APP_BUTT;




MMA_GET_REC_INFO_STRU                   f_stRecInfo;

NAS_MMA_NEW_ADD_GLABAL_VARIABLE_FOR_PC_REPLAY_ST g_MmaNewValue;

#define MMA_PIN_HANDLE_TIME             25000
#define MMA_GET_FILE_TIME               21000
#define MMA_START_INITIAL_TIME          5000
#define MMA_INTERNAL_TIME               1000


#define MMA_PIN_LEN_MAX                 8
#define MMA_PIN_LEN_MIN                 4
#define MMA_TI_USED                     1


#define MMA_WRITE_NVIM_INDEX            0x1
#define MMA_READ_NVIM_INDEX             0x1
#define MMA_DE_ATTACH_NULL              0x0
#define MMA_WCDMA_BAND_TYPE_MAX         0x3
#define MMA_BAND_TYPE_NULL              0x0


#define MMA_RSCP_MAX                    (-60)
#define MMA_ECNO_MAX                    (0)

#define MMA_RSSI_INVALID                (99)

/* ���� */
#define MMA_INVALID_RSCP_SEC_MAX        (2)


 MMA_ME_PERSONALISATION_STATUS_STRU      g_stMmaMePersonalisationStatus;

MMA_MODIFY_PLMN_INFO_STRU               f_stMmaPlmnInfo;
/* ��¼��һ����WAS��ѯ RSCP �� ECNO ����Чֵ */
VOS_INT16                               g_sLastRscp = MMA_RSCP_MIN;
VOS_INT16                               g_sLastEcNo = MMA_ECNO_MIN;



#define PROTOCOL_STACK_VERSION "V300R001C01B050"

VOS_UINT8                               g_ucMnPhRoamStatus = TAF_PH_INFO_NONE_ROMAING;  /* ��¼����״̬(�ϱ���Ӧ��) */



/* �汾���Ի������������Ϊ׼ */
#ifdef EV_PS_VERSION
    #undef PROTOCOL_STACK_VERSION
    #define PROTOCOL_STACK_VERSION EV_PS_VERSION
#endif




TAF_PH_BAND_NAME_STRU gastMmaSyscfgBandStr[] =
{
    {TAF_PH_BAND_GSM_850     ,      "GSM850"   },
    {TAF_PH_BAND_GSM_900     ,      "GSM900"   },
    {TAF_PH_BAND_GSM_DCS_1800,      "GSM1800"  },
    {TAF_PH_BAND_GSM_PCS_1900,      "GSM1900"  },
    {TAF_PH_BAND_WCDMA_VI_800,      "WCDMA800" },
    {TAF_PH_BAND_WCDMA_V_850,       "WCDMA850" },
    {TAF_PH_BAND_WCDMA_VIII_900,    "WCDMA900" },
    {TAF_PH_BAND_WCDMA_XI_1500,     "WCDMA1500"},
    {TAF_PH_BAND_WCDMA_IV_1700,     "AWS"},
    {TAF_PH_BAND_WCDMA_IX_1700,     "WCDMA1700"},
    {TAF_PH_BAND_WCDMA_III_1800,    "WCDMA1800"},
    {TAF_PH_BAND_WCDMA_II_PCS_1900, "WCDMA1900"},
    {TAF_PH_BAND_WCDMA_I_IMT_2100,  "WCDMA2100"},
    {TAF_PH_BAND_WCDMA_VII_2600,    "WCDMA2600"}

};





/*lint -save -e958 */

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
VOS_INT32 MMA_Bcd2Int (VOS_UINT8 ucChar)
{
    return ((ucChar>>4) + ((ucChar&0x0f)*10));
}


VOS_BOOL MN_PH_IsPlmnValid(TAF_PLMN_ID_STRU *pstPlmnId)
{
    VOS_UINT32                          i;

    for (i=0; i<3; i++)
    {
        if ((((pstPlmnId->Mcc >> (i*4)) & 0x0F) > 9)
         || ((((pstPlmnId->Mnc >> (i*4)) & 0x0F) > 9) && (i != 2 ))
         || ((((pstPlmnId->Mnc >> (i*4)) & 0x0F) > 9) && (((pstPlmnId->Mnc >> (i*4)) & 0x0F) != 0x0F)))
        {
            /* PLMN ID��Ч */
            return VOS_FALSE;
        }
    }
    return VOS_TRUE;
}
VOS_UINT16 MN_PH_GetUpdateFileForPrefPlmn(
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPLMNType
)
{
    VOS_UINT16                          usUpdateFile;
    /* Added by h00313353 for iteration 9, 2015-2-5, begin */
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;

    enSimType       = TAF_SDC_GetSimType();
    usUpdateFile    = 0;
    /* Added by h00313353 for iteration 9, 2015-2-5, end */

    if (MN_PH_PREF_PLMN_UPLMN == enPrefPLMNType)
    {
        if (VOS_TRUE == MN_PH_IsUsingPlmnSel())
        {
            usUpdateFile = USIMM_GSM_EFPLMNSEL_ID;
        }
        else
        {
            /* Added by h00313353 for iteration 9, 2015-2-4, begin */
            if (TAF_SDC_SIM_TYPE_USIM == enSimType)
            {/* 3G USIM */
                usUpdateFile = USIMM_USIM_EFPLMNWACT_ID;
            }
            else if (TAF_SDC_SIM_TYPE_SIM == enSimType)
            {/* 2G SIM */
                usUpdateFile = USIMM_GSM_EFPLMNWACT_ID;
            }
            else
            {
                usUpdateFile = USIMM_DEF_FILEID_BUTT;
            }
            /* Added by h00313353 for iteration 9, 2015-2-4, end */
        }
    }
    else if (MN_PH_PREF_PLMN_OPLMN == enPrefPLMNType)
    {
        /* Added by h00313353 for iteration 9, 2015-2-4, begin */
        if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {/* 3G USIM */
            usUpdateFile = USIMM_USIM_EFOPLMNWACT_ID;
        }
        else if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {/* 2G SIM */
            usUpdateFile = USIMM_GSM_EFOPLMNWACT_ID;
        }
        else
        {
            usUpdateFile = USIMM_DEF_FILEID_BUTT;
        }
        /* Added by h00313353 for iteration 9, 2015-2-4, end */
    }
    else
    {
        /* Added by h00313353 for iteration 9, 2015-2-4, begin */
        if (TAF_SDC_SIM_TYPE_USIM == enSimType)
        {/* 3G USIM */
            usUpdateFile = USIMM_USIM_EFHPLMNwACT_ID;
        }
        else if (TAF_SDC_SIM_TYPE_SIM == enSimType)
        {/* 2G SIM */
            usUpdateFile = USIMM_GSM_EFHPLMNACT_ID;
        }
        else
        {
            usUpdateFile = USIMM_DEF_FILEID_BUTT;
        }
        /* Added by h00313353 for iteration 9, 2015-2-4, end */
    }
    return usUpdateFile;
}



VOS_UINT32 MMA_DbProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usMsgType;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    MN_APP_REQ_MSG_STRU                *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    /*��Ϣ����*/
    usMsgType = pstRcvMsg->usMsgName;

    /*ClientId*/
    usClientId = pstRcvMsg->clientId;
    ucOpId     = pstRcvMsg->opId;

    if (usClientId >= TAF_MAX_CLIENT_OF_ONE_PROC)
    {
        TAF_LOG(WUEPS_PID_MMA, 0, PS_LOG_LEVEL_ERROR,
            "MMA_TafMsgProc:ERROR:Client ID is out of range!");

        return VOS_TRUE;
    }

    switch((TAF_MSG_TYPE)usMsgType)
    {


        case TAF_MSG_MMA_USIM_INFO:
            MMA_QryUsimInfo(usClientId,ucOpId, (TAF_PH_QRY_USIM_INFO_STRU *)pstRcvMsg->aucContent);
            break;
        case TAF_MSG_MMA_CPNN_INFO:
            MMA_CPnnQuery(usClientId, ucOpId, (TAF_PH_ICC_TYPE*)pstRcvMsg->aucContent);
            break;


        default:
            Taf_ParaSetResult(usClientId,ucOpId, TAF_ERR_CMD_TYPE_ERROR, (TAF_PARA_TYPE)usMsgType, VOS_NULL_PTR);
            MMA_ERRORLOG1("MMA_DbProc:ERROR:ERROR DB PROC INDEX:", usMsgType);
    }

    return VOS_TRUE;
}




VOS_VOID MN_MMA_GetOnlyGURatOrder(
    TAF_MMA_RAT_ORDER_STRU             *pstAllRatOrder,
    TAF_MMA_RAT_ORDER_STRU             *pstGURatOrder
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucIndex;

    ucIndex         = 0;

    /* ��ȡGUģ��Ϣ */
    for (i = 0; i < pstAllRatOrder->ucRatOrderNum; i++)
    {
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
        if ( (TAF_MMA_RAT_WCDMA == pstAllRatOrder->aenRatOrder[i])
          || (TAF_MMA_RAT_GSM   == pstAllRatOrder->aenRatOrder[i]) )
        {
            pstGURatOrder->aenRatOrder[ucIndex] = pstAllRatOrder->aenRatOrder[i];
            ucIndex++;
        }
    }

    pstGURatOrder->ucRatOrderNum          = ucIndex;
    pstGURatOrder->aenRatOrder[ucIndex]   = TAF_MMA_RAT_BUTT;
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    return;
}
VOS_VOID MN_MMA_GetCpamGURatPrio(
   MN_MMA_CPAM_RAT_PRIO_ENUM_UINT8     *pucPlmnPrio,
   TAF_MMA_RAT_ORDER_STRU              *pstAllRatOrder
)
{
    TAF_MMA_RAT_ORDER_STRU              stGURatOrder;

    /* �ӽ�����Ϣ��ȡ��GUģ����Ϣ */
    MN_MMA_GetOnlyGURatOrder(pstAllRatOrder, &stGURatOrder);

    /* û��GUģ��Ϣʱ��Ĭ��ΪW���� */
    if ( 0 == stGURatOrder.ucRatOrderNum )
    {
        *pucPlmnPrio = MN_MMA_CPAM_RAT_PRIO_WCDMA;
        return;
    }

    /* ����ǰGUģ��Ϣת��ΪCPAM�Ľ������ȼ���Ϣ��ʽ */
    switch ( stGURatOrder.aenRatOrder[0] )
    {
        /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
        case TAF_MMA_RAT_WCDMA:
            *pucPlmnPrio = MN_MMA_CPAM_RAT_PRIO_WCDMA;
            break;

        case TAF_MMA_RAT_GSM :
        /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
            *pucPlmnPrio = MN_MMA_CPAM_RAT_PRIO_GSM;
            break;

        default:
            MN_ERR_LOG("MN_MMA_GetGUPlmnPrio,ERROR:RAT WRONG!");
            *pucPlmnPrio = MN_MMA_CPAM_RAT_PRIO_WCDMA;
            break;
    }

    return;
}
VOS_VOID MN_MMA_GetCpamGUAccessRat(
   MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8     *penAccessMode,
   TAF_MMA_RAT_ORDER_STRU              *pstAllRatOrder
)
{
    TAF_MMA_RAT_ORDER_STRU              stGURatOrder;

    /* �ӽ�����Ϣ��ȡ��GUģ����Ϣ */
    MN_MMA_GetOnlyGURatOrder(pstAllRatOrder, &stGURatOrder);

    if ( 0 == stGURatOrder.ucRatOrderNum)
    {
        /* û��GUģ��Ĭ�Ͻ��뼼��Ϊ˫ģ��֧�� */
        *penAccessMode = MN_MMA_CPAM_RAT_TYPE_BUTT;
    }
    else if (VOS_TRUE == MN_MMA_IsGOnlyMode(&stGURatOrder))
    {
        *penAccessMode = MN_MMA_CPAM_RAT_TYPE_GSM;;
    }
    else if (VOS_TRUE == MN_MMA_IsWOnlyMode(&stGURatOrder))
    {
        *penAccessMode = MN_MMA_CPAM_RAT_TYPE_WCDMA;
    }
    else
    {
        *penAccessMode = MN_MMA_CPAM_RAT_TYPE_WCDMA_GSM;
    }

    return;
}




VOS_VOID MMA_GetCpolPara(
    TAF_PH_SET_PREFPLMN_STRU           *pstPrefPlmn,
    VOS_UINT32                         *pulIndex,
    TAF_PLMN_ID_STRU                   *pstPlmnId,
    AT_COPS_FORMAT_TYPE                *pTmpFormat,
    VOS_BOOL                           *pbOperExist,
    VOS_BOOL                           *pbFormat
)
{
    /* ����<index> */
    if ( 0 != pstPrefPlmn->usIndexLen )
    {
        *pulIndex = pstPrefPlmn->usIndex;
    }

    /* ����<format> */
    if ( 0 != pstPrefPlmn->usFormatLen )
    {
        *pTmpFormat = (AT_COPS_FORMAT_TYPE)pstPrefPlmn->usFormat;
    }
    else
    {
        *pTmpFormat = AT_COPS_LONG_ALPH_TYPE;
        *pbFormat   = TAF_FALSE;
    }

    PS_MEM_SET(pstPlmnId,(VOS_CHAR)0xFF,sizeof(TAF_PLMN_ID_STRU));
    /* ����<oper> */
    if ( 0 != pstPrefPlmn->usOperNameLen )
    {
        /* ת���û�����PLMN�ַ�ΪPLMN ID */
        if( VOS_TRUE != MMA_FormatPlmnStr2PlmnId(pstPlmnId,
                                                 pstPrefPlmn->usFormat,
                                                 pstPrefPlmn->usOperNameLen,
                                                 pstPrefPlmn->ucOperName) )
        {
            *pbOperExist = TAF_FALSE;
        }
    }
    else
    {
        *pbOperExist = TAF_FALSE;
    }

    return;
}


VOS_UINT16 MMA_SetCpolOperType(
    TAF_PH_SET_PREFPLMN_STRU           *pstPrefPlmnParam,
    TAF_PH_PREF_PLMN_OPERATE_STRU      *pstPrefPlmnOpt)
{
    VOS_UINT32                          ulIndex;
    TAF_PLMN_ID_STRU                    stPlmnId;
    AT_COPS_FORMAT_TYPE                 TmpFormat;
    VOS_BOOL                            bOperExist;
    VOS_BOOL                            bFormat;

    ulIndex      = MMA_INVALID_INDEX;
    TmpFormat    = AT_COPS_LONG_ALPH_TYPE;
    bOperExist   = TAF_TRUE;
    bFormat      = TAF_TRUE;

    MMA_GetCpolPara(pstPrefPlmnParam,&ulIndex,&stPlmnId,&TmpFormat,&bOperExist,&bFormat);

    /* <index>����,��<oper>�����ڣ���Ĭ��Ϊɾ��������¼ */
    if ((MMA_INVALID_INDEX != ulIndex) && (TAF_FALSE == bOperExist))
    {
        pstPrefPlmnOpt->enPrefPlmnOperType = MN_PH_PrefPLMN_DEL_ONE;
        pstPrefPlmnOpt->ulIndex            = ulIndex;
    }
    else if ((MMA_INVALID_INDEX == ulIndex)
          && (TAF_TRUE == bOperExist)
          && (TAF_TRUE == bFormat) )
    {
        /* <oper>����,��<index>�����ڣ���Ĭ��Ϊ����һ����¼ */
        pstPrefPlmnOpt->enPrefPlmnOperType = MN_PH_PrefPLMN_ADD_ONE;
        PS_MEM_CPY(&pstPrefPlmnOpt->stPlmn,&stPlmnId,sizeof(stPlmnId));
    }
    else if ((MMA_INVALID_INDEX != ulIndex)
          && (TAF_TRUE == bOperExist)
          && (TAF_TRUE == bFormat) )
    {
        /* <oper>����,<index>���ڣ�����Ϊ�޸�һ����¼ */
        pstPrefPlmnOpt->enPrefPlmnOperType = MN_PH_PrefPLMN_MODIFY_ONE;
        pstPrefPlmnOpt->ulIndex            = ulIndex;
        PS_MEM_CPY(&pstPrefPlmnOpt->stPlmn,&stPlmnId,sizeof(stPlmnId));
    }
    else
    {
        return TAF_ERR_PARA_ERROR;
    }

    return VOS_TRUE;
}
VOS_UINT16 MMA_CheckAccessExist(
    TAF_PH_SET_PREFPLMN_STRU             *pstPrefPlmnParam,
    TAF_MMC_USIM_RAT                     *pusRat
)
{
    VOS_BOOL                            bPlmnSelFlg;

#if(FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulPlatformSuppLteFlg;
#endif
    VOS_UINT32                          ulAtParaRatValid;

    *pusRat     = TAF_MMC_USIM_NO_RAT;
    bPlmnSelFlg = VOS_FALSE;

    if (MN_PH_PREF_PLMN_UPLMN == pstPrefPlmnParam->enPrefPlmnType)
    {
        bPlmnSelFlg = MN_PH_IsUsingPlmnSel();
    }

    if ((3 == pstPrefPlmnParam->ucAtParaIndex)
     && (VOS_TRUE == bPlmnSelFlg))
    {
        /* ��ǰUplmnΪPlmnSelʱ������Ҫ������뼼��,�ñ�ʶ��MMA�д���*/
        *pusRat = TAF_MMC_USIM_UTRN_GSM_RAT;
        return VOS_TRUE;
    }

#if(FEATURE_ON == FEATURE_LTE)
    ulPlatformSuppLteFlg = TAF_SDC_IsPlatformSupportLte();

    /* ����������Ϊ7ʱ��LTE���ʼ����Ϊ��Ч */
    if (7 == pstPrefPlmnParam->ucAtParaIndex)
    {
        ulAtParaRatValid = VOS_TRUE;
    }
    /* ����������Ϊ6ʱ��LTE���ƽ̨��֧��LTEʱ����Ч */
    else if ((6 == pstPrefPlmnParam->ucAtParaIndex)
          && (VOS_FALSE == ulPlatformSuppLteFlg))
    {
        ulAtParaRatValid = VOS_TRUE;
    }
    else
    {
        ulAtParaRatValid = VOS_FALSE;
    }
#else
    /* ��LTE��رգ���������Ϊ6����Ϊ��Ч */
    if (6 == pstPrefPlmnParam->ucAtParaIndex)
    {
        ulAtParaRatValid = VOS_TRUE;
    }
    else
    {
        ulAtParaRatValid = VOS_FALSE;
    }
#endif

    if (VOS_FALSE == ulAtParaRatValid)
    {
        return VOS_FALSE;
    }

    if (1 == pstPrefPlmnParam->usGsmRat)
    {
        *pusRat = TAF_MMC_USIM_GSM_RAT;
    }

    if (1 == pstPrefPlmnParam->usGsmCompactRat)
    {
        *pusRat |= TAF_MMC_USIM_GSM_COMPACT_RAT;
    }

    if (1 == pstPrefPlmnParam->usUtrn)
    {
        *pusRat |= TAF_MMC_USIM_UTRN_RAT;
    }

#if(FEATURE_ON == FEATURE_LTE)
    if ((VOS_TRUE == pstPrefPlmnParam->usEutrn)
     && (VOS_TRUE == ulPlatformSuppLteFlg))
    {
        *pusRat |= TAF_MMC_USIM_E_UTRN_RAT;
    }
#endif

    return VOS_TRUE;
}


VOS_UINT16 MMA_CheckCpolPara(
    TAF_PH_SET_PREFPLMN_STRU           *pstPrefPlmnParam,
    TAF_PH_PREF_PLMN_OPERATE_STRU      *pstPrefPlmnOpt)
{
    VOS_UINT16                          usRet;

    usRet = MMA_SetCpolOperType(pstPrefPlmnParam,pstPrefPlmnOpt);

    if (VOS_TRUE != usRet)
    {
        return usRet;
    }

    if ((MN_PH_PrefPLMN_ADD_ONE == pstPrefPlmnOpt->enPrefPlmnOperType)
     || (MN_PH_PrefPLMN_MODIFY_ONE == pstPrefPlmnOpt->enPrefPlmnOperType))
    {
        /* ���ӻ��޸�ʱ,���û����ý��뼼���޸�ΪUSIM�ĸ�ʽ */
        usRet = MMA_CheckAccessExist(pstPrefPlmnParam,&pstPrefPlmnOpt->usRat);
        if (VOS_TRUE != usRet)
        {
            return usRet;
        }
    }
    else
    {
        if ((0 != pstPrefPlmnParam->usGsmRatLen)
         || (0 != pstPrefPlmnParam->usGsmCompactRatLen)
#if(FEATURE_ON == FEATURE_LTE)
         || (0 != pstPrefPlmnParam->usEutrnLen)
#endif
         || (0 != pstPrefPlmnParam->usUtrnLen))
        {
            return TAF_ERR_PARA_ERROR;
        }
    }

    return VOS_TRUE;
}

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-3-26, begin */

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-3-26, end */

VOS_VOID    Mma_VerifyPhonePersSuccEvent(SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enVerifySimlockRsltOrig)
{
    TAF_PHONE_EVENT_INFO_STRU *         pstPhoneEvent;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("Mma_VerifyPhonePersSuccEvent:ERROR:ALLOC MEMORY FAIL.");
        return;
    }
    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    /*����TAF�¼��ϱ�����,�ϱ�PIN�¼�*/
    pstPhoneEvent->OP_Pin             = VOS_TRUE;
    pstPhoneEvent->PhoneEvent         = TAF_PH_EVT_OP_PIN_CNF;

    pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_OK;

    switch (enVerifySimlockRsltOrig)
    {
        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN:
            pstPhoneEvent->PinCnf.PinType = TAF_PHNET_PIN;
            pstPhoneEvent->PinCnf.CmdType = TAF_PIN_VERIFY;
           break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PUK:
            pstPhoneEvent->PinCnf.PinType = TAF_PHNET_PUK;
            pstPhoneEvent->PinCnf.CmdType = TAF_PIN_UNBLOCK;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN:
            pstPhoneEvent->PinCnf.PinType = TAF_PHNETSUB_PIN;
            pstPhoneEvent->PinCnf.CmdType = TAF_PIN_VERIFY;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PUK:
            pstPhoneEvent->PinCnf.PinType = TAF_PHNETSUB_PUK;
            pstPhoneEvent->PinCnf.CmdType = TAF_PIN_UNBLOCK;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN:
            pstPhoneEvent->PinCnf.PinType = TAF_PHSP_PIN;
            pstPhoneEvent->PinCnf.CmdType = TAF_PIN_VERIFY;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PUK:
            pstPhoneEvent->PinCnf.PinType = TAF_PHSP_PUK;
            pstPhoneEvent->PinCnf.CmdType = TAF_PIN_UNBLOCK;
            break;
        default:
            /* �쳣ȡֵ */
            pstPhoneEvent->PinCnf.PinType = TAF_SIM_NON;
            pstPhoneEvent->PinCnf.CmdType = TAF_PIN_VERIFY;
            break;
    }

    Taf_PhoneEvent(pstPhoneEvent);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

}



VOS_VOID MMA_SetCPinForApModemWhenLocked(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    MN_PH_SET_CPIN_REQ_STRU            *pstSetCPinReq
)
{
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enVerifySimlockRslt;
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enVerifySimlockRsltOrig;
    SC_ERROR_CODE_ENUM_UINT32           enScResult;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucTi;
    MODEM_ID_ENUM_UINT16                enModemId;


    enVerifySimlockRslt     = SC_VERIFY_SIMLOCK_RESULT_BUTT;
    enVerifySimlockRsltOrig = SC_VERIFY_SIMLOCK_RESULT_BUTT;

    /* ��ASCII�ַ�������("0"~"9"��ASCII�ַ�)ת��Ϊ��������(0~9������) */
    for (ulLoop = 0; ulLoop < pstSetCPinReq->usPara0Len; ulLoop++)
    {
        if( ('0' <= *(pstSetCPinReq->aucPara0 + ulLoop) )
         && ('9' >= *(pstSetCPinReq->aucPara0 + ulLoop) ))
        {
            *(pstSetCPinReq->aucPara0 + ulLoop) -= '0';
        }
        else
        {
            MMA_HandleEventError(usClientId,
                                 ucOpId,
                                 TAF_ERR_PARA_ERROR,
                                 TAF_PH_EVT_OP_PIN_CNF );
            return;
        }
    }

    /* �Ȼ�ȡ������ǰ������״̬���û��������ؽ���/UNBLOCK �ɹ��¼�ʱ����дPinTypeʹ�� */
    enModemId  = VOS_GetModemIDFromPid(WUEPS_PID_MMA);
    enScResult = SC_PERS_VerifySimLock(&enVerifySimlockRsltOrig, enModemId);

    if (SC_ERROR_CODE_NO_ERROR != enScResult)
    {
        MMA_HandleEventError(usClientId,
                             ucOpId,
                             TAF_ERR_UNSPECIFIED_ERROR,
                             TAF_PH_EVT_OP_PIN_CNF );
        return;
    }

    /* ����SC�ӿڽ��н�����UNBLOCK */
    enScResult = SC_PERS_UnLock(pstSetCPinReq->aucPara0, (VOS_UINT8)pstSetCPinReq->usPara0Len, &enVerifySimlockRslt, enModemId);


    if (SC_ERROR_CODE_NO_ERROR != enScResult)
    {
        if ( SC_ERROR_CODE_UNLOCK_KEY_INCORRECT == enScResult)
        {
            MMA_HandleEventError(usClientId,
                                 ucOpId,
                                 TAF_ERR_SIM_INCORRECT_PASSWORD,
                                 TAF_PH_EVT_OP_PIN_CNF );
        }
        else
        {
            MMA_HandleEventError(usClientId,
                                 ucOpId,
                                 TAF_ERR_UNSPECIFIED_ERROR,
                                 TAF_PH_EVT_OP_PIN_CNF );
        }
        return;
    }

    /*�����PIN������ȫ�ֱ��������غ�����ѯ���洢CLIENTID*/
    /*��¼��ǰclientId��OpId*/
    if (MMA_SUCCESS != MMA_TiAlloc(TAF_MMA, usClientId, ucOpId, TAF_PH_EVT_OP_PIN_CNF, &ucTi))
    {   /*Ti����ʧ��*/
        MMA_WARNINGLOG("MMA_SetCPinForApModemWhenLocked():WARNING:ALLOC TI FAILED!");
        /*������*/
        MMA_HandleEventError(usClientId, ucOpId, TAF_ERR_TI_ALLOC_FAIL, TAF_PH_EVT_OP_PIN_CNF);
        return;
    }

    /* ��AT���ͽ�����UNBLOCK�ɹ��¼� */
    Mma_VerifyPhonePersSuccEvent(enVerifySimlockRsltOrig);

    /* �����������ready̬�����쿨״̬�仯�ϱ�����������״̬����Ϊ�Ѿ����� */
    if (SC_VERIFY_SIMLOCK_RESULT_READY == enVerifySimlockRslt)
    {
        /* �������󴥷���������״̬�仯ָʾ��Ϣ */
        TAF_MMA_SndSimlocakStatusChangeInd();

        g_stMmaMePersonalisationStatus.SimLockStatus = MMA_SIM_LOCK_IS_VERIFY;
    }

    return;
}



VOS_UINT32 MMA_SetCPin(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PH_PIN_DATA_STRU                stPinData;
    TAF_ME_PERSONALISATION_DATA_STRU    stMePersonalisationData;
    MN_PH_SET_CPIN_REQ_STRU            *pstSetCPinReq;
    VOS_UINT32                          i;
    MN_APP_REQ_MSG_STRU                *pRcvMsg;
    VOS_UINT16                          ClientId;
    VOS_UINT8                           OpId;

    pRcvMsg         = (MN_APP_REQ_MSG_STRU*)pstMsg;
    ClientId        = pRcvMsg->clientId;
    OpId            = pRcvMsg->opId;



    PS_MEM_SET(&stPinData, (VOS_CHAR)0xFF, sizeof(stPinData));

    pstSetCPinReq = (MN_PH_SET_CPIN_REQ_STRU*)pRcvMsg->aucContent;

    if (TAF_PH_ME_SIM_LOCK == MMA_GetMeLockStatus())
    {
        /* ���ϲ�Ӧ��ΪAP-Modem������AP-Modem�Ĵ����֧��������MBB�Ĵ����֧ */
        if (SYSTEM_APP_ANDROID == g_usMmaAppConfigSupportType)
        {
            MMA_SetCPinForApModemWhenLocked(ClientId, OpId, pstSetCPinReq);
        }
        else
        {
            /* ��ʼ�� */
            PS_MEM_SET(&stMePersonalisationData,0x00,sizeof(stMePersonalisationData));

            /* ����<pin> */
            if (0 != pstSetCPinReq->usPara0Len)
            {
                PS_MEM_CPY((VOS_VOID*)stMePersonalisationData.aucOldPwd,
                           (VOS_VOID*)pstSetCPinReq->aucPara0,
                           pstSetCPinReq->usPara0Len);
            }

            /* ����<newpin> */
            if (0 != pstSetCPinReq->usPara1Len)
            {
                PS_MEM_CPY((VOS_VOID*)stMePersonalisationData.aucNewPwd,
                           (VOS_VOID*)pstSetCPinReq->aucPara1,
                           pstSetCPinReq->usPara1Len);
            }

            /* ����CmdType */
            stMePersonalisationData.MePersonalType  = TAF_SIM_PERSONALISATION;
            stMePersonalisationData.CmdType         = TAF_ME_PERSONALISATION_VERIFY;

            /* ִ��������� */
            MMA_MePersonalisationHandle(ClientId, OpId,stMePersonalisationData);
        }
    }
    else
    {
        /* ��ʼ�� */
        SI_PB_MemSet(sizeof(stPinData), 0xFF,(VOS_UINT8 *)&stPinData);

        /* ����<pin> */
        if(0 != pstSetCPinReq->usPara0Len)
        {
            if (TAF_PH_PINCODELENMAX < pstSetCPinReq->usPara0Len)
            {
                MMA_HandleEventError(ClientId,
                                     OpId,
                                     TAF_ERR_PARA_ERROR,
                                     TAF_PH_EVT_OP_PIN_CNF );

                return VOS_TRUE;
            }

            for(i=0; i<pstSetCPinReq->usPara0Len; i++)
            {
                if((pstSetCPinReq->aucPara0[i] > '9' )||(pstSetCPinReq->aucPara0[i] < '0'))
                {
                    MMA_HandleEventError(ClientId,
                                         OpId,
                                         TAF_ERR_PARA_ERROR,
                                         TAF_PH_EVT_OP_PIN_CNF );

                    return VOS_TRUE;
                }
            }

            PS_MEM_CPY((VOS_VOID*)stPinData.aucOldPin,(VOS_VOID*)pstSetCPinReq->aucPara0,pstSetCPinReq->usPara0Len);
        }

        /* ����<newpin> */
        if (0 != pstSetCPinReq->usPara1Len)
        {
            for (i=0; i<pstSetCPinReq->usPara1Len; i++)
            {
                if ((pstSetCPinReq->aucPara1[i] > '9' )||(pstSetCPinReq->aucPara1[i] < '0'))
                {
                    MMA_HandleEventError(ClientId,
                                         OpId,
                                         TAF_ERR_PARA_ERROR,
                                         TAF_PH_EVT_OP_PIN_CNF );

                    return VOS_TRUE;
                }
            }

            PS_MEM_CPY((VOS_VOID*)stPinData.aucNewPin,(VOS_VOID*)pstSetCPinReq->aucPara1,pstSetCPinReq->usPara1Len);
        }

        /* ����CmdType */
        if (0 == pstSetCPinReq->usPara1Len)
        {
            stPinData.PinType = TAF_SIM_PIN;
            stPinData.CmdType = TAF_PIN_VERIFY;
        }
        else
        {
            stPinData.PinType = TAF_SIM_PUK;
            stPinData.CmdType = TAF_PIN_UNBLOCK;
        }

        /* ִ��������� */
        MMA_PinHandle(ClientId, OpId,stPinData);
    }

    return VOS_TRUE;

}



VOS_UINT32 MMA_DigitString2Hex(TAF_UINT8 *nptr,TAF_UINT16 usLen,TAF_UINT32 *pRtn)
{
    TAF_UINT32 c     = 0;         /* current Char */
    TAF_UINT32 total = 0;         /* current total */
    TAF_UINT8 Length = 0;         /* current Length */
    /*lint -e961*/
    c = (TAF_UINT32)*nptr++;

    while(Length++ < usLen)
    {
        if( (c  >= '0') && (c  <= '9') )
        {
            c  = c  - '0';
        }
        else
        {
            return VOS_FALSE;
        }

        if(total > 0x0FFFFFFF)              /* ������ת */
        {
            return VOS_FALSE;
        }
        else
        {
            total = (total << 4) + c;              /* accumulate digit */
            c = (TAF_UINT32)(TAF_UINT8)*nptr++;    /* get next Char */
        }
    }
    /*lint +e961*/
    *pRtn = total;   /* return result, negated if necessary */
    return VOS_TRUE;
}


VOS_UINT32 MMA_FormatPlmnStr2PlmnId(
    TAF_PLMN_ID_STRU                   *pPlmn,
    VOS_UINT32                          usFormat,
    VOS_UINT16                          usOprNameLen,
    VOS_CHAR                           *pucOprName
)
{
    TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU AtOperName;

    PS_MEM_SET(&AtOperName,0x00,sizeof(AtOperName));
    /* ����ucType����ȡPLMN */
    switch(usFormat)
    {
    case AT_COPS_LONG_ALPH_TYPE:    /* long format alphanumeric */
        (VOS_VOID)VOS_StrCpy((VOS_CHAR*)AtOperName.OperName.aucOperatorNameLong,
                   (VOS_CHAR*)pucOprName);
        AtOperName.ListOp = TAF_PH_OPER_NAME_LONGNAME2OTERS;

        if(MMA_SUCCESS == Taf_PhoneGetOperNameInfo(&AtOperName))
        {
            pPlmn->Mnc = AtOperName.OperName.PlmnId.Mnc;

            pPlmn->Mcc = AtOperName.OperName.PlmnId.Mcc;
        }
        else
        {
            return VOS_FALSE;
        }
        break;

    case AT_COPS_SHORT_ALPH_TYPE:   /* short format alphanumeric */
        (VOS_VOID)VOS_StrCpy((VOS_CHAR*)AtOperName.OperName.aucOperatorNameShort,
                   (VOS_CHAR*)pucOprName);
        AtOperName.ListOp = TAF_PH_OPER_NAME_SHORTNAME2OTHERS;

        if(MMA_SUCCESS == Taf_PhoneGetOperNameInfo(&AtOperName))
        {
            pPlmn->Mnc = AtOperName.OperName.PlmnId.Mnc;

            pPlmn->Mcc = AtOperName.OperName.PlmnId.Mcc;
        }
        else
        {
            return VOS_FALSE;
        }
        break;

    default:  /* numeric */
        if(VOS_FALSE == MMA_DigitString2Hex((TAF_UINT8*)pucOprName,3,&pPlmn->Mcc))
        {
            return VOS_FALSE;
        }
        /* Mnc */
        if(VOS_FALSE == MMA_DigitString2Hex((TAF_UINT8*)&pucOprName[3],usOprNameLen-3,&pPlmn->Mnc))
        {
            return VOS_FALSE;
        }

        pPlmn->Mcc |= 0xFFFFF000;
        pPlmn->Mnc |= (0xFFFFFFFF << ((usOprNameLen-3)*4));

        break;
    }
    return VOS_TRUE;
}
VOS_VOID TAF_MMA_QryEonsUcs2(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                          stMmPlmnInfo;
    VOS_UINT8                                               ucIndex;
    TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU               *pstEnhancedOperNameInfo = VOS_NULL_PTR;
    TAF_SDC_PLMN_ID_STRU                                    stPlmnId;
    TAF_SDC_PLMN_ID_STRU                                   *pstAppServicePlmnId = VOS_NULL_PTR;
    TAF_MMA_EONS_UCS2_PLMN_NAME_STRU                        stEonsUcs2PlmnName;

    pstEnhancedOperNameInfo = TAF_SDC_GetEnhancedOperatorNameInfo();
    pstAppServicePlmnId     = TAF_SDC_GetAppServicePlmnId();
    PS_MEM_SET(&stPlmnId, 0, sizeof(stPlmnId));

    /*��ȡ��ǰPLMN����������Ӫ����Ϣ*/
    PS_MEM_SET(&stMmPlmnInfo, 0, sizeof(stMmPlmnInfo));
    PS_MEM_SET(&stEonsUcs2PlmnName, 0, sizeof(stEonsUcs2PlmnName));

    if (VOS_FALSE == TAF_IsNormalSrvStatus())
    {
        stEonsUcs2PlmnName.ucLongNameLen  = stMmPlmnInfo.ucLongNameLen;
        stEonsUcs2PlmnName.ucShortNameLen = stMmPlmnInfo.ucShortNameLen;
        PS_MEM_CPY(stEonsUcs2PlmnName.aucLongName, stMmPlmnInfo.aucLongName, sizeof(stEonsUcs2PlmnName.aucLongName));
        PS_MEM_CPY(stEonsUcs2PlmnName.aucShortName, stMmPlmnInfo.aucShortName, sizeof(stEonsUcs2PlmnName.aucShortName));
        TAF_MMA_ReportEonsUcs2Rsp(TAF_ERR_NO_ERROR, &stEonsUcs2PlmnName);
        return;
    }

    stPlmnId.ulMcc = pstAppServicePlmnId->ulMcc;
    stPlmnId.ulMnc = pstAppServicePlmnId->ulMnc;

    for (ucIndex = 0; ucIndex < pstEnhancedOperNameInfo->stOperNameTypePrio.ucOperNamePrioNum; ucIndex++)
    {
        /* ��PNN�л�ȡ��Ӫ������*/
        if (TAF_SDC_OPER_NAME_TYPE_PNN == pstEnhancedOperNameInfo->stOperNameTypePrio.aucOperNameTypePrio[ucIndex])
        {
            /* ��PNN�л�ȡ��Ӫ�����Ƴɹ�����ֱ�ӷ���*/
            if (VOS_TRUE == TAF_MMA_GetPnnNetWorkName(&stPlmnId, &stMmPlmnInfo, TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2))
            {
                stEonsUcs2PlmnName.ucLongNameLen  = stMmPlmnInfo.ucLongNameLen;
                stEonsUcs2PlmnName.ucShortNameLen = stMmPlmnInfo.ucShortNameLen;
                PS_MEM_CPY(stEonsUcs2PlmnName.aucLongName, stMmPlmnInfo.aucLongName, sizeof(stEonsUcs2PlmnName.aucLongName));
                PS_MEM_CPY(stEonsUcs2PlmnName.aucShortName, stMmPlmnInfo.aucShortName, sizeof(stEonsUcs2PlmnName.aucShortName));
                TAF_MMA_ReportEonsUcs2Rsp(TAF_ERR_NO_ERROR, &stEonsUcs2PlmnName);
                return;
            }
        }

        /* ��CPHS�л�ȡ��Ӫ������,CPHS������UCS2����*/
        if (TAF_SDC_OPER_NAME_TYPE_CPHS == pstEnhancedOperNameInfo->stOperNameTypePrio.aucOperNameTypePrio[ucIndex])
        {
            continue;
        }

        /* ��MM INFO�л�ȡ��Ӫ������*/
        if (TAF_SDC_OPER_NAME_TYPE_MMINFO == pstEnhancedOperNameInfo->stOperNameTypePrio.aucOperNameTypePrio[ucIndex])
        {
            /* ��MM INFO�л�ȡ��Ӫ�����Ƴɹ�����ֱ�ӷ���*/
            if (VOS_TRUE == TAF_MMA_GetMmInfoNetWorkName(&stPlmnId, &stMmPlmnInfo, TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2))
            {
                stEonsUcs2PlmnName.ucLongNameLen  = stMmPlmnInfo.ucLongNameLen;
                stEonsUcs2PlmnName.ucShortNameLen = stMmPlmnInfo.ucShortNameLen;
                PS_MEM_CPY(stEonsUcs2PlmnName.aucLongName, stMmPlmnInfo.aucLongName, sizeof(stEonsUcs2PlmnName.aucLongName));
                PS_MEM_CPY(stEonsUcs2PlmnName.aucShortName, stMmPlmnInfo.aucShortName, sizeof(stEonsUcs2PlmnName.aucShortName));
                TAF_MMA_ReportEonsUcs2Rsp(TAF_ERR_NO_ERROR, &stEonsUcs2PlmnName);
                return;
            }
        }

        /* ��SPN�л�ȡ��Ӫ������*/
        if (TAF_SDC_OPER_NAME_TYPE_SPN == pstEnhancedOperNameInfo->stOperNameTypePrio.aucOperNameTypePrio[ucIndex])
        {
            /* ��SPN�л�ȡ��Ӫ�����Ƴɹ�����ֱ�ӷ���*/
            if (VOS_TRUE == TAF_MMA_GetSpnNetWorkName(&stPlmnId, &stMmPlmnInfo, TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2))
            {
                stEonsUcs2PlmnName.ucLongNameLen  = stMmPlmnInfo.ucLongNameLen;
                stEonsUcs2PlmnName.ucShortNameLen = stMmPlmnInfo.ucShortNameLen;
                PS_MEM_CPY(stEonsUcs2PlmnName.aucLongName, stMmPlmnInfo.aucLongName, sizeof(stEonsUcs2PlmnName.aucLongName));
                PS_MEM_CPY(stEonsUcs2PlmnName.aucShortName, stMmPlmnInfo.aucShortName, sizeof(stEonsUcs2PlmnName.aucShortName));
                TAF_MMA_ReportEonsUcs2Rsp(TAF_ERR_NO_ERROR, &stEonsUcs2PlmnName);

                return;
            }
        }
    }


    /*ʹ�������ϱ����������ݴ���AT*/
    stEonsUcs2PlmnName.ucLongNameLen  = stMmPlmnInfo.ucLongNameLen;
    stEonsUcs2PlmnName.ucShortNameLen = stMmPlmnInfo.ucShortNameLen;
    PS_MEM_CPY(stEonsUcs2PlmnName.aucLongName, stMmPlmnInfo.aucLongName, sizeof(stEonsUcs2PlmnName.aucLongName));
    PS_MEM_CPY(stEonsUcs2PlmnName.aucShortName, stMmPlmnInfo.aucShortName, sizeof(stEonsUcs2PlmnName.aucShortName));

    TAF_MMA_ReportEonsUcs2Rsp(TAF_ERR_NO_ERROR, &stEonsUcs2PlmnName);
    return;
}



 VOS_UINT8 TAF_MMA_TranslateOperatorName2UCS2(
    TAF_SDC_OPERATOR_NAME_STRU  *pstSrcNtwkName,
    VOS_CHAR                    *pucDstNtwkName,
    VOS_UINT8                    ucDstLen
)
 {
    VOS_UINT8                           ucCodScheme;
    VOS_UINT8                           uc7BitCharNum;
    VOS_UINT8                          *pucTmpNtwkName;
    VOS_UINT8                          *pTmpDstName;
    VOS_UINT8                           ucTmpDecodeLen;
    VOS_UINT8                           ucDecodeLen;
    VOS_UINT8                           i;

    VOS_UINT32                          ulRslt;

    ucDecodeLen = 0;

    /* pucSrcNtwkName�еı���ο�24.008 MM INFORMATION
       ��һ���ֽ��ǳ���,�ڶ����ֽ��Ǳ�������,������Ǳ������������� */
    if (0 == pstSrcNtwkName->ucLength)
    {
        return ucDecodeLen;
    }

    ucCodScheme     = pstSrcNtwkName->bitCoding;

    uc7BitCharNum   = (VOS_UINT8)(((pstSrcNtwkName->ucLength) * 8) / 7);
    pucTmpNtwkName    = &pstSrcNtwkName->aucOperatorName[0];

    ucTmpDecodeLen = uc7BitCharNum;
    if (0 != (((pstSrcNtwkName->ucLength) * 8) % 7))
    {
        ucTmpDecodeLen += 1;
    }

    pTmpDstName = PS_MEM_ALLOC(WUEPS_PID_MMC, ucTmpDecodeLen);
    if (VOS_NULL_PTR == pTmpDstName)
    {
        return ucDecodeLen;
    }

    /* �����7 BIT����,ת����UCS-2 */
    if (0 == ucCodScheme)
    {
        ulRslt = TAF_STD_UnPack7Bit(pucTmpNtwkName, uc7BitCharNum, 0,(VOS_UINT8*)pTmpDstName);

        if (VOS_OK != ulRslt)
        {
            MMA_WARNINGLOG("TAF_MMA_TranslateNtwkName2Str: TAF_STD_UnPack7Bit Err.");
        }

        /* ����������ת����UCS-2 */
        for (i = 0; i < ucTmpDecodeLen; i++)
        {
            if ((i * 2) < ucDstLen)
            {
                /*lint -e961*/
                *(pucDstNtwkName+i*2) = 0;
                *(pucDstNtwkName+(i*2 + 1)) = (VOS_CHAR)(pTmpDstName[i]);
                /*lint +e961*/
            }
            else
            {
                break;
            }
        }
        ucDecodeLen = (VOS_UINT8)((i - 1)*2);
    }
    else if (1 == ucCodScheme)
    {
        ucDecodeLen = pstSrcNtwkName->ucLength;
        if (ucDecodeLen > ucDstLen)
        {
            PS_MEM_CPY(pucDstNtwkName, pucTmpNtwkName, ucDstLen);
            ucDecodeLen = ucDstLen;
        }
        else
        {
            PS_MEM_CPY(pucDstNtwkName, pucTmpNtwkName, ucDecodeLen);
        }
    }
    else
    {
    }

    PS_MEM_FREE(WUEPS_PID_MMC, pTmpDstName);

    return ucDecodeLen;
 }
/* Deleted by k902809 for Iteration 11, 2015-3-30, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-30, end */

/* Added by c00318887 for AT&T phaseII, 2015-3-12, begin */
/**********************************************************
 �� �� ��  : TAF_MMA_ReportEonsUcs2Rsp
 ��������  : �ظ�EONSUCS2�Ĳ�ѯ
 �������  : TAF_ERROR_CODE_ENUM_UINT32          usErrorCode
             TAF_MMA_EONS_UCS2_PLMN_NAME_STRU    *pstEonsUcs2PlmnName
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��12��
    ��    ��   : c00318887
    �޸�����   : ��������
*************************************************************/
VOS_VOID TAF_MMA_ReportEonsUcs2Rsp(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode,
    TAF_MMA_EONS_UCS2_PLMN_NAME_STRU   *pstEonsUcs2PlmnName
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;

    pstMmaOperCtx   = TAF_MMA_GetOperCtxAddr();
    enRslt          = TAF_MMA_APP_OPER_RESULT_SUCCESS;

    if ( TAF_ERR_NO_ERROR != enErrorCode )
    {
        enRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
    }

    if (VOS_TRUE == TAF_MMA_GetSpecOperTypeIndex(TAF_MMA_OPER_EONS_UCS2_REQ, &ucCtxIndex))
    {
        TAF_MMA_SndEonsUcs2Rsp(&(pstMmaOperCtx[ucCtxIndex].stCtrl),
                                enRslt,
                                enErrorCode,
                                pstEonsUcs2PlmnName);

        /* ���CTX������  */
        TAF_MMA_ClearOperCtx(ucCtxIndex);
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReportEonsUcs2Rsp:ERROR");
    }

    return;

}

/* Added by c00318887 for AT&T phaseII, 2015-3-12, end */



VOS_UINT32 MMA_PhoneProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent= VOS_NULL_PTR;
    VOS_UINT8                           ucError = TAF_ERR_NO_ERROR;
    VOS_UINT8                          *pucTmp  = VOS_NULL_PTR;
    VOS_UINT32                          ulTmpAddr;
    /*���ӵ绰������̱���*/
    TAF_PH_PIN_DATA_STRU                stPinData;
    TAF_ME_PERSONALISATION_DATA_STRU    stMePersonalData;
    VOS_UINT16                          usMsgType;
    VOS_UINT16                          ClientId;
    VOS_UINT8                           OpId;
    MN_APP_REQ_MSG_STRU                *pstRcvMsg= VOS_NULL_PTR;

    PS_MEM_SET(&stPinData, 0, sizeof(TAF_PH_PIN_DATA_STRU));
    PS_MEM_SET(&stMePersonalData, 0, sizeof(TAF_ME_PERSONALISATION_DATA_STRU));

    pstRcvMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    usMsgType   = pstRcvMsg->usMsgName;
    ClientId    = pstRcvMsg->clientId;
    OpId        = pstRcvMsg->opId;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_PhoneProc():ERROR:ALLOC MEMORY FAIL!");

        return VOS_TRUE;
    }

    pucTmp = &(pstRcvMsg->aucContent[0]);

    switch(usMsgType)
    {


        case TAF_MSG_MMA_OP_PIN_REQ:
            ulTmpAddr = (VOS_UINT32)pucTmp;
            MMA_MEM_CPY((VOS_UINT8 *)&stPinData, (VOS_UINT8 *)ulTmpAddr, sizeof(TAF_PH_PIN_DATA_STRU));
            MMA_PinHandle(ClientId, OpId,stPinData);
            break;
        case TAF_MSG_MMA_ME_PERSONAL_REQ:
            ulTmpAddr = (VOS_UINT32)pucTmp;
            MMA_MEM_CPY((VOS_UINT8 *)&stMePersonalData, (VOS_UINT8 *)ulTmpAddr, sizeof(TAF_ME_PERSONALISATION_DATA_STRU));
            MMA_MePersonalisationHandle(ClientId, OpId,stMePersonalData);
            break;





        default:

            ucError = TAF_ERR_CMD_TYPE_ERROR;
            break;
    }
    if (TAF_ERR_NO_ERROR != ucError)
    {
        Taf_InitEventInfoOP(pstPhoneEvent);
        pstPhoneEvent->OP_PhoneError      = 1;
        pstPhoneEvent->PhoneEvent         = TAF_PH_EVT_ERR;
        pstPhoneEvent->ClientId           = ClientId;
        pstPhoneEvent->OpId               = OpId;
        pstPhoneEvent->PhoneError         = ucError;

        /* ���õ绰�����ϱ����� */
        MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    }

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

    return VOS_TRUE;
}

/*TAF_MMA_PnnListMemProtectTimerExpired*/


VOS_VOID TAF_MMA_RcvDelayPowerDownTimerExpired(VOS_VOID)
{
    /* ����API�ӿڽ����µ�ػ� */
    mdrv_sysboot_poweroff();
}


VOS_UINT32 MMA_TimeExpired(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    REL_TIMER_MSG                      *pMsg;

    pMsg = (REL_TIMER_MSG*)pstMsg;

    switch(pMsg->ulPara)
    {
        case TAF_USIM_OPPIN:
            MMA_OpPinExpired();
            break;



        case MMA_INTERNAL_TIMER_ID :
            MMA_ExpiredInternalTimer();
            break;
        case MMA_TIMER_FOR_PC_REPLAY :
            /* ����ط���Ϣ */
#ifndef __PS_WIN32_RECUR__

            /* ����PC��������, ��PC���߲�ʹ����NAS PC�ط���Ϣ�ķ��� */
            if ( (VOS_TRUE == g_ucMmaOmConnectFlg)
              && (VOS_TRUE == g_ucMmaOmPcRecurEnableFlg) )
            {
                NAS_MMA_SndOutsideContextData();
            }

#endif
            break;
        case TI_MN_PH_RESET:
            MN_PH_ResetTimerOutProc();
            break;
        case TI_MN_PH_PIN_OPER:
            MN_PH_PinOperTimerOutProc();
            break;



        case TI_TAF_MMA_DELAY_POWER_DOWN:
            TAF_MMA_RcvDelayPowerDownTimerExpired();
            break;


        case TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU:
            TAF_MMA_NetworkSelectionMenuCtrlTimerExpired();
            break;

        case TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING:
            TAF_MMA_RatBalancingCtrlTimerExpired();
            break;

        case TI_TAF_MMA_NET_SCAN_TIMER:
            TAF_MMA_NetScanTimerExpired();
            break;

        case TI_TAF_MMA_ABORT_NET_SCAN_TIMER:
            TAF_MMA_AbortNetScanTimerExpired();
            break;

        default:
            Sta_TimeoutProc(pMsg);
            break;
    }
    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_IsEventNeedRpt(
    TAF_PHONE_EVENT_INFO_STRU          *pEvent
)
{
    VOS_UINT32                          ulResult;

    ulResult                = VOS_TRUE;

    switch (pEvent->PhoneEvent)
    {


        /* ��״̬�ϱ� */
        case TAF_PH_EVT_USIM_INFO_IND:

            ulResult = TAF_MMA_IsSimStaChangeNeedRpt();

            break;

        default:
            ulResult = VOS_TRUE;
    }

    return ulResult;
}


/*lint -e429 -e830*/


VOS_VOID  Taf_PhoneEvent (TAF_PHONE_EVENT_INFO_STRU  *pEvent)
{

    /* BEGIN: Modified by liuyang id:48197, 2006/3/16   PN:A32D02382*/
    VOS_UINT8 ucTi;
    /* END:   Modified by liuyang id:48197, 2006/3/16 */
    VOS_UINT16 ClientId;
    VOS_UINT8 AppOpId;
    TAF_PHONE_EVENT PhoneEvent;

    TAF_SDC_CURC_RPT_CTRL_STRU          *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU   *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    PS_MEM_CPY(pEvent->aucCurcRptCfg, pstCurcRptCtrl->aucRptCfg, TAF_MMA_RPT_CFG_MAX_SIZE);
    PS_MEM_CPY(pEvent->aucUnsolicitedRptCfg, pstUnsolicitedRptCtrl->aucRptCfg, TAF_MMA_RPT_CFG_MAX_SIZE);

    ucTi = pEvent->OpId;
    switch(pEvent->PhoneEvent)
    {
        case TAF_PH_EVT_SERVICE_STATUS_IND:
        /*������ע��״̬���ź���������ص������ڹ㲥��Ϣ��*/
        case TAF_PH_EVT_PLMN_LIST_IND:
        case TAF_PH_EVT_POWER_STA_IND:
        case MN_PH_EVT_SIMLOCKED_IND:
        case MN_PH_EVT_ROAMING_IND:
        case TAF_PH_EVT_NSM_STATUS_IND:
        /* Deleted by k902809 for Iteration 11, 2015-3-23, begin */
        /* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-23, end */
            AppOpId = MMA_OP_ID_INTERNAL;
            ClientId = MMA_CLIENTID_BROADCAST;
            break;
         case TAF_PH_EVT_OP_PINREMAIN_CNF :
            ucTi = MMA_PH_PIN_TI;
            if (TAF_SUCCESS != MMA_GetIdByTi(TAF_MMA, ucTi, &ClientId, &AppOpId,&PhoneEvent))
            {
                MMA_WARNINGLOG("Taf_PhoneEvent():WARNING:Invoke Taf_GetIdByTi failed.");
                return;
            }
            break;


        /*PIN�����Ľṹ�Ѿ������ɣ����ǵ�PIN��ĳЩ����,��������Ȼ��������¼�
        ��������ʹ��PHONE EVENT�¼��ṹ���ڰ�����ClientId��OpId*/
        case TAF_PH_EVT_OP_PIN_CNF :
            ucTi = MMA_PH_PIN_TI;
            if (TAF_SUCCESS != MMA_GetIdByTi(TAF_MMA, ucTi, &ClientId, &AppOpId,&PhoneEvent))
            {
                MMA_WARNINGLOG("Taf_PhoneEvent():WARNING:Invoke Taf_GetIdByTi failed.");
                return;
            }
            break;

        /*TAF_PH_EVT_STOP_CNF, TAF_PH_EVT_START_CNF�¼�
        ���ߴ˷�֧, �����¼�û�о������*/
        default:
            if (ucTi > TAF_MAX_STATUS_TI)
            {   /*����APP��������ֱ�ӷ���*/
                return;
            }
            /*ͨ��Ti��ȡClientId,CallId*/
            if (TAF_SUCCESS != MMA_GetIdByTi(TAF_MMA, ucTi, &ClientId, &AppOpId,&PhoneEvent))
            {
                MMA_WARNINGLOG("Taf_PhoneEvent():WARNING:Invoke Taf_GetIdByTi failed.");
                return;
            }
            break;
    }

    pEvent->ClientId  = ClientId;
    pEvent->OpId      = AppOpId;

    /* ���õ绰�����ϱ����� */
    MN_PH_SendMsg(pEvent->ClientId,(VOS_UINT8*)pEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    return;
}
/*lint +e429 +e830*/

/* MMA_DefPhClassType��������ʹ�ã�ɾ�� */


VOS_VOID TAF_MMA_SndAtSubPnnList(
    VOS_UINT32                   ulSndNum,
    TAF_SDC_PNN_FILE_INFO_STRU  *pstPnnFileInfo
)
{
    TAF_PH_USIM_PNN_CNF_STRU           *pstPNN = VOS_NULL_PTR;
    VOS_UINT16                          usCurrIndex;
    VOS_UINT16                          i;

    i           = 0;
    usCurrIndex = gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usCurrIndex;

    pstPNN = (TAF_PH_USIM_PNN_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
              sizeof(TAF_PH_USIM_PNN_CNF_STRU)+(sizeof(TAF_PH_USIM_PNN_RECORD)*ulSndNum));

    if(VOS_NULL_PTR == pstPNN)
    {
        MMA_ReportParaQueryError(gstMmaValue.stPNN.ClientId, gstMmaValue.stPNN.OpId,
                                 TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_PNN_PARA);

        /* Deleted by c00318887 for AT&T phaseII, 2015-3-6, begin */
        /* Deleted by c00318887 for AT&T phaseII, 2015-3-6, end */

        return;
    }

    MMA_MEM_SET(pstPNN, 0, sizeof(TAF_PH_USIM_PNN_CNF_STRU)+(sizeof(TAF_PH_USIM_PNN_RECORD)*ulSndNum));

    pstPNN->TotalRecordNum            = ulSndNum;
    pstPNN->usPnnCurrIndex            = gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usCurrIndex;
    pstPNN->Icctype                   = gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.Icctype;

    for (i = 0; i < ulSndNum; i++)
    {
        pstPNN->PNNRecord[i].stOperNameShort.ucLength  = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameShort.ucLength;    /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstPNN->PNNRecord[i].stOperNameShort.bitExt    = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameShort.bitExt;      /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstPNN->PNNRecord[i].stOperNameShort.bitCoding = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameShort.bitCoding;   /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstPNN->PNNRecord[i].stOperNameShort.bitAddCi  = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameShort.bitAddCi;    /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstPNN->PNNRecord[i].stOperNameShort.bitSpare  = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameShort.bitSpare;    /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */

        PS_MEM_CPY(pstPNN->PNNRecord[i].stOperNameShort.aucOperatorName,
                   pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameShort.aucOperatorName,
                   TAF_SDC_MAX_OPER_NAME_NUM);

        pstPNN->PNNRecord[i].stOperNameLong.ucLength  = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameLong.ucLength;      /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstPNN->PNNRecord[i].stOperNameLong.bitExt    = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameLong.bitExt;        /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstPNN->PNNRecord[i].stOperNameLong.bitCoding = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameLong.bitCoding;     /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstPNN->PNNRecord[i].stOperNameLong.bitAddCi  = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameLong.bitAddCi;      /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstPNN->PNNRecord[i].stOperNameLong.bitSpare  = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameLong.bitSpare;      /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */

        PS_MEM_CPY(pstPNN->PNNRecord[i].stOperNameLong.aucOperatorName,
                   pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].stOperatorNameLong.aucOperatorName,
                   TAF_SDC_MAX_OPER_NAME_NUM);

        pstPNN->PNNRecord[i].ucPlmnAdditionalInfoLen = pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].ucPlmnAdditionalInfoLen;           /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */

        PS_MEM_CPY(pstPNN->PNNRecord[i].aucPlmnAdditionalInfo,
                   pstPnnFileInfo->astPnnRecordInfo[i + usCurrIndex].aucPlmnAdditionalInfo,
                   TAF_SDC_MAX_PLMN_ADDITIONAL_INFO_LEN);
    }

    MMA_ParaQueryReport(gstMmaValue.stPNN.ClientId, gstMmaValue.stPNN.OpId,
                        TAF_PH_PNN_PARA, TAF_ERR_NO_ERROR, pstPNN);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPNN);

}


/* Deleted by c00318887 for AT&T phaseII, 2015-3-6, begin */
/* TAF_MMA_ClearcPnnListQryCtrInfo */
/* TAF_MMA_PnnListMemProtectTimerProc */
/* Deleted by c00318887 for AT&T phaseII, 2015-3-6, end */


VOS_VOID TAF_MMA_AtTestPnnProc()
{
    TAF_SDC_PNN_FILE_INFO_STRU         *pstUsimPnnFileInfo = VOS_NULL_PTR;
    TAF_SDC_PNN_FILE_INFO_STRU         *pstSimPnnFileInfo  = VOS_NULL_PTR;
    TAF_PH_QRY_USIM_RANGE_INFO_STRU     stQryRangeInfo;

    PS_MEM_SET(&stQryRangeInfo, 0, sizeof(stQryRangeInfo));

    pstUsimPnnFileInfo = TAF_SDC_GetUsimPnnFileInfo();
    pstSimPnnFileInfo  = TAF_SDC_GetSimPnnFileInfo();

    if (0 != pstUsimPnnFileInfo->ulPnnRecordNum)
    {
        stQryRangeInfo.stUsimInfo.bFileExist    = VOS_TRUE;
        stQryRangeInfo.stUsimInfo.Icctype       = TAF_PH_ICC_USIM;
        stQryRangeInfo.stUsimInfo.ulTotalRecNum = pstUsimPnnFileInfo->ulPnnRecordNum;
        stQryRangeInfo.stUsimInfo.ulRecordLen   = pstUsimPnnFileInfo->ulPnnEfLen;
    }
    else
    {
        stQryRangeInfo.stUsimInfo.bFileExist    = VOS_FALSE;
    }

    if (0 != pstSimPnnFileInfo->ulPnnRecordNum)
    {
        stQryRangeInfo.stSimInfo.bFileExist     = VOS_TRUE;
        stQryRangeInfo.stSimInfo.Icctype        = TAF_PH_ICC_SIM;
        stQryRangeInfo.stSimInfo.ulTotalRecNum  = pstSimPnnFileInfo->ulPnnRecordNum;
        stQryRangeInfo.stSimInfo.ulRecordLen    = pstSimPnnFileInfo->ulPnnEfLen;
    }
    else
    {
        stQryRangeInfo.stSimInfo.bFileExist    = VOS_FALSE;
    }

    MMA_ParaQueryReport(gstMmaValue.stPNN.ClientId, gstMmaValue.stPNN.OpId, TAF_PH_PNN_RANGE_PARA, TAF_ERR_NO_ERROR, &stQryRangeInfo);

    return;
}


VOS_VOID TAF_MMA_AtTestOplProc()
{
    TAF_SDC_OPL_FILE_INFO_STRU         *pstUsimOplFileInfo = VOS_NULL_PTR;
    TAF_SDC_OPL_FILE_INFO_STRU         *pstSimOplFileInfo  = VOS_NULL_PTR;
    TAF_PH_QRY_USIM_RANGE_INFO_STRU     stQryRangeInfo;

    PS_MEM_SET(&stQryRangeInfo, 0, sizeof(stQryRangeInfo));

    pstUsimOplFileInfo = TAF_SDC_GetUsimOplFileInfo();
    pstSimOplFileInfo  = TAF_SDC_GetSimOplFileInfo();

    if (0 != pstUsimOplFileInfo->ulOplRecordNum)
    {
        stQryRangeInfo.stUsimInfo.bFileExist    = VOS_TRUE;
        stQryRangeInfo.stUsimInfo.Icctype       = TAF_PH_ICC_USIM;
        stQryRangeInfo.stUsimInfo.ulTotalRecNum = pstUsimOplFileInfo->ulOplRecordNum;
        stQryRangeInfo.stUsimInfo.ulRecordLen   = pstUsimOplFileInfo->ulOplEfLen;
    }
    else
    {
        stQryRangeInfo.stUsimInfo.bFileExist    = VOS_FALSE;
    }

    if (0 != pstSimOplFileInfo->ulOplRecordNum)
    {
        stQryRangeInfo.stSimInfo.bFileExist     = VOS_TRUE;
        stQryRangeInfo.stSimInfo.Icctype        = TAF_PH_ICC_SIM;
        stQryRangeInfo.stSimInfo.ulTotalRecNum  = pstSimOplFileInfo->ulOplRecordNum;
        stQryRangeInfo.stSimInfo.ulRecordLen    = pstSimOplFileInfo->ulOplEfLen;
    }
    else
    {
        stQryRangeInfo.stSimInfo.bFileExist    = VOS_FALSE;
    }

    MMA_ParaQueryReport(gstMmaValue.stOPL.ClientId, gstMmaValue.stOPL.OpId, TAF_PH_OPL_RANGE_PARA, TAF_ERR_NO_ERROR, &stQryRangeInfo);

    return;
}

VOS_VOID TAF_MMA_AtQryPnnProc(TAF_PH_QRY_USIM_INFO_STRU *pstInfo)
{
    VOS_UINT32                          ulSndNum; /* ���η��͵�Pnn��Ŀ */
    VOS_UINT16                          usUnSentNum;
    TAF_SDC_PNN_FILE_INFO_STRU         *pstPnnFileInfo = VOS_NULL_PTR;

    ulSndNum               = 0;
    usUnSentNum            = 0;

    if (TAF_PH_ICC_SIM == pstInfo->Icctype)
    {
        pstPnnFileInfo = TAF_SDC_GetSimPnnFileInfo();
    }
    else if (TAF_PH_ICC_USIM == pstInfo->Icctype)
    {
        pstPnnFileInfo = TAF_SDC_GetUsimPnnFileInfo();
    }
    else
    {
        MMA_ReportParaQueryError(gstMmaValue.stPNN.ClientId, gstMmaValue.stPNN.OpId,
                                                TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_PNN_PARA);

        return;
    }

    if ((0 == pstPnnFileInfo->ulPnnRecordNum)
     || (pstPnnFileInfo->ulPnnRecordNum < pstInfo->ulRecNum))
    {
        MMA_ReportParaQueryError(gstMmaValue.stPNN.ClientId, gstMmaValue.stPNN.OpId,
                                                TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_PNN_PARA);

        return;
    }

    /* �������Ҫ���ȡPNN�б����ϱ�������¼ */
    if (0 != pstInfo->ulRecNum)
    {
        gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usCurrIndex = (VOS_UINT16)pstInfo->ulRecNum - 1;

        ulSndNum = 1;
        TAF_MMA_SndAtSubPnnList(ulSndNum, pstPnnFileInfo);

        return;
    }

    gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usCurrIndex = pstInfo->stPnnQryIndex.usPnnCurrIndex;
    gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usReadNum   = pstInfo->stPnnQryIndex.usPnnNum;
    gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.Icctype     = pstInfo->Icctype;

    if (0 == pstPnnFileInfo->ulPnnRecordNum)
    {
        MMA_WARNINGLOG("TAF_MMA_AtQryPnnListProc():The PNN LIST is empty!");

        TAF_MMA_SndAtSubPnnList(ulSndNum, pstPnnFileInfo);
        return;
    }

    /* ���Ҫ���ȡ��index���ڵ���PNN������Ŀ����Ϊ�����һ���ϱ����ϱ�һ�����б���ֹͣ������ʱ�� */
    if (gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usCurrIndex >= (VOS_UINT16)pstPnnFileInfo->ulPnnRecordNum)
    {
        MMA_WARNINGLOG("TAF_MMA_AtQryPnnListProc():There is no unsent pnn in the list!");

        ulSndNum               = 0;
        TAF_MMA_SndAtSubPnnList(ulSndNum, pstPnnFileInfo);


        return;
    }

    /* ���PNN LIST����Ŀ��ȥAT�·���INDEX���ڵ���ATҪ���ȡ����Ŀ�����ϱ�ATҪ���ȡ����Ŀ */
    usUnSentNum = (VOS_UINT16)pstPnnFileInfo->ulPnnRecordNum - gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usCurrIndex;

    if (usUnSentNum >= gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usReadNum)
    {
        ulSndNum = gstMmaValue.stPNN.stPnnListInfo.stPnnListCtrInfo.usReadNum;
    }
    else
    {
        ulSndNum               = usUnSentNum;
    }

    TAF_MMA_SndAtSubPnnList(ulSndNum, pstPnnFileInfo);

}


VOS_VOID TAF_MMA_AtQryOplProc(TAF_PH_QRY_USIM_INFO_STRU *pstInfo)
{
    TAF_SDC_OPL_FILE_INFO_STRU         *pstOplFileInfo = VOS_NULL_PTR;
    TAF_PH_USIM_OPL_CNF_STRU           *pstOPL;
    VOS_UINT8                           ucSimType;
    VOS_UINT32                          ulBeginIndex;
    VOS_UINT32                          i;

    ucSimType = 0;
    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucSimType);

    if (TAF_PH_ICC_SIM == pstInfo->Icctype)
    {
        pstOplFileInfo = TAF_SDC_GetSimOplFileInfo();
    }
    else if (TAF_PH_ICC_USIM == pstInfo->Icctype)
    {
        pstOplFileInfo = TAF_SDC_GetUsimOplFileInfo();
    }
    else
    {
        MMA_ReportParaQueryError(gstMmaValue.stOPL.ClientId, gstMmaValue.stOPL.OpId,
                                                TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_OPL_PARA);

        return;
    }

    if ((0 == pstOplFileInfo->ulOplRecordNum)
     || (pstOplFileInfo->ulOplRecordNum < pstInfo->ulRecNum))
    {
        MMA_ReportParaQueryError(gstMmaValue.stOPL.ClientId, gstMmaValue.stOPL.OpId,
                                                TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_OPL_PARA);

        return;
    }

    pstOPL = (TAF_PH_USIM_OPL_CNF_STRU *)VOS_MemAlloc(WUEPS_PID_MMA, DYNAMIC_MEM_PT,
                                sizeof(TAF_PH_USIM_OPL_CNF_STRU) + (sizeof(TAF_PH_USIM_OPL_RECORD) * pstOplFileInfo->ulOplRecordNum));

    if(VOS_NULL_PTR == pstOPL)
    {
        MMA_ReportParaQueryError(gstMmaValue.stOPL.ClientId, gstMmaValue.stOPL.OpId,
                            TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_OPL_PARA);

        return;
    }

    MMA_MEM_SET(pstOPL, 0, sizeof(TAF_PH_USIM_OPL_CNF_STRU) + (sizeof(TAF_PH_USIM_OPL_RECORD) * pstOplFileInfo->ulOplRecordNum));

    pstOPL->CardType  = ucSimType;
    pstOPL->cWildCard = TAF_SDC_GetPlmnCompareWildCard();

    if (0 != pstInfo->ulRecNum)
    {
        /* ָ�������ϱ� */
        ulBeginIndex           = pstInfo->ulRecNum - 1;
        pstOPL->TotalRecordNum = 1;

        /* ת��Ϊ�ϱ��ĸ�ʽ */
        pstOPL->OPLRecord[0].PLMN[0]  =  pstOplFileInfo->astOplRecordInfo[ulBeginIndex].stPlmnId.ulMcc & 0xFF;
        pstOPL->OPLRecord[0].PLMN[1]  =  (pstOplFileInfo->astOplRecordInfo[ulBeginIndex].stPlmnId.ulMcc & 0xFF00) >> 8;
        pstOPL->OPLRecord[0].PLMN[2]  =  (pstOplFileInfo->astOplRecordInfo[ulBeginIndex].stPlmnId.ulMcc & 0xFF0000) >> 16;
        pstOPL->OPLRecord[0].PLMN[3]  =  pstOplFileInfo->astOplRecordInfo[ulBeginIndex].stPlmnId.ulMnc & 0xFF;
        pstOPL->OPLRecord[0].PLMN[4]  =  (pstOplFileInfo->astOplRecordInfo[ulBeginIndex].stPlmnId.ulMnc & 0xFF00) >> 8;
        pstOPL->OPLRecord[0].PLMN[5]  =  (pstOplFileInfo->astOplRecordInfo[ulBeginIndex].stPlmnId.ulMnc & 0xFF0000) >> 16;
        pstOPL->OPLRecord[0].PlmnLen  =  6;
        if ((pstOPL->OPLRecord[0].PLMN[5] >= 0xA)
         && (pstOPL->OPLRecord[0].PLMN[5] <= 0xF))
        {
            pstOPL->OPLRecord[0].PLMN[5] = 0xF;
            pstOPL->OPLRecord[0].PlmnLen = 5;
        }
        pstOPL->OPLRecord[0].LACLow   =  pstOplFileInfo->astOplRecordInfo[ulBeginIndex].usLacRangeLow;
        pstOPL->OPLRecord[0].LACHigh  =  pstOplFileInfo->astOplRecordInfo[ulBeginIndex].usLacRangeHigh;
        pstOPL->OPLRecord[0].PNNIndex =  pstOplFileInfo->astOplRecordInfo[ulBeginIndex].usPnnIndex;

        MMA_ParaQueryReport(gstMmaValue.stOPL.ClientId, gstMmaValue.stOPL.OpId,
                                        TAF_PH_OPL_PARA, TAF_ERR_NO_ERROR, pstOPL);

        PS_MEM_FREE(WUEPS_PID_MMA, pstOPL);

        return;

    }

    /* ȫ���ϱ� */
    ulBeginIndex           = 0;
    pstOPL->TotalRecordNum = pstOplFileInfo->ulOplRecordNum;

    for (i = ulBeginIndex; i < pstOPL->TotalRecordNum; i++)
    {
        /* ת��Ϊ�ϱ��ĸ�ʽ */
        pstOPL->OPLRecord[i].PLMN[0]  =  pstOplFileInfo->astOplRecordInfo[i].stPlmnId.ulMcc & 0xFF;                 /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstOPL->OPLRecord[i].PLMN[1]  =  (pstOplFileInfo->astOplRecordInfo[i].stPlmnId.ulMcc & 0xFF00) >> 8;        /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstOPL->OPLRecord[i].PLMN[2]  =  (pstOplFileInfo->astOplRecordInfo[i].stPlmnId.ulMcc & 0xFF0000) >> 16;     /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstOPL->OPLRecord[i].PLMN[3]  =  pstOplFileInfo->astOplRecordInfo[i].stPlmnId.ulMnc & 0xFF;                 /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstOPL->OPLRecord[i].PLMN[4]  =  (pstOplFileInfo->astOplRecordInfo[i].stPlmnId.ulMnc & 0xFF00) >> 8;        /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstOPL->OPLRecord[i].PLMN[5]  =  (pstOplFileInfo->astOplRecordInfo[i].stPlmnId.ulMnc & 0xFF0000) >> 16;     /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstOPL->OPLRecord[i].PlmnLen  =  6;                                                                         /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        if ((pstOPL->OPLRecord[i].PLMN[5] >= 0xA)
         && (pstOPL->OPLRecord[i].PLMN[5] <= 0xF))
        {
            pstOPL->OPLRecord[i].PLMN[5] = 0xF;                                                                     /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
            pstOPL->OPLRecord[i].PlmnLen = 5;                                                                       /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        }
        pstOPL->OPLRecord[i].LACLow   =  pstOplFileInfo->astOplRecordInfo[i].usLacRangeLow;                         /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstOPL->OPLRecord[i].LACHigh  =  pstOplFileInfo->astOplRecordInfo[i].usLacRangeHigh;                        /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
        pstOPL->OPLRecord[i].PNNIndex =  pstOplFileInfo->astOplRecordInfo[i].usPnnIndex;                            /* [false alarm]:ͨ����̬�����ڴ�Ľ��  */
    }

    MMA_ParaQueryReport(gstMmaValue.stOPL.ClientId, gstMmaValue.stOPL.OpId,
                                    TAF_PH_OPL_PARA, TAF_ERR_NO_ERROR, pstOPL);

    PS_MEM_FREE(WUEPS_PID_MMA, pstOPL);

    return;
}


/* TAF_MMA_IsNeedSndGetUsimPnnFileReq */

/* Added by c00318887 for AT&T phaseII, 2015-3-6, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_IsTestCmdTypeOfUsimFile
 ��������  : ���ݼ�¼���ж��Ƿ���USIM���������͵�AT����(AT^pnn=?)
 �������  : TAF_PH_QRY_USIM_INFO_STRU             *pstInfo
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��6��
    ��    ��   : c00318887
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsTestCmdTypeOfUsimFile(
        TAF_PH_QRY_USIM_INFO_STRU           *pstInfo
)
{
    if (TAF_PH_INVALID_USIM_REC == pstInfo->ulRecNum)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by c00318887 for AT&T phaseII, 2015-3-6, end */

VOS_VOID MMA_QryUsimInfo(
    VOS_UINT16        ClientId,
    VOS_UINT8         OpId,
    TAF_PH_QRY_USIM_INFO_STRU           *pstInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucSimStatus;
    VOS_UINT32                          ulFileExist;
    TAF_PARA_TYPE                       enRptQryType;


    if(MMA_TIMER_STOP != gstMmaInternalTimer.stTimer.ucTimerStatus)
    {
        MMA_WARNINGLOG("MMA_QryUsimInfo():WARNING:USIM is not Ready!");
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_UNSPECIFIED_ERROR,
                                 TAF_PH_PNN_PARA);
        return;
    }

    /*�жϿ�״̬*/
    ulRet = MMA_PhoneGetUsimStatus(&ucSimStatus );
    if ( (ulRet           != MMA_SUCCESS )
       ||(MMA_USIM_ABSENT == ucSimStatus)
       )
    {
        MMA_WARNINGLOG("MMA_QryUsimInfo():WARNING:USIM is Error or Absent!");
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_USIM_SIM_CARD_NOTEXIST,
                                 TAF_PH_PNN_PARA);
        return;
    }

    if (TAF_PH_PNN_FILE == pstInfo->enEfId)
    {

        ulFileExist = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_PLMN_NTWRK_NAME);

        enRptQryType = TAF_PH_PNN_PARA;
    }
    else
    {

       ulFileExist = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_OPLMN_LIST);

       enRptQryType = TAF_PH_OPL_PARA;
    }

    if (PS_USIM_SERVICE_NOT_AVAILIABLE == ulFileExist)
    {
        if (VOS_TRUE == MMA_IsNeedToDisplayCPHSOperNameStr())
        {
            /*ʹ��CPHS�ļ��� SIM�� PNN�ϱ���6f14��ֵ��Opl����OK,���̨���������CPHS����ʾҪ��*/
            if (TAF_PH_PNN_FILE == pstInfo->enEfId)
            {
                MMA_ReportPNNParaFromCPHSOperNameStr(ClientId, OpId);
            }
            else
            {
                MMA_ReportOPLParaForCPHSDisplay(ClientId, OpId);
            }
        }
        else
        {
            MMA_WARNINGLOG("MMA_QryUsimInfo():WARNING:file not exist!");
            MMA_ReportParaQueryError(ClientId, OpId,
                                     TAF_ERR_FILE_NOT_EXIST,
                                     enRptQryType);
        }
        return;
    }

    /* ʹ��ȫ�ֱ����д�������ϱ� */
    switch (pstInfo->enEfId)
    {
        case TAF_PH_PNN_FILE:
            gstMmaValue.stPNN.ClientId = ClientId;
            gstMmaValue.stPNN.OpId     = OpId;

            if (VOS_TRUE == TAF_MMA_IsTestCmdTypeOfUsimFile(pstInfo))
            {
                /* at^pnn=?���� */
                TAF_MMA_AtTestPnnProc();
            }
            else
            {
                TAF_MMA_AtQryPnnProc(pstInfo);
            }

            break;

        case TAF_PH_OPL_FILE:
            gstMmaValue.stOPL.ClientId = ClientId;
            gstMmaValue.stOPL.OpId     = OpId;

            if (VOS_TRUE == TAF_MMA_IsTestCmdTypeOfUsimFile(pstInfo))
            {
                /* at^opl=?���� */
                TAF_MMA_AtTestOplProc();
            }
            else
            {
                TAF_MMA_AtQryOplProc(pstInfo);
            }

            break;

        default:
            MMA_WARNINGLOG("MMA_QryUsimInfo():efid not support");
            break;
    }

    return;
}


VOS_VOID MMA_CPnnQuery(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PH_ICC_TYPE                    *pIccType
)
{
    VOS_UINT32                      ulRet;
    VOS_UINT8                       ucSimStatus;
    VOS_UINT32                      ulPnnExistFlg;
    VOS_UINT32                      ulOplExistFlg;

    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsServiceStatus;

    enCsServiceStatus = TAF_SDC_GetCsServiceStatus();
    enPsServiceStatus = TAF_SDC_GetPsServiceStatus();

    if(MMA_TIMER_STOP != gstMmaInternalTimer.stTimer.ucTimerStatus)
    {
        MMA_WARNINGLOG("MMA_PnnQuery():WARNING:USIM is not Ready!");
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_UNSPECIFIED_ERROR,
                                 TAF_PH_CPNN_PARA);
        return;
    }

    /*�жϿ�״̬*/
    ulRet = MMA_PhoneGetUsimStatus(&ucSimStatus );
    if ( (ulRet           != MMA_SUCCESS )
       ||(MMA_USIM_ABSENT == ucSimStatus)
       )
    {
        MMA_WARNINGLOG("MMA_PnnQuery():WARNING:USIM is Error or Absent!");
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_USIM_SIM_CARD_NOTEXIST,
                                 TAF_PH_CPNN_PARA);
        return;
    }

    if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enCsServiceStatus)
     && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enPsServiceStatus) )
    {
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_UNSPECIFIED_ERROR,
                                 TAF_PH_CPNN_PARA);
        return;
    }
    else
    {
        ulPnnExistFlg = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_PLMN_NTWRK_NAME);
        ulOplExistFlg = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_OPLMN_LIST);

        if ( (PS_USIM_SERVICE_NOT_AVAILIABLE == ulPnnExistFlg)
            || (PS_USIM_SERVICE_NOT_AVAILIABLE == ulOplExistFlg) )
        {
            MMA_ReportParaQueryError(ClientId, OpId,
                                     TAF_ERR_UNSPECIFIED_ERROR,
                                     TAF_PH_CPNN_PARA);
            return;
        }

        MMA_CPnnReport(*pIccType, ClientId, OpId);

        return;
    }
}

/*MMA_GetPlmnIdxInOplList*/




VOS_VOID MMA_CPnnReport(
    TAF_PH_ICC_TYPE                     ucIccType,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_SDC_OPL_FILE_INFO_STRU         *pstOplFileInfo = VOS_NULL_PTR;
    TAF_SDC_PNN_FILE_INFO_STRU         *pstPnnFileInfo = VOS_NULL_PTR;
    TAF_PH_USIM_PNN_CNF_STRU           *pstPNN         = VOS_NULL_PTR;
    VOS_UINT8                           ucRoamFlag;
    TAF_MMA_MM_INFO_PLMN_NAME_STRU      stMmInfoPlmnName;
    VOS_UINT32                          ulPnnIndex;

    if (TAF_PH_ICC_SIM == ucIccType)
    {
        pstOplFileInfo = TAF_SDC_GetSimOplFileInfo();
        pstPnnFileInfo = TAF_SDC_GetSimPnnFileInfo();
    }
    else if (TAF_PH_ICC_USIM == ucIccType)
    {
        pstOplFileInfo = TAF_SDC_GetUsimOplFileInfo();
        pstPnnFileInfo = TAF_SDC_GetUsimPnnFileInfo();
    }
    else
    {
        MMA_ReportParaQueryError(usClientId, ucOpId,
                            TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_CPNN_PARA);

        return;
    }

    pstPNN   = (TAF_PH_USIM_PNN_CNF_STRU *)VOS_MemAlloc(WUEPS_PID_MMA, DYNAMIC_MEM_PT,
                                                        sizeof(TAF_PH_USIM_PNN_CNF_STRU));
    if (VOS_NULL_PTR == pstPNN)
    {
        MMA_ReportParaQueryError(usClientId, ucOpId,
                            TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_CPNN_PARA);

        return;
    }

    PS_MEM_SET(pstPNN, 0, sizeof(TAF_PH_USIM_PNN_CNF_STRU));
    PS_MEM_SET(&stMmInfoPlmnName, 0, sizeof(stMmInfoPlmnName));

    pstPNN->TotalRecordNum = 0;
    ucRoamFlag             = MMA_IsRoam(TAF_SDC_GetAppRoamFlg());

    /* OPL��PNN�ļ���¼����Ϊ0����ʧ�� */
    if ((0 == pstPnnFileInfo->ulPnnRecordNum)
     && (0 == pstOplFileInfo->ulOplRecordNum))
    {
        MMA_ReportParaQueryError(usClientId, ucOpId,
                            TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_CPNN_PARA);

        return;
    }

    /* OPL�ļ���¼Ϊ0��PNN�ļ���¼��Ϊ0��פ��hplmn�ϣ�����PNN�ļ���һ����¼��Ӧ����Ӫ������ */
    if ((0 == pstOplFileInfo->ulOplRecordNum)
     && (TAF_PH_NO_ROAM == ucRoamFlag))
    {
        ulPnnIndex = 1;
    }
    else
    {
        /* OPL��PNN�ļ���¼����Ϊ0 */
        ulPnnIndex = TAF_MMA_GetPlmnPnnIndexInOplFile(TAF_SDC_GetAppServicePlmnId(), pstOplFileInfo);
    }

    /* ��OPL�л�ȡ��PNN index�Ƿ������֧��100��������ʧ�� */
    if ((ulPnnIndex < TAF_SDC_VALID_PNN_LOW_INDEX)
     || (ulPnnIndex > TAF_SDC_PNN_MAX_RECORD_NUM))
    {
        MMA_ReportParaQueryError(usClientId, ucOpId,
                            TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_CPNN_PARA);

        return;

    }

    pstPNN->TotalRecordNum= 1;
    pstPNN->PNNRecord[0].stOperNameLong.bitExt     = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong.bitExt;
    pstPNN->PNNRecord[0].stOperNameLong.bitCoding  = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong.bitCoding;
    pstPNN->PNNRecord[0].stOperNameLong.bitAddCi   = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong.bitAddCi;
    pstPNN->PNNRecord[0].stOperNameLong.bitSpare   = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong.bitSpare;
    pstPNN->PNNRecord[0].stOperNameLong.ucLength   = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong.ucLength;
    PS_MEM_CPY(pstPNN->PNNRecord[0].stOperNameLong.aucOperatorName, pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong.aucOperatorName, TAF_SDC_MAX_OPER_NAME_NUM);

    pstPNN->PNNRecord[0].stOperNameShort.bitExt    = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort.bitExt;
    pstPNN->PNNRecord[0].stOperNameShort.bitCoding = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort.bitCoding;
    pstPNN->PNNRecord[0].stOperNameShort.bitAddCi  = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort.bitAddCi;
    pstPNN->PNNRecord[0].stOperNameShort.bitSpare  = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort.bitSpare;
    pstPNN->PNNRecord[0].stOperNameShort.ucLength  = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort.ucLength;

    PS_MEM_CPY(pstPNN->PNNRecord[0].stOperNameShort.aucOperatorName, pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort.aucOperatorName, TAF_SDC_MAX_OPER_NAME_NUM);

    pstPNN->PNNRecord[0].ucPlmnAdditionalInfoLen = pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].ucPlmnAdditionalInfoLen;
    PS_MEM_CPY(pstPNN->PNNRecord[0].aucPlmnAdditionalInfo, pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].aucPlmnAdditionalInfo, TAF_SDC_MAX_PLMN_ADDITIONAL_INFO_LEN);

    MMA_ParaQueryReport(usClientId, ucOpId,
                        TAF_PH_CPNN_PARA, TAF_ERR_NO_ERROR, pstPNN);

    return;
}


VOS_VOID Mma_LoadDefault(VOS_VOID)
{
    NAS_NVIM_MS_CLASS_STRU              stMsClass;
    NAS_NVIM_SELPLMN_MODE_STRU          stPlmnSelMode;
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   stSetBand;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulAutoSwitchOnFlg;

    /*set default value:+CGCLASS*/
    PS_MEM_SET(&stMsClass, 0x00, sizeof(NAS_NVIM_MS_CLASS_STRU));
    stMsClass.ucMsClass = TAF_PH_MS_CLASS_A;
    ulLength    = 0;

    gstMmaValue.stSetMsClass.NewMsClassType = stMsClass.ucMsClass;
    (VOS_VOID)NV_GetLength(en_NV_Item_MMA_MsClass, &ulLength);

    if (NV_OK != NV_Write(en_NV_Item_MMA_MsClass, &stMsClass, ulLength))
    {
        MMA_WARNINGLOG("Mma_LoadDefault():WARNING:Write NV:MsClass FAIL!");
    }

    stPlmnSelMode.usSelPlmnMode = NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO;
    (VOS_VOID)NV_GetLength(en_NV_Item_SelPlmn_Mode, &ulLength);

    if (NV_OK != NV_Write (en_NV_Item_SelPlmn_Mode, &stPlmnSelMode, ulLength))
    {
        MMA_WARNINGLOG("Mma_LoadDefault():WARNING:Write NV:SelPlmn_Mode, FAIL!");
    }


    stSetBand.unGsmBand.BitBand.BandGsm850 = 1;
    stSetBand.unGsmBand.BitBand.BandGsmP900 = 1;
    stSetBand.unGsmBand.BitBand.BandGsmR900 = 1;
    stSetBand.unGsmBand.BitBand.BandGsmE900 = 1;
    stSetBand.unGsmBand.BitBand.BandGsm1800 = 1;
    stSetBand.unGsmBand.BitBand.BandGsm1900 = 1;

    stSetBand.unWcdmaBand.BitBand.BandWCDMA_I_2100 = 1;
    stSetBand.unWcdmaBand.BitBand.BandWCDMA_II_1900 = 1;
    stSetBand.unWcdmaBand.BitBand.BandWCDMA_V_850 = 1;

    PS_MEM_SET(stSetBand.aucReserved1, 0, sizeof(stSetBand.aucReserved1));
    PS_MEM_SET(stSetBand.aucReserved2, 0, sizeof(stSetBand.aucReserved2));

    /* ����Ƶ��NV */
    if (NV_OK != NV_Write(en_NV_Item_Support_Freqbands,
                          &(stSetBand),
                          sizeof(TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU)))
    {
        MMA_WARNINGLOG("Mma_LoadDefault():WARNING:NVIM_Write en_NV_Item_Support_Freqbands failed");
    }

    ulAutoSwitchOnFlg = MMA_RF_AUTO_TEST_DISABLE;
    (VOS_VOID)NV_GetLength(en_NV_Item_RF_Auto_Test_Flag, &ulLength);

    if (NV_OK != NV_Write(en_NV_Item_RF_Auto_Test_Flag,
            (VOS_VOID*)(&ulAutoSwitchOnFlg),
            ulLength))
    {
        MMA_WARNINGLOG("Mma_LoadDefault():WARNING:NVIM_Write en_NV_Item_Support_Freqbands failed");
    }

    TAF_MMA_SetAutoSwitchOnFlg(ulAutoSwitchOnFlg);
}

/* Deleted by wx270776 for OM�ں�, 2015-7-17, begin */

/* Deleted by wx270776 for OM�ں�, 2015-7-17, end */



VOS_UINT32 MMA_WriteValue2Nvim(const NV_ID_ENUM_U16 enNVItemType,
                               VOS_VOID *pData, VOS_UINT16 usDataLen)
{
    VOS_UINT8* pNvTemp;
    VOS_UINT8* pDataTemp;
    VOS_UINT16 i;

    i = 0;
    pDataTemp = (VOS_UINT8*)pData;

    pNvTemp = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_MMA, usDataLen);

    if (VOS_NULL_PTR == pNvTemp)
    {
        MMA_ERRORLOG("MMA_WriteValue2Nvim:ERROR:ALLOC MEMORY FAIL.");
        return MMA_ERROR;
    }

    PS_MEM_SET(pNvTemp, 0, usDataLen);

    if ( NV_OK == NV_Read(enNVItemType, pNvTemp, usDataLen) )
    {
        for ( i = 0 ; i < usDataLen ; i++ )
        {
            if ( *(pDataTemp + i) != *(pNvTemp + i))
            {
                break;
            }
        }
    }

    MMC_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pNvTemp);

    if ( i == usDataLen )
    {
        MMA_INFOLOG("MMA_WriteValue2Nvim():The content to write is same as NV's");
        return MMA_SUCCESS;
    }

    if (NV_OK !=  NV_Write(enNVItemType, pData, usDataLen))
    {
         MMA_WARNINGLOG("MMA_WriteValue2Nvim():WARNING:Invoke NVIM Write function falied");
         return MMA_ERROR;
    }

    return MMA_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : MMA_SyncMsClassTypeGolbalValue
 ��������  : ����ȫ�ֱ���gstMmaValue���й��ֻ����͵Ĳ���
 �������  : TAF_PH_MS_CLASS_TYPE MsClass
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��9��24��
    ��    ��   : liuyang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MMA_UpdateMsClassTypeGolbalValue(TAF_PH_MS_CLASS_TYPE MsClass)
{
    /*�������ò�����־λ��ͬ��ȫ�ֲ���*/
    gstMmaValue.pg_StatusContext->ucModeService             = MsClass;
    gstMmaValue.stSetMsClass.MsClassType                    = MsClass;
    gstMmaValue.stSetMsClass.NewMsClassType                 = MsClass;
    return;
}
VOS_VOID MMA_ImsiToImsiStr(VOS_CHAR  *pcImsi)
{
    VOS_UINT32                          i;

    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;

    pucImsi = TAF_SDC_GetSimImsi();

    for (i = 1; i <9; i++)
    {
        /*lint -e961*/
        if (1 == i)
        {
            *pcImsi++ = ((pucImsi[i] >> 4) & 0x0f) + 0x30;
        }
        else
        {
            *pcImsi++ = (pucImsi[i] & 0x0f) + 0x30;
            *pcImsi++ = ((pucImsi[i] >> 4) & 0x0f) + 0x30;
        }
        /*lint +e961*/
    }

}
VOS_UINT32 MMA_GetCardLockCfgData(VOS_VOID)
{
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU          stSimLockPlmnInfo;
    TAF_CUSTOM_CARDLOCK_STATUS_STRU             stCardLockStatus;
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU          stSimLockMaxTimes;
    VOS_UINT32                                  ulResult;


    PS_MEM_SET(&stSimLockPlmnInfo, 0x00, sizeof(stSimLockPlmnInfo));
    PS_MEM_SET(&stCardLockStatus,  0x00, sizeof(stCardLockStatus));
    PS_MEM_SET(&stSimLockMaxTimes, 0x00, sizeof(stSimLockMaxTimes));

    ulResult = NV_Read(en_NV_Item_CardlockStatus,
                       &stCardLockStatus,
                       (VOS_UINT32)(sizeof(stCardLockStatus)));
    if (NV_OK != ulResult)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_WARNING, "MMA_GetCardLockCfgData:WARNING: Not read sim lock status");
        return VOS_ERR;
    }
    g_MmaNewValue.stCardLockStatus = stCardLockStatus;

    ulResult = NV_Read(en_NV_Item_CustomizeSimLockMaxTimes,
                       &stSimLockMaxTimes,
                       sizeof(stSimLockMaxTimes));
    if (NV_OK != ulResult)
    {
        g_MmaNewValue.stSimLockMaxTimes.ulStatus = VOS_FALSE;
        g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
    }
    else
    {
        g_MmaNewValue.stSimLockMaxTimes = stSimLockMaxTimes;
    }

    ulResult = NV_Read(en_NV_Item_CustomizeSimLockPlmnInfo,
                       &stSimLockPlmnInfo,
                       sizeof(stSimLockPlmnInfo));
    if (NV_OK != ulResult)
    {
        g_MmaNewValue.stSimLockPlmnInfo.ulStatus = VOS_FALSE;
        PS_MEM_SET(g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange, (VOS_CHAR)0xaa,
                       sizeof(g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange));
    }
    else
    {
        g_MmaNewValue.stSimLockPlmnInfo = stSimLockPlmnInfo;
    }

    return VOS_OK;
}

VOS_UINT32 Taf_GetSimLockStatus(VOS_BOOL *pbActiveFlg)
{

    TAF_CUSTOM_CARDLOCK_STATUS_STRU             stCardLockStatus;
    VOS_UINT32                                  ulResult;


    PS_MEM_SET(&stCardLockStatus, 0x00, sizeof(stCardLockStatus));

    ulResult = NV_Read(en_NV_Item_CardlockStatus,
                       &stCardLockStatus,
                       (VOS_UINT32)(sizeof(stCardLockStatus)));

    if (NV_OK != ulResult)
    {
        MN_WARN_LOG("Taf_GetSimLockStatus:WARNING:  read sim lock status fail");
        return VOS_ERR;
    }

    if ((VOS_TRUE == MMA_IsSimLockPlmnInfoValid())
     && (NV_ITEM_ACTIVE == stCardLockStatus.ulStatus)
     && (TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE != stCardLockStatus.enCardlockStatus))
    {
        *pbActiveFlg = VOS_TRUE;
    }
    else
    {
        *pbActiveFlg = VOS_FALSE;

    }

    return VOS_OK;
}

VOS_UINT32 MMA_IsImsiIllegal(VOS_VOID)
{
    VOS_UINT32                          i,j;
    VOS_UINT32                          ulRslt = VOS_FALSE;
    VOS_UINT8                           aucTmpImsi[20];
    VOS_INT                             CmpRslt1,CmpRslt2;

    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;

    pucImsi = TAF_SDC_GetSimImsi();


    if (VOS_FALSE == g_MmaNewValue.stSimLockPlmnInfo.ulStatus)
    {
        return VOS_FALSE;
    }

    /* �ж���ǰ��IMSI�Ƿ��NV���ƥ�� */
    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        if (0xAA == g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin[0])
        {
            continue;
        }

        (VOS_VOID)VOS_MemSet(aucTmpImsi, 0x00, 20);
        for (j=0; j < 8; j++)
        {
            if (j < 7)
            {
                aucTmpImsi[j] = (VOS_UINT8)((pucImsi[j + 1] & 0xf0) + ((pucImsi[j + 2]) & 0x0f));
            }
            else
            {
                aucTmpImsi[j] = (VOS_UINT8)((pucImsi[j + 1] & 0xf0) + 0x0f);
            }

            if ((0x0f == (g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin[j] & 0x0f))
             && (0xff != g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin[j]))
            {
                aucTmpImsi[j] = (VOS_UINT8)((aucTmpImsi[j] & 0xf0) + 0x0f);
                j++;
                break;
            }


            if (0xff == g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin[j])
            {
                break;
            }

        }

        CmpRslt1 = VOS_MemCmp(aucTmpImsi,
                              g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                              j);

        CmpRslt2 = VOS_MemCmp(aucTmpImsi,
                              g_MmaNewValue.stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeEnd,
                              j);

        if ((CmpRslt1>=0) && (CmpRslt2<=0))
        {
            ulRslt = VOS_FALSE;
            break;
        }
        else
        {
            ulRslt = VOS_TRUE;
        }
    }

    return ulRslt;
}
VOS_UINT32 MMA_IsEygptVdfImsiIllegal()
{
    VOS_UINT32                          i;
    VOS_CHAR                            acTmpImsi[16] = {0};
    VOS_CHAR                            *pacEygptVdf[]={"50503", "60202", "26202",
                                                        "20205", "21670", "27201",
                                                        "22210", "20404", "53001",
                                                        "26801", "21401", "23415",
                                                        "27801", "22601", "27602",
                                                        "54201", "23003", "20601",
                                                        "65501", "20810", "23201",
                                                        "24008", "21910", "23801",
                                                        "27403", "24405", "29340",
                                                        "41902", "42602", "28001",
                                                        "24802", "27001", "45406",
                                                        "52503", "28401", "23211",
                                                        "24421"};

    MMA_ImsiToImsiStr(acTmpImsi);
    for (i = 0; i < 37; i++)
    {
        if (0 == VOS_MemCmp(acTmpImsi, pacEygptVdf[i], 5))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


VOS_UINT32 MMA_IsNorwayNetcomImsiIllegal()
{
    VOS_CHAR                            acTmpImsi[16] = {0};
    VOS_CHAR                            *pcNorwayNetcomImsi = "24202";

    /*����NETCOM������IMSI range: 24202xy ,Where x = 0-9 and y = 0-3,����xy = 59,86����ֻҪ�ж�
    IMSI������ź͹��Һ�Ϊ24202,����y�ķ�ΧΪ0-3�Ϳ�����,��Ϊ
    x�ķ�Χ��0-9,�����ⷶΧ,���Բ����ж�.
    */
    MMA_ImsiToImsiStr(acTmpImsi);

    if (0 == VOS_MemCmp(acTmpImsi, pcNorwayNetcomImsi, 5))
    {
        if (((acTmpImsi[5] == 0x35) && (acTmpImsi[6] == 0x39) )
         || ((acTmpImsi[5] == 0x38) && (acTmpImsi[6] == 0x36) ) )
        {
            return VOS_FALSE;
        }

        if ((acTmpImsi[6] >= 0x30) && (acTmpImsi[6] <= 0x33))
        {
            return VOS_FALSE;
        }

    }

    return VOS_TRUE;

}


VOS_UINT32 MMA_IsMexicoTelcelIllegal()
{
    VOS_CHAR                            acTmpImsi[16] = {0};
    VOS_CHAR                            *pcMexicoTelcelImsi="334020";

    /* ī����telce PLMN ID 334020 */
    MMA_ImsiToImsiStr(acTmpImsi);
    if (0 == VOS_MemCmp(acTmpImsi, pcMexicoTelcelImsi, 6))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 MMA_IsDominicaTelcelIllegal()
{
    VOS_CHAR                            acTmpImsi[16] = {0};
    VOS_CHAR                            *pcDominicaTelcelImsi1="37002";
    VOS_CHAR                            *pcDominicaTelcelImsi2="42502";
    VOS_CHAR                            *pcDominicaTelcelImsi3="338070";
    VOS_INT32                           iImsiCmpRslt1,iImsiCmpRslt2,iImsiCmpRslt3;

    /*dominica permanet SIM Lock 37002, 42502, 338070*/
    MMA_ImsiToImsiStr(acTmpImsi);
    iImsiCmpRslt1 = VOS_MemCmp(acTmpImsi, pcDominicaTelcelImsi1, 5);
    iImsiCmpRslt2 = VOS_MemCmp(acTmpImsi, pcDominicaTelcelImsi2, 5);
    iImsiCmpRslt3 = VOS_MemCmp(acTmpImsi, pcDominicaTelcelImsi3, 6);
    if ((0 == iImsiCmpRslt1)
      ||(0 == iImsiCmpRslt2)
      ||(0 == iImsiCmpRslt3))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 Mma_VerifyPhonePersonalization(VOS_VOID)
{
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enVerifySimlockResult;
    SC_ERROR_CODE_ENUM_UINT32           enScResult;
    VOS_UINT32                          ulResult;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId  = VOS_GetModemIDFromPid(WUEPS_PID_MMA);
    enScResult = SC_PERS_VerifySimLock(&enVerifySimlockResult, enModemId);

    /* ����SC�ӿڽ�������У�飬������ִ��ʧ�ܣ�����SIM������������ */
    if (SC_ERROR_CODE_NO_ERROR != enScResult)
    {
        return VOS_TRUE;
    }

    /* ����У��������SIM���Ƿ��� */
    switch (enVerifySimlockResult)
    {
        case SC_VERIFY_SIMLOCK_RESULT_READY:
            ulResult = VOS_FALSE;
            break;

        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN:
        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PUK:
        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN:
        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PUK:
        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN:
        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PUK:
            ulResult = VOS_TRUE;
            break;

        default:
            /* ��Чֵ������SIM���������д��� */
            ulResult = VOS_TRUE;
            break;
    }

    return ulResult;
}
VOS_BOOL Mma_IsImsiLocked(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    MMA_CUSTOM_CARDLOCK_OPERATOR_STRU   stCardLockOp;
    MMA_CUSTOM_CARDLOCK_PERM_STRU       stCardPerm;
    VOS_CHAR                            acTmpImsi[16] = {0};
    VOS_CHAR                            *pcLabImsi1="00101";
    VOS_CHAR                            *pcLabImsi2="00102";
    VOS_CHAR                            *pcLabImsi3="00201";
    VOS_INT32                           iImsiCmpRslt1,iImsiCmpRslt2,iImsiCmpRslt3;
    VOS_UINT32                          ulChkRslt;
    VOS_UINT32                          ulLength;

    ulLength        = 0;
    stCardLockOp.ucStatus           = VOS_FALSE;
    stCardLockOp.enCardLockOperator = MMA_CUSTOM_CARDLOCK_BUTT;

    stCardPerm.ucStatus             = VOS_FALSE;
    stCardPerm.ucCardLockPerm       = VOS_FALSE;

    /*��IMSI��ֵΪ00101,00102,00201ʱ�������������ж�*/
    (VOS_VOID)VOS_MemSet(acTmpImsi, 16, 0);
    MMA_ImsiToImsiStr(acTmpImsi);

    iImsiCmpRslt1 = VOS_MemCmp(acTmpImsi, pcLabImsi1, 5);
    iImsiCmpRslt2 = VOS_MemCmp(acTmpImsi, pcLabImsi2, 5);
    iImsiCmpRslt3 = VOS_MemCmp(acTmpImsi, pcLabImsi3, 5);

    if ((0 == iImsiCmpRslt1)
      ||(0 == iImsiCmpRslt2)
      ||(0 == iImsiCmpRslt3))
    {
        return VOS_FALSE;
    }

    /*
    ���ݲ�Ʒ�ߵ�Ҫ�����CardLock���NV���ȡʧ�ܣ�����ΪӦ���ǿ���������
    ʣ�����Ϊ0(����������ٳ���)
    */
    if (VOS_OK!= MMA_GetCardLockCfgData())
    {
        g_MmaNewValue.stCardLockStatus.ulStatus = VOS_TRUE;
        g_MmaNewValue.stCardLockStatus.enCardlockStatus = TAF_OPERATOR_LOCK_LOCKED;
        g_MmaNewValue.stCardLockStatus.ulRemainUnlockTimes = 0;
        return VOS_TRUE;
    }


    if (VOS_TRUE != g_MmaNewValue.stCardLockStatus.ulStatus)
    {
        return VOS_FALSE;
    }

    (VOS_VOID)NV_GetLength(en_NV_Item_HUAWEI_CARDLOCK_OPERATOR_EXT, &ulLength);

    ulResult = NV_Read(en_NV_Item_HUAWEI_CARDLOCK_OPERATOR_EXT,
                       &stCardLockOp,
                       ulLength);
    if (NV_OK != ulResult)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mma_IsImsiLocked:WARNING: Read en_NV_Item_HUAWEI_CARDLOCK_PERM_EXT Err");
        return VOS_FALSE;
    }

    if (VOS_TRUE == stCardLockOp.ucStatus)
    {
        switch (stCardLockOp.enCardLockOperator)
        {
            case MMA_CUSTOM_CARDLOCK_EGYPT_VDF:
                ulChkRslt = MMA_IsEygptVdfImsiIllegal();
                break;

            case MMA_CUSTOM_CARDLOCK_NORWAY_NETCOM:
                ulChkRslt = MMA_IsNorwayNetcomImsiIllegal();
                break;

            case MMA_CUSTOM_CARDLOCK_MEXICO_TELCEL:
                ulChkRslt = MMA_IsMexicoTelcelIllegal();
                break;

            case MMA_CUSTOM_CARDLOCK_DOMINICA_TELCEL:
                ulChkRslt = MMA_IsDominicaTelcelIllegal();
                break;

            default:
                ulChkRslt = MMA_IsImsiIllegal();
                break;
        }

        if (VOS_TRUE == ulChkRslt)
        {
            /*�����������ѡ���򽫿���Ϊ��������״̬*/
            (VOS_VOID)NV_GetLength(en_NV_Item_HUAWEI_CARDLOCK_PERM_EXT, &ulLength);

            ulResult = NV_Read(en_NV_Item_HUAWEI_CARDLOCK_PERM_EXT,
                               &stCardPerm,
                               ulLength);
            if ((NV_OK == ulResult)
              &&(VOS_TRUE == stCardPerm.ucStatus)
              &&(VOS_TRUE == stCardPerm.ucCardLockPerm))
            {
                g_MmaNewValue.stCardLockStatus.enCardlockStatus = TAF_OPERATOR_LOCK_LOCKED;
                ulResult = NV_Write(en_NV_Item_CardlockStatus,
                                    &g_MmaNewValue.stCardLockStatus,
                                    sizeof(g_MmaNewValue.stCardLockStatus));
                if (NV_OK != ulResult)
                {
                     MMA_ERRORLOG("Mma_IsImsiLocked:ERROR:write en_NV_Item_Me_Personalisation_Active_Flag Fail.");
                     return VOS_TRUE;
                }

                /*lint -e774*/
                ulResult = NV_SpecialNvIdBackup(en_NV_Item_CardlockStatus,
                                                &g_MmaNewValue.stCardLockStatus,
                                                sizeof(g_MmaNewValue.stCardLockStatus));

                if (NV_OK != ulResult)
                {
                    MMA_ERRORLOG("Mma_IsImsiLocked:ERROR:write special en_NV_Item_CardlockStatus Fail.");
                    return VOS_TRUE;
                }
                /*lint +e774*/

            }
            else
            {
                /*���֮ǰ�Ѿ������ˣ�����cardlock��Ҫ�󣬲���Ҫ��У��*/
                /*����û�������һ��������ȷ֮�����뽫�ᱻ�����������
                �û���������ʹ�ø����ݿ�����ʹ��������һ�ŷ�ָ������
                ��ʱҲ������Ҫ�����������롣*/
                if (TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE == g_MmaNewValue.stCardLockStatus.enCardlockStatus )
                {
                    return VOS_FALSE;
                }
            }

        }
    }
    else
    {
        /*���֮ǰ�Ѿ������ˣ�����cardlock��Ҫ�󣬲���Ҫ��У��*/
        /*����û�������һ��������ȷ֮�����뽫�ᱻ�����������
        �û���������ʹ�ø����ݿ�����ʹ��������һ�ŷ�ָ������
        ��ʱҲ������Ҫ�����������롣*/
        if (TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE == g_MmaNewValue.stCardLockStatus.enCardlockStatus )
        {
            return VOS_FALSE;
        }
        ulChkRslt = MMA_IsImsiIllegal();
    }

    return ulChkRslt;


}

/*<==A32D06630*/

VOS_UINT32 MMA_CheckMePersonalisationStatus()
{
    VOS_UINT32 ulResult = VOS_FALSE;

    if (MMA_QUICK_START_ENABLE == gstMmaValue.ulQuickStartFlg)
    {
        MMA_INFOLOG("MMA_CheckMePersonalisationStatus Info:Usim status is ROMSIM!");
        return VOS_FALSE;
    }

    /*���������sim�����򲻽�����������У��*/
    if (VOS_TRUE == USIMM_VsimIsActive())
    {
        MMA_INFOLOG("MMA_CheckMePersonalisationStatus Info:Is virtual sim!");
        return VOS_FALSE;
    }

    if (g_stMmaMePersonalisationStatus.SimLockStatus == MMA_SIM_IS_UNLOCK)
    {
        /* �ж��������ϲ�Ӧ�ã��Ӷ�������̬�ֱ����AP-Modem�ͷ�AP-Modem����������У�� */
        if (SYSTEM_APP_ANDROID == g_usMmaAppConfigSupportType)
        {
            /* AP-Modemģʽ�£���ȡ��ǰ�Ƿ����� */
            ulResult = Mma_VerifyPhonePersonalization();
        }
        else
        {
            ulResult = Mma_IsImsiLocked();
        }

        if (VOS_FALSE == ulResult)
        {
            g_stMmaMePersonalisationStatus.SimLockStatus = MMA_SIM_LOCK_IS_VERIFY;
            MMA_INFOLOG("MMA_CheckMePersonalisationStatus Info:Usim is not locked!");
        }
        else
        {
            g_stMmaMePersonalisationStatus.SimLockStatus = (VOS_UINT8)ulResult;
            MMA_INFOLOG("MMA_CheckMePersonalisationStatus Info:Usim is locked!");
        }

    }
    else if (g_stMmaMePersonalisationStatus.SimLockStatus == MMA_SIM_IS_LOCK)
    {
        MMA_INFOLOG("MMA_CheckMePersonalisationStatus Info:Usim is locked!");
        return VOS_TRUE;
    }
    else
    {

    }

    return ulResult;

}
VOS_VOID MMA_PhoneStopEventReport ( VOS_UINT16 usClientID, VOS_UINT32 ulOpID, VOS_UINT32 ulEventType )
{
    TAF_PHONE_EVENT_INFO_STRU   *pEvent;

    pEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pEvent)
    {
        MMA_ERRORLOG("MMA_PhoneStopEventReport:ERROR:ALLOC MEMORY ERROR!");
        return;
    }
    PS_MEM_SET(pEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));
    /* ����ṹ������־ */
    pEvent->OP_CsServiceStatus    = 0;
    pEvent->OP_PhoneError         = 0;
    pEvent->OP_PlmnReselMode      = 0;
    pEvent->OP_PsServiceStatus    = 0;
    pEvent->OP_RegPlmn            = 0;
    pEvent->OP_Spare              = 0;
    /*�����ϱ��¼�ѡ���ʼ��*/
    pEvent->OP_CurRegSta          = 0;
    pEvent->OP_Rssi               = 0;
    pEvent->OP_BatteryPower       = 0;
    pEvent->OP_Pin                = 0;

    /* ��д�ϱ��¼����� */
    /* ������� */
    pEvent->ClientId = usClientID;
    pEvent->OpId = (VOS_UINT8)ulOpID;         /*д��ulOpId*/
    pEvent->PhoneEvent = (TAF_PHONE_EVENT)ulEventType;

    /* ���õ绰�����ϱ����� */
    MN_PH_SendMsg(pEvent->ClientId,(VOS_UINT8*)pEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    PS_MEM_FREE(WUEPS_PID_MMA, pEvent);

    return;
}





VOS_VOID  MMA_PhonePlmnList()
{
    VOS_UINT8  ucError = TAF_ERR_NO_ERROR;

    ucError = MMA_CheckUsimStatusForPlmnSel();
    if(TAF_ERR_NO_ERROR != ucError)
    {
        MMA_WARNINGLOG("MMA_PhonePlmnList():WARNING:UsimStatus Error!");
        /*������*/
        TAF_MMA_PlmnListErrorReport(ucError);
        return;
    }



    /* �����C+Lģʽ����ʱ��AT������plmn list���� ����ظ�ʧ��,���б���  */
    if (VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())
    {
        TAF_MMA_PlmnListErrorReport(TAF_ERR_ERROR);

        return;
    }

    /* ����Status������������PLMN����*/
    (VOS_VOID)Sta_PlmnList();

    return;
}

/* delete MMA_PlmnListAbort*/


VOS_VOID MMA_PhonePlmnUserSel (
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PLMN_ID_STRU                    Plmn,
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enPhRat,
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    TAF_PLMN_RESEL_MODE_TYPE            ReselMode
)
{
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enPrioSelRat;
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */

    enPrioSelRat = MN_MMA_GetUserPlmnSelPrioRat(enPhRat, Plmn);

    Sta_PlmnSelect(OpId, Plmn, enPrioSelRat, ReselMode);


    return;
}



VOS_VOID MMA_HandleEventError(VOS_UINT16   ClientId,
                              VOS_UINT8          OpId,
                              VOS_UINT8       ucError,
                              TAF_PHONE_EVENT PhEvent)
{
    TAF_PHONE_EVENT_INFO_STRU *pstPhoneEvent;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_HandleEventError:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    if (TAF_ERR_NO_ERROR != ucError)
    {
        /*��ʼ�������¼�ѡ��*/
        MMA_InitEventInfoOP(pstPhoneEvent);
        /*�������ϱ��¼���1*/
        pstPhoneEvent->OP_PhoneError = VOS_TRUE;

        pstPhoneEvent->PhoneEvent    = PhEvent;
        pstPhoneEvent->ClientId      = ClientId;
        pstPhoneEvent->OpId          = OpId;
        pstPhoneEvent->PhoneError    = ucError;

        /*�����ǰTiȫ�ֱ����ж�Ӧ�ļ�¼*/
        MMA_CleanTiVar(ClientId, OpId);

        /* ���õ绰�����ϱ����� */
        MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    }
    PS_MEM_FREE(WUEPS_PID_MMA,pstPhoneEvent);
    return;
}



VOS_VOID MMA_PhoneGetImsi(VOS_UINT16           ClientId,
                          VOS_UINT8                  OpId)
{
    TAF_UINT16                          usErrorCode;
    TAF_PH_IMSI_STRU                    stImsiTmp;
    VOS_UINT8                          *pPara = VOS_NULL_PTR;

    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;

    pucImsi = TAF_SDC_GetSimImsi();

    /*��ѯUSIM״̬*/
    if ( MMA_ERROR == MMA_PhoneUsimReady(ClientId, OpId, TAF_PH_IMSI_ID_PARA) )
    {
        MMA_WARNINGLOG("MMA_PhoneGetImsi():WARNING:NO USIM");
        return;
    }

    switch ( MMA_CheckPin1SatusSimple() )
    {
        case MMA_ENABLE_PIN1_NONEED:
        case MMA_NONEED_PIN1:
            usErrorCode = TAF_ERR_NO_ERROR;
            break;
        case MMA_NEED_PIN1:
            usErrorCode = TAF_ERR_NEED_PIN1;
            break;
        case MMA_NEED_PUK1:
            usErrorCode = TAF_ERR_NEED_PUK1;
            break;
        case MMA_PUK1_REMAINS_ZERO:
            usErrorCode = TAF_ERR_USIM_SIM_INVALIDATION;
            break;
        case MMA_PIN1_STATUS_FAIL:
            usErrorCode = TAF_ERR_UNSPECIFIED_ERROR;
            break;
        default:
            usErrorCode = TAF_ERR_UNSPECIFIED_ERROR;
            break;
    }
    if ( TAF_ERR_NO_ERROR != usErrorCode )
    {
        /*������*/
        MMA_ReportParaQueryError(ClientId, OpId,
                                 usErrorCode,
                                 TAF_PH_IMSI_ID_PARA);
        return;
    }

    if (USIMM_API_SUCCESS != NAS_USIMMAPI_GetCardIMSI(pucImsi))
    {
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_ERROR,
                                 TAF_PH_IMSI_ID_PARA);
        return;
    }


    if (pucImsi[0]>8)
    {
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_ERROR,
                                 TAF_PH_IMSI_ID_PARA);
        return;
    }
    MMA_ImsiBcd2Ascii(  (VOS_UINT8)(pucImsi[0] * 2),
                      &pucImsi[1],
                        stImsiTmp.aucImsi
                     );


    pPara = (VOS_UINT8 *)stImsiTmp.aucImsi;
    /*ʹ�������ϱ����������ݴ���TAFm*/
    MMA_ParaQueryReport(ClientId, OpId, TAF_PH_IMSI_ID_PARA, TAF_ERR_NO_ERROR,pPara);
    return;
}
VOS_UINT32 MMA_PhoneUsimReady( VOS_UINT16           ClientId,
                               VOS_UINT8                  OpId,
                               TAF_PARA_TYPE     QueryType )
{
    VOS_UINT8               ucUsimStatus;


    ucUsimStatus = USIMM_CARD_SERVIC_ABSENT;

    /*��ȡ��ǰUSIM״̬*/
    if  ( MMA_SUCCESS != MMA_GetUsimStatusFromUsim(&ucUsimStatus, VOS_NULL_PTR))
    {
        MMA_WARNINGLOG("MMA_PhoneUsimReady():WORNING:Invoke Taf_UsimmGetStatus fail.");
        /*CLIENTIDΪ��Чֵʱ,���඼����Ч*/
        if ( MMA_CLIENTID_NONE != ClientId )
        {
            MMA_ReportParaQueryError(ClientId, OpId,
                                     TAF_ERR_SIM_BUSY,
                                     QueryType);
        }
        return MMA_ERROR;
    }

    /*������USIMAPI��ֵ��Ϊ0,���ʾ�д���*/
    if ( USIMM_CARD_SERVIC_ABSENT == ucUsimStatus )
    {
        /*��ӡ��Ϣ*/
        MMA_NORMAILLOG("MMA_PhoneUsimReady():NORMAL:USIM status is Not Ready.");
        /*���ɴ������ݰ�,*/
        /*CLIENTIDΪ��Чֵʱ,���඼����Ч*/
        if ( MMA_CLIENTID_NONE != ClientId )
        {
            MMA_ReportParaQueryError(ClientId, OpId,
                                     TAF_ERR_USIM_SIM_CARD_NOTEXIST,
                                     QueryType);
        }
        /*���ػ�ȡ������Ч*/
        return MMA_ERROR;
    }

    return MMA_SUCCESS;
}





VOS_VOID TAF_MMA_SndStkLocationInfoInd (VOS_VOID)
{
    NAS_STK_LOCATION_INFO_IND_STRU     *pstMsg        = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;
    TAF_SDC_PLMN_ID_STRU               *pstTempPlmnID = VOS_NULL_PTR;

    /* ���֧��SVLTE���Ǹ�modem��֧��CS����ֱ���˳�������STK���͸���Ϣ */
    if (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
    {
       if (VOS_TRUE != TAF_MMA_IsCsServDomainAvail(gstMmaValue.stSetMsClass.MsClassType))
       {
           return;
       }
    }

    /* �����ڴ� */
    ulLength = sizeof(NAS_STK_LOCATION_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (NAS_STK_LOCATION_INFO_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("TAF_MMA_SndStkLocationInfoInd: Alloc Msg");
        return;
    }

    PS_MEM_SET(&(pstMsg->stSysInfo), 0, sizeof(NAS_STK_SYS_INFO_STRU));

    PS_MEM_SET(&(pstMsg->stServiceStatus), 0, sizeof(NAS_STK_SERVICE_STATUS_INFO_STRU));

    /* ��д����Ϣ���� */
    pstMsg->ulMsgName            = ID_NAS_STK_LOCATION_INFO_IND;

    pstMsg->ulReceiverPid        = NAS_GetOamReceivePid(MAPS_STK_PID);

    pstMsg->stSysInfo.enRat      = TAF_MMA_ConvertMmaRatToStkRat(TAF_SDC_GetSysMode());

    pstMsg->stSysInfo.ulCellId   = TAF_SDC_GetCurrCampCellId();

    pstMsg->stSysInfo.usLac      = TAF_SDC_GetCurrCampLac();

    pstTempPlmnID                = TAF_SDC_GetCurrCampPlmnId();
    pstMsg->stSysInfo.stPlmn.Mcc = pstTempPlmnID->ulMcc;
    pstMsg->stSysInfo.stPlmn.Mnc = pstTempPlmnID->ulMnc;

    pstMsg->stSysInfo.enUtranMode = NAS_STK_UTRAN_MODE_BUTT;
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    if (TAF_MMA_RAT_WCDMA == pstMsg->stSysInfo.enRat)
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    {
        pstMsg->stSysInfo.enUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();
    }

    pstMsg->stServiceStatus.enCsServiceStatus = TAF_SDC_GetCsServiceStatus();

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMA, pstMsg))
    {
        MN_ERR_LOG("TAF_MMA_SndStkLocationInfoInd: PS_SEND_MSG ERROR");
    }

    return;

}

#if (FEATURE_MULTI_MODEM == FEATURE_ON)


VOS_VOID TAF_MMA_SndMtcEplmnInfoInd(
    MSCC_MMA_EPLMN_INFO_IND_STRU        *pstEplmnInfoIndMsg
)
{
    MMA_MTC_EPLMN_INFO_IND_STRU        *pstMmaSndMtcEplmnInfoInd = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    pstMmaSndMtcEplmnInfoInd = (MMA_MTC_EPLMN_INFO_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                              WUEPS_PID_MMA,
                                              sizeof(MMA_MTC_EPLMN_INFO_IND_STRU));

    if( VOS_NULL_PTR == pstMmaSndMtcEplmnInfoInd )
    {
        MN_ERR_LOG("TAF_MMA_SndMtcEplmnInfoInd: Alloc Msg Failed!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMmaSndMtcEplmnInfoInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_MTC_EPLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMmaSndMtcEplmnInfoInd->stMsgHeader.ulReceiverPid   = UEPS_PID_MTC;
    pstMmaSndMtcEplmnInfoInd->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstMmaSndMtcEplmnInfoInd->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMmaSndMtcEplmnInfoInd->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMmaSndMtcEplmnInfoInd->stMsgHeader.ulMsgName       = ID_MMA_MTC_EPLMN_INFO_IND;

    pstMmaSndMtcEplmnInfoInd->stEplmnInfo.ucEquPlmnNum    = pstEplmnInfoIndMsg->stEplmnInfo.ucEquPlmnNum;
    PS_MEM_CPY(pstMmaSndMtcEplmnInfoInd->stEplmnInfo.astEquPlmnAddr, pstEplmnInfoIndMsg->stEplmnInfo.astEquPlmnAddr,
               sizeof(pstMmaSndMtcEplmnInfoInd->stEplmnInfo.astEquPlmnAddr));

    ulResult = PS_SEND_MSG(WUEPS_PID_MMA, pstMmaSndMtcEplmnInfoInd);

    if( VOS_OK != ulResult )
    {
        MN_ERR_LOG("TAF_MMA_SndMtcEplmnInfoInd: Send Msg Failed!");
    }

    return;
}


#endif


VOS_UINT32 TAF_MMA_IsCellChange(MSCC_MMA_3GPP_SYS_INFO_IND_STRU *pstCurrSysInfo)
{
    TAF_SDC_PLMN_ID_STRU               *pstOldPlmnId = VOS_NULL_PTR;
    VOS_UINT16                          stOldLac;
    VOS_UINT8                           stOldRac;
    VOS_UINT32                          stOldCellId;

    pstOldPlmnId = TAF_SDC_GetCurrCampPlmnId();
    stOldLac     = TAF_SDC_GetCurrCampLac();
    stOldRac     = TAF_SDC_GetCurrCampRac();
    stOldCellId  = TAF_SDC_GetCurrCampCellId();

    if ((pstOldPlmnId->ulMcc != pstCurrSysInfo->stPlmnId.ulMcc)
     || (pstOldPlmnId->ulMnc != pstCurrSysInfo->stPlmnId.ulMnc)
     || (stOldLac            != pstCurrSysInfo->usLac)
     || (stOldRac            != pstCurrSysInfo->ucRac)
     || (stOldCellId         != pstCurrSysInfo->stCellId.aulCellId[0]))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsAppNetworkInfoCellChange
 ��������  : �ж�AppNetworkInfo��NetworkInfoС����Ϣ�Ƿ�仯
 �������  : AppNetworkInfo�е�С����Ϣ

 �������  :
 �� �� ֵ  : С����Ϣ�Ƿ����仯
 ���ú���  :
 ��������  :

 �޸���ʷ    :
1.��    ��   : 2015��02��11��
  ��    ��   : l00305157
  �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsAppNetworkInfoCellChange(
    TAF_SDC_SERVICED_PLMN_INFO_STRU  *pstAppServPlmnInfo
)
{
    TAF_SDC_PLMN_ID_STRU               *pstOldPlmnId = VOS_NULL_PTR;
    VOS_UINT16                          usOldLac;
    VOS_UINT8                           ucOldRac;
    VOS_UINT32                          ulOldCellId;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enOldSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enOldSysSubMode;

    TAF_SDC_PLMN_ID_STRU               *pstAppPlmnId = VOS_NULL_PTR;
    VOS_UINT16                          usAppLac;
    VOS_UINT8                           ucAppLac;
    VOS_UINT32                          ulAppCellId;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enAppSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enAppSysSubMode;

    pstOldPlmnId = TAF_SDC_GetCurrCampPlmnId();
    usOldLac     = TAF_SDC_GetCurrCampLac();
    ucOldRac     = TAF_SDC_GetCurrCampRac();
    ulOldCellId  = TAF_SDC_GetCurrCampCellId();
    enOldSysMode = TAF_SDC_GetSysMode();
    enOldSysSubMode = TAF_SDC_GetSysSubMode();

    pstAppPlmnId = &(pstAppServPlmnInfo->stServicePlmnId);
    usAppLac     = pstAppServPlmnInfo->usServiceLac;
    ucAppLac     = pstAppServPlmnInfo->ucServiceRac;
    ulAppCellId  = pstAppServPlmnInfo->ulServiceCellId;
    enAppSysMode = pstAppServPlmnInfo->enServiceSysMode;
    enAppSysSubMode = pstAppServPlmnInfo->enServiceSysSubMode;


    if ((pstOldPlmnId->ulMcc != pstAppPlmnId->ulMcc)
     || (pstOldPlmnId->ulMnc != pstAppPlmnId->ulMnc)
     || (usOldLac            != usAppLac)
     || (ucOldRac            != ucAppLac)
     || (ulOldCellId         != ulAppCellId)
     || (enOldSysMode        != enAppSysMode)
     || (enOldSysSubMode     != enAppSysSubMode))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID TAF_MMA_ProcMsccSysInfoInNormalService(
    VOS_UINT32                          ulCellChangeFlg
)
{

    if ((VOS_TRUE == NAS_MMA_CellIdChangeForStkLocSta())
     || (TAF_REPORT_SRVSTA_NORMAL_SERVICE != g_stMmsStkLocStaSysInfo.enServiceStatus))
    {
        NAS_MMA_ReportLociStatus();
    }


    /* �յ�ϵͳ��Ϣʱ���ϱ�CREG��CGREG/CEREG������ע�������ϱ� */

    return;
}


VOS_UINT32 TAF_MMA_IsCGIInfoChanged(
    TAF_SDC_SYS_INFO_STRU              *pstOldSysInfo,
    TAF_SDC_SYS_INFO_STRU              *pstNewSysInfo
)
{
    /* ����Plmn�� lac,cellid,access type��ϵͳ��ģʽ�Ƿ��б仯 */
    if ((pstOldSysInfo->st3gppSysInfo.stPlmnId.ulMcc  != pstNewSysInfo->st3gppSysInfo.stPlmnId.ulMcc)
     || (pstOldSysInfo->st3gppSysInfo.stPlmnId.ulMnc  != pstNewSysInfo->st3gppSysInfo.stPlmnId.ulMnc)
     || (pstOldSysInfo->enSysMode       != pstNewSysInfo->enSysMode)
     || (pstOldSysInfo->st3gppSysInfo.usLac           != pstNewSysInfo->st3gppSysInfo.usLac)
     || (pstOldSysInfo->st3gppSysInfo.ulCellId        != pstNewSysInfo->st3gppSysInfo.ulCellId)
     || (pstOldSysInfo->st3gppSysInfo.ucRoamFlag      != pstNewSysInfo->st3gppSysInfo.ucRoamFlag)
     || (pstOldSysInfo->st3gppSysInfo.enLmmAccessType != pstNewSysInfo->st3gppSysInfo.enLmmAccessType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_VOID TAF_MMA_Proc3gppMsccSysInfoIndInGulMode(
    MSCC_MMA_3GPP_SYS_INFO_IND_STRU    *pstMsccSysInfo
)
{
    VOS_UINT32                                              ulCellChangeFlg;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enCsServiceStauts;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enPsServiceStatus;
    NAS_MML_MISCELLANEOUS_CFG_INFO_STRU                    *pstMiscellaneousCfgInfo = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    VOS_UINT32                                              ulIsClInterWorkFlg;
#endif

#if ( (FEATURE_ON == FEATURE_IMS) || (FEATURE_ON == FEATURE_CL_INTERWORK) )

    TAF_SDC_SYS_INFO_STRU                                   stOldSysInfo;
    TAF_SDC_SYS_INFO_STRU                                  *pstCurSysInfo     = VOS_NULL_PTR;


    PS_MEM_SET(&stOldSysInfo, 0, sizeof(TAF_SDC_SYS_INFO_STRU));

    pstCurSysInfo = TAF_SDC_GetSysInfo();

    PS_MEM_CPY(&stOldSysInfo, pstCurSysInfo, sizeof(TAF_SDC_SYS_INFO_STRU));

#endif

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    ulIsClInterWorkFlg = TAF_MMA_IsPowerOnCLInterWork();
#endif



    pstMiscellaneousCfgInfo = NAS_MML_GetMiscellaneousCfgInfo();

    enCsServiceStauts  = TAF_SDC_GetCsServiceStatus();
    enPsServiceStatus  = TAF_SDC_GetPsServiceStatus();

    /* �����no rf��־����ֱ�Ӳ����� */
#if (FEATURE_ON == FEATURE_DSDS)
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-18, begin */
    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        return;
    }
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-18, end */
#endif

    TAF_MMA_PlmnIdReport((TAF_PLMN_ID_STRU*)&(pstMsccSysInfo->stPlmnId));

    /* ����Ƿ���Ҫ�ϱ�^MODE */
    Mma_ModeChgReport((TAF_SDC_SYS_MODE_ENUM_UINT8)pstMsccSysInfo->enCurNetWork, pstMsccSysInfo->ucSysSubMode);

    /* ֻ��С��ID�ı�ʱ�����ܸ���RAT���͡�������������SYSINFO��ѯʱʹ�� */
    TAF_SDC_SetSysMode(pstMsccSysInfo->enCurNetWork);
    TAF_SDC_SetSysSubMode(pstMsccSysInfo->ucSysSubMode);

    TAF_SDC_SetRoamFlag(pstMsccSysInfo->ucRoamFlag);

    ulCellChangeFlg = TAF_MMA_IsCellChange(pstMsccSysInfo);

    TAF_SDC_SetCsAttachAllowFlg(pstMsccSysInfo->ucCsAttachAllowFlag);
    TAF_SDC_SetPsAttachAllowFlg(pstMsccSysInfo->ucPsAttachAllowFlag);

    /*���µ�ǰȫ�ֱ����е�PLMN*/
    TAF_SDC_SetCurrCampPlmnId((TAF_SDC_PLMN_ID_STRU *)&pstMsccSysInfo->stPlmnId);
    TAF_SDC_SetCurrCampLac(pstMsccSysInfo->usLac);
    TAF_SDC_SetCurrCampRac(pstMsccSysInfo->ucRac);
    TAF_SDC_SetCurrCampCellId(pstMsccSysInfo->stCellId.aulCellId[0]);

    TAF_SDC_SetCurrLmmAccessType(pstMsccSysInfo->enLmmAccessType);

    TAF_SDC_SetAppLteArfcn(pstMsccSysInfo->ulArfcn);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    TAF_MMA_SndMtcSysInfo(pstMsccSysInfo->ucIsFobbiddenPlmnFlag,
                          pstMsccSysInfo->ucPsSupportFlg);
#endif

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

    /* פ��ʱ�ж�CGI��Ϣ�����ı�ʱ֪ͨCMMCAģ�� */
    if ( (VOS_TRUE == TAF_MMA_IsCGIInfoChanged(&stOldSysInfo, TAF_SDC_GetSysInfo()))
      && (VOS_TRUE == ulIsClInterWorkFlg) )
    {
        /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-21, begin */
        TAF_MMA_SndCmmcaSysInfoInd(pstMsccSysInfo->stPlmnId.ulMcc,
                          pstMsccSysInfo->stPlmnId.ulMnc,
                          pstMsccSysInfo->ulArfcn,
                          pstMsccSysInfo->enPrioClass);
        /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-21, end */
    }
#endif

    if ( SYSTEM_APP_WEBUI == pstMiscellaneousCfgInfo->usAppConfigSupportFlg)
    {
        /* �ж��Ƿ���Ҫ��Ӧ�õ�����״̬���и��� */
        MN_PH_AppRoamStatusRpt();
    }



    if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enPsServiceStatus)
     || (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStauts))
    {
        TAF_MMA_ProcMsccSysInfoInNormalService(ulCellChangeFlg);
    }

    TAF_MMA_SndStkLocationInfoInd();

    /* ��ǰ��Lģ����֪ͨATģ�鵱ǰ�Ľ��뼼�� */
    if (NAS_MML_NET_RAT_TYPE_LTE == pstMsccSysInfo->enCurNetWork)
    {
        /*��L�²�ʹ�ø�ȫ�ֱ�����¼�����ֹ�������ճɷǽ����ֹ
        �ص�GU��ʱ��������ֹ�����ı�MSCC�������ϱ�*/
        TAF_MMA_InitCellAcInfo();
    }

    /* ��AppServPlmnInfo���µĴ���:�����������ܻ����APP�����Ϣ���������Ҫ�õ�APP����Ϣ����ע��ʱ�� */
    TAF_MMA_ProcAppServPlmnInfo_SysInfoInd(pstMsccSysInfo);


#if (FEATURE_ON == FEATURE_BASTET)
    if(VOS_TRUE == TAF_SDC_GetBastetSupportFlag())
    {
        TAF_MMA_SndBastetRatModeInd(TAF_SDC_GetSysMode(), NAS_UTRANCTRL_GetCurrUtranMode());
    }
#endif

#if (FEATURE_ON == FEATURE_IMS)
    if (VOS_FALSE == TAF_SDC_GetImsSupportFlag())
    {
        return;
    }

    /* ���뼼���仯ʱ֪ͨSPM,����SPM������ */
    if (TAF_SDC_GetSysMode() != stOldSysInfo.enSysMode)
    {
        TAF_MMA_SndSpmRatChangeNotify();
    }

#endif

    return;
}


VOS_UINT32 TAF_MMA_Proc3gppMsccSysInfoIndInClMode(
    MSCC_MMA_3GPP_SYS_INFO_IND_STRU    *pstMsccSysInfo
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode;
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncUpdateSysModSrvRegSta;

    pFuncUpdateSysModSrvRegSta = VOS_NULL_PTR;
    enSysMode = TAF_SDC_SYS_MODE_BUTT;
    enSubMode = TAF_SDC_SYS_SUBMODE_BUTT;

    if (VOS_FALSE == TAF_SDC_Get3GppRfAvailFlag())
    {
        return VOS_TRUE;
    }

    TAF_SDC_SetRoamFlag(pstMsccSysInfo->ucRoamFlag);

    /* to calc the sysmode and submode */
    TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_LTE_NETWORK_EXIST, &enSysMode, &enSubMode, &pFuncUpdateSysModSrvRegSta);

    Mma_ModeChgReport(enSysMode, enSubMode);

    TAF_SDC_SetSysMode(enSysMode);
    TAF_SDC_SetSysSubMode(enSubMode);

    /* Added by h00313353 for Iteration 17, 2015-8-13, begin */
    TAF_MMA_PlmnIdReport((TAF_PLMN_ID_STRU*)&(pstMsccSysInfo->stPlmnId));
    /* Added by h00313353 for Iteration 17, 2015-8-13, end */

    /* TO DO: Ŀǰ������������Щ��Ϣ�������������Ҫ�����ϱ��Ļ���������� */

    /*���µ�ǰȫ�ֱ����е�PLMN*/
    TAF_SDC_SetCurrCampPlmnId((TAF_SDC_PLMN_ID_STRU *)&pstMsccSysInfo->stPlmnId);

    TAF_SDC_SetCurrCampLac(pstMsccSysInfo->usLac);

    TAF_SDC_SetCurrCampRac(pstMsccSysInfo->ucRac);

    TAF_SDC_SetCurrCampCellId(pstMsccSysInfo->stCellId.aulCellId[0]);

    TAF_SDC_SetCurrLmmAccessType(pstMsccSysInfo->enLmmAccessType);


    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_Rcv3gppMsccSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_3GPP_SYS_INFO_IND_STRU    *pstMsccSysInfo = VOS_NULL_PTR;

    pstMsccSysInfo = (MSCC_MMA_3GPP_SYS_INFO_IND_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        TAF_MMA_Proc3gppMsccSysInfoIndInClMode(pstMsccSysInfo);
    }
    else
#endif
    {
        TAF_MMA_Proc3gppMsccSysInfoIndInGulMode(pstMsccSysInfo);
    }

    return VOS_TRUE;
}
VOS_VOID MMA_GetRssiLevelFromValue( VOS_INT32      lRssiValue, VOS_UINT8    *pucRssiLevel )
{
    if (lRssiValue >= -51)
    {
        *pucRssiLevel = 31;
    }
    else if (lRssiValue <= MMA_RSSI_LOWER_LIMIT)
    {
        *pucRssiLevel = TAF_PH_RSSIZERO;
    }
    else
    {
        *pucRssiLevel = (VOS_UINT8)(((VOS_UINT32)(lRssiValue - MMA_RSSI_LOWER_LIMIT )) >> 1);
    }

    return;
}



VOS_VOID MMA_InitEventInfoOP(TAF_PHONE_EVENT_INFO_STRU *pstEvent)
{
    /*�������ѡ��Ϊ0*/
    pstEvent->OP_BatteryPower    = VOS_FALSE;
    pstEvent->OP_CsServiceStatus = VOS_FALSE;
    pstEvent->OP_CurRegSta       = VOS_FALSE;
    pstEvent->OP_PhoneError      = VOS_FALSE;
    pstEvent->OP_PlmnReselMode   = VOS_FALSE;
    pstEvent->OP_PsServiceStatus = VOS_FALSE;
    pstEvent->OP_RegPlmn         = VOS_FALSE;
    pstEvent->OP_Rssi            = VOS_FALSE;
    pstEvent->OP_OperMode        = VOS_FALSE;
    pstEvent->OP_Pin             = VOS_FALSE;
    pstEvent->OP_Spare           = VOS_FALSE;
    pstEvent->OP_PinRemain       = VOS_FALSE;
    pstEvent->OP_Mode            = VOS_FALSE;
    pstEvent->OP_Srvst           = VOS_FALSE;
    pstEvent->OP_UsimRestrictAccess = VOS_FALSE;
    pstEvent->OP_UsimPNN         = VOS_FALSE;
    pstEvent->OP_UsimOPL         = VOS_FALSE;

    pstEvent->Op_CellAcInfo      = VOS_FALSE;
    pstEvent->OP_PsInitRslt     = VOS_FALSE;
    return;
}
/*****************************************************************************
 �� �� ��  : MMA_PhonePinRemainTimeReport
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��30��
    ��    ��   : liuyang
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MMA_PhonePinRemainTimeReport(const TAF_PH_PIN_TIMECNF_STRU * pstPinCnf)
{
    TAF_PHONE_EVENT_INFO_STRU *pstPhoneEvent;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_PhonePinRemainTimeReport:ERROR:ALLOC MEMORY FAIL.");
        return;
    }
    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));
    /*������Ч���ж�*/
    if ( VOS_NULL_PTR == pstPinCnf)
    {
        MMA_WARNINGLOG("MMA_PinDataReport():WARNING:pPinCnf is NULL PTR!.");
        MMA_HandleEventError(gstMmaValue.stOpPinData.ClientId,
                             gstMmaValue.stOpPinData.OpId,
                             TAF_ERR_NULL_PTR,
                             TAF_PH_EVT_OP_PINREMAIN_CNF);
        PS_MEM_FREE(WUEPS_PID_MMA,pstPhoneEvent);
        return;
    }

    MMA_InitEventInfoOP(pstPhoneEvent);

    pstPhoneEvent->OP_PinRemain    = VOS_TRUE;
    pstPhoneEvent->PinRemainCnf    = *pstPinCnf;
    pstPhoneEvent->PhoneEvent      = TAF_PH_EVT_OP_PINREMAIN_CNF;
    Taf_PhoneEvent(pstPhoneEvent);
    PS_MEM_FREE(WUEPS_PID_MMA,pstPhoneEvent);
}
VOS_VOID TAF_MMA_GetRegStateInfo( TAF_PH_REG_STATE_STRU *pstCurRegInf )
{
    TAF_PLMN_ID_STRU                   *pstPlmnId = VOS_NULL_PTR;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enCsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enPsRegStatus;

    /* Modified by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
    /*��ȡMM��ע��״̬*/
    enCsRegStatus          = TAF_SDC_GetAppCsRegStatus();

    if (TAF_SDC_REG_STATUS_BUTT == enCsRegStatus)
    {
        enCsRegStatus = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    }

    pstCurRegInf->RegState   = (TAF_PH_REG_STATE_TYPE)enCsRegStatus;

    /*��ȡPSע��״̬*/
    enPsRegStatus              = TAF_SDC_GetAppPsRegStatus();

    if (TAF_SDC_REG_STATUS_BUTT == enPsRegStatus)
    {
        enPsRegStatus = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    }

    pstCurRegInf->ucPsRegState  = (TAF_PH_REG_STATE_TYPE)enPsRegStatus;
    /* Modified by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */

    /* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, begin */
    /*��ȡ��ǰPLMN*/
    pstPlmnId          = (TAF_PLMN_ID_STRU *)TAF_SDC_GetAppServicePlmnId();
    pstCurRegInf->Plmn = *pstPlmnId;

    /*��ȡ��ǰCI*/
    pstCurRegInf->CellId.aulCellId[0] = TAF_SDC_GetAppCampCellId();
    pstCurRegInf->CellId.ucCellNum = 1;

    /*��ȡ��ǰLAC*/
    pstCurRegInf->usLac  = TAF_SDC_GetAppCampLac();

    /*��ȡ��ǰRAC*/
    pstCurRegInf->ucRac     = TAF_SDC_GetAppCampRac();


    /* ��MMC�ϱ���ϵͳ��ģʽתΪ+CREG/+CGREG�������[ACT]��Э��涨�Ľ��뼼��ֵ */
    NAS_MMA_TransferSysSubMode2ActForAtCmdCreg(TAF_SDC_GetAppSysSubMode(), &(pstCurRegInf->ucAct));
  /* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, end */

    return;
}
VOS_UINT32 TAF_MMA_GetPidFromClientId(
    MN_CLIENT_ID_T                      usClientId
)
{
    MN_CLIENT_ID_TYPE_UINT16            enClientIdType;

    enClientIdType = MN_GetClientIdType(usClientId);

    if (MN_CLIENT_ID_TYPE_AT == enClientIdType)
    {
        return WUEPS_PID_AT;
    }
    else if (CMMCA_CLIENT_ID == usClientId)
    {
        return WUEPS_PID_CMMCA;
    }
    else
    {
        return MN_GetPidFromClientId(usClientId);
    }
}


VOS_VOID MMA_PhModeReport(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_PH_OP_MODE_CNF_STRU             stPhMode,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent = VOS_NULL_PTR;
    TAF_MMA_CTRL_STRU                   stCtrlInfo;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;
    VOS_UINT32                          ulModuleId;
    VOS_UINT32                          ulRcvPid;

    enRslt = TAF_MMA_APP_OPER_RESULT_SUCCESS;

    if ( TAF_ERR_NO_ERROR != enErrorCode )
    {
        enRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
    }

    /* ��ǰΪCMMCA_CLIENT_ID�����ϱ���CMMCAģ��,���ΪINTERNAL_CLIENT_ID_SPM�����ϱ���TAFģ��*/
    if ( (CMMCA_CLIENT_ID        == ClientId)
      || (INTERNAL_CLIENT_ID_SPM == ClientId) )
    {
        if (CMMCA_CLIENT_ID == ClientId)
        {
            ulModuleId = WUEPS_PID_CMMCA;
        }
        else
        {
            ulModuleId = WUEPS_PID_TAF;
        }

        TAF_MMA_BuildMmaCtrlInfo(ulModuleId, ClientId, OpId, &stCtrlInfo);
        TAF_MMA_SndPhoneModeSetCnf(&stCtrlInfo,
                                   stPhMode.PhMode,
                                   enRslt,
                                   enErrorCode);
        return ;
    }
    /* ��ʼ���¼��ϱ� */

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_PhModeReport:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    /* ����ģʽ���� */
    pstPhoneEvent->OP_OperMode = 1;
    pstPhoneEvent->PhoneEvent = TAF_PH_EVT_OPER_MODE_IND;

    /* ����д�����д������ */
    if ( TAF_ERR_NO_ERROR != enErrorCode )
    {
        pstPhoneEvent->OP_PhoneError = 1;
        pstPhoneEvent->PhoneError = enErrorCode;
        MMA_INFOLOG1("MMA_PhModeReport():INFO:Report Error code:",(VOS_INT32)enErrorCode);
    }


    /* ��д�ϱ��¼�OperMode�ṹ*/
    pstPhoneEvent->OperMode = stPhMode;
    pstPhoneEvent->OpId     = OpId;

    if ( ( TAF_PH_CMD_SET == stPhMode.CmdType )
      && ( TAF_ERR_NO_ERROR == enErrorCode ) )
    {
        /* ���óɹ��¼��㲥 */
        pstPhoneEvent->ClientId = MMA_CLIENTID_BROADCAST;
        MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));
    }

    /* ���ý���ϱ� */
    if ( TAF_PH_CMD_SET == stPhMode.CmdType )
    {
        /* ��ǰΪCMMCAģʽ�����ϱ���CMMCAģ�� */
        ulRcvPid = TAF_MMA_GetPidFromClientId(ClientId);

        if ((WUEPS_PID_AT == ulRcvPid)
         || (WUEPS_PID_CMMCA == ulRcvPid))
        {
            TAF_MMA_BuildMmaCtrlInfo(ulRcvPid, ClientId, OpId, &stCtrlInfo);
            TAF_MMA_SndPhoneModeSetCnf(&stCtrlInfo,
                                       stPhMode.PhMode,
                                       enRslt,
                                       enErrorCode);
        }
        else if (VOS_PID_BUTT != ulRcvPid)
        {
            pstPhoneEvent->ClientId   = ClientId;
            pstPhoneEvent->PhoneEvent = TAF_PH_EVT_OPER_MODE_CNF;

            MN_PH_SendMsg(ClientId, (VOS_UINT8*)pstPhoneEvent, sizeof(TAF_PHONE_EVENT_INFO_STRU));
        }
        else
        {
        }

        PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

        return;
    }

    /* ��ѯ�¼��ϱ����ÿͻ��� */
    pstPhoneEvent->PhoneEvent = TAF_PH_EVT_OPER_MODE_CNF;
    pstPhoneEvent->ClientId   = ClientId;

    /* ���õ绰�����ϱ����� */
    MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);
}

/* ����MMA_PhModeQuery MMA_PhModeHandle MMA_PhModeSet�ƶ�λ�� */

/* Modified by h00313353 for Iteration 13, 2015-4-9, begin */

VOS_VOID MMA_ChangeSrv2Class(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8     enSrvDomain,
    TAF_PH_MS_CLASS_TYPE                 *pucMsClass
)
{
    switch(enSrvDomain)
    {
        case TAF_MMA_SERVICE_DOMAIN_CS_PS:
            *pucMsClass = TAF_PH_MS_CLASS_A;
            break;
        case TAF_MMA_SERVICE_DOMAIN_PS:
            *pucMsClass = TAF_PH_MS_CLASS_CG;
            break;
        case TAF_MMA_SERVICE_DOMAIN_ANY:
        case TAF_MMA_SERVICE_DOMAIN_CS:
            *pucMsClass = TAF_PH_MS_CLASS_CC;
            break;
        default:
            *pucMsClass = TAF_PH_MS_CLASS_NULL;
            break;
    }
    return;
}
/* Modified by h00313353 for Iteration 13, 2015-4-10, end */

/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */

VOS_VOID MMA_ChangeClass2Srv(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8  *pucSrvDomain,
    TAF_PH_MS_CLASS_TYPE                ucMsClass
)
{
    switch(ucMsClass)
    {
        case TAF_PH_MS_CLASS_A:
        case TAF_PH_MS_CLASS_B:
            *pucSrvDomain = TAF_MMA_SERVICE_DOMAIN_CS_PS;
            break;
        case TAF_PH_MS_CLASS_CG:
            *pucSrvDomain = TAF_MMA_SERVICE_DOMAIN_PS;
            break;
        case TAF_PH_MS_CLASS_CC:
            *pucSrvDomain = TAF_MMA_SERVICE_DOMAIN_CS;
            break;
        case TAF_PH_MS_CLASS_ANY:
            *pucSrvDomain = TAF_MMA_SERVICE_DOMAIN_ANY;
            break;
        default:
            *pucSrvDomain = TAF_MMA_SERVICE_DOMAIN_NULL;
            break;
    }
    return;
}
/* Modified by h00313353 for Iteration 13, 2015-4-10, end */

VOS_UINT32 TAF_MMA_IsUserSettedRatOrderChanged(
    TAF_MMA_RAT_ORDER_STRU             *pstUserSettedRatOrder,
    TAF_MMA_RAT_ORDER_STRU             *pstOrigUserSettedRatOrder
)
{
    VOS_UINT32                          i;

    /* �������� */
    if (pstUserSettedRatOrder->ucRatOrderNum != pstOrigUserSettedRatOrder->ucRatOrderNum)
    {
        return VOS_TRUE;
    }

    /* �Ƚ����ȼ������Ƿ���ȫ��� */
    for (i = 0; i < pstUserSettedRatOrder->ucRatOrderNum; i++)
    {
        if (pstUserSettedRatOrder->aenRatOrder[i] != pstOrigUserSettedRatOrder->aenRatOrder[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}



VOS_UINT32 TAF_MMA_IsUserSettedLBandChanged(
    TAF_USER_SET_PREF_BAND64            *pstLBand,
    TAF_USER_SET_PREF_BAND64            *pstOrigLBand

)
{
    /* ��LTE��Ƶ��ָʾΪ��TAF_PH_BAND_NO_CHANGE */
    if ( (TAF_PH_BAND_NO_CHANGE != pstLBand->ulBandLow)
      || (0                     != pstLBand->ulBandHigh) )
    {
        if ( (pstLBand->ulBandLow != pstOrigLBand->ulBandLow)
          || (pstLBand->ulBandHigh != pstOrigLBand->ulBandHigh) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
VOS_UINT32 MN_MMA_IsGUDualMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
    VOS_UINT8                           isWModeExist;
    VOS_UINT8                           isGModeExist;
    VOS_UINT32                          i;

    isWModeExist = VOS_FALSE;
    isGModeExist = VOS_FALSE;

    for (i = 0; i < pstRatOrder->ucRatOrderNum; i++)
    {
        /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
        if (TAF_MMA_RAT_GSM == pstRatOrder->aenRatOrder[i])
        {
            isGModeExist = VOS_TRUE;
        }
        else if(TAF_MMA_RAT_WCDMA == pstRatOrder->aenRatOrder[i])
        /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
        {
            isWModeExist = VOS_TRUE;
        }
        else
        {
        }
    }

    if ((VOS_TRUE == isGModeExist) && (VOS_TRUE == isWModeExist))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 MN_MMA_IsGOnlyMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
    if ((1 == pstRatOrder->ucRatOrderNum)
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
     && (TAF_MMA_RAT_GSM == pstRatOrder->aenRatOrder[0]))
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 MN_MMA_IsWOnlyMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
    if ((1 == pstRatOrder->ucRatOrderNum)
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
     && (TAF_MMA_RAT_WCDMA == pstRatOrder->aenRatOrder[0]))
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 MN_MMA_IsLOnlyMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
    if ((1 == pstRatOrder->ucRatOrderNum)
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
     && (TAF_MMA_RAT_LTE == pstRatOrder->aenRatOrder[0]))
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#endif


VOS_VOID MN_MMA_Convert64BitBandTo32Bit(
    TAF_USER_SET_PREF_BAND64           *pstBand,
    VOS_UINT32                         *pulBand
)
{
    /* ֻ��WCDMA900��WCDMA1700����Ƶ�γ���32λ��Ҫ����ת��,
       ת��ԭ��:WCDMA900��0x2000000000000ת��Ϊ0x00020000
                WCDMA1700��0x4000000000000ת��Ϊ0x00040000
       ԭGU����32λ��Ƶ�β�����0x00020000��0x00040000��ֵ */
    if ((0 != pstBand->ulBandHigh)
     || ( TAF_PH_BAND_ANY != pstBand->ulBandLow))
    {
        *pulBand = pstBand->ulBandHigh |
                        (pstBand->ulBandLow & ~TAF_PH_BAND_NEED_CHANGE_TO_64BIT);
    }
    else
    {
        *pulBand = pstBand->ulBandLow;
    }

    return;
}

    /* Move this function in SYS CFG state machine */

VOS_VOID MN_MMA_ConvertGUFrequencyBand(
    VOS_UINT32                         *pulPrefBand
)
{
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU *pstUserSettedBand   = VOS_NULL_PTR;
    VOS_UINT32                          ulUserSettedPrefBand;

    pstUserSettedBand    = TAF_MMA_GetSyscfgUserSetBandAddr();
    ulUserSettedPrefBand = *pulPrefBand;

    switch ( ulUserSettedPrefBand )
    {
        /* �û����õ�GUƵ��Ϊ���ı� */
        case TAF_PH_BAND_NO_CHANGE:
            *pulPrefBand     = pstUserSettedBand->uUserSetGuBand.ulPrefBand;
            break;

        /* �û����õ�GUƵ��Ϊ�κ�Ƶ�� */
        case TAF_PH_BAND_ANY:
            *pulPrefBand     &= TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand;
            break;

        default:
            *pulPrefBand     = ulUserSettedPrefBand;
            break;
    }

    /* ������ЧƵ�� */
    *pulPrefBand &= TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand;

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_MMA_ConvertLteFrequencyBand(
    TAF_USER_SET_PREF_BAND64           *pstLBand
)
{
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstUserSettedBand   = VOS_NULL_PTR;
    TAF_USER_SET_PREF_BAND64           *pstUeSupportLteBand = VOS_NULL_PTR;
    TAF_USER_SET_PREF_BAND64            stLBand;

    stLBand            = *pstLBand;
    pstUserSettedBand  = TAF_MMA_GetSyscfgUserSetBandAddr();

    /* �û����õ�LTEƵ��Ϊ�κ�Ƶ�� */
    if ((MN_MMA_LTE_HIGH_BAND_ANY == stLBand.ulBandHigh)
     && (MN_MMA_LTE_LOW_BAND_ANY == stLBand.ulBandLow))
    {
        *pstLBand = TAF_MMA_GetUeSupportBandAddr()->stUeSupportLteBand;
    }

    /* �û����õ�LTEƵ��Ϊ���ı� */
    else if((TAF_PH_BAND_NO_CHANGE == stLBand.ulBandLow)
         && (0 == stLBand.ulBandHigh))
    {
        *pstLBand = pstUserSettedBand->stUserSetLteBand;
    }
    else
    {
        *pstLBand = stLBand;
    }

    /* ������ЧƵ�� */
    pstUeSupportLteBand   = TAF_MMA_GetUeSupportLteBandAddr();
    pstLBand->ulBandLow  &= pstUeSupportLteBand->ulBandLow;
    pstLBand->ulBandHigh &= pstUeSupportLteBand->ulBandHigh;

    return;
}
#endif

VOS_UINT32  MN_MMA_IsUserSettedBandValid(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
{
    TAF_MMA_USER_BAND_SET_UN            uGuBand;
#if(FEATURE_ON == FEATURE_LTE)
    TAF_USER_SET_PREF_BAND64           *pstUeSupportLteBand = VOS_NULL_PTR;
#endif
    TAF_MMA_UE_BAND_CAPA_ST            *pstUeBandCap = VOS_NULL_PTR;

    /* ��GUƵ�� pstSysCfgPara->stGuBand 64λת��Ϊ32λ�� */
    MN_MMA_Convert64BitBandTo32Bit(&pstSysCfgPara->stGuBand, &uGuBand.ulPrefBand);

    MN_MMA_ConvertGUFrequencyBand(&uGuBand.ulPrefBand);

#if (FEATURE_ON == FEATURE_LTE)
    /* ��ȡ�û����õ�LBand */
    TAF_MMA_ConvertLteFrequencyBand(&pstSysCfgPara->stLBand);
#endif

    pstUeBandCap = TAF_MMA_GetUeSupportBandAddr();

    /* ��ģ���ģʱ,�û����õ�GU��L��Ƶ�α���Ҫ�뵱ǰUE֧�ֵ�GU��L��Ƶ�����ص�Ƶ��
       �����ֹ�û�����Ƶ����ȥ;��UE֧�ֵ�GU��L��Ƶ����Чʱ,������û����õ�Ƶ�� */
    if ((0 == (uGuBand.ulPrefBand & pstUeBandCap->ulUeGSptBand))
     && (0 != pstUeBandCap->ulUeGSptBand))
    {
        return VOS_FALSE;
    }

    if ((0 == (uGuBand.ulPrefBand & pstUeBandCap->ulUeWSptBand))
     && (0 != pstUeBandCap->ulUeWSptBand))
    {
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    pstUeSupportLteBand = TAF_MMA_GetUeSupportLteBandAddr();

    if ((0 == (pstSysCfgPara->stLBand.ulBandLow & pstUeSupportLteBand->ulBandLow))
     && (0 == (pstSysCfgPara->stLBand.ulBandHigh & pstUeSupportLteBand->ulBandHigh))
     && ((0 != pstUeSupportLteBand->ulBandLow)
      || (0 != pstUeSupportLteBand->ulBandHigh)))
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}

/* Modified by l00301449 for Iteration 13, 2015-04-07, begin */

VOS_VOID TAF_MMA_SetSyscfg_PowerOffStatus(
    TAF_MMA_SYS_CFG_REQ_STRU           *pstSysCfgReq
)
{
            /* ����NV */
    TAF_MMA_UpdateSysCfgPara(&(pstSysCfgReq->stSysCfgPara));

    /* �ϱ����ý�� */
    TAF_MMA_SndSysCfgSetCnf(&(pstSysCfgReq->stCtrl), TAF_ERR_NO_ERROR);

    return;

}
/* Modified by l00301449 for Iteration 13, 2015-04-07, end */

/* move these function in SYS CFG state machine */


/* delete this function */


VOS_VOID MMA_SwitchUserSetBand2UESupportBand
(
  TAF_MMA_USER_BAND_SET_UN              uUserSetBand,
  TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU    *pstUeBand
)
{

    TAF_MMA_USER_PREF_BAND_STRU        *pstUserBitBand  = VOS_NULL_PTR;
    TAF_MMA_GSM_PREF_BAND_STRU         *pstGsmBitBand   = VOS_NULL_PTR;
    TAF_MMA_WCDMA_PREF_BAND_STRU       *pstWcdmaBitBand = VOS_NULL_PTR;
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstUserSetBand  = VOS_NULL_PTR;

    pstUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();

    pstUserBitBand = &(uUserSetBand.BitBand);
    pstGsmBitBand = &(pstUeBand->unGsmBand.BitBand);
    pstWcdmaBitBand = &(pstUeBand->unWcdmaBand.BitBand);

    PS_MEM_SET(pstGsmBitBand,0,sizeof(TAF_MMA_GSM_PREF_BAND_STRU));
    PS_MEM_SET(pstWcdmaBitBand,0,sizeof(TAF_MMA_WCDMA_PREF_BAND_STRU));

    if (TAF_PH_BAND_NO_CHANGE == uUserSetBand.ulPrefBand)
    {
        pstUeBand->unGsmBand.ulBand   = pstUserSetBand->uUserSetUeFormatGuBand.unGsmBand.ulBand;
        pstUeBand->unWcdmaBand.ulBand = pstUserSetBand->uUserSetUeFormatGuBand.unWcdmaBand.ulBand;

        MMA_NORMAILLOG("MMA_SwitchUserSetBand2UESupportBand:INFO:BAND NO CHANGE.");
        return;
    }

    if (TAF_PH_BAND_ANY == uUserSetBand.ulPrefBand)
    {
        uUserSetBand.ulPrefBand = TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand;
    }

    /* ������ЧƵ�� */
    uUserSetBand.ulPrefBand  &= (TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand);

    pstGsmBitBand->BandGsm850 = pstUserBitBand->BandGsm850;
    pstGsmBitBand->BandGsm1800 = pstUserBitBand->BandGsmDcs1800;
    pstGsmBitBand->BandGsmE900 = pstUserBitBand->BandGsmEgsm900;
    pstGsmBitBand->BandGsm1900 = pstUserBitBand->BandGsmPcs1900;
    pstGsmBitBand->BandGsmP900 = pstUserBitBand->BandGsmPgsm900;
    pstGsmBitBand->BandGsmR900 = pstUserBitBand->BandGsmRgsm900;
    pstGsmBitBand->BandGsm850 = pstUserBitBand->BandGsm850;

    pstWcdmaBitBand->BandWCDMA_I_2100 = pstUserBitBand->BandWcdma_I_Imt2k1;
    pstWcdmaBitBand->BandWCDMA_II_1900 = pstUserBitBand->BandWcdma_II_PCS_1900;
    pstWcdmaBitBand->BandWCDMA_III_1800 = pstUserBitBand->BandWcdma_III_1800;
    pstWcdmaBitBand->BandWCDMA_IV_1700 = pstUserBitBand->BandWcdma_IV_1700;
    pstWcdmaBitBand->BandWCDMA_V_850 = pstUserBitBand->BandWcdma_V_850;
    pstWcdmaBitBand->BandWCDMA_VI_800 = pstUserBitBand->BandWcdma_VI_800;
    pstWcdmaBitBand->BandWCDMA_VII_2600 = pstUserBitBand->BandWcdma_VII_2600;
    pstWcdmaBitBand->BandWCDMA_VIII_900 = pstUserBitBand->BandWcdma_VIII_900;
    pstWcdmaBitBand->BandWCDMA_IX_J1700 = pstUserBitBand->BandWcdma_IX_1700;

    pstWcdmaBitBand->BandWCDMA_XIX_850 = pstUserBitBand->BandWCDMA_XIX_850;
    pstWcdmaBitBand->BandWCDMA_XI_1500  = pstUserBitBand->BandWcdma_XI_1500;

    MMA_INFOLOG1("MMA_SwitchUserSetBand2UESupportBand:INFO:GSM band:",
                 (VOS_INT32)pstUeBand->unGsmBand.ulBand);
    MMA_INFOLOG1("MMA_SwitchUserSetBand2UESupportBand:INFO:WCDMA band:",
                 (VOS_INT32)pstUeBand->unWcdmaBand.ulBand);

    return;
}
VOS_VOID MMA_SwitchUESupportBand2UserSetBand
(
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   stUeBand,
    TAF_MMA_USER_BAND_SET_UN           *puUserSetBand
)
{
    TAF_MMA_USER_PREF_BAND_STRU         *pstUserBitBand  = VOS_NULL_PTR;
    TAF_MMA_GSM_PREF_BAND_STRU          *pstGsmBitBand   = VOS_NULL_PTR;
    TAF_MMA_WCDMA_PREF_BAND_STRU        *pstWcdmaBitBand = VOS_NULL_PTR;

    PS_MEM_SET(puUserSetBand, 0, sizeof(TAF_MMA_USER_BAND_SET_UN));
    pstUserBitBand                      = &(puUserSetBand->BitBand);
    pstGsmBitBand                       = &(stUeBand.unGsmBand.BitBand);
    pstWcdmaBitBand                     = &(stUeBand.unWcdmaBand.BitBand);

    pstUserBitBand->BandGsmDcs1800        = pstGsmBitBand->BandGsm1800;
    pstUserBitBand->BandGsmPcs1900        = pstGsmBitBand->BandGsm1900;
    pstUserBitBand->BandGsm850            = pstGsmBitBand->BandGsm850;
    pstUserBitBand->BandGsmEgsm900        = pstGsmBitBand->BandGsmE900;
    pstUserBitBand->BandGsmPgsm900        = pstGsmBitBand->BandGsmP900;
    pstUserBitBand->BandGsmRgsm900        = pstGsmBitBand->BandGsmR900;
    pstUserBitBand->BandWcdma_I_Imt2k1    = pstWcdmaBitBand->BandWCDMA_I_2100;
    pstUserBitBand->BandWcdma_II_PCS_1900 = pstWcdmaBitBand->BandWCDMA_II_1900;
    pstUserBitBand->BandWcdma_III_1800    = pstWcdmaBitBand->BandWCDMA_III_1800;
    pstUserBitBand->BandWcdma_IV_1700     = pstWcdmaBitBand->BandWCDMA_IV_1700;
    pstUserBitBand->BandWcdma_V_850       = pstWcdmaBitBand->BandWCDMA_V_850;
    pstUserBitBand->BandWcdma_VI_800      = pstWcdmaBitBand->BandWCDMA_VI_800;
    pstUserBitBand->BandWcdma_VII_2600    = pstWcdmaBitBand->BandWCDMA_VII_2600;
    pstUserBitBand->BandWcdma_VIII_900    = pstWcdmaBitBand->BandWCDMA_VIII_900;
    pstUserBitBand->BandWcdma_IX_1700     = pstWcdmaBitBand->BandWCDMA_IX_J1700;
    pstUserBitBand->BandWcdma_XI_1500     = pstWcdmaBitBand->BandWCDMA_XI_1500;

    pstUserBitBand->BandWCDMA_XIX_850     = pstWcdmaBitBand->BandWCDMA_XIX_850;
    MMA_INFOLOG1("MMA_SwitchUESupportBand2UserSetBand:INFO:band:",
                 (VOS_INT32)puUserSetBand->ulPrefBand);
    return;
}


VOS_VOID TAF_MMA_UpdateRatPriorityToNvim(
    TAF_MMA_RAT_ORDER_STRU             *pstCurrRatOrder,
    TAF_MMA_RAT_ORDER_STRU             *pstLastRatOrder
)
{
    VOS_UINT32                         ulRatOrderChangedFlg;
    TAF_PH_NVIM_RAT_ORDER_STRU          stRatPrioList;


    ulRatOrderChangedFlg = VOS_FALSE;

    ulRatOrderChangedFlg = TAF_MMA_IsUserSettedRatOrderChanged(pstCurrRatOrder,
                                                               TAF_MMA_GetRatPrioListAddr());
    if (VOS_TRUE == ulRatOrderChangedFlg)
    {
        PS_MEM_SET(&stRatPrioList, 0, sizeof(TAF_PH_NVIM_RAT_ORDER_STRU));

        PS_MEM_CPY(&stRatPrioList, pstCurrRatOrder, sizeof(TAF_PH_NVIM_RAT_ORDER_STRU));

        /* ���½��뼼��,�������ȼ�NV */
        if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_RAT_PRIO_LIST,
                                               &stRatPrioList,
                                               sizeof(stRatPrioList)))
        {
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateRatpriorityToNvim: Write en_NV_Item_RAT_PRIO_LIST failed");
        }

        /* ���µ�ǰ��RAT ordeȫ�ֱ��� */
        PS_MEM_CPY(pstLastRatOrder, pstCurrRatOrder, sizeof(TAF_MMA_RAT_ORDER_STRU));

        /* ���µ�ǰ��RAT orde��SDC */
        TAF_SDC_SetMsPrioRatList((TAF_SDC_RAT_PRIO_STRU *)pstCurrRatOrder);
    }
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_MMA_UpdateLteBandToNvim(
    TAF_USER_SET_PREF_BAND64           *pstCurrLteBand,
    TAF_USER_SET_PREF_BAND64           *pstLastLteBand
)
{

    VOS_UINT32                          ulLBandChangedFlg;

    ulLBandChangedFlg = TAF_MMA_IsUserSettedLBandChanged(pstCurrLteBand,
                                                         TAF_MMA_GetUserSetLteBandAddr());
    if (VOS_TRUE == ulLBandChangedFlg)
    {

        /* �����û����õ�LƵ�ε�NV */
        if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_USER_SET_LTEBANDS,
                                               pstCurrLteBand,
                                               sizeof(TAF_USER_SET_PREF_BAND64)))
        {
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateLteBandToNvim: Write en_NV_Item_USER_SET_LTEBANDS failed");
        }

        /* ����band��ȫ�ֱ��� */
        pstLastLteBand->ulBandHigh = pstCurrLteBand->ulBandHigh;
        pstLastLteBand->ulBandLow  = pstCurrLteBand->ulBandLow;
    }
}
#endif


VOS_VOID TAF_MMA_UpdateGuBandToNvim(
    TAF_USER_SET_PREF_BAND64           *pstCurrGuBand,
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstLastUserBand
)
{
    VOS_UINT32                          ulBand;
    TAF_MMA_USER_BAND_SET_UN            unUserSetBand;
    TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU   stSetBand;

    MN_MMA_Convert64BitBandTo32Bit(pstCurrGuBand, &ulBand);

    if (TAF_PH_BAND_NO_CHANGE != ulBand)
    {
        MN_MMA_ConvertGUFrequencyBand(&ulBand);

        unUserSetBand.ulPrefBand = ulBand;

        PS_MEM_SET(&stSetBand, 0, sizeof(TAF_MMA_UE_SUPPORT_FREQ_BAND_STRU));

        MMA_SwitchUserSetBand2UESupportBand(unUserSetBand, &stSetBand);

        /* �����û�����Ƶ�ε�NV */
        if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_User_Set_Freqbands,
                                               pstCurrGuBand,
                                               sizeof(TAF_USER_SET_PREF_BAND64)))
        {
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateGuBandToNvim: Write en_NV_Item_User_Set_Freqbands failed");
        }

        /* ����Ƶ��NV */
        if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_Support_Freqbands,
                                               &(stSetBand),
                                               sizeof(stSetBand.unGsmBand)+sizeof(stSetBand.unWcdmaBand)))
        {
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateGuBandToNvim: Write en_NV_Item_Support_Freqbands failed");
        }

        /* ����GU band��ȫ�ֱ��� */
        pstLastUserBand->uUserSetGuBand.ulPrefBand                 = unUserSetBand.ulPrefBand ;

        pstLastUserBand->uUserSetUeFormatGuBand.unGsmBand.ulBand   = stSetBand.unGsmBand.ulBand;

        pstLastUserBand->uUserSetUeFormatGuBand.unWcdmaBand.ulBand = stSetBand.unWcdmaBand.ulBand;

        pstLastUserBand->stOrigUserSetGuBand.ulBandLow             = pstCurrGuBand->ulBandLow;

        pstLastUserBand->stOrigUserSetGuBand.ulBandHigh            = pstCurrGuBand->ulBandHigh;
    }

}
VOS_VOID TAF_MMA_UpdateRoamToNvim(
    TAF_MMA_ROAM_MODE_ENUM_UINT8       enCurrRoam,
    TAF_MMA_ROAM_MODE_ENUM_UINT8      *penLastRoam
)
{
    NAS_NVIM_ROAM_CFG_INFO_STRU         stRoamFeature;
    TAF_MMA_ROAM_MODE_ENUM_UINT8        enLastRoam;
    VOS_UINT8                           ucRoamParaChange;

    ucRoamParaChange = VOS_FALSE;

    PS_MEM_SET(&stRoamFeature, 0x00, sizeof(NAS_NVIM_ROAM_CFG_INFO_STRU));

    if (NV_OK != NV_Read(en_NV_Item_Roam_Capa, &stRoamFeature, sizeof(stRoamFeature)))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateRoamToNvim: Read en_NV_Item_Roam_Capa Nvim failed");
    }

    enLastRoam = TAF_MMA_GetSyscfgUserSetRoamValue();

    if (NAS_MSCC_PIF_ROAM_FEATURE_OFF == stRoamFeature.ucRoamFeatureFlg)
    {
        if ((enLastRoam                                 != enCurrRoam)
         && (TAF_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_ON != enCurrRoam))
        {
            ucRoamParaChange = VOS_TRUE;
        }
    }
    else
    {
        if ((enLastRoam            != enCurrRoam)
         && (TAF_MMA_ROAM_UNCHANGE != enCurrRoam))
        {
            ucRoamParaChange = VOS_TRUE;
        }
    }

    if (VOS_TRUE == ucRoamParaChange)
    {
        /* ��������֧����ȫ�ֲ��� */
        stRoamFeature.ucRoamCapability = enCurrRoam;

        /* ��������֧����NV */
        if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_Roam_Capa,
                                               &stRoamFeature,
                                               TAF_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_ON))
        {
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateRoamToNvim: Write en_NV_Item_Support_Freqbands failed");
        }

        *penLastRoam = enCurrRoam;
    }
}


VOS_VOID TAF_MMA_UpdateMsClassToNvim(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8     enCurrSrvDomain,
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8    *penLastSrvDomain
)
{
    TAF_PH_MS_CLASS_TYPE                ucClass;

    if (TAF_MMA_SERVICE_DOMAIN_NOCHANGE != enCurrSrvDomain)
    {
        /* ���·�����ȫ�ֲ��� */
        MMA_ChangeSrv2Class(enCurrSrvDomain, &ucClass);

        /* ���·�����NV */
        if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_MMA_MsClass,
                                               &(enCurrSrvDomain),
                                                sizeof(TAF_PH_MS_CLASS_TYPE)))
        {
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateMsClassToNvim: Write en_NV_Item_MMA_MsClass failed");
        }

        /* ����ȫ�ֱ��� */
        gstMmaValue.stSetMsClass.NewMsClassType     = ucClass;
        gstMmaValue.stSetMsClass.MsClassType        = ucClass;
        gstMmaValue.pg_StatusContext->ucModeService = ucClass;

        *penLastSrvDomain                           = enCurrSrvDomain;
    }
}
VOS_VOID TAF_MMA_UpdateAccessModeToNvim(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstCurrSysCfg,
    TAF_MMA_USER_SET_PRIO_RAT_ENUM_U8  *penLastPrioRat
)
{
    VOS_UINT16                          i;
    NAS_MMA_NVIM_ACCESS_MODE_STRU       stAccessMode;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulRatOrderChangedFlg;

    ulLength = 0;
    ulRatOrderChangedFlg = VOS_FALSE;

    /* ��֧��Lģʱ��Ҫд�� */
    for ( i = 0 ; i < pstCurrSysCfg->stRatOrder.ucRatOrderNum; i++ )
    {
        if ( TAF_MMA_RAT_LTE == pstCurrSysCfg->stRatOrder.aenRatOrder[i])
        {
            return;
        }
    }

    PS_MEM_SET(&stAccessMode, 0x00, sizeof(NAS_MMA_NVIM_ACCESS_MODE_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_MMA_AccessMode, &ulLength);

    if (ulLength > sizeof(NAS_MMA_NVIM_ACCESS_MODE_STRU))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_MMA_AccessMode ,
                         &stAccessMode,
                         ulLength))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateAccessModeToNvim: Read TAF_MMA_UpdateAccessModeToNvim failed");

        return;
    }

    ulRatOrderChangedFlg = TAF_MMA_IsUserSettedRatOrderChanged(&(pstCurrSysCfg->stRatOrder),
                                                               TAF_MMA_GetRatPrioListAddr());
    /* NVIM�еڶ����ֽڱ�ʾ�������ȼ� */
    if (((stAccessMode.aucAccessMode[1]  != pstCurrSysCfg->enUserPrio)
      && (TAF_MMA_USER_SET_PRIO_NOCHANGE != pstCurrSysCfg->enUserPrio))
     || (VOS_TRUE                        == ulRatOrderChangedFlg))
    {
        /* ��Ҫ����NVIM�� */
        if (1 == pstCurrSysCfg->stRatOrder.ucRatOrderNum)
        {
            if (TAF_MMA_RAT_GSM == pstCurrSysCfg->stRatOrder.aenRatOrder[0])
            {
                stAccessMode.aucAccessMode[0] = TAF_PH_USER_SET_RAT_GSM;
            }
            else
            {
                stAccessMode.aucAccessMode[0] = TAF_PH_USER_SET_RAT_WCDMA;
            }
        }
        else
        {
            stAccessMode.aucAccessMode[0] = TAF_PH_USER_SET_RAT_WCDMA_GSM;
        }

        if ( TAF_MMA_USER_SET_PRIO_NOCHANGE != pstCurrSysCfg->enUserPrio)
        {
            stAccessMode.aucAccessMode[1] = pstCurrSysCfg->enUserPrio;
            *penLastPrioRat               = pstCurrSysCfg->enUserPrio;
        }

        if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_MMA_AccessMode,
                                               &stAccessMode,
                                               (VOS_UINT16)ulLength))
        {
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateAccessModeToNvim: Write en_NV_Item_MMA_AccessMode failed");
        }
    }
}
VOS_VOID TAF_MMA_UpdateSysCfgPara(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstCurrSysCfg
)
{
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                     *pstLastSyscfgSet = VOS_NULL_PTR;

    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();

    /* update RAT priority to NV */
    TAF_MMA_UpdateRatPriorityToNvim(&(pstCurrSysCfg->stRatOrder), &(pstLastSyscfgSet->stRatPrioList));

#if (FEATURE_ON == FEATURE_LTE)
    /* update LTE to NV */
    TAF_MMA_UpdateLteBandToNvim(&(pstCurrSysCfg->stLBand), &(pstLastSyscfgSet->stUserSetBand.stUserSetLteBand));
#endif

    TAF_MMA_UpdateGuBandToNvim(&(pstCurrSysCfg->stGuBand), &(pstLastSyscfgSet->stUserSetBand));

    TAF_MMA_UpdateRoamToNvim(pstCurrSysCfg->enRoam, &pstLastSyscfgSet->enRoam);

    TAF_MMA_UpdateMsClassToNvim(pstCurrSysCfg->enSrvDomain, &pstLastSyscfgSet->enSrvDomain);

    TAF_MMA_UpdateAccessModeToNvim(pstCurrSysCfg, &(pstLastSyscfgSet->enPrioRat));
}


VOS_UINT32  MMA_IsGsmForbidden()
{
    VOS_UINT32   ulGsmFordidenFlg = VOS_FALSE;
    VOS_UINT32   ulEfustGsmAccess = 1;
    VOS_UINT32   ulEfustGsmSecContext = 1;

    if (MMA_QUICK_START_ENABLE == gstMmaValue.ulQuickStartFlg)
    {
        return VOS_FALSE;
    }

    /* ɾ����USIM����ֹGSM������ж� */

    /* �ж�Gģ֧�ֵ�Ƶ�Σ����UE��֧��Gģ����ΪGģ����ֹ */
    if (0 == TAF_MMA_GetUeSupportBandAddr()->ulUeGSptBand)
    {
        ulGsmFordidenFlg = VOS_TRUE;
    }

    MMA_INFOLOG1("MMA_IsGsmForbidden: ucForbidReg2GNetWork = ",(VOS_INT32)gstMmaValue.stEfustServiceCfg.ucForbidReg2GNetWork);
    MMA_INFOLOG1("MMA_IsGsmForbidden: ulEfustGsmAccess = ",(VOS_INT32)ulEfustGsmAccess);
    MMA_INFOLOG1("MMA_IsGsmForbidden: ulEfustGsmSecContext = ",(VOS_INT32)ulEfustGsmSecContext);

    return ulGsmFordidenFlg;
}


/* MMA_SndMsccSysCfgReq��������MmaSndMscc.c�� */

VOS_UINT32 TAF_MMA_ConvertDetachTypeToMscc(
    TAF_MMA_DETACH_TYPE_ENUM_UINT8           enDetachType,
    NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32    *pulMsccDetachType
)
{
    switch(enDetachType)
    {
        case TAF_MMA_DETACH_TYPE_GPRS:
            *pulMsccDetachType = NAS_MSCC_PIF_DETACH_TYPE_GPRS;
            break;

        case TAF_MMA_DETACH_TYPE_IMSI:
            *pulMsccDetachType = NAS_MSCC_PIF_DETACH_TYPE_IMSI;
            break;

        case TAF_MMA_DETACH_TYPE_GPRS_IMSI:
            *pulMsccDetachType = NAS_MSCC_PIF_DETACH_TYPE_GPRS_IMSI;
            break;

        default:
            return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MMA_ConvertAttachTypeToMscc(
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enMmaAttachType,
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32    *pulMsccAttachType
)
{
    switch(enMmaAttachType)
    {
        case TAF_MMA_ATTACH_TYPE_GPRS:
            *pulMsccAttachType = NAS_MSCC_PIF_ATTACH_TYPE_GPRS;
            break;

        case TAF_MMA_ATTACH_TYPE_IMSI:
            *pulMsccAttachType = NAS_MSCC_PIF_ATTACH_TYPE_IMSI;
            break;

        case TAF_MMA_ATTACH_TYPE_GPRS_IMSI:
            *pulMsccAttachType = NAS_MSCC_PIF_ATTACH_TYPE_GPRS_IMSI;
            break;

        default:
            return VOS_ERR;
    }

    return VOS_OK;
}



VOS_VOID TAF_MMA_ConvertPlmnPriorityClass(
    NAS_MSCC_PIF_PLMN_PRIORITY_CLASS_ENUM_UINT8                  enPrioClass,
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8                 *penDestPrioClass
)
{
    switch(enPrioClass)
    {
        case NAS_MSCC_PIF_PLMN_PRIORITY_HOME:
            *penDestPrioClass = TAF_MMA_PLMN_PRIORITY_HOME;
            break;

        case NAS_MSCC_PIF_PLMN_PRIORITY_PREF:
            *penDestPrioClass = TAF_MMA_PLMN_PRIORITY_PREF;
            break;

        case NAS_MSCC_PIF_PLMN_PRIORITY_ANY:
            *penDestPrioClass = TAF_MMA_PLMN_PRIORITY_ANY;
            break;

        case NAS_MSCC_PIF_PLMN_PRIORITY_BUTT:
            *penDestPrioClass = TAF_MMA_PLMN_PRIORITY_BUTT;
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ConvertPlmnPriorityClass ERROR!!!");
            *penDestPrioClass = TAF_MMA_PLMN_PRIORITY_BUTT;

            return;
    }

    return;
}



VOS_UINT32 TAF_MMA_ConvertCardType(
    USIMM_CARD_TYPE_ENUM_UINT32                             enCardType,
    TAF_MMA_USIMM_CARD_TYPE_ENUM_UINT32                    *penDestCardType
)
{
    switch(enCardType)
    {
        case USIMM_CARD_SIM:
            *penDestCardType = TAF_MMA_USIMM_CARD_SIM;
            break;

        case USIMM_CARD_USIM:
            *penDestCardType = TAF_MMA_USIMM_CARD_USIM;
            break;

        case USIMM_CARD_ROM_SIM:
            *penDestCardType = TAF_MMA_USIMM_CARD_ROM_SIM;
            break;

        case USIMM_CARD_ISIM:
            *penDestCardType = TAF_MMA_USIMM_CARD_ISIM;
            break;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case USIMM_CARD_UIM:
            *penDestCardType = TAF_MMA_USIMM_CARD_UIM;
            break;

        case USIMM_CARD_CSIM:
            *penDestCardType = TAF_MMA_USIMM_CARD_CSIM;
            break;
#endif
        case USIMM_CARD_NOCARD:
            *penDestCardType = TAF_MMA_USIMM_CARD_NOCARD;
            break;

        default:
            *penDestCardType = TAF_MMA_USIMM_CARD_TYPE_BUTT;
            break;
    }

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_ConvertCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardStatus,
    TAF_MMA_CARD_STATUS_ENUM_UINT8     *penDestCardStatus
)
{
    switch(enCardStatus)
    {
        case USIMM_CARD_SERVIC_AVAILABLE:
            *penDestCardStatus = TAF_MMA_CARD_STATUS_AVAILABLE;
            break;

        default:
            *penDestCardStatus = TAF_MMA_CARD_STATUS_NOT_AVAILABLE;
            break;
    }

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_ConvertServiceStatus(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enServiceStatus,
    TAF_PHONE_SERVICE_STATUS                               *penDestServiceStatus
)
{
    switch(enServiceStatus)
    {
        case TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE:
            *penDestServiceStatus = TAF_REPORT_SRVSTA_NORMAL_SERVICE;
            break;

        case TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE:
            *penDestServiceStatus = TAF_REPORT_SRVSTA_LIMITED_SERVICE;
            break;

        case TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE_REGION:
            *penDestServiceStatus = TAF_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE;
            break;


        case TAF_SDC_SERVICE_STATUS_NO_SERVICE:
            *penDestServiceStatus = TAF_REPORT_SRVSTA_NO_SERVICE;
            break;

        case TAF_SDC_SERVICE_STATUS_NO_CHANGE:
            *penDestServiceStatus = TAF_REPORT_SRVSTA_LIMITED_SERVICE;
            break;

        case TAF_SDC_SERVICE_STATUS_DEEP_SLEEP:
            *penDestServiceStatus = TAF_REPORT_SRVSTA_DEEP_SLEEP;
            break;

        default:
            *penDestServiceStatus = TAF_REPORT_SRVSTA_NO_SERVICE;

            return VOS_FALSE;
    }

    return VOS_TRUE;
}

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-1, begin */

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-1, end */

#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID MN_MMA_GetSupportedUserLteBand(
    TAF_USER_SET_PREF_BAND64           *pstLBand
)
{
    TAF_USER_SET_PREF_BAND64           *pstUserSetLteBand   = VOS_NULL_PTR;
    TAF_USER_SET_PREF_BAND64           *pstUeSupportLteBand = VOS_NULL_PTR;

    /* ȡ�õ�ǰ�û����õ�LTE��Ƶ�� */
    pstUserSetLteBand   = TAF_MMA_GetUserSetLteBandAddr();

    /* ȡ�õ�ǰ��Ʒ֧�ֵ�LTE��Ƶ�� */
    pstUeSupportLteBand = TAF_MMA_GetUeSupportLteBandAddr();

    /* ��ȡ��ǰ��Ʒ֧�ֵ��û����õ�LTEƵ����Ϣ */
    pstLBand->ulBandLow  = (pstUserSetLteBand->ulBandLow) & (pstUeSupportLteBand->ulBandLow);
    pstLBand->ulBandHigh = (pstUserSetLteBand->ulBandHigh) & (pstUeSupportLteBand->ulBandHigh);

}

#endif




/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-1, begin */

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-1, end */


/* MMA_PhSysCfgHandle */

#if ( FEATURE_ON == FEATURE_LTE )

 VOS_UINT32 TAF_MMA_SendL4aMsg(
    VOS_UINT32                          MsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          uLen
)
{
    VOS_UINT32                          ulRet       = VOS_OK;
    MsgBlock                           *pMsgBlock   = NULL;

    pMsgBlock = (MsgBlock*)PS_ALLOC_MSG(WUEPS_PID_MMA, (uLen - VOS_MSG_HEAD_LENGTH));
    if(NULL == pMsgBlock)
    {
        return VOS_ERR;
    }

    (VOS_VOID)VOS_MemCpy((VOS_UINT8*)pMsgBlock, (VOS_UINT8*)pData, uLen);

    /* ��װVOS��Ϣ */
    pMsgBlock->ulReceiverPid = MSP_L4_L4A_PID;
    pMsgBlock->ulSenderPid = WUEPS_PID_MMA;

    ulRet = PS_SEND_MSG(WUEPS_PID_MMA, pMsgBlock);
    if(VOS_OK != ulRet)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "TAF_MMA_SendL4aMsg:ERROR: Fail to send message!");
    }

    return ulRet;
}


#endif

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-1, begin */

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-1, end */

VOS_VOID MMA_GetPhCellRscp (VOS_UINT16          ClientId,
                           VOS_UINT8                 OpId)
{
    TAF_PH_CELL_RSSI_STRU               stMmaRssiTmp;
    VOS_UINT8                           ucRscpLevelTmp;

    TAF_SDC_CTX_STRU                    *pstSdcCtx = VOS_NULL_PTR;

    pstSdcCtx =                                 TAF_SDC_GetSdcCtx();
    /*֧���ϱ�һ��С��*/
    stMmaRssiTmp.CellNum = 1;
    stMmaRssiTmp.CellDlFreq = pstSdcCtx->stAppNetworkInfo.stRssiValue.usCellDlFreq;

    if (TAF_SDC_SYS_MODE_GSM == TAF_SDC_GetAppSysMode())
    {
        MMA_GetRssiLevelFromValue(pstSdcCtx->stAppNetworkInfo.stRssiValue.u.st2GCellSignInfo.sRssiValue,
                                      &ucRscpLevelTmp);
        stMmaRssiTmp.CellRscp[0].CellRSCP = ucRscpLevelTmp;
    }
    else
    {
        MMA_GetRssiLevelFromValue(pstSdcCtx->stAppNetworkInfo.stRssiValue.u.st3GCellSignInfo.sRscpValue,
                                      &ucRscpLevelTmp);
        stMmaRssiTmp.CellRscp[0].CellRSCP = ucRscpLevelTmp;
    }

    stMmaRssiTmp.CellRscp[0].CellId = TAF_SDC_GetCurrCampCellId();


    /*ʹ�������ϱ����������ݴ���TAFm*/
    MMA_ParaQueryReport(ClientId, OpId, TAF_PH_CELL_RSCP_VALUE_PARA,TAF_ERR_NO_ERROR, (VOS_VOID*)&stMmaRssiTmp);

    return;
}


VOS_VOID MMA_GetPhUeRfPowerFreq(VOS_UINT16          ClientId,
                            VOS_UINT8           OpId)
{
    TAF_PH_UE_RFPOWER_FREQ_STRU         stUeRfPowerFreq;

    /*Ƶ�㡢RF��Ϣ��������SDC*/
    stUeRfPowerFreq.CellUlFreq = (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stRssiValue.usCellUlFreq);
    stUeRfPowerFreq.UeRfPower = (TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stRssiValue.sUeRfPower);



    /*ʹ�������ϱ����������ݴ���TAFm*/
    MMA_ParaQueryReport(ClientId, OpId, TAF_PH_UE_RFPOWER_FREQ_PARA,TAF_ERR_NO_ERROR, (VOS_VOID*)&stUeRfPowerFreq);

    return;
}

/* MMA_PhoneRssiInd�Ƶ�Ԥ�������� */

VOS_UINT32 MMA_ConvertPhonePinType(TAF_PH_PIN_TYPE *penPinType)
{
    SC_VERIFY_SIMLOCK_RESULT_ENUM_UINT8 enSimLockResult;
    VOS_UINT32                          ulResult;
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId  = VOS_GetModemIDFromPid(WUEPS_PID_MMA);
    /* ��������У�飬��У�麯������ʧ�ܣ����յ�ǰ����PH_NET_PIN�������쳣���� */
    if (SC_ERROR_CODE_NO_ERROR != SC_PERS_VerifySimLock(&enSimLockResult, enModemId))
    {
        *penPinType = TAF_PHNET_PIN;
        return VOS_OK;
    }

    ulResult = VOS_OK;
    switch (enSimLockResult)
    {
        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PIN:
            *penPinType = TAF_PHNET_PIN;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_NET_PUK:
            *penPinType = TAF_PHNET_PUK;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PIN:
            *penPinType = TAF_PHNETSUB_PIN;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_NETSUB_PUK:
            *penPinType = TAF_PHNETSUB_PUK;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PIN:
            *penPinType = TAF_PHSP_PIN;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_PH_SP_PUK:
            *penPinType = TAF_PHSP_PUK;
            break;
        case SC_VERIFY_SIMLOCK_RESULT_READY:
            /* SIM��δ���������򷵻���������У��ͨ�� */
            break;
        default:
            /* �쳣���򷵻�����У��ʧ�� */
            ulResult = VOS_ERR;
            break;
    }

    return ulResult;
}
VOS_VOID MMA_PinQueryHandle(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_PH_PIN_CMD_TYPE                 ucPinCmdType,
    TAF_PH_PIN_CNF_STRU                *pstPinCnf
)
{
    VOS_UINT32                          ulResult;
    TAF_PH_ME_LOCK_STATUS               ucLockStatus;

    /*���ǲ�ѯPIN״̬���ߴ˷�֧��ͨ������usim�ṩ�Ĳ�ѯAPI����*/
    pstPinCnf->OpPinResult = (VOS_UINT8)NAS_USIMMAPI_GetPinStatus(&(pstPinCnf->PinType),
                                                            &(pstPinCnf->QueryResult.UsimmEnableFlg),
                                                            &(pstPinCnf->QueryResult.UsimmNeedType),
                                                            &(pstPinCnf->ucRemain));
    (VOS_VOID)NAS_USIMMAPI_GetPinRemainTime((USIMM_PIN_REMAIN_STRU *)(&(pstPinCnf->RemainTime)));


    ucLockStatus = MMA_GetMeLockStatus();

    /* ���ϲ�Ӧ��ΪAP-Modem����SIM��״̬ΪREADY(��TAF_SIM_PIN��TAF_SIM_PUK)����ΪAT^CPIN��AT+CPIN��ѯ���������ӵ�ǰ����״̬���ж��߼� */
    if ( (SYSTEM_APP_ANDROID == g_usMmaAppConfigSupportType)
      && (TAF_PIN_QUERY == ucPinCmdType)
      && (TAF_PH_ME_SIM_LOCK == ucLockStatus) )
    {
        /* ����USIMM��ȡ�Ŀ�״̬ΪPIN��PUK״̬����ֱ�ӷ��أ�����������У�� */
        if ((TAF_SIM_PIN != pstPinCnf->PinType) && (TAF_SIM_PUK != pstPinCnf->PinType))
        {
            ulResult = MMA_ConvertPhonePinType(&(pstPinCnf->PinType));
            /* ����+CPIN�����ERROR */
            if(VOS_OK != ulResult)
            {
                MMA_HandleEventError(usClientId, ucOpId, TAF_ERR_AT_ERROR, TAF_PH_EVT_OP_PIN_CNF);
                return;
            }
        }
    }

    /*��ѯAPIֱ�ӷ�����Ҫ��ֵ�������ϱ������ϱ�*/
    MMA_PinDataReport( pstPinCnf );

    return;
}
VOS_VOID MMA_PinHandle (VOS_UINT16 ClientId, VOS_UINT8 OpId,
                        TAF_PH_PIN_DATA_STRU stPinData)
{
    TAF_PH_PIN_CNF_STRU stPinTmp;
    TAF_PH_PIN_TIMECNF_STRU stPinRemainTime;
    VOS_UINT8           ucTi;
    VOS_UINT32          ulRet;
    VOS_UINT8           ucError = TAF_ERR_NO_ERROR;
    VOS_UINT32          ulResult;
    VOS_UINT8           ucSimType;

    TAF_SDC_USIM_STATUS_ENUM_UINT8  enUsimStatus;

    enUsimStatus = TAF_SDC_GetSimStatus();

    stPinTmp.CmdType  = stPinData.CmdType;
    stPinTmp.PinType  = stPinData.PinType;
    stPinTmp.ucRemain = MMA_PIN_REMAINS_UNINIT;

    /*����PIN����Ч���ж�*/

    if (TAF_SDC_USIM_STATUS_NO_PRESENT == enUsimStatus)
    {
        MMA_WARNINGLOG("MMA_PinHandle():WARNING:sim busy!");
        MMA_HandleEventError(ClientId,
                             OpId,
                             TAF_ERR_USIM_SIM_CARD_NOTEXIST,
                             TAF_PH_EVT_OP_PIN_CNF );
        return;
    }

    if ( (TAF_SDC_USIM_STATUS_READY_TIMEROUT == enUsimStatus)
      || (TAF_SDC_USIM_STATUS_BUTT == enUsimStatus))
    {
        MMA_WARNINGLOG("MMA_PinHandle():WARNING:sim busy!");
        MMA_HandleEventError(ClientId,
                             OpId,
                             TAF_ERR_SIM_BUSY,
                             TAF_PH_EVT_OP_PIN_CNF );
        return;
    }


    if ( MMA_SUCCESS != Mma_CheckPin(stPinData))
    {
        MMA_WARNINGLOG("MMA_PinHandle():WARNING:INPUT PIN is Error!");
        MMA_HandleEventError(ClientId,
                             OpId,
                             TAF_ERR_PARA_ERROR,
                             TAF_PH_EVT_OP_PIN_CNF );
        return;
    }

/* Modified by l00301449 for card multi type, 2015-5-25, begin */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#else
    /*��ȡ��ǰUSIM״̬*/
    if ( MMA_SUCCESS != MMA_PhoneUsimReady(MMA_CLIENTID_NONE, MMA_OP_ID_INTERNAL, TAF_TELE_PARA_BUTT))
    {
        /*��ӡ��Ϣ*/
        MMA_WARNINGLOG("MMA_PinHandle():WARNING: usim NOT ready!");
        /*���ɴ������ݰ�*/
        /*���ػ�ȡ������Ч*/
        /*���ز���ʧ��*/
        if ((TAF_PIN_VERIFY == stPinTmp.CmdType)
         || (TAF_PIN_UNBLOCK == stPinTmp.CmdType))
        {
            MMA_HandleEventError(ClientId,
                                 OpId,
                                 TAF_ERR_CMD_TYPE_ERROR,
                                 TAF_PH_EVT_OP_PIN_CNF );
        }
        else
        {
            MMA_HandleEventError(ClientId,
                                 OpId,
                                 TAF_ERR_SIM_FAIL,
                                 TAF_PH_EVT_OP_PIN_CNF );
        }
        return;
    }
#endif
    /* Modified by l00301449 for card multi type, 2015-5-25, end */

    if ( TAF_PIN_DISABLE == stPinTmp.CmdType )
    {
        ulRet = MMA_PhoneGetUsimType( &ucSimType );
        if ( (MMA_SUCCESS       == ulRet  )
           &&(MMA_USIM_TYPE_SIM == ucSimType)
           )
        {
            /*���SST�ļ��ж��Ƿ����DISABLE*/
            ulResult = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_CHV1_DISABLE);

            if (VOS_TRUE != ulResult)
            {
                /*��ӡ��Ϣ*/
                MMA_WARNINGLOG("MMA_PinHandle():WARNING: GET SST FAIL, OR Service not allowed!");
                ucError = TAF_ERR_UNSPECIFIED_ERROR;
            }
        }
        else if ( MMA_SUCCESS       != ulRet )
        {
            /*��ӡ��Ϣ*/
            MMA_WARNINGLOG("MMA_PinHandle():WARNING: Get uicc Tpye Fail!");
            ucError = TAF_ERR_UNSPECIFIED_ERROR;
        }
        else
        {
            MMA_NORMAILLOG("MMA_PinHandle():NORMAL: Usim return no error!");
        }
        if ( TAF_ERR_NO_ERROR != ucError )
        {
            MMA_HandleEventError(ClientId,
                                 OpId,
                                 ucError,
                                 TAF_PH_EVT_OP_PIN_CNF );
            return;
        }
    }

    /*�����PIN������ȫ�ֱ��������غ�����ѯ���洢CLIENTID*/
    /*��¼��ǰclientId��OpId*/
    if (MMA_SUCCESS != MMA_TiAlloc(TAF_MMA, ClientId, OpId, TAF_PH_EVT_OP_PIN_CNF, &ucTi))
    {   /*Ti����ʧ��*/
        MMA_WARNINGLOG("MMA_PinHandle():WARNING:ALLOC TI FAILED!");
        /*������*/
        MMA_HandleEventError(ClientId, OpId, TAF_ERR_TI_ALLOC_FAIL, TAF_PH_EVT_OP_PIN_CNF);
        return;
    }
    gstMmaValue.stOpPinData.ClientId        = ClientId;
    gstMmaValue.stOpPinData.OpId            = OpId;
    gstMmaValue.stOpPinData.stMmaPinData    = stPinData;

    if ((TAF_PIN_QUERY == stPinData.CmdType) || (TAF_PIN2_QUERY == stPinData.CmdType))
    {
        MMA_PinQueryHandle(ClientId, OpId, stPinData.CmdType, &stPinTmp);
    }
    else if(TAF_PIN_RemainTime == stPinData.CmdType)
    {
        stPinRemainTime.CmdType = TAF_PIN_RemainTime;

        stPinRemainTime.PinType = USIMM_PIN;

        stPinRemainTime.OpPinResult =  (VOS_UINT8)NAS_USIMMAPI_GetPinStatus(&(stPinRemainTime.PinType),
                                                       &(stPinRemainTime.QueryResult.UsimmEnableFlg),
                                                       &(stPinRemainTime.QueryResult.UsimmNeedType),
                                                       &(stPinRemainTime.ucPIN1Remain));    /* Read PIN1 remain time */

        stPinRemainTime.PinType = USIMM_PUK;

        stPinRemainTime.OpPinResult =  (VOS_UINT8)NAS_USIMMAPI_GetPinStatus(&(stPinRemainTime.PinType),
                                                       &(stPinRemainTime.QueryResult.UsimmEnableFlg),
                                                       &(stPinRemainTime.QueryResult.UsimmNeedType),
                                                       &(stPinRemainTime.ucPUK1Remain));    /* Read PUK1 remain time */

        stPinRemainTime.PinType = USIMM_PIN2;

        stPinRemainTime.OpPinResult =  (VOS_UINT8)NAS_USIMMAPI_GetPinStatus(&(stPinRemainTime.PinType),
                                                       &(stPinRemainTime.QueryResult.UsimmEnableFlg),
                                                       &(stPinRemainTime.QueryResult.UsimmNeedType),
                                                       &(stPinRemainTime.ucPIN2Remain));    /* Read PUK1 remain time */

        stPinRemainTime.PinType = USIMM_PUK2;

        stPinRemainTime.OpPinResult =  (VOS_UINT8)NAS_USIMMAPI_GetPinStatus(&(stPinRemainTime.PinType),
                                                       &(stPinRemainTime.QueryResult.UsimmEnableFlg),
                                                       &(stPinRemainTime.QueryResult.UsimmNeedType),
                                                       &(stPinRemainTime.ucPUK2Remain));    /* Read PUK1 remain time */

        MMA_PhonePinRemainTimeReport( &stPinRemainTime );
    }
    else
    {
        /*��USIM����ʵ��*/
        /*������ʱ��*/
        if( VOS_OK != NAS_StartRelTimer( &(g_MmaSimTimer[0].MmaHTimer),
                                         WUEPS_PID_MMA,
                                         MMA_PIN_HANDLE_TIME,
                                         TAF_MMA,
                                         TAF_USIM_OPPIN,
                                         VOS_RELTIMER_NOLOOP ) )
        {
            MMA_ERRORLOG("MMA_PinHandle():ERROR:Start Timer Error!");
            /*���ز���ʧ��*/
            /*������*/
            MMA_HandleEventError(ClientId, OpId, TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_EVT_OP_PIN_CNF);
            g_MmaSimTimer[0].ucTimerStatus     = MMA_TIMER_ERROR;
            return;
        }
        g_MmaSimTimer[0].ucTimerStatus         = MMA_TIMER_RUN;

        /*��ѯϵͳ��ǰ��Ҫ��֤��PIN������,�����������PIN����������������������*/
        (VOS_VOID)NAS_USIMMAPI_GetPinStatus(&(stPinData.PinType),
                              &stPinTmp.QueryResult.UsimmEnableFlg,
                              &stPinTmp.QueryResult.UsimmNeedType,
                              &stPinTmp.ucRemain);
        /*����USIM�ṩ�Ĳ�������PIN���в���*/
        /* BEGIN: Modified by liuyang id:48197, 2006/3/16   PN:A32D02412*/

        if(USIMM_API_SUCCESS != NAS_USIMMAPI_PinReq(WUEPS_PID_MMA,
                                            stPinData.CmdType,
                                            stPinData.PinType,
                                            stPinData.aucOldPin,
                                            stPinData.aucNewPin))

        {
            MMA_WARNINGLOG("MMA_PinHandle():WARNING:Invoke USIMM Function Fail!");
            /*ֹͣ��ʱ��*/

            if (VOS_OK != NAS_StopRelTimer(WUEPS_PID_MMA, TAF_USIM_OPPIN, &(g_MmaSimTimer[0].MmaHTimer)))
            {
                MMA_WARNINGLOG("MMA_PinHandle():WARNING:NAS_StopRelTimer failed!");
            }

            /*����ֹͣ��ʱ����־*/
            g_MmaSimTimer[0].ucTimerStatus    = MMA_TIMER_STOP;
            /*�ϱ�����*/
            MMA_HandleEventError(ClientId, OpId, TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_EVT_OP_PIN_CNF);
            MMA_WARNINGLOG("MMA_PinHandle():WARNING:invoke USIM Api Fail!");

            return;
        }

    }
    return;
}

VOS_UINT32 MMA_VerifyOperatorLockPwd(VOS_UINT8 *pucPwd)
{
    VOS_UINT8   aucTmpImei[TAF_PH_IMEI_LEN];

    PS_MEM_CPY(aucTmpImei, g_aucMmaImei, TAF_PH_IMEI_LEN-1);

    aucTmpImei[TAF_PH_IMEI_LEN -1] = 0;


    if (VOS_FALSE == VerifySL((char *)pucPwd, (char *)aucTmpImei))
    {
        return VOS_ERR;
    }

    return VOS_OK;


}

VOS_VOID MMA_MePersonalCnfReport(VOS_UINT16                        ClientId,
                                VOS_UINT8                         OpId,
                                TAF_PH_ME_PERSONLISATION_CNF_STRU stMePersonalCnf)
{
    TAF_PHONE_EVENT_INFO_STRU   *pstPhoneEvent;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_MePersonalCnfReport:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    pstPhoneEvent->ClientId = ClientId;
    pstPhoneEvent->OpId = OpId;
    pstPhoneEvent->PhoneEvent = TAF_PH_EVT_ME_PERSONALISATION_CNF;

    pstPhoneEvent->MePersonalisation = stMePersonalCnf;

    /* ���õ绰�����ϱ����� */
    MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

}
VOS_UINT32 MMA_CheckMePersonalisationPwd(TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    VOS_UINT8       aucPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +1];
    VOS_UINT32      ulRslt;
    VOS_UINT16      usDataLen = TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX;


    PS_MEM_SET(aucPwd, 0x00, sizeof(aucPwd));

    switch(stMePersonalData.MePersonalType)
    {
        case TAF_SIM_PERSONALISATION:
            ulRslt = NV_Read(en_NV_Item_Sim_Personalisation_Pwd,
                             aucPwd,
                             usDataLen);

            if (NV_OK != ulRslt)
            {
                return TAF_PH_ME_PERSONALISATION_ERROR;
            }
            PS_MEM_CPY(g_MmaNewValue.aucPwd, aucPwd, TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX);

            ulRslt = (VOS_UINT32)VOS_MemCmp(stMePersonalData.aucOldPwd,
                                aucPwd,
                                TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX);
            if (VOS_OK != ulRslt)
            {
                return TAF_PH_ME_PERSONALISATION_WRONG_PWD;
            }
            break;
        case TAF_OPERATOR_PERSONALISATION:
            if (VOS_OK != MMA_VerifyOperatorLockPwd(stMePersonalData.aucOldPwd))
            {
                return TAF_PH_ME_PERSONALISATION_WRONG_PWD;
            }
            break;
        default:
            return TAF_PH_ME_PERSONALISATION_WRONG_PARA;
    }

    return TAF_PH_ME_PERSONALISATION_OK;
}




VOS_VOID MMA_MePersonlisationSet(VOS_UINT16 ClientId,
                                VOS_UINT8 OpId,
                                TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    TAF_PH_ME_PERSONLISATION_CNF_STRU stMePersonalCnf;
    VOS_UINT32          ulResult;
    TAF_UINT8           aucSimPersonalisationStr[TAF_MAX_IMSI_LEN + 1];


    PS_MEM_SET(&stMePersonalCnf, 0x00, sizeof(stMePersonalCnf));

    stMePersonalCnf.CmdType  = stMePersonalData.CmdType;
    stMePersonalCnf.MePersonalisatonType  = stMePersonalData.MePersonalType;

    switch(stMePersonalData.MePersonalType)
    {
        case TAF_SIM_PERSONALISATION:
            /*��������Ƿ���ȷ*/
            ulResult = MMA_CheckMePersonalisationPwd(stMePersonalData);


            /*������ȷ�������õ�ǰ��IMSI String*/
            if (TAF_PH_ME_PERSONALISATION_OK == ulResult)
            {
                aucSimPersonalisationStr[0] = (VOS_UINT8)stMePersonalData.unMePersonalisationSet.SimPersionalisationStr.DataLen;
                (VOS_VOID)VOS_MemCpy(aucSimPersonalisationStr + 1,
                           stMePersonalData.unMePersonalisationSet.SimPersionalisationStr.aucSimPersonalisationStr,
                           aucSimPersonalisationStr[0]);

                ulResult = NV_Write(en_NV_Item_Sim_Personalisation_Imsi_Str,
                                    aucSimPersonalisationStr,
                                    aucSimPersonalisationStr[0] + 1);

                if (NV_OK != ulResult)
                {
                    ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
                }
            }
            break;

        default:
            ulResult = TAF_PH_ME_PERSONALISATION_WRONG_PARA;
            break;
    }

    stMePersonalCnf.OpRslt = (VOS_UINT8)ulResult;

    MMA_MePersonalCnfReport(ClientId, OpId, stMePersonalCnf);

}

VOS_VOID TAF_UsimmStatusCardUnlocked()
{
    VOS_UINT8                           ucUsimStatus;
    VOS_UINT8                           ucUsimType;
    USIMM_CARDSTATUS_IND_STRU          *pUsimMsg = VOS_NULL_PTR;


    /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
    ucUsimStatus = USIMM_CARD_SERVIC_BUTT;
    ucUsimType   = USIMM_CARD_NOCARD;
    (VOS_VOID)MMA_GetUsimStatusFromUsim(&ucUsimStatus,&ucUsimType);
    /* Modified by h00313353 for iteration 9, 2015-2-9, end */

    /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
    if (USIMM_CARD_SERVIC_AVAILABLE != ucUsimStatus)
    /* Modified by h00313353 for iteration 9, 2015-2-9, end */
    {
        return;
    }
    pUsimMsg = (USIMM_CARDSTATUS_IND_STRU *)PS_ALLOC_MSG(MAPS_PIH_PID, sizeof(USIMM_CARDSTATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pUsimMsg)
    {
        return;
    }

    MMA_MEM_SET(pUsimMsg,0x00,sizeof(USIMM_CARDSTATUS_IND_STRU));

    pUsimMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;

    pUsimMsg->ulSenderPid     = MAPS_PIH_PID;

    pUsimMsg->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pUsimMsg->ulReceiverPid                 = WUEPS_PID_MMA;
    /* Deleted by h00313353 for iteration 9, 2015-2-10, begin */
    /* pUsimMsg->ucIMSILen                     = USIMM_EF_IMSI_LEN; */
    /* Deleted by h00313353 for iteration 9, 2015-2-10, end */
    pUsimMsg->stUsimSimInfo.enCardService   = ucUsimStatus;
    pUsimMsg->stUsimSimInfo.enCardType      = ucUsimType;
    pUsimMsg->ulMsgName                     = USIMM_CARDSTATUS_IND;
    /* Deleted by h00313353 for iteration 9, 2015-2-10, begin
    if (USIMM_API_SUCCESS != NAS_USIMMAPI_GetCardIMSI(pUsimMsg->aucIMSI))
    {
        NAS_WARNING_LOG(MAPS_PIH_PID, "TAF_UsimmStatusCardUnlocked():WARNING:NAS_USIMMAPI_GetCardIMSI FIAL");
    }
    Deleted by h00313353 for iteration 9, 2015-2-10, end */


    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_USIM, pUsimMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_USIM, "TAF_UsimmStatusCardUnlocked():WARNING:SEND MSG FIAL");
    }

    return;
}


VOS_UINT32   MMA_OperatorPersonlisationVerify(
TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucRemainTimes;
    VOS_UINT8                           ucLockStatus;

    TAF_CUSTOM_CARDLOCK_STATUS_STRU     stCardLockStatus;
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU  stSimLockMaxTimes;


    PS_MEM_SET(&stSimLockMaxTimes, 0x00, sizeof(stSimLockMaxTimes));
    PS_MEM_SET(&stCardLockStatus,  0x00, sizeof(stCardLockStatus));

    /* ��ȡ��ǰ����״̬��ʣ����� */
    ulResult = NV_Read(en_NV_Item_CardlockStatus,
                       &stCardLockStatus,
                       sizeof(stCardLockStatus));
    if (NV_OK != ulResult)
    {
        MMA_ERRORLOG("MMA_OperatorPersonlisationVerify:ERROR:Read en_NV_Item_CardlockStatus Fail.");
        return TAF_PH_ME_PERSONALISATION_OP_NOT_ALLOW;
    }
    g_MmaNewValue.stCardLockStatus = stCardLockStatus;

    ulResult = NV_Read(en_NV_Item_CustomizeSimLockMaxTimes,
                      &stSimLockMaxTimes,
                      sizeof(stSimLockMaxTimes));
    if (NV_OK != ulResult)
    {
        g_MmaNewValue.stSimLockMaxTimes.ulStatus = VOS_FALSE;
        g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
    }
    else
    {
        if (VOS_FALSE == stSimLockMaxTimes.ulStatus)
        {
            g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
        }
        else
        {
            g_MmaNewValue.stSimLockMaxTimes = stSimLockMaxTimes;
        }
    }

    if (VOS_FALSE == stCardLockStatus.ulStatus)
    {
        MMA_ERRORLOG("MMA_OperatorPersonlisationVerify:ERROR:Status no correct.");
        return TAF_PH_ME_PERSONALISATION_OP_NOT_ALLOW;
    }

    ucLockStatus = (VOS_UINT8)stCardLockStatus.enCardlockStatus;
    ucRemainTimes  = (VOS_UINT8)stCardLockStatus.ulRemainUnlockTimes;

    /* �Ѿ�������������״̬������У��  */

    if (( ( TAF_OPERATOR_UNLOCK_TIMES_MIN == ucRemainTimes )
           &&( TAF_OPERATOR_LOCK_LOCKED == ucLockStatus))
          ||(TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE == ucLockStatus) )
    {
        ulResult = TAF_PH_ME_PERSONALISATION_OP_NOT_ALLOW;
        MMA_ERRORLOG("MMA_OperatorPersonlisationVerify:card locked already.");
    }
    else
    {
        /* ��������Ƿ���ȷ */
        ulResult = MMA_CheckMePersonalisationPwd(stMePersonalData);

        /* ������ȷ */
        if (TAF_PH_ME_PERSONALISATION_OK == ulResult)
        {
            MMA_INFOLOG("MMA_OperatorPersonlisationVerify:INFO:MMA_CheckMePersonalisationPwd Return OK.");
            /* g_stMmaMePersonalisationStatus ���ݸ��º��� */



            /* һ��У��ͨ���������ý������״̬  */
            stCardLockStatus.enCardlockStatus = TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE;
            stCardLockStatus.ulRemainUnlockTimes = stSimLockMaxTimes.ulLockMaxTimes;

            ulResult = NV_Write(en_NV_Item_CardlockStatus,
                                &stCardLockStatus,
                                sizeof(stCardLockStatus));
            if (NV_OK != ulResult)
            {
                MMA_ERRORLOG("MMA_OperatorPersonlisationVerify:ERROR:write en_NV_Item_CardlockStatus Fail.");
                return TAF_PH_ME_PERSONALISATION_ERROR;
            }

            /*nvд�ɹ�ʱ�Ŷ��䱸��*/
            /*lint -e774*/
            ulResult = NV_SpecialNvIdBackup(en_NV_Item_CardlockStatus,
                                           &stCardLockStatus,
                                           sizeof(stCardLockStatus));
            if (NV_OK != ulResult)
            {
                MMA_WARNINGLOG("MMA_OperatorPersonlisationVerify: WARNING:write Special en_NV_Item_CardlockStatus Fail.");
                return TAF_PH_ME_PERSONALISATION_ERROR;
            }
            /*lint +e774*/

            /* �������󴥷���������״̬�仯ָʾ��Ϣ */
            TAF_MMA_SndSimlocakStatusChangeInd();

            /* �������״̬ */
            g_stMmaMePersonalisationStatus.SimLockStatus
                                 = MMA_SIM_LOCK_IS_VERIFY;

            g_stMmaMePersonalisationStatus.stCardLockInfo.RemainTimes
                                 = stSimLockMaxTimes.ulLockMaxTimes;

            ulResult = TAF_PH_ME_PERSONALISATION_OK;
        }
        else if (TAF_PH_ME_PERSONALISATION_WRONG_PWD == ulResult)
        {
            MMA_WARNINGLOG("MMA_OperatorPersonlisationVerify:WARNING:MMA_CheckMePersonalisationPwd Return error.");
            stCardLockStatus.ulRemainUnlockTimes--;
            g_stMmaMePersonalisationStatus.stCardLockInfo.RemainTimes
                                    = ucRemainTimes;

            if (TAF_OPERATOR_UNLOCK_TIMES_MIN == stCardLockStatus.ulRemainUnlockTimes)
            {
                stCardLockStatus.enCardlockStatus = TAF_OPERATOR_LOCK_LOCKED;
            }

            /* ����RemainTimes������״̬��NV�� */
            ulResult = NV_Write(en_NV_Item_CardlockStatus,
                         &stCardLockStatus,
                         sizeof(stCardLockStatus));
            if (NV_WRITE_SECURE_FAIL == ulResult)
            {
                /* �������ʧ�ܣ��ָ�ԭ����ֵ */
                g_stMmaMePersonalisationStatus.stCardLockInfo.RemainTimes++;
            }



            if (NV_OK == ulResult)
            {
                /*nvд�ɹ�ʱ�Ŷ��䱸��*/
                /*lint -e774*/
                ulResult = NV_SpecialNvIdBackup(en_NV_Item_CardlockStatus,
                                               &stCardLockStatus,
                                               sizeof(stCardLockStatus));
                if (NV_OK != ulResult)
                {
                    MMA_WARNINGLOG("MMA_OperatorPersonlisationVerify: WARNING:write en_NV_Item_CardlockStatus Fail.");
                }
                /*lint +e774*/
            }


            ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
        }
        else
        {
            ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
        }
    }

    return ulResult;
}


VOS_VOID MMA_MePersonlisationVerify(VOS_UINT16   ClientId,
                                   VOS_UINT8    OpId,
                                   TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    TAF_PH_ME_PERSONLISATION_CNF_STRU   stMePersonalCnf;
    VOS_UINT32                          ulResult;


    PS_MEM_SET(&stMePersonalCnf, 0x00, sizeof(stMePersonalCnf));

    stMePersonalCnf.CmdType  = stMePersonalData.CmdType;
    stMePersonalCnf.MePersonalisatonType  = stMePersonalData.MePersonalType;

    ulResult = MMA_GetMeLockStatus();

    if (TAF_PH_ME_SIM_LOCK == ulResult)
    {
        switch(stMePersonalData.MePersonalType)
        {
            case TAF_SIM_PERSONALISATION:
                /* ��������Ƿ���ȷ */
                ulResult = MMA_CheckMePersonalisationPwd(stMePersonalData);
                /* ������ȷ�������õ�ǰ��IMSI String */
                if (TAF_PH_ME_PERSONALISATION_OK == ulResult)
                {
                    /* �������״̬ */
                    g_stMmaMePersonalisationStatus.SimLockStatus = MMA_SIM_LOCK_IS_VERIFY;
                }
                break;
            case TAF_OPERATOR_PERSONALISATION:
                ulResult = MMA_OperatorPersonlisationVerify( stMePersonalData );
                break;
            default:
                ulResult = TAF_PH_ME_PERSONALISATION_WRONG_PARA;
                break;
        }
    }
    else if (TAF_PH_ME_NO_SIM == ulResult)
    {
        if ( TAF_OPERATOR_PERSONALISATION == stMePersonalData.MePersonalType )
        {
            ulResult = MMA_OperatorPersonlisationVerify( stMePersonalData );
        }
        else
        {
            ulResult = TAF_PH_ME_PERSONALISATION_NO_SIM;
        }
    }
    else
    {
        ulResult = TAF_PH_ME_PERSONALISATION_OP_NOT_ALLOW;
    }
    stMePersonalCnf.OpRslt = (VOS_UINT8)ulResult;

    MMA_MePersonalCnfReport(ClientId, OpId, stMePersonalCnf);

}
VOS_VOID MMA_MePersonlisationPwdChange(VOS_UINT16   ClientId,
                                      VOS_UINT8    OpId,
                                      TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    TAF_PH_ME_PERSONLISATION_CNF_STRU stMePersonalCnf;
    VOS_UINT32          ulResult;


    PS_MEM_SET(&stMePersonalCnf, 0x00, sizeof(stMePersonalCnf));


    stMePersonalCnf.CmdType  = stMePersonalData.CmdType;
    stMePersonalCnf.MePersonalisatonType  = stMePersonalData.MePersonalType;

    switch(stMePersonalData.MePersonalType)
    {
        case TAF_SIM_PERSONALISATION:
            /*��������Ƿ���ȷ*/
            ulResult = MMA_CheckMePersonalisationPwd(stMePersonalData);


            /*������ȷ���������µ�����*/
            if (TAF_PH_ME_PERSONALISATION_OK == ulResult)
            {
                ulResult = NV_Write(en_NV_Item_Sim_Personalisation_Pwd,
                                    stMePersonalData.aucNewPwd,
                                    TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX);

                if (NV_OK != ulResult)
                {
                    ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
                }
            }
            break;

        default:
            ulResult = TAF_PH_ME_PERSONALISATION_WRONG_PARA;
            break;
    }

    stMePersonalCnf.OpRslt = (VOS_UINT8)ulResult;;

    MMA_MePersonalCnfReport(ClientId, OpId, stMePersonalCnf);

}


VOS_VOID MMA_MePersonlisationActive(VOS_UINT16   ClientId,
                                   VOS_UINT8    OpId,
                                   TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    TAF_PH_ME_PERSONLISATION_CNF_STRU   stMePersonalCnf;
    VOS_UINT32                          ulResult;
    NAS_MMA_ME_PERSONAL_ACT_FLAG_STRU   stMePersonActFlag;
    VOS_UINT16                          usDataLen = TAF_MAX_IMSI_LEN + 1;
    VOS_UINT32                          ulNvLength;
    TAF_UINT8                           aucSimPersonalisationStr[TAF_MAX_IMSI_LEN + 1];

    PS_MEM_SET(&stMePersonalCnf,         0x00, sizeof(stMePersonalCnf));
    PS_MEM_SET(aucSimPersonalisationStr, 0x00, sizeof(aucSimPersonalisationStr));
    stMePersonActFlag.usMePersonalActFlag = TAF_ME_PERSONALISATION_ACTIVE_STATUS;
    ulNvLength = 0;

    stMePersonalCnf.CmdType  = stMePersonalData.CmdType;
    stMePersonalCnf.MePersonalisatonType  = stMePersonalData.MePersonalType;

    switch(stMePersonalData.MePersonalType)
    {
        case TAF_SIM_PERSONALISATION:
            /*��������Ƿ���ȷ*/
            ulResult = MMA_CheckMePersonalisationPwd(stMePersonalData);
            if (TAF_PH_ME_PERSONALISATION_OK != ulResult)
            {
                break;
            }

            /*��鵱ǰ�Ƿ����趨���ִ����ִ�Ϊ0ʱ�����ܼ���*/
            ulResult = NV_Read(en_NV_Item_Sim_Personalisation_Imsi_Str,
                               aucSimPersonalisationStr,
                               usDataLen);
            if (NV_OK != ulResult)
            {
                ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
                break;
            }
            else
            {
                if (0 == aucSimPersonalisationStr[0])
                {
                    ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
                    break;
                }
            }

            /*���ü���״̬*/
            (VOS_VOID)NV_GetLength(en_NV_Item_Me_Personalisation_Active_Flag, &ulNvLength);
            ulResult = NV_Write(en_NV_Item_Me_Personalisation_Active_Flag,
                                &stMePersonActFlag,
                                ulNvLength);
            if (NV_OK != ulResult)
            {
                ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
            }
            break;

        default:
            ulResult = TAF_PH_ME_PERSONALISATION_WRONG_PARA;
            break;
    }

    stMePersonalCnf.OpRslt = (VOS_UINT8)ulResult;

    MMA_MePersonalCnfReport(ClientId, OpId, stMePersonalCnf);
}
VOS_VOID MMA_MePersonlisationDeactive(VOS_UINT16   ClientId,
                                     VOS_UINT8    OpId,
                                     TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    TAF_PH_ME_PERSONLISATION_CNF_STRU   stMePersonalCnf;
    VOS_UINT32                          ulResult;
    NAS_MMA_ME_PERSONAL_ACT_FLAG_STRU   stMePersonActFlag;

    stMePersonActFlag.usMePersonalActFlag = TAF_ME_PERSONALISATION_DEACTIVE_STATUS;


    PS_MEM_SET(&stMePersonalCnf, 0x00, sizeof(stMePersonalCnf));

    stMePersonalCnf.CmdType  = stMePersonalData.CmdType;
    stMePersonalCnf.MePersonalisatonType  = stMePersonalData.MePersonalType;

    switch(stMePersonalData.MePersonalType)
    {
        case TAF_SIM_PERSONALISATION:
            /*��������Ƿ���ȷ*/
            ulResult = MMA_CheckMePersonalisationPwd(stMePersonalData);

            /*������ȷ��ȥ������������*/
            if (TAF_PH_ME_PERSONALISATION_OK == ulResult)
            {
                ulResult = NV_Write(en_NV_Item_Me_Personalisation_Active_Flag,
                                    &stMePersonActFlag,
                                    sizeof(NAS_MMA_ME_PERSONAL_ACT_FLAG_STRU));
                if (NV_OK != ulResult)
                {
                    ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
                }
            }
            break;

        default:
            ulResult = TAF_PH_ME_PERSONALISATION_WRONG_PARA;
            break;
    }

    stMePersonalCnf.OpRslt = (VOS_UINT8)ulResult;;

    MMA_MePersonalCnfReport(ClientId, OpId, stMePersonalCnf);
}


VOS_VOID MMA_MePersonlisationRetrieve(VOS_UINT16   ClientId,
                                     VOS_UINT8    OpId,
                                     TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    TAF_PH_ME_PERSONLISATION_CNF_STRU   stMePersonalCnf;
    VOS_UINT32                          ulResult = TAF_PH_ME_PERSONALISATION_OK;
    VOS_UINT16                          usDataLen = TAF_MAX_IMSI_LEN + 1;
    TAF_UINT8                           aucSimPersonalisationStr[TAF_MAX_IMSI_LEN + 1];


    PS_MEM_SET(&stMePersonalCnf,         0x00, sizeof(stMePersonalCnf));
    PS_MEM_SET(aucSimPersonalisationStr, 0x00, sizeof(aucSimPersonalisationStr));

    stMePersonalCnf.CmdType  = stMePersonalData.CmdType;
    stMePersonalCnf.MePersonalisatonType  = stMePersonalData.MePersonalType;

    switch(stMePersonalData.MePersonalType)
    {
        case TAF_SIM_PERSONALISATION:
            /*��������Ƿ���ȷ*/
            ulResult = MMA_CheckMePersonalisationPwd(stMePersonalData);

            /*������ȷ����ȡ�������ִ�*/
            if (TAF_PH_ME_PERSONALISATION_OK == ulResult)
            {
                ulResult = NV_Read(en_NV_Item_Sim_Personalisation_Imsi_Str,
                                   aucSimPersonalisationStr,
                                   usDataLen);
                if (NV_OK != ulResult)
                {
                    if (ulResult == NV_ID_NOT_EXIST)
                    {
                        stMePersonalCnf.unReportContent.SimPersionalisationStr.DataLen = 0;
                        ulResult = TAF_PH_ME_PERSONALISATION_OK;
                    }
                    else
                    {
                        ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
                    }
                }
                else
                {
                    stMePersonalCnf.unReportContent.SimPersionalisationStr.DataLen = aucSimPersonalisationStr[0];
                    (VOS_VOID)VOS_MemCpy(stMePersonalCnf.unReportContent.SimPersionalisationStr.aucSimPersonalisationStr,
                               aucSimPersonalisationStr + 1,
                               aucSimPersonalisationStr[0]
                               );
                }
            }
            break;

        default:
            ulResult = TAF_PH_ME_PERSONALISATION_WRONG_PARA;
            break;
    }

    stMePersonalCnf.OpRslt = (VOS_UINT8)ulResult;;

    MMA_MePersonalCnfReport(ClientId, OpId, stMePersonalCnf);

}


VOS_BOOL MMA_IsSimLockPlmnInfoValid(VOS_VOID)
{
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU  stSimLockPlmnInfo;
    VOS_UINT32                          i;


    PS_MEM_SET(&stSimLockPlmnInfo, 0x00, sizeof(stSimLockPlmnInfo));

    if (NV_OK != NV_Read(en_NV_Item_CustomizeSimLockPlmnInfo,
                       &stSimLockPlmnInfo,
                       sizeof(stSimLockPlmnInfo)))
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == stSimLockPlmnInfo.ulStatus)
    {
        return VOS_FALSE;
    }

    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        if (0xAA == stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin[0])
        {
            continue;
        }

        break;
    }

    /* ���ÿһ���PLMN��������Ч�ģ���ô����û����Ч��PLMN��Ϣ */
    if (TAF_MAX_SIM_LOCK_RANGE_NUM == i)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 MMA_GetCardLockInfo(TAF_OPERATOR_LOCK_INFO_STRU *pstOperatorLockInfo)
{

    VOS_UINT32                          ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
    TAF_CUSTOM_CARDLOCK_STATUS_STRU     stCardLockStatus;
    TAF_OPERATOR_LOCK_INFO_STRU         *pstCardLockInfo;
    VOS_UINT8                           ucSimStatus;


    PS_MEM_SET(&stCardLockStatus, 0x00, sizeof(stCardLockStatus));

    if (VOS_NULL_PTR == pstOperatorLockInfo)
    {
        return ulResult;
    }

    ulResult = TAF_PH_ME_PERSONALISATION_OK;
    pstCardLockInfo = &(g_stMmaMePersonalisationStatus.stCardLockInfo);

    if (NV_OK == NV_Read(en_NV_Item_CardlockStatus,
                            &stCardLockStatus,sizeof(stCardLockStatus)))
    {

        if (VOS_TRUE != stCardLockStatus.ulStatus)
        {
            /*������Ӫ����״̬*/
            pstCardLockInfo->OperatorLockStatus = TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE;
        }
        else
        {
            /*������Ӫ����״̬*/
            pstCardLockInfo->OperatorLockStatus= stCardLockStatus.enCardlockStatus;

            if (MMA_SIM_LOCK_IS_VERIFY == g_stMmaMePersonalisationStatus.SimLockStatus)
            {
                pstCardLockInfo->OperatorLockStatus = TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE;
            }
        }

        /* ����ʣ����� */
        if (TAF_OPERATOR_LOCK_LOCKED == pstCardLockInfo->OperatorLockStatus)
        {
            pstCardLockInfo->RemainTimes = 0;
        }
        else if (TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE == pstCardLockInfo->OperatorLockStatus)
        {
            pstCardLockInfo->RemainTimes = g_MmaNewValue.stSimLockMaxTimes.ulLockMaxTimes;
        }
        else
        {
            pstCardLockInfo->RemainTimes = stCardLockStatus.ulRemainUnlockTimes;
        }


    }
    else
    {
        pstCardLockInfo->OperatorLockStatus = TAF_OPERATOR_LOCK_LOCKED;
        pstCardLockInfo->RemainTimes = 0;
    }

    /* �����ǰ�޿�������NV��en_NV_Item_CustomizeSimLockPlmnInfo�е�
       PLMN��Ч��ʱ�� */
    (VOS_VOID)MMA_PhoneGetUsimStatus(&ucSimStatus);
    if ((VOS_FALSE == MMA_IsSimLockPlmnInfoValid())
      &&(MMA_USIM_ABSENT == ucSimStatus))
    {
        pstCardLockInfo->OperatorLockStatus = TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE;
    }

    /*Ŀǰ���������ݿ���ʹ��^cardlock�������ʱ���ϱ���
      operatorû��ʹ�ã�����������ѳ�����0*/
    pstCardLockInfo->OperatorLen = 0;

    g_MmaNewValue.stCardLockStatus = stCardLockStatus;

    PS_MEM_CPY(pstOperatorLockInfo,
                   pstCardLockInfo,
                       sizeof(TAF_OPERATOR_LOCK_INFO_STRU));

    return ulResult;

}




VOS_VOID MMA_MePersonlisationQuery(VOS_UINT16   ClientId,
                                  VOS_UINT8    OpId,
                                  TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{
    TAF_PH_ME_PERSONLISATION_CNF_STRU   stMePersonalCnf;
    VOS_UINT32                          ulResult;
    NAS_MMA_ME_PERSONAL_ACT_FLAG_STRU   stMePersonActFlag;
    VOS_UINT16                          usDataLen = 2;
    VOS_UINT8                           ucSimStatus;

    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;

    pucImsi = TAF_SDC_GetSimImsi();


    stMePersonActFlag.usMePersonalActFlag = VOS_FALSE;

    PS_MEM_SET(&stMePersonalCnf,0,sizeof(TAF_PH_ME_PERSONLISATION_CNF_STRU));
    stMePersonalCnf.CmdType  = stMePersonalData.CmdType;
    stMePersonalCnf.MePersonalisatonType  = stMePersonalData.MePersonalType;

    (VOS_VOID)MMA_PhoneGetUsimStatus(&ucSimStatus);

    if (MMA_USIM_PRESENT != ucSimStatus)
    {
        if (MMA_USIM_ABSENT == ucSimStatus)
        {
            ulResult = MMA_GetCardLockInfo(&(stMePersonalCnf.unReportContent.OperatorLockInfo));
        }
        else
        {
            ulResult = TAF_PH_ME_PERSONALISATION_NO_SIM;
        }
    }
    else if (MMA_QUICK_START_ENABLE == gstMmaValue.ulQuickStartFlg)
    {
        ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
    }
    else if (MMA_NONEED_PIN1 != MMA_CheckPin1SatusSimple())
    {
        ulResult = MMA_GetCardLockInfo(&(stMePersonalCnf.unReportContent.OperatorLockInfo));
    }
    else
    {
        if (USIMM_API_SUCCESS == NAS_USIMMAPI_GetCardIMSI(pucImsi))
        {
            (VOS_VOID)MMA_CheckMePersonalisationStatus();

            switch(stMePersonalData.MePersonalType)
            {
                /* this case is  used for clck query  */
                case TAF_SIM_PERSONALISATION:
                    ulResult = NV_Read(en_NV_Item_Me_Personalisation_Active_Flag,
                                       &stMePersonActFlag,
                                       usDataLen);
                    if (NV_OK != ulResult)
                    {
                        ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
                        break;
                    }
                    g_MmaNewValue.usSimMePersonalisationActFlag = stMePersonActFlag.usMePersonalActFlag;

                    ulResult = TAF_PH_ME_PERSONALISATION_OK;
                    stMePersonalCnf.ActiveStatus = (VOS_UINT8)(stMePersonActFlag.usMePersonalActFlag);
                    break;
                case TAF_OPERATOR_PERSONALISATION:
                    ulResult = MMA_GetCardLockInfo(&(stMePersonalCnf.unReportContent.OperatorLockInfo));
                    break;
                default:
                    ulResult = TAF_PH_ME_PERSONALISATION_WRONG_PARA;
                    break;
            }
        }
        else
        {
            ulResult = TAF_PH_ME_PERSONALISATION_ERROR;
        }
    }
    stMePersonalCnf.OpRslt              = (VOS_UINT8)ulResult;
    MMA_MePersonalCnfReport(ClientId, OpId, stMePersonalCnf);
}
VOS_VOID MMA_MePersonalisationHandle(VOS_UINT16 ClientId,
                                     VOS_UINT8 OpId,
                                     TAF_ME_PERSONALISATION_DATA_STRU stMePersonalData)
{


    switch (stMePersonalData.CmdType)
    {
        case  TAF_ME_PERSONALISATION_SET:
            MMA_MePersonlisationSet(ClientId, OpId, stMePersonalData);
            break;

        case TAF_ME_PERSONALISATION_VERIFY:
            MMA_MePersonlisationVerify(ClientId, OpId, stMePersonalData);
            break;

        case TAF_ME_PERSONALISATION_PWD_CHANGE:
            MMA_MePersonlisationPwdChange(ClientId, OpId, stMePersonalData);
            break;

        case TAF_ME_PERSONALISATION_ACTIVE:
            MMA_MePersonlisationActive(ClientId, OpId, stMePersonalData);
            break;

        case TAF_ME_PERSONALISATION_DEACTIVE:
            MMA_MePersonlisationDeactive(ClientId, OpId, stMePersonalData);
            break;

        case TAF_ME_PERSONALISATION_RETRIEVE:
            MMA_MePersonlisationRetrieve(ClientId, OpId, stMePersonalData);
            break;

        case TAF_ME_PERSONALISATION_QUERY:
            MMA_MePersonlisationQuery(ClientId, OpId, stMePersonalData);
            break;

        default:
            break;
    }


    return;
}


VOS_UINT8 MMA_GetMeLockStatus(VOS_VOID)
{
    VOS_UINT8                          ucSimStatus;
    VOS_UINT8                           ucSdcSimStatus;

    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;

    pucImsi = TAF_SDC_GetSimImsi();

    (VOS_VOID)MMA_PhoneGetUsimStatus(&ucSimStatus);
    if (MMA_USIM_PRESENT != ucSimStatus)
    {
        return TAF_PH_ME_NO_SIM;
    }

    ucSdcSimStatus = TAF_SDC_GetSimStatus();

    if ((TAF_SDC_USIM_STATUS_SIM_PIN == ucSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_SIM_PUK == ucSdcSimStatus))
    {
        return TAF_PH_ME_NO_SIM;
    }

    /* �����ǰû�л�ȡ��IMSI,���»�ȡһ�� */
    if (pucImsi[0] > 8)
    {
        if (USIMM_API_SUCCESS == NAS_USIMMAPI_GetCardIMSI(pucImsi))
        {
            /* ����Ƿ����� */
            (VOS_VOID)MMA_CheckMePersonalisationStatus();
        }
        else
        {
            return TAF_PH_ME_NO_SIM;
        }
    }

    if (g_stMmaMePersonalisationStatus.SimLockStatus == 1)
    {
        return TAF_PH_ME_SIM_LOCK;
    }
    return TAF_PH_ME_SIM_UNLOCK;
}

/*****************************************************************************
 �� �� ��  : MMA_OpPinExpired
 ��������  : PIN ��ʱ������������PIN ��ʱ������ϲ�AT
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��9��1��
    ��    ��   : liuyang
    �޸�����   : �����ɺ���

  2.��    ��   : 2006��3��8��
    ��    ��   : liuyang id:48197
    �޸�����   : ���ⵥ�ţ�A32D02371��ʹ�ú������ԭ�еĳ���

  3.��    ��   : 2006��3��20��
    ��    ��   : liuyang id:48197
    �޸�����   : ���ⵥ�ţ�A32D02602
*****************************************************************************/
VOS_VOID MMA_OpPinExpired(VOS_VOID)
{
    /*��ʱ��Ϣ��Ч���ж�*/
    if ( MMA_TIMER_RUN != g_MmaSimTimer[0].ucTimerStatus  )
    {
        MMA_WARNINGLOG("MMA_OpPinExpired():WARNING:OP PIN TIMER is not running!");
        return;
    }
    MMA_WARNINGLOG("MMA_OpPinExpired():WARNING:OP PIN TIMER OUT!");
    /*����ֹͣ��ʱ����־*/
    g_MmaSimTimer[0].ucTimerStatus           = MMA_TIMER_STOP;
    /*���ʹ�ñ�־*/
    gastMmaTiTab[MMA_PH_PIN_TI].ucUsed       = MMA_TI_UNUSED;
    /*������*/
    MMA_HandleEventError(gastMmaTiTab[MMA_PH_PIN_TI].ClientId, gastMmaTiTab[MMA_PH_PIN_TI].Id, TAF_ERR_TIME_OUT, TAF_PH_EVT_OP_PIN_CNF);
    return;
}

/* ɾ�� MMA_SendPINOk���� ���ú���û�еط����� */

VOS_UINT32 MN_PH_PinOper(
    const TAF_PH_PIN_CNF_STRU           *pstPinInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucMmaImsi[9];
    VOS_UINT32                          ulPin1;
    VOS_UINT8                           ucSdcSimStatus;

    ucSdcSimStatus  = TAF_SDC_GetSimStatus();

    /* ��ȡ��ǰ�Ƿ��ܻ�ȡ��IMSI,�ܻ�ȡ������������ʱ�� */
    ulPin1 = MMA_Pin1Noneed();

    if ((VOS_TRUE == MMA_OpPin1Success(pstPinInfo))
     && (VOS_TRUE == ulPin1)
     && ((TAF_SDC_USIM_STATUS_SIM_PIN == ucSdcSimStatus)
      || (TAF_SDC_USIM_STATUS_SIM_PUK == ucSdcSimStatus)))
    {

        /* �ػ�״̬�½�PIN,���ܰ�MMA״̬��Ϊ����״̬ */

        /*A32D11538==>��Ҫ����PIN��ʱ,MMAģ���ʼ��ʱ��Ϊ�п�*/


        if (USIMM_API_SUCCESS == NAS_USIMMAPI_GetCardIMSI(aucMmaImsi))
        {
            MMA_INFOLOG("MN_PH_PinOper():Info :USIMM_GetCardIMSI OK!");
            return VOS_OK;
        }

        /* PIN OK��USIM��Ҫ��ʼ������Ҫ��ʱ�Ա�֤��ȡIMSI���� */
        g_stPhPhResetTimer.ulTimerId = TI_MN_PH_PIN_OPER;

        ulRet = NAS_StartRelTimer( &g_stPhPhResetTimer.MmaHTimer,
                                     WUEPS_PID_MMA,
                                     TI_MN_PH_PIN_OPER_LENGTH,
                                     TAF_MMA,
                                     TI_MN_PH_PIN_OPER,
                                     VOS_RELTIMER_NOLOOP );

        if( VOS_OK !=  ulRet)
        {
            MMA_ERRORLOG("MN_PH_PinOper():ERROR:Start TI_MN_PH_PIN_OPER Timer Error!");
        }
        else
        {
            g_stPhPhResetTimer.ucTimerStatus = MMA_TIMER_RUN;
        }
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID MMA_PinDataReport( const TAF_PH_PIN_CNF_STRU *pstPinCnf)
{
    TAF_PHONE_EVENT_INFO_STRU           *pstPhoneEvent;
    VOS_UINT32                          ulRet;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_InitAtMsgReq:ERROR:ALLOC MEMORY FAIL.");
        return;
    }
    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));
    /*������Ч���ж�*/
    if ( VOS_NULL_PTR == pstPinCnf)
    {
        MMA_WARNINGLOG("MMA_PinDataReport():WARNING:pPinCnf is NULL PTR!.");
        MMA_HandleEventError(gstMmaValue.stOpPinData.ClientId,
                             gstMmaValue.stOpPinData.OpId,
                             TAF_ERR_NULL_PTR,
                             TAF_PH_EVT_OP_PIN_CNF);
        PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);
        return;
    }
    MMA_InitEventInfoOP(pstPhoneEvent);
    /*����TAF�¼��ϱ�����,�ϱ�PIN�¼�*/
    pstPhoneEvent->OP_Pin                    = VOS_TRUE;
    pstPhoneEvent->PinCnf                    = *pstPinCnf;
    pstPhoneEvent->PhoneEvent                = TAF_PH_EVT_OP_PIN_CNF;

    /*�ǲ�ѯ״̬�£�Ҫֹͣ��ʱ��*/
    if ( (TAF_PIN_QUERY != pstPinCnf->CmdType)
     && (TAF_PIN2_QUERY != pstPinCnf->CmdType) )
    {
        /*ֹͣ��ʱ��*/
        if ( MMA_TIMER_RUN == g_MmaSimTimer[0].ucTimerStatus )
        {
            if (VOS_OK != NAS_StopRelTimer(WUEPS_PID_MMA, TAF_USIM_OPPIN, &(g_MmaSimTimer[0].MmaHTimer)))
            {
                MMA_WARNINGLOG("MMA_PinDataReport():WARNING:NAS_StopRelTimer failed!");
            }

            /*����ֹͣ��ʱ����־*/
            g_MmaSimTimer[0].ucTimerStatus    = MMA_TIMER_STOP;
        }
        switch ( pstPinCnf->OpPinResult )
        {
            case USIMM_SIM_PIN_REQUIRED:
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_NEED_PIN1;
                break;
            case USIMM_SIM_PIN2_REQUIRED:
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_NEED_PIN2;
                break;
            case USIMM_SIM_PUK_REQUIRED:
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_NEED_PUK1;
                break;
            case USIMM_SIM_PUK2_REQUIRED:
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_NEED_PUK2;
                break;
            case USIMM_INCORRECT_PASSWORD:
                if ((TAF_SIM_PUK == pstPhoneEvent->PinCnf.PinType) && (0 == pstPhoneEvent->PinCnf.RemainTime.ucPuk1RemainTime))
                {
                    pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_SIM_FAIL;
                }
                else
                {
                    pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_INCORRECT_PASSWORD;
                }
                break;
            case USIMM_OPERATION_NOT_ALLOW:
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_OPERATION_NOT_ALLOW;
                break;
            case USIMM_SIM_FAILURE:
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_SIM_FAIL;
                break;
            case USIMM_API_SUCCESS:
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_OK;
                break;
            default:
                MMA_WARNINGLOG1("MMA_PinDataReport():WARNING:WRONG PIN RESULT is", pstPhoneEvent->PinCnf.OpPinResult);
                pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_PIN_ERROR;
                break;
        }
    }

    ulRet = VOS_OK;

    if ( ((TAF_PIN_QUERY != pstPinCnf->CmdType) && (TAF_PIN2_QUERY != pstPinCnf->CmdType))
      && (TAF_PH_OP_PIN_OK == pstPhoneEvent->PinCnf.OpPinResult))
    {
        ulRet = MN_PH_PinOper(pstPinCnf);
    }

    /*��ȡ��ǰ�Ƿ����ϱ�,�����Ҫ������ʱ������ȶ�ʱ����ʱ������ϱ� */
    if ( VOS_OK == ulRet)
    {
        Taf_PhoneEvent(pstPhoneEvent);
    }
    else
    {
        PS_MEM_CPY(&g_stPhPinCnf,&pstPhoneEvent->PinCnf,sizeof(g_stPhPinCnf));
    }

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

    return;
}

/* MMA_PhoneGetNetworkNameFromUsim */

/*MMA_PhoneGetNetworkName*/

VOS_UINT32 TAF_MMA_GetPlmnPnnIndexInOplFile(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId,
    TAF_SDC_OPL_FILE_INFO_STRU         *pstOplFileInfo
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT16                          usAppCampLac;
    VOS_CHAR                            cWildCard;

    usAppCampLac    = TAF_SDC_GetAppCampLac();
    cWildCard       = TAF_SDC_GetPlmnCompareWildCard();

    for (ulIndex = 0; ulIndex < pstOplFileInfo->ulOplRecordNum; ulIndex++)
    {
        /* ��֧��plmnͨ����Ƚ� */
        if (0 == cWildCard)
        {
            if (VOS_FALSE == TAF_SDC_CompareBcchPlmnwithSimPlmn(pstPlmnId, &pstOplFileInfo->astOplRecordInfo[ulIndex].stPlmnId))
            {
                continue;
            }
        }
        else
        {
            if (VOS_FALSE == TAF_SDC_CompareBcchPlmnwithSimPlmn_WithWildcard(pstPlmnId, &pstOplFileInfo->astOplRecordInfo[ulIndex].stPlmnId, cWildCard))
            {
                continue;
            }
        }

        if ((TAF_SDC_VALID_LAC_RANGE_LOW == pstOplFileInfo->astOplRecordInfo[ulIndex].usLacRangeLow)
         && (TAF_SDC_VALID_LAC_RANGE_HIGH == pstOplFileInfo->astOplRecordInfo[ulIndex].usLacRangeHigh))
        {
            return pstOplFileInfo->astOplRecordInfo[ulIndex].usPnnIndex;
        }

        if ((usAppCampLac >= pstOplFileInfo->astOplRecordInfo[ulIndex].usLacRangeLow)
         && (usAppCampLac <= pstOplFileInfo->astOplRecordInfo[ulIndex].usLacRangeHigh))
        {
            return pstOplFileInfo->astOplRecordInfo[ulIndex].usPnnIndex;
        }
    }

    return TAF_SDC_INVALID_PNN_INDEX;
}
VOS_UINT32 TAF_MMA_Get7BitNetworkNameStr(
    TAF_SDC_OPERATOR_NAME_STRU         *pstNetworkLongName,
    TAF_SDC_OPERATOR_NAME_STRU         *pstNetworkShortName,
    TAF_MMA_MM_INFO_PLMN_NAME_STRU     *pstOperatorName
)
{
    VOS_UINT32                                              ulRet;
    NAS_MSCC_PIF_OPERATOR_NAME_INFO_STRU                    stMmcName;
    VOS_UINT8                                               ucNetworkNameValidFlag;
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8                     enCopsFormatType;

    ucNetworkNameValidFlag = VOS_FALSE;
    PS_MEM_SET(&stMmcName, 0, sizeof(stMmcName));
    enCopsFormatType       = TAF_SDC_GetCopsFormatType();

    ulRet = TAF_MMA_TranslateNtwkName2Str(pstNetworkLongName,
                                          (VOS_CHAR *)stMmcName.aucOperatorNameLong,
                                          TAF_PH_OPER_NAME_LONG);
    if ((TAF_SDC_COPS_FORMAT_TYPE_LONG_ALPH == enCopsFormatType)
      && (VOS_TRUE == ulRet))
    {
        PS_MEM_CPY(pstOperatorName->aucLongName,
                   stMmcName.aucOperatorNameLong,
                   sizeof(pstOperatorName->aucLongName));
        ucNetworkNameValidFlag = VOS_TRUE;
    }

    ulRet = TAF_MMA_TranslateNtwkName2Str(pstNetworkShortName,
                                          (VOS_CHAR *)stMmcName.aucOperatorNameShort,
                                          TAF_PH_OPER_NAME_SHORT);

    if ((TAF_SDC_COPS_FORMAT_TYPE_SHORT_ALPH == enCopsFormatType)
     && (VOS_TRUE == ulRet))
    {
        PS_MEM_CPY(pstOperatorName->aucShortName,
                   stMmcName.aucOperatorNameShort,
                   sizeof(pstOperatorName->aucShortName));
        ucNetworkNameValidFlag = VOS_TRUE;
    }

    if (VOS_TRUE == ucNetworkNameValidFlag)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_MMA_GetUcs2NetworkName(
    TAF_SDC_OPERATOR_NAME_STRU                             *pstIeNtwkLongName,
    TAF_SDC_OPERATOR_NAME_STRU                             *pstIeNtwkShortName,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8             enNetNameCodeScheme,
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                         *pstOperatorName
)
{
    TAF_MMA_MM_INFO_PLMN_NAME_STRU      stMmPlmnInfo;
    VOS_UINT8                           ucNetworkNameValidFlag;
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8 enCopsFormatType;

    PS_MEM_SET(&stMmPlmnInfo, 0, sizeof(TAF_MMA_MM_INFO_PLMN_NAME_STRU));

    enCopsFormatType       = TAF_SDC_GetCopsFormatType();
    ucNetworkNameValidFlag = VOS_FALSE;

    pstOperatorName->ucLongNameLen = TAF_MMA_TranslateOperatorName2UCS2(pstIeNtwkLongName,
                                                        (VOS_CHAR *)(stMmPlmnInfo.aucLongName),
                                                         TAF_PH_OPER_NAME_LONG);

    if ((((TAF_SDC_NETWORK_NAME_CODE_SCHEME_COPS_UCS2 == enNetNameCodeScheme)
       && (TAF_SDC_COPS_FORMAT_TYPE_LONG_ALPH == enCopsFormatType))
      || (TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2 == enNetNameCodeScheme))
     && (0 != pstOperatorName->ucLongNameLen))
    {
        PS_MEM_CPY(pstOperatorName->aucLongName,
                   stMmPlmnInfo.aucLongName,
                   pstOperatorName->ucLongNameLen);

        ucNetworkNameValidFlag = VOS_TRUE;
    }

    pstOperatorName->ucShortNameLen = TAF_MMA_TranslateOperatorName2UCS2(pstIeNtwkShortName,
                                                        (VOS_CHAR *)(stMmPlmnInfo.aucShortName),
                                                        TAF_PH_OPER_NAME_SHORT);

    if ((((TAF_SDC_NETWORK_NAME_CODE_SCHEME_COPS_UCS2 == enNetNameCodeScheme)
       && (TAF_SDC_COPS_FORMAT_TYPE_SHORT_ALPH == enCopsFormatType))
      || (TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2 == enNetNameCodeScheme))
     && (0 != pstOperatorName->ucShortNameLen))
    {
        PS_MEM_CPY(pstOperatorName->aucShortName,
                   stMmPlmnInfo.aucShortName,
                   pstOperatorName->ucShortNameLen);

        ucNetworkNameValidFlag = VOS_TRUE;
    }

    if (VOS_TRUE == ucNetworkNameValidFlag)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_MMA_GetPnnNetWorkName(
    TAF_SDC_PLMN_ID_STRU                                   *pstPlmnId,
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                         *pstPlmnName,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8             enNetNameCodeScheme
)
{
    TAF_SDC_PNN_FILE_INFO_STRU         *pstPnnFileInfo = VOS_NULL_PTR;
    TAF_SDC_OPL_FILE_INFO_STRU         *pstOplFileInfo = VOS_NULL_PTR;
    TAF_PH_ROAM_STA                     ucIsRoamFlag;
    VOS_UINT32                          ulPnnIndex;
    VOS_UINT32                          ulRet;
    TAF_SDC_FILE_TYPE_ENUM_UINT8        enValidOplFileType;
    TAF_SDC_FILE_TYPE_ENUM_UINT8        enValidPnnFileType;

    enValidOplFileType = TAF_SDC_GetOplFileType();
    enValidPnnFileType = TAF_SDC_GetPnnFileType();

    ucIsRoamFlag       = MMA_IsRoam(TAF_SDC_GetAppRoamFlg());

    /* ��֧��PNN����ʧ�� */
    if (VOS_FALSE == TAF_SDC_IsOperNameTypeSupport(TAF_SDC_OPER_NAME_TYPE_PNN))
    {
        return VOS_FALSE;
    }

    /* pnn��opl�ļ����Ͳ�һ��,��opl��¼������Ϊ�գ�����ʧ�� */
    if ((enValidPnnFileType != enValidOplFileType)
     && (enValidOplFileType != TAF_SDC_FILE_TYPE_BUTT))
    {
        return VOS_FALSE;
    }

    /* OPL��PNN�ļ���¼����Ϊ0����ʧ�� */
    if ((TAF_SDC_FILE_TYPE_BUTT == enValidPnnFileType)
     && (TAF_SDC_FILE_TYPE_BUTT == enValidOplFileType))
    {
        return VOS_FALSE;
    }

    pstOplFileInfo     = TAF_SDC_GetUsimOplFileInfo();
    pstPnnFileInfo     = TAF_SDC_GetUsimPnnFileInfo();

    if (TAF_SDC_FILE_TYPE_SIM == enValidPnnFileType)
    {
        pstOplFileInfo = TAF_SDC_GetSimOplFileInfo();
        pstPnnFileInfo = TAF_SDC_GetSimPnnFileInfo();
    }


    /* OPL�ļ���¼Ϊ0��PNN�ļ���¼��Ϊ0��פ��hplmn�ϣ�����PNN�ļ���һ����¼��Ӧ����Ӫ������ */
    if ((0 == pstOplFileInfo->ulOplRecordNum)
     && (TAF_PH_NO_ROAM == ucIsRoamFlag))
    {
        ulPnnIndex = 1;
    }
    else
    {
        /* OPL��PNN�ļ���¼����Ϊ0 */
        ulPnnIndex = TAF_MMA_GetPlmnPnnIndexInOplFile(pstPlmnId, pstOplFileInfo);
    }

    /* ��OPL�л�ȡ��PNN index�Ƿ������֧��100��������ʧ�� */
    if ((ulPnnIndex < TAF_SDC_VALID_PNN_LOW_INDEX)
     || (ulPnnIndex > TAF_SDC_PNN_MAX_RECORD_NUM))
    {
        return VOS_FALSE;
    }

    /* ��OPL�л�ȡ��PNN index�Ϸ�,��PNN�л�ȡ7 bit�������Ӫ������ */
    if (TAF_SDC_NETWORK_NAME_CODE_SCHEME_7BIT == enNetNameCodeScheme)
    {
        ulRet = TAF_MMA_Get7BitNetworkNameStr(&pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong,
                                 &pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort,
                                 pstPlmnName);

        if (VOS_TRUE == ulRet)
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }


    /* ��OPL�л�ȡ��PNN index�Ϸ�,��PNN�л�ȡUCS2�������Ӫ������ */
    if ((TAF_SDC_NETWORK_NAME_CODE_SCHEME_COPS_UCS2 == enNetNameCodeScheme)
     || (TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2 == enNetNameCodeScheme))
    {
        ulRet = TAF_MMA_GetUcs2NetworkName(&pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameLong,
                        &pstPnnFileInfo->astPnnRecordInfo[ulPnnIndex - 1].stOperatorNameShort,
                        enNetNameCodeScheme,
                        pstPlmnName);

        if (VOS_TRUE == ulRet)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 TAF_MMA_GetCphsNetWorkName(
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                         *pstOperatorName,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8             enNetNameCodeScheme
)
{
    TAF_SDC_CPHS_FILE_INFO_STRU        *pstCphsFileInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    TAF_PH_ROAM_STA                     ucIsRoamFlag;

    ucIsRoamFlag    = MMA_IsRoam(TAF_SDC_GetAppRoamFlg());
    pstCphsFileInfo = TAF_SDC_GetChpsFileInfo();

    /* ��֧��CPHS����ʧ�� */
    if (VOS_FALSE == TAF_SDC_IsOperNameTypeSupport(TAF_SDC_OPER_NAME_TYPE_CPHS))
    {
        return VOS_FALSE;
    }

    /* ���ļ������ڻ��ļ�����Ϊ0����ʧ�� */
    if (0 == pstCphsFileInfo->stCPHSOperName.ucLength)
    {
        return VOS_FALSE;
    }

    /* פ����hplmn��ʹ��cphs��Ϣ */
    if (TAF_PH_ROAMING == ucIsRoamFlag)
    {
        return VOS_FALSE;
    }

    if (TAF_SDC_NETWORK_NAME_CODE_SCHEME_7BIT == enNetNameCodeScheme)
    {
        ulRet = TAF_MMA_Get7BitNetworkNameStr(&pstCphsFileInfo->stCPHSOperName,
                                              &pstCphsFileInfo->stCPHSOperName,
                                              pstOperatorName);

        if (VOS_TRUE == ulRet)
        {
            return VOS_TRUE;
        }
    }

    /* CPHS������UCS2���룬����ʧ�� */
    return VOS_FALSE;
}


VOS_UINT32 TAF_MMA_GetMmInfoNetWorkName(
    TAF_SDC_PLMN_ID_STRU                                   *pstPlmnId,
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                         *pstOperatorName,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8             enNetNameCodeScheme
)
{
    TAF_SDC_MM_INFO_STRU               *pstMmInfo           = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    pstMmInfo           = TAF_SDC_GetMmInfo();

    /* ��֧��MM INFO����ʧ�� */
    if (VOS_FALSE == TAF_SDC_IsOperNameTypeSupport(TAF_SDC_OPER_NAME_TYPE_MMINFO))
    {
        return VOS_FALSE;
    }

    /* ��ǰפ���������յ�MM INFO�����粻��ͬ����ʧ�� */
    if (VOS_FALSE == TAF_SDC_CompareBcchPlmnwithSimPlmn(pstPlmnId, &pstMmInfo->stOperatorPlmnId))
    {
        return VOS_FALSE;
    }

    if (TAF_SDC_NETWORK_NAME_CODE_SCHEME_7BIT == enNetNameCodeScheme)
    {
        ulRet = TAF_MMA_Get7BitNetworkNameStr(&pstMmInfo->stOperatorNameLong,
                                              &pstMmInfo->stOperatorNameShort,
                                              pstOperatorName);

        if (VOS_TRUE == ulRet)
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }

    if ((TAF_SDC_NETWORK_NAME_CODE_SCHEME_COPS_UCS2 == enNetNameCodeScheme)
     || (TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2 == enNetNameCodeScheme))
    {
        ulRet = TAF_MMA_GetUcs2NetworkName(&pstMmInfo->stOperatorNameLong,
                                           &pstMmInfo->stOperatorNameShort,
                                           enNetNameCodeScheme,
                                           pstOperatorName);

        if (VOS_TRUE == ulRet)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 TAF_MMA_GetSpnNetWorkName(
    TAF_SDC_PLMN_ID_STRU                                   *pstPlmnId,
    TAF_MMA_MM_INFO_PLMN_NAME_STRU                         *pstOperatorName,
    TAF_SDC_NETWORK_NAME_CODE_SCHEME_ENUM_UINT8             enNetNameCodeScheme
)
{
    TAF_SDC_SPN_FILE_INFO_STRU         *pstUsimSpnFileInfo = VOS_NULL_PTR;
    TAF_SDC_SPN_FILE_INFO_STRU         *pstSimSpnFileInfo = VOS_NULL_PTR;
    TAF_SDC_SPDI_FILE_INFO_STRU        *pstSpdiFileInfo = VOS_NULL_PTR;
    TAF_PH_ROAM_STA                     ucIsRoamFlag;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;
    TAF_SDC_SPN_FILE_INFO_STRU          stSpnFileInfo;
    TAF_MMA_MM_INFO_PLMN_NAME_STRU      stMmPlmnInfo;

    enSysMode           = TAF_SDC_GetAppSysMode();
    pstUsimSpnFileInfo  = TAF_SDC_GetUsimSpnFileInfo();
    pstSimSpnFileInfo   = TAF_SDC_GetSimSpnFileInfo();
    pstSpdiFileInfo     = TAF_SDC_GetSpdiFileInfo();
    ucIsRoamFlag        = MMA_IsRoam(TAF_SDC_GetAppRoamFlg());
    PS_MEM_SET(&stSpnFileInfo, 0, sizeof(stSpnFileInfo));
    PS_MEM_SET(&stMmPlmnInfo, 0, sizeof(stMmPlmnInfo));

    /* ��֧��SPN����ʧ�� */
    if (VOS_FALSE == TAF_SDC_IsOperNameTypeSupport(TAF_SDC_OPER_NAME_TYPE_SPN))
    {
        return VOS_FALSE;
    }

    /* ��ǰפ�����粻��HPLMN����EFSPDI�ļ���¼��PLMN�б��У�����ʧ�� */
    if ((VOS_FALSE == TAF_SDC_IsBcchPlmnIdInDestSimPlmnList(pstPlmnId, pstSpdiFileInfo->ucServiceProviderPlmnNum, pstSpdiFileInfo->astSeriveProviderPlmn))
     && (TAF_PH_ROAMING == ucIsRoamFlag))
    {
        return VOS_FALSE;
    }

    /* 31102Э������:
    b1=0: display of registered PLMN name not required when registered PLMN is either HPLMN or a PLMN in the service provider PLMN list (see EFSPDI).
    B1=1: display of registered PLMN name required when registered PLMN is either HPLMN or a PLMN in the service provider PLMN list(see EFSPDI).
    B2=0: display of the service provider name is required when registered PLMN is neither HPLMN nor a PLMN in the service provider PLMN list(see EFSPDI).
    B2=1: display of the service provider name is not required when registered PLMN is neither HPLMN nor a PLMN in the service provider PLMN list(see EFSPDI).*/
    /* פ��w��l�����usim spn�ļ�����Ϊ0����ʾģʽ���Է���ʧ�� */
    if ((TAF_SDC_SYS_MODE_WCDMA == enSysMode)
     || (TAF_SDC_SYS_MODE_LTE == enSysMode))
    {
        if ((0 == pstUsimSpnFileInfo->stSpnOperName.ucLength)
         || (0 != (pstUsimSpnFileInfo->ucDispRplmnMode & 0x02)))
        {
            return VOS_FALSE;
        }

        stSpnFileInfo = *pstUsimSpnFileInfo;
    }

    if (TAF_SDC_SYS_MODE_GSM == enSysMode)
    {
        if ((0 == pstSimSpnFileInfo->stSpnOperName.ucLength)
         || (0 != (pstSimSpnFileInfo->ucDispRplmnMode & 0x02)))
        {
            return VOS_FALSE;
        }

        stSpnFileInfo = *pstSimSpnFileInfo;
    }

    if (TAF_PH_GSM_7BIT_DEFAULT == enNetNameCodeScheme)
    {
        /* UCS2���뷵��ʧ�� */
        if (TAF_PH_RAW_MODE == stSpnFileInfo.stSpnOperName.bitCoding)
        {
            return VOS_FALSE;
        }

        pstOperatorName->ucLongNameLen = stSpnFileInfo.stSpnOperName.ucLength;

        if (pstOperatorName->ucLongNameLen > TAF_PH_OPER_NAME_LONG)
        {
            pstOperatorName->ucLongNameLen = TAF_PH_OPER_NAME_LONG;
        }

        PS_MEM_CPY(pstOperatorName->aucLongName, stSpnFileInfo.stSpnOperName.aucOperatorName, pstOperatorName->ucLongNameLen);

        pstOperatorName->ucShortNameLen = stSpnFileInfo.stSpnOperName.ucLength;

        if (pstOperatorName->ucShortNameLen > TAF_PH_OPER_NAME_SHORT)
        {
            pstOperatorName->ucShortNameLen = TAF_PH_OPER_NAME_SHORT;
        }

        PS_MEM_CPY(pstOperatorName->aucShortName, stSpnFileInfo.stSpnOperName.aucOperatorName, pstOperatorName->ucShortNameLen);

        return VOS_TRUE;
    }

    if ((TAF_SDC_NETWORK_NAME_CODE_SCHEME_COPS_UCS2 == enNetNameCodeScheme)
     || (TAF_SDC_NETWORK_NAME_CODE_SCHEME_EONS_UCS2 == enNetNameCodeScheme))
    {
        pstOperatorName->ucLongNameLen = TAF_MMA_TranslateOperatorName2UCS2(&stSpnFileInfo.stSpnOperName,
                                                        (VOS_CHAR *)(stMmPlmnInfo.aucLongName),
                                                         TAF_PH_OPER_NAME_LONG);

        if (0 != pstOperatorName->ucLongNameLen)
        {
            PS_MEM_CPY(pstOperatorName->aucLongName,
                       stMmPlmnInfo.aucLongName,
                       pstOperatorName->ucLongNameLen);

        }

        pstOperatorName->ucShortNameLen = TAF_MMA_TranslateOperatorName2UCS2(&stSpnFileInfo.stSpnOperName,
                                                        (VOS_CHAR *)(stMmPlmnInfo.aucShortName),
                                                        TAF_PH_OPER_NAME_SHORT);

        if (0 != pstOperatorName->ucShortNameLen)
        {
            PS_MEM_CPY(pstOperatorName->aucShortName,
                       stMmPlmnInfo.aucShortName,
                       pstOperatorName->ucShortNameLen);

        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_MMA_GetNvimNetWorkName(
    TAF_PH_NETWORKNAME_STRU            *pstOperatorName
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucNetworkNameValidFlag;
    TAF_SDC_CUSTOM_OPER_NAME_INFO_STRU *pstCustomOperNameInfo = VOS_NULL_PTR;
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8 enCopsFormatType;

    enCopsFormatType       = TAF_SDC_GetCopsFormatType();
    pstCustomOperNameInfo  = TAF_SDC_GetCustomOperNameInfo();
    ucNetworkNameValidFlag = VOS_FALSE;

    /* ��NV���в�ѯPLMN ID��Ӧ����Ӫ������*/
    for (ucIndex = 0; ucIndex < TAF_NVIM_STORED_OPER_NAME_NUM; ucIndex++)
    {
        if (VOS_TRUE == TAF_SDC_CompareBcchPlmnwithSimPlmn((TAF_SDC_PLMN_ID_STRU *)&pstOperatorName->Name.PlmnId, &pstCustomOperNameInfo->astCustomOperName[ucIndex].stOperatorPlmnId))
        {
            if ((TAF_SDC_COPS_FORMAT_TYPE_LONG_ALPH == enCopsFormatType)
             && ('\0' != pstCustomOperNameInfo->astCustomOperName[ucIndex].stOperatorNameLong.aucOperatorName[0]))
            {
                PS_MEM_CPY(pstOperatorName->Name.aucOperatorNameLong, pstCustomOperNameInfo->astCustomOperName[ucIndex].stOperatorNameLong.aucOperatorName, NV_ITEM_OPER_NAME_LONG);
                ucNetworkNameValidFlag = VOS_TRUE;
            }

            if((TAF_SDC_COPS_FORMAT_TYPE_SHORT_ALPH == enCopsFormatType)
              && ('\0' != pstCustomOperNameInfo->astCustomOperName[ucIndex].stOperatorNameShort.aucOperatorName[0]))
            {
                PS_MEM_CPY(pstOperatorName->Name.aucOperatorNameShort, pstCustomOperNameInfo->astCustomOperName[ucIndex].stOperatorNameShort.aucOperatorName,NV_ITEM_OPER_NAME_SHORT);
                ucNetworkNameValidFlag = VOS_TRUE;
            }

            if (VOS_TRUE == ucNetworkNameValidFlag)
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}
VOS_UINT32 TAF_MMA_GetStoredInternalNetWorkName(
    TAF_PH_NETWORKNAME_STRU            *pstOperatorName
)
{
    TAF_PH_OPERATOR_NAME_STRU           stOperName;
    VOS_UINT8                           ucNetworkNameValidFlag;
    TAF_SDC_COPS_FORMAT_TYPE_ENUM_UINT8 enCopsFormatType;

    stOperName.PlmnId      = pstOperatorName->Name.PlmnId;
    enCopsFormatType       = TAF_SDC_GetCopsFormatType();
    ucNetworkNameValidFlag = VOS_FALSE;
    PS_MEM_CPY(stOperName.aucOperatorNameLong, pstOperatorName->Name.aucOperatorNameLong, sizeof(stOperName.aucOperatorNameLong));
    PS_MEM_CPY(stOperName.aucOperatorNameShort, pstOperatorName->Name.aucOperatorNameShort, sizeof(stOperName.aucOperatorNameShort));

    if (MMA_FAILURE == MMA_PhoneFindNtwkNameByPlmnId(&stOperName))
    {
        return VOS_FALSE;
    }

    if ((TAF_SDC_COPS_FORMAT_TYPE_LONG_ALPH == enCopsFormatType)
      && ('\0' != stOperName.aucOperatorNameLong[0]))
    {
        PS_MEM_CPY(pstOperatorName->Name.aucOperatorNameLong, stOperName.aucOperatorNameLong, TAF_PH_OPER_NAME_LONG);
        ucNetworkNameValidFlag = VOS_TRUE;
    }

    if((TAF_SDC_COPS_FORMAT_TYPE_SHORT_ALPH == enCopsFormatType)
    && ('\0' != stOperName.aucOperatorNameShort[0]))
    {
        PS_MEM_CPY(pstOperatorName->Name.aucOperatorNameShort, stOperName.aucOperatorNameShort,TAF_PH_OPER_NAME_SHORT);
        ucNetworkNameValidFlag = VOS_TRUE;
    }

    if (VOS_TRUE == ucNetworkNameValidFlag)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* delete TAF_MMA_GetCopsNetWorkName */



/* ɾ��MMA_PhoneGetCellRoam */


TAF_UINT32 Taf_PhoneGetNetworkNameForListPlmn(TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU *pstOperName)
{
    VOS_UINT32                ulRet = MMA_FAILURE;

    pstOperName->OperName.aucOperatorNameLong[0]  = '\0';
    pstOperName->OperName.aucOperatorNameShort[0] = '\0';

    if ((0 == pstOperName->OperName.PlmnId.Mcc) && (0 == pstOperName->OperName.PlmnId.Mnc))
    {
        return ulRet;
    }

    /* ����Ӫ���б��в�ѯPLMNID��Ӧ������ */
    ulRet = MMA_PhoneFindNtwkNameByPlmnId(&(pstOperName->OperName));

    return ulRet;
}


/* ɾ��MMA_PhoneGetRoamSta */



VOS_VOID MMA_PhoneGetDomain(VOS_UINT16  ClientId,  VOS_UINT8  OpId)
{
    TAF_PH_DOMAIN_FLAG       PhDomain;

    /*��status�л�ȡ��ǰ��״̬*/
    PhDomain = gstMmaValue.pg_StatusContext->ucDomainFlag;

    /*ʹ�������ϱ����������ݴ���TAFm*/
    MMA_ParaQueryReport(ClientId, OpId, TAF_PH_DOMAIN_PARA,TAF_ERR_NO_ERROR, (VOS_VOID*)&PhDomain);
    return;
}


VOS_UINT32 NAS_MMA_MntnTraceGetUsimStatus(
    VOS_UINT8                           ucUsimStatus,
    VOS_UINT8                           ucMeLockStatus
)
{
    NAS_MMA_MNTN_GET_USIM_STATUS_STRU   *pstSendMsg;
    NAS_MMA_USIM_STATUS_INFO_STRT       *pstUsimStatusInfo;

    pstSendMsg = (NAS_MMA_MNTN_GET_USIM_STATUS_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, sizeof(NAS_MMA_MNTN_GET_USIM_STATUS_STRU));

    if ( VOS_NULL_PTR == pstSendMsg )
    {
        MMA_ERRORLOG("NAS_MMA_MntnTraceGetUsimStatus:ERROR: Alloc Memory Fail.");
        return MMA_ERROR;
    }

    pstUsimStatusInfo = &pstSendMsg->stStatusInfo;

    pstUsimStatusInfo->ulUsimHotInFlg           = g_ucUsimHotInFlag;
    pstUsimStatusInfo->ulUsimHotOutFlg          = g_ucUsimHotOutFlag;

    pstUsimStatusInfo->ulUsimHotInCount         = g_ulUsimHotInCount;
    pstUsimStatusInfo->ulUsimHotOutCount        = g_ulUsimHotOutCount;

    pstUsimStatusInfo->ucUsimStatusFromUsim     = ucUsimStatus;

    pstUsimStatusInfo->ucMeLockStatus           = ucMeLockStatus;

    pstUsimStatusInfo->ucMmaGlobalUsimStatus    = TAF_SDC_GetSimStatus();


    pstSendMsg->ulReceiverPid                   = WUEPS_PID_MMA;
    pstSendMsg->ulSenderPid                     = WUEPS_PID_MMA;
    pstSendMsg->ulSenderCpuId                   = VOS_LOCAL_CPUID;
    pstSendMsg->ulReceiverCpuId                 = VOS_LOCAL_CPUID;
    pstSendMsg->ulLength                        = sizeof(NAS_MMA_USIM_STATUS_INFO_STRT) + 4;
    pstSendMsg->ulMsgID                         = ID_NAS_MMA_MNTN_GET_USIM_STATUS;

    DIAG_TraceReport(pstSendMsg);
    PS_FREE_MSG(WUEPS_PID_MMA, pstSendMsg);

    return MMA_SUCCESS;
}


VOS_UINT8 MMA_GetUsimStatus(
    VOS_UINT32                          ulUsimStaChg
)
{
    VOS_BOOL                            bCsSimStaus;
    VOS_BOOL                            bPsSimStaus;
    VOS_UINT8                           ucMeLockStatus;
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSdcSimStatus;
    VOS_UINT8                           ucCurPhMode;

    /* ���ٿ���ʱ����ROMSIM */
    if (MMA_QUICK_START_ENABLE == gstMmaValue.ulQuickStartFlg)
    {
        return TAF_PH_USIM_ROMSIM;
    }

    enSdcSimStatus = TAF_SDC_GetSimStatus();
    ucMeLockStatus = MMA_GetMeLockStatus();

    /* �����ǰ��ҪУ��PIN��򿨴�������״̬�򿨲����ã���״̬Ϊ��Ч״̬ */
    if ((VOS_TRUE                    == g_ucUsimHotInFlag)
     || (TAF_SDC_USIM_STATUS_SIM_PIN == enSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_SIM_PUK == enSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_UNVALID == enSdcSimStatus)
     || (MMA_SIM_IS_LOCK             == ucMeLockStatus)
     || (TAF_SDC_USIM_STATUS_READY_TIMEROUT == enSdcSimStatus))
    {
        return TAF_PH_USIM_STATUS_UNAVAIL;
    }

    if (TAF_SDC_USIM_STATUS_NO_PRESENT == enSdcSimStatus)
    {
        return TAF_PH_USIM_NON;
    }

    ucCurPhMode = TAF_SDC_GetCurPhoneMode();

    /* �ػ�״̬�򿪻������л�״̬�����仯ʹ��SDC�еĿ�״̬�ϱ� */
    if ((TAF_MMA_FSM_PHONE_MODE == TAF_MMA_GetCurrFsmId())
     || (TAF_PH_MODE_FULL       != ucCurPhMode)
     || (VOS_TRUE               == ulUsimStaChg))
    {
        return enSdcSimStatus;
    }

    /* ͨ��SDC �ӿڻ�ȡCS/PS�Ŀ��Ƿ���Ч��Ϣ, */
    bCsSimStaus = TAF_SDC_GetSimCsRegStatus();
    bPsSimStaus = TAF_SDC_GetSimPsRegStatus();
    if ((VOS_FALSE == bCsSimStaus)
     && (VOS_FALSE == bPsSimStaus))
    {
        return TAF_PH_USIM_STATUS_CSPS_UNVAIL;
    }

    if (VOS_FALSE == bCsSimStaus)
    {
        return TAF_PH_USIM_STATUS_CS_UNVAIL;
    }

    if (VOS_FALSE == bPsSimStaus)
    {
        return TAF_PH_USIM_STATUS_PS_UNVAIL;
    }

    return TAF_PH_USIM_STATUS_AVAIL;
}


VOS_VOID  MN_PH_ConvertSysSubModeToAtFormat_FDD(
    TAF_SYS_SUBMODE_ENUM_UINT8          enSrcSysSubMode,
    MN_PH_SUB_SYS_MODE_EX_ENUM_U8      *penDestSysSubMode
)
{
    switch (enSrcSysSubMode)
    {
        case TAF_SYS_SUBMODE_NONE:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_NONE_RAT;
            break;

        case TAF_SYS_SUBMODE_GSM:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_GSM_RAT;
            break;

        case TAF_SYS_SUBMODE_GPRS:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_GPRS_RAT;
            break;

        case TAF_SYS_SUBMODE_EDGE:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_EDGE_RAT;
            break;

        case TAF_SYS_SUBMODE_WCDMA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_WCDMA_RAT;
            break;

        case TAF_SYS_SUBMODE_HSDPA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_HSDPA_RAT;
            break;

        case TAF_SYS_SUBMODE_HSUPA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_HSUPA_RAT;
            break;

        case TAF_SYS_SUBMODE_HSDPA_HSUPA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_HSPA_RAT;
            break;

        case TAF_SYS_SUBMODE_HSPA_PLUS:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_HSPA_PLUS_RAT;
            break;

        case TAF_SYS_SUBMODE_DC_HSPA_PLUS:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_DCHSPA_PLUS_RAT;
            break;

        case TAF_SYS_SUBMODE_DC_MIMO:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_DCHSPA_PLUS_RAT;
            break;

        case TAF_SYS_SUBMODE_LTE:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_LTE_RAT;
            break;

        case TAF_SYS_SUBMODE_CDMA_1X:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_CDMA20001X_RAT;
            break;

        case TAF_SYS_SUBMODE_EVDO_REL_0:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_EVDOREL0_RAT;
            break;

        case TAF_SYS_SUBMODE_EVDO_REL_A:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_EVDORELA_RAT;
            break;

        case TAF_SYS_SUBMODE_HYBRID_EVDO_REL_0:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_HYBIRD_EVDOREL0_RAT;
            break;

        case TAF_SYS_SUBMODE_HYBRID_EVDO_REL_A:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_HYBIRD_EVDORELA_RAT;
            break;


        case TAF_SYS_SUBMODE_EHRPD:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_EHRPD_RAT;
            break;

        default:

            /* �쳣��ӡ */
            MN_INFO_LOG("MN_PH_ConvertSysSubModeToAtFormat: invalid sub sys mode!");
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_BUTT_RAT;
            break;
    }

    return;
}
VOS_VOID  MN_PH_ConvertSysSubModeToAtFormat_TDD(
    TAF_SYS_SUBMODE_ENUM_UINT8          enSrcSysSubMode,
    MN_PH_SUB_SYS_MODE_EX_ENUM_U8      *penDestSysSubMode
)
{
    switch (enSrcSysSubMode)
    {
        case TAF_SYS_SUBMODE_NONE:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_NONE_RAT;
            break;

        case TAF_SYS_SUBMODE_GSM:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_GSM_RAT;
            break;

        case TAF_SYS_SUBMODE_GPRS:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_GPRS_RAT;
            break;

        case TAF_SYS_SUBMODE_EDGE:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_EDGE_RAT;
            break;

        case TAF_SYS_SUBMODE_HSDPA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_TD_HSDPA_RAT;
            break;

        case TAF_SYS_SUBMODE_HSUPA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_TD_HSUPA_RAT;
            break;

        case TAF_SYS_SUBMODE_HSDPA_HSUPA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_TD_HSPA_RAT;
            break;

        case TAF_SYS_SUBMODE_TD_SCDMA:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_TDCDMA_RAT;
            break;

        case TAF_SYS_SUBMODE_HSPA_PLUS:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_TD_HSPA_PLUS_RAT;
            break;

        case TAF_SYS_SUBMODE_DC_HSPA_PLUS:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_DCHSPA_PLUS_RAT;
            break;

        case TAF_SYS_SUBMODE_DC_MIMO:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_DCHSPA_PLUS_RAT;
            break;

        case TAF_SYS_SUBMODE_LTE:
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_LTE_RAT;
            break;


        default:

            /* �쳣��ӡ */
            MN_INFO_LOG("MN_PH_ConvertSysSubModeToAtFormat: invalid sub sys mode!");
            *penDestSysSubMode = MN_PH_SUB_SYS_MODE_EX_BUTT_RAT;
            break;
    }

   return;
}





VOS_VOID  MN_PH_ConvertSysSubModeToAtFormat(
    TAF_SYS_SUBMODE_ENUM_UINT8          enSrcSysSubMode,
    MN_PH_SUB_SYS_MODE_EX_ENUM_U8      *penDestSysSubMode
)
{
    if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        MN_PH_ConvertSysSubModeToAtFormat_FDD(enSrcSysSubMode, penDestSysSubMode);
    }
    else
    {
        MN_PH_ConvertSysSubModeToAtFormat_TDD(enSrcSysSubMode, penDestSysSubMode);
    }

   return;
}



VOS_VOID  MN_PH_GetSysInfoRoamStatus(
    TAF_PH_SYSINFO_STRU                 *pstSysInfo
)
{
    TAF_PH_ROAM_STA                     enRoamSta;

    enRoamSta = MMA_IsRoam(TAF_SDC_GetAppRoamFlg());

    /* �ɹ�ע�ᵽHOME PLMNʱ��ʾ�����Σ��ɹ�ע�ᵽ��������ʱ��ʾ���Σ����Ʒ���ʱ��ʾδ֪ */
    if (TAF_PH_NO_ROAM == enRoamSta)
    {
        pstSysInfo->ucRoamStatus = TAF_PH_INFO_NONE_ROMAING;
    }
    else if (TAF_PH_ROAMING == enRoamSta)
    {
        pstSysInfo->ucRoamStatus = TAF_PH_INFO_ROMAING;
    }
    else
    {
        pstSysInfo->ucRoamStatus = TAF_PH_INFO_ROAM_UNKNOW;
    }
}
VOS_VOID  MN_PH_GetSysInfoSrvStatus(
    TAF_PH_SYSINFO_STRU                 *pstSysInfo
)
{
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus;

    enSimStatus = TAF_SDC_GetSimStatus();

    if ( (VOS_TRUE           == gstMmaValue.pg_StatusContext->ulTimMaxFlg)
      && (SYSTEM_APP_ANDROID != g_usMmaAppConfigSupportType) )
    {

        pstSysInfo->ucSrvStatus = TAF_PH_INFO_DEEP_SLEEP;
        pstSysInfo->ucSrvDomain = TAF_PH_INFO_NO_DOMAIN;
    }

    if ((TAF_SDC_USIM_STATUS_NO_PRESENT == enSimStatus)
     || (TAF_SDC_USIM_STATUS_UNVALID == enSimStatus)
     || (TAF_SDC_USIM_STATUS_READY_TIMEROUT == enSimStatus))
    {
        pstSysInfo->ucSrvDomain = TAF_PH_INFO_NO_DOMAIN;
    }

    /* �ϵ粻����ʱ��ѯsysinfo��sysinfoex,��ʼ��ֵΪBUTT,AT�ֲ���û�����ֵ,��һ��ת�� */
    if (TAF_SDC_SERVICE_DOMAIN_BUTT == pstSysInfo->ucSrvDomain)
    {
        pstSysInfo->ucSrvDomain = TAF_PH_INFO_NO_DOMAIN;
    }

    if (TAF_SDC_REPORT_SRVSTA_BUTT == pstSysInfo->ucSrvStatus)
    {
        pstSysInfo->ucSrvStatus = TAF_PH_INFO_NO_SERV;
    }

}
VOS_VOID  MN_PH_GetSysInfoSysModeEx(
    TAF_PH_SYSINFO_STRU                 *pstSysInfo
)
{
    TAF_SYS_SUBMODE_ENUM_UINT8          enSubMode;

    /* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, begin */

    /* AppNetworkInfo��Ŀǰֻ�洢3GPP����Ϣ��������1x CDMA�ķ���״̬��ע��״̬�ӳ��ϱ� */
    if (TAF_SDC_SYS_MODE_CDMA_1X == TAF_SDC_GetSysMode())
    {

        pstSysInfo->ucSysMode = MN_PH_SYS_MODE_EX_CDMA_RAT;

        pstSysInfo->ucSysSubMode = MN_PH_SUB_SYS_MODE_EX_CDMA20001X_RAT;

        return;
    }

    if (TAF_SDC_SYS_MODE_EVDO == TAF_SDC_GetSysMode())
    {

        pstSysInfo->ucSysMode = MN_PH_SYS_MODE_EX_EVDO_RAT;

        pstSysInfo->ucSysSubMode = MN_PH_SUB_SYS_MODE_EX_EVDORELA_RAT;

        return;
    }
    if (TAF_SDC_SYS_MODE_HYBRID == TAF_SDC_GetSysMode())
    {

        pstSysInfo->ucSysMode = MN_PH_SYS_MODE_EX_HYBRID_RAT;

        pstSysInfo->ucSysSubMode = MN_PH_SUB_SYS_MODE_EX_EVDORELA_RAT;

        return;
    }

    /* 3GPP�Ĵ���,��ע��״̬�ͷ���״̬���ӳ��ϱ���ҪȡAppNetworkInfo����Ϣ */
    switch(TAF_SDC_GetAppSysMode())
    {
        case TAF_SDC_SYS_MODE_GSM:
            pstSysInfo->ucSysMode = MN_PH_SYS_MODE_EX_GSM_RAT;
            enSubMode = TAF_SDC_GetAppSysSubMode();
            break;
    /* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, end */

        case TAF_SDC_SYS_MODE_WCDMA:
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                pstSysInfo->ucSysMode = MN_PH_SYS_MODE_EX_WCDMA_RAT;

                /*W�£�^SYSINFO��ѯ��ϵͳ��ģʽ������̬��ϵͳ��ģʽ */
                enSubMode = Sta_GetSysSubMode_W(gstMmaValue.pg_StatusContext->ucDataTranStatus,
                                                            gstMmaValue.pg_StatusContext->ucDataTranMode);
            }
            else
            {
                pstSysInfo->ucSysMode = MN_PH_SYS_MODE_EX_TDCDMA_RAT;

                /*TD�£�^SYSINFO��ѯ��ϵͳ��ģʽ������̬��ϵͳ��ģʽ */
                enSubMode = Sta_GetSysSubMode_Td(gstMmaValue.pg_StatusContext->ucDataTranStatus,
                                                            gstMmaValue.pg_StatusContext->ucDataTranMode);
            }
            break;

        case TAF_SDC_SYS_MODE_LTE:
            pstSysInfo->ucSysMode = MN_PH_SYS_MODE_EX_LTE_RAT;
            /* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, begin */
            enSubMode  = TAF_SDC_GetAppSysSubMode();
            /* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, end */
            break;

        default:
            pstSysInfo->ucSysMode    = MN_PH_SYS_MODE_EX_NONE_RAT;

            enSubMode                = TAF_SYS_SUBMODE_NONE;
            break;
    }


    /* ��ϵͳ��ģʽ����ת�� */
    MN_PH_ConvertSysSubModeToAtFormat(enSubMode, &(pstSysInfo->ucSysSubMode));

    return;
}


VOS_VOID  MMA_GetSysInfoSysMode(
    TAF_PH_SYSINFO_STRU                *pstSysInfo
)
{
    switch (TAF_SDC_GetAppSysMode())
    {
        case TAF_SDC_SYS_MODE_GSM:
            pstSysInfo->ucSysMode    = TAF_PH_INFO_GSM_RAT;
            pstSysInfo->ucSysSubMode = TAF_SDC_GetAppSysSubMode();
            break;

        case TAF_SDC_SYS_MODE_WCDMA:
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                pstSysInfo->ucSysMode = TAF_PH_INFO_WCDMA_RAT;

                /* W�£�^SYSINFO��ѯ��ϵͳ��ģʽ������̬��ϵͳ��ģʽ */
                pstSysInfo->ucSysSubMode = Sta_GetSysSubMode_W(gstMmaValue.pg_StatusContext->ucDataTranStatus,
                                                               gstMmaValue.pg_StatusContext->ucDataTranMode);
            }
            else
            {
                pstSysInfo->ucSysMode = TAF_PH_INFO_TD_SCDMA_RAT;

                /* TD�£�^SYSINFO��ѯ��ϵͳ��ģʽ������̬��ϵͳ��ģʽ */
                pstSysInfo->ucSysSubMode = Sta_GetSysSubMode_Td(gstMmaValue.pg_StatusContext->ucDataTranStatus,
                                                                gstMmaValue.pg_StatusContext->ucDataTranMode);
            }
            break;

#if(FEATURE_ON == FEATURE_LTE)
        case TAF_SDC_SYS_MODE_LTE:
            /*  SYSINFO��GUʹ�õ������L��ʱ����W��ʾ */
            pstSysInfo->ucSysMode    = TAF_PH_INFO_WCDMA_RAT;
            pstSysInfo->ucSysSubMode = TAF_SYS_SUBMODE_WCDMA;

            break;
#endif

         default:
            pstSysInfo->ucSysMode    = TAF_PH_INFO_NONE_RAT;
            pstSysInfo->ucSysSubMode = TAF_SYS_SUBMODE_NONE;
            break;
    }
}

VOS_VOID MN_PH_AppRoamStatusRpt( VOS_VOID )
{
    TAF_PH_SYSINFO_STRU                 sys_info;
    VOS_INT32                           lInvalidRssi;

    VOS_INT32                           lRssiValue;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    sys_info.ucSrvStatus = TAF_SDC_GetServiceStatus();
    sys_info.ucSrvDomain = TAF_SDC_GetServiceDomain();
    enSysMode            = TAF_SDC_GetSysMode();

    if (TAF_SDC_SYS_MODE_GSM == enSysMode)
    {
        lInvalidRssi = MMA_UTRA_RSSI_INVALID;
    }
    else
    {
        lInvalidRssi = MMA_UTRA_RSCP_INVALID;
    }

    if (TAF_SDC_SYS_MODE_GSM == enSysMode)
    {
        lRssiValue = gstMmaValue.stCerssiValue.aRssi[0].u.stGCellSignInfo.sRssiValue;
    }
    else
    {
        lRssiValue = gstMmaValue.stCerssiValue.aRssi[0].u.stWCellSignInfo.sRscpValue;
    }

    if(lInvalidRssi >= lRssiValue)
    {
        sys_info.ucSrvStatus = TAF_REPORT_SRVSTA_NO_SERVICE;
        sys_info.ucSrvDomain = TAF_PH_INFO_NO_DOMAIN;
    }


    if (VOS_TRUE == gstMmaValue.pg_StatusContext->ulTimMaxFlg )
    {
        sys_info.ucSrvStatus = TAF_PH_INFO_DEEP_SLEEP;
        sys_info.ucSrvDomain = TAF_PH_INFO_NO_DOMAIN;
    }

    if ( TAF_PH_INFO_NOMRL_SERV != sys_info.ucSrvStatus )
    {
        /* ������Ч ���������ж� */
        MN_INFO_LOG("MN_PH_AppRoamStatusRpt: service is not normal services");
        return;
    }

    if ( TAF_PH_ROAMING == MMA_IsRoam(TAF_SDC_GetRoamFlag()) )
    {
        sys_info.ucRoamStatus = TAF_PH_INFO_ROMAING;
    }
    else
    {
        sys_info.ucRoamStatus = TAF_PH_INFO_NONE_ROMAING;
    }

    if ( sys_info.ucRoamStatus != g_ucMnPhRoamStatus )
    {
        g_ucMnPhRoamStatus = sys_info.ucRoamStatus;
        MN_PH_RoamingRpt( g_ucMnPhRoamStatus );
    }

}


VOS_VOID MN_PH_GetRssilvForCsqlvlExt (
    VOS_INT32                           lRssiValue,
    VOS_UINT8                           ucCurRaForSysInfo,
    MN_PH_CSQLVLEXT_RSSILV_ENUM_UINT8  *pucRssilv
)
{
    VOS_UINT32                          ulAbsRssiValue;
    VOS_UINT32                          aulGsmRssi[MN_PH_CSQLVLEXT_RSSILV_BUTT] = {105, 90, 84, 82, 80, 76};
    VOS_UINT32                          aulWcdmaRscp[MN_PH_CSQLVLEXT_RSSILV_BUTT] = {105, 102, 96, 94, 92, 88};
    VOS_UINT32                         *pulRssiConvertRule;

    /* ȡ����ֵ */
    ulAbsRssiValue = (VOS_UINT32)(-lRssiValue);

    if (TAF_PH_RA_GSM == ucCurRaForSysInfo)
    {
        pulRssiConvertRule = aulGsmRssi;
    }
    else
    {
        pulRssiConvertRule = aulWcdmaRscp;
    }

    /* ����SRS���������ź�ǿ�ȶ�Ӧ��ϵ��ȡ���ź�ǿ�ȸ��� */
    if (ulAbsRssiValue <= pulRssiConvertRule[MN_PH_CSQLVLEXT_RSSILV_5])
    {
        *pucRssilv = MN_PH_CSQLVLEXT_RSSILV_VALUE_99; /* 5�� */
    }
    else if (ulAbsRssiValue <= pulRssiConvertRule[MN_PH_CSQLVLEXT_RSSILV_4])
    {
        *pucRssilv = MN_PH_CSQLVLEXT_RSSILV_VALUE_80; /* 4�� */
    }
    else if (ulAbsRssiValue <= pulRssiConvertRule[MN_PH_CSQLVLEXT_RSSILV_3])
    {
        *pucRssilv = MN_PH_CSQLVLEXT_RSSILV_VALUE_60; /* 3�� */
    }
    else if (ulAbsRssiValue <= pulRssiConvertRule[MN_PH_CSQLVLEXT_RSSILV_2])
    {
        *pucRssilv = MN_PH_CSQLVLEXT_RSSILV_VALUE_40; /* 2�� */
    }
    else if (ulAbsRssiValue <= pulRssiConvertRule[MN_PH_CSQLVLEXT_RSSILV_1])
    {
        *pucRssilv = MN_PH_CSQLVLEXT_RSSILV_VALUE_20; /* 1�� */
    }
    else
    {
        *pucRssilv = MN_PH_CSQLVLEXT_RSSILV_VALUE_0;  /* 0�� */
    }

    return;
}

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-11, begin */

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-11, end */


VOS_VOID MMA_GetPhIccType(VOS_UINT16 ClientId,VOS_UINT8 OpId)

{
    TAF_PH_UICC_TYPE stIcc_Type;
    VOS_UINT8 ucSimType;
    VOS_UINT8 usPinType;


    if(TAF_PH_USIM_ROMSIM == MMA_GetUsimStatus(VOS_FALSE))
    {
        stIcc_Type.MmaIccType = TAF_PH_ICC_UNKNOW;
    }
    else
    {
        (VOS_VOID)MMA_PhoneGetUsimType(&ucSimType);

        if(MMA_USIM_TYPE_USIM == ucSimType)
        {
            stIcc_Type.MmaIccType = TAF_PH_ICC_USIM;
        }
        else if(MMA_USIM_TYPE_SIM == ucSimType)
        {
            stIcc_Type.MmaIccType = TAF_PH_ICC_SIM;
        }
        else
        {
        }
    }

    usPinType = USIMM_PIN;

    (VOS_VOID)NAS_USIMMAPI_GetPinStatus(&usPinType, &stIcc_Type.MmaIccPinStatus, &stIcc_Type.MmaIccPinVerifyStatus, &stIcc_Type.ucRemainTimes);

    MMA_ParaQueryReport(ClientId, OpId, TAF_PH_ICC_TYPE_PARA,TAF_ERR_NO_ERROR, (VOS_VOID*)(&stIcc_Type));
    return;
}



VOS_VOID MMA_GetPhIccStatus(VOS_UINT16 ClientId,VOS_UINT8 OpId)
{
    TAF_USIM_STATUS                     ICC_STATE;
    ICC_STATE                           = MMA_GetUsimStatus(VOS_FALSE);
    MMA_ParaQueryReport(ClientId, OpId, TAF_PH_ICC_STATUS_PARA,TAF_ERR_NO_ERROR, &ICC_STATE);
    return;
}



VOS_VOID TAF_MMA_SndAtIccStatusInd(
    VOS_UINT8                           ucSimStatus,
    VOS_UINT8                           ucSimLockStatus
)
{
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent = VOS_NULL_PTR;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("TAF_MMA_SndAtIccStatusInd:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    /* ��ʼ���绰�ϱ��¼� */
    MMA_InitEventInfoOP(pstPhoneEvent);

    /* ��д�¼�����Ϊ��״̬��Ϣָʾ:TAF_PH_EVT_USIM_INFO_IND*/
    pstPhoneEvent->PhoneEvent             = TAF_PH_EVT_USIM_INFO_IND;

    /* ��д�¼��ͻ�������Ϊ�㲥�¼� */
    pstPhoneEvent->ClientId               = MMA_CLIENTID_BROADCAST;
    pstPhoneEvent->OpId                   = MMA_OP_ID_INTERNAL;

    /* ��д�ϱ��Ŀ�״̬������״̬ */
    pstPhoneEvent->SimStatus              = ucSimStatus;
    pstPhoneEvent->MeLockStatus           = ucSimLockStatus;

    /* ���õ绰�����ϱ����� */
    MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);
    return;
}



VOS_VOID MMA_QueryProc(VOS_UINT16 ClientId,
                       VOS_UINT8        OpId,
                       VOS_UINT8     *pMsg)
{
    TAF_PARA_TYPE ParaQuery;

    ParaQuery = (TAF_PARA_TYPE)(*pMsg);

    if(  (ParaQuery > (TAF_PH_PRODUCT_NAME_PARA + 1))
       ||(ParaQuery < TAF_PH_MS_CLASS_PARA)
      )
    {
          MMA_WARNINGLOG("MMA_QueryProc():WARNING:Receive Error ParaQuery");
          MMA_ReportParaQueryError(ClientId, OpId,
                                   TAF_ERR_CAPABILITY_ERROR,
                                   ParaQuery);
          return;
    }

    /*���ݲ�ѯ����ֵ���ַ����ú���*/
    switch ( ParaQuery)
    {

        /*��ȡIMSI*/
        case TAF_PH_IMSI_ID_PARA:
            MMA_PhoneGetImsi(ClientId, OpId);
            break;

        /* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-1, begin */

        /* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-1, end */

        /*==>A32D06630*/
        case TAF_PH_CELL_RSCP_VALUE_PARA:   /*Get cell RCSP & Cell Info*/
            MMA_GetPhCellRscp(ClientId, OpId);
            break;

        case TAF_PH_UE_RFPOWER_FREQ_PARA:   /*Get UE's RF power and uplink frequency*/
            MMA_GetPhUeRfPowerFreq(ClientId, OpId);
            break;
        /*<==A32D06630*/





        /* ɾ��MMA_PhoneGetRoamSta */

        /*��ȡ��״̬*/
        case TAF_PH_DOMAIN_PARA :
            MMA_PhoneGetDomain(ClientId,OpId);
            break;

        /* case TAF_PH_WHOLE_DATA */

        /*��ȡ�ֻ���Ʒ����*/
        case TAF_PH_PRODUCT_NAME_PARA:
            MMA_PhoneGetProductName(ClientId, OpId);
            break;

        /* case TAF_PH_IDENTIFICATION_INFO_PARA */



        case TAF_PH_ICC_ID:
            MMA_PhoneGetIccId(ClientId, OpId);
            break;


        case TAF_PH_ICC_TYPE_PARA:  /*Get the UICC type*/
            MMA_GetPhIccType(ClientId, OpId);
            break;
        case TAF_PH_ICC_STATUS_PARA:    /*Get the UICC state*/
            MMA_GetPhIccStatus(ClientId, OpId);
            break;


        case TAF_PH_SIMLOCK_VALUE_PARA:
            TAF_MMA_RcvSimLockQry(ClientId, OpId);
            break;

        /* Deleted by k902809 for Iteration 11, 2015-3-30, begin */

        /* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-30, end */

        /* Deleted by k902809 for Iteration 11, 2015-3-30, begin */

        /* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-30, end */

        /* Deleted by k902809 for Iteration 11, 2015-3-28, begin */

        /* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-28, end */

        default:
            MMA_WARNINGLOG("MMA_QueryProc():WARNING:No funcation fit the case");
            break;
    }
    return;
}




VOS_VOID MMA_PhoneGetProductName( VOS_UINT16     ClientId, VOS_UINT8    OpId )
{
    VOS_UINT8     ucParalen;
    VOS_VOID      *pPara;

    /*��������׼��*/
    /*��ȡ��״̬��Ϣ����*/
    ucParalen = (VOS_UINT8)VOS_StrLen((VOS_CHAR *)(gstMmaValue.stMeInfo.ProductName.aucProductName)) + 1;
    if ( ucParalen > TAF_PH_PRODUCT_NAME_LEN)
    {
        gstMmaValue.stMeInfo.ProductName.aucProductName[TAF_PH_PRODUCT_NAME_LEN] = '\0';
        /*����һ��warning��ӡ*/
        MMA_WARNINGLOG("MMA_PhoneGetProductName():WARNING:Length of Product is too Long!");
    }

    pPara = (VOS_VOID*)gstMmaValue.stMeInfo.ProductName.aucProductName;
    /*ʹ�������ϱ����������ݴ���TAFm*/
    MMA_ParaQueryReport(ClientId, OpId, TAF_PH_PRODUCT_NAME_PARA,TAF_ERR_NO_ERROR, pPara);

    return;
}

/*MMA_PhoneGetIdentificationInfo()
  MMA_PhoneGetRevisionIdentification()
  MMA_PhoneGetWholeInfo()
  MMA_FillWholeInfo()*/

TAF_PH_ROAM_STA MMA_IsRoam(
    VOS_UINT8                           ucRoamFlg
)
{
    TAF_SDC_REG_STATUS_ENUM_UINT8       enCsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enPsRegStatus;

    enCsRegStatus  = TAF_SDC_GetAppCsRegStatus();
    enPsRegStatus  = TAF_SDC_GetAppPsRegStatus();

    /* ����һ����ע��ɹ����ҷ�����ʱ */
    if ( (VOS_FALSE                            == ucRoamFlg)
      && ((TAF_SDC_REG_REGISTERED_HOME_NETWORK == enCsRegStatus)
       || (TAF_SDC_REG_REGISTERED_HOME_NETWORK == enPsRegStatus)) )
    {
        return TAF_PH_NO_ROAM;
    }
    /* ����һ����ע��ɹ���������ʱ */
    if ( (VOS_TRUE                     == ucRoamFlg)
      && ((TAF_SDC_REG_REGISTERED_ROAM == enCsRegStatus)
       || (TAF_SDC_REG_REGISTERED_ROAM == enPsRegStatus)) )
    {
        return TAF_PH_ROAMING;
    }
    else
    {
        return TAF_PH_ROAM_UNKNOW;
    }

}


VOS_VOID MMA_ReportParaQueryError( VOS_UINT16       ClientId,
                                   VOS_UINT8              OpId,
                                   VOS_UINT16           usErrorCode,
                                   TAF_PARA_TYPE ParaType)
{
    if (TAF_ERR_NO_ERROR != usErrorCode)
    {
        MMA_WARNINGLOG1("MMA_ReportParaQueryError():WARNING:Para query falied, Error Code = %d", usErrorCode);

        /*����APP������ѯʧ���ϱ�����*/
        MN_QRYPARA_SendMsg(ClientId, OpId, ParaType,usErrorCode, TAF_NULL_PTR);

    }
    return;
}
/*lint -e429*/
VOS_VOID MMA_ParaQueryReport(VOS_UINT16            ClientId,
                              VOS_UINT8                   OpId,
                              TAF_PARA_TYPE      QueryType,
                              VOS_UINT16         usErrorCode,
                              VOS_VOID                 *pucPara)
{
    /*����APP��ѯ�����ϱ�����*/
    MN_QRYPARA_SendMsg(ClientId, OpId, QueryType,usErrorCode, pucPara);

    return;
}
/*lint +e429*/

VOS_UINT32  MMA_TiAlloc(VOS_UINT8        ucModule,
                        VOS_UINT16    ClientId,
                        VOS_UINT8           Id,
                        TAF_PHONE_EVENT  PhoneEvt,
                        VOS_UINT8       *pucTi)
{

    if (VOS_NULL_PTR == pucTi)
    {
        MMA_WARNINGLOG("MMA_TiAlloc():WARNING:pucTi is NULL PTR!");
        return MMA_FAILURE;
    }
    switch (ucModule)
    {
        case TAF_MMA:
            if ( TAF_PH_EVT_OP_PIN_CNF == PhoneEvt )
            {
                if ( MMA_TI_USED == gastMmaTiTab[MMA_PH_PIN_TI].ucUsed)
                {
                    return MMA_FAILURE;
                }
                gastMmaTiTab[MMA_PH_PIN_TI].ClientId          = ClientId;
                gastMmaTiTab[MMA_PH_PIN_TI].Id                = Id;
                gastMmaTiTab[MMA_PH_PIN_TI].PhoneEvent        = PhoneEvt;
                /* BEGIN: Modified by liuyang id:48197, 2006/3/8   PN:A32D02371*/
                gastMmaTiTab[MMA_PH_PIN_TI].ucUsed            = MMA_TI_USED;
                /* END:   Modified by liuyang id:48197, 2006/3/8 */
                return TAF_SUCCESS;
            }
            switch (gstMmaValue.pg_StatusContext->ulFsmState)
            {
                case STA_FSM_NULL:
                case STA_FSM_ENABLE:
                case STA_FSM_RESTART:
                case STA_FSM_STOP :
                    /*TI����ɹ�*/
                    gastMmaTiTab[0].ClientId          = ClientId;
                    gastMmaTiTab[0].Id                = Id;
                    gastMmaTiTab[0].PhoneEvent        = PhoneEvt;
                    gastMmaTiTab[0].ucUsed            = MMA_TI_USED;
                    *pucTi = 0;
                    return MMA_SUCCESS;

                /* Deleted by h00313353 for Iteration 13, 2015-4-13 */
                case STA_FSM_PLMN_LIST:
                case STA_FSM_PLMN_RESEL:
                case STA_FSM_PLMN_SEL:
                /* Deleted by h00313353 for Iteration 13, 2015-4-13 */
                    /*TI����ɹ�*/
                    gastMmaTiTab[1].ClientId          = ClientId;
                    gastMmaTiTab[1].Id                = Id;
                    gastMmaTiTab[1].PhoneEvent        = PhoneEvt;
                    gastMmaTiTab[1].ucUsed            = MMA_TI_USED;
                    *pucTi = 1;
                    return MMA_SUCCESS;
                default:
                    MMA_WARNINGLOG("MMA_TiAlloc():WARNING:Error in Status FSM!");
                    return MMA_FAILURE;
            }
       default:
            /*���Ӵ�ӡ��Ϣ*/
            MMA_WARNINGLOG("MMA_TiAlloc():WARNING:Error input Module Name!");
            return MMA_FAILURE;
    }
}




/**********************************************************
 Function:     MMA_GetIdByTi
 Description:  ��TI��¼������TI��ȡ������ClientId��Id
 Calls:
 Data Accessed:
 Data Updated:
 Input:        ucModule����ģ�����ͣ�TAF_STATUS,
               Ti��TIֵ
 Output:       pClientId��APP��AT��ʶ
               pId�� APP��AT������ʶ
 Return:       MMA_SUCCESS���ɹ�
               MMA_FAILURE��ʧ��
 Others:

  1.��    ��   : 2006��3��8��
    ��    ��   : liuyang id:48197
    �޸�����   : ���ⵥ�ţ�A32D02371��ʹ�ú궨���滻ԭ�еĳ���
**********************************************************/
VOS_UINT32  MMA_GetIdByTi (VOS_UINT8         ucModule,
                           VOS_UINT8         ucTi,
                           VOS_UINT16    *pClientId,
                           VOS_UINT8           *pId,
                           TAF_PHONE_EVENT  *PhoneEvt)
{
    /*�����б���Ч��*/
    if ( (VOS_NULL_PTR == pClientId) || (VOS_NULL_PTR == pId) )
    {
        MMA_WARNINGLOG("MMA_GetIdByTi():WARNING:pClientId & pId are NULL PTR!!");
        return MMA_FAILURE;
    }
    switch (ucModule)
    {
        case TAF_MMA:
            /*Ti=2ר������PIN����*/
            if ( MMA_PH_PIN_TI == ucTi )
            {
                *pClientId = gastMmaTiTab[MMA_PH_PIN_TI].ClientId;
                *pId       = gastMmaTiTab[MMA_PH_PIN_TI].Id;
                *PhoneEvt  = gastMmaTiTab[MMA_PH_PIN_TI].PhoneEvent;
                /* BEGIN: Modified by liuyang id:48197, 2006/3/8   PN:A32D02371*/
                /*���ʹ�ñ�־*/
                /*gastMmaTiTab[MMA_PH_PIN_TI].ucUsed   = 0;
                gastMmaTiTab[MMA_PH_PIN_TI].ClientId = 0;
                gastMmaTiTab[MMA_PH_PIN_TI].Id       = 0;*/
                gastMmaTiTab[MMA_PH_PIN_TI].ucUsed   = MMA_TI_UNUSED;
                gastMmaTiTab[MMA_PH_PIN_TI].ClientId = MMA_CLIENTID_NONE;
                gastMmaTiTab[MMA_PH_PIN_TI].Id       = MMA_OP_ID_INTERNAL;
                /* END:   Modified by liuyang id:48197, 2006/3/8 */
                return MMA_SUCCESS;
            }
            if (ucTi > TAF_MAX_STATUS_TI)
            {   /*TI��Ч��Χ��0-1*/
                MMA_WARNINGLOG("MMA_GetIdByTi():WARNNING:TI is out of MAX");
                return MMA_FAILURE;
            }
            /* ����Ҫ�ж�g_TafPhoneTiTab[ucTi].ucUsed,��Ϊ����ʱû��ʹ��*/
            *pClientId = gastMmaTiTab[ucTi].ClientId;
            *pId       = gastMmaTiTab[ucTi].Id;
            *PhoneEvt  = gastMmaTiTab[ucTi].PhoneEvent;
            /* BEGIN: Modified by liuyang id:48197, 2006/3/8   PN:A32D02371*/
            /*���ʹ�ñ�־*/
            /*gastMmaTiTab[ucTi].ucUsed   = 0;
            gastMmaTiTab[ucTi].ClientId = 0;
            gastMmaTiTab[ucTi].Id       = 0;*/
            gastMmaTiTab[ucTi].ucUsed   = MMA_TI_UNUSED;
            gastMmaTiTab[ucTi].ClientId = MMA_CLIENTID_NONE;
            gastMmaTiTab[ucTi].Id       = MMA_OP_ID_INTERNAL;
            /* END:   Modified by liuyang id:48197, 2006/3/8 */
            return MMA_SUCCESS;
        default:
            /*�����Ӵ�ӡ��Ϣ*/
            MMA_WARNINGLOG("MMA_GetIdByTi():WARNING:Error input Module Name!");
            return MMA_FAILURE;
    }
}

/* MMA_InitUsimInfoɾ�� */
/* MMA_UpdateBandNvRefForbBand�ŵ�TafMmaProcNvim�ļ��� */
/* MMA_UpdateForbBandStatusToNV�ŵ�TafMmaProcNvim�ļ��� */

/* TAF_MMA_InitOrigMeInfo�ƶ�λ�� */




VOS_VOID MN_MMA_SetDefaultRatPrioList(
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList
)
{
    VOS_UINT8                           i;
#if (FEATURE_OFF == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulGsmForbiddenFlg;
#endif

    i = 0;

#if (FEATURE_ON == FEATURE_LTE)
    /* ƽ̨���뼼��֧��LTEʱ��������֧��LTE */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
        pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_LTE;
        i ++;
    }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* ƽ̨���뼼��֧��UTRANʱ��������֧��1X */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupport1x())
    {
        pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_1X;
        i ++;
    }

    if (VOS_TRUE == TAF_SDC_IsPlatformSupportHrpd())
    {
        pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_HRPD;
        i ++;
    }
#else
    /* ƽ̨���뼼��֧��UTRANʱ��������֧��WCDMA */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportUtran())
    {
        pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_WCDMA;
        i ++;
    }

    /* ƽ̨���뼼��֧��GSM����Ӳ��֧��GSMƵ��ʱ��������֧��GSM */
    ulGsmForbiddenFlg = MMA_IsGsmForbidden();
    if ((VOS_TRUE == TAF_SDC_IsPlatformSupportGsm())
     && (VOS_FALSE == ulGsmForbiddenFlg))
    {
        pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_GSM;
        i ++;
    }
#endif

    pstRatPrioList->ucRatOrderNum  = i;

    /* ������ֵΪBUTT */
    for (; i < TAF_PH_MAX_GUL_RAT_NUM; i ++)
    {
        pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_BUTT;
    }
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */

    return;
}
VOS_VOID TAF_MMA_ReadNvimRatPrioList(
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          k;
    TAF_PH_NVIM_RAT_ORDER_STRU          stRatPrioList;
    VOS_UINT32                          ulLength;

    ulLength        = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_RAT_PRIO_LIST, &ulLength);
    if (ulLength > sizeof(TAF_PH_NVIM_RAT_ORDER_STRU))
    {
        return;
    }

    PS_MEM_SET(&stRatPrioList, 0X0, ulLength);

    /* ��NV�л�ȡ���뼼�����ȼ� */
    if (NV_OK != NV_Read (en_NV_Item_RAT_PRIO_LIST, &stRatPrioList,
                         ulLength))
    {
        MN_MMA_SetDefaultRatPrioList(pstRatPrioList);

        return;
    }

    PS_MEM_CPY(pstRatPrioList, &stRatPrioList, ulLength);

    /* ���NV������Ч�� */
    for ( i = 0 ; i < pstRatPrioList->ucRatOrderNum; i++ )
    {
        /* �ж��Ƿ������Ч�Ľ��뼼�� */
        /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
        if (pstRatPrioList->aenRatOrder[i] >= TAF_MMA_RAT_BUTT)
        /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
        {
            MN_MMA_SetDefaultRatPrioList(pstRatPrioList);

            return;
        }

        /* �ж��Ƿ�����ظ��Ľ��뼼�� */
        for (k = i + 1 ; k < pstRatPrioList->ucRatOrderNum; k++ )
        {
            if (pstRatPrioList->aenRatOrder[i] == pstRatPrioList->aenRatOrder[k])
            {
                MN_MMA_SetDefaultRatPrioList(pstRatPrioList);

                return;
            }
        }
    }

    /* ɾ��ƽ̨��֧�ֵĽ��뼼�� */
    TAF_MMA_DelPlatformUnsupportedRat(pstRatPrioList);

    /* ������н��뼼��ƽ̨����֧�֣�ʹ��ƽ̨Ĭ��ֵ */
    if (0 == pstRatPrioList->ucRatOrderNum)
    {
        MN_MMA_SetDefaultRatPrioList(pstRatPrioList);
    }
    else
    {
        /* ������ֵΪBUTT */
        for (i = pstRatPrioList->ucRatOrderNum; i < TAF_PH_MAX_GUL_RAT_NUM; i ++)
        {
            /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
            pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_BUTT;
            /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
        }
    }

    return;
}



/* ɾ�� MMA_InitMeInfo */


/* TAF_MMA_InitRssiValue�ƶ�λ�� */
/* MMA_InitGobalValueɾ�� */

VOS_VOID    MMA_InitCm(VOS_VOID)
{

#ifndef __PS_WIN32_RECUR__
    TAF_MMA_SndPowerIndMsg();
#else
    Aps_PowerOff();
#endif

    NAS_RabmPowerOff();

    Sm_PowerOff();

    /* ɾ���ô��������ã�CALLģ���յ�power offָʾ��Ϣ����� */

    MN_MSG_PowerOff();

    NAS_CC_PowerOff();

    SMS_Poweroff();

    SSA_PowerOff();

    Ss_Init();

    Tc_TaskInit();

}

/* ɾ��MMA_Init1 */

/* MMA_ReadSimCPHSOperNameStr */

VOS_BOOL   MMA_IsNeedToDisplayCPHSOperNameStr(VOS_VOID)
{
    TAF_SDC_SPN_FILE_INFO_STRU         *pstUsimSpnFileInfo = VOS_NULL_PTR;
    TAF_SDC_CPHS_FILE_INFO_STRU        *pstCphsFileInfo    = VOS_NULL_PTR;
    VOS_BOOL                            bRptFlg;

    bRptFlg = VOS_FALSE;

    pstUsimSpnFileInfo = TAF_SDC_GetUsimSpnFileInfo();
    pstCphsFileInfo    = TAF_SDC_GetChpsFileInfo();

    /* CPHS�ļ���Ч����SPN��Чʱ���ϱ�^PNN,^OPL */
    if (0 != pstCphsFileInfo->stCPHSOperName.ucLength)
    {
        if (0 == pstUsimSpnFileInfo->stSpnOperName.ucLength)
        {
            bRptFlg = VOS_TRUE;
        }
    }

    return bRptFlg;
}
VOS_VOID   MMA_ReportOPLParaForCPHSDisplay(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId
)
{
    TAF_PH_USIM_OPL_CNF_STRU            *pstOPL;

    pstOPL   = (TAF_PH_USIM_OPL_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                            sizeof(TAF_PH_USIM_OPL_CNF_STRU));

    if(VOS_NULL_PTR == pstOPL)
    {
        MMA_ReportParaQueryError(ClientId, OpId,
                            TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_OPL_PARA);
        return;
    }

    MMA_MEM_SET(pstOPL, 0, sizeof(TAF_PH_USIM_OPL_CNF_STRU));

    MMA_ParaQueryReport(ClientId, OpId,
                        TAF_PH_OPL_PARA, TAF_ERR_NO_ERROR, pstOPL);

    PS_MEM_FREE(WUEPS_PID_MMA, pstOPL);

    return;

}

/* MMA_CovertCPHSOperNameStrToPNNFormat */

VOS_VOID   MMA_ReportPNNParaFromCPHSOperNameStr(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId
)
{

    TAF_PH_USIM_PNN_CNF_STRU            *pstPNN          = VOS_NULL_PTR;
    TAF_SDC_CPHS_FILE_INFO_STRU         *pstChpsFileInfo = VOS_NULL_PTR;

    pstChpsFileInfo = TAF_SDC_GetChpsFileInfo();

    pstPNN   = (TAF_PH_USIM_PNN_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                               sizeof(TAF_PH_USIM_PNN_CNF_STRU));

    if(VOS_NULL_PTR == pstPNN)
    {
        MMA_ReportParaQueryError(ClientId, OpId,TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_PNN_PARA);
        return;
    }

    PS_MEM_SET(pstPNN, 0, sizeof(TAF_PH_USIM_PNN_CNF_STRU));

    PS_MEM_CPY(pstPNN->PNNRecord[0].stOperNameLong.aucOperatorName, pstChpsFileInfo->stCPHSOperName.aucOperatorName, TAF_SDC_MAX_OPER_LONG_NAME_LEN);

    pstPNN->TotalRecordNum = 1;
    MMA_ParaQueryReport(ClientId, OpId,
                                TAF_PH_PNN_PARA, TAF_ERR_NO_ERROR, pstPNN);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPNN);
    return;
}

/* MMA_ReadCPHSOperNameStrFileCnf */
/* MMA_ReadCPHSOperNameStrFileExpired */
/* MMA_ReadSpnFileExpired */
/* MMA_ReadSpnFileCnf */




VOS_UINT32 Taf_PhoneGetOperNameInfo( TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU *pstOperName )
{
    TAF_PH_OPERATOR_NAME_STRU stOperNameTmp;
    VOS_UINT32                ulRet = MMA_FAILURE;
    TAF_UCHAR                 aucSpnName[TAF_PH_OPER_NAME_LONG];

    /*������Ч���ж�*/
    if ( VOS_NULL_PTR == pstOperName )
    {
        MMA_WARNINGLOG("Taf_PhoneGetOperNameInfo():WARNING:NULL PTR");
        return ulRet;
    }

    stOperNameTmp = pstOperName->OperName;
    MMA_INFOLOG1("Taf_PhoneGetOperNameInfo():stOperNameTmp.Mcc =",(VOS_INT32)stOperNameTmp.PlmnId.Mcc);
    MMA_INFOLOG1("Taf_PhoneGetOperNameInfo():stOperNameTmp.Mnc =",(VOS_INT32)stOperNameTmp.PlmnId.Mnc);

    PS_MEM_SET(aucSpnName,0x00,TAF_PH_OPER_NAME_LONG);

    /*�������ṩ����Ϣ,��ȡ����NVIM��ʣ�����Ӫ������*/
    switch ( pstOperName->ListOp )
    {
        /*ͨ��PLMN��ó����ֺͶ�����*/
        case TAF_PH_OPER_NAME_PLMN2ALPHANUMERICNAME :
            break;

        /*ͨ�������ֻ�ȡ��Ӧ�ĳ����ֺ�PLMN*/
        case TAF_PH_OPER_NAME_SHORTNAME2OTHERS :
            ulRet = MMA_PhoneGetOperInfoByShortNameFromOperTbl(&stOperNameTmp);
            if (MMA_SUCCESS == ulRet)
            {
                pstOperName->OperName = stOperNameTmp;
            }
            break;

        /*ͨ�������ֻ�ȡ��Ӧ�Ķ����ֺ�PLMN*/
        case TAF_PH_OPER_NAME_LONGNAME2OTERS :
            ulRet = MMA_PhoneGetOperInfoByLongNameFromOperTbl(&stOperNameTmp);
            if (MMA_SUCCESS == ulRet)
            {
                pstOperName->OperName = stOperNameTmp;
            }
            break;

        default:
            MMA_WARNINGLOG("Taf_PhoneGetOperNameInfo():WARNING:error ListOp");
            break;
    }
    return ulRet;
}
VOS_UINT32 MMA_PhoneFindNtwkNameByPlmnId( TAF_PH_OPERATOR_NAME_STRU   *pstOperName)
{

    VOS_UINT16                          usTotalNtwkNum;
    VOS_UINT16                          i = 0;
    VOS_BOOL                            bFound = VOS_FALSE;
    VOS_BOOL                            bContinueSearch = VOS_TRUE;
    TAF_PH_OPERATOR_NAME_TBL_STRU       *pstNetworkNameTbl = VOS_NULL_PTR;

    TAF_PLMN_ID_STRU tmpPlmnId = pstOperName->PlmnId;

    MMA_INFOLOG1("orig MMA_PhoneFindNtwkNameByPlmnId():tmpPlmnId.Mcc =",(VOS_INT32)tmpPlmnId.Mcc);
    MMA_INFOLOG1("orig MMA_PhoneFindNtwkNameByPlmnId():tmpPlmnId.Mnc =",(VOS_INT32)tmpPlmnId.Mnc);

    tmpPlmnId.Mcc &= 0x0fff;
    tmpPlmnId.Mnc &= 0x0fff;

    if( 0x0F == ((0x0f00 & tmpPlmnId.Mnc) >> 8))
    {
        tmpPlmnId.Mnc &= 0x00ff;
    }
    MMA_INFOLOG1("MMA_PhoneFindNtwkNameByPlmnId():tmpPlmnId.Mcc =",(VOS_INT32)tmpPlmnId.Mcc);
    MMA_INFOLOG1("MMA_PhoneFindNtwkNameByPlmnId():tmpPlmnId.Mnc =",(VOS_INT32)tmpPlmnId.Mnc);

    usTotalNtwkNum      = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl   = TAF_MMA_GetNetworkNameTblAddr();


    /* �����ǰNV���ò���ʾ���ص�ȫ���������б���Ϣ,��ֱ�ӷ��� */
    if ( VOS_TRUE == TAF_MMA_GetNotDisplayLocalNetworkNameFlg() )
    {
        pstOperName->aucOperatorNameLong[0]  = '\0';
        pstOperName->aucOperatorNameShort[0] = '\0';

        return MMA_FAILURE;
    }

    while(( VOS_TRUE == bContinueSearch )&&(i < usTotalNtwkNum))
    {
        if(tmpPlmnId.Mcc == pstNetworkNameTbl->PlmnId.Mcc)
        {
            if(tmpPlmnId.Mnc == pstNetworkNameTbl->PlmnId.Mnc)
            {
                bFound = VOS_TRUE;
                bContinueSearch = VOS_FALSE;

                (VOS_VOID)VOS_StrNCpy(pstOperName->aucOperatorNameLong,
                        pstNetworkNameTbl->pStrOperatorNameLong,TAF_PH_OPER_NAME_LONG);
                (VOS_VOID)VOS_StrNCpy(pstOperName->aucOperatorNameShort,
                        pstNetworkNameTbl->pStrOperatorNameShort,TAF_PH_OPER_NAME_SHORT);
            }
            else if (tmpPlmnId.Mnc < pstNetworkNameTbl->PlmnId.Mnc)
            {
                bContinueSearch = VOS_FALSE;
            }
            else
            {
            }
        }
        else if(tmpPlmnId.Mcc < pstNetworkNameTbl->PlmnId.Mcc)
        {
            bContinueSearch = VOS_FALSE;
        }
        else
        {
        }

        pstNetworkNameTbl ++;

        ++ i;

    }

    if(VOS_FALSE == bFound)
    {
        pstOperName->aucOperatorNameLong[0]  = '\0';
        pstOperName->aucOperatorNameShort[0] = '\0';
        return MMA_FAILURE;
    }

    return MMA_SUCCESS;
}

/* ��ȡ��������NVδʹ�ã���Ӧ�ĺ���ɾ�� */

VOS_BOOL NAS_MMA_PlmnInCurUserSrchList(TAF_PLMN_ID_STRU *pstPlmnId)
{
    VOS_UINT32                          i;
    TAF_PLMN_ID_STRU                    stPlmnId;

    for (i = 0; i < g_StatusContext.PlmnList.ucPlmnNum; i++)
    {
        stPlmnId = g_StatusContext.PlmnList.Plmn[i];
        MMA_PlmnId2Bcd(&stPlmnId);

        stPlmnId.Mcc &= 0x0fff;
        stPlmnId.Mnc &= 0x0fff;

        if (0x0F == ((0x0f00 & stPlmnId.Mnc) >> 8))
        {
            stPlmnId.Mnc &= 0x00ff;
        }

        if ((stPlmnId.Mcc == pstPlmnId->Mcc)
         && (stPlmnId.Mnc == pstPlmnId->Mnc))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 MMA_PhoneGetOperInfoByLongNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOperName)
{
    VOS_UINT16                          usTotalNtwkNum;
    VOS_UINT16                          i;
    VOS_BOOL                            bFlag;
    TAF_PH_OPERATOR_NAME_STRU           stDestPhOperName;
    TAF_PH_OPERATOR_NAME_TBL_STRU      *pstNetworkNameTbl = VOS_NULL_PTR;

    bFlag = VOS_FALSE;
    usTotalNtwkNum      = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl   = TAF_MMA_GetNetworkNameTblAddr();

    PS_MEM_SET(&stDestPhOperName, 0, sizeof(stDestPhOperName));


    /* �����ǰNV���ò���ʾ���ص�ȫ���������б���Ϣ,��ֱ�ӷ��� */
    if ( VOS_TRUE == TAF_MMA_GetNotDisplayLocalNetworkNameFlg() )
    {
        pstOperName->aucOperatorNameShort[0]    = '\0';
        pstOperName->PlmnId.Mcc                 = 0;
        pstOperName->PlmnId.Mnc                 = 0;

        return MMA_FAILURE;
    }

    for (i = 0; i < usTotalNtwkNum; i++ )
    {
        if ( VOS_FALSE == VOS_StrNiCmp( (VOS_CHAR *)(pstOperName->aucOperatorNameLong),
                          (VOS_CHAR *)(pstNetworkNameTbl->pStrOperatorNameLong),
                          TAF_PH_OPER_NAME_LONG) )
        {
            /* the current long operator name is equal to the specified one
             * copy PLMN ID & short operator name into output parameter and return back
             */
            pstOperName->PlmnId.Mcc = pstNetworkNameTbl->PlmnId.Mcc;
            pstOperName->PlmnId.Mnc = pstNetworkNameTbl->PlmnId.Mnc;

            (VOS_VOID)VOS_StrNCpy(pstOperName->aucOperatorNameShort,
                    pstNetworkNameTbl->pStrOperatorNameShort,TAF_PH_OPER_NAME_SHORT);
            MMA_NORMAILLOG("the specified PLMN found in gastNetworkNameTbl!");


            if (VOS_FALSE == bFlag)
            {
                stDestPhOperName = *pstOperName;
                bFlag            = VOS_TRUE;
            }

            if (VOS_TRUE == NAS_MMA_PlmnInCurUserSrchList(&pstOperName->PlmnId))
            {
                stDestPhOperName = *pstOperName;
                break;
            }

        }

        pstNetworkNameTbl ++;
    }

    if (VOS_FALSE != bFlag)
    {
        (VOS_VOID)VOS_StrNCpy(pstOperName->aucOperatorNameShort,
                stDestPhOperName.aucOperatorNameShort,TAF_PH_OPER_NAME_SHORT);
        pstOperName->PlmnId = stDestPhOperName.PlmnId;

        if ( pstOperName->PlmnId.Mnc < 0x100)
        {
            pstOperName->PlmnId.Mnc <<= 4;
            pstOperName->PlmnId.Mnc |= 0xF;
        }

        return MMA_SUCCESS;
    }
    else
    {
        MMA_NORMAILLOG("the specified PLMN not found in gastNetworkNameTbl!");
        pstOperName->aucOperatorNameShort[0]    = '\0';
        pstOperName->PlmnId.Mcc                 = 0;
        pstOperName->PlmnId.Mnc                 = 0;
        return MMA_FAILURE;
    }

}
VOS_UINT32 MMA_PhoneGetOperInfoByShortNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOperName)
{
    VOS_UINT16                          usTotalNtwkNum;
    VOS_UINT16                          i ;
    VOS_BOOL                            bFlag;
    TAF_PH_OPERATOR_NAME_STRU           stDestPhOperName;
    TAF_PH_OPERATOR_NAME_TBL_STRU      *pstNetworkNameTbl = VOS_NULL_PTR;

    bFlag = VOS_FALSE;

    usTotalNtwkNum      = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl   = TAF_MMA_GetNetworkNameTblAddr();

    PS_MEM_SET(&stDestPhOperName, 0, sizeof(stDestPhOperName));



    /* �����ǰNV���ò���ʾ���ص�ȫ���������б���Ϣ,��ֱ�ӷ��� */
    if ( VOS_TRUE == TAF_MMA_GetNotDisplayLocalNetworkNameFlg() )
    {
        pstOperName->aucOperatorNameLong[0]    = '\0';
        pstOperName->PlmnId.Mcc                 = 0;
        pstOperName->PlmnId.Mnc                 = 0;

        return MMA_FAILURE;
    }

    for (i = 0; i < usTotalNtwkNum; i++ )
    {
        if ( VOS_FALSE == VOS_StrNiCmp( (VOS_CHAR *)(pstOperName->aucOperatorNameShort),
                          (VOS_CHAR *)(pstNetworkNameTbl->pStrOperatorNameShort),
                          TAF_PH_OPER_NAME_SHORT) )
        {
            /* the current long operator name is equal to the specified one
             * copy PLMN ID & short operator name into output parameter and return back
             */
            pstOperName->PlmnId.Mcc = pstNetworkNameTbl->PlmnId.Mcc;
            pstOperName->PlmnId.Mnc = pstNetworkNameTbl->PlmnId.Mnc;

            (VOS_VOID)VOS_StrNCpy(pstOperName->aucOperatorNameLong,
                    pstNetworkNameTbl->pStrOperatorNameLong,TAF_PH_OPER_NAME_LONG);
            MMA_NORMAILLOG("the specified PLMN found in gastNetworkNameTbl!");


            if (VOS_FALSE == bFlag)
            {
                stDestPhOperName = *pstOperName;
                bFlag            = VOS_TRUE;
            }

            if (VOS_TRUE == NAS_MMA_PlmnInCurUserSrchList(&pstOperName->PlmnId))
            {
                stDestPhOperName = *pstOperName;
                break;
            }
        }

        pstNetworkNameTbl ++;

    }

    if (VOS_FALSE != bFlag)
    {

        (VOS_VOID)VOS_StrNCpy(pstOperName->aucOperatorNameLong,
                stDestPhOperName.aucOperatorNameLong,TAF_PH_OPER_NAME_LONG);

        pstOperName->PlmnId              = stDestPhOperName.PlmnId;

        if ( pstOperName->PlmnId.Mnc < 0x100)
        {
            pstOperName->PlmnId.Mnc <<= 4;
            pstOperName->PlmnId.Mnc |= 0xF;
        }

        return MMA_SUCCESS;
    }
    else
    {
        MMA_NORMAILLOG("the specified PLMN not found in gastNetworkNameTbl!");
        pstOperName->aucOperatorNameLong[0]    = '\0';
        pstOperName->PlmnId.Mcc                 = 0;
        pstOperName->PlmnId.Mnc                 = 0;
        return MMA_FAILURE;
    }
}
VOS_UINT32 MMA_PhoneGetAllOperNumByLongNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOperName,
                                                                                 VOS_UINT8 *pucMaxMncLen)
{
    VOS_UINT16                          usTotalNtwkNum;
    VOS_UINT32                          ulTotalOperNum = 0;
    VOS_UINT16                          i = 0;
    VOS_UINT8                           ucCurMncLen;
    TAF_PH_OPERATOR_NAME_TBL_STRU      *pstNetworkNameTbl = VOS_NULL_PTR;

    usTotalNtwkNum      = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl   = TAF_MMA_GetNetworkNameTblAddr();

    *pucMaxMncLen = 0;


    /* �����ǰNV���ò���ʾ���ص�ȫ���������б���Ϣ,��ֱ�ӷ��� */
    if ( VOS_TRUE == TAF_MMA_GetNotDisplayLocalNetworkNameFlg() )
    {
        return ulTotalOperNum;
    }

    for (i = 0; i < usTotalNtwkNum; i++ )
    {
        if ( VOS_FALSE == VOS_StrNiCmp( (VOS_CHAR *)(pstOperName->aucOperatorNameLong),
                          (VOS_CHAR *)(pstNetworkNameTbl->pStrOperatorNameLong),
                          TAF_PH_OPER_NAME_LONG) )
        {
            /* �ۼ�OPER���� */
            ulTotalOperNum++;

            /* the current long operator name is equal to the specified one
             * copy PLMN ID & short operator name into output parameter and return back
             */
            if ( pstNetworkNameTbl->PlmnId.Mnc < 0x100)
            {
                ucCurMncLen = 5;
            }
            else
            {
                ucCurMncLen = 6;
            }

            if (*pucMaxMncLen < ucCurMncLen)
            {
                *pucMaxMncLen = ucCurMncLen;
            }

        }

        pstNetworkNameTbl ++;
    }

    return ulTotalOperNum;

}
VOS_UINT32 MMA_PhoneGetAllOperNumByShortNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOperName,
                                                                                 VOS_UINT8 *pucMaxMncLen)
{
    VOS_UINT16                          usTotalNtwkNum;
    VOS_UINT32                          ulTotalOperNum = 0;
    VOS_UINT16                          i = 0;
    VOS_UINT8                           ucCurMncLen;
    TAF_PH_OPERATOR_NAME_TBL_STRU      *pstNetworkNameTbl = VOS_NULL_PTR;

    usTotalNtwkNum      = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl   = TAF_MMA_GetNetworkNameTblAddr();

    *pucMaxMncLen = 0;


    /* �����ǰNV���ò���ʾ���ص�ȫ���������б���Ϣ,��ֱ�ӷ��� */
    if ( VOS_TRUE == TAF_MMA_GetNotDisplayLocalNetworkNameFlg() )
    {
        return ulTotalOperNum;
    }

    for (i = 0; i < usTotalNtwkNum; i++ )
    {
        if ( VOS_FALSE == VOS_StrNiCmp( (VOS_CHAR *)(pstOperName->aucOperatorNameShort),
                          (VOS_CHAR *)(pstNetworkNameTbl->pStrOperatorNameShort),
                          TAF_PH_OPER_NAME_SHORT) )
        {
            /* �ۼ�OPER���� */
            ulTotalOperNum++;

            /* the current long operator name is equal to the specified one
             * copy PLMN ID & short operator name into output parameter and return back
             */
            if ( pstNetworkNameTbl->PlmnId.Mnc < 0x100)
            {
                ucCurMncLen = 5;
            }
            else
            {
                ucCurMncLen = 6;
            }

            if (*pucMaxMncLen < ucCurMncLen)
            {
                *pucMaxMncLen = ucCurMncLen;
            }

        }

        pstNetworkNameTbl ++;
    }

    return ulTotalOperNum;

}
VOS_VOID MMA_PhoneGetAllOperInfoByLongNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOrigOperName,
                                                                                TAF_PH_OPERATOR_NAME_STRU   *pstOperName)
{
    VOS_UINT16                          usTotalNtwkNum;
    VOS_UINT16                          i = 0;
    TAF_PH_OPERATOR_NAME_STRU          *pstOperResult = pstOperName;
    TAF_PH_OPERATOR_NAME_TBL_STRU      *pstNetworkNameTbl = VOS_NULL_PTR;

    usTotalNtwkNum      = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl   = TAF_MMA_GetNetworkNameTblAddr();


    /* �����ǰNV���ò���ʾ���ص�ȫ���������б���Ϣ,��ֱ�ӷ��� */
    if ( VOS_TRUE == TAF_MMA_GetNotDisplayLocalNetworkNameFlg() )
    {
        return;
    }

    for (i = 0; i < usTotalNtwkNum; i++ )
    {
        if ( VOS_FALSE == VOS_StrNiCmp( (VOS_CHAR *)(pstOrigOperName->aucOperatorNameLong),
                          (VOS_CHAR *)(pstNetworkNameTbl->pStrOperatorNameLong),
                          TAF_PH_OPER_NAME_LONG) )
        {
            /* the current long operator name is equal to the specified one
             * copy PLMN ID & short operator name into output parameter and return back
             */
            pstOperResult->PlmnId.Mcc = pstNetworkNameTbl->PlmnId.Mcc;
            pstOperResult->PlmnId.Mnc = pstNetworkNameTbl->PlmnId.Mnc;

            (VOS_VOID)VOS_StrNCpy(pstOperResult->aucOperatorNameShort,
                        pstNetworkNameTbl->pStrOperatorNameShort,
                        TAF_PH_OPER_NAME_SHORT);

            (VOS_VOID)VOS_StrNCpy(pstOperResult->aucOperatorNameLong,
                        pstNetworkNameTbl->pStrOperatorNameLong,
                        TAF_PH_OPER_NAME_LONG);

            pstOperResult++;
        }

        pstNetworkNameTbl ++;
    }

    return;
}
VOS_VOID MMA_PhoneGetAllOperInfoByShortNameFromOperTbl( TAF_PH_OPERATOR_NAME_STRU   *pstOrigOperName,
                                                                                TAF_PH_OPERATOR_NAME_STRU   *pstOperName)
{
    VOS_UINT16                          usTotalNtwkNum;
    VOS_UINT16                          i = 0;
    TAF_PH_OPERATOR_NAME_STRU          *pstOperResult = pstOperName;
    TAF_PH_OPERATOR_NAME_TBL_STRU      *pstNetworkNameTbl = VOS_NULL_PTR;

    usTotalNtwkNum      = TAF_MMA_GetNetWorkNameTblSize();
    pstNetworkNameTbl   = TAF_MMA_GetNetworkNameTblAddr();


    /* �����ǰNV���ò���ʾ���ص�ȫ���������б���Ϣ,��ֱ�ӷ��� */
    if ( VOS_TRUE == TAF_MMA_GetNotDisplayLocalNetworkNameFlg() )
    {
        return;
    }

    for (i = 0; i < usTotalNtwkNum; i++ )
    {
        if ( VOS_FALSE == VOS_StrNiCmp( (VOS_CHAR *)(pstOrigOperName->aucOperatorNameShort),
                          (VOS_CHAR *)(pstNetworkNameTbl->pStrOperatorNameShort),
                          TAF_PH_OPER_NAME_SHORT) )
        {
            /* the current short operator name is equal to the specified one
             * copy PLMN ID & long operator name into output parameter and return back
             */
            pstOperResult->PlmnId.Mcc = pstNetworkNameTbl->PlmnId.Mcc;
            pstOperResult->PlmnId.Mnc = pstNetworkNameTbl->PlmnId.Mnc;

            (VOS_VOID)VOS_StrNCpy(pstOperResult->aucOperatorNameShort,
                        pstNetworkNameTbl->pStrOperatorNameShort,
                        TAF_PH_OPER_NAME_SHORT);

            (VOS_VOID)VOS_StrNCpy(pstOperResult->aucOperatorNameLong,
                        pstNetworkNameTbl->pStrOperatorNameLong,
                        TAF_PH_OPER_NAME_LONG);

            pstOperResult++;
        }

        pstNetworkNameTbl ++;

    }

    return;
}




VOS_VOID MMA_InitAtMsgReq( VOS_UINT16   ClientId,
                             VOS_UINT8          OpId,
                             TAF_START_INFO_IND_STRU   stAtMsgReq)
{
    VOS_UINT32                   ulRet = MMA_ERROR;
    TAF_PHONE_EVENT_INFO_STRU   *pstPhoneEvent;
    VOS_UINT32                   ulRptCmdStatus;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    /* ����CERSSI��Ӧ��SDCȫ�ֱ��� */
    if (0 == stAtMsgReq.ucSignThreshold)
    {
        ulRptCmdStatus = VOS_FALSE;
    }
    else
    {
        ulRptCmdStatus = VOS_TRUE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CERSSI, ulRptCmdStatus);

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_InitAtMsgReq:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    if ( (stAtMsgReq.ucActionType > TAF_START_EVENT_INFO_STOP)
       ||(stAtMsgReq.ucRrcMsgType > ( TAF_EVENT_INFO_CELL_BLER
                                     |TAF_EVENT_INFO_CELL_ID
                                     |TAF_EVENT_INFO_CELL_SIGN
                                    )
         )
       )
    {
        MMA_HandleEventError(ClientId, OpId, TAF_ERR_PARA_ERROR, TAF_PH_EVT_SETUP_SYSTEM_INFO_RSP);
        MMA_WARNINGLOG("MMA_InitAtMsgReq():WARNING:Error Para");
        PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);
        return;
    }
    else
    {
        ulRet = TAF_MMA_SndMsccSignalReportReq(stAtMsgReq.ucActionType, stAtMsgReq.ucRrcMsgType,
                          stAtMsgReq.ucSignThreshold, stAtMsgReq.ucMinRptTimerInterval);

    }

    /*�ϱ����ý��*/
    if ( MMA_SUCCESS == ulRet)
    {
        pstPhoneEvent->ClientId              = ClientId;
        pstPhoneEvent->OpId                  = OpId;
        pstPhoneEvent->OP_PhoneError         = TAF_PARA_OK;
        pstPhoneEvent->PhoneEvent            = TAF_PH_EVT_SETUP_SYSTEM_INFO_RSP;
        Taf_InitEventInfoOP(pstPhoneEvent);

        /* ���õ绰�����ϱ����� */
        MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));
    }
    else
    {
        MMA_HandleEventError(ClientId, OpId, TAF_ERR_UNSPECIFIED_ERROR, TAF_PH_EVT_SETUP_SYSTEM_INFO_RSP);
    }
    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);


    return;
}

/*****************************************************************************
 �� �� ��  : MMA_CleanTiVar
 ��������  : ���gastMmaTiTabȫ�ֱ�����Ӧ��ֵ��Ĭ��ֵΪ0���ú���û�з���ֵ��
             �����ɹ�����Ч���ɵ����߱�֤
 �������  : VOS_UINT16            ClientId
             VOS_UINT8                   OpId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��12��8��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���

  2.��    ��   : 2006��3��8��
    ��    ��   : liuyang id:48197
    �޸�����   : ���ⵥ�ţ�A32D02371��ʹ�ú��滻ԭ�е�����
*****************************************************************************/
VOS_VOID MMA_CleanTiVar(VOS_UINT16            ClientId,
                        VOS_UINT8                   OpId     )
{
    VOS_UINT32 ulI = 0;

    for ( ulI = 0; ulI < MMA_MAX_TI ; ulI++ )
    {
        if ( (TAF_USED == gastMmaTiTab[ulI].ucUsed  )
           &&(ClientId == gastMmaTiTab[ulI].ClientId)
           &&(OpId     == gastMmaTiTab[ulI].Id      )
           )
        {
            /*�����ǰʹ�ñ�־*/
            gastMmaTiTab[ulI].ucUsed    = MMA_TI_UNUSED;
            gastMmaTiTab[ulI].ClientId  = MMA_CLIENTID_NONE;
            gastMmaTiTab[ulI].Id        = MMA_OP_ID_INTERNAL;
            break;
        }
    }
    return;
}


/*****************************************************************************
 �� �� ��  : MMA_BcdNumToAsciiNum
 ��������  : BCD��תλASCII�룬��������SSA
 �������  : VOS_UINT8 *pucAsciiNum
             VOS_UINT8 *pucBcdNum
             VOS_UINT8 ucBcdNumLen
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��12��9��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MMA_BcdNumToAsciiNum(VOS_UINT8 *pucAsciiNum, VOS_UINT8 *pucBcdNum, VOS_UINT8 ucBcdNumLen)
{
    VOS_UINT8       ucTmp;
    VOS_UINT8       ucFirstNumber;
    VOS_UINT8       ucSecondNumber;

    for (ucTmp = 0; ucTmp < ucBcdNumLen; ucTmp++)
    {
        ucFirstNumber = (VOS_UINT8)((*(pucBcdNum + ucTmp)) & 0x0f);             /*low four bits*/
        ucSecondNumber = (VOS_UINT8)(((*(pucBcdNum + ucTmp)) >> 4) & 0x0f);   /*high four bits*/
        if(ucFirstNumber <= 9)
        {
            *pucAsciiNum = ucFirstNumber + 0x30;
            pucAsciiNum++;
        }
        else if(0xa == ucFirstNumber)            /* the key is '*' */
        {
            *pucAsciiNum = 0x2a;
            pucAsciiNum++;
        }
        else if(0xb == ucFirstNumber)            /* the key is '#' */
        {
            *pucAsciiNum = 0x23;
            pucAsciiNum++;
        }
        else                                     /* the key is 'a','b'or 'c' */
        {
            *pucAsciiNum = ucFirstNumber + 0x57;
            pucAsciiNum++;
        }

        /* the following proceed the second number */
        if(0xf == ucSecondNumber)
        {
            break;
        }
        if(ucSecondNumber <= 9)
        {
            *pucAsciiNum = ucSecondNumber + 0x30;
            pucAsciiNum++;
        }
        else if(0xa == ucSecondNumber)            /* the key is '*' */
        {
            *pucAsciiNum = 0x2a;
            pucAsciiNum++;
        }
        else if(0xb == ucSecondNumber)            /* the key is '#' */
        {
            *pucAsciiNum = 0x23;
            pucAsciiNum++;
        }
        else                                     /* the key is 'a','b'or 'c' */
        {
            *pucAsciiNum = ucSecondNumber + 0x57;
            pucAsciiNum++;
        }
    }
    *pucAsciiNum = '\0';
    return;
}
VOS_VOID MMA_ImsiBcd2Ascii(VOS_UINT8 ucLen, VOS_UINT8 *pucNum, VOS_UINT8 *pucAsciiStr)
{
    VOS_UINT32 ulI = 0;
    VOS_UINT8   ucTmp;
    /*��Ч���ж�*/
    if ( (VOS_NULL_PTR == pucNum)
       ||(VOS_NULL_PTR == pucAsciiStr)
       ||(           0 == ucLen )
       )
    {
        MMA_WARNINGLOG("MMA_ImsiBcd2Ascii():WARNING:NULL PTR");
        return;
    }

    /*�����ƶ��û�ʶ����*/
    /*��մ���ַ����Ļ�����*/
    for ( ulI = 0; ulI < (VOS_UINT32)ucLen; ulI++ )
    {
        pucAsciiStr[ulI] = 0;
    }
    ucTmp = (*pucNum >> 4) & 0x0f;
    /*ȡ����һλ*/
    MMA_BcdNumToAsciiNum(pucAsciiStr, &ucTmp, 1);
    /*����Bcd��Ascii��ת��*/
    MMA_BcdNumToAsciiNum(pucAsciiStr + 1, pucNum + 1, (ucLen - 1)/2);
    return;
}

/*****************************************************************************
 �� �� ��  : MMA_ImeiBcd2Ascii
 ��������  : ת��IMEI����Ϊ�ַ�����ʽ
 �������  : VOS_UINT8 ucLen   --BCD�볤��
             VOS_UINT8 *pucNum --BCD���ŵ�λ��
             VOS_UINT8 *pucAsciiStr  --�ַ���д��λ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��12��9��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MMA_ImeiBcd2Ascii(VOS_UINT8 ucLen, VOS_UINT8 *pucNum, VOS_UINT8 *pucAsciiStr)
{
    VOS_UINT32 ulI = 0;
    if ( (VOS_NULL_PTR == pucNum)
       ||(VOS_NULL_PTR == pucAsciiStr)
       ||(           0 == ucLen )
       )
    {
        MMA_WARNINGLOG("MMA_ImsiBcd2Ascii():WARNING:NULL PTR");
        return;
    }
    /*�����ƶ��豸ʶ����*/
    for ( ulI = 0; ulI < ucLen ; ulI++ )
    {
        *(pucAsciiStr + ulI) = *(pucNum + ulI) + 0x30;
    }
    pucAsciiStr[ulI] = '\0';
    return;
}
VOS_UINT32 MMA_ImeiAsciiToBcd(VOS_UINT8 *pucAsciiNum, VOS_UINT8 ucAsciiNumLen, VOS_UINT8 *pucBcdNum)
{
    VOS_UINT32 ulI = 0;
    if ( (VOS_NULL_PTR == pucAsciiNum)
       ||(VOS_NULL_PTR == pucBcdNum)
       ||(           0 == ucAsciiNumLen )
       )
    {
        MMA_WARNINGLOG("MMA_ImeiAsciiToBcd():WARNING:NULL PTR");
        return MMA_FAILURE;
    }
    /*�����ƶ��豸ʶ����*/
    for ( ulI = 0; ulI < ucAsciiNumLen ; ulI++ )
    {
        *(pucBcdNum + ulI) = *(pucAsciiNum + ulI) - 0x30;
    }

    return MMA_SUCCESS;
}
VOS_VOID Taf_GetCurrentAttachStatus(
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8    *penCsResult,
    TAF_MMA_ATTACH_STATUS_ENUM_UINT8    *penPsResult
)
{
    /* Deleted by h00313353 for Iteration 13, 2015-4-17 */

    /*ֻ�е���ǰ����״̬Ϊ������������Ʒ���״̬�ű���Ϊ�ɹ����ţ�����״̬��
      Ϊδ����*/
    /* Modified by h00313353 for Iteration 13, 2015-4-17, begin */
    if  ( TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == TAF_SDC_GetCsServiceStatus())
    {
        *penCsResult = TAF_MMA_ATTACH_STATUS_ATTACHED;
    }
    else
    {
        *penCsResult = TAF_MMA_ATTACH_STATUS_DETACHED;
    }
    if  (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == TAF_SDC_GetPsServiceStatus())
    {
        *penPsResult = TAF_MMA_ATTACH_STATUS_ATTACHED;
    }
    else
    {
        *penPsResult = TAF_MMA_ATTACH_STATUS_DETACHED;
    }
    /* Modified by h00313353 for Iteration 13, 2015-4-17, end */

}



/*****************************************************************************
 �� �� ��  : MMA_PlmnId2Bcd
 ��������  : ��ԭPLMNidת��ΪBCD��ʽ��¼
             ����:MCCΪ460,MNCΪ01ʱ,
             pstPlmnId->Mcc = 0x000604      pstPlmnId->Mcc = 0x00000460
                                        ---->
             pstPlmnId->Mnc = 0x000100      pstPlmnId->Mnc = 0x00000001
 �������  : TAF_PLMN_ID_STRU *pstPlmnId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��12��20��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���

  2.��    ��   : 2006��2��23��
    ��    ��   : liuyang id:48197
    �޸�����   : ������Wcdma�Ľӿ��޸Ĵ����PLMN˳��,���ⵥ��:A32D02119
*****************************************************************************/
VOS_VOID MMA_PlmnId2Bcd(TAF_PLMN_ID_STRU *pstPlmnId)
{
    VOS_UINT8   ucI;
    VOS_UINT32  ulTmp;
    VOS_UINT8   aucTmp[4];

    ulTmp           = pstPlmnId->Mcc;
    pstPlmnId->Mcc  = 0;
    for ( ucI = 0 ; ucI < 3 ; ucI++ )
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  8;
    }
    pstPlmnId->Mcc = ((VOS_UINT32)aucTmp[0] << 8)
                    |((VOS_UINT32)aucTmp[1] << 4)
                    | aucTmp[2];

    ulTmp           = pstPlmnId->Mnc;
    pstPlmnId->Mnc  = 0;
    for ( ucI = 0 ; ucI < 3 ; ucI++ )
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  8;
    }

    /* BEGIN: Modified by liuyang id:48197, 2006/2/23   PN:A32D02119*/
    /*pstPlmnId->Mnc = ((VOS_UINT32)aucTmp[0] << 8)
                    |((VOS_UINT32)aucTmp[1] << 4)
                    | aucTmp[2];*/
    if(0xf == aucTmp[2])
    {
        pstPlmnId->Mnc = ((VOS_UINT32)aucTmp[0] << 4)
                        |((VOS_UINT32)aucTmp[1] )
                        |0xf00;
    }
    else
    {
        pstPlmnId->Mnc = ((VOS_UINT32)aucTmp[0] << 8)
                    |((VOS_UINT32)aucTmp[1] << 4)
                    | aucTmp[2];
    }
    /* END:   Modified by liuyang id:48197, 2006/2/23 */
    return;
}


/*****************************************************************************
 �� �� ��  : MMA_PlmnId2NasStyle
 ��������  : ��ԭPLMNidת��ΪNAS�ڲ�ʹ�ø�ʽ��¼
             ����:MCCΪ460,MNCΪ01ʱ,
             pstPlmnId->Mcc = 0x000604      pstPlmnId->Mcc = 0x00000460
                                        <----
             pstPlmnId->Mnc = 0x000100      pstPlmnId->Mnc = 0x00000001
 �������  : TAF_PLMN_ID_STRU *pstPlmnId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��12��20��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���

  2.��    ��   : 2006��2��23��
    ��    ��   : liuyang id:48197
    �޸�����   : ������Wcdma�Ľӿ��޸Ĵ����PLMN˳��,���ⵥ��:A32D02119

*****************************************************************************/
VOS_VOID MMA_PlmnId2NasStyle(TAF_PLMN_ID_STRU *pstPlmnId)
{
    VOS_UINT8   ucI;
    VOS_UINT8   aucTmp[4];
    VOS_UINT32  ulTmp;

    ulTmp           = pstPlmnId->Mcc;
    pstPlmnId->Mcc  = 0;
    for ( ucI = 0 ; ucI < 3 ; ucI++ )
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  4;
    }
    pstPlmnId->Mcc  =  aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);

    ulTmp           = pstPlmnId->Mnc;
    pstPlmnId->Mnc  = 0;
    for ( ucI = 0 ; ucI < 3 ; ucI++ )
    {
        aucTmp[ucI]     = ulTmp & 0x0f;
        ulTmp         >>=  4;
    }
    /* BEGIN: Modified by liuyang id:48197, 2006/2/23   PN:A32D02119*/
    /*pstPlmnId->Mnc =   aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);*/
    if(0xf == aucTmp[2])
    {
        pstPlmnId->Mnc =  aucTmp[1]
                         |((VOS_UINT32)aucTmp[0] << 8)
                         |0x0f0000;
    }
    else
    {
        pstPlmnId->Mnc =   aucTmp[2]
                     |((VOS_UINT32)aucTmp[1] << 8)
                     |((VOS_UINT32)aucTmp[0] << 16);
    }
    /* END:   Modified by liuyang id:48197, 2006/2/23 */
    return;
}


/* Modified by h00313353 for iteration 9, 2015-2-7, begin */
VOS_UINT32 TAF_MMA_IsUsimCardStatusChanged(
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardStatus
)
/* Modified by h00313353 for iteration 9, 2015-2-7, end */
{
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus;

    VOS_UINT32                          ulChangeFlg;

    /* Modified by h00313353 for iteration 9, 2015-2-7, begin */
    enSimStatus     = TAF_SDC_GetUsimStatus();
    /* Modified by h00313353 for iteration 9, 2015-2-7, end */

    /* Ĭ��USIM״̬û�иı� */
    ulChangeFlg = VOS_FALSE;

    switch ( enCardStatus )
    {
        case USIMM_CARD_SERVIC_ABSENT :
        case USIMM_CARD_SERVIC_UNAVAILABLE :
            ulChangeFlg = TAF_MMA_IsUsimStatusChange_UsimmCardServiceAbsent(enSimStatus);
            break;

        case USIMM_CARD_SERVIC_AVAILABLE :
            ulChangeFlg = TAF_MMA_IsUsimStatusChange_UsimmCardServiceAvailable(enSimStatus);
            break;

        case USIMM_CARD_SERVIC_SIM_PIN :
        case USIMM_CARD_SERVIC_SIM_PUK :
        case USIMM_CARD_SERVIC_NET_LCOK :
        /* Modified by h00313353 for iteration 9, 2015-2-7, begin */
        case USIMM_CARD_SERVICE_IMSI_LOCK :
        /* Modified by h00313353 for iteration 9, 2015-2-7, end */
            ulChangeFlg = TAF_MMA_IsUsimStatusChange_UsimmCardServiceSimPin(enSimStatus);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMA, "MMA_IsUsimStatusChange:WARNING INVALID SIM STATUS!");
            break;
    }

    return ulChangeFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsCsimCardStatusChanged
 ��������  : �ж�Csim��״̬�Ƿ����ı�
 �������  : VOS_UINT32 ulCardStatus: ���µĿ�״̬
 �������  : ��
 �� �� ֵ  : TRUE -- ״̬�����ı�
             FALSE-- ״̬δ�����ı�
 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsCsimCardStatusChanged(
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardStatus
)
/* Modified by h00313353 for iteration 9, 2015-2-7, end */
{
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus;

    VOS_UINT32                          ulChangeFlg;

    /* Modified by h00313353 for iteration 9, 2015-2-7, begin */
    enSimStatus     = TAF_SDC_GetCsimStatus();
    /* Modified by h00313353 for iteration 9, 2015-2-7, end */

    /* Ĭ��USIM״̬û�иı� */
    ulChangeFlg = VOS_FALSE;

    switch ( enCardStatus )
    {
        case USIMM_CARD_SERVIC_ABSENT :
        case USIMM_CARD_SERVIC_UNAVAILABLE :
            ulChangeFlg = TAF_MMA_IsUsimStatusChange_UsimmCardServiceAbsent(enSimStatus);
            break;

        case USIMM_CARD_SERVIC_AVAILABLE :
            ulChangeFlg = TAF_MMA_IsUsimStatusChange_UsimmCardServiceAvailable(enSimStatus);
            break;

        case USIMM_CARD_SERVIC_SIM_PIN :
        case USIMM_CARD_SERVIC_SIM_PUK :
        case USIMM_CARD_SERVIC_NET_LCOK :
        /* Modified by h00313353 for iteration 9, 2015-2-7, begin */
        case USIMM_CARD_SERVICE_IMSI_LOCK :
        /* Modified by h00313353 for iteration 9, 2015-2-7, end */
            ulChangeFlg = TAF_MMA_IsUsimStatusChange_UsimmCardServiceSimPin(enSimStatus);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMA, "MMA_IsUsimStatusChange:WARNING INVALID SIM STATUS!");
            break;
    }

    return ulChangeFlg;
}

/* Added by h00313353 for iteration 9, 2015-2-7, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_IsCardStatusChanged
 ��������  : �жϿ�״̬�Ƿ����ı�
 �������  : USIMM_CARDSTATUS_IND_STRU          *pstUsimMsg: ��״̬��Ϣ
 �������  : ��
 �� �� ֵ  : TRUE -- �����ı�
             FALSE-- δ�����ı�
 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsCardStatusChanged(
    USIMM_CARDSTATUS_IND_STRU          *pstUsimMsg
)
{
    VOS_UINT32                          ulIsUsimStatusChanged;
    VOS_UINT32                          ulIsCsimStatusChanged;

    ulIsUsimStatusChanged = TAF_MMA_IsUsimCardStatusChanged(pstUsimMsg->stUsimSimInfo.enCardService);
    ulIsCsimStatusChanged = TAF_MMA_IsCsimCardStatusChanged(pstUsimMsg->stCsimUimInfo.enCardService);

    return (VOS_UINT32)(ulIsUsimStatusChanged || ulIsCsimStatusChanged);
}
/* Added by h00313353 for iteration 9, 2015-2-7, end */

VOS_UINT32 TAF_MMA_IsImsiChanged(
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_CARD_STATUS_STRU            *pstUsimMsg,
    VOS_UINT8                         *pstImsi
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
)
{
    VOS_UINT8                          *pucSdcImsi = VOS_NULL_PTR;
    /* Modified by h00313353 for iteration 9, 2015-2-7, begin */
    if (USIMM_CARD_SERVIC_AVAILABLE != pstUsimMsg->enCardService)
    /* Modified by h00313353 for iteration 9, 2015-2-7, end */
    {
        return VOS_FALSE;
    }

    pucSdcImsi = TAF_SDC_GetLastSimImsi();

    if (0 != VOS_MemCmp(pucSdcImsi, pstImsi, NAS_MAX_IMSI_LENGTH))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}




VOS_VOID MMA_ForwardOmMaintainInfoInd(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT32                          ulMsgName,
    VOS_UINT8                           ucOmConnectFlg,
    VOS_UINT8                           ucOmPcRecurEnableFlg
)
{
    MMCM_OM_MAINTAIN_INFO_IND_STRU     *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    /* ��Ϣ�����ڴ����� */
    pstSndMsg = (MMCM_OM_MAINTAIN_INFO_IND_STRU*)PS_ALLOC_MSG(
                                           WUEPS_PID_MMA,
                                           sizeof(MMCM_OM_MAINTAIN_INFO_IND_STRU)- VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_ERROR,
               "MMA_ForwardOmMaintainInfoInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    pstSndMsg->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid          = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid        = ulReceiverPid;
    pstSndMsg->ulLength             = sizeof(MMCM_OM_MAINTAIN_INFO_IND_STRU)- VOS_MSG_HEAD_LENGTH;

    pstSndMsg->ulMsgName            = ulMsgName;

    pstSndMsg->ucOmConnectFlg       = ucOmConnectFlg;
    pstSndMsg->ucOmPcRecurEnableFlg = ucOmPcRecurEnableFlg;
    pstSndMsg->aucRsv2[0]           = 0;
    pstSndMsg->aucRsv2[1]           = 0;


    /* ��Ϣ���� */
    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if( VOS_OK != ulRst)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "MMA_ForwardOmMaintainInfoInd:ERROR: Fail to send message!");
        return;
    }

    return;
}


VOS_VOID MMA_SndAtOmMaintainInfoInd(
    VOS_UINT8                           ucOmConnectFlg,
    VOS_UINT8                           ucOmPcRecurEnableFlg
)
{
    ATMMA_OM_MAINTAIN_INFO_IND_STRU    *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;


    /* ��Ϣ�����ڴ����� */
    pstSndMsg = (ATMMA_OM_MAINTAIN_INFO_IND_STRU*)PS_ALLOC_MSG(
                                           WUEPS_PID_MMA,
                                           sizeof(ATMMA_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if ( VOS_NULL_PTR == pstSndMsg )
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_ERROR,
               "MMA_SndAtOmMaintainInfoInd:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    pstSndMsg->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid          = WUEPS_PID_MMA;
    pstSndMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid        = WUEPS_PID_AT;
    pstSndMsg->ulLength             = sizeof(ATMMA_OM_MAINTAIN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstSndMsg->ulMsgName            = ID_TAF_MMA_OM_MAINTAIN_INFO_IND;

    pstSndMsg->ucOmConnectFlg       = ucOmConnectFlg;
    pstSndMsg->ucOmPcRecurEnableFlg = ucOmPcRecurEnableFlg;
    pstSndMsg->aucRsv2[0]           = 0;
    pstSndMsg->aucRsv2[1]           = 0;

    /* ��Ϣ���� */
    ulRst = PS_SEND_MSG(WUEPS_PID_MMA, pstSndMsg);
    if( VOS_OK != ulRst)
    {
        TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "MMA_SndAtOmMaintainInfoInd:ERROR: Fail to send message!");
        return;
    }

    return;
}



VOS_UINT32 MMA_PhoneGetUsimStatus( VOS_UINT8 *pucSimStatus )
{
    VOS_UINT8               ucUsimStatus;

    /*��ȡ��ǰUSIM״̬*/
    /*������USIMAPI��ֵ��Ϊ0,���ʾ�д���*/

    /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
    ucUsimStatus = USIMM_CARD_SERVIC_ABSENT;

    if( MMA_SUCCESS != MMA_GetUsimStatusFromUsim(&ucUsimStatus, VOS_NULL_PTR) )
    {
        MMA_WARNINGLOG("MMA_PhoneGetUsimStatus():WORNING:Invoke Taf_UsimmGetStatus fail.");
        *pucSimStatus = MMA_USIM_NOREADY;
        return MMA_ERROR;
    }

    /*��ȡ��ǰUSIM״̬*/
    if(USIMM_CARD_SERVIC_ABSENT == ucUsimStatus)
    /* Modified by h00313353 for iteration 9, 2015-2-9, end */
    {
        *pucSimStatus = MMA_USIM_ABSENT;

        MMA_NORMAILLOG("MMA_PhoneGetUsimStatus():USIM is not present!");
    }
    else
    {
        *pucSimStatus = MMA_USIM_PRESENT;

        if (USIMM_API_SUCCESS != NAS_USIMMAPI_GetCardIMSI(gstMmaValue.stUsimInfo.UsimStatus.aucImsi))
        {
            MMA_NORMAILLOG("MMA_PhoneGetUsimStatus():USIMM_GetCardIMSI failed!");
        }
        MMA_NORMAILLOG("MMA_PhoneGetUsimStatus():USIM is present!");

    }

    return MMA_SUCCESS;
}



/* BEGIN: Added by liuyang id:48197, 2006/2/28   PN:A32D01672*/

VOS_UINT32 MMA_CheckPin1SatusSimple(VOS_VOID)
{
    TAF_PH_PIN_CNF_STRU  stPinTmp;

    stPinTmp.PinType     = TAF_SIM_PIN;
    /*��ѯ�Ƿ���ҪPIN1��*/
    stPinTmp.OpPinResult =  (VOS_UINT8)NAS_USIMMAPI_GetPinStatus(&(stPinTmp.PinType),
                                                   &(stPinTmp.QueryResult.UsimmEnableFlg),
                                                   &(stPinTmp.QueryResult.UsimmNeedType),
                                                   &(stPinTmp.ucRemain));

    if( stPinTmp.OpPinResult != TAF_PH_OP_PIN_OK )
    {
        MMA_WARNINGLOG("MMA_CheckPin1SatusSimple():WARNING:QUERY PIN Status Fail!");
        return MMA_PIN1_STATUS_FAIL;
    }
    else
    {
        if ( USIMM_PIN_NEED == stPinTmp.QueryResult.UsimmNeedType )
        {
            MMA_NORMAILLOG("MMA_CheckPin1SatusSimple():NORMAL:USIM ENABLE,RETURN NEED!");
            return MMA_NEED_PIN1;
        }
        else if( USIMM_PUK_NEED == stPinTmp.QueryResult.UsimmNeedType )
        {
            MMA_NORMAILLOG("MMA_CheckPin1SatusSimple():NORMAL:USIM ENABLE,RETURN NEED!");
            return MMA_NEED_PUK1;
        }
        else if( USIMM_PUK_BLOCK == stPinTmp.QueryResult.UsimmNeedType )
        {
            MMA_NORMAILLOG("MMA_CheckPin1SatusSimple():NORMAL:USIM ENABLE,RETURN NEED!");
            return MMA_PUK1_REMAINS_ZERO;
        }
        else
        {
            MMA_NORMAILLOG("MMA_CheckPin1SatusSimple():NORMAL:USIM ENABLE,RETURN NO NEED!");
            return MMA_NONEED_PIN1;
        }
    }
}
/* END:   Added by liuyang id:48197, 2006/2/28 */

/* BEGIN: Added by liuyang id:48197, 2006/3/2   PN:A32D02310*/
/*****************************************************************************
 �� �� ��  : MMA_StartInternalTimer
 ��������  : �����ڲ���ʱ��������ʱ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��3��2��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���

  2.��    ��   : 2006��3��15��
    ��    ��   : liuyang id:48197
    �޸�����   : ����������ʱ��״̬�ж�
*****************************************************************************/
VOS_UINT32 MMA_StartInternalTimer(VOS_UINT32    ulTimes,
                                  VOS_UINT32    ulOpType,
                                  VOS_UINT16 ClientId,
                                  VOS_UINT8        OpId)
{
    VOS_UINT32 ulRet;

    if ( ulTimes < 1)
    {
        MMA_WARNINGLOG("MMA_StartInternalTimer():WARNING:TIMES IS ZERO, NO DELAY");
        return MMA_ERROR;
    }
    if ( MMA_INTERNAL_OP_NONE  == ulOpType)
    {
        MMA_WARNINGLOG("MMA_StartInternalTimer():WARNING:OP TYPE NONE, NO DELAY");
        return MMA_ERROR;
    }
    /* BEGIN: Added by liuyang id:48197, 2006/3/15   PN:A32D02500*/
    if( gstMmaInternalTimer.stTimer.ucTimerStatus != MMA_TIMER_STOP)
    {
        MMA_WARNINGLOG("MMA_StartInternalTimer():WARNING:TIMER HAS ALREADY START");
        return MMA_ERROR;
    }
    /* END:   Added by liuyang id:48197, 2006/3/15 */
    gstMmaInternalTimer.ulTimes                       = ulTimes;
    gstMmaInternalTimer.ulOpType                      = ulOpType;
    gstMmaInternalTimer.ClientId                      = ClientId;
    gstMmaInternalTimer.OpId                          = OpId;
    /*������ʱ��*/
    ulRet =  NAS_StartRelTimer(  &(gstMmaInternalTimer.stTimer.MmaHTimer),
                                 WUEPS_PID_MMA,
                                 MMA_INTERNAL_TIME,
                                 TAF_MMA,
                                 MMA_INTERNAL_TIMER_ID,
                                 VOS_RELTIMER_NOLOOP );
    if( ulRet != VOS_OK )
    {
        MMA_ERRORLOG("MMA_StartInternalTimer():ERROR:Start Timer Error!");
        /*���ز���ʧ��*/
        gstMmaInternalTimer.stTimer.ucTimerStatus     = MMA_TIMER_ERROR;
        return MMA_ERROR;
    }
    gstMmaInternalTimer.stTimer.ucTimerStatus         = MMA_TIMER_RUN;

    return MMA_SUCCESS;
}


VOS_VOID MMA_ExpiredInternalTimer(VOS_VOID)
{

    if ( MMA_TIMER_RUN != gstMmaInternalTimer.stTimer.ucTimerStatus )
    {
        MMA_WARNINGLOG("MMA_ExpiredInternalTimer():WARNING:It's not wait for this Timer!");
        return;
    }
    /*���ö�ʱ��״̬��־*/
    gstMmaInternalTimer.stTimer.ucTimerStatus = MMA_TIMER_STOP;
    switch ( gstMmaInternalTimer.ulOpType )
    {



        case MMA_GET_USIM_ICC_ID:
            if ( gstMmaInternalTimer.ulTimes < MMA_WAIT_GET_USIM_ICC_ID_MAX_TIMES )
            {
                if (  MMA_SUCCESS == MMA_StartInternalTimer(gstMmaInternalTimer.ulTimes+1,
                                                            MMA_GET_USIM_ICC_ID,
                                                            gstMmaInternalTimer.ClientId,
                                                            gstMmaInternalTimer.OpId))
                {
                    MMA_NORMAILLOG("MMA_ExpiredInternalTimer():NORMAL:Continue to get ICC ID Ready");
                    return;
                }
                else
                {
                    MMA_WARNINGLOG("MMA_ExpiredInternalTimer():WARNING:START INTERNAL TIMER FAIL for ICC ID Ready");
                    /*���ó�ʱ������*/
                    MMA_GetUsimIccIdExpired();
                }
            }
            else
            {
                /*���ó�ʱ������*/
                MMA_GetUsimIccIdExpired();
            }
            break;


        case MMA_GET_USIM_MNC_LENGTH_OP:
            MMA_WARNINGLOG("MMA_ExpiredInternalTimer():WARNING:START INTERNAL TIMER FAIL for HPLMN MNC LEN");

            TAF_MMA_SndApHplmnCnf(gstMmaValue.stGetHplmn.usClientId,
                                  gstMmaValue.stGetHplmn.ucOpId,
                                  TAF_ERR_ERROR,
                                  VOS_NULL_PTR);

            gstMmaValue.stGetHplmn.ucHplmnQryFlag = VOS_FALSE;
            break;

        default:
            MMA_WARNINGLOG("MMA_ExpiredInternalTimer:WARNING:NONE Op Type fit the Timer");
            break;
    }
    /*�����ǰ�ڲ���ʱ��ȫ�ֱ�־*/
    TAF_MMA_InitInternalTimer();

    return;
}

/* END:   Added by liuyang id:48197, 2006/3/2 */

/* BEGIN: Added by liuyang id:48197, 2006/3/8   PN:A32D02383*/

VOS_UINT32 Mma_CheckPin(TAF_PH_PIN_DATA_STRU stPinData)
{
    VOS_UINT32                          ulTemp;
    if ( MMA_SUCCESS != Mma_CheckPinCmdType(stPinData.CmdType))
    {
        MMA_WARNINGLOG("Mma_CheckPin():WARNING:PIN cmd Type error!");
        return MMA_ERROR;
    }
    if ( MMA_SUCCESS != Mma_CheckPinTypes(stPinData.PinType))
    {
        MMA_WARNINGLOG("Mma_CheckPin():WARNING:PIN TYPES ERROR!");
        return MMA_ERROR;
    }
    /*ֻ��CHANGE��UNBLOCK�� ʱ��Ż�ʹ��NEWPIN����������ֻ��ʹ��OLDPIN��
    ��ѯ����ʱ������PIN*/
    switch ( stPinData.CmdType )
    {
        /* BEGIN: Added by liuyang id:48197, 2006/3/16   PN:A32D02412*/
        case TAF_PIN_UNBLOCK:
        /* END:   Added by liuyang id:48197, 2006/3/16 */
        case TAF_PIN_CHANGE:
            ulTemp = Mma_CheckPinAvail(stPinData.aucOldPin);
            if ( (MMA_SUCCESS != Mma_CheckPinAvail(stPinData.aucNewPin))
               ||(MMA_SUCCESS != ulTemp)
               )
            {
                MMA_WARNINGLOG("Mma_CheckPin():WARNING:PIN is Error");
                return MMA_ERROR;
            }
            return MMA_SUCCESS;
        case TAF_PIN_VERIFY:
        case TAF_PIN_DISABLE:
        case TAF_PIN_ENABLE:
        /* BEGIN: Deleted by liuyang id:48197, 2006/3/16   PN:A32D02412*/
        /*case TAF_PIN_UNBLOCK:*/
        /* END:   Deleted by liuyang id:48197, 2006/3/16 */
            return Mma_CheckPinAvail(stPinData.aucOldPin);
        case TAF_PIN_QUERY:
        case TAF_PIN_RemainTime:
        case TAF_PIN2_QUERY:
            return MMA_SUCCESS;
        default:
            MMA_WARNINGLOG("Mma_CheckPin():WARNING:PIN cmd Type error in switch");
            return MMA_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : Mma_CheckPinTypes
 ��������  : У��PIN����
 �������  : TAF_PH_PIN_TYPE PinTypes
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��3��8��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mma_CheckPinTypes(TAF_PH_PIN_TYPE PinTypes)
{
    switch ( PinTypes)
    {
        case TAF_SIM_PIN:
        case TAF_SIM_PUK:
        case TAF_SIM_PIN2:
        case TAF_SIM_PUK2:
        case TAF_SIM_NON:
            return MMA_SUCCESS;
        default:
            MMA_WARNINGLOG("Mma_CheckPinTypes():WARNING:UNSUPPORT Pin Types");
            return MMA_ERROR;
    }
}


VOS_UINT32 Mma_CheckPinCmdType(TAF_PH_PIN_CMD_TYPE PinCmdType)
{
    VOS_UINT32 ulRet;

    switch ( PinCmdType)
    {
        case TAF_PIN_VERIFY:
        case TAF_PIN_CHANGE:
        case TAF_PIN_DISABLE:
        case TAF_PIN_ENABLE:
        case TAF_PIN_UNBLOCK:
        case TAF_PIN_QUERY:
        case TAF_PIN_RemainTime:
        case TAF_PIN2_QUERY:
            ulRet = MMA_SUCCESS;
            break;
        default:
            MMA_WARNINGLOG("Mma_CheckPinCmdType():WARNING:UNKNOW PIN CMD TYPE");
            ulRet = MMA_ERROR;
            break;
    }
    return ulRet;
}

/*****************************************************************************
 �� �� ��  : Mma_CheckPinLength
 ��������  : Pin�����ж�
 �������  : VOS_UINT8 *pucPin
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��3��8��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mma_CheckPinLength(VOS_UINT8 *pucPin)
{
    if ( VOS_NULL_PTR == pucPin)
    {
        MMA_WARNINGLOG("Mma_CheckPinLength():WARNING:PIN is NULL PTR");
        return MMA_ERROR;
    }
/*
    ulTemp = VOS_StrLen((VOS_INT8 *)pucPin);
    if ( (ulTemp > MMA_PIN_LEN_MAX)
       ||(ulTemp < MMA_PIN_LEN_MIN)
       )
    {
        MMA_WARNINGLOG("Mma_CheckPinLength():WARNING:PIN LENGTH is Error");
        return MMA_ERROR;
    }
 */
    return MMA_SUCCESS;
}

/* BEGIN: Added by liuyang id:48197, 2006/3/8   PN:A32D02407*/
/*****************************************************************************
 �� �� ��  : Mma_CheckPinValue
 ��������  : ���PINֵ��Ч��
 �������  : VOS_UINT8 *pucPin
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��3��8��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mma_CheckPinValue(VOS_UINT8 *pucPin)
{
    if ( VOS_NULL_PTR == pucPin)
    {
        MMA_WARNINGLOG("Mma_CheckPinValue():WARNING:PIN is NULL PTR");
        return MMA_ERROR;
    }
/*
    for ( ulI = 0; ulI < VOS_StrLen((VOS_INT8 *)pucPin) ; ulI++ )
    {
        if ( (pucPin[ulI] >'9' )
           ||(pucPin[ulI] <'0')
           )
        {
            MMA_WARNINGLOG("Mma_CheckPinValue():WARNING:PIN Value is Error");
            return MMA_ERROR;
        }
    }
*/
    return MMA_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : Mma_CheckPinAvail
 ��������  : ���PIN��Ч��
 �������  : VOS_UINT8 *pucPin
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��3��8��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mma_CheckPinAvail(VOS_UINT8 *pucPin)
{
    if ( MMA_SUCCESS != Mma_CheckPinLength(pucPin) )
    {
        MMA_WARNINGLOG("Mma_CheckPinAvail():WARNING:PIN Length is Error");
        return MMA_ERROR;
    }
    else
    {
        if ( MMA_SUCCESS != Mma_CheckPinValue(pucPin))
        {
            MMA_WARNINGLOG("Mma_CheckPinAvail():WARNING:PIN Value is Error");
            return MMA_ERROR;
        }
    }
    return MMA_SUCCESS;
}

/* MMA_InitTiλ���ƶ� */

/* NAS_MMA_RestoreContextData����λ���ƶ� */


VOS_VOID NAS_MMA_SndOutsideContextData()
{
    NAS_MMA_SDT_MSG_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_MMA_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;

    VOS_UINT8                               *pucImsi = VOS_NULL_PTR;

    pucImsi = TAF_SDC_GetSimImsi();

    pSndMsgCB = (NAS_MMA_SDT_MSG_ST *)PS_ALLOC_MSG(WUEPS_PID_MMA, sizeof(NAS_MMA_SDT_MSG_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MMA_ERRORLOG("NAS_MMA_SndOutsideContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;

    (VOS_VOID)VOS_StrNCpy(pstOutsideCtx->acVersionBuffer, PROTOCOL_STACK_VERSION, VER_MAX_LENGTH);

    pstOutsideCtx->ucSimType = g_MmaNewValue.ucSimType;

    PS_MEM_CPY(pstOutsideCtx->pc_g_aucMmaImsi, pucImsi, 9);

    PS_MEM_CPY(pstOutsideCtx->pc_g_aucMmaImei, g_aucMmaImei, TAF_PH_IMEI_LEN-1);


    PS_MEM_CPY(&pstOutsideCtx->pc_g_StatusContext, &g_StatusContext, sizeof(STATUS_CONTEXT_STRU));

    PS_MEM_CPY(&pstOutsideCtx->pc_gstMmaValue, &gstMmaValue, sizeof(TAF_MMA_GLOBAL_VALUE_ST));
    PS_MEM_CPY(&pstOutsideCtx->pc_g_stMmaMePersonalisationStatus, &g_stMmaMePersonalisationStatus, sizeof(MMA_ME_PERSONALISATION_STATUS_STRU));
    PS_MEM_CPY(pstOutsideCtx->pc_gastMmaTiTab, gastMmaTiTab, MMA_MAX_TI*sizeof(MMA_TI_TABLE));

    PS_MEM_CPY(&pstOutsideCtx->pc_gstMmaInternalTimer, &gstMmaInternalTimer, sizeof(MMA_INTERNAL_TIMER_ST));

    PS_MEM_CPY(pstOutsideCtx->pc_g_MmaSimTimer, g_MmaSimTimer, TAF_SIM_TIMER_NUM*sizeof(MMA_TIMER_ST));

    pSndMsgCB->ulReceiverPid = WUEPS_PID_MMA;
    pSndMsgCB->ulSenderPid   = WUEPS_PID_MMA;
    pSndMsgCB->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength      = sizeof(NAS_MMA_OUTSIDE_RUNNING_CONTEXT_ST) + 4;
    pSndMsgCB->usMsgID       = EVT_NAS_MMA_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;

    DIAG_TraceReport(pSndMsgCB);
    PS_FREE_MSG(WUEPS_PID_MMA, pSndMsgCB);

    return;
}

/* NAS_MMA_RestoreFixedContextData����λ���ƶ� */

VOS_VOID NAS_MMA_SndOutsideFixedContextData()
{
    NAS_MMA_FIXED_CONTEXT_MSG_ST                   *pSndMsgCB     = VOS_NULL_PTR;
    NAS_MMA_FIXED_PART_CONTEXT_ST                  *pstOutsideCtx;
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU            *pstLastSyscfgSet = VOS_NULL_PTR;
    TAF_MMA_RAT_ORDER_STRU                         *pstAllRatOrder      = VOS_NULL_PTR;
    MN_MMA_CPAM_RAT_PRIO_ENUM_UINT8                 enCpamPlmnPrio;
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8                 enAccessMode;

    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;

    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();

    pucImsi          = TAF_SDC_GetSimImsi();

    pSndMsgCB = (NAS_MMA_FIXED_CONTEXT_MSG_ST *)PS_ALLOC_MSG(WUEPS_PID_MMA, sizeof(NAS_MMA_FIXED_CONTEXT_MSG_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MMA_ERRORLOG("NAS_MMA_SndOutsideFixedContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstOutsideCtx = &pSndMsgCB->stFixedOutsideCtx;

    /* version 0 part variable */
    PS_MEM_CPY(pstOutsideCtx->aucMmaImsi, pucImsi, 9);

    pstOutsideCtx->aucSimType = g_MmaNewValue.ucSimType;

    pstOutsideCtx->ulPrefBand = pstLastSyscfgSet->stUserSetBand.uUserSetGuBand.ulPrefBand;
    pstOutsideCtx->Band = pstLastSyscfgSet->stUserSetBand.uUserSetUeFormatGuBand;
    pstOutsideCtx->ulQuickStartFlg = gstMmaValue.ulQuickStartFlg;

    pstOutsideCtx->stEfustServiceCfg = gstMmaValue.stEfustServiceCfg;

    PS_MEM_CPY(pstOutsideCtx->aucImeiBcd, g_MmaNewValue.aucImeiBcd, TAF_PH_IMEI_LEN+1);
    pstAllRatOrder = TAF_MMA_GetRatPrioListAddr();

    MN_MMA_GetCpamGURatPrio(&enCpamPlmnPrio, pstAllRatOrder);
    MN_MMA_GetCpamGUAccessRat(&enAccessMode, pstAllRatOrder);

    /* ����gstMmaValue.stRatPrioList��pstOutsideCtx->AccessMode��pstOutsideCtx->PlmnPrio��ֵ */
    pstOutsideCtx->enAccessMode   = enAccessMode;
    pstOutsideCtx->PlmnPrio       = enCpamPlmnPrio + TAF_PLMN_PRIO_DIST_BTWN_CPAM_SYSCFG;

    pstOutsideCtx->MsClassType = gstMmaValue.stSetMsClass.MsClassType;
    /* Modified by h00313353 for Iteration 13, 2015-4-15, begin */
    pstOutsideCtx->enRoam = pstLastSyscfgSet->enRoam;
    /* Modified by h00313353 for Iteration 13, 2015-4-15, end */
    pstOutsideCtx->ucRoamFeatureStatus = gstMmaValue.ucRoamFeatureStatus;

    pstOutsideCtx->stMeInfo = gstMmaValue.stMeInfo;

    pstOutsideCtx->stSimLockPlmnInfo = g_MmaNewValue.stSimLockPlmnInfo;
    pstOutsideCtx->stCardLockStatus = g_MmaNewValue.stCardLockStatus;
    pstOutsideCtx->stSimLockMaxTimes = g_MmaNewValue.stSimLockMaxTimes;

    PS_MEM_CPY(pstOutsideCtx->aucPwd, g_MmaNewValue.aucPwd, TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX+1);
    pstOutsideCtx->usSimMePersonalisationActFlag = g_MmaNewValue.usSimMePersonalisationActFlag;
    PS_MEM_CPY(pstOutsideCtx->aucSimPersonalisationStr, g_MmaNewValue.aucSimPersonalisationStr, TAF_MAX_IMSI_LEN+1);

    /* version 1 part variable */
    PS_MEM_CPY(&pstOutsideCtx->gstMmaBandCapa,
               TAF_MMA_GetUeSupportBandAddr(),
               sizeof(TAF_MMA_UE_BAND_CAPA_ST));

    pstOutsideCtx->ulVersion = 1;

    pSndMsgCB->ulReceiverPid = WUEPS_PID_MMA;
    pSndMsgCB->ulSenderPid   = WUEPS_PID_MMA;
    pSndMsgCB->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pSndMsgCB->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pSndMsgCB->ulLength      = sizeof(NAS_MMA_FIXED_PART_CONTEXT_ST) + 4;
    pSndMsgCB->usMsgID       = EVT_NAS_MMA_FIXED_PART_CONTEXT;

    DIAG_TraceReport(pSndMsgCB);
    PS_FREE_MSG(WUEPS_PID_MMA, pSndMsgCB);

    return;
}



/*****************************************************************************
 �� �� ��  : MMA_OpPinSuccess
 ��������  : ����PIN�Ƿ�ɹ�
 �������  : TAF_PH_PIN_CNF_STRU *pstPinCnf
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��3��14��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���
  2.��    ��   : 2007��02��09��
    ��    ��   : luojian id:60022475
    �޸�����   : �������ⵥ��A32D08488
*****************************************************************************/
VOS_UINT32 MMA_OpPin1Success(const TAF_PH_PIN_CNF_STRU *pstPinCnf)
{


    if ( (TAF_SIM_PIN != pstPinCnf->PinType) && (TAF_SIM_PUK != pstPinCnf->PinType) )
    {
        return VOS_FALSE;
    }

    if ( TAF_PH_OP_PIN_OK != pstPinCnf->OpPinResult )
    {
       return VOS_FALSE;
    }
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : MMA_Pin1Noneed
 ��������  : �ж��Ƿ���ҪPIN1
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��3��14��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MMA_Pin1Noneed()
{
    VOS_UINT32 ulRet;
    /*���PIN״̬*/
    ulRet = MMA_CheckPin1SatusSimple();
    /*PINʹ��*/
    if ( MMA_NONEED_PIN1 != ulRet )
    {
        MMA_NORMAILLOG("MMA_Pin1Noneed():NORMAL:NEED PIN");
        return VOS_FALSE;
    }
    else
    {
        MMA_NORMAILLOG("MMA_Pin1Noneed():NORMAL:NO NEED PIN");
        return VOS_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : MMA_CheckUsimStatus
 ��������  : ���USIM״̬�Ƿ�����,PIN״̬�Ƿ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��3��15��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MMA_CheckUsimStatus()
{
    VOS_UINT8   ucUsimStatus;
    VOS_UINT32  ulRet;

    ulRet = MMA_PhoneGetUsimStatus(&ucUsimStatus);
    if ( (MMA_SUCCESS != ulRet )
       ||((  (ucUsimStatus != MMA_USIM_ABSENT)
              &&(ucUsimStatus != MMA_USIM_PRESENT)
             )
         )
       )
    {
        /*USIM��ʼ��δ��ɣ�������ʱ���ȴ�*/
        /*MMA_StartInitialTimer();*/
        MMA_WARNINGLOG("MMA_CheckUsimStatus():WARNING:USIM IS NOT READY");
        return MMA_ERROR;
    }
    else
    {
        if ( MMA_USIM_PRESENT == ucUsimStatus)
        {
            /*PINʹ��*/
            ulRet = MMA_CheckPin1SatusSimple();
            if (MMA_PIN1_STATUS_FAIL == ulRet)
            {
                MMA_NORMAILLOG("MMA_CheckUsimStatus():NORMAL:PIN1 STATUS NOT READY");
                return MMA_ERROR;
            }
            else if ( MMA_NEED_PIN1 == ulRet )
            {
                MMA_NORMAILLOG("MMA_CheckUsimStatus():NORMAL:PIN1 NEED");
                return MMA_NORMAL;
            }
            else
            {
                MMA_NORMAILLOG("MMA_CheckUsimStatus():NORMAL:PIN1 NO NEED");
            }
        }
        return MMA_SUCCESS;
    }
}
TAF_PH_MS_CLASS_TYPE MMA_GetCurMsClass()
{
    TAF_PH_MS_CLASS_TYPE                Result;
    VOS_UINT32                          ulDataLen;
    NAS_NVIM_MS_CLASS_STRU              stMsClass;

    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    enSysMode = TAF_SDC_GetSysMode();
    ulDataLen = 0;

    if (  (TAF_PH_MS_CLASS_A == gstMmaValue.pg_StatusContext->ucModeService)
        &&(TAF_SDC_SYS_MODE_GSM     == enSysMode)
       )
    {
        return TAF_PH_MS_CLASS_B;
    }

    if (TAF_PH_MS_CLASS_NULL == gstMmaValue.pg_StatusContext->ucModeService )
    {

        PS_MEM_SET(&stMsClass, 0x00, sizeof(NAS_NVIM_MS_CLASS_STRU));

        (VOS_VOID)NV_GetLength(en_NV_Item_MMA_MsClass, &ulDataLen);

        if (NV_OK != NV_Read(en_NV_Item_MMA_MsClass ,
                             &stMsClass,
                             ulDataLen))
        {
            MMA_WARNINGLOG("MMA_GetCurMsClass():WARNING:Read from NVIM MSClass Fail");
            Result = TAF_PH_MS_CLASS_A;/*TAF_PH_MS_CLASS_CC TAF_PH_MS_CLASS_CG*/
        }
        else
        {
            Result = stMsClass.ucMsClass;
        }
    }
    else
    {
        Result = gstMmaValue.pg_StatusContext->ucModeService;
    }
    return Result;
}

/* ɾ��MMA_TranslateIntIntoBitInRegStates */


/*****************************************************************************
 �� �� ��  : MMA_ClearCurRegOp
 ��������  : ���ע��״̬�ṹ�����е�OP��
 �������  : TAF_PH_REG_STATE_STRU  *pstCurRegSta
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��4��13��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MMA_ClearCurRegOp(TAF_PH_REG_STATE_STRU  *pstCurRegSta)
{
    pstCurRegSta->OP_CsRegState = VOS_FALSE;
    pstCurRegSta->OP_PsRegState = VOS_FALSE;
    pstCurRegSta->OP_ucAct      = VOS_FALSE;
    pstCurRegSta->OP_Lac        = VOS_FALSE;
    pstCurRegSta->OP_Plmn       = VOS_FALSE;
    pstCurRegSta->OP_Rac        = VOS_FALSE;
    pstCurRegSta->OP_CellId     = VOS_FALSE;
    pstCurRegSta->OP_Spare      = VOS_FALSE;
    return;
}




VOS_UINT32 MMA_PhoneGetUsimType( VOS_UINT8 *pucSimType )
{
    VOS_UINT8               ucUsimType;


    ucUsimType = USIMM_CARD_NOCARD;

#ifndef __PS_WIN32_RECUR__
    /*��ȡ��ǰUSIM״̬*/
    /*������USIMAPI��ֵ��Ϊ0,���ʾ�д���*/
    if  ( MMA_SUCCESS != MMA_GetUsimStatusFromUsim(VOS_NULL_PTR, &ucUsimType) )
    {
        *pucSimType = USIMM_CARD_NOCARD;

        MMA_WARNINGLOG("MMA_PhoneGetUsimType():WORNING:Invoke Taf_UsimmGetStatus fail.");
        return MMA_ERROR;
    }
    if ( USIMM_CARD_SIM == ucUsimType )
    {
        *pucSimType = MMA_USIM_TYPE_SIM;
    }
    else
    {
        *pucSimType = MMA_USIM_TYPE_USIM;
    }

    g_MmaNewValue.ucSimType = *pucSimType;

#else
    *pucSimType = g_MmaNewValue.ucSimType;

#endif

    return MMA_SUCCESS;
}



VOS_VOID MMA_StopInternalTimer()
{
    VOS_UINT32 ulRet;
    if ( gstMmaInternalTimer.stTimer.ucTimerStatus != MMA_TIMER_RUN )
    {
        MMA_WARNINGLOG("MMA_StopInternalTimer():WARNING:INTERNAL TIMER IS NOT RUNNING");
    }


    ulRet = NAS_StopRelTimer(WUEPS_PID_MMA, MMA_INTERNAL_TIMER_ID,
                            &(gstMmaInternalTimer.stTimer.MmaHTimer));


    if ( VOS_OK != ulRet )
    {
        MMA_WARNINGLOG("MMA_StopInternalTimer():WARNING:Nas_StopRelTimer failed");
    }
    TAF_MMA_InitInternalTimer();
    return;
}






VOS_VOID MMA_TurnOffForFlightMode( VOS_VOID )
{
    /*Make DSP into Halt mode, and close DSP PLL, BBP PLL, power off BBP, RF */

    OM_SetDrxTimerWakeSrc(VOS_GetModemIDFromPid(WUEPS_PID_MMA));

    TAF_MMA_SndDrxTimerInfo(VOS_TRUE);
    return;
}
VOS_VOID MMA_TurnOnForFlightMode()
{
    /* ��ֹ�ײ�˯�� */
    /* V9R1/V3R3��NAS����ͶPSƱ��ɾ��LTE���Ժ���� */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);

    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        (VOS_VOID)vos_printf("\n*MMA_TurnOnForFlightMode:PWRCTRL_SLEEP_NAS,TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK\n");
    }
    return;
}
VOS_BOOL MN_PH_IsUsingPlmnSel(VOS_VOID)
{
    VOS_BOOL                            bPlmnSelFlg;
    VOS_UINT8                           ucSimType;

    bPlmnSelFlg = VOS_FALSE;
    ucSimType   = MMA_USIM_TYPE_USIM;

    /*User controlled PLMN Selector with Access Technology*/
    if (PS_USIM_SERVICE_NOT_AVAILIABLE
                    == NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_UPLMN_SEL_WACT))
    {
        (VOS_VOID)MMA_PhoneGetUsimType(&ucSimType);

        if (MMA_USIM_TYPE_SIM == ucSimType)
        {
            if (PS_USIM_SERVICE_AVAILIABLE
                        == NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_PLMN_SELECTOR))

            {
                bPlmnSelFlg = VOS_TRUE;
            }
        }

    }

    return bPlmnSelFlg;

}
VOS_VOID MN_MMA_FillUPlmnFile(
    VOS_UINT16                  usUpdateFile,
    VOS_UINT8                  *pucEfFile,
    TAF_USER_PLMN_LIST_STRU    *pstUPlmnInfo
)
{
    VOS_UINT8  ucRecordLen;
    VOS_UINT16 i;
    VOS_UINT16 usRatMode;

    /* Modified by h00313353 for iteration 9, 2015-2-11, begin */
    if (USIMM_GSM_EFPLMNSEL_ID == usUpdateFile)
    /* Modified by h00313353 for iteration 9, 2015-2-11, end */
    {
        ucRecordLen = 3;
    }
    else
    {
        ucRecordLen = 5;
    }

    for (i = 0; i < pstUPlmnInfo->usPlmnNum; i++)
    {
        pucEfFile[i*ucRecordLen]  = (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].Mcc >> 4));
        pucEfFile[i*ucRecordLen] <<= 4;
        pucEfFile[i*ucRecordLen] |= (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].Mcc >> 8));

        pucEfFile[(i*ucRecordLen)+1]  = (VOS_UINT8)(0x0f & pstUPlmnInfo->Plmn[i].Mcc);
        if (0xF0 == (0xf0 & (pstUPlmnInfo->Plmn[i].Mnc >>4)))
        {
            pucEfFile[(i*ucRecordLen)+1] |= (VOS_UINT8)(0xf0 & (pstUPlmnInfo->Plmn[i].Mnc >>4));

            pucEfFile[(i*ucRecordLen)+2]  = (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].Mnc));
            pucEfFile[(i*ucRecordLen)+2] <<= 4;
            pucEfFile[(i*ucRecordLen)+2] |= (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].Mnc >>4));
        }
        else
        {
            pucEfFile[(i*ucRecordLen)+1] |= (VOS_UINT8)(0xf0 & (pstUPlmnInfo->Plmn[i].Mnc <<4));

            pucEfFile[(i*ucRecordLen)+2]  = (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].Mnc >>4));
            pucEfFile[(i*ucRecordLen)+2] <<= 4;
            pucEfFile[(i*ucRecordLen)+2] |= (VOS_UINT8)(0x0f & (pstUPlmnInfo->Plmn[i].Mnc >>8));
        }

        if (5 == ucRecordLen)
        {
            usRatMode = pstUPlmnInfo->PlmnRat[i];
            pucEfFile[(i*ucRecordLen)+3] = (VOS_UINT8)(usRatMode >> 8);
            pucEfFile[(i*ucRecordLen)+4] = (VOS_UINT8)(usRatMode & 0xFF);
        }
    }

    return;
}



/*****************************************************************************
 �� �� ��  : MMA_GetProductionVersion
 ��������  : �õ���Ʒ��Ϣ
 �������  : ������Ϣ�ĵ�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��1��13��
    ��    ��   : ���ٻ�
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MMA_GetProductionVersion(VOS_CHAR *pcDest)
{
    (VOS_VOID)VOS_StrNCpy(pcDest, (VOS_CHAR *)gstMmaValue.stMeInfo.SoftVersion.aucRevisionId,
        TAF_MAX_REVISION_ID_LEN+1);
}


VOS_VOID Taf_GetProductionID(VOS_CHAR *pcDest)
{
    (VOS_VOID)VOS_StrNCpy(pcDest, (VOS_CHAR *)gstMmaValue.stMeInfo.ModelId.aucModelId,
        TAF_MAX_MODEL_ID_LEN+1);
}

/*****************************************************************************
 �� �� ��  : MMA_WriteVersion
 ��������  : ��PS�汾��Ϣע�ᵽ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��1��13��
    ��    ��   : ���ٻ�
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MMA_WriteVersion(VOS_VOID)
{
    VOS_UINT32                 ulRslt;
    VOS_CHAR                   acVersionBuffer[VER_MAX_LENGTH]  = {0};

    (VOS_VOID)VOS_StrNCpy(acVersionBuffer, PROTOCOL_STACK_VERSION, VER_MAX_LENGTH);

    ulRslt = (VOS_UINT32)mdrv_ver_memberctrl((signed char *)acVersionBuffer,
                    VER_MAX_LENGTH, VER_PS, VERIONWRITEMODE); /* д��Э��ջ�汾��Ϣ */
    if( VOS_OK != ulRslt )
    {
        MMA_WARNINGLOG("MMA_WriteVersion():WARNING:Write PS Version Info fail.");
    }
}


/* ����WuepsMmaPidInit�ƶ�λ�� */


/* ����Mma_TimeOutProcɾ�� */


/* ɾ��Mma_MsgProc�������Ƶ����ļ��� */

/* ɾ�� MMA_UsimAccessCnfMsgProc�ӿں�������Ϊ PS_USIM_GENERIC_ACCESS_CNF �����ϱ� MMA ģ�鴦�� */

VOS_UINT32 MMA_USIMMaxRecordNumCnfProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{



    MMA_StopInternalTimer();

    return VOS_TRUE;
}



VOS_UINT32 MMA_UsimPINOperateMsgProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_PINHANDLE_CNF_STRU           *pstUsimPinMsg;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */
    TAF_PH_PIN_CNF_STRU                 stPinTmp;

    pstUsimPinMsg = (USIMM_PINHANDLE_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stPinTmp, 0x00, sizeof(stPinTmp));

    stPinTmp.CmdType      = (VOS_UINT8)pstUsimPinMsg->enCmdType;
    stPinTmp.OpPinResult  = (VOS_UINT8)pstUsimPinMsg->stCmdResult.ulResult;
    stPinTmp.PinType      = (VOS_UINT8)pstUsimPinMsg->enPinType;
    (VOS_VOID)NAS_USIMMAPI_GetPinRemainTime((USIMM_PIN_REMAIN_STRU *)(&(stPinTmp.RemainTime)));
    MMA_PinDataReport((const TAF_PH_PIN_CNF_STRU *)&(stPinTmp));

    return VOS_TRUE;
}

/* MMA_UsimGetPNNFileRspForCPNN */
/* MMA_UsimGetOPLFileRspForCPNN */
/* MMA_ProcRecRange */
/* MMA_UsimGetSimSpnInfo */

/* TAF_MMA_UsimGetFileRspPnnMsgProc */



/* MMA_UsimGetFileRspMsgProc */







/* TAF_MMA_UsimRefreshIndAllFileChangedMsgProc */
/* MMA_USIMRefreshFileProc */
/* TAF_MMA_UsimRefreshIndFileListChangedMsgProc */
/* MMA_USIMRefreshFileProc */


VOS_UINT32 MMA_ProcHotInOutUsimStatusInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
    VOS_UINT8                           ucCardStatus;
    /* Modified by h00313353 for iteration 9, 2015-2-9, end */
    VOS_UINT8                           ucSimLockStatus;
    USIMM_HOTINOUT_IND_STRU            *pstUsimMsg = VOS_NULL_PTR;

    pstUsimMsg = (USIMM_HOTINOUT_IND_STRU *)pstMsg;

    /* ��ȡ����״̬ */
    if ( MMA_SIM_IS_LOCK == MMA_GetMeLockStatus() )
    {
        ucSimLockStatus                 = VOS_TRUE;
    }
    else
    {
        ucSimLockStatus                 = VOS_FALSE;
    }

    /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
    ucCardStatus                        = USIMM_CARD_SERVIC_BUTT;
    /* Modified by h00313353 for iteration 9, 2015-2-9, end */

    /* �Ȳ��� */
    if (SIM_CARD_OUT == pstUsimMsg->ulCardInOutStatus)
    {
        /* USIM���Ȱγ���״̬�ϱ�255 */
        TAF_MMA_SndAtIccStatusInd(TAF_PH_USIM_NON, ucSimLockStatus);

        /* ��USIM�Ȱγ��ı�ʶ��ΪTRUE */
        g_ucUsimHotOutFlag = VOS_TRUE;

        g_ucUsimHotInFlag  = VOS_FALSE;

        /* �յ��Ȱγ��¼���������1 */
        g_ulUsimHotOutCount++;
    }
    /* �Ȳ��� */
    else if (SIM_CARD_IN == pstUsimMsg->ulCardInOutStatus)
    {
        g_ucUsimHotOutFlag = VOS_FALSE;

        /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
        (VOS_VOID)NAS_USIMMAPI_GetCardType(&ucCardStatus, VOS_NULL_PTR);
        /* Modified by h00313353 for iteration 9, 2015-2-9, end */

        /* ֻ���ڿ����γ���������յ����������Ч */
        /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
        if (USIMM_CARD_SERVIC_ABSENT == ucCardStatus)
        /* Modified by h00313353 for iteration 9, 2015-2-9, end */
        {
            TAF_MMA_SndAtIccStatusInd(TAF_PH_USIM_STATUS_UNAVAIL, ucSimLockStatus);

            /* ��USIM�Ȳ���ı�ʶ��ΪTRUE */
            g_ucUsimHotInFlag  = VOS_TRUE;
        }

        /* �յ��Ȳ����¼���������1 */
        g_ulUsimHotInCount++;
    }
    else
    {
        /* for pclint */
    }

    return VOS_TRUE;
}

VOS_UINT32 MMA_UsimRestrictedAccessCnfMsgProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent;

    /* Modified by h00313353 for iteration 9, 2015-2-6, begin */
    USIMM_RACCESS_CNF_STRU             *pMsg;

    pMsg = (USIMM_RACCESS_CNF_STRU *)pstMsg;
    /* Modified by h00313353 for iteration 9, 2015-2-6, end */

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_UsimRestrictedAccessCnfMsgProc:ERROR:ALLOC MEMORY FAIL.");

        return VOS_TRUE;
    }
    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if ((MMA_SUCCESS == (pMsg->stCmdResult.ulResult))
     && (USIMM_SW_SENDCMD_ERROR != pMsg->stCmdResult.ulErrorCode))
    {

        pstPhoneEvent->PhoneEvent = TAF_PH_EVT_RESTRICTED_ACCESS_CNF;
        pstPhoneEvent->OpId = 0;
        pstPhoneEvent->ClientId = (VOS_UINT16)pMsg->stCmdResult.ulSendPara;
        pstPhoneEvent->OP_UsimRestrictAccess = 1;
        pstPhoneEvent->RestrictedAccess.ucLen = (VOS_UINT8)pMsg->usLen;
        pstPhoneEvent->RestrictedAccess.ucSW1 = pMsg->ucSW1;
        pstPhoneEvent->RestrictedAccess.ucSW2 = pMsg->ucSW2;
        PS_MEM_CPY(pstPhoneEvent->RestrictedAccess.aucContent,
                  pMsg->aucContent,
                  pMsg->usLen);
    }
    else
    {
        pstPhoneEvent->PhoneEvent    = TAF_PH_EVT_ERR;
        pstPhoneEvent->ClientId      = (VOS_UINT16)pMsg->stCmdResult.ulSendPara;
        pstPhoneEvent->OP_PhoneError = 1;
        pstPhoneEvent->PhoneError    = TAF_ERR_SIM_FAIL;
    }

    /* ���õ绰�����ϱ����� */
    MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

    return VOS_TRUE;
}
VOS_UINT32 MMA_UsimRestrictedAccessCommandProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent   = VOS_NULL_PTR;
    USIMM_RACCESS_REQ_STRU             *pstCommand      = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstRcvMsg       = VOS_NULL_PTR;

    pstRcvMsg = (MN_APP_REQ_MSG_STRU *)pstMsg;

    pstCommand  = (USIMM_RACCESS_REQ_STRU *)pstRcvMsg->aucContent;
    usClientId  = pstRcvMsg->clientId;
    ucOpId      = pstRcvMsg->opId;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MMA_UsimRestrictedAccessCommandProc:ERROR:ALLOC MEMORY FAIL.");
        return VOS_TRUE;
    }

    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    ulRslt = NAS_USIMMAPI_RestrictedAccessReq(WUEPS_PID_MMA,
                                              usClientId,
                                              pstCommand);

    if (TAF_ERR_NO_ERROR != ulRslt)
    {

        pstPhoneEvent->OP_PhoneError      = 1;
        pstPhoneEvent->PhoneEvent         = TAF_PH_EVT_ERR;
        pstPhoneEvent->ClientId           = usClientId;
        pstPhoneEvent->OpId               = ucOpId;
        pstPhoneEvent->PhoneError         = TAF_ERR_SIM_BUSY;

        /* ���õ绰�����ϱ����� */
        MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    }

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

    return VOS_TRUE;

}

/* MMA_TafMsgProc ����ɾ�� */

/* END:   Added by liuyang id:48197, 2006/8/9   PN:�Ż�MMA*/

VOS_VOID  MMA_PhoneGetIccId(VOS_UINT16           ClientId,
                            VOS_UINT8            OpId)
{
    /* Modified by h00313353 for iteration 9, 2015-2-3, begin */
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;

    PS_MEM_SET(&stGetFileInfo, 0x00, sizeof(stGetFileInfo));
    /* Modified by h00313353 for iteration 9, 2015-2-3, end */

    if(MMA_TIMER_STOP != gstMmaInternalTimer.stTimer.ucTimerStatus)
    {
        MMA_WARNINGLOG("MMA_PhoneGetIccId():WARNING:USIM is not Ready!");
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_UNSPECIFIED_ERROR,
                                 TAF_PH_ICC_ID);
        return;
    }

    /*������ʱ��*/
    if(MMA_SUCCESS != MMA_StartInternalTimer(1,
                                             MMA_GET_USIM_ICC_ID,
                                             ClientId,
                                             OpId))
    {
        MMA_WARNINGLOG("MMA_PhoneGetIccId():WARNING:Unknow Error!");
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_UNSPECIFIED_ERROR,
                                 TAF_PH_ICC_ID);
        return;
    }
    /*����*/
    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                    /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
                                    USIMM_UNLIMIT_AUTO,
                                    USIMM_ICCID_ID,
                                    /* Modified by h00313353 for iteration 9, 2015-2-4, end */
                                    0);

    if( USIMM_API_SUCCESS != NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMA,
                                              0,
                                              &stGetFileInfo))
    {
        MMA_WARNINGLOG("MMA_PhoneGetIccId():WARNING:get File Error!");
        MMA_ReportParaQueryError(ClientId, OpId,
                                 TAF_ERR_UNSPECIFIED_ERROR,
                                 TAF_PH_ICC_ID);

        /*ֹͣ��ʱ��*/
        MMA_StopInternalTimer();
        return;
    }
    gstMmaValue.stGetIccId.ClientId = ClientId;
    gstMmaValue.stGetIccId.OpId     = OpId;
    return;
}


/* MMA_GetUsimIccIdFileInd */


MMA_GET_ICC_ID_ST *TAF_MMA_GetIccIdInfo(VOS_VOID)
{
    return &gstMmaValue.stGetIccId;
}


TAF_MMA_GET_HPLMN_STRU *TAF_MMA_GetHplmnInfo(VOS_VOID)
{
    return &gstMmaValue.stGetHplmn;
}


/*****************************************************************************
 �� �� ��  : MMA_GetUsimIccIdExpired
 ��������  : �ȴ�USIM�ϱ������ʱ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2006��8��23��
    ��    ��   : liuyang id:48197
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MMA_GetUsimIccIdExpired(VOS_VOID)
{
    /*��ȡICCID����ʧ��*/
    MMA_WARNINGLOG("MMA_GetUsimIccIdExpired():WARNING:GET USIM ICC ID, Fail");

    MMA_ReportParaQueryError(gstMmaInternalTimer.ClientId,
                             gstMmaInternalTimer.OpId,
                             TAF_ERR_UNSPECIFIED_ERROR,
                             TAF_PH_ICC_ID);

    return;
}




/*VOS_VOID  Taf_GetSpnName(VOS_UINT8*  aucSpnName,VOS_UINT32 ulMaxLen)*/
/*TAF_UINT32  Taf_DefGetSPN(TAF_UINT8 ucSpnType, TAF_PH_USIM_SPN_STRU   *pstAtSPNRslt)*/

VOS_BOOL Taf_IsWBandSupported(VOS_UINT16 usBandNo)
{
    VOS_UINT16    usBandMask;

    /*Ŀǰֻ֧��Wֻ������֧�ֵ�Band11*/
    /*lint -e701*/
    if ((TAF_DEVICE_AT_MAX_W_BAND_NUM < usBandNo)||(0 == usBandNo))

    {
        return VOS_FALSE;
    }
    /* W Rf support
    -------------------------------------------------------------------------------
          bit8       bit7      bit6     bit5    bit4     bit3      bit2     bit1
                                                         bit11     bit10    bit9
    -------------------------------------------------------------------------------
    WCDMA   900(VIII)  2600(VII) 800(VI)  850(V)  1700(IV) 1800(III) 1900(II) 2100(I) oct1
            spare      spare     spare    spare   spare    spare     spare   J1700(IX)oct2
   */
    usBandMask = (VOS_UINT16)(0x0001 << (usBandNo-1));
    /*lint +e701*/

    if (usBandMask & TAF_MMA_GetUeSupportBandAddr()->unWRFSptBand.ulBand)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}
TAF_UINT32  TAF_SetPrefPlmnType(
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType
)
{
    VOS_UINT32                          ulRet;

    if (enPrefPlmnType > MN_PH_PREF_PLMN_HPLMN)
    {
        return TAF_PARA_TYPE_NOT_SUPPORT;
    }

    if (MN_PH_PREF_PLMN_UPLMN == enPrefPlmnType)
    {
        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_UPLMN_SEL_WACT);

        if (PS_USIM_SERVICE_NOT_AVAILIABLE == ulRet)
        {
            ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_PLMN_SELECTOR);
        }
    }
    else if (MN_PH_PREF_PLMN_OPLMN == enPrefPlmnType)
    {
        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_OPLMN_SEL_WACT);
    }
    else
    {
        ulRet = NAS_USIMMAPI_IsServiceAvailable(NAS_USIM_SVR_HPLMN_WACT);
    }


    if (PS_USIM_SERVICE_NOT_AVAILIABLE == ulRet)
    {
        return TAF_PARA_TYPE_NOT_SUPPORT;
    }

    return TAF_PARA_OK;
}



VOS_VOID  Taf_SyscfgBand2Str(VOS_UINT32 band,TAF_CHAR* strBand)
{

    VOS_UINT32 i,ulLen;
    VOS_UINT32 ulBandStrLen = 0;
    TAF_CHAR* strSep = "/";

    ulBandStrLen = 0;
    ulLen = sizeof(gastMmaSyscfgBandStr)/sizeof(gastMmaSyscfgBandStr[0]);

    MMA_INFOLOG1("Taf_SyscfgBand2Str:band = \r\n", (VOS_INT)band);

    for (i = 0; i < ulLen; i++)
    {
        if(0 != (band & gastMmaSyscfgBandStr[i].BandMask))
        {
            (VOS_VOID)VOS_StrCpy(strBand + ulBandStrLen, gastMmaSyscfgBandStr[i].BandStr);

            ulBandStrLen += VOS_StrLen(gastMmaSyscfgBandStr[i].BandStr);

            (VOS_VOID)VOS_StrCpy(strBand + ulBandStrLen, strSep);

            ulBandStrLen += VOS_StrLen(strSep);

            if(ulBandStrLen >= (TAF_PH_SYSCFG_GROUP_BAND_LEN/2))
            {
                MMA_ERRORLOG("Taf_SyscfgBand2Str(): ERROR :strBand too long ");
                break;
            }
        }
    }

    if (ulBandStrLen > 0)
    {
        strBand[ulBandStrLen-1] = '\0';
    }

    return;
}



VOS_VOID  Taf_GetSyscfgBandGroupStr(TAF_PH_SYSCFG_BAND_STR* pstSysCfgBandStr)
{
    /*
    ��ȡ֧�ֵ�Ƶ���� gstMmaBandCapa.ulAllUeBand
    ��Group1����õ�Band1,��Group2����õ�Band2,�ǿ�ʱ�ٸ������������ʾ��Ӧ��Str
    */

    VOS_UINT32 bandGroup1,bandGroup2,bandAll,bandNeedTransferTo64Bit;
    TAF_CHAR*  BandStr1;
    TAF_CHAR*  BandStr2;

    TAF_CHAR* strSysCfgBandGroup = pstSysCfgBandStr->strSysCfgBandGroup;

    BandStr1 = (TAF_CHAR*)PS_MEM_ALLOC(WUEPS_PID_MMA, (TAF_PH_SYSCFG_GROUP_BAND_LEN/2));

    if (VOS_NULL_PTR == BandStr1)
    {
        return;
    }

    BandStr2 = (TAF_CHAR*)PS_MEM_ALLOC(WUEPS_PID_MMA, (TAF_PH_SYSCFG_GROUP_BAND_LEN/2));

    if (VOS_NULL_PTR == BandStr2)
    {
        PS_MEM_FREE(WUEPS_PID_MMA,BandStr1);
        return;
    }

    PS_MEM_SET(BandStr1,0,(TAF_PH_SYSCFG_GROUP_BAND_LEN/2));
    PS_MEM_SET(BandStr2,0,(TAF_PH_SYSCFG_GROUP_BAND_LEN/2));


    bandAll = TAF_PH_BAND_ANY;
    bandGroup1 = TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand & TAF_PH_BAND_GROUP1_FOR_SYSCFG;
    bandGroup2 = TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand & TAF_PH_BAND_GROUP2_FOR_SYSCFG;
    bandNeedTransferTo64Bit = bandGroup1 & TAF_PH_BAND_NEED_CHANGE_TO_64BIT;


    if ((0 == bandGroup1)&&(0 == bandGroup2))
    {
        (VOS_VOID)VOS_sprintf(strSysCfgBandGroup, "((%x,\"All bands\"))",bandAll);
    }
    else if ((0 != bandGroup1) && (0 != bandGroup2))
    {
        Taf_SyscfgBand2Str(bandGroup1,BandStr1);
        Taf_SyscfgBand2Str(bandGroup2,BandStr2);
        if (0 != bandNeedTransferTo64Bit )
        {
            (VOS_VOID)VOS_sprintf(strSysCfgBandGroup, "((%x%08x,\"%s\"),(%x,\"%s\"),(%x,\"All bands\"))",
                        bandNeedTransferTo64Bit,(bandGroup1 & ~bandNeedTransferTo64Bit),BandStr1,bandGroup2,BandStr2,bandAll);
        }
        else
        {
            (VOS_VOID)VOS_sprintf(strSysCfgBandGroup, "((%x,\"%s\"),(%x,\"%s\"),(%x,\"All bands\"))",
                        bandGroup1,BandStr1,bandGroup2,BandStr2,bandAll);
        }
    }
    else if  (0 != bandGroup1)
    {
        Taf_SyscfgBand2Str(bandGroup1,BandStr1);
        if (0 != bandNeedTransferTo64Bit )
        {
            (VOS_VOID)VOS_sprintf(strSysCfgBandGroup, "((%x%08x,\"%s\"),(%x,\"All bands\"))",
                                     bandNeedTransferTo64Bit,(bandGroup1 & ~bandNeedTransferTo64Bit),BandStr1,bandAll);
        }
        else
        {
            (VOS_VOID)VOS_sprintf(strSysCfgBandGroup, "((%x,\"%s\"),(%x,\"All bands\"))",
                                     bandGroup1 ,BandStr1,bandAll);
        }

    }
    else
    {
        Taf_SyscfgBand2Str(bandGroup2,BandStr2);
        (VOS_VOID)VOS_sprintf(strSysCfgBandGroup, "((%x,\"%s\"),(%x,\"All bands\"))",
                                          bandGroup2,BandStr2,bandAll);

    }

    PS_MEM_FREE(WUEPS_PID_MMA,BandStr1);
    PS_MEM_FREE(WUEPS_PID_MMA,BandStr2);

    return;
}

/* Deleted by h00313353 for Iteration 13, 2015-4-25, begin */
/* MN_MMA_GetSyscfgExLteBandGroupStr */
/* Deleted by h00313353 for Iteration 13, 2015-4-25, end */

VOS_UINT32  TAF_TimeCmp(
    VOS_UINT32                          ulStartTick,
    VOS_UINT32                          ulEndTick,
    VOS_UINT32                          ulCmpSec
)
{
    VOS_UINT32                          ulCostSec;

    /* ʱ�������0��ʼ���������Ե�ǰ��ʱ���Ӧ�ô����ϴΡ�����ʱ���
       ��0xFFFFFFFFʱ�����õ�0������else��֧����������� */
    if (ulEndTick >= ulStartTick)
    {
        ulCostSec = (ulEndTick - ulStartTick)/(32*1024);
    }
    else
    {
        /*lint -e961*/
        ulCostSec = (0xFFFFFFFF - ulStartTick + ulEndTick)/(32*1024);
        /*lint +e961*/
    }

    if ( ulCostSec <= ulCmpSec )
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}
TAF_UINT32  Taf_QueryCSNR(TAF_INT16 *psCpichRscp,TAF_INT16 *psCpichEcNo)
{
    TAF_UINT32                          ulRslt;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enRadioMode;        /*�ֻ�����ģʽ��ѯ*/
    static VOS_UINT32                   ulFirstInvalidTick = 0;
    VOS_UINT32                          ulTmpTick;

    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrentUtranMode;

    /* Modified by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
    if (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE == TAF_SDC_GetAppServiceStatus())
    /* Modified by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */
    {
        /*��ȡ��ǰ����ģʽ*/
        enRadioMode = TAF_SDC_GetAppSysMode();
        if (TAF_SDC_SYS_MODE_WCDMA == enRadioMode)
        {/* WCDMA */

            /* ȡ�õ�ǰ��UTRANģʽ */
            enCurrentUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

            if ( NAS_UTRANCTRL_UTRAN_MODE_FDD == enCurrentUtranMode )
            {
                ulRslt = WAS_MNTN_QueryCSNR(psCpichRscp,psCpichEcNo);
            }
            else
            {
                *psCpichRscp = RRC_NAS_MEASURE_INVALID_VALUE;
                *psCpichEcNo = MMA_RSCP_MIN;
                ulRslt = TAF_FAILURE;
            }

            /* ����û������б��Ѻ�UE�ڻ�RPLMN�����в�ѯRSCP����ʱWAS��������������
               ������һ����Чֵ�����º�̨��ʾ���źţ������������⴦��:
               ���UE������������״̬����WAS���ص��ź�Ϊ��Чֵ���������ٲ�ѯ��ʹ���ϴ�
               ����Чֵ������������Ȼ������Чֵ������Ϊ���������쳣��������Сֵ */

            if (RRC_NAS_MEASURE_INVALID_VALUE == *psCpichRscp)
            {
                ulTmpTick = VOS_GetSlice();

                if ( 0 == ulFirstInvalidTick )
                {
                    /* ��¼�տ�ʼ��Ч�źŵ� tick, ���ر�����ź�ֵ */
                    ulFirstInvalidTick = ulTmpTick;
                    *psCpichRscp = g_sLastRscp;
                    *psCpichEcNo = g_sLastEcNo;
                }
                else if( TAF_TimeCmp(ulFirstInvalidTick, ulTmpTick, MMA_INVALID_RSCP_SEC_MAX ) )
                {
                    /* 2 ���ڳ�����Ч�ź�, ���ر�����ź�ֵ */
                    *psCpichRscp = g_sLastRscp;
                    *psCpichEcNo = g_sLastEcNo;
                }
                else
                {
                    /* ����2 ��, ������Сֵ */
                    *psCpichRscp = MMA_RSCP_MIN;
                    *psCpichEcNo = MMA_ECNO_MIN;
                }
            }
            else
            {
                /* ����ֵ�򱣴� */
                g_sLastRscp = *psCpichRscp;
                g_sLastEcNo = *psCpichEcNo;
                ulFirstInvalidTick = 0;
            }
        }
        else
        {/* GSM */
            *psCpichRscp = MMA_RSCP_MIN;
            *psCpichEcNo = MMA_ECNO_MIN;

            ulRslt = TAF_SUCCESS;
        }
    }
    else
    {   /* ����������״̬ */
        *psCpichRscp = MMA_RSCP_MIN;
        *psCpichEcNo = MMA_ECNO_MIN;

        ulRslt = TAF_SUCCESS;

        /* �޷����ʱ���ʼ����Ϊ��Сֵ */
        g_sLastRscp = MMA_RSCP_MIN;
        g_sLastEcNo = MMA_ECNO_MIN;
    }



    if(*psCpichRscp > MMA_RSCP_MAX)
    {
        *psCpichRscp = MMA_RSCP_MAX;
    }

    if(*psCpichRscp < MMA_RSCP_MIN)
    {
        *psCpichRscp = MMA_RSCP_MIN;
    }

    if(*psCpichEcNo > MMA_ECNO_MAX)
    {
        *psCpichEcNo = MMA_ECNO_MAX;
    }

    if(*psCpichEcNo < MMA_ECNO_MIN)
    {
        *psCpichEcNo = MMA_ECNO_MIN;
    }

    return ulRslt;
}

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-11, begin */

/* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-4-11, end */

/* Taf_DefGetCardMode */


TAF_UINT32 TAF_GetUsimStatus(TAF_VOID)
{
    return MMA_CheckUsimStatusForPlmnSel();
}



VOS_UINT32 MMA_GetUsimStatusFromUsim(VOS_UINT8 *pucCardStatus,
                                                   VOS_UINT8 *pucCardType)
{
    VOS_UINT32               ulResult;
    VOS_UINT8                aucImsi[9] = {0};

    ulResult = NAS_USIMMAPI_GetCardType(pucCardStatus, pucCardType) ;

    if ((VOS_NULL_PTR == pucCardStatus)
     || (USIMM_CARD_SERVIC_AVAILABLE != *pucCardStatus))
    {
        return ulResult;
    }


    /* ������ȷ�ϣ������ǰ��״̬ΪUSIMM_CARD_SERVIC_AVAILABLE����һ��������IMSI���ļ� */
    if (USIMM_API_SUCCESS != NAS_USIMMAPI_GetCardIMSI(aucImsi))
    {
        return ulResult;
    }

    /* ���IMSI���ȷǷ��������޿�����עTAF_SDC_MAX_IMSI_LEN�����ǰ���������Ϣ�� */
    if (aucImsi[0] >= TAF_SDC_MAX_IMSI_LEN)
    {
        *pucCardStatus = USIMM_CARD_SERVIC_ABSENT;
    }

    return ulResult;
}


VOS_UINT8 MMA_CheckUsimStatusForPlmnSel()
{
    VOS_UINT8                           ucSimStatus = MMA_USIM_ABSENT;
    VOS_UINT8                           ucError    = TAF_ERR_NO_ERROR;

    (VOS_VOID)MMA_PhoneGetUsimStatus(&ucSimStatus);
    if ( MMA_USIM_PRESENT == ucSimStatus )
    {
        /*��Ҫ����PIN��*/
        switch ( MMA_CheckPin1SatusSimple() )
        {
            case MMA_ENABLE_PIN1_NONEED:
            case MMA_NONEED_PIN1:
                ucError = TAF_ERR_NO_ERROR;
                break;
            case MMA_NEED_PIN1:
                ucError = TAF_ERR_NEED_PIN1;
                break;
            case MMA_NEED_PUK1:
                ucError = TAF_ERR_NEED_PUK1;
                break;
            case MMA_PIN1_STATUS_FAIL:
                ucError = TAF_ERR_SIM_FAIL;
                break;
            default:
                ucError = TAF_ERR_UNSPECIFIED_ERROR;
                MMA_WARNINGLOG("MMA_CheckUsimStatusForPlmnSel():WARNING:MEET MYSTERIOUS THING!");
                break;
        }
    }
    else
    {
        ucError = TAF_ERR_USIM_SIM_CARD_NOTEXIST;
    }
    return ucError;
}
VOS_UINT8 MMA_GetCurrentPhoneMode(VOS_VOID)
{
    return TAF_SDC_GetCurPhoneMode();
}

VOS_VOID MMA_ClearEplmnFromNV(VOS_VOID)
{
    NVIM_EQUIVALENT_PLMN_LIST_STRU *pEquivPlmn;
    VOS_UINT16    usTemLen;

    usTemLen = sizeof (NVIM_EQUIVALENT_PLMN_LIST_STRU);
    pEquivPlmn = (NVIM_EQUIVALENT_PLMN_LIST_STRU *)MMC_MEM_ALLOC(
                            VOS_MEMPOOL_INDEX_NAS,
                            usTemLen,
                            WUEPS_MEM_NO_WAIT);                             /* �����ڴ�                                 */
    if (VOS_NULL_PTR == pEquivPlmn)
    {
        TAF_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_ERROR, "MMC_ClearEplmn:ERROR: Memory Alloc Error");
        return;                                                             /* ����                                     */
    }


    if (NV_OK == NV_Read(en_NV_Item_EquivalentPlmn, pEquivPlmn, usTemLen))
    {
        if ( 0 == pEquivPlmn->ucCount )
        {
            MMC_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pEquivPlmn);
            MMA_INFOLOG("MMA_ClearEplmnFromNV():The content to write is same as NV's");

            return;
        }
    }


    /* ��ʼ��EPLMN�ĸ��� */
    PS_MEM_SET(pEquivPlmn, 0, usTemLen);

    if (NV_OK != NV_Write(en_NV_Item_EquivalentPlmn,
                          pEquivPlmn,
                          sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU)))
    {
        TAF_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "MMC_ClearEplmn:WARNING: en_NV_Item_EquivalentPlmn Error");
    }
    MMC_MEM_FREE(VOS_MEMPOOL_INDEX_NAS, pEquivPlmn);

    return;
}
VOS_VOID  Taf_GetSysInfoForSTK(TAF_MMA_LOCATION_STATUS_EVENT_INFO_STRU *pstSysInfo)
{
    pstSysInfo->stPlmn = *(TAF_SDC_GetCurrCampPlmnId());

    pstSysInfo->ulCellId            = TAF_SDC_GetCurrCampCellId();

    pstSysInfo->enServiceStatus     = TAF_MMA_GetSrvTypeForStk();
    pstSysInfo->enSysMode = TAF_SDC_GetSysMode();
    pstSysInfo->usLac     = TAF_SDC_GetCurrCampLac();


    return;
}




TAF_BOOL TAF_IsNormalSrvStatus(VOS_VOID)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsServiceStatus;

    enCsServiceStatus = TAF_SDC_GetCsServiceStatus();
    enPsServiceStatus = TAF_SDC_GetPsServiceStatus();

    if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enCsServiceStatus )
     && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enPsServiceStatus) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#if (VOS_WIN32 == VOS_OS_VER)
/*****************************************************************************
 �� �� ��  : NAS_MMA_SndNVData
 ��������  : ��ps��ص�nv���͸�OM���Ա�ط�ʹ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��6��
    ��    ��   : ���� 59430
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMA_SndNVData(VOS_VOID)
{
    /* Absolute Path for Operating NV file */
    extern const VOS_CHAR g_aucNvFolderPath[]; /* NV Folder path */

    const VOS_CHAR aucNvimCtrlFile[]   = "NvimCtrl.bin";
    const VOS_CHAR aucNvimAuthFile[]   = "NvimAuth.bin";
    const VOS_CHAR aucSYSNVTableFile[] = "SYSNVTable.bin";
    const VOS_CHAR aucPSNVTableFile[]  = "PSNVTable.bin";
    const VOS_CHAR aucRFNVTableFile[]  = "RFNVTable.bin";
    const VOS_CHAR aucCODECNVTableFile[]  = "CODECNVTable.bin";
    const VOS_CHAR aucCFDNVTableFile[]  = "CFDNVTable.bin";

    NAS_MMA_SndNVFileData(g_aucNvFolderPath , aucNvimCtrlFile);
    NAS_MMA_SndNVFileData(g_aucNvFolderPath , aucNvimAuthFile);
    NAS_MMA_SndNVFileData(g_aucNvFolderPath , aucSYSNVTableFile);
    NAS_MMA_SndNVFileData(g_aucNvFolderPath , aucPSNVTableFile);
    NAS_MMA_SndNVFileData(g_aucNvFolderPath , aucRFNVTableFile);
    NAS_MMA_SndNVFileData(g_aucNvFolderPath , aucCODECNVTableFile);
    NAS_MMA_SndNVFileData(g_aucNvFolderPath , aucCFDNVTableFile);

    return;
}
/*****************************************************************************
 �� �� ��  : NAS_MMA_SndNVFileData
 ��������  : ��ָ��NV���͸�OM
 �������  : aucFileName NV�ļ�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��6��
    ��    ��   : ���� 59430
    �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32 NAS_MMA_SndNVFileData(const VOS_CHAR * aucNVFolder ,const VOS_CHAR * aucFileName)
{
    VOS_CHAR                                   *paucNvFilePath = VOS_NULL_PTR;
    VOS_UINT32                                  ulNvFilePathLen;
    FILE *                                      fp = VOS_NULL_PTR;
    VOS_UINT32                                  ulFileSize;
    VOS_UINT32                                  ulReadSize;
    VOS_UINT32                                  ulReadCount;
    VOS_UINT32                                  ulReadTotaldSize;
    VOS_UINT32                                  ulPacketLen;
    NAS_MMA_NV_MSG_ST                          *pNvMsgCB     = VOS_NULL_PTR;



#if (VOS_OS_VER == VOS_VXWORKS)
    ulNvFilePathLen = VOS_StrLen((VOS_CHAR *)aucNVFolder) + VOS_StrLen("/") + VOS_StrLen((VOS_CHAR *)aucFileName);
    paucNvFilePath = (VOS_CHAR *)PS_MEM_ALLOC(WUEPS_PID_MMA, ulNvFilePathLen + 1);

    if ( VOS_NULL_PTR == paucNvFilePath )
    {
        MMA_ERRORLOG("NAS_MMA_SndNVData:ERROR: Alloc Memory Fail.");
        return MMA_ERROR;
    }

    (VOS_VOID)VOS_sprintf(paucNvFilePath , "%s/%s" , aucNVFolder , aucFileName);
#elif( (VOS_WIN32 == VOS_OS_VER) ||  (defined __PS_WIN32_RECUR__) )
    ulNvFilePathLen = VOS_StrLen((VOS_CHAR *)aucNVFolder) + VOS_StrLen((VOS_CHAR *)aucFileName);
    paucNvFilePath = (VOS_CHAR *)PS_MEM_ALLOC(WUEPS_PID_MMA, ulNvFilePathLen + 1);

    if ( VOS_NULL_PTR == paucNvFilePath )
    {
        MMA_ERRORLOG("NAS_MMA_SndNVData:ERROR: Alloc Memory Fail.");
        return MMA_ERROR;
    }

    (VOS_VOID)VOS_sprintf(paucNvFilePath , "%s" , aucFileName);
#endif


    /*��ֻ���ķ�ʽ���ļ�*/
    fp = NV_File_Open((VOS_CHAR*)paucNvFilePath, NV_FILE_OPEN_MODE_R);

    /*�����ȡNV file ����ʧ��*/
    if ( VOS_NULL_PTR == fp )
    {
        PS_MEM_FREE(WUEPS_PID_MMA, paucNvFilePath);
        return MMA_ERROR;
    }

    /*��ȡ�ļ�����*/
    NV_File_Seek(fp, 0, NV_FILE_SEEK_END);
    ulFileSize = (VOS_UINT32)NV_File_Tell(fp);

    /* ��ʱ��������PS NV�ļ�����0xFFFF,OM�������ݵĵĳ�������δUNSIGNED SHORT���ͣ������޷����� */
    if (ulFileSize > 0xe000 )
    {
        ulPacketLen = 0xe000;
    }
    else
    {
        ulPacketLen = ulFileSize;
    }

    /* ָ���ļ���ͷ */
    NV_File_Seek(fp, 0, NV_FILE_SEEK_SET);

    /*��ȡNV file ���ȳɹ�*/
    pNvMsgCB = (NAS_MMA_NV_MSG_ST *)PS_ALLOC_MSG(WUEPS_PID_MMA, sizeof(NAS_MMA_NV_MSG_ST) + ulPacketLen);
    if ( VOS_NULL_PTR == pNvMsgCB )
    {
        MMA_ERRORLOG("NAS_MMA_SndNVData:ERROR: Alloc Memory Fail.");

        NV_File_Close(fp);

        PS_MEM_FREE(WUEPS_PID_MMA, paucNvFilePath);
        paucNvFilePath = VOS_NULL_PTR;

        return MMA_ERROR;
    }

    /*������Ϣͷ��*/
    pNvMsgCB->ulReceiverPid   = WUEPS_PID_MMA;
    pNvMsgCB->ulSenderPid     = WUEPS_PID_MMA;
    pNvMsgCB->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pNvMsgCB->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pNvMsgCB->ulLength        = sizeof(NAS_MMA_NV_CONTEXT_ST) + 4 + ulPacketLen;
    pNvMsgCB->usMsgID         = EVT_NAS_MMA_NV_CONTEXT;

    /*NV�ļ���*/
    (VOS_VOID)VOS_StrCpy((VOS_CHAR *)pNvMsgCB->stNVCtxt.auNvFileName , (VOS_CHAR *)aucFileName);

    /*�ļ�����*/
    pNvMsgCB->stNVCtxt.ulNvFileLen = ulFileSize;
    pNvMsgCB->stNVCtxt.ulPacketLen = ulPacketLen;

    /*��ȡ�ļ�����*/
    ulReadCount = 0;
    ulReadSize = 0;
    ulReadTotaldSize = 0;
    do
    {
        if( ( ulPacketLen - ulReadTotaldSize ) >= 4096)
        {
            ulReadSize = 4096;

        }
        else
        {
            ulReadSize = ulPacketLen - ulReadTotaldSize ;

        }

        ulReadCount = (VOS_UINT32)NV_File_Read(
                              (VOS_CHAR*)(pNvMsgCB->stNVCtxt.auNvFileData + ulReadTotaldSize),
                              ulReadSize ,
                              1,
                              fp);

        if (ulReadSize != ulReadCount)
        {
            MMA_ERRORLOG("NAS_MMA_SndNVData:ERROR: NV_File_Read Fail.");
            break;
        }

        ulReadTotaldSize += ulReadSize;

    }while(ulReadTotaldSize < ulPacketLen);

    /*������ļ��ɹ�*/
    if(ulReadTotaldSize == ulPacketLen)
    {
        /*������Ϣ*/
        DIAG_TraceReport(pNvMsgCB);
    }

    if ( ulFileSize > ulPacketLen)
    {
        /* ��ʱ�����ļ�̫��OM���Ͳ��ˣ�OM���ݳ�������ΪUNSIGNED SHORT�����Ըô�������������� */
        ulPacketLen = ulFileSize - 0xe000;
        /*������Ϣͷ��*/
        pNvMsgCB->ulReceiverPid   = WUEPS_PID_MMA;
        pNvMsgCB->ulSenderPid     = WUEPS_PID_MMA;
        pNvMsgCB->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pNvMsgCB->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pNvMsgCB->ulLength        = sizeof(NAS_MMA_NV_CONTEXT_ST) + 4 + ulPacketLen;
        pNvMsgCB->usMsgID         = EVT_NAS_MMA_NV_CONTEXT;

        /*NV�ļ���*/
        (VOS_VOID)VOS_StrCpy((VOS_CHAR *)pNvMsgCB->stNVCtxt.auNvFileName , (VOS_CHAR *)aucFileName);

        /*�ļ�����*/
        pNvMsgCB->stNVCtxt.ulNvFileLen = ulFileSize;
        pNvMsgCB->stNVCtxt.ulPacketLen = ulPacketLen;

        /*��ȡ�ļ�����*/
        ulReadCount = 0;
        ulReadSize = 0;
        ulReadTotaldSize = 0;
        do
        {
            if( ( ulPacketLen - ulReadTotaldSize ) >= 4096)
            {
                ulReadSize = 4096;
            }
            else
            {
                ulReadSize = ulPacketLen - ulReadTotaldSize ;
            }

            ulReadCount = (VOS_UINT32)NV_File_Read(
                                    (VOS_CHAR*)(pNvMsgCB->stNVCtxt.auNvFileData + ulReadTotaldSize),
                                                ulReadSize ,
                                                1,
                                                fp);

            if (ulReadSize != ulReadCount)
            {
                MMA_ERRORLOG("NAS_MMA_SndNVData:ERROR: NV_File_Read Fail.");
                break;
            }

            ulReadTotaldSize += ulReadSize;

        }while(ulReadTotaldSize < ulPacketLen);

        /*������ļ��ɹ�*/
        if(ulReadTotaldSize == ulPacketLen)
        {
            /*������Ϣ*/
            DIAG_TraceReport(pNvMsgCB);
        }
    }

    /*�ر��ļ�*/
    NV_File_Close(fp);

    /*�ͷ��ڴ�*/
    PS_MEM_FREE(WUEPS_PID_MMA, paucNvFilePath);
    paucNvFilePath = VOS_NULL_PTR;
    PS_FREE_MSG(WUEPS_PID_MMA, pNvMsgCB);
    pNvMsgCB = VOS_NULL_PTR;

    return MMA_SUCCESS;
}

#endif





VOS_VOID MN_PH_ResetTimerOutProc( VOS_VOID  )
{
    VOS_UINT32                          ulRslt;

    ulRslt = NAS_StopRelTimer(WUEPS_PID_MMA, TI_MN_PH_RESET, &g_stPhPhResetTimer.MmaHTimer);
    if (VOS_OK != ulRslt)
    {
        MMA_ERRORLOG("MN_PH_ResetTimerOutProc:ERROR:NAS_StopRelTimer failed.");
    }

    /* ʹ�ô˽ӿڣ���ֹAT�������λ����dump�ļ� */
    mdrv_sysboot_shutdown(DRV_SHUTDOWN_RESET);

}
VOS_VOID MN_PH_PinOperTimerOutProc( VOS_VOID )
{
    TAF_PHONE_EVENT_INFO_STRU           *pstPhoneEvent;
    VOS_UINT32                          ulRslt;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                                              sizeof(TAF_PHONE_EVENT_INFO_STRU));
    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MMA_ERRORLOG("MN_PH_PinOperTimerOutProc:ERROR:ALLOC MEMORY FAIL.");
        return;
    }
    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    ulRslt = NAS_StopRelTimer(WUEPS_PID_MMA, TI_MN_PH_PIN_OPER, &g_stPhPinOperTimer.MmaHTimer);
    if (VOS_OK != ulRslt)
    {
        MMA_ERRORLOG("MN_PH_PinOperTimerOutProc:ERROR:NAS_StopRelTimer FAIL.");
    }
    g_stPhPhResetTimer.ucTimerStatus = MMA_TIMER_STOP;

    MMA_InitEventInfoOP(pstPhoneEvent);

    /*����TAF�¼��ϱ�����,�ϱ�PIN�¼�*/
    pstPhoneEvent->OP_Pin                    = VOS_TRUE;
    pstPhoneEvent->PhoneEvent                = TAF_PH_EVT_OP_PIN_CNF;
    PS_MEM_CPY(&pstPhoneEvent->PinCnf,&g_stPhPinCnf,sizeof(g_stPhPinCnf));
    pstPhoneEvent->PinCnf.OpPinResult = TAF_PH_OP_PIN_OK;

    Taf_PhoneEvent(pstPhoneEvent);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

    /* MMA_SendPINOk(); */
}


NAS_OM_REGISTER_STATE_ENUM_UINT8 NAS_GetRegisterState(VOS_VOID)
{
    NAS_OM_REGISTER_STATE_ENUM_UINT8    ucRegisterState;

    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    enSysMode = TAF_SDC_GetAppSysMode();

    ucRegisterState = NAS_OM_REGISTER_STATE_BUTT;

    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        ucRegisterState = NAS_OM_REGISTER_STATE_POWEROFF;
    }
    else
    {
        /* Modified by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
        if (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE == TAF_SDC_GetAppServiceStatus())
        /* Modified by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */
        {
            if (TAF_SDC_SYS_MODE_GSM == enSysMode)
            {
                ucRegisterState = NAS_OM_REGISTER_STATE_REGISTER_2G;
            }
            else if (TAF_SDC_SYS_MODE_WCDMA == enSysMode)
            {
                ucRegisterState = NAS_OM_REGISTER_STATE_REGISTER_3G;
            }
            else if (TAF_SDC_SYS_MODE_LTE == enSysMode)
            {
                ucRegisterState = NAS_OM_REGISTER_STATE_REGISTER_4G;
            }
            else
            {
                ucRegisterState = NAS_OM_REGISTER_STATE_NOT_REGISTER;
            }
        }
        else
        {
            ucRegisterState = NAS_OM_REGISTER_STATE_NOT_REGISTER;
        }
    }

    return ucRegisterState;
}


NAS_OM_SERVICE_TYPE_ENUM_UINT8   NAS_GetServiceType(VOS_VOID)
{
    NAS_OM_SERVICE_TYPE_ENUM_UINT8  ucServiceType;

    TAF_SDC_SYS_MODE_ENUM_UINT8     enSysMode;

    enSysMode = TAF_SDC_GetAppSysMode();

    ucServiceType = NAS_OM_SERVICE_TYPE_BUTT;

    if (TAF_SDC_SYS_MODE_GSM == enSysMode)
    {
        if (TAF_APS_USER_CONN_EXIST == TAF_APS_GetUserConnStatus())
        {
            /* ��ǰ��G�� */
            ucServiceType = NAS_OM_SERVICE_TYPE_GSM;
        }
        else
        {
            ucServiceType = NAS_OM_SERVICE_TYPE_NO_SERVICE;
        }
    }
    else if (TAF_SDC_SYS_MODE_WCDMA == enSysMode)
    {
        if (TAF_APS_USER_CONN_EXIST == TAF_APS_GetUserConnStatus())
        {
            /* ��ǰ��W�� */
            switch (g_StatusContext.ucDataTranMode)
            {
                case STA_DATA_TRANSFER_R99_ONLY:
                    ucServiceType = NAS_OM_SERVICE_TYPE_WCDMA;
                    break;
                case STA_DATA_TRANSFER_HSDPA:
                case STA_DATA_TRANSFER_HSUPA:
                case STA_DATA_TRANSFER_HSDPA_AND_HSUPA:
                case STA_DATA_TRANSFER_HSPA_PLUS:
                case STA_DATA_TRANSFER_DC_HSPA_PLUS:
                case STA_DATA_TRANSFER_DC_MIMO:
                    ucServiceType = NAS_OM_SERVICE_TYPE_HSPA;
                    break;
                default:
                    ucServiceType = NAS_OM_SERVICE_TYPE_WCDMA;
                    break;
            }
        }
        else
        {
            ucServiceType = NAS_OM_SERVICE_TYPE_NO_SERVICE;
        }
    }
    else if (TAF_SDC_SYS_MODE_LTE == enSysMode)
    {
        if ( STA_DATA_TRANSFER_LTE_DATA == g_StatusContext.ucDataTranMode )
        {
            ucServiceType = NAS_OM_SERVICE_TYPE_LTE;
        }
        else
        {
            ucServiceType = NAS_OM_SERVICE_TYPE_NO_SERVICE;
        }
    }
    else
    {
        ucServiceType = NAS_OM_SERVICE_TYPE_NO_SERVICE;
    }



    return ucServiceType;
}


VOS_VOID NAS_MMA_TransferSysSubMode2ActForAtCmdCreg(
    VOS_UINT8                           ucSysSubMode,
    TAF_PH_ACCESS_TECH_ENUM_UINT8      *pucAct
)
{
    switch (ucSysSubMode)
    {
        case TAF_SYS_SUBMODE_GSM:
            *pucAct = TAF_PH_ACCESS_TECH_GSM;
            break;
        case TAF_SYS_SUBMODE_GPRS:
            *pucAct = TAF_PH_ACCESS_TECH_GSM;
            break;
        case TAF_SYS_SUBMODE_EDGE:
            *pucAct = TAF_PH_ACCESS_TECH_EGPRS;
            break;
        case TAF_SYS_SUBMODE_WCDMA:
            *pucAct = TAF_PH_ACCESS_TECH_UTRAN;
            break;
        case TAF_SYS_SUBMODE_HSDPA:
            *pucAct = TAF_PH_ACCESS_TECH_HSDPA;
            break;
        case TAF_SYS_SUBMODE_HSUPA:
            *pucAct = TAF_PH_ACCESS_TECH_HSUPA;
            break;
        case TAF_SYS_SUBMODE_HSDPA_HSUPA:
            *pucAct = TAF_PH_ACCESS_TECH_HSDPA_HSUPA;
            break;

        /* 27007Э��10.1.20:
          <AcT>: a numeric parameter that indicates the access technology of the serving cell
          0   GSM
          1   GSM Compact
          2   UTRAN
          3   GSM w/EGPRS (see NOTE 2)
          4   UTRAN w/HSDPA (see NOTE 3)
          5   UTRAN w/HSUPA (see NOTE 3)
          6   UTRAN w/HSDPA and HSUPA (see NOTE 3)
          7   E-UTRAN
          NOTE 2: 3GPP TS 44.060 [71] specifies the System Information messages which give the information about whether the serving cell supports EGPRS.
          NOTE 3: 3GPP TS 25.331 [74] specifies the System Information blocks which give the information about whether the serving cell supports HSDPA or HSUPA.
          Э��δ��HSPA+����ȷ˵����Ŀǰ��6UTRAN w/HSDPA and HSUPA�ϱ�
        */

        case TAF_SYS_SUBMODE_HSPA_PLUS:
        case TAF_SYS_SUBMODE_DC_HSPA_PLUS:
        case TAF_SYS_SUBMODE_DC_MIMO:
            *pucAct = TAF_PH_ACCESS_TECH_HSDPA_HSUPA;
            break;

        case TAF_SYS_SUBMODE_LTE:
            *pucAct = TAF_PH_ACCESS_TECH_E_UTRAN;
            break;

        default:
            *pucAct = TAF_PH_ACCESS_TECH_BUTT;
            break;
    }

    return;
}


VOS_BOOL NAS_MMA_CellIdChangeForStkLocSta()
{
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId;
    VOS_UINT32                          ulCellId;
    VOS_UINT16                          usLac;

    pstPlmnId = TAF_SDC_GetCurrCampPlmnId();
    usLac     = TAF_SDC_GetCurrCampLac();
    ulCellId  = TAF_SDC_GetCurrCampCellId();

    if ((g_stMmsStkLocStaSysInfo.stPlmn.ulMcc != pstPlmnId->ulMcc)
     || (g_stMmsStkLocStaSysInfo.stPlmn.ulMnc != pstPlmnId->ulMnc)
     || (g_stMmsStkLocStaSysInfo.usLac != usLac)
     || (g_stMmsStkLocStaSysInfo.ulCellId != ulCellId))
    {
       return VOS_TRUE;
    }

    return VOS_FALSE;
}



NAS_STK_SERVICE_STATUS_ENUM_UINT8 NAS_MMA_ConvertSdcServStaToStkServSta(
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enSdcSrvSta
)
{
    switch (enSdcSrvSta)
    {
        case TAF_SDC_REPORT_SRVSTA_NO_SERVICE:
             return NAS_STK_SERVICE_STATUS_NO_SERVICE;

        case TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE:
             return NAS_STK_SERVICE_STATUS_LIMITED_SERVICE;

        case TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE:
             return NAS_STK_SERVICE_STATUS_NORMAL_SERVICE;

        case TAF_SDC_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE:
             return NAS_STK_SERVICE_STATUS_LIMITED_SERVICE_REGION;

        case TAF_SDC_REPORT_SRVSTA_DEEP_SLEEP:
             return NAS_STK_SERVICE_STATUS_DEEP_SLEEP;

        default:
            MN_ERR_LOG("NAS_MMA_ConvertSdcServStaToStkServSta: The input is invalid");
            return NAS_STK_SERVICE_STATUS_BUTT;
    }

}




VOS_VOID NAS_MMA_SndStkLociStatusEvent(VOS_VOID)
{
    NAS_STK_LOC_STATUS_EVENT_STRU      *pstMsg        = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;
    TAF_SDC_PLMN_ID_STRU               *pstTempPlmnID = VOS_NULL_PTR;

    /* �����ڴ� */
    ulLength = sizeof(NAS_STK_LOC_STATUS_EVENT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (NAS_STK_LOC_STATUS_EVENT_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("TAF_MMA_UpdateStkLociStatusEvent: Alloc Msg");
        return;
    }

    PS_MEM_SET(&(pstMsg->stLocStatusEvent), 0, sizeof(NAS_STK_LOC_STATUS_EVENT_INFO_STRU));

    /* ��д����Ϣ���� */
    pstMsg->ulMsgId                            = ID_NAS_STK_LOC_STATUS_EVENT;

    pstMsg->ulReceiverPid                      = NAS_GetOamReceivePid(MAPS_STK_PID);

    pstTempPlmnID                              = TAF_SDC_GetCurrCampPlmnId();
    pstMsg->stLocStatusEvent.stPlmn.Mcc        = pstTempPlmnID->ulMcc;
    pstMsg->stLocStatusEvent.stPlmn.Mnc        = pstTempPlmnID->ulMnc;

    pstMsg->stLocStatusEvent.enRat             = TAF_SDC_GetSysMode();

    pstMsg->stLocStatusEvent.enServiceStatus   = NAS_MMA_ConvertSdcServStaToStkServSta(TAF_SDC_GetServiceStatus());

    pstMsg->stLocStatusEvent.ulCellId          = TAF_SDC_GetCurrCampCellId();

    pstMsg->stLocStatusEvent.usLac             = TAF_SDC_GetCurrCampLac();

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG( WUEPS_PID_MMA, pstMsg))
    {
        MN_ERR_LOG("TAF_MMA_UpdateStkLociStatusEvent: PS_SEND_MSG ERROR");
    }

    return;

}



VOS_VOID NAS_MMA_ReportLociStatus(VOS_VOID)
{
    /* ����SVLTE������Modem������û�б�Ҫ�����ƶ�ȷ�Ϲ���ֻ��ҪCS ����Modem���¼��ɡ�
       MMA�ڵ���ǰ�ж��£�SVLTE��̬�£����û��CS���������Ͳ����á�*/
    if (VOS_TRUE == TAF_MMA_IsNeedSndStkEvt())
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_LOCATION_STATUS_EVENT, VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);
#ifndef __PS_WIN32_RECUR__

        NAS_MMA_SndStkLociStatusEvent();

        Taf_GetSysInfoForSTK(&g_stMmsStkLocStaSysInfo);

        gstMmaValue.pg_StatusContext->ucIsReportedLocStatus = VOS_TRUE;
#endif
    }

    return;
}
VOS_UINT32 MN_PH_QryApHplmn(
    VOS_UINT32                          *pulMcc,
    VOS_UINT32                          *pulMnc
)
{
    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;

    pucImsi = TAF_SDC_GetSimImsi();

    if (MMA_SIM_IS_LOCK == g_stMmaMePersonalisationStatus.SimLockStatus)
    {
        MN_WARN_LOG("MN_PH_QryApHplmn:ERROR:SIM LOCKED.");
        return VOS_ERR;
    }

    /* ��ȡMMC��HPlmn */
    if (USIMM_API_SUCCESS != NAS_USIMMAPI_GetCardIMSI(pucImsi))
    {
        MN_ERR_LOG("MN_PH_QryApHplmn:ERROR:GET IMSI FAIL.");
        return VOS_ERR;
    }

    *pulMcc = 0;
    *pulMnc = 0;

    *pulMcc |= (pucImsi[1] & 0xF0) >> 4;
    *pulMcc |= (pucImsi[2] & 0x0F) << 8;
    *pulMcc |= (pucImsi[2] & 0xF0) << 12;
    *pulMnc |= (pucImsi[3] & 0x0F);
    *pulMnc |= (pucImsi[3] & 0xF0) << 4;
    *pulMnc |= (pucImsi[4] & 0x0F) << 16;


    return VOS_OK;
}
VOS_UINT32 MN_PH_QryAnQuery(
    VOS_INT16                           *psCpichRscp,
    VOS_INT16                           *psCpichEcNo,
    VOS_UINT8                           *pucRssi,
    VOS_UINT32                          *pulCellId
)
{
    VOS_UINT32                          ulResult;

    VOS_INT32                           lRssiValue;

    /* ����Taf_QueryCSNR����ȡrscp, ecio��ֵ */
    ulResult =  Taf_QueryCSNR(psCpichRscp,psCpichEcNo);
    if(TAF_SUCCESS != ulResult)
    {
        return VOS_ERR;
    }

    /* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, begin */
    if (TAF_SDC_SYS_MODE_GSM == TAF_SDC_GetAppSysMode())
    {
        lRssiValue = TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stRssiValue.u.st2GCellSignInfo.sRssiValue;
    }
    else
    {
        lRssiValue = TAF_SDC_GetSdcCtx()->stAppNetworkInfo.stRssiValue.u.st3GCellSignInfo.sRscpValue;
    }
    /* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, end */

    MMA_GetRssiLevelFromValue(lRssiValue, pucRssi);

    /* �޷���״̬ʱ����RSSI��Ϊ���ɲ�99 */
    /* Modified by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
    if ( TAF_REPORT_SRVSTA_NO_SERVICE == TAF_SDC_GetAppServiceStatus() )
    /* Modified by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */
    {
        *pucRssi = MMA_RSSI_INVALID;
    }

    /* ���ú���Api_MmaGetParaFromMscc��ȡmscc�еĵ�ǰפ����CellId��ֵ */
    *pulCellId  = TAF_SDC_GetAppCampCellId();

    /* �ϱ�����ת��:�� Rscp��Ecio��ʾΪ�Ǹ�ֵ����Rscp��EcioΪ-145��-32������rssiΪ99����ת��Ϊ0 */
    if ( ((MMA_RSCP_MIN == (*psCpichRscp)) && (MMA_ECNO_MIN == (*psCpichEcNo)))
      || (MMA_RSSI_INVALID == (*pucRssi)) )
    {
        (*psCpichRscp) = 0;
        (*psCpichEcNo) = 0;
        (*pulCellId)   = 0xFFFFFFFF;
    }


    return VOS_OK;
}


VOS_VOID NAS_MMA_OutputUsimInfo(NAS_MNTN_USIM_INFO_STRU *pstUsimInfo)
{
    VOS_UINT32                          ulRet;
    NAS_MML_PLMN_ID_STRU                stRplmn;

    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;

    pucImsi = TAF_SDC_GetSimImsi();

    stRplmn.ulMcc = MMA_INVALID_MCC;
    stRplmn.ulMnc = MMA_INVALID_MNC;

    ulRet = NAS_USIMMAPI_GetCardType(&pstUsimInfo->ucCardStatus,
                              &pstUsimInfo->ucCardType);

    if (USIMM_API_SUCCESS != ulRet)
    {
        MN_WARN_LOG("NAS_MMA_OutputUsimInfo: Fail to get (U)SIM information.");
        return;
    }

    /* ���ٿ������޿���������Ϣ��Ҫ��ȡ��ֱ�ӷ��� */
    if ((USIMM_CARD_ROM_SIM       == pstUsimInfo->ucCardType)
     || (USIMM_CARD_SERVIC_ABSENT == pstUsimInfo->ucCardStatus))
    {
        return;
    }

    /* ��ȡ����PIN������״̬
    #define TAF_ERR_NO_ERROR                   (0)  �ɹ�
    #define TAF_ERR_NEED_PIN1                 (18)  ��Ҫ����PIN1��
    #define TAF_ERR_NEED_PUK1                 (19)  ��Ҫ����PUK1
    #define TAF_ERR_SIM_FAIL                  (24)  SIM������ʧ��
    #define TAF_ERR_UNSPECIFIED_ERROR         (50)  ������������
    */
    pstUsimInfo->ucPinStatus = MMA_CheckUsimStatusForPlmnSel();

    if (TAF_ERR_NO_ERROR == pstUsimInfo->ucPinStatus)
    {
        PS_MEM_CPY(pstUsimInfo->aucImsi, pucImsi, NAS_MNTN_IMSI_LENGTH_IN_USIM);

        if (VOS_TRUE != NAS_MML_GetGURPlmn(&stRplmn))
        {
            MN_WARN_LOG("NAS_MMA_OutputUsimInfo(): Warning:NAS_MML_GetGURPlmn failed.");
        }

        pstUsimInfo->stRplmn.ulMcc = stRplmn.ulMcc;
        pstUsimInfo->stRplmn.ulMnc = stRplmn.ulMnc;
    }

    return;
}


VOS_VOID NAS_MMA_OutputPlmnSrchBand(VOS_UINT32 *pulBand)
{
    /* BAND���ã�gstMmaValue.uUserSetBand */
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *pstLastSyscfgSet = VOS_NULL_PTR;

    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();
    *pulBand = pstLastSyscfgSet->stUserSetBand.uUserSetGuBand.ulPrefBand;
    return;
}
VOS_VOID MN_PH_SimLockedRpt( VOS_VOID  )
{
    TAF_PHONE_EVENT_INFO_STRU           *pstPhoneEvent;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                        sizeof(TAF_PHONE_EVENT_INFO_STRU));
    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MN_ERR_LOG("MN_PH_PinOperTimerOutProc:ERROR:ALLOC MEMORY FAIL.");
        return ;
    }
    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    MMA_InitEventInfoOP(pstPhoneEvent);

    /*����TAF�¼��ϱ�����,�ϱ������¼�*/
    pstPhoneEvent->PhoneEvent                = MN_PH_EVT_SIMLOCKED_IND;
    Taf_PhoneEvent(pstPhoneEvent);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

}

VOS_UINT8 APP_MN_PH_AppQryPhMode (VOS_VOID)
{
    return TAF_SDC_GetCurPhoneMode();
}
VOS_VOID MN_PH_RoamingRpt( VOS_UINT8 ucTmpRoamStatus )
{
    TAF_PHONE_EVENT_INFO_STRU           *pstPhoneEvent;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                        sizeof(TAF_PHONE_EVENT_INFO_STRU));
    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        MN_ERR_LOG("MN_PH_RoamingRpt:ERROR:ALLOC MEMORY FAIL.");
        return ;
    }
    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    MMA_InitEventInfoOP(pstPhoneEvent);

    /*����TAF�¼��ϱ�����,�ϱ������¼�*/
    pstPhoneEvent->PhoneEvent                = MN_PH_EVT_ROAMING_IND;
    pstPhoneEvent->ucRoamStatus              = ucTmpRoamStatus;
    Taf_PhoneEvent(pstPhoneEvent);

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

}
VOS_UINT8 NAS_MMA_GetPhoneMode(VOS_VOID)
{
    return TAF_SDC_GetCurPhoneMode();
}


VOS_UINT8 MN_MMA_GetServiceDomain(VOS_VOID)
{
    /* Modified by h00313353 for Iteration 13, 2015-4-9, begin */
    return TAF_MMA_GetLastSyscfgSetAddr()->enSrvDomain;
    /* Modified by h00313353 for Iteration 13, 2015-4-9, end */
}


/* MMA_SndTafMsccPlmnSrchReq() ����MmaSndMscc.c��*/

VOS_UINT8 MN_MMA_GetRoamingBrokerFlg(VOS_VOID)
{
    return gstMmaValue.ucRoamBrokerSwitch;
}


VOS_UINT32 MN_MMA_IsSpecRatSupported(
    TAF_MMA_RAT_TYPE_ENUM_UINT8          enSpecRat
)
{
    VOS_UINT32                          i;
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList = VOS_NULL_PTR;

    pstRatPrioList     = TAF_MMA_GetRatPrioListAddr();

    /* ���GSM��ֹ����,����Ϊ��֧��GSM */
    if ((VOS_TRUE == MMA_IsGsmForbidden())
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
     && (TAF_MMA_RAT_GSM == enSpecRat))
    {
        return VOS_FALSE;
    }

    /* ָ���Ľ��뼼���Ƿ��ڵ�ǰ�û����õ�RAT�б��� */
    for (i = 0 ; i < pstRatPrioList->ucRatOrderNum; i++)
    {
        if ((enSpecRat == pstRatPrioList->aenRatOrder[i])
         && (enSpecRat < TAF_MMA_RAT_BUTT))
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

VOS_UINT32 MN_MMA_IsSpecRatInRatList(
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enSpecRat,
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList
)
{
    VOS_UINT32                          i;

    /* ָ���Ľ��뼼���Ƿ���pstRatPrioList�� */
    for (i = 0 ; i < pstRatPrioList->ucRatOrderNum; i++)
    {
        if ((enSpecRat == pstRatPrioList->aenRatOrder[i])
        /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
         && (enSpecRat < TAF_MMA_RAT_BUTT))
        /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
TAF_MMA_RAT_TYPE_ENUM_UINT8 MN_MMA_GetUserPlmnSelPrioRat(
    TAF_MMA_RAT_TYPE_ENUM_UINT8          enPhRat,
/* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    TAF_PLMN_ID_STRU                    stPlmn
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    TAF_MMA_RAT_ORDER_STRU              stRatPrioList;
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList = VOS_NULL_PTR;

    pstRatPrioList     = TAF_MMA_GetRatPrioListAddr();

    /* ����û�ָ���Ľ��뼼����ǰ֧��,�����������û�ָ���Ľ��뼼�� */
    if (VOS_TRUE == MN_MMA_IsSpecRatSupported(enPhRat))
    {
        return enPhRat;
    }

    stRatPrioList.ucRatOrderNum = 0x0;

    /* ��MMA�ϱ���PLMN�б��в���ָ��������,����ҵ�������Ӧ�Ľ��뼼������ */
    for (i = 0; i < g_StatusContext.PlmnList.ucPlmnNum; i++)
    {
        /* �Ƚ��û�ָ�����������б��б��������,�����û���ֱ�Ӵ��ϱ����б���ѡ�������,��˿���ֱ�ӱȽ� */
        if ((stPlmn.Mcc == g_StatusContext.PlmnList.Plmn[i].Mcc)
         && (stPlmn.Mnc == g_StatusContext.PlmnList.Plmn[i].Mnc))
        {
            stRatPrioList.aenRatOrder[stRatPrioList.ucRatOrderNum] =
                g_StatusContext.PlmnList.PlmnInfo[i].RaMode;

            stRatPrioList.ucRatOrderNum++;
        }

        /* ����Խ�� */
        if (stRatPrioList.ucRatOrderNum >= TAF_PH_MAX_GUL_RAT_NUM)
        {
            break;
        }
    }

    /* �û�ָ���Ľ��뼼����ǰ��֧��,����б��а����û�ָ��������,�򷵻ش��ڽ��뼼����������ȼ��Ľ��뼼�� */
    for (i = 0; i < pstRatPrioList->ucRatOrderNum; i++)
    {
        for (j = 0; j < stRatPrioList.ucRatOrderNum; j++)
        {
            if (pstRatPrioList->aenRatOrder[i] == stRatPrioList.aenRatOrder[j])
            {
                return pstRatPrioList->aenRatOrder[i];
            }
        }
    }

    if ((VOS_TRUE == MMA_IsGsmForbidden())
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
     && (TAF_MMA_RAT_GSM == pstRatPrioList->aenRatOrder[0]))
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    {
        /* �û�ָ���Ľ��뼼����ǰ��֧��,�����б���Ҳû���û�ָ��������,
           ������ȼ�ΪGSM���ҵ�ǰGSM�����ֹ,��ʱ������ΪGSM��ģ(SYSCFG�ᱣ֤),
           ���شθ����ȼ����뼼�� */
        return pstRatPrioList->aenRatOrder[1];
    }

    /* �û�ָ���Ľ��뼼����ǰ��֧��,�����б���Ҳû���û�ָ��������,
       �����û����õ������Ƚ��뼼�� */
    return pstRatPrioList->aenRatOrder[0];
}


VOS_VOID MMA_HomePlmnProc(VOS_UINT16 ClientId, VOS_UINT8 OpId)
{
    VOS_UINT32 ulRet;
    VOS_UINT8 ucSimStatus;
    /* Modified by h00313353 for iteration 9, 2015-2-3, begin */
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;
    VOS_UINT16                          usFileId;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;

    enSimType   = TAF_SDC_GetSimType();
    usFileId    = USIMM_DEF_FILEID_BUTT;
    PS_MEM_SET(&stGetFileInfo, 0x00, sizeof(stGetFileInfo));
    /* Modified by h00313353 for iteration 9, 2015-2-3, end */

    if(MMA_TIMER_STOP != gstMmaInternalTimer.stTimer.ucTimerStatus)
    {
        MMA_WARNINGLOG("MMA_HomePlmnProc():WARNING:USIM is not Ready!");

        TAF_MMA_SndApHplmnCnf(ClientId, OpId, TAF_ERR_ERROR, VOS_NULL_PTR);

        return;
    }

    /*�жϿ�״̬*/
    ulRet = MMA_PhoneGetUsimStatus(&ucSimStatus );
    if ( (ulRet != MMA_SUCCESS )
       ||(MMA_USIM_ABSENT == ucSimStatus)
       )
    {
        MMA_WARNINGLOG("MMA_HomePlmnProc():WARNING:USIM is Error or Absent!");

        TAF_MMA_SndApHplmnCnf(ClientId, OpId, TAF_ERR_ERROR, VOS_NULL_PTR);

        return;
    }

    /*������ʱ��*/
    if(MMA_SUCCESS != MMA_StartInternalTimer(1,
                                             MMA_GET_USIM_MNC_LENGTH_OP,
                                             ClientId,
                                             OpId))
    {
        MMA_WARNINGLOG("MMA_HomePlmnProc():WARNING:Unknow Error!");

        TAF_MMA_SndApHplmnCnf(ClientId, OpId, TAF_ERR_ERROR, VOS_NULL_PTR);

        return;
    }
    /*����*/
    /* Added by h00313353 for iteration 9, 2015-2-4, begin */
    if (TAF_SDC_SIM_TYPE_USIM == enSimType)
    {/* 3G USIM */
        usFileId = USIMM_USIM_EFAD_ID;
    }
    else if (TAF_SDC_SIM_TYPE_SIM == enSimType)
    {/* 2G SIM */
        usFileId = USIMM_GSM_EFAD_ID;
    }
    else
    {
        return;
    }
    /* Added by h00313353 for iteration 9, 2015-2-4, end */

    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                    /* Modified by h00313353 for iteration 9, 2015-2-5, begin */
                                    USIMM_GUTL_APP,
                                    usFileId,
                                    /* Modified by h00313353 for iteration 9, 2015-2-5, end */
                                    0);

    if( USIMM_API_SUCCESS != NAS_USIMMAPI_GetFileReq(WUEPS_PID_MMA,
                                              0,
                                              &stGetFileInfo))
    {
        MMA_WARNINGLOG("MMA_HomePlmnProc():WARNING:get File Error!");

        TAF_MMA_SndApHplmnCnf(ClientId, OpId, TAF_ERR_ERROR, VOS_NULL_PTR);

        /*ֹͣ��ʱ��*/
        MMA_StopInternalTimer();
        return;
    }

    gstMmaValue.stGetHplmn.usClientId = ClientId;
    gstMmaValue.stGetHplmn.ucOpId     = OpId;
    gstMmaValue.stGetHplmn.ucHplmnQryFlag = VOS_TRUE;


    return;
}



TAF_UINT32 MMA_String2Hex(VOS_UINT8 *nptr,VOS_UINT16 usLen,VOS_UINT32 *pRtn)
{
    VOS_UINT32 c     = 0;         /* current Char */
    VOS_UINT32 total = 0;         /* current total */
    VOS_UINT8 Length = 0;         /* current Length */

    /*lint -e961*/
    c = (VOS_UINT32)*nptr++;

    while(Length++ < usLen)
    {
        if( (c  >= '0') && (c  <= '9') )
        {
            c  = c  - '0';
        }
        else if( (c  >= 'a') && (c  <= 'f') )
        {
            c  = (c  - 'a') + 10;
        }
        else if( (c  >= 'A') && (c  <= 'F') )
        {
            c  = (c  - 'A') + 10;
        }
        else
        {
            return VOS_ERR;
        }

        if(total > 0x0FFFFFFF)              /* ������ת */
        {
            return VOS_ERR;
        }
        else
        {
            total = (total << 4) + c;              /* accumulate digit */
            c = (TAF_UINT32)(TAF_UINT8)*nptr++;    /* get next Char */
        }
    }
    /*lint +e961*/
    *pRtn = total;   /* return result, negated if necessary */
    return VOS_OK;
}
VOS_VOID MMA_CrpnQuery_GetPlmnNum(
    TAF_PH_OPERATOR_NAME_STRU          *pstOrigOperName,
    TAF_MMA_CRPN_QRY_PARA_STRU         *pstMnMmaCrpnQry,
    VOS_UINT8                          *pucMaxMncLen,
    VOS_UINT32                         *pulTotalNum
)
{
    VOS_UINT8                           ucMaxMncLen;
    VOS_UINT32                          ulTotalNum;

    if (0 == pstMnMmaCrpnQry->ucPlmnType)
    {
        PS_MEM_CPY(pstOrigOperName->aucOperatorNameLong, pstMnMmaCrpnQry->aucPlmnName, pstMnMmaCrpnQry->usPlmnNameLen);
        pstOrigOperName->aucOperatorNameLong[pstMnMmaCrpnQry->usPlmnNameLen] = 0;
        ulTotalNum = MMA_PhoneGetAllOperNumByLongNameFromOperTbl(pstOrigOperName, &ucMaxMncLen);
    }
    else if(1 == pstMnMmaCrpnQry->ucPlmnType)
    {
        PS_MEM_CPY(pstOrigOperName->aucOperatorNameShort, pstMnMmaCrpnQry->aucPlmnName, pstMnMmaCrpnQry->usPlmnNameLen);
        pstOrigOperName->aucOperatorNameShort[pstMnMmaCrpnQry->usPlmnNameLen] = 0;
        ulTotalNum = MMA_PhoneGetAllOperNumByShortNameFromOperTbl(pstOrigOperName, &ucMaxMncLen);
    }
    else
    {
        /*һ��PLMN IDֻ��Ӧ��һ��PLMN INFO*/
        ulTotalNum = 1;
        ucMaxMncLen = (VOS_UINT8)pstMnMmaCrpnQry->usPlmnNameLen;
    }

    *pucMaxMncLen = ucMaxMncLen;
    *pulTotalNum  = ulTotalNum;

    return;
}
VOS_UINT8 TAF_MMA_IsMncLenVaild(
    VOS_UINT8                           ucMncLen
)
{
    if ((5 != ucMncLen)
     && (6 != ucMncLen))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/* Deleted by k902809 for Iteration 11, 2015-3-30, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-30, end */

/* MN_MMA_GetBandInfo */

/* delete MMA_PhCrpnQueryRsp */

/* Deleted by h00313353 for iteration 9, 2015-2-7, begin */

/* Deleted by h00313353 for iteration 9, 2015-2-7, end */

/*lint -e429 -e830*/

VOS_VOID Taf_InitEventInfoOP(TAF_PHONE_EVENT_INFO_STRU *pstEvent)
{

    /*�������ѡ��Ϊ0*/
    pstEvent->OP_RegPlmn            = 0;
    pstEvent->OP_CsServiceStatus    = 0;
    pstEvent->OP_PsServiceStatus    = 0;
    pstEvent->OP_PlmnReselMode      = 0;
    pstEvent->OP_PhoneError         = 0;
    pstEvent->OP_CurRegSta          = 0;
    pstEvent->OP_Rssi               = 0;
    pstEvent->OP_BatteryPower       = 0;
    pstEvent->OP_Pin                = 0;
    pstEvent->OP_UsimAccessData     = 0;
    pstEvent->OP_PinRemain          = 0;
    pstEvent->OP_MeLockStatus       = 0;
    pstEvent->OP_MePersonalisation  = 0;
    pstEvent->OP_OperMode           = 0;
    pstEvent->OP_SpnInfo            = 0;
    pstEvent->OP_Mode               = 0;
    pstEvent->OP_Srvst              = 0;
    pstEvent->OP_UsimRestrictAccess = 0;
    pstEvent->OP_UsimPNN            = 0;
    pstEvent->OP_SysCfg             = 0;
    pstEvent->OP_UsimOPL            = 0;
    pstEvent->OP_Spare              = 0;

    return;
}
/*lint +e429 +e830*/


/* Deleted by y00307564 for CDMA Iteration 8 2015-2-28 begin */
/* Deleted by y00307564 for CDMA Iteration 8 2015-2-28 end */



VOS_BOOL TAF_MMA_IsSimLockPlmnInfoValid(VOS_VOID)
{
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU  stSimLockPlmnInfo;
    VOS_UINT32                          i;

    PS_MEM_SET(&stSimLockPlmnInfo, 0x00, sizeof(stSimLockPlmnInfo));

    if (NV_OK != NV_Read(en_NV_Item_CustomizeSimLockPlmnInfo,
                       &stSimLockPlmnInfo,
                       sizeof(stSimLockPlmnInfo)))
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == stSimLockPlmnInfo.ulStatus)
    {
        return VOS_FALSE;
    }

    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        if (0xAA == stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin[0])
        {
            continue;
        }

        break;
    }

    /* ���ÿһ���PLMN��������Ч�ģ���ô����û����Ч��PLMN��Ϣ */
    if (TAF_MAX_SIM_LOCK_RANGE_NUM == i)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_VOID TAF_MMA_RcvSimLockQry(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId
)
{
    TAF_CUSTOM_CARDLOCK_STATUS_STRU     stCardLockStatus;
    VOS_UINT32                          ulRet;
    AT_MMA_SIMLOCK_STATUS_STRU         *pstEvent;


    PS_MEM_SET(&stCardLockStatus, 0x00, sizeof(stCardLockStatus));

    pstEvent = (AT_MMA_SIMLOCK_STATUS_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_MMA,
                                             sizeof(AT_MMA_SIMLOCK_STATUS_STRU));
    if (VOS_NULL_PTR == pstEvent)
    {
        MN_WARN_LOG("TAF_MMA_RcvSimLockQry: read sim lock status fail");
        return;
    }

    pstEvent->ulReceiverPid          = WUEPS_PID_AT;
    pstEvent->ulMsgName              = ID_TAF_MMA_SIMLOCK_STAUS_QUERY_CNF;
    pstEvent->stAtAppCtrl.usClientId = MN_GetRealClientId(ClientId, WUEPS_PID_MMA);;
    pstEvent->stAtAppCtrl.ucOpId     = OpId;

    ulRet = NV_Read(en_NV_Item_CardlockStatus,
                    &stCardLockStatus,
                    (VOS_UINT32)(sizeof(stCardLockStatus)));
    if (NV_OK != ulRet)
    {
        pstEvent->bSimlockEnableFlg = VOS_TRUE;
    }
    else
    {
        if ((VOS_TRUE == TAF_MMA_IsSimLockPlmnInfoValid())
         && (NV_ITEM_ACTIVE == stCardLockStatus.ulStatus)
         && (TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE != stCardLockStatus.enCardlockStatus))
        {
            pstEvent->bSimlockEnableFlg = VOS_TRUE;
        }
        else
        {
            pstEvent->bSimlockEnableFlg = VOS_FALSE;
        }
    }

    /* ������Ϣ */
    ulRet = PS_SEND_MSG(WUEPS_PID_MMA, pstEvent);
    if( VOS_OK != ulRet)
    {
        MMA_WARNINGLOG("TAF_MMA_RcvSimLockQry: Send Msg Error");
    }

    return;
}
VOS_VOID TAF_MMA_UpdateSimlockStatus(VOS_BOOL bUnlockOK)
{

    VOS_UINT32                          ulResult;
    TAF_CUSTOM_CARDLOCK_STATUS_STRU     stCardLockStatus;
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU  stSimLockMaxTimes;


    stSimLockMaxTimes.ulStatus       = NV_ITEM_DEACTIVE;
    stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;

    /* ��ȡ��ǰ���������� */
    ulResult = NV_Read(en_NV_Item_CustomizeSimLockMaxTimes,
                      &stSimLockMaxTimes,
                      sizeof(stSimLockMaxTimes));
    if (NV_OK != ulResult)
    {
        MMA_WARNINGLOG("TAF_MMA_UpdateSimlockStatus: Fail to read en_NV_Item_CustomizeSimLockMaxTimes.");
        stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
    }
    else
    {
        if (NV_ITEM_DEACTIVE == stSimLockMaxTimes.ulStatus)
        {
            stSimLockMaxTimes.ulLockMaxTimes = TAF_PH_CARDLOCK_DEFAULT_MAXTIME;
        }
    }

    /* ��ȡNV��en_NV_Item_CardlockStatus�е��������� */
    if (NV_OK != NV_Read(en_NV_Item_CardlockStatus, &stCardLockStatus, sizeof(stCardLockStatus)))
    {
        MMA_WARNINGLOG("TAF_MMA_UpdateSimlockStatus: Not read sim lock status");
        stCardLockStatus.ulRemainUnlockTimes = 0;
    }

    if (VOS_TRUE == bUnlockOK)
    {
        /* SimlockУ��ͨ���������ý������״̬  */
        stCardLockStatus.ulStatus            = NV_ITEM_ACTIVE;
        stCardLockStatus.enCardlockStatus    = TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE;
        stCardLockStatus.ulRemainUnlockTimes = stSimLockMaxTimes.ulLockMaxTimes;
    }
    else
    {
        stCardLockStatus.ulStatus            = NV_ITEM_ACTIVE;
        stCardLockStatus.enCardlockStatus    = TAF_OPERATOR_LOCK_LOCKED;
    }

    ulResult = NV_Write(en_NV_Item_CardlockStatus,
                        &stCardLockStatus,
                        sizeof(stCardLockStatus));
    if (NV_OK != ulResult)
    {
        MMA_WARNINGLOG("TAF_MMA_UpdateSimlockStatus: write en_NV_Item_CardlockStatus Fail.");
        return;
    }

    /*lint -e774*/
    ulResult = NV_SpecialNvIdBackup(en_NV_Item_CardlockStatus,
                                    &stCardLockStatus,
                                    sizeof(stCardLockStatus));
    if (NV_OK != ulResult)
    {
        MMA_WARNINGLOG("TAF_MMA_UpdateSimlockStatus:ERROR:write special en_NV_Item_CardlockStatus Fail.");
        return;
    }
    /*lint +e774*/


    return;

}
VOS_UINT32 MMA_SaveWCipherInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU  *pstCipherInfoInd;

    pstCipherInfoInd = (MSCC_MMA_UMTS_CIPHER_INFO_IND_STRU*)pstMsg;

    /* ��MSCC������Cipher��Ϣ���浽ȫ�ֱ��� */
    g_stMmaCipherInfo.enCipherAlgorForCSDomain = pstCipherInfoInd->ucCipherAlgorForCSDomain;
    g_stMmaCipherInfo.enCipherAlgorForPSDomain = pstCipherInfoInd->ucCipherAlgorForPSDomain;

    return VOS_TRUE;
}
VOS_UINT32 MMA_SaveGCipherInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU  *pstCipherInfoInd;
    pstCipherInfoInd = (MSCC_MMA_GPRS_CIPHER_INFO_IND_STRU*)pstMsg;

    /* ��MSCC������Cipher��Ϣ���浽ȫ�ֱ��� */
    g_stMmaCipherInfo.ucGprsCipher             = pstCipherInfoInd->ucGprsCipher;
    g_stMmaCipherInfo.ucGprsCipherAlg          = pstCipherInfoInd->ucGprsCipherAlg;

    return VOS_TRUE;
}
VOS_VOID MMA_QryCipherInfo(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT8                           ucCipherInfo;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enRadioMode;

    /* ��ʼ������ */
    ucCipherInfo    = MMA_UMTS_UEA0;

    /*��ȡ��ǰ���뼼��, ����API*/
    enRadioMode = TAF_SDC_GetSysMode();

    if (TAF_SDC_SYS_MODE_GSM == enRadioMode)
    {
        /* ��ȡGģ�µ�PS�������Ϣ */
        if (VOS_TRUE == g_stMmaCipherInfo.ucGprsCipher)
        {
            ucCipherInfo = g_stMmaCipherInfo.ucGprsCipherAlg;
        }
        else
        {
            ucCipherInfo = MMA_UMTS_UEA0;
        }
    }
    else
    {
        /* ��ȡWģ�µ�PS�������Ϣ */
        switch(g_stMmaCipherInfo.enCipherAlgorForPSDomain)
        {
            case MMA_CIPHER_ALGOR_UEA0:
                ucCipherInfo = MMA_UMTS_UEA0;
                break;
            case MMA_CIPHER_ALGOR_UEA1:
                ucCipherInfo = MMA_UMTS_UEA1;
                break;
            case MMA_CIPHER_ALGOR_UEA2:
                ucCipherInfo = MMA_UMTS_UEA2;
                break;
            default:
                ucCipherInfo = MMA_UMTS_UEA0;
                break;
        }
    }

    TAF_MMA_SndCipherQryCnf(usClientId, ucOpId, ucCipherInfo, VOS_OK);

    return;
}


VOS_UINT32 MN_PH_QryLocinfo (
    VOS_UINT32                         *pulMcc,
    VOS_UINT32                         *pulMnc,
    VOS_UINT16                         *pusLac,
    VOS_UINT8                          *pucRac,
    VOS_UINT32                         *pulCellId
)
{
    TAF_SDC_PLMN_ID_STRU                *pstPlmnId = VOS_NULL_PTR;

    /* Modified by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
    if ( TAF_REPORT_SRVSTA_NO_SERVICE == TAF_SDC_GetAppServiceStatus() )
    /* Modified by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */
    {
        /* �޷���״̬ʱ�Ĵ���*/
        (*pulMcc)       = 0;
        (*pulMnc)       = 0;
        (*pusLac)       = 0;
        (*pucRac)       = 0;
        (*pulCellId)    = 0;

        return VOS_OK;
    }

    /* ��ȡ��ǰ�����PLMN��LAC��RAC��CellIdֵ */
    /* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, begin */
    pstPlmnId            = TAF_SDC_GetAppServicePlmnId();
    *pulMcc              = pstPlmnId->ulMcc;
    *pulMnc              = pstPlmnId->ulMnc;
    *pusLac              = TAF_SDC_GetAppCampLac();
    *pucRac              = TAF_SDC_GetAppCampRac();
    *pulCellId           = TAF_SDC_GetAppCampCellId();
    /* Modified by l00305157 for Service_State_Optimize_PhaseI, 2014-11-29, end */


    return VOS_OK;
}


VOS_VOID TAF_MMA_GetUsimHplmnMncLenFileInd(USIMM_READFILE_CNF_STRU *pUsimTafMsg)
{
    TAF_MMA_HPLMN_WITH_MNC_LEN_STRU     stHplmnWithMncLen;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stHplmnWithMncLen, 0, sizeof(TAF_MMA_HPLMN_WITH_MNC_LEN_STRU));

    /* ��������Ч */
    if ( pUsimTafMsg->usEfLen <= 3 )
    {
        stHplmnWithMncLen.ucHplmnMncLen = MN_MMA_MNC_LENGTH_THREE_BYTES_IN_IMSI;
    }
    else
    {
        /* ��ȡMNC���� */
        if (( MN_MMA_MNC_LENGTH_TWO_BYTES_IN_IMSI == (pUsimTafMsg->aucEf[MN_MMA_MNC_LENGTH_INDICATOR_POSITION-1] & MN_MMA_OCTET_LOW_FOUR_BITS) )
         || ( MN_MMA_MNC_LENGTH_THREE_BYTES_IN_IMSI == (pUsimTafMsg->aucEf[MN_MMA_MNC_LENGTH_INDICATOR_POSITION-1] & MN_MMA_OCTET_LOW_FOUR_BITS) ))
        {
            stHplmnWithMncLen.ucHplmnMncLen = pUsimTafMsg->aucEf[MN_MMA_MNC_LENGTH_INDICATOR_POSITION-1] & MN_MMA_OCTET_LOW_FOUR_BITS;
        }
        else
        {
            stHplmnWithMncLen.ucHplmnMncLen = MN_MMA_MNC_LENGTH_THREE_BYTES_IN_IMSI;
        }
    }

    /* ��ȡHPLMN */
    ulResult = MN_PH_QryApHplmn(&stHplmnWithMncLen.stHplmn.Mcc, &stHplmnWithMncLen.stHplmn.Mnc);

    /* �ϱ�AT^APHPLMN������ѯ����¼� */
    if (VOS_OK != ulResult)
    {
        TAF_MMA_SndApHplmnCnf(gstMmaValue.stGetHplmn.usClientId,
                              gstMmaValue.stGetHplmn.ucOpId,
                              TAF_ERR_ERROR,
                              VOS_NULL_PTR);
    }
    else
    {

        TAF_MMA_SndApHplmnCnf(gstMmaValue.stGetHplmn.usClientId,
                              gstMmaValue.stGetHplmn.ucOpId,
                              TAF_ERR_NO_ERROR,
                              &stHplmnWithMncLen);
    }

    /*ֹͣ��ʱ��*/
    MMA_StopInternalTimer();

    return;
}



/* Deleted by wx270776 for OM�ں�, 2015-7-16, begin */

/* Deleted by wx270776 for OM�ں�, 2015-7-16, end */



/* TAF_MMA_ReadCustomerServiceProfileFile_SwitchOn */


VOS_VOID TAF_MMA_TransferRatMode(
    TAF_MMA_RAT_MODE_ENUM_U8            enRatMode,
    TAF_MMA_RAT_ORDER_STRU             *pstRatModeOrder
)
{
    switch(enRatMode)
    {
        /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
        case TAF_MMA_RAT_MODE_ENUM_DAUL_MODE:
            pstRatModeOrder->ucRatOrderNum  = TAF_PH_MAX_GU_RAT_NUM;
            pstRatModeOrder->aenRatOrder[0] = TAF_MMA_RAT_WCDMA;
            pstRatModeOrder->aenRatOrder[1] = TAF_MMA_RAT_GSM;
            pstRatModeOrder->aenRatOrder[2] = TAF_MMA_RAT_BUTT;
            break;

        case TAF_MMA_RAT_MODE_ENUM_2G_ONLY:
            pstRatModeOrder->ucRatOrderNum  = 1;
            pstRatModeOrder->aenRatOrder[0] = TAF_MMA_RAT_GSM;
            pstRatModeOrder->aenRatOrder[1] = TAF_MMA_RAT_BUTT;
            pstRatModeOrder->aenRatOrder[2] = TAF_MMA_RAT_BUTT;
            break;

        case TAF_MMA_RAT_MODE_ENUM_3G_ONLY:
            pstRatModeOrder->ucRatOrderNum  = 1;
            pstRatModeOrder->aenRatOrder[0] = TAF_MMA_RAT_WCDMA;
            pstRatModeOrder->aenRatOrder[1] = TAF_MMA_RAT_BUTT;
            pstRatModeOrder->aenRatOrder[2] = TAF_MMA_RAT_BUTT;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_MMA_RAT_MODE_ENUM_TRI_MODE:
            pstRatModeOrder->ucRatOrderNum  = TAF_PH_MAX_GUL_RAT_NUM;
            pstRatModeOrder->aenRatOrder[0] = TAF_MMA_RAT_LTE;
            pstRatModeOrder->aenRatOrder[1] = TAF_MMA_RAT_WCDMA;
            pstRatModeOrder->aenRatOrder[2] = TAF_MMA_RAT_GSM;
            break;

        case TAF_MMA_RAT_MODE_ENUM_LTE_ONLY:
            pstRatModeOrder->ucRatOrderNum  = 1;
            pstRatModeOrder->aenRatOrder[0] = TAF_MMA_RAT_LTE;
            pstRatModeOrder->aenRatOrder[1] = TAF_MMA_RAT_BUTT;
            pstRatModeOrder->aenRatOrder[2] = TAF_MMA_RAT_BUTT;

            break;
#endif

        default:
#if (FEATURE_ON == FEATURE_LTE)
            pstRatModeOrder->ucRatOrderNum  = TAF_PH_MAX_GUL_RAT_NUM;
            pstRatModeOrder->aenRatOrder[0] = TAF_MMA_RAT_LTE;
            pstRatModeOrder->aenRatOrder[1] = TAF_MMA_RAT_WCDMA;
            pstRatModeOrder->aenRatOrder[2] = TAF_MMA_RAT_GSM;
#else
            pstRatModeOrder->ucRatOrderNum  = TAF_PH_MAX_GU_RAT_NUM;
            pstRatModeOrder->aenRatOrder[0] = TAF_MMA_RAT_WCDMA;
            pstRatModeOrder->aenRatOrder[1] = TAF_MMA_RAT_GSM;
            pstRatModeOrder->aenRatOrder[2] = TAF_MMA_RAT_BUTT;
        /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
#endif
            break;
    }

    /* ɾ��ƽ̨��֧�ֵĽ��뼼�� */
    TAF_MMA_DelPlatformUnsupportedRat(pstRatModeOrder);

    /* ������н��뼼��ƽ̨����֧�֣�ʹ��ƽ̨Ĭ��ֵ */
    if (0 == pstRatModeOrder->ucRatOrderNum)
    {
        MN_MMA_SetDefaultRatPrioList(pstRatModeOrder);
    }

    return;
}

VOS_VOID TAF_MMA_ReadRatModeFile(VOS_VOID)
{
    VOS_UINT32                          ulEfLen;
    VOS_UINT8                          *pucEf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucSimType;
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList = VOS_NULL_PTR;


    ulEfLen   = 0;
    ucSimType = USIMM_CARD_NOCARD;

    pstRatPrioList = TAF_MMA_GetRatPrioListAddr();

    /* ���뼼��ƽ����ƹ���δʹ�� */
    if (VOS_TRUE != TAF_MMA_GetRatBalancingEnableFlg())
    {
        return;
    }

    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucSimType);

    if (USIMM_CARD_USIM == ucSimType)
    {
        /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
        ulResult = NAS_USIMMAPI_GetCachedFile(USIMM_ATTUSIM_EFRATMODE_ID, &ulEfLen, &pucEf, USIMM_GUTL_APP);
        /* Modified by h00313353 for iteration 9, 2015-2-9, end */

        /* ���ļ�ʧ�� */
        if (USIMM_API_SUCCESS != ulResult)
        {
            /* ʹ��Ĭ��ֵ */
            MN_MMA_SetDefaultRatPrioList(pstRatPrioList);
        }
        /* ���ļ��ɹ� */
        else
        {
            /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
            TAF_MMA_SndOmGetCacheFile(USIMM_ATTUSIM_EFRATMODE_ID, ulEfLen, pucEf);
            /* Modified by h00313353 for iteration 9, 2015-2-9, end */

            if (ulEfLen < TAF_MMA_RAT_MODE_FILE_LEN)
            {
                /* ʹ��Ĭ��ֵ */
                MN_MMA_SetDefaultRatPrioList(pstRatPrioList);
            }
            else
            {
                TAF_MMA_TransferRatMode(pucEf[0], pstRatPrioList);
            }
        }
    }
    else
    {
        /* ��USIM����ֱ�����ó�DUAL MODE*/
        TAF_MMA_TransferRatMode(TAF_MMA_RAT_MODE_ENUM_DAUL_MODE, pstRatPrioList);
    }

    /* ����gstMmaValue.pg_StatusContext.stRatPrioListȫ�ֱ��� */
    PS_MEM_CPY(&gstMmaValue.pg_StatusContext->stRatPrioList, pstRatPrioList, sizeof(TAF_MMA_RAT_ORDER_STRU));

    return;
}
VOS_VOID TAF_MMA_SetPlmnSelectionMode(VOS_UINT8 ucPlmnSelMode)
{
    g_StatusContext.ucPlmnSelMode = ucPlmnSelMode;
}


VOS_UINT8 TAF_MMA_GetPlmnSelectionMode(VOS_VOID)
{
    return g_StatusContext.ucPlmnSelMode;
}


VOS_VOID TAF_MMA_SetNetworkSelectionMenuEnableFlg(VOS_UINT8 ucEnableFlg)
{
    g_StatusContext.stNetSelMenuCtx.ucNetSelMenuFlg = ucEnableFlg;
}


VOS_UINT8 TAF_MMA_GetNetworkSelectionMenuEnableFlg(VOS_VOID)
{
    return g_StatusContext.stNetSelMenuCtx.ucNetSelMenuFlg;
}


VOS_VOID TAF_MMA_SetPlmnMode_Refresh(TAF_MMA_PLMN_MODE_ENUM_UINT8 enPlmnMode)
{
    g_StatusContext.stNetSelMenuCtx.enPlmnMode = enPlmnMode;
}


TAF_MMA_PLMN_MODE_ENUM_UINT8 TAF_MMA_GetPlmnMode_Refresh(VOS_VOID)
{
    return g_StatusContext.stNetSelMenuCtx.enPlmnMode;
}


VOS_VOID TAF_MMA_SetAutoPlmnSelUser(TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 enAutoPlmnSelUser)
{
    g_StatusContext.stNetSelMenuCtx.enAutoPlmnSelUser = enAutoPlmnSelUser;
}


TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 TAF_MMA_GetAutoPlmnSelUser(VOS_VOID)
{
    return g_StatusContext.stNetSelMenuCtx.enAutoPlmnSelUser;
}


VOS_UINT8 TAF_MMA_GetTiTryingPeriodNetSelMenuStatus(VOS_VOID)
{
    return g_StatusContext.stNetSelMenuCtx.stTiPeriodTryingNetSelMenu.ucTimerStatus;
}


VOS_VOID TAF_MMA_SetTiTryingPeriodNetSelMenuStatus(VOS_UINT8 ucStatus)
{
    g_StatusContext.stNetSelMenuCtx.stTiPeriodTryingNetSelMenu.ucTimerStatus = ucStatus;
}


VOS_VOID TAF_MMA_SetRatBalancingEnableFlg(VOS_UINT8 ucEnableFlg)
{
    g_StatusContext.stRatBalancingCtx.ucRatBalancingFlg = ucEnableFlg;
}


VOS_UINT8 TAF_MMA_GetRatBalancingEnableFlg(VOS_VOID)
{
    return g_StatusContext.stRatBalancingCtx.ucRatBalancingFlg;
}


VOS_VOID TAF_MMA_SetRatMode_Refresh(TAF_MMA_RAT_MODE_ENUM_U8 enRatMode)
{
    g_StatusContext.stRatBalancingCtx.enRatMode = enRatMode;
}


TAF_MMA_RAT_MODE_ENUM_U8 TAF_MMA_GetRatMode_Refresh(VOS_VOID)
{
    return g_StatusContext.stRatBalancingCtx.enRatMode;
}


VOS_UINT8 TAF_MMA_GetTiTryingPeriodRatBalancingStatus(VOS_VOID)
{
    return g_StatusContext.stRatBalancingCtx.stTiPeriodTryingRatBalancing.ucTimerStatus;
}


VOS_VOID TAF_MMA_SetTiTryingPeriodRatBalancingStatus(VOS_UINT8 ucStatus)
{
    g_StatusContext.stRatBalancingCtx.stTiPeriodTryingRatBalancing.ucTimerStatus = ucStatus;
}


VOS_UINT32 TAF_MMA_GetPlmnModeOfCustomerServiceProfileFile(
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf,
    TAF_MMA_PLMN_MODE_ENUM_UINT8       *penPlmnMode
)
{
    VOS_UINT16                          usIndex;
    VOS_UINT16                          usIndexMax;

    /* 6F15�ļ���ʽ
    |Byte
    |---|---|---|---|--------|-------|--------|
    |1  |2  |3  |4  |.. .. ..| X-1   | X      |
    |---|---|---|---|--------|-------|--------|
    |A1 |B1 |A2 |B2 |.. .. ..| A(X/2)| B(X/2) |
    |---|---|---|---|--------|-------|--------|

    Byte A   Byte B
    <hex>    <----------------------------------------binary--------------------------------------->

    |--------|-----------|------|-----|--------|-------|------|------|----------|----------|
    |Service |           |      |     |        |       |      |      |          |          |
    |Group   |           |      |     |        |       |      |      |          |          |
    |Code    | Service   | Bit8 | Bit7| Bit6   | Bit5  | Bit4 | Bit3 | Bit2     | Bit1     |
    |--------|-----------|------|-----|--------|-------|------|------|----------|----------|
    |C0      | ValueAdded| PLMN | VPS | SM/MO  | SM/MO | Fax  | Data | Reserved | Language |
    |        | Services  | MODE |     | PAGING | EMAIL |      |      |          |          |
    |--------|-----------|------|-----|--------|-------|------|------|----------|----------|

    A*��B*Ϊһ����ϣ�A*��ʾservice group��B*��ÿ��bit��ʾһ��service
    plmn modeλ: A*ΪC0��B*��Bit8
    */

    usIndexMax = usEfLen;

    /* �ļ����Ȳ�Ϊż���������һ��GROUPֻ��A*û��B*�����Բ���Ҫƥ�����һ��A* */
    if (0 != (usEfLen % TAF_MMA_GROUP_LEN_IN_CUSTOMER_SERVICE_PROFILE_FILE))
    {
        usIndexMax = usEfLen - 1;
        MMA_WARNINGLOG("TAF_MMA_GetPlmnModeOfCustomerServiceProfileFile: file content is invalid");
    }

    /* ����PLMN MODEλ */
    for (usIndex = 0; usIndex < usIndexMax; usIndex = (usIndex + TAF_MMA_GROUP_LEN_IN_CUSTOMER_SERVICE_PROFILE_FILE))
    {
        if (TAF_MMA_SERVICE_GROUP_CODE_IN_CUSTOMER_SERVICE_PROFILE_FILE == pucEf[usIndex])
        {
            /* Bit8��ʾPLMN MODE*/
            *penPlmnMode
                = (pucEf[usIndex + 1] & TAF_MMA_PLMN_MODE_IN_SERVICE_GROUP_CODE) >> TAF_MMA_PLMN_MODE_OFFSET_IN_SERVICE_GROUP_CODE;

            break;
        }
    }

    /* PLMN MODEλ�����ڣ�����VOS_ERR */
    if (usIndex >= usIndexMax)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 TAF_MMA_RcvCustomerServiceProfileFile_PreProc(
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
)
{
    TAF_MMA_PLMN_MODE_ENUM_UINT8        enPlmnMode;

    /* ����ѡ��˵����ƹ���δʹ�ܣ�����VOS_TRUE */
    if (VOS_FALSE == TAF_MMA_GetNetworkSelectionMenuEnableFlg())
    {
        MMA_WARNINGLOG("TAF_MMA_RcvCustomerServiceProfileFile_PreProc: NV is deactive");
        return VOS_TRUE;
    }

    /* δ��ȡPLMN MODEλ������VOS_TRUE */
    if (VOS_OK != TAF_MMA_GetPlmnModeOfCustomerServiceProfileFile(usEfLen, pucEf, &enPlmnMode))
    {
        MMA_ERRORLOG("TAF_MMA_RcvCustomerServiceProfileFile_PreProc: No Plmn Mode");
        return VOS_TRUE;
    }

    /* ����TAF_MMA_ReportPlmnModeEvent�ϱ�TAF_PH_EVT_NSM_STATUS_IND�¼� */
    TAF_MMA_ReportPlmnModeEvent(enPlmnMode);

    /* ����TAF_MMA_SetPlmnMode_Refresh ����PLMN MODE */
    TAF_MMA_SetPlmnMode_Refresh(enPlmnMode);

    /* PLMN MODE λ1������VOS_TRUE */
    if (TAF_MMA_PLMN_MODE_ENUM_ENABLE == enPlmnMode)
    {
        return VOS_TRUE;
    }

    /* ��ǰ�Ѿ����Զ�������ֱ�ӷ��� VOS_TRUE*/
    if (NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO== TAF_MMA_GetPlmnSelectionMode())
    {
        return VOS_TRUE;
    }

    /* TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU��ʱ���������У�ֱ�ӷ���VOS_TRUE */
    if (MMA_TIMER_RUN == TAF_MMA_GetTiTryingPeriodNetSelMenuStatus())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_VOID TAF_MMA_ProcCustomerServiceProfileFile(VOS_VOID)
{
    VOS_UINT32                          ulResult;

    if ((STA_FSM_STOP == g_StatusContext.ulFsmState)
     || (STA_FSM_NULL == g_StatusContext.ulFsmState))
    {
        /* �ػ���NULL״̬������ */
        MMA_NORMAILLOG("TAF_MMA_ProcCustomerServiceProfileFile(): Start Timer Fail");
    }
    else if (STA_FSM_ENABLE == g_StatusContext.ulFsmState)
    {
        /* �����Զ��������� */
        TAF_MMA_SndAutoPlmnReselect_Refresh();

        /* ��¼ΪRefresh�������Զ����� */
        TAF_MMA_SetAutoPlmnSelUser(TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH);
    }
    else
    {
        /* ����TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU��ʱ�� */
        ulResult = NAS_StartRelTimer(&(g_StatusContext.stNetSelMenuCtx.stTiPeriodTryingNetSelMenu.MmaHTimer),
                                     WUEPS_PID_MMA,
                                     TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU_LEN,
                                     TAF_MMA,
                                     TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU,
                                     VOS_RELTIMER_NOLOOP );

        if( VOS_OK !=  ulResult)
        {
            MMA_ERRORLOG("TAF_MMA_ProcCustomerServiceProfileFile(): Start Timer Fail");
        }
        else
        {
            TAF_MMA_SetTiTryingPeriodNetSelMenuStatus(MMA_TIMER_RUN);
        }
    }

    return;
}

/* TAF_MMA_RcvCustomerServiceProfileFile */

VOS_VOID TAF_MMA_NetworkSelectionMenuCtrlTimerExpired(VOS_VOID)
{
    /* ���¶�ʱ��״̬ */
    TAF_MMA_SetTiTryingPeriodNetSelMenuStatus(MMA_TIMER_STOP);

    /* ����ڶ�ʱ�����й����У��ִ�����REFRESH����Ҫ�ж����һ��REFRESH�Ƿ���Ҫ�����Զ����� */
    if (TAF_MMA_PLMN_MODE_ENUM_DISABLE != TAF_MMA_GetPlmnMode_Refresh())
    {
        return;
    }

    /* ��ǰ�Ѿ����Զ����� ������ */
    if (NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO == TAF_MMA_GetPlmnSelectionMode())
    {
        return;
    }

    /* ����6F15�ļ� */
    TAF_MMA_ProcCustomerServiceProfileFile();

    return;
}



VOS_VOID TAF_MMA_ProcRatMode_EnableStatus(TAF_MMA_RAT_MODE_ENUM_U8 enRatMode)
{
    TAF_MMA_RAT_ORDER_STRU              stCurRatModeOrder;

    TAF_MMA_SYS_CFG_PARA_STRU           stSysCfg;

    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *pLastSyscfgSet = VOS_NULL_PTR;
#if(FEATURE_ON == FEATURE_LTE)
    TAF_USER_SET_PREF_BAND64           *pstUeSupportLteBand = VOS_NULL_PTR;
#endif

    /* ��4F36�ļ���PLMN MODEֵת����MMA�Ľ��뼼���б� */
    TAF_MMA_TransferRatMode(enRatMode, &stCurRatModeOrder);

    /* ��MN_MMA_GetRatPrioListAddr�л�ȡ���뼼��֮��Ĳ��� */
    pLastSyscfgSet     = TAF_MMA_GetLastSyscfgSetAddr();


    /* Modified by h00313353 for Iteration 13, 2015-4-9, begin */
    stSysCfg.enRoam      = pLastSyscfgSet->enRoam;
    stSysCfg.enSrvDomain = pLastSyscfgSet->enSrvDomain;
    /* Modified by h00313353 for Iteration 13, 2015-4-9, end */
    stSysCfg.stGuBand    = pLastSyscfgSet->stUserSetBand.stOrigUserSetGuBand;
#if(FEATURE_ON == FEATURE_LTE)
    stSysCfg.stLBand     = pLastSyscfgSet->stUserSetBand.stUserSetLteBand;
#endif

    stSysCfg.stGuBand.ulBandLow  &= TAF_MMA_GetUeSupportBandAddr()->ulAllUeBand;
#if(FEATURE_ON == FEATURE_LTE)
    pstUeSupportLteBand = TAF_MMA_GetUeSupportLteBandAddr();
    stSysCfg.stLBand.ulBandHigh &= pstUeSupportLteBand->ulBandHigh;
    stSysCfg.stLBand.ulBandLow  &= pstUeSupportLteBand->ulBandLow;
#endif

    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    if (VOS_TRUE == MN_MMA_IsSpecRatSupported(TAF_MMA_RAT_LTE))
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    {
        stSysCfg.enUserPrio = TAF_MMA_USER_SET_PRIO_NOCHANGE;
    }
    else
    {
        stSysCfg.enUserPrio = TAF_MMA_USER_SET_PRIO_AUTO;
    }

    /* ����refresh�Ľ��뼼�����½��뼼�� */
    stSysCfg.stRatOrder  = stCurRatModeOrder;

    /* Modified by l00301449 for Iteration 13, 2015-04-09, begin */

    TAF_MMA_SndInterSysCfgSetReq(&stSysCfg);

#if 0
    /* ����MMA_PhSysCfgSetCmdCheck��ȡ���� */
    MMA_PhSysCfgSetCmdCheck(&stSysCfg, &usSetFlg, &ucAttachType, &ucDetachType);

    /* ����MN_MMA_SetSyscfg_EnableStatus����SYSCFG����  */
    MN_MMA_SetSyscfg_EnableStatus(&stSysCfg, TAF_MMA_SYSCFG_USER_USIM_REFRESH);
#endif
    /* Modified by l00301449 for Iteration 13, 2015-04-09, begin */

    return;
}
VOS_VOID TAF_MMA_ProcRatMode(TAF_MMA_RAT_MODE_ENUM_U8 enRatMode)
{
    if ((STA_FSM_STOP == g_StatusContext.ulFsmState)
     || (STA_FSM_NULL == g_StatusContext.ulFsmState))
    {
        /* �ػ���NULL״̬������ */
        MMA_NORMAILLOG("TAF_MMA_RcvRatModeFileRefresh(): Start Timer Fail");
    }
    else if (STA_FSM_ENABLE == g_StatusContext.ulFsmState)
    {
        /* ����SYSCFG���� */
        TAF_MMA_ProcRatMode_EnableStatus(enRatMode);
    }
    else
    {
        /* ����TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING��ʱ�� */

        TAF_MMA_StartTimer(TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING, TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING_LEN);

            TAF_MMA_SetTiTryingPeriodRatBalancingStatus(MMA_TIMER_RUN);
        }

    return;
}
VOS_UINT32 TAF_MMA_CheckRatModePara(
    TAF_MMA_RAT_ORDER_STRU             *pstCurRatModeOrder
)
{
    VOS_UINT8                           ucCardType;
    VOS_UINT32                          ulGForbbidenFlag;


    ucCardType = USIMM_CARD_NOCARD;

    ulGForbbidenFlag = MN_MMA_IsGOnlyMode(pstCurRatModeOrder);

    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucCardType) ;

#if (FEATURE_ON == FEATURE_LTE)

    /* �����SIM���������ó�L��ģʱ������ */
    if (VOS_TRUE == MN_MMA_IsLOnlyMode(pstCurRatModeOrder))
    {
        if (USIMM_CARD_SIM == ucCardType)
        {
            MMA_ERRORLOG("TAF_MMA_CheckRatModePara_PreProc: L ONLY & SIM CARD!");
            return VOS_TRUE;
        }
    }
#endif

    /* ���UE��֧��GSM�������ó�G��ģʱ������ʧ��; */
    if (VOS_TRUE == MMA_IsGsmForbidden())
    {
        if (VOS_TRUE == ulGForbbidenFlag)
        {
            MMA_ERRORLOG("TAF_MMA_CheckRatModePara_PreProc: G ONLY & FORBIDDEN!");
            return VOS_TRUE;
        }
    }

    /* SIM������Gģ��ֹ����ǰ���뼼��ΪGL����LG������ʧ�� */
    if ((USIMM_CARD_SIM == ucCardType)
     && (VOS_TRUE == ulGForbbidenFlag)
     && ((TAF_PH_MAX_GUL_RAT_NUM - 1) == pstCurRatModeOrder->ucRatOrderNum))
    {
        /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
        if ((TAF_MMA_RAT_LTE == pstCurRatModeOrder->aenRatOrder[0])
         && (TAF_MMA_RAT_GSM == pstCurRatModeOrder->aenRatOrder[1]))
        {
            return VOS_TRUE;
        }

        if ((TAF_MMA_RAT_GSM == pstCurRatModeOrder->aenRatOrder[0])
         && (TAF_MMA_RAT_LTE == pstCurRatModeOrder->aenRatOrder[1]))
        {
            return VOS_TRUE;
        }
        /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_MMA_RcvRatModeFileRefresh_PreProc(
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
)
{
    TAF_MMA_RAT_ORDER_STRU              stCurRatModeOrder;
    VOS_UINT32                          ulRatOrderChangedFlg;
    TAF_MMA_RAT_ORDER_STRU             *pstLastRatPrioList = VOS_NULL_PTR;


    /* �������ΪCL ģʽ����ֱ�ӷ��� */
    if (VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())
    {
        return VOS_TRUE;
    }

    /* ���뼼��ƽ����ƹ���δʹ�ܣ�ֱ�ӷ��� */
    if (VOS_FALSE == TAF_MMA_GetRatBalancingEnableFlg())
    {
        return VOS_TRUE;
    }

    /* ���ļ�����ֻ��һ��byte */
    if (usEfLen < TAF_MMA_RAT_MODE_FILE_LEN)
    {
        return VOS_TRUE;
    }

    /* ��4F36�ļ���PLMN MODEֵת����MMA�Ľ��뼼���б� */
    TAF_MMA_TransferRatMode(pucEf[0], &stCurRatModeOrder);

    /* ���뼼�����*/
    if (VOS_TRUE == TAF_MMA_CheckRatModePara(&stCurRatModeOrder))
    {
        return VOS_TRUE;
    }

    /* ����refresh�Ľ��뼼�� */
    TAF_MMA_SetRatMode_Refresh(pucEf[0]);

    /* TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING��ʱ���������У����� */
    if (MMA_TIMER_RUN == TAF_MMA_GetTiTryingPeriodRatBalancingStatus())
    {
        return VOS_TRUE;
    }

    pstLastRatPrioList = TAF_MMA_GetRatPrioListAddr();

    /* ��MN_MMA_GetRatPrioListAddr�еĽ��뼼���Ƚϣ����ı䣬ֱ�ӷ���*/
    ulRatOrderChangedFlg = TAF_MMA_IsUserSettedRatOrderChanged(&stCurRatModeOrder,
                                                              pstLastRatPrioList);

    /* ���뼼�����ı� */
    if (VOS_FALSE == ulRatOrderChangedFlg)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_VOID TAF_MMA_RcvRatModeFileRefresh(
    VOS_UINT16                          usEfLen,
    VOS_UINT8                          *pucEf
)
{
    /* Ԥ�������������Ҫ��һ������ */
    if (VOS_TRUE == TAF_MMA_RcvRatModeFileRefresh_PreProc(usEfLen, pucEf))
    {
        return;
    }

    /* ����4F36�ļ� */
    TAF_MMA_ProcRatMode(pucEf[0]);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetIccIdChangedFlg
 ��������  : �жϵ�ǰIccId�Ƿ����仯
 �������  : VOS_UINT8                                ucIsCardRefresh,
             NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8      enCsimStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��27��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetIccIdChangedFlg(
    VOS_UINT8                                ucIsCardRefresh,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8      enCsimStatus
)
{
    VOS_UINT8                          *pucEf           = VOS_NULL_PTR;
    VOS_UINT32                          ulEfLen;
    TAF_SDC_ICCID_INFO_STRU            *pstIccIdInfo    = VOS_NULL_PTR;

    pstIccIdInfo                        = TAF_SDC_GetIccIdInfo();

    ulEfLen                             = 0;

    if (NAS_MSCC_PIF_CARD_STATUS_ABSENT != enCsimStatus)
    {
        /* ��ȡIccId */
        if (USIMM_API_SUCCESS == NAS_USIMMAPI_GetCachedFile(USIMM_ICCID_ID, &ulEfLen, &pucEf, USIMM_UNLIMIT_AUTO))
        {
            if ((ulEfLen        <= TAF_SDC_ICC_ID_MAX_NUM)
			 && (0              != ulEfLen)
             && (VOS_NULL_PTR   != pucEf))
            {
                if ((0          == PS_MEM_CMP(pucEf, pstIccIdInfo->aucIccId, ulEfLen))
                 && (ulEfLen    == pstIccIdInfo->ucLen))
                {
                    return ucIsCardRefresh;
                }

                TAF_SDC_SetIccIdInfo((VOS_UINT8)ulEfLen, pucEf);

                return VOS_TRUE;
            }
        }
    }

    if (VOS_TRUE    == TAF_MMA_IsValidIccId())
    {
        /* ˢ��Ϊ�޿�״̬ */
        TAF_MMA_InitSdcIccId();

        return VOS_TRUE;
    }

    return ucIsCardRefresh;
}



VOS_VOID TAF_MMA_RatBalancingCtrlTimerExpired(VOS_VOID)
{
    TAF_MMA_RAT_ORDER_STRU             *pstLastRatPrioList = VOS_NULL_PTR;
    TAF_MMA_RAT_ORDER_STRU              stCurRatModeOrder;
    VOS_UINT32                          ulRatOrderChangedFlg;

    /* ���¶�ʱ��״̬ */
    TAF_MMA_SetTiTryingPeriodRatBalancingStatus(MMA_TIMER_STOP);

    pstLastRatPrioList = TAF_MMA_GetRatPrioListAddr();

    /* ��4F36�ļ���PLMN MODEֵת����MMA�Ľ��뼼���б� */
    TAF_MMA_TransferRatMode(TAF_MMA_GetRatMode_Refresh(), &stCurRatModeOrder);

    /* ��MN_MMA_GetRatPrioListAddr�еĽ��뼼���Ƚϣ����ı䣬ֱ�ӷ���*/
    ulRatOrderChangedFlg = TAF_MMA_IsUserSettedRatOrderChanged(&stCurRatModeOrder,
                                                              pstLastRatPrioList);

    /* �����ı䣬��Ҫ����4F36�ļ� */
    if (VOS_TRUE == ulRatOrderChangedFlg)
    {
        TAF_MMA_ProcRatMode(TAF_MMA_GetRatMode_Refresh());
    }

    return;
}



VOS_VOID TAF_MMA_PlmnIdReport(
    TAF_PLMN_ID_STRU                   *pstPlmn
)
{
    TAF_MMA_PLMN_CHANGE_IND_STRU       *pstPlmnChangeInd = VOS_NULL_PTR;

    TAF_SDC_PLMN_ID_STRU               *pstPlmnId = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl = VOS_NULL_PTR;

    pstPlmnId = TAF_SDC_GetCurrCampPlmnId();


    /* plmnû�иı䣬���ϱ� */
    if ((pstPlmn->Mcc == pstPlmnId->ulMcc)
     && (pstPlmn->Mnc == pstPlmnId->ulMnc))
    {
        return;
    }

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    if ( VOS_TRUE != TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_PLMN))
    {
        return;
    }

    /* ������� */
    pstPlmnChangeInd = (TAF_MMA_PLMN_CHANGE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                        WUEPS_PID_MMA,
                                                        sizeof(TAF_MMA_PLMN_CHANGE_IND_STRU));
    if (VOS_NULL_PTR == pstPlmnChangeInd)
    {
        MMA_ERRORLOG("TAF_MMA_PlmnIdReport:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    /* ��ʼ������ */
    PS_MEM_SET((VOS_CHAR *)pstPlmnChangeInd + VOS_MSG_HEAD_LENGTH,
            0x00,
            (sizeof(TAF_MMA_PLMN_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH));


    /* ����ϱ��¼� */
    pstPlmnChangeInd->MsgHeader.ulMsgName              = ID_TAF_MMA_PLMN_CHANGE_IND;
    pstPlmnChangeInd->stCurPlmn.Mcc                    = pstPlmn->Mcc;
    pstPlmnChangeInd->stCurPlmn.Mnc                    = pstPlmn->Mnc;
    pstPlmnChangeInd->usClientId                       = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstPlmnChangeInd->ucOpId                           = MMA_OP_ID_INTERNAL;
    pstPlmnChangeInd->MsgHeader.ulReceiverPid          = WUEPS_PID_AT;

    MMA_PlmnId2Bcd(&(pstPlmnChangeInd->stCurPlmn));

    /* �¼��ϱ� */
    PS_SEND_MSG(WUEPS_PID_MMA, pstPlmnChangeInd);

    return;
}
VOS_VOID  TAF_MMA_SndOmGetCacheFile(
    VOS_UINT32                          ulFileId,
    VOS_UINT32                          ulFileLen,
    VOS_UINT8                          *pucFileContent
)
{
    TAF_MMA_GET_CACHE_FILE_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen = sizeof(TAF_MMA_GET_CACHE_FILE_STRU) + ulFileLen;

    pstMsg = (TAF_MMA_GET_CACHE_FILE_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        MMA_ERRORLOG("TAF_MMA_SndOmMsccTimerStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength        = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = ulFileId;

    pstMsg->ulFileLen                   = ulFileLen;

    PS_MEM_CPY(pstMsg->aucFileContent, pucFileContent, ulFileLen);

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

}


VOS_VOID  TAF_MMA_SndOmLocationStatus(VOS_VOID)
{
    MSG_HEADER_STRU                    *pstMsg = VOS_NULL_PTR;

    pstMsg = (MSG_HEADER_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(MSG_HEADER_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        MMA_ERRORLOG("TAF_MMA_SndOmLocationStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->ulLength        = 4;
    pstMsg->ulMsgName       = 0x9999;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

}


VOS_VOID  TAF_MMA_SndDrxTimerInfo( VOS_UINT8 ucDrxTimerStatus )
{
    TAF_MMA_DRX_TIMER_STAUTS_STRU        *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen = sizeof(TAF_MMA_DRX_TIMER_STAUTS_STRU)  ;

    pstMsg = (TAF_MMA_DRX_TIMER_STAUTS_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "TAF_MMA_SndDrxTimerInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength        = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = 0x8888;
    PS_MEM_SET(pstMsg->aucReserve,0x00,sizeof(pstMsg->aucReserve));
    pstMsg->ucDrxTimerStatus            = ucDrxTimerStatus;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

}



VOS_UINT32 TAF_MMA_IsPlatformSupportSpecUserRat(
    /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
    TAF_MMA_RAT_TYPE_ENUM_UINT8          enUserRat
    /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
)
{
    VOS_UINT32                          ulPlatformSuppFlg;
    VOS_UINT32                          ulGsmForbiddenFlg;

    ulPlatformSuppFlg = VOS_TRUE;

    switch (enUserRat)

    {
        /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
        case TAF_MMA_RAT_GSM:
            /* ����GSM���뼼��������Ҫ�ж�GSMӲ��Ƶ���Ƿ�֧�� */
            ulGsmForbiddenFlg = MMA_IsGsmForbidden();

            if ((VOS_FALSE == TAF_SDC_IsPlatformSupportGsm())
             || (VOS_TRUE == ulGsmForbiddenFlg))
            {
                ulPlatformSuppFlg = VOS_FALSE;
            }
            break;

        case TAF_MMA_RAT_WCDMA:
            if (VOS_FALSE == TAF_SDC_IsPlatformSupportUtran())
            {
                ulPlatformSuppFlg = VOS_FALSE;
            }
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case TAF_MMA_RAT_LTE:
            if (VOS_FALSE == TAF_SDC_IsPlatformSupportLte())
            {
                ulPlatformSuppFlg = VOS_FALSE;
            }
            break;
#endif


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case TAF_MMA_RAT_1X:
            if (VOS_FALSE == TAF_SDC_IsPlatformSupport1x())
            {
                ulPlatformSuppFlg = VOS_FALSE;
            }
            break;

        case TAF_MMA_RAT_HRPD:
            if (VOS_FALSE == TAF_SDC_IsPlatformSupportHrpd())
            {
                ulPlatformSuppFlg = VOS_FALSE;
            }
            break;
        /* Modified by h00313353 for Iteration 13, 2015-4-10, end */

#endif


        default :
            MMA_WARNINGLOG("TAF_MMA_IsPlatformSupportSpecUserRat:WARNING:invalid rat.");

            /* ��Ч���뼼��Ĭ�ϲ�֧�� */
            ulPlatformSuppFlg = VOS_FALSE;
            break;
    }

    return ulPlatformSuppFlg;
}


VOS_VOID TAF_MMA_DelPlatformUnsupportedRat(
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulPlatformSuppFlg;

    i = 0;

    if (pstRatPrioList->ucRatOrderNum > TAF_PH_MAX_GUL_RAT_NUM)
    {
        pstRatPrioList->ucRatOrderNum = TAF_PH_MAX_GUL_RAT_NUM;
    }

    /* ��pstRatPrioList��֧�ֽ��뼼�����б��������ƽ̨���뼼�������Ƿ�֧�� */
    while (i < pstRatPrioList->ucRatOrderNum)
    {
        ulPlatformSuppFlg = TAF_MMA_IsPlatformSupportSpecUserRat(pstRatPrioList->aenRatOrder[i]);

        /* �����֧�֣���Ҫɾ�������֧�֣����������һ�� */
        if (VOS_FALSE == ulPlatformSuppFlg)
        {
            /* Modified by h00313353 for Iteration 13, 2015-4-10, begin */
            pstRatPrioList->aenRatOrder[i] = TAF_MMA_RAT_BUTT;
            /* Modified by h00313353 for Iteration 13, 2015-4-10, end */
            /*lint -e961*/
            (VOS_VOID)PS_MEM_MOVE(&(pstRatPrioList->aenRatOrder[i]),
                        &(pstRatPrioList->aenRatOrder[i+1]),
                        (TAF_PH_MAX_GUL_RAT_NUM-i-1));
            /*lint +e961*/
            pstRatPrioList->ucRatOrderNum --;
        }
        else
        {
            i ++;
        }
    }

    return;
}

/* Deleted by k902809 for Iteration 11, 2015-3-23, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-23, end */


VOS_VOID TAF_MMA_FillCopnOperNameList(
    VOS_UINT32                          ulFromIndex,
    VOS_UINT16                          usPlmnNum,
    TAF_MMA_COPN_INFO_QRY_CNF_STRU     *pstCopnQryCnf
)
{
    VOS_UINT32                          ulLoop;
    TAF_PH_OPERATOR_NAME_STRU          *pstOperNameList   = VOS_NULL_PTR;
    TAF_PH_OPERATOR_NAME_TBL_STRU      *pstNetworkNameTbl = VOS_NULL_PTR;

    /*
       ��дgastNetworkNameTbl�д�ulFromIndex��ʼ��usPlmnNum��Ӫ����Ϣ��
       +COPN����ϱ���Ϣ����Ӫ�������б�
    */
    pstCopnQryCnf->usPlmnNum      = usPlmnNum;

    pstNetworkNameTbl             = TAF_MMA_GetNetworkNameTblAddr();
    pstNetworkNameTbl            +=  ulFromIndex;

    pstOperNameList               = (TAF_PH_OPERATOR_NAME_STRU *)pstCopnQryCnf->aucContent;

    for (ulLoop = 0; ulLoop < usPlmnNum; ulLoop++)
    {
        /*
        ����Ӫ�̵���Ϣ������+COPN�ϱ���Ϣ��: �������͵�PLMN����Ӫ�̳���
        Ϊ��߽ӿڵĿ���չ�ԣ���Ӫ�̶���Ҳ����Ϣ�з���
        */
        pstOperNameList->PlmnId.Mcc = pstNetworkNameTbl->PlmnId.Mcc;
        pstOperNameList->PlmnId.Mnc = pstNetworkNameTbl->PlmnId.Mnc;

        /* ��Ӫ�̵�MNC���Ȳ�Ϊ3ʱ��������λ����ΪF */
        if (TAF_MMA_PLMN_MNC_TWO_BYTES == pstNetworkNameTbl->ucMncLength)
        {
            pstOperNameList->PlmnId.Mnc |= TAF_MMA_PLMN_MNC_DIGIT3_MASK;
        }

        (VOS_VOID)VOS_StrNCpy(pstOperNameList->aucOperatorNameShort,
                   pstNetworkNameTbl->pStrOperatorNameShort,
                   TAF_PH_OPER_NAME_SHORT);

        (VOS_VOID)VOS_StrNCpy(pstOperNameList->aucOperatorNameLong,
                   pstNetworkNameTbl->pStrOperatorNameLong,
                   TAF_PH_OPER_NAME_LONG);

        pstNetworkNameTbl ++;
        pstOperNameList ++;
    }

    return;
}
/* Deleted by k902809 for Iteration 11, 2015-3-24, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-24, end */

VOS_VOID TAF_MMA_SaveCellAcInfo(
    MSCC_MMA_AC_INFO_CHANGE_IND_STRU    *pstAcInfoInd
)
{
    TAF_SDC_ACCESS_RESTRICTION_STRU     stAcRestriction;

    PS_MEM_SET(&stAcRestriction, 0, sizeof(stAcRestriction));

    stAcRestriction.enCellAcType              = pstAcInfoInd->enCellAcType;
    stAcRestriction.ucRestrictPagingRsp       = pstAcInfoInd->ucRestrictPagingRsp;
    stAcRestriction.ucRestrictRegister        = pstAcInfoInd->ucRestrictRegister;

    if (NAS_MSCC_PIF_SRVDOMAIN_CS == pstAcInfoInd->enCnDomainId)
    {
        TAF_SDC_SetCsAcRestriction(&stAcRestriction);
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_PS == pstAcInfoInd->enCnDomainId)
    {
        TAF_SDC_SetPsAcRestriction(&stAcRestriction);
    }
    else
    {
        MMA_ERRORLOG("TAF_MMA_SaveCellAcInfo:ERROR:Unexpected src domain.");
    }


    return;
}

/* TAF_MMA_InitCellAcInfo�ƶ�λ�� */

VOS_UINT32 TAF_MMA_RcvMsccAcInfoChangeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_AC_INFO_CHANGE_IND_STRU    *pstAcInfoChangeInd = VOS_NULL_PTR;
    MSCC_MMA_AC_INFO_CHANGE_IND_STRU   *pstRcvAcInfoChangeInd = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl     = VOS_NULL_PTR;

    pstCurcRptCtrl = TAF_SDC_GetCurcRptCtrl();

    pstRcvAcInfoChangeInd = (MSCC_MMA_AC_INFO_CHANGE_IND_STRU*)pstMsg;

    TAF_MMA_SaveCellAcInfo(pstRcvAcInfoChangeInd);

    if (VOS_TRUE != TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                              TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                              TAF_SDC_RPT_CMD_ACINFO))
    {
        return VOS_TRUE;
    }

    pstAcInfoChangeInd = (TAF_MMA_AC_INFO_CHANGE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                            WUEPS_PID_MMA,
                                                            sizeof(TAF_MMA_AC_INFO_CHANGE_IND_STRU));

    if (VOS_NULL_PTR == pstAcInfoChangeInd)
    {
        return VOS_TRUE;
    }

    PS_MEM_SET( ((VOS_UINT8 *)pstAcInfoChangeInd + VOS_MSG_HEAD_LENGTH), 0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_AC_INFO_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH) );


    pstAcInfoChangeInd->ulReceiverPid                       = WUEPS_PID_AT;
    pstAcInfoChangeInd->ulMsgName                           = ID_TAF_MMA_AC_INFO_CHANGE_IND;
    pstAcInfoChangeInd->ucOpId                              = MMA_OP_ID_INTERNAL;
    pstAcInfoChangeInd->usClientId                          = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);

    pstAcInfoChangeInd->stCellAcInfo.enCellAcType           = pstRcvAcInfoChangeInd->enCellAcType;
    pstAcInfoChangeInd->stCellAcInfo.ucRestrictPagingRsp    = pstRcvAcInfoChangeInd->ucRestrictPagingRsp;
    pstAcInfoChangeInd->stCellAcInfo.ucRestrictRegister     = pstRcvAcInfoChangeInd->ucRestrictRegister;

    if (NAS_MSCC_PIF_SRVDOMAIN_CS == pstRcvAcInfoChangeInd->enCnDomainId)
    {
        pstAcInfoChangeInd->stCellAcInfo.enSrvDomain  = TAF_MMA_SERVICE_DOMAIN_CS;
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_PS == pstRcvAcInfoChangeInd->enCnDomainId)
    {
        pstAcInfoChangeInd->stCellAcInfo.enSrvDomain  = TAF_MMA_SERVICE_DOMAIN_PS;
    }
    else
    {
        MMA_ERRORLOG("TAF_MMA_RcvMsccAcInfoChangeInd:ERROR:Unexpected srv domain.");
    }

    /* Sending message */
    PS_SEND_MSG(WUEPS_PID_MMA, pstAcInfoChangeInd);

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_IsModeChangeNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    VOS_UINT32                              ulChkCurcRptFlg;
    VOS_UINT32                              ulChkUnsolicitedRptFlg;

    pstCurcRptCtrl              = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl       = TAF_SDC_GetUnsolicitedRptCtrl();

    ulChkCurcRptFlg             = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_MODE);

    ulChkUnsolicitedRptFlg      = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_MODE);

    /* CURC��^mode������Ϊ�����ϱ���ʱ������Ҫ�ϱ� */
    if ( (VOS_FALSE == ulChkCurcRptFlg)
     ||  (VOS_FALSE == ulChkUnsolicitedRptFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_IsServStatusChangeNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    VOS_UINT32                              ulChkCurcRptFlg;
    VOS_UINT32                              ulChkUnsolicitedRptFlg;

    pstCurcRptCtrl                  = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl           = TAF_SDC_GetUnsolicitedRptCtrl();

    ulChkCurcRptFlg                 = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_SRVST);

    ulChkUnsolicitedRptFlg          = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_SRVST);

    /* CURC��^srvst������Ϊ�����ϱ���ʱ������Ҫ�ϱ� */
    if ( (VOS_FALSE == ulChkCurcRptFlg)
     ||  (VOS_FALSE == ulChkUnsolicitedRptFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_IsRssiChangeNeedRpt(VOS_VOID)
{
    VOS_UINT32                              ulChkRssiCurcFlg;
    VOS_UINT32                              ulChkRssiUnsolicitedFlg;
    VOS_UINT32                              ulChkCerssiCurcFlg;
    VOS_UINT32                              ulChkCerssiUnsolicitedFlg;
    VOS_UINT32                              ulChkAnlevelCurcFlg;
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstCurcRptCtrl              = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl       = TAF_SDC_GetUnsolicitedRptCtrl();

    ulChkRssiCurcFlg            = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_RSSI);

    ulChkRssiUnsolicitedFlg     = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_RSSI);

    ulChkCerssiCurcFlg          = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_CERSSI);

    ulChkCerssiUnsolicitedFlg   = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CERSSI);

    ulChkAnlevelCurcFlg          = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_ANLEVEL);

    /* RSSI��Ҫ�ϱ� */
    if ( (VOS_TRUE == ulChkRssiCurcFlg)
      && (VOS_TRUE == ulChkRssiUnsolicitedFlg) )
    {
        return VOS_TRUE;
    }

    /* CERSSI��Ҫ�ϱ� */
    if ( (VOS_TRUE == ulChkCerssiCurcFlg)
      && (VOS_TRUE == ulChkCerssiUnsolicitedFlg) )
    {
        return VOS_TRUE;
    }

    /* ANLEVEL��Ҫ�ϱ� */
    if (VOS_TRUE == ulChkAnlevelCurcFlg)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 TAF_MMA_IsTimeChangeNeedRpt(VOS_VOID)
{
    VOS_UINT32                              ulChkTimeCurcFlg;
    VOS_UINT32                              ulChkTimeUnsolicitedFlg;
    VOS_UINT32                              ulChkCtzvCurcFlg;
    VOS_UINT32                              ulChkCtzvUnsolicitedFlg;
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstCurcRptCtrl              = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl       = TAF_SDC_GetUnsolicitedRptCtrl();

    ulChkTimeCurcFlg            = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_TIME);

    ulChkTimeUnsolicitedFlg     = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_TIME);

    ulChkCtzvCurcFlg            = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_CTZV);

    ulChkCtzvUnsolicitedFlg     = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CTZV);

    /* TIME��Ҫ�ϱ� */
    if ( (VOS_TRUE == ulChkTimeCurcFlg)
      && (VOS_TRUE == ulChkTimeUnsolicitedFlg) )
    {
        return VOS_TRUE;
    }

    /* CTZV��Ҫ�ϱ� */
    if ( (VOS_TRUE == ulChkCtzvCurcFlg)
      && (VOS_TRUE == ulChkCtzvUnsolicitedFlg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_MMA_IsSimStaChangeNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU             *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    VOS_UINT32                              ulChkCurcRptFlg;
    VOS_UINT32                              ulChkUnsolicitedRptFlg;

    pstCurcRptCtrl                  = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl           = TAF_SDC_GetUnsolicitedRptCtrl();

    ulChkCurcRptFlg                 = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_SIMST);

    ulChkUnsolicitedRptFlg          = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_SIMST);

    /* simst��Ҫ�ϱ� */
    if ( (VOS_TRUE == ulChkCurcRptFlg)
      && (VOS_TRUE == ulChkUnsolicitedRptFlg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 TAF_MMA_IsRegRejChangeNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;

    pstCurcRptCtrl   = TAF_SDC_GetCurcRptCtrl();

    if (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                              TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                              TAF_SDC_RPT_CMD_REJINFO))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_UINT32 TAF_MMA_IsPlmnSelectInfoNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;

    pstCurcRptCtrl   = TAF_SDC_GetCurcRptCtrl();

    if (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                              TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                              TAF_SDC_RPT_CMD_PLMNSELEINFO))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_UINT32 TAF_MMA_IsRegStatusChangeNeedRpt(
    TAF_PH_REG_STATE_STRU                  *pstRegState
)
{
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU      *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstUnsolicitedRptCtrl           = TAF_SDC_GetUnsolicitedRptCtrl();

    /* creg ��Ҫ�ϱ� */
    if ( (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CREG))
      && (VOS_TRUE == pstRegState->OP_CsRegState) )
    {
        return VOS_TRUE;
    }

    /* cgreg ��Ҫ�ϱ� */
    if ( (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CGREG))
      && (VOS_TRUE == pstRegState->OP_PsRegState) )
    {
        return VOS_TRUE;
    }

    /* cereg ��Ҫ�ϱ� */
    if ( (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CEREG))
      && (VOS_TRUE == pstRegState->OP_PsRegState) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8 TAF_MMA_GetRegDomain(VOS_VOID)
{
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8                   enAllowedRegDomain;
    VOS_UINT8                                               ucAutoAttachFlg;
    NAS_NVIM_AUTOATTACH_STRU                            stAutoattachFlag;
    VOS_UINT32                                              ulLength;

    ulLength = 0;
    PS_MEM_SET(&stAutoattachFlag, 0x00, sizeof(NAS_NVIM_AUTOATTACH_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_Autoattach, &ulLength);
    if (NV_OK == NV_Read(en_NV_Item_Autoattach,
                         (VOS_VOID*)(&stAutoattachFlag),
                         ulLength))
    {
        if (NV_ITEM_ACTIVE == stAutoattachFlag.usAutoattachFlag)
        {
            ucAutoAttachFlg = MMA_AUTO_ATTACH_ENABLE;
        }
        else
        {
            ucAutoAttachFlg = MMA_AUTO_ATTACH_DISABLE;
        }
    }
    else
    {
        ucAutoAttachFlg = MMA_AUTO_ATTACH_ENABLE;
    }

    switch (g_StatusContext.ucModeService)
    {
        case TAF_PH_MS_CLASS_A:
            enAllowedRegDomain = NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS_PS;

            if (MMA_AUTO_ATTACH_DISABLE == ucAutoAttachFlg)
            {
                 enAllowedRegDomain = NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS;
            }
            break;

        case TAF_PH_MS_CLASS_CG:
            enAllowedRegDomain = NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_PS;

            if (MMA_AUTO_ATTACH_DISABLE == ucAutoAttachFlg)
            {
                enAllowedRegDomain = NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_NULL;
            }
            break;

        case TAF_PH_MS_CLASS_CC:
            enAllowedRegDomain = NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS;
            break;

        case TAF_PH_MS_CLASS_NULL:
            enAllowedRegDomain = NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_NULL;
            break;

        default:
            enAllowedRegDomain = NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_NULL;
            break;
    }

    return enAllowedRegDomain;
}


 VOS_UINT32 TAF_MMA_HexAlpha2AsciiString(
    VOS_UINT32                      ulDestLength,
    VOS_UINT8                      *pucDst,
    VOS_UINT8                      *pucSrc,
    VOS_UINT16                      usSrcLen)
 {
    VOS_UINT16                     usLen;
    VOS_UINT16                     usChkLen;
    VOS_UINT8                     *pWrite = VOS_NULL_PTR;
    VOS_UINT8                     *pRead = VOS_NULL_PTR;
    VOS_UINT8                      ucHigh;
    VOS_UINT8                      ucLow;

    usLen       = 0;
    usChkLen    = 0;
    pWrite      = pucDst;
    pRead       = pucSrc;
    ucHigh      = 0;
    ucLow       = 0;

    if((2 * usSrcLen)>= ulDestLength)
    {
        TAF_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "MM_HexAlpha2AsciiString too long");
        return 0;
    }
    /*lint -e961*/
    if(0 != usSrcLen)
    {
        /* ɨ�������ִ� */
        while( usChkLen++ < usSrcLen )
        {
            ucHigh = 0x0F & (*pRead >> 4);
            ucLow = 0x0F & *pRead;

            usLen += 2;    /* ��¼���� */

            if(0x09 >= ucHigh)   /* 0-9 */
            {
                *pWrite++ = ucHigh + 0x30;
            }
            else if(0x0A <= ucHigh)    /* A-F */
            {
                *pWrite++ = ucHigh + 0x37;
            }
            else
            {
            }

            if(0x09 >= ucLow)   /* 0-9 */
            {
                *pWrite++ = ucLow + 0x30;
            }
            else if(0x0A <= ucLow)    /* A-F */
            {
                *pWrite++ = ucLow + 0x37;
            }
            else
            {
            }

             /* ��һ���ַ� */
            pRead++;
        }

    }
    /*lint +e961*/
    return usLen;
 }
VOS_VOID TAF_MMA_DefaultAlphaToAscii(
    VOS_UINT8                          *pucDefAlpha,
    VOS_UINT8                           ucDefAlphaLen,
    VOS_UINT8                          *pucAsciiChar
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucPos;
    VOS_UINT16                          usDecode;

    for (ucLoop = 0; ucLoop < ucDefAlphaLen; ucLoop++)
    {
        ucPos           = 0x7f & pucDefAlpha[ucLoop];
        usDecode        = f_ausMnAsciiSfxDefAlpha[ucPos];
        /* �ο����:�ڵ��ֽڲ��ܱ�ʾʱ,ʹ��?���д��� */
        if (usDecode > 0x00ff)
        {
            *pucAsciiChar = '?';
        }
        else
        {
            *pucAsciiChar = (VOS_UINT8)usDecode;
        }

        pucAsciiChar++;
    }

    return;
}
VOS_UINT32 TAF_MMA_TranslateNtwkName2Str(
    TAF_SDC_OPERATOR_NAME_STRU      *pstIeNtwkName,
    VOS_CHAR                        *pucNtwkName,
    VOS_UINT32                       ulLen
)
{
    VOS_UINT8                       ucIeLen;
    VOS_UINT8                       ucCodScheme;
    VOS_UINT8                       uc7BitCharNum;
    VOS_UINT8                      *pTmpNtwkName;
    VOS_UINT8                      *pucDecodeNwName;
    VOS_UINT8                       ucSpareBit;

    VOS_UINT32                      ulRslt;

    /*lint -e961*/
    ucIeLen         = pstIeNtwkName->ucLength;
    /*lint +e961*/
    ucCodScheme     = pstIeNtwkName->bitCoding;
    /* ���BIT */
    ucSpareBit      = pstIeNtwkName->bitSpare;
    pTmpNtwkName    = &pstIeNtwkName->aucOperatorName[0];

    if (0 == ucIeLen)
    {
        return VOS_FALSE;
    }

    if (ulLen == 0)
    {
        return VOS_FALSE;
    }

    if (0 == ucCodScheme)
    {
        /* 7Bit������� */
        uc7BitCharNum   = (VOS_UINT8)(((ucIeLen) * 8) / 7);
        if (uc7BitCharNum < ulLen)
        {
            pucDecodeNwName = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_MMA, ulLen);
            if (VOS_NULL_PTR == pucDecodeNwName)
            {
                TAF_LOG(WUEPS_PID_MMA, VOS_NULL, PS_LOG_LEVEL_WARNING, "TAF_MMA_TranslateNtwkName2Str: Alloc memory fail.");
                return VOS_FALSE;
            }

            ulRslt = TAF_STD_UnPack7Bit(pTmpNtwkName, uc7BitCharNum, 0, pucDecodeNwName);

            if (VOS_OK != ulRslt)
            {
                MMA_WARNINGLOG("TAF_MMA_TranslateNtwkName2Str: TAF_STD_UnPack7Bit Err.");
            }

            /* ��7�����BIT,���һ���ֽڽ�����������Ч����Ҫ�����ݳ��ȼ�1 */
            if ((ucSpareBit == 7) && (uc7BitCharNum > 0))
            {
                uc7BitCharNum -= 1;
            }
            TAF_MMA_DefaultAlphaToAscii(pucDecodeNwName, uc7BitCharNum, (VOS_UINT8 *)pucNtwkName);

            MMA_FREE_MEM(pucDecodeNwName);
            return VOS_TRUE;
        }
    }

    /* Ϊ�˷���Ӧ�öԽӣ��˴�����֧�������������� */
    return VOS_FALSE;

}

/* Deleted by k902809 for Iteration 11, 2015-3-30, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-30, end */


/* Deleted by k902809 for Iteration 11, 2015-3-27, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-27, end */

/* Deleted by k902809 for Iteration 11, 2015-3-24, begin */



/* TAF_MMA_ReadSpnFile */




VOS_UINT32 TAF_MMA_IsUsimStatusChange_UsimmCardServiceAbsent(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enPreSimStatus
)
{
    switch ( enPreSimStatus )
    {
        /* ��ǰSDC�п�״̬����Ч�ģ�����Ϊ��Ҫ���� */
        case TAF_SDC_USIM_STATUS_NO_PRESENT :
        case TAF_SDC_USIM_STATUS_SIM_PIN :
        case TAF_SDC_USIM_STATUS_SIM_PUK :
        case TAF_SDC_USIM_STATUS_NET_LCOK :
        case TAF_SDC_USIM_STATUS_IMSI_LCOK :
        case TAF_SDC_USIM_STATUS_READY_TIMEROUT:
            return VOS_FALSE;

        /* ������Ҫ���� */
        default:
            return VOS_TRUE;
    }

}
VOS_UINT32 TAF_MMA_IsUsimStatusChange_UsimmCardServiceAvailable(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enPreSimStatus
)
{
    switch ( enPreSimStatus )
    {
        /* ��ǰSDC�п�״̬����Ч�ģ�����Ϊ��Ҫ���� */
        case TAF_SDC_USIM_STATUS_VALID :
        case TAF_SDC_USIM_STATUS_CS_UNVALID :
        case TAF_SDC_USIM_STATUS_PS_UNVALID :
        case TAF_SDC_USIM_STATUS_CS_PS_UNVALID :
        case TAF_SDC_USIM_STATUS_ROMSIM :

            return VOS_FALSE;

        /* ������Ҫ���� */
        default:
            return VOS_TRUE;
    }
}


VOS_UINT32 TAF_MMA_IsUsimStatusChange_UsimmCardServiceSimPin(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enPreSimStatus
)
{
    switch ( enPreSimStatus )
    {
        /* ��ǰSDC�п�״̬����Ч������Ϊ�ı䣬��Ҫ���� */
        case TAF_SDC_USIM_STATUS_VALID :
        case TAF_SDC_USIM_STATUS_CS_UNVALID :
        case TAF_SDC_USIM_STATUS_PS_UNVALID :
        case TAF_SDC_USIM_STATUS_CS_PS_UNVALID :
        case TAF_SDC_USIM_STATUS_ROMSIM :

        case TAF_SDC_USIM_STATUS_BUTT:

            return VOS_TRUE;

        /* ���򶼲���Ҫ���� */
        default:
            return VOS_FALSE;
    }

}
#if (FEATURE_MULTI_MODEM == FEATURE_ON)

VOS_VOID TAF_MMA_SndMtcPowerStateInd(MTC_MODEM_POWER_STATE_ENUM_UINT8 enPowerState)
{
    VOS_UINT16                          ulLenth;
    MMA_MTC_POWER_STATE_IND_STRU       *pstPowerState = VOS_NULL_PTR;

    ulLenth = sizeof(MMA_MTC_POWER_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstPowerState  = (MMA_MTC_POWER_STATE_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLenth);
    if (VOS_NULL_PTR == pstPowerState)
    {
        MN_ERR_LOG("TAF_MMA_SndMtcPowerStateInd: Alloc Msg Failed!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstPowerState + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstPowerState->stMsgHeader.ulReceiverPid      = UEPS_PID_MTC;
    pstPowerState->stMsgHeader.ulMsgName          = ID_MMA_MTC_POWER_STATE_IND;
    pstPowerState->enPowerState                   = enPowerState;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstPowerState))
    {
        MN_ERR_LOG("TAF_MMA_SndMtcPowerStateInd: Snd Msg Failed!");
    }

    return;

}


VOS_VOID TAF_MMA_SndMtcRatModeInd(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode,
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
)
{
    MMA_MTC_RAT_MODE_IND_STRU          *pstRatMode = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    pstRatMode = (MMA_MTC_RAT_MODE_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(MMA_MTC_RAT_MODE_IND_STRU));
    if( VOS_NULL_PTR == pstRatMode )
    {
        MN_ERR_LOG("TAF_MMA_SndMtcRatModeInd: Alloc Msg Failed!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstRatMode + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_MTC_RAT_MODE_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstRatMode->stMsgHeader.ulReceiverPid   = UEPS_PID_MTC;
    pstRatMode->stMsgHeader.ulMsgName       = ID_MMA_MTC_RAT_MODE_IND;

    switch (enSysMode)
    {
        case TAF_SDC_SYS_MODE_GSM:
            pstRatMode->enRatMode = MTC_RATMODE_GSM;
            break;
        case TAF_SDC_SYS_MODE_WCDMA:
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == enUtranMode)
            {
                pstRatMode->enRatMode = MTC_RATMODE_WCDMA;
            }
            else
            {
                pstRatMode->enRatMode = MTC_RATMODE_TDS;
            }
            break;
        case TAF_SDC_SYS_MODE_LTE:
            pstRatMode->enRatMode = MTC_RATMODE_LTE;
            break;
        default:
            pstRatMode->enRatMode = MTC_RATMODE_BUTT;
            break;
    }

    ulResult = PS_SEND_MSG(WUEPS_PID_MMA, pstRatMode);
    if( VOS_OK != ulResult )
    {
        MN_ERR_LOG("TAF_MMA_SndMtcRatModeInd: Send Msg Failed!");
    }

    return;
}

VOS_VOID TAF_MMA_SndMtcRegStatusInd(VOS_UINT8 ucIsUsimValidFlag)
{
    VOS_UINT16                          ulLenth;
    MMA_MTC_REG_STATUS_IND_STRU        *pstMsg = VOS_NULL_PTR;

    ulLenth = sizeof(MMA_MTC_REG_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstMsg  = (MMA_MTC_REG_STATUS_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLenth);
    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("TAF_MMA_SndMtcRegStatusInd: Alloc Msg Failed!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_MTC;
    pstMsg->stMsgHeader.ulMsgName        = ID_MMA_MTC_REG_STATUS_IND;
    pstMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid      = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength         = sizeof(MMA_MTC_REG_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->ucIsUsimValidFlg             = ucIsUsimValidFlag;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstMsg))
    {
        MN_ERR_LOG("TAF_MMA_SndMtcRegStatusInd: Snd Msg Failed!");
    }

    return;
}



VOS_VOID TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_STATE_ENUM_UINT8 enPowerState)
{
    VOS_UINT16                          ulLenth;
    MMA_MTC_IMSA_STATE_IND_STRU        *pstImsaState = VOS_NULL_PTR;

    ulLenth = sizeof(MMA_MTC_IMSA_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstImsaState  = (MMA_MTC_IMSA_STATE_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLenth);
    if (VOS_NULL_PTR == pstImsaState)
    {
        MN_ERR_LOG("TAF_MMA_SndMtcImsaStateInd: Alloc Msg Failed!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstImsaState + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstImsaState->stMsgHeader.ulReceiverPid      = UEPS_PID_MTC;
    pstImsaState->stMsgHeader.ulMsgName          = ID_MMA_MTC_IMSA_STATE_IND;
    pstImsaState->enPowerState                   = enPowerState;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstImsaState))
    {
        MN_ERR_LOG("TAF_MMA_SndMtcImsaStateInd: Snd Msg Failed!");
    }

    return;

}

#endif

/* Added by w00316404 for NEXT B26 Project, 2015-6-17, begin */
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndMtcImsVoiceCapInd
 ��������  : MMA��MTC����IMS VOICE CAP֪ͨ
 �������  : ucAvail---IMS VOICE�Ƿ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��17��
    ��    ��   : w00316404
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MMA_SndMtcImsVoiceCapInd(
    VOS_UINT8                           ucAvail
)
{
    MMA_MTC_IMS_VOICE_CAP_IND_STRU     *pstMsg      = VOS_NULL_PTR;
    VOS_UINT16                          ulLenth;

    ulLenth = sizeof(MMA_MTC_IMS_VOICE_CAP_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����ڴ�  */
    pstMsg  = (MMA_MTC_IMS_VOICE_CAP_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMA, ulLenth);

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndMtcImsVoiceCapInd: Alloc Msg Failed!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    pstMsg->stMsgHeader.ulReceiverPid           = UEPS_PID_MTC;
    pstMsg->stMsgHeader.ulMsgName               = ID_MMA_MTC_IMS_VOICE_CAP_IND;
    pstMsg->enImsVoiceCap                       = (MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8)ucAvail;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstMsg))
    {
        MN_ERR_LOG("TAF_MMA_SndMtcImsVoiceCapInd: Snd Msg Failed!");
    }

    return;
}
#endif
/* Added by w00316404 for NEXT B26 Project, 2015-6-17, end */

#if (VOS_WIN32 == VOS_OS_VER)

VOS_VOID TAF_MMA_SetSimLockStatus(VOS_UINT8 ucSimLockStatus)
{
    g_stMmaMePersonalisationStatus.SimLockStatus = ucSimLockStatus;

}
#endif
/* Deleted by k902809 for Iteration 11, 2015-3-24, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-24, end */

VOS_UINT32 TAF_MMA_RcvMsccEOPlmnSetCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by k902809 for Iteration 11, 2015-3-24, begin */
    TAF_MMA_EOPLMN_SET_CNF_STRU        *pstEOPlmnSetCnf = VOS_NULL_PTR;
    MSCC_MMA_EOPLMN_SET_CNF_STRU       *pstMsccMsg      = VOS_NULL_PTR;

    pstMsccMsg   = (MSCC_MMA_EOPLMN_SET_CNF_STRU *)pstMsg;

    pstEOPlmnSetCnf = (TAF_MMA_EOPLMN_SET_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                     WUEPS_PID_MMA,
                                                     sizeof(TAF_MMA_EOPLMN_SET_CNF_STRU));
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-24, end */

    if (VOS_NULL_PTR == pstEOPlmnSetCnf)
    {
        MN_ERR_LOG("TAF_MMA_RcvMsccEOPlmnSetCnf: Alloc Msg Failed!");
        return VOS_TRUE;
    }

    PS_MEM_SET( (VOS_UINT8 *)pstEOPlmnSetCnf + VOS_MSG_HEAD_LENGTH, 0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_EOPLMN_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH) );

    pstEOPlmnSetCnf->ulReceiverPid          = WUEPS_PID_AT;
    pstEOPlmnSetCnf->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstEOPlmnSetCnf->ulResult               = pstMsccMsg->ulResult;
    pstEOPlmnSetCnf->usClientId             = MN_GetRealClientId(gstMmaValue.stEOPlmnSet.usClientId, WUEPS_PID_TAF);
    pstEOPlmnSetCnf->ucOpId                 = gstMmaValue.stEOPlmnSet.ucOpId;

    /* �����Ϣͷ */
    /* Modified by k902809 for Iteration 11, 2015-3-24, begin */
    pstEOPlmnSetCnf->ulMsgName              = ID_TAF_MMA_EOPLMN_SET_CNF;

    PS_SEND_MSG(WUEPS_PID_MMA, pstEOPlmnSetCnf);
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-24, end */

    return VOS_TRUE;
}
/* Deleted by k902809 for Iteration 11, 2015-3-30, begin */

/* Deleted by k902809 for Iteration 11, Iteration 11 2015-3-30, end */

VOS_VOID  TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(
    PWC_CLIENT_ID_E                     enPwcClientId
)
{
   VOS_UINT32                           ulRslt;
   PWC_CLIENT_ID_E                      enClientId;

#if defined(INSTANCE_1)
    switch (enPwcClientId)
    {
        case PWRCTRL_SLEEP_NAS:
            enClientId = PWRCTRL_SLEEP_NAS_1;
            break;

        case PWRCTRL_SLEEP_FTM:
            enClientId = PWRCTRL_SLEEP_FTM_1;
            break;

        default:
            enClientId = enPwcClientId;
            break;
    }
#elif defined (INSTANCE_2)
    switch (enPwcClientId)
    {
        case PWRCTRL_SLEEP_NAS:
            enClientId = PWRCTRL_SLEEP_NAS_2;
            break;

        case PWRCTRL_SLEEP_FTM:
            enClientId = PWRCTRL_SLEEP_FTM_2;
            break;

        default:
            enClientId = enPwcClientId;
            break;
    }
#else
    enClientId = enPwcClientId;
#endif

    ulRslt = mdrv_pm_wake_unlock(enClientId);

    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        (VOS_VOID)vos_printf("\n*TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK:enClientId = %d\n", enClientId);
    }


    TAF_MMA_LogDrvApiPwrCtrlSleepVoteUnlock(ulRslt, enClientId);
}




VOS_VOID  TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(
    PWC_CLIENT_ID_E                     enPwcClientId
)
{
   VOS_UINT32                           ulRslt;
   PWC_CLIENT_ID_E                      enClientId;

#if defined(INSTANCE_1)

    switch (enPwcClientId)
    {
        case PWRCTRL_SLEEP_NAS:
            enClientId = PWRCTRL_SLEEP_NAS_1;
            break;

        case PWRCTRL_SLEEP_FTM:
            enClientId = PWRCTRL_SLEEP_FTM_1;
            break;

        default:
            enClientId = enPwcClientId;
            break;
    }
#elif defined (INSTANCE_2)
        switch (enPwcClientId)
        {
            case PWRCTRL_SLEEP_NAS:
                enClientId = PWRCTRL_SLEEP_NAS_2;
                break;

            case PWRCTRL_SLEEP_FTM:
                enClientId = PWRCTRL_SLEEP_FTM_2;
                break;

            default:
                enClientId = enPwcClientId;
                break;
        }
#else
    enClientId = enPwcClientId;
#endif

    ulRslt = mdrv_pm_wake_lock(enClientId);

    TAF_MMA_LogDrvApiPwrCtrlSleepVoteLock(ulRslt, enClientId);


    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        (VOS_VOID)vos_printf("\n*TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK:enClientId = %d\n", enClientId);
    }

}


VOS_VOID TAF_MMA_UpdateSimRegStatus(VOS_VOID)
{
    TAF_SDC_USIM_STATUS_ENUM_UINT8      ucSimStatus;

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    VOS_UINT32                          ulOldUsimValidStatus;
    VOS_UINT32                          ulNewUsimValidStatus;

    ulOldUsimValidStatus = TAF_SDC_IsUsimStausValid();
#endif

    ucSimStatus = TAF_SDC_GetSimStatus();

    if ((TAF_SDC_USIM_STATUS_VALID  == ucSimStatus)
     || (TAF_SDC_USIM_STATUS_ROMSIM == ucSimStatus))
    {
        TAF_SDC_SetSimCsRegStatus(VOS_TRUE);
        TAF_SDC_SetSimPsRegStatus(VOS_TRUE);
    }
    else
    {
        TAF_SDC_SetSimCsRegStatus(VOS_FALSE);
        TAF_SDC_SetSimPsRegStatus(VOS_FALSE);
    }

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    ulNewUsimValidStatus = TAF_SDC_IsUsimStausValid();

    /* ���cs ps��״̬�����ı���Ҫ֪ͨmtc */
    if (ulOldUsimValidStatus != ulNewUsimValidStatus)
    {
        TAF_MMA_SndMtcRegStatusInd((VOS_UINT8)ulNewUsimValidStatus);
    }
#endif

    return;
}
VOS_VOID TAF_MMA_ReportSrvStatus(VOS_VOID)
{
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enSrvStatus;

    /* �ж��Ƿ���Ҫ�����ϱ�����״̬ */
    if (VOS_FALSE == TAF_MMA_IsServStatusChangeNeedRpt())
    {
        return;
    }

    enSrvStatus = TAF_SDC_GetServiceStatus();

    TAF_MMA_SndSrvStatusInd(enSrvStatus);

    return;
}
VOS_VOID TAF_MMA_StartNetScanProtectTimer(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    ulRet = VOS_OK;

    /* ��ʱ���������У�������ʱ�� */
    if (MMA_TIMER_RUN != g_stNetScanProtectTimer.ucTimerStatus)
    {
        ulRet = NAS_StartRelTimer(&g_stNetScanProtectTimer.MmaHTimer,
                                  WUEPS_PID_MMA,
                                  TI_TAF_MMA_NET_SCAN_TIMER_LEN,
                                  TAF_MMA,
                                  TI_TAF_MMA_NET_SCAN_TIMER,
                                  VOS_RELTIMER_NOLOOP );

        if( VOS_OK !=  ulRet)
        {
            MMA_WARNINGLOG("TAF_MMA_NetScanProtectTimerProc():ERROR:Start TI_TAF_MMA_PNN_LIST_MEM_PROTECT_TIMER Timer Error!");
        }
        else
        {
            g_stNetScanProtectTimer.ucTimerStatus = MMA_TIMER_RUN;
        }
    }

    return;
}
VOS_VOID TAF_MMA_StopNetScanProtectTimer(VOS_VOID)
{
    /* ��ʱ��������ֹͣ״̬����ֹͣ��ʱ�� */
    if ( MMA_TIMER_RUN == g_stNetScanProtectTimer.ucTimerStatus )
    {
        (VOS_VOID)NAS_StopRelTimer(WUEPS_PID_MMA,
                                 TI_TAF_MMA_NET_SCAN_TIMER,
                                 &(g_stNetScanProtectTimer.MmaHTimer));
        /*����ֹͣ��ʱ����־*/
        g_stNetScanProtectTimer.ucTimerStatus = MMA_TIMER_STOP;
    }

    return;
}


VOS_UINT32 TAF_MMA_StartAbortNetScanProtectTimer(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    ulRet = VOS_OK;

    /* ������ʱ�� */
    if (MMA_TIMER_RUN != g_stAbortNetScanProtectTimer.ucTimerStatus)
    {
        ulRet = NAS_StartRelTimer(&g_stAbortNetScanProtectTimer.MmaHTimer,
                                  WUEPS_PID_MMA,
                                  TI_TAF_MMA_ABORT_NET_SCAN_TIMER_LEN,
                                  TAF_MMA,
                                  TI_TAF_MMA_ABORT_NET_SCAN_TIMER,
                                  VOS_RELTIMER_NOLOOP );

        if( VOS_OK !=  ulRet)
        {
            MMA_WARNINGLOG("TAF_MMA_AbortNetScanProtectTimerProc():ERROR:Start TI_TAF_MMA_ABORT_NET_SCAN_TIMER Timer Error!");
        }
        else
        {
            g_stAbortNetScanProtectTimer.ucTimerStatus = MMA_TIMER_RUN;
        }
    }

    return ulRet;
}
VOS_VOID TAF_MMA_StopAbortNetScanProtectTimer(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    ulRet = VOS_OK;

    /* ����ö�ʱ����������״̬����ֹͣ */
    if ( MMA_TIMER_RUN == g_stAbortNetScanProtectTimer.ucTimerStatus )
    {
        ulRet = NAS_StopRelTimer(WUEPS_PID_MMA,
                                 TI_TAF_MMA_ABORT_NET_SCAN_TIMER,
                                 &(g_stAbortNetScanProtectTimer.MmaHTimer));
        if (VOS_OK != ulRet)
        {
            MMA_WARNINGLOG("TAF_MMA_AbortNetScanProtectTimerProc():WARNING:NAS_StopRelTimer failed");
        }

        /*����ֹͣ��ʱ����־*/
        g_stAbortNetScanProtectTimer.ucTimerStatus = MMA_TIMER_STOP;
    }

    return;
}



VOS_VOID TAF_MMA_NetScanTimerExpired(VOS_VOID)
{
    TAF_MMA_StopNetScanProtectTimer();

    /* ��MSCC����ֹͣɨ������ */
    TAF_MMA_SndMsccAbortNetScanMsgReq();

    (VOS_VOID)TAF_MMA_StartAbortNetScanProtectTimer();

    return;
}
VOS_VOID TAF_MMA_AbortNetScanTimerExpired(VOS_VOID)
{
    /* Modified by k902809 for Iteration 11, 2015-3-25, begin */
    TAF_MMA_NET_SCAN_RESULT_ENUM_UINT8  enResult;
    TAF_MMA_NET_SCAN_CAUSE_ENUM_UINT8   enCause;
    TAF_MMA_NET_SCAN_CNF_STRU          *pstNetScanCnf = VOS_NULL_PTR;;

    enResult               = TAF_MMA_NET_SCAN_RESULT_FAILURE;
    enCause                = TAF_MMA_NET_SCAN_CAUSE_TIMER_EXPIRED;

    pstNetScanCnf = (TAF_MMA_NET_SCAN_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(TAF_MMA_NET_SCAN_CNF_STRU));
    if (VOS_NULL_PTR == pstNetScanCnf)
    {
        return;
    }

    PS_MEM_SET( (VOS_UINT8 *)pstNetScanCnf + VOS_MSG_HEAD_LENGTH, 0x00,
                (VOS_SIZE_T)(sizeof(TAF_MMA_NET_SCAN_CNF_STRU) - VOS_MSG_HEAD_LENGTH));

    TAF_MMA_StopAbortNetScanProtectTimer();

    /* �����Ϣͷ */
    pstNetScanCnf->ulSenderPid            = WUEPS_PID_MMA;
    pstNetScanCnf->ulSenderCpuId          = VOS_LOCAL_CPUID;
    pstNetScanCnf->ulReceiverPid          = WUEPS_PID_AT;
    pstNetScanCnf->ulReceiverCpuId        = VOS_LOCAL_CPUID;
    pstNetScanCnf->ulMsgName              = ID_TAF_MMA_NET_SCAN_CNF;

    pstNetScanCnf->usClientId             = gstMmaValue.stNetScan.usClientId;
    pstNetScanCnf->ucOpId                 = gstMmaValue.stNetScan.ucOpId;
    pstNetScanCnf->enResult               = enResult;
    pstNetScanCnf->enCause                = enCause;

    /* Sending message */
    PS_SEND_MSG(WUEPS_PID_MMA, pstNetScanCnf);

    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-25, end */
    return;
}

/* Deleted by k902809 for Iteration 11, 2015-3-25, begin */

/* Deleted by k902809 for Iteration 11, 2015-3-25, end */

#if (FEATURE_MULTI_MODEM == FEATURE_ON)

VOS_VOID TAF_MMA_SndMtcCurrCampPlmnInfoInd(
    MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU                   *pstPlmnInfo
)
{
    MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU                   *pstCurrCampPlmnInfo = VOS_NULL_PTR;
    VOS_UINT32                                              ulResult;

    pstCurrCampPlmnInfo = (MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                              WUEPS_PID_MMA,
                                              sizeof(MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU));

    if( VOS_NULL_PTR == pstCurrCampPlmnInfo )
    {
        MN_ERR_LOG("TAF_MMA_SndMtcCurrCampPlmnInfoInd: Alloc Msg Failed!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCurrCampPlmnInfo + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstCurrCampPlmnInfo->stMsgHeader.ulReceiverPid   = UEPS_PID_MTC;
    pstCurrCampPlmnInfo->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstCurrCampPlmnInfo->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCurrCampPlmnInfo->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCurrCampPlmnInfo->stMsgHeader.ulMsgName       = ID_MMA_MTC_CURR_CAMP_PLMN_INFO_IND;
    pstCurrCampPlmnInfo->enRatMode                   = pstPlmnInfo->enRatMode;
    pstCurrCampPlmnInfo->ucIsForbiddenPlmnFlag       = pstPlmnInfo->ucIsForbiddenPlmnFlag;
    pstCurrCampPlmnInfo->ucPsAttachAllowFlag         = pstPlmnInfo->ucPsAttachAllowFlag;
    pstCurrCampPlmnInfo->stPlmnId.ulMcc              = pstPlmnInfo->stPlmnId.ulMcc;
    pstCurrCampPlmnInfo->stPlmnId.ulMnc              = pstPlmnInfo->stPlmnId.ulMnc;
    pstCurrCampPlmnInfo->ucPsSupportFlg              = pstPlmnInfo->ucPsSupportFlg;

    ulResult = PS_SEND_MSG(WUEPS_PID_MMA, pstCurrCampPlmnInfo);

    if( VOS_OK != ulResult )
    {
        MN_ERR_LOG("TAF_MMA_SndMtcCurrCampPlmnInfoInd: Send Msg Failed!");
    }

    return;
}


VOS_VOID TAF_MMA_SndMtcSysInfo(
    VOS_UINT8                           ucIsFobbiddenPlmnFlag,
    VOS_UINT8                           ucPsSupportFlg
)
{
    MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU   stSndMtcPlmnInfo;
    TAF_SDC_PLMN_ID_STRU                  *pstCurrCampPlmnId = VOS_NULL_PTR;

    pstCurrCampPlmnId = TAF_SDC_GetCurrCampPlmnId();

    /* ��MTCģ���ϱ���ǰ����ģʽ */
    TAF_MMA_SndMtcRatModeInd(TAF_SDC_GetSysMode(), NAS_UTRANCTRL_GetCurrUtranMode());

    /* ֪ͨmtc ��ǰפ��������뼼�����Ƿ��ֹ��Ϣ */
    PS_MEM_SET(&stSndMtcPlmnInfo, 0, sizeof(stSndMtcPlmnInfo));
    TAF_MMA_ConvertRatModeToMtc(TAF_SDC_GetSysMode(), NAS_UTRANCTRL_GetCurrUtranMode(),
                                &stSndMtcPlmnInfo.enRatMode);

    stSndMtcPlmnInfo.ucIsForbiddenPlmnFlag  = ucIsFobbiddenPlmnFlag;
    stSndMtcPlmnInfo.ucPsAttachAllowFlag    = TAF_SDC_GetPsAttachAllowFlg();
    stSndMtcPlmnInfo.stPlmnId.ulMcc         = pstCurrCampPlmnId->ulMcc;
    stSndMtcPlmnInfo.stPlmnId.ulMnc         = pstCurrCampPlmnId->ulMnc;
    stSndMtcPlmnInfo.ucPsSupportFlg         = ucPsSupportFlg;
    TAF_MMA_SndMtcCurrCampPlmnInfoInd(&stSndMtcPlmnInfo);

    return;
}


VOS_VOID TAF_MMA_ConvertRatModeToMtc(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode,
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode,
    MTC_RATMODE_ENUM_UINT8             *pucRatMode
)
{
    switch (enSysMode)
    {
        case TAF_SDC_SYS_MODE_GSM:
            *pucRatMode = MTC_RATMODE_GSM;
            break;

        case TAF_SDC_SYS_MODE_WCDMA:
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == enUtranMode)
            {
                *pucRatMode = MTC_RATMODE_WCDMA;
            }
            else
            {
                *pucRatMode = MTC_RATMODE_TDS;
            }
            break;

        case TAF_SDC_SYS_MODE_LTE:
            *pucRatMode = MTC_RATMODE_LTE;
            break;
        default:
            *pucRatMode = MTC_RATMODE_BUTT;
            break;
    }

    return;
}

#endif



VOS_VOID TAF_MMA_BuildMmaCtrlInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_CTRL_STRU                  *pstCtrlInfo
)
{
    pstCtrlInfo->ulModuleId = ulModuleId;
    pstCtrlInfo->usClientId = usClientId;
    pstCtrlInfo->ucOpId     = ucOpId;

    return;
}


VOS_UINT32 TAF_MMA_IsPowerOnCLInterWork(VOS_VOID)
{
    /* ��ǰNV����Ϊ��CL������ģʽ */
    if (VOS_FALSE == TAF_SDC_IsConfigCLInterWorkCOutside())
    {
        return VOS_FALSE;
    }


    /* ģʽ����״̬��������,�򷵻�VOS_TRUE */
    if (TAF_MMA_FSM_PHONE_MODE == TAF_MMA_GetCurrFsmId())
    {
        return VOS_TRUE;
    }

    /* ģʽ״̬�����������ҵ�ǰ��Ϊ����ģʽ���򷵻�VOS_FALSE */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        return VOS_FALSE;
    }

    /* ��ǰΪ����ģʽ���򷵻�VOS_TRUE */
    return VOS_TRUE;
}


#if (FEATURE_MULTI_MODEM == FEATURE_ON)

VOS_UINT32 MMA_MTC_ConvertCardStatus(
    USIMM_CARD_SERVIC_ENUM_UINT32           enCardStatus,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16  *penDestCardStatus
)
{
    switch(enCardStatus)
    {
        case USIMM_CARD_SERVIC_ABSENT:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_ABSENT;
            break;

        case USIMM_CARD_SERVIC_UNAVAILABLE:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_UNAVAILABLE;
            break;

        case USIMM_CARD_SERVIC_SIM_PIN:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_SIM_PIN;
            break;

        case USIMM_CARD_SERVIC_SIM_PUK:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_SIM_PUK;
            break;

        case USIMM_CARD_SERVIC_NET_LCOK:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_NET_LCOK;
            break;

        case USIMM_CARD_SERVICE_IMSI_LOCK:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_IMSI_LCOK;
            break;

        case USIMM_CARD_SERVIC_AVAILABLE:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_AVAILABLE;
            break;

        default:
            *penDestCardStatus = TAF_MTC_USIMM_CARD_SERVIC_ABSENT;
            break;
    }

    return VOS_TRUE;
}
#endif

#if (FEATURE_ON == FEATURE_BASTET)

VOS_VOID TAF_MMA_SndBastetRatModeInd(
    TAF_SDC_SYS_MODE_ENUM_UINT8  enSysMode,
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranMode
)
{
    MMA_BASTET_RAT_MODE_IND_STRU       *pstRatMode = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    pstRatMode = (MMA_BASTET_RAT_MODE_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(MMA_BASTET_RAT_MODE_IND_STRU));
    if( VOS_NULL_PTR == pstRatMode )
    {
        MN_ERR_LOG("TAF_MMA_SndBastetRatModeInd: Alloc Msg Failed!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstRatMode + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_BASTET_RAT_MODE_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstRatMode->stMsgHeader.ulReceiverPid   = UEPS_PID_BASTET;
    pstRatMode->stMsgHeader.ulMsgName       = ID_MMA_BASTET_RAT_MODE_IND;

    switch (enSysMode)
    {
        case TAF_SDC_SYS_MODE_GSM:
            pstRatMode->enRatMode = BST_RATMODE_GSM;
            break;
        case TAF_SDC_SYS_MODE_WCDMA:
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == enUtranMode)
            {
                pstRatMode->enRatMode = BST_RATMODE_WCDMA;
            }
            else
            {
                pstRatMode->enRatMode = BST_RATMODE_TDS;
            }
            break;
        case TAF_SDC_SYS_MODE_LTE:
            pstRatMode->enRatMode = BST_RATMODE_LTE;
            break;
        default:
            pstRatMode->enRatMode = BST_RATMODE_BUTT;
            break;
    }

    ulResult = PS_SEND_MSG(WUEPS_PID_MMA, pstRatMode);
    if( VOS_OK != ulResult )
    {
        MN_ERR_LOG("TAF_MMA_SndBastetRatModeInd: Send Msg Failed!");
    }

    return;
}



VOS_VOID TAF_MMA_SndBastetCsServiceInd(PS_BOOL_ENUM_UINT8 bCSConnected)
{
    MMA_BASTET_CS_SERVICE_IND_STRU     *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    pstMsg = (MMA_BASTET_CS_SERVICE_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(MMA_BASTET_CS_SERVICE_IND_STRU));
    if( VOS_NULL_PTR == pstMsg )
    {
        MN_ERR_LOG("TAF_MMA_SndBastetCsServiceInd: Alloc Msg Failed!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_BASTET_CS_SERVICE_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_BASTET;
    pstMsg->stMsgHeader.ulMsgName       = ID_MMA_BASTET_CS_SERVICE_IND;
    pstMsg->bCSConnected                = bCSConnected;

    ulResult = PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);
    if( VOS_OK != ulResult )
    {
        MN_ERR_LOG("TAF_MMA_SndBastetCsServiceInd: Send Msg Failed!");
    }

    return;

}



VOS_VOID TAF_MMA_SndBastetServiceStatusInd(VOS_VOID)
{
    MMA_BASTET_SERVICE_STATUS_IND_STRU *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;


    pstMsg = (MMA_BASTET_SERVICE_STATUS_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                 WUEPS_PID_MMA,
                                                 sizeof(MMA_BASTET_SERVICE_STATUS_IND_STRU));
    if( VOS_NULL_PTR == pstMsg )
    {
        MN_ERR_LOG("TAF_MMA_SndBastetServiceStatusInd: Alloc Msg Failed!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(MMA_BASTET_SERVICE_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    pstMsg->stMsgHeader.ulReceiverPid   = UEPS_PID_BASTET;
    pstMsg->stMsgHeader.ulMsgName       = ID_MMA_BASTET_SERVICE_STATUE_IND;

    if(NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == TAF_SDC_GetCsServiceStatus())
    {
        pstMsg->bCsInservice            = PS_TRUE;
    }
    else
    {
        pstMsg->bCsInservice            = PS_FALSE;
    }


    if(NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == TAF_SDC_GetPsServiceStatus())
    {
        pstMsg->bPsInservice            = PS_TRUE;
    }
    else
    {
        pstMsg->bPsInservice            = PS_FALSE;
    }
    ulResult = PS_SEND_MSG(WUEPS_PID_MMA, pstMsg);
    if( VOS_OK != ulResult )
    {
        MN_ERR_LOG("TAF_MMA_SndBastetServiceStatusInd: Send Msg Failed!");
    }

    return;

}

#endif


#if (FEATURE_LTE == FEATURE_ON)

VOS_VOID TAF_MMA_GetRssiLevelFromLteRssi(
    VOS_INT16                           usLteRssi,
    VOS_UINT8                          *pucRssiLevel
)
{
    /* ��atSetCsqCnfSameProc������ͬ */
    if(TAF_PH_RSSIUNKNOW == usLteRssi)
    {
        *pucRssiLevel =  TAF_PH_RSSIUNKNOW;
    }
    else if(usLteRssi >= TAF_PH_RSSI_HIGH)
    {
        *pucRssiLevel = TAF_PH_CSQ_RSSI_HIGH;
    }
    else if(usLteRssi <= TAF_PH_RSSI_LOW)
    {
        *pucRssiLevel = TAF_PH_CSQ_RSSI_LOW;
    }
    else
    {
        *pucRssiLevel = (VOS_UINT8)((usLteRssi -TAF_PH_RSSI_LOW) / 2);
    }

    return;
}
#endif


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_MMA_QueryClSysInfo(
    TAF_PH_SYSINFO_STRU                *pstSysInfo
)
{
    /* ��ȡϵͳMode SubMode */
    TAF_MMA_ConvertSysInfoExSysMode(TAF_SDC_GetSysMode(), &pstSysInfo->ucSysMode);
    TAF_MMA_ConvertSysInfoExSysSubMode(TAF_SDC_GetSysSubMode(), &pstSysInfo->ucSysSubMode);


    /* ��ȡ���α�־ */
    if (TAF_SDC_SYS_ROAMING_STATUS_OFF == TAF_SDC_Get1xRoamingFlag())
    {
        pstSysInfo->ucRoamStatus = TAF_PH_INFO_NONE_ROMAING;
    }
    else
    {
        pstSysInfo->ucRoamStatus = TAF_PH_INFO_ROMAING;

    }

    pstSysInfo->ucSrvStatus  = TAF_SDC_GetServiceStatus();

    pstSysInfo->ucSrvDomain  = TAF_SDC_GetServiceDomain();

    MN_PH_GetSysInfoSrvStatus(pstSysInfo);

    /*To do: ĿǰSim��״̬δ֧�� */
    pstSysInfo->ucSimLockStatus = VOS_FALSE;

    pstSysInfo->ucSimStatus     = TAF_PH_USIM_STATUS_AVAIL;

    return;
}
VOS_VOID TAF_MMA_Report1xRegStatus(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegState,
    TAF_SDC_SERVICE_DOMAIN_ENUM_UINT8   enCnDomainId
)
{
    TAF_PH_REG_STATE_STRU               stRegStatus;

    PS_MEM_SET(&stRegStatus, 0, sizeof(TAF_PH_REG_STATE_STRU));

    if (TAF_SDC_SERVICE_DOMAIN_CS == enCnDomainId)
    {
        stRegStatus.OP_CsRegState = VOS_TRUE;
        stRegStatus.RegState      = enRegState;
        stRegStatus.ucAct         = TAF_PH_ACCESS_TECH_CDMA_1X;

        TAF_SDC_SetCsRegStatus(enRegState);
    }

    if (VOS_TRUE != TAF_MMA_IsRegStatusChangeNeedRpt(&stRegStatus))
    {
        return;
    }

    TAF_MMA_SndRegStatusInd(&stRegStatus);

    return;
}


VOS_VOID TAF_MMA_Report1xCregStatus(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegStatus
)
{
    /* CS��״̬�仯�󣬲Ż��ϱ�Creg AT���� */
    if (enRegStatus != TAF_SDC_GetCsRegStatus())
    {
        TAF_MMA_Report1xRegStatus(enRegStatus, TAF_SDC_SERVICE_DOMAIN_CS);
    }
}
VOS_VOID TAF_MMA_UpdataHrpdServiceStatusAndDomain(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
)
{
    /* update ps servcie status*/
    if ((TAF_SDC_SYS_MODE_EVDO == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))
    {
        TAF_SDC_SetPsServiceStatus(TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE);
    }
    else
    {
        TAF_SDC_SetPsServiceStatus(TAF_SDC_SERVICE_STATUS_NO_SERVICE);
    }

    /* update servcie domain */
    if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))
    {
        TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS_PS);
    }
    else if(TAF_SDC_SYS_MODE_EVDO == enSysMode)
    {
        TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_PS);
    }
    else
    {
        TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN);
    }

}


VOS_VOID TAF_MMA_ReprotCdmaServiceState(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus,
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
)
{
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    oldSrvSta;

    oldSrvSta = TAF_SDC_GetServiceStatus();

    /* process new SrvSta */
    if ((TAF_SDC_SYS_MODE_EVDO == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
    }
    else if(TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
    {
        if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStatus)
        {
            TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
        }
        else if(TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == enCsServiceStatus)
        {
            TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE);
        }
        else
        {
            /* should not happen */
            TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_NO_SERVICE);
        }
    }
    else
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_NO_SERVICE);
    }

    if (TAF_SDC_GetServiceStatus() != oldSrvSta)
    {
        /* ����^SRVST�����ϱ� */
        TAF_MMA_ReportSrvStatus();
    }
}
VOS_VOID TAF_MMA_Updata1xServiceStatusAndDomain(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus,
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
)
{
    /* update cs servcie status*/
    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStatus)
    {
        TAF_SDC_SetCsServiceStatus(TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE);
    }
    else if(TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == enCsServiceStatus)
    {
        TAF_SDC_SetCsServiceStatus(TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE);
    }
    else
    {
        TAF_SDC_SetCsServiceStatus(TAF_SDC_SERVICE_STATUS_NO_SERVICE);
    }

    /* update servcie domain */
    if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStatus)
     || (TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == enCsServiceStatus))
    {
        /* when ever there is 1x service, it implies */
        TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS_PS);
    }
    else
    {
        /* when no 1x service, hrpd should be taken into consideration */
        if (TAF_SDC_SYS_MODE_EVDO == enSysMode)
        {
            TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_PS);
        }
        else
        {
            TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN);
        }
    }

}

/* Deleted by y00322978 for CDMA Iteration 17, 2015-7-9, begin */

/* Deleted by y00322978 for CDMA Iteration 17, 2015-7-9, end */


VOS_VOID TAF_MMA_ReportCSid(
    VOS_INT32                          lSid
)
{
    TAF_MMA_CSID_IND_STRU              *pstCSidInd;

    pstCSidInd = (TAF_MMA_CSID_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                             sizeof(TAF_MMA_CSID_IND_STRU));
    if (VOS_NULL_PTR == pstCSidInd)
    {
        MMA_ERRORLOG("TAF_MMA_ReportCSidNid: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCSidInd + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_CSID_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    TAF_MMA_CFG_MSG_HDR(pstCSidInd,
                        WUEPS_PID_AT,
                        ID_TAF_MMA_CSID_IND);

    pstCSidInd->stCtrl.usClientId    = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstCSidInd->stCtrl.ucOpId        = MMA_OP_ID_INTERNAL;
    pstCSidInd->lSid                 = lSid;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstCSidInd);

    return;
}
/* Added by y00322978 for CDMA Iteration 17, 2015-7-14, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_Report1xEmcCallBack
 ��������  : mma �ϱ���APP callbackģʽ
 �������  : ulIsInCallBack �Ƿ���emc callbackģʽ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��14��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_Report1xEmcCallBack(
    VOS_UINT32                          ulIsInCallBack
)
{
    TAF_MMA_1X_EMC_CALL_BACK_NTF_STRU  *pstEmcCallBack;

    pstEmcCallBack = (TAF_MMA_1X_EMC_CALL_BACK_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                             sizeof(TAF_MMA_1X_EMC_CALL_BACK_NTF_STRU));
    if (VOS_NULL_PTR == pstEmcCallBack)
    {
        MMA_ERRORLOG("TAF_MMA_Report1xEmcCallBack: ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstEmcCallBack + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(TAF_MMA_1X_EMC_CALL_BACK_NTF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    TAF_MMA_CFG_MSG_HDR(pstEmcCallBack,
                        WUEPS_PID_AT,
                        ID_TAF_MMA_1X_EMC_CALL_BACK_NTF);

    pstEmcCallBack->stCtrl.usClientId               = MN_GetRealClientId(MMA_CLIENTID_BROADCAST, WUEPS_PID_TAF);
    pstEmcCallBack->stCtrl.ucOpId                   = MMA_OP_ID_INTERNAL;
    pstEmcCallBack->ulIsInCallBack                  = ulIsInCallBack;

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_MMA, pstEmcCallBack);

    return;
}
/* Added by y00322978 for CDMA Iteration 17, 2015-7-14, end */

VOS_VOID TAF_MMA_ConvertSysSubModeToActForAtCmdCgreg(
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSysSubMode,
    TAF_PH_ACCESS_TECH_ENUM_UINT8      *pucAct
)
{
    switch (enSysSubMode)
    {
        case TAF_SYS_SUBMODE_EVDO_REL_A:
        case TAF_SYS_SUBMODE_HYBRID_EVDO_REL_A:
            *pucAct = TAF_PH_ACCESS_TECH_EVDO;
            break;

        default:
            *pucAct = TAF_PH_ACCESS_TECH_BUTT;
            break;
    }

}

VOS_VOID TAF_MMA_ReportPsRegStatus(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enRegState,
    TAF_PH_ACCESS_TECH_ENUM_UINT8       enAct
)
{
    TAF_PH_REG_STATE_STRU               stRegStatus;

    PS_MEM_SET(&stRegStatus, 0, sizeof(TAF_PH_REG_STATE_STRU));

    if (enRegState == TAF_SDC_GetPsRegStatus())
    {
        /* no change no report */
        return;
    }

    /* set report values */
    stRegStatus.OP_PsRegState = VOS_TRUE;
    stRegStatus.OP_ucAct      = VOS_TRUE;
    stRegStatus.ucPsRegState  = enRegState;
    stRegStatus.ucAct         = enAct;
    TAF_SDC_SetPsRegStatus(enRegState);

    if (VOS_TRUE != TAF_MMA_IsRegStatusChangeNeedRpt(&stRegStatus))
    {
        return;
    }

    TAF_MMA_SndRegStatusInd(&stRegStatus);

    return;
}
#endif

/* Added by y00307564 for CDMA Iteration 8 2015-2-9 begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_GetPrefPlmnParaType
 ��������  : ��ȡplmn����
 �������  : MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPLMNType
 �������  : ��
 �� �� ֵ  : MMC_MMA_PARA_TYPE_ENUM
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��09��
    ��    ��   : y00307564
    �޸�����   : �����ɺ���
*****************************************************************************/
MMC_MMA_PARA_TYPE_ENUM TAF_MMA_GetPrefPlmnParaType(
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPLMNType
)
{
    if (MN_PH_PREF_PLMN_UPLMN == enPrefPLMNType)
    {
        if (VOS_TRUE == MN_PH_IsUsingPlmnSel())
        {
            return EN_MMC_PLMNSEL_INFO;
        }
        else
        {
            return EN_MMC_UPLMN_INFO;
        }
    }
    else if (MN_PH_PREF_PLMN_OPLMN == enPrefPLMNType)
    {
        return EN_MMC_OPLMN_INFO;
    }
    else
    {
        return EN_MMC_HPLMN_INFO;
    }
}
/* Added by y00307564 for CDMA Iteration 8 2015-2-9 end */

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


