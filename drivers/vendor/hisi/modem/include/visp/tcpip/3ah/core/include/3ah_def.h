/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              3ah_def.h
*
*  Project Code: VISPV100R007
*   Module Name: ETH OAM 3AH 
*  Date Created: 2008-2-28
*        Author: LY(57500)
*   Description: 3AHģ��ĺ��ö��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-2-28  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _3AH_DEF_H_
#define _3AH_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif

#ifndef MACADDRLEN
#define MACADDRLEN       6       /*physical��ַ����*/
#endif

#define VLANTYPE_DOT1Q   0x8100  /* VLAN 802.1q��ʽ*/
#define DOT1Q_TAG_SIZE   4


#define OAM3AH_LINKEVENT_NUM        4       /* 3ah֧�ֵ���·�¼�����    */

#define SLOW_PROTOCOL_SUBTYPE_OAM   0x03    /* ��Э��OAM������          */

#define OAMPDU_HEADER_LEN           18      /* OAMPDU ͷ����(����TLV)   */

#define OAMPDU_OUI_LENGTH           3       /* OUI Length               */

#define OAMPDU_VERSION              0x01    /* OAM Version              */

#define OAMPDU_MAX_TX_COUNT         10      /* max number of OAMPDUs send per period */

/* min frame size of OAMPDU,exclude FCS */
#define OAMPDU_MIN_FRAME_SIZE       60

/* frame size of OAMPDU,inlude FCS      */
#define OAMPDU_MAX_PDUSIZE          1518    /* max size     */
#define OAMPDU_MIN_PDUSIZE          64      /* min size     */
#define OAMPDU_DEFAULT_PDUSIZE      128     /* default size */

/* for errored frame seconds summary, timer interval always 1s */
#define OAM3AH_FRMSECSUM_INTERVAL   1000

/* OAM configuration field default:
   OAM MODE: Active mode (1)   
   Unidirectional Support: YES (1) -- Ϊ֧��PTN
   OAM Remote Loopback Support:Yes (1)
   Link Events:Support (1)
   Variable Retrieval:No (0)  
*/
#define OAM3AH_DEFAULT_OAM_CONFIG 0x0F /* binary: 0000 1111 */

/* info revision is start at zero,so the default value of remote info revision must different from zero */
#define OAM3AH_DEFAULT_REMOTE_INFO_REVISION     0x5555

/* the default window,in terms of 100ms */
#define OAM3AH_DEFAULT_ERR_SYMPRD_WINDOW            10
/* ������������¼�����ֵ����ģʽΪ������ģʽʱ��Ĭ��ֵ.Э��涨Ĭ��ֵΪ1s�������ܹ����յķ�������
   ��ƷҲ�������������ζ����,�������ｫ�������Ϊ�ֽ���.
   ��Ĭ��ֵ�ǰ���100M Bit/s������ģ���(100*1024*1024)/8=13107200��*/
#define OAM3AH_DEFAULT_ERR_SYMPRD_WINDOW_SYMMODE    13107200
#define OAM3AH_DEFAULT_ERR_FRAME_WINDOW             10
#define OAM3AH_DEFAULT_ERR_FRMPRD_WINDOW            10

#define OAM3AH_DEFAULT_ERR_FRMPRD_WINDOW_NUMMODE    204800
#define OAM3AH_DEFAULT_ERR_FRMSECSUM_WINDOW         600

/* the default threshold,four link event is same  */
#define OAM3AH_DEFAULT_ERR_THRESHOLD            1

/* default send times of link event oampdu  */
#define OAM3AH_LINK_EVENT_SEND_TIMES            3

/* for reset fsm */
#define OAM3AH_FALSE                        0
#define OAM3AH_TRUE                         1

/* define link event enable & disable */
#define OAM3AH_LINK_EVENT_DISABLE               0
#define OAM3AH_LINK_EVENT_ENABLE                1

/*define  min & max OAMPDU size*/
#define OAM3AH_MIN_PDUSIZE                  64
#define OAM3AH_MAX_PDUSIZE                  1518

/* define min & max lb test pkt size */
#define OAM3AH_MIN_LBTESTPKT_SIZE           48
#define OAM3AH_MAX_LBTESTPKT_SIZE           1500

/* debug level mask */
#define OAM3AH_DBG_OAMPDU_MASK              0x01    /* ���ĵ�������         */
#define OAM3AH_DBG_FSMTRANS_MASK            0x02    /* ״̬��Ǩ�Ƶ�������   */
#define OAM3AH_DBG_LBDATA_MASK              0x04    /* ���ز������ݵ������� */
#define OAM3AH_DBG_ERR_MASK                 0x08    /* ��������������     */

#define OAM3AH_DBG_ALL                      0x0F    /* ���е��Կ��� */

/* detect interval(ms) & code define    */
#define OAM3AH_DETECT_INTERVAL_3                3
#define OAM3AH_DETECT_INTERVAL_10               10
#define OAM3AH_DETECT_INTERVAL_20               20
#define OAM3AH_DETECT_INTERVAL_50               50
#define OAM3AH_DETECT_INTERVAL_100              100
#define OAM3AH_DETECT_INTERVAL_200              200
#define OAM3AH_DETECT_INTERVAL_500              500
#define OAM3AH_DETECT_INTERVAL_1000             1000

/* Ĭ��̽������ */
#define OMA3AH_DEFAULT_DETECT_INTERVAL          OAM3AH_DETECT_INTERVAL_1000

/* ��·��ʱʱ����̽��ʱ����屶 */
#define OAM3AH_LOSTTIME_MULTI                   5

/* Ĭ����·��ʱ���� */
#define OAM3AH_DEFAULT_LOST_TIME                (OAM3AH_DETECT_INTERVAL_1000 * OAM3AH_LOSTTIME_MULTI)

/* lb ctrl lost time */
#define OAM3AH_LB_TIMEOUT_INTERVAL_2000         2000

/*���ر����ط��Ĵ���*/
#define OAM3AH_LB_CMD_RETRY_TIMES                3

/* code interval code(������oam pdu ��info tlv����� configuration�ֶ��е�3λ�����ֶ�) */
#define OAM3AH_DETECT_CODE_1000                 0x0 /* ��λ��ʾ: 000, ��׼̽����  */
#define OAM3AH_DETECT_CODE_3                    0x3 /* ��λ��ʾ: 011, ��չ̽����;������ͨ */
#define OAM3AH_DETECT_CODE_10                   0x1 /* ��λ��ʾ: 001, ��չ̽����;������ͨ */
#define OAM3AH_DETECT_CODE_20                   0x2 /* ��λ��ʾ: 010, ��չ̽����  */
#define OAM3AH_DETECT_CODE_50                   0x4 /* ��λ��ʾ: 100, ��չ̽����  */
#define OAM3AH_DETECT_CODE_100                  0x5 /* ��λ��ʾ: 101, ��չ̽����  */
#define OAM3AH_DETECT_CODE_200                  0x6 /* ��λ��ʾ: 110, ��չ̽����  */
#define OAM3AH_DETECT_CODE_500                  0x7 /* ��λ��ʾ: 111, ��չ̽����  */

/* local stable & local evaluating two-bit encoding     */
/* remote stable & remote evaluating two-bit encoding   */
enum
{
    OAM3AH_DSCVR_STATUS_UNSATISFIED,    /* Unsatisfied,Discovery can not completed  */
    OAM3AH_DSCVR_STATUS_NOT_COMPLETED,  /* Discovery process has not completed      */
    OAM3AH_DSCVR_STATUS_SATISFIED,      /* Discovery process has completed          */
    OAM3AH_DSCVR_STATUS_RESERVED,       /* Reserved                                 */
};

/* parse field action define */
typedef enum
{
    PARSER_FORWARD = 0,  /* 00 = Device is forwarding non-OAMPDUs to higher sublayser        */
    PARSER_LB,           /* 01 = Device is looping back non-OAMPDUs to the lower sublayer    */
    PARSER_DISCARD,      /* 10 = Device is discarding non-OAMPDUs                            */
    PARSER_RESERVED,     /* 11 = Reserved. This value shall not be sent.If the value 11 is 
                            received,it should be ignored and not change the last received value. */
}OAM3AH_PARSER_ACTION_E;

/* multiplexer field action define */
typedef enum
{
    MULTIPLEXER_FORWARD = 0,            /* 0 = Device is forwarding non-OAMPDU */
    MULTIPLEXER_DISCARD = 1             /* 1 = Device is discarding non-OAMPDU */
}OAM3AH_MULTIPLEXER_ACTION_E;

/* loopback control code in loopback OAMPDU */
enum
{
    OAM3AH_ENABLE_REMOTE_LB = 1,    /* enable LB CMD    */
    OAM3AH_DISABLE_REMOTE_LB = 2,   /* disable LB CMD   */
    OAM3AH_REMOTE_LB_CMD_RESERVED
};

/* LOCAL & REMOTE discovery status */
enum 
{
    OAM3AH_LOCAL_DISCOVERY_COMPLETED = 1,   /* local has completed discovery    */
    OAM3AH_REMOTE_DISCOVERY_COMPLETED,      /* remote has completed discovery   */
};

/* OAMPDU CODE define */
typedef enum
{
    OAM3AH_CODE_INFORMATION = 0,
    OAM3AH_CODE_EVENT_NOTIFICATIOIN,
    OAM3AH_CODE_VAR_REQUEST,
    OAM3AH_CODE_VAR_RESPONSE,
    OAM3AH_CODE_LOOPBACK_CONTROL,
    OAM3AH_CODE_DUPLICATE_EVENT_NOTIFICATION,
    OAM3AH_CODE_UNSOPPORTED,
    
    OAM3AH_CODE_ORG_SPECIFIC = 0xfe,

    OAM3AH_CODE_RESERVED
}OAM3AH_OAMDPU_CODE_E;

/* oampdu code for statistic */
enum
{
    OAM3AH_INFO_OAMPDU = 1,
    OAM3AH_EVENT_OAMPDU,
    OAM3AH_LBCTL_OAMPDU,
    OAM3AH_DROP_OAMPDU,
    OAM3AH_FAULT_OAMPDU,
};

/* OAM3AH information tlv type define */
typedef enum
{
    OAM3AH_END_OF_INFO_TLV = 0,
    OAM3AH_LOCAL_INFORMATION,
    OAM3AH_REMOTE_INFORMATION,

    OAM3AH_ORG_SPEC_INFORMATION = 0xfe,
    OAM3AH_RESERVED_INFORMATION,
}OAM3AH_INFORMATION_TYPE_E;

/* max info tlv in send oampdu  */
#define OAM3AH_INFO_TLV_NUM     3

/* �¼�����ö�ٶ���         */
typedef enum enLinkEventType
{
    OAM3AH_END_OF_EVENT_TLV = 0,
    OAM3AH_ERR_SYMPRD_EVENT = 1,    /* ������������¼� */
    OAM3AH_ERR_FRAME_EVENT,         /* ��֡�¼�         */
    OAM3AH_ERR_FRMPRD_EVENT,        /* ��֡�����¼�     */
    OAM3AH_ERR_FRMSECSUM_EVENT,     /* ��֡���¼�       */

    OAM3AH_ORG_SPEC_EVENT = 0xfe,    /* ��֯�Զ����¼�,��ǰ��֧�ַ��ͺͽ��� */
    OAM3AH_RESERVED_EVENT,          /* �����¼�         */   
}OAM3AH_LINKEVENT_TYPE_E;

/* ��������ö�ٶ���         */
typedef enum enFaultType
{
    OAM3AH_FAULT_LINKFAULT,         /* ��·����         */
    OAM3AH_FAULT_DYINGGASP,         /* ��������         */
    OAM3AH_FAULT_CRITICALEVT,       /* �����¼�         */
}OAM3AH_FAULT_TYPE_E;

   
/* define state field bit flags */
#define OAM3AH_STATE_MAIN_FIELD     0xff00
#define OAM3AH_STATE_SUB_FIELD      0x00ff

/* ״̬����״̬ö��,*/
/* ���״̬��״̬����ɾҪͬ��g_sz3ahFsmIdle,g_asz3ahFsmDscvr,g_asz3ahFsmLb�ַ���������� */
typedef enum
{
    OAM3AH_STATE_IDLE,              /* ����״̬,δʹ��3ah   */
    OAM3AH_STATE_DISCOVERY = 0x100, /* ����״̬             */
    OAM3AH_STATE_LOOPBACK = 0x200,  /* ����״̬             */
}OAM3AH_STATE_E;

/* ����״̬ö�ٶ��� */
/* ���״̬��״̬����ɾҪͬ��g_sz3ahFsmIdle,g_asz3ahFsmDscvr,g_asz3ahFsmLb�ַ���������� */
typedef enum
{
    OAM3AH_DSCVR_NONE = OAM3AH_STATE_DISCOVERY,
        
    OAM3AH_DSCVR_FAULT,
    OAM3AH_DSCVR_PASSIVE_WAIT,
    OAM3AH_DSCVR_ACTIVE_SEND_LOCAL,
    OAM3AH_DSCVR_SEND_LOCAL_REMOTE,
    OAM3AH_DSCVR_SEND_LOCAL_REMOTE_OK,
    OAM3AH_DSCVR_SEND_ANY,  
    
    OAM3AH_DSCVR_UNKNOWN,
}OAM3AH_DISCOVERY_E;

/* ����״̬ö�ٶ��� */
/* ���״̬��״̬����ɾҪͬ��g_sz3ahFsmIdle,g_asz3ahFsmDscvr,g_asz3ahFsmLb�ַ���������� */
typedef enum
{
    OAM3AH_LB_IDLE = OAM3AH_STATE_LOOPBACK,
        
    OAM3AH_LB_NO,           /* no loopback in progress                  */
    OAM3AH_LB_INITIATING,   /* start loopback process with it's perr    */
    OAM3AH_LB_REMOTE,       /* in loopback mode with it's peer          */
    OAM3AH_LB_TERMINATING,  /* start terminating loopback               */
    OAM3AH_LB_LOCAL,        /* in loopback mode(remote controlled)      */
    OAM3AH_LB_UNKNOWN,      /* unknown state                            */
}OAM3AH_LBPK_STATE_E;

/* Ϊ֧��״̬����Ǩ���������ض������º� */
typedef enum
{
    OAM3AH_INVALID = 0, /* �Ƿ�״̬                 */
    OAM3AH_DISCOVERING, /* ��OAM3AH_STATE_IDLE״̬��С��OAM3AH_DSCVR_SEND_ANY��DSCVR״̬ */
    OAM3AH_SENDANY,     /* OAM3AH_DSCVR_SEND_ANY    */
    OAM3AH_LBREMOTE,    /* OAM3AH_LB_REMOTE         */
    OAM3AH_LBLOCAL,     /* OAM3AH_LB_LOCAL          */
    OAM3AH_LBING,       /* ��OAM3AH_LB_REMOTE/OAM3AH_LB_LOCAL��Ļ��ش����м�״̬ */
}OAM3AH_FP_STATE_E;

/* main state */
#define OAM3AH_MAIN_STATE(pstPorInfo) \
    ((pstPorInfo)->ulFsmState & OAM3AH_STATE_MAIN_FIELD)

/* judge discovery is completed or not */
#define OAM3AH_DISCOVERY_COMPLETED(pstPorInfo) \
    ((pstPorInfo)->ulFsmState >= OAM3AH_DSCVR_SEND_ANY)

/* judge discovery process status */
#define OAM3AH_DISCOVERY_PROCESS_STATUS(pstPorInfo) \
    ((pstPorInfo)->usDscvrProcessStatue)
    
/* local discover status */
#define OAM3AH_LOCAL_DSCVR_STATUS(pstPorInfo) \
    ((pstPorInfo)->unFlags.s.uslclDscvrStatus)

/* remote discover status */
#define OAM3AH_REMOTE_DSCVR_STATUS(pstPortInfo) \
    ((pstPortInfo)->unFlags.s.usRmtDscvrStatus)

/* remote revision */
#define OAM3AH_REMOTE_INFO_REVISION(pstPorInfo) \
    ((pstPorInfo)->stRmtInfoTlv.usRevision)
    
/* local info revision */
#define OAM3AH_LOCAL_INFO_REVISION(pstPortInfo) \
    ((pstPortInfo)->stLclInfoTlv.usRevision)

/* local oamconfig */
#define OAM3AH_LOCAL_OAMCONFIG(pstPortInfo) \
    ((pstPortInfo)->stLclInfoTlv.unOamCfg.ucConfig)

/* remote oamconfig */
#define OAM3AH_REMOTE_OAMCONFIG(pstPortInfo) \
    ((pstPortInfo)->stRmtInfoTlv.unOamCfg.ucConfig)

/* local oampdu cfg */
#define OAM3AH_LOCAL_MAXOAMPDUSIZE(pstPortInfo) \
    ((pstPortInfo)->stLclInfoTlv.usOamPduCfg)
    
/* remote oampdu cfg */
#define OAM3AH_REMOTE_MAXOAMPDUSIZE(pstPortInfo) \
    (VOS_NTOHS((pstPortInfo)->stRmtInfoTlv.usOamPduCfg))

/* remote state valid */
#define OAM3AH_REMOTE_STATE_VALID(pstPortInfo) \
    ( OAM3AH_DSCVR_STATUS_NOT_COMPLETED != (pstPortInfo)->unFlags.s.uslclDscvrStatus)

/* local detect interval */
#define OAM3AH_LOCAL_DETECTINTERVAL(pstPortInfo) \
    ((pstPortInfo)->stLclInfoTlv.unOamCfg.s.ucDetectInterval)

/* remote detect interval */
#define OAM3AH_REMOTE_DETECTINTERVAL(pstPortInfo) \
    ((pstPortInfo)->stRmtInfoTlv.unOamCfg.s.ucDetectInterval)

/* lcl board state */
#define OAM3AH_BOARDSTATE(pstPortInfo) \
    ((pstPortInfo)->stOrgSpecInfo.ulLclBoardState)

/* 0xec: 11101100 */
/* we just care about bit 7 6 5 3 2 in OAM Configuration field of Info TLV */
/* bit 7~5: Detect Interval */
/* bit 4: Variable Retrieval */
/* bit 3: Link Event Support */
/* bit 2: OAM LoopBack Support */
/* bit 1: Unidirectional Support */
/* bit 0: OAM mode */
#define OAM3AH_LOCAL_SATISFIED(pstPortInfo) \
    (((pstPortInfo)->stLclInfoTlv.unOamCfg.ucConfig & 0xe0) \
     == ((pstPortInfo)->stRmtInfoTlv.unOamCfg.ucConfig & 0xe0))

/* �����Ƿ��Ǳ���ģʽ���жϺ� */
#define OAM3AH_BOTH_PASSIVE_MODE(pstPortInfo) \
((OAM3AH_PASSIVE_MODE == ((pstPortInfo)->stLclInfoTlv.unOamCfg.ucConfig & 0x1)) \
  && (OAM3AH_PASSIVE_MODE == ((pstPortInfo)->stRmtInfoTlv.unOamCfg.ucConfig & 0x1)))
     
/* fault bit in oampdu flag field */
#define OAM3AH_PDU_FLAG_LINKFAULT(pstPortInfo)\
    ((pstPortInfo)->unFlags.s.usLinkFalut)
#define OAM3AH_PDU_FLAG_DYINGGASP(pstPortInfo)\
    ((pstPortInfo)->unFlags.s.usDyingGasp)
#define OAM3AH_PDU_FLAG_CRITICALEVENT(pstPortInfo)\
    ((pstPortInfo)->unFlags.s.usCriticalEvent)

/* get Local Multiplexer and Parser Action */
#define OAM3AH_LOCAL_MUX_ACTION(pstPortInfo)\
    ((pstPortInfo)->stLclInfoTlv.unState.s.ucMuxAction)
#define OAM3AH_LOCAL_PAR_ACTION(pstPortInfo)\
        ((pstPortInfo)->stLclInfoTlv.unState.s.ucParserAction)
        
/* get Remote Multiplexer and Parser Action */
#define OAM3AH_REMOTE_MUX_ACTION(pstPortInfo)\
    ((pstPortInfo)->stRmtInfoTlv.unState.s.ucMuxAction)
#define OAM3AH_REMOTE_PAR_ACTION(pstPortInfo)\
        ((pstPortInfo)->stRmtInfoTlv.unState.s.ucParserAction)
        
/* Errored type */
#define OAM3AH_EVENT_TYPE(pstErrEvent)\
    ((pstErrEvent)->stLinkEventInfo.ulEventType)
    
/* Errored Window */
#define OAM3AH_EVENT_WINDOW(pstErrEvent) \
    ((pstErrEvent)->stLinkEventInfo.stDulErrWindows.ulDulLo)
    
/* Errored Threshold */
#define OAM3AH_EVENT_THRESHOLDHI(pstErrEvent) \
    ((pstErrEvent)->stLinkEventInfo.stDulErrThreshold.ulDulHi)

#define OAM3AH_EVENT_THRESHOLDLo(pstErrEvent) \
    ((pstErrEvent)->stLinkEventInfo.stDulErrThreshold.ulDulLo)

/* Errored Event Running Total */
#define OAM3AH_EVENT_TOTAL(pstErrEvent) \
    ((pstErrEvent)->stLinkEventInfo.ulEventRunTotal)

/* Errored Event time stamp */
#define OAM3AH_EVENT_TIMESTAMP(pstErrEvent) \
    ((pstErrEvent)->stLinkEventInfo.ulEventStamp)

/* local OAM mode */
#define OAM3AH_LOCAL_OAMMODE(pstPortInfo) \
    ((pstPortInfo)->stLclInfoTlv.unOamCfg.s.ucOamMode)

/* remote OAM mode */
#define OAM3AH_REMOTE_OAMMODE(pstPortInfo) \
    ((pstPortInfo)->stRmtInfoTlv.unOamCfg.s.ucOamMode)

/* Is 3ah enabled */
#define OAM3AH_IS_ENABLED(pstPortInfo) ( OAM3AH_ENABLE == (pstPortInfo)->ul3ahEnable)

/* Is 3ah disabled*/
#define OAM3AH_IS_DISABLED(pstPortInfo) ( OAM3AH_DISABLE == (pstPortInfo)->ul3ahEnable)

/* Is 3ah virtual enabled */
#define OAM3AH_IS_VIRTUAL_ENABLED(pstPortInfo) ( OAM3AH_VIRTUAL_ENABLE == (pstPortInfo)->ul3ahEnable)


/* ����ʹ��/״̬��¼λ�ĺ궨��*/
#define OAM3AH_FAULT_LINKFAULT_BIT          0x01    /* ��·�¼� */
#define OAM3AH_FAULT_DYINGGASP_BIT          0x02    /* �������� */
#define OAM3AH_FAULT_CRITICALEVT_BIT        0x04    /* �����¼� */

/* ����λ���� */
#define OAM3AH_FLAGS_CRITICAL_EVENTS        0x07

/* λ����/���/�Ƿ������жϺ� */
#define OAM3AH_FLAG_SET(t,f)    ((t) |= (f))
#define OAM3AH_FLAG_CLR(t,f)    ((t) &= ~(f))
#define OAM3AH_FLAG_ISSET(t,f)  (((t) & (f)) ? 1 : 0)

/* ���ù���ʹ��ֵ�� */
#define OAM3AH_SET_FAULT_ENABLE(pstPortInfo, ulFaultMask, ulEnableValue) \
{\
    /* ʹ�� */\
    if (ulEnableValue)\
    {\
        OAM3AH_FLAG_SET((pstPortInfo)->ulFaultEnable, (ulFaultMask));\
    }\
    /* ȥʹ�� */\
    else\
    {\
        OAM3AH_FLAG_CLR((pstPortInfo)->ulFaultEnable, (ulFaultMask));\
    }\
}

/* 3AHģ�鶨ʱ���ص�����ָ�� */
typedef VOID (*OAM3AH_TIMER_FUNC)(ULONG ulIfIndex);

/* 3AHģ�����ݽṹSID����:ģ����Ψһ */
#define  SID_COMP_OAM3AH_PORTINFO_S         0x01
#define  SID_COMP_OAM3AH_DLL_S              0x02
#define  SID_COMP_OAM3AH_LINKEVT_S          0x03

/* 3AHģ��澯�� */
#define OAM_3AH_WARNINGOUT(pstWarnParam) TCPIP_WarningOut(WARNING_3AH, (pstWarnParam))

/* �¼���ʶ�ڶ���8λ��ʾ��Ҫ�¼����� */
#define OAM3AH_EVENT_MAIN_FIELD             0xff00

/* ״̬�����������¼����� */
/* ����¼���������ɾҪͬ��g_asz3ahEvtCtrl�ַ���������� */
typedef enum
{
    OAM3AH_EVT_CTRL_IDLE = 0x0000,

    OAM3AH_EVT_DISABLE,
    OAM3AH_EVT_ENABLE,

    OAM3AH_EVT_CFG_MUX_FWD,
    OAM3AH_EVT_CFG_MUX_DISCARD,
    OAM3AH_EVT_CFG_ENABLE_REMOTE_LB,
    OAM3AH_EVT_CFG_DISABLE_REMOTE_LB,

    OAM3AH_EVT_LOCAL_LOST_LINK,
    OAM3AH_EVT_LOCAL_LINK_FAULT,
    OAM3AH_EVT_LOCAL_LINK_OK,
    OAM3AH_EVT_LOCAL_DYING_GASP,
    OAM3AH_EVT_LOCAL_CRITICAL_EVENT,

    OAM3AH_EVT_LCL_UNSATISFIED,
    OAM3AH_EVT_LCL_SATISFIED,

    OAM3AH_EVT_LCL_HA,  /* ר������HA���ݵ���ʹ�� */

    OAM3AH_EVT_RCV_INFO = 0x100,
    OAM3AH_EVT_LPBK_CMD = 0x200,
}OAM3AH_CTRL_EVENTS_E;

/* ״̬�������Զ��¼����� */
/* ����¼���������ɾҪͬ��g_asz3ahEvtRmt�ַ���������� */
typedef enum
{
    OAM3AH_EVT_RCV_INFO_NONE = OAM3AH_EVT_RCV_INFO,
    OAM3AH_EVT_RMT_LINK_FAULT,
    OAM3AH_EVT_RMT_DYING_GASP,
    OAM3AH_EVT_RMT_CRITICAL_EVENT,
    
    OAM3AH_EVT_RMT_STATEINFO_CHANGED,
    OAM3AH_EVT_RMT_UNSATISFIED,
    OAM3AH_EVT_RMT_NOT_COMPLETED,
    OAM3AH_EVT_RMT_CHGDETECT,               /* ���ֶԶ�ȥ�ı�̽�����ڲ�ȥ����ͳ����Ϣ */
    OAM3AH_EVT_RMT_SATISFIED,
}OAM3AH_EVT_RMT_INFO_E;

/* ״̬���������ؿ����¼����� */
/* ����¼���������ɾҪͬ��g_asz3ahEvtLb�ַ���������� */
enum
{
    OAM3AH_EVT_LPBK_CMD_RSV = OAM3AH_EVT_LPBK_CMD,
    OAM3AH_EVT_ENABLE_REMOTE_LB,
    OAM3AH_EVT_DISABLE_REMOTE_LB,

    OAM3AH_EVT_LB_TIMEOUT
};

/* ���ķ��ͽ��ձ�־ */
#define OAM3AH_PKT_SND      0
#define OAM3AH_PKT_RCV      1

/* NP MODE */
#define OAM3AH_NP_VISP      0   /* VISP���ģʽ */
#define OAM3AH_NP_HALF      1   /* ��NPģʽ     */
#define OAM3AH_NP_FULL      2   /* ȫNPģʽ     */

/* Organization Specific Information Tlv ���������ð屸�ð�ֵ�궨�� */
#define OAM3AH_ORG_BOARDSTATE_MASTE 0xAB
#define OAM3AH_ORG_BOARDSTATE_SLAVE 0xBA

/* get board state from org spec tlv value */
/* 0 ------- OAM3AH_BOARD_STATE_NULL   (0)  (�Զ���ͨ��)
   0xAB ---- OAM3AH_BOARD_STATE_MASTER (1)  (�Զ�ͨ��������Ϣ)
   0xBA ---- OAM3AH_BOARD_STATE_SLAVE  (2)  (�Զ�ͨ�汸����Ϣ)  
*/
#define OAM3AH_GET_BOARDSTATE(ulType) \
    (0 == (ulType)) ? OAM3AH_BOARD_STATE_NULL : \
    ((OAM3AH_ORG_BOARDSTATE_MASTE == (ulType)) ? OAM3AH_BOARD_STATE_MASTER : OAM3AH_BOARD_STATE_SLAVE)

/* get board type(org spec value) from board state */
/* OAM3AH_BOARD_STATE_NULL   (0) ----- 0    (����Զ�ͨ��)
   OAM3AH_BOARD_STATE_MASTER (1) ----- 0xAB (��Զ�ͨ��������Ϣ)
   OAM3AH_BOARD_STATE_SLAVE  (2) ----- 0xBA (��Զ�ͨ�汸����Ϣ)  
*/
#define OAM3AH_GET_BOARDTYPE(ulState) \
    (OAM3AH_BOARD_STATE_NULL == (ulState)) ? 0 : \
    ((OAM3AH_BOARD_STATE_MASTER == (ulState)) ? OAM3AH_ORG_BOARDSTATE_MASTE : OAM3AH_ORG_BOARDSTATE_SLAVE)


/* check oui validity,0-invalid; 1-valid */
#define OAM3AH_CHECK_OUI(aucOUI,ulOuiCheckRet) \
{\
    LONG lCmpRet1 = 1;\
    LONG lCmpRet2 = 1;\
    (VOID)VOS_Mem_Cmp((VOID*)(aucOUI), (VOID*)g_aucHuaweiOui[0], OAMPDU_OUI_LENGTH, &lCmpRet1);\
    (VOID)VOS_Mem_Cmp((VOID*)(aucOUI), (VOID*)g_aucHuaweiOui[1], OAMPDU_OUI_LENGTH, &lCmpRet2);\
    ulOuiCheckRet = !((lCmpRet1 != 0) && (lCmpRet2 != 0));\
}

#define OAM3AH_Timer_Resize(ulTimerId,ulNewTime)\
{\
    if(ulTimerId)\
    {\
        (VOID)VOS_Timer_Resize((ulTimerId),(ulNewTime));\
    }\
}

#define OAM3AH_Timer_Resume(ulTimerId)\
{\
    if(ulTimerId)\
    {\
        if (!OAM_3AH_Timer_IsStoped(ulTimerId))\
        {\
            /* ������PauseȻ����Resume�����������¿�ʼ��ʱ! */\
            (VOID)VOS_Timer_Pause (ulTimerId);\
        }\
        (VOID)VOS_Timer_Resume(ulTimerId);\
    }\
}

#define OAM3AH_Timer_Pause(ulTimerId)\
{\
    if(ulTimerId && (!OAM_3AH_Timer_IsStoped(ulTimerId)))\
    {\
        (VOID)VOS_Timer_Pause(ulTimerId);\
    }\
}
    
/* ��̽��׶�(SEND_ANY)�˻ص����ֽ׶�ʱ�Ķ�ʱ������� */
#define OAM3AH_BACK_TO_DSCVR_TIMER_DEAL(pstPortInfo) \
{\
    if (OAM3AH_NP_VISP == g_stOam3ahModInfo.ulNpMode)/* NPΪ���ģʽ */\
    {\
        /* ���ֽ׶��Ա�׼����̽�� */\
        OAM3AH_Timer_Resize((pstPortInfo)->ulPduTimerId, g_ulDefaultDetectIntervar);\
        OAM3AH_Timer_Resize((pstPortInfo)->ulLostLinkTimerId, g_ulDefaultlostLinkTime);\
    }\
    else if (OAM3AH_NP_FULL== g_stOam3ahModInfo.ulNpMode)/* ȫNP */\
    {\
        /* ������·��ʱ��ʱ�� */\
        /* OAM3AH_Timer_Resume((pstPortInfo)->ulPduTimerId);*/\
        /* ���״̬���˻�ΪFAULT/PASSIVE_WAIT/SEND_LOCAL������·��ʱ��ʱ��Ӧ����ֹͣ״̬ */\
        if ((pstPortInfo)->ulFsmState > OAM3AH_DSCVR_ACTIVE_SEND_LOCAL)\
        {\
            OAM3AH_Timer_Resume((pstPortInfo)->ulLostLinkTimerId);\
        }\
    }\
    else /* ��NP */\
    {\
        /*������·��ʱ��ʱ������ֵ */\
        /* OAM3AH_Timer_Resume((pstPortInfo)->ulPduTimerId);*/\
        OAM3AH_Timer_Resize((pstPortInfo)->ulLostLinkTimerId, g_ulDefaultlostLinkTime);\
    }\
}

/* ����û����õ���·�¼�����ֵ�Ƿ�Ϸ� */
#define OAM3AH_WINDOW_10    10 
#define OAM3AH_WINDOW_100   100 
#define OAM3AH_WINDOW_600   600 
#define OAM3AH_WINDOW_9000  9000 
#define OAM3AH_LINKEVT_CHECK_WINDOW(ulLinkEventType,stdulErrWindow,ulCheckWin)\
{\
    ulCheckWin = OAM3AH_OK;\
    if ((OAM3AH_ERR_SYMPRD_EVENT == ulLinkEventType) || (OAM3AH_ERR_FRAME_EVENT == ulLinkEventType))\
    {\
        if ((OAM3AH_ERR_SYMPRD_EVENT == ulLinkEventType) && (1 == g_stOam3ahModInfo.ulErrSymPrdEventSetMode))\
        {\
            /* ������������¼�(������ģʽ)�������õķ�����ֻҪ����0�Ϳ���,ȡֵ��ΧΪ1~ULONG�ɱ�ʾ�����ֵ4294967295,����1 */\
            if (DULONG_S_COMPARE_ULONG(stdulErrWindow, 1) < 0)\
            {\
                ulCheckWin = OAM3AH_ERR_EVENT_WIN;\
            }\
        }\
        else\
        {\
            if ((DULONG_S_COMPARE_ULONG(stdulErrWindow, OAM3AH_WINDOW_10) < 0) || ((DULONG_S_COMPARE_ULONG(stdulErrWindow, OAM3AH_WINDOW_600) > 0) || (0 != (stdulErrWindow.ulDulLo% 10))))\
            {\
                /* ������������¼�(ʱ��ģʽ)/��֡�¼�����ֵ10~600(0.1s��λ),����10(0.1s��λ),��λ���涼һ�� */\
                ulCheckWin = OAM3AH_ERR_EVENT_WIN;\
            }\
        }\
    }\
    else if (OAM3AH_ERR_FRMPRD_EVENT == ulLinkEventType)\
    {\
        /* ��֡�����¼�����ֵ����ģʽΪ0��ʾ���õĴ���ֵΪʱ��ֵ;Ϊ1��ʾ���õĴ���ֵΪ֡��Ŀ */\
        if(0 == g_stOam3ahModInfo.ulErrFrmPrdEventSetMode)\
        {\
            /* ��֡�����¼��������õ�ʱ��ֵΪ1~600,����1 */\
            if ((DULONG_S_COMPARE_ULONG(stdulErrWindow, 1) < 0) || (DULONG_S_COMPARE_ULONG(stdulErrWindow, OAM3AH_WINDOW_600) > 0))\
            {\
                ulCheckWin = OAM3AH_ERR_EVENT_WIN;\
            }\
        }\
        else\
        {\
            /* ��֡�����¼��������õ�֡��ĿֻҪ����0�Ϳ���,ȡֵ��ΧΪ1~ULONG�ɱ�ʾ�����ֵ4294967295,����1 */\
            if (DULONG_S_COMPARE_ULONG(stdulErrWindow, 1) < 0)\
            {\
                ulCheckWin = OAM3AH_ERR_EVENT_WIN;\
            }\
        }\
    }\
    else /* ���ú�ǰǰ���Ѿ����ж�typeֵ,���˴���ΪOAM3AH_ERR_FRMSECSUM_EVENT */\
    {\
        if ((DULONG_S_COMPARE_ULONG(stdulErrWindow, OAM3AH_WINDOW_100) < 0) || (DULONG_S_COMPARE_ULONG(stdulErrWindow, OAM3AH_WINDOW_9000) > 0) || (0 != (stdulErrWindow.ulDulLo % 10)))\
        {\
            ulCheckWin = OAM3AH_ERR_EVENT_WIN;\
        }\
    }\
}

/* ����û����õ���·�¼�����ֵ�Ƿ�Ϸ� */
#define OAM3AH_THRESHOLD_900    900 
#define OAM3AH_LINKEVT_CHECK_THRESHOLD(ulLinkEventType, stdulErrThres, ulCheckThres)\
{\
    ulCheckThres = OAM3AH_OK;\
    if (OAM3AH_ERR_FRMSECSUM_EVENT == ulLinkEventType)\
    {\
        if ((DULONG_S_COMPARE_ULONG(stdulErrThres, 1) < 0) || (DULONG_S_COMPARE_ULONG(stdulErrThres, OAM3AH_THRESHOLD_900) > 0))\
        {\
            ulCheckThres = OAM3AH_ERR_EVENT_THRESH;\
        }\
    }\
    else\
    {\
        /* ������������¼�����֡�¼�����֡�����¼�����ֵ�����ֵ�������ƣ�ȡULONG�ɱ�ʾ�����ֵ4294967295 */\
        if (DULONG_S_COMPARE_ULONG(stdulErrThres, 1) < 0)\
        {\
             ulCheckThres = OAM3AH_ERR_EVENT_THRESH;\
        }\
    }\
}

/* ��֡/��֡���¼��Ƿ�ΪNPʵ�� */
#define OAM3AH_FRAMEEVT_ACT_NP (1 == g_stOam3ahModInfo.ulFrmAct)

/* ���/��ȡ�ֶ���ʹ�õ�һЩ����� */
/* ���ַ�ָ��cp���һ��char��c��cpָ���1 */
#define OAM3AH_GETCHAR(c, cp) { \
    (c) = *(cp); \
    (cp) ++ ; \
}

/* ���ַ�cд���ַ�ָ��cp����cpָ���1 */
#define OAM3AH_PUTCHAR(c, cp) { \
    *(cp) = (UCHAR) (c); \
    (cp) ++ ; \
}

/* ���ַ�ָ��cp���һ��ushortֵ��s��cpָ���2 */
#define OAM3AH_GETSHORT(s, cp) { \
    USHORT usTemp;\
    VOS_CopyVar((usTemp), *((USHORT*)(cp)));\
    (s) = VOS_NTOHS(usTemp);\
    (cp) += sizeof(USHORT) ; \
}

/* ���ַ�ָ��cp���һ��ushortֵ��s,����ָ����ƫ�� */
#define OAM3AH_GETSHORT_NOSHIFT(s, cp) { \
    USHORT usTemp;\
    VOS_CopyVar((usTemp), *((USHORT*)(cp)));\
    (s) = VOS_NTOHS(usTemp);\
}

/* ��ushort����s��ֵд���ַ�ָ��cp����cpָ���2 */
#define OAM3AH_PUTSHORT(s, cp) { \
    USHORT usTemp;\
    (usTemp) = (USHORT)(s);\
    (usTemp) = (USHORT)VOS_HTONS(usTemp);\
    VOS_CopyVar(*(((USHORT*)(cp))), (usTemp));\
    (cp) += sizeof(USHORT) ; \
}

/* ���ַ�ָ��cp���һ��ulongֵ��s��cpָ���4 */
#define OAM3AH_GETLONG(l, cp) { \
    ULONG ulTemp;\
    VOS_CopyVar((ulTemp), *((ULONG*)(cp)));\
    (l) = VOS_NTOHL(ulTemp);\
    (cp) += sizeof(ULONG) ; \
}

/* ���ַ�ָ��cp���һ��ulongֵ��s������ָ����ƫ�� */
#define OAM3AH_GETLONG_NOSHIFT(l, cp) { \
    ULONG ulTemp;\
    VOS_CopyVar((ulTemp), *((ULONG*)(cp)));\
    (l) = VOS_NTOHL(ulTemp);\
}

/* ��ulong����l��ֵд���ַ�ָ��cp����cpָ���4 */
#define OAM3AH_PUTLONG(l, cp) { \
    ULONG ulTemp;\
    (ulTemp) = (l);\
    (ulTemp) = (ULONG)VOS_HTONL(ulTemp);\
    VOS_CopyVar(*(((ULONG*)(cp))), (ulTemp));\
    (cp) += sizeof(ULONG) ; \
} 

/* ���Ĵ���ʱ��ע�ắ�� */
typedef ULONG (*DEALPKT_TIMETEST__HOOK_FUNC) (ULONG ulDealStatus);

/* ���Ĵ���״̬,���ܲ���ʹ�� */
#define OAM3AH_RCV_DEALPKT_BEGIN        0x01
#define OAM3AH_RCV_DEALPKT_END          0x02

/* ��ʱ��״̬��,OAM_3AH_Timer_IsStopedʹ��.
 * ˵��:Ϊ����VISP�����dopra�µ������������Զ��庯�� OAM_3AH_Timer_IsStoped;�ú�����Ҫʹ������������,
 * ����������dopraͷ�ļ�v_relatm.h���ж���,�����������nodeb�汾��������,���ڴ��ظ���������������
 */
#ifndef VOS_TM_IS_PAUSED
#define VOS_TM_IS_PAUSED        0xAE      /*��Զ�ʱ����״̬����ֹ̬        */
#endif
#ifndef VOS_TM_IS_DELETED
#define VOS_TM_IS_DELETED       0x55      /*��Զ�ʱ����״̬�Ǳ�ɾ��̬      */
#endif

#define OAM3AH_MAX_NEG_TIME 600         /* �����״�Э�̲�������澯���ʱ��,��λΪs */
#define OAM3AH_NEGWARNING_TIMEINIT  (ULONG)~0x0  /* 0xFFFFFFFF */
#define OAM3AH_NEGWARNING_TIMEDONE  (ULONG)~0x1  /* 0xFFFFFFFE */

#define OAM3AH_WARN_TRACE_SENDANY_BIT 0x01       /* SENDANY�澯׷�� */
#define OAM3AH_WARN_TRACE_LB_LCL_BIT  0x02       /* ������Ӧ��̬�澯׷�� */
#define OAM3AH_WARN_TRACE_LB_RMT_BIT  0x04       /* ���ط�����̬�澯׷�� */

/* ����ע��ר�ú�-�Ա�����SI��symbol���ڲ鿴����,�ú�������̫��,����Ч������ */
#define NOTE(x)                         1

#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */


#endif      /* end of _3AH_DEF_H_   */

