

#ifndef __NASEMMSECUAUTH_H__
#define __NASEMMSECUAUTH_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "NasEmmSecuSoftUsim.h"
#include "NasEmmSecuInterface.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 macro
*****************************************************************************/
#define NAS_EMM_SECU_SUCC                                    0
#define NAS_EMM_SECU_FAIL                                    1

#define NAS_EMM_SECU_MEM_CMP_EQUAL                           0

/*Separation Bit of AMF in AUTH REQ*/
#define NAS_EMM_AUTH_FOR_EUTRAN                              1

/* IEI */
#define NAS_EMM_AUTH_FAIl_PARAM_IEI                          0x30

#define NAS_EMM_AUTH_AMF_IN_AUTN_POS                         6

#define NAS_EMM_SECU_AUTH_AUTN_LEN                           16
#define NAS_EMM_SECU_MAX_AUTH_RES_LEN                        16
#define NAS_LMM_SECU_NAS_KEY_LEN                              16
#define NAS_EMM_SECU_CKEY_LEN                                16
#define NAS_EMM_SECU_IKEY_LEN                                16

#define NAS_EMM_AUTH_LEN_CN_MAX_FAIL_MSG                     19

#define NAS_EMM_FIRST_AUTH_FAIL                              1
#define NAS_EMM_MAX_AUTH_FAIL_TIMES                          3

#define NAS_EMM_SECU_MAX_ALG_PARAM_LEN                       150        /*��ȷ��һ��*/

/*algorithm param*/
#define NAS_EMM_SECU_ALG_PARAM_KASME_FC                      0x10
#define NAS_EMM_SECU_ALG_PARAM_NAS_KEY_FC                    0x15
#define NAS_EMM_SECU_ALG_PARAM_UMTS_CKIK_HO_FC               0x16
#define NAS_EMM_SECU_ALG_PARAM_NAS_TOKEN_FC                  0x17
#define NAS_EMM_SECU_ALG_PARAM_MAPPED_KASME_HO_FC            0x18
#define NAS_EMM_SECU_ALG_PARAM_MAPPED_KASME_IDLE_FC          0x19
#define NAS_EMM_SECU_ALG_PARAM_UMTS_CKIK_SRVCC_FC            0x1A
#define NAS_EMM_SECU_ALG_PARAM_UMTS_CKIK_IDLE_FC             0x1B



/* Kasme param */
#define NAS_EMM_SECU_ALG_PARAM_KASME_PLMNID_LEN              0x03

/*algorithm param*/
#define NAS_EMM_SECU_ALG_PARAM_KASME_PRE_LEN                 0x00
#define NAS_EMM_SECU_ALG_PARAM_IDENTITY_LEN                  0x01
#define NAS_EMM_SECU_ALG_PARAM_DISTINGUISHER_LEN             0x01
#define NAS_EMM_SECU_ALG_PARAM_CK_DISTINGUISHER              0x01
#define NAS_EMM_SECU_ALG_PARAM_IK_DISTINGUISHER              0x02

#define NAS_EMM_SECU_SN_LEN                                  1
#define NAS_EMM_SECU_SQN_LEN                                 6

#define NAS_EMM_SECU_AUTH_AUTS_LEN                           0x0E

#define NAS_EMM_HARD_USIM_AUTN_L_POS                         0
#define NAS_EMM_HARD_USIM_AUTN_V_POS                         1

#define NAS_EMM_USIM_CNF_RES_L_POS                           0
#define NAS_EMM_USIM_CNF_RES_V_POS                           1

#define NAS_EMM_USIM_CNF_AUTS_L_POS                          0
#define NAS_EMM_USIM_CNF_AUTS_V_POS                          1

#define NAS_EMM_SECU_MASK_OVERFLOW_COUNT          0x00FFFF00
#define NAS_EMM_SECU_MASK_HO_OVERFLOW_COUNT       0x00FFFFF0
#define NAS_EMM_SECU_MASK_NAS_COUNT_SQN           0x000000FF
#define NAS_EMM_SECU_COUNT_FLOW_OFFSET            0x100
#define NAS_EMM_SECU_HO_DL_OVERFLOW               0x00000010
/* Add by yanglei 00307272 for DL_NAS_COUNT_OPTIMIZE, 2015-08-27, Begin */
#define NAS_EMM_SECU_DL_COUNT_WINDOW            0x05
/* Add by yanglei 00307272 for DL_NAS_COUNT_OPTIMIZE, 2015-08-27, End */
/* OP SELECTED */
#define NAS_EMM_SECU_OP_SLCT                            1
#define NAS_EMM_SECU_OP_NO_SLCT                         0

#define NAS_EMM_SECU_NONCE_UE_LEN                       4
#define NAS_EMM_SECU_NONCE_MME_LEN                      4
#define NAS_EMM_SECU_NASCOUNT_LEN                       4

#define NAS_EMM_SECU_RANDOM_RANGE                       255

#define NAS_EMM_SECU_MIN_KSI                            0
#define NAS_EMM_SECU_MAX_KSI                            6

/* Set Vos Header */
#define NAS_EMM_SET_SECU_INTRA_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_MM;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }
/* Set Vos Header */
#define NAS_EMM_SET_SECU_OUTER_MSG_HEADER(pMsg,MsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_ERRC;\
            (pMsg)->ulLength            = (MsgLenthNoHeader);\
        }

#define NAS_EMM_SET_SECU_ESM_MSG_HEADER(pMsg,ulMsgLenthNoHeader)\
        {\
            (pMsg)->ulSenderCpuId       = VOS_LOCAL_CPUID;\
            (pMsg)->ulSenderPid         = PS_PID_MM;\
            (pMsg)->ulReceiverCpuId     = VOS_LOCAL_CPUID;\
            (pMsg)->ulReceiverPid       = PS_PID_ESM;\
            (pMsg)->ulLength            = (ulMsgLenthNoHeader);\
        }

#define NAS_EMM_GetSecuSrcSpace()           (g_pucSecuSrcBuf)
#define NAS_EMM_GetSecuDstSpace()           (g_pucSecuDstBuf)

/* zhaochen 00308719 begin for USIM Interface modify 2015-02-09 */
/*��װдUSIM��Ϣͷ�ĺ�*/
/*USIM����Ϣͷ����ͳһ��װ����MsgHeader��*/
#define NAS_EMM_SET_USIM_MSG_HEADER(pstMsg, ulMsgID, enApptype, ulSendpara)\
                    (pstMsg)->stMsgHeader.enMsgName   = (ulMsgID);\
                    (pstMsg)->stMsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.ulSenderPid = PS_PID_MM;\
                    (pstMsg)->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;\
                    (pstMsg)->stMsgHeader.enAppType = (enApptype);\
                    (pstMsg)->stMsgHeader.ulSendPara = (ulSendpara);\
                    (pstMsg)->stMsgHeader.ulReceiverPid = WUEPS_PID_USIM;
/* zhaochen 00308719 end for USIM Interface modify 2015-02-09 */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum    NAS_EMM_SMC_TYPE_ENUM
{
    NAS_EMM_SMC_UPDATE_NEW_MAPPED,
    NAS_EMM_SMC_UPDATE_NEW_NATIVE,
    NAS_EMM_SMC_UPDATE_NON_CUR_NATIVE,
    NAS_EMM_SMC_UPDATE_CUR,
    NAS_EMM_SMC_UPDATE_BUTT
};
typedef VOS_UINT32 NAS_EMM_SMC_TYPE_ENUM_UINT32;

enum    NAS_EMM_AUTH_FAIL_CAUSE_ENUM
{
    NAS_EMM_AUTH_MAC_FAILURE                   = 0x14,     /* USIM����MAC��ƥ����� */
    NAS_EMM_AUTH_SYNC_FAILURE                  = 0x15,     /* USIM����SYNCH��ƥ����� */
    NAS_EMM_AUTH_NON_EPS_AUTH_UNACCEPTABLE     = 0x1A,     /* �ж�AMFЯ����Separation Bit����E_UTRAN*/
    NAS_EMM_AUTH_FAIL_CAUSE_BUTT
};
typedef VOS_UINT8 NAS_EMM_AUTH_FAIL_CAUSE_ENUM_UINT8;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*****************************************************************************
�ṹ����    :NAS_LMM_MIDDLE_PARA_STRU
ʹ��˵��    :CK,IK
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucCK[NAS_LMM_SECU_NAS_KEY_LEN];
    VOS_UINT8                           aucIK[NAS_LMM_SECU_NAS_KEY_LEN];
}NAS_LMM_MIDDLE_PARA_STRU;

/*****************************************************************************
�ṹ����    :NAS_EMM_SECU_AUTH_RES_STRU
ʹ��˵��    :��Ȩ������RES�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucResLen;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                           aucRes[NAS_EMM_SECU_MAX_AUTH_RES_LEN];
}NAS_EMM_SECU_AUTH_RES_STRU;

/*****************************************************************************
�ṹ����    :NAS_LMM_AUTH_REQ_PARAM_STRU
ʹ��˵��    :��¼AUTH REQ��ϢЯ���Ĳ���
*****************************************************************************/

typedef struct
{
    VOS_UINT8                           aucRand[NAS_EMM_SECU_AUTH_RAND_LEN];
    VOS_UINT8                           aucAutn[NAS_EMM_SECU_AUTH_AUTN_LEN];
    VOS_UINT8                           ucKsi; /*USIM��Ȩ�ɹ���,���浽stNewSecuContext*/
    VOS_UINT8                           aucRsv[3];
}NAS_LMM_AUTH_REQ_PARAM_STRU;

/*****************************************************************************
�ṹ����    :NAS_LMM_USIM_AUTH_PARAM_STRU
ʹ��˵��    :USIM�İ�ȫ��ز���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpRand        :1;/* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv         :31;

    VOS_UINT8                           aucRand[NAS_EMM_SECU_AUTH_RAND_LEN];

    VOS_UINT8                           aucCK[NAS_LMM_SECU_NAS_KEY_LEN];
    VOS_UINT8                           aucIK[NAS_LMM_SECU_NAS_KEY_LEN];
    VOS_UINT8                           aucAuts[NAS_EMM_SECU_AUTH_AUTS_LEN]; /*USIM�ظ���AUTS��ֵ����������*/
    NAS_EMM_USIM_AUTH_RSLT_ENUM_UINT8   enUsimAuthRslt;          /* USIM����auth�����Ľ��*/
    VOS_UINT8                           ucOpId;  /* ���ڸ�USIM���ͼ�Ȩ����ʱ������USIM�Ļظ�ʱʹ�� */
    NAS_EMM_SECU_AUTH_RES_STRU          stRes;
}NAS_LMM_USIM_AUTH_PARAM_STRU;

typedef struct
{
    NAS_LMM_SECU_CONTEXT_STRU           stCurSecuContext;   /*��ǰ��ȫ������*/
    NAS_LMM_SECU_CONTEXT_STRU           stNewMappedSecuContext;
    NAS_LMM_SECU_CONTEXT_STRU           stNewNativeSecuContext;
    NAS_LMM_SECU_CONTEXT_STRU           stNonCurNativeSecuContext;

    NAS_LMM_SECU_KEY_STRU               stTempNasKey;

    NAS_GUMM_UMTS_CONTEXT_STRU          stUmtsSecuContext;
    VOS_UINT8                           aucNonceUE[NAS_EMM_SECU_NONCE_UE_LEN];
    VOS_UINT8                           aucNonceMME[NAS_EMM_SECU_NONCE_MME_LEN];

    NAS_LMM_USIM_AUTH_PARAM_STRU        stNasUsimAuthParam; /*��ȫģ����USIM������ز���*/

    VOS_UINT32                          ulFailTimes;        /*��¼"MAC"�� "Synch"ʧ�ܴ��� */
    NAS_EMM_SMC_TYPE_ENUM_UINT32        enSmcType;          /*��¼SMCЯ����KSI��New����Cur*/
    VOS_UINT32                          ulFlagInterRatHoMapped;
    VOS_UINT8                           aucSecuBuf[LRRC_LNAS_MAX_DATA_LENGTH];/*��ȫģ�������������Ҫ����ʱBuf*/

    NAS_LMM_AUTH_REQ_PARAM_STRU          stAuthReqParam;
}NAS_LMM_SECU_CONTROL_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern  NAS_LMM_SECU_CONTROL_STRU    g_NasEmmSecuControl;
extern  VOS_UINT8                    *g_pucSecuSrcBuf;
extern  VOS_UINT8                    *g_pucSecuDstBuf;


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID    NAS_EMM_SendAuthRsp(VOS_VOID);
extern VOS_VOID    NAS_EMM_AuthStateConvert(NAS_EMM_MAIN_STATE_ENUM_UINT16 ucMs,
                                            NAS_EMM_SUB_STATE_ENUM_UINT16 ucSs,
                                            NAS_EMM_STATE_TI_ENUM_UINT16 ucStaTId);
extern VOS_VOID    NAS_EMM_UsimAuthFail( NAS_EMM_AUTH_FAIL_CAUSE_ENUM_UINT8 enAuthFailCause );
extern VOS_UINT32  NAS_EMM_DeriveKasme(        const VOS_UINT8 *pucCK,
                                               const VOS_UINT8 *pucIK,
                                               VOS_UINT8 *pucKasme);
extern VOS_VOID NAS_EMM_AuthCheckFail(VOS_VOID);
extern VOS_VOID NAS_EMM_SecuDmaMalloc(VOS_VOID);
extern VOS_VOID  NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgRrcRelInd(VOS_UINT32 ulCause);
extern VOS_VOID  NAS_EMM_ProcMsRegImsiDetachInitMsgRrcRelInd
(
    VOS_UINT32                          ulCause
);
extern VOS_VOID  NAS_EMM_MsTauInitSsWaitCNCnfProcMsgRrcRelInd( VOS_UINT32 ulCause );
extern VOS_VOID  NAS_EMM_MsSerInitSsWaitCnSerCnfProcMsgRrcRelInd( VOS_UINT32 ulCause);
extern VOS_VOID  NAS_EMM_MsDrgInitSsWtCnDetCnfProcMsgRrcRelInd( VOS_UINT32 ulCause);
extern VOS_VOID  NAS_EMM_MsRegInitSsWtCnAttCnfProcMsgAuthRej(
                                                    VOS_UINT32  ulCause);

extern VOS_VOID NAS_LMM_PreProcAnyStateUsimAuthCnf(const USIMM_AUTHENTICATION_CNF_STRU  *pstUsimAuthCnf);
extern VOS_UINT32 NAS_LMM_PreProcUsimAuthCnf(MsgBlock  *pMsg);


extern VOS_VOID NAS_EMM_SndMmcSimAuthFailInd(LMM_MMC_SIM_AUTH_FAIL_ENUM_UINT16  enSimAuthFailValue);

extern VOS_VOID NAS_EMM_AuthCnFailErrRecord(
        EMM_OM_ERRLOG_AUTH_FAIL_ENUM_UINT16       enErrAuthFail);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/










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

#endif /* end of NasEmmSecuAuth.h */
