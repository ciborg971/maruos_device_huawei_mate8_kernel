/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.
******************************************************************************/

#ifndef __ETCLPPINTERFACE_H__
#define __ETCLPPINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"
#include    "LPSCommon.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 macro
*****************************************************************************/

#define ETC_LPP_MSG_HDR  0

/*��װдLPP DL��Ϣͷ�ĺ�*/
#define NAS_ETC_WRITE_LPP_MSG_HEAD(pstMsg, ulLppMsgID)\
                    (pstMsg)->enMsgName         = (ulLppMsgID);\
                    (pstMsg)->ulSenderCpuId     = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulSenderPid       = PS_PID_TC;\
                    (pstMsg)->ulReceiverCpuId   = VOS_LOCAL_CPUID;\
                    (pstMsg)->ulReceiverPid     = PS_PID_LPP;


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

enum ETC_LPP_MSG_TYPE_ENUM
{
    /*��Ϣԭ��*/
    /*ETC���͸�LPP����Ϣԭ��*/
    ID_ETC_LPP_RESET_POSTION_INFO_IND                     = (ETC_LPP_MSG_HDR + 0x1),  /* _H2ASN_MsgChoice ETC_LPP_RESET_POSTION_INFO_STRU*/

    ID_ETC_LPP_BUTT
};
typedef VOS_UINT32 ETC_LPP_MSG_TYPE_ENUM_UINT32;
enum ETC_LPP_RESET_TYPE_ENUM
{
    ETC_LPP_RESET_TYPE_GNSS                         = 0, /*reset GNSS*/
    ETC_LPP_RESET_TYPE_OTDOA                        = 1, /*reset OTODA*/

    ETC_LPP_RESET_TYPE_BUTT
};
typedef VOS_UINT32 ETC_LPP_RESET_TYPE_ENUM_UINT32;


/*****************************************************************************
 5. STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : ETC_LPP_RESET_POSTION_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ETC��LPP֮��ĸ�λ������Ϣ���߼�
*****************************************************************************/
typedef struct
 {
     VOS_MSG_HEADER                                     /*_H2ASN_Skip*/
     ETC_LPP_MSG_TYPE_ENUM_UINT32           enMsgName;  /*_H2ASN_Skip*/

     ETC_LPP_RESET_TYPE_ENUM_UINT32         enRestType;
} ETC_LPP_RESET_POSTION_INFO_STRU;

typedef struct
{
    ETC_LPP_MSG_TYPE_ENUM_UINT32        enMsgID;            /*_H2ASN_MsgChoice_Export ETC_LPP_MSG_TYPE_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          ETC_LPP_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}ETC_LPP_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    ETC_LPP_MSG_DATA                     stMsgData;
}EtcLppInterface_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
extern VOS_VOID NAS_LPP_RcvLppEtcResetPostitionInfoInd( ETC_LPP_RESET_POSTION_INFO_STRU *pRcvMsg );
extern VOS_VOID NAS_LPP_EtcMsgDistr( VOS_VOID *pRcvMsg );

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

#endif /* end of EmmLppInterface.h */





