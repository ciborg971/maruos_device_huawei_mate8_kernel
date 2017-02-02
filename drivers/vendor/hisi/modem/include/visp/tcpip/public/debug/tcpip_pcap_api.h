
#ifndef __TCPIP_PCAP_API_H__
#define __TCPIP_PCAP_API_H__

#ifdef __cplusplus
extern "C"{
#endif

/*****************************�궨��**************************************************/

/*��·����, ĿǰVISP��֧��ETH��PPP���ͺ�ATM���� */
#define PCAP_LINK_TYPE_ETH               1 /* Ethernet (10Mb) */
#define PCAP_LINK_TYPE_PPP               9 /* Point-to-point Protocol */
#define PCAP_LINK_TYPE_ATM_RFC1483      11 /* LLC/SNAP encapsulated atm */

#define PCAP_LINK_NULL                   0 /* no link-layer encapsulation */
#define PCAP_LINK_TYPE_ETH3MB            2 /* Experimental Ethernet (3Mb) */
#define PCAP_LINK_TYPE_AX25              3 /* Amateur Radio AX.25 */
#define PCAP_LINK_TYPE_PRONET            4 /* Proteon ProNET Token Ring */
#define PCAP_LINK_TYPE_CHAOS             5 /* Chaos */
#define PCAP_LINK_TYPE_IEEE802           6 /* IEEE 802 Networks */
#define PCAP_LINK_TYPE_ARCNET            7 /* ARCNET */
#define PCAP_LINK_TYPE_SLIP              8 /* Serial Line IP */
#define PCAP_LINK_TYPE_FDDI             10 /* FDDI */
#define PCAP_LINK_TYPE_RAW              12 /* raw IP */
#define PCAP_LINK_TYPE_SLIP_BSDOS       13 /* BSD/OS Serial Line IP */
#define PCAP_LINK_TYPE_PPP_BSDOS        14 /* BSD/OS Point-to-point Protocol */

#define PCAP_FILEHEAD_LEN               24 /* PCAP����װ���ļ�ͷ���� */
#define PCAP_FILEHEAD_MAGIC     0xa1b2c3d4 /* PCAP����װ���ļ�ͷ�е�ħ�����ֶ�ֵ */
#define PCAP_FILEHEAD_VERSION_MAJOR      2 /* PCAP����װ���ļ�ͷ�е�VERSION MAJOR�ֶ�ֵ */
#define PCAP_FILEHEAD_VERSION_MINOR      4 /* PCAP����װ���ļ�ͷ�е�VERSION MINOR�ֶ�ֵ */
#define PCAP_FILEHEAD_SNAPLEN       0xffff /* Ĭ��֧�����65535�ֽڳ��ȵı������ */

#define PCAP_MACADDRLEN                  6 /* physical��ַ���� */

/*Added by wangchengyang62830 for VISPV1R8C01-252, 2009/6/23 */
#define PCAP_DIRECTION_IN                2 /* ֧�ֱ��Ľ��շ����ϻ�ȡ���� */
#define PCAP_DIRECTION_OUT               1 /* ֧�ֱ��ķ��ͷ����ϻ�ȡ���� */
#define PCAP_DIRECTION_ALL               0 /* ֧�ֱ��Ľ��պͷ��ͷ����ϻ�ȡ���� */
/* End of Added by wangchengyang62830, 2009/6/23 */

/*****************************ö�ٽṹ�����붨��********************************************/
typedef enum enPcapPktFilterErrorCode
{
    PCAP_OK = VOS_OK,                   /* 0 OK    */
    PCAP_ERR,                           /* 1 δ֪���� */
    PCAP_ERR_PARAWRONG,
    PCAP_ERR_INVALID_SWITCH,
    PCAP_ERR_POINTER_NULL,
    PCAP_ERR_INVALID_TYPE,
    PCAP_ERR_IFISNULL,
    PCAP_ERR_INVALID_IFTYPE,
    PCAP_ERR_INVALID_DIRECTION
}TCPIP_PCAP_ERRCODE_E;

/*****************************���ݽṹ����********************************************/

typedef struct TCPIP_TIMEVAL
{
    ULONG  tv_sec;       /* no. of seconds */
    ULONG  tv_usec;      /* no. of micro seconds */
}TCPIP_TIMEVAL_S;

typedef struct TCPIP_PCAP_PKTHDR
{
    TCPIP_TIMEVAL_S ts;     /* time stamp */
    ULONG           caplen; /* length of portion present */
    ULONG           len;    /* length this packet (off wire) */
}TCPIP_PCAP_PKTHDR_S;

typedef struct TCPIP_PCAP_FILE_HEADER
{
    ULONG    magic;
    USHORT   version_major;
    USHORT   version_minor;
    LONG     thiszone;     /* gmt to local correction */
    ULONG    sigfigs;      /* accuracy of timestamps */
    ULONG    snaplen;      /* max length saved portion of each pkt */
    ULONG    linktype;     /* data link type (DLT_*) */
}TCPIP_PCAP_FILE_HEADER_S;


typedef struct TCPIP_PKT_FILTER
{
    ULONG ulIfIndex;
    ULONG ulProtocol;
    ULONG ulSrcIP;
    ULONG ulDstIP;
    UCHAR ucSrcMac[PCAP_MACADDRLEN];
    UCHAR ucDstMac[PCAP_MACADDRLEN];
    /*Added by wangchengyang62830 for VISPV1R8C01-252, 2009/6/23 */
    ULONG ulInOrOut;   /*  0-Ĭ��ֵ����ʾ֧�ַ��ͺͽ��գ�1-��ʾ���ͣ�2--��ʾ���� */
    /* End of Added by wangchengyang62830, 2009/6/23 */
}TCPIP_PKT_FILTER_S;

typedef ULONG (*TCPIP_PCAP_PKTFILTER_OUTPUT_HOOK_FUNC)(CHAR *pcBuf, ULONG ulMsglen, ULONG ulLinkType);

/********************************��������*********************************************/

/*******************************************************************************
*    Func Name: TCPIP_Pcap_RegFuncPktFilterOutput
* Date Created: 2009-04-08
*       Author: wuhailan103194
*  Description: �ֲ��ȡ���������Ϣע�ṳ��
*        Input: TCPIP_PCAP_PKTFILTER_OUTPUT_HOOK_FUNC pfFunc:��������ָ��
*       Output: 
*       Return: �ɹ�VOS_OK,��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-08   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_Pcap_RegFuncPktFilterOutput(TCPIP_PCAP_PKTFILTER_OUTPUT_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_Pcap_SetPacketFilter
* Date Created: 2009-04-08
*       Author: wuhailan103194
*  Description: �ֲ��ȡ���Ĺ��ܽӿ����ü����˹������ýӿ�
*        Input: ULONG ulSwitch:���ܿ���
*               ULONG ulFilterType:��������
*               TCPIP_PKT_FILTER_S *pstFilterRule:���˹���
*               ULONG ulMaxPkt:����������������Ŀ
*       Output: 
*       Return: �ɹ�VOS_OK,��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-08   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_Pcap_SetPacketFilter(ULONG ulSwitch, ULONG ulFilterType, TCPIP_PKT_FILTER_S *pstFilterRule, ULONG ulMaxPkt);

/*******************************************************************************
*    Func Name: TCPIP_Pcap_GetFileHead
* Date Created: 2009-04-10
*       Author: wuhailan103194
*  Description: ��ȡPCAP����װ���ļ�ͷ��Ϣ,��ǰͨ��VISP�ýӿڸ���ȥ�ķ�װͷwin32Сͷ���¶�����ֵΪ:
*               ��̫��·����:
*               D4 C3 B2 A1 02 00 04 00 00 00 00 00 00 00 00 00
*               FF FF 00 00 01 00 00 00
*               ����
*               PPP��Ե���·����:
*               D4 C3 B2 A1 02 00 04 00 00 00 00 00 00 00 00 00
*               FF FF 00 00 09 00 00 00
*               ����������:
*               stPcapFileHdr.linktype = ulLinkType;
*               stPcapFileHdr.snaplen  = 0xffff;
*               stPcapFileHdr.magic    = 0xa1b2c3d4;
*               stPcapFileHdr.version_major = 2;
*               stPcapFileHdr.version_minor = 4;  
*               �û�Ҳ���Բο�VISPͷ�ļ��е�TCPIP_PCAP_FILE_HEADER_S�ṹ�ֶ���������Ethereal�ļ�ͷ��ʽ����
*        Input: ULONG ulLinkType:��·����
*       Output: CHAR szFileHead[PCAP_FILEHEAD_LEN]:���ص��ļ�ͷ��Ϣ,Ҫ�����û�����24�ֽڳ����ڴ�
*       Return: �ɹ�VOS_OK,��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-04-10   wuhailan103194          Create
*
*******************************************************************************/
extern ULONG TCPIP_Pcap_GetFileHead(CHAR szFileHead[PCAP_FILEHEAD_LEN], ULONG ulLinkType);

#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif /* __TCPIP_PCAP_API_H__ */


