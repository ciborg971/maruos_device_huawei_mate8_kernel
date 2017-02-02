/************************************************************************
*                                                                      *
*                             Vsncp_def.h                              *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2012/12/15                                      *
*  Author:             WANGYONG                                        *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PPP��VSNCPЭ��ģ��                              *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   ����ļ�������VSNCPЭ��ģ���ȫ���ӿں������ڲ�������            *
*                                                                      *
************************************************************************/

/* Code + ID + length */
#define VSNCP_CODE_LEN 1
#define VSNCP_CODE_ID_LEN 2
#define VSNCP_LENGTH_LEN 2
#define VSNCP_HEADERLEN 4

#define VSNCP_3GPP2_OUI       0xCF0002
#define VSNCP_3GPP2_OUI_LEN   3
#define VSNCP_3GPP2_OUI_BYTE_1       0xCF
#define VSNCP_3GPP2_OUI_BYTE_2       0x00
#define VSNCP_3GPP2_OUI_BYTE_3       0x02


#define VSNCP_OPTION_PDNID_MAX 14
#define VSNCP_OPTION_PDNID_LEN 3

#define VSNCP_OPTION_PDNTYPE_IPV4    1
#define VSNCP_OPTION_PDNTYPE_IPV6    2
#define VSNCP_OPTION_PDNTYPE_IPV4V6  3
#define VSNCP_OPTION_PDNTYPE_LEN 3

#define VSNCP_OPTION_PDNADDR_INIT_LEN 3
#define VSNCP_OPTION_PDNADDR_V4_LEN 7
#define VSNCP_OPTION_PDNADDR_V6_LEN 11
#define VSNCP_OPTION_PDNADDR_V4V6_LEN 15

/* BEGIN: Deleted for PN: PS10.1 HSGW by lihairong, 2013/3/11 */

#define VSNCP_OPTION_PCO_MAX_LEN 253
#define VSNCP_OPTION_ERRCODE_LEN 3


#define VSNCP_OPTION_IPV4_DEFROUT_LEN 6

#define VSNCP_OPTION_IPV6_LINKLOCAL_LEN 10

#define VSNCP_OPTION_AMBR_LEN 2

#define VSNCP_OPTION_ADDRESS_ALLOC_CAUSE_LEN 3

#define VSNCP_OPTION_DEF_APN_IND_LEN 3
#define VSNCP_OPTION_DEF_APN     1
#define VSNCP_OPTION_NOT_DEF_APN 0

#define NEW_PDN_TYPE_DUE_TO_NETWORK_PREFERNCE 18
#define NEW_PDN_TYPE_SUCCESS                  255


/* VSNCP AMBR */
#define VSNCP_AMBR_LEN_3   3
#define VSNCP_AMBR_LEN_2   2
#define VSNCP_AMBR_LEN_1   1

#define VSNCP_AMBR_ZERO   VOS_NULL_BYTE

/* AMBR����: �ο�24.301 - 9.9.4.2 */
/* ÿ�ε���ʼֵ */
#define VSNCP_AMBR_256M_65280M_START   256000
#define VSNCP_AMBR_130M_256M_START     130000
#define VSNCP_AMBR_17M_128M_START      17000
#define VSNCP_AMBR_8700K_16000K_START  8700
#define VSNCP_AMBR_576K_8640K_START    576
#define VSNCP_AMBR_64K_568K_START      64
#define VSNCP_AMBR_1K_63K_START        1
/* ÿ�εĽ���ֵ */
#define VSNCP_AMBR_256M_65280M_END     65280000
#define VSNCP_AMBR_130M_256M_END       256000
#define VSNCP_AMBR_17M_128M_END        128000
#define VSNCP_AMBR_8700K_16000K_END    16000
#define VSNCP_AMBR_576K_8640K_END      8640
#define VSNCP_AMBR_64K_568K_END        568
#define VSNCP_AMBR_1K_63K_END          63
/* ÿ�εĲ��� */
#define VSNCP_AMBR_256M_65280M_STEP   256000
#define VSNCP_AMBR_130M_256M_STEP     2000
#define VSNCP_AMBR_17M_128M_STEP      1000
#define VSNCP_AMBR_8700K_16000K_STEP  100
#define VSNCP_AMBR_576K_8640K_STEP    64
#define VSNCP_AMBR_64K_568K_STEP      8
#define VSNCP_AMBR_1K_63K_STEP        1
/* octet 3/4 ��BIT��ʾֵ */
#define VSNCP_AMBR_1K_63K_BIT_START        0x01     /* 0000 0001 -- 0011 1111 */
#define VSNCP_AMBR_64K_568K_BIT_START      0x40     /* 0100 0000 -- 0111 1111 */
#define VSNCP_AMBR_576K_8640K_BIT_START    0x80     /* 1000 0000 -- 1111 1110 */
#define VSNCP_AMBR_8640K_BIT               0xfe     /* 1111 1110 */
/* extended byte 1 (octet 5/6) ��BIT��ʾֵ */
#define VSNCP_AMBR_8700K_16000K_BIT_START  0x01     /* 0000 0001 -- 0100 1010 */
#define VSNCP_AMBR_17M_128M_BIT_START      0x4b     /* 0100 1011 -- 1011 1010 */
#define VSNCP_AMBR_130M_256M_BIT_START     0xbb     /* 1011 1011 -- 1111 1010 */
#define VSNCP_AMBR_256M_BIT                0xfa     /* 1111 1010 */
/* extended byte 2 (octet 7/8) ��BIT��ʾֵ */
#define VSNCP_AMBR_256M_65280M_BIT_START   0x01     /* 0000 0001 -- 1111 1110 */


/* VSNCP OPTION CHECK */
#define VSNCP_CONFIG_REQ_OPTION_CHECK \
  ((VOS_TRUE != g_stVsncpOptionFlag.ucAPNNameFlag) \
    || (VOS_TRUE != g_stVsncpOptionFlag.ucAttachTypeFlag) \
    || (VOS_TRUE != g_stVsncpOptionFlag.ucPDNAddrFlag) \
    || (VOS_TRUE != g_stVsncpOptionFlag.ucPDNIDFlag) \
    || (VOS_TRUE != g_stVsncpOptionFlag.ucPDNTypeFlag))

/* VSNCP PCO OPTION */
#define VSNCP_CONFIG_REQ_PCO_OPTION_FLAG \
  (VOS_TRUE == g_stVsncpOptionFlag.ucPCOFlag)

/* ����ID */
#define VSNCP_REFRESH_PACKET_ID(old, new) \
    *(old + VSNCP_CODE_LEN) = *(new + VSNCP_CODE_LEN)



/* Э��ʧ�ܺ�,��VSNCP down�� */
#define PPP_VSNCP_NegotiationDown(pVsncpInfo) \
{ \
    /* ��VSNCP����Close�¼�,���ɽ���Э��  */ \
    PPP_VSNCP_ReceiveEventFromCore(pVsncpInfo, (LONG)PPP_EVENT_FSM_CLOSE, VOS_NULL_PTR) ; \
}

/* ���Э��ѡ��(addci)�� */
#define ADDCIPDNID(opt, val) \
    PPP_PUTCHAR(opt, pPacket); \
    PPP_PUTCHAR(VSNCP_OPTION_PDNID_LEN, pPacket); \
    PPP_PUTCHAR(val, pPacket);

#define ADDCIDEFAULTAPN(opt, val) \
    PPP_PUTCHAR(opt, pPacket); \
    PPP_PUTCHAR(VSNCP_OPTION_DEF_APN_IND_LEN, pPacket); \
    PPP_PUTCHAR(val, pPacket);

/* ����ACK���ĵ�ѡ��(ackci)�� */
#define ACKCIPDNID(opt, val) \
    if ((LONG)(ulLen -= VSNCP_OPTION_PDNID_LEN) < 0) \
    { \
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_ERROR,  \
                     "\r\n PPP_VSNCP_ackci: PDNID not exist!");  \
        goto bad; \
    } \
    PPP_GETCHAR(citype, pPacket); \
    PPP_GETCHAR(cilen, pPacket); \
    if (cilen != VSNCP_OPTION_PDNID_LEN || \
        citype != opt) \
    { \
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_ERROR,  \
                     "\r\n PPP_VSNCP_ackci: PDNID len[%u] or type[%u] err!", cilen, citype);  \
        goto bad; \
    } \
    PPP_GETCHAR(cichar, pPacket); \
    if (cichar != val) \
    { \
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_ERROR,  \
                     "\r\n PPP_VSNCP_ackci: PDNID value[%u][%u] err!", cichar, val);  \
        goto bad; \
    }

#define ACKCIDEFAULTAPN(opt, val) \
    if ((LONG)(ulLen -= VSNCP_OPTION_DEF_APN_IND_LEN) < 0) \
    { \
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_ERROR,  \
                     "\r\n PPP_VSNCP_ackci: default apn not exist!");  \
        goto bad; \
    } \
    PPP_GETCHAR(citype, pPacket); \
    PPP_GETCHAR(cilen, pPacket); \
    if (cilen != VSNCP_OPTION_DEF_APN_IND_LEN || \
        citype != opt) \
    { \
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_ERROR,  \
                     "\r\n PPP_VSNCP_ackci: default apn len[%u] or type[%u] err!", cilen, citype);  \
        goto bad; \
    } \
    PPP_GETCHAR(cichar, pPacket); \
    if (cichar != val) \
    { \
        PPP_DebugOut(MID_PPPC, PPP_DEBUG_ERROR,  \
                     "\r\n PPP_VSNCP_ackci: default apn value[%u][%u] err!", cichar, val);  \
        goto bad; \
    }


#define PPP_VSNCP_SET_AMBR(ucAMBRDLLen, aucAMBR, pucAMBR) \
{ \
    if (VSNCP_AMBR_LEN_3 == ucAMBRDLLen) \
    { \
        *pucAMBR = aucAMBR[0]; \
        *(pucAMBR + VSNCP_AMBR_LEN_2) = aucAMBR[1]; \
        *(pucAMBR + VSNCP_AMBR_LEN_2 * 2) = aucAMBR[2]; \
    } \
    else if (VSNCP_AMBR_LEN_2 == ucAMBRDLLen) \
    { \
        *pucAMBR = aucAMBR[0]; \
        *(pucAMBR + VSNCP_AMBR_LEN_2) = aucAMBR[1]; \
    } \
    else if (VSNCP_AMBR_LEN_1 == ucAMBRDLLen) \
    { \
        *pucAMBR = aucAMBR[0]; \
    } \
}


/*VSNCP ��ϢConfigure Option��typeֵ*/
typedef enum
{
    PPP_VSNCP_CO_PDNID = 1,
    PPP_VSNCP_CO_APN,
    PPP_VSNCP_CO_PDN_TYPE,
    PPP_VSNCP_CO_PDN_ADDR,
    PPP_VSNCP_CO_PDN_PCO = 5,

    PPP_VSNCP_CO_ERRCODE = 6,
    PPP_VSNCP_CO_ATTACH_TYPE,
    PPP_VSNCP_CO_IPV4_DEFRTADDR,
    PPP_VSNCP_CO_ADDRESS_ALLOC_CAUSE,
    PPP_VSNCP_CO_APN_AMBR = 10,        /* ����Ҫ����,�������Ҫ�����ն� */

    PPP_VSNCP_CO_LINK_LOCAL_ADDR = 11,
    PPP_VSNCP_CO_DEFAULT_APN_IND = 17, /* ����Ҫ����,�������Ҫ�����ն� */
    PPP_VSNCP_CO_BUTT,
}PPP_VSNCP_CO_TYPE_E;;


typedef struct tagVSNP_CONIFG_OPTION_SEQUENCE_S
{
    UCHAR aucConfigOptionType[PPP_VSNCP_CO_BUTT];
}VSNP_CONIFG_OPTION_SEQUENCE_S;



typedef struct tagVSNP_CONIFG_OPTION_FLAG_S
{
    UCHAR ucPDNIDFlag : 1;
    UCHAR ucAPNNameFlag : 1;
    UCHAR ucPDNTypeFlag : 1;
    UCHAR ucPDNAddrFlag : 1;
    UCHAR ucAttachTypeFlag : 1;
    UCHAR ucPCOFlag : 1;
}VSNP_CONIFG_OPTION_FLAG_S;


typedef struct tagPppVsncpInfo
{
    PPPINFO_S *pstPppInfo ;           /* PPP���ƿ�ָ�� */
    PPPFSM_S stFsm;                   /* VSNCPЭ��״̬�� */
    ULONG ulPDNRleaseCode;
    ULONG ulPDNIndex;
    ULONG ulApnAmbrUL;                 /* AAA��Ȩ��AMBR */
    ULONG ulApnAmbrDL;                 /* AAA��Ȩ��AMBR */
    UCHAR ucPDNID;
    UCHAR ucUsedFlag : 1;                  /*VSNCP���ƿ�ʹ�ñ��*/
    UCHAR ucRenegoFlag : 1;
    UCHAR ucDefaultAPNFlag : 1;
    UCHAR ucApnAmbrDLFlag : 1;
    UCHAR ucApnAmbrULFlag : 1;
} PPPVSNCPINFO_S ;


/* vsncpѡ�� */
typedef ULONG (*VSNCP_OPTION_DECODE) (PPPCONIFG_OPTION_S *, PDN_PPP_VSNCP_REQ_S *);
typedef ULONG (*VSNCP_OPTION_ENCODE) (UCHAR *, PDN_CONTEXT_S *, ULONG *, PDN_PPP_VSNCP_REQ_S *);

#define VSNCP_OPTION_DECODE_REG(type, decode_handle) {g_pVsncpOptionDecode[(type)] = (decode_handle);}
#define VSNCP_OPTION_ENCODE_REG(type, encode_handle) {g_pVsncpOptionEncode[(type)] = (encode_handle);}



extern ULONG PPP_Shell_ReceiveVSNCPUpFromCore(PPPINFO_S *pstPppInfo);
extern USHORT PPP_VSNCP_ackci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG ulLen);
extern VOID PPP_VSNCP_addci(PPPFSM_S *pstFsm, UCHAR *pPacket);
extern ULONG PPP_VSNCP_CheckOptionIsChange(PDN_PPP_VSNCP_REQ_S *pstNewVsncpReqInfo,
                                    PDN_PPP_VSNCP_REQ_S *pstOldVsncpReqInfo,
                                    USHORT usOldAPNIndex,
                                    UCHAR ucPDNType);
extern USHORT PPP_VSNCP_cilen(PPPFSM_S *pstFsm);
extern ULONG PPP_VSNCP_ConAckPactketProc(PPPINFO_S *pstPppInfo,
                                           UCHAR *pHead,
                                           UCHAR *pPacket,
                                           ULONG ulLen);
extern ULONG PPP_VSNCP_ConRejPactketProc(PPPINFO_S *pstPppInfo,
                                           UCHAR *pHead,
                                           UCHAR *pPacket,
                                           ULONG ulLen);
extern ULONG PPP_VSNCP_ConReqPactketProc(PPPINFO_S *pstPppInfo,
                                           UCHAR *pHead,
                                           UCHAR *pPacket,
                                           ULONG ulLen);
extern VOID PPP_VSNCP_down(PPPFSM_S *pstFsm);
extern VOID PPP_VSNCP_finished(PPPFSM_S *pstFsm);
extern VOID PPP_CORE_VSNCPFinishProc(PPPINFO_S *pstPppInfo);
extern VOID PPP_VSNCP_FreshPDNContext(PPPVSNCPINFO_S *pstVSNCPInfo, PDN_CONTEXT_S *pstPDNContext, PPPINFO_S *pstPppInfo);
extern ULONG PPP_VSNCP_GetPDNContextByPDNID(ULONG ulRpIdx, UCHAR ucPDNId, PDN_CONTEXT_S **ppstPDNContext);
extern VOID PPP_VSNCP_Init(PPPINFO_S *pstPppInfo,
                             PPPVSNCPINFO_S *pstVSNCPInfo,
                             PDN_CONTEXT_S *pstPDNContext,
                             UCHAR ucPDNID);
extern VOID PPP_VSNCP_PactketProc(PPPINFO_S *pstPppInfo,
                                    UCHAR *pHead,
                                    UCHAR *pPacket,
                                    ULONG ulLen,
                                    UCHAR ucCode);
extern VOID PPP_VSNCP_ReceiveEventFromCore(VOID *pstVsncpInfo, ULONG ulCmd, char *pPara);
extern VOID PPP_VSNCP_ReceivePacket (VOID *pstVsncpInfo, UCHAR* pHead, UCHAR* pPacket, ULONG ulLen);
extern USHORT PPP_VSNCP_rejci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG ulLen);
extern UCHAR PPP_VSNCP_reqci(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG *pulLen);
extern VOID PPP_VSNCP_resetci(PPPFSM_S *pstFsm);
extern VOID PPP_VSNCP_SendReject(PPPINFO_S *pstPppInfo,
                                   UCHAR *pucMsg,
                                   UCHAR ucErrCode,
                                   USHORT usPdnId);
extern VOID PPP_VSNCP_starting(PPPFSM_S *pstFsm);
extern ULONG PPP_VSNCP_TermAckPactketProc(PPPINFO_S *pstPppInfo,
                                            UCHAR *pHead,
                                            UCHAR *pPacket,
                                            ULONG ulLen);
extern ULONG PPP_VSNCP_TermReqPactketProc(PPPINFO_S *pstPppInfo,
                                            UCHAR *pHead,
                                            UCHAR *pPacket,
                                            ULONG ulLen);
extern VOID PPP_VSNCP_up(PPPFSM_S *pstFsm);
extern ULONG PPP_VSNCP_UpResetCi(PPPINFO_S *pstPppInfo);
extern UCHAR *PPP_VSNCP_DecodePactket(UCHAR *pPacket,
                               ULONG ulLen,
                               USHORT *pusPdnId,
                               PPPINFO_S *pstPppInfo);
extern ULONG PPP_VSNCP_AttachTypeEncode(UCHAR *pucPacket,
                                        PDN_CONTEXT_S *pstPDNContext,
                                        ULONG *pulLen,
                                        PDN_PPP_VSNCP_REQ_S *pstVsncpInfo);
extern VOID PPP_VSNCP_Termaddci(PPPFSM_S *pstFsm, UCHAR *pPacket);

extern VOID PPP_VSNCP_Clear(PPPVSNCPINFO_S *pstVsncpInfo, PDN_CONTEXT_S *pstPDNContext);
extern UCHAR PPP_VSNCP_SetRejectCodeByReleaseCode(ULONG ulReleaseCode);
extern ULONG PPP_NotifyIpv6SendRA(ULONG ulRpIndex, UCHAR ucPDNId);

extern ULONG PPP_VSNCP_NotifyVSNCPStop(PPPINFO_S *pstPppInfo, UCHAR ucPDNId);
extern ULONG PPP_VSNCP_NotifyVSNCPStart(PPPINFO_S *pstPppInfo, UCHAR ucPDNId);


extern VOS_VOID A11_OM_HSGWPerfStatisticPCFUnit(ULONG ulStatisticType, ULONG ulPcfIp, ULONG ulOperType, ULONG ulValue);

extern ULONG PDN_VsncpNotifyGetPCO(PDN_CONTEXT_S *pstPdnContext, PDN_PPP_VSNCP_REQ_S *pstVsncpReq);
extern ULONG PDN_VsncpNotifyReconnect(PDN_CONTEXT_S *pstPdnContext, PDN_PPP_VSNCP_REQ_S *pstVsncpReq);
extern VOID PDN_FsmStopTimer(ULONG ulTimerType, ULONG ulTimerId);
extern UCHAR PPP_VSNCP_GetAMBRLength(ULONG ulAMBR);
extern ULONG PPP_GetPDNContextByPDNID(UCHAR ucPDNId, PDN_CONTEXT_S **ppstPDNContext);
extern VOID PPP_VSNCP_ClearPdnContext(VOS_UINT8 ucPdnId);

