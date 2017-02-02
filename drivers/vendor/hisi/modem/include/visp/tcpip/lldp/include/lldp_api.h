
#ifndef _LLDP_API_H_
#define _LLDP_API_H_

#ifdef  __cplusplus
extern "C"{
#endif

/*****ȫ��������Ϣ*****/
typedef struct tagLLDP_GLOBAL_CFG_S
{
    ULONG  ulTxInterval;            /* LLDP���ķ��ͼ�� */
    ULONG  ulTxHoldMultiplier;      /* TTL����  */
    ULONG  ulReinitDelay;           /* ��ʼ����ʱ */
    ULONG  ulFastTxPktNum;          /* FASTģʽ���䱨�ĸ���*/
    ULONG  ulMsgFastTx;             /* FASTģʽ���ķ���ʱ����*/
} LLDP_GLOBAL_CFG_S; 

/******* Class ID TLV  *******/
#define LLDP_MAC_ADDR_LEN      6    /*physical��ַ�ĳ���*/
#define LLDP_STR_LEN_256       256  /*256���ַ�����*/
typedef struct tagLLDP_CHASSISID_INFO_S
{
    UCHAR  ucChassisIdSubtype; /* ChassisId���ͣ�ȡֵ��Χ��1~7��
                                        chassisComponent(1),   
                                        interfaceAlias(2),     
                                        portComponent(3),      
                                        macAddress(4),         
                                        networkAddress(5),     
                                        interfaceName(6),      
                                        local(7)  */
    UCHAR  ucChassisIdLen;                  /* Chassis Id��Ч����  */
    UCHAR  ucRes[2];                         /*����ֶΣ���֤�ṹ��4���ֽڶ���*/               
    CHAR   szChassisId[LLDP_STR_LEN_256];   /* ChassisId��ȡֵ��Χ���ַ���1~255��  */
}LLDP_CHASSISID_INFO_S; 

/******* Management Address TLV  *******/
#define LLDP_STR_LEN_32  32     /*32���ַ�����*/
typedef struct tagLLDP_MANAGEMENT_INFO_S
{
    ULONG  ulManAddrSubtype;    /*�����ַ���ͣ�ȡֵ��IPv4��1�� */
    CHAR   szManAddr[LLDP_STR_LEN_32];       /* Management Address TLV�еĹ����ַ*/
    ULONG  ulManAddrIfSubtype;  /*�����ַ���ڽӿ����ͣ�Ĭ��unknown(1)
                                            unknown(1)
                                            ifIndex(2)
                                            systemPortNumber(3) */
    ULONG  ulManAddrIfId;       /*�����ַ���ڽӿ�ID��Ĭ��0 */
}LLDP_MANAGEMENT_INFO_S;

/******* system name TLV  *******/
typedef struct tagLLDP_SYS_NAME_INFO_S
{
    CHAR   szSysName[LLDP_STR_LEN_256];       /*system name TLV , ����ϵͳ���ƣ�Ĭ��ֵ"System" */
}LLDP_SYS_NAME_INFO_S; 

/******* system description TLV *******/
typedef struct tagLLDP_SYS_DESC_INFO_S
{
    CHAR   szSysDesc[LLDP_STR_LEN_256];       /* system description TLV,����ϵͳ������Ĭ��ֵ"System" */
}LLDP_SYS_DESC_INFO_S;

#define LLDP_SYS_CAP_BIT_LEN 16              /*����ϵͳ֧�ֵĹ���λ�����ֽڵı���λ*/
/* system Capabilities TLV */
typedef struct tagLLDP_SYS_CAPABILITY_INFO_S
{

    USHORT usSysCapSupported;     /* ����ϵͳ֧�ֵĹ��ܣ�BITS��*/
    USHORT usSysCapEnabled;       /* ����ϵͳ�����Ĺ��ܣ�ͬ�� */    
}LLDP_SYS_CAPABILITY_INFO_S;

/*Management VID TLV*/
typedef struct tagLLDP_MANAGEMENT_VID_INFO_S
{
    USHORT usManagementVid;       /*����Management VID��Ϣ*/
    UCHAR ucRes[2];                /*����ֶΣ���֤�ṹ��4���ֽڶ���*/  
} LLDP_MANAGEMENT_VID_INFO_S;


/*�����ⲿ���õı���ϵͳ��Ϣ������ϵͳ���ƣ�ϵͳ����*/
typedef struct tagLLDP_CFG_SYS_NAME_DESC_S
{
    LLDP_SYS_NAME_INFO_S stSysName;        /* ����ϵͳ���ƣ�Ĭ��ֵ"System" */
    LLDP_SYS_DESC_INFO_S stSysDesc;        /* ����ϵͳ������Ĭ��ֵ"System" */
}LLDP_CFG_SYS_NAME_DESC_S;

/*�����ⲿ��ѯ������ChassisId��ϵͳ���ƣ�ϵͳ�����������ַ��Ϣ������ϵͳ����*/
typedef struct tagLLDP_SYS_INFO_S
{
    LLDP_SYS_NAME_INFO_S stSysName;        /* ����ϵͳ���ƣ�Ĭ��ֵ"System" */
    LLDP_SYS_DESC_INFO_S stSysDesc;        /* ����ϵͳ������Ĭ��ֵ"System" */
    LLDP_MANAGEMENT_INFO_S stManagement;  /*�����ַTLV��Ϣ*/
    LLDP_SYS_CAPABILITY_INFO_S stSysCapability;  /*system Capabilities TLV��Ϣ*/
    LLDP_MANAGEMENT_VID_INFO_S stManagementVid;  /*Management VID TLV*/
}LLDP_SYS_INFO_S;


/******* Port Description TLV  *******/
typedef struct tagLLDP_PORT_DESC_INFO_S
{
    CHAR   szPortDesc[LLDP_STR_LEN_256];     /* Port Description���� */
}LLDP_PORT_DESC_INFO_S;

/* Port And Protocol VLAN ID TLV */
typedef struct tagLLDP_PPVID_INFO_S
{
    USHORT usPpvid;     /* PPVID���� */
    UCHAR ucFlags;      /*��ʾ�ֶ�*/
    UCHAR ucResv[1];    /*����ֶΣ���֤�ṹ��4���ֽڶ���*/  
}LLDP_PPVID_INFO_S;

/*Port ID TLV*/
typedef struct tagLLDP_PORTID_INFO_S
{
    UCHAR  ucPortIdSubtype;     /* PortId���ͣ���ǰ��֧��
                                    LLDP_PORTID_MAC_ADDRESS(3)
                                    LLDP_PORTID_INTERFACE_NAME(5)
                                  */
    UCHAR ucResv[3];    /*����ֶΣ���֤�ṹ��4���ֽڶ���*/  
    CHAR   szPortId[LLDP_STR_LEN_256];   /* PortId���̶�physical��ַ  */
}LLDP_PORTID_INFO_S;


/*Link Aggregation TLV*/
typedef struct tagLLDP_LINK_AGG_INFO_S
{
    UCHAR ucLinkAggCapStatus;      /* ��·�ۺ�������״̬
                                                ��0bitλ��ʾ������1bitλ��ʾ״̬�� */
    UCHAR ucResv[3];                /*����ֶΣ���֤�ṹ��4���ֽڶ���*/  
    ULONG ulLinkAggPortID;         /* ��·�ۺ�ID */
}LLDP_LINK_AGG_INFO_S; 

/***Power Via MDI TLV***/
typedef struct tagLLDP_POWER_VIA_MDI_INFO_S
{
    UCHAR ucMdiPowerSupport;         /* MDI Power Support */
    UCHAR ucPsePowerPair;            /* PSE Power Pair*/
    UCHAR ucPowerClass;              /* Power Class       */
    UCHAR ucResv[1];                 /*����ֶΣ���֤�ṹ��4���ֽڶ���*/  
}LLDP_POWER_VIA_MDI_INFO_S;

/*Port VLAN ID TLV*/
typedef struct tagLLDP_PVID_INFO_S
{
    USHORT usPvid;     /* PVID���� */
    UCHAR ucResv[2];   /*����ֶΣ���֤�ṹ��4���ֽڶ���*/  
}LLDP_PVID_INFO_S; 


/***** MAC/PHY Configuration/Status TLV *****/
typedef struct tagLLDP_MAC_PHY_CFG_INFO_S
{
    UCHAR ucLinkAutoNegoCapStatus; /* ��·��Э�������͹���״̬
                                    ��0bitλ��ʾ������1bitλ��ʾ����״̬�� */
    UCHAR ucResv[3];                 /*����ֶΣ���֤�ṹ��4���ֽڶ���*/  
    USHORT usLinkPmdAutoNegoCap;   /* ��·PMD��Э������ */
    USHORT usLinkOperMauType;      /* ��·MAU�������� */
}LLDP_MAC_PHY_CFG_INFO_S; 


/* Maximum Frame Size TLV */
typedef struct tagLLDP_MAX_FRAME_SIZE_INFO_S
{
    USHORT usMaxFrameSize;        /* Maximum Frame Size TLV֧�ֵ�Maximum Frame Size��Ϣ */
    CHAR ucResv[2];                /*����ֶΣ���֤�ṹ��4���ֽڶ���*/  
}LLDP_MAX_FRAME_SIZE_INFO_S;

#define LLDP_MAX_VLAN_NAME_TLV_NUM 32  /*ÿ���ӿ������32��VLAN NAME TLV*/
/*Vlan Name TLV��Ϣ*/
typedef struct tagLLDP_VLAN_NAME_INFO_S
{
    USHORT usVlanId;               /*Vlan ID*/
    UCHAR ucNameLen;               /*Vlan Name����*/
    UCHAR ucRes;                   /*����ֶΣ���֤�ṹ��4���ֽڶ���*/
    UCHAR ucVlanName[32];          /*Vlan Name*/
} LLDP_VLAN_NAME_INFO_S;

typedef struct tagLLDP_CFG_PORT_INFO_S
{
    LLDP_PORTID_INFO_S  stPortId;      /* Port ID TLV */
    LLDP_PORT_DESC_INFO_S stPortDesc;  /* Port Description TLV */
}LLDP_CFG_PORT_INFO_S;

/*�ھӽڵ��ѯ�Ĺ�������*/
typedef struct tagLLDP_REM_FILTER_S
{
    ULONG  ulPortIfIndex;         /* Remote���ڶ˿ڵı��*/
    ULONG  ulDestAddrGroup;       /* Remote�����鲥��ı�ţ� 
                                                    DestMac��Nearest bridge ��1��
                                                    DestMac��Nearest non-TPMR bridge��2��
                                                    DestMac��Nearest Customer Bridge��3��
                                                    �ù���������Ҫ�������Remote���һ��ʹ��*/
    ULONG  ulRemIndex;            /* Remote��ţ�ȡֵ��Χ��1~7FFFFFFF��*/
}LLDP_REM_FILTER_S;

/**�ھӲ�ѯʱ��ͨ��LLDP_RemTableGet()������ȡ���ھӽڵ㣬���ھӱ��е�����**/
typedef struct tagLLDP_REM_INDEX_S
{
    ULONG  ulPortPos;   /*�α굱ǰ���ڽӿ������е�����*/
    ULONG  ulMacPos;    /*�α굱ǰ���ڵ��鲥��ַ(Agent)*/
    ULONG  ulRemPos;    /*�α굱ǰ����Agent���ھӱ������*/
}LLDP_REM_INDEX_S;

/***  �ھӽڵ���Ϣ***/
#define LLDP_MAX_PPVID_TLV_NUM  16  /*ÿ���ӿ������16��Port And Protocol VLAN ID TLV*/

/*�ⲿ�ھӲ�ѯ�õ��ھӽڵ�*/
typedef struct tagLLDP_REM_INFO_S
{    
    ULONG  ulDestAddrIndex;       /* Remote�����鲥��ı�ţ�ȡֵ��Χ��1~3��
                                            DestMac��01:80:c2:00:00:0e��1��
                                            DestMac��01:80:c2:00:00:03��2��
                                            DestMac��01:80:c2:00:00:00��3��*/
    ULONG  ulRemIndex;            /* Remote��ţ�ȡֵ��Χ��1~7FFFFFFF��*/
    ULONG  ulRemTimeMark;         /* Remote�ϴα�������ڵ�ʱ�䣨��λ���룩 */
    ULONG  ulRemExpireTime;       /* Remote��ʱʱ�䣬ȡ��TTL TLV����λ���룩 */
    ULONG  ulTlvValidFlag;        /* Remote Я���Ŀ�ѡTLV��Ч��־��bit��ʶ��
                                    ChassisId, PortId, Management����Я������ռ�ñ�ʶλ
                                      0-  System Name TLV
                                      1-  System Description TLV 
                                      2-  System Capability TLV
                                      3-  Port Description TLV
                                      4-  Management Address TLV
                                      5-  MAC/PHY Configuration/Status TLV
                                      6-  Port Vlan Id TLV
                                      7-  Max Frame Size TLV
                                      8-  Link Aggregation TLV
                                      9-  Power Via Mdi TLV
                                      10- Port and Protocol Vlan ID TLV
                                      11- Vlan Name TLV
                                      12- Management VID TLV*/    
    ULONG  ulPpvidNum;            /* Port and Protocol Vlan ID TLV ����*/
    UCHAR ucVlanNameNum;/* Vlan Name TLV ����*/
    UCHAR ucRes[3];
    LLDP_CHASSISID_INFO_S stRemChassisId; /* Remote ChassisId TLV*/     
    LLDP_PORTID_INFO_S  stRemPortId; /* Remote PortId TLV */ 
    LLDP_MANAGEMENT_INFO_S stRemManagement; /*�����ַTLV*/ 
    LLDP_SYS_NAME_INFO_S stRemSysName;        /* ����ϵͳ���ƣ�Ĭ��ֵ"System" */
    LLDP_SYS_DESC_INFO_S stRemSysDesc;        /* ����ϵͳ������Ĭ��ֵ"System" */
    LLDP_SYS_CAPABILITY_INFO_S stRemSysCapability;  /*ϵͳ����TLV*/
    LLDP_PORT_DESC_INFO_S stRemPortDesc;      /* Port Description TLV */
    LLDP_MAC_PHY_CFG_INFO_S stRemPhyCfgStatus;/* MAC/PHY Configuration/Status TLV */
    LLDP_PVID_INFO_S stRemPortVlanId;   /*Port Vlan Id TLV*/
    LLDP_MANAGEMENT_VID_INFO_S stRemManagementVid; /* Management VID TLV */
    LLDP_MAX_FRAME_SIZE_INFO_S stRemMaxFrameSize;   /*Max Frame Size TLV */
    LLDP_LINK_AGG_INFO_S stLinkAgg; /* Link Aggregation TLV */
    LLDP_VLAN_NAME_INFO_S stRemVlanName[LLDP_MAX_VLAN_NAME_TLV_NUM]; /* Vlan Name TLV */
    LLDP_PPVID_INFO_S stPpvid[LLDP_MAX_PPVID_TLV_NUM]; /* Port And Protocol VLAN ID TLV */

}LLDP_REM_INFO_S; 

/*ϵͳͳ����Ϣ*/
typedef struct tagLLDP_SYS_STAT_S
{
    ULONG  ulRemTablesLastChangeTime; /* Remote�����һ���޸�ʱ�� */
    ULONG  ulRemTablesInserts;        /* Remote���������������� */
    ULONG  ulRemTablesDeletes;        /* Remote��ɾ������ */
    ULONG  ulRemTablesDrops;          /* Remote�����ڵ���� */
    ULONG  ulRemTablesAgeouts;        /* Remote��ʱ���� */
    ULONG  ulRemTablesUpdates;        /* Remote����¸��� */
}LLDP_SYS_STAT_S; 

/*�ӿ�ÿ��Agent(��Ӧ��һ���鲥��ַ)�ϵ�ͳ����Ϣ*/
typedef struct tagLLDP_PORT_STAT_S
{
    ULONG  ulRxFramesTotal;             /* �յ���LLDP ֡���� */
    ULONG  ulRxDiscardedTotal;          /* ������LLDP ֡���� */
    ULONG  ulRxErrorsTotal;             /* �յ��Ĵ���LLDP ֡���� */
    ULONG  ulRxTLVsDiscardedTotal;      /* ������LLDP TLV ֡���� */
    ULONG  ulRxTLVsUnrecognizedTotal;   /* ����ʶ���LLDP TLV ֡���� */
    ULONG  ulTxFramesTotal;             /* ���͵�LLDP ֡���� */
    ULONG  ulRxAgeoutsTotal;            /* �ϻ���LLDP �ھ���Ϣ���� */
}LLDP_PORT_STAT_S; 


/*�ھӽڵ��ѯ�Ĺ�������*/
/*Remote �����鲥��ı�ţ���3���鲥��ַ��Ĭ��ΪNearest bridg(1)*/
#define LLDP_NEAREST_BRIDGE             1
#define LLDP_NEAREST_NON_TPMR_BRIDGE    2
#define LLDP_NEAREST_CUSTOMER_BRIDGE    3

/*�ھӲ�ѯ��������Remote��ţ�ȡֵ��Χ��1~7FFFFFFF��*/
#define LLDP_REMINDEX_MIN    1
#define LLDP_REMINDEX_MAX    0x7FFFFFFF


/*LLDP CBB������*/
#define LLDP_OK                              VOS_OK
#define LLDP_ERR                             VOS_ERR
#define LLDP_ERR_NO_SUCH_FUNC                2       /*�޸ú�������*/
#define LLDP_ERR_INVALID_PARA                3       /*API������Ч��Ƿ�*/
#define LLDP_ERR_PORT_NUM_ZERO               4       /*���ؽӿ�����Ϊ0*/
#define LLDP_ERR_PORT_NOT_EXIST              5       /*PORT�����ڣ����PORTδʹ��LLDP*/
#define LLDP_ERR_INVALID_IF_INDEX            6       /*�ӿ�������Ч*/
#define LLDP_ERR_MALLOC_FAIL                 7       /*�ڴ�����ʧ��*/
#define LLDP_ERR_TABLE_END                   8       /*����Ϊ��*/
#define LLDP_ERR_NOSPACEFORTLV               9       /*��װTLV�Ŀռ䲻��*/
#define LLDP_ERR_PORT_MODE_REPEATED          10      /*�ظ����ýӿ�ģʽ*/
#define LLDP_ERR_CHASSISID_SUBTYPE_INVALID   11      /*����ChassisIdSubType��Ч*/
#define LLDP_ERR_CHASSISID_INVALID           12      /*����ChassisId��Ч(����/ֵ)*/
#define LLDP_ERR_MAN_ADDR_SUBTYPE_INVALID    13      /*����ManAddrSubtype��Ч*/
#define LLDP_ERR_MAN_ADDR_INVALID            14      /*����ManAddr��Ч*/
#define LLDP_ERR_MAN_ADDR_IF_SUBTYPE_INVALID 15      /*����ManAddrIfSubtype��Ч*/
#define LLDP_ERR_MAN_ADDR_IF_ID_INVALID      16      /*����ManAddrIfId��Ч*/
#define LLDP_ERR_LOCAL_SYS_NAME_INVALID      17      /*����LocSysName��Ч*/
#define LLDP_ERR_LOCAL_SYS_DESC_INVALID      18      /*����LocSysDesc��Ч*/
#define LLDP_ERR_LLDP_NOT_INIT               19      /*LLDPδ��ʼ��*/
#define LLDP_ERR_IF_NOT_SUPPORT              20      /*����̫�ӿ�,LLDP��֧��*/
#define LLDP_ERR_PPI_NOT_CONFIG              21      /*LLDP PPIδע��*/
#define LLDP_ERR_PPI_UPDATE_FUN_NOT_CFG      22      /*�ӿ�ģʽ����PPIδע��*/
#define LLDP_ERR_INVALID_PARA_VALUE          23      /*API����ֵ��Ч*/
#define LLDP_ERR_PPVID_IS_FULL               24      /*PPVID�ﵽ������*/
#define LLDP_ERR_PPVID_NOT_EXIST             25      /*PPVID������*/
#define LLDP_ERR_PORT_DESC_INVALID           26      /*����Port Desc������Ч*/
#define LLDP_ERR_VLAN_NAME_NUM_LARGE         27      /*����VLAN NAME TLV����̫��*/
#define LLDP_ERR_VLAN_NAME_EXIST             28      /*VLAN NAME TLV�Ѵ���*/
#define LLDP_ERR_VLAN_NAME_NOEXIST           29      /*VLAN NAME TLV������*/
#define LLDP_ERR_VLAN_NAME_LENGTH            30      /*VLAN NAME ���ȴ���*/
#define LLDP_ERR_MANAGE_VID_TPYE             31      /*Management Vid ���ʹ���*/
#define LLDP_ERR_SYSCAP_INVALID              32      /*SysCap����*/
#define LLDP_ERR_PORTID_INVALID              33      /*PortID����*/
#define LLDP_ERR_PORTDESC_LEN                34      /*Port Desc���ȴ���*/
#define LLDP_ERR_PORTID_LEN                  35      /*Port ID���ȴ���*/
#define LLDP_ERR_MACPHY_INVALID              36      /*MacPhy tlv����*/
#define LLDP_ERR_LINKAGG_INVALID             37      /*LinkAgg tlv����*/
#define LLDP_ERR_VLAN_NAME_DUPLATE           38      /*VLAN NAME TLV�ظ�����*/
#define LLDP_ERR_OPERATE_INVALID             39      /*�������������ȡֵ���Ϸ�*/
#define LLDP_ERR_PVID_INVALID                40      /*ɾ����PortVlanIdֵ������*/
#define LLDP_ERR_DELETE_PVID_IS_ZERO         41      /*ɾ����PortVlanIdֵ����Ϊ0*/
#define LLDP_ERR_MANAGEVID_NOEXIST           42      /*ɾ��MANAGEVID������ */
#define LLDP_ERR_LINKAGG_NOEXIST             43      /*ɾ��LinkAgg tlv������*/
#define LLDP_ERR_MANAGEMENT_NOEXIST          44      /*ɾ��MANAGEMENT������ */
#define LLDP_ERR_GETEXTTLV_FUN_NOT_CFG       45      /*��ȡ��Ʒ�Զ���TLV���Ӻ���δע��*/
#define LLDP_ERR_INPUTHOOK_FUN_NOT_CFG       45      /*����LLDP���Ĺ��Ӻ���δע��*/


/*�жϽӿ������Ƿ�Ϊ0�����жϲ�ѯ���Ľӿ��Ƿ����*/
#define LLDP_VALID_IF_INDEX(ulIfIndex)  \
  (ulIfIndex) != (0)

/*�ϱ�LLDP�澯��Ϣ������*/
#define LLDP_WARNING_INSERT    1    /*�ھӽڵ����*/
#define LLDP_WARNING_UPDATE    2    /*�ھӽڵ����*/
#define LLDP_WARNING_DELETE    3    /*�ھӽڵ�ɾ��*/
#define LLDP_WARNING_DROP      4    /*�ھӱ�ﵽ������ֵ�������յ������ھӵı���*/
#define LLDP_WARNING_AGEOUT    5    /*�ھӽڵ��ϻ�ɾ��*/

/*�ӿ��ϱ�������*/
#define LLDP_IF_CMD_CREATE        1    /*�ӿڴ���*/
#define LLDP_IF_CMD_DEL           2    /*�ӿ�ɾ��*/
#define LLDP_IF_CMD_UP            3    /*�ӿ�����*/ 
#define LLDP_IF_CMD_DOWN          4    /*�ӿڹر�*/ 
#define LLDP_IF_CMD_MTU           5    /*�ϱ�MTU�仯*/
#define LLDP_IF_CMD_MAC           6    /*�ϱ�physical��ַ����*/


/*�ӿ�Agent����ģʽ*/
#define LLDP_PORT_MODE_DISABLE     0    /*�Ȳ��ܷ���LLDP���ģ�Ҳ���ܽ��ձ���*/
#define LLDP_PORT_MODE_TX          1    /*ֻ�����ͱ���*/
#define LLDP_PORT_MODE_RX          2    /*ֻ�ܽ��ձ���*/
#define LLDP_PORT_MODE_TXRX        3    /*���ܷ���LLDP���ģ����ܽ��ձ���*/

/*����/ɾ��LLDP�ӿ�Port Desc TLV��Ϣ�����֣�1--��ӣ�0--ɾ��*/
#define LLDP_CREATE            1
#define LLDP_DELETE            0

#define LLDP_PORT_STATUS_UP    1
#define LLDP_PORT_STATUS_DOWN  2

/*LLDP�ϱ��ĸ澯��Ϣ*/
typedef struct tagLLDP_REMOTE_TABLE_WARNING_S
{
    ULONG  ulWarningType;         /* �澯�����ͣ�
                                      LLDP_WARNING_INSERT    1
                                      LLDP_WARNING_UPDATE    2
                                      LLDP_WARNING_DELETE    3
                                      LLDP_WARNING_DROP      4
                                      LLDP_WARNING_AGEOUT    5*/
    ULONG  ulPortIfIndex;         /* Remote���ڶ˿ڵı��*/
    ULONG  ulDestAddrIndex;       /* Remote�����鲥��ı��
                                      DestMac��01:80:c2:00:00:0e��1��
                                      DestMac��01:80:c2:00:00:03��2��
                                      DestMac��01:80:c2:00:00:00��3��*/
    ULONG  ulRemIndex;            /* Remote��ţ�ȡֵ��Χ��1~7FFFFFFF��*/
    LLDP_REM_INFO_S *pstRemoteInfo; /* ���� �ھӵ�������Ϣ  �ɸ�����Ʒ���л�ȡ��Ҫ����Ϣ   
                                    ����ṹ�Ƚϴ���2608�ֽڣ�����ָ�룬���ΪNULL����ʾ�ڴ�����Ѿ�ʧ��*/
}LLDP_REMOTE_TABLE_WARNING_S; 

/* Ŀǰ֧�������ಥ��ַ */
#define LLDP_MAX_MACTYPE_SIZE  3

/*�ⲿ��ѯ�ͻ�ȡLLDP�ӿ���Ϣ*/
typedef struct tagLLDP_PORT_INFO_S
{
    ULONG  ulPortMode[LLDP_MAX_MACTYPE_SIZE];   /* LLDP�ӿ�ģʽ�� Tx��Rx��TxRx��Disable */

    USHORT usPktVLanId; /*����ͷ��Vlan Tag��ID, ����Port Vlan ID TLV��Ϣ.*/
    USHORT usPktVLanPri; /*����ͷ��Vlan Tag�����ȼ�, ����Port Vlan ID TLV��Ϣ.*/
        
    LLDP_PORTID_INFO_S  stPortId;   /*Port ID TLV*/
    LLDP_PORT_DESC_INFO_S stPortDesc;   /* Port Description���� */
    LLDP_PVID_INFO_S stPortVlanId;  /*Port VLAN ID*/
    LLDP_MAC_PHY_CFG_INFO_S stMacPhyCfg;    /*��·��Э������*/
    LLDP_MAX_FRAME_SIZE_INFO_S stMaxFrameSize;  /*MTU*/
    LLDP_LINK_AGG_INFO_S stLinkAgg;     /*Link Aggregation */
    LLDP_VLAN_NAME_INFO_S stVlanName[LLDP_MAX_VLAN_NAME_TLV_NUM];  /*LLDP Vlan Name��Ϣ*/
    LLDP_CHASSISID_INFO_S stChassisId;
}LLDP_PORT_INFO_S;

/* LLDP Debug���Կ��ر�־*/
#define LLDP_DEBUG_TX_PKT  0x01 /* ����bit���أ����ķ���*/
#define LLDP_DEBUG_RX_PKT  0x02 /* ����bit���أ����Ľ���*/
#define LLDP_DEBUG_TX_FSM  0x04 /* ����bit���أ�����״̬��*/
#define LLDP_DEBUG_RX_FSM  0x08 /* ����bit���أ�����״̬��*/
#define LLDP_DEBUG_TR_FSM  0x10 /* ����bit���أ�����timer״̬��*/
#define LLDP_DEBUG_ADD_REM 0x20 /* ����bit���أ��ھ�����*/
#define LLDP_DEBUG_UPD_REM 0x40 /* ����bit���أ��ھӸ���*/
#define LLDP_DEBUG_DEL_REM 0x80 /* ����bit���أ��ھ�ɾ��*/
#define LLDP_DEBUG_RX_ALL_PKT  0x100 /* ����bit���أ����Ľ��մ�ӡ���б��İ�����lldp����*/
#define LLDP_DEBUG_ALL     0xffff /* ����bit���أ�ȫ����*/

/*LLDP  PPI��Ϣ���ݽṹ��*/
typedef struct tagLLDP_PPI_UPDATE_S
{
    ULONG ulIfIndex;         /* �ӿ����� */
    ULONG ulDestAddrGroup;  /*Ŀ���鲥��ı��
                                Nearest bridge              1
                                Nearest non-TPMR bridge     2
                                Nearest Customer Bridge     3*/
}LLDP_PPI_UPDATE_S;

/*PPIע�ắ������TRANע�ᣬVISP���ʵ���ʱ����øú�����������Ϣ֪ͨTRAN*/
typedef struct tabLLDP_PPI_HOOK
{
    /*LLDPģʽ����*/
    ULONG (*pfLLDP_PPI_Mode_Update)(ULONG ulOperType, LLDP_PPI_UPDATE_S *pstLldpUpdateMsg);
}LLDP_PPI_HOOK_S;

/* ��Ʒ�ص�����ȡ�Զ���TLV */
typedef struct tagLLDP_GETEXTTLV
{
	ULONG  ulIfIndex;      /*�ӿ�����*/
	ULONG  ulDestAddrGroup;/*[1,3]
                           Nearest bridge 1
                           Nearest non-TPMR bridge 2
                           Nearest Customer Bridge 3
                           
                           Ĭ��Ϊ��1 Nearest Bridge
                           */
	ULONG  ulRemTlvLen;    /*��չTLV���Է�װ����󳤶�*/
	ULONG  ulExtTlvLen;    /*��������ص���չTLV�ĳ��ȣ����Ϊ0�򲻷�װ�Զ���TLV*/
	CHAR * pExtTlv;        /*��������ص���չTLV*/
}LLDP_GETEXTTLV_S;

/* ��Ʒע�ắ������ȡ�Զ���TLV */
typedef ULONG (*LLDP_GETEXTTLV_HOOK_FUNC)(LLDP_GETEXTTLV_S *pstData);

/* ���յ���LLDP�������͸���Ʒ */
typedef struct tagLLDP_INPUT
{
	ULONG  ulIfIndex;      /*�ӿ�����*/
	ULONG  ulDestAddrGroup;/*[1,3]
                           Nearest bridge 1
                           Nearest non-TPMR bridge 2
                           Nearest Customer Bridge 3
                           
                           Ĭ��Ϊ��1 Nearest Bridge
                           */
    ULONG  ulPktLen;       /* �յ���LLDP���ĳ��� */
	CHAR * pRcvPacket;     /*�յ��ı���*/
}LLDP_INPUT_S;

/* LLDP�հ�����ԭ�� */
typedef ULONG (*LLDP_INPUT_HOOK_FUNC)(LLDP_INPUT_S *pstData);

/*******************************************************************************
*    Func Name: LLDP_CfgTxInterval
* Date Created: 2011-09-27
*       Author: limin00188004
*  Description:  ����LLDP���ķ��ͼ���ӿ�
*        Input: ULONG ulTxInterval: LLDP���ķ��ͼ��
*       Output: 
*       Return: LLDP_OK, LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-27   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_CfgTxInterval(ULONG ulTxInterval);


ULONG LLDP_CfgMsgFastTx(ULONG ulMsgFastTx);

/*******************************************************************************
*    Func Name: LLDP_CfgTxHoldMultiplier
* Date Created: 2011-09-27
*       Author: limin00188004
*  Description:  ����TTL����
*        Input: ULONG ulTxHoldMultiplier: TTL��������������TTL.
*                        TTL(Time to live TLV) = min(65535, (LLDP���ķ��ͼ�� * TTL����))
*       Output:  
*       Return:  LLDP_OK, LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-27   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_CfgTxHoldMultiplier(ULONG ulTxHoldMultiplier);

/*******************************************************************************
*    Func Name: LLDP_CfgReinitDelay
* Date Created: 2011-09-27
*       Author: limin00188004
*  Description:  �����س�ʼ����ʱ�ӿ�
*        Input: ULONG ulReinitDelay: ��ʼ����ʱʱ��
*       Output: 
*       Return: LLDP_OK, LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-27   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_CfgReinitDelay(ULONG ulReinitDelay);

/*******************************************************************************
*    Func Name: LLDP_CfgFastTxPacketNum
* Date Created: 2011-09-27
*       Author: limin00188004
*  Description: ����FASTģʽ���䱨�ĸ���
*        Input: ULONG ulPacketNum: FASTģʽ���䱨�ĸ���
*       Output: 
*       Return: LLDP_OK, LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-27   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_CfgFastTxPacketNum(ULONG ulPacketNum);

/*******************************************************************************
*    Func Name: LLDP_CfgPortMode
* Date Created: 2011-09-28
*       Author: limin00188004
*  Description:  ����LLDP�ӿ�ģʽ��֧��Tx��Rx��TxRx��Disable
*        Input: ULONG ulIfIndex: ʹ��LLDP�Ľӿ�����
*               ULONG ulPortMode:�ӿ�ģʽ��ȡֵ��Χ��1~4��
*                                               LLDP_ADMIN_STATUS_TX               1
*                                               LLDP_ADMIN_STATUS_RX               2
*                                               LLDP_ADMIN_STATUS_TXRX           3
*                                               LLDP_ADMIN_STATUS_DISABLE      4
*               ULONG ulDestAddrGroup: Ŀ���鲥��ı�ţ�Ĭ��ΪNearest bridg(1)
*                                               Nearest bridge                           1
*                                               Nearest non-TPMR bridge          2
*                                               Nearest Customer Bridge           3
*       Output: 
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_IF_NOT_SUPPORT,LLDP_ERR_INVALID_PARA,
*               LLDP_ERR_PORT_NOT_EXIST,LLDP_ERR_PORT_MODE_REPEATED
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-28   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_CfgPortMode(ULONG ulIfIndex, ULONG ulPortMode, ULONG ulDestAddrGroup);

/*******************************************************************************
*    Func Name: LLDP_CfgIfVlan
* Date Created: 2011-10-20
*       Author: zhangliangzhi00187023
*  Description: ����LLDP�ӿ�Vlan ID.
*        Input: ULONG ulIfIndex: �ӿ�����
*               ULONG ulVlanId: Vlan ID��ȡֵ��Χ��0��4094��Ĭ��ֵ��0��
*       Output: 
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_IF_NOT_SUPPORT,LLDP_ERR_INVALID_PARA,
*           LLDP_ERR_PORT_NOT_EXIST
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-20   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgIfVlan(ULONG ulIfIndex, USHORT usVlanId, USHORT usPri);

/*******************************************************************************
*    Func Name: LLDP_DisableAllPort
* Date Created: 2011-10-21
*       Author: zhangliangzhi00187023
*  Description: ��ϵͳ�����п���LLDP�ӿڵ�ģʽ��ΪDISABLE
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-21   zhangliangzhi00187023   Create
*
*******************************************************************************/
VOID LLDP_DisableAllPort(VOID);

/*******************************************************************************
*    Func Name: LLDP_CfgSysNameAndDescInfo
* Date Created: 2012-10-17
*       Author: zhangliangzhi00187023
*  Description: ����ϵͳ���ƺ�ϵͳ����
*        Input: LLDP_CFG_SYS_NAME_DESC_S *pstSysNameDesc:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-10-17   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgSysNameAndDescInfo(LLDP_CFG_SYS_NAME_DESC_S *pstSysNameDesc);


/*******************************************************************************
*    Func Name: LLDP_GetGlobalConfig
* Date Created: 2011-09-30
*       Author: limin00188004
*  Description: ��ȡLLDPȫ��������Ϣ��
*        Input: 
*       Output: LLDP_GLOBAL_CFG_S *pstGlobalConfig: LLDPȫ��������Ϣ
*               ����LLDP���ķ��ͼ����TTL��������ʼ����ʱ��FASTģʽ���䱨�ĸ�����
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-30   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_GetGlobalConfig(LLDP_GLOBAL_CFG_S *pstGlobalConfig);

/*******************************************************************************
*    Func Name: LLDP_ShowGlobalConfig
* Date Created: 2011-10-09
*       Author: guo00178934
*  Description: ��ʾLLDPȫ��������Ϣ��
*               ����LLDP���ķ��ͼ����TTL��������ʼ����ʱ��FASTģʽ���䱨�ĸ�����
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-09   guo00178934             Create
*
*******************************************************************************/
VOID LLDP_ShowGlobalConfig(VOID);

/*******************************************************************************
*    Func Name: LLDP_GetLocalInfo
* Date Created: 2011-10-08
*       Author: guo00178934
*  Description: ��ȡLLDP������Ϣ��
*        Input: 
*       Output: LLDP_SYS_INFO_S *pstLocal: LLDP������Ϣ��
*               ����ChassisId��ϵͳ���ƣ�ϵͳ�����������ַ��Ϣ������ϵͳ������
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-08   guo00178934             Create
*
*******************************************************************************/
ULONG LLDP_GetLocalInfo(LLDP_SYS_INFO_S *pstLocal);

/*******************************************************************************
*    Func Name: LLDP_ShowLocalInfo
* Date Created: 2011-10-08
*       Author: guo00178934
*  Description: ��ʾ������Ϣ������ChassisId��ϵͳ���ƣ�ϵͳ������������Ϣ��ϵͳ������
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-08   guo00178934             Create
*
*******************************************************************************/
VOID LLDP_ShowLocalInfo(VOID);

/*******************************************************************************
*    Func Name: LLDP_GetPortInfo
* Date Created: 2011-09-30
*       Author: guo00178934
*  Description: ��ȡLLDP�ӿ���Ϣ
*        Input: ULONG ulIfIndex: LLDP�Ľӿ�����
*       Output: LLDP_PORT_INFO_S *pstPortInfo: LLDP�ӿ���Ϣ
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA,
*               LLDP_ERR_IF_NOT_SUPPORT,LLDP_ERR_PORT_NOT_EXIST
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-30   guo00178934             Create
*
*******************************************************************************/
ULONG LLDP_GetPortInfo(ULONG ulIfIndex, LLDP_PORT_INFO_S *pstPortInfo);

/*******************************************************************************
*    Func Name: LLDP_ShowPortInfo
* Date Created: 2011-10-31
*       Author: limin00188004
*  Description: ��ʾ���п���LLDP�Ľӿ���Ϣ��
*               �����ӿڱ�ţ��ӿ�ģʽ���ӿ�ID��Port Desc TLV��PPVID TLV�ȡ�
*        Input: CHAR *pIfName: ָ���Ľӿ����ƣ�����Ϊ""�������ʾ���п���LLDP�Ľӿ���Ϣ
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-31   limin00188004           Create
*
*******************************************************************************/
VOID LLDP_ShowPortInfo(CHAR *pIfName);

/*******************************************************************************
*    Func Name: LLDP_RemTableOpen
* Date Created: 2011-09-29
*       Author: limin00188004
*  Description:  ��ѯLLDP�ھ���Ϣ��Open����
*        Input:   LLDP_REM_FILTER_S *pstFilter:  ������������ǰ�˿ڱ�ű���ָ������
*               LLDP_REM_FILTER_S�е�ulDestAddrGroup��ulRemIndex�ֶ�ȡֵ����:
*               ULONG ulDestAddrGroup: Remote�����鲥��ı�ţ�Ϊ0������ֶβ�ѯʱ��Ч��
*                                  DestMac��Nearest bridge ��1��
*                                  DestMac��Nearest non-TPMR bridge��2��
*                                  DestMac��Nearest Customer Bridge��3��
*               ULONG ulRemIndex:Remote��ţ�ȡֵ��Χ��1~7FFFFFFF����Ϊ0������ֶβ�ѯʱ��Ч��
*       Output:  ULONG *pHandle: ��ѯ���
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA,LLDP_ERR_PORT_NUM_ZERO,
*               LLDP_ERR_MALLOC_FAIL
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-29   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_RemTableOpen(UINTPTR *pulHandle, LLDP_REM_FILTER_S *pstFilter);

/*******************************************************************************
*    Func Name: LLDP_RemTableGet
* Date Created: 2011-09-29
*       Author: limin00188004
*  Description: ��ѯLLDP�ھ���Ϣ��Get����
*        Input: ULONG ulHandle:  ��ѯ���
*       Output: LLDP_REM_INFO_S * pstRemInfo: ��ѯ����LLDP�ھӽڵ���Ϣ
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-29   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_RemTableGet(UINTPTR ulHandle, LLDP_REM_INFO_S * pstRemInfo);

/*******************************************************************************
*    Func Name: LLDP_RemTableClose
* Date Created: 2011-09-30
*       Author: limin00188004
*  Description: ��ѯLLDP�ھ���Ϣ��Close����
*        Input: ULONG ulHandle: ��ѯ���
*       Output: 
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-30   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_RemTableClose(UINTPTR ulHandle);


VOID LLDP_ShowRemInfo(CHAR *pIfName, ULONG ulDestAddrGroup, ULONG ulRemIndex);

/*******************************************************************************
*    Func Name: LLDP_GetSysStat
* Date Created: 2011-10-24
*       Author: limin00188004
*  Description: ��ȡLLDPϵͳͳ����Ϣ
*        Input: 
*       Output: LLDP_SYS_STAT_S *pstSysStat: ȫϵͳͳ����Ϣ
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-24   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_GetSysStat(LLDP_SYS_STAT_S *pstSysStat);

/*******************************************************************************
*    Func Name: LLDP_ClearSysStat
* Date Created: 2011-10-24
*       Author: limin00188004
*  Description: ���LLDPϵͳͳ����Ϣ
*        Input: VOID
*       Output: 
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-24   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_ClearSysStat(VOID);

/*******************************************************************************
*    Func Name: LLDP_ShowSysStat
* Date Created: 2011-10-24
*       Author: limin00188004
*  Description: ��ʾLLDPϵͳͳ����Ϣ
*        Input: VOID
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-24   limin00188004           Create
*
*******************************************************************************/
VOID LLDP_ShowSysStat(VOID);

/*******************************************************************************
*    Func Name: LLDP_GetPortStat
* Date Created: 2011-10-19
*       Author: guo00178934
*  Description: ��ȡLLDP�ӿ�ͳ����Ϣ������ָ���ӿڱ�ź��鲥��ţ�.
*        Input: ULONG ulIfIndex: LLDP�Ľӿ�����
*               ULONG ulDestAddrGroup: Ŀ���鲥��ı��.
*                    Nearest bridge              1
*                    Nearest non-TPMR bridge     2
*                    Nearest Customer Bridge     3
*       Output: LLDP_PORT_STAT_S *pstPortStat: �ӿ�ͳ����Ϣ
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA,LLDP_ERR_IF_NOT_SUPPORT,
*               LLDP_ERR_PORT_NOT_EXIST
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-19   limin00188004             Create
*
*******************************************************************************/
ULONG LLDP_GetPortStat(ULONG ulIfIndex, ULONG ulDestAddrGroup, LLDP_PORT_STAT_S *pstPortStat);

/*******************************************************************************
*    Func Name: LLDP_ClearPortStat
* Date Created: 2011-10-19
*       Author: guo00178934
*  Description: ���ָ���ӿ�ָ���鲥���LLDPͳ����Ϣ��
*        Input: ULONG ulIfIndex:ʹ��LLDP�Ľӿ�������Ϊ0���������ʹ��LLDP�Ľӿڵ�ͳ����Ϣ��
*               ULONG ulDestAddrGroup: Ŀ���鲥��ı�š�Ϊ0��������ýӿ��ϵ�����Agent�ϵ�ͳ����Ϣ��
*                    Nearest bridge              1
*                    Nearest non-TPMR bridge     2
*                    Nearest Customer Bridge     3
*       Output: 
*       Return: LLDP_OK,LLDP_ERR_LLDP_NOT_INIT,LLDP_ERR_INVALID_PARA_VALUE,
*               LLDP_ERR_PORT_NOT_EXIST,LLDP_ERR_INVALID_PARA
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-10   limin00188004           Create
*
*******************************************************************************/
ULONG LLDP_ClearPortStat(ULONG ulIfIndex, ULONG ulDestAddrGroup);

/*******************************************************************************
*    Func Name: LLDP_ShowPortStat
* Date Created: 2011-10-19
*       Author: guo00178934
*  Description: ��ʾָ���ӿ������鲥���LLDPͳ����Ϣ
*        Input: CHAR *pIfName: ָ���Ľӿ�����
*               ULONG ulDestAddrGroup:Ŀ���鲥��ı�š�Ϊ0������ʾ�ýӿ�������Agent��ͳ����Ϣ��
*                    Nearest bridge              1
*                    Nearest non-TPMR bridge     2
*                    Nearest Customer Bridge     3
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-10   limin00188004           Create
*
*******************************************************************************/
VOID LLDP_ShowPortStat(CHAR *pIfName, ULONG ulDestAddrGroup);

/*******************************************************************************
*    Func Name: LLDP_SetDebugSwitch
* Date Created: 2011-10-30
*       Author: guo00178934
*  Description: ����Debug���غ͹�������
*        Input: ULONG ulDebug: LLDP Debug����ֵ��
*               ULONG ulIfIndex: ָ���ӿ�������0�������еĽӿڣ�����ָ��ĳ���ӿڡ�
*               ULONG ulDestAddrGroup: ָ���鲥���ͣ�0���������鲥��ַ����0����ָ��ĳ���鲥��ַ��
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-30   guo00178934             Create
*
*******************************************************************************/
ULONG LLDP_SetDebugSwitch (ULONG ulDebug, ULONG ulIfIndex, ULONG ulDestAddrGroup);

/*******************************************************************************
*    Func Name: LLDP_GetDebugSwitch
* Date Created: 2011-10-30
*       Author: guo00178934
*  Description: ��ȡDebug���غ͹�������
*        Input: ULONG *pulDebug: ��ȡ��LLDP Debug����ֵ��
*               ULONG *pulIfIndex: ��ȡ��ǰ��debug���صĽӿ�����ֵ��
*               ULONG *pulDestAddrGroup: ��ȡ��ǰ��debug���صĶಥ���͡�
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-10-30   guo00178934             Create
*
*******************************************************************************/
ULONG LLDP_GetDebugSwitch (ULONG *pulDebug, ULONG *pulIfIndex, ULONG *pulDestAddrGroup);

/*******************************************************************************
*    Func Name: LLDP_ShowDebugSwitch
* Date Created: 2011-10-30
*       Author: guo00178934
*  Description: ��ʾȫ��LLDP Debug���ء�
*        Input: 
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-27   guo00178934             Create
*
*******************************************************************************/
VOID LLDP_ShowDebugSwitch ();

/*******************************************************************************
*    Func Name: LLDP_PPI_HookRegister
* Date Created: 2011-09-28
*       Author: guo00178934
*  Description: PPIע�ắ������TRANע�ᣬVISP���ʵ���ʱ����øú�����������Ϣ֪ͨTRAN.
*        Input: LLDP_PPI_HOOK_S *pstHookFun:
*                typedef struct tabLLDP_PPI_HOOK
*                {
*                    ULONG (*pfLLDP_PPI_Mode_Update)(ULONG ulOperType, LLDP_PPI_UPDATE_S *pstLldpUpdateMsg);
*                }LLDP_PPI_HOOK_S;
*
*                   ulOperType    �������ͣ�
*                   PPI_LLDP_PORT_MODE_DISABLE     0
*                   PPI_LLDP_PORT_MODE_TX          1
*                   PPI_LLDP_PORT_MODE_RX          2
*                   PPI_LLDP_PORT_MODE_TXRX        3
*
*                typedef struct tagLldpPpiUpdate
*                {
*                    ULONG ulIfIndex;      
*                    ULONG ulDestAddrGroup 
*                }LLDP_PPI_UPDATE_S;
*                    ulIfIndex: �ӿ�����
*                    ulDestAddrGroup:Ŀ���鲥��ı��
*                    Nearest bridge              1
*                    Nearest non-TPMR bridge     2
*                    Nearest Customer Bridge     3
*       Output: 
*       Return: LLDP_OK,LLDP_ERR_PPI_UPDATE_FUN_NOT_CFG
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2011-09-28   guo00178934             Create
*
*******************************************************************************/
ULONG LLDP_PPI_HookRegister(LLDP_PPI_HOOK_S *pstHookFun);

/*LLDP  PPI��Ϣ�·����Ӻ����ĺ궨��*/
#define g_pfLLDP_PPI_Mode_Update g_stLldpHookRegister.pfLLDP_PPI_Mode_Update

/*******************************************************************************
*    Func Name: LLDP_CfgPortMFS
* Date Created: 2012-08-17
*       Author: zhangliangzhi00187023
*  Description: 
*        Input: ULONG ulIfIndex:
*               USHORT usMaxFrameSize:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-17   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgPortMFS(ULONG ulIfIndex, USHORT usMaxFrameSize);

/*******************************************************************************
*    Func Name: LLDP_CfgSysCapTlv
* Date Created: 2012-08-17
*       Author: zhangliangzhi00187023
*  Description: 
*        Input: LLDP_SYS_CAPABILITY_INFO_S *pstSysCap:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-17   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgSysCapTlv(LLDP_SYS_CAPABILITY_INFO_S *pstSysCap);

/*******************************************************************************
*    Func Name: LLDP_CfgManageVidTlv
* Date Created: 2012-08-17
*       Author: zhangliangzhi00187023
*  Description: 
*        Input: LLDP_MANAGEMENT_VID_INFO_S *pstMngVid:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-17   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgManageVidTlv(ULONG ulOperate, LLDP_MANAGEMENT_VID_INFO_S *pstMngVid);

/*******************************************************************************
*    Func Name: LLDP_CfgPortInfo
* Date Created: 2012-08-17
*       Author: zhangliangzhi00187023
*  Description: 
*        Input: ULONG ulIfIndex:
*               LLDP_CFG_PORT_INFO_S *pstPortInfo:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-17   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgPortInfo(ULONG ulIfIndex, LLDP_CFG_PORT_INFO_S *pstPortInfo);

/*******************************************************************************
*    Func Name: LLDP_CfgPortVlanIdTlv
* Date Created: 2012-08-17
*       Author: zhangliangzhi00187023
*  Description: 
*        Input: ULONG ulOperate:
*               ULONG ulIfIndex:
*               LLDP_PVID_INFO_S *pstPortVlanId:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-17   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgPortVlanIdTlv(ULONG ulOperate,ULONG ulIfIndex, LLDP_PVID_INFO_S 
*pstPortVlanId);

/*******************************************************************************
*    Func Name: LLDP_CfgMacPhyCfgTlv
* Date Created: 2012-08-17
*       Author: zhangliangzhi00187023
*  Description: 
*        Input: ULONG ulIfIndex:
*               LLDP_MAC_PHY_CFG_INFO_S *pstMacPhyCfg:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-17   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgMacPhyCfgTlv(ULONG ulIfIndex,LLDP_MAC_PHY_CFG_INFO_S 
*pstMacPhyCfg);


/*******************************************************************************
*    Func Name: LLDP_CfgLinkAggregationTlv
* Date Created: 2012-08-17
*       Author: zhangliangzhi00187023
*  Description: 
*        Input: ULONG ulOperate:
*               ULONG ulIfIndex:
*               LLDP_LINK_AGG_INFO_S *pstLinkAgg:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-17   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgLinkAggregationTlv( ULONG ulOperate,ULONG ulIfIndex, LLDP_LINK_AGG_INFO_S 
*pstLinkAgg);

/*******************************************************************************
*    Func Name: LLDP_CfgVlanNameTlv
* Date Created: 2012-08-17
*       Author: zhangliangzhi00187023
*  Description: 
*        Input: ULONG ulOperate:
*               ULONG ulIfIndex:
*               ULONG ulNumber:
*               LLDP_VLAN_NAME_INFO_S stVlanName[]:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-17   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgVlanNameTlv(ULONG ulOperate,ULONG ulIfIndex, ULONG ulNumber, LLDP_VLAN_NAME_INFO_S 
stVlanName[]);


/*******************************************************************************
*    Func Name: LLDP_CfgChassisIDTlv
* Date Created: 2012-10-17
*       Author: zhangliangzhi00187023
*  Description: ����chassis id 
*        Input: ULONG ulIfIndex:
*               LLDP_CHASSISID_INFO_S *pstChassisId:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-10-17   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgChassisIDTlv(ULONG ulIfIndex,LLDP_CHASSISID_INFO_S *pstChassisId);


/*******************************************************************************
*    Func Name: LLDP_CfgManagementTlv
* Date Created: 2012-10-17
*       Author: zhangliangzhi00187023
*  Description: ���ù����ַ
*        Input: ULONG ulOperate:
*               LLDP_MANAGEMENT_INFO_S *pstManagement:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-10-17   zhangliangzhi00187023   Create
*
*******************************************************************************/
ULONG LLDP_CfgManagementTlv(ULONG ulOperate, LLDP_MANAGEMENT_INFO_S 
*pstManagement);


ULONG LLDP_AddPortDynamic(ULONG ulIfIndex);


ULONG LLDP_DelPortDynamic(ULONG ulIfIndex);


ULONG LLDP_RegFuncGetExtendTlvHook(LLDP_GETEXTTLV_HOOK_FUNC pfFuncHook);


ULONG LLDP_CfgLocalChange(ULONG ulIfIndex, ULONG ulDestAddrGroup);


ULONG LLDP_RegFuncInputHook(LLDP_INPUT_HOOK_FUNC pfFuncHook);

#ifdef  __cplusplus
}
#endif

#endif

