#ifndef __PPP_AM_PUBLIC_H__
#define __PPP_AM_PUBLIC_H__

/************************* �������� **********************************/
#define PPP_MP 0x003d
#define PPP_IP 0x0021
#define PPP_IP6 0x0057
#define PPP_VSNP 0x005b
#define PPP_OSI 0x0023
#define PPP_IPX 0x002b

/*��ַ����*/
#define PPP_LOCAL_ALLOTADDR 1
#define PPP_RADIUS_ALLOTADDR 2
#define PPP_RADIUSPRI_ALLOTADDR 5

#define PPP_EAP_USER_NAME_256BYTE  256
#define VSNCP_RESERVED_LEN 500

/* EAP PACKET CODE */
#define EAP_PACKET_CODE_REQUEST        1
#define EAP_PACKET_CODE_RESPONSE       2
#define EAP_PACKET_CODE_SUCCESS        3
#define EAP_PACKET_CODE_FAILURE        4

/* PPP */
#define A11_SUBNET_LENGTH 37 /* SUBNET */
#define IMSI_S A11_IMSI_S

#define PPP_A11_ALARM_IMSI_LENGTH   15
#define PPP_A11_ALARM_BSID_LENGTH   12
#define PPP_A11_ALARM_BSID_BCD_LEN  6
#define PPP_A11_ALARM_SUBNET_LENGTH 74
#define PPP_A11_ALARM_MAX_NUM        500
#define IPV6_ADDR_LEN 8         /*IPV6��ַ����(ushort����)*/

#define Authentication_Fail 0x83
#define PPP_Negotiation_Fail 0xD2
#define RM_MAX_RADIUSGROUP_NUM 1000
#define AAA_DEFAULT_DOMAIN_INDEX 0xFFFF

#define M_DIAMAUTH_DYNAAA_AAA     1
#define M_DIAMAUTH_STATIC_AAA     0
/* ��һ�η��� DIAMETER ��Ϣ��־ */
#define DIAM_AUTH_FIRST_SEND      1
#define DIAM_AUTH_NO_FIRST_SEND   0


/*  ��PPP�����Ϣ����  */
#define PPP_DIAM_AAA_CREAT_REQ       1    /* ��Ȩ���� */
#define DIAM_AAA_PPP_CREAT_RSP       2    /* ��Ȩ��Ӧ */
#define PPP_DIAM_AAA_RELEASE_REQ     3    /* release���� */

/*��������ppp�û�����*/
#define PPP_USERTYPE_SIP 0
#define PPP_USERTYPE_MIP 1
#define PPP_USERTYPE_MIPAGENT 2
#define PPP_USERTYPE_NULL 3
/* BEGIN: Added for PN: PS10.1 HSGW by lihairong, 2013/3/9 */
#define VSNCP_OPTION_ATTACHTYPE_INIT     1
#define VSNCP_OPTION_ATTACHTYPE_HANDOFF  3
#define VSNCP_OPTION_ATTACHTYPE_LEN 3
/* END:   Added for PN: PS10.1 HSGW by lihairong, 2013/3/9 */

typedef enum
{
    A11_SEND_ECHO,
    A11_STOP_ECHO
}A11_ECHO_E;

typedef enum
{
    PPP_NEGO_LIST_NODE_LCP_START = 1,
    PPP_NEGO_LIST_NODE_VSNCP_RENEGO_START = 2,
    PPP_NEGO_LIST_NODE_MS_RELEASE_START = 3,
    PPP_NEGO_LIST_NODE_RP_RELEASE_START = 4,
    PPP_NEGO_LIST_NODE_TYPE_BUTT
} PPP_NEGO_LIST_NODE_TYPE_E;



/*VSNCP Configure Reject������*/
typedef enum
{
    PPP_VSNCP_GENERAL_ERROR = 0,
    PPP_VSNCP_UNAUTHORIZEDN_APN,
    PPP_VSNCP_EXCEED_PDN_LIMIT,
    PPP_VSNCP_NO_PGW,
    PPP_VSNCP_PGW_UNREACHABLE,
    PPP_VSNCP_PGW_REJECT = 5,
    PPP_VSNCP_INSUFFICIENT_PARAS,
    PPP_VSNCP_RES_UNAVAILABLE,
    PPP_VSNCP_ADMIN_PROHIBITED,
    PPP_VSNCP_PDN_INUSE,
    PPP_VSNCP_SUBSCRIPTION_LIMIT = 10,
    PPP_VSNCP_APN_EXIST,
    /* �����codeֵ��˽�е� */
    PPP_VSNCP_DECODE_OK,
}PPP_VSNCP_REJECT_ERRCODE_E;


/* ��Ȩ��Ӧ */
typedef struct tagDIAMAuthRspMsg
{
    ULONG ulMsgCode;                                                    /* ��Ϣ�� */
    ULONG ulSDBIndex;                                                   /* context���� ��SDB���� */
    ULONG ulQosProfileID;                                               /* qos profile id */
    ULONG ulSessionTimeout;                                             /* session timeout */
    ULONG ulAccountInterval;                                            /* Accounting-Interim-Interval */
    ULONG ulDefaultAPNId;                                               /* default APN id */
    ULONG ulULMaxBw;                                                    /* �������������� */
    ULONG ulDLMaxBw;                                                    /* �������������� */
    ULONG ulResultCode;                                                 /* result code */
    ULONG ulEAPLen;                                                     /* EAP LEN */
    DIAM_AUTH_APN_INFO_S stApnInfo[DIAM_AUTH_APN_INFO_MAX_NUMBER];      /* APN CONFIGURATION */
    USHORT usPeerId;                                                    /* PEER ID */
    USHORT us3GPPCC;                               /* �Ʒ����� */
    UCHAR aucUsername[DIAM_AUTH_USERNAME_MAX_LEN + 1];                       /* �û��� */
    UCHAR aucMnId[DIAM_AUTH_MNID_MAX_LENGTH + 1];                           /* Mobile-Node-Identifier */
    UCHAR ucUsernameLen;                                                /* �û������� */
    UCHAR ucResult;                                                     /* ��Ȩ��� */
    UCHAR ucApnInfoNum;                                                 /* APN INFO���� */
    UCHAR ucStateLen;                                                   /* APN INFO���� */
    UCHAR aucState[DIAM_AUTH_STATE_LEN];                                    /* state */
    UCHAR aucMSK[DIAM_AUTH_MSK_LEN];                                    /* MSK */
    UCHAR aucMdn[MDN_MAX_LEN+1];                                        /* ����MDN���� */
    UCHAR aucEAP[0];                                                    /* EAP */
}DIAM_AUTHRSP_S;

/* diam��Ȩ���� */
typedef struct tagPppDiamAuthMsg
{
    ULONG ulMsgType;            /* ��Ϣ���� */
    ULONG ulRpIndex;            /* SDB���� */
    ULONG ulNowUTCInSec;
    ULONG ulReleaseCode;
    USHORT usPeerID;            /* diameter aaa server ID */
    USHORT usEAPlen;            /* EAP len */
    USHORT usTokenId;           /* �����ĵ�TOKEN ID */
    USHORT usDynLocalPeerId;    /* ��̬aaa����������local���� */
    UCHAR ucAAAType;
    UCHAR ucRsv;
    UCHAR ucStateLen;
    UCHAR ucFirstSendFlag;
    A11_IMSI_S stIMSI;
    UCHAR aucUserName[DIAM_AUTH_USERNAME_MAX_LEN + 1];
    UCHAR aucState[DIAM_AUTH_STATE_LEN];                                    /* state */
    UCHAR aucAAAHost[DIAM_AUTH_DRA_HOST_MAX_LENGTH + 1];        /* origin host */
    UCHAR aucAAARealm[DIAM_AUTH_REALM_OR_HOST_MAX_LENGTH + 1];       /* origin realm */
    UCHAR aucEAP[0];
}PPP_DIAM_AUTH_MSG_S;



enum enumPPPFailedFlag
{
    PPPNEGOFAIL = 0,
    PPPLOWEDOWN,
    PPPUSERDOWN,
    PPPL2TPDOWN,
    LAPRECYCLE,
    PPPA11DOWN,
    PPPFADOWN,
    PPPPCRFCFAIL, /*pcrfc����ʧ��*/
    PPPLICESEERROR,
    PPPA11DOWNNOLCPTER, /*����Ҫ����lcp termination*/
};


/* PPP_A11_Alarm���ýṹ */
typedef struct tagAlarmLink
{
    ULONG ulPDSNIP;     /* PDSN IP */
    ULONG ulPcfIP;      /* PCF IP */
    UCHAR ucIMSI[PPP_A11_ALARM_IMSI_LENGTH + 1];   /* IMSI */
    ULONG ulTimestamp;  /* Timestamp */
    UCHAR ucErrorCode;  /* Error Code */
    UCHAR ucBSID[PPP_A11_ALARM_BSID_LENGTH + 1];   /* BSID */
    UCHAR aucSubnet[PPP_A11_ALARM_SUBNET_LENGTH + 1]; /* SUBNET */
    #ifdef __LINUX_PLATFORM__
    UCHAR ucReserve456567[3];
    #endif
}VOS_PACKED PPPA11_AlarmLink_S;


/* upʱ�Ĳ��� */
typedef struct tagPppLUpPara    /* �ײ�UP���Ĳ��� */
{
    IMSI_S stIMSI;              /* IMSI */
    ULONG  ulPcfIP;
    USHORT usPcfIndex;
    USHORT usTokenId;
    UCHAR  ucServiceOpt;
    UCHAR  beHRPDMode:1,
           bReserv:7;
    UCHAR  ucBSID[6];
    UCHAR  aucSubnet[A11_SUBNET_LENGTH + 1];      /*Subnet For HRPD d7*/
} PPP_LUPPARA_S;



/* downʱ�Ĳ��� */
typedef struct tagPppLDownPara    /* �ײ�UP���Ĳ��� */
{
    ULONG ulLcpSendFlag;  /* 1-- send   0-- nosend */
} PppLDownPara;

/* AAA��PPPC����Ϣ */
typedef struct tagPppcAaaAuthReq
{
    MSG_HDR_S stMsgHdr;             /* NE80ͷ */
    ULONG     ulMsgType;            /* ��Ϣ���� */
    ULONG     ulSDBIndex;            /* SDB���� */

    USHORT usCDBIndex;                /* GGSN:APNIndex PDSN:DomainIndex */
    UCHAR  ucPktID;                 /* �û���֤�����ID */
    UCHAR  ucUsernameLen;           /* �û������� */

    UCHAR ucUsername[A11_MAX_NAI_LENGTH + 1]; /* �û��� */
    UCHAR ucPwd[18];                /* ���� */
    UCHAR ucPwdLen;                    /* ���볤�� */
    UCHAR ucChapResponseLen;        /* Chap-Response���� */

    UCHAR ucChapResponse[256];        /* Chap-Response */
    UCHAR ucChapChallenge[256];        /* Chap-Challenge */

    UCHAR  ucChapChallengeLen;       /* Response���� */
    UCHAR  ucRes;
    USHORT usVPNID;                 /* VPN ID */

    ULONG  ulIp;                       /* IP��ַ */
    UCHAR ucIMSI[8];                /* IMSI */
    ULONG  ulIpMask;                   /* IP��ַ�������� */
    ULONG  ulG4EvtTime;               /* Event Time */
    UCHAR  aucC2CorLID[8];           /* Correlation ID */
    ULONG  ulCurVolume;         /* ����ֵ */
    ULONG  ulCurDuration;       /* ʱ��ֵ */
    ULONG  ulVUATS;                /* �����л���֮����û����� */
    USHORT usGroupIndex;                    /* test ��Ϣר�� */
    UCHAR  ucPreparedFlag;   /* ʹ��A11_PPC_TYPE_E���� */
    UCHAR  ucUpdateReason;  /* ����ԭ�� */
    UCHAR  ucRenegoFlag;    /* ��Э�̱�� */
    UCHAR  ucPPPFlag;       /*Я����־λ��ֵΪ 1��AUTH�ж���PPP��PPC��Ϣ*/
    UCHAR  ucReserved[6];

}PPPC_AAA_AUTH_REQ_S ;

typedef enum
{
    LCP_INFOR = 1,   /* LCP ��Ϣ */

    IPCP_INFOR,      /* IPCP ��Ϣ */

    SCP_INFOR,

    IPCPV6_INFOR,     /* IPV6 IPCP ��Ϣ */

    VSNCP_INFOR,      /* VSNCP ��Ϣ */

    MAGICNUM_INVALID, /* magic number ��Ч��־ */
} PPPC_USR_INFOR_FLAG_E;    /* PPPC�����û���Ϣʱʹ�õı�־ */

#define PPP_CPU_2_ON_SPU 2
#define PPP_SET_IPTECH(pppinfo, iptech) (PPP_USERTYPE_NULL == pppinfo->bIPTech ) ? (pppinfo->bIPTech = (iptech)) : NULL;

extern ULONG g_ucSelfScId;

#define PPP_SELF_SGID      g_stPppCompInfo.ullSelfSgId

#define PPP_CPU_OFFLINE  0  /* CPU����λ */
#define PPP_CPU_ONLINE   1  /* CPU��λ */


ULONG PPP_Shell_OutPut(ULONG ulRpindex, PMBUF_S *pstPMBuffNew, USHORT usProtocol);
ULONG PPP_StartIPV4CP(ULONG ulRpIdx, ULONG ulIpAddr, ULONG ulPriDns, ULONG ulSecDns);
ULONG PPP_StartIPV6CP(ULONG ulRpIdx, UCHAR* szIpV6Addr, UCHAR* szPriDns, UCHAR* szSecDns);
ULONG PPP_StopIPV4CP(ULONG ulRpIndex);
ULONG PPP_StopIPV6CP(ULONG ulRpIndex);
ULONG PPP_ReleaseIPV4CP(ULONG ulRpIndex);
ULONG PPP_ReleaseIPV6CP(ULONG ulRpIndex);
ULONG PPP_SendFakeIPV4CPReqMsg(ULONG ulRpIndex);
ULONG PPP_SendFakeIPV6CPReqMsg(ULONG ulRpIndex);

ULONG PPP_ipv6_addr_check(USHORT *pstIpv6addr);
ULONG PPP_GetNowUTCInSec(ULONG ulRpIndex);
extern ULONG PPP_SubPDNNotifyVSNCPStop(ULONG ulRpIdx, UCHAR ucPDNId, ULONG ulReleaseCode);
extern ULONG PPP_SubPDNNotifyVSNCPStart(ULONG ulRpIdx, UCHAR ucPDNId, UCHAR *pucPacket);
extern ULONG PPP_SubPDNNotifyVSNCPRenegoStart(ULONG ulRpIdx, UCHAR ucPDNId);
extern ULONG PPP_GetRetryInterval(VOID);
extern VOS_UINT32 PPP_Shell_L2tpProc(ULONG ulRpIdx, L2TP_PPPPARA_S *pstL2tpPara);
extern ULONG PPP_Shell_NotifyL2tpDown(PDN_CONTEXT_S *pstPdnContext, UCHAR ucMsgCode);
extern VOID PPP_PDNSendVSNCPReject(ULONG ulRPIndex, UCHAR *pucMsg, UCHAR ucErrCode);
extern ULONG PPP_GetIpV6Capbility(VOID);
extern VOID PPP_PDNClearVSNCP(PDN_CONTEXT_S *pstPDNContext);
extern ULONG A11_PPPC_EchoSet(A11_ECHO_E ucFlag, ULONG ulRPIndex);
extern VOS_UINT32 AM_PPP_SendMsgToLap2(USM_LAP2_MSG_S* pstMsg);
extern ULONG InsertAlarmLink(PPPA11_AlarmLink_S *pstAlarmLink);
extern ULONG PPP_SendRtMsg(VOS_UINT64 ullSrtCsi,VOS_UINT64 ullDstCsi, ULONG ulMsgType, ULONG ulMsgCode, UCHAR *pucMsg, ULONG ulMsgLen );
extern ULONG PPP_GetPeerID(ULONG ulRpIndex, USHORT *pusPeerId);
extern ULONG PPP_GetAAAType(ULONG ulRpIndex, UCHAR *pucAAAType);
extern VOID PPP_SetSendSTRFlag(ULONG ulRpIndex, ULONG ulAuthSessionState);
extern ULONG PPP_GetIpAddrByBufReq( ULONG ulRpIndex, ULONG *pulReqIpAddr );
extern ULONG PPP_BackupMasterCreUpdPppProc(ULONG ulRpIndex, ULONG ulOperType,
                                                  UCHAR **ppucCurrent, ULONG *pulEncapLen);
extern ULONG PPP_BackupSlaveCreUpdPppProc(UCHAR *pucCurrent);

extern VOS_UINT64 PPP_GetLocalL2tpCsi(VOID);
extern VOID PPP_BackupRestoreVsncp(PDN_CONTEXT_S *pstPdnContext, UCHAR ucPDNID, UCHAR ucPktId);
extern VOID PPP_BackupSlaveDelResource(ULONG ulRpIndex);
extern ULONG PPP_BackupSmoothPppInfo(SDB_PDSN_RP_CONTEXT_S *pstRpContext);

VOID PPP_BackupSmoothSubBoardDown(VOID);


extern VOID PPP_IpcpTimeOutProcForPdn(ULONG ulRpIndex);
extern VOID PPP_UpdatePcfInfo(ULONG ulRpIndex, ULONG ulPcfIp, USHORT usPcfIndex);




extern ULONG PPP_USMStartVsncp(UCHAR *pucVsncpMsg, ULONG ulRpIndex);
extern ULONG PPP_RPNodeDelete(ULONG ulRPIndex);
extern VOID PPP_RPNegoListProc(VOID* pPara);
extern ULONG PPP_RPNodeAdd(ULONG ulRpIndex, ULONG ulReleaseCode, UCHAR ucNodeType);
extern ULONG PPP_A11_GetSubBoardStat( UCHAR ucDmpuId);

#endif


