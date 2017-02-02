

#ifndef __NAS_MSCC_SND_XSD_H__
#define __NAS_MSCC_SND_XSD_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "xsd_mscc_pif.h"
#include  "NasMsccPifInterface.h"
#include  "PsCommonDef.h"
#include  "NasMsccCtx.h"
#include  "MmaMsccInterface.h"
#include  "NasMsccFsmMain.h"
#include  "hsd_mscc_pif.h"

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
VOS_VOID NAS_MSCC_SndXsdStartReq(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8                     enCsimStatus,
    NAS_MSCC_PIF_RAT_PRIO_STRU                             *pstRatPrio
);

VOS_VOID NAS_MSCC_SndXsdPowerOffReq(
    NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32                    enCause
);

VOS_VOID NAS_MSCC_SndXsdCdmaMoCallStartNtf(
    MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU         *pstCdmaMoCallStartNtf
);

VOS_VOID NAS_MSCC_SndXsdCdmaMoCallRedialSysAcqNtf(
    MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU         *pstCdmaMoCallRedialSysAcqNtf
);

VOS_VOID NAS_MSCC_SndXsdCdmaMoCallSuccessNtf(
    MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU         *pstCdmaMoCallSuccessNtf
);

VOS_VOID NAS_MSCC_SndXsdCdmaMoCallEndNtf(
    MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU *pstCdmaMoCallEndNtf
);

VOS_VOID NAS_MSCC_SndXsdCfreqLockNtf(
    MMA_MSCC_CFREQ_LOCK_NTF_STRU       *pstCfreqLockNtf
);

VOS_VOID NAS_MSCC_SndXsdCdmacsqSetReq(
    MMA_MSCC_CDMACSQ_SET_REQ_STRU       *pstCdmacsqSetReq
);

VOS_VOID NAS_MSCC_SndXsdSysAcqReq(VOS_VOID);


VOS_VOID NAS_MSCC_SndXsdSysCfgReq(
    MMA_MSCC_SYS_CFG_SET_REQ_STRU      *pstSysCfgReq
);
VOS_VOID NAS_MSCC_SndXsdHrpdCasStatusInd(
    HSD_MSCC_CAS_STATUS_IND_STRU       *pstCasStatusInd
);

VOS_VOID NAS_MSCC_SndXsdPowerSaveReq(VOS_VOID);

/* Added by z00316370 for UTS 2015-5-22 begin */
VOS_VOID NAS_MSCC_SndXsdHandsetInfoQryReq(
    VOS_UINT32                          ulInfoType
);
/* Added by z00316370 for UTS 2015-5-22 end */


VOS_VOID NAS_MSCC_SndXsdSrvAcqReq(
    MMA_MSCC_SRV_ACQ_REQ_STRU          *pstSrvAcqReq
);

VOS_VOID NAS_MSCC_SndXsdBeginSessionNotify(
    MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU *pstBeginSessionNtf
);

VOS_VOID NAS_MSCC_SndXsdEndSessionNotify(
    MMA_MSCC_END_SESSION_NOTIFY_STRU   *pstEndSessionNtf
);

VOS_VOID NAS_MSCC_SndXsdEndEmcCallBackNtf( VOS_VOID );

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

#endif /* end of NasMsccSndXsd.h */
