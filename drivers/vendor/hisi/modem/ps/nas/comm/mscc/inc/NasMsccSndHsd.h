

#ifndef __NAS_MSCC_SND_HSD_H__
#define __NAS_MSCC_SND_HSD_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "MmaMsccInterface.h"
#include  "hsd_mscc_pif.h"
#include  "NasMsccFsmMain.h"
#include  "MsccMmcInterface.h"
#include  "NasMsccMlplMsplParse.h"

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


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID NAS_MSCC_SndHsdStartReq(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimStatus,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enUsimStatus,
    NAS_MSCC_PIF_RAT_PRIO_STRU                             *pstRatPrio
);

VOS_VOID NAS_MSCC_SndHsdPowerOffReq(
    MSCC_HSD_POWER_OFF_CAUSE_ENUM_UINT32                    enCause
);

VOS_VOID NAS_MSCC_SndHsdCdmaMoCallStartNtf(
    MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU         *pstCdmaMoCallStartNtf
);

/* Modified by y00307564 for CDMA Iteration 10 2015-4-7 begin */
VOS_VOID NAS_MSCC_SndHsdSysAcqReq(
    MSCC_HSD_ACQUIRE_REASON_ENUM_UINT32 enAcqReason,
    VOS_UINT8                           ucHighPrioHrpdNum,
    VOS_VOID                           *pucHighPrioHrpdList
);

/* Modified by y00307564 for CDMA Iteration 10 2015-4-7 end */
VOS_VOID NAS_MSCC_SndHsdCdmaMoCallRedialSysAcqNtf(
    MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU         *pstCdmaMoCallRedialSysAcqNtf
);

VOS_VOID NAS_MSCC_SndHsdCdmaMoCallSuccessNtf(
    MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU         *pstCdmaMoCallSuccessNtf
);

VOS_VOID NAS_MSCC_SndHsdCdmaMoCallEndNtf(
    MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU *pstCdmaMoCallEndNtf
);

VOS_VOID NAS_MSCC_SndHsdCfreqLockNtf(
    MMA_MSCC_CFREQ_LOCK_NTF_STRU       *pstCfreqLockNtf
);

VOS_VOID NAS_MSCC_SndHsdCdmacsqSetReq(
    MMA_MSCC_CDMACSQ_SET_REQ_STRU       *pstCdmacsqSetReq
);
/* Added by m00312079 for CDMA Iteration 10 2015-4-4 begin */
VOS_VOID NAS_MSCC_SndHsdDisableLteNtf(VOS_VOID);

VOS_VOID NAS_MSCC_SndHsd1xSysChgInd(
    VOS_UINT8                           ucIs1xAvail,
    MSCC_HSD_1X_SYS_INFO_STRU          *pst1xSysInfo
);

VOS_VOID NAS_MSCC_SndHsdPowerSaveReq(VOS_VOID);
/* Added by m00312079 for CDMA Iteration 10 2015-4-4 end */

/* Added by x00314862 for CDMA Iteration 10 2015-4-7 begin */
VOS_VOID NAS_MSCC_SndHsdBgSearchReq(
    VOS_RATMODE_ENUM_UINT32             enRatMode
);

VOS_VOID NAS_MSCC_SndHsdStopBgSearchReq(VOS_VOID);
/* Added by x00314862 for CDMA Iteration 10 2015-4-7 end */

/* Added by y00307564 for CDMA Iteration 10 2015-4-7 begin */
VOS_VOID NAS_MSCC_SndHsdQryHrpdSysInfoReq(
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enDestBsrSysType,
    VOS_UINT8                                               ucHrpdSysNum,
    MSCC_MMC_HRPD_SYS_STRU                                 *pstHrpdSysList
);
/* Added by y00307564 for CDMA Iteration 10 2015-4-7 end */

VOS_VOID NAS_MSCC_SndHsdSysCfgReq(
    MMA_MSCC_SYS_CFG_SET_REQ_STRU      *pstSysCfgReq
);

#if(FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_MSCC_SndHsdSrvAcqReq(
    MMA_MSCC_SRV_ACQ_REQ_STRU          *pstSrvAcqReq
);

VOS_VOID NAS_MSCC_SndHsdBeginSessionNotify(
    MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU *pstBeginSessionNtf
);

VOS_VOID NAS_MSCC_SndHsdEndSessionNotify(
    MMA_MSCC_END_SESSION_NOTIFY_STRU   *pstEndSessionNtf
);
#endif






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

#endif /* end of NasMsccSndHsd.h */
