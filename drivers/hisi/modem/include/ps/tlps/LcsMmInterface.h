

#ifndef __LCSMMINTERFACE_H__
#define __LCSMMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  #pragma pack(*)    设置字节对齐方式
*****************************************************************************/
/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "LPSCommon.h"
#include "MmCmInterface.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif



/*****************************************************************************
  2 Macro
*****************************************************************************/
#define PS_MSG_ID_LCS_TO_MM_BASE 0
#define PS_MSG_ID_MM_TO_LCS_BASE 100

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 枚举名    : LCS_MM_MSG_ID_ENUM_UINT32
 协议表格  :
 ASN.1描述 :
 枚举说明  : LCS与MM之间的消息枚举
*****************************************************************************/
enum    LCS_MM_MSG_ID_ENUM_UINT32
{
    /* LCS发给MM的消息原语 */
    ID_LCS_MM_EST_REQ                   = 0x01+PS_MSG_ID_SS_TO_LMM_BASE,        /* _H2ASN_MsgChoice LCS_MM_EST_REQ_STRU */
    ID_LCS_MM_DATA_REQ                  = 0x02+PS_MSG_ID_SS_TO_LMM_BASE,        /* _H2ASN_MsgChoice LCS_MM_DATA_REQ_STRU */
    ID_LCS_MM_REL_REQ                   = 0x03+PS_MSG_ID_SS_TO_LMM_BASE,        /* _H2ASN_MsgChoice LCS_MM_REL_REQ_STRU */


    /* MM发送给LCS的消息原语*/
    ID_MM_LCS_EST_CNF                   = 0x01+PS_MSG_ID_LMM_TO_SS_BASE,        /* _H2ASN_MsgChoice MM_LCS_EST_CNF_STRU */
    ID_MM_LCS_DATA_IND                  = 0x02+PS_MSG_ID_LMM_TO_SS_BASE,        /* _H2ASN_MsgChoice MM_LCS_DATA_IND_STRU */
    ID_MM_LCS_REL_IND                   = 0x03+PS_MSG_ID_LMM_TO_SS_BASE,        /* _H2ASN_MsgChoice MM_LCS_REL_IND_STRU */

    ID_LCS_MM_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 LCS_MM_MSG_ID_ENUM_UINT32;




/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 结构名称: LCS_MM_EST_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LCS请求MM建链
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_MM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulTi;
} LCS_MM_EST_REQ_STRU;

/*****************************************************************************
 结构名称: MM_LCS_EST_CNF_STRU
 协议表格:
 ASN.1 描述:
 结构说明:MM对SS的建链回复，回复此消息就以为着建链成功
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_MM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulTi;
} MM_LCS_EST_CNF_STRU;

/*****************************************************************************
 结构名    : LCS_MM_AIR_MSG_STRU
 结构说明  : LCS空口消息
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulLcsMsgSize;       /* 长度不超过256                    */
    VOS_UINT8                          aucLcsMsg[4];       /* 消息的前四个字节内容             */
    /*************************************************************************
        _H2ASN_Array2String
    *************************************************************************/
}LCS_MM_AIR_MSG_STRU;

/*****************************************************************************
 结构名称: LCS_MM_DATA_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LCS请求数据发送
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_MM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulTi;

    LCS_MM_AIR_MSG_STRU                 stLcsMsg;
} LCS_MM_DATA_REQ_STRU;

/*****************************************************************************
 结构名称: MM_LCS_DATA_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明:网侧发送的LCS空口消息
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_MM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulTi;

    LCS_MM_AIR_MSG_STRU                 stLcsMsg;
} MM_LCS_DATA_IND_STRU;

/*****************************************************************************
 结构名称: LCS_MM_REL_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明:LCS通知MM实体释放
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_MM_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulTi;
} LCS_MM_REL_REQ_STRU;


/*****************************************************************************
 结构名称: MM_LCS_REL_IND_STRU
 协议表格:
 ASN.1 描述:
 结构说明: MM通知LCS链路释放
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LMM_SS_MSG_ID_ENUM_UINT32           ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulTi;

    VOS_UINT32      			ulRelCause;
} MM_LCS_REL_IND_STRU;


/*****************************************************************************
 结构名称: LPP_LCS_GNSS_ASSISTDATA_REQ_STRU
 协议表格:
 ASN.1 描述:
 结构说明: LPP请求LCS获取GNSS辅助数据
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_LPP_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          ulLppMsgSize;       
    VOS_UINT8                           aucLppMsg[4];       /* 消息的前四个字节内容 */
}LPP_LCS_GNSS_ASSISTDATA_REQ_STRU;

/*****************************************************************************
 结构名称: LCS_LPP_GNSS_ASSISTDATA_CNF_STRU
 协议表格:
 ASN.1 描述:
 结构说明:
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    LCS_LPP_MSG_ID_ENUM_UINT32          ulMsgId;            /*_H2ASN_Skip*/

    VOS_UINT32                          ulRslt;/*0:表示成功；1：表示失败*/
}LCS_LPP_GNSS_ASSISTDATA_CNF_STRU;


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

#endif /* end of LcsMmInterface.h */


