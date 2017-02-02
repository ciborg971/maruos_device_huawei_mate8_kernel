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
#include "AtCmdCagpsProc.h"
#include "AtEventReport.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_AT_CMDCAGPSPROC_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

AT_CAGPS_CMD_NAME_TLB_STRU  g_astAtCagpsCmdNameTlb[] =
{
    {ID_XPDS_AT_GPS_TIME_INFO_IND,         0,             "^CAGPSTIMEINFO"},
    {ID_XPDS_AT_GPS_REFLOC_INFO_CNF,       0,             "^CAGPSREFLOCINFO"},
    {ID_XPDS_AT_GPS_PDE_POSI_INFO_IND,     0,             "^CAGPSPOSINFO"},
    {ID_XPDS_AT_GPS_NI_SESSION_IND,        0,             "^CAGPSNIREQ"},
    {ID_XPDS_AT_GPS_START_REQ,             0,             "^CAGPSSTARTREQ"},
    {ID_XPDS_AT_GPS_CANCEL_IND,            0,             "^CAGPSCANCELIND"},
    {ID_XPDS_AT_GPS_ACQ_ASSIST_DATA_IND,   0,             "^CAGPSACQASSISTINFO"},
    {ID_XPDS_AT_GPS_ABORT_IND,             0,             "^CAGPSABORT"},
    /* Added by y00346957 for CDMA Iteration 14 2015-7-22 begin */
    {ID_XPDS_AT_GPS_ION_INFO_IND,          0,             "^CAGPSIONINFO"},
    {ID_XPDS_AT_GPS_EPH_INFO_IND,          0,             "^CAGPSEPHINFO"},
    {ID_XPDS_AT_GPS_DEL_ASSIST_DATA_IND,   0,             "^CAGPSDELASSISTDATAIND"},
    /* Added by y00346957 for CDMA Iteration 14 2015-7-22 end */

    /* Added by x00314862 for CDMA Iteration 14 2015-7-23 begin */
    {ID_XPDS_AT_GPS_ALM_INFO_IND,          0,             "^CAGPSALMINFO"},
    /* Added by x00314862 for CDMA Iteration 14 2015-7-23 end */

    /* Added by A00903922 for AGPS IT2 2015-9-08 begin */
    {ID_XPDS_AT_GPS_NI_CP_START,           0,             "^CAGPSNICPSTART"},
    {ID_XPDS_AT_GPS_NI_CP_STOP,            0,             "^CAGPSNICPSTOP"},
    /* Added by A00903922 for AGPS IT2 2015-9-08 end */
};

AT_CAGPS_CMD_OPT_TLB_STRU  g_astAtCagpsCmdOptTbl[] =
{
    {ID_XPDS_AT_GPS_START_CNF,             AT_CMD_CAGPSSTART_SET},
    {ID_XPDS_AT_GPS_CFG_MPC_ADDR_CNF,      AT_CMD_CAGPSCFGMPCADDR_SET},
    {ID_XPDS_AT_GPS_CFG_PDE_ADDR_CNF,      AT_CMD_CAGPSCFGPDEADDR_SET},
    {ID_XPDS_AT_GPS_CFG_MODE_CNF,          AT_CMD_CAGPSCFGPOSMODE_SET},
    {ID_XPDS_AT_GPS_STOP_CNF,              AT_CMD_CAGPSSTOP_SET},
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/


/*****************************************************************************
 函 数 名  : At_SetAgpsDataCallStatus
 功能描述  : ^CAGPSDATACALLSTATUS
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月11日
    作    者   : zhuli
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 At_SetAgpsDataCallStatus(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    AT_XPDS_AP_DATA_CALL_STATUS_IND_STRU stDataCallInd;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 参数过多 */
    if (gucAtParaIndex > 1)
    {
        return AT_TOO_MANY_PARA;
    }

    if (gastAtParaList[0].ulParaValue >= AT_XPDS_DATA_CALL_STATUS_BUTT)
    {
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    stDataCallInd.enChannelState= gastAtParaList[0].ulParaValue;

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   ID_AT_XPDS_AP_DATA_CALL_STATUS_IND,
                                   (VOS_VOID*)&stDataCallInd,
                                   sizeof(stDataCallInd),
                                   I0_UEPS_PID_XPDS);

    if (AT_SUCCESS == ulRst)
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : At_SetAgpsUpBindStatus
 功能描述  : ^CUPBINDSTATUS
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月11日
    作    者   : zhuli
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 At_SetAgpsUpBindStatus(
    VOS_UINT8                               ucIndex
)
{
    VOS_UINT32                                              ulRst;
    AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU                  stUpBindInd;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 参数过多 */
    if (gucAtParaIndex > 2)
    {
        return AT_TOO_MANY_PARA;
    }

    if ((gastAtParaList[0].ulParaValue >= AT_XPDS_SERVER_MODE_BUTT)
        ||(gastAtParaList[1].ulParaValue >= AT_XPDS_SERVER_BIND_STATUS_BUTT))
    {
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    stUpBindInd.enServerMode = gastAtParaList[0].ulParaValue;
    stUpBindInd.enBindStatus = gastAtParaList[1].ulParaValue;

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   ID_AT_XPDS_AP_SERVER_BIND_STATUS_IND,
                                   (VOS_VOID*)&stUpBindInd,
                                   sizeof(stUpBindInd),
                                   I0_UEPS_PID_XPDS);

    if (AT_SUCCESS == ulRst)
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : At_SetAgpsForwardData
 功能描述  : ^CAGPSFORWARDDATA
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月11日
    作    者   : zhuli
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 At_SetAgpsForwardData(
    VOS_UINT8                               ucIndex
)
{
    VOS_UINT32                          ulRst;
    VOS_UINT32                          ulDataLen;
    AT_XPDS_AP_FORWARD_DATA_IND_STRU       *pstDownDataInd;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* 参数过多 */
    if (gucAtParaIndex > 5)
    {
        return AT_TOO_MANY_PARA;
    }

    if ((gastAtParaList[0].ulParaValue >= AT_XPDS_SERVER_MODE_BUTT)
        ||(gastAtParaList[2].ulParaValue > gastAtParaList[1].ulParaValue))
    {
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    if (1 == (gastAtParaList[3].ulParaValue % 2))
    {
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    ulDataLen = (gastAtParaList[3].ulParaValue / 2);

    pstDownDataInd = (AT_XPDS_AP_FORWARD_DATA_IND_STRU*)VOS_MemAlloc(
                                            WUEPS_PID_AT,
                                            DYNAMIC_MEM_PT,
                                            sizeof(AT_XPDS_AP_FORWARD_DATA_IND_STRU)+ulDataLen );

    pstDownDataInd->enServerMode    = gastAtParaList[0].ulParaValue;
    pstDownDataInd->ulTotalNum      = gastAtParaList[1].ulParaValue;
    pstDownDataInd->ulCurNum        = gastAtParaList[2].ulParaValue;
    pstDownDataInd->ulDataLen       = ulDataLen;

    if (AT_SUCCESS !=  At_AsciiString2HexSimple(pstDownDataInd->aucData,
                                                gastAtParaList[4].aucPara,
                                                (VOS_UINT16)gastAtParaList[3].ulParaValue))
    {
        VOS_MemFree(WUEPS_PID_AT, pstDownDataInd);

        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   ID_AT_XPDS_AP_FORWARD_DATA_IND,
                                   (VOS_VOID*)pstDownDataInd,
                                   sizeof(AT_XPDS_AP_FORWARD_DATA_IND_STRU)+ulDataLen,
                                   I0_UEPS_PID_XPDS);

    if (AT_SUCCESS == ulRst)
    {
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 函 数 名  : AT_RcvXpdsAgpsDataCallReq
 功能描述  : ID_XPDS_AT_AP_DATA_CALL_REQ 消息处理 ^CAGPSDATACALLREQ
 输入参数  : 消息内容
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月11日
    作    者   : zhuli
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvXpdsAgpsDataCallReq(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_XPDS_MSG_STRU                   *pstRcvMsg;
    XPDS_AT_AP_DATA_CALL_REQ_STRU      *pstCallInd;

    /* 初始化 */
    pstRcvMsg   = (AT_XPDS_MSG_STRU*)pstMsg;
    pstCallInd  = (XPDS_AT_AP_DATA_CALL_REQ_STRU *)pstRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsAgpsDataCallReq: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      "%s^CAGPSDATACALLREQ: %d,%d%s",
                                      gaucAtCrLf,
                                      pstCallInd->enAgpsMode,
                                      pstCallInd->enAgpsOper,
                                      gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : AT_RcvXpdsAgpsServerBindReq
 功能描述  : ID_MTA_AT_AGPS_BINDUPREQ_IND 消息处理 ^CBINDUPREQ
 输入参数  : 消息内容
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月11日
    作    者   : zhuli
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvXpdsAgpsServerBindReq(
    VOS_VOID                            *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_XPDS_MSG_STRU                    *pstRcvMsg;
    XPDS_AT_AP_SERVER_BIND_REQ_STRU    *pstBindupInd;

    /* 初始化 */
    pstRcvMsg       = (AT_XPDS_MSG_STRU*)pstMsg;
    pstBindupInd    = (XPDS_AT_AP_SERVER_BIND_REQ_STRU *)pstRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsAgpsServerBindReq: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      "%s^CAGPSBINDCONN: %d,%d,%08x,%d%s",
                                      gaucAtCrLf,
                                      pstBindupInd->enServerMode,
                                      pstBindupInd->enDataCallCtrl,
                                      pstBindupInd->ulIpAddr,
                                      pstBindupInd->ulPortNum,
                                      gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


/*****************************************************************************
 函 数 名  : AT_RcvXpdsAgpsReverseDataInd
 功能描述  : ID_MTA_AT_AGPS_UPDATA_IND 消息处理 ^CAGPSREVERSEDATA
 输入参数  : 消息内容
 输出参数  : 无
 返 回 值  : AT_XXX
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月11日
    作    者   : zhuli
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_RcvXpdsAgpsReverseDataInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_XPDS_MSG_STRU                    *pstRcvMsg;
    XPDS_AT_AP_REVERSE_DATA_IND_STRU   *pstUpdataInd;
    VOS_UINT32                          ulCurNum;
    VOS_UINT32                          ulTotalNum;
    VOS_UINT32                          ulOffset;
    VOS_UINT8                          *pucSrc;
    VOS_UINT32                          ulOutputLen;
    VOS_UINT32                          ulRemainLen;
    VOS_UINT16                          usLength;

    /* 初始化 */
    pstRcvMsg       = (AT_XPDS_MSG_STRU*)pstMsg;
    pstUpdataInd    = (XPDS_AT_AP_REVERSE_DATA_IND_STRU *)pstRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsAgpsReverseDataInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    ulTotalNum = (pstUpdataInd->ulDataLen / AT_XPDS_AGPS_DATAUPLEN_MAX);

    if (0 != (pstUpdataInd->ulDataLen % AT_XPDS_AGPS_DATAUPLEN_MAX))
    {
        ulTotalNum++;
    }

    if (VOS_NULL_WORD <= ulTotalNum)
    {
        AT_WARN_LOG("AT_RcvXpdsAgpsReverseDataInd: Data Len Error.");
        return VOS_ERR;
    }

    ulOffset = 0;

    pucSrc = pstUpdataInd->aucData;

    ulOutputLen = 0;

    ulRemainLen = pstUpdataInd->ulDataLen;

    for (ulCurNum = 1; ulCurNum <= ulTotalNum; ulCurNum++)
    {
        if (ulRemainLen <= AT_XPDS_AGPS_DATAUPLEN_MAX)
        {
            ulOutputLen = ulRemainLen;
        }
        else
        {
            ulOutputLen = AT_XPDS_AGPS_DATAUPLEN_MAX;

            ulRemainLen -= AT_XPDS_AGPS_DATAUPLEN_MAX;
        }

        usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          "%s^CAGPSREVERSEDATA: %d,%d,%d,%d,",
                                          gaucAtCrLf,
                                          pstUpdataInd->enServerMode,
                                          ulTotalNum,
                                          ulCurNum,
                                          ulOutputLen*2);

        /* 将16进制数转换为ASCII码后输入主动命令内容 */
        usLength += (TAF_UINT16)At_HexText2AsciiStringSimple(AT_CMD_MAX_LEN,
                                                            (TAF_INT8 *)pgucAtSndCodeAddr,
                                                            (TAF_UINT8 *)pgucAtSndCodeAddr+usLength,
                                                            ulOutputLen,
                                                            (pucSrc+ulOffset));

        usLength  += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                          "%s",
                                          gaucAtCrLf);

        ulOffset += AT_XPDS_AGPS_DATAUPLEN_MAX;

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
    }

    return VOS_OK;
}
VOS_UINT32 AT_CagpsSndXpdsReq(
    VOS_UINT8                           ucIndex,
    AT_XPDS_MSG_TYPE_ENUM_UINT32        enMsgType,
    VOS_UINT32                          ulDataLen
)
{
    VOS_UINT32                          ulRst;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数过多 */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 字符串长度不正确 */
    if (gastAtParaList[0].ulParaValue != gastAtParaList[1].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 将字符串转换为16进制数组 */
    if (AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[1].aucPara, &gastAtParaList[1].usParaLen))
    {
        AT_ERR_LOG1("AT_CagpsSndXpdsReq: At_AsciiNum2HexString fail.", enMsgType);

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 消息内容长度是否正确 */
    if (ulDataLen != gastAtParaList[1].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   (VOS_UINT16)enMsgType,
                                   gastAtParaList[1].aucPara,
                                   gastAtParaList[1].usParaLen,
                                   I0_UEPS_PID_XPDS);

    if (TAF_SUCCESS == ulRst)
    {
        return AT_OK;
    }

    return AT_ERROR;
}
VOS_UINT32 AT_SetCagpsCfgPosMode(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulResult;

    ulResult = AT_CagpsSndXpdsReq(ucIndex,
                                 ID_AT_XPDS_GPS_CFG_POSITION_MODE_REQ,
                                 sizeof(AT_XPDS_GPS_CFG_POSITION_MODE_REQ_STRU));

    if (AT_OK == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CAGPSCFGPOSMODE_SET;

        return AT_WAIT_ASYNC_RETURN;
    }

    return ulResult;
}


VOS_UINT32 AT_SetCagpsStart(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulResult;

    ulResult = AT_CagpsSndXpdsReq(ucIndex,
                                 ID_AT_XPDS_GPS_START_REQ,
                                 sizeof(AT_XPDS_GPS_START_REQ_STRU));

    if (AT_OK == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CAGPSSTART_SET;

        return AT_WAIT_ASYNC_RETURN;
    }

    return ulResult;
}


VOS_UINT32 AT_SetCagpsStop(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRst;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_XPDS_GPS_STOP_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_XPDS);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CAGPSSTOP_SET;

        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
VOS_UINT32 AT_SetCagpsCfgMpcAddr(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulResult;

    ulResult = AT_CagpsSndXpdsReq(ucIndex,
                                 ID_AT_XPDS_GPS_CFG_MPC_ADDR_REQ,
                                 sizeof(AT_XPDS_GPS_CFG_MPC_ADDR_REQ_STRU));

    if (AT_OK == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CAGPSCFGMPCADDR_SET;

        return AT_WAIT_ASYNC_RETURN;
    }

    return ulResult;
}


VOS_UINT32 AT_SetCagpsCfgPdeAddr(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulResult;

    ulResult = AT_CagpsSndXpdsReq(ucIndex,
                                 ID_AT_XPDS_GPS_CFG_PDE_ADDR_REQ,
                                 sizeof(AT_XPDS_GPS_CFG_PDE_ADDR_REQ_STRU));

    if (AT_OK == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CAGPSCFGPDEADDR_SET;

        return AT_WAIT_ASYNC_RETURN;
    }

    return ulResult;
}


VOS_UINT32 AT_SetCagpsQryRefloc(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRst;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_XPDS_GPS_QRY_REFLOC_INFO_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_XPDS);

    if (TAF_SUCCESS == ulRst)
    {
        return AT_OK;
    }

    return AT_ERROR;
}
VOS_UINT32 AT_SetCagpsQryTime(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRst;

    /* 参数检查 */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 参数过多 */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 将字符串转换为16进制数组 */
    if (AT_FAILURE == At_AsciiNum2HexString(gastAtParaList[1].aucPara, &gastAtParaList[1].usParaLen))
    {
        AT_ERR_LOG("AT_SetCagpsQryTime: At_AsciiNum2HexString fail.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 消息内容长度是否正确 */
    if (sizeof(VOS_UINT32) != gastAtParaList[1].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* 按照方案要求，1:reply time sync info；2:reply time sync info and GPS assist data */
    if ((0 == gastAtParaList[1].aucPara[0])
        || (AT_XPDS_REPLY_SYNC_BUTT <= gastAtParaList[1].aucPara[0]))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_XPDS_GPS_QRY_TIME_INFO_REQ,
                                   gastAtParaList[1].aucPara,
                                   gastAtParaList[1].usParaLen,
                                   I0_UEPS_PID_XPDS);

    if (TAF_SUCCESS == ulRst)
    {
        return AT_OK;
    }

    return AT_ERROR;
}
VOS_UINT32 AT_SetCagpsPrmInfo(
    VOS_UINT8                           ucIndex
)
{
    return AT_CagpsSndXpdsReq(ucIndex,
                             ID_AT_XPDS_GPS_PRM_INFO_RSP,
                             sizeof(AT_XPDS_GPS_PRM_INFO_RSP_STRU));
}


VOS_UINT32 AT_SetCagpsReplyNiReq(
    VOS_UINT8                           ucIndex
)
{
    return AT_CagpsSndXpdsReq(ucIndex,
                             ID_AT_XPDS_GPS_REPLY_NI_REQ,
                             sizeof(AT_XPDS_GPS_REPLY_NI_RSP_STRU));
}


VOS_CHAR* AT_SearchCagpsATCmd(
    AT_XPDS_MSG_TYPE_ENUM_UINT32        enMsgType
)
{
    VOS_UINT32                          i;

    for (i = 0; i < sizeof(g_astAtCagpsCmdNameTlb)/sizeof(AT_CAGPS_CMD_NAME_TLB_STRU); i++)
    {
        if (enMsgType == g_astAtCagpsCmdNameTlb[i].enMsgType)
        {
            return g_astAtCagpsCmdNameTlb[i].pcATCmd;
        }
    }

    return "UNKOWN-MSG";
}

/* Added by x00314862 for CDMA Iteration 14 2015-7-23 begin */
/*****************************************************************************
 函 数 名  : At_SetCagpsPosInfo
 功能描述  : ^CAGPSPOSINFO 用于GPS 给moderm发送pos info
             ^CAGPSPOSINFO=<data_length>,<data>
 输入参数  : ucIndex - 端口索引
 输出参数  : 无
 返 回 值  : AT_OK 成功；AT_ERROR 失败
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月16日
    作    者   : x00314862
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 At_SetCagpsPosInfo(
    VOS_UINT8                           ucIndex
)
{
    if (AT_OK == AT_CagpsSndXpdsReq(ucIndex,
                                   ID_AT_XPDS_GPS_POS_INFO_RSP,
                                   sizeof(AT_XPDS_GPS_POS_INFO_RSP_STRU)))
    {
        return AT_OK;
    }

    return AT_ERROR;
}

/* Added by x00314862 for CDMA Iteration 14 2015-7-23 end */

VOS_UINT32 AT_RcvXpdsCagpsCnf(
    VOS_VOID                           *pMsg
)
{
    AT_XPDS_MSG_STRU                   *pstRcvMsg       = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulContentLen;
    VOS_UINT16                          usLength        = 0;

    /* 初始化 */
    pstRcvMsg           = (AT_XPDS_MSG_STRU *)pMsg;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsCagpsCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr, (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s%s", gaucAtCrLf, AT_SearchCagpsATCmd(pstRcvMsg->ulMsgId));

    /* 获取消息内容长度 */
    ulContentLen = pstRcvMsg->ulLength - (sizeof(pstRcvMsg->ulMsgId) + sizeof(AT_APPCTRL_STRU));

    if (ulContentLen != 0)
    {
         /* <length>, */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr, (TAF_CHAR *)pgucAtSndCodeAddr + usLength,": %d,\"", ulContentLen * 2);

        /* <command>, */
        usLength += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, (TAF_UINT8 *)pgucAtSndCodeAddr + usLength, pstRcvMsg->aucContent, (TAF_UINT16)ulContentLen);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%s", gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}
AT_CMD_CURRENT_OPT_ENUM AT_SearchCagpsATCmdOpt(
    AT_XPDS_MSG_TYPE_ENUM_UINT32        enMsgType
)
{
    VOS_UINT32                          i;

    for (i = 0; i < sizeof(g_astAtCagpsCmdOptTbl)/sizeof(AT_CAGPS_CMD_OPT_TLB_STRU); i++)
    {
        if (enMsgType == g_astAtCagpsCmdOptTbl[i].enMsgType)
        {
            return g_astAtCagpsCmdOptTbl[i].enCmdOpt;
        }
    }

    return AT_CMD_CURRENT_OPT_BUTT;
}


VOS_UINT32 AT_RcvXpdsCagpsRlstCnf(
    VOS_VOID                           *pMsg
)
{
    AT_XPDS_MSG_STRU                            *pstRcvMsg       = VOS_NULL_PTR;
    XPDS_AT_RESULT_CNF_STRU                     *pstMtaCnf       = VOS_NULL_PTR;
    VOS_UINT32                                  ulResult;
    VOS_UINT8                                   ucIndex;
    AT_CMD_CURRENT_OPT_ENUM                     enCmdOpt;

    /* 初始化 */
    pstRcvMsg           = (AT_XPDS_MSG_STRU *)pMsg;
    pstMtaCnf           = (XPDS_AT_RESULT_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsCagpsRlstCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    enCmdOpt = AT_SearchCagpsATCmdOpt(pstRcvMsg->ulMsgId);

    /* 当前AT是否在等待该命令返回 */
    if (enCmdOpt != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvXpdsCagpsRlstCnf : Current Option is not correct.");
        return VOS_ERR;
    }

    /* 复位AT状态 */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstMtaCnf->enResult)
    {
        ulResult = AT_ERROR;
    }

    /* 输出结果 */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
VOS_UINT32 AT_RcvXpdsEphInfoInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_XPDS_MSG_STRU                   *pstRcvMsg;
    XPDS_AT_GPS_EPH_INFO_IND_STRU      *pstEphInfoInd;
    VOS_UINT16                          usAtCmdLength;
    VOS_UINT32                          ulEphDataStrLen;
    VOS_UINT32                          ulEphDataByteOffset;
    VOS_UINT8                          *pucEphData;
    VOS_UINT8                           ucLoop;

    /* 初始化 */
    pstRcvMsg     = (AT_XPDS_MSG_STRU*)pstMsg;
    pstEphInfoInd = (XPDS_AT_GPS_EPH_INFO_IND_STRU *)pstRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsEphInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsEphInfoInd: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    pucEphData = (VOS_UINT8 *)pstEphInfoInd;

    ulEphDataStrLen = AT_AGPS_EPH_INFO_FIRST_SEG_STR_LEN;

    /* 第1包数据 */
    usAtCmdLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "%s^CAGPSEPHINFO: %d,%d,%d,",
                                            gaucAtCrLf,
                                            AT_AGPS_EPH_INFO_MAX_SEG_NUM,
                                            0,
                                            ulEphDataStrLen);

    /* 第1包数据 */
    /* 将16进制数转换为ASCII码后输入主动命令内容 */
    usAtCmdLength += (TAF_UINT16)At_HexText2AsciiStringSimple(AT_CMD_MAX_LEN,
                                            (TAF_INT8 *)pgucAtSndCodeAddr,
                                            ((TAF_UINT8 *)pgucAtSndCodeAddr) + usAtCmdLength,
                                            ulEphDataStrLen / 2,
                                            pucEphData);

    usAtCmdLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usAtCmdLength,
                                            "%s", gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usAtCmdLength);

    ulEphDataByteOffset = ulEphDataStrLen / 2;

    /* 从第2包到第5包的数据 */
    for (ucLoop = 0; ucLoop < AT_AGPS_EPH_INFO_MAX_SEG_NUM - 1; ucLoop++)
    {
        ulEphDataStrLen = AT_AGPS_EPH_INFO_NOT_FIRST_SEG_STR_LEN;

        usAtCmdLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                "%s^CAGPSEPHINFO: %d,%d,%d,",
                                                gaucAtCrLf,
                                                AT_AGPS_EPH_INFO_MAX_SEG_NUM,
                                                ucLoop + 1,
                                                ulEphDataStrLen);

        /* 将16进制数转换为ASCII码后输入主动命令内容 */
        usAtCmdLength += (TAF_UINT16)At_HexText2AsciiStringSimple(AT_CMD_MAX_LEN,
                                                (TAF_INT8 *)pgucAtSndCodeAddr,
                                                ((TAF_UINT8 *)pgucAtSndCodeAddr) + usAtCmdLength,
                                                ulEphDataStrLen / 2,
                                                pucEphData + ulEphDataByteOffset);

        usAtCmdLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + usAtCmdLength,
                                                "%s", gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, usAtCmdLength);

        ulEphDataByteOffset += ulEphDataStrLen / 2;
    }

    return VOS_OK;
}
VOS_UINT32 AT_RcvXpdsAlmInfoInd(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_XPDS_MSG_STRU                   *pstRcvMsg;
    XPDS_AT_GPS_ALM_INFO_IND_STRU      *pstAlmInfoInd;
    VOS_UINT16                          usAtCmdLength;
    VOS_UINT32                          ulAlmDataStrLen;
    VOS_UINT32                          ulAlmDataByteOffset;
    VOS_UINT8                          *pucAlmData;
    VOS_UINT8                           ucLoop;

    /* 初始化 */
    pstRcvMsg     = (AT_XPDS_MSG_STRU*)pstMsg;
    pstAlmInfoInd = (XPDS_AT_GPS_ALM_INFO_IND_STRU *)pstRcvMsg->aucContent;

    /* 通过clientid获取index */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsAlmInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvXpdsAlmInfoInd: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    pucAlmData = (VOS_UINT8 *)pstAlmInfoInd;

    ulAlmDataStrLen = AT_AGPS_ALM_INFO_FIRST_SEG_STR_LEN;

    /* 第1包数据 */
    usAtCmdLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "%s^CAGPSALMINFO: %d,%d,%d,",
                                            gaucAtCrLf,
                                            AT_AGPS_ALM_INFO_MAX_SEG_NUM,
                                            0,
                                            ulAlmDataStrLen);

    /* 第1包数据 */
    /* 将16进制数转换为ASCII码后输入主动命令内容 */
    usAtCmdLength += (TAF_UINT16)At_HexText2AsciiStringSimple(AT_CMD_MAX_LEN,
                                            (TAF_INT8 *)pgucAtSndCodeAddr,
                                            ((TAF_UINT8 *)pgucAtSndCodeAddr) + usAtCmdLength,
                                            ulAlmDataStrLen / 2,
                                            pucAlmData);

    usAtCmdLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usAtCmdLength,
                                            "%s", gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usAtCmdLength);

    ulAlmDataByteOffset = ulAlmDataStrLen / 2;

    /* 从第2包到第3包的数据 */
    for (ucLoop = 0; ucLoop < AT_AGPS_ALM_INFO_MAX_SEG_NUM - 1; ucLoop++)
    {
        ulAlmDataStrLen = AT_AGPS_ALM_INFO_NOT_FIRST_SEG_STR_LEN;

        usAtCmdLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                "%s^CAGPSALMINFO: %d,%d,%d,",
                                                gaucAtCrLf,
                                                AT_AGPS_ALM_INFO_MAX_SEG_NUM,
                                                ucLoop + 1,
                                                ulAlmDataStrLen);

        /* 将16进制数转换为ASCII码后输入主动命令内容 */
        usAtCmdLength += (TAF_UINT16)At_HexText2AsciiStringSimple(AT_CMD_MAX_LEN,
                                                (TAF_INT8 *)pgucAtSndCodeAddr,
                                                ((TAF_UINT8 *)pgucAtSndCodeAddr) + usAtCmdLength,
                                                ulAlmDataStrLen / 2,
                                                pucAlmData + ulAlmDataByteOffset);

        usAtCmdLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr + usAtCmdLength,
                                                "%s", gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, usAtCmdLength);

        ulAlmDataByteOffset += ulAlmDataStrLen / 2;
    }

    return VOS_OK;
}


#endif

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

