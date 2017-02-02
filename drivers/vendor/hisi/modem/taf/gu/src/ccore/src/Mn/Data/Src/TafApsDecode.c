


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafApsDecode.h"
#include "MnComm.h"
#include "TafLog.h"

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_DECODE_C

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/
/*AT AGENTģ����Ϣ��������Ӧ��*/
const TAF_APS_DECODE_IPCP_PROC_STRU g_astTafApsDecIpcpProcTab[]=
{
    /* ����ID */                            /* ���봦���� */
    {APS_PPP_IP_ADDR_ID,                    TAF_APS_DecodeIpcpIpAddr},
    {APS_PPP_PRI_DNS_ID,                    TAF_APS_DecodeIpcpPriDns},
    {APS_PPP_PRI_NBNS_ID,                   TAF_APS_DecodeIpcpPriNbns},
    {APS_PPP_SEC_DNS_ID,                    TAF_APS_DecodeIpcpSecDns},
    {APS_PPP_SEC_NBNS_ID,                   TAF_APS_DecodeIpcpSecNbns}
 };


/******************************************************************************
   5 ����ʵ��
******************************************************************************/


VOS_UINT32 TAF_APS_DecodeIpcpIpAddr(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
)
{
    /*--------------------------------------------------------------
       Peer IP��ַ���ȱ������6
       OPTION TYPE(1 byte) + OPTION LEN(1 btye) + IPV4 LEN(4 bytes)
    --------------------------------------------------------------*/
    if (APS_PPP_IP_ADDR_LEN != ucOptLen)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodeIpcpIpAddr: Invalid IPCP ADDRESS Option. Len:", ucOptLen);
        return VOS_ERR;
    }
    else
    {
        pstIpcpInfo->bitOpIpAddr = VOS_TRUE;
        PS_MEM_CPY(pstIpcpInfo->aucIpAddr, pucProtocolPacket, TAF_IPV4_ADDR_LEN);
    }

    return VOS_OK;
}


VOS_UINT32 TAF_APS_DecodeIpcpPriDns(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
)
{
    /*--------------------------------------------------------------
       Primary DNS��ַ���ȱ������6
       OPTION TYPE(1 byte) + OPTION LEN(1 btye) + IPV4 LEN(4 bytes)
    --------------------------------------------------------------*/
    if (APS_PPP_PRI_DNS_LEN != ucOptLen)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodeIpcpPriDns: Invalid Pri DNS Option Len. Len:", ucOptLen);
        return VOS_ERR;
    }
    else
    {
        pstIpcpInfo->bitOpPrimDns = VOS_TRUE;
        PS_MEM_CPY(pstIpcpInfo->aucPrimDns, pucProtocolPacket, TAF_IPV4_ADDR_LEN);
    }

    return VOS_OK;
}


VOS_UINT32 TAF_APS_DecodeIpcpPriNbns(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
)
{
    /*--------------------------------------------------------------
       Primary NBNS��ַ���ȱ������6
       OPTION TYPE(1 byte) + OPTION LEN(1 btye) + IPV4 LEN(4 bytes)
    --------------------------------------------------------------*/
    if (APS_PPP_PRI_NBNS_LEN != ucOptLen)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodeIpcpPriNbns: Invalid Pri NBNS Option Len. Len:", ucOptLen);
        return VOS_ERR;
    }
    else
    {
        pstIpcpInfo->bitOpPrimNbns = VOS_TRUE;
        PS_MEM_CPY(pstIpcpInfo->aucPrimNbns, pucProtocolPacket, TAF_IPV4_ADDR_LEN);
    }

    return VOS_OK;
}


VOS_UINT32 TAF_APS_DecodeIpcpSecDns(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
)
{
    /*--------------------------------------------------------------
       Secondary DNS��ַ���ȱ������6
       OPTION TYPE(1 byte) + OPTION LEN(1 btye) + IPV4 LEN(4 bytes)
    --------------------------------------------------------------*/
    if (APS_PPP_SEC_DNS_LEN != ucOptLen)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodeIpcpSecDns: Invalid Sec DNS Option Len. Len:", ucOptLen);
        return VOS_ERR;
    }
    else
    {
        pstIpcpInfo->bitOpSecDns = VOS_TRUE;
        PS_MEM_CPY(pstIpcpInfo->aucSecDns, pucProtocolPacket, TAF_IPV4_ADDR_LEN);
    }

    return VOS_OK;
}


VOS_UINT32 TAF_APS_DecodeIpcpSecNbns(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          ucOptLen
)
{
    /*--------------------------------------------------------------
     Secondary NBNS��ַ���ȱ������6
     OPTION TYPE(1 byte) + OPTION LEN(1 btye) + IPV4 LEN(4 bytes)
    --------------------------------------------------------------*/
    if (APS_PPP_SEC_NBNS_LEN != ucOptLen)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodeIpcpSecNbns: Invalid Sec NBNS Option Len. Len:", ucOptLen);
        return VOS_ERR;
    }
    else
    {
        pstIpcpInfo->bitOpSecNbns = VOS_TRUE;
        PS_MEM_CPY(pstIpcpInfo->aucSecNbns, pucProtocolPacket, TAF_IPV4_ADDR_LEN);
    }

    return VOS_OK;
}


TAF_APS_DECODE_IPCP_PROC_FUNC TAF_APS_GetIpcpDecFuncByOptType(VOS_UINT8 ucOptType)
{
    VOS_UINT8                           i;
    VOS_UINT32                          ulTableSize;

    /* ��g_astTafApsDecIpcpProcTab�л�ȡ�������� */
    ulTableSize = sizeof(g_astTafApsDecIpcpProcTab)/sizeof(TAF_APS_DECODE_IPCP_PROC_STRU);

    /* g_astTafApsDecIpcpProcTab������н���ַ� */
    for (i = 0; i < ulTableSize; i++)
    {
        if (g_astTafApsDecIpcpProcTab[i].ucOptType == ucOptType)
        {
            return g_astTafApsDecIpcpProcTab[i].pDecIpcpProcFunc;
        }
    }

    return VOS_NULL_PTR;
}


VOS_UINT32 TAF_APS_DecodeIpcpConfigReqPkt(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucProtocolPacket,
    VOS_UINT16                          usPktLen
)
{
    VOS_UINT8                           ucOptType;
    VOS_UINT8                           ucOptLen;
    VOS_UINT32                          ulResult;
    TAF_APS_DECODE_IPCP_PROC_FUNC       pDecIpcpFunc;

    ulResult     = VOS_OK;
    pDecIpcpFunc = VOS_NULL_PTR;

    /*-------------------------------------------------------------------
       ���� Peer IP/PRI DNS/SEC DNS/PRI NBNS/SEC NBNS
    -------------------------------------------------------------------*/
    while (usPktLen)
    {
        /*--------------------------------------------------------------
           OPTION���ȱ������6
           OPTION TYPE(1 byte) + OPTION LEN(1 btye) + VALUE(4 bytes)
        --------------------------------------------------------------*/
        /*lint -e961*/
        /* ��ȡIPCP Option���� */
        ucOptType   = *pucProtocolPacket++;

        /* ��ȡIPCP Option���� */
        ucOptLen    = *pucProtocolPacket++;
        /*lint +e961*/
        /* ���ʣ���IPCP Packet�ĳ��ȱȸ�IPCP Option�ĳ���С, ��ֱ�Ӷ��� */
        if (usPktLen < ucOptLen)
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF,
                          "TAF_APS_DecodeIpcpConfigReqPkt: Invalid IPCP packet Len.");

            return VOS_ERR;
        }

        /* ���IPCP Option�ĳ���Ϊ0, ��ֱ�Ӷ��� */
        if (0 == ucOptLen)
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF,
                          "TAF_APS_DecodeIpcpConfigReqPkt: IPCP option length is zero.");

            return VOS_ERR;
        }

        /* ���ҽ�����н���Ĳ��� */
        pDecIpcpFunc = TAF_APS_GetIpcpDecFuncByOptType(ucOptType);
        if (VOS_NULL_PTR != pDecIpcpFunc)
        {
            ulResult = pDecIpcpFunc(pstIpcpInfo, pucProtocolPacket, ucOptLen);
            if (VOS_ERR == ulResult)
            {
                TAF_ERROR_LOG(WUEPS_PID_TAF,
                              "TAF_APS_DecodeIpcpConfigReqPkt: IPCP option decode error.");

                return VOS_ERR;
            }
        }
        else
        {
            TAF_WARNING_LOG1(WUEPS_PID_TAF,
                             "TAF_APS_DecodeIpcpConfigReqPkt: Option type not supported %d", ucOptType);
        }

        /* ǰ�����ʱ�Ѿ�������OPTION��ͷ */
        pucProtocolPacket += (ucOptLen - TAF_APS_PPP_IPCP_OPTION_HEAD_LEN);

        usPktLen -= ucOptLen;

    }

    return VOS_OK;
}



VOS_UINT32 TAF_APS_DecodeIpcpPkt(
    TAF_APS_IPCP_INFO_STRU             *pstIpcpInfo,
    VOS_UINT8                          *pucIpcpPkt,
    VOS_UINT16                          usIpcpPktLen
)
{
    VOS_UINT8                           ucConfigType;
    VOS_UINT8                           ucIdentifier;
    VOS_UINT16                          usLength;

    while (usIpcpPktLen > 0)
    {
        /*lint -e961*/
        /* ��ȡConfig type */
        ucConfigType  = *pucIpcpPkt++;

        /* ��ȡIdentifier */
        ucIdentifier  = *pucIpcpPkt++;
        TAF_WARNING_LOG1(WUEPS_PID_TAF,
                         "TAF_APS_DecodeIpcpPkt: Identifier:", ucIdentifier);

        /* ��ȡPacket length */
        usLength  = (*pucIpcpPkt++) << 8;
        usLength |= *pucIpcpPkt++;
        /*lint +e961*/
        if (usIpcpPktLen < usLength)
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF,
                          "TAF_APS_DecodeIpcpPkt: Invalid packet length.");

            return VOS_ERR;
        }

        usIpcpPktLen -= usLength;

        if (usLength < APS_PCO_CONFIG_HDR_LEN)
        {
            TAF_ERROR_LOG(WUEPS_PID_TAF,
                          "TAF_APS_DecodeIpcpPkt: Invalid IPCP packet length.");

            return VOS_ERR;
        }

        /* �Ӱ������м�ȥCONFIG_HDR_LEN */
        usLength -= APS_PCO_CONFIG_HDR_LEN;

        /* ֻ����CONFIG_REQ, ���������� */
        switch (ucConfigType)
        {
            case APS_PPP_CODE_REQ:
                TAF_NORMAL_LOG(WUEPS_PID_TAF,
                               "TAF_APS_DecodeIpcpPkt: CONFIG_REQ IPCP pkt.");
                if (VOS_OK != TAF_APS_DecodeIpcpConfigReqPkt(pstIpcpInfo,
                                                             pucIpcpPkt,
                                                             usLength))
                {
                    return VOS_ERR;
                }

                pucIpcpPkt += usLength;

                break;

            default:

                TAF_WARNING_LOG1(WUEPS_PID_TAF,
                                 "TAF_APS_DecodeIpcpPkt: Invalid IPCP code, Ignore. Type:", ucConfigType);
                pucIpcpPkt += usLength;

                break;
        }
    }

    return VOS_OK;
}
VOS_UINT32 TAF_APS_DecodePapInfo(
    TAF_APS_AUTH_INFO_STRU             *pstAuthInfo,
    VOS_UINT8                           aucPapReqBuf[],
    VOS_UINT16                          usPapReqLen
)
{
    VOS_UINT8                           ucLoc;
    TAF_APS_PAP_PARAM_STRU             *pstPapParam;

    ucLoc = 0;
    pstPapParam = &pstAuthInfo->unAuthParam.stPapParam;

    /* ��Ȩ�ĳ���Ϊ0,���˳� */
    if (0 == usPapReqLen)
    {
        return VOS_OK;
    }

   /***************************************************************
   AUTH_PAP (RFC 1334)
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Code      |  Identifier   |            Length             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   | Peer-ID Length|  Peer-Id ...
   +-+-+-+-+-+-+-+-+-+-+-+-+
   | Passwd-Length |  Password ...
   +-+-+-+-+-+-+-+-+-+-+-+-+-+
   ****************************************************************/

    pstAuthInfo->ucAuthId   = aucPapReqBuf[TAF_APS_PPP_PAP_CODE_LEN];

    /* ����CODE1�ֽ�,Identifier1�ֽ�,����2�ֽ��е�2���ֽ� */
    ucLoc += TAF_APS_PPP_PAP_HEAD_OFFSET;

    /* ����UserName */
    if (aucPapReqBuf[ucLoc] > TAF_MAX_USERNAME_LEN)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodePapInfo: USERNAME LEN LARGER THEN MAX. Len:", aucPapReqBuf[ucLoc]);
        return  VOS_ERR;
    }
    else
    {
        /*lint -e961*/
        pstPapParam->ucUsernameLen = aucPapReqBuf[ucLoc++];
        /*lint +e961*/
        /* ��UserName */
        if (0 != pstPapParam->ucUsernameLen)
        {
            PS_MEM_CPY(pstPapParam->aucUsername,
                       &aucPapReqBuf[ucLoc],
                       pstPapParam->ucUsernameLen);
        }

        /* ����USERNAME */
        ucLoc += pstPapParam->ucUsernameLen;
    }

    /* ����PassWord */
    if (aucPapReqBuf[ucLoc] > TAF_MAX_PASSCODE_LEN)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodePapInfo: PASSWORD LEN LARGER THEN MAX. Len:", aucPapReqBuf[ucLoc]);
        return  VOS_ERR;
    }
    else
    {
        /*lint -e961*/
        pstPapParam->ucPasswordLen = aucPapReqBuf[ucLoc++];
        /*lint +e961*/
        /* ��Password */
        if (0 != pstPapParam->ucPasswordLen)
        {
            PS_MEM_CPY(pstPapParam->aucPassword,
                       &aucPapReqBuf[ucLoc],
                       pstPapParam->ucPasswordLen);
        }

    }

    return  VOS_OK;
}


VOS_UINT32 TAF_APS_DecodeChapInfo(
    TAF_APS_AUTH_INFO_STRU             *pstAuthInfo,
    VOS_UINT8                           aucChapChallengeBuf[],
    VOS_UINT16                          usChapChallengeLen,
    VOS_UINT8                           aucChapResponseBuf[],
    VOS_UINT16                          usChapResponseLen
)
{
    TAF_APS_CHAP_PARAM_STRU            *pstChapParam;

    /******************************************************************
     AUTH_CHAP (RFC 1994)
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |     Code      |  Identifier   |            Length             |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |    Data ...
     +-+-+-+-+

     1. challenge_info & challenge_info_len
     2. challenge_name & challenge_name_len
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |     Code      |  Identifier   |            Length             |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  Value-Size   |  Value ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  Name ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     Value ---> challenge_info
     Name  ---> challenge_name

     3. response_info & response_len
     4. response_name & response_name_len
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |     Code      |  Identifier   |            Length             |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  Value-Size   |  Value ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  Name ...
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     Value ---> response_info
     Name  ---> response_name
    ******************************************************************/

    pstChapParam = &pstAuthInfo->unAuthParam.stChapParam;

    /*Ŀǰ��ʵ���У���ȻҪ��challenge��response����*/
    if ( (0 == usChapChallengeLen)
      || (0 == usChapResponseLen) )
    {
        return VOS_ERR;
    }

    /*******************************************************************
     The Response Value is the one-way hash calculated over a stream of
     octets consisting of the Identifier, followed by (concatenated with)
     the "secret", followed by (concatenated with) the Challenge Value.
     The length of the Response Value depends upon the hash algorithm
     used (16 octets for MD5). Refer to RFC[1994] section 4.1.
    ******************************************************************/
    pstAuthInfo->ucAuthId   = aucChapResponseBuf[TAF_APS_PPP_CHAP_CODE_LEN];

    /* PPP ��������chap challenge buffer �ĽṹΪ:
       code(1B)+id(1B)+length(2B)+challenge_size(1B)+challenge+name */
    /* ����challenge value,���ȹ̶�Ϊ16�ֽ� */
    pstChapParam->ulChallengeLen = aucChapChallengeBuf[TAF_APS_PPP_CHAP_HEAD_OFFSET];

    if (TAF_APS_PPP_CHAP_CHALLNGE_LEN != pstChapParam->ulChallengeLen)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodeChapInfo: Challenge value len error. Len:", pstChapParam->ulChallengeLen);
        return VOS_ERR;
    }

    PS_MEM_CPY(pstChapParam->aucChallenge,
               &aucChapChallengeBuf[TAF_APS_PPP_CHAP_CHALLENGE_HEAD_OFFSET],
               pstChapParam->ulChallengeLen);

    /* ����challenge name */
    pstChapParam->ulChallengeNameLen = (VOS_UINT32)((usChapChallengeLen - TAF_APS_PPP_CHAP_CHALLENGE_HEAD_OFFSET) - pstChapParam->ulChallengeLen);

    if (pstChapParam->ulChallengeNameLen > TAF_APS_PPP_CHAP_CHALLNGE_NAME_LEN)
    {
        pstChapParam->ulChallengeNameLen = TAF_APS_PPP_CHAP_CHALLNGE_NAME_LEN;
    }

    PS_MEM_CPY(pstChapParam->aucChallengeName,
               &aucChapChallengeBuf[TAF_APS_PPP_CHAP_CHALLENGE_HEAD_OFFSET + pstChapParam->ulChallengeLen],
               pstChapParam->ulChallengeNameLen);

    /* PPP ��������chap response buffer �ĽṹΪ:
       code(1B)+id(1B)+length(2B)+response_size(1B)+response+name */
    /* ����response value,���ȹ̶�Ϊ16�ֽ� */
    pstChapParam->ulResponseLen = aucChapResponseBuf[TAF_APS_PPP_CHAP_HEAD_OFFSET];

    if (TAF_APS_PPP_CHAP_RESPONSE_LEN != pstChapParam->ulResponseLen)
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF,
                       "TAF_APS_DecodeChapInfo: Response value len error. Len:", pstChapParam->ulResponseLen);
        return VOS_ERR;
    }

    PS_MEM_CPY(pstChapParam->aucResponse,
               &aucChapResponseBuf[TAF_APS_PPP_CHAP_RESPONSE_HEAD_OFFSET],
               pstChapParam->ulResponseLen);

    /* ����response name */
    pstChapParam->ucResponseNameLen = (VOS_UINT8)((usChapResponseLen - TAF_APS_PPP_CHAP_RESPONSE_HEAD_OFFSET) - pstChapParam->ulResponseLen);

    if (pstChapParam->ucResponseNameLen > TAF_MAX_USERNAME_LEN)
    {
        pstChapParam->ucResponseNameLen = TAF_MAX_USERNAME_LEN;
    }

    PS_MEM_CPY(pstChapParam->aucResponseName,
               &aucChapResponseBuf[TAF_APS_PPP_CHAP_RESPONSE_HEAD_OFFSET + pstChapParam->ulResponseLen],
               pstChapParam->ucResponseNameLen);

    return VOS_OK;
}


VOS_UINT32 TAF_APS_DecodeAuthInfo(
    TAF_APS_AUTH_INFO_STRU             *pstAuthInfo,
    TAF_PPP_REQ_AUTH_CONFIG_INFO_STRU  *pstPppAuthConfig
)
{
    VOS_UINT8                           ucAuthType;
    VOS_UINT32                          ulResult;

    if (VOS_NULL_PTR == pstAuthInfo)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                      "TAF_APS_DecodeAuthInfo: pstPppAuthInfo NULL_PTR!");
        return VOS_ERR;
    }

    /* Ŀ��ṹ��ʼ�� */
    PS_MEM_SET(pstAuthInfo, 0x00, sizeof(TAF_APS_AUTH_INFO_STRU));

   /***************************************************************
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   |     Code      |  Identifier   |            Length             |
   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
   Code       => AuthType
   ****************************************************************/

    ucAuthType = pstPppAuthConfig->enAuthType;

    switch(ucAuthType)
    {
        case PPP_NO_AUTH_TYPE:

            pstAuthInfo->enAuthType = TAF_PDP_AUTH_TYPE_NONE;
            ulResult = VOS_OK;

            break;

        case PPP_PAP_AUTH_TYPE:

            pstAuthInfo->enAuthType = TAF_PDP_AUTH_TYPE_PAP;
            ulResult = TAF_APS_DecodePapInfo(pstAuthInfo,
                                             pstPppAuthConfig->enAuthContent.stPapContent.aucPapReqBuf,
                                             pstPppAuthConfig->enAuthContent.stPapContent.usPapReqLen);
            break;

        case PPP_CHAP_AUTH_TYPE:

            pstAuthInfo->enAuthType = TAF_PDP_AUTH_TYPE_CHAP;
            ulResult = TAF_APS_DecodeChapInfo(pstAuthInfo,
                                              pstPppAuthConfig->enAuthContent.stChapContent.aucChapChallengeBuf,
                                              pstPppAuthConfig->enAuthContent.stChapContent.usChapChallengeLen,
                                              pstPppAuthConfig->enAuthContent.stChapContent.aucChapResponseBuf,
                                              pstPppAuthConfig->enAuthContent.stChapContent.usChapResponseLen);
            break;

        default:

            TAF_ERROR_LOG1(WUEPS_PID_TAF,
                          "TAF_APS_DecodeAuthInfo: Invalid Auth type ", ucAuthType);
            ulResult = VOS_ERR;

            break;
    }

    return ulResult;
}


/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



