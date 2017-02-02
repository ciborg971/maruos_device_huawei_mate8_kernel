/******************************************************************************

    Copyright(C)2014,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : diag_msgphy.h
  Description     :
  History         :
     1.cuijunqiang       2014-10-20     Draft Enact
     2.
******************************************************************************/

#ifndef __DIAG_MSGPHY_H__
#define __DIAG_MSGPHY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include <mdrv.h>
#include  "vos.h"
#include "msp_diag_comm.h"
#include "diag_common.h"
#include "msp_errno.h"
#if (VOS_OS_VER != VOS_LINUX)
#include "TLPhyInterface.h"
#endif


/*****************************************************************************
  2 macro
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum DIAG_SOCP_STATE_ENUM
{
    SOCP_DISABLE,       /* SOCP不可用 */
    SOCP_ENABLE,        /* SOCP可用 */
    SOCP_STATE_BUTT
};
typedef unsigned int DIAG_SOCP_STATE_ENUM_U32;

enum DIAG_LDSP_STATE_ENUM
{
    LDSP_NOT_INIT,      /* 未初始化 */
    LDSP_INITING,       /* 正在初始化 */
    LDSP_INITED,        /* 初始化完成 */
    LDSP_SOCP_ENABLE,   /* DIAG已通知LDSP SOCP可用 */
    LDSP_SOCP_DISABLE,  /* DIAG已通知LDSP SOCP不可用 */
    LDSP_STATE_BUTT
};
typedef unsigned int DIAG_LDSP_STATE_ENUM_U32;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/* 发给DSP的工具连接状态变化请求 */
typedef struct
{
    VOS_UINT32                  ulMsgId;
    VOS_UINT32                  ulOpId;
    VOS_UINT32                  ulReq;
} DIAG_MSG_TO_DSP_STRU;

/* DSP对DIAG发送邮箱消息的回复 */
typedef struct
{
    VOS_UINT32  ulMsgId;
    VOS_UINT32  ulOpId;
    VOS_UINT32  ulCnf;
} DIAG_MSG_FROM_DSP_STRU;

typedef struct
{
    VOS_MSG_HEADER
    DIAG_MSG_FROM_DSP_STRU  ulMsgData;
} DIAG_MSG_DSP_CNF_TO_AGENT_STRU;

/* 核间透传通信结构体 */
typedef struct
{
     VOS_MSG_HEADER                     /*VOS头 */
     VOS_UINT32                         ulMsgId;
     DIAG_FRAME_INFO_STRU               stInfo;
}DIAG_PHY_MSG_A_TRANS_C_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
VOS_UINT32 diag_DspMsgProc(DIAG_FRAME_INFO_STRU *pData);
VOS_UINT32 diag_AppTransPhyProc(MsgBlock* pMsgBlock);
VOS_VOID   diag_DspMsgInit(VOS_VOID);
VOS_VOID   diag_DspNotifySocpState(DIAG_SOCP_STATE_ENUM_U32 state);
VOS_VOID   diag_DspMailboxSelfTask(VOS_VOID);
VOS_VOID   diag_DspConnMsgProc(DIAG_CONNECT_CMD_ENUM_U32 connCmd);

#if (VOS_OS_VER != VOS_LINUX)
VOS_UINT32 diag_DspSendMsg(MAILBOX_SERVICE_TYPE_E serType,VOS_UINT8* pstReq ,VOS_UINT32 ulCmdId,VOS_UINT32 ulDataLen);
VOS_VOID   diag_DspMailboxCb(MAILBOX_INT_TYPE_E enIntType);
#endif
VOS_UINT32 diag_DspSocpVoteCnfMsgProc(MsgBlock * pMsgBlock);
VOS_VOID diag_DspVoteToSocp(SOCP_VOTE_TYPE_ENUM_U32 voteType);
/*****************************************************************************
  9 OTHERS
*****************************************************************************/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of  */


