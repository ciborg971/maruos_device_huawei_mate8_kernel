#ifndef __LI_AM_PUBLIC_H__
#define __LI_AM_PUBLIC_H__

/* ��ע���ͷ�ļ�һ��Ҫ���ܰ��������궨��ͽṹ�� */

#define AUTH_PAP_PPP 1
#define AUTH_CHAP_PPP 0

/*��Ҫ����LI_TARGET_TYPE_E ��ȷ��*/
#define  LI_USM_TARGET_TYPE_IMSI  1 /* ͬLI_TARGET_TYPE_IMSI */
#define  LI_USM_TARGET_TYPE_ESN   3 /* ͬLI_TARGET_TYPE_ESN */
#define  LI_USM_TARGET_TYPE_MDN   4 /* ͬLI_TARGET_TYPE_MDN */
#define  LI_USM_TARGET_TYPE_MEID  5 /* ͬLI_TARGET_TYPE_MEID */


typedef enum
{
    PDSN_SUCCESS =  0,
    PDSN_FAIL    
}A11_LI_PDSN_FLAG;

typedef enum
{
    PDSN_OPTION_SETUP = 0,       /* ����Ự�����¼�*/
    PDSN_OPTION_RELEASE,         /* ����Ự�ͷ��¼� */
    PDSN_OPTION_HANDOFF,         /* ����Ự�л��¼� */
    PDSN_OPTION_START_SESSION,   /* ��ʼ��������Ự�¼� */
    PDSN_PACKET_FILTER           /* �������ݹ����¼� */
} A11_LI_PDSN_OPTION_E;

typedef enum
{
    E_LI_A11_CHECK_OK    = 0,           /* Registration Accepted */
    E_LI_A11_REASON_UNSPECIFIED = 0x80, /* reason unspecified */
    E_LI_A11_ADMIN_PROHIBTED = 0x81,    /* administratively prohibited */
    E_LI_A11_INSUF_RES = 0x82,          /* insufficient resources */
    E_LI_A11_AUTHEN_FAILED = 0x83,      /*mobile node failed authentication */
    E_LI_A11_ID_MISMATCH = 0x85,        /* identification mismatch */
    E_LI_A11_POOR_FORM = 0x86,          /* poorly formed request */
    E_LI_A11_UNKNOWN_PDSN_IP = 0x88,    /* unknown PDSN address */
    E_LI_A11_TUNNELS_NOT_SET =0x89,
    E_LI_A11_T_BIT_NOT_SET = 0x8A,      /* reverse tunnel is mandatory and 'T' bit not set */
    E_LI_A11_UNSUPPORT_VEND_ID = 0x8D,  /* unsupported vendor ID */
    E_LI_A11_UNKNOWN_MSG_TYPE = 0X8E,
    E_LI_A11_RESEND_MSG = 0x8F,
    E_LI_A11_UNSUPPORT_SERVICEOPT_HRPD = 0X90,/* add by dongenjie for HRPD support */
    E_LI_RELEASE_REASON_UNSPECIFIED = 0xC1,
    E_LI_RELEASE_PPP_TIMEOUT  = 0xC2,
    E_LI_RELEASE_REGISTRATION_TIMEOUT = 0xC3,
    E_LI_RELEASE_PDSN_ERR = 0xC4,
    E_LI_RELEASE_inter_PCFHANDOFF  = 0xC5,
    E_LI_RELEASE_inter_PDSNHANDOFF = 0xC6,
    E_LI_RELEASE_PDSN_OM_INTERVENTION= 0xC7,
    E_LI_RELEASE_ACCT_ERR = 0xC8,
    E_LI_PPP_Negotiation_Fail = 0xD2,
    E_LI_A11_CHECK_LI_USED = 0xff    /* LIģ��ʹ�� */
} A11_LI_FAILORRELEASE_CAUSE_E;


typedef struct tagAU_INFO_S
{
    UCHAR    ucSubPasswordLen;
    UCHAR    szSubPassword[20];
    UCHAR    ucAuType;
    UCHAR    ucChapChallengeLen;
    UCHAR    szChapChallenge[16];

} AuInfo_S;

#define IMSIBCDLEN   8
#define ESNBCDLEN    4
#define MEIDBCDLEN   7
#define MDNBCDLEN    8
#define NAILEN      65

typedef struct 
{
    USHORT usIriTargetMap;
    USHORT usIdpTargetMap;
    UCHAR  ucLiFlag;
    UCHAR  ucRev;
}LI_USM_FLAG_S;


typedef struct tagLI_X2PACKET_FILTER_INFO
{
    struct  tagLI_X2PACKET_FILTER_INFO *next;
    ULONG length;
    UCHAR value[100];
} LI_X2PACKET_FILTER_INFO;


typedef struct 
{        
    ULONG ulPdpIndex;       /* RP ���������� */
    ULONG ulTeidc;           
    ULONG ulPcfKey;         /* PCF��ʶ */
    ULONG ulHaAddr;
    ULONG ulCoAAddr;
    ULONG ulSetUpTimeInSec;

    UCHAR szIMSI[IMSIBCDLEN];        /* ����BCD�� */
    UCHAR szESN[ESNBCDLEN];          
    UCHAR szMEID[MEIDBCDLEN]; 
    UCHAR ucMeidLen;
    UCHAR szMDN[MDNBCDLEN];          /* ����BCD�� */
    
    UCHAR szNAI[NAILEN];
    UCHAR ucNaiLen;
    UCHAR ucImsiLen;
    UCHAR ucEsnLen;
    
    UCHAR aucBsid[6];
    UCHAR ucMdnLen;      
    UCHAR ucBsidFlag;
    
    UCHAR szPdsnIpAddr[16];   /* DPSN��ַ */
    UCHAR szSubIpAddr[16];    /* ��������Ϊ����Ŀ������IP��ַ */
    
    UCHAR ucPdsnIpType;       /* 0:IPv4, 1:IPv6 */
    UCHAR ucSubIpType;        /* 0:IPv4, 1:IPv6 */
    UCHAR ucSIPorMIP;         /* ָ������Ŀ��ʹ�õ��Ǽ�IP�����ƶ�IP��SIP��PDSN��AAA���䣬MIP��HA���䡣 */
    UCHAR ucGotOldIpFlag;     /* �л�ʱ�Ƿ��ܻ�ȡ��ԭPCF IP 0:��ȡ����,1:��ȡ��*/

    UCHAR ucAccPcfIpType;     /* 0:IPv4, 1:IPv6 */
    UCHAR ucCurPcfIPType;
    UCHAR uchandOffType;      /* handoff ���� */
    UCHAR ucOtherNetIdLen;

    UCHAR szAccPcfIpAddr[16]; /* �л�ʱ��ʾԭPCF IP */
    UCHAR szCurPcfIPAdd[16];  /* �л�ʱ��ʾ�л���PCF IP */
    UCHAR szOtherNetId[20];   /* handoff ���� */
    
    UCHAR szCanId[10];        /* ��ǰ���������ʶ */
    UCHAR ucCanIdLen;
    UCHAR ucPanIdLen;
    
    UCHAR szPanId[10];        /* �л�ǰ�����ʶ */
    UCHAR ucSuccessFlag;
    UCHAR ucPacketFilterFlag; /*packerfilter Я�����*/

    UCHAR ucAuType;           /* ����Ŀ������������ʱ����AAA�н��м�Ȩ�ķ�ʽ */
    UCHAR ucAuFlag;           /* 1:ucAuType��Ч�� 0:ucAuType��Ч */
    UCHAR ucSubPasswordLen;   
    UCHAR ucChapChallengeLen;
    
    UCHAR szSubPassword[20];  /* ����Ŀ����˻����� */
    UCHAR szChapChallenge[16];/* ������CHAP��֤ʱ�û��������һ��16���ص������ */

    USHORT usFailureCause;    /* ��������ʧ��ԭ��ֵ */
    USHORT usReleaseCause;    /* ȥ��ԭ��ֵ */

    USHORT usIriTargetMap;    /*������䵽�������е�bitmap ֵ*/
    USHORT usIdpTargetMap;    /*������䵽�������е�bitmap ֵ*/
    
    UCHAR ucPortType;         /*PPP�û�����IP �û�*/
    UCHAR ucSduVcpu;
    
    UCHAR ucRev[2];

    LI_X2PACKET_FILTER_INFO stX2PacketFilterInfo;

}LI_CDMA2000_PDPINFO_S;

#define PORTTYPE_PPP  2
#define PORTTYPE_IPV4 0


/*�û�����ʧ�ܣ���û�з��������ĵĳ���*/
extern VOID  LI_PdsnSetInfoWithoutContext(LI_CDMA2000_PDPINFO_S *pstPdpInfo, A11_LI_PDSN_OPTION_E enEvent, UCHAR ucCause);
/*�������Ѿ�����ĳ���*/
extern VOID  LI_PdsnSetInfo(LI_CDMA2000_PDPINFO_S *pstPdpInfo, A11_LI_PDSN_OPTION_E enEvent, A11_LI_PDSN_FLAG ucSuccessFlag);
extern VOID  USM_SetLiFlagToRpcontext(ULONG ulRpindex, LI_USM_FLAG_S *pstLiUsmFlag);
extern ULONG USM_LIGetContextByTargetID(UCHAR ucTargetIdType, UCHAR *pucTargetId, LI_CDMA2000_PDPINFO_S *pstLiPdpinfo);
extern ULONG USM_LIGetContextByRpintexforBatchBackup(ULONG ulRpIndex, LI_CDMA2000_PDPINFO_S *pstLiPdpinfo);
extern ULONG LI_PdsnIsInterceptBan(LI_CDMA2000_PDPINFO_S *pstPdpInfo);
extern ULONG USM_LIRelContextByTargetID(UCHAR ucTargetIdType, UCHAR * pucTargetId);

#endif /* __LI_AM_PUBLIC_H__ */

