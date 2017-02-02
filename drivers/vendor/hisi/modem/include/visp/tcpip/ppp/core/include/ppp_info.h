/************************************************************************
 *                                                                      *
 *                          ģ����PPP_info.h                            *
 *                                                                      *
 *  Project Code:                                                       *
 *  Create Date:                                                        *
 *  Author:                                                             *
 *  Modify Date:                                                        *
 *            VRPV3R001M07��������2002/11/29                            *
 *                -- ��enum_PPP��������PPP_VJCOMP_DEBUG                 *
 *                -- ����·�����Ķ��������˱����                       *
 *            VRPV3R001M07, liminglei 27056, 2002.10.29                 *
 *                -- ��enum_PPP��������                                 *
 *                                    PPP_REQUEST_CALLBACK              *
 *                                    PPP_NTSTRING_CALLBACK             *
 *                                    PPP_NTSTRINGCB_HELP               *
 *                                    PPP_QUALITY_CLOSEPER              *
 *                                    PPP_QUALITY_RESUMEPER             *
 *  Document:                                                           *
 *  Function:                                                           *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.1 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *    ��Ϣ�ַ��������ⲿ����ͷ�ļ���                                    *
 *                                                                      *
 ************************************************************************/

#ifdef    __cplusplus
extern "C"{
#endif

enum enum_ppp 
{
    /*PPP_NO,*//*modified for D21089,2003/04/13*/
    PPP_ENPPP,
    PPP_PPP,
    PPP_NEGO_PARAMETER, 
    PPP_NEGO_TIMEOUT, 
    PPP_NEGO_TIMEOUT_SECOND, 
    PPP_ENCAP, 
    PPP_COMPRESS_METHOD, 
    PPP_STAC_LZS, 
    /*PPP_DEBUG_FUNCTION, *//*modified for D21089,2003/04/13*/
    PPP_DEBUG_INFORMATION, 
    PPP_CORE_DEBUG, 
    PPP_IPCP_DEBUG, 
    PPP_LCP_DEBUG, 
    PPP_ERROR_DEBUG, 
    PPP_EVENT_DEBUG, 
    PPP_PACKET_DEBUG, 
    PPP_STATE_DEBUG, 
    PPP_ALL_DEBUG, 
    PPP_EVENT_CORE, 
    PPP_CCP_DEBUG, 
    PPP_SCP_DEBUG, 
    PPP_IP_DEBUG, 
    PPP_PAP_DEBUG, 
    PPP_CHAP_DEBUG, 
    PPP_DEBUG_INTERFACE, 
    /*modified for D21089,2003/04/13*/
    /*
    PPP_INTERFACE_NAME, 
    PPP_INTERFACE_TYPE, 
    PPP_INTERFACE_NUMBER, 
    */
    /*end of D21089 modified*/
    PPP_OSICP_DEBUG, 
    PPP_OSINPDU_DEBUG, 
    PPP_MPLSCP_DEBUG, 
    PPP_MPLSUNICAST_DEBUG, 
    PPP_MPLSMULTICAST_DEBUG, 
    PPP_MP_DEBUG, 
    PPP_AUTH_TYPE, 
    PPP_AUTH_PAP, 
    PPP_AUTH_CHAP, 
    PPP_CHAP_CALLIN, 
    PPP_DEFAULT_SCHEME,
    PPP_DEFAULT_AUTHLIST, 
    PPP_AUTH_LISTNAME, 
    PPP_SET_ACCOUNT, 
    PPP_DEFAULT_ACCOUNTLIST, 
    PPP_NAMED_ACCOUNTLIST, 
    PPP_CHAP_PARAMETER, 
    PPP_HOSTNAME, 
    PPP_CHAP_HOST_NAME,
    PPP_LOCAL_SECRET, 
    PPP_NOHIDE_PASSWORD, 
    PPP_HIDE_PASSWORD, 
    PPP_USER_PASSWORD0,
    PPP_USER_PASSWORD7,
    /*End of D24898*/
    PPP_PAP_PARAMETER, 
    PPP_HOSTNAME_SECRET, 
    PPP_PAP_NAME, 
    PPP_PAP_PASSWORD, 
    PPP_CALLBACK, 
    PPP_ACCEPT_CALLBACK, 
    /*liminglei added 2002.10.18*/
    PPP_REQUEST_CALLBACK,
    PPP_NTSTRING_CALLBACK,
    PPP_NTSTRINGCB_HELP, 

    PPP_IPCP_INFO,
    PPP_IPCP_DNS,
    PPP_IPCP_DNS_REJECT,
    PPP_IPCP_DNS_ACCEPT,
    PPP_IPCP_DNS_PRIMADDR,
    PPP_IPCP_DNS_SNDADDR,
    /*lml add end*/
    PPP_VJCOMP_DEBUG,

    PPP_IP6CP_DEBUG,
    PPP_IP6_DEBUG,

    PPP_PACKET_SEND,
    PPP_ACTION_DEBUG,

/* VRPV3R001M07��������2002/11/29��end */
    ppp_MAX 
};


extern CHAR* g_apszPPPErrorInfo_En[];

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */
