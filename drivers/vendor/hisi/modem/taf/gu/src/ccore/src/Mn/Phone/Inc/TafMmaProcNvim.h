
#ifndef _TAF_MMA_PROC_NVIM_H
#define _TAF_MMA_PROC_NVIM_H

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "NVIM_Interface.h"
#include "MmaAppLocal.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MSCC_NV_ITEM_ACTIVE          (1)                                     /* NV��� */
#define NAS_MSCC_NV_ITEM_DEACTIVE        (0)                                     /* NV��δ���� */

/* GPRS GEA �㷨֧�ֺ궨�� */
#define NAS_MSCC_GPRS_GEA1_SUPPORT       (0x01)                                  /* ֧��GPRS GEA1�㷨 */
#define NAS_MSCC_GPRS_GEA1_VALUE         (0x80)                                  /* ֧��GEA1ʱ����������ֵ */
#define NAS_MSCC_GPRS_GEA2_VALUE         (0x40)                                  /* ֧��GEA2ʱ����������ֵ */
#define NAS_MSCC_GPRS_GEA3_VALUE         (0x20)                                  /* ֧��GEA3ʱ����������ֵ */
#define NAS_MSCC_GPRS_GEA4_VALUE         (0x10)                                  /* ֧��GEA4ʱ����������ֵ */
#define NAS_MSCC_GPRS_GEA5_VALUE         (0x08)                                  /* ֧��GEA5ʱ����������ֵ */
#define NAS_MSCC_GPRS_GEA6_VALUE         (0x04)                                  /* ֧��GEA6ʱ����������ֵ */
#define NAS_MSCC_GPRS_GEA7_VALUE         (0x02)                                  /* ֧��GEA7ʱ����������ֵ */

#define NAS_MSCC_GPRS_GEA2_SUPPORT       (0x02)                                  /* ֧��GPRS GEA2�㷨 */
#define NAS_MSCC_GPRS_GEA3_SUPPORT       (0x04)                                  /* ֧��GPRS GEA3�㷨 */
#define NAS_MSCC_GPRS_GEA4_SUPPORT       (0x08)                                  /* ֧��GPRS GEA4�㷨 */
#define NAS_MSCC_GPRS_GEA5_SUPPORT       (0x10)                                  /* ֧��GPRS GEA5�㷨 */
#define NAS_MSCC_GPRS_GEA6_SUPPORT       (0x20)                                  /* ֧��GPRS GEA6�㷨 */
#define NAS_MSCC_GPRS_GEA7_SUPPORT       (0x40)                                  /* ֧��GPRS GEA7�㷨 */
#define NAS_MSCC_NVIM_MAX_EPLMN_NUM      (16)                                    /* en_NV_Item_EquivalentPlmn NV�е�Чplmn���� */
#define NAS_MSCC_NVIM_MAX_MCC_SIZE       (3)                                     /* plmn��Mcc��󳤶� */
#define NAS_MSCC_NVIM_MAX_MNC_SIZE       (3)                                     /* plmn��Mnc��󳤶� */
#define NAS_MSCC_LOW_BYTE_MASK           (0x0f)

#define NAS_MSCC_MAX_USER_CFG_IMSI_PLMN_NUM                  (6)                 /* �û����õ�����֧�ֵ�USIM/SIM���ĸ��� */
#define NAS_MSCC_MAX_USER_CFG_EHPLMN_NUM                     (6)                 /* �û����õ�EHplmn�ĸ��� */
#define NAS_MSCC_MAX_BLACK_LOCK_PLMN_WITH_RAT_NUM            (8)                 /* ��ֹ���뼼����PLMN ID�������� */

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
VOS_VOID TAF_MMA_ReadUeSupporttedGuBandNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadForbBandNvim(VOS_VOID);
VOS_UINT32  TAF_MMA_ReadFreqBandNvim(VOS_VOID);
#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_MMA_ReadNvimUeSupporttedLteBand(VOS_VOID);
VOS_VOID TAF_MMA_ReadUserSetLteBands(VOS_VOID);
#endif
VOS_VOID MMA_UpdateBandNvRefForbBand(VOS_VOID);
VOS_VOID MMA_UpdateForbBandStatusToNV(VOS_VOID);
VOS_VOID TAF_MMA_UpdateUeAllowedBandRange(VOS_VOID);
VOS_VOID TAF_MMA_ReadProductNameNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadFmridNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadImeiNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadSystemAppCofigNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadNotDisplayLocalNetworkNameNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadDisplaySpnFlagNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadEFustServiceCfgNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadRfAutoTestFlagNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadFollowonOpenSpeedFlagNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadUserSettedBandNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadAccessModeNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadReportPlmnSupportFlgNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadRoamingBrokerInfoNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadRoamCapaNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadMsClassNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadPlmnSelectionModeNvim(VOS_VOID);
VOS_UINT32 TAF_MMA_ReadAlphanumericNameByPlmnIdNvim( TAF_PH_OPERATOR_NAME_STRU   *pstOperName);
VOS_VOID TAF_MMA_ReadDeactUsimWhenPoweroffNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadSimPersonalisationPwdNvim( VOS_VOID );

VOS_VOID TAF_MMA_ReadLcCtrlNvim( VOS_VOID );
VOS_VOID TAF_MMA_ReadUeSupporttedCPHSFlagNvim(VOS_VOID);
VOS_VOID  TAF_MMA_ReadPsStartNvim( VOS_VOID );
VOS_VOID  TAF_MMA_ReadCardLockStatusNvim( VOS_VOID );
VOS_VOID  TAF_MMA_ReadSimLockMaxTimesNvim( VOS_VOID );
VOS_VOID  TAF_MMA_ReadSimLockPlmnNvim( VOS_VOID );
VOS_UINT32  TAF_MMA_ReadLastImsiNvim(
    NAS_MMC_NVIM_LAST_IMSI_STRU        *pstLastImsi
);
#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  TAF_MMA_ReadLastTinInfoNvim(
    NAS_NVIM_TIN_INFO_STRU             *pstTinInfo
);
#endif

VOS_VOID TAF_MMA_WritePlmnSelectionModeNvim(VOS_UINT8 ucReselMode);

VOS_VOID TAF_MMA_UpdateUeBandNvim(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_MMA_UpdateUserSetLteBands(VOS_VOID);
#endif

/* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, begin */
VOS_VOID TAF_MMA_ReadCFreqLockNvim(VOS_VOID);
/* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, end */

VOS_VOID TAF_MMA_ReadPlatformRatCap(VOS_VOID);
VOS_VOID TAF_MMA_ReadCcpuResetRecordNvim(VOS_VOID);
VOS_VOID TAF_MMA_ReadGetGeoCfgInfoNvim(VOS_VOID);

#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 TAF_MMA_UpdataVoiceDomainNv(
    VOS_UINT32                          ulVoiceDomain
);

VOS_UINT32 TAF_MMA_UpdateLteImsSupportNv(
    VOS_UINT8                           ucFlag
);
#endif


/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
VOS_VOID TAF_MMA_ReadDelayReportServiceStatusCfgNvim(VOS_VOID);
/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */
/* Added by y00322978 for CDMA 1X Iteration 17, 2015-8-22, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_MMA_ReadEsnFromNvim( VOS_VOID );
VOS_VOID TAF_MMA_ReadMeidFromNvim( VOS_VOID );
#endif
/* Added by y00322978 for CDMA 1X Iteration 17, 2015-8-22, end */

VOS_VOID TAF_MMA_ReadNonnormalRegStatusMergeCfgNvim( VOS_VOID );

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

