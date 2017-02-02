/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMtaPhy.h
  �� �� ��   : ����
  ��    ��   :
  ��������   : 2013��03��11��
  ����޸�   :
  ��������   : TafMtaPhy.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��03��11��
    ��    ��   :
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAFMTAPHY_H__
#define __TAFMTAPHY_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafMtaCtx.h"
#include "MtaPhyInterface.h"

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
VOS_VOID TAF_MTA_RcvAtBodySarSetReq(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_RcvPhyBodySarSetCnf(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_RcvTiWaitPhySetBodySarExpired(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_SndPhyEmergencyCallStatus(
    MTA_PHY_EMERGENCY_CALL_STATUS_ENUM_UINT16               enState
);

VOS_VOID TAF_MTA_RcvTiWaitGrrSetNCellMonitorExpired(VOS_VOID *pMsg);
VOS_VOID TAF_MTA_RcvTiWaitGrrQryNCellMonitorExpired(VOS_VOID *pMsg);

VOS_VOID TAF_MTA_RcvAtSetHandleDectReq(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvAtQryHandleDectReq(
    VOS_VOID                           *pMsg
);

VOS_UINT32 TAF_MTA_SndPhySetHandleDectReqMsg(
    VOS_UINT16                          usHandleType
);

VOS_UINT32 TAF_MTA_SndPhyQryHandleDectReqMsg(VOS_VOID);

VOS_VOID TAF_MTA_RcvPhyHandleDectSetCnf(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvPhyHandleDectQryCnf(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvTiWaitPhySetHandleDectExpired(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvTiWaitPhyQryHandleDectExpired(
    VOS_VOID                           *pMsg
);

VOS_UINT32 TAF_MTA_CheckRatModeTypeValid(
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode
);

VOS_VOID TAF_MTA_RcvAtSetDpdtTestFlagReq(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvAtSetDpdtValueReq(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvAtQryDpdtValueReq(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvGuPhyQryDpdtValueCnf(
    VOS_VOID                           *pMsg
);

VOS_VOID TAF_MTA_RcvTiReqDpdtValueQryExpired(
    VOS_VOID                           *pMsg
);


/* Added by w00316404 for eMBMS project, 2015-5-22, begin */
#if(FEATURE_ON == FEATURE_LTE)
#if 0
VOS_VOID TAF_MTA_SndLphySetIsmCoexReqMsg(
    AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU           *pstCoexPara
);
VOS_VOID TAF_MTA_RcvLphyIsmCoexSetCnf(
    VOS_VOID                           *pLphyCnfMsg
);
#endif
VOS_VOID TAF_MTA_RcvAtIsmCoexSetReq(
    VOS_VOID                           *pMsg
);
VOS_VOID TAF_MTA_RcvTiWaitSetIsmCoexList(
    VOS_VOID                           *pMsg
);
#endif
/* Added by w00316404 for eMBMS project, 2015-5-22, end */


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

#endif /* end of TafMtaSecure.h */


