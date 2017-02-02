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
    
    UCHAR   ucDccFlowID;             /* DCC���������ID */
    UCHAR   ucDccFlag;               /* DCC ��� */
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

    ULONG ulEncapType;             /* Eth���ķ�װ����: Ŀǰֻ��Eth2/SNAP��ʽ */  

    USHORT usIpv6SourcePort;        /*��TCP��UDP���ģ���Դ�˿ںţ���ICMP6������type*/
    USHORT usIpv6DestinationPort;   /*��TCP��UDP���ģ���Ŀ�Ķ˿ںţ���ICMP6������code*/
    ULONG ulIpVersion;             /*ip version*/
    ULONG ulTimeStampHigh;         /* ���ֽ�ʱ��� */
    ULONG ulTimeStampLow;         /* ���ֽ�ʱ��� */
    
    /*Added by zhoushisong202096, ����TCP�������, 2013/11/5 */ 
    struct tagMBuf * pstPrevMBuf;/*��һ��mbuf�� NULL��ʾ��Ч��������ʾ��Ч*/        
    UCHAR *pu8NetLayerHeader;    /* ָ���ĵ�������ײ� */
    /* End of Added by zhoushisong202096, 2013/11/5 */
    
    ULONG ulReserved[2];           /*����Ϊ�Ժ�ʹ��*/

    
}MBUF_S;/*mbuf��ͷ��ǩ���ݽṹ*/
    

/*����Mbuf��ص�Ԥ���ò���ֵ*/
typedef struct MbufCfgInfo
{
    ULONG ulHeadCacheNum;
    ULONG ulDBDCacheNum;
    ULONG ulDBCacheNum;
    ULONG ulHeadCacheMask;
    ULONG ulDBDCacheMask;
    ULONG ulDBCacheMask;
    ULONG ulCacheLock;
    /*Added by zhoushisong202096, ֧��MBUFԤ�����ȿ���չ, 2013/11/25 */
    ULONG ulReservedExtHeadLength;
    /* End of Added by zhoushisong202096, 2013/11/25 */
}MBUFCFGINFO_S;

/*��ȡMBUF��״̬*/
typedef struct tagMbufStatusInfo
{
    ULONG ulHeadCacheNum;      /*MBUF HeadԤ��������*/
    ULONG ulDBDCacheNum;       /*DBD����*/
    ULONG ulDBCacheNum;        /*DB����*/
    ULONG ulHeadCacheFreeNum;  /*δ��ʹ�õ�MBUF HEAD����*/
    ULONG ulDBDCacheFreeNum;   /*δ��ʹ��DBD����*/
    ULONG ulDBCacheFreeNum;    /*δ��ʹ��DB����*/
}MBUFSTATUSINFO_S;

/*STRUCT<ע���û�����DB�Ĺ��Ӻ���ԭ��>*/
typedef struct tagTCPIP_USER_DB_HOOK
{
    USHORT usMBufDataBlockLength;  /*�û������DB�鳤�ȷ�Χ��2048~65535*/
    USHORT usRes; 
    VOID* (*AllocUserDB_HOOK_FUNC)(USHORT usLen); /*�����û������DB����������ֵ��Ϊ�����DB�ڴ�ָ�� */
    ULONG (*FreeUserDB_HOOK_FUNC)(VOID * pBuf); /*�ͷ��û������DB */
    ULONG (*IncRefUserDB_HOOK_FUNC)(VOID * pBuf); /*���� DB�����ü������ο�VOS_Mem_IncRef */
    ULONG (*DecRefUserDB_HOOK_FUNC)(VOID * pBuf); /*���� DB�����ü������ο�VOS_Free�ж����ü����Ĵ��� */
    ULONG (*GetRefUserDB_HOOK_FUNC) (VOID * pBuf, ULONG * pulRetRef ); /*��ȡ DB�����ü������ο�VOS_Mem_GetRef */
}TCPIP_USER_DB_HOOK_S;

typedef ULONG (*FreeSysDB_HOOK_FUNC)(MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor);
typedef ULONG (*DupSysDB_HOOK_FUNC)(MBUF_DATABLOCKDESCRIPTOR_S * pstSrcDataBlockDescriptor,
                                    MBUF_DATABLOCKDESCRIPTOR_S * pstDstDataBlockDescriptor);
typedef ULONG (*GetSysDBRefCnt_HOOK_FUNC)(MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor,
                                          ULONG *pulCount);
typedef ULONG (*DecSysDBRefCnt_HOOK_FUNC)(MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor);


/*private data type------------------------------------------------------END*/


/*private macro----------------------------------------------------------*/
/*no parameters*/

#define MBUF_MBUF_SIZE ( sizeof(MBUF_S) )
#define MBUF_DATA_BLOCK_DESC_SIZE ( sizeof(MBUF_DATABLOCKDESCRIPTOR_S) )
#define MBUF_DATA_BLOCK2048_SIZE 2048
#define MBUF_DATA_BLOCK4096_SIZE 4096

#define MBUF_MAGIC_WORD                0x12345678

/*with parameters*/
#define MBUF_MIN(a,b) (((a) < (b)) ? (a) : (b))


/*private macro----------------------------------------------------------END*/


/*private function----------------------------------------------------------*/

/****************************************************************************
*    Func Name: MBUF_CreateDBDescriptorAndDB()
*  Description: to create a data block and a data block descriptor,
*               then link the data block to the data block descriptor.
*               The size of data block is as the ulDataBlockLength specified.
*        Input: ULONG ulDataBlockLength:���ݿ鳤��
*               ULONG ulType:���ݿ�����
*               ULONG ulModuleID:�����ߵ�ģ���
*       Output: ��
*       Return: NULL:ʧ��
*               ����ֵ:MBUF��DB Descriptorָ��
*      Caution: this function assiged 5 items
*               pucDataBlock
*               pstNextDataBlockDescriptor(NULL)
*               ulDataBlockLength
*               ulType
*               ulOption(0)
*               remain the following items
*               pucData
*               ulDataLength
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_DATABLOCKDESCRIPTOR_S * MBUF_CreateDBDescriptorAndDB(ULONG ulDataBlockLength, ULONG ulType, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_PullUp()
*  Description: create a data block and data block descriptor, 
*               then move the first ulLength data to the data block,
*               then insert the data block and data block descriptor 
*               into the head of data block list
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulLength:the first ulLength data that need be moved to the data block
*               ULONG ulModuleID:ģ���
*       Output: ��
*       Return: MBUF_OK:   �ɹ�
*               MBUF_FAIL: ʧ��
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_PullUp(MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_PrependDataBlock()
*  Description: create a data block and data block descriptor, 
*               then insert the data block and data block descriptor into the head of mbuf list
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulLength:����
*               ULONG ulModuleID:ģ���
*       Output: ��
*       Return: MBUF_OK:   �ɹ�
*               MBUF_FAIL: ʧ��
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_PrependDataBlock(MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_CutHeadInMultiDataBlock()
*  Description: cut the first ulLength data that may be in multiple data blocks of the pstMBuf
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulLength:����
*       Output: ��
*       Return: ��
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
VOID MBUF_CutHeadInMultiDataBlock(MBUF_S * pstMBuf, ULONG ulLength);


VOID MBUF_DestroyFunc(CHAR *szCurrentFileName, ULONG ulLine, MBUF_S *pMBuf);


ULONG TCPIP_GetUserDBRef(VOID * pBuf, ULONG * pulRetRef );

/*private function----------------------------------------------------------END*/








/*************************************************************************




                                 PUBLIC SECTION



You can use the following items as the programmer manual described
**************************************************************************/


/*public macro----------------------------------------------------------*/
/*macro without parameters*/

/*DB����Դ*/
#define MBUF_DATA_NORMAL 0/*DB�Ǵ�Э��ջ�����*/
#define MBUF_DATA_ETHDRV 1/*DB�Ǵ���̫���������*/
#define MBUF_DATA_PPPDRV 2/*DB�Ǵ�PPP���������*/
#define MBUF_DATA_USERMNG 3/*DB���û������*/

#define MBUF_HEAD_CACHE_NUM         4096            /* MBUF Head������� */
#define MBUF_HEAD_CACHE_MASK        (MBUF_HEAD_CACHE_NUM - 1)

#define MBUF_DBD_CACHE_NUM          4096            /* MBUF DBD�������  */
#define MBUF_DBD_CACHE_MASK         (MBUF_DBD_CACHE_NUM - 1)

#define MBUF_DB_CACHE_NUM           8192            /* MBUF DB�������   */
#define MBUF_DB_CACHE_MASK          (MBUF_DB_CACHE_NUM - 1)

#define MBUF_DEF_CACHE_NUM          128             /*Ĭ��MBUF CACHE����*/

#define MBUF_FAIL ((ULONG) 1)/*�ӿڲ���ʧ��*/
#define MBUF_OK   ((ULONG) 0)/*�ӿڲ����ɹ�*/
#define MBUF_INPUT_NULL        ((ULONG) 2)/*mbuf�ӿ����Ϊ��*/
#define MBUF_DB_LENGTH_ERROR   ((ULONG) 3)/*mbuf�ӿ����DB���ȴ���*/
#define MBUF_INPUT_HOOK_NULL   ((ULONG) 4)/*mbuf�ӿ����DB���ȴ���*/


#define MBUF_TYPE_DATA     1
#define MBUF_TYPE_CONTROL  2
#define MBUF_TYPE_NAME     3
#define MBUF_TYPE_OOBDATA  4
#define MBUF_TYPE_SOOPTS   5

#define MBUF_TYPE_MPLS     8
#define MBUF_TYPE_MPLS_SW  9
#define MBUF_TYPE_MPLS_VPN 10

/*add by wht06310 for mbufcache debug,2006-05-10*/
/* add magic number for mbuf */
#define MBUF_IDLE          0x49444C45  /* ASCII of "IDLE"*/
#define MBUF_BUSY          0x42555359  /* ASCII of "BUSY"*/

#define MBUF_MAX_MID         256    /*ģ���ڴ�ͳ������������ģ��ID��Ӧ����������*/

extern ULONG   gulMBufHeadCacheFreeNum;
extern ULONG   gulMBufHeadCacheFreeIndex;
extern ULONG   gulMBufHeadCacheAllocIndex;
extern ULONG   gulMbufHeadCacheFailedCount;
extern MBUF_S** gstMBufHeadCache;

extern ULONG   gulMBufDBDCacheFreeNum;
extern ULONG   gulMBufDBDCacheFreeIndex;
extern ULONG   gulMBufDBDCacheAllocIndex;
extern ULONG   gulMbufDBDCacheFailedCount;
extern MBUF_DATABLOCKDESCRIPTOR_S** gstMBufDBDCache;

extern ULONG   gulMBufDBCacheFreeNum;
extern ULONG   gulMBufDBCacheFreeIndex;
extern ULONG   gulMBufDBCacheAllocIndex;
extern ULONG   gulMbufDBCacheFailedCount;
extern UCHAR** gstMBufDBCache;

extern MBUFCFGINFO_S g_stMbufCfgInfo;

extern ULONG g_ulMbufStatByMID[MBUF_MAX_MID + 1];

/*Add for S-IP-002-MBUF.002 ֧�ֲ�Ʒ�����ڴ���ΪDB���ƿ�*/
extern TCPIP_USER_DB_HOOK_S *g_pfTCPIPUserDBMng;
extern USHORT g_usMBufDataBlockLength;

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

/*******************************************************************************
*    Func Name: TCPIP_FreeSysDB
*  Description: �ͷŴ����������DB
*        Input: MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor:Ҫ�ͷ�DB��DBD
*       Output: 
*       Return: VOS_ERR:ʧ��
*               VOS_OK:�ͷųɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2004-7-7     zhany hong yan(19316)   Create
*
*******************************************************************************/
extern ULONG TCPIP_FreeSysDB (MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor);
/*******************************************************************************
*    Func Name: MBUF_LOG_Info
*  Description: �ṩ��MBUFʹ�÷�װ��־��¼�꣬�Խ����Ʒ����mbuf.h�ļ�ʱ����־�ļ�������
*               ע��:��־һ�㲻�����װ,���˵�����,����Ҫ����־�ļ�¼Ҫ�ﵽ�������¼��
*        Input: ULONG ulCaseType:��־���¼��
*               MBUF_S *pstMbuf:MBUFָ��
*               CHAR *cCurrentFileName:��ǰ�ļ���
*               ULONG ulCurrentFileLine:��ǰ�ļ��к�
*               ULONG ulCurrentTaskId:��ǰ����ID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-04-25   wuhailan                Create
*
*******************************************************************************/
extern VOID MBUF_LOG_Info (ULONG ulCaseType, MBUF_S *pstMbuf,
                           CHAR *cCurrentFileName, ULONG ulCurrentFileLine, ULONG ulCurrentTaskId);
/*******************************************************************************
*    Func Name: TCPIP_GetFileName
*  Description: ��ȡ����·�����ļ���
*        Input: CHAR *pstFile:����Ĵ�·�����ļ���
*               ULONG ulstrMaxLen:��ŷ����ļ����Ŀռ��С,
*                                 �������ַ�������ֻռulstrMaxLen-1���ַ������һ���ַ���Ϊ\0��
*       Output: CHAR *pstFileName:���ز���·�����ļ���
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-12   wuhailan                Create
*
*******************************************************************************/
extern VOID TCPIP_GetFileName(CHAR *pstFile, CHAR *pstFileName, ULONG ulstrMaxLen);
/*******************************************************************************
*    Func Name: MBUF_FreeMbuf
*  Description: �ͷ�MBUF��Ϣ
*        Input: MBUF_S *pstMBuf:MBUFָ��
*       Output: 
*       Return: ����VOS_OK
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-05-17   wuhailan                Create
*
*******************************************************************************/
extern ULONG MBUF_FreeMbuf(MBUF_S *pstMBuf);

#if defined(TCPIP_DOPRA_V2) && defined(DOPRAV2)
extern VOID *VOS_Malloc( ULONG ulInfo, SIZE_T ulSize );
#else
extern VOID * VOS_Malloc( ULONG ulInfo, ULONG ulSize );
#endif

#ifndef PCLINT_FOR_VOS_MEM
#define PCLINT_FOR_VOS_MEM
#if defined(TCPIP_DOPRA_V2) && defined(DOPRAV2)
extern ULONG VOS_Mem_Copy(VOID * pDestPtr, const VOID * pSrcPtr, SIZE_T uvCopyLen);
extern ULONG VOS_Mem_Set( CHAR * pBufPtr, CHAR uChar, SIZE_T ulSetLen );
extern ULONG VOS_Mem_Zero( CHAR * pBufPtr, SIZE_T ulSetLen );
#else
extern ULONG VOS_Mem_Copy( VOID * pDestPtr,const VOID * pSrcPtr,ULONG ulCopyLen );
extern ULONG VOS_Mem_Set( CHAR * pBufPtr, CHAR uChar, ULONG ulSetLen );
extern ULONG VOS_Mem_Zero( CHAR * pBufPtr, ULONG ulSetLen );
#endif
#endif

extern ULONG VOS_Free( VOID *pBuf );
extern ULONG VOS_SplImp(LONG *plRetSpl);
extern ULONG VOS_SplX(LONG lSpl);

extern ULONG VOS_Mem_GetRef( VOID * pBuf, ULONG * pulRetRef );
extern ULONG VOS_T_GetSelfID( ULONG * pulTaskID );

extern VOID TCPIP_SchedPoint_Check_Delay(VOID);

/* macro with parameters */

#ifndef TCPIP_Mem_Set
#define TCPIP_Mem_Set(pDstPtr, uChar, ulSetLen)                 TCPIP_Safe_Mem_Set(pDstPtr, ulSetLen, uChar, ulSetLen)
#endif

#ifndef TCPIP_Mem_Copy
#define TCPIP_Mem_Copy(pDstPtr, dst_size, pSrcPtr, copy_size)   TCPIP_Safe_Mem_Copy(pDstPtr, dst_size, pSrcPtr, copy_size)
#endif

/*����Ԥ���÷�ʽ,�����ж��Ƿ���Ҫ��MBUF Cache���й������ݻ��Ᵽ��*/
#define MBUF_CACHE_LOCK(ulValue) \
{\
    if (g_stMbufCfgInfo.ulCacheLock != VRP_NO)\
    {\
        (VOID)VOS_SplImp(&(ulValue));\
    }\
}

#define MBUF_CACHE_UNLOCK(ulValue) \
{\
    if (g_stMbufCfgInfo.ulCacheLock != VRP_NO)\
    {\
        (VOID)VOS_SplX(ulValue);\
    }\
}

/*����Mbufͷ*/
#define MBUF_ALLOC_HEAD(pstMBufHead)\
{\
    LONG iFastMbufMask = 0;\
    /*gulMbufHeadAllocCount++;*/\
    MBUF_CACHE_LOCK(iFastMbufMask);\
    if ( gulMBufHeadCacheFreeNum > 0 )\
    {\
        (pstMBufHead) = gstMBufHeadCache[gulMBufHeadCacheAllocIndex]; \
        gstMBufHeadCache[gulMBufHeadCacheAllocIndex] = NULL; \
        gulMBufHeadCacheAllocIndex = (gulMBufHeadCacheAllocIndex + 1) & g_stMbufCfgInfo.ulHeadCacheMask;\
        gulMBufHeadCacheFreeNum--;\
        if(MBUF_IDLE != pstMBufHead->ulState)\
        {\
            MBUF_LOG_Info(6, 0, 0, 0, 0);\
            /*VOS_DBGASSERT(0);*/\
        }\
    }\
    else \
    {\
        (pstMBufHead)->ulState = MBUF_BUSY;\
        (pstMBufHead)->stDataBlockDescriptor.ulState = MBUF_BUSY;\
    }\
    MBUF_CACHE_UNLOCK(iFastMbufMask);\
}

/*�ͷ�Mbufͷ*/
#define MBUF_FREE_HEAD(pstMBufHead)\
{\
    LONG iFastMbufMask = 0;\
    /*add by wht06310 for mbufcache debug,2006-05-10*/\
    if (pstMBufHead->ulState != MBUF_BUSY)\
    {\
        MBUF_LOG_Info(0, 0, 0, 0, 0);\
        /*VOS_DBGASSERT(0);*/\
    }\
    MBUF_CACHE_LOCK(iFastMbufMask);\
    pstMBufHead->ulState = MBUF_IDLE;\
    pstMBufHead->stDataBlockDescriptor.ulState = MBUF_IDLE;\
    if (gulMBufHeadCacheFreeNum >= g_stMbufCfgInfo.ulHeadCacheNum)\
    {\
        (VOID)VOS_Free(pstMBufHead);\
    }\
    else\
    {\
        gstMBufHeadCache[gulMBufHeadCacheFreeIndex] = (pstMBufHead); \
        gulMBufHeadCacheFreeIndex = (gulMBufHeadCacheFreeIndex + 1) & g_stMbufCfgInfo.ulHeadCacheMask; \
        gulMBufHeadCacheFreeNum++;\
    }\
    MBUF_CACHE_UNLOCK(iFastMbufMask);\
}

/*����Mbuf DBD*/
#define MBUF_ALLOC_DBD(pstMBufDBD)\
{\
    LONG iFastMbufMask = 0;\
    MBUF_CACHE_LOCK(iFastMbufMask);\
    if ( gulMBufDBDCacheFreeNum > 0 )\
    {\
        (pstMBufDBD) = gstMBufDBDCache[gulMBufDBDCacheAllocIndex]; \
        gstMBufDBDCache[gulMBufDBDCacheAllocIndex] = NULL; \
        gulMBufDBDCacheAllocIndex = (gulMBufDBDCacheAllocIndex + 1) & g_stMbufCfgInfo.ulDBDCacheMask;\
        gulMBufDBDCacheFreeNum--;\
        if(MBUF_IDLE != pstMBufDBD->ulState)\
        {\
            MBUF_LOG_Info(7, 0, 0, 0, 0);\
            /*VOS_DBGASSERT(0);*/\
        }\
    }\
    else \
    {\
        (pstMBufDBD)->ulState = MBUF_BUSY;\
    }\
    MBUF_CACHE_UNLOCK(iFastMbufMask);\
}

/*�ͷ�Mbuf DBD*/
#define MBUF_FREE_DBD(pstMBufDBD)\
{\
    LONG iFastMbufMask = 0;\
    /*add by wht06310 for mbufcache debug,2006-05-10*/\
    if (pstMBufDBD->ulState != MBUF_BUSY)\
    {\
        MBUF_LOG_Info(1, 0, 0, 0, 0);\
        /*VOS_DBGASSERT(0);*/\
    }\
    MBUF_CACHE_LOCK(iFastMbufMask);\
    pstMBufDBD->ulState = MBUF_IDLE;\
    if (gulMBufDBDCacheFreeNum >= g_stMbufCfgInfo.ulDBDCacheNum)\
    {\
        (VOID)VOS_Free(pstMBufDBD);\
    }\
    else\
    {\
        gstMBufDBDCache[gulMBufDBDCacheFreeIndex] = (pstMBufDBD);\
        gulMBufDBDCacheFreeIndex = (gulMBufDBDCacheFreeIndex + 1) & g_stMbufCfgInfo.ulDBDCacheMask; \
        gulMBufDBDCacheFreeNum++;\
    }\
    MBUF_CACHE_UNLOCK(iFastMbufMask);\
}

/*����Mbuf DB*/ /* Modified for A82D22552 to got rid of calling VOS_Malloc2048 */
#define MBUF_ALLOC_DB(pstMBufDB, ulDataBlockSource) \
{\
    LONG iFastMbufMask = 0;\
    MBUF_CACHE_LOCK(iFastMbufMask);\
    if ( NULL != g_pfTCPIPUserDBMng) \
    {\
        (pstMBufDB) = g_pfTCPIPUserDBMng->AllocUserDB_HOOK_FUNC(g_usMBufDataBlockLength);\
        if(NULL != (pstMBufDB))\
        {\
             ulDataBlockSource = MBUF_DATA_USERMNG;\
        }\
    }\
    else if ( gulMBufDBCacheFreeNum > 0 )\
    {\
        (pstMBufDB) = gstMBufDBCache[gulMBufDBCacheAllocIndex]; \
        gstMBufDBCache[gulMBufDBCacheAllocIndex] = NULL; \
        gulMBufDBCacheAllocIndex = (gulMBufDBCacheAllocIndex + 1) & g_stMbufCfgInfo.ulDBCacheMask;\
        gulMBufDBCacheFreeNum--;\
    }\
    else \
    {\
#define MBUF_FREE_DB(pstMBufDBD)\
{\
    if((pstMBufDBD)->ulDataBlockSource == MBUF_DATA_USERMNG)\
    {\
        (VOID)g_pfTCPIPUserDBMng->FreeUserDB_HOOK_FUNC((pstMBufDBD)->pucDataBlock);\
    }\
    else if((pstMBufDBD)->ulDataBlockSource != MBUF_DATA_NORMAL)\
    {\
        (VOID)TCPIP_FreeSysDB((pstMBufDBD));\
    }\
    else\
    {\
        LONG iFastMbufMask = 0;\
        MBUF_CACHE_LOCK(iFastMbufMask);\
        if ((gulMBufDBCacheFreeNum >= g_stMbufCfgInfo.ulDBCacheNum)\
            || (MBUF_DATA_BLOCK2048_SIZE != (pstMBufDBD)->ulDataBlockLength))\
        {\
            (VOID)VOS_Free((pstMBufDBD)->pucDataBlock);\
        }\
        else\
        {\
            ULONG ulFastMbufRetVal = 0;\
            ULONG ulFastMbufReferenceCount = 0;\
            ulFastMbufRetVal = VOS_Mem_GetRef((pstMBufDBD)->pucDataBlock, & ulFastMbufReferenceCount);\
            if(ulFastMbufRetVal != 0)\
            {\
                ulFastMbufReferenceCount = 2;\
            }\
            if (1 == ulFastMbufReferenceCount)\
            {\
                gstMBufDBCache[gulMBufDBCacheFreeIndex] = ((pstMBufDBD)->pucDataBlock);\
                gulMBufDBCacheFreeIndex = (gulMBufDBCacheFreeIndex + 1) & g_stMbufCfgInfo.ulDBCacheMask; \
                gulMBufDBCacheFreeNum++;\
            }\
            else\
            {\
                (VOID)VOS_Free((pstMBufDBD)->pucDataBlock);\
            }\
        }\
        MBUF_CACHE_UNLOCK(iFastMbufMask);\
    }\
}

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


#define MBUF_CREATE_BY_DATA_BLOCK(pstMBufM, pucDataBlockM, ulDataBlockLengthM,    pucDataM, \
    ulDataLengthM, ulReceiveIfnetIndexM, ulModuleIDM)\
{\
    MBUF_ALLOC_HEAD(pstMBufM);\
    if( (pstMBufM) != NULL)\
    {\
        (pstMBufM)->stDataBlockDescriptor.pstNextDataBlockDescriptor = NULL;\
        (pstMBufM)->stDataBlockDescriptor.pucDataBlock = (pucDataBlockM);\
        (pstMBufM)->stDataBlockDescriptor.ulDataBlockLength = (ulDataBlockLengthM);\
        (pstMBufM)->stDataBlockDescriptor.pucData = (pucDataM);\
        (pstMBufM)->stDataBlockDescriptor.ulDataLength = (ulDataLengthM);\
        (pstMBufM)->stDataBlockDescriptor.ulDataBlockSource = MBUF_DATA_NORMAL;\
        (pstMBufM)->stDataBlockDescriptor.pucSysBlockCtl = NULL;\
        (pstMBufM)->stDataBlockDescriptor.ulType = MBUF_TYPE_DATA;\
        (pstMBufM)->stDataBlockDescriptor.ulOption = 0;\
        \
        (VOID)TCPIP_Mem_Set( (VOID *) (& pstMBufM->stUserTagData), 0 , sizeof(MBUF_USERTAGDATA_S));\
        (pstMBufM)->ulHeadLenth = 0;\
        (pstMBufM)->ulEntry = NULL;\
        (pstMBufM)->ulTotalDataLength = (ulDataLengthM);\
        (pstMBufM)->ulDataBlockNumber = 1;\
        (pstMBufM)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex = (ulReceiveIfnetIndexM);\
        (pstMBufM)->pstNextMBuf = NULL;\
        \
        if (((ulModuleIDM) >= MID_COMP_BASE) && ((ulModuleIDM) <= (MID_COMP_BASE + 0x00FF0000)))\
        {\
            ULONG ulMidIndex = ((ulModuleIDM) - MID_COMP_BASE) >> 16;\
            (pstMBufM)->ulModID = (ulModuleIDM);\
            g_ulMbufStatByMID[ulMidIndex]++; \
        }\
        else\
        {\
            (pstMBufM)->ulModID = 0;\
            g_ulMbufStatByMID[MBUF_MAX_MID]++;\
        }\
    }\
}


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

#define MBUF_SET_HEADLENTH(pMbuf, ulLenth) ((pMbuf)->ulHeadLenth = (ulLenth))
#define MBUF_GET_HEADLENTH(pMbuf)  ((pMbuf)->ulHeadLenth)
#define MBUF_ADD_HEADLENTH(pMbuf, ulLenth) ((pMbuf)->ulHeadLenth += (ulLenth))

/*public macro----------------------------------------------------------END*/



/*public function---------------------------------------------------------------------*/

/****************************************************************************
*    Func Name: MBUF_CreateByCopyBuffer()
*  Description: ͨ������buffer����MBUF
*        Input: ULONG ulReserveHeadSpace:������ͷ�ռ�
*               ULONG ulLength:����
*               UCHAR * pucBuffer:������
*               ULONG ulType:����
*               ULONG ulModuleID:ģ���,��δ��
*       Output: ��
*       Return: NULL:ʧ��
*               ����ֵ:������MBUF
*      Caution: even if both ulReserveHeadSpace and ulLength are 0, 
*               this function will create a DB
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_S * MBUF_CreateByCopyBuffer(ULONG ulReserveHeadSpace, ULONG ulLength, UCHAR * pucBuffer, ULONG ulType, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_CreateForControlPacket()
*  Description: ����һ��MBuf(��������)
*        Input: ULONG ulReserveHeadSpace:������ͷ�ռ�
*               ULONG ulLength:����
*               ULONG ulType:����
*               ULONG ulModuleID:ģ���,��δ��
*       Output: ��
*       Return: NULL:ʧ��
*               ����ֵ:������MBUF
*      Caution: even if both ulReserveHeadSpace and ulLength are 0, 
*               this function will create a DB
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_S * MBUF_CreateForControlPacket(ULONG ulReserveHeadSpace, ULONG ulLength, ULONG ulType, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_CreateBySysBuffer()
*  Description: ʹ�ô����������ݵ�����DB����һ��MBUF
*        Input: UCHAR * pucBuffer:����DB�ĵ�ַ
*               ULONG ulLength:����DB���ݳ���
*               ULONG ulDBLenth:����DB�ĳ���
*               UCHAR *pucCtl:����DB��MBUF��ַ
*               ULONG ulDataSource:����DB����Դ,1 --��̫����2--ppp����
*               ULONG ulType:DB���ݵ�����
*               ULONG ulModuleID:ģ���,��δ��
*       Output: ��
*       Return: NULL:ʧ��
*               ����ֵ:������MBUF
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_S * MBUF_CreateBySysBuffer(UCHAR * pucBuffer, ULONG ulLength, ULONG ulDBLenth,\
                                UCHAR *pucCtl, ULONG ulDataSource, ULONG ulType, ULONG ulModuleID);

/****************************************************************************
*    Func Name: MBUF_CopyDataFromBufferToMBuf()
*  Description: ��buffer�������ݵ�MBUF
*        Input: MBUF_S * pstMBuf: Mbufָ��
*               ULONG ulOffset:   ƫ����
*               ULONG ulLength:   ��������
*               UCHAR * pucBuffer:��������buf
*               ULONG ulModuleID: ģ��ID
*       Output: ��
*       Return: MBUF_OK:   �ɹ�
*               MBUF_FAIL: ʧ��
*      Caution: this function can deal with the mbuf whose first DB does not exist
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_CopyDataFromBufferToMBuf(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, UCHAR * pucBuffer, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_CopyDataFromMBufToBuffer()
*  Description: ��MBUF�������ݵ�buffer
*        Input: MBUF_S * pstMBuf:MBUFָ��
*               ULONG ulOffset:ƫ����
*               ULONG ulLength:����
*               UCHAR * pucBuffer:buffer
*       Output: ��
*       Return: MBUF_OK:   �ɹ�
*               MBUF_FAIL: ʧ��
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_CopyDataFromMBufToBuffer(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, UCHAR * pucBuffer);
/****************************************************************************
*    Func Name: MBUF_ReferenceCopy()
*  Description: MBUF���ÿ���
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulOffset:ƫ����
*               ULONG ulLength:����
*               ULONG ulModuleID:ģ���
*       Output: ��
*       Return: NULL:ʧ��
*               ����ֵ:����������MBUF
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_S * MBUF_ReferenceCopy(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_RawCopy()
*  Description: MBUF ��ʵ����
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulOffset:ƫ����
*               ULONG ulLength:����
*               ULONG ulReserveHeadSpace:����ͷ�ռ�
*               ULONG ulModuleID:ģ���
*       Output: ��
*       Return: NULL:ʧ��
*               ����ֵ:������MBUF
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_S * MBUF_RawCopy(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength, ULONG ulReserveHeadSpace, ULONG ulModuleID);

/****************************************************************************
*    Func Name: MBUF_Concatenate()
*  Description: ����MBUF Concatenate
*        Input: MBUF_S * pstDestinationMBuf:Ŀ��MBUF
*               MBUF_S * pstSourceMBuf:ԴMBUF
*               ULONG ulModuleID:ģ���,��δ��
*       Output: ��
*       Return: MBUF_OK:   �ɹ�
*               MBUF_FAIL: ʧ��
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_Concatenate(MBUF_S * pstDestinationMBuf, MBUF_S * pstSourceMBuf, ULONG ulModuleID);/*when ok, pstSourceMBuf is NOT valid any more*/
/****************************************************************************
*    Func Name: MBUF_NeatConcatenate_Chain()
*  Description: �ѿ�����Ϣ��mbuf�����һ��mbuf;
*        Input: MBUF_S *pstMbufHead:ָ��mbuf����ͷָ��
*               ULONG ulModuleID:ģ���
*       Output: ��
*       Return: 0:�ɹ�
*               1:ʧ��
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_NeatConcatenate_Chain(MBUF_S *pstMbufHead, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_Fragment()
*  Description: MBUF��Ƭ
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulLength:����
*               ULONG ulModuleID:ģ���
*       Output: ��
*       Return: NULL:��
*               ����ֵ:��Ƭ���MBUF
*      Caution: return surplus, pstMBuf store the first ulLength data
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_S * MBUF_Fragment(MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID);/*return the surplus data, pstMBuf is the first ulLength data*/

/****************************************************************************
*    Func Name: MBUF_CutAndFreeHead()
*  Description: MBUF��ͷ���ͷ�
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulLength:����
*       Output: ��
*       Return: MBUF_OK:   �ɹ�
*               MBUF_FAIL: ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_CutAndFreeHead(MBUF_S * pstMBuf, ULONG ulLength);
/****************************************************************************
*    Func Name: MBUF_CutPart()
*  Description: MBUF��������
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulOffset:ƫ����
*               ULONG ulLength:����
*       Output: ��
*       Return: MBUF_OK:   �ɹ�
*               MBUF_FAIL: ʧ��
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_CutPart(MBUF_S * pstMBuf, ULONG ulOffset, ULONG ulLength);
/****************************************************************************
*    Func Name: MBUF_CutTail()
*  Description: cut and free tail
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulLength:����
*       Output: ��
*       Return: MBUF_OK:   �ɹ�
*               MBUF_FAIL: ʧ��
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_CutTail(MBUF_S * pstMBuf, ULONG ulLength);

/****************************************************************************
*    Func Name: MBUF_AppendMemorySpace()
*  Description: MBUF����ڴ�ռ�
*        Input: MBUF_S * pstMBuf:MBUF
*               ULONG ulLength:����
*               ULONG ulModuleID:ģ���
*       Output: ��
*       Return: NULL:ʧ��
*               ����ֵ:���ӵ����ݿ��ַ
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
UCHAR * MBUF_AppendMemorySpace(MBUF_S * pstMBuf, ULONG ulLength, ULONG ulModuleID);
/****************************************************************************
*    Func Name: MBUF_AssignZero()
*  Description: MBUF������0
*        Input: MBUF_S * pstMBuf:MBUF
*       Output: ��
*       Return: MBUF_OK:   �ɹ�
*               MBUF_FAIL: ʧ��
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_AssignZero(MBUF_S * pstMBuf);

/****************************************************************************
*    Func Name: MBUF_ReferenceCopyByDescriptor()
*  Description: ����Descriptor���ÿ���MBUF
*        Input: MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor:���ݿ�
*               ULONG ulOffset:ƫ����
*               ULONG ulLength:����
*               ULONG ulModuleID:ģ���,��δ��
*       Output: ��
*       Return: NULL:ʧ��
*               ����ֵ:������MBUF
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
MBUF_S * MBUF_ReferenceCopyByDescriptor(MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor,  ULONG ulOffset, ULONG ulLength,  ULONG ulModuleID);

/****************************************************************************
*    Func Name: MBUF_NeatConcatenate()
*  Description: MBUF Neat Concatenate
*        Input: MBUF_S * pstDestinationMBuf:Ŀ��MBUF
*               MBUF_S * pstSourceMBuf:ԴMBUF
*               ULONG ulModuleID:ģ��ţ���δ��
*       Output: MBUF_DATABLOCKDESCRIPTOR_S ** ppstLastDataBlockDescriptor:���ݿ�
*       Return: MBUF_OK:   �ɹ�
*               MBUF_FAIL: ʧ��
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_NeatConcatenate(MBUF_S * pstDestinationMBuf, MBUF_S * pstSourceMBuf, MBUF_DATABLOCKDESCRIPTOR_S ** ppstLastDataBlockDescriptor, ULONG ulModuleID);

/****************************************************************************
*    Func Name: MBUF_RegMbufCfgInfo()
*  Description: ע��MBUF���ò����ĺ���
*        Input: MBUFCFGINFO_S *pstMbufCfgInfo:���ò�������
*       Output: ��
*       Return: MBUF_OK:   �ɹ�
*               MBUF_FAIL: ʧ��
*      Caution:  
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2000-3-25  zhang hong yan(19316)         Creat the first version.
*
*******************************************************************************/
ULONG MBUF_RegMbufCfgInfo(MBUFCFGINFO_S *pstMbufCfgInfo);
/*******************************************************************************
*    Func Name: MBUF_GetMbufStatusInfo
*  Description: ��ȡMBUF��״̬��Ϣ
*        Input: 
*       Output: MBUF_STATUS_S: *pstMbufStatus mbuf״̬
*       Return: MBUF_OK �ɹ�
*               MBUF_FAIL ��������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2007-07-11   mafeng 59090            Create
*
*******************************************************************************/
ULONG MBUF_GetMbufStatusInfo(MBUFSTATUSINFO_S* pstMbufStatus);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncFreeSysDBHook
*  Description: ע���ͷ�ϵͳDB�ĺ���ָ��
*        Input: FreeSysDB_HOOK_FUNC pfHookFunc:����ָ��
*       Output: 
*       Return: VOS_OK      �ɹ�
*               VOS_ERR     ����ָ��Ϊ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-27   zhoutong(43740)         Create
*
*******************************************************************************/
ULONG TCPIP_RegFuncFreeSysDBHook(FreeSysDB_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncDupSysDBHook
*  Description: ע�ḳֵϵͳDB�ĺ���ָ��
*        Input: DupSysDB_HOOK_FUNC pfHookFunc:����ָ��
*       Output: 
*       Return: VOS_OK      �ɹ�
*               VOS_ERR     ����ָ��Ϊ��
*      Caution: ���ϵͳDB���ü�������0�������reference copy���������ü���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-27   zhoutong(43740)         Create
*
*******************************************************************************/
ULONG TCPIP_RegFuncDupSysDBHook(DupSysDB_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncGetSysDBRefCntHook
*  Description: ע���ȡϵͳDB���ü����ĺ���ָ��
*        Input: GetSysDBRefCnt_HOOK_FUNC pfHookFunc:����ָ��
*       Output: 
*       Return: VOS_OK      �ɹ�
*               VOS_ERR     ����ָ��Ϊ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-27   zhoutong(43740)         Create
*
*******************************************************************************/
ULONG TCPIP_RegFuncGetSysDBRefCntHook(GetSysDBRefCnt_HOOK_FUNC pfHookFunc);
/*******************************************************************************
*    Func Name: TCPIP_RegFuncDecSysDBRefCntHook
*  Description: ע�����ϵͳDB�����ü����ĺ���ָ��
*        Input: DecSysDBRefCnt_HOOK_FUNC pfHookFunc:����ָ��
*       Output: 
*       Return: VOS_OK      �ɹ�
*               VOS_ERR     ����ָ��Ϊ��
*      Caution: �����ü���Ϊ0ʱ����Ҫ�ͷ�ϵͳDB
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-27   zhoutong(43740)         Create
*
*******************************************************************************/
ULONG TCPIP_RegFuncDecSysDBRefCntHook(DecSysDBRefCnt_HOOK_FUNC pfHookFunc);


ULONG TCPIP_RegFuncUserMngDBHook(TCPIP_USER_DB_HOOK_S *pstHookFunc);

/*public function---------------------------------------------------------------------END*/
/****************************************************************************************



                       mbuf queue interface


*****************************************************************************************/
typedef struct tagMBufQueue
{
    MBUF_S * pstHeadMBuf;
    MBUF_S * pstTailMBuf;
    ULONG ulCurrentLength;
    ULONG ulMaxLength;
}MBUF_QUEUE_S;

#define MBUF_QUE_INIT(pstMBufQueueM, ulMaxLengthM)\
{\
    (pstMBufQueueM)->pstHeadMBuf = NULL;\
    (pstMBufQueueM)->pstTailMBuf = NULL;\
    (pstMBufQueueM)->ulCurrentLength = 0;\
    (pstMBufQueueM)->ulMaxLength = (ulMaxLengthM);\
}

#define MBUF_QUE_NOT_EMPTY(pstMBufQueueM) ( (pstMBufQueueM)->ulCurrentLength )
#define MBUF_QUE_IS_FULL(pstMBufQueueM) ( (pstMBufQueueM)->ulCurrentLength >=  (pstMBufQueueM)->ulMaxLength )
#define MBUF_QUE_ENQUEUE(pstMBufQueueM, pstMBufM)\
{\
    MBUF_ASSIGN_PTR_NEXT_MBUF( (pstMBufM), NULL);\
    if( (pstMBufQueueM)->pstTailMBuf != NULL)/*queue is NOT empty*/\
    {\
        MBUF_ASSIGN_PTR_NEXT_MBUF( (pstMBufQueueM)->pstTailMBuf, (pstMBufM) );\
    }\
    else/*queue is empty*/\
    {\
        (pstMBufQueueM)->pstHeadMBuf = (pstMBufM);\
    }\
    (pstMBufQueueM)->pstTailMBuf = (pstMBufM);\
    (pstMBufQueueM)->ulCurrentLength++;\
}

#define MBUF_QUE_DEQUEUE(pstMBufQueueM, pstMBufM)\
{\
    (pstMBufM) = (pstMBufQueueM)->pstHeadMBuf;\
    if((pstMBufM) != NULL)/*queue is NOT empty*/\
    {\
        (pstMBufQueueM)->pstHeadMBuf = MBUF_GET_PTR_NEXT_MBUF( (pstMBufM) );\
        (pstMBufQueueM)->ulCurrentLength--;\
        if( (pstMBufQueueM)->pstTailMBuf == (pstMBufM) )/*this (pstMBufM) is the last in the queue*/\
        {\
            (pstMBufQueueM)->pstTailMBuf = NULL;\
        }\
    }\
}

#define MBUF_QUE_CATENATE(pstDestinationMBufQueueM, pstSourceMBufQueueM)\
{\
    if( (pstDestinationMBufQueueM)->pstTailMBuf == NULL)/*destination is empty*/\
    {\
        /*that source is empty or not has no difference to this process*/\
        (pstDestinationMBufQueueM)->pstHeadMBuf = (pstSourceMBufQueueM)->pstHeadMBuf;\
        (pstDestinationMBufQueueM)->pstTailMBuf = (pstSourceMBufQueueM)->pstTailMBuf;\
        (pstDestinationMBufQueueM)->ulCurrentLength = (pstSourceMBufQueueM)->ulCurrentLength;\
    }\
    else/*destination is NOT empty*/\
    {\
        if( (pstSourceMBufQueueM)->pstHeadMBuf != NULL)/*source is NOT empty*/\
        {\
            MBUF_ASSIGN_PTR_NEXT_MBUF( (pstDestinationMBufQueueM)->pstTailMBuf, (pstSourceMBufQueueM)->pstHeadMBuf);\
            (pstDestinationMBufQueueM)->pstTailMBuf = (pstSourceMBufQueueM)->pstTailMBuf;\
            (pstDestinationMBufQueueM)->ulCurrentLength += (pstSourceMBufQueueM)->ulCurrentLength;\
        }\
        /*when source is empty, nothing need to do*/\
    }\
    (pstSourceMBufQueueM)->pstHeadMBuf = NULL;\
    (pstSourceMBufQueueM)->pstTailMBuf = NULL;\
    (pstSourceMBufQueueM)->ulCurrentLength = 0;\
}


#define MBUF_QUE_PEEK(pstMBufQueueM) ((pstMBufQueueM)->pstHeadMBuf)

#define MBUF_QUE_GET_CURRENT_LENGTH(pstMBufQueueM) ((pstMBufQueueM)->ulCurrentLength)

#define MBUF_QUE_GET_MAX_LENGTH(pstMBufQueueM) ((pstMBufQueueM)->ulMaxLength)

#define MBUF_QUE_GET_ALL( pstMBufQueueM, pstMBufM)\
{\
    ( pstMBufM )= ( pstMBufQueueM )->pstHeadMBuf;\
    ( pstMBufQueueM )->pstHeadMBuf = NULL;\
    ( pstMBufQueueM )->pstTailMBuf = NULL;\
    ( pstMBufQueueM )->ulCurrentLength = 0;\
}

#define MBUF_QUE_DEAL_PACKET(pstMBufQueueM, ulCountM, pfDeal)\
{\
    MBUF_S * pstMBufM;\
    MBUF_S * pstTempMBuf;\
    ULONG ulCount;\
    \
    ulCount = (ulCountM);\
    pstTempMBuf = (pstMBufQueueM)->pstHeadMBuf;\
    (pstMBufQueueM)->ulCurrentLength -= ulCount;\
    for(; ulCount > 0; ulCount-- )\
    {\
        pstMBufM = pstTempMBuf;\
        pstTempMBuf = MBUF_GET_PTR_NEXT_MBUF(pstMBufM);\
        MBUF_ASSIGN_PTR_NEXT_MBUF( pstMBufM, NULL );\
        (VOID)pfDeal(pstMBufM);\
        (VOID)TCPIP_SchedPoint_Check_Delay();\
    }\
    (pstMBufQueueM)->pstHeadMBuf = pstTempMBuf;\
}

#define MBUF_QUE_PREPEND(pstMBufQueueM, pstMBufM)\
{\
    MBUF_ASSIGN_PTR_NEXT_MBUF(pstMBufM, ( pstMBufQueueM )->pstHeadMBuf);\
    ( pstMBufQueueM )->pstHeadMBuf = pstMBufM;\
    if( NULL == ( pstMBufQueueM )->pstTailMBuf )\
    {\
        ( pstMBufQueueM )->pstTailMBuf = pstMBufM;\
    }\
    ( pstMBufQueueM )->ulCurrentLength ++;\
}

#define MBUF_QUE_FREE(pstMBufQueueM)\
{\
    MBUF_S * pstMBuf;\
    MBUF_S * pstNextMBuf;\
    \
    pstMBuf = ( pstMBufQueueM )->pstHeadMBuf;\
    while(pstMBuf != NULL)\
    {\
        pstNextMBuf = MBUF_GET_PTR_NEXT_MBUF(pstMBuf);\
        MBUF_Destroy(pstMBuf);\
        pstMBuf = pstNextMBuf;\
    }\
    ( pstMBufQueueM )->pstHeadMBuf = NULL;\
    ( pstMBufQueueM )->pstTailMBuf = NULL;\
    ( pstMBufQueueM )->ulCurrentLength = 0;\
}

/***************************************************************************

                        user tag data macro

***************************************************************************/
#define MBUF_FLAG_BROADCAST     0x00000001
#define MBUF_FLAG_MULTICAST     0x00000002
#define MBUF_FLAG_URGENT_PACKET 0x00000004
/************************************************
L2&L3Ϊ֧�ֲ�Ʒ�ĵײ㷢�ͣ��ڷ��͵�MBUF��������������MBUF��ǣ�
1������ָ������˿ڵĵ������ģ���:ARPӦ���ġ�IP���ݱ��ĵȣ�
   VISP�ڴ����͵�MBUF�����ñ��ı�� MBUF_FLAG_SINGLECAST��
   ��Ʒ�ײ��ڷ��ʹ����У�ʶ��˱�Ǻ󣬿��Ը��ݳ��˿�ֱ�ӷ��ͣ�Ҳ���Խ���L2���ת����
2��������·��Э�鱨�ģ���MSTP��OAM��LACP�ȣ�������Щ���Ķ���MAC�鲥�ģ�����������ָ���˿��Ϸ���(������VLAN�ڹ㲥)��
   VISP�ڴ����͵�MBUF�����ñ��ı�� MBUF_FLAG_PROTOCOLCAST����ָ�����˿ڣ�
   ��Ʒ�ײ��ڷ��ʹ����У��������ָ�����˿������ͱ��ģ�������VLAN�ڹ㲥����
*************************************************/
#define MBUF_FLAG_SINGLECAST    0x00000008
#define MBUF_FLAG_PROTOCOLCAST  0x00000080

#define MBUF_FLAG_MFORWARD_IO    0x00040000

#define MBUF_FLAG_CONF            0x00000010    /*for ipsec, packet has been encrypted*/
#define MBUF_FLAG_AUTH            0x00000020    /*for ipsec, packet has been authenticated*/
#define MBUF_FLAG_TUNNEL          0x00000040    /*for ipsec, packet has been added tunnel IP head*/
#define MBUF_FLAG_ENCAPSULATED    0x00000800  /*for ipsec outbound packet*/

#define MBUF_FLAG_COMPRESSED_TCP_PACKET        0x00000100
#define MBUF_FLAG_ORDER_PACKET        0x00000200

#define MBUF_FLAG_RECORD_ROUTE        0x00010000

#define MBUF_FLAG_RTP_LLQ_PACKET        0x00100000 /*���Ӵ���MBUF*/
#define MBUF_FLAG_LINK_FRAGMENT_PACKET 0x00200000 /*��·���Ƭ��Ӵ���MBUF*/

#define MBUF_FLAG_FRF12_FRAGMENT_PACKET        0x00400000 /*���Ӵ���MBUF*/

#define MBUF_FLAG_HEADCACHE  0x00800000 /*Head Cache����*/

/* add for BfdOverTrunkPort */
#define MBUF_FLAG_BFD_OVER_TRUNKPORT 0x00020000
#define MBUF_SET_BFD_TRUNKPORT_IFNET_INDEX(pstMBufM, ulOutIfnetIndex) \
{\
    (pstMBufM)->stUserTagData.stCommonInfo.ulPhyInputIfIndex = (ulOutIfnetIndex);\
}
#define MBUF_GET_BFD_TRUNKPORT_IFNET_INDEX(pstMBuf) \
    ((pstMBuf)->stUserTagData.stCommonInfo.ulPhyInputIfIndex)

#define MBUF_AMFLAG_DECAPSULATED    0x00000400  /*for ipsec inbound packet*/
#define MBUF_AMFLAG_QOSINPUT             0x00000001

#define MBUF_GET_USER_TAG_DATA_PTR(pstMBufM) (&((pstMBufM)->stUserTagData))
#define MBUF_GET_RECEIVE_IFNET_INDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex )
#define MBUF_ASSIGN_RECEIVE_IFNET_INDEX(pstMBufM, ulReceiveIfnetIndexM) \
{\
    if ((pstMBufM)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex != (ulReceiveIfnetIndexM))\
    {\
        MBUF_CLEAR_AMFLAG(pstMBufM, MBUF_AMFLAG_DECAPSULATED);\
    }\
    (pstMBufM)->stUserTagData.stCommonInfo.ulReceiveIfnetIndex = (ulReceiveIfnetIndexM);\
}

/*����L2IFģ��ı�����˿ڽӿ�����*/
#define MBUF_SET_PORTIFINDEX(pstMBufM, PortIfIndex)\
{\
    (pstMBufM)->stUserTagData.stCommonInfo.ulPortIfIndex = PortIfIndex;\
}

/*��ȡL2IFģ��ı�����˿ڽӿ�����*/
#define MBUF_GET_PORTIFINDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulPortIfIndex )

#define MBUF_GET_SEND_IFNET_INDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulSendIfnetIndex )
#define MBUF_ASSIGN_SEND_IFNET_INDEX(pstMBufM, ulSendIfnetIndexM) \
    ((pstMBufM)->stUserTagData.stCommonInfo.ulSendIfnetIndex = (ulSendIfnetIndexM))

#define MBUF_GET_SEND_AT_INDEX(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulSendAtIndex )
#define MBUF_ASSIGN_SEND_AT_INDEX(pstMBufM, ulSendAtIndexM) \
    ((pstMBufM)->stUserTagData.stCommonInfo.ulSendAtIndex = (ulSendAtIndexM))

#define MBUF_GET_IP_INFO_REV_BOARD_ID(pstMBufM) ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.ulRevBoardId)
#define MBUF_ASSIGN_IP_INFO_REV_BOARD_ID(pstMBufM, ulSendSlot) ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.ulRevBoardId = ulSendSlot )


#define MBUF_GET_FLAG(pstMBufM) ( (pstMBufM)->stUserTagData.stCommonInfo.ulFlag )
#define MBUF_SET_FLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.stCommonInfo.ulFlag |= (ulFlagM))
#define MBUF_CLEAR_FLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.stCommonInfo.ulFlag &= ( ~(ulFlagM) ))
#define MBUF_GET_AMFLAG(pstMBufM) ( (pstMBufM)->stUserTagData.ulAntiMultiFlag )
#define MBUF_SET_AMFLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.ulAntiMultiFlag |= (ulFlagM))
#define MBUF_CLEAR_AMFLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.ulAntiMultiFlag &= ( ~(ulFlagM) ))

#define MBUF_GET_QUEUE_ID(pstMBufM) ((pstMBufM)->stUserTagData.stCommonInfo.ulQueueID)
#define MBUF_ASSIGN_QUEUE_ID(pstMBufM, ulQueIDM) \
    ((pstMBufM)->stUserTagData.stCommonInfo.ulQueueID = (ulQueIDM))

#define MBUF_LINK_TYPE_X25                1
#define MBUF_LINK_TYPE_ETHERNET           2
#define MBUF_LINK_TYPE_FRAME_RELAY        3

#define MBUF_GET_TAG_LINK_TYPE(pstMBufM) ((pstMBufM)->stUserTagData.ulLinkType)
#define MBUF_ASSIGN_TAG_LINK_TYPE(pstMBufM, ulLinkTypeM) ((pstMBufM)->stUserTagData.ulLinkType = ulLinkTypeM)

#define MBUF_GET_TAG_LINK_X25_PTR(pstMBufM) (& ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToLink.stX25Info ))
#define MBUF_GET_TAG_LINK_ETHERNET_PTR(pstMBufM) (& ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToLink.stEthernetInfo ))

#define MBUF_GET_TAG_LINK_FRAME_RELAY_PTR(pstMBufM) (& ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToLink.stFrameRelayInfo ))

#define MBUF_GET_TAG_LINK_ATM_PTR(pstMBufM) (& ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToLink.stATMInfo ))

#define MBUF_GET_TAG_VCCINDEX_ATM_PTR(pstMBufM) ( ((CHAR*)&(pstMBufM->stUserTagData.unPacketInfoRelevantToLink.stATMInfo)) + 8 )

#define MBUF_GET_LINK_PPP_PROTOCOL(pstMBufM) \
((pstMBufM)->stUserTagData.unPacketInfoRelevantToLink.stPppInfo.usProtocol)


#define MBUF_ASSIGN_LINK_PPP_PROTOCOL(pstMBufM,usProtocolM) \
((pstMBufM)->stUserTagData.unPacketInfoRelevantToLink.stPppInfo.usProtocol = \
(usProtocolM))

#define MBUF_GET_NETWORK_IP_PROTOCOL(pstMBufM)\
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.ucProtocolId)
#define MBUF_GET_NETWORK_IP_DESPORT(pstMBufM)\
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.usDestinationPortOrIcmpCode)

#define MBUF_NETWORK_TYPE_IP            1
#define MBUF_NETWORK_TYPE_IPX           2

#define MBUF_GET_TAG_NETWORK_TYPE(pstMBufM) ((pstMBufM)->stUserTagData.ulNetworkType)
#define MBUF_ASSIGN_TAG_NETWORK_TYPE(pstMBufM, ulNetworkTypeM) \
    ((pstMBufM)->stUserTagData.ulNetworkType = ulNetworkTypeM)

#define MBUF_GET_TAG_NETWORK_IP_PTR(pstMBufM) (& ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo ))

#define MBUF_GET_TAG_MPLS_PTR(pstMBufM)   (& ( (pstMBufM)->stUserTagData.stMplsPacketInfo))

#define MBUF_GET_TAG_MPLS_VPNID(psMBufM, ulXId)\
{\
        ulXId = (psMBufM)->stUserTagData.stMplsPacketInfo.ulVrfIndex; \
}

#define MBUF_SET_TAG_MPLS(pstMBufM, ulToken, ulFlag) \
{\
        (pstMBufM)->stUserTagData.stMplsPacketInfo.ulL3Info |= (ulFlag);    \
        (pstMBufM)->stUserTagData.stMplsPacketInfo.ulVrfIndex = (ulToken);\
}

#define MBUF_SET_TAG_MPLS_VPNID(psMBufM, ulXId)\
{\
        (psMBufM)->stUserTagData.stMplsPacketInfo.ulVrfIndex = ulXId; \
}

/* �õ�MBUF��IPv6���ƽṹָ�� */
#define MBUF_GET_TAG_NETWORK_IP6_PTR(pstMBufM) (& ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo ))

/* �õ���������һ��physical��ַ��ָ�� */
#define MBUF_GET_IPV6_NEXTHOPMACADDR(pstMBufM) \
((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.unLinkAddr.szLinkEtherAddr)

/* ���ñ�������һ��physical��ַ */
#define MBUF_ASSIGN_IPV6_NEXTHOPMACADDR(pstMBufM, szMac) \
((VOID)TCPIP_Mem_Copy((UCHAR *)((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.unLinkAddr.szLinkEtherAddr),MBUF_MACADDRLEN, \
(UCHAR *)szMac, MBUF_MACADDRLEN))

#define MBUF_GET_IP_INFO_ICMP_TYPE(pstMBufM)   ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.usSourcePortOrIcmpType )
#define MBUF_SET_IP_INFO_ICMP_TYPE(pstMBufM, ulType)\
    ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.usSourcePortOrIcmpType = (USHORT)(ulType) )

#define MBUF_GET_IP_INFO_ICMP_CODE(pstMBufM)   ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.usDestinationPortOrIcmpCode )
#define MBUF_SET_IP_INFO_ICMP_CODE(pstMBufM, ulCode)\
    ( (pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.usDestinationPortOrIcmpCode = (USHORT)(ulCode) )

/* V100R006 Lijing 52889 Add for Trunk */
#define MBUF_SET_INPUT_PHY_IFINDEX(pstMBuf, ulIfIndex) \
    ((pstMBuf)->stUserTagData.stCommonInfo.ulPhyInputIfIndex = (ulIfIndex))

/* V100R006 Lijing 52889 Add for Trunk */
#define MBUF_GET_INPUT_PHY_IFINDEX(pstMBuf) \
    ((pstMBuf)->stUserTagData.stCommonInfo.ulPhyInputIfIndex)

#define MBUF_SET_DCC_FLOWID(pstMBufM, ucDccPktFlowID) (pstMBufM->stUserTagData.ucDccFlowID = ucDccPktFlowID)
#define MBUF_GET_DCC_FLOWID(pstMBufM) (pstMBufM->stUserTagData.ucDccFlowID)

#define MBUF_SET_DCCFLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.ucDccFlag |= (ulFlagM))
#define MBUF_CLEAR_DCCFLAG(pstMBufM, ulFlagM) ((pstMBufM)->stUserTagData.ucDccFlag &= (~(ulFlagM)))
#define MBUF_GET_DCCFLAG(pstMBufM) ((pstMBufM)->stUserTagData.ucDccFlag)
#define MBUF_FLAG_DCCSTREAM_RCV       0x01
#define MBUF_FLAG_DCCSTREAM_SND       0x02
#define MBUF_FLAG_DCCSTREAM_DESTROY   0x04
/* END */

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
/*******************************************************************************
*    Func Name: TCPIP_GetSysDBRefCnt
*  Description: ��ȡϵͳDB�����ü���
*        Input: MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor:Ҫ��ȡ���ü���DB��Ӧ��DBD
*       Output: ULONG *pulCount:���ü���
*       Return: VOS_OK:�ܷ��سɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2004-7-7     zhany hong yan(19316)   Create
*
*******************************************************************************/
extern ULONG TCPIP_GetSysDBRefCnt(MBUF_DATABLOCKDESCRIPTOR_S * pstDataBlockDescriptor, ULONG *pulCount);

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

/* ��ȡMBUF�е�IPV6�������ͱ�ʶ */
#define MBUF_GET_IP6_INFO_PKT_TYPE(pstMBufM)\
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIp6PacketInfo.ulIpPktType)

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

#define MBUF_ASSIGN_VLANID(pstMBuf,usVLANID) ((pstMBuf)->stUserTagData.usVID = (USHORT)(usVLANID))
#define MBUF_GET_VLANID(pstMBuf) ((pstMBuf)->stUserTagData.usVID)

#define ARP_LOG_GET_VLANHEAD(pstMBuf) pstMBuf->stUserTagData.unPacketInfoRelevantToPhysical.ulTemp
#define ARP_LOG_SET_VLANHEAD(pstMBuf,ulVlanHead) \
{\
    pstMBuf->stUserTagData.unPacketInfoRelevantToPhysical.ulTemp = ulVlanHead;\
}
/* End of addition */

/*************************�������Ż��йصĺ�*************************/
/* �����������ձ�־ */
#define MBUF_SET_IPTYPE_OURRCV(pMbuf)\
{\
    (pMbuf)->usPktType = OPTIM_MBUF_OURRCV;\
}

/* ����socket ID */
/* iFdǰ�����(USHORT)������ǿ������ת���Ժ���߱��ʽ����һ�� */
#define MBUF_SET_SOCKET_ID(pMbuf, iFd)\
{\
    (pMbuf)->usSocketID = (USHORT)(iFd);\
}

/* ��ȡsocket ID */
#define MBUF_GET_SOCKET_ID(pMbuf, iFd)\
{\
    (iFd) = (pMbuf)->usSocketID;\
}

#define MBUF_GET_IP_INFO_PKT_TYPE(pstMBufM)\
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.ulIpPktType)

#define MBUF_SET_IP_INFO_PKT_TYPE(pstMBufM,flag)\
    ((pstMBufM)->stUserTagData.unPacketInfoRelevantToNetwork.stIpPacketInfo.ulIpPktType |= flag)

/*************************�������Ż��йصĺ�*************************/

/* ��ȡ��̫֡��װ����(Eth2/SNAP) */
#define MBUF_GET_ETHERNET_ENCAP_TYPE(pstMBufM)\
    ((pstMBufM)->ulEncapType)

/* ������̫֡��װ����(Eth2/SNAP) */    
#define MBUF_SET_ETHERNET_ENCAP_TYPE(pstMBufM,ulFlagM)\
    (((pstMBufM)->ulEncapType ) = (ulFlagM))

/*****************************ʱ���������*****************************/
/* ���õ��ֽ�ʱ��� */
#define MBUF_SET_TIMESTAMP_LOW(pstMbuf,ulTimeMinSecondLow) \
    ((pstMbuf)->ulTimeStampLow = (ulTimeMinSecondLow))

/* ���ø��ֽ�ʱ��� */
#define MBUF_SET_TIMESTAMP_HIGH(pstMbuf, ulTimeMinSecondHigh) \
    ((pstMbuf)->ulTimeStampHigh = (ulTimeMinSecondHigh))

/* ��ȡ���ֽ�ʱ��� */
#define MBUF_GET_TIMESTAMP_LOW(pstMbuf)       ((pstMbuf)->ulTimeStampLow)

/* ��ȡ���ֽ�ʱ��� */
#define MBUF_GET_TIMESTAMP_HIGH(pstMbuf)      ((pstMbuf)->ulTimeStampHigh)

/* ����ģ��ID��Mbuf����ͳ�� */
#define MBUF_ADD_STAT_BY_MID(pstMbuf, ulModuleId)\
{\
    pstMbuf->ulModID = ulModuleId;\
    if ((ulModuleId >= MID_COMP_BASE) && (ulModuleId <= (MID_COMP_BASE + 0x00FF0000)))\
    {\
        ULONG ulMidIndex = (ulModuleId - MID_COMP_BASE) >> 16;\
        g_ulMbufStatByMID[ulMidIndex]++;\
    }\
    else\
    {\
        pstMbuf->ulModID = 0;\
        g_ulMbufStatByMID[MBUF_MAX_MID]++;\
    }\
}

/* ����ģ��ID��Mbuf�Լ�ͳ�� */
#define MBUF_DEC_STAT_BY_MID(pstMbuf)\
{\
    if (0 == pstMbuf->ulModID)\
    {\
        g_ulMbufStatByMID[MBUF_MAX_MID]--;\
    }\
    else\
    {\
        ULONG ulMidIndex = (pstMbuf->ulModID - MID_COMP_BASE) >> 16;\
        ulMidIndex &= (ULONG)0xff;\
        g_ulMbufStatByMID[ulMidIndex]--;\
    }\
}

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif    /* end of _MBUF_H_ */

