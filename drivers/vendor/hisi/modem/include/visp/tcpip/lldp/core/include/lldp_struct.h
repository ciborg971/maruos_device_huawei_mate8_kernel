
#ifndef _LLDP_STRUCT_H_
#define _LLDP_STRUCT_H_

#ifdef  __cplusplus
extern "C"{
#endif
#ifndef PCK

typedef struct tagLLDP_RAW_PACKET_S
{
    ULONG  ulLength;
    UCHAR* pucBuf;
}LLDP_RAW_PACKET_S; 

/************************************************************************************/
typedef struct tagLLDP_BASIC_TLV_HEADER_S
{
    USHORT usTLVType : 7;                /*����*/
    USHORT usTLVInfoLength : 9;          /*������Ϣ�ĳ���*/
}LLDP_BASIC_TLV_HEADER_S;

typedef struct tagLLDP_VAR_STRING_S
{
    LLDP_BASIC_TLV_HEADER_S stLldpTLVheader;
    UCHAR ucString[2];                  /*TLV Value*/
    
}LLDP_VAR_STRING_S;

typedef struct tagLLDP_ETH_HEADER_S
{
    UCHAR     ucEthDMA[LLDP_MAC_ADDR_LEN];
    UCHAR     ucEthSMA[LLDP_MAC_ADDR_LEN];
    USHORT    usProtocolVer;           /* Э��汾�� �� 0x80CC */
}LLDP_ETH_HEADER_S;


/* LLDPЭ�鱨�ĸ�ʽ */
typedef struct tagLLDP_PACKET_S
{
    LLDP_ETH_HEADER_S stEthHeader;   /*��̫��ͷ*/
    
    LLDP_VAR_STRING_S stTLV[1];      /* �ɱ䳤���ַ��� */
} LLDP_PACKET_S;

#endif

#ifndef TLV

/*Time To Live TLV*/
typedef struct tagLLDP_TTL_INFO_S
{
    USHORT usTTL;
    UCHAR ucResv[2]; 
}LLDP_TTL_INFO_S;

#endif

#ifndef GLOBAL


/* �����ڲ� */
typedef struct tagLLDP_LOCAL_SYS_INFO_S
{
    /**ϵͳȫ�ֹ����TLV**/
    LLDP_SYS_NAME_INFO_S stLocSysName;      /*system name TLV , ����ϵͳ���ƣ�Ĭ��ֵ"System" */
    LLDP_SYS_DESC_INFO_S stLocSysDesc;      /* system description TLV,����ϵͳ������Ĭ��ֵ"System" */
    LLDP_SYS_CAPABILITY_INFO_S stSysCapability; /* system Capabilities TLV */ 
    LLDP_MANAGEMENT_VID_INFO_S stManagementVid;  /*Management VID TLV*/
    LLDP_MANAGEMENT_INFO_S stManagement; /** Management Address TLV  **/  

    LLDP_ADMIN_STATUS_E eAdminStatus;              /*�����豸ʹ��LLDP��־*/
    ULONG ulTrapEnabled;                           /*�澯ʹ�ܱ�־*/  
    
    LLDP_GLOBAL_CFG_S stConfigutation;          /*LLDPȫ��������Ϣ*/
    LLDP_SYS_STAT_S         stStatsInfo;               /*LLDPȫ��ͳ����Ϣ*/   
    ULONG ulTickTimerID;                    /**/    
    ULONG ulManagementVidFlag;  /*Management VID TLV �Ƿ���Ч*/
    ULONG ulManagementAddressFlag;  /*Management TLV �Ƿ���Ч*/
}LLDP_LOCAL_SYS_INFO_S;

#endif

#ifndef PORT

/***  �ھӽڵ���Ϣ�������ڲ�ϵͳ�洢***/
typedef struct tagLLDP_LOCAL_REM_INFO_S
{
    ULONG  ulPortIfIndex;         /* Remote���ڶ˿ڵı��*/
    ULONG  ulDestAddrIndex;       /* Remote�����鲥��ı�ţ�ȡֵ��Χ��0~2��,�л����ⲿ�ṹ��ʱ���1
                                            DestMac��01:80:c2:00:00:0e��0��
                                            DestMac��01:80:c2:00:00:03��1��
                                            DestMac��01:80:c2:00:00:00��2��*/
    ULONG  ulRemIndex;            /* Remote��ţ�ȡֵ��Χ��1~7FFFFFFF��*/
    ULONG  ulRemLastMarkTime;         /* Remote�ϴα����ʱ�䣨��λ���룩 */
    
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
                                      10- Port and Protocol Vlan ID TLV*/
    USHORT usTTL;                 /* �ھӽڵ���ϻ�ʱ��, ȡ�Ա����е�TTL TLV.*/
    USHORT usRemTTL;              /* �ھӵ�TTL TLV�е���Ϣ*/
    LLDP_CHASSISID_INFO_S stRemChassisId;       /* Remote ChassisId TLV*/     
    LLDP_PORTID_INFO_S  stRemPortId;            /* Remote PortId TLV */ 
    LLDP_MANAGEMENT_INFO_S stRemManagement;
    LLDP_SYS_NAME_INFO_S stRemSysName;          /* ����ϵͳ���ƣ�Ĭ��ֵ"System" */
    LLDP_SYS_DESC_INFO_S stRemSysDesc;          /* ����ϵͳ������Ĭ��ֵ"System" */
    LLDP_SYS_CAPABILITY_INFO_S stRemSysCapability;   
    LLDP_PORT_DESC_INFO_S stRemPortDesc;        /* Port Description TLV */
    LLDP_MAC_PHY_CFG_INFO_S stRemPhyCfgStatus;/* MAC/PHY Configuration/Status TLV */
    LLDP_PVID_INFO_S stRemPortVlanId;
    LLDP_MAX_FRAME_SIZE_INFO_S stRemMaxFrameSize;
    LLDP_LINK_AGG_INFO_S stLinkAgg;             /* Link Aggregation TLV */
    LLDP_POWER_VIA_MDI_INFO_S stPowerViaMdi;
    ULONG  ulPpvidNum;                          /* Port and Protocol Vlan ID TLV ����*/
    LLDP_PPVID_INFO_S stPpvid[LLDP_MAX_PPVID_TLV_NUM]; /* PPVID TLV */
    LLDP_MANAGEMENT_VID_INFO_S stRemManagementVid; /* Management VID TLV */     
    UCHAR ucVlanNameNum;/* Vlan Name TLV ����*/
    UCHAR ucRes[2];    
    LLDP_VLAN_NAME_INFO_S stRemVlanName[LLDP_MAX_VLAN_NAME_TLV_NUM]; /*Vlan Name TLV */    

}LLDP_LOCAL_REM_INFO_S; 

/*���˽ӿ�ͳ����Ϣ*/
typedef struct tagLLDP_LOCAL_PORT_STAT_S
{
    ULONG  ulRxFramesTotal;             /* �յ���LLDP ֡���� */
    ULONG  ulRxDiscardedTotal;          /* ������LLDP ֡���� */
    ULONG  ulRxErrorsTotal;             /* �յ��Ĵ���LLDP ֡���� */
    ULONG  ulRxTLVsDiscardedTotal;      /* ������LLDP TLV ֡���� */
    ULONG  ulRxTLVsUnrecognizedTotal;   /* ����ʶ���LLDP TLV ֡���� */
    ULONG  ulTxFramesTotal;             /* ���͵�LLDP ֡���� */
    ULONG  ulRxAgeoutsTotal;            /* �ϻ���LLDP �ھ���Ϣ���� */
    ULONG  ulRxErrTLVSysName;
    ULONG  ulRxErrTLVSysDesc;
    ULONG  ulRxErrTLVSysCapability;
    ULONG  ulRxErrTLVPortDesc;
    ULONG  ulRxErrTLVManAddr;
    ULONG  ulRxErrTLVMacPhyCfg;
    ULONG  ulRxErrTLVPortVlanId;
    ULONG  ulRxErrTLVMaxFrameSize;
    ULONG  ulRxErrTLVLinkAgg;
    ULONG  ulRxErrTLVPowerViaMdi;
    ULONG  ulRxErrTLVPpvid;
    ULONG  ulRxErrTLVChassisId;
    ULONG  ulRxErrTLVPortId;   
    ULONG  ulRxErrTLVTTL;
    ULONG  ulRxErrTLVEndTLV;
}LLDP_LOCAL_PORT_STAT_S; 

typedef struct tagLLDP_LOCAL_AGENT
{
    /*ָ��agentֱ���ھӵ���ϢLLDP_REM_INFO_S����*/
    LLDP_LOCAL_REM_INFO_S *stRemNeighborDataArray[LLDP_AGENT_MAX_REMOTE_TABLE];
    LLDP_LOCAL_PORT_STAT_S  stStatsPort;             /*���ض˿�ͳ����Ϣ*/      
    ULONG ulPortMode;                                 /*�ӿ�ģʽ Tx��Rx��TxRx��Disable*/   
    ULONG ulRemNeighborNum;                 /*��agent��Ч�ھӽڵ�����*/
    ULONG ulTransmitFsmState;               /*����״̬��״̬*/
    ULONG ulTransmitTimerFsmState;          /*���Ͷ�ʱ��״̬��״̬*/
    ULONG ulReceiveFsmState;                /*����״̬��״̬*/
    ULONG ulTransmitTimerID;                /**/
    ULONG ulShutdownTimerID;                /**/
    ULONG ulRXInfoAgeTimerID;               /**/
    ULONG ulRxInfoAge;                        /**/
    ULONG ulRcvFrame;
    ULONG ulRxChanges;
    ULONG ulBadFrame;
    ULONG ulTxTTL;
    ULONG ulRxTTL;
    ULONG ulTxTick;
    ULONG ulTxNow;
    ULONG ulLocalChange;
    ULONG ulTxTTR;                          /*��λ:ms*/
    ULONG ulTxFast;
    ULONG ulTxShutdownWhile;
    ULONG ulNewNeighbor;
    ULONG ulTxCredit;
    ULONG szMsg[4];
}LLDP_LOCAL_AGENT_S;



/*���ض˿���Ϣ����*/
typedef struct tagLLDP_LOCAL_PORT
{
    ULONG  ulIfIndex;                                 /* LLDP�ӿڱ�� */
    ULONG  ulPortEnabled;                             /*��¼�˿ڵ�״̬,���ڶ˿�shut/undo shut����*/    
    ULONG  ulPpvidNum;                               /* Port and Protocol Vlan ID TLV ����*/
    CHAR  szIfName[LLDP_IF_NAME_LEN];              
    UCHAR szEthMAC[LLDP_MAC_ADDR_LEN];

    UCHAR ucDefaultMaxSizeTlv;       
    UCHAR ucResv; 
    USHORT usPktVLanId; /*����ͷ��Vlan Tag��ID, ����Port Vlan ID TLV��Ϣ.*/
    USHORT usPktVLanPri; /*����ͷ��Vlan Tag�����ȼ�, ����Port Vlan ID TLV��Ϣ.*/
    ULONG ulLinkAggIfCfg; /*Link Aggregation TLV��Ϣͨ��API���ý���(ֵΪ1),��ͨ��LLDP_GetTrunkId��ȡ��(0)*/
    
    LLDP_PORTID_INFO_S stPortID;                      /*Port ID TLV*/
    LLDP_TTL_INFO_S stTTL;                            /*Time To Live TLV*/    
    LLDP_SYS_CAPABILITY_INFO_S stSysCapability;      /* system Capabilities TLV */
    LLDP_PVID_INFO_S stPortVlanID;                 /* PortVlan ID TLV֧�ֵ�VLAN ID��Port VLAN ID TLV��Ϣ */
    LLDP_PORT_DESC_INFO_S stPortDesc;                 /* Port Description TLV */ 
    LLDP_PPVID_INFO_S stPpvid[LLDP_MAX_PPVID_TLV_NUM];/*Port VLAN ID TLV ֧�ֶ��vlanIDĿǰ��֧��*/
    LLDP_LINK_AGG_INFO_S stLinkAgg;                   /* Link Aggregation TLV */
    LLDP_MAC_PHY_CFG_INFO_S stMacPhyCfg;            /*MAC/PHY Configuration/Status TLV*/ 
    LLDP_MAX_FRAME_SIZE_INFO_S stMaxFrameSize;        /*MaxFrameSize TLV*/
    LLDP_POWER_VIA_MDI_INFO_S stMdi;
    LLDP_VLAN_NAME_INFO_S stVlanName[LLDP_MAX_VLAN_NAME_TLV_NUM];
    LLDP_CHASSISID_INFO_S stChassisId;
    LLDP_LOCAL_AGENT_S  stPortAgent[LLDP_MAX_MACTYPE_SIZE];/*3���ಥ��ַ*/              
}LLDP_LOCAL_PORT_S;

#endif

/*ϵͳͳ����Ϣ*/
typedef struct tagLLDP_LOCAL_SYS_STAT_S
{
    ULONG  ulRemTablesLastChangeTime; /* Remote�����һ���޸�ʱ�� */
    ULONG  ulRemTablesInserts;        /* Remote���������������� */
    ULONG  ulRemTablesDeletes;        /* Remote��ɾ������ */
    ULONG  ulRemTablesDrops;          /* Remote�����ڵ���� */
    ULONG  ulRemTablesAgeouts;        /* Remote��ʱ���� */
    ULONG  ulRemTablesUpdates;        /* Remote����¸��� */
}LLDP_LOCAL_SYS_STAT_S; 


#ifdef  __cplusplus
}
#endif

#endif
