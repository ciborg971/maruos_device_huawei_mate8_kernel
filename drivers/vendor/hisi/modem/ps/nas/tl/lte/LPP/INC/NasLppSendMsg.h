/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLppSendMsg.h
  Description     : NasLppSendMsg.c header file
  History         :
     1.XiaoJun       2015-7-30     Draft Enact
     2.
******************************************************************************/

#ifndef __NASLPPSENDMSG_H__
#define __NASLPPSENDMSG_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "LPPLRrcInterface.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID NAS_LPP_SndLppLrrcEcidMeasReq
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8    ucLcsMeasCmd
);
extern VOS_VOID NAS_LPP_SndOtdoaMeasReq
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    LPP_LRRC_LCS_MEAS_CMD_ENUM_UINT8    ucLcsMeasCmd
);
extern VOS_VOID  NAS_LPP_SndIntraLppMsg
(
    VOS_UINT32                                  ulOpId,
    NAS_LPP_MSG_IDENTITY_STRU           *pstLppMsgIdentity,
    NAS_LPP_ERROR_CODE_ENUM_UINT32       enErrorCode
);
extern VOS_VOID  NAS_LPP_SndUpLppErrorMsg
(
    VOS_UINT32                          ulSessionId,
    NAS_LPP_TRANS_ID_STRU              *pstTransID,
    LPP_COMMON_IES_ERROR_ENUM_UINT8     enErrorCause,
    VOS_BOOL                            enNeedAck,
    VOS_BOOL                            bEndTransaction

);
extern VOS_VOID  NAS_LPP_SndUplinkReqAssistDataMsg
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT8                           ucTransIndx,
    VOS_BOOL                            enOtdoaAssist,
    VOS_BOOL                            enGnssAssist
);
extern VOS_VOID  NAS_LPP_SndUpLppAbortMsg
(
    VOS_UINT8                           ucSessionIndx,
    VOS_UINT8                           ucSessionTransIndx,
    VOS_UINT8                           ucTransIndx,
    LPP_COMMON_IES_ABORT_ENUM_UINT8     enAbortCause,
    VOS_BOOL                            enNeedAck,
    VOS_BOOL                            bEndTransaction
);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
         }
    #endif
#endif

#endif /* end of NasLppSendMsg.h */
