


#ifndef __LNASSTKINTERFACE_H__
#define __LNASSTKINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"


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

enum LNAS_STK_MSG_ID_ENUM
{
    ID_LNAS_STK_NETWORK_REJECTION_EVENT       = 0x00,      /* _H2ASN_MsgChoice LNAS_STK_NETWORK_REJECTION_EVENT_STRU*/

    ID_LNAS_STK_MSG_ID_BUTT
} ;
typedef VOS_UINT32 LNAS_STK_MSG_ID_ENUM_UINT32;

enum LNAS_STK_UPDATE_TYPE_ENUM
{
    LNAS_STK_UPDATE_TYPE_EPS_ATTACH  = 0x09,
    LNAS_STK_UPDATE_TYPE_COMBINED_ATTACH,
    LNAS_STK_UPDATE_TYPE_TA_UPDATEING,
    LNAS_STK_UPDATE_TYPE_COMBINED_TALA_UPDATING,
    LNAS_STK_UPDATE_TYPE_COMBINED_TALA_UPDATING_WITH_IMSI_ATTACH,
    LNAS_STK_UPDATE_TYPE_PERIODIC_UPDATING,
    LNAS_STK_UPDATE_TYPE_BUTT
} ;
typedef VOS_UINT8 LNAS_STK_UPDATE_TYPE_ENUM_UINT8 ;

/*****************************************************************************
 5. STRUCT
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           ucRsv;
}LNAS_STK_PLMN_ID_STRU;

/*****************************************************************************
�ṹ����    :LNAS_STK_TAC_STRU
ʹ��˵��    :TAC��Ϣ  24.301  9.9.3.26
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTac;
    VOS_UINT8                           ucTacCnt;
    VOS_UINT8                           aucRsv[2];
}LNAS_STK_TAC_STRU;

typedef struct
{
    LNAS_STK_PLMN_ID_STRU               stCurPlmnID;
    LNAS_STK_TAC_STRU                   stTac;
}LNAS_STK_TAI_INFO_STRU;




typedef struct
{
    LNAS_STK_UPDATE_TYPE_ENUM_UINT8         enUpdateAttachType;
    VOS_UINT8                               ucCauseCode;
    VOS_UINT16                              ucRsv;
    LNAS_STK_TAI_INFO_STRU                  stTaiInfo;
}LNAS_STK_NETWORK_REJECTION_EVENT_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                 ulMsgName;
    LNAS_STK_NETWORK_REJECTION_EVENT_INFO_STRU stNetworkRejectionEvent;
}LNAS_STK_NETWORK_REJECTION_EVENT_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/




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

#endif /* end of LNasStkInterface.h */


