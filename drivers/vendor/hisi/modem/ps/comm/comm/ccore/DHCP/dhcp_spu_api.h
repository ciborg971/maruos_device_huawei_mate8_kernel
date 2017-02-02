
#ifndef __DHCP_SPU_API_H__
#define __DHCP_SPU_API_H__

/*******************************************************************************************************/
/********************                          �궨��                           ************************/
/*******************************************************************************************************/
/*dhcp���ݰ��е�chaddr ��,sname���file��ĳ���*/
#define DHCPS_CHADDR_LEN               16
#define DHCPS_SNAME_LEN                64
#define DHCPS_FILE_LEN                128

#define DHCPV6C_MAX_DUID_LEN 14 /* DUID ����󳤶� 14�ֽ� */

/* 24bit��С�ֽ���ת��---��Ҫ��transctionId��24bit 0x15001605----0x15051600*/
#ifndef VOS_NTOHBIT24
#if VOS_BYTE_ORDER == VOS_BIG_ENDIAN
#define VOS_NTOHBIT24(x)    (x)
#define VOS_HTONBIT24(x)    (x)
#else
#define VOS_NTOHBIT24(x)    ((((x) & 0x0000ff) << 16) | \
             ((x) & 0x00ff00) | \
             (((x) & 0xff0000) >> 16) )

#define VOS_HTONBIT24(x)    ((((x) & 0x0000ff) << 16) | \
             ((x) & 0x00ff00) | \
             (((x) & 0xff0000) >> 16) )
#endif
#endif

/*******************************************************************************************************/
/********************                        �ṹ����                           ************************/
/*******************************************************************************************************/

/*DHCPS��USM֮�����Ϣ����*//*��Ҫ�ŵ�pub.h��*/
typedef enum tagDHCPS_USM_MSG_E
{
    DHCPS_USM_APPLYIP_MSG           =  1,   /*DHCPS���͸�USM����IP��ַ*/
    DHCPS_USM_RELEASEIP_MSG        =  2,  /*DHCPS���͸�USM�ͷ�IP��ַ*/
    DHCPS_USM_APPLYIPOK_MSG       = 3,  /*USM��Ӧ�������ַ�ɹ�*/
    DHCPS_USM_APPLYIPFAILED_MSG = 4,  /*USM��Ӧ�������ַʧ��*/
    DHCPS_USM_DEACTIVE_MSG         = 5,  /*USM���͵�ȡ���û�*/
    DHCPS_USM_MSG_END
}DHCPS_USM_MSG_E;

/*DHCP���ƿ�*/
typedef struct tagDHCPC_CTRLBLK
{
    struct tagDHCPC_CTRLBLK *pstPreNode;
    struct tagDHCPC_CTRLBLK *pstNextNode;
    VOID *pTmpDhcpCtrlBlkPtr;       /* ���ڱ�����ʱ���ƿ�ָ�� */
    ULONG       ulDHCPCtxIdx;       /*DHCP���ƿ�����*/
    ULONG       ulPDPIndex;         /*�û�������������*/
    ULONG       aulMSISDN[2];       /*MSISDN*/
    ULONG       aulIMSI[2];         /*IMSI*/
    ULONG       aulIMEI[2];         /* IMEI */
    ULONG       ulLease;            /*��õ�lease*/
    ULONG       ulTimeStamp;        /*����REQ��Ϣ��ϵͳʱ��*/
    ULONG       aulSrvIp[4];        /*������server IP*/
    ULONG       aulUserIpAddr[4];   /*�û������ĵ�IP��ַ*/
    ULONG       aulMainDnsAddr[4];  /*��DNS-IP��ַ*/
    ULONG       aulSecdDnsAddr[4];  /*��DNS-IP��ַ*/
    ULONG       aulAgentIpAddr[4];  /*����IP��ַ*/
    ULONG       ulTmpVar;           /*��ʱ���������ڱ�����ʱ���ƿ�ָ�뼰��Լʱ����REQ��ulTimeStamp*/
    ULONG       ulTEIDC;            /* TEIDC. ע��!!!! ���������޸ġ���Dhcpv6��ʹ����,�����ڿ��ƿ���������޸ġ� */
    ULONG       ulT1;               /* DHCPv6��ַ��T1ʱ�� */
    ULONG       ulT2;               /* DHCPv6��ַ��T2ʱ�� */

    USHORT      usVPNIndex;         /* ����LAP��Ϣ�е�VPN���� */
    USHORT      usPoolIndex;
    USHORT      usServerGrpIndex;   /*ServerGrp index*/
    USHORT      usApnIndex;         /*APN����*/ /* Modified by heguangwei 65937 at 2008-04-29 performance for AX4D00955 */

    USHORT      usSeqNum;
    UCHAR       ucUserType:4;       /*UserType ppp,gtp*/
    UCHAR       usDhcpStatus:4;     /*DHCP״̬*/ /* Modified by heguangwei 65937 at 2008-04-29 performance for AX4D00955 */
    UCHAR       ucRole:4;
    UCHAR       ucUser:4;            /*�û�����:V0:0;V1:1;V2:2*/
    UCHAR       ucCurSvrSendCount:4; /* ��ǰServer������Ϣ�Ĵ��� */
    UCHAR       ucTotalSendCount:4;  /* ��Server������Ϣ���ܴ��� */
    UCHAR       ucResendTimeout;     /* �ڷ�����Ϣ�ĵ�һ�λ�ȡ,�ط���Ϣ�����в���ȡ. */
    UCHAR       ucCurrentServer:1;
    UCHAR       ucWaitRspTimeOutNum:4;
    UCHAR       ucAgingFlag:3;       /* ���ƿ��� */
    UCHAR       ucLAPNo;

    UCHAR       aucSiDuid[DHCPV6C_MAX_DUID_LEN]; /* �����ַ��DHCP������ID */
    UCHAR       ucIpType:4;
    UCHAR       ucResource:3;       /* ��Դλ��־ */
    UCHAR       ucUsedFlag:1;       /* ���ƿ��Ƿ�ռ�ñ�־. ע��!!!! �����ڿ��ƿ���������޸ġ�  */
    UCHAR       ucLeaseStatus:4;    /* ��Լ״̬ */
    UCHAR       ucCause:4;

    UCHAR       ucRandomNo;

#if 0
    UCHAR       aucResved[3];       /*�����ֶ�*/
#endif
    VOS_UINT8   ucRabId;                      /*RabId*/
    MODEM_ID_ENUM_UINT16  enModemId;          /*enModemId*/
}DHCPC_CTRLBLK;

/* BEGIN: Added by jixiaoming for ��ʡ�ڴ� at 2012-10-26 */

typedef struct tagDHCPV4C_BAK_INFO_S
{
    ULONG       ulUserIpAddr;
    ULONG       ulAgentIpAddr;
    ULONG       ulServerIp;
    UCHAR       aucReserve[44];
}DHCPV4C_BAK_INFO_S;

typedef struct tagDHCPV6C_BAK_INFO_S
{
    ULONG       aulUserIpAddr[4];
    ULONG       aulAgentIpAddr[4];
    ULONG       ulT1;               /* DHCPv6��ַ��T1ʱ�� */
    ULONG       ulT2;               /* DHCPv6��ַ��T2ʱ�� */
    UCHAR       aucSiDuid[DHCPV6C_MAX_DUID_LEN];    /* �����ַ��DHCPV6������ID */
    UCHAR       ucLeaseStatus:4;    /* ��Լ״̬.V6��ʹ�� */
    UCHAR       ucResource:3;       /* ��Դλ,V6ʹ�� */
    UCHAR       ucCurrentServer:1;  /* ��ǰʹ�õ�Server,V6ʹ�� */
    UCHAR       ucReserve;
}DHCPV6C_BAK_INFO_S;

/*
   DHCP Client���ݿ��ƿ�.���д�ŵ�Ϊ���뱸�ݵ�����,�Ǳ��뱸�����ݲ��ɷ��롣
   �޸ĸýṹ��,��Ӱ�쵽CKP������ڴ��С�������޸ĸýṹ�����ͨ��MDE����
*/
typedef struct tagDHCPC_BACKBLK_S
{
    ULONG       aulMSISDN[2];       /* MSISDN */
    ULONG       aulIMSI[2];         /* IMSI */
    ULONG       aulIMEI[2];         /* IMEI */
    ULONG       ulLease;            /* leaseʱ��,V4��V6���� */
    ULONG       ulTimeStamp;        /* ��ַ�����renew�ɹ���ʱ��� */
    ULONG       ulTEIDC;
    ULONG       ulPDPIndex;         /* ���������� */
    USHORT      usVPNIndex;         /* �����LAP��Ϣ�л�ȡ��VPN���� */
    USHORT      usPoolIndex;        /* ��ַ������ */
    USHORT      usServerGrpIndex;   /* ServerGrp index*/
    USHORT      usApnIndex;         /* APN���� */

    union
    {
        DHCPV4C_BAK_INFO_S stDhcpv4;
        DHCPV6C_BAK_INFO_S stDhcpv6;
    }unBakInfo;

    UCHAR       ucLAPNo;            /* �����ַ��LAP���е�ı�� */
    UCHAR       ucRandomNo;         /* ������ٺ� */
    UCHAR       ucRole:4;           /* Ŀǰ���������ĵĽ�ɫ */
    UCHAR       usDhcpStatus:4;     /* DHCP״̬ */
    UCHAR       ucReserve;
}DHCPC_BACK_BLK_S;
/* END: Added by jixiaoming for ��ʡ�ڴ� at 2012-10-26 */

/*dhcp���������ṹDHCPS_ANALYZEDPACKET_S*/
typedef struct tagDHCPS_ANALYZEDPACKET
{
    ULONG        ulRequestedAddr;      /*�����ip��ַ*/
    USHORT      usPacketLength;       /*���ݰ�����*/
    UCHAR        ucPacketType;          /*���ݰ�����*/
    UCHAR        ucHtype;                 /* �û�Ӳ������*/

    ULONG        ulXid;                       /* Transaction ID */
    USHORT      usFlags;                  /* Flag bits */
    USHORT      usMaxDhcpSize;     /*���İ��ĳ��� */

    ULONG        ulCiaddr;                 /* Client IP address (if already in use) */
    ULONG        ulGiaddr;                 /* DHCP relay agent IP address */
    UCHAR        pucChaddr [DHCPS_CHADDR_LEN];       /* Client hardware address */
    ULONG        ulYiaddr;                 /* Client IP address */
    ULONG        ulServerId;             /* ��������IP��ַ */
    UCHAR        aucParaReqList[256];   /*1~254, ��ౣ��254��*/
    UCHAR        ucParaReqLen;
    UCHAR        ucOptionOverload;  /*�ֶ� overload��־*/
    UCHAR       ucRapidCommitFlag;
    UCHAR       aucRev[1];
}DHCPS_ANALYZEDPACKET_S;

/*��Լ������Ϣ�ṹDHCPS_LEASE_S*/
typedef struct tagDHCPS_LEASE
{
    DHCPS_ANALYZEDPACKET_S  *pstAnalyzedPacket;       /*��Ӧ��ԭʼ���ĵĽ�����Ϣ*/
    ULONG                   ulAddr;                   /*lease��ipv4��ַ*/
    ULONG                   ulIndex;                  /*��Լ������Ҳ���û�������������*/

    UCHAR                   ucPmipFlag;               /*S5S8�ӿڵ�Э���־  0 gtp  1 pmip*/
    UCHAR                   ucRole;                   /*���ӽ�ɫ*/
    UCHAR                   ucLeaseState:4;           /*����LEASE��״̬ */
    UCHAR                   ucLeaseTimerOP:3;         /*֪ͨ������Լ��ʱ��������־:0��ʾ��Ч;1��ʾ����;2��ʾɾ��;3��ʾ��ɾ��������*/
    UCHAR                   ucUsed:1;                 /*ʹ�ñ��*/
    UCHAR                   ucUserNumFlag:1;          /*Ԥ���ֶ�*/
    UCHAR                   ucFirstRequestMsgFlag:1;  /*ֱ�ӷ���Request��Ϣ�ı�־λ*/
    UCHAR                   ucReserveBit:6;
#ifdef __LINUX_PLATFORM__
    UCHAR                   aucReserve[4];
#endif
}DHCPS_LEASE_S;

typedef struct tagDHCP
{
    UCHAR       ucOp; /*1=����2=Ӧ��*/
    UCHAR       ucHtype; /*client��Ӳ����ַ����:1=Ethernet*/
    UCHAR       ucHlen; /*client��Ӳ����ַ����:Ethernet=6*/
    UCHAR       ucHops;
    ULONG       ulXid;
    USHORT      usSecs;
    USHORT      usFlag;
    ULONG       ulCiaddr;
    ULONG       ulYiaddr; /*Server�����client��IP��ַ*/
    ULONG       ulSiaddr;
    ULONG       ulGiaddr; /*���ص�ַ*/
    UCHAR       szChaddr[DHCPS_CHADDR_LEN];/*client��Ӳ����ַ*/
    CHAR        szSname[DHCPS_SNAME_LEN];
    CHAR        szFile[DHCPS_FILE_LEN];
}VOS_PACKED DHCP_S;

/*DHCPS��USM�ӿڵ����ݽṹ����*/
typedef struct tagDHCPS_USM_MSG_S
{
    ULONG ulMsgType;                    /*��Ϣ����*/
    ULONG ulPDPContextIndex;     /*PDP�����ĵ�����������Լ������*/
    ULONG ulAddress;                    /*IP��ַ*/
} DHCPS_USM_MSG_S;

/***************************************************************/
/**************         DHCPV6 ��Ϣ�ṹ��         ***************/
/***************************************************************/

/*�����ȫ����չ���� 1�ֽڶ���*/
#pragma pack(1)
/* DHCPV6��Ϣ�嶨�� */
typedef struct tagDHCPV6C_MSG_S
{
    ULONG  ulMsgTypeBit8:8;  /* ��Ϣ���� */
    ULONG  ulTransIdBit24:24; /* transaction ID */
    UCHAR  ucData[0];    /* options (variable) */
}DHCPV6C_MSG_S;
#pragma pack()

/*******************************************************************************************************/
/********************                        ȫ�ֱ���                           ************************/
/*******************************************************************************************************/

extern ULONG g_ulDhcpDebug;
extern ULONG g_ulDHCPSUSMQueId;
extern ULONG g_ulDhcpServerTaskId ;

/*******************************************************************************************************/
/********************                        ��������                           ************************/
/*******************************************************************************************************/
extern ULONG DHCPC_BackupProc( char **ppbuff, UCHAR ucIpType, ULONG ulTEIDC);
extern ULONG DHCPC_BKRestoreProc( char **ppbuff, UCHAR ucIpType, ULONG ulTEIDC );
//extern ULONG DHCPC_BKDeleteProc( UCHAR ucIpType, ULONG ulTEIDC, UCHAR ucUser, ULONG ulPDPIndex );

#endif /* end of __DHCP_SPU_API_H__ */
