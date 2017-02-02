

#ifndef __TAF_APS_PROC_EPDSZID_H__
#define __TAF_APS_PROC_EPDSZID_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafApsCtx.h"
#include "xcc_aps_pif.h"


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



#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
TAF_APS_CDATA_EPDSZID_CTX_STRU* TAF_APS_GetEpdszidCtx(VOS_VOID);

VOS_UINT8 TAF_APS_GetCurrPacketZoneListLen(VOS_VOID);

VOS_VOID TAF_APS_SetCurrPacketZoneListLen(
    VOS_UINT8                           ucZoneListLen
);

VOS_VOID TAF_APS_ReduceEpdszidInZoneList(
    VOS_UINT8                           ucMaxZoneListLen
);

VOS_UINT8 TAF_APS_GetMaxPacketZoneListLen(VOS_VOID);

VOS_VOID TAF_APS_SetMaxPacketZoneListLen(
    VOS_UINT8                           ucMaxZoneListLen
);

VOS_UINT8 TAF_APS_GetHysEnableFlg(VOS_VOID);

VOS_VOID TAF_APS_SetHysEnableFlg(
    VOS_UINT8                           ucHysEnableFlg
);

VOS_UINT8 TAF_APS_GetHysActivationInd(VOS_VOID);

VOS_VOID TAF_APS_SetHysActivationInd(
    VOS_UINT8                           ucHysActivationInd
);

TAF_APS_EPDSZID_SUPPORT_TYPE_ENUM_UINT8 TAF_APS_GetEpdszidType(VOS_VOID);

VOS_VOID TAF_APS_SetEpdszidType(
    TAF_APS_EPDSZID_SUPPORT_TYPE_ENUM_UINT8       enEpdszidType
);

VOS_UINT8 TAF_APS_GetEpdszidHatTimerLen(VOS_VOID);

VOS_VOID TAF_APS_SetEpdszidHatTimerLen(
    VOS_UINT8                           ucHatTimerLen
);

VOS_UINT8 TAF_APS_GetEpdszidHtTimerLen(VOS_VOID);

VOS_VOID TAF_APS_SetEpdszidHtTimerLen(
    VOS_UINT8                           ucHtTimerLen
);

TAF_APS_CDATA_EPDSZID_CHG_REORIG_SCENE_ENUM_UINT8 TAF_APS_GetEpdszidChgReOrigScene(VOS_VOID);

VOS_VOID TAF_APS_SetEpdszidChgReOrigScene(
    TAF_APS_CDATA_EPDSZID_CHG_REORIG_SCENE_ENUM_UINT8        enReOrigScene
);

TAF_APS_CDATA_EPDSZID_STRU* TAF_APS_GetCurrEpdszidInfo(VOS_VOID);

VOS_VOID TAF_APS_SetCurrEpdszidInfo(
    TAF_APS_CDATA_EPDSZID_STRU         *pstEpdszid
);

TAF_APS_CDATA_HRPD_EPDSZID_CTX_STRU* TAF_APS_GetHrpdEpdszidInfo(VOS_VOID);

VOS_VOID TAF_APS_SetHrpdEpdszidInfo(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid,
    VOS_UINT8                           ucPzid
);
TAF_APS_CDATA_EPDSZID_STRU* TAF_APS_GetOldestEntryInZoneList(VOS_VOID);

VOS_UINT32 TAF_APS_IsEpdszidExistInZoneList(
    TAF_APS_CDATA_EPDSZID_STRU         *pstEpdszid
);

VOS_UINT8 TAF_APS_GetEpdszidIndexInZoneList(
    TAF_APS_CDATA_EPDSZID_STRU         *pstEpdszid
);

VOS_VOID TAF_APS_AddEpdszidToZoneList
(
    TAF_APS_CDATA_EPDSZID_STRU         *pstEpdszid
);

VOS_VOID TAF_APS_DeleteOldestEntryInZoneList(VOS_VOID);

VOS_VOID TAF_APS_InitPacketZoneList(VOS_VOID);

VOS_VOID TAF_APS_InitCurrEpdszidInfo(VOS_VOID);

VOS_VOID TAF_APS_InitEpdszidCtx(VOS_VOID);

VOS_VOID TAF_APS_ReleaseEpdszidResource(VOS_VOID);

VOS_VOID TAF_APS_EpdszidSocmDisableReconn(VOS_VOID);

VOS_VOID TAF_APS_EpdszidSocmEnableReconn(
    VOS_UINT8                           ucMaxZoneListLen
);

VOS_VOID TAF_APS_EpdszidSocmClearPacketZoneList(
    VOS_UINT8                           ucMaxZoneListLen
);

VOS_VOID TAF_APS_EpdszidScomTransferPzid(
    XCC_APS_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsgInd
);

VOS_VOID TAF_APS_EpdszidProcHt(VOS_VOID);

VOS_VOID TAF_APS_EpdszidStopHat(VOS_VOID);

VOS_VOID TAF_APS_EpdszidStopHt(VOS_VOID);

VOS_VOID TAF_APS_ProcEpdszidEnterDormant(VOS_VOID);

VOS_VOID TAF_APS_ProcEpdszidHaiChangeInd(VOS_VOID);

VOS_VOID TAF_APS_ProcEpdszidAfterRcvXccOrigDataCallCnf(VOS_VOID);

VOS_VOID TAF_APS_ProcEpdszidHatExpired(VOS_VOID);

VOS_VOID TAF_APS_ProcEpdszidHtExpired(VOS_VOID);

VOS_VOID TAF_APS_ProcMmaEpdszidInfo(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid,
    VOS_UINT8                           ucPzid,
    VOS_UINT8                           ucPdpId
);

VOS_VOID TAF_APS_ProcXregEpdszidRegBeginInd(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid,
    VOS_UINT8                           ucPzid
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

#endif /* end of TafApsProcEpdszid.h */
