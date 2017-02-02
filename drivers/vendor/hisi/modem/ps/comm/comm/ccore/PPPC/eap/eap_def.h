
/************************************************************************
 *                                                                      *
 *                             eap_def.h                                *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2010/07/05                                      *
 *  Author:             WANGYONG                                        *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP��EAPЭ��ģ��˽�к궨��                      *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 * Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
 *                     ALL RIGHTS RESERVED                              *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   ����ļ�������EAPЭ��ģ���ȫ��˽�к궨��                          *
 *                                                                      *
 ************************************************************************/

#if( VRP_MODULE_LINK_PPP == VRP_YES )

#ifndef      _EAP_DEF_H_
#define      _EAP_DEF_H_

#ifdef      __cplusplus
extern "C" {
#endif      /* end of __cplusplus */

/* Code + ID + length */
#define EAP_HEADERLEN      4

#define EAP_PAYLOAD_TYPELEN        1

#define EAP_PACKET_CODE_INNER_ERR      5
/*  EAP state */
#define EAP_STATE_INITIAL                     0
#define EAP_STATE_SEND_REQUEST_FOR_IDENTITY   1
#define EAP_STATE_SEND_REQUEST                2
#define EAP_STATE_SUCCESS                     3
#define EAP_STATE_FAILED                      4
#define EAP_STATE_WAITING_AAA                 5

#define PPP_GET_EAP_CODE(ucCode,pEapMsg) (ucCode = (*(VOS_UINT8 *)pEapMsg))
#define PPP_GET_EAP_ID(ucID,pEapMsg) (ucID = (*(VOS_UINT8 *)((VOS_UINT8 *)pEapMsg + EAP_ID_OFFSET)))
#define PPP_GET_EAP_LEN(usCiLen,pEapMsg) {usCiLen = (*(VOS_UINT16 *)((VOS_UINT8 *)pEapMsg + EAP_LEN_OFFSET)); usCiLen = VOS_HTONS(usCiLen);}
#define PPP_GET_EAP_TYPE(ucType,pEapMsg) (ucType = (*((VOS_UINT8 *)pEapMsg + EAP_TYPE_OFFSET)))
#define PPP_GET_EAP_NAI(pucNAI,pEapMsg) (pucNAI = ((VOS_UINT8 *)pEapMsg + EAP_NAI_OFFSET))


/*  ���EAP���� */
#define EAP_PAYLOAD_MAX_LEN         2048
/*  ���ID���� */
#define EAP_ID_MAX_LEN              260
/*  �����EAP���� */
#define EAP_PAYLOAD_SEND_MAX_LEN    1500

#define EAP_CODE_OFFSET  0      /* codeƫ�� */
#define EAP_ID_DEFAULT  1      /* Identifier��Ĭ��ֵ */
#define EAP_ID_OFFSET   1       /* Identifier��EAP-Message�е�ƫ�� */
#define EAP_LEN_OFFSET  2      /* Length��EAP-Message�е�ƫ�� */
#define EAP_TYPE_OFFSET 4     /* TYPE��EAP-Message�е�ƫ�� */
#define EAP_NAI_OFFSET  5      /* NAI��EAP-Message�е�ƫ�� */

/* EAP-Message����С����,����EAP-Request/Response����,��С���Ȼ�Ҫ��1,
   ����EAP-Success/Failure����,�����4 */
#define EAP_MSG_MIN_LEN 4

/* EAP-Request/Response�е���Ϣ���� */
#define EAP_IDENTITY 1
#define EAP_RESPONSE 2


/* ֪ͨdiam auth�Ķ�ʱ��ʱ���ʹ��� */
#define EAP_WAITAAARSPTIMEOUT  45000
#define EAP_MAXAUTHTRANSMITS   1

#define CHAP_WAITLNSAUTHTIME         10000;/*added by wangliang ht04409 at 2006-2-13 for BYHD09482*/

/*EAP ����CORE���¼����� */
#define EAP_EVENT_CLIENTLOWERUP    0
#define EAP_EVENT_SERVERLOWERUP    1
#define EAP_EVENT_LOWERDOWN        2

/*EAP �ڲ����¼����� */
#define EAP_SERVERLOWERUP      0
#define EAP_CLIENTLOWERUP      1
#define EAP_LOWERDOWN          2
#define EAP_RECEIVEREQUEST_FROMAAA   3
#define EAP_RECEIVERESPONSE    4
#define EAP_AUTHSUCCESS_FROMAAA        5
#define EAP_AUTHFAILURE_FROMAAA        6
#define EAP_REQUESTTIMEOUT_FORID    7
#define EAP_REQUESTTIMEOUT     8
#define EAP_INITIALIZATION     9
#define EAP_REAUTH            10
#define EAP_CODEREJECT         11
#define EAP_AAARESULT          12
#define EAP_AAARESULTTIMEOUT   13
#define EAP_ERROREVENT         14

/*״̬����*/
#define EAP_CLIENT_STATE       0
#define EAP_SERVER_STATE       1

#define PPP_EAP_USER_NAME_256BYTE_MAX_NUM        12000


/* �¼�λ */
#define PPP_DIAM_AUTH_EVENTBIT    0x1<<4


#define PPP_EAP_AAAAuthFailed(pstEapInfo) \
{   \
    PPPINFO_S *pstPPPInfo = pstEapInfo->pstPppInfo;     \
    UCHAR *pucEAP = pstEapInfo->pucEAP;                 \
    if (pucEAP)                                          \
    {                                                   \
        PPP_Free (pucEAP);                              \
        pstEapInfo->pucEAP = NULL;                      \
        pstEapInfo->usEAPLen = 0;                       \
    }                                                   \
    EAP_Debug_StateChange(pstPPPInfo, EAP_STATE_FAILED, EAP_SERVER_STATE) ; \
    pstEapInfo->ucState = EAP_STATE_FAILED ; \
    PPP_Core_ReceiveEventFromProtocol (pstPPPInfo,(ULONG)PPP_EVENT_EAPFAILED,NULL) ;   \
}


/* hmac_sha�㷨ʹ�� */
#define EAP_ARITH_PPP_BLOCK_COPY(from, to, len) VOS_MemCpy(to, from, len)
#define SHA1HANDSOFF
#define EAP_ARITH_REMOVAL(data, bitnum) (((data) << (bitnum)) | ((data) >> (32 - (bitnum))))

#if (VRP_LITTLE_ENDIAN == VRP_YES)
#define EAP_ARITH_BLOCK_A(i) (pDataBlock64->uiIntData[i] = (EAP_ARITH_REMOVAL(pDataBlock64->uiIntData[i], 24) & 0xFF00FF00) \
                                | (EAP_ARITH_REMOVAL(pDataBlock64->uiIntData[i], 8) & 0x00FF00FF))
#else
#define EAP_ARITH_BLOCK_A(i) pDataBlock64->uiIntData[i]
#endif
#define EAP_ARITH_BLOCK(i) (pDataBlock64->uiIntData[i & 15] = EAP_ARITH_REMOVAL(pDataBlock64->uiIntData[(i + 13) & 15] ^ pDataBlock64->uiIntData[(i + 8) & 15] \
                                       ^ pDataBlock64->uiIntData[(i + 2) & 15] ^ pDataBlock64->uiIntData[i & 15], 1))

#define EAP_ARITH_REMOVAL_A(a, b, c, d, e, i) e += ((b & (c ^ d)) ^ d) + EAP_ARITH_BLOCK_A(i) + 0x5A827999 + EAP_ARITH_REMOVAL(a, 5); b = EAP_ARITH_REMOVAL(b, 30);
#define EAP_ARITH_REMOVAL_B(a, b, c, d, e, i) e += ((b & (c ^ d)) ^ d) + EAP_ARITH_BLOCK(i) + 0x5A827999 + EAP_ARITH_REMOVAL(a, 5); b = EAP_ARITH_REMOVAL(b, 30);
#define EAP_ARITH_REMOVAL_C(a, b, c, d, e, i) e += (b ^ c ^ d) + EAP_ARITH_BLOCK(i) + 0x6ED9EBA1 + EAP_ARITH_REMOVAL(a, 5); b = EAP_ARITH_REMOVAL(b, 30);
#define EAP_ARITH_REMOVAL_D(a, b, c, d, e, i) e += (((b | c) & d) | (b & c)) + EAP_ARITH_BLOCK(i) + 0x8F1BBCDC + EAP_ARITH_REMOVAL(a, 5); b = EAP_ARITH_REMOVAL(b, 30);
#define EAP_ARITH_REMOVAL_E(a, b, c, d, e, i) e += (b ^ c ^ d) + EAP_ARITH_BLOCK(i) + 0xCA62C1D6 + EAP_ARITH_REMOVAL(a, 5); b = EAP_ARITH_REMOVAL(b, 30);



#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _EAP_DEF_H_ */

#endif     /* #if( VRP_MODULE_LINK_PPP == VRP_YES ) */


