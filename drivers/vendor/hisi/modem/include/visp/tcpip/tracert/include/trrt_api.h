/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trrt_api.h
*
*  Project Code: VISPV1R7
*   Module Name: trrt  
*  Date Created: 2008-03-09
*        Author: wuhailan
*   Description: trrt�û�API�ӿ��ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
#ifndef _TRRT_API_H_
#define _TRRT_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define TRRT_VRF_MAX_VRFNAME_LENGTH 31

#ifndef _VRP_IN6ADDR_S
#define _VRP_IN6ADDR_S
typedef   struct    tagVRPIN6Addr
{
    union
    {
        UCHAR   u6_ucaddr[16];
        USHORT  u6_usaddr[8];
        ULONG   u6_uladdr[4];
    } vrp_u6_addr;    /* 128-bit IP6 address */
}VRP_IN6ADDR_S;
#endif


typedef struct tagTrrtCommonParam
{
    /* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05ͳһ������   */
    /* CHAR    *szVrfName;*/ 
    CHAR  szVrfName[TRRT_VRF_MAX_VRFNAME_LENGTH + 1];
    /* End:VISP1.7C03 VRF wangchengyang,2009-02-05   */
    CHAR    *szHostName; 
    ULONG    ulFirstTTL;
    ULONG    ulMaxTTL;
    USHORT   usPort;
    UCHAR    ucPadding[2]; 
    ULONG    ulNQueries;
    ULONG    ulTimeout;
    ULONG    ulSourceAddr;
    ULONG    ulTrrtFlag;         /* TRRT_6  or TRRT4 */
    ULONG    ulVrfFlag ;         /* VRF_YES or VRF_NO*/
    ULONG    ulOutIfIndex;       /* ָ�����ӿڷ���, TRRT4����ָ����һ��Ҳ���Բ�ָ����һ��. ����TRRT6��һ���ͳ��ӿڱ���ͬʱָ��,������Բ�ָ�� */
    ULONG    ulDetectMtu;        /* ·��Mtu̽���� */
    ULONG    ulVrfIndex;         /* VrfIndex,����ͬʱָ��szVrfName��VRFIndex,��szVrfName���ȿ���VRF */
    ULONG    ulNextHopAddr;      /* IPV4��һ��, ָ����һ������ָ�����ӿ� */
    VRP_IN6ADDR_S stSourAddr6;   /* IPV6ָ��Դ��ַ , ������*/
    VRP_IN6ADDR_S stNextHopAddr6;/* IPV6ָ����һ��, ��һ���ͳ��ӿڱ���ͬʱָ��,������Բ�ָ��, ������ */
}TrrtCommonParam;

typedef struct tagTCPIP_TRRT_STAT
{
    ULONG ulInfoID;      /* ��Ϣ���� */
    ULONG ulCode;        /* �ӿڲ��ɴ�����,������Ϣ����ΪTRRT_UNREACHABLEʱʹ�� */
    ULONG ulHops;        /* ���� */
    ULONG ulDstIPAddr;   /* Ŀ�ĵ�ַ��������, ��ping4�����и��ֶ���Ч  */
    ULONG ulHopIPAddr;   /* ��;��ַ, ������  ��ping4�����и��ֶ���Ч  */
    ULONG ulQueryId;     /* ���Դ��� */
    ULONG ulTime;        /* ��ʱ(����) */
    VRP_IN6ADDR_S stDstIPAddr6;  /* Ŀ��IPv6��ַ, ������, ��ping6�����и��ֶ���Ч  */
    VRP_IN6ADDR_S stHopIPAddr6;  /* ��;IPv6��ַ, ������, ��ping6�����и��ֶ���Ч  */
}TCPIP_TRRT_STAT_S;

typedef struct tagTrrtDetectMtuParam
{
    CHAR     szVrfName[TRRT_VRF_MAX_VRFNAME_LENGTH + 1];
    CHAR    *szHostName;         /* ������ */
    ULONG    ulFirstTTL;         /* ��СTTL */
    ULONG    ulMaxTTL;           /* ���TTL,���ܴ���255 */
    USHORT   usPort;             /* Ŀ�Ķ˿ں�(���ڵ���49152)*/
    UCHAR    ucTos;              /* IP�ײ�TOS�ֶ�ֵ */
    UCHAR    ucDspPathDscp;      /* ��ʾ�յ���ICMP�����غ��е�IP�ײ���DSCPֵ��Ϊ0����ʾDSCP��Ϊ1�����DSCP��Ĭ��Ϊ0 */
    ULONG    ulNQueries;         /* ÿ�η��͵ı������ֶ� */
    ULONG    ulTimeout;          /* ��ʱʱ�� */
    ULONG    ulSourceAddr;       /* Դ��ַ�ֶ�(������) */
    ULONG    ulTrrtFlag;         /* TRRT_6 or TRRT_4 */
    ULONG    ulVrfFlag ;         /* VRF_YES or VRF_NO */
    ULONG    ulOutIfIndex;       /* ָ�����ӿڷ���, TRRT4����ָ����һ��Ҳ���Բ�ָ����һ��. ����TRRT6��һ���ͳ��ӿڱ���ͬʱָ��,������Բ�ָ�� */
    ULONG    ulDetectMtu;        /* ·��Mtu̽����, VOS_TRUE:����̽�⹦��  VOS_FALSE:������̽�⹦�� */
    ULONG    ulVrfIndex;         /* VrfIndex,����ͬʱָ��szVrfName��VRFIndex,��szVrfName���ȿ���VRF */
    ULONG    ulNextHopAddr;      /* IPV4��һ��, ָ����һ������ָ�����ӿ� */
    VRP_IN6ADDR_S stSourAddr6;   /* IPV6ָ��Դ��ַ , ������*/
    VRP_IN6ADDR_S stNextHopAddr6;/* IPV6ָ����һ��, ��һ���ͳ��ӿڱ���ͬʱָ��,������Բ�ָ��, ������ */
    struct tagDetectMtu
    {
        ULONG    ulIpaddr;       /* �������,·��MTU���ڽӿ�IP,�����򣬵�ulResult����TRRT_SUC_MTUCHANGE��Ч */
        ULONG    ulPathMtu;      /* �������,̽��·��MTU����ulResult����TRRT_SUC_MTUCHANGE��Ч */
        ULONG    ulResult;       /* �������,̽��·��MTU���صĽ��,����ֵ�ο�enumTrrtMtuErrInf */
    }DETECT_MTU;
}TCPIP_TRRT_DETECTMTU_S;


/*ע��:����޸Ĵ����룬��ͬ���޸�trrt_sh_info.c�ļ��е�CHAR * Inf_Tracert_En[]������Ϣ*/
enum enumTracertErrInf
{ 
    TRRT_SUCESS  = 0,                                   /* 0 */
    TRRT_FAIL    = 1,                                   /* 1 */
    
    TRRT_CREATE_RECSOCKERR,                             /* 2 */
    TRRT_CREATE_SNDSOCKERR,                             /* 3 */                            
    TRRT_UNKNOWN_VPN,                                   /* 4 */
    TRRT_NO_SELECTLOCALADDR,                            /* 5 */
    TRRT_DESTADDR_NOLOCALADDR,                          /* 6 */
    TRRT_UNKNOW_HOST,                                   /* 7 */
    TRRT_OUTOF_MEMORY,                                  /* 8 */
    TRRT_SET_IP_HDRINCLERR,                             /* 9 */
    TRRT_TRACERT_VRFTO,                                 /* 10 */
    TRRT_TRACERT_TO,                                    /* 11 */
    TRRT_TRRT_BEGININFO,                                /* 12 */
    TRRT_PACKET_TOOSHORT,                               /* 13 */
    TRRT_PACKET_RETURNFORM,                             /* 14 */
    TRRT_ICMP_RETURNINFO,                               /* 15 */
    TRRT_SET_IPV6_RECVPKTINFOERR,                       /* 16 */
    TRRT__HOSTNAME_RESLOVED,                            /* 17 */
    TRRT_DESTADDR_UNSPEC,                               /* 18 */
    TRRT_FAIL_LINKLOCAL,                                /* 19 */
    TRRT_FAIL_MCASTADDR,                                /* 20 */
    TRRT_TTL_OUTOFBANK,                                 /* 21 */
    TRRT_UNABLE_SEND,                                   /* 22 */
    TRRT_SEND_DATAINFO,                                 /* 23 */
    TRRT_IPV6_PACKETDUMP,                               /* 24 */
    TRRT_RECEIVE_RESPONSE,                              /* 25 */ 
    TRRT_SET_OPTIONERR,                                 /* 26 */
    TRRT_INVALID_ADDRESS,                               /* 27 */
    TRRT_MINTTL_INVAL,                                  /* 28 */
    TRRT_SET_IPV6_RECVHOPLIMTERR,                       /* 29 */

    TRRT_PARAM_ERR,                                     /* 30 */   
    TRRT_PRINT_TRACE,                                   /* 31 */
    TRRT_PRINT,                                         /* 32 */
    TRRT_PRINT_TTL,                                     /* 33 */
    TRRT_PRINT_TIME,                                    /* 34 */
    TRRT_UNREACH_NOPORT,                                /* 35 */                   
    TRRT_UNREACH_NOROUTE,                               /* 36 */ 
    TRRT_UNREACH_ADDR,                                  /* 37 */ 
    TRRT_UNREACH_ADMIN,                                 /* 38 */              
    TRRT_UNREACH_NOTNEIGHBOR,                           /* 39 */                    
    TRRT_UNREACHABLE,                                   /* 40 */              
    TRRT_UNREACH_HOST,                                  /* 41 */                     
    TRRT_UNREACH_NEEDFRAG,                              /* 42 */                        
    TRRT_PRINT_TIMEOUT,                                 /* 43 */                         
    TRRT_NAME_NULL,                                     /* 44 */                         
    TRRT_NAMELEN_INVALID,                               /* 45 */                       
    TRRT_FLAG_ERR,                                      /* 46 */                            
    TRRT_MINTTL_ERR,                                    /* 47 */                            
    TRRT_MAXTTL_ERR,                                    /* 48 */                            

    TRRT_API_COM_NULL,                                  /* 49 ���Ϊ��*/
    TRRT_API_PARA_WRONG,                                /* 50 �����������*/

    TRRT_NULL_IFNET,                                    /* 51 �Ҳ������ӿ� */
    TRRT_WRONG_IFTYPE,                                  /* 52 ���ӿڲ���֧�ֵ����� */
    TRRT_SET_OUTIFERR,                                  /* 53 ���ó��ӿڴ��� */

    TRRT_VRF_NOT_INIT,                                  /* 54 VRFû�г�ʼ�� */
    TRRT_DETECTMTU_SUCCESS,                             /* 55 ̽��·��MTU�ɹ� */
    TRRT_DETECTMTU_FAIL,                                /* 56 ̽��·��MTUʧ�� */
    TRRT_DETECTMTU_BEGININFO,                           /* 57 ̽��·��MTUINFO��Ϣ */
    TRRT_GETIFBYIP_FAIL,                                /* 58 ����Ŀ��IP���ҳ��ӿ�ʧ�� */
    TRRT_MTUFLAG_WRONG,                                 /* 59 MTU̽���Ǵ��� */

    TRRT_SET_PORTERR,                                   /* 60 ����Ŀ�Ķ˿ںŴ��� */
    
    TRRT_SOURIP_ONLY_GLOBAL,                            /* 61 Դ��ַ��������·���ص�ַ��ಥ��ַ  */
    TRRT_BIND_ERR,                                      /* 62 ��ʧ�� */
    TRRT_NOGLOBALIP,                                    /* 63 ���ӿڲ�����ȫ�򵥲���ַ */
    TRRT_IPV6ADDRCOM_NULL,                              /* 64 ipv6��ַ�齨Ϊ�� */
    TRRT_IPV6_IPCTL_NULL,                               /* 65 ��ȡIPV6���ƿ�ָ��Ϊ�� */
    TRRT_NEXTHOPIP_ONLY_GLOBAL,                         /* 66 ��һ����ַ��������·���ص�ַ��ಥ��ַ */
    TRRT_NHOP_IF_NOTALL,                                /* 67 ���ӿں���һ����ַ����ͬʱָ��,����ָֻ������һ�� */
    TRRT_NHOP_NO_IF,                                    /* 68 ָ�����ӿ�һ��Ҫָ����һ�� */
    TRRT_ERR_IFANDNEXTHOP,                              /* 69 PING4ָ�����ӿں���һ��ʧ�� */
    TRRT_ERR_IFANDNEXTHOP_2,                            /* 70 ��ȡ��һ�������ó��ӿں���һ��ʧ�� */
    TRRT_ERR_IFANDNEXTHOP_3,                            /* 71 ��ȡ���ӿں����ó��ӿں���һ��ʧ�� */
    TRRT_ERR_GETNEXTHOP_BY_FIB,                         /* 72 ��ȡ��һ��ʧ�� */
    TRRT_ERR_GETIFINDEX_BY_FIB,                         /* 73 ��ȡ���ӿ�ʧ�� */
    TRRT_OVER,                                          /* 74 */
    TRRT_SET_PORTRANGE_ERR,                             /* 75 ����TracerouteĿ�Ķ˿ںŷ�Χ����*/
    TRRT_SET_DEFAULTPORT_ERR,                           /* 76 ����TracerouteĬ��Ŀ�Ķ˿ںŴ���*/
    TRRT_MULTI_PTMU_DETECT,                             /* 77 ���·��MTU̽��*/
    TRRT_DROP_PACKET_BYSRCIP,                           /* 78 ͨ��ԴIP���ҳ��ӿڷ��ض��� */
    TRRT_ERR_UNKNOWN_VRF,                               /* 79 ָ�����ӿ���ָ��VRF����� */
    TRRT_PRINT_DSCP,                                    /* 80 TRRT����д�ӡDSCP��Ϣ */
    TRRT_ERR_INVAILD_DSCPFLAG                           /* 81 �������ucDspPathDscp���� */
};
/*ע��:����޸Ĵ����룬��ͬ���޸�trrt_sh_info.c�ļ��е�CHAR * Inf_Tracert_En[]������Ϣ*/

/* ֻ��ʹ��̽��MTUʱ���Ż�Ѹ�ֵ����DETECT_MTU.ulResult�ֶ� */
enum enumTrrtMtuErrInf
{
    TRRT_SUC_MTUCHANGE = 0,                             /* 0 ̽��·��MTU�ɹ������и�С��MTU */
    TRRT_SUC_MTUNOCHANGE,                               /* 1 ̽��·��MTU�ɹ���·������СMTU�ͱ��ӿ�MTUһ�� */
    TRRT_ERR_DETECTMTU,                                 /* 2 ̽��·��MTUʧ�� */
};

typedef VOID (*TCPIP_TRRTOutput_HOOK_FUNC)(CHAR *pstBuf);

/* TraceRouteͳ����Ϣ֪ͨ�ص�����ԭ��, ͳ����Ϣ�ڴ���VISP����, �����������ָ�벻Ϊ��, ����Ҫ��Ʒ�ͷ� */
typedef VOID (*TCPIP_TRRTSTAT_HOOK_FUNC)(TCPIP_TRRT_STAT_S *pstTRRTStat);

/*������ͳ����Ϣ֪ͨ�ص�����ԭ��, ͳ����Ϣ�ڴ���VISP����, �����������ָ�벻Ϊ��, ����Ҫ��Ʒ�ͷ� */
typedef VOID (*TCPIP_TRRTEXSTAT_HOOK_FUNC)(TCPIP_TRRT_STAT_S *pstTRRTStat, ULONG ulExecID);

typedef VOID (*TCPIP_TRRTDETECTMTU_HOOK_FUNC)(ULONG ulMtu);

typedef VOID (*TCPIP_TRRTExOutput_HOOK_FUNC)(ULONG ulExecID,CHAR *pstBuf);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncTRRTOutputHook
*  Description: TRACEROUTE��Ϣ������亯��ע��ӿ�
*        Input: TCPIP_TRRTOutput_HOOK_FUNC pfHookFuc:�ṩ���û�ע���TRRTģ����Ϣ�������ָ��
*       Output: ��
*       Return: VOS_OK�ɹ�,��������ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncTRRTOutputHook(TCPIP_TRRTOutput_HOOK_FUNC pfHookFuc);

/*******************************************************************************
*    Func Name: TCPIP_Traceroute
*  Description: Traceroute���ܺ���
*        Input: TrrtCommonParam *pstTrrtParam:ָ����Ľṹ����Ϣ������ָ��
*       Output: ��
*       Return: �ɹ�����TRRT_SUCESS
*               ʧ�ܷ���enumTracertErrInf �ж���Ĵ�����
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
extern ULONG TCPIP_Traceroute(TrrtCommonParam *pstTrrtParam);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncTRRTStatHook
*  Description: ע��TraceRouteͳ����Ϣ֪ͨ�ص�����
*        Input: TCPIP_TRRTSTAT_HOOK_FUNC pfFunc: �ص�����
*       Output: 
*       Return: TRRT_API_PARA_WRONG���ص�����ָ��Ϊ��
*               VOS_OK������ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2008-10-21  wujie(61195)     Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncTRRTStatHook(TCPIP_TRRTSTAT_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFuncTRRTDetectMtuHook
* Date Created: 2009-03-25
*       Author: zhangchi00142640
*  Description: ע��TraceRouteMtu̽����֪ͨ�ص�����
*        Input: TCPIP_TRRTDETECTMTU_HOOK_FUNC pfFunc: �ص�����
*       Output: 
*       Return: TRRT_API_PARA_WRONG���ص�����ָ��Ϊ��
*               VOS_OK������ɹ�
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2009-03-25   zhangchi00142640        Create
*
*******************************************************************************/
extern ULONG TCPIP_RegFuncTRRTDetectMtuHook(TCPIP_TRRTDETECTMTU_HOOK_FUNC pfFunc);


extern ULONG TCPIP_RegFuncTRRTExOutputHook(TCPIP_TRRTExOutput_HOOK_FUNC pfHookFuc); 



extern ULONG TCPIP_TracerouteEx(ULONG ulExecID,TrrtCommonParam *pstTrrtParam) ;

/*******************************************************************************
*    Func Name: TCPIP_RegFuncTRRTExStatHook
* Date Created: 2009-12-17
*       Author: zhangchunyu(62474)
*  Description: ע��TraceRouteͳ����Ϣ֪ͨ�ص�����
*        Input: TCPIP_TRRTEXSTAT_HOOK_FUNC pfFunc: 
*       Output: 
*       Return: TRRT_API_PARA_WRONG���ص�����ָ��Ϊ��
*               TRRT_SUCESS������ɹ�
*      Caution: ͳ����Ϣ�ڴ���VISP����, �����������ָ�벻Ϊ��, ����Ҫ��Ʒ�ͷ� 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-17    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
ULONG TCPIP_RegFuncTRRTExStatHook(TCPIP_TRRTEXSTAT_HOOK_FUNC pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_TrrtDetectPathMtu
* Date Created: 2010-08-21
*       Author: c168670
*      Purpose: ʵ��Traceroute���ܣ�����̽��·��MTU
*  Description: ʵ��Traceroute���ܣ�����̽��·��MTU
*        Input: ULONG ulExecID: �û�ID<ULONG��Χ>
*               TCPIP_TRRT_DETECTMTU_S *pstTrrtMtuParam: TRRT��̽��MTU����ָ��<�ǿ�>
*       Output: ����̽��MTU���ܣ����DETECT_MTU�ṹ
*       Return: �ɹ�����TRRT_SUCESS
*               ʧ�ܷ���enumTracertErrInf �ж���Ĵ�����
*      Caution: ����ָ��̽��MTU,��Ҫ��̽�⿪��ulDetectMtu��1������ýӿ�ֻʵ��traceroute����
*        Since: V200R003C02
*    Reference: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2010-08-21   c168670        Create the first version.
*
*******************************************************************************/
extern ULONG TCPIP_TrrtDetectPathMtu(ULONG ulExecID, TCPIP_TRRT_DETECTMTU_S *pstTrrtMtuParam);


ULONG TCPIP_TRRT_SetPortRange(USHORT usTrrtMinPort, USHORT usTrrtMaxPort, USHORT usTrrtDefaultPort);


ULONG TCPIP_TRRT_GetPortRange(USHORT *pusTrrtMinPort, USHORT *pusTrrtMaxPort, USHORT *pusTrrtDefaultPort);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* _TRRT_API_H_ */

