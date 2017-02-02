/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              3ah_ha.h
*
*  Project Code: VISPV100R007
*   Module Name: ETH OAM 3AH  
*  Date Created: 2008-2-28
*        Author: LY(57500)
*   Description: 3AHģ��HAͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-2-28  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _3AH_HA_H_
#define _3AH_HA_H_

#ifdef __cplusplus
extern "C"{
#endif


/*  3AHģ��HA������Ϣͷ     */
typedef struct tagOam3ahHaHead
{
    USHORT  usBakType;          /* 3AH������Ϣ����  */
    USHORT  usBakLen;           /* 3AH������Ϣ����  */
}OAM3AH_HA_HEAD_S;

/* ha tlv head(type+len) */
typedef struct tagOam3ahHaTlv
{
    USHORT  usHaTlvType;
    USHORT  usHaTlvLen;
}OAM3AH_HA_TLV_HEAD_S;

/* �û����õ���·�¼��������޲������ݽṹ */
typedef struct tagHaEventWinThrsh
{
    ULONG   ulEventType;          /* ��·�¼�����,��ʱ�ɲ���,��ҪΪ������������ʹ��,��Ҫͨ�������ֲ�ͬ��������·�¼�*/
    ULONG   ulEventEnable;        /* �Ƿ�ʹ��         */
    ULONG   ulEventWindow;        /* ��·�¼�����     */
    ULONG   ulEventThresh;        /* ��·�¼�����     */
}OAM3AH_HA_LINKEVT_S;

/* INFO TLV HA���ݽṹ */
typedef struct tagHaInfoTlv
{
        UCHAR   ucInfoType;             /* INFO TYPE: ���˻�Զ�        */
        UCHAR   ucInfoLen;              /* INFO LEN:��ǰ0x10            */
        UCHAR   ucOamVersion;           /* OAM �汾��                   */
        UCHAR   ucState;                /* INFO TLV״̬�ֶ�             */
        USHORT  usRevision;             /* ���ð汾��                   */
        USHORT  usOamPduCfg;            /* OAMPDU��С�ֶ�               */
        UCHAR   ucOamCfg;               /* OAMPDU config�ֶ�            */
        UCHAR   aucOUI[OAMPDU_OUI_LENGTH];   /* OUI������Ϣ              */
        ULONG   ulVendorInfo;           /* ��Ʒ��Ϣ                     */
}OAM3AH_HA_INFOTLV_S;

/* info oampdu: org spec tlv back; append to OAM3AH_HA_PORTCFG_S */
typedef struct tagOam3ahInfoOrgSpec
{
    ULONG ulLclBoardState;  /* 0 - OAM3AH_BOARD_STATE_NULL,1-OAM3AH_BOARD_STATE_MASTER,2-OAM3AH_BOARD_STATE_SLAVE */
    ULONG ulRmtBoardState;  /* 0,1,2 - same pre */
}OAM3AH_HA_INFO_ORGSPEC_S;

/* �˿�������Ϣ���ݽṹ */
typedef struct tagOam3ahHaPortInfo
{
    ULONG   ulIfIndex;                  /* �ӿ�����                     */
    ULONG   ul3ahEnable;                /* �ӿ�ʹ�ܱ��                 */
    ULONG   ulDetectIntervar;           /* ̽������,msΪ��λ            */
    ULONG   ulFsmState;                 /* �ӿ�3AH״̬��״̬            */
    USHORT  usDscvrProcessStatue;       /* ���ػ�Զ˷����Ƿ����       */
    UCHAR   aucPeerMacAddr[MACADDRLEN]; /* �Զ�physical��ַ                  */
    USHORT  usFlags;                    /* OAMPDU flag�ֶ�              */
    USHORT  usLbTestMode;               /* ���ز���ģʽ,0=VISP�������ģʽ;1=NP���ز���ģʽ                     */
    ULONG   ulFaultEnable;              /* ����ͨ��ʹ��״̬,�ӵ�0λ����2λ�ֱ��ʾ��·����/��������/�����¼�    */

    OAM3AH_HA_LINKEVT_S     stEventSymPrd;      /* ������������¼����ں�����   */
    OAM3AH_HA_LINKEVT_S     stEventFrame;       /* ��֡�¼����ں�����           */
    OAM3AH_HA_LINKEVT_S     stEventFrmPrd;      /* ��֡�����¼����ں�����       */
    OAM3AH_HA_LINKEVT_S     stEventFrmSecSum;   /* ��֡���¼����ں�����         */
    
    OAM3AH_HA_INFOTLV_S     stHaLclInfoTlv;     /* ����INFO TLV                 */
    OAM3AH_HA_INFOTLV_S     stHaRmtInfoTlv;     /* �Զ�INFO TLV                 */
}OAM3AH_HA_PORTCFG_S;

/* �û����õ�֧��64λ��·�¼��������޲������ݽṹ */
typedef struct tagHaEventWinThrshEx
{
    ULONG   ulEventType;          /* ��·�¼�����,��ʱ�ɲ���,��ҪΪ������������ʹ��,��Ҫͨ�������ֲ�ͬ��������·�¼�*/
    ULONG   ulEventEnable;        /* �Ƿ�ʹ��         */
    DULONG_S stdulEventWindow;        /* ��·�¼�����     */
    DULONG_S stdulEventThresh;        /* ��·�¼�����     */
}OAM3AH_HA_LINKEVT_Ex_S;


typedef struct tagHaEventWinThrshTlv
{
    OAM3AH_HA_LINKEVT_Ex_S     stEventSymPrd;      /* ������������¼����ں�����   */
    OAM3AH_HA_LINKEVT_Ex_S     stEventFrame;       /* ��֡�¼����ں�����           */
    OAM3AH_HA_LINKEVT_Ex_S     stEventFrmPrd;      /* ��֡�����¼����ں�����       */
    OAM3AH_HA_LINKEVT_Ex_S     stEventFrmSecSum;   /* ��֡���¼����ں�����         */
}OAM3AH_HA_LINKEVT_TLV_S;

/* ������·�¼�������Ϣ��HA���ݰ��� */
#define OAM3AH_HA_PACK_LINKEVT(pst3ahBakEvt, pst3ahLinkEvt)\
{\
    (pst3ahBakEvt)->ulEventType = OAM3AH_EVENT_TYPE(pst3ahLinkEvt);\
    (pst3ahBakEvt)->ulEventEnable = (pst3ahLinkEvt)->ulEventEnable;\
    (pst3ahBakEvt)->ulEventWindow = 0;\
    (pst3ahBakEvt)->ulEventThresh = 0; \
}

/* �ӱ��ݰ��лָ���·������Ϣ */
#define OAM3AH_HA_UNPACK_LINKEVT(pst3ahLinkEvt,pst3ahBakEvt)\
{\
    OAM3AH_EVENT_TYPE(pst3ahLinkEvt)= (pst3ahBakEvt)->ulEventType;\
    (pst3ahLinkEvt)->ulEventEnable = (pst3ahBakEvt)->ulEventEnable;\
    (pst3ahLinkEvt)->stdulEventWindow.ulDulLo = (pst3ahBakEvt)->ulEventWindow;\
    OAM3AH_EVENT_THRESHOLDLo(pst3ahLinkEvt) = (pst3ahBakEvt)->ulEventThresh; \
}

#define OAM3AH_HA_PACK_LINKEVT_EX(pst3ahBakEvt, pst3ahLinkEvt)\
{\
    (pst3ahBakEvt)->ulEventType = OAM3AH_EVENT_TYPE(pst3ahLinkEvt);\
    (pst3ahBakEvt)->ulEventEnable = (pst3ahLinkEvt)->ulEventEnable;\
    DULONG_S_COPY((pst3ahBakEvt)->stdulEventWindow, (pst3ahLinkEvt)->stdulEventWindow);\
    DULONG_S_COPY((pst3ahBakEvt)->stdulEventThresh, pst3ahLinkEvt->stLinkEventInfo.stDulErrThreshold);\
}

#define OAM3AH_HA_UNPACK_LINKEVT_EX(pst3ahLinkEvt,pst3ahBakEvt)\
{\
    OAM3AH_EVENT_TYPE(pst3ahLinkEvt)= (pst3ahBakEvt)->ulEventType;\
    (pst3ahLinkEvt)->ulEventEnable = (pst3ahBakEvt)->ulEventEnable;\
    DULONG_S_COPY((pst3ahLinkEvt)->stdulEventWindow, (pst3ahBakEvt)->stdulEventWindow);\
    DULONG_S_COPY(pst3ahLinkEvt->stLinkEventInfo.stDulErrThreshold, (pst3ahBakEvt)->stdulEventThresh); \
}

/* ����TLV��Ϣ��HA���ݰ��� */
#define OAM3AH_HA_PACK_INFOTLV(pst3ahBakInfo, pst3ahInfo) \
{\
    (pst3ahBakInfo)->ucInfoType = (pst3ahInfo)->ucInfoType;\
    (pst3ahBakInfo)->ucInfoLen = (pst3ahInfo)->ucInfoLen;\
    (pst3ahBakInfo)->ucOamVersion = (pst3ahInfo)->ucOamVersion;\
    (pst3ahBakInfo)->ucState = (pst3ahInfo)->unState.ucState;\
    (pst3ahBakInfo)->usRevision = (pst3ahInfo)->usRevision;\
    (pst3ahBakInfo)->usOamPduCfg = (pst3ahInfo)->usOamPduCfg;\
    (pst3ahBakInfo)->ucOamCfg = (pst3ahInfo)->unOamCfg.ucConfig;\
    (VOID)TCPIP_Mem_Copy((pst3ahBakInfo)->aucOUI, OAMPDU_OUI_LENGTH, (pst3ahInfo)->aucOUI, OAMPDU_OUI_LENGTH);\
    (pst3ahBakInfo)->ulVendorInfo = (pst3ahInfo)->ulVendorInfo;\
}

/* �ӱ��ݰ��лָ�TLV��Ϣ */
#define OAM3AH_HA_UNPACK_INFOTLV(pst3ahInfo, pst3ahBakInfo) \
{\
    (pst3ahInfo)->ucInfoType = (pst3ahBakInfo)->ucInfoType;\
    (pst3ahInfo)->ucInfoLen = (pst3ahBakInfo)->ucInfoLen;\
    (pst3ahInfo)->ucOamVersion = (pst3ahBakInfo)->ucOamVersion;\
    (pst3ahInfo)->unState.ucState = (pst3ahBakInfo)->ucState;\
    (pst3ahInfo)->usRevision = (pst3ahBakInfo)->usRevision;\
    (pst3ahInfo)->usOamPduCfg = (pst3ahBakInfo)->usOamPduCfg;\
    (pst3ahInfo)->unOamCfg.ucConfig = (pst3ahBakInfo)->ucOamCfg;\
    (VOID)TCPIP_Mem_Copy((pst3ahInfo)->aucOUI, OAMPDU_OUI_LENGTH, (pst3ahBakInfo)->aucOUI, OAMPDU_OUI_LENGTH);\
    (pst3ahInfo)->ulVendorInfo = (pst3ahBakInfo)->ulVendorInfo;\
}

/* �������ͣ������ڹ���HA�ṹͷ��ucOperation�ֶ� */
#define OAM3AH_HA_BATCH         0x1
#define OAM3AH_HA_REALTIME      0x2

/* 3AH������Ϣ����     */
typedef enum enOam3ahHaBakType
{
    OAM3AH_HA_PORTCFG = 0x0100,         /* ���ƿ鱸��,����PORTCFG�ֶθ�����TLV��TYPEֵΪ0x0101��0x0102��etc ... */
    OAM3AH_HA_INFO_ORGSPEC = 0x0101,    /* info OAMPDU: ORG SPEC TLV(board type) */
    OAM3AH_HA_LINKEVT = 0x0102,         /* DULONG LINKEVT TLV TYPE*/

    OAM3AH_HA_GLOBAL_DISABLE = 0x0200,  /* ȫ��ȥʹ�ܱ���   */

    OAM3AH_HA_GLOBALVAR = 0x0300,       /* 3AHȫ�ֱ������� */
    OAM3AH_HA_GLOBALVAR_NEGOUTTIME = 0x0301,  /* �״�Э�̲�ͨ������澯ʱ�� */


}OAM3AH_HA_BAKTYPE_E;

/* �������͸�8λ��ʾ������ */
#define OAM3AH_MAIN_TYPE_MASK   0xff00
/* ��ȡ���������� */
#define OAM3AH_HA_MAINTYPE(ulBakType) \
    ((ulBakType) & OAM3AH_MAIN_TYPE_MASK)

/* ʵʱ���������� */
/* ���и�����ͬ��g_asz3ahRtBakDbgInfo�ַ������� */
typedef enum enOam3ahHaBakCmd
{
    OAM3AH_HA_BAKCFG = 0,               /* ����������Ϣ     */
    OAM3AH_HA_BAKGDISABLE,              /* ����ȫ��ȥʹ��   */
    OAM3AH_HA_BAKGVAR,                   /* ����ȫ�ֱ��� */
}OAM3AH_HA_BAKCMD_E;

/* HA������Ϣ����� */
#define OAM3AH_DBG_OUTPUT(szInfo) TCPIP_DebugOutput(szInfo)

/* ����OAM3AH HA�ڲ�ģ�鱨��ͷ */
#define SET_OAM3AH_HA_HEAD(pst3ahBakHdr, ulBakType, ulBakLen)\
{\
    (pst3ahBakHdr)->usBakType = (USHORT)(ulBakType);\
    (pst3ahBakHdr)->usBakLen  = (USHORT)(ulBakLen);\
}

extern OAM3AH_HASTAT_S g_stOam3ahHaStat;

/* HA������Ϣ����� */
#define OAM3AH_HA_DBG_OUTPUT(szInfo) (VOID)TCPIP_IC_SendMsg(0, 0, szInfo)

/* ����·������Ϣ��ӡ���ڴ��� */
#define OAM3AH_SPRINTF_HA_LINKEVT(pst3ahBakEvt, szDbgStr, iDbgLen)\
{\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P2("\r\n%20s: %lu", "- Link Evt Type", (pst3ahBakEvt)->ulEventType));\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P2("\r\n%20s: %lu", "Link Evt Enable", (pst3ahBakEvt)->ulEventEnable));\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P2("\r\n%20s: %lu(decisecond)", "Link Evt Window", (pst3ahBakEvt)->ulEventWindow));\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P2("\r\n%20s: %lu", "Link Evt Thresh", (pst3ahBakEvt)->ulEventThresh));\
}

/* ����·������Ϣ��ӡ���ڴ��� */
#define OAM3AH_SPRINTF_HA_LINKEVT_EX(pst3ahBakEvt, szDbgStr, iDbgLen)\
{\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P2("\r\n%20s: %lu", "- Link Evt Type", (pst3ahBakEvt)->ulEventType));\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P2("\r\n%20s: %lu", "Link Evt Enable", (pst3ahBakEvt)->ulEventEnable));\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P3("\r\n%20s: %lu %lu(decisecond)", "Link Evt Window", (pst3ahBakEvt)->stdulEventWindow.ulDulHi, (pst3ahBakEvt)->stdulEventWindow.ulDulLo));\
    iDbgLen += TCPIP_SNPRINTF(szDbgStr + iDbgLen, LEN_1024 - iDbgLen, P3("\r\n%20s: %lu %lu", "Link Evt Thresh", (pst3ahBakEvt)->stdulEventThresh.ulDulHi, (pst3ahBakEvt)->stdulEventThresh.ulDulLo));\
}

#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _3AH_HA_H_    */

