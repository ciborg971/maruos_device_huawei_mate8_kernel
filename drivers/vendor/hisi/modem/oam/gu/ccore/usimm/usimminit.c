

#include "vos_Id.h"
#include "usimminit.h"
#include "usimmapdu.h"
#include "usimmdl.h"
#include "siappstk.h"
#include "NvIdList.h"
#include "usimmt1dl.h"
#include "usimmglobal.h"
#include "errorlog.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "CasNvInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_USIMM_INIT_C
/*lint +e960*/

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
/* USIM����ʼ���б� */
USIMM_INITAPPLIST_FUNC g_aUSIMInitProcFuncTbl[] =
{
    {USIMM_UICC_InitUsimGlobal,         USIMM_FUNC_AVAILABLE},  /*λ����Ҫ�̶�*/
    {USIMM_UICC_InitUsimADF,            USIMM_FUNC_AVAILABLE},  /*λ����Ҫ�̶�*/
    {USIMM_UICC_InitPINTime,            USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitUsimECC,            USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitUsimEFLI,           USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitUsimATT,            USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_AutoVerifyPIN,          USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitAppState,           USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitUsimMFile,          USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitUsimMFile2,         USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitUsimFinish,         USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitUsimOPFile,         USIMM_FUNC_AVAILABLE}
};

/* CSIM����ʼ���б� */
USIMM_INITAPPLIST_FUNC g_aCSIMInitProcFuncTbl[] =
{
    {USIMM_UICC_InitCsimGlobal,         USIMM_FUNC_AVAILABLE},  /*λ����Ҫ�̶�*/
    {USIMM_UICC_InitCsimADF,            USIMM_FUNC_AVAILABLE},  /*λ����Ҫ�̶�*/
    {USIMM_UICC_InitPINTime,            USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitCsimECC,            USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_AutoVerifyPIN,          USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitAppState,           USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitCsimMFile,          USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitStoreMeid,          USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitCsimMFile2,         USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitCsimEFMecrp,        USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitCsimFinish,         USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitCsimOPFile,         USIMM_FUNC_AVAILABLE}
};

/* CSIM����ʼ���б� */
USIMM_INITAPPLIST_FUNC g_aVIACSIMInitProcFuncTbl[] =
{
    {USIMM_UICC_InitCsimGlobal,         USIMM_FUNC_AVAILABLE},  /*λ����Ҫ�̶�*/
    {USIMM_UICC_InitCsimADF,            USIMM_FUNC_AVAILABLE},  /*λ����Ҫ�̶�*/
    {USIMM_UICC_InitPINTime,            USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_AutoVerifyPIN,          USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitAppState,           USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitVIACsimFinish,      USIMM_FUNC_AVAILABLE},
};

/* ISIM����ʼ���б� */
USIMM_INITAPPLIST_FUNC g_aISIMInitProcFuncTbl[] =
{
    {USIMM_UICC_InitIsimGlobal,         USIMM_FUNC_AVAILABLE},  /*λ����Ҫ�̶�*/
    {USIMM_UICC_InitIsimADF,            USIMM_FUNC_AVAILABLE},  /*λ����Ҫ�̶�*/
    {USIMM_UICC_InitPINTime,            USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_AutoVerifyPIN,          USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitAppState,           USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitIsimMFile,          USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitIsimFinish,         USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitIsimOPFile,         USIMM_FUNC_AVAILABLE}
};

/* UICC��Ӧ�ó�ʼ���б� */
USIMM_INITAPPLIST_STRU g_aUICCInitProcTbl[] =
{
    {g_aUSIMInitProcFuncTbl,            ARRAYSIZE(g_aUSIMInitProcFuncTbl)},
    {g_aISIMInitProcFuncTbl,            ARRAYSIZE(g_aISIMInitProcFuncTbl)},
    {g_aCSIMInitProcFuncTbl,            ARRAYSIZE(g_aCSIMInitProcFuncTbl)}
};

/* UICC���ϵ��ʼ�����̺����б� */
USIMM_COMM_CARD_INIT_FUNC g_aUICCCommInitProcFuncTbl[] =
{
    {USIMM_UICC_InitGlobalVar,          USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitCardTypeByATR,      USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InsertCommFileToPool,   USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_ProfileDownload,        USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_DecodeEFDIR,            USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_DecodeATRStep2,         USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_SortAppSN,              USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitCardApps,           USIMM_FUNC_AVAILABLE},
    {USIMM_UICC_InitIsimSimuState,      USIMM_FUNC_AVAILABLE}
};

/* SIM����ʼ���б� */
USIMM_INITAPPLIST_FUNC g_aSIMInitProcFuncTbl[] =
{
    {USIMM_ICC_InitSimGlobal,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimADF,              USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitPINInfo,             USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InsertCommFileToPool,    USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimECC,              USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimEFLP,             USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimATT,              USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_AutoVerifyPIN,          USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitAppState,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitPhase,               USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimSST,              USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitTerminalProfile,     USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimFBDN,             USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimMFile,            USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimMFile2,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimFinish,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitSimOPFile,           USIMM_FUNC_AVAILABLE}
};

/* UIM����ʼ���б� */
USIMM_INITAPPLIST_FUNC g_aUIMInitProcFuncTbl[] =
{
    {USIMM_ICC_InitUimGlobal,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimADF,              USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitPINInfo,             USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InsertCommFileToPool,    USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimECC,              USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimRuimId,           USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_AutoVerifyPIN,          USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitAppState,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitPhase,               USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitCST,                 USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitTerminalProfile,     USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimFdnBdn,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimMFile,            USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitStoreEsnMeid,        USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimMFile2,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimEFMecrp,          USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimFinish,           USIMM_FUNC_AVAILABLE}
};

/* UIM����ʼ���б� */
USIMM_INITAPPLIST_FUNC g_aVIAUIMInitProcFuncTbl[] =
{
    {USIMM_ICC_InitUimGlobal,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimADF,              USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitPINInfo,             USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_AutoVerifyPIN,          USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitAppState,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitUimFinish,           USIMM_FUNC_AVAILABLE}
};

/* ICC��Ӧ�ó�ʼ���б� */
USIMM_INITAPPLIST_STRU g_aICCInitProcTbl[] =
{
    {g_aSIMInitProcFuncTbl,             ARRAYSIZE(g_aSIMInitProcFuncTbl)},
    {VOS_NULL_PTR,                      0},
    {g_aUIMInitProcFuncTbl,             ARRAYSIZE(g_aUIMInitProcFuncTbl)}
};

/* ICC���ϵ��ʼ�����̺����б� */
USIMM_COMM_CARD_INIT_FUNC g_aICCCommInitProcFuncTbl[] =
{
    {USIMM_ICC_InitGlobalVar,           USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitCardTypeByATR,       USIMM_FUNC_AVAILABLE},
    {USIMM_ICC_InitAppOrder,            USIMM_FUNC_AVAILABLE},
    {USIMM_COMM_InitCardApps,           USIMM_FUNC_AVAILABLE}
};

/* ����Ӧ�ó�ʼ���ṹ */
USIMM_INITAPPSCTRL_STRU                 g_astUSIMMInitAppCtrl[USIMM_CARDAPP_BUTT];

/*****************************************************************************
�� �� ��  :USIMM_COMM_ClearInitCtrlGlobal
��������  :��ɿ���ʼ����ȫ�ֱ����ĳ�ʼ��
�������  :pMsg ->��Ϣָ��
�������  :��
�� �� ֵ  :VOS_ERR
           VOS_OK
�޶���¼  :
1. ��    ��   : 2015��2��26��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_ClearInitCtrlGlobal(VOS_VOID)
{
    VOS_UINT32                  i;

    /*lint -e534*/
    VOS_MemSet(g_astUSIMMInitAppCtrl, 0, sizeof(g_astUSIMMInitAppCtrl));
    /*lint +e534*/

    for(i=0; i < ARRAYSIZE(g_astUSIMMInitAppCtrl); i++)
    {
        g_astUSIMMInitAppCtrl[i].enAppType          = USIMM_CARDAPP_BUTT;
        g_astUSIMMInitAppCtrl[i].ucChannelNo        = VOS_NULL_BYTE;
        g_astUSIMMInitAppCtrl[i].enAppInitResult    = USIMM_INITAPPS_BUTT;
        g_astUSIMMInitAppCtrl[i].enAppStepResult    = USIMM_INITSTEPS_BUTT;
    }

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_COMM_ResetInitGlobal
��������  :��ɳ�ʼ����ȫ�ֱ�����������ʱ����Ҫ��յı���
�������  :pMsg ->��Ϣָ��
�������  :��
�� �� ֵ  :��
�޶���¼  :
1. ��    ��   : 2015��2��26��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_ResetInitGlobal(VOS_VOID)
{
    VOS_UINT32                  i;

    for(i=0; i<ARRAYSIZE(g_astUSIMMInitAppCtrl); i++)
    {
        g_astUSIMMInitAppCtrl[i].ucChannelNo        = VOS_NULL_BYTE;

        g_astUSIMMInitAppCtrl[i].enAppStepResult    = USIMM_INITSTEPS_BUTT;

        g_astUSIMMInitAppCtrl[i].ucCurStep          = VOS_NULL;
    }

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_COMM_ClearAppInfoGlobal
��������  :��ɿ���ʼ����APP Infoȫ�ֱ����ĳ�ʼ��
�������  :��
�������  :��
�� �� ֵ  :��
�޶���¼  :
1. ��    ��   : 2015��2��26��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_ClearAppInfoGlobal(VOS_VOID)
{
    VOS_UINT32                          i;

    /*lint -e534*/
    VOS_MemSet(g_astUSIMMCardAppInfo, 0, sizeof(g_astUSIMMCardAppInfo));
    VOS_MemSet(g_astUSIMMInitAIDInfo, 0, sizeof(g_astUSIMMInitAIDInfo));
    /*lint +e534*/

    for(i=0; i<USIMM_CHANNEL_NUMBER_MAX; i++)
    {
        g_astUSIMMCardAppInfo[i].enAppType      = USIMM_UNLIMIT_APP_BUTT;

        g_astUSIMMCardAppInfo[i].enAppService   = USIMM_CARD_SERVIC_ABSENT;
    }

    return;
}


VOS_VOID USIMM_COMM_ResetInitListStatus(VOS_VOID)
{
    USIMM_PHYCARD_TYPE_ENUM_UINT32          enCardType;
    USIMM_CARDAPP_ENUM_UINT32               enAppType;
    VOS_UINT32                              ulAppNum;
    VOS_UINT32                              i;
    USIMM_INITAPPLIST_FUNC                 *pstListItem;

    /* �ָ�UICC������ʼ���б�״̬ */
    for (i = 0; i < ARRAYSIZE(g_aUICCCommInitProcFuncTbl); i++)
    {
        g_aUICCCommInitProcFuncTbl[i].enStatus = USIMM_FUNC_AVAILABLE;
    }

    /* �ָ�ICC������ʼ���б�״̬ */
    for (i = 0; i < ARRAYSIZE(g_aICCCommInitProcFuncTbl); i++)
    {
        g_aICCCommInitProcFuncTbl[i].enStatus = USIMM_FUNC_AVAILABLE;
    }

    /* �ָ�Ӧ�ó�ʼ���б�״̬ */
    for (enCardType = USIMM_PHYCARD_TYPE_ICC; enCardType <= USIMM_PHYCARD_TYPE_UICC; enCardType++)
    {
        for (enAppType = USIMM_GUTL_APP; enAppType < USIMM_CARDAPP_BUTT; enAppType++)
        {
            ulAppNum    = USIMM_COMM_GetAppInitNum(enCardType, enAppType);
            pstListItem = USIMM_COMM_GetAppInitList(enCardType, enAppType);

            for (i = 0; i < ulAppNum; i++)
            {
                pstListItem[i].enStatus = USIMM_FUNC_AVAILABLE;
            }
        }
    }

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_InitCommFuncTble
��������  :��ɿ���ʼ����ȫ�ֱ����б���ϵ��ʼ��
�������  :��
�������  :��
�� �� ֵ  :��
�޶���¼  :
1. ��    ��   : 2015��2��26��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_InitCommFuncTble(VOS_VOID)
{

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    g_aUICCInitProcTbl[USIMM_CDMA_APP].pFuncList = g_aCSIMInitProcFuncTbl;
    g_aUICCInitProcTbl[USIMM_CDMA_APP].ulListNum = ARRAYSIZE(g_aCSIMInitProcFuncTbl);

    g_aICCInitProcTbl[USIMM_CDMA_APP].pFuncList = g_aUIMInitProcFuncTbl;
    g_aICCInitProcTbl[USIMM_CDMA_APP].ulListNum = ARRAYSIZE(g_aUIMInitProcFuncTbl);

    return;

#else
    if (VOS_TRUE == USIMM_IsCLEnable()) /*ƴƬ���ܴ�*/
    {
        g_aUICCInitProcTbl[USIMM_CDMA_APP].pFuncList = g_aVIACSIMInitProcFuncTbl;
        g_aUICCInitProcTbl[USIMM_CDMA_APP].ulListNum = ARRAYSIZE(g_aVIACSIMInitProcFuncTbl);

        g_aICCInitProcTbl[USIMM_CDMA_APP].pFuncList = g_aVIAUIMInitProcFuncTbl;
        g_aICCInitProcTbl[USIMM_CDMA_APP].ulListNum = ARRAYSIZE(g_aVIAUIMInitProcFuncTbl);
    }
    else
    {
        g_aUICCInitProcTbl[USIMM_CDMA_APP].pFuncList = g_aCSIMInitProcFuncTbl;
        g_aUICCInitProcTbl[USIMM_CDMA_APP].ulListNum = ARRAYSIZE(g_aCSIMInitProcFuncTbl);

        g_aICCInitProcTbl[USIMM_CDMA_APP].pFuncList = g_aUIMInitProcFuncTbl;
        g_aICCInitProcTbl[USIMM_CDMA_APP].ulListNum = ARRAYSIZE(g_aUIMInitProcFuncTbl);
    }

    return;
#endif

}

/*****************************************************************************
�� �� ��  :USIMM_COMM_ResetPIN1Global
��������  :��ɿ�PIN��ʼ����ȫ�ֱ����ĳ�ʼ��
�������  :��
�������  :��
�� �� ֵ  :��
�޶���¼  :
1. ��    ��   : 2015��2��26��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_ResetPIN1Global(VOS_VOID)
{
    VOS_UINT32          i;

    for (i = 0; i < ARRAYSIZE(g_astUSIMMAppPIN1Info); i++)
    {
        if (g_astUSIMMAppPIN1Info[i].ucPINLen != 0)
        {
            continue;
        }

        g_astUSIMMAppPIN1Info[i].enPinEnable    = USIMM_PIN_ENABLE_BUTT;
        g_astUSIMMAppPIN1Info[i].enPinVerified  = USIMM_PIN_VERIY_BUTT;
    }

    return;
}


USIMM_INITAPPLIST_FUNC* USIMM_COMM_GetAppInitList(
    USIMM_PHYCARD_TYPE_ENUM_UINT32          enCardType,
    USIMM_CARDAPP_ENUM_UINT32               enAppType
)
{
    if (USIMM_PHYCARD_TYPE_UICC == enCardType)
    {
        return g_aUICCInitProcTbl[enAppType].pFuncList;
    }

    if (USIMM_PHYCARD_TYPE_ICC == enCardType)
    {
        return g_aICCInitProcTbl[enAppType].pFuncList;
    }

    return VOS_NULL_PTR;
}


VOS_UINT32 USIMM_COMM_GetAppInitNum(
    USIMM_PHYCARD_TYPE_ENUM_UINT32          enCardType,
    USIMM_CARDAPP_ENUM_UINT32               enAppType
)
{
    if (USIMM_PHYCARD_TYPE_UICC == enCardType)
    {
        return g_aUICCInitProcTbl[enAppType].ulListNum;
    }

    if (USIMM_PHYCARD_TYPE_ICC == enCardType)
    {
        return g_aICCInitProcTbl[enAppType].ulListNum;
    }

    return 0;
}


VOS_UINT32 USIMM_COMM_IsGcfSim(
    VOS_UINT8                          *pucATR,
    VOS_UINT32                          ulATRLen
)
{
    VOS_UINT8                           aucAtrStub[2] = {0x3B, 0x00};
    OM_SIM_ATR_FLAG_STRU                stFlag;

    stFlag.ulSimAtrFlag = VOS_FALSE;

    /* ���´�����GCF����׮����NV���ʱ����ATRΪ3B 00ʱ����Ҫ����Ϊ��ǰ��SIM�� */
    if (VOS_OK != NV_Read(en_NV_Item_Sim_ATR_Flag, &stFlag, sizeof(stFlag)))
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == stFlag.ulSimAtrFlag)
    {
        return VOS_FALSE;
    }

    if (ulATRLen != sizeof(aucAtrStub))
    {
        return VOS_FALSE;
    }

    /*lint -e534*/
    if (VOS_OK == VOS_MemCmp(pucATR, aucAtrStub, sizeof(aucAtrStub)))
    {
        return VOS_TRUE;
    /*lint +e534*/
    }

    return VOS_FALSE;
}

/*****************************************************************************
�� �� ��  :USIMM_COMM_DecodeATR
��������  :����ATR����
�������  :��
�������  :��
�� �� ֵ  :USIMM_COMMINIT_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��13��
    ��    ��   : zhuli
    �޸�����   : Creat

*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_COMM_DecodeATR(VOS_VOID)
{
    VOS_INT32                           lSCIResult;
    VOS_UINT32                          ulATRLen     = 0;
    VOS_UINT8                           aucATR[USIMM_ATR_MAX_LEN] = {0};
    VOS_UINT32                          ulHistoryLen;
    SCI_ATRINFO_S                       stSCIATRInfo;

    lSCIResult = mdrv_sci_get_atr((VOS_ULONG*)&ulATRLen, aucATR, &stSCIATRInfo);

    if ((USIMM_SCI_SUCCESS != lSCIResult) || (ulATRLen > sizeof(aucATR)))
    {
        USIMM_ERROR_LOG("USIMM_COMM_DecodeATR:USIMMSCIGetATR get ATR Error");

        return USIMM_COMM_INIT_FATAL_FAIL;
    }

    if (VOS_OK != USIMM_DecideTMode(&stSCIATRInfo))
    {
        USIMM_ERROR_LOG("USIMM_COMM_DecodeATR:USIMM_DecideTMode Error");

        return USIMM_COMM_INIT_FATAL_FAIL;
    }

    /* ֪ͨ����ǰ֧��Tģʽ,ʧ��ֻ����ӡ */
    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, WUEPS_PID_USIM, WUEPS_PID_USIM, USIMMDL_DRV_USIMMSCI_T1_PRTCL_SWITCH_2);

    if (VOS_OK != mdrv_sci_switch_protocol((PROTOCOL_MODE_E)g_enUSIMMTMode))
    {
        USIMM_WARNING_LOG("USIMM_COMM_DecodeATR:SET T MODE FAILED");

        /* ��ά�ɲ���Ϣͳ�� */
        g_stT1StatisticInfo.ulProtocolSwitchFailCnt++;
    }

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    USIMM_SciDataHook(ulATRLen, aucATR);

    /* �ж��Ƿ�ΪGCF����ʹ�õ�SIM�� */
    if (VOS_TRUE == USIMM_COMM_IsGcfSim(aucATR, ulATRLen))
    {
        USIMM_CCB_SetTestCardType(USIMM_TEST_TYPE_GCF_SIM);

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    ulHistoryLen = aucATR[USIMM_ATR_T0_OFFSET] & 0x0F;  /*��ȡATR��ʷ�ֽڳ���*/

    if (ulATRLen < (ulHistoryLen + 1))
    {
        USIMM_ERROR_LOG("USIMM_COMM_DecodeATR:USIM ATR Length Error");
    }

    return USIMM_COMM_INIT_SUCC;
}


USIMM_CARDAPP_ENUM_UINT32 USIMM_COMM_GetMainAppType(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i = 0; i < USIMM_CARDAPP_BUTT; i++)
    {
        /* �ҵ���ͨ��*/
        if (0 == USIMM_CCB_GetAppChNO(i))
        {
            return i;
        }
    }

    USIMM_ERROR_LOG("USIMM_COMM_GetMainAppType: No main application.");

    return USIMM_CARDAPP_BUTT;
}
VOS_VOID USIMM_COMM_GetTerminalProfile(
    USIMM_STK_CFG_STRU                 *pstProfileContent
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucUsimProfile[] = STK_USIM_PROFILE_DEFAULT;
    VOS_UINT8                           aucSimProfile[]  = STK_SIM_PROFILE_DEFAULT;

    /*��ȡNV���жϵ�ǰ��SAT״̬*/
    ulResult = NV_Read(en_NV_Item_TerminalProfile_Set, pstProfileContent, sizeof(USIMM_STK_CFG_STRU));

    if (NV_OK == ulResult)/*��ȡʧ�ܰ���Ĭ���·�*/
    {
        return;
    }

    USIMM_WARNING_LOG("USIMM_COMM_GetTerminalProfile: NV_Read Failed");

    if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
    {
        /*lint -e534*/
        VOS_MemCpy(pstProfileContent->stUsimProfile.aucProfile, aucUsimProfile, sizeof(aucUsimProfile));
        /*lint +e534*/

        pstProfileContent->stUsimProfile.ucProfileLen = sizeof(aucUsimProfile);
    }
    else if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        /*lint -e534*/
        VOS_MemCpy(pstProfileContent->stSimProfile.aucProfile, aucSimProfile, sizeof(aucSimProfile));
        /*lint +e534*/

        pstProfileContent->stSimProfile.ucProfileLen = sizeof(aucSimProfile);
    }
    else
    {
        USIMM_WARNING_LOG("USIMM_COMM_GetTerminalProfile: Card Type Failed");
    }

    return;
}


VOS_UINT32 USIMM_COMM_InitPINApp(VOS_VOID)
{
    USIMM_COMMINIT_RST_ENUM_UINT32      enInitRlst;

    enInitRlst = USIMM_COMM_InitCardApps();

    if (USIMM_COMM_INIT_RESET == enInitRlst)
    {
        if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
        {
            enInitRlst = USIMM_UICC_InitCard();
        }
        else if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
        {
            enInitRlst = USIMM_ICC_InitCard();
        }
        else
        {
            USIMM_ERROR_LOG("USIMM_COMM_InitPINApp: Card Type Failed");
        }
    }

    if (USIMM_COMM_INIT_SUCC != enInitRlst)
    {
        USIMM_ERROR_LOG("USIMM_COMM_InitPINApp: Card Init Failed");

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_COMM_InitCard(
    USIMM_MsgBlock                     *pstMsg
)
{
    USIMM_COMMINIT_RST_ENUM_UINT32      enCommRslt;

    /* UICC����ʼ���ɹ� */
    enCommRslt = USIMM_UICC_InitCard();

    /* UICC����ʼ���ɹ� */
    if (USIMM_COMM_INIT_SUCC == enCommRslt)
    {
        USIMM_CCB_SetMainAppType(USIMM_COMM_GetMainAppType());

        return VOS_OK;
    }

    /* ������ʹ�� */
    if (USIMM_COMM_INIT_FATAL_FAIL == enCommRslt)
    {
        USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_NOCARD);

        USIMM_WARNING_LOG("USIMM_COMM_InitCard: Init card fail during UICC procedure.");

        return VOS_ERR;
    }

    USIMM_WARNING_LOG("USIMM_COMM_InitCard: Switch to ICC card.");

    USIMM_ResetGlobalVar();

    /* ICC����ʼ�� */
    if (USIMM_COMM_INIT_SUCC == USIMM_ICC_InitCard())
    {
        USIMM_CCB_SetMainAppType(USIMM_COMM_GetMainAppType());

        return VOS_OK;
    }

    USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_NOCARD);

    USIMM_WARNING_LOG("USIMM_COMM_InitCard: Init card fail during ICC procedure.");

    return VOS_ERR;
}

/*****************************************************************************
�� �� ��  : USIMM_COMM_InitCardApps
��������  : ��ʼ����ǰ����Ӧ���б�
�������  : ��
�������  : ��
�� �� ֵ  : USIMM_COMMINIT_RST_ENUM_UINT32
�޶���¼  :
1. ��    ��   : 2015-3-10
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_COMM_InitCardApps(VOS_VOID)
{
    VOS_UINT32                          ulAppNum;
    VOS_UINT32                          i;
    USIMM_INITSTEPS_RST_ENUM_UINT32     enStepResult;
    USIMM_INITAPPS_RST_ENUM_UINT32      enAppResult;
    VOS_UINT32                          ulSuccessNum;

    ulAppNum = USIMM_COMM_GetAppInitFuncs();

    if (0 == ulAppNum)
    {
        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    ulSuccessNum = 0;

    for (i = 0; i < ulAppNum; i++)
    {
        if ((USIMM_INITAPPS_FAIL == g_astUSIMMInitAppCtrl[i].enAppInitResult)
            ||(VOS_NULL_PTR == g_astUSIMMInitAppCtrl[i].pfList))
        {
            USIMM_WARNING_LOG("USIMM_COMM_InitCardApps: Jump Over a APP");

            continue;
        }

        if (USIMM_INITSTEPS_SUCCESS == g_astUSIMMInitAppCtrl[i].enAppStepResult)
        {
            (VOS_VOID)USIMM_COMM_InitAppState(g_astUSIMMInitAppCtrl[i].ucChannelNo);

            ulSuccessNum++;

            continue;
        }

        enStepResult = USIMM_INITSTEPS_SUCCESS;

        if (VOS_NULL_BYTE == g_astUSIMMInitAppCtrl[i].ucChannelNo)
        {
            if (ulSuccessNum != 0)
            {
                enStepResult = UISMM_UICC_InitCardOpenChannel(&g_astUSIMMInitAppCtrl[i]);
            }
            else
            {
                g_astUSIMMInitAppCtrl[i].ucChannelNo = 0;
            }
        }

        if (USIMM_INITSTEPS_SUCCESS == enStepResult)
        {
            enStepResult = USIMM_COMM_InitAppList(&g_astUSIMMInitAppCtrl[i]);
        }
        else
        {
            USIMM_WARNING_LOG("USIMM_COMM_InitCardApps: Open Channel is Fail");
        }

        g_astUSIMMInitAppCtrl[i].ucInitTimes++;

        enAppResult = USIMM_COMM_CheckInitStepResult(enStepResult, &g_astUSIMMInitAppCtrl[i]);

        g_astUSIMMInitAppCtrl[i].enAppInitResult = enAppResult;

        g_astUSIMMInitAppCtrl[i].enAppStepResult = enStepResult;

        if (USIMM_INITAPPS_SUCCESS == enAppResult)
        {
            ulSuccessNum++;
        }
        else
        {
            USIMM_COMM_ResetInitGlobal();

            /* ���ֻ��һ��Ӧ�÷���APP ��ʼ��ʧ�ܣ��е�ICC��ʼ�� */
            if ((1 == ulAppNum)
             && (USIMM_INITAPPS_FAIL == enAppResult))
            {
                break;
            }
            else
            {
                return USIMM_COMM_INIT_RESET;
            }
        }
    }

    if (0 == ulSuccessNum)
    {
        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
�� �� ��  : USIMM_COMM_GetAppInitFuncs
��������  : ��ȡ��ǰApp��ʼ���ĺ���
�������  : ��
�������  : ��
�� �� ֵ  : ��
�޶���¼  :
1. ��    ��   : 2015-3-10
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_COMM_GetAppInitFuncs(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i = 0; i < ARRAYSIZE(g_astUSIMMInitAppCtrl); i++)
    {
        /* �ҵ�����λ�� */
        if (USIMM_CARDAPP_BUTT <= g_astUSIMMInitAppCtrl[i].enAppType)
        {
            break;
        }
    }

    return i;
}

/*****************************************************************************
�� �� ��  : USIMM_InitAppList
��������  : ִ�е�ǰ��Ҫ��ʼ��Ӧ�õ�ĳһ���б�ľ�������
�������  : pstInitList: ��ǰӦ�õĳ�ʼ���б�����
�������  : ��
�� �� ֵ  : USIMM_INITSTEPS_RST_ENUM_UINT32
�޶���¼  :
1. ��    ��   : 2015-3-10
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_COMM_InitAppList(
    USIMM_INITAPPSCTRL_STRU            *pstInitList
)
{
    VOS_UINT32                          i;
    USIMM_INITSTEPS_RST_ENUM_UINT32     enResult;
    USIMM_INITAPPLIST_FUNC              *pStepList;

    pStepList = pstInitList->pfList;

    enResult = USIMM_INITSTEPS_SUCCESS;

    for (i = pstInitList->ucCurStep; i < pstInitList->ucInitListNum; i++)
    {
        if (pStepList[i].enStatus != USIMM_FUNC_AVAILABLE)
        {
            continue;
        }

        enResult = pStepList[i].pProcFun(pstInitList->ucChannelNo);

        if (USIMM_INITSTEPS_REMOVE == enResult)
        {
            pStepList[i].enStatus = USIMM_FUNC_UNAVAILABLE;
        }
        else if ((USIMM_INITSTEPS_SUSPEND == enResult)
              || (USIMM_INITSTEPS_FAIL == enResult))
        {
            break;
        }
        else if (USIMM_INITSTEPS_FAIL_REMOVE == enResult)
        {
            pStepList[i].enStatus = USIMM_FUNC_UNAVAILABLE;

            enResult = USIMM_INITSTEPS_FAIL;

            break;
        }
        else
        {
            continue;
        }
    }

    pstInitList->ucCurStep = (VOS_UINT8)i;

    return enResult;
}

/*****************************************************************************
�� �� ��  : USIMM_CheckInitStepResult
��������  : ���Ӧ�÷��صĽ��
�������  : enResult: �����ʼ���Ĺ��̵Ľ��
            pstInitList: Ӧ�ó�ʼ���Ŀ�����Ϣ
�������  : ��
�� �� ֵ  : USIMM_INITAPPS_RST_ENUM_UINT32
�޶���¼  :
1. ��    ��   : 2015-3-15
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITAPPS_RST_ENUM_UINT32 USIMM_COMM_CheckInitStepResult(
    USIMM_INITSTEPS_RST_ENUM_UINT32         enResult,
    USIMM_INITAPPSCTRL_STRU                *pstInitList
)
{
    switch (enResult)
    {
        case USIMM_INITSTEPS_SUCCESS:
            pstInitList->ucCurStep   = 0;
            pstInitList->ucInitTimes = 0;
            return USIMM_INITAPPS_SUCCESS;

        case USIMM_INITSTEPS_SUSPEND:
            pstInitList->ucInitTimes = 0;
            return USIMM_INITAPPS_SUCCESS;

        case USIMM_INITSTEPS_FAIL:
        case USIMM_INITSTEPS_FAIL_REMOVE:
            pstInitList->ucCurStep   = 0;

            if (pstInitList->ucInitTimes >= USIMM_INITAPPS_TIMES_MAX)
            {
                return USIMM_INITAPPS_FAIL;
            }
            else
            {
                return USIMM_INITAPPS_RESET;
            }

        default:
            return USIMM_INITAPPS_SUCCESS;
    }
}

/*****************************************************************************
�� �� ��  :USIMM_COMM_AutoVerifyPIN
��������  :�Զ���֤PIN
�������  :pstPIN1Info -- ��ǰPIN Info
�������  :pstPIN1Info -- ��ǰPIN Info
�� �� ֵ  : VOS_OK/VOS_ERR
�޶���¼  :
1. ��    ��    : 2015-3-10
    ��    ��   : zhuli
    �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_COMM_AutoVerifyPIN(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_COMM_CARD_APP_INFO_STRU      *pstAppInfo;
    VOS_UINT32                          ulResult;
    USIMM_APDU_RSP_STRU                 stRspData;
    USIMM_APP_PIN_INFO_STRU            *pstPIN1Info;
    VOS_UINT8                           ucPIN1No;

    pstAppInfo = USIMM_CCB_GetAppInfoByCH(ucChannelNo);

    if (VOS_NULL_PTR == pstAppInfo)
    {
        return USIMM_INITSTEPS_FAIL;
    }

    ucPIN1No = pstAppInfo->stCurFileInfo.stDFInfo.ucPIN1RefNum;

    if ((ucPIN1No < 1)||(ucPIN1No > 8))
    {
        return USIMM_INITSTEPS_FAIL;
    }

    pstPIN1Info = USIMM_CCB_GetPIN1InfoByRef(ucPIN1No);

    if (VOS_NULL_PTR == pstPIN1Info)
    {
        return USIMM_INITSTEPS_FAIL;
    }

    if (VOS_NULL == pstPIN1Info->ucPINLen)  /*��ǰPIN����Ч����Ҫ�ϱ���״̬*/
    {
        return USIMM_INITSTEPS_SUCCESS;
    }

    if ( (USIMM_PIN_ENABLED == pstPIN1Info->enPinEnable)
        &&(USIMM_PIN_NEED == pstPIN1Info->enPinVerified) )
    {
        USIMM_NORMAL_LOG("USIMM_COMM_AutoVerifyPIN: Need Verify The Pin");

        /* �ɹ�У���PIN�룬���Զ�У��PIN�� */
        ulResult = USIMM_SendVerifyPinApdu(ucChannelNo,
                                           USIMM_PINCMD_VERIFY,
                                           pstPIN1Info->ucPINRefNum,
                                           pstPIN1Info->aucPin,
                                           &stRspData);

        if (VOS_OK != ulResult)/*�����*/
        {
            USIMM_ERROR_LOG("USIMM_COMM_AutoVerifyPIN: USIMM_PINVerify_APDU Error");

            return USIMM_INITSTEPS_FAIL;
        }

        pstPIN1Info->enPinVerified = USIMM_PIN_NONEED;
    }

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  : USIMM_COMM_InitAppState
��������  : �жϵ�ǰ��Ӧ��״̬
�������  : ucChannelNo �߼�ͨ����
�������  : ��
�� �� ֵ  : USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015-3-10
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_COMM_InitAppState(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_CARD_SERVIC_ENUM_UINT32       enProCardService;
    USIMM_COMM_CARD_APP_INFO_STRU      *pstAppInfo;
    USIMM_APP_PIN_INFO_STRU            *pstPIN1Info;
    VOS_UINT8                           ucPIN1No;
    USIMM_INITSTEPS_RST_ENUM_UINT32     enResult;

    pstAppInfo = USIMM_CCB_GetAppInfoByCH(ucChannelNo);

    if (VOS_NULL_PTR == pstAppInfo)
    {
        return USIMM_INITSTEPS_FAIL;
    }

    enProCardService = pstAppInfo->enAppService;    /*���浱ǰ�Ŀ�״̬*/

    ucPIN1No = pstAppInfo->stCurFileInfo.stDFInfo.ucPIN1RefNum;

    if ((ucPIN1No < 1)||(ucPIN1No > 8))
    {
        return USIMM_INITSTEPS_FAIL;
    }

    pstPIN1Info = USIMM_CCB_GetPIN1InfoByRef(ucPIN1No);

    if (VOS_NULL_PTR == pstPIN1Info)
    {
        return USIMM_INITSTEPS_FAIL;
    }

    /*��������״̬�жϿ�״̬*/
    if (USIMM_PUK_BLOCK == pstPIN1Info->enPinVerified)/*�ж�PUK BLOCK״̬*/
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitAppState: PUK is Block");

        pstAppInfo->stPinInfo.enCurPINType  = USIMM_PUK;

        pstAppInfo->enAppService            = USIMM_CARD_SERVIC_UNAVAILABLE;

        enResult                            = USIMM_INITSTEPS_SUSPEND;
    }
    else if(USIMM_PUK_NEED == pstPIN1Info->enPinVerified)/*�ж�PUK״̬*/
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitAppState: The Card Need the PUK Password");

        pstAppInfo->stPinInfo.enCurPINType  = USIMM_PUK;

        pstAppInfo->enAppService            = USIMM_CARD_SERVIC_SIM_PUK;

        enResult                            = USIMM_INITSTEPS_SUSPEND;
    }
    else if(USIMM_PIN_NEED == pstPIN1Info->enPinVerified) /*���жϵ�ǰPIN1״̬*/
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitAppState: The Card Need the PIN Password");

        pstAppInfo->stPinInfo.enCurPINType  = USIMM_PIN;

        pstAppInfo->enAppService            = USIMM_CARD_SERVIC_SIM_PIN;

        enResult                            = USIMM_INITSTEPS_SUSPEND;
    }
    else if(USIMM_PUK_NEED == pstAppInfo->stPinInfo.stPin2Info.enPinVerified)   /*���ж�PUK2״̬*/
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitAppState: The Card Need the PUK2 Password");

        pstAppInfo->stPinInfo.enCurPINType  = USIMM_PUK2;

        pstAppInfo->enAppService            = USIMM_CARD_SERVIC_AVAILABLE;

        enResult                            = USIMM_INITSTEPS_SUCCESS;
    }
    else  /*���ж�PIN2״̬*/                                                                                  /*���Ĭ����ҪPIN2*/
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitAppState: The Card Need the PIN2 Password");

        pstAppInfo->stPinInfo.enCurPINType  = USIMM_PIN2;

        pstAppInfo->enAppService            = USIMM_CARD_SERVIC_AVAILABLE;

        enResult                            = USIMM_INITSTEPS_SUCCESS;
    }

    if (enProCardService != pstAppInfo->enAppService )
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitAppState: The Card State is Changed, Need Report the Card State");

        USIMM_CCB_SetAppStateChange(pstAppInfo->enAppType, USIMM_CARD_STATE_CHANGED);
    }

    return enResult;
}

/*****************************************************************************
�� �� ��  :USIMM_COMM_InitPINState
��������  :��ʼӦ�õ�ǰ��PIN����
�������  :pstPINInfo -- PIN��Ϣ
�������  :pstPINInfo -- PIN��Ϣ
�� �� ֵ  :��

�޶���¼  :
1. ��    ��   : 2015-3-10
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_InitPINState(
    USIMM_APP_PIN_INFO_STRU            *pstPINInfo
)
{
    pstPINInfo->enPinVerified = USIMM_PIN_NONEED;

    if(USIMM_PIN_ENABLED == pstPINInfo->enPinEnable)
    {
        if (0 != pstPINInfo->ucPinRemainTime)
        {
            USIMM_NORMAL_LOG("USIMM_COMM_InitPINState: Set USIMM_PIN_NEED");

            pstPINInfo->enPinVerified = USIMM_PIN_NEED;
        }
    }

    if (0 == pstPINInfo->ucPinRemainTime)
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitPINState: Set USIMM_PUK_NEED");

        pstPINInfo->enPinVerified = USIMM_PUK_NEED;
    }

    if (0 == pstPINInfo->ucPukRemainTime)
    {
        USIMM_NORMAL_LOG("USIMM_COMM_InitPINState: Set USIMM_PUK_BLOCK");

        pstPINInfo->enPinVerified = USIMM_PUK_BLOCK;
    }

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_COMM_SaveDFPinInfo
��������  :����Ӧ��ADF PIN����Ϣ
�������  :enAppType Ӧ������
�������  :��
�� �� ֵ  :��

�޶���¼  :
1. ��    ��   : 2015-3-10
   ��    ��   : ganlan
   �޸�����   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_SaveDFPinInfo(
    USIMM_CARDAPP_ENUM_UINT32               enAppType
)
{
    USIMM_DFFCP_ST                     *pstDFInfo;
    USIMM_APP_PIN_INFO_STRU            *pstPin1Info;
    USIMM_APP_PIN_INFO_STRU            *pstPin2Info;

    pstDFInfo = USIMM_CCB_GetCurDFInfo(enAppType);

    if (VOS_NULL_PTR == pstDFInfo)
    {
        USIMM_ERROR_LOG("USIMM_COMM_SaveDFPinInfo: The DFInfo is Error");

        return;
    }

    /* ����PIN1ʹ�õ�KeyReference */
    USIMM_CCB_GetPINInfo(enAppType)->enPinKeyRef = pstDFInfo->ucPIN1RefNum;

    pstPin1Info = USIMM_CCB_GetPIN1InfoByRef(pstDFInfo->ucPIN1RefNum);

    if (VOS_NULL_PTR == pstPin1Info)
    {
        USIMM_ERROR_LOG("USIMM_COMM_SaveDFPinInfo: The pstPin1Info is Error");

        return;
    }

    pstPin2Info = USIMM_CCB_GetPIN2InfoByApp(enAppType);

    if (VOS_NULL_PTR == pstPin2Info)
    {
        USIMM_ERROR_LOG("USIMM_COMM_SaveDFPinInfo: The pstPin2Info is Error");

        return;
    }

    /* ICC��PIN��ʣ����Ϣ�����DF�ļ��� */
    if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        pstPin1Info->ucPinRemainTime = pstDFInfo->stPINInfo.ucPin1RemainTime;  /* PIN1��ʣ�����      */
        pstPin2Info->ucPinRemainTime = pstDFInfo->stPINInfo.ucPin2RemainTime;  /* PIN2��ʣ�����      */
        pstPin1Info->ucPukRemainTime = pstDFInfo->stPINInfo.ucPuk1RemainTime;  /* PUK1��ʣ�����     */
        pstPin2Info->ucPukRemainTime = pstDFInfo->stPINInfo.ucPuk2RemainTime;  /* PUK2��ʣ�����     */
    }

    pstPin1Info->enPinEnable     = pstDFInfo->stPINInfo.enPin1Enable;           /* PIN1����״̬        */
    pstPin2Info->enPinEnable     = pstDFInfo->stPINInfo.enPin2Enable;           /* PIN2����״̬        */
    pstPin1Info->ucPINRefNum     = pstDFInfo->ucPIN1RefNum;
    pstPin2Info->ucPINRefNum     = pstDFInfo->ucPIN2RefNum;

    return;
}

/*****************************************************************************
�� �� ��  : USIMM_COMM_StoreAppSN
��������  : ��·���жϵ�ǰ������������
�������  : enAppType Ӧ������
�������  : ��
�� �� ֵ  : ��
���ú���  : ��
��������  :
�޶���¼  :
1. ��    ��   : 2015-3-10
   ��    ��   : ganlan
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_COMM_StoreAppSN(
    USIMM_CARDAPP_ENUM_UINT32               enAppType
)
{
    VOS_UINT32                              i;

    /* ������� */
    if (USIMM_UNLIMIT_APP_BUTT <= enAppType)
    {
        return;
    }

    /* UE��֧��IMS�򲻳�ʼ��ISIMӦ�� */
#if (FEATURE_OFF == FEATURE_IMS)
    if (USIMM_IMS_APP == enAppType)
    {
        return;
    }
#endif

    if (VOS_FALSE == USIMM_IsCLEnable())
    {
    /* UE��֧��CDMA�򲻳�ʼ��CSIM��UIMӦ�� */
#if (FEATURE_OFF == FEATURE_UE_MODE_CDMA)
        if (USIMM_CDMA_APP == enAppType)
        {
            return;
        }
#endif
    }

    for (i = 0; i < ARRAYSIZE(g_astUSIMMInitAppCtrl); i++)
    {
        /* �Ѿ��б��� */
        if (enAppType == g_astUSIMMInitAppCtrl[i].enAppType)
        {
            return;
        }

        /* �ҵ�����λ�� */
        if (USIMM_CARDAPP_BUTT <= g_astUSIMMInitAppCtrl[i].enAppType)
        {
            g_astUSIMMInitAppCtrl[i].enAppType     = enAppType;
            g_astUSIMMInitAppCtrl[i].pfList        = USIMM_COMM_GetAppInitList(USIMM_CCB_GetCardType(),enAppType);
            g_astUSIMMInitAppCtrl[i].ucInitListNum = (VOS_UINT8)USIMM_COMM_GetAppInitNum(USIMM_CCB_GetCardType(),enAppType);

            return;
        }
    }

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_COMM_IsAndroidPhone
��������  :��ʼUSIM��ȫ�ֱ���
�������  :��
�������  :��
�� �� ֵ  :VOS_OK

�޶���¼  :
1. ��    ��   : 2015-3-10
   ��    ��   : ganlan
   �޸�����   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_COMM_IsAndroidPhone(VOS_VOID)
{
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU stSysAppCfg;

    /* Ĭ�����öԽ�MP */
    stSysAppCfg.usSysAppConfigType = SYSTEM_APP_MP;

    if (NV_OK != NV_Read(en_NV_Item_System_APP_Config, &stSysAppCfg, sizeof(NAS_NVIM_SYSTEM_APP_CONFIG_STRU)))
    {
        USIMM_ERROR_LOG("USIMM_COMM_IsAndroidPhone: Read en_NV_Item_System_APP_Config Failed");
    }

    if (SYSTEM_APP_ANDROID == stSysAppCfg.usSysAppConfigType)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
�� �� ��  :USIMM_COMM_GetMecrpValue
��������  :��ȡNV�еĶ���ֵ
�������  :��
�������  :��
�� �� ֵ  :VOS_OK

�޶���¼  :
1. ��    ��   : 2015-3-10
   ��    ��   : ף�
   �޸�����   : Creat

*****************************************************************************/

VOS_UINT32 USIMM_COMM_GetMecrpValue(
    VOS_UINT8                           *pucSCM, 
    VOS_UINT8                           *pucMOBP)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    CAS_1X_NVIM_CAPA_INFO_STRU          stNVInfo;

    if (NV_OK != NV_Read(en_NV_Item_CAS_1X_NVIM_CAPA_INFO, &stNVInfo, sizeof(CAS_1X_NVIM_CAPA_INFO_STRU)))
    {
        USIMM_ERROR_LOG("USIMM_COMM_GetMecrpValue: NV_Read is Fail");

        return VOS_ERR;
    }

    *pucMOBP = stNVInfo.ucMobPRev;

    *pucSCM = (VOS_UINT8)(USIMM_CDMA_DEFAULT_SCM | (((VOS_UINT32)(stNVInfo.enSlottedClass))<< 5)
                        |(((VOS_UINT32)(stNVInfo.enSupportMeid)) << 4)
                        |(((VOS_UINT32)(stNVInfo.enTransMode))   << 2));
#endif

    return VOS_OK;
}


/*****************************************************************************
�� �� ��  :USIMM_COMM_InitOPFile
��������  :��ʼUSIM��ȫ�ֱ���
�������  :��
�������  :��
�� �� ֵ  :VOS_OK

�޶���¼  :
1. ��    ��   : 2015-3-10
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
VOS_VOID USIMM_COMM_InitOPFile(VOS_VOID)
{
    if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
    {
        USIMM_UICC_ReadUsimOPFile();
    }
    else if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        USIMM_ICC_ReadSimOPFile();
    }
    else
    {
        ;
    }

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitStoreMeid
��������  :��ʼCSIM��������MANAGE ESN MEID
�������  :ucChannelNo:Channel Number
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_SUCCESS/USIMM_INITSTEPS_REMOVE

�޶���¼  :
1. ��    ��   : 2015��3��10��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitStoreMeid(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    NV_MEID_STRU                        stMeId;
    USIMM_APDU_RSP_STRU                 stRspData = {0};
    VOS_UINT8                           aucMeid[USIMM_STORE_ESNMEID_MAX];

    USIMM_NORMAL_LOG("USIMM_UICC_InitStoreMeid: Step is Begin");

    if (NV_OK != NV_Read(en_NV_Item_MEID, &stMeId, sizeof(stMeId)))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitStoreMeid: NV_Read en_NV_Item_MEID Failed");

        return USIMM_INITSTEPS_FAIL;
    }

    aucMeid[0] = MEID_NV_DATA_LEN_NEW;

    (VOS_VOID)VOS_MemCpy(aucMeid + 1, stMeId.aucMeID, MEID_NV_DATA_LEN_NEW);

    ulResult = USIMM_SendStoreESNMEIDApdu(UICC_STORE_MEID_P1,
                                          ucChannelNo,
                                          aucMeid,
                                          &stRspData);

    if (VOS_OK == ulResult)
    {
        g_ucStoreEsMeidResult = stRspData.aucRsp[0];

        USIMM_NORMAL_LOG("USIMM_UICC_InitStoreMeid: Step is OK");

        return USIMM_INITSTEPS_SUCCESS;
    }

    USIMM_ERROR_LOG("USIMM_UICC_InitStoreMeid: Command Send error");

    g_ucStoreEsMeidResult = VOS_NULL;

    /* ���˲����Ƴ����������� */
    return USIMM_INITSTEPS_REMOVE;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_DecodeAppAid
��������  :�����ļ����ݽ�����Ӧ��AID
�������  :pucdata
     ��    usFileLen
           ucRecordLen
�������  :��
�� �� ֵ  :USIMM_COMMINIT_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015-3-10
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_DecodeAppAid(
    VOS_UINT8                          *pucdata,
    VOS_UINT16                          usFileLen,
    VOS_UINT8                           ucRecordLen
)
{
    USIMM_COMMINIT_RST_ENUM_UINT32      enResult;
    VOS_UINT32                          i;
    VOS_UINT32                          ulAidLen;
    VOS_UINT8                           aucUsimRidAppCode[USIMM_RID_LEN + USIMM_APP_CODE_LEN] = {0xA0,0x00,0x00,0x00,0x87,0x10,0x02};
    VOS_UINT8                           aucIsimRidAppCode[USIMM_RID_LEN + USIMM_APP_CODE_LEN] = {0xA0,0x00,0x00,0x00,0x87,0x10,0x04};
    VOS_UINT8                           aucCsimRidAppCode[USIMM_RID_LEN + USIMM_APP_CODE_LEN] = {0xA0,0x00,0x00,0x03,0x43,0x10,0x02};
    USIMM_CARDAPP_ENUM_UINT32           enAppType = USIMM_UNLIMIT_APP_BUTT;

    enResult = USIMM_COMM_INIT_NORMAL_FAIL;

    for (i = 0; i < usFileLen; i += ucRecordLen)
    {
        if ((APP_TMP_TAG != pucdata[i + APP_TMP_TAG_OFFSET])
         || (APP_IND_TAG != pucdata[i + APP_IND_TAG_OFFSET]))    /*�ж����ݺϷ���*/
        {
            USIMM_WARNING_LOG("USIMM_UICC_DecodeAppAid: EFDIR Content not Right");/*��ӡ����*/

            continue;
        }

        ulAidLen = (pucdata[i + APP_AID_LEN_OFFSET] > USIMM_AID_LEN_MAX)?USIMM_AID_LEN_MAX:pucdata[i + APP_AID_LEN_OFFSET];

        /* ֻҪƥ�䵽A0000000871002����Ϊ�ҵ���USIM��AID */
        /*lint -e534*/
        if (VOS_OK == VOS_MemCmp(pucdata + i + APP_AID_VALUE_OFFSET, aucUsimRidAppCode, sizeof(aucUsimRidAppCode)))
        {
            enAppType = USIMM_GUTL_APP;
        /*lint +e534*/

            enResult = USIMM_COMM_INIT_SUCC;
        }

        /* ֻҪƥ�䵽A0000000871004����Ϊ�ҵ���ISIM��AID,ĿǰISIM�����ܵ���֧�� */
        /*lint -e534*/
        if (VOS_OK == VOS_MemCmp(pucdata + i + APP_AID_VALUE_OFFSET, aucIsimRidAppCode, sizeof(aucIsimRidAppCode)))
        {
            enAppType = USIMM_IMS_APP;
        /*lint +e534*/

            enResult = USIMM_COMM_INIT_SUCC;
        }

        /* ֻҪƥ�䵽A0000003431002����Ϊ�ҵ���CSIM��AID */
        /*lint -e534*/
        if (VOS_OK == VOS_MemCmp(pucdata + i + APP_AID_VALUE_OFFSET, aucCsimRidAppCode, sizeof(aucCsimRidAppCode)))
        {
            enAppType = USIMM_CDMA_APP;
        /*lint +e534*/

            enResult = USIMM_COMM_INIT_SUCC;
        }

        USIMM_COMM_StoreAppSN(enAppType);

        /*���������Ϣ*/
        USIMM_CCB_SetAIDByApp(enAppType, ulAidLen, &pucdata[i + APP_AID_VALUE_OFFSET]);

        enAppType = USIMM_UNLIMIT_APP_BUTT;
    }

    return enResult;
}


USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_DecodeEFDIR(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                          *pucdata;
    USIMM_COMMINIT_RST_ENUM_UINT32      enInitRslt = USIMM_COMM_INIT_FATAL_FAIL;

    ulResult = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, USIMM_DIR_ID);

    if (VOS_OK != ulResult)/*ѡ���ļ�*/
    {
        USIMM_ERROR_LOG("USIMM_UICC_DecodeEFDIR: EFDIR could not Found");/*��ӡ����*/

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    pucdata = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, USIMM_CCB_GetCurEFInfo(USIMM_UNLIMIT_AUTO)->usFileLen);

    if (VOS_NULL_PTR == pucdata)   /*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_UICC_DecodeEFDIR: VOS_MemAlloc Error");/*��ӡ����*/

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    if (USIMM_EFSTRUCTURE_FIXED == USIMM_CCB_GetCurEFInfo(USIMM_UNLIMIT_AUTO)->enFileType)
    {
        if (USIMM_SW_OK != USIMM_SendReadRecordApdu(USIMM_APDU_BASECHANNEL,
                                                    USIMM_CCB_GetCurEFInfo(USIMM_UNLIMIT_AUTO)->ucRecordNum,
                                                    USIMM_CCB_GetCurEFInfo(USIMM_UNLIMIT_AUTO)->ucRecordLen,
                                                    USIMM_READ_ALLRECORD,
                                                    pucdata))      /*��ȡ��¼����*/
        {
            USIMM_INFO_LOG("USIMM_UICC_DecodeEFDIR: USIMM_ReadLFFile Error");
        }
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_DecodeEFDIR: EFDIR File Type Error");/*��ӡ����*/

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pucdata);
        /*lint +e534*/

        return USIMM_COMM_INIT_NORMAL_FAIL;                                              /*����102.221 13.1 �ڲ�֧�ֶ����Ƹ�ʽ�ļ�*/
    }

    /* �����ļ����ݽ�����Ӧ��AID��*/
    enInitRslt = USIMM_UICC_DecodeAppAid(pucdata,
                                         USIMM_CCB_GetCurEFInfo(USIMM_UNLIMIT_AUTO)->usFileLen,
                                         USIMM_CCB_GetCurEFInfo(USIMM_UNLIMIT_AUTO)->ucRecordLen);

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pucdata);
    /*lint +e534*/

    /* ���һ����Ч��AID��û���ҵ����ش����е�SIM��������ʼ�� */
    if (USIMM_COMM_INIT_SUCC != enInitRslt)
    {
        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    return USIMM_UICC_CUIMCheck();
}

/*****************************************************************************
�� �� ��  : USIMM_UICC_CUIMCheck
��������  : �е��Ż�ȫ��ͨ�汾��麯��
�������  : ��
�������  : ��
�� �� ֵ  : USIMM_COMMINIT_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��6��6��
    ��    ��   : h00300778
    �޸�����   : Creat
*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_CUIMCheck(VOS_VOID)
{
    USIMM_AID_INFO_STRU                *pstAidInfo;

    pstAidInfo = USIMM_CCB_GetAIDByApp(USIMM_CDMA_APP);

    /* ����ǵ��Ű汾��CSIM+USIMʱ���п���ʼ������USIM�ϱ��޿�����CSIMʱ�ϱ��п� */
    if (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulCUIMCheck)
    {
        if (VOS_NULL_PTR == pstAidInfo)
        {
            return USIMM_COMM_INIT_FATAL_FAIL;
        }

        if (VOS_NULL == pstAidInfo->ulAIDLen)
        {
            return USIMM_COMM_INIT_FATAL_FAIL;
        }
    }

    return USIMM_COMM_INIT_SUCC;
}
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_DecodeATRStep2(VOS_VOID)
{
    VOS_UINT32                          ulATRLen                  = 0;
    VOS_UINT8                           aucATR[USIMM_ATR_MAX_LEN] = {0};
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulDataOffset;
    VOS_UINT32                          ulHistoryLen;
    VOS_INT32                           lSCIResult;
    VOS_UINT32                          ulResult;
    SCI_ATRINFO_S                       stSCIATRInfo;

    lSCIResult = mdrv_sci_get_atr((VOS_ULONG*)&ulATRLen, aucATR, &stSCIATRInfo);

    if ((USIMM_SCI_SUCCESS != lSCIResult)
        || (ulATRLen > sizeof(aucATR)))
    {
        USIMM_ERROR_LOG("USIMM_UICC_DecodeATRStep2:USIMMSCIGetATR get ATR Error");

        return USIMM_COMM_INIT_SUCC;
    }

    USIMM_SciDataHook(ulATRLen, aucATR);

    /* ��ȡATR��ʷ�ֽڳ��� */
    ulHistoryLen    = aucATR[USIMM_ATR_T0_OFFSET] & 0x0F;

    /* ��ȡATR��ʷ�ֽڵ���ʼλ�� */
    if ((ulATRLen < ulHistoryLen) || (VOS_NULL == ulHistoryLen))
    {
        return USIMM_COMM_INIT_SUCC;
    }

    ulOffset        = ulATRLen - ulHistoryLen;

    /* 3G������ʷ�ֽ� */
    if (CTLV_IND_TAG == aucATR[ulOffset])
    {
        ulOffset++; /* ָ�����ĵ�һ��Tag */

        if (ulOffset >= sizeof(aucATR))
        {
            return USIMM_COMM_INIT_SUCC;
        }

        ulHistoryLen--;

        /*�����������ֽ�*/
        ulResult = USIMM_FindTagInCTLV(&aucATR[ulOffset], CARD_CPB_TAG, ulHistoryLen);

        if (USIMM_TAGNOTFOUND != ulResult)
        {
            if (ulResult > ulHistoryLen)
            {
                return USIMM_COMM_INIT_SUCC;
            }

            ulDataOffset = ulResult + ulOffset;

            if (ulDataOffset >= sizeof(aucATR))
            {
                return USIMM_COMM_INIT_SUCC;
            }

            gstUSIMMBaseInfo.enSupportPath = USIMM_GetBitFromBuf(&aucATR[ulDataOffset], 6, sizeof(VOS_UINT8));

            gstUSIMMBaseInfo.enSupportSFI  = USIMM_GetBitFromBuf(&aucATR[ulDataOffset], 3, sizeof(VOS_UINT8));

            if (CARD_CPB3_TAG == aucATR[ulDataOffset-1])
            {
                if ((ulDataOffset + 1) >= sizeof(aucATR))
                {
                    return USIMM_COMM_INIT_SUCC;
                }

                gstUSIMMBaseInfo.enSupportChannel = (((aucATR[ulDataOffset+1]&0x10) != 0)?USIMM_SUPPORT_CHANNEL:USIMM_NOTSUPPORT_CHANNEL);
            }
        }
    }

    return USIMM_COMM_INIT_SUCC;
}
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_InitGlobalVar(VOS_VOID)
{
    USIMM_COMM_ResetPIN1Global();

    USIMM_PoolDelAll(); /*�����ڴ��ظ���ӣ����ͷ�����ڴ�*/

    gstUSIMMBaseInfo.ucCLA      = USIMM_USIM_CLA;

    return USIMM_COMM_INIT_SUCC;
}
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_InitCardTypeByATR(VOS_VOID)
{
    VOS_UINT32                          ulErrlogNumber;
    OAM_MNTN_NO_SIM_CARD_EVENT_STRU     stNoSimCard;
    USIMM_COMMINIT_RST_ENUM_UINT32      enInitRslt        = USIMM_COMM_INIT_FATAL_FAIL;
    VOS_INT32                           lVoltageSwitchRst = USIMM_SCI_NONEED_CHANGEVCC;
    VOS_UINT32                          ulResult          = VOS_ERR;

    ulResult = USIMM_DLResetCard(USIMM_RESET_CARD, &lVoltageSwitchRst);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitCardTypeByATR: Reset Card is Failed");

        /* ��Ϊ˫��˫�����Ը�16λ��¼pid,��16λ��¼ԭ����id */
        ulErrlogNumber = WUEPS_PID_USIM;
        ulErrlogNumber <<= 16;
        ulErrlogNumber |= MNTN_OAM_NO_SIM_CARD_EVENT;

        if(VOS_OK != MNTN_RecordErrorLog(ulErrlogNumber, (void *)&stNoSimCard, sizeof(OAM_MNTN_NO_SIM_CARD_EVENT_STRU)))
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitCardTypeByATR: Fail to record no SIM card in Errorlog file");
        }

        return USIMM_COMM_INIT_FATAL_FAIL;
    }

    enInitRslt = USIMM_COMM_DecodeATR(); /*�жϿ�����*/

    if (USIMM_COMM_INIT_SUCC == enInitRslt)
    {
        USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_UICC);
    }

    return enInitRslt;                  /*��ʼ����һ�����*/
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InsertCommFileToPool
��������  :�������ļ����뻺���
�������  :��
�������  :��
�� �� ֵ  :USIMM_COMMINIT_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��13��
   ��    ��   : g0256031
*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_InsertCommFileToPool(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;

    USIMM_ClearCurFileInfo(USIMM_UNLIMIT_AUTO);   /* ���� MF ����ѡ�� */

    ulResult = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, USIMM_MF_ID);

    if (ulResult != VOS_OK)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InsertCommFileToPool: Select MF is Failed");

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    ulResult = USIMM_UsimVoltageSwitch(USIMM_CCB_GetCurDFInfo(USIMM_UNLIMIT_AUTO)->ucCharaByte,
                                       &g_stUSIMMInitInfo.stUSIMMInfo.ucVoltageSwitchFlag);

    if (ulResult != VOS_OK)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InsertCommFileToPool: Voltage Switch is Failed");

        return USIMM_COMM_INIT_NORMAL_FAIL;
    }

    USIMM_UsimTerminalCapability();

    /*��ʼ����ǰMF�µ��ļ�*/
    for (i = 0; i < USIMM_INITFIRST_FILENUM; i++)
    {
        if (USIMM_ICCID_ID == gausInitFileOne[i])
        {
            ulResult = USIMM_InsertFileToPool(USIMM_UNLIMIT_AUTO, gausInitFileOne[i]);
        }
        else
        {
            ulResult = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, gausInitFileOne[i]);
        }

        if (VOS_OK != ulResult)/*�жϽ��*/
        {
            USIMM_WARNING_LOG("USIMM_UICC_InsertCommFileToPool: Select File under MF is Failed");
        }
    }

    USIMM_INFO_LOG("USIMM_UICC_InsertCommFileToPool: Init Card File First Step 1 Finished");

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_ProfileDownload
��������  :UICC���ն����������·�
�������  :��
�������  :��
�� �� ֵ  :USIMM_COMMINIT_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015-3-10
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_ProfileDownload(VOS_VOID)
{
    USIMM_STK_CFG_STRU                  stProfileContent;

    USIMM_COMM_GetTerminalProfile(&stProfileContent);

    if (VOS_OK != USIMM_SendTermimalProfileDownloadApdu(stProfileContent.stUsimProfile.ucProfileLen,
                                             stProfileContent.stUsimProfile.aucProfile))
    {
         USIMM_ERROR_LOG("USIMM_UICC_ProfileDownload: USIMM_SendTermimalProfileDownloadApdu Error");

        return USIMM_COMM_INIT_REMOVE_RESET;
    }

    return USIMM_COMM_INIT_SUCC;
}


USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_InitCard(VOS_VOID)
{
    VOS_UINT32                          ulStep;
    USIMM_COMMINIT_RST_ENUM_UINT32      enInitRslt = USIMM_COMM_INIT_FATAL_FAIL;

    /* UICC����ʼ�� */
    for (ulStep = 0; ulStep < ARRAYSIZE(g_aUICCCommInitProcFuncTbl); ulStep++)
    {
        if (USIMM_FUNC_UNAVAILABLE == g_aUICCCommInitProcFuncTbl[ulStep].enStatus)
        {
            enInitRslt  = USIMM_COMM_INIT_NORMAL_FAIL;

            continue;
        }

        enInitRslt = g_aUICCCommInitProcFuncTbl[ulStep].pProcFun();

        /* ��ʼ��ʧ��ֱ�ӷ��� */
        if (USIMM_COMM_INIT_FATAL_FAIL == enInitRslt)
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitCard: USIMM_COMM_INIT_FATAL_FAIL");

            break;
        }

        /* ��Ҫ�������ٴγ�ʼ�� */
        if (USIMM_COMM_INIT_RESET == enInitRslt)
        {
            ulStep = VOS_NULL_DWORD;

            continue;
        }

        if (USIMM_COMM_INIT_REMOVE_RESET == enInitRslt)
        {
            g_aUICCCommInitProcFuncTbl[ulStep].enStatus = USIMM_FUNC_UNAVAILABLE;
            ulStep = VOS_NULL_DWORD;

            continue;
        }

        /* ��Ҫ�л���ICC����ʼ�� */
        if (USIMM_COMM_INIT_NORMAL_FAIL == enInitRslt)
        {
            break;
        }
    }

    return enInitRslt;
}


USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_SortAppSN(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    USIMM_APP_PRIORITY_CONFIG_STRU      stPrioCfg;
    USIMM_INITAPPSCTRL_STRU             stAppCtrlItem;

    if (NV_OK != NV_Read(en_NV_Item_Usim_App_Priority_Cfg,
                         (VOS_VOID*)&stPrioCfg, sizeof(stPrioCfg)))
    {
        return USIMM_COMM_INIT_SUCC;
    }

    /* ͨ��NV��ֵ��g_astUICCAppArray�������� */
    for (i = stPrioCfg.ucAppNum; i > 0; i--)
    {
        for (j = 0; j < ARRAYSIZE(g_astUSIMMInitAppCtrl); j++)
        {
            /* �ҵ�����λ�� */
            if (USIMM_CARDAPP_BUTT <= g_astUSIMMInitAppCtrl[j].enAppType)
            {
                break;
            }

            /* �ҵ���ͬ���ᵽ��ǰ�� */
            if (stPrioCfg.aenAppList[i - 1] == g_astUSIMMInitAppCtrl[j].enAppType)
            {
                stAppCtrlItem = g_astUSIMMInitAppCtrl[j];
                /*lint -e534*/
                VOS_MemMove(&g_astUSIMMInitAppCtrl[1], &g_astUSIMMInitAppCtrl[0], j*sizeof(g_astUSIMMInitAppCtrl[j]));
                /*lint +e534*/
                g_astUSIMMInitAppCtrl[0] = stAppCtrlItem;
            }
        }
    }

    return USIMM_COMM_INIT_SUCC;
}
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_InitIsimSimuState(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    USIMM_USIMSUPIMS_STRU               stUsimSupIms;

    if (USIMM_CARD_SERVIC_ABSENT != USIMM_CCB_GetAppService(USIMM_IMS_APP))
    {
        USIMM_CCB_SetUsimSimulateIsimStatus(VOS_FALSE);

        return USIMM_COMM_INIT_SUCC;
    }

    /* ͨ��NV�ж�usim�Ƿ�֧��IMS,Ĭ��֧�� */
    ulResult = NV_Read(en_NV_Item_Usim_Support_Ims, &stUsimSupIms, sizeof(USIMM_USIMSUPIMS_STRU));

    if ((NV_OK == ulResult)
     && (PS_USIM_SERVICE_AVAILIABLE == stUsimSupIms.ulUsimSupImsEnable))/*��ȡʧ�ܰ���Ĭ���·�*/
    {
        USIMM_CCB_SetUsimSimulateIsimStatus(VOS_TRUE);
    }

    return USIMM_COMM_INIT_SUCC;
}

/*****************************************************************************
�� �� ��  : UISMM_UICC_InitCardOpenChannel
��������  : ���߼�ͨ���������ڳ�ʼ���ı����м�¼���
�������  : pstInitList:Ӧ�ó�ʼ�����Ʋ���
�������  : ��
�� �� ֵ  : USIMM_INITAPPS_RST_ENUM_UINT32
�޶���¼  :
1. ��    ��   : 2015-3-18
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 UISMM_UICC_InitCardOpenChannel(
    USIMM_INITAPPSCTRL_STRU            *pstInitList
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucChannelNo;

    if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
    {
        pstInitList->ucChannelNo = 0;

        return USIMM_INITSTEPS_SUCCESS;
    }

    /* �·�manage���߼�ͨ��,��ͨ����ʱ���ڻ����߼�ͨ���ϣ����P2����Ϊ0,P3������1����������һ���ֽڵ�channelID */
    ulResult = USIMM_SendOpenChannelApdu(&ucChannelNo);

    if (ulResult != USIMM_SW_OK)
    {
        USIMM_ERROR_LOG("UISMM_UICC_InitCardOpenChannel: USIMM_CheckSW Fail");

        return USIMM_INITSTEPS_FAIL;
    }

    pstInitList->ucChannelNo = ucChannelNo;

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitPINRemainTime
��������  :��ȡ��ǰ��PINʣ�����
�������  :ucPINNo   :��ǰPIN��������
�������  :pucPINTime:PINʣ�����
�� �� ֵ  :VOS_ERR
           VOS_OK
���ú���  :USIMM_VerifyPIN_APDU
�޶���¼  :
1. ��    ��   : 2015��3��18��
    ��    ��   : zhuli
    �޸�����   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_UICC_InitPINRemainTime(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucPINNo,
    VOS_UINT8                          *pucPINTime
)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_RSP_STRU                 stRspData;

    if (VOS_NULL_PTR == pucPINTime)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINRemainTime: Input Para Error");

        return VOS_ERR;
    }

    ulResult = USIMM_SendVerifyPinApdu(ucChannelID, CMD_INS_VERIFY, ucPINNo, VOS_NULL_PTR, &stRspData);

    if ((USIMM_SW_PIN_BLOCK != ulResult)&&(USIMM_SW_CMD_REMAINTIME != ulResult))/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINRemainTime: USIMM_PINVerify_APDU Error");

        return VOS_ERR;
    }

    if(0x63 == stRspData.ucSW1)
    {
        *pucPINTime = stRspData.ucSW2&0x0F;
    }
    else
    {
        *pucPINTime = 0;
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitPUKRemainTime
��������  :��ȡ��ǰ��PUK��ʣ�����
�������  :ucPINNo :PUK��Ӧ��PIN��������
�������  :pucPUKTime: PUKʣ�����
�� �� ֵ  :VOS_ERR
           VOS_OK
�޶���¼  :
1. ��    ��   : 2015��3��18��
    ��    ��   : zhuli
    �޸�����   : Creat

*****************************************************************************/
VOS_UINT32 USIMM_UICC_InitPUKRemainTime(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucPINNo,
    VOS_UINT8                          *pucPUKTime
)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_RSP_STRU                 stRspData;

    if (VOS_NULL_PTR == pucPUKTime)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPUKRemainTime: Input Para Error");

        return VOS_ERR;
    }

    ulResult = USIMM_SendUnblockPinApdu(ucChannelID, ucPINNo, VOS_NULL_PTR, VOS_NULL_PTR, &stRspData);

	if ((USIMM_SW_ERR == ulResult)||(USIMM_SW_SENDCMD_ERROR == ulResult))/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPUKRemainTime: USIMM_UnblockPIN_APDU Error");

        return VOS_ERR;
    }

    if(0x63 == stRspData.ucSW1)
    {
        *pucPUKTime = stRspData.ucSW2&0x0F;
    }
    else
    {
        *pucPUKTime = 0;
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitUsimGlobal
��������  :��ʼUSIM��ȫ�ֱ���
�������  :ucChannelNo
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_SUCCESS

�޶���¼  :
1. ��    ��   : 2015��3��18��
    ��    ��   : zhuli
    �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimGlobal(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_CCB_SetAppChNO(ucChannelNo, USIMM_GUTL_APP);

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitUsimADF
��������  :��ʼUSIM��ADF
�������  :ucChannelNo
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
    ��    ��   : zhuli
    �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimADF(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_RSP_STRU                 stApduRsp;
    USIMM_AID_INFO_STRU                *pstAIDInfo;

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimADF: Step is Begin");

    pstAIDInfo = USIMM_CCB_GetAIDByApp(USIMM_GUTL_APP);

    if (VOS_NULL == pstAIDInfo)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitUsimADF: AID Len Error");

        return USIMM_INITSTEPS_FAIL;
    }

    ulResult = USIMM_SelectAIDFile(ucChannelNo,
                                   USIMM_SELECT_RETURN_FCP_TEMPLATE,
                                   pstAIDInfo,
                                   &stApduRsp);

    if(USIMM_SW_OK == ulResult) /*�ж�AIDѡ����*/
    {
        USIMM_ClearCurEFInfo(USIMM_CCB_GetCurFileInfo(USIMM_GUTL_APP));/*ѡ��DF�ļ����ϴ�ѡ�е�EF�ļ���Ϊ��Чֵ*/

        USIMM_NORMAL_LOG("USIMM_UICC_InitUsimADF: Select AID is Success");

        ulResult = USIMM_DecodeDFFcp(USIMM_PHYCARD_TYPE_UICC, &stApduRsp, USIMM_CCB_GetCurFileInfo(USIMM_GUTL_APP));
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitUsimADF: Select File Error");/*��ӡ����*/

        ulResult = VOS_ERR;
    }

    if (VOS_OK == ulResult)
    {
        USIMM_CCB_GetCurFileInfo(USIMM_GUTL_APP)->usCurDFID = ADF;

        USIMM_COMM_SaveDFPinInfo(USIMM_GUTL_APP);

        USIMM_NORMAL_LOG("USIMM_UICC_InitUsimADF: Decode AID is Success");

        return USIMM_INITSTEPS_SUCCESS;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitUsimADF: Select AID is Error");/*��ӡ����*/

        return USIMM_INITSTEPS_FAIL;
    }
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitPINTime
��������  :��ʼUSIM��PIN��ʣ�����
�������  :ucChannelNo:ͨ����
�������  :��
�� �� ֵ  :VOS_OK

�޶���¼  :
1. ��    ��   : 2015��3��18��
    ��    ��   : zhuli
    �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitPINTime(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_COMM_CARD_APP_INFO_STRU      *pstAppInfo;
    USIMM_APP_PIN_INFO_STRU            *pstPIN1Info;
    USIMM_APP_PIN_INFO_STRU            *pstPIN2Info;
    VOS_UINT8                           ucPIN1No;
    VOS_UINT8                           ucPIN2No;

    USIMM_NORMAL_LOG("USIMM_UICC_InitPINTime: Step is Begin");

    pstAppInfo = USIMM_CCB_GetAppInfoByCH(ucChannelNo);

    if (VOS_NULL_PTR == pstAppInfo)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: App Info is NULL");/*��ӡ����*/

        return USIMM_INITSTEPS_FAIL;
    }

    ucPIN1No = (VOS_UINT8)pstAppInfo->stPinInfo.enPinKeyRef;

    if ((ucPIN1No < 1)||(ucPIN1No > 8))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: PIN Ref Info is Wrong");/*��ӡ����*/

        return USIMM_INITSTEPS_FAIL;
    }

    pstPIN1Info = USIMM_CCB_GetPIN1InfoByRef(ucPIN1No);

    if (VOS_NULL_PTR == pstPIN1Info)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: Get PIN Info is Fail");/*��ӡ����*/

        return USIMM_INITSTEPS_FAIL;
    }

    pstPIN2Info = &pstAppInfo->stPinInfo.stPin2Info;

    ucPIN2No = pstPIN2Info->ucPINRefNum;

    if ((ucPIN2No < 0x81)||(ucPIN2No > 0x88))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: PIN2 Ref Info is Wrong");/*��ӡ����*/

        return USIMM_INITSTEPS_FAIL;
    }

    if (VOS_OK != USIMM_UICC_InitPINRemainTime(ucChannelNo, ucPIN1No, &pstPIN1Info->ucPinRemainTime))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: Get PIN1 Times is Wrong");/*��ӡ����*/

        return USIMM_INITSTEPS_FAIL;
    }

    if (VOS_OK != USIMM_UICC_InitPINRemainTime(ucChannelNo, ucPIN2No, &pstPIN2Info->ucPinRemainTime))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: Get PIN2 Times is Wrong");/*��ӡ����*/

        return USIMM_INITSTEPS_FAIL;
    }

    if (VOS_OK != USIMM_UICC_InitPUKRemainTime(ucChannelNo, ucPIN1No, &pstPIN1Info->ucPukRemainTime))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: Get PUK1 Times is Wrong");/*��ӡ����*/

        return USIMM_INITSTEPS_FAIL;
    }

    if (VOS_OK != USIMM_UICC_InitPUKRemainTime(ucChannelNo, ucPIN2No, &pstPIN2Info->ucPukRemainTime))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitPINTime: Get PUK2 Times is Wrong");/*��ӡ����*/

        return USIMM_INITSTEPS_FAIL;
    }

    USIMM_COMM_InitPINState(pstPIN1Info);

    USIMM_COMM_InitPINState(pstPIN2Info);

    USIMM_NORMAL_LOG("USIMM_UICC_InitPINTime: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitUsimECC
��������  :��ʼUSIM��ECC��Ϣ
�������  :ucChannelNo �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimECC(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimECC: Step is Begin");

    ulResult = USIMM_InitUsimEccFile();

    if (VOS_OK == ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitUsimECC: Step is OK");

        return USIMM_INITSTEPS_SUCCESS;
    }

    USIMM_ERROR_LOG("USIMM_UICC_InitUsimECC: Step is Fail");

    return USIMM_INITSTEPS_REMOVE;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitUsimEFLI
��������  :��ʼUSIM���ļ�
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :VOS_OK

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimEFLI(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           *pucData;

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimEFLI: Step is Begin");

    ulResult = USIMM_GetDefTFMem(USIMM_GUTL_APP, USIMM_USIM_EFLI_ID, &usDataLen, &pucData);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitUsimEFLI: Step is Fail");

        return USIMM_INITSTEPS_REMOVE;
    }
    else
    {
        (VOS_VOID)VOS_MemFree(WUEPS_PID_USIM, pucData);

        USIMM_NORMAL_LOG("USIMM_UICC_InitUsimEFLI: Step is OK");

        return USIMM_INITSTEPS_SUCCESS;
    }
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitUsimATT
��������  :��ʼUSIM��ATT���Ʋ���
�������  :ucChannelNo   �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimATT(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          i;

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimATT: Step is Begin");

    /* ATT���ƹ��̣�ʧ����Ҳ������������ʼ�� */
    /* ������USIMʱѡ��AID��ȷ������ѡ��6FD2�ļ� */
    USIMM_AttUpdataSupportTable(ucChannelNo);

    /* �ж�AT&T�����Ƿ�� */
    if (VOS_FALSE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAtt_flg)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitUsimATT: Step is no need");

        return USIMM_INITSTEPS_SUCCESS;
    }

    for (i = 0;i < ARRAYSIZE(g_aulAttUsimInitFile); i++ )
    {
        (VOS_VOID)USIMM_InsertFileToPool(USIMM_GUTL_APP, g_aulAttUsimInitFile[i]);
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimATT: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitUsimFBDNStatus
��������  :��ʼ��USIM����ǰ��FDN/BDN״̬��
�������  :��
�������  :��
�� �� ֵ  :��
�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
VOS_VOID USIMM_UICC_InitUsimFBDNStatus(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucData;
    USIMM_FDNSTATUS_ENUM_UINT32         enFDNStatus;
    USIMM_BDNSTATUS_ENUM_UINT32         enBDNStatus;

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFBDNStatus: Step is Begin");

    ulResult = USIMM_GetTFByDefFID(USIMM_GUTL_APP, USIMM_USIM_EFEST_ID, sizeof(ucData), &ucData);

    if(VOS_OK == ulResult) /*���ļ��Ĵ��ڲ��Ǳ����*/
    {
        /*�ж����ݳ�ʼ����Ӧ��ȫ�ֱ���*/
        if (PS_USIM_SERVICE_AVAILIABLE == USIMM_IsServiceAvailable(USIM_SVR_FDN))
        {
            USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFBDNStatus: Set FDN by File Data");

            enFDNStatus = (ucData&0x01)?USIMM_FDNSTATUS_ON:USIMM_FDNSTATUS_OFF;

            USIMM_CCB_SetAppFDN(USIMM_GUTL_APP, enFDNStatus);
        }
        else
        {
            USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFBDNStatus: FDN Service is OFF");

            USIMM_CCB_SetAppFDN(USIMM_GUTL_APP, USIMM_FDNSTATUS_OFF);
        }

        if (PS_USIM_SERVICE_AVAILIABLE == USIMM_IsServiceAvailable(USIM_SVR_BDN))
        {
            USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFBDNStatus: Set BDN by File Data");

            enBDNStatus = (ucData&0x02)?USIMM_BDNSTATUS_ON:USIMM_BDNSTATUS_OFF;

            USIMM_CCB_SetAppBDN(USIMM_GUTL_APP, enBDNStatus);
        }
        else
        {
            USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFBDNStatus: BDN Service is OFF");

            USIMM_CCB_SetAppBDN(USIMM_GUTL_APP, USIMM_BDNSTATUS_OFF);
        }
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitUsimFBDNStatus: Get EF EST Error");
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFBDNStatus: Step is Over");

    return ;
}

/*****************************************************************************
�� �� ��  : USIMM_UICC_InitUsimMFile
��������  : ��ʼUSIM����ѡ�ļ���ʧ�ܻ�����Ӧ�ò�����
�������  : ucChannelNO  �߼�ͨ����
�������  : ��
�� �� ֵ  : USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimMFile(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;
    VOS_UINT16                          ausUsimInitMFile[] = {USIMM_USIM_EFIMSI_ID,
                                                              USIMM_USIM_EFAD_ID};

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimMFile: Step is Begin");

    USIMM_CCB_GetFilePoolTotalGlobal()->enPoolStatus = USIMM_POOL_AVAILABLE;

    ulResult = USIMM_InsertFileToPool(USIMM_GUTL_APP, USIMM_USIM_EFUST_ID);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitUsimMFile: Read EFUST File Failed");

        return USIMM_INITSTEPS_FAIL;
    }

    USIMM_UICC_InitUsimFBDNStatus();

    for(i = 0;i < ARRAYSIZE(ausUsimInitMFile); i++ )
    {
        if(VOS_OK != USIMM_InsertFileToPool(USIMM_GUTL_APP, ausUsimInitMFile[i]))
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitUsimMFile:Read Mandatory File Failed");

            return USIMM_INITSTEPS_FAIL;
        }
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimMFile: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitUsimMFile2
��������  :��ʼUSIM��������ѡ�ļ���ʧ�ܿ�������
�������  :ucChannelNo   �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_SUCCESS

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimMFile2(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          ausUsimInitMFile[] = {USIMM_USIM_EFNETPAR_ID,
                                                              USIMM_USIM_EFHPPLMN_ID,
                                                              USIMM_USIM_EFLOCI_ID,
                                                              USIMM_USIM_EFACC_ID,
                                                              USIMM_USIM_EFPSLOCI_ID,
                                                              USIMM_USIM_EFKEYS_ID,
                                                              USIMM_USIM_EFKEYSPS_ID,
                                                              USIMM_USIM_EFFPLMN_ID,
                                                              USIMM_USIM_EFSTART_HFN_ID,
                                                              USIMM_USIM_EFTHRESHOL_ID};

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimMFile2: Step is Begin");

    for(i = 0;i < ARRAYSIZE(ausUsimInitMFile); i++ )
    {
        if(VOS_OK != USIMM_InsertFileToPool(USIMM_GUTL_APP, ausUsimInitMFile[i]))
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitUsimMFile2:Read Mandatory File Failed");

            continue;
        }
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimMFile2: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitUsimFinish
��������  :��ʼUSIM������
�������  : ucChannelNo
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_SUCCESS

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimFinish(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFinish: Step is Begin");

    if (USIMM_SW_OK != USIMM_SendStatusApdu(ucChannelNo,
                                        USIMM_STATUS_CURAPP_INITIALIZED,
                                        USIMM_STATUS_NO_DATA_RETURNED,
                                        0x00))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitUsimFinish: USIMM_Status_APDU is Fail");
    }

    USIMM_SetAccFileAccess();

	USIMM_SetImsiFile();

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimFinish: Step is Over");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_ReadUsimOPFile
��������  :��ʼUSIM����ѡ�ļ�
�������  :��
�������  :��
�� �� ֵ  :��

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
VOS_VOID USIMM_UICC_ReadUsimOPFile(VOS_VOID)
{
    VOS_UINT32                          i;

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimOPFile: Step is Begin");

    for (i =  0; i < ARRAYSIZE(gastUsimInitOFile); i++)
    {
        if (UICC_SVR_NONE != gastUsimInitOFile[i].ulService)
        {
            if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(gastUsimInitOFile[i].ulService))
            {
                continue;
            }
        }

        if (VOS_OK != USIMM_InsertFileToPool(USIMM_GUTL_APP, gastUsimInitOFile[i].enDefFileID))
        {
            USIMM_WARNING_LOG("USIMM_UICC_ReadUsimOPFile: Read Optional File Failed");
        }
    }

    USIMM_NORMAL_LOG("USIMM_UICC_ReadUsimOPFile: Step is OK");

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitUsimOPFile
��������  :��ʼUSIM����ѡ�ļ�
�������  :ucChannelNo    �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimOPFile(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimOPFile: Step is Begin");

    if (VOS_FALSE == USIMM_COMM_IsAndroidPhone())
    {
        /*lint -e534*/
        USIMM_SendInitCardMsg(WUEPS_PID_USIM, USIMM_INITCONTINUE_REQ);
        /*lint +e534*/
    }
    else
    {
        USIMM_UICC_ReadUsimOPFile();
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitUsimOPFile: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitCsimGlobal
��������  :��ʼCSIM��ȫ�ֱ���
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimGlobal(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_CCB_SetAppChNO(ucChannelNo, USIMM_CDMA_APP);

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitCsimADF
��������  :��ʼCSIM��Ӧ����Ϣ
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimADF(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_RSP_STRU                 stApduRsp;
    USIMM_AID_INFO_STRU                 *pstAIDInfo;

    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimADF: Step is Begin");

    pstAIDInfo = USIMM_CCB_GetAIDByApp(USIMM_CDMA_APP);

    if (VOS_NULL == pstAIDInfo)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitCsimADF: AID Len Error");

        return USIMM_INITSTEPS_FAIL;
    }

    ulResult = USIMM_SelectAIDFile(ucChannelNo,
                                    USIMM_SELECT_RETURN_FCP_TEMPLATE,
                                    pstAIDInfo,
                                    &stApduRsp);

    if(USIMM_SW_OK == ulResult) /*�ж�AIDѡ����*/
    {
        USIMM_ClearCurEFInfo(USIMM_CCB_GetCurFileInfo(USIMM_CDMA_APP));/*ѡ��DF�ļ����ϴ�ѡ�е�EF�ļ���Ϊ��Чֵ*/

        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimADF: Select AID is Success");

        ulResult = USIMM_DecodeDFFcp(USIMM_PHYCARD_TYPE_UICC, &stApduRsp, USIMM_CCB_GetCurFileInfo(USIMM_CDMA_APP));
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitCsimADF: Select File Error");/*��ӡ����*/

        ulResult = VOS_ERR;
    }

    if (VOS_OK == ulResult)
    {
        USIMM_CCB_GetCurFileInfo(USIMM_CDMA_APP)->usCurDFID = ADF;

        USIMM_CCB_GetAdfInfoByCH(ucChannelNo)->ucCharaByte = USIMM_CCB_GetCurDFInfo(USIMM_CDMA_APP)->ucCharaByte;

        USIMM_CCB_GetAdfInfoByCH(ucChannelNo)->ucSupCmd    = USIMM_CCB_GetCurDFInfo(USIMM_CDMA_APP)->ucSupCmd;

        USIMM_COMM_SaveDFPinInfo(USIMM_CDMA_APP);

        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimADF: Decode AID is Success");

        return USIMM_INITSTEPS_SUCCESS;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitCsimADF: Select AID is Error");/*��ӡ����*/

        return USIMM_INITSTEPS_FAIL;
    }
}


VOS_VOID USIMM_UICC_InitCUIMEccFile(VOS_VOID)
{
    VOS_UINT16              usDataLen;
    VOS_UINT8               *pucData;

    if (VOS_OK != USIMM_GetDefTFMem(USIMM_CDMA_APP, USIMM_CSIM_EFECC_ID, &usDataLen, &pucData))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitCUIMEccFile:USIMM_UICC_InitCUIMTFileContent err");

        return ;
    }

    /* �ϱ���ǰ��Ecc�������� */
    USIMM_XeccNumberInd(usDataLen, pucData);

    if (VOS_NULL_PTR != pucData)
    {
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pucData);
        /*lint +e534*/
    }

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitCsimECC
��������  :��ʼCSIM���������к���
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimECC(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimECC: Step is Begin");

    USIMM_UICC_InitCUIMEccFile();

    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimECC: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}


VOS_VOID USIMM_UICC_InitCSIMEstFile(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucData;
    USIMM_FDNSTATUS_ENUM_UINT32         enFDNStatus;

    USIMM_NORMAL_LOG("USIMM_UICC_InitCSIMEstFile: Step is Begin");

    ulResult = USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CSIM_EFEST_ID);

    if(VOS_OK == ulResult) /*���ļ��Ĵ��ڲ��Ǳ����*/
    {
        ulResult = USIMM_PoolReadOneFile(EF_CSIM_EST, sizeof(ucData), &ucData, USIMM_CDMA_APP);

        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitCSIMEstFile: Get EF EST Error");
            return;
        }

        /*�ж����ݳ�ʼ����Ӧ��ȫ�ֱ���*/
        if (PS_USIM_SERVICE_AVAILIABLE == USIMM_IsServiceAvailable(CSIM_SVR_FDN))
        {
            USIMM_NORMAL_LOG("USIMM_UICC_InitCSIMEstFile: Set FDN by File Data");

            enFDNStatus = (ucData&0x01)?USIMM_FDNSTATUS_ON:USIMM_FDNSTATUS_OFF;

            USIMM_CCB_SetAppFDN(USIMM_CDMA_APP, enFDNStatus);
        }
        else
        {
            USIMM_NORMAL_LOG("USIMM_UICC_InitCSIMEstFile: FDN Service is OFF");

            USIMM_CCB_SetAppFDN(USIMM_CDMA_APP, USIMM_FDNSTATUS_OFF);
        }
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitCSIMEstFile: USIMM_InsertFileToPool EF EST Error");
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitCSIMEstFile: Step is Over");

    return ;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitCsimFDNStatus
��������  :��ʼ��CSIM����ǰ��FDN/BDN״̬��
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :��

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
VOS_VOID USIMM_UICC_InitCsimFDNStatus(VOS_VOID)
{
    VOS_UINT16                          ausCsimFdnFile[] = {USIMM_CSIM_EFIMSIM_ID,
                                                            USIMM_CSIM_EFIMSIT_ID,
                                                            USIMM_CSIM_EFTMSI_ID };
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;

    for (i=0; i<ARRAYSIZE(ausCsimFdnFile); i++)
    {
        /*Selct IMSI_M, IMSI_T, TMSI*/
        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, ausCsimFdnFile[i]);

        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitCsimFDNStatus: One Mandory file is absent");

            continue;
        }

        if (USIMM_EFSTATUS_DEACTIVE == USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus)
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitCsimFDNStatus: One file is deactive");
        }
    }

    return ;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitCsimMFile
��������  :��ʼUSIM����ѡ�ļ�
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimMFile(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimMFile: Step is Begin");

    /*Read EF AD*/
    (VOS_VOID)USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CSIM_EFAD_ID);

    /*Save EF CST*/
    (VOS_VOID)USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CSIM_EFCSIMST_ID);

    (VOS_VOID)USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CSIM_EFIMSIM_ID);

    /*Read EF EST*/
    USIMM_UICC_InitCSIMEstFile();

    USIMM_UICC_InitCsimFDNStatus();

    /*Read UIMID*/
    (VOS_VOID)USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CSIM_EFRUIMID_ID);

    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimMFile: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitCsimMFile2
��������  :��ʼCSIM��������ѡ�ļ�
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimMFile2(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          ausCsimInitMFile[] = {USIMM_CSIM_EFUSGIND_ID,
                                                              USIMM_CSIM_EFSP_ID,
                                                              USIMM_CSIM_EFIMSIM_ID,
                                                              USIMM_CSIM_EFIMSIT_ID,
                                                              USIMM_CSIM_EFACCOLC_ID,
                                                              USIMM_CSIM_EFPRL_ID,
                                                              USIMM_CSIM_EFEPRL_ID,
                                                              USIMM_CSIM_EFMAXPRL_ID,
                                                              USIMM_CSIM_EFTMSI_ID,
                                                              };
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           *pucData;

    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimMFile2: Step is Begin");

    for(i = 0;i < ARRAYSIZE(ausCsimInitMFile); i++ )
    {
        if (VOS_OK == USIMM_GetDefTFMem(USIMM_CDMA_APP,ausCsimInitMFile[i],&usDataLen, &pucData))
        {
            (VOS_VOID)VOS_MemFree(WUEPS_PID_USIM, pucData);
        }
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimMFile2: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitCsimEFMecrp
��������  :��ʼUIM�������и������ļ�EF MECRP
�������  :ucChannelNo:Channel Number
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_SUCCESS/USIMM_INITSTEPS_REMOVE

�޶���¼  :
1. ��    ��   : 2015��3��10��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimEFMecrp(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucUpdate[2];

    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, 
                                           USIMM_NEED_FCP, 
                                           USIMM_CSIM_EFMECRP_ID);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimEFMecrp: Select File is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    ulResult = USIMM_COMM_GetMecrpValue(&aucUpdate[0], &aucUpdate[1]);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimEFMecrp: USIMM_COMM_GetMecrpValue is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    ulResult = USIMM_SendUpdateBinaryApdu(ucChannelNo, sizeof(aucUpdate), aucUpdate);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimEFMecrp: Update is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitCsimFinish
��������  :��ʼUSIM����ʼ�����
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimFinish(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimFinish: Step is Begin");

    if (USIMM_SW_OK != USIMM_SendStatusApdu(ucChannelNo,
                                            USIMM_STATUS_CURAPP_INITIALIZED,
                                            USIMM_STATUS_NO_DATA_RETURNED,
                                            0x00))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitCsimFinish: USIMM_Status_APDU is Fail");
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitCsimFinish: Step is Over");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitVIACsimFinish
��������  :��ʼƴƬCSIM����ʼ�����
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitVIACsimFinish(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_UICC_InitVIACsimFinish: Step is Begin");

    USIMM_NORMAL_LOG("USIMM_UICC_InitVIACsimFinish: Step is Over");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_UICC_InitCsimOPFile
��������  :��ʼUSIM����ѡ�ļ�
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimOPFile(
    VOS_UINT8                           ucChannelNo
)
{
    return USIMM_INITSTEPS_SUCCESS;
}


USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitIsimGlobal(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_CCB_SetAppChNO(ucChannelNo, USIMM_IMS_APP);

    return USIMM_INITSTEPS_SUCCESS;
}


USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitIsimADF(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    USIMM_APDU_RSP_STRU                 stApduRsp;
    USIMM_AID_INFO_STRU                 *pstAIDInfo;

    USIMM_NORMAL_LOG("USIMM_UICC_InitIsimADF: Step is Begin");

    pstAIDInfo = USIMM_CCB_GetAIDByApp(USIMM_IMS_APP);

    if (VOS_NULL == pstAIDInfo)
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitIsimADF: AID Len Error");

        return USIMM_INITSTEPS_FAIL;
    }

    ulResult = USIMM_SelectAIDFile(ucChannelNo,
                                   USIMM_SELECT_RETURN_FCP_TEMPLATE,
                                   pstAIDInfo,
                                   &stApduRsp);

    if(USIMM_SW_OK == ulResult) /*�ж�AIDѡ����*/
    {
        USIMM_ClearCurEFInfo(USIMM_CCB_GetCurFileInfo(USIMM_IMS_APP));/*ѡ��DF�ļ����ϴ�ѡ�е�EF�ļ���Ϊ��Чֵ*/

        USIMM_NORMAL_LOG("USIMM_UICC_InitIsimADF: Select AID is Success");

        ulResult = USIMM_DecodeDFFcp(USIMM_PHYCARD_TYPE_UICC, &stApduRsp, USIMM_CCB_GetCurFileInfo(USIMM_IMS_APP));
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitIsimADF: Select File Error");/*��ӡ����*/

        ulResult = VOS_ERR;
    }

    if (VOS_OK == ulResult)
    {
        USIMM_CCB_GetCurFileInfo(USIMM_IMS_APP)->usCurDFID = ADF;

        USIMM_CCB_GetAdfInfoByCH(ucChannelNo)->ucCharaByte = USIMM_CCB_GetCurDFInfo(USIMM_IMS_APP)->ucCharaByte;

        USIMM_CCB_GetAdfInfoByCH(ucChannelNo)->ucSupCmd    = USIMM_CCB_GetCurDFInfo(USIMM_IMS_APP)->ucSupCmd;

        USIMM_COMM_SaveDFPinInfo(USIMM_IMS_APP);

        USIMM_NORMAL_LOG("USIMM_UICC_InitIsimADF: Decode AID is Success");

        return USIMM_INITSTEPS_SUCCESS;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitIsimADF: Select AID is Error");/*��ӡ����*/

        return USIMM_INITSTEPS_FAIL;
    }
}


USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitIsimMFile(
    VOS_UINT8                           ucChannelNo
)
{
    /*ISIM����Ҫ��ʼ����ȡ�����Mandatory�ļ�ID*/
    VOS_UINT16                          ausIsimInitMFile[] = {USIMM_ISIM_EFAD_ID,
                                                              USIMM_ISIM_EFIMPI_ID,
                                                              USIMM_ISIM_EFIMPU_ID,
                                                              USIMM_ISIM_EFDOMAIN_ID,
                                                              USIMM_ISIM_EFIST_ID};
    VOS_UINT32                          i;

    USIMM_NORMAL_LOG("USIMM_UICC_InitIsimMFile: Step is Begin");

    for(i = 0;i < ARRAYSIZE(ausIsimInitMFile); i++ )
    {
        if(VOS_OK != USIMM_InsertFileToPool(USIMM_IMS_APP, ausIsimInitMFile[i]))
        {
            USIMM_ERROR_LOG("USIMM_UICC_InitIsimMFile:Read Mandatory File Failed");

            continue;
        }
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitIsimMFile: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitIsimFinish(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_UICC_InitIsimFinish: Step is Begin");

    if (USIMM_SW_OK != USIMM_SendStatusApdu(ucChannelNo,
                                            USIMM_STATUS_CURAPP_INITIALIZED,
                                            USIMM_STATUS_NO_DATA_RETURNED,
                                            0x00))
    {
        USIMM_ERROR_LOG("USIMM_UICC_InitIsimFinish: USIMM_Status_APDU is Fail");
    }

    USIMM_NORMAL_LOG("USIMM_UICC_InitIsimFinish: Step is Over");

    return USIMM_INITSTEPS_SUCCESS;
}


USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitIsimOPFile(
    VOS_UINT8                           ucChannelNo
)
{
#if 0
    VOS_UINT32                          i;
    VOS_UINT32                          ulFirstService;
    VOS_UINT32                          ulSecondService;
    VOS_UINT8                           ucCheck;

    /*ISIM����Ҫ��ʼ����ȡ�����Optional�ļ�ID*/
    USIMM_OPFILE_ISIM_LIST_STRU         astIsimInitOFile[] = {\
    {USIMM_ISIM_EFPCSCF_ID,    ISIM_SVR_PCSCF_ADDR, (VOS_UINT16)ISIM_SVR_IMS_PCSCF, (VOS_UINT16)USIMM_ISIM_SERVICE_OR},
    {USIMM_ISIM_EFGBAP_ID,     ISIM_SVR_GBA,        (VOS_UINT16)ISIM_SVR_GBA,       (VOS_UINT16)USIMM_ISIM_SERVICE_AND},
    {USIMM_ISIM_EFGBANL_ID,    ISIM_SVR_GBA,        (VOS_UINT16)ISIM_SVR_GBA,       (VOS_UINT16)USIMM_ISIM_SERVICE_AND},
    {USIMM_ISIM_EFNAFKCA_ID,   ISIM_SVR_GBA,        (VOS_UINT16)ISIM_SVR_LOCAL_GBA, (VOS_UINT16)USIMM_ISIM_SERVICE_AND},
    {USIMM_ISIM_EFSMS_ID,      ISIM_SVR_SMS,        (VOS_UINT16)ISIM_SVR_SOI,       (VOS_UINT16)USIMM_ISIM_SERVICE_AND},
    {USIMM_ISIM_EFSMSS_ID,     ISIM_SVR_SMS,        (VOS_UINT16)ISIM_SVR_SOI,       (VOS_UINT16)USIMM_ISIM_SERVICE_AND},
    {USIMM_ISIM_EFSMSR_ID,     ISIM_SVR_SMSR,       (VOS_UINT16)ISIM_SVR_SOI,       (VOS_UINT16)USIMM_ISIM_SERVICE_AND},
    {USIMM_ISIM_EFSMSP_ID,     ISIM_SVR_SOI,        (VOS_UINT16)ISIM_SVR_SOI,       (VOS_UINT16)USIMM_ISIM_SERVICE_AND},
    {USIMM_ISIM_EFUICCIARI_ID, ISIM_SVR_UICC_IMS,   (VOS_UINT16)ISIM_SVR_UICC_IMS,  (VOS_UINT16)USIMM_ISIM_SERVICE_AND}};

    USIMM_NORMAL_LOG("USIMM_UICC_InitIsimOPFile: Step is Begin");

    for (i =  0; i < ARRAYSIZE(astIsimInitOFile); i++)
    {
        ulFirstService  = USIMM_IsServiceAvailable(astIsimInitOFile[i].ulFService);
        ulSecondService = USIMM_IsServiceAvailable(astIsimInitOFile[i].usSService);

        /*��ǰ��ISIM��Ҫ��������λ����һ������*/
        if (USIMM_ISIM_SERVICE_OR == astIsimInitOFile[i].enCheckType)
        {
            if ((PS_USIM_SERVICE_NOT_AVAILIABLE == ulFirstService)
             && (PS_USIM_SERVICE_NOT_AVAILIABLE == ulSecondService))
            {
                ucCheck = VOS_NO;
            }
            else
            {
                ucCheck = VOS_YES;
            }
        }
        else /*��ǰISIM��Ҫ��������λ������*/
        {
            if ((PS_USIM_SERVICE_NOT_AVAILIABLE == ulFirstService)
             || (PS_USIM_SERVICE_NOT_AVAILIABLE == ulSecondService))
            {
                ucCheck = VOS_NO;
            }
            else
            {
                ucCheck = VOS_YES;
            }
        }

        if (VOS_YES != ucCheck)
        {
            continue;
        }

        /* ѡ���ļ� */
        if (VOS_OK != USIMM_SelectFileByDefFileId(USIMM_IMS_APP, USIMM_NEED_FCP, astIsimInitOFile[i].enDefFileId))
        {
            USIMM_WARNING_LOG("USIMM_UICC_InitIsimOPFile: USIMM_SelectFile Failed");
        }

    }
#endif
    USIMM_NORMAL_LOG("USIMM_UICC_InitIsimOPFile: USIMM Init Card File Third is Finished");

    return USIMM_INITSTEPS_SUCCESS;
}


USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_ICC_InitGlobalVar(VOS_VOID)
{
    USIMM_COMM_ResetPIN1Global();

    USIMM_PoolDelAll(); /*�����ڴ��ظ���ӣ����ͷ�����ڴ�*/

    gstUSIMMBaseInfo.ucCLA              = USIMM_SIM_CLA;
    gstUSIMMBaseInfo.enSupportPath      = USIMM_NOTSUPPORT_PATH;
    gstUSIMMBaseInfo.enSupportSFI       = USIMM_NOTSUPPORT_SFI;
    gstUSIMMBaseInfo.enSupportChannel   = USIMM_NOTSUPPORT_CHANNEL;

    return USIMM_COMM_INIT_SUCC;
}
USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_ICC_InitCardTypeByATR(VOS_VOID)
{
    VOS_UINT32                          ulResult          = VOS_ERR;
    VOS_UINT32                          ulErrlogNumber;
    OAM_MNTN_NO_SIM_CARD_EVENT_STRU     stNoSimCard;
    VOS_INT32                           lVoltageSwitchRst = USIMM_SCI_NONEED_CHANGEVCC;
    USIMM_CURFILEINFO_ST               *pstCurFile;

    if (USIMM_TEST_TYPE_GCF_SIM == USIMM_CCB_GetTestCardType())
    {
        USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_ICC);

        pstCurFile = USIMM_CCB_GetCurFileInfo(USIMM_UNLIMIT_AUTO);

        /* Ĭ�ϴ�7F20��ʼѡ���ļ� */
        pstCurFile->usCurDFID      = MF;
        pstCurFile->usCurEFID      = USIMM_NULL_ID;
        pstCurFile->usCurDFFcpLen  = VOS_NULL;
        pstCurFile->usFilePathLen  = 1;
        pstCurFile->ausFilePath[0] = MF;

        return USIMM_COMM_INIT_SUCC;
    }

    ulResult = USIMM_DLResetCard(USIMM_RESET_CARD, &lVoltageSwitchRst);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitCardTypeByATR: Reset Card is Failed");

        /* ��Ϊ˫��˫�����Ը�16λ��¼pid,��16λ��¼ԭ����id */
        ulErrlogNumber = WUEPS_PID_USIM;
        ulErrlogNumber <<= 16;
        ulErrlogNumber |= MNTN_OAM_NO_SIM_CARD_EVENT;

        if(VOS_OK != MNTN_RecordErrorLog(ulErrlogNumber, (void *)&stNoSimCard, sizeof(OAM_MNTN_NO_SIM_CARD_EVENT_STRU)))
        {
            USIMM_ERROR_LOG("USIMM_ICC_InitCardTypeByATR: Fail to record no SIM card in Errorlog file");
        }

        return USIMM_COMM_INIT_FATAL_FAIL;
    }

    ulResult = USIMM_COMM_DecodeATR(); /*�жϿ�����*/

    if(USIMM_COMM_INIT_SUCC == ulResult)
    {
        USIMM_CCB_SetCardType(USIMM_PHYCARD_TYPE_ICC);
    }

    return ulResult;                                 /*��ʼ����һ�����*/
}


VOS_UINT32 USIMM_ICC_CheckCLStep(
    USIMM_CARDAPP_ENUM_UINT32          *penCardApp
)
{
    VOS_UINT32                          ulCDMAResult = VOS_OK;
    VOS_UINT32                          ulGsmResult = VOS_OK;

    /* �ֱ�ѡ��7F20��7F25���ж��Ƿ�֧��GSM��CDMA,֮������ */
    ulCDMAResult = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, USIMM_CDMA_ID);

    if (USIMM_SW_OK == ulCDMAResult)
    {
        USIMM_CCB_SetAIDByApp(USIMM_CDMA_APP, VOS_StrLen(USIMM_CDMA_STR), (VOS_UINT8 *)USIMM_CDMA_STR);
    }

    ulGsmResult  = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, USIMM_GSM_ID);

    if (USIMM_SW_OK == ulGsmResult)
    {
        USIMM_CCB_SetAIDByApp(USIMM_GUTL_APP, VOS_StrLen(USIMM_GSM_STR), (VOS_UINT8 *)USIMM_GSM_STR);
    }

    /* ����Ҫ���鿨��CDMA���� */
    if ((VOS_OK != ulCDMAResult)
     && (VOS_TRUE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulCUIMCheck))
    {
        USIMM_WARNING_LOG("USIMM_ICC_CheckCLStep: Select Card 7F25 is Failed");     /*��ӡ����*/

        return VOS_ERR;
    }

    /* ���ʿ���Ҫ�ж�UIM/SIM��ʼ����һ�� */
    if ((VOS_OK == ulCDMAResult)
     && (VOS_OK == ulGsmResult))
    {
        if (USIMM_NV_CDMA_APP == USIMM_GetPreferApp())
        {
            *penCardApp = USIMM_CDMA_APP;
        }
        else
        {
            *penCardApp = USIMM_GUTL_APP;
        }

        return VOS_OK;
    }

    if (VOS_OK == ulCDMAResult)
    {
        *penCardApp = USIMM_CDMA_APP;
    }
    else if (VOS_OK == ulGsmResult)
    {
        *penCardApp = USIMM_GUTL_APP;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_ICC_InitAppOrder(VOS_VOID)
{
    USIMM_CARDAPP_ENUM_UINT32           enCardApp;

    /* �����GCF���Կ�ʱ��ֻ��ʼ��GSM APP */
    if (USIMM_TEST_TYPE_GCF_SIM == USIMM_CCB_GetTestCardType())
    {
        if (USIMM_NV_CDMA_APP == USIMM_GetPreferApp())
        {
            USIMM_COMM_StoreAppSN(USIMM_CDMA_APP);
        }
        else
        {
            USIMM_COMM_StoreAppSN(USIMM_GUTL_APP);
        }

        return USIMM_COMM_INIT_SUCC;
    }

    /* ����BALONG+VIAƴƬʹ��״̬�жϳ�ʼ��˳�� */
    if (VOS_OK == USIMM_ICC_CheckCLStep(&enCardApp))
    {
        USIMM_COMM_StoreAppSN(enCardApp);

        return USIMM_COMM_INIT_REMOVE_RESET;
    }

    return USIMM_COMM_INIT_FATAL_FAIL;
}


USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InsertCommFileToPool(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          i;

    /* ��֤MF����ѡ�� */
    USIMM_ClearCurFileInfo(USIMM_UNLIMIT_AUTO);

    ulResult = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NEED_FCP, USIMM_MF_ID);

    if (ulResult != VOS_OK)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InsertCommFileToPool: Select MF is Failed");

        /*����ǰ������*/
        return USIMM_INITSTEPS_FAIL;
    }

    /* ��ʼ����ǰMF�µ��ļ����ļ����У�����ΪGUTL */
    for(i=0; i<USIMM_INITFIRST_FILENUM; i++)
    {
        if (USIMM_ICCID_ID == gausInitFileOne[i])
        {
            ulResult = USIMM_InsertFileToPool(USIMM_UNLIMIT_AUTO, gausInitFileOne[i]);
        }
        else
        {
            ulResult = USIMM_SelectFileByDefFileId(USIMM_UNLIMIT_AUTO, USIMM_NO_NEED_FCP, gausInitFileOne[i]);
        }

        if(VOS_OK != ulResult)/*�жϽ��*/
        {
            USIMM_WARNING_LOG("USIMM_ICC_InsertCommFileToPool: Select File under MF is Failed");
        }
    }

    USIMM_INFO_LOG("USIMM_ICC_InsertCommFileToPool: Init Card File First Step 1 Finished");

    return USIMM_INITSTEPS_SUCCESS;
}


USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_ICC_InitCard(VOS_VOID)
{
    VOS_UINT32                          ulStep;
    USIMM_COMMINIT_RST_ENUM_UINT32      enInitRslt = USIMM_COMM_INIT_FATAL_FAIL;

    /* ICC����ʼ�� */
    for (ulStep = 0; ulStep < ARRAYSIZE(g_aICCCommInitProcFuncTbl); ulStep++)
    {
        if (USIMM_FUNC_UNAVAILABLE == g_aICCCommInitProcFuncTbl[ulStep].enStatus)
        {
            continue;
        }

        enInitRslt = g_aICCCommInitProcFuncTbl[ulStep].pProcFun();

        /* ��ʼ��ʧ��ֱ�ӷ��� */
        if ((USIMM_COMM_INIT_NORMAL_FAIL == enInitRslt)
         || (USIMM_COMM_INIT_FATAL_FAIL == enInitRslt))
        {
            return USIMM_COMM_INIT_FATAL_FAIL;
        }

        /* ��Ҫ�������ٴγ�ʼ�� */
        if (USIMM_COMM_INIT_RESET == enInitRslt)
        {
            ulStep = VOS_NULL_DWORD;

            continue;
        }

        if (USIMM_COMM_INIT_REMOVE_RESET == enInitRslt)
        {
            g_aICCCommInitProcFuncTbl[ulStep].enStatus = USIMM_FUNC_UNAVAILABLE;

            ulStep = VOS_NULL_DWORD;

            continue;
        }
    }

    return enInitRslt;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitSimGlobal
��������  :��ʼUSIM��ȫ�ֱ���
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimGlobal(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_CCB_SetAppChNO(0, USIMM_GUTL_APP);

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitSimADF
��������  :��ʼUSIM����DFGAM
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimADF(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    VOS_INT32                           lVoltageSwitchRst = USIMM_SCI_NONEED_CHANGEVCC;

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimADF: Step is Begin");

    ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_GSM_ID);

    if (VOS_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitSimADF: Select SIM Card DFGSM is Failed");     /*��ӡ����*/

        return USIMM_INITSTEPS_FAIL;
    }

    USIMM_COMM_SaveDFPinInfo(USIMM_GUTL_APP);

    if (0x10 == (USIMM_CCB_GetCurDFInfo(USIMM_GUTL_APP)->ucCharaByte & 0x70)) /*SIM�������ļ������ֽ��л���ѹ*/
    {
        USIMM_NORMAL_LOG("USIMM_ICC_InitSimADF: SIM Card Need Change the Voltage.");

        /*g_stUSIMMInitInfo.stUSIMMInfo.ucVoltageSwitchFlag = VOS_TRUE;*/

        /*����λʧ�ܰ����޿�����*/
        if (VOS_OK != USIMM_DLResetCard(USIMM_CHANGE_VCC, &lVoltageSwitchRst))
        {
            USIMM_ERROR_LOG("USIMM_ICC_InitSimADF:SIM Card Change the Voltage Failed.");

            return USIMM_INITSTEPS_FAIL;      /*����Ҫ�������жϴ���*/
        }

        /* ��ѹδ�л�ֱ�ӷ��� */
        if (USIMM_SCI_NONEED_CHANGEVCC == lVoltageSwitchRst)
        {
            USIMM_NORMAL_LOG("USIMM_ICC_InitSimADF: No Need to Reset, Step is OK");

            return USIMM_INITSTEPS_SUCCESS;
        }

        ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_GSM_ID);

        /* ��ѹ�л�����ѡ��һ��DFGSM */
        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_ICC_InitSimADF: Select MF is Failed");

            return USIMM_INITSTEPS_FAIL;      /*����Ҫ�������жϴ���*/
        }
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimADF: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitPINInfo
��������  :��ʼUSIM��PIN��Ϣ
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitPINInfo(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_APP_PIN_INFO_STRU            *pstPIN1Info;
    USIMM_APP_PIN_INFO_STRU            *pstPIN2Info;
    USIMM_CARDAPP_ENUM_UINT32           enCardApp;

    USIMM_NORMAL_LOG("USIMM_ICC_InitPINInfo: Step is Begin");

    enCardApp   = USIMM_CCB_GetAppTypeByCH(ucChannelNo);

    if (USIMM_UNLIMIT_APP_BUTT == enCardApp)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitPINInfo: USIMM_CCB_GetAppTypeByCH is Fail");

        return USIMM_INITSTEPS_FAIL;
    }

    pstPIN1Info = USIMM_CCB_GetPIN1InfoByApp(enCardApp);

    if (VOS_NULL_PTR == pstPIN1Info)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitPINInfo: USIMM_CCB_GetPIN1InfoByApp is Fail");

        return USIMM_INITSTEPS_FAIL;
    }

    pstPIN2Info = USIMM_CCB_GetPIN2InfoByApp(enCardApp);

    if (VOS_NULL_PTR == pstPIN2Info)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitPINInfo: USIMM_CCB_GetPIN2InfoByApp is Fail");

        return USIMM_INITSTEPS_FAIL;
    }

    USIMM_COMM_InitPINState(pstPIN1Info);

    USIMM_COMM_InitPINState(pstPIN2Info);

    USIMM_NORMAL_LOG("USIMM_ICC_InitPINInfo: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitSimECC
��������  :��ʼSIM��ECC
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimECC(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32          ulResult;

    USIMM_NORMAL_LOG("USIMM_ICC_InitPINInfo: Step is Begin");

    ulResult = USIMM_InitSimEccFile(ucChannelNo);

    if (VOS_OK == ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_ICC_InitPINInfo: Step is OK");

        return USIMM_INITSTEPS_SUCCESS;
    }
    else
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitPINInfo: Step is Fail");

        return USIMM_INITSTEPS_REMOVE;
    }
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitSimEFLP
��������  :��ʼUSIM���ļ�
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimEFLP(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32          ulResult;

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimEFLP: Step is Begin");

    ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_GSM_EFLP_ID);

    if (VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitSimEFLP: Step is Fail");

        return USIMM_INITSTEPS_REMOVE;
    }
    else
    {
        //USIMM_InitSimCardFileMap();

        USIMM_NORMAL_LOG("USIMM_ICC_InitSimEFLP: Step is OK");

        return USIMM_INITSTEPS_SUCCESS;
    }
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitSimATT
��������  :��ʼSIM��ATT���Ʋ���
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimATT(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          i;

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimATT: Step is Begin");

    /* �ж�AT&T�����Ƿ�� */
    if (VOS_FALSE == g_stUsimmFeatureCfg.unCfg.stFeatureCfg.ulAtt_flg)
    {
        USIMM_NORMAL_LOG("USIMM_ICC_InitSimATT: Step is Jump out");

        return USIMM_INITSTEPS_SUCCESS;
    }

    for (i = 0;i < ARRAYSIZE(g_aulAttSimInitFile); i++ )
    {
        (VOS_VOID)USIMM_InsertFileToPool(USIMM_GUTL_APP, g_aulAttSimInitFile[i]);
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimATT: Step is End");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitPhase
��������  :��ʼUSIM��Phase��Ϣ
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitPhase(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT8                           ucData;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;

    USIMM_NORMAL_LOG("USIMM_ICC_InitPhase: Step is Begin");

    enAppType = USIMM_CCB_GetAppTypeByCH(ucChannelNo);

    if (USIMM_CARDAPP_BUTT <= enAppType)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitPhase: USIMM_CCB_GetAppTypeByCH Error");

        return USIMM_INITSTEPS_FAIL;
    }

    /* EFphase�ļ���Ĭ��ֵΪ2�Ա������FDNBDN���̿��Լ�������ȥ */
    USIMM_CCB_SetSimPhase(enAppType, USIMM_SIM_PHASE_TWO);

    /* �жϽ�����ļ�״̬ */
    if (VOS_OK != USIMM_GetTFByDefFID(enAppType, USIMM_GSM_EFPHASE_ID, sizeof(ucData), &ucData))
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitPhase:Read EFPHASE Failed");

        return USIMM_INITSTEPS_REMOVE;
    }

    /* ���浱ǰSIM��PHASE */
    USIMM_CCB_SetSimPhase(enAppType, ucData);

    USIMM_NORMAL_LOG("USIMM_ICC_InitPhase: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitSimSST
��������  :��ʼSIM��SST
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimSST(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_ICC_InitPhase: Step is Begin");

    if (VOS_OK != USIMM_InsertFileToPool(USIMM_GUTL_APP, USIMM_GSM_EFSST_ID))
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitSST:Read EFSST File Failed");

        return USIMM_INITSTEPS_FAIL;
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitSST:Read EFSST File OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitTerminalProfile
��������  :��ʼUSIM��TerminalProfile
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitTerminalProfile(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    USIMM_STK_CFG_STRU                  stProfileContent;
    USIMM_CARDAPP_ENUM_UINT32           enAppType;

    USIMM_NORMAL_LOG("USIMM_ICC_InitTerminalProfile: Step is Begin");

    enAppType = USIMM_CCB_GetAppTypeByCH(ucChannelNo);

    if (USIMM_CARDAPP_BUTT <= enAppType)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitTerminalProfile: USIMM_CCB_GetAppTypeByCH Error");

        return USIMM_INITSTEPS_FAIL;
    }

    if (USIMM_CCB_GetSimPhase(enAppType) < USIMM_SIM_PHASE_TWO)
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitTerminalProfile: SIM Not Support SAT, Step is OK");

        return USIMM_INITSTEPS_SUCCESS;
    }

    /*��ȡNV���жϵ�ǰ��SAT״̬*/
    USIMM_COMM_GetTerminalProfile(&stProfileContent);

    ulResult = USIMM_SendTermimalProfileDownloadApdu(stProfileContent.stSimProfile.ucProfileLen,
                                                     stProfileContent.stSimProfile.aucProfile);

    if(VOS_OK != ulResult)
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitTerminalProfile: USIMM_SendTermimalProfileDownloadApdu Error");

        return USIMM_INITSTEPS_FAIL_REMOVE;
    }

    /* ATT���ƹ��̣�ʧ����Ҳ������������ʼ�� */
    USIMM_AttUpdataSupportTable(ucChannelNo);

    USIMM_NORMAL_LOG("USIMM_ICC_InitTerminalProfile: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitSimFBDN
��������  :��ʼSIM��FDN/BDN״̬
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimFBDN(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    USIMM_EFSTATUS_ENUM_UINT8           imsiState = USIMM_EFSTATUS_ACTIVE;
    USIMM_EFSTATUS_ENUM_UINT8           lociState = USIMM_EFSTATUS_ACTIVE;
    USIMM_BDNSTATUS_ENUM_UINT32         enBdnStatus;
    USIMM_FDNSTATUS_ENUM_UINT32         enFdnStatus;

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimFBDN: Step is Begin");

    /* PHASE1��SIM������Ҫ����BDN FDN���̣�ֻ�� PHASE2 PHASE2+�Ŀ�����Ҫ */
    if (USIMM_CCB_GetSimPhase(USIMM_GUTL_APP) < USIMM_SIM_PHASE_TWO)
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitSimFBDN: SIM Not Support SAT");

        return USIMM_INITSTEPS_SUCCESS;
    }

    ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_GSM_EFIMSI_ID);

    if (VOS_OK != ulResult)/*�жϽ�����ļ�״̬*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitSimFBDN: USIMM_SelectFileByDefFileId(EFIMSI) Error");

        return USIMM_INITSTEPS_FAIL;
    }

    imsiState = USIMM_CCB_GetCurEFInfo(USIMM_GUTL_APP)->enFileStatus;

    ulResult = USIMM_SelectFileByDefFileId(USIMM_GUTL_APP, USIMM_NEED_FCP, USIMM_GSM_EFLOCI_ID);

    if (VOS_OK != ulResult)/*�жϽ�����ļ�״̬*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitSimFBDN: USIMM_SelectFileByDefFileId(EFLOCI) Error");

        return USIMM_INITSTEPS_FAIL;
    }

    lociState = USIMM_CCB_GetCurEFInfo(USIMM_GUTL_APP)->enFileStatus;

    /* IMSI��LOCI��ͬʱ��Чʱ������ִ�в���Լ������ */
    if ((USIMM_EFSTATUS_DEACTIVE != imsiState) || (USIMM_EFSTATUS_DEACTIVE != lociState))
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitSimFBDN: EFIMIS or EFLOCI File status fail");
    }

    /* BDN�������� */
    USIMM_BdnCapabilityRequest(&enBdnStatus);

    USIMM_CCB_SetAppBDN(USIMM_GUTL_APP, enBdnStatus);

    /* FDN�������� */
    USIMM_FdnCapabilityRequest(&enFdnStatus);

    USIMM_CCB_SetAppFDN(USIMM_GUTL_APP, enFdnStatus);

    if (VOS_OK != USIMM_SimFDNBDNProcess())
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitSimFBDN: USIMM_SimFDNBDNProcess is Fail");
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimFBDN: Step is Over");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitSimMFile
��������  :��ʼSIM����ѡ�ļ�
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimMFile(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          ausSimInitMFile[] = {USIMM_GSM_EFIMSI_ID, USIMM_GSM_EFAD_ID};

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimMFile: Step is Begin");

    USIMM_CCB_GetFilePoolTotalGlobal()->enPoolStatus = USIMM_POOL_AVAILABLE;

    for(i = 0;i < ARRAYSIZE(ausSimInitMFile); i++ )
    {
        if(VOS_OK != USIMM_InsertFileToPool(USIMM_GUTL_APP, ausSimInitMFile[i]))
        {
            USIMM_ERROR_LOG("USIMM_ICC_InitSimMFile:Read Mandatory File Failed");

            return USIMM_INITSTEPS_FAIL;
        }
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimMFile: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitSimMFile2
��������  :��ʼSIM����ѡ�ļ�
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimMFile2(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          ausSimInitMFile[] = {USIMM_GSM_EFACC_ID,
                                                             USIMM_GSM_EFHPLMN_ID,
                                                             USIMM_GSM_EFLOCI_ID,
                                                             USIMM_GSM_EFKC_ID,
                                                             USIMM_GSM_EFBCCH_ID,
                                                             USIMM_GSM_EFFPLMN_ID};

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimMFile2: Step is Begin");

    USIMM_CCB_GetFilePoolTotalGlobal()->enPoolStatus = USIMM_POOL_AVAILABLE;

    for(i = 0;i < ARRAYSIZE(ausSimInitMFile); i++ )
    {
        if(VOS_OK != USIMM_InsertFileToPool(USIMM_GUTL_APP, ausSimInitMFile[i]))
        {
            USIMM_ERROR_LOG("v:Read Mandatory File Failed");
        }
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimMFile2: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitSimFinish
��������  :��ʼSIM�����
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimFinish(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_ICC_InitSimFinish: Step is Begin");

    USIMM_SetAccFileAccess();

	USIMM_SetImsiFile();

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimFinish: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_ReadSimOPFile
��������  :��ʼUSIM����ѡ�ļ�
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :��

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
VOS_VOID USIMM_ICC_ReadSimOPFile(VOS_VOID)
{
    VOS_UINT32                      i;

    for (i = 0; i < ARRAYSIZE(gastSimInitOFile); i++)
    {
        if (UICC_SVR_NONE != gastSimInitOFile[i].ulService)
        {
            if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(gastSimInitOFile[i].ulService))
            {
                continue;
            }
        }

        if (VOS_OK != USIMM_InsertFileToPool(USIMM_GUTL_APP, gastSimInitOFile[i].enDefFileID))
        {
            USIMM_WARNING_LOG("USIMM_ICC_InitSimOPFile: Read Optional File Failed");
        }
    }

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitSimOPFile
��������  :��ʼSIM����ѡ�ļ�
�������  :ucChannelNo  �߼�ͨ����
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��18��
   ��    ��   : zhuli
   �޸�����   : Creat

*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimOPFile(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_ICC_InitSimOPFile: Step is Begin");

    if (VOS_FALSE == USIMM_COMM_IsAndroidPhone())
    {
        /*lint -e534*/
        USIMM_SendInitCardMsg(WUEPS_PID_USIM, USIMM_INITCONTINUE_REQ);
        /*lint +e534*/
    }
    else
    {
        USIMM_ICC_ReadSimOPFile();
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitSimOPFile: Step is Begin");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitUimGlobal
��������  :��ʼUIM��ȫ�ֱ���
�������  :ucChannelNo:Channel Number
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_SUCCESS

�޶���¼  :
1. ��    ��   : 2015��3��10��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimGlobal(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_CCB_SetAppChNO(0, USIMM_CDMA_APP);

    return USIMM_INITSTEPS_SUCCESS;
}


/*****************************************************************************
�� �� ��  :USIMM_ICC_InitUimADF
��������  :��ʼUIM����ADF
�������  :ucChannelNo:Channel Number
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_FAIL/USIMM_INITSTEPS_SUCCESS

�޶���¼  :
1. ��    ��   : 2015��3��10��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimADF(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;

    VOS_INT32                           lVoltageSwitchRst = USIMM_SCI_NONEED_CHANGEVCC;

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimADF: Step is Begin");

    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_ID);

    if (VOS_OK != ulResult)
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitUimADF: Select SIM Card DFGSM is Failed");     /*��ӡ����*/

        return USIMM_INITSTEPS_FAIL;
    }

    USIMM_COMM_SaveDFPinInfo(USIMM_CDMA_APP);

    if (0x10 == (USIMM_CCB_GetCurDFInfo(USIMM_CDMA_APP)->ucCharaByte & 0x70)) /*SIM�������ļ������ֽ��л���ѹ*/
    {
        USIMM_NORMAL_LOG("USIMM_ICC_InitUimADF: SIM Card Need Change the Voltage.");

        /*����λʧ�ܰ����޿�����*/
        if (VOS_OK != USIMM_DLResetCard(USIMM_CHANGE_VCC, &lVoltageSwitchRst))
        {
            USIMM_ERROR_LOG("USIMM_ICC_InitUimADF:SIM Card Change the Voltage Failed.");

            return USIMM_INITSTEPS_FAIL;      /*����Ҫ�������жϴ���*/
        }

        /* ��ѹδ�л�ֱ�ӷ��� */
        if (USIMM_SCI_NONEED_CHANGEVCC == lVoltageSwitchRst)
        {
            return USIMM_INITSTEPS_SUCCESS;
        }

        ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_ID);
        /* ��ѹ�л�����ѡ��һ��DFCDMA */
        if (VOS_OK != ulResult)
        {
            USIMM_ERROR_LOG("USIMM_ICC_InitUimADF: Select MF is Failed");

            return USIMM_INITSTEPS_FAIL;      /*����Ҫ�������жϴ���*/
        }
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimADF: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}


/*****************************************************************************
�� �� ��  :USIMM_ICC_InitUimRuimId
��������  :UIM����ʼ��RUIMID
�������  :��
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_RST_ENUM_UINT32

�޶���¼  :
1. ��    ��   : 2015��3��10��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimRuimId(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT8                           aucRuimId[8];


    USIMM_NORMAL_LOG("USIMM_ICC_InitUimRuimId: Step is Begin");

    if (USIMM_SW_OK != USIMM_GetTFByDefFID(USIMM_CDMA_APP, USIMM_CDMA_EFRUIMID_ID, sizeof(aucRuimId), aucRuimId))/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitUimRuimId:USIMM_SendReadBinaryApdu error");
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimRuimId: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitUimECC
��������  :UIM����ʼ���������к���
�������  :��
�������  :ucChannelNo:Channel Number
�� �� ֵ  :USIMM_INITSTEPS_REMOVE/USIMM_INITSTEPS_SUCCESS

�޶���¼  :
1. ��    ��   : 2015��3��10��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimECC(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT8                          *pData;
    VOS_UINT32                          ulResult;

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimECC: Step is Begin");

    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_EFECC_ID);

    if(VOS_OK != ulResult)/*�жϽ��*/
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_SELECT_FAIL;

        /* ECC�ļ������ڵ��������PB�ϱ��ļ�����Ϊ0������ok������ֹ��ʼ������ */
        USIMM_XeccNumberInd(VOS_NULL, VOS_NULL_PTR);

        return USIMM_INITSTEPS_REMOVE;
    }

    if (USIMM_EFSTRUCTURE_TRANSPARENT != USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileType)
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_TYPE_ERR;

        USIMM_ERROR_LOG("USIMM_ICC_InitUimECC:ECC FILE TYPE error");

        /* ECC�ļ������ڵ��������PB�ϱ��ļ�����Ϊ0������ok������ֹ��ʼ������ */
        USIMM_XeccNumberInd(VOS_NULL, VOS_NULL_PTR);

        return USIMM_INITSTEPS_REMOVE;
    }

    pData = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_USIM,
                                      DYNAMIC_MEM_PT,
                                      USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->usFileLen);/*�������ݴ洢�ռ�*/

    if (VOS_NULL_PTR == pData)/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitUimECC:VOS_MemAlloc error");

        return USIMM_INITSTEPS_SUCCESS;
    }

    ulResult = USIMM_SendReadBinaryApdu(ucChannelNo,
                                        VOS_NULL,
                                        USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->usFileLen,
                                        pData);

    if (USIMM_SW_OK != ulResult)/*�жϽ��*/
    {
        g_stUSIMMInitInfo.stUSIMMInfo.enEccInitStatus = USIMM_ECC_READ_FAIL;

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pData);
        /*lint +e534*/

        USIMM_ERROR_LOG("USIMM_ICC_InitUimECC:USIMM_SendReadBinaryApdu error");

        /* ��ȡ�ļ�ʧ����ΪECC�ļ������ڣ���PB�ϱ��ļ�����Ϊ0������ok������ֹ��ʼ������ */
        USIMM_XeccNumberInd(VOS_NULL, VOS_NULL_PTR);

        return USIMM_INITSTEPS_SUCCESS;
    }

    /* �ϱ���ǰ��Ecc�������� */
    USIMM_XeccNumberInd(USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->usFileLen, pData);

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_USIM, pData);
    /*lint +e534*/

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimECC: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitCST
��������  :��ʼ��UIM��Cdma Service Table
�������  :ucChannelNo:Channel Number
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_SUCCESS

�޶���¼  :
1. ��    ��   : 2015��3��10��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitCST(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_ICC_InitCST: Step is Begin");

    /* ��ʼ��ʧ��Ҳ�����ش��󣬼�����ʼ������ */
    if (VOS_OK != USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CDMA_EFCST_ID))
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitCST:Read EFCST File Failed");
    }
    else
    {
        USIMM_NORMAL_LOG("USIMM_ICC_InitSST:Read EFCST File OK");
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitCST: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}


/*****************************************************************************
�� �� ��  :USIMM_ICC_InitTerminalProfile
��������  :��ʼUSIM����FdnBdn
�������  :ucChannelNo:Channel Number
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_SUCCESS

�޶���¼  :
1. ��    ��   : 2015��3��10��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimFdnBdn(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_ICC_InitUimFdnBdn: Step is Begin");

    if (VOS_OK != USIMM_ICC_InitUimFdnStatus())
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitUimFdnBdn: USIMM_ICC_InitUimFdnStatus Error");
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimFdnBdn: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_InitUimFDNBDNStatus
��������  :��ʼ��UIM����ǰ��FDN/BDN״̬��
�������  :��
�������  :��
�� �� ֵ  :VOS_OK/VOS_ERR

�޶���¼  :
1. ��    ��   : 2015��3��10��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ICC_InitUimFdnStatus(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    USIMM_EFSTATUS_ENUM_UINT8           enImsimState    = USIMM_EFSTATUS_ACTIVE;
    USIMM_EFSTATUS_ENUM_UINT8           enImsitState    = USIMM_EFSTATUS_ACTIVE;
    USIMM_EFSTATUS_ENUM_UINT8           enTmsiState     = USIMM_EFSTATUS_ACTIVE;
    USIMM_FDNSTATUS_ENUM_UINT32         enFDNStatus     = USIMM_FDNSTATUS_OFF;
    USIMM_FILEPATH_INFO_STRU            stFilePath;

    /*lint -e534*/
    VOS_MemSet(&stFilePath, 0, sizeof(USIMM_FILEPATH_INFO_STRU));
    /*lint +e534*/

    /* ֻ�� PHASE2/PHASE2+�Ŀ�����Ҫ */
    if (USIMM_CCB_GetSimPhase(USIMM_CDMA_APP) < USIMM_SIM_PHASE_TWO)
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitUimFdnStatus: SIM Not Support SAT");

        return VOS_OK;
    }

    /* ��ʼ��IMSIM��״̬ */
    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_EFIMSIM_ID);

    if (VOS_OK != ulResult)/*�жϽ�����ļ�״̬*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitUimFdnStatus: USIMM_SelectFileByDefFileId(EF_CUIM_IMSIM) Error");

        return VOS_ERR;
    }

    enImsimState = USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus;

    /* ��ʼ��IMSIT��״̬ */
    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_EFIMSIT_ID);

    if (VOS_OK != ulResult)/*�жϽ�����ļ�״̬*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitUimFdnStatus: USIMM_SelectFileByDefFileId(EF_CUIM_IMSIT) Error");

        return VOS_ERR;
    }

    enImsitState = USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus;

    /* ��ʼ��TMSI��״̬ */
    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_EFTMSI_ID);

    if (VOS_OK != ulResult)/*�жϽ�����ļ�״̬*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitUimFdnStatus: USIMM_SelectFileByDefFileId(EF_CUIM_IMSIT) Error");

        return VOS_ERR;
    }

    enTmsiState = USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus;

    /* IMSI��LOCI��ͬʱ��Чʱ������ִ�в���Լ������ */
    if ((USIMM_EFSTATUS_DEACTIVE != enImsimState)
     || (USIMM_EFSTATUS_DEACTIVE != enImsitState)
     || (USIMM_EFSTATUS_DEACTIVE != enTmsiState))
    {
        USIMM_WARNING_LOG("USIMM_ICC_InitUimFdnStatus: File status Error");
    }

    /* UIM��û��BDN���� */
    USIMM_CCB_SetAppBDN(USIMM_CDMA_APP, USIMM_BDNSTATUS_OFF);

    /* FDN�������� */
    USIMM_ICC_FdnCapabilityRequest(&enFDNStatus);

    USIMM_CCB_SetAppFDN(USIMM_CDMA_APP, enFDNStatus);

    return USIMM_ICC_UimFdnProcess();
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_FdnCapabilityRequest
��������  :��ʼ��UIM��FDN��������
�������  :��
�������  :USIMM_FDNSTATUS_ENUM_UINT32 *pulFdnStatus
�� �� ֵ  :��

�޶���¼  :
1. ��    ��   : 2015��3��10��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID USIMM_ICC_FdnCapabilityRequest(
    USIMM_FDNSTATUS_ENUM_UINT32        *pulFdnStatus
)
{
    VOS_UINT32                          ulResult;

    /* ��FDN״̬��CST�ļ���δallocated and activated,FDNδ���� */
    if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(UIM_SVR_FDN))
    {
        *pulFdnStatus = USIMM_FDNSTATUS_OFF;

        USIMM_NORMAL_LOG("USIMM_ICC_FdnCapabilityRequest: USIMM_FDNSTATUS_OFF");

        return;
    }

    /* ��ADN״̬��CST�ļ���δallocated and activated,FDN���� */
    if (PS_USIM_SERVICE_NOT_AVAILIABLE == USIMM_IsServiceAvailable(UIM_SVR_ADN))
    {
        *pulFdnStatus = USIMM_FDNSTATUS_ON;

        USIMM_NORMAL_LOG("USIMM_ICC_FdnCapabilityRequest: USIMM_FDNSTATUS_ON");

        return;
    }

    /* ADN�ļ�������,FDN���� */
    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_TELE_EFADN_ID);

    if (VOS_OK != ulResult)
    {
        *pulFdnStatus = USIMM_FDNSTATUS_ON;

        USIMM_NORMAL_LOG("USIMM_ICC_FdnCapabilityRequest: USIMM_FDNSTATUS_ON");
    }
    else
    {
        /* ADN�ļ���Ч,FDN���� */
        if (USIMM_EFSTATUS_DEACTIVE == USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus)
        {
            *pulFdnStatus = USIMM_FDNSTATUS_ON;

            USIMM_NORMAL_LOG("USIMM_ICC_FdnCapabilityRequest: USIMM_FDNSTATUS_ON");
        }
        /* ADN�ļ���Ч,FDNδ���� */
        else
        {
            *pulFdnStatus = USIMM_FDNSTATUS_OFF;

            USIMM_NORMAL_LOG("USIMM_ICC_FdnCapabilityRequest: USIMM_FDNSTATUS_OFF");
        }
    }

    return;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_UimFdnProcess
��������  :���UIM����FDN���ܿ�����ĳ�ʼ��������ļ���Ч�Ĺ��̡�
�������  :��
�������  :��
�� �� ֵ  :VOS_ERR/VOS_OK

�޶���¼  :
1. ��    ��   : 2015��3��10��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_ICC_UimFdnProcess(VOS_VOID)
{

    /* �ָ�IMSIM�ļ� */
    if (VOS_OK != USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_EFIMSIM_ID))
    {
        USIMM_ERROR_LOG("USIMM_ICC_UimFdnProcess: USIMM_SelectFileByDefFileId(EFIMSIM) Error");

        return VOS_ERR;
    }

    if (USIMM_EFSTATUS_DEACTIVE == USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus)
    {
        /*lint -e534*/
        (VOS_VOID)USIMM_SendActivateApdu(USIMM_APDU_BASECHANNEL);
        /*lint +e534*/
    }

    /* �ָ�IMSIT�ļ� */
    if (VOS_OK != USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_EFIMSIT_ID))/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_UimFdnProcess: USIMM_SelectFileByDefFileId(EFIMSIT) Error");

        return VOS_ERR;
    }

    if (USIMM_EFSTATUS_DEACTIVE == USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus)
    {
        /*lint -e534*/
        (VOS_VOID)USIMM_SendActivateApdu(USIMM_APDU_BASECHANNEL);
        /*lint +e534*/
    }

    /* �ָ�TMSI�ļ� */
    if (VOS_OK != USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, USIMM_NEED_FCP, USIMM_CDMA_EFTMSI_ID))/*�жϽ��*/
    {
        USIMM_ERROR_LOG("USIMM_ICC_UimFdnProcess: USIMM_SelectFileByDefFileId(EFTMSI) Error");

        return VOS_ERR;
    }

    if (USIMM_EFSTATUS_DEACTIVE == USIMM_CCB_GetCurEFInfo(USIMM_CDMA_APP)->enFileStatus)
    {
        /*lint -e534*/
        (VOS_VOID)USIMM_SendActivateApdu(USIMM_APDU_BASECHANNEL);
        /*lint +e534*/
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitUimMFile
��������  :��ʼUIM��M���͵��ļ�
�������  :ucChannelNo:Channel Number
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_SUCCESS

�޶���¼  :
1. ��    ��   : 2015��3��10��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimMFile(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_ICC_InitUimMFile: Step is Begin");

    /*Read EF AD*/
    (VOS_VOID)USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CDMA_EFAD_ID);

    /*Read EF Revision*/
    (VOS_VOID)USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CDMA_EFREVISION_ID);

    (VOS_VOID)USIMM_InsertFileToPool(USIMM_CDMA_APP, USIMM_CDMA_EFIMSIM_ID);

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimMFile: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitUimMFile2
��������  :��ʼUIM��M2���͵��ļ�
�������  :ucChannelNo:Channel Number
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_SUCCESS

�޶���¼  :
1. ��    ��   : 2015��3��10��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimMFile2(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          aucFileList[] = {USIMM_CDMA_EFUSGIND_ID,
                                                         USIMM_CDMA_EFSP_ID,
                                                         USIMM_CDMA_EFIMSIM_ID,
                                                         USIMM_CDMA_EFIMSIT_ID,
                                                         USIMM_CDMA_EFACCOLC_ID,
                                                         USIMM_CDMA_EFPRL_ID,
                                                         USIMM_CDMA_EFEPRL_ID,
                                                         USIMM_CDMA_EFTMSI_ID};
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           *pucData;

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimMFile2: Step is Begin");

    for (i=0; i<ARRAYSIZE(aucFileList); i++)
    {
        if(VOS_OK == USIMM_GetDefTFMem(USIMM_CDMA_APP, aucFileList[i], &usDataLen, &pucData))
        {
            (VOS_VOID)VOS_MemFree(WUEPS_PID_USIM, pucData);
        }
    }

    USIMM_NORMAL_LOG("USIMM_ICC_InitUimMFile2: Step is OK");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitUimEFMecrp
��������  :��ʼUIM�������и������ļ�EF MECRP
�������  :ucChannelNo:Channel Number
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_SUCCESS/USIMM_INITSTEPS_REMOVE

�޶���¼  :
1. ��    ��   : 2015��3��10��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimEFMecrp(
    VOS_UINT8                           ucChannelNo
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucUpdate[2];

    ulResult = USIMM_SelectFileByDefFileId(USIMM_CDMA_APP, 
                                           USIMM_NEED_FCP, 
                                           USIMM_CDMA_EFMECRP_ID);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimEFMecrp: Select File is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    ulResult = USIMM_COMM_GetMecrpValue(&aucUpdate[0], &aucUpdate[1]);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimEFMecrp: USIMM_COMM_GetMecrpValue is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    ulResult = USIMM_SendUpdateBinaryApdu(ucChannelNo, sizeof(aucUpdate), aucUpdate);

    if (VOS_OK != ulResult)
    {
        USIMM_NORMAL_LOG("USIMM_UICC_InitCsimEFMecrp: Update is Error");

        return USIMM_INITSTEPS_REMOVE;
    }

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitUimFinish
��������  :��ʼUIM�����̽���
�������  :ucChannelNo:Channel Number
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_SUCCESS/USIMM_INITSTEPS_REMOVE

�޶���¼  :
1. ��    ��   : 2015��3��10��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimFinish(
    VOS_UINT8                           ucChannelNo
)
{
    USIMM_NORMAL_LOG("USIMM_ICC_InitUimFinish: Step is Over");

    return USIMM_INITSTEPS_SUCCESS;
}

/*****************************************************************************
�� �� ��  :USIMM_ICC_InitStoreEsnMeid
��������  :��ʼUIM��������MANAGE ESN MEID
�������  :ucChannelNo:Channel Number
�������  :��
�� �� ֵ  :USIMM_INITSTEPS_SUCCESS/USIMM_INITSTEPS_REMOVE

�޶���¼  :
1. ��    ��   : 2015��8��28��
   ��    ��   : H00300778
   �޸�����   : Creat
*****************************************************************************/
USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitStoreEsnMeid(
    VOS_UINT8                           ucChannelNo
)
{

    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulSvcStatus;
    NV_MEID_STRU                        stMeId;
    NV_PESN_STRU                        stPEsn;
    USIMM_APDU_RSP_STRU                 stRspData = {0};
    VOS_UINT8                           aucEsnMeid[USIMM_STORE_ESNMEID_MAX];

    USIMM_NORMAL_LOG("USIMM_ICC_InitStoreEsnMeid: Step is Begin");

    if (NV_OK != NV_Read(en_NV_Item_MEID, &stMeId, sizeof(stMeId)))
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitStoreEsnMeid: NV_Read en_NV_Item_MEID Failed");

        return USIMM_INITSTEPS_FAIL;
    }

    ulSvcStatus = USIMM_IsServiceAvailable(UIM_SVR_MEID);

    if (PS_USIM_SERVICE_AVAILIABLE == ulSvcStatus)
    {
        aucEsnMeid[0] = MEID_NV_DATA_LEN_NEW;

        (VOS_VOID)VOS_MemCpy(aucEsnMeid + 1, stMeId.aucMeID, MEID_NV_DATA_LEN_NEW);

        ulResult = USIMM_SendStoreESNMEIDApdu(UICC_STORE_MEID_P1,
                                              ucChannelNo,
                                              aucEsnMeid,
                                              &stRspData);

        if (VOS_OK == ulResult)
        {
            g_ucStoreEsMeidResult = stRspData.aucRsp[0];

            USIMM_NORMAL_LOG("USIMM_ICC_InitStoreEsnMeid: Step is OK");

            return USIMM_INITSTEPS_SUCCESS;
        }
    }

    if (NV_OK != NV_Read(en_NV_Item_PESN, &stPEsn, sizeof(stPEsn)))
    {
        USIMM_ERROR_LOG("USIMM_ICC_InitStoreEsnMeid: NV_Read en_NV_Item_PESN Failed");

        return USIMM_INITSTEPS_FAIL;
    }

    aucEsnMeid[0] = PESN_NV_DATA_LEN;

    (VOS_VOID)VOS_MemCpy(aucEsnMeid + 1, stPEsn.aucPEsn, PESN_NV_DATA_LEN);

    ulResult = USIMM_SendStoreESNMEIDApdu(UICC_STORE_ESN_P1,
                                          ucChannelNo,
                                          aucEsnMeid,
                                          &stRspData);

    if (VOS_OK == ulResult)
    {
        g_ucStoreEsMeidResult = stRspData.aucRsp[0];

        USIMM_NORMAL_LOG("USIMM_ICC_InitStoreEsnMeid: Step is OK");

        return USIMM_INITSTEPS_SUCCESS;
    }

    USIMM_ERROR_LOG("USIMM_ICC_InitStoreEsnMeid: Command Send error");

    g_ucStoreEsMeidResult = VOS_NULL;

    /* ���˲����Ƴ����������� */
    return USIMM_INITSTEPS_REMOVE;
}

/*****************************************************************************
�� �� ��  : USIMM_GetAppInitList
��������  : ʵ���˿�������ز���
�������  : API���·���Ϣ����
�������  : ��
�� �� ֵ  : VOS_ERR
           VOS_OK
�޶���¼  :
1. ��    ��   : 2007��7��10��
   ��    ��   : zhuli
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 USIMM_GetAppInitList(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_INITAPPLIST_FUNC            **ppstFuncList,
    VOS_UINT8                          *pucListNum
)
{
    if (USIMM_GUTL_APP == enAppType)
    {
        if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
        {
            *ppstFuncList   = g_aSIMInitProcFuncTbl;
            *pucListNum     = ARRAYSIZE(g_aSIMInitProcFuncTbl);
        }
        else if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
        {
            *ppstFuncList   = g_aUSIMInitProcFuncTbl;
            *pucListNum     = ARRAYSIZE(g_aUSIMInitProcFuncTbl);
        }
        else
        {
            return VOS_ERR;
        }
    }
    else if (USIMM_CDMA_APP == enAppType)
    {
        if (USIMM_PHYCARD_TYPE_ICC == USIMM_CCB_GetCardType())
        {
            *ppstFuncList   = g_aUIMInitProcFuncTbl;
            *pucListNum     = ARRAYSIZE(g_aUIMInitProcFuncTbl);
        }
        else if (USIMM_PHYCARD_TYPE_UICC == USIMM_CCB_GetCardType())
        {
            *ppstFuncList   = g_aCSIMInitProcFuncTbl;
            *pucListNum     = ARRAYSIZE(g_aCSIMInitProcFuncTbl);
        }
        else
        {
            return VOS_ERR;
        }
    }
    else if (USIMM_IMS_APP == enAppType)
    {
        *ppstFuncList   = g_aISIMInitProcFuncTbl;
        *pucListNum     = ARRAYSIZE(g_aISIMInitProcFuncTbl);
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 USIMM_INIT_GetUiccCommInitFuncNum(VOS_VOID)
{
    return ARRAYSIZE(g_aUICCCommInitProcFuncTbl);
}


USIMM_COMM_CARD_INIT_FUNC* USIMM_INIT_GetUiccCommInitFunc(VOS_VOID)
{
    return g_aUICCCommInitProcFuncTbl;
}


USIMM_INITAPPLIST_FUNC*  USIMM_GetInitFunsByAppType(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    PFAPPSETPINITPROC                   pInitFunc
)
{
    USIMM_INITAPPLIST_FUNC             *pInitFuncList = VOS_NULL_PTR;
    VOS_UINT8                           ucInitFuncNum = 0;
    VOS_UINT8                           ucIndex       = 0;

    if (VOS_ERR == USIMM_GetAppInitList(enAppType, &pInitFuncList, &ucInitFuncNum))
    {
        USIMM_WARNING_LOG("USIMM_INIT_GetFuncStatus:USIMM_RefreshGetAppInitList error");

        return VOS_NULL_PTR;
    }

    for (ucIndex = 0; ucIndex < ucInitFuncNum; ucIndex++)
    {
        if (pInitFuncList[ucIndex].pProcFun == pInitFunc)
        {
            return &pInitFuncList[ucIndex];
        }
    }

    return VOS_NULL_PTR;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif
