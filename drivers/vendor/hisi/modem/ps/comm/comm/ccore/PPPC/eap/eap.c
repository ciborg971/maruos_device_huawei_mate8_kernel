/************************************************************************
*                                                                      *
*                             Eap.c                                    *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2010/07/05                                      *
*  Author:             WANGYONG                                        *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP的EAP协议模块                                *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件定义了EAP协议模块的全部接口函数和内部处理函数              *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
extern VOID PPP_EAP_SendAAAAuthReq(PPPEAPINFO_S *pstEapInfo, PPP_DIAM_AUTH_MSG_S *pstMsg, ULONG ulMsgLen);

ULONG g_ulUserName256byteNum = 0;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/****************************************************************************
* CREATE DATE  ：2010/07/14                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：EAP初始化EAP控制块                                         *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_Core_AuthenticatePhase                                 *
****************************************************************************/
VOID PPP_EAP_Init(PPPINFO_S *pstPppInfo)
{
    PPPEAPINFO_S *pstEapInfo = NULL;
    PPPCONFIGINFO_S *pstConfig = NULL;

    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_104);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_Init: pstPppInfo=NULL");
        return;
    }

    pstEapInfo = pstPppInfo->pstEapInfo;
    pstConfig = pstPppInfo->pstUsedConfigInfo;
    if ((NULL == pstEapInfo) || (NULL == pstConfig))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_105);
        VOS_DBGASSERT(NULL != pstEapInfo);
        VOS_DBGASSERT(NULL != pstConfig);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_Init: pstEapInfo=NULL or pstConfig=NULL");
        return;
    }

    PPP_MemSet((VOID*)pstEapInfo, 0, sizeof(PPPEAPINFO_S));

    pstEapInfo->pstPppInfo = pstPppInfo;
    pstEapInfo->ucUsed = 1;
    pstEapInfo->ucFirstFlag = VOS_TRUE;


    pstEapInfo->ulTimeOutTime  = pstConfig->ulNegTimeOut;

    pstEapInfo->ucState = EAP_STATE_INITIAL;

    /*输出事件调试信息*/
    EAP_Debug_Event(pstPppInfo, EAP_INITIALIZATION);

    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：EAP接收外部事件.事件包括：ServerUp、Down                   *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                ulCmd:命令字, 可以为如下值:                                *
*                EAP_EVENT_SERVERLOWERUP:对端下层UP                         *
*                EAP_EVENT_LOWERDOWN:下层DOWN                               *
*                pPara:事件的参数, 为NULL                                   *
* OUTPUT       ：                                                           *
* RETURN       ：NULL                                                       *
* CALLED BY    ：PPP_Core_ReceiveEventFromShell                             *
****************************************************************************/
VOID PPP_EAP_ReceiveEventFromCore (PPPINFO_S *pstPppInfo, ULONG ulCmd, CHAR *pPara)
{
    if (pstPppInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_106);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                       "PPP_EAP_ReceiveEventFromCore: pstPppInfo=NULL");
        return;
    }

    switch (ulCmd)
    {
        case EAP_EVENT_SERVERLOWERUP:
            PPP_EAP_ServerLowerUp(pstPppInfo);
            break;

        case EAP_EVENT_LOWERDOWN:
            PPP_EAP_LowerDown(pstPppInfo);
            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_107);
            /*输出错误调试信息*/
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                         "EAP Receive UNKNOWN Event!");
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：分配EAP内存，挂到EAP控制块下面                             *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstEapInfo:EAP控制块指针                                   *
* OUTPUT       ：分配EAP内存，挂到EAP控制块下面pstChapInfo->pucEAP          *
*                EAP长度放入pstChapInfo->usEAPLen                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_EAP_ServerLowerUp                                     *
****************************************************************************/
ULONG PPP_EAP_MallocEAP(PPPEAPINFO_S *pstEapInfo)
{
    UCHAR *pucEAP = NULL;
    PPPINFO_S *pstPppInfo = NULL;
    UCHAR ucEapRequestID = 0;
    ULONG ulRand = 0;

    pstPppInfo = pstEapInfo->pstPppInfo;
    if(NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_108);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_MallocEAP pstPppInfo is NULL!");
        return VOS_ERR;
    }

    if (NULL == pstEapInfo->pucEAP)
    {
        pucEAP = (UCHAR *)PPP_Malloc(EAP_PAYLOAD_MAX_LEN);
        if(NULL == pucEAP)
        {
            /*输出调试信息*/
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                         "PPP_EAP_MallocEAP Failed!");
            PPP_DBG_ERR_CNT(PPP_PHERR_109);
            return VOS_ERR;
        }
        PPP_MemSet(pucEAP, 0, EAP_PAYLOAD_MAX_LEN);
    }
    else
    {
        /*输出调试信息*/
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_MallocEAP pstEapInfo->pucEAP != NULL!");
        PPP_DBG_ERR_CNT(PPP_PHERR_110);
        return VOS_ERR;
    }

    /* 第一次申请EAP,必须构造EAP */
    /* Code */
    *pucEAP = EAP_PACKET_CODE_REQUEST;
    /* Identifier */
    /* Identity 生成采用2-255的随机数 */
    (VOID)CRYPT_random((UCHAR*)&ulRand, (SEC_UINT32)sizeof(ULONG));
    ucEapRequestID = (UCHAR)(ulRand % 254 +2);
    *(pucEAP + EAP_ID_OFFSET) = ucEapRequestID;
    /* Length */
    *(VOS_UINT16 *)(pucEAP + EAP_LEN_OFFSET) = VOS_NTOHS(EAP_MSG_MIN_LEN + 1);
    /* Type */
    *(pucEAP + EAP_TYPE_OFFSET) = EAP_IDENTITY;

    pstEapInfo->usEAPLen = EAP_MSG_MIN_LEN + 1;
    pstEapInfo->ucEapRequestID = ucEapRequestID;

    /* 将EAP挂到EAP控制块下 */
    pstEapInfo->pucEAP = pucEAP;

    return VOS_OK;
}

/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：填充eap，挂到EAP控制块下面                                 *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstEapInfo:EAP控制块指针                                   *
* OUTPUT       ：分配EAP内存，挂到EAP控制块下面pstChapInfo->pucEAP          *
*                EAP长度放入pstChapInfo->usEAPLen                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_EAP_ServerLowerUp                                     *
****************************************************************************/
ULONG PPP_EAP_FillEAPPayload(PPPEAPINFO_S *pstEapInfo,
                             PPP_EAPPAYLOAD_S *pstEAPPayload,
                             UCHAR ucEAPCode)
{
    ULONG ulRand = 0;

    if ((NULL == pstEapInfo) || (NULL == pstEAPPayload))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_MallocEAP input is NULL!");
        PPP_DBG_ERR_CNT(PPP_PHERR_111);
        return VOS_ERR;
    }

    /* Code */
    pstEAPPayload->ucEAPCode = ucEAPCode;

    /* Code */
    if (EAP_PACKET_CODE_REQUEST == ucEAPCode)
    {
        /* Identifier */
        /* Identity 生成采用2-255的随机数 */
        (VOID)CRYPT_random((UCHAR*)&ulRand, (SEC_UINT32)sizeof(ULONG));
        pstEAPPayload->ucEAPID = (UCHAR)(ulRand % 254 +2);
        pstEapInfo->usEAPLen = (EAP_MSG_MIN_LEN + 1);
        /* Length */
        pstEAPPayload->usEAPLen = VOS_NTOHS(EAP_MSG_MIN_LEN + 1);
        /* Type */
        pstEAPPayload->ucEAPType = EAP_IDENTITY;
    }
    else
    {
        /* Identifier */
        pstEAPPayload->ucEAPID = pstEapInfo->ucEapRequestID;
        pstEapInfo->usEAPLen = (EAP_MSG_MIN_LEN);
        /* Length */
        pstEAPPayload->usEAPLen = VOS_NTOHS(EAP_MSG_MIN_LEN);
    }



    return VOS_OK;
}

/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：开始重认证流程                                             *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：                                                           *
****************************************************************************/
VOID PPP_EAP_StartReAuth(ULONG ulRpIndex)
{
    PPPINFO_S *pstPppInfo = NULL;
    PPPEAPINFO_S *pstEapInfo = NULL;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n-------enter PPP_EAP_StartReAuth--------");
    PPP_DBG_OK_CNT(PPP_PHOK_840);

    /*获取PPP控制块*/
    GETPPPINFOPTRBYRP(pstPppInfo, ulRpIndex)
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_112);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\nPPP PPP_EAP_StartReAuth: User [%d ]isn't exist!",
                     ulRpIndex);
        return;
    }

    pstEapInfo = pstPppInfo->pstEapInfo;
    if (NULL == pstPppInfo->pstEapInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_113);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\nPPP PPP_EAP_StartReAuth: eapinfo null");
        return;
    }

    /* 判断阶段状态是否正确 */
    if ((pstPppInfo->usPhase != (USHORT)PPP_PHASE_NETWORK)
        && (pstPppInfo->usPhase != (USHORT)PPP_PHASE_AUTHENTICATE))
    {
        /* 输出debug信息 */
        PPP_DBG_ERR_CNT(PPP_PHERR_114);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\nPPP PPP_EAP_StartReAuth: PHASE[%u] err!",
                     pstPppInfo->usPhase);
        return;
    }

    /* 通知diam auth删除DER控制块 */
    (VOID)Diam_AuthPPPRenegoRelCB(pstPppInfo->ulRPIndex);

    if (pstPppInfo->pstEapInfo != NULL)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_841);
        /* 设置阶段为auth */
        pstPppInfo->usPhase = (USHORT)PPP_PHASE_AUTHENTICATE;
        M_SET_NEWPHASE(pstPppInfo, PPP_SNMP_PERF_PHASE_AUTH);
        /* 将vsncp都down掉 */
        PPP_VSNCP_ClearALL(pstPppInfo);
        PPP_MemSet(pstPppInfo->pstEapInfo, 0, sizeof(PPPEAPINFO_S));
        /* 初始化EAP控制块 */
        PPP_EAP_Init(pstPppInfo);

        pstEapInfo->ucReAuthFlag = VOS_TRUE;

        /* 向EAP发送消息,触发EAP开始协商 */
        PPP_EAP_ReceiveEventFromCore(pstPppInfo, EAP_EVENT_SERVERLOWERUP, NULL);
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/09                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：EAP Server 端LowerUp,由我端向对端发送EAP REQ请求identity   *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_EAP_ReceiveEventFromCore                               *
****************************************************************************/
VOID PPP_EAP_ServerLowerUp(PPPINFO_S *pstPppInfo)
{
    PPPEAPINFO_S *pstEapInfo = NULL;

    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_115);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ServerLowerUp: pstPppInfo=NULL");
        return;
    }

    pstEapInfo = pstPppInfo->pstEapInfo;
    if (NULL == pstEapInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_116);
        VOS_DBGASSERT(NULL != pstEapInfo);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ServerLowerUp: pstEapInfo=NULL or pstConfig=NULL");
        return;
    }

    pstEapInfo->ulReqTransmits = 0;
    /* 将需要构造eap的标志位置位 */
    pstEapInfo->ucRequestforIdentity = 1;

    /* 输出事件调试信息 */
    EAP_Debug_Event(pstPppInfo, EAP_SERVERLOWERUP);

    /* 分配EAP内存，挂到EAP控制块下面 */
    if (VOS_ERR == PPP_EAP_MallocEAP(pstEapInfo))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ServerLowerUp: PPP_EAP_MallocEAP FAIL");
        PPP_DBG_ERR_CNT(PPP_PHERR_117);
        return;
    }

    /* EAP 标志位 1:Success  2:Fail  0:request */
    pstEapInfo->ucEAPFlag = 0;

    /* 送出EAP request for identity */
    PPP_EAP_SendEAP(pstPppInfo, EAP_STATE_SEND_REQUEST_FOR_IDENTITY);
    PPP_DBG_OK_CNT(PPP_PHOK_842);

    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：PPP_EAP_LowerDown                                          *
*                进入EAP_STATE_SERVER_INITIAL状态                           *
*                同时删除定时器                                             *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_EAP_ReceiveEventFromCore                               *
****************************************************************************/
VOID PPP_EAP_LowerDown(PPPINFO_S *pstPppInfo)
{
    PPPEAPINFO_S *pstEapInfo = NULL;

    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_118);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_LowerDown: pstPppInfo=NULL");
        return;
    }

    pstEapInfo = pstPppInfo->pstEapInfo;
    if (NULL == pstEapInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_119);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_LowerDown: pstEapInfo=NULL");
        return;
    }

    /* 输出事件调试信息 */
    EAP_Debug_Event(pstPppInfo, EAP_LOWERDOWN);

    /* 删除定时器 */
    PPP_EAP_DeleteTimer(pstPppInfo);

    /* 输出调试信息 */
    EAP_Debug_StateChange(pstPppInfo, EAP_STATE_INITIAL, EAP_SERVER_STATE);

    if (NULL != pstEapInfo->pucEAP)
    {
        PPP_Free(pstEapInfo->pucEAP);
        pstEapInfo->pucEAP = NULL;
    }

    /* 改变状态 */
    pstEapInfo->ucState = EAP_STATE_INITIAL;
    PPP_DBG_OK_CNT(PPP_PHOK_843);

    return;
}


/****************************************************************************
* CREATE DATE  ：2013/08/27                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：分配256byte usernmae                                       *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：                                                           *
****************************************************************************/
UCHAR* PPP_EAP_MallocUserName()
{
    UCHAR *pstUserName = NULL;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_EAP_MallocUserName: enter g_ulUserName256byteNum(%u)!",
                 g_ulUserName256byteNum);

    if (g_ulUserName256byteNum >= PPP_EAP_USER_NAME_256BYTE_MAX_NUM)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_120);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_EAP_MallocUserName: g_ulUserName256byteNum[%u] > %u",
                     g_ulUserName256byteNum, PPP_EAP_USER_NAME_256BYTE_MAX_NUM);
        return NULL;
    }

    pstUserName = PPP_Malloc(PPP_EAP_USER_NAME_256BYTE);
    if (NULL == pstUserName)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_121);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_EAP_MallocUserName: PPP_Malloc fail!");
        return NULL;
    }

    VOS_MemSet(pstUserName, 0, PPP_EAP_USER_NAME_256BYTE);

    PPP_DBG_OK_CNT(PPP_PHOK_844);
    g_ulUserName256byteNum++;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_EAP_MallocUserName: success g_ulUserName256byteNum(%u)!",
                 g_ulUserName256byteNum);

    return pstUserName;
}


/****************************************************************************
* CREATE DATE  ：2013/08/27                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：释放256byte usernmae                                       *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：                                                           *
****************************************************************************/
VOID PPP_EAP_FreeUserName(UCHAR *pstUserName)
{
    if (NULL == pstUserName)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_122);
        return;
    }

    PPP_Free(pstUserName);
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_EAP_FreeUserName: enter g_ulUserName256byteNum(%u)!",
                 g_ulUserName256byteNum);

    if (g_ulUserName256byteNum > 0)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_845);
        g_ulUserName256byteNum--;
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_846);
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_EAP_FreeUserName: success g_ulUserName256byteNum(%u)!",
                 g_ulUserName256byteNum);
    return;
}



/****************************************************************************
* CREATE DATE  ：2013/08/27                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：构造usernmae                                               *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：                                                           *
****************************************************************************/
VOID PPP_EAP_ConstructUserName(PPPINFO_S *pstPppInfo)
{
    IMSI_S *pstIMSI = NULL;
    ULONG ulIndex = 0;
    UCHAR ucMncLen = HSGW_MNC_LENTH_DEFAULT;
    UCHAR aucMnId[DIAM_AUTH_IMSI_LEN * 2 + 1] = {0};


    pstIMSI = &(pstPppInfo->stIMSI);
    ulIndex = 100 * pstIMSI->IMSI_ID1 + 10 * pstIMSI->IMSI_ID2 + pstIMSI->IMSI_ID3;
    if (ulIndex < M_HSGW_MNC_LENGTH_TBL_MAX_TUPLE_NUM)
    {
        ucMncLen = g_aucHsgwMncLength[ulIndex];
    }

    /* 将IMSI转换为字符串 */
    PPP_MemSet(aucMnId, 0, (DIAM_AUTH_IMSI_LEN * 2 + 1));
    ImsiToString(pstPppInfo->stIMSI, (CHAR *)aucMnId);
    /* 按照协议23-003生成user name
       The result will be a root NAI of the form:
       "0<IMSI>@nai.epc.mnc<MNC>.mcc<MCC>.3gppnetwork.org" for EAP AKA authentication
       "6<IMSI>@nai.epc.mnc<MNC>.mcc<MCC>.3gppnetwork.org" for EAP AKA' authentication
       For example, if the IMSI is 234150999999999 (MCC = 234, MNC = 15),
       the root NAI then takes the form as 0234150999999999@nai.epc.mnc015.mcc234.3gppnetwork.org
       for EAP AKA authentication,
       and takes the form as 6234150999999999@nai.epc.mnc015.mcc234.3gppnetwork.org
       for EAP AKA' authentication.
    */

    if (HSGW_MNC_LENTH_DEFAULT != ucMncLen)
    {
        VOS_sprintf((CHAR *)pstPppInfo->ucNAI,
                    "6%s@nai.epc.mnc%d%d%d.mcc%d%d%d.3gppnetwork.org",
                    aucMnId,
                    pstIMSI->IMSI_ID4, pstIMSI->IMSI_ID5, pstIMSI->IMSI_ID6,
                    pstIMSI->IMSI_ID1, pstIMSI->IMSI_ID2, pstIMSI->IMSI_ID3);
    }
    else
    {
        VOS_sprintf((CHAR *)pstPppInfo->ucNAI,
                    "6%s@nai.epc.mnc%d%d%d.mcc%d%d%d.3gppnetwork.org",
                    aucMnId,
                    0, pstIMSI->IMSI_ID4, pstIMSI->IMSI_ID5,
                    pstIMSI->IMSI_ID1, pstIMSI->IMSI_ID2, pstIMSI->IMSI_ID3);
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                  "\r\n PPP_EAP_ConstructUserName: DER Username(%s)!",
                  pstPppInfo->ucNAI);
    return;

}


/****************************************************************************
* CREATE DATE  ：2013/08/27                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：保存 usernmae                                              *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：                                                           *
****************************************************************************/
ULONG PPP_EAP_SaveUserName(PPPINFO_S *pstPppInfo, UCHAR *pstUserName, UCHAR ucUserNameLen,
                           UCHAR ucIDRspFlag)
{
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    SDB_RETURNCODE_E enRetCode = SDB_RECORD_NOT_EXIST;

    enRetCode = SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, (UCHAR **)&pstRpContext);
    if ((SDB_SUCCESS != enRetCode) || (VOS_NULL_PTR == pstRpContext))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_123);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_EAP_SaveUserName: call SDB_GetRpContextByIndex failed! index[%u]",
                     pstPppInfo->ulRPIndex);
        return VOS_ERR;
    }

    /* 如果是重协商，并且已经获取到username，则不需要再次保存了 */
    if ((VOS_TRUE == ucIDRspFlag)
        && ((pstRpContext->pstUsername != NULL) || (pstPppInfo->ucNAI[0])))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_847);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_EAP_SaveUserName: renego eap!");
        return VOS_OK;
    }

    /* 如果EAP成功过，则不需要再次保存了 */
    if (VOS_TRUE == pstPppInfo->bEAPAuthFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_848);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_EAP_SaveUserName: renego bEAPAuthFlag[%u]!",
                     pstPppInfo->bEAPAuthFlag);
        return VOS_OK;
    }


    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_EAP_SaveUserName: ucUserNameLen[%u]!", ucUserNameLen);

    /* 保存username */
    if (ucUserNameLen > DIAM_AUTH_NAI_MAX_LEN)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_849);

        if (NULL == pstRpContext->pstUsername)
        {
            pstRpContext->pstUsername = PPP_EAP_MallocUserName();
            if (NULL == pstRpContext->pstUsername)
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_124);
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                             "\r\n PPP_EAP_SaveUserName: PPP_EAP_MallocUserName fail!");
                return VOS_ERR;
            }
        }

        PPP_MemSet(pstRpContext->pstUsername, 0, (DIAM_AUTH_USERNAME_MAX_LEN + 1));
        VOS_MemCpy(pstRpContext->pstUsername, pstUserName, ucUserNameLen);
        /* 如果小于63的username有值，需要清零 */
        if (pstPppInfo->ucNAI[0])
        {
            PPP_MemSet(pstPppInfo->ucNAI, 0, (A11_MAX_NAI_LENGTH + 1));
        }
    }
    else if (ucUserNameLen > 0)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_850);
        PPP_MemSet(pstPppInfo->ucNAI, 0, (A11_MAX_NAI_LENGTH + 1));
        VOS_MemCpy(pstPppInfo->ucNAI, pstUserName, ucUserNameLen);
        /* 如果大于63的username有值，需要释放内存 */
        if (pstRpContext->pstUsername != NULL)
        {
            PPP_EAP_FreeUserName(pstRpContext->pstUsername);
            pstRpContext->pstUsername = NULL;
        }
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_851);
    }

    return VOS_OK;
}

/****************************************************************************
* CREATE DATE  ：2013/08/27                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：获取usernmae                                               *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：                                                           *
****************************************************************************/
ULONG PPP_EAP_GetUsername(UCHAR *pstUserName, PPPINFO_S *pstPppInfo)
{
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    SDB_RETURNCODE_E enRetCode = SDB_RECORD_NOT_EXIST;


    enRetCode = SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, (UCHAR **)&pstRpContext);
    if ((SDB_SUCCESS != enRetCode) || (VOS_NULL_PTR == pstRpContext))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_852);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_EAP_GetUsername: call SDB_GetRpContextByIndex failed! index[%u]",
                     pstPppInfo->ulRPIndex);
    }

    if ((pstRpContext != NULL)
        && (pstRpContext->pstUsername != NULL))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_853);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_EAP_GetUsername: 256username[%s]",
                     pstRpContext->pstUsername);
        VOS_MemCpy(pstUserName, pstRpContext->pstUsername, DIAM_AUTH_USERNAME_MAX_LEN);
    }
    else if (pstPppInfo->ucNAI[0])
    {
        PPP_DBG_OK_CNT(PPP_PHOK_854);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_EAP_GetUsername: ucNAI[%s]",
                     pstPppInfo->ucNAI);
        VOS_MemCpy(pstUserName, pstPppInfo->ucNAI, A11_MAX_NAI_LENGTH);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_125);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n err: PPP_EAP_GetUsername: no username !![%u]",
                     pstPppInfo->ulRPIndex);
        return VOS_ERR;
    }

    return VOS_OK;
}

/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：EAP收到Eap 数据包, 分析报文头并作相应处理                  *
*                pHead:存放报文内存的头指针包括协议号, 应负责释放这段内存   *
*                pPacket:报文头位置                                         *
*                ulLen:报文长度                                             *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_Core_ReceivePacketFromShell                            *
****************************************************************************/
VOID PPP_EAP_ReceivePacket(PPPINFO_S *pstPppInfo, UCHAR* pHead, UCHAR* pPacket, ULONG ulLen)
{
    PPPEAPINFO_S *pstEapInfo = NULL;
    UCHAR ucCode = 0;
    UCHAR ucId = 0;
    USHORT usCiLen = 0;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n-------enter PPP_EAP_ReceivePacket--------");

    if (NULL == pPacket)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_126);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceivePacket: pPacket=NULL");
        return;
    }

    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_127);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceivePacket: pstPppInfo=NULL");
        return;
    }

    pstEapInfo = pstPppInfo->pstEapInfo;
    if (NULL == pstEapInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_128);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceivePacket: pstEapInfo=NULL");
        return;
    }

    /* 输出事件调试信息 */
    EAP_Debug_Packet(pstPppInfo, pPacket, ulLen, PPP_EAP, 1);

    /* 分析报文头(ucCode,ucId, length) */
    /* 如果报文包太短则丢弃 */
    if (ulLen < FSM_HDRLEN)
    {
        /*输出错误调试信息*/
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceivePacket: Too short packet(%lu)",
                     ulLen);
        PPP_DBG_ERR_CNT(PPP_PHERR_129);
        return;
    }

    /* 获得报文中字段值, 并移动报文指针 */
    PPP_GET_EAP_CODE(ucCode, pPacket);
    PPP_GET_EAP_ID(ucId, pPacket);
    PPP_GET_EAP_LEN(usCiLen, pPacket);

    if (usCiLen <= EAP_HEADERLEN)
    {
        /*输出错误调试信息*/
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceivePacket: Too short EAP packet(%lu)",
                     usCiLen);
        PPP_DBG_ERR_CNT(PPP_PHERR_130);
        return;
    }
    if (EAP_PACKET_CODE_RESPONSE != ucCode)
    {
        /*输出错误调试信息*/
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceivePacket: EAP packet code(%d) is not Response!",
                     ucCode);
        PPP_DBG_ERR_CNT(PPP_PHERR_131);
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_855);

    /* Payload 长度 */
    //ulCiLen -= EAP_HEADERLEN;

    /* 处理EAP response,通知diam auth进行鉴权 */
    PPP_EAP_ReceiveEAPResponse(pstPppInfo, pPacket, ucId, usCiLen);

    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：EAP收到对端的Response包, 向AAA请求验证                     *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                pPacket:   报文头位置                                      *
*                ucId:      报文ID                                          *
*                ulLen:     EAP Payload报文数据长度                         *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_EAP_ReceivePacket                                      *
****************************************************************************/
VOID PPP_EAP_ReceiveEAPResponse(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, ULONG ulLen)
{
    PPPEAPINFO_S *pstEapInfo = NULL;
    PPP_DIAM_AUTH_MSG_S *pstMsg = NULL;
    ULONG ulMsgLen = 0;
    UCHAR ucPayloadType = 0;
    SDB_RETURNCODE_E enSdbResult = SDB_SUCCESS;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = NULL;

    if ((NULL == pstPppInfo)||(NULL == pPacket))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_132);
        VOS_DBGASSERT(NULL != pstPppInfo);
        VOS_DBGASSERT(NULL != pPacket);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceiveEAPResponse: pstPppInfo=NULL or pPacket=NULL");
        return;
    }
    pstEapInfo = pstPppInfo->pstEapInfo;
    if (NULL == pstEapInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_133);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceiveEAPResponse: pstEapInfo=NULL");
        return;
    }

    /*输出事件调试信息*/
    EAP_Debug_Event(pstPppInfo, EAP_RECEIVERESPONSE);

    /* 性能统计 */
    //(*g_stPppPerfStatistic.pulChapTotal)++;

    /* ID 不匹配 */
    if (ucId != pstEapInfo->ucEapRequestID)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_34);
        /*输出错误调试信息*/
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceiveEAPResponse: unmatched ID(%d)(%d)!",
                     ucId, pstEapInfo->ucEapRequestID);
        PPP_DBG_ERR_CNT(PPP_PHERR_134);
        return;
    }

    if ((ulLen > EAP_PAYLOAD_MAX_LEN)  || (ulLen <= EAP_HEADERLEN))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_35);
        /*输出错误调试信息*/
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceiveEAPResponse: EAP Payload err(%lu)",
                     ulLen);
        PPP_DBG_ERR_CNT(PPP_PHERR_135);
        return;
    }

    /* 获取EAP报文中的Payload type */
    PPP_GET_EAP_TYPE(ucPayloadType,pPacket);

    /* 判断EAP状态 */
    if ((EAP_STATE_SEND_REQUEST_FOR_IDENTITY == pstEapInfo->ucState)
        && (EAP_IDENTITY == ucPayloadType))
    {
        if (ulLen > EAP_ID_MAX_LEN)
        {
            HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_36);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                         "\r\n PPP_EAP_ReceiveEAPResponse: EAP ID LEN(%lu) err!",
                         ulLen);
            PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);  /*释放链路*/
            PPP_DBG_ERR_CNT(PPP_PHERR_136);
            return;
        }

        /* 保存username */
        if (VOS_OK != PPP_EAP_SaveUserName(pstPppInfo, (pPacket + EAP_NAI_OFFSET), (UCHAR)(ulLen - EAP_NAI_OFFSET), VOS_TRUE))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_137);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                         "\r\n PPP_EAP_ReceiveEAPResponse : PPP_EAP_SaveUserName fail [%u]!",
                         ulLen);
            PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);  /*释放链路*/
            return;
        }

        PPP_DBG_OK_CNT(PPP_PHOK_856);
    }
    else if (EAP_STATE_SEND_REQUEST != pstEapInfo->ucState)
    {
        /* 输出错误调试信息 */
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceiveEAPResponse: EAP status(%d) err!",
                     pstEapInfo->ucState);
        PPP_DBG_ERR_CNT(PPP_PHERR_138);
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_857);

    /* 删除等待EAP Response 超时定时器 */
    if (pstEapInfo->ulRspTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstEapInfo->ulRspTimeoutID));
        pstEapInfo->ulRspTimeoutID = 0;
    }

    enSdbResult = SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, &pstRpContext);
    if ((SDB_SUCCESS != enSdbResult) || (VOS_NULL == pstRpContext))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_139);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_EAP_ReceiveEAPResponse: ulRpIdx(%d) is ERR!!pstRpContext(%x)",
                     pstPppInfo->ulRPIndex,
                     pstRpContext);
        return;
    }

    /* 分配鉴权消息内存 */
    ulMsgLen = sizeof(PPP_DIAM_AUTH_MSG_S) + ulLen;
    pstMsg = PPP_Malloc(ulMsgLen);
    if (NULL == pstMsg)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceiveEAPResponse: Malloc DIAM_AUTHREQ_S error!");
        PPP_DBG_ERR_CNT(PPP_PHERR_140);
        return;
    }
    PPP_MemSet((VOID *)pstMsg, 0, ulMsgLen);

    /* 填充EAP */
    /* 拷贝长度为payload长度 */
    /* 挂到通知鉴权消息下面 */
    VOS_MemCpy(pstMsg->aucEAP, pPacket, ulLen);
    pstMsg->usEAPlen = (VOS_UINT16)ulLen;

    pstMsg->ulMsgType  = PPP_DIAM_AAA_CREAT_REQ;
    pstMsg->ulRpIndex = pstPppInfo->ulRPIndex;
    /* 携带第一次发送服务器id */
    pstMsg->usPeerID = pstPppInfo->usPeerId;
    pstMsg->ucAAAType = pstPppInfo->ucAAAType;
    /* 下上文token id */
    pstMsg->usTokenId = pstRpContext->usTokenId;
    pstMsg->ulNowUTCInSec = pstPppInfo->ulNowUTCInSec;

    if (VOS_TRUE == pstEapInfo->ucFirstFlag)
    {
        pstMsg->ucFirstSendFlag = VOS_TRUE;
        pstEapInfo->ucFirstFlag = VOS_FALSE;
    }

    /* 拷贝state */
    if (pstEapInfo->ucStateLen <= DIAM_AUTH_STATE_LEN)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_858);
        VOS_MemCpy(pstMsg->aucState, pstEapInfo->aucState, pstEapInfo->ucStateLen);
        pstMsg->ucStateLen = pstEapInfo->ucStateLen;
    }

    /* 获取username */
    if (VOS_OK != PPP_EAP_GetUsername(pstMsg->aucUserName, pstPppInfo))
    {
        PPP_Free(pstMsg);
        PPP_DBG_ERR_CNT(PPP_PHERR_141);
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);  /*释放链路*/
        return;
    }

    /* IMSI */
    VOS_MemCpy((UCHAR *)&(pstMsg->stIMSI), (UCHAR *)&(pstPppInfo->stIMSI), sizeof(A11_IMSI_S));

    /* 输出状态转换调试信息 */
    EAP_Debug_StateChange(pstPppInfo, EAP_STATE_WAITING_AAA, EAP_SERVER_STATE);
    /* 切换状态为等待aaa */
    pstEapInfo->ucState = EAP_STATE_WAITING_AAA;

    /* 通知diam AAA进行认证 */
    PPP_EAP_SendAAAAuthReq(pstEapInfo, pstMsg, ulMsgLen);

    PPP_Free(pstMsg);
    return;
}
/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：EAP收到AAA的EAP Request包                                  *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                pstEapInfo:EAP控制块指针                                   *
*                pMsg:      AAA响应消息                                     *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_EAP_ReceivePacket                                      *
****************************************************************************/
VOID PPP_EAP_ReceiveEAPRequestFromAAA(PPPINFO_S *pstPppInfo,
                                      PPPEAPINFO_S *pstEapInfo,
                                      DIAM_AUTHRSP_S *pMsg)
{
    UCHAR *pucEAP = NULL;
    UCHAR ucId = 0;

    if ((NULL == pstEapInfo) || (NULL == pstPppInfo) || (NULL == pMsg))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_142);
        VOS_DBGASSERT(NULL != pstEapInfo);
        VOS_DBGASSERT(NULL != pstPppInfo);
        VOS_DBGASSERT(NULL != pMsg);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceiveEAPRequestFromAAA: pstEapInfo=NULL or pstPppInfo=NULL or pMsg=NULL");
        return;
    }

    /*输出事件调试信息*/
    EAP_Debug_Event(pstPppInfo, EAP_RECEIVEREQUEST_FROMAAA);

    pucEAP = pstEapInfo->pucEAP;
    /* EAP是否为空 */
    if (NULL == pucEAP)
    {
        /*输出错误调试信息*/
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                    "PPP_EAP_ReceiveEAPRequestFromAAA: pstEapInfo->pucEAP = NULL");
        PPP_DBG_ERR_CNT(PPP_PHERR_143);
        return;
    }

    if (pMsg->ulEAPLen > EAP_PAYLOAD_SEND_MAX_LEN)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_37);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                    "PPP_EAP_ReceiveEAPRequestFromAAA: ulEAPLen[%lu] ERR !",
                    pMsg->ulEAPLen);
        /* 构造eap fail */
        PPP_EAP_SendEAPFail(pstEapInfo, pstPppInfo);
        /* 向内核报EAP验证失败 */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_EAPFAILED, NULL);
        A11_PPP_TermTag(pstPppInfo->ulRPIndex, Authentication_Fail);
        PPP_DBG_ERR_CNT(PPP_PHERR_144);
        return;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_859);
    /* 性能统计 */
    //(*g_stPppPerfStatistic.pulChapTotal)++;
    VOS_MemCpy(pucEAP, pMsg->aucEAP, pMsg->ulEAPLen);

    PPP_MemSet(pstEapInfo->aucState, 0, DIAM_AUTH_STATE_LEN);

    if (pMsg->ucStateLen <= DIAM_AUTH_STATE_LEN)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_860);
        VOS_MemCpy(pstEapInfo->aucState, pMsg->aucState, pMsg->ucStateLen);
        pstEapInfo->ucStateLen = pMsg->ucStateLen;
    }

    /* 获取id */
    PPP_GET_EAP_ID(ucId, pucEAP);
    /* 保存id用于收到eap response 后检测 */
    pstEapInfo->ucEapRequestID = ucId;
    /* 保存EAP长度 */
    pstEapInfo->usEAPLen = (VOS_UINT16)pMsg->ulEAPLen;
    /* EAP 标志位 1:Success  2:Fail  0:request */
    pstEapInfo->ucEAPFlag = 0;
    pstEapInfo->ulReqTransmits = 0;
    /* 将需要构造eap的标志位置位 */
    pstEapInfo->ucRequestforIdentity = 0;

    /* 保存第一次发送服务器id */
    pstPppInfo->usPeerId = pMsg->usPeerId;

    /* 送出EAP到对端 */
    PPP_EAP_SendEAP(pstPppInfo, EAP_STATE_SEND_REQUEST);

    return;
}
/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：EAP收到AAA的EAP Success包                                  *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                pstEapInfo:EAP控制块指针                                   *
*                pMsg:      AAA响应消息                                     *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_EAP_ReceivePacket                                      *
****************************************************************************/
VOID PPP_EAP_ReceiveEAPSuccessFromAAA(PPPINFO_S *pstPppInfo,
                                      PPPEAPINFO_S *pstEapInfo,
                                      DIAM_AUTHRSP_S *pMsg)
{
    UCHAR *pucEAP = NULL;

    if ((NULL == pstEapInfo)||(NULL == pstPppInfo)||(NULL == pMsg))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_145);
        VOS_DBGASSERT(NULL != pstEapInfo);
        VOS_DBGASSERT(NULL != pstPppInfo);
        VOS_DBGASSERT(NULL != pMsg);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceiveEAPSuccessFromAAA: pstEapInfo=NULL or pstPppInfo=NULL or pMsg=NULL");
        return;
    }

    /*输出事件调试信息*/
    EAP_Debug_Event(pstPppInfo, EAP_RECEIVEREQUEST_FROMAAA);

    /* 性能统计 */
    //(*g_stPppPerfStatistic.pulChapTotal)++;
    pucEAP = pstEapInfo->pucEAP;
    /* EAP是否为空 */
    if (NULL == pucEAP)
    {
        /*输出错误调试信息*/
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                    "PPP_EAP_ReceiveEAPSuccessFromAAA: pstEapInfo->pucEAP = NULL");
        PPP_DBG_ERR_CNT(PPP_PHERR_146);
        return;
    }

    if (pMsg->ulEAPLen > EAP_PAYLOAD_SEND_MAX_LEN)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_38);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                    "PPP_EAP_ReceiveEAPSuccessFromAAA: ulEAPLen[%lu] ERR !",
                    pMsg->ulEAPLen);
        /* 构造eap fail */
        PPP_EAP_SendEAPFail(pstEapInfo, pstPppInfo);
        /* 向内核报EAP验证失败 */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_EAPFAILED, NULL);
        A11_PPP_TermTag(pstPppInfo->ulRPIndex, Authentication_Fail);
        PPP_DBG_ERR_CNT(PPP_PHERR_147);
        return;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_861);
    VOS_MemCpy(pucEAP, pMsg->aucEAP, pMsg->ulEAPLen);

    pstEapInfo->ulReqTransmits = 0;
    /* 不需要构造eap */
    pstEapInfo->ucRequestforIdentity = 0;

    /* EAP标志位 1:Success  2:Fail  0:request */
    pstEapInfo->ucEAPFlag = 1;

    /* 保存EAP长度 */
    pstEapInfo->usEAPLen = (VOS_UINT16)pMsg->ulEAPLen;

    /* state需要清零 */
    PPP_MemSet(pstEapInfo->aucState, 0, DIAM_AUTH_STATE_LEN);
    pstEapInfo->ucStateLen = 0;

    /* 保存第一次发送服务器id */
    pstPppInfo->usPeerId = pMsg->usPeerId;

    /* 送出EAP到对端 */
    PPP_EAP_SendEAP(pstPppInfo, EAP_STATE_SUCCESS);

    /* 释放EAP */
    PPP_Free(pucEAP);
    pstEapInfo->pucEAP = NULL;
    pstEapInfo->usEAPLen = 0;
    pstEapInfo->ucEapRequestID = 0;

    /* 通知CORE鉴权成功 */
    pstPppInfo->bAuthServer = VRP_NO;
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_EAPSUCCESS, (CHAR *)pMsg);

    pstPppInfo->bEAPAuthFlag = VOS_TRUE;

    return;
}
/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：EAP收到AAA的EAP Request包                                  *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                pstEapInfo:EAP控制块指针                                   *
*                pMsg:      AAA响应消息                                     *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_EAP_ReceivePacket                                      *
****************************************************************************/
VOID PPP_EAP_ReceiveEAPFailFromAAA(PPPINFO_S *pstPppInfo,
                                   PPPEAPINFO_S *pstEapInfo,
                                   DIAM_AUTHRSP_S *pMsg)
{
    UCHAR *pucEAP = NULL;

    if ((NULL == pstEapInfo) || (NULL == pstPppInfo) || (NULL == pMsg))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_148);
        VOS_DBGASSERT(NULL != pstEapInfo);
        VOS_DBGASSERT(NULL != pstPppInfo);
        VOS_DBGASSERT(NULL != pMsg);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceiveEAPFailFromAAA: pstEapInfo=NULL or pstPppInfo=NULL or pMsg=NULL");
        return;
    }

    /*输出事件调试信息*/
    EAP_Debug_Event(pstPppInfo, EAP_RECEIVEREQUEST_FROMAAA);

    /* 性能统计 */
    //(*g_stPppPerfStatistic.pulChapTotal)++;
    pucEAP = pstEapInfo->pucEAP;
    /* EAP是否为空 */
    if (NULL == pucEAP)
    {
        /*输出错误调试信息*/
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                      "PPP_EAP_ReceiveEAPFailFromAAA: pstEapInfo->pucEAP = NULL");
        PPP_DBG_ERR_CNT(PPP_PHERR_149);
        return;
    }

    if (pMsg->ulEAPLen > EAP_PAYLOAD_SEND_MAX_LEN)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_39);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                    "PPP_EAP_ReceiveEAPFailFromAAA: ulEAPLen[%lu] ERR !",
                    pMsg->ulEAPLen);
        //SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_OTHER);
        /* 构造eap fail */
        PPP_EAP_SendEAPFail(pstEapInfo, pstPppInfo);
        /* 向内核报EAP验证失败 */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_EAPFAILED, NULL);
        A11_PPP_TermTag(pstPppInfo->ulRPIndex, Authentication_Fail);
        PPP_DBG_ERR_CNT(PPP_PHERR_150);
        return;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_862);
    VOS_MemCpy(pucEAP, pMsg->aucEAP, pMsg->ulEAPLen);

    pstEapInfo->ulReqTransmits = 0;
    /* 将需要构造eap的标志位置位 */
    pstEapInfo->ucRequestforIdentity = 0;

    /* EAP 标志位 1:Success  2:Fail  0:request */
    pstEapInfo->ucEAPFlag = 2;

    /* 保存EAP长度 */
    pstEapInfo->usEAPLen = (VOS_UINT16)pMsg->ulEAPLen;


    /* 送出EAP到对端 */
    PPP_EAP_SendEAP(pstPppInfo, EAP_STATE_FAILED);

    /* 释放EAP */
    PPP_Free(pucEAP);
    pstEapInfo->pucEAP = NULL;

    /* 向内核报EAP验证失败 */
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_EAPFAILED, NULL);
    A11_PPP_TermTag(pstPppInfo->ulRPIndex, Authentication_Fail);

    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：wangyong                                                   *
* FUNCTION     ：EAP收到AAA验证结果, 进行处理                               *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                pMsg:存放验证结果                                          *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：                                                           *
****************************************************************************/
VOID PPP_EAP_ReceiveDiamAAAResult(DIAM_AUTHRSP_S *pMsg)
{
    PPPINFO_S *pstPppInfo = NULL;
    PPPEAPINFO_S *pstEapInfo = NULL;

    PPP_TRACE("\r\n---Into PPP_EAP_ReceiveDiamAAAResult---\r\n");

    /* 判断输入参数的有效性 */
    if (NULL == pMsg)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_151);
        VOS_DBGASSERT(pMsg);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceiveDiamAAAResult: Invalid input parameter");
        return;
    }

    /* 获取PPP控制块 */
    GETPPPINFOPTRBYRP(pstPppInfo, pMsg->ulSDBIndex);
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_152);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_EAP_ReceiveDiamAAAResult: User %lu isn't exist!",
                     pMsg->ulSDBIndex);
        return;
    }
    /* 获取EAP控制块 */
    pstEapInfo = pstPppInfo->pstEapInfo;
    if (NULL == pstEapInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_153);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_EAP_ReceiveDiamAAAResult: User %lu  pstEapInfo isn't exist!",
                     pMsg->ulSDBIndex);
        return;
    }

    /* 删除等待auth Response 定时器 */
    if (pstEapInfo->ulWaitAuthRspTimeID != 0)
    {
        (VOID)VOS_StopRelTimer(&pstEapInfo->ulWaitAuthRspTimeID);
        pstEapInfo->ulWaitAuthRspTimeID = 0;
    }

    /* 输出事件调试信息 */
    EAP_Debug_Event(pstPppInfo, EAP_AAARESULT);

    /* 状态与事件不符 */
    if (pstEapInfo->ucState != EAP_STATE_WAITING_AAA)
    {
        /*输出错误调试信息*/
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceiveDiamAAAResult: Illegal event %d!",
                     pstEapInfo->ucState);
        PPP_DBG_ERR_CNT(PPP_PHERR_154);
        return;
    }

    /* 此时不管是否返回成功失败，都需要刷新服务器ID */
    //pstPppInfo->usPeerId = pMsg->usPeerId;

    /* 保存username */
    if (VOS_OK != PPP_EAP_SaveUserName(pstPppInfo, pMsg->aucUsername, pMsg->ucUsernameLen, VOS_FALSE))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_155);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReceiveDiamAAAResult : PPP_EAP_SaveUserName fail [%u]!",
                     pMsg->ucUsernameLen);
        pMsg->ucResult = VOS_ERR;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_863);
    if (VOS_OK == pMsg->ucResult)
    {
        /* 性能统计 */
        //(*g_stPppPerfStatistic.pulChapSuccess)++;
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_EAP_ReceiveDiamAAAResult:ucMsgCode=%lu",
                     pMsg->ulMsgCode);

        switch (pMsg->ulMsgCode)
        {
            case EAP_PACKET_CODE_REQUEST:
                PPP_DBG_OK_CNT(PPP_PHOK_864);
                PPP_EAP_ReceiveEAPRequestFromAAA(pstPppInfo, pstEapInfo, pMsg);
                break;

            case EAP_PACKET_CODE_SUCCESS:
                PPP_DBG_OK_CNT(PPP_PHOK_865);
                PPP_EAP_ReceiveEAPSuccessFromAAA(pstPppInfo, pstEapInfo, pMsg);
                break;

            case EAP_PACKET_CODE_FAILURE:
                PPP_DBG_OK_CNT(PPP_PHOK_866);
                //SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_OTHER);
                PPP_EAP_ReceiveEAPFailFromAAA(pstPppInfo, pstEapInfo, pMsg);
                break;

            default:
                PPP_DBG_ERR_CNT(PPP_PHERR_156);
                /*输出错误调试信息*/
                PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                             "EAP Receive UNKNOWN result code[%lu]!",
                             pMsg->ulMsgCode);
                break;
        }
    }
    else
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_40);
        if (DIAM_AUTH_SRV_ERR == pMsg->ucResult)
        {
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_AAA_NO_RSP);
        }
        /* 构造eap fail */
        PPP_EAP_SendEAPFail(pstEapInfo, pstPppInfo);

        /* 向内核报EAP验证失败 */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_EAPFAILED, NULL);

        A11_PPP_TermTag(pstPppInfo->ulRPIndex, Authentication_Fail);

        PPP_DBG_ERR_CNT(PPP_PHERR_157);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPP_EAP_SendEAPFail
 功能描述  : 构造失败响应给终端
 输入参数  : PPPEAPINFO_S *pstEapInfo
             DIAM_AUTHREQ_S *pstMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月21日
    作    者   : WANGYONG
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_EAP_SendEAPFail(PPPEAPINFO_S *pstEapInfo, PPPINFO_S *pstPppInfo)
{
    PPP_TRACE("\r\n---Into PPP_EAP_SendEAPFail---\r\n");

    if ((NULL == pstEapInfo) || (NULL == pstPppInfo))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_158);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_SendEAPFail: pstEapInfo=NULL");
        return;
    }

    if (VOS_OK != PPP_EAP_FillEAPPayload(pstEapInfo,
                                         (PPP_EAPPAYLOAD_S *)pstEapInfo->pucEAP,
                                         EAP_PACKET_CODE_FAILURE))
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_SendEAPFail: PPP_EAP_FillEAPPayload fail!");
        PPP_DBG_ERR_CNT(PPP_PHERR_159);
        return;
    }

    /* EAP 标志位 1:Success  2:Fail  0:request */
    pstEapInfo->ucEAPFlag = 2;

    /* 验证未通过 */
    PPP_EAP_SendEAP(pstPppInfo, EAP_STATE_FAILED);

    PPP_DBG_OK_CNT(PPP_PHOK_867);
    return;
}

/*****************************************************************************
 函 数 名  : PPP_EAP_SendAAAAuthReq
 功能描述  : 向AAA发送鉴权请求
 输入参数  : PPPEAPINFO_S *pstEapInfo
             DIAM_AUTHREQ_S *pstMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月21日
    作    者   : WANGYONG
    修改内容   : 新生成函数
*****************************************************************************/
VOID PPP_EAP_SendAAAAuthReq(PPPEAPINFO_S *pstEapInfo, PPP_DIAM_AUTH_MSG_S *pstMsg, ULONG ulMsgLen)
{
    ULONG ulRet = 0;
    PPPINFO_S *pstPppInfo = NULL;

    PPP_TRACE("\r\n---Into PPP_EAP_SendAAAAuthReq---\r\n");
    PPP_DBG_OK_CNT(PPP_PHOK_868);

    if ((NULL == pstEapInfo) || (NULL == pstMsg))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_160);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_SendAAAAuthReq: pstEapInfo=NULL");
        return;
    }

    pstPppInfo = pstEapInfo->pstPppInfo;
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_161);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_SendAAAAuthReq: pstEapInfo->pstPppInfo=NULL");
        return;
    }

    ulRet = PPP_SendRtMsg(PPP_SELF_CSI,
                          g_ullPppDiamAuthCsi,
                          DIAMAUTH_MSG_TYPE_EAP,
                          0,
                          (UCHAR *)pstMsg,
                          ulMsgLen);
    if (VOS_OK != ulRet)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_SendAAAAuthReq: PPP_SendRtMsg Err!!");
        PPP_DBG_ERR_CNT(PPP_PHERR_162);
        return;
    }

    /* 设置超时定时器 */
    VOS_DBGASSERT(pstEapInfo->ulWaitAuthRspTimeID == 0);

    ulRet   = VOS_StartRelTimer((HTIMER)&(pstEapInfo->ulWaitAuthRspTimeID), MID_PPPC,
        EAP_WAITAAARSPTIMEOUT, pstPppInfo->ulRPIndex, PPPC_EAP_SEND_AAA_AUTH_REQ_TIMER,
        VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);
    if (ulRet != VOS_OK)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "EAP VOS_Timer_Create AAA TIMER error[%x]!",
                     ulRet);
        PPP_DBG_ERR_CNT(PPP_PHERR_163);
    }

    PPP_DBG_OK_CNT(PPP_PHOK_869);
    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：EAP向对端发出EAP                                           *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:       PPP控制块指针                            *
*                ucNewSeverStatus: 迁到到的新状态                           *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_EAP_ServerLowerUp,PPP_EAP_EAPRequestTimeout,           *
*                PPP_EAP_ServerSuccess,PPP_EAP_ReAuth                       *
****************************************************************************/
VOID PPP_EAP_SendEAP(PPPINFO_S *pstPppInfo, UCHAR ucNewSeverStatus)
{
    PPPEAPINFO_S *pstEapInfo = NULL;
    UCHAR *pHead = NULL, *pPacket = NULL;
    UCHAR *pucEapMsg = NULL;
    ULONG ulOffset = 0;
    ULONG ulErrorCode = 0;
    ULONG ulRet = 0;

    PPP_TRACE("\r\n---Into PPP_EAP_SendEAP---\r\n");
    PPP_DBG_OK_CNT(PPP_PHOK_870);

    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_SendEAP: pstPppInfo=NULL");
        PPP_DBG_ERR_CNT(PPP_PHERR_164);
        return;
    }

    pstEapInfo = pstPppInfo->pstEapInfo;
    if (NULL == pstEapInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_165);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_SendEAP: pstEapInfo=NULL");
        return;
    }

    if (NULL == pstEapInfo->pucEAP)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_166);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_SendEAP: pstEapInfo->pucEAP=NULL");
        return;
    }

    /* EAP */
    pucEapMsg = pstEapInfo->pucEAP;

    /* 预留出打PPP报文头的空间 */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* 申请内存 */
    pHead = g_ucPppSendPacketHead;
    if (NULL == pHead)
    {
        /*输出错误调试信息*/
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_SendEAP: g_ucPppSendPacketHead == NULL");
        PPP_DBG_ERR_CNT(PPP_PHERR_167);
        return;
    }

    pPacket = pHead + ulOffset;

    /* 将EAP写入报文 */
    (VOID)VOS_MemCpy((CHAR *)pPacket, pucEapMsg, (ULONG)pstEapInfo->usEAPLen);

    /*输出调试信息*/
    EAP_Debug_Packet(pstPppInfo, pPacket, pstEapInfo->usEAPLen, PPP_EAP, 0);

    /* 直接调用外壳的发送函数 */
    ulErrorCode = PPP_Shell_GetPacketFromCore((CHAR *)pstPppInfo,
                                              pHead,
                                              pPacket,
                                              pstEapInfo->usEAPLen,
                                              PPP_EAP);
    if (ulErrorCode != VOS_OK)
    {
        /*输出调试信息*/
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_SendEAP: PPP_Shell_GetPacketFromCore FAIL,resultcode(%lu)",
                     ulErrorCode);
        PPP_DBG_ERR_CNT(PPP_PHERR_168);
    }

    /* 如果为EAP request需要启动定时器 */
    if (0 == pstEapInfo->ucEAPFlag)
    {
        if (0 == pstEapInfo->ulRspTimeoutID)
        {
           /* 设置重传EAP REQUEST定时器 */
            ulRet   = VOS_StartRelTimer((HTIMER)&(pstEapInfo->ulRspTimeoutID), MID_PPPC,
                   pstEapInfo->ulTimeOutTime, pstPppInfo->ulRPIndex, PPPC_EAP_SEND_EAP_REQ_TIMER,
                   VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);
            if (ulRet != VOS_OK)
            {
               PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                            "PPP_EAP_SendEAP : EAP VOS_Timer_Create TIMER error!");
               PPP_DBG_ERR_CNT(PPP_PHERR_169);
            }
        }
        else
        {
           VOS_DBGASSERT(0);
           PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                        "PPP_EAP_SendEAP: Timer ID err!");
           PPP_DBG_ERR_CNT(PPP_PHERR_170);
        }

        /* 发送次数加1 */
        ++pstEapInfo->ulReqTransmits;
    }

    /* 输出状态转换调试信息 */
    EAP_Debug_StateChange(pstPppInfo, ucNewSeverStatus, EAP_SERVER_STATE);

    /* 改变状态 */
    pstEapInfo->ucState = ucNewSeverStatus;

    PPP_DBG_OK_CNT(PPP_PHOK_871);

    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：EAP等待发送EAP RESPONSE 超时，进行相应处理                 *
*                超过最大重传次数，向内核报EAP 验证失败                     *
*                否则再次发送EAP REQUEST                                    *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：EAP 定时器ulReqTimeoutID触发                               *
****************************************************************************/
VOS_VOID PPP_EAP_WaitEAPRspTimeout(VOS_UINT32 ulPppId)
{
    PPPINFO_S *pstPppInfo = NULL;
    PPPEAPINFO_S *pstEapInfo = NULL;

    PPP_DBG_OK_CNT(PPP_PHOK_872);

    /* 获取PPPC控制块指针 */
    GETPPPINFOPTRBYRP(pstPppInfo, ulPppId);
    if (NULL == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_WaitEAPRspTimeout: pstPppInfo == NULL");
        PPP_DBG_ERR_CNT(PPP_PHERR_171);
        return;
    }
    /* 获取EAP控制块指针 */
    pstEapInfo = pstPppInfo->pstEapInfo;
    if (NULL == pstEapInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_WaitEAPRspTimeout: pstEapInfo == NULL");
        PPP_DBG_ERR_CNT(PPP_PHERR_172);
        return;
    }

    if (1 == pstEapInfo->ucRequestforIdentity)
    {
        /* 输出事件调试信息 */
        EAP_Debug_Event(pstPppInfo, EAP_REQUESTTIMEOUT_FORID);
        PPP_DBG_OK_CNT(PPP_PHOK_873);
    }
    else
    {
        /* 输出事件调试信息 */
        EAP_Debug_Event(pstPppInfo, EAP_REQUESTTIMEOUT);
        PPP_DBG_OK_CNT(PPP_PHOK_874);
    }

    /* 清除定时器id */
    pstEapInfo->ulRspTimeoutID = 0;

    if ((pstEapInfo->ucState != EAP_STATE_SEND_REQUEST_FOR_IDENTITY)
        && (pstEapInfo->ucState != EAP_STATE_SEND_REQUEST))
    {
        /* 输出错误调试信息 */
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_WaitEAPRspTimeout: Illegal Status(%d)!",
                     pstEapInfo->ucState);
        PPP_DBG_ERR_CNT(PPP_PHERR_173);
        return;
    }

    /* 输出错误调试信息 */
    PPP_TRACE("PPP_EAP_WaitEAPRspTimeout : Send EAP Request No. %lu !",
              pstEapInfo->ulReqTransmits);

    if (pstEapInfo->ulReqTransmits >= PPP_DEFMAXCONFREQS)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_41);
        pstEapInfo->ulReqTransmits = 0;

        /* 输出状态转换调试信息 */
        EAP_Debug_StateChange(pstPppInfo, EAP_STATE_FAILED, EAP_SERVER_STATE);
        /* 改变状态 */
        pstEapInfo->ucState = EAP_STATE_FAILED;
        /* 删除定时器 */
        PPP_EAP_DeleteTimer(pstPppInfo);

        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_MS_NO_RSP);

        /* 向内核报EAP 验证失败 */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_EAPFAILED, NULL);

        pstPppInfo->ucFSMFailType = FSM_ALARM_AUTH_MS_NO_RSP;

        PPP_DBG_ERR_CNT(PPP_PHERR_174);

        return;
    }

    /* 重传 EAP Request */
    PPP_EAP_SendEAP(pstPppInfo, pstEapInfo->ucState);
    PPP_DBG_OK_CNT(PPP_PHOK_875);

    return;
}

/*****************************************************************************
 函 数 名  : PPP_EAP_AuthRspTimeout
 功能描述  : EAP等待AAA验证结果超时
 输入参数  : VOID *pMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月21日
    作    者   : WANGYONG
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPP_EAP_WaitAuthRspTimeout(VOS_UINT32 ulPppId)
{
    PPPINFO_S *pstPppInfo = NULL;
    PPPEAPINFO_S *pstEapInfo = NULL;
    ULONG ulIdxTmp = (ULONG)ulPppId;

    PPP_TRACE("\r\n---Into PPP_EAP_WaitAuthRspTimeout---\r\n");
    PPP_DBG_OK_CNT(PPP_PHOK_876);

    /* 获取PPP控制块 */
    GETPPPINFOPTRBYRP(pstPppInfo, ulPppId);
    if (NULL == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_WaitAuthRspTimeout: ulIdxTmp(%d)pstPppInfo=NULL",
                     ulIdxTmp);
        PPP_DBG_ERR_CNT(PPP_PHERR_175);
        return;
    }
    /* 获取EAP控制块 */
    pstEapInfo = (PPPEAPINFO_S *)pstPppInfo->pstEapInfo;
    if (NULL == pstEapInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_WaitAuthRspTimeout: ulIdxTmp(%d)pstEapInfo=NULL",
                     ulIdxTmp);
        PPP_DBG_ERR_CNT(PPP_PHERR_176);
        return;
    }
    /* 通过EAP控制块获取PPP控制块 */
    pstPppInfo = pstEapInfo->pstPppInfo;
    if(NULL == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_WaitAuthRspTimeout: ulIdxTmp(%d)pstEapInfo->pstPppInfo=NULL",
                     ulIdxTmp);
        PPP_DBG_ERR_CNT(PPP_PHERR_177);
        return;
    }
    /* 状态是否为等待AAA */
    if(pstEapInfo->ucState != EAP_STATE_WAITING_AAA)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_WaitAuthRspTimeout: ulIdxTmp(%d)pstEapInfo->ucState(%d)",
                     ulIdxTmp, pstEapInfo->ucState);
        PPP_DBG_ERR_CNT(PPP_PHERR_178);
        return;
    }

    SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_AAA_NO_RSP);

    /* 输出事件调试信息 */
    EAP_Debug_Event(pstPppInfo, EAP_AAARESULTTIMEOUT);

    /* 清除定时器 */
    pstEapInfo->ulWaitAuthRspTimeID = 0;

    /* 认证失败 */
    PPP_EAP_AAAAuthFailed(pstEapInfo);
    PPP_DBG_OK_CNT(PPP_PHOK_877);

    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：EAP定时发起重认证                                          *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：                                                           *
****************************************************************************/
VOID PPP_EAP_ReAUTHTimeout(VOID *ulIndex)
{
    PPPINFO_S *pstPppInfo = NULL;
    PPPEAPINFO_S *pstEapInfo = NULL;

    PPP_DBG_OK_CNT(PPP_PHOK_878);

    /* 获取PPP控制块 */
    GETPPPINFOPTRBYRP(pstPppInfo, (ULONG)ulIndex);
    if (NULL == pstPppInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReAUTHTimeout: pstPppInfo=NULL");
        PPP_DBG_ERR_CNT(PPP_PHERR_179);
        return;
    }

    pstEapInfo = pstPppInfo->pstEapInfo;
    if (NULL == pstEapInfo)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReAUTHTimeout: pstEapInfo=NULL");
        PPP_DBG_ERR_CNT(PPP_PHERR_180);
        return;
    }

    /* 输出事件调试信息 */
    EAP_Debug_Event(pstPppInfo, EAP_REAUTH);

    /* 状态是否为EAP 成功 */
    if (pstEapInfo->ucState != EAP_STATE_SUCCESS)
    {
        /*输出错误调试信息*/
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_ReAUTHTimeout: Illegal status!");
        PPP_DBG_ERR_CNT(PPP_PHERR_181);
        return;
    }

    /* 清除定时器 */
    (VOID)VOS_StopRelTimer(&(pstEapInfo->ulRaAUTHTimerID));
    pstEapInfo->ulRaAUTHTimerID = 0;

    /* 向内核报EAP 重新验证 */
    //PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_EAPREAUTH, NULL);

    /* 重新发送 */
    PPP_EAP_StartReAuth((ULONG)ulIndex);

    PPP_DBG_OK_CNT(PPP_PHOK_879);
    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/09                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：删除定时器                                                 *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：                                                           *
****************************************************************************/
VOID PPP_EAP_DeleteTimer(PPPINFO_S *pstPppInfo)
{
    PPPEAPINFO_S *pstEapInfo = (PPPEAPINFO_S *)pstPppInfo->pstEapInfo;

    if (NULL == pstEapInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_182);
        return;
    }
    /* 删除等待EAP response定时器 */
    if (pstEapInfo->ulRspTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&pstEapInfo->ulRspTimeoutID);
        pstEapInfo->ulRspTimeoutID = 0;
    }

    /* 删除等待auth Response 定时器 */
    if (pstEapInfo->ulWaitAuthRspTimeID != 0)
    {
        (VOID)VOS_StopRelTimer(&pstEapInfo->ulWaitAuthRspTimeID);
        pstEapInfo->ulWaitAuthRspTimeID = 0;
    }
    /* 删除等待 reauth 定时器 */
    if (pstEapInfo->ulRaAUTHTimerID != 0)
    {
        (VOID)VOS_StopRelTimer(&pstEapInfo->ulRaAUTHTimerID);
        pstEapInfo->ulRaAUTHTimerID = 0;
    }

    return;
}
/****************************************************************************
* CREATE DATE  ：2010/07/12                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：EAP收到对端的Response包, 向AAA请求验证                     *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                pPacket:   报文头位置                                      *
*                ucId:      报文ID                                          *
*                ulLen:     EAP Payload报文数据长度                         *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：PPP_EAP_ReceivePacket                                      *
****************************************************************************/
VOID PPP_EAP_NotifyDiamAuthRelease(PPPINFO_S *pstPppInfo)
{
    PPP_DIAM_AUTH_MSG_S *pstMsg = NULL;
    ULONG ulMsgLen = 0;
    ULONG ulRet = 0;
    SDB_PDSN_RP_CONTEXT_S *pstRpContext = VOS_NULL_PTR;
    SDB_RETURNCODE_E enRetCode = SDB_RECORD_NOT_EXIST;

    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_183);
        VOS_DBGASSERT(NULL != pstPppInfo);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_NotifyDiamAuthRelease: pstPppInfo=NULL or pPacket=NULL");
        return;
    }

    /* 分配鉴权消息内存 */
    ulMsgLen = sizeof(PPP_DIAM_AUTH_MSG_S);
    pstMsg = PPP_Malloc(ulMsgLen);
    if (NULL == pstMsg)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_NotifyDiamAuthRelease: Malloc DIAM_AUTHREQ_S error!");
        PPP_DBG_ERR_CNT(PPP_PHERR_184);
        return;
    }
    PPP_MemSet((VOID *)pstMsg, 0, ulMsgLen);

    pstMsg->ulMsgType  = PPP_DIAM_AAA_RELEASE_REQ;
    pstMsg->ulRpIndex = pstPppInfo->ulRPIndex;
    /* 携带第一次发送服务器id */
    pstMsg->usPeerID = pstPppInfo->usPeerId;
    pstMsg->ucAAAType = pstPppInfo->ucAAAType;
    /* 下上文token id */
    pstMsg->usTokenId = pstPppInfo->usTokenId;
    pstMsg->ulNowUTCInSec = pstPppInfo->ulNowUTCInSec;

    enRetCode = SDB_GetRpContextByIndex(pstPppInfo->ulRPIndex, (UCHAR **)&pstRpContext);
    if ((SDB_SUCCESS != enRetCode) || (VOS_NULL_PTR == pstRpContext))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_880);
        pstMsg->ulReleaseCode = pstPppInfo->ucPppRleaseCode;
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n PPP_EAP_NotifyDiamAuthRelease: call SDB_GetRpContextByIndex failed! index[%u]releasecode[%u]",
                     pstPppInfo->ulRPIndex, pstPppInfo->ucPppRleaseCode);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_881);
        pstMsg->ulReleaseCode = (pstRpContext->ulReleaseCode) ? (pstRpContext->ulReleaseCode) :(pstPppInfo->ucPppRleaseCode);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_EAP_NotifyDiamAuthRelease:pstRpContext->ulReleaseCode = %lu!,pstPppInfo->ucPppRleaseCode =%lu",
                     pstRpContext->ulReleaseCode, pstPppInfo->ucPppRleaseCode);
    }

    /* 获取username */
    if ((NULL != pstRpContext)
        && (NULL != pstRpContext->pstEhrpdUserInfo))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_882);
        pstMsg->aucUserName[0] = '6';
        VOS_MemCpy((pstMsg->aucUserName + 1),
                   pstRpContext->pstEhrpdUserInfo->aucMnId,
                   DIAM_AUTH_MNID_MAX_LENGTH);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_185);
        if (VOS_OK != PPP_EAP_GetUsername(pstMsg->aucUserName, pstPppInfo))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_186);
        }
    }

    /* IMSI */
    VOS_MemCpy((UCHAR *)&(pstMsg->stIMSI), (UCHAR *)&(pstPppInfo->stIMSI), sizeof(A11_IMSI_S));

    /* 如果是动态aaa，需要填充host，realm */
    if (M_DIAMAUTH_DYNAAA_AAA == pstPppInfo->ucAAAType)
    {
        ulRet = Diam_AUTHGetDynAAAInfoByIndex(pstPppInfo->usPeerId, pstMsg->aucAAAHost, pstMsg->aucAAARealm, &(pstMsg->usDynLocalPeerId));
        if (ulRet != VOS_OK)
        {
            PPP_Free(pstMsg);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                         "PPP_EAP_NotifyDiamAuthRelease: Diam_AUTHGetDynAAAInfoByIndex Err!! dynaaacbindex[%u]",
                         pstPppInfo->usPeerId);
            PPP_DBG_ERR_CNT(PPP_PHERR_187);
            return;
        }
    }

    /* 通知diam AAA进行认证 */
    ulRet = PPP_SendRtMsg(PPP_SELF_CSI,
                          g_ullPppDiamAuthCsi,
                          DIAMAUTH_MSG_TYPE_EAP,
                          0,
                          (UCHAR *)pstMsg,
                          ulMsgLen);
    if (VOS_OK != ulRet)
    {
        PPP_Free(pstMsg);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_NotifyDiamAuthRelease: PPP_SendRtMsg Err!!");
        PPP_DBG_ERR_CNT(PPP_PHERR_188);
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_883);

    PPP_Free(pstMsg);
    return;
}


/****************************************************************************
* CREATE DATE  ：2013/09/24                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：重协商通知aaa释放会话                                      *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
****************************************************************************/
VOID PPP_EAP_NotifyDiamAuthReleaseForRenego(PPPINFO_S *pstPppInfo)
{
    PPP_DIAM_AUTH_MSG_S *pstMsg = NULL;
    ULONG ulMsgLen = 0;
    ULONG ulRet = 0;

    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_189);
        VOS_DBGASSERT(NULL != pstPppInfo);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_NotifyDiamAuthReleaseForRenego: pstPppInfo=NULL or pPacket=NULL");
        return;
    }

    /* 分配鉴权消息内存 */
    ulMsgLen = sizeof(PPP_DIAM_AUTH_MSG_S);
    pstMsg = PPP_Malloc(ulMsgLen);
    if (NULL == pstMsg)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_NotifyDiamAuthReleaseForRenego: Malloc DIAM_AUTHREQ_S error!");
        PPP_DBG_ERR_CNT(PPP_PHERR_190);
        return;
    }
    PPP_MemSet((VOID *)pstMsg, 0, ulMsgLen);

    pstMsg->ulMsgType  = PPP_DIAM_AAA_RELEASE_REQ;
    pstMsg->ulRpIndex = pstPppInfo->ulRPIndex;
    /* 携带第一次发送服务器id */
    pstMsg->usPeerID = pstPppInfo->usPeerId;
    /* 下上文token id */
    pstMsg->usTokenId = pstPppInfo->usTokenId;
    pstMsg->ulNowUTCInSec = pstPppInfo->ulNowUTCInSec;
    pstMsg->ulReleaseCode = AM_RELCODE_COMMAND;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n PPP_EAP_NotifyDiamAuthReleaseForRenego: call SDB_GetRpContextByIndex failed! index[%u]releasecode[%u]",
                 pstPppInfo->ulRPIndex, pstMsg->ulReleaseCode);

    /* 获取username */
    if (VOS_OK != PPP_EAP_GetUsername(pstMsg->aucUserName, pstPppInfo))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_191);
    }

    /* IMSI */
    VOS_MemCpy((UCHAR *)&(pstMsg->stIMSI), (UCHAR *)&(pstPppInfo->stIMSI), sizeof(A11_IMSI_S));

    /* 通知diam AAA进行认证 */
    ulRet = PPP_SendRtMsg(PPP_SELF_CSI,
                          g_ullPppDiamAuthCsi,
                          DIAMAUTH_MSG_TYPE_EAP,
                          0,
                          (UCHAR *)pstMsg,
                          ulMsgLen);
    if (VOS_OK != ulRet)
    {
        PPP_Free(pstMsg);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "PPP_EAP_NotifyDiamAuthReleaseForRenego: PPP_SendRtMsg Err!!");
        PPP_DBG_ERR_CNT(PPP_PHERR_192);
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_884);

    PPP_Free(pstMsg);

    /* 重新生成时间戳 */
    pstPppInfo->ulNowUTCInSec = RDA_GetEventTime();
    pstPppInfo->usPeerId = VOS_NULL_WORD;

    return;
}


#define   PPP_EAP_HMAC_SHA_256
/****************************************************************************
* CREATE DATE  ：2010/07/09                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：SHA1Transform - Hash a single 512-bit block.
                 This is the core of the algorithm                          *
* MODIFY DATE  ：                                                           *
* INPUT        ：                                                           *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：                                                           *
****************************************************************************/
void PPP_EAP_AlgoSha1TransformStat(ULONG ulState[5], UCHAR ucBuff[64])
{
    ULONG ulState1, ulState2, ulState3, ulState4, ulState5;
    CHAR64LONG16* pDataBlock64;

#ifdef SHA1HANDSOFF
    UCHAR ucWorkData[64];
    pDataBlock64 = (CHAR64LONG16 *)ucWorkData;
    EAP_ARITH_PPP_BLOCK_COPY(ucBuff, pDataBlock64, 64);
#else
    pDataBlock64 = (CHAR64LONG16 *)ucBuff;
#endif

    ulState1 = ulState[0];
    ulState2 = ulState[1];
    ulState3 = ulState[2];
    ulState4 = ulState[3];
    ulState5 = ulState[4];

    /*lint -e778*/
    EAP_ARITH_REMOVAL_A(ulState1, ulState2, ulState3, ulState4, ulState5, 0);
    EAP_ARITH_REMOVAL_A(ulState5, ulState1, ulState2, ulState3, ulState4, 1);
    EAP_ARITH_REMOVAL_A(ulState4, ulState5, ulState1, ulState2, ulState3, 2);
    EAP_ARITH_REMOVAL_A(ulState3, ulState4, ulState5, ulState1, ulState2, 3);
    EAP_ARITH_REMOVAL_A(ulState2, ulState3, ulState4, ulState5, ulState1, 4);
    EAP_ARITH_REMOVAL_A(ulState1, ulState2, ulState3, ulState4, ulState5, 5);
    EAP_ARITH_REMOVAL_A(ulState5, ulState1, ulState2, ulState3, ulState4, 6);
    EAP_ARITH_REMOVAL_A(ulState4, ulState5, ulState1, ulState2, ulState3, 7);
    EAP_ARITH_REMOVAL_A(ulState3, ulState4, ulState5, ulState1, ulState2, 8);
    EAP_ARITH_REMOVAL_A(ulState2, ulState3, ulState4, ulState5, ulState1, 9);
    EAP_ARITH_REMOVAL_A(ulState1, ulState2, ulState3, ulState4, ulState5, 10);
    EAP_ARITH_REMOVAL_A(ulState5, ulState1, ulState2, ulState3, ulState4, 11);
    EAP_ARITH_REMOVAL_A(ulState4, ulState5, ulState1, ulState2, ulState3, 12);
    EAP_ARITH_REMOVAL_A(ulState3, ulState4, ulState5, ulState1, ulState2, 13);
    EAP_ARITH_REMOVAL_A(ulState2, ulState3, ulState4, ulState5, ulState1, 14);
    EAP_ARITH_REMOVAL_A(ulState1, ulState2, ulState3, ulState4, ulState5, 15);
    EAP_ARITH_REMOVAL_B(ulState5, ulState1, ulState2, ulState3, ulState4, 16);
    EAP_ARITH_REMOVAL_B(ulState4, ulState5, ulState1, ulState2, ulState3, 17);
    EAP_ARITH_REMOVAL_B(ulState3, ulState4, ulState5, ulState1, ulState2, 18);
    EAP_ARITH_REMOVAL_B(ulState2, ulState3, ulState4, ulState5, ulState1, 19);
    EAP_ARITH_REMOVAL_C(ulState1, ulState2, ulState3, ulState4, ulState5, 20);
    EAP_ARITH_REMOVAL_C(ulState5, ulState1, ulState2, ulState3, ulState4, 21);
    EAP_ARITH_REMOVAL_C(ulState4, ulState5, ulState1, ulState2, ulState3, 22);
    EAP_ARITH_REMOVAL_C(ulState3, ulState4, ulState5, ulState1, ulState2, 23);
    EAP_ARITH_REMOVAL_C(ulState2, ulState3, ulState4, ulState5, ulState1, 24);
    EAP_ARITH_REMOVAL_C(ulState1, ulState2, ulState3, ulState4, ulState5, 25);
    EAP_ARITH_REMOVAL_C(ulState5, ulState1, ulState2, ulState3, ulState4, 26);
    EAP_ARITH_REMOVAL_C(ulState4, ulState5, ulState1, ulState2, ulState3, 27);
    EAP_ARITH_REMOVAL_C(ulState3, ulState4, ulState5, ulState1, ulState2, 28);
    EAP_ARITH_REMOVAL_C(ulState2, ulState3, ulState4, ulState5, ulState1, 29);
    EAP_ARITH_REMOVAL_C(ulState1, ulState2, ulState3, ulState4, ulState5, 30);
    EAP_ARITH_REMOVAL_C(ulState5, ulState1, ulState2, ulState3, ulState4, 31);
    EAP_ARITH_REMOVAL_C(ulState4, ulState5, ulState1, ulState2, ulState3, 32);
    EAP_ARITH_REMOVAL_C(ulState3, ulState4, ulState5, ulState1, ulState2, 33);
    EAP_ARITH_REMOVAL_C(ulState2, ulState3, ulState4, ulState5, ulState1, 34);
    EAP_ARITH_REMOVAL_C(ulState1, ulState2, ulState3, ulState4, ulState5, 35);
    EAP_ARITH_REMOVAL_C(ulState5, ulState1, ulState2, ulState3, ulState4, 36);
    EAP_ARITH_REMOVAL_C(ulState4, ulState5, ulState1, ulState2, ulState3, 37);
    EAP_ARITH_REMOVAL_C(ulState3, ulState4, ulState5, ulState1, ulState2, 38);
    EAP_ARITH_REMOVAL_C(ulState2, ulState3, ulState4, ulState5, ulState1, 39);
    EAP_ARITH_REMOVAL_D(ulState1, ulState2, ulState3, ulState4, ulState5, 40);
    EAP_ARITH_REMOVAL_D(ulState5, ulState1, ulState2, ulState3, ulState4, 41);
    EAP_ARITH_REMOVAL_D(ulState4, ulState5, ulState1, ulState2, ulState3, 42);
    EAP_ARITH_REMOVAL_D(ulState3, ulState4, ulState5, ulState1, ulState2, 43);
    EAP_ARITH_REMOVAL_D(ulState2, ulState3, ulState4, ulState5, ulState1, 44);
    EAP_ARITH_REMOVAL_D(ulState1, ulState2, ulState3, ulState4, ulState5, 45);
    EAP_ARITH_REMOVAL_D(ulState5, ulState1, ulState2, ulState3, ulState4, 46);
    EAP_ARITH_REMOVAL_D(ulState4, ulState5, ulState1, ulState2, ulState3, 47);
    EAP_ARITH_REMOVAL_D(ulState3, ulState4, ulState5, ulState1, ulState2, 48);
    EAP_ARITH_REMOVAL_D(ulState2, ulState3, ulState4, ulState5, ulState1, 49);
    EAP_ARITH_REMOVAL_D(ulState1, ulState2, ulState3, ulState4, ulState5, 50);
    EAP_ARITH_REMOVAL_D(ulState5, ulState1, ulState2, ulState3, ulState4, 51);
    EAP_ARITH_REMOVAL_D(ulState4, ulState5, ulState1, ulState2, ulState3, 52);
    EAP_ARITH_REMOVAL_D(ulState3, ulState4, ulState5, ulState1, ulState2, 53);
    EAP_ARITH_REMOVAL_D(ulState2, ulState3, ulState4, ulState5, ulState1, 54);
    EAP_ARITH_REMOVAL_D(ulState1, ulState2, ulState3, ulState4, ulState5, 55);
    EAP_ARITH_REMOVAL_D(ulState5, ulState1, ulState2, ulState3, ulState4, 56);
    EAP_ARITH_REMOVAL_D(ulState4, ulState5, ulState1, ulState2, ulState3, 57);
    EAP_ARITH_REMOVAL_D(ulState3, ulState4, ulState5, ulState1, ulState2, 58);
    EAP_ARITH_REMOVAL_D(ulState2, ulState3, ulState4, ulState5, ulState1, 59);
    EAP_ARITH_REMOVAL_E(ulState1, ulState2, ulState3, ulState4, ulState5, 60);
    EAP_ARITH_REMOVAL_E(ulState5, ulState1, ulState2, ulState3, ulState4, 61);
    EAP_ARITH_REMOVAL_E(ulState4, ulState5, ulState1, ulState2, ulState3, 62);
    EAP_ARITH_REMOVAL_E(ulState3, ulState4, ulState5, ulState1, ulState2, 63);
    EAP_ARITH_REMOVAL_E(ulState2, ulState3, ulState4, ulState5, ulState1, 64);
    EAP_ARITH_REMOVAL_E(ulState1, ulState2, ulState3, ulState4, ulState5, 65);
    EAP_ARITH_REMOVAL_E(ulState5, ulState1, ulState2, ulState3, ulState4, 66);
    EAP_ARITH_REMOVAL_E(ulState4, ulState5, ulState1, ulState2, ulState3, 67);
    EAP_ARITH_REMOVAL_E(ulState3, ulState4, ulState5, ulState1, ulState2, 68);
    EAP_ARITH_REMOVAL_E(ulState2, ulState3, ulState4, ulState5, ulState1, 69);
    EAP_ARITH_REMOVAL_E(ulState1, ulState2, ulState3, ulState4, ulState5, 70);
    EAP_ARITH_REMOVAL_E(ulState5, ulState1, ulState2, ulState3, ulState4, 71);
    EAP_ARITH_REMOVAL_E(ulState4, ulState5, ulState1, ulState2, ulState3, 72);
    EAP_ARITH_REMOVAL_E(ulState3, ulState4, ulState5, ulState1, ulState2, 73);
    EAP_ARITH_REMOVAL_E(ulState2, ulState3, ulState4, ulState5, ulState1, 74);
    EAP_ARITH_REMOVAL_E(ulState1, ulState2, ulState3, ulState4, ulState5, 75);
    EAP_ARITH_REMOVAL_E(ulState5, ulState1, ulState2, ulState3, ulState4, 76);
    EAP_ARITH_REMOVAL_E(ulState4, ulState5, ulState1, ulState2, ulState3, 77);
    EAP_ARITH_REMOVAL_E(ulState3, ulState4, ulState5, ulState1, ulState2, 78);
    EAP_ARITH_REMOVAL_E(ulState2, ulState3, ulState4, ulState5, ulState1, 79);
    /*lint +e778*/

    ulState[0] += ulState1;
    ulState[1] += ulState2;
    ulState[2] += ulState3;
    ulState[3] += ulState4;
    ulState[4] += ulState5;

    return;
}
/****************************************************************************
* CREATE DATE  ：2010/07/09                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：SHA1Init - Initialize new context
* MODIFY DATE  ：                                                           *
* INPUT        ：                                                           *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：                                                           *
****************************************************************************/
void PPP_EAP_AlgoSha1StateInit(SHA1_CTX* context)
{
    context->state[0] = 0x67452301;
    context->state[1] = 0xEFCDAB89;
    context->state[2] = 0x98BADCFE;
    context->state[3] = 0x10325476;
    context->state[4] = 0xC3D2E1F0;
    context->count[0] = context->count[1] = 0;
    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/09                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：SHA1Update
* MODIFY DATE  ：                                                           *
* INPUT        ：                                                           *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：                                                           *
****************************************************************************/
void PPP_EAP_AlgoSha1StateUpdate(SHA1_CTX *context, UCHAR *data, unsigned int len)
{
    ULONG i = 0;
    ULONG j = 0;

    j = context->count[0];
    if ((context->count[0] += len << 3) < j)
    {
        context->count[1] += (len >> 29) + 1;
    }

    j = (j >> 3) & 63;
    if ((j + len) > 63)
    {
        EAP_ARITH_PPP_BLOCK_COPY(data, &context->buffer[j], (i = 64 - j));
        PPP_EAP_AlgoSha1TransformStat(context->state, context->buffer);
        for (; i + 63 < len; i += 64)
        {
            PPP_EAP_AlgoSha1TransformStat(context->state, &data[i]);
        }

        j = 0;
    }
    else
    {
        i = 0;
    }

    EAP_ARITH_PPP_BLOCK_COPY(&data[i], &context->buffer[j], len - i);/*lint !e669 */
    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/09                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：SHA1Final   Add padding and return the message digest.
* MODIFY DATE  ：                                                           *
* INPUT        ：                                                           *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：                                                           *
****************************************************************************/
void PPP_EAP_AlgoSha1StateFinial(UCHAR digest[20], SHA1_CTX *context)
{
    ULONG i = 0;
    UCHAR finalcount[8] = {0};

    for (i = 0; i < 8; i++)
    {
        finalcount[i] = (UCHAR)((context->count[(i >= 4 ? 0 : 1)]
                               >> ((3 - (i & 3)) * 8)) & 255);
    }

    PPP_EAP_AlgoSha1StateUpdate(context, (UCHAR *)"\200", 1);
    while ((context->count[0] & 504) != 448)
    {
        /*lint -e840*/
        PPP_EAP_AlgoSha1StateUpdate(context, (UCHAR *)"\0", 1);
        /*lint +e840*/
    }

    PPP_EAP_AlgoSha1StateUpdate(context, finalcount, 8);
    if (digest)
    {
        for (i = 0; i < 20; i++)
        {
            digest[i] = (UCHAR)
                      ((context->state[i >> 2] >> ((3 - (i & 3)) * 8)) & 255);
        }
    }
    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/09                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：HMAC_SHA的算法实现
* MODIFY DATE  ：                                                           *
* INPUT        ：                                                           *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：                                                           *
****************************************************************************/
VOID PPP_EAP_AlgoHmacSha(UCHAR *d, LONG ld, UCHAR *k, LONG lk, UCHAR *digest)
{
    SHA1_CTX ictx = {0};
    SHA1_CTX octx = {0};
    UCHAR iSHA[20] = {0};
    UCHAR oSHA[20] = {0};
    CHAR key[20] = {0};
    UCHAR buf[64] = {0};
    LONG i = 0;

    if (lk > 64)
    {
        SHA1_CTX tctx;

        PPP_EAP_AlgoSha1StateInit(&tctx);
        PPP_EAP_AlgoSha1StateUpdate(&tctx, (UCHAR *)k, (ULONG)lk);
        PPP_EAP_AlgoSha1StateFinial((UCHAR *)key, &tctx);

        k  = (UCHAR*)key;
        lk = 20;
    }


    PPP_EAP_AlgoSha1StateInit(&ictx);

    for (i = 0; i < lk; ++i)
    {
        buf[i] = (UCHAR)(k[i] ^ 0x36);
    }

    for (i = lk; i < 64; ++i)
    {
        buf[i] = 0x36;
    }

    PPP_EAP_AlgoSha1StateUpdate(&ictx, buf, 64);
    PPP_EAP_AlgoSha1StateUpdate(&ictx, (UCHAR *)d, (ULONG)ld);

    PPP_EAP_AlgoSha1StateFinial(iSHA, &ictx);

    PPP_EAP_AlgoSha1StateInit(&octx);

    for (i = 0; i < lk; ++i)
    {
        buf[i] = (UCHAR)(k[i] ^ 0x5C);
    }

    for (i = lk; i < 64; ++i)
    {
        buf[i] = (UCHAR)0x5C;
    }

    PPP_EAP_AlgoSha1StateUpdate(&octx, buf, 64);
    PPP_EAP_AlgoSha1StateUpdate(&octx, iSHA, 20);
    PPP_EAP_AlgoSha1StateFinial(oSHA, &octx);
    (VOID)VOS_MemCpy(digest, oSHA, 20);

    return;
}

#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
