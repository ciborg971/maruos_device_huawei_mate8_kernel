

#ifndef __CASNVINTERFACE_H__
#define __CASNVINTERFACE_H__


/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "PsTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define CAS_1X_MAX_RLP_BLOB_LEN                     (15)
#define CAS_1X_MAX_SCH_MO_NUM                       (4)                         /* MS支持的SCH上最大速率的MO个数 */
#define CAS_1X_FCH_DCCH_MAX_MO                      (3)
#define CAS_1X_MAX_SUPPORT_SCH_NUM                  (1)
#define NV_ITEM_CAS_1X_TERMINAL_INFO_SIZE           (16)
#define NV_ITEM_CAS_1X_CAPA_INFO_SIZE               (28)
#define NV_ITEM_CAS_1X_RATE_FEATURE_CAPA_INFO_SIZE  (20)
#define NV_ITEM_CAS_1X_CHANNEL_CFG_CAPA_INFO_SIZE   (52)
#define NV_ITEM_CAS_1X_MO_CAPA_SIZE                 (32)
#define NV_ITEM_CAS_1X_RC_PREF_SIZE                 (4)
#define NV_ITEM_CAS_1X_ENCRYPT_CAPA_SIZE            (4)
#define NV_ITEM_CAS_1X_CELL_THRESHOLD_SIZE          (16)
#define NV_ITEM_CAS_1X_IMSI_TYPE_INFO_SIZE          (4)
#define NV_ITEM_CAS_1X_PROTOCOL_OPTIMIZE_SIZE       (8)
#define NV_ITEM_CPORC_1X_FILTER_COEF_SIZE           (36)        /* 对应NV_ITEM_CPROC_1X_FILTER_COEF */
#define NV_ITEM_CPROC_1X_NXM_SWITCH_SIZE            (24)


#define NV_ITEM_CAS_HRPD_AT_REV_SIZE                    (4)
#define NV_ITEM_CDMA_SUPPORT_BANDCLASS_MASK_SIZE        (4)
#define NV_ITEM_CAS_HRPD_CELL_THRESHOLD_SIZE            (4)
#define NV_ITEM_CAS_HRPD_SUSPEND_TIMER_SIZE             (4)
#define NV_ITEM_CAS_HRPD_CONNCLOSE_TO_1X_SWITCH_SIZE    (4)
#define NV_ITEM_CAS_HRPD_C2L_PARA_SIZE                  (8)
#define NV_ITEM_CAS_HRPD_IDLE_HO_PARA_SIZE              (8)
#define NV_ITEM_CAS_HRPD_CFG_PARA_SIZE                  (8)
#define NV_ITEM_CAS_HRPD_TIMER_SIZE                     (16)
/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/

/** ****************************************************************************
 * Name        : CAS_1X_FCH_FRAME_SIZE_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum CAS_1X_FCH_FRAME_SIZE_ENUM
{
    CAS_1X_FCH_FRAME_SIZE_20MS        = 0x0000,
    CAS_1X_FCH_FRAME_SIZE_5MS_20MS    = 0x0001,
    CAS_1X_FCH_FRAME_SIZE_BUTT        = 0x0002
};
typedef VOS_UINT16 CAS_1X_FCH_FRAME_SIZE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CAS_1X_DCCH_FRAME_SIZE_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum CAS_1X_DCCH_FRAME_SIZE_ENUM
{
    CAS_1X_DCCH_FRAME_SIZE_20MS       = 0x0001,
    CAS_1X_DCCH_FRAME_SIZE_5MS        = 0x0002,
    CAS_1X_DCCH_FRAME_SIZE_5MS_20MS   = 0x0003,
    CAS_1X_DCCH_FRAME_SIZE_BUTT       = 0x0004
};
typedef VOS_UINT16 CAS_1X_DCCH_FRAME_SIZE_ENUM_UINT16;


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
 结构名    : CAS_1X_MEID_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MEID一共56个bit
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMeidLow;                              /* Low 32 bit of MEID */
    VOS_UINT32                          ulMeidHigh;                             /* High 24 bit of MEID */
}CAS_1X_MEID_STRU;

/*****************************************************************************
 结构名    : CAS_1X_TERMINAL_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 手机规格信息 , not handle it now
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEsn;                                  /* ESN */
    CAS_1X_MEID_STRU                    stMeid;                                 /* MEID */

    VOS_UINT8                           ucMobMfgCode;                           /* Manufacturer code */
    VOS_UINT8                           ucMobModel;                             /* Model number */
    VOS_UINT16                          usMobFirmRev;                           /* Firmware revision number */
} CAS_1X_NVIM_TERMINAL_INFO_STRU;                                        /* modify as CAS_1X_NVIM_TERMINAL_INFO_STRU */

/*****************************************************************************
 结构名    : CAS_1X_NVIM_CELL_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 门限相关信息结构
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sPilotSrchRssiThreshold;                /* PILOT搜索过程中使用非优选频点的RSSI的最低门限 */
    VOS_INT16                           sPrefChanPilotSrchRssiThreshold;        /* PILOT搜索过程中使用优选频点的RSSI的最低门限 */
    VOS_INT8                            sNbrSetStrengthOffset;                  /* 公式中的邻区截距 */
    VOS_INT8                            sRemainSetStrengthOffset;               /* 公式中的剩余集截距 */
    VOS_INT16                           sDiffStrengthK;                         /* 公式中的线性系数 */
    VOS_INT16                           sDropThresh;                            /* 掉网导频门限 */
    VOS_UINT16                          ulTCandCellLen;                         /* 切换列表元素的定时器时长 单位:ms 默认值为1000 */
    VOS_UINT16                          usFilterA;                              /* alpha滤波系数 */
    VOS_UINT16                          usFilterB;                              /* alpha滤波系数 */
} CAS_1X_NVIM_CELL_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : CAS_1X_ENCRYPT_CAPA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 手机加密能力信息
*****************************************************************************/
typedef struct
{
    /* wanglingping:add ucEncryptAlgSupport to this struct */
    VOS_UINT8                           ucEncryptAlgSupport;                    /* Encryption algorithms supported */
    VOS_UINT8                           ucSigEncryptSpt;                        /* Signaling Encryption supported indicator */
    VOS_UINT8                           ucUiEncryptSpt;                         /* User information Encryption supported indicator */
    VOS_UINT8                           aucReserve[1];
} CAS_1X_NVIM_ENCRYPT_CAPA_STRU;

/*****************************************************************************
 结构名    : CAS_1X_FCH_CFG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : FCH信道能力
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enFchSupport;                           /* Fundamental Channel supported indicator */
    VOS_UINT8                           ucReserve;
    CAS_1X_FCH_FRAME_SIZE_ENUM_UINT16   enFchFrameSize;                         /* Fundamental Channel Frame Size capability indicator */
    VOS_UINT16                          usFwdFchRc;                             /* Fwd Rc,UE支持的所有下行RC,也是FCH信道支持的下行RC */
    VOS_UINT16                          usRevFchRc;                             /* Rev Rc UE支持的所有上行RC,也是FCH信道支持的上行RC */
} CAS_1X_FCH_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_DCCH_CFG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DCCH信道能力
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                      enDcchSupport;                      /* Dedicated Control Channel supported indicator */
    VOS_UINT8                               ucReserve;
    CAS_1X_DCCH_FRAME_SIZE_ENUM_UINT16      enDcchFrameSize;                    /* Dedicated Control Channel Frame Size capability */
    VOS_UINT16                              usDcchFwdRc;                        /* DCCH支持的下行RC */
    VOS_UINT16                              usDcchRevRc;                        /* DCCH支持的上行RC */
} CAS_1X_DCCH_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_SCH_REC_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  SCH配置能力信息
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enTurboSpt;                             /* Turbo Coding supported indicator */
    VOS_UINT8                           ucMaxTurboBlockSize;                    /* maximum Turbo Coding block size */
    PS_BOOL_ENUM_UINT8                  enConvSpt;                              /* Convolutional Coding supported indicator */
    VOS_UINT8                           ucMaxConvBlockSize;                     /* maximum Convolutional Coding block size */
    PS_BOOL_ENUM_UINT8                  enFrame40Spt;                           /* 40ms frame indicator */
    PS_BOOL_ENUM_UINT8                  enFrame80Spt;                           /* 80ms frame indicator */
    VOS_UINT8                           ucMaxRate;                              /* Maximum forward supplemental channels rate */
    VOS_UINT8                           ucReserve;
} CAS_1X_SCH_REC_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_SCH_CFG_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : SCH信道能力
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enForSchSupport;                                /* Forward Supplemental Channel supported indicator */
    VOS_UINT8                           ucReserve1;
    VOS_UINT16                          usForSchRcMap;                                  /* Forward Supplemental Channel Radio Configuration capability */
    VOS_UINT8                           ucForSchNum;                                    /* Number of Forward Supplemental Channels */
    VOS_UINT8                           aucReserve2[3];
    CAS_1X_SCH_REC_INFO_STRU            astForSchRecInfo[CAS_1X_MAX_SUPPORT_SCH_NUM];   /* 下行SCH REC INFO */

    PS_BOOL_ENUM_UINT8                  enRevSchSupport;                                /* Reverse Supplemental Channel supported indicator */
    VOS_UINT8                           ucReserve3;
    VOS_UINT16                          usRevSchRcMap;                                  /* Reverse Supplemental Channel Radio Configuration capability */
    VOS_UINT8                           ucRevSchNum;                                    /* Number of Reverse Supplemental Channels */
    VOS_UINT8                           aucReserve4[3];
    CAS_1X_SCH_REC_INFO_STRU            astRevSchRecInfo[CAS_1X_MAX_SUPPORT_SCH_NUM];   /* 上行SCH REC INFO */
} CAS_1X_SCH_CFG_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_NVIM_CHANNEL_CFG_CAPA_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  信道支持的能力 add a nv id
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enOtdSupport;                           /* OTD supported indcator */
    PS_BOOL_ENUM_UINT8                  enStsSupport;                           /* STS supported indicator */
    PS_BOOL_ENUM_UINT8                  en3XCchSupport;                         /* 3X Common Channel supported */
    VOS_UINT8                           ucReserve;
    CAS_1X_FCH_CFG_INFO_STRU            stFchCfgInfo;                           /* fch 配置信息 */
    CAS_1X_DCCH_CFG_INFO_STRU           stDcchCfgInfo;                          /* dcch 配置信息 */
    CAS_1X_SCH_CFG_INFO_STRU            stSchCfgInfo;                           /* sch 配置信息 */
} CAS_1X_NVIM_CHANNEL_CFG_CAPA_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_FLEX_SPT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  flex支持能力
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enFlexSupport;                          /* Flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enFFchFlexSpt;                          /* Forward Fundamental channel flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enRFchFlexSpt;                          /* Reverse Fundamental channel flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enFDcchFlexSpt;                         /* Forward Dedicated Control channel flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enRDcchFlexSpt;                         /* Reverse Dedicated Control channel flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enFSchFlexSpt;                          /* Forward Supplemental channel flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enRSchFlexSpt;                          /* Reverse Supplemental channel flexible rate feature supported indicator */
    VOS_UINT8                           ucReserve;
} CAS_1X_FLEX_SPT_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_VAR_SPT_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : variable rate feature支持能力
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enVarSupport;                           /* Variable rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enFSchVarSpt;                           /* Forward Supplemental Channel Variable Rate supported indicator */
    PS_BOOL_ENUM_UINT8                  enRSchVarSpt;                           /* Reverse Supplemental Channel Variable Rate supported indicator */
    VOS_UINT8                           ucReserve;
    VOS_UINT16                          usMaxSumNumBitsC;                       /* Maximum sum of number of bits corresponding to Convolutional rates in the variable rate set */
    VOS_UINT16                          usMaxSumNumBitsT;                       /* Maximum sum of number of bits corresponding to Turbo Code rates in the variable rate set */
} CAS_1X_VAR_SPT_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_NVIM_CAPA_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  capability infomation
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMobPRev;                              /* MOB_P_REV: UE支持的协议版本 */
    PS_BOOL_ENUM_UINT8                  enPacketDataServSupp;                   /* MS supports packet data service */
    PS_BOOL_ENUM_UINT8                  enDeviceInfoMsgSupp;                    /* MS supports the  Device Information Message on the r-csch */
    PS_BOOL_ENUM_UINT8                  enPmSupported;                          /* PM: Voice Private Mode */
    PS_BOOL_ENUM_UINT8                  enTransMode;                            /* Transmission */

    PS_BOOL_ENUM_UINT8                  enAccessEntryHo;                        /* Access Entry Handoff Support */
    PS_BOOL_ENUM_UINT8                  enAccessProbeHo;                        /* Access Probe Handoff Support */
    PS_BOOL_ENUM_UINT8                  enAnalogSearch;                         /* Analog Search Support */
    PS_BOOL_ENUM_UINT8                  enHoppingBeacon;                        /* Hopping Beacon Support */
    PS_BOOL_ENUM_UINT8                  enMahHo;                                /* Mobile Assisted Hard Handoff Support */
    PS_BOOL_ENUM_UINT8                  enPuf;                                  /* Location Power Up Function Support */
    PS_BOOL_ENUM_UINT8                  enAnalog553A;                           /* Analog Support */
    PS_BOOL_ENUM_UINT8                  enQpchSupport;                          /* QPCH是否支持的标记 */
    PS_BOOL_ENUM_UINT8                  enBroadCastSupport;                     /* BC是否支持的标记 */

    PS_BOOL_ENUM_UINT8                  enSlottedClass;                         /* Slotted Class, scm第6位 */
    PS_BOOL_ENUM_UINT8                  enSlottedTimer;                         /* Slotted Timer Support */
    PS_BOOL_ENUM_UINT8                  enChsSupport;                           /* Control Hold Mode supported indicator */
    VOS_UINT8                           ucGatingRateSet;                        /* Set of supported Reverse Pilot gating rates */
    PS_BOOL_ENUM_UINT8                  enExtCapIncluded;                       /* Extended Capabilities Included indicator */
    PS_BOOL_ENUM_UINT8                  enMabo;                                 /* Mobile Assisted Burst Operation capability indicator */
    PS_BOOL_ENUM_UINT8                  enSdb;                                  /* Short Data Burst supported indicator */

    VOS_UINT8                           ucCdmaSptOpMode;                        /* UE支持的操作模式 */
    VOS_UINT8                           ucMinPwrCntlStep;                       /* Minimum power control step size */
    PS_BOOL_ENUM_UINT8                  enRevFchGating;                         /* REV_FCH_GATING_REQ */
    VOS_UINT8                           ucGeoLoc;                               /* Geo-location */
    PS_BOOL_ENUM_UINT8                  enSyncIdReportCapa;                     /* 标识MS是否支持上报SYNC ID */

    PS_BOOL_ENUM_UINT8                  enSupportMeid;                          /* Meid support, scm第6位 */
    VOS_UINT8                           aucReserve1[1];
} CAS_1X_NVIM_CAPA_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_NVIM_RATE_FEATURE_CAPA_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  rate feature capability infomation
*****************************************************************************/
typedef struct
{
    CAS_1X_FLEX_SPT_INFO_STRU           stFlexSptInfo;                          /* flex info 支持能力 */
    CAS_1X_VAR_SPT_INFO_STRU            stVarSptInfo;                           /* VAR支持能力 */
    PS_BOOL_ENUM_UINT8                  enCsSupport;                            /* Concurrent Services supported indicator */
    PS_BOOL_ENUM_UINT8                  enFSchLtuTabSpt;                        /* Forward Supplemental Channel Downloadable LTU tables supported indicator */
    PS_BOOL_ENUM_UINT8                  enRSchLtuTabSpt;                        /* Reverse Supplemental Channel Downloadable LTU tables supported indicator */
    VOS_UINT8                           aucReserve2[1];
} CAS_1X_NVIM_RATE_FEATURE_CAPA_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_SCH_MO_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  SCH支持的MO
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          ausMoForSch[CAS_1X_MAX_SCH_MO_NUM];
    VOS_UINT16                          ausMoRevSch[CAS_1X_MAX_SCH_MO_NUM];
} CAS_1X_SCH_MO_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_FCH_DCCH_MO_LIST_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : FCH DCCH MO能力
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMoNum;
    VOS_UINT16                          ausMoList[CAS_1X_FCH_DCCH_MAX_MO];
} CAS_1X_FCH_DCCH_MO_LIST_STRU;

/*****************************************************************************
 结构名    : CAS_1X_NVIM_MO_CAPA_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : MO能力
*****************************************************************************/
typedef struct
{
    CAS_1X_FCH_DCCH_MO_LIST_STRU        stFwdMo;                                /* Fwd Mo,FCH和DCCH支持的下行MO */
    CAS_1X_FCH_DCCH_MO_LIST_STRU        stRevMo;                                /* Rev Mo,FCH和DCCH支持的上行MO */
    CAS_1X_SCH_MO_INFO_STRU             stSchMoInfo;                            /* sch上支持的MO */
}CAS_1X_NVIM_MO_CAPA_STRU;

/*****************************************************************************
 结构名    : CAS_1X_NVIM_RC_PREF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : RC PREF能力
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucForRcPref;                            /* FOR_RC_PREF */
    VOS_UINT8                           ucRevRcPref;                            /* REV_RC_PREF */
    VOS_UINT8                           aucReserve[2];
}CAS_1X_NVIM_RC_PREF_STRU;

/*****************************************************************************
 结构名    : CAS_1X_NVIM_IMSI_TYPE_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : Imsi_T programmed标志 3508
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enProgrammedImsiT;                      /* IMSI_T programmed or not*/
    VOS_UINT8                           aucReserve[3];
}CAS_1X_NVIM_IMSI_TYPE_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_1X_NVIM_PROTOCOL_OPTIMIZE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 协议优化选项 3509
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enSaveSystemInfo;                       /* 是否缓存系统消息，默认缓存 */
    VOS_UINT8                           ucTaddDelta;                            /* Tadd增量系数 单位:0.5db 默认值为0 */
    VOS_UINT8                           ucTdropDelta;                           /* Tdrop增量系数 单位:0.5db 默认值为0 */
    VOS_UINT8                           aucReserve[5];
}CAS_1X_NVIM_PROTOCOL_OPTIMIZE_STRU;

/*****************************************************************************
 结构名    : CPROC_1X_NVIM_FILTER_COEF_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : CPROC 滤波系数,CAS 维护
*****************************************************************************/
typedef struct
{
    /* SF continuous */
    VOS_UINT16                          usSfContMpsAlphaEc;
    VOS_UINT16                          usSfContMpsAlphaEcIo;

    VOS_UINT16                          usSfContMeasAlphaEc;
    VOS_UINT16                          usSfContMeasAlphaEcIo;

    /* CF TCH */
    VOS_UINT16                          usCfContTchAlphaEc;
    VOS_UINT16                          usCfContTchAlphaEcIo;

    /* SF DRX */
    VOS_UINT16                          usSfDrxMpsOsAlphaEc;
    VOS_UINT16                          usSfDrxMpsOsAlphaEcIo;

    VOS_UINT16                          usSfDrxMpsContAlphaEc;
    VOS_UINT16                          usSfDrxMpsContAlphaEcIo;

    VOS_UINT16                          usSfDrxMeasAlphaEc;
    VOS_UINT16                          usSfDrxMeasAlphaEcIo;

    /* CF DRX */
    VOS_UINT16                          usCfDrxMeasAlphaEc;
    VOS_UINT16                          usCfDrxMeasAlphaEcIo;

    /* ilde continuous(reserve) */
    VOS_UINT16                          usSfContIdleMpsAlphaEc;
    VOS_UINT16                          usSfContIdleMpsAlphaEcIo;

    VOS_UINT16                          usSfContIdleMeasAlphaEc;
    VOS_UINT16                          usSfContIdleMeasAlphaEcIo;

}CPROC_1X_NVIM_FILTER_COEF_STRU;

/*****************************************************************************
 结构名    : CPROC_1X_NVIM_NXM_SWITCH_STRU
 协议表格  : C.S0005 Table D-2.
 ASN.1描述 :
 结构说明  : CPROC 在前向信道上较差信号质量的持续时间选择开关,CAS 维护, 3511
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucN2mHuaweiConfigValue;                /*N2m自定义配置值*/
    VOS_UINT8                          ucN3mHuaweiConfigValue;                /*N3m自定义配置值*/
    VOS_UINT8                          aucReserved[22];
}CPROC_1X_NVIM_NXM_SWITCH_STRU;
/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_REV_INFO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : EVDO终端版本信息 3600
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enSuppOnlyDo0;                          /* 是否只支持DO0版本 */
    PS_BOOL_ENUM_UINT8                  enSuppDoaWithMfpa;                      /* 是否支持DOA版本，应用类型只支持MFPA */
    PS_BOOL_ENUM_UINT8                  enSuppDoaWithEmfpa;                     /* 是否支持DOA版本，应用类型支持MFPA和EMPA */
    PS_BOOL_ENUM_UINT8                  enSuppDoaEhrpd;                         /* 是否支持eHRPD */
}CAS_HRPD_NVIM_REV_INFO_STRU;

/*****************************************************************************
 结构名    : CAS_CDMA_NVIM_SUPPORT_BANDCLASS_MASK_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 终端支持的频段能力掩码  3601
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSupportBandclassMask;               /* 终端支持的频段能力掩码，每bit表示是否支持对应的频段能力，比如0x00000001表示只支持频段0 */
}CAS_CDMA_NVIM_SUPPORT_BANDCLASS_MASK_STRU;

/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_CELL_THRESHOLD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 搜网门限相关信息结构  3602
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sPilotSrchRssiThreshold;              /* Pilot Srch Rssi Threshold */
    VOS_UINT8                           aucReserve[2];
}CAS_HRPD_NVIM_CELL_THRESHOLD_STRU;

/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_SUSPEND_TIMER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : 挂起定时器时长 3603
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usConnSuspendTimerLength;             /* AT进入挂起模式时，挂起定时器的时长，单位为ms */
    VOS_UINT8                           aucReserve[2];
}CAS_HRPD_NVIM_SUSPEND_TIMER_STRU;

/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_CONNCLOSE_TO_1X_SWITCH_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : DO到1x切换开关    3604
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enDO21XSwitch;                        /* 当HRPD连接态能量值低于sStrengthThresholdTo1x时，是否断开HRPD连接 */
    VOS_UINT8                           ucReserve;
    VOS_INT16                           sStrengthThresholdTo1x;               /* 连接态时激活集能量值监控门限，低于该门限，EVDO主动发起连接关闭，切换到1x */
}CAS_HRPD_NVIM_CONNCLOSE_TO_1X_SWITCH_STRU;



/*****************************************************************************
 结构名    : CAS_HRPD_C2L_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HRPD到LTE重选相关的参数  3605
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLteReselectTimerLen;                /* EVDO到LTE的重选时间 */
    VOS_INT16                           sHrpdQualityThreshold;                /* Hrpd Quality Threshold value, CL互操作使用，DO能建立业务信道的门限 */
    PS_BOOL_ENUM_UINT8                  enSortEUTRAFreqByOhmOrder;            /* 是否根据otherRatNeighbor list消息中的频点顺序，对要重选的频点进行排序 */
    VOS_UINT8                           ucReserve;
}CAS_HRPD_NVIM_C2L_STRU;

/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_IDLE_HO_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HRPD版本信息   3606
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sIdleHoOffset;                          /* idle ho 参数f*/
    VOS_INT16                           sIdleHoStrengthK;                       /* idle ho 参数k*/
    VOS_INT16                           sIdleHoThresh;                          /* idle ho 参数y*/
    VOS_UINT16                          usTimeLength;                           /* 监控时常,单位ms */
}CAS_HRPD_NVIM_IDLE_HO_STRU;

/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_CFG_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : HRPD配置协商相关参数  3607
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHscpAnPhaseTimerLength;             /* 配置协商AT协商阶段的保护定时器时长 */
    VOS_UINT8                           ucCfgMsgSendTimes;                    /* 配置协商过程中，ConfigurationRequest消息的发送次数，默认值为1 */
    VOS_UINT8                           ucKeyResponseTimeout;                 /* KeyResponse消息中的Timeout字段，单位为秒 */
    VOS_UINT8                           aucReserve[2];
}CAS_HRPD_NVIM_CFG_STRU;

/*****************************************************************************
 结构名    : CAS_HRPD_NVIM_TIMER_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  :  HRPD Timer类NV定义
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usConnectCloseDelayTimerLength;       /* 等待ConnectionClose消息发出时长，单位为ms */
    VOS_UINT16                          ucReserve1;
    VOS_UINT16                          ucReserve2;
    VOS_UINT16                          ucReserve3;
    VOS_UINT16                          ucReserve4;
    VOS_UINT16                          ucReserve5;
    VOS_UINT16                          ucReserve6;
    VOS_UINT16                          ucReserve7;
}CAS_HRPD_NVIM_TIMER_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


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

#endif /* end of CasNvInterface.h */

