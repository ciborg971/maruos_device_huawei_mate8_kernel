

#ifndef __TAFMTAMODEMCONTROL_H__
#define __TAFMTAMODEMCONTROL_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#if (FEATURE_ON == FEATURE_DSDS)
#include "PsRrmInterface.h"
#endif

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
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
VOS_VOID TAF_MTA_RcvMtcPsTransferInd(
    VOS_VOID                           *pMsg
);
#endif


VOS_VOID TAF_MTA_RcvAtQryMipiClkReq(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_RcvTiMipiClkExpired(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_RcvMtcMipiClkInfoInd(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_SndMipiClkInfoToAt(VOS_UINT16 usMipiClk);

#if (FEATURE_ON == FEATURE_DSDS)
VOS_UINT32 TAF_MTA_SndRrmProtectPsInd(VOS_VOID);

VOS_UINT32 TAF_MTA_SndRrmDeProtectPsInd(VOS_VOID);

VOS_UINT32 TAF_MTA_SndRrmPsProtectType(
    PS_BOOL_ENUM_UINT8                  usRrmPsProtectType
);

VOS_UINT32 TAF_MTA_SndAsPsProtectIndMsg(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT8                           ucProtectFlg
);

VOS_VOID TAF_MTA_SndAtSetPsProtectCnf(
    AT_MTA_MSG_STRU                    *pstAtMtaReqMsg,
    AT_MTA_MSG_TYPE_ENUM_UINT32         enErr
);

VOS_VOID TAF_MTA_RcvAtPsProtectSetReq(
    VOS_VOID                           *pMsg
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

#endif /* end of TafMtaModemControl.h */
