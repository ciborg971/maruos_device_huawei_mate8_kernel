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
   1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "AtMnInterface.h"
#include "MnCallApi.h"
#include  "product_config.h"
#include "MnErrorCode.h"
#include "AtParse.h"
#include "ATCmdProc.h"
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif


#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_API_C

/*****************************************************************************
   2 ����ʵ��
*****************************************************************************/


VOS_UINT32  MN_CALL_SendAppRequest(
    MN_CALL_APP_REQ_ENUM_UINT32         enReq,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_APP_REQ_PARM_UNION   *punParam
)
{
    MN_CALL_APP_REQ_MSG_STRU *pstMsg =
        (MN_CALL_APP_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(MN_CALL_APP_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("MN_CALL_SendAppRequest: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(MN_CALL_APP_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��дVOS��Ϣͷ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /* ��дԭ���ײ� */
    pstMsg->enReq = enReq;
    pstMsg->clientId = clientId;
    pstMsg->opId = opId;
    pstMsg->callId = callId;

    if (TAF_NULL_PTR != punParam)
    {
        PS_MEM_CPY(&pstMsg->unParm, punParam, sizeof(pstMsg->unParm));
    }

    /* ����VOS��Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_ERR_LOG1("MN_CALL_SendAppRequest: Send Message Fail. reqtype:", (VOS_INT32)enReq);
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32  MN_CALL_Orig(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                       *pCallId,
    const MN_CALL_ORIG_PARAM_STRU      *pstOrigParam
)
{
    VOS_UINT32                          ulResult;
    MN_CALL_ID_T                        callId;

    /* �ڸô����ڷ���CallId��ֱ�ӽ�callId��ֵΪ0
       CallId�ķ���ŵ�MN CALLģ�鴦�������ĺ����� */
    callId = 0;

    /* �����첽Ӧ������ */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_ORIG_REQ, clientId,
                                      opId, callId,
                                      (MN_CALL_APP_REQ_PARM_UNION*)pstOrigParam);

    *pCallId = callId;

    return ulResult;

}
VOS_UINT32  MN_CALL_End(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_END_PARAM_STRU       *pstEndParam
)
{
    MN_CALL_END_PARAM_STRU              stEndParam;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stEndParam, 0x00, sizeof(MN_CALL_END_PARAM_STRU));

    if ( TAF_NULL_PTR == pstEndParam)
    {
        /* ���ع���һ��MN_CALL_END_REQ_PARAM_STRU�ṹ, ��дԭ��ֵΪ255 */
        stEndParam.enEndCause = MN_CALL_INTERWORKING_UNSPECIFIED;
        pstEndParam = &stEndParam;
    }

    /* �����첽Ӧ������ */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_END_REQ, clientId,
                                      opId, callId,
                                      (MN_CALL_APP_REQ_PARM_UNION*)pstEndParam);

    return ulResult;
}


VOS_UINT32  MN_CALL_QryCdur(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId
)
{
    VOS_UINT32                          ulResult;

    /* �����첽Ӧ������ */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_GET_CDUR_REQ, clientId,
                                      opId, callId,
                                      VOS_NULL_PTR);

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_Answer
 ��������  : ����һ������
 �������  : clientId   - Client ID
             opId       - ���β����ı�ʶ
             callId     - ��Ҫ�����ĺ��е�ID
             pstAnsParam  - ����������Ҫ�Ĳ���, �ò�����ѡ, NULL��ʾʹ��Ĭ�ϲ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  MN_CALL_Answer(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_ANS_PARAM_STRU        *pstAnsParam
)
{
    MN_CALL_ANS_PARAM_STRU              stAnsParam;
    VOS_UINT32                          ulResult;

    if ( TAF_NULL_PTR == pstAnsParam)
    {
        /* ���ع���һ��MN_CALL_ANS_REQ_PARAM_STRU�ṹ */
        pstAnsParam = &stAnsParam;
    }

    /* �����첽Ӧ������ */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_ANSWER_REQ, clientId,
                                      opId, callId,
                                      (MN_CALL_APP_REQ_PARM_UNION*)pstAnsParam);
    return ulResult;

}



VOS_UINT32  TAF_CALL_SendDtmf(
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgType,
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const TAF_CALL_DTMF_PARAM_STRU     *pstDtmfParam
)
{
    VOS_UINT32                          ulResult;
    MN_CALL_APP_REQ_PARM_UNION          stAppPara;

    /* ��ʼ���ֲ����� */
    PS_MEM_SET(&stAppPara, 0, sizeof(stAppPara));
    PS_MEM_CPY(&stAppPara.stDtmf, pstDtmfParam, sizeof(TAF_CALL_DTMF_PARAM_STRU));

    /* �����첽Ӧ������ */
    ulResult = MN_CALL_SendAppRequest(enMsgType, clientId, opId,
                                      pstDtmfParam->CallId,
                                      &stAppPara);

    return ulResult;
}


VOS_UINT32  MN_CALL_Sups(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulResult;

    /* �����첽Ӧ������ */
    /* ��������CallId���һ�� */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_SUPS_CMD_REQ, clientId,
                                      opId, pstCallSupsParam->callId,
                                      (MN_CALL_APP_REQ_PARM_UNION*)pstCallSupsParam);

    return ulResult;
}



VOS_UINT32  MN_CALL_GetCallInfos(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId
)
{
    VOS_UINT32                          ulResult;

    /* �����첽Ӧ������ */
    ulResult = MN_CALL_SendAppRequest(MN_CALL_APP_GET_INFO_REQ, clientId,
                                      opId, callId,
                                      VOS_NULL_PTR);

    return ulResult;
}
VOS_UINT32 MN_CALL_SetAlsLineNo(
    TAF_UINT8                           ucIndex,
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine
)
{
    VOS_UINT32                          ulRst;
    MN_CALL_SET_ALS_PARAM_STRU          stSetAls;

    stSetAls.enAlsLine = enAlsLine;

    /*1.ͨ��TAF_MSG_ALS_LINE_NO_SET��Ϣ�������ṹMN_CALL_ALS_PARAM_STRU
        ֪ͨTAF��ALS�������á�*/
    ulRst = MN_CALL_SendAppRequest(MN_CALL_APP_SET_ALS_REQ,
                                   gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   0,
                                   (MN_CALL_APP_REQ_PARM_UNION*)&stSetAls);

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CheckUus1ParmValid
 ��������  : �������UUS1��������Ƿ�Ϸ�
 �������  : enSetType      :�����ȥ����UUS1
             pstUus1Info    :UUS1�����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32     :�������ɹ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��27��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_CALL_CheckUus1ParmValid(
    MN_CALL_SET_UUS1_TYPE_ENUM_U32      enSetType,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
)
{
    if ( VOS_NULL_PTR == pstUus1Info )
    {
        return MN_ERR_INVALIDPARM;
    }

    /*  У������ĺϷ���,�Ƿ�ֱ�ӷ��� */
    if ( ( enSetType >= MN_CALL_SET_UUS1_BUTT )
      || ( pstUus1Info->enMsgType > MN_CALL_UUS1_MSG_RELEASE_COMPLETE ))
    {
        return MN_ERR_INVALIDPARM;
    }


    /* ����UUIE�ļ�������һ���Ƿ���UUIE,�����ĳ��Ⱥ�PD�����м��,
       ��Ӧ�ñ�֤,������ڼ���UUS1ʱ��Ҫ���,ȥ������ĸ���  */
    if ( ( MN_CALL_SET_UUS1_ACT == enSetType)
      && ( MN_CALL_UUS_IEI != pstUus1Info->aucUuie[MN_CALL_IEI_POS]))
    {
        return MN_ERR_INVALIDPARM;
    }

    return MN_ERR_NO_ERROR;
}


VOS_UINT32  TAF_XCALL_SendFlashReq(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_FLASH_PARA_STRU           *pstFlashPara
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_CALL_APP_SEND_FLASH_REQ_STRU *pstMsg =
        (TAF_CALL_APP_SEND_FLASH_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(TAF_CALL_APP_SEND_FLASH_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("TAF_XCALL_SendFlashReq: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_SEND_FLASH_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��дVOS��Ϣͷ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /* ��д��Ϣ���� */
    pstMsg->usMsgId    = TAF_CALL_APP_SEND_FLASH_REQ;
    pstMsg->usClientId = clientId;
    pstMsg->ucOpId     = opId;
    PS_MEM_CPY(&(pstMsg->stFlashPara), pstFlashPara, sizeof(TAF_CALL_FLASH_PARA_STRU));

    /* ����VOS��Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_ERR_LOG("TAF_XCALL_SendFlashReq: Send TAF_CALL_APP_SEND_FLASH_REQ Message Fail");
        return VOS_ERR;
    }

    return VOS_OK;
#else
    return VOS_ERR;
#endif
}

/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, begin */
/*****************************************************************************
 �� �� ��  : TAF_XCALL_SendBurstDtmf
 ��������  : APP��TAF����Flash����
 �������  : clientId              - Client ID
             opId                  - ���β����ı�ʶ
             pstSndBurstDTMFPara   - ����Send Burst Dtmf������Ҫ�Ĳ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_XCALL_SendBurstDtmf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_BURST_DTMF_PARA_STRU      *pstSndBurstDTMFPara
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_CALL_BURST_DTMF_REQ_MSG_STRU *pstMsg =
        (TAF_CALL_BURST_DTMF_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(TAF_CALL_BURST_DTMF_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("TAF_XCALL_SendBurstDtmf: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_BURST_DTMF_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��дVOS��Ϣͷ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /* ��д��Ϣ���� */
    pstMsg->usMsgId    = TAF_CALL_APP_SEND_BURST_DTMF_REQ;
    pstMsg->usClientId = clientId;
    pstMsg->ucOpId     = opId;
    PS_MEM_CPY(&(pstMsg->stBurstDTMFPara), pstSndBurstDTMFPara, sizeof(TAF_CALL_BURST_DTMF_PARA_STRU));

    /* ����VOS��Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_ERR_LOG("TAF_XCALL_SendBurstDtmf: Send TAF_CALL_APP_SEND_BURST_DTMF_REQ Message Fail");
        return VOS_ERR;
    }

    return VOS_OK;
#else
    return VOS_ERR;
#endif
}
/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, end */


VOS_UINT32  TAF_XCALL_SendCustomDialReq(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_CUSTOM_DIAL_PARA_STRU     *pstCustomDialPara
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU *pstMsg =
        (TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("TAF_XCALL_SendCustomDialReq: Failed to alloc VOS message.");
        return VOS_FALSE;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��дVOS��Ϣͷ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /* ��д��Ϣ���� */
    pstMsg->usMsgId    = TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ;
    pstMsg->usClientId = clientId;
    pstMsg->ucOpId     = opId;
    PS_MEM_CPY(&(pstMsg->stCustomDialPara), pstCustomDialPara, sizeof(pstMsg->stCustomDialPara));

    /* ����VOS��Ϣ */
    PS_SEND_MSG(WUEPS_PID_AT, pstMsg);

    return VOS_TRUE;
#else
    return VOS_FALSE;
#endif
}


/* Added by w00351686 for CDMA Iteration 16 2015-7-24 begin */
/*****************************************************************************
Function Name   :   TAF_XCALL_SendContinuousDtmf
Description     :   Process the message of Send Continuous DTMF
Input parameters:   clientId              - Client ID
                    opId                  - The identification of current operation
                    pstSndContDTMFPara    - The required parameter of "Send Burst Dtmf"
Output parameters:  NULL
Return Value    :   VOS_UINT32

Modify History  :
1)  Date           : 2015-07-24
    Author         : w00351686
    Modify content : Create
*****************************************************************************/
VOS_UINT32  TAF_XCALL_SendContinuousDtmf(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CALL_CONT_DTMF_PARA_STRU       *pstSndContDTMFPara
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_CALL_CONT_DTMF_REQ_MSG_STRU *pstMsg = VOS_NULL_PTR;
    pstMsg = (TAF_CALL_CONT_DTMF_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(TAF_CALL_CONT_DTMF_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("TAF_XCALL_SendContinuousDtmf: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_CONT_DTMF_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* fill in VOS_MSG_HEAD */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /* fill in message content */
    pstMsg->usMsgId    = TAF_CALL_APP_SEND_CONT_DTMF_REQ;
    pstMsg->usClientId = clientId;
    pstMsg->ucOpId     = opId;
    PS_MEM_CPY(&(pstMsg->stContDTMFPara), pstSndContDTMFPara, sizeof(TAF_CALL_CONT_DTMF_PARA_STRU));

    /* Send VOS message */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_ERR_LOG("TAF_XCALL_SendContinuousDtmf: Send TAF_CALL_APP_SEND_CONT_DTMF_REQ Message Fail");
        return VOS_ERR;
    }

    return VOS_OK;
#else
    return VOS_ERR;
#endif
}
/* Added by w00351686 for CDMA Iteration 16 2015-7-24 end */

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SendCclpr
 ��������  : APP��TAF����Clpr����
 �������  : clientId              - Client ID
             opId                  - ���β����ı�ʶ
             ucCallId               - ����id
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��20��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_XCALL_SendCclpr(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT8                           ucCallId
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_CALL_SND_CCLPR_REQ_MSG_STRU *pstMsg =
        (TAF_CALL_SND_CCLPR_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_AT,
                                              sizeof(TAF_CALL_SND_CCLPR_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("TAF_XCALL_SendCclpr: Failed to alloc VOS message.");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                0x00,
               (VOS_SIZE_T)(sizeof(TAF_CALL_SND_CCLPR_REQ_MSG_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��дVOS��Ϣͷ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = AT_GetDestPid(clientId, I0_WUEPS_PID_TAF);

    /* ��д��Ϣ���� */
    pstMsg->usMsgId    = TAF_CALL_APP_SEND_CCLPR_REQ;
    pstMsg->usClientId = clientId;
    pstMsg->ucOpId     = opId;
    pstMsg->ucCallId   = ucCallId;

    /* ����VOS��ϢTAF_CALL_APP_SEND_CCLPR_REQ */
    PS_SEND_MSG(WUEPS_PID_AT, pstMsg);

    return VOS_OK;
#else
    return VOS_ERR;
#endif
}


#ifdef  __cplusplus
#if  __cplusplus
}
#endif
#endif
