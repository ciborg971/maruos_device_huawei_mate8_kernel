
#ifndef _NAS_MM_SND_OM_H
#define _NAS_MM_SND_OM_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "MM_Global.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum NAS_MM_OM_MSG_ID_ENUM
{
    /* MM���͸�OM����Ϣ */
    MMOM_LOG_STATE_INFO_IND                       = 0x1000,      /*_H2ASN_MsgChoice  NAS_MM_LOG_STATE_INFO_STRU */
    MMOM_LOG_AUTH_INFO_IND                        = 0x1001,      /*_H2ASN_MsgChoice  NAS_MM_LOG_AUTH_INFO_STRU */

    MMOM_LOG_CTX_INFO_IND                         = 0x1002,      /*_H2ASN_MsgChoice  MMOM_LOG_CTX_INFO_STRU */

    MMOM_LOG_T3212_INFO_IND                       = 0x1003,      /*_H2ASN_MsgChoice  MMOM_LOG_CTX_INFO_STRU */

    MMOM_LOG_BUTT
};
typedef VOS_UINT32 NAS_MM_OM_MSG_ID_ENUM_UINT32;

/* ɾ���˴�ö�ٶ���, ����NAS_MM_STATE_ENUM_UINT8��ö�ٶ��� */

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ */ /*_H2ASN_Skip*/
    NAS_MM_STATE_ENUM_UINT8             enMmState;
    VOS_UINT8                           aucRsv3[3];
}NAS_MM_LOG_STATE_INFO_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucExpectOpId;
    VOS_UINT8                           ucRcvOpId;
    VOS_UINT8                           aucRsv[2];
}NAS_MM_LOG_AUTH_INFO_STRU;
typedef struct
{
    MSG_HEADER_STRU                                         stMsgHeader;/* ��Ϣͷ */ /*_H2ASN_Skip*/

    /* NV�ж��Ƶ�T3212��Ϣ */
    NAS_MML_T3212_TIMER_INFO_CONFIG_STRU                    stMmlT3212NvCfgInfo;

    /* ��ǰʹ��NV��T3212ʱ���ļ��� */
    VOS_UINT32                                              ulT3212Count;

    /* ��������T3212��ʱ��ʱ�� */
    VOS_UINT32                                              ulNetworkT3212Len;

    /* ��������T3212ʱ���ı��������ʱ��ʱ�� */
    VOS_UINT32                                              ulNetworkRandT3212Len;

    NAS_MML_LAI_STRU                                        stAllocT3212ValueLaiInfo;
    NAS_MM_NETWORK_T3212_VALUE_TYPE_ENUM_UINT8              enT3212ValueType;
    VOS_UINT8                                               aucReserved[3];
}NAS_MM_LOG_T3212_INFO_STRU;
typedef struct
{
    NAS_MML_LOCATION_UPDATE_STATUS_ENUM_UINT8      enCsUpdateStatus;   /*��¼NAS_MML_GetCsUpdateStatus*/
    NAS_MML_CALL_MODE_ENUM_UINT8                   enCallMode;         /*��¼NAS_MML_GetCallMode*/
    NAS_MML_CSFB_SERVICE_STATUS_ENUM_UINT8         enCsfbServiceStatus;/*��¼NAS_MML_GetCsfbServiceStatus*/
    VOS_UINT8                                      ucImsVoiceAvailFlg; /*��¼NAS_MML_GetImsVoiceAvailFlg*/
    VOS_UINT8                                      ucImsVoiceInterSysLauEnableFlg; /*��¼NAS_MML_GetImsVoiceInterSysLauEnableFlg*/
    NAS_MML_TIMER_INFO_ENUM_UINT8                  enT3423Status;      /*��¼NAS_MML_GetT3423Status*/
    VOS_UINT8                                      ucCsSecurityCksn;   /*��¼NAS_MML_GetSimCsSecurityCksn */
    VOS_UINT8                                      ucStaOfRcvXXEstReqCsfb;/*��¼NAS_MM_GetStaOfRcvXXEstReq_CSFB*/
    MM_LAI_STRU                                    stAttemptUpdateLaiInfo;/*��¼NAS_MM_GetAttemptUpdateLaiInfo*/
    NAS_MML_LAI_STRU                               stCsLastSuccLai;    /*��¼NAS_MML_GetCsLastSuccLai*/
    NAS_MML_LAI_STRU                               stCurrCampLai;      /*��¼NAS_MML_GetCurrCampLai*/
}MMOM_LOG_MML_CTX_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucT3213TimerStatus;        /*��¼gstMmTimer[MM_TIMER_T3213].ucTimerStatus*/
    VOS_UINT8                           ucT3211TimerStatus;        /*��¼gstMmTimer[MM_TIMER_T3211].ucTimerStatus*/
    VOS_UINT8                           ucT3212TimerStatus;        /*��¼gstMmTimer[MM_TIMER_T3212].ucTimerStatus*/
    VOS_UINT8                           ucT3242TimerStatus;        /*��¼gstMmTimer[MM_TIMER_T3242].ucTimerStatus*/
    VOS_UINT8                           ucT3243TimerStatus;        /*��¼gstMmTimer[MM_TIMER_T3243].ucTimerStatus*/
    VOS_UINT8                           aucReserved[3];
}MMOM_LOG_MM_TIMER_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucMmServiceState;                   /*��¼g_MmGlobalInfo.ucMmServiceState*/
    VOS_UINT8                           ConnCtrlInfo_SMS_RcvXXEstReq_ucFlg; /* ��¼g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SMS].RcvXXEstReq.ucFlg*/
    VOS_UINT8                           ConnCtrlInfo_SS_RcvXXEstReq_ucFlg;  /* ��¼g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_SS].RcvXXEstReq.ucFlg*/
    VOS_UINT8                           ConnCtrlInfo_CC_RcvXXEstReq_ucFlg;  /* ��¼g_MmGlobalInfo.ConnCtrlInfo[MM_CONN_CTRL_CC].RcvXXEstReq.ucFlg*/
    VOS_UINT8                           ucLikeB;                            /*��¼g_MmGlobalInfo.ucLikeB*/
    VOS_UINT8                           MsCsInfo_ucOldRac;                  /* ��¼g_MmGlobalInfo.MsCsInfo.ucOldRac*/
    VOS_UINT16                          usRac;                              /*��¼g_MmGlobalInfo.usRac*/
    VOS_UINT8                           ucNtMod;                            /* ��¼g_MmGlobalInfo.ucNtMod*/
    VOS_UINT8                           ucNotCampONPreState;                /* ��¼g_MmGlobalInfo.ucNotCampONPreState*/
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enPreRatType;                       /*��¼g_MmGlobalInfo.enPreRatType*/
    VOS_UINT8                           ucPreState;                         /*��¼g_MmGlobalInfo.ucPreState*/
    NAS_MM_DETACH_TYPE_ENUM_UINT32      stDetachInfo_enDetachType;          /*��¼g_MmGlobalInfo.stDetachInfo.enDetachType*/
    VOS_UINT8                           ucAttFlg;                           /*��¼g_MmGlobalInfo.ucAttFlg*/
    VOS_UINT8                           ucPowerOnFlg;                       /*��¼g_MmGlobalInfo.ucPowerOnFlg*/
    VOS_UINT8                           LuInfo_ucT3212ExpiredFlg;           /*��¼g_MmGlobalInfo.LuInfo.ucT3212ExpiredFlg*/
    VOS_UINT8                           ucReserved[1];
}MMOM_LOG_MM_GLOBAL_INFO_STRU;
typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;/* ��Ϣͷ */ /*_H2ASN_Skip*/
    MMOM_LOG_MML_CTX_INFO_STRU          stMmlCtxInfo;
    MMOM_LOG_MM_GLOBAL_INFO_STRU        stMmGlobalInfo;
    MMOM_LOG_MM_TIMER_INFO_STRU         stMmTimerInfo;
}MMOM_LOG_CTX_INFO_STRU;



/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    NAS_MM_OM_MSG_ID_ENUM_UINT32        enMsgID;    /*_H2ASN_MsgChoice_Export NAS_MM_OM_MSG_ID_ENUM_UINT32*/
                                                    /* Ϊ�˼���NAS����Ϣͷ���壬����ת��ASN.1ʹ��NAS_MM_OM_MSG_ID_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          NAS_MM_OM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}NAS_MM_SND_OM_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    NAS_MM_SND_OM_MSG_DATA              stMsgData;
}NasMmSndOm_MSG;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID  NAS_MM_LogMmStateInfo(
    NAS_MM_STATE_ENUM_UINT8             ucMmState
);


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

