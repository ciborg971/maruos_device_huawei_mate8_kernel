

#ifndef __MTCCOMM_H__
#define __MTCCOMM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#include "MtcMmaInterface.h"

#include "MtcPsTransfer.h"

#include "MtcRcmInterface.h"

#include "CmmcaMtcInterface.h"
/* Added by wx270776 for OM�ں�, 2015-8-23, begin */
#include "TafNvInterface.h"
/* Added by wx270776 for OM�ں�, 2015-8-23, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CMMCA_MAX_EUTRA_NEIGHBOR_PLMN_NUM       (8)
#define CMMCA_MAX_ARFCN_NUM                     (8)
#define CBPCA_MSG_DATA_RSV_LEN                  (4)                 /* CBPCA�շ�����Ϣ�ṹ���У�������ʱ���� */

#define MTC_ALLOC_MSG_WITH_HDR(ulMsglen)\
            PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MTC, (ulMsglen))

#define MTC_GET_MSG_ENTITY(pstMsg)\
            ((VOS_VOID *)&(((MSG_HEADER_STRU *)(pstMsg))->ulMsgName))

#define MTC_GET_MSG_LENGTH(pstMsg)\
            (((MSG_HEADER_STRU *)(pstMsg))->ulLength)

#define MTC_CFG_MSG_HDR(pstMsg, ulRecvPid, ulMsgId)\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderPid     = UEPS_PID_MTC;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverPid   = (ulRecvPid);\
            ((MSG_HEADER_STRU *)(pstMsg))->ulMsgName       = (ulMsgId)

#define MTC_CFG_I1_GAS_MSG_HDR(pstMsg, ulMsgId)\
            MTC_CFG_MSG_HDR(pstMsg, I1_UEPS_PID_GAS, ulMsgId)

#define MTC_SEND_MSG(pstMsg)\
            if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstMsg))\
            {\
                MTC_ERROR_LOG("MTC_SEND_MSG: Send message fail!\n");\
            }

#define MTC_CFG_RCM_MSG_HDR(pstMsg, ulMsgId)\
            MTC_CFG_MSG_HDR(pstMsg, DSP_PID_RCM, ulMsgId)

#define MTC_CFG_IMSA_MSG_HDR(pstMsg, ulMsgId)\
            MTC_CFG_MSG_HDR(pstMsg, PS_PID_IMSA, ulMsgId)

#define MTC_NO_SESSION_INFO          (0)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
#if 0

enum CMMCA_RAT_ID_ENUM
{
    CMMCA_RAT_NULL,
    CMMCA_CDMA2K1X      = 2,        /* 1X */
    CMMCA_GERAN,                    /* GSM */
    CMMCA_CDMA2KHRPD,               /* DO */
    CMMCA_UTRAN,                    /* 3GPP */
    CMMCA_CDMA2KAI,                 /* 1X&DO, for matching type MMSS_SYS_CDMA2000_AI */
    CMMCA_EUTRAN        = 9,        /* LTE */
    CMMCA_3GPPAI,                   /* GSM&UMTS&LTE, for matching type MMSS_SYS_3GPP_AI */
    CMMCA_RAT_ID_BUTT
};
typedef VOS_UINT8 CMMCA_RAT_ID_ENUM_UINT8;
enum CMMCA_MMC_RAT_CMD_ID_ENUM
{
    ID_CMMCA_MMC_RAT_OTHER_RAT_INFO_IND             = 0x18,
    ID_CMMCA_MMC_RAT_CMD_MAX,
};
typedef VOS_UINT8 CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16;
#endif

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
#if 0

typedef struct
{
    VOS_UINT16                          usEarfcn;                               /* EUTRA channel number */
    /* priority of EARFCN of the neighbir EUTRA system. 0xff means not provided */
    VOS_UINT8                           ucEarfcnPri;
    /* Min required signal threshold used for selecting an EARFCN,
        The actual threshold value in dB used to compare against the measured reference signal receive Power(RSRP).*/
    VOS_UINT8                           ucThreshX;
    /* Min ref power level to select EUTRA, which in dBm is equal to the minimum
        reference signal received power(RSRP) level of a EUTRA cell required for the UE to reselect EUTRA.*/
    VOS_UINT16                          usRxLevMinEutra;
    /* Offset to min ref power level to select EUTRA. 0xff means not provided */
    VOS_UINT8                           ucRxLevMinEutraOffset;
    /* Max TX power level UE may use when transmitting up-link of EUTRA */
    VOS_UINT8                           ucPeMax;
    /* measurement bandwidth Nrb value, Table 7.1-1 */
    VOS_UINT8                           ucMeasBandWidth;
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT8                           ucNumPlmn;                              /* number of PLMN on this EARFCN channel */
    /* PLMN ID of the neighbor EUTRA system. 0xffffffff means not provided */
    VOS_UINT32                          aulPlmnId[CMMCA_MAX_EUTRA_NEIGHBOR_PLMN_NUM];
} CMMCA_OTHER_RAT_INFO_STRU;
typedef struct
{
    CMMCA_MMC_RAT_CMD_ID_ENUM_UINT16    enCmdId;
    CMMCA_RAT_ID_ENUM_UINT8             enRatId;
    VOS_UINT8                           aucReserved1[1];
    VOS_UINT16                          usEarfcnListSize;
    CMMCA_OTHER_RAT_INFO_STRU           astOtherRatInfo[CMMCA_MAX_ARFCN_NUM];
}CMMCA_OTHER_RAT_INFO_IND_STRU;
#endif

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID MTC_RcvMmaRatModeInd(VOS_VOID *pMsg);

VOS_VOID MTC_SndMmaOtherModemDplmnNplmnInfoNotify(
    MODEM_ID_ENUM_UINT16                enModemId,
    MODEM_ID_ENUM_UINT16                enOtherModemId
);

VOS_VOID MTC_RcvMmaPowerStateInd(VOS_VOID *pMsg);

VOS_VOID MTC_RcvTafCsSrvInfoInd(VOS_VOID *pMsg);

VOS_VOID MTC_RcvMmaRegStatusInd(VOS_VOID *pMsg);

VOS_VOID MTC_RcvMmaCurrCampPlmnInfoInd(VOS_VOID *pMsg);

VOS_VOID MTC_SndMmaOtherModemInfoNotify(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MMA_PLMN_ID_STRU               *pstPlmnId,
    MTC_MMA_EPLMN_INFO_STRU            *pstEplmnInfo
);

VOS_VOID MTC_RcvMmaImsaStateInd(VOS_VOID *pMsg);

VOS_VOID MTC_RcvMmaEplmnInfoInd(VOS_VOID *pMsg);

VOS_VOID MTC_RcvRrcNcellInfoInd(VOS_VOID * pMsg);

VOS_VOID MTC_SndMmaNcellInfoInd(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MMA_TDS_NCELL_INFO_STRU        *pstTddNcellInfo,
    MTC_MMA_LTE_NCELL_INFO_STRU        *pstLteNcellInfo
);

VOS_UINT32 MTC_GetOtherModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    MODEM_ID_ENUM_UINT16               *penOtherModemId
);

#if 0
VOS_VOID MTC_RcvCbpcaDataInd(VOS_VOID *pMsg);

VOS_VOID MTC_ParseCmmcaOtherRatInfo(
    VOS_UINT8                         **ppMsgBuff,
    CMMCA_OTHER_RAT_INFO_STRU          *pstOtherRatInfo
);

VOS_UINT32 MTC_ParseCmmcaOtherRatInfoInd(
    VOS_UINT8                          *pMsg,
    CMMCA_OTHER_RAT_INFO_IND_STRU      *pstOtherRatInfoInd
);
#endif

VOS_VOID MTC_TransCdmaPlmnId(
    VOS_UINT32                          ulSrcPlmnId,
    MTC_MMA_PLMN_ID_STRU               *pstDetPlmnId
);

VOS_UINT32 MTC_IsContainPlmnId(
    MTC_MMA_PLMN_ID_STRU               *pstPlmnId,
    VOS_UINT32                          ulPlmnNum,
    MTC_MMA_PLMN_ID_STRU               *pastSrcPlmnId
);

VOS_UINT32 MTC_GetEplmnFromOtherRatInfoInd(
    MTC_MMA_EPLMN_INFO_STRU            *pstEplmnInfo,
    CMMCA_OTHER_RAT_INFO_IND_STRU      *pstOtherRatInfoInd
);

VOS_UINT32 MTC_GetLteNcellInfoFromOtherRatInfoInd(
    MTC_MMA_LTE_NCELL_INFO_STRU        *pstLteNcellInfo,
    CMMCA_OTHER_RAT_INFO_IND_STRU      *pstOtherRatInfoInd
);

VOS_VOID MTC_RcvCmmcaOtherRatInfoInd(VOS_VOID* pMsg);

/* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, begin */
VOS_VOID MTC_ProcSetCdmaExtModemConnStateInfo(VOS_VOID* pMsg);
/* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, end */

VOS_VOID MTC_ProcModemServiceConnStateInd(VOS_VOID *pMsg);

VOS_VOID MTC_ProcImsaSrvConnStateInfo(VOS_VOID* pMsg);

VOS_VOID MTC_ProcUsimmStateInd(VOS_VOID *pMsg);


VOS_VOID MTC_RcvGsmCellInfoExInd(VOS_VOID *pMsg);

VOS_VOID MTC_RcvMtaGsmCellInfoQryReq(VOS_VOID *pMsg);

VOS_VOID MTC_RcvTcStatusInfo(
    VOS_VOID                           *pMsg
);
/* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, begin */
MTC_RCM_RAT_MODE_ENUM_UINT16 MTC_ConvertRcmRatMode(
    MTC_NAS_RAT_MODE_ENUM_UINT16        enMtcNasRatMode
);
/* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, end */

/* Added by w00316404 for NEXT B26 Project, 2015-6-17, begin */
VOS_VOID MTC_RcvMmaImsVoiceCapInd(VOS_VOID *pMsg);
/* Added by w00316404 for NEXT B26 Project, 2015-6-17, end */

VOS_VOID MTC_ProcBeginSessionInd(VOS_VOID *pMsg);

VOS_VOID MTC_ProcEndSessionInd(VOS_VOID *pMsg);

PS_BOOL_ENUM_UINT8 MTC_IsNeedSndTasCsInfo2Rcm(
    MODEM_ID_ENUM_UINT16                enModemId,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvConnState,
    MTC_CS_TYPE_ENUM_UINT8              enCsType
);

PS_BOOL_ENUM_UINT8 MTC_IsNeedBufModem0Msg(VOS_UINT32 ulSendPid);

PS_BOOL_ENUM_UINT8 MTC_IsNeedPopModem0BufMsg(VOS_UINT32 ulSendPid);

VOS_VOID MTC_ProcModem0BufMsg(VOS_VOID);


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

#endif /* end of MtcComm.h */
