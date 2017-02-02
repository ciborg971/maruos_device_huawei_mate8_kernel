/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dns_api.h
*
*  Project Code: VISPV1R7
*   Module Name: dns
*  Date Created: 2008-03-09
*        Author: wuhailan
*   Description: dns�û�API�ӿ��ļ�,��ͷ�ļ��漰��IPV6�ĵ�ַ���ݽṹVRP_IN6ADDR_S,��Ҫ�Ȱ���IPV6ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-03-09   wuhailan                Create
*
*******************************************************************************/
/**
*@defgroup dnsclient DNS_CLIENT
*@ingroup app
*/

#ifndef _DNS_API_H_
#define _DNS_API_H_


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 *@ingroup dnsclient
 *@brief DNS CLIENT�궨��
 *@{
*/
#ifndef DNS_DOMAIN_LIST_NAME_LENGTH
#define DNS_DOMAIN_LIST_NAME_LENGTH 20  /**< �����б�����������󳤶� */
#endif

/*
����rfc882�ĵ�������������:
To simplify implementations, the total number of octets that
represent label octets and label lengths is limited to 255.  Thus
a printed domain name can be up to 254 characters.

����VISP֧��DNS������󳤶�Ϊ254
*/
#define DNS_DOMAIN_NAME_LENGTH 254  /**< ������󳤶� */

#define DNS_DOMAIN_LIST_NUM         10  /**< �����б��������������� */

#define DNS_DOMAIN_SERVER_NUM        6  /**< ������������������ */

#define DNS_MAX_INTERFACE_NAME_LEN  47  /**< �ӿ�������,��MAX_INTERFACE_NAME_LENֵһ��,���иĶ���Ҫͬ������*/

/*����DNS������������ʹ�õĺ�ֵ*/
#define DNS_ADD_SERVER_IP      0  /**< ��ʾ����ָ��������������ַ */
#define DNS_DEL_SERVER_IP      1  /**< ��ʾɾ��ָ��������������ַ */
#define DNS_DEL_ALL_SERVER_IP  2  /**< ��ʾɾ��ȫ��������������ַ */
/**@}*/

/**
 *@ingroup dnsclient
 *@brief IPv6��ַ
*/
#ifndef _VRP_IN6ADDR_S
#define _VRP_IN6ADDR_S
typedef struct tagVRPIN6Addr
{
    union
    {
        UCHAR   u6_ucaddr[16];
        USHORT  u6_usaddr[8];
        ULONG   u6_uladdr[4];
    } vrp_u6_addr;    /* 128-bit IP6 address */
}VRP_IN6ADDR_S;
#endif

/**
 *@ingroup dnsclient
 *@brief DNS������Ϣ��IPV6��صĽṹ��Ϣ��
*/
typedef struct tagTCPIP_IPV6_DNS_SERVADDRINFO
{
    VRP_IN6ADDR_S stIpAddr;
    ULONG         ulIfIndex;
    CHAR          szInterfaceName[DNS_MAX_INTERFACE_NAME_LEN + 1];
}TCPIP_IPV6_DNS_SERVADDRINFO_S;

/*dns������Ϣ�ṹ,��DomainInfo_S�ṹһ�£������޸ģ�Ҫ��ͬ���޸�*/
/**
 *@ingroup dnsclient
 *@brief DNS������Ϣ�ṹ
*/
typedef struct  tagTCPIP_DomainInfo
{
     ULONG  ulDomainServer[DNS_DOMAIN_SERVER_NUM];
     TCPIP_IPV6_DNS_SERVADDRINFO_S stDomainServer6[DNS_DOMAIN_SERVER_NUM];
     CHAR   szDomainList[DNS_DOMAIN_LIST_NUM][DNS_DOMAIN_LIST_NAME_LENGTH + 1];
     UCHAR  ucPadding[2];
}TCPIP_DomainInfo_S;


/*dnsģ������붨��*/
/*ע��:����޸Ĵ����룬��ͬ���޸�dns_sh_info.c �ļ��е�CHAR *Inf_Dnsc_En[]������Ϣ*/
/**
 *@ingroup dnsclient
 *@brief DNS CLIENT������
*/
enum enum_DnsErr_INFO
{
    /* success */
    DNSC_SUCCESS       = 0,                  /**< 0 �ɹ�*/

    /* error code */
    DNS_INVALID_V4_ADDR,                     /**< 1 ��Ч��IPV4��������ַ */
    DNS_INVALID_V6_ADDR,                     /**< 2 ��Ч��IPV6��������ַ */
    DNS_UNSPECIFIED_ADDR,                    /**< 3 */
    DNS_MULTICAST_ADDR,                      /**< 4 */
    DNS_NO_DOMAIN_SERVER,                    /**< 5 */
    DNS_ILLEGAL_V6_SERVER_ADDR,              /**< 6 */
    DNS_ILLEGAL_INTF_NAME,                   /**< 7 */
    DNS_TOO_MANY_SERVERS,                    /**< 8 */
    DNS_EXISTING_SERVER,                     /**< 9 */
    DNS_SPECIFY_INTF_NAME,                   /**< 10 */
    DNS_INVALID_INTF_NAME,                   /**< 11 */
    DNS_INVALID_DOMAIN_NAME,                 /**< 12��������Ч�����ܹ����򳤶�Ϊ0���зǷ��ַ� */
    DNS_NO_DOMAIN_NAME,                      /**< 13 */
    DNS_TOO_MANY_DOMAINS,                    /**< 14 */
    DNS_EXISTING_DOMAIN,                     /**< 15 */

    /* info code */
    DNS_V4_SERVERS,                          /**< 16 */
    DNS_DOMAIN_SERVER,                       /**< 17 */
    DNS_IP_ADDR,                             /**< 18 */
    DNS_NO_SERVERS,                          /**< 19 */
    DNS_V6_SERVERS,                          /**< 20 */
    DNS_IPv6_ADDR,                           /**< 21 */
    DNS_INTF_NAME,                           /**< 22 */
    DNS_NO,                                  /**< 23 */
    DNS_DOMAIN_NAME,                         /**< 24 */
    DNS_TTL,                                 /**< 25 */
    DNS_ALIAS,                               /**< 26 */
    DNS_STOP_SEARCH,                         /**< 27 */
    DNS_TRY_SERVER,                          /**< 28 */
    DNS_NO_FIRST,                            /**< 29 */

    /**< error code */
    DNS_NULL_POINTER,                        /**< 30, ��ָ�����. */
    DNS_ERR_WAITLIST,                        /**< 31, ��waitlist register/unregister����ʧ��*/
    DNS_ERR_SETWAITLIST,                     /**< 32, ��waitlist SET����ʧ��*/
    DNS_ERR_GETWAITLIST,                     /**< 33, ��waitlist GET����ʧ��*/
    DNS_LEN_DOMAIN_NAME,                     /**< 34��������Ч,��������*/
    DNS_LEN_INTF_NAME,                       /**< 35��IFNET���ֹ���*/
    DNS_ADD_IPV6_INTF_NAME,                  /**< 36������ ipv6 Domain Setver��ַ���Ϸ�*/
    DNS_DEL_IPV6_INTF_NAME,                  /**< 37��ɾ�� ipv6 Domain Setver��ַ���Ϸ�*/
    DNS_V6_TOO_MANY_SERVERS,                 /**< 38��IPV6 ����������*/
    DNS_V4_TOO_MANY_SERVERS,                 /**< 39��IPV4 ����������*/
    DNS_TOO_MANY_SERVERS_FORLINT,            /**< 40��IPV4 ���������� for pclint*/
    DNS_DEL_V6_NO_DOMAIN_SERVER,             /**< 41,  ɾ��V6 DOMAIN SEVER������*/
    DNS_V6_EXISTING_SERVER,

    DNS_API_COM_NULL,                        /**< 43, DNS���Ϊ��*/
    DNS_API_PARA_WRONG,                      /**< 44, �����������*/
    DNS_API_POINTER_NULL,                    /**< 45, ָ�����Ϊ��*/

    DNS_LEN_DOMAIN_LABEL,                    /**< 46, ����Label���� */
    DNS_API_IPV6ADDR_WRONG = 47,             /**< 47, ����IPv6��ַ����*/
    DNS_API_IPV4ADDR_WRONG,                  /**< 48, ����IPv4��ַ����*/
};
/*ע��:����޸Ĵ����룬��ͬ���޸�dns_sh_info.c �ļ��е�CHAR *Inf_Dnsc_En[]������Ϣ*/

/* ����DNS server IP��ַ��ȡ��Ҫ�󶨵�ԴIP��ַ, server IP��ַ��ԴIP��ַ��Ϊ������ */
/**
 *@ingroup dnsclient
 *@brief ����DNS server IP��ַ��ȡ��Ҫ�󶨵�ԴIP��ַ���Ӻ�����
 *
 *@par ����:
 *�ڷ���DNS������ʱ������DNS server IP��ַ��ȡ��Ҫ�󶨵�ԴIP��ַ���Ӻ�����
 *
 *@attention
 *��
 *
 *@param ulDnsServerIP [IN] DNS������IP��ַ��������32λ�޷�������
 *
 *@retval VOS_OK 0    �ɹ�
 *@retval ����    ��0  ʧ�ܣ���Ʒ���ش�����
 *
 *@par ����:
 *@li dns_api.h:�ýӿ����������ļ���
 *@li tcpip_dnsc.lib:�ýӿ����������ļ�����
 *
 *@see TCPIP_RegFuncDNSCGetSrcIPHook
*/
typedef ULONG (*DNSCGetSrcIPHOOK)(ULONG ulDnsServerIP);

/**
 *@ingroup dnsclient
 *@brief ���DNS���������������ӿڡ�
 *
 *@par ����:
 *���DNS���������������ӿڡ�
 *
 *@attention
 *��
 *
 *@param ulProtocolFlag [IN] AF_INET(2) �� AF_INET6(29)�����������൱����Ч�����������Ƿ��Լ�顣
 *
 *@retval #DNSC_SUCCESS 0    �ɹ�
 *@retval ����          ��0  ʧ�ܣ��ο�enum_DnsErr_INFO
 *
 *@par ����:
 *@li dns_api.h:�ýӿ����������ļ���
 *@li tcpip_dnsc.lib:�ýӿ����������ļ�����
 *
 *@see TCPIP_GetDnsDomainList
*/
extern ULONG TCPIP_ClrDnsDynamicHost(ULONG ulProtocolFlag);

/**
 *@ingroup dnsclient
 *@brief ��ȡDNS������׺�б���Ϣ��
 *
 *@par ����:
 *��ȡDNS������׺�б���Ϣ��
 *
 *@attention
 *��
 *
 *@param pstDomainInfo [OUT] ����б��ָ�롣�ǿ�ָ��
 *
 *@retval #DNSC_SUCCESS 0    �ɹ�
 *@retval ����          ��0  ʧ�ܣ��ο�enum_DnsErr_INFO
 *
 *@par ����:
 *@li dns_api.h:�ýӿ����������ļ���
 *@li tcpip_dnsc.lib:�ýӿ����������ļ�����
 *
 *@see TCPIP_SetDnsDomainSuffix
*/
extern ULONG TCPIP_GetDnsDomainList(TCPIP_DomainInfo_S *pstDomainInfo);

/**
 *@ingroup dnsclient
 *@brief ���������ӿڡ�
 *
 *@par ����:
 *���������ӿڡ�
 *
 *@attention
 *������������ȣ�����������'.'�ַ���Ӧ�ò�����254��������Ȱ���������׺��������������׺��������������Ӧ�ò�����254��
 *
 *@param pcDNSName [IN] Ԥ������������Ҫ������������Ϣ���Ȳ�����254���ǿ�ָ��
 *@param pulIPAddr [OUT] ���صĽ����õ�IP��ַָ�롣�ǿ�ָ��
 *@param ulIPV6Flag [IN] IPV6��ǣ�0��ʾIPV4,��0��ʾIPV6��32λ�޷�������
 *
 *@retval #DNSC_SUCCESS 0    �ɹ�
 *@retval ����          ��0  ʧ�ܣ��ο�enum_DnsErr_INFO
 *
 *@par ����:
 *@li dns_api.h:�ýӿ����������ļ���
 *@li tcpip_dnsc.lib:�ýӿ����������ļ�����
 *
 *@see TCPIP_SetDnsServer
 *@see TCPIP_SetDnsDomainSuffix
*/
extern ULONG TCPIP_GetDnsHost(CHAR *pcDNSName, VOID *pulIPAddr, ULONG ulIPV6Flag);

/**
 *@ingroup dnsclient
 *@brief ��������������б�ӿڡ�
 *
 *@par ����:
 *��������������б�ӿڡ�
 *
 *@attention
 *��
 *
 *@param pstDomainInfo [OUT] ����б��ָ�롣�ǿ�ָ��
 *
 *@retval #DNSC_SUCCESS 0    �ɹ�
 *@retval ����          ��0  ʧ�ܣ��ο�enum_DnsErr_INFO
 *
 *@par ����:
 *@li dns_api.h:�ýӿ����������ļ���
 *@li tcpip_dnsc.lib:�ýӿ����������ļ�����
 *
 *@see TCPIP_SetDnsServer
*/
extern ULONG TCPIP_GetDnsServer(TCPIP_DomainInfo_S * pstDomainInfo);

/**
 *@ingroup dnsclient
 *@brief ����DNS����ǰ׺�б�ӿڡ�
 *
 *@par ����:
 *����DNS����ǰ׺�б�ӿڡ�
 *
 *@attention
 *��
 *
 *@param ulNoFlag [IN] ��ʾ���ӻ���ɾ��������׺����0��ʾɾ����0��ʾ���ӡ�32λ�޷�������
 *@param pstDomainName [IN] ������׺��Ϣ����������󳤶�Ϊ20���ǿ�ָ��
 *@param ulDomainNameFlag [IN] ��ulNoFlag=1��ulDomainNameFlag=0ʱ��ɾ��ȫ��������׺����������˲���û�����á�32λ�޷�������
 *
 *@retval #DNSC_SUCCESS 0    �ɹ�
 *@retval ����          ��0  ʧ�ܣ��ο�enum_DnsErr_INFO
 *
 *@par ����:
 *@li dns_api.h:�ýӿ����������ļ���
 *@li tcpip_dnsc.lib:�ýӿ����������ļ�����
 *
 *@see TCPIP_GetDnsDomainList
 *@see TCPIP_ClrDnsDynamicHost
*/
extern ULONG TCPIP_SetDnsDomainSuffix(ULONG ulNoFlag,
                                      CHAR  *pstDomainName,
                                      ULONG ulDomainNameFlag);

/**
 *@ingroup dnsclient
 *@brief ����DNS������������
 *
 *@par ����:
 *����DNS������������
 *
 *@attention
 *��
 *
 *@param ulOpMode [IN] �����롣0��ʾ����ָ��������������ַ��1��ʾɾ��ָ��������������ַ��2��ʾɾ��ȫ��������������ַ��
 *@param pstServerIP [IN] ������IP��ַ�����ǿ�ָ��
 *@param ulIPV6Flag [IN] IPV6���,0��ʾIPV4,��0��ʾIPV6��32λ�޷�������
 *
 *@retval #DNSC_SUCCESS 0    �ɹ�
 *@retval ����          ��0  ʧ�ܣ��ο�enum_DnsErr_INFO
 *
 *@par ����:
 *@li dns_api.h:�ýӿ����������ļ���
 *@li tcpip_dnsc.lib:�ýӿ����������ļ�����
 *
 *@see TCPIP_GetDnsServer
*/
extern ULONG TCPIP_SetDnsServer(ULONG ulOpMode, CHAR *pstServerIP, ULONG ulIPV6Flag);

/**
 *@ingroup dnsclient
 *@brief ��ʾ�����ϵ�DNS�����Ϣ�ӿڡ�
 *
 *@par ����:
 *��ʾ�����ϵ�DNS�����Ϣ�ӿڣ����������ϵ�����������Ϣ��DNS Server��Ϣ��������׺��Ϣ��
 *
 *@attention
 *��
 *
 *@param ��
 *
 *@retval ��
 *
 *@par ����:
 *@li dns_api.h:�ýӿ����������ļ���
 *@li tcpip_dnsc.lib:�ýӿ����������ļ�����
 *
 *@see ��
*/
extern VOID TCPIP_ShowDnsInfo(VOID);

/**
 *@ingroup dnsclient
 *@brief ����DNS���Կ��ء�
 *
 *@par ����:
 *����DNS���Կ��ء�
 *
 *@attention
 *��
 *
 *@param ulswitch [IN] ���Կ�������ֵ��0 �򿪣�1 �رա�
 *
 *@retval #DNSC_SUCCESS 0    �ɹ�
 *@retval ����          ��0  ʧ�ܣ��ο�enum_DnsErr_INFO
 *
 *@par ����:
 *@li dns_api.h:�ýӿ����������ļ���
 *@li tcpip_dnsc.lib:�ýӿ����������ļ�����
 *
 *@see TCPIP_GetDNSDebugSwitch
*/
extern ULONG TCPIP_SetDNSDebugSwitch(ULONG ulswitch);

/**
 *@ingroup dnsclient
 *@brief ��ȡDNS���Կ��ء�
 *
 *@par ����:
 *��ȡDNS���Կ��ء�
 *
 *@attention
 *��
 *
 *@param pulswitch [OUT] ���صĵ��Կ���ֵ��0 �򿪣�1 �رա��ǿ�ָ��
 *
 *@retval #DNSC_SUCCESS 0    �ɹ�
 *@retval ����          ��0  ʧ�ܣ��ο�enum_DnsErr_INFO
 *
 *@par ����:
 *@li dns_api.h:�ýӿ����������ļ���
 *@li tcpip_dnsc.lib:�ýӿ����������ļ�����
 *
 *@see TCPIP_SetDNSDebugSwitch
*/
extern ULONG TCPIP_GetDNSDebugSwitch(ULONG *pulswitch);

/**
 *@ingroup dnsclient
 *@brief ����DNSCģ��ȫ��TOS��
 *
 *@par ����:
 *����DNSCģ��ȫ��TOS��
 *
 *@attention
 *ֻ��DNSC4��Ч����DNSC6��Ч�������壩��
 *
 *@param ucTos [IN] ����DNSC TOSֵ��ֵ����Ч��
 *
 *@retval #DNSC_SUCCESS 0    �ɹ�
 *@retval ����          ��0  ʧ�ܣ��ο�enum_DnsErr_INFO
 *
 *@par ����:
 *@li dns_api.h:�ýӿ����������ļ���
 *@li tcpip_dnsc.lib:�ýӿ����������ļ�����
 *
 *@see TCPIP_GetDnsTos
*/
extern ULONG TCPIP_SetDnsTos(UCHAR ucTos);

/**
 *@ingroup dnsclient
 *@brief ��ȡDNSC ģ��ȫ��TOS��
 *
 *@par ����:
 *��ȡDNSC ģ��ȫ��TOS��
 *
 *@attention
 *��
 *
 *@param pucTos [OUT] �����ȡDNSC TOSֵ���ǿ�ָ��
 *
 *@retval #DNSC_SUCCESS 0    �ɹ�
 *@retval ����          ��0  ʧ�ܣ��ο�enum_DnsErr_INFO
 *
 *@par ����:
 *@li dns_api.h:�ýӿ����������ļ���
 *@li tcpip_dnsc.lib:�ýӿ����������ļ�����
 *
 *@see TCPIP_SetDnsTos
*/
extern ULONG TCPIP_GetDnsTos(UCHAR *pucTos);

/**
 *@ingroup dnsclient
 *@brief ע�����DNS server��IP��ַ��ȡDNS�������������ĵ�Դ��ַ�Ļص�������
 *
 *@par ����:
 *ע�����DNS server��IP��ַ��ȡDNS�������������ĵ�Դ��ַ�Ļص�������
 *
 *@attention
 *�ûص�������Ҫ��Э��ջ����ǰע�ᣬע�����ע����
 *
 *@param pfHook [IN] ע��ĺ���ָ�롣�ǿ�ָ��
 *
 *@retval #DNSC_SUCCESS 0    �ɹ�
 *@retval ����          ��0  ʧ�ܣ��ο�enum_DnsErr_INFO
 *
 *@par ����:
 *@li dns_api.h:�ýӿ����������ļ���
 *@li tcpip_dnsc.lib:�ýӿ����������ļ�����
 *
 *@see DNSCGetSrcIPHOOK
*/
extern ULONG TCPIP_RegFuncDNSCGetSrcIPHook(DNSCGetSrcIPHOOK pfHook);

/*******************************************************************************
* Func Name: TCPIP_SetDnsCompatibleSwitch
* Description: API to set the  g_ulDNSCompatibleswitch to decide
*                   underscore is allowed or not in host name
* Input: ULONG ulSwitch - switch value (1 - Enable , 0 - Disable)
* Output:
* Returns: VOS_OK - success
*             VOS_ERR- failure
*             DNS_API_COM_NULL - When g_pstShDnsCfgVtbl is null
* Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE              NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-18   r84019196                  Created
*
*******************************************************************************/
/**
 *@ingroup dnsclient
 *@brief ����DNS���ݿ��ء�
 *
 *@par ����:
 *����DNS���ݿ��ء�
 *
 *@attention
 *NA
 *
 *@param ulSwitch [IN] ���ݿ���ֵ��[0, 1]��0-ȥʹ�ܣ�1-ʹ��
 *
 *@retval VOS_OK  0 �ɹ�
 *@retval VOS_ERR 1 ʧ��
 *
 *@par ����:
 *@li dns_api.h:�ýӿ����������ļ���
 *@li tcpip_dnsc.lib:�ýӿ����������ļ�����
 *
 *@since V300R002C20
 *@see TCPIP_GetDnsCompatibleSwitch
*/
ULONG TCPIP_SetDnsCompatibleSwitch(ULONG ulSwitch);

/*******************************************************************************
* Func Name: TCPIP_GetDnsCompatibleSwitch
* Description: API to get the  g_ulDNSCompatibleswitch
* Input:
* Output: ULONG *pulSwitch
* Returns: VOS_OK - success
*             VOS_ERR- failure
*             DNS_API_COM_NULL - When g_pstShDnsCfgVtbl is null
* Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE              NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-09-18   r84019196                  Created
*
*******************************************************************************/
/**
 *@ingroup dnsclient
 *@brief ��ȡDNS���ݿ�������ֵ��
 *
 *@par ����:
 *��ȡDNS���ݿ�������ֵ��
 *
 *@attention
 *NA
 *
 *@param pulSwitch [OUT] ָ���ȡ���ļ��ݿ���ֵ��ָ�롣�ǿ�ָ�룬ָ��ֵȡֵ[0, 1]��0-ȥʹ�ܣ�1-ʹ��
 *
 *@retval #DNSC_SUCCESS 0    �ɹ�
 *@retval ����          ��0  ʧ�ܣ��ο�enum_DnsErr_INFO
 *
 *@par ����:
 *@li dns_api.h:�ýӿ����������ļ���
 *@li tcpip_dnsc.lib:�ýӿ����������ļ�����
 *
 *@since V300R002C20
 *@see TCPIP_SetDnsCompatibleSwitch
*/
ULONG TCPIP_GetDnsCompatibleSwitch(ULONG *pulSwitch);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* _DNS_API_H_ */

