/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaPublic.c
  Description     : ��C�ļ�ʵ�ֹ����ĺ�������NV��д��USIM��
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaPublic.h"
#include "ImsaEntity.h"
#include "LNvCommon.h"
#include "LPsNvInterface.h"
#include "UsimPsInterface.h"
#include "ImsaNvInterface.h"
#include "SysNvId.h"
#include "NVIM_Interface.h"
#include "ImsaImsInterface.h"
#include "ImsaImsAdaption.h"
#include "NasCommPrint.h"
#include "VcImsaInterface.h"
#include "ImsaCdsInterface.h"
#include "ImsaImsInterface.h"
#include "MsgImsaInterface.h"
#include "ImsaRegManagement.h"
#include "ScInterface.h"
#include "CallImsaInterface.h"
#include "NasNvInterface.h"
#include "LNasNvInterface.h"
#if (FEATURE_ON == FEATURE_PTM)
#include "ImsaProcOmMsg.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_IMSAPUBLIC_C
#define    THIS_NAS_FILE_ID      NAS_FILE_ID_IMSAPUBLIC_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
/*IMSA�������͸�IMS��Ϣ��OPID*/
static VOS_UINT32 gulImsaImsOpId = 0;

/*IMS�������͸�IMSA����ҪIMSA�ظ���Ϣ��OPID*/
static VOS_UINT32 gulImsaRcvImsNormOpId = 0;
static VOS_UINT32 gulImsaRcvImsEmcOpId = 0;

static VOS_UINT8 gucImsaUsimOpId = 0;


#if (FEATURE_ON == FEATURE_DSDS)
/*ͳ���������Ϣ����*/
IMSA_DSDS_MSG_COUNT_STRU  g_astImsaDsdsNotifyMsgNum[IMSA_LRRC_SESSION_TYPE_BUTT];
#endif
#if (FEATURE_ON == FEATURE_PTM)
/* IMSAģ��Error Log�쳣����� */
IMSA_ERR_LOG_ALM_LEVEL_STRU g_astImsaErrAlmLevelTb[] = {
    {IMSA_ERR_LOG_ALM_CALL_FAIL_EVENT,      IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {IMSA_ERR_LOG_ALM_REG_FAIL_EVENT,       IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {IMSA_ERR_LOG_ALM_MNTN,                 IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {IMSA_ERR_LOG_ALM_NORM_NOT_INIT_REG_EVENT,  IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {IMSA_ERR_LOG_ALM_NORM_PDN_CONN_REJ_EVENT,  IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {IMSA_ERR_LOG_ALM_NORM_REG_FAIL_EVENT,      IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {IMSA_ERR_LOG_ALM_NORM_INIT_DEREG_EVENT,    IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {IMSA_ERR_LOG_ALM_NORM_CALL_FAIL_EVENT,     IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {IMSA_ERR_LOG_ALM_EMC_CALL_FAIL_EVENT,      IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL},
    {IMSA_ERR_LOG_ALM_MODIFY_CALL_TYPE_FAIL_EVENT, IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL}
};
#endif

extern VOS_UINT32  IMSA_EncodeIsimFile(const IMSA_ISIM_DATA_STRU *pstIsimData);
extern VOS_UINT32  IMSA_DecodeIsimDomain(const  IMSA_ISIM_DATA_STRU *pstIsimData);
extern VOS_UINT32  IMSA_DecodeIsimImpi(const  IMSA_ISIM_DATA_STRU *pstIsimData);
extern VOS_UINT32  IMSA_DecodeIsimImpu(const  IMSA_ISIM_DATA_STRU *pstIsimData);
/*zhaochen 00308719 begin for card lock 2015-10-31*/
extern VOS_UINT32  IMSA_DecodeSimMncLen(const  IMSA_ISIM_DATA_STRU *pstIsimData);
/*zhaochen 00308719 end for card lock 2015-10-31*/

extern VOS_VOID    IMSA_ReadImsaNvImsRatSupportConfig( VOS_VOID);
extern VOS_VOID    IMSA_ReadImsaNvImsaConfig( VOS_VOID);
extern VOS_VOID    IMSA_ReadImsaNvImsCapability( VOS_VOID);
extern VOS_VOID    IMSA_ReadImsaNvSipPortConfig( VOS_VOID);
extern VOS_VOID     IMSA_ReadImei( VOS_VOID );
extern VOS_VOID     IMSA_ReadNvVoiceDomain(VOS_VOID );
extern VOS_VOID     IMSA_ReadPcscfDiscoveryPolicy(VOS_VOID);

extern VOS_VOID IMSA_ReadNvIpv6FallBackExtCause(VOS_VOID);

extern VOS_VOID  IMSA_ReadImsaNvImsConfig( VOS_VOID);
extern VOS_VOID IMSA_SndD2AuthSyncFailure
(
    const USIMM_IMS_AUTH_CNF_STRU      *pstIMSCnf,
    VOS_UINT32                          ulIsEmergencyAuth
);
extern VOS_VOID IMSA_SndD2AuthNetworkFailure
(
    VOS_UINT32                          ulIsEmergencyAuth
);
extern VOS_VOID IMSA_SndD2AuthSuccRsp
(
    const USIMM_IMS_AUTH_CNF_STRU      *pstIMSCnf,
    VOS_UINT32                          ulIsEmergencyAuth
);

extern VOS_UINT32  IMSA_BcdToAsciiCode
(
    VOS_UINT8                           ucBcdCode,
    VOS_CHAR                            *pcAsciiCode
);
extern VOS_UINT32  IMSA_AsciiToBcdCode
(
    VOS_CHAR                            cAsciiCode,
    VOS_UINT8                           *pucBcdCode
);
extern VOS_INT32   IMSA_PrintImsaIntraMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    IMSA_INTRA_MSG_ID_ENUM_UINT32       enMsgId
);
extern VOS_INT32   IMSA_PrintUsimMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulMsgId
);
extern VOS_INT32   IMSA_PrintVcMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulMsgId
);
extern VOS_INT32   IMSA_PrintCdsMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulMsgId
);
extern VOS_INT32  IMSA_PrintImsaTimer
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulTimerType,
    VOS_UINT32                          ulTimerPara
);
extern VOS_INT32   IMSA_PrintMmaMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulMsgId
);
extern VOS_INT32   IMSA_PrintApsMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    const TAF_PS_EVT_STRU              *pstApsEvt
);
extern VOS_INT32  IMSA_PrintSpmMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
);
extern VOS_INT32  IMSA_PrintAtMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
);
extern VOS_INT32  IMSA_PrintMsgMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
);
extern VOS_INT32  IMSA_PrintCallMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
);
extern VOS_INT32  IMSA_PrintImsMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
);
extern VOS_INT32  IMSA_PrintRcvTafMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
);
extern VOS_INT32  IMSA_PrintSendTafMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
);

extern VOS_INT32   IMSA_PrintMtcMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulMsgId
);

extern IMSA_IMS_NW_ACCESS_TYPE_ENUM_UINT8 IMSA_ConverterAccessType2Ims
(
    MSCC_IMSA_ACCESS_TYPE_ENUM_UINT8     enAccessType
);
extern VOS_VOID IMSA_ConverterCgiParam2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
);
extern VOS_VOID IMSA_ConverterImeiParam2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
);
extern VOS_VOID IMSA_ConverterRetyrTimeParam2Ims
(
    VOS_UINT32                          ulRetryTimerLen,
    VOS_UINT32                          ulPeriodRergisterTimerLen,
    IMSA_IMS_INPUT_EVENT_STRU          *pstImsaImsInputEvt
);
extern VOS_VOID IMSA_ConverterUeCapParam2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
);
extern VOS_VOID IMSA_ConverterNetCapParam2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
);
extern VOS_VOID IMSA_ConverterImsiParam2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
);

IMSA_ISIM_ACT_STRU g_astIsimDataMap[] =
{
    {USIMM_ISIM_EFIMPI_ID,    IMSA_DecodeIsimImpi,     IMSA_EncodeIsimFile},
    {USIMM_ISIM_EFDOMAIN_ID,  IMSA_DecodeIsimDomain,     IMSA_EncodeIsimFile},
    {USIMM_ISIM_EFIMPU_ID,    IMSA_DecodeIsimImpu,     IMSA_EncodeIsimFile},
    /*zhaochen 00308719 begin for card lock 2015-10-31*/
    {USIMM_USIM_EFAD_ID,      IMSA_DecodeSimMncLen,    IMSA_EncodeIsimFile}
    /*zhaochen 00308719 end for card lock 2015-10-31*/

};

VOS_UINT32 g_ulIsimDataMapNum
            = sizeof(g_astIsimDataMap)/sizeof(IMSA_ISIM_ACT_STRU);


VOS_CHAR                                g_acImsaPrintBuf[IMSA_PRINT_BUFF_LEN] = "";

/* IMSA�ڲ���Ϣ��ӡ���� */
NAS_COMM_PRINT_MSG_LIST_STRU g_astImsaIntraMsgIdArray[] =
{
    {   ID_IMSA_REG_REG_REQ                   ,
            "MSG:  ID_IMSA_REG_REG_REQ                               "},
    {   ID_IMSA_REG_DEREG_REQ                   ,
            "MSG:  ID_IMSA_REG_DEREG_REQ                             "},
    {   ID_IMSA_REG_REG_IND                    ,
            "MSG:  ID_IMSA_REG_REG_IND                               "},
    {   ID_IMSA_REG_DEREG_IND                    ,
            "MSG:  ID_IMSA_REG_DEREG_IND                             "},
    {   ID_IMSA_CONN_SETUP_REQ                    ,
            "MSG:  ID_IMSA_CONN_SETUP_REQ                            "},
    {   ID_IMSA_CONN_REL_REQ                ,
            "MSG:  ID_IMSA_CONN_REL_REQ                              "},
    {   ID_IMSA_CONN_SETUP_IND           ,
            "MSG:  ID_IMSA_CONN_SETUP_IND                            "},
    {   ID_IMSA_CONN_REL_IND             ,
            "MSG:  ID_IMSA_CONN_REL_IND                              "},
    {   ID_IMSA_CONN_MODIFY_IND             ,
            "MSG:  ID_IMSA_CONN_MODIFY_IND                           "},
    {   ID_IMSA_NRM_CALL_SRV_STATUS_IND                       ,
            "MSG:  ID_IMSA_NRM_CALL_SRV_STATUS_IND                   "},
    {   ID_IMSA_EMC_CALL_SRV_STATUS_IND                        ,
            "MSG:  ID_IMSA_EMC_CALL_SRV_STATUS_IND                   "},
    {   ID_IMSA_CALL_RESULT_ACTION_IND                        ,
            "MSG:  ID_IMSA_CALL_RESULT_ACTION_IND                    "}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astImsaUsimMsgIdArray[] =
{
    {   USIMM_READFILE_CNF                   ,
            "MSG:  USIMM_READFILE_CNF                              "},
    {   USIMM_AUTHENTICATION_CNF                   ,
            "MSG:  USIMM_AUTHENTICATION_CNF                        "},
    {   USIMM_CARDSTATUS_IND                    ,
            "MSG:  USIMM_CARDSTATUS_IND                            "},
    {   USIMM_STKREFRESH_IND                    ,
            "MSG:  USIMM_STKREFRESH_IND                               "}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astImsaVcMsgIdArray[] =
{
    {   ID_IMSA_VC_START_HIFI_NTF                   ,
            "MSG:  ID_IMSA_VC_START_HIFI_NTF                         "},
    {   ID_IMSA_VC_STOP_HIFI_NTF                   ,
            "MSG:  ID_IMSA_VC_STOP_HIFI_NTF                          "},
    {   ID_IMSA_VC_HIFI_PARA_CHANGED_NTF                   ,
            "MSG:  ID_IMSA_VC_HIFI_PARA_CHANGED_NTF                  "},
    {   ID_VC_IMSA_HIFI_EXCEPTION_NTF                   ,
            "MSG:  ID_VC_IMSA_HIFI_EXCEPTION_NTF                     "}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astImsaCdsMsgIdArray[] =
{
    {   ID_IMSA_CDS_SET_IMS_BEARER_REQ                   ,
            "MSG:  ID_IMSA_CDS_SET_IMS_BEARER_REQ                    "},
    {   ID_IMSA_CDS_SET_IMS_BEARER_CNF                   ,
            "MSG:  ID_IMSA_CDS_SET_IMS_BEARER_CNF                    "}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astImsaTimerArray[] =
{
    {   TI_IMSA_START_OR_STOP,
            "STATE TI:  TI_IMSA_START_OR_STOP                       "},
    {   TI_IMSA_PERIOD_TRY_IMS_SRV     ,
            "STATE TI:  TI_IMSA_PERIOD_TRY_IMS_SRV                  "},
    {   TI_IMSA_PERIOD_TRY_IMS_EMC_SRV     ,
            "STATE TI:  TI_IMSA_PERIOD_TRY_IMS_EMC_SRV                  "},
    {   TI_IMSA_SIP_SIGAL_PDP_ORIG               ,
            "STATE TI:  TI_IMSA_SIP_SIGAL_PDP_ORIG                  "},
    {   TI_IMSA_SIP_SIGAL_PDP_END               ,
            "STATE TI:  TI_IMSA_SIP_SIGAL_PDP_END                   "},
    {   TI_IMSA_WAIT_IPV6_INFO             ,
            "STATE TI:  TI_IMSA_WAIT_IPV6_INFO                      "},
    {   TI_IMSA_REG_PROTECT               ,
            "STATE TI:  TI_IMSA_REG_PROTECT                         "},
    {   TI_IMSA_REG_RETRY               ,
            "STATE TI:  TI_IMSA_REG_RETRY                           "},
    {   TI_IMSA_REG_PERIOD_TRY               ,
            "STATE TI:  TI_IMSA_REG_PERIOD_TRY                      "},
    {   TI_IMSA_CALL_PROTECT,
            "STATE TI:  TI_IMSA_CALL_PROTECT                        "},
    {   TI_IMSA_CALL_RES_READY,
            "STATE TI:  TI_IMSA_CALL_RES_READY                      "},
    {   TI_IMSA_SMS_TR1M,
            "STATE TI:  TI_IMSA_SMS_TR1M                            "} ,
    {   TI_IMSA_SMS_TR2M,
            "STATE TI:  TI_IMSA_SMS_TR2M                            "},
    {   TI_IMSA_BACK_OFF_TX,
            "STATE TI:  TI_IMSA_BACK_OFF_TX                            "},
    {   TI_IMSA_BACK_OFF_TY,
            "STATE TI:  TI_IMSA_BACK_OFF_TY                            "},
    {   TI_IMSA_USSD_WAIT_NET_RSP,
            "STATE TI:  TI_IMSA_USSD_WAIT_NET_RSP                    "},
    {   TI_IMSA_USSD_WAIT_APP_RSP,
            "STATE TI:  TI_IMSA_USSD_WAIT_APP_RSP                    "},
    {   TI_IMSA_CALL_NORMAL_TCALL,
            "STATE TI:  TI_IMSA_CALL_NORMAL_TCALL                    "},
    {   TI_IMSA_CALL_EMC_TCALL,
            "STATE TI:  TI_IMSA_CALL_EMC_TCALL                       "},
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astImsaMsccMsgIdArray[] =
{
    {   ID_MSCC_IMSA_START_REQ,
            "MSG:  ID_MSCC_IMSA_START_REQ                             "},
    {   ID_MSCC_IMSA_STOP_REQ                   ,
            "MSG:  ID_MSCC_IMSA_STOP_REQ                              "},
    {   ID_MSCC_IMSA_DEREG_REQ                    ,
            "MSG:  ID_MSCC_IMSA_DEREG_REQ                             "},
    {   ID_MSCC_IMSA_SERVICE_CHANGE_IND                    ,
            "MSG:  ID_MSCC_IMSA_SERVICE_CHANGE_IND                    "},
    {   ID_MSCC_IMSA_CAMP_INFO_CHANGE_IND                    ,
            "MSG:  ID_MSCC_IMSA_CAMP_INFO_CHANGE_IND                  "},
    {   ID_IMSA_MSCC_START_CNF                    ,
            "MSG:  ID_IMSA_MSCC_START_CNF                             "},
    {   ID_IMSA_MSCC_STOP_CNF                    ,
            "MSG:  ID_IMSA_MSCC_STOP_CNF                              "},
    {   ID_IMSA_MSCC_DEREG_CNF                    ,
            "MSG:  ID_IMSA_MSCC_DEREG_CNF                             "},
    {   ID_IMSA_MSCC_IMS_VOICE_CAP_NOTIFY                    ,
            "MSG:  ID_IMSA_MSCC_IMS_VOICE_CAP_NOTIFY                  "}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astImsaApsEvtIdArray[] =
{
    {   ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF,
            "MSG:  ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF               "},
    {   ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ                   ,
            "MSG:  ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ               "},
    {   ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_IND                    ,
            "MSG:  ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_IND               "},
    {   ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND                    ,
            "MSG:  ID_EVT_TAF_PS_CALL_PDP_MODIFY_IND                 "},
    {   ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF                    ,
            "MSG:  ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF             "},
    {   ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND                    ,
            "MSG:  ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND             "},
    {   ID_EVT_TAF_PS_CALL_PDP_IPV6_INFO_IND                    ,
            "MSG:  ID_EVT_TAF_PS_CALL_PDP_IPV6_INFO_IND              "},
    {   ID_EVT_TAF_PS_CALL_ORIG_CNF                    ,
            "MSG:  ID_EVT_TAF_PS_CALL_ORIG_CNF                       "},
    {   ID_EVT_TAF_PS_CALL_END_CNF                    ,
            "MSG:  ID_EVT_TAF_PS_CALL_END_CNF                        "},
    {   ID_EVT_TAF_PS_SRVCC_CANCEL_NOTIFY_IND                    ,
            "MSG:  ID_EVT_TAF_PS_SRVCC_CANCEL_NOTIFY_IND             "}
};

NAS_COMM_PRINT_LIST_STRU g_astImsaSpmMsgIdArray[] =
{
    {   ID_SPM_IMSA_CALL_ORIG_REQ               ,
            "MSG:  ID_SPM_IMSA_CALL_ORIG_REQ                         ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_CALL_SUPS_CMD_REQ     ,
            "MSG:  ID_SPM_IMSA_CALL_SUPS_CMD_REQ                     ",
        IMSA_PrintSpmImsaCallSupsCmdReq},
    {   ID_SPM_IMSA_CALL_GET_CALL_INFO_REQ               ,
            "MSG:  ID_SPM_IMSA_CALL_GET_CALL_INFO_REQ                ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_CALL_START_DTMF_REQ               ,
            "MSG:  ID_SPM_IMSA_CALL_START_DTMF_REQ                   ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_CALL_STOP_DTMF_REQ             ,
            "MSG:  ID_SPM_IMSA_CALL_STOP_DTMF_REQ                    ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_CALL_GET_CUDR_REQ               ,
            "MSG:  ID_SPM_IMSA_CALL_GET_CUDR_REQ                     ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_CALL_GET_CLPR_REQ               ,
            "MSG:  ID_SPM_IMSA_CALL_GET_CLPR_REQ                     ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_CALL_MODIFY_REQ               ,
            "MSG:  ID_SPM_IMSA_CALL_MODIFY_REQ                     ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ               ,
            "MSG:  ID_SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ                     ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_CALL_ECONF_DIAL_REQ               ,
            "MSG:  ID_SPM_IMSA_CALL_ECONF_DIAL_REQ                     ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_CALL_ECONF_ADD_USERS_REQ               ,
            "MSG:  ID_SPM_IMSA_CALL_ECONF_ADD_USERS_REQ                     ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ               ,
            "MSG:  ID_SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ                     ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_REGISTER_SS_REQ     ,
            "MSG:  ID_SPM_IMSA_REGISTER_SS_REQ                       ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_ERASE_SS_REQ               ,
            "MSG:  ID_SPM_IMSA_ERASE_SS_REQ                          ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_ACTIVATE_SS_REQ               ,
            "MSG:  ID_SPM_IMSA_ACTIVATE_SS_REQ                       ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_DEACTIVATE_SS_REQ             ,
            "MSG:  ID_SPM_IMSA_DEACTIVATE_SS_REQ                     ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_INTERROGATE_SS_REQ               ,
            "MSG:  ID_SPM_IMSA_INTERROGATE_SS_REQ                    ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_PROCESS_USSD_REQ     ,
            "MSG:  ID_SPM_IMSA_PROCESS_USSD_REQ                      ",
        VOS_NULL_PTR},
    {   ID_SPM_IMSA_RELEASE_REQ               ,
            "MSG:  ID_SPM_IMSA_RELEASE_REQ                           ",
        VOS_NULL_PTR},
    {   ID_IMSA_SPM_CALL_MSG               ,
            "MSG:  ID_IMSA_SPM_CALL_MSG                              ",
        IMSA_PrintImsaSpmCallMsg},
    {   ID_IMSA_SPM_CALL_GET_CALL_INFO_CNF             ,
            "MSG:  ID_IMSA_SPM_CALL_GET_CALL_INFO_CNF                ",
        VOS_NULL_PTR},
    {   ID_IMSA_SPM_CHANNEL_INFO_IND               ,
            "MSG:  ID_IMSA_SPM_CHANNEL_INFO_IND                      ",
        VOS_NULL_PTR},
    {   ID_IMSA_SPM_CALL_GET_CLPR_CNF               ,
            "MSG:  ID_IMSA_SPM_CALL_GET_CLPR_CNF                     ",
        VOS_NULL_PTR},
    {   ID_IMSA_SPM_CALL_START_DTMF_CNF               ,
            "MSG:  ID_IMSA_SPM_CALL_START_DTMF_CNF                   ",
        VOS_NULL_PTR},
    {   ID_IMSA_SPM_CALL_START_DTMF_RSLT_IND             ,
            "MSG:  ID_IMSA_SPM_CALL_START_DTMF_RSLT_IND              ",
        VOS_NULL_PTR},
    {   ID_IMSA_SPM_CALL_STOP_DTMF_CNF               ,
            "MSG:  ID_IMSA_SPM_CALL_STOP_DTMF_CNF                    ",
        VOS_NULL_PTR},
    {   ID_IMSA_SPM_CALL_STOP_DTMF_RSLT_IND               ,
            "MSG:  ID_IMSA_SPM_CALL_STOP_DTMF_RSLT_IND               ",
        VOS_NULL_PTR},
    {   ID_IMSA_SPM_CALL_MODIFY_CNF               ,
            "MSG:  ID_IMSA_SPM_CALL_MODIFY_CNF               ",
        VOS_NULL_PTR},
    {   ID_IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF               ,
            "MSG:  ID_IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF               ",
        VOS_NULL_PTR},
    {   ID_IMSA_SPM_CALL_MODIFY_STATUS_IND               ,
            "MSG:  ID_IMSA_SPM_CALL_MODIFY_STATUS_IND               ",
        VOS_NULL_PTR},
    {   ID_IMSA_SPM_SS_MSG,
            "MSG:  ID_IMSA_SPM_SS_MSG                                ",
        VOS_NULL_PTR},
    /* xiongxianghui00253310 add for conference 20140210 begin */
    {   ID_SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ,
            "MSG:  ID_SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ              ",
        VOS_NULL_PTR},
    {   ID_IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF,
            "MSG:  ID_IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF              ",
        VOS_NULL_PTR},
    /* xiongxianghui00253310 add for conference 20140210 end */
    {   ID_IMSA_SPM_CALL_ECONF_DIAL_CNF,
            "MSG:  ID_IMSA_SPM_CALL_ECONF_DIAL_CNF              ",
        VOS_NULL_PTR},
    {   ID_IMSA_SPM_CALL_ECONF_ADD_USERS_CNF,
            "MSG:  ID_IMSA_SPM_CALL_ECONF_ADD_USERS_CNF              ",
        VOS_NULL_PTR},
    {   ID_IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF,
            "MSG:  ID_IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF              ",
        VOS_NULL_PTR},
    {   ID_IMSA_SPM_CALL_ECONF_NOTIFY_IND,
            "MSG:  ID_IMSA_SPM_CALL_ECONF_NOTIFY_IND              ",
        VOS_NULL_PTR}
};

NAS_COMM_PRINT_LIST_STRU g_astImsaMsgMsgIdArray[] =
{
    {   ID_MSG_IMSA_RP_DATA_REQ                 ,
            "MSG:  ID_MSG_IMSA_RP_DATA_REQ                           ",
        VOS_NULL_PTR},
    {   ID_MSG_IMSA_REPORT_REQ                  ,
            "MSG:  ID_MSG_IMSA_REPORT_REQ                            ",
        VOS_NULL_PTR},
    {   ID_MSG_IMSA_SMMA_REQ                    ,
            "MSG:  ID_MSG_IMSA_SMMA_REQ                              ",
        VOS_NULL_PTR},
    {   ID_IMSA_MSG_DATA_IND                    ,
            "MSG:  ID_IMSA_MSG_DATA_IND                              ",
        VOS_NULL_PTR},
    {   ID_IMSA_MSG_REPORT_IND                  ,
            "MSG:  ID_IMSA_MSG_REPORT_IND                            ",
        VOS_NULL_PTR},
    {   ID_IMSA_MSG_MT_ERR_IND                  ,
            "MSG:  ID_IMSA_MSG_MT_ERR_IND                            ",
        VOS_NULL_PTR}
};

NAS_COMM_PRINT_LIST_STRU g_astImsaAtMsgIdArray[] =
{
    {   ID_AT_IMSA_CIREG_SET_REQ                 ,
            "MSG:  ID_AT_IMSA_CIREG_SET_REQ                           ",
        VOS_NULL_PTR},
    {   ID_AT_IMSA_CIREG_QRY_REQ                  ,
            "MSG:  ID_AT_IMSA_CIREG_QRY_REQ                            ",
        VOS_NULL_PTR},
    {   ID_AT_IMSA_CIREP_SET_REQ                    ,
            "MSG:  ID_AT_IMSA_CIREP_SET_REQ                              ",
        VOS_NULL_PTR},
    {   ID_AT_IMSA_CIREP_QRY_REQ                    ,
            "MSG:  ID_AT_IMSA_CIREP_QRY_REQ                              ",
        VOS_NULL_PTR},
    {   ID_AT_IMSA_VOLTEIMPU_QRY_REQ                    ,
            "MSG:  ID_AT_IMSA_VOLTEIMPU_QRY_REQ                              ",
        VOS_NULL_PTR},
    {   ID_AT_IMSA_CCWAI_SET_REQ                    ,
            "MSG:  ID_AT_IMSA_CCWAI_SET_REQ                              ",
        VOS_NULL_PTR},
    {   ID_IMSA_AT_CIREG_SET_CNF                  ,
            "MSG:  ID_IMSA_AT_CIREG_SET_CNF                            ",
        VOS_NULL_PTR},
    {   ID_IMSA_AT_CIREG_QRY_CNF                  ,
            "MSG:  ID_IMSA_AT_CIREG_QRY_CNF                            ",
        VOS_NULL_PTR},
    {   ID_IMSA_AT_CIREP_SET_CNF                  ,
            "MSG:  ID_IMSA_AT_CIREP_SET_CNF                            ",
        VOS_NULL_PTR},
    {   ID_IMSA_AT_CIREP_QRY_CNF                    ,
            "MSG:  ID_IMSA_AT_CIREP_QRY_CNF                              ",
        VOS_NULL_PTR},
    {   ID_IMSA_AT_VOLTEIMPU_QRY_CNF                    ,
            "MSG:  ID_IMSA_AT_VOLTEIMPU_QRY_CNF                              ",
        VOS_NULL_PTR},
    {   ID_IMSA_AT_CCWAI_SET_CNF                    ,
            "MSG:  ID_IMSA_AT_CCWAI_SET_CNF                              ",
        VOS_NULL_PTR},
    {   ID_IMSA_AT_CIREGU_IND                    ,
            "MSG:  ID_IMSA_AT_CIREGU_IND                              ",
        VOS_NULL_PTR},
    {   ID_IMSA_AT_CIREPH_IND                  ,
            "MSG:  ID_IMSA_AT_CIREPH_IND                            ",
        VOS_NULL_PTR},
    {   ID_IMSA_AT_CIREPI_IND                  ,
            "MSG:  ID_IMSA_AT_CIREPI_IND                            ",
        VOS_NULL_PTR},
    {   ID_IMSA_AT_MT_STATES_IND                  ,
            "MSG:  ID_IMSA_AT_MT_STATES_IND                            ",
        VOS_NULL_PTR}

};


NAS_COMM_PRINT_LIST_STRU g_astImsaCallMsgIdArray[] =
{
    {   ID_CALL_IMSA_SRVCC_STATUS_NOTIFY         ,
            "MSG:  ID_CALL_IMSA_SRVCC_STATUS_NOTIFY                  ",
        IMSA_PrintCallImsaSrvccStatusNotify},
    {   ID_IMSA_CALL_SRVCC_CALL_INFO_NOTIFY      ,
            "MSG:  ID_IMSA_CALL_SRVCC_CALL_INFO_NOTIFY               ",
        VOS_NULL_PTR},
    {   ID_IMSA_CALL_MSG_SYNC_IND      ,
            "MSG:  ID_IMSA_CALL_MSG_SYNC_IND                         ",
        VOS_NULL_PTR}
};

NAS_COMM_PRINT_LIST_STRU g_astImsaImsMsgIdArray[] =
{
    {   ID_IMSA_IMS_INPUT_CALL_MSG               ,
            "MSG:  ID_IMSA_IMS_INPUT_CALL_MSG                      ",
        IMSA_PrintImsaImsInputCall},
    {   ID_IMSA_IMS_INPUT_SMS_MSG     ,
            "MSG:  ID_IMSA_IMS_INPUT_SMS_MSG                       ",
        IMSA_PrintImsaImsInputSms},
    {   ID_IMSA_IMS_INPUT_SERVICE_MSG               ,
            "MSG:  ID_IMSA_IMS_INPUT_SERVICE_MSG                   ",
        IMSA_PrintImsaImsInputService},
    {   ID_IMSA_IMS_INPUT_SYSTEM_MSG               ,
            "MSG:  ID_IMSA_IMS_INPUT_SYSTEM_MSG                     ",
        IMSA_PrintImsaImsInputSystem},
    {   ID_IMSA_IMS_INPUT_PARA_MSG             ,
            "MSG:  ID_IMSA_IMS_INPUT_PARA_MSG                    ",
        IMSA_PrintImsaImsInputPara},
    {   ID_IMSA_IMS_INPUT_USSD_MSG             ,
            "MSG:  ID_IMSA_IMS_INPUT_USSD_MSG                    ",
        IMSA_PrintImsaImsInputPara},
    {   ID_IMSA_IMS_INPUT_NV_INFO_MSG             ,
            "MSG:  ID_IMSA_IMS_INPUT_NV_INFO_MSG                    ",
        VOS_NULL_PTR},

    {   ID_IMS_IMSA_OUTPUT_CALL_MSG     ,
            "MSG:  ID_IMS_IMSA_OUTPUT_CALL_MSG                     ",
        IMSA_PrintImsaImsOutputCall},
    {   ID_IMS_IMSA_OUTPUT_SMS_MSG               ,
            "MSG:  ID_IMS_IMSA_OUTPUT_SMS_MSG                      ",
        IMSA_PrintImsaImsOutputSms},
    {   ID_IMS_IMSA_OUTPUT_SERVICE_MSG               ,
            "MSG:  ID_IMS_IMSA_OUTPUT_SERVICE_MSG                  ",
        IMSA_PrintImsaImsOutputService},
    {   ID_IMS_IMSA_OUTPUT_SYSTEM_MSG             ,
            "MSG:  ID_IMS_IMSA_OUTPUT_SYSTEM_MSG                    ",
        IMSA_PrintImsaImsOutputSystem},
    {   ID_IMS_IMSA_OUTPUT_PARA_MSG               ,
            "MSG:  ID_IMS_IMSA_OUTPUT_PARA_MSG                   ",
        IMSA_PrintImsaImsOutputPara},
    {   ID_IMS_IMSA_OUTPUT_USSD_MSG               ,
            "MSG:  ID_IMS_IMSA_OUTPUT_USSD_MSG                   ",
        IMSA_PrintImsaImsOutputPara},
    {   ID_IMS_IMSA_OUTPUT_NV_INFO_MSG             ,
            "MSG:  IID_IMS_IMSA_OUTPUT_NV_INFO_MSG                    ",
        VOS_NULL_PTR}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astCallSupsCmdArray[] =
{
    {   MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB                   ,
            "enCallSupsCmd:  MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB                 \r\n"},
    {   MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH                   ,
            "enCallSupsCmd:  MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH                 \r\n"},
    {   MN_CALL_SUPS_CMD_REL_CALL_X                    ,
            "enCallSupsCmd:  MN_CALL_SUPS_CMD_REL_CALL_X                       \r\n"},
    {   MN_CALL_SUPS_CMD_REL_ALL_CALL                   ,
            "enCallSupsCmd:  MN_CALL_SUPS_CMD_REL_ALL_CALL                     \r\n"},
    {   MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH                   ,
            "enCallSupsCmd:  MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH                \r\n"},
    {   MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X                    ,
            "enCallSupsCmd:  MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X                 \r\n"},
    {   MN_CALL_SUPS_CMD_BUILD_MPTY                    ,
            "enCallSupsCmd:  MN_CALL_SUPS_CMD_BUILD_MPTY                       \r\n"},
    {   MN_CALL_SUPS_CMD_ECT                   ,
            "enCallSupsCmd:  MN_CALL_SUPS_CMD_ECT                              \r\n"},
    {   MN_CALL_SUPS_CMD_DEFLECT_CALL                   ,
            "enCallSupsCmd:  MN_CALL_SUPS_CMD_DEFLECT_CALL                     \r\n"},
    {   MN_CALL_SUPS_CMD_ACT_CCBS                    ,
            "enCallSupsCmd:  MN_CALL_SUPS_CMD_ACT_CCBS                         \r\n"},
    {   MN_CALL_SUPS_CMD_REL_ALL_EXCEPT_WAITING_CALL                   ,
            "enCallSupsCmd:  MN_CALL_SUPS_CMD_REL_ALL_EXCEPT_WAITING_CALL      \r\n"},
    {   MN_CALL_SUPS_CMD_REL_HELD                   ,
            "enCallSupsCmd:  MN_CALL_SUPS_CMD_REL_HELD                         \r\n"},
    {   MN_CALL_SUPS_CMD_REL_ACTIVE                    ,
            "enCallSupsCmd:  MN_CALL_SUPS_CMD_REL_ACTIVE                       \r\n"},
    {   MN_CALL_SUPS_CMD_ECONF_REL_USER                    ,
            "enCallSupsCmd:  MN_CALL_SUPS_CMD_ECONF_REL_USER                       \r\n"},
    {   MN_CALL_SUPS_CMD_ECONF_MERGE_CALL                    ,
            "enCallSupsCmd:  MN_CALL_SUPS_CMD_ECONF_MERGE_CALL                       \r\n"},
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astCallMsgEvtArray[] =
{
    {   MN_CALL_EVT_ORIG                   ,
            "enEventType:  MN_CALL_EVT_ORIG                                  \r\n"},
    {   MN_CALL_EVT_CALL_PROC                   ,
            "enEventType:  MN_CALL_EVT_CALL_PROC                             \r\n"},
    {   MN_CALL_EVT_ALERTING                    ,
            "enEventType:  MN_CALL_EVT_ALERTING                              \r\n"},
    {   MN_CALL_EVT_CONNECT                   ,
            "enEventType:  MN_CALL_EVT_CONNECT                               \r\n"},
    {   MN_CALL_EVT_RELEASED                   ,
            "enEventType:  MN_CALL_EVT_RELEASED                              \r\n"},
    {   MN_CALL_EVT_INCOMING                    ,
            "enEventType:  MN_CALL_EVT_INCOMING                              \r\n"},
    {   MN_CALL_EVT_SS_CMD_PROGRESS                    ,
            "enEventType:  MN_CALL_EVT_SS_CMD_PROGRESS                       \r\n"},
    {   MN_CALL_EVT_SS_CMD_RSLT                    ,
            "enEventType:  MN_CALL_EVT_SS_CMD_RSLT                           \r\n"},
    {   MN_CALL_EVT_START_DTMF_CNF                   ,
            "enEventType:  MN_CALL_EVT_START_DTMF_CNF                        \r\n"},
    {   MN_CALL_EVT_STOP_DTMF_CNF                    ,
            "enEventType:  MN_CALL_EVT_STOP_DTMF_CNF                         \r\n"},
    {   MN_CALL_EVT_HOLD                   ,
            "enEventType:  MN_CALL_EVT_HOLD                                  \r\n"},
    {   MN_CALL_EVT_RETRIEVE                   ,
            "enEventType:  MN_CALL_EVT_RETRIEVE                              \r\n"},
    /*del the MN_CALL_EVT_ERR_IND base on gu xixiangying request*/
    {   MN_CALL_EVT_CALL_ORIG_CNF                    ,
            "enEventType:  MN_CALL_EVT_CALL_ORIG_CNF                         \r\n"},
    {   MN_CALL_EVT_SUPS_CMD_CNF                    ,
            "enEventType:  MN_CALL_EVT_SUPS_CMD_CNF                          \r\n"},
    {   MN_CALL_EVT_ALL_RELEASED                    ,
            "enEventType:  MN_CALL_EVT_ALL_RELEASED                          \r\n"},
    {   MN_CALL_EVT_START_DTMF_RSLT                    ,
            "enEventType:  MN_CALL_EVT_START_DTMF_RSLT                       \r\n"},
    {   MN_CALL_EVT_STOP_DTMF_RSLT                    ,
            "enEventType:  MN_CALL_EVT_STOP_DTMF_RSLT                        \r\n"},
    {   MN_CALL_EVT_CALL_MODIFY_CNF                    ,
            "enEventType:  MN_CALL_EVT_CALL_MODIFY_CNF                        \r\n"},
    {   MN_CALL_EVT_CALL_ANSWER_REMOTE_MODIFY_CNF                    ,
            "enEventType:  MN_CALL_EVT_CALL_ANSWER_REMOTE_MODIFY_CNF        \r\n"},
    {   MN_CALL_EVT_CALL_MODIFY_STATUS_IND                    ,
            "enEventType:  MN_CALL_EVT_CALL_MODIFY_STATUS_IND               \r\n"},
    {   TAF_CALL_EVT_ECONF_DIAL_CNF                    ,
            "enEventType:  TAF_CALL_EVT_ECONF_DIAL_CNF                        \r\n"},
    {   TAF_CALL_EVT_ECONF_NOTIFY_IND                    ,
            "enEventType:  TAF_CALL_EVT_ECONF_NOTIFY_IND                        \r\n"},
    {   TAF_CALL_EVT_CLCCECONF_INFO                    ,
            "enEventType:  TAF_CALL_EVT_CLCCECONF_INFO                        \r\n"}

};

NAS_COMM_PRINT_MSG_LIST_STRU g_astInputCallReasonArray[] =
{
    {   IMSA_IMS_INPUT_CALL_REASON_DIAL                   ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_DIAL                           \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_REPORT                   ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_REPORT                         \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_ANSWER                    ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_ANSWER                         \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_HANGUP                   ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_HANGUP                         \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_SWAP                   ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_SWAP                           \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_REL_ACTIVE_AND_ACCEPT_OTH                    ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_REL_ACTIVE_AND_ACCEPT_OTH      \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_REL_HELD_OR_WAITING                    ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_REL_HELD_OR_WAITING            \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_HOLD_ALL_EXCEPT_X                   ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_HOLD_ALL_EXCEPT_X              \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_DTMF                   ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_DTMF                           \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_RELEASE_AT_X                    ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_RELEASE_AT_X                   \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_CONFERENCE                   ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_CONFERENCE                     \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_SRVCC_START                    ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_SRVCC_START                    \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_SRVCC_SUCCESS                   ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_SRVCC_SUCCESS                  \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_SRVCC_FAILED                   ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_SRVCC_FAILED                   \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_SRVCC_CANCELED                   ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_SRVCC_CANCELED                  \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_RESOURCE_READY                   ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_RESOURCE_READY                 \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_RESOURCE_FAILED                   ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_RESOURCE_FAILED                \r\n"},
    /* xiongxianghui00253310 add for conference 20140214 begin */
    {   IMSA_IMS_INPUT_CALL_REASON_CONFERENCE_INVITE_NEW_PARTICIPANT   ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_CONFERENCE_INVITE_NEW_PARTICIPANT  \r\n"},
    /* xiongxianghui00253310 add for conference 20140214 end */
    {   IMSA_IMS_INPUT_CALL_REASON_MODIFY   ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_MODIFY                         \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_ANSWER_REMOTE_MODIFY   ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_ANSWER_REMOTE_MODIFY           \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_CREAT_NEW_ECONFERENCE    ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_CREAT_NEW_ECONFERENCE           \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_ECONFERENCE_INVITE_NEW_PARTICIPANT    ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_ECONFERENCE_INVITE_NEW_PARTICIPANT \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_ECONFERENCE_MERGER_NEW_PARTICIPANT    ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_ECONFERENCE_MERGER_NEW_PARTICIPANT \r\n"},
    {   IMSA_IMS_INPUT_CALL_REASON_ECONFERENCE_KICK_PARTICIPANT    ,
            "REASON:  IMSA_IMS_INPUT_CALL_REASON_ECONFERENCE_KICK_PARTICIPANT   \r\n"}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astInputSmsReasonArray[] =
{
    {   IMSA_IMS_INPUT_SMS_REASON_SEND_MESSAGE                   ,
            "REASON:  IMSA_IMS_INPUT_SMS_REASON_SEND_MESSAGE                    \r\n"},
    {   IMSA_IMS_INPUT_SMS_REASON_TR1M_EXP                   ,
            "REASON:  IMSA_IMS_INPUT_SMS_REASON_TR1M_EXP                        \r\n"}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astInputServiceReasonArray[] =
{
    {   IMSA_IMS_INPUT_SERVICE_REASON_REGISTER                   ,
            "REASON:  IMSA_IMS_INPUT_SERVICE_REASON_REGISTER                    \r\n"},
    {   IMSA_IMS_INPUT_SERVICE_REASON_REGISTER_EMERGENCY                   ,
            "REASON:  IMSA_IMS_INPUT_SERVICE_REASON_REGISTER_EMERGENCY          \r\n"},
    {   IMSA_IMS_INPUT_SERVICE_REASON_DEREGISTER                    ,
            "REASON:  IMSA_IMS_INPUT_SERVICE_REASON_DEREGISTER                  \r\n"},
    {   IMSA_IMS_INPUT_SERVICE_REASON_LOCAL_DEREGISTER                   ,
            "REASON:  IMSA_IMS_INPUT_SERVICE_REASON_LOCAL_DEREGISTER            \r\n"},
    {   IMSA_IMS_INPUT_SERVICE_REASON_LOCAL_DEREGISTER_EMERGENCY                    ,
            "REASON:  IMSA_IMS_INPUT_SERVICE_REASON_LOCAL_DEREGISTER_EMERGENCY  \r\n"},
    {   IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_SUCCESS                    ,
            "REASON:  IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_SUCCESS        \r\n"},
    {   IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_NETWORK_FAILURE                   ,
            "REASON:  IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_NETWORK_FAILURE\r\n"},
    {   IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_SYNC_FAILURE                   ,
            "REASON:  IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_SYNC_FAILURE   \r\n"},
    {   IMSA_IMS_INPUT_SERVICE_REASON_SUSPEND_NRM_SRV                   ,
            "REASON:  IMSA_IMS_INPUT_SERVICE_REASON_SUSPEND_NRM_SRV   \r\n"},
    {   IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV                   ,
            "REASON:  IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV   \r\n"},
    {   IMSA_IMS_INPUT_SERVICE_REASON_SUSPEND_EMC_SRV                   ,
            "REASON:  IMSA_IMS_INPUT_SERVICE_REASON_SUSPEND_EMC_SRV   \r\n"},
    {   IMSA_IMS_INPUT_SERVICE_REASON_RESUME_EMC_SRV                   ,
            "REASON:  IMSA_IMS_INPUT_SERVICE_REASON_RESUME_EMC_SRV   \r\n"}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astInputSystemReasonArray[] =
{
    {   IMSA_IMS_INPUT_SYSTEM_REASON_START                   ,
            "REASON:  IMSA_IMS_INPUT_SYSTEM_REASON_START                        \r\n"},
    {   IMSA_IMS_INPUT_SYSTEM_REASON_STOP                    ,
            "REASON:  IMSA_IMS_INPUT_SYSTEM_REASON_STOP                         \r\n"}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astInputParaReasonArray[] =
{
    {   IMAS_IMS_INPUT_PARA_REASON_SET_CGI                   ,
            "REASON:  IMAS_IMS_INPUT_PARA_REASON_SET_CGI                        \r\n"},
    {   IMAS_IMS_INPUT_PARA_REASON_SET_NORMAL_IP                    ,
            "REASON:  IMAS_IMS_INPUT_PARA_REASON_SET_NORMAL_IP                  \r\n"},
    {   IMAS_IMS_INPUT_PARA_REASON_SET_EMC_IP                   ,
            "REASON:  IMAS_IMS_INPUT_PARA_REASON_SET_EMC_IP                     \r\n"},
    {   IMAS_IMS_INPUT_PARA_REASON_SET_PORTS                   ,
            "REASON:  IMAS_IMS_INPUT_PARA_REASON_SET_PORTS                      \r\n"},
    {   IMAS_IMS_INPUT_PARA_REASON_SET_IPSEC                    ,
            "REASON:  IMAS_IMS_INPUT_PARA_REASON_SET_IPSEC                      \r\n"},
    {   IMAS_IMS_INPUT_PARA_REASON_SET_NORMAL_ACCOUNT                   ,
            "REASON:  IMAS_IMS_INPUT_PARA_REASON_SET_NORMAL_ACCOUNT             \r\n"},
    {   IMAS_IMS_INPUT_PARA_REASON_SET_EMC_ACCOUNT                    ,
            "REASON:  IMAS_IMS_INPUT_PARA_REASON_SET_EMC_ACCOUNT                \r\n"},
    {   IMAS_IMS_INPUT_PARA_REASON_SET_UE_CAPABILITIES                   ,
            "REASON:  IMAS_IMS_INPUT_PARA_REASON_SET_UE_CAPABILITIES            \r\n"},
    {   IMAS_IMS_INPUT_PARA_REASON_SET_NETWORK_CAPABILITIES                   ,
            "REASON:  IMAS_IMS_INPUT_PARA_REASON_SET_NETWORK_CAPABILITIES       \r\n"},
    {   IMAS_IMS_INPUT_PARA_REASON_SET_TIMER_LENGTH                    ,
            "REASON:  IMAS_IMS_INPUT_PARA_REASON_SET_TIMER_LENGTH               \r\n"},
    {   IMAS_IMS_INPUT_PARA_REASON_SET_IMEI                    ,
            "REASON:  IMAS_IMS_INPUT_PARA_REASON_SET_IMEI                       \r\n"},
    {   IMAS_IMS_INPUT_PARA_REASON_SET_CALL_WAITING                    ,
            "REASON:  IMAS_IMS_INPUT_PARA_REASON_SET_CALL_WAITING               \r\n"}
};


NAS_COMM_PRINT_MSG_LIST_STRU g_astOutputCallReasonArray[] =
{
    {   IMSA_IMS_OUTPUT_CALL_REASON_OK                   ,
            "REASON:  IMSA_IMS_OUTPUT_CALL_REASON_OK                            \r\n"},
    {   IMSA_IMS_OUTPUT_CALL_REASON_ERROR                   ,
            "REASON:  IMSA_IMS_OUTPUT_CALL_REASON_ERROR                         \r\n"},
    {   IMSA_IMS_OUTPUT_CALL_REASON_CALL_LIST                    ,
            "REASON:  IMSA_IMS_OUTPUT_CALL_REASON_CALL_LIST                     \r\n"},
    {   IMSA_IMS_OUTPUT_CALL_REASON_DISCONNECT_EVENT                   ,
            "REASON:  IMSA_IMS_OUTPUT_CALL_REASON_DISCONNECT_EVENT              \r\n"},
    {   IMSA_IMS_OUTPUT_CALL_REASON_INCOMING_EVENT                   ,
            "REASON:  IMSA_IMS_OUTPUT_CALL_REASON_INCOMING_EVENT                \r\n"},
    {   IMSA_IMS_OUTPUT_CALL_REASON_WAITING_EVENT                    ,
            "REASON:  IMSA_IMS_OUTPUT_CALL_REASON_WAITING_EVENT                 \r\n"},
    {   IMSA_IMS_OUTPUT_CALL_REASON_INITIALIZING_EVENT                    ,
            "REASON:  IMSA_IMS_OUTPUT_CALL_REASON_INITIALIZING_EVENT            \r\n"},
    {   IMSA_IMS_OUTPUT_CALL_REASON_SRVCC_CALL_LIST                   ,
            "REASON:  IMSA_IMS_OUTPUT_CALL_REASON_SRVCC_CALL_LIST               \r\n"},
    {   IMSA_IMS_OUTPUT_CALL_REASON_EARLY_MEDIA                    ,
            "REASON:  IMSA_IMS_OUTPUT_CALL_REASON_EARLY_MEDIA                   \r\n"},
    {   IMSA_IMS_OUTPUT_CALL_REASON_EMERGENCY_INDICATION                   ,
            "REASON:  IMSA_IMS_OUTPUT_CALL_REASON_EMERGENCY_INDICATION          \r\n"},
    {   IMSA_IMS_OUTPUT_CALL_REASON_EXTRA_INFO                    ,
            "REASON:  IMSA_IMS_OUTPUT_CALL_REASON_EXTRA_INFO                    \r\n"},
    {   IMSA_IMS_OUTPUT_CALL_REASON_MODIFY_IND                    ,
            "REASON:  IMSA_IMS_OUTPUT_CALL_REASON_MODIFY_IND                    \r\n"},
    {   IMSA_IMS_OUTPUT_CALL_REASON_MODIFY_BEGIN                    ,
            "REASON:  IMSA_IMS_OUTPUT_CALL_REASON_MODIFY_BEGIN                  \r\n"},
    {   IMSA_IMS_OUTPUT_CALL_REASON_MODIFY_END                    ,
            "REASON:  IMSA_IMS_OUTPUT_CALL_REASON_MODIFY_END                    \r\n"},
    {   IMSA_IMS_OUTPUT_CALL_REASON_ECONF_NOTIFY_IND                    ,
            "REASON:  IMSA_IMS_OUTPUT_CALL_REASON_ECONF_NOTIFY_IND                    \r\n"}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astOutputSmsReasonArray[] =
{
    {   IMSA_IMS_OUTPUT_SMS_REASON_OK                   ,
            "REASON:  IMSA_IMS_OUTPUT_SMS_REASON_OK                             \r\n"},
    {   IMSA_IMS_OUTPUT_SMS_REASON_ERROR                   ,
            "REASON:  IMSA_IMS_OUTPUT_SMS_REASON_ERROR                          \r\n"},
    {   IMSA_IMS_OUTPUT_SMS_REASON_SMS_RECEIVED                   ,
            "REASON:  IMSA_IMS_OUTPUT_SMS_REASON_SMS_RECEIVED                   \r\n"},
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astOutputServiceReasonArray[] =
{
    {   IMSA_IMS_OUTPUT_SEVICE_REASON_OK                   ,
            "REASON:  IMSA_IMS_OUTPUT_SEVICE_REASON_OK                          \r\n"},
    {   IMSA_IMS_OUTPUT_SEVICE_REASON_ERROR                   ,
            "REASON:  IMSA_IMS_OUTPUT_SEVICE_REASON_ERROR                       \r\n"},
    {   IMSA_IMS_OUTPUT_SEVICE_REASON_STATE                    ,
            "REASON:  IMSA_IMS_OUTPUT_SEVICE_REASON_STATE                       \r\n"},
    {   IMSA_IMS_OUTPUT_SEVICE_REASON_AUTH_CHALLENGE                   ,
            "REASON:  IMSA_IMS_OUTPUT_SEVICE_REASON_AUTH_CHALLENGE              \r\n"},
    {   IMSA_IMS_OUTPUT_SEVICE_REASON_IPSEC_SETUP                    ,
            "REASON:  IMSA_IMS_OUTPUT_SEVICE_REASON_IPSEC_SETUP                 \r\n"},
    {   IMSA_IMS_OUTPUT_SEVICE_REASON_IPSEC_RELEASE                    ,
            "REASON:  IMSA_IMS_OUTPUT_SEVICE_REASON_IPSEC_RELEASE               \r\n"}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astOutputSystemReasonArray[] =
{
    {   IMSA_IMS_OUTPUT_SYSTM_REASON_OK                   ,
            "REASON:  IMSA_IMS_OUTPUT_SYSTM_REASON_OK                           \r\n"},
    {   IMSA_IMS_OUTPUT_SYSTM_REASON_ERROR                    ,
            "REASON:  IMSA_IMS_OUTPUT_SYSTM_REASON_ERROR                        \r\n"}
};

NAS_COMM_PRINT_MSG_LIST_STRU g_astOutputParaReasonArray[] =
{
    {   IMSA_IMS_OUTPUT_PARA_REASON_SET_OK                   ,
            "REASON:  IMSA_IMS_OUTPUT_PARA_REASON_SET_OK                        \r\n"},
    {   IMSA_IMS_OUTPUT_PARA_REASON_SET_PORTS_ERROR                    ,
            "REASON:  IMSA_IMS_OUTPUT_PARA_REASON_SET_PORTS_ERROR               \r\n"},
    {   IMAS_IMS_OUTPUT_PARA_REASON_SET_CGI_ERROR                   ,
            "REASON:  IMAS_IMS_OUTPUT_PARA_REASON_SET_CGI_ERROR                 \r\n"},
    {   IMAS_IMS_OUTPUT_PARA_REASON_SET_NORMAL_IP_ERROR                   ,
            "REASON:  IMAS_IMS_OUTPUT_PARA_REASON_SET_NORMAL_IP_ERROR           \r\n"},
    {   IMAS_IMS_OUTPUT_PARA_REASON_SET_EMC_IP_ERROR                    ,
            "REASON:  IMAS_IMS_OUTPUT_PARA_REASON_SET_EMC_IP_ERROR              \r\n"},
    {   IMAS_IMS_OUTPUT_PARA_REASON_SET_IPSEC_ERROR                   ,
            "REASON:  IMAS_IMS_OUTPUT_PARA_REASON_SET_IPSEC_ERROR               \r\n"},
    {   IMAS_IMS_OUTPUT_PARA_REASON_SET_NORMAL_ACCOUNT_ERROR                    ,
            "REASON:  IMAS_IMS_OUTPUT_PARA_REASON_SET_NORMAL_ACCOUNT_ERROR      \r\n"},
    {   IMAS_IMS_OUTPUT_PARA_REASON_SET_EMC_ACCOUNT_ERROR                   ,
            "REASON:  IMAS_IMS_OUTPUT_PARA_REASON_SET_EMC_ACCOUNT_ERROR         \r\n"},
    {   IMAS_IMS_OUTPUT_PARA_REASON_SET_TIMER_LENGTH_ERROR                   ,
            "REASON:  IMAS_IMS_OUTPUT_PARA_REASON_SET_TIMER_LENGTH_ERROR        \r\n"},
    {   IMAS_IMS_OUTPUT_PARA_REASON_SET_REG_CAPABILITIES_ERROR                    ,
            "REASON:  IMAS_IMS_OUTPUT_PARA_REASON_SET_REG_CAPABILITIES_ERROR    \r\n"},
    {   IMSA_IMS_OUTPUT_PARA_REASON_QUERY_OK                    ,
            "REASON:  IMSA_IMS_OUTPUT_PARA_REASON_QUERY_OK                        \r\n"}
};

#if (FEATURE_ON == FEATURE_DSDS)
NAS_COMM_PRINT_MSG_LIST_STRU g_astImsaErrcMsgIdArray[] =
{
    {   ID_IMSA_LRRC_BEGIN_SESSION_NOTIFY,
            "MSG:  ID_IMSA_LRRC_BEGIN_SESSION_NOTIFY                    "},
    {   ID_IMSA_LRRC_END_SESSION_NOTIFY                   ,
            "MSG:  ID_IMSA_LRRC_END_SESSION_NOTIFY                    "}
};
#endif


NAS_COMM_PRINT_MSG_LIST_STRU g_astImsaMtcMsgIdArray[] =
{
    {   ID_IMSA_MTC_SRV_CONN_STATUS_NOTIFY                   ,
            "MSG:  ID_IMSA_MTC_SRV_CONN_STATUS_NOTIFY                    "},
    {   ID_MTC_IMSA_MODEM1_INFO_IND                   ,
            "MSG:  ID_MTC_IMSA_MODEM1_INFO_IND                    "}
};

/*****************************************************************************
  3 Function
*****************************************************************************/
/*lint -e961*/

VOS_VOID  IMSA_SndOmImsaTimerStatus(
    IMSA_TIMER_RUN_STA_ENUM_UINT32          enTimerStatus,
    VOS_UINT16                          enTimerId,
    VOS_UINT32                          ulTimerRemainLen
)
{
    IMSA_TIMER_INFO_STRU                     *pstMsg = VOS_NULL_PTR;

    pstMsg = (IMSA_TIMER_INFO_STRU*)IMSA_ALLOC_MSG(sizeof(IMSA_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndOmImsaTimerStatus: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndOmImsaTimerStatus_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_WRITE_INTRA_MSG_HEAD(  pstMsg,
                                enTimerId + PS_MSG_ID_IMSA_TO_IMSA_OM_BASE,
                                sizeof(IMSA_TIMER_INFO_STRU));

    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->usTimerId                   = enTimerId;
    pstMsg->usRsv                       = 0;

    pstMsg->ulTimerRemainLen            = ulTimerRemainLen;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    IMSA_FREE_MSG(pstMsg);

}



/*****************************************************************************
 Function Name  : IMSA_StartTimer()
 Description    : ������ʱ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_StartTimer(IMSA_TIMER_STRU *pstTimer)
{
    if(pstTimer == VOS_NULL_PTR)
    {
        return;
    }

    /*�ж϶�ʱ���Ƿ�򿪣��Ѵ���ر�*/
    if(VOS_NULL_PTR != pstTimer->phTimer)
    {
        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimer->phTimer)))
        {
            /*��ӡ�쳣��Ϣ*/
            IMSA_WARN_LOG("IMSA_StartTimer:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING(IMSA_StartTimer_ENUM, LNAS_ERROR);
            return;
        }

        /*��ӡ�쳣��Ϣ*/
        IMSA_WARN_LOG1("(TimerType) Timer not close!",pstTimer->usName);
        TLPS_PRINT2LAYER_WARNING1(IMSA_StartTimer_ENUM, 2, pstTimer->usName);
    }

    if (pstTimer->ulTimerLen == 0)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_StopTimer:ERROR: start unreasonable reltimer.");
        TLPS_PRINT2LAYER_ERROR(IMSA_StartTimer_ENUM, 3);
        return;
    }

    /*�趨��ʱ��NAME����ʧ���򱨾�����*/
    if (VOS_OK !=\
            PS_START_REL_TIMER(&(pstTimer->phTimer),PS_PID_IMSA,\
                                pstTimer->ulTimerLen,(VOS_UINT32)pstTimer->usName,\
                                pstTimer->usPara,pstTimer->ucMode))
    {
          /*��ӡ�쳣��Ϣ*/
          IMSA_WARN_LOG("IMSA_StartTimer:WARN: start reltimer error!");
          TLPS_PRINT2LAYER_WARNING(IMSA_StartTimer_ENUM, 4);
          return;
    }

    /*������ǰ�Ķ�ʱ����Ϣ */
    /*bsun*/
    IMSA_SndOmImsaTimerStatus(IMSA_TIMER_RUNNING, pstTimer->usName, pstTimer->ulTimerLen);

}

/*****************************************************************************
 Function Name  : IMSA_StopTimer()
 Description    : ֹͣ��ʱ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_StopTimer(IMSA_TIMER_STRU *pstTimer)
{
    VOS_UINT32                          ulTimerRemainLen    =    0;

    if(pstTimer == VOS_NULL_PTR)
    {
        return;
    }

    /*�ж϶�ʱ���Ƿ�򿪣��Ѵ���ر�*/
    if(VOS_NULL_PTR != pstTimer->phTimer)
    {
        /* ��ȡ��ǰ��ʱ����ʣ��ʱ�� */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstTimer->phTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }

        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimer->phTimer)))
        {
            /*��ӡ�쳣��Ϣ*/
            IMSA_WARN_LOG("IMSA_StopTimer:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING(IMSA_StopTimer_ENUM, IMSA_CALL_API_ERROR);
            return;
        }

        pstTimer->phTimer = VOS_NULL_PTR;

        IMSA_INFO_LOG1("(TimerType) Timer closed!",pstTimer->usName);
        TLPS_PRINT2LAYER_INFO(IMSA_StopTimer_ENUM, LNAS_TIMER_STOP);
    }

    /*������ǰ�Ķ�ʱ����Ϣ */
    /*bsun*/
    /* modify by jiqiang 2014.03.24 pclint fix error 644 begin */
    /*lint -e644*/
    IMSA_SndOmImsaTimerStatus(IMSA_TIMER_STOPED, pstTimer->usName, ulTimerRemainLen);
    /*lint +e644*/
    /* modify by jiqiang 2014.03.24 pclint fix error 644 end */


}



/*****************************************************************************
 Function Name  : IMSA_IsTimerRunning()
 Description    : ��ѯ��ʱ���Ƿ���������
 Input          : IMSA_TIMER_STRU *pstTimer
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-26  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_IsTimerRunning(const IMSA_TIMER_STRU *pstTimer)
{
    /*��δ���*/
    if(pstTimer == VOS_NULL_PTR)
    {
        return VOS_FALSE;
    }

    /*�ж϶�ʱ���Ƿ�򿪣��Ѵ���ر�*/
    if(VOS_NULL_PTR != pstTimer->phTimer)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}


VOS_VOID IMSA_GetRemainTimeLen
(
    IMSA_TIMER_STRU                    *pstTimer,
    VOS_UINT32                         *pulRemainTimeLen
)
{
    VOS_UINT32                          ulRemainTick = IMSA_NULL;

    if (VOS_FALSE == IMSA_IsTimerRunning(pstTimer))
    {
        *pulRemainTimeLen = 0;
    }

    if (VOS_OK != VOS_GetRelTmRemainTime(&(pstTimer->phTimer), &ulRemainTick))
    {
        *pulRemainTimeLen = 0;
    }

    *pulRemainTimeLen = ulRemainTick * IMSA_TIMER_1_TICK_10_MS;
}



/*****************************************************************************
 Function Name  : IMSA_ProcReadIsimFileResult()
 Description    : ����������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing     49683      2013-06-21  Draft Enact
      2.zhaochen    00308719   2015-02-10  Modify for USIM interface
*****************************************************************************/
VOS_UINT32 IMSA_ProcReadIsimFileResult(VOS_VOID *pRcvMsg)
{
    /*zhaochen 00308719 begin for USIM interface*/
    USIMM_READFILE_CNF_STRU         *pstUsimCnf;
    IMSA_ISIM_ACTION_FUN            pActFun   = VOS_NULL_PTR;
    VOS_UINT32                      i;
    IMSA_ISIM_DATA_STRU             stIsimData;
    IMSA_CONTROL_MANAGER_STRU       *pstControlManager;
    USIMM_DEF_FILEID_ENUM_UINT32    enDefFileID;
    VOS_UINT32                      ulresult;

    pstUsimCnf          = (USIMM_READFILE_CNF_STRU*)pRcvMsg;
    pstControlManager   = IMSA_GetControlManagerAddress();

    /* ����USIM�ṩ�Ľӿڣ����ļ�·��ת��ΪFileID */
    /*zhaochen 00308719 begin for card lock 2015-10-31*/
    if (0 == strcmp(USIMM_USIM_EFAD_STR, pstUsimCnf->stFilePath.acPath))
    {
        ulresult = USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pstUsimCnf->stFilePath.ulPathLen, pstUsimCnf->stFilePath.acPath, &enDefFileID);
    }
    /*zhaochen 00308719 end for card lock 2015-10-31*/
    else
    {
        ulresult = USIMM_ChangePathToDefFileID(USIMM_IMS_APP, pstUsimCnf->stFilePath.ulPathLen, pstUsimCnf->stFilePath.acPath, &enDefFileID);
    }
    if(VOS_OK != ulresult)
    {
        /* ���ת��ʧ�ܣ���ʾû�ж�Ӧ��FileID */
        IMSA_WARN_LOG("IMSA_ProcReadIsimFileResult: USIMM_ChangePathToDefFileID err");
        TLPS_PRINT2LAYER_WARNING(IMSA_ProcReadIsimFileResult_ENUM, IMSA_CALL_API_ERROR);
        return VOS_ERR;
    }
    if(VOS_OK != pstUsimCnf->stCmdResult.ulResult)
    {
        /* ������صĽ��Ϊʧ�ܣ������������Ϣ */
        IMSA_WARN_LOG1("IMSA_ProcReadIsimFileResult: Read File err. UsimFileID =  ",
                                        enDefFileID);
        TLPS_PRINT2LAYER_WARNING1(IMSA_ProcReadIsimFileResult_ENUM, IMSA_CALL_API_ERROR, enDefFileID);
        return VOS_ERR;
    }
    /*zhaochen 00308719 end for USIM interface*/

    stIsimData.pData    = pstUsimCnf->aucEf;
    stIsimData.usDataLen= pstUsimCnf->usEfLen;

    for(i = 0; i < g_ulIsimDataMapNum; i++)
    {
        /* ��NV������ͬ,���ҵ���,���ص�ǰ��NV�����������˳�ѭ�� */
        if(enDefFileID == g_astIsimDataMap[i].enIsimFileId)
        {
           pActFun            = g_astIsimDataMap[i].pfDecodeActionFun;
           break;
        }
    }

    if (VOS_NULL_PTR != pActFun)
    {
        (VOS_VOID)(*pActFun) (&stIsimData);

        if ((IMSA_STATUS_STARTED == pstControlManager->enImsaStatus )
            && (IMSA_OP_TRUE == pstControlManager->stImsaCommonInfo.stImsaUeId.bitOpImpi)
            && (IMSA_OP_TRUE == pstControlManager->stImsaCommonInfo.stImsaUeId.bitOpTImpu)
            && (IMSA_OP_TRUE == pstControlManager->stImsaCommonInfo.bitOpHomeNetDomainName))
        {
            /* config account info to ims */
            IMSA_ConfigAccoutInfo2Ims(IMSA_REG_TYPE_NORMAL);

            /* config account info to ims */
            IMSA_ConfigAccoutInfo2Ims(IMSA_REG_TYPE_EMC);
        }

        return VOS_OK;
    }
    else
    {
        /* ����Ҳ�������������ʾ��ǰû�иô����� */
        IMSA_WARN_LOG1("IMSA_ProcReadIsimFileResult: no fun deal with UsimFileID =  ",
                                        enDefFileID);
        TLPS_PRINT2LAYER_WARNING1(IMSA_ProcReadIsimFileResult_ENUM, LNAS_PARAM_INVALID, enDefFileID);
        return  VOS_ERR;
    }

}

/*****************************************************************************
 Function Name  : IMSA_DecodeIsimImpu()
 Description    : IMPU����
 Input          : IMSA_ISIM_DATA_STRU *pstIsimData
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.sunbing 49683      2013-06-27  Draft Enact
*****************************************************************************/
VOS_UINT32  IMSA_DecodeIsimImpu(const IMSA_ISIM_DATA_STRU *pstIsimData)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;

    /*31.103 4.2.4��������IMPU�ĸ�ʽΪTLV��tag = '80'*/
    if( 0x80 != pstIsimData->pData[0])
    {
        IMSA_INFO_LOG1("IMSA_DecodeIsimImpu:tag = ", pstIsimData->pData[0]);
        TLPS_PRINT2LAYER_INFO1(IMSA_DecodeIsimImpu_ENUM, IMSA_ISIM_TAG, pstIsimData->pData[0]);
    }

    /*���Ȳ��Ϸ���������Ϊ���ֵ*/
    if(pstIsimData->pData[1]> IMSA_MAX_TIMPU_LEN)
    {
        IMSA_INFO_LOG1("IMSA_DecodeIsimImpu:lenth = ", pstIsimData->pData[1]);
        TLPS_PRINT2LAYER_INFO1(IMSA_DecodeIsimImpu_ENUM, IMSA_ISIM_LENGTH, pstIsimData->pData[1]);

        pstIsimData->pData[1] = IMSA_MAX_TIMPU_LEN;
    }

    pstControlManager = IMSA_GetControlManagerAddress();

    if (VOS_FALSE == pstControlManager->stImsaConfigPara.ucUserInfoFlag)
    {
        pstControlManager->stImsaCommonInfo.stImsaUeId.bitOpTImpu = IMSA_OP_TRUE;

        IMSA_MEM_SET(&pstControlManager->stImsaCommonInfo.stImsaUeId.stTImpu,\
                  0,\
                  IMSA_MAX_TIMPU_LEN+1);

        IMSA_MEM_CPY(&pstControlManager->stImsaCommonInfo.stImsaUeId.stTImpu, \
                 &pstIsimData->pData[2], \
                  pstIsimData->pData[1]);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_DecodeIsimImpi()
 Description    : IMPI����
 Input          : IMSA_ISIM_DATA_STRU *pstIsimData
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-27  Draft Enact
*****************************************************************************/
VOS_UINT32  IMSA_DecodeIsimImpi(const IMSA_ISIM_DATA_STRU *pstIsimData)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;

    /*31.103 4.2.2��������IMPI�ĸ�ʽΪTLV��tag = '80'*/
    if( 0x80 != pstIsimData->pData[0])
    {
        IMSA_INFO_LOG1("IMSA_DecodeIsimImpi:tag = ", pstIsimData->pData[0]);
        TLPS_PRINT2LAYER_INFO1(IMSA_DecodeIsimImpi_ENUM, IMSA_ISIM_TAG, pstIsimData->pData[0]);
    }

    /*���Ȳ��Ϸ���������Ϊ���ֵ*/
    if(pstIsimData->pData[1]> IMSA_MAX_IMPI_LEN)
    {
        IMSA_INFO_LOG1("IMSA_DecodeIsimImpi:lenth = ", pstIsimData->pData[1]);
        TLPS_PRINT2LAYER_INFO1(IMSA_DecodeIsimImpi_ENUM, IMSA_ISIM_LENGTH, pstIsimData->pData[1]);

        pstIsimData->pData[1] = IMSA_MAX_IMPI_LEN;
    }

    pstControlManager = IMSA_GetControlManagerAddress();

    if (VOS_FALSE == pstControlManager->stImsaConfigPara.ucUserInfoFlag)
    {
        pstControlManager->stImsaCommonInfo.stImsaUeId.bitOpImpi = IMSA_OP_TRUE;

        IMSA_MEM_SET(&pstControlManager->stImsaCommonInfo.stImsaUeId.stImpi,\
                  0,\
                  IMSA_MAX_IMPI_LEN +1);

        IMSA_MEM_CPY(&pstControlManager->stImsaCommonInfo.stImsaUeId.stImpi, \
                 &pstIsimData->pData[2], \
                  pstIsimData->pData[1]);
    }


    return VOS_TRUE;

}

/*****************************************************************************
 Function Name  : IMSA_DecodeIsimDomain()
 Description    : Domain����
 Input          : IMSA_ISIM_DATA_STRU *pstIsimData
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-27  Draft Enact
*****************************************************************************/
VOS_UINT32  IMSA_DecodeIsimDomain(const IMSA_ISIM_DATA_STRU *pstIsimData)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;

    /*31.103 4.2.3��������DOMAIN�ĸ�ʽΪTLV��tag = '80'*/
    if( 0x80 != pstIsimData->pData[0])
    {
        IMSA_INFO_LOG1("IMSA_DecodeIsimDomain:tag = ", pstIsimData->pData[0]);
        TLPS_PRINT2LAYER_INFO1(IMSA_DecodeIsimDomain_ENUM, IMSA_ISIM_TAG, pstIsimData->pData[0]);
    }

    /*���Ȳ��Ϸ���������Ϊ���ֵ*/
    if(pstIsimData->pData[1]> IMSA_MAX_HOME_NET_DOMAIN_NAME_LEN)
    {
        IMSA_INFO_LOG1("IMSA_DecodeIsimDomain:lenth = ", pstIsimData->pData[1]);
        TLPS_PRINT2LAYER_INFO1(IMSA_DecodeIsimDomain_ENUM, IMSA_ISIM_LENGTH, pstIsimData->pData[1]);

        pstIsimData->pData[1] = IMSA_MAX_HOME_NET_DOMAIN_NAME_LEN;
    }

    pstControlManager = IMSA_GetControlManagerAddress();

    if (VOS_FALSE == pstControlManager->stImsaConfigPara.ucUserInfoFlag)
    {
        pstControlManager->stImsaCommonInfo.bitOpHomeNetDomainName = IMSA_OP_TRUE;

        IMSA_MEM_SET(&pstControlManager->stImsaCommonInfo.stHomeNetDomainName,\
                  0,\
                  IMSA_MAX_HOME_NET_DOMAIN_NAME_LEN +1);

        IMSA_MEM_CPY(&pstControlManager->stImsaCommonInfo.stHomeNetDomainName, \
                 &pstIsimData->pData[2], \
                  pstIsimData->pData[1]);
    }

    return VOS_TRUE;

}

/*zhaochen 00308719 begin for card lock 2015-10-31*/
/*****************************************************************************
 Function Name  : IMSA_DecodeSimMncLen()
 Description    : Efad���룬��ȡ���е�MNC����
 Input          : IMSA_ISIM_DATA_STRU *pstIsimData
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.zhaochen    00308719    2015-10-31  Draft Enact
*****************************************************************************/
VOS_UINT32  IMSA_DecodeSimMncLen(const IMSA_ISIM_DATA_STRU *pstIsimData)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;
    IMSA_NV_CARD_LOCK_STRU          stNvCardLock;
    VOS_UINT32                      ulImsiMncLen;
    VOS_UINT8                       aucPlmnId[4] = {0};
    VOS_UINT8                       ucImsi[10]   = {0};
    VOS_UINT8                       i,ucPlmnNotMatchflag = 0;

    /* Ĭ���ǲ�����״̬ */
    pstControlManager                 = IMSA_GetControlManagerAddress();
    pstControlManager->ucIsCardLocked = VOS_FALSE;

    /* ����USIM�ṩ�Ľӿڣ���ȡIMSI */
    if (VOS_OK != USIMM_GetCardIMSI (ucImsi))
    {
        TLPS_PRINT2LAYER_INFO(IMSA_DecodeIsimDomain_ENUM, 1);
        return VOS_FALSE;
    }

    /* 31.102,4.2.18�½ڣ�SIM���ļ����Ȳ�С��3��Я��MNC��Ҫ��С��4 */
    if (4 > pstIsimData->usDataLen)
    {
        TLPS_PRINT2LAYER_INFO(IMSA_DecodeIsimDomain_ENUM, 2);
        return VOS_FALSE;
    }

    /* ����ǲ��Կ��������ж�ֱ���˳� */
    if (PS_SUCC == LPS_OM_IsTestMode())
    {
        TLPS_PRINT2LAYER_INFO(IMSA_DecodeIsimDomain_ENUM, 3);
        return VOS_FALSE;
    }

    /* ȡ����Ӧλ�õĵ�4bit */
    ulImsiMncLen = pstIsimData->pData[3] & 0x0F;

    /* Э��涨MNC����Ч����ֻ����2��3 */
    if (( 2 != ulImsiMncLen ) && ( 3 != ulImsiMncLen))
    {
        /* ��ѧ��˵GU NASĬ��ֵΪ3����Ҫ��GU NAS����һ�� */
        ulImsiMncLen = 3;
    }
    else
    {
        ;
    }

    /* ��IMSIת����LMMʹ�õĸ�ʽ */

    /* ����IMSI��0�ֽ�(����)�͵�1�ֽڵĵ�4bit(У��λ)��������pucImsi[0]��pucImsi[1]�ĵ�4bit*/

    /* ��ȡMCC */
    /* ��1�ֽڵĸ�4bitΪMCC��1λ��������HPLMN��0���ֽڵĵ�4λ */
    aucPlmnId[0] |= ((ucImsi[1] & 0xF0) >> 4);

    /* ��2�ֽڵĵ�4bitΪMCC��2λ��������HPLMN��0���ֽڵĸ�4λ */
    aucPlmnId[0] |= ((ucImsi[2] & 0x0F) << 4);

    /* ��2�ֽڵĸ�4bitΪMCC��3λ��������HPLMN��1���ֽڵĵ�4λ */
    aucPlmnId[1] |= ((ucImsi[2] & 0xF0) >> 4);

    /* ��ȡMNC */
    /* ��3�ֽڵĵ�4bitΪMNC��1λ��������HPLMN��2���ֽڵĵ�4λ */
    aucPlmnId[2] |= (ucImsi[3] & 0x0F);

    /* ��3�ֽڵĸ�4bitΪMNC��2λ��������HPLMN��2���ֽڵĸ�4λ */
    aucPlmnId[2] |= (ucImsi[3] & 0xF0);

    /* ���MNC����Ϊ2����MNC��3λ����ΪF��Ҳ����HPLMN�ĵ�1�ֽڵĸ�4bit�������������MNC��3λ */
    if(2 == ulImsiMncLen)
    {
        aucPlmnId[1] |= 0xF0;
    }
    else
    {
        aucPlmnId[1] |= ((ucImsi[4] & 0x0F) << 4);
    }

    /* ��NV���ж��Ƿ����� */
    if (VOS_OK != IMSA_NV_Read(EN_NV_ID_VOLTE_CARD_LOCK,&stNvCardLock,\
                 sizeof(IMSA_NV_CARD_LOCK_STRU)))
    {
        TLPS_PRINT2LAYER_INFO(IMSA_DecodeIsimDomain_ENUM, 6);
        return VOS_TRUE;
    }

    /* �����������û�д򿪣���ֱ�ӷ��� */
    if (VOS_FALSE == stNvCardLock.ucEnableCardLockFlag)
    {
        TLPS_PRINT2LAYER_INFO(IMSA_DecodeIsimDomain_ENUM, 7);
        return VOS_TRUE;
    }

    /* ��������쳣����ֱ�ӷ��� */
    if (IMSA_NV_PLMN_LIST_LEN < stNvCardLock.ucPlmnNum || 0 == stNvCardLock.ucPlmnNum)
    {
        TLPS_PRINT2LAYER_INFO(IMSA_DecodeIsimDomain_ENUM, 8);
        return VOS_TRUE;
    }

    /* �����б� */
    for (i = 0 ; i < stNvCardLock.ucPlmnNum ; i ++)
    {
        /* ���PLMN�б�Ϊȫ0��ȫF������Ϊ�����쳣������ѭ�������ȫ���б��Ϊ�쳣ֵ������Ϊ������ */
        if ((stNvCardLock.astPlmnList[i].aucPlmnId[0] == 0 && stNvCardLock.astPlmnList[i].aucPlmnId[1] == 0 && stNvCardLock.astPlmnList[i].aucPlmnId[2] == 0)
         || (stNvCardLock.astPlmnList[i].aucPlmnId[0] == 0xFF && stNvCardLock.astPlmnList[i].aucPlmnId[1] == 0xFF && stNvCardLock.astPlmnList[i].aucPlmnId[2] == 0xFF))
        {
            TLPS_PRINT2LAYER_INFO(IMSA_DecodeIsimDomain_ENUM, 9);
            continue;
        }

        if (stNvCardLock.astPlmnList[i].aucPlmnId[0] == aucPlmnId[0]
         && stNvCardLock.astPlmnList[i].aucPlmnId[1] == aucPlmnId[1]
         && stNvCardLock.astPlmnList[i].aucPlmnId[2] == aucPlmnId[2])
        {
            /* ����ҵ�ƥ���PLMN���������ı�־��ΪFALSE���˳�ѭ�� */
            pstControlManager->ucIsCardLocked = VOS_FALSE;
            return VOS_TRUE;
        }
        else
        {
            /* ���PLMN��ƥ�䣬˵��PLMN�б��а����Ϸ���PLMN����¼��� */
            ucPlmnNotMatchflag = 1;
        }
    }

    if((i == stNvCardLock.ucPlmnNum)&&(ucPlmnNotMatchflag == 1))
    {
        /*�ߵ����˵����������֧��volte*/
        TLPS_PRINT2LAYER_INFO(IMSA_DecodeIsimDomain_ENUM, 10);

        pstControlManager->ucIsCardLocked = VOS_TRUE;
    }

    return VOS_TRUE;
}
/*zhaochen 00308719 end for card lock 2015-10-31*/

/*****************************************************************************
 Function Name  : IMSA_DecodeIsimImpu()
 Description    : IMPU����
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-27  Draft Enact
*****************************************************************************/
VOS_UINT32  IMSA_EncodeIsimFile(const IMSA_ISIM_DATA_STRU *pstIsimData)
{
    (VOS_VOID)pstIsimData;

    return 0;
}
/*lint -e732*/
/*lint -e718*/
/*lint -e516*/
/*****************************************************************************
 Function Name  : IMSA_ReadImsaNvImsRatSupportConfig()
 Description    : ��ȡ��ͬ���뼼����IMS��֧��������Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-27  Draft Enact
*****************************************************************************/
VOS_VOID  IMSA_ReadImsaNvImsRatSupportConfig( VOS_VOID)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;
    IMSA_NV_IMS_RAT_SUPPORT_STRU    stNvImsRatSupport;
    VOS_UINT32                      ulRslt;

    pstControlManager = IMSA_GetControlManagerAddress();

    ulRslt = IMSA_NV_Read(EN_NV_ID_IMS_RAT_SUPPORT,&stNvImsRatSupport,\
                 sizeof(IMSA_NV_IMS_RAT_SUPPORT_STRU));

    if(ulRslt == VOS_OK)
    {
        /*����NV��������*/
        pstControlManager->stImsaConfigPara.ucGsmEmsSupportFlag = stNvImsRatSupport.ucGsmEmsSupportFlag;
        pstControlManager->stImsaConfigPara.ucGsmImsSupportFlag = stNvImsRatSupport.ucGsmImsSupportFlag;
        pstControlManager->stImsaConfigPara.ucUtranEmsSupportFlag= stNvImsRatSupport.ucUtranEmsSupportFlag;
        pstControlManager->stImsaConfigPara.ucUtranImsSupportFlag= stNvImsRatSupport.ucUtranImsSupportFlag;
        pstControlManager->stImsaConfigPara.ucLteEmsSupportFlag= stNvImsRatSupport.ucLteEmsSupportFlag;
        pstControlManager->stImsaConfigPara.ucLteImsSupportFlag= stNvImsRatSupport.ucLteImsSupportFlag;
        pstControlManager->stImsaConfigPara.ucRoamingImsNotSupportFlag = stNvImsRatSupport.ucRoamingImsNotSupportFlag;
    }
    else
    {
        IMSA_WARN_LOG("IMSA_ReadImsaNvImsRatSupportConfig: read NV err!");

        /*���ó�ʼֵ*/
        pstControlManager->stImsaConfigPara.ucGsmEmsSupportFlag = VOS_FALSE;
        pstControlManager->stImsaConfigPara.ucGsmImsSupportFlag = VOS_FALSE;
        pstControlManager->stImsaConfigPara.ucUtranEmsSupportFlag= VOS_FALSE;
        pstControlManager->stImsaConfigPara.ucUtranImsSupportFlag= VOS_FALSE;
        pstControlManager->stImsaConfigPara.ucLteEmsSupportFlag= VOS_FALSE;
        pstControlManager->stImsaConfigPara.ucLteImsSupportFlag= VOS_TRUE;
        /* ���������²�����IMSע�Ṧ�ܣ�Ĭ�Ϲر� */
        pstControlManager->stImsaConfigPara.ucRoamingImsNotSupportFlag = VOS_FALSE;
    }

}

/* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */
/*****************************************************************************
 Function Name  : IMSA_ReadImsaNvHifiControlConfig()
 Description    : ��ȡHIFI���ؿ���������Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719   2015-11-18  Draft Enact
*****************************************************************************/
VOS_VOID  IMSA_ReadImsaNvHifiControlConfig( VOS_VOID)
{
    IMSA_HIFI_DATA_MANAGER_STRU        *pstHifiDataManager;
    IMSA_COMM_PARA_CONFIG_STRU          stNvImsaConfig;
    VOS_UINT32                          ulRslt;

    pstHifiDataManager = IMSA_GetHifiDataManagerAddress();

    /* ��NV */

    ulRslt = IMSA_NV_Read(EN_NV_ID_IMSA_COMM_PARA_CONFIG,&stNvImsaConfig,\
                 sizeof(IMSA_COMM_PARA_CONFIG_STRU));

    if(VOS_OK == ulRslt)
    {
        /* ����NV���� */
        pstHifiDataManager->ucHifiDataControlFlag = stNvImsaConfig.ucHifiDataControlFlag;
        pstHifiDataManager->ucHifiDataNeedAckNum  = stNvImsaConfig.ucHifiDataNeedAckNum;
        pstHifiDataManager->ucHifiDatMaxBufferNum = stNvImsaConfig.ucHifiDatMaxBufferNum;
    }
    else
    {
        IMSA_WARN_LOG("IMSA_ReadImsaNvHifiControlConfig: read NV err!");

        /* ���ó�ʼֵ */
        pstHifiDataManager->ucHifiDataControlFlag = VOS_TRUE;
        pstHifiDataManager->ucHifiDataNeedAckNum  = 5;
        pstHifiDataManager->ucHifiDatMaxBufferNum = 25;
    }

    return;
}
/* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */


VOS_VOID  IMSA_ReadImsaNvImsaConfig( VOS_VOID)
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlManager;
    IMSA_REG_MANAGER_STRU              *pstImsaRegManager   = IMSA_RegCtxGet();
    IMSA_NV_IMSA_CONFIG_STRU            stNvImsaConfig;
    VOS_UINT32                          ulRslt;

    pstControlManager = IMSA_GetControlManagerAddress();

    ulRslt = IMSA_NV_Read(EN_NV_ID_IMSA_CONFIG,&stNvImsaConfig,\
                 sizeof(IMSA_NV_IMSA_CONFIG_STRU));

    if(ulRslt == VOS_OK)
    {
        /*����NV��������*/
        pstControlManager->stImsaConfigPara.ucNoCardEmcCallSupportFlag
                    = stNvImsaConfig.ucNoCardEmcCallSupportFlag;
        pstControlManager->stImsaConfigPara.ucImsLocDeregSigPdpRelFlag
                    = stNvImsaConfig.ucImsLocDeregSigPdpRelFlag;
        pstControlManager->stImsaConfigPara.ucUeRelMediaPdpFLag
                    = stNvImsaConfig.ucUeRelMediaPdpFLag;
        pstImsaRegManager->ulMaxTime    = stNvImsaConfig.ulMaxTime;
        pstImsaRegManager->ulBaseTime   = stNvImsaConfig.ulBaseTime;
        pstImsaRegManager->ulRetryPeriod= stNvImsaConfig.ulRegFailRetryIntervel;
        pstImsaRegManager->ulSaveRetryTimes = stNvImsaConfig.ucRetryTimes;
        pstControlManager->stImsaConfigPara.stCMCCCustomReq.ucCMCCCustomDeregFlag
                    = stNvImsaConfig.stCMCCCustomReq.ucCMCCCustomDeregFlag;
        pstControlManager->stImsaConfigPara.stCMCCCustomReq.ucCMCCCustomTcallFlag
                    = stNvImsaConfig.stCMCCCustomReq.ucCMCCCustomTcallFlag;
        pstControlManager->stImsaConfigPara.stCMCCCustomReq.ucCMCCCustomTqosFlag
                    = stNvImsaConfig.stCMCCCustomReq.ucCMCCCustomTqosFlag;

        /* ������ƶ����ƿ��ش򿪣���TCALL��ʱ������NV���õ�ʱ��������TCALLʱ������Ϊ5s */
        if (VOS_TRUE == pstControlManager->stImsaConfigPara.stCMCCCustomReq.ucCMCCCustomTcallFlag)
        {
            pstControlManager->stImsaConfigPara.stCMCCCustomReq.ulTcallTimerLen
                        = stNvImsaConfig.stCMCCCustomReq.ulTcallTimerLen;
        }
        else
        {
            pstControlManager->stImsaConfigPara.stCMCCCustomReq.ulTcallTimerLen = 5000;
        }
        pstControlManager->stImsaConfigPara.stCMCCCustomReq.ulTqosTimerLen
                    = stNvImsaConfig.stCMCCCustomReq.ulTqosTimerLen;
        IMSA_MEM_CPY(   &pstControlManager->stImsaConfigPara.stImsRedialCfg,
                        &stNvImsaConfig.stImsRedialCfg,
                        sizeof(IMSA_NV_IMS_REDIAL_CFG_STRU));
        pstImsaRegManager->stNormalRegEntity.stProtectTimer.ulTimerLen = stNvImsaConfig.ulRegTimerLen;
        pstImsaRegManager->stEmcRegEntity.stProtectTimer.ulTimerLen = stNvImsaConfig.ulRegTimerLen;
    }
    else
    {
        IMSA_WARN_LOG("IMSA_ReadImsaNvImsaConfig: read NV err!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ReadImsaNvImsaConfig_ENUM, IMSA_CALL_API_ERROR);

        /*���ó�ʼֵ*/
        pstControlManager->stImsaConfigPara.ucNoCardEmcCallSupportFlag
                    = VOS_FALSE;
        pstControlManager->stImsaConfigPara.ucImsLocDeregSigPdpRelFlag
                    = VOS_TRUE;
        pstControlManager->stImsaConfigPara.ucUeRelMediaPdpFLag
                    = VOS_FALSE;
        pstImsaRegManager->ulMaxTime    = 1800;
        pstImsaRegManager->ulBaseTime   = 30;
        pstImsaRegManager->ulRetryPeriod= 0;
        pstControlManager->stImsaConfigPara.stCMCCCustomReq.ucCMCCCustomDeregFlag = VOS_FALSE;
        pstControlManager->stImsaConfigPara.stCMCCCustomReq.ucCMCCCustomTcallFlag = VOS_FALSE;
        pstControlManager->stImsaConfigPara.stCMCCCustomReq.ucCMCCCustomTqosFlag = VOS_FALSE;
        pstControlManager->stImsaConfigPara.stCMCCCustomReq.ulTcallTimerLen = 10000;
        pstControlManager->stImsaConfigPara.stCMCCCustomReq.ulTqosTimerLen = 2000;
        IMSA_MEM_SET(   &pstControlManager->stImsaConfigPara.stImsRedialCfg,
                        0,
                        sizeof(IMSA_NV_IMS_REDIAL_CFG_STRU));
    }
}
VOS_VOID  IMSA_ReadImsaNvImsCapability( VOS_VOID)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;
    IMS_NV_IMS_CAP_STRU             stNvImsCapability;
    VOS_UINT32                      ulRslt;

    pstControlManager = IMSA_GetControlManagerAddress();

    ulRslt = IMSA_NV_Read(EN_NV_ID_IMS_CAPABILITY,&stNvImsCapability,\
                 sizeof(IMS_NV_IMS_CAP_STRU));

    if(ulRslt == VOS_OK)
    {
        /*����NV��������*/
        pstControlManager->stImsaConfigPara.ucVoiceCallOnImsSupportFlag
                    = stNvImsCapability.ucVoiceCallOnImsSupportFlag;
        pstControlManager->stImsaConfigPara.ucVideoCallOnImsSupportFlag
                    = stNvImsCapability.ucVideoCallOnImsSupportFlag;
        pstControlManager->stImsaConfigPara.ucSmsOnImsSupportFlag
                    = stNvImsCapability.ucSmsOnImsSupportFlag;
        pstControlManager->stImsaConfigPara.ucSrvccOnImsSupportFlag
                    = stNvImsCapability.ucSrvccOnImsSupportFlag;
        pstControlManager->stImsaConfigPara.ucSrvccMidCallOnImsSupportFlag
                    = stNvImsCapability.ucSrvccMidCallOnImsSupportFlag;
        pstControlManager->stImsaConfigPara.ucSrvccAlertingOnImsSupportFlag
                    = stNvImsCapability.ucSrvccAlertingOnImsSupportFlag;
        pstControlManager->stImsaConfigPara.ucSrvccPreAlertingOnImsSupportFlag
                    = stNvImsCapability.ucSrvccPreAlertingOnImsSupportFlag;
        pstControlManager->stImsaConfigPara.ucSrvccTiFlag
                    = stNvImsCapability.ucSrvccTiFlag;
    }
    else
    {
        IMSA_WARN_LOG("IMSA_ReadImsaNvImsCapability: read NV err!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ReadImsaNvImsCapability_ENUM, IMSA_CALL_API_ERROR);

        /*���ó�ʼֵ*/
        pstControlManager->stImsaConfigPara.ucVoiceCallOnImsSupportFlag
                    = VOS_TRUE;
        pstControlManager->stImsaConfigPara.ucVideoCallOnImsSupportFlag
                    = VOS_FALSE;
        pstControlManager->stImsaConfigPara.ucSmsOnImsSupportFlag
                    = VOS_TRUE;
        pstControlManager->stImsaConfigPara.ucSrvccOnImsSupportFlag
                    = VOS_TRUE;
        pstControlManager->stImsaConfigPara.ucSrvccMidCallOnImsSupportFlag
                    = VOS_TRUE;
        pstControlManager->stImsaConfigPara.ucSrvccAlertingOnImsSupportFlag
                    = VOS_TRUE;
        pstControlManager->stImsaConfigPara.ucSrvccPreAlertingOnImsSupportFlag
                    = VOS_FALSE;
        pstControlManager->stImsaConfigPara.ucSrvccTiFlag
                    = VOS_TRUE;
    }

}



VOS_VOID  IMSA_ReadImsaNvSipPortConfig( VOS_VOID)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;
    IMSA_NV_SIP_PORT_CONFIG_STRU    stNvSipPort;
    VOS_UINT32                      ulRslt;

    pstControlManager = IMSA_GetControlManagerAddress();

    ulRslt = IMSA_NV_Read(EN_NV_ID_SIP_PORT_CONFIG,&stNvSipPort,\
                 sizeof(IMSA_NV_SIP_PORT_CONFIG_STRU));

    if ((ulRslt == VOS_OK)
        && (stNvSipPort.usImsMaxPort >= stNvSipPort.usImsMinPort))
    {
        /*����NV��������*/
        pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMinPort
                    = stNvSipPort.usImsMinPort;
        pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMaxPort
                    = stNvSipPort.usImsMaxPort;

    }
    else
    {
        IMSA_WARN_LOG("IMSA_ReadImsaNvSipPortConfig: read NV err!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ReadImsaNvSipPortConfig_ENUM, IMSA_CALL_API_ERROR);

        /*���ó�ʼֵ*/
        pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMinPort = 5000;
        pstControlManager->stImsaConfigPara.stImsPortConfig.usImsMaxPort = 32000;
        /*IMSA_MEM_SET(&pstControlManager->stImsaConfigPara.stImsPortConfig,
                     0, sizeof(IMSA_IMS_PORT_CONFIG_STRU));*/
    }

}


VOS_VOID  IMSA_ReadImsaNvImsConfig( VOS_VOID)
{
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;
    IMSA_NV_IMS_CONFIG_STRU         stNvImsConfig;
    VOS_UINT32                      ulRslt;

    pstControlManager = IMSA_GetControlManagerAddress();

    ulRslt = IMSA_NV_Read(EN_NV_ID_IMS_CONFIG,&stNvImsConfig,\
                 sizeof(IMSA_NV_IMS_CONFIG_STRU));

    if(ulRslt == VOS_OK)
    {
        /*����NV��������*/
        pstControlManager->stImsaConfigPara.ucUserInfoFlag
                = stNvImsConfig.ucUserInfoFlag;

        pstControlManager->stImsaConfigPara.ucAuthType
                = stNvImsConfig.ucAuthType;
        IMSA_MEM_CPY(pstControlManager->stImsaConfigPara.aucPassWord,
                stNvImsConfig.aucPassWord, IMSA_PASSWORD_LEN);

        if (VOS_TRUE == stNvImsConfig.ucUserInfoFlag)
        {

            pstControlManager->stImsaCommonInfo.stImsaUeId.bitOpImpi = IMSA_OP_TRUE;
            IMSA_MEM_CPY(pstControlManager->stImsaCommonInfo.stImsaUeId.stImpi.acImpi,
                    stNvImsConfig.acImpi, IMSA_IMPI_LEN);

            pstControlManager->stImsaCommonInfo.stImsaUeId.bitOpTImpu = IMSA_OP_TRUE;
            IMSA_MEM_CPY(pstControlManager->stImsaCommonInfo.stImsaUeId.stTImpu.acTImpu,
                    stNvImsConfig.acTImpu, IMSA_IMPU_LEN);

            pstControlManager->stImsaCommonInfo.bitOpHomeNetDomainName = IMSA_OP_TRUE;
            IMSA_MEM_CPY(pstControlManager->stImsaCommonInfo.stHomeNetDomainName.acHomeNetDomainName,
                    stNvImsConfig.acHomeNetDomainName, IMSA_HOME_NET_DOMAIN_NAME_LEN);
        }


    }
    else
    {
        IMSA_WARN_LOG("IMSA_ReadImsaNvImsConfig: read NV err!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ReadImsaNvImsConfig_ENUM, IMSA_CALL_API_ERROR);

        /*���ó�ʼֵ*/
        pstControlManager->stImsaConfigPara.ucUserInfoFlag = VOS_FALSE;

        pstControlManager->stImsaConfigPara.ucAuthType = VOS_FALSE;

        IMSA_MEM_SET(pstControlManager->stImsaConfigPara.aucPassWord,
                0, IMSA_PASSWORD_LEN);

    }

}


VOS_VOID  IMSA_ReadImei( VOS_VOID )
{
    IMSA_COMMON_INFO_STRU          *pstCommInfo;
    VOS_UINT8                       aucBuf[NV_ITEM_IMEI_SIZE] = {0};
    VOS_UINT32                      i = 0;

    /* ����SC�ӿڶ�ȡIMEI���� */
    if (SC_ERROR_CODE_NO_ERROR != SC_PERS_NvRead(   MODEM_ID_0,
                                                    en_NV_Item_IMEI,
                                                    aucBuf,
                                                    NV_ITEM_IMEI_SIZE))
    {
        IMSA_WARN_LOG("IMSA_ReadImei: Read IMEI from NV fail!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ReadImei_ENUM, IMSA_CALL_API_ERROR);

        aucBuf[0] = 0x3;
        aucBuf[1] = 0x5;
        aucBuf[2] = 0x6;
        aucBuf[3] = 0x6;
        aucBuf[4] = 0x2;
        aucBuf[5] = 0x6;
        aucBuf[6] = 0x0;
        aucBuf[7] = 0x0;
        aucBuf[8] = 0x7;
        aucBuf[9] = 0x7;
        aucBuf[10] = 0x3;
        aucBuf[11] = 0x1;
        aucBuf[12] = 0x7;
        aucBuf[13] = 0x4;
        aucBuf[14] = 0x0;
    }

    pstCommInfo = IMSA_GetCommonInfoAddress();
    pstCommInfo->stImsaUeId.bitOpImei  = IMSA_OP_TRUE;

    /* ��NV�и�ʽת��ΪIMSA�ڲ�IMEI��Ÿ�ʽ */
    for (i = 0; i < IMSA_IMS_IMEI_LEN; i++)
    {
        pstCommInfo->stImsaUeId.acImei[i] = IMSA_ConverterDigit2Chacter(aucBuf[i]);
    }
    pstCommInfo->stImsaUeId.acImei[IMSA_IMS_IMEI_LEN-1] = 0x30;
    pstCommInfo->stImsaUeId.acImei[IMSA_IMS_IMEI_LEN] = '\0';
}


VOS_VOID  IMSA_ReadNvVoiceDomain(VOS_VOID )
{

    LNAS_LMM_NV_VOICE_DOMAIN_STRU   stNvVoiceDomain;
    IMSA_CONTROL_MANAGER_STRU      *pstControlManager;
    VOS_UINT32                      ulRslt;

    pstControlManager = IMSA_GetControlManagerAddress();

    ulRslt = IMSA_NV_Read(EN_NV_ID_UE_VOICE_DOMAIN,&stNvVoiceDomain,\
                 sizeof(LNAS_LMM_NV_VOICE_DOMAIN_STRU));

    /*NV����׼ȷ*/
    if((VOS_OK == ulRslt) && (stNvVoiceDomain.bitOpVoicDomain == 1))
    {
        switch(stNvVoiceDomain.enVoicDomain)
        {
            case NAS_LMM_VOICE_DOMAIN_CS_ONLY:
                pstControlManager->stImsaConfigPara.enVoiceDomain = IMSA_VOICE_DOMAIN_CS_ONLY;
                break;

            case NAS_LMM_VOICE_DOMAIN_IMS_PS_ONLY:
                pstControlManager->stImsaConfigPara.enVoiceDomain = IMSA_VOICE_DOMAIN_IMS_PS_ONLY;
                break;

            case NAS_LMM_VOICE_DOMAIN_CS_PREFERRED:
                pstControlManager->stImsaConfigPara.enVoiceDomain = IMSA_VOICE_DOMAIN_CS_PREFERRED;
                break;

            case NAS_LMM_VOICE_DOMAIN_IMS_PS_PREFERRED:
                pstControlManager->stImsaConfigPara.enVoiceDomain = IMSA_VOICE_DOMAIN_IMS_PS_PREFERRED;
                break;

            default:
                IMSA_WARN_LOG("IMSA_ReadNvVoiceDomain: Para is err!");
                TLPS_PRINT2LAYER_WARNING(IMSA_ReadNvVoiceDomain_ENUM, LNAS_PARAM_INVALID);
                pstControlManager->stImsaConfigPara.enVoiceDomain = IMSA_VOICE_DOMAIN_IMS_PS_PREFERRED;
                break;
        }
    }
    else
    {
        IMSA_WARN_LOG("IMSA_ReadNvVoiceDomain: read NV err.");
        TLPS_PRINT2LAYER_WARNING(IMSA_ReadNvVoiceDomain_ENUM, IMSA_CALL_API_ERROR);

        pstControlManager->stImsaConfigPara.enVoiceDomain = IMSA_VOICE_DOMAIN_IMS_PS_PREFERRED;
    }

    return;
}
VOS_VOID IMSA_ReadPcscfDiscoveryPolicy(VOS_VOID)
{
    IMSA_CONTROL_MANAGER_STRU                   *pstControlManager;
    IMSA_NV_PCSCF_DISCOVERY_POLICY_STRU         stPcscfPolicy;
    VOS_UINT32                                  ulRslt;

    pstControlManager = IMSA_GetControlManagerAddress();

    ulRslt = IMSA_NV_Read(EN_NV_ID_PCSCF_DISCOVERY_POLICY,&stPcscfPolicy,\
                 sizeof(IMSA_NV_PCSCF_DISCOVERY_POLICY_STRU));

    if (VOS_OK == ulRslt)
    {
        if ((IMSA_PCSCF_DISCOVERY_POLICY_PCO == stPcscfPolicy.enPcscfDiscoverPolicy) ||
            (IMSA_PCSCF_DISCOVERY_POLICY_NV == stPcscfPolicy.enPcscfDiscoverPolicy))
        {
            pstControlManager->stPcscfDiscoveryPolicyInfo.enPcscfDiscoverPolicy
                = stPcscfPolicy.enPcscfDiscoverPolicy;

            IMSA_MEM_CPY(&pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv4Pcscf,
                         &stPcscfPolicy.stIpv4Pcscf, sizeof(IMSA_NV_PDP_IPV4_PCSCF_STRU));

            IMSA_MEM_CPY(&pstControlManager->stPcscfDiscoveryPolicyInfo.stIpv6Pcscf,
                &stPcscfPolicy.stIpv6Pcscf, sizeof(IMSA_NV_PDP_IPV6_PCSCF_STRU));
        }
        else
        {
            pstControlManager->stPcscfDiscoveryPolicyInfo.enPcscfDiscoverPolicy
                = IMSA_PCSCF_DISCOVERY_POLICY_PCO;
        }
    }
    else
    {
        IMSA_WARN_LOG("IMSA_ReadPcscfDiscoveryPolicy: read NV err.");
        TLPS_PRINT2LAYER_WARNING(IMSA_ReadPcscfDiscoveryPolicy_ENUM, IMSA_CALL_API_ERROR);

        pstControlManager->stPcscfDiscoveryPolicyInfo.enPcscfDiscoverPolicy
                = IMSA_PCSCF_DISCOVERY_POLICY_PCO;
    }

    return;
}


VOS_VOID IMSA_ReadNvIpv6FallBackExtCause(VOS_VOID)
{
    IMSA_CONN_MANAGER_STRU              *pstConnManager;
    TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU stNvFallBackExtCause;
    VOS_UINT32                          ulCauseNum = 0;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulCnt;

    pstConnManager  =  IMSA_CONN_GetConnManagerAddr();

    ulRslt = IMSA_NV_Read(en_NV_Item_IPV6_BACKPROC_EXT_CAUSE,&stNvFallBackExtCause,\
                 sizeof(TAF_NV_IPV6_FALLBACK_EXT_CAUSE_STRU));

    if ((VOS_OK == ulRslt) && (VOS_TRUE == stNvFallBackExtCause.ulActiveFlag))
    {
        for (ulCnt = 0 ; ulCnt < TAF_NV_IPV6_FALLBACK_EXT_CAUSE_MAX_NUM; ulCnt++)
        {
            if (!TAF_PS_IS_SM_CAUSE_VALID(stNvFallBackExtCause.aucSmCause[ulCnt]))
            {
                continue;
            }
            else
            {
                pstConnManager->stIpv6FallBackExtCause.aenPsCause[ulCauseNum] = TAF_PS_CONVERT_SM_CAUSE_TO_PS_CAUSE(stNvFallBackExtCause.aucSmCause[ulCnt]);
                ulCauseNum++;
            }
        }

        pstConnManager->stIpv6FallBackExtCause.ulCauseNum = ulCauseNum;
    }
    else
    {
        IMSA_WARN_LOG("IMSA_ReadNvIpv6FallBackExtCause: read NV err.");
        TLPS_PRINT2LAYER_WARNING(IMSA_ReadNvIpv6FallBackExtCause_ENUM, IMSA_CALL_API_ERROR);
    }
}


/*****************************************************************************
 Function Name  : IMSA_ReadImsaNV()
 Description    : ��ȡNV��Ϣ��������Ϣ��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ReadImsaNV(VOS_VOID)
{
    IMSA_ReadImsaNvImsRatSupportConfig();

    IMSA_ReadImsaNvImsaConfig();

    IMSA_ReadImsaNvImsCapability();

    IMSA_ReadImsaNvSipPortConfig();

    IMSA_ReadImsaNvImsConfig();

    /*��ȡIMEI*/
    IMSA_ReadImei();

    IMSA_ReadNvVoiceDomain();

    IMSA_ReadPcscfDiscoveryPolicy();

    IMSA_ReadNvIpv6FallBackExtCause();

    /* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */
    IMSA_ReadImsaNvHifiControlConfig();
    /* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */
}

/*****************************************************************************
 Function Name  : IMSA_ReadIsimFile()
 Description    : ��ȡ���ļ���Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing     49683      2013-06-24  Draft Enact
      2.zhaochen    00308719   2015-02-10  USIM interface modify
*****************************************************************************/
VOS_VOID IMSA_ReadIsimFile(VOS_VOID)
{
    VOS_CHAR                         *cPathStr;
    VOS_UINT8                        ucRecordNum;
    USIMM_FILEPATH_INFO_STRU         stGetFilePath = {0};

    /*����USIM�ṩ�Ľӿڣ���FILE IDת��Ϊ�ļ�·��*/
    /*���ת���Ƿ�ɹ�*/
    if (VOS_OK != USIMM_ChangeDefFileToPath(USIMM_ISIM_EFIMPI_ID, &cPathStr))
    {
        IMSA_WARN_LOG("IMSA_ReadIsimFile: ChangeDefFileToPath err.");
        TLPS_PRINT2LAYER_WARNING(IMSA_ReadIsimFile_ENUM, IMSA_CALL_API_ERROR);
        return;
    }
    stGetFilePath.ulPathLen = VOS_StrLen(cPathStr);
    IMSA_MEM_CPY(stGetFilePath.acPath, cPathStr, stGetFilePath.ulPathLen);
    /*��ȡ��ѡ�ļ�*/
    ucRecordNum  = 1;
    IMSA_SndUsimReadFileReq(USIMM_IMS_APP, \
                            ucRecordNum, \
                            0, \
                            &stGetFilePath);

    /*����USIM�ṩ�Ľӿڣ���FILE IDת��Ϊ�ļ�·��*/
    /*���ת���Ƿ�ɹ�*/
    if (VOS_OK != USIMM_ChangeDefFileToPath(USIMM_ISIM_EFDOMAIN_ID, &cPathStr))
    {
        IMSA_WARN_LOG("IMSA_ReadIsimFile: ChangeDefFileToPath err.");
        TLPS_PRINT2LAYER_WARNING(IMSA_ReadIsimFile_ENUM, IMSA_CALL_API_ERROR);
        return;
    }
    stGetFilePath.ulPathLen = VOS_StrLen(cPathStr);
    IMSA_MEM_CPY(stGetFilePath.acPath, cPathStr, stGetFilePath.ulPathLen);
    /*��ȡ��ѡ�ļ�*/
    ucRecordNum  = 1;
    IMSA_SndUsimReadFileReq(USIMM_IMS_APP, \
                            ucRecordNum, \
                            0, \
                            &stGetFilePath);

    /*����USIM�ṩ�Ľӿڣ���FILE IDת��Ϊ�ļ�·��*/
    /*���ת���Ƿ�ɹ�*/
    if (VOS_OK != USIMM_ChangeDefFileToPath(USIMM_ISIM_EFIMPU_ID, &cPathStr))
    {
        IMSA_WARN_LOG("IMSA_ReadIsimFile: ChangeDefFileToPath err.");
        TLPS_PRINT2LAYER_WARNING(IMSA_ReadIsimFile_ENUM, IMSA_CALL_API_ERROR);
        return;
    }
    stGetFilePath.ulPathLen = VOS_StrLen(cPathStr);
    IMSA_MEM_CPY(stGetFilePath.acPath, cPathStr, stGetFilePath.ulPathLen);
    /*��ȡ��ѡ�ļ�*/
    ucRecordNum  = 1;
    IMSA_SndUsimReadFileReq(USIMM_IMS_APP, \
                            ucRecordNum, \
                            0, \
                            &stGetFilePath);

    /*zhaochen 00308719 begin for card lock 2015-10-31*/
    /*��ȡMNC����*/
    /*��FileIDת��Ϊ�ļ�·��*/
    if (VOS_OK != USIMM_ChangeDefFileToPath(USIMM_USIM_EFAD_ID, &cPathStr))
    {
        IMSA_WARN_LOG("IMSA_ReadIsimFile: ChangeDefFileToPath err.");
        TLPS_PRINT2LAYER_WARNING(IMSA_ReadIsimFile_ENUM, IMSA_CALL_API_ERROR);
        return;
    }

    stGetFilePath.ulPathLen = strlen(cPathStr);
    IMSA_MEM_CPY(stGetFilePath.acPath, cPathStr, stGetFilePath.ulPathLen);

    /*���Ͷ�USIM�ļ�����Ϣ*/
    IMSA_SndUsimReadFileReq(USIMM_GUTL_APP, ucRecordNum, 0, &stGetFilePath);
    /*zhaochen 00308719 end for card lock 2015-10-31*/

}



VOS_UINT32 IMSA_AllocImsOpId(VOS_VOID)
{
    do
    {
        gulImsaImsOpId++;
    } while(0 == gulImsaImsOpId);

    IMSA_INFO_LOG1("IMSA_AllocImsOpId: ", gulImsaImsOpId);
    TLPS_PRINT2LAYER_INFO1(IMSA_AllocImsOpId_ENUM, IMSA_NORMAL_OPID, gulImsaImsOpId);

    return gulImsaImsOpId;
}


VOS_VOID IMSA_ResetImsOpId(VOS_VOID)
{
    gulImsaImsOpId = 0;
}


VOS_UINT32 IMSA_GetImsOpId(VOS_VOID)
{
    return gulImsaImsOpId;
}


VOS_UINT8 IMSA_AllocUsimOpId(VOS_VOID)
{
    /* ��gucImsaUsimOpId�ĵڰ�λ���ֵ�ǰ����ͨ��Ȩ���ǽ�����Ȩ�����Խ��õ�0~6λ��
    ����OPID�������ǰOPIDֵΪ0x7Fʱ����ת */
    if (IMSA_USIM_MAX_OPID > gucImsaUsimOpId)
    {
        gucImsaUsimOpId++;
    }
    else
    {
        gucImsaUsimOpId = 0;
        gucImsaUsimOpId ++;
    }

    IMSA_INFO_LOG1("IMSA_AllocUsimOpId: ", gucImsaUsimOpId);
    TLPS_PRINT2LAYER_INFO1(IMSA_AllocUsimOpId_ENUM, IMSA_NORMAL_OPID, gulImsaImsOpId);

    return gucImsaUsimOpId;
}


VOS_VOID IMSA_ResetUsimOpId(VOS_VOID)
{
    gucImsaUsimOpId = 0;
}


VOS_UINT8 IMSA_GetUsimOpId(VOS_VOID)
{
    return gucImsaUsimOpId;
}


VOS_VOID IMSA_SaveRcvImsNormOpid(VOS_UINT32 ulImsOpid)
{
    gulImsaRcvImsNormOpId = ulImsOpid;
}


VOS_UINT32 IMSA_GetRcvImsNormOpid(VOS_VOID)
{
    return gulImsaRcvImsNormOpId;
}

VOS_VOID IMSA_SaveRcvImsEmcOpid(VOS_UINT32 ulImsOpid)
{
    gulImsaRcvImsEmcOpId = ulImsOpid;
}


VOS_UINT32 IMSA_GetRcvImsEmcOpid(VOS_VOID)
{
    return gulImsaRcvImsEmcOpId;
}

/*****************************************************************************
 Function Name  : IMSA_ProcIsimStatusInd()
 Description    : ����ISIM��״ָ̬ʾ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-06-24  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcIsimStatusInd(const VOS_VOID *pRcvMsg)
{
    USIMM_CARDSTATUS_IND_STRU *pstIsimStatusInd;
    IMSA_CONTROL_MANAGER_STRU *pstControlManager;

    pstIsimStatusInd = (USIMM_CARDSTATUS_IND_STRU*)pRcvMsg;

    if((pstIsimStatusInd->stIsimInfo).enCardType != USIMM_CARD_ISIM)
    {
        /*��ISIM��Ϣ*/
        IMSA_WARN_LOG("IMSA_ProcIsimStatusInd: not ISIM!");
        TLPS_PRINT2LAYER_INFO1(IMSA_ProcIsimStatusInd_ENUM, IMSA_NORMAL_OPID, gulImsaImsOpId);

        return;
    }

    pstControlManager = IMSA_GetControlManagerAddress();

    /*����λ����*/
    if((pstIsimStatusInd->stIsimInfo).enCardService == USIMM_CARD_SERVIC_AVAILABLE)
    {
        /*��ǰ��״̬����λ�����ѿ������������Ϣ*/
        if((pstControlManager->enImsaIsimStatus == IMSA_ISIM_STATUS_ABSENT)
            &&(pstControlManager->enImsaStatus != IMSA_STATUS_NULL))
        {
            IMSA_ReadIsimFile();
        }

        /*���¿�״̬*/
        pstControlManager->enImsaIsimStatus = IMSA_ISIM_STATUS_AVAILABLE;
    }
    else/*������λ*/
    {
        /*���¿�״̬��ɾ�����ļ���Ϣ*/
        pstControlManager->enImsaIsimStatus = IMSA_ISIM_STATUS_ABSENT;
        pstControlManager->stImsaCommonInfo.bitOpHomeNetDomainName = 0;
        pstControlManager->stImsaCommonInfo.stImsaUeId.bitOpImpi   = 0;
        pstControlManager->stImsaCommonInfo.stImsaUeId.bitOpTImpu  = 0;

        (VOS_VOID)vos_printf("IMSA_ProcIsimStatusInd: card isnot avail");
    }

}

/*****************************************************************************
 Function Name  : IMSA_ProcIsimRefreshInd()
 Description    : ����ISIM���ļ�ˢ��ָʾ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-31  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcIsimRefreshInd(const VOS_VOID *pRcvMsg)
{
    /*�����ļ�ˢ�����󣬲�ʵ��*/
    (VOS_VOID)pRcvMsg;
}


/*****************************************************************************
 Function Name  : IMSA_SndD2AuthSyncFailure()
 Description    : ����ISIM����Ȩͬ��ʧ����Ϣ
 Input          : pstIMSCnf   ����Ȩ���
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-17  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndD2AuthSyncFailure
(
    const USIMM_IMS_AUTH_CNF_STRU      *pstIMSCnf,
    VOS_UINT32                          ulIsEmergencyAuth
)

{

    IMSA_IMS_INPUT_EVENT_STRU   *pstHiInputEvent;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstHiInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstHiInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndD2AuthSyncFailure:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndD2AuthSyncFailure_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstHiInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstHiInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_SERVICE;

    if (IMSA_TRUE == ulIsEmergencyAuth)
    {
        pstHiInputEvent->evt.stInputServiceEvent.ulOpId = IMSA_GetRcvImsEmcOpid();
        pstHiInputEvent->evt.stInputServiceEvent.enInputServeReason = IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_SYNC_FAILURE_EMERGENCY;
    }
    else
    {
        pstHiInputEvent->evt.stInputServiceEvent.ulOpId = IMSA_GetRcvImsNormOpid();
        pstHiInputEvent->evt.stInputServiceEvent.enInputServeReason = IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_SYNC_FAILURE;
    }

    pstHiInputEvent->evt.stInputServiceEvent.bitOpAka = IMSA_OP_TRUE;

    /*SYNC������д*/
    IMSA_MEM_CPY(pstHiInputEvent->evt.stInputServiceEvent.stAka.aucAuts,
                 &pstIMSCnf->aucAuts[1],
                 pstIMSCnf->aucAuts[0]);

    IMSA_SndImsMsgServiceEvent(pstHiInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstHiInputEvent);

}
VOS_VOID IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo
(
    IMSA_IMS_INPUT_SERVICE_REASON_ENUM_UINT32   enInputServeReason
)
{
    IMSA_IMS_INPUT_EVENT_STRU   *pstHiInputEvent;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstHiInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstHiInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndImsMsgServiceSuspendOrResumeSrvInfo_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstHiInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstHiInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_SERVICE;

    pstHiInputEvent->evt.stInputServiceEvent.enInputServeReason = enInputServeReason;

    pstHiInputEvent->evt.stInputServiceEvent.ulOpId = IMSA_AllocImsOpId();

    IMSA_SndImsMsgServiceEvent(pstHiInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstHiInputEvent);

    return;

}

/*****************************************************************************
 Function Name  : IMSA_SndD2AuthNetworkFailure()
 Description    : ����ISIM����Ȩ����ʧ����Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-17  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndD2AuthNetworkFailure
(
    VOS_UINT32                          ulIsEmergencyAuth
)

{
    IMSA_IMS_INPUT_EVENT_STRU               *pstHiInputEvent;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstHiInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstHiInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndD2AuthNetworkFailure:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndD2AuthNetworkFailure_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstHiInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstHiInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_SERVICE;

    if (IMSA_TRUE == ulIsEmergencyAuth)
    {
        pstHiInputEvent->evt.stInputServiceEvent.ulOpId = IMSA_GetRcvImsEmcOpid();
        pstHiInputEvent->evt.stInputServiceEvent.enInputServeReason = IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_NETWORK_FAILURE_EMERGENCY;
    }
    else
    {
        pstHiInputEvent->evt.stInputServiceEvent.ulOpId = IMSA_GetRcvImsNormOpid();
        pstHiInputEvent->evt.stInputServiceEvent.enInputServeReason = IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_NETWORK_FAILURE;
    }

    pstHiInputEvent->evt.stInputServiceEvent.bitOpAka = IMSA_OP_TRUE;

    IMSA_SndImsMsgServiceEvent(pstHiInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstHiInputEvent);

}


VOS_VOID IMSA_SndD2AuthSuccRsp
(
    const USIMM_IMS_AUTH_CNF_STRU      *pstIMSCnf,
    VOS_UINT32                          ulIsEmergencyAuth
)
{
    IMSA_IMS_INPUT_EVENT_STRU               *pstHiInputEvent;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstHiInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstHiInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndD2AuthSuccRsp:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndD2AuthSuccRsp_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstHiInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstHiInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_SERVICE;

    if (IMSA_TRUE == ulIsEmergencyAuth)
    {
        pstHiInputEvent->evt.stInputServiceEvent.ulOpId = IMSA_GetRcvImsEmcOpid();
        pstHiInputEvent->evt.stInputServiceEvent.enInputServeReason = IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_SUCCESS_EMERGENCY;
    }
    else
    {
        pstHiInputEvent->evt.stInputServiceEvent.ulOpId = IMSA_GetRcvImsNormOpid();
        pstHiInputEvent->evt.stInputServiceEvent.enInputServeReason = IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_SUCCESS;
    }

    pstHiInputEvent->evt.stInputServiceEvent.bitOpAka = IMSA_OP_TRUE;

    IMSA_MEM_CPY(pstHiInputEvent->evt.stInputServiceEvent.stAka.aucCk,
                 &pstIMSCnf->aucCK[1],
                 pstIMSCnf->aucCK[0]);

    IMSA_MEM_CPY(pstHiInputEvent->evt.stInputServiceEvent.stAka.aucIk,
                 &pstIMSCnf->aucIK[1],
                 pstIMSCnf->aucIK[0]);

    pstHiInputEvent->evt.stInputServiceEvent.stAka.ulResLength = pstIMSCnf->aucAuthRes[0];

    IMSA_MEM_CPY(pstHiInputEvent->evt.stInputServiceEvent.stAka.aucResponse,
                 &pstIMSCnf->aucAuthRes[1],
                 pstIMSCnf->aucAuthRes[0]);


    IMSA_SndImsMsgServiceEvent(pstHiInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstHiInputEvent);

}

/*****************************************************************************
 Function Name  : IMSA_SndUsimAuthenticationReq()
 Description    : ��USIM���ͼ�Ȩ����
 Input          : ulAppType     Ӧ������
                  enAuthType    ��Ȩ����
                  ulOpId
                  uAuth         ��Ȩ����
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719  2015-02-07   Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndUsimAuthenticationReq
(
    USIMM_CARDAPP_ENUM_UINT32       ulAppType,
    USIMM_AUTH_TYPE_ENUM_UINT32     enAuthType,
    VOS_UINT8                       ulOpId,
    USIMM_AUTH_DATA_UNION          *puAuth
)
{
    USIMM_AUTHENTICATION_REQ_STRU           *pstUsimAuthenticationReq;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstUsimAuthenticationReq = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(USIMM_AUTHENTICATION_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstUsimAuthenticationReq)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndUsimAuthenticationReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndUsimAuthenticationReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( pstUsimAuthenticationReq, 0, sizeof(USIMM_AUTHENTICATION_REQ_STRU));

    /*��д��Ϣͷ*/
    /*��Ϣ�ṹ���е�SendPara�����洢OpId*/
    IMSA_WRITE_USIM_MSG_HEAD(pstUsimAuthenticationReq, USIMM_AUTHENTICATION_REQ, ulAppType, ulOpId);

    pstUsimAuthenticationReq->enAuthType = enAuthType;

    IMSA_MEM_CPY(&(pstUsimAuthenticationReq->uAuth),
                puAuth,
                sizeof(USIMM_AUTH_DATA_UNION));

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstUsimAuthenticationReq);
}

/*****************************************************************************
 Function Name  : IMSA_SndUsimReadFileReq()
 Description    : ��USIM���Ͷ�ȡ�ļ�����
 Input          : ulAppType         Ӧ������
                  ucRecordNum
                  ulOpId
                  stGetFilePath     �ļ�·��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.zhaochen 00308719  2015-02-10   Draft Enact
*****************************************************************************/
VOS_VOID IMSA_SndUsimReadFileReq
(
    USIMM_CARDAPP_ENUM_UINT32       ulAppType,
    VOS_UINT8                       ucRecordNum,
    VOS_UINT8                       ulOpId,
    USIMM_FILEPATH_INFO_STRU       *pstGetFilePath
)
{
    USIMM_READFILE_REQ_STRU     *pstUsimReadFileReq;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstUsimReadFileReq = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(USIMM_READFILE_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstUsimReadFileReq)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndUsimReadFileReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndUsimReadFileReq_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( pstUsimReadFileReq, 0, sizeof(USIMM_READFILE_REQ_STRU));

    /*��д��Ϣͷ*/
    /*��Ϣ�ṹ���е�SendPara�����洢OpId*/
    IMSA_WRITE_USIM_MSG_HEAD(pstUsimReadFileReq, USIMM_READFILE_REQ, ulAppType, ulOpId);

    /*��д��Ϣ����*/
    pstUsimReadFileReq->ucRecordNum = ucRecordNum;
    pstUsimReadFileReq->bNeedReadCache = VOS_TRUE;
    IMSA_MEM_CPY(&(pstUsimReadFileReq->stFilePath),
                 pstGetFilePath,
                 sizeof(USIMM_FILEPATH_INFO_STRU));

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstUsimReadFileReq);
}


/* zhaochen 00308719 begin for USIM interface 2015-02-10 */
/*****************************************************************************
 Function Name  : IMSA_ProcIsimAuthRsp()
 Description    : ����ISIM����Ȩ��Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing     49683      2013-06-24  Draft Enact
      2.zhaochen    00308719   2015-02-10  USIM interface modify
*****************************************************************************/
VOS_VOID IMSA_ProcIsimAuthRsp(const VOS_VOID *pRcvMsg)
{
    USIMM_AUTHENTICATION_CNF_STRU      *pstAuthCnf;
    VOS_UINT32                          ulIsEmergencyAuth = IMSA_FALSE;

    IMSA_NORM_LOG("IMSA_ProcIsimAuthRsp: ENTER!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcIsimAuthRsp_ENUM, LNAS_ENTRY);

    pstAuthCnf = (USIMM_AUTHENTICATION_CNF_STRU*)pRcvMsg;

    if(USIMM_IMS_APP != pstAuthCnf->stCmdResult.enApptype )
    {
        IMSA_WARN_LOG("IMSA_ProcIsimAuthRsp: Not IMS auth!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ProcIsimAuthRsp_ENUM, 2);
        return;
    }

    if (IMSA_GetUsimNormOpid() == pstAuthCnf->stCmdResult.ulSendPara)
    {
        ulIsEmergencyAuth = IMSA_FALSE;
    }
    else if (IMSA_GetUsimEmcOpid() == pstAuthCnf->stCmdResult.ulSendPara)
    {
        ulIsEmergencyAuth = IMSA_TRUE;
    }
    else
    {
        IMSA_WARN_LOG("IMSA_ProcIsimAuthRsp: OPID not match!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ProcIsimAuthRsp_ENUM, IMSA_OPID_NOT_MATCH);
        return;
    }

    switch(pstAuthCnf->enResult)
    {
    case USIMM_AUTH_IMS_SUCCESS:
        IMSA_SndD2AuthSuccRsp(&pstAuthCnf->uCnfData.stIMSCnf, ulIsEmergencyAuth);
        break;

    case USIMM_AUTH_MAC_FAILURE:
        IMSA_SndD2AuthNetworkFailure(ulIsEmergencyAuth);
        break;

    case USIMM_AUTH_SYNC_FAILURE:
        IMSA_SndD2AuthSyncFailure(&pstAuthCnf->uCnfData.stIMSCnf, ulIsEmergencyAuth);
        break;

    case USIMM_AUTH_IMS_OTHER_FAILURE:
        IMSA_SndD2AuthNetworkFailure(ulIsEmergencyAuth);
        break;

    default:/*����������쳣����*/
        IMSA_WARN_LOG("IMSA_ProcIsimAuthRsp: Not IMS auth result!");
        TLPS_PRINT2LAYER_WARNING(IMSA_ProcIsimAuthRsp_ENUM, LNAS_MSG_INVALID);
        break;
    }


}
/* zhaochen 00308719 end for USIM interface 2015-02-10 */


VOS_UINT32  IMSA_BcdToAsciiCode(
    VOS_UINT8                           ucBcdCode,
    VOS_CHAR                            *pcAsciiCode
)
{
    VOS_CHAR                            cAsciiCode;

    if (VOS_NULL_PTR == pcAsciiCode)
    {
        IMSA_ERR_LOG("IMSA_BcdToAsciiCode: Parameter of the function is null.");
        TLPS_PRINT2LAYER_ERROR(IMSA_BcdToAsciiCode_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    if (ucBcdCode <= 0x09)
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x30);
    }
    else if (0x0A == ucBcdCode)
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x20);    /*�ַ�'*'*/
    }
    else if (0x0B == ucBcdCode)
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x18);    /*�ַ�'#'*/
    }
    else if ((0x0C == ucBcdCode)
          || (0x0D == ucBcdCode)
          || (0x0E == ucBcdCode))
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x55);    /*�ַ�'a', 'b', 'c'*/
    }
    else
    {
        IMSA_ERR_LOG("IMSA_BcdToAsciiCode: Parameter of the function is invalid.");
        TLPS_PRINT2LAYER_ERROR(IMSA_BcdToAsciiCode_ENUM, LNAS_PARAM_INVALID);
        return VOS_FALSE;
    }

    *pcAsciiCode = cAsciiCode;

    return VOS_TRUE;
}

VOS_UINT32  IMSA_AsciiToBcdCode(
    VOS_CHAR                            cAsciiCode,
    VOS_UINT8                           *pucBcdCode
)
{
    if (VOS_NULL_PTR == pucBcdCode)
    {
        IMSA_ERR_LOG("IMSA_AsciiToBcdCode: Parameter of the function is null.");
        TLPS_PRINT2LAYER_ERROR(IMSA_AsciiToBcdCode_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    if ((cAsciiCode >= '0')
     && (cAsciiCode <= '9'))
    {
        *pucBcdCode = (VOS_UINT8)(cAsciiCode - '0');
    }
    else if ('*' == cAsciiCode)
    {
        *pucBcdCode = 0x0a;
    }
    else if ('#' == cAsciiCode)
    {
        *pucBcdCode = 0x0b;
    }
    else if (('a' == cAsciiCode)
          || ('b' == cAsciiCode)
          || ('c' == cAsciiCode))
    {
        *pucBcdCode = (VOS_UINT8)((cAsciiCode - 'a') + 0x0c);
    }
    else
    {
        IMSA_ERR_LOG("IMSA_AsciiToBcdCode: Parameter of the function is invalid.");
        TLPS_PRINT2LAYER_ERROR(IMSA_AsciiToBcdCode_ENUM, LNAS_PARAM_INVALID);
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32  IMSA_AsciiToDtmfKeyEnum
(
    VOS_CHAR                            cAsciiCode,
    IMSA_IMS_DTMF_KEY_ENUM_UINT8       *penDtmfKey
)
{
    VOS_CHAR                            cKey = cAsciiCode;

    /* ת��ΪСд�ַ� */
    if ( (cKey >= 'A') && (cKey <= 'D'))
    {
        cKey = cKey + 0x20;
    }

    if ((cKey >= '0') && (cKey <= '9'))
    {
        *penDtmfKey = (IMSA_IMS_DTMF_KEY_ENUM_UINT8)(cKey - '0');
    }
    else if ('*' == cKey)
    {
        *penDtmfKey = IMSA_IMS_DTMF_KEY_STAR;
    }
    else if ('#' == cKey)
    {
        *penDtmfKey = IMSA_IMS_DTMF_KEY_POUND;
    }
    else if (('a' == cKey)
          || ('b' == cKey)
          || ('c' == cKey)
          || ('d' == cKey))
    {
        *penDtmfKey = (IMSA_IMS_DTMF_KEY_ENUM_UINT8)((cKey - 'a') + 0x0c);
    }
    else
    {
        IMSA_ERR_LOG("IMSA_AsciiToDtmfKeyEnum: Parameter of the function is invalid.");
        TLPS_PRINT2LAYER_ERROR(IMSA_AsciiToDtmfKeyEnum_ENUM, LNAS_PARAM_INVALID);
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

VOS_UINT32  IMSA_UtilAsciiNumberToBcd(
    const VOS_CHAR                      *pcAsciiNumber,
    VOS_UINT8                           *pucBcdNumber,
    VOS_UINT8                           *pucBcdLen
)
{
    VOS_UINT8                           ucLoop = 0;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pcAsciiNumber)
     || (VOS_NULL_PTR == pucBcdNumber)
     || (VOS_NULL_PTR == pucBcdLen))
    {
        IMSA_ERR_LOG("IMSA_UtilAsciiNumberToBcd: Parameter of the function is null.");
        TLPS_PRINT2LAYER_ERROR(IMSA_UtilAsciiNumberToBcd_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    for (ucLoop = 0; pcAsciiNumber[ucLoop] != '\0'; ucLoop++)
    {
        ulRet = IMSA_AsciiToBcdCode(pcAsciiNumber[ucLoop], &ucBcdCode);
        if (VOS_TRUE != ulRet)
        {
            return ulRet;
        }

        /*����ǰ��Ҫ����Ŀռ���0*/
        pucBcdNumber[(ucLoop / 2)] &= ((ucLoop % 2) == 1) ? 0x0F : 0xF0;

        /*������������Ӧ�Ŀռ�*/
        pucBcdNumber[(ucLoop / 2)] |= (((ucLoop % 2) == 1) ? ((ucBcdCode << 4) & 0xF0) : (ucBcdCode & 0x0F));
    }

    /*�������Ϊ�����������һ���ַ���Ҫ�� F */
    if (1 == (ucLoop % 2))
    {
        pucBcdNumber[(ucLoop / 2)] |= 0xF0;
    }

    *pucBcdLen = (ucLoop + 1) / 2;

    return VOS_TRUE;
}

VOS_UINT32  IMSA_UtilBcdNumberToAscii(
    const VOS_UINT8                     *pucBcdNumber,
    VOS_UINT8                           ucBcdLen,
    VOS_CHAR                            *pcAsciiNumber
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pucBcdNumber)
     || (VOS_NULL_PTR == pcAsciiNumber))
    {
        IMSA_ERR_LOG("IMSA_UtilBcdNumberToAscii: Parameter of the function is null.");
        TLPS_PRINT2LAYER_ERROR(IMSA_UtilBcdNumberToAscii_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /*��������ַ�����ȥ����Ч��0XFF����*/
    while (ucBcdLen > 1)
    {
        if (0xFF == pucBcdNumber[ucBcdLen - 1])
        {
            ucBcdLen--;
        }
        else
        {
            break;
        }
    }

    /*�ж�pucBcdAddress��ָ����ַ��������һ���ֽڵĸ�λ�Ƿ�Ϊ1111��
    ����ǣ�˵������λ��Ϊ����������Ϊż��*/
    if ((pucBcdNumber[ucBcdLen - 1] & 0xF0) == 0xF0)
    {
        ucLen = (VOS_UINT8)((ucBcdLen * 2) - 1);
    }
    else
    {
        ucLen = (VOS_UINT8)(ucBcdLen * 2);
    }

    /*��������*/
    for (ucLoop = 0; ucLoop < ucLen; ucLoop++)
    {
        /*�жϵ�ǰ�����������λ���뻹��ż��λ���룬��0��ʼ����ż��*/
        if (1 == (ucLoop % 2))
        {
            /*���������λ���룬��ȡ��4λ��ֵ*/
            ucBcdCode = ((pucBcdNumber[(ucLoop / 2)] >> 4) & 0x0F);
        }
        else
        {
            /*�����ż��λ���룬��ȡ��4λ��ֵ*/
            ucBcdCode = (pucBcdNumber[(ucLoop / 2)] & 0x0F);
        }

        /*������������ת����Ascii����ʽ*/
        ulRet = IMSA_BcdToAsciiCode(ucBcdCode, &(pcAsciiNumber[ucLoop]));
        if (VOS_TRUE != ulRet)
        {
            return ulRet;
        }
    }

    pcAsciiNumber[ucLoop] = '\0';      /*�ַ���ĩβΪ0*/

    return VOS_TRUE;
}



VOS_VOID IMSA_UtilStrNCpy(VOS_CHAR *pDst, const VOS_CHAR *pSrc, VOS_UINT32 ulLen)
{
    if (pDst && pSrc)
    {
        (VOS_VOID)VOS_StrNCpy(pDst, (VOS_CHAR *)pSrc, ulLen);
        /*pDst[ulLen - 1] = 0;*/
    }
}
VOS_INT32  IMSA_PrintImsaImsOutputService
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulOutputServiceReasonNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    IMS_IMSA_OUTPUT_SERVICE_MSG_STRU   *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* ��ӡ��Ϣ�ṹ���� */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :IMS_IMSA_OUTPUT_SERVICE_MSG****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    ulOutputServiceReasonNum = sizeof(g_astOutputServiceReasonArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulOutputServiceReasonNum; ulLoop++)
    {
        if (g_astOutputServiceReasonArray[ulLoop].ulId == pstRcvMsg->stOutputService.enOutputServiceReason)
        {
            break;
        }
    }

    if ( ulLoop < ulOutputServiceReasonNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astOutputServiceReasonArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintImsaImsOutputService, Invalid OutputService Reason: ",
                              pstRcvMsg->stOutputService.enOutputServiceReason);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintImsaImsOutputService_ENUM, LNAS_PARAM_INVALID, pstRcvMsg->stOutputService.enOutputServiceReason);
    }

    /* ��ӡ��Ϣ�Ľ�������*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :IMS_IMSA_OUTPUT_SERVICE_MSG****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}


VOS_INT32  IMSA_PrintImsaImsOutputCall
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulOutputCallReasonNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    IMS_IMSA_OUTPUT_CALL_MSG_STRU      *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* ��ӡ��Ϣ�ṹ���� */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :IMS_IMSA_OUTPUT_CALL_MSG****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    ulOutputCallReasonNum = sizeof(g_astOutputCallReasonArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulOutputCallReasonNum; ulLoop++)
    {
        if (g_astOutputCallReasonArray[ulLoop].ulId == pstRcvMsg->stOutputCall.enOutputCallReason)
        {
            break;
        }
    }

    if ( ulLoop < ulOutputCallReasonNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astOutputCallReasonArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintImsaImsOutputCall, Invalid OutputCall Reason: ",
                              pstRcvMsg->stOutputCall.enOutputCallReason);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintImsaImsOutputCall_ENUM, LNAS_PARAM_INVALID, pstRcvMsg->stOutputCall.enOutputCallReason);
    }

    /* ��ӡ��Ϣ�Ľ�������*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :IMS_IMSA_OUTPUT_CALL_MSG****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}


VOS_INT32  IMSA_PrintImsaImsOutputSms
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulOutputSmsReasonNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    IMS_IMSA_OUTPUT_SMS_MSG_STRU       *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* ��ӡ��Ϣ�ṹ���� */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :IMS_IMSA_OUTPUT_SMS_MSG****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    ulOutputSmsReasonNum = sizeof(g_astOutputSmsReasonArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulOutputSmsReasonNum; ulLoop++)
    {
        if (g_astOutputSmsReasonArray[ulLoop].ulId == pstRcvMsg->stOutputSms.enOutputSmsReason)
        {
            break;
        }
    }

    if ( ulLoop < ulOutputSmsReasonNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astOutputSmsReasonArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintImsaImsOutputSms, Invalid OutputSms Reason: ",
                              pstRcvMsg->stOutputSms.enOutputSmsReason);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintImsaImsOutputSms_ENUM, LNAS_PARAM_INVALID, pstRcvMsg->stOutputSms.enOutputSmsReason);
    }

    /* ��ӡ��Ϣ�Ľ�������*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :IMS_IMSA_OUTPUT_SMS_MSG****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}


VOS_INT32  IMSA_PrintImsaImsOutputSystem
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulOutputSystemReasonNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    IMS_IMSA_OUTPUT_SYSTEM_MSG_STRU    *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* ��ӡ��Ϣ�ṹ���� */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :IMS_IMSA_OUTPUT_SYSTEM_MSG****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    ulOutputSystemReasonNum = sizeof(g_astOutputSystemReasonArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulOutputSystemReasonNum; ulLoop++)
    {
        if (g_astOutputSystemReasonArray[ulLoop].ulId == pstRcvMsg->stOutputSystem.enOutputSysReason)
        {
            break;
        }
    }

    if ( ulLoop < ulOutputSystemReasonNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astOutputSystemReasonArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintImsaImsOutputSystem, Invalid OutputSystem Reason: ",
                              pstRcvMsg->stOutputSystem.enOutputSysReason);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintImsaImsOutputSystem_ENUM, LNAS_PARAM_INVALID, pstRcvMsg->stOutputSystem.enOutputSysReason);
    }

    /* ��ӡ��Ϣ�Ľ�������*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :IMS_IMSA_OUTPUT_SYSTEM_MSG****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}


VOS_INT32  IMSA_PrintImsaImsOutputPara
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulOutputParaReasonNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    IMS_IMSA_OUTPUT_PARA_MSG_STRU      *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* ��ӡ��Ϣ�ṹ���� */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :IMS_IMSA_OUTPUT_PARA_MSG****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    ulOutputParaReasonNum = sizeof(g_astOutputParaReasonArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulOutputParaReasonNum; ulLoop++)
    {
        if (g_astOutputParaReasonArray[ulLoop].ulId == pstRcvMsg->stOutputPara.enOutputParaReason)
        {
            break;
        }
    }

    if ( ulLoop < ulOutputParaReasonNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astOutputParaReasonArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintImsaImsOutputPara, Invalid OutputPara Reason: ",
                              pstRcvMsg->stOutputPara.enOutputParaReason);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintImsaImsOutputPara_ENUM, LNAS_PARAM_INVALID, pstRcvMsg->stOutputPara.enOutputParaReason);
    }

    /* ��ӡ��Ϣ�Ľ�������*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :IMS_IMSA_OUTPUT_PARA_MSG****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}


VOS_INT32  IMSA_PrintCallImsaSrvccStatusNotify
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* ��ӡ��Ϣ�ṹ���� */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :IMSA_PrintCallImsaSrvccStatusNotify****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* ��ӡ��Ϣ��ÿ������*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       " enSrvccStatus = %d \r\n",
                       pstRcvMsg->enSrvccStatus,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* ��ӡ��Ϣ�Ľ�������*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :IMSA_PrintCallImsaSrvccStatusNotify****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}
VOS_INT32  IMSA_PrintImsaImsInputSystem
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulInputRadioReasonNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    IMSA_IMS_INPUT_SYSTEM_MSG_STRU     *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* ��ӡ��Ϣ�ṹ���� */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :IMSA_IMS_INPUT_SYSTEM_MSG****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;


    ulInputRadioReasonNum = sizeof(g_astInputSystemReasonArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulInputRadioReasonNum; ulLoop++)
    {
        if (g_astInputSystemReasonArray[ulLoop].ulId == pstRcvMsg->stInputSystem.enInputSysReason)
        {
            break;
        }
    }

    if ( ulLoop < ulInputRadioReasonNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astInputSystemReasonArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintImsaImsInputSystem, Invalid InputSystem Reason: ",
                              pstRcvMsg->stInputSystem.enInputSysReason);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintImsaImsInputSystem_ENUM, LNAS_PARAM_INVALID, pstRcvMsg->stInputSystem.enInputSysReason);
    }

    /* ��ӡ��Ϣ�Ľ�������*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :IMSA_IMS_INPUT_SYSTEM_MSG****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}


VOS_INT32  IMSA_PrintImsaImsInputPara
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulInputRadioReasonNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    IMSA_IMS_INPUT_PARA_MSG_STRU       *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* ��ӡ��Ϣ�ṹ���� */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :IMSA_IMS_INPUT_PARA_MSG****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;


    ulInputRadioReasonNum = sizeof(g_astInputParaReasonArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulInputRadioReasonNum; ulLoop++)
    {
        if (g_astInputParaReasonArray[ulLoop].ulId == pstRcvMsg->stInputPara.enInputParaReason)
        {
            break;
        }
    }

    if ( ulLoop < ulInputRadioReasonNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astInputParaReasonArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintImsaImsInputPara, Invalid InputPara Reason: ",
                              pstRcvMsg->stInputPara.enInputParaReason);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintImsaImsInputPara_ENUM, LNAS_PARAM_INVALID, pstRcvMsg->stInputPara.enInputParaReason);
    }

    /* ��ӡ��Ϣ�Ľ�������*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :IMSA_IMS_INPUT_PARA_MSG****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}


VOS_INT32  IMSA_PrintImsaImsInputService
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulInputServiceReasonNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    IMSA_IMS_INPUT_SERVICE_MSG_STRU    *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* ��ӡ��Ϣ�ṹ���� */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :IMSA_IMS_INPUT_SERVICE_MSG****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;


    ulInputServiceReasonNum = sizeof(g_astInputServiceReasonArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulInputServiceReasonNum; ulLoop++)
    {
        if (g_astInputServiceReasonArray[ulLoop].ulId == pstRcvMsg->stInputService.enInputServeReason)
        {
            break;
        }
    }

    if ( ulLoop < ulInputServiceReasonNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astInputServiceReasonArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintImsaImsInputService, Invalid InputService Reason: ",
                              pstRcvMsg->stInputService.enInputServeReason);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintImsaImsInputService_ENUM, LNAS_PARAM_INVALID, pstRcvMsg->stInputService.enInputServeReason);
    }

    /* ��ӡ��Ϣ�Ľ�������*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :IMSA_IMS_INPUT_SERVICE_MSG****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}



VOS_INT32  IMSA_PrintImsaImsInputSms
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulInputSmsReasonNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    IMSA_IMS_INPUT_SMS_MSG_STRU        *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* ��ӡ��Ϣ�ṹ���� */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :IMSA_IMS_INPUT_SMS_MSG****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;


    ulInputSmsReasonNum = sizeof(g_astInputSmsReasonArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulInputSmsReasonNum; ulLoop++)
    {
        if (g_astInputSmsReasonArray[ulLoop].ulId == pstRcvMsg->stInputSms.enInputSmsReason)
        {
            break;
        }
    }

    if ( ulLoop < ulInputSmsReasonNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astInputSmsReasonArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintImsaImsInputSms, Invalid InputSms Reason: ",
                              pstRcvMsg->stInputSms.enInputSmsReason);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintImsaImsInputSms_ENUM, LNAS_PARAM_INVALID, pstRcvMsg->stInputSms.enInputSmsReason);
    }

    /* ��ӡ��Ϣ�Ľ�������*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :IMSA_IMS_INPUT_SMS_MSG****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}



VOS_INT32  IMSA_PrintImsaImsInputCall
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulInputCallReasonNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    IMSA_IMS_INPUT_CALL_MSG_STRU       *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* ��ӡ��Ϣ�ṹ���� */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :IMSA_IMS_INPUT_CALL_MSG****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;


    ulInputCallReasonNum = sizeof(g_astInputCallReasonArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulInputCallReasonNum; ulLoop++)
    {
        if (g_astInputCallReasonArray[ulLoop].ulId == pstRcvMsg->stInputCall.enInputCallReason)
        {
            break;
        }
    }

    if ( ulLoop < ulInputCallReasonNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astInputCallReasonArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintImsaImsInputCall, Invalid InputCall Reason: ",
                              pstRcvMsg->stInputCall.enInputCallReason);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintImsaImsInputCall_ENUM, LNAS_PARAM_INVALID, pstRcvMsg->stInputCall.enInputCallReason);
    }

    /* ��ӡ��Ϣ�Ľ�������*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :IMSA_IMS_INPUT_CALL_MSG****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}



VOS_INT32  IMSA_PrintImsaSpmCallMsg
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulCallMsgEvtNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    IMSA_SPM_CALL_MSG_STRU             *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* ��ӡ��Ϣ�ṹ���� */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :IMSA_SPM_CALL_MSG****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;


    ulCallMsgEvtNum = sizeof(g_astCallMsgEvtArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulCallMsgEvtNum; ulLoop++)
    {
        if (g_astCallMsgEvtArray[ulLoop].ulId == pstRcvMsg->enEventType)
        {
            break;
        }
    }

    if ( ulLoop < ulCallMsgEvtNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astCallMsgEvtArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintImsaSpmCallMsg, Invalid enEventType: ",
                              pstRcvMsg->enEventType);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintImsaSpmCallMsg_ENUM, LNAS_PARAM_INVALID, pstRcvMsg->enEventType);
    }

    /* ��ӡ��Ϣ��ÿ������*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       "CallId = %d \r\n",
                       pstRcvMsg->stCallInfo.callId,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* ��ӡ��Ϣ��ÿ������*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       "ClientId = %d \r\n",
                       pstRcvMsg->stCallInfo.clientId,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* ��ӡ��Ϣ��ÿ������*/
    NAS_COMM_nsprintf_1(pcBuff,
                       usTotalLen,
                       "OpId = %d \r\n",
                       pstRcvMsg->stCallInfo.opId,
                      &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* ��ӡ��Ϣ�Ľ�������*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :IMSA_SPM_CALL_MSG****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}
VOS_INT32  IMSA_PrintSpmImsaCallSupsCmdReq
(
    VOS_CHAR                                *pcBuff,
    VOS_UINT16                               usOffset,
    const PS_MSG_HEADER_STRU                *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulCallSupsCmdNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen  = usOffset;
    SPM_IMSA_CALL_SUPS_CMD_REQ_STRU    *pstRcvMsg   = VOS_NULL_PTR;

    pstRcvMsg = (VOS_VOID *)pstMsg;

    /* ��ӡ��Ϣ�ṹ���� */
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "\r\n ****************Begin :SPM_IMSA_CALL_SUPS_CMD_REQ****************\r\n",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;


    ulCallSupsCmdNum = sizeof(g_astCallSupsCmdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulCallSupsCmdNum; ulLoop++)
    {
        if (g_astCallSupsCmdArray[ulLoop].ulId == pstRcvMsg->stCallMgmtCmd.enCallSupsCmd)
        {
            break;
        }
    }

    if ( ulLoop < ulCallSupsCmdNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astCallSupsCmdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintSpmImsaCallSupsCmdReq, Invalid enCallSupsCmd: ",
                              pstRcvMsg->stCallMgmtCmd.enCallSupsCmd);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintSpmImsaCallSupsCmdReq_ENUM, LNAS_PARAM_INVALID, pstRcvMsg->stCallMgmtCmd.enCallSupsCmd);
    }

    /* ��ӡ��Ϣ�Ľ�������*/
    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     " ****************End :SPM_IMSA_CALL_SUPS_CMD_REQ****************",
                    &ilOutPutLen);

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset) ;
}



VOS_INT32   IMSA_PrintImsaIntraMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    IMSA_INTRA_MSG_ID_ENUM_UINT32       enMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulImsaIntraMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulImsaIntraMsgNum = sizeof(g_astImsaIntraMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulImsaIntraMsgNum; ulLoop++)
    {
        if (g_astImsaIntraMsgIdArray[ulLoop].ulId == enMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulImsaIntraMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astImsaIntraMsgIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintImsaIntraMsg, Invalid enMsgId: ",
                              enMsgId);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintImsaIntraMsg_ENUM, LNAS_MSG_INVALID, enMsgId);
    }

    return (usTotalLen - usOffset);
}


VOS_INT32   IMSA_PrintUsimMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulImsaUsimMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulImsaUsimMsgNum = sizeof(g_astImsaUsimMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulImsaUsimMsgNum; ulLoop++)
    {
        if (g_astImsaUsimMsgIdArray[ulLoop].ulId == ulMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulImsaUsimMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astImsaUsimMsgIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintUsimMsg, Invalid enMsgId: ",
                              ulMsgId);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintUsimMsg_ENUM, LNAS_MSG_INVALID, ulMsgId);
    }

    return (usTotalLen - usOffset);
}


VOS_INT32   IMSA_PrintVcMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulImsaVcMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulImsaVcMsgNum = sizeof(g_astImsaVcMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulImsaVcMsgNum; ulLoop++)
    {
        if (g_astImsaVcMsgIdArray[ulLoop].ulId == ulMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulImsaVcMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astImsaVcMsgIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintVcMsg, Invalid enMsgId: ",
                              ulMsgId);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintVcMsg_ENUM, LNAS_MSG_INVALID, ulMsgId);
    }

    return (usTotalLen - usOffset);
}


VOS_INT32   IMSA_PrintCdsMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulImsaCdsMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulImsaCdsMsgNum = sizeof(g_astImsaCdsMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulImsaCdsMsgNum; ulLoop++)
    {
        if (g_astImsaCdsMsgIdArray[ulLoop].ulId == ulMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulImsaCdsMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astImsaCdsMsgIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintCdsMsg, Invalid enMsgId: ",
                              ulMsgId);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintCdsMsg_ENUM, LNAS_MSG_INVALID, ulMsgId);
    }

    return (usTotalLen - usOffset);
}


VOS_INT32   IMSA_PrintMtcMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulImsaMtcMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulImsaMtcMsgNum = sizeof(g_astImsaMtcMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulImsaMtcMsgNum; ulLoop++)
    {
        if (g_astImsaMtcMsgIdArray[ulLoop].ulId == ulMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulImsaMtcMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astImsaMtcMsgIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintMtcMsg, Invalid enMsgId: ",
                              ulMsgId);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintMtcMsg_ENUM, LNAS_MSG_INVALID, ulMsgId);
    }

    return (usTotalLen - usOffset);
}



VOS_INT32  IMSA_PrintImsaTimer
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulTimerType,
    VOS_UINT32                          ulTimerPara
)

{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulImsaTimerNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulImsaTimerNum = sizeof(g_astImsaTimerArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulImsaTimerNum; ulLoop++)
    {
        if (g_astImsaTimerArray[ulLoop].ulId == ulTimerType)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulImsaTimerNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astImsaTimerArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        /* ��ӡ��Ϣ��ÿ������*/
        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           " ulPara = %d \r\n",
                           ulTimerPara,
                          &ilOutPutLen);

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintImsaTimer, Invalid Timer Type: ",ulTimerType);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintImsaTimer_ENUM, LNAS_PARAM_INVALID, ulTimerType);
    }

    return (usTotalLen - usOffset);

}
VOS_INT32   IMSA_PrintMmaMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulImsaMmaMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulImsaMmaMsgNum = sizeof(g_astImsaMsccMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulImsaMmaMsgNum; ulLoop++)
    {
        if (g_astImsaMsccMsgIdArray[ulLoop].ulId == ulMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulImsaMmaMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astImsaMsccMsgIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintMmaMsg, Invalid enMsgId: ",
                              ulMsgId);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintMmaMsg_ENUM, LNAS_MSG_INVALID, ulMsgId);
    }

    return (usTotalLen - usOffset);
}


VOS_INT32   IMSA_PrintApsMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    const TAF_PS_EVT_STRU              *pstApsEvt
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulImsaApsEvtNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulImsaApsEvtNum = sizeof(g_astImsaApsEvtIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulImsaApsEvtNum; ulLoop++)
    {
        if (g_astImsaApsEvtIdArray[ulLoop].ulId == pstApsEvt->ulEvtId)
        {
            break;
        }
    }

    if ( ulLoop < ulImsaApsEvtNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astImsaApsEvtIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintApsMsg, Invalid enMsgId: ",
                              pstApsEvt->ulEvtId);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintApsMsg_ENUM, LNAS_MSG_INVALID, pstApsEvt->ulEvtId);
    }

    return (usTotalLen - usOffset);
}


VOS_INT32  IMSA_PrintSpmMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulSpmImsaMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulSpmImsaMsgNum = sizeof(g_astImsaSpmMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    /* ���Ҷ�Ӧ����Ϣ */
    for (ulLoop = 0; ulLoop< ulSpmImsaMsgNum ; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astImsaSpmMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulSpmImsaMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astImsaSpmMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astImsaSpmMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astImsaSpmMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                     usTotalLen,
                                                                     pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintSpmMsg, Invalid enMsgId: ",pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintSpmMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);

}
VOS_INT32  IMSA_PrintAtMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulAtImsaMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulAtImsaMsgNum = sizeof(g_astImsaAtMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    /* ���Ҷ�Ӧ����Ϣ */
    for (ulLoop = 0; ulLoop< ulAtImsaMsgNum ; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astImsaAtMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulAtImsaMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astImsaAtMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astImsaAtMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astImsaAtMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                     usTotalLen,
                                                                     pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintAtMsg, Invalid enMsgId: ",pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintAtMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);

}


/*****************************************************************************
 Function Name   : IMSA_PrintMsgMsg
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_INT32

 History         :
    1.sunbing 49683      2013-10-15  Draft Enact

*****************************************************************************/
VOS_INT32  IMSA_PrintMsgMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulSpmImsaMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulSpmImsaMsgNum = sizeof(g_astImsaMsgMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    /* ���Ҷ�Ӧ����Ϣ */
    for (ulLoop = 0; ulLoop< ulSpmImsaMsgNum ; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astImsaMsgMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulSpmImsaMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astImsaMsgMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astImsaMsgMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astImsaMsgMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                     usTotalLen,
                                                                     pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintMsgMsg, Invalid enMsgId: ",pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintMsgMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);

}

/*****************************************************************************
 Function Name   : IMSA_PrintCallMsg
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_INT32

 History         :
    1.sunbing 49683      2013-10-15  Draft Enact

*****************************************************************************/
VOS_INT32  IMSA_PrintCallMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulSpmImsaMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulSpmImsaMsgNum = sizeof(g_astImsaCallMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    /* ���Ҷ�Ӧ����Ϣ */
    for (ulLoop = 0; ulLoop< ulSpmImsaMsgNum ; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astImsaCallMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulSpmImsaMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astImsaCallMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astImsaCallMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astImsaCallMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                     usTotalLen,
                                                                     pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintCallMsg, Invalid enMsgId: ",pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintCallMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);

}
VOS_INT32  IMSA_PrintImsMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)

{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulImsImsaMsgNum;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* �����Ϣ��ĳ��� */
    ulImsImsaMsgNum = sizeof(g_astImsaImsMsgIdArray)/sizeof(NAS_COMM_PRINT_LIST_STRU);

    /* ���Ҷ�Ӧ����Ϣ */
    for (ulLoop = 0; ulLoop< ulImsImsaMsgNum ; ulLoop++)
    {
        if (pstMsg->ulMsgName == g_astImsaImsMsgIdArray[ulLoop].ulId)
        {
            break;
        }
    }

    /* ��ӡ��Ӧ����Ϣ */
    if ( ulLoop < ulImsImsaMsgNum )
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         (VOS_CHAR *)(g_astImsaImsMsgIdArray[ulLoop].aucPrintString),
                         &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                           usTotalLen,
                           "[ TICK : %ld ]",
                           PS_GET_TICK(),
                          &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        if (VOS_NULL_PTR != g_astImsaImsMsgIdArray[ulLoop].pfActionFun)
        {
            ilOutPutLen = g_astImsaImsMsgIdArray[ulLoop].pfActionFun(pcBuff,
                                                                     usTotalLen,
                                                                     pstMsg);
        }

        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintImsMsg, Invalid enMsgId: ",pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintImsMsg_ENUM, LNAS_MSG_INVALID, pstMsg->ulMsgName);
    }

    return (usTotalLen - usOffset);

}

/*****************************************************************************
 Function Name   : IMSA_PrintRcvTafMsg
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_INT32

 History         :
    1.sunbing 49683      2013-10-15  Draft Enact

*****************************************************************************/
VOS_INT32  IMSA_PrintRcvTafMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)
{
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    if (MN_CALLBACK_PS_CALL == pstMsg->ulMsgName)
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         "APS-->IMSA\t",
                        &ilOutPutLenHead);

        usTotalLen += (VOS_UINT16)ilOutPutLenHead;
        /*lint -e826*/
        ilOutPutLen = IMSA_PrintApsMsg( pcBuff,
                                        usTotalLen,
                                        (const TAF_PS_EVT_STRU*)pstMsg);
        /*lint +e826*/
    }

    if((pstMsg->ulMsgName >= ID_SPM_IMSA_CALL_ORIG_REQ)
     && (pstMsg->ulMsgName < ID_SPM_IMSA_MSG_TYPE_BUTT))
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         "SPM-->IMSA\t",
                        &ilOutPutLenHead);

        usTotalLen += (VOS_UINT16)ilOutPutLenHead;

        ilOutPutLen = IMSA_PrintSpmMsg( pcBuff,
                                        usTotalLen,
                                        pstMsg);
    }

    if((pstMsg->ulMsgName >= ID_MSG_IMSA_RP_DATA_REQ)
     && (pstMsg->ulMsgName < ID_IMSA_MSG_TYPE_BUTT))
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         "MSG-->IMSA\t",
                        &ilOutPutLenHead);

        usTotalLen += (VOS_UINT16)ilOutPutLenHead;

        ilOutPutLen = IMSA_PrintMsgMsg( pcBuff,
                                        usTotalLen,
                                        pstMsg);
    }



    if((pstMsg->ulMsgName >= ID_CALL_IMSA_SRVCC_STATUS_NOTIFY)
        &&(pstMsg->ulMsgName <= ID_CALL_IMSA_MSG_TYPE_BUTT))
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         "CALL-->IMSA\t",
                        &ilOutPutLenHead);

        usTotalLen += (VOS_UINT16)ilOutPutLenHead;

        ilOutPutLen = IMSA_PrintCallMsg( pcBuff,
                                        usTotalLen,
                                        pstMsg);
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset);

}



VOS_VOID IMSA_PrintImsaRevMsg
(
    const PS_MSG_HEADER_STRU           *pstMsg,
    VOS_CHAR                           *pcBuff
)
{
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen          = 0;

    NAS_COMM_nsprintf(pcBuff,
                     usTotalLen,
                     "IMSA Receive Message:",
                     &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        IMSA_WARN_LOG("IMSA_PrintImsaRevMsg, Print receive msg header exception.");
        TLPS_PRINT2LAYER_WARNING(IMSA_PrintImsaRevMsg_ENUM, LNAS_PARAM_INVALID);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* ��ӡ����PID����Ϣ */
    switch ( pstMsg->ulSenderPid )
    {
        case WUEPS_PID_TAF:
            ilOutPutLen = IMSA_PrintRcvTafMsg( pcBuff,
                                                usTotalLen,
                                                pstMsg);
            break;

        case UEPS_PID_MSCC:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "MSCC-->IMSA\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintMmaMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;

        case PS_PID_IMSA:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "IMSA-->IMSA\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintImsaIntraMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg->ulMsgName);
            break;

        case PS_PID_IMSVA  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "IMS-->IMSA\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintImsMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case WUEPS_PID_AT  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "AT-->IMSA\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintAtMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case WUEPS_PID_USIM:
        case MAPS_PIH_PID:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "USIM-->IMSA\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintUsimMsg(pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;

        case WUEPS_PID_VC:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "VC-->IMSA\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintVcMsg(  pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;

        case UEPS_PID_CDS:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "CDS-->IMSA\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintCdsMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;

        case VOS_PID_TIMER  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "TIMER-->IMSA\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintImsaTimer(pcBuff,
                                            usTotalLen,
                                            ((REL_TIMER_MSG *)(VOS_VOID *)pstMsg)->ulName,
                                            ((REL_TIMER_MSG *)(VOS_VOID *)pstMsg)->ulPara);
            break;

        case UEPS_PID_MTC:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "MTC-->IMSA\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintMtcMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;

        default:
            IMSA_WARN_LOG2("IMSA_PrintImsaRevMsg,Invalid Pid, MsgId: ",
                          pstMsg->ulSenderPid,
                          pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_WARNING2(IMSA_PrintImsaRevMsg_ENUM, LNAS_PARAM_INVALID, pstMsg->ulSenderPid, pstMsg->ulMsgName);

            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        IMSA_WARN_LOG2("IMSA_PrintImsaRevMsg, print return zero length.SenderPid, MsgId: ",
                      pstMsg->ulSenderPid,
                      pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING2(IMSA_PrintImsaRevMsg_ENUM, LNAS_FAIL, pstMsg->ulSenderPid, pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff, usTotalLen);

    return ;

}

/*****************************************************************************
 Function Name   : IMSA_PrintSendTafMsg
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_INT32

 History         :
    1.sunbing 49683      2013-10-15  Draft Enact

*****************************************************************************/
VOS_INT32  IMSA_PrintSendTafMsg
(
    VOS_CHAR                            *pcBuff,
    VOS_UINT16                           usOffset,
    const PS_MSG_HEADER_STRU            *pstMsg
)
{
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    if (MN_CALLBACK_PS_CALL == pstMsg->ulMsgName)
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         "IMSA-->APS\t",
                        &ilOutPutLenHead);

        usTotalLen += (VOS_UINT16)ilOutPutLenHead;

        /*lint -e826*/
        ilOutPutLen = IMSA_PrintApsMsg( pcBuff,
                                        usTotalLen,
                                        (TAF_PS_EVT_STRU*)pstMsg);
        /*lint +e826*/
    }

    if((pstMsg->ulMsgName >= ID_SPM_IMSA_CALL_ORIG_REQ)
     && (pstMsg->ulMsgName < ID_SPM_IMSA_MSG_TYPE_BUTT))
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         "IMSA-->SPM\t",
                        &ilOutPutLenHead);

        usTotalLen += (VOS_UINT16)ilOutPutLenHead;

        ilOutPutLen = IMSA_PrintSpmMsg( pcBuff,
                                        usTotalLen,
                                        pstMsg);
    }

    if((pstMsg->ulMsgName >= ID_MSG_IMSA_RP_DATA_REQ)
     && (pstMsg->ulMsgName < ID_IMSA_MSG_TYPE_BUTT))
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         "IMSA-->MSG\t",
                        &ilOutPutLenHead);

        usTotalLen += (VOS_UINT16)ilOutPutLenHead;

        ilOutPutLen = IMSA_PrintMsgMsg( pcBuff,
                                        usTotalLen,
                                        pstMsg);
    }

    if((pstMsg->ulMsgName >= ID_CALL_IMSA_SRVCC_STATUS_NOTIFY)
        &&(pstMsg->ulMsgName <= ID_CALL_IMSA_MSG_TYPE_BUTT))
    {
        NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         "IMSA-->CALL\t",
                        &ilOutPutLenHead);

        usTotalLen += (VOS_UINT16)ilOutPutLenHead;

        ilOutPutLen = IMSA_PrintCallMsg( pcBuff,
                                        usTotalLen,
                                        pstMsg);
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    return (usTotalLen - usOffset);

}


/*****************************************************************************
 Function Name   : IMSA_PrintImsaSendMsg
 Description     :
 Input           : None
 Output          : None
 Return          : VOS_INT32

 History         :
    1.lihong00150010    2013-08-08  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_PrintImsaSendMsg
(
    const PS_MSG_HEADER_STRU               *pstMsg,
    VOS_CHAR                               *pcBuff
)
{
    VOS_INT32                           ilOutPutLenHead     = 0;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen          = 0;

    /* delay begin */
    PS_LOG_RETURN();
    /* delay end */

    /* ��ӡ����*/
    NAS_COMM_nsprintf(pcBuff,
                         usTotalLen,
                         "IMSA Send Message:",
                         &ilOutPutLen);

    if ( 0 == ilOutPutLen )
    {
        IMSA_WARN_LOG("IMSA_PrintImsaSendMsg, Print send msg header exception.");
        TLPS_PRINT2LAYER_WARNING(IMSA_PrintImsaSendMsg_ENUM, LNAS_PARAM_INVALID);
        return ;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    /* ��ӡ����PID����Ϣ */
    switch ( pstMsg->ulReceiverPid )
    {
        case WUEPS_PID_TAF:
            ilOutPutLen = IMSA_PrintSendTafMsg(pcBuff,
                                               usTotalLen,
                                               pstMsg);
            break;

        case UEPS_PID_MSCC:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "IMSA-->MSCC\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintMmaMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;

        case PS_PID_IMSA:
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "IMSA-->IMSA\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintImsaIntraMsg(pcBuff,
                                              usTotalLen,
                                              pstMsg->ulMsgName);
            break;

        case PS_PID_IMSVA  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "IMSA-->IMS\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintImsMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case WUEPS_PID_AT  :
            NAS_COMM_nsprintf(pcBuff,
                             usTotalLen,
                             "IMSA-->AT\t",
                            &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintAtMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg);
            break;

        case WUEPS_PID_VC:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "IMSA-->VC\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintVcMsg(  pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;

        case UEPS_PID_CDS:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "IMSA-->CDS\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintCdsMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;
        #if (FEATURE_ON == FEATURE_DSDS)
        case PS_PID_ERRC:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "IMSA-->ERRC\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintErrcMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;
        #endif

        case UEPS_PID_MTC:
            NAS_COMM_nsprintf(  pcBuff,
                                usTotalLen,
                                "IMSA-->MTC\t",
                                &ilOutPutLenHead);

            usTotalLen += (VOS_UINT16)ilOutPutLenHead;

            ilOutPutLen = IMSA_PrintMtcMsg( pcBuff,
                                            usTotalLen,
                                            pstMsg->ulMsgName);
            break;
        default:
            IMSA_WARN_LOG2("IMSA_PrintImsaSendMsg,Invalid Pid, MsgId: ",
                          pstMsg->ulReceiverPid,
                          pstMsg->ulMsgName);
            TLPS_PRINT2LAYER_WARNING2(IMSA_PrintImsaSendMsg_ENUM, LNAS_PARAM_INVALID, pstMsg->ulReceiverPid, pstMsg->ulMsgName);

            return ;
    }

    if ( 0 == ilOutPutLen )
    {
        IMSA_WARN_LOG2("IMSA_PrintImsaSendMsg, print return zero length. ReceiverPid, MsgId: ",
                              pstMsg->ulReceiverPid,
                              pstMsg->ulMsgName);
        TLPS_PRINT2LAYER_WARNING2(IMSA_PrintImsaSendMsg_ENUM, LNAS_FAIL, pstMsg->ulReceiverPid, pstMsg->ulMsgName);
        return;
    }

    usTotalLen += (VOS_UINT16)ilOutPutLen;

    NAS_COMM_Print(pcBuff,usTotalLen);


    /*��ӡ��ǰ��ȫ������״̬�Ϳտ���Ϣԭʼ����*/
    IMSA_NORM_LOG("=============OUT MSG CONTENT is :====================");
    NAS_COMM_PrintArray(             IMSA_GET_IMSA_PRINT_BUF(),
                                     (VOS_UINT8 *)pstMsg,
                                     (pstMsg->ulLength + VOS_MSG_HEAD_LENGTH));
    IMSA_NORM_LOG("====================================================");

    return ;
}
IMSA_IMS_NW_ACCESS_TYPE_ENUM_UINT8 IMSA_ConverterAccessType2Ims
(
    MSCC_IMSA_ACCESS_TYPE_ENUM_UINT8     enAccessType
)
{
    IMSA_IMS_NW_ACCESS_TYPE_ENUM_UINT8  enImsAccessType = IMSA_IMS_NW_ACCESS_TYPE_BUTT;

    switch (enAccessType)
    {
        case MSCC_IMSA_ACCESS_TYPE_GERAN:
            enImsAccessType = IMSA_IMS_NW_ACCESS_TYPE_3GPP_GERAN;
            break;
        case MSCC_IMSA_ACCESS_TYPE_UTRAN_TDD:
            enImsAccessType = IMSA_IMS_NW_ACCESS_TYPE_3GPP_UTRAN_TDD;
            break;
        case MSCC_IMSA_ACCESS_TYPE_UTRAN_FDD:
            enImsAccessType = MSCC_IMSA_ACCESS_TYPE_UTRAN_FDD;
            break;
        case MSCC_IMSA_ACCESS_TYPE_EUTRAN_TDD:
            enImsAccessType = IMSA_IMS_NW_ACCESS_TYPE_3GPP_EUTRAN_TDD;
            break;
        case MSCC_IMSA_ACCESS_TYPE_EUTRAN_FDD:
            enImsAccessType = IMSA_IMS_NW_ACCESS_TYPE_3GPP_EUTRAN_FDD;
            break;
        default:
            IMSA_WARN_LOG("IMSA_ConverterAccessType2Ims:illegal type");
            TLPS_PRINT2LAYER_WARNING(IMSA_ConverterAccessType2Ims_ENUM, LNAS_PARAM_INVALID);
            break;
    }

    return enImsAccessType;
}


VOS_CHAR IMSA_ConverterDigit2Chacter
(
    VOS_UINT8                           ucDigit
)
{
    return (VOS_CHAR)(ucDigit + 0x30);
}


VOS_VOID IMSA_ConverterCgiParam2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo   = VOS_NULL_PTR;
    VOS_UINT8                           ucDigit     = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_ConverterCgiParam2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConverterCgiParam2Ims_ENUM, LNAS_ENTRY);

    pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_PARA;

    pstImsaImsInputEvt->evt.stInputParaEvent.ulOpId = IMSA_AllocImsOpId();
    pstImsaImsInputEvt->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_SET_CGI;

    pstNwInfo   = IMSA_GetNetInfoAddress();
    pstImsaImsInputEvt->evt.stInputParaEvent.u.stCgi.enNwAccessType
                = IMSA_ConverterAccessType2Ims(pstNwInfo->enAccessType);

    /* ȡMCC��һDIGIT */
    ucDigit     = (pstNwInfo->stPlmnId.ulMcc & 0xff);
    pstImsaImsInputEvt->evt.stInputParaEvent.u.stCgi.cMcc[0]
                = IMSA_ConverterDigit2Chacter(ucDigit);

    /* ȡMCC�ڶ�DIGIT */
    ucDigit     = (pstNwInfo->stPlmnId.ulMcc & 0xff00) >> IMSA_MOVEMENT_8;
    pstImsaImsInputEvt->evt.stInputParaEvent.u.stCgi.cMcc[1]
                = IMSA_ConverterDigit2Chacter(ucDigit);

    /* ȡMCC����DIGIT */
    ucDigit     = (pstNwInfo->stPlmnId.ulMcc & 0xff0000) >> IMSA_MOVEMENT_16;
    pstImsaImsInputEvt->evt.stInputParaEvent.u.stCgi.cMcc[2]
                = IMSA_ConverterDigit2Chacter(ucDigit);

    pstImsaImsInputEvt->evt.stInputParaEvent.u.stCgi.cMcc[3] = '\0';

    /* ȡMNC��һDIGIT */
    ucDigit     = (pstNwInfo->stPlmnId.ulMnc & 0xff);
    pstImsaImsInputEvt->evt.stInputParaEvent.u.stCgi.cMnc[0]
                = IMSA_ConverterDigit2Chacter(ucDigit);

    /* ȡMNC�ڶ�DIGIT */
    ucDigit     = (pstNwInfo->stPlmnId.ulMnc & 0xff00) >> IMSA_MOVEMENT_8;
    pstImsaImsInputEvt->evt.stInputParaEvent.u.stCgi.cMnc[1]
                = IMSA_ConverterDigit2Chacter(ucDigit);

    /* ȡMNC����DIGIT */
    if ((pstNwInfo->stPlmnId.ulMnc & 0xff0000) != 0x0f0000)
    {
        ucDigit = (pstNwInfo->stPlmnId.ulMnc & 0xff0000) >> IMSA_MOVEMENT_16;
        pstImsaImsInputEvt->evt.stInputParaEvent.u.stCgi.cMnc[2]
                = IMSA_ConverterDigit2Chacter(ucDigit);

        pstImsaImsInputEvt->evt.stInputParaEvent.u.stCgi.cMnc[3] = '\0';
    }
    else
    {
        pstImsaImsInputEvt->evt.stInputParaEvent.u.stCgi.cMnc[2] = '\0';
    }

    pstImsaImsInputEvt->evt.stInputParaEvent.u.stCgi.usLac
                = pstNwInfo->usLac;
    pstImsaImsInputEvt->evt.stInputParaEvent.u.stCgi.usTac
                = pstNwInfo->usTac;
    pstImsaImsInputEvt->evt.stInputParaEvent.u.stCgi.ulCellId
                = pstNwInfo->ulCellId;
}


VOS_VOID IMSA_ConverterImeiParam2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
)
{
    IMSA_ENTITY_STRU                   *pstImsaEntity = IMSA_CtxGet();

    IMSA_INFO_LOG("IMSA_ConverterImeiParam2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConverterImeiParam2Ims_ENUM, LNAS_ENTRY);

    pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_PARA;

    pstImsaImsInputEvt->evt.stInputParaEvent.ulOpId = IMSA_AllocImsOpId();
    pstImsaImsInputEvt->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_SET_IMEI;

    IMSA_MEM_CPY(   pstImsaImsInputEvt->evt.stInputParaEvent.u.cImei,
                    pstImsaEntity->stImsaControlManager.stImsaCommonInfo.stImsaUeId.acImei,
                    IMSA_IMS_IMEI_LEN + 1);
}

VOS_UINT32 IMSA_ConverterSipInfo2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
)
{
    IMS_PARM_SIP_STRU     stNvImsConfig;
    VOS_UINT32                      ulRslt = VOS_ERR;

    IMSA_INFO_LOG("IMSA_ConverterSipInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConverterSipInfo2Ims_ENUM, LNAS_ENTRY);

    ulRslt = IMSA_NV_Read(EN_NV_ID_IMS_SIP_CONFIG,&stNvImsConfig,\
                 sizeof(IMS_PARM_SIP_STRU));


    if(ulRslt == VOS_OK)
    {
        pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_NV_INFO;

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.ulOpId = IMSA_AllocImsOpId();

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.enInputNvInfoReason = IMSA_IMS_INPUT_NV_INFO_REASON_SIP;

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.ulNvInfoLen = sizeof(IMS_PARM_SIP_STRU);

        /*lint -e419*/
        IMSA_MEM_CPY(   pstImsaImsInputEvt->evt.stInputNvInfoEvent.aucNvInfo,
                        &stNvImsConfig,
                        sizeof(IMS_PARM_SIP_STRU));
        /*lint +e419*/
    }
    return ulRslt;

}


VOS_UINT32 IMSA_ConverterVoipInfo2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
)
{
    IMS_PARM_VOIP_STRU    stNvImsVoipConfig;
    VOS_UINT32                      ulRslt = VOS_ERR;

    IMSA_INFO_LOG("IMSA_ConverterVoipInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConverterVoipInfo2Ims_ENUM, LNAS_ENTRY);

    ulRslt = IMSA_NV_Read(EN_NV_ID_IMS_VOIP_CONFIG,&stNvImsVoipConfig,\
                 sizeof(IMS_PARM_VOIP_STRU));


    if (ulRslt == VOS_OK)
    {
        pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_NV_INFO;

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.ulOpId = IMSA_AllocImsOpId();

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.enInputNvInfoReason = IMSA_IMS_INPUT_NV_INFO_REASON_VOIP;

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.ulNvInfoLen = sizeof(IMS_PARM_VOIP_STRU);

        /*lint -e419*/
        IMSA_MEM_CPY(   pstImsaImsInputEvt->evt.stInputNvInfoEvent.aucNvInfo,
                        &stNvImsVoipConfig,
                        sizeof(IMS_PARM_VOIP_STRU));
        /*lint +e419*/
    }
    return ulRslt;

}

VOS_UINT32 IMSA_ConverterCodeInfo2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
)
{
    IMS_PARM_VOIP_CODE_STRU    stNvImsCodeConfig;
    VOS_UINT32                      ulRslt = VOS_ERR;

    IMSA_INFO_LOG("IMSA_ConverterCodeInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConverterCodeInfo2Ims_ENUM, LNAS_ENTRY);

    ulRslt = IMSA_NV_Read(EN_NV_ID_IMS_CODE_CONFIG,&stNvImsCodeConfig,\
                 sizeof(IMS_PARM_VOIP_CODE_STRU));

    if(ulRslt == VOS_OK)
    {
        pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_NV_INFO;

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.ulOpId = IMSA_AllocImsOpId();

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.enInputNvInfoReason = IMSA_IMS_INPUT_NV_INFO_REASON_CODE;

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.ulNvInfoLen = sizeof(IMS_PARM_VOIP_CODE_STRU);

        /*lint -e419*/
        IMSA_MEM_CPY(   pstImsaImsInputEvt->evt.stInputNvInfoEvent.aucNvInfo,
                        &stNvImsCodeConfig,
                        sizeof(IMS_PARM_VOIP_CODE_STRU));
        /*lint +e419*/
    }

    return ulRslt;
}

VOS_UINT32 IMSA_ConverterSsConfInfo2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
)
{
    IMS_PARM_SS_CONF_STRU stNvImsSsConfConfig;
    VOS_UINT32                      ulRslt = VOS_ERR;

    IMSA_INFO_LOG("IMSA_ConverterSsConfInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConverterSsConfInfo2Ims_ENUM, LNAS_ENTRY);

    ulRslt = IMSA_NV_Read(EN_NV_ID_IMS_SS_CONF_CONFIG,&stNvImsSsConfConfig,\
                 sizeof(IMS_PARM_SS_CONF_STRU));

    if(ulRslt == VOS_OK)
    {
        pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_NV_INFO;

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.ulOpId = IMSA_AllocImsOpId();

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.enInputNvInfoReason = IMSA_IMS_INPUT_NV_INFO_REASON_SS_CONF;

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.ulNvInfoLen = sizeof(IMS_PARM_SS_CONF_STRU);

        /*lint -e419*/
        IMSA_MEM_CPY(   pstImsaImsInputEvt->evt.stInputNvInfoEvent.aucNvInfo,
                        &stNvImsSsConfConfig,
                        sizeof(IMS_PARM_SS_CONF_STRU));
        /*lint +e419*/

    }

    return ulRslt;
}

VOS_UINT32 IMSA_ConverterSecurityInfo2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
)
{
    IMS_PARM_SECURITY_STRU        stNvImsSecurityConfig;
    VOS_UINT32                      ulRslt = VOS_ERR;

    IMSA_INFO_LOG("IMSA_ConverterSecurityInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConverterSecurityInfo2Ims_ENUM, LNAS_ENTRY);

    ulRslt = IMSA_NV_Read(EN_NV_ID_IMS_SECURITY_CONFIG,&stNvImsSecurityConfig,\
                 sizeof(IMS_PARM_SECURITY_STRU));

    if(ulRslt == VOS_OK)
    {
        pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_NV_INFO;

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.ulOpId = IMSA_AllocImsOpId();

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.enInputNvInfoReason = IMSA_IMS_INPUT_NV_INFO_REASON_SECURITY;

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.ulNvInfoLen = sizeof(IMS_PARM_SECURITY_STRU);

        /*lint -e419*/
        IMSA_MEM_CPY(   pstImsaImsInputEvt->evt.stInputNvInfoEvent.aucNvInfo,
                        &stNvImsSecurityConfig,
                        sizeof(IMS_PARM_SECURITY_STRU));
        /*lint +e419*/
    }

    return ulRslt;
}


VOS_UINT32 IMSA_ConverterMediaParmInfo2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
)
{
    IMS_PARM_MEDIA_STRU        stNvImsMediaParmConfig;
    VOS_UINT32                      ulRslt = VOS_ERR;

    IMSA_INFO_LOG("IMSA_ConverterMediaParmInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConverterMediaParmInfo2Ims_ENUM, LNAS_ENTRY);

    ulRslt = IMSA_NV_Read(EN_NV_ID_IMS_MEDIA_PARM_CONFIG,&stNvImsMediaParmConfig,\
                 sizeof(IMS_PARM_MEDIA_STRU));

    if(ulRslt == VOS_OK)
    {
        pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_NV_INFO;

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.ulOpId = IMSA_AllocImsOpId();

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.enInputNvInfoReason = IMSA_IMS_INPUT_NV_INFO_REASON_MEDIA;

        pstImsaImsInputEvt->evt.stInputNvInfoEvent.ulNvInfoLen = sizeof(IMS_PARM_MEDIA_STRU);

        /*lint -e419*/
        IMSA_MEM_CPY(   pstImsaImsInputEvt->evt.stInputNvInfoEvent.aucNvInfo,
                        &stNvImsMediaParmConfig,
                        sizeof(IMS_PARM_MEDIA_STRU));
        /*lint +e419*/
    }

    return ulRslt;
}


/*lint +e516*/
/*lint +e718*/
/*lint +e732*/

VOS_VOID IMSA_ConverterRetyrTimeParam2Ims
(
    VOS_UINT32                          ulRetryTimerLen,
    VOS_UINT32                          ulPeriodRergisterTimerLen,
    IMSA_IMS_INPUT_EVENT_STRU          *pstImsaImsInputEvt
)
{
    IMSA_INFO_LOG("IMSA_ConverterRetyrTimeParam2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConverterRetyrTimeParam2Ims_ENUM, LNAS_ENTRY);

    pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_PARA;

    pstImsaImsInputEvt->evt.stInputParaEvent.ulOpId = IMSA_AllocImsOpId();
    pstImsaImsInputEvt->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_SET_TIMER_LENGTH;

    pstImsaImsInputEvt->evt.stInputParaEvent.u.stTimerLength.ulRetryTimerLength
                = ulRetryTimerLen;
    pstImsaImsInputEvt->evt.stInputParaEvent.u.stTimerLength.ulPeriodRergisterTimerLength
                = ulPeriodRergisterTimerLen;
}



VOS_VOID IMSA_ConfigCgi2Ims( VOS_VOID )
{
    IMSA_IMS_INPUT_EVENT_STRU          *pstImsaImsInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_ConfigCgi2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConfigCgi2Ims_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ConfigCgi2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ConfigCgi2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_ConverterCgiParam2Ims(pstImsaImsInputEvent);

    IMSA_SndImsMsgParaEvent(pstImsaImsInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}


VOS_VOID IMSA_ConfigImei2Ims( VOS_VOID )
{
    IMSA_IMS_INPUT_EVENT_STRU                    *pstImsaImsInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_ConfigImei2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConfigImei2Ims_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ConfigImei2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ConfigImei2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_ConverterImeiParam2Ims(pstImsaImsInputEvent);

    IMSA_SndImsMsgParaEvent(pstImsaImsInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}


VOS_VOID IMSA_ConfigSipInfo2Ims( VOS_VOID )
{
    IMSA_IMS_INPUT_EVENT_STRU           *pstImsaImsInputEvent = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt = VOS_ERR;
    VOS_UINT32                          ulInputEventLen = 0;

    IMSA_INFO_LOG("IMSA_ConfigSipInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConfigSipInfo2Ims_ENUM, LNAS_ENTRY);

    ulInputEventLen = sizeof(IMSA_IMS_INPUT_EVENT_STRU) + sizeof(IMS_PARM_SIP_STRU)-IMSA_NV_INFO_LEN ;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(ulInputEventLen);

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ConfigSipInfo2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ConfigSipInfo2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    /*lint --e{669}*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, ulInputEventLen);

    ulRslt = IMSA_ConverterSipInfo2Ims(pstImsaImsInputEvent);

    /* ֻ�ж�ȡNV�ɹ����Ÿ�IMS ���� */
    if (VOS_OK == ulRslt)
    {
        IMSA_SndImsMsgNvInfoEvent(pstImsaImsInputEvent,sizeof(IMS_PARM_SIP_STRU));
    }

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}

VOS_VOID IMSA_ConfigVoipInfo2Ims( VOS_VOID )
{
    IMSA_IMS_INPUT_EVENT_STRU           *pstImsaImsInputEvent = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt = VOS_ERR;

    VOS_UINT32                          ulInputEventLen = 0;

    IMSA_INFO_LOG("IMSA_ConfigVoipInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConfigVoipInfo2Ims_ENUM, LNAS_ENTRY);

    ulInputEventLen = sizeof(IMSA_IMS_INPUT_EVENT_STRU) + sizeof(IMS_PARM_VOIP_STRU)-IMSA_NV_INFO_LEN;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(ulInputEventLen);

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ConfigVoipInfo2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ConfigVoipInfo2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/

    /*lint --e{669}*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, ulInputEventLen);

    ulRslt = IMSA_ConverterVoipInfo2Ims(pstImsaImsInputEvent);

    /* ֻ�ж�ȡNV�ɹ����Ÿ�IMS ���� */
    if (VOS_OK == ulRslt)
    {
        IMSA_SndImsMsgNvInfoEvent(pstImsaImsInputEvent,sizeof(IMS_PARM_VOIP_STRU));
    }

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}


VOS_VOID IMSA_ConfigCodeInfo2Ims( VOS_VOID )
{
    IMSA_IMS_INPUT_EVENT_STRU           *pstImsaImsInputEvent = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt = VOS_ERR;
    VOS_UINT32                          ulInputEventLen = 0;

    IMSA_INFO_LOG("IMSA_ConfigCodeInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConfigCodeInfo2Ims_ENUM, LNAS_ENTRY);

    ulInputEventLen = sizeof(IMSA_IMS_INPUT_EVENT_STRU) + sizeof(IMS_PARM_VOIP_CODE_STRU)-IMSA_NV_INFO_LEN ;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(ulInputEventLen);

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ConfigCodeInfo2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ConfigCodeInfo2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    /*lint --e{669}*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, ulInputEventLen);

    ulRslt = IMSA_ConverterCodeInfo2Ims(pstImsaImsInputEvent);

    /* ֻ�ж�ȡNV�ɹ����Ÿ�IMS ���� */
    if (VOS_OK == ulRslt)
    {
        IMSA_SndImsMsgNvInfoEvent(pstImsaImsInputEvent,sizeof(IMS_PARM_VOIP_CODE_STRU));
    }

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}

VOS_VOID IMSA_ConfigSsConfInfo2Ims( VOS_VOID )
{
    IMSA_IMS_INPUT_EVENT_STRU           *pstImsaImsInputEvent = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt = VOS_ERR;
    VOS_UINT32                          ulInputEventLen = 0;

    IMSA_INFO_LOG("IMSA_ConfigSsConfInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConfigSsConfInfo2Ims_ENUM, LNAS_ENTRY);


    ulInputEventLen = sizeof(IMSA_IMS_INPUT_EVENT_STRU) + sizeof(IMS_PARM_SS_CONF_STRU)-IMSA_NV_INFO_LEN ;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(ulInputEventLen);

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ConfigSsConfInfo2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ConfigSsConfInfo2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    /*lint --e{669}*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, ulInputEventLen);

    ulRslt = IMSA_ConverterSsConfInfo2Ims(pstImsaImsInputEvent);

    /* ֻ�ж�ȡNV�ɹ����Ÿ�IMS ���� */
    if (VOS_OK == ulRslt)
    {
        IMSA_SndImsMsgNvInfoEvent(pstImsaImsInputEvent,sizeof(IMS_PARM_SS_CONF_STRU));
    }

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}

VOS_VOID IMSA_ConfigSecurityInfo2Ims( VOS_VOID )
{
    IMSA_IMS_INPUT_EVENT_STRU           *pstImsaImsInputEvent = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt = VOS_ERR;
    VOS_UINT32                          ulInputEventLen = 0;

    IMSA_INFO_LOG("IMSA_ConfigSecurityInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConfigSecurityInfo2Ims_ENUM, LNAS_ENTRY);


    ulInputEventLen = sizeof(IMSA_IMS_INPUT_EVENT_STRU) + sizeof(IMS_PARM_SECURITY_STRU)-IMSA_NV_INFO_LEN ;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(ulInputEventLen);

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ConfigSecurityInfo2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ConfigSecurityInfo2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    /*lint --e{669}*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, ulInputEventLen);

    ulRslt = IMSA_ConverterSecurityInfo2Ims(pstImsaImsInputEvent);

    /* ֻ�ж�ȡNV�ɹ����Ÿ�IMS ���� */
    if (VOS_OK == ulRslt)
    {
        IMSA_SndImsMsgNvInfoEvent(pstImsaImsInputEvent,sizeof(IMS_PARM_SECURITY_STRU));
    }

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}


VOS_VOID IMSA_ConfigMediaParmInfo2Ims( VOS_VOID )
{
    IMSA_IMS_INPUT_EVENT_STRU           *pstImsaImsInputEvent = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt = VOS_ERR;
    VOS_UINT32                          ulInputEventLen = 0;

    IMSA_INFO_LOG("IMSA_ConfigMediaParmInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConfigMediaParmInfo2Ims_ENUM, LNAS_ENTRY);


    ulInputEventLen = sizeof(IMSA_IMS_INPUT_EVENT_STRU) + sizeof(IMS_PARM_MEDIA_STRU)-IMSA_NV_INFO_LEN ;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(ulInputEventLen);

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ConfigMediaParmInfo2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ConfigMediaParmInfo2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    /*lint --e{669}*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, ulInputEventLen);

    ulRslt = IMSA_ConverterMediaParmInfo2Ims(pstImsaImsInputEvent);

    /* ֻ�ж�ȡNV�ɹ����Ÿ�IMS ���� */
    if (VOS_OK == ulRslt)
    {
        IMSA_SndImsMsgNvInfoEvent(pstImsaImsInputEvent,sizeof(IMS_PARM_MEDIA_STRU));
    }

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}



VOS_VOID IMSA_ConfigTimerLength2Ims( VOS_VOID )
{
    IMSA_IMS_INPUT_EVENT_STRU          *pstImsaImsInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_ConfigTimerLength2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConfigTimerLength2Ims_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_RegConfigRetryTime2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ConfigTimerLength2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_ConverterRetyrTimeParam2Ims(0, 0, pstImsaImsInputEvent);

    IMSA_SndImsMsgParaEvent(pstImsaImsInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}


VOS_VOID IMSA_ConfigSipPort2Ims( VOS_VOID )
{
    IMSA_IMS_INPUT_EVENT_STRU          *pstImsaImsInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_ConfigSipPort2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConfigSipPort2Ims_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ConfigSipPort2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ConfigSipPort2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_ConverterSipPort2Ims(pstImsaImsInputEvent);

    IMSA_SndImsMsgParaEvent(pstImsaImsInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}

VOS_VOID IMSA_ConverterSipPort2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU          *pstImsaImsInputEvt
)
{
    IMSA_ENTITY_STRU *pstImsaEntity = IMSA_CtxGet();

    IMSA_INFO_LOG("IMSA_ConverterSipPort2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConverterSipPort2Ims_ENUM, LNAS_ENTRY);

    pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_PARA;

    pstImsaImsInputEvt->evt.stInputParaEvent.ulOpId = IMSA_AllocImsOpId();
    pstImsaImsInputEvt->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_SET_PORTS;

    pstImsaImsInputEvt->evt.stInputParaEvent.u.stPortInfo.usMinPort
                = pstImsaEntity->stImsaControlManager.stImsaConfigPara.stImsPortConfig.usImsMinPort;

    pstImsaImsInputEvt->evt.stInputParaEvent.u.stPortInfo.usMaxPort
                = pstImsaEntity->stImsaControlManager.stImsaConfigPara.stImsPortConfig.usImsMaxPort;
}



VOS_VOID IMSA_ConverterUeCapParam2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
)
{
    IMSA_ENTITY_STRU *pstImsaEntity = IMSA_CtxGet();

    IMSA_INFO_LOG("IMSA_ConverterUeCapParam2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConverterUeCapParam2Ims_ENUM, LNAS_ENTRY);

    /* ���������¼����� */
    pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_PARA;

    /* ��������Reason��opid */
    pstImsaImsInputEvt->evt.stInputParaEvent.ulOpId = IMSA_AllocImsOpId();

    pstImsaImsInputEvt->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_SET_UE_CAPABILITIES;

    /* ���UeCapability���� */
    pstImsaImsInputEvt->evt.stInputParaEvent.u.stUeCapability.ucVoiceCall =
        pstImsaEntity->stImsaControlManager.stImsaConfigPara.ucVoiceCallOnImsSupportFlag;

    pstImsaImsInputEvt->evt.stInputParaEvent.u.stUeCapability.ucVideoCall =
        pstImsaEntity->stImsaControlManager.stImsaConfigPara.ucVideoCallOnImsSupportFlag;

    pstImsaImsInputEvt->evt.stInputParaEvent.u.stUeCapability.ucSms =
        pstImsaEntity->stImsaControlManager.stImsaConfigPara.ucSmsOnImsSupportFlag;

    pstImsaImsInputEvt->evt.stInputParaEvent.u.stUeCapability.ucSrvcc =
        pstImsaEntity->stImsaControlManager.stImsaConfigPara.ucSrvccOnImsSupportFlag;

    pstImsaImsInputEvt->evt.stInputParaEvent.u.stUeCapability.ucSrvccMidCall =
        pstImsaEntity->stImsaControlManager.stImsaConfigPara.ucSrvccMidCallOnImsSupportFlag;

    pstImsaImsInputEvt->evt.stInputParaEvent.u.stUeCapability.ucSrvccAlerting =
        pstImsaEntity->stImsaControlManager.stImsaConfigPara.ucSrvccAlertingOnImsSupportFlag;

    pstImsaImsInputEvt->evt.stInputParaEvent.u.stUeCapability.ucSrvccPreAlerting =
        pstImsaEntity->stImsaControlManager.stImsaConfigPara.ucSrvccPreAlertingOnImsSupportFlag;

    pstImsaImsInputEvt->evt.stInputParaEvent.u.stUeCapability.ucSrvccTiFlag =
        pstImsaEntity->stImsaControlManager.stImsaConfigPara.ucSrvccTiFlag;

    pstImsaImsInputEvt->evt.stInputParaEvent.u.stUeCapability.ucCallWaiting = VOS_TRUE;
}
VOS_VOID IMSA_ConverterNetCapParam2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
)
{
    IMSA_NETWORK_INFO_STRU             *pstNwInfo           = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_ConverterNetCapParam2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConverterNetCapParam2Ims_ENUM, LNAS_ENTRY);

    pstNwInfo                               = IMSA_GetNetInfoAddress();

    /* ���������¼����� */
    pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_PARA;

    /* ��������Reason��opid */
    pstImsaImsInputEvt->evt.stInputParaEvent.ulOpId = IMSA_AllocImsOpId();

    pstImsaImsInputEvt->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_SET_NETWORK_CAPABILITIES;

    /* ���Net Capability���� */
    if (IMSA_IMS_VOPS_STATUS_SUPPORT == pstNwInfo->enImsaImsVoPsStatus)
    {
        pstImsaImsInputEvt->evt.stInputParaEvent.u.stNetworkCapability.ucVoice = VOS_TRUE;
    }
    else
    {
        pstImsaImsInputEvt->evt.stInputParaEvent.u.stNetworkCapability.ucVoice = VOS_FALSE;
    }
    /* zhaochen 00308719 begin for sending RAT to IMS 2015-09-03 */
    switch (pstNwInfo->enImsaCampedRatType)
    {
        case IMSA_CAMPED_RAT_TYPE_EUTRAN:
            pstImsaImsInputEvt->evt.stInputParaEvent.u.stNetworkCapability.enNwRatType = IMSA_IMS_RAT_TYPE_LTE;
            break;
        case IMSA_CAMPED_RAT_TYPE_UTRAN:
            pstImsaImsInputEvt->evt.stInputParaEvent.u.stNetworkCapability.enNwRatType = IMSA_IMS_RAT_TYPE_UTRAN;
            break;
        case IMSA_CAMPED_RAT_TYPE_GSM:
            pstImsaImsInputEvt->evt.stInputParaEvent.u.stNetworkCapability.enNwRatType = IMSA_IMS_RAT_TYPE_GSM;
            break;
        default:
            pstImsaImsInputEvt->evt.stInputParaEvent.u.stNetworkCapability.enNwRatType = IMSA_IMS_RAT_TYPE_BUTT;
    }
    /* zhaochen 00308719 end for sending RAT to IMS 2015-09-03 */
}
VOS_VOID IMSA_ConfigUeCapabilityInfo2Ims( VOS_VOID )
{
    IMSA_IMS_INPUT_EVENT_STRU                    *pstImsaImsInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_ConfigUeCapabilityInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConfigUeCapabilityInfo2Ims_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ConfigUeCapabilityInfo2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ConfigUeCapabilityInfo2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_ConverterUeCapParam2Ims(pstImsaImsInputEvent);

    IMSA_SndImsMsgParaEvent(pstImsaImsInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}


VOS_VOID IMSA_ConfigNetCapInfo2Ims( VOS_VOID )
{
    IMSA_IMS_INPUT_EVENT_STRU                    *pstImsaImsInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_ConfigNetCapInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConfigNetCapInfo2Ims_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ConfigNetCapInfo2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ConfigNetCapInfo2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_ConverterNetCapParam2Ims(pstImsaImsInputEvent);

    IMSA_SndImsMsgParaEvent(pstImsaImsInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}


VOS_VOID IMSA_ConverterImsiParam2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType,
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
)
{
    IMSA_ENTITY_STRU *pstImsaEntity = IMSA_CtxGet();

    IMSA_INFO_LOG("IMSA_ConverterImsiParam2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConverterImsiParam2Ims_ENUM, LNAS_ENTRY);

    /* ���������¼����� */
    pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_PARA;

    /* ��������Reason��opid */
    pstImsaImsInputEvt->evt.stInputParaEvent.ulOpId = IMSA_AllocImsOpId();
    if (IMSA_REG_TYPE_NORMAL == enRegType)
    {
        pstImsaImsInputEvt->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_SET_NORMAL_ACCOUNT;

        /* ���Account���� */
        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stNormalAccount.acImpi,
            pstImsaEntity->stImsaControlManager.stImsaCommonInfo.stImsaUeId.stImpi.acImpi, IMSA_IMS_EVENT_STRING_SZ);

        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stNormalAccount.acImpu,
            pstImsaEntity->stImsaControlManager.stImsaCommonInfo.stImsaUeId.stTImpu.acTImpu, IMSA_IMS_EVENT_STRING_SZ);

        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stNormalAccount.acDomain,
            pstImsaEntity->stImsaControlManager.stImsaCommonInfo.stHomeNetDomainName.acHomeNetDomainName, IMSA_IMS_EVENT_STRING_SZ);

        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stNormalAccount.acPassword,
            pstImsaEntity->stImsaControlManager.stImsaConfigPara.aucPassWord, IMSA_IMS_EVENT_STRING_SZ);

        if (IMSA_AUTH_TYPE_AKA == pstImsaEntity->stImsaControlManager.stImsaConfigPara.ucAuthType)
        {
            pstImsaImsInputEvt->evt.stInputParaEvent.u.stNormalAccount.enAuthType
                                    = IMSA_IMS_AUTH_TYPE_AKA;
        }
        else if (IMSA_AUTH_TYPE_DIGIST == pstImsaEntity->stImsaControlManager.stImsaConfigPara.ucAuthType)
        {
            pstImsaImsInputEvt->evt.stInputParaEvent.u.stNormalAccount.enAuthType
                                    = IMSA_IMS_AUTH_TYPE_DIGIST;
        }
        else
        {
            pstImsaImsInputEvt->evt.stInputParaEvent.u.stNormalAccount.enAuthType
                                    = IMSA_IMS_AUTH_TYPE_AKA_IPSEC;
        }
    }
    else
    {
        pstImsaImsInputEvt->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_SET_EMC_ACCOUNT;

        /* ���Account���� */
        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stEmcAccount.acImpi,
            pstImsaEntity->stImsaControlManager.stImsaCommonInfo.stImsaUeId.stImpi.acImpi, IMSA_IMS_EVENT_STRING_SZ);

        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stEmcAccount.acImpu,
            pstImsaEntity->stImsaControlManager.stImsaCommonInfo.stImsaUeId.stTImpu.acTImpu, IMSA_IMS_EVENT_STRING_SZ);

        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stEmcAccount.acDomain,
            pstImsaEntity->stImsaControlManager.stImsaCommonInfo.stHomeNetDomainName.acHomeNetDomainName, IMSA_IMS_EVENT_STRING_SZ);

        IMSA_UtilStrNCpy(pstImsaImsInputEvt->evt.stInputParaEvent.u.stEmcAccount.acPassword,
            pstImsaEntity->stImsaControlManager.stImsaConfigPara.aucPassWord, IMSA_IMS_EVENT_STRING_SZ);

        if (IMSA_AUTH_TYPE_AKA == pstImsaEntity->stImsaControlManager.stImsaConfigPara.ucAuthType)
        {
            pstImsaImsInputEvt->evt.stInputParaEvent.u.stEmcAccount.enAuthType
                                    = IMSA_IMS_AUTH_TYPE_AKA;
        }
        else if (IMSA_AUTH_TYPE_DIGIST == pstImsaEntity->stImsaControlManager.stImsaConfigPara.ucAuthType)
        {
            pstImsaImsInputEvt->evt.stInputParaEvent.u.stEmcAccount.enAuthType
                                    = IMSA_IMS_AUTH_TYPE_DIGIST;
        }
        else
        {
            pstImsaImsInputEvt->evt.stInputParaEvent.u.stEmcAccount.enAuthType
                                    = IMSA_IMS_AUTH_TYPE_AKA_IPSEC;
        }
    }
}


VOS_VOID IMSA_ConfigAccoutInfo2Ims
(
    IMSA_REG_TYPE_ENUM_UINT8            enRegType
)
{
    IMSA_IMS_INPUT_EVENT_STRU                    *pstImsaImsInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_ConfigAccoutInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConfigAccoutInfo2Ims_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ConfigAccoutInfo2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ConfigAccoutInfo2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_ConverterImsiParam2Ims(enRegType, pstImsaImsInputEvent);

    IMSA_SndImsMsgParaEvent(pstImsaImsInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}


VOS_VOID IMSA_Send_Intra_Msg(VOS_VOID* pIntraMsg)
{
    IMSA_PrintImsaSendMsg((const PS_MSG_HEADER_STRU *)pIntraMsg,
                              IMSA_GET_IMSA_PRINT_BUF());
    if(VOS_OK !=  IMSA_SndIntraMsg((pIntraMsg)))
    {
        IMSA_ERR_LOG("IMSA_SEND_INTRA_MSG  ERR!!");
        TLPS_PRINT2LAYER_ERROR(IMSA_Send_Intra_Msg_ENUM, LNAS_ERROR);
    }
}

VOS_VOID IMSA_Send_Msg(VOS_VOID* pMsg)
{
    IMSA_PrintImsaSendMsg((const PS_MSG_HEADER_STRU *)pMsg,IMSA_GET_IMSA_PRINT_BUF());
    if(VOS_OK != PS_SND_MSG_ALL_CHECK(PS_PID_IMSA , pMsg))
    {
        IMSA_ERR_LOG("IMSA_SND_MSG:Msg Snd Err!");
    }
}

VOS_VOID IMSA_Send_Msg_Normally(VOS_VOID* pMsg)
{
    IMSA_PrintImsaSendMsg((const PS_MSG_HEADER_STRU *)pMsg,IMSA_GET_IMSA_PRINT_BUF());
    #if (VOS_OS_VER != VOS_WIN32)
    if(VOS_OK != VOS_SendMsgNormally(PS_PID_IMSA , pMsg))
    #else
    if(VOS_OK != PS_SND_MSG_ALL_CHECK(PS_PID_IMSA , pMsg))
    #endif
    {
        IMSA_ERR_LOG("IMSA_SND_MSG_Nomally:Msg Snd Err!");
    }
}



VOS_UINT32 IMSA_IsImsVoiceContidionSatisfied( VOS_VOID )
{
    IMSA_CONTROL_MANAGER_STRU          *pstControlMagnaer   = VOS_NULL_PTR;

    pstControlMagnaer                       = IMSA_GetControlManagerAddress();

    IMSA_INFO_LOG2("IMSA_IsImsVoiceContidionSatisfied:NV IMS = ,IMS voice = ",
                pstControlMagnaer->stImsaConfigPara.ucLteImsSupportFlag,
                pstControlMagnaer->stImsaConfigPara.ucVoiceCallOnImsSupportFlag);
    TLPS_PRINT2LAYER_INFO1(IMSA_IsImsVoiceContidionSatisfied_ENUM, IMSA_NV_IMS, pstControlMagnaer->stImsaConfigPara.ucLteImsSupportFlag);
    TLPS_PRINT2LAYER_INFO1(IMSA_IsImsVoiceContidionSatisfied_ENUM, IMSA_IMS_VOICE, pstControlMagnaer->stImsaConfigPara.ucLteImsSupportFlag);

    IMSA_INFO_LOG2("IMSA_IsImsVoiceContidionSatisfied:voice domain = ,nw IMS voice = ",
                pstControlMagnaer->stImsaConfigPara.enVoiceDomain,
                IMSA_GetNwImsVoiceCap());
    TLPS_PRINT2LAYER_INFO1(IMSA_IsImsVoiceContidionSatisfied_ENUM, IMSA_VOICE_DOMAIN, pstControlMagnaer->stImsaConfigPara.enVoiceDomain);
    TLPS_PRINT2LAYER_INFO1(IMSA_IsImsVoiceContidionSatisfied_ENUM, IMSA_IMS_VOICE, IMSA_GetNwImsVoiceCap());

    IMSA_INFO_LOG1("IMSA_IsImsVoiceContidionSatisfied:IMSA REG STATE = ",
                IMSA_SRV_GetNormalSrvStatus());
    TLPS_PRINT2LAYER_INFO1(IMSA_IsImsVoiceContidionSatisfied_ENUM, IMSA_REG_STATE, IMSA_SRV_GetNormalSrvStatus());

    if ((VOS_TRUE == pstControlMagnaer->stImsaConfigPara.ucLteImsSupportFlag)
        && (VOS_TRUE == pstControlMagnaer->stImsaConfigPara.ucVoiceCallOnImsSupportFlag)
        && (IMSA_VOICE_DOMAIN_CS_ONLY != pstControlMagnaer->stImsaConfigPara.enVoiceDomain)
        && (IMSA_IMS_VOPS_STATUS_SUPPORT == IMSA_GetNwImsVoiceCap())
        && (IMSA_SRV_STATUS_CONN_REG == IMSA_SRV_GetNormalSrvStatus()))
    {
        return IMSA_TRUE;
    }

    return IMSA_FALSE;
}


VOS_UINT32 IMSA_IsRegParaAvailable
(
    IMSA_CONN_TYPE_ENUM_UINT32      enConnType,
    VOS_CHAR                        *pacUeAddr,
    VOS_CHAR                        *pacPcscfAddr
)
{
    IMSA_REG_ENTITY_STRU               *pstRegEntity = VOS_NULL_PTR;
    IMSA_REG_ADDR_PAIR_STRU            *pstIpAddr;

    IMSA_INFO_LOG("IMSA_IsRegParaAvailable is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_IsRegParaAvailable_ENUM, LNAS_ENTRY);

    pstRegEntity = IMSA_RegEntityGetByType((IMSA_REG_TYPE_ENUM_UINT8)enConnType);

    pstIpAddr = pstRegEntity->stPairMgrCtx.pstIpv6List;

    /* ��������IPV6��ַ�ԣ��鿴�Ƿ񱸷ݵ�ע����Ϣ�Ƿ���Ч */
    while (VOS_NULL_PTR != pstIpAddr)
    {
        if ((0 ==VOS_StrCmp(pacUeAddr, pstIpAddr->acUeAddr))
            && (0 ==VOS_StrCmp(pacPcscfAddr, pstIpAddr->acPcscfAddr)))
        {
            return IMSA_TRUE;
        }
        pstIpAddr = pstIpAddr->pstNext;
    }

    pstIpAddr = pstRegEntity->stPairMgrCtx.pstIpv4List;

    /* ��������IPV4��ַ�ԣ��鿴�Ƿ񱸷ݵ�ע����Ϣ�Ƿ���Ч */
    while (VOS_NULL_PTR != pstIpAddr)
    {
        if ((0 ==VOS_StrCmp(pacUeAddr, pstIpAddr->acUeAddr))
            && (0 ==VOS_StrCmp(pacPcscfAddr, pstIpAddr->acPcscfAddr)))
        {
            return IMSA_TRUE;
        }
        pstIpAddr = pstIpAddr->pstNext;
    }

    return IMSA_FALSE;

}


VOS_UINT32 IMSA_SetCurrentPara
(
    IMSA_CONN_TYPE_ENUM_UINT32      enConnType,
    VOS_CHAR                        *pacUeAddr,
    VOS_CHAR                        *pacPcscfAddr
)
{
    IMSA_REG_ENTITY_STRU               *pstRegEntity        = IMSA_RegEntityGetByType((IMSA_REG_TYPE_ENUM_UINT8)enConnType);
    IMSA_REG_ADDR_PAIR_STRU            *pstIpAddr;

    IMSA_INFO_LOG("IMSA_SetCurrentPara is entered!");

    pstIpAddr = pstRegEntity->stPairMgrCtx.pstIpv6List;

    /* ��������IPV6��ַ�ԣ��鿴�Ƿ񱸷ݵ�ע����Ϣ�Ƿ���Ч */
    while (VOS_NULL_PTR != pstIpAddr)
    {
        if ((0 ==VOS_StrCmp(pacUeAddr, pstIpAddr->acUeAddr))
            && (0 ==VOS_StrCmp(pacPcscfAddr, pstIpAddr->acPcscfAddr)))
        {
            pstRegEntity->stPairMgrCtx.pstCurrent = pstIpAddr;
            return IMSA_TRUE;
        }
        pstIpAddr = pstIpAddr->pstNext;
    }

    pstIpAddr = pstRegEntity->stPairMgrCtx.pstIpv4List;

    /* ��������IPV4��ַ�ԣ��鿴�Ƿ񱸷ݵ�ע����Ϣ�Ƿ���Ч */
    while (VOS_NULL_PTR != pstIpAddr)
    {
        if ((0 ==VOS_StrCmp(pacUeAddr, pstIpAddr->acUeAddr))
            && (0 ==VOS_StrCmp(pacPcscfAddr, pstIpAddr->acPcscfAddr)))
        {
            pstRegEntity->stPairMgrCtx.pstCurrent = pstIpAddr;
            return IMSA_TRUE;
        }
        pstIpAddr = pstIpAddr->pstNext;
    }

    return IMSA_FALSE;
}


#if (FEATURE_ON == FEATURE_DSDS)

VOS_VOID IMSA_DSDS_Init(VOS_VOID)
{
    VOS_UINT32 ulLength = 0;

    IMSA_INFO_LOG("IMSA_DSDS_Init is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_DSDS_Init_ENUM, LNAS_ENTRY);

    ulLength = sizeof(IMSA_DSDS_MSG_COUNT_STRU)*IMSA_LRRC_SESSION_TYPE_BUTT;

    IMSA_MEM_SET(g_astImsaDsdsNotifyMsgNum, 0, ulLength);

    return;

}


VOS_INT32   IMSA_PrintErrcMsg
(
    VOS_CHAR                           *pcBuff,
    VOS_UINT16                          usOffset,
    VOS_UINT32                          ulMsgId
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulImsaErrcMsgNum;
    VOS_INT32                           ilOutPutLen         = 0;
    VOS_UINT16                          usTotalLen = usOffset;

    /* delay begin */
    PS_LOG_RETURN_SUCC();
    /* delay end */

    ulImsaErrcMsgNum = sizeof(g_astImsaErrcMsgIdArray)/sizeof(NAS_COMM_PRINT_MSG_LIST_STRU);

    for (ulLoop = 0; ulLoop < ulImsaErrcMsgNum; ulLoop++)
    {
        if (g_astImsaErrcMsgIdArray[ulLoop].ulId == ulMsgId)
        {
            break;
        }
    }

    if ( ulLoop < ulImsaErrcMsgNum )
    {
        NAS_COMM_nsprintf(
                    pcBuff,
                    usTotalLen,
                    (VOS_CHAR *)(g_astImsaErrcMsgIdArray[ulLoop].aucPrintString),
                    &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;

        NAS_COMM_nsprintf_1(pcBuff,
                               usTotalLen,
                               "[ TICK : %ld ]",
                               PS_GET_TICK(),
                              &ilOutPutLen);
        usTotalLen += (VOS_UINT16)ilOutPutLen;
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_PrintErrcMsg, Invalid enMsgId: ",
                              ulMsgId);
        TLPS_PRINT2LAYER_WARNING1(IMSA_PrintErrcMsg_ENUM, LNAS_MSG_INVALID, ulMsgId);
    }

    return (usTotalLen - usOffset);
}




VOS_VOID  IMSA_SendRrcDsdsBeginNotify(IMSA_LRRC_SESSION_TYPE_ENUM_UINT8  ucSessionType)
{
    IMSA_LRRC_BEGIN_SESSION_NOTIFY_STRU   *pstRrcBeginNotifyMsg;

    if(PS_FALSE == g_ulDsdsRFSharedFlag)
    {
        /*�����Ƶ�����عرգ��򲻽�������Ĵ���*/
        IMSA_INFO_LOG("IMSA_SendRrcDsdsBeginNotify: g_ulDsdsRFSharedFlag=PS_FALSE!!!");
        TLPS_PRINT2LAYER_INFO(IMSA_SendRrcDsdsBeginNotify_ENUM, IMSA_PS_SWITCH_OFF);
        return;
    }

    if(IMSA_LRRC_SESSION_TYPE_BUTT <= ucSessionType)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        IMSA_ERR_LOG("IMSA_SendRrcDsdsBeginNotify: INPUT PARA ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SendRrcDsdsBeginNotify_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    /* ����DOPRA��Ϣ */
    pstRrcBeginNotifyMsg = (VOS_VOID *) IMSA_ALLOC_MSG(sizeof(IMSA_LRRC_BEGIN_SESSION_NOTIFY_STRU));
    if(VOS_NULL_PTR == pstRrcBeginNotifyMsg)
    {
        return;
    }

    IMSA_INFO_LOG1("IMSA_SendRrcDsdsBeginNotify:DSDS Protection procedure begin,SessionType = ",ucSessionType);
    TLPS_PRINT2LAYER_INFO1(IMSA_SendRrcDsdsBeginNotify_ENUM, 3, ucSessionType);

    /* ����Ϊ0 */
    IMSA_MEM_SET(pstRrcBeginNotifyMsg,0,sizeof(IMSA_LRRC_BEGIN_SESSION_NOTIFY_STRU));

    /*��д��Ϣͷ*/
    IMSA_WRITE_LRRC_MSG_HEAD(pstRrcBeginNotifyMsg,ID_IMSA_LRRC_BEGIN_SESSION_NOTIFY,
                             sizeof(IMSA_LRRC_BEGIN_SESSION_NOTIFY_STRU));

    /* �����Ϣ�� */
    pstRrcBeginNotifyMsg->enSessionType            = ucSessionType;

    /* ����DOPRA��Ϣ */
    IMSA_SND_MSG(pstRrcBeginNotifyMsg);

    /*������begin��Ϣ�󣬽���Ӧsession type�ļ�����1*/
    g_astImsaDsdsNotifyMsgNum[ucSessionType].ulBeginMsgCnt++;

    return;
}


VOS_VOID  IMSA_SendRrcDsdsEndNotify(IMSA_LRRC_SESSION_TYPE_ENUM_UINT8  ucSessionType)
{
    IMSA_LRRC_END_SESSION_NOTIFY_STRU   *pstRrcEndNotifyMsg;

    if(PS_FALSE == g_ulDsdsRFSharedFlag)
    {
        /*�����Ƶ�����عرգ��򲻽�������Ĵ���*/
        IMSA_INFO_LOG("IMSA_SendRrcDsdsEndNotify: g_ulDsdsRFSharedFlag=PS_SWITCH_OFF!!!");
        TLPS_PRINT2LAYER_INFO(IMSA_SendRrcDsdsEndNotify_ENUM, IMSA_PS_SWITCH_OFF);
        return;
    }

    if(IMSA_LRRC_SESSION_TYPE_BUTT <= ucSessionType)
    {
        /* ��ӡ�쳣��ERROR_LEVEL */
        IMSA_ERR_LOG("IMSA_SendRrcDsdsEndNotify: INPUT PARA ERROR!!!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SendRrcDsdsEndNotify_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    /*��LNAS���̽����쳣���������������Ϣ�����뿪ʼ��Ϣ������ͬ����˵���Ѿ������˽�����Ϣ�������ظ�����*/
    if(g_astImsaDsdsNotifyMsgNum[ucSessionType].ulBeginMsgCnt <= g_astImsaDsdsNotifyMsgNum[ucSessionType].ulEndMsgCnt)
    {
        IMSA_INFO_LOG1("IMSA_SendRrcDsdsEndNotify: begin=end��session =",ucSessionType);
        TLPS_PRINT2LAYER_INFO1(IMSA_SendRrcDsdsEndNotify_ENUM, 3, ucSessionType);
        return;
    }

    /* ����DOPRA��Ϣ */
    pstRrcEndNotifyMsg = (VOS_VOID *) IMSA_ALLOC_MSG(sizeof(IMSA_LRRC_END_SESSION_NOTIFY_STRU));
    if(VOS_NULL_PTR == pstRrcEndNotifyMsg)
    {
        return;
    }

    IMSA_INFO_LOG1("IMSA_SendRrcDsdsEndNotify:DSDS Protection procedure end,SessionType = ",ucSessionType);
    TLPS_PRINT2LAYER_INFO1(IMSA_SendRrcDsdsEndNotify_ENUM, 4, ucSessionType);

    /* ����Ϊ0 */
    IMSA_MEM_SET(pstRrcEndNotifyMsg,0,sizeof(IMSA_LRRC_END_SESSION_NOTIFY_STRU));


    /*��д��Ϣͷ*/
    IMSA_WRITE_LRRC_MSG_HEAD(pstRrcEndNotifyMsg,ID_IMSA_LRRC_END_SESSION_NOTIFY,
                             sizeof(IMSA_LRRC_END_SESSION_NOTIFY_STRU));

    /* �����Ϣ�� */
    pstRrcEndNotifyMsg->enSessionType            = ucSessionType;

    /* ����DOPRA��Ϣ */
    IMSA_SND_MSG(pstRrcEndNotifyMsg);

    /*������end��Ϣ���򽫼�����1*/
    /*lint -e661*/
    g_astImsaDsdsNotifyMsgNum[ucSessionType].ulEndMsgCnt++;
    /*lint +e661*/

    return;
}

#endif
VOS_VOID IMSA_SndMtcSrvConnStatusNotify(VOS_UINT8 ucIsImsExist)
{
    IMSA_MTC_SRV_CONN_STATUS_NOTIFY_STRU           *pstImsaMtcSrvConnNotify;

    IMSA_INFO_LOG("IMSA_SndMtcSrvConnStatusNotify is enter!");
    TLPS_PRINT2LAYER_INFO(IMSA_SndMtcSrvConnStatusNotify_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaMtcSrvConnNotify = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_MTC_SRV_CONN_STATUS_NOTIFY_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstImsaMtcSrvConnNotify)
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SndMtcSrvConnStatusNotify:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndMtcSrvConnStatusNotify_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstImsaMtcSrvConnNotify), 0, IMSA_GET_MSG_LENGTH(pstImsaMtcSrvConnNotify));

    /*��д��Ϣͷ*/
    IMSA_WRITE_MTC_MSG_MSG_HEAD(pstImsaMtcSrvConnNotify, ID_IMSA_MTC_SRV_CONN_STATUS_NOTIFY);

    pstImsaMtcSrvConnNotify->enIsImsSrvExist = ucIsImsExist;

    /*������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstImsaMtcSrvConnNotify);
}


VOS_UINT32 IMSA_IsImsExist(VOS_VOID)
{
    if (VOS_TRUE == IMSA_IsCallConnExist())
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == IMSA_IsSmsConnExist())
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == IMSA_IsSsConnExist())
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

VOS_VOID IMSA_WhenImsSrvConnStatusChangeNotifyMtc(VOS_VOID)
{
    IMSA_CONTROL_MANAGER_STRU    *pstControlManager;

    VOS_UINT32     ulRst = VOS_FALSE;

    pstControlManager = IMSA_GetControlManagerAddress();

    ulRst = IMSA_IsImsExist();

    if (pstControlManager->enIsImsSrvExist != ulRst)
    {
        if (VOS_TRUE == ulRst)
        {
            pstControlManager->enIsImsSrvExist = IMSA_SRV_CONN_STATUS_IS_EXIST;
        }
        else
        {
            pstControlManager->enIsImsSrvExist = IMSA_SRV_CONN_STATUS_ISNOT_EXIST;
        }

        IMSA_SndMtcSrvConnStatusNotify(pstControlManager->enIsImsSrvExist);
    }
    else
    {

    }

}



VOS_VOID IMSA_ProcMtcMsgModem1InfoInd
(
    const VOS_VOID                     *pRcvMsg
)
{
    MTC_IMSA_MODEM1_INFO_IND_STRU *pstModem1InfoInd;

    pstModem1InfoInd = (MTC_IMSA_MODEM1_INFO_IND_STRU*)pRcvMsg;

    IMSA_INFO_LOG1("IMSA_ProcMtcMsgModem1InfoInd is entered!", pstModem1InfoInd->enPowerState);
    TLPS_PRINT2LAYER_INFO1(IMSA_ProcMtcMsgModem1InfoInd_ENUM, LNAS_ENTRY, pstModem1InfoInd->enPowerState);

    IMSA_GetPowerState() = pstModem1InfoInd->enPowerState;
    return;
}



VOS_UINT32 IMSA_IsCurrentAccessTypeSupportIms(VOS_VOID)
{

    VOS_UINT32                   ulResult           = VOS_TRUE;
    IMSA_NETWORK_INFO_STRU       *pstNwInfo         = VOS_NULL_PTR;
    IMSA_CONTROL_MANAGER_STRU    *pstControlManager = VOS_NULL_PTR;

    pstNwInfo             = IMSA_GetNetInfoAddress();
    pstControlManager     = IMSA_GetControlManagerAddress();

    IMSA_INFO_LOG1("IMSA_IsCurrentAccessTypeSupportIms: enAccessType=",pstNwInfo->enAccessType);
    TLPS_PRINT2LAYER_INFO1(IMSA_IsCurrentAccessTypeSupportIms_ENUM, 1, pstNwInfo->enAccessType);

    switch(pstNwInfo->enAccessType)
    {
    case MSCC_IMSA_ACCESS_TYPE_EUTRAN_TDD:
    case MSCC_IMSA_ACCESS_TYPE_EUTRAN_FDD:
        if ((VOS_FALSE == pstControlManager->stImsaConfigPara.ucLteEmsSupportFlag) &&
            (VOS_FALSE == pstControlManager->stImsaConfigPara.ucLteImsSupportFlag))
        {

            ulResult = VOS_FALSE;
        }
        break;
    case MSCC_IMSA_ACCESS_TYPE_UTRAN_TDD:
    case MSCC_IMSA_ACCESS_TYPE_UTRAN_FDD:
        if ((VOS_FALSE == pstControlManager->stImsaConfigPara.ucUtranEmsSupportFlag) &&
            (VOS_FALSE == pstControlManager->stImsaConfigPara.ucUtranImsSupportFlag))
        {
            ulResult = VOS_FALSE;
        }
        break;
    case MSCC_IMSA_ACCESS_TYPE_GERAN:
        if ((VOS_FALSE == pstControlManager->stImsaConfigPara.ucGsmEmsSupportFlag) &&
            (VOS_FALSE == pstControlManager->stImsaConfigPara.ucGsmImsSupportFlag))
        {
            ulResult = VOS_FALSE;
        }
        break;
    default:
        break;
    }

    return ulResult;
}
#if (FEATURE_ON == FEATURE_PTM)

VOS_UINT16 IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_ID_ENUM_UINT16 enAlmId)
{
    VOS_UINT16                          usTableLen;
    VOS_UINT16                          usStep;

    /* ��ȡTab���� */
    usTableLen = sizeof(g_astImsaErrAlmLevelTb)/sizeof(g_astImsaErrAlmLevelTb[0]);

    /* ����ض�ӦAlm ID��log�ȼ� */
    for (usStep = 0; usStep < usTableLen; usStep++)
    {
        if (g_astImsaErrAlmLevelTb[usStep].enAlmID == enAlmId)
        {
            return g_astImsaErrAlmLevelTb[usStep].usLogLevel;
        }
    }

    /* δ�鵽������δ����ȼ� */
    return IMSA_ERR_LOG_CTRL_LEVEL_NULL;
}
VOS_UINT32 IMSA_IsErrLogNeedRecord(VOS_UINT16 usLevel)
{
    /* Log���عرգ�����Ҫ�ϱ� */
    if (0 == IMSA_GetErrlogCtrlFlag())
    {
        IMSA_INFO_LOG1("IMSA_IsErrLogNeedRecord: IMSA_GetErrlogCtrlFlag=",IMSA_GetErrlogCtrlFlag());
        TLPS_PRINT2LAYER_INFO1(IMSA_IsErrLogNeedRecord_ENUM, 1, IMSA_GetErrlogCtrlFlag());
        return VOS_FALSE;
    }

    /* ģ��log����usLevel�����û����õ�log�ϱ������usLevel��Ч������Ҫ�ϱ� */
    if ((IMSA_GetErrlogAlmLevel() < usLevel)
     || (IMSA_ERR_LOG_CTRL_LEVEL_NULL == usLevel))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 IMSA_GetErrLogRingBufContent
(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    return (VOS_UINT32)OM_RingBufferGet(IMSA_GetErrorLogRingBufAddr(), pbuffer, (VOS_INT)ulbytes);
}


VOS_UINT32 IMSA_GetErrLogRingBufferUseBytes(VOS_VOID)
{
    return (VOS_UINT32)OM_RingBufferNBytes(IMSA_GetErrorLogRingBufAddr());
}


VOS_VOID IMSA_CleanErrLogRingBuf(VOS_VOID)
{
    OM_RingBufferFlush(IMSA_GetErrorLogRingBufAddr());

    return;
}

VOS_UINT32 IMSA_PutErrLogRingBuf
(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulbytes
)
{
    VOS_UINT32                          ulFreeSize;
    VOS_UINT32                          ulCount;
    OM_RING_ID                          pTafRingBuffer;

    pTafRingBuffer = IMSA_GetErrorLogRingBufAddr();
    if (VOS_NULL_PTR == pTafRingBuffer)
    {
        return 0;
    }

    /* ���д���RING BUFFER������д�� */
    if (ulbytes > IMSA_RING_BUFFER_SIZE)
    {
        return 0;
    }

    /* ��ȡRING BUFFERʣ��ռ��С */
    ulFreeSize = (VOS_UINT32)OM_RingBufferFreeBytes(pTafRingBuffer);

    ulCount = IMSA_GetErrlogOverflowCnt();
    /* ���ʣ��ռ䲻��д��Ĵ�С�������RING BUFFER */
    if (ulFreeSize < ulbytes)
    {
        ulCount++;
        IMSA_SetErrlogOverflowCnt(ulCount);

        OM_RingBufferFlush(pTafRingBuffer);
    }

    /* д��RING BUFFER */
    return (VOS_UINT32)OM_RingBufferPut(pTafRingBuffer, pbuffer, (VOS_INT)ulbytes);
}




IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8 IMSA_CallImsaState2ErrlogState(IMSA_CALL_STATUS_ENUM_UINT8 enImsaState)
{
    IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8 enNewState = IMSA_ERR_LOG_CALL_STATUS_BUTT;

    switch (enImsaState)
    {
    case IMSA_CALL_STATUS_ACTIVE:
        enNewState = IMSA_ERR_LOG_CALL_STATUS_ACTIVE;
        break;
    case IMSA_CALL_STATUS_HELD:
        enNewState = IMSA_ERR_LOG_CALL_STATUS_HELD;
        break;
    case IMSA_CALL_STATUS_TRYING:
        enNewState = IMSA_ERR_LOG_CALL_STATUS_TRYING;
        break;
    case IMSA_CALL_STATUS_DIALING:
        enNewState = IMSA_ERR_LOG_CALL_STATUS_DIALING;
        break;
    case IMSA_CALL_STATUS_ALERTING:
        enNewState = IMSA_ERR_LOG_CALL_STATUS_ALERTING;
        break;
    case IMSA_CALL_STATUS_INCOMING:
        enNewState = IMSA_ERR_LOG_CALL_STATUS_INCOMING;
        break;
    case IMSA_CALL_STATUS_WAITING:
        enNewState = IMSA_ERR_LOG_CALL_STATUS_WAITING;
        break;
    default:
        IMSA_ERR_LOG1("IMSA_CallImsaState2ErrlogState: invalid mapping state", enImsaState);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallImsaState2ErrlogState_ENUM, IMSA_STATE_ERROR, enImsaState);
    }

    return enNewState;
}

IMSA_ERR_LOG_REGISTER_REASON_ENUM_UINT8 IMSA_RegAddrType2ErrlogRegReason(IMSA_REG_ADDR_PARAM_ENUM_UINT32 enImsaRegAddr)
{
    IMSA_ERR_LOG_REGISTER_REASON_ENUM_UINT8 enImsaRegReason = IMSA_ERR_LOG_REGISTER_REASON_BUTT;

    switch (enImsaRegAddr)
    {
    case IMSA_REG_ADDR_PARAM_NEW:
        enImsaRegReason = IMSA_ERR_LOG_REGISTER_REASON_ADDR_PARAM_NEW;
        break;
    case IMSA_REG_ADDR_PARAM_SAME:
        enImsaRegReason = IMSA_ERR_LOG_REGISTER_REASON_ADDR_PARAM_SAME;
        break;
    case IMSA_REG_ADDR_PARAM_NEXT:
        enImsaRegReason = IMSA_ERR_LOG_REGISTER_REASON_ADDR_PARAM_NEXT;
        break;
    case IMSA_REG_ADDR_PARAM_RESTORATION:
        enImsaRegReason = IMSA_ERR_LOG_REGISTER_REASON_ADDR_PARAM_RESTORATION;
        break;
    default:
        IMSA_ERR_LOG1("IMSA_RegAddrType2ErrlogRegReason: invalid mapping state", enImsaRegAddr);
        TLPS_PRINT2LAYER_ERROR1(IMSA_RegAddrType2ErrlogRegReason_ENUM, IMSA_STATE_ERROR, enImsaRegAddr);
    }

    return enImsaRegReason;
}


IMSA_ERR_LOG_MPTY_STATE_ENUM_UINT8 IMSA_CallImsaMpty2ErrlogMpty(MN_CALL_MPTY_STATE_ENUM_UINT8 enImsaMpty)
{
    IMSA_ERR_LOG_MPTY_STATE_ENUM_UINT8 enNewMpty = IMSA_ERR_LOG_CALL_MPYT_STATE_BUTT;

    switch (enImsaMpty)
    {
    case MN_CALL_NOT_IN_MPTY:
        enNewMpty = IMSA_ERR_LOG_CALL_NOT_IN_MPTY;
        break;
    case MN_CALL_IN_MPTY:
        enNewMpty = IMSA_ERR_LOG_CALL_IN_MPTY;
        break;
    default:
        IMSA_ERR_LOG1("IMSA_CallImsaMpty2ErrlogMpty: invalid mapping state", enImsaMpty);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallImsaMpty2ErrlogMpty_ENUM, IMSA_STATE_ERROR, enImsaMpty);
    }

    return enNewMpty;
}

IMSA_ERR_LOG_REG_STATUS_ENUM_UINT8 IMSA_RegState2ErrlogState(IMSA_REG_STAUTS_ENUM_UINT8 enImsaRegState)
{
    IMSA_ERR_LOG_REG_STATUS_ENUM_UINT8 enRegState = IMSA_ERR_LOG_REG_STATUS_BUTT;

    switch (enImsaRegState)
    {
    case IMSA_REG_STATUS_NOT_REGISTER:
        enRegState = IMSA_ERR_LOG_REG_STATUS_NOT_REGISTER;
        break;
    case IMSA_REG_STATUS_REGISTERING:
        enRegState = IMSA_ERR_LOG_REG_STATUS_REGISTERING;
        break;
    case IMSA_REG_STATUS_REGISTERED:
        enRegState = IMSA_ERR_LOG_REG_STATUS_REGISTERED;
        break;
    case IMSA_REG_STATUS_DEREGING:
        enRegState = IMSA_ERR_LOG_REG_STATUS_DEREGING;
        break;
    case IMSA_REG_STATUS_WAIT_RETRY:
        enRegState = IMSA_ERR_LOG_REG_STATUS_WAIT_RETRY;
        break;
    case IMSA_REG_STATUS_PENDING:
        enRegState = IMSA_ERR_LOG_REG_STATUS_PENDING;
        break;
    case IMSA_REG_STATUS_ROLLING_BACK:
        enRegState = IMSA_ERR_LOG_REG_STATUS_ROLLING_BACK;
        break;
    default:
        IMSA_ERR_LOG1("IMSA_RegState2ErrlogState: invalid mapping state", enImsaRegState);
        TLPS_PRINT2LAYER_ERROR1(IMSA_RegState2ErrlogState_ENUM, IMSA_STATE_ERROR, enImsaRegState);
    }

    return enRegState;
}

IMSA_ERR_LOG_PS_SERVICE_STATUS_ENUM_UINT8 IMSA_PsSerStates2ErrlogPsStates
(
    IMSA_PS_SERVICE_STATUS_ENUM_UINT8 enImsaPsStates
)
{
    IMSA_ERR_LOG_PS_SERVICE_STATUS_ENUM_UINT8 enPsState = IMSA_ERR_LOG_PS_SERVICE_STATUS_BUTT;

    switch (enImsaPsStates)
    {
    case IMSA_PS_SERVICE_STATUS_NORMAL_SERVICE:
        enPsState = IMSA_ERR_LOG_PS_SERVICE_STATUS_NORMAL_SERVICE;
        break;
    case IMSA_PS_SERVICE_STATUS_LIMITED_SERVICE:
        enPsState = IMSA_ERR_LOG_PS_SERVICE_STATUS_LIMITED_SERVICE;
        break;
    case IMSA_PS_SERVICE_STATUS_NO_SERVICE:
        enPsState = IMSA_ERR_LOG_PS_SERVICE_STATUS_NO_SERVICE;
        break;
    default:
        IMSA_ERR_LOG1("IMSA_PsSerStates2ErrlogPsStates: invalid mapping state", enImsaPsStates);
        TLPS_PRINT2LAYER_ERROR1(IMSA_PsSerStates2ErrlogPsStates_ENUM, IMSA_STATE_ERROR, enImsaPsStates);
    }

    return enPsState;
}


IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM_UINT8 IMSA_ConnState2ErrlogConnState(IMSA_CONN_STATUS_ENUM_UINT8 enImsaConnState)
{
    IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM_UINT8 enConnState = IMSA_ERR_LOG_PDN_CONN_STATUS_BUTT;

    switch (enImsaConnState)
    {
    case IMSA_CONN_STATUS_IDLE:
        enConnState = IMSA_ERR_LOG_PDN_CONN_STATUS_IDLE;
        break;
    case IMSA_CONN_STATUS_CONNING:
        enConnState = IMSA_ERR_LOG_PDN_CONN_STATUS_CONNING;
        break;
    case IMSA_CONN_STATUS_RELEASING:
        enConnState = IMSA_ERR_LOG_PDN_CONN_STATUS_RELEASING;
        break;
    case IMSA_CONN_STATUS_CONN:
        enConnState = IMSA_ERR_LOG_PDN_CONN_STATUS_CONN;
        break;
    default:
        IMSA_ERR_LOG1("IMSA_ConnState2ErrlogConnState: invalid mapping state", enImsaConnState);
        TLPS_PRINT2LAYER_ERROR1(IMSA_ConnState2ErrlogConnState_ENUM, IMSA_STATE_ERROR, enImsaConnState);
    }

    return enConnState;
}


IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8 IMSA_VoPsState2ErrlogVoPsState(IMSA_IMS_VOPS_STATUS_ENUM_UINT8 enImsaImsVoPsStatus)
{
    IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8 enVoPsState = IMSA_ERR_LOG_VOPS_STATUS_BUTT;

    switch (enImsaImsVoPsStatus)
    {
    case IMSA_IMS_VOPS_STATUS_NOT_SUPPORT:
        enVoPsState = IMSA_ERR_LOG_VOPS_STATUS_NOT_SUPPORT;
        break;
    case IMSA_IMS_VOPS_STATUS_SUPPORT:
        enVoPsState = IMSA_ERR_LOG_VOPS_STATUS_SUPPORT;
        break;
    default:
        IMSA_ERR_LOG1("IMSA_VoPsState2ErrlogVoPsState: invalid mapping state", enImsaImsVoPsStatus);
        TLPS_PRINT2LAYER_ERROR1(IMSA_VoPsState2ErrlogVoPsState_ENUM, IMSA_STATE_ERROR, enImsaImsVoPsStatus);
    }

    return enVoPsState;
}

/*lint -e593 -e830*/

VOS_VOID IMSA_InitErrLogInfo(VOS_VOID)
{
    VOS_CHAR                           *pbuffer;
    OM_RING_ID                          pRingbuffer;

    IMSA_ReadErrlogCtrlInfoNvim();

    /* ����cache�Ķ�̬�ڴ� , ���ȼ�1����Ϊ����дָ��֮����д��ʱ�����һ���ֽ� */
    pbuffer = (char *)PS_MEM_ALLOC(PS_PID_IMSA, IMSA_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pbuffer)
    {
        IMSA_SetErrorLogRingBufAddr(VOS_NULL_PTR);
        IMSA_ERR_LOG("IMSA_InitErrLogInfo: alloc fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_InitErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    /* ����OM�Ľӿڣ�������Ķ�̬�ڴ洴��ΪRING BUFFER */
    pRingbuffer = OM_RingBufferCreateEx(pbuffer, IMSA_RING_BUFFER_SIZE + 1);
    if (VOS_NULL_PTR == pRingbuffer)
    {
        IMSA_MEM_FREE(pbuffer);
    }

    /* ����ringbufferָ�� */
    IMSA_SetErrorLogRingBufAddr(pRingbuffer);

    IMSA_SetErrlogOverflowCnt(0);

    return;

}
/*lint +e593 +e830*/


VOS_VOID IMSA_ConverterErrlogCtrlInfo2Ims
(
    IMSA_IMS_INPUT_EVENT_STRU                   *pstImsaImsInputEvt
)
{
    IMSA_INFO_LOG("IMSA_ConverterErrlogCtrlInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConverterErrlogCtrlInfo2Ims_ENUM, LNAS_ENTRY);

    pstImsaImsInputEvt->enEventType = IMSA_IMS_EVENT_TYPE_PARA;

    pstImsaImsInputEvt->evt.stInputParaEvent.ulOpId = IMSA_AllocImsOpId();
    pstImsaImsInputEvt->evt.stInputParaEvent.enInputParaReason = IMAS_IMS_INPUT_PARA_REASON_SET_ERR_LOG_CTRL_INFO;

    pstImsaImsInputEvt->evt.stInputParaEvent.u.stErrlogCtrlInfo.ucErrlogCtrlFlag = IMSA_GetErrlogCtrlFlag();
    pstImsaImsInputEvt->evt.stInputParaEvent.u.stErrlogCtrlInfo.usAlmLevel = IMSA_GetErrlogAlmLevel();
}


VOS_VOID IMSA_ConfigErrlogCtrlInfo2Ims( VOS_VOID )
{
    IMSA_IMS_INPUT_EVENT_STRU          *pstImsaImsInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_ConfigErrlogCtrlInfo2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ConfigErrlogCtrlInfo2Ims_ENUM, LNAS_ENTRY);

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstImsaImsInputEvent = IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstImsaImsInputEvent )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_ConfigErrlogCtrlInfo2Ims:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_ConfigErrlogCtrlInfo2Ims_ENUM, LNAS_NULL_PTR);
        return ;
    }

    /*���*/
    IMSA_MEM_SET(pstImsaImsInputEvent, 0, \
                 sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_ConverterErrlogCtrlInfo2Ims(pstImsaImsInputEvent);

    IMSA_SndImsMsgParaEvent(pstImsaImsInputEvent);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_MEM_FREE(pstImsaImsInputEvent);
}

#endif
/*lint +e961*/


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaPublic.c */



