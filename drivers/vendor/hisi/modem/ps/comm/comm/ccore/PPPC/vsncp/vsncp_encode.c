/************************************************************************
*                                                                      *
*                             Vsncp_encode.c                           *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2012/12/15                                      *
*  Author:             WANGYONG                                        *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP的VSNCP模块属性编码                          *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件定义了VSNCP协议模块的全部接口函数和内部处理函数            *
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
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_VSNCP_ENCODE_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

ULONG PPP_VSNCP_StrToAPNLabel(UCHAR *pApnLabel, UCHAR *pApnStr)
{
    UCHAR ucApnStrLen = 0;
    UCHAR i = 0;
    UCHAR ucLabelLen = 0;

    if ((VOS_NULL_PTR == pApnLabel) || (VOS_NULL_PTR == pApnStr))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    ucApnStrLen = (UCHAR)VOS_StrLen(pApnStr);
    if ((0 == ucApnStrLen) || (100 <= ucApnStrLen))
    {
        PPPC_WARNING_LOG1("ucApnStrLen ERR!\r\n", ucApnStrLen);

        return VOS_ERR;
    }

    if ('.' == *pApnStr)
    {
        PPPC_WARNING_LOG1("first is err!\r\n", *pApnStr);
        return VOS_ERR;
    }

    for (i = 0; i <= ucApnStrLen; i++)
    {
        *(pApnLabel + i + 1) = *(pApnStr + i);
        if (('.' == *(pApnStr + i)) || (0x0 == *(pApnStr + i)))
        {
            *(pApnLabel + i - ucLabelLen) = ucLabelLen;
            ucLabelLen = 0;
            continue;
        }
        ucLabelLen++;
    }
    return VOS_OK;
}



ULONG PPP_VSNCP_PDNIDEncode(UCHAR *pucPacket,
                            PDN_CONTEXT_S *pstPDNContext,
                            ULONG *pulLen,
                            PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    /* 保存到消息中 */
    PPP_PUTCHAR(PPP_VSNCP_CO_PDNID, pucPacket);
    PPP_PUTCHAR(VSNCP_OPTION_PDNID_LEN, pucPacket);
    PPP_PUTCHAR(pstPDNContext->stEhrpd.ucPdnId, pucPacket);

    *pulLen = VSNCP_OPTION_PDNID_LEN;

    return VOS_OK;
}
ULONG PPP_VSNCP_APNEncode(UCHAR *pucPacket,
                          PDN_CONTEXT_S *pstPDNContext,
                          ULONG *pulLen,
                          PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucAPNLen = 0;
    ULONG ulRet = 0;
    HSGW_APN_INFO_S *pstHsgwApn = VOS_NULL_PTR;
    UCHAR *pucAPN = VOS_NULL_PTR;

    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

#if 0
    if ('\0' == pstVsncpInfo->szApn[0])
    {
        ulRet = USM_GetApnCfgByApnIndex(pstPDNContext->stEhrpd.usApnIndex, &pstHsgwApn);
        if ((ulRet != VOS_OK) || (VOS_NULL_PTR == pstHsgwApn))
        {
            PPP_DBG_ERR_CNT(PPP_PHERR_756);
            PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                         "\r\n[ppp]PPP_VSNCP_APNEncode USM_GetApnCfgByApnIndex fail apnidex(%u)!",
                         pstPDNContext->stEhrpd.usApnIndex);
            return VOS_ERR;
        }
        pucAPN = pstHsgwApn->aucApnInfoName;
    }
    else
    {
        pucAPN = pstVsncpInfo->szApn;
    }

    /* apn长度 */
    ucAPNLen = (UCHAR)VOS_StrLen(pucAPN);
    if (ucAPNLen > M_CFG_MAX_APN_STRING_LEN)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1453);
        ucAPNLen = M_CFG_MAX_APN_STRING_LEN;
    }
#endif

    /* apn长度 */
    ucAPNLen = pstPDNContext->stEhrpd.stApn.ucApnLen;
    if (ucAPNLen > M_CFG_MAX_APN_STRING_LEN)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1453);
        ucAPNLen = M_CFG_MAX_APN_STRING_LEN;
    }

    /* 保存到消息中 */
    PPP_PUTCHAR(PPP_VSNCP_CO_APN, pucPacket);
    /* 长度需要加一个label的长度 */
    PPP_PUTCHAR((ucAPNLen + VSNCP_CODE_ID_LEN + 1), pucPacket);

    pucAPN = pstPDNContext->stEhrpd.stApn.aucApn;

    /* 转换为label */
    ulRet = PPP_VSNCP_StrToAPNLabel(pucPacket, pucAPN);
    if (ulRet != VOS_OK)
    {
        PPPC_WARNING_LOG("PPP_VSNCP_StrToAPNLabel fail!\r\n");
        return VOS_ERR;
    }

    *pulLen = (ucAPNLen + VSNCP_CODE_ID_LEN + 1);

    return VOS_OK;
}
ULONG PPP_VSNCP_PDNTypeEncode(UCHAR *pucPacket,
                              PDN_CONTEXT_S *pstPDNContext,
                              ULONG *pulLen,
                              PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucPdnType = 0;

    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }
    /*ucPdnType = ((pstPDNContext->ucPdnCapability) & (pstVsncpInfo->ucPdnType));*/
    ucPdnType = (UCHAR)(pstPDNContext->stEhrpd.enPdnType);

    /* 保存到消息中 */
    PPP_PUTCHAR(PPP_VSNCP_CO_PDN_TYPE, pucPacket);
    PPP_PUTCHAR(VSNCP_OPTION_PDNTYPE_LEN, pucPacket);
    PPP_PUTCHAR(ucPdnType, pucPacket);

    *pulLen = VSNCP_OPTION_PDNTYPE_LEN;

    return VOS_OK;
}






ULONG PPP_VSNCP_AttachTypeEncode(UCHAR *pucPacket,
                                 PDN_CONTEXT_S *pstPDNContext,
                                 ULONG *pulLen,
                                 PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    /* 保存到消息中 */
    PPP_PUTCHAR(PPP_VSNCP_CO_ATTACH_TYPE, pucPacket);
    PPP_PUTCHAR(VSNCP_OPTION_ATTACHTYPE_LEN, pucPacket);
    /*PPP_PUTCHAR(pstVsncpInfo->ucAttchType, pucPacket);*/
    PPP_PUTCHAR(pstPDNContext->stEhrpd.ucAttchType, pucPacket);

    *pulLen = VSNCP_OPTION_ATTACHTYPE_LEN;

    return VOS_OK;
}


ULONG PPP_VSNCP_PDNAddressEncode(UCHAR *pucPacket,
                                 PDN_CONTEXT_S *pstPDNContext,
                                 ULONG *pulLen,
                                 PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucLen = 1;   /* 初始化为1 */
    UCHAR *pucLenPos = 0;
    UCHAR ucPdnType = 0;
    UCHAR *pucAddress = VOS_NULL_PTR;

    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

#if 0
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n[ppp]PPP_VSNCP_PDNAddressEncode ucDelayFlag[%u]!",
                 pstPDNContext->stEhrpd.ucDelayFlag);

    ucPdnType = ((pstPDNContext->ucPdnCapability) & (pstVsncpInfo->ucPdnType));

    /* 保存到消息中 */
    PPP_PUTCHAR(PPP_VSNCP_CO_PDN_ADDR, pucPacket);
    pucLenPos = pucPacket;
    PPP_PUTCHAR((ucLen + VSNCP_CODE_ID_LEN), pucPacket);
    PPP_PUTCHAR(ucPdnType, pucPacket);

    if (ucPdnType & VSNCP_OPTION_PDNTYPE_IPV6)
    {
        ucLen += (VSNCP_OPTION_PDNADDR_V6_LEN - VSNCP_OPTION_PDNADDR_INIT_LEN);
        PPP_PUTCHARPTR((pstPDNContext->aucIpV6Addr + PDN_IPV6INTF_LEN),
                       pucPacket,
                       PDN_IPV6INTF_LEN);
    }

    if (ucPdnType & VSNCP_OPTION_PDNTYPE_IPV4)
    {
        ucLen += (VSNCP_OPTION_PDNADDR_V4_LEN - VSNCP_OPTION_PDNADDR_INIT_LEN);
        PPP_PUTADDR(pstPDNContext->ulIpV4Addr, pucPacket);
    }

    /* 刷新长度 */
    *pucLenPos = (ucLen + VSNCP_CODE_ID_LEN);
#endif

    ucPdnType = (UCHAR)(pstPDNContext->stEhrpd.stPdnAddress.enPdnType);
    pucAddress = pstPDNContext->stEhrpd.stPdnAddress.aucAddress;

    /* 计算长度 */
    ucLen += (UCHAR)VOS_StrLen(pucAddress);

    /* 保存到消息中 */
    PPP_PUTCHAR(PPP_VSNCP_CO_PDN_ADDR, pucPacket);
    PPP_PUTCHAR((ucLen + VSNCP_CODE_ID_LEN), pucPacket);
    PPP_PUTCHAR(ucPdnType, pucPacket);

    PPP_PUTCHARPTR(pucAddress, pucPacket, ucLen);

    *pulLen = (ucLen + VSNCP_CODE_ID_LEN);

    return VOS_OK;
}
ULONG PPP_VSNCP_AddressAllocCauseEncode(UCHAR *pucPacket,
                                        PDN_CONTEXT_S *pstPDNContext,
                                        ULONG *pulLen,
                                        PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucPdnIndicatorCause = 0;

    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

#if 0
    ucPdnIndicatorCause = NEW_PDN_TYPE_SUCCESS;
    ucPdnType = ((pstPDNContext->ucPdnCapability) & (pstVsncpInfo->ucPdnType));
    if (ucPdnType != pstVsncpInfo->ucPdnType)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1454);
        ucPdnIndicatorCause = NEW_PDN_TYPE_DUE_TO_NETWORK_PREFERNCE;
    }
#endif

    ucPdnIndicatorCause = pstPDNContext->stEhrpd.ucAddressAllocCause;

    /* 保存到消息中 */
    PPP_PUTCHAR(PPP_VSNCP_CO_ADDRESS_ALLOC_CAUSE, pucPacket);
    PPP_PUTCHAR(VSNCP_OPTION_ADDRESS_ALLOC_CAUSE_LEN, pucPacket);
    PPP_PUTCHAR(ucPdnIndicatorCause, pucPacket);

    *pulLen = VSNCP_OPTION_ADDRESS_ALLOC_CAUSE_LEN;

    return VOS_OK;
}
ULONG PPP_VSNCP_PCOEncode(UCHAR *pucPacket,
                          PDN_CONTEXT_S *pstPDNContext,
                          ULONG *pulLen,
                          PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucPcoLen = 0;
    UCHAR *pucPco = VOS_NULL_PTR;

    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    if (0 == pstPDNContext->stEhrpd.stPco.ucPcoLen)
    {
        PPPC_WARNING_LOG("ucPcoLen is 0!\r\n");
        *pulLen = 0;
        return VOS_OK;
    }

#if 0
    if (pstVsncpInfo->ucPcoLen > VSNCP_OPTION_PCO_MAX_LEN)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1456);
        pstVsncpInfo->ucPcoLen = VSNCP_OPTION_PCO_MAX_LEN;
    }

    /* 保存到消息中 */
    PPP_PUTCHAR(PPP_VSNCP_CO_PDN_PCO, pucPacket);
    PPP_PUTCHAR((pstVsncpInfo->ucPcoLen + VSNCP_CODE_ID_LEN), pucPacket);
    PPP_PUTCHARPTR(pstVsncpInfo->szPco, pucPacket, pstVsncpInfo->ucPcoLen);
#endif

    ucPcoLen = pstPDNContext->stEhrpd.stPco.ucPcoLen;
    pucPco = pstPDNContext->stEhrpd.stPco.aucPco;

    if (ucPcoLen > VSNCP_OPTION_PCO_MAX_LEN)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_1456);
        ucPcoLen = VSNCP_OPTION_PCO_MAX_LEN;
    }

    /* 保存到消息中 */
    PPP_PUTCHAR(PPP_VSNCP_CO_PDN_PCO, pucPacket);
    PPP_PUTCHAR((ucPcoLen + VSNCP_CODE_ID_LEN), pucPacket);
    PPP_PUTCHARPTR(pucPco, pucPacket, ucPcoLen);

    *pulLen = (ucPcoLen + VSNCP_CODE_ID_LEN);

    return VOS_OK;
}


ULONG PPP_VSNCP_IPV4DefRouterEncode(UCHAR *pucPacket,
                                    PDN_CONTEXT_S *pstPDNContext,
                                    ULONG *pulLen,
                                    PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    /* 保存到消息中 */
    PPP_PUTCHAR(PPP_VSNCP_CO_IPV4_DEFRTADDR, pucPacket);
    PPP_PUTCHAR(VSNCP_OPTION_IPV4_DEFROUT_LEN, pucPacket);
    /*PPP_PUTADDR(pstPDNContext->stEhrpd.ulRouterAddrV4, pucPacket);*/

    PPP_PUTCHARPTR(pstPDNContext->stEhrpd.aucIpv4DefaultRouterAddress,
                   pucPacket, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    *pulLen = VSNCP_OPTION_IPV4_DEFROUT_LEN;

    return VOS_OK;
}


ULONG PPP_VSNCP_IPV6LinkLocalEncode(UCHAR *pucPacket,
                                    PDN_CONTEXT_S *pstPDNContext,
                                    ULONG *pulLen,
                                    PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    /* 保存到消息中 */
    PPP_PUTCHAR(PPP_VSNCP_CO_LINK_LOCAL_ADDR, pucPacket);
    PPP_PUTCHAR(VSNCP_OPTION_IPV6_LINKLOCAL_LEN, pucPacket);
    PPP_PUTCHARPTR((pstPDNContext->stEhrpd.aucLinkLocalAddr + PDN_IPV6INTF_LEN),
                   pucPacket,
                   PDN_IPV6INTF_LEN);

    *pulLen = VSNCP_OPTION_IPV6_LINKLOCAL_LEN;

    return VOS_OK;
}
UCHAR PPP_VSNCP_GetAMBRLength(ULONG ulAMBR)
{
    ULONG ulAmbrKbps = 0;
    UCHAR ucAMBRLen = 0;

    /* 转换为KBPS */
    ulAmbrKbps = ulAMBR/1000;

    if (ulAmbrKbps >= VSNCP_AMBR_256M_65280M_START)
    {
        ucAMBRLen = VSNCP_AMBR_LEN_3;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_130M_256M_START)
    {
        ucAMBRLen = VSNCP_AMBR_LEN_2;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_17M_128M_START)
    {
        ucAMBRLen = VSNCP_AMBR_LEN_2;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_8700K_16000K_START)
    {
        ucAMBRLen = VSNCP_AMBR_LEN_2;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_576K_8640K_START)
    {
        ucAMBRLen = VSNCP_AMBR_LEN_1;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_64K_568K_START)
    {
        ucAMBRLen = VSNCP_AMBR_LEN_1;
    }
    else
    {
        ucAMBRLen = VSNCP_AMBR_LEN_1;
    }

    return (UCHAR)((UCHAR)(ucAMBRLen * 2) + VSNCP_CODE_ID_LEN);
}
UCHAR PPP_VSNCP_TransAMBR(ULONG ulAMBR, UCHAR *pucAMBR)
{
    UCHAR ucOffset = 0;
    ULONG ulAmbrKbps = 0;
    UCHAR ucAMBRLen = 0;
    ULONG ulValueStart = 0;
    ULONG ulValueStep = 0;
    UCHAR ucBitStart = 0;

    /* 转换为KBPS */
    ulAmbrKbps = ulAMBR/1000;

    /* 如果AAA下发为0，则携带为全F */
    if (0 == ulAmbrKbps)
    {
        pucAMBR[ucOffset] = VSNCP_AMBR_ZERO;
        return VSNCP_AMBR_LEN_1;
    }

    if (ulAmbrKbps >= VSNCP_AMBR_256M_65280M_START)
    {
        ulValueStart = VSNCP_AMBR_256M_65280M_START;
        ulValueStep = VSNCP_AMBR_256M_65280M_STEP;
        ucBitStart = VSNCP_AMBR_256M_65280M_BIT_START;
        ucAMBRLen = VSNCP_AMBR_LEN_3;
        *(pucAMBR + ucOffset) = VSNCP_AMBR_8640K_BIT;
        ucOffset++;
        *(pucAMBR + ucOffset) = VSNCP_AMBR_256M_BIT;
        ucOffset++;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_130M_256M_START)
    {
        ulValueStart = VSNCP_AMBR_130M_256M_START;
        ulValueStep = VSNCP_AMBR_130M_256M_STEP;
        ucBitStart = VSNCP_AMBR_130M_256M_BIT_START;
        ucAMBRLen = VSNCP_AMBR_LEN_2;
        *(pucAMBR + ucOffset) = VSNCP_AMBR_8640K_BIT;
        ucOffset++;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_17M_128M_START)
    {
        if (ulAmbrKbps > VSNCP_AMBR_17M_128M_END)
        {
            ulAmbrKbps = VSNCP_AMBR_17M_128M_END;
        }
        ulValueStart = VSNCP_AMBR_17M_128M_START;
        ulValueStep = VSNCP_AMBR_17M_128M_STEP;
        ucBitStart = VSNCP_AMBR_17M_128M_BIT_START;
        ucAMBRLen = VSNCP_AMBR_LEN_2;
        *(pucAMBR + ucOffset) = VSNCP_AMBR_8640K_BIT;
        ucOffset++;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_8700K_16000K_START)
    {
        if (ulAmbrKbps > VSNCP_AMBR_8700K_16000K_END)
        {
            ulAmbrKbps = VSNCP_AMBR_8700K_16000K_END;
        }
        ulValueStart = VSNCP_AMBR_8700K_16000K_START;
        ulValueStep = VSNCP_AMBR_8700K_16000K_STEP;
        ucBitStart = VSNCP_AMBR_8700K_16000K_BIT_START;
        ucAMBRLen = VSNCP_AMBR_LEN_2;
        *(pucAMBR + ucOffset) = VSNCP_AMBR_8640K_BIT;
        ucOffset++;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_576K_8640K_START)
    {
        ulValueStart = VSNCP_AMBR_576K_8640K_START;
        ulValueStep = VSNCP_AMBR_576K_8640K_STEP;
        ucBitStart = VSNCP_AMBR_576K_8640K_BIT_START;
        ucAMBRLen = VSNCP_AMBR_LEN_1;
    }
    else if (ulAmbrKbps >= VSNCP_AMBR_64K_568K_START)
    {
        ulValueStart = VSNCP_AMBR_64K_568K_START;
        ulValueStep = VSNCP_AMBR_64K_568K_STEP;
        ucBitStart = VSNCP_AMBR_64K_568K_BIT_START;
        ucAMBRLen = VSNCP_AMBR_LEN_1;
    }
    else
    {
        ulValueStart = VSNCP_AMBR_1K_63K_START;
        ulValueStep = VSNCP_AMBR_1K_63K_STEP;
        ucBitStart = VSNCP_AMBR_1K_63K_BIT_START;
        ucAMBRLen = VSNCP_AMBR_LEN_1;
    }

    *(pucAMBR + ucOffset) = ucBitStart + (UCHAR)((ulAmbrKbps - ulValueStart) / ulValueStep);

    return ucAMBRLen;
}

#if 0

UCHAR PPP_VSNCP_AMBREncode(PPPVSNCPINFO_S *pstVSNCPInfo, UCHAR *pucAMBR)
{
    UCHAR aucAMBRUL[VSNCP_AMBR_LEN_3] = {0};
    UCHAR aucAMBRDL[VSNCP_AMBR_LEN_3] = {0};
    UCHAR ucAMBRULLen = 0;
    UCHAR ucAMBRDLLen = 0;
    UCHAR ucAMBRLen = 0;
    UCHAR *pucCOLen = VOS_NULL_PTR;
    UCHAR *pucAMBRTmp = VOS_NULL_PTR;

    if ((VOS_NULL_PTR == pucAMBR) || (VOS_NULL_PTR == pstVSNCPInfo))
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_765);
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_LOG,
                     "\r\n[ppp]PPP_VSNCP_AMBREncode input is null!");
        return 0;
    }

    /* 保存到消息中 */
    PPP_PUTCHAR(PPP_VSNCP_CO_APN_AMBR, pucAMBR);
    /* 后续更新长度 */
    pucCOLen = pucAMBR;
    PPP_INCPTR(VSNCP_CODE_LEN, pucAMBR);
    ucAMBRLen = ucAMBRLen + VSNCP_CODE_ID_LEN;

    if (pstVSNCPInfo->ucApnAmbrDLFlag)
    {
        ucAMBRDLLen = PPP_VSNCP_TransAMBR(pstVSNCPInfo->ulApnAmbrDL,
                                          aucAMBRDL);
        pucAMBRTmp = pucAMBR;
        PPP_VSNCP_SET_AMBR(ucAMBRDLLen, aucAMBRDL, pucAMBRTmp);
    }

    if (pstVSNCPInfo->ucApnAmbrULFlag)
    {
        ucAMBRULLen = PPP_VSNCP_TransAMBR(pstVSNCPInfo->ulApnAmbrUL,
                                          aucAMBRUL);
        pucAMBRTmp = (pucAMBR + VSNCP_AMBR_LEN_1);
        PPP_VSNCP_SET_AMBR(ucAMBRULLen, aucAMBRUL, pucAMBRTmp);
    }

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n[ppp]PPP_VSNCP_AMBREncode AMBR ucAMBRULLen[%u]ucAMBRULLen[%u]!",
                 ucAMBRDLLen, ucAMBRULLen);

    ucAMBRLen += ((ucAMBRDLLen > ucAMBRULLen) ? ((UCHAR)(ucAMBRDLLen * 2)) : ((UCHAR)(ucAMBRULLen * 2)));

    /* 修改长度 */
    *pucCOLen = ucAMBRLen;

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n[ppp]PPP_VSNCP_AMBREncode AMBR ucAMBRLen[%u]!",
                 ucAMBRLen);

    return ucAMBRLen;
}
#endif
ULONG PPP_VSNCP_AmbrEncode(UCHAR *pucPacket,
                          PDN_CONTEXT_S *pstPDNContext,
                          ULONG *pulLen,
                          PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)

{
    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    if (0 == pstVsncpInfo->ucAMBRLen)
    {
        PPPC_WARNING_LOG("ucAMBRLen is 0!\r\n");
        *pulLen = 0;
        return VOS_OK;
    }

    /* 保存到消息中 */
    PPP_PUTCHAR(PPP_VSNCP_CO_APN_AMBR, pucPacket);
    PPP_PUTCHAR((pstVsncpInfo->ucAMBRLen + VSNCP_CODE_ID_LEN), pucPacket);
    PPP_PUTCHARPTR(pstVsncpInfo->aucAMBR, pucPacket, pstVsncpInfo->ucAMBRLen);

    *pulLen = pstVsncpInfo->ucAMBRLen + VSNCP_CODE_ID_LEN;

    return VOS_OK;
}
ULONG PPP_VSNCP_DefAPNIndEncode(UCHAR *pucPacket,
                                PDN_CONTEXT_S *pstPDNContext,
                                ULONG *pulLen,
                                PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucDefAPNInd = VSNCP_OPTION_NOT_DEF_APN;
    ULONG ulRet = 0;

    if ((VOS_NULL_PTR == pucPacket) || (VOS_NULL_PTR == pstPDNContext)
        || (VOS_NULL_PTR == pulLen) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_ERR;
    }

    if ('\0' == pstVsncpInfo->szApn[0])
    {
        /* 是否是default apn */
        ulRet = USM_IsDefaultApn(pstPDNContext->ulRpIndex, pstPDNContext->stEhrpd.usApnIndex);
        if (VOS_TRUE == ulRet)
        {
            PPP_DBG_OK_CNT(PPP_PHOK_1457);
            ucDefAPNInd = VSNCP_OPTION_DEF_APN;
            /* 保存到消息中 */
            PPP_PUTCHAR(PPP_VSNCP_CO_DEFAULT_APN_IND, pucPacket);
            PPP_PUTCHAR(VSNCP_OPTION_DEF_APN_IND_LEN, pucPacket);
            PPP_PUTCHAR(ucDefAPNInd, pucPacket);
            *pulLen = VSNCP_OPTION_DEF_APN_IND_LEN;
        }
    }

    return VOS_OK;
}


VOID PPP_VSNCP_OptionEncodeReg(VOS_VOID)
{
    /* vsncp option编码函数注册 */
    /*lint -e63*/
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_PDNID, PPP_VSNCP_PDNIDEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_APN, PPP_VSNCP_APNEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_PDN_TYPE, PPP_VSNCP_PDNTypeEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_PDN_ADDR, PPP_VSNCP_PDNAddressEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_PDN_PCO, PPP_VSNCP_PCOEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_IPV4_DEFRTADDR, PPP_VSNCP_IPV4DefRouterEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_ADDRESS_ALLOC_CAUSE, PPP_VSNCP_AddressAllocCauseEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_LINK_LOCAL_ADDR, PPP_VSNCP_IPV6LinkLocalEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_APN_AMBR, PPP_VSNCP_AmbrEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_DEFAULT_APN_IND, PPP_VSNCP_DefAPNIndEncode);
    VSNCP_OPTION_ENCODE_REG(PPP_VSNCP_CO_ATTACH_TYPE, PPP_VSNCP_AttachTypeEncode);
    /*lint +e63*/
    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
