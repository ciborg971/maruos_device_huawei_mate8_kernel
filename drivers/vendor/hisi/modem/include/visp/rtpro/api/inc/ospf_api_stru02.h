/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ospf_api_stru02.h
*
*  Project Code: VISPV1R7C02
*   Module Name: OSPF  
*   Description:
*   01 OSPF API �ṹ����(SGSN�ӿ�����)
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-11-25   liangjicheng             Create                
*  2008-12-23   wangchengyang            modify for statis(error & cumul)
*******************************************************************************/
#ifndef _OSPF_API_STRU02_H
#define _OSPF_API_STRU02_H

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

/*21 �¿����ӿڽṹ��*/

/* Begin BC3D03313 liangjicheng 2010-06-22 ������RTM�ṹһ��*/
/*����/ɾ�� OSPF�������·�ɹ��ˣ������ô�OSPF��RM��·�ɹ���*/
typedef struct tagOSPF_RPM_PLCYDIST
{
    union
    {
        ULONG ulAccNum;         /* Access List Number */
    } stFltrName;
    USHORT  usProcessID;    /* AS Number/Process ID */
    UCHAR   ucProtocolID;    /* Protocol ID */
    UCHAR   ucPadding;
     
    /*Begin BC3D02905 liangjicheng*/
    union
    {        
        ULONG ulAccNum;      /* Next hop Access List Number */        
    } stHopFltrName;
    /*End    BC3D02905 liangjicheng*/
    
} OSPF_RPM_PLCYDIST_S;
/* End   BC3D03313 liangjicheng 2010-06-22 */

#if 101 
typedef struct tagOSPF_SHOWIF
{
    USHORT  usProcessId; 
    USHORT  usPadding;    
}OSPF_SHOWIF_S;

typedef struct tagOSPF_SHOWIF_OUT
{
    ULONG ulAreaId;                             /*01 ����ID*/
    ULONG ulIfIpAddr;                             /*02 ��ַ*/
    ULONG ulIfIpMask;                             /*-- ��ַ����*/
    CHAR  szIfName[OSPF_MAX_IF_NAME_LENGTH + 1];/*03 �ӿ���*/
    ULONG ulIfMetric;                           /*04 �ӿ�COST*/

    /*OSPF�ӿ��������� 1-�㲥 2-NBMA 3-�㵽�� 5-�㵽��� 10 ����*/
    ULONG ulIfNetworkType;                      /*05 ��������*/
    ULONG ulDrPriority;                         /*06 DR���ȼ�*/
    /* no item*/                                /*07 --------*/
    ULONG ulIfState;                            /*08 �ӿ�״̬*/  
    ULONG ulHelloInterval;                      /*09 Hello��� FastHello��Чʱ��Ч*/  
    ULONG ulFastHelloInterval;                  /*-- FastHello��� 0��Ч ������Ч*/
    ULONG ulDeadInterval;                       /*10 Dead���*/ 
    ULONG ulDr;                                 /*11 DR*/ 
    ULONG ulBdr;                                /*12 BDR*/ 
    
    ULONG ulAuthType;                           /*13 �ӿ���Ч����֤����*/ 
    ULONG ulIfCfgAuthType;                      /*-- �ӿ����õ���֤����*/ 

    ULONG ulAuthKeyId;                          /*13 �ӿ���Ч����֤Key Id*/ 
    ULONG ulIfCfgAuthKeyId;                     /*-- �ӿ����õ���֤Key Id*/ 
    /*End for BC3D02736*/

    /* no item*/                                /*14 Smart hello�Ƿ�ʹ��*/
    ULONG ulProcessId;                          /*15 ���̺�*/ 

    ULONG ulPollInterval;                       /*-- ��ѯ���*/ 
    ULONG ulRxmtInterval;                       /*-- LSA�ش�ʱ��*/ 
    ULONG ulInfTransDelay;                      /*-- �ӿڴ�����ʱ*/ 
    ULONG ulIfMtuSize;                          /*-- �ӿ�MTU*/ 

    /*�����ֶ�ΪVISP�����ֶ�*/
    ULONG ulAddrlessif;     
    ULONG ulIfIndex;
    ULONG ulLsaCount;   
    
    /*LSU packet delay for reduce the network traffic Unit:ms Default:100 */
    ULONG ulLSUTransmitDelay; 
    /*������־,��ʱ1ʱ,�ӿڲ��ٽ��շ���Hello���� Ĭ��:0*/
    ULONG ulPassive;
    ULONG ulRemoteIfIndex;
    ULONG ulMtusizePcntge;
    ULONG ulMaxHitlessGracePeriod;
    ULONG ulFastHelloMultiplier;
    ULONG ulMtuIgnoreFlg;
    ULONG ulAdminStatus;
    ULONG ulAutoDelNbrFlag;                         /*Default: 1*/
    ULONG ulGrHelperMode;
    /* add for BC3D02908  */
    ULONG ulAccNum;
    /* end for BC3D02908  */
    /*Added by liubinKF35460, ����һ�������������Ա���, 2011/5/20   ���ⵥ��:OSPF_20110519_01 */
    ULONG ulSupportQos;
    /* End of Added by liubinKF35460, 2011/5/20   ���ⵥ��:OSPF_20110519_01 */
}OSPF_SHOWIF_OUT_S;

#endif

#if 102
typedef struct tagOSPF_SHOWNEIGHBOR
{
    USHORT  usProcessId; 
    USHORT  usPadding;   
}OSPF_SHOWNEIGHBOR_S;

typedef struct tagOSPF_SHOWNBR_OUT_S
{     
    ULONG ulAreaId;                                     /*01 ����ID*/
    ULONG ulIfIpAddr;                                   /*02 �ӿڵ�ַ*/
    ULONG ulNeighborRouterId;                           /*03 �ھ�Router ID*/   
    ULONG ulNeighborIpAddr;                             /*04 �ھӵ�ַ*/
    ULONG ulProcessId;                                  /*05 ����ID*/
    ULONG ulNeighborState;                              /*06 �ھ�״̬*/
    ULONG ulNeighborPriority;                           /*07 �ھ����ȼ�*/
                                       
    CHAR  szIfName[OSPF_MAX_IF_NAME_LENGTH + 1];        /*08 ���ӿ�����*/ 
    ULONG ulInactivityInterval;                         /*09 �ھ�ʧЧ���*/
    ULONG ulNeighbourDR;                                /*10 �ھ�DR*/
    ULONG ulNeighbourBDR;                               /*10 �ھ�BDR*/
    ULONG ulNeighbourGRState;                           /*11 �ھ�BDR*/
    ULONG ulBFDSessionID;                               /*12 �ھ�BFD�ỰID*/

    ULONG ulHelloSuppressed;                            /*-- Hellp ����*/
    /*Neighbor is Dynamical, Peer is static, Here return Dynamical*/
    ULONG ulPermanence;                                 /*-- �ھӶ�̬or��̬*/
    
    ULONG ulNbrLastUpdTime;                           /*�ھӴﵽFULL���뿪FULL֮����ۼ�ʱ�䣬��λ:��*/
    ULONG ulNbrUpDownTimes;                         /*�ھ�UP/DOWN����*/
}OSPF_SHOWNBR_OUT_S;
#endif

#if 103
typedef struct tagOSPF_SHOWROUTING
{
    USHORT  usProcessId; 
    USHORT  usPadding;   
}OSPF_SHOWROUTING_S;


typedef struct tagOSPF_SHOWROUTING_OUT
{
    ULONG ulProcessId;                                  /* NR01*/
    ULONG ulAreaId;                                     /*01 ����ID*/
    ULONG ulDestIpAddr;                                 /*02 Ŀ����·��ַ*/
    ULONG ulDestIpMask;                                 /*03 Ŀ����·��ַ����*/ 
    ULONG ulAdvRouterId;
    
    /* 04 ·������
    0x01 Indicates a path to a destination belonging to one of the router's 
         attached OSPF areas.  
    0x02 Indicates a path to a destination in another OSPF area. 
    0x03 Indicates a path to a destination external to OSPF with a metric
         expressed in the same units as the OSPF internal metric.  
    0x04 Indicates a path to a destination external to OSPF with a metric an order
         of magnitude larger than the OSPF internal metric.  A cost in the type-2
         metric is considered greater than any cost in the type-1 metric. */

    ULONG ulPathCost;                                   /*05 ·������*/   
    ULONG ulType2Cost;                                  /*Only valid for type 2 external paths*/
    
    UCHAR ucPathType;                                   /*04 ·������*/ 
    UCHAR ucOriginType;              /*DCL ��δ���ơ�·����Դ���� 1-RTM����·�� 2-LSA����*/
   
    /*-- ·��Ŀ�ĵ�ַ���� 
    0x01 Area boundary or AS boundary router.    
    0x02 Transit or stub network.    
    0x03 Address range which if active will be a reject route. 
    0x04 Address range corresponding to an NSSA type-7 area aggregation.
    0x05 Route entry used solely for the root of the patricia tree.   */    
    UCHAR ucDestType;    
    UCHAR ucEntryType;                                  /*06 ·��״̬0-Inactive 1-active*/
    
    UCHAR ucRouterEntryFlags; 
    UCHAR ucRouterEntryFlags2;    
    UCHAR ucPadding[2];
    
    ULONG ulExternalRouteTag;
    /***************************************************************************/
    /* External route tag.  This is not used by the OSPF protocol, but         */
    /* external routes with a different external route tag should be           */
    /* considered different, and all should be advertised.                     */
    /***************************************************************************/
    /*UCHAR ucExternal_Route_Tag[4]; Don't use Delete it                       */

    /***************************************************************************/
    /* NextHop Infomation                                                      */
    /***************************************************************************/
    /*--01 The size of the appended next hops. */
    /*ULONG ulNextHopSize;*/     
    /*--02 The number of equal cost paths */
    
    USHORT usNumOfEqualCostPaths;
    USHORT usPadding;                                       
    /*--03 path Infomation*/
    OSPF_ROUTING_NEXTHOP_S stOspfRt[OSPF_MAX_EQCOST_PATH];
}OSPF_SHOWROUTING_OUT_S;
#endif

#if 105
typedef struct tagOSPF_SHOWPEERCFG
{
    USHORT   usProcessId;
    USHORT   usRes;
}OSPF_SHOWPEERCFG_S;
typedef struct tagOSPF_SHOWPEERCFG_OUT
{
    ULONG   ulPeerIpAddr;                   /*01 �ֹ����öԶ˵ĵ�ַ*/
    ULONG   ulProcessId;                    /*02 ����ID*/
    ULONG   ulNbrPriority;                  /*03 �ھ����ȼ�*/
}OSPF_SHOWPEERCFG_OUT_S;
#endif

/*6   �˽ӿ�û�У�����������ʽ���� */
#if 106
typedef struct tagOSPF_SHOWNETWORK
{
    USHORT   usProcessId;
    /*Added for BC3D03465, 2010/8/5 */
    USHORT   usIsAllVRF;
    /*End Added for BC3D03465, 2010/8/5 */
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    UCHAR    szVrfName[OSPF_MAX_VRF_NAME_LENGTH + 1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}OSPF_SHOWNETWORK_S;

typedef struct tagOSPF_SHOWNETWORK_OUT
{
    ULONG   ulAreaId;                       /*01 ����ID*/
    ULONG   ulIpAddr;                       /*02 ��ַ*/
    ULONG   ulIpMask;                       /*03 ��ַ����*/
    ULONG   ulProcessId;                    /*04 ����ID*/
    /*Added for BC3D03465, 2010/8/5 */
    ULONG   ulVrfIndex;                     /*05 VrfIndex */
    /*End for BC3D03465, 2010/8/5 */
}OSPF_SHOWNETWORK_OUT_S;

#endif

#if 107
typedef struct tag_OSPF_SHOWOSPF_BRIEF
{
    USHORT   usProcessId;       /* Process Id of the process */
    USHORT   usRes;
}OSPF_SHOWOSPF_BRIEF_S;

typedef struct tag_OSPF_SHOWOSPF_BRIEF_OUT
{
    ULONG   ulRouterId;         /*01 RouterId for this process */
    USHORT  usProcessId;        /*02 Process Id for the process */
    UCHAR   ucPreferenceINT;
    UCHAR   ucPreferenceEXT;
    ULONG   ulExternLsaCount;
    ULONG   ulOriginateNewLsaCount;
    ULONG   ulRxNewLsaCount;
    ULONG   ulExtLsaRfshIntvl;
    ULONG   ulAsbrFlg;          /*Asbr flag*/
    ULONG   ulCompRfc1583;      /*����Rfc1583��־ 1-True(����) 0-False*/
    ULONG   ulDoGrHitless;           /*Do grace hitless*/
    ULONG   ulDoGrUnplannedHitless;  /*Do grace unplanned hitless*/
    ULONG   ulHitlessGrPeriod;       /*Gr period*/
    ULONG   ulHitlessRestartReason;  /*Restart Reason*/
    ULONG   ulCalcThrshIncSpfUpd;    /*�������ؼ�������ֵ*/
    ULONG   ulFastDownFlag;          /* ����down��� for CGP BC3D02904*/
    /*Add for BC3D02970 ���VrfIndex*/
    ULONG   ulVrfIndex;
    /*End for BC3D02866*/

    /*Add for BC3D03437 at 2010-07-16*/
    ULONG ulHelperMode;
    ULONG ulGrPeriod;
    ULONG ulAccNum;
    /*End for BC3D03437 at 2010-07-16*/
    ULONG   ulCFGRouterId;      /*���õ�Router ID */
}OSPF_SHOWOSPF_BRIEF_OUT_S;
#endif

#if 108
typedef struct tagOSPF_SHOWCUMLTVE
{
    USHORT  usProcessId;
    USHORT  usRes;
}OSPF_SHOWCUMLTVE_S;

typedef struct tagOSPF_SHOWCUMLTVE_OUT
{
    ULONG  ulRouterId;
    USHORT usProcessId;
    USHORT usPadding;/*������չ*/
    /* Begin:added by wangchengyang,2008-12-23 */
    
    /* packets stat. */
    ULONG  ulInHello;              /* input hello pkts */
    ULONG  ulOutHello;
    ULONG  ulInDbDescr;            /* input DB Description */
    ULONG  ulOutDbDescr;   
    ULONG  ulInLinkStateReq;       /* input Link-State Req */
    ULONG  ulOutLinkStateReq;  
    ULONG  ulInLinkStateUpdate;    /* Input Link-State Update */
    ULONG  ulOutLinkStateUpdate;
    ULONG  ulInLinkStateAck;       /* Link-State Ack  */
    ULONG  ulOutLinkStateAck;

    /* LSAs originated by this router  */
    ULONG  ulRouter;
    ULONG  ulNetwork;
    ULONG  ulSumNet;
    ULONG  ulSumAsbr;
    ULONG  ulExternal;
    ULONG  ulNssa;
    ULONG  ulOpqLink;
    ULONG  ulOpqArea;
    ULONG  ulOpqExternal;
    ULONG  ulOriginateNewLsas;
    ULONG  ulRxNewLsas;

    ULONG  ulAreaBdr;    /* Area �߽�·���� */
    ULONG  ulAsBdr;      /* as �߽�·���� */
    /* End:wangchengyang 2008-12-23 */

    ULONG  ulMaxAgeLsaNoImport;    /*OSPF ����·��ɾ����ɵ� MAX-AGE LSA ����*/
    ULONG  ulMaxAgeLsaTimer;       /*3600�뵽ʱ MAX-AGE LSA ����*/
    ULONG  ulMaxAgeLsaTotal;       /*����flush��LSA������*/

    /*Added by guojianjun178934, ���OSPF NSR������ʱ������Ϣ, 2013/4/7   ���ⵥ��:20130118_01 */
    ULONG  ulRestoreTime;
    ULONG  ulRestoreUnpacketTime;
    ULONG  ulRestorePacket;
    /* End of Added by guojianjun178934, 2013/4/7   ���ⵥ��:20130118_01 */
}OSPF_SHOWCUMLTVE_OUT_S;
#endif

#if 109
typedef struct tagOSPF_SHOWERROR
{
    USHORT   usProcessId;   /* Process Id of the process */
    USHORT   usRes;
}OSPF_SHOWERROR_S;

typedef struct tagOSPF_SHOWERROR_OUT
{    
    USHORT   usProcessId;   /* Process Id of the process */
    USHORT   usRes;
    ULONG ulBadVersion;         /* �汾��ƥ�� */
    ULONG ulAreaMismatch;       /* ����Ų�ƥ��*/
    ULONG ulUnknownNbmaNbr;     /* δ֪NBMA�����ھ�*/
    ULONG ulUnknownVirtualNbr;  /* δ֪���ھ� */
    ULONG ulAuthTypeMismatch;   /* ��֤���Ͳ�ƥ�� */
    ULONG ulAuthKeyIdMismatch;  /* ��֤KeyID��ƥ�� */
    ULONG ulAuthFailure;        /* ��֤ʧ�� */
    ULONG ulNetmaskMismatch;    /* ���벻ƥ�� */
    ULONG ulHelloInterval;      /* HelloInterval��ƥ�� */
    ULONG ulDeadInterval;       /* DeadInterval��ƥ�� */
    ULONG ulOptionMismatch;     /* ѡ��λ��ƥ�� */
    ULONG ulMtuMismatch;        /* MTU��ƥ�� */
    ULONG ulDuplicateRouterId;  /* RouterID�ظ� */
    ULONG ulBadPacket;          /* ������������packet drop */
}OSPF_SHOWERROR_OUT_S;
#endif

#if 110
typedef struct tagOSPF_RPM_PLCYREDIS
{
    UCHAR   ucRPAID;
    UCHAR   ucPadding;
    USHORT  usRPAProcessID;
    ULONG   enMetricType;
    ULONG   ulMetricVal;
} OSPF_RPM_PLCYREDIS_S;
 
typedef struct tagOSPF_SHOWIMPORT
{
    USHORT   usProcessId;
    USHORT   usRes;
}OSPF_SHOWIMPORT_S;

typedef struct tagOSPF_SHOWIMPORT_OUT
{
    ULONG   ulProcessId;
    OSPF_RPM_PLCYREDIS_S stReDis;
}OSPF_SHOWIMPORT_OUT_S;
#endif

#if 111

typedef struct tagOSPF_SHOWPLCYDIST
{
    USHORT   usProcessId;
    USHORT   usRes;
}OSPF_SHOWPLCYDIST_S;

typedef struct tagOSPF_SHOWPLCYDIST_OUT
{
    USHORT  usProcessId;
    CHAR    ucPadding[2];
/*#define DF_OSPF_TO_RM 1
#define DF_RM_TO_OSPF 2*/
    ULONG   ulPlcyDirectFlag;
    OSPF_RPM_PLCYDIST_S stPlcyDist;
}OSPF_SHOWPLCYDIST_OUT_S;
#endif

#if 201 
            
typedef struct tagOSPF_CFGREDISTRIBUTE
{
    USHORT bNoFlag;
    USHORT usProcessId;
    OSPF_RPM_PLCYREDIS_S stPolicyRedist;
}OSPF_CFGREDISTRIBUTE_S;
#endif

#if 202
typedef struct tagOSPF_CFGDISTRIBUTE
{
    USHORT bNoFlag;
    USHORT usProcessId;
    OSPF_RPM_PLCYDIST_S stPolicyDist;
}OSPF_CFGDISTRIBUTE_S;
#endif

#if 203
/*Notes:�μ�ospf_api.h�ṹ*/
#endif

#if 204
/*Notes:�μ�ospf_api.h�ṹ*/
typedef struct tagOSPF_CFGIF_NETTYPE
{
    CHAR  szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    UCHAR  bNoFlag;
    UCHAR  ucNetworkType;
    UCHAR ucPadding[2]; 
}OSPF_CFGIF_NETTYPE_S;

typedef struct tagOSPF_CFGIF_HELLO
{
    CHAR  szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    USHORT usHelloInterval;
    USHORT bNoFlag;        /*1���ã�0�ָ�Ĭ��ֵ 10*/                  
}OSPF_CFGIF_HELLO_S;

typedef struct tagOSPF_CFGIF_DEAD
{
    CHAR  szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    USHORT usDeadItvl;
    USHORT bNoFlag;        /*0���ã�1�ָ�Ĭ��ֵ 40*/   
    
    /*������ʹ��fast hello��1s�ڷ���hello���ĵ���Ŀ Range<3-20> Default 5*/
    ULONG ulFast_Hello_Multiplier;
                             
}OSPF_CFGIF_DEAD_S;

typedef struct tagOSPF_CFGIF_RETRANSMIT
{
    CHAR szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    USHORT usRetransInterval;
    UCHAR bNoFlag;
    UCHAR ucPadding[1];
}OSPF_CFGIF_RETRANSMIT_S;

typedef struct tagOSPF_CFGIF_PRIORITY
{
    CHAR szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    UCHAR bNoFlag;
    UCHAR  ucPriority;
    UCHAR ucPadding[2];
}OSPF_CFGIF_PRIORITY_S;

typedef struct tagOSPF_CFGIF_COST
{
    CHAR  szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    ULONG  ulIfCost;  /*Interface Metric [1-65535] default:1*/
    USHORT bNoFlag;   /*0-Set 1-Recover default */
    UCHAR ucPadding[2];
}OSPF_CFGIF_COST_S;
#endif

/*#endif*/
#if 22  /*22*/

#if 205
/*Notes:ospf_api.h ���ڲ�һ�µĽṹ*/
typedef struct tagOSPF_CFGIFAUTHKEY
{
    CHAR  szIfName[OSPF_MAX_IF_NAME_LENGTH+1];
    USHORT bNoFlag;
/*
#define OSPF_CFG_IF_AUTH_NULL         0x0
#define OSPF_CFG_IF_AUTH_SIMPLE       0x01
#define OSPF_CFG_IF_AUTH_MD5          0x02
#define OSPF_CFG_IF_AUTH_HMAC         0x03*/
    UCHAR  ucAuthenType;
    
/*
#define OSPF_IF_P***W***_PLAIN        0x01
#define OSPF_IF_P***W***_CIPHER       0x02*/
    UCHAR  ucPasswordType;

    CHAR  szPassword[OSPF_ENCRYPT_DATA_LENGTH+1];
    UCHAR  ucKeyId;
    UCHAR  ucPadding[3];
}OSPF_CFGIFAUTHKEY_S;

typedef struct tagOSPF_CFGAUTHENMODE
{
    USHORT bNoFlag;
    USHORT usProcessId;
    ULONG  ulAreaId;
    CHAR  szPassword[OSPF_ENCRYPT_DATA_LENGTH + 1];
    UCHAR  ucKeyId;

/*  #define OSPF_CFG_IF_AUTH_NULL         0x0
    #define OSPF_CFG_IF_AUTH_SIMPLE       0x01
    #define OSPF_CFG_IF_AUTH_MD5          0x02 
    #define OSPF_CFG_IF_AUTH_HMAC         0x03  */
    UCHAR  ucAuthenType;

/*  #define OSPF_AREA_P***W***_PLAIN    0x01
    #define OSPF_AREA_P***W***_CIPHER   0x02 */      
    UCHAR  ucPasswordType;
    UCHAR  ucPadding;
}OSPF_CFGAUTHENMODE_S;

#endif

#if 206        
typedef struct tagOSPF_CFGPREFERENCE
{
    USHORT bNoFlag;
    /*USHORT usProcessId;    */ /*����id ���ṩ */
    UCHAR  ucINTPreference;
    UCHAR  ucEXTPreference;
/*
#define OSPF_PREFERENCE_SWITH_INT        0x01
#define OSPF_PREFERENCE_SWITH_EXT        0x02
*/
    UCHAR  ucSwitch;
    UCHAR  ucPadding;
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    CHAR szVrfName[OSPF_MAX_VRF_NAME_LENGTH + 1];
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
}OSPF_CFGPREFERENCE_S;
#endif   

#if 207
/*�����ݽṹ��������NSSA����*/
typedef struct tagOSPF_CFGAREANSSA
{
    USHORT bNoFlag; /*�����Ƿ��һ���������ó�nssa,0-���� 1-�ָ���ͨ����*/
    USHORT usProcessId;                 /*����id*/
    ULONG  ulAreaId;                    /*����ID*/
/*
#define OSPF_CFG_NSSAOPT_DEFAULT    0x01  DCL��֧�� bring default Type-7LSA to area NSSA   
#define OSPF_CFG_NSSAOPT_NOIMPORT   0x02  no import exterior route to NSSA area 
#define OSPF_CFG_NSSAOPT_NOSUMMARY  0x04  forbid ABR send Summary LSA to NSSA area 
#define OSPF_CFG_NSSAOPT_TRANSLATE_ROLE_ALWAYS  0x08  forbid NSSA area import route*/
    UCHAR  ucNssaOption;                /*NSSA option*/
    UCHAR  ucRes[3];                     /*���λ*/
}OSPF_CFGAREANSSA_S;
#endif

/*�����ݽṹ�������ý��̵ļ����ӳ�*/
typedef struct tagOSPF_CFGCALCDELAY
{
    USHORT usProcessId; 
    USHORT usPadding; 
    ULONG ulCaclDelay;  /*·�ɼ��������ʱ���(ms)��Ĭ��ֵ2000��ȡֵ��Χ��1~10000*/
}OSPF_CFGCALCDELAY_S;

#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif 
