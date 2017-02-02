/******************************************************************************

                  ��Ȩ���� (C), 2003-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : gunas_errno.h
  �� �� ��   : ����
  ��    ��   : ��ˮ��/wx247453
  ��������   : 2015��8��25��
  ����޸�   :
  ��������   : gunas���������ӿڵ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��08��25��
    ��    ��   : ��ˮ��/wx247453
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __GUNAS_ERRNO_H__
#define __GUNAS_ERRNO_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ����DRV_SYSTEM_ERRORʱ, �����Ҫ��������FID������ջ��Ϣ�轫��24 Bit��λ */

#define NAS_MML_SAVE_OTHER_FID_TCB_FLAG                 (1<<24)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum NAS_MML_REBOOT_MOD_ID_ENUM
{
    NAS_REBOOT_MOD_ID_MML   = 0X60000000,
    NAS_REBOOT_MOD_ID_BUTT  = 0X6FFFFFFF
};
typedef VOS_UINT32 NAS_MML_REBOOT_MOD_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MML_REBOOT_SCEAN_ENUM
 ö��˵��  : MM��λ����
 1.��    ��   : 2015��1��27��
   ��    ��   : wx270776
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MML_REBOOT_SCEAN_ENUM
{
    NAS_MML_OTHER_REBOOT_SCENE                                                  = 0X00,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_SUSPEND_CNF_EXPIRED                       = 0X01,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED                       = 0X02,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED                        = 0X03,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED                       = 0X04,

    NAS_MML_REBOOT_SCENE_MMC_IN_LMM_WAIT_RESUME_IND_EXPIRED                     = 0X05,
    NAS_MML_REBOOT_SCENE_MMC_IN_WAS_WAIT_RESUME_IND_EXPIRED                     = 0X06,
    NAS_MML_REBOOT_SCENE_MMC_IN_TD_WAIT_RESUME_IND_EXPIRED                      = 0X07,
    NAS_MML_REBOOT_SCENE_MMC_IN_GAS_WAIT_RESUME_IND_EXPIRED                     = 0X08,
    NAS_MML_REBOOT_SCENE_MMC_WAIT_CMMCA_RESUME_IND_EXPIRED                      = 0X09,

    NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_LMM_RESUME_IND              = 0X0A,
    NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_WAS_RESUME_IND              = 0X0B,
    NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_TD_RESUME_IND               = 0X0C,
    NAS_MML_REBOOT_SCENE_MMC_NOT_IN_INTERSYSFSM_RCV_GAS_RESUME_IND              = 0X0D,

    NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_LMM_SUSPEND_IND                 = 0X0E,
    NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_WAS_SUSPEND_IND                 = 0X0F,
    NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_TD_SUSPEND_IND                  = 0X10,
    NAS_MML_REBOOT_SCENE_MMC_IN_INTERSYSFSM_RCV_GAS_SUSPEND_IND                 = 0X11,

    NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE                        = 0X12,
    NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE                        = 0X13,
    NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE                         = 0X14,
    NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE                        = 0X15,

    NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_ERR_IND                                = 0X16,
    NAS_MML_REBOOT_SCENE_MMC_NO_MASTER_AND_SLAVE_MODE                           = 0X17,
    NAS_MML_REBOOT_SCENE_MMC_READ_PLATFORM_RAT_CAP_NVIM_FAILURE                 = 0X18,
    /* Added by l00324781 for CDMA Iteration 12, 2015-5-29, begin */
    NAS_MML_REBOOT_SCENE_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_EXPIRED                = 0x19
    /* Added by l00324781 for CDMA Iteration 12, 2015-5-29, end */
};
typedef VOS_UINT8 NAS_MML_REBOOT_SCENE_ENUM_UINT8;


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of gunas_errno.h */
