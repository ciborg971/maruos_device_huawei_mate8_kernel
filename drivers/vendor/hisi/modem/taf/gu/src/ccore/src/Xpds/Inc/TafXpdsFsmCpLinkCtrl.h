/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXpdsFsmUpLinkCtrl.h
  �� �� ��   : ����
  ��    ��   : OM_AcpuIccInfoInit
  ��������   : 2015��8��27��
  ����޸�   :
  ��������   : TafXpdsFsmUpLinkCtrl.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��8��27��
    ��    ��   : OM_AcpuIccInfoInit
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAFXPDSFSMUPLINKCTRL_H__
#define __TAFXPDSFSMUPLINKCTRL_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "TafXpdsFsmCpLinkCtrlTbl.h"

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

extern VOS_UINT32 TAF_XPDS_RcvTimerExpireForExitFsm_CpLinkCtrl(
       VOS_UINT32                          ulEventType,
       struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXccAnsCallCnf_CpLinkCtrl_WaitAnsCallCnf(
       VOS_UINT32                          ulEventType,
       struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXccIncomingCallInd_CpLinkCtrl_Init(
       VOS_UINT32                          ulEventType,
       struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXccOrigCallCnf_CpLinkCtrl_Init(
       VOS_UINT32                          ulEventType,
       struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXccCallConnInd_CpLinkCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXccServConnInd_CpLinkCtrl_WaitServConnIndMO(
       VOS_UINT32                          ulEventType,
       struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvXccServConnInd_CpLinkCtrl_WaitServConnIndMT(
           VOS_UINT32                          ulEventType,
           struct MsgCB                       *pstMsg
       );
extern VOS_UINT32  TAF_XPDS_RcvXpdsCtrlPlaneReq_CpLinkCtrl_Init(
       VOS_UINT32                          ulEventType,
       struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_XPDS_RcvDataIndMsg_CpLinkCtrl(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

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

#endif /* end of TafXpdsFsmUpLinkCtrl.h */

