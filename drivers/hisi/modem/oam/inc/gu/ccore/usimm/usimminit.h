

#ifndef __USIMM_INIT_H__
#define __USIMM_INIT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "usimmbase.h"

#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define USIMM_ACTIVEADF_OFFSET              (1)

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/


/*****************************************************************************
 ö����    : USIMM_FUNCSTATUS_ENUM
 �ṹ˵��  : �����Ƿ���Ч
*****************************************************************************/
enum USIMM_FUNCSTATUS_ENUM
{
    USIMM_FUNC_AVAILABLE   = 0,
    USIMM_FUNC_UNAVAILABLE,
    USIMM_FUNC_STATUS_BUTT,
};
typedef VOS_UINT32      USIMM_FUNCSTATUS_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_COMMINIT_RST_ENUM
 �ṹ˵��  : ������ʼ�����̷���ֵ
*****************************************************************************/
enum USIMM_COMMINIT_RST_ENUM
{
    USIMM_COMM_INIT_SUCC        = VOS_OK,               /* �ɹ� */
    USIMM_COMM_INIT_FATAL_FAIL,                         /* ��������ʹ�� */
    USIMM_COMM_INIT_NORMAL_FAIL,                        /* ���Գ���ICC�����ͳ�ʼ�� */
    USIMM_COMM_INIT_REMOVE_RESET,                       /* �Ƴ���ǰ���貢���³�ʼ���� */
    USIMM_COMM_INIT_RESET,                              /* ���³�ʼ���� */

    USIMM_COMM_INIT_RSLT_BUTT
};
typedef VOS_UINT32 USIMM_COMMINIT_RST_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_INITSTEPS_RST_ENUM
 �ṹ˵��  : Ӧ�ó�ʼ�����践��ֵ
*****************************************************************************/
enum USIMM_INITSTEPS_RST_ENUM
{
    USIMM_INITSTEPS_SUCCESS     = VOS_OK,               /* �ɹ� */
    USIMM_INITSTEPS_REMOVE,                             /* �Ƴ���ǰ��������������� */
    USIMM_INITSTEPS_SUSPEND,                            /* �����ʼ������ */
    USIMM_INITSTEPS_FAIL,                               /* ִ��ʧ�� */
    USIMM_INITSTEPS_FAIL_REMOVE,                        /* ִ��ʧ�ܲ��Ƴ���ǰ���� */
    USIMM_INITSTEPS_BUTT
};
typedef VOS_UINT32  USIMM_INITSTEPS_RST_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_INITAPPS_RST_ENUM
 �ṹ˵��  : Ӧ�ó�ʼ������ֵ
*****************************************************************************/
enum USIMM_INITAPPS_RST_ENUM
{
    USIMM_INITAPPS_SUCCESS      = VOS_OK,               /* �ɹ� */
    USIMM_INITAPPS_RESET,                               /* ���³�ʼ��Ӧ�� */
    USIMM_INITAPPS_FAIL,                                /* Ӧ�ó�ʼ��ʧ�� */
    USIMM_INITAPPS_BUTT
};
typedef VOS_UINT32  USIMM_INITAPPS_RST_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_ISIM_SERVICE_ENUM
 �ṹ˵��  : ISIM����λ�жϹ�ϵ
*****************************************************************************/
enum USIMM_ISIM_SERVICE_ENUM
{
    USIMM_ISIM_SERVICE_OR      = VOS_OK,                /* ���ϵ */
    USIMM_ISIM_SERVICE_AND,                             /* ���ϵ */
    USIMM_ISIM_SERVICE_BUTT
};
typedef VOS_UINT32  USIMM_ISIM_SERVICE_ENUM_UINT16;

/*****************************************************************************
  4 STRUCT����
*****************************************************************************/


typedef USIMM_COMMINIT_RST_ENUM_UINT32 (*PAPPINITPROC)(VOS_VOID);


typedef struct
{
    PAPPINITPROC                        pProcFun;        /* ������ */
    USIMM_FUNCSTATUS_ENUM_UINT32        enStatus;
}USIMM_COMM_CARD_INIT_FUNC;
typedef USIMM_INITSTEPS_RST_ENUM_UINT32 (*PFAPPSETPINITPROC)(VOS_UINT8 ucChannelNo);


typedef struct
{
    PFAPPSETPINITPROC                   pProcFun;        /* ������ */
    USIMM_FUNCSTATUS_ENUM_UINT32        enStatus;
}USIMM_INITAPPLIST_FUNC;
typedef struct
{
    USIMM_INITAPPLIST_FUNC             *pFuncList;
    VOS_UINT32                         ulListNum;
}USIMM_INITAPPLIST_STRU;


typedef struct
{
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    USIMM_INITSTEPS_RST_ENUM_UINT32     enAppStepResult;
    USIMM_INITAPPS_RST_ENUM_UINT32      enAppInitResult;
    VOS_UINT8                           ucInitTimes;
    VOS_UINT8                           ucCurStep;
    VOS_UINT8                           ucChannelNo;
    VOS_UINT8                           ucInitListNum;
    USIMM_INITAPPLIST_FUNC             *pfList;
}USIMM_INITAPPSCTRL_STRU;


typedef struct
{
    USIMM_DEF_FILEID_ENUM_UINT32        enDefFileId;
    VOS_UINT32                          ulFService;
    VOS_UINT16                          usSService;
    USIMM_ISIM_SERVICE_ENUM_UINT16      enCheckType;
}USIMM_OPFILE_ISIM_LIST_STRU;

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 ��������
*****************************************************************************/

extern VOS_VOID USIMM_COMM_ClearInitCtrlGlobal(VOS_VOID);

extern VOS_VOID USIMM_COMM_ResetInitGlobal(VOS_VOID);

extern VOS_VOID USIMM_COMM_InitCommFuncTble(VOS_VOID);

extern VOS_VOID USIMM_COMM_ResetInitListStatus(VOS_VOID);

extern VOS_VOID USIMM_COMM_ResetPIN1Global(VOS_VOID);

extern USIMM_INITAPPLIST_FUNC* USIMM_COMM_GetAppInitList(
    USIMM_PHYCARD_TYPE_ENUM_UINT32          enCardType,
    USIMM_CARDAPP_ENUM_UINT32               enAppType
);

extern VOS_UINT32 USIMM_COMM_GetAppInitNum(
    USIMM_PHYCARD_TYPE_ENUM_UINT32          enCardType,
    USIMM_CARDAPP_ENUM_UINT32               enAppType
);

extern VOS_UINT32 USIMM_COMM_IsGcfSim(
    VOS_UINT8                          *pucATR,
    VOS_UINT32                          ulATRLen
);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_COMM_DecodeATR(VOS_VOID);

extern USIMM_CARDAPP_ENUM_UINT32 USIMM_COMM_GetMainAppType(VOS_VOID);

extern VOS_VOID USIMM_COMM_GetTerminalProfile(
    USIMM_STK_CFG_STRU                 *pstProfileContent
);

extern VOS_UINT32 USIMM_COMM_InitPINApp(VOS_VOID);

extern VOS_UINT32 USIMM_COMM_InitCard(
    USIMM_MsgBlock                     *pstMsg
);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_COMM_InitCardApps(VOS_VOID);

extern VOS_UINT32 USIMM_COMM_GetAppInitFuncs(VOS_VOID);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_COMM_InitAppList(
    USIMM_INITAPPSCTRL_STRU            *pstInitList
);

extern USIMM_INITAPPS_RST_ENUM_UINT32 USIMM_COMM_CheckInitStepResult(
    USIMM_INITSTEPS_RST_ENUM_UINT32         enResult,
    USIMM_INITAPPSCTRL_STRU                *pstInitList
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_COMM_AutoVerifyPIN(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_COMM_InitAppState(
    VOS_UINT8                           ucChannelNo
);

extern VOS_VOID USIMM_COMM_InitPINState(
    USIMM_APP_PIN_INFO_STRU            *pstPINInfo
);

extern VOS_VOID USIMM_COMM_SaveDFPinInfo(
    USIMM_CARDAPP_ENUM_UINT32               enAppType
);

extern VOS_VOID USIMM_COMM_StoreAppSN(USIMM_CARDAPP_ENUM_UINT32 enAppType);

extern VOS_UINT32 USIMM_COMM_IsAndroidPhone(VOS_VOID);

extern VOS_UINT32 USIMM_COMM_GetMecrpValue(
    VOS_UINT8                           *pucSCM, 
    VOS_UINT8                           *pucMOBP);

extern VOS_VOID USIMM_COMM_InitOPFile(VOS_VOID);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_DecodeAppAid(
    VOS_UINT8                          *pucdata,
    VOS_UINT16                          usFileLen,
    VOS_UINT8                           ucRecordLen
);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_DecodeEFDIR(VOS_VOID);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_CUIMCheck(VOS_VOID);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_DecodeATRStep2(VOS_VOID);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_InitGlobalVar(VOS_VOID);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_InitCardTypeByATR(VOS_VOID);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_InsertCommFileToPool(VOS_VOID);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_ProfileDownload(VOS_VOID);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_InitCard(VOS_VOID);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_SortAppSN(VOS_VOID);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_UICC_InitIsimSimuState(VOS_VOID);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 UISMM_UICC_InitCardOpenChannel(
    USIMM_INITAPPSCTRL_STRU            *pstInitList);


extern VOS_UINT32 USIMM_UICC_InitPINRemainTime(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucPINNo,
    VOS_UINT8                          *pucPINTime
);

extern VOS_UINT32 USIMM_UICC_InitPUKRemainTime(
    VOS_UINT8                           ucChannelID,
    VOS_UINT8                           ucPINNo,
    VOS_UINT8                          *pucPUKTime
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimGlobal(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimADF(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitPINTime(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimECC(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimEFLI(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimATT(
    VOS_UINT8                           ucChannelNo
);

extern VOS_VOID USIMM_UICC_InitUsimFBDNStatus(VOS_VOID);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimMFile(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimMFile2(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimFinish(
    VOS_UINT8                           ucChannelNo
);

extern VOS_VOID USIMM_UICC_ReadUsimOPFile(VOS_VOID);

USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitUsimOPFile(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimGlobal(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimADF(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimECC(
    VOS_UINT8                           ucChannelNo
);

extern VOS_VOID USIMM_UICC_InitCsimFDNStatus(VOS_VOID);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimMFile(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimMFile2(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimEFMecrp(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimFinish(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitVIACsimFinish(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitCsimOPFile(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitIsimGlobal(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitIsimADF(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitIsimMFile(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitIsimFinish(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitIsimOPFile(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_ICC_InitGlobalVar(VOS_VOID);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_ICC_InitCardTypeByATR(VOS_VOID);

extern VOS_UINT32 USIMM_ICC_CheckCLStep(
    USIMM_CARDAPP_ENUM_UINT32          *penCardApp
);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_ICC_InitAppOrder(VOS_VOID);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InsertCommFileToPool(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_COMMINIT_RST_ENUM_UINT32 USIMM_ICC_InitCard(VOS_VOID);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimGlobal(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimADF(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitPINInfo(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimECC(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimEFLP(
    VOS_UINT8                           ucChannelNo
);

USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimATT(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitPhase(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimSST(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitTerminalProfile(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimFBDN(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimMFile(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimMFile2(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimFinish(
    VOS_UINT8                           ucChannelNo
);

extern VOS_VOID USIMM_ICC_ReadSimOPFile(VOS_VOID);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitSimOPFile(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimGlobal(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimADF(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimRuimId(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimECC(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitCST(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimFdnBdn(
    VOS_UINT8                           ucChannelNo
);

extern VOS_UINT32 USIMM_ICC_InitUimFdnStatus(VOS_VOID);

extern VOS_VOID USIMM_ICC_FdnCapabilityRequest(
    USIMM_FDNSTATUS_ENUM_UINT32        *pulFdnStatus
);

extern VOS_UINT32 USIMM_ICC_UimFdnProcess(VOS_VOID);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimMFile(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimMFile2(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_UICC_InitStoreMeid(
    VOS_UINT8                           ucChannelNo
);


extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimEFMecrp(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitStoreEsnMeid(
    VOS_UINT8                           ucChannelNo
);

extern USIMM_INITSTEPS_RST_ENUM_UINT32 USIMM_ICC_InitUimFinish(
    VOS_UINT8                           ucChannelNo
);

extern VOS_VOID USIMM_UICC_InitCUIMEccFile(VOS_VOID);

extern VOS_VOID USIMM_UICC_InitCUIMCstFile(VOS_VOID);

extern VOS_VOID USIMM_UICC_InitCSIMEstFile(VOS_VOID);

extern VOS_UINT32 USIMM_GetAppInitList(USIMM_CARDAPP_ENUM_UINT32         enAppType,
                                                  USIMM_INITAPPLIST_FUNC          **ppstFuncList,
                                                  VOS_UINT8                       *pucListNum);

extern VOS_UINT32 USIMM_INIT_GetUiccCommInitFuncNum(VOS_VOID);

extern USIMM_COMM_CARD_INIT_FUNC* USIMM_INIT_GetUiccCommInitFunc(VOS_VOID);

extern USIMM_INITAPPLIST_FUNC*  USIMM_GetInitFunsByAppType(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    PFAPPSETPINITPROC                   pInitFunc
);

#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of UsimmDL.h*/


