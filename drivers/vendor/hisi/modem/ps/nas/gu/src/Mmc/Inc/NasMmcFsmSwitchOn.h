

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#ifndef __NASMMCFSMSWITCHON_H__
#define __NASMMCFSMSWITCHON_H__

#include  "vos.h"
#include "NasMmlCtx.h"
#include "MsccMmcInterface.h"





#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvStartReq_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvUsimGetFileRsp_SwitchOn_WaitSimFilesCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn_WaitSimFilesCnf(
    USIMM_DEF_FILEID_ENUM_UINT32        enEfId
);

VOS_UINT32  NAS_MMC_RcvTiReadSimFilesExpired_SwitchOn_WaitSimFilesCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvMmStartCnf_SwitchOn_WaitMmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGmmStartCnf_SwitchOn_WaitMmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiMmStartCnfExpired_SwitchOn_WaitMmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvGasStartCnf_SwitchOn_WaitGasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvWasStartCnf_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32  NAS_MMC_RcvTiWaitGasStartCnfExpired_SwitchOn_WaitGasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if   (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_RcvLmmStartCnf_SwitchOn_WaitLStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32  NAS_MMC_RcvTiLmmStartCnfExpired_SwitchOn_WaitLStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#endif

VOS_UINT32  NAS_MMC_GetLastRplmn_SwitchOn(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstLasRplmn
);


VOS_UINT32  NAS_MMC_IsImsiChange_SwitchOn(VOS_VOID);

VOS_VOID NAS_MMC_InitUserSpecPlmnId_SwitchOn(VOS_VOID);

VOS_VOID    NAS_MMC_ReadNvimInfo_SwitchOn(VOS_VOID);

VOS_VOID    NAS_MMC_UpdateNvRplmnWithSimRplmn_SwitchOn(VOS_VOID);

VOS_UINT32  NAS_MMC_IsSimRplmnInNvRplmn_SwitchOn(
    NAS_MML_PLMN_ID_STRU               *pstSimRplmnId
);

VOS_VOID    NAS_MMC_UpdateEplmn_SwitchOn(VOS_VOID);

VOS_VOID NAS_MMC_UpdateLastRplmnRat_LastRplmnRatInvalid_SwitchOn(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstLasRplmn,
    VOS_UINT8                           ucLastRplmnExistFlag
);



VOS_VOID NAS_MMC_RcvStartCnf_SwitchOn_ProcAsRatCapabilityStatus (VOS_VOID);

VOS_VOID NAS_MMC_RcvStartCnf_SwitchOn_InitRatForbidListCfg (VOS_VOID);

VOS_VOID NAS_MMC_SavePlmnRatPrio_SwitchOn(
    MSCC_MMC_PLMN_RAT_PRIO_STRU          *pRcvPlmnRatPrio
);

VOS_VOID NAS_MMC_Save3Gpp2RatPrio_SwitchOn(
    MSCC_MMC_3GPP2_RAT_STRU             *pst3Gpp2Rat
);

VOS_VOID NAS_MMC_SaveAllowRegDomain_SwitchOn(
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8                   enRegDomain
);

VOS_VOID NAS_MMC_SndRatModeSwitchOnReq_SwitchOn(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat
);

VOS_VOID NAS_MMC_UpdateEhplmnInfo_SwitchOn(
    VOS_UINT8                           *pucImsi
);

VOS_VOID NAS_MMC_InitLastRplmnRat_SwitchOn(VOS_VOID);




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
