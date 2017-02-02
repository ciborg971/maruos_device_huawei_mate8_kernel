

#ifndef __TAF_X_CALL_SND_XCC_H__
#define __TAF_X_CALL_SND_XCC_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "TafXCallCtx.h"
#include "xcc_xcall_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_XCALL_CALL_NUM_TYPE_VALID_BIT         (0x70)
#define TAF_XCALL_CALL_PLAN_TYPE_VALID_BIT        (0x0F)


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
VOS_VOID TAF_XCALL_SndXccOrigCallReq(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_SndXccAnswerCallReq(
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_SndXccHangUpCallReq(
    VOS_UINT8                           ucCallId,
    TAF_XCC_END_REASON_ENUM_UINT8       enEndReason
);

VOS_VOID TAF_XCALL_SndXccIncomingCallRsp(
    XCC_XCALL_RESULT_ENUM_UINT32        enRslt,
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConnectId
);

VOS_VOID TAF_XCALL_BuildOrigCallPara(
    XCALL_XCC_ORIG_CALL_REQ_STRU       *pstOrigPara,
    VOS_UINT8                           ucCallId
);

VOS_VOID TAF_XCALL_BuildCallingNum(
    XCC_XCALL_CALLING_PARTY_NUM_INFO_STRU  *pstCallingNum,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity,
    XCC_XCALL_DIGIT_MODE_ENUM_UINT8         enDigitMode
);

VOS_VOID TAF_XCALL_BuildCallingSubAddr(
    XCC_XCALL_SUB_ADDRESS_INFO_STRU        *pstSubAddr,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity
);

VOS_VOID TAF_XCALL_BuildCalledNum(
    XCC_XCALL_CALLED_PARTY_NUM_INFO_STRU   *pstCalledNum,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity,
    XCC_XCALL_DIGIT_MODE_ENUM_UINT8         enDigitMode
);

VOS_VOID TAF_XCALL_BuildCalledSubAddr(
    XCC_XCALL_SUB_ADDRESS_INFO_STRU        *pstSubAddr,
    TAF_XCALL_CALL_ENTITY_STRU             *pstCallEntity
);

/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-12, begin */
extern VOS_UINT32 TAF_XCALL_SndXccFlashReq(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucDigitNum,
    VOS_UINT8                          *pucDigits
);

extern TAF_CALL_SEND_BURST_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SndXccBurstDTMFReq(
    TAF_CALL_BURST_DTMF_PARA_STRU      *pstBurstDtmfInfo
);
/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-12, end */

/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, begin */

extern TAF_CALL_SEND_CONT_DTMF_CNF_RESULT_ENUM_U8 TAF_XCALL_SndXccContDTMFReq(
    TAF_CALL_CONT_DTMF_PARA_STRU      *pstContDtmfInfo
);
/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, end */

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

#endif /* end of TafXCallSndXcc.h */

