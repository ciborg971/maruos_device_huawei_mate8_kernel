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


#include "pamappom.h"
#include "omprivate.h"
#include "cpm.h"
#include "NVIM_Interface.h"
#include "TafNvInterface.h"
#include "SCMProc.h"
#include "SCMSoftDecode.h"
#include "CbtPpm.h"
#include "DrvNvInterface.h"
#include "ScComm.h"
#include "NasNvInterface.h"

#if (RAT_MODE != RAT_GU)
#include "msp_nvim.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_PAM_APP_OM_C
/*lint +e767*/

/* wait for the feedback of modem id quereying */
VOS_SEM                                 g_ulPamVosQuereyModemIdSem = VOS_NULL;
VOS_SEM                                 g_ulPamVosQuereyModemIdProtectionSem = VOS_NULL;

/* the result of modem ID */
MODEM_ID_ENUM_UINT16                    g_usPamVosQuereyModemIdResult = MODEM_ID_BUTT;

/* 记录收到消息信息的buffer及当前长度 */
OM_RECORD_BUF_STRU                      g_astAcpuRecordInfo[VOS_EXC_DUMP_MEM_NUM_BUTT];

VOS_UINT32                              g_ulAcpuOmFilterFlag;

VOS_CHAR*                               g_apcATFileterTable[]=
{
        "AT+CPIN"    ,
        "\r\n+CPIN:" ,
        "AT+CLCK"    ,
        "\r\n+CLCK:" ,
        "AT+CPWD"    ,
        "\r\n+CPWD:" ,
        "AT^CPIN"    ,
        "\r\n^CPIN:" ,
        "AT^CPIN2"   ,
        "\r\n^CPIN2:",
        "AT+CPBW"    ,
        "\r\n+CPBW:" ,
        "AT+CRSM"    ,
        "\r\n+CRSM:" ,
        "AT+CSIM"    ,
        "\r\n+CSIM:" ,
        "AT+CCHO"    ,
        "\r\n+CCHO:" ,
        "AT+CCHC"    ,
        "AT+CNUM"    ,
        "\r\n+CNUM:" ,
        "AT+CGLA"    ,
        "\r\n+CGLA:" ,
        "AT+CRLA"    ,
        "\r\n+CRLA:" ,
        "AT+CIMI"    ,
        "\r\n+CIMI:" ,
        "AT^CSIN"    ,
        "\r\n^CSIN:" ,
        "AT^CSTR"    ,
        "\r\n^CSTR:" ,
        "AT^CSEN"    ,
        "\r\n^CSEN:" ,
        "\r\n^CCIN:" ,
        "AT^CISA"    ,
        "\r\n^CISA:" ,
        "AT^CARDATR" ,
        "\r\n^CARDATR:" ,
        "AT^UICCAUTH",
        "\r\n^UICCAUTH:" ,
        "AT^URSM"    ,
        "\r\n^URSM:" ,
        "AT^ICCID"   ,
        "\r\n^ICCID:"
};
VOS_VOID OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber)
{
    VOS_UINT32 *pulBuf;

    if(VOS_EXC_DUMP_MEM_NUM_BUTT <= enNumber)
    {
        return;
    }

    if(VOS_NULL_PTR == g_astAcpuRecordInfo[enNumber].pucBuf)
    {
        return;
    }

    if(0 == g_astAcpuRecordInfo[enNumber].ulLen)
    {
        return;
    }

    /* 在start中已经变更了记录endslice的长度，因此此处回退四个字节填写endslice的值 */
    pulBuf = (VOS_UINT32*)(g_astAcpuRecordInfo[enNumber].pucBuf + g_astAcpuRecordInfo[enNumber].ulLen - sizeof(VOS_UINT32));

    *pulBuf = VOS_GetSlice();

    return;
}

/*****************************************************************************
 Prototype       : OM_RecordInfoStart
 Description     : A核保留桩函数
 Input           : ulNumer -- 任务号
                   ulSendPid -- 发送PID
                   ulRcvPid -- 接收PID
                   ulMsgName -- 消息名称
 Output          : None
 Return Value    : VOS_VOID

 History         : ---
    Date         : 2012-07-09
    Author       : s00702770
    Modification : Created function
 *****************************************************************************/
VOS_VOID OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber, VOS_UINT32 ulSendPid, VOS_UINT32 ulRcvPid, VOS_UINT32 ulMsgName)
{
    OM_RECORD_INFO_STRU     stRecordInfo;

    if(VOS_EXC_DUMP_MEM_NUM_BUTT <= enNumber)
    {
       return;
    }

    if(VOS_NULL_PTR == g_astAcpuRecordInfo[enNumber].pucBuf)
    {
       return;
    }

    g_astAcpuRecordInfo[enNumber].ulLen %= VOS_TASK_DUMP_INFO_SIZE;

    stRecordInfo.usSendPid      = (VOS_UINT16)ulSendPid;
    stRecordInfo.usRcvPid       = (VOS_UINT16)ulRcvPid;
    stRecordInfo.ulMsgName      = ulMsgName;
    stRecordInfo.ulSliceStart   = VOS_GetSlice();
    stRecordInfo.ulSliceEnd     = 0;

    /*lint -e534*/
    VOS_MemCpy((g_astAcpuRecordInfo[enNumber].pucBuf + g_astAcpuRecordInfo[enNumber].ulLen),
              &stRecordInfo, sizeof(OM_RECORD_INFO_STRU));
    /*lint +e534*/

    g_astAcpuRecordInfo[enNumber].ulLen += (VOS_UINT32)sizeof(OM_RECORD_INFO_STRU);

    return;
}


VOS_VOID OM_RecordMemInit(VOS_VOID)
{
   VOS_UINT32 i;

   /*lint -e534*/
   VOS_MemSet(g_astAcpuRecordInfo, 0, sizeof(g_astAcpuRecordInfo));
   /*lint +e534*/

   /* 分配每个模块记录可谓可测信息的空间 */
   for(i = 0; i < VOS_EXC_DUMP_MEM_NUM_BUTT; i++)
   {
      g_astAcpuRecordInfo[i].pucBuf = (VOS_UINT8*)VOS_ExcDumpMemAlloc(i);

      if(VOS_NULL_PTR == g_astAcpuRecordInfo[i].pucBuf)
      {
          return;
      }
   }

   return;
}
VOS_VOID PAMOM_AcpuTimerMsgProc(MsgBlock* pMsg)
{
    return;
}


MODEM_ID_ENUM_UINT16 PAMOM_QuereyModemIdFromPid(VOS_UINT32 ulPid)
{
    PAM_VOS_QUEREY_MODEM_ID_STRU    *pstMsg;
    MODEM_ID_ENUM_UINT16             usModemId;

    if ( VOS_NULL == g_ulPamVosQuereyModemIdSem )
    {
        /*lint -e534*/
        Print("PAMOM_QuereyModemIdFromPid: Don't call in init state.\r\n");
        /*lint +e534*/

        return MODEM_ID_BUTT;
    }

    if ( VOS_OK != VOS_SmP(g_ulPamVosQuereyModemIdProtectionSem, 0) )
    {
        return MODEM_ID_BUTT;
    }

    pstMsg = (PAM_VOS_QUEREY_MODEM_ID_STRU *)VOS_AllocMsg(ACPU_PID_PAM_OM,
                            sizeof(PAM_VOS_QUEREY_MODEM_ID_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 分配消息失败 */
    if (VOS_NULL_PTR == pstMsg)
    {
        if ( VOS_OK != VOS_SmV(g_ulPamVosQuereyModemIdProtectionSem) )
        {
            /*blank */
        }

        return MODEM_ID_BUTT;
    }

    pstMsg->ulReceiverPid  = CCPU_PID_PAM_OM;
    pstMsg->usPrimId       = PAM_VOS_QUEREY_MODEM_ID_REQ;
    pstMsg->usModemID      = MODEM_ID_BUTT;
    pstMsg->ulPid          = ulPid;

    (VOS_VOID)VOS_SendMsg(ACPU_PID_PAM_OM, pstMsg);

    if ( VOS_OK != VOS_SmP(g_ulPamVosQuereyModemIdSem, 1000) )
    {
        if ( VOS_OK != VOS_SmV(g_ulPamVosQuereyModemIdProtectionSem) )
        {
            /*blank */
        }

        return MODEM_ID_BUTT;
    }

    usModemId = g_usPamVosQuereyModemIdResult;

    g_usPamVosQuereyModemIdResult = MODEM_ID_BUTT;

    if ( VOS_OK != VOS_SmV(g_ulPamVosQuereyModemIdProtectionSem) )
    {
        /*blank */
    }

    return usModemId;
}


VOS_VOID PAMOM_QueryModemIdMsgProc(MsgBlock* pMsg)
{
    PAM_VOS_QUEREY_MODEM_ID_STRU    *pstMsg;
    PAM_VOS_QUEREY_MODEM_ID_STRU    *pstCnfMsg;
    MODEM_ID_ENUM_UINT16             usModemId;

    pstMsg = (PAM_VOS_QUEREY_MODEM_ID_STRU *)pMsg;

    if (PAM_VOS_QUEREY_MODEM_ID_REQ == pstMsg->usPrimId)
    {
        usModemId = VOS_GetModemIDFromPid(pstMsg->ulPid);

        pstCnfMsg = (PAM_VOS_QUEREY_MODEM_ID_STRU *)VOS_AllocMsg(ACPU_PID_PAM_OM,
                            sizeof(PAM_VOS_QUEREY_MODEM_ID_STRU) - VOS_MSG_HEAD_LENGTH);

        /* 分配消息失败 */
        if (VOS_NULL_PTR == pstCnfMsg)
        {
            return;
        }

        pstCnfMsg->ulReceiverPid  = CCPU_PID_PAM_OM;
        pstCnfMsg->usPrimId       = PAM_VOS_QUEREY_MODEM_ID_CNF;
        pstCnfMsg->usModemID      = usModemId;
        pstCnfMsg->ulPid          = pstMsg->ulPid;

        (VOS_VOID)VOS_SendMsg(ACPU_PID_PAM_OM, pstCnfMsg);

    }
    else if (PAM_VOS_QUEREY_MODEM_ID_CNF == pstMsg->usPrimId)
    {
        g_usPamVosQuereyModemIdResult = pstMsg->usModemID;

        if ( VOS_OK != VOS_SmV(g_ulPamVosQuereyModemIdSem) )
        {
            g_usPamVosQuereyModemIdResult = MODEM_ID_BUTT;
        }
    }
    else
    {
        /* blank */
    }

    return;
}


 VOS_VOID PAMOM_AcpuCcpuPamMsgProc(MsgBlock* pMsg)
 {
    VOS_UINT16                          usPrimId;

    usPrimId = *(VOS_UINT16 *)(pMsg->aucValue);

    if (PAM_VOS_QUEREY_MODEM_ID_REQ == usPrimId)
    {
        PAMOM_QueryModemIdMsgProc(pMsg);
    }
    else if (PAM_VOS_QUEREY_MODEM_ID_CNF == usPrimId)
    {
        PAMOM_QueryModemIdMsgProc(pMsg);
    }
    else
    {
        Om_AcpuQueryDumpMsgProc(pMsg);/* GUTL 归一后需要整改 */
    }

    return;
}
VOS_VOID PAMOM_AppMsgProc(MsgBlock* pMsg)
{
    if (VOS_PID_TIMER == pMsg->ulSenderPid)
    {
        PAMOM_AcpuTimerMsgProc(pMsg);
    }
    else if (CCPU_PID_PAM_OM == pMsg->ulSenderPid)
    {
        PAMOM_AcpuCcpuPamMsgProc(pMsg);
    }
    else if ((DSP_PID_PROCSTUB == pMsg->ulSenderPid)
        || (CPROC_PID_1X_CM == pMsg->ulSenderPid)
        || (CPROC_PID_1X_SM == pMsg->ulSenderPid)
        || (CPROC_PID_1X_DSP == pMsg->ulSenderPid)
        || (CPROC_PID_HRPD_CM == pMsg->ulSenderPid)
        || (CPROC_PID_HRPD_SM == pMsg->ulSenderPid))
    {
        Om_AcpuPhyMsgProc(pMsg);
    }
    else
    {
        /* blank */
    }

    return;
}
VOS_UINT32 PAMOM_AcpuInit(VOS_VOID)
{
    NAS_NV_SMS_FILTER_CFG_STRU          stSmsFilterCfg;

    /* 分配二进制信号量 */
    if (VOS_OK != VOS_SmBCreate("VQMI", 0, VOS_SEMA4_FIFO, &g_ulPamVosQuereyModemIdSem))
    {
        return VOS_ERR;
    }

    if (VOS_OK != VOS_SmBCreate("VQMP", 1, VOS_SEMA4_FIFO, &g_ulPamVosQuereyModemIdProtectionSem))
    {
        return VOS_ERR;
    }

    /* SC文件有效性自检 */
    (VOS_VOID)SC_COMM_Restore();

    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                           en_NV_Item_Sms_Log_Filter_Cfg,
                          &stSmsFilterCfg,
                           sizeof(NAS_NV_SMS_FILTER_CFG_STRU)))
    {
        stSmsFilterCfg.ucSmsFilterEnableFlg = VOS_FALSE;
    }

    if (VOS_FALSE != stSmsFilterCfg.ucSmsFilterEnableFlg)
    {
        stSmsFilterCfg.ucSmsFilterEnableFlg = VOS_TRUE;
    }

    g_ulAcpuOmFilterFlag = stSmsFilterCfg.ucSmsFilterEnableFlg;

    return VOS_OK;
}


VOS_UINT32 PAMOM_AppPidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            return PAMOM_AcpuInit();

        default:
            break;
    }

    return VOS_OK;
}


VOS_UINT32 PAMOM_APP_FID_Init(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;

    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
        {
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_PAM_OM,
                                        (Init_Fun_Type)PAMOM_AppPidInit,
                                        (Msg_Fun_Type)PAMOM_AppMsgProc);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskPrio(ACPU_FID_PAM_OM, VOS_PRIORITY_M2);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            break;
        }

        default:
            break;
    }
    return VOS_OK;
}


VOS_UINT VOS_ICCError_CB(VOS_UINT ulChanID, VOS_UINT ulEvent, VOS_VOID* pParam)
{
    /*lint -e534*/
    LogPrint2("VOS_ICCError_CB: The Error Channel ID is %d,and Event is %d\n",
                (VOS_INT32)ulChanID, (VOS_INT32)ulEvent);
    /*lint +e534*/

    return VOS_OK;
}


VOS_UINT32 VOS_ICC_Init(VOS_VOID)
{
    OM_ICC_UDI_CTRL_STRU                astACPUICCCtrlTable;

    /*初始化 ICC通道*/
    /*lint -e534*/
    VOS_MemSet((&astACPUICCCtrlTable), 0, sizeof(astACPUICCCtrlTable));
    /*lint +e534*/

    astACPUICCCtrlTable.pstICCAttr = (ICC_CHAN_ATTR_S*)VOS_MemAlloc(ACPU_PID_PAM_OM,
                                                                    STATIC_MEM_PT,
                                                                    sizeof(ICC_CHAN_ATTR_S));
    if(VOS_NULL_PTR == astACPUICCCtrlTable.pstICCAttr)
    {
        return VOS_ERR;             /*分配内存失败单板会重启，因此不需要释放之前已经申请的内存*/
    }

    astACPUICCCtrlTable.enICCId               = UDI_ICC_GUOM4;
    astACPUICCCtrlTable.pstICCAttr->read_cb   = V_ICC_OSAMsg_CB;
    astACPUICCCtrlTable.pstICCAttr->u32Priority    = OM_ICC_CHANNEL_PRIORITY;
    astACPUICCCtrlTable.pstICCAttr->u32TimeOut     = OM_ICC_HANDSHAKE_TIME_MAX;
    astACPUICCCtrlTable.pstICCAttr->u32FIFOInSize  = OSA_ICC_BUFFER_SIZE;
    astACPUICCCtrlTable.pstICCAttr->u32FIFOOutSize = OSA_ICC_BUFFER_SIZE;
    astACPUICCCtrlTable.pstICCAttr->enChanMode     = ICC_CHAN_MODE_PACKET;
    astACPUICCCtrlTable.pstICCAttr->event_cb       = VOS_ICCError_CB;
    astACPUICCCtrlTable.pstICCAttr->write_cb       = VOS_NULL_PTR;

    if(VOS_ERROR == DRV_ICC_OPEN(astACPUICCCtrlTable.enICCId, astACPUICCCtrlTable.pstICCAttr))
    {
        /* 打开失败时记录当前ICC通道信息 */
        VOS_ProtectionReboot(OM_APP_ICC_INIT_ERROR, THIS_FILE_ID, __LINE__,VOS_NULL_PTR,0);

        return VOS_ERR;
    }

    return VOS_OK;
}

#if (VOS_WIN32 != VOS_OS_VER)
VOS_VOID OM_OSAEvent(VOS_VOID *pData, VOS_UINT32 ulLength)
{
    DIAG_EVENT_IND_STRU                 stEventInd;

    stEventInd.ulModule = DIAG_GEN_MODULE(DIAG_MODEM_0, DIAG_MODE_COMM);
    stEventInd.ulPid    = ACPU_PID_PAM_OM;
    stEventInd.ulEventId= OAM_EVENT_TIMER;
    stEventInd.ulLength = ulLength;
    stEventInd.pData    = pData;

    /*lint -e534*/
    (VOS_VOID)DIAG_EventReport(&stEventInd);
    /*lint +e534*/

    return;
}
#endif

/*****************************************************************************
 函 数 名  : PAM_OM_LayerMsgFilter
 功能描述  : 过滤PAM中的敏感信息
 输入参数  : const VOID *pMsg:消息指针
 输出参数  : 无
 返 回 值  : VOS_UINT32:
                返回VOS_TRUE:  表示该消息需要进行过滤
                返回VOS_FALSE: 表示该消息无需进行过滤
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2015年10月28日
    作    者   : zhuli
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PAM_OM_LayerMsgFilter(
    const VOS_VOID                      *pMsg
)
{
    OM_FILTER_MSG_HEAD_STRU             *pstMsgHead;

    if (VOS_FALSE == g_ulAcpuOmFilterFlag)
    {
        return VOS_FALSE;
    }

    pstMsgHead = (OM_FILTER_MSG_HEAD_STRU*)pMsg;

    /* SIM消息过滤 */
    if (  ((I0_WUEPS_PID_USIM <= pstMsgHead->ulSenderPid)&&(I0_MAPS_PB_PID >= pstMsgHead->ulSenderPid))
        ||((I1_WUEPS_PID_USIM <= pstMsgHead->ulSenderPid)&&(I1_MAPS_PB_PID >= pstMsgHead->ulSenderPid))
        ||((I2_WUEPS_PID_USIM <= pstMsgHead->ulSenderPid)&&(I2_MAPS_PB_PID >= pstMsgHead->ulSenderPid))
       )
    {
        return VOS_TRUE;
    }

    if (((I0_WUEPS_PID_USIM <= pstMsgHead->ulReceiverPid)&&(I0_MAPS_PB_PID >= pstMsgHead->ulReceiverPid))
        ||((I1_WUEPS_PID_USIM <= pstMsgHead->ulReceiverPid)&&(I1_MAPS_PB_PID >= pstMsgHead->ulReceiverPid))
        ||((I2_WUEPS_PID_USIM <= pstMsgHead->ulReceiverPid)&&(I2_MAPS_PB_PID >= pstMsgHead->ulReceiverPid))
       )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : PAM_OM_USIMMATFilter
 功能描述  : 过滤At到At USIM层间消息的函数
 输入参数  : pucATData     -- 消息中的数据
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

VOS_UINT32 PAM_OM_USIMMATFilter(
    VOS_UINT8                           *pucATData)
{
    VOS_UINT32                          i;
    VOS_UINT8                           aucTempData[USIMM_AT_CMD_MAX] = {0};

    (VOS_VOID)VOS_MemCpy(aucTempData, pucATData, sizeof(aucTempData));

    (VOS_VOID)At_UpString(aucTempData, sizeof(aucTempData));

    for(i=0; i<(sizeof(g_apcATFileterTable)/sizeof(g_apcATFileterTable[0])); i++)
    {
        if(VOS_OK == VOS_MemCmp((VOS_UINT8 *)g_apcATFileterTable[i], 
                                aucTempData, VOS_StrLen(g_apcATFileterTable[i])))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

