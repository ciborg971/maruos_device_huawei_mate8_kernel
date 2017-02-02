

#ifndef __MTCINTRUSION_H__
#define __MTCINTRUSION_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "MtcComm.h"
#include "MtcCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MTC_BAND_B3_BIT                 (2)
#define MTC_BAND_B8_BIT                 (7)
#define MTC_BAND_B31_BIT                (30)
#define MTC_BAND_B32_BIT                (31)
#define MTC_BAND_B39_BIT                (6)
#define MTC_BAND_B40_BIT                (7)
#define MTC_BAND_WITHOUT_B3             (0x3FFFFFFB)
#define MTC_BAND_B34_BIT                (1)

#ifndef FUNC_VOID
typedef void (*func_void_t)(void);
#define FUNC_VOID func_void_t
#endif

#define MTC_BAND_MASK_B39               (MTC_SET_BIT64(38))

#define MTC_BAND_CHECK64(band1, band2)\
            (((VOS_UINT64)(band1) & (VOS_UINT64)(band2)) ? VOS_TRUE : VOS_FALSE)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum MTC_INTRUSION_GSM_BAND_STATE_ENUM
{
    MTC_INTRUSION_GSM_BAND_NONE         = 0x00,                                 /* ���κ�Ƶ����Ϣ(����) */
    MTC_INTRUSION_GSM_BAND_B31,                                                 /* ������B31 */
    MTC_INTRUSION_GSM_BAND_B32,                                                 /* ������B32 */
    MTC_INTRUSION_GSM_BAND_B3,                                                  /* ����B3(B31 B32) */
    MTC_INTRUSION_GSM_BAND_OTHER,                                               /* ���ڷ�B3 */
    MTC_INTRUSION_GSM_BAND_B31_OTHER,                                           /* ����B31����B3 */
    MTC_INTRUSION_GSM_BAND_B32_OTHER,                                           /* ����B32����B3 */
    MTC_INTRUSION_GSM_BAND_B3_OTHER,                                            /* ����B3(B31 B32)����B3 */

    MTC_INTRUSION_GSM_BAND_STATE_BUTT
};
typedef VOS_UINT8 MTC_INTRUSION_GSM_BAND_STATE_ENUM_UINT8;


enum MTC_INTRUSION_TL_BAND_STATE_ENUM
{
    MTC_INTRUSION_TL_BAND_NONE          = 0x00,                                 /* ���κ�Ƶ����Ϣ(����) */
    MTC_INTRUSION_TL_BAND_WITH_B39,                                             /* ����B39Ƶ�� */
    MTC_INTRUSION_TL_BAND_WITHOUT_B39,                                          /* ������B39Ƶ�� */

    MTC_INTRUSION_TL_BAND_STATE_BUTT
};
typedef VOS_UINT8 MTC_INTRUSION_TL_BAND_STATE_ENUM_UINT8;


/*****************************************************************************
  4 STRUCT����
*****************************************************************************/

typedef struct
{
    MTC_INTRUSION_GSM_BAND_STATE_ENUM_UINT8         enGsmBandState;             /* modem1 GSM����Ƶ��״̬ */
    MTC_INTRUSION_TL_BAND_STATE_ENUM_UINT8          enTLBandState;              /* modem0 TDS��LTE����Ƶ��״̬ */
    MTC_CS_SERVICE_STATE_ENUM_UINT8                 enCsSrvState;               /* modem1 CS��ҵ��״̬ */
    FUNC_VOID                                       pFunc;                      /* �þ����ִ�к��� */
} MTC_INTRUSION_RULING_STRATEGY_STRU;


typedef struct
{
    VOS_UINT8                                       ucBand31;                   /* Band31����״̬ */
    VOS_UINT8                                       ucBand32;                   /* Band32����״̬ */
    VOS_UINT8                                       ucBandOther;                /* ��Band3����״̬ */
    MTC_INTRUSION_GSM_BAND_STATE_ENUM_UINT8         enGsmBandState;             /* ��Ӧ��GSMƵ��״̬ö��ֵ */
} MTC_INTRUSION_GSM_BAND_STATE_STRU;

/*****************************************************************************
  5 OTHERS����
*****************************************************************************/

/*****************************************************************************
  6 ��������
*****************************************************************************/
VOS_VOID MTC_SndRrcIntrusionActionSetReq(
    VOS_UINT32                          ulRecvPid,
    PS_BOOL_ENUM_UINT8                  enEnableFlag
);

VOS_VOID MTC_SndModem0IntrusionActionSetReq(
    PS_BOOL_ENUM_UINT8                  enEnableFlg
);

VOS_VOID MTC_SndModem1IntrusionActionSetReq(
    PS_BOOL_ENUM_UINT8                  enEnableFlg
);

VOS_VOID MTC_SndRrcIntrusionBandSetReq(
    VOS_UINT32                          ulRecvPid,
    RRC_MTC_MS_BAND_INFO_STRU          *pstForbiddenBandInfo
);

VOS_VOID MTC_IntrusionDisableB39(VOS_VOID);

VOS_VOID MTC_IntrusionDisableB3(VOS_VOID);

VOS_VOID MTC_IntrusionEnableB39(VOS_VOID);

VOS_VOID MTC_IntrusionEnableB3(VOS_VOID);

VOS_VOID MTC_IntrusionEnableB3B39(VOS_VOID);

VOS_VOID MTC_ProcIntrusionStrategy(VOS_VOID);

VOS_VOID MTC_SndIntrusionActionSetReq(
    MODEM_ID_ENUM_UINT16                enModemId,
    PS_BOOL_ENUM_UINT8                  enEnableFlg
);

VOS_VOID MTC_IntrusionModemPowerStateChange(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enPowerState
);

MTC_INTRUSION_GSM_BAND_STATE_ENUM_UINT8 MTC_GetModem1GsmBandState(VOS_VOID);

MTC_INTRUSION_TL_BAND_STATE_ENUM_UINT8 MTC_GetModem0TLBandState(VOS_VOID);

VOS_VOID MTC_RcvIntrusionActionSetCnf(VOS_VOID * pMsg);

VOS_VOID MTC_RcvIntrusionBandSetCnf(VOS_VOID * pMsg);

VOS_VOID MTC_RcvIntrusionBandInfoInd(VOS_VOID * pMsg);

PS_BOOL_ENUM_UINT8 MTC_CheckM1GsmWithB3(VOS_VOID);
PS_BOOL_ENUM_UINT8 MTC_CheckM0TLWithB34B39(VOS_VOID);
VOS_VOID MTC_ProcNotchStrategy(VOS_VOID);
VOS_VOID MTC_ChangeNotchState(PS_BOOL_ENUM_UINT8 enEnableFlag);
VOS_VOID MTC_SndRrcNotchChannelInd(
    VOS_UINT32                          ulRecvPid,
    PS_BOOL_ENUM_UINT8                  enEnableFlag
);

PS_BOOL_ENUM_UINT8 MTC_CheckGsmWithB31(
    RRC_MTC_MS_BAND_INFO_STRU          *pulBandInfo
);
PS_BOOL_ENUM_UINT8 MTC_CheckGsmWithB32(
    RRC_MTC_MS_BAND_INFO_STRU          *pulBandInfo
);
VOS_VOID MTC_SndRrcBandCfgInd(
    VOS_UINT32                          ulRecvPid,
    PS_BOOL_ENUM_UINT8                  enEnableFlag
);
VOS_VOID MTC_ChangeNarrowBandDcsState(
    PS_BOOL_ENUM_UINT8                  enEnableFlag
);
VOS_VOID MTC_ProcNarrowDcsStrategy(VOS_VOID);



VOS_VOID MTC_SndI1GasRrcTdsLteRfCtrlInd(PS_BOOL_ENUM_UINT8 enUplinkCloseFlag);

VOS_VOID MTC_SndRrcRseCfgInd(
    VOS_UINT32                          ulRcvPid,
    PS_BOOL_ENUM_UINT8                  enRseOnFlag
);

VOS_VOID MTC_ProcRseStrategy(VOS_VOID);


PS_BOOL_ENUM_UINT8 MTC_ProcB39B32IntrusionStrategy(VOS_VOID);
VOS_VOID MTC_ProcB39B32Intrusion(VOS_VOID);

MTC_INTRUSION_TL_BAND_STATE_ENUM_UINT8 MTC_GetModem0NCellTLBandState(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
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



