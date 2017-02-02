

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "msp.h"
#include    "NasEmmPubUInclude.h"
#include    "LRrcLPhyInterface.h"
#include    "LPsOm.h"
#include    "EmmUeModeInterface.h"
#include    "SysNvId.h"
#include    "NVIM_Interface.h"
#include    "NasEmmSecuSmc.h"
#include    "NasNvInterface.h"
#include    "msp_nvim.h"
#include    "ScInterface.h"
/* add by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
#include    "NasCommSndOm.h"
/* add by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */
/* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-13, begin */
#include    "NasMmlCtx.h"
/* Added by g00322017 for SEARCH_NW_CHR_OPT, 2015-8-13, end */


/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMPUBUGLOBAL_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMPUBUGLOBAL_C
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

/*VOS_UINT32                              g_ulRatMode = 2;*/    /* PS_FIRST_CALL ʹ�� */
NAS_EMM_PUB_INFO_STRU                   g_stEmmInfo;
VOS_UINT32                              g_ulSmcControl      = NAS_EMM_SMC_CLOSE;
VOS_UINT32                              g_ulUeSecuCapMatch  = NAS_EMM_SMC_OPEN;

/*
VOS_UINT32                              g_ulDetachPowerOff  = NAS_EMM_DO_DETACH_WHEN_POWEROFF;
*/
/*VOS_UINT32                              g_ulAutoStartFlag   = NOT_AUTO_START;*/
VOS_UINT32                              g_ulAutoAttFlag     = NAS_EMM_AUTO_ATTACH_ALLOW;
VOS_UINT32                              g_ulCsAutoAttFlag   = NAS_EMM_AUTO_ATTACH_ALLOW;
NAS_LMM_SYSINFO_COUNT_STRU               g_stMsgSysInfCnt;

OM_EMM_STATE_INFO_STRU                   g_stEmmOmInfo;

#if (FEATURE_ON == FEATURE_DSDS)
NAS_LMM_SESSION_TYPE_MAP_STRU g_astDsdsCvtSessionTypeTbl[]=
{
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_CS_MO_NORMAL_CALL,        LRRC_LNAS_SESSION_TYPE_MO_NORMAL_CALL},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_CS_MO_EMERGENCY_CALL,     LRRC_LNAS_SESSION_TYPE_MO_EMERGENCY_CALL},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_CS_MO_SS,                 LRRC_LNAS_SESSION_TYPE_MO_SS},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_CS_MO_SMS,                LRRC_LNAS_SESSION_TYPE_MO_SMS},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_PS_CONVERSAT_CALL,        LRRC_LNAS_SESSION_TYPE_PS_CONVERSAT_CALL},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_PS_STREAM_CALL,           LRRC_LNAS_SESSION_TYPE_PS_STREAM_CALL},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_PS_INTERACT_CALL,         LRRC_LNAS_SESSION_TYPE_PS_INTERACT_CALL},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_PS_BACKGROUND_CALL,       LRRC_LNAS_SESSION_TYPE_PS_BACKGROUND_CALL},
    {WUEPS_PID_MMC,   MMC_LMM_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL, LRRC_LNAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL},

    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MO_NORMAL_CALL,            LRRC_LNAS_SESSION_TYPE_MO_NORMAL_CALL},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MO_EMERGENCY_CALL,         LRRC_LNAS_SESSION_TYPE_MO_EMERGENCY_CALL},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MO_SS,                     LRRC_LNAS_SESSION_TYPE_MO_SS},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MO_SMS,                    LRRC_LNAS_SESSION_TYPE_MO_SMS},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MT_NORMAL_CALL,            LRRC_LNAS_SESSION_TYPE_MT_NORMAL_CALL},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MT_SMS,                    LRRC_LNAS_SESSION_TYPE_MT_SMS},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MT_SS,                     LRRC_LNAS_SESSION_TYPE_MT_SS},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MO_NORMAL_CSFB,            LRRC_LNAS_SESSION_TYPE_MO_NORMAL_CSFB},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MO_EMERGENCY_CSFB,         LRRC_LNAS_SESSION_TYPE_MO_EMERGENCY_CSFB},
    {WUEPS_PID_MM,    MM_LMM_SESSION_TYPE_MT_CSFB,                   LRRC_LNAS_SESSION_TYPE_MT_CSFB},

    {WUEPS_PID_GMM,   GMM_LMM_SESSION_TYPE_MO_SMS,                   LRRC_LNAS_SESSION_TYPE_MO_SMS},
    {WUEPS_PID_GMM,   GMM_LMM_SESSION_TYPE_MT_SMS,                   LRRC_LNAS_SESSION_TYPE_MT_SMS},

    {PS_PID_ESM,      EMM_ESM_SESSION_TYPE_ESM,                      LRRC_LNAS_SESSION_TYPE_PS_ESM}
};

VOS_UINT32 g_astDsdsCvtSessionTypeTblLen = sizeof(g_astDsdsCvtSessionTypeTbl)
                                                                /sizeof(NAS_LMM_SESSION_TYPE_MAP_STRU);

/*ͳ���������Ϣ����*/
NAS_LMM_DSDS_MSG_COUNT_STRU  g_astDsdsNotifyMsgNum[LRRC_LNAS_SESSION_TYPE_BUTT];

/*ͳ���������Ϣ����*/
NAS_LMM_DSDS_MSG_COUNT_STRU  g_astDsdsInputNotifyMsgNum[NAS_EMM_INPUT_DSDS_MSG_NUM];

/*DSDS���ԣ�RF�����أ�vc����Ĭ�Ϲر�*/
#if (VOS_OS_VER != VOS_WIN32)
VOS_UINT32 g_ulDsdsRFSharedFlag = PS_TRUE;
#else
VOS_UINT32 g_ulDsdsRFSharedFlag = PS_FALSE;
#endif

#endif

VOS_UINT32  g_ulCsfbProcedureFlag = PS_FALSE;

LNAS_LMM_LTE_NO_SUBSCRIBE_CONFIG_STRU    stLteNoSubscribeConfig;
/* ��ά�ɲ��ϱ����ƿ��� */
LNAS_NV_OM_SWITCH_STRU g_stNasOmSwitch;
VOS_UINT32  g_aulNasFunFlg[8];

VOS_UINT32                       g_ulPtmsiTauActiveFlag = PS_FALSE;

/* ���������Ż����� */
VOS_UINT8                               g_ucLmmGradualForbFlag        = PS_FALSE;
NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST  g_stGradualForbTempForbTaList;
VOS_UINT32                              g_ulGradualForbTimerFirstLen  = 300 * 1000;
VOS_UINT32                              g_ulGradualForbTimerSecondLen = 1200 * 1000;
VOS_UINT32                              g_ulGradualForbAgingTimerLen  = 7200 * 1000;
VOS_UINT32                              g_ulGradualForbTaTimerPara    = 0;


/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/


VOS_VOID    NAS_LMM_EmmStateInit( VOS_VOID )
{

    NAS_LMM_FSM_STATE_STRU              *pEmmCurState;

    /* ��ǰ״̬��ʼ�� */
    pEmmCurState = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);
    pEmmCurState->enFsmId               = NAS_LMM_PARALLEL_FSM_EMM;
    pEmmCurState->enMainState           = EMM_MS_NULL;
    pEmmCurState->enSubState            = EMM_SS_NULL_WAIT_APP_START_REQ;
    pEmmCurState->enStaTId              = TI_NAS_EMM_STATE_NO_TIMER;

    return;
}
VOS_VOID    NAS_EMM_FsmInit(            VOS_VOID )
{

    NAS_LMM_FSM_STATE_STRU              *pEmmCurState;
    NAS_LMM_FSM_STATE_STACK_STRU        *pEmmStack;

    NAS_LMM_PUBM_LOG_NORM(
    "NAS_EMM_FsmInit                   START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_FsmInit_ENUM,LNAS_BEGIN);

    /* ��ǰ״̬��ʼ�� */
    pEmmCurState = NAS_LMM_GetCurFsmAddr(NAS_LMM_PARALLEL_FSM_EMM);
    pEmmCurState->enFsmId               = NAS_LMM_PARALLEL_FSM_EMM;
    pEmmCurState->enMainState           = EMM_MS_NULL;
    pEmmCurState->enSubState            = EMM_SS_NULL_WAIT_APP_START_REQ;
    pEmmCurState->enStaTId              = TI_NAS_EMM_STATE_NO_TIMER;


    /* ״̬��ջ ��ʼ�� */
    pEmmStack   = NAS_LMM_GetFsmStackAddr(NAS_LMM_PARALLEL_FSM_EMM);
    pEmmStack->ucStackDepth             = NAS_EMM_STACK_EMPTY;

    NAS_EMM_InitBufMsgQue();

    return;
}


VOS_VOID    NAS_EMM_PubmInfoUeIdInit(   VOS_VOID )
{
    /*IMSI,IMEI�����У����Գ�ʼ��UeId��Ч*/
    NAS_LMM_GetEmmInfoAddr()->bitOpUeId  = NAS_EMM_BIT_SLCT;

    NAS_LMM_GetEmmInfoUeidAddr()->bitOpTmsi     = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_GetEmmInfoUeidAddr()->bitOpPtmsi    = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_GetEmmInfoUeidAddr()->bitOpTmgiMbms = NAS_EMM_BIT_NO_SLCT;
    return;
}
VOS_VOID    NAS_EMM_PubmInfoNetInfoInit(VOS_VOID )
{
    /*��ʼ������Ϣ��Ч*/
    NAS_LMM_GetEmmInfoAddr()->bitOpNetInfo = NAS_EMM_BIT_SLCT;

    /*���IMSI��Ч��������Ч������HPLMN��Ч��MMC��ʼ��ʱ���㸳ֵ*/
    if (NAS_EMM_BIT_SLCT == NAS_LMM_GetEmmInfoUeidAddr()->bitOpImsi)
    {
        NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpHplmn = NAS_EMM_BIT_SLCT;
    }

    /*δ��������ǰ������Ϣ��Ч*/
    NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpPresentNetId = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_UndefPlmn(NAS_LMM_GetEmmInfoPresentPlmnAddr());

    /*δ�������ϴγ��Է���ע���TA��Ϣ��Ч*/
    NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpLastAttmpRegTa = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_UndefPlmn(NAS_LMM_GetEmmInfoLastAttmpRegPlmnAddr());


    /* ����ǰ������Ϣ��TAC��Cell ID��ʼ��Ϊ��Чֵ*/
    NAS_EMMC_DeleteCurrentAreaCellId();
    NAS_LMM_UndefTac(&(NAS_LMM_GetEmmInfoNetInfoPresentNetAddr()->stTac));

    /*ForbTaList For Roaming�ػ�ʱ����,�ϵ���Ч*/
    /*ForbTaList For Rpos�ػ�ʱ����,�ϵ���Ч*/
    NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpFoibTaForRoam = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpFoibTaForRpos = NAS_EMM_BIT_NO_SLCT;

    NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr()->ulTaNum = 0;
    NAS_LMM_GetEmmInfoNetInfoForbTaForRposAddr()->ulTaNum = 0;

    /*EHPLMN ListĿǰδʹ��,��ʼ����Ч*/
    NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpEHplmnList = NAS_EMM_BIT_NO_SLCT;


    /*L.V.R TAI��ʼ��*/
    NAS_EMM_ClearLVRTai();

    return;
}
VOS_VOID  NAS_EMM_PubmInfoDrxInit(VOS_VOID)
{
    /*PC REPLAY DEL BY LEILI */

    /*����DRX�ı��ʶ*/
    NAS_LMM_SetEmmInfoDrxNetCapChange(NAS_EMM_NO);
    NAS_EMM_SetDrxCycleLenChangeFlag(NAS_EMM_DRX_CYCLE_LEN_CHANGED);

    return;
}
/*PC REPLAY MODIFY BY LEILI BEGIN*/

VOS_UINT32  NAS_EMM_IsGuContainPsRegDrx(VOS_VOID)
{
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_IsGuContainPsRegDrx:NAS_MML_GetPsRegContainDrx =",
                           NAS_MML_GetPsRegContainDrx());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_IsGuContainPsRegDrx_ENUM,LNAS_FUNCTION_LABEL1,NAS_MML_GetPsRegContainDrx());
    #ifndef __PS_WIN32_RECUR__
    if (NAS_MML_GU_PS_REG_CONTAIN_DRX_PARA == NAS_MML_GetPsRegContainDrx())
    {
       NAS_LMM_LogPsRegContainDrxInfo(NAS_MML_GetPsRegContainDrx());
       return NAS_EMM_SUCC;
    }
    NAS_LMM_LogPsRegContainDrxInfo(NAS_MML_GetPsRegContainDrx());
    return NAS_EMM_FAIL;
    #else
    if (NAS_MML_GU_PS_REG_CONTAIN_DRX_PARA == Stub_NAS_MML_GetPsRegContainDrx())
    {
        return NAS_EMM_SUCC;
    }
    return NAS_EMM_FAIL;
    #endif
}
/*PC REPLAY MODIFY BY LEILI END*/

VOS_VOID  NAS_EMM_UpdateLteContainDrxFlag( VOS_VOID )
{
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_UpdateLteContainDrxFlag before:NAS_MML_GetPsRegContainDrx() = ",
                               NAS_MML_GetPsRegContainDrx());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_UpdateLteContainDrxFlag_ENUM,LNAS_FUNCTION_LABEL1,NAS_MML_GetPsRegContainDrx());
    if (NAS_EMM_YES == NAS_EMM_TAU_GetEmmTauContainDrxFlag())
    {
        NAS_MML_SetPsRegContainDrx(NAS_MML_LTE_PS_REG_CONTAIN_DRX_PARA);
    }
    else
    {
        NAS_MML_SetPsRegContainDrx(NAS_MML_LTE_PS_REG_NOT_CONTAIN_DRX_PARA);
    }
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_UpdateLteContainDrxFlag After:NAS_MML_GetPsRegContainDrx() = ",
                               NAS_MML_GetPsRegContainDrx());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_UpdateLteContainDrxFlag_ENUM,LNAS_FUNCTION_LABEL2,NAS_MML_GetPsRegContainDrx());
    return;
}








VOS_VOID    NAS_EMM_ReadNvUeNetCap(VOS_VOID)
{
    LNAS_LMM_NV_UE_NET_CAP_STRU         stNvUeNetCap;
    NAS_MM_UE_NET_CAP_STRU             *pstUeNetCap = VOS_NULL_PTR;
    NAS_EMM_PUB_INFO_STRU              *pstEmmInfo  = VOS_NULL_PTR;
    VOS_VOID                           *pData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;
    /* leixiantiao 2014-10-23 begin */
    #if (VOS_OS_VER != VOS_WIN32)
    FTM_TMODE_ENUM                      enMspFtmMode = EN_FTM_TMODE_SIGNAL ;
    #endif
    /* leixiantiao 2014-10-23 end */
    NAS_MML_UE_NETWORK_CAPABILITY_STRU  stUeNetworkCapbility = {0};

    /* ָ�� UeNetCap*/
    pstEmmInfo  = NAS_LMM_GetEmmInfoAddr();
    pstUeNetCap = NAS_LMM_GetEmmInfoSecuParaUeNetCapAddr();

    /* ��ʼ��д��MML��UeNetCapΪĬ��ֵ */
    /*stUeNetworkCapbility.bitOpUeNetCap      = NAS_EMM_BIT_SLCT;*/
    stUeNetworkCapbility.ucUeNetCapLen      = 0x05;

    stUeNetworkCapbility.aucUeNetCap[0]     = 0xF0;
    stUeNetworkCapbility.aucUeNetCap[1]     = 0xF0;
    stUeNetworkCapbility.aucUeNetCap[2]     = 0x40;
    stUeNetworkCapbility.aucUeNetCap[3]     = 0x40;
    stUeNetworkCapbility.aucUeNetCap[4]     = 0x0;

    /* ��ʼ������ȫ�ֱ���UeNetCapΪĬ��ֵ */
    pstEmmInfo->bitOpUeNetCap       = NAS_EMM_BIT_SLCT;
    pstUeNetCap->ucUeNetCapLen      = 0x05;

    pstUeNetCap->aucUeNetCap[0]     = 0xF0;
    pstUeNetCap->aucUeNetCap[1]     = 0xF0;

    pstUeNetCap->aucUeNetCap[2]     = 0x40;
    pstUeNetCap->aucUeNetCap[3]     = 0x40;
    pstUeNetCap->aucUeNetCap[4]     = 0x0;

#if (VOS_OS_VER != VOS_WIN32)
    /*�����ȡ��ǰģʽʧ�ܣ���Ĭ��Ϊ��ǰģʽΪEN_FTM_TMODE_SIGNAL����ӡ������Ϣ*/
    if(LPS_OM_GetTmode(&enMspFtmMode)!= ERR_MSP_SUCCESS)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_ReadNvUeNetCap : FTM_GetMode() called fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_ReadNvUeNetCap_ENUM,LNAS_FAIL);
    }
    else
    {
        /*���߲���ģʽ����ȡĬ��ֵ:0xE0,0xE0,0x40,0x40*/
        if( EN_FTM_TMODE_SIGNAL_NOCARD == enMspFtmMode)
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_EMM_ReadNvUeNetCap : EN_FTM_TMODE_SIGNAL_NOCARD, UE NetCap is 0xe0,0xe0!");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUeNetCap_ENUM,LNAS_FUNCTION_LABEL1);

            /* ��Ĭ��ֵд��MML */
            NAS_MML_SetUeNetWorkCapability(&stUeNetworkCapbility);

            return;
        }
    }
#endif
    /*read UE NET CAP from NVIM*/
    pData = (VOS_VOID *)&(stNvUeNetCap);
    usDataLen = sizeof(LNAS_LMM_NV_UE_NET_CAP_STRU);

    ulRslt = NAS_LMM_NvimRead(EN_NV_ID_UE_NET_CAPABILITY, pData, &usDataLen);

    /* ��ȡ NVIM�ɹ� */
    if((NAS_LMM_NVIM_OK == ulRslt) && (NAS_EMM_BIT_SLCT == stNvUeNetCap.bitOpUeNetCap))
    {
        /*��֤��ȡ���ݵ���Ч��:Ŀǰ�׶�ֻ��֤���ȷ���Э�顣
          ����ʵ�ֻ���Ҫ����EEA,EIA,UEA,UIA��ȡֵ���뿪��֧�ֵĽ��뼼���Ƿ���ϣ�
          ���翪��ָʾ֧��L��U�������ȡ��UEA,UIA��֧���κ��㷨������Ϊ������Ч��
          �����ģʽ����֤��Ŀǰ�׶���δʵ��
        */
        if ((NAS_MM_MIN_UE_NET_CAP_LEN <= stNvUeNetCap.stUeNetCap.ucUeNetCapLen)
            && (NAS_MM_MAX_UE_NET_CAP_LEN >= stNvUeNetCap.stUeNetCap.ucUeNetCapLen))
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUeNetCap:NV value is Valid");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUeNetCap_ENUM,LNAS_FUNCTION_LABEL2);
            pstEmmInfo->bitOpUeNetCap           = NAS_EMM_BIT_SLCT;
            NAS_LMM_MEM_CPY(    pstUeNetCap,
                                &(stNvUeNetCap.stUeNetCap),
                                sizeof(NAS_MM_UE_NET_CAP_STRU));

            /* ����д��MML��UeNetCapΪNV�ж�ȡ����ֵ */
            NAS_LMM_MEM_SET(    &stUeNetworkCapbility,
                                0,
                                sizeof(NAS_MML_UE_NETWORK_CAPABILITY_STRU));

            stUeNetworkCapbility.ucUeNetCapLen = stNvUeNetCap.stUeNetCap.ucUeNetCapLen;
            NAS_LMM_MEM_CPY(    &(stUeNetworkCapbility.aucUeNetCap[0]),
                                &(stNvUeNetCap.stUeNetCap.aucUeNetCap[0]),
                                stUeNetworkCapbility.ucUeNetCapLen);
        }
        /* NVIM�ж�ȡ��������Ч����ΪĬ��ֵ*/
        else
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUeNetCap:Nv value is Invalid");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUeNetCap_ENUM,LNAS_FUNCTION_LABEL3);
        }
    }
    /* ��ȡ NVIM ʧ�ܣ���ΪĬ��ֵ*/
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_ReadNvUeNetCap:Read Net Cap Fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_ReadNvUeNetCap_ENUM,LNAS_FUNCTION_LABEL4);
    }

    /* ���UeNetCap��ȡ�ɹ�������NV�õ���ֵд��MML�����ʧ�ܣ�д��Ĭ��ֵ */
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUeNetCap: Set to MML UeNetCap value is:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUeNetCap_ENUM,LNAS_FUNCTION_LABEL5);
    NAS_MML_SetUeNetWorkCapability(&stUeNetworkCapbility);

    NAS_COMM_PrintArray(    NAS_COMM_GET_MM_PRINT_BUF(),
                            (VOS_UINT8*)&stUeNetworkCapbility,
                            sizeof(NAS_MML_UE_NETWORK_CAPABILITY_STRU));

    return;
}




VOS_VOID  NAS_EMM_ReadNvVoiceDomain(VOS_VOID )
{
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo;
#if (FEATURE_ON == FEATURE_IMS)
    LNAS_LMM_NV_VOICE_DOMAIN_STRU       stNvVoiceDomain;
    VOS_VOID                           *pData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;
#endif
    pstPubInfo = NAS_LMM_GetEmmInfoAddr();
    pstPubInfo->bitOpVoiceDomain      = NAS_EMM_BIT_SLCT;
    pstPubInfo->ulVoiceDomain         = NAS_LMM_VOICE_DOMAIN_CS_ONLY;
    NAS_MML_SetVoiceDomainPreference(NAS_LMM_VOICE_DOMAIN_CS_ONLY);
#if (FEATURE_ON == FEATURE_IMS)
    pData                               = (VOS_VOID *)&(stNvVoiceDomain);
    usDataLen = sizeof(LNAS_LMM_NV_VOICE_DOMAIN_STRU);

    ulRslt = NAS_LMM_NvimRead(          EN_NV_ID_UE_VOICE_DOMAIN,
                                        pData,
                                        &usDataLen);

    /*sunbing 49683 2013-10-28 VoLTE begin*/
    if((EN_NV_OK == ulRslt) && (stNvVoiceDomain.bitOpVoicDomain == NAS_EMM_BIT_SLCT))
    {
        NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_ReadNvVoiceDomain: read NV success.",
            stNvVoiceDomain.enVoicDomain);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ReadNvVoiceDomain_ENUM,LNAS_EMM_VOICE_DOMAIN,stNvVoiceDomain.enVoicDomain);

        if (NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED >= stNvVoiceDomain.enVoicDomain)
        {
            pstPubInfo->bitOpVoiceDomain = NAS_EMM_BIT_SLCT;
            pstPubInfo->ulVoiceDomain = stNvVoiceDomain.enVoicDomain;
            /* lihong00150010 csfb begin */

            NAS_MML_SetVoiceDomainPreference((VOS_UINT8)pstPubInfo->ulVoiceDomain);

        }
        else
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvVoiceDomain:NV Value is Invalid");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvVoiceDomain_ENUM,LNAS_PARAM_INVALID);
            pstPubInfo->bitOpVoiceDomain  = NAS_EMM_BIT_SLCT;
            pstPubInfo->ulVoiceDomain     = NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED;

            NAS_MML_SetVoiceDomainPreference(NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED);

        }
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvVoiceDomain: read NV err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvVoiceDomain_ENUM,LNAS_ERROR);
        pstPubInfo->bitOpVoiceDomain      = NAS_EMM_BIT_SLCT;
        pstPubInfo->ulVoiceDomain         = NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED;

        NAS_MML_SetVoiceDomainPreference(NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED);

    }
    /*sunbing 49683 2013-10-28 VoLTE end*/
#endif
    return;
}
VOS_VOID  NAS_EMM_ReadNvNasRelease(VOS_VOID )
{
    LNAS_LMM_NV_NAS_RELEASE_STRU        stNvNasRelease;
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo;
    VOS_VOID                           *pData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();
    pData                               = (VOS_VOID *)&(stNvNasRelease);
    usDataLen = sizeof(LNAS_LMM_NV_NAS_RELEASE_STRU);

    ulRslt = NAS_LMM_NvimRead(          EN_NV_ID_NAS_RELEASE,
                                        pData,
                                        &usDataLen);

    if((EN_NV_OK == ulRslt)
        && (stNvNasRelease.bitOpReleaseName  == NAS_EMM_BIT_SLCT))
    {

        NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_ReadNvNasRelease: read NV success.",
            stNvNasRelease.ulReleaseName);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ReadNvNasRelease_ENUM,LNAS_FUNCTION_LABEL1,
            stNvNasRelease.ulReleaseName);

        pstPubInfo->ulNasRelease = stNvNasRelease.ulReleaseName;
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvNasRelease: read NV err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvNasRelease_ENUM,LNAS_ERROR);
        pstPubInfo->ulNasRelease        = 0x00000900;

    }

    return;
}

/*sunbing 49683 2013-10-21 VoLTE begin*/
/*****************************************************************************
 Function Name   : NAS_EMM_ReadNvUmtsCodecInfo
 Description     : ��NV���ȡUmts codec֧����Ϣ
                   �ο�MN_CALL_FillUmtsSupCodecList,MN_CALL_UmtsCapaProcInit��ʵ��
 Input           : None
 Output          : None
 Return          : None

 History         :
    1.sunbing 49683      2013-10-21  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ReadNvUmtsCodecInfo(NAS_EMM_SUPPORT_CODEC_UNION *punCodecList)
{
    VOS_UINT8       aucNvCodecInfo[NAS_EMM_MAX_UMTS_CODEC_TYPE_NUM+1];/*codec����+����codec��Ϣ*/
    VOS_UINT32      ulDefaultValue;
    VOS_UINT32      i;
    VOS_UINT16      usDataLen;

    NAS_LMM_MEM_SET(aucNvCodecInfo, 0x00, sizeof(aucNvCodecInfo));

    ulDefaultValue          = VOS_FALSE;

    usDataLen               = sizeof(aucNvCodecInfo);

    /*����NV�Ľṹ��ԭʼ����ΪMN_CALL_UMTS_CODEC_TYPE_STRU��codec����+����codec��Ϣ*/
    if ( NAS_LMM_NVIM_OK != NAS_LMM_NvimRead(en_NV_Item_UMTS_CODEC_TYPE,
                                   aucNvCodecInfo,
                                   &usDataLen))
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUmtsCodecInfo: read NV err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUmtsCodecInfo_ENUM,LNAS_ERROR);
        ulDefaultValue = VOS_TRUE;
    }

    /* ���NVIM�еĲ����Ƿ�Ϸ�,���Ϸ���ʹ��Ĭ��ֵ,�����Ƿ�Խ�� */
    if ( aucNvCodecInfo[0] > NAS_EMM_MAX_UMTS_CODEC_TYPE_NUM )
    {
        ulDefaultValue     = VOS_TRUE;

        aucNvCodecInfo[0]  = NAS_EMM_MAX_UMTS_CODEC_TYPE_NUM;

        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUmtsCodecInfo: Codec num is err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUmtsCodecInfo_ENUM,LNAS_FUNCTION_LABEL1);

    }

    /* ����Ƿ����ظ�����ͳ�����Χ��codec����*/
    for ( i = 0; i < aucNvCodecInfo[0]; i++ )
    {
        switch ( aucNvCodecInfo[i+1])
        {
            case NAS_EMM_UMTS_CODEC_TYPE_AMR :
                punCodecList->stSupportCodec.CodecType_UMTSAMR     = VOS_TRUE;
                break;

            case NAS_EMM_UMTS_CODEC_TYPE_AMR2 :
                punCodecList->stSupportCodec.CodecType_UMTSAMR2     = VOS_TRUE;
                break;

            case NAS_EMM_UMTS_CODEC_TYPE_AMRWB :
                punCodecList->stSupportCodec.CodecType_UMTSAMRWB   = VOS_TRUE;
                break;

            default:
                NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUmtsCodecInfo: Codec Type is err.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUmtsCodecInfo_ENUM,LNAS_FUNCTION_LABEL2);
                ulDefaultValue = VOS_TRUE;
                break;
        }

        if(ulDefaultValue == VOS_TRUE)
        {
            /*NV���ݴ������*/
            punCodecList->usSupportCodec = 0;
            break;
        }

    }

    if ( VOS_TRUE == ulDefaultValue )
    {
        punCodecList->stSupportCodec.CodecType_UMTSAMR     = VOS_TRUE;
        punCodecList->stSupportCodec.CodecType_UMTSAMR2    = VOS_TRUE;
    }

}

/*****************************************************************************
 Function Name   : NAS_EMM_ReadNvGsmCodecInfo
 Description     : ��NV���ȡGsm codec֧����Ϣ
                   �ο�MN_CALL_FillGsmSupCodecList,MN_CALL_GsmCapaProcInit��ʵ��
 Input           : None
 Output          : None
 Return          : None

 History         :
    1.sunbing 49683      2013-10-21  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ReadNvGsmCodecInfo(NAS_EMM_SUPPORT_CODEC_UNION *punCodecList)
{
    VOS_UINT8       aucNvGsmCodecInfo[NAS_EMM_BC_MAX_SPH_VER_NUM + 2] ;/*codec����+����codec��Ϣ+1��spare byte*/
    VOS_UINT32      ulDefaultValue;
    VOS_UINT32      i;
    VOS_UINT16      usDataLen;

    NAS_LMM_MEM_SET(aucNvGsmCodecInfo, 0x00, sizeof(aucNvGsmCodecInfo));

    ulDefaultValue          = VOS_FALSE;

    usDataLen               = sizeof(aucNvGsmCodecInfo);

    /*����NV�Ľṹ��ԭʼ����ΪMN_CALL_NIMV_ITEM_CODEC_TYPE_STRU��codec����+����codec��Ϣ*/
    if ( NAS_LMM_NVIM_OK != NAS_LMM_NvimRead(en_NV_Item_MED_CODEC_TYPE,
                         aucNvGsmCodecInfo,
                          &usDataLen))
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvGsmCodecInfo: read NV err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvGsmCodecInfo_ENUM,LNAS_FUNCTION_LABEL1);
        ulDefaultValue = VOS_TRUE;
    }

    /* ���NVIM�еĲ����Ƿ�Ϸ�,���Ϸ���ʹ��Ĭ��ֵ,�����Ƿ�Խ�� */
    if ( aucNvGsmCodecInfo[0] > NAS_EMM_BC_MAX_SPH_VER_NUM )
    {
        ulDefaultValue = VOS_TRUE;

        aucNvGsmCodecInfo[0] = NAS_EMM_BC_MAX_SPH_VER_NUM;

        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvGsmCodecInfo: Codec num is err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvGsmCodecInfo_ENUM,LNAS_FUNCTION_LABEL2);
    }

    /* ����Ƿ����ظ�����ͳ�����Χ��codec����*/
    for ( i = 0; i < aucNvGsmCodecInfo[0] ; i++ )
    {
        switch ( aucNvGsmCodecInfo[i+1])
        {
            case NAS_EMM_BC_VAL_SPH_VER_FR_1 :
                punCodecList->stSupportCodec.CodecType_GSMFR        = VOS_TRUE;
                break;

            case NAS_EMM_BC_VAL_SPH_VER_FR_2 :
                punCodecList->stSupportCodec.CodecType_GSMEFR       = VOS_TRUE;
                break;

            case NAS_EMM_BC_VAL_SPH_VER_FR_3 :
                punCodecList->stSupportCodec.CodecType_GSMFRAMR     = VOS_TRUE;
                break;

            case NAS_EMM_BC_VAL_SPH_VER_HR_1 :
                punCodecList->stSupportCodec.CodecType_GSMHR        = VOS_TRUE;
                break;

            case NAS_EMM_BC_VAL_SPH_VER_HR_3 :
                punCodecList->stSupportCodec.CodecType_GSMHRAMR     = VOS_TRUE;
                break;

            case NAS_EMM_BC_VAL_SPH_VER_FR_5 :
                punCodecList->stSupportCodec.CodecType_GSMFRAMRWB   = VOS_TRUE;
                break;

            default:
                NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvGsmCodecInfo: Codec Type is err.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvGsmCodecInfo_ENUM,LNAS_FUNCTION_LABEL3);
                ulDefaultValue = VOS_TRUE;
                break;

        }

        if(ulDefaultValue == VOS_TRUE)
        {
            /*NV���ݴ������*/
            punCodecList->usSupportCodec = 0;
            break;
        }
    }

    /* �˴���ʾ��Ҫʹ��Ĭ��ֵ */
    if ( VOS_TRUE == ulDefaultValue )
    {
        punCodecList->stSupportCodec.CodecType_GSMFR        = VOS_TRUE;
        punCodecList->stSupportCodec.CodecType_GSMEFR       = VOS_TRUE;
        punCodecList->stSupportCodec.CodecType_GSMFRAMR     = VOS_TRUE;
        punCodecList->stSupportCodec.CodecType_GSMHR        = VOS_TRUE;
        punCodecList->stSupportCodec.CodecType_GSMHRAMR     = VOS_TRUE;
        punCodecList->stSupportCodec.CodecType_GSMFRAMRWB   = VOS_TRUE;
    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_ReadNvCodecSupportList
 Description     : ��NV���ȡGU codec֧��list��Ϣ
 Input           : None
 Output          : None
 Return          : None

 History         :
    1.sunbing 49683      2013-10-21  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ReadNvCodecSupportList(VOS_VOID )
{
    NAS_LMM_PUB_INFO_STRU               *pstPubInfo;
    NAS_EMM_SUPPORT_CODEC_UNION          unCodec;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    pstPubInfo->bitOpSupCodecList               = NAS_EMM_BIT_SLCT;
    pstPubInfo->stSupCodecList.ucLenOfCodecList = 0x08;

     /* ����֧�ֵ��б�Ŀǰ������GSM��UMTS֧�ֵ�codec list,
       00 ��ʾGSM, 04��ʾUMTS */
    /* ���帳ֵ�ĺ���μ�26.103 */
    NAS_LMM_MEM_SET(&unCodec,0x00,sizeof(unCodec));
    NAS_EMM_ReadNvUmtsCodecInfo(&unCodec);
    pstPubInfo->stSupCodecList.astCodec[0].ucSysId = 0x04;
    pstPubInfo->stSupCodecList.astCodec[0].ucLenOfBitmap = 0x02;
    pstPubInfo->stSupCodecList.astCodec[0].aucCodecBitmap[0] = (VOS_UINT8)(unCodec.usSupportCodec);
    pstPubInfo->stSupCodecList.astCodec[0].aucCodecBitmap[1] = (VOS_UINT8)(unCodec.usSupportCodec >> 8);

    NAS_LMM_MEM_SET(&unCodec,0x00,sizeof(unCodec));
    NAS_EMM_ReadNvGsmCodecInfo(&unCodec);
    pstPubInfo->stSupCodecList.astCodec[1].ucSysId = 0x00;
    pstPubInfo->stSupCodecList.astCodec[1].ucLenOfBitmap = 0x02;
    pstPubInfo->stSupCodecList.astCodec[1].aucCodecBitmap[0] = (VOS_UINT8)(unCodec.usSupportCodec);
    pstPubInfo->stSupCodecList.astCodec[1].aucCodecBitmap[1] = (VOS_UINT8)(unCodec.usSupportCodec >> 8);

}
/*sunbing 49683 2013-10-21 VoLTE end*/

/*self-adaption NW cause modify begin for leili*/

VOS_VOID  NAS_EMM_ReadNvConfigNwCause(VOS_VOID )
{
    LNAS_LMM_NV_CONFIG_NWCAUSE_STRU    stNvConfigCause;
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo;
    VOS_VOID                           *pData = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();
    pData                               = (VOS_VOID *)&(stNvConfigCause);
    usDataLen = sizeof(LNAS_LMM_NV_CONFIG_NWCAUSE_STRU);

    ulRslt = NAS_LMM_NvimRead(          EN_NV_ID_CONFIG_NWCAUSE,
                                        pData,
                                        &usDataLen);

    if((EN_NV_OK == ulRslt)
        && (stNvConfigCause.ucCauseNum > NAS_EMM_NULL))
    {

        NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_ReadNvConfigNwCause: read NV success, CauseNum=",
            stNvConfigCause.ucCauseNum);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ReadNvConfigNwCause_ENUM,LNAS_CAUSE_NUMBER,
            stNvConfigCause.ucCauseNum);
        if ((NAS_EMM_NULL == stNvConfigCause.ucCauseNum)
            || (NAS_LMM_MAX_CAUSE_NUM < stNvConfigCause.ucCauseNum))
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvConfigNwCause: config NV err.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvConfigNwCause_ENUM,LNAS_FUNCTION_LABEL1);
            return;
        }

        pstPubInfo->stConfCause.ucCauseNum = stNvConfigCause.ucCauseNum;
        NAS_LMM_MEM_CPY(pstPubInfo->stConfCause.astAdaptCause,
                        stNvConfigCause.astAdaptCause,
                        sizeof(NAS_LMM_ADAPTION_CAUSE_STRU) * NAS_LMM_MAX_CAUSE_NUM);
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvConfigNwCause: read NV err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvConfigNwCause_ENUM,LNAS_FUNCTION_LABEL2);
        pstPubInfo->stConfCause.ucCauseNum = 0;
        NAS_LMM_MEM_SET(pstPubInfo->stConfCause.astAdaptCause,
                        0,
                        sizeof(NAS_LMM_ADAPTION_CAUSE_STRU) * NAS_LMM_MAX_CAUSE_NUM);

    }
    return;
}

/*self-adaption NW cause modify end for leili*/

VOS_VOID  NAS_EMM_SetLteUeUsageSetting2Mml
(
    NAS_EMM_USAGE_SETTING_UINT32        enUeUsageSetting
)
{
    NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_SetLteUeUsageSetting2Mml: ue's usage setting:",
                           enUeUsageSetting);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SetLteUeUsageSetting2Mml_ENUM,LNAS_EMM_UE_USG_SETTING,
                           enUeUsageSetting);

    NAS_MML_SetLteUeUsageSetting((VOS_UINT8)enUeUsageSetting);
}


VOS_VOID  NAS_EMM_ReadNvUeSetting( VOS_VOID )
{
    VOS_VOID                           *pData           = VOS_NULL_PTR;
    LNAS_LMM_NV_UE_CENTER_STRU          stNvUeCenter    = {0};
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo      = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt          = NAS_EMM_NULL;
    VOS_UINT16                          usDataLen       = NAS_EMM_NULL;

    pstPubInfo  = NAS_LMM_GetEmmInfoAddr();
    pData       = (VOS_VOID *)&(stNvUeCenter);
    usDataLen   = sizeof(LNAS_LMM_NV_UE_CENTER_STRU);

    ulRslt      = NAS_LMM_NvimRead(     EN_NV_ID_UE_CENTER,
                                        pData,
                                        &usDataLen);

    if((EN_NV_OK == ulRslt)
        && (stNvUeCenter.bitOpUeCenter == NAS_EMM_BIT_SLCT))
    {
        NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_ReadNvUeSetting: read NV success.",
            stNvUeCenter.enUeCenter);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ReadNvUeSetting_ENUM,LNAS_FUNCTION_LABEL1,
            stNvUeCenter.enUeCenter);
        if (EMM_USAGE_SETTING_BUTT > stNvUeCenter.enUeCenter)
        {
            pstPubInfo->ulUsageSetting  = stNvUeCenter.enUeCenter;
        }
        else
        {
            NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUeSetting:NV Value is Invalid");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUeSetting_ENUM,LNAS_FUNCTION_LABEL2);
            pstPubInfo->ulUsageSetting  = EMM_SETTING_DATA_CENTRIC;
        }
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_ReadNvUeSetting: read NV err.");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_ReadNvUeSetting_ENUM,LNAS_FUNCTION_LABEL3);
        pstPubInfo->ulUsageSetting      = EMM_SETTING_DATA_CENTRIC;
    }

    NAS_EMM_SetLteUeUsageSetting2Mml(pstPubInfo->ulUsageSetting);

    return;
}



VOS_VOID    NAS_EMM_PubmInfoSupCodecListInit( VOS_VOID )
{
    NAS_LMM_PUB_INFO_STRU               *pstPubInfo;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    /*sunbing 49683 2013-10-14 VoLTE begin*/
    /*��ʼ������Ϊ��Ч��������ȡNV�����һ����ֵ*/
    pstPubInfo->bitOpSupCodecList       = NAS_EMM_BIT_NO_SLCT;

     /* ����֧�ֵ��б�Ŀǰ������GSM��UMTS֧�ֵ�codec list,
       00 ��ʾGSM, 04��ʾUMTS */
    /* ���帳ֵ�ĺ���μ�26.103 */
    /*
    pstPubInfo->stSupCodecList.ucLenOfCodecList = 0x08;
    pstPubInfo->stSupCodecList.astCodec[0].ucSysId = 0x04;
    pstPubInfo->stSupCodecList.astCodec[0].ucLenOfBitmap = 0x02;
    pstPubInfo->stSupCodecList.astCodec[0].aucCodecBitmap[0] = 0x60;
    pstPubInfo->stSupCodecList.astCodec[0].aucCodecBitmap[1] = 0x00;
    pstPubInfo->stSupCodecList.astCodec[1].ucSysId = 0x00;
    pstPubInfo->stSupCodecList.astCodec[1].ucLenOfBitmap = 0x02;
    pstPubInfo->stSupCodecList.astCodec[1].aucCodecBitmap[0] = 0x1F;
    pstPubInfo->stSupCodecList.astCodec[1].aucCodecBitmap[1] = 0x00;
    */
    /*sunbing 49683 2013-10-14 VoLTE end*/

    return;
}
VOS_VOID     NAS_EMM_PubmInfoBearerContextInit(VOS_VOID)
{
    /*leili modify for isr begin*/
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
    NAS_MML_PS_BEARER_CONTEXT_STRU      *pstPsBearerCtx = NAS_EMM_NULL_PTR;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */

    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,begin */
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PubmInfoBearerContextInit is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PubmInfoBearerContextInit_ENUM,LNAS_ENTRY);

    pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();

    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    NAS_LMM_MEM_SET(                    pstPsBearerCtx,
                                        0,
                                        EMM_ESM_MAX_EPS_BEARER_NUM*
                                        sizeof(NAS_MML_PS_BEARER_CONTEXT_STRU));

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PubmInfoBearerContextInit: UPDATE MML PS BEARER INFO:");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PubmInfoBearerContextInit_ENUM,LNAS_FUNCTION_LABEL2);
    NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
    /* mod by yanglei 00307272 for KEY_INFO_REPORT,2015-07-30,end */

    /*PC REPLAY MODIFY BY LEILI END*/
    /*leili modify for isr end*/
    return;
}


VOS_VOID    NAS_EMM_FsmReg( VOS_VOID )
{
    VOS_UINT32                      ulRslt = NAS_LMM_FAIL;

    VOS_UINT32                      ulSizeof1;
    VOS_UINT32                      ulSizeof2;

    ulSizeof1                       = g_ulSizeof_g_astEmmStaTbl;
    ulSizeof2                       = sizeof(NAS_LMM_STA_STRU);

    /* ע��RRC_FSM_CESL״̬�� */
    ulRslt = NAS_LMM_FsmRegisterFsm(NAS_LMM_PARALLEL_FSM_EMM,
                                    (VOS_UINT32)(ulSizeof1 / ulSizeof2),
                                    g_astEmmStaTbl,
                                    NAS_EMM_FsmErr);
    if (ulRslt != NAS_LMM_SUCC)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_FsmReg, register fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_FsmReg_ENUM,LNAS_FAIL);
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_FsmReg, register SUCC!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_FsmReg_ENUM,LNAS_SUCC);
    }

    return;
}
VOS_UINT32  NAS_EMM_FsmErr(             VOS_UINT32           ulMsgId,
                                                VOS_VOID             *pMsg )
{
/*    NAS_LMM_PUBM_LOG2_ERR("NAS_EMM_FsmErr: ", ulMsgId, pMsg);*/
    (VOS_VOID)(ulMsgId);
    (VOS_VOID)(pMsg);
    return  NAS_LMM_MSG_DISCARD;
}
VOS_VOID    NAS_EMM_FSM_PushState(VOS_VOID)
{
    NAS_LMM_FSM_PushStackCombine(NAS_LMM_PARALLEL_FSM_EMM);
    return;
}


VOS_VOID    NAS_EMM_FSM_PopState(VOS_VOID)
{
    NAS_LMM_FSM_PopStackCombine(NAS_LMM_PARALLEL_FSM_EMM);
    return;
}


VOS_VOID    NAS_EMM_FSM_PopAllState(VOS_VOID)
{
    VOS_UINT32                          ulStackCurDepth;
    NAS_LMM_FSM_STATE_STACK_STRU        *pstFsmStack;        /* ״̬��ջ��ַ */


    /* ��ȡEMM״̬����ǰ״̬�ĵ�ַ��״̬��ջ�ĵ�ַ */
    pstFsmStack = NAS_LMM_GetFsmStackAddr(NAS_LMM_PARALLEL_FSM_EMM);
    ulStackCurDepth = pstFsmStack->ucStackDepth;
    NAS_LMM_PUBM_LOG1_INFO("NAS_EMM_FSM_PopAllState: ulStackCurDepth = ", ulStackCurDepth);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_FSM_PopAllState_ENUM,LNAS_FUNCTION_LABEL1,ulStackCurDepth);

    for(; 0 < ulStackCurDepth; ulStackCurDepth-- )
    {
        NAS_LMM_FSM_PopStackCombine(NAS_LMM_PARALLEL_FSM_EMM);
    }

    return;
}


VOS_VOID    NAS_EMM_FSM_ClearState(VOS_VOID)
{
    NAS_LMM_FSM_ClearStackCombine(NAS_LMM_PARALLEL_FSM_EMM);
    return;
}




VOS_UINT32  NAS_LMM_MatchNvImsi( VOS_VOID )
{
    VOS_VOID                           *pData;
    LNAS_LMM_NV_IMSI_STRU               stNvImsi;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;


    /*read Imsi from Nvim*/
    pData                               = &(stNvImsi);
    usDataLen                           = sizeof(LNAS_LMM_NV_IMSI_STRU);
    ulRslt = NAS_LMM_NvimRead(           EN_NV_ID_IMSI,
                                        pData,
                                        &usDataLen);

    if((NAS_LMM_NVIM_OK == ulRslt) && (NAS_EMM_BIT_SLCT == stNvImsi.bitOpImsi))
    {
        if (0 == NAS_LMM_MEM_CMP((const VOS_VOID *) g_stEmmInfo.stMmUeId.aucImsi,
                         (const VOS_VOID *) stNvImsi.aucImsi,
                         NAS_LMM_NVIM_IMSI_FILE_LEN))
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_LMM_MatchNvImsi: IMSI EQUAL. ");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_MatchNvImsi_ENUM,LNAS_FUNCTION_LABEL1);
            return NAS_EMM_SUCC;

        }
    }

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_MatchNvImsi: IMSI DIFF. ");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_MatchNvImsi_ENUM,LNAS_FUNCTION_LABEL2);
    return NAS_EMM_FAIL;
}
VOS_VOID  NAS_LMM_UpdateNvImsi(const VOS_UINT8  *pucImsi )
{

    VOS_UINT32                          ulRst;
    VOS_VOID                           *pData;
    LNAS_LMM_NV_IMSI_STRU               stNvImsi;
    VOS_UINT16                          usDataLen;
    NAS_LMM_UEID_STRU                    *pstUeId;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_UpdateNvImsi is entered");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_UpdateNvImsi_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_SET(&stNvImsi, 0, sizeof(LNAS_LMM_NV_IMSI_STRU));

    pstUeId                             = NAS_LMM_GetEmmInfoUeidAddr();

    /*����µ�IMSI*/
    stNvImsi.bitOpImsi                  = pstUeId->bitOpImsi;
    NAS_LMM_MEM_CPY(                    stNvImsi.aucImsi,
                                        pucImsi,
                                        NAS_LMM_NVIM_IMSI_FILE_LEN);

    /*write new IMSI to NVIM*/
    pData                               = &stNvImsi;
    usDataLen                           = sizeof(LNAS_LMM_NV_IMSI_STRU);

    ulRst = NAS_LMM_NvimWrite(           EN_NV_ID_IMSI,
                                        pData,
                                        usDataLen);
    if(EN_NV_OK != ulRst)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_UpdateNvImsi: nvim ERR!!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_UpdateNvImsi_ENUM,LNAS_ERROR);
        return;
    }

    return;
}



VOS_VOID NAS_LMM_ReadNvimImei(VOS_VOID)
{
    VOS_UINT8                           aucDefImei[NAS_MM_MAX_UEID_BUF_SIZE] = {0};

    VOS_UINT8                           aucBuf[NV_ITEM_IMEI_SIZE] = {0};

    VOS_UINT32                          i = 0;

    /*IMEI��ȡʧ�ܣ���ʹ��ȱʡֵ*/
    if(ERR_MSP_SUCCESS != SC_PERS_NvRead(MODEM_ID_0, en_NV_Item_IMEI, aucBuf, NV_ITEM_IMEI_SIZE))
    {
        NAS_LMM_MEM_SET(aucDefImei, 0, NAS_MM_MAX_UEID_BUF_SIZE);
        aucDefImei[0] = 0x08;
        aucDefImei[1] = 0x3A;
        aucDefImei[2] = 0x65;
        aucDefImei[3] = 0x26;
        aucDefImei[4] = 0x06;
        aucDefImei[5] = 0x70;
        aucDefImei[6] = 0x37;
        aucDefImei[7] = 0x71;
        aucDefImei[8] = 0x04;
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_ReadNvimImei: Read IMEI from NV fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LMM_ReadNvimImei_ENUM,LNAS_FAIL);
    }
    else
    {
        /* NV��ȡ�ɹ������¼���IMEIУ��λ����ת��ΪLNAS�ڲ�IMEI�Ŵ洢��ʽ */
        aucDefImei[0] = 0x08;
        aucDefImei[1] = 0x0A;

        /* ��NV�и�ʽת��ΪLNAS�ڲ�IMEI��Ÿ�ʽ */
        for (i = 0; i < (NV_ITEM_IMEI_SIZE - 1); i++)
        {
             aucDefImei[((i + 1) / 2) + 1] |= (VOS_UINT8)(aucBuf[i] << (((i + 1) % 2) * NAS_LMM_MOVEMENT_4_BITS));
        }
    }

    NAS_LMM_GetEmmInfoUeidAddr()->bitOpImei = NAS_EMM_BIT_SLCT;
    NAS_LMM_MEM_CPY(                NAS_LMM_GetEmmInfoUeidImeiAddr(),
                                    aucDefImei,
                                    NAS_MM_MAX_UEID_BUF_SIZE);
    /* ��ӡ��ȡ����IMEIֵ */
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvimImei: IMEI value is :");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvimImei_ENUM,LNAS_FUNCTION_LABEL1);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                   NAS_LMM_GetEmmInfoUeidImeiAddr(),
                   NAS_MM_MAX_UEID_BUF_SIZE);

    return;
}
VOS_VOID  NAS_LMM_ReadNvEpsSecContext(VOS_VOID )
{
    LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU    stNvEpsSecContext;
    NAS_LMM_SECU_CONTEXT_STRU            stSecuCurContext;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvEpsSecContext is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvEpsSecContext_ENUM,LNAS_ENTRY);

    /*read  from Nvim*/
    usDataLen                           = sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU);
    ulRslt = NAS_LMM_NvimRead(           EN_NV_ID_SEC_CONTEXT,
                                        (VOS_VOID *)&(stNvEpsSecContext),
                                        &usDataLen);

    /* ��NV�����ݽṹ�� NAS ���Ľṹת�� */
    NAS_LMM_MEM_SET(                    &stSecuCurContext,
                                        0,
                                        sizeof(NAS_LMM_SECU_CONTEXT_STRU));

    NAS_LMM_MEM_SET( NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR(),
                     0,
                     NAS_NVIM_SECU_CONTEXT_MAX_LEN);

    /*process the result of reading,���崦��ʽ�д�����ȷ��*/
    if((NAS_LMM_NVIM_OK == ulRslt) && (NAS_EMM_BIT_SLCT == stNvEpsSecContext.bitOpEpsSec))
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvEpsSecContext: read NV Succ.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvEpsSecContext_ENUM,LNAS_SUCC);

        /* ��NV�еİ�ȫ�����������������ϴ�д����ȫ�ֱ����У������´�д��ʱ�ıȽ� */
        NAS_LMM_MEM_CPY( NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR(),
                         (VOS_VOID *)&(stNvEpsSecContext),
                         sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU));

  /*��ǰ��ȫ�����Ľṹ��ֵ*/
        stSecuCurContext.ucKSIasme      = stNvEpsSecContext.ucKSIasme;

        NAS_LMM_MEM_CPY(                 stSecuCurContext.aucKasme,
                                        stNvEpsSecContext.aucKasme,
                                        NAS_MM_AUTH_KEY_ASME_LEN);
        stSecuCurContext.ulUlNasCount   = stNvEpsSecContext.ulUlNasCount;
        stSecuCurContext.ulDlNasCount   = stNvEpsSecContext.ulDlNasCount;
        stSecuCurContext.ucSecuAlg      = stNvEpsSecContext.ucSecuAlg;

        /*���ð�ȫ�����ĸ��º���,������NasCK ,NasIk*/
        NAS_EMM_SecuSetCurCntxt(&stSecuCurContext);
    }

    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_ReadNvEpsSecContext: read NV Fail!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvEpsSecContext_ENUM,LNAS_FAIL);
    }

    return;
}


VOS_VOID  NAS_LMM_ReadNvDamParaCServiceAndPlmnList(VOS_VOID )
{
    PS_NV_DAM_CONFIG_PARA_STRU            stNvDamPara = {0};
    VOS_UINT32                            ulRslt    = NAS_LMM_NVIM_FAIL;
    VOS_UINT16                            usDataLen = 0;
    NAS_MM_DAM_PLMN_LIST_STRU            *pstDamPlmnList;
    NAS_DAM_IMSI_PLMN_LIST               *pstImsiPlmnList;

    pstDamPlmnList   = NAS_EMM_GetEmmInfoDamParaPlmnListAddr();
    pstImsiPlmnList  = NAS_EMM_GetEmmInfoDamParaImsiPlmnListAddr();

    /* ��NV֮ǰ�ȸ�ֵĬ��ֵ����ȡ�ɹ����ٽ���ˢ�� */
    NAS_EMM_GetEmmInfoDamParaCserviceMax() = NAS_LMM_DAM_CSERVICE_DEFAULT_VALUE;

    NAS_LMM_MEM_SET(pstDamPlmnList, 0, sizeof(NAS_MM_DAM_PLMN_LIST_STRU));
    NAS_LMM_MEM_SET(pstImsiPlmnList, 0, sizeof(NAS_DAM_IMSI_PLMN_LIST));

    /* ��NV */
    usDataLen = sizeof(PS_NV_DAM_CONFIG_PARA_STRU);
    ulRslt = NAS_LMM_NvimRead(EN_NV_ID_DAM_CONFIG_PARA,
                              (VOS_VOID *)&(stNvDamPara),
                              &usDataLen);

    if(NAS_LMM_NVIM_OK == ulRslt)
    {
        /* CService��ֵ��Ч�ұ��봦��1-60֮�� */
        if((NAS_LMM_DAM_NV_CSERVICE_MAX_VALUE >= stNvDamPara.ulCService)
            &&(NAS_LMM_DAM_NV_CSERVICE_MIN_VALUE <= stNvDamPara.ulCService))
        {
            NAS_EMM_GetEmmInfoDamParaCserviceMax() = stNvDamPara.ulCService;
        }

        if((0 < stNvDamPara.stDamConfigPlmnPara.stDamPlmnList.ulPlmnNum)
            &&(NAS_MM_DAM_MAX_PLMN_NUM >= stNvDamPara.stDamConfigPlmnPara.stDamPlmnList.ulPlmnNum))
        {
            pstDamPlmnList->ulPlmnNum = stNvDamPara.stDamConfigPlmnPara.stDamPlmnList.ulPlmnNum;
            NAS_LMM_MEM_CPY(pstDamPlmnList->astPlmnId,
                            stNvDamPara.stDamConfigPlmnPara.stDamPlmnList.astPlmnId,
                            sizeof(NAS_MM_PLMN_ID_STRU)*NAS_MM_DAM_MAX_PLMN_NUM);
        }

        if((0 < stNvDamPara.stDamConfigPlmnPara.stImsiPlmnList.ulPlmnNum)
            &&(NAS_MM_DAM_MAX_PLMN_NUM >= stNvDamPara.stDamConfigPlmnPara.stImsiPlmnList.ulPlmnNum))
        {
            pstImsiPlmnList->ulPlmnNum = stNvDamPara.stDamConfigPlmnPara.stImsiPlmnList.ulPlmnNum;
            NAS_LMM_MEM_CPY(pstImsiPlmnList->astPlmnId,
                            stNvDamPara.stDamConfigPlmnPara.stImsiPlmnList.astPlmnId,
                            sizeof(NAS_MM_PLMN_ID_STRU)*NAS_MM_DAM_MAX_PLMN_NUM);
        }
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvATTDamParaCServiceAndPlmnList: read NV Fail.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvDamParaCServiceAndPlmnList_ENUM,LNAS_FAIL);
    }

    /* ���������NV������HIDS */
    NAS_LMM_SndOmDamPara();

    return;
}


VOS_VOID  NAS_LMM_ReadRej19AtmptCntFlag(VOS_UINT8 ucRej19AtmptCntFlag)
{
    NAS_EMM_GetEmmInfoRej19AtmptCntFlag() = ucRej19AtmptCntFlag;
    return;
}


VOS_VOID  NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag
(
    NAS_TMO_IMSI_HPLMN_LIST *pstTmoImsiHplmnList
)
{
    VOS_UINT8                 *pucImsi = 0;
    NAS_MM_PLMN_ID_STRU        stHplmn;
    VOS_UINT32                 ulIndex = 0;

    PS_MEM_SET(&stHplmn, 0x00, sizeof(NAS_MM_PLMN_ID_STRU));
    pucImsi = (VOS_UINT8*)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PARA_IMSI);

    /* ��ʼ��FlagΪ��TMO�� */
    NAS_EMM_GetEmmInfoTmoUsimCardFlag() = VOS_FALSE;

    /* Լ����NV�й���IMSI��PLMN�ж����ֻ����1��PLMN��ȫΪ0XFF����Ĭ�����п�����TMO�� */
    if((1 == pstTmoImsiHplmnList->ulPlmnNum)
        &&(NAS_LMM_BYTE_FF == pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[0])
        &&(NAS_LMM_BYTE_FF == pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[1])
        &&(NAS_LMM_BYTE_FF == pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[2]))
    {
        NAS_EMM_GetEmmInfoTmoUsimCardFlag() = VOS_TRUE;
        return;
    }

    NAS_LMM_PUBM_LOG3_INFO("NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag: plmnNum/0/1",
                           pstTmoImsiHplmnList->ulPlmnNum,
                           pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[0],
                           pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[1]);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag_ENUM,LNAS_EMM_PLMN,
                           pstTmoImsiHplmnList->ulPlmnNum);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag_ENUM,LNAS_FUNCTION_LABEL1,
                            pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[0],
                           pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[1]);
    NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag: id2",
                           pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[2]);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag_ENUM,LNAS_FUNCTION_LABEL2,
                           pstTmoImsiHplmnList->astPlmnId[0].aucPlmnId[2]);

    /* ��Ҫ�жϿ� */
    /* ��ȡHPLMN��Ȼ���IMSI PLMN�б���бȶԣ���ȡ�ɹ��ұȶԳɹ�����TMO�Ŀ� */
    if(NAS_EMM_SUCC == NAS_EMM_GetImsiHplmn(pucImsi, &stHplmn))
    {
        for(ulIndex = 0; ulIndex < pstTmoImsiHplmnList->ulPlmnNum; ulIndex++)
        {
            if(NAS_LMM_MATCH_SUCCESS == NAS_LMM_PlmnMatch(&(stHplmn),
                (NAS_MM_PLMN_ID_STRU*)&(pstTmoImsiHplmnList->astPlmnId[ulIndex])))
            {
                NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag: TMO Card.");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag_ENUM,LNAS_FUNCTION_LABEL3);
                NAS_EMM_GetEmmInfoTmoUsimCardFlag() = VOS_TRUE;
                return;
            }
        }
    }

    return;
}



VOS_VOID  NAS_EMM_LteNoSubscribeInit(
            LNAS_LMM_NV_LTE_NO_SUBSCRIBE_CONFIG_STRU stLteNoSubscribeNvConfig)
{
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_LteNoSubscribeInit is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_LteNoSubscribeInit_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_SET(NAS_EMM_GetLteNoSubscribeAddr(), 0, sizeof(LNAS_LMM_NV_LTE_NO_SUBSCRIBE_CONFIG_STRU));

    /*���������Գ����Ž��в��ֶ��ƹ��ܵĳ�ʼ��*/
    if(PS_SUCC != LPS_OM_IsTestMode())
    {
        NAS_EMM_SetLteNoSubscribeNvConfigHplmnSwitch(
                    stLteNoSubscribeNvConfig.ucLteNoSubscribeHplmnSwitch);
        NAS_EMM_SetLteNoSubscribeNvConfigVplmnSwitch(
                    stLteNoSubscribeNvConfig.ucLteNoSubscribeVplmnSwitch);
    }

    /*�����ʱʱ���������ֵ�������ó����ֵ*/
    if( NAS_MAX_PUBLISHMENT_TIMER_LEN < stLteNoSubscribeNvConfig.ulPublishmentTimerVplmnLen)
    {
        stLteNoSubscribeNvConfig.ulPublishmentTimerVplmnLen = NAS_MAX_PUBLISHMENT_TIMER_LEN;
    }

    /*�����ʱʱ������0�� �����ó�Ĭ��ֵ1��Сʱ*/
    if(0 == stLteNoSubscribeNvConfig.ulPublishmentTimerVplmnLen)
    {
        stLteNoSubscribeNvConfig.ulPublishmentTimerVplmnLen = NAS_PUBLISHMENT_LEN_ONE_HOUR;
    }

    /*�����ʱʱ���������ֵ�������ó����ֵ*/
    if( NAS_MAX_PUBLISHMENT_TIMER_LEN < stLteNoSubscribeNvConfig.ulPublishmentTimerHplmnLen)
    {
        stLteNoSubscribeNvConfig.ulPublishmentTimerHplmnLen = NAS_MAX_PUBLISHMENT_TIMER_LEN;
    }

    /*�����ʱʱ������0�� �����ó�Ĭ��ֵ1��Сʱ*/
    if(0 == stLteNoSubscribeNvConfig.ulPublishmentTimerHplmnLen)
    {
        stLteNoSubscribeNvConfig.ulPublishmentTimerHplmnLen = NAS_PUBLISHMENT_LEN_ONE_HOUR;
    }

    NAS_EMM_SetLteNoSubscribeNvConfigPublishmentTimerVplmnLen(
        stLteNoSubscribeNvConfig.ulPublishmentTimerVplmnLen);
    NAS_EMM_SetLteNoSubscribeNvConfigPublishmentTimerHplmnLen(
        stLteNoSubscribeNvConfig.ulPublishmentTimerHplmnLen);

    /*Ĭ��֧��Э��涨��4Gδ��������*/
    if(0 == stLteNoSubscribeNvConfig.ucDiscardExtendedEmmCauseFlag)
    {
        NAS_EMM_SetLteNoSubscribeNvConfigDiscardExtCauseFlag(PS_FALSE);
    }
    else
    {
        NAS_EMM_SetLteNoSubscribeNvConfigDiscardExtCauseFlag(PS_TRUE);
    }

    return;
}


VOS_VOID  NAS_LMM_ReadNvLmmCommConfigPara(VOS_VOID )
{
    LNAS_LMM_NV_COMM_CONFIG_PARA_STRU     stNvCommPara;
    VOS_UINT32                            ulRslt      = NAS_LMM_NVIM_FAIL;
    VOS_UINT16                            usDataLen   = 0;

    NAS_LMM_MEM_SET(&stNvCommPara, 0, sizeof(LNAS_LMM_NV_COMM_CONFIG_PARA_STRU));

    /* ��NV */
    usDataLen = sizeof(LNAS_LMM_NV_COMM_CONFIG_PARA_STRU);
    ulRslt = NAS_LMM_NvimRead(EN_NV_ID_LNAS_COMM_CONFIG_PARA,
                              (VOS_VOID *)&(stNvCommPara),
                              &usDataLen);

    if(NAS_LMM_NVIM_OK == ulRslt)
    {
        /* ��ȡ�ɹ������������NV������HIDS */
        NAS_LMM_SndOmCommConfigPara(&stNvCommPara);
    }
    else
    {
        /* ��NVʧ�������Ŀ�������������ӦNV����Ĭ��ֵ��ʼ�� */
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvLmmCommConfigPara: read NV Fail.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvLmmCommConfigPara_ENUM,LNAS_FAIL);
    }

    /* ��ȡulRej19AtmptCnt��ֵ */
    NAS_LMM_ReadRej19AtmptCntFlag(stNvCommPara.ucRej19AtmptCntFlag);

    /* ��ȡTMO��HPLMN�б������Ƿ���TMO����� */
    NAS_LMM_ReadTmoImsiHplmnListAndSetTmoUsimCardFlag(&stNvCommPara.stTmoImsiHplmnList);

    NAS_EMM_LteNoSubscribeInit(stNvCommPara.stLteNoSubscribeConfig);

    /* ��ȡ�������ֵ�����������ڴ˲��� */

    return;
}



VOS_VOID  NAS_LMM_ReadSimEpsSecContext( VOS_VOID )
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadSimEpsSecContext is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadSimEpsSecContext_ENUM,LNAS_ENTRY);

    NAS_LMM_UsimFileRead(USIMM_USIM_EFEPSNSC_ID);
    return;
}


VOS_VOID  NAS_LMM_ReadNvPsLoc( VOS_VOID )
{
    VOS_VOID                            *pData;
    LNAS_LMM_NV_EPS_LOC_STRU            stNvPsLoc;
    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usDataLen;
    NAS_LMM_UEID_STRU                    *pstUeId;
    NAS_MM_NETWORK_ID_STRU              stMmNetId;
    VOS_UINT8                          *pstLastPsLoc;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvPsLoc is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvPsLoc_ENUM,LNAS_ENTRY);

    pstUeId                             = NAS_LMM_GetEmmInfoUeidAddr();
    pstLastPsLoc                        =NAS_LMM_GetEmmInfoLastWriteUsimPsLocAddr();

    /*read EPS PS LOC from Nvim*/
    pData                               = &(stNvPsLoc);
    usDataLen                           = sizeof(LNAS_LMM_NV_EPS_LOC_STRU);
    ulRslt = NAS_LMM_NvimRead(           EN_NV_ID_EPS_LOC,
                                        pData,
                                        &usDataLen);

    /*process the result of reading,���崦��ʽ�д�����ȷ��*/
    if(NAS_LMM_NVIM_OK == ulRslt)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvPsLoc: read NV Succ.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvPsLoc_ENUM,LNAS_SUCC);

        /* ��NV�ɹ��������ζ�NV���������浽�ϴγɹ�д����ȫ�ֱ����� */
        NAS_LMM_MEM_CPY( pstLastPsLoc,
                         pData,
                         sizeof(LNAS_LMM_NV_EPS_LOC_STRU));

        /*GUTI*/
        if (NAS_EMM_BIT_SLCT == stNvPsLoc.bitOpGuti)
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvPsLoc: GUTI VALID");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvPsLoc_ENUM,LNAS_FUNCTION_LABEL1);
            pstUeId->bitOpGuti          = NAS_EMM_BIT_SLCT;
            NAS_LMM_MEM_CPY(            &pstUeId->stGuti,
                                        &(stNvPsLoc.stGuti),
                                        sizeof(NAS_LMM_GUTI_STRU));

            NAS_EMM_SetLteNoSubscribeLteRegFlag(NAS_LMM_HAVE_REG_SUCC_ON_LTE);
        }

        /*L.R.V TAI*/
        if (NAS_EMM_BIT_SLCT == stNvPsLoc.bitOpTai)
        {
            NAS_LMM_MEM_CPY(            &(stMmNetId.stPlmnId),
                                        &(stNvPsLoc.stLastRegTai.stPlmnId),
                                        sizeof(NAS_MM_PLMN_ID_STRU));

            NAS_LMM_MEM_CPY(            &(stMmNetId.stTac),
                                        &(stNvPsLoc.stLastRegTai.stTac),
                                        sizeof(NAS_MM_TAC_STRU));


            /*PLMN��Чʱ,����ȫ�ֱ���*/
            if (VOS_FALSE == NAS_LMM_CheckPlmnIsInvalid(&stMmNetId.stPlmnId))
            {
                NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvPsLoc: L.V.R TAI PLMN VALID");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvPsLoc_ENUM,LNAS_FUNCTION_LABEL2);
                if (VOS_TRUE == NAS_LMM_TacIsUnexist(&(stMmNetId.stTac)))
                {
                    NAS_LMM_UndefTac(&(stMmNetId.stTac));
                }
                NAS_EMM_SetLVRTai(&stMmNetId);
            }
            else
            {
                NAS_EMM_ClearLVRTai();
            }

        }

        /*UPDATE STATUS*/
        if (NAS_EMM_BIT_SLCT == stNvPsLoc.bitOpUpState)
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadNvPsLoc: EU VALID");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvPsLoc_ENUM,LNAS_FUNCTION_LABEL3);
            NAS_EMM_TAUSER_SaveAuxFsmUpStat((VOS_UINT8)stNvPsLoc.enUpdateState);

        }
    }
    else
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_ReadNvPsLoc: read NV Fail!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadNvPsLoc_ENUM,LNAS_FUNCTION_LABEL4);
        NAS_EMM_ClearGuti();
        NAS_EMM_ClearLVRTai();
    }

    return;
}
VOS_VOID  NAS_LMM_ReadSimPsLoc( VOS_VOID )
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadSimPsLoc is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadSimPsLoc_ENUM,LNAS_ENTRY);

    NAS_LMM_UsimFileRead(USIMM_USIM_EFEPSLOCI_ID);
    return;
}


VOS_VOID  NAS_LMM_ReadSimMncLen(VOS_VOID)
{
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ReadSimMncLen is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ReadSimMncLen_ENUM,LNAS_ENTRY);

    NAS_LMM_UsimFileRead(USIMM_USIM_EFAD_ID);
    return ;
}


VOS_VOID  NAS_LMM_WriteSimEpsSecurityContext(NAS_NV_ITEM_OP_TYPE_ENUM_UINT32 enOpType)
{
    LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU    stNvSecContext;
    NAS_LMM_SECU_CONTEXT_STRU          *pstCurSecuCntxt = VOS_NULL_PTR;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteSimEpsSecurityContext is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteSimEpsSecurityContext_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_SET(&stNvSecContext, 0, sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU));

    if(NAS_NV_ITEM_UPDATE == enOpType)
    {
        /*��ȡ��ǰ��ȫ������*/
        pstCurSecuCntxt = NAS_EMM_SecuGetCurCntxtAddr();

        /* ����㷨��EIA0����д����ֱ���˳� */
        if (NAS_EMM_SECU_ALG_EIA0 == (pstCurSecuCntxt->ucSecuAlg & NAS_EMM_LOW_3_BITS_F))
        {
            NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteSimEpsSecurityContext:EIA0");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteSimEpsSecurityContext_ENUM,LNAS_FUNCTION_LABEL1);
            return ;
        }

        /* ���ע��״̬Ϊ����ע�ᣬ��д����ֱ���˳� */
        if (NAS_LMM_REG_STATUS_EMC_REGED == NAS_LMM_GetEmmInfoRegStatus())
        {
            NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteSimEpsSecurityContext:emc regged");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteSimEpsSecurityContext_ENUM,LNAS_FUNCTION_LABEL2);
            return ;
        }

        /*���д��USIM������*/
        stNvSecContext.ucKSIsgsn        = pstCurSecuCntxt->ucKSIsgsn;
        stNvSecContext.ucKSIasme        = pstCurSecuCntxt->ucKSIasme;
        stNvSecContext.ucSecuAlg        = pstCurSecuCntxt->ucSecuAlg;
        stNvSecContext.ulUlNasCount     = pstCurSecuCntxt->ulUlNasCount;
        stNvSecContext.ulDlNasCount     = pstCurSecuCntxt->ulDlNasCount;
        NAS_LMM_MEM_CPY(                 stNvSecContext.aucKasme,
                                        pstCurSecuCntxt->aucKasme,
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);
    }
    else
    {
        NAS_LMM_MEM_SET(&stNvSecContext, (VOS_CHAR)0xff, sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU));
    }

    /*write EPS SECURITY CONTEXT to USIM*/
    NAS_LMM_UsimFileWrite(USIMM_USIM_EFEPSNSC_ID,
                          &stNvSecContext,
                          sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU));

    return;
}
VOS_VOID  NAS_LMM_WriteNvEpsSecurityContext( NAS_NV_ITEM_OP_TYPE_ENUM_UINT32 enOpType )
{
    VOS_UINT32                          ulRst;
    LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU    stNvSecContext;
    NAS_LMM_SECU_CONTEXT_STRU           *pstCurSecuCntxt = VOS_NULL_PTR;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvEpsSecurityContext entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvEpsSecurityContext_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_SET(&stNvSecContext, 0, sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU));

    if (NAS_NV_ITEM_UPDATE == enOpType)
    {
        /*��ȡ��ǰ��ȫ������*/
        pstCurSecuCntxt = NAS_EMM_SecuGetCurCntxtAddr();

        /* ����㷨��EIA0����дNV��ֱ���˳� */
        if (NAS_EMM_SECU_ALG_EIA0 == (pstCurSecuCntxt->ucSecuAlg & NAS_EMM_LOW_3_BITS_F))
        {
            NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvEpsSecurityContext:EIA0");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvEpsSecurityContext_ENUM,LNAS_FUNCTION_LABEL1);
            return ;
        }

        /* ���ע��״̬Ϊ����ע�ᣬ��дNV��ֱ���˳� */
        if (NAS_LMM_REG_STATUS_EMC_REGED == NAS_LMM_GetEmmInfoRegStatus())
        {
            NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvEpsSecurityContext:emc regged");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvEpsSecurityContext_ENUM,LNAS_FUNCTION_LABEL2);
            return ;
        }

        /*���д��USIM������*/
        stNvSecContext.bitOpEpsSec      = NAS_NVIM_BIT_SLCT;

        stNvSecContext.ucKSIsgsn        = pstCurSecuCntxt->ucKSIsgsn;
        stNvSecContext.ucKSIasme        = pstCurSecuCntxt->ucKSIasme;
        stNvSecContext.ucSecuAlg        = pstCurSecuCntxt->ucSecuAlg;
        stNvSecContext.ulUlNasCount     = pstCurSecuCntxt->ulUlNasCount;
        stNvSecContext.ulDlNasCount     = pstCurSecuCntxt->ulDlNasCount;
        NAS_LMM_MEM_CPY(                 stNvSecContext.aucKasme,
                                        pstCurSecuCntxt->aucKasme,
                                        NAS_LMM_SECU_AUTH_KEY_ASME_LEN);
    }
    else
    {
        stNvSecContext.bitOpEpsSec      = NAS_NVIM_BIT_SLCT;
        stNvSecContext.ucKSIasme        = NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE;
        stNvSecContext.ucKSIsgsn        = NAS_LMM_NKSI_NO_KEY_IS_AVAILABLE;
    }

    /* ���NV���б�����뱾��Ҫд�����ȫ��ͬ��������д�� */
    if((0 == NAS_LMM_MEM_CMP( (const VOS_VOID *)NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR(),
                              (const VOS_VOID *)&stNvSecContext,
                              sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU))))
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvEpsSecurityContext:  Don't need to write Nvim.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvEpsSecurityContext_ENUM,LNAS_FUNCTION_LABEL3);
        return;
    }


    /*write EPS SECURITY CONTEXT to NVIM*/
    ulRst = NAS_LMM_NvimWrite(       EN_NV_ID_SEC_CONTEXT,
                                    &stNvSecContext,
                                    sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU));
    if(EN_NV_OK != ulRst)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_WriteNvEpsSecurityContext: Write nvim Err!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_WriteNvEpsSecurityContext_ENUM,LNAS_ERROR);
    }
    else
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvEpsSecurityContext:Write Nvim SUCC, update last write NV EpsSecurityContext.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvEpsSecurityContext_ENUM,LNAS_FUNCTION_LABEL4);

        /* дNV�ɹ��轫����дNV���ݸ��µ��ϴ�д��EpsSecurityContext��Ϣ�� */
        NAS_LMM_MEM_SET(NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR(),
                        0,
                        NAS_NVIM_SECU_CONTEXT_MAX_LEN);

        NAS_LMM_MEM_CPY(NAS_LMM_GET_USIM_EPS_SECU_CONTEXT_ADDR(),
                        &stNvSecContext,
                        sizeof(LNAS_LMM_NV_EPS_SEC_CONTEXT_STRU));
    }


    return;
}
VOS_VOID  NAS_LMM_WriteNvPsLoc
(
    NAS_NV_ITEM_OP_TYPE_ENUM_UINT32     enOpType
)
{
    VOS_UINT32                          ulRst;
    LNAS_LMM_NV_EPS_LOC_STRU            stNvPsLoc = {0};
    NAS_LMM_UEID_STRU                    *pstUeId;
    NAS_MM_NETWORK_ID_STRU              *pstNetId;
    VOS_UINT8                          *pstLastPsLoc;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvPsLoc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvPsLoc_ENUM,LNAS_ENTRY);

    pstLastPsLoc                        =NAS_LMM_GetEmmInfoLastWriteUsimPsLocAddr();

    /*����µ�GUTI*/
    if (NAS_NV_ITEM_UPDATE == enOpType)
    {
        pstUeId                         = NAS_LMM_GetEmmInfoUeidAddr();
        pstNetId                        = NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr();
        stNvPsLoc.bitOpGuti             = pstUeId->bitOpGuti;
        stNvPsLoc.bitOpTai              = NAS_EMM_GetLVRTaiOpBit();
        stNvPsLoc.bitOpUpState          = NAS_NVIM_BIT_SLCT;

        NAS_LMM_MEM_CPY(                &(stNvPsLoc.stGuti),
                                        &(pstUeId->stGuti),
                                        sizeof(NAS_LMM_GUTI_STRU));


        NAS_LMM_MEM_CPY(                &(stNvPsLoc.stLastRegTai.stPlmnId),
                                        &(pstNetId->stPlmnId),
                                        sizeof(NAS_MM_PLMN_ID_STRU));

        NAS_LMM_MEM_CPY(                &(stNvPsLoc.stLastRegTai.stTac),
                                        &(pstNetId->stTac),
                                        sizeof(NAS_MM_TAC_STRU));

        stNvPsLoc.enUpdateState         = NAS_EMM_UPDATE_STAE;
    }
    else
    {
        NAS_LMM_MEM_SET(&stNvPsLoc, 0, sizeof(LNAS_LMM_NV_EPS_LOC_STRU));

        NAS_LMM_UndefPlmn(&stNvPsLoc.stLastRegTai.stPlmnId);
        NAS_LMM_UndefTac(&stNvPsLoc.stLastRegTai.stTac);

    }

    /* ���NV���б�����뱾��Ҫд�����ȫ��ͬ��������д�� */
    if((0 == NAS_LMM_MEM_CMP( (const VOS_VOID *)pstLastPsLoc,
                              (const VOS_VOID *)&stNvPsLoc,
                              sizeof(LNAS_LMM_NV_EPS_LOC_STRU))))
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvPsLoc:  Don't need to write Nvim.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvPsLoc_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    /*write new PS LOC to NVIM*/
    ulRst = NAS_LMM_NvimWrite(           EN_NV_ID_EPS_LOC,
                                        &stNvPsLoc,
                                        sizeof(LNAS_LMM_NV_EPS_LOC_STRU));
    if(EN_NV_OK != ulRst)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_WriteNvPsLoc: nvim ERR!!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_WriteNvPsLoc_ENUM,LNAS_ERROR);
    }
    else
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteNvPsLoc:Write Nvim SUCC, update last write NV EPS LOC  info.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteNvPsLoc_ENUM,LNAS_FUNCTION_LABEL2);

        /* дNV�ɹ��轫����дNV���ݸ��µ��ϴ�д��PS LOC��Ϣ�� */
        NAS_LMM_MEM_CPY( pstLastPsLoc,
                         &stNvPsLoc,
                         sizeof(LNAS_LMM_NV_EPS_LOC_STRU));
    }

    return;
}


VOS_VOID  NAS_LMM_WriteSimPsLoc( VOS_VOID )
{

    LNAS_LMM_NV_EPS_LOC_STRU             stNvPsLoc;
    NAS_LMM_UEID_STRU                    *pstUeid;
    NAS_MM_GUTI_STRU                    *pstGuti;
    NAS_MM_NETWORK_ID_STRU              *pstNetId;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteSimPsLoc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteSimPsLoc_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_SET(&stNvPsLoc, 0, sizeof(LNAS_LMM_NV_EPS_LOC_STRU));

    pstUeid                             = NAS_LMM_GetEmmInfoUeidAddr();
    pstGuti                             = NAS_LMM_GetEmmInfoUeidGutiAddr();
    pstNetId                            = NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr();

    /*GUTI�����*/
    if (NAS_NVIM_BIT_NO_SLCT == pstUeid->bitOpGuti)
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_WriteSimPsLoc : GUTI Invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_WriteSimPsLoc_ENUM,LNAS_FUNCTION_LABEL1);

        NAS_LMM_SetArrayAllBytesFF((VOS_UINT8 *)&stNvPsLoc.stGuti,
                                   sizeof(NAS_LMM_GUTI_STRU));
        stNvPsLoc.stGuti.stGutiHead.ucLenth = NAS_LMM_NVIM_GUTI_AND_OETOI_LEN;
        stNvPsLoc.stGuti.stGutiHead.ucOeToi = NAS_LMM_NVIM_GUTI_OETOI;

    }
    else
    {

        NAS_LMM_MEM_CPY(                &stNvPsLoc.stGuti,
                                        pstGuti,
                                        sizeof(NAS_LMM_GUTI_STRU));
    }

    /*L.V.R TAI�����*/
    if (NAS_NVIM_BIT_NO_SLCT == NAS_EMM_GetLVRTaiOpBit())
    {
        NAS_LMM_NVIM_LOG_ERR("NAS_LMM_WriteSimPsLoc : L.V.R Invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_WriteSimPsLoc_ENUM,LNAS_FUNCTION_LABEL2);
        NAS_LMM_UndefPlmn(&stNvPsLoc.stLastRegTai.stPlmnId);
        NAS_LMM_UndefTac(&stNvPsLoc.stLastRegTai.stTac);
    }
    else
    {
        NAS_LMM_MEM_CPY(                &stNvPsLoc.stLastRegTai.stPlmnId,
                                        &(pstNetId->stPlmnId),
                                        sizeof(NAS_MM_PLMN_ID_STRU));

        NAS_LMM_MEM_CPY(                &stNvPsLoc.stLastRegTai.stTac,
                                        &(pstNetId->stTac),
                                        sizeof(NAS_MM_TAC_STRU));
    }

    /*EU����д*/
    stNvPsLoc.enUpdateState             = NAS_EMM_UPDATE_STAE;

    /*write new PS LOC to USIM*/
    NAS_LMM_UsimFileWrite(USIMM_USIM_EFEPSLOCI_ID,
                          &stNvPsLoc,
                          sizeof(LNAS_LMM_NV_EPS_LOC_STRU));

    return;
}


VOS_VOID  NAS_LMM_WriteEpsSecuContext( NAS_NV_ITEM_OP_TYPE_ENUM_UINT32 enOpType )
{
    VOS_UINT32                          ulRslt;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WriteEpsSecuContext enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_WriteEpsSecuContext_ENUM,LNAS_ENTRY);
    /* ������ǰ��ȫ������ */
    NAS_EMM_SndOmLogEpsSecContextInfo();

    if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
    {
        return ;
    }
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    ulRslt = NAS_EMM_IsServiceAvailable(USIM_SVR_EPS_INFO);

    if (PS_USIM_SERVICE_AVAILIABLE == ulRslt)
    {
        /* ��USIMд��EPS SECURITY CONTEXT */
        NAS_LMM_WriteSimEpsSecurityContext(enOpType);
    }
    else
    {
        /*��NV��д��EPS SECURITY CONTEXT*/
        NAS_LMM_WriteNvEpsSecurityContext(enOpType);
    }
    /*PC REPLAY MODIFY BY LEILI END*/

    return;
}
VOS_VOID  NAS_LMM_WritePsLoc
(
    NAS_NV_ITEM_OP_TYPE_ENUM_UINT32     enOpType
)
{
    VOS_UINT32                          ulRslt;

    NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WritePsLoc enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_WritePsLoc_ENUM,LNAS_ENTRY);

    /* �ϱ�EPS  LOC ��Ϣ */
    NAS_EMM_SndOmLogEpsLocInfo();

    if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_LMM_WritePsLoc: USIM is unavailable!.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_WritePsLoc_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    ulRslt = NAS_EMM_IsServiceAvailable(USIM_SVR_EPS_INFO);
    if (PS_USIM_SERVICE_AVAILIABLE == ulRslt)
    {
        /*��USIMд��PS LOC*/
        NAS_LMM_WriteSimPsLoc();
    }
    else
    {
        /*��NV��д��PS LOC*/
        NAS_LMM_WriteNvPsLoc(enOpType);
    }
    /*PC REPLAY MODIFY BY LEILI END*/

    return;
}

/*leili modify for isr begin*/

VOS_VOID  NAS_EMM_SetTinType(MMC_LMM_TIN_TYPE_ENUM_UINT32 ulTinType)
{
    NAS_NVIM_TIN_INFO_STRU         stNvTinType;
    VOS_UINT32                          ulRslt;

    NAS_LMM_MEM_SET(&stNvTinType, 0, sizeof(NAS_NVIM_TIN_INFO_STRU));

    /* ��ȫ�ֱ����е�TIN*/

    /*����MML����*/
    NAS_MML_SetTinType((VOS_UINT8)ulTinType);

    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
    NAS_LMM_LogTinInfo(ulTinType,PS_PID_MM,PS_PID_MM);
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */

    /* ����ǽ���ע������л��߽���ע�ᣬ��ֱ���˳�����дNV */
    if ((NAS_LMM_REG_STATUS_EMC_REGING == NAS_LMM_GetEmmInfoRegStatus())
         || (NAS_LMM_REG_STATUS_EMC_REGED == NAS_LMM_GetEmmInfoRegStatus()))
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_EMM_SetTinType : Need not write nv!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SetTinType_ENUM,LNAS_FUNCTION_LABEL1);
        return ;
    }
    /*lint -e718*/
    /*lint -e732*/
    /*lint -e516*/
    /*lint -e746*/
    /*lint -e830*/
    ulRslt = LPs_NvimItem_Read(en_NV_Item_TIN_INFO, &stNvTinType, sizeof(NAS_NVIM_TIN_INFO_STRU));
    /*lint +e830*/
    /*lint +e746*/
    /*lint +e516*/
    /*lint +e732*/
    /*lint +e718*/
    if ((ERR_MSP_SUCCESS != ulRslt) || (MMC_LMM_TIN_INVALID < stNvTinType.ucTinType))
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_EMM_SetTinType:read NVIM fail or Value Invalid!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SetTinType_ENUM,LNAS_FUNCTION_LABEL2);
    }

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_SetTinType: read NV ITEM VALUE:IMSI = \n");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SetTinType_ENUM,LNAS_FUNCTION_LABEL3);
    NAS_COMM_PrintArray(                NAS_COMM_GET_MM_PRINT_BUF(),
                                        stNvTinType.aucImsi,
                                        NVIM_ITEM_MAX_IMSI_LEN);

    NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_SetTinType: read NV ITEM VALUE:ulTinType = ",stNvTinType.ucTinType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SetTinType_ENUM,LNAS_EMM_TIN_TYPE,stNvTinType.ucTinType);

    /*��� NV  TIN �ṹ*/
    stNvTinType.ucTinType = (VOS_UINT8)ulTinType;
    /*lint -e718*/
    /*lint -e746*/
    /*lint -e732*/
    /*lint -e516*/
    ulRslt = LPs_NvimItem_Write(en_NV_Item_TIN_INFO, &stNvTinType, sizeof(NAS_NVIM_TIN_INFO_STRU));
    /*lint +e516*/
    /*lint +e732*/
    /*lint +e746*/
    /*lint +e718*/
    if (ERR_MSP_SUCCESS != ulRslt)
    {
        NAS_LMM_NVIM_LOG_INFO("NAS_EMM_SetTinType:write NVIM fail!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SetTinType_ENUM,LNAS_FAIL);
    }


    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_SetTinType: write NV ITEM VALUE:IMSI = \n");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SetTinType_ENUM,LNAS_FUNCTION_LABEL4);
    NAS_COMM_PrintArray(                NAS_COMM_GET_MM_PRINT_BUF(),
                                           stNvTinType.aucImsi,
                                           NAS_MML_MAX_IMSI_LEN);

    NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_SetTinType: write NV ITEM VALUE:ulTinType = ",stNvTinType.ucTinType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SetTinType_ENUM,LNAS_FUNCTION_LABEL5,stNvTinType.ucTinType);


    return;
}
/*leili modify for isr end*/

VOS_VOID NAS_EMM_WriteNvMmInfo(VOS_VOID)
{
    if (NAS_LMM_SIM_STATUS_AVAILABLE == NAS_LMM_GetSimState())
    {
        /*���氲ȫ������*/
        NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);

        /* �ж�û�зŵ�����NAS_LMM_WritePsLoc�������������ڽ���ע�ᱻ�ܻ��߳���
           �����ﵽ5��ʱ����Ҫɾ������ ��Э��ֻ�涨�ǽ���ע��ɹ���Ų�д������
           NV�� */
        if ((NAS_LMM_REG_STATUS_EMC_REGING != NAS_LMM_GetEmmInfoRegStatus())
            && (NAS_LMM_REG_STATUS_EMC_REGED != NAS_LMM_GetEmmInfoRegStatus()))
        {
            /*����PS LOC��Ϣ*/
            NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
        }


        /*GUά����L���� дNV*/
        /*NAS_LMM_WriteGuUeMode();*/
    }

    return;
}
VOS_VOID NAS_LMM_GetImeisvFromImei(VOS_VOID)
{

    VOS_UINT8                           aucImeiSvn[4] = {0,0,0,0};

    if (NAS_EMM_BIT_SLCT != NAS_LMM_GetEmmInfoUeidAddr()->bitOpImei)
    {
        NAS_LMM_ReadNvimImei();
    }

    NAS_LMM_GetEmmInfoUeidAddr()->bitOpImeisv   = NAS_EMM_BIT_SLCT;
    NAS_LMM_MEM_CPY(                     NAS_LMM_GetEmmInfoUeidImeisvAddr(),
                                        NAS_LMM_GetEmmInfoUeidImeiAddr(),
                                        NAS_MM_MAX_UEID_BUF_SIZE);
    NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[0] =  0x09; /*����Ϊ�̶�ֵ9*/
    NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[1] &= 0xF0;
    NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[1] |= 0x03;
    NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[8] &= 0x0F;
    NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[9] = 0xF0;

    /* ��ȡIMEISV������ */
    /*lint -e516*/
    if (NV_OK != NVM_Read(en_NV_Item_Imei_Svn,
                   aucImeiSvn, sizeof(aucImeiSvn)))
    {
       NAS_LMM_PUBM_LOG_WARN("NAS_LMM_GetImeisvFromImei:Read Nvim Failed");
       TLPS_PRINT2LAYER_WARNING(NAS_LMM_GetImeisvFromImei_ENUM,LNAS_FAIL);
       return;
    }
    /*lint +e516*/

    /* NV����Ч,����� */
    if (VOS_TRUE == aucImeiSvn[0])
    {
        NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[8] &= 0x0F;
        NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[9] &= 0x00;
        NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[8] |= (VOS_UINT8)(aucImeiSvn[1] << NAS_LMM_MOVEMENT_4_BITS);
        NAS_LMM_GetEmmInfoUeidAddr()->aucImeisv[9] |= (aucImeiSvn[2] | 0xF0);
    }

     /* ��ӡ��ȡ����IMEISVֵ */
    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_GetImeisvFromImei: IMEISV value is :");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_GetImeisvFromImei_ENUM,LNAS_FUNCTION_LABEL1);
    NAS_COMM_PrintArray(NAS_COMM_GET_MM_PRINT_BUF(),
                   NAS_LMM_GetEmmInfoUeidImeisvAddr(),
                   NAS_MM_MAX_UEID_BUF_SIZE);

    return;
}



/***************************************************************************
 Function Name  :NAS_EMM_GetEmmGlobleAddr
 Discription    :���ڵ�������ģ���ȫ�ֱ���
 Input          :
 Output         : None
 Return         : None
 History:
      1.  yangfan  2009-10-19  Draft Enact
*****************************************************************************/
VOS_UINT32  * NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PARA_ENUM_UINT32 ulGlobleParaName)
{
    VOS_UINT32  * pucGlobleAddr;

    /* PRINT */

    switch(ulGlobleParaName )
    {
        case    NAS_LMM_GLOBLE_PARA_IMSI:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoUeidImsiAddr();
            break;

        case    NAS_LMM_GLOBLE_PARA_UEID:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoUeidAddr();
            break;

        case    NAS_LMM_GLOBLE_PARA_MNC_LEN:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoUeidImsiMncLenAddr();
            break;

        case    NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr();
            break;
        case    NAS_LMM_GLOBLE_FORB_TA_FOR_RPOS:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoNetInfoForbTaForRposAddr();
            break;
        case    NAS_LMM_GLOBLE_PRESENT_NET_ID:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoNetInfoPresentNetAddr();
            break;
        case    NAS_LMM_GLOBLE_NET_INFO:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoNetInfoAddr();
            break;

        case    NAS_LMM_GLOBLE_TA_LIST:
            pucGlobleAddr = (VOS_VOID * )NAS_LMM_GetEmmInfoNetInfoTaiListAddr();
            break;

        default :
            pucGlobleAddr = VOS_NULL;
            break;
    }

    return pucGlobleAddr;
}
VOS_VOID  NAS_EMM_SendIntraConn2IdleReq( VOS_VOID )
{
    NAS_EMM_INTRA_CONN2IDLE_REQ_STRU   *pIntraConn2IdleReq = NAS_LMM_NULL_PTR;
    VOS_UINT32                          ulLen;

    /*ȷ����Ϣ����*/
/*    ulLen = NAS_EMM_GIM_VOS_MSG_HEADER_LEN + NAS_EMM_MSG_ID_LEN;*/
    ulLen = sizeof(NAS_EMM_INTRA_CONN2IDLE_REQ_STRU);

    /*����ռ�*/
    pIntraConn2IdleReq  = (VOS_VOID *)NAS_LMM_GetSendIntraMsgBuffAddr(ulLen);
    if(NAS_EMM_NULL_PTR == pIntraConn2IdleReq)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SendIntraConn2IdleReq: INTRA MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendIntraConn2IdleReq_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* ���VOS��Ϣͷ */
    NAS_EMM_INTRA_MSG_HEADER(pIntraConn2IdleReq,(ulLen-NAS_EMM_GIM_VOS_MSG_HEADER_LEN));

    /* ���DOPRA��ϢID    */
    pIntraConn2IdleReq->ulMsgId = ID_NAS_LMM_INTRA_CONN2IDLE_REQ;

    /*�����ڲ���Ϣ�����*/
    NAS_EMM_SEND_INTRA_MSG(pIntraConn2IdleReq);

    return;
}


VOS_VOID  NAS_EMM_CommProcConn2Ilde( VOS_VOID )
{
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_CommProcConn2Ilde enter!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CommProcConn2Ilde_ENUM,LNAS_ENTRY);

    /*�����ǰ����״̬����IDLE������ MMC�ϱ�*/
    if((NAS_EMM_CONN_IDLE != NAS_EMM_GetConnState())
        && (NAS_EMM_CONN_WAIT_SYS_INFO != NAS_EMM_GetConnState()))
    {
        NAS_EMM_SendMmcStatusInd(MMC_LMM_STATUS_TYPE_CONN_STATE,
                                 MMC_LMM_CONN_IDLE);
    }

    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState())
        || (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState())
        || (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState()))
    {
        /*������״̬���ó�NAS_EMM_CONN_WAIT_SYS_INFO�� ��ǰRRC��ǰ����·��������
          ���������ͷ���·��RRC��Ҫ����������LNAS�ȴ�LRRC�ϱ�ϵͳ��Ϣ��
        */
        NAS_EMM_SetConnState(NAS_EMM_CONN_WAIT_SYS_INFO);
    }
    else
    {
        /* ��RRC����״̬����ΪIDLE */
        NAS_EMM_SetConnState(NAS_EMM_CONN_IDLE);
    }

    if (NAS_LMM_CONNECTION_CLIENT_ID_SMS == NAS_LMM_GetConnectionClientId())
    {
        NAS_LMM_SndLmmSmsErrInd(LMM_SMS_ERR_CAUSE_OTHERS);
        NAS_LMM_SetConnectionClientId(NAS_LMM_CONNECTION_CLIENT_ID_NULL);
    }
    /*����̬��CONN����IDLE�����µ�ǰ��ȫ������״̬�仯*/
    NAS_EMM_ConnToIdleTransSecuSta();

    /*�����ڲ���Ϣ:INTRA_CONN2IDLE_REQ*/
    NAS_EMM_SendIntraConn2IdleReq();

    return;
}
VOS_VOID NAS_EMM_SaveAppMsgPara( VOS_UINT32 ulMsgId, VOS_UINT32 ulOpId)
{
    g_stEmmInfo.bitOpAppPara         = NAS_EMM_BIT_SLCT;
    g_stEmmInfo.stAppPara.ulMsgId    = ulMsgId;
    g_stEmmInfo.stAppPara.ulOpId     = ulOpId;

    return;
}



VOS_VOID  NAS_EMM_ClearAppMsgPara( VOS_VOID )
{
    /*���APP����*/
    g_stEmmInfo.bitOpAppPara       = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_MEM_SET(                &g_stEmmInfo.stAppPara,
                                   0,
                                   sizeof(NAS_LMM_APP_PARA_STRU));
}
VOS_UINT32  NAS_EMM_CheckAppMsgPara( VOS_UINT32 ulMsgId )
{
    if ((ulMsgId              == g_stEmmInfo.stAppPara.ulMsgId)
        && (NAS_EMM_BIT_SLCT  == g_stEmmInfo.bitOpAppPara))
    {
        return                   VOS_OK;
    }
    else
    {
        return                   VOS_ERR;
    }
}


VOS_UINT32  NAS_EMM_GetAppMsgOpId( VOS_VOID )
{
    return                      g_stEmmInfo.stAppPara.ulOpId;
}


VOS_VOID  NAS_LMM_CountSysInfo( VOS_UINT16 usSubState )
{
    NAS_LMM_SYSINFO_COUNT_STRU           *pstSysInfoCnt;

    pstSysInfoCnt                      = NAS_EMM_GetSysInfCntAddr();

    switch( usSubState )
    {
        case    EMM_SS_RRC_CONN_WAIT_EST_CNF:
            pstSysInfoCnt->ulEstCnfCount++;
            NAS_LMM_PUBM_LOG1_INFO("MsRrcConnEstInitSsWaitRrcEstCnf: Receive SysInfo ",pstSysInfoCnt->ulEstCnfCount);
            TLPS_PRINT2LAYER_INFO1(NAS_LMM_CountSysInfo_ENUM,LNAS_FUNCTION_LABEL1,pstSysInfoCnt->ulEstCnfCount);
            break;

        case    EMM_SS_RRC_CONN_WAIT_REL_CNF:
            pstSysInfoCnt->ulRelCnfCount++;
            NAS_LMM_PUBM_LOG1_INFO("MsRrcConnRelInitSsWaitRrcRelCnf: Receive SysInfo ",pstSysInfoCnt->ulRelCnfCount);
            TLPS_PRINT2LAYER_INFO1(NAS_LMM_CountSysInfo_ENUM,LNAS_FUNCTION_LABEL2,pstSysInfoCnt->ulRelCnfCount);
            break;

        /*case    EMM_SS_ATTACH_WAIT_RRC_REL_IND:
            pstSysInfoCnt->ulRegInitRrcRelIndCount++;
            NAS_LMM_PUBM_LOG1_INFO("MsRegInitSsWaitRrcRelInd: Receive SysInfo ",pstSysInfoCnt->ulRegInitRrcRelIndCount);
            break;*/


        default :
            NAS_LMM_PUBM_LOG_ERR("NAS_LMM_CountSysInfo,Error State!");
            TLPS_PRINT2LAYER_ERROR(NAS_LMM_CountSysInfo_ENUM,LNAS_ERROR);
            break;
    }

}


VOS_VOID  NAS_LMM_EmmInfoInit( VOS_VOID )
{
    NAS_EMM_PubmInfoUeIdInit();
    NAS_EMM_PubmInfoNetInfoInit();
    NAS_EMM_PubmInfoSupCodecListInit();
    NAS_EMM_PubmInfoBearerContextInit();
    NAS_EMM_PubmInfoDrxInit();

    NAS_EMM_PubmInfoUeModeInit();

    /*����IMSI�Ķ�ȡ���ÿ�״̬*/
    /* NAS_EMM_InitSimState();*/
    NAS_EMM_SetUsimState(NAS_LMM_SIM_STATUS_UNAVAILABLE);

    NAS_LMM_SetPsSimValidity(NAS_LMM_SIM_VALID);

    /* ����������ֵ */
    NAS_EMM_GetTransceiverType()        = NAS_EMM_TRANSCEIVER_TYPE_BUTT;
    NAS_LMM_GetCurGsmPrio()             = NAS_LMM_RAT_PRIO_BUTT;
    NAS_LMM_GetCurWcdmaPrio()           = NAS_LMM_RAT_PRIO_BUTT;
    NAS_LMM_GetCurLtePrio()             = NAS_LMM_RAT_PRIO_BUTT;
    /*leili modify for isr begin*/
    NAS_LMM_SetTempEmmInfoTinType(MMC_LMM_TIN_BUTT);
    /*leili modify for isr end*/

    NAS_EMM_GetEmmInfoDamParaT3402Len() = NAS_LMM_TIMER_T3402_LEN;
    NAS_EMM_GetEmmInfoDamParaCserviceCnt() = 0;

    return;
}
VOS_VOID  NAS_EMM_ReadEmmNvim( VOS_VOID )
{
    /*�޿�����ʱ���ȡ�Ļ���������NV*/
    NAS_EMM_ReadNvimNoImsi();

}
VOS_VOID  NAS_EMM_ReadNvimNoImsi( VOS_VOID )
{
    /*read IMEI from NVIM*/
    NAS_LMM_ReadNvimImei();

    /*caculate Imeisv with IMEI*/
    NAS_LMM_GetImeisvFromImei();



    /*read UeNetCap from NVIM*/
    NAS_EMM_ReadNvUeNetCap();

    /*read ue operation mode from NVIM*/
    /*NAS_EMM_ReadNvUeOperationMode();*/

    /*read CsService from NVIM*/
    /* lihong00150010 csfb begin */

    /*NAS_EMM_ReadNvCsService();*/

    /* lihong00150010 csfb end */

    /*read Voice Domain for E-UTRAN from NVIM*/
    NAS_EMM_ReadNvVoiceDomain();

    /* ��NV���ж�ȡUE's setting�������õ�MML�� */
    NAS_EMM_ReadNvUeSetting();


    /*read ClassMark from NVIM*/
    /*NAS_EMM_ReadNvClassMark();*/

    /*read Drx from NVIM*/
    /*NAS_EMM_ReadNvDrx();*/

    /*read RaMod from NVIM*/
    /*NAS_EMM_ReadNvRaMod();  */
    NAS_EMM_ReadNvNasRelease();

    /*sunbing 49683 2013-10-21 VoLTE begin*/
    NAS_EMM_ReadNvCodecSupportList();
    /*sunbing 49683 2013-10-21 VoLTE end*/
    /*self-adaption NW cause modify begin for leili*/
    NAS_EMM_ReadNvConfigNwCause();
    /*self-adaption NW cause modify end for leili*/

    NAS_LMM_ReadNvDamParaCServiceAndPlmnList();
    NAS_LMM_ReadNvLmmCommConfigPara();
    /*  LNAS���ܿ���NV��ȡ */
    NAS_LMM_ReadNvLmmSwitchPara();
    NAS_EMM_SndOmLogUeImportantCapabilityInfo();
    NAS_EMM_SndOmLogUeIdInfo();
    /* ������ǰ��ȫ������ */
    NAS_EMM_SndOmLogEpsSecContextInfo();
    /* ����EPS LOC��Ϣ */
    NAS_EMM_SndOmLogEpsLocInfo();
    /* add by yanglei 00307272 for KEY_INFO_REPORT3,2015-08-17,begin */
    NAS_LMM_SndOmStaticUeIdInfo();
    /* add by yanglei 00307272 for KEY_INFO_REPORT3,2015-08-17,end */
}
VOS_VOID  NAS_EMM_NoUsimInit( VOS_VOID )
{
    /* ɾ�����ñ��� */

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_NoUsimInit IS ENTERED ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_NoUsimInit_ENUM,LNAS_ENTRY);

    /****�޿������³�ʼ��EMM*****/
    /* ��NV�ж�ȡ�޿�״̬������Ҫ���� */
    NAS_EMM_ReadNvimNoImsi();

    /*Ϊ����ڹ��Ų����ӿ�һ���Բ���ʱ,����ʱ�ֻ�����ʱ����PIN��,�޿���������˺���ɾ����NV�еİ�ȫ�����ģ�����ʧ��,
      ���ڸ�NV���汾����Ĭ�ϴ�, �������ٴβ忨����, ��IMSI��ͬ�Ļ���ɾ����ȫ������, ����Ϊ��ֹ��Ѹ�NV�رյ�������
      ʧ��, �˴��޿�ɾ����ȫ�����Ĵ���ɾ��*/

    /*�޿������£�����ɾ��NV�е�PS LOC*/
    /*NAS_LMM_WriteNvPsLoc(0);*/

    NAS_EMM_PubmInfoNetInfoInit();
    NAS_EMM_SecuInit();

    return;

}
/* del by lihong00150010 emergency tau&service */

VOS_UINT32  NAS_LMM_CheckPlmnAct(VOS_UINT8 const *pucPlmn)
{

    if ((NAS_LMM_NULL == (pucPlmn[NAS_EMM_PLMNACT_IDEN] & NAS_LMM_BYTE_FF))
        && (NAS_LMM_NULL == (pucPlmn[NAS_EMM_PLMNACT_IDEN + 1] & NAS_LMM_BYTE_FF)))
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_CheckPlmnAct: PLMNAct is support");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_CheckPlmnAct_ENUM,LNAS_FUNCTION_LABEL1);
        return VOS_OK;
    }
    switch ( NAS_LMM_GetEmmInfoRaMod())
    {
        case    NAS_MM_RAT_LTE_FDD:
        case    NAS_MM_RAT_LTE_TDD:
            if (NAS_EMM_PLMNACT_LTE == (pucPlmn[NAS_EMM_PLMNACT_IDEN] & NAS_EMM_PLMNACT_LTE))
            {
                NAS_LMM_PUBM_LOG_INFO("NAS_LMM_CheckPlmnAct: PLMNAct: LTE");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_CheckPlmnAct_ENUM,LNAS_FUNCTION_LABEL2);
                return VOS_OK;
            }
            break;

        case    NAS_MM_RAT_WCDMA:
        case    NAS_MM_RAT_GSM_GPRS:
            break;

        default:
            break;
    }

    NAS_LMM_PUBM_LOG_WARN("NAS_LMM_CheckPlmnAct: PLMNAct: NO LTE");
    TLPS_PRINT2LAYER_WARNING(NAS_LMM_CheckPlmnAct_ENUM,LNAS_FUNCTION_LABEL3);
    return VOS_ERR;

}


VOS_VOID NAS_EMM_ClearTaiList( VOS_VOID )
{
    NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpTaiList  = NAS_EMM_BIT_NO_SLCT;

    /*ɾ��TA LIST*/
    NAS_LMM_MEM_SET(           NAS_LMM_GetEmmInfoNetInfoTaiListAddr(),
                              0,
                              sizeof(NAS_EMM_TA_LIST_STRU));
}
VOS_VOID  NAS_EMM_ClearLVRTai( VOS_VOID )
{
    /*ɾ�� L.V.R TAI*/
    NAS_LMM_GetEmmInfoNetInfoAddr()->bitOpLastRegNetId      = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr()->bitOpTac     = NAS_EMM_BIT_NO_SLCT;

    NAS_LMM_UndefPlmn(NAS_LMM_GetEmmInfoLastRegPlmnAddr());
    NAS_LMM_UndefTac(NAS_LMM_GetEmmInfoLastRegTacAddr());

}
VOS_VOID  NAS_EMM_SetLVRTacInvalid( VOS_VOID )
{
    NAS_LMM_UndefTac(NAS_LMM_GetEmmInfoLastRegTacAddr());

    if (NAS_EMM_BIT_NO_SLCT == NAS_EMM_GetLVRTaiOpBit())
    {
        NAS_LMM_UndefPlmn(NAS_LMM_GetEmmInfoLastRegPlmnAddr());
    }
    return;
}




VOS_UINT32 NAS_EMM_GetLVRTaiOpBit(VOS_VOID)
{
    NAS_LMM_NETWORK_INFO_STRU            *pstNetInfo;
    VOS_UINT32                          ulRslt;

    pstNetInfo = NAS_LMM_GetEmmInfoNetInfoAddr();

    ulRslt = (pstNetInfo->bitOpLastRegNetId) && (pstNetInfo->stLastRegNetId.bitOpTac);

    return ulRslt;
}


VOS_VOID  NAS_EMM_SetLVRTai(const NAS_MM_NETWORK_ID_STRU *pstNetId)
{
    NAS_LMM_NETWORK_INFO_STRU            *pstNetInfo;

    pstNetInfo = NAS_LMM_GetEmmInfoNetInfoAddr();

    if (NAS_EMM_NULL_PTR == pstNetId)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_SetLVRTai: Point is null");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SetLVRTai_ENUM,LNAS_NULL_PTR);

        return;
    }

    pstNetInfo->bitOpLastRegNetId       = NAS_EMM_BIT_SLCT;
    pstNetInfo->stLastRegNetId.bitOpTac = NAS_EMM_BIT_SLCT;

    NAS_LMM_MEM_CPY (                    &pstNetInfo->stLastRegNetId.stPlmnId,
                                        &pstNetId->stPlmnId,
                                        sizeof(NAS_MM_PLMN_ID_STRU));

    NAS_LMM_MEM_CPY (                    &pstNetInfo->stLastRegNetId.stTac,
                                        &pstNetId->stTac,
                                        sizeof(NAS_MM_TAC_STRU));
    return;
}


VOS_VOID  NAS_EMM_SetGuti
(
    const NAS_EMM_GUTI_STRU *pstGuti
)
{
    NAS_LMM_UEID_STRU                   *pstUeId;

    pstUeId = NAS_LMM_GetEmmInfoUeidAddr();

    if (NAS_EMM_NULL_PTR == pstGuti)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_SetGuti: Point is null");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SetGuti_ENUM,LNAS_NULL_PTR);

        return;
    }

    pstUeId->bitOpGuti                  = NAS_EMM_BIT_SLCT;
    NAS_LMM_MEM_CPY (                   &(pstUeId->stGuti),
                                        pstGuti,
                                        sizeof(NAS_LMM_GUTI_STRU));
    return;
}



VOS_UINT32  NAS_EMM_UpdatePresentPlmnInfo(VOS_VOID)
{
    VOS_UINT32                          ulCount          = 0;
    VOS_UINT32                          ulUpdateResult   = NAS_EMM_FAIL;
    NAS_LMM_UEID_STRU                  *pstMmUeId        = NAS_EMM_NULL_PTR;
    NAS_MM_PLMN_ID_STRU                *pstPresentPlmnId = NAS_EMM_NULL_PTR;
    NAS_MM_GUTI_STRU                   *pstGuti          = NAS_EMM_NULL_PTR;

    pstGuti          = NAS_LMM_GetEmmInfoUeidGutiAddr();
    pstMmUeId        = NAS_LMM_GetEmmInfoUeidAddr();
    pstPresentPlmnId = NAS_LMM_GetEmmInfoPresentPlmnAddr();

    /* ����GUTI, ����Present Plmn ID ��GUTI�е�Plmn ID��ͬ, ��Present Plmn ID���³�GUTI�е�Plmn ID */
    if ( NAS_EMM_BIT_SLCT== pstMmUeId->bitOpGuti )
    {
        for ( ulCount = 0; ulCount < 3; ulCount++ )
        {
            if ( pstPresentPlmnId->aucPlmnId[ulCount] != pstGuti->stPlmnId.aucPlmnId[ulCount] )
            {
                pstPresentPlmnId->aucPlmnId[ulCount] = pstGuti->stPlmnId.aucPlmnId[ulCount];
                ulUpdateResult = NAS_EMM_SUCC;
            }
        }
    }

    return   ulUpdateResult;

}
VOS_UINT32 NAS_EMM_GetMmlFormatMcc
(
    const NAS_MM_PLMN_ID_STRU             *pstPlmnId
)
{
    VOS_UINT32                          ulMcc       = NAS_EMM_NULL;
    VOS_UINT8                           ucMccDigit  = NAS_EMM_NULL;

    /* ��ȡMCC DIGIT1 */
    ucMccDigit  = pstPlmnId->aucPlmnId[0] & NAS_EMM_LOW_4_BIT;
    ulMcc       |=  ucMccDigit;

    /* ��ȡMCC DIGIT2 */
    ucMccDigit  = (pstPlmnId->aucPlmnId[0] & NAS_EMM_HIGH_4_BIT) >> NAS_EMM_MOVEMENT_4_BITS;
    ulMcc       |=  (ucMccDigit << NAS_EMM_MOVEMENT_8_BITS);

    /* ��ȡMCC DIGIT3 */
    ucMccDigit  = pstPlmnId->aucPlmnId[1] & NAS_EMM_LOW_4_BIT;
    ulMcc       |=  (ucMccDigit << NAS_EMM_MOVEMENT_16_BITS);

    return ulMcc;
}
/* lihong00150010 csfb begin */


VOS_UINT32 NAS_EMM_IsMccChanged( VOS_VOID )
{
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstMmlEmerNumLIst   = VOS_NULL_PTR;
    VOS_UINT32                          ulMcc               = NAS_EMM_NULL;

    pstMmlEmerNumLIst = NAS_EMM_GetEmergencyListFromMml();

    /* ��ȡ��ǰPLMN�е�MCC����ʽ��MML��һ�� */
    ulMcc = NAS_EMM_GetMmlFormatMcc(NAS_LMM_GetEmmInfoPresentPlmnAddr());

    /* �жϵ�ǰ����PLMN�е�MCC��MML�д洢��MCC�Ƿ�һ�� */
    if (ulMcc == (pstMmlEmerNumLIst->ulMcc & NAS_EMM_LOW_3_BYTE_F))
    {
        return VOS_FALSE;
    }
    return VOS_TRUE;
}

VOS_UINT32 NAS_EMM_IsUSAMcc(VOS_UINT32 ulMcc)
{
    if ((ulMcc & NAS_EMM_FIRST_BYTE_F) == 0x03)
    {
        if (((ulMcc & NAS_EMM_SECOND_BYTE_F) >> NAS_EMM_MOVEMENT_8_BITS) == 0x01)
        {
            if (((ulMcc & NAS_EMM_THIRD_BYTE_F)>> NAS_EMM_MOVEMENT_16_BITS) < 0x07)
            {
                return VOS_TRUE;
            }
        }
    }
    return VOS_FALSE;
}

VOS_UINT32 NAS_EMM_IsIndiaMcc(VOS_UINT32 ulMcc)
{
    if ((ulMcc & NAS_EMM_FIRST_BYTE_F) == 0x04)
    {
        if (((ulMcc & NAS_EMM_SECOND_BYTE_F) >> NAS_EMM_MOVEMENT_8_BITS) == 0x00)
        {
            if ((((ulMcc & NAS_EMM_THIRD_BYTE_F) >> NAS_EMM_MOVEMENT_16_BITS) > 0x03) &&
                (((ulMcc & NAS_EMM_THIRD_BYTE_F) >> NAS_EMM_MOVEMENT_16_BITS) < 0x07) )
            {
                return VOS_TRUE;
            }
        }
    }
    return VOS_FALSE;
}

VOS_UINT32 NAS_EMM_IsCountryChanged()
{
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstMmlEmerNumLIst   = VOS_NULL_PTR;
    VOS_UINT32                          ulMcc               = NAS_EMM_NULL;

    pstMmlEmerNumLIst = NAS_EMM_GetEmergencyListFromMml();

    /* ��ȡ��ǰPLMN�е�MCC����ʽ��MML��һ�� */
    ulMcc = NAS_EMM_GetMmlFormatMcc(NAS_LMM_GetEmmInfoPresentPlmnAddr());

    /* �жϵ�ǰ����PLMN�е�MCC��MML�д洢��MCC�Ƿ�����������MCC */
    if ((VOS_TRUE == NAS_EMM_IsUSAMcc(ulMcc)) &&
        (VOS_TRUE == NAS_EMM_IsUSAMcc(pstMmlEmerNumLIst->ulMcc)))
    {
        return VOS_FALSE;
    }
    /* �жϵ�ǰ����PLMN�е�MCC��MML�д洢��MCC�Ƿ�����ӡ�ȵ�MCC */
    if ((VOS_TRUE == NAS_EMM_IsIndiaMcc(ulMcc)) &&
        (VOS_TRUE == NAS_EMM_IsIndiaMcc(pstMmlEmerNumLIst->ulMcc)))
    {
        return VOS_FALSE;
    }

    /* �жϵ�ǰ����PLMN�е�MCC��MML�д洢��MCC�Ƿ�һ�� */
    if (ulMcc == (pstMmlEmerNumLIst->ulMcc & NAS_EMM_LOW_3_BYTE_F))
    {
        return VOS_FALSE;
    }
    return VOS_TRUE;
}


VOS_VOID  NAS_EMM_PrintEmergencyList
(
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstMmlEmerNumList
)
{
    VOS_UINT32                          ulMcc           = NAS_EMM_NULL;
    VOS_UINT8                           ucMccDigit      = NAS_EMM_NULL;
    VOS_UINT32                          ulLoop          = NAS_EMM_NULL;
    VOS_UINT32                          ulLoop2         = NAS_EMM_NULL;
    NAS_MML_EMERGENCY_NUM_STRU         *pstMmlEmerNum   = VOS_NULL_PTR;

    /*add by lifuxin00253982 pc-lint error */
    if(NULL == pstMmlEmerNumList)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_PrintEmergencyList: NULL Input!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PrintEmergencyList_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* ��ӡMCC��Ϣ */
    ulMcc = pstMmlEmerNumList->ulMcc;
    ucMccDigit = ulMcc & NAS_EMM_FIRST_BYTE_F;
    NAS_LMM_PUBM_LOG1_NORM("MCC DIGIT1: ",ucMccDigit);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PrintEmergencyList_ENUM,LNAS_FUNCTION_LABEL1,ucMccDigit);

    ucMccDigit = (ulMcc & NAS_EMM_SECOND_BYTE_F) >> NAS_EMM_MOVEMENT_8_BITS;
    NAS_LMM_PUBM_LOG1_NORM("MCC DIGIT2: ",ucMccDigit);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PrintEmergencyList_ENUM,LNAS_FUNCTION_LABEL2,ucMccDigit);

    ucMccDigit = (ulMcc & NAS_EMM_THIRD_BYTE_F) >> NAS_EMM_MOVEMENT_16_BITS;
    NAS_LMM_PUBM_LOG1_NORM("MCC DIGIT3: ",ucMccDigit);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PrintEmergencyList_ENUM,LNAS_FUNCTION_LABEL3,ucMccDigit);

    /* ��ӡ�����������б� */
    NAS_LMM_PUBM_LOG1_NORM("EMERGENCY NUM LIST AMOUT: ",pstMmlEmerNumList->ucEmergencyNumber);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PrintEmergencyList_ENUM,LNAS_FUNCTION_LABEL4,pstMmlEmerNumList->ucEmergencyNumber);

    for (ulLoop = NAS_EMM_NULL; ulLoop < pstMmlEmerNumList->ucEmergencyNumber; ulLoop++)
    {
        pstMmlEmerNum = &pstMmlEmerNumList->aucEmergencyList[ulLoop];

        NAS_LMM_PUBM_LOG1_NORM("EMER NUM INFO",ulLoop);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PrintEmergencyList_ENUM,LNAS_FUNCTION_LABEL5,ulLoop);

        NAS_LMM_PUBM_LOG1_NORM("EMER NUM CATOGORY: ",pstMmlEmerNum->ucCategory);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_PrintEmergencyList_ENUM,LNAS_FUNCTION_LABEL6,pstMmlEmerNum->ucCategory);

        for (ulLoop2 = NAS_EMM_NULL; ulLoop2 < pstMmlEmerNum->ucEmcNumLen; ulLoop2++)
        {
            NAS_LMM_PUBM_LOG1_NORM("EMER NUM : ",pstMmlEmerNum->aucEmcNum[ulLoop2]);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_PrintEmergencyList_ENUM,LNAS_FUNCTION_LABEL7,pstMmlEmerNum->aucEmcNum[ulLoop2]);
        }
    }
}
/*PC REPLAY MODIFY BY LEILI BEGIN*/

NAS_MML_EMERGENCY_NUM_LIST_STRU*  NAS_EMM_GetEmergencyListFromMml( VOS_VOID )
{
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstMmlEmerNumList = VOS_NULL_PTR;
    #ifndef __PS_WIN32_RECUR__
    pstMmlEmerNumList = NAS_MML_GetEmergencyNumList();

    /* ��ӡ��MML��ȡ�Ľ����������б���Ϣ */
    NAS_EMM_PrintEmergencyList(pstMmlEmerNumList);

    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
    NAS_LMM_LogEmergencyNumListInfo(pstMmlEmerNumList,WUEPS_PID_MMC,PS_PID_MM);
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */

    #else
    pstMmlEmerNumList = Stub_NAS_MML_GetEmergencyNumList();
    #endif
    return pstMmlEmerNumList;
}
/*PC REPLAY MODIFY BY LEILI END*/

VOS_VOID  NAS_EMM_SetEmergencyList2Mml
(
    const NAS_MM_PLMN_ID_STRU             *pstCurPlmnId,
    const NAS_LMM_EMERGENCY_NUM_LIST_STRU *pstEmerNumList
)
{
    VOS_UINT32                          ulMcc           = NAS_EMM_NULL;
    NAS_MML_EMERGENCY_NUM_LIST_STRU     stMmlEmerNumList= {NAS_EMM_NULL};

    /* ȡ����ǰPLMN�е�MCC����ת��ΪMML��MCC�ĸ�ʽ */
    ulMcc = NAS_EMM_GetMmlFormatMcc(pstCurPlmnId);

    stMmlEmerNumList.ulMcc              = ulMcc;
    stMmlEmerNumList.ucEmergencyNumber  = pstEmerNumList->ucEmergencyNumAmount;
    NAS_LMM_MEM_CPY(    stMmlEmerNumList.aucEmergencyList,
                        pstEmerNumList->astEmergencyNumList,
                        sizeof(LMM_MM_EMERGENCY_NUM_STRU) * NAS_MML_EMERGENCY_NUM_LIST_MAX_RECORDS);

    /* ��ӡд��MML�Ľ������б���Ϣ */
    NAS_EMM_PrintEmergencyList(&stMmlEmerNumList);

    NAS_MML_SetEmergencyNumList(&stMmlEmerNumList);

    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
    NAS_LMM_LogEmergencyNumListInfo(&stMmlEmerNumList,PS_PID_MM,PS_PID_MM);
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
}


VOS_VOID NAS_EMM_ClearEmergencyList( VOS_VOID )
{
    NAS_LMM_EMERGENCY_NUM_LIST_STRU      stEmerNumListTmp   = {NAS_EMM_NULL};

    /* ���MML�еĽ����������б� */
    NAS_EMM_SetEmergencyList2Mml(   NAS_LMM_GetEmmInfoPresentPlmnAddr(),
                                    &stEmerNumListTmp);
}

/* lihong00150010 csfb end */


VOS_VOID  NAS_EMM_SetEmergencyList
(
    VOS_UINT32                             ulOpEmerList,
    const NAS_LMM_EMERGENCY_NUM_LIST_STRU *pstEmerNumList
)
{
    NAS_LMM_PUB_INFO_STRU               *pstPubInfo = VOS_NULL_PTR;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    if (NAS_EMM_NULL_PTR == pstEmerNumList)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_SetEmergencyList: Point is null");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SetEmergencyList_ENUM,LNAS_NULL_PTR);

        return;
    }
/* lihong00150010 csfb begin */

    if (NAS_EMM_BIT_SLCT == ulOpEmerList)
    {
        /* �������������б����õ�MML */
        NAS_EMM_SetEmergencyList2Mml(   &pstPubInfo->stNetInfo.stPresentNetId.stPlmnId,
                                        pstEmerNumList);
        return ;
    }

    /* ����տ�û��Я�������������б���Ƚϵ�ǰPLMN�е�MCC�Ƿ����������������
       �����ý����������б����Ϊ0 */
    /* The emergency number(s) received in the Emergency Number List IE are valid only in networks
        in the same country as the cell on which this IE is received.    */
    if ((NAS_RELEASE_R11 && (VOS_TRUE == NAS_EMM_IsCountryChanged()))
          || (VOS_TRUE == NAS_EMM_IsMccChanged()))
    {
        NAS_EMM_ClearEmergencyList();
        return ;
    }
/* lihong00150010 csfb end */
}
VOS_VOID  NAS_EMM_SetEpsNetFeature
(
    VOS_UINT32                          ulOpNetFeature,
    VOS_UINT8                           ucNetFeature
)
{
    NAS_LMM_PUB_INFO_STRU               *pstPubInfo = VOS_NULL_PTR;

    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_SetEpsNetFeature is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SetEpsNetFeature_ENUM,LNAS_ENTRY);

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    if (NAS_EMM_BIT_SLCT == ulOpNetFeature)
    {
        pstPubInfo->bitOpNetFeature         = NAS_EMM_BIT_SLCT;
        pstPubInfo->ucNetFeature            = ucNetFeature;
    }
    else
    {
        pstPubInfo->bitOpNetFeature         = NAS_EMM_BIT_NO_SLCT;
        pstPubInfo->ucNetFeature            = NAS_EMM_NULL;
    }

    return;
}
/* lihong00150010 ims begin */
/*leili modify for isr begin*/

VOS_VOID  NAS_EMM_SetAddUpdateRslt
(
    VOS_UINT32                                  ulOpAddUpdateRslt,
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAddUpdateRslt
)
{
    NAS_LMM_PUB_INFO_STRU              *pstEmmInfo = VOS_NULL_PTR;

    pstEmmInfo = NAS_LMM_GetEmmInfoAddr();

    /* ATTACH ACP����TAU ACCEPTЯ��Additional update result,����Additional update
       result��ȫ�ֱ����� */
    if (NAS_EMM_BIT_SLCT == ulOpAddUpdateRslt)
    {
        NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_SetAddUpdateRslt:enAddUpdateRslt = ,",
                               enAddUpdateRslt);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_SetAddUpdateRslt_ENUM,LNAS_EMM_ADD_UPDATE_RST,
                               enAddUpdateRslt);

        pstEmmInfo->enAdditionUpRslt = enAddUpdateRslt;
        /*NAS_MML_SetAdditionUpdateRslt((VOS_UINT8)enAddUpdateRslt);*/
        return ;
    }

    /* ���UE������֧��CSFB��ֻ֧��SMS ONLY����ʹATTACH ACCPET��û��Я��
       Additional update result��Ԫ��ҲҪ��EMM INFOȫ�ֱ����е�Additional update
       resultֵ��ΪSMS ONLY */
    if (NAS_LMM_CS_SERVICE_SMS_ONLY == NAS_EMM_GetCsService())
    {
        NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_SetAddUpdateRslt:enAddUpdateRslt = ,",
                               NAS_MML_ADDITION_UPDATE_RSLT_SMS_ONLY);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_SetAddUpdateRslt_ENUM,LNAS_FUNCTION_LABEL1,
                               NAS_MML_ADDITION_UPDATE_RSLT_SMS_ONLY);

        pstEmmInfo->enAdditionUpRslt = NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY;
        /*NAS_MML_SetAdditionUpdateRslt(NAS_MML_ADDITION_UPDATE_RSLT_SMS_ONLY);*/
    }
    else
    {
        NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_SetAddUpdateRslt:enAddUpdateRslt = ,",
                               NAS_MML_ADDITION_UPDATE_RSLT_BUTT);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_SetAddUpdateRslt_ENUM,LNAS_FUNCTION_LABEL2,
                               NAS_MML_ADDITION_UPDATE_RSLT_BUTT);

        pstEmmInfo->enAdditionUpRslt = NAS_LMM_ADDITIONAL_UPDATE_BUTT;
        /*NAS_MML_SetAdditionUpdateRslt(NAS_MML_ADDITION_UPDATE_RSLT_BUTT);*/
    }

    return;
}

NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  NAS_EMM_GetAddUpdateRslt
(
   VOS_VOID
)
{
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAddUpdateRslt;
    NAS_LMM_PUB_INFO_STRU                      *pstEmmInfo = VOS_NULL_PTR;

    pstEmmInfo = NAS_LMM_GetEmmInfoAddr();

    /*enAddUpdateRslt = NAS_MML_GetAdditionUpdateRslt();*/
    enAddUpdateRslt = pstEmmInfo->enAdditionUpRslt;

    NAS_LMM_PUBM_LOG1_NORM("NAS_EMM_GetAddUpdateRslt:enAddUpdateRslt = ",
                            enAddUpdateRslt);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_GetAddUpdateRslt_ENUM,LNAS_EMM_ADD_UPDATE_RST,
                            enAddUpdateRslt);

    NAS_LMM_LogAdditionUpdateRsltInfo(enAddUpdateRslt);
    return enAddUpdateRslt;
}

/* leili moidfy for isr end */
/* lihong00150010 ims end */

VOS_VOID NAS_EMM_GetCurrentTa( NAS_MM_TA_STRU *pstTa )
{
    NAS_EMM_NETWORK_ID_STRU             *pstAreaInfo;

    pstAreaInfo                         = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr();

    NAS_LMM_PlmnCpy(&(pstTa->stPlmnId), &pstAreaInfo->stPlmnId);

    pstTa->stTac.ucTac                  = pstAreaInfo->stTac.ucTac;

    pstTa->stTac.ucTacCnt               = pstAreaInfo->stTac.ucTacCnt;

    return;
}

VOS_VOID NAS_EMM_AddForbTa
(
    const NAS_MM_TA_STRU               *pstTa,
    NAS_MM_TA_LIST_STRU                *pstTaList
)
{
    NAS_LMM_PUBM_LOG_NORM("NAS_EMMC_AddForbTa is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_AddForbTa_ENUM,LNAS_ENTRY);

    NAS_LMM_AddTaInTaList(pstTa, pstTaList, NAS_LMM_MAX_FORBTA_NUM);
    /* DEL FORB TA PROID��ʱ��δ����ʱ������ʱ��,��ֹ����AС������TA�����б�,��ʱ���쳬ʱʱ,
        BС����������TA�����б�����������ʱ��,���³���AС����ʱ���޷������ */
    if(NAS_LMM_TIMER_RUNNING != NAS_LMM_IsStaTimerRunning(TI_NAS_EMM_STATE_DEL_FORB_TA_PROID))
    {
        NAS_LMM_StartStateTimer(TI_NAS_EMM_STATE_DEL_FORB_TA_PROID);
    }
    return;
}


VOS_UINT32 NAS_EMM_IsNeedAddForbTa
(
    VOS_VOID
)
{
    NAS_LMM_PUBM_LOG_NORM("NAS_EMM_IsNeedAddForbTa is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsNeedAddForbTa_ENUM,LNAS_ENTRY);

    if ((VOS_TRUE == NAS_EMMC_GetShareNetFlag()) &&
         (NAS_EMM_CONN_DATA == NAS_EMM_TAU_GetEmmTauStartConnSta()))
    {
        return NAS_EMM_NO;
    }
    return NAS_EMM_YES;
}


VOS_UINT32  NAS_LMM_IsLastAttemptRegTaInTaiList(VOS_VOID)
{
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa = NAS_EMM_NULL_PTR;
    NAS_LMM_NETWORK_INFO_STRU          *pstNetInfo        = NAS_EMM_NULL_PTR;

    pstNetInfo                         = NAS_LMM_GetEmmInfoNetInfoAddr();
    pstLastAttmpRegTa                  = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

    if (NAS_EMM_BIT_NO_SLCT == pstNetInfo->bitOpLastAttmpRegTa)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_IsLastAttemptRegTaInTaiList: Not exist last attempt TA.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_IsLastAttemptRegTaInTaiList_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_NO;
    }

    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTaList(pstLastAttmpRegTa, NAS_LMM_GetEmmInfoNetInfoTaiListAddr()))
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_IsLastAttemptRegTaInTaiList: Last attempt TA is in TAI LIST.");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_IsLastAttemptRegTaInTaiList_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_YES;
    }
    else
    {
        return NAS_EMM_NO;
    }

}


VOS_UINT8  NAS_EMM_GetImsiHplmn
(
    VOS_UINT8             *pucImsi,
    NAS_MM_PLMN_ID_STRU   *pstHplmn
)
{
    NAS_MM_PLMN_ID_STRU       stHplmn;
    VOS_UINT32               *pulImsiMncLen;

    /* ��ȡUSIM��ָʾ��MNC�ĳ��� */
    pulImsiMncLen = NAS_LMM_GetEmmInfoUeidImsiMncLenAddr();

    NAS_LMM_MEM_SET(&stHplmn, 0, sizeof(NAS_MM_PLMN_ID_STRU));

    /* ��IMSIת����LMMʹ�õĸ�ʽ */

    /* ����IMSI��0�ֽ�(����)�͵�1�ֽڵĵ�4bit(У��λ)��������pucImsi[0]��pucImsi[1]�ĵ�4bit*/

    /* ��ȡMCC */
    /* ��1�ֽڵĸ�4bitΪMCC��1λ��������HPLMN��0���ֽڵĵ�4λ */
    stHplmn.aucPlmnId[0] |= ((pucImsi[1] & NAS_EMM_HIGH_HALF_BYTE_F) >> NAS_EMM_MOVEMENT_4_BYTE);

    /* ��2�ֽڵĵ�4bitΪMCC��2λ��������HPLMN��0���ֽڵĸ�4λ */
    stHplmn.aucPlmnId[0] |= ((pucImsi[2] & NAS_EMM_LOW_HALF_BYTE_F) << NAS_EMM_MOVEMENT_4_BYTE);

    /* ��2�ֽڵĸ�4bitΪMCC��3λ��������HPLMN��1���ֽڵĵ�4λ */
    stHplmn.aucPlmnId[1] |= ((pucImsi[2] & NAS_EMM_HIGH_HALF_BYTE_F) >> NAS_EMM_MOVEMENT_4_BYTE);

    /* ��ȡMNC */
    /* ��3�ֽڵĵ�4bitΪMNC��1λ��������HPLMN��2���ֽڵĵ�4λ */
    stHplmn.aucPlmnId[2] |= (pucImsi[3] & NAS_EMM_LOW_HALF_BYTE_F);

    /* ��3�ֽڵĸ�4bitΪMNC��2λ��������HPLMN��2���ֽڵĸ�4λ */
    stHplmn.aucPlmnId[2] |= (pucImsi[3] & NAS_EMM_HIGH_HALF_BYTE_F);

    /* ���MNC����Ϊ2����MNC��3λ����ΪF��Ҳ����HPLMN�ĵ�1�ֽڵĸ�4bit�������������MNC��3λ */
    if(NAS_LMM_NVIM_MNCLEN_VALUE_2 == (*pulImsiMncLen))
    {
        stHplmn.aucPlmnId[1] |= 0xF0;
    }
    else
    {
        stHplmn.aucPlmnId[1] |= ((pucImsi[4] & NAS_EMM_LOW_HALF_BYTE_F) << NAS_EMM_MOVEMENT_4_BYTE);
    }

    NAS_LMM_MEM_CPY(pstHplmn, &stHplmn, sizeof(NAS_MM_PLMN_ID_STRU));

    return NAS_EMM_SUCC;
}
VOS_UINT8  NAS_EMM_IsDamUsimCard(VOS_VOID)
{
    VOS_UINT8                *pucImsi;
    NAS_MM_PLMN_ID_STRU       stHplmn;
    VOS_UINT32                ulIndex;
    NAS_DAM_IMSI_PLMN_LIST   *pstDamImsiPlmnList;

    PS_MEM_SET(&stHplmn, 0x00, sizeof(NAS_MM_PLMN_ID_STRU));
    pucImsi            = (VOS_UINT8*)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PARA_IMSI);
    pstDamImsiPlmnList = NAS_EMM_GetEmmInfoDamParaImsiPlmnListAddr();

    /* Լ����NV�й���IMSI��PLMN�ж����ֻ����1��PLMN��ȫΪ0XFF����Ĭ�϶����п����
             �����жϣ��������Ƿ�פ����DAM PLMN����ȷ���Ƿ�����DAM,�ڴ˳����£�ֱ
             �ӷ�����DAM������������ֻ�ж�פ��PLMN����                             */
    if((1 == pstDamImsiPlmnList->ulPlmnNum)
        &&(NAS_LMM_BYTE_FF == pstDamImsiPlmnList->astPlmnId[0].aucPlmnId[0])
        &&(NAS_LMM_BYTE_FF == pstDamImsiPlmnList->astPlmnId[0].aucPlmnId[1])
        &&(NAS_LMM_BYTE_FF == pstDamImsiPlmnList->astPlmnId[0].aucPlmnId[2]))
    {
        return NAS_EMM_YES;
    }

    /* ��Ҫ�жϿ� */
    /* ��ȡHPLMN��Ȼ���IMSI PLMN�б���бȶԣ���ȡʧ��ֱ�ӷ��ز���DAM�� */
    if(NAS_EMM_SUCC == NAS_EMM_GetImsiHplmn(pucImsi, &stHplmn))
    {
        for(ulIndex = 0; ulIndex < pstDamImsiPlmnList->ulPlmnNum; ulIndex++)
        {
            if(NAS_LMM_MATCH_SUCCESS == NAS_LMM_PlmnMatch(&(stHplmn),
                (NAS_MM_PLMN_ID_STRU*)&(pstDamImsiPlmnList->astPlmnId[ulIndex])))
            {
                NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsCampOnATTPlmn: DAM Card.");
                TLPS_PRINT2LAYER_INFO(NAS_EMM_IsDamUsimCard_ENUM,LNAS_EMM_JUDGE_FLAG);
                return NAS_EMM_YES;
            }
        }
    }

   return NAS_EMM_NO;

}


VOS_UINT8  NAS_EMM_IsTmoUsimCard(VOS_VOID)
{
    NAS_LMM_PUBM_LOG1_INFO("NAS_EMM_IsTmoUsimCard: TmoUsimCardFlag is ", NAS_EMM_GetEmmInfoTmoUsimCardFlag());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_IsTmoUsimCard_ENUM,LNAS_EMM_JUDGE_FLAG,NAS_EMM_GetEmmInfoTmoUsimCardFlag());

    if(VOS_TRUE == NAS_EMM_GetEmmInfoTmoUsimCardFlag())
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;

}


VOS_UINT8  NAS_EMM_IsPtmsiTauActiveFlagSatified(VOS_VOID)
{
    /* ���NV��򿪣��Ҳ�Ϊ���Կ�����TINΪP-TMSI�����������㣬�������������� */
    if ((PS_TRUE == g_ulPtmsiTauActiveFlag)
        && (PS_SUCC != LPS_OM_IsTestMode())
        && (MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType()))
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}
VOS_UINT8  NAS_EMM_IsCampOnDamPlmn(VOS_VOID)
{
    VOS_UINT32                          ulIndex;
    NAS_MM_NETWORK_ID_STRU             *pstAreaInfo;
    NAS_MM_DAM_PLMN_LIST_STRU          *pstDamPlmnList;

    pstDamPlmnList = NAS_EMM_GetEmmInfoDamParaPlmnListAddr();
    pstAreaInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);

    /* Լ����NV�й���פ����PLMN�ж����ֻ����1��PLMN��ȫΪ0XFF����Ĭ�϶�פ����PLMN
             �����жϣ��������Ƿ���DAM����ȷ���Ƿ�����DAM,�ڴ˳����£�ֱ
             �ӷ���פ����DAM��PLMN�ϣ���������ֻ�жϿ����ͼ���                    */
    if((1 == pstDamPlmnList->ulPlmnNum)
        &&(NAS_LMM_BYTE_FF == pstDamPlmnList->astPlmnId[0].aucPlmnId[0])
        &&(NAS_LMM_BYTE_FF == pstDamPlmnList->astPlmnId[0].aucPlmnId[1])
        &&(NAS_LMM_BYTE_FF == pstDamPlmnList->astPlmnId[0].aucPlmnId[2]))
    {
        return NAS_EMM_YES;
    }

    for(ulIndex = 0; ulIndex < pstDamPlmnList->ulPlmnNum; ulIndex++)
    {
        if(NAS_LMM_MATCH_SUCCESS == NAS_LMM_PlmnMatch(&(pstAreaInfo->stPlmnId),
            (NAS_MM_PLMN_ID_STRU*)&(pstDamPlmnList->astPlmnId[ulIndex])))
        {
            NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsCampOnATTPlmn: Camp on DAM PLMN.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_IsCampOnDamPlmn_ENUM,LNAS_EMM_JUDGE_FLAG);
            return NAS_EMM_YES;
        }
    }

    return NAS_EMM_NO;

}


VOS_UINT8  NAS_EMM_IsDamConfitionSatisfied(VOS_VOID)
{
    if((NAS_EMM_YES == NAS_EMM_IsDamUsimCard())
        &&(NAS_EMM_YES== NAS_EMM_IsCampOnDamPlmn()))
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}


VOS_VOID  NAS_EMM_SendMMCT3402LenNotify(VOS_UINT32 ulT3402Len)
{
    LMM_MMC_T3402_LEN_NOTIFY_STRU           *pstT3402LenMsg;

    /* ����MMC�ڲ���Ϣ */
    pstT3402LenMsg = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_T3402_LEN_NOTIFY_STRU));

    if (NAS_LMM_NULL_PTR == pstT3402LenMsg)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_SendMMCT3402LenNotify: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SendMMCT3402LenNotify_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstT3402LenMsg,0,sizeof(LMM_MMC_T3402_LEN_NOTIFY_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstT3402LenMsg),NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_T3402_LEN_NOTIFY_STRU));

    /* �����ϢID */
    pstT3402LenMsg->ulMsgId             = ID_LMM_MMC_T3402_LEN_NOTIFY;

    /* �����Ϣ�� */
    pstT3402LenMsg->ulOpId              = NAS_EMM_OPID_MMC;

    pstT3402LenMsg->ulT3402Len          = ulT3402Len;

    NAS_EMM_PUBU_LOG1_WARN("NAS_EMM_SendMMCT3402LenNotify: ulT3402Len=",ulT3402Len);
    TLPS_PRINT2LAYER_WARNING1(NAS_EMM_SendMMCT3402LenNotify_ENUM,LNAS_EMM_T3402_LEN,ulT3402Len);

    /* ����MMC�ڲ���Ϣ */
    NAS_LMM_SendLmmMmcMsg(pstT3402LenMsg);

    return;
}
VOS_UINT32  NAS_EMM_IsRegStatusEmcRegingOrContainEmcBear(VOS_VOID)
{
    /* ���ڽ���ע������� */
    if(NAS_LMM_REG_STATUS_EMC_REGING == NAS_LMM_GetEmmInfoRegStatus())
    {
        return NAS_EMM_YES;
    }

    /* �����Ѿ�����ע���������ע���н������� */
    if ((NAS_LMM_REG_STATUS_EMC_REGED == NAS_LMM_GetEmmInfoRegStatus())
        ||(NAS_LMM_REG_STATUS_NORM_REGED_AND_EMC_BEAR == NAS_LMM_GetEmmInfoRegStatus()))
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;

}



VOS_VOID NAS_EMM_ClearGuti(VOS_VOID)
{
    NAS_LMM_GetEmmInfoUeidAddr()->bitOpGuti      = NAS_EMM_BIT_NO_SLCT;
    NAS_LMM_MEM_SET(                               NAS_LMM_GetEmmInfoUeidGutiAddr(),
                                                  0,
                                                  sizeof(NAS_EMM_GUTI_STRU));
    return;
}


VOS_VOID NAS_EMM_ClearRegInfo(VOS_UINT32 ulDeleteRplmn )
{
    /*ɾ��GUTI*/
    NAS_EMM_ClearGuti();

    /*ɾ��LVR TAI*/

    if (NAS_EMM_DELETE_RPLMN == ulDeleteRplmn)
    {
        NAS_EMM_ClearLVRTai();
    }
    else
    {
        NAS_EMM_SetLVRTacInvalid();
    }
    /*ɾ��TAI list*/
    NAS_EMM_ClearTaiList();

    /*ɾ��KSIasme*/
    /*NAS_EMM_ClearCurSecuCntxt();*/
    NAS_EMM_ClearAllSecuCntxt();

    /* ����Ч�İ�ȫ������ֱ���ں����ڲ�д�� */
    NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_UPDATE);

    /*����PS LOC��Ϣ*/
    NAS_LMM_WritePsLoc(NAS_NV_ITEM_UPDATE);
}
VOS_VOID NAS_EMM_ClearResumeInfo( VOS_VOID )
{
    NAS_EMM_FSM_STATE_STRU             *pstStateBeforeResume;

    NAS_LMM_PUBM_LOG_NORM( "NAS_EMM_ClearResumeInfoOriTypeDir: ResumeInfo  is  cleared!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ClearResumeInfo_ENUM,LNAS_ENTRY);

    pstStateBeforeResume = NAS_EMM_GetStateBeforeResumeAddr();

    pstStateBeforeResume->enMainState   = NAS_LMM_MAIN_STATE_BUTT;
    pstStateBeforeResume->enSubState    = MM_SS_BUTT;
    pstStateBeforeResume->enStaTId      = TI_NAS_EMM_STATE_NO_TIMER;

    NAS_EMM_SetResumeOri(NAS_LMM_SYS_CHNG_ORI_BUTT);
    NAS_EMM_SetResumeType(NAS_LMM_SYS_CHNG_TYPE_BUTT);
    NAS_EMM_SetResumeDir(LRRC_LMM_RSM_SYS_CHNG_DIR_BUTT);

    return;

}


VOS_VOID NAS_LMM_ClearEmmInfoMmcAttachReason( VOS_VOID )
{
    NAS_LMM_PUBM_LOG_NORM( "NAS_LMM_ClearEmmInfoMmcAttachReason is  enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ClearEmmInfoMmcAttachReason_ENUM,LNAS_ENTRY);
    NAS_LMM_SetEmmInfoMmcAttachReason(MMC_LMM_ATT_REASON_INITIAL);
    return;

}



VOS_VOID  NAS_EMM_LocalDetachProc( VOS_VOID )
{
    /* �رյ�ǰEMM�ĳ�Del Forb Ta Proid֮���״̬��ʱ��, Del Forb Ta Proidֻ���ڹػ�ʱֹͣ*/
    NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer();

    /* ֹͣ����Э�鶨ʱ�� */
    NAS_LMM_StopAllPtlTimer();

    /* �ͷſ��ܴ��ڵĶ�̬�ڴ� */
    NAS_LMM_FreeDynMem();

    /* ֪ͨESM�����Դ */
    NAS_EMM_PLMN_SendEmmEsmStautsInd(   EMM_ESM_ATTACH_STATUS_DETACHED);

    /*���bar���̺�����*/
    NAS_EMM_ClearBarResouce();

    /*֪ͨ RABM:RRC_CONN_REL_IND*/
    NAS_LMM_SendRabmRrcConRelInd(EMM_ERABM_REL_CAUSE_NULL);
}


VOS_UINT32  NAS_EMM_TransferUeSpecDrxCycleLen( VOS_VOID )
{
    VOS_UINT32                  ulUeSpecDrxCycle = 0;
    VOS_UINT8                   ucUeEutranPsDrxLen = 0;
    /*NAS_MM_DRX_STRU            *pstUeDrxParam = VOS_NULL_PTR;*/

    /*��ȡUEָ����DRX����*/
    /*pstUeDrxParam = NAS_LMM_GetEmmInfoDrxAddr();*/
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /*����24008-930 10.5.5.6Э����������ת��*/
    switch(NAS_EMM_GetUeEutranPsDrxLen())
    {
        case NAS_LMM_DEC_DIGIT_0:
            ulUeSpecDrxCycle = 0;
            break;

        case NAS_LMM_DEC_DIGIT_6:
            ulUeSpecDrxCycle = 32;
            break;

        case NAS_LMM_DEC_DIGIT_7:
            ulUeSpecDrxCycle = 64;
            break;

        case NAS_LMM_DEC_DIGIT_8:
            ulUeSpecDrxCycle = 128;
            break;
        case NAS_LMM_DEC_DIGIT_9:
            ulUeSpecDrxCycle = 256;
            break;

             /*����ֵ������,ת��Ϊ0*/
        default:
            ucUeEutranPsDrxLen = NAS_MML_GetUeEutranPsDrxLen();
            NAS_EMM_PUBU_LOG1_WARN("NAS_EMM_TransferUeSpecDrxCycleLen:Drx Err.",
                                        ucUeEutranPsDrxLen);
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_TransferUeSpecDrxCycleLen_ENUM,LNAS_ERROR);
            ulUeSpecDrxCycle = 0;
            break;
    }

     /*PC REPLAY MODIFY BY LEILI END*/
    return ulUeSpecDrxCycle;
}
VOS_VOID  NAS_EMM_SendUeSpecDrxCycleLenToRrc( VOS_VOID )
{
    LRRC_LNAS_INFO_STRU                   stNasInfo;
    VOS_UINT32                          ulUeSpecDrxCycle;

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_SendUeSpecDrxCycleLenToRrc entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendUeSpecDrxCycleLenToRrc_ENUM,LNAS_ENTRY);

    /*����ڴ�*/
    NAS_LMM_MEM_SET(&stNasInfo, 0, sizeof(LRRC_LNAS_INFO_STRU));

    /*��ȡȫ�ֱ����е�DRX Param,������Э��ת��Ϊ UeSpecDrxCycle*/
    ulUeSpecDrxCycle = NAS_EMM_TransferUeSpecDrxCycleLen();

    /*���UEָ���� DRX_Cycle_Len*/
    stNasInfo.bitOpDrxLength            = NAS_EMM_BIT_SLCT;
    stNasInfo.ulDrxLength               = ulUeSpecDrxCycle;

    /*����RRC_MM_INFO_CHANGE_REQ��Ϣ��RRC*/
    NAS_EMM_SendInfoChangeReqMsg(&stNasInfo);

    return;

}


VOS_VOID  NAS_EMM_SendInfoChangeReqMsg( CONST LRRC_LNAS_INFO_STRU *pstNasInfo )
{
    LRRC_LMM_NAS_INFO_CHANGE_REQ_STRU    *pstInfoChgReqMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    /*���㳤�Ȳ�����VOS��Ϣͷ*/
    ulMsgLen     = NAS_EMM_MSG_ID_LEN + sizeof(LRRC_LNAS_INFO_STRU);

    /*�����ڴ�*/
    pstInfoChgReqMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(ulMsgLen + NAS_EMM_LEN_VOS_MSG_HEADER);
    if(NAS_EMM_NULL_PTR == pstInfoChgReqMsg)
    {
        return;
    }

    /*������뵽����Ϣ�ռ�*/
    PS_MEM_SET(pstInfoChgReqMsg,0,sizeof(LRRC_LMM_NAS_INFO_CHANGE_REQ_STRU));

    /*���VOS��Ϣͷ*/
    NAS_EMM_SET_RRC_MSG_HEADER(pstInfoChgReqMsg, ulMsgLen);

    /*�����ϢID*/
    pstInfoChgReqMsg->enMsgId           = ID_LRRC_LMM_NAS_INFO_CHANGE_REQ;

    /*�����Ϣ�� */
    NAS_LMM_MEM_CPY(                    &(pstInfoChgReqMsg->stNasInfo),
                                        pstNasInfo,
                                        sizeof(LRRC_LNAS_INFO_STRU));

    /* ����RRC_MM_NAS_INFO_CHANGE_REQ */
    NAS_LMM_SEND_MSG(pstInfoChgReqMsg);

    return;
}
VOS_VOID    NAS_EMM_PUBU_ClearResource(VOS_VOID)
{
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PUBU_ClearResource: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PUBU_ClearResource_ENUM,LNAS_ENTRY);

    /* ���ESM�ĳ���״̬ */
    NAS_EMM_PubmInfoBearerContextInit();

    /* ��������APP������Ϣ�Ĳ��� */
    /*NAS_EMM_ClearAppMsgPara();*/

    /* ������һ��������CN��Ϣ������ */
    NAS_LMM_GetLastAirMsgType() = EMM_MSG_TYPE_INVALID;

    return;
}



VOS_VOID    NAS_EMM_PUBU_SuspendClearResource(VOS_VOID)
{
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PUBU_SuspendClearResource: enter.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PUBU_SuspendClearResource_ENUM,LNAS_ENTRY);

    /* ���ESM�ĳ���״̬ */
    /*NAS_EMM_PubmInfoBearerContextInit();*/

    /* ��������APP������Ϣ�Ĳ��� */
    /*NAS_EMM_ClearAppMsgPara();*/

    /* ������һ��������CN��Ϣ������ */
    NAS_LMM_GetLastAirMsgType() = EMM_MSG_TYPE_INVALID;

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_SetUsimState
 Description     : ���ÿ�״̬
 Input           : NAS_LMM_SIM_STAT_ENUM_UINT32 ulUsimStatus
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.HanLufeng 41410      2011-3-3  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_EMM_SetUsimState( NAS_LMM_SIM_STAT_ENUM_UINT32 ulUsimStatus )
{
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_SetUsimState: set ulUsimStatus = ", ulUsimStatus);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_SetUsimState_ENUM,LNAS_EMM_USIM_STATE,ulUsimStatus);

    if( (NAS_LMM_SIM_STATUS_UNAVAILABLE != ulUsimStatus) &&
        (NAS_LMM_SIM_STATUS_AVAILABLE != ulUsimStatus))
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SetUsimState: Input Para err ! ");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SetUsimState_ENUM,LNAS_PARAM_INVALID);
        return;
    }
    else
    {
        NAS_LMM_GetSimState() = ulUsimStatus;
        return;
    }
}


VOS_VOID NAS_EMM_LmmEmmInfo2MmcEmmInfo(const NAS_EMM_INFO_STRU *pstLmmEmmInfo, MMC_EMM_INFO_STRU *pstMmcEmmInfo)
{
    /* convert bit flag field */
    pstMmcEmmInfo->bitOpLocTimeZone        = pstLmmEmmInfo->bitOpLocTimeZone;
    pstMmcEmmInfo->bitOpUniTimeLocTimeZone = pstLmmEmmInfo->bitOpUniTimeLocTimeZone;
    pstMmcEmmInfo->bitOpDaylightTime       = pstLmmEmmInfo->bitOpDaylightTime;
    pstMmcEmmInfo->bitReserved             = pstLmmEmmInfo->bitShare;

    /* convert LTZ field */
    if (NAS_LMM_TIMEZONE_POSITIVE == pstLmmEmmInfo->stLocTimeZone.enPosNegTimeZone)
    {
        pstMmcEmmInfo->cLocTimeZone =  (VOS_INT8)(pstLmmEmmInfo->stLocTimeZone.ucTimeZone & 0x7F);
    }
    else
    {
        pstMmcEmmInfo->cLocTimeZone = -(VOS_INT8)(pstLmmEmmInfo->stLocTimeZone.ucTimeZone & 0x7F);
    }

    /* convert UT_LTZ field */
    pstMmcEmmInfo->stTimeZoneAndTime.ucYear   = pstLmmEmmInfo->stTimeZoneAndTime.ucYear;
    pstMmcEmmInfo->stTimeZoneAndTime.ucMonth  = pstLmmEmmInfo->stTimeZoneAndTime.ucMonth;
    pstMmcEmmInfo->stTimeZoneAndTime.ucDay    = pstLmmEmmInfo->stTimeZoneAndTime.ucDay;
    pstMmcEmmInfo->stTimeZoneAndTime.ucHour   = pstLmmEmmInfo->stTimeZoneAndTime.ucHour;
    pstMmcEmmInfo->stTimeZoneAndTime.ucMinute = pstLmmEmmInfo->stTimeZoneAndTime.ucMinute;
    pstMmcEmmInfo->stTimeZoneAndTime.ucSecond = pstLmmEmmInfo->stTimeZoneAndTime.ucSecond;
    if (NAS_LMM_TIMEZONE_POSITIVE == pstLmmEmmInfo->stTimeZoneAndTime.stTimeZone.enPosNegTimeZone)
    {
        pstMmcEmmInfo->stTimeZoneAndTime.cTimeZone =  (VOS_INT8)(pstLmmEmmInfo->stTimeZoneAndTime.stTimeZone.ucTimeZone & 0x7F);
    }
    else
    {
        pstMmcEmmInfo->stTimeZoneAndTime.cTimeZone = -(VOS_INT8)(pstLmmEmmInfo->stTimeZoneAndTime.stTimeZone.ucTimeZone & 0x7F);
    }
    /* convert DST field */
    switch(pstLmmEmmInfo->enDaylightSavingTime)
    {
    case NAS_LMM_DAYLIGHT_NO_ADJUST:
        pstMmcEmmInfo->enDaylightSavingTime = MMC_EMM_INFO_DST_NO_ADJUST;
        break;
    case NAS_LMM_DAYLIGHT_1_HOUR_ADJUST:
        pstMmcEmmInfo->enDaylightSavingTime = MMC_EMM_INFO_DST_1_HOUR_ADJUST;
        break;
    case NAS_LMM_DAYLIGHT_2_HOUR_ADJUST:
        pstMmcEmmInfo->enDaylightSavingTime = MMC_EMM_INFO_DST_2_HOUR_ADJUST;
        break;
    default:
        pstMmcEmmInfo->enDaylightSavingTime = MMC_EMM_INFO_DST_BUTT;
    }
}


VOS_VOID NAS_EMM_SendMmcEmmInfoInd(const NAS_EMM_INFO_STRU *pLmmEmmInfo)
{
    LMM_MMC_EMM_INFO_IND_STRU *pstMmcEmmInfoIndMsg = VOS_NULL_PTR;
    NAS_EMM_INFO_STRU                   *pstEmmInfo;


    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_SendMmcEmmInfoInd: enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendMmcEmmInfoInd_ENUM,LNAS_ENTRY);

    /* check input parameter */
    if (NAS_LMM_NULL_PTR == pLmmEmmInfo)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcEmmInfoInd: invalid input parameter");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcEmmInfoInd_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* alloc memory */
    pstMmcEmmInfoIndMsg = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_EMM_INFO_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcEmmInfoIndMsg)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcEmmInfoInd: MSG ALLOC ERROR");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcEmmInfoInd_ENUM,LNAS_ERROR);
        return;
    }

    /* initialization */
    NAS_LMM_MEM_SET(pstMmcEmmInfoIndMsg, 0, sizeof(LMM_MMC_EMM_INFO_IND_STRU));

    /* composite message header */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcEmmInfoIndMsg), NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_EMM_INFO_IND_STRU));

    /* assign message id */
    pstMmcEmmInfoIndMsg->ulMsgId = ID_LMM_MMC_EMM_INFO_IND;

    /* assign message context */
    NAS_EMM_LmmEmmInfo2MmcEmmInfo(pLmmEmmInfo, &pstMmcEmmInfoIndMsg->stLteEmmInfo);


    pstEmmInfo  = NAS_LMM_GetEmmInfoNasEmmInfoListAddr();

    if(NAS_EMM_BIT_SLCT == pstEmmInfo->bitOpFullName)
    {
        pstMmcEmmInfoIndMsg->stLteEmmInfo.bitOpLongName = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(pstMmcEmmInfoIndMsg->stLteEmmInfo.aucOperatorNameLong,
                        pLmmEmmInfo->aucOperatorNameLong,
                        MMC_LMM_MAX_OPER_LONG_NAME_LEN);
    }

    if(NAS_EMM_BIT_SLCT == pstEmmInfo->bitOpShortName)
    {
        pstMmcEmmInfoIndMsg->stLteEmmInfo.bitOpShortName = NAS_EMM_BIT_SLCT;
        NAS_LMM_MEM_CPY(pstMmcEmmInfoIndMsg->stLteEmmInfo.aucOperatorNameShort,
                        pLmmEmmInfo->aucOperatorNameShort,
                        MMC_LMM_MAX_OPER_SHORT_NAME_LEN);
    }

    /* send message to MMC */
    NAS_LMM_SendLmmMmcMsg(pstMmcEmmInfoIndMsg);
}
VOS_VOID    NAS_EMM_SendMmcStatusInd(
                                MMC_LMM_STATUS_TYPE_ENUM_UINT32 ulMmcLmmStaType,
                                MMC_LMM_CONN_STATE_ENUM_UINT32  ulConnState )
{
    LMM_MMC_STATUS_IND_STRU           *pstMmcStatusIndMsg = VOS_NULL_PTR;

    NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_SendMmcStatusInd: ulMmcLmmStaType = , ulConnState =",
                        ulMmcLmmStaType,
                        ulConnState);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_SendMmcStatusInd_ENUM,LNAS_FUNCTION_LABEL1,
                        ulMmcLmmStaType,
                        ulConnState);
    /* ����MMC�ڲ���Ϣ */
    pstMmcStatusIndMsg = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_STATUS_IND_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcStatusIndMsg)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcStatusInd: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcStatusInd_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstMmcStatusIndMsg, 0, sizeof(LMM_MMC_STATUS_IND_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcStatusIndMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_STATUS_IND_STRU));

    /* �����ϢID */
    pstMmcStatusIndMsg->ulMsgId         = ID_LMM_MMC_STATUS_IND;

    /* �����Ϣ�� */
    pstMmcStatusIndMsg->ulOpId          = NAS_EMM_OPID_MMC;
    pstMmcStatusIndMsg->ulStatusType    = ulMmcLmmStaType;

    /* ����ϱ�������ΪMMC_LMM_STATUS_TYPE_CONN_STATE�����������״̬*/
    if(MMC_LMM_STATUS_TYPE_CONN_STATE == ulMmcLmmStaType)
    {
        pstMmcStatusIndMsg->bitOpConnState  = NAS_EMM_BIT_SLCT;
        pstMmcStatusIndMsg->ulConnState     = ulConnState;
    }

    /* ����MMC�ڲ���Ϣ */
    NAS_LMM_SendLmmMmcMsg(pstMmcStatusIndMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SendMmcUsimStatusCnf
 Description     : ��MMC����LMM_MMC_USIM_STATUS_CNF��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-7-2  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SendMmcUsimStatusCnf( VOS_VOID )
{
    LMM_MMC_USIM_STATUS_CNF_STRU       *pstMmcUsimStatusCnf = VOS_NULL_PTR;

    /* ����MMC�ڲ���Ϣ*/
    pstMmcUsimStatusCnf = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_USIM_STATUS_CNF_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcUsimStatusCnf)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcUsimStatusCnf: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcUsimStatusCnf_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstMmcUsimStatusCnf, 0, sizeof(LMM_MMC_USIM_STATUS_CNF_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcUsimStatusCnf),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_USIM_STATUS_CNF_STRU));

    /* �����ϢID */
    pstMmcUsimStatusCnf->ulMsgId    = ID_LMM_MMC_USIM_STATUS_CNF;

    /* �����Ϣ�� */
    pstMmcUsimStatusCnf->ulOpId     = NAS_EMM_OPID_MMC;

    /* ����MMC�ڲ���Ϣ */
    NAS_LMM_SendLmmMmcMsg(pstMmcUsimStatusCnf);

    return;
}
VOS_UINT32  NAS_EMM_CheckSupportGUMode( VOS_VOID)
{
    if ( ((NAS_LMM_RAT_PRIO_NULL < NAS_LMM_GetCurGsmPrio())
       &&(NAS_LMM_RAT_PRIO_BUTT > NAS_LMM_GetCurGsmPrio()))
      ||((NAS_LMM_RAT_PRIO_NULL < NAS_LMM_GetCurWcdmaPrio())
       &&(NAS_LMM_RAT_PRIO_BUTT > NAS_LMM_GetCurWcdmaPrio())))
    {
        return NAS_LMM_SUCC;
    }
    return NAS_EMM_FAIL;
}



VOS_UINT32  NAS_EMM_CheckMutiModeSupport(VOS_VOID  )
{
    VOS_UINT32                          ulRslt = NAS_EMM_FAIL;

    if ( (NAS_LMM_RAT_PRIO_NULL == NAS_LMM_GetCurLtePrio ())
       ||(NAS_LMM_RAT_PRIO_BUTT == NAS_LMM_GetCurLtePrio ()))
    {
        ulRslt = NAS_LMM_FAIL;
    }
    else if( (NAS_LMM_RAT_PRIO_NULL < NAS_LMM_GetCurLtePrio ())
            &&(NAS_LMM_RAT_PRIO_BUTT > NAS_LMM_GetCurLtePrio ()))
    {
        ulRslt = NAS_EMM_CheckSupportGUMode();
    }
    else
    {
    }
    return ulRslt;

}


VOS_UINT32  NAS_EMM_CheckPtmsiAndRaiValidity( VOS_VOID )
{
    NAS_GUMM_INFO_STRU                  stGuInfo;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt1;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt2;
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /*�ж�P-TMSI �� RAI�Ƿ���Ч*/
    ulRslt1 = NAS_EMM_GetGuInfo(NAS_GUMM_PTMSI,&stGuInfo);

    ulRslt2 = NAS_EMM_GetGuInfo(NAS_GUMM_RAI,&stGuInfo);
    /*PC REPLAY MODIFY BY LEILI END*/

    if ((MMC_LMM_SUCC == ulRslt1) &&
        (MMC_LMM_SUCC == ulRslt2))
    {

        return NAS_EMM_SUCC;
    }

    return NAS_EMM_FAIL;

}
VOS_VOID  NAS_EMM_GetPtmsiAndRai
(
    NAS_GUMM_PTMSI_STRU     *pstPtmsi,
    MMC_LMM_RAI_STRU        *pstRai
)
{
    NAS_GUMM_INFO_STRU                  stGuInfo;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt1;
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt2;

    /*��ʼ��*/
    NAS_LMM_MEM_SET(&stGuInfo, 0, sizeof(NAS_GUMM_INFO_STRU));
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /*�ж�P-TMSI �� RAI�Ƿ���Ч*/
    ulRslt1 = NAS_EMM_GetGuInfo(NAS_GUMM_PTMSI,&stGuInfo);

    if (MMC_LMM_SUCC == ulRslt1)
    {
        NAS_LMM_MEM_CPY(                 pstPtmsi,
                                        &(stGuInfo.u.stPtmsi),
                                        sizeof(NAS_GUMM_PTMSI_STRU));
    }

    ulRslt2 = NAS_EMM_GetGuInfo(NAS_GUMM_RAI,&stGuInfo);

    if (MMC_LMM_SUCC == ulRslt2)
    {
        NAS_LMM_MEM_CPY(                 pstRai,
                                        &(stGuInfo.u.stRAI),
                                        sizeof(MMC_LMM_RAI_STRU));
    }
    /*PC REPLAY MODIFY BY LEILI END*/
    return;
}

VOS_VOID  NAS_EMM_DeriveMappedGuti
(
    NAS_LMM_GUTI_STRU                   *pstMappedGuti
)
{
    NAS_GUMM_PTMSI_STRU                 stPtmsi;
    MMC_LMM_RAI_STRU                    stRai;

    PS_MEM_SET(&stPtmsi, 0, sizeof(NAS_GUMM_PTMSI_STRU));
    PS_MEM_SET(&stRai, 0, sizeof(MMC_LMM_RAI_STRU));

    NAS_EMM_PUBU_LOG_NORM("NAS_EMM_DeriveMappedGuti entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_DeriveMappedGuti_ENUM,LNAS_ENTRY);

    if(VOS_NULL_PTR == pstMappedGuti)
    {
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_DeriveMappedGuti: Input para is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_DeriveMappedGuti_ENUM,LNAS_PARAM_INVALID);
        return;
    }
    /* �����οռ�*/
    NAS_LMM_MEM_SET(pstMappedGuti, 0, sizeof(NAS_LMM_GUTI_STRU))

    /* ��ȡ P-TMSI�� RAI*/
    NAS_EMM_GetPtmsiAndRai(&stPtmsi,&stRai);

    /* ��װMapped GUTI*/
    pstMappedGuti->stGutiHead.ucLenth   = NAS_EMM_AD_LEN_GUTI;
    pstMappedGuti->stGutiHead.ucOeToi   = NAS_EMM_AD_ID_GUTI;

    NAS_LMM_MEM_CPY(                    &(pstMappedGuti->stPlmnId),
                                       &(stRai.stLai.stPlmnId),
                                        sizeof(NAS_MM_PLMN_ID_STRU));
    pstMappedGuti->stMmeGroupId.ucGroupId = stRai.stLai.stLac.ucLac;
    pstMappedGuti->stMmeGroupId.ucGroupIdCnt = stRai.stLai.stLac.ucLacCnt;
    pstMappedGuti->stMmeCode.ucMmeCode  = stPtmsi.aucPtmsi[1];
    pstMappedGuti->stMTmsi.ucMTmsi      = ((stPtmsi.aucPtmsi[0])|(NAS_EMM_HITH_2_BITS_F));
    pstMappedGuti->stMTmsi.ucMTmsiCnt1  = stRai.ucRac;
    pstMappedGuti->stMTmsi.ucMTmsiCnt2  = stPtmsi.aucPtmsi[2];
    pstMappedGuti->stMTmsi.ucMTmsiCnt3  = stPtmsi.aucPtmsi[3];

    return;
}


/*leili modify for isr begin*/
/*PC REPLAY MODIFY BY LEILI BEGIN*/

VOS_UINT32  NAS_EMM_GetTinType(VOS_VOID )
{
    MMC_LMM_TIN_TYPE_ENUM_UINT32        ulTinType;

    #ifndef __PS_WIN32_RECUR__
    ulTinType = NAS_MML_GetTinType();

    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
    /* coverity[unchecked_value] */
    NAS_LMM_LogTinInfo(ulTinType,WUEPS_PID_MMC,PS_PID_MM);
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
    NAS_EMM_PUBU_LOG1_NORM("NAS_EMM_GetTinType: ulTinType = ", ulTinType);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_GetTinType_ENUM,LNAS_EMM_TIN_TYPE,ulTinType);

    #else

    ulTinType = Stub_NAS_MML_GetTinType();
    #endif
    return ulTinType;
}
/*PC REPLAY MODIFY BY LEILI END*/


VOS_VOID  NAS_EMM_SendTimerStateNotify
(
    NAS_LMM_PTL_TI_ENUM_UINT16      ulTimerId,
    LMM_MMC_TIMER_STATE_ENUM_UINT32  ulTimerState
)
{
    LMM_MMC_TIMER_STATE_NOTIFY_STRU           *pstTimerStateMsg;

    /* ����MMC�ڲ���Ϣ */
    pstTimerStateMsg = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_TIMER_STATE_NOTIFY_STRU));

    NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_SendTimerStateNotify", ulTimerId, ulTimerState);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_SendTimerStateNotify_ENUM,LNAS_FUNCTION_LABEL1,
                                        ulTimerId,
                                        ulTimerState);

    if (NAS_LMM_NULL_PTR == pstTimerStateMsg)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_WARN("NAS_EMM_SendTimerStateNotify: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SendTimerStateNotify_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstTimerStateMsg,0,sizeof(LMM_MMC_TIMER_STATE_NOTIFY_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstTimerStateMsg),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_TIMER_STATE_NOTIFY_STRU));

    /* �����ϢID */
    pstTimerStateMsg->ulMsgId           = ID_LMM_MMC_TIMER_STATE_NOTIFY;

    /* �����Ϣ�� */
    pstTimerStateMsg->ulOpId            = NAS_EMM_OPID_MMC;

    if (TI_NAS_EMM_PTL_T3412 == ulTimerId)
    {
        pstTimerStateMsg->bitOpT3412    = NAS_EMM_BIT_SLCT;
        pstTimerStateMsg->enT3412State  = ulTimerState;
    }
    else if (TI_NAS_EMM_PTL_T3423 == ulTimerId)
    {
        pstTimerStateMsg->bitOpT3423    = NAS_EMM_BIT_SLCT;
        pstTimerStateMsg->enT3423State  = ulTimerState;
    }
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
    else if (TI_NAS_EMM_PTL_T3402 == ulTimerId)
    {
        pstTimerStateMsg->bitOpT3402    = NAS_EMM_BIT_SLCT;
        pstTimerStateMsg->enT3402State  = ulTimerState;
    }
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */
    else
    {
        NAS_EMM_PUBU_LOG_NORM("NAS_EMM_SendTimerStateNotify: Timer type is err!!!");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_SendTimerStateNotify_ENUM,LNAS_ERROR);
    }

    /* ����MMC�ڲ���Ϣ */
    NAS_LMM_SendLmmMmcMsg(pstTimerStateMsg);

    return;
}

/*leili modify for isr end*/


VOS_VOID LNAS_LPSOM_GetCampedCellInfo(LPS_NAS_MM_TA_LIST_STRU *pstRegPlmnTaList,
    LPS_NAS_IMSI_STRU *pstImsiInfo,LPS_NAS_MM_GUTI_STRU *pstGutiInfo)
{
    VOS_UINT8                          *pucImsi;

    pucImsi = (VOS_UINT8 *)NAS_LMM_GetEmmInfoUeidImsiAddr();
    NAS_LMM_MEM_CPY(pstRegPlmnTaList, NAS_LMM_GetEmmInfoNetInfoTaiListAddr(), sizeof(NAS_MM_TA_LIST_STRU));
    NAS_LMM_MEM_CPY(pstGutiInfo, NAS_LMM_GetEmmInfoUeidGutiAddr(), sizeof(NAS_MM_GUTI_STRU));
    NAS_LMM_MEM_CPY(&(pstImsiInfo->aucImsi[0]),pucImsi,NAS_LMM_NVIM_IMSI_FILE_LEN);

    return;
}
/*****************************************************************************
 Function Name  : NAS_EMM_IsCsPsUeMode
 Description    : �ж��Ƿ�ΪCP/PS1����CS/PS2
 Input          : None
 Output         : None
 Return Value   : VOS_UINT32

 History        :
      1.lihong00150010      2011-08-27  Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_EMM_IsCsPsUeMode( VOS_VOID )
{
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-29, begin */
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32                   ulLteUeMode;
    ulLteUeMode  = NAS_LMM_GetEmmInfoUeOperationMode();

    if ((NAS_LMM_UE_CS_PS_MODE_1 == ulLteUeMode)
        || (NAS_LMM_UE_CS_PS_MODE_2 == ulLteUeMode))
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-29, end */
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}


/*****************************************************************************
 Function Name   : Nas_InitUeModeInfo
 Description     : ��ʼ��GU��UE MODE ��Ϣ
 Input           : ulInfoType:
 Output          :
 Return          :
 History         :
     1.    hanlufeng 41410       2011-9-27   Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_PubmInfoUeModeInit(VOS_VOID)
{
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32       ulLteUeMode;
    NAS_EMM_PUB_INFO_STRU                       *pstPubInfo = NAS_LMM_GetEmmInfoAddr();


    /* ��ȫ�ֱ�����ֵ

    NAS_LMM_GU_UE_MODE_ENUM_UINT32              ulGuUeMode;
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32       ulLteUeMode;
    NAS_EMM_USAGE_SETTING_UINT8                 ulUsageSetting;
    NAS_LMM_CS_SERVICE_ENUM_UINT32              ulCsService;


    NAS_LMM_SUP_ENUM_UINT32                     aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_BUTT];
    NAS_LMM_VOICE_DOMAIN_ENUM_UINT32            ulVoiceDomain;

    NAS_LMM_SUP_ENUM_UINT32                     aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_BUTT];
    NAS_LMM_SUP_SMS_DOMAIN_ENUM_UINT32          ulSmsDomainPrefer;

    NAS_LMM_SUP_ENUM_UINT32                     ulLmmSupIms;
    NAS_LMM_SUP_ENUM_UINT32                     ulCSFBAvail;

    NAS_LMM_EMERGENCY_NUM_LIST_STRU             stEmergencyNumList;
    VOS_UINT8                                   ucNetFeature;
    VOS_UINT8                                   aucRsv1[3];
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  ulAdditionUpRslt;
    */

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PubmInfoUeModeInit:  UE MODE init begin: ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_BEGIN);


    /* ��ֵ����ڶ�NVʱ���� NAS_EMM_ReadNvUeOperationMode����ʱҲͬ������LTE UE MODE*/
    NAS_LMM_SetEmmInfoGuUeMode(NAS_LMM_GU_UE_MODE_PS);

    NAS_LMM_SetEmmInfoUeCenter(EMM_SETTING_DATA_CENTRIC);
    NAS_EMM_PUBU_LOG1_INFO("UE CENTER = ",
                            NAS_LMM_GetEmmInfoUeCenter());
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_EMM_UE_CENTER,
                            NAS_LMM_GetEmmInfoUeCenter());

    /* ���ɶ�Ӧ��LTE UE MODE */
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-29, begin */
    ulLteUeMode  = NAS_LMM_GetEmmInfoUeOperationMode();
    NAS_LMM_SetEmmInfoUeOperationMode(ulLteUeMode);

    NAS_EMM_PUBU_LOG1_INFO("LTE UE MODE = ",
                            ulLteUeMode);
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-29, end */

    pstPubInfo->ulCsService = NAS_LMM_CS_SERVICE_BUTT;  /* ��ֵ����ڶ�NVʱ���� */
    NAS_EMM_PUBU_LOG1_INFO("ulCsService = ",
                            pstPubInfo->ulCsService);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_EMM_CSSERVICECFG,
                            pstPubInfo->ulCsService);

    pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_CS]  = NAS_LMM_NOT_SUP;
    pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_IMS] = NAS_LMM_NOT_SUP;
    NAS_EMM_PUBU_LOG2_INFO("aulLmmSupVoiceDomain CS and PS = ",
                            pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_CS],
                            pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_IMS]);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_EMM_VOICE_DOMAIN_CS_PS,
                            pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_CS],
                            pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_IMS]);

    /* ��ֵ����ڶ�NVʱ���� NAS_EMM_ReadNvVoiceDomain*/
    pstPubInfo->ulVoiceDomain = NAS_LMM_VOICE_DOMAIN_BUTT;
    NAS_EMM_PUBU_LOG1_INFO("ulVoiceDomain = ",
                            pstPubInfo->ulVoiceDomain);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_EMM_VOICE_DOMAIN,
                            pstPubInfo->ulVoiceDomain);

    pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_SGS]  = NAS_LMM_NOT_SUP;
    pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_IP ]  = NAS_LMM_NOT_SUP;
    NAS_EMM_PUBU_LOG2_INFO("aulLmmSupSmsDomain SGS and IP = ",
                            pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_SGS],
                            pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_IP]);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_EMM_SMS_DOMAIN_SGS_IP,
                            pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_SGS],
                            pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_IP]);

    /* �����ݲ�֧��SMS������Ϊ��Чֵ */
    pstPubInfo->ulSmsDomainPrefer = NAS_LMM_SUP_SMS_DOMAIN_BUTT;
    NAS_EMM_PUBU_LOG1_INFO("ulSmsDomainPrefer = ",
                            pstPubInfo->ulSmsDomainPrefer);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_EMM_SMS_DOMAIN_PREFER,
                            pstPubInfo->ulSmsDomainPrefer);

    pstPubInfo->ulLmmSupIms = NAS_LMM_NOT_SUP;
    NAS_EMM_PUBU_LOG1_INFO("ulLmmSupIms = ",
                            pstPubInfo->ulLmmSupIms);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_EMM_JUDGE_FLAG,
                            pstPubInfo->ulSmsDomainPrefer);

    /*
    pstPubInfo->ulCSFBAvail = NAS_LMM_NOT_SUP;
    NAS_EMM_PUBU_LOG1_INFO("ulCSFBAvail = ",
                            pstPubInfo->ulCSFBAvail);
    */
    /* lihong00150010 ims begin */
    /* ��ʼֵ��ΪNOT_ATTACHED */
    pstPubInfo->enAdditionUpRslt = NAS_LMM_ADDITIONAL_UPDATE_NOT_ATTACHED;
    /* lihong00150010 ims end */

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PubmInfoUeModeInit:  UE MODE init END. ");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PubmInfoUeModeInit_ENUM,LNAS_END);

    return;
}
VOS_UINT32  Nas_LMM_SetLteUeModeInfo(
    NAS_LMM_UEMODE_TYPE_ENUM_UINT32     ulInfoType,
    NAS_LMM_UEMODE_INFO_STRU           *pstLmmUeModeInfo)
{

    NAS_EMM_PUBU_LOG2_INFO("Nas_LMM_SetLteUeModeInfo:  ulInfoType = , pstLmmUeModeInfo = ",
                            ulInfoType,
                            pstLmmUeModeInfo);
    TLPS_PRINT2LAYER_INFO2(Nas_LMM_SetLteUeModeInfo_ENUM,LNAS_EMM_UE_MODE_TYPE_INFO,
                            ulInfoType,
                            pstLmmUeModeInfo);

    /* ��μ�� */
    if((NAS_EMM_NULL_PTR == pstLmmUeModeInfo) ||
        (NAS_LMM_UEMODE_INFO_GU_UEMODE != ulInfoType))
    {

        NAS_EMM_PUBU_LOG_WARN("Nas_LMM_SetLteUeModeInfo: ERR.");
        TLPS_PRINT2LAYER_WARNING(Nas_LMM_SetLteUeModeInfo_ENUM,LNAS_ERROR);
        return  NAS_EMM_FAIL;
    }

    NAS_EMM_PUBU_LOG_INFO("Nas_LMM_SetLteUeModeInfo: NAS_LMM_UEMODE_INFO_STRU content are :");
    TLPS_PRINT2LAYER_INFO(Nas_LMM_SetLteUeModeInfo_ENUM,LNAS_EMM_UE_MODE_INFO);
    NAS_COMM_PrintArray(             NAS_COMM_GET_MM_PRINT_BUF(),
                                     (VOS_UINT8 *)pstLmmUeModeInfo,
                                     sizeof(NAS_LMM_UEMODE_INFO_STRU));

    /*Coverity �澯���� 2013-9-26 Begin*/
    NAS_LMM_SetGuUeMode(pstLmmUeModeInfo->u.ulGuUeMode);
    /*Coverity �澯���� 2013-9-26 End*/

    return  NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : Nas_GetLteUeModeInfo
 Description     : ����GU��UE MODE����LNAS���ڲ�ģ�����
 Input           : ulInfoType:
 Output          :
 Return          :
 History         :
    1.Hanlufeng 41410      2011-10-13  Draft Enact

*****************************************************************************/
VOS_UINT32  Nas_LMM_GetLteUeModeInfo(
    NAS_LMM_UEMODE_TYPE_ENUM_UINT32     ulInfoType,
    NAS_LMM_UEMODE_INFO_STRU           *pstLmmUeModeInfo)
{

    NAS_EMM_PUB_INFO_STRU                       *pstPubInfo = NAS_LMM_GetEmmInfoAddr();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,begin */
    NAS_MML_MS_MODE_ENUM_UINT8         ucMsMode;
    ucMsMode = NAS_EMM_GetMsMode();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,end */

    NAS_EMM_PUBU_LOG2_INFO("Nas_LMM_GetLteUeModeInfo:  ulInfoType = , pstLmmUeModeInfo = ",
                            ulInfoType,
                            pstLmmUeModeInfo);
    TLPS_PRINT2LAYER_INFO2(Nas_LMM_GetLteUeModeInfo_ENUM,LNAS_EMM_UE_MODE_TYPE_INFO,
                            ulInfoType,
                            pstLmmUeModeInfo);

    /* ��μ�� */
    if((NAS_EMM_NULL_PTR == pstLmmUeModeInfo) ||
        (NAS_LMM_UEMODE_INFO_BUTT <= ulInfoType))
    {
        NAS_EMM_PUBU_LOG_WARN("Nas_LMM_GetLteUeModeInfo:  ERR");
        TLPS_PRINT2LAYER_WARNING(Nas_LMM_GetLteUeModeInfo_ENUM,LNAS_ERROR);
        return  NAS_EMM_FAIL;
    }

    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    switch(ulInfoType)
    {
        case    NAS_LMM_UEMODE_INFO_GU_UEMODE:
                pstLmmUeModeInfo->u.ulGuUeMode = ucMsMode;
                break;

        case    NAS_LMM_UEMODE_INFO_CENTER:
                pstLmmUeModeInfo->u.ulUsageSetting = NAS_LMM_GetEmmInfoUeCenter();
                break;

        case    NAS_LMM_UEMODE_INFO_LTE_UEMODE:
                pstLmmUeModeInfo->u.ulLteUeMode
                    = NAS_LMM_ComputeLteUeMode( ucMsMode,
                                                NAS_LMM_GetEmmInfoUeCenter());
                break;
        /*PC REPLAY MODIFY BY LEILI END*/
        case    NAS_LMM_UEMODE_INFO_SUP_VOICE_DOMAIN:
                pstLmmUeModeInfo->u.aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_CS ]
                    = pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_CS ];
                pstLmmUeModeInfo->u.aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_IMS]
                    = pstPubInfo->aulLmmSupVoiceDomain[NAS_LMM_SUP_VOICE_DOMAIN_IMS ];
                break;

        case    NAS_LMM_UEMODE_INFO_VOICE_DOMAIN_PRE:
                pstLmmUeModeInfo->u.ulVoiceDomain
                    = pstPubInfo->ulVoiceDomain;
                break;

        case    NAS_LMM_UEMODE_INFO_SUP_SMS_DOMAIN:
                pstLmmUeModeInfo->u.aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_SGS ]
                    = pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_SGS];
                pstLmmUeModeInfo->u.aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_IP]
                    = pstPubInfo->aulLmmSupSmsDomain[NAS_LMM_SUP_SMS_DOMAIN_IP ];
                break;

        case    NAS_LMM_UEMODE_INFO_SMS_DOMAIN_PRE:
                pstLmmUeModeInfo->u.ulSmsDomainPrefer
                    = pstPubInfo->ulSmsDomainPrefer;
                break;

        case    NAS_LMM_UEMODE_INFO_SUP_IMS:
                pstLmmUeModeInfo->u.ulLmmSupIms
                    = pstPubInfo->ulLmmSupIms;
                break;

        case    NAS_LMM_UEMODE_INFO_NET_FEATURE:
                pstLmmUeModeInfo->u.ucNetFeature
                    = pstPubInfo->ucNetFeature;
                break;

        default:
                NAS_EMM_PUBU_LOG_WARN("Nas_LMM_GetLteUeModeInfo: TYPE ERR.");
                TLPS_PRINT2LAYER_WARNING(Nas_LMM_GetLteUeModeInfo_ENUM,LNAS_FUNCTION_LABEL1);
                return  NAS_EMM_FAIL;
    }

    NAS_EMM_PUBU_LOG_INFO("Nas_LMM_GetLteUeModeInfo: NAS_LMM_UEMODE_INFO_STRU content are :");
    TLPS_PRINT2LAYER_INFO(Nas_LMM_GetLteUeModeInfo_ENUM,LNAS_EMM_UE_MODE_INFO);
    NAS_COMM_PrintArray(             NAS_COMM_GET_MM_PRINT_BUF(),
                                     (VOS_UINT8 *)pstLmmUeModeInfo,
                                     sizeof(NAS_LMM_UEMODE_INFO_STRU));

    return  NAS_EMM_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SetGuUeMode
 Description     : GU UE MODE�ı�ᵼ��LTE UE MODE�޸�
                   ��GU��UE MODE��UE CENTER����LTE UE MODE����������ȫ�ֱ���
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-10-10  Draft Enact

*****************************************************************************/
VOS_VOID NAS_LMM_SetGuUeMode
(
    NAS_LMM_GU_UE_MODE_ENUM_UINT32      ulGuUeMode
)
{
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   ulLteUeModeCur;
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   ulLteUeModeNew;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,begin */
    NAS_MML_MS_MODE_ENUM_UINT8         ucMsMode;
    ucMsMode = NAS_EMM_GetMsMode();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30,end */

    NAS_EMM_PUBU_LOG1_INFO("NAS_LMM_SetGuUeMode: income ulGuUeMode = ", ulGuUeMode);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SetGuUeMode_ENUM,LNAS_EMM_GU_UE_MODE,ulGuUeMode);
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    /* ��ȡ��ǰ�� LTE UE MODE */
    ulLteUeModeCur = NAS_LMM_ComputeLteUeMode(ucMsMode,
                                              NAS_LMM_GetEmmInfoUeCenter());

    /* ��GU��UE MODE��UE CENTER����LTE UE MODE */
    ulLteUeModeNew = NAS_LMM_ComputeLteUeMode(ucMsMode, NAS_LMM_GetEmmInfoUeCenter());
    /*PC REPLAY MODIFY BY LEILI END*/
    /* ��ӡ�仯ǰ������� */
    NAS_EMM_PUBU_LOG1_INFO(" NAS_LMM_SetGuUeMode: CUR LTE_UE_MODE = ", ulLteUeModeCur);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SetGuUeMode_ENUM,LNAS_EMM_LTE_UE_MODE,ulLteUeModeCur);
    NAS_EMM_PUBU_LOG_INFO("  LTE_UE_MODE change   ===>");
    NAS_EMM_PUBU_LOG1_INFO(" NAS_LMM_SetGuUeMode: NEW LTE_UE_MODE = ", ulLteUeModeNew);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SetGuUeMode_ENUM,LNAS_EMM_UE_MODE_CHANGE_TO,ulLteUeModeNew);


    /* LMM��ȫ�ֱ�������GU UE MODE */
    NAS_LMM_SetEmmInfoGuUeMode(ulGuUeMode);
    NAS_LMM_SetEmmInfoUeOperationMode(ulLteUeModeNew);

    /* Ue Center �仯��Ӧ�ĸ�ģ��Ĳ��� */
    NAS_LMM_LteModeChange(ulLteUeModeCur, ulLteUeModeNew);

    return;
}
NAS_LMM_GU_UE_MODE_ENUM_UINT32  NAS_LMM_GetEmmInfoGuUeMode(VOS_VOID)
{
    /* ����GU OPERATION MODE��MML���ź���MML�������� */
    NAS_LMM_GU_UE_MODE_ENUM_UINT32      ulGuOperationMode;

    ulGuOperationMode       = NAS_LMM_GetEmmInfoAddr()->ulGuUeMode;
    return ulGuOperationMode;
}
NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32  NAS_LMM_GetEmmInfoUeOperationMode(VOS_VOID)
{
    /* ����lte OPERATION MODE��
        ʵʱ��ȡGU OPRATION MODE������ue setting �����LTE OPERATION MODE*/
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32      ullteOperationMode;
    /*PC REPLAY MODIFY BY LEILI BEGIN*/
    ullteOperationMode = NAS_LMM_ComputeLteUeMode( NAS_EMM_GetMsMode(),
                                            NAS_LMM_GetEmmInfoUeCenter());
    /*PC REPLAY MODIFY BY LEILI END*/
    return ullteOperationMode;
}

/*****************************************************************************
 Function Name   : NAS_LMM_LteModeChange
 Description     : ��ģ���ڴ���Ӻ��� ,�԰�LTE UE MODE�ı��֪ͨ���Լ�
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.Hanlufeng 41410      2011-10-13  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LMM_LteModeChange(
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   ulLteUeModeCur,
    NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   ulLteUeModeNew)
{
    /* ��Ҫ��ʱ�˽�LTE UE MODE�����ģ���ڴ���ӻص����� */

    (void)ulLteUeModeCur;
    (void)ulLteUeModeNew;
    return;
}
NAS_LMM_UE_OPERATION_MODE_ENUM_UINT32   NAS_LMM_ComputeLteUeMode
(
    NAS_MML_MS_MODE_ENUM_UINT8          ulGuUeMode,
    NAS_EMM_USAGE_SETTING_UINT32        ulUeCenter
)
{

    NAS_EMM_PUBU_LOG2_INFO("NAS_LMM_ComputeLteUeMode: ulGuUeMode =,  ucUeCenter = ",
                             ulGuUeMode, ulUeCenter);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_ComputeLteUeMode_ENUM,LNAS_EMM_GU_UE_MODE,ulGuUeMode);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_ComputeLteUeMode_ENUM,LNAS_EMM_UE_CENTER,ulUeCenter);

    NAS_EMM_PUBU_LOG_INFO("Compute out : LTE UE MODE = ");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_ComputeLteUeMode_ENUM,LNAS_EMM_UE_CENTER);

    /* ��GU��UE MODE��UE CENTER����LTE UE MODE */
    if( (NAS_MML_MS_MODE_PS_ONLY == ulGuUeMode) ||
        (NAS_MML_MS_MODE_CS_ONLY == ulGuUeMode))
    {   /* GU PS  ,GU��CSû��Э���Ӧ��SRSҪ����LTE ��PS������ */

        if(EMM_SETTING_DATA_CENTRIC == ulUeCenter)
        {
            NAS_EMM_PUBU_LOG_INFO(" NAS_LMM_UE_PS_MODE_2 ");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_ComputeLteUeMode_ENUM,LNAS_FUNCTION_LABEL1);
            return  NAS_LMM_UE_PS_MODE_2;
        }
        else
        {
            NAS_EMM_PUBU_LOG_INFO(" NAS_LMM_UE_PS_MODE_1 ");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_ComputeLteUeMode_ENUM,LNAS_FUNCTION_LABEL2);
            return  NAS_LMM_UE_PS_MODE_1;
        }
    }
    else
    {   /*CS_PS*/

        if(EMM_SETTING_DATA_CENTRIC == ulUeCenter)
        {
            NAS_EMM_PUBU_LOG_INFO(" NAS_LMM_UE_CS_PS_MODE_2 ");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_ComputeLteUeMode_ENUM,LNAS_FUNCTION_LABEL3);
            return  NAS_LMM_UE_CS_PS_MODE_2;
        }
        else
        {
            NAS_EMM_PUBU_LOG_INFO("NAS_LMM_UE_CS_PS_MODE_1 ");
            TLPS_PRINT2LAYER_INFO(NAS_LMM_ComputeLteUeMode_ENUM,LNAS_FUNCTION_LABEL4);
            return  NAS_LMM_UE_CS_PS_MODE_1;
        }
    }
}
/*****************************************************************************
 Function Name   : NAS_EMM_lteRatIsExist
 Description     :
 Input           :
 Output          :
 Return          : NAS_LMM_FAIL:���뼼������L
                   NAS_LMM_SUCC:���뼼������L
 History         :
    1.ZHANGCAIXIA      2011-9-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_lteRatIsExist(VOS_VOID)
{
    if ( (NAS_LMM_RAT_PRIO_NULL ==  NAS_LMM_GetCurLtePrio())
      ||(NAS_LMM_RAT_PRIO_BUTT == NAS_LMM_GetCurLtePrio()))
    {
        NAS_LMM_EMM_PLMN_LOG_ERR("NAS_EMM_lteRatIsExist: MMC START REQ RAT LIST LTE NOT EXIST ");
        TLPS_PRINT2LAYER_ERROR1(NAS_EMM_lteRatIsExist_ENUM,LNAS_EMM_JUDGE_FLAG,NAS_LMM_FAIL);
        return NAS_LMM_FAIL;
    }
    return NAS_LMM_SUCC;
}


VOS_UINT32  NAS_EMM_IsLteDisabled( VOS_VOID )
{
    if(NAS_LMM_LTE_DISABLED == NAS_EMM_GetLteEnableSta())
    {
        NAS_LMM_EMM_PLMN_LOG_INFO("NAS_EMM_IsLteDisabled:LTE DISABLTED.");
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_IsLteDisabled_ENUM,LNAS_EMM_JUDGE_FLAG,NAS_LMM_SUCC);
        return NAS_LMM_SUCC;
    }

    return NAS_LMM_FAIL;
}
/*****************************************************************************
 Function Name   : NAS_EMM_SendMmCombinedStartNotifyReq
 Description     : ��MM����LMM_MM_COMBINED_START_NOTIFY_REQ��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-11-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SendMmCombinedStartNotifyReq
(
    MM_LMM_COMBINED_TYPE_ENUM_UINT32    enCombinedType
)
{
    LMM_MM_COMBINED_START_NOTIFY_REQ_STRU   *pstMmComStartNotfiyReq = VOS_NULL_PTR;

    /* ����DOPRA��Ϣ */
    pstMmComStartNotfiyReq = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MM_COMBINED_START_NOTIFY_REQ_STRU));
    if (NAS_LMM_NULL_PTR == pstMmComStartNotfiyReq)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmCombinedStartNotifyReq: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmCombinedStartNotifyReq_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstMmComStartNotfiyReq, 0, sizeof(LMM_MM_COMBINED_START_NOTIFY_REQ_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_MM_MSG_HEADER((pstMmComStartNotfiyReq),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MM_COMBINED_START_NOTIFY_REQ_STRU));

    /* �����ϢID */
    pstMmComStartNotfiyReq->ulMsgId    = ID_LMM_MM_COMBINED_START_NOTIFY_REQ;

    /* �����Ϣ�� */
    pstMmComStartNotfiyReq->ulOpId     = NAS_EMM_OPID_MM;

    /* ��������������� */
    pstMmComStartNotfiyReq->enCombinedType = enCombinedType;

    /* ����DOPRA��Ϣ */
    NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstMmComStartNotfiyReq);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SetTauTypeNoProcedure
 Description     : δ����TAU����ʱUE��ǰ�Ƿ���������������TAU����дTAU����
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-11-15  Draft Enact

*****************************************************************************/
VOS_VOID NAS_EMM_SetTauTypeNoProcedure( VOS_VOID )
{
    /* LMM����ݵ�ǰע��������дTAU�������ͣ������ǰע����ΪCS+PS����TAU������
       ����ΪMMC_LMM_COMBINED_TA_LA_UPDATING�������ǰע����ΪPS����TAU��������
       ��ΪMMC_LMM_TA_UPDATING��*/
    if (NAS_LMM_REG_DOMAIN_CS_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_EMM_TAU_SaveTAUtype(NAS_EMM_CN_TAU_TYPE_COMBINED_TA_LA_UPDATING);
    }
    else if (NAS_LMM_REG_DOMAIN_PS == NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_EMM_TAU_SaveTAUtype(NAS_EMM_CN_TAU_TYPE_TA_UPDATING);
    }
    else
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SetTauTypeNoProcedure: Reg Domain is NULL!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SetTauTypeNoProcedure_ENUM,LNAS_ERROR);
    }
}
VOS_UINT32 NAS_LMM_SetEmmInfoUeRadioCapChg(
           NAS_LMM_UE_RADIO_CAP_CHANGE_ENUM_UINT32   enCurrentUeCapChg,
           NAS_LMM_UE_RADIO_CAP_CHANGE_ENUM_UINT32   enLastUeCapChg)
{
    NAS_EMM_PUBU_LOG_INFO("NAS_LMM_SetEmmInfoUeRadioCapChg is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_SetEmmInfoUeRadioCapChg_ENUM,LNAS_ENTRY);

    /*�����ǰ�ĸ������ʹ��ڵ����ϴεĸ������ͣ������õ�ǰ��UE�����ı䣬
      �������������ø�������, ����ΪʲôҪ����? ��������:
      ����ʱҲ��Ϊ��Ҫ���£���Ҫ�ǿ��ǵ�NAS_LMM_ProcRrcSysCfgCnfNotSuspend
      ������REG+REG_IMSI_DETACH_WATI_CN_DETACH_CNF״̬��AUTH_INIT+AUTH_WAIT_CN_AUTH
      ״̬�µĵ����ȼ������֧��������ڲ���Ϊ��Ҫ���£��򵱴�������ȼ������SYSCFG
      ʱ����Ϊû�и��¶�ֱ���˳�
     */
    if(enCurrentUeCapChg >= enLastUeCapChg ||
       NAS_LMM_UE_RADIO_CAP_CHG_BUTT == enLastUeCapChg)
    {
        NAS_LMM_SetEmmInfoUeRadioCapChgFlag(enCurrentUeCapChg);
        return NAS_UE_CAP_CHG_HAVE_UPDATE;
    }
    else
    {
        return  NAS_UE_CAP_CHG_NO_UPDATE;
    }
}


VOS_UINT32  NAS_EMM_RecordUeRadioAccCapChg(
    VOS_UINT8                           ucRadioAccCapChgInd )
{
    NAS_UE_CAP_CHG_UPDATE_TYPE_ENUM_UINT32      enResult = NAS_UE_CAP_CHG_BUTT;

    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_RecordUeRadioAccCapChg: ucRadioAccCapChgInd value ="
                             , ucRadioAccCapChgInd);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_RecordUeRadioAccCapChg_ENUM,LNAS_EMM_RADIO_ACC_CAP_CHG,
                                ucRadioAccCapChgInd);
    /*�����ǰ����״̬��EMM_MS_DEREG��ֱ�ӷ������߱������û�и���*/
    if(EMM_MS_DEREG == NAS_EMM_CUR_MAIN_STAT)
    {
        return  NAS_UE_CAP_CHG_NO_UPDATE;
    }

    /* LTE���������仯*/
    if(NAS_EMM_UE_LTE_RADIO_CAP_NOT_CHG != (ucRadioAccCapChgInd & NAS_EMM_BIT_3))
    {

        /* ����ǹ���̬���յ�L���������仯��Ϊ�˻ص�Lģ����TAU����ATTACH����Ϊ��¼��GU�仯 */
        if (NAS_LMM_CUR_LTE_SUSPEND == NAS_EMM_GetCurLteState())
        {
            NAS_EMM_PUBU_LOG_NORM("NAS_EMM_RecordUeRadioAccCapChg: LTE current is suspended, record GU change.");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_RecordUeRadioAccCapChg_ENUM,LNAS_FUNCTION_LABEL1);
            enResult = NAS_LMM_SetEmmInfoUeRadioCapChg(NAS_LMM_UE_RADIO_CAP_GU_CHG,
                                                       NAS_LMM_GetEmmInfoUeRadioCapChgFlag());
        }
        else
        {
            enResult = NAS_LMM_SetEmmInfoUeRadioCapChg(NAS_LMM_UE_RADIO_CAP_LTE_CHG,
                                                       NAS_LMM_GetEmmInfoUeRadioCapChgFlag());
        }
    }

    /* GU���������仯 */
    else if (NAS_EMM_UE_GU_RADIO_CAP_NOT_CHG != (ucRadioAccCapChgInd & NAS_EMM_LOW_2_BITS_F))
    {
        enResult = NAS_LMM_SetEmmInfoUeRadioCapChg(NAS_LMM_UE_RADIO_CAP_GU_CHG,
                                                   NAS_LMM_GetEmmInfoUeRadioCapChgFlag());
    }

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* EHRPD���������仯�����������GU�仯��ȫ��ͬ */
    else if (NAS_EMM_UE_HRPD_RADIO_CAP_NOT_CHG != (ucRadioAccCapChgInd & NAS_EMM_FIFTH_BITS_F))
    {
        enResult = NAS_LMM_SetEmmInfoUeRadioCapChg(NAS_LMM_UE_RADIO_CAP_GU_CHG,
                                                   NAS_LMM_GetEmmInfoUeRadioCapChgFlag());
    }
    #endif

    /* �ޱ仯 */
    else
    {
        enResult = NAS_LMM_SetEmmInfoUeRadioCapChg(NAS_LMM_UE_RADIO_CAP_NOT_CHG,
                                                   NAS_LMM_GetEmmInfoUeRadioCapChgFlag());
    }
    return enResult;
}


VOS_VOID  NAS_EMM_ClearUeRadioAccCapChgFlag(VOS_VOID)
{
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_ClearUeRadioAccCapChgFlag: UeRadioCapChgFlag is cleared !");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_ClearUeRadioAccCapChgFlag_ENUM,LNAS_BEGIN);

    NAS_LMM_SetEmmInfoUeRadioCapChgFlag(NAS_LMM_UE_RADIO_CAP_NOT_CHG);

    return ;
}




VOS_VOID  NAS_EMM_SomeStateRcvMsgSysInfoLteRadioCapChgCommProc(VOS_VOID)
{
        VOS_UINT32                      ulRst = NAS_EMM_FAIL;

        /* ����DETACH, ͬʱ�ͷŸ�ģ����Դ:��̬�ڴ桢����ֵ */
        NAS_EMM_LocalDetachProc();

        #if (FEATURE_PTM == FEATURE_ON)
        NAS_EMM_LocalDetachErrRecord(EMM_ERR_LOG_LOCAL_DETACH_TYPE_RADIO_CAP_CHANGE);
        #endif
        NAS_LMM_DeregReleaseResource();

        NAS_EMM_AdStateConvert(EMM_MS_DEREG,
                              EMM_SS_DEREG_NORMAL_SERVICE,
                              TI_NAS_EMM_STATE_NO_TIMER);


        /* ��MMC���ͱ���LMM_MMC_DETACH_IND��Ϣ */
        NAS_EMM_MmcSendDetIndLocal(MMC_LMM_L_LOCAL_DETACH_OTHERS);

        /* ���·���ATTACH */
        ulRst = NAS_EMM_SendIntraAttachReq();
        if (NAS_EMM_SUCC != ulRst)
        {
            NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SomeStateRcvMsgSysInfoLteRadioCapChgCommProc:  send INTRA ATTACH REQ ERR !");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SomeStateRcvMsgSysInfoLteRadioCapChgCommProc_ENUM,LNAS_ERROR);
        }

    return;
}

/* del by lihong00150010 ims */



VOS_VOID    NAS_EMM_SendMmcInfoChangeNotify( VOS_VOID )
{
    LMM_MMC_INFO_CHANGE_NOTIFY_STRU    *pstMmcInfoChangeNotify  = VOS_NULL_PTR;
    NAS_LMM_PUB_INFO_STRU              *pstPubInfo              = VOS_NULL_PTR;
    NAS_MML_EMERGENCY_NUM_LIST_STRU    *pstMmlEmerNumList       = VOS_NULL_PTR;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30, begin */
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAddUpdateRslt;

    enAddUpdateRslt = NAS_EMM_GetAddUpdateRslt();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30, end */

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_SendMmcInfoChangeNotify is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendMmcInfoChangeNotify_ENUM,LNAS_ENTRY);

    /* ����MMC�ڲ���Ϣ */
    pstMmcInfoChangeNotify = (VOS_VOID *) NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_INFO_CHANGE_NOTIFY_STRU));
    if (NAS_LMM_NULL_PTR == pstMmcInfoChangeNotify)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_EMM_SendMmcInfoChangeNotify: MSG ALLOC ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendMmcInfoChangeNotify_ENUM,LNAS_NULL_PTR);
        return ;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstMmcInfoChangeNotify, 0, sizeof(LMM_MMC_INFO_CHANGE_NOTIFY_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_MMC_MSG_HEADER((pstMmcInfoChangeNotify),
                             NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LMM_MMC_INFO_CHANGE_NOTIFY_STRU));

    /* �����ϢID */
    pstMmcInfoChangeNotify->ulMsgId                 = ID_LMM_MMC_INFO_CHANGE_NOTIFY;

    /* �����Ϣ�� */
    pstMmcInfoChangeNotify->ulOpId                  = NAS_EMM_OPID_MM;

    pstMmlEmerNumList   = NAS_EMM_GetEmergencyListFromMml();
    pstPubInfo          = NAS_LMM_GetEmmInfoAddr();

    /* �������������б� */
    /* ��GUͬ��ȷ��LMM_MMC_INFO_CHANGE_NOTIFY_STRU������bit λ��ȥ�� */
    /*pstMmcInfoChangeNotify->bitOpEmcNumList         = NAS_EMM_BIT_SLCT;*/
    pstMmcInfoChangeNotify->ucEmergencyNumAmount    = pstMmlEmerNumList->ucEmergencyNumber;
    NAS_LMM_MEM_CPY(    pstMmcInfoChangeNotify->astEmergencyNumList,
                        pstMmlEmerNumList->aucEmergencyList,
                        sizeof(LMM_MMC_EMERGENCY_NUM_STRU) * LMM_MMC_EMERGENCY_NUM_LIST_MAX_RECORDS);

    /* ��������Ƿ�֧��IMS VOICE�ͽ����� */
    if (NAS_EMM_BIT_SLCT == pstPubInfo->bitOpNetFeature)
    {
        /*pstMmcInfoChangeNotify->bitOpImsVoPS        = NAS_EMM_BIT_SLCT;*/
        pstMmcInfoChangeNotify->enNwImsVoPS         = pstPubInfo->ucNetFeature & NAS_EMM_BIT_1;

        /*pstMmcInfoChangeNotify->bitOpEmcBS          = NAS_EMM_BIT_SLCT;*/
        pstMmcInfoChangeNotify->enNwEmcBS           = (pstPubInfo->ucNetFeature & NAS_EMM_BIT_2) >> NAS_EMM_MOVEMENT_1_BYTE;
    }
    else
    {
        /*pstMmcInfoChangeNotify->bitOpImsVoPS        = NAS_EMM_BIT_SLCT;*/
        pstMmcInfoChangeNotify->enNwImsVoPS         = LMM_MMC_NW_IMS_VOICE_NOT_SUPPORTED;

        /*pstMmcInfoChangeNotify->bitOpEmcBS          = NAS_EMM_BIT_SLCT;*/
        pstMmcInfoChangeNotify->enNwEmcBS           = LMM_MMC_NW_EMC_BS_NOT_SUPPORTED;
    }
    /* pstMmcInfoChangeNotify->bitOpLteCsCap           = NAS_EMM_BIT_SLCT; */
    if (NAS_LMM_ADDITIONAL_UPDATE_BUTT == enAddUpdateRslt)
    {
        pstMmcInfoChangeNotify->enLteCsCap          = LMM_MMC_LTE_CS_CAPBILITY_NO_ADDITION_INFO;
    }
    else
    {
        pstMmcInfoChangeNotify->enLteCsCap          = enAddUpdateRslt;
    }

    /* ����MMC�ڲ���Ϣ */
    NAS_LMM_SendLmmMmcMsg((VOS_VOID*)pstMmcInfoChangeNotify);

    return;
}



VOS_VOID NAS_EMM_SaveLastAttemptRegTa(VOS_VOID)
{
    NAS_MM_NETWORK_ID_STRU             *pstPresentNetInfo = NAS_EMM_NULL_PTR;
    NAS_LMM_NETWORK_INFO_STRU          *pstNetInfo        = NAS_EMM_NULL_PTR;
    NAS_MM_TA_STRU                     *pstLastAttmpRegTa = NAS_EMM_NULL_PTR;

    pstNetInfo                         = NAS_LMM_GetEmmInfoNetInfoAddr();
    pstPresentNetInfo                  = NAS_LMM_GetEmmInfoNetInfoPresentNetAddr();
    pstLastAttmpRegTa                  = NAS_LMM_GetEmmInfoNetInfoLastAttmpRegTaAddr();

    pstNetInfo->bitOpLastAttmpRegTa    = NAS_EMM_BIT_SLCT;
    pstLastAttmpRegTa->stTac.ucTac     = pstPresentNetInfo->stTac.ucTac;
    pstLastAttmpRegTa->stTac.ucTacCnt  = pstPresentNetInfo->stTac.ucTacCnt;
    NAS_LMM_PlmnCpy(&pstLastAttmpRegTa->stPlmnId, &pstPresentNetInfo->stPlmnId);

}


VOS_UINT32 NAS_EMM_IsT3411orT3402Running
(
    NAS_LMM_PTL_TI_ENUM_UINT16  *pPtlTimerId
)
{
    VOS_UINT32    ulCheckRslt = NAS_EMM_NO;
    if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3411))
    {
        *pPtlTimerId = TI_NAS_EMM_PTL_T3411;
        ulCheckRslt = NAS_EMM_YES;
    }
    else if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsPtlTimerRunning(TI_NAS_EMM_PTL_T3402))
    {
        *pPtlTimerId = TI_NAS_EMM_PTL_T3402;
        ulCheckRslt = NAS_EMM_YES;
    }
    else
    {
        *pPtlTimerId = NAS_LMM_PTL_TI_BUTT;
        ulCheckRslt = NAS_EMM_NO;
    }

    return ulCheckRslt;
}


VOS_UINT32  NAS_LMM_IsRrcConnectStatusIdle(VOS_VOID)
{
    /* IDLE̬���ͷŹ����ж���MMC��RRC��������Ϊ��IDLE, ��LMM�ڲ��������� */
    if ((NAS_EMM_CONN_IDLE == NAS_EMM_GetConnState())
        || (NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState()))
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;

}
VOS_VOID  NAS_EMM_DisableLteCommonProc( VOS_VOID )
{
   if(NAS_EMM_TAU_COMPLETE_VALID == NAS_EMM_TAU_GetEmmTauCompleteFlag())
   {
       NAS_LMM_PUBM_LOG_NORM("NAS_EMM_DisableLteCommonProc,TAU COMPLETE NEEDED DELAY");
       TLPS_PRINT2LAYER_INFO(NAS_EMM_DisableLteCommonProc_ENUM,LNAS_EMM_TAU_CMP_NEED_DELAY);

       /* �ӳ�500ms����Ϊ��ʹ��TAU COMPLETE��Ϣ�ܹ��������ͳ�ȥ */
       (VOS_VOID)TLPS_TaskDelay(500);
   }
   NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
}
VOS_VOID  NAS_EMM_SendIntraEia0ActNotify( VOS_VOID )
{
    NAS_LMM_INTRA_EIA0_ACT_NOTIFY_STRU         *pstEia0ActNotify    = NAS_LMM_NULL_PTR;
    VOS_UINT32                                  ulLen               = NAS_EMM_NULL;

    /*ȷ����Ϣ����*/
    ulLen = sizeof(NAS_LMM_INTRA_EIA0_ACT_NOTIFY_STRU);

    /*����ռ�*/
    pstEia0ActNotify  = (VOS_VOID *)NAS_LMM_GetSendIntraMsgBuffAddr(ulLen);
    if(NAS_EMM_NULL_PTR == pstEia0ActNotify)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_EMM_SendIntraEia0ActNotify: INTRA MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SendIntraEia0ActNotify_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* ���VOS��Ϣͷ */
    NAS_EMM_INTRA_MSG_HEADER(pstEia0ActNotify,(ulLen-NAS_EMM_VOS_HEADER_LEN));

    /* ���DOPRA��ϢID    */
    pstEia0ActNotify->ulMsgId = ID_NAS_LMM_INTRA_EIA0_ACT_NOTIFY;

    /*�����ڲ���Ϣ�����*/
    NAS_EMM_SEND_INTRA_MSG(pstEia0ActNotify);

    return;
}
VOS_UINT32 NAS_EMM_IsSmsOnlyCsfbNotPrefDisableNeeded( VOS_VOID )
{
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30, begin */
    NAS_LMM_ADDITIONAL_UPDATE_RSLT_ENUM_UINT32  enAddUpdateRslt;

    enAddUpdateRslt = NAS_EMM_GetAddUpdateRslt();
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-30, end */

    if (NAS_LMM_REG_DOMAIN_CS_PS != NAS_LMM_GetEmmInfoRegDomain())
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_IsCsPs1DisableNeeded:Reg domain is not cs+ps");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSmsOnlyCsfbNotPrefDisableNeeded_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_NO;
    }

    if (NAS_LMM_UE_CS_PS_MODE_1 != NAS_LMM_GetEmmInfoUeOperationMode())
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_IsCsPs1DisableNeeded:ue mode is not cs/ps1");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSmsOnlyCsfbNotPrefDisableNeeded_ENUM,LNAS_FUNCTION_LABEL2);
        return NAS_EMM_NO;
    }

    if (NAS_EMM_SUCC != NAS_EMM_CheckMutiModeSupport())
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_IsCsPs1DisableNeeded:lte only");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSmsOnlyCsfbNotPrefDisableNeeded_ENUM,LNAS_FUNCTION_LABEL3);
        return NAS_EMM_NO;
    }

    if ((NAS_LMM_ADDITIONAL_UPDATE_SMS_ONLY == enAddUpdateRslt)
            || (NAS_LMM_ADDITIONAL_UPDATE_CSFB_NOT_PREFERED == enAddUpdateRslt))
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_EMM_IsCsPs1DisableNeeded:SMS ONLY or CSFB not preferred");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsSmsOnlyCsfbNotPrefDisableNeeded_ENUM,LNAS_FUNCTION_LABEL4);
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}


VOS_VOID NAS_EMM_RecogAndProcSmsOnlyCsfbNotPrefDisable( VOS_VOID )
{
    if (NAS_EMM_YES == NAS_EMM_IsSmsOnlyCsfbNotPrefDisableNeeded())
    {

        NAS_EMM_DisableLteCommonProc();

    }
}

/*****************************************************************************
 Function Name   : NAS_EMM_ClearEmcEsmMsg
 Description     : ����������͵�ESM��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2012-10-31  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ClearEmcEsmMsg( VOS_VOID )
{
    VOS_UINT8                          *pucEsmMsg   = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulRslt      = NAS_EMM_NULL;

    pucEsmMsg = NAS_LMM_GetEmmInfoEsmBuffAddr();

    if (NAS_EMM_NULL_PTR == pucEsmMsg)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_ClearEmcEsmMsg, Memory is null");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_ClearEmcEsmMsg_ENUM,LNAS_NULL_PTR);
        return ;
    }

    ulRslt = NAS_COMM_FreeBuffItem(NAS_COMM_BUFF_TYPE_EMM,(VOS_VOID *)pucEsmMsg);

    if (NAS_COMM_BUFF_SUCCESS != ulRslt)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_ClearEmcEsmMsg, Memory Free is not succ");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_ClearEmcEsmMsg_ENUM,LNAS_FAIL);
    }

    /* lihong00150010 emergency tau&service begin */
    NAS_LMM_GetEmmInfoEsmBuffAddr() = NAS_EMM_NULL_PTR;
    /* lihong00150010 emergency tau&service end */

    return ;
}

/* lihong00150010 emergency tau&service begin */
/*****************************************************************************
 Function Name   : NAS_EMM_SndEmcEsmMsg
 Description     : ���ͽ������͵�ESM��Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2012-12-13  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_SndEmcEsmMsg( VOS_VOID )
{
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg   = NAS_EMM_NULL_PTR;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_SndEmcEsmMsg is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SndEmcEsmMsg_ENUM,LNAS_ENTRY);

    pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU *)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();

    if (NAS_EMM_NULL_PTR == pstEsmMsg)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_SndEmcEsmMsg, Memory is null");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SndEmcEsmMsg_ENUM,LNAS_NULL_PTR);
        return ;
    }

    NAS_EMM_SER_SendMrrcDataReq_ESMdata(&pstEsmMsg->stEsmMsg, pstEsmMsg->ulOpid);

    /* ����PDN����SERVICE��Ȼ��TAU��ϣ�TAU�ɹ���ɷ��ͽ���PDN����������Ϣ��
       ��Ҫ���SERVICE�����д洢�Ľ���PDN����������Ϣ��������SERVICE��ͻ����ʱ��
       ���ᷢ��һ�� */
    NAS_EMM_SER_DeleteEsmMsg(pstEsmMsg->ulOpid);

    NAS_EMM_ClearEmcEsmMsg();

    return ;
}
/* lihong00150010 emergency tau&service end */

/*****************************************************************************
 Function Name   : NAS_EMM_SaveEmcEsmMsg
 Description     : ����������͵�ESM��Ϣ
 Input           : pstMsgStru
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2012-10-31  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_SaveEmcEsmMsg
(
    VOS_VOID                           *pMsgStru
)
{
    NAS_EMM_ESM_MSG_BUFF_STRU          *pstEsmMsg       = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulBufSize       = NAS_EMM_NULL;
    EMM_ESM_DATA_REQ_STRU              *pstEsmDataReq   = NAS_EMM_NULL_PTR;

    if (NAS_EMM_NULL_PTR != NAS_LMM_GetEmmInfoEsmBuffAddr())
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_EMM_SaveEmcEsmMsg, Memory is already used!");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SaveEmcEsmMsg_ENUM,LNAS_NULL_PTR);
        NAS_EMM_ClearEmcEsmMsg();
    }

    pstEsmDataReq = (EMM_ESM_DATA_REQ_STRU*)pMsgStru;

    /* ����ռ� */
    ulBufSize = (sizeof(NAS_EMM_ESM_MSG_BUFF_STRU) +
                                        pstEsmDataReq->stEsmMsg.ulEsmMsgSize) - 4;

    NAS_LMM_GetEmmInfoEsmBuffAddr() = NAS_COMM_AllocBuffItem(   NAS_COMM_BUFF_TYPE_EMM,
                                                                ulBufSize);

    if (NAS_LMM_NULL_PTR != NAS_LMM_GetEmmInfoEsmBuffAddr())
    {
        pstEsmMsg = (NAS_EMM_ESM_MSG_BUFF_STRU*)(VOS_VOID*)NAS_LMM_GetEmmInfoEsmBuffAddr();

        /* �洢ESM��Ϣ */
        pstEsmMsg->stEsmMsg.ulEsmMsgSize = pstEsmDataReq->stEsmMsg.ulEsmMsgSize;

        NAS_LMM_MEM_CPY(        pstEsmMsg->stEsmMsg.aucEsmMsg,
                                pstEsmDataReq->stEsmMsg.aucEsmMsg,
                                pstEsmDataReq->stEsmMsg.ulEsmMsgSize);

        /* �洢OPID */
        pstEsmMsg->ulOpid       = pstEsmDataReq->ulOpId;

        /* �洢������ʶ */
        pstEsmMsg->ulIsEmcType  = pstEsmDataReq->ulIsEmcType;
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN( "NAS_EMM_SaveEmcEsmMsg: NAS_AllocBuffItem return null pointer.");
        TLPS_PRINT2LAYER_WARNING(NAS_EMM_SaveEmcEsmMsg_ENUM,LNAS_RETRUN_RST);
    }

    return ;
}

/*****************************************************************************
 Function Name   : NAS_EMM_IsDeregState
 Description     : �ж��Ƿ���DEREG̬
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2012-10-31  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_IsDeregState( VOS_VOID )
{

    VOS_UINT32                          ulCurEmmStat            = NAS_EMM_NULL;

    ulCurEmmStat = NAS_LMM_PUB_COMP_EMMSTATE(   NAS_EMM_CUR_MAIN_STAT,
                                                NAS_EMM_CUR_SUB_STAT);

    /* ��ǰ״̬ΪRESUME+EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_INDʱ������ǻ��ˣ�
       ��鿴����ǰ״̬������鿴�ָ�ǰ״̬ */
    if (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(  EMM_MS_RESUME,
                                                    EMM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND))
    {
        if ((NAS_LMM_SYS_CHNG_TYPE_REVERSE_RSL == NAS_EMM_GetResumeType())
            || (NAS_LMM_SYS_CHNG_TYPE_REVERSE_HO == NAS_EMM_GetResumeType())
            || (NAS_LMM_SYS_CHNG_TYPE_REVERSE_CCO == NAS_EMM_GetResumeType())
            || (NAS_LMM_SYS_CHNG_TYPE_REVERSE_REDIR == NAS_EMM_GetResumeType()))
        {
            /* �жϹ���ǰ״̬ */
            if (EMM_MS_DEREG == NAS_EMM_GetMsBefSuspend())
            {
                return NAS_EMM_YES;
            }

            return NAS_EMM_NO;
        }
        else
        {
            /* �жϻָ�ǰ״̬ */
            if (EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
            {
                return NAS_EMM_YES;
            }

            return NAS_EMM_NO;
        }
    }

    if (ulCurEmmStat == NAS_LMM_PUB_COMP_EMMSTATE(  EMM_MS_RESUME,
                                                    EMM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND))
    {
        /* �жϻָ�ǰ״̬ */
        if (EMM_MS_DEREG == NAS_EMM_GetMsBefResume())
        {
            return NAS_EMM_YES;
        }

        return NAS_EMM_NO;
    }

    if (EMM_MS_DEREG == NAS_EMM_CUR_MAIN_STAT)
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}
VOS_VOID  NAS_EMM_SendUsimStatusToRrc( LRRC_LNAS_SIM_STATUS_ENUM_UINT32  enSimStatus)
{
    LRRC_LNAS_INFO_STRU                   stNasInfo;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_SendSecuParamToRrc entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SendUsimStatusToRrc_ENUM,LNAS_ENTRY);

    /*����ڴ�*/
    NAS_LMM_MEM_SET(&stNasInfo, 0, sizeof(LRRC_LNAS_INFO_STRU));

    /*��䰲ȫ����: Kasme + UL_NasCount*/
    stNasInfo.bitOpUsimStatus = NAS_EMM_BIT_SLCT;
    stNasInfo.enUsimStatus = enSimStatus;

    /*����RRC_MM_INFO_CHANGE_REQ��Ϣ��RRC*/
    NAS_EMM_SendInfoChangeReqMsg(&stNasInfo);

    return;

}



VOS_VOID  NAS_LMM_ChangeRegRejCauseAvoidInvalidSim
(
    VOS_UINT8        *pucCause
)
{
    VOS_UINT32                          ulRslt     = MMC_LMM_FAIL;
    VOS_UINT32                          i          = 0;
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo = NAS_EMM_NULL_PTR;

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();
    ulRslt     = NAS_LMM_IsRegisteredInHplmn();

    for (i = 0; i < pstPubInfo->stConfCause.ucCauseNum; i++)
    {
        if (pstPubInfo->stConfCause.astAdaptCause[i].ucCnCause == *pucCause)
        {
            if (NAS_EMM_YES == ulRslt)
            {
                NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ChangeRegRejCauseAvoidInvalidSim:HPLMN entered.");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_ChangeRegRejCauseAvoidInvalidSim_ENUM,LNAS_FUNCTION_LABEL1);
                /* ��ǰPLMN��HPLMN/EHPLMN��ʱ��ʹ���û����õ�HPLMNԭ��ֵ */
                NAS_EMM_HandleHplmnRejCauseChange(pucCause, pstPubInfo->stConfCause.astAdaptCause[i].ucHplmnCause);
            }
            else
            {
                NAS_LMM_PUBM_LOG_INFO("NAS_LMM_ChangeRegRejCauseAvoidInvalidSim:NOT HPLMN entered.");
                TLPS_PRINT2LAYER_INFO(NAS_LMM_ChangeRegRejCauseAvoidInvalidSim_ENUM,LNAS_FUNCTION_LABEL2);
                /* ��ȡʧ�ܣ����ߵ�ǰPLMN����HPLMN/EHPLMN��ʱ��ʹ���û����õķ�HPLMNԭ��ֵ */
                NAS_EMM_HandleVplmnRejCauseChange(pucCause, pstPubInfo->stConfCause.astAdaptCause[i].ucNotHplmnCause);
            }
            /* add by yanglei 00307272 for KEY_INFO_REPORT3,2015-08-18,begin */
            NAS_EMM_SndOmLogConfigNwCauseInfo(  pstPubInfo->stConfCause.astAdaptCause[i].ucCnCause,
                                               *pucCause,
                                                ulRslt);
            /* add by yanglei 00307272 for KEY_INFO_REPORT3,2015-08-18,end */
            break;
        }
    }

    /* �����û���Ҫ�޸ĵ�ԭ��ֵ�������κ��޸ķ��� */
    return;
}


VOS_VOID NAS_LMM_AdaptRegRejCau(VOS_UINT8 *pucCause)
{
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo;


    pstPubInfo = NAS_LMM_GetEmmInfoAddr();
#if (VOS_OS_VER != VOS_WIN32)

    /* �ǲ��Կ������������Կ���ֱ����Э�����̣����޸�ԭ��ֵ */
    if (PS_SUCC == LPS_OM_IsTestMode())
    {
        return;
    }
    if(VOS_NULL_PTR != pucCause)
    {
        NAS_MML_SetOriginalRejectCause(*pucCause);
    }
#endif

    /* ���ǲ��Կ�, �������Ӧ����ܾ�ԭ��ֵ���Կ��ش򿪣�����ԭ��ֵ */

    if (NAS_LMM_NULL < pstPubInfo->stConfCause.ucCauseNum)
    {
        /* coverity[var_deref_model] */
        NAS_LMM_ChangeRegRejCauseAvoidInvalidSim(pucCause);
    }

    return;

}




/*PC REPLAY MODIFY BY LEILI BEGIN*/

MMC_LMM_RESULT_ID_ENUM_UINT32 NAS_EMM_GetGulPubInfo
(
    MMC_LMM_INFO_TYPE_ENUM_UINT32    ulInfoType,
    MMC_LMM_PUB_INFO_STRU           *pPubInfo
)
{
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_GetGulPubInfo is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetGulPubInfo_ENUM,LNAS_ENTRY);

    #ifndef __PS_WIN32_RECUR__
    ulRslt = Nas_GetPubInfo (ulInfoType, pPubInfo);

    NAS_LMM_LogPubInfo(ulInfoType, pPubInfo,ulRslt);
    #else
    /*����API��׮����*/
    ulRslt = Stub_Nas_GetPubInfo(ulInfoType, pPubInfo);
    #endif

    return ulRslt;
}
MMC_LMM_RESULT_ID_ENUM_UINT32 NAS_EMM_GetGuInfo
(
    NAS_GUMM_INFO_TYPE_ENUM_UINT32  ulInfoType,
    NAS_GUMM_INFO_STRU *            pstGuInfo
)
{
    MMC_LMM_RESULT_ID_ENUM_UINT32       ulRslt;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_GetGuInfo is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetGuInfo_ENUM,LNAS_ENTRY);

    #ifndef __PS_WIN32_RECUR__
    ulRslt = Nas_GetGuInfo (ulInfoType, pstGuInfo);

    NAS_LMM_LogGuInfo(ulInfoType, pstGuInfo,ulRslt);
    #else
    /*����API��׮����*/
    ulRslt = Stub_Nas_GetGuInfo(ulInfoType, pstGuInfo);
    #endif

    return ulRslt;
}
VOS_VOID NAS_EMM_GetMsNetworkCapability
(
    NAS_MML_MS_NETWORK_CAPACILITY_STRU  *pstMsNetworkCapbility
)
{
    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_GetMsNetworkCapability is entered");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetMsNetworkCapability_ENUM,LNAS_ENTRY);

    #ifndef __PS_WIN32_RECUR__
    NAS_MML_GetMsNetworkCapability (pstMsNetworkCapbility);

    NAS_LMM_LogMsNetworkCapabilityInfo(pstMsNetworkCapbility);

    #else
    /*����API��׮����*/
    Stub_NAS_MML_GetMsNetworkCapability(pstMsNetworkCapbility);
    #endif

    return;
}
VOS_UINT8* NAS_EMM_GetUeIdTmsi(VOS_VOID)
{

    VOS_UINT8               *pucTmsi;
    #ifndef __PS_WIN32_RECUR__
    pucTmsi = NAS_MML_GetUeIdTmsi ();

    NAS_LMM_LogUeIdTmsiInfo (pucTmsi);
    #else
    pucTmsi = Stub_NAS_MML_GetUeIdTmsi();
    #endif
    return pucTmsi;

}


NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8  NAS_EMM_GetLteCsServiceCfg(  VOS_VOID  )
{
    NAS_MML_LTE_CS_SERVICE_CFG_ENUM_UINT8   ucRslt;

    #ifndef __PS_WIN32_RECUR__
    ucRslt = NAS_MML_GetLteCsServiceCfg ();

    NAS_LMM_LogCsServiceCfgInfo(ucRslt);
    #else

    ucRslt = Stub_NAS_MML_GetLteCsServiceCfg();
    #endif
    return ucRslt;
}


NAS_MML_PS_BEARER_CONTEXT_STRU* NAS_EMM_GetPsBearerCtx(VOS_VOID)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU *pstPsBearerCtx;
    #ifndef __PS_WIN32_RECUR__
    pstPsBearerCtx   =  NAS_MML_GetPsBearerCtx();

    NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);

    #else
    pstPsBearerCtx = Stub_NAS_MML_GetPsBearerCtx();

    #endif

    return pstPsBearerCtx;
}


VOS_UINT8  NAS_EMM_GetUeEutranPsDrxLen(  VOS_VOID  )
{
    VOS_UINT8                 ucRslt;
    #ifndef __PS_WIN32_RECUR__
    ucRslt = NAS_MML_GetUeEutranPsDrxLen ();

    NAS_LMM_LogUeEutranPsDrxLenInfo (ucRslt);

    #else
    ucRslt = Stub_NAS_MML_GetUeEutranPsDrxLen();

    #endif

    return ucRslt;

}

VOS_UINT8  NAS_EMM_GetNonDrxTimer(  VOS_VOID  )
{
    VOS_UINT8                 ucRslt;
    #ifndef __PS_WIN32_RECUR__
    ucRslt = NAS_MML_GetNonDrxTimer ();

    NAS_LMM_LogNonDrxTimerInfo (ucRslt);
    #else
    ucRslt = Stub_NAS_MML_GetNonDrxTimer();
    #endif
    return ucRslt;
}


VOS_UINT8  NAS_EMM_GetSplitPgCycleCode(  VOS_VOID  )
{
    VOS_UINT8                 ucRslt;
    #ifndef __PS_WIN32_RECUR__
    ucRslt = NAS_MML_GetSplitPgCycleCode ();

    NAS_LMM_LogDrxSplitPgCycleCodeInfo (ucRslt);
    #else
    ucRslt = Stub_NAS_MML_GetSplitPgCycleCode();
    #endif
    return ucRslt;
}

VOS_UINT8  NAS_EMM_GetSplitOnCcch(  VOS_VOID  )
{
    VOS_UINT8                 ucRslt;

    #ifndef __PS_WIN32_RECUR__
    ucRslt = NAS_MML_GetSplitOnCcch ();

    NAS_LMM_LogDrxSplitOnCcch(ucRslt);

    #else

    ucRslt = Stub_NAS_MML_GetSplitOnCcch();
    #endif

    return ucRslt;
}


VOS_VOID NAS_EMM_FillIEClassMark2(VOS_UINT8  *pClassMark2)
{

    #ifndef __PS_WIN32_RECUR__
    NAS_MML_Fill_IE_ClassMark2(pClassMark2);

    NAS_LMM_LogClassMark2Info(pClassMark2);

    #else

    Stub_NAS_MML_Fill_IE_ClassMark2(pClassMark2);
    #endif
    return;
}

VOS_UINT8  NAS_EMM_GetCsAttachAllowFlg(  VOS_VOID  )
{
    VOS_UINT8                 ucRslt;
    #ifndef __PS_WIN32_RECUR__
    ucRslt = NAS_MML_GetCsAttachAllowFlg ();

    /* coverity[unchecked_value] */
    NAS_LMM_LogCsAttachAllowFlgInfo (ucRslt);
    #else
    ucRslt = Stub_NAS_MML_GetCsAttachAllowFlg();
    #endif
    return ucRslt;
}
VOS_UINT8  NAS_EMM_GetPsAttachAllowFlg(  VOS_VOID  )
{
    VOS_UINT8                 ucRslt;
    #ifndef __PS_WIN32_RECUR__
    ucRslt = NAS_MML_GetPsAttachAllowFlg ();

    NAS_LMM_LogPsAttachAllowFlgInfo (ucRslt);
    #else
    ucRslt = Stub_NAS_MML_GetPsAttachAllowFlg();
    #endif

    return ucRslt;
}


NAS_MML_MS_MODE_ENUM_UINT8  NAS_EMM_GetMsMode(  VOS_VOID  )
{
    NAS_MML_MS_MODE_ENUM_UINT8         ucMsMode;
    #ifndef __PS_WIN32_RECUR__
    ucMsMode = NAS_MML_GetMsMode ();

    /* coverity[unchecked_value] */
    NAS_LMM_LogMsMode (ucMsMode);
    #else

    ucMsMode = Stub_NAS_MML_GetMsMode();
    #endif
    return ucMsMode;
}
MMC_LMM_PLMN_CTRL_ENUM_UINT32  NAS_EMM_PlmnIdIsForbid(MMC_LMM_PLMN_ID_STRU *pstPlmn )
{
    MMC_LMM_PLMN_CTRL_ENUM_UINT32      ulRslt;
    #ifndef __PS_WIN32_RECUR__
    ulRslt = Nas_PlmnIdIsForbid (pstPlmn);

    NAS_LMM_LogPlmnIsForbid (pstPlmn,ulRslt);
    #else

    ulRslt = Stub_Nas_PlmnIdIsForbid(pstPlmn);
    #endif
    return ulRslt;
}


NAS_MML_REG_STATUS_ENUM_UINT8  NAS_EMM_GetPsRegStatus( VOS_VOID)
{
    NAS_MML_REG_STATUS_ENUM_UINT8      ucPsRegStatus;
    #ifndef __PS_WIN32_RECUR__
    ucPsRegStatus = NAS_MML_GetPsRegStatus ();

    /* coverity[unchecked_value] */
    NAS_LMM_LogPsRegStatus (ucPsRegStatus);
    #else
    ucPsRegStatus = Stub_NAS_MML_GetPsRegStatus();
    #endif
    return ucPsRegStatus;
}
NAS_MML_REG_STATUS_ENUM_UINT8  NAS_EMM_GetSimType( VOS_VOID)
{
    NAS_MML_SIM_TYPE_ENUM_UINT8      ucSimType;
    #ifndef __PS_WIN32_RECUR__
    ucSimType = NAS_MML_GetSimType ();

    /* coverity[unchecked_value] */
    NAS_LMM_LogSimType (ucSimType);
    #else
    ucSimType = Stub_NAS_MML_GetSimType();
    #endif
    return ucSimType;
}
VOS_UINT32  NAS_EMM_GetCardIMSI
(
    VOS_UINT8      *pucImsi
)
{
    VOS_UINT32      ulRslt;
    #ifndef __PS_WIN32_RECUR__
    ulRslt = USIMM_GetCardIMSI (pucImsi);

    /* coverity[unchecked_value] */
    NAS_LMM_LogCardIMSIInfo (pucImsi,ulRslt);
    #else
    ulRslt = Stub_USIMM_GetCardIMSI(pucImsi);
    #endif
    return ulRslt;
}
VOS_UINT32  NAS_EMM_IsServiceAvailable
(
    UICC_SERVICES_TYPE_ENUM_UINT32  enService
)
{
    VOS_UINT32      ulRslt;
    #ifndef __PS_WIN32_RECUR__
    ulRslt = USIMM_IsServiceAvailable (enService);
    /*lint -e718*/
    /*lint -e746*/
    /* coverity[unchecked_value] */
    NAS_LMM_LogUsimServiceInfo (enService,ulRslt);
    /*lint +e746*/
    /*lint +e718*/
    #else
    ulRslt = Stub_USIMM_IsServiceAvailable();
    #endif
    return ulRslt;
}
/*PC REPLAY MODIFY BY LEILI END*/


VOS_UINT32  NAS_EMM_IsAnnexP2ConditionSatisfied(VOS_VOID)
{
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsAnnexP2ConditionSatisfied is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsAnnexP2ConditionSatisfied_ENUM,LNAS_ENTRY);

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

    /*1.IMS voice��not available��Ϊavailable
      2.NV Mobility Management for IMS Voice TerminationΪenable
      3.IMS voice over PS session in S1 mode supported��
        IMS voice over PS session supported in Iu mode, but not supported in A/Gb mode
      4.voice domain preference for UTRAN��ΪCS voice only ��
        voice domain preference for E-UTRAN��ΪCS voice only*/
    /* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
    if ((VOS_TRUE == NAS_LMM_GetImsVoiceMMEnableFlg())
        &&((NAS_MML_NW_IMS_VOICE_SUPPORTED == NAS_LMM_GetLteNwImsVoiceSupportFlag())
            ||(NAS_MML_NW_IMS_VOICE_SUPPORTED == NAS_LMM_GetGUNwImsVoiceSupportFlg()))
    /* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
        &&((NAS_EMM_BIT_SLCT == pstPubInfo->bitOpVoiceDomain)
            && (NAS_LMM_VOICE_DOMAIN_CS_ONLY != pstPubInfo->ulVoiceDomain)))
    {

        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}


VOS_UINT32  NAS_EMM_IsAnnexP4ConditionSatisfied(VOS_VOID)
{
    NAS_EMM_PUB_INFO_STRU              *pstPubInfo;

    NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsAnnexP4ConditionSatisfied is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_IsAnnexP4ConditionSatisfied_ENUM,LNAS_ENTRY);

    pstPubInfo = NAS_LMM_GetEmmInfoAddr();

     /*1.IMS voiceΪavailable
       2.NV Mobility Management for IMS Voice TerminationΪenable
       3.IMS voice over PS session in S1 mode supported
       4.voice domain preference for E-UTRAN��ΪCS voice only*/
    if ((MMC_LMM_IMS_VOICE_CAP_AVAILABLE == pstPubInfo->enImsaVoiceCap)
    /* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
        &&(VOS_TRUE == NAS_LMM_GetImsVoiceMMEnableFlg())
        &&(NAS_MML_NW_IMS_VOICE_SUPPORTED == NAS_LMM_GetLteNwImsVoiceSupportFlag())
    /* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
        &&((NAS_EMM_BIT_SLCT == pstPubInfo->bitOpVoiceDomain)
            && (NAS_LMM_VOICE_DOMAIN_CS_ONLY != pstPubInfo->ulVoiceDomain)))
    {

        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}


/* lihong00150010 emergency tau&service begin */
/*****************************************************************************
 Function Name   : NAS_EMM_IsEnterRegLimitService
 Description     : �ж��Ƿ����REG+LIMIT_SERVICE̬
 Input           : pstMsgStru
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2012-10-31  Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_EMM_IsEnterRegLimitService( VOS_VOID )
{
    NAS_MM_NETWORK_ID_STRU             *pstPresentNwInfo = NAS_EMM_NULL_PTR;

    /* ����޿��������REG+LIMIT_SERVICE */
    if (NAS_LMM_SIM_STATUS_UNAVAILABLE == NAS_LMM_GetSimState())
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsEnterRegLimitService:NO CARD");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsEnterRegLimitService_ENUM,LNAS_EMM_NO_CARD);
        return VOS_TRUE;
    }

    /* �������Ч�������REG+LIMIT_SERVICE */
    if (NAS_LMM_SIM_INVALID == NAS_LMM_GetPsSimValidity())
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsEnterRegLimitService:CARD INVALID");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsEnterRegLimitService_ENUM,LNAS_EMM_CARD_INVALID);
        return VOS_TRUE;
    }

    /* ���ע��״̬Ϊ����ע�ᣬ�����REG+LIMIT_SERVICE */
    if (NAS_LMM_REG_STATUS_EMC_REGED == NAS_LMM_GetEmmInfoRegStatus())
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsEnterRegLimitService:EMC REGED");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsEnterRegLimitService_ENUM,LNAS_EMM_EMC_REG);
        return VOS_TRUE;
    }

    pstPresentNwInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);

    /* ��ǰ�����С���Ǳ���С���������REG+LIMIT_SERVICE */
    if (EMMC_EMM_NO_FORBIDDEN != pstPresentNwInfo->ulForbiddenInfo)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsEnterRegLimitService:forbidden");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsEnterRegLimitService_ENUM,LNAS_EMM_FORBIDDEN);
        return VOS_TRUE;
    }

    /* ��ǰ�����С����ANYCELLС���������REG+LIMIT_SERVICE */
    if (EMMC_EMM_CELL_STATUS_ANYCELL == pstPresentNwInfo->ulCellStatus)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_EMM_IsEnterRegLimitService:forbidden");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_IsEnterRegLimitService_ENUM,LNAS_FUNCTION_LABEL1);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_VOID NAS_EMM_TranStateRegNormalServiceOrRegLimitService(VOS_VOID)
{
    if (VOS_TRUE == NAS_EMM_IsEnterRegLimitService())
    {
        NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_LIMITED_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
    else
    {
        NAS_EMM_TAUSER_FSMTranState(    EMM_MS_REG,
                                        EMM_SS_REG_NORMAL_SERVICE,
                                        TI_NAS_EMM_STATE_NO_TIMER);
    }
}
/* lihong00150010 emergency tau&service end */

#if (FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_LMM_SndOmDsdsPreProcMsgInfo
(
    NAS_LMM_DSDS_MSG_TYPE_ENUM_UINT32                 enMsgType,
    VOS_UINT32                                        ulIndex
)
{
    NAS_LMM_DSDS_PREPROC_MSG_INFO_STRU            *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                    ulMsgName = NAS_OM_LOG_DSDS_MSG_PREPROC;

    pstMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(NAS_LMM_DSDS_PREPROC_MSG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SndOmDsdsPreProcMsgInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SndOmDsdsPreProcMsgInfo_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_DSDS_PREPROC_MSG_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = ulMsgName + PS_MSG_ID_DSDS_DEBUG_BASE;
    pstMsg->enMsgType                   = enMsgType;
    pstMsg->ulInputType                 = ulIndex;
    pstMsg->ulBeginMsgTotal             = g_astDsdsInputNotifyMsgNum[ulIndex].ulBeginMsgCnt;
    pstMsg->ulEndMsgTotal               = g_astDsdsInputNotifyMsgNum[ulIndex].ulEndMsgCnt;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_FREE_MSG(pstMsg);

    return;
}



VOS_VOID NAS_LMM_SndOmDsdsSessionMsgInfo
(
    NAS_LMM_DSDS_MSG_TYPE_ENUM_UINT32                 enMsgType,
    MM_SESSION_TYPE_ENUM_UINT32                       enSessionType
)
{
    NAS_LMM_DSDS_SESSION_MSG_INFO_STRU            *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                    ulMsgName = NAS_OM_LOG_DSDS_MSG_SEND;

    pstMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(NAS_LMM_DSDS_SESSION_MSG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SndDsdsSessionMsgInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SndOmDsdsSessionMsgInfo_ENUM,LNAS_NULL_PTR);
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_DSDS_SESSION_MSG_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = ulMsgName + PS_MSG_ID_DSDS_DEBUG_BASE;
    pstMsg->enMsgType                   = enMsgType;
    pstMsg->enOutputSessionType         = enSessionType;
    pstMsg->ulBeginMsgTotal             = g_astDsdsNotifyMsgNum[enSessionType].ulBeginMsgCnt;
    pstMsg->ulEndMsgTotal               = g_astDsdsNotifyMsgNum[enSessionType].ulEndMsgCnt;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_FREE_MSG(pstMsg);

    return;
}



VOS_VOID  NAS_LMM_SendRrcDsdsBeginNotify(LRRC_LNAS_SESSION_TYPE_ENUM_UINT8  ucSessionType)
{
    LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU   *pstRrcBeginNotifyMsg;

    if(PS_FALSE == g_ulDsdsRFSharedFlag)
    {
        /*�����Ƶ�����عرգ��򲻽�������Ĵ���*/
        NAS_EMM_PUBU_LOG_INFO("NAS_LMM_SendRrcDsdsBeginNotify: g_ulDsdsRFSharedFlag=PS_FALSE!!!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_SendRrcDsdsBeginNotify_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    if(LRRC_LNAS_SESSION_TYPE_BUTT <= ucSessionType)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_LMM_SendRrcDsdsBeginNotify: INPUT PARA ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendRrcDsdsBeginNotify_ENUM,LNAS_PARAM_INVALID);
        return;
    }

    /* ����DOPRA��Ϣ */
    pstRrcBeginNotifyMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU));
    if(NAS_EMM_PLMN_NULL_PTR == pstRrcBeginNotifyMsg)
    {
        return;
    }

    NAS_EMM_PUBU_LOG1_INFO("DSDS Protection procedure begin,SessionType = ",ucSessionType);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SendRrcDsdsBeginNotify_ENUM,LNAS_EMM_SESSION_TYPE,ucSessionType);

    /* ����Ϊ0 */
    NAS_LMM_MEM_SET(pstRrcBeginNotifyMsg,0,sizeof(LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU));

    /* ���VOS��Ϣͷ */
    NAS_EMM_SET_RRC_MSG_HEADER((pstRrcBeginNotifyMsg),
                                      NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_BEGIN_SESSION_NOTIFY_STRU));

    /* �����ϢID */
    pstRrcBeginNotifyMsg->enMsgId          = ID_LRRC_LMM_BEGIN_SESSION_NOTIFY;

    /* �����Ϣ�� */
     pstRrcBeginNotifyMsg->enSessionType            = ucSessionType;

    /* ����DOPRA��Ϣ */
    NAS_LMM_SEND_MSG(                   pstRrcBeginNotifyMsg);

    /*������begin��Ϣ�󣬽���Ӧsession type�ļ�����1*/
    g_astDsdsNotifyMsgNum[ucSessionType].ulBeginMsgCnt++;

    /* DSDS������Ϣ��Ϣ�������� */
    NAS_LMM_SndOmDsdsSessionMsgInfo(NAS_LMM_DSDS_MSG_TYPE_BEGIN,ucSessionType);

    return;
}


VOS_VOID  NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_ENUM_UINT8  ucSessionType)
{
    LRRC_LMM_END_SESSION_NOTIFY_STRU   *pstRrcEndNotifyMsg;

    if(PS_FALSE == g_ulDsdsRFSharedFlag)
    {
        /*�����Ƶ�����عرգ��򲻽�������Ĵ���*/
        NAS_EMM_PUBU_LOG_INFO("NAS_LMM_SendRrcDsdsEndNotify: g_ulDsdsRFSharedFlag=PS_SWITCH_OFF!!!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_SendRrcDsdsEndNotify_ENUM,LNAS_FUNCTION_LABEL1);
        return;
    }

    if(LRRC_LNAS_SESSION_TYPE_BUTT <= ucSessionType)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        NAS_EMM_PUBU_LOG_ERR("NAS_LMM_SendRrcDsdsEndNotify: INPUT PARA ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendRrcDsdsEndNotify_ENUM,LNAS_PARAM_INVALID);
        return;
    }

    /*��LNAS���̽����쳣���������������Ϣ�����뿪ʼ��Ϣ������ͬ����˵���Ѿ������˽�����Ϣ�������ظ�����*/
    if(((LRRC_LNAS_SESSION_TYPE_PS_ATTACH <= ucSessionType) && (LRRC_LNAS_SESSION_TYPE_PS_ESM >= ucSessionType))
        && (g_astDsdsNotifyMsgNum[ucSessionType].ulBeginMsgCnt <= g_astDsdsNotifyMsgNum[ucSessionType].ulEndMsgCnt))
    {
        NAS_EMM_PUBU_LOG1_WARN("NAS_LMM_SendRrcDsdsEndNotify: begin=end��session =",ucSessionType);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_SendRrcDsdsEndNotify_ENUM,LNAS_EMM_SESSION_TYPE,ucSessionType);
        /* DSDS������Ϣ��Ϣ�������� */
        NAS_LMM_SndOmDsdsSessionMsgInfo(NAS_LMM_DSDS_MSG_TYPE_END,ucSessionType);
        return;
    }

    /* ����DOPRA��Ϣ */
    pstRrcEndNotifyMsg = (VOS_VOID *) NAS_LMM_ALLOC_MSG(sizeof(LRRC_LMM_END_SESSION_NOTIFY_STRU));
    if(NAS_EMM_PLMN_NULL_PTR == pstRrcEndNotifyMsg)
    {
        return;
    }

    NAS_EMM_PUBU_LOG1_INFO("DSDS Protection procedure end,SessionType = ",ucSessionType);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SendRrcDsdsEndNotify_ENUM,LNAS_FUNCTION_LABEL1,ucSessionType);

    /* ����Ϊ0 */
    NAS_LMM_MEM_SET(pstRrcEndNotifyMsg,0,sizeof(LRRC_LMM_END_SESSION_NOTIFY_STRU));

    /* ���VOS��Ϣͷ */
    NAS_EMM_SET_RRC_MSG_HEADER((pstRrcEndNotifyMsg),
                                      NAS_EMM_GET_MSG_LENGTH_NO_HEADER(LRRC_LMM_END_SESSION_NOTIFY_STRU));

    /* �����ϢID */
    pstRrcEndNotifyMsg->enMsgId          = ID_LRRC_LMM_END_SESSION_NOTIFY;

    /* �����Ϣ�� */
    pstRrcEndNotifyMsg->enSessionType            = ucSessionType;

    /* ����DOPRA��Ϣ */
    NAS_LMM_SEND_MSG(                   pstRrcEndNotifyMsg);

    /*������end��Ϣ���򽫼�����1*/
    /*lint -e661*/
    g_astDsdsNotifyMsgNum[ucSessionType].ulEndMsgCnt++;
    /*lint +e661*/

    /* DSDS������Ϣ��Ϣ�������� */
    NAS_LMM_SndOmDsdsSessionMsgInfo(NAS_LMM_DSDS_MSG_TYPE_END,ucSessionType);

    return;
}
#endif


VOS_VOID NAS_EMM_HandleHplmnRejCauseChange(
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT8                           ucConfigCauseNvim
)
{
    if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == ucConfigCauseNvim)
    {
        if (VOS_TRUE != NAS_MML_GetHplmnPsRejChangeTo17Flg())
        {
            /* ����滻��ԭ��ֵΪ#17�����滻�������Ѿ��ﵽ���ޣ������滻 */
            return;
        }

        /* ������+1 */
        NAS_MML_IncHplmnPsRejCauseChangedCounter();
    }

    /* ����滻���ԭ��ֵ��#17�����滻���ԭ��ֵΪ#17���滻����δ�ﵽ���ޣ����滻 */
    *pucRcvMsg = ucConfigCauseNvim;
}
VOS_VOID NAS_EMM_HandleVplmnRejCauseChange(
    VOS_UINT8                          *pucRcvMsg,
    VOS_UINT8                           ucConfigCauseNvim
)
{
    if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE == ucConfigCauseNvim)
    {
        if (VOS_TRUE != NAS_MML_GetVplmnPsRejChangeTo17Flg())
        {
            /* ����滻��ԭ��ֵΪ#17�����滻�������Ѿ��ﵽ���ޣ������滻 */
            return;
        }

        /* ������+1 */
        NAS_MML_IncVplmnPsRejCauseChangedCounter();
    }

    /* ����滻���ԭ��ֵ��#17�����滻���ԭ��ֵΪ#17���滻����δ�ﵽ���ޣ����滻 */
    *pucRcvMsg = ucConfigCauseNvim;
}
VOS_VOID NAS_EMM_ResetRejCauseChangedCounter(VOS_VOID)
{
    NAS_MML_ResetHplmnPsRejCauseChangedCounter();
    NAS_MML_ResetVplmnPsRejCauseChangedCounter();
}


VOS_UINT32 NAS_EMM_IsNeedIgnoreHplmnAuthRej(VOS_VOID)
{
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU  *pstAuthRejInfo = NAS_EMM_NULL_PTR;

    pstAuthRejInfo = NAS_MML_GetAuthRejInfo();

    if (NAS_EMM_NULL_PTR == pstAuthRejInfo)
    {
        return NAS_EMM_NO;
    }

    /* VPLMN��,���ܴ��Һ���auth rej��Ϣ����δ�ﵽ���ֵ������Ҫ���� */
    if (   (NAS_EMM_YES == NAS_LMM_IsRegisteredInHplmn())
        && (VOS_TRUE    == pstAuthRejInfo->ucIgnoreAuthRejFlg)
        && (pstAuthRejInfo->ucHplmnPsAuthRejCounter < pstAuthRejInfo->ucMaxAuthRejNo))
    {
        pstAuthRejInfo->ucHplmnPsAuthRejCounter++;
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}
VOS_VOID NAS_EMM_ResetHplmnAuthRejCout(VOS_VOID)
{
    NAS_MML_IGNORE_AUTH_REJ_INFO_STRU  *pstAuthRejInfo = NAS_EMM_NULL_PTR;

    pstAuthRejInfo = NAS_MML_GetAuthRejInfo();

    if (pstAuthRejInfo)
    {
        pstAuthRejInfo->ucHplmnPsAuthRejCounter = 0;
    }
}


VOS_VOID NAS_EMM_GetCurrentCampInfo
(
    ESM_EMM_PLMN_ID_STRU *pstCurrentCampInfo
)
{
    NAS_MM_NETWORK_ID_STRU             *pstAreaInfo;

    NAS_LMM_EMMC_LOG_INFO("NAS_EMM_GetCurrentCampInfo enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetCurrentCampInfo_ENUM,LNAS_ENTRY);

    pstAreaInfo = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PRESENT_NET_ID);

    NAS_LMM_MEM_CPY(pstCurrentCampInfo,
                    &(pstAreaInfo->stPlmnId),
                    sizeof(ESM_EMM_PLMN_ID_STRU));

    return;
}

VOS_VOID NAS_EMM_GetEplmnList
(
    NAS_ESM_PLMN_LIST_STRU *pstEplmnList
)
{

    NAS_LMM_EMMC_LOG_INFO("NAS_EMM_GetEplmnList enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetEplmnList_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_CPY(pstEplmnList,
                    NAS_EMMC_GetEplmnListAddr(),
                    sizeof(MMC_LMM_EPLMN_STRU));

    return ;
}

VOS_UINT32 NAS_EMM_GetNasRelease(VOS_VOID)
{

    NAS_LMM_EMMC_LOG_INFO("NAS_EMM_GetNasRelease enter");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_GetNasRelease_ENUM,LNAS_ENTRY);

    return NAS_LMM_GetNasRelease();
}


VOS_VOID NAS_EMM_SndOmLogUeIdInfo(VOS_VOID)
{
    NAS_LMM_OM_LOG_UE_ID_INFO_STRU      *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_LOG_UE_ID_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_UE_ID_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMMC_SndOmLogForbPlmnInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndOmLogUeIdInfo_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET(pstMsg, 0, sizeof(NAS_LMM_OM_LOG_UE_ID_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_UE_ID_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = ID_NAS_LMM_OM_LOG_UE_ID_INFO;
    NAS_LMM_MEM_CPY(&pstMsg->stMmUeId, &g_stEmmInfo.stMmUeId, sizeof(NAS_LMM_UEID_STRU));
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
}

VOS_VOID NAS_EMM_SndOmLogEpsLocInfo(VOS_VOID)
{
    NAS_LMM_OM_LOG_EPS_LOC_INFO_STRU          *pstMsg = VOS_NULL_PTR;
    NAS_LMM_UEID_STRU                         *pstUeId;
    NAS_MM_NETWORK_ID_STRU                    *pstNetId;

    pstMsg = (NAS_LMM_OM_LOG_EPS_LOC_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_EPS_LOC_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMM_SndOmLogEpsLocInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndOmLogEpsLocInfo_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET(pstMsg, 0, sizeof(NAS_LMM_OM_LOG_EPS_LOC_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_EPS_LOC_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName   = ID_NAS_LMM_OM_LOG_EPS_LOC_INFO;
    pstMsg->enUpdateState           = NAS_EMM_UPDATE_STAE;

    pstUeId                         = NAS_LMM_GetEmmInfoUeidAddr();
    pstNetId                        = NAS_LMM_GetEmmInfoNetInfoLastRegNetAddr();
    pstMsg->bitOpGuti               = pstUeId->bitOpGuti;
    pstMsg->bitOpTai                = NAS_EMM_GetLVRTaiOpBit();
    pstMsg->bitOpUpState            = NAS_NVIM_BIT_SLCT;

    NAS_LMM_MEM_CPY(                &(pstMsg->stGuti),
                                    &(pstUeId->stGuti),
                                    sizeof(NAS_LMM_GUTI_STRU));


    NAS_LMM_MEM_CPY(                &(pstMsg->stLastRegTai.stPlmnId),
                                    &(pstNetId->stPlmnId),
                                    sizeof(NAS_MM_PLMN_ID_STRU));

    NAS_LMM_MEM_CPY(                &(pstMsg->stLastRegTai.stTac),
                                    &(pstNetId->stTac),
                                    sizeof(NAS_MM_TAC_STRU));
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
}

VOS_VOID NAS_EMM_SndOmLogEpsSecContextInfo(VOS_VOID)
{
    NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO_STRU                *pstMsg = VOS_NULL_PTR;
    NAS_LMM_SECU_CONTEXT_STRU                               *pstCurSecuCntxt = VOS_NULL_PTR;
    NAS_LMM_SECU_CONTEXT_STRU                               *pstNewMappedSecuCntxt = VOS_NULL_PTR;
    NAS_LMM_SECU_CONTEXT_STRU                               *pstNewNativeCurSecuCntxt = VOS_NULL_PTR;
    NAS_LMM_SECU_CONTEXT_STRU                               *pstNonCurNativeSecuCntxt = VOS_NULL_PTR;
    NAS_LMM_SECU_KEY_STRU                                   *pstCurNasKey = VOS_NULL_PTR;
    NAS_GUMM_UMTS_CONTEXT_STRU                              *pstUmtsSecuContext = VOS_NULL_PTR;
    NAS_MM_UE_NET_CAP_STRU                                  *pstUeNetCap = VOS_NULL_PTR;
    NAS_MM_MS_NET_CAP_STRU                                  *pstMsNetCap = VOS_NULL_PTR;



    pstMsg = (NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMM_SndOmLogEpsSecContextInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndOmLogEpsSecContextInfo_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET(pstMsg, 0, sizeof(NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO_STRU));


    /*��ȡ��ǰ��ȫ������*/
    pstCurSecuCntxt                     = NAS_EMM_SecuGetCurCntxtAddr();
    pstNewMappedSecuCntxt               = NAS_EMM_GetSecuNewMappedCntxtAddr();
    pstNewNativeCurSecuCntxt            = NAS_EMM_GetSecuNewNativeCntxtAddr();
    pstNonCurNativeSecuCntxt            = NAS_EMM_GetSecuNonCurNativeCntxtAddr();
    pstCurNasKey                        = NAS_EMM_GetSecuCurNasKeyAddr();
    pstUmtsSecuContext                  = NAS_EMM_GetUmtsSecuContextAddr();
    pstUeNetCap                         = NAS_LMM_GetEmmInfoSecuParaUeNetCapAddr();
    pstMsNetCap                         = NAS_LMM_GetEmmInfoMsNetCapAddr();

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO;
    NAS_LMM_MEM_CPY(&pstMsg->stCurSecContext, pstCurSecuCntxt, sizeof(NAS_LMM_SECU_CONTEXT_STRU));
    NAS_LMM_MEM_CPY(&pstMsg->stNewMappedSecuContext, pstNewMappedSecuCntxt, sizeof(NAS_LMM_SECU_CONTEXT_STRU));
    NAS_LMM_MEM_CPY(&pstMsg->stNewNativeSecuContext, pstNewNativeCurSecuCntxt, sizeof(NAS_LMM_SECU_CONTEXT_STRU));
    NAS_LMM_MEM_CPY(&pstMsg->stNonCurNativeSecuContext, pstNonCurNativeSecuCntxt, sizeof(NAS_LMM_SECU_CONTEXT_STRU));
    NAS_LMM_MEM_CPY(&pstMsg->stTempNasKey, pstCurNasKey, sizeof(NAS_LMM_SECU_KEY_STRU));
    NAS_LMM_MEM_CPY(&pstMsg->stUmtsSecuContext, pstUmtsSecuContext, sizeof(NAS_GUMM_UMTS_CONTEXT_STRU));
    NAS_LMM_MEM_CPY(&pstMsg->stUeNetCap, pstUeNetCap, sizeof(NAS_MM_UE_NET_CAP_STRU));
    NAS_LMM_MEM_CPY(&pstMsg->stMsNetCap, pstMsNetCap, sizeof(NAS_MM_MS_NET_CAP_STRU));

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
}
VOS_VOID NAS_EMM_SndOmLogUeImportantCapabilityInfo(VOS_VOID)
{
    NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY_INFO_STRU      *pstMsg          = VOS_NULL_PTR;
    NAS_EMM_PUB_INFO_STRU                 *pstPubInfo      = VOS_NULL_PTR;

    pstPubInfo  = NAS_LMM_GetEmmInfoAddr();

    pstMsg = (NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMM_SndOmLogUeImportantCapabilityInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndOmLogUeImportantCapabilityInfo_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET(pstMsg, 0, sizeof(NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName = ID_NAS_LMM_OM_LOG_UE_IMPORTANT_CAPABILITY;
    pstMsg->ulVoiceDomain = pstPubInfo->ulVoiceDomain;
    pstMsg->enUeCenter = pstPubInfo->ulUsageSetting;
    pstMsg->ulNasRelease = pstPubInfo->ulNasRelease;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
    NAS_LMM_MEM_CPY(&pstMsg->stRrcNasAc, &gstRrcNasAc, sizeof(LRRC_NAS_AC_CLASS_STRU));
    /* mod by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */
    NAS_LMM_MEM_CPY(&pstMsg->stSupCodecList, &pstPubInfo->stSupCodecList, sizeof(NAS_LMM_CODEC_LIST_STRU));
    NAS_LMM_MEM_CPY(&pstMsg->stConfCause, &pstPubInfo->stConfCause, sizeof(LNAS_LMM_CONFIG_NWCAUSE_STRU));
    NAS_LMM_MEM_CPY(&pstMsg->stUeNetCap, &pstPubInfo->stUeNetCap, sizeof(NAS_MM_UE_NET_CAP_STRU));
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
}

VOS_VOID NAS_EMM_SndOmLogConfigNwCauseInfo
(
    VOS_UINT8                           ucCnCause,
    VOS_UINT8                           ucModifiedCnCause,
    VOS_UINT32                          ucIsHplmn
)
{
    NAS_LMM_OM_LOG_CONFIG_NW_CAUSE_INFO_STRU *pstMsg          = VOS_NULL_PTR;
    NAS_EMM_PUB_INFO_STRU                    *pstPubInfo      = VOS_NULL_PTR;

    pstPubInfo  = NAS_LMM_GetEmmInfoAddr();

    pstMsg = (NAS_LMM_OM_LOG_CONFIG_NW_CAUSE_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_CONFIG_NW_CAUSE_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_EMMC_LOG_ERR("NAS_EMM_SndOmLogConfigNwCauseInfo: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndOmLogConfigNwCauseInfo_ENUM,LNAS_NULL_PTR);
        return;
    }

    NAS_LMM_MEM_SET(pstMsg, 0, sizeof(NAS_LMM_OM_LOG_CONFIG_NW_CAUSE_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_CONFIG_NW_CAUSE_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = ID_NAS_LMM_OM_LOG_NW_CAUSE_CHANGE_INFO;
    pstMsg->ucCnCause                   = ucCnCause;
    pstMsg->ucModifiedCnCause           = ucModifiedCnCause;
    pstMsg->ucIsHplmn                   = ucIsHplmn;
    pstMsg->ucHplmnPsRejChangeTo17Flg   = NAS_MML_GetHplmnPsRejChangeTo17Flg();
    pstMsg->ucModifiedCnCause           = NAS_MML_GetVplmnPsRejChangeTo17Flg();
    NAS_LMM_MEM_CPY(&pstMsg->stConfCause, &pstPubInfo->stConfCause, sizeof(LNAS_LMM_CONFIG_NWCAUSE_STRU));

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}



VOS_UINT32  NAS_LMM_LteNoSubscribeIsRegisteredInHplmn(NAS_EMM_PLMN_ID_STRU  *pstPlmn)
{
    NAS_MM_PLMN_LIST_STRU               stEHplmnList    = {0};
    VOS_UINT32                          ulRslt          = MMC_LMM_FAIL;
    MMC_LMM_PUB_INFO_STRU               stPubInfo;
    NAS_EMM_PLMN_ID_STRU               *pstCurentPlmn   = VOS_NULL_PTR;

    pstCurentPlmn = pstPlmn;

    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_LteNoSubscribeIsRegisteredInHplmn is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_LteNoSubscribeIsRegisteredInHplmn_ENUM,LNAS_ENTRY);

    NAS_LMM_MEM_SET(&stPubInfo,0,sizeof(MMC_LMM_PUB_INFO_STRU));
    /* ���EHPLMN��ȡ�ɹ����Ҹ�����Ϊ0�����жϵ�ǰPLMN�Ƿ���EHPLMN�б��У����
       ���ڣ�����ע����HPLMN�ϣ��������ע�ᵽRPLMN�� */
    ulRslt = NAS_EMM_GetGulPubInfo(MMC_LMM_EHPLMN, &stPubInfo);

    if ((MMC_LMM_SUCC == ulRslt) && (stPubInfo.u.stEHplmnList.ulPlmnNum > 0))
    {
        NAS_LMM_MEM_CPY (   &stEHplmnList,
                            &stPubInfo.u.stEHplmnList,
                            sizeof(MMC_LMM_PLMN_LIST_STRU));

        if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_PlmnIDMatchHplmnList(pstCurentPlmn, &stEHplmnList))
        {
            return NAS_EMM_YES;
        }

        return NAS_EMM_NO;
    }

    /* ���EHPLMN��Ч�����жϵ�ǰPLMN��HPLMN�Ƿ���ͬ�������ͬ������ע����HPLMN
       �ϣ��������ע�ᵽRPLMN�� */
    ulRslt = NAS_EMM_GetGulPubInfo(MMC_LMM_HPLMN, &stPubInfo);
    if (MMC_LMM_SUCC != ulRslt)
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_LteNoSubscribeIsRegisteredInHplmn:Hplmn cannot be got!");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_LteNoSubscribeIsRegisteredInHplmn_ENUM,LNAS_FUNCTION_LABEL1);
        return NAS_EMM_NO;
    }

    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_HplmnMatch((NAS_MM_PLMN_ID_STRU *)(&stPubInfo.u.stHplmn), pstCurentPlmn))
    {
        return NAS_EMM_YES;
    }

    return NAS_EMM_NO;
}


VOS_UINT32  NAS_LMM_LteNoSubscribeAtLeastHaveOneHplmn(
                    MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU  *pstLteNoSubsPLmnList)
{
    VOS_UINT32 i = 0;

    for(i = 0; i < pstLteNoSubsPLmnList->ulPlmnNum; i++)
    {
        if(NAS_EMM_YES == NAS_LMM_LteNoSubscribeIsRegisteredInHplmn(
                        (NAS_EMM_PLMN_ID_STRU*)&pstLteNoSubsPLmnList->astPlmnId[i]))
        {
            /*����ҵ���һ��plmn��EHPLMN�б��У��򷵻�YES*/
            return NAS_EMM_YES;
        }
    }

    /*�����û���ҵ����򷵻�NO*/
    return NAS_EMM_NO;
}


VOS_UINT32  NAS_LMM_SendMmcEutranNotAllowNotify(
                                            VOS_UINT8  ucNetWorkTriggerFlag,
                                            VOS_UINT32 ulTimerLen,
                                            MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU  *pstLteNoSubsPLmnList)
{
    LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU           *pstMmcEutranNotAllowMsg    = NAS_EMM_NULL_PTR;
    VOS_UINT32                                      ulSendResult;

    NAS_LMM_PUBM_LOG_INFO( "NAS_LMM_SendMmcEutranNotAllowNotify: enter");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_SendMmcEutranNotAllowNotify_ENUM,LNAS_ENTRY);

    /* ����MMC�ڲ���Ϣ */
    pstMmcEutranNotAllowMsg = (VOS_VOID *)NAS_LMM_GetLmmMmcMsgBuf(sizeof(LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU));

    if(NAS_EMM_NULL_PTR == pstMmcEutranNotAllowMsg)
    {
        NAS_LMM_PUBM_LOG_ERR( "NAS_LMM_SendMmcEutranNotAllowNotify: MSG ALLOC ERR !!");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SendMmcEutranNotAllowNotify_ENUM,LNAS_NULL_PTR);
        ulSendResult = NAS_EMM_SEND_MMC_ERR;
        return ulSendResult;
    }

    /*lint -e960*/
    NAS_LMM_MEM_SET(pstMmcEutranNotAllowMsg, 0, sizeof(LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU));

    /* ��дID_LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY ��DOPRA��Ϣͷ */
    EMM_PUBU_COMP_MMC_MSG_HEADER(pstMmcEutranNotAllowMsg,
            sizeof(LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY_STRU) - EMM_LEN_VOS_MSG_HEADER);
    /*lint +e960*/

    /* ��дID_LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY ����ϢID��ʶ */
    pstMmcEutranNotAllowMsg->ulMsgId = ID_LMM_MMC_EUTRAN_NOT_ALLOW_NOTIFY;
    pstMmcEutranNotAllowMsg->ulOpId = 0;
    pstMmcEutranNotAllowMsg->ucPlmnNum = (VOS_UINT8)pstLteNoSubsPLmnList->ulPlmnNum;
    pstMmcEutranNotAllowMsg->ulTimerLen = ulTimerLen;
    pstMmcEutranNotAllowMsg->ucNetWorkTriggerFlag = ucNetWorkTriggerFlag;
    NAS_LMM_MEM_CPY(&(pstMmcEutranNotAllowMsg->astPlmnIdList[0]),
                    &(pstLteNoSubsPLmnList->astPlmnId[0]),
                     sizeof(MMC_LMM_PLMN_ID_STRU)*(pstLteNoSubsPLmnList->ulPlmnNum));

    /* ������Ϣ */
    NAS_LMM_SendLmmMmcMsg(pstMmcEutranNotAllowMsg);

    ulSendResult = NAS_EMM_SEND_MMC_OK;

    return ulSendResult;
}


VOS_VOID  NAS_LMM_LteNoSubscribeWithExtCauseHandle(
                               MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU  *pstLteNoSubsPLmnList)
{
    VOS_UINT32              ulTimerLen;

    NAS_LMM_PUBM_LOG_INFO( "NAS_LMM_LteNoSubscribeWithExtCauseHandle: enter");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_LteNoSubscribeWithExtCauseHandle_ENUM,LNAS_ENTRY);

    if(NAS_EMM_YES == NAS_LMM_LteNoSubscribeAtLeastHaveOneHplmn(pstLteNoSubsPLmnList))
    {
        /*HPLMN*/
        ulTimerLen = NAS_EMM_GetLteNoSubscribeNvConfigPublishmentTimerHplmnLen();
    }
    else
    {
        /*VPLMN*/
        ulTimerLen = NAS_EMM_GetLteNoSubscribeNvConfigPublishmentTimerVplmnLen();
    }

    /*����ʱ�����8Сʱ*/
    if(ulTimerLen > NAS_MAX_EXT_PUBLISHMENT_TIMER_LEN)
    {
        ulTimerLen = NAS_MAX_EXT_PUBLISHMENT_TIMER_LEN;
    }

    ( VOS_VOID )NAS_LMM_SendMmcEutranNotAllowNotify(NAS_LMM_WITH_EXT_CAUSE, ulTimerLen, pstLteNoSubsPLmnList);

    return;
}
VOS_VOID  NAS_LMM_LteNoSubscribeWithOutExtCauseHandle(
                        MMC_LMM_LTE_NO_SUBSCRIBE_PLMN_LIST_STRU  *pstLteNoSubsPLmnList)
{
    /*����ǲ��Կ�����ֱ���˳�*/
    if(PS_SUCC == LPS_OM_IsTestMode())
    {
        return;
    }

    /*�ǲ��Կ�*/
    if(NAS_EMM_YES == NAS_LMM_LteNoSubscribeAtLeastHaveOneHplmn(pstLteNoSubsPLmnList))
    {
        NAS_LMM_PUBM_LOG_INFO( "NAS_LMM_LteNoSubscribeWithOutExtCauseHandle: Hplmn");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_LteNoSubscribeWithOutExtCauseHandle_ENUM,LNAS_FUNCTION_LABEL1);
        /*Hplmn*/
        /*Hplmn����NV�Ǵ򿪵ģ�����û����L����ע��ɹ���*/
        if((PS_TRUE == NAS_EMM_GetLteNoSubscribeNvConfigHplmnSwitch())
            && (NAS_LMM_NO_REG_SUCC_ON_LTE == NAS_EMM_GetLteNoSubscribeLteRegFlag()))
        {
            ( VOS_VOID )NAS_LMM_SendMmcEutranNotAllowNotify(
                                            NAS_LMM_WITHOUT_EXT_CAUSE,
                                            NAS_EMM_GetLteNoSubscribeNvConfigPublishmentTimerHplmnLen(),
                                            pstLteNoSubsPLmnList);

            #if (FEATURE_ON == FEATURE_PTM)
            NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_LTE_NO_SUBSCRIBE);
            #endif
        }
    }
    else
    {
        NAS_LMM_PUBM_LOG_INFO( "NAS_LMM_LteNoSubscribeWithOutExtCauseHandle: Vplmn");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_LteNoSubscribeWithOutExtCauseHandle_ENUM,LNAS_FUNCTION_LABEL2);
        /*Vplmn*/
        /*Vplmn����NV�Ǵ򿪵�*/
        if(PS_TRUE == NAS_EMM_GetLteNoSubscribeNvConfigVplmnSwitch())
        {
            ( VOS_VOID )NAS_LMM_SendMmcEutranNotAllowNotify(
                                            NAS_LMM_WITHOUT_EXT_CAUSE,
                                            NAS_EMM_GetLteNoSubscribeNvConfigPublishmentTimerVplmnLen(),
                                            pstLteNoSubsPLmnList);

            #if (FEATURE_ON == FEATURE_PTM)
            NAS_EMM_ImprovePerformceeErrReport(EMM_OM_ERRLOG_IMPROVEMENT_TYPE_LTE_NO_SUBSCRIBE);
            #endif
        }

    }

    return;
}

VOS_VOID  NAS_LMM_ReadNvLmmSwitchPara(VOS_VOID )
{
    LNAS_NV_SWITCH_PARA_STRU              stNvSwitchPara;
    VOS_UINT32                            ulRslt      = NAS_LMM_NVIM_FAIL;
    VOS_UINT16                            usDataLen   = 0;

    NAS_LMM_MEM_SET(&stNvSwitchPara, 0, sizeof(LNAS_NV_SWITCH_PARA_STRU));

    /* ��NV */
    usDataLen = sizeof(LNAS_NV_SWITCH_PARA_STRU);
    ulRslt = NAS_LMM_NvimRead(EN_NV_ID_LNAS_SWITCH_PARA,
                              (VOS_VOID *)&(stNvSwitchPara),
                              &usDataLen);

    if(NAS_LMM_NVIM_OK != ulRslt)
    {
        /* ��NVʧ�������Ŀ�������������ӦNV����Ĭ��ֵ��ʼ�� */
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_ReadNvLmmSwitchPara: read NV Fail.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_ReadNvLmmSwitchPara_ENUM,LNAS_FAIL);
    }

    g_aulNasFunFlg[0]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag01)));
    g_aulNasFunFlg[1]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag02)));
    g_aulNasFunFlg[2]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag03)));
    g_aulNasFunFlg[3]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag04)));
    g_aulNasFunFlg[4]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag05)));
    g_aulNasFunFlg[5]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag06)));
    g_aulNasFunFlg[6]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag07)));
    g_aulNasFunFlg[7]     = *((VOS_UINT32 * )(&(stNvSwitchPara.stNasFunFlag08)));
    /* NV��ȡʱҪ��˳���,��Ҫ���ִ��� */
    /* OM��ά�ɲ���ƿ��� */
    NAS_EMM_GetOmSwitchKeyInfoFlag()    = LNAS_NV_GET_NAS_FUN_FLAG(0, LNAS_NV_GET_KEY_INFO_FLAG_BIT);
    NAS_EMM_GetOmSwitchKeyInfoFlag()    = (0 != NAS_EMM_GetOmSwitchKeyInfoFlag()) ? NAS_EMM_YES : NAS_EMM_NO;
    NAS_EMM_GetOmSwitchKeyEventFlag()   = LNAS_NV_GET_NAS_FUN_FLAG(0, LNAS_NV_GET_KEY_EVENT_FLAG_BIT);
    NAS_EMM_GetOmSwitchKeyEventFlag()   = (0 != NAS_EMM_GetOmSwitchKeyEventFlag()) ? NAS_EMM_YES : NAS_EMM_NO;
    NAS_EMM_GetOmSwitchApiFlag()        = LNAS_NV_GET_NAS_FUN_FLAG(0, LNAS_NV_GET_API_FLAG_BIT);
    NAS_EMM_GetOmSwitchApiFlag()        = (0 != NAS_EMM_GetOmSwitchApiFlag()) ? NAS_EMM_YES : NAS_EMM_NO;
    NAS_EMM_GetOmSwitchSuccRatioFlag()  = LNAS_NV_GET_NAS_FUN_FLAG(0, LNAS_NV_GET_SUCC_RATIO_FLAG_BIT);
    NAS_EMM_GetOmSwitchSuccRatioFlag()  = (0 != NAS_EMM_GetOmSwitchSuccRatioFlag()) ? NAS_EMM_YES : NAS_EMM_NO;
    NAS_EMM_GetOmSwitchDelayFlag()      = LNAS_NV_GET_NAS_FUN_FLAG(0, LNAS_NV_GET_DELAY_FLAG_BIT);
    NAS_EMM_GetOmSwitchDelayFlag()      = (0 != NAS_EMM_GetOmSwitchDelayFlag()) ? NAS_EMM_YES : NAS_EMM_NO;

    /* Gradual Forb�������»� */
    NAS_LMM_GradualForbParaInit(stNvSwitchPara.stGradualForbPara);
    return;
}
VOS_VOID  NAS_EMM_SndEsmClearAllClBearerNotify(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU           *pstEsmMsg;

    /* ����DOPRA��Ϣ */
    pstEsmMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(sizeof(EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU));

    if (NAS_LMM_NULL_PTR == pstEsmMsg)
    {
        return;
    }

    /* ��� */
    NAS_LMM_MEM_SET(pstEsmMsg,0,sizeof(EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU));

    /* ���VOS��Ϣͷ */
    EMM_PUBU_COMP_ESM_MSG_HEADER((pstEsmMsg),     \
                                       NAS_EMM_GET_MSG_LENGTH_NO_HEADER(EMM_ESM_CLEAR_CL_BEARER_NOTIFY_STRU));

    /* �����ϢID */
    pstEsmMsg->ulMsgId                 = ID_EMM_ESM_CLEAR_CL_BEARER_NOTIFY;

    /* ����DOPRA��Ϣ */
    NAS_LMM_SEND_MSG(pstEsmMsg);
#endif
    return;
}
/* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, begin */
/*****************************************************************************
 Function Name   : NAS_LMM_SetVoiceDomain
 Description     : ����VOICE DOMAIN�����ϱ�UE����
 Input           : MMC_LMM_VOICE_DOMAIN_ENUM_UINT32     enVoiceDomain
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SetVoiceDomain(MMC_LMM_VOICE_DOMAIN_ENUM_UINT32     enVoiceDomain )
{
    NAS_LMM_SetEmmInfoVoiceDomain(enVoiceDomain);
    NAS_EMM_SndOmLogUeImportantCapabilityInfo();

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_GetImsVoiceMMEnableFlg
 Description     : ��ȡIms Voice �ƶ��Թ����Ƿ�򿪱�־���ϱ�
 Input           : None
 Output          : None
 Return          : VOS_UINT8
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LMM_GetImsVoiceMMEnableFlg( VOS_VOID )
{
    VOS_UINT8                           ucRslt;

    ucRslt = NAS_MML_GetImsVoiceMMEnableFlg();
    NAS_LMM_SndOmLogImsVoiceMMEnableFlgInfo();

    return ucRslt;
}

/*****************************************************************************
 Function Name   : NAS_LMM_SndOmLogImsVoiceMMEnableFlgInfo
 Description     : �ϱ�Ims Voice �ƶ��Թ����Ƿ�򿪱�־
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmLogImsVoiceMMEnableFlgInfo( VOS_VOID )
{
    NAS_LMM_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_STRU       *pstMsg          = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET(pstMsg, 0, sizeof(NAS_LMM_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = LNAS_OM_LOG_IMS_VOICE_MM_ENABLE_FLAG_INFO_IND;
    pstMsg->ucImsVoiceMMEnable          = NAS_MML_GetImsVoiceMMEnableFlg();
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_GetLteNwImsVoiceSupportFlag
 Description     : ��ȡEPS�����IMS Voice ֧����Ϣ���ϱ�
 Input           : None
 Output          : None
 Return          : NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8  NAS_LMM_GetLteNwImsVoiceSupportFlag( VOS_VOID )
{
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 ucRslt;

    ucRslt = NAS_MML_GetLteNwImsVoiceSupportFlg();
    NAS_LMM_SndOmLogLteNwImsVoiceSupportFlagInfo();

    return ucRslt;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmLogLteNwImsVoiceSupportFlagInfo
 Description     : �ϱ�EPS�����IMS Voice ֧����Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmLogLteNwImsVoiceSupportFlagInfo( VOS_VOID )
{
    NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU                    *pstMsg          = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET(pstMsg, 0, sizeof(NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = LNAS_OM_LOG_LTE_NW_IMS_VOICE_CAP_INFO_IND;
    pstMsg->enNwImsVoCap                = NAS_MML_GetLteNwImsVoiceSupportFlg();
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_GeGUNwImsVoiceSupportFlg
 Description     : ��ȡPS������Ims Voice ֧���������ϱ�
 Input           : None
 Output          : None
 Return          : NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8  NAS_LMM_GetGUNwImsVoiceSupportFlg( VOS_VOID )
{
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 ucRslt;

    ucRslt = NAS_MML_GetGUNwImsVoiceSupportFlg();
    NAS_LMM_SndOmLogGUNwImsVoiceSupportFlagInfo();

    return ucRslt;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmLogGUNwImsVoiceSupportFlagInfo
 Description     : �ϱ�PS�����IMS Voice ֧����Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmLogGUNwImsVoiceSupportFlagInfo( VOS_VOID )
{
    NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU                    *pstMsg          = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET(pstMsg, 0, sizeof(NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_NW_IMS_VOICE_CAP_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = LNAS_OM_LOG_GU_NW_IMS_VOICE_CAP_INFO_IND;
    pstMsg->enNwImsVoCap                = NAS_MML_GetGUNwImsVoiceSupportFlg();
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_GetRoamingRejectNoRetryFlg
 Description     : ��ȡ�Ƿ����reject #17�Ķ��Ƶı�ʶ���ϱ�
 Input           : VOS_UINT8 ucCause
 Output          : None
 Return          : VOS_UINT8
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LMM_GetRoamingRejectNoRetryFlg( VOS_UINT8 ucCause )
{
    VOS_UINT8                           ucRslt;

    ucRslt = NAS_MML_IsRoamingRejectNoRetryFlgActived(ucCause);
    NAS_LMM_SndOmLogRoamingRejectNoRetryFlgInfo(ucCause);

    return ucRslt;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SndOmLogRoamingRejectNoRetryFlgInfo
 Description     : �ϱ��Ƿ����reject #17�Ķ��Ƶı�ʶ��Ϣ
 Input           : VOS_UINT8 ucCause
 Output          : None
 Return          : VOS_VOID
 History         :
    1.    yanglei 00307272      2015-07-28  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LMM_SndOmLogRoamingRejectNoRetryFlgInfo( VOS_UINT8 ucCause )
{
    NAS_LMM_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_STRU         *pstMsg          = VOS_NULL_PTR;

    pstMsg = (NAS_LMM_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_STRU *)NAS_LMM_MEM_ALLOC(sizeof(NAS_LMM_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    NAS_LMM_MEM_SET(pstMsg, 0, sizeof(NAS_LMM_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_STRU));

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_LMM_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_STRU) - 20;
    pstMsg->stMsgHeader.ulMsgName       = LNAS_OM_LOG_ROAMING_REJECT_NO_RETRY_FLG_INFO_IND;
    pstMsg->ucRoamingRejectNoRetryFlg   = NAS_MML_IsRoamingRejectNoRetryFlgActived(ucCause);
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);
    NAS_LMM_MEM_FREE(pstMsg);
    return;
}
/* add by yanglei 00307272 for KEY_INFO_REPORT, 2015-07-28, end */

VOS_UINT32 NAS_LMM_GetGradualForbTaTimerPara(VOS_VOID)
{
    /* Timer Para��1��ʼ, ���ڳ�ʼ����Forb�ͷ���ʱ������β���, ����ʱ����ʱ�����ж϶�ӦTA */
    g_ulGradualForbTaTimerPara++;

    return g_ulGradualForbTaTimerPara;
}
VOS_UINT32 NAS_LMM_IsGradualForbidenOptimizationOpened(VOS_VOID)
{
    /* �ж�NV�Ƿ�� */
    if(PS_FALSE == g_ucLmmGradualForbFlag)
    {
        NAS_LMM_PUBM_LOG_INFO("NAS_LMM_IsGradualForbidenOptimizationOpened: NV IS CLOSE");
        return NAS_EMM_NO;
    }

    /*����ǲ��Կ�������δ��*/
    if(PS_SUCC == LPS_OM_IsTestMode())
    {
        NAS_LMM_PUBM_LOG_WARN( "NAS_LMM_IsGradualForbidenOptimizationOpened: Test Mode");
        return NAS_EMM_NO;
    }
    /* �Ż��� */
    return NAS_EMM_YES;
}
NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TaMatchGradualForbTaList(const NAS_MM_TA_STRU  *pstTa, VOS_UINT32 *pulIndex)
{
    VOS_UINT8                               i;
    NAS_LMM_MATCH_RESULT_ENUM_UINT32        ulMatchResult = NAS_LMM_MATCH_FAIL;
    NAS_MM_TA_STRU                          stTa;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST  *pstTaList     = VOS_NULL_PTR;
    VOS_UINT32                              ulIndex       = 0;

    /* ��μ�� */
    if ((VOS_NULL_PTR == pstTa) || (VOS_NULL_PTR == pulIndex))
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_TaMatchGradualForbTaList VOS NULL PTR");
        return NAS_LMM_MATCH_PTR_NULL;
    }
    pstTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* �ж��б��Ƿ�Ϊ�� */
    if (0 == pstTaList->ulTaNum)
    {
        return NAS_LMM_MATCH_FAIL;
    }

    /* ƥ��TA�б� */
    for (i = 0; i < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; i++)
    {
        NAS_LMM_TaCpy(&stTa, &(pstTaList->astGradualForbTa[i].stTa));

        /* ��Ta List���ÿ��TA�Ա� */
        if ((NAS_EMM_GRADUAL_FORBIDDEN_TA_USED == pstTaList->astGradualForbTa[i].enUsedFlag)
             && (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatch(pstTa, &stTa)))
        {
            /* ��¼��ǰ���� */
            ulMatchResult           = NAS_LMM_MATCH_SUCCESS;
            ulIndex                 = i;

            /* �����һ��ƥ��ɹ�����������ѭ�� */
            break;
        }
    }
    /* ��ֵ���� */
    *pulIndex = ulIndex;
    return ulMatchResult;
}
VOS_VOID NAS_LMM_DelTaFromTempForbList(VOS_UINT32 ulIndex)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST   *pstTaList;
    pstTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* �����μ��б���TA���� */
    if ((ulIndex >= NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM) || (0 == pstTaList->ulTaNum))
    {
        NAS_LMM_PUBM_LOG2_WARN(" NAS_LMM_DelTaFromTempForbList ulIdex =,TaNum =", ulIndex, pstTaList->ulTaNum);
        return;
    }
    /* �ж��Ƿ�ʹ��, ��δ��ʹ��, �򷵻� */
    if (NAS_EMM_GRADUAL_FORBIDDEN_TA_NOT_USED == pstTaList->astGradualForbTa[ulIndex].enUsedFlag)
    {
        NAS_LMM_PUBM_LOG1_WARN(" NAS_LMM_DelTaFromTempForbList TA NOT USED ulIdex =", ulIndex);
        return;
    }
    /* �ȰѶ�ʱ��ͣ�� */
    NAS_LMM_StopGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER);
    NAS_LMM_StopGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER);

    /* �����ǰTA��Ϣ */
    NAS_LMM_MEM_SET(&pstTaList->astGradualForbTa[ulIndex], 0, sizeof(NAS_LMM_GRADUAL_FORB_TA));

    pstTaList->astGradualForbTa[ulIndex].enUsedFlag = NAS_EMM_GRADUAL_FORBIDDEN_TA_NOT_USED;

    /* ά����ʱ�б�TA���� */
    pstTaList->ulTaNum--;
}
VOS_VOID NAS_LMM_AddNewTaWithTempTaListNotFull(NAS_MM_TA_STRU   *pstTa)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST      *pstTaList    = VOS_NULL_PTR;
    VOS_UINT32                                  ulTimerPara  = NAS_LMM_GetGradualForbTaTimerPara();
    VOS_UINT32                                  ulIndex      = 0;
    VOS_UINT32                                  i;

    /* ��ȡ��ʱ�б��ַ */
    pstTaList          = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* ������ʱ�б�δʹ�õ�λ�� */
    for (i = 0; i < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; i++)
    {
        if (NAS_EMM_GRADUAL_FORBIDDEN_TA_NOT_USED == pstTaList->astGradualForbTa[i].enUsedFlag)
        {
            /* �ҵ���һ������ѭ�� */
            break;
        }
    }

    /* ��iС���б�������ʱ, ����TA�����λ�� */
    if (i < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM)
    {
        ulIndex = i;
    }
    else
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_AddNewTaWithTempTaListNotFull TA LIST is Full  ");
        return;
    }

    /* ��ʼ�����ܴ��� */
    pstTaList->astGradualForbTa[ulIndex].uc15RejTimes = NAS_LMM_GRADUAL_FORB_REJ_FIRST;

    /* ����Timer Para, ���ڶ�ʱ���ж��ҵ���ӦTA */
    pstTaList->astGradualForbTa[ulIndex].ulTimerPara  = ulTimerPara;

    /* ��¼��λ���Ѿ���ʹ�� */
    pstTaList->astGradualForbTa[ulIndex].enUsedFlag   = NAS_EMM_GRADUAL_FORBIDDEN_TA_USED;

    /* ����TA��Ϣ */
    pstTaList->astGradualForbTa[ulIndex].stTa.stPlmnId.aucPlmnId[0] = pstTa->stPlmnId.aucPlmnId[0];
    pstTaList->astGradualForbTa[ulIndex].stTa.stPlmnId.aucPlmnId[1] = pstTa->stPlmnId.aucPlmnId[1];
    pstTaList->astGradualForbTa[ulIndex].stTa.stPlmnId.aucPlmnId[2] = pstTa->stPlmnId.aucPlmnId[2];
    pstTaList->astGradualForbTa[ulIndex].stTa.stTac.ucTac           = pstTa->stTac.ucTac;
    pstTaList->astGradualForbTa[ulIndex].stTa.stTac.ucTacCnt        = pstTa->stTac.ucTacCnt;

    /* �����ͷ���ʱ�����ϻ���ʱ�� */
    NAS_LMM_StartGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER, ulTimerPara);
    NAS_LMM_StartGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER, ulTimerPara);

    /* TA������ 1 */
    pstTaList->ulTaNum++;
}

VOS_VOID NAS_LMM_AddNewTaInGradualForbTempTaList(NAS_MM_TA_STRU   *pstTa)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST      *pstTaList = VOS_NULL_PTR;
    VOS_UINT32                                  ulLoop;
    VOS_UINT32                                  ulDelIndex;

    pstTaList          = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* ����ʱ�б�û����ʱֱ�Ӽ����б��� */
    if(NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM > pstTaList->ulTaNum)
    {
        NAS_LMM_AddNewTaWithTempTaListNotFull(pstTa);
    }
    else
    {
        for(ulLoop = 0; ulLoop < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; ulLoop++)
        {
            /* ��0��ʼ����, �ҵ���һ����ʱ���Ѿ�ֹͣ��TA, ����ѭ�� */
            if(NAS_LMM_TIMER_STOPED == NAS_LMM_IsGradualForbiddenTimerRunning(ulLoop, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER))
            {
                break;
            }
        }
        if (ulLoop < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM)
        {
            /* �ҵ���ʱ��δ����������������б��TA, �Ѹ�TA���б����޳� */
            ulDelIndex = ulLoop;
        }
        else
        {
            /* ����ʱ����������, ��ѵ�һ�������б��е�TA�޳� */
            ulDelIndex = 0;
        }
        /* �޳�ѡ�е�TA */
        NAS_LMM_DelTaFromTempForbList(ulDelIndex);

        /* ����ǰ���һ��TA�޳���, ���Դ˴�ֻ�����TA��Ϣ������ʱ�б��� */
        NAS_LMM_AddNewTaWithTempTaListNotFull(pstTa);
    }
}

NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32 NAS_LMM_AddTaInGradualForbTempTaList(NAS_MM_TA_STRU   *pstTa)
{
    NAS_MMC_TA_LIST_STRU                         *pstForbTaForRoming;
    VOS_UINT32                                   ulIndex = 0;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST       *pstTaList = VOS_NULL_PTR;
    VOS_UINT32                                   ulTimerPara;
    NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32 enResult = NAS_EMM_GRADUAL_FORB_TA_IN_TEMP_LIST;

    /* �ж������Ƿ�� */
    if (NAS_EMM_NO == NAS_LMM_IsGradualForbidenOptimizationOpened())
    {
        return NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST;
    }
    pstTaList          = NAS_LMM_GetGradualForbTempForbTaListAddr();
    pstForbTaForRoming = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_FORB_TA_FOR_ROAMING);

    /* �ж�TA�Ƿ���Roming�б��� */
    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchTaList(pstTa, pstForbTaForRoming))
    {
        return NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST;
    }

    /* �ж�TA�Ƿ�����ʱ�б��� */
    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchGradualForbTaList(pstTa, &ulIndex))
    {
        /* �л���Forb Ta����TAU����ʱ�ͷ���ʱ�����ܻ�������, ���Դ˴���ͣ��ʱ�� */
        NAS_LMM_StopGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER);

        /* �ٴα���ʱ, ��ͣ�ϻ���ʱ��, �����ܴ���δ�ﵽ����ʱ, ���������� */
        NAS_LMM_StopGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER);

        /* ��#15������, �����ʱ�б���ɾ��, �ӵ�ԭ���б��� */
        if (pstTaList->astGradualForbTa[ulIndex].uc15RejTimes >= NAS_LMM_GRADUAL_FORB_REJ_SECOND)
        {
            NAS_LMM_DelTaFromTempForbList(ulIndex);
            enResult = NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST;
        }
        else
        {
            /* �ȸ���#15�ܾ�����, ��������ʱ��, ������ʱ��ʱ����ݾܾ�����������ʱ������ */
            pstTaList->astGradualForbTa[ulIndex].uc15RejTimes++;
            ulTimerPara = pstTaList->astGradualForbTa[ulIndex].ulTimerPara;
            NAS_LMM_StartGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER, ulTimerPara);
            NAS_LMM_StartGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER, ulTimerPara);
            enResult = NAS_EMM_GRADUAL_FORB_TA_IN_TEMP_LIST;
        }
    }
    else
    {
        /* ��TA������ʱ�б���, ������ʱ�б� */
        NAS_LMM_AddNewTaInGradualForbTempTaList(pstTa);
        enResult = NAS_EMM_GRADUAL_FORB_ADD_TA_SUCC;
    }

    /* ������ά�ɲ� */
    if(NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST == enResult)
    {
        NAS_EMM_SndOmGradualForbTaInfo(pstTa, NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_DEL);
    }
    else
    {
        NAS_EMM_SndOmGradualForbTaInfo(pstTa, NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_ADD);
    }
    return enResult;
}
VOS_VOID NAS_LMM_FillTempTaInRrcNasForbTaList(LRRC_LNAS_FORB_TA_LIST_STRU *pstRrcNasForbTaList)
{
    VOS_UINT32                                  ulIndex;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST      *pstTaList = VOS_NULL_PTR;
    VOS_UINT32                                  ulLoop;

    pstTaList          = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* �ж������Ƿ�� */
    if (NAS_EMM_NO == NAS_LMM_IsGradualForbidenOptimizationOpened())
    {
        return;
    }

    /* �жϸ�RRC��ForbTaList�Ƿ�����, ������, ֱ�ӷ��� */
    if (pstRrcNasForbTaList->ulTaNum >= LRRC_LNAS_MAX_FORBTA_NUM)
    {
        return;
    }

    /* ��ʱ�б�Ϊ��ʱ, ֱ�ӷ��� */
    if (0 == pstTaList->ulTaNum)
    {
        return;
    }

    /* ��RRC��ForbTaListû��, ��ʱ�б�Ϊ��, ���������ʱ�б�����ȥ */
    /* ��ȡRRC��ForbTaList��һ�����λ�� */
    ulIndex     = pstRrcNasForbTaList->ulTaNum;

    /* ������ʱ�б�, ���RRC�б� */
    for (ulLoop = 0; ulLoop < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; ulLoop++)
    {
        /* �жϸ�RRC���б��Ƿ������� */
        if (LRRC_LNAS_MAX_FORBTA_NUM <= ulIndex)
        {
            return;
        }
        /* �ҵ���ʹ�õ�TA */
        if (NAS_EMM_GRADUAL_FORBIDDEN_TA_USED == pstTaList->astGradualForbTa[ulLoop].enUsedFlag)
        {
            /* �ͷ���ʱ�����������¼�����ʱ�б��е�TA */
            if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsGradualForbiddenTimerRunning(ulLoop, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER))
            {
                /* ������ʱ�б��RRC�б�ṹ�岻һ��, ���Դ˴����ÿ������� */
                pstRrcNasForbTaList->astForbTa[ulIndex].stPlmnId.aucPlmnId[0]
                    = pstTaList->astGradualForbTa[ulLoop].stTa.stPlmnId.aucPlmnId[0];
                pstRrcNasForbTaList->astForbTa[ulIndex].stPlmnId.aucPlmnId[1]
                    = pstTaList->astGradualForbTa[ulLoop].stTa.stPlmnId.aucPlmnId[1];
                pstRrcNasForbTaList->astForbTa[ulIndex].stPlmnId.aucPlmnId[2]
                    = pstTaList->astGradualForbTa[ulLoop].stTa.stPlmnId.aucPlmnId[2];
                pstRrcNasForbTaList->astForbTa[ulIndex].stTac.ucTac
                    = pstTaList->astGradualForbTa[ulLoop].stTa.stTac.ucTac;
                pstRrcNasForbTaList->astForbTa[ulIndex].stTac.ucTacCont
                    = pstTaList->astGradualForbTa[ulLoop].stTa.stTac.ucTacCnt;

                /* ��һ�����������1 */
                ulIndex++;

                /* Ta������1 */
                pstRrcNasForbTaList->ulTaNum++;
            }
        }
    }
}

VOS_VOID NAS_LMM_FillUserSpecRrcNasForbTaListWithTempTa
(
    const NAS_MM_PLMN_ID_STRU  *pstPlmnId,
    NAS_MM_TA_LIST_STRU        *pstRrcTaList
)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST      *pstTaList = VOS_NULL_PTR;
    VOS_UINT32                                  ulLoop;

    pstTaList          = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* �ж������Ƿ�� */
    if (NAS_EMM_NO == NAS_LMM_IsGradualForbidenOptimizationOpened())
    {
        return;
    }

    /* �жϸ�RRC��ForbTaList�Ƿ�����, ������, ֱ�ӷ��� */
    if (pstRrcTaList->ulTaNum >= NAS_MM_MAX_TA_NUM)
    {
        return;
    }

    /* ��ʱ�б�Ϊ��ʱ, ֱ�ӷ��� */
    if (0 == pstTaList->ulTaNum)
    {
        return;
    }

    /* ������ʱ�б�, ���RRC�б� */
    for (ulLoop = 0; ulLoop < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; ulLoop++)
    {
        /* �ҵ���ʹ�õ�TA */
        if (NAS_EMM_GRADUAL_FORBIDDEN_TA_USED == pstTaList->astGradualForbTa[ulLoop].enUsedFlag)
        {
            /* �ѷ�ָ��PLMN�µ�Forb TA����LRRC */
            if (NAS_LMM_MATCH_SUCCESS != NAS_LMM_PlmnMatch(pstPlmnId,&pstTaList->astGradualForbTa[ulLoop].stTa.stPlmnId))
            {
                /* �ͷ���ʱ�����������¼�����ʱ�б��е�TA */
                if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsGradualForbiddenTimerRunning(ulLoop, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER))
                {
                    NAS_LMM_AddTaInTaList(   &pstTaList->astGradualForbTa[ulLoop].stTa,
                                             pstRrcTaList,
                                             NAS_LMM_MAX_FORBTA_NUM);
                }
            }
        }
    }
}
NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32 NAS_LMM_UpdateGradualForbTempTaList(VOS_VOID)
{
    VOS_UINT32                                   ulIndex        = 0;
    NAS_MM_TA_LIST_STRU                          *pstCurTaiList = VOS_NULL_PTR;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST       *pstTempTaList = VOS_NULL_PTR;
    VOS_UINT32                                   i              = 0;
    NAS_EMM_GRADUAL_FORBIDDEN_RESULT_ENUM_UINT32 enUpdateResult = NAS_EMM_GRADUAL_FORB_TA_LIST_NOT_CHANGED;

    /* �ж������Ƿ�� */
    if (NAS_EMM_NO == NAS_LMM_IsGradualForbidenOptimizationOpened())
    {
        return NAS_EMM_GRADUAL_FORB_TA_LIST_NOT_CHANGED;
    }

    /*��ȡ��ǰ��TAI List,ForTA for Roaming,ForbTA for RPOS*/
    pstCurTaiList = (VOS_VOID *)NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_TA_LIST);
    pstTempTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();
    if(0 == pstTempTaList->ulTaNum)
    {
        return NAS_EMM_GRADUAL_FORB_TA_LIST_NOT_CHANGED;
    }

    /* �ж�TA LIST�Ƿ�����ʱ�б��� */
    for(i = 0; i < pstCurTaiList->ulTaNum; i++)
    {
        if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchGradualForbTaList(&(pstCurTaiList->astTa[i]), &ulIndex))
        {
            /* TA����ʱ�б���, �޳���TA */
            enUpdateResult = NAS_EMM_GRADUAL_FORB_TA_LIST_CHANGED;

            /* ���б���ɾ��ƥ���ϵ�TA */
            NAS_LMM_DelTaFromTempForbList(ulIndex);

            /* ������ά�ɲ� */
            NAS_EMM_SndOmGradualForbTaInfo(&(pstCurTaiList->astTa[i]), NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_DEL);
        }
    }
    return enUpdateResult;
}

VOS_UINT32 NAS_LMM_CheckNvGradualForbiddenTimerLenVaild(VOS_UINT32 ulTimerLen)
{
    /* ��ʱ������Ϊ0ʱ��Ч */
    if(0 == ulTimerLen)
    {
        return NAS_EMM_NO;
    }
    /* ��ʱ�����Ȳ�С��ԭ��Forb��ʱ������ʱ��Ч */
    if(NAS_LMM_TIMER_EMM_DEL_FORB_TA_PRIOD_LEN <= ulTimerLen)
    {
        return NAS_EMM_NO;
    }

    return NAS_EMM_YES;
}

VOS_VOID NAS_LMM_GradualForbParaInit(LNAS_LMM_NV_GRADUAL_FORBIDDEN_PARA_STRU stNvGradualForbPara)
{
    VOS_UINT32                                ulTimerLen;

    /* ��NVǰ�ȸ�Ĭ��ֵ */
    g_ucLmmGradualForbFlag               = PS_FALSE;
    g_ulGradualForbTimerFirstLen         = 300*1000;
    g_ulGradualForbTimerSecondLen        = 1200*1000;
    g_ulGradualForbAgingTimerLen         = 7200*1000;

    /* �����ƿ��ط�0ʱ, ���Դ� */
    if (0 != stNvGradualForbPara.ucGradualForbFlag)
    {
        g_ucLmmGradualForbFlag       = PS_TRUE;
    }

    /* �жϵ�һ�γͷ���ʱ�����������Ƿ���Ч */
    ulTimerLen = stNvGradualForbPara.usGradualForbTimerFirstLen * 60 * 1000;
    if (NAS_EMM_YES == NAS_LMM_CheckNvGradualForbiddenTimerLenVaild(ulTimerLen))
    {
        g_ulGradualForbTimerFirstLen = ulTimerLen;
    }
    /* �жϵڶ��γͷ���ʱ�����������Ƿ���Ч */
    ulTimerLen = stNvGradualForbPara.usGradualForbTimerSecondLen * 60 * 1000;
    if (NAS_EMM_YES == NAS_LMM_CheckNvGradualForbiddenTimerLenVaild(ulTimerLen))
    {
        g_ulGradualForbTimerSecondLen = ulTimerLen;
    }
    /* �ж��ϻ���ʱ�����������Ƿ���Ч */
    ulTimerLen = stNvGradualForbPara.ulGradualForbAgingTimerLen * 60 *1000;
    if (NAS_EMM_YES == NAS_LMM_CheckNvGradualForbiddenTimerLenVaild(ulTimerLen))
    {
        g_ulGradualForbAgingTimerLen = ulTimerLen;
    }

    /* ��������Ϣ����HIDS�� */
    NAS_EMM_SndOmGradualForbParaLog(stNvGradualForbPara);
}


VOS_VOID NAS_LMM_GradualForbTaListInit(VOS_VOID)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST       *pstTempTaList = VOS_NULL_PTR;
    VOS_UINT32                                   ulLoop;

    pstTempTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* ��ʼ��Gradual Forb��ʱ�б���ά������Ϣ */
    NAS_LMM_MEM_SET(pstTempTaList, 0, sizeof(NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST));

    for (ulLoop = 0; ulLoop < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; ulLoop++)
    {
        pstTempTaList->astGradualForbTa[ulLoop].enUsedFlag = NAS_EMM_GRADUAL_FORBIDDEN_TA_NOT_USED;
    }

    /* ��TimerParaȫ�ֱ������ */
    g_ulGradualForbTaTimerPara= 0;
}


VOS_VOID NAS_LMM_StopAllGradualForbiddenTimer(VOS_VOID)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST       *pstTempTaList = VOS_NULL_PTR;
    VOS_UINT32                                    ulIndex;

    pstTempTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    for (ulIndex = 0; ulIndex < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; ulIndex++)
    {
        if (NAS_EMM_GRADUAL_FORBIDDEN_TA_USED == pstTempTaList->astGradualForbTa[ulIndex].enUsedFlag)
        {
            /* �жϳͷ���ʱ���Ƿ�������, ����������ֹͣ�ͷ���ʱ�� */
            if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsGradualForbiddenTimerRunning(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER))
            {
                NAS_LMM_StopGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER);
            }
            /* �ж��ϻ���ʱ���Ƿ�������, ����������ֹͣ�ϻ���ʱ�� */
            if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsGradualForbiddenTimerRunning(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER))
            {
                NAS_LMM_StopGradualForbiddenTimer(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER);
            }
        }
    }
    return;
}

VOS_VOID NAS_LMM_ClearAllGradualForbTaList(VOS_VOID)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST       *pstTempTaList = VOS_NULL_PTR;

    pstTempTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* ֹͣ����Gradual Forb��ʱ�� */
    NAS_LMM_StopAllGradualForbiddenTimer();

    /* ֹͣ��ʱ����, ���Gradual Forb��ʱ�б���ά������Ϣ */
    NAS_LMM_MEM_SET(pstTempTaList, 0, sizeof(NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST));

    /* ��TimerParaȫ�ֱ������ */
    g_ulGradualForbTaTimerPara= 0;
}
NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TimerParaMatchGradualForbTaList(VOS_UINT32 ulTimerPara, VOS_UINT32 *pulIndex)
{
    VOS_UINT8                               i;
    NAS_LMM_MATCH_RESULT_ENUM_UINT32        ulMatchResult = NAS_LMM_MATCH_FAIL;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST  *pstTaList     = VOS_NULL_PTR;
    VOS_UINT32                              ulIndex       = 0;
    if(VOS_NULL_PTR == pulIndex)
    {
        return NAS_LMM_MATCH_PTR_NULL;
    }

    pstTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* TA������� */
    if (0 == pstTaList->ulTaNum)
    {
        NAS_LMM_PUBM_LOG_WARN("NAS_LMM_TaMatchTempTaList is empty ");
        return NAS_LMM_MATCH_FAIL;
    }

    for(i = 0; i < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; i++)
    {
        if ((NAS_EMM_GRADUAL_FORBIDDEN_TA_USED == pstTaList->astGradualForbTa[i].enUsedFlag)
            && (ulTimerPara == pstTaList->astGradualForbTa[i].ulTimerPara))
        {
            ulIndex       = i;
            ulMatchResult = NAS_LMM_MATCH_SUCCESS;
            break;
        }
    }
    *pulIndex = ulIndex;
    return ulMatchResult;
}
VOS_VOID NAS_LMM_GetGradualForbTaWithIndex(VOS_UINT32 ulIndex, NAS_MM_TA_STRU *pstTa)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST  *pstTaList     = VOS_NULL_PTR;

    /* ��ȡ��ʱ�б� */
    pstTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* ������ӦTA��Ϣ */
    NAS_LMM_MEM_CPY(pstTa, &pstTaList->astGradualForbTa[ulIndex].stTa, sizeof(NAS_MM_TA_STRU));
    return;
}

VOS_VOID  NAS_LMM_AddTaInForbListWithTauRejCauseVal15(VOS_UINT32 ulIsWithExtCause,
                                                                        VOS_UINT32 *pulIsNeedExecLteNotAllow)
{
    NAS_MM_TA_STRU                              stCurrentTa;

    *pulIsNeedExecLteNotAllow  = NAS_EMM_YES;

    NAS_LMM_MEM_SET(&stCurrentTa, 0, sizeof(NAS_MM_TA_STRU));

    /* ��ȡ��ǰפ��TA */
    NAS_EMM_GetCurrentTa(&stCurrentTa);

    /* �û�ָ����, ����Rej #15�б��� */
    if (NAS_EMMC_USER_SPEC_PLMN_YES == NAS_EMMC_GetUserSpecPlmnFlag())
    {
        NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRej15Addr());

        *pulIsNeedExecLteNotAllow = NAS_EMM_YES;
        return;
    }

    /* R11��Ҫ�ж��Ƿ��ǹ������� */
    if (NAS_RELEASE_R11)
    {
        /* ��Ҫ����Forb �б� */
        if (NAS_EMM_YES == NAS_EMM_IsNeedAddForbTa())
        {
            /* Я����չԭ��ֵָʾ4Gδ����, ����Roaming�б� */
            if (NAS_EMM_YES == ulIsWithExtCause)
            {
                /*store the current TAI in the list of
                        "forbidden tracking areas for roaming"*/
                NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
                *pulIsNeedExecLteNotAllow = NAS_EMM_YES;
            }
            else if (NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST == NAS_LMM_AddTaInGradualForbTempTaList(&stCurrentTa))
            {
                /* û�м�����ʱ�б� */
                /*store the current TAI in the list of
                        "forbidden tracking areas for roaming"*/
                NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
                *pulIsNeedExecLteNotAllow = NAS_EMM_YES;
            }
            else
            {
                /* ���ߵ��÷�֧, ˵��TA������ʱ�б���, ����Ҫ��4Gδ�������� */
                *pulIsNeedExecLteNotAllow = NAS_EMM_NO;
            }
            NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
        }
        else
        {
            *pulIsNeedExecLteNotAllow = NAS_EMM_YES;
        }
    }
    else
    {
        /* Я����չԭ��ֵָʾ4Gδ����, ����Roaming�б� */
        if (NAS_EMM_YES == ulIsWithExtCause)
        {
            /*store the current TAI in the list of
                    "forbidden tracking areas for roaming"*/
            NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
            *pulIsNeedExecLteNotAllow = NAS_EMM_YES;
        }
        else if (NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST == NAS_LMM_AddTaInGradualForbTempTaList(&stCurrentTa))
        {
            /* û�м�����ʱ�б� */
            /*store the current TAI in the list of
                    "forbidden tracking areas for roaming"*/
            NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
            *pulIsNeedExecLteNotAllow = NAS_EMM_YES;
        }
        else
        {
            /* ���ߵ��÷�֧, ˵��TA������ʱ�б���, ����Ҫ��4Gδ�������� */
            *pulIsNeedExecLteNotAllow = NAS_EMM_NO;
        }
        NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
    }
    return;
}
VOS_VOID  NAS_LMM_AddTaInForbListWithAttRejCauseVal15(VOS_UINT32 ulIsWithExtCause,
                                                                         VOS_UINT32 *pulIsNeedExecLteNotAllow)
{
    NAS_MM_TA_STRU                              stCurrentTa;
    *pulIsNeedExecLteNotAllow   = NAS_EMM_NO;

    NAS_LMM_MEM_SET(&stCurrentTa, 0, sizeof(NAS_MM_TA_STRU));

    /* ��ȡ��ǰפ��TA */
    NAS_EMM_GetCurrentTa(&stCurrentTa);

    /* �û�ָ����, ����Rej #15�б��� */
    if (NAS_EMMC_USER_SPEC_PLMN_YES == NAS_EMMC_GetUserSpecPlmnFlag())
    {
        NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRej15Addr());
        *pulIsNeedExecLteNotAllow   = NAS_EMM_YES;
        return;
    }

    /* ����Я����չԭ��ֵ, ָʾ4Gδ����, ֱ�Ӽӵ�Roam �б��� */
    if (NAS_EMM_YES == ulIsWithExtCause)
    {
        /*store the current TAI in the list of "forbidden tracking areas for roaming"*/
        NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
        NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
        *pulIsNeedExecLteNotAllow   = NAS_EMM_YES;
        return;
    }

    /* ������û��Я����չԭ��ֵ, ����Ҫ������ʱ�����б��� */
    /* �ж��Ƿ���Ҫ����Roam�б���, ����Form�б� */
    if (NAS_EMM_GRADUAL_FORB_TA_NEED_ADD_ROAM_LIST == NAS_LMM_AddTaInGradualForbTempTaList(&stCurrentTa))
    {
        /*store the current TAI in the list of "forbidden tracking areas for roaming"*/
        NAS_EMM_AddForbTa(&stCurrentTa,NAS_LMM_GetEmmInfoNetInfoForbTaForRoamAddr());
        NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
        *pulIsNeedExecLteNotAllow   = NAS_EMM_YES;
    }
    else
    {
        /* ������ʱ�б� */
        NAS_EMMC_SendRrcCellSelectionReq(LRRC_LNAS_FORBTA_CHANGE);
        *pulIsNeedExecLteNotAllow   = NAS_EMM_NO;
    }
    return;
}

VOS_VOID NAS_LMM_DelCurrTaFromGradualForbTaList(NAS_MM_TA_STRU   *pstCurrTa)
{
    VOS_UINT32                          ulIndex = 0;

    /* Gradual Forb�Ż���, ��Ҫ�ѵ�ǰTA����ʱ�б����޳� */
    if (NAS_EMM_YES == NAS_LMM_IsGradualForbidenOptimizationOpened())
    {
        if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchGradualForbTaList(pstCurrTa, &ulIndex))
        {
            NAS_LMM_DelTaFromTempForbList(ulIndex);

            /* ������ά�ɲ� */
            NAS_EMM_SndOmGradualForbTaInfo(pstCurrTa, NAS_LMM_GRADUAL_FORB_TA_OPERATION_TYPE_DEL);
        }
    }
    return;
}

VOS_VOID NAS_LMM_UpdateGradualForbListWithTauRejCause13(NAS_MM_TA_STRU   *pstCurrTa)
{
    if (NAS_RELEASE_R11)
    {
        if (NAS_EMM_YES == NAS_EMM_IsNeedAddForbTa())
        {
            /* ��#13��, ��Ҫ����Roaming �б�, ���Դ�ʱ��Ҫ��Ta����ʱ�б���ɾ�� */
            NAS_LMM_DelCurrTaFromGradualForbTaList(pstCurrTa);
        }
    }
    else
    {
        NAS_LMM_DelCurrTaFromGradualForbTaList(pstCurrTa);
    }
}
VOS_UINT32 NAS_LMM_ExistTaInTempTaListWithForbTimerRunning(VOS_VOID)
{
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST  *pstTaList     = VOS_NULL_PTR;
    VOS_UINT32                              ulLoop;
    VOS_UINT32                              ulIsExistTa   = NAS_EMM_NO;

    /* ��ȡ��ʱ�б� */
    pstTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();

    /* ��ʱ�б���TA����Ϊ0, �򲻴���TA����ʱ�б��ҳͷ���ʱ�������� */
    if (0 == pstTaList->ulTaNum)
    {
        return NAS_EMM_NO;
    }

    for (ulLoop = 0; ulLoop < NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM; ulLoop++)
    {
        if (NAS_EMM_GRADUAL_FORBIDDEN_TA_USED == pstTaList->astGradualForbTa[ulLoop].enUsedFlag)
        {
            if (NAS_LMM_TIMER_RUNNING == NAS_LMM_IsGradualForbiddenTimerRunning(ulLoop, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER))
            {
                /* �ҵ�TA����ʱ�б��ҳͷ���ʱ��������, �˳�ѭ��*/
                ulIsExistTa   = NAS_EMM_YES;
                break;
            }
        }
    }
    return ulIsExistTa;
}
NAS_LMM_MATCH_RESULT_ENUM_UINT32 NAS_LMM_TaMatchTempTaListWithForbTimerRunning
(
    const NAS_MMC_TA_STRU                    *pstTa
)
{
    VOS_UINT32                      ulIndex;
    if (NAS_LMM_MATCH_SUCCESS == NAS_LMM_TaMatchGradualForbTaList(pstTa, &ulIndex))
    {
        /* ��TA��Gradul Forb��ʱ�б���, �ҳͷ���ʱ��������, �򱻽� */
        if(NAS_LMM_TIMER_RUNNING == NAS_LMM_IsGradualForbiddenTimerRunning(ulIndex, TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER))
        {
            return NAS_LMM_MATCH_SUCCESS;
        }
    }
    return NAS_LMM_MATCH_FAIL;
}
NAS_LMM_REG_DOMAIN_ENUM_UINT32 NAS_LMM_GetEmmInfoRegDomain(VOS_VOID)
{
    NAS_EMM_PUB_INFO_STRU                   *pstEmmInfo;
    NAS_LMM_REG_DOMAIN_ENUM_UINT32          enRegDomainCur;

    pstEmmInfo = NAS_LMM_GetEmmInfoAddr();

    /* ��ȡ��ǰע���� */
    enRegDomainCur = pstEmmInfo->enRegisteredDomain;

    return enRegDomainCur;
}
VOS_VOID NAS_LMM_SetEmmInfoRegDomain(NAS_LMM_REG_DOMAIN_ENUM_UINT32 enRegDomainDst)
{
    NAS_EMM_PUB_INFO_STRU                   *pstEmmInfo;
    NAS_LMM_REG_DOMAIN_ENUM_UINT32          enRegDomainCur;

    pstEmmInfo = NAS_LMM_GetEmmInfoAddr();

    /* �޸�ע����ǰ,��ȡ��ǰע���� */
    enRegDomainCur = pstEmmInfo->enRegisteredDomain;

    /* �޸�ע���� */
    pstEmmInfo->enRegisteredDomain = enRegDomainDst;

    #if (VOS_WIN32 != VOS_OS_VER)
    /* ������ά�ɲ� */
    NAS_LMM_SndOmRegDomainInfo(enRegDomainCur, enRegDomainDst);
    #endif
}

/* zhaochen 00308719 begin for SMS Message hook */
/*****************************************************************************
 Function Name   : NAS_LMM_IsMsgContainsSMS
 Description     : �жϿտ���Ϣ�Ƿ���δ���ܵĶ�������
 Input           : None
 Output          : None
 Return          : VOS_UINT8
 History         :
    1.zhaochen 00308719      2015-04-02  Draft Enact
*****************************************************************************/
VOS_UINT8  NAS_LMM_IsMsgContainsSMS(VOS_UINT32 ulMsgSize, VOS_UINT8 *pstMsg)
{
    /* ������ζ�����Ϣ��NVû�д򿪣���ֱ�ӷ��ز����� */
    if (VOS_TRUE != NAS_MML_GetSmsFilterFlg())
    {
        return NAS_EMM_NO;
    }
    NAS_EMM_PUBU_LOG2_INFO("NAS_LMM_IsMsgContainsSMS: pstMsg[0]=, pstMsg[1] ="
                             , pstMsg[0] ,pstMsg[1]);
    NAS_EMM_PUBU_LOG2_INFO("NAS_LMM_IsMsgContainsSMS: pstMsg[5]=, pstMsg[6] ="
                             , pstMsg[5] ,pstMsg[6]);
    /* �˴����Զ�NV�����ر���ֱ�ӷ���NO? */
    /* ����Ϊ0��1ʱ�������ܴ��ڶ������� */
    if (2 > ulMsgSize)
    {
        return NAS_EMM_NO;
    }
    /* �ж��Ƿ�Ϊ���� */
    if (0x07 == pstMsg[0] && (0x62 == pstMsg[1] || 0x63 == pstMsg[1]))
    {
        /* �տ���ϢΪδ���ܵĶ��� */
        return NAS_EMM_YES;
    }
    if (0x27 == pstMsg[0])
    {
        /* �м��ܺ������Ա������������Ҫ�ж���Ϣ���ȣ�����С��7�򲻻���ж������� */
        if (7 > ulMsgSize)
        {
            return NAS_EMM_NO;
        }
        /* ������ȫͷ�������Ϣ�Ƿ�Ϊ���ĵĶ��� */
        if (0x07 == pstMsg[5] && (0x62 == pstMsg[6] || 0x63 == pstMsg[6]))
        {
            return NAS_EMM_YES;
        }
    }
    return NAS_EMM_NO;
}
/* zhaochen 00308719 end for SMS Message hook */

/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

/* end of ��ϵͳ+ģ��+�ļ���.c */
