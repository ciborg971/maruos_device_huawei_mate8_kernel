
#ifndef __NASEMMCMAIN_H__
#define __NASEMMCMAIN_H__


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "NasLmmCore.h"


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
#define NAS_EMMC_GetEmmcInfoAddr()          (&g_stEmmcGlobalCtrl)

#define NAS_EMMC_GetGuSysInfoAddr()         (&g_stEmmcGuSysInfo)

#define NAS_EMMC_GetRej18PlmnListAddr()     (&(NAS_EMMC_GetEmmcInfoAddr()->stRej18PlmnList))

/* ����PlmnSrch�ı�ʶ */
#define NAS_EMMC_SetPlmnSrchFlag(Flag)              (((NAS_EMMC_GetEmmcInfoAddr())->ulPlmnsrchFlag) = (Flag))
#define NAS_EMMC_GetPlmnSrchFlag()                  ((NAS_EMMC_GetEmmcInfoAddr())->ulPlmnsrchFlag)

/* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
#define NAS_EMMC_GetMsgSenderPid(pMsg)                  (((PS_MSG_HEADER_STRU*)pMsg)->ulSenderPid)

/* �����Ƿ��յ�RRC������Not Camp On ��Ϣ */
#define NAS_EMMC_SetNotCampOnFlag(Flag)             (((NAS_EMMC_GetEmmcInfoAddr())->ulNotCampOnFlag) = (Flag))
#define NAS_EMMC_GetNotCampOnFlag()                 ((NAS_EMMC_GetEmmcInfoAddr())->ulNotCampOnFlag)

#define NAS_EMMC_GetGuSysInfoPlmnAddr()             (&(NAS_EMMC_GetGuSysInfoAddr()->stPlmnId))


#define NAS_EMMC_GetNameFromMsg(ulMsgId,pMsg)\
{\
    if(VOS_PID_TIMER == NAS_EMMC_GetMsgSenderPid(pMsg))\
    {\
        ulMsgId = PS_GET_REL_TIMER_NAME(pMsg);\
    }\
    else\
    {\
        ulMsgId = NAS_LMM_GetMsgId(pMsg);\
    }\
}

#define NAS_EMMC_SetShareNetFlag(Flag)             (((NAS_EMMC_GetEmmcInfoAddr())->ucShareNetFlag) = (Flag))
#define NAS_EMMC_GetShareNetFlag()                 ((NAS_EMMC_GetEmmcInfoAddr())->ucShareNetFlag)

#define NAS_EMMC_GetEplmnListAddr()                 (&((NAS_EMMC_GetEmmcInfoAddr())->stEPlmnList))

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_EMMC_USER_SPEC_PLMN_FLAG_ENUM
 ö��˵��  : �û�ָ��������ʶ
*****************************************************************************/
enum NAS_EMMC_USER_SPEC_PLMN_FLAG_ENUM
{
    NAS_EMMC_USER_SPEC_PLMN_NO           = 0x00,
    NAS_EMMC_USER_SPEC_PLMN_YES          = 0x01,

    NAS_EMMC_USER_SPEC_PLMN_BUTT

};
typedef VOS_UINT32  NAS_EMMC_USER_SPEC_PLMN_FLAG_UINT32;



/*****************************************************************************
   5 STRUCT
*****************************************************************************/
typedef struct
{
    /*NAS_MM_PLMN_ID_STRU                stReqPlmn;*/          /* ���������PLMN */

    NAS_EMMC_USER_SPEC_PLMN_FLAG_UINT32 enUserSpecPlmnFlag;
    NAS_MM_PLMN_LIST_STRU               stRej18PlmnList;
    NAS_EMM_REJ_FLAG_ENUM_UINT32        ulRej18Flag;
    NAS_EMM_PLMN_SRCH_FLAG_ENUM_UINT32  ulPlmnsrchFlag;
    /* ע��/����״̬�ϱ�����MMC��ɾ��ע��/����״̬��ش��� */
    VOS_UINT32                          ulNotCampOnFlag;

    VOS_UINT8                           ucShareNetFlag; /* ���ӹ��������ʶ��VOS_TRUE:�������磬VOS_FALSE:���ǹ������� */
    VOS_UINT8                           aucRsv[3];

    /* �����ЧPLMN�б� */
    NAS_MM_PLMN_LIST_STRU               stEPlmnList;
} NAS_EMMC_GLOBAL_STRU;

typedef struct
{
    VOS_UINT32                          bitOpRac      :1; /* 1: VALID; 0: INVALID*/
    VOS_UINT32                          bitOpRsv      :31;

    NAS_MM_PLMN_ID_STRU                 stPlmnId;
    VOS_UINT32                          ulCellId;
    VOS_UINT16                          usLac;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           ucRatType;          /*0:GSM; 1:UMTS */
}NAS_EMMC_GU_SYS_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern  NAS_EMMC_GLOBAL_STRU                    g_stEmmcGlobalCtrl;

extern  NAS_EMMC_GU_SYS_INFO_STRU               g_stEmmcGuSysInfo;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID  NAS_EMMC_Init(VOS_VOID );



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

#endif /* end of NasEmmcMain.h */

















