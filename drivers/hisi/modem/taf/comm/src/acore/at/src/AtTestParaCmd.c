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

#include "AtCheckFunc.h"
#include "ATCmdProc.h"
#include "AtDataProc.h"
#include "Taf_Tafm_Remote.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"

#include "AtTestParaCmd.h"

#include "TafAppMma.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e767 -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_TESTPARACMD_C
/*lint +e767 +e960*/



VOS_UINT32 At_TestCgdcont(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

#if (FEATURE_ON == FEATURE_LTE)
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (0-31),\"IP\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);


#if (FEATURE_ON == FEATURE_IPV6)
    if (AT_IPV6_CAPABILITY_IPV4_ONLY != AT_GetIpv6Capability())
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: (0-31),\"IPV6\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: (0-31),\"IPV4V6\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
#endif

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0-31),\"PPP\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

#else
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11),\"IP\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

#if (FEATURE_ON == FEATURE_IPV6)
    if (AT_IPV6_CAPABILITY_IPV4_ONLY != AT_GetIpv6Capability())
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: (1-11),\"IPV6\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: (1-11),\"IPV4V6\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
#endif

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (1-11),\"PPP\",,,(0-2),(0-3),(0,1),(0,1),(0-2),(0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);


#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_TestCgdscont(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

#if (FEATURE_ON == FEATURE_LTE)
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                        "%s: (1-31),(0-31),(0-2),(0-3)",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#else
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                        "%s: (1-11),(0-11),(0-2),(0-3)",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 At_TestCgtft(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: \"IP\",(1-16),(0-255),,(0-255),,,(00000000-FFFFFFFF),,(00000-FFFFF),(0-3)\r\n",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

#if (FEATURE_ON == FEATURE_IPV6)
    if (AT_IPV6_CAPABILITY_IPV4_ONLY != AT_GetIpv6Capability())
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: \"IPV6\",(1-16),(0-255),,(0-255),,,(00000000-FFFFFFFF),,(00000-FFFFF),(0-3)\r\n",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR*)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%s: \"IPV4V6\",(1-16),(0-255),,(0-255),,,(00000000-FFFFFFFF),,(00000-FFFFF),(0-3)",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_TestCgact(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_TestCgcmod(VOS_UINT8 ucIndex)
{


    /* CGEQNEG的测试命令和CGCMODE的返回值相同，使用相同的函数 */
   return At_TestCgeqnegPara(ucIndex);


}
VOS_UINT32 At_TestCgpaddr(VOS_UINT8 ucIndex)
{

    /* 执行命令操作 */
    if ( VOS_OK != TAF_PS_GetPdpContextInfo(WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGPADDR_TEST;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 At_TestCgautoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_TestAuhtdata(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

#if (FEATURE_ON == FEATURE_LTE)
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                   "%s: (0-31),(0-2),,",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#else
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11),(0-2),,",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_TestNdisconn(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    usLength = 0;

#if (FEATURE_ON == FEATURE_LTE)
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-20),(0,1),,,,(0,1,2,3)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#else
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-16),(0,1),,,,(0,1,2,3)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_TestNdisDup(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    usLength = 0;

#if (FEATURE_ON == FEATURE_LTE)
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-20),(0-1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#else
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-16),(0-1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 At_TestCgeqos(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-31),(0-9),(0-262144),(0-262144),(0-262144),(0-262144)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 At_TestCgeqosrdp(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-31)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 At_TestCgcontrdp(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-31)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 At_TestCgscontrdp(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-31)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 At_TestCgtftrdp(VOS_UINT8 ucIndex)
{
    VOS_UINT16 usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-31)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

/*****************************************************************************
 函 数 名  : AT_TestChrgEnablePara
 功能描述  : ^TCHRENABLE=? 查询是否需要补电
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年3月16日
    作    者   : 崔军强
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 AT_TestChrgEnablePara(VOS_UINT8 ucIndex)
{
    VOS_INT32                           lChargeEnable = 0;

    lChargeEnable = mdrv_misc_get_charge_state(); /* BSP_TBAT_CHRStGet()) */
    /* 只有TRUE/FLASE的返回值是有效的 */
    if((lChargeEnable == TRUE)||( lChargeEnable == FALSE))
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                  "%s:%d",
                                                  "^TCHRENABLE",
                                                  lChargeEnable);
        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_TestCposrPara(VOS_UINT8 ucIndex)
{
    /* 通道检查 */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* 打印输出+CPOSR支持的参数设置范围 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   "%s: (0,1)",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}


VOS_UINT32 AT_TestCmutPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0-1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



/* 如下函数并非此项目中新增, 只是从AtExtendCmd.c文件中移动到此文件而已 */

VOS_UINT32 At_TestVtsPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "+VTS: (0-9,A-D,*,#)");
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_TestCuus1Para(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR*)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                      "+CUUS1:(0,1),(0,1),(0-6),(0-4),(0-3)");

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_TestCcwaPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_TestCcfcPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0-5)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_TestCusdPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0-2)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_TestCpwdPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (\"P2\",8),(\"SC\",8),(\"AO\",4),(\"OI\",4),(\"OX\",4),(\"AI\",4),(\"IR\",4),(\"AB\",4),(\"AG\",4),(\"AC\",4)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_TestClckPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    /* Modified by w00316404 for M project A characeristic AT part, 2015-4-7, Begin */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (\"SC\",\"AO\",\"OI\",\"OX\",\"AI\",\"IR\",\"AB\",\"AG\",\"AC\",\"FD\",\"PN\",\"PU\",\"PP\")",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    /* Modified by w00316404 for M project A characeristic AT part, 2015-4-7, End */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_TestCpbsPara(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == SI_PB_Query(gastAtClientTab[ucIndex].usClientId, 1))
    {
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_TestCpbrPara(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == SI_PB_Query(gastAtClientTab[ucIndex].usClientId, 0))
    {
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

VOS_UINT32 AT_TestCnmaPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if(AT_CMGF_MSG_FORMAT_PDU == pstSmsCtx->enCmgfMsgFormat)    /* TEXT方式参数检查 */
    {
        gstAtSendData.usBufLen = (TAF_UINT16)VOS_sprintf((TAF_CHAR*)pgucAtSndCodeAddr,
                                          "%s: (0-2)",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        gstAtSendData.usBufLen = 0;
    }

    return AT_OK;
}
VOS_UINT32 AT_TestCpasPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (0-5)",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);


    return AT_OK;
}
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))

VOS_UINT32 AT_TestCscbPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)VOS_sprintf((VOS_CHAR*)pgucAtSndCodeAddr,"%s:(0,1)",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    return AT_OK;
}
#endif


VOS_UINT32 AT_TestCpmsPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    usLength  = 0;
    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (MN_MSG_ME_STORAGE_ENABLE == pstSmsCtx->enMsgMeStorageStatus)
    {
        usLength = (VOS_UINT16)VOS_sprintf((VOS_CHAR*)pgucAtSndCodeAddr,
                    "%s: (\"SM\",\"ME\"),(\"SM\",\"ME\"),(\"SM\",\"ME\")",
                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        usLength = (VOS_UINT16)VOS_sprintf((VOS_CHAR*)pgucAtSndCodeAddr,
                    "%s: (\"SM\"),(\"SM\"),(\"SM\")",
                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 At_TestCopsPara(TAF_UINT8 ucIndex)
{
    TAF_MMA_PLMN_LIST_PARA_STRU             stPlmnListPara;

    stPlmnListPara.usQryNum    = TAF_MMA_MAX_PLMN_NAME_LIST_NUM;
    stPlmnListPara.usCurrIndex = 0;

    if (VOS_TRUE == Taf_PhonePlmnList(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0, &stPlmnListPara))
    {
        /* 设置当前操作类型 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COPS_TEST;

        /* 返回命令处理挂起状态 */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}

VOS_UINT32 At_TestCpolPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    /* Added by y00307564 for CDMA Iteration 8 2015-2-5 begin */
    /* 参数检查 */
    if (AT_CMD_OPT_TEST_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    ulRst = TAF_MMA_TestCpolReq(WUEPS_PID_AT,
                                gastAtClientTab[ucIndex].usClientId,
                                0,
                                pstNetCtx->enPrefPlmnType);

    if (VOS_TRUE == ulRst)
    {
        /* 设置AT模块实体的状态为等待异步返回 */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPOL_TEST;

        return AT_WAIT_ASYNC_RETURN;
    }
    /* Added by y00307564 for CDMA Iteration 8 2015-2-5 end */

    return AT_ERROR;
}


VOS_UINT32 At_TestCgeqnegPara(VOS_UINT8 ucIndex)
{

    /*CGEQNEG的测试命令和CGACT的查询命令的功能类似,都要获取当前各CID的激活
    情况,向TAF查询当前各CID的激活情况*/

    if ( VOS_OK != TAF_PS_GetPdpContextState(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0) )
    {
        return AT_ERROR;
    }

    /*发送查询消息成功后,将命令状态改为CGEQNEG*/
    if(AT_SUCCESS != At_StartTimer(AT_QRY_PARA_TIME,ucIndex))
    {
        AT_ERR_LOG("At_TestParaCmd:ERROR:Start Timer");
        return AT_ERROR;
    }

    /* 设置当前操作类型 */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQNEG_TEST;
    return AT_WAIT_ASYNC_RETURN;    /* 返回命令处理挂起状态 */

    /*接下来到TAF事件上报的地方,获取当前哪些CID被激活,并打印当前哪些CID被激活.*/


}



VOS_UINT32 At_TestCgeqreqPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr,
                                        "%s: \"IP\",%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        CGEQREQ_TEST_CMD_PARA_STRING,
                                        gaucAtCrLf);

#if (FEATURE_ON == FEATURE_IPV6)

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%s: \"IPV6\",%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        CGEQREQ_TEST_CMD_PARA_STRING,
                                        gaucAtCrLf);


    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%s: \"IPV4V6\",%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        CGEQREQ_TEST_CMD_PARA_STRING);
#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_TestCgansPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0,1),(\"NULL\")",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_TestCgansExtPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

VOS_UINT32 At_TestCgdnsPara(VOS_UINT8 ucIndex)
{



    /* CGDNS的测试命令和CGCMODE的返回值相同，使用相同的函数 */
    return At_TestCgeqnegPara(ucIndex);

}
VOS_UINT32 At_TestCgdataPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16      usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: (\"NULL\")",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 AT_TestCbgPara( VOS_UINT8 ucIndex )
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (0,1)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}


VOS_UINT32 AT_TestNCellMonitorPara(VOS_UINT8 ucIndex)
{

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (0,1)",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}


VOS_UINT32 AT_TestRefclkfreqPara(VOS_UINT8 ucIndex)
{
    /* 通道检查 */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* 打印输出^REFCLKFREQ支持的参数设置范围 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   "%s: (0,1)",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_UINT32 AT_TestCiregPara(VOS_UINT8 ucIndex)
{

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (0-2)",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}


VOS_UINT32 AT_TestCirepPara(VOS_UINT8 ucIndex)
{

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (0,1)",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}
#endif

#if (FEATURE_ON == FEATURE_AT_HSUART)

VOS_UINT32 AT_TestIprPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength = 0;

#ifdef CONFIG_DIALUP_HSUART_REVISE
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: (0,300,600,1200,2400,4800,9600,19200,38400,57600,115200,230400,460800,921600,2764800)",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#else
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: (0,300,600,1200,2400,4800,9600,19200,38400,57600,115200,230400,250000,300000,375000,600000,750000,1000000,3000000)",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#endif

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}


VOS_UINT32 AT_TestIcfPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: (1-6),(0-1)",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}


VOS_UINT32 AT_TestIfcPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength = 0;

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: (0,2),(0,2)",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}
#endif

/* Added by lwx277467 for UE Mode, 2015-9-7, begin */
/*****************************************************************************
 函 数 名  : AT_TestUECenterPara
 功能描述  : +CEUS=?
 输入参数  : ucIndex --- 用户索引
 输出参数  : 无
 返 回 值  : AT_XXX  --- ATC返回码
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月07日
    作    者   : lwx277467
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 AT_TestUECenterPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (0,1)",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}
/* Added by lwx277467 for UE Mode, 2015-9-7, end */

#ifdef  __cplusplus
#if  __cplusplus
  }
  #endif
#endif

