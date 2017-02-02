/*
* Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
* foss@huawei.com
*
* If distributed as part of the Linux kernel, the following license terms
* apply:
*
* * This program is free software; you can redistribute it and/or modify
* * it under the terms of the GNU General Public License version 2 and
* * only version 2 as published by the Free Software Foundation.
* *
* * This program is distributed in the hope that it will be useful,
* * but WITHOUT ANY WARRANTY; without even the implied warranty of
* * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* * GNU General Public License for more details.
* *
* * You should have received a copy of the GNU General Public License
* * along with this program; if not, write to the Free Software
* * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
*
* Otherwise, the following license terms apply:
*
* * Redistribution and use in source and binary forms, with or without
* * modification, are permitted provided that the following conditions
* * are met:
* * 1) Redistributions of source code must retain the above copyright
* *    notice, this list of conditions and the following disclaimer.
* * 2) Redistributions in binary form must reproduce the above copyright
* *    notice, this list of conditions and the following disclaimer in the
* *    documentation and/or other materials provided with the distribution.
* * 3) Neither the name of Huawei nor the names of its contributors may
* *    be used to endorse or promote products derived from this software
* *    without specific prior written permission.
*
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*/

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "GuNasLogFilter.h"
#include "MnMsgApi.h"

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#include "MsgImsaInterface.h"
#include "Nasrrcinterface.h"
#endif

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#include "AtInternalMsg.h"
#include "AtParse.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_GU_NAS_LOG_FILTER_C

#define    AT_CMD_LEN_7             (7)
#define    AT_CMD_LEN_8             (8)
#define    AT_CMD_LEN_13            (13)
#define    AT_SMS_MODE              (1)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
typedef VOS_UINT32 (*pGuNasSmsMsgFilterProcFunc)(
    PS_MSG_HEADER_STRU      *pstMsg
);

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
extern VOS_UINT32 GUNAS_GetSmsFilterFlg( VOS_VOID );
#endif

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
extern VOS_UINT8 AT_GetSmsFilterEnableFlg(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT32 PAM_OM_USIMMATFilter(
    VOS_UINT8                           *pucATData);
#endif

/*******************************************************************************
 结构名    : NAS_MNTN_SMS_MSG_FILTER_PROC_TBL_FUNC
 结构说明  : 短信过滤消息处理函数结构体
 1.日    期   : 2015年09月25日
   作    者   : h00313353
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulSenderPid;
    VOS_UINT32                                  ulReceiverPid;
    pGuNasSmsMsgFilterProcFunc                  pFuncSmsFilterProc;
} GUNAS_SMS_MSG_FILTER_PROC_TBL_FUNC;

GUNAS_SMS_MSG_FILTER_PROC_TBL_FUNC              g_astGuNasSmsMsgFilterProcFuncTbl[] =
{
#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    {WUEPS_PID_AT,          WUEPS_PID_AT,       GUNAS_SMS_FilterAtToAtMsg},
#endif

    {WUEPS_PID_TAF,         WUEPS_PID_AT,       GUNAS_SMS_FilterTafToAtMsg},
    {WUEPS_PID_AT,          WUEPS_PID_TAF,      GUNAS_SMS_FilterAtToTafMsg},

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    {PS_PID_IMSA,           WUEPS_PID_TAF,      GUNAS_SMS_FilterImsaToTafMsg},
    {WUEPS_PID_WRR,         WUEPS_PID_GMM,      GUNAS_SMS_FilterWrrToGmmMmMsg},
    {WUEPS_PID_WRR,         WUEPS_PID_MM,       GUNAS_SMS_FilterWrrToGmmMmMsg},
    {UEPS_PID_GAS,          WUEPS_PID_MM,       GUNAS_SMS_FilterGasToMmMsg},
#endif
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
/*****************************************************************************
 函 数 名  : GUNAS_SMS_FilterImsaToTafMsg
 功能描述  : 过滤Imsa到Taf短信层间消息的函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_SMS_FilterImsaToTafMsg(
    PS_MSG_HEADER_STRU                 *pstMsg
)
{
    if ((ID_IMSA_MSG_DATA_IND   == pstMsg->ulMsgName)
     || (ID_IMSA_MSG_REPORT_IND == pstMsg->ulMsgName))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : GUNAS_SMS_FilterWrrToGmmMmMsg
 功能描述  : 过滤Wrr到GMM或MM短信层间消息的函数
 输入参数  : pstMsg    -- 消息指针
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_SMS_FilterWrrToGmmMmMsg(
    PS_MSG_HEADER_STRU                 *pstMsg
)
{
    VOS_UINT8                           ucPd;

    ucPd                                = 0;

    if (RRMM_DATA_IND   != pstMsg->ulMsgName)
    {
        return VOS_FALSE;
    }

    if (VOS_OK != NAS_MM_GetL3RcvMsgPd((RRMM_DATA_IND_STRU *)pstMsg, &ucPd))
    {
        return VOS_FALSE;
    }

    if (NAS_SMS_PD == ucPd)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : GUNAS_SMS_FilterGasToMmMsg
 功能描述  : 过滤Gas短信到MM的消息层间消息的函数
 输入参数  : pstMsg -- 消息指针
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_SMS_FilterGasToMmMsg(
    PS_MSG_HEADER_STRU                 *pstMsg
)
{
    VOS_UINT8                           ucPd;

    ucPd                                = 0;

    if (RRMM_DATA_IND   != pstMsg->ulMsgName)
    {
        return VOS_FALSE;
    }

    if (VOS_OK != NAS_MM_GetL3RcvMsgPd((RRMM_DATA_IND_STRU *)pstMsg, &ucPd))
    {
        return VOS_FALSE;
    }

    if (NAS_SMS_PD == ucPd)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
/*****************************************************************************
 函 数 名  : GUNAS_SMS_FilterAtToAtMsg
 功能描述  : 过滤At到At短信层间消息的函数
 输入参数  : pstMsg     -- 消息指针
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_SMS_FilterAtToAtMsg(
    PS_MSG_HEADER_STRU                 *pstMsg
)
{
    /* AT+CMGS */
    VOS_UINT8                           aucCMGSMsg[AT_CMD_LEN_7]  = {0x41, 0x54, 0x2B, 0x43, 0x4D, 0x47, 0x53};
    /* AT+CMGW */
    VOS_UINT8                           aucCMGWMsg[AT_CMD_LEN_7]  = {0x41, 0x54, 0x2B, 0x43, 0x4D, 0x47, 0x57};
    /* AT+CMGC */
    VOS_UINT8                           aucCMGCMsg[AT_CMD_LEN_7]  = {0x41, 0x54, 0x2B, 0x43, 0x4D, 0x47, 0x43};
    /* +CMT */
    VOS_UINT8                           aucCMTRpt[AT_CMD_LEN_7]   = {0x0D, 0x0A, 0x2B, 0x43, 0x4D, 0x54, 0x3A};
    /* +CMGR */
    VOS_UINT8                           aucCMGRRpt[AT_CMD_LEN_8]  = {0x0D, 0x0A, 0x2B, 0x43, 0x4D, 0x47, 0x52, 0x3A};
    /* ^RSTRIGGER */
    VOS_UINT8                           aucRSTRIGGERRpt[AT_CMD_LEN_13]  = {0x0D, 0x0A, 0x5E, 0x52, 0x53, 0x54, 0x52, 0x49, 0x47, 0x47, 0x45, 0x52, 0x3A};
    /* +CMGS */
    VOS_UINT8                           aucCMGSRpt[AT_CMD_LEN_8]  = {0x0D, 0x0A, 0x2B, 0x43, 0x4D, 0x47, 0x53, 0x3A};
    /* +CDS */
    VOS_UINT8                           aucCDSRpt[AT_CMD_LEN_7]   = {0x0D, 0x0A, 0x2B, 0x43, 0x44, 0x53, 0x3A};
    VOS_UINT8                          *pucTmpAdr                 = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;
    VOS_UINT8                           aucTmpVal[AT_CMD_LEN_8];

    ulLen                               = 0;
    PS_MEM_SET(aucTmpVal, 0x00, sizeof(aucTmpVal));

    switch (pstMsg->ulMsgName)
    {
        case ID_AT_MNTN_INPUT_MSC:
        case ID_AT_MNTN_OUTPUT_MSC:
        case ID_AT_MNTN_START_FLOW_CTRL:
        case ID_AT_MNTN_STOP_FLOW_CTRL:
        case ID_AT_MNTN_REG_FC_POINT:
        case ID_AT_MNTN_DEREG_FC_POINT:
        case ID_AT_MNTN_PC_REPLAY_MSG:
        case ID_AT_MNTN_PC_REPLAY_CLIENT_TAB:
        case ID_AT_MNTN_RPT_PORT:
            return VOS_FALSE;

        default:
        {
            if (AT_SMS_MODE == g_stParseContext[((AT_MSG_STRU *)pstMsg)->ucIndex].ucMode)
            {
                /* 短信模式直接进行过滤 */
                return VOS_TRUE;
            }

            pucTmpAdr                   = (VOS_UINT8 *)((VOS_UINT8 *)pstMsg
                                                        + sizeof(AT_MSG_STRU)
                                                        - sizeof(((AT_MSG_STRU *)pstMsg)->aucValue));

            ulLen                       = ((AT_MSG_STRU *)pstMsg)->usLen;

            if (ulLen < AT_CMD_LEN_8)
            {
                return VOS_FALSE;
            }

            PS_MEM_CPY(aucTmpVal, pucTmpAdr, AT_CMD_LEN_8);

            (VOS_VOID)At_UpString(aucTmpVal, AT_CMD_LEN_8);
            if (0 == PS_MEM_CMP(aucCMGSMsg, aucTmpVal, sizeof(aucCMGSMsg)))
            {
                return VOS_TRUE;
            }

            if (0 == PS_MEM_CMP(aucCMGWMsg, aucTmpVal, sizeof(aucCMGWMsg)))
            {
                return VOS_TRUE;
            }

            if (0 == PS_MEM_CMP(aucCMGCMsg, aucTmpVal, sizeof(aucCMGCMsg)))
            {
                return VOS_TRUE;
            }

            if (0 == PS_MEM_CMP(aucCMTRpt, pucTmpAdr, sizeof(aucCMTRpt)))
            {
                return VOS_TRUE;
            }

            if (0 == PS_MEM_CMP(aucCMGRRpt, pucTmpAdr, sizeof(aucCMGRRpt)))
            {
                return VOS_TRUE;
            }

            if (0 == PS_MEM_CMP(aucCMGSRpt, pucTmpAdr, sizeof(aucCMGSRpt)))
            {
                return VOS_TRUE;
            }

            if (0 == PS_MEM_CMP(aucCDSRpt, pucTmpAdr, sizeof(aucCDSRpt)))
            {
                return VOS_TRUE;
            }

            if (ulLen < AT_CMD_LEN_13)
            {
                return VOS_FALSE;
            }

            if (0 == PS_MEM_CMP(aucRSTRIGGERRpt, pucTmpAdr, sizeof(aucRSTRIGGERRpt)))
            {
                return VOS_TRUE;
            }

            if (VOS_TRUE == PAM_OM_USIMMATFilter(pucTmpAdr))
            {
                return VOS_TRUE;
            }

            return VOS_FALSE;
        }
    }
}
#endif

/*****************************************************************************
 函 数 名  : GUNAS_SMS_FilterAtToTafMsg
 功能描述  : 过滤At到Taf短信层间消息的函数
 输入参数  : pstMsg -- 消息内容
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_SMS_FilterAtToTafMsg(
    PS_MSG_HEADER_STRU                 *pstMsg
)
{
    switch (pstMsg->ulMsgName)
    {
        case MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT:
        case MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM:
        case MN_MSG_MSGTYPE_WRITE:
        case MN_MSG_MSGTYPE_READ:
        case MN_MSG_MSGTYPE_LIST:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : GUNAS_SMS_FilterTafToAtMsg
 功能描述  : 过滤Taf到At短信层间消息的函数
 输入参数  : pstMsg     -- 消息指针
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_SMS_FilterTafToAtMsg(
    PS_MSG_HEADER_STRU                 *pstMsg
)
{
    VOS_UINT32                          ulEventType;

    ulEventType = 0;

    if (MN_CALLBACK_MSG   != pstMsg->ulMsgName)
    {
        return VOS_FALSE;
    }

    PS_MEM_CPY(&ulEventType, ((MN_AT_IND_EVT_STRU *)pstMsg)->aucContent, sizeof(VOS_UINT32));

    switch ((MN_MSG_EVENT_ENUM_U32)ulEventType)
    {
        case MN_MSG_EVT_SUBMIT_RPT:
        case MN_MSG_EVT_MSG_SENT:
        case MN_MSG_EVT_DELIVER:
        case MN_MSG_EVT_READ:
        case MN_MSG_EVT_LIST:
        case MN_MSG_EVT_WRITE:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : GUNAS_SMS_FilterLayerMsg
 功能描述  : 过滤短信层间消息的函数
 输入参数  : pstMsg     -- 消息指针
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_SMS_FilterLayerMsg(
    const VOS_VOID                     *pstMsg
)
{
    PS_MSG_HEADER_STRU                 *pstTempMsg = VOS_NULL_PTR;
    pGuNasSmsMsgFilterProcFunc          pfunSmsFilter;
    VOS_UINT32                          i;

    pstTempMsg      = (PS_MSG_HEADER_STRU *)pstMsg;
    pfunSmsFilter   = VOS_NULL_PTR;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    if (VOS_FALSE == AT_GetSmsFilterEnableFlg(0))
    {
        return VOS_FALSE;
    }
#endif

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    if (VOS_FALSE == GUNAS_GetSmsFilterFlg())
    {
        return VOS_FALSE;
    }

    /* SMS消息过滤 */
    if ((WUEPS_PID_SMS == pstTempMsg->ulSenderPid)
     || (WUEPS_PID_SMS == pstTempMsg->ulReceiverPid))
    {
        return VOS_TRUE;
    }
#endif

    for (i = 0; i < (sizeof(g_astGuNasSmsMsgFilterProcFuncTbl)/sizeof(GUNAS_SMS_MSG_FILTER_PROC_TBL_FUNC)); i++)
    {
        if ((pstTempMsg->ulSenderPid    == g_astGuNasSmsMsgFilterProcFuncTbl[i].ulSenderPid)
         && (pstTempMsg->ulReceiverPid  == g_astGuNasSmsMsgFilterProcFuncTbl[i].ulReceiverPid))
        {
            pfunSmsFilter = g_astGuNasSmsMsgFilterProcFuncTbl[i].pFuncSmsFilterProc;
            break;
        }
    }

    if (VOS_NULL_PTR != pfunSmsFilter)
    {
        return pfunSmsFilter(pstTempMsg);
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : GUNAS_OM_LayerMsgFilter
 功能描述  : GUNAS用于过滤层间消息的函数
 输入参数  : pstMsg     -- 消息指针
 输出参数  : NONE
 返 回 值  : VOS_TRUE :表示这个消息被过滤掉了，不需要上报给OM
             VOS_FALSE:表示这个消息需要上报OM
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月17日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 GUNAS_OM_LayerMsgFilter(
    const VOS_VOID                     *pstMsg
)
{
    /* 短信层间消息过滤 */
    if (VOS_TRUE == GUNAS_SMS_FilterLayerMsg(pstMsg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
