

#ifndef __NASEMMSECUINTERFACE_H__
#define __NASEMMSECUINTERFACE_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"

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
  2 Macro
*****************************************************************************/
#define NAS_EMM_SECU_AUTH_RAND_LEN                           16
#define NAS_LMM_SECU_AUTH_KEY_ASME_LEN                        32

#define NAS_LMM_SECU_AUTH_KEY_NAS_INT_LEN                     16
#define NAS_LMM_SECU_AUTH_KEY_NAS_ENC_LEN                     16

/*  ��Ϊ����:  LPS_NV_GET_HARD_KDF_OFF
#define NAS_EMM_HARD_KDF_OPEN                               1
#define NAS_EMM_HARD_KDF_CLOSE                              0
#define NAS_EMM_HARD_KDF_HYBRI                              2
*/

#define NAS_EMM_COUNT_INTRA_MSG_NO_HEADER_LEN(ulNasMsgSize)\
        (\
            ((sizeof(NAS_EMM_MRRC_DATA_REQ_STRU)\
            - NAS_EMM_VOS_HEADER_LEN)\
            - NAS_EMM_4BYTES_LEN)\
            + ulNasMsgSize\
        )

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

enum    NAS_EMM_SECU_HEAD_TYPE_ENUM
{
    NAS_EMM_SECU_HEAD_TYPE_PLAIN                            = 0x00,
    NAS_EMM_SECU_HEAD_TYPE_INTEGRITY                        = 0x10,
    NAS_EMM_SECU_HEAD_TYPE_INTEGRITY_CIPHERED               = 0x20,
    NAS_EMM_SECU_HEAD_TYPE_NEW_KEY_INTEGRITY                = 0x30,
    NAS_EMM_SECU_HEAD_TYPE_NEW_KEY_INTEGRITY_CIPHERED       = 0x40,
    NAS_EMM_SECU_HEAD_TYPE_SERVICE_REQUEST                  = 0xC0,
    NAS_EMM_SECU_HEAD_TYPE_BUTT
};
typedef VOS_UINT8   NAS_EMM_SECU_HEAD_TYPE_ENUM_UINT8;

enum NAS_EMM_SECU_NAS_KEY_TYPE_ENUM
{
    NAS_EMM_SECU_CIPHER_KEY,                             /* ������Կ */
    NAS_EMM_SECU_INTEGRITY_KEY,                          /* �����Ա�����Կ */
    NAS_EMM_SECU_NAS_KEY_BUTT
};
typedef VOS_UINT8   NAS_EMM_SECU_NAS_KEY_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : NAS_EMM_SECURITY_UNPROTECT_RLT_ENUM
 �ṹ˵��  : ����,�����Ա������Ƿ�ɹ�
*****************************************************************************/
enum NAS_EMM_SECU_UNPROTECT_RLT_ENUM
{
    NAS_EMM_SECU_UNPROTECT_SUCC               = 0,       /* �Ᵽ���ɹ� */
    NAS_EMM_SECU_UNPROTECT_FAIL_NO_INTRA_MSG      = 1,   /* �Ᵽ��ʧ�ܣ����ڲ���Ϣ */
    NAS_EMM_SECU_UNPROTECT_FAIL_WITH_INTRA_MSG    = 2,   /* �Ᵽ��ʧ�ܣ����ڲ���Ϣ */

    NAS_EMM_SECU_UNPROTECT_RLT_BUTT
};
typedef VOS_UINT32 NAS_EMM_SECU_UNPROTECT_RLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_EMM_AUTH_REJ_INTRA_CAUSE_ENUM
 �ṹ˵��  : AUTH REJ�ڲ�����ԭ��ֵ,���Ժ�RRC_REL_INDͳһ����
*****************************************************************************/
enum NAS_EMM_AUTH_REJ_INTRA_CAUSE_ENUM
{
    NAS_EMM_AUTH_REJ_INTRA_CAUSE_START                = LRRC_LNAS_REL_CAUSE_BUTT,/* ��RRC_NAS_REL_CAUSE����*/
    NAS_EMM_AUTH_REJ_INTRA_CAUSE_NORMAL,
    NAS_EMM_AUTH_REJ_INTRA_CAUSE_BUTT
};
typedef VOS_UINT32 NAS_EMM_AUTH_REJ_INTRA_CAUSE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
�ṹ����    :NAS_EMM_INTRA_AUTH_FAIL_STRU
ʹ��˵��    :INTRA_AUTH_FAIL��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32          ulMsgId;   /* ��ϢID */
    VOS_UINT32          ulCause;   /*ʧ��ԭ��*/
}NAS_EMM_INTRA_AUTH_FAIL_STRU;

/*****************************************************************************
�ṹ����    :NAS_LMM_KEY_STRU
ʹ��˵��    :NasCK,NasIK
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucKNasInt[NAS_LMM_SECU_AUTH_KEY_NAS_INT_LEN];
    VOS_UINT8                           aucKNasEnc[NAS_LMM_SECU_AUTH_KEY_NAS_ENC_LEN];
}NAS_LMM_SECU_KEY_STRU;

/*****************************************************************************
�ṹ����    :NAS_LMM_SECU_CONTEXT_STRU
ʹ��˵��    :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucKSIsgsn;
    VOS_UINT8                           ucKSIasme;
    VOS_UINT8                           ucSecuAlg;
    VOS_UINT8                           ucRsv;
    VOS_UINT8                           aucKasme[NAS_LMM_SECU_AUTH_KEY_ASME_LEN];
    VOS_UINT32                          ulUlNasCount;
    VOS_UINT32                          ulDlNasCount;
    NAS_LMM_SECU_KEY_STRU                stNasKey;
}NAS_LMM_SECU_CONTEXT_STRU;
/*****************************************************************************
 ???    : NAS_LMM_OM_LOG_NV_SEC_CONTEXT_INFO_STRU
 ????  : NV??SecContext????
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;     /*_H2ASN_Skip*/
    /* mod by yanglei 00307272 for KEY_INFO_REPORT2,2015-08-13,begin */
    NAS_LMM_SECU_CONTEXT_STRU           stCurSecContext;
    NAS_LMM_SECU_CONTEXT_STRU           stNewMappedSecuContext;
    NAS_LMM_SECU_CONTEXT_STRU           stNewNativeSecuContext;
    NAS_LMM_SECU_CONTEXT_STRU           stNonCurNativeSecuContext;

    NAS_LMM_SECU_KEY_STRU               stTempNasKey;
    NAS_GUMM_UMTS_CONTEXT_STRU          stUmtsSecuContext;

    NAS_MM_UE_NET_CAP_STRU              stUeNetCap;
    NAS_MM_MS_NET_CAP_STRU              stMsNetCap;
    /* mod by yanglei 00307272 for KEY_INFO_REPORT2,2015-08-13,end */

}NAS_LMM_OM_LOG_EPS_SEC_CONTEXT_INFO_STRU;
/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
/*  LRRCҲҪʹ�ã��ŵ� LPsOm.h ������
extern VOS_UINT32                              g_ulHardKdf;
*/
/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32  NAS_EMM_SecuUnProtect( MsgBlock  *pMsg );
extern VOS_VOID    NAS_LMM_SECU_FsmReg( VOS_VOID );
extern VOS_VOID    NAS_EMM_SecuInit( VOS_VOID );
extern VOS_VOID    NAS_EMM_FreeSecuDyn( VOS_VOID );
extern VOS_VOID    NAS_Secu_FsmInit( VOS_VOID );
extern VOS_VOID    NAS_EMM_ConnToIdleTransSecuSta( VOS_VOID );
extern VOS_VOID    NAS_EMM_ClearCurSecuCntxt(VOS_VOID);
extern VOS_VOID    NAS_EMM_ClearAllSecuCntxt( VOS_VOID );
extern VOS_UINT32  NAS_EMM_SecuProtect(VOS_VOID  * pstMrrcDataReq);
extern VOS_UINT8   NAS_EMM_SecuGetKSIValue( VOS_VOID );
extern VOS_UINT32  NAS_EMM_SecuGetUmtsKsi( VOS_VOID );
extern VOS_UINT32  NAS_EMM_SecuGetUlNasCountVAlue( VOS_VOID );
extern VOS_UINT8*  NAS_EMM_SecuGetNonceUE( VOS_VOID );
extern VOS_UINT8   NAS_EMM_SecuGetNonCurKSIasme( VOS_VOID );
extern VOS_VOID    NAS_EMM_SecuSetCurCntxt( const NAS_LMM_SECU_CONTEXT_STRU *pstCurSecuCntxt );
extern NAS_LMM_SECU_CONTEXT_STRU *  NAS_EMM_SecuGetCurCntxtAddr(VOS_VOID);
extern VOS_VOID    NAS_EMM_AbortAuthProcedure(VOS_VOID);
extern VOS_VOID    NAS_EMM_SecuClearRandRes( VOS_VOID );
extern VOS_VOID    NAS_EMM_SecuStateConvert(  NAS_EMM_MAIN_STATE_ENUM_UINT16 usCurSta,
                                              NAS_EMM_SUB_STATE_ENUM_UINT16 usNewSta );
extern VOS_UINT32  NAS_EMM_MsAnyStateSsAnyStateMsgCnAuthReq(
                                        VOS_UINT32 ulMsgId,
                                        VOS_VOID   *pMsg );
extern VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthReq(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsg );
extern VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgCnAuthRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru);
extern VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru);
extern VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgTauRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru);
extern VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgSerRej(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru);
extern VOS_UINT32  NAS_EMM_MsAnyStateSsAnyStateMsgUsimAuthCnf(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsg );
extern VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgT3418Exp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru );
extern VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgT3420Exp(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru );
extern VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgRrcRelInd(
                                        VOS_UINT32  ulMsgId,
                                        VOS_VOID   *pMsgStru);
extern VOS_VOID    NAS_EMM_SECU_ClearResource(VOS_VOID);

/*INTER RAT*/
extern VOS_UINT32  NAS_LMM_PreProcReselSecuInfoReq( MsgBlock * pMsg );
extern VOS_UINT32  NAS_LMM_PreProcHoSecuInfoReq( MsgBlock * pMsg );
extern VOS_UINT32  NAS_LMM_PreProcMsgMmHoSecuInfoReq(  MsgBlock * pMsg );
extern VOS_VOID  NAS_EMM_SecuResumeIdle(VOS_VOID );
extern VOS_VOID  NAS_EMM_SecuRrcSecuParamIndHo(
                                                const VOS_UINT8 *pucSecuParaHo );
extern VOS_VOID  NAS_EMM_SecuRrcRelIndHoFail(VOS_VOID );
extern VOS_VOID  NAS_EMM_ClearNewMappedSecuCntxt( VOS_VOID );
extern VOS_VOID  NAS_EMM_ClearNewNativeSecuCntxt( VOS_VOID );
extern VOS_VOID  NAS_EMM_ClearCurMappedSecuCntxt( VOS_VOID );
extern VOS_VOID  NAS_EMM_ClearNonCurNativeSecuCntxt( VOS_VOID );
extern VOS_VOID  NAS_EMM_SecuDeregClrSecuCntxt(VOS_VOID);
extern VOS_VOID  NAS_EMM_SecuUpdateDlNasCountHo( VOS_UINT8 ucCnDlNasCount );
extern VOS_VOID  NAS_EMM_SecuHoOrCcoReverse( VOS_VOID);

extern VOS_UINT32 NAS_EMM_KDF_HmacSha256
(
    VOS_UINT8 *pucBuf,
    VOS_UINT32 ulBuflen,
    VOS_UINT8 *pucKey,
    VOS_UINT8 aucDigest[NAS_LMM_SECU_AUTH_KEY_ASME_LEN]
);
extern VOS_VOID  NAS_EMM_SecuSetInterRatHoNotMapped( VOS_VOID );

extern VOS_UINT32 NAS_EMM_SndCommonProcedureMsgFailProc(VOS_VOID* pMsg,VOS_UINT32 *pulIsDelBuff);

extern VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgEia0ActNotify
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgRabmDrbSetupInd
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                            *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgAttachAccept
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgTauAccept
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);
extern VOS_UINT32  NAS_EMM_MsAuthInitSsWtCnAuthMsgCnDetachAcp
(
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pMsgStru
);


extern VOS_UINT32  NAS_EMM_IsRegStatusEmcRegingOrContainEmcBear(VOS_VOID);




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

#endif /* end of NasEmmSecuInterface.h */
