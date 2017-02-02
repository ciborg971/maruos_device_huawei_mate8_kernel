/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXsmsMsgProc.h
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��10��31��
  ��������   : TafXsmsMsgProc.cͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

#ifndef _TAF_XSMS_MSG_PROC_H_
#define _TAF_XSMS_MSG_PROC_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "NasNvInterface.h"
#include "cas_1x_control_main_nas_pif.h"
#include "xcc_sms_pif.h"
#include "TafXsmsCtx.h"
#include "TafXsmsInterMsg.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_XSMS_CAS_DATA_IND_MAX_LEN  (255)
#define TAF_XSMS_DBM_SMS_TYPE          (0x03)

#define TAF_XSMS_RESEND_TIMES_MAX          (7)   /* ���ŷ��͹��������Դ��� */
#define TAF_XSMS_RECONNECT_INTERVAL_MAX    (5)   /* ���ŷ��͹��������½������ӵļ������Ϊ��λ */
#define TAF_XSMS_RESEND_INTERVAL_MAX       (1)   /* ���ŷ��͹��������¸�����㷢���ݵļ������Ϊ��λ */

/* ���� CS0005E_Details ��Ա */
#define TAF_XSMS_SetCS0005EDetailPara(pstCS0005Detail,usMsgTag,usPRevInUse,usAuthMode)\
    {\
        PS_MEM_SET((pstCS0005Detail),0,sizeof(CS0005E_Details));\
        (pstCS0005Detail)->n_MSG_TAG          = (usMsgTag);\
        (pstCS0005Detail)->n_P_REV_IN_USEs    = (usPRevInUse);\
        (pstCS0005Detail)->n_AUTH_MODE        = (usAuthMode);\
    }

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : TAF_XSMS_3RD_PARTY_ERR_TYPE_ENUM
 ö��˵��  : ��������뺯����������
*****************************************************************************/
enum TAF_XSMS_3RD_PARTY_ERR_TYPE_ENUM
{
    TAF_XSMS_3RD_PARTY_ERR_DECODE_c_f_csch_mini6                = 0x00,
    TAF_XSMS_3RD_PARTY_ERR_DECODE_SETPRESENT_c_r_csch_mini6_DBM = 0x01,
    TAF_XSMS_3RD_PARTY_ERR_DECODE_ENCODE_c_r_csch_mini6         = 0x02,
    TAF_XSMS_3RD_PARTY_ERR_DECODE_DECODE_c_f_dsch               = 0x03,
    TAF_XSMS_3RD_PARTY_ERR_DECODE_SETPRESENT_c_r_dsch_DBM       = 0x04,
    TAF_XSMS_3RD_PARTY_ERR_DECODE_ENCODE_c_r_dsch               = 0x05,
    TAF_XSMS_3RD_PARTY_ERR_DECODE_ENCODE_BUTT
};

typedef VOS_UINT32 TAF_XSMS_3RD_PARTY_ERR_TYPE_ENUM_UINT32;



/*****************************************************************************
 ö����    : TAF_XSMS_CAS_DATA_REQ_TYPE_ENUM
 ö��˵��  : ��������DATA_REQ����
*****************************************************************************/
enum TAF_XSMS_CAS_DATA_REQ_TYPE_ENUM
{
    TAF_XSMS_CAS_DATA_REQ_TYPE_MO   = 0x5A,
    TAF_XSMS_CAS_DATA_REQ_TYPE_MT   = 0xA5,
    TAF_XSMS_CAS_DATA_REQ_TYPE_BUTT = 0xFF
};

typedef VOS_UINT8 TAF_XSMS_CAS_DATA_REQ_TYPE_ENUM_UINT8;


/*****************************************************************************
 ö����    : TAF_XSMS_SEND_XCC_CALL_ID_ENUM
 ö��˵��  : MO/MT���ŵ�call id
*****************************************************************************/
enum TAF_XSMS_SEND_XCC_CALL_ID_ENUM
{
    TAF_XSMS_SEND_XCC_CALL_ID_MO     = 0x55,
    TAF_XSMS_SEND_XCC_CALL_ID_MT     = 0xAA,
    TAF_XSMS_SEND_XCC_CALL_ID_BUTT   = 0xFF
};

typedef VOS_UINT8 TAF_XSMS_SEND_XCC_CALL_ID_ENUM_UINT8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : TAF_XSMS_CAS_DATA_IND_MSG_STRU
 �ṹ˵��  : ������ϱ���DSCH��CSCH����ת������XSMS�ڲ�ʹ�õ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CAS_1X_CONTROL_MAIN_NAS_PIF_MSG_TYPE_ENUM_UINT16        enMsgId;       /* _H2ASN_Skip */
    VOS_UINT16                                              usOpId;
    VOS_UINT8                                               ucLen;
    VOS_UINT8                                               aucMsg[TAF_XSMS_CAS_DATA_IND_MAX_LEN];
}TAF_XSMS_CAS_DATA_IND_MSG_STRU;





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
/* Deleted by wx270776 for OM�ں�, 2015-7-16, begin */
/* Deleted by wx270776 for OM�ں�, 2015-7-16, end */

extern VOS_VOID   TAF_XSMS_MsgHook(TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32 enMsgName, VOS_UINT8 *pucMsg, VOS_UINT32 ulMsgLen);

extern VOS_VOID   TAF_XSMS_AtDeleteMsgProc(TAF_XSMS_DELETE_MSG_REQ_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_AtWriteMsgProc(TAF_XSMS_WRITE_MSG_REQ_STRU *pstMsg);

extern VOS_VOID   TAF_XSMS_AtMsgProc(MsgBlock* pstMsg);

extern VOS_VOID   TAF_XSMS_TimeOutMsgProc(REL_TIMER_MSG *pstRelTimerMsg);

extern VOS_VOID   TAF_XSMS_XccEndCallCnfChooseStateMachine(MsgBlock *pstMsg);

extern VOS_VOID   TAF_XSMS_XccSoIndChooseStateMachine(MsgBlock *pstMsg);

extern VOS_VOID   TAF_XSMS_XccMsgProc(MsgBlock *pstMsg);

extern VOS_VOID   TAF_XSMS_1xCasMsgProc(MsgBlock* pstMsg);

extern VOS_UINT32 TAF_XSMS_TransCSCHDataToDbm(
    CAS_CNAS_1X_CSCH_DATA_IND_STRU     *pstCschData,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm
);

extern VOS_UINT32 TAF_XSMS_TransDbmToCSCHData
(
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm,
    CNAS_CAS_1X_CSCH_DATA_REQ_STRU     *pstCschData
);

extern VOS_UINT32 TAF_XSMS_TransDSCHDataToDbm
(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pstDschData,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm
);

extern VOS_UINT32 TAF_XSMS_TransDbmToDSCHData
(
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm,
    CNAS_CAS_1X_DSCH_DATA_REQ_STRU     *pstDschData
);

extern VOS_VOID   TAF_XSMS_CasDschCnfProc(MsgBlock *pstMsg);

extern VOS_VOID   TAF_XSMS_CasDschDataIndProc(MsgBlock *pstMsg);

extern VOS_VOID   TAF_XSMS_CasCschCnfProc(MsgBlock *pstMsg);

extern VOS_VOID   TAF_XSMS_CasCschDataIndProc(MsgBlock *pstMsg);

extern VOS_VOID   TAF_XSMS_CasAbortProc(MsgBlock *pstMsg);

extern VOS_UINT32 TAF_XSMS_CheckIsSmsDbm(TAF_XSMS_DATA_BURST_MSG_STRU *pstDbm);

extern VOS_VOID   TAF_XSMS_PidMsgProc(MsgBlock* pstMsg);

extern VOS_UINT32 TAF_XSMS_PidInit(enum VOS_INIT_PHASE_DEFINE  ip);
extern VOS_UINT32 TAF_XSMS_EncodeCschOrderMsg
(
    CNAS_CAS_1X_CSCH_DATA_REQ_STRU     *pstCschDataReq
);

extern VOS_UINT32 TAF_XSMS_TransDbmToAucData
(
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm,
    VOS_UINT8                          *paucData
);

extern VOS_VOID TAF_XSMS_TransAucDataToDbm
(
    VOS_UINT8                          *paucData ,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm
);

extern VOS_VOID TAF_XSMS_DealXccVoiceMailInd(MsgBlock* pstMsg);
extern VOS_VOID TAF_XSMS_AtApMemFullMsgProc(TAF_XSMS_APP_MSG_SET_AP_MEM_FULL_REQ_STRU *pstApMemFullMsg);
extern VOS_VOID TAF_XSMS_StkProc(MsgBlock *pstMsg);
extern VOS_VOID TAF_XSMS_HookSmsContect(
    TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32  enMsgName,
    VOS_UINT32                          ulReqSeq,
    TAF_XSMS_MESSAGE_STRU              *pstXsmsMsg
);
extern VOS_VOID TAF_XSMS_HookSmsTlAck(
    TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32  enMsgName,
    TAF_XSMS_CAUSE_CODE_STRU           *pstCauseCode
);



#endif


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

