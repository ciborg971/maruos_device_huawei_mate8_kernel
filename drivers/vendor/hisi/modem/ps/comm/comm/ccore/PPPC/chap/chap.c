/************************************************************************
*                                                                      *
*                             chap.c                                   *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/06/05                                      *
*  Author:             Zhu Fengzhi                                     *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP的CHAP协议模块                               *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件定义了CHAP协议模块的全部接口函数和内部处理函数             *
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
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_CHAP_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
PS_BOOL_ENUM_UINT8  g_enGetChapRespSelf = PS_TRUE;
/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

void PPP_MD5Init(MD5_CTX *context)
{
  context->count[0] = context->count[1] = 0;
  /* Load magic initialization constants.
 */
  context->state[0] = 0x67452301;
  context->state[1] = 0xefcdab89;
  context->state[2] = 0x98badcfe;
  context->state[3] = 0x10325476;
}

void PPP_MD5_memset (UCHAR * output, LONG value, ULONG len)
{
  ULONG i;

  for (i = 0; i < len; i++)
 ((char *)output)[i] = (char)value;
}

void PPP_Decode (ULONG *output,UCHAR *input, ULONG len)
{
  ULONG i, j;

  for (i = 0, j = 0; j < len; i++, j += 4)
 output[i] = ((ULONG)input[j]) | (((ULONG)input[j+1]) << 8) |
   (((ULONG)input[j+2]) << 16) | (((ULONG)input[j+3]) << 24);
}

void PPP_MD5Transform (ULONG state[4], UCHAR block[64])
{
  ULONG a = state[0], b = state[1], c = state[2], d = state[3], x[16];

  PPP_Decode (x, block, 64);

  /* Round 1 */
  FF (a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
  FF (d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
  FF (c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
  FF (b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
  FF (a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
  FF (d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
  FF (c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
  FF (b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
  FF (a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
  FF (d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
  FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
  FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
  FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
  FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
  FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
  FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

 /* Round 2 */
  GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
  GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
  GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
  GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
  GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
  GG (d, a, b, c, x[10], S22,  0x2441453); /* 22 */
  GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
  GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
  GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
  GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
  GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
  GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
  GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
  GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
  GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
  GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

  /* Round 3 */
  HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
  HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
  HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
  HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
  HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
  HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
  HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
  HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
  HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
  HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
  HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
  HH (b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
  HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
  HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
  HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
  HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

  /* Round 4 */
  II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
  II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
  II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
  II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
  II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
  II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
  II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
  II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
  II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
  II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
  II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
  II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
  II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
  II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
  II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
  II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;

  /* Zeroize sensitive information.
 */
  PPP_MD5_memset ((UCHAR *)x, 0, sizeof (x));
}

void PPP_MD5_memcpy (UCHAR * output,UCHAR * input,ULONG len)
{
  ULONG i;

  for (i = 0; i < len; i++)
 output[i] = input[i];
}



void PPP_MD5Update(MD5_CTX *context, UCHAR *input, ULONG inputLen)
{
  ULONG i, index, partLen;

  /* Compute number of bytes mod 64 */
  index = (ULONG)((context->count[0] >> 3) & 0x3F);

  /* Update number of bits */
  if ((context->count[0] += ((ULONG)inputLen << 3))
   < ((ULONG)inputLen << 3))
 context->count[1]++;
  context->count[1] += ((ULONG)inputLen >> 29);

  partLen = 64 - index;

  /* Transform as many times as possible.
 */
  if (inputLen >= partLen) {
 PPP_MD5_memcpy
   ((UCHAR *)&context->buffer[index], (UCHAR *)input, partLen);
 PPP_MD5Transform (context->state, context->buffer);

 for (i = partLen; i + 63 < inputLen; i += 64)
 {
    PPP_MD5Transform (context->state, &input[i]);
 }

 index = 0;
  }
  else
 i = 0;

  /* Buffer remaining input */
  PPP_MD5_memcpy
 ((UCHAR *)&context->buffer[index], (UCHAR *)&input[i],
  inputLen-i);
}

UCHAR PPP_PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

void PPP_Encode (UCHAR *output, ULONG *input, ULONG len)
{
  ULONG i, j;

  for (i = 0, j = 0; j < len; i++, j += 4) {
 output[j] = (UCHAR)(input[i] & 0xff);
 output[j+1] = (UCHAR)((input[i] >> 8) & 0xff);
 output[j+2] = (UCHAR)((input[i] >> 16) & 0xff);
 output[j+3] = (UCHAR)((input[i] >> 24) & 0xff);
  }
}


void PPP_MD5Final(UCHAR digest[16], MD5_CTX *context)
{
  UCHAR bits[8];
  ULONG index, padLen;

  /* Save number of bits */
  PPP_Encode (bits, context->count, 8);

  /* Pad out to 56 mod 64.
 */
  index = (ULONG)((context->count[0] >> 3) & 0x3f);
  padLen = (index < 56) ? (56 - index) : (120 - index);
  PPP_MD5Update(context, PPP_PADDING, padLen);

  /* Append length (before padding) */
  PPP_MD5Update(context, bits, 8);

  /* Store state in digest */
  PPP_Encode (digest, context->state, 16);

  /* Zeroize sensitive information.
 */
  PPP_MD5_memset ((UCHAR *)context, 0, sizeof (*context));
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP初始化CHAP控制块                                        *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_Core_AuthenticatePhase                                    *
****************************************************************************/
VOID PPP_CHAP_Init(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo;
    PPPCONFIGINFO_S *pstConfig;


    /* 初始化为自己算Resposne */
    g_enGetChapRespSelf = PS_TRUE;

    if (pstPppInfo == 0)
    {
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    pstConfig = pstPppInfo->pstUsedConfigInfo;
    if ((pstChapInfo == 0) || (pstConfig == 0))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_35);
        return;
    }

    PPP_MemSet((VOID*)pstChapInfo, 0, sizeof(PPPCHAPINFO_S));

    pstChapInfo->pstPppInfo = pstPppInfo;
    pstChapInfo->ucUsed = 1;
    pstChapInfo->ucClientState = CHAP_STATE_CLIENT_INITIAL;
    pstChapInfo->ucServerState = CHAP_STATE_SERVER_INITIAL;
    pstChapInfo->ucChalId = 0;
    pstChapInfo->ucRespId = 0;
    pstChapInfo->ulChalTransmits = 0;
    pstChapInfo->ulRespTransmits = 0;
    pstChapInfo->ulChalTimeoutID = 0;
    pstChapInfo->ulRespTimeoutID = 0;
    pstChapInfo->usAuthServerFailureTimes = 0;
    pstChapInfo->usAuthClientFailureTimes = 0;

    pstChapInfo->ulTimeOutTime  = pstConfig->ulNegTimeOut;
    pstChapInfo->ulMaxTransmits = PPP_DEFMAXCONFREQS;

    /*设置周期验证间隔, 暂不启动此功能*/
    pstChapInfo->ulChalInterval = 0;

    /*设置hash算法*/
    pstChapInfo->ucRespType = CHAP_DIGEST_MD5;
    pstChapInfo->ucChalType = CHAP_DIGEST_MD5;

    /* added by gxf 20030221 */
    pstChapInfo->ulWaitAuthRspTimeout = CHAP_WAITAAARSPTIMEOUT;
    pstChapInfo->ulAuthMaxTransmits = CHAP_MAXAUTHTRANSMITS;
    pstChapInfo->ucAuthTransmits  = 0;
    pstChapInfo->pstAAAAuthReqMsg = NULL;
    pstChapInfo->ulWaitLnsAuthTimeOut = CHAP_WAITLNSAUTHTIME;/*added by wangliang ht04409 at 2006-2-13 for BYHD09482*/

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_INITIALIZATION);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP接收外部事件.事件包括：ClientUp、ServerUp、Down            *                                           Open、Close            *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                ulCmd:命令字, 可以为如下值:                                *
*                    CHAP_EVENT_CLIENTLOWERUP:本地下层UP                        *
*                    CHAP_EVENT_SERVERLOWERUP:对端下层UP                        *
*                    CHAP_EVENT_LOWERDOWN:下层DOWN                            *
*                pPara:事件的参数, 为NULL                                   *
* OUTPUT       ：                                                           *
* RETURN       ：NULL                                                       *
* CALLED BY    ：PPP_Core_ReceiveEventFromShell                                *
****************************************************************************/
VOID PPP_CHAP_ReceiveEventFromCore (PPPINFO_S *pstPppInfo, ULONG ulCmd, CHAR *pPara)
{
    if (pstPppInfo == 0)
    {
        return;
    }

    switch (ulCmd)
    {
        case CHAP_EVENT_CLIENTLOWERUP:
            PPP_CHAP_ClientLowerUp(pstPppInfo);
            break;

        case CHAP_EVENT_SERVERLOWERUP:
            PPP_CHAP_ServerLowerUp(pstPppInfo);
            break;

        case CHAP_EVENT_LOWERDOWN:
            PPP_CHAP_LowerDown(pstPppInfo);
            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_36);

            /*输出错误调试信息*/
            CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "CHAP Receive UNKNOWN Event!");
            break;
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP Client 端LowerUp,由对端验证我端                        *
*                 进入CHAP_STATE_LISTEN_CHALLENGE状态, 等待对端送出CHALLENGE    *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceiveEventFromCore                                *
****************************************************************************/
VOID PPP_CHAP_ClientLowerUp(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S * pstChapInfo = pstPppInfo->pstChapInfo;
    PPPCONFIGINFO_S *pstConfig = pstPppInfo->pstUsedConfigInfo;
    VOS_UINT32                          ulRet;


    if ((pstChapInfo == NULL) || (pstConfig == NULL))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_37);
        return;
    }

    ulRet = PPP_GetConfigUserName(pstChapInfo->szHostName);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("Get username fail when chap client up.");
    }

    pstChapInfo->ulTimeOutTime = pstConfig->ulNegTimeOut;
    pstChapInfo->ulRespTransmits = 0;
    pstChapInfo->ucRespId = 0;
    pstChapInfo->ulRespTimeoutID = 0;
    pstChapInfo->usAuthClientFailureTimes = 0;

    /* 输出事件调试信息 */
    CHAP_Debug_Event(pstPppInfo, CHAP_CLIENTLOWERUP);

    /* 输出状态转换调试信息 */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_LISTEN_CHALLENGE, CHAP_CLIENT_STATE);
    pstChapInfo->ucClientState = CHAP_STATE_LISTEN_CHALLENGE;

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP Server 端LowerUp,由我端向对端发送Challenge             *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceiveEventFromCore                                *
****************************************************************************/
VOID PPP_CHAP_ServerLowerUp(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S * pstChapInfo = pstPppInfo->pstChapInfo;
    PPPCONFIGINFO_S *pstConfig = pstPppInfo->pstUsedConfigInfo;

    if ((pstChapInfo == NULL) || (pstConfig == NULL))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_38);
        return;
    }

    (VOID)VOS_StrCpy((CHAR *)pstChapInfo->szHostName, (const CHAR *)pstConfig->cChapHostName);
    pstChapInfo->ulChalTransmits = 0;
    pstChapInfo->ulTimeOutTime = pstConfig->ulNegTimeOut;
    pstChapInfo->ucChalId = 0;
    pstChapInfo->ulChalTransmits = 0;
    pstChapInfo->ulChalTimeoutID = 0;
    pstChapInfo->usAuthServerFailureTimes = 0;

    /* 输出事件调试信息 */
    CHAP_Debug_Event(pstPppInfo, CHAP_SERVERLOWERUP);

    PPP_CHAP_GenChallenge(pstChapInfo);        /* 产生challenge */
    PPP_CHAP_SendChallenge(pstPppInfo);        /* 送出challenge */

    PPP_PerfInc(&g_stPppPerfStatistic.ulChapTotal, PERF_TYPE_PPPC_CHAP_AUTHEN_NUM, pstPppInfo->bEhrpdUser);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAPLowerDown                                                *
*                 进入CHAP_STATE_SERVER_INITIAL ,CHAP_STATE_CLIENT_INITIAL状态        *
*                 同时删除定时器                                                *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceiveEventFromCore                                *
****************************************************************************/
VOID PPP_CHAP_LowerDown(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;

    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_40);
        return;
    }

    /* 输出事件调试信息 */
    CHAP_Debug_Event(pstPppInfo, CHAP_LOWERDOWN);

    /* 删除定时器 */
    PPP_CHAP_DeleteTimer(pstPppInfo);

    /* 输出调试信息 */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_CLIENT_INITIAL, CHAP_CLIENT_STATE);
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_SERVER_INITIAL, CHAP_SERVER_STATE);

    /* 改变状态 */
    pstChapInfo->ucClientState = CHAP_STATE_CLIENT_INITIAL;
    pstChapInfo->ucServerState = CHAP_STATE_SERVER_INITIAL;

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP收到chap 数据包, 分析报文头并作相应处理                *
*                pHead:存放报文内存的头指针包括协议号, 应负责释放这段内存   *
*                pPacket:报文头位置                                         *
*                ulLen:报文长度                                             *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_Core_ReceivePacketFromShell                            *
****************************************************************************/
VOID PPP_CHAP_ReceivePacket (PPPINFO_S *pstPppInfo, UCHAR* pHead, UCHAR* pPacket, ULONG ulLen)
{
    PPPCHAPINFO_S *pstChapInfo;
    UCHAR ucCode, ucId;
    ULONG ulCiLen;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n-------enter PPP_CHAP_ReceivePacket--------");
    if (pstPppInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_41);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "pstPppInfo == 0");
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (pstChapInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_42);
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "pstChapInfo == 0");
        return;
    }

    /*输出事件调试信息*/
    CHAP_Debug_Packet(pstPppInfo, pPacket, ulLen, PPP_CHAP, 1);

    /*分析报文头(ucCode,ucId, length)*/

    if (ulLen < FSM_HDRLEN)        /* 如果报文包太短则丢弃 */
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        PPP_DBG_ERR_CNT(PPP_PHERR_43);
        return;
    }

    /* 获得报文中字段值, 并移动报文指针 */
    PPP_GETCHAR(ucCode, pPacket);
    PPP_GETCHAR(ucId, pPacket);
    PPP_GETSHORT(ulCiLen, pPacket);

    if (ulCiLen < CHAP_HEADERLEN)
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        PPP_DBG_ERR_CNT(PPP_PHERR_44);
        return;
    }

    ulCiLen -= CHAP_HEADERLEN;

    /* 依照 ucCode 采用相应的动作 */
    switch (ucCode)
    {
        case CHAP_PACKET_CODE_CHALLENGE:
            PPP_CHAP_ReceiveChallenge(pstPppInfo, pPacket, ucId, ulCiLen);
            break;

        case CHAP_PACKET_CODE_RESPONSE:
            PPP_CHAP_ReceiveResponse(pstPppInfo, pPacket, ucId, ulCiLen);
            break;

        case CHAP_PACKET_CODE_FAILURE:
            PPP_CHAP_ReceiveFailure(pstPppInfo);
            break;

        case CHAP_PACKET_CODE_SUCCESS:
            PPP_CHAP_ReceiveSuccess(pstPppInfo, ucId);
            break;

        default:
            PPP_DBG_ERR_CNT(PPP_PHERR_45);
            PPP_CHAP_ReceiveUnknownCode(pstPppInfo);
            break;
    }
    return;
}
VOS_UINT32 PPP_CHAP_GetHrpdResponse(PPPINFO_S *pstPppInfo, PPPAUTHMSG_S *pstMsg)
{
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;
    VOS_UINT32                          ulRandu;
    PS_BOOL_ENUM_UINT8                  enIsCaveAlgorithmEnable;
    PS_BOOL_ENUM_UINT8                  enIsMD5AlgorithmEnable;


    /* 如果是HRPD模式，由USIM卡来计算Response */
    enRatMode = PPPC_GetRatMode();
    if (PPPC_RAT_MODE_HRPD == enRatMode)
    {
        ulRandu = ((VOS_UINT32)pstMsg->szPwd[0] << 24)
                 | ((VOS_UINT32)pstMsg->szPwd[1] << 16)
                 | ((VOS_UINT32)pstMsg->szPwd[2] << 8)
                 | ((VOS_UINT32)pstMsg->szPwd[3]);
        PPPC_SaveRunCaveRandu(ulRandu);

        enIsCaveAlgorithmEnable = PPPC_IsCaveAlgorithmEnable();
        enIsMD5AlgorithmEnable  = PPPC_MD5Active();
        /* 不支持CAVE算法 或 支持CAVE算法且MD5算法可用 时让USIM卡使用MD5算法 */
        if ((PS_FALSE == enIsCaveAlgorithmEnable) || (PS_TRUE == enIsMD5AlgorithmEnable))
        {
            /* 使用MD5算法 */
            PPPC_UIM_MD5ChapAuthReq(pstPppInfo, pstMsg);
            return VOS_OK;
        }
        else
        {
            /* 使用CAVE算法 */
            PPPC_UIM_RunCaveAuthReq(ulRandu);
            return VOS_OK;
        }
    }

    PPPC_WARNING_LOG2("It is 1X mode,should not let sim compute response\r\n", enRatMode, ulRandu);

    return VOS_ERR;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP收到对端的Challenge包                                    *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                 pPacket:报文头位置                                            *
*                 ucId:报文ID                                                *
*                ulLen:报文数据长度                                            *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_CHAP_ReceiveChallenge(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, ULONG ulLen)
{
    PPPCHAPINFO_S *pstChapInfo;
    PPPCONFIGINFO_S *pstConfigInfo;
    PPPAUTHMSG_S stMsg;
    LONG lLen = (LONG)ulLen;
    VOS_UINT32                          ulRet;
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;
    PS_BOOL_ENUM_UINT8                  enIsDoingAccessAuth;
    VOS_UINT32                          ulRandu;


    if (pstPppInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_46);
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_47);
        return;
    }

    pstConfigInfo = pstPppInfo->pstUsedConfigInfo;

    PPP_MemSet((VOID *)&stMsg, 0, sizeof(PPPAUTHMSG_S));

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_RECEIVECHALLENGE);
    if (pstChapInfo->ucClientState == CHAP_STATE_CLIENT_INITIAL)
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "CHAP receive Challenge packet on CHAP_STATE_CLIENT_INITIAL!");
        PPP_DBG_ERR_CNT(PPP_PHERR_48);
        return;
    }

    /*取出Challenge,用于产生Response*/
    PPP_GETCHAR(stMsg.ucPwdLen, pPacket);
    (VOID)VOS_MemCpy((CHAR * )stMsg.szPwd, pPacket, (ULONG)stMsg.ucPwdLen);

    /*pPacket指针移动*/
    PPP_INCPTR(stMsg.ucPwdLen, pPacket);

    /* 计算Name域长度 */
    lLen -= (LONG)sizeof (UCHAR) + (LONG)(stMsg.ucPwdLen);
    if (lLen < 0) /*是否过短*/
    {
        /*输出错误调试信息*/
        PPP_DBG_ERR_CNT(PPP_PHERR_49);
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        return;
    }

    if (lLen >= PPP_MAXUSERNAMELEN)   /*是否过长*/
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_50);
        lLen = PPP_MAXUSERNAMELEN;
    }

    /*保存Challenge ID*/
    pstChapInfo->ucRespId = ucId;

    /*取得对端Hostname,用于产生Response*/
    stMsg.ucUsrNameLen = (UCHAR )lLen;
    (VOID)VOS_MemCpy((CHAR * )stMsg.szUsrName, pPacket, (ULONG)lLen);

    /*取得Challeng Id,用于产生Response */
    stMsg.ucPktID = ucId;

    /*删除等待RespTimeoutID超时定时器*/
    if (pstChapInfo->ulRespTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));
        pstChapInfo->ulRespTimeoutID = 0;
    }

    /* 接入鉴权不需要从节点获取密码 */
    enIsDoingAccessAuth = PPPC_IsDoingAccessAuth();
    if (PS_TRUE == enIsDoingAccessAuth)
    {
        /* 接入鉴权必须用SIM卡算,不管内部用MD5/CAVE算法或者成功失败都直接退出 */
        (VOS_VOID)PPP_CHAP_GetHrpdResponse(pstPppInfo, &stMsg);
        return;
    }
    else
    {
        /*取本地的password,作为产生Response的备用secret */
        ulRet = PPP_GetConfigPassWord((VOS_UINT8 *)stMsg.szResponse);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG("Get pass word fail when when receive challenge.");
        }

        stMsg.ucResponseLen = (UCHAR )VOS_StrLen((const CHAR *)(stMsg.szResponse));
    }

    if (PS_TRUE != g_enGetChapRespSelf)
    {
        ulRet = PPP_CHAP_GetHrpdResponse(pstPppInfo, &stMsg);
        if (VOS_OK == ulRet)
        {
            /* 返回OK说明是HRPD模式,可以用SIM卡算,否则需要MS自己用MD5算法计算 */
            return;
        }

    }
    else
    {
        g_enGetChapRespSelf = PS_FALSE;
    }

    /*根据Challeng Id,Challenge,secret(由对端Hostname得出)产生Response */
    if (PPP_CHAP_GenResponse( &stMsg ))
    {
        /*保存Response 及长度*/
        (VOID)VOS_MemCpy((CHAR *)pstChapInfo->szResponse, (UCHAR*)(stMsg.szResponse),
                           (ULONG )stMsg.ucResponseLen );
        pstChapInfo->szResponse[stMsg.ucResponseLen] = 0;
        pstChapInfo->ucRespLen = stMsg.ucResponseLen;
        PPP_CHAP_SendResponse(pstPppInfo);
    }
    else
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Generate response error!");
        PPP_DBG_ERR_CNT(PPP_PHERR_51);

        /* 删除定时器 */
        PPP_CHAP_DeleteTimer(pstPppInfo);

        /* 向内核报CHAP验证失败 */
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_CHAPFAILED, NULL);
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP收到对端的Response包, 向AAA请求验证                    *
* MODIFY DATE  ：modified by gxf for GGSN80 20030220                        *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                 pPacket:报文头位置                                            *
*                 ucId:报文ID                                                *
*                ulLen:报文数据长度                                            *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_CHAP_ReceiveResponse(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, ULONG ulLen)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    AAA_AUTHREQ_S *pstMsg;

    UCHAR ucValueSize;
    LONG lLen = (LONG)ulLen;

    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_52);
        return;
    }

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_RECEIVERESPONSE);

    if ((pstChapInfo->ucServerState == CHAP_STATE_SERVER_INITIAL)
        || (pstChapInfo->ucServerState == CHAP_STATE_WAITING_AAA))
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING,
                         "CHAP receive Response ON CHAP_STATE_SERVER_INITIAL or CHAP_STATE_WAITING_AAA phase!");
        PPP_ERROR_COUNTER(PPP_ERROR_COUNTER048);
        PPP_DBG_ERR_CNT(PPP_PHERR_53);
        return;
    }

    if (ucId != pstChapInfo->ucChalId)    /*ID 不匹配 */
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_19);
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "unmatched ID!");
        PPP_DBG_ERR_CNT(PPP_PHERR_54_RESP_CHAID_ERR);
        return;
    }

    /* 收到多次或假的Response依然要回送与第一次收到Response一样的answer(Success/Failure)*/
    if (pstChapInfo->ucServerState != CHAP_STATE_SEND_CHALLENGE)
    {
        if ( ( 0 == pstPppInfo->bReNego )
                && (0 == pstPppInfo->bPppClient)
                 && (1 == pstPppInfo->bPppMode))
        {
            PPP_DBG_OK_CNT(PPP_PHOK_820);
        }
        else
        {
            PPP_CHAP_SendStatus(pstPppInfo, pstChapInfo->ucServerState); /* return auth-result */
        }
        return;
    }

    if ((pstPppInfo->ulPeerIPAddr) && (0 == pstPppInfo->bReNego))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_821);
    }

    /*删除等待Response 超时定时器*/
    if (pstChapInfo->ulChalTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
        pstChapInfo->ulChalTimeoutID = 0;
    }

    if (pstChapInfo->pstAAAAuthReqMsg)
    {
        pstMsg = pstChapInfo->pstAAAAuthReqMsg;
    }
    else
    {
        pstMsg = (AAA_AUTHREQ_S *)PPP_Malloc(sizeof(AAA_AUTHREQ_S));
        if (!pstMsg)
        {
            CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Malloc error!");
            PPP_DBG_ERR_CNT(PPP_PHERR_55);
            return;
        }

        pstChapInfo->pstAAAAuthReqMsg = pstMsg;
    }

    PPP_MemSet((VOID *)pstMsg, 0, sizeof(AAA_AUTHREQ_S));

    /* Response消息中的ResponseLen、Response */
    PPP_GETCHAR(ucValueSize, pPacket);        /* 取得MD 长度 */
    /* 构造验证信息块stMsg  */
    if (ucValueSize > CHAP_MAX_RESPONSE_LENGTH)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_822);
        pstMsg->ucChapResponseLen = CHAP_MAX_RESPONSE_LENGTH;
    }
    else
    {
        pstMsg->ucChapResponseLen = ucValueSize;
    }

    /* 取出 response 中的secret到 msg */
    (VOID)VOS_MemCpy((CHAR *)pstMsg->ucChapResponse, pPacket, (ULONG )pstMsg->ucChapResponseLen);
    pstMsg->ucChapResponse[pstMsg->ucChapResponseLen] = 0x0;

    /* 取出 CHAP 控制块中的 challenge 到 msg */
    pstMsg->ucChapChallengeLen = pstChapInfo->ucChalLen;
    (VOID)VOS_MemCpy((CHAR *)pstMsg->ucChapChallenge, pstChapInfo->szChallenge, (ULONG)pstMsg->ucChapChallengeLen);
    pstMsg->ucChapChallenge[pstMsg->ucChapChallengeLen] = 0x0;

    /* 取出 response 中的name到 msg */
    PPP_INCPTR(ucValueSize, pPacket);
    lLen -= (LONG)sizeof (UCHAR) + (LONG)ucValueSize;

    if ((0 == (g_ulSoftPara567 & 0x01)) && (lLen <= 0))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_20);
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
        PPP_DBG_ERR_CNT(PPP_PHERR_56);
        return;
    }
    else
    {
        /* 兼容R1C3B047 版本允许不携带用户名属性 */
        if (lLen < 0)
        {
            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
            /*End of liushuang*/
            PPP_CHAP_AAAAuthFailed(pstChapInfo);
            CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Too short packet!");
            PPP_DBG_ERR_CNT(PPP_PHERR_57);
            return;
        }
    }

    if (lLen > A11_MAX_NAI_LENGTH)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_21);
        PPP_CHAP_SendStatus(pstPppInfo, CHAP_STATE_SERVER_FAILED);
        A11_ReqNumSubProc(pstPppInfo);

        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
        PPP_DBG_ERR_CNT(PPP_PHERR_58);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_CHAP_ReceiveResponse: NAI Len(%u) > 63",
                     lLen);
        return;
    }

    pstMsg->ucUsernameLen = (UCHAR)lLen;
    (VOID)VOS_MemCpy((CHAR *)pstMsg->ucUsername, pPacket, (ULONG)pstMsg->ucUsernameLen);
    pstMsg->ucUsername[pstMsg->ucUsernameLen] = 0x0;

    if ((0 != pstPppInfo->ucNAI[0]) && 0 != VOS_StrCmp((CHAR*)(pstMsg->ucUsername), (CHAR*)(pstPppInfo->ucNAI)))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_22);
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
        /*End of liushuang*/
        PPP_CHAP_SendStatus(pstPppInfo, CHAP_STATE_SERVER_FAILED);
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "NAI != username");
        PPP_DBG_ERR_CNT(PPP_PHERR_59);
        return;
    }

  #ifdef    __PRODUCT_TYPE_PDSN80

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
               "\r\n PPP_CHAP_ReceiveResponse:the domainindex is (%u)(%u)",
               pstPppInfo->usCDBIndex,
               pstPppInfo->usVirtualDomainIdx);

    if ((pstPppInfo->usCDBIndex >= RM_MAX_APN_NUM)
       && (pstPppInfo->usVirtualDomainIdx >= RM_MAX_APN_NUM))
    {
        PPP_DBG_OK_CNT(PPP_PHOK_823);
        if (VOS_OK != PPP_GetDomainInfoByName(pstPppInfo, pstMsg->ucUsername))
        {

            SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_ERROR_ACCOUNT);
            /*End of liushuang*/
            PPP_CHAP_AAAAuthFailed(pstChapInfo);
            PPP_DBG_ERR_CNT(PPP_PHERR_60);
            return;
        }
    }

    A11_UpdateDomainIndexAtEntryState(pstPppInfo->ulRPIndex, pstPppInfo->usCDBIndex, VOS_FALSE);

    (VOID)VOS_sprintf((char*)pstPppInfo->ucNAI, "%s", pstMsg->ucUsername);

    /* Begin delete by cxf for B02 */

    /* 判断CPU是否过载
    if (1 == g_ulSpuOverloadFlag)
    {
        DebugOut((ULONG)FSU_TID_PPPC, 1, "\r\nPPP_CHAP_ReceiveAuthReq:The cpu is over loading.");
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
        return;
    }*/

    /* 根据LOCK标志判断是否允许激活，如是被LOCK，则不允许它激活，返回协商失败 */
    if ((PPP_DOMAIN_LOCKED == g_pstApnByIndex[pstPppInfo->usCDBIndex].ucLock)
        || (PPP_DOMAIN_LOCKED == g_pstApnByIndex[pstPppInfo->usVirtualDomainIdx].ucLock))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_23);
        PPP_DBG_ERR_CNT(PPP_PHERR_61);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n PPP_CHAP_ReceiveResponse:The domain is locked, the domainindex is (%u)(%u)",
                     pstPppInfo->usCDBIndex,
                     pstPppInfo->usVirtualDomainIdx);
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
        return;
    }

    if(VOS_TRUE == pstPppInfo->bAuthFlag)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                            "\r\n [ppp]PPP_CHAP_ReceiveResponse: pstPppInfo->bAuthFlag is %u bPpcAAAFlag %d",
                            pstPppInfo->bAuthFlag,
                            pstPppInfo->bPpcAAAFlag);

        /* 不需要到AAA鉴权 */
        if (0 == pstPppInfo->bPpcAAAFlag)
        {
            PPP_CHAP_SendStatus(pstPppInfo, CHAP_STATE_SERVER_SUCCESS);
            PPP_PerfInc(&g_stPppPerfStatistic.ulChapSuccess, PERF_TYPE_PPPC_CHAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);

            if (NULL != pstChapInfo->pstAAAAuthReqMsg)
            {
                PPP_Free( pstChapInfo->pstAAAAuthReqMsg);
                pstChapInfo->pstAAAAuthReqMsg = NULL;
                pstMsg = NULL;
            }

            PPP_DBG_OK_CNT(PPP_PHOK_824);
            pstPppInfo->bAuthServer = VRP_NO;
            PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_CHAPSUCCESS, NULL);

            return;
        }
    }

    /* End Added by hyj for B02 */
  #endif
    pstMsg->ulMsgType  = PPPC_AAA_CREAT_REQ;
    pstMsg->ulSDBIndex = pstPppInfo->ulRPIndex;
    pstMsg->usCDBIndex = pstPppInfo->usCDBIndex;
    /*pstMsg->usVPNID = pstPppInfo->usVPNID;*/
    pstMsg->ucPktID = ucId;
    pstMsg->stIMSI = pstPppInfo->stIMSI;

    pstMsg->ucRenegoFlag = pstPppInfo->bPpcAAAFlag;
    /* 输出状态转换调试信息 */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_WAITING_AAA, CHAP_SERVER_STATE);
    pstChapInfo->ucServerState = CHAP_STATE_WAITING_AAA;

#if (VRP_MODULE_SEC_L2TP == VRP_YES)
    /* 设置PPP 与 L2TP 通信数据 */
    if (pstPppInfo->pL2tpPara != NULL)
    {
        L2TP_SESSIONPARA_S *pstOptionalPara = (L2TP_SESSIONPARA_S*)pstPppInfo->pL2tpPara;

        /* 设置验证类型 */
        pstOptionalPara->usAuthenType = L2TP_PPP_CHAP;

        /* 设置被验证用户名 */
        VOS_MemCpy(pstOptionalPara->szAuthenName,
                        pstMsg->ucUsername,
                        pstMsg->ucUsernameLen);
        pstOptionalPara->szAuthenName[pstMsg->ucUsernameLen] = 0x0;

        /* 设置Challenge */
        pstOptionalPara->ulChallengeLen = pstMsg->ucChapChallengeLen;
        VOS_MemCpy(pstOptionalPara->szChallenge,
                        pstMsg->ucChapChallenge,
                        pstMsg->ucChapChallengeLen);
        pstOptionalPara->szChallenge[pstMsg->ucChapChallengeLen] = 0x0;

        /* 设置Response */
        pstOptionalPara->ulResponseLen = pstMsg->ucChapResponseLen;
        VOS_MemCpy(pstOptionalPara->szResponse,
                        pstMsg->ucChapResponse,
                        pstMsg->ucChapResponseLen);
        pstOptionalPara->szResponse[pstMsg->ucChapResponseLen] = 0x0;

        pstOptionalPara->usAuthenID = pstChapInfo->ucChalId;
    }
#endif

    /*向AAA 申请验证*/
    /*PPP_Shell_AuthRequest(pstPppInfo->ulIfIndex, &stMsg);*/
#if 0
    PPP_CHAP_SendAAAAuthReq(pstChapInfo);
#endif
	return;
}

#if 0
/*****************************************************************************
 函 数 名  : PPP_CHAP_ReceiveAAAResult
 功能描述  : Chap模块收到AAA鉴权消息
 输入参数  : AAA_AUTHRSP_S *pMsg
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年11月30日
    作    者   : luofang
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_CHAP_ReceiveAAAResult(AAA_AUTHRSP_S *pMsg)
{
    UCHAR ucResult;
    PPPINFO_S *pstPppInfo;
    PPPCHAPINFO_S *pstChapInfo;

    PPP_TRACE("\r\n---Into PPP_CHAP_ReceiveAAAResult---\r\n");

    /*判断输入参数的有效性*/
    if (NULL == pMsg)
    {
        VOS_DBGASSERT(pMsg);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_CHAP_ReceiveAAAResult: Invalid input parameter!");
        return;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_825);
    GETPPPINFOPTRBYRP(pstPppInfo, pMsg->ulSDBIndex);
    if (pstPppInfo == NULL)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_CHAP_ReceiveAAAResult: User %d isn't exist!", pMsg->ulSDBIndex);
        PPP_DBG_ERR_CNT(PPP_PHERR_62);
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_63);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "\r\n PPP_CHAP_ReceiveAAAResult: User %d  pstChapInfo isn't exist!",
                     pMsg->ulSDBIndex);
        return;
    }

    /* 删除定时器 */
    if (pstChapInfo->ulChalTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
        pstChapInfo->ulChalTimeoutID = 0;
    }

    /* 释放AAA认证请求消息 */
    if (pstChapInfo->pstAAAAuthReqMsg)
    {
        PPP_Free(pstChapInfo->pstAAAAuthReqMsg);
        pstChapInfo->pstAAAAuthReqMsg = NULL;
    }

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_AAARESULT);
    if (pstChapInfo->ucServerState != CHAP_STATE_WAITING_AAA)    /* 状态与事件不符 */
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        PPP_DBG_ERR_CNT(PPP_PHERR_64);
        return;
    }

    /* 认证成功 */
    if (pMsg->ucResult == 0)
    {
        PPP_PerfInc(g_stPppPerfStatistic.pulChapSuccess, PERF_TYPE_PPPC_CHAP_AUTHEN_SUCC_NUM, pstPppInfo->bEhrpdUser);

        /* 验证通过 */
        ucResult = CHAP_STATE_SERVER_SUCCESS;
        PPP_CHAP_SendStatus(pstPppInfo, ucResult);
        PPP_DBG_OK_CNT(PPP_PHOK_826);

        /* 删除定时器 */
        PPP_CHAP_DeleteTimer(pstPppInfo);

        if (pstChapInfo->ulChalInterval != 0)
        {
            if (pstChapInfo->ulChalTimeoutID == 0)
            {
                /* 设置下次chap验证时间 */
                (VOID)VOS_Timer_Create(g_ulPPPTaskId,
                                                       g_ulPppTimeQueID,
                                                       pstChapInfo->ulChalInterval,
                                                       PPP_CHAP_Rechallenge,
                                                       (VOID *) pstPppInfo->ulRPIndex,
                                                       &(pstChapInfo->ulChalTimeoutID), VOS_TIMER_LOOP );
            }
            else
            {
                PPP_DBG_ERR_CNT(PPP_PHERR_65);
                VOS_DBGASSERT(0);
            }
        }

        /* 通知内核 chap Server端验证通过 */
        pstPppInfo->bAuthServer = VRP_NO;
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_CHAPSUCCESS, (CHAR*)pMsg);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_66);

        /* 验证未通过 */
        ucResult = CHAP_STATE_SERVER_FAILED;
        PPP_CHAP_SendStatus(pstPppInfo, ucResult);

        /* 输出状态转换调试信息 */
        CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_SERVER_FAILED, CHAP_SERVER_STATE);
        pstChapInfo->ucClientState = CHAP_STATE_SERVER_FAILED;/* 改变状态 */
        /* 删除定时器 */
        PPP_CHAP_DeleteTimer(pstPppInfo);

        /* 超过验证失败次数, 向内核报CHAP验证失败 */
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_NAK);
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_CHAPFAILED, NULL);
        A11_PPP_TermTag(pstPppInfo->ulRPIndex, Authentication_Fail);
    }

    return;
}


/*****************************************************************************
 函 数 名  : PPP_CHAP_SendAAAAuthReq
 功能描述  : 向AAA发送鉴权请求
 输入参数  : PPPCHAPINFO_S *pstChapInfo
             AAA_AUTHREQ_S *pstMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年2月21日
    作    者   : gxf
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_CHAP_SendAAAAuthReq(PPPCHAPINFO_S *pstChapInfo)
{
    AAA_AUTHREQ_S *pstMsg = NULL;
    ULONG ulRet;
    PPPINFO_S *pstPppInfo;

    PPP_TRACE("\r\n---Into PPP_CHAP_SendAAAAuthReq---\r\n");
    PPP_DBG_OK_CNT(PPP_PHOK_827);

    if (NULL == pstChapInfo)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_67);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_SendAAAAuthReq: pstChapInfo=NULL");
        return;
    }

    pstMsg = pstChapInfo->pstAAAAuthReqMsg;
    if (NULL == pstMsg)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_68);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_SendAAAAuthReq: pstMsg=NULL");
        return;
    }

    pstPppInfo = pstChapInfo->pstPppInfo;
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_69);
        VOS_DBGASSERT(0);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_SendAAAAuthReq: pstChapInfo->pstPppInfo=NULL");
        return;
    }

    /* 用于控制是否将NAI转换成小写软参 */
    if (1 == M_SPM_USER_NAME_LOWERCASE)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_828);
        VOS_lowercase((CHAR*)(((AAA_AUTHREQ_S*)pstMsg)->ucUsername));
    }

    /* BEGIN: Modified by luofang, 2012/9/26 */
    ((AAA_AUTHREQ_S*)pstMsg)->ucPPPFlag =1;
    ulRet = PPP_SendRtMsg(PPP_SELF_CSI,
                         g_ullPppAuthCsi,
                         AUTH_MSG_TYPE_PPP,
                         PPP_AUTH_FLAG,
                         (UCHAR *)pstMsg,
                         sizeof( AAA_AUTHREQ_S ));
    if ( VOS_OK != ulRet )
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_70);
        PPP_Debug_CoreEvent(pstPppInfo, PPP_LOG_ERROR, "PPP_CHAP_SendAAAAuthReq: OSS_Que_Write Err!!");
        return;
    }
    ///TODO:luofang 是否需要内部消息跟踪
    /* 内部消息跟踪 */
    /*  是否需要
    PPP_InternalMsgTrc(PPP_INNERTRC_AAA_REQ, pstMsg, pstPppInfo->ulRPIndex);
    */

    /* 设置超时定时器 */
    VOS_DBGASSERT(pstChapInfo->ulChalTimeoutID == 0);
    ulRet = PGP_Timer_Create(PPP_SELF_CSI,
                             PPP_MSG_TYPE_TIMER,
                             pstChapInfo->ulWaitAuthRspTimeout,
                             PPP_CHAP_AuthRspTimeout,
                             (VOID*)pstPppInfo->ulRPIndex,                    /* Modified by heyajun kf1199 at 2004-08-12 V800R001C01B011 for BYHD03243 */
                             &(pstChapInfo->ulChalTimeoutID),
                             VOS_TIMER_LOOP);
    if (ulRet != VOS_OK)
    {
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "PGP_Timer_Create error!");
        PPP_DBG_ERR_CNT(PPP_PHERR_71);
        /*PPP_CHAP_AAAAuthFailed(pstChapInfo);*/
    }
    PPP_DBG_OK_CNT(PPP_PHOK_829);

    ++pstChapInfo->ucAuthTransmits;
    return ;
}
#endif

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP收到对端验证成功回应, 进入新状态并报CHAP SUCCESS        *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                 ucId:报文ID                                                *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_CHAP_ReceiveSuccess(PPPINFO_S *pstPppInfo, UCHAR ucId)
{
    PPPCHAPINFO_S                      *pstChapInfo = pstPppInfo->pstChapInfo;
    PS_BOOL_ENUM_UINT8                  enIsDoingAccesAuth;
    VOS_UINT32                          ulRet;


    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_72);
        return;
    }

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_AUTHSUCCESS);

    if (pstChapInfo->ucClientState != CHAP_STATE_SEND_RESPONSE)
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        PPP_DBG_ERR_CNT(PPP_PHERR_73);
        return;
    }

    /*删除等待对端验证结果超时定时器*/
    if (pstChapInfo->ulRespTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));
        pstChapInfo->ulRespTimeoutID = 0;
    }

    /* 输出状态转换调试信息 */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_CLIENT_SUCCESS, CHAP_CLIENT_STATE);
    pstChapInfo->ucClientState = CHAP_STATE_CLIENT_SUCCESS; /* 改变状态 */
    /*向内核报 CHAP Client 端验证成功 */
    pstPppInfo->bAuthClient = VRP_NO;

    /* 删除定时器 */
    PPP_CHAP_DeleteTimer(pstPppInfo);

    enIsDoingAccesAuth = PPPC_IsDoingAccessAuth();
    if (PS_TRUE == enIsDoingAccesAuth)
    {
        ulRet = PPP_StopNegoTimer();
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG2("Stop timer fail!\r\n", pstPppInfo->ulRPIndex, enIsDoingAccesAuth);
        }

        /* 接入鉴权完成需要删除PPP实体的节点 */
        PPP_NodeDelete(0);

        /* 如果正在进行接入鉴权,不切换到IPCP阶段 */
        PPPC_ChangeAccessAuthState(PS_FALSE);

        return;
    }

    PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (ULONG)PPP_EVENT_CHAPSUCCESS, NULL);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP收到对端验证失败回应, 进入新状态，                        *
*                并向内核报CHAP Client 端验证失败                            *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                 pPacket:报文头位置                                            *
*                 ucId:报文ID                                                *
*                ulLen:报文数据长度                                            *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceivePacket                                        *
****************************************************************************/
VOID PPP_CHAP_ReceiveFailure(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    CHAR cErrstr[100];

    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_74);
        return;
    }

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_AUTHFAILURE);

    if (pstChapInfo->ucClientState != CHAP_STATE_SEND_RESPONSE)
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        PPP_DBG_ERR_CNT(PPP_PHERR_75);
        return;
    }

    /*删除等待对端验证结果超时定时器*/
    if (pstChapInfo->ulRespTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));
        pstChapInfo->ulRespTimeoutID = 0;
    }

    /*Client端验证失败次数加一*/
    pstChapInfo->usAuthClientFailureTimes += 1;

    /*输出错误调试信息*/
    (VOID)VOS_sprintf(cErrstr, "Client auth failed No. %2d !",
                      pstChapInfo->usAuthClientFailureTimes );
    CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, cErrstr);

    /* 验证失败次数过多, 向上报CHAP DOWN */
    if (pstChapInfo->usAuthClientFailureTimes > PPP_MAXAUTHFAILTIMES)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_76);
        /* 输出状态转换调试信息 */
        CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_CLIENT_FAILED, CHAP_CLIENT_STATE);
        pstChapInfo->ucClientState = CHAP_STATE_CLIENT_FAILED; /* 改变状态 */
        /* 删除定时器 */
        PPP_CHAP_DeleteTimer(pstPppInfo);
        PPP_Core_ReceiveEventFromProtocol (pstPppInfo, (ULONG)PPP_EVENT_CHAPFAILED, NULL);
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP向对端发出验证challenge                                *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ServerLowerUp,PPP_CHAP_ChallengeTimeout,            *
*                 PPP_CHAP_ServerSuccess,PPP_CHAP_Rechallenge                *
****************************************************************************/
VOID PPP_CHAP_SendChallenge(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    UCHAR *pHead, *pPacket;
    USHORT usChal_len, usName_len;
    USHORT usOutLen;
    ULONG ulOffset;
    ULONG ulErrorCode;

    PPP_TRACE("\r\n---Into PPP_CHAP_SendChallenge---\r\n");

    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_77);
        return;
    }

    /* 预留出打PPP报文头的空间 */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* 申请内存 */
    pHead = g_ucPppSendPacketHead;
    if (!pHead)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_78);
        /* 内存申请失败*/
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Malloc error!");
        return;
    }

    /* 防止IP泄露，增加异常打点计数 */
    if (pstPppInfo->ulPeerIPAddr && (0 == pstPppInfo->bReNego))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_79);
    }

    pPacket = pHead + ulOffset;

    usChal_len = pstChapInfo->ucChalLen;
    usName_len = (USHORT )VOS_StrLen((const CHAR *)(pstChapInfo->szHostName));
    usOutLen = CHAP_HEADERLEN + 1 + usChal_len + usName_len;

    PPP_PUTCHAR(CHAP_PACKET_CODE_CHALLENGE, pPacket);            /*CHAP CODE */
    PPP_PUTCHAR(pstChapInfo->ucChalId, pPacket);        /*CHAP ID */
    PPP_PUTSHORT(usOutLen, pPacket);                    /*CHAP LENGTH */

    /* 写challege Length,challenge以及Name*/
    PPP_PUTCHAR(usChal_len, pPacket);
    (VOID)VOS_MemCpy((CHAR *)pPacket, pstChapInfo->szChallenge, (ULONG) usChal_len);
    PPP_INCPTR(usChal_len, pPacket);
    (VOID)VOS_MemCpy((CHAR *)pPacket, pstChapInfo->szHostName, (ULONG)usName_len);
    PPP_INCPTR(usName_len, pPacket );
    pPacket -= usOutLen;

    /*输出调试信息*/
    CHAP_Debug_Packet(pstPppInfo, pPacket, (ULONG)usOutLen, PPP_CHAP, 0);

    /* 直接调用外壳的发送函数 */
    ulErrorCode = PPP_Shell_GetPacketFromCore((CHAR *)pstPppInfo, pHead, pPacket, (ULONG) usOutLen, PPP_CHAP);
    if (ulErrorCode != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_80);
        /*输出调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_ERROR, "Send Packet Failed!");
    }

    if (pstChapInfo->ulChalTimeoutID == 0)
    {
        /* 设置重传chap验证时间 */
        (VOS_VOID)VOS_StartRelTimer((HTIMER)&(pstChapInfo->ulChalTimeoutID), MID_PPPC,
            pstChapInfo->ulTimeOutTime, pstPppInfo->ulRPIndex, PPPC_CHAP_CHALLENGE_RESEND_TIMER,
            VOS_TIMER_LOOP, VOS_TIMER_PRECISION_0);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_81);
        VOS_DBGASSERT(0);
    }

    /* 输出状态转换调试信息 */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_SEND_CHALLENGE, CHAP_SERVER_STATE);
    pstChapInfo->ucServerState = CHAP_STATE_SEND_CHALLENGE; /* 改变状态 */

    ++pstChapInfo->ulChalTransmits;

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP向对端送出验证成功/失败报文                            *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                 ucResult: 验证结果                                            *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceiveResponse,PPP_CHAP_ServerSuccess            *
****************************************************************************/
VOID PPP_CHAP_SendStatus(PPPINFO_S *pstPppInfo, UCHAR ucResult)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    UCHAR *pPacket, *pHead;
    USHORT usOutLen, usMsgLen;
    ULONG ulOffset;
    CHAR msg[256];
    ULONG ulErrorCode;

    if (pstChapInfo == NULL)
    {
        return;
    }

    PPP_DBG_OK_CNT(PPP_PHOK_830);

    /* 预留出打PPP报文头的空间 */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* 申请内存 */
    pHead = g_ucPppSendPacketHead;
    if (!pHead)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_82);
        /* 内存申请失败*/
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Malloc error!");
        return;
    }

    pPacket = pHead + ulOffset;

    /* 输出状态转换调试信息 */
    CHAP_Debug_StateChange(pstPppInfo, ucResult, CHAP_SERVER_STATE);
    pstChapInfo->ucServerState = ucResult;    /* 改变状态 */

    if (ucResult == CHAP_PACKET_CODE_SUCCESS)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_831);
        (VOID)VOS_sprintf(msg, "Welcome to %s.", pstChapInfo->szHostName);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_832);
        (VOID)VOS_sprintf(msg, "Illegal user or password.");
    }

    usMsgLen = (USHORT)VOS_StrLen(msg);

    /*计算报文长度 */
    usOutLen = (USHORT)(CHAP_HEADERLEN + usMsgLen);

    PPP_PUTCHAR(ucResult, pPacket);                /*CHAP CODE */
    PPP_PUTCHAR(pstChapInfo->ucChalId, pPacket);    /*CHAP ID */
    PPP_PUTSHORT(usOutLen, pPacket);                /*CHAP LENGTH */
    /* 报文message */
    (VOID)VOS_MemCpy((CHAR *)pPacket, msg, (ULONG) usMsgLen);
    PPP_INCPTR(usMsgLen, pPacket);

    pPacket -= usOutLen; /* 恢复指向 CHAP 报文头 */

    /*输出报文调试信息*/
    CHAP_Debug_Packet(pstPppInfo, pPacket, (ULONG)usOutLen, PPP_CHAP, 0);

    /* 直接调用外壳的发送函数 */
    ulErrorCode = PPP_Shell_GetPacketFromCore((CHAR *)pstPppInfo, pHead, pPacket, (ULONG )usOutLen, PPP_CHAP);
    if (ulErrorCode != VOS_OK)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_83);
        /*输出调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_ERROR, "Send Packet Failed!");
    }
    PPP_DBG_OK_CNT(PPP_PHOK_833);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：产生一个随机字符串, 同时 Challenge ID 加 1                    *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstChapInfo:CHAP控制块指针                                 *
* OUTPUT       ：随机字符串放入pstChapInfo->szChallenge                        *
*                 随机字符串长度放入pstChapInfo->len                            *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceiveResponse,PPP_CHAP_ServerSuccess            *
****************************************************************************/
VOID PPP_CHAP_GenChallenge(PPPCHAPINFO_S *pstChapInfo)
{
    UCHAR ucChalLen;
    UCHAR *ptr;
    UCHAR i;
    ULONG ulRand = 0;

    ptr = pstChapInfo->szChallenge;

    /* 选出一长度在MIN_CHALLENGE_LENGTH和MAX_CHALLENGE_LENGTH之间的随机长度 */
    ucChalLen = CHAP_MAX_CHALLENGE_LENGTH;
    pstChapInfo->ucChalLen = ucChalLen;

    /*CHAP 控制块 Challenge Id 加 1 */
    pstChapInfo->ucChalId++;

    /* 产生随机字符串 */
    if (SOFTPARA_BIT1398 != 0)
    {
        for (i = 0; i < ucChalLen; i++)
        {
            *ptr = (UCHAR )(0x55);
            ptr++;
        }
    }
    else
    {
        for (i = 0; i < ucChalLen; i++)
        {
            (VOID)PPPC_CRYPT_random((UCHAR*)&ulRand, (SEC_UINT32)sizeof(ULONG));
            *ptr = (UCHAR )(ulRand * 0xff);
            ptr++;
        }
    }

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP向对端送出response报文, 并改变状态                        *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceiveResponse,PPP_CHAP_ServerSuccess            *
****************************************************************************/
VOID PPP_CHAP_SendResponse(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo = pstPppInfo->pstChapInfo;
    UCHAR *pPacket, *pHead;
    UCHAR  *pName;
    USHORT usOutLen, usMdLen, usNameLen;
    ULONG ulOffset;
    ULONG ulErrorCode;

    if (pstChapInfo == NULL)
    {
        return;
    }

    /* 预留出打PPP报文头的空间 */
    ulOffset = PPP_RESERVED_PACKET_HEADER;

    /* 申请内存 */
    pHead = g_ucPppSendPacketHead;
    if (!pHead)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_84);
        /* 内存申请失败*/
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Malloc error!");
        return;
    }

    pPacket = pHead + ulOffset;

    pName     = pstChapInfo->szHostName;
    usMdLen   = pstChapInfo->ucRespLen;
    usNameLen = (USHORT) VOS_StrLen((const CHAR *)pName);

    usOutLen = CHAP_HEADERLEN + sizeof (UCHAR) + usMdLen + usNameLen;

    PPP_PUTCHAR(CHAP_PACKET_CODE_RESPONSE, pPacket);        /* CHAP CODE -RESPONSE */
    PPP_PUTCHAR(pstChapInfo->ucRespId, pPacket);    /* CHAP ID */
    PPP_PUTSHORT(usOutLen, pPacket);                /* CHAP LENGTH */

    /* secret长度和secret  */
    PPP_PUTCHAR(usMdLen, pPacket);
    (VOID)VOS_MemCpy((CHAR * )pPacket, pstChapInfo->szResponse, (ULONG)usMdLen);
    PPP_INCPTR(usMdLen, pPacket);

    /* 添加NAME */
    (VOID)VOS_MemCpy((CHAR *)pPacket, pName, (ULONG)usNameLen);
    PPP_INCPTR(usNameLen, pPacket);
    pPacket -= usOutLen; /* 恢复指向 CHAP 报文头 */

    /*输出报文调试信息*/
    CHAP_Debug_Packet(pstPppInfo, pPacket, (ULONG)usOutLen, PPP_CHAP, 0);

    /* 直接调用外壳的发送函数 */
    ulErrorCode = PPP_Shell_GetPacketFromCore((CHAR *)pstPppInfo, pHead, pPacket, (ULONG)usOutLen, PPP_CHAP);
    if (ulErrorCode != VOS_OK)
    {
        /*输出调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_ERROR, "Send Packet Failed!");
    }

    if (pstChapInfo->ulRespTimeoutID == 0)
    {
        /* 设置重传response时间 */
        (VOS_VOID)VOS_StartRelTimer((HTIMER)&(pstChapInfo->ulRespTimeoutID), MID_PPPC,
            pstChapInfo->ulTimeOutTime, pstPppInfo->ulRPIndex, PPPC_CHAP_RESPONSE_RESEND_TIMER,
            VOS_TIMER_LOOP, VOS_TIMER_PRECISION_0);
    }
    else
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_85);
        VOS_DBGASSERT(0);
    }

    ++pstChapInfo->ulRespTransmits;

    /* 输出状态转换调试信息 */
    CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_SEND_RESPONSE, CHAP_CLIENT_STATE);
    pstChapInfo->ucClientState = CHAP_STATE_SEND_RESPONSE;/* 改变状态 */
    PPP_DBG_OK_CNT(PPP_PHOK_834);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP发送Challenge 超时，进行相应处理                        *
*                 超过最大重传次数，向内核报CHAP 验证失败                    *
*                 否则再次发送Challenge                                        *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：CHAP 定时器ulChalTimeoutID触发                                *
****************************************************************************/
VOS_VOID PPP_CHAP_ChallengeTimeout(VOS_UINT32 ulPppId)
{
    PPPINFO_S *pstPppInfo;
    PPPCHAPINFO_S *pstChapInfo;
    CHAR cErrstr[100];

    /* Modified by heyajun kf1199 at 2004-08-12 V800R001C01B011 for BYHD03243 */
    GETPPPINFOPTRBYRP(pstPppInfo, ulPppId);
    if (pstPppInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_86);
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (pstChapInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_87);
        return;
    }

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_CHALLENGETIMEOUT);

    /*清除定时器*/
    if (pstChapInfo->ulChalTimeoutID)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
        pstChapInfo->ulChalTimeoutID = 0;
    }

    if (pstChapInfo->ucServerState != CHAP_STATE_SEND_CHALLENGE)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_88);
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!");
        return;
    }

    /*输出错误调试信息*/
    (VOID)VOS_sprintf(cErrstr, "Send Challenge No. %2lu !", pstChapInfo->ulChalTransmits);
    CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, cErrstr);

    if (pstChapInfo->ulChalTransmits >= pstChapInfo->ulMaxTransmits)
    {
        pstChapInfo->ulChalTransmits = 0;

        /* 输出状态转换调试信息 */
        CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_SERVER_FAILED, CHAP_SERVER_STATE);
        pstChapInfo->ucServerState = CHAP_STATE_SERVER_FAILED; /* 改变状态 */
        /* 删除定时器 */
        PPP_CHAP_DeleteTimer(pstPppInfo);

        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_MS_NO_RSP);
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_24);


        /*向内核报CHAP 验证失败*/
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_CHLTIMEOUT);
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_CHAPFAILED, NULL);

        if (0 == SOFTPARA_BIT1383)
        {
            A11_ReqNumSubProc(pstPppInfo);
            PPP_DBG_ERR_CNT(PPP_PHERR_89);
        }
        else
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_90);
        }


        return;
    }

    pstChapInfo->ucChalId++;
    /*End of liushuang*/

    PPP_DBG_OK_CNT(PPP_PHOK_835);
    PPP_CHAP_SendChallenge(pstPppInfo);        /*重传 challenge */
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP发送Response 超时，进行相应处理                        *
*                 再次发送Response                                            *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：CHAP 定时器ulRespTimeoutID触发                                *
****************************************************************************/
VOS_VOID PPP_CHAP_ResponseTimeout(VOS_UINT32 ulPppId)
{
    PPPINFO_S *pstPppInfo;
    PPPCHAPINFO_S *pstChapInfo;
    CHAR cErrstr[100];

    /* Modified by heyajun kf1199 at 2004-08-12 V800R001C01B011 for BYHD03243 */
    GETPPPINFOPTRBYRP(pstPppInfo, ulPppId);
    if (pstPppInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_91);
        return;
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (pstChapInfo == 0)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_92);
        return;
    }

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_RESPONSETIMEOUT);

    /*清除定时器*/
    (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));
    pstChapInfo->ulRespTimeoutID = 0L;

    if (pstChapInfo->ucClientState != CHAP_STATE_SEND_RESPONSE)
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!" );
        PPP_DBG_ERR_CNT(PPP_PHERR_93);
        return;
    }

    /*输出错误调试信息*/
    (VOID)VOS_sprintf(cErrstr, "Send Response No. %2lu !", pstChapInfo->ulRespTransmits);
    CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, cErrstr);

    if (pstChapInfo->ulRespTransmits >= pstChapInfo->ulMaxTransmits)
    {
        /* 输出状态转换调试信息 */
        CHAP_Debug_StateChange(pstPppInfo, CHAP_STATE_CLIENT_FAILED, CHAP_CLIENT_STATE);
        pstChapInfo->ucClientState = CHAP_STATE_CLIENT_FAILED; /* 改变状态 */
        /* 删除定时器 */
        PPP_CHAP_DeleteTimer(pstPppInfo);

        /*向内核报CHAP 验证失败*/
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_RSPTIMEOUT);
        PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_CHAPFAILED, NULL);
        PPP_DBG_ERR_CNT(PPP_PHERR_94);
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_836);

    PPP_CHAP_SendResponse(pstPppInfo);        /* 重传 response */

    return;
}

/*****************************************************************************
 函 数 名  : PPP_CHAP_AuthRspTimeout
 功能描述  : CHAP等待AAA验证结果超时
 输入参数  : VOID *pMsg
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2003年2月21日
    作    者   : gxf
    修改内容   : 新生成函数

*****************************************************************************/
VOID PPP_CHAP_AuthRspTimeout(VOID *ulIndex)
{
#if 0
    PPPINFO_S *pstPppInfo = NULL;
    PPPCHAPINFO_S *pstChapInfo = NULL;
    AAA_AUTHREQ_S *pstAuthRspMsg = NULL;
    ULONG ulIdxTmp = (ULONG)ulIndex;

    PPP_TRACE("\r\n---Into PPP_CHAP_AuthRspTimeout---\r\n");
    PPP_DBG_OK_CNT(PPP_PHOK_837);

    /* Modified by heyajun kf1199 at 2004-08-12 V800R001C01B011 for BYHD03243 */
    GETPPPINFOPTRBYRP(pstPppInfo, (ULONG)ulIndex);
    if (NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_95);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_AuthRspTimeout: ulIdxTmp(%d)pstPppInfo=NULL", ulIdxTmp);
        return;
    }

    pstChapInfo = (PPPCHAPINFO_S *)pstPppInfo->pstChapInfo;
    if (NULL == pstChapInfo)
    {
        //VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_96);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_AuthRspTimeout: ulIdxTmp(%d)pstChapInfo=NULL", ulIdxTmp);
        return;
    }

    pstAuthRspMsg = pstChapInfo->pstAAAAuthReqMsg;
    if(NULL == pstAuthRspMsg)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_97);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_AuthRspTimeout: ulIdxTmp(%d)pstAuthRspMsg=NULL", ulIdxTmp);
        return;
    }

    pstPppInfo = pstChapInfo->pstPppInfo;
    if(NULL == pstPppInfo)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_98);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_AuthRspTimeout: ulIdxTmp(%d)pstChapInfo->pstPppInfo=NULL", ulIdxTmp);
        return;
    }

    if(pstChapInfo->ucServerState != CHAP_STATE_WAITING_AAA)
    {
        VOS_DBGASSERT(0);
        PPP_DBG_ERR_CNT(PPP_PHERR_99);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO, "PPP_CHAP_AuthRspTimeout: ulIdxTmp(%d)pstChapInfo->ucServerState(%d)",
                         ulIdxTmp, pstChapInfo->ucServerState);
        return;
    }

    /* 输出事件调试信息 */
    CHAP_Debug_Event(pstPppInfo, CHAP_AAARESULTTIMEOUT);

    /* 清除定时器 */
    VOS_DBGASSERT(pstChapInfo->ulChalTimeoutID);
    (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
    pstChapInfo->ulChalTimeoutID = 0;

    if (pstChapInfo->ucAuthTransmits >= pstChapInfo->ulAuthMaxTransmits)
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_25);
        PPP_DBG_ERR_CNT(PPP_PHERR_100);
        SNMP_SetFailReason(pstPppInfo, FSM_ALARM_AUTH_AAA_NO_RSP);
        /*End of liushuang*/
        PPP_SET_REL_CODE(pstPppInfo, AM_RELCODE_PPP_CHAP_AAATIMEOUT);
        PPP_CHAP_AAAAuthFailed(pstChapInfo);
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_838);
        PPP_CHAP_SendAAAAuthReq(pstChapInfo);
    }
#endif
    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP定时向对端发送challenge                                *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：CHAP 定时器ulChalTimeoutID触发                                *
****************************************************************************/
VOID PPP_CHAP_Rechallenge(VOID *ulIndex)
{
    /* Modified start by heyajun kf1199 at 2004-08-12 V800R001C01B011 for BYHD03243 */
    PPPINFO_S *pstPppInfo = NULL;
    PPPCHAPINFO_S *pstChapInfo;

    GETPPPINFOPTRBYRP(pstPppInfo, (ULONG)ulIndex);
    if (NULL == pstPppInfo)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_101);
        return;
    }

    /* Modified end by heyajun kf1199 at 2004-08-12 V800R001C01B011 for BYHD03243 */
    pstChapInfo = pstPppInfo->pstChapInfo;

    /*输出事件调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_RECHANLLENGE);

    /*清除定时器*/
    (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));
    pstChapInfo->ulChalTimeoutID = 0;

    if (pstChapInfo->ucServerState != CHAP_STATE_SERVER_SUCCESS)
    {
        /*输出错误调试信息*/
        CHAP_Debug_Error(pstPppInfo, PPP_LOG_WARNING, "Illegal event!" );
        PPP_DBG_ERR_CNT(PPP_PHERR_102);
        return;
    }
    PPP_DBG_OK_CNT(PPP_PHOK_839);

    /*向内核报CHAP 重新验证*/
    PPP_Core_ReceiveEventFromProtocol(pstPppInfo, (ULONG)PPP_EVENT_RECHALLENGE, NULL);

    PPP_CHAP_GenChallenge(pstChapInfo);    /*产生challege */
    PPP_CHAP_SendChallenge(pstPppInfo);    /*发送challege */

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：CHAP收到一非法协议, 通知底层DOWN                            *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：                                                            *
****************************************************************************/
VOID PPP_CHAP_ReceiveUnknownCode(PPPINFO_S *pstPppInfo)
{
    /*输出调试信息*/
    CHAP_Debug_Event(pstPppInfo, CHAP_CODEREJECT);

    return;
}

/****************************************************************************
* CREATE DATE  ：2000/06/12                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：根据pstMsg中的信息，产生Response  放入pcResponse中         *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstMsg：验证信息块指针，所用各域意义:                      *
*                ucPktID     :Challenge Id                                  *
*                szUsrName   :对端Hostname用于查找对应Secret                *
*                ucUsrNameLen:对端Hostname长度                              *
*                szPwd       :Challenge                                     *
*                ucPwdLen    :Challenge 长度                                *
*                szResponse  :本端Hostname(当无Secret表时使用此作为Secret)  *
*                ucResponseLen:本端Hostname 长度                            *
* OUTPUT       ：根据MD5 算法产生的pstMsg->szResponse                       *
* RETURN       ：                                                            *
* CALLED BY    ：PPP_CHAP_ReceiveChallenge                                     *
****************************************************************************/
SHORT PPP_CHAP_GenResponse(PPPAUTHMSG_S *pstMsg )
{
    MD5_CTX mdContext;

    UCHAR szResponse[PPP_MAXUSERPWDLEN + 1];

    /* 根据pstMsg->szUsrName查找Secret.如果有替换szResponse?*/

    /*  根据预定算法产生Response */
    PPP_MD5Init(&mdContext);

    /*Challeng Id */
    PPP_MD5Update(&mdContext, &(pstMsg->ucPktID), 1);

    /*secret */
    PPP_MD5Update(&mdContext, (UCHAR*)(pstMsg->szResponse), (ULONG)(pstMsg->ucResponseLen));

    /*Challenge */
    PPP_MD5Update(&mdContext, (UCHAR*)(pstMsg->szPwd), (ULONG)(pstMsg->ucPwdLen));
    PPP_MD5Final(szResponse, &mdContext);

    /*返回response */
    (VOID)VOS_MemCpy((CHAR *)pstMsg->szResponse, szResponse, (ULONG )MD5_SIGNATURE_SIZE);
    pstMsg->szResponse[MD5_SIGNATURE_SIZE] = 0;
    pstMsg->ucResponseLen = MD5_SIGNATURE_SIZE;

    return 1;
}

/****************************************************************************
* CREATE DATE  ：2000/06/09                                                 *
* CREATED BY   ：Zhu Feng Zhi                                               *
* FUNCTION     ：删除定时器                                                    *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
* OUTPUT       ：                                                           *
* RETURN       ：                                                            *
* CALLED BY    ：                                                            *
****************************************************************************/
VOID PPP_CHAP_DeleteTimer(PPPINFO_S *pstPppInfo)
{
    PPPCHAPINFO_S *pstChapInfo = (PPPCHAPINFO_S *)pstPppInfo->pstChapInfo;

    if (pstChapInfo == NULL)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_103);
        return;
    }

    if (pstChapInfo->ulChalTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulChalTimeoutID));   /* 删除challenge定时器 */
        pstChapInfo->ulChalTimeoutID = 0;
    }

    if (pstChapInfo->ulRespTimeoutID != 0)
    {
        (VOID)VOS_StopRelTimer(&(pstChapInfo->ulRespTimeoutID));    /* 删除Response 定时器 */
        pstChapInfo->ulRespTimeoutID = 0;
    }

    return;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
