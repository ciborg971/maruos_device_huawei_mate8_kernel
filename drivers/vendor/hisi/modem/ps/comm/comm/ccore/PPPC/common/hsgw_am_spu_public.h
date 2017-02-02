

#ifndef __HSGW_AM_PUBLIC_H__
#define __HSGW_AM_PUBLIC_H__


#define DIAM_AUTH_DYNAAA_CONTEXT_ALARM_FLAG  "DIAM_DYNAAA_CONTEXT_ALARM_FLAG"
#define DIAM_AUTH_DYNAAA_CONTEXT_ALARM_NUM 64

/* HSGW/PDSN ״̬��IDͳһ���� */
typedef enum
{
    E_FSM_ID_USM = 1,
    E_FSM_ID_A11,
    E_FSM_ID_PDN,
    E_FSM_ID_SIPV4,
    E_FSM_ID_SIPV6,
    E_FSM_ID_CMIP,
    E_FSM_ID_PMIPV4,
    E_FSM_ID_PMIPV6_4,
    E_FSM_ID_PMIPV6_6,
    E_FSM_ID_L2TP,
    E_FSM_ID_EHRPD,
    E_FSM_ID_DHCP,
    E_FSM_ID_PMV6,

    E_FSM_ID_BUTT
}HSGW_FSM_ID_E;

/*�ӿ�����*/
typedef struct tagFA_COF_CFG_S
{
    ULONG      ulCmip4Vpn4Index; 
    ULONG      ulFaCofAddrCmipV4;         /* FAת����ַV4*/
    ULONG      ulFaCofSubIndexCmipv4;     /* PI�ӿ�subindex */

    ULONG      ulPmip4Vpn4Index; 
    ULONG      ulFaCofAddrPmipV4;
    ULONG      ulFaCofSubIndexPmipv4;     /* PI�ӿ�subindex */

    ULONG      ulPdsnPmipv6Vpn6Index;
    in6_addr   stPdsnPmipv6Vpn6CofAddr;
    ULONG      ulPdsnPmipv6Vpn6CofSubIndex;

    ULONG      ulHsgwPmipv6Vpn4Index; 
    ULONG      ulHsgwPmipv6Vpn4CofAddr;
    ULONG      ulHsgwPmipv6Vpn4CofSubIndex;

    ULONG      ulHsgwPmipv6Vpn6Index;
    in6_addr   stHsgwPmipv6Vpn6CofAddr;
    ULONG      ulHsgwPmipv6Vpn6CofSubIndex; 

    ULONG      ulFaCofIndexCmipv4;        /* PI�ӿ�����*/
    ULONG      ulFaCofIndexPmipv4;        /* PI�ӿ�����*/
}VOS_PACKED FA_COF_CFG_S;


/*  ��ȨӦ��ԭ��ֵ  */
#define  DIAM_AUTH_SUCCESS           0  /* ��Ȩ����ɹ� */
#define  DIAM_AUTH_FAIL              1  /* ��Ȩ����ܾ� */
#define  DIAM_AUTH_SRV_ERR           2  /* ���������ϻ��������ͨ���쳣 */
#define  DIAM_AUTH_CLT_ERR           3  /* DIAM AUTHģ������Դ�ľ����쳣 */
#define  DIAM_AUTH_MSG_FMT_ERR       4  /* ��Ϣ��ʽ���� */
#define  DIAM_AUTH_SERVER_DELETE     6  /* 3GPP SERVERȥ�� */


#define MDN_MAX_LEN 20
#define RD_HW_VPN_NAME_LEN_MAX          31     /* VPN Name�Ϊ31���ֽ� */
#define MDN_BCD_MAX_LEN_WITH_PREFIX 15
#define MDN_BCD_MAX_LEN_WITHOUT_PREFIX 13

#define A11_RESV_MESSAGE       0x18  /*Resv message*/

#define A11_RESVCONF_MESSAGE  0x19  /*ResvConf message*/

#define A11_RESVERR_MESSAGE   0x20  /*ResvErr message*/
#define A11_RESV_ERR_MESSAGE       0x21  /*Resv err message*/
#define A11_RESV_NW_MESSAGE       0x22  /*����෢���Resv message*/
/* Added end by zhuying 51443 at 2007-04-07 PDSNV8R5C2 for RSVP */



/* ==============�������Ͷ���============== */
#define PDN_UPD_MSK_AUXA10_CREATE       0x00000001      /* ��A10���� */
#define PDN_UPD_MSK_AUXA10_RELEASE      0x00000002      /* ��A10�ͷ� */
#define PDN_UPD_MSK_AUXA10_CHANGE       0x00000004      /* ��A10�޸� */
#define PDN_UPD_MSK_PCF_HANDOFF         0x00000008      /* PCF�л� */
#define PDN_UPD_MSK_RAT_CHANGE          0x00000010      /* SO�л� */
#define PDN_UPD_MSK_QOS_CHANGE          0x00000020      /* QOS�ı� */
#define PDN_UPD_MSK_LOC_CHANGE          0x00000040      /* λ��(BSID)�ı� */
#define PDN_UPD_MSK_SUBNET_CHANGE       0x00000080      /* SUBNET�ı� */
#define PDN_UPD_MSK_AIRSTATE_CHANGE     0x00000100      /* �տ�״̬�ı� */
#define PDN_UPD_MSK_COA                 0x00000200      /* AAA����COA */
#define PDN_UPD_MSK_QCI_ARP             0x00000400      /*QCI ARP����*/
#define PDN_UPD_MSK_AMBR                0x00000800  
#define PDN_UPD_MSK_STACK_CREATE        0x00001000      /* ˫ջ���� */
#define PDN_UPD_MSK_STACK_RELEASE       0x00002000      /* ˫ջ(֮һ)�ͷ� */
#define PDN_UPD_MSK_OLD_PCF_RELEASE     0x00004000      /*�ϵ�pcf����ȥ�����*/

#define HSGW_MAX_APP_NUM                8192
typedef enum
{
    PDN_UPDTYPE_INVALID = 0, 
    PDN_UPDTYPE_A11     = 1,     /* A11����ĸ��� */
    PDN_UPDTYPE_SUBNET,          /* PDN��״̬������ĸ��� */
    PDN_UPDTYPE_COA,             /* COA����ĸ��� */    
    PDN_UPDTYPE_PCC_PCRFC,       /* PDSN PCC�û�PCRFC������������� */    
    PDN_UPDTYPE_PCC_ROLLBACK,    /* PDSN PCC�û��ع���SIP���� */
    PDN_UPDTYPE_EHRPD_PPP_RENEGO,/* ehrpd��Э�� */
    PDN_UPDTYPE_BUTT,
}PDN_UPDATE_TYPE_E;

/* PDN�ĸ�����Ϣͷ */
typedef struct
{
    ULONG ulUpdateType;     /* ��������, PDN_UPDATE_TYPE_E */
    ULONG ulUpdateMask;     /* �������µ����� */
}PDN_UPDATE_MSGHEAD_S;

#define HSGW_AM_MSG_ENCAP_STR(PucMsgStorPointer, PucStr, UlStrLen) \
    (VOID)VOS_MemCpy((PucMsgStorPointer), (PucStr), (UlStrLen));\
    (PucMsgStorPointer) = ((UCHAR *)(PucMsgStorPointer)) + (UlStrLen);


extern  VOID AUTH_RegProductCallBackFun4DEF(VOS_VOID);
extern ULONG *g_aulHSGWDynAAAContextAlarmFlag;

VOS_UINT32 A11_GetGrmSruCpuRate(ULONG *pulSruCpuValue);
VOID USM_HsgwApnAlarmRefresh(VOID);

extern ULONG  A11_StringTo4Bits( UCHAR *strSrc, UCHAR DstArr[], UCHAR ucMaxNum );


#endif /* __HSGW_AM_PUBLIC_H__ */
