

#ifndef __MTCCTX_H__
#define __MTCCTX_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "Ps.h"

#include "MtcRrcInterface.h"
#include "MtcMmaInterface.h"
#include "TafMtcInterface.h"
#include "MtaMtcInterface.h"
#include "MtcNasInterface.h"
#include "MtcRcmInterface.h"
#include "TafMtcApi.h"
/* Added by wx270776 for OM�ں�, 2015-6-27, begin */
#include "TafLog.h"
#include "TafNvInterface.h"
/* Added by wx270776 for OM�ں�, 2015-6-27, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if (VOS_WIN32 == VOS_OS_VER)
#define MTC_WARNING_LOG(string)                 vos_printf("%s \r\n", string)
#define MTC_WARNING1_LOG(string, para1)         vos_printf("%s %d.\r\n", string, para1)
#define MTC_WARNING2_LOG(string, para1, para2)  vos_printf("%s %d, %d.\r\n", string, para1, para2)

#define MTC_ERROR_LOG(string)                   vos_printf("%s \r\n", string)
#define MTC_ERROR1_LOG(string, para1)           vos_printf("%s %d.\r\n", string, para1)
#define MTC_ERROR2_LOG(string, para1, para2)    vos_printf("%s %d, %d.\r\n", string, para1, para2)
#else
#define MTC_WARNING_LOG(string)                 TAF_LOG(UEPS_PID_MTC, 0, PS_LOG_LEVEL_WARNING,  string)
#define MTC_WARNING1_LOG(string, para1)         TAF_LOG1(UEPS_PID_MTC, 0, PS_LOG_LEVEL_WARNING,  string, (VOS_INT32)para1)
#define MTC_WARNING2_LOG(string, para1, para2)  TAF_LOG2(UEPS_PID_MTC, 0, PS_LOG_LEVEL_WARNING,  string, (VOS_INT32)para1, (VOS_INT32)para2)

#define MTC_ERROR_LOG(string)                   TAF_LOG(UEPS_PID_MTC, 0, PS_LOG_LEVEL_ERROR,  string)
#define MTC_ERROR1_LOG(string, para1)           TAF_LOG1(UEPS_PID_MTC, 0, PS_LOG_LEVEL_ERROR,  string, (VOS_INT32)para1)
#define MTC_ERROR2_LOG(string, para1, para2)    TAF_LOG2(UEPS_PID_MTC, 0, PS_LOG_LEVEL_ERROR,  string, (VOS_INT32)para1, (VOS_INT32)para2)
#endif

/* ��BIT n��λ */
#define MTC_SET_BIT(n)                  ((VOS_UINT32)0x01 << n)
#define MTC_SET_BIT64(n)                ((VOS_UINT64)1 << (n))

#define MTC_INTRUSION_CFG_BIT           MTC_SET_BIT(0)                          /* NV�б�ʶ���ſ��Ƶ�bitλ */

#define MTC_NOTCH_CFG_BIT               MTC_SET_BIT(1)                          /* NV�б�ʶnotch���Ƶ�bitλ */

#define MTC_RSE_CFG_BIT                 MTC_SET_BIT(4)                          /* NV�б�ʶRSE���Ƶ�bitλ */


#define MTC_PS_AUTOMATIC_START              (0)                                 /* ֵ��NAS_MMA_AUTOMATIC_START����һ�� */
#define MTC_PS_MMA_MANUAL_START             (1)                                 /* ֵ��NAS_MMA_MANUAL_START����һ��  */

#define MTC_NARROW_BAND_DCS_CFG_BIT     MTC_SET_BIT(2)                          /* NV�б�ʶnarrow band dcs���Ƶ�bitλ */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum MTC_CFG_ENUM
{
    MTC_CFG_DISABLE                     = 0x00,                                 /* ���ò�ʹ�� */
    MTC_CFG_ENABLE                      = 0x01,                                 /* ����ʹ�� */
    MTC_CFG_BUTT
};
typedef VOS_UINT8  MTC_CFG_ENUM_UINT8;


enum MTC_CS_SERVICE_STATE_ENUM
{
    MTC_CS_NO_SERVICE         = 0x00,                                           /* CS����ҵ�� */
    MTC_CS_IN_SERVICE,                                                          /* CS�����ҵ�� */

    MTC_CS_SERVICE_STATE_BUTT
};
typedef VOS_UINT8 MTC_CS_SERVICE_STATE_ENUM_UINT8;


enum MTC_OPERATOR_CUST_SOLUTION_ENUM
{
    MTC_OPERATOR_CUST_NONE          = 0x00,                                     /* ����Ӫ�̶��Ʒ��� */
    MTC_OPERATOR_CUST_CMCC_SVLTE    = 0x01,                                     /* ���ƶ�����SVLTE���� */
    MTC_OPERATOR_CUST_CT_LC         = 0x02,                                     /* �й�����C+L���� */

    MTC_OPERATOR_CUST_BUTT
};
typedef VOS_UINT8 MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8;
enum MTC_PS_TRANSFER_CAUSE_ENUM
{
    MTC_PS_TRANSFER_CAUSE_AREA_LOST                 = 0,

    MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE            = 1,

    MTC_PS_TRANSFER_CAUSE_BUTT
};
typedef VOS_UINT8 MTC_PS_TRANSFER_CAUSE_ENUM_UINT8;


enum MTC_OUTSIDE_MODEM_ENUM
{
    MTC_OUTSIDE_MODEM_CDMA              = 0x0000,                              /* ���CDMA */

    MTC_OUTSIDE_MODEM_BUTT
};
typedef VOS_UINT16 MTC_OUTSIDE_MODEM_ENUM_UINT16;

/*****************************************************************************
 ö����    : MTC_BAND_INFO_ENUM
 Э����  :
 ö��˵��  : Ƶ��ö��
*****************************************************************************/
enum MTC_BAND_INFO_ENUM
{
    MTC_FREQ_BAND_NONE = 0,                                                     /*  û��Band */
    MTC_FREQ_BAND1 ,                                                            /*  Band1 */
    MTC_FREQ_BAND2 ,
    MTC_FREQ_BAND3 ,
    MTC_FREQ_BAND4 ,
    MTC_FREQ_BAND5 ,
    MTC_FREQ_BAND6 ,
    MTC_FREQ_BAND7 ,
    MTC_FREQ_BAND8 ,
    MTC_FREQ_BAND9 ,
    MTC_FREQ_BAND10,
    MTC_FREQ_BAND11,
    MTC_FREQ_BAND12,
    MTC_FREQ_BAND13,
    MTC_FREQ_BAND14,
    MTC_FREQ_BAND15,
    MTC_FREQ_BAND16,
    MTC_FREQ_BAND17,
    MTC_FREQ_BAND18,
    MTC_FREQ_BAND19,
    MTC_FREQ_BAND20,

    MTC_FREQ_BAND21,
    MTC_FREQ_BAND22,
    MTC_FREQ_BAND23,
    MTC_FREQ_BAND24,
    MTC_FREQ_BAND25,
    MTC_FREQ_BAND26,
    MTC_FREQ_BAND27,
    MTC_FREQ_BAND28,
    MTC_FREQ_BAND29,
    MTC_FREQ_BAND30,
    MTC_FREQ_BAND31,
    MTC_FREQ_BAND32,
    MTC_FREQ_BAND33 = 33,
    MTC_FREQ_BAND34,
    MTC_FREQ_BAND35,
    MTC_FREQ_BAND36,
    MTC_FREQ_BAND37,
    MTC_FREQ_BAND38,
    MTC_FREQ_BAND39,
    MTC_FREQ_BAND40,
    MTC_FREQ_BAND41,
    MTC_FREQ_BAND42,
    MTC_FREQ_BAND43,
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, begin */
    MTC_FREQ_BAND44,
    /* Modified by w00316404 for R11 Update LTE Arf, 2015-07-20, end */
    MTC_FREQ_BAND64 = 64,

    /* �Ǳ�Ƶ��begin */
    MTC_FREQ_BAND101 = 101,
    MTC_FREQ_BAND102 = 102,
    MTC_FREQ_BAND103 = 103,
    MTC_FREQ_BAND104 = 104,
    MTC_FREQ_BAND105 = 105,
    MTC_FREQ_BAND106 = 106,
    MTC_FREQ_BAND107 = 107,
    MTC_FREQ_BAND108 = 108,
    MTC_FREQ_BAND109 = 109,
    MTC_FREQ_BAND110 = 110,
    MTC_FREQ_BAND111 = 111,
    MTC_FREQ_BAND112 = 112,
    MTC_FREQ_BAND113 = 113,
    MTC_FREQ_BAND114 = 114,
    MTC_FREQ_BAND115 = 115,
    MTC_FREQ_BAND116 = 116,

    /* �Ǳ�Ƶ��end */
    MTC_FREQ_BAND_BUTT = 0xFFFF
};
typedef VOS_UINT16 MTC_BAND_INFO_ENUM_UINT16;



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
    VOS_UINT8                           ucIntrusionCfg      : 1;
    VOS_UINT8                           ucNotchBypass       : 1;
    VOS_UINT8                           ucNarrowBandDcsCfg  : 1;
    VOS_UINT8                           ucTlRfCtrlCfg       : 1;
    VOS_UINT8                           ucReserved          : 4;

    VOS_UINT8                           aucAdditonCfg[3];

} MTC_RF_INTRUSION_CFG_STRU;


typedef struct
{
    MTC_NV_RF_INTRUSION_CFG_STRU        stIntrusionCfg;                         /* ����RF INTRUSION NV������Ϣ */
    PS_BOOL_ENUM_UINT8                  enNotchEnableFlag;

    PS_BOOL_ENUM_UINT8                  enNarrowDcsEnableFlag;                  /* ��¼NarrowDcs״̬ */

    PS_BOOL_ENUM_UINT8                  enTlRfCtrlEnableFlag;

    PS_BOOL_ENUM_UINT8                  enRseCfg;                               /* ��¼�Ѿ��·�����RSE���� */
}MTC_INTRUSION_CTX_STRU;
typedef struct
{
    VOS_UINT8                           ucCallSrvExistFlg;                      /* Modem�Ƿ���ں��з��� */
    VOS_UINT8                           ucSmsSrvExistFlg;                       /* Modem�Ƿ���ڶ���ҵ�� */
    VOS_UINT8                           ucSsSrvExistFlg;                        /* Modem�Ƿ���ڲ���ҵ�� */
    VOS_UINT8                           aucReserved1[1];
}MTC_MODEM_SERVICE_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucPsSupportFlg;                         /* ��ǰPS���Ƿ�֧��GPRS���� */
    VOS_UINT8                           ucPsAttachAllowFlg;                     /* PS���Ƿ�����ע��,VOS_TRUE:����PS��ע��,VOS_FALSE:������PS��ע�� */

    VOS_UINT8                           aucReserved1[2];
}MTC_MODEM_PS_DOMAIN_INFO_STRU;


typedef struct
{
    MTC_MMA_PLMN_ID_STRU                stPlmnId;                               /* Modem��ǰפ������ */
    MTC_MODEM_PS_DOMAIN_INFO_STRU       stPsDomainInfo;                         /* Modem��ǰPS����Ϣ */

    VOS_UINT8                           ucIsForbiddenPlmnFlag;                  /* Modem��ǰפ�������Ƿ�Ϊ��ֹ�����ʶ */
    VOS_UINT8                           aucReserved1[3];
}MTC_MODEM_NETWORK_INFO_STRU;
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enCsExistFlag;
    PS_BOOL_ENUM_UINT8                  enPsExistFlag;

    VOS_UINT16                          usScellBitMap;
    VOS_UINT16                          usHoppingBitMap;
    VOS_UINT16                          usNcellBitMap;
}MTC_MODEM_MIPICLK_BITMAP_STRU;


typedef struct
{
    VOS_UINT32                          ulCsSessionInfo;
    VOS_UINT32                          ulPsSessionInfo;
    VOS_UINT8                           ucCsSrvConnInfo;
    VOS_UINT8                           ucPsSrvConnInfo;
    VOS_UINT8                           ucPsActualConnInfo;
    VOS_UINT8                           aucReserved[1];
}MTC_MODEM_CONN_STATE_INFO_STRU;


typedef struct
{
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvConnState;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvConnState;
    VOS_UINT8                           aucReserved[2];
}MTC_OUTSIDE_MODEM_CONN_STATE_INFO_STRU;



typedef struct
{
    MTC_OUTSIDE_MODEM_CONN_STATE_INFO_STRU  stConnStateInfo;
    MTC_MODEM_POWER_STATE_ENUM_UINT8        enPowerState;
    VOS_UINT8                               aucReserved1[3];
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimmState;
    VOS_UINT8                               aucReserved2[2];
} MTC_OUTSIDE_MODEM_INFO_STRU;


typedef struct
{
    PS_BOOL_ENUM_UINT8                              enExitBufMsgFlag;
    VOS_UINT8                                       aucRsv[3];
    RRC_MTC_INTRUSION_BAND_INFO_IND_STRU            stIntrusionBandInfoMsg;
}MTC_BAND_INFO_MSG_BUF_STRU;


typedef struct
{
    PS_BOOL_ENUM_UINT8                              enExitBufMsgFlag;
    VOS_UINT8                                       aucRsv[3];
    RRC_MTC_USING_FREQ_IND_STRU                     stUsingFreqInfoMsg;
}MTC_USING_FREQ_MSG_BUF_STRU;


typedef struct
{
    MTC_BAND_INFO_MSG_BUF_STRU          stBufBandInfoMsg;
    MTC_USING_FREQ_MSG_BUF_STRU         stBufUsingFreqInfoMsg;
}MTC_MSG_BUF_STRU;


typedef struct
{
    VOS_UINT8                               ucRatCap;                           /* Modem�Ľ��뼼������ֵ */
    MTC_MODEM_POWER_STATE_ENUM_UINT8        enPowerState;                       /* Modem�Ŀ��ػ�״̬ */
    MTC_RATMODE_ENUM_UINT8                  enRatMode;                          /* Modem��ǰ��ģʽ���� */
    VOS_UINT8                               ucUsimValidFlag;                    /* modem��ǰ���Ƿ���Ч��1:����Ч��0:����Ч */

    MTC_MODEM_SERVICE_INFO_STRU             stSrvInfo;                          /* Modem��ǰ������Ϣ */
    RRC_MTC_MS_BAND_INFO_STRU               stCurBandInfo;                      /* Modem��ǰ��Ƶ����Ϣ */

    RRC_MTC_MS_BAND_INFO_STRU               stNCellBandInfo;                      /* Modem������Band��Ϣ�� Ŀǰֻ��¼GUģʱ��TL����Band��Ϣ */

    RRC_MTC_MS_BAND_INFO_STRU               stSerCellBandInfo;                  /* Modem��ǰפ������Ƶ����Ϣ */

    MTC_MODEM_NETWORK_INFO_STRU             stNetworkInfo;                      /* Modem��ǰפ��������Ϣ */

    MTC_MODEM_MIPICLK_BITMAP_STRU           stRfCellInfo;                       /* Modem��ǰ��BITMAP״̬ */

    MTC_MODEM_CONN_STATE_INFO_STRU          stConnStateInfo;                    /* Modem��ǰ����״̬ */
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimmState;                       /* ��״̬ */
    MTC_MODEM_POWER_STATE_ENUM_UINT8        enImsaState;                        /* Modem��IMSA���ػ�״̬ */

    /* Modified by w00316404 for NEXT B26 Project, 2015-6-17, begin */
    MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8      enImsVoiceCap;
    /* Modified by w00316404 for NEXT B26 Project, 2015-6-17, end */

    MTC_GSM_CELLINFO_EX_STRU                stGsmCellInfoEx;                    /* GSMС����չ��Ϣ(������modem) */

    MTC_RCM_TC_STATUS_ENUM_UINT16           enTcStatus;                         /* ��¼TAS���ز���״̬ */
    VOS_UINT8                               aucRsv[2];

    MTC_MSG_BUF_STRU                        stBufMsg;
}MTC_MODEM_INFO_STRU;
typedef struct
{
    MTC_NV_PS_TRANSFER_CFG_STRU         stPsTransferCfg;                        /* ����PS TRANSFER NV������Ϣ */

    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enRrcCause;
    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enReportCause;
    VOS_UINT8                           aucRsve[2];
}MTC_PS_TRANSFER_CTX_STRU;
typedef struct
{
    VOS_UINT32                          ulAvailNum;                             /* ��ЧƵ�ʸ��� */
    VOS_UINT32                          ulMipiClk;                              /* MipiClkֵ */
    VOS_UINT32                          aulFreq[MTC_RF_LCD_MIPICLK_FREQ_MAX_NUM];/* ulMipiClkֵӰ���Ƶ�ʱ� */
}MTC_RF_LCD_MIPICLK_FREQ_STRU;
typedef struct
{
    VOS_UINT8                           ucAvailFreqListNum;                     /* ��Ч��astRfLcdFreqList���� */
    VOS_UINT8                           aucReserved[1];
    VOS_UINT16                          usMipiClkBitMap;                        /* MIPICLKλͼ */
    VOS_UINT32                          ulMipiClkReportModemId;                 /* ����MipiClk�����ϱ����Ǹ�modem��MTA */
    VOS_UINT16                          usFreqWidth;                            /* ���� ��λ100KHZ */
    VOS_UINT16                          usEnableBitMap;
    MTC_RF_LCD_MIPICLK_FREQ_STRU        astRfLcdFreqList[MTC_RF_LCD_MIPICLK_MAX_NUM];
}MTC_RF_LCD_INTRUSION_CTX_STRU;


typedef struct
{
    MTC_MODEM_INFO_STRU                 astModemInfo[MODEM_ID_BUTT];            /* MTCģ�鱣��Modem״̬��Ϣ */

    MTC_INTRUSION_CTX_STRU              stIntrusionCtx;                         /* ���ſ��������� */

    MTC_PS_TRANSFER_CTX_STRU            stPsTransferCtx;                        /* PS��Ǩ�������� */

    MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8   enOperatorCustSolution;             /* ��Ӫ�̶��Ʒ��� */

    VOS_UINT8                           aucReserved1[3];

    MTC_RF_LCD_INTRUSION_CTX_STRU       stRfLcdIntrusionCtx;

    MTC_OUTSIDE_MODEM_INFO_STRU         astOutSideModemInfo[MTC_OUTSIDE_MODEM_BUTT];/* ���modem ��Ϣ */

    /* �������ܻ���չ�������� */

}MTC_CONTEXT_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
MTC_CONTEXT_STRU* MTC_GetCtxAddr(VOS_VOID);

MTC_INTRUSION_CTX_STRU* MTC_GetIntrusionCtxAddr(VOS_VOID);

MTC_MODEM_INFO_STRU* MTC_GetModemCtxAddr(MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID MTC_InitIntrusionCtx(VOS_VOID);

VOS_UINT32 MTC_IsSupportRatType(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_RATMODE_ENUM_UINT8              enRatMode
);

VOS_VOID MTC_InitModemCtx(VOS_VOID);

VOS_VOID MTC_InitCtx(VOS_VOID);

MTC_CFG_ENUM_UINT8 MTC_GetIntrusionCfg(VOS_VOID);

VOS_VOID MTC_SetModemPowerState(MODEM_ID_ENUM_UINT16 enModemId, MTC_MODEM_POWER_STATE_ENUM_UINT8 enState);

MTC_MODEM_POWER_STATE_ENUM_UINT8 MTC_GetModemPowerState(MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID MTC_SetModemRatMode(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_RATMODE_ENUM_UINT8              enRatMode
);

VOS_VOID MTC_SetModemImsaState(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enState);

MTC_MODEM_POWER_STATE_ENUM_UINT8 MTC_GetModemImsaState(MODEM_ID_ENUM_UINT16 enModemId);

/* Added by w00316404 for NEXT B26 Project, 2015-6-17, begin */
VOS_VOID MTC_SetModemImsVoiceCap(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8  enState
);
MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8 MTC_GetModemImsVoiceCap(
    MODEM_ID_ENUM_UINT16                enModemId
);
/* Added by w00316404 for NEXT B26 Project, 2015-6-17, end */

MTC_RATMODE_ENUM_UINT8 MTC_GetModemRatMode(MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID MTC_SetModemCallSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucFlg
);

VOS_VOID MTC_SetModemSmsSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucFlg
);

VOS_VOID MTC_SetModemSsSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucFlg
);

MTC_CS_SERVICE_STATE_ENUM_UINT8 MTC_GetModemCsSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId
);

RRC_MTC_MS_BAND_INFO_STRU* MTC_GetModemCurBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_UINT8 MTC_GetModemUsimValidFlag(MODEM_ID_ENUM_UINT16 enModemId);
VOS_VOID MTC_SetModemUsimValidFlag(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucUsimValidStatus
);

VOS_VOID MTC_ResetModemInfo(MODEM_ID_ENUM_UINT16 enModemId);

VOS_VOID MTC_SetNotchEnalbeFlag(PS_BOOL_ENUM_UINT8 enFlag);
PS_BOOL_ENUM_UINT8 MTC_GetNotchEnalbeFlag(VOS_VOID);
MTC_CFG_ENUM_UINT8 MTC_GetNotchCfg(VOS_VOID);

RRC_MTC_MS_BAND_INFO_STRU* MTC_GetModemSerCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);
MTC_CFG_ENUM_UINT8 MTC_GetTlRfCtrlCfg(VOS_VOID);
VOS_VOID MTC_SetTlRfCtrlEnalbeFlag(PS_BOOL_ENUM_UINT8 enFlag);
PS_BOOL_ENUM_UINT8 MTC_GetTlRfCtrlEnalbeFlag(VOS_VOID);

VOS_VOID MTC_InitPsTransferCtx(VOS_VOID);

VOS_VOID MTC_InitOperatorCustSolution(VOS_VOID);

MTC_PS_TRANSFER_ENUM_UINT8 MTC_GetPsTransferCfg(VOS_VOID);

MTC_PS_TRANSFER_CTX_STRU* MTC_GetPsTransferCtxAddr(VOS_VOID);

MTC_MODEM_NETWORK_INFO_STRU* MTC_GetModemNetworkInfoAddr(
    MODEM_ID_ENUM_UINT16                enModemId);

MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8 MTC_GetOperatorCustSolution(VOS_VOID);

VOS_VOID MTC_SetOperatorCustSolution(
    MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8   enOperatorCustSolution);


VOS_VOID MTC_SetNarrowDcsEnalbeFlag(PS_BOOL_ENUM_UINT8 enFlag);
PS_BOOL_ENUM_UINT8 MTC_GetNarrowDcsEnalbeFlag(VOS_VOID);
MTC_CFG_ENUM_UINT8 MTC_GetNarrowBandDcsCfg(VOS_VOID);

MTC_RF_LCD_INTRUSION_CTX_STRU* MTC_GetRfLcdIntrusionCtxAddr(VOS_VOID);
MTC_CFG_ENUM_UINT8 MTC_GetRfLcdIntrusionCfg(VOS_VOID);
VOS_VOID MTC_InitRfLcdIntrusionCtx(VOS_VOID);
VOS_VOID MTC_ReadRfLcdCfgNv(VOS_VOID);
VOS_UINT32 MTC_GetMipiClkRcvPid(VOS_VOID);
MTC_MODEM_MIPICLK_BITMAP_STRU* MTC_GetRfCellInfoAddr(
    MODEM_ID_ENUM_UINT16                enModemId
);
VOS_UINT16 MTC_GetMipiClkBitMap(VOS_VOID);
VOS_VOID MTC_InitRfCellInfo(MODEM_ID_ENUM_UINT16 enModemId);
MTC_RF_LCD_INTRUSION_CTX_STRU* MTC_GetRfLcdIntrusionCtxAddr(VOS_VOID);

MTC_CFG_ENUM_UINT8 MTC_GetRseSupportCfg(VOS_VOID);

PS_BOOL_ENUM_UINT8 MTC_GetRseCfgValue(VOS_VOID);

VOS_VOID MTC_SetRseCfgValue(PS_BOOL_ENUM_UINT8 enValue);


VOS_VOID MTC_SetCsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucCsTypeInfo,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvConnState
);

VOS_UINT8 MTC_GetCsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetCsSrvState(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID MTC_SetPsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucPsTypeInfo,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvConnState
);

VOS_UINT8 MTC_GetPsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetPsSrvState(
    MODEM_ID_ENUM_UINT16                enModemId
);


MTC_OUTSIDE_MODEM_INFO_STRU* MTC_GetOutSideModemCtxAddr(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
);

VOS_VOID MTC_SetOutSideCsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enConnSt
);

TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetOutSideCsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
);

VOS_VOID MTC_SetOutSidePsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enConnSt
);

TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetOutSidePsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
);

VOS_VOID MTC_SetOutSideModemPowerState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId,
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enPowerStatus
);

MTC_MODEM_POWER_STATE_ENUM_UINT8 MTC_GetOutSideModemPowerState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
);

VOS_VOID MTC_SetUsimmStateInfo(
    MODEM_ID_ENUM_UINT16                    enModemId,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimmState
);

TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16 MTC_GetUsimmStateInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID MTC_SetOutSideModemUsimmState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16           enModemId,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimmStatus
);

TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16 MTC_GetOutSideModemUsimmState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
);


MTC_GSM_CELLINFO_EX_STRU* MTC_GetModemGsmCellInfoEx(
    MODEM_ID_ENUM_UINT16                enModemId
);

/* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, begin */
MTC_RCM_TC_STATUS_ENUM_UINT16 MTC_GetCurrentTcStatus(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID MTC_SetCurrentTcStatus(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_RCM_TC_STATUS_ENUM_UINT16       enTcStatus
);
/* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, end */

VOS_VOID MTC_SetCsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
);
VOS_VOID MTC_ClearCsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
);

VOS_UINT32 MTC_GetCsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_UINT32 MTC_GetPsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);


PS_BOOL_ENUM_UINT8 MTC_IsCsSessionInfoExit(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID MTC_SetActualPsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_PS_TYPE_ENUM_UINT8              enPsType,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvConnState
);

VOS_UINT8 MTC_GetActualPsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetActualPsSrvState(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID MTC_ResetModemCurBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

RRC_MTC_MS_BAND_INFO_STRU* MTC_GetModemNCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID MTC_SetModemNCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_BAND_INFO_ENUM_UINT16           enBandNum
);

VOS_VOID MTC_ResetNCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
);

MTC_MSG_BUF_STRU* MTC_GetBufAddr(
    MODEM_ID_ENUM_UINT16                enModemId
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

#endif /* end of MtcCtx.h */
