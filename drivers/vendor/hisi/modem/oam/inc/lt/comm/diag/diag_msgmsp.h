/******************************************************************************

    Copyright(C)2014,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : diag_msgmsp.h
  Description     :
  History         :
     1.cuijunqiang       2014-10-20     Draft Enact
     2.
******************************************************************************/

#ifndef __DIAG_MSGMSP_H__
#define __DIAG_MSGMSP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "msp_errno.h"
#include  "OmCommon.h"
#include  "diag_cfg.h"
#include  "blist.h"

/*****************************************************************************
  2 macro
*****************************************************************************/

#if(VOS_OS_VER == VOS_LINUX)
#define ERR_HIDS_CORE_ERROR     ERR_MSP_DIAG_ACORE_ERROR
#else
#define ERR_HIDS_CORE_ERROR     ERR_MSP_DIAG_CCORE_ERROR
#endif

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/* 建链核间通信结构体 */
typedef struct
{
     VOS_MSG_HEADER                     /*VOS头 */
     VOS_UINT32                     ulMsgId;
     VOS_UINT32                     ulCmdId;
     DIAG_CMD_HOST_CONNECT_CNF_STRU stConnInfo;
}DIAG_MSG_MSP_CONN_STRU;


/* 核间透传通信结构体 */
typedef struct
{
     VOS_MSG_HEADER                     /*VOS头 */
     VOS_UINT32                         ulMsgId;
     DIAG_FRAME_INFO_STRU               stInfo;
}DIAG_MSG_A_TRANS_C_STRU;

/*****************************************************************************
描述 : 针对消息ID/命令ID开关,支持多个命令参数
ID   : DIAG_CMD_GTR_SET
REQ : DIAG_CMD_GTR_SET_REQ_STRU
CNF : DIAG_CMD_GTR_SET_CNF_STRU
*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulGtrDtaSize;
    VOS_UINT8 aucDta[0];
} DIAG_CMD_GTR_SET_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;          /* 原AUID*/
    VOS_UINT32 ulSn;            /* HSO分发，插件命令管理*/
    VOS_UINT32 ulRc;            /* 结果码*/
} DIAG_CMD_GTR_SET_CNF_STRU;


/*****************************************************************************
描述 : 获取modem个数
ID   : DIAG_CMD_GET_MODEM_NUM
REQ : DIAG_CMD_GET_MODEM_NUM_REQ_STRU
CNF : DIAG_CMD_GET_MODEM_NUM_CNF_STRU
*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulRsv;
} DIAG_CMD_GET_MODEM_NUM_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulAuid;
    VOS_UINT32 ulSn;
    VOS_UINT32 ulRc;
    VOS_UINT32 ulNum;
} DIAG_CMD_GET_MODEM_NUM_CNF_STRU;


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
extern VOS_UINT32 diag_ConnMsgProc(MsgBlock* pMsgBlock);
extern VOS_UINT32 diag_AppTransMspProc(MsgBlock* pMsgBlock);

extern VOS_UINT32 diag_PsProcEntry (VOS_UINT8 * pData);
extern VOS_UINT32 diag_InvalidCmdCnf(DIAG_FRAME_INFO_STRU *pData);
extern VOS_UINT32 diag_GtrProcEntry(VOS_UINT8* pstReq);
extern VOS_UINT32 diag_GuGtrProcEntry(VOS_UINT8* pstReq);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of msp_diag.h */

