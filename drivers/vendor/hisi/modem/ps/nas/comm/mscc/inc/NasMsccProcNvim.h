

#ifndef __NAS_MSCC_PROC_NVIM_H__
#define __NAS_MSCC_PROC_NVIM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "NasMsccCtx.h"


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

VOS_VOID NAS_MSCC_ReadImsRatSupportNvim(VOS_VOID);

VOS_VOID NAS_MSCC_ReadVoiceDomainNvim(VOS_VOID);

VOS_VOID NAS_MSCC_ReadWaitImsVoiceCapTimerLenNvim(VOS_VOID);

VOS_VOID NAS_MSCC_ReadImsCfgInfoNvim(VOS_VOID);

VOS_VOID NAS_MSCC_ReadPlatformRatCapNvim(VOS_VOID);


VOS_VOID NAS_MSCC_ReadMmssSystemAcquireCfgNvim(VOS_VOID);

VOS_VOID NAS_MSCC_ReadLastLocationInfoNvim(VOS_VOID);

VOS_VOID NAS_MSCC_WriteMmssLocationInfoNvim(
    NAS_MSCC_MMSS_LOCATION_INFO_STRU                       *pstMmssLocationInfo
);

VOS_VOID NAS_MSCC_ReadMmssNvimInfo(VOS_VOID);


VOS_UINT8 NAS_MSCC_ReadMlplMsplNvim(
    NAS_MSCC_NVIM_MLPL_MSPL_STRU                            *pstNvimMlplMspl
);

VOS_VOID NAS_MSCC_ReadNvim(VOS_VOID);



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
