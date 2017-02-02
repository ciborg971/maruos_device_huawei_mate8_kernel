/************************************************************************
 *                                                                      *
 *                             DHCPS_DEC.C                               *
 *                                                                      *
 *  Project Code:       DHCP                                            *
 *  Create Date:        2002/04/10                                      *
 *  Author:                                                             *
 *  Modify Date:                                                        *
 *  Document:  ��DHCP��������ϸ���˵���顷                             *
 *             ��DHCP��������Ҫ���˵���顷                             *
 *  Function:                                                           *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *             Copyright 2000 - 2002 HuaWei Tech, Inc.                  *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 ***********************************************************************/
#include "dhcp_inc.h"
/* add by w00316385 start */
#include "dhcpc_def.h"
/* add by w00316385 end */
#include "dhcpv4s_def.h"
#include "dhcpv4s_type.h"
#include "dhcpv4s_var.h"
#include "dhcpv4s_fun.h"
#include "dhcpv4s_comp.h"
#include "dhcpv4s_dbgcmd.h"


/*****************************************************************************
     Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV4S_DEC_C
/*lint +e767*/

 /*=================================================================
 * ��������:  DHCP_DEC_ParseOption
 * �������:  2002/03/15
 * ��    ��:  ������
 * ��������:  �Ի����������ݰ���DHCPЭ���е�Option������з���
 * �������:
    UCHAR * pucBuffer : ��������DHCP��option��������ʼָ��
    USHORT usLen : ����������
 * �������:
    *pstAnalyzedPacket : dhcp�ı��ķ����ṹ
 *  ��������: ��ȷ�򷵻�VOS_OK�����󷵻�VOS_ERR��
 *  ����˵��:
 *  ���ú���:
 *  ��������:  DHCP_DEC_Decode
*================================================================*/

ULONG DHCPS_DEC_ParseOption (DHCPS_ANALYZEDPACKET_S *pstAnalyzedPacket, UCHAR *pucBuffer,USHORT usLen)
{
    UCHAR    *pucPoint = NULL;
    USHORT    usLenCounter = 0;
    UCHAR  ucTempLen = 0;
    UCHAR *pucTemp = NULL;

    if ((NULL == pucBuffer) || (NULL == pstAnalyzedPacket))
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_DEC_ParseOption: input err!");
        /* Added start by lvwenbin45820 at 2008-12-19 UGW9811V900R001C01 for ADDRESS SUBSYSTEM */
        /*�����쳣��������ͬ*/
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_175);
        /* Added end by lvwenbin45820 at 2008-12-19 UGW9811V900R001C01 for ADDRESS SUBSYSTEM */
        return VOS_ERR;
    }
    usLenCounter = 0;
    pucPoint = pucBuffer;

    /*�������еĻ������Ŀռ� */
    while(usLenCounter < usLen)
    {
        if ( DHCP_OPTION_END == * pucPoint )
        {
            /* ���ֽ����֣��򷵻�*/
            return VOS_OK;
        }
        else if ( DHCP_OPTION_PAD == * pucPoint )
        {
            /*���������ַ��������� */
            pucPoint ++;
            usLenCounter++;
            continue;
        }

        switch ( * pucPoint )
        {
            /*���� OPTION �����ֱ���д��� */
            case DHCP_OPTION_MESSAGE_TYPE:
                pstAnalyzedPacket->ucPacketType = *(pucPoint+2) ;
                /* �� OPTIONS ��صĳ���������ڶ��ֽ� */
                break;
            case DHCP_OPTION_REQUESTED_IP:
                VOS_MemCpy(&(pstAnalyzedPacket->ulRequestedAddr), (pucPoint+2), sizeof(ULONG));
                pstAnalyzedPacket->ulRequestedAddr = pstAnalyzedPacket->ulRequestedAddr;
                break;
            case DHCP_OPTION_OVERLOAD:
                pstAnalyzedPacket->ucOptionOverload =  *(pucPoint+2);
                break;
            case DHCP_OPTION_MAXMESSAGE_SIZE:
                VOS_MemCpy(&(pstAnalyzedPacket->usMaxDhcpSize), (pucPoint+2), sizeof(USHORT));
                pstAnalyzedPacket->usMaxDhcpSize = (USHORT) VOS_NTOHS(pstAnalyzedPacket->usMaxDhcpSize);
                if(pstAnalyzedPacket->usMaxDhcpSize < DHCP_MIN_LEN)
                {
                    pstAnalyzedPacket->usMaxDhcpSize = DHCP_MIN_LEN;
                }
                break;
            case DHCP_OPTION_SERVERID:
                VOS_MemCpy(&(pstAnalyzedPacket->ulServerId), (pucPoint+2), sizeof(ULONG));
                pstAnalyzedPacket->ulServerId = pstAnalyzedPacket->ulServerId;
                break;
            case DHCP_OPTION_PARAMETER_REQUEST_LIST:
                VOS_MemSet(pstAnalyzedPacket->aucParaReqList, 0, sizeof(UCHAR)*256);/*��ʼ������ĳ�ֵ*/
                ucTempLen=*(pucPoint+1);/*ȡ��OPTION55��������ݵĸ���*/
                pucTemp = (pucPoint+2);
                VOS_MemCpy(pstAnalyzedPacket->aucParaReqList, pucTemp, ucTempLen);
                pstAnalyzedPacket->ucParaReqLen = ucTempLen;
                break;
            case DHCP_OPTION_RAPID_COMMIT:
                pstAnalyzedPacket->ucRapidCommitFlag = 1;
                break;
            default:
                /*������Option���Ȳ�������*/
                break;
        }
        /* �� OPTIONS ��صĳ����������һ�ֽ� */
        usLenCounter = usLenCounter + 2 + *(pucPoint+1);
        pucPoint  = pucPoint + 2 + *(pucPoint+1);
    }
    DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_176);
    return VOS_ERR;
}


/*=================================================================
 *  ��������:  ULONG DHCP_DEC_Decode
 *  �������:
 *  ��    ��:  ������
 *  ��������:  DHCP���ĵĽ��뺯��
 *  �������:
    UCHAR *pucUDPBuf�� ��socket���ս�����dhcp���ĵ�ָ��
    USHORT usUDPBufLe�������յ�dhcp���ĵĳ���
    ULONG ulInterfaceIP ������������dhcp���ĵĽӿڵ�ַ����dhcp���ĵ�Ŀ��ip��ַ)
    ULONG ulNetmask ���ӿڵ���������
 *  �������:
    ����������dhcp���ģ������pstAnalyzedPacket��
 *  ��������:  VOS_OK��ʾ�ɹ���VOS_ERR��ʾʧ��
 *  ����˵��:
 *  ���ú���:  DHCP_DEC_ParseOption
 *  ��������:  DHCP_COMM
 *================================================================*/

ULONG DHCPS_DEC_Decode (UCHAR *pucUdpBuf, USHORT usUdpBufLen ,DHCPS_ANALYZEDPACKET_S *pstAnalyzedPacket)
{
    DHCPS_PACKET_S stDhcpPacket;

    if ((NULL == pucUdpBuf) || (NULL == pstAnalyzedPacket))
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_DEC_Decode: pstMbuf NULL!");
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_177);
        return VOS_ERR;
    }

    if(usUdpBufLen < (DHCPS_HEAD_LEN + 5))
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_DEC_Decode: usUdpBufLen %u",
                          usUdpBufLen);

        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_178);
        /* Option������СҲҪ����һ��COOKIE�ͽ�����־����5�ֽ�
        �����������С�� DHCP_HEAD_LEN + 5 ��������쳣��*/
        return VOS_ERR;
    }

    PGP_MemZero(&stDhcpPacket,  sizeof(DHCPS_PACKET_S));
    stDhcpPacket.pstHead = (DHCPS_PACKET_HEAD_S *) pucUdpBuf;
    stDhcpPacket.pucOptions = pucUdpBuf + DHCPS_HEAD_LEN;

    /* op �ֶ��Ƿ�ҲҪ���???*/

    /* ���DHCP���ĵ�option���ֵ�ǰ�ĸ��ֽ��Ƿ�Ϊ magic cookie */
    if (VOS_OK != VOS_MemCmp (stDhcpPacket.pucOptions, DHCPS_OPTIONS_COOKIE, 4))
    {
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_180);
        /*�ȽϽ�������߲�ͬ��˵���� Magic Cookie �ַ��������ݰ�������Ч*/
        return VOS_ERR;
    }

    /* ����д��pstAnalyzedPacket�Ŀռ�������*/
    (VOID)VOS_MemSet((VOID *)pstAnalyzedPacket, 0, sizeof(DHCPS_ANALYZEDPACKET_S));

    /* pstAnalyzedPacket����ز����ĸ�ֵ */

    pstAnalyzedPacket->usPacketLength   = usUdpBufLen;
    /*�����Ӧ��ƥ�伴��,������һ���û�������Ϣ�Ƿ���ͬһ��Xid*/
    pstAnalyzedPacket->ulXid = VOS_NTOHL(stDhcpPacket.pstHead->ulXid);
    pstAnalyzedPacket->usFlags = VOS_NTOHS(stDhcpPacket.pstHead->usFlags);
    pstAnalyzedPacket->ulCiaddr = stDhcpPacket.pstHead->ulCiaddr;
    pstAnalyzedPacket->ulGiaddr = stDhcpPacket.pstHead->ulGiaddr;
    pstAnalyzedPacket->ulYiaddr = stDhcpPacket.pstHead->ulYiaddr;

    pstAnalyzedPacket->ucHtype = stDhcpPacket.pstHead->ucHtype;
    (VOID)VOS_MemCpy(pstAnalyzedPacket->pucChaddr, stDhcpPacket.pstHead->pucChaddr, DHCPS_CHADDR_LEN);

    /*��ʼ�����dhcp���ݰ�����*/
    pstAnalyzedPacket->usMaxDhcpSize = DHCPS_OPTION_MAXLEN + DHCPS_HEAD_LEN;

    /* ����option��(�Ȳ�����Option�ֶε�overload���)*/
    if(VOS_OK!=DHCPS_DEC_ParseOption (pstAnalyzedPacket, stDhcpPacket.pucOptions+4 , (USHORT)(pstAnalyzedPacket->usPacketLength-DHCPS_HEAD_LEN- 4)))
    {
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_181);
        /*���� Options �д��󣬷���*/
        return VOS_ERR;
    }

    /*�����option overload��ѡ����������overload�ֶβ��ֵ�Option */
    if ( (DHCP_OPTION_PAD != *(stDhcpPacket.pstHead->pcFile))
        && (pstAnalyzedPacket->ucOptionOverload & DHCP_OVERLOAD_FILE_FLAG) )
    {
        if(VOS_OK!=DHCPS_DEC_ParseOption(pstAnalyzedPacket, (UCHAR *)stDhcpPacket.pstHead->pcFile, DHCPS_FILE_LEN))
        {
            DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_182);
            /*���� Options �д��󣬷���*/
            return VOS_ERR;
        }
    }
    if ( (DHCP_OPTION_PAD != *(stDhcpPacket.pstHead->pcSname))
        && (pstAnalyzedPacket->ucOptionOverload & DHCP_OVERLOAD_SNAME_FLAG) )
    {
        if(VOS_OK!=DHCPS_DEC_ParseOption(pstAnalyzedPacket, (UCHAR *)stDhcpPacket.pstHead->pcSname, DHCPS_SNAME_LEN))
        {
            DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_183);
            /*���� Options �д��󣬷���*/
            return VOS_ERR;
        }
    }

    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_DEC_Decode : OK");
    return VOS_OK;

}


USHORT DHCPS_IpCkSum(USHORT* pusIpMsg,ULONG ulWordNum)
{
    ULONG ulSum = 0;  /* ����� */
     USHORT usSum;

    if (pusIpMsg == NULL)
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_IpCkSum: input Error.");
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_144);
        return VOS_ERR;
    }

    while (ulWordNum > 0)
    {
        ulSum += *pusIpMsg++;
        ulWordNum --;
    }

    ulSum = (ulSum >> 16) + (ulSum & 0xffff);   /* ��16λ���16λ��� */
    ulSum += (ulSum >> 16);        /* �ӽ�λλ */
    usSum = (USHORT)(~ulSum);

    return (usSum);
}

