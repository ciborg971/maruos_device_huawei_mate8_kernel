

#ifndef __NASEMMCEMMINTERFACE_H__
#define __NASEMMCEMMINTERFACE_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "NasLmmPublic.h"


#include  "NasLmmPubMIntraMsg.h"
#include  "AppMmInterface.h"
#include  "NasEmmPubUGlobal.h"
#include  "NasEmmcMain.h"

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

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum    EMMC_EMM_MSG_ID_ENUM
{
    /* EMM����MMC����Ϣԭ�� */
    ID_EMMC_EMM_START_REQ                = ID_NAS_LMM_INTRA_EMMC_EMM_START_REQ,
    ID_EMMC_EMM_STOP_REQ                 = ID_NAS_LMM_INTRA_EMMC_EMM_STOP_REQ,


    /*ID_EMMC_EMM_ACTION_RESULT_REQ        = ID_NAS_LMM_INTRA_EMMC_EMM_ACTION_RESULT_REQ,*/
    ID_EMMC_EMM_USIM_STATUS_IND          = ID_NAS_LMM_INTRA_EMMC_EMM_USIM_STATUS_IND,

    /* MMC����EMM����Ϣԭ�� */
    ID_EMMC_EMM_START_CNF                = ID_NAS_LMM_INTRA_EMMC_EMM_START_CNF,
    ID_EMMC_EMM_STOP_CNF                 = ID_NAS_LMM_INTRA_EMMC_EMM_STOP_CNF,
    ID_EMMC_EMM_PLMN_IND                 = ID_NAS_LMM_INTRA_EMMC_EMM_PLMN_IND,
    ID_EMMC_EMM_SYS_INFO_IND             = ID_NAS_LMM_INTRA_EMMC_EMM_SYS_INFO_IND,
    ID_EMMC_EMM_COVERAGE_LOST_IND        = ID_NAS_LMM_INTRA_EMMC_EMM_COVERAGE_LOST_IND,

    ID_EMMC_EMM_MSG_ID_ENUM_BUTT         = ID_NAS_LMM_INTRA_MSG_TYPE_BUTT
};
typedef VOS_UINT32 EMMC_EMM_MSG_ID_ENUM_UINT32;

enum    EMMC_EMM_FORBIDDEN_INFO_ENUM
{
    EMMC_EMM_NO_FORBIDDEN                = 0x0000,   /* �����κν�ֹ�б���*/
    EMMC_EMM_FORBIDDEN_PLMN              = 0x0001,   /* �ڽ�ֹPLMN�б���*/
    EMMC_EMM_FORBIDDEN_PLMN_FOR_GPRS     = 0X0002,   /* �ڽ�ֹPLMN FOR GPRS�б���*/
    EMMC_EMM_FORBIDDEN_TA_FOR_ROAMING    = 0x0003,   /* �ڽ�ֹTA FOR ROAMING�б���*/
    EMMC_EMM_FORBIDDEN_TA_FOR_RPOS       = 0x0004,   /* �ڽ�ֹTA FOR RPOS�б���*/
    EMMC_EMM_FORBIDDEN_INFO_BUTT
};
typedef VOS_UINT32 EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32;


enum    EMMC_EMM_CHANGE_INFO_ENUM
{
    EMMC_EMM_NO_CHANGE   = 0x0000,    /* �κ���Ϣ��û�иı�              */
    EMMC_EMM_CHANGE_PLMN  = 0x0001,   /* PLMN ID �ı�         */
    EMMC_EMM_CHANGE_TA       = 0x0002,   /* TA �ı� */
    EMMC_EMM_CHANGE_CELL  = 0x0004,   /* CELL ID �ı�     */

    EMMC_EMM_CHANGE_INFO_BUTT
};
typedef VOS_UINT32 EMMC_EMM_CHANGE_INFO_ENUM_UINT32;

/*****************************************************************************
 ö����    : EMMC_EMM_CELL_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : С��פ��״̬,EMMC֪ͨEMM��ǰפ��С����AnyCell״̬����Normal״̬
*****************************************************************************/
enum EMMC_EMM_CELL_STATUS_ENUM
{
    EMMC_EMM_CELL_STATUS_NORMAL          = 0,                                    /* ����פ��    */
    EMMC_EMM_CELL_STATUS_ANYCELL         = 1,                                    /* AnyCellפ�� */
    EMMC_EMM_CELL_STATUS_BUTT
};
typedef VOS_UINT32 EMMC_EMM_CELL_STATUS_ENUM_UINT32;


/* EMMָʾMMC������ԭ��ֵ */
enum EMMC_EMM_PLMN_REQ_CAUSE_ENUM
{
    EMMC_EMM_PLMN_REQ_CAUSE_PS_START     = 0,        /* Э��ջ������Ҫ�������� */
    EMMC_EMM_PLMN_REQ_CAUSE_PLMN_SELECT  = 1,        /* ��Ҫ����PLMNѡ�� */
    EMMC_EMM_PLMN_REQ_CAUSE_BUTT
};
typedef VOS_UINT32 EMMC_EMM_PLMN_REQ_CAUSE_ENUM_UINT32;


enum EMMC_EMM_START_REQ_CAUSE_ENUM
{
    EMMC_EMM_START_REQ_CAUSE_NORMAL_START    = 0,    /* �������� */
    EMMC_EMM_START_REQ_CAUSE_NEED_RESET      = 1,    /* ��Ҫ��λ */
    EMMC_EMM_START_REQ_CAUSE_BUTT
};
typedef VOS_UINT32 EMMC_EMM_START_REQ_CAUSE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : MMC_EMM_START_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_START_REQ_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    EMMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;
    EMMC_EMM_START_REQ_CAUSE_ENUM_UINT32 enCause;
} EMMC_EMM_START_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MMC_EMM_START_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_START_CNF_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    EMMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;

} EMMC_EMM_START_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MMC_EMM_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_STOP_REQ_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    EMMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;
    VOS_UINT32                          ulReserved;

} EMMC_EMM_STOP_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MMC_EMM_STOP_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_STOP_CNF_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    EMMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;

} EMMC_EMM_STOP_CNF_STRU;


/*****************************************************************************
 �ṹ��    : MMC_EMM_PLMN_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_PLMN_IND_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    EMMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;

} EMMC_EMM_PLMN_IND_STRU;

/*****************************************************************************
 �ṹ��    : NAS_EMMC_EMM_SYS_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NAS_EMMC_EMM_SYS_INFO_IND_STRU�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    EMMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;

    EMMC_EMM_CHANGE_INFO_ENUM_UINT32    ulChangeInfo;
    NAS_MM_PLMN_ID_STRU                 stPlmnId;           /* PLMN ID            */
    NAS_MM_TAC_STRU                     stTac;              /* Tracking Area Code */
    VOS_UINT32                          ulCellId;           /* Cell Identity      */
    EMMC_EMM_FORBIDDEN_INFO_ENUM_UINT32  ulForbiddenInfo;    /* ��ֹ��Ϣ */
    EMMC_EMM_CELL_STATUS_ENUM_UINT32    ulCellStatus;
} EMMC_EMM_SYS_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMC_EMM_COVERAGE_LOST_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_COVERAGE_LOST_IND_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    EMMC_EMM_MSG_ID_ENUM_UINT32          enMsgId;

} EMMC_EMM_COVERAGE_LOST_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMC_EMM_USIM_STATUS_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMC_EMM_USIM_STATUS_IND_STRU��Ϣ�ṹ����
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
extern VOS_UINT32  NAS_EMMC_MsgDistr( MsgBlock *pMsg );

extern VOS_VOID  NAS_EMMC_UpdateForbTaList( VOS_VOID );
extern VOS_VOID  NAS_EMMC_SendEmmCoverageLostInd( VOS_VOID );
extern VOS_VOID  NAS_EMM_AppRegStatInd( NAS_APP_REG_STAT_ENUM_UINT32   ulNasAppState,
                                           NAS_LMM_MAIN_STATE_ENUM_UINT16  enMainState);

extern  VOS_UINT32 * NAS_EMM_GetEmmGlobleAddr(NAS_LMM_GLOBLE_PARA_ENUM_UINT32 ulGlobleParaName);
/*extern VOS_UINT32  NAS_EMM_GetRrcConnState(VOS_VOID);*/
extern VOS_VOID  NAS_EMMC_SendRrcCellSelectionReq
(
    LRRC_LNAS_RESEL_TYPE_ENUM_UINT32 ulReselType
);
extern VOS_VOID    NAS_LMM_StartStateTimer(
                           NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId );
extern VOS_UINT32  NAS_EMM_lteRatIsExist(VOS_VOID);
extern VOS_UINT32  NAS_EMM_IsLteDisabled( VOS_VOID );
extern VOS_UINT32  NAS_EMMC_GetUserSpecPlmnFlag(VOS_VOID);
extern VOS_VOID  NAS_EMMC_SetUserSpecPlmnFlag(NAS_EMMC_USER_SPEC_PLMN_FLAG_UINT32  ulUserFlag);
extern VOS_VOID  NAS_EMMC_AddPlmnInRej18PlmnList(const NAS_MM_PLMN_ID_STRU *pstPlmnId);
extern VOS_UINT32 NAS_EMMC_GetRejCause18Flag(VOS_VOID);
extern VOS_VOID NAS_EMMC_SetRejCause18Flag
(
    NAS_EMM_REJ_FLAG_ENUM_UINT32 ulRejFlag
);

extern VOS_UINT32 NAS_EMMC_ProcTimerMsgWaitPlmnSrchcnfTimerExp(MsgBlock *pMsg);
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

#endif /* end of EmmcEmmInterface.h */
