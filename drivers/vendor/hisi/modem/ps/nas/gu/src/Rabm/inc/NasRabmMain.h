
#ifndef _NAS_RABM_MAIN_H_
#define _NAS_RABM_MAIN_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "AtRabmInterface.h"
#include "NVIM_Interface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define NAS_RABM_GetProFuncTblAddr(enSysMode)                   (g_pstNasRabmProcFuncTbl[enSysMode])
#define NAS_RABM_SetProFuncTblAddr(enSysMode, pstProcFucTbl)    (g_pstNasRabmProcFuncTbl[enSysMode] = (pstProcFucTbl))

#define NAS_RABM_GetCurrentSysMode()                (g_enNasRabmSysMode)
#define NAS_RABM_SetSysMode(enMode)                 (g_enNasRabmSysMode = (enMode))

/*define AP Status Mask*/
#define VP_AGPS_STATUS_MASK             (0x00000002)
#define VP_MMS_STATUS_MASK              (0x00000004)
#define VP_TETHERING_STATUS_MASK        (0x00000010)
#define VP_WIFI_HOTSPOT_STATUS_MASK     (0x00000020)
#define VP_BT_SHARING_STATUS_MASK       (0x00000040)
#define VP_SCREEN_STATUS_MASK           (0x00000080)
#define VP_ENABLE_MASK                  (0x00000100)

/* ���²�ѯ GMM ������*/
#define VP_REQRY_GMM_MAX_TIMES          (1)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern GMM_RABM_NET_RAT_ENUM_UINT32              g_enNasRabmSysMode;


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

typedef VOS_VOID (*NAS_RABM_SYS_MODE_CHG_PROC_FUNC)(VOS_VOID);

typedef VOS_VOID (*NAS_RABM_SM_ACTIVATE_IND_PROC_FUNC)(VOS_VOID *pMsg);
typedef VOS_VOID (*NAS_RABM_SM_DEACTIVATE_IND_PROC_FUNC)(VOS_VOID *pMsg);
typedef VOS_VOID (*NAS_RABM_SM_MODIFY_IND_PROC_FUNC)(VOS_VOID *pMsg);

typedef VOS_VOID (*NAS_RABM_GMM_REESTABLISH_CNF_PROC_FUNC)(VOS_VOID *pMsg);
typedef VOS_VOID (*NAS_RABM_DATA_SUSPEND_IND_FUNC)(VOS_BOOL bRatChangeFlg);
typedef VOS_VOID (*NAS_RABM_DATA_RESUME_IND_FUNC)(VOS_UINT8 ucRebuildRabFlag);

typedef VOS_VOID (*NAS_RABM_SYS_MODE_CHG_IND_FUNC)(GMM_RABM_NET_RAT_ENUM_UINT32 enOldSysMode, GMM_RABM_NET_RAT_ENUM_UINT32 enNewSysMode);
typedef VOS_VOID (*NAS_RABM_TASK_ENTRY_FUNC)(struct MsgCB* pMsg);

/*****************************************************************************
 �ṹ��    : NAS_RABM_PROC_FUNC_TBL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RABM��Ϣ��������ṹ
*****************************************************************************/
typedef struct
{
    NAS_RABM_SM_ACTIVATE_IND_PROC_FUNC      pSmActivateIndProcFunc;
    NAS_RABM_SM_DEACTIVATE_IND_PROC_FUNC    pSmDeactivateIndProcFunc;
    NAS_RABM_SM_MODIFY_IND_PROC_FUNC        pSmModifyIndProcFunc;

    NAS_RABM_GMM_REESTABLISH_CNF_PROC_FUNC  pGmmReestablishCnfProcFunc;

    NAS_RABM_DATA_SUSPEND_IND_FUNC          pDataSuspendIndProcFunc;
    NAS_RABM_DATA_RESUME_IND_FUNC           pDataResumeIndProcFunc;
    NAS_RABM_SYS_MODE_CHG_IND_FUNC          pSysModeChgIndProcFunc;

    NAS_RABM_TASK_ENTRY_FUNC                pTaskEntry;

}NAS_RABM_PROC_FUNC_TBL_STRU;

/*****************************************************************************
 �ṹ��    : NAS_RABM_SYS_CHG_TBL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  ģʽ�ı䴦������ṹ
*****************************************************************************/
typedef struct
{
    GMM_RABM_NET_RAT_ENUM_UINT32        enOldMode;
    GMM_RABM_NET_RAT_ENUM_UINT32        enNewMode;
    NAS_RABM_SYS_MODE_CHG_PROC_FUNC     pSysModeChgProcFunc;

} NAS_RABM_SYS_CHG_TBL_STRU;


typedef struct
{
    VOS_UINT32 ulApVoicePreferStatusMask;                   /* Ap��VP��Ч���� */
    VOS_UINT32 ulVoiceCallExsitFlag;                        /* ����ҵ����ڱ�־ */
    VOS_UINT32 ulCurCampMcc;                                /* ��ǰ�ֻ�ע���ʮ������BCD��ʽ��PLMN:MCC*/
    VOS_UINT32 ulCurCampMnc;                                /* ��ǰ�ֻ�ע���ʮ������BCD��ʽ��PLMN:MNC*/

    VOS_UINT32 ulCpVoicePreferActiveFlag;                   /* ���о�VP��Ч��־0:δ����;1:���� */
    VOS_UINT32 ulReceiveApVoicePreferStopFlag;              /* �յ�AP ����ֹͣVoicePrefer*/

    VOS_UINT32 ulNvTestMcc;                                 /* ��NV��ȡ ���ڲ��Ե�ʮ����PLMN:MCC*/
    VOS_UINT32 ulNvTestMnc;                                 /* ��NV��ȡ���ڲ��Ե�ʮ����PLMN:MNC*/

    VOS_UINT8 ucVoicePreferReQryGmmCnt;                     /* VP��Ч�о��Ѿ����Բ�ѯGMM�Ĵ��� */
    VOS_UINT8 ucVoicePreferNvimEnableFlag;                  /* NV ʹ��VP*/
    VOS_UINT8 ucReserve[2];

}NAS_RABM_VOICEPREFER_CTX_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : NAS_RABM_RegProcFuncTbl
 ��������  : ע��ָ��ϵͳģʽ�µ�RABM���������
 �������  : enSysMode      - ϵͳģʽ
             pstProcFucTbl  - ���������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_RegProcFuncTbl(
    GMM_RABM_NET_RAT_ENUM_UINT32        enSysMode,
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstProcFucTbl
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_CtxInit
 ��������  : RABM��ʼ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_CtxInit(VOS_VOID);


/*****************************************************************************
 �� �� ��  : NAS_RABM_MsgProc
 ��������  : ����RABM��Ϣ, ������Ϣ���͵�����Ӧ�Ĵ�����
 �������  : struct MsgCB                       *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_MsgProc(
    struct MsgCB                       *pMsg
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_RcvSmMsg
 ��������  : ����SM��Ϣ, ������Ϣ���͵��ö�Ӧ������
 �������  : struct MsgCB                       *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSmMsg(
    struct MsgCB                       *pMsg
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_ProcessGmmMsg
 ��������  : ����GMM��Ϣ, ������Ϣ���͵��ö�Ӧ������
 �������  : struct MsgCB                       *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvGmmMsg(
    struct MsgCB                       *pMsg
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_RcvSmActivateInd
 ��������  : ����ID_SM_RABM_ACTIVATE_INDԭ��
 �������  : pstSmActivateInd - ID_SM_RABM_ACTIVATE_IND��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSmActivateInd(
    RABMSM_ACTIVATE_IND_STRU           *pstSmActivateInd
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_RcvSmDeactivateInd
 ��������  : ����RABMSM_DEACTIVATE_INDԭ��
 �������  : pstSmDeactivateInd - RABMSM_DEACTIVATE_IND��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSmDeactivateInd(
    RABMSM_DEACTIVATE_IND_STRU         *pstSmDeactivateInd
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_RcvSmModifyInd
 ��������  : ����RABMSM_MODIFY_INDԭ��
 �������  : pstSmModifyInd - RABMSM_MODIFY_IND��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSmModifyInd(
    RABMSM_MODIFY_IND_STRU             *pstSmModifyInd
);

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_RABM_RcvSmBearerActivateInd
 ��������  : ����ID_SM_RABM_BEARER_MODIFY_INDԭ��
 �������  : pstSmBearerActivateInd - ID_SM_RABM_BEARER_ACTIVATE_IND��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSmBearerActivateInd(
    SM_RABM_BEARER_ACTIVATE_IND_STRU   *pstSmBearerActivateInd
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_RcvSmBearerModifyInd
 ��������  : ����ID_SM_RABM_BEARER_DEACTIVATE_INDԭ��
 �������  : pstSmBearerModifyInd - ID_SM_RABM_BEARER_MODIFY_IND��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSmBearerModifyInd(
    SM_RABM_BEARER_MODIFY_IND_STRU     *pstSmBearerModifyInd
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_RcvSmBearerDeactivateInd
 ��������  : ����RABMSM_PDP_DEACTIVATE_INDԭ��
 �������  : pstSmBearerDeactivateInd - ID_SM_RABM_BEARER_DEACTIVATE_IND��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSmBearerDeactivateInd(
    SM_RABM_BEARER_DEACTIVATE_IND_STRU *pstSmBearerDeactivateInd
);

#endif

/*****************************************************************************
 �� �� ��  : NAS_RABM_RcvGmmReestablishCnf
 ��������  : ����ID_GMM_RABM_REESTABLISH_CNFԭ��
 �������  : pstGmmReestablishCnf   - ID_GMM_RABM_REESTABLISH_CNF��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvGmmReestablishCnf(
    GMMRABM_REESTABLISH_CNF_STRU       *pstGmmReestablishCnf
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_ProcSysSrvChangeInd
 ��������  : ����ϵͳ״̬�ı�ָʾ��Ϣ, ����ϵͳģʽ�ͷ���״̬
 �������  : pstGmmSysSrvChgInd - ID_GMM_RABM_SYS_SRV_CHG_IND��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvGmmSysSrvChgInd(
    GMM_RABM_SYS_SRV_CHG_IND_STRU      *pstGmmSysSrvChgInd
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_RcvDataSuspendInd
 ��������  : �������ָʾ
 �������  : bRatChangeFlg - ��ϵͳ�л���־
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvDataSuspendInd(
    VOS_BOOL                            bRatChangeFlg
);

/*****************************************************************************
 �� �� ��  : NAS_RABM_RcvDataResumeInd
 ��������  : ����ָ�ָʾ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvDataResumeInd(
    VOS_UINT8                           ucRebuildRabFlag
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_RcvSysModeChgInd
 ��������  : ����ϵͳģʽ�ı�
 �������  : enNewSysMode - �µ�ϵͳģʽ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvSysModeChgInd(
    GMM_RABM_NET_RAT_ENUM_UINT32        enNewSysMode
);


/*****************************************************************************
 �� �� ��  : NAS_RABM_ProcessCommMsg
 ��������  :
 �������  : struct MsgCB                       *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID NAS_RABM_RcvCommMsg(
    struct MsgCB                       *pMsg
);

extern VOS_VOID NAS_RABM_RcvAtMsg(
    struct MsgCB                       *pMsg
);

VOS_VOID NAS_RABM_RcvCdsMsg(
    struct MsgCB                       *pMsg
);

VOS_VOID NAS_RABM_RcvCdsServiceInd(
    CDS_RABM_SERVICE_IND_STRU          *pstCdsServiceInd
);



VOS_UINT32 NAS_RABM_IsDataServiceRequestPending(VOS_VOID);
VOS_UINT32 NAS_RABM_IsRabReestablishPending(VOS_VOID);
VOS_VOID NAS_RABM_MNTN_TracePktLostEvt(
    NAS_RABM_PKT_FLOW_DIR_ENUM_UINT8    enPtkFlowDir,
    VOS_UINT8                           ucPoint
);

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
VOS_UINT32 NAS_RABM_VoicePreferGetVpStatus(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferSetVpStatus(VOS_UINT32 ulVpStatus);
VOS_UINT8 NAS_RABM_VoicePreferGetNvEnableFlag(VOS_VOID);
VOS_UINT8 NAS_RABM_VoicePreferGetReQryGmmCnt(VOS_VOID);
VOS_VOID  NAS_RABM_VoicePreferClrReQryGmmCnt(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferIncReQryGmmCnt(VOS_VOID);
VOS_UINT32 NAS_RABM_VoicePreferGetVoiceCallExsitFlag(VOS_VOID);
VOS_UINT32 NAS_RABM_VoicePreferGetStopVpFlag(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferSetStopVpFlag(VOS_UINT32 ulStopVpFlag);
VOS_UINT32 NAS_RABM_VoicePreferGetApStatusMask(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferSetApStatusMask(VOS_UINT32 ulApStatusMask);
VOS_VOID NAS_RABM_InitVoicePreferCtx(VOS_VOID);
VOS_VOID NAS_RABM_ReadVoicePreferNvim(VOS_VOID);
VOS_VOID NAS_RABM_RcvSetVoicePreferParaReq(AT_RABM_SET_VOICEPREFER_PARA_REQ_STRU *pstVoicePreferPara);
VOS_VOID NAS_RABM_RcvGetVoicePreferParaReq(
    AT_RABM_QRY_VOICEPREFER_PARA_REQ_STRU *pstVoicePreferPara);
VOS_VOID NAS_RABM_RcvVoicePreferCsExistInd(VOS_VOID *pstMsg);
VOS_UINT32 NAS_RABM_VoicePreferIsPdpActive(VOS_VOID);
VOS_UINT32 NAS_RABM_VoicePreferApStatusMatch(VOS_VOID);
VOS_UINT32 NAS_RABM_VoicePreferPlmnMatch(VOS_VOID);
VOS_UINT32 NAS_RABM_IsVpActivateMatchInStepOne(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferActivateJudgeStepOne(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferActivateJudgeStepTwo(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferDelayExpired(VOS_VOID);
VOS_VOID NAS_RABM_VoicePreferReQryGmmDelayExpired(VOS_VOID);
VOS_VOID NAS_RABM_RcvGmmVoicePreferMmlProcStatusQryCnf(
    struct MsgCB                       *pstMsg
);

#endif

#if (FEATURE_ON == FEATURE_BASTET)
VOS_VOID NAS_RABM_RcvBastetMsg(
    struct MsgCB                       *pstMsg
);
#endif
#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

