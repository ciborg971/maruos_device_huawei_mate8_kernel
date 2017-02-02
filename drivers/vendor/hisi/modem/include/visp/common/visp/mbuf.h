/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              mbuf.h
*
*  Project Code: VISPV100R005
*   Module Name: Mbuf
*  Date Created: 2000-3-25
*        Author: zhang hong yan(19316)
*   Description: ���ļ�����Mbuf��صĺ�����ݽṹ
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  -----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)  Creat the first version.
*  2006-4-27  wang xin(03278)        ���ݱ�̹淶�����ļ����й淶������
*  2006-05-10  lu yao(60000758)     Ϊ֧��ARM CPU�ֽڶ������ԣ��޸Ľṹ��
*  2006-07-06 xiehuaguo             �޸�MBUF State�ֶθ�ֵ�Ŀ����жϱ��� A82d03169
*******************************************************************************/

#ifndef _MBUF_H_
#define _MBUF_H_

#ifdef    __cplusplus
extern "C"{
#endif

/*
Remark:*/
#define MBUF_GET_TAG_MPLS_PTR(pstMBufM)   (& ( (pstMBufM)->stUserTagData.stMplsPacketInfo))

/******************************************************************************

                              user tag data

******************************************************************************/
typedef struct tagMBufCommonInfo
{
    ULONG ulReceiveIfnetIndex;/*ethernet, ����ӿڵ�ifnet������0��ʾ���������İ�*/
    ULONG ulSendIfnetIndex;/*ethernet*/

    /* V100R006 Lijing 52889 Add for Trunk */
    ULONG ulPhyInputIfIndex;    /* Trunk�µĳ�Ա�˿��յ�ARP����󽫶˿ڵĽӿ�������¼������
                                   ��֤ARP��Ӧ�ı��Ĵ�ͬһ����Ա�˿ڷ��� */

    ULONG ulSendAtIndex;
    ULONG ulQueueID;        /* ��ǰ��֧��MP������󣬿��Խ�QueID�ŵ�MBUF_S�� */
    /*ULONG ulPacketLength;*//*�����ֵ�ܵ���mbuf�����ݵĳ��ȣ������ȥ������*/
    ULONG ulFlag;/*��־����λ�ĺ����ɺ�MBUF_FLAG_XXXXXXXXXXXXXX����*/

    ULONG ulPortIfIndex;   /*L2IFģ����˿ڽӿ�����*/
}MBUF_COMMON_INFO_S;

typedef struct tagMBufX25Info
{
    /*added by songyizhen for X25ENH,2002-12-19,VRPV3R001M07*/
    USHORT  usX25OutLCI;    /*���ӿ����·��*/
    UCHAR  ucX25InLCDIsXOT;    /*��ӿ����·�����Ƿ�ΪXOT*/
    UCHAR  ucX25OutLCDIsXOT;    /*���ӿ����·�����Ƿ�ΪXOT*/
    LONG  lX25OutSocketID;    /*����ΪXOTʱ����LCD��SocketID*/
    USHORT  usPktTyp;        /*X25���������*/
    UCHAR   ucPadding[2];
    /*addition end for X25ENH*/

}MBUF_X25_INFO_S;

typedef struct tagMBufEthernetInfo
{
    UCHAR ucSourceMacAddress[8];/*ethernet*//*the excessive 2 bytes is only for byte alignment*/
    UCHAR ucDstMacAddress[8];
}MBUF_ETHERNET_INFO_S;

typedef struct tagMBufFrameRelayInfo
{
    ULONG ulFrInfo;

}MBUF_FRAME_RELAY_INFO_S;

typedef struct tagMBufATMInfo
{
    ULONG ulATMInfo;
    ULONG ulPhyInfo;
    ULONG ulVccIndex;
}MBUF_ATM_INFO_S;

typedef struct tagMBufPPPInfo
{
    USHORT usProtocol; /*���ĵ�PppЭ���*/
    USHORT usReserved;
}MBUF_PPP_INFO_S;

typedef struct tagMBufIpPacketInfo
{
    /*IP����Ϣ,��IP���ĸ������л��*/
    UCHAR ucServiceType;/*the type of service domain in ip head, ���а���precedence*/
    UCHAR ucIsFragment;/*is fragment or not */
    UCHAR ucProtocolId;/*the protocol in ip head, TCP UDP ICMP*/
    UCHAR ucReserve;/*for byte alignment*/
    ULONG ulSourceIpAddress;
    ULONG ulDestinationIpAddress;
    /*IP����Э�����Ϣ�������IP����Ƭ�Σ������������������壬�������Ƭ�Σ������ǵĺ�����ע������˵��*/
    USHORT usSourcePortOrIcmpType;/*��TCP��UDP���ģ���Դ�˿ںţ���ICMP������type*/
    USHORT usDestinationPortOrIcmpCode;/*��TCP��UDP���ģ���Ŀ�Ķ˿ںţ���ICMP������code*/

    ULONG ulLoopTimes;        /* ��IP�����ڱ����ڲ�ѭ������Ĵ���, IP*/
    ULONG ulIpPktType;        /* �ñ����Ƿ��ǹ㲥���ģ���IP_forward��IP_Distrubute��ʹ�� */
    ULONG ulNextHopIpAddress;/*��һ���ĵ�ַ����·�ɱ��л��*//*ethernet*/
    ULONG ulRevBoardId;        /* ����ת����ʹ��,���ת���Զ˰�� */
    ULONG ulLenExpIcmpOption;   /*  ����ICMPѡ���  */
}MBUF_IP_PACKET_INFO_S;

#define MBUF_MACADDRLEN 6

typedef struct tagMBufIp6PacketInfo
{
    ULONG ulLoopTimes;      /* ��IP�����ڱ����ڲ�ѭ������Ĵ���*/
    ULONG ulIpPktType;      /* �������� */

    /*
    ��һ���ĽṹӦ����IN6ADDR_S,������Ϊͷ�ļ����õĹ�ϵ,
    ����󽫵���ԭ�е��ļ��޷�����ͨ��,ֻ�ܶ���һ����ͬ�Ľṹ����
    */
    struct {
        UCHAR ucaddr[16];
    }stNextHopIpAddr;       /*��һ���ĵ�ַ����·�ɱ��л��*/

    /* ��·���ַ */
    union
    {
        UCHAR szLinkEtherAddr[MBUF_MACADDRLEN]; /* physical��ַ */
    }unLinkAddr;

    UCHAR ucServiceType;/* used by qos, be similar to the ipv4,IPv6����ͨ��������TrafficClass */
    /*Added by wangchengyang-xujun62830-57575 for VISPV1R8C01-203, 2009/5/12 */
    /* UCHAR ucReserve; for future use and byte alignment */
    UCHAR ucHopLimit   ;/* ipv6 hoplimit��Ϣ,BFD֧��IPv6��ʱ����Ҫ���� */
    /* End of Added by wangchengyang-xujun62830-57575, 2009/5/12 */

    UCHAR ucProtocolID;     /* IPv6����Я�����ϲ�Э���, ��IANAͳһ����: TCP: 6, UDP: 17, ICMP6: 58 */
    UCHAR ucReserve[3];     /* Ԥ��δʹ���ֶ� */
}MBUF_IP6_PACKET_INFO_S;

typedef struct tagMBufMplsPacketInfo
{
    ULONG ulL3Info; /* record info about network layer */

    ULONG    ulVrfIndex;
}MBUF_MPLS_PACKET_INFO_S;

typedef struct tagMBufIpxPacketInfo
{
    ULONG ulTemp;
}MBUF_IPX_PACKET_INFO_S;

typedef struct tagMBUF_UserTagData/*this data type is public, can be used by user*/
{
    /*���е���Ϣ*/
    MBUF_COMMON_INFO_S stCommonInfo;

    /*���������ص���Ϣ��������̫���ķ����ߵ�physical��ַ��X.25����·�ŵ�*/
    ULONG ulPhysicalType;
    union
    {
        ULONG ulTemp;   /* ���ֶ������ڴ��VLANͷ��Ϣ */
    }unPacketInfoRelevantToPhysical;

    /*����·����ص���Ϣ*/
    ULONG ulLinkType;/*X.25, ethernet*/
    union
    {
        MBUF_X25_INFO_S stX25Info;
        MBUF_ETHERNET_INFO_S stEthernetInfo;
        MBUF_FRAME_RELAY_INFO_S stFrameRelayInfo;
        MBUF_ATM_INFO_S stATMInfo;
        MBUF_PPP_INFO_S stPppInfo;
    }unPacketInfoRelevantToLink;

    MBUF_MPLS_PACKET_INFO_S stMplsPacketInfo;

    /*����������Ϣ*/
    ULONG ulNetworkType;/*IP, IPX��ARP,����*//*ethernet*/
    union
    {
        MBUF_IP_PACKET_INFO_S stIpPacketInfo;
        MBUF_IPX_PACKET_INFO_S stIpxPacketInfo;

        MBUF_IP6_PACKET_INFO_S stIp6PacketInfo;
    }unPacketInfoRelevantToNetwork;
    /*module macro removed by Desh*/
    ULONG ulNatPtFlag; /*  to hold ipv6 natpt info */

    /*�������ص���Ϣ*/
    ULONG   ulAntiMultiFlag;

    UCHAR   aucSockAddr[36]; /*��ַ��Ϣ����󳤶Ȳ��ᳬ��36�ֽ�*/
    
    USHORT usVID;
    USHORT usPingMode;
    
    UCHAR   ucDccFlowID;             /* DCC���������ID*/
    UCHAR   ucDccFlag;                /*DCC ���*/
    /* End*/

    UCHAR   ucUserSpecifyFlag;  /* �Ƿ��û�ָ������һ�����߳��ӿ���Ϣ */
    UCHAR   ucPad;
    ULONG   ulPrivateData[4];   /* ��Ʒ��ʹ�õ�˽�����ݣ�����������ʹ���߶��� */
}MBUF_USERTAGDATA_S;

/*************************************************************************




                            PRIVATE SECTION



IMPORTANT

You can NOT use any of the following items!!!
**************************************************************************/

/*private data type------------------------------------------------------*/

typedef struct tagMBUF_DataBlockDescriptor/**/
{
    ULONG  ulState;/*add by wht06310 for mbufcache debug,2006-05-10*/

    ULONG  ulType;
    ULONG  ulOption;

    ULONG  ulDataBlockSource;/*DB����Դ����ϸ���ͼ��º궨��*/
    UCHAR *pucSysBlockCtl;/*����DB��MBUF��ַ*/

    ULONG  ulDataLength;/*���ݿ������ݵĳ��ȣ�ȡֵ��Χ[0, ulDataBlockLength]*/
    UCHAR *pucData;/*���ݿ������ݵ���ʼ��ַ, [pucDataBlock, pucDataBlock + ulDataBlockLength]*/
    ULONG  ulDataBlockLength;/*���ݿ���ܳ���, 2048 �� 4096 */
    UCHAR *pucDataBlock;/*���ݿ����ʼ��ַ�� NULL��ʾ��Ч��������ʾ��Ч*/
    struct tagMBUF_DataBlockDescriptor * pstNextDataBlockDescriptor;/*��һ�����ݿ��������� NULL��ʾ��Ч��������ʾ��Ч*/
}MBUF_DATABLOCKDESCRIPTOR_S;/*���ݿ����������ݽṹ*/

#define FILENAME_LEN 16
typedef struct tagMBuf
{
    ULONG ulState;/*add by wht06310 for mbufcache debug,2006-05-10*/

    struct tagMBuf * pstNextMBuf;/*��һ��mbuf�� NULL��ʾ��Ч��������ʾ��Ч*/
    ULONG ulTotalDataLength;/*mbuf�����ݵ��ܳ��ȣ���ֵΪ���ݿ�����������������������ulDataLength�ĺ�*/
    ULONG ulDataBlockNumber;/*mbuf�����ݿ�ĸ�������ֵΪ���ݿ����������������������ĸ���
                            �������ݿ�ĸ��������ݿ�ĸ����ܵ������ݿ��������ĸ�����*/

    /*
    other info about this packet such as QoS's PACKETINFO_S,
    fast switching info, etc.
    */
    MBUF_USERTAGDATA_S stUserTagData;

    /*����Ҫ��MBUF�������Ϣ����������*/
    ULONG ulHeadLenth;/*�����ײ�����*/
    ULONG ulEntry;/* Head Cache���ĵ�ַ*/
    MBUF_DATABLOCKDESCRIPTOR_S stDataBlockDescriptor;/*��һ�����ݿ��������������ݿ�����������ĵ�һ�����*/

    /* �������Ż���� */
    USHORT usPktType;
    USHORT usSocketID;

    CHAR  cFileName[FILENAME_LEN]; /*��¼��ǰ���ú������ļ���*/
    ULONG ulFileLine;              /*��¼��ǰ���ú������к�*/
    ULONG ulTaskID;                /*��¼��ǰ��������ID*/
    ULONG ulModID;                 /*ģ��ID*/

    ULONG ulEncapType;             /*Eth���ķ�װ����: Ŀǰֻ��Eth2/SNAP��ʽ */    
    USHORT usIpv6SourcePort;        /*��TCP��UDP���ģ���Դ�˿ںţ���ICMP6������type*/
    USHORT usIpv6DestinationPort;   /*��TCP��UDP���ģ���Ŀ�Ķ˿ںţ���ICMP6������code*/
    ULONG ulIpVersion;             /*ip version*/
    /*Added by zhoushisong202096, ����TCP�������, 2013/11/5 */ 
    struct tagMBuf * pstPrevMBuf;/*��һ��mbuf�� NULL��ʾ��Ч��������ʾ��Ч*/        
    UCHAR *pu8NetLayerHeader;    /* ָ���ĵ�������ײ� */
    /* End of Added by zhoushisong202096, 2013/11/5 */    
    ULONG ulReserved[4];           /*����Ϊ�Ժ�ʹ��*/
}MBUF_S;/*mbuf��ͷ��ǩ���ݽṹ*/

/*����L2IFģ��ı�����˿ڽӿ�����*/
#define MBUF_SET_PORTIFINDEX(pstMBufM, PortIfIndex)\
{\
    (pstMBufM)->stUserTagData.stCommonInfo.ulPortIfIndex = PortIfIndex;\
}

/*��ȡL2IFģ��ı�����˿ڽӿ�����*/
#define MBUF_GET_PORTIFINDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulPortIfIndex )

#define MBUF_ASSIGN_VLANID(pstMBuf,usVLANID) ((pstMBuf)->stUserTagData.usVID = (USHORT)(usVLANID))
#define MBUF_GET_VLANID(pstMBuf) ((pstMBuf)->stUserTagData.usVID)

#define ARP_LOG_GET_VLANHEAD(pstMBuf) pstMBuf->stUserTagData.unPacketInfoRelevantToPhysical.ulTemp
#define ARP_LOG_SET_VLANHEAD(pstMBuf,ulVlanHead) \
{\
    pstMBuf->stUserTagData.unPacketInfoRelevantToPhysical.ulTemp = ulVlanHead;\
}
/* End of addition */

/*private data type------------------------------------------------------END*/

/*private function----------------------------------------------------------*/

MBUF_DATABLOCKDESCRIPTOR_S * MBUF_CreateDBDescriptorAndDB(ULONG ulDataBlockLength, ULONG ulType, ULONG ulModuleID);
ULONG MBUF_PullUp(MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID);
ULONG MBUF_PrependDataBlock(MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID);
VOID MBUF_CutHeadInMultiDataBlock(MBUF_S * pstMBuf, ULONG ulLength);

extern VOID MBUF_DestroyFunc(CHAR *szCurrentFileName, ULONG ulLine, MBUF_S *pMBuf);
extern ULONG TCPIP_GetUserDBRef(VOID * pBuf, ULONG * pulRetRef );

/*private function----------------------------------------------------------END*/

/*************************************************************************


                                 PUBLIC SECTION



You can use the following items as the programmer manual described
**************************************************************************/

#define MBUF_TYPE_DATA     1

/* Prabhu Add Begin */
#define MBUF_FAIL ((ULONG) 1)/*�ӿڲ���ʧ��*/
#define MBUF_OK   ((ULONG) 0)/*�ӿڲ����ɹ�*/
#define MBUF_INPUT_NULL        ((ULONG) 2)/*mbuf�ӿ����Ϊ��*/
#define MBUF_DB_LENGTH_ERROR   ((ULONG) 3)/*mbuf�ӿ����DB���ȴ���*/
#define MBUF_INPUT_HOOK_NULL   ((ULONG) 4)/*mbuf�ӿ����DB���ȴ���*/




/*add by wht06310 for mbufcache debug,2006-05-10*/
/* add magic number for mbuf */
#define MBUF_IDLE          0x49444C45  /* ASCII of "IDLE"*/
#define MBUF_BUSY          0x42555359  /* ASCII of "BUSY"*/

#define MBUF_TYPE_SOOPTS   5

#define MBUF_DATA_BLOCK2048_SIZE 2048

#define MBUF_DATA_NORMAL 0/*DB�Ǵ�Э��ջ�����*/
#define MBUF_DATA_USERMNG 3/*DB���û������*/

#define MBUF_AMFLAG_DECAPSULATED    0x00000400  /*for ipsec inbound packet*/

#define MBUF_GET_PTR_NEXT_MBUF(pstMBufM) ( (pstMBufM)->pstNextMBuf )

#define MBUF_GET_FLAG(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulFlag )

/* �õ�MBUF��IPv6���ƽṹָ�� */
#define MBUF_GET_TAG_NETWORK_IP6_PTR(pstMBufM) (& ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo ))

#define MBUF_ASSIGN_SEND_IFNET_INDEX(pstMBufM, ulSendIfnetIndexM) \
    ((pstMBufM)->stUserTagData.stCommonInfo.ulSendIfnetIndex = (ulSendIfnetIndexM))

#define MBUF_ASSIGN_SEND_AT_INDEX(pstMBufM, ulSendAtIndexM) \
        ((pstMBufM)->stUserTagData.stCommonInfo.ulSendAtIndex = (ulSendAtIndexM))

#define MBUF_ASSIGN_RECEIVE_IFNET_INDEX(pstMBufM, ulReceiveIfnetIndexM) \
{\
    if ((pstMBufM)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex != (ulReceiveIfnetIndexM))\
    {\
        MBUF_CLEAR_AMFLAG(pstMBufM, MBUF_AMFLAG_DECAPSULATED);\
    }\
    (pstMBufM)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex = (ulReceiveIfnetIndexM);\
}

#define MBUF_GET_AMFLAG(pstMBufM) ( (pstMBufM)->stUserTagData.ulAntiMultiFlag )
#define MBUF_SET_AMFLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.ulAntiMultiFlag |= (ulFlagM))
#define MBUF_CLEAR_AMFLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.ulAntiMultiFlag &= ( ~(ulFlagM) ))

#define MBUF_GET_TAG_MPLS_VPNID(psMBufM, ulXId)\
{\
        ulXId = (psMBufM)->stUserTagData.stMplsPacketInfo.ulVrfIndex; \
}

#define MBUF_SET_TAG_MPLS_VPNID(psMBufM, ulXId)\
{\
        (psMBufM)->stUserTagData.stMplsPacketInfo.ulVrfIndex = ulXId; \
}

extern VOID MBUF_LOG_Info (ULONG ulCaseType, MBUF_S *pstMbuf,
                           CHAR *cCurrentFileName, ULONG ulCurrentFileLine, ULONG ulCurrentTaskId);
extern VOID TCPIP_GetFileName(CHAR *pstFile, CHAR *pstFileName, ULONG ulstrMaxLen);
extern ULONG MBUF_FreeMbuf(MBUF_S *pstMBuf);

MBUF_S * MBUF_ReferenceCopy(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, ULONG ulModuleID);
/* Prabhu Add End */

/*�˺�����Mbuf��ͷ*/
#define MBUF_CUT_HEAD(pstMBufM, ulLengthM)\
{\
    if( (pstMBufM) != NULL )\
    {\
        if( (pstMBufM)->stDataBlockDescriptor.ulDataLength >= (ulLengthM) )\
        {\
            (pstMBufM)->stDataBlockDescriptor.pucData += (ulLengthM);\
            (pstMBufM)->stDataBlockDescriptor.ulDataLength -= (ulLengthM);\
            (pstMBufM)->ulTotalDataLength -= (ulLengthM);\
        }\
        else\
        {\
            MBUF_CutHeadInMultiDataBlock( (pstMBufM), (ulLengthM) );\
        }\
    }\
}

/*�˺�����ʹMbufָ��������������*/
#define MBUF_MAKE_MEMORY_CONTINUOUS(pstMBufM, ulLengthM, ulModuleIDM, ulResultM) \
{\
    if( (pstMBufM) != NULL )\
    {\
        if( (pstMBufM)->stDataBlockDescriptor.ulDataLength < (ulLengthM) )\
        {\
            (ulResultM) = MBUF_PullUp( (pstMBufM), (ulLengthM), (ulModuleIDM) );\
        }\
        else\
        {\
            (ulResultM) = MBUF_OK;\
        }\
    }\
    else\
    {\
        (ulResultM) = MBUF_FAIL;\
    }\
}

/*�˺�����ʹMbuf��ǰ��չһ������*/
/*the ulLengthM must <= 2048*/
#define MBUF_PREPEND_MEMORY_SPACE(pstMBufM, ulLengthM, ulModuleIDM, ulResultM)\
{\
     ULONG ulReferenceCount=0; /*CodeCC Error: 25376  Fix */\
     MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor;\
     \
     if( (pstMBufM) != NULL)    \
     {\
        pstDataBlockDescriptor = &( (pstMBufM)->stDataBlockDescriptor );\
        if (MBUF_DATA_USERMNG == pstDataBlockDescriptor->ulDataBlockSource)\
        {\
            if(TCPIP_GetUserDBRef(pstDataBlockDescriptor->pucDataBlock, &ulReferenceCount) != 0)\
            {\
                ulReferenceCount = 2;\
            }\
        }\
        else if (pstDataBlockDescriptor->ulDataBlockSource == MBUF_DATA_NORMAL)\
        {\
            if (VOS_Mem_GetRef(pstDataBlockDescriptor->pucDataBlock, &ulReferenceCount) != 0)\
            {\
               ulReferenceCount = 2;\
            }\
        }\
        else\
        {\
            if (TCPIP_GetSysDBRefCnt(pstDataBlockDescriptor, &ulReferenceCount) != 0)\
            {\
                ulReferenceCount = 2;\
            }\
        }\
        if(ulReferenceCount == 1 \
            && (ULONG) (pstDataBlockDescriptor->pucData - pstDataBlockDescriptor->pucDataBlock) >= (ulLengthM) )\
        {\
            pstDataBlockDescriptor->pucData -= (ulLengthM);\
            pstDataBlockDescriptor->ulDataLength += (ulLengthM);\
            (pstMBufM)->ulTotalDataLength += (ulLengthM);\
            (ulResultM) = MBUF_OK;\
        }\
        else\
        {\
            (ulResultM) = MBUF_PrependDataBlock( (pstMBufM), (ulLengthM), (ulModuleIDM) );\
        }\
    }\
    else\
    {\
        (ulResultM) = MBUF_FAIL;\
    }\
}


#define MBUF_GET_DATA_BLOCK_DESC(pstMBufM) ( & ( (pstMBufM)->stDataBlockDescriptor) )
#define MBUF_MTOD(pstMBufM, DataTypeM) ( (DataTypeM)  (pstMBufM)->stDataBlockDescriptor.pucData )


#define MBUF_GET_TOTAL_DATA_LENGTH(pstMBufM) ( (pstMBufM)->ulTotalDataLength )

/*
����ĺ������ͷ�һ��MBUF��,
ĿǰMBUF��û����Ӧ�ĺ�,MBUF_Destroyֻ�ͷ�һ��MBUF,�Ժ�Ӧ�������ӵ�MBUFģ����
*/
#define FREE_MBUF_CHAIN(pstMBuf) \
{ \
    MBUF_S *pTmpMBuf = pstMBuf; \
    \
    while (NULL != pTmpMBuf) \
    { \
        pstMBuf = MBUF_GET_PTR_NEXT_MBUF(pTmpMBuf); \
        MBUF_Destroy(pTmpMBuf); \
        pTmpMBuf = pstMBuf; \
    } \
}

/*public macro----------------------------------------------------------END*/

/*public function---------------------------------------------------------------------*/
/*******************************************************************************
*    Func Name: TCPIP_Safe_Mem_Set
* Date Created: 2014-12-13
*       Author: likaikun213099
*  Description: mem_set��ȫ/�ǰ�ȫ����ʵ��(Balong�������˷ǰ�ȫ��֧)
*        Input: VOID *pDest:
*               ULONG ulDstMaxLen:
*               CHAR uChar:
*               ULONG ulCount:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-12-13   likaikun213099          Create
*
*******************************************************************************/
extern ULONG TCPIP_Safe_Mem_Set(VOID *pDest, ULONG ulDstMaxLen, CHAR uChar, ULONG ulCount);

MBUF_S * MBUF_CreateByCopyBuffer(ULONG ulReserveHeadSpace, ULONG ulLength, UCHAR * pucBuffer, ULONG ulType, ULONG ulModuleID);
MBUF_S * MBUF_CreateForControlPacket(ULONG ulReserveHeadSpace, ULONG ulLength, ULONG ulType, ULONG ulModuleID);

ULONG MBUF_CopyDataFromBufferToMBuf(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, UCHAR * pucBuffer, ULONG ulModuleID);
ULONG MBUF_CopyDataFromMBufToBuffer(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, UCHAR * pucBuffer);
MBUF_S * MBUF_RawCopy(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, ULONG ulReserveHeadSpace, ULONG ulModuleID);

ULONG MBUF_Concatenate(MBUF_S * pstDestinationMBuf, MBUF_S * pstSourceMBuf, ULONG ulModuleID);/*when ok, pstSourceMBuf is NOT valid any more*/
ULONG MBUF_NeatConcatenate_Chain(MBUF_S *pstMbufHead, ULONG ulModuleID);
ULONG MBUF_CutPart(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength);
ULONG MBUF_CutTail(MBUF_S * pstMBuf, ULONG ulLength);

UCHAR * MBUF_AppendMemorySpace(MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID);

/*public function---------------------------------------------------------------------END*/

/***************************************************************************

                        user tag data macro

***************************************************************************/
#define MBUF_FLAG_MULTICAST    0x00000002

#define MBUF_FLAG_CONF            0x00000010    /*for ipsec, packet has been encrypted*/
#define MBUF_FLAG_AUTH            0x00000020    /*for ipsec, packet has been authenticated*/
#define MBUF_FLAG_TUNNEL          0x00000040    /*for ipsec, packet has been added tunnel IP head*/
#define MBUF_FLAG_ENCAPSULATED    0x00000800  /*for ipsec outbound packet*/


#define MBUF_GET_RECEIVE_IFNET_INDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex )

#define MBUF_GET_SEND_IFNET_INDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulSendIfnetIndex )

#define MBUF_GET_SEND_AT_INDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulSendAtIndex )

#define MBUF_SET_FLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.stCommonInfo.ulFlag |= (ulFlagM))
#define MBUF_CLEAR_FLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.stCommonInfo.ulFlag &= ( ~(ulFlagM) ))

#define MBUF_ASSIGN_QUEUE_ID(pstMBufM, ulQueIDM) \
    ((pstMBufM)->stUserTagData.stCommonInfo.ulQueueID = (ulQueIDM))


#define MBUF_PING_COMMON                   0x00 
#define MBUF_PING_OUTIF_SPECIFY            0x01 
#define MBUF_PING_OUTIF_NEXTHOP            0x02 

#define MBUF_ASSIGN_PING_MODE(pstMBufM, usPingMode) \
    ((pstMBufM)->stUserTagData.usPingMode = (usPingMode))

#define MBUF_GET_PING_MODE(pstMBufM) ((pstMBufM)->stUserTagData.usPingMode)

#define MBUF_GET_SRC_PORT_IP6(pstMBufM)   ( (pstMBufM)->usIpv6SourcePort )
#define MBUF_SET_SRC_PORT_IP6(pstMBufM, ulType)\
    ( (pstMBufM)->usIpv6SourcePort = (ulType) )

#define MBUF_GET_DST_PORT_IP6(pstMBufM)   ( (pstMBufM)->usIpv6DestinationPort )
#define MBUF_SET_DST_PORT_IP6(pstMBufM, ulCode)\
    ( (pstMBufM)->usIpv6DestinationPort = (ulCode) )
    
#define MBUF_IP4_VERSION                   0x04 
#define MBUF_IP6_VERSION                   0x06 
#define MBUF_GET_IP_VER(pstMBufM)   ( (pstMBufM)->ulIpVersion )
#define MBUF_SET_IP_VER(pstMBufM, ulVersion)\
    ( (pstMBufM)->ulIpVersion = (ulVersion) )

#define MBUF_SPECIFY_OUTIF_FLAG          0x01
#define MBUF_SPECIFY_NEXTHOP_FLAG        0x02

/* ��ȡMBUFָ����һ������ӿڱ����Ϣ */
#define MBUF_GET_SPECIFY_FLAG(pstMBufM) ((pstMBufM)->stUserTagData.ucUserSpecifyFlag)

/* ����MBUFָ����һ������ӿڱ����Ϣ */
#define MBUF_ASSIGN_SPECIFY_FLAG(pstMBufM,ucSpecifyFlagM)\
(((pstMBufM)->stUserTagData.ucUserSpecifyFlag) = (ucSpecifyFlagM))

/* MBUF �������ݵĵ�ַ */
#define MBUF_GET_PRIVATE_DATA_PTR(pstMBufM) (&(pstMBufM)->stUserTagData.ulPrivateData[0])

/* ���ñ�������һ��physical��ַ */
#define MBUF_ASSIGN_IPV6_NEXTHOPMACADDR(pstMBufM, szMac) \
((VOID)TCPIP_Mem_Copy((UCHAR *)((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.unLinkAddr.szLinkEtherAddr),MBUF_MACADDRLEN, \
(UCHAR *)szMac, MBUF_MACADDRLEN))

/* �����������Ǵ�ppmng_pub.h�Ƶ�mbuf.h�е� */
#define MBUF_IP6ADDRLEN 16

/* �õ���������һ��IPv6��ַ��ָ�� */
#define MBUF_GET_IPV6_NEXTHOPADDR(pstMBufM) \
    (&((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.stNextHopIpAddr))

/* ���ñ�������һ��IPv6��ַ */
#define MBUF_ASSIGN_IPV6_NEXTHOPADDR(pstMBufM, addr) \
    ((VOID)TCPIP_Mem_Copy((VOID *)&((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.stNextHopIpAddr),MBUF_IP6ADDRLEN, \
    (VOID *)&addr, MBUF_IP6ADDRLEN))

/* ��ȡMBUF�е�IPV6����Э��� */
#define MBUF_GET_IPV6_PROTOCOL_ID(pstMBufM) \
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.ucProtocolID)

/* ����MBUF�е�IPV6����Э��� */
#define MBUF_SET_IPV6_PROTOCOL_ID(pstMBufM, ucProtocolIDM) \
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.ucProtocolID = (ucProtocolIDM))

/* ��ȡMBUF�е�IPV6����ͨ������� */
#define MBUF_GET_IPV6_TRAFFIC_CLASS(pstMBufM) \
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.ucServiceType)

/* ����MBUF�е�IPV6����ͨ������� */
#define MBUF_SET_IPV6_TRAFFIC_CLASS(pstMBufM, ucServiceTypeM) \
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.ucServiceType = (ucServiceTypeM))

/* ��ȡVLANͷ��Ϣ(����VLAN���ͺ�ֵ),������ */
#define MBUF_GET_VLAN_HEAD_VALUE(pstMBufM) \
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToPhysical.ulTemp)

/* ����VLANͷ��Ϣ(����VLAN���ͺ�ֵ),������ */
#define MBUF_SET_VLAN_HEAD_VALUE(pstMBufM, ulVlanHeadM) \
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToPhysical.ulTemp = (ulVlanHeadM))


#define MBUF_Destroy(pMBuf) \
{ \
    ULONG ulLine = __LINE__;\
    CHAR  szCurrentFileName[FILENAME_LEN];\
    MBUF_S *pst_MBuf = pMBuf;\
    \
    TCPIP_GetFileName((CHAR*)__FILE__, szCurrentFileName, FILENAME_LEN);\
    \
    MBUF_DestroyFunc(szCurrentFileName, ulLine, pst_MBuf);\
}

/* IR add in 2007/04/12. */
#define MBUF_TR_ICMP6_DELIVEREDTOUP             0x0000001D

#define MBUF_AMFLAG_IPSEC6_ENCAPSULATED_IPV6    0x00000200

/* Added by sumangala*/
#ifdef TCPIP_SUPPORT_ARMCPU
/*��Mbuf���Ľ����ϲ�Э��ʱ����ô˺ꡣ�˺���������жϱ��ĵ���ʼ��ַ�Ƿ�4�ֽڵ���������
������ǣ�����Ҫ������һ��DB����ԭ������Mbuf����Copy���µ�DB��*/
#define MBUF_ADJUST_DB(pMBuf)\
{\
    ULONG ulReserveLen = 0;\
    UCHAR *pucData = NULL;\
    UCHAR *pucDataBlock = NULL;\
    UCHAR *pucNewDataBlock = NULL;\
    if (((pMBuf) != NULL) && ((pMBuf)->stDataBlockDescriptor.pucDataBlock != NULL))\
    {\
        pucData = MBUF_MTOD((pMBuf), UCHAR *);\
        if (((ULONG)pucData & 0x00000003) != 0)\
        {\
            pucDataBlock = (pMBuf)->stDataBlockDescriptor.pucDataBlock;\
            ulReserveLen = (ULONG)(pucData - pucDataBlock); \
            MBUF_ALLOC_DB(pucNewDataBlock, (pMBuf)->stDataBlockDescriptor.ulDataBlockSource);\
            if (pucNewDataBlock != NULL)\
            {\
                ulReserveLen -= (ulReserveLen & 0x00000003);\
                (VOID)TCPIP_Mem_Copy(pucNewDataBlock + ulReserveLen, (pMBuf)->stDataBlockDescriptor.ulDataLength,pucData, (pMBuf)->stDataBlockDescriptor.ulDataLength);\
                MBUF_FREE_DB(&((pMBuf)->stDataBlockDescriptor));\
                (pMBuf)->stDataBlockDescriptor.pucDataBlock = pucNewDataBlock;\
                (pMBuf)->stDataBlockDescriptor.pucData = pucNewDataBlock + ulReserveLen;\
                (pMBuf)->stDataBlockDescriptor.ulDataBlockSource = MBUF_DATA_NORMAL;\
                (pMBuf)->stDataBlockDescriptor.pucSysBlockCtl = NULL;\
                (pMBuf)->stDataBlockDescriptor.ulDataBlockLength = g_usMBufDataBlockLength;\
            }\
         }\
     }\
}
#else /*�������ARM CPU����˺겻��Ҫ���κβ���*/
#define MBUF_ADJUST_DB(pMBuf)
#endif

/* ��ȡ��̫֡��װ����(Eth2/SNAP) */
#define MBUF_GET_ETHERNET_ENCAP_TYPE(pstMBufM)\
    ((pstMBufM)->ulEncapType)

/* ������̫֡��װ����(Eth2/SNAP) */    
#define MBUF_SET_ETHERNET_ENCAP_TYPE(pstMBufM,ulFlagM)\
    (((pstMBufM)->ulEncapType ) = (ulFlagM))


#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _MBUF_H_ */

