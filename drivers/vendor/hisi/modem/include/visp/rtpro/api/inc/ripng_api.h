#ifndef _RIPNG_API_H
#define _RIPNG_API_H

#ifdef  __cplusplus
    extern "C"{
#endif

/*MACRO<RIPNG_Define> */
#ifndef MAX_IF_NAME_LENGTH
#define MAX_IF_NAME_LENGTH              47          /*�ӿ�����󳤶�*/
#endif
#define RIPNG_CFG_ADD                   0           /*�������*/
#define RIPNG_CFG_DEL                   1           /*����ɾ��*/
#define RIPNG_INPUT                     1           /*RIPng���շ���*/
#define RIPNG_OUTPUT                    2           /*RIPng���ͷ���*/
#define RIPNG_MAX_VRFNAME_LENGTH        31          /*VRF ����󳤶�*/
#define RIPNG_MAX_VRF_NAME_LENGTH       31          /*VRF ����󳤶�*/
#define RIPNG_IPV6_ADDRESS_WORD_LEN     16          /*IPV6��ַ�ֽ� 4*4 bytes*/
#define RIPNG_MAX_EQUAL_ROUTE_NUM       32          /*RIPng��ƽ��·�ɺ�ֵ*/
#define RIPNG_MAX_UPDATE_TIMEOUT        255         /*���¶�ʱ��,���ȡֵ255��*/
#define RIPNG_MIN_UPDATE_TIMEOUT        1           /*���¶�ʱ��,��Сȡֵ1��*/
#define RIPNG_DEF_UPDATE_TIMEOUT        30          /*���¶�ʱ��,Ĭ��30��*/
#define RIPNG_MAX_AGE_TIMEOUT           255         /*�ϻ���ʱ�����ȡֵ255*/
#define RIPNG_MIN_AGE_TIMEOUT           1           /*�ϻ���ʱ����Сȡֵ1*/
#define RIPNG_DEF_AGE_TIMEOUT           180         /*�ϻ���ʱ��,Ĭ��180��*/
#define RIPNG_MAX_GARBAGE_TIMEOUT       255         /*�����Ѽ���ʱ�����ȡֵ255*/
#define RIPNG_MIN_GARBAGE_TIMEOUT       1           /*�����Ѽ���ʱ����Сȡֵ1*/
#define RIPNG_DEF_GARBAGE_TIMEOUT       120         /*�����Ѽ���ʱ��,Ĭ��120��*/
#define RIPNG_MAX_PREFERENCE            255         /*RIPNG·�����ȼ����ȡֵ255*/
#define RIPNG_MIN_PREFERENCE            1           /*RIPNG·�����ȼ���Сȡֵ1*/
#define RIPNG_DEF_PREFERENCE            120         /*RIPNG·�����ȼ�,Ĭ��120*/
#define RIPNG_MAX_BALANCE_NUMBER        4           /*���ƽ��·�ɸ���,���ȡֵ4*/
#define RIPNG_MIN_BALANCE_NUMBER        1           /*���ƽ��·�ɸ���,��Сȡֵ1*/
#define RIPNG_DEF_BALANCE_NUMBER        4           /*���ƽ��·�ɸ���,Ĭ��4*/
#define RIPNG_SPLIT_ENABLE_B            0x01        /*����ˮƽ�ָ�ʹ��λ*/
#define RIPNG_POISON_ENABLE_B           0x02        /*���ö�����תʹ��λ*/
#define RIPNG_METRICIN_ENABLE_B         0x04        /*���ý��ո��Ӷ���ֵʹ��λ*/
#define RIPNG_METRICOUT_ENABLE_B        0x08        /*���÷��͸��Ӷ���ֵʹ��λ*/
#define RIPNG_DEF_METRIC_ENABLE_B       0x10        /*����Ĭ��·�ɸ��Ӷ���ֵʹ��λ*/
#define RIPNG_METRIC_INOUT_DEF          0           /*���շ��͸��Ӷ���Ĭ��ֵ*/
#define RIPNG_METRIC_INOUT_MIN          1           /*���շ��͸��Ӷ�����Сֵ*/
#define RIPNG_METRIC_INOUT_MAX          15          /*���շ��͸��Ӷ������ֵ*/
#define RIPNG_DEFAULT_METRIC_DEF        0           /*Ĭ��·�ɸ��Ӷ���Ĭ��ֵ*/
#define RIPNG_DEFAULT_METRIC_MIN        1           /*Ĭ��·�ɸ��Ӷ�����Сֵ*/
#define RIPNG_DEFAULT_METRIC_MAX        15          /*Ĭ��·�ɸ��Ӷ������ֵ*/

/*RIP �շ�����ע�ṳ�Ӻ�������*/
typedef ULONG (*RIPNG_PACKET_HOOK_FUNC)(ULONG ulProcId ,ULONG ulIfIndex, CHAR *pcPacket, ULONG ulLen);


/*STRUCT<RIPNG��������,���16��RIPNG>*/
typedef struct tagRIPNG_CFG_PROC
{ 
    BOOL_T bUndoConfig;  /*RIPNG_CFG_ADD - ����
                           RIPNG_CFG_DEL  - ɾ��*/
    USHORT usProcId;      /*RIPNG��ʵ����ȡֵ��Χ��[1,0xffff]*/
    CHAR   szVrfName[RIPNG_MAX_VRF_NAME_LENGTH + 1]; /*vrf ���ƣ����31�ֽ� ȡֵ��Χ���ǿ�*/
}RIPNG_CFG_PROC_S;

/*STRUCT<RIPNG �Ķ�ʱ�����ýṹ>*/
typedef struct tagRIPNG_CFG_TIMERS 
{ 
    BOOL_T bUndoConfig;  /*RIPNG_CFG_ADD - ����
                           RIPNG_CFG_DEL  - ɾ��*/
    USHORT usProcId;            /*RIPNG��ʵ����ȡֵ��Χ��[1,0xffff]*/
    ULONG  ulUpdateTimeOutVal; /*���¶�ʱ��,Ĭ��30�룬ȡֵ��Χ1-255*/
    ULONG  ulAgeTimeOutVal;    /*�ϻ���ʱ��,Ĭ��180�룬ȡֵ��Χ1-255*/
    ULONG  ulGarbageTimeOutVal;/*�����Ѽ���ʱ��,Ĭ��120�룬ȡֵ��Χ1-255*/
}RIPNG_CFG_TIMERS_S;

/*STRUCT<RIPNG��ƽ��·�ɸ�������>*/
typedef struct tagRIPNG_CFG_MAXLOAD 
{ 
    BOOL_T bUndoConfig;  /*RIPNG_CFG_ADD - ����
                           RIPNG_CFG_DEL  - ɾ��*/
    USHORT usProcId;            /*RIPNG��ʵ����ȡֵ��Χ��[1,0xffff]*/
    USHORT usNumBalancePaths;   /*ƽ��·�ɸ���,Ĭ��4��--ȡֵ��Χ1-4*/
    UCHAR  aucPad[2];           /*��� --*/
}RIPNG_CFG_MAXLOAD_S;

/*STRUCT<RIPNG�Ľӿ�ʹ��>*/
typedef struct tagRIPNG_CFG_ENABLE
{ 
    BOOL_T bUndoConfig;  /*RIPNG_CFG_ADD - ����
                           RIPNG_CFG_DEL  - ɾ��*/
    USHORT usProcId;     /*RIPNG��ʵ����ȡֵ��Χ��[1,0xffff]*/
    UCHAR  szIfName [MAX_IF_NAME_LENGTH + 1];   /*�ӿ���,���47�ֽ�--ȡֵ��Χ���ǿ�*/
}RIPNG_CFG_ENABLE_S; 

/*STRUCT<RIPNG��ʵ����ѯ�ṹ>*/
typedef struct tagRIPNG_PROC_INFO
{  
    USHORT usProcId;            /*RIPNG��ʵ����ȡֵ��Χ��[1,0xffff]*/
    USHORT usMaxBalCount;       /*���ƽ��·�ɸ�����Ĭ��4��--ȡֵ��Χ1-4*/ 
    ULONG  ulVrfIndex;          /*VRF����ֵ--ȡֵ��Χ��0��32Ϊ����*/
    UCHAR  ucUpdateTimeOutVal;  /*ˢ��ʱ��,Ĭ��30�룬--ȡֵ��Χ1-255*/ 
    UCHAR  ucAgeTimeOutVal;     /*�ϻ���ʱʱ��,Ĭ��180�룬--ȡֵ��Χ1-255*/
    UCHAR  ucGarbageTimeOutVal; /*�����Ѽ�ʱ��,Ĭ��120�룬--ȡֵ��Χ1-255*/ 
    UCHAR  ucPad;               /*��� --*/
}RIPNG_PROC_INFO_S;

/*STRUCT<���ڲ�ѯRIPNGʵ���Ĺ�����Ϣ>*/ 
typedef struct tagRIPNG_PROC_FILTER
{
    USHORT usProcId;            /*RIPNG��ʵ����--ȡֵ��Χ��[0,0xffff]*/
    UCHAR  aucPad[2];           /*��� --*/
}RIPNG_PROC_FILTER_S;


/*STRUCT<����·��Ȩֵ�����ýṹ>*/
typedef struct  tagRIPNG_CFG_METRIC 
{ 
    BOOL_T bUndoConfig;    /*RIPNG_CFG_ADD - ����
                             RIPNG_CFG_DEL  - ɾ��*/
    UCHAR  ucMetricVal;                     /*����·��Ȩֵ,Ĭ��ֵΪ0,--ȡֵ��Χ1-15*/
    UCHAR  aucPad;                          /*��� --*/
    UCHAR  szIfName[MAX_IF_NAME_LENGTH + 1];/*ָ���ӿڵĽӿ�������󳤶�47�ֽڡ�--ȡֵ��Χ���ǿ�*/
}RIPNG_CFG_METRIC_S;

/*STRUCT<RIPNG�Ľӿ�����>*/
typedef struct tagRIPNG_IFCFG
{
    BOOL_T bUndoConfig;  /*RIPNG_CFG_ADD - ����
                           RIPNG_CFG_DEL  - ɾ��*/
    UCHAR  aucPad[2];                       /*��� --*/
    UCHAR  szIfName[MAX_IF_NAME_LENGTH + 1];/*RIPNG�Ľӿ��������47�ֽ�--ȡֵ��Χ���ǿ�*/
}RIPNG_IFCFG_S;

/*STRUCT<·�ɵ�Ĭ��costֵ���ýṹ>*/
typedef struct tagRIPNG_CFG_DEFCOST
{ 
    BOOL_T bUndoConfig;  /*RIPNG_CFG_ADD - ����
                           RIPNG_CFG_DEL  - ɾ��*/ 
    USHORT usDefRtMetric;                    /*Ĭ��·�ɵ�Metricֵ,Ĭ��0(��ʾ�ýӿڲ�����RIPng Ĭ��·��),--ȡֵ��Χ1-15*/
    UCHAR  szIfName[MAX_IF_NAME_LENGTH + 1]; /*ָ���ӿڵĽӿ�������󳤶�47�ֽڡ�--ȡֵ��Χ���ǿ�*/
}RIPNG_CFG_DEFCOST_S; 


/*STRUCT<RIP��·�ɱ���>*/
typedef struct tagRIPNG_ROUTE
{ 
    UCHAR  ucDestAddr[RIPNG_IPV6_ADDRESS_WORD_LEN];   /*Ŀ�ĵ�ַ--ȡֵ��Χ���ǿ�*/
    ULONG  ulPrefixLen;                               /*ǰ׺���ȣ�--ȡֵ0-128*/
    UCHAR  ucNextHopAddr[RIPNG_IPV6_ADDRESS_WORD_LEN];/*��һ�������ص�ַ--ȡֵ��Χ���ǿ�*/
    USHORT usAge;                                     /*�ϻ�ʱ��--ȡֵ��Χ��[0,0xffff]*/
    USHORT usMetric;                                  /*����ֵ--ȡֵ��Χ��[0,0xffff]*/
    USHORT usRouteTag;                                /*·�ɱ��--ȡֵ��Χ��[0,0xffff]*/
    USHORT usRouteType;                               /*·������:�ӿ����͡�Э�顢RPI--ȡֵ��Χ��[0,0xffff]*/    
    ULONG ulTimerType; /*��������usAge�ֶΣ���ǰ��Ч�Ķ�ʱ������
                                    0:�ϻ���ʱ��
                                    1:�������ն�ʱ��*/
}RIPNG_ROUTE_S; 

/*STRUCT<���ڲ�ѯ�ھӵĹ�����Ϣ>*/
typedef struct tagRIPNG_ROUTE_FILTER
{
    USHORT usProcId;            /*RIPNG��ʵ����--ȡֵ��Χ��[0,0xffff]*/
    UCHAR  aucPad[2];           /*��� --*/
} RIPNG_ROUTE_FILTER_S; 

/*STRUCT<RIP��һ��·��:����Ŀ�ĵ�ַ����һ����ͬ��·��>*/
typedef struct tagRIPNG_ROUTE_GROUP
{ 
    USHORT usProcessId;                                     /*RIPNG��ʵ����--ȡֵ��Χ��[1,0xffff]*/
    USHORT usRouteNum;                                      /*·����Ŀ --ȡֵ��Χ��[0,0xffff]*/
    RIPNG_ROUTE_S stRipngRoutes[RIPNG_MAX_EQUAL_ROUTE_NUM]; /*·�ɾ�����Ϣ--ȡֵ��Χ���ǿ�*/
} RIPNG_ROUTE_GROUP_S;

/*STRUCT<���ڲ�ѯ�ھӵĹ�����Ϣ>*/
typedef struct tagRIPNG_NBR_FILTER
{
    USHORT usProcId;        /*RIPNG��ʵ����--ȡֵ��Χ��[0,0xffff]*/
    UCHAR  aucPad[2];       /*��� --*/
} RIPNG_NBR_FILTER_S; 

/*STRUCT<RIPNG���ھ���Ϣ>*/
typedef struct tagRIPNG_NBR_INFO 
{   
    ULONG  ulAddressType;                           /*��ַ���� --ȡֵ��Χ��0x00-0x12*/
    ULONG  ulAddressLen;                            /*��ַ����,--ȡֵ��Χ��RIPΪ4��RIPNGΪ16*/
    UCHAR  aucAddress[RIPNG_IPV6_ADDRESS_WORD_LEN]; /*RIPNG�ھӵĵ�ַ--ȡֵ��Χ���ǿ�*/
    ULONG  ulVersion;                               /*�汾��--ȡֵ��Χ��1-2*/
    ULONG  ulRcvBadPackets;                         /*���մ���ı��ĸ���--ȡֵ��Χ��[0,0xffffffff]*/
    ULONG  ulRcvBadRoutes;                          /*���մ����·�ɸ���--ȡֵ��Χ��[0,0xffffffff]*/
    USHORT usProcId;                                /*RIPNG��ʵ����--ȡֵ��Χ��[0,0xffff]*/
    UCHAR  ucPad[2];                               /*����ֶ�*/  
} RIPNG_NBR_INFO_S; 


/*STRUCT<���ڲ�ѯ�ӿ����õĹ�����Ϣ>*/
typedef struct tagRIPNG_INTF_FILTER
{
    USHORT usProcId;        /*RIPNG��ʵ����--ȡֵ��Χ��[0,0xffff]*/
    UCHAR  aucPad[2];       /*��� --*/
} RIPNG_INTF_FILTER_S;

/*STRUCT<�ӿڲ�ѯ��Ϣ�ṹ>*/
typedef struct tagRIPNG_INTF_INFO
{  
    USHORT usProcId;        /*RIPNG��ʵ����--ȡֵ��Χ��[0,0xffff]*/
    UCHAR  ucSend;          /*����״̬--ȡֵ��Χ��[0,1]*/
    UCHAR  ucReceive;       /*����״̬--ȡֵ��Χ��[0,1]*/
    ULONG  ulDefaultMetric; /*Ĭ��·�ɶ���ֵ--ȡֵ��Χ��[0,16]*/
    ULONG  ulIfIndex;       /*�ӿ�����ֵ--ȡֵ��Χ����0��32Ϊ����*/
    UCHAR  ucSplitHorizon;  /*�Ƿ�����ˮƽ�ָ�--ȡֵ��Χ��[0,1]*/
    UCHAR  ucPoisonReverse; /*�Ƿ����ö�����ת--ȡֵ��Χ��[0,1]*/
    UCHAR  ucMetricIn;      /*����·��Ȩֵ ����--ȡֵ��Χ��[0,16]*/
    UCHAR  ucMetricOut;     /*����·��Ȩֵ ���--ȡֵ��Χ��[0,16]*/ 
} RIPNG_INTF_INFO_S;

/*STRUCT<���ڲ�ѯ�ӿ���չ���õĹ�����Ϣ>*/
typedef struct tagRIPNG_INTF_EX_FILTER
{
    ULONG ulIfIndex;        /*�ӿ�����ֵ--ȡֵ��Χ����0��32Ϊ����*/
} RIPNG_INTF_EX_FILTER_S; 


/*STRUCT<һ���ӿ�ֻ������һ��RIP>*/
typedef struct tagRIPNG_INTF_EX_INFO 
{  
    ULONG  ulIfIndex;      /*�ӿ�����ֵ--ȡֵ��Χ����0��32Ϊ����*/  
    USHORT usFlag;         /*�ӿ�����������Ч��־λ--ȡֵ��Χ��[0,1]*/  
    USHORT usDefRtMetric;  /*Ĭ��·�ɵ�Metricֵ,Ĭ��0,--ȡֵ��Χ1-15*/
    UCHAR  ucSplitHorizon; /*�Ƿ�����ˮƽ�ָ�--ȡֵ��Χ��[0,1]*/
    UCHAR  ucPoisonReverse;/*�Ƿ����ö�����ת--ȡֵ��Χ��[0,1]*/
    UCHAR  ucMetricIn;     /*����·��Ȩֵ ����--ȡֵ��Χ��[0,16]*/
    UCHAR  ucMetricOut;    /*����·��Ȩֵ ���--ȡֵ��Χ��[0,16]*/ 
} RIPNG_INTF_EX_INFO_S;

/*STRUCT<RIPNG���˽ӿ�������Ϣ��ѯ����>*/
typedef struct tagRIPNG_CFG_FILTER
{
    USHORT usProcessId;                     /*����ID
                                              ��Χ��0~0xffff��
                                              0�����ڵ����н��̣�
                                              1��0xffff��ָ����RIPNG���̺š�*/
    UCHAR  ucPadding[2];                    /*��� --*/
    ULONG  ulIfIndex;                       /*�ӿ�������Ϊ0��ʾ��ָ���ӿڲ�ѯ--ȡֵ��Χ��32Ϊ����*/
} RIPNG_CFG_FILTER_S;

/*STRUCT<ipv6��ַ�ṹ>*/
typedef struct tagRIPNG_INET6_ADDRESS
{
    UCHAR ucAddress[RIPNG_IPV6_ADDRESS_WORD_LEN]; /*IP6��ַ--ȡֵ��Χ���ǿ�*/
    UCHAR ucPrefixLen;                            /*IP6���볤��--ȡֵ��Χ��[1,128]*/
    UCHAR ucPad[3];                               /*��� --*/  
}RIPNG_INET6_ADDRESS_S;

/*STRUCT<RIPNG�ӿ�������Ϣ��ѯ>*/
typedef struct tagRIPNG_SHOWCFGINTF
{
    CHAR   szIfName[MAX_IF_NAME_LENGTH + 1];      /*�ӿ���--ȡֵ��Χ���ǿ�*/
    RIPNG_INET6_ADDRESS_S ulIpAddr;               /*IP6��ַ--ȡֵ��Χ���ǿ�*/
    ULONG  ulProcessId;                           /*����ID--ȡֵ��Χ��[0,0xffff]*/
    ULONG  ulIfIndex;                             /*�ӿ�����--ȡֵ��Χ����0��32Ϊ����*/
    ULONG  ulDefaultMetric;                       /*Ĭ��·�ɶ���ֵ--ȡֵ��Χ��[0,16]*/
}RIPNG_SHOWCFGINTF_S;

/*STRUCT<RIPNG����ӿ�������Ϣ��ѯ����>*/
typedef struct tagRIPng_RPM_PLCYREDIS
{
    UCHAR  ucProtoType;                     /*    
                                                        #define RM_PROTO_CONNECTED  0x2  
                                                        #define RM_PROTO_STATIC     0x3
                                                        #define RM_PROTO_RIPNG      0x18
                                                        #define RM_PROTO_OSPF6      0x1D
                                                        Э��ID����*/
    UCHAR  ucPadding;                       /*��� --*/
    USHORT usProcessId;                     /*������˵Ľ���ID--ȡֵ��Χ��[0,0xffff]*/
    ULONG  ulMetricVal;                      /*Metricֵ��Ĭ��ֵ1,0 - ������Metricֵ--ȡֵ��Χ��[0,16]*/
} RIPNG_RPM_PLCYREDIST_S;

/*STRUCT<RIPNG���˽ӿ�������Ϣ��ѯ����>*/
typedef struct tagRIPng_RPM_PLCYDIST
{
    USHORT usProcId;                      /*����ID: --ȡֵ��Χ1~65535*/
    UCHAR  ucProtocolId;                  /* �����ԴЭ������
                                                       #define RM_PROTO_CONNECTED  0x2  
                                                       #define RM_PROTO_STATIC     0x3
                                                       #define RM_PROTO_RIPNG      0x18
                                                       #define RM_PROTO_OSPF6      0x1D
                                                       Protocol ID  ���ڽ��չ�����˵��
                                                      ���ֶ���Ч*/
    UCHAR  ucPadding;                     /*��� --*/  
    union
    {
        ULONG ulAclNum;                   /*ACL6�������--ȡֵ��Χ:2000~2999*/
    } stFltrName;
} RIPNG_RPM_PLCYDIST_S;


/*STRUCT<RIPNG�������˽ӿ�������Ϣ��ѯ����>*/
typedef struct tagRIPng_CFGDISTRIBUTE
{
    USHORT bNoFlag;                         /*RIPNG_CFG_ADD - ����
                                              RIPNG_CFG_DEL - ɾ��*/
    USHORT usProcId;                        /*RIPNG��ʵ����ȡֵ��Χ��[1,0xffff]*/
    RIPNG_RPM_PLCYDIST_S stPolicyDist;      /*����/���չ���--ȡֵ��Χ:�ǿ�*/
} RIPNG_CFGDISTRIBUTE_S;

/*STRUCT<RIPNG ·������������ýṹ>*/
typedef struct tagRIPNG_CFG_REDIST
{
    BOOL_T bNoFlag;     /*RIPNG_CFG_ADD - ����
                          RIPNG_CFG_DEL  - ɾ��*/
    USHORT usProcId;                        /*RIPNG��ʵ����ȡֵ��Χ��[1,0xffff]*/ 
    RIPNG_RPM_PLCYREDIST_S stPolicyRedist;  /*����/���չ���--ȡֵ��Χ:�ǿ�*/
}RIPNG_CFG_REDIST_S;



/*STRUCT<���� RIPng �Ľ��չ��˻��߷�������>*/
typedef struct tagRIPng_Cfg_Filter_Info
{
    USHORT bNoFlag;                 /*RIPNG_CFG_ADD - ����
                                      RIPNG_CFG_DEL - ɾ��*/
    USHORT usProcId;               /*RIPNG��ʵ����ȡֵ��Χ��[1,0xffff]*/
    union
    {
        ULONG ulAclNum;            /*ACL6�������--ȡֵ��Χ:2000~2999*/
    } stFltrName;   
} RIPNG_CFG_FILTER_INFO_S;


/*STRUCT<����RIPng ���˲�ѯ������>*/
typedef struct tagRIPng_Plcy_Filter
{
    USHORT usProcId;                 /*����ID
                                              ��Χ��0~65535��
                                              0����ѯ���н��̣�
                                              1��0xffff��ָ����RIPng���̺š�*/
    UCHAR  ucPadding[2];             /*��� --*/ 
} RIPNG_PLCY_FILTER_S;

/*STRUCT<RIPng ������ԵĲ�ѯ��Ϣ>*/
typedef struct tagRIPng_Show_Redist
{
    ULONG  ulProcId;                        /*RIPNG��ʵ����ȡֵ��Χ��[1,0xffff]*/
    RIPNG_RPM_PLCYREDIST_S stReDist;        /*����/���չ���--ȡֵ��Χ:�ǿ�*/
}RIPNG_SHOW_REDIST_S;  


/*STRUCT<RIPng ������˵Ĳ�ѯ��Ϣ>*/
typedef struct tagRIPng_SHOW_EXPORT_FILTER_S
{
    ULONG  ulProcId;                        /*RIPNG��ʵ����ȡֵ��Χ��[1,0xffff]*/
    RIPNG_RPM_PLCYDIST_S stPlcyDist;        /*����/���չ���--ȡֵ��Χ:�ǿ�*/
}RIPNG_SHOW_EXPORT_FILTER_S; 


/*STRUCT<RIPng �Ľ��չ��˲�ѯ��Ϣ>*/
typedef struct tagRIPng_Show_Import_Filter
{
    ULONG  ulProcId;                        /*����ID: --ȡֵ��Χ1~65535*/
    union
    {
        ULONG ulAclNum;                     /*ACL6�������--ȡֵ��Χ:2000~2999*/
    } stFltrName;   
}RIPNG_SHOW_IMPORT_FILTER_S; 


/*STRUCT<RIPng �Ľ��չ��˲�ѯ��Ϣ>*/
typedef struct tagRIPng_Show_Distribute_Filter
{
    ULONG  ulProcId;                      /*RIPNG��ʵ����ȡֵ��Χ��[1,0xffff]*/
    union
    {
        ULONG ulAclNum;                   /*ACL6�������--ȡֵ��Χ:2000~2999*/
    } stFltrName;   
}RIPNG_SHOW_DISTRIBUTE_FILTER_S; 


/*STRUCT<����RIPNG���̵Ĵ���>*/
typedef struct tagRIPNG_CFGPREFERENCE 
{ 
    USHORT bDefFlag;                               /*RIPNG_CFG_ADD - ����
                                                     RIPNG_CFG_DEL - �ָ�Ĭ��ֵ*/
    UCHAR  ucPreference;                            /*���ۣ�Ĭ��ֵ120--ȡֵ��Χ:1~255*/
    UCHAR  ucPadding;                               /*���--*/
    CHAR   szVrfName[RIPNG_MAX_VRF_NAME_LENGTH + 1];/*VRF����--ȡֵ��Χ:�ǿ�*/
}RIPNG_CFGPREFERENCE_S;

/*STRUCT<��ȡRIPNG���̵Ĵ���>*/
typedef struct tagRIPNG_PREFERENCE_SHOW
{
    ULONG  ulVrfIndex;                      /*VRF����--ȡֵ��Χ:��0*/
    UCHAR  ucPreference;                    /*���ۣ�--ȡֵ��Χ:1~255*/
    UCHAR  ucPadding[3];                    /*���--*/  
}RIPNG_PREFERENCE_SHOW_S;




/*******************************************************************************
*    Func Name: RIPng_CFG_Proc
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ����RIPNG ����
*  Description: ����RIPNG ����,֧�ִ����Ľ��̹��Ϊ8
*        Input: RIPNG_CFG_PROC_S *pstCfgInfo:����������Ϣ<�ǿ�>
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش����� 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CFG_Proc(RIPNG_CFG_PROC_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CFG_Timers
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ����RIPNG ��ʱ��ֵ
*  Description: ����RIPNG ��ʱ��ֵ,֧�ֶԸ��¶�ʱ��,�ϻ���ʱ���������ռ���ʱ��������
*        Input: RIPNG_CFG_TIMERS_S *pstCfgInfo:��ʱ��������Ϣ
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش����� 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CFG_Timers(RIPNG_CFG_TIMERS_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CFG_Enable
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: �ӿ���ʹ��RIPng
*  Description: �ӿ���ʹ��RIPng,ͬһ���ӿ���ֻ֧��ʹ�ܰ�ͬһ�����̣���ͬ�ӿ���֧��ʹ�ܰ���ͬ����
*        Input: RIPNG_CFG_ENABLE_S *pstCfgInfo:��������Ϣ
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش����� 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CFG_Enable(RIPNG_CFG_ENABLE_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CFG_MaxLoadBalance
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ����/�ָ�RIPng���ƽ��·������
*  Description: ����/�ָ�RIPng���ƽ��·����������ֵ��RIPng·���·�RTMʱ��Ч
*        Input: RIPNG_CFG_MAXLOAD_S *pstCfgInfo:ƽ��·������������Ϣ
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش����� 
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CFG_MaxLoadBalance(RIPNG_CFG_MAXLOAD_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CMM_Proc_Open
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ȡRIPngʵ����Ϣ��ѯ�ľ��
*  Description: ��ȡRIPngʵ����Ϣ��ѯ�ľ��
*        Input: RIPNG_PROC_FILTER_S *pstDspProcFlt:��������<�ǿ�>
*       Output: ULONG *pulSessionId:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: RIPng_CMM_Proc_GetFirst
*               RIPng_CMM_Proc_GetNext
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CMM_Proc_Open (ULONG *pulSessionId, RIPNG_PROC_FILTER_S *pstDspProcFlt);

/*******************************************************************************
*    Func Name: RIPng_CMM_Handle_Close
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: �ر�RIPng��Ϣ��ѯ�ľ��
*  Description: �ر�RIPng��Ϣ��ѯ�ľ��
*        Input: ULONG ulSessionId:���<�ǿ�>
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CMM_Handle_Close (ULONG ulSessionId);

/*******************************************************************************
*    Func Name: RIPng_CMM_Proc_GetFirst
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ȡ��һ��RIPngʵ����Ϣ
*  Description: ��ȡ��һ��RIPngʵ����Ϣ
*        Input: ULONG ulSessionId:���<�ǿ�>
*       Output: RIPNG_PROC_INFO_S *pstProcInfo:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: RIPng_CMM_Proc_Open
*               RIPng_CMM_Proc_GetNext
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CMM_Proc_GetFirst (ULONG ulSessionId, RIPNG_PROC_INFO_S *pstProcInfo);

/*******************************************************************************
*    Func Name: RIPng_CMM_Proc_GetNext
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: 
*  Description: ��ȡ��һ��RIPngʵ����Ϣ
*        Input: ULONG ulSessionId:
*       Output: RIPNG_PROC_INFO_S *pstProcInfo:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: RIPng_CMM_Proc_Open
*               RIPng_CMM_Proc_GetFirst
*               RIPng_CMM_Handle_Close 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CMM_Proc_GetNext (ULONG ulSessionId, RIPNG_PROC_INFO_S *pstProcInfo);

/*******************************************************************************
*    Func Name: RIPng_ShowProcInfo
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ʾָ��RIPng ʵ����Ϣ
*  Description: ��ʾָ��RIPng ʵ����Ϣ 
*        Input: USHORT usProcId:
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern VOID RIPng_ShowProcInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: RIPng_CFG_MetricIn
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ����RIPng���ո��Ӷ���ֵ
*  Description: ����·�ɶ���ֵ����RIPNG·��ԭ������ֵ�Ļ����������ӵĶ���ֵ����������
*               ������ֱ�Ӹı�·�ɱ���RIPNG·�ɵĶ���ֵ�����ո��Ӷ���ֵ���ڽ���
*               RIPNG·��ʱ���ӵ�һ��Ȩֵ��Ĭ�Ͻ��ո��Ӷ���ֵΪ0��ȡֵ��ΧΪ1~15��
*               �����Ȩ�����ֵ����16��������Ϊ16��
*        Input: RIPNG_CFG_METRIC_S *pstCfgInfo:���ո��Ӷ���ֵ�ṹ<�ǿ�>
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: ����ʱ�ӿڱ������
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CFG_MetricIn(RIPNG_CFG_METRIC_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CFG_MetricOut
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ����RIPng���͸��Ӷ���ֵ
*  Description: ����·�ɶ���ֵ����RIPNG·��ԭ������ֵ�Ļ����������ӵĶ���ֵ����������
*               ������ֱ�Ӹı�·�ɱ���RIPNG·�ɵĶ���ֵ�����͸��Ӷ���ֵ���ڷ���
*               RIPNG·��ʱ���ӵ�һ��Ȩֵ��Ĭ�Ϸ��͸��Ӷ���ֵΪ0��ȡֵ��ΧΪ1~15��
*               �����Ȩ�����ֵ����16��������Ϊ16��
*        Input: RIPNG_CFG_METRIC_S *pstCfgInfo:���͸��Ӷ���ֵ�ṹ<�ǿ�>
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: ����ʱ�ӿڱ������
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_CFG_MetricOut(RIPNG_CFG_METRIC_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CFG_PoisonReverse
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ����RIPng������ת
*  Description: ������ת��RIPNG��ĳ���ӿ�ѧ����·�ɣ�����·�ɵ�Cost���16��
*               Ȼ���ٴӸýӿڷ�����ȥ����������Է�·�ɱ��е�������Ϣ��Ĭ�ϲ������ù��ܡ�
*               ���ͬʱ����ˮƽ�ָ�Ͷ�����ת���ܣ���������ת������Ч��  
*        Input: RIPNG_IFCFG_S *pstCfgInfo:������ת���ýṹ<�ǿ�>
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: ����ʱ�ӿڱ������
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CFG_PoisonReverse(RIPNG_IFCFG_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CFG_SplitHorizon
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ����RIPngˮƽ�ָ�
*  Description: ˮƽ�ָ�����RIPNG��ĳ���ӿ�ѧ����·�ɲ��ٴӸýӿڷ���������·������
*               ����ĳ�̶ֳ��ϱ�����·��ѭ����������������£������ֹˮƽ�ָ�ܣ�
*               ������Ч������ȡ·�ɵ���ȷ������Ĭ������������ù��ܡ����ͬʱ����
*               ˮƽ�ָ�Ͷ�����ת���ܣ���������ת������Ч���ڵ�Ե���·�Ͻ�ֹˮƽ
*               �ָ������Ч�ġ�
*        Input: RIPNG_IFCFG_S *pstCfgInfo:ˮƽ�ָ����ýṹ<�ǿ�>
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: ����ʱ�ӿڱ������
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CFG_SplitHorizon(RIPNG_IFCFG_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CFG_DefaultRouteOrig
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ����Ĭ��·�ɶ���ֵ
*  Description: Ĭ��ֵΪ0���������ⷢ�������˵�Ĭ��·�ɣ������÷�Χ:1~15��һ������
*               �����ⷢ�������˵�Ĭ��·��
*        Input: RIPNG_CFG_DEFCOST_S *pstCfgInfo:Ĭ��·�ɶ���ֵ���ýṹ<�ǿ�>
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: ����ʱ�ӿڱ������
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CFG_DefaultRouteOrig(RIPNG_CFG_DEFCOST_S *pstCfgInfo);

/*******************************************************************************
*    Func Name: RIPng_CMM_Route_Open
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ȡRIPng·����Ϣ��ѯ�ľ��
*  Description: ��ȡRIPng·����Ϣ��ѯ�ľ��
*        Input: RIPNG_ROUTE_FILTER_S* pstDspRouteFlt:
*       Output: ULONG *pulHandle:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_Route_GetFirst
*                 RIPng_CMM_Route_GetNext
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Route_Open(ULONG *pulHandle, RIPNG_ROUTE_FILTER_S* pstDspRouteFlt);

/*******************************************************************************
*    Func Name: RIPng_CMM_Route_GetFirst
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ȡ��һ��RIPng·����Ϣ
*  Description: ��ȡ��һ��RIPng·����Ϣ
*        Input: ULONG ulHandle:
*       Output: RIPNG_ROUTE_GROUP_S *pstRouteInfo:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_Route_Open
*                 RIPng_CMM_Route_GetNext
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Route_GetFirst(ULONG ulHandle, RIPNG_ROUTE_GROUP_S *pstRouteInfo);

/*******************************************************************************
*    Func Name: RIPng_CMM_Route_GetNext
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ȡ��һ��RIPng·����Ϣ
*  Description: ��ȡ��һ��RIPng·����Ϣ
*        Input: ULONG ulHandle:
*       Output: RIPNG_ROUTE_GROUP_S *pstRouteInfo:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_Route_Open
*                 RIPng_CMM_Route_GetFirst
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Route_GetNext(ULONG ulHandle, RIPNG_ROUTE_GROUP_S *pstRouteInfo);

/*******************************************************************************
*    Func Name: RIPng_ShowRouteInfo
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ʾRIPng��·����Ϣ
*  Description: ��ʾRIPng��·����Ϣ
*        Input: USHORT usProcId:
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern VOID RIPng_ShowRouteInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: RIPng_CMM_Nbr_Open
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ȡRIPng�ھ���Ϣ��ѯ�ľ��
*  Description: ��ȡRIPng�ھ���Ϣ��ѯ�ľ��
*        Input: RIPNG_NBR_FILTER_S* pstDspNbrFlt:
*       Output: ULONG *pulSessionId:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_Nbr_GetFirst
*                 RIPng_CMM_Nbr_GetNext
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Nbr_Open(ULONG *pulSessionId, RIPNG_NBR_FILTER_S* pstDspNbrFlt);


/*******************************************************************************
*    Func Name: RIPng_CMM_Nbr_GetFirst
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ȡ��һ��RIPng�ھ���Ϣ
*  Description: ��ȡ��һ��RIPng�ھ���Ϣ
*        Input: ULONG ulSessionId:
*       Output: RIPNG_NBR_INFO_S *pstNbrInfo:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_Nbr_Open
*                 RIPng_CMM_Nbr_GetNext
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Nbr_GetFirst(ULONG ulSessionId, RIPNG_NBR_INFO_S *pstNbrInfo);

/*******************************************************************************
*    Func Name: RIPng_CMM_Nbr_GetNext
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ȡ��һ��RIPng�ھ���Ϣ
*  Description: ��ȡ��һ��RIPng�ھ���Ϣ
*        Input: ULONG ulSessionId:
*       Output: RIPNG_NBR_INFO_S *pstNbrInfo:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_Nbr_Open
*                 RIPng_CMM_Nbr_GetFirst
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Nbr_GetNext(ULONG ulSessionId, RIPNG_NBR_INFO_S *pstNbrInfo);

/*******************************************************************************
*    Func Name: RIPng_ShowNbrInfo
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ʾָ��RIPngʵ�����ھ���Ϣ
*  Description: ��ʾָ��RIPngʵ�����ھ���Ϣ
*        Input: USHORT usProcId:
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern VOID RIPng_ShowNbrInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: RIPng_CMM_Intf_Open
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ȡRIPng�ӿ�������Ϣ��ѯ�ľ��
*  Description: ��ȡRIPng�ӿ�������Ϣ��ѯ�ľ��
*        Input: RIPNG_INTF_FILTER_S* pstDspIntfFlt:
*       Output: ULONG *pulSessionId:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_Intf_GetFirst
*                 RIPng_CMM_Intf_GetNext
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Intf_Open(ULONG *pulSessionId, RIPNG_INTF_FILTER_S* pstDspIntfFlt);

/*******************************************************************************
*    Func Name: RIPng_CMM_Intf_GetFirst
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ȡ��һ��RIPng�ӿ�������Ϣ
*  Description: ��ȡ��һ��RIPng�ӿ�������Ϣ
*        Input: ULONG ulSessionId:
*       Output: RIPNG_INTF_INFO_S *pstIntfInfo:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_Intf_Open
*                 RIPng_CMM_Intf_GetNext
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Intf_GetFirst(ULONG ulSessionId, RIPNG_INTF_INFO_S *pstIntfInfo);

/*******************************************************************************
*    Func Name: RIPng_CMM_Intf_GetNext
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ȡ��һ��RIPng�ӿ�������Ϣ
*  Description: ��ȡ��һ��RIPng�ӿ�������Ϣ
*        Input: ULONG ulSessionId:
*       Output: RIPNG_INTF_INFO_S *pstIntfInfo:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_Intf_Open
*                 RIPng_CMM_Intf_GetFirst
*                 RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_Intf_GetNext(ULONG ulSessionId, RIPNG_INTF_INFO_S *pstIntfInfo);

/*******************************************************************************
*    Func Name: RIPng_ShowIntfInfo
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ʾָ��RIPngʵ����ָ���ӿڵĽӿ�������Ϣ
*  Description: ��ʾָ��RIPngʵ����ָ���ӿڵĽӿ�������Ϣ
*        Input: USHORT usProcId:
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern VOID  RIPng_ShowIntfInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: RIPng_CMM_IntfEx_Open
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ȡRIPng�ӿ���չ������Ϣ��ѯ�ľ��
*  Description: ��ȡRIPng�ӿ���չ������Ϣ��ѯ�ľ��
*        Input: RIPNG_INTF_EX_FILTER_S* pstDspIntfExFlt:��������<Ϊ�ձ�ʾ��ָ������>
*       Output: ULONG *pulHandle:��ѯ���
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: RIPng_CMM_IntfEx_GetFirst
*               RIPng_CMM_IntfEx_GetNext
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_IntfEx_Open(ULONG *pulHandle, RIPNG_INTF_EX_FILTER_S* pstDspIntfExFlt);

/*******************************************************************************
*    Func Name: RIPng_CMM_IntfEx_GetFirst
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ȡ��һ��RIPng�ӿ���չ������Ϣ
*  Description: ��ȡ��һ��RIPng�ӿ���չ������Ϣ
*        Input: ULONG ulHandle:��ѯ���<�ǿ�>
*       Output: RIPNG_INTF_EX_INFO_S *pstIntfExInfo:�ӿ���չ������Ϣ<�ǿ�>
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: RIPng_CMM_IntfEx_Open
*               RIPng_CMM_IntfEx_GetNext
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_IntfEx_GetFirst(ULONG ulHandle, RIPNG_INTF_EX_INFO_S *pstIntfExInfo);

/*******************************************************************************
*    Func Name: RIPng_CMM_IntfEx_GetNext
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ȡ��һ��RIPng�ӿ���չ������Ϣ
*  Description: ��ȡ��һ��RIPng�ӿ���չ������Ϣ
*        Input: ULONG ulHandle:��ѯ���<�ǿ�>
*       Output: RIPNG_INTF_EX_INFO_S *pstIntfExInfo:�ӿ���չ������Ϣ<�ǿ�>
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: RIPng_CMM_IntfEx_GetFirst
*               RIPng_CMM_IntfEx_GetNext
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG  RIPng_CMM_IntfEx_GetNext(ULONG ulHandle, RIPNG_INTF_EX_INFO_S *pstIntfExInfo);

/*******************************************************************************
*    Func Name: RIPng_ShowIntfExInfo
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: ��ʾRIPngָ���ӿڵĽӿ���չ������Ϣ
*  Description: ��ʾRIPngָ���ӿڵĽӿ���չ������Ϣ
*        Input: UCHAR *pszIfName:�ӿ���<�ǿ�>
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern VOID RIPng_ShowIntfExInfo(CHAR *pszIfName);

/*******************************************************************************
*    Func Name: RIPng_Intermediate_Hook_Register
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: RIPng�����շ�����ע�ắ��
*  Description: RIPng�����շ�����ע�ắ�� 
*        Input: ULONG ulDirection:RIPng�ı����շ�����
*               RIPNG_PACKET_HOOK_FUNC pfRipngFwHookFunc:���Ӵ�����
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_Intermediate_Hook_Register(ULONG ulDirection, RIPNG_PACKET_HOOK_FUNC pfRipngFwHookFunc);

/*******************************************************************************
*    Func Name: RIPng_Intermediate_UnHook_Register
* Date Created: 2009-07-03
*       Author: hanna55555
*      Purpose: RIPng�����շ����ӽ�ע�ắ��
*  Description: RIPng�����շ����ӽ�ע�ắ��
*        Input: ULONG ulDirection:RIPng�ı����շ�����
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-07-03   hanna55555              Create
*
*******************************************************************************/
extern ULONG RIPng_Intermediate_UnHook_Register(ULONG ulDirection);

/*******************************************************************************
*    Func Name: RIPng_CMM_CfgIntf_Open
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: ��ȡRIPng�ӿ�������Ϣ�ľ��
*  Description: ����һ��Handle�����ڴ���һ������ȡ�ӿ�������Ϣ
*        Input: RIPNG_CFG_FILTER_S *pstFilterIn:����ID�ͽӿ�����������ϲ�ѯ
*       Output: ULONG *pulHandle:Handle
*       Return: �ɹ�����VOS_OK
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: RIPng_CMM_CfgIntf_GetFirst
*               RIPng_CMM_CfgIntf_GetNext
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   qinyun62011             Create
*
*******************************************************************************/
extern  ULONG RIPng_CMM_CfgIntf_Open(ULONG *pulHandle, RIPNG_CFG_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: RIPng_CMM_CfgIntf_GetFirst
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: ��ȡһ���ӿ�������Ϣ
*  Description: ��ȡһ���ӿ�������Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: RIPNG_SHOWCFGINTF_S *pstIntfIn:�ӿ�������Ϣ
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: RIPng_CMM_CfgIntf_Open
*               RIPng_CMM_CfgIntf_GetNext
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   qinyun62011             Create
*
*******************************************************************************/
extern  ULONG RIPng_CMM_CfgIntf_GetFirst(ULONG ulHandle,RIPNG_SHOWCFGINTF_S *pstIntfIn);
/*******************************************************************************
*    Func Name: RIPng_CMM_CfgIntf_GetNext
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: ��ȡ��һ���ӿ�������Ϣ
*  Description: ��ȡ��һ���ӿ�������Ϣ
*        Input: ULONG ulHandle:Handle
*       Output: RIPNG_SHOWCFGINTF_S *pstIntfIn:�ӿ�������Ϣ
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: RIPng_CMM_CfgIntf_Open
*               RIPng_CMM_CfgIntf_GetFirst
*               RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   qinyun62011             Create
*
*******************************************************************************/
extern  ULONG RIPng_CMM_CfgIntf_GetNext(ULONG ulHandle,RIPNG_SHOWCFGINTF_S *pstIntfIn);
/*******************************************************************************
*    Func Name: RIPng_ShowCfgIntfInfo
* Date Created: 2009-08-04
*       Author: qinyun62011
*      Purpose: ��ʾ�û����õĽӿ���Ϣ
*  Description: ��ʾ�û����õĽӿ���Ϣ
*        Input: USHORT usProcId:����ID,��Χ��0~0xffff��
*               CHAR *szIfName:�ӿ���
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-08-04   qinyun62011             Create
*
*******************************************************************************/
extern  VOID RIPng_ShowCfgIntfInfo(USHORT usProcId,CHAR *szIfName);

/*******************************************************************************
*    Func Name: RIPng_CFG_Redistribute
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ����RIPng �����������
*  Description: RIPng �����������,������������У�ֱ��·�ɡ���̬·�ɡ�OSPFv3·���Լ�RIPng·��
*        Input: RIPNG_CFG_REDIST_S* pstRedistIn: �����������Ϣ
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CFG_Redistribute(RIPNG_CFG_REDIST_S* pstRedistIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_Redist_Open
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: RIPng ����������ò�ѯ��Open����
*  Description: RIPng ����������ò�ѯ��Open������usProcIdΪ0�����ѯ����
*        Input: RIPNG_PLCY_FILTER_S *pstFilterIn: ��ѯ�Ĺ�������
*       Output: ULONG *pulHandle:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_Redist_GetFirst
*                      RIPng_CMM_Redist_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_Redist_Open(ULONG *pulHandle, RIPNG_PLCY_FILTER_S *pstFilterIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_Redist_GetFirst
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ��ѯRIPng ����������õĵ�һ����Ϣ
*  Description: ��ѯRIPng ����������õĵ�һ����Ϣ
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_REDIST_S *pstRedistOut:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_Redist_Open
*                      RIPng_CMM_Redist_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_Redist_GetFirst(ULONG ulHandle, RIPNG_SHOW_REDIST_S *pstRedistOut);

/*******************************************************************************
*    Func Name: RIPng_CMM_Redist_GetNext
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ��ѯRIPng ����������õ���һ����Ϣ
*  Description: ��ѯRIPng ����������õ���һ����Ϣ
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_REDIST_S *pstRedistOut:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_Redist_Open
*                      RIPng_CMM_Redist_GetFirst
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_Redist_GetNext (ULONG ulHandle, RIPNG_SHOW_REDIST_S *pstRedistOut);

/*******************************************************************************
*    Func Name: RIPng_ShowRedistInfo
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ��ʾָ��������������Բ�ѯ��Ϣ
*  Description: ��ʾָ��������������Բ�ѯ��Ϣ
*        Input: USHORT usProcId:ָ����RIPng ����id, 0 ��ʾ��ѯ����
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
VOID RIPng_ShowRedistInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: RIPng_CFG_RouteExportFilter
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ����RIPng ��������ˣ�
*  Description: ����������RIPng��·��������Ե�ACL�������ã��Ƚ���RIPng ·������Ĳ������ú��ٸ��ݸò������ù���������
*        Input: RIPNG_CFGDISTRIBUTE_S* pstExportFilterIn:
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CFG_RouteExportFilter(RIPNG_CFGDISTRIBUTE_S* pstExportFilterIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_ExportFilter_Open
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: RIPng ������˵�open����
*  Description: RIPng ������˵�open������usProcIdΪ0�����ѯ����
*        Input: RIPNG_PLCY_FILTER_S *pstFilterIn:
*       Output: ULONG *pulHandle:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_ExportFilter_GetFirst
*                      RIPng_CMM_ExportFilter_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_ExportFilter_Open(ULONG *pulHandle, RIPNG_PLCY_FILTER_S *pstFilterIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_ExportFilter_GetFirst
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ��ѯRIPng �ĵ�һ��������Ϣ
*  Description: ��ѯRIPng �ĵ�һ��������Ϣ
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_EXPORT_FILTER_S *pstExportInfoOut:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_ExportFilter_Open
*                      RIPng_CMM_ExportFilter_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_ExportFilter_GetFirst(ULONG ulHandle, RIPNG_SHOW_EXPORT_FILTER_S *pstExportInfoOut);

/*******************************************************************************
*    Func Name: RIPng_CMM_ExportFilter_GetNext
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ��ѯRIPng ����һ��������Ϣ
*  Description: ��ѯRIPng ����һ��������Ϣ
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_EXPORT_FILTER_S *pstExportInfoOut:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_ExportFilter_Open
*                      RIPng_CMM_ExportFilter_GetFirst
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_ExportFilter_GetNext (ULONG ulHandle, RIPNG_SHOW_EXPORT_FILTER_S *pstExportInfoOut);

/*******************************************************************************
*    Func Name: RIPng_ShowExportFilterInfo
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ��ѯָ��RIPng �����������Ϣ
*  Description: ��ѯָ��RIPng �����������Ϣ
*        Input: USHORT usProcId:ָ����RIPng ����id, 0 ��ʾ��ѯ����
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
VOID RIPng_ShowExportFilterInfo(USHORT usProcId);


/*******************************************************************************
*    Func Name: RIPng_CFG_RouteImportFilter
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: RIPng���չ���
*  Description: RIPng���չ���,�Խ��յ���·�ɽ���RIPng�Ľ��չ�������
*        Input: RIPNG_CFG_FILTER_INFO_S* pstFilterCfg:
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CFG_RouteImportFilter(RIPNG_CFG_FILTER_INFO_S* pstImportFilterIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_ImportFilter_Open
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: RIPng ���չ��˵�open ����
*  Description: RIPng ���չ��˵�open ������usProcIdΪ0�����ѯ����
*        Input: RIPNG_PLCY_FILTER_S *pstFilterIn:
*       Output: ULONG *pulHandle:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_ImportFilter_GetFirst
*                      RIPng_CMM_ImportFilter_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_ImportFilter_Open(ULONG *pulHandle, RIPNG_PLCY_FILTER_S *pstFilterIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_ImportFilter_GetFirst
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ��ѯRIPng ���չ��˵ĵ�һ����Ϣ
*  Description: ��ѯRIPng ���չ��˵ĵ�һ����Ϣ
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_IMPORT_FILTER_S *pstImportOut:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_ImportFilter_Open
*                      RIPng_CMM_ImportFilter_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_ImportFilter_GetFirst(ULONG ulHandle, RIPNG_SHOW_IMPORT_FILTER_S *pstImportOut);

/*******************************************************************************
*    Func Name: RIPng_CMM_ImportFilter_GetNext
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ��ѯRIPng ���չ��˵���һ����Ϣ
*  Description: ��ѯRIPng ���չ��˵���һ����Ϣ
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_IMPORT_FILTER_S *pstImportOut:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_ImportFilter_Open
*                      RIPng_CMM_ImportFilter_GetFirst
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_ImportFilter_GetNext (ULONG ulHandle, RIPNG_SHOW_IMPORT_FILTER_S *pstImportOut);

/*******************************************************************************
*    Func Name: RIPng_ShowImportFilterInfo
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ��ѯRIPng �Ľ��չ�����Ϣ
*  Description: ��ѯRIPng �Ľ��չ�����Ϣ
*        Input: USHORT usProcId:ָ����RIPng ����id, 0 ��ʾ��ѯ����
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
VOID RIPng_ShowImportFilterInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: RIPng_CFG_RouteDistributeFilter
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ����RIPng��������
*  Description: ����RIPng��������
*        Input: RIPNG_CFG_FILTER_INFO_S* pstDistributeFilterIn:
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CFG_RouteDistributeFilter(RIPNG_CFG_FILTER_INFO_S* pstDistributeFilterIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_DistributeFilter_Open
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ��ѯ RIPng �������˵�open ����
*  Description: ��ѯ RIPng �������˵�open ������usProcIdΪ0�����ѯ����
*        Input: RIPNG_PLCY_FILTER_S *pstFilterIn:
*       Output: ULONG *pulHandle:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_DistributeFilter_GetFirst
*                      RIPng_CMM_DistributeFilter_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_DistributeFilter_Open(ULONG *pulHandle, RIPNG_PLCY_FILTER_S *pstFilterIn);
/*******************************************************************************
*    Func Name: RIPng_CMM_DistributeFilter_GetFirst
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ��ѯRIPng �ĵ�һ������������Ϣ
*  Description: ��ѯRIPng �ĵ�һ������������Ϣ
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_DISTRIBUTE_FILTER_S *pstDistributeOut:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_DistributeFilter_Open
*                      RIPng_CMM_DistributeFilter_GetNext
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_DistributeFilter_GetFirst(ULONG ulHandle, RIPNG_SHOW_DISTRIBUTE_FILTER_S *pstDistributeOut);

/*******************************************************************************
*    Func Name: RIPng_CMM_DistributeFilter_GetNext
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ��ѯRIPng ����һ������������Ϣ
*  Description: ��ѯRIPng ����һ������������Ϣ
*        Input: ULONG ulHandle:
*       Output: RIPNG_SHOW_DISTRIBUTE_FILTER_S *pstDistributeOut:
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش�����
*      Caution: 
*      Reference: RIPng_CMM_DistributeFilter_Open
*                      RIPng_CMM_DistributeFilter_GetFirst
*                      RIPng_CMM_Handle_Close
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
ULONG RIPng_CMM_DistributeFilter_GetNext (ULONG ulHandle, RIPNG_SHOW_DISTRIBUTE_FILTER_S *pstDistributeOut);

/*******************************************************************************
*    Func Name: RIPng_ShowDistributeFilterInfo
* Date Created: 2009-10-15
*       Author: luogaoweil61496
*      Purpose: ��ѯָ��RIPng �ķ���������Ϣ
*  Description: ��ѯָ��RIPng �ķ���������Ϣ
*        Input: USHORT usProcId:ָ����RIPng ����id, 0 ��ʾ��ѯ����
*       Output: 
*       Return: VOID
*      Caution: 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   luogaoweil61496         Create
*
*******************************************************************************/
VOID RIPng_ShowDistributeFilterInfo(USHORT usProcId);

/*******************************************************************************
*    Func Name: RIPng_CFG_Preference
* Date Created: 2009-10-15
*       Author: hanna55555
*      Purpose: ����/�ָ�RIPNG·�����ȼ�
*  Description: ����/�ָ�RIPNG·�����ȼ�
*        Input: RIPNG_CFGPREFERENCE_S* pstPrefIn:RIPNG·�����ȼ�������Ϣ
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش����� 
*      Caution: �ú������ָ��VRFȫ����Ч,������Խ��̵ġ�
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   hanna55555              Create
*
*******************************************************************************/
extern  ULONG RIPng_CFG_Preference(RIPNG_CFGPREFERENCE_S* pstPrefIn);

/*******************************************************************************
*    Func Name: RIPng_CMM_Pref_GetByVrfName
* Date Created: 2009-10-15
*       Author: hanna55555
*      Purpose: ��ȡRIPNG·�����ȼ�
*  Description: ��ȡRIPNG·�����ȼ�
*        Input: CHAR *pszVrfName:VRF����
*               RIPNG_PREFERENCE_SHOW_S *pstPrefIn:RIPNG·�����ȼ���ȡ��Ϣ
*       Output: 
*       Return: �ɹ�����RIP_SUCCESS
*               ʧ�ܷ��ش����� 
*      Caution: �ú������ָ��VRFȫ����Ч,������Խ��̵ġ� 
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   hanna55555              Create
*
*******************************************************************************/
extern  ULONG RIPng_CMM_Pref_GetByVrfName(CHAR *pszVrfName,RIPNG_PREFERENCE_SHOW_S *pstPrefIn);

/*******************************************************************************
*    Func Name: RIPng_ShowPreferenceInfo
* Date Created: 2009-10-15
*       Author: hanna55555
*      Purpose: ��ʾRIPNG·�����ȼ�
*  Description: ��ʾRIPNG·�����ȼ�
*        Input: CHAR *pszVrfName:VRF����
*       Output: 
*       Return: VOID
*      Caution: �ú������ָ��VRFȫ����Ч,������Խ��̵ġ�
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-10-15   hanna55555              Create
*
*******************************************************************************/
extern  VOID RIPng_ShowPreferenceInfo(CHAR *pszVrfName);


#ifdef  __cplusplus
}
#endif

#endif 


