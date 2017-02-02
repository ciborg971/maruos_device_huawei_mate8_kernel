/******************************************************************************
*
*        Copyright 2003-2006  Huawei Technologies India Private Limited
*                          All Rights Reserved
*
*------------------------------------------------------------------------------
*    Project Code   : VRP5.0
*    Module Name    : VISP Adapter for ND
*    Version        : Initial Draft
*    File Name      : nd_api.h
*    Create Date    : 2008/09/09
*    Author         : Suraj R (72063)
*    Description    : VISP adapter for ND
*------------------------------------------------------------------------------
* Modification History
* DATE        NAME              DESCRIPTION
* ------------------------------------------------------------------------
* 2008/09/09  Suraj R (72063)   Create
**************************************************************************
*/

#ifndef      _ND_API_H_
#define      _ND_API_H_

#ifdef      __cplusplus
extern "C"{
#endif


/* ------------------------------------------*
 * ND Adapter Configuration Switches         *
 * ------------------------------------------*/

/* Enable / Disable ADAPTER Error / Info Ouput on Console */
#define NDADP_SHOWERRORINFO          VRP_YES

/* Enable / Disable Auto-Init for Adapter */
/* If VRP_YES, a call to adapter API, will auto-init the Adapter,
   if it has not been initialized previously */
#define NDADP_AUTOINIT               VRP_YES

/* ------------------------------------------*/


/* ------------------------------------------*
 * ND ADAPTER RETURN VALUES                  *
 * ------------------------------------------*/

#define NDADP_OK                       VOS_OK
#define NDADP_ERR                      VOS_ERR

#define ND_ADP_ERROR_STARTVALUE        0x400
#define ND_ADP_ERROR_MAXVALUE          0xFFFFFFFF

/* Error Codes */
typedef enum tagND_ADP_ERRORNUM_E
{
    NDADP_ERR_MEMBERFN_UNAVAILABLE = ND_ADP_ERROR_STARTVALUE,
    NDADP_ERR_INIT_NOTDONE,
    NDADP_ERR_IFNAME_INVALID,
    NDADP_ERR_INVALIDIP,
    NDADP_ERR_INVALIDMAC,
    NDADP_ERR_OPFAIL,
    NDADP_ERR_INVALIDINPUT,
    NDADP_ERR_VTBLFETCHFAIL,
    NDADP_ERR_INVALIDNEXTHOP,
    NDADP_ERR_INVALIDDESTIP,
    NDADP_ERR_INVALIDPREFIX,
    NDADP_ERR_NDINFOISNULL,
    ND_ADP_ERRORNUM_ULONG_PAD       = ND_ADP_ERROR_MAXVALUE
}ND_ADP_ERRORNUM_E;


/* Types of Neighbor Entry */
typedef enum tagND_ADP_NBENTRYTYPE_E
{
    NDADP_NBTYPE_ALL,
    NDADP_NBTYPE_STATIC,
    NDADP_NBTYPEDYNAMIC,
    NDADP_NBTYPE_ULONG_PAD = ND_ADP_ERROR_MAXVALUE
}ND_ADP_NBTYPE_E;

/* ------------------------------------------*/


/* ------------------------------------------*
 * ND Adapter Functions                      *
 * ------------------------------------------*
 */

/*------------------------------------------*
                 * Common for host & router *
                 *--------------------------*/

/* Initialize adapter */
extern ULONG ND_InitAdapt();

/* Get HopLimit */
extern ULONG ND_GetHopLimit(UCHAR *pucHopLimit);

/* Add Static Neighbor Entry */
extern ULONG ND_AddStaticNBEntry(CHAR *szIfName, CHAR *pcIp6Addr, UCHAR *pucMac);

/* Add Static Neighbor Entry With VLAN ID support */
extern ULONG ND_AddStaticNBEntry_Vlan(CHAR *szIfName, CHAR *pcIp6Addr, UCHAR *pucMac,
                                        USHORT usVlanId, ULONG ulPortIndex);

/* Delete static Neighbor entry */
extern ULONG ND_DelStaticNBEntry(CHAR *szIfName, CHAR *pcIp6Addr);

/* Reset all Neighbor entries */
extern ULONG ND_ResetAllNBEntries(ULONG ulFlag);

/* Display NB Cache on interface */
extern ULONG ND_DisplayNBCacheOnIntf(CHAR * szIfName);

/* Rset NB Statistics on interface */
extern ULONG ND_ResetNBStatisticsIntf(CHAR * szIfName);

/* Get DAD Attempts on interface */
extern ULONG ND_GetDADAttempts(CHAR *szIfName, ULONG *pulRetVal);

/* Get Debug Status */
extern ULONG ND_GetDebug(ULONG *pulRetVal);

/* Set Debug */
extern ULONG ND_SetDebug(IP6_ND_CFG_OPT_E enFlag);

/* Get the entry limit after which timer should stop
   for deleting LRU entries */
extern ULONG ND_GetNDTimerTriggerLimit(ULONG *pulRetVal);

/* Set the entry limit after which timer should stop
   for deleting LRU entries */
extern ULONG ND_SetNDTimerTriggerLimit(ULONG ulEntryToDelete);

/* Get Number of Static Entries */
extern ULONG ND_GetStaticEntryCount(CHAR *szIfName,
                                            ULONG *pulStaticEntryCount);

/* Set DAD attempts for ND */
extern ULONG ND_SetDADAttempts(CHAR *szIfName, ULONG ulValue,
                                        IP6_ND_SETFLAG_E enFlag);

/* Start Address Resolution */
extern ULONG ND_Start_AddressResolution(ULONG ulIfIndex, IN6ADDR_S *pstIP6Addr,
                                                    IN6ADDR_S *pstSrcIP6Addr);

/* Start NUD */
extern ULONG ND_Start_NUD(ULONG ulIfIndex, IN6ADDR_S *pstIP6Addr);

extern ULONG ND_ResetNBEntriesIntfbyVLAN(ULONG ulIfIndex, ULONG ulVlanId,
                                                                                    UCHAR ucType);

/* ND NB open table */
extern ULONG ND_OpenTable (UINTPTR *pulWaitListHandle);

/* ND NB Close table */
extern ULONG ND_CloseTable (UINTPTR ulNBWaitListHandle);

/* NB Get First Entry */
extern ULONG ND_GetFirstExt(ULONG ulIfIndex, ND_NBENTRY_INFO_S *pstNBEntryOut, UINTPTR ulNBWaitListHandle);

extern ULONG ND_GetFirstExtWithErrCode(ULONG ulIfIndex,                                            
                                           UINTPTR ulNBWaitListHandle,
                                           ND_NBENTRY_INFO_S *pstNBEntryOut,
                                           ULONG *pulErrCode);

/* NB Get Next Entry */
extern ULONG ND_GetNextExt(UINTPTR ulNBWaitListHandle,
                                                    ND_NBENTRY_INFO_S *pstNextNBInfo);

extern ULONG ND_GetNextExtWithErrCode(UINTPTR ulNBWaitListHandle, 
                                           ND_NBENTRY_INFO_S *pstNextNBInfo,
                                           ULONG *pulErrCode);

/* Register ND Flow Callback */
extern ULONG ND_RegisterFlowCallback(IP6_ND_FLOW_CALLBACK_SET_S *pstFlowCallback);

/*------------------------------------------*
                 * Specific to host         *
                 *--------------------------*/

/* Display APIs */
/* Display Destination Cache */
extern ULONG ND_DisplayDestCache_Host();

/* Display Prefix List on Interface */
extern ULONG ND_DisplayPrefixListIntf_Host(CHAR *szIfName);

/* Display Default Router List on Interface */
extern ULONG ND_DisplayDefRouterListIntf_Host(CHAR * szIfName);

/* Delete all prefix list entries per interface */
extern ULONG ND_DelAllPrefixListEntriesIntf_Host(CHAR *szIfName);

/* Delete all destination cache entries */
extern ULONG ND_DelAllDestCacheEntries_Host();

/* Delete all default router list entries on an interface */
extern ULONG ND_DelRouterListEntriesIntf_Host(CHAR *szIfName);

/* Get ND Host-Specific Parameters */
extern ULONG ND_GetNDParams_Host(CHAR * szIfName,
                                IP6_ND_GETHOSTPARAMS_S *pstHostParams);

/* Default router Open table */
extern ULONG ND_DefRouterOpenTable_HOST(ULONG ulIfIndex, UINTPTR *pulHandle);

/* Get First Default Router entry */
extern ULONG ND_DefRouterGetFirst_HOST(UINTPTR ulWaitListHandle,
                                IP6_ND_DEFROUTER_INFO_S  *pstDefRouterEntryOut);

/* Get Next Default Router entry */
extern ULONG ND_DefRouterGetNext_HOST(UINTPTR ulWaitListHandle,
                                IP6_ND_DEFROUTER_INFO_S  *pstDefRouterEntryOut);

/* Close Default router Waitlist */
extern ULONG ND_DefRouterCloseTable_HOST(UINTPTR ulWaitListHandle);

/* Interface Prefix List Open Table */
extern ULONG ND_PrefixListOpenTable_HOST(ULONG ulIfIndex, UINTPTR *pulHandle);

/* Get First Prefix list entry */
extern ULONG ND_PrefixListGetFirst_HOST(UINTPTR ulWaitListHandle,
                                IP6_ND_INTFPREFIX_INFO_S *pstPrefixEntryOut);

/* Get First Prefix list entry */
extern ULONG ND_PrefixListGetNext_HOST(UINTPTR ulWaitListHandle,
                                        IP6_ND_INTFPREFIX_INFO_S *pstPrefixEntryOut);

/* Close Interface Prefix list Waitlist */
extern ULONG ND_PrefixListCloseTable_HOST(UINTPTR ulWaitListHandle);


/* Destination Cache Open Table*/
extern ULONG ND_DestinationCacheOpenTable_HOST(UINTPTR *pulHandle);

/* Get Destination cache First entry */
extern ULONG ND_DestCacheGetFirst_HOST(UINTPTR ulWtLstHandle,
                                                    IP6_ND_DESTCACHE_INFO_S  *pstDestEntryOut);

/* Get Destination cache Next entry */
extern ULONG ND_DestCacheGetNext_HOST(UINTPTR ulWtLstHandle,
                                        IP6_ND_DESTCACHE_INFO_S *pstDestEntryOut);

/* Destination Cache close Table*/
extern ULONG ND_DestinationCacheCloseTable_HOST(UINTPTR ulWaitListHandle);

/*------------------------------------------*
                 * Specific to router       *
                 *--------------------------*/

/* Set Manage Router Flag */
extern ULONG ND_SetManageFlag_Router(CHAR *szIfName, IP6_ND_SETFLAG_E enFlag);

/* Get Manage Router Flag */
extern ULONG ND_GetManageFlag_Router(CHAR *szIfName, UCHAR *pucRetVal);

/* Set Manage Router Flag */
extern ULONG ND_SetOtherFlag_Router(CHAR * szIfName, IP6_ND_SETFLAG_E enFlag);

/* Set Others Router Flag */
extern ULONG ND_GetOtherFlag_Router(CHAR *szIfName, UCHAR *pucRetVal);

/* Get Reachable Time */
extern ULONG ND_GetReachableTime_Router(CHAR *szIfName, ULONG *pulRetVal);

/* Get RA Interval */
extern ULONG ND_GetRAInterval_Router(CHAR *szIfName, ULONG *pulRetVal);

/* Get Minimium interval for RA sending */
extern ULONG ND_GetRAMinInterval_Router(CHAR *szIfName, ULONG *pulRetVal);

/* Set Default Routerliftime to be advertized in RA */
extern ULONG ND_GetDefaultRouterLifeTime_Router(CHAR *szIfName,
                                                        ULONG *pulRetVal);

/* Set HoptLimit */
extern ULONG ND_SetHopLimit_Router(UCHAR ucValue, IP6_ND_SETFLAG_E enFlag);

/* Set or Unset Suppressing or RA sent */
extern ULONG ND_SetSuppressRAFlag_Router(CHAR *szIfName,
                                                    IP6_ND_SETFLAG_E enFlag);

/* Set NS INterval */
extern ULONG ND_GetNSInterval_Router(CHAR *szIfName, ULONG *pulRetVal);

/* Set VLink Router */
extern ULONG ND_SetVLink_Router(ULONG ulFlag);

/* Set Global Value Router */
extern ULONG ND_SetGlobalValue_Router(ULONG ulValue);

/* Reboot Router */
extern ULONG ND_Reboot_Router();

/* Set RA Interval */
extern ULONG ND_SetRAInterval_Router(CHAR *szIfName, ULONG ulValue,
                                                    IP6_ND_SETFLAG_E enFlag);

/* Set Default Lifetime */
extern ULONG ND_SetDefaultLifeTime_Router(CHAR *szIfName, ULONG ulValue,
                                IP6_ND_SETFLAG_E enFlag);

/* Set NS Interval */
extern ULONG ND_SetNSInterval_Router(CHAR *szIfName, ULONG ulValue,
                                               IP6_ND_SETFLAG_E enFlag);

/* Add / Delete prefixes */
extern ULONG ND_ProcPrefixInfo_Router(CHAR *szIfName,
                                        ULONG ulNo,
                                        ULONG ulValidTime,
                                        UCHAR ucAutoConfFlag,
                                        ULONG ulPreferredTime,
                                        ULONG ulPrefixLength,
                                        CHAR *szIp6Addr,
                                        UCHAR ucOnLinkFlag);

/* Set Reachable Time */
extern ULONG ND_SetReachableTime_Router(CHAR *szIfName, ULONG ulValue,
                                IP6_ND_SETFLAG_E enFlag);

/* Get ND Information from Core */
extern ULONG ND_GetInfoFromCore_Router(CHAR *szIfName,
                                            ND_GETFROMCORE_S *pstNDInfo);

/* Register DHCP6 Adapter Callbacks */
extern ULONG ND_DHCP6C_Adapt_RegCallbackFunc(IP6_ND_DHCP6CADAPT_CALLBACK_S
                                                    *pstDHCP6AdaptCallBackFunc);

extern ULONG ND_Get_OG_Intf_HOST(IN6ADDR_S *pstDestAddress, ULONG *pulIfIndex, 
                                                                IN6ADDR_S *pstNexthopAddr);

extern ULONG ND_SendAdvertiseNA(CHAR *szIfName, IN6ADDR_S *pstDstAddr, UCHAR *pucMac);

extern ULONG ND_DelNBDynamicEntriesByAddr(ULONG ulIfIndex, IN6ADDR_S *pstIn6Addr);

extern ULONG ND_NS_Output_Ext(ULONG ulIfIndex,
                                        ULONG  ucOptionFlag,
                                        IN6ADDR_S *pstDstAddr,
                                        IN6ADDR_S *pstSrcAddr,
                                        IN6ADDR_S *pstTgtAddr);

extern ULONG ND_RegFuncSpecialProxyHook(gpfIP6NDSpecialNDProxy pfHookFuc);
extern ULONG ND_RegFuncGetDADProxyIfIndexHook(gpfIP6GetDADProxyIfIndex pfHookFuc);
extern ULONG ND_SetNDSpecialProxyFlag(ULONG ulIfIndex, UCHAR ucFalg);
ULONG ND_FetchNBEntry(ULONG ulIfnetIndex, IN6ADDR_S *pstIPv6Addr,
                                                ND_NBENTRY_INFO_S *pstNBInfo);
ULONG ND_GetNBEntryNum(ULONG *pulTotalNum, ULONG *pulTotalStaticNum);

/*Added by guojianjun178934, �ӿ�״̬�仯��physical��ַ�仯��������ͨ��NA����, 2014/1/27   ���ⵥ��:S-IP-005-PUBLIC-FUNC-003 */
/*******************************************************************************
*    Func Name: ND_SetNAAttempts
* Date Created: 2014-02-07
*       Author: guojianjun178934
*  Description: �趨NA���ĵ�����ʹ���[0,ND_SET_MAXNAATTEMPT](0,600)��
*               Ĭ��ΪMAX_NEIGHBOR_ADVERTISEMENT(3)
*        Input: CHAR *szIfName:�ӿ���
*               ULONG ulValue:NA���ķ��ʹ���
*               IP6_ND_SETFLAG_E enFlag:Set/Unset��ʶ
*       Output: 
*       Return: 
*      Caution: 1) ����趨NA���ʹ���Ϊ0,�򲻷��͡�
*               2) ������ڷ���NA���ģ��趨��ֵ����������Ч�����´���Ч��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-07   guojianjun178934        Create
*
*******************************************************************************/
ULONG ND_SetNAAttempts(CHAR *szIfName, ULONG ulValue,
                                   IP6_ND_SETFLAG_E enFlag);

/*******************************************************************************
*    Func Name: ND_GetNAAttempts
* Date Created: 2014-02-07
*       Author: guojianjun178934
*  Description: ��ȡ�趨��NA���ĵ�����ʹ���
*        Input: CHAR *szIfName:�ӿ���
*       Output: ULONG *pulRetVal:���ص�NA���ʹ���
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-07   guojianjun178934        Create
*
*******************************************************************************/
ULONG ND_GetNAAttempts(CHAR *szIfName, ULONG *pulRetVal);

/*******************************************************************************
*    Func Name: ND_SetNAInterval
* Date Created: 2014-02-07
*       Author: guojianjun178934
*  Description: �趨NA���ķ��ͼ��[ND_NA_INTERVAL_MIN, ND_NA_INTERVAL_MAX]([1s,3600s]),
*               Ĭ��ΪRETRANS_TIMER(1s)
*        Input: CHAR *szIfName:�ӿ���
*               ULONG ulValue:NA���ķ��ͼ��
*               IP6_ND_SETFLAG_E enFlag:Set/Unset��ʶ
*       Output: 
*       Return: 
*      Caution: 1) ������ڷ���NA���ģ��趨��ֵ����������Ч�����´���Ч��    
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-07   guojianjun178934        Create
*
*******************************************************************************/
ULONG ND_SetNAInterval(CHAR *szIfName, ULONG ulValue,
                                IP6_ND_SETFLAG_E enFlag);

/*******************************************************************************
*    Func Name: ND_GetNAInterval
* Date Created: 2014-02-07
*       Author: guojianjun178934
*  Description: ��ȡ�趨��NA���ͼ��
*        Input: CHAR *szIfName:�ӿ���
*       Output: ULONG *pulRetVal:NA���ͼ��
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-02-07   guojianjun178934        Create
*
*******************************************************************************/
ULONG ND_GetNAInterval(CHAR *szIfName, ULONG *pulRetVal);
/* End of Added by guojianjun178934, 2014/2/7   ���ⵥ��:S-IP-005-PUBLIC-FUNC-003 */

/*******************************************************************************
*    Func Name: TCPIP_OpenNDTable
* Date Created: 2014-03-10
*       Author: likaikun213099
*  Description: Registers the wait list handle
*        Input: TCPIP_ND_FILTER_S* pstNDFilterInfo:
*       Output: UINTPTR *pulNDInfoHandle:
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-10   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_OpenNDTable (UINTPTR *pulNDInfoHandle, TCPIP_ND_FILTER_S* pstNDFilterInfo);

/*******************************************************************************
*    Func Name: TCPIP_GetNextNDInfo
* Date Created: 2014-03-10
*       Author: likaikun213099
*  Description: ��ȡ�ӿ��ϵ���һ��ND�����Ʒ��Ҫ��֪�ڲ��Ĵ�����
*        Input: UINTPTR ulNDInfoHandle:
*       Output: TCPIP_ND_NBENTRY_INFO_S *pstNdInfo:
*               ULONG *pulErrCode:
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-10   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_GetNextNDInfo( UINTPTR ulNDInfoHandle, TCPIP_ND_NBENTRY_INFO_S* pstNdInfo);

/*******************************************************************************
*    Func Name: TCPIP_CloseNDTable
* Date Created: 2014-03-10
*       Author: likaikun213099
*  Description: Un registers the wait list handle
*        Input: UINTPTR ulNDInfoHandle:
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-10   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_CloseNDTable( UINTPTR ulNDInfoHandle);

/*******************************************************************************
*    Func Name: TCPIP_ShowNDInfo
* Date Created: 2014-03-11
*       Author: likaikun213099
*  Description: Display Nb entry
*        Input: CHAR* pIfName
*       Output: 
*       Return: 
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-11   likaikun213099          Create
*
*******************************************************************************/
ULONG TCPIP_ShowNDInfo(CHAR* pIfName);

/*******************************************************************************
*    Func Name: TCPIP_OpenIfNDHandle
* Date Created: 2014-03-27
*       Author: fengjing209023
*  Description: ע��WAITLIST
*        Input: szFilter: ��������
*       Output: pulIfNDInfoHandle: WAITLIST ���
*       Return: �ɹ���VOS_OK
*               ʧ�ܣ�VOS_ERR
*      Caution: �ӿ�������0���ѯ���нӿ��µ�ND��Ϣ�������ѯָ���ӿ��µ�ND��Ϣ
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-27   fengjing209023  Create
*
*******************************************************************************/
ULONG TCPIP_OpenIfNDHandle(UINTPTR *pulIfNDInfoHandle, TCPIP_IF_ND_FILTER_S *pstFilter);
/*******************************************************************************
*    Func Name: TCPIP_GetNextIfNDInfo
* Date Created: 2014-03-27
*       Author: fengjing209023
*  Description: ��ȡND��Ϣ
*        Input: ulNDInfoHandle: WAITLIST���
*       Output: psIfNdInfo: ���ص�ND��Ϣ������DAD���Դ�������Ϣ
*       Return: �ɹ���VOS_OK
*               ʧ�ܣ�VOS_ERR
*      Caution: �ӿ�������0���ѯ���нӿ��µ�ND��Ϣ�������ѯָ���ӿ��µ�ND��Ϣ
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-27   fengjing209023  Create
*
*******************************************************************************/
ULONG TCPIP_GetNextIfNDInfo(UINTPTR ulNDInfoHandle , TCPIP_IF_NDINFO_S *psIfNdInfo);
/*******************************************************************************
*    Func Name: TCPIP_CloseIfNDHandle
* Date Created: 2014-03-27
*       Author: fengjing209023
*  Description: �ر�WAITLIST���
*        Input: ulNDInfoHandle: waitlistHandle
*       Return: �ɹ���VOS_OK
*               ʧ�ܣ�VOS_ERR
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-27   fengjing209023  Create
*
*******************************************************************************/
ULONG TCPIP_CloseIfNDHandle(UINTPTR ulNDInfoHandle);
/*******************************************************************************
*    Func Name: TCPIP_GetIfNDInfo
* Date Created: 2014-03-27
*       Author: fengjing209023
*  Description: ��ȡָ���ӿ������DAD���Դ�������Ϣ
*        Input: ulIfIndex: �ӿ�����
*       Output: psIfNdInfo: ���ص�ND��Ϣ������DAD���Դ�������Ϣ
*       Return: �ɹ���VOS_OK
*               ʧ�ܣ�VOS_ERR
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-03-27   fengjing209023  Create
*
*******************************************************************************/
ULONG TCPIP_GetIfNDInfo(ULONG ulIfIndex, TCPIP_IF_NDINFO_S *pstIfNDInfo);
/*******************************************************************************
*    Func Name: TCPIP_IfND_Display
* Date Created: 2014-04-08
*       Author: fengjing209023
*  Description: ��ʾIPV6��ַ��Ϣ
*        Input: CHAR *pcIfName:�ӿ����ƣ�Ϊ�����е�ַ���ǿ�ָ���ӿ��µ�DAD����
*                              ��������Ϣ
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-04-08   fengjing209023  Create
*
*******************************************************************************/
VOID TCPIP_IfND_Display(CHAR *pcIfName);


ULONG TCPIP_NDMiss(ULONG ulIfIndex, IN6ADDR_S *pstIP6Addr);


ULONG ND_SendAdvertiseNAByIf(ULONG ulIfIndex, IN6ADDR_S *pstDstAddr, UCHAR *pucMac);


ULONG ND_GetReachableTimeByIndex(ULONG ulIfIndex, ULONG *pulRetVal);


ULONG ND_GetDADAttemptsByIndex(ULONG ulIfIndex, ULONG *pulRetVal);


ULONG ND_SetDADAttemptsByIndex(ULONG ulIfIndex, ULONG ulValue,
                                            IP6_ND_SETFLAG_E enFlag);


ULONG ND_SetReachableTime_RouterByIndex(ULONG ulIfIndex, ULONG ulValue,
                                IP6_ND_SETFLAG_E enFlag);


ULONG ND_GetNSInterval_RouterByIndex(ULONG ulIfIndex, ULONG *pulRetVal);


ULONG ND_SetNSInterval_RouterByIndex(ULONG ulIfIndex, ULONG ulValue,
                                               IP6_ND_SETFLAG_E enFlag);


ULONG ND_DelStaticNBEntryByIndex(ULONG ulIfIndex, CHAR *szIp6Addr);


ULONG ND_AddStaticNBEntry_VlanByIndex(ULONG ulIfIndex, CHAR *pcIp6Addr, UCHAR *pucMac,
                                        USHORT usVlanId, ULONG ulPortIndex);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _ND_API_H_ */

