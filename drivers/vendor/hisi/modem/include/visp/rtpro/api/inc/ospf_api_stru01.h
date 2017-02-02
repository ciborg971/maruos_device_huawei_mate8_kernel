
#ifndef _OSPF_API_STRU01_H
#define _OSPF_API_STRU01_H
#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*11 ԭ�����ӿڽṹ��*/
/*�����ݽṹ��������ASBR·����*/
typedef struct tagOSPF_CFG_ASBR
{
    USHORT usProcessId;                   /*����ID*/
    /*Modify for BC3D00579���������� liangjicheng 2008-10-29 */
    USHORT usAsbrFlg;                    /*�Ƿ�ΪASBR�ı�־,1��ʾ·����ΪASBR,
                                           0��ʾ·������ΪASBR��Ĭ��Ϊ1*/
    /*Modify for BC3D00578 Delete the filed liangjicheng 2008-10-29 
      no need set this filed*/
    /*ULONG ulRouterId; */                   /*·����ID*/
    
}OSPF_CFG_ASBR_S;



/*�����ݽṹ����������ɾ��һ������*/
typedef struct tagOSPF_CFGAREA
{
    ULONG  ulAreaId;                    /*����ID*/ 
    USHORT bNoFlag;                     /*�������û���ɾ������,0���ã�1ɾ��*/
    USHORT usProcessId;                 /*����id*/
}OSPF_CFGAREA_S;

/*�����ݽṹ��������·�ɾۺ�*/
typedef struct tagOSPF_CFGAREARANGE
{
    USHORT bNoFlag;                    /*���������û���ɾ����1���ã�0ɾ��*/                 
    USHORT usProcessId;                /*����ID*/
    ULONG ulAreaId;                    /*����ID*/
    ULONG ulIpAddr;                    /*��ַ*/
    ULONG ulIpMask;                    /*�����ַ*/
    ULONG ulEffect;                    /*�Ƿ���Ч��־��1��Ч��0����Ч*/
    ULONG ulLsdbType;                  /*lsdb type:summary link or nssa external link */
}OSPF_CFGAREARANGE_S;

/*�������������ý���GR����ز���*/
/*
#define OSPF_CFG_RESET_CFG_GRPARA   0x00
#define OSPF_CFG_RESET_SET_DOWN     0x01
#define OSPF_CFG_RESET_SET_UP       0x02
#define OSPF_CFG_RESET_SET_DOWNUP   0x03*/
typedef struct tagOSPF_CFGRESET
{
    USHORT usResetFlg;                 /*������־��
    0-���ò�����1-Down 2-UP 3-����(DownUp)*/
    USHORT usProcessId;                /*����ID*/
    ULONG ulDoGraceHitless;            /*ƽ��������־*/
    ULONG ulDoGraceUnplannedHitless;   /*�޼ƻ���ƽ��������־*/
    ULONG ulHitlessGrPeriod;           /*ƽ����������*/
    ULONG ulhitlessGrReason;           /*ƽ������ԭ��*/
}OSPF_CFGRESET_S;

/*Add for RPU BC3D02904*/
typedef struct tagOSPF_CFGFASTDOWN
{
  USHORT usProcessId;
  USHORT usFlag;/* 0 ��ʹ��  1 ʹ��*/
}OSPF_CFGFASTDOWN_S;
/*End for RPU BC3D02904*/

typedef struct tagOSPF_CFGMAXPATH
{
    ULONG ulProcessId;
    ULONG ulEqRouterNums;
}OSPF_CFGMAXPATH_S;

typedef struct tagOSPF_CFGNEIGHBOR
{
    ULONG  ulNeighborIpAddr;
    USHORT bNoFlag;
    USHORT bPriority;
    USHORT usProcessId;
    UCHAR  ucPriority;
    UCHAR  ucRes;
}OSPF_CFGNEIGHBOR_S;

typedef struct tagOSPF_CFGNETWORK
{
    ULONG  ulAreaId;
    ULONG  ulNetworkAddr;
    ULONG  ulMaskLen;
    USHORT usProcessId;
    USHORT bNoFlag;
}OSPF_CFGNETWORK_S;

typedef struct tagOSPF_CFGPASSIVEIF
{
    /*������־,��ʱ1ʱ,�ӿڲ��ٽ��շ���Hello���� Ĭ��:0*/
    USHORT usPassiveFlg;
    USHORT usProcessId;
    UCHAR szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
}OSPF_CFGPASSIVEIF_S;

typedef struct tagOSPF_CFGPROC_WITHRID
{
    ULONG  ulRouterId;                /*·����ID,�û�ָ��*/
    USHORT usProcessId;               /*����ID*/
    USHORT bNoFlag;                   /*������ɾ����־*/
    ULONG ulMaxEqCostPaths;           /* OSPF·�ɱ��еĵȼ�·��������
                                        ȡֵ��Χ��0~32
                                        ������Ϊ0ʱ����ʾ������
                                        ϵͳ����ʱĬ��Ϊ5�� */   
                                        
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[OSPF_MAX_VRF_NAME_LENGTH + 1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}OSPF_CFGPROC_WITHRID_S;

typedef struct tagOSPF_CFGPROC
{
    USHORT usProcessId;               /*����ID*/
    USHORT bNoFlag;                   /*������ɾ����־*/
    ULONG ulMaxEqCostPaths;           /* OSPF·�ɱ��еĵȼ�·��������
                                        ȡֵ��Χ��0~32
                                        ������Ϊ0ʱ����ʾ������
                                        ϵͳ����ʱĬ��Ϊ5�� */

    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[OSPF_MAX_VRF_NAME_LENGTH + 1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}OSPF_CFGPROC_S;
/*Add for BC3D02908*/
typedef struct tagOSPF_CFGGRHELPER
{
    /* ULONG usProcessId;*//* BC3D03437 ȡ���������� */
    UCHAR szIfname[OSPF_MAX_IF_NAME_LENGTH+1];
    ULONG ulHelperMode;
    ULONG ulGrPeriod;
    ULONG ulAccNum;
    
}OSPF_CFGGRHELPER_S;
/*end BC3D02908*/
/*Add for BC3D03437 at 2010-07-16*/
typedef struct tagOSPF_CFGGRHELPER_PRO
{
    ULONG usProcessId;
    ULONG ulHelperMode;
    ULONG ulGrPeriod;
    ULONG ulAccNum;
}OSPF_CFGGRHELPER_PRO_S;
/*End for BC3D03437 at 2010-07-16*/
typedef struct tagOSPF_CFGCOMPRFC1583
{
    ULONG ulProcessId;
    ULONG ulCompFlg;
}OSPF_CFGCOMPRFC1583_S;

typedef struct tagOSPF_CFGIFLSADELAY
{
    USHORT usProcessId;  /*ULONG->USHORT L*/ 
    USHORT usPadding;
    ULONG ulAreaId;
    UCHAR szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    ULONG ulLsaDelay; 
}OSPF_CFGIFLSADELAY_S;

typedef struct tagOSPF_CFGIF_POLL
{
    ULONG ulProcessId;
    UCHAR szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    ULONG ulPollItvl;
}OSPF_CFGIF_POLL_S;

typedef struct tagOSPF_CFG_MAXMTU
{
    /*ULONG ulProcessId;*/
    UCHAR szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    /*ULONG ulMtuLen;*/  /*MTU 46-1560 Default 576 the same to VRP*/
    ULONG ulMtuIgnore;
}OSPF_CFG_MAXMTU_S;

typedef struct OSPF_CFGAREA_RFSHITVL
{
    ULONG ulProcessId;
    ULONG ulAreaId;
    ULONG ulRfshItvl;
}OSPF_CFGAREA_RFSHITVL_S;

typedef struct tagOSPF_CFGSPFITVL
{
    ULONG ulProcessId;
    ULONG ulSpfItvl;
}OSPF_CFGSPFITVL_S;

typedef struct tagOSPF_CFGAREASTUB
{
    USHORT bNoFlag;
    USHORT bNoSummaryFlag; /*1-VOS_TRUE������Summary  0-VOS_FALSE*/
    ULONG  ulAreaId;
    USHORT usProcessId; 
    USHORT usRes;
}OSPF_CFGAREASTUB_S;

typedef struct tagOSPF_CFG_VLINKPEER
{
    ULONG ulCfgFlg;
    ULONG ulProcessId;
    ULONG ulAreaId;
    ULONG ulNbrId;
}OSPF_CFG_VLINKPEER_S;

typedef struct tagOSPF_CFG_VLINKAUTH
{
    ULONG ulProcessId;
    ULONG ulAreaId;
    ULONG ulNbrId;
    ULONG ulAuthType;
    ULONG ulAuthkeyLen;
    UCHAR szAuthKeyValue[256];
    ULONG ulAuthUserDataLen;
    UCHAR szAuthUserDataValue[4];
}OSPF_CFG_VLINKAUTH_S;

typedef struct tagOSPF_CFG_VLINKPARA
{
    ULONG ulProcessId;
    ULONG ulAreaId;
    ULONG ulNbrId;
    ULONG ulHelloItvl;
    ULONG ulDeadItvl;
    ULONG ulRetransItvl;
    ULONG ulTransDelay;
}OSPF_CFG_VLINKPARA_S;


/*if����Ҫ��ʾ��������*/

/*�����ݽṹ�а���AMB_OSPF_PM_LSDB�е��û����ĵ��ֶ�*/
typedef struct tagOSPF_SHOW_LSDB
{
    UCHAR ucAreaId[4];
    ULONG ulType;
    UCHAR ucLsId[4];
    UCHAR ucRouterId[4];
    ULONG ulProcessId;
    ULONG ulSequence;
    ULONG ulAge;
    ULONG ulChksum;
}OSPF_SHOW_LSDB_S;

/*�����ݽṹ����AMB_OSPF_PM_NBR���û������ĵ������ֶ�*/
typedef struct tagOSPF_SHOWINFO_NBR
{
    UCHAR ucIpAddr[4];
    ULONG ulAddr_Less_If;
    ULONG ulProcessId;
    UCHAR ucRouterId[4];
    ULONG ulPriority;
    ULONG ulPermanence;
    ULONG ulHello_Suppressed;
    UCHAR ucIf_Ip_Addr[4];
    ULONG ulDead_Time;
    UCHAR ucArea_Id[4];
    ULONG ulState;              /*neighbor state*/
}OSPF_SHOWINFO_NBR_S;

typedef struct tagINET_ADDRESS
{
    UCHAR ucType;
    UCHAR ucLength;
    UCHAR ucPad[2];
    UCHAR ucAddress[OSPF_MAX_INET_ADDR_LEN];
}INET_ADDRESS_S;

/*�����ݽṹ����ospf routing����next-hop�����Ϣ*/
typedef struct tagOSPF_ROUTING_NEXTHOP
{
    ULONG ulOutput_If_Index;
    INET_ADDRESS_S next_hop_inet_addr;
}OSPF_ROUTING_NEXTHOP_S;

/*�����ݽṹ����virtual if���û����ĵ��ֶ�*/
typedef struct tagOSPF_SHOW_VIRTUAL_IF
{
    UCHAR ucAreaId[4];
    UCHAR ucNeighbor[4];
    ULONG ulProcessId;
    ULONG ulTransit_Delay;
    ULONG ulRetrans_Interval;
    ULONG ulHello_Interval;
    ULONG ulRtr_Dead_Interval;
    ULONG ulState;
    ULONG ulAuth_Type;
}OSPF_SHOW_VIRTUAL_IF_S;

/*�����ݽṹ�����û������ĵ�virtual lsdb�е��ֶ�*/
typedef struct tagOSPF_SHOW_VIRTUAL_LSDB
{
    UCHAR uctransit_area_id[4];
    UCHAR ucneighbor[4];
    ULONG ultype;
    UCHAR ucls_id[4];
    UCHAR ucrouter_id[4];
    ULONG ulappl_index;
    ULONG ulsequence;
    ULONG ulage;    
}OSPF_SHOW_VIRTUAL_LSDB_S;

typedef struct tagOSPF_SHOW_VIRTUAL_NBR
{
    UCHAR ucarea_id[4];
    UCHAR ucrtr_id[4];
    ULONG ulappl_index;
    UCHAR ucip_addr[4];
    ULONG ulstate;
    ULONG uldead_time;
}OSPF_SHOW_VIRTUAL_NBR_S;

#define OSPF_FILTER_ALL        0    
#define OSPF_FILTER_PROC       0x01
#define OSPF_FILTER_AREA       0x02
typedef struct tagOSPF_SHOWAREA
{
    USHORT  usFltFlag;/*ȡֵ��Χ:OSPF_FILTER_ALL        0    
                                OSPF_FILTER_PROC       0x01
                                OSPF_FILTER_AREA       0x02*/
    USHORT  usProcessId;       /* Process Id of the process */
    ULONG   ulAreaId;
}OSPF_SHOWAREA_S;

typedef struct tagOSPF_AREA_INFO
{
    ULONG ulAreaId;       /*host liangjicheng 2008-10-28*/
    LONG  lAuthType;
    ULONG ulAuthKeyLen;
    UCHAR ucAuthKeyValue[256]; 
    UCHAR ucAuthKeyId;
    UCHAR ucPad[3];
    /*End for BC3D02736*/
    ULONG ulAuthUserDataLen;
    UCHAR ucAuthUserData[4];   
}OSPF_AREA_INFO_S;

typedef struct tagOSPF_NETWORK
{
    ULONG ulOspfInstance;
    ULONG ulAreaId;
    ULONG ulNetworkAddr;
    ULONG ulNetworkAddrMaskLen;
}OSPF_NETWORK_S;

/*�����ݽṹ����ospf entity mib�й��û���ȡ���ֶ�*/
typedef struct tagOSPF_ENTITY_SHOW
{
    ULONG ulProcessId;             /*OSPFʵ����*/
    UCHAR ucRouter_Id[4];          /*Router id*/
    ULONG ulAdmin_Status;          /*Admin Status 1-up 0-down  */
    ULONG ulOspfVersion;           /*Ospf version*/
    ULONG ulAsbrFlg;               /*Asbr flag*/
    ULONG ulCompRfc1583;           /*����Rfc1583��־ 1-True(����) 0-False*/
    ULONG ulMaxPaths;              /*�ȼ�·����Ŀ*/
    ULONG ulDo_Gr;                 /*Do grace hitless*/
    ULONG ulDo_Gr_Unplanned;       /*Do grace unplanned hitless*/
    ULONG ulGr_Period;             /*Gr period*/
    ULONG ulRestart_Reason;        /*Restart Reason*/
    ULONG ulCalc_Thrsh_Inc_Spf_Upd;/*�������ؼ�������ֵ*/
    ULONG ulOper_Status;           /*����״̬*/
    ULONG ulVrfIndex;
    /*Added by guo00178934, ��Story��ROUTE_DR_023_S_001 ���̲�ѯ���Ĭ��ֵ��ʾ, 2011/5/20   ���ⵥ��:OSPF_20110519_02 */
    ULONG ulCalc_Max_Delay;         /*·�ɼ���ʱ��*/
    ULONG ulOpaque_Lsa_Support;    /*�Ƿ�֧��Opaque LSA*/
    ULONG ulTraffic_Eng_Support;   /*�Ƿ�֧��TE*/
    /* End of Added by guo00178934, 2011/5/20   ���ⵥ��:OSPF_20110519_02 */
    /*Added by guo00178934, SPC200��������Router_ID, 2012/10/17   ���ⵥ��:20121013_1 */
    UCHAR ucCFGRouterId[4];       /*���õ�Router id */
    /* End of Added by guo00178934, 2012/10/17   ���ⵥ��:20121013_1 */
}OSPF_ENTITY_SHOW_S;

/*�����ݽṹ����ospf if metric mib���û������ĵ��ֶ�*/
typedef struct tagOSPF_IF_METRIC_SHOW
{
    UCHAR ucIPAddr[4];             /*address*/
    ULONG ulAddr_Less_If;          /*address less if*/
    ULONG ulTos;                   /*The type of service metric being referenced*/
    ULONG ulProcess_Id;            /*Process Id*/
    ULONG ulValue;                 /*Metric value*/
}OSPF_IF_METRIC_SHOW_S;

/*�����ݽṹ����ospf area mib���û������ĵ��ֶ�*/
typedef struct tagOSPF_SHOW_AREA
{
    UCHAR ucAreaId[4];
    ULONG ulProcessId;

    /*BC3D00572 liangjicheng 2008-10-29 */
    ULONG ulImport_As_Extern; /*1-IMPORT_EXTERNAL 2-IMPORT_NO_EXTERNAL 3-IMPORT_NSSA*/

    /*BC3D00574 liangjicheng 2008-10-29 */
    ULONG ulSummary;          /*1-SEND_AREA_SUMMARY  0-NO_AREA_SUMMARY*/
    
    ULONG ulDefaultlsa;       /*1-DEFAULT_AREA_LSA  0-NO_DEFAULT_AREA_LSA*/    
    /*End for BC3D02758*/
    ULONG ulNssaNoImport;
    
    /* Description: Indicates an NSSA Border router's ability to perform NSSA  */
    /*              translation of type-7 LSAs into type-5 LSAs.               */
    /* 1-ALWAYS  2-CANDIDATE                                                   */
    ULONG ulNssa_Translator_Role;

    /* Description: Indicates if and how an NSSA Border router is performing   */
    /*              NSSA translation of type-7 LSAs into type-5 LSAs.  When    */
    /*              this object set to enabled, the NSSA Border router's       */
    /*              ddrpPmAreaNssaTranslatorRole has been set to always.  When */
    /*              this object is set to elected, a candidate NSSA Border     */
    /*              router is Translating type-7 LSAs into type-5.  When this  */
    /*              object is set to disabled, a candidate NSSA Border router  */
    /*              is NOT translating type-7 LSAs into type-5.                */
    /*1-ENABLED   2-ELECTED  3-DISABLED                                        */
    ULONG ulNssa_Translator_State;

    /* Description: This parameter indicates whether the area can carry data   */
    /*              traffic that neither originates nor terminates in the area */
    /*              itself.  This parameter is calculated when the area's      */
    /*              shortest-path tree is built.                               */
    /* 1-TRUE 2-FASLE                                                          */
    ULONG ulTransitCapability;
    ULONG ulAdmin_Status;
    ULONG ulLsa_Rfsh_Intvl;
    ULONG ulAuthType;                           /*������֤����*/ 
    UCHAR ucAuthKeyId;                          /*������֤Key ID*/  
    UCHAR ucPad[3];
    /*End for BC3D02824*/
    /* Description: The number of LSAs with LS type-1 in this area's Link State Database. */
    ULONG ulRtrLsaCount;
    /* Description: The number of LSAs with LS type-2 in this area's Link State Database.*/
    ULONG ulNetLsaCount;
    /* Description: The number of LSAs with LS type-3 in this area's Link State Database.*/
    ULONG ulSummLsaCount;
    /* Description: The number of LSAs with LS type-4 in this area's Link State Database.*/
    ULONG ulSummAsLsaCount;
    /* Description: The number of LSAs with LS type-7 in this area's Link State Database.*/
    ULONG ulNssaLsaCount;
    /* Description: The number of LSAs with LS type-10 in this area's Link State Database.*/
    ULONG ulOpLsaCount;
    /* Description: The total number of link-state advertisements in this      */
    /*              area's link-state database, excluding AS External LSA's.   */
    ULONG ulLsaCount;
    /* Description: The total number of area border routers reachable within   */
    /*              this area.  This is initially zero, and is calculated in   */
    /*              each SPF Pass.                                             */
    ULONG ulBdrRtrCount;
    /* Description: The total number of Autonomous System border routers       */
    /*              reachable within this area.  This is initially zero, and   */
    /*              is calculated in each SPF Pass.                            */
    ULONG ulAsBdrRtrCount;
    /* Description: The number of times that the intra-area route table  has   */
    /*              been calculated using this area's link-state database.     */
    /*              This is typically done using Dijkstra's algorithm.         */
    ULONG ulSpfRuns;
    /*End of Modified by qinyun62011, 2010/10/27 */
}OSPF_SHOW_AREA_S;

/*�����ݽṹ����ospf area agg���û����ĵ��ֶ�*/
typedef struct tagOSPF_SHOW_AREA_AGG
{
    UCHAR ucAreaId[4];             /*area id*/
    ULONG ulLsdb_Type;             /*Lsdb type*/
    UCHAR ucIpAddr[4];             /*address*/
    UCHAR ucIpMask[4];             /*ip mask*/
    ULONG ulEffect;                /*a flag,indicata advertise or not advertise*/
    ULONG ulProcessId;             /*process id*/
}OSPF_SHOW_AREA_AGG_S;

/* #endif */

/*��ʱ���л���Ϣ*/
typedef struct tagOSPF_SHOW_TIMER_SWITCH
{
  /*��ʼ��ʱ�Ķ�ʱ������*/
  ULONG ulInitTimerType;
  /*��ǰ��ʱ������,Ĭ��ΪDopraʱ�䴦����*/
  ULONG ulCurTimerType;
  /*�л�ǰ�Ķ�ʱ������*/
  ULONG ulOldTimerType;
  /*��ʱ������(�Ժ���Ϊ��λ)*/
  LONG lMSOffset;
  /*�Ƿ���Ҫ����ƫ��*/
  BOOL_T bNeedCalcOffset;
  UCHAR pad[2];
}OSPF_SHOW_TIMER_SWITCH_S;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif 
