#ifdef    __cplusplus
extern "C" {
#endif

#ifndef _PPP_INIT_H
#define _PPP_INIT_H

#define M_IMSI_LEN 16
#define CMP_CHECK_CPU_USAGE 60

#ifndef __LINUX_PLATFORM__
#define MAX_DMPU_ID MAX_DMPU_NUM
#else
#define MAX_DMPU_ID PPP_CPU_3_ON_SPU
#endif


#define HSGW_PRODUCT_VJ_USER_NUMBER_PER_SC                (HSGW_PRODUCT_VJ_USER_NUMBER/SC_NUM)
#define HSGW_PRODUCT_MPPC_PDP_NUMBER_PER_SC               (HSGW_PRODUCT_MPPC_PDP_NUMBER/SC_NUM)

/* PPP�ڲ���Ϣ�ṹ�� */
typedef struct
{
    ULONG ulCurRenegoIndex;
}PPP_INNER_MSG_S;

typedef enum
{
    PPP_INNER_MSG_CODE_RENEGO = 1,
} PPP_INNER_MSG_CODE_E;



/* PPP���ƿ�ȫ�����ݵĽṹ�� */
typedef struct tagCKP_BACKUP_PPPALLINFO_S
{
    /*********************************/
    /*       ָ�붨��              */
    /*********************************/
    //PPPCONFIGINFO_S* pstConfigInfo;         /* ������Ϣ */
    //PPPCONFIGINFO_S* pstUsedConfigInfo;     /* ��ǰ�ӿ����û������������Ϣ,ֻ�����ÿɼ��ӿ���Ч */
    //PPPRENOGOINFO*   pstPppRenegoInfo;      /* ��Э����Ϣ */

    //VOID* pstLcpInfo;           /* LCP  ���ƿ�ָ�� */
    //VOID* pstPapInfo;           /* PAP  ���ƿ�ָ�� */
    //VOID* pstChapInfo;          /* CHAP ���ƿ�ָ�� */
    //VOID* pstEapInfo;           /* EAP  ���ƿ� */
    //VOID* pstIpcpInfo;          /* IPCP ���ƿ�ָ�� */
    //VOID* pstIpV6cpInfo;        /* IPV6CP ���ƿ�ָ�� */
    //VOID* pstVsncpInfo;         /* VSNCP ���ƿ�ָ�� */
    //VOID* pstCcpInfo;           /* CCP  ���ƿ�ָ�� */
    //VOID* pL2tpPara;            /* L2TP��Ҫ�Ĳ��� */
    //VOID* pulCurrFsm;           /* ��ǰ״̬�� */

    PPP_LCP_OPTION_S  stLcpGotOptions;
    PPP_IPCP_OPTION_S stIpcpGotOptions;
    PPP_IPV6CP_OPTION_S stIpv6cpGotOptions;

    ULONG bIsAsync          : 1,        /* �Ƿ����첽��, ��LCP���ж��Ƿ�Э��ACCMAP */
          bSynAsyConvert    : 1,        /* �����첽�ڣ�����ȷ���Ƿ���PPP����ͬ/�첽����ת�� */
          bLoopBacked       : 1,        /* �ӿ��Ƿ������Ի� */
          bLowerIsUp        : 1,
          bIPReleaseFlg     : 1,        /* 0: ��Ҫ�ͷ�IP�� 1: ����Ҫ�ͷ�IP(MIP&L2tp�û�)*/
          bIPTech           : 2,        /* 0: SIP; 1: MIP; 2: MIPAgent ;3 NIL*/
          bAuthServer       : 1,        /* PDSN��Ʒ��̬��֧��serverģʽ��0��ʾ��֤��ϻ�������֤��1���ڽ�����֤ */
          bAuthClient       : 1,        /* PDSN��Ʒ��̬��֧��clientģʽ����ֵʼ��Ϊ�� */
          bReNego           : 1,        /* ��Э�̱�־ */
          bReNegoV6         : 1,        /* IPV6��Э�̱�־ */
          bPppStateFlg      : 2,        /* ��̬���ӱ�� */
          bPppMode          : 1,        /* �ս�ģʽΪ0������ģʽΪ1 */
          bPppClient        : 1,        /* �ͻ���ģʽΪ1������Ϊ0 */
          bPhaseFlag        : 2,        /* 0:LCP�׶Σ�1:��Ȩ�׶Σ�2:IPCP�׶� 3:�ɹ��׶� */
          bFailFlag         : 4,        /* 0:�Լ�Э��ʧ��. 1:A11/GTPC֪ͨɾ��. 2:�û�Ҫ������. 3:L2TP֪ͨɾ�� */
          bMppcFlag         : 1,        /* MPPC�û���ͳ�Ʊ�־ */
          bVjFlag           : 1,        /* VJ�û���ͳ�Ʊ�־ */
          bLzs0Flag         : 1,        /* Stac_Lzs0�û���ͳ�� */
          bLzs1Flag         : 1,        /* Stac_Lzs1�û���ͳ�� */
          bPpcAAAFlag       : 1,
          bPppSuccess       : 1,        /* PPP�����ɹ����,����PPPָ���Ż� */
          bAuthFlag         : 1,        /* �����ж��Ƿ��Ѿ���ɹ�chap��pap��Ȩ,����VOS_TRUE,����Э�̲�����AAA */
          bIpcpSucFlag      : 1,        /* PPPЭ��IPCPЭ�̳ɹ����,�ñ������Э�̹���Ҳ����ı� */
          bPppStateFlgV6    : 2,        /* IPV6��̬���ӱ�� */
          bPccFlag          : 1;        /* �Ƿ�ΪPCC�û���ʶ*/

    ULONG bRecvLcpMsgFlag   : 1,        /* ��ʾ�Ƿ��յ���LCP����Ϣ*/
          bBit328SoftPara   : 1,        /* bit328������� */
          bIpv6cpNoToPDN    : 1,        /* ipv6cp finish ʱ�Ƿ�֪ͨPDN, 0��ʾ֪ͨ�� 1Ϊ��֪ͨ */
          bIpcpNoToPDN      : 1,        /* ipcp finish ʱ�Ƿ�֪ͨPDN, 0��ʾ֪ͨ�� 1Ϊ��֪ͨ */
          bEhrpdUser        : 1,        /* �Ƿ�ΪeHRPD�û� */
          bMppc             : 1,        /* mppcѹ����־ */
          bEAPAuthFlag      : 1,        /* EAP�Ƿ��Ѿ��ɹ��� */
          bIPCPNakHandFlag  : 1,        /* IPCP NAK HANDLING */
          bReservNew        : 24;       /* ע���޸�Ϊ���� */


    /*********************************/
    /*       �ṹ�嶨��              */
    /*********************************/
    //IMSI_S            stIMSI;

    //PPPDEBUGINFO_S stPppDebugInfo;    /* ������Ϣ */
    //ULONG ulPppRleaseCode;
    ULONG ulRemoteAccm;         /* �Զ�ACCM������ */
    ULONG ulLocalAccm;          /* ����ACCM������ */
    //ULONG ulRPIndex;
    ULONG ulPcfIP;
    ULONG ulIPAddr;             /* ����IP��ַ����ʼ��Ϊ2.2.2.2 */
    ULONG ulPeerIPAddr;         /* ����RADIUS SERVER��DHCP���͵��û�IP��ַ */
    ULONG ulDNSAddr1;
    ULONG ulDNSAddr2;
    //ULONG64 ulNegoStartTime;      /* PPPЭ�̿�ʼʱ�� */
    ULONG ulNowUTCInSec;

    USHORT usPeerId;                   /* �����һ�η��ͷ�����id */
    USHORT usDynPeerId;                /* �����һ�η��ͷ�����id */
    UCHAR ucLcpPktId;
    UCHAR ucIpcpPktId;
    UCHAR ucAAAType;
    UCHAR aucRvs;
    UCHAR aucAAAHost[DIAM_AUTH_DRA_HOST_MAX_LENGTH + 1];        /* origin host */
    UCHAR aucAAARealm[DIAM_AUTH_REALM_OR_HOST_MAX_LENGTH + 1];       /* origin realm */
    //USHORT usTokenId;

    //USHORT usState;
    //USHORT usPhase;
                                                /* PPP��ǰ����Э�̽׶�,����Ϊ����ֵ:
                                                 PPP_PHASE_DEAD
                                                 PPP_PHASE_ESTABLISH
                                                 PPP_PHASE_AUTHENTICATE
                                                 PPP_PHASE_CBCP
                                                 PPP_PHASE_NETWORK
                                                 PPP_PHASE_TERMINATE
                                               */
    USHORT usCDBIndex;     /* GGSN:APNIndex PDSN:DomainIndex */
    USHORT usVirtualDomainIdx;

    USHORT usMtu;
    USHORT usPcfIndex;

    USHORT usIpv6Addr[IPV6_ADDR_LEN];     /*����ipv6��ַ����ʼ��Ϊ:FE80::FFFF:FFFF:FFFF:FFFF*/
    USHORT usPeerIPv6Addr[IPV6_ADDR_LEN]; /* ����RADIUS SERVER��lap������û�IPv6��ַ����ǰ׺�ͽӿ�id*/


    //UCHAR ucNAI[A11_MAX_NAI_LENGTH + 1];

    UCHAR  ucServiceOpt;
    UCHAR  ucFSMFailType;           /* FSM_CODE_E */
    UCHAR  ucDmpuId;                /* ѹ���ӿ�CPU��, 0ΪCPU2, 1ΪCPU3 */
    UCHAR  ucDpeId;                 /* �ӿ�DPE�� */

    UCHAR  ucIpCapability;     /*ip�������μ�ö�� PDSN_PPP_IPTYE ���� */
    UCHAR  ucEchoState;
    USHORT usStac_historys;
} CKP_BACKUP_PPPALLINFO_S;

VOID PPP_PerfInc(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType, UCHAR ucEhrpdMode);
VOID PPP_PerfDec(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType, UCHAR ucEhrpdMode);
VOID IPV6_PerfInc(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType);
VOID IPV6_PerfDec(VOS_UINT32 *pulPerfCounter, VOS_UINT32 ulPerfType);

extern ULONG g_ulDmpuMppcUser[MAX_DMPU_NUM]; /* �ӿ�MPPC�û��� */
extern ULONG g_ulDmpuVjUser[MAX_DMPU_NUM];   /* �ӿ�VJ�û��� */
extern ULONG g_ulPppSubBordStat[MAX_DMPU_NUM]; /* �ӿ�״̬ */

#define PPP_ClearLCPCB(pstLcpInfo)    \
    if(pstLcpInfo != VOS_NULL_PTR)            \
    {                                 \
        PPP_ClearCB_LCP(pstLcpInfo);  \
        pstLcpInfo = VOS_NULL_PTR;            \
    }

#define PPP_ClearMipAgentCB(pstMipAgentInfo)   \
    if(pstMipAgentInfo != VOS_NULL_PTR)                \
    {                                          \
        PPP_ClearCB_MipAgent(pstMipAgentInfo); \
        pstMipAgentInfo = VOS_NULL_PTR;                \
    }

#define PPP_ClearPAPCB(pstPapInfo)   \
    if(pstPapInfo != VOS_NULL_PTR)           \
    {                                \
        PPP_ClearCB_PAP(pstPapInfo); \
        pstPapInfo = VOS_NULL_PTR;           \
    }

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)
#define PPP_ClearEAPCB(pstEAPInfo)   \
        if(pstEAPInfo != VOS_NULL_PTR)           \
        {                                \
            PPP_ClearCB_EAP(pstEAPInfo); \
            pstEAPInfo = VOS_NULL_PTR;           \
        }
#endif

#define PPP_ClearCHAPCB(pstChapInfo)   \
    if(pstChapInfo != VOS_NULL_PTR)            \
    {                                  \
        PPP_ClearCB_CHAP(pstChapInfo); \
        pstChapInfo = VOS_NULL_PTR;            \
    }

#define PPP_ClearIPCPCB(pstIpcpInfo)   \
    if(pstIpcpInfo != VOS_NULL_PTR)            \
    {                                  \
        PPP_ClearCB_IPCP(pstIpcpInfo); \
        pstIpcpInfo = VOS_NULL_PTR;            \
    }

#define PPP_ClearIPV6CPCB(pstIpv6cpInfo)   \
if(pstIpv6cpInfo != VOS_NULL_PTR)            \
{                                  \
    PPP_ClearCB_IPV6CP(pstIpv6cpInfo); \
    pstIpv6cpInfo = VOS_NULL_PTR;            \
}

#if (VRP_MODULE_LINK_PPP_CCP == VRP_YES)

#define PPP_ClearMSIDCB(pstMsidInfo)   \
    if(pstMsidInfo != VOS_NULL_PTR)            \
    {                                  \
        PPP_ClearCB_MSID(pstMsidInfo); \
        pstMsidInfo = VOS_NULL_PTR;            \
    }


#define PPP_ClearCCPCB(pstCcpInfo)   \
    if(pstCcpInfo != VOS_NULL_PTR)           \
    {                                \
        /*lint -e746*/  \
        PPP_ClearCB_CCP(pstCcpInfo); \
        /*lint +e746*/ \
        pstCcpInfo = VOS_NULL_PTR;           \
    }


#define PPP_ClearMPLSCPCB(pstMplscpInfo)   \
    if(pstMplscpInfo != VOS_NULL_PTR)              \
    {                                      \
        PPP_ClearCB_MPLSCP(pstMplscpInfo); \
        pstMplscpInfo = VOS_NULL_PTR;              \
    }

#define PPP_ClearSTACCB(pstStacCompressInfo, pstStacDeCompressInfo)      \
    if((pstStacCompressInfo != VOS_NULL_PTR) || (pstStacDeCompressInfo != NULL)) \
    {                                                                     \
        PPP_ClearCB_STAC(pstStacCompressInfo, pstStacDeCompressInfo);     \
        pstStacCompressInfo = VOS_NULL_PTR;     \
        pstStacDeCompressInfo = VOS_NULL_PTR;   \
    }
#endif

#define PPP_ClearIPXCPCB(pstIpxcpInfo)   \
    if(pstIpxcpInfo != VOS_NULL_PTR)             \
    {                                    \
        PPP_ClearCB_IPXCP(pstIpxcpInfo); \
        pstIpxcpInfo = VOS_NULL_PTR;             \
    }

ULONG PPP_GetDomainInfoByName(PPPINFO_S *pstPppInfo, UCHAR* pucName);
extern ULONG PPP_GetIpAddrFromPacket(UCHAR *pPacket, ULONG ulLen, ULONG *pulIpAddr );
extern VOID PPP_EAP_NotifyDiamAuthRelease(PPPINFO_S *pstPppInfo);
extern VOID PPP_VSNCP_ClearALL(PPPINFO_S *pstPppInfo);



extern VOID PPP_A11_GetBSIDFromBCD(UCHAR *pucDst, const UCHAR *pucSrc, ULONG ulLength);

VOID PPP_CompRescSyn(VOS_VOID);

extern ULONG PPP_CheckMppcLimit(VOS_VOID);
extern VOS_UINT32 A11_CompressStatistic(VOS_UINT32 ulValue, VOS_UINT8 ucOperateObject, VOS_UINT8 ucDmpuId,
                             VOS_UINT8 ucDpeId, VOS_UINT8 ucFlag);

extern VOID CDB_PppCompressCfgModNotify(CDB_TBLID nTbl, CDB_RECID nRecId, UCHAR* pNewValue, UCHAR* pOldValue);
extern VOID CDB_PppCompressGetGlobalVar(PPP_COMPRESS_CFG *pstCompCfg);
extern VOID CDB_PppCompressCfgAddNotify(CDB_TBLID nTbl, CDB_RECID nRecId, UCHAR*  pValue);

extern VOID PPP_SendInnerMsg(ULONG  ulPara);
extern VOID PPP_ClearVjFlag(ULONG  ulRpIndex);

extern ULONG PPP_ModDomainInfoForCMIP(ULONG ulRpIndex, USHORT usDomainIdx);
extern ULONG PPP_USMNotifyRelease(PPP_A11MSG_S *pstA11Msg);
extern ULONG Diam_AUTHBackupRebuildDynAAACB(USHORT usNewPeerId, USHORT usDynPeerId,
                                     UCHAR *pucAAAHost, UCHAR *pucAAARealm);

extern VOID PPP_PDNNegoListProc(VOID *pPara);
extern ULONG PPP_CompCheckVjUserNum(UCHAR *pucDmpuId);
extern ULONG PPP_CompCheckMppcUserNum(UCHAR *pucDmpuId);

#endif

#ifdef    __cplusplus
 }
#endif    /* end of __cplusplus */

