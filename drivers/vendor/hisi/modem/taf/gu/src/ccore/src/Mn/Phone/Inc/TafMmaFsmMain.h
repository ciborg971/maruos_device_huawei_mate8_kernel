

#ifndef _TAF_MMA_FSM_MAIN_H
#define _TAF_MMA_FSM_MAIN_H

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
/* Modified by h00313353 for Iteration 13, 2015-4-13, begin */
#include "TafLog.h"
/* Modified by h00313353 for Iteration 13, 2015-4-13, end */


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
VOS_UINT32 TAF_MMA_RcvAppPhoneModeSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvTafPhoneModeSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


VOS_UINT32 TAF_MMA_RcvSysCfgSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_MMA_RcvMmaPlmnListReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvUsimRefreshIndMsg_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvDetachReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMmaInterPowerInit_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMmaInterUsimStatusChangeInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMmaPhoneModeRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/* Added by h00313353 for Iteration 13, 2015-5-5, begin */
VOS_UINT32 TAF_MMA_RcvMmaSysCfgRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
/* Added by h00313353 for Iteration 13, 2015-5-5, end */

VOS_UINT32 TAF_MMA_RcvMmaSimlockStatusChangeInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);


extern VOS_UINT32 TAF_MMA_RcvPlmnSpecialSelReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
extern VOS_UINT32 TAF_MMA_RcvPlmnAutoReselReq_Main (
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if (FEATURE_IMS == FEATURE_ON)
VOS_UINT32 TAF_MMA_RcvTafImsSwitchSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMmaImsSwitchRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif


/* Modified by l00301449 for Iteration 13, 2015-04-09, begin */
VOS_UINT32 TAF_MMA_RcvAttachReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_MMA_RcvMmaInterSysCfgSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);



/* Modified by l00301449 for Iteration 13, 2015-04-09, end */



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

#endif /* end of Taf_MMA_FSM_MAIN.h */

