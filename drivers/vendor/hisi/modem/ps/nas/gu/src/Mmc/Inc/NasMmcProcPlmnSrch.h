
#ifndef _NAS_MMC_PROC_PLMNSRCH_H
#define _NAS_MMC_PROC_PLMNSRCH_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "Nasrrcinterface.h"

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
NAS_MMC_NET_RAT_TYPE_ENUM_U8 NAS_MMC_GetStartPlmnSrchRat( VOS_VOID );
VOS_VOID NAS_MMC_UpdateNvRplmnWithSimRplmn(VOS_VOID);
VOS_UINT32  NAS_MMC_IsSimRplmnInNvRplmn(
    MMC_PLMN_ID_STRU                   *pSimRplmnId
);
VOS_VOID NAS_MMC_InitFsmCtx_AutoPlmnSrch_RcvTafPlmnSrchReq(VOS_VOID );

VOS_VOID NAS_MMC_UpdatePlmnListInfoAsNoSuitableCellInSrchProc(VOS_VOID);

VOS_UINT32  NAS_MMC_IsAllListPlmnEquSpecPlmn(
    MMC_PLMN_ID_STRU                   *pstPlmnId,
    VOS_UINT32                          ulPlmnNum,
    NAS_MMC_PLMN_INFO_STRU             *pstPlmnListAddr
);
VOS_UINT32 NAS_MMC_UpdateLastSrchedPlmnStatus(
    NAS_MMC_NET_STATUS_ENUM_U8          enNewStatus,
    NAS_MMC_NET_RAT_TYPE_ENUM_U8        enSpecRat,
    VOS_UINT32                          ulPlmnNum,
    NAS_MMC_PLMN_INFO_STRU             *pstPlmnListAddr
);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_MMC_ConvertLmmPlmnIDListToGuRRCPlmnIDList(
    MMC_LMM_PLMN_ID_LIST_STRU          *pstLMMPlmnList,
    RRC_PLMN_ID_LIST_STRU              *pstGURrcPlmnList
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

