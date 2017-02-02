
#ifndef __NASEMMSECUPROTECT_H__
#define __NASEMMSECUPROTECT_H__



/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "NasLmmPubMFsm.h"
#if (VOS_VXWORKS == VOS_OS_VER)
#include "cacheLib.h"
#endif

/*lint -e7*/
/*lint -e322*/
#include  "TlPsDrv.h"
/*lint +e322*/
/*lint +e7*/




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
#define NAS_EMM_SECU_CN_MSG_HEAD_POS             0
#define NAS_EMM_SECU_CN_MSG_TYPE_POS             1
#define NAS_EMM_SECU_IDEN_REQ_TYPE_POS           2
#define NAS_EMM_SECU_REJ_CAUSE_POS               2
#define NAS_EMM_SECU_MSG_HIGH_BIT                0xF0
#define NAS_EMM_SECU_MSG_LOW_BIT                 0x0F

#define NAS_EMM_SECU_HEADER_LEN                  1

#define NAS_EMM_SECU_SHORT_MAC_LEN               2
#define NAS_EMM_SECU_SHORT_MAC_POS               2

#define NAS_EMM_SECU_NEED_PROT                   0
#define NAS_EMM_SECU_NOT_NEED_PROT               1

#define NAS_EMM_MIN_PLAIN_MSG_LEN                2
#define NAS_EMM_MIN_PROT_MSG_LEN                 8


/* Cipher and Integrity param */
#define NAS_EMM_SECU_SECURITY_BEARERID                  0x00

/* NAS���� CIPHER û�� Private ����*/
#define NAS_EMM_SECU_NO_PRIVATE                  0

/*���ֽ���洢ul�������ݵ�pucData*/
#define NAS_SECU_SET_32BIT_PARA(pucData, ulPara) \
        ((pucData)[0]) = (VOS_UINT8)(((ulPara)>>24) & 0xff);\
        ((pucData)[1]) = (VOS_UINT8)(((ulPara)>>16) & 0xff); \
        ((pucData)[2]) = (VOS_UINT8)(((ulPara)>>8) & 0xff); \
        ((pucData)[3]) = (VOS_UINT8)((ulPara) & 0xff)

#define NAS_SECU_GET_SNOW_3G_KEY(SecuParamKey,NasKey)\
        NAS_LMM_MEM_CPY((SecuParamKey), (NasKey + 12), 4);\
        NAS_LMM_MEM_CPY((SecuParamKey + 4), (NasKey + 8), 4);\
        NAS_LMM_MEM_CPY((SecuParamKey + 8), (NasKey + 4), 4);\
        NAS_LMM_MEM_CPY((SecuParamKey + 12), (NasKey), 4);

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

enum NAS_EMM_SECU_UNPROT_RSLT_ENUM
{
    NAS_EMM_SECU_UNPROT_SUCC                   = 0,
    NAS_EMM_SECU_UNPROT_FAIL                   = 1,
    NAS_EMM_SECU_UNPROT_SMC                    = 2,
    NAS_EMM_SECU_UNPROT_RSLT_BUTT
};
typedef VOS_UINT32 NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32;

enum NAS_EMM_SECU_DIRECTION_ENUM
{
    NAS_EMM_SECU_UPLINK                = 0 ,
    NAS_EMM_SECU_DNLINK                = 1 ,
    NAS_EMM_SECU_DIRECTION_BUTT
};
typedef VOS_UINT8 NAS_EMM_SECU_DIRECTION_ENUM_UINT8;


enum    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_ENUM
{
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_SPECIAL_NAS_MSG       = 1,/*����Ȩ��Ϣ��ulValue��Ϊ��ϢID*/
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_EIA0                  = 2,/*������ȫ״̬��ΪNOT EXIST��ֻ����EIA0��SMC,ulValue��Ч*/
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_INT_CHECK_FAIL            = 3,/*�������Ա���ʧ��,ulValue��Ч*/
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECRYPT_FAIL              = 4,/*����ʧ��,ulValue��Ч*/
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_REJ_PLAIN_MSG             = 5,/*��ȫ����ʱ�յ�PLAIN MSG,ulValue��Ϊg_ulNasPlainRejMsgFlag������ϢID*/
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_PD_EMM                = 6,/*��PD EMM,ulValue��Ч*/
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NON_SMC                   = 7,/*��SMC��Ϣ,ulValue��Ϊ��ϢID*/
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_EIA0_NO_EMC_PDN           = 8,/*û�н���PDNʱ����EIA0,ulValue��ΪNAS_LMM_GetEmmInfoRegStatus*/
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_DECODE_FAIL               = 9,/*SMC����ʧ��,ulValue��ΪNAS_EMM_DecodeSmcMsg�����쳣�˳���֧��*/
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_KSI_MISMATCH              = 10,/*ksi��ƥ��,ulValue��ΪSQN*/
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_ALG_NOT_SUPPORT           = 11,/*�㷨��֧��,ulValue��Ч*/
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_UE_CAP_MISMATCH           = 12,/*UE������ƥ��,ulValue��ΪNAS_EMM_CheckMutiModeSupport*/
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_NONCE_MISMATCH            = 13,/*NONCE��ƥ��,ulValue��Ч*/

    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_BUTT
};
typedef VOS_UINT32  NAS_LMM_OM_LOG_SECU_FAIL_TYPE_ENUM_UINT32;




/*****************************************************************************
   5 STRUCT
*****************************************************************************/
#define NAS_EMM_SECU_ACT_TBL_ITEM(NAS_LMM_SECU_HEADER_TYPE, pFun)    \
        {NAS_LMM_SECU_HEADER_TYPE, pFun}

/*****************************************************************************
�ṹ����    :NAS_EMM_PROT_PARAM_STRU
ʹ��˵��    :�տ���Ϣ�����Ա����������Լ�飬���ܣ�����ʱ�������ṹ
            pucMsg:
            1)�����Լ��:��ȫͷ+MAC+SN+MSG
            2)����:MSG(����)
            3)����:MSG(����)
            4)�����Ա���:MSG(���ܺ����Ϣ)
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSecuALg;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT8                          *pucMsg;
    VOS_UINT32                         *pulMsgSize;
    VOS_UINT32                          ulNasCount;
}NAS_EMM_PROT_PARAM_STRU;

typedef struct
{
    MSG_HEADER_STRU                                 stMsgHeader;     /*_H2ASN_Skip*/
    NAS_LMM_FSM_STATE_STRU                          stEmmCurState;
    NAS_LMM_FSM_STATE_STRU                          stSecuCurState;
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_ENUM_UINT32       enSecuFailType;
    VOS_UINT32                                      ulValue;
}NAS_LMM_OM_LOG_SECU_VERIFY_FAIL_STRU;


typedef struct
{
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_ENUM_UINT32       ulFailType;
    VOS_UINT8                                       aucPrintStr[NAS_COMM_PRINT_MAX_ITEM_LEN];
}NAS_LMM_OM_LOG_SECU_VERIFY_FAIL_PRINT_STR_STRU;




/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern NAS_EMM_STA_STRU     g_astEmmSecuStaTbl[];

extern VOS_UINT32 g_ulTauCipheredFlag;
extern VOS_UINT8  *g_pucSecuSrcBuf;
extern VOS_UINT8  *g_pucSecuDstBuf;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_UINT32  NAS_LMM_SECU_FsmErr(        VOS_UINT32           ulMsgId,
                                              VOS_VOID      *PMsg);
extern VOS_BOOL    NAS_EMM_IsSpecNasMsg(      const VOS_UINT8   *pucRcvNasMsg,
                                              VOS_UINT32  *pulNasMsgSize);
extern VOS_UINT32  NAS_EMM_CompDlNasCount(
                                        VOS_UINT32  ulLocDlNasCount,
                                        VOS_UINT8   ucRcvSn );
/*extern VOS_VOID    NAS_EMM_FillL2SrcForIntCheck(VOS_UINT8          *pucRcvCnNasMsg,
                                              const VOS_UINT32     *pulNasMsgSize,
                                              PS_SECU_PARA_STRU  *pstSecuPara);*/
/*extern VOS_VOID    NAS_EMM_FillL2IV(          NAS_EMM_SECU_DIRECTION_ENUM_UINT8 enDirection,
                                              VOS_UINT32  ulNasCount,
                                              PS_SECU_PARA_STRU  *pstSecuPara);*/
/*extern VOS_VOID    NAS_EMM_FillL2Key(         VOS_UINT8         ucSecuALg,
                                              const VOS_UINT8  *pucNasKey,
                                              VOS_UINT8        *pucL2Key);*/
extern VOS_UINT32  NAS_EMM_SecuIntCheck(      const NAS_EMM_PROT_PARAM_STRU   *pstUnProtParam);
extern VOS_UINT32  NAS_EMM_SecuDecrypt(       const NAS_EMM_PROT_PARAM_STRU   *pstUnProtParam);
extern VOS_VOID    NAS_EMM_SecuDelSecuHead(    VOS_UINT8    *pucRcvCnNasMsg,
                                              VOS_UINT32   *pulNasMsgSize);
extern VOS_UINT32  NAS_EMM_IntEncMsgCommProc( LRRC_LNAS_MSG_STRU *pstNasMsg );

extern  NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32    NAS_EMM_CurNotActiveNewAnyMsgPlain(
                                                VOS_UINT32  ulSecuHeadType,
                                                VOS_VOID   *pulRrcNasMsg);
extern  NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32    NAS_EMM_CurNotActiveNewAnyMsgInt(
                                                VOS_UINT32  ulSecuHeadType,
                                                VOS_VOID   *pulRrcNasMsg);
extern  NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32    NAS_EMM_CurExistNotAcitveNewAnyMsgIntEnc(
                                                VOS_UINT32  ulSecuHeadType,
                                                VOS_VOID   *pulRrcNasMsg);
extern  NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32    NAS_EMM_CurExistActiveNewAnyMsgIntEnc(
                                                VOS_UINT32  ulSecuHeadType,
                                                VOS_VOID   *pulRrcNasMsg);

extern NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32     NAS_EMM_CurExistActiveNewAnyMsgPlain(
                                                VOS_UINT32  ulSecuHeadType,
                                                VOS_VOID   *pulRrcNasMsg);
extern  NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32    NAS_EMM_OnlyCurExistMsgSmc(
                                                VOS_UINT32  ulSecuHeadType,
                                                VOS_VOID   *pulRrcNasMsg);
extern NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32    NAS_EMM_CurAnyNewExistMsgSmc(
                                                VOS_UINT32  ulSecuHeadType,
                                                VOS_VOID   *pulRrcNasMsg);

extern NAS_EMM_SECU_UNPROT_RSLT_ENUM_UINT32 NAS_EMM_CurNotExistNewNotExistMsgSmc
(
    VOS_UINT32                          ulSecuHeadType,
    VOS_VOID                           *pulRrcNasMsg
);
extern  VOS_UINT32  NAS_EMM_SecuNotSerIntProt( const LRRC_LNAS_MSG_STRU *pstRrcNasMsg );
extern  VOS_UINT32  NAS_EMM_SecuSerIntProt( LRRC_LNAS_MSG_STRU *pstNasMsg );
extern  VOS_UINT32  NAS_EMM_SecuEncrypt( LRRC_LNAS_MSG_STRU *pstRrcNasMsg );
extern  VOS_UINT32  NAS_EMM_SecuMsgNeedNotEncrypt( NAS_EMM_CN_MSG_TYPE_ENUM_UINT8 enMsgType);
extern  VOS_UINT32  NAS_EMM_VerifyDlMsgLen(      VOS_UINT32   ulSecuHeaderType,
                                                 MsgBlock    *pMsg );
extern  VOS_VOID    NAS_EMM_SecuAddSecuHeader(NAS_EMM_SECU_HEAD_TYPE_ENUM_UINT8 enSecurHeadType,
                                                    LRRC_LNAS_MSG_STRU *pstRrcNasMsg);
extern VOS_UINT32  NAS_EMM_NotSerReqMsgProt( LRRC_LNAS_MSG_STRU *pstRrcNasMsg );
extern VOS_UINT32 NAS_EMM_SecuWhetherNeedProt(const LRRC_LNAS_MSG_STRU *pstNasMsg);
extern VOS_UINT32  NAS_EMM_SecuUpLayerMsgProt( LRRC_LNAS_MSG_STRU *pstNasMsg );
extern VOS_UINT32  NAS_EMM_SecuEmmMsgProt( LRRC_LNAS_MSG_STRU *pstNasMsg );
extern VOS_VOID NAS_EMM_SndOmLogSecuVerifyFail
(
    NAS_LMM_OM_LOG_SECU_FAIL_TYPE_ENUM_UINT32           enSecuFailType,
    VOS_UINT32                                          ulValue
);
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

#endif /* end of NasEmmSecuProtect.h */
