/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_pkt.h
*
*  Project Code:
*   Module Name: PTPV2 func
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifndef _PTPV2_PKT_H_
#define _PTPV2_PKT_H_

#ifdef __cplusplus
extern "C" {
#endif

ULONG PTPV2_PktWithCastModeMatch(PTPV2_PORT_S *pstPortInfo, TCPIP_PTP_ADDRINFO_S *pstAddrInfo);

/*******************************************************************************
*    Func Name: PTPV2_GeneralPktProc
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
*  Description:
*        Input: UCHAR* pBuffer:
*               ULONG ulPacketLen:
*               TCPIP_PTP_ADDRINFO_S *pstAddrInfo:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_GeneralPktProc(UCHAR* pBuffer, ULONG ulPacketLen, TCPIP_PTP_ADDRINFO_S *pstAddrInfo);

/*******************************************************************************
*    Func Name: PTPV2_PktAnnSequenceIdCheck
* Date Created: 2014-03-18
*       Author: luogaowei & dutianyi61496
 *  Description: announce�������кż��
*        Input: PTPV2_PORT_S *pstPtpPort:
*               PTPV2_MSGHEADER_S* pstMsgHeader:
*               TCPIP_PTP_ADDRINFO_S *pstPortAddrInfo:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-18   luogaowei & dutianyi61496  Create
*
*******************************************************************************/
ULONG PTPV2_PktAnnSequenceIdCheck(PTPV2_PORT_S *pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, 
                                        TCPIP_PTP_ADDRINFO_S *pstPortAddrInfo);

ULONG PTPV2_PktFlagfieldCheck(PTPV2_PORT_S *pstPtpPort, CHAR *pcFlagfield, ULONG ulMsgType);

/******************************************************************************
*Func Name   : PTPV2_PktGeneralHeaderCheck
*Description : PTP��Ϣͷͨ����Ϸ��Լ�⣬��PTP_PKT_HeaderCheck����
*Input       : PTP_PORT_S       *pstPtpPort   ʱ�Ӷ˿ڿ��ƿ�ָ��
*              PTP_MSGHEADER_S  *pstMsgHeader ��Ϣͷ
*              ULONG            ulPtpMsgType  ��Ϣ����
*              ULONG            ulPacketLen   ���ĳ���
*Output      : .
*Return      : �ɹ�����PTP_OK��ʧ�ܷ��ش�����
*Caution     :
*Calls       :
*Called by   :
*-----------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME           DESCRIPTION
*  2008-6-5             wangchengyang  Create
*******************************************************************************/
ULONG PTPV2_PktGeneralHeaderCheck(PTPV2_PORT_S* pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, 
                                            ULONG ulPtpMsgType, ULONG ulPacketLen);

ULONG PTPV2_BCBuildPktFlagfield(PTPV2_PORT_S* pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, 
                                    ULONG ulPtpMsgType);

ULONG PTPV2_OCBuildPktFlagfield(PTPV2_PORT_S* pstPtpPort, PTPV2_MSGHEADER_S* pstMsgHeader, 
                                    ULONG ulPtpMsgType);


/*
   Bits                                  Octets  Offset
   7     6     5     4   3   2   1   0
   |transportSpecific|  messageType  |     1       0
   |    reserved     |  versionPTP   |     1       1
   |           messageLength         |     2       2
   |           domainNumber          |     1       4
   |           reserved              |     1       5
   |           flagField             |     2       6
   |           correctionField       |     8       8
   |           reserved              |     4       16
   |           sourcePortIdentity    |     10      20
   |           sequenceId            |     2       30
   |           controlField          |     1       32
   |           logMessageInterval    |     1       33
*/
ULONG PTPV2_PktHeaderCheck(PTPV2_PORT_S* pstPtpPort, UCHAR *pucBuffer, ULONG ulPtpMsgType,
                          ULONG ulPacketLen, TCPIP_PTP_ADDRINFO_S* pstAddrInfo);

ULONG PTPV2_BuildAnnPktHeader(PTPV2_PORT_S* pstPtpPort,  PTPV2_MSGHEADER_S* pstMsgHeader);

ULONG PTPV2_ComputeSeqId(VOID *pThis, MBUF_S *pstMbuf);

ULONG PTPV2_OverMacSndAnnPkt(VOID *pThis, VOID *pData, VOID *pAddr);

VOID PTPV2_PrintHeader(PTPV2_MSGHEADER_S *pstMsgHeader, TCPIP_PTP_ADDRINFO_S *pstAddrInfo);

ULONG PTPV2_GrandMasterIDCheck(PTPV2_ANNOUNCE_MSG_S* pstAnnMsg);

ULONG PTPV2_BuildAnnPktClockQa(PTPV2_ANNOUNCE_MSG_S* pstAnnMsg, TCPIP_PTP_CLOCK_QA_S* pstClockQa);

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of _PTPV2_FUNC_h_   */

