/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_pcap.h
*
*  Project Code: VISP
*   Module Name:   
*  Date Created: 2009-04-08
*        Author: wuhailan103194
*   Description: 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2009-04-08   wuhailan103194          Create
*
*******************************************************************************/
#ifndef __TCPIP_PCAP_H__
#define __TCPIP_PCAP_H__

#ifdef __cplusplus
extern "C"{
#endif

#include "tcpip/public/debug/tcpip_pcap_api.h"

/*****************************�궨��**************************************************/
#define PCAP_NOTFOUND                    0
#define PCAP_FOUND                       1  

#define PCAP_ENABLE                      1
#define PCAP_DISNABLE                    0

/*�Ƿ�ʹ��PCAP����*/
#define PCAP_IS_ENABLE                   (PCAP_ENABLE == g_ulPcapPktFilterSwitch) 


/*****************************ö�ٽṹ����********************************************/

typedef enum enPcapPktFilterType
{
    PCAP_FILTER_LINK_ETH,
    PCAP_FILTER_LINK_PPP,
    PCAP_FILTER_LINK_ATM,
    PCAP_FILTER_NETWORK,
    PCAP_FILTER_MBUFDESTROY,
    PCAP_FILTER_ALL,
    PCAP_FILTER_END
}PCAP_PKTFILTER_TYPE_E;

/*****************************���ݽṹ����********************************************/

typedef struct PCAP_FILTER_RULE
{
    TCPIP_PKT_FILTER_S stFilterInfo;
    ULONG              ulFilterType;
    ULONG              ulFilterMaxNum;
}PCAP_FILTER_RULE_S;


typedef struct  tagPCAP_PPPHDR
{
    UCHAR  ucAddrField;
    UCHAR  ucProField;
    USHORT usProtocol;
}PCAP_PPPHDR_S;

#define PCAP_PACKET_IN_TAG             0x00000000
#define PCAP_PACKET_OUT_TAG            0x00000032
#define PCAP_PACKET_ALL_TAG            0x00000063


/*****************************ȫ�ֱ�������********************************************/
extern ULONG   g_ulPcapPktFilterSwitch;
extern PCAP_FILTER_RULE_S g_stPcapPktFilterRule;
extern ULONG   g_ulPcapPktFilterMaxNum;
extern TCPIP_PCAP_PKTFILTER_OUTPUT_HOOK_FUNC g_pfTCPIP_Pcap_PktFilterOutput;


/********************************��������*********************************************/
/*Modified by wangchengyang62830 for VISPV1R8C01-252, 2009/6/23 */
extern VOID PCAP_Filter_ClassifyInMBuf(MBUF_S * pstMbuf, ULONG ulFilterType, ULONG ulInOrOut);
/*End of Modified by wangchengyang62830, 2009/6/23 */
extern ULONG PCAP_Filter_EthHaveIt(MBUF_S *pstMbuf);
extern ULONG PCAP_Filter_PppHaveIt(MBUF_S *pstMbuf);
extern ULONG PCAP_Filter_IPHaveIt(MBUF_S *pstMbuf);
extern ULONG PCAP_Filter_GetPppProtocol(MBUF_S *pstMbuf, USHORT *pusProtocol);
extern ULONG PCAP_Filter_MBUFDesroyHaveIt(MBUF_S *pstMbuf);
extern ULONG PCAP_Filter_AtmHaveIt(MBUF_S *pstMbuf);
extern ULONG PCAP_Filter_Output(MBUF_S *pstMbuf, ULONG ulFilterTyp,ULONG ulInOrOute);
extern ULONG PCAP_Filter_InsertLinkHead(MBUF_S *pstMbuf, UCHAR szLinkHead[LEN_16], 
                                            ULONG *pulLinkLen, ULONG *pulLinkType);
extern ULONG PCAP_Filter_GetLinkType(MBUF_S *pstMbuf, ULONG *pulLinkType);


#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif /* __TCPIP_PCAP_H__ */

