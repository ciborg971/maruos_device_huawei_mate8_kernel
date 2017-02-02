/************************************************************************
*                                                                      *
*                             Vsncp_decode.c                           *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2012/12/15                                      *
*  Author:             WANGYONG                                        *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP��VSNCPģ�����Խ���                          *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   ����ļ�������VSNCPЭ��ģ���ȫ���ӿں������ڲ�������            *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_VSNCP_DECODE_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

VOID PPP_VSNCP_EmsTrace(ULONG ulRpIndex, UCHAR ucCode)
{
    switch (ucCode)
    {

        case PPP_VSNCP_CO_PDNID:
            HSGW_EmsTraceByRpIndex(ulRpIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_46);
            break;

        case PPP_VSNCP_CO_APN:
            HSGW_EmsTraceByRpIndex(ulRpIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_47);
            break;

        case PPP_VSNCP_CO_PDN_TYPE:
            HSGW_EmsTraceByRpIndex(ulRpIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_48);
            break;

        case PPP_VSNCP_CO_PDN_ADDR:
            HSGW_EmsTraceByRpIndex(ulRpIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_49);
            break;

        case PPP_VSNCP_CO_ATTACH_TYPE:
            HSGW_EmsTraceByRpIndex(ulRpIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_50);
            break;

        default:
            break;
    }
    return;
}


VOID PPP_VSNCP_ApnLabelToString(UCHAR *pLabelApn,
                                UCHAR *pStringApn,
                                UCHAR ucApnLen)
{
    UCHAR i = 0;
    UCHAR ucLen = 0;
    UCHAR ucLabelLen = 0;

    if ((VOS_NULL_PTR == pStringApn) || (VOS_NULL_PTR == pLabelApn))
    {
        return;
    }

    ucLen = 0;
    while(ucLen < ucApnLen)
    {
        ucLabelLen = *pLabelApn;
        pLabelApn++;
        ucLen++;

        for (i = 0; ((i < ucLabelLen) && (ucLen <= ucApnLen)); i++)
        {
            *pStringApn = *pLabelApn;
            pStringApn++;
            pLabelApn++;
            ucLen++;
        }
        *pStringApn = '.';
        pStringApn++;
    }

    pStringApn--;
    *pStringApn = '\0';
    return;
}


VOID PPP_VSNCP_SaveOptionTypeSequence(VSNP_CONIFG_OPTION_SEQUENCE_S *pstOptSequence,
                                      UCHAR ucType)
{
    ULONG i = 0;
    ULONG ulFreePos = VOS_NULL_DWORD;

    if (VOS_NULL_PTR == pstOptSequence)
    {
        PPPC_WARNING_LOG("pstOptSequence is null!\r\n");
        return;
    }

    for (i = 0; i < PPP_VSNCP_CO_BUTT; i++)
    {
        if (ucType == pstOptSequence->aucConfigOptionType[i])
        {
            return;
        }

        if (VOS_NULL_DWORD == ulFreePos)
        {
            if (0 == pstOptSequence->aucConfigOptionType[i])
            {
                ulFreePos = i;
            }
        }
    }

    if (VOS_NULL_DWORD != ulFreePos)
    {
        pstOptSequence->aucConfigOptionType[ulFreePos] = ucType;
    }

    return;
}

UCHAR *PPP_VSNCP_DecodePactket(UCHAR *pPacket,
                               ULONG ulLen,
                               USHORT *pusPdnId,
                               PPPINFO_S *pstPppInfo)
{
    UCHAR *pucMsg = VOS_NULL_PTR;
    ULONG ulMsgLen = 0;
    PPPCONIFG_OPTION_S *pstConfigOpt = VOS_NULL_PTR;
    LONG lPacketLen = (LONG)(ulLen - VSNCP_HEADERLEN - VSNCP_3GPP2_OUI_LEN);
    UCHAR *pucNewPacket = VOS_NULL_PTR;
    VSNCP_OPTION_DECODE pOptionFunc = VOS_NULL_PTR;
    PDN_PPP_VSNCP_REQ_S *pstVsncpInfo = VOS_NULL_PTR;
    VSNP_CONIFG_OPTION_SEQUENCE_S *pstOptSequence = VOS_NULL_PTR;
    ULONG ulRet = 0;
    ULONG ulFailFlag = VOS_FALSE;

    if ((VOS_NULL_PTR == pPacket) || (VOS_NULL_PTR == pusPdnId) || (VOS_NULL_PTR == pstPppInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return VOS_NULL_PTR;
    }

    if (ulLen < (VSNCP_HEADERLEN + VSNCP_3GPP2_OUI_LEN + VSNCP_CODE_ID_LEN))
    {
        PPPC_WARNING_LOG1("pPacket Len error!\r\n", ulLen);

        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_45);
        return NULL;
    }

    /* �˴������ڴ�Ԥ��500���ֽ�, ���ڻظ�ACKʱʹ�� */
    ulMsgLen = (ulLen + VSNCP_RESERVED_LEN + sizeof(PDN_PPP_VSNCP_REQ_S)
                                 + sizeof(VSNP_CONIFG_OPTION_SEQUENCE_S));
    pucMsg = (UCHAR *)PPP_Malloc(ulMsgLen);
    if (VOS_NULL_PTR == pucMsg)
    {
        PPPC_WARNING_LOG("PPP_Malloc fail!\r\n");
        return VOS_NULL_PTR;
    }
    PPP_MemSet((UCHAR *)pucMsg, 0, ulMsgLen);

    /* ��Ԫ������� */
    pstVsncpInfo = (PDN_PPP_VSNCP_REQ_S *)(pucMsg);
    pstVsncpInfo->usVsncpMsgBodyLen = (USHORT)ulLen;
    pstVsncpInfo->ulTotalMsgLen = ulMsgLen;
    /* ��ԪЯ��˳�� */
    pstOptSequence = (VSNP_CONIFG_OPTION_SEQUENCE_S *)(pucMsg + sizeof(PDN_PPP_VSNCP_REQ_S));
    /* ��Ϣ���� */
    pucNewPacket = (pucMsg + sizeof(PDN_PPP_VSNCP_REQ_S) + sizeof(VSNP_CONIFG_OPTION_SEQUENCE_S));
    /* ������Ϣ */
    VOS_MemCpy(pucNewPacket, pPacket, ulLen);

    /* ָ���һ��OPTION */
    pstConfigOpt = (PPPCONIFG_OPTION_S *)(pPacket + VSNCP_HEADERLEN + VSNCP_3GPP2_OUI_LEN);

    PPP_MemSet((UCHAR *)&g_stVsncpOptionFlag, 0, sizeof(VSNP_CONIFG_OPTION_FLAG_S));

    while (lPacketLen > 0)
    {
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                     "\r\n[ppp]PPP_VSNCP_DecodePactket len [%d][%d]!",
                     pstConfigOpt->ucLen, lPacketLen);
        if (pstConfigOpt->ucLen < VSNCP_CODE_ID_LEN)
        {
            PPPC_WARNING_LOG2("PPP_VSNCP_DecodePactket tyep len err!\r\n",
                         pstConfigOpt->ucType,
                         pstConfigOpt->ucLen);
            ulFailFlag = VOS_TRUE;
            break;
        }

        if (pstConfigOpt->ucType < PPP_VSNCP_CO_BUTT)
        {
            pOptionFunc = g_pVsncpOptionDecode[pstConfigOpt->ucType];
            if(pOptionFunc != VOS_NULL_PTR)
            {
                ulRet = pOptionFunc(pstConfigOpt, pstVsncpInfo);
                if (PPP_VSNCP_DECODE_OK != ulRet)
                {
                    PPP_VSNCP_EmsTrace(pstPppInfo->ulRPIndex, pstConfigOpt->ucType);
                    ulFailFlag = VOS_TRUE;

                    PPPC_WARNING_LOG2("PPP_VSNCP_DecodePactket err!\r\n",
                         ulRet, pstConfigOpt->ucType);
                }
                /* ��������˳�� */
                PPP_VSNCP_SaveOptionTypeSequence(pstOptSequence, pstConfigOpt->ucType);
            }
        }
        /* ���ȸ��� */
        lPacketLen = lPacketLen - (pstConfigOpt->ucLen);
        /* ��λ������һ������ */
        pstConfigOpt = (PPPCONIFG_OPTION_S *)((UCHAR*)pstConfigOpt + (pstConfigOpt->ucLen));
    }

    if (VOS_TRUE == g_stVsncpOptionFlag.ucPDNIDFlag)
    {
        *pusPdnId = (USHORT)pstVsncpInfo->ucPdnId;
    }


    if ((VOS_TRUE != g_stVsncpOptionFlag.ucPDNIDFlag)
        || (*pusPdnId > VSNCP_OPTION_PDNID_MAX))
    {
        HSGW_EmsTraceByRpIndex(pstPppInfo->ulRPIndex, HSGW_EMS_MODULE_PPP, EMS_PPP_45);

        PPPC_WARNING_LOG3("PPP_VSNCP_DecodePactket fail!\r\n", ulFailFlag,
                     g_stVsncpOptionFlag.ucPDNIDFlag,
                     *pusPdnId);
        PPP_Free(pucMsg);
        return VOS_NULL_PTR;
    }

    if (VOS_TRUE == ulFailFlag)
    {
        PPPC_WARNING_LOG1("PPP_VSNCP_DecodePactket fail!\r\n", ulFailFlag);
        PPP_Free(pucMsg);
        return VOS_NULL_PTR;
    }


    return pucMsg;
}
ULONG PPP_VSNCP_PDNIDDecode(PPPCONIFG_OPTION_S *pstConfigOpt,
                            PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucPDNID = 0;

    if ((VOS_NULL_PTR == pstConfigOpt) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return PPP_VSNCP_GENERAL_ERROR;
    }

    if (pstConfigOpt->ucLen != VSNCP_OPTION_PDNID_LEN)
    {
        PPPC_WARNING_LOG1("ucLen err!\r\n", pstConfigOpt->ucLen);
        return PPP_VSNCP_GENERAL_ERROR;
    }

    ucPDNID = *(pstConfigOpt->aucValue);
    /* ���浽��������� */
    pstVsncpInfo->ucPdnId = ucPDNID;
    g_stVsncpOptionFlag.ucPDNIDFlag = VOS_TRUE;

    return PPP_VSNCP_DECODE_OK;
}
ULONG PPP_VSNCP_APNDecode(PPPCONIFG_OPTION_S *pstConfigOpt,
                          PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucAPNLen = 0;

    if ((VOS_NULL_PTR == pstConfigOpt) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return PPP_VSNCP_GENERAL_ERROR;
    }

    /* ��Ч����: 2~102 */
    if (pstConfigOpt->ucLen < VSNCP_CODE_ID_LEN)
    {
        PPPC_WARNING_LOG1("APN len err!\r\n", pstConfigOpt->ucLen);
        return PPP_VSNCP_GENERAL_ERROR;
    }

    ucAPNLen = pstConfigOpt->ucLen - VSNCP_CODE_ID_LEN;
    if (ucAPNLen > HSGW_MAX_APN_NAME_LEN)
    {
        PPPC_WARNING_LOG1("APN len err!\r\n", ucAPNLen);
        return PPP_VSNCP_GENERAL_ERROR;
    }

    if (0 != ucAPNLen)
    {
        /* ��apn��lableȥ�� */
        PPP_VSNCP_ApnLabelToString(pstConfigOpt->aucValue, pstVsncpInfo->szApn, ucAPNLen);
    }
    g_stVsncpOptionFlag.ucAPNNameFlag = VOS_TRUE;

    return PPP_VSNCP_DECODE_OK;
}




ULONG PPP_VSNCP_PDNTypeDecode(PPPCONIFG_OPTION_S *pstConfigOpt,
                              PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucPDNType = 0;

    if ((VOS_NULL_PTR == pstConfigOpt) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");

        return PPP_VSNCP_GENERAL_ERROR;
    }

    if (pstConfigOpt->ucLen != VSNCP_OPTION_PDNTYPE_LEN)
    {
        PPPC_WARNING_LOG1("ucLen err!\r\n", pstConfigOpt->ucLen);
        return PPP_VSNCP_GENERAL_ERROR;
    }

    ucPDNType = *(pstConfigOpt->aucValue);
    if ((ucPDNType < VSNCP_OPTION_PDNTYPE_IPV4)
        || (ucPDNType > VSNCP_OPTION_PDNTYPE_IPV4V6))
    {
        PPPC_WARNING_LOG1("ucPDNType err!\r\n", ucPDNType);
        return PPP_VSNCP_GENERAL_ERROR;
    }

    /* ���浽��������� */
    pstVsncpInfo->ucPdnType = ucPDNType;
    g_stVsncpOptionFlag.ucPDNTypeFlag = VOS_TRUE;

    return PPP_VSNCP_DECODE_OK;
}
ULONG PPP_VSNCP_PDNAddressDecode(PPPCONIFG_OPTION_S *pstConfigOpt,
                                 PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucPDNAddrType = 0;

    if ((VOS_NULL_PTR == pstConfigOpt) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return PPP_VSNCP_GENERAL_ERROR;
    }

    if (pstConfigOpt->ucLen < VSNCP_OPTION_PDNADDR_INIT_LEN)
    {
        PPPC_WARNING_LOG1("ucLen err!\r\n", pstConfigOpt->ucLen);
        return PPP_VSNCP_GENERAL_ERROR;
    }

    ucPDNAddrType = *(pstConfigOpt->aucValue);

    if ((VSNCP_OPTION_PDNADDR_INIT_LEN == pstConfigOpt->ucLen)
        && (0 == ucPDNAddrType))
    {
        g_stVsncpOptionFlag.ucPDNAddrFlag = VOS_TRUE;
    }
    else if ((VSNCP_OPTION_PDNADDR_V4_LEN == pstConfigOpt->ucLen)
        && (VSNCP_OPTION_PDNTYPE_IPV4 == ucPDNAddrType))
    {
        /* ���浽��������� */
        VOS_MemCpy((UCHAR *)(&pstVsncpInfo->ulIpAddr),
                   (pstConfigOpt->aucValue + 1),
                   (VSNCP_OPTION_PDNADDR_V4_LEN - VSNCP_OPTION_PDNADDR_INIT_LEN));
        g_stVsncpOptionFlag.ucPDNAddrFlag = VOS_TRUE;
    }
    else if ((VSNCP_OPTION_PDNADDR_V6_LEN == pstConfigOpt->ucLen)
        && (VSNCP_OPTION_PDNTYPE_IPV6 == ucPDNAddrType))
    {
        /* ���浽��������� */
        g_stVsncpOptionFlag.ucPDNAddrFlag = VOS_TRUE;
        VOS_MemCpy((UCHAR *)(pstVsncpInfo->aucIpv6Addr + PDN_IPV6PREF_LEN),
                   (pstConfigOpt->aucValue + 1),
                   PDN_IPV6INTF_LEN);
    }
    else if ((VSNCP_OPTION_PDNADDR_V4V6_LEN == pstConfigOpt->ucLen)
        && (VSNCP_OPTION_PDNTYPE_IPV4V6 == ucPDNAddrType))
    {
        /* ���浽��������� */
        VOS_MemCpy((UCHAR *)(pstVsncpInfo->aucIpv6Addr + PDN_IPV6PREF_LEN),
                   (pstConfigOpt->aucValue + 1),
                   PDN_IPV6INTF_LEN);

        VOS_MemCpy((UCHAR *)(&pstVsncpInfo->ulIpAddr),
                   (pstConfigOpt->aucValue + 1 + (VSNCP_OPTION_PDNADDR_V6_LEN - VSNCP_OPTION_PDNADDR_INIT_LEN)),
                   (VSNCP_OPTION_PDNADDR_V4_LEN - VSNCP_OPTION_PDNADDR_INIT_LEN));
        g_stVsncpOptionFlag.ucPDNAddrFlag = VOS_TRUE;
    }
    else
    {
        PPPC_WARNING_LOG2("ucPDNAddrType err!\r\n", ucPDNAddrType,
                     pstConfigOpt->ucLen);
        return PPP_VSNCP_GENERAL_ERROR;
    }

    return PPP_VSNCP_DECODE_OK;
}
ULONG PPP_VSNCP_AttachTypeDecode(PPPCONIFG_OPTION_S *pstConfigOpt,
                                 PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucAttchType = 0;

    if ((VOS_NULL_PTR == pstConfigOpt) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");

        return PPP_VSNCP_GENERAL_ERROR;
    }

    if (pstConfigOpt->ucLen != VSNCP_OPTION_ATTACHTYPE_LEN)
    {
        PPPC_WARNING_LOG1("ucLen error!\r\n", pstConfigOpt->ucLen);
        return PPP_VSNCP_GENERAL_ERROR;
    }

    ucAttchType = *(pstConfigOpt->aucValue);
    if ((ucAttchType != VSNCP_OPTION_ATTACHTYPE_INIT)
        && (ucAttchType != VSNCP_OPTION_ATTACHTYPE_HANDOFF))
    {
        PPPC_WARNING_LOG1("ucAttchType error!\r\n", ucAttchType);
        return PPP_VSNCP_GENERAL_ERROR;
    }

    /* ���浽��������� */
    pstVsncpInfo->ucAttchType = ucAttchType;
    g_stVsncpOptionFlag.ucAttachTypeFlag = VOS_TRUE;

    return PPP_VSNCP_DECODE_OK;
}
ULONG PPP_VSNCP_PCODecode(PPPCONIFG_OPTION_S *pstConfigOpt,
                          PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{

    if ((VOS_NULL_PTR == pstConfigOpt) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return PPP_VSNCP_GENERAL_ERROR;
    }

    /* ��Ч����: 3~253 */
    if ((pstConfigOpt->ucLen < (VSNCP_CODE_ID_LEN + 1))
        || (pstConfigOpt->ucLen > HSGW_MAX_PCO_LEN))
    {
        PPPC_WARNING_LOG1("PCO len err!\r\n", pstConfigOpt->ucLen);
        return PPP_VSNCP_GENERAL_ERROR;
    }


    /* ���浽��������� */
    VOS_MemCpy(pstVsncpInfo->szPco,
               pstConfigOpt->aucValue,
               pstConfigOpt->ucLen - VSNCP_CODE_ID_LEN);

    pstVsncpInfo->ucPcoLen = pstConfigOpt->ucLen - VSNCP_CODE_ID_LEN;

    g_stVsncpOptionFlag.ucPCOFlag = VOS_TRUE;

    return PPP_VSNCP_DECODE_OK;
}



ULONG PPP_VSNCP_IPV4DefRouterDecode(PPPCONIFG_OPTION_S *pstConfigOpt,
                                    PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    if ((VOS_NULL_PTR == pstConfigOpt) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return PPP_VSNCP_GENERAL_ERROR;
    }

    if (pstConfigOpt->ucLen != VSNCP_OPTION_IPV4_DEFROUT_LEN)
    {
        PPPC_WARNING_LOG1("ucLen error!\r\n", pstConfigOpt->ucLen);
        return PPP_VSNCP_GENERAL_ERROR;
    }

    /* ���浽��������� */
    VOS_MemCpy(pstVsncpInfo->aucIpv4DefaultRouterAddress,
               pstConfigOpt->aucValue,
               pstConfigOpt->ucLen - VSNCP_CODE_ID_LEN);

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n[ppp]PPP_VSNCP_IPV4DefRouterDecode ok!");
    return PPP_VSNCP_DECODE_OK;
}
ULONG PPP_VSNCP_AddressAllocCauseDecode(PPPCONIFG_OPTION_S *pstConfigOpt,
                                        PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    if ((VOS_NULL_PTR == pstConfigOpt) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return PPP_VSNCP_GENERAL_ERROR;
    }

    if (pstConfigOpt->ucLen != VSNCP_OPTION_ADDRESS_ALLOC_CAUSE_LEN)
    {
        PPPC_WARNING_LOG1("ucLen error!\r\n", pstConfigOpt->ucLen);
        return PPP_VSNCP_GENERAL_ERROR;
    }

    /* ���浽��������� */
    pstVsncpInfo->ucAddressAllocCause = *(pstConfigOpt->aucValue);

    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n[ppp]PPP_VSNCP_AddressAllocCauseDecode ok!");
    return PPP_VSNCP_DECODE_OK;
}
ULONG PPP_VSNCP_IPV6LinkLocalDecode(PPPCONIFG_OPTION_S *pstConfigOpt,
                                    PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    PPP_DebugOut(MID_PPPC, PPP_DEBUG_INFO,
                 "\r\n[ppp]PPP_VSNCP_IPV6LinkLocalDecode ok!");
    return PPP_VSNCP_DECODE_OK;
}


ULONG PPP_VSNCP_ErrorCodeDecode(PPPCONIFG_OPTION_S *pstConfigOpt,
                            PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    UCHAR ucErrorCode = 0;

    if ((VOS_NULL_PTR == pstConfigOpt) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return PPP_VSNCP_GENERAL_ERROR;
    }

    if (pstConfigOpt->ucLen != VSNCP_OPTION_ERRCODE_LEN)
    {
        PPPC_WARNING_LOG1("ucLen error!\r\n", pstConfigOpt->ucLen);
        return PPP_VSNCP_GENERAL_ERROR;
    }

    ucErrorCode = *(pstConfigOpt->aucValue);
    /* ���浽��������� */
    pstVsncpInfo->ucErrorCode = ucErrorCode;

    return PPP_VSNCP_DECODE_OK;
}
ULONG PPP_VSNCP_AmbrDecode(PPPCONIFG_OPTION_S *pstConfigOpt,
                            PDN_PPP_VSNCP_REQ_S *pstVsncpInfo)
{
    if ((VOS_NULL_PTR == pstConfigOpt) || (VOS_NULL_PTR == pstVsncpInfo))
    {
        PPPC_WARNING_LOG("null pointer!\r\n");
        return PPP_VSNCP_GENERAL_ERROR;
    }

    /* ��Ч����: 4~8 */
    if ((pstConfigOpt->ucLen > (VSNCP_AMBR_LEN_3 * 2 + VSNCP_CODE_ID_LEN))
        || (pstConfigOpt->ucLen < (VSNCP_AMBR_LEN_1 * 2 + VSNCP_CODE_ID_LEN)))
    {
        PPPC_WARNING_LOG1("ucLen error!\r\n", pstConfigOpt->ucLen);
        return PPP_VSNCP_GENERAL_ERROR;
    }

    /* ���浽��������� */
    VOS_MemCpy(pstVsncpInfo->aucAMBR,
               pstConfigOpt->aucValue,
               pstConfigOpt->ucLen - VSNCP_CODE_ID_LEN);

    pstVsncpInfo->ucAMBRLen = pstConfigOpt->ucLen - VSNCP_CODE_ID_LEN;

    return PPP_VSNCP_DECODE_OK;
}


VOID PPP_VSNCP_OptionDecodeReg(VOS_VOID)
{
    /* vsncp option��������ע�� */
    /*lint -e63*/
    VSNCP_OPTION_DECODE_REG(PPP_VSNCP_CO_PDNID, PPP_VSNCP_PDNIDDecode);
    VSNCP_OPTION_DECODE_REG(PPP_VSNCP_CO_APN, PPP_VSNCP_APNDecode);
    VSNCP_OPTION_DECODE_REG(PPP_VSNCP_CO_PDN_TYPE, PPP_VSNCP_PDNTypeDecode);
    VSNCP_OPTION_DECODE_REG(PPP_VSNCP_CO_PDN_ADDR, PPP_VSNCP_PDNAddressDecode);
    VSNCP_OPTION_DECODE_REG(PPP_VSNCP_CO_PDN_PCO, PPP_VSNCP_PCODecode);
    VSNCP_OPTION_DECODE_REG(PPP_VSNCP_CO_ERRCODE, PPP_VSNCP_ErrorCodeDecode);
    VSNCP_OPTION_DECODE_REG(PPP_VSNCP_CO_ATTACH_TYPE, PPP_VSNCP_AttachTypeDecode);
    VSNCP_OPTION_DECODE_REG(PPP_VSNCP_CO_IPV4_DEFRTADDR, PPP_VSNCP_IPV4DefRouterDecode);
    VSNCP_OPTION_DECODE_REG(PPP_VSNCP_CO_ADDRESS_ALLOC_CAUSE, PPP_VSNCP_AddressAllocCauseDecode);
    VSNCP_OPTION_DECODE_REG(PPP_VSNCP_CO_APN_AMBR, PPP_VSNCP_AmbrDecode);
    VSNCP_OPTION_DECODE_REG(PPP_VSNCP_CO_LINK_LOCAL_ADDR, PPP_VSNCP_IPV6LinkLocalDecode);
    /*lint +e63*/
    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
