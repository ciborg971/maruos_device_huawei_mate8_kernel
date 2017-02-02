

#ifndef TCPIP_PPI_H
#define TCPIP_PPI_H

#ifdef  __cplusplus
extern  "C"{
#endif

#include "tcpip/public/tcpip_pub_api.h"
#include "tcpip/public/tcpip_pub.h"
#include "public/dopra_cbb/include/utlsll.h"




/* NP�ظ��·���غ꣬�ṹ��ȫ�ֱ����� */
#define PPI_REPEATE_TIME                2000    /* NP�ظ��·���ʱ��2�볬ʱһ�� */
#define PPI_REPEATE_QUEUE_NUM           1024    /* NP�ظ��·����е���󳤶� */
#define PPI_REPEATE_MAX_HANDLE          128     /* ÿ�ζ�ʱ����ʱ��ദ��128��Ԫ�� */
#define PPI_REPEATE_MAX_DOWN_TIME       3       /* NP�ظ��·�����ÿ��Ԫ�ص�����·����� */
#define PPI_REPEATE_DEFAULT_PRIORITY    128     /* NP�ظ��·�����Ԫ�ص�Ĭ�����ȼ� */
#define PPI_REPEATE_ARG_NUM             5       /* NP�ظ��·�����Ԫ�صĲ������� */


/* NP�ظ��·����� */
typedef struct tagPPI_REPEATE
{
    SLL_NODE_S stNode;      /* ȫ������ڵ� */
    ULONG ulModuleId;       /* ģ��ID */
    ULONG ulFailedCount;    /* �ۼ��·�ʧ�ܴ��� */
    ULONG ulPriority;       /* ֵԽС�����ȼ�Խ�ߣ�Ĭ��128 */
    ULONG aulArgs[PPI_REPEATE_ARG_NUM];       /* �ص������Ĳ������ɸ���ģ���Լ����ͣ���ͬ */
}PPI_REPEATE_S;

extern SLL_S g_sllPpiRepeate;
extern ULONG g_ulPpiRepeateTimer;
/* NP�ظ��·���غ꣬�ṹ��ȫ�ֱ����� */



/*NP�·���ʱͳ�ƴ���ṹ*/
#define PPI_COUNT 5
typedef struct tagPPI_TIME
{
    TCPIP_CPUTICK_S stStartTime[PPI_COUNT];   /*�·���¼�Ŀ�ʼʱ��*/
    TCPIP_CPUTICK_S stEndTime[PPI_COUNT];     /*�·���¼�Ľ���ʱ��*/
    ULONG           ulOprType[PPI_COUNT];     /*�·��Ĳ�������*/
    ULONG           ulNPUpdateCount;          /*�·�����*/
}PPI_TIME_S;

typedef struct tagNpPppOsicpOption
{
    /* �Ƿ�Э�� */
    UCHAR neg_Align_NPDU;
    /* Э�̲���ֵ */
    UCHAR ucAlign_NPDU;
    USHORT  usReserved;
}PPI_PPP_OSICP_OPTION_S;

/*NP�·���ǰ��ʱ���*/
extern VOID VOS_GetCpuTick( ULONG *plow,ULONG *phigh );
#define MAKE_NP_STARTDOT(ulMsgType, OprType)\
{\
    if (g_ulNPUpdateSwitch)\
    {\
        ULONG ii = g_stNPPpiTime[ulMsgType].ulNPUpdateCount;\
        ii %= PPI_COUNT;\
        VOS_GetCpuTick( &(g_stNPPpiTime[ulMsgType].stStartTime[ii].ulLowTick),  \
                        &(g_stNPPpiTime[ulMsgType].stStartTime[ii].ulHighTick) );\
        g_stNPPpiTime[ulMsgType].ulOprType[ii] = OprType;\
    }\
}
/*NP�·��ķ��غ�ʱ����*/
#define MAKE_NP_ENDDOT(ulMsgType)\
{\
    if (g_ulNPUpdateSwitch)\
    {\
        ULONG ii = g_stNPPpiTime[ulMsgType].ulNPUpdateCount;\
        ii %= PPI_COUNT;\
        VOS_GetCpuTick( &(g_stNPPpiTime[ulMsgType].stEndTime[ii].ulLowTick),  \
                        &(g_stNPPpiTime[ulMsgType].stEndTime[ii].ulHighTick) );\
        g_stNPPpiTime[ulMsgType].ulNPUpdateCount++;\
    }\
}

#define PPP_COPY_LCPPPI_TO_BUF(pcBuf, iBufLen, iOffset, pstOptions) \
{ \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg acfc:%d", pstOptions->neg_accompression)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg magicnumber:%d", pstOptions->neg_magicnumber));\
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg accm:%d", pstOptions->neg_asyncmap)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg mhf:%d", pstOptions->neg_mhf)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg mrru:%d", pstOptions->neg_mrru)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg mru:%d", pstOptions->neg_mru)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg pfc:%d", pstOptions->neg_pcompression)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg prefix elision:%d", pstOptions->neg_prefix)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg ssnhf:%d", pstOptions->neg_ssnhf)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg discr:%d", pstOptions->neg_discr));\
    if (pstOptions->neg_asyncmap) \
    { \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\naccm:%d", pstOptions->ulAsyncmap)); \
    } \
    if (pstOptions->neg_mhf) \
    { \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), \
            P2("\r\ncode:%d, class:%d", pstOptions->ucCode, pstOptions->ucClass)); \
    } \
    if (pstOptions->neg_mrru) \
    { \
        UCHAR ucDiscrLen; \
        UCHAR ucIndex; \
        CHAR  szTemp[LEN_64] = {0}; \
        INT32   i32TempLen = 0; \
        \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmrru:%d", pstOptions->usMrru)); \
        \
        if((pstOptions->ucDiscr_len > PPP_CILEN_DISCR) \
            && (pstOptions->ucDiscr_len <= (PPP_CILEN_DISCR + PPI_MP_MP_DISCR_MAX_LENGTH))) \
        { \
            ucDiscrLen = pstOptions->ucDiscr_len - PPP_CILEN_DISCR; \
            \
            for(ucIndex=0; ucIndex < ucDiscrLen; ucIndex++) \
            { \
                i32TempLen += TCPIP_SNPRINTF(szTemp + i32TempLen, (LEN_64 - i32TempLen), P1("%02x", pstOptions->discr_addr[ucIndex])); \
            } \
            \
            iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P3("\r\nDISCRIMINATOR : Class: %u, Len: %u, Discr: %s", \
                                  pstOptions->ucDiscr_class, ucDiscrLen, szTemp)); \
        } \
    } \
    if (pstOptions->neg_mru) \
    { \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmru:%d", pstOptions->usMru)); \
    } \
    \
    if(pstOptions->neg_magicnumber) \
    { \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmagicnumber:%#x", pstOptions->ulMagicnumber)); \
    } \
    if (pstOptions->neg_prefix) \
    { \
        ULONG m; \
        ULONG n; \
        PPI_MC_PREFIX_S*pstPrefixEInfo = NULL; \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P0("\r\nPrefix-E info:")); \
        for (m = 0; m < PPI_MC_PREFIX_MAX_NUM; m++) \
        { \
            pstPrefixEInfo = &pstOptions->astPrefix[m]; \
            if (pstPrefixEInfo->ucPrefixValid) \
            { \
                iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\nCls:%02d, ", pstPrefixEInfo->ucClass)); \
                iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P0("Field:")); \
                for (n = 0; n < pstPrefixEInfo->usPrefixLength; n++) \
                { \
                    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("%02x", pstPrefixEInfo->aucPrefix[n])); \
                } \
            } \
        } \
    } \
}

#define PPP_COPY_IPCPPPI_TO_BUF(pcBuf, iBufLen, iOffset, pstOptions) \
{ \
    CHAR cTemp[LEN_32] = {0}; \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg iphc:%d", pstOptions->neg_iphc)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg vj:%d", pstOptions->neg_vj)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nouraddr:%s",  \
        VOS_IpAddrToStr(VOS_NTOHL(pstOptions->ulOurAddr), cTemp))); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nhisaddr:%s", \
        VOS_IpAddrToStr(VOS_NTOHL(pstOptions->ulHisAddr), cTemp))); \
    if (pstOptions->neg_iphc) \
    { \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\ncompress type:%d", pstOptions->ucCompressType)); \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nrtp compress type:%d", pstOptions->ucRtpCompressType)); \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmax header:%d", pstOptions->usMaxHeader)); \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmax period:%d", pstOptions->usMaxPeriod)); \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmax time:%d", pstOptions->usMaxTime)); \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nnon-tcp space:%d", pstOptions->usNonTcpSpace)); \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\ntcp space:%d", pstOptions->usTcpSpace)); \
    } \
} \

/* Added by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/30 */
#define PPP_COPY_IP6CPPPI_TO_BUF(pcBuf, iBufLen, iOffset, pstOptions) \
{ \
    ULONG i = 0;\
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg interfaceid:%d", pstOptions->neg_interfaceid)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg compprotocol:%d", pstOptions->neg_compprotocol)); \
\
    if (pstOptions->neg_interfaceid)\
    {\
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P0("\r\nmy interface id:0x")); \
        for (i = 0; i < INTERFACE_ID_LEN; i++)\
        {\
            iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("%x", pstOptions->my_interface_id[i])); \
        }\
\
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P0("\r\nhis interface id:0x")); \
        for (i = 0; i < INTERFACE_ID_LEN; i++)\
        {\
            iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("%x", pstOptions->his_interface_id[i])); \
        }\
    }\
\
    if (pstOptions->neg_compprotocol)\
    {\
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\ncomp protocol:%#x", pstOptions->comp_protocol)); \
    }\
}
/*End of Added by hanna55555, 2009/3/30 */

#define PPP_COPY_PMUXPPI_TO_BUF(pcBuf, iBufLen, iOffset, pstOptions) \
{ \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nneg default pid:%d", pstOptions->neg_defaultpid)); \
    if (pstOptions->neg_defaultpid) \
    { \
        iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\ndefault pid:%x", pstOptions->usDefaultPid)); \
    } \
} 

#define PPP_COPY_CONFIG_TO_BUF(pcBuf,  iBufLen, iOffset, pstConfig) \
{ \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nPppInterleave:%d", pstConfig->bPppInterleave)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nPppReorderWindow:%d", pstConfig->bPppReorderWindow)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmp min frag len:%d", pstConfig->usMinFragLen)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nlfi max delay LFI:%d", pstConfig->usMaxDelayLFI)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmax delay:%d", pstConfig->usMaxDelay)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmax frame len:%d", pstConfig->usMaxFrameLen)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmax sub frame len:%d", pstConfig->usMaxSubFrameLen)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\nmax sub frame num:%d", pstConfig->usMaxSubFrameNum)); \
    iOffset += TCPIP_SNPRINTF(pcBuf + iOffset, (iBufLen - iOffset), P1("\r\niphc nego suboptions :%d", pstConfig->ulNegoSubOptions)); \
}
#define NEXTLINE         5


extern ULONG       g_ulNPUpdateSwitch;   /*NP�·���ʱ���㿪��*/
extern PPI_TIME_S  g_stNPPpiTime[PPI_TYPE_END];/*NP�·���ʱͳ�ƴ������*/

/*Ϊ�˷�ֹ���ú������ֹ������ú궨���滻*/
#define g_pfTCPIP_PPI_FIB4_Update   g_stPPIHook.pfTCPIP_PPI_FIB4_Update     
#define g_pfTCPIP_PPI_ARP_Update    g_stPPIHook.pfTCPIP_PPI_ARP_Update      
#define g_pfTCPIP_PPI_IFNET_Update  g_stPPIHook.pfTCPIP_PPI_IFNET_Update   
#define g_pfTCPIP_PPI_PPP_Update    g_stPPIHook.pfTCPIP_PPI_PPP_Update      
#define g_pfTCPIP_PPI_IP4_Output    g_stPPIHook.pfTCPIP_PPI_IP4_Output
#define g_pfTCPIP_PPI_TRUNKPORT_Update g_stPPIHook.pfTCPIP_PPI_TRUNKPORT_Update

#define g_pfTCPIP_PPI_OSI_Output    g_stPPIHook.pfTCPIP_PPI_OSI_Output

/* 3ah ppi update */
#define     g_pfTCPIP_PPI_3AH_Update    g_stPPIHook.pfTCPIP_PPI_3AH_Update

#define     g_pfTCPIP_PPI_1AG_Update    g_stPPIHook.pfTCPIP_PPI_1AG_Update

#define     g_pfTCPIP_PPI_IGMP_Update    g_stPPIHook.pfTCPIP_PPI_IGMP_Update

/* l2if ppi  */
#define     g_pfTCPIP_PPI_VLAN_Update    g_stPPIHook.pfTCPIP_PPI_VLAN_Update
#define     g_pfTCPIP_PPI_PORT_Update    g_stPPIHook.pfTCPIP_PPI_PORT_Update
#define     g_pfTCPIP_PPI_MAC_Update     g_stPPIHook.pfTCPIP_PPI_MAC_Update
#define     g_pfTCPIP_PPI_QINQ_Update    g_stPPIHook.pfTCPIP_PPI_QINQ_Update

/* vrrp ppi */
#define     g_pfTCPIP_PPI_VRRP_Update    g_stPPIHook.pfTCPIP_PPI_VRRP_Update

/* multicase mac */
#define     g_pfTCPIP_PPI_CTRL_Update     g_stPPIHook.pfTCPIP_PPI_CTRL_Update

#define g_pfTCPIP_PPI_MAP_Update g_stPPIHook.pfTCPIP_PPI_MAP_Update
#define g_pfTCPIP_PPI_FIB6_Update g_stPPIHook.pfTCPIP_PPI_FIB6_Update
/* Begin:VISP1.7C03 VRF wangchengyang,2009-02-05   */
#define     g_pfTCPIP_PPI_VRF_Update    g_stPPIHook.pfTCPIP_PPI_VRF_Update
/* End:VISP1.7C03 VRF wangchengyang,2009-02-05   */

#define g_pfTCPIP_PPI_TRUNKBIND_Update    g_stPPIHook.pfTCPIP_PPI_TRUNKBIND_Update     
#define g_pfTCPIP_PPI_AM4_Update          g_stPPIHook.pfTCPIP_PPI_AM4_Update      

#define g_pfTCPIP_PPI_MPLSFW_Output  g_stPPIHook.pfTCPIP_PPI_MPLSFW_Output

#define g_pfTCPIP_PPI_IP6_Output   g_stPPIHook.pfTCPIP_PPI_IP6_Output 

#define g_pfTCPIP_PPI_PPPOE_Update g_stPPIHook.pfTCPIP_PPI_PPPOE_Update

#define g_pfTCPIP_PPI_TRUNK_LACP_Update g_stPPIHook.pfTCPIP_PPI_TRUNK_LACP_Update
    /* Chandra */
#define g_pfTCPIP_PPI_POLICYRT_Update g_stPPIHook.pfTCPIP_PPI_POLICYRT_Update

/*Added by apurba for VRF6*/
#define     g_pfTCPIP_PPI_VRF6_Update    g_stPPIHook.pfTCPIP_PPI_VRF6_Update
/*End of Added by apurba for VRF6*/

/*******************************ȫ�ֱ�������***************************************/
extern TCPIP_PPI_HOOK_S   g_stPPIHook; /*PPI�ӿڹ��Ӻ�����*/

extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl       *g_pstPp4Am4Vtbl;


/*******************************��������***************************************/
VOID TCPIP_PPI_LogRt6Msg(ULONG ulRet, ULONG ulOprType, PPI_RTMSG6_S *pstRtEntry);
VOID TCPIP_PPI_LogRtMsg(ULONG ulRet, ULONG ulOprType, PPI_RTMSG4_S *pstRtEntry);
VOID TCPIP_PPI_LogArpMsg(ULONG ulRet, ULONG ulOprType, PPI_ARP_S *pstArpMsg);
VOID TCPIP_PPI_LogIfMsg(ULONG ulRet, IFNET_S *pstIf, ULONG ulOprType, VOID *pData);
VOID TCPIP_PPI_LogPppMsg(ULONG ulRet, IFNET_S *pstIf, ULONG ulOprType, VOID *pData);
VOID TCPIP_PPI_LogMapMsg(ULONG ulRet, ULONG ulOprType, PPI_MAP_S  *pstMapInfo);

VOID TCPIP_PPI_LogOutpkt();
VOID TCPIP_PPI_LogIp6Outpkt();
VOID TCPIP_PPI_OSI_LogOutpkt();


VOID TRUNKPORT_PPI_Download_State(IFNET_S *pstPortIf, ULONG ulCmd, VOID* pstTrunkIf);

VOID TCPIP_PPI_LogIGMPMsg(ULONG ulRet, ULONG ulOprType, PPI_IGMPConfigInfo_S *pstIGMPInfo);
/* 3ah ppi log */
VOID TCPIP_PPI_3AH_LogMsg(ULONG ulRet, ULONG ulIfIndex, ULONG ulOperType, VOID *pOam3ahMsg);

VOID TCPIP_PPI_1AG_LogMsg(ULONG ulRet,ULONG ulIfIndex,ULONG ulOperType,VOID *pEoam1agMsg);

VOID TCPIP_PPI_L2IFVLAN_LogMsg(ULONG ulRet, USHORT usViD, ULONG ulOprType, VOID *pstInfo);
VOID TCPIP_PPI_L2IFPORT_LogMsg(ULONG ulRet, ULONG ulIndex, ULONG ulOprType, VOID *pstInfo);
VOID TCPIP_PPI_L2IFMAC_LogMsg(ULONG ulRet, ULONG ulOprType, VOID *pstInfo);
VOID TCPIP_PPI_L2IFQINQ_LogMsg(ULONG ulRet, ULONG ulIndex, ULONG ulOprType, VOID *pstInfo);
VOID TCPIP_PPI_VRRP_InfoMsg(ULONG ulRet, ULONG ulIfIndex, ULONG ulOprType, VOID *pData);
VOID TCPIP_PPI_LogCtrlMsg(ULONG ulRet, ULONG ulIfIndex, ULONG ulOprType, VOID *pstMMacInfo);
ULONG PPI_MultiMac_Update(ULONG ulIfIndex, ULONG ulOptType, UCHAR *pszMacAddr, UCHAR *pszMacMask);

extern NPDOWNLOAD_FAILED_PROCESS g_pfNpDownLoadFailProcHook;
ULONG PpiRepeate_Init(VOID);
ULONG PpiRepeate_InQueue(ULONG ulModuleId, ULONG ulPriority, ULONG aulArgs[]);
VOID PpiRepeate_Timer(VOID* pArg);
VOID PpiRepeate_WarningOutput(PPI_REPEATE_S *pNode);
/*******************************************************************************
*    Func Name: TCPIP_PPI_LogVRFMsg
* Date Created: 2009-02-04
*       Author: Wangchengyang
*  Description: VRF PPI����־��¼����
*        Input: ULONG ulRet:PPI�·�����ֵ
*               pstVrfPpiInfo:�·���Ϣ(���VRF_PPI_S)
*               ulOprType:��enum tagVRF_PPI_MSGTYPE_E
*
*       Output: 
*       Return: ��           
*
*
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-02-04      wangchengyang    Create
*******************************************************************************/
extern VOID TCPIP_PPI_LogVRFMsg(ULONG ulRet, VRF_PPI_S *pstVrfPpiInfo, ULONG ulOprType);

extern VOID TCPIP_PPI_LogVRF6Msg(ULONG ulRet, VRF6_PPI_S *pstVrfPpiInfo, ULONG ulOprType);


extern VOID TCPIP_PPI_LogPolicyRtMsg(ULONG ulRet, PPI_POLICYRT_S *pstPolicyRtPpiInfo, ULONG ulOprType);

extern VOID TCPIP_PPI_TRUNKBIND_LogMsg(ULONG ulRet, ULONG ulOperType, PPI_TRUNK_BIND_S *pstTrunkBind);
extern VOID TCPIP_PPI_TRUNKUpdate_LogMsg(ULONG ulRet, ULONG ulOperType, PPI_TRUNK_LACP_S *pstTrunkPPI);
extern VOID TCPIP_PPI_AM4_LogMsg(ULONG ulRet, ULONG ulOperType, PPI_IPADDR_INFO_S *pstIpAddrInfo);

extern VOID TCPIP_PPI_VPN_LogOutputPkt();
extern VOID TCPIP_PPI_VPN_LogInputPkt();
extern VOID TCPIP_PPI_VPN_LogErrorPkt();
extern VOID TCPIP_PPI_LogIFOutPkt(ULONG ulOutIndexIf, BOOL_T bIsPpiProcessed, BOOL_T bIsBcast, BOOL_T bIsMcast);


extern VOID TCPIP_PPI_NsrTrunk_LogMsg(ULONG ulRet, ULONG ulIfIndex, ULONG ulOperType, UCHAR *pucData);

#ifdef  __cplusplus
}
#endif

#endif

