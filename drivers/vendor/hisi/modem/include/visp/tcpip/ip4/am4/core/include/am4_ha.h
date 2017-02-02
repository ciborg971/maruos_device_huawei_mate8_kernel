

#ifndef _AM4_HA_H_
#define _AM4_HA_H_

#ifdef  __cplusplus
extern  "C"{
#endif

#define IP4_CFG_ADD_MAIN_ADDR_BAK          1    /*������������ַ */
#define IP4_CFG_ADD_SEC_ADDR_BAK           2    /*�������ôӵ�ַ */
#define IP4_CFG_DEL_MAIN_ADDR_BAK          3    /*ɾ���ӿڵ�����ַ */
#define IP4_CFG_DEL_SEC_ADDR_BAK           4    /*ɾ�����õĴӵ�ַ */
#define IP4_UNNUMBER_ADDR_BAK              5    /* ���ýӿڵ�ַ��־ */

#define IP4_UNNUMBER_DEL_ADDR_BAK          10   /* ɾ�����ýӿڵ�ַ��־ */
#define IP4_NEGO_ADDR_BAK                  11   /* Э�̵�ַ���ݱ�� */
#define IP4_NEGO_DEL_ADDR_BAK              12   /* ɾ��Э�̵�ַ���ݱ�� */
#define IP_DEL_BAK                         13   /* ��սӿ��ϵĵ�ַ */

#define IP4_TTL_BAK                        21   /* TTLֵ�ı��� */
#define IP4_ICMP_REDIRECTS                 22   /* ICMPֵ���ض��� */
#define IP4_ICMP_HOSTUNREACH               23   /* �������ɴ������ */
#define IP4_FORWARDFLAG_BAK                24   /* ����ת�����ر��� */
#define IP4_HOSTRTRESERVED_BAK             25   /* �ӿ�DOWNʱ����������·�ɱ�� */

/* Begin of HA UPGRADE modification, 2010 December to 2011 January */
#define IP4_HA_MSGID_VRF                   25   /* VRF */
#define IP4_HA_MSGID_VRF_CREATE            26   /* Create VRF */
#define IP4_HA_MSGID_VRF_DELETE            27   /* delete VRF  */
#define IP4_HA_MSGID_INT_BIND_VRF          28   /*  VRF is bind to interface */
#define IP4_HA_MSGID_INT_UNBIND_VRF        29   /* VRF is unbind to interface  */

typedef struct tagIP4_VRF_BAK
{
    USHORT  usType;            /* ������Ϣ������ */
    USHORT  usLen;             /* ������Ϣ����ܳ��� */
    ULONG   ulIfIndex;         /* Interface Index */
    ULONG   ulVrfIndex;        /* VRF Index */
} IP4_VRF_BAK_S;
/* End of HA UPGRADE modification, 2010 December to 2011 January */
        
typedef struct tagIP4_PACKET_HEAD_BAK
{
    USHORT usType;              /* ������Ϣ������ */
    USHORT usLen;              /* ������Ϣ����ܳ��� */
    ULONG  ulIfIndex;          /* ���ÿ������Ľӿ����� */
    ULONG  ulExtend;           /* ��չ�ֶ� */
} IP4_PACKET_HEAD_BAK_S;

typedef struct tagIP4_CFG_PACKET_HEAD_BAK
{
    USHORT  usType;              /* ������Ϣ������ */
    USHORT  usLen;              /* ������Ϣ����ܳ��� */
    ULONG    ulIfIndex;          /* ���ÿ������Ľӿ����� */
    ULONG    ulIpAddr;           /* ���õĵ�ַ*/
    ULONG    ulIpMask;           /* ���õĵ�ַ����*/
} IP4_CFG_PACKET_HEAD_BAK_S;

typedef struct tagIP4_HA_PACKET_TLV
{
    USHORT  usHaMsgType;         /* ������Ϣ������ */
    USHORT  usHaMsgLength;       /* ������Ϣ�ĳ��� */
}IP4_HA_PACKET_TLV_S;

typedef struct tagIP4_HA_HOSTRTRESERVED
{
    ULONG ulIfIndex;             /* Ҫ�ڽӿ�Э��ջDWONʱ��������·�ɵĽӿ����� */
    ULONG ulHostRtReservedFlag;  /* ��������·�ɱ�� */
}IP4_HA_HOSTRTRESERVED_S;

typedef struct tagIP4_UNNUMBER_PACKET_HEAD_BAK
{
    USHORT usType;                /* ������Ϣ������ */
    USHORT  usLen;                /* ������Ϣ����ܳ��� */
    ULONG  ulMyIfIndex;           /* ���ÿ������Ľӿ����� */
    ULONG  ulOtherIfIndex;        /* ���õ�ַ�Ľӿ����� */
} IP4_UNNUMBER_PACKET_HEAD_BAK_S;

typedef enum tagIP4_HA_OPTTYPE
{
    IP4_HA_OPTTYPE_BASE = 0,             /* �������ݵı��� */
    IP4_HA_OPTTYPE_TLV,                  /* ��TLV��ʽ������� */
    IP4_HA_OPTTYPE_END
}IP4_HA_OPTTYPE_E;

#ifndef AM4_MAX_ONE_BAK_SIZE
#define AM4_MAX_ONE_BAK_SIZE \
             (sizeof(IP4_UNNUMBER_PACKET_HEAD_BAK_S))
#endif


ULONG IP_HA_BatchBackup();
ULONG IP_HA_PP4Batchup(ULONG ulCount);
ULONG IP_HA_BuildOnePacket(USHORT usType, ULONG ulIfIndex, UCHAR * pucData, UCHAR *pucInBuf, USHORT usInBufLen);
ULONG IP_HA_BatchBackupSendPacket(UCHAR * pucData, USHORT usDataLen, ULONG ulCount, UCHAR ucOperation);
ULONG IP_HA_Input(UCHAR * pucBuf, ULONG ulMsgLen);
ULONG IP_HA_BuildSendOnePacket(USHORT usType, ULONG ulIfIndex, UCHAR * pucData,
    USHORT usInBufLen, UCHAR ucOperation);
ULONG IP_HA_SendPacket(UCHAR * pucData, USHORT usDataLen);
ULONG TCPIP_HA_SetIpDbg(ULONG ulDbg);
ULONG IP_HA_GetIpDbg(ULONG *pulDbg);
ULONG IP_HA_Smooth();
VOID IP_HA_DebugOutPut(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd);
ULONG IP_HA_SetIpVerboseDbg(ULONG ulDbg);
ULONG IP_HA_GetIpVerboseDbg (ULONG *pulDbg);
ULONG IP_HA_BatchBackup_TLV(ULONG ulCount);

#ifdef  __cplusplus
}
#endif

#endif

