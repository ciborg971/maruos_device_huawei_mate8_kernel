/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_g3d_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:35
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_G3D.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_G3D_INTERFACE_H__
#define __SOC_G3D_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_GPU_ID_UNION */
#define SOC_G3D_GPU_ID_ADDR(base)                     ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_L2_FEATURES_UNION */
#define SOC_G3D_L2_FEATURES_ADDR(base)                ((base) + (0x0004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TILER_FEATURES_UNION */
#define SOC_G3D_TILER_FEATURES_ADDR(base)             ((base) + (0x000C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_MEM_FEATURES_UNION */
#define SOC_G3D_MEM_FEATURES_ADDR(base)               ((base) + (0x0010))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_MMU_FEATURES_UNION */
#define SOC_G3D_MMU_FEATURES_ADDR(base)               ((base) + (0x0014))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS_PRESENT_UNION */
#define SOC_G3D_AS_PRESENT_ADDR(base)                 ((base) + (0x0018))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS_PRESENT_UNION */
#define SOC_G3D_JS_PRESENT_ADDR(base)                 ((base) + (0x001C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_GPU_IRQ_RAWSTAT_UNION */
#define SOC_G3D_GPU_IRQ_RAWSTAT_ADDR(base)            ((base) + (0x0020))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_GPU_IRQ_CLEAR_UNION */
#define SOC_G3D_GPU_IRQ_CLEAR_ADDR(base)              ((base) + (0x0024))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_GPU_IRQ_MASK_UNION */
#define SOC_G3D_GPU_IRQ_MASK_ADDR(base)               ((base) + (0x0028))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_GPU_IRQ_STATUS_UNION */
#define SOC_G3D_GPU_IRQ_STATUS_ADDR(base)             ((base) + (0x002C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_GPU_COMMAND_UNION */
#define SOC_G3D_GPU_COMMAND_ADDR(base)                ((base) + (0x0030))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_GPU_STATUS_UNION */
#define SOC_G3D_GPU_STATUS_ADDR(base)                 ((base) + (0x0034))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_GPU_FAULTSTATUS_UNION */
#define SOC_G3D_GPU_FAULTSTATUS_ADDR(base)            ((base) + (0x003C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_GPU_FAULTADDRESS_LO_UNION */
#define SOC_G3D_GPU_FAULTADDRESS_LO_ADDR(base)        ((base) + (0x0040))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_GPU_FAULTADDRESS_HI_UNION */
#define SOC_G3D_GPU_FAULTADDRESS_HI_ADDR(base)        ((base) + (0x0044))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_PWR_KEY_UNION */
#define SOC_G3D_PWR_KEY_ADDR(base)                    ((base) + (0x0050))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_PWR_KEYOVERRIDE0_UNION */
#define SOC_G3D_PWR_KEYOVERRIDE0_ADDR(base)           ((base) + (0x0054))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_PWR_KEYOVERRIDE1_UNION */
#define SOC_G3D_PWR_KEYOVERRIDE1_ADDR(base)           ((base) + (0x0058))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_PRFCNT_BASE_LO_UNION */
#define SOC_G3D_PRFCNT_BASE_LO_ADDR(base)             ((base) + (0x0060))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_PRFCNT_BASE_HI_UNION */
#define SOC_G3D_PRFCNT_BASE_HI_ADDR(base)             ((base) + (0x0064))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_PRFCNT_CONFIG_UNION */
#define SOC_G3D_PRFCNT_CONFIG_ADDR(base)              ((base) + (0x0068))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_PRFCNT_JM_EN_UNION */
#define SOC_G3D_PRFCNT_JM_EN_ADDR(base)               ((base) + (0x006C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_PRFCNT_SHADER_EN_UNION */
#define SOC_G3D_PRFCNT_SHADER_EN_ADDR(base)           ((base) + (0x0070))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_PRFCNT_TILER_EN_UNION */
#define SOC_G3D_PRFCNT_TILER_EN_ADDR(base)            ((base) + (0x0074))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_PRFCNT_MMU_L2_EN_UNION */
#define SOC_G3D_PRFCNT_MMU_L2_EN_ADDR(base)           ((base) + (0x007C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_CYCLE_COUNT_LO_UNION */
#define SOC_G3D_CYCLE_COUNT_LO_ADDR(base)             ((base) + (0x0090))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_CYCLE_COUNT_HI_UNION */
#define SOC_G3D_CYCLE_COUNT_HI_ADDR(base)             ((base) + (0x0094))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TIMESTAMP_LO_UNION */
#define SOC_G3D_TIMESTAMP_LO_ADDR(base)               ((base) + (0x0098))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TIMESTAMP_HI_UNION */
#define SOC_G3D_TIMESTAMP_HI_ADDR(base)               ((base) + (0x009C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_THREAD_MAX_THREADS_UNION */
#define SOC_G3D_THREAD_MAX_THREADS_ADDR(base)         ((base) + (0x00A0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_THREAD_MAX_WORKGROUP_UNION */
#define SOC_G3D_THREAD_MAX_WORKGROUP_ADDR(base)       ((base) + (0x00A4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_THREAD_MAX_BARRIER_SIZE_UNION */
#define SOC_G3D_THREAD_MAX_BARRIER_SIZE_ADDR(base)    ((base) + (0x00A8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_THREAD_FEATURES_UNION */
#define SOC_G3D_THREAD_FEATURES_ADDR(base)            ((base) + (0x00AC))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TEXTURE_FEATURES_0_UNION */
#define SOC_G3D_TEXTURE_FEATURES_0_ADDR(base)         ((base) + (0x00B0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TEXTURE_FEATURES_1_UNION */
#define SOC_G3D_TEXTURE_FEATURES_1_ADDR(base)         ((base) + (0x00B4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TEXTURE_FEATURES_2_UNION */
#define SOC_G3D_TEXTURE_FEATURES_2_ADDR(base)         ((base) + (0x00B8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_FEATURES_UNION */
#define SOC_G3D_JS0_FEATURES_ADDR(base)               ((base) + (0x00C0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_FEATURES_UNION */
#define SOC_G3D_JS1_FEATURES_ADDR(base)               ((base) + (0x00C4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_FEATURES_UNION */
#define SOC_G3D_JS2_FEATURES_ADDR(base)               ((base) + (0x00C8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_SHADER_PRESENT_LO_UNION */
#define SOC_G3D_SHADER_PRESENT_LO_ADDR(base)          ((base) + (0x0100))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_SHADER_PRESENT_HI_UNION */
#define SOC_G3D_SHADER_PRESENT_HI_ADDR(base)          ((base) + (0x0104))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TILER_PRESENT_LO_UNION */
#define SOC_G3D_TILER_PRESENT_LO_ADDR(base)           ((base) + (0x0110))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TILER_PRESENT_HI_UNION */
#define SOC_G3D_TILER_PRESENT_HI_ADDR(base)           ((base) + (0x0114))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_L2_PRESENT_LO_UNION */
#define SOC_G3D_L2_PRESENT_LO_ADDR(base)              ((base) + (0x0120))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_L2_PRESENT_HI_UNION */
#define SOC_G3D_L2_PRESENT_HI_ADDR(base)              ((base) + (0x0124))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_SHADER_READY_LO_UNION */
#define SOC_G3D_SHADER_READY_LO_ADDR(base)            ((base) + (0x0140))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_SHADER_READY_HI_UNION */
#define SOC_G3D_SHADER_READY_HI_ADDR(base)            ((base) + (0x0144))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TILER_READY_LO_UNION */
#define SOC_G3D_TILER_READY_LO_ADDR(base)             ((base) + (0x0150))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TILER_READY_HI_UNION */
#define SOC_G3D_TILER_READY_HI_ADDR(base)             ((base) + (0x0154))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_L2_READY_LO_UNION */
#define SOC_G3D_L2_READY_LO_ADDR(base)                ((base) + (0x0160))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_L2_READY_HI_UNION */
#define SOC_G3D_L2_READY_HI_ADDR(base)                ((base) + (0x0164))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_SHADER_PWRON_LO_UNION */
#define SOC_G3D_SHADER_PWRON_LO_ADDR(base)            ((base) + (0x0180))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_SHADER_PWRON_HI_UNION */
#define SOC_G3D_SHADER_PWRON_HI_ADDR(base)            ((base) + (0x0184))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TILER_PWRON_LO_UNION */
#define SOC_G3D_TILER_PWRON_LO_ADDR(base)             ((base) + (0x0190))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TILER_PWRON_HI_UNION */
#define SOC_G3D_TILER_PWRON_HI_ADDR(base)             ((base) + (0x0194))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_L2_PWRON_LO_UNION */
#define SOC_G3D_L2_PWRON_LO_ADDR(base)                ((base) + (0x01A0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_L2_PWRON_HI_UNION */
#define SOC_G3D_L2_PWRON_HI_ADDR(base)                ((base) + (0x01A4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_SHADER_PWROFF_LO_UNION */
#define SOC_G3D_SHADER_PWROFF_LO_ADDR(base)           ((base) + (0x01C0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_SHADER_PWROFF_HI_UNION */
#define SOC_G3D_SHADER_PWROFF_HI_ADDR(base)           ((base) + (0x01C4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TILER_PWROFF_LO_UNION */
#define SOC_G3D_TILER_PWROFF_LO_ADDR(base)            ((base) + (0x01D0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TILER_PWROFF_HI_UNION */
#define SOC_G3D_TILER_PWROFF_HI_ADDR(base)            ((base) + (0x01D4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_L2_PWROFF_LO_UNION */
#define SOC_G3D_L2_PWROFF_LO_ADDR(base)               ((base) + (0x01E0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_L2_PWROFF_HI_UNION */
#define SOC_G3D_L2_PWROFF_HI_ADDR(base)               ((base) + (0x01E4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_SHADER_PWRTRANS_LO_UNION */
#define SOC_G3D_SHADER_PWRTRANS_LO_ADDR(base)         ((base) + (0x0200))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_SHADER_PWRTRANS_HI_UNION */
#define SOC_G3D_SHADER_PWRTRANS_HI_ADDR(base)         ((base) + (0x0204))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TILER_PWRTRANS_LO_UNION */
#define SOC_G3D_TILER_PWRTRANS_LO_ADDR(base)          ((base) + (0x0210))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TILER_PWRTRANS_HI_UNION */
#define SOC_G3D_TILER_PWRTRANS_HI_ADDR(base)          ((base) + (0x0214))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_L2_PWRTRANS_LO_UNION */
#define SOC_G3D_L2_PWRTRANS_LO_ADDR(base)             ((base) + (0x0220))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_L2_PWRTRANS_HI_UNION */
#define SOC_G3D_L2_PWRTRANS_HI_ADDR(base)             ((base) + (0x0224))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_SHADER_PWRACTIVE_LO_UNION */
#define SOC_G3D_SHADER_PWRACTIVE_LO_ADDR(base)        ((base) + (0x0240))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_SHADER_PWRACTIVE_HI_UNION */
#define SOC_G3D_SHADER_PWRACTIVE_HI_ADDR(base)        ((base) + (0x0244))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TILER_PWRACTIVE_LO_UNION */
#define SOC_G3D_TILER_PWRACTIVE_LO_ADDR(base)         ((base) + (0x0250))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TILER_PWRACTIVE_HI_UNION */
#define SOC_G3D_TILER_PWRACTIVE_HI_ADDR(base)         ((base) + (0x0254))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_L2_PWRACTIVE_LO_UNION */
#define SOC_G3D_L2_PWRACTIVE_LO_ADDR(base)            ((base) + (0x0260))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_L2_PWRACTIVE_HI_UNION */
#define SOC_G3D_L2_PWRACTIVE_HI_ADDR(base)            ((base) + (0x0264))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_REV_ID_UNION */
#define SOC_G3D_REV_ID_ADDR(base)                     ((base) + (0x0280))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JM_CONFIG_UNION */
#define SOC_G3D_JM_CONFIG_ADDR(base)                  ((base) + (0x0F00))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_SHADER_CONFIG_UNION */
#define SOC_G3D_SHADER_CONFIG_ADDR(base)              ((base) + (0x0F04))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_TILER_CONFIG_UNION */
#define SOC_G3D_TILER_CONFIG_ADDR(base)               ((base) + (0x0F08))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_L2_MMU_CONFIG_UNION */
#define SOC_G3D_L2_MMU_CONFIG_ADDR(base)              ((base) + (0x0F0C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JOB_IRQ_RAWSTAT_UNION */
#define SOC_G3D_JOB_IRQ_RAWSTAT_ADDR(base)            ((base) + (0x1000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JOB_IRQ_CLEAR_UNION */
#define SOC_G3D_JOB_IRQ_CLEAR_ADDR(base)              ((base) + (0x1004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JOB_IRQ_MASK_UNION */
#define SOC_G3D_JOB_IRQ_MASK_ADDR(base)               ((base) + (0x1008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JOB_IRQ_STATUS_UNION */
#define SOC_G3D_JOB_IRQ_STATUS_ADDR(base)             ((base) + (0x100C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JOB_IRQ_JS_STATE_UNION */
#define SOC_G3D_JOB_IRQ_JS_STATE_ADDR(base)           ((base) + (0x1010))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JOB_IRQ_THROTTLE_UNION */
#define SOC_G3D_JOB_IRQ_THROTTLE_ADDR(base)           ((base) + (0x1014))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_HEAD_LO_UNION */
#define SOC_G3D_JS0_HEAD_LO_ADDR(base)                ((base) + (0x1800))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_HEAD_HI_UNION */
#define SOC_G3D_JS0_HEAD_HI_ADDR(base)                ((base) + (0x1804))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_TAIL_LO_UNION */
#define SOC_G3D_JS0_TAIL_LO_ADDR(base)                ((base) + (0x1808))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_TAIL_HI_UNION */
#define SOC_G3D_JS0_TAIL_HI_ADDR(base)                ((base) + (0x180C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_AFFINITY_LO_UNION */
#define SOC_G3D_JS0_AFFINITY_LO_ADDR(base)            ((base) + (0x1810))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_AFFINITY_HI_UNION */
#define SOC_G3D_JS0_AFFINITY_HI_ADDR(base)            ((base) + (0x1814))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_CONFIG_UNION */
#define SOC_G3D_JS0_CONFIG_ADDR(base)                 ((base) + (0x1818))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_COMMAND_UNION */
#define SOC_G3D_JS0_COMMAND_ADDR(base)                ((base) + (0x1820))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_STATUS_UNION */
#define SOC_G3D_JS0_STATUS_ADDR(base)                 ((base) + (0x1824))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_HEAD_NEXT_LO_UNION */
#define SOC_G3D_JS0_HEAD_NEXT_LO_ADDR(base)           ((base) + (0x1840))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_HEAD_NEXT_HI_UNION */
#define SOC_G3D_JS0_HEAD_NEXT_HI_ADDR(base)           ((base) + (0x1844))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_AFFINITY_NEXT_LO_UNION */
#define SOC_G3D_JS0_AFFINITY_NEXT_LO_ADDR(base)       ((base) + (0x1850))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_AFFINITY_NEXT_HI_UNION */
#define SOC_G3D_JS0_AFFINITY_NEXT_HI_ADDR(base)       ((base) + (0x1854))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_CONFIG_NEXT_UNION */
#define SOC_G3D_JS0_CONFIG_NEXT_ADDR(base)            ((base) + (0x1858))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS0_COMMAND_NEXT_UNION */
#define SOC_G3D_JS0_COMMAND_NEXT_ADDR(base)           ((base) + (0x1860))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_HEAD_LO_UNION */
#define SOC_G3D_JS1_HEAD_LO_ADDR(base)                ((base) + (0x1880))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_HEAD_HI_UNION */
#define SOC_G3D_JS1_HEAD_HI_ADDR(base)                ((base) + (0x1884))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_TAIL_LO_UNION */
#define SOC_G3D_JS1_TAIL_LO_ADDR(base)                ((base) + (0x1888))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_TAIL_HI_UNION */
#define SOC_G3D_JS1_TAIL_HI_ADDR(base)                ((base) + (0x188C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_AFFINITY_LO_UNION */
#define SOC_G3D_JS1_AFFINITY_LO_ADDR(base)            ((base) + (0x1890))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_AFFINITY_HI_UNION */
#define SOC_G3D_JS1_AFFINITY_HI_ADDR(base)            ((base) + (0x1894))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_CONFIG_UNION */
#define SOC_G3D_JS1_CONFIG_ADDR(base)                 ((base) + (0x1898))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_COMMAND_UNION */
#define SOC_G3D_JS1_COMMAND_ADDR(base)                ((base) + (0x18A0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_STATUS_UNION */
#define SOC_G3D_JS1_STATUS_ADDR(base)                 ((base) + (0x18A4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_HEAD_NEXT_LO_UNION */
#define SOC_G3D_JS1_HEAD_NEXT_LO_ADDR(base)           ((base) + (0x18C0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_HEAD_NEXT_HI_UNION */
#define SOC_G3D_JS1_HEAD_NEXT_HI_ADDR(base)           ((base) + (0x18C4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_AFFINITY_NEXT_LO_UNION */
#define SOC_G3D_JS1_AFFINITY_NEXT_LO_ADDR(base)       ((base) + (0x18D0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_AFFINITY_NEXT_HI_UNION */
#define SOC_G3D_JS1_AFFINITY_NEXT_HI_ADDR(base)       ((base) + (0x18D4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_CONFIG_NEXT_UNION */
#define SOC_G3D_JS1_CONFIG_NEXT_ADDR(base)            ((base) + (0x18D8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS1_COMMAND_NEXT_UNION */
#define SOC_G3D_JS1_COMMAND_NEXT_ADDR(base)           ((base) + (0x18E0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_HEAD_LO_UNION */
#define SOC_G3D_JS2_HEAD_LO_ADDR(base)                ((base) + (0x1900))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_HEAD_HI_UNION */
#define SOC_G3D_JS2_HEAD_HI_ADDR(base)                ((base) + (0x1904))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_TAIL_LO_UNION */
#define SOC_G3D_JS2_TAIL_LO_ADDR(base)                ((base) + (0x1908))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_TAIL_HI_UNION */
#define SOC_G3D_JS2_TAIL_HI_ADDR(base)                ((base) + (0x190C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_AFFINITY_LO_UNION */
#define SOC_G3D_JS2_AFFINITY_LO_ADDR(base)            ((base) + (0x1910))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_AFFINITY_HI_UNION */
#define SOC_G3D_JS2_AFFINITY_HI_ADDR(base)            ((base) + (0x1914))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_CONFIG_UNION */
#define SOC_G3D_JS2_CONFIG_ADDR(base)                 ((base) + (0x1918))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_COMMAND_UNION */
#define SOC_G3D_JS2_COMMAND_ADDR(base)                ((base) + (0x1920))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_STATUS_UNION */
#define SOC_G3D_JS2_STATUS_ADDR(base)                 ((base) + (0x1924))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_HEAD_NEXT_LO_UNION */
#define SOC_G3D_JS2_HEAD_NEXT_LO_ADDR(base)           ((base) + (0x1940))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_HEAD_NEXT_HI_UNION */
#define SOC_G3D_JS2_HEAD_NEXT_HI_ADDR(base)           ((base) + (0x1944))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_AFFINITY_NEXT_LO_UNION */
#define SOC_G3D_JS2_AFFINITY_NEXT_LO_ADDR(base)       ((base) + (0x1950))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_AFFINITY_NEXT_HI_UNION */
#define SOC_G3D_JS2_AFFINITY_NEXT_HI_ADDR(base)       ((base) + (0x1954))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_CONFIG_NEXT_UNION */
#define SOC_G3D_JS2_CONFIG_NEXT_ADDR(base)            ((base) + (0x1958))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_JS2_COMMAND_NEXT_UNION */
#define SOC_G3D_JS2_COMMAND_NEXT_ADDR(base)           ((base) + (0x1960))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_MMU_IRQ_RAWSTAT_UNION */
#define SOC_G3D_MMU_IRQ_RAWSTAT_ADDR(base)            ((base) + (0x2000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_MMU_IRQ_CLEAR_UNION */
#define SOC_G3D_MMU_IRQ_CLEAR_ADDR(base)              ((base) + (0x2004))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_MMU_IRQ_MASK_UNION */
#define SOC_G3D_MMU_IRQ_MASK_ADDR(base)               ((base) + (0x2008))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_MMU_IRQ_STATUS_UNION */
#define SOC_G3D_MMU_IRQ_STATUS_ADDR(base)             ((base) + (0x200C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS0_TRANSTAB_LO_UNION */
#define SOC_G3D_AS0_TRANSTAB_LO_ADDR(base)            ((base) + (0x2400))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS0_TRANSTAB_HI_UNION */
#define SOC_G3D_AS0_TRANSTAB_HI_ADDR(base)            ((base) + (0x2404))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS0_MEMATTR_LO_UNION */
#define SOC_G3D_AS0_MEMATTR_LO_ADDR(base)             ((base) + (0x2408))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS0_MEMATTR_HI_UNION */
#define SOC_G3D_AS0_MEMATTR_HI_ADDR(base)             ((base) + (0x240C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS0_LOCKADDR_LO_UNION */
#define SOC_G3D_AS0_LOCKADDR_LO_ADDR(base)            ((base) + (0x2410))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS0_LOCKADDR_HI_UNION */
#define SOC_G3D_AS0_LOCKADDR_HI_ADDR(base)            ((base) + (0x2414))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS0_COMMAND_UNION */
#define SOC_G3D_AS0_COMMAND_ADDR(base)                ((base) + (0x2418))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS0_FAULTSTATUS_UNION */
#define SOC_G3D_AS0_FAULTSTATUS_ADDR(base)            ((base) + (0x241C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS0_FAULTADDRESS_LO_UNION */
#define SOC_G3D_AS0_FAULTADDRESS_LO_ADDR(base)        ((base) + (0x2420))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS0_FAULTADDRESS_HI_UNION */
#define SOC_G3D_AS0_FAULTADDRESS_HI_ADDR(base)        ((base) + (0x2424))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS0_STATUS_UNION */
#define SOC_G3D_AS0_STATUS_ADDR(base)                 ((base) + (0x2428))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS1_TRANSTAB_LO_UNION */
#define SOC_G3D_AS1_TRANSTAB_LO_ADDR(base)            ((base) + (0x2440))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS1_TRANSTAB_HI_UNION */
#define SOC_G3D_AS1_TRANSTAB_HI_ADDR(base)            ((base) + (0x2444))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS1_MEMATTR_LO_UNION */
#define SOC_G3D_AS1_MEMATTR_LO_ADDR(base)             ((base) + (0x2448))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS1_MEMATTR_HI_UNION */
#define SOC_G3D_AS1_MEMATTR_HI_ADDR(base)             ((base) + (0x244C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS1_LOCKADDR_LO_UNION */
#define SOC_G3D_AS1_LOCKADDR_LO_ADDR(base)            ((base) + (0x2450))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS1_LOCKADDR_HI_UNION */
#define SOC_G3D_AS1_LOCKADDR_HI_ADDR(base)            ((base) + (0x2454))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS1_COMMAND_UNION */
#define SOC_G3D_AS1_COMMAND_ADDR(base)                ((base) + (0x2458))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS1_FAULTSTATUS_UNION */
#define SOC_G3D_AS1_FAULTSTATUS_ADDR(base)            ((base) + (0x245C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS1_FAULTADDRESS_LO_UNION */
#define SOC_G3D_AS1_FAULTADDRESS_LO_ADDR(base)        ((base) + (0x2460))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS1_FAULTADDRESS_HI_UNION */
#define SOC_G3D_AS1_FAULTADDRESS_HI_ADDR(base)        ((base) + (0x2464))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS1_STATUS_UNION */
#define SOC_G3D_AS1_STATUS_ADDR(base)                 ((base) + (0x2468))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS2_TRANSTAB_LO_UNION */
#define SOC_G3D_AS2_TRANSTAB_LO_ADDR(base)            ((base) + (0x2480))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS2_TRANSTAB_HI_UNION */
#define SOC_G3D_AS2_TRANSTAB_HI_ADDR(base)            ((base) + (0x2484))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS2_MEMATTR_LO_UNION */
#define SOC_G3D_AS2_MEMATTR_LO_ADDR(base)             ((base) + (0x2488))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS2_MEMATTR_HI_UNION */
#define SOC_G3D_AS2_MEMATTR_HI_ADDR(base)             ((base) + (0x248C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS2_LOCKADDR_LO_UNION */
#define SOC_G3D_AS2_LOCKADDR_LO_ADDR(base)            ((base) + (0x2490))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS2_LOCKADDR_HI_UNION */
#define SOC_G3D_AS2_LOCKADDR_HI_ADDR(base)            ((base) + (0x2494))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS2_COMMAND_UNION */
#define SOC_G3D_AS2_COMMAND_ADDR(base)                ((base) + (0x2498))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS2_FAULTSTATUS_UNION */
#define SOC_G3D_AS2_FAULTSTATUS_ADDR(base)            ((base) + (0x249C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS2_FAULTADDRESS_LO_UNION */
#define SOC_G3D_AS2_FAULTADDRESS_LO_ADDR(base)        ((base) + (0x24A0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS2_FAULTADDRESS_HI_UNION */
#define SOC_G3D_AS2_FAULTADDRESS_HI_ADDR(base)        ((base) + (0x24A4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS2_STATUS_UNION */
#define SOC_G3D_AS2_STATUS_ADDR(base)                 ((base) + (0x24A8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS3_TRANSTAB_LO_UNION */
#define SOC_G3D_AS3_TRANSTAB_LO_ADDR(base)            ((base) + (0x24C0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS3_TRANSTAB_HI_UNION */
#define SOC_G3D_AS3_TRANSTAB_HI_ADDR(base)            ((base) + (0x24C4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS3_MEMATTR_LO_UNION */
#define SOC_G3D_AS3_MEMATTR_LO_ADDR(base)             ((base) + (0x24C8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS3_MEMATTR_HI_UNION */
#define SOC_G3D_AS3_MEMATTR_HI_ADDR(base)             ((base) + (0x24CC))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS3_LOCKADDR_LO_UNION */
#define SOC_G3D_AS3_LOCKADDR_LO_ADDR(base)            ((base) + (0x24D0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS3_LOCKADDR_HI_UNION */
#define SOC_G3D_AS3_LOCKADDR_HI_ADDR(base)            ((base) + (0x24D4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS3_COMMAND_UNION */
#define SOC_G3D_AS3_COMMAND_ADDR(base)                ((base) + (0x24D8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS3_FAULTSTATUS_UNION */
#define SOC_G3D_AS3_FAULTSTATUS_ADDR(base)            ((base) + (0x24DC))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS3_FAULTADDRESS_LO_UNION */
#define SOC_G3D_AS3_FAULTADDRESS_LO_ADDR(base)        ((base) + (0x24E0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS3_FAULTADDRESS_HI_UNION */
#define SOC_G3D_AS3_FAULTADDRESS_HI_ADDR(base)        ((base) + (0x24E4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_G3D_AS3_STATUS_UNION */
#define SOC_G3D_AS3_STATUS_ADDR(base)                 ((base) + (0x24E8))





/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/



/*****************************************************************************
  6 STRUCT����
*****************************************************************************/



/*****************************************************************************
  7 UNION����
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_G3D_GPU_ID_UNION
 �ṹ˵��  : GPU_ID �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x08800020�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  version_status : 4;  /* bit[0-3]  : release �汾�����кţ���0��ʼ���� */
        unsigned int  version_minor  : 8;  /* bit[4-11] : RxPx P�汾. */
        unsigned int  version_major  : 4;  /* bit[12-15]: RxPx R�汾 */
        unsigned int  product_id     : 16; /* bit[16-31]: The product ID. All other values are reserved. */
    } reg;
} SOC_G3D_GPU_ID_UNION;
#endif
#define SOC_G3D_GPU_ID_version_status_START  (0)
#define SOC_G3D_GPU_ID_version_status_END    (3)
#define SOC_G3D_GPU_ID_version_minor_START   (4)
#define SOC_G3D_GPU_ID_version_minor_END     (11)
#define SOC_G3D_GPU_ID_version_major_START   (12)
#define SOC_G3D_GPU_ID_version_major_END     (15)
#define SOC_G3D_GPU_ID_product_id_START      (16)
#define SOC_G3D_GPU_ID_product_id_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_L2_FEATURES_UNION
 �ṹ˵��  : L2_FEATURES �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x07130206�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  line_size          : 8;  /* bit[0-7]  : cache line:
                                                              64B */
        unsigned int  associativity      : 8;  /* bit[8-15] : assiciativity:
                                                              Level 2 cache associativity:
                                                              0x02 4 ways */
        unsigned int  cache_size         : 8;  /* bit[16-23]: l2 cache ��С
                                                              0x12:256KB
                                                              0x13:512KB */
        unsigned int  external_bus_width : 8;  /* bit[24-31]: AXI����λ��
                                                              0x06:64bit
                                                              0x07;128bit */
    } reg;
} SOC_G3D_L2_FEATURES_UNION;
#endif
#define SOC_G3D_L2_FEATURES_line_size_START           (0)
#define SOC_G3D_L2_FEATURES_line_size_END             (7)
#define SOC_G3D_L2_FEATURES_associativity_START       (8)
#define SOC_G3D_L2_FEATURES_associativity_END         (15)
#define SOC_G3D_L2_FEATURES_cache_size_START          (16)
#define SOC_G3D_L2_FEATURES_cache_size_END            (23)
#define SOC_G3D_L2_FEATURES_external_bus_width_START  (24)
#define SOC_G3D_L2_FEATURES_external_bus_width_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TILER_FEATURES_UNION
 �ṹ˵��  : TILER_FEATURES �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000809�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bin_size          : 6;  /* bit[0-5]  : bin_size:
                                                             0x09 - Log2 of the bin size, in bytes */
        unsigned int  reserved_0        : 2;  /* bit[6-7]  : reserved */
        unsigned int  max_active_levels : 4;  /* bit[8-11] : 0x08 - Maximum number of active hierarchy levels */
        unsigned int  reserved_1        : 20; /* bit[12-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_TILER_FEATURES_UNION;
#endif
#define SOC_G3D_TILER_FEATURES_bin_size_START           (0)
#define SOC_G3D_TILER_FEATURES_bin_size_END             (5)
#define SOC_G3D_TILER_FEATURES_max_active_levels_START  (8)
#define SOC_G3D_TILER_FEATURES_max_active_levels_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_G3D_MEM_FEATURES_UNION
 �ṹ˵��  : MEM_FEATURES �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  COHERENT_CORE_GROUP : 1;  /* bit[0]    : ͬһ��core_group�µ�core����memory
                                                               0����
                                                               1���� */
        unsigned int  COHERENT_SUPERGROUP : 1;  /* bit[1]    : set if the cores ina supergroup haver coherent memory with the other cores in that group */
        unsigned int  reserved_0          : 6;  /* bit[2-7]  : RSV */
        unsigned int  l2_slices           : 4;  /* bit[8-11] : L2 cache������
                                                               0:1��
                                                               1:2�� */
        unsigned int  reserved_1          : 20; /* bit[12-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_MEM_FEATURES_UNION;
#endif
#define SOC_G3D_MEM_FEATURES_COHERENT_CORE_GROUP_START  (0)
#define SOC_G3D_MEM_FEATURES_COHERENT_CORE_GROUP_END    (0)
#define SOC_G3D_MEM_FEATURES_COHERENT_SUPERGROUP_START  (1)
#define SOC_G3D_MEM_FEATURES_COHERENT_SUPERGROUP_END    (1)
#define SOC_G3D_MEM_FEATURES_l2_slices_START            (8)
#define SOC_G3D_MEM_FEATURES_l2_slices_END              (11)


/*****************************************************************************
 �ṹ��    : SOC_G3D_MMU_FEATURES_UNION
 �ṹ˵��  : MMU_FEATURES �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00002830�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  va_bits      : 8;  /* bit[0-7]  : �����ַλ��48bit */
        unsigned int  pa_bits      : 8;  /* bit[8-15] : ��ʵ��ַλ��40bit */
        unsigned int  mmu_features : 16; /* bit[16-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_MMU_FEATURES_UNION;
#endif
#define SOC_G3D_MMU_FEATURES_va_bits_START       (0)
#define SOC_G3D_MMU_FEATURES_va_bits_END         (7)
#define SOC_G3D_MMU_FEATURES_pa_bits_START       (8)
#define SOC_G3D_MMU_FEATURES_pa_bits_END         (15)
#define SOC_G3D_MMU_FEATURES_mmu_features_START  (16)
#define SOC_G3D_MMU_FEATURES_mmu_features_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS_PRESENT_UNION
 �ṹ˵��  : AS_PRESENT �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x000000FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as_present_low : 8;  /* bit[0-7] : ��ַ�ռ�AS0~AS7Sʹ�ܡ� */
        unsigned int  as_present     : 24; /* bit[8-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_AS_PRESENT_UNION;
#endif
#define SOC_G3D_AS_PRESENT_as_present_low_START  (0)
#define SOC_G3D_AS_PRESENT_as_present_low_END    (7)
#define SOC_G3D_AS_PRESENT_as_present_START      (8)
#define SOC_G3D_AS_PRESENT_as_present_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS_PRESENT_UNION
 �ṹ˵��  : JS_PRESENT �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000007�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js_present_low : 4;  /* bit[0-3] : JS0~JS2ʹ�ܡ� */
        unsigned int  js_present     : 28; /* bit[4-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_JS_PRESENT_UNION;
#endif
#define SOC_G3D_JS_PRESENT_js_present_low_START  (0)
#define SOC_G3D_JS_PRESENT_js_present_low_END    (3)
#define SOC_G3D_JS_PRESENT_js_present_START      (4)
#define SOC_G3D_JS_PRESENT_js_present_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_GPU_IRQ_RAWSTAT_UNION
 �ṹ˵��  : GPU_IRQ_RAWSTAT �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000100�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpu_fault              : 1;  /* bit[0-0]  : GPUʧЧ�жϡ���GPU_FAULTADDRESS�Ĵ�������ʧЧ���� */
        unsigned int  reserved_0             : 6;  /* bit[1-6]  : RSV */
        unsigned int  multi_gpu_fault        : 1;  /* bit[7]    : RSV */
        unsigned int  reset_completed        : 1;  /* bit[8]    : ��λ��� */
        unsigned int  power_change_single    : 1;  /* bit[9]    : ����һ��core������µ磬��1 */
        unsigned int  power_change_all       : 1;  /* bit[10]   : ����core������µ磬��1 */
        unsigned int  reserved_1             : 5;  /* bit[11-15]: RSV */
        unsigned int  prfcnt_sample_complete : 1;  /* bit[16]   : ���һ��performance cout sample����1 */
        unsigned int  clean_cache_completed  : 1;  /* bit[17]   : ���clear cache��������1 */
        unsigned int  reserved_2             : 14; /* bit[18-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_GPU_IRQ_RAWSTAT_UNION;
#endif
#define SOC_G3D_GPU_IRQ_RAWSTAT_gpu_fault_START               (0)
#define SOC_G3D_GPU_IRQ_RAWSTAT_gpu_fault_END                 (0)
#define SOC_G3D_GPU_IRQ_RAWSTAT_multi_gpu_fault_START         (7)
#define SOC_G3D_GPU_IRQ_RAWSTAT_multi_gpu_fault_END           (7)
#define SOC_G3D_GPU_IRQ_RAWSTAT_reset_completed_START         (8)
#define SOC_G3D_GPU_IRQ_RAWSTAT_reset_completed_END           (8)
#define SOC_G3D_GPU_IRQ_RAWSTAT_power_change_single_START     (9)
#define SOC_G3D_GPU_IRQ_RAWSTAT_power_change_single_END       (9)
#define SOC_G3D_GPU_IRQ_RAWSTAT_power_change_all_START        (10)
#define SOC_G3D_GPU_IRQ_RAWSTAT_power_change_all_END          (10)
#define SOC_G3D_GPU_IRQ_RAWSTAT_prfcnt_sample_complete_START  (16)
#define SOC_G3D_GPU_IRQ_RAWSTAT_prfcnt_sample_complete_END    (16)
#define SOC_G3D_GPU_IRQ_RAWSTAT_clean_cache_completed_START   (17)
#define SOC_G3D_GPU_IRQ_RAWSTAT_clean_cache_completed_END     (17)


/*****************************************************************************
 �ṹ��    : SOC_G3D_GPU_IRQ_CLEAR_UNION
 �ṹ˵��  : GPU_IRQ_CLEAR �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpu_fault              : 1;  /* bit[0-0]  : ��Ӧ�ж���� */
        unsigned int  reserved_0             : 6;  /* bit[1-6]  : ��Ӧ�ж���� */
        unsigned int  multi_gpu_fault        : 1;  /* bit[7]    : ��Ӧ�ж���� */
        unsigned int  reset_completed        : 1;  /* bit[8]    : ��Ӧ�ж���� */
        unsigned int  power_change_single    : 1;  /* bit[9]    : ��Ӧ�ж���� */
        unsigned int  power_change_all       : 1;  /* bit[10]   : ��Ӧ�ж���� */
        unsigned int  reserved_1             : 5;  /* bit[11-15]: ��Ӧ�ж���� */
        unsigned int  prfcnt_sample_complete : 1;  /* bit[16]   : ��Ӧ�ж���� */
        unsigned int  clean_cache_completed  : 1;  /* bit[17]   : ��Ӧ�ж������д1��� */
        unsigned int  reserved_2             : 14; /* bit[18-31]: Job management clear Interrupts register */
    } reg;
} SOC_G3D_GPU_IRQ_CLEAR_UNION;
#endif
#define SOC_G3D_GPU_IRQ_CLEAR_gpu_fault_START               (0)
#define SOC_G3D_GPU_IRQ_CLEAR_gpu_fault_END                 (0)
#define SOC_G3D_GPU_IRQ_CLEAR_multi_gpu_fault_START         (7)
#define SOC_G3D_GPU_IRQ_CLEAR_multi_gpu_fault_END           (7)
#define SOC_G3D_GPU_IRQ_CLEAR_reset_completed_START         (8)
#define SOC_G3D_GPU_IRQ_CLEAR_reset_completed_END           (8)
#define SOC_G3D_GPU_IRQ_CLEAR_power_change_single_START     (9)
#define SOC_G3D_GPU_IRQ_CLEAR_power_change_single_END       (9)
#define SOC_G3D_GPU_IRQ_CLEAR_power_change_all_START        (10)
#define SOC_G3D_GPU_IRQ_CLEAR_power_change_all_END          (10)
#define SOC_G3D_GPU_IRQ_CLEAR_prfcnt_sample_complete_START  (16)
#define SOC_G3D_GPU_IRQ_CLEAR_prfcnt_sample_complete_END    (16)
#define SOC_G3D_GPU_IRQ_CLEAR_clean_cache_completed_START   (17)
#define SOC_G3D_GPU_IRQ_CLEAR_clean_cache_completed_END     (17)


/*****************************************************************************
 �ṹ��    : SOC_G3D_GPU_IRQ_MASK_UNION
 �ṹ˵��  : GPU_IRQ_MASK �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpu_fault              : 1;  /* bit[0-0]  : ��Ӧ�ж����� */
        unsigned int  reserved_0             : 6;  /* bit[1-6]  : ��Ӧ�ж����� */
        unsigned int  multi_gpu_fault        : 1;  /* bit[7]    : ��Ӧ�ж����� */
        unsigned int  reset_completed        : 1;  /* bit[8]    : ��Ӧ�ж����� */
        unsigned int  power_change_single    : 1;  /* bit[9]    : ��Ӧ�ж����� */
        unsigned int  power_change_all       : 1;  /* bit[10]   : ��Ӧ�ж����� */
        unsigned int  reserved_1             : 5;  /* bit[11-15]: ��Ӧ�ж����� */
        unsigned int  prfcnt_sample_complete : 1;  /* bit[16]   : ��Ӧ�ж����� */
        unsigned int  clean_cache_completed  : 1;  /* bit[17]   : ��Ӧ�ж����룬д1�����Ӧ�ж� */
        unsigned int  reserved_2             : 14; /* bit[18-31]: Job management enable Interrupts register */
    } reg;
} SOC_G3D_GPU_IRQ_MASK_UNION;
#endif
#define SOC_G3D_GPU_IRQ_MASK_gpu_fault_START               (0)
#define SOC_G3D_GPU_IRQ_MASK_gpu_fault_END                 (0)
#define SOC_G3D_GPU_IRQ_MASK_multi_gpu_fault_START         (7)
#define SOC_G3D_GPU_IRQ_MASK_multi_gpu_fault_END           (7)
#define SOC_G3D_GPU_IRQ_MASK_reset_completed_START         (8)
#define SOC_G3D_GPU_IRQ_MASK_reset_completed_END           (8)
#define SOC_G3D_GPU_IRQ_MASK_power_change_single_START     (9)
#define SOC_G3D_GPU_IRQ_MASK_power_change_single_END       (9)
#define SOC_G3D_GPU_IRQ_MASK_power_change_all_START        (10)
#define SOC_G3D_GPU_IRQ_MASK_power_change_all_END          (10)
#define SOC_G3D_GPU_IRQ_MASK_prfcnt_sample_complete_START  (16)
#define SOC_G3D_GPU_IRQ_MASK_prfcnt_sample_complete_END    (16)
#define SOC_G3D_GPU_IRQ_MASK_clean_cache_completed_START   (17)
#define SOC_G3D_GPU_IRQ_MASK_clean_cache_completed_END     (17)


/*****************************************************************************
 �ṹ��    : SOC_G3D_GPU_IRQ_STATUS_UNION
 �ṹ˵��  : GPU_IRQ_STATUS �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpu_fault              : 1;  /* bit[0-0]  : ��Ӧ�жϺ��������߼����ֵ */
        unsigned int  reserved_0             : 6;  /* bit[1-6]  : ��Ӧ�жϺ��������߼����ֵ */
        unsigned int  multi_gpu_fault        : 1;  /* bit[7]    : ��Ӧ�жϺ��������߼����ֵ */
        unsigned int  reset_completed        : 1;  /* bit[8]    : ��Ӧ�жϺ��������߼����ֵ */
        unsigned int  power_change_single    : 1;  /* bit[9]    : ��Ӧ�жϺ��������߼����ֵ */
        unsigned int  power_change_all       : 1;  /* bit[10]   : ��Ӧ�жϺ��������߼����ֵ */
        unsigned int  reserved_1             : 5;  /* bit[11-15]: ��Ӧ�жϺ��������߼����ֵ */
        unsigned int  prfcnt_sample_complete : 1;  /* bit[16]   : ��Ӧ�жϺ��������߼����ֵ */
        unsigned int  clean_cache_completed  : 1;  /* bit[17]   : ��Ӧ�жϺ��������߼����ֵ */
        unsigned int  reserved_2             : 14; /* bit[18-31]: Job management interrupt status register */
    } reg;
} SOC_G3D_GPU_IRQ_STATUS_UNION;
#endif
#define SOC_G3D_GPU_IRQ_STATUS_gpu_fault_START               (0)
#define SOC_G3D_GPU_IRQ_STATUS_gpu_fault_END                 (0)
#define SOC_G3D_GPU_IRQ_STATUS_multi_gpu_fault_START         (7)
#define SOC_G3D_GPU_IRQ_STATUS_multi_gpu_fault_END           (7)
#define SOC_G3D_GPU_IRQ_STATUS_reset_completed_START         (8)
#define SOC_G3D_GPU_IRQ_STATUS_reset_completed_END           (8)
#define SOC_G3D_GPU_IRQ_STATUS_power_change_single_START     (9)
#define SOC_G3D_GPU_IRQ_STATUS_power_change_single_END       (9)
#define SOC_G3D_GPU_IRQ_STATUS_power_change_all_START        (10)
#define SOC_G3D_GPU_IRQ_STATUS_power_change_all_END          (10)
#define SOC_G3D_GPU_IRQ_STATUS_prfcnt_sample_complete_START  (16)
#define SOC_G3D_GPU_IRQ_STATUS_prfcnt_sample_complete_END    (16)
#define SOC_G3D_GPU_IRQ_STATUS_clean_cache_completed_START   (17)
#define SOC_G3D_GPU_IRQ_STATUS_clean_cache_completed_END     (17)


/*****************************************************************************
 �ṹ��    : SOC_G3D_GPU_COMMAND_UNION
 �ṹ˵��  : GPU_COMMAND �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved          : 1;  /* bit[0]   : Reserved, write as zero, read undefined. */
        unsigned int  soft_reset        : 1;  /* bit[1]   : ��λ */
        unsigned int  hard_reset        : 1;  /* bit[2]   : Ӳ��λ */
        unsigned int  prfcnt_clear      : 1;  /* bit[3]   : pfrcnt��0 */
        unsigned int  prfcnt_sample     : 1;  /* bit[4]   : ����pfrcntд��memory������� */
        unsigned int  cycle_count_start : 1;  /* bit[5]   : pfrcnt��ʼ���� */
        unsigned int  cycle_count_stop  : 1;  /* bit[6]   : pfrcntֹͣ���� */
        unsigned int  clean_caches      : 1;  /* bit[7]   : ��cache */
        unsigned int  clean_inv_caches  : 1;  /* bit[8]   : Cleans and invalidates all caches */
        unsigned int  gpu_command       : 23; /* bit[9-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_GPU_COMMAND_UNION;
#endif
#define SOC_G3D_GPU_COMMAND_soft_reset_START         (1)
#define SOC_G3D_GPU_COMMAND_soft_reset_END           (1)
#define SOC_G3D_GPU_COMMAND_hard_reset_START         (2)
#define SOC_G3D_GPU_COMMAND_hard_reset_END           (2)
#define SOC_G3D_GPU_COMMAND_prfcnt_clear_START       (3)
#define SOC_G3D_GPU_COMMAND_prfcnt_clear_END         (3)
#define SOC_G3D_GPU_COMMAND_prfcnt_sample_START      (4)
#define SOC_G3D_GPU_COMMAND_prfcnt_sample_END        (4)
#define SOC_G3D_GPU_COMMAND_cycle_count_start_START  (5)
#define SOC_G3D_GPU_COMMAND_cycle_count_start_END    (5)
#define SOC_G3D_GPU_COMMAND_cycle_count_stop_START   (6)
#define SOC_G3D_GPU_COMMAND_cycle_count_stop_END     (6)
#define SOC_G3D_GPU_COMMAND_clean_caches_START       (7)
#define SOC_G3D_GPU_COMMAND_clean_caches_END         (7)
#define SOC_G3D_GPU_COMMAND_clean_inv_caches_START   (8)
#define SOC_G3D_GPU_COMMAND_clean_inv_caches_END     (8)
#define SOC_G3D_GPU_COMMAND_gpu_command_START        (9)
#define SOC_G3D_GPU_COMMAND_gpu_command_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_GPU_STATUS_UNION
 �ṹ˵��  : GPU_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpu_active         : 1;  /* bit[0]   : The GPU, or part of the GPU, is active */
        unsigned int  pwr_active         : 1;  /* bit[1]   : The power controller is active, changing an area of the
                                                             power state of the GPU. */
        unsigned int  prfcnt_active      : 1;  /* bit[2]   : The performance counters are active, writing counter
                                                             values to memory */
        unsigned int  job_active         : 1;  /* bit[3]   : The job slots are active */
        unsigned int  page_fault         : 1;  /* bit[4]   : The page faults are active */
        unsigned int  irq_active         : 1;  /* bit[5]   : The interrupt signals are active */
        unsigned int  cycle_count_active : 1;  /* bit[6]   : The cycle counter is active */
        unsigned int  gpu_status         : 25; /* bit[7-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_GPU_STATUS_UNION;
#endif
#define SOC_G3D_GPU_STATUS_gpu_active_START          (0)
#define SOC_G3D_GPU_STATUS_gpu_active_END            (0)
#define SOC_G3D_GPU_STATUS_pwr_active_START          (1)
#define SOC_G3D_GPU_STATUS_pwr_active_END            (1)
#define SOC_G3D_GPU_STATUS_prfcnt_active_START       (2)
#define SOC_G3D_GPU_STATUS_prfcnt_active_END         (2)
#define SOC_G3D_GPU_STATUS_job_active_START          (3)
#define SOC_G3D_GPU_STATUS_job_active_END            (3)
#define SOC_G3D_GPU_STATUS_page_fault_START          (4)
#define SOC_G3D_GPU_STATUS_page_fault_END            (4)
#define SOC_G3D_GPU_STATUS_irq_active_START          (5)
#define SOC_G3D_GPU_STATUS_irq_active_END            (5)
#define SOC_G3D_GPU_STATUS_cycle_count_active_START  (6)
#define SOC_G3D_GPU_STATUS_cycle_count_active_END    (6)
#define SOC_G3D_GPU_STATUS_gpu_status_START          (7)
#define SOC_G3D_GPU_STATUS_gpu_status_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_GPU_FAULTSTATUS_UNION
 �ṹ˵��  : GPU_FAULTSTATUS �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exception_type  : 8;  /* bit[0-7]  : �����ж����� */
        unsigned int  access_type     : 2;  /* bit[8-9]  : Access type that triggered the fault */
        unsigned int  gpu_faultstatus : 22; /* bit[10-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_GPU_FAULTSTATUS_UNION;
#endif
#define SOC_G3D_GPU_FAULTSTATUS_exception_type_START   (0)
#define SOC_G3D_GPU_FAULTSTATUS_exception_type_END     (7)
#define SOC_G3D_GPU_FAULTSTATUS_access_type_START      (8)
#define SOC_G3D_GPU_FAULTSTATUS_access_type_END        (9)
#define SOC_G3D_GPU_FAULTSTATUS_gpu_faultstatus_START  (10)
#define SOC_G3D_GPU_FAULTSTATUS_gpu_faultstatus_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_GPU_FAULTADDRESS_LO_UNION
 �ṹ˵��  : GPU_FAULTADDRESS_LO �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpu_faultaddress_lo : 32; /* bit[0-31]: GPU exception fault address register  */
    } reg;
} SOC_G3D_GPU_FAULTADDRESS_LO_UNION;
#endif
#define SOC_G3D_GPU_FAULTADDRESS_LO_gpu_faultaddress_lo_START  (0)
#define SOC_G3D_GPU_FAULTADDRESS_LO_gpu_faultaddress_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_GPU_FAULTADDRESS_HI_UNION
 �ṹ˵��  : GPU_FAULTADDRESS_HI �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gpu_faultaddress_hi : 32; /* bit[0-31]: GPU exception fault address register */
    } reg;
} SOC_G3D_GPU_FAULTADDRESS_HI_UNION;
#endif
#define SOC_G3D_GPU_FAULTADDRESS_HI_gpu_faultaddress_hi_START  (0)
#define SOC_G3D_GPU_FAULTADDRESS_HI_gpu_faultaddress_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_PWR_KEY_UNION
 �ṹ˵��  : PWR_KEY �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwr_key : 32; /* bit[0-31]: д0x54,0x58�Ĵ���֮ǰ�������øüĴ����� The key value is
                                                  0x2968A819. */
    } reg;
} SOC_G3D_PWR_KEY_UNION;
#endif
#define SOC_G3D_PWR_KEY_pwr_key_START  (0)
#define SOC_G3D_PWR_KEY_pwr_key_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_PWR_KEYOVERRIDE0_UNION
 �ṹ˵��  : PWR_KEYOVERRIDE0 �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pwrup_override       : 2;  /* bit[0-1]  : Specifies overrides of the power domain PWRUP signal */
        unsigned int  isolate_override     : 2;  /* bit[2-3]  : Specifies overrides of the power domain ISOLATE signal */
        unsigned int  reset_override       : 2;  /* bit[4-5]  : Specifies overrides of the power domain RESET signal */
        unsigned int  clken_override       : 2;  /* bit[6-7]  : Specifies overrides of the power domain CLKEN signal */
        unsigned int  ack_override         : 2;  /* bit[8-9]  : Specifies overrides of the power domain PWRUP_ACK
                                                                signal */
        unsigned int  isolate_ack_override : 2;  /* bit[10-11]: Specifies overrides of the power domain ISOLATE_ACK
                                                                signal */
        unsigned int  reserved_0           : 4;  /* bit[12-15]: Reserved, write as zero, read undefined */
        unsigned int  powertrain_limt      : 6;  /* bit[16-21]: Maximum number of active power transactions at any time,
                                                                minus one.
                                                                The POWERTRANS_LIMIT field default of 0 enables a
                                                                single power domain to transition at a time. Setting this to a
                                                                higher value can speed up power transition, but also requires
                                                                that the device can handle the larger power requirements. */
        unsigned int  reserved_1           : 10; /* bit[22-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_PWR_KEYOVERRIDE0_UNION;
#endif
#define SOC_G3D_PWR_KEYOVERRIDE0_pwrup_override_START        (0)
#define SOC_G3D_PWR_KEYOVERRIDE0_pwrup_override_END          (1)
#define SOC_G3D_PWR_KEYOVERRIDE0_isolate_override_START      (2)
#define SOC_G3D_PWR_KEYOVERRIDE0_isolate_override_END        (3)
#define SOC_G3D_PWR_KEYOVERRIDE0_reset_override_START        (4)
#define SOC_G3D_PWR_KEYOVERRIDE0_reset_override_END          (5)
#define SOC_G3D_PWR_KEYOVERRIDE0_clken_override_START        (6)
#define SOC_G3D_PWR_KEYOVERRIDE0_clken_override_END          (7)
#define SOC_G3D_PWR_KEYOVERRIDE0_ack_override_START          (8)
#define SOC_G3D_PWR_KEYOVERRIDE0_ack_override_END            (9)
#define SOC_G3D_PWR_KEYOVERRIDE0_isolate_ack_override_START  (10)
#define SOC_G3D_PWR_KEYOVERRIDE0_isolate_ack_override_END    (11)
#define SOC_G3D_PWR_KEYOVERRIDE0_powertrain_limt_START       (16)
#define SOC_G3D_PWR_KEYOVERRIDE0_powertrain_limt_END         (21)


/*****************************************************************************
 �ṹ��    : SOC_G3D_PWR_KEYOVERRIDE1_UNION
 �ṹ˵��  : PWR_KEYOVERRIDE1 �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: mtcmos���µ�cnt��������
                                                   31���µ��������ʹ��
                                                   30���ϵ��������ʹ��
                                                   29:15;�µ����ֵ
                                                   14:0���ϵ����ֵ */
    } reg;
} SOC_G3D_PWR_KEYOVERRIDE1_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_G3D_PRFCNT_BASE_LO_UNION
 �ṹ˵��  : PRFCNT_BASE_LO �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved       : 8;  /* bit[0-7] : Reserved, write as zero, read undefined. */
        unsigned int  prfcnt_base_lo : 24; /* bit[8-31]: The start address of the memory region where the
                                                         performance counter values can be written. The start
                                                         address is a virtual address in the address space
                                                         specified by the ADDRESS_SPACE field in the
                                                         PRCFNT_CONFIG register */
    } reg;
} SOC_G3D_PRFCNT_BASE_LO_UNION;
#endif
#define SOC_G3D_PRFCNT_BASE_LO_prfcnt_base_lo_START  (8)
#define SOC_G3D_PRFCNT_BASE_LO_prfcnt_base_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_PRFCNT_BASE_HI_UNION
 �ṹ˵��  : PRFCNT_BASE_HI �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  prfcnt_base_hi : 16; /* bit[0-15] : The start address of the memory region where the
                                                          performance counter values can be written. The start
                                                          address is a virtual address in the address space
                                                          specified by the ADDRESS_SPACE field in the
                                                          PRCFNT_CONFIG register */
        unsigned int  reserved       : 16; /* bit[16-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_PRFCNT_BASE_HI_UNION;
#endif
#define SOC_G3D_PRFCNT_BASE_HI_prfcnt_base_hi_START  (0)
#define SOC_G3D_PRFCNT_BASE_HI_prfcnt_base_hi_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_G3D_PRFCNT_CONFIG_UNION
 �ṹ˵��  : PRFCNT_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mode          : 2;  /* bit[0-1] : Performance counter mode:
                                                        0 Off. The performance counters are disabled.
                                                        1 Manual. The performance counters are enabled.
                                                        2 to15 Reserved
                                                        To change mode, first change to mode OFF, then wait until the
                                                        PRFCNT_ACTIVE bit in the GPU_STATUS register is low, then
                                                        set the new mode. */
        unsigned int  address_space : 2;  /* bit[2-3] : The index of the address space to which the counters are written. */
        unsigned int  reserved      : 28; /* bit[4-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_PRFCNT_CONFIG_UNION;
#endif
#define SOC_G3D_PRFCNT_CONFIG_mode_START           (0)
#define SOC_G3D_PRFCNT_CONFIG_mode_END             (1)
#define SOC_G3D_PRFCNT_CONFIG_address_space_START  (2)
#define SOC_G3D_PRFCNT_CONFIG_address_space_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_G3D_PRFCNT_JM_EN_UNION
 �ṹ˵��  : PRFCNT_JM_EN �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pfrcnt_jm_en : 32; /* bit[0-31]: Enables the performance counter. */
    } reg;
} SOC_G3D_PRFCNT_JM_EN_UNION;
#endif
#define SOC_G3D_PRFCNT_JM_EN_pfrcnt_jm_en_START  (0)
#define SOC_G3D_PRFCNT_JM_EN_pfrcnt_jm_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_PRFCNT_SHADER_EN_UNION
 �ṹ˵��  : PRFCNT_SHADER_EN �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pfrcnt_shader_en : 32; /* bit[0-31]: Enables a subset of the performance counter to be written out to memory */
    } reg;
} SOC_G3D_PRFCNT_SHADER_EN_UNION;
#endif
#define SOC_G3D_PRFCNT_SHADER_EN_pfrcnt_shader_en_START  (0)
#define SOC_G3D_PRFCNT_SHADER_EN_pfrcnt_shader_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_PRFCNT_TILER_EN_UNION
 �ṹ˵��  : PRFCNT_TILER_EN �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pfrcnt_tiler_en : 32; /* bit[0-31]: Enables a subset of the performance counter to be written out to memory */
    } reg;
} SOC_G3D_PRFCNT_TILER_EN_UNION;
#endif
#define SOC_G3D_PRFCNT_TILER_EN_pfrcnt_tiler_en_START  (0)
#define SOC_G3D_PRFCNT_TILER_EN_pfrcnt_tiler_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_PRFCNT_MMU_L2_EN_UNION
 �ṹ˵��  : PRFCNT_MMU_L2_EN �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pfrcnt_mmu_en : 32; /* bit[0-31]: Enables a subset of the performance counter to be written out to memory */
    } reg;
} SOC_G3D_PRFCNT_MMU_L2_EN_UNION;
#endif
#define SOC_G3D_PRFCNT_MMU_L2_EN_pfrcnt_mmu_en_START  (0)
#define SOC_G3D_PRFCNT_MMU_L2_EN_pfrcnt_mmu_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_CYCLE_COUNT_LO_UNION
 �ṹ˵��  : CYCLE_COUNT_LO �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cycle_count_lo : 32; /* bit[0-31]: Cycle counter register  */
    } reg;
} SOC_G3D_CYCLE_COUNT_LO_UNION;
#endif
#define SOC_G3D_CYCLE_COUNT_LO_cycle_count_lo_START  (0)
#define SOC_G3D_CYCLE_COUNT_LO_cycle_count_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_CYCLE_COUNT_HI_UNION
 �ṹ˵��  : CYCLE_COUNT_HI �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cycle_count_hi : 32; /* bit[0-31]: Cycle counter register  */
    } reg;
} SOC_G3D_CYCLE_COUNT_HI_UNION;
#endif
#define SOC_G3D_CYCLE_COUNT_HI_cycle_count_hi_START  (0)
#define SOC_G3D_CYCLE_COUNT_HI_cycle_count_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TIMESTAMP_LO_UNION
 �ṹ˵��  : TIMESTAMP_LO �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timestamp_lo : 32; /* bit[0-31]: Timestamp register :64-bit value of the global timestamp. The value is the current
                                                       broadcast value of the system time counter. */
    } reg;
} SOC_G3D_TIMESTAMP_LO_UNION;
#endif
#define SOC_G3D_TIMESTAMP_LO_timestamp_lo_START  (0)
#define SOC_G3D_TIMESTAMP_LO_timestamp_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TIMESTAMP_HI_UNION
 �ṹ˵��  : TIMESTAMP_HI �Ĵ����ṹ���塣��ַƫ����:0x009C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timestamp_hi : 32; /* bit[0-31]: Timestamp register :64-bit value of the global timestamp. The value is the current
                                                       broadcast value of the system time counter. */
    } reg;
} SOC_G3D_TIMESTAMP_HI_UNION;
#endif
#define SOC_G3D_TIMESTAMP_HI_timestamp_hi_START  (0)
#define SOC_G3D_TIMESTAMP_HI_timestamp_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_THREAD_MAX_THREADS_UNION
 �ṹ˵��  : THREAD_MAX_THREADS �Ĵ����ṹ���塣��ַƫ����:0x00A0����ֵ:0x00000100�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thread_max_thread : 32; /* bit[0-31]: ����shader core����̸߳��� */
    } reg;
} SOC_G3D_THREAD_MAX_THREADS_UNION;
#endif
#define SOC_G3D_THREAD_MAX_THREADS_thread_max_thread_START  (0)
#define SOC_G3D_THREAD_MAX_THREADS_thread_max_thread_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_THREAD_MAX_WORKGROUP_UNION
 �ṹ˵��  : THREAD_MAX_WORKGROUP �Ĵ����ṹ���塣��ַƫ����:0x00A4����ֵ:0x00000100�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thread_max_workgroup : 32; /* bit[0-31]: workgroup����̸߳��� */
    } reg;
} SOC_G3D_THREAD_MAX_WORKGROUP_UNION;
#endif
#define SOC_G3D_THREAD_MAX_WORKGROUP_thread_max_workgroup_START  (0)
#define SOC_G3D_THREAD_MAX_WORKGROUP_thread_max_workgroup_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_THREAD_MAX_BARRIER_SIZE_UNION
 �ṹ˵��  : THREAD_MAX_BARRIER_SIZE �Ĵ����ṹ���塣��ַƫ����:0x00A8����ֵ:0x00000100�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thread_max_barrier_size : 32; /* bit[0-31]: ��Ӳ��barrierʱ�ĵȴ���������̸߳��� */
    } reg;
} SOC_G3D_THREAD_MAX_BARRIER_SIZE_UNION;
#endif
#define SOC_G3D_THREAD_MAX_BARRIER_SIZE_thread_max_barrier_size_START  (0)
#define SOC_G3D_THREAD_MAX_BARRIER_SIZE_thread_max_barrier_size_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_THREAD_FEATURES_UNION
 �ṹ˵��  : THREAD_FEATURES �Ĵ����ṹ���塣��ַƫ����:0x00AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  max_registers          : 16; /* bit[0-15] : Maximum size fo register file available for each core. A register is 128bit wide. */
        unsigned int  max_task_queue         : 8;  /* bit[16-23]: Maximum number of tasks that can be sent to a core before it becomes blocked.Thsi value is an 8-bit unsigned integer */
        unsigned int  max_thread_group_split : 6;  /* bit[24-29]: maximum allowed thread group split value field in a job descriptor.This value is a 6-bit unsigned integer. */
        unsigned int  reserved               : 2;  /* bit[30-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_THREAD_FEATURES_UNION;
#endif
#define SOC_G3D_THREAD_FEATURES_max_registers_START           (0)
#define SOC_G3D_THREAD_FEATURES_max_registers_END             (15)
#define SOC_G3D_THREAD_FEATURES_max_task_queue_START          (16)
#define SOC_G3D_THREAD_FEATURES_max_task_queue_END            (23)
#define SOC_G3D_THREAD_FEATURES_max_thread_group_split_START  (24)
#define SOC_G3D_THREAD_FEATURES_max_thread_group_split_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TEXTURE_FEATURES_0_UNION
 �ṹ˵��  : TEXTURE_FEATURES_0 �Ĵ����ṹ���塣��ַƫ����:0x00B0����ֵ:0x01FFFFDF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  texture_features_0 : 32; /* bit[0-31]: ����ѹ��ȫ֧�� */
    } reg;
} SOC_G3D_TEXTURE_FEATURES_0_UNION;
#endif
#define SOC_G3D_TEXTURE_FEATURES_0_texture_features_0_START  (0)
#define SOC_G3D_TEXTURE_FEATURES_0_texture_features_0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TEXTURE_FEATURES_1_UNION
 �ṹ˵��  : TEXTURE_FEATURES_1 �Ĵ����ṹ���塣��ַƫ����:0x00B4����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  texture_features_1 : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TEXTURE_FEATURES_1_UNION;
#endif
#define SOC_G3D_TEXTURE_FEATURES_1_texture_features_1_START  (0)
#define SOC_G3D_TEXTURE_FEATURES_1_texture_features_1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TEXTURE_FEATURES_2_UNION
 �ṹ˵��  : TEXTURE_FEATURES_2 �Ĵ����ṹ���塣��ַƫ����:0x00B8����ֵ:0x9F81FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  texture_features_2 : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TEXTURE_FEATURES_2_UNION;
#endif
#define SOC_G3D_TEXTURE_FEATURES_2_texture_features_2_START  (0)
#define SOC_G3D_TEXTURE_FEATURES_2_texture_features_2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_FEATURES_UNION
 �ṹ˵��  : JS0_FEATURES �Ĵ����ṹ���塣��ַƫ����:0x00C0����ֵ:0x0000020E�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js0_features : 32; /* bit[0-31]: JS0_FEATURES registers  */
    } reg;
} SOC_G3D_JS0_FEATURES_UNION;
#endif
#define SOC_G3D_JS0_FEATURES_js0_features_START  (0)
#define SOC_G3D_JS0_FEATURES_js0_features_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_FEATURES_UNION
 �ṹ˵��  : JS1_FEATURES �Ĵ����ṹ���塣��ַƫ����:0x00C4����ֵ:0x000001FE�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_features : 32; /* bit[0-31]: JS1_FEATURES registers */
    } reg;
} SOC_G3D_JS1_FEATURES_UNION;
#endif
#define SOC_G3D_JS1_FEATURES_js1_features_START  (0)
#define SOC_G3D_JS1_FEATURES_js1_features_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_FEATURES_UNION
 �ṹ˵��  : JS2_FEATURES �Ĵ����ṹ���塣��ַƫ����:0x00C8����ֵ:0x0000007E�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_features : 32; /* bit[0-31]: JS2_FEATURES registers */
    } reg;
} SOC_G3D_JS2_FEATURES_UNION;
#endif
#define SOC_G3D_JS2_FEATURES_js2_features_START  (0)
#define SOC_G3D_JS2_FEATURES_js2_features_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_SHADER_PRESENT_LO_UNION
 �ṹ˵��  : SHADER_PRESENT_LO �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x0000000F�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_present_lo : 32; /* bit[0-31]: shader core ���� */
    } reg;
} SOC_G3D_SHADER_PRESENT_LO_UNION;
#endif
#define SOC_G3D_SHADER_PRESENT_LO_shader_present_lo_START  (0)
#define SOC_G3D_SHADER_PRESENT_LO_shader_present_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_SHADER_PRESENT_HI_UNION
 �ṹ˵��  : SHADER_PRESENT_HI �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_present_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_SHADER_PRESENT_HI_UNION;
#endif
#define SOC_G3D_SHADER_PRESENT_HI_shader_present_hi_START  (0)
#define SOC_G3D_SHADER_PRESENT_HI_shader_present_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TILER_PRESENT_LO_UNION
 �ṹ˵��  : TILER_PRESENT_LO �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_present_lo : 32; /* bit[0-31]: tiler ���� */
    } reg;
} SOC_G3D_TILER_PRESENT_LO_UNION;
#endif
#define SOC_G3D_TILER_PRESENT_LO_tiler_present_lo_START  (0)
#define SOC_G3D_TILER_PRESENT_LO_tiler_present_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TILER_PRESENT_HI_UNION
 �ṹ˵��  : TILER_PRESENT_HI �Ĵ����ṹ���塣��ַƫ����:0x0114����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_present_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TILER_PRESENT_HI_UNION;
#endif
#define SOC_G3D_TILER_PRESENT_HI_tiler_present_hi_START  (0)
#define SOC_G3D_TILER_PRESENT_HI_tiler_present_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_L2_PRESENT_LO_UNION
 �ṹ˵��  : L2_PRESENT_LO �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_present_lo : 32; /* bit[0-31]: l2���� */
    } reg;
} SOC_G3D_L2_PRESENT_LO_UNION;
#endif
#define SOC_G3D_L2_PRESENT_LO_l2_present_lo_START  (0)
#define SOC_G3D_L2_PRESENT_LO_l2_present_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_L2_PRESENT_HI_UNION
 �ṹ˵��  : L2_PRESENT_HI �Ĵ����ṹ���塣��ַƫ����:0x0124����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_present_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_L2_PRESENT_HI_UNION;
#endif
#define SOC_G3D_L2_PRESENT_HI_l2_present_hi_START  (0)
#define SOC_G3D_L2_PRESENT_HI_l2_present_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_SHADER_READY_LO_UNION
 �ṹ˵��  : SHADER_READY_LO �Ĵ����ṹ���塣��ַƫ����:0x0140����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_ready_lo : 32; /* bit[0-31]: shader core ready ���� */
    } reg;
} SOC_G3D_SHADER_READY_LO_UNION;
#endif
#define SOC_G3D_SHADER_READY_LO_shader_ready_lo_START  (0)
#define SOC_G3D_SHADER_READY_LO_shader_ready_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_SHADER_READY_HI_UNION
 �ṹ˵��  : SHADER_READY_HI �Ĵ����ṹ���塣��ַƫ����:0x0144����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_ready_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_SHADER_READY_HI_UNION;
#endif
#define SOC_G3D_SHADER_READY_HI_shader_ready_hi_START  (0)
#define SOC_G3D_SHADER_READY_HI_shader_ready_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TILER_READY_LO_UNION
 �ṹ˵��  : TILER_READY_LO �Ĵ����ṹ���塣��ַƫ����:0x0150����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_ready_lo : 32; /* bit[0-31]: tiler ready ���� */
    } reg;
} SOC_G3D_TILER_READY_LO_UNION;
#endif
#define SOC_G3D_TILER_READY_LO_tiler_ready_lo_START  (0)
#define SOC_G3D_TILER_READY_LO_tiler_ready_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TILER_READY_HI_UNION
 �ṹ˵��  : TILER_READY_HI �Ĵ����ṹ���塣��ַƫ����:0x0154����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_ready_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TILER_READY_HI_UNION;
#endif
#define SOC_G3D_TILER_READY_HI_tiler_ready_hi_START  (0)
#define SOC_G3D_TILER_READY_HI_tiler_ready_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_L2_READY_LO_UNION
 �ṹ˵��  : L2_READY_LO �Ĵ����ṹ���塣��ַƫ����:0x0160����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_ready_lo : 32; /* bit[0-31]: l2 cache ready ���� */
    } reg;
} SOC_G3D_L2_READY_LO_UNION;
#endif
#define SOC_G3D_L2_READY_LO_l2_ready_lo_START  (0)
#define SOC_G3D_L2_READY_LO_l2_ready_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_L2_READY_HI_UNION
 �ṹ˵��  : L2_READY_HI �Ĵ����ṹ���塣��ַƫ����:0x0164����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_ready_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_L2_READY_HI_UNION;
#endif
#define SOC_G3D_L2_READY_HI_l2_ready_hi_START  (0)
#define SOC_G3D_L2_READY_HI_l2_ready_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_SHADER_PWRON_LO_UNION
 �ṹ˵��  : SHADER_PWRON_LO �Ĵ����ṹ���塣��ַƫ����:0x0180����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_pwron_lo : 32; /* bit[0-31]: ����shader core�ϵ硣���shader core�����µ��ʱ���·��ϵ����������ᱻ���棬��shader core�µ���ɺ��������ϵ硣 */
    } reg;
} SOC_G3D_SHADER_PWRON_LO_UNION;
#endif
#define SOC_G3D_SHADER_PWRON_LO_shader_pwron_lo_START  (0)
#define SOC_G3D_SHADER_PWRON_LO_shader_pwron_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_SHADER_PWRON_HI_UNION
 �ṹ˵��  : SHADER_PWRON_HI �Ĵ����ṹ���塣��ַƫ����:0x0184����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_pwron_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_SHADER_PWRON_HI_UNION;
#endif
#define SOC_G3D_SHADER_PWRON_HI_shader_pwron_hi_START  (0)
#define SOC_G3D_SHADER_PWRON_HI_shader_pwron_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TILER_PWRON_LO_UNION
 �ṹ˵��  : TILER_PWRON_LO �Ĵ����ṹ���塣��ַƫ����:0x0190����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwron_lo : 32; /* bit[0-31]: ����tiler �ϵ� */
    } reg;
} SOC_G3D_TILER_PWRON_LO_UNION;
#endif
#define SOC_G3D_TILER_PWRON_LO_tiler_pwron_lo_START  (0)
#define SOC_G3D_TILER_PWRON_LO_tiler_pwron_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TILER_PWRON_HI_UNION
 �ṹ˵��  : TILER_PWRON_HI �Ĵ����ṹ���塣��ַƫ����:0x0194����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwron_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TILER_PWRON_HI_UNION;
#endif
#define SOC_G3D_TILER_PWRON_HI_tiler_pwron_hi_START  (0)
#define SOC_G3D_TILER_PWRON_HI_tiler_pwron_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_L2_PWRON_LO_UNION
 �ṹ˵��  : L2_PWRON_LO �Ĵ����ṹ���塣��ַƫ����:0x01A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwron_lo : 32; /* bit[0-31]: ����l2 cache�ϵ� */
    } reg;
} SOC_G3D_L2_PWRON_LO_UNION;
#endif
#define SOC_G3D_L2_PWRON_LO_l2_pwron_lo_START  (0)
#define SOC_G3D_L2_PWRON_LO_l2_pwron_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_L2_PWRON_HI_UNION
 �ṹ˵��  : L2_PWRON_HI �Ĵ����ṹ���塣��ַƫ����:0x01A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwron_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_L2_PWRON_HI_UNION;
#endif
#define SOC_G3D_L2_PWRON_HI_l2_pwron_hi_START  (0)
#define SOC_G3D_L2_PWRON_HI_l2_pwron_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_SHADER_PWROFF_LO_UNION
 �ṹ˵��  : SHADER_PWROFF_LO �Ĵ����ṹ���塣��ַƫ����:0x01C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_pwroff_lo : 32; /* bit[0-31]: ����shader core �µ� */
    } reg;
} SOC_G3D_SHADER_PWROFF_LO_UNION;
#endif
#define SOC_G3D_SHADER_PWROFF_LO_shader_pwroff_lo_START  (0)
#define SOC_G3D_SHADER_PWROFF_LO_shader_pwroff_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_SHADER_PWROFF_HI_UNION
 �ṹ˵��  : SHADER_PWROFF_HI �Ĵ����ṹ���塣��ַƫ����:0x01C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_pwroff_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_SHADER_PWROFF_HI_UNION;
#endif
#define SOC_G3D_SHADER_PWROFF_HI_shader_pwroff_hi_START  (0)
#define SOC_G3D_SHADER_PWROFF_HI_shader_pwroff_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TILER_PWROFF_LO_UNION
 �ṹ˵��  : TILER_PWROFF_LO �Ĵ����ṹ���塣��ַƫ����:0x01D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwroff_lo : 32; /* bit[0-31]: ����tiler�µ� */
    } reg;
} SOC_G3D_TILER_PWROFF_LO_UNION;
#endif
#define SOC_G3D_TILER_PWROFF_LO_tiler_pwroff_lo_START  (0)
#define SOC_G3D_TILER_PWROFF_LO_tiler_pwroff_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TILER_PWROFF_HI_UNION
 �ṹ˵��  : TILER_PWROFF_HI �Ĵ����ṹ���塣��ַƫ����:0x01D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwroff_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TILER_PWROFF_HI_UNION;
#endif
#define SOC_G3D_TILER_PWROFF_HI_tiler_pwroff_hi_START  (0)
#define SOC_G3D_TILER_PWROFF_HI_tiler_pwroff_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_L2_PWROFF_LO_UNION
 �ṹ˵��  : L2_PWROFF_LO �Ĵ����ṹ���塣��ַƫ����:0x01E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwroff_lo : 32; /* bit[0-31]: ����l2 cache�µ� */
    } reg;
} SOC_G3D_L2_PWROFF_LO_UNION;
#endif
#define SOC_G3D_L2_PWROFF_LO_l2_pwroff_lo_START  (0)
#define SOC_G3D_L2_PWROFF_LO_l2_pwroff_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_L2_PWROFF_HI_UNION
 �ṹ˵��  : L2_PWROFF_HI �Ĵ����ṹ���塣��ַƫ����:0x01E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwroff_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_L2_PWROFF_HI_UNION;
#endif
#define SOC_G3D_L2_PWROFF_HI_l2_pwroff_hi_START  (0)
#define SOC_G3D_L2_PWROFF_HI_l2_pwroff_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_SHADER_PWRTRANS_LO_UNION
 �ṹ˵��  : SHADER_PWRTRANS_LO �Ĵ����ṹ���塣��ַƫ����:0x0200����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: shader core�������µ� */
    } reg;
} SOC_G3D_SHADER_PWRTRANS_LO_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_G3D_SHADER_PWRTRANS_HI_UNION
 �ṹ˵��  : SHADER_PWRTRANS_HI �Ĵ����ṹ���塣��ַƫ����:0x0204����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_SHADER_PWRTRANS_HI_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_G3D_TILER_PWRTRANS_LO_UNION
 �ṹ˵��  : TILER_PWRTRANS_LO �Ĵ����ṹ���塣��ַƫ����:0x0210����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwrtrans_lo : 32; /* bit[0-31]: tiler�������µ� */
    } reg;
} SOC_G3D_TILER_PWRTRANS_LO_UNION;
#endif
#define SOC_G3D_TILER_PWRTRANS_LO_tiler_pwrtrans_lo_START  (0)
#define SOC_G3D_TILER_PWRTRANS_LO_tiler_pwrtrans_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TILER_PWRTRANS_HI_UNION
 �ṹ˵��  : TILER_PWRTRANS_HI �Ĵ����ṹ���塣��ַƫ����:0x0214����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwrtrans_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TILER_PWRTRANS_HI_UNION;
#endif
#define SOC_G3D_TILER_PWRTRANS_HI_tiler_pwrtrans_hi_START  (0)
#define SOC_G3D_TILER_PWRTRANS_HI_tiler_pwrtrans_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_L2_PWRTRANS_LO_UNION
 �ṹ˵��  : L2_PWRTRANS_LO �Ĵ����ṹ���塣��ַƫ����:0x0220����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwrtrans_lo : 32; /* bit[0-31]: l2 cache�����µ� */
    } reg;
} SOC_G3D_L2_PWRTRANS_LO_UNION;
#endif
#define SOC_G3D_L2_PWRTRANS_LO_l2_pwrtrans_lo_START  (0)
#define SOC_G3D_L2_PWRTRANS_LO_l2_pwrtrans_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_L2_PWRTRANS_HI_UNION
 �ṹ˵��  : L2_PWRTRANS_HI �Ĵ����ṹ���塣��ַƫ����:0x0224����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwrtrans_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_L2_PWRTRANS_HI_UNION;
#endif
#define SOC_G3D_L2_PWRTRANS_HI_l2_pwrtrans_hi_START  (0)
#define SOC_G3D_L2_PWRTRANS_HI_l2_pwrtrans_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_SHADER_PWRACTIVE_LO_UNION
 �ṹ˵��  : SHADER_PWRACTIVE_LO �Ĵ����ṹ���塣��ַƫ����:0x0240����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_pwractive_lo : 32; /* bit[0-31]: shader core active */
    } reg;
} SOC_G3D_SHADER_PWRACTIVE_LO_UNION;
#endif
#define SOC_G3D_SHADER_PWRACTIVE_LO_shader_pwractive_lo_START  (0)
#define SOC_G3D_SHADER_PWRACTIVE_LO_shader_pwractive_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_SHADER_PWRACTIVE_HI_UNION
 �ṹ˵��  : SHADER_PWRACTIVE_HI �Ĵ����ṹ���塣��ַƫ����:0x0244����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  shader_pwractive_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_SHADER_PWRACTIVE_HI_UNION;
#endif
#define SOC_G3D_SHADER_PWRACTIVE_HI_shader_pwractive_hi_START  (0)
#define SOC_G3D_SHADER_PWRACTIVE_HI_shader_pwractive_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TILER_PWRACTIVE_LO_UNION
 �ṹ˵��  : TILER_PWRACTIVE_LO �Ĵ����ṹ���塣��ַƫ����:0x0250����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwractive_lo : 32; /* bit[0-31]: tiler active */
    } reg;
} SOC_G3D_TILER_PWRACTIVE_LO_UNION;
#endif
#define SOC_G3D_TILER_PWRACTIVE_LO_tiler_pwractive_lo_START  (0)
#define SOC_G3D_TILER_PWRACTIVE_LO_tiler_pwractive_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TILER_PWRACTIVE_HI_UNION
 �ṹ˵��  : TILER_PWRACTIVE_HI �Ĵ����ṹ���塣��ַƫ����:0x0254����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_pwractive_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TILER_PWRACTIVE_HI_UNION;
#endif
#define SOC_G3D_TILER_PWRACTIVE_HI_tiler_pwractive_hi_START  (0)
#define SOC_G3D_TILER_PWRACTIVE_HI_tiler_pwractive_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_L2_PWRACTIVE_LO_UNION
 �ṹ˵��  : L2_PWRACTIVE_LO �Ĵ����ṹ���塣��ַƫ����:0x0260����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwractive_lo : 32; /* bit[0-31]: l2 cache active */
    } reg;
} SOC_G3D_L2_PWRACTIVE_LO_UNION;
#endif
#define SOC_G3D_L2_PWRACTIVE_LO_l2_pwractive_lo_START  (0)
#define SOC_G3D_L2_PWRACTIVE_LO_l2_pwractive_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_L2_PWRACTIVE_HI_UNION
 �ṹ˵��  : L2_PWRACTIVE_HI �Ĵ����ṹ���塣��ַƫ����:0x0264����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  l2_pwractive_hi : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_L2_PWRACTIVE_HI_UNION;
#endif
#define SOC_G3D_L2_PWRACTIVE_HI_l2_pwractive_hi_START  (0)
#define SOC_G3D_L2_PWRACTIVE_HI_l2_pwractive_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_REV_ID_UNION
 �ṹ˵��  : REV_ID �Ĵ����ṹ���塣��ַƫ����:0x0280����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rev_id : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_REV_ID_UNION;
#endif
#define SOC_G3D_REV_ID_rev_id_START  (0)
#define SOC_G3D_REV_ID_rev_id_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JM_CONFIG_UNION
 �ṹ˵��  : JM_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x0F00����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  jc_config : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_JM_CONFIG_UNION;
#endif
#define SOC_G3D_JM_CONFIG_jc_config_START  (0)
#define SOC_G3D_JM_CONFIG_jc_config_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_SHADER_CONFIG_UNION
 �ṹ˵��  : SHADER_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x0F04����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 3;  /* bit[0-2] : RSV */
        unsigned int  all_counters  : 1;  /* bit[3-3] : 0:��
                                                        1:1/8
                                                        2:1/4
                                                        3:1/2 */
        unsigned int  shader_config : 28; /* bit[4-31]: Reserved. write as zero, read undefined.  */
    } reg;
} SOC_G3D_SHADER_CONFIG_UNION;
#endif
#define SOC_G3D_SHADER_CONFIG_all_counters_START   (3)
#define SOC_G3D_SHADER_CONFIG_all_counters_END     (3)
#define SOC_G3D_SHADER_CONFIG_shader_config_START  (4)
#define SOC_G3D_SHADER_CONFIG_shader_config_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_TILER_CONFIG_UNION
 �ṹ˵��  : TILER_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x0F08����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tiler_config : 32; /* bit[0-31]: RSV */
    } reg;
} SOC_G3D_TILER_CONFIG_UNION;
#endif
#define SOC_G3D_TILER_CONFIG_tiler_config_START  (0)
#define SOC_G3D_TILER_CONFIG_tiler_config_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_L2_MMU_CONFIG_UNION
 �ṹ˵��  : L2_MMU_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x0F0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved              : 24; /* bit[0-23] : RSV */
        unsigned int  limit_external_reads  : 2;  /* bit[24-25]: 0:��
                                                                 1:1/8
                                                                 2:1/4
                                                                 3:1/2 */
        unsigned int  limit_external_writes : 2;  /* bit[26-27]: 0:��
                                                                 1:1/8
                                                                 2:1/4
                                                                 3:1/2 */
        unsigned int  l2_mmu_config         : 4;  /* bit[28-31]: Reserved. write as zero, read undefined.  */
    } reg;
} SOC_G3D_L2_MMU_CONFIG_UNION;
#endif
#define SOC_G3D_L2_MMU_CONFIG_limit_external_reads_START   (24)
#define SOC_G3D_L2_MMU_CONFIG_limit_external_reads_END     (25)
#define SOC_G3D_L2_MMU_CONFIG_limit_external_writes_START  (26)
#define SOC_G3D_L2_MMU_CONFIG_limit_external_writes_END    (27)
#define SOC_G3D_L2_MMU_CONFIG_l2_mmu_config_START          (28)
#define SOC_G3D_L2_MMU_CONFIG_l2_mmu_config_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JOB_IRQ_RAWSTAT_UNION
 �ṹ˵��  : JOB_IRQ_RAWSTAT �Ĵ����ṹ���塣��ַƫ����:0x1000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  job_done : 3;  /* bit[0-2]  : job done.1 bit ��Ӧ 1��slot */
        unsigned int  reserved_0: 13; /* bit[3-15] : Reserved. write as zero, read undefined. */
        unsigned int  job_fail : 3;  /* bit[16-18]: job fail.1 bit ��Ӧ 1��slot */
        unsigned int  reserved_1: 13; /* bit[19-31]: Reserved. write as zero, read undefined.  */
    } reg;
} SOC_G3D_JOB_IRQ_RAWSTAT_UNION;
#endif
#define SOC_G3D_JOB_IRQ_RAWSTAT_job_done_START  (0)
#define SOC_G3D_JOB_IRQ_RAWSTAT_job_done_END    (2)
#define SOC_G3D_JOB_IRQ_RAWSTAT_job_fail_START  (16)
#define SOC_G3D_JOB_IRQ_RAWSTAT_job_fail_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JOB_IRQ_CLEAR_UNION
 �ṹ˵��  : JOB_IRQ_CLEAR �Ĵ����ṹ���塣��ַƫ����:0x1004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  job_done      : 3;  /* bit[0-2]  : ��Ӧ�ж�д1����Ĵ��� */
        unsigned int  reserved      : 13; /* bit[3-15] : Interrupt clear register :Reserved, write as zero, read undefined. */
        unsigned int  job_fail      : 3;  /* bit[16-18]: ��Ӧ�ж�д1����Ĵ��� */
        unsigned int  job_irq_clear : 13; /* bit[19-31]: Interrupt clear register :Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_JOB_IRQ_CLEAR_UNION;
#endif
#define SOC_G3D_JOB_IRQ_CLEAR_job_done_START       (0)
#define SOC_G3D_JOB_IRQ_CLEAR_job_done_END         (2)
#define SOC_G3D_JOB_IRQ_CLEAR_job_fail_START       (16)
#define SOC_G3D_JOB_IRQ_CLEAR_job_fail_END         (18)
#define SOC_G3D_JOB_IRQ_CLEAR_job_irq_clear_START  (19)
#define SOC_G3D_JOB_IRQ_CLEAR_job_irq_clear_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JOB_IRQ_MASK_UNION
 �ṹ˵��  : JOB_IRQ_MASK �Ĵ����ṹ���塣��ַƫ����:0x1008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  job_done : 3;  /* bit[0-2]  : ��Ӧд1ʹ�ܼĴ����� */
        unsigned int  reserved_0: 13; /* bit[3-15] : Reserved. write as zero, read undefined. */
        unsigned int  job_fail : 3;  /* bit[16-18]: ��Ӧд1ʹ�ܼĴ����� */
        unsigned int  reserved_1: 13; /* bit[19-31]: Interrupt mask register ��Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JOB_IRQ_MASK_UNION;
#endif
#define SOC_G3D_JOB_IRQ_MASK_job_done_START  (0)
#define SOC_G3D_JOB_IRQ_MASK_job_done_END    (2)
#define SOC_G3D_JOB_IRQ_MASK_job_fail_START  (16)
#define SOC_G3D_JOB_IRQ_MASK_job_fail_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JOB_IRQ_STATUS_UNION
 �ṹ˵��  : JOB_IRQ_STATUS �Ĵ����ṹ���塣��ַƫ����:0x100C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  job_done : 3;  /* bit[0-2]  : ״̬���������߼���״̬ */
        unsigned int  reserved_0: 13; /* bit[3-15] : Reserved. write as zero, read undefined. */
        unsigned int  job_fail : 3;  /* bit[16-18]: ״̬���������߼���״̬ */
        unsigned int  reserved_1: 13; /* bit[19-31]: Interrupt status register ����Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JOB_IRQ_STATUS_UNION;
#endif
#define SOC_G3D_JOB_IRQ_STATUS_job_done_START  (0)
#define SOC_G3D_JOB_IRQ_STATUS_job_done_END    (2)
#define SOC_G3D_JOB_IRQ_STATUS_job_fail_START  (16)
#define SOC_G3D_JOB_IRQ_STATUS_job_fail_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JOB_IRQ_JS_STATE_UNION
 �ṹ˵��  : JOB_IRQ_JS_STATE �Ĵ����ṹ���塣��ַƫ����:0x1010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  job_active_n      : 16; /* bit[0-15] : A job chain is queued in job slot n */
        unsigned int  job_next_active_n : 16; /* bit[16-31]: A job chain is queued in the NEXT registers in job slot n */
    } reg;
} SOC_G3D_JOB_IRQ_JS_STATE_UNION;
#endif
#define SOC_G3D_JOB_IRQ_JS_STATE_job_active_n_START       (0)
#define SOC_G3D_JOB_IRQ_JS_STATE_job_active_n_END         (15)
#define SOC_G3D_JOB_IRQ_JS_STATE_job_next_active_n_START  (16)
#define SOC_G3D_JOB_IRQ_JS_STATE_job_next_active_n_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JOB_IRQ_THROTTLE_UNION
 �ṹ˵��  : JOB_IRQ_THROTTLE �Ĵ����ṹ���塣��ַƫ����:0x1014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  job_irq_throttle : 32; /* bit[0-31]: Interrupt throttle register��Writing a value to the register sets the value of a counter,
                                                           which then continuously counts down at the GPU clock
                                                           frequency. Reading this register returns the current value
                                                           of the counter. */
    } reg;
} SOC_G3D_JOB_IRQ_THROTTLE_UNION;
#endif
#define SOC_G3D_JOB_IRQ_THROTTLE_job_irq_throttle_START  (0)
#define SOC_G3D_JOB_IRQ_THROTTLE_job_irq_throttle_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_HEAD_LO_UNION
 �ṹ˵��  : JS0_HEAD_LO �Ĵ����ṹ���塣��ַƫ����:0x1800����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved    : 6;  /* bit[0-5] : Reserved. write as zero, read undefined. */
        unsigned int  js0_head_lo : 26; /* bit[6-31]: Job queue head pointer for job slot register��Contains the virtual address for the current job
                                                      descriptor */
    } reg;
} SOC_G3D_JS0_HEAD_LO_UNION;
#endif
#define SOC_G3D_JS0_HEAD_LO_js0_head_lo_START  (6)
#define SOC_G3D_JS0_HEAD_LO_js0_head_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_HEAD_HI_UNION
 �ṹ˵��  : JS0_HEAD_HI �Ĵ����ṹ���塣��ַƫ����:0x1804����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js0_head_hi : 16; /* bit[0-15] : Job queue head pointer for job slot register��Contains the virtual address for the current job
                                                       descriptor */
        unsigned int  reserved    : 16; /* bit[16-31]: Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JS0_HEAD_HI_UNION;
#endif
#define SOC_G3D_JS0_HEAD_HI_js0_head_hi_START  (0)
#define SOC_G3D_JS0_HEAD_HI_js0_head_hi_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_TAIL_LO_UNION
 �ṹ˵��  : JS0_TAIL_LO �Ĵ����ṹ���塣��ַƫ����:0x1808����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved    : 6;  /* bit[0-5] : Reserved. write as zero, read undefined. */
        unsigned int  js0_tail_lo : 26; /* bit[6-31]: Contains the virtual address of the oldest job that has
                                                      finished issuing tasks, but is still running. */
    } reg;
} SOC_G3D_JS0_TAIL_LO_UNION;
#endif
#define SOC_G3D_JS0_TAIL_LO_js0_tail_lo_START  (6)
#define SOC_G3D_JS0_TAIL_LO_js0_tail_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_TAIL_HI_UNION
 �ṹ˵��  : JS0_TAIL_HI �Ĵ����ṹ���塣��ַƫ����:0x180C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js0_tail_hi : 16; /* bit[0-15] : Contains the virtual address of the oldest job that has
                                                       finished issuing tasks, but is still running. */
        unsigned int  reserved    : 16; /* bit[16-31]: Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JS0_TAIL_HI_UNION;
#endif
#define SOC_G3D_JS0_TAIL_HI_js0_tail_hi_START  (0)
#define SOC_G3D_JS0_TAIL_HI_js0_tail_hi_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_AFFINITY_LO_UNION
 �ṹ˵��  : JS0_AFFINITY_LO �Ĵ����ṹ���塣��ַƫ����:0x1810����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js0_affinity_lo : 32; /* bit[0-31]: Core affinity mask for job slot register:Contains the address of the oldest job that has finished
                                                          issuing tasks, but is still running. */
    } reg;
} SOC_G3D_JS0_AFFINITY_LO_UNION;
#endif
#define SOC_G3D_JS0_AFFINITY_LO_js0_affinity_lo_START  (0)
#define SOC_G3D_JS0_AFFINITY_LO_js0_affinity_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_AFFINITY_HI_UNION
 �ṹ˵��  : JS0_AFFINITY_HI �Ĵ����ṹ���塣��ַƫ����:0x1814����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js0_affinity_hi : 32; /* bit[0-31]: Core affinity mask register for job slot:Contains the address of the oldest job that has finished
                                                          issuing tasks, but is still running. */
    } reg;
} SOC_G3D_JS0_AFFINITY_HI_UNION;
#endif
#define SOC_G3D_JS0_AFFINITY_HI_js0_affinity_hi_START  (0)
#define SOC_G3D_JS0_AFFINITY_HI_js0_affinity_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_CONFIG_UNION
 �ṹ˵��  : JS0_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x1818����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_space : 4;  /* bit[0-3]  : Selects which of the address spaces to use for jobs in
                                                         this slot. The address space configuration values are
                                                         read from the ASn registers. */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : Reserved, write as zero, read undefined. */
        unsigned int  start_flush   : 2;  /* bit[8-9]  : Cache flush action on job chain start. Specifies what
                                                         action the caches must take before starting the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches except the tiler
                                                         cache. */
        unsigned int  start_mmu     : 1;  /* bit[10]   : MMU action on job chain start. Causes the Job Manager
                                                         to issue an MMU update before the job chain is started. */
        unsigned int  reserved_1    : 1;  /* bit[11]   : Reserved, write as zero, read undefined. */
        unsigned int  end_flush     : 2;  /* bit[12-13]: Cache flush action on job end chain. Specifies what
                                                         action the caches must take after finishing the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches including the
                                                         tiler cache. */
        unsigned int  reserved_2    : 18; /* bit[14-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_JS0_CONFIG_UNION;
#endif
#define SOC_G3D_JS0_CONFIG_address_space_START  (0)
#define SOC_G3D_JS0_CONFIG_address_space_END    (3)
#define SOC_G3D_JS0_CONFIG_start_flush_START    (8)
#define SOC_G3D_JS0_CONFIG_start_flush_END      (9)
#define SOC_G3D_JS0_CONFIG_start_mmu_START      (10)
#define SOC_G3D_JS0_CONFIG_start_mmu_END        (10)
#define SOC_G3D_JS0_CONFIG_end_flush_START      (12)
#define SOC_G3D_JS0_CONFIG_end_flush_END        (13)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_COMMAND_UNION
 �ṹ˵��  : JS0_COMMAND �Ĵ����ṹ���塣��ַƫ����:0x1820����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nop       : 1;  /* bit[0]   : Writing to this value is ignored */
        unsigned int  start     : 1;  /* bit[1]   : Start processing a job chain */
        unsigned int  soft_stop : 1;  /* bit[2]   : A soft stop requests that no more tasks are issued for a
                                                    job, and when all running tasks are finished, the job
                                                    state is written to memory and the job suspended.
                                                    It is possible to recover from this state and continue the
                                                    job. */
        unsigned int  hard_stop : 1;  /* bit[3]   : A hard stop stops all running tasks for a job. No attempt
                                                    is made to finish, write partial results, or save state.
                                                    It is not possible to resume a job after a hard stop,
                                                    although it might be possible to restart it from scratch if
                                                    it does not write to its own inputs. */
        unsigned int  reserved  : 28; /* bit[4-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_JS0_COMMAND_UNION;
#endif
#define SOC_G3D_JS0_COMMAND_nop_START        (0)
#define SOC_G3D_JS0_COMMAND_nop_END          (0)
#define SOC_G3D_JS0_COMMAND_start_START      (1)
#define SOC_G3D_JS0_COMMAND_start_END        (1)
#define SOC_G3D_JS0_COMMAND_soft_stop_START  (2)
#define SOC_G3D_JS0_COMMAND_soft_stop_END    (2)
#define SOC_G3D_JS0_COMMAND_hard_stop_START  (3)
#define SOC_G3D_JS0_COMMAND_hard_stop_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_STATUS_UNION
 �ṹ˵��  : JS0_STATUS �Ĵ����ṹ���塣��ַƫ����:0x1824����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exception_type : 8;  /* bit[0-7] : Contains the type of exception that caused the fault. */
        unsigned int  reserved       : 24; /* bit[8-31]: Status for job slot register:Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_JS0_STATUS_UNION;
#endif
#define SOC_G3D_JS0_STATUS_exception_type_START  (0)
#define SOC_G3D_JS0_STATUS_exception_type_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_HEAD_NEXT_LO_UNION
 �ṹ˵��  : JS0_HEAD_NEXT_LO �Ĵ����ṹ���塣��ַƫ����:0x1840����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js0_head_next_lo : 32; /* bit[0-31]: Next job queue head pointer for job slot register */
    } reg;
} SOC_G3D_JS0_HEAD_NEXT_LO_UNION;
#endif
#define SOC_G3D_JS0_HEAD_NEXT_LO_js0_head_next_lo_START  (0)
#define SOC_G3D_JS0_HEAD_NEXT_LO_js0_head_next_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_HEAD_NEXT_HI_UNION
 �ṹ˵��  : JS0_HEAD_NEXT_HI �Ĵ����ṹ���塣��ַƫ����:0x1844����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js0_head_next_hi : 32; /* bit[0-31]: Next job queue head pointer for job slot register */
    } reg;
} SOC_G3D_JS0_HEAD_NEXT_HI_UNION;
#endif
#define SOC_G3D_JS0_HEAD_NEXT_HI_js0_head_next_hi_START  (0)
#define SOC_G3D_JS0_HEAD_NEXT_HI_js0_head_next_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_AFFINITY_NEXT_LO_UNION
 �ṹ˵��  : JS0_AFFINITY_NEXT_LO �Ĵ����ṹ���塣��ַƫ����:0x1850����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS0_AFFINITY_NEXT_LO_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_AFFINITY_NEXT_HI_UNION
 �ṹ˵��  : JS0_AFFINITY_NEXT_HI �Ĵ����ṹ���塣��ַƫ����:0x1854����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS0_AFFINITY_NEXT_HI_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_CONFIG_NEXT_UNION
 �ṹ˵��  : JS0_CONFIG_NEXT �Ĵ����ṹ���塣��ַƫ����:0x1858����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_space : 4;  /* bit[0-3]  : Selects which of the address spaces to use for jobs in
                                                         this slot. The address space configuration values are
                                                         read from the ASn registers. */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : Reserved, write as zero, read undefined. */
        unsigned int  start_flush   : 2;  /* bit[8-9]  : Cache flush action on job chain start. Specifies what
                                                         action the caches must take before starting the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches except the tiler
                                                         cache. */
        unsigned int  start_mmu     : 1;  /* bit[10]   : MMU action on job chain start. Causes the Job Manager
                                                         to issue an MMU update before the job chain is started. */
        unsigned int  reserved_1    : 1;  /* bit[11]   : Reserved, write as zero, read undefined. */
        unsigned int  end_flush     : 2;  /* bit[12-13]: Cache flush action on job end chain. Specifies what
                                                         action the caches must take after finishing the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches including the
                                                         tiler cache. */
        unsigned int  reserved_2    : 18; /* bit[14-31]: Next configuration setting for job slot register
                                                         The JSn_CONFIG_NEXT register is an identical register used to construct job chains one ahead
                                                         so maintaining throughput. The values in the register are loaded into the JSn_CONFIG register
                                                         when the current job chain completes */
    } reg;
} SOC_G3D_JS0_CONFIG_NEXT_UNION;
#endif
#define SOC_G3D_JS0_CONFIG_NEXT_address_space_START  (0)
#define SOC_G3D_JS0_CONFIG_NEXT_address_space_END    (3)
#define SOC_G3D_JS0_CONFIG_NEXT_start_flush_START    (8)
#define SOC_G3D_JS0_CONFIG_NEXT_start_flush_END      (9)
#define SOC_G3D_JS0_CONFIG_NEXT_start_mmu_START      (10)
#define SOC_G3D_JS0_CONFIG_NEXT_start_mmu_END        (10)
#define SOC_G3D_JS0_CONFIG_NEXT_end_flush_START      (12)
#define SOC_G3D_JS0_CONFIG_NEXT_end_flush_END        (13)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS0_COMMAND_NEXT_UNION
 �ṹ˵��  : JS0_COMMAND_NEXT �Ĵ����ṹ���塣��ַƫ����:0x1860����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next command for job slot register */
    } reg;
} SOC_G3D_JS0_COMMAND_NEXT_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_HEAD_LO_UNION
 �ṹ˵��  : JS1_HEAD_LO �Ĵ����ṹ���塣��ַƫ����:0x1880����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved    : 6;  /* bit[0-5] : Reserved. write as zero, read undefined. */
        unsigned int  js1_head_lo : 26; /* bit[6-31]: Job queue head pointer for job slot register��Contains the virtual address for the current job
                                                      descriptor */
    } reg;
} SOC_G3D_JS1_HEAD_LO_UNION;
#endif
#define SOC_G3D_JS1_HEAD_LO_js1_head_lo_START  (6)
#define SOC_G3D_JS1_HEAD_LO_js1_head_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_HEAD_HI_UNION
 �ṹ˵��  : JS1_HEAD_HI �Ĵ����ṹ���塣��ַƫ����:0x1884����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_head_hi : 16; /* bit[0-15] : Job queue head pointer for job slot register��Contains the virtual address for the current job
                                                       descriptor */
        unsigned int  reserved    : 16; /* bit[16-31]: Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JS1_HEAD_HI_UNION;
#endif
#define SOC_G3D_JS1_HEAD_HI_js1_head_hi_START  (0)
#define SOC_G3D_JS1_HEAD_HI_js1_head_hi_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_TAIL_LO_UNION
 �ṹ˵��  : JS1_TAIL_LO �Ĵ����ṹ���塣��ַƫ����:0x1888����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved    : 6;  /* bit[0-5] : Reserved. write as zero, read undefined. */
        unsigned int  js1_tail_lo : 26; /* bit[6-31]: Contains the virtual address of the oldest job that has
                                                      finished issuing tasks, but is still running. */
    } reg;
} SOC_G3D_JS1_TAIL_LO_UNION;
#endif
#define SOC_G3D_JS1_TAIL_LO_js1_tail_lo_START  (6)
#define SOC_G3D_JS1_TAIL_LO_js1_tail_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_TAIL_HI_UNION
 �ṹ˵��  : JS1_TAIL_HI �Ĵ����ṹ���塣��ַƫ����:0x188C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_tail_hi : 16; /* bit[0-15] : Contains the virtual address of the oldest job that has
                                                       finished issuing tasks, but is still running. */
        unsigned int  reserved    : 16; /* bit[16-31]: Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JS1_TAIL_HI_UNION;
#endif
#define SOC_G3D_JS1_TAIL_HI_js1_tail_hi_START  (0)
#define SOC_G3D_JS1_TAIL_HI_js1_tail_hi_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_AFFINITY_LO_UNION
 �ṹ˵��  : JS1_AFFINITY_LO �Ĵ����ṹ���塣��ַƫ����:0x1890����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_affinity_lo : 32; /* bit[0-31]: Core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS1_AFFINITY_LO_UNION;
#endif
#define SOC_G3D_JS1_AFFINITY_LO_js1_affinity_lo_START  (0)
#define SOC_G3D_JS1_AFFINITY_LO_js1_affinity_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_AFFINITY_HI_UNION
 �ṹ˵��  : JS1_AFFINITY_HI �Ĵ����ṹ���塣��ַƫ����:0x1894����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_affinity_hi : 32; /* bit[0-31]: Core affinity mask register for job slot */
    } reg;
} SOC_G3D_JS1_AFFINITY_HI_UNION;
#endif
#define SOC_G3D_JS1_AFFINITY_HI_js1_affinity_hi_START  (0)
#define SOC_G3D_JS1_AFFINITY_HI_js1_affinity_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_CONFIG_UNION
 �ṹ˵��  : JS1_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x1898����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_space : 4;  /* bit[0-3]  : Selects which of the address spaces to use for jobs in
                                                         this slot. The address space configuration values are
                                                         read from the ASn registers. */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : Reserved, write as zero, read undefined. */
        unsigned int  start_flush   : 2;  /* bit[8-9]  : Cache flush action on job chain start. Specifies what
                                                         action the caches must take before starting the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches except the tiler
                                                         cache. */
        unsigned int  start_mmu     : 1;  /* bit[10]   : MMU action on job chain start. Causes the Job Manager
                                                         to issue an MMU update before the job chain is started. */
        unsigned int  reserved_1    : 1;  /* bit[11]   : Reserved, write as zero, read undefined. */
        unsigned int  end_flush     : 2;  /* bit[12-13]: Cache flush action on job end chain. Specifies what
                                                         action the caches must take after finishing the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches including the
                                                         tiler cache. */
        unsigned int  reserved_2    : 18; /* bit[14-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_JS1_CONFIG_UNION;
#endif
#define SOC_G3D_JS1_CONFIG_address_space_START  (0)
#define SOC_G3D_JS1_CONFIG_address_space_END    (3)
#define SOC_G3D_JS1_CONFIG_start_flush_START    (8)
#define SOC_G3D_JS1_CONFIG_start_flush_END      (9)
#define SOC_G3D_JS1_CONFIG_start_mmu_START      (10)
#define SOC_G3D_JS1_CONFIG_start_mmu_END        (10)
#define SOC_G3D_JS1_CONFIG_end_flush_START      (12)
#define SOC_G3D_JS1_CONFIG_end_flush_END        (13)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_COMMAND_UNION
 �ṹ˵��  : JS1_COMMAND �Ĵ����ṹ���塣��ַƫ����:0x18A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_command : 32; /* bit[0-31]: Command for job slot register */
    } reg;
} SOC_G3D_JS1_COMMAND_UNION;
#endif
#define SOC_G3D_JS1_COMMAND_js1_command_START  (0)
#define SOC_G3D_JS1_COMMAND_js1_command_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_STATUS_UNION
 �ṹ˵��  : JS1_STATUS �Ĵ����ṹ���塣��ַƫ����:0x18A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_status : 32; /* bit[0-31]: Status for job slot register */
    } reg;
} SOC_G3D_JS1_STATUS_UNION;
#endif
#define SOC_G3D_JS1_STATUS_js1_status_START  (0)
#define SOC_G3D_JS1_STATUS_js1_status_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_HEAD_NEXT_LO_UNION
 �ṹ˵��  : JS1_HEAD_NEXT_LO �Ĵ����ṹ���塣��ַƫ����:0x18C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_head_next_lo : 32; /* bit[0-31]: Next job queue head pointer for job slot register */
    } reg;
} SOC_G3D_JS1_HEAD_NEXT_LO_UNION;
#endif
#define SOC_G3D_JS1_HEAD_NEXT_LO_js1_head_next_lo_START  (0)
#define SOC_G3D_JS1_HEAD_NEXT_LO_js1_head_next_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_HEAD_NEXT_HI_UNION
 �ṹ˵��  : JS1_HEAD_NEXT_HI �Ĵ����ṹ���塣��ַƫ����:0x18C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js1_head_next_hi : 32; /* bit[0-31]: Next job queue head pointer for job slot register */
    } reg;
} SOC_G3D_JS1_HEAD_NEXT_HI_UNION;
#endif
#define SOC_G3D_JS1_HEAD_NEXT_HI_js1_head_next_hi_START  (0)
#define SOC_G3D_JS1_HEAD_NEXT_HI_js1_head_next_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_AFFINITY_NEXT_LO_UNION
 �ṹ˵��  : JS1_AFFINITY_NEXT_LO �Ĵ����ṹ���塣��ַƫ����:0x18D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS1_AFFINITY_NEXT_LO_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_AFFINITY_NEXT_HI_UNION
 �ṹ˵��  : JS1_AFFINITY_NEXT_HI �Ĵ����ṹ���塣��ַƫ����:0x18D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS1_AFFINITY_NEXT_HI_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_CONFIG_NEXT_UNION
 �ṹ˵��  : JS1_CONFIG_NEXT �Ĵ����ṹ���塣��ַƫ����:0x18D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_space : 4;  /* bit[0-3]  : Selects which of the address spaces to use for jobs in
                                                         this slot. The address space configuration values are
                                                         read from the ASn registers. */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : Reserved, write as zero, read undefined. */
        unsigned int  start_flush   : 2;  /* bit[8-9]  : Cache flush action on job chain start. Specifies what
                                                         action the caches must take before starting the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches except the tiler
                                                         cache. */
        unsigned int  start_mmu     : 1;  /* bit[10]   : MMU action on job chain start. Causes the Job Manager
                                                         to issue an MMU update before the job chain is started. */
        unsigned int  reserved_1    : 1;  /* bit[11]   : Reserved, write as zero, read undefined. */
        unsigned int  end_flush     : 2;  /* bit[12-13]: Cache flush action on job end chain. Specifies what
                                                         action the caches must take after finishing the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches including the
                                                         tiler cache. */
        unsigned int  reserved_2    : 18; /* bit[14-31]: Next configuration setting for job slot register
                                                         The JSn_CONFIG_NEXT register is an identical register used to construct job chains one ahead
                                                         so maintaining throughput. The values in the register are loaded into the JSn_CONFIG register
                                                         when the current job chain completes */
    } reg;
} SOC_G3D_JS1_CONFIG_NEXT_UNION;
#endif
#define SOC_G3D_JS1_CONFIG_NEXT_address_space_START  (0)
#define SOC_G3D_JS1_CONFIG_NEXT_address_space_END    (3)
#define SOC_G3D_JS1_CONFIG_NEXT_start_flush_START    (8)
#define SOC_G3D_JS1_CONFIG_NEXT_start_flush_END      (9)
#define SOC_G3D_JS1_CONFIG_NEXT_start_mmu_START      (10)
#define SOC_G3D_JS1_CONFIG_NEXT_start_mmu_END        (10)
#define SOC_G3D_JS1_CONFIG_NEXT_end_flush_START      (12)
#define SOC_G3D_JS1_CONFIG_NEXT_end_flush_END        (13)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS1_COMMAND_NEXT_UNION
 �ṹ˵��  : JS1_COMMAND_NEXT �Ĵ����ṹ���塣��ַƫ����:0x18E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next command for job slot register */
    } reg;
} SOC_G3D_JS1_COMMAND_NEXT_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_HEAD_LO_UNION
 �ṹ˵��  : JS2_HEAD_LO �Ĵ����ṹ���塣��ַƫ����:0x1900����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved    : 6;  /* bit[0-5] : Reserved. write as zero, read undefined. */
        unsigned int  js2_head_lo : 26; /* bit[6-31]: Job queue head pointer for job slot register��Contains the virtual address for the current job
                                                      descriptor */
    } reg;
} SOC_G3D_JS2_HEAD_LO_UNION;
#endif
#define SOC_G3D_JS2_HEAD_LO_js2_head_lo_START  (6)
#define SOC_G3D_JS2_HEAD_LO_js2_head_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_HEAD_HI_UNION
 �ṹ˵��  : JS2_HEAD_HI �Ĵ����ṹ���塣��ַƫ����:0x1904����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_head_hi : 16; /* bit[0-15] : Job queue head pointer for job slot register��Contains the virtual address for the current job
                                                       descriptor */
        unsigned int  reserved    : 16; /* bit[16-31]: Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JS2_HEAD_HI_UNION;
#endif
#define SOC_G3D_JS2_HEAD_HI_js2_head_hi_START  (0)
#define SOC_G3D_JS2_HEAD_HI_js2_head_hi_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_TAIL_LO_UNION
 �ṹ˵��  : JS2_TAIL_LO �Ĵ����ṹ���塣��ַƫ����:0x1908����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved    : 6;  /* bit[0-5] : Reserved. write as zero, read undefined. */
        unsigned int  js2_tail_lo : 26; /* bit[6-31]: Contains the virtual address of the oldest job that has
                                                      finished issuing tasks, but is still running. */
    } reg;
} SOC_G3D_JS2_TAIL_LO_UNION;
#endif
#define SOC_G3D_JS2_TAIL_LO_js2_tail_lo_START  (6)
#define SOC_G3D_JS2_TAIL_LO_js2_tail_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_TAIL_HI_UNION
 �ṹ˵��  : JS2_TAIL_HI �Ĵ����ṹ���塣��ַƫ����:0x190C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_tail_hi : 16; /* bit[0-15] : Contains the virtual address of the oldest job that has
                                                       finished issuing tasks, but is still running. */
        unsigned int  reserved    : 16; /* bit[16-31]: Reserved. write as zero, read undefined. */
    } reg;
} SOC_G3D_JS2_TAIL_HI_UNION;
#endif
#define SOC_G3D_JS2_TAIL_HI_js2_tail_hi_START  (0)
#define SOC_G3D_JS2_TAIL_HI_js2_tail_hi_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_AFFINITY_LO_UNION
 �ṹ˵��  : JS2_AFFINITY_LO �Ĵ����ṹ���塣��ַƫ����:0x1910����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_affinity_lo : 32; /* bit[0-31]: Core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS2_AFFINITY_LO_UNION;
#endif
#define SOC_G3D_JS2_AFFINITY_LO_js2_affinity_lo_START  (0)
#define SOC_G3D_JS2_AFFINITY_LO_js2_affinity_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_AFFINITY_HI_UNION
 �ṹ˵��  : JS2_AFFINITY_HI �Ĵ����ṹ���塣��ַƫ����:0x1914����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_affinity_hi : 32; /* bit[0-31]: Core affinity mask register for job slot */
    } reg;
} SOC_G3D_JS2_AFFINITY_HI_UNION;
#endif
#define SOC_G3D_JS2_AFFINITY_HI_js2_affinity_hi_START  (0)
#define SOC_G3D_JS2_AFFINITY_HI_js2_affinity_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_CONFIG_UNION
 �ṹ˵��  : JS2_CONFIG �Ĵ����ṹ���塣��ַƫ����:0x1918����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_space : 4;  /* bit[0-3]  : Selects which of the address spaces to use for jobs in
                                                         this slot. The address space configuration values are
                                                         read from the ASn registers. */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : Reserved, write as zero, read undefined. */
        unsigned int  start_flush   : 2;  /* bit[8-9]  : Cache flush action on job chain start. Specifies what
                                                         action the caches must take before starting the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches except the tiler
                                                         cache. */
        unsigned int  start_mmu     : 1;  /* bit[10]   : MMU action on job chain start. Causes the Job Manager
                                                         to issue an MMU update before the job chain is started. */
        unsigned int  reserved_1    : 1;  /* bit[11]   : Reserved, write as zero, read undefined. */
        unsigned int  end_flush     : 2;  /* bit[12-13]: Cache flush action on job end chain. Specifies what
                                                         action the caches must take after finishing the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches including the
                                                         tiler cache. */
        unsigned int  reserved_2    : 18; /* bit[14-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_JS2_CONFIG_UNION;
#endif
#define SOC_G3D_JS2_CONFIG_address_space_START  (0)
#define SOC_G3D_JS2_CONFIG_address_space_END    (3)
#define SOC_G3D_JS2_CONFIG_start_flush_START    (8)
#define SOC_G3D_JS2_CONFIG_start_flush_END      (9)
#define SOC_G3D_JS2_CONFIG_start_mmu_START      (10)
#define SOC_G3D_JS2_CONFIG_start_mmu_END        (10)
#define SOC_G3D_JS2_CONFIG_end_flush_START      (12)
#define SOC_G3D_JS2_CONFIG_end_flush_END        (13)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_COMMAND_UNION
 �ṹ˵��  : JS2_COMMAND �Ĵ����ṹ���塣��ַƫ����:0x1920����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_command : 32; /* bit[0-31]: Command for job slot register */
    } reg;
} SOC_G3D_JS2_COMMAND_UNION;
#endif
#define SOC_G3D_JS2_COMMAND_js2_command_START  (0)
#define SOC_G3D_JS2_COMMAND_js2_command_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_STATUS_UNION
 �ṹ˵��  : JS2_STATUS �Ĵ����ṹ���塣��ַƫ����:0x1924����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_status : 32; /* bit[0-31]: Status for job slot register */
    } reg;
} SOC_G3D_JS2_STATUS_UNION;
#endif
#define SOC_G3D_JS2_STATUS_js2_status_START  (0)
#define SOC_G3D_JS2_STATUS_js2_status_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_HEAD_NEXT_LO_UNION
 �ṹ˵��  : JS2_HEAD_NEXT_LO �Ĵ����ṹ���塣��ַƫ����:0x1940����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_head_next_lo : 32; /* bit[0-31]: Next job queue head pointer for job slot register */
    } reg;
} SOC_G3D_JS2_HEAD_NEXT_LO_UNION;
#endif
#define SOC_G3D_JS2_HEAD_NEXT_LO_js2_head_next_lo_START  (0)
#define SOC_G3D_JS2_HEAD_NEXT_LO_js2_head_next_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_HEAD_NEXT_HI_UNION
 �ṹ˵��  : JS2_HEAD_NEXT_HI �Ĵ����ṹ���塣��ַƫ����:0x1944����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  js2_head_next_hi : 32; /* bit[0-31]: Next job queue head pointer for job slot register */
    } reg;
} SOC_G3D_JS2_HEAD_NEXT_HI_UNION;
#endif
#define SOC_G3D_JS2_HEAD_NEXT_HI_js2_head_next_hi_START  (0)
#define SOC_G3D_JS2_HEAD_NEXT_HI_js2_head_next_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_AFFINITY_NEXT_LO_UNION
 �ṹ˵��  : JS2_AFFINITY_NEXT_LO �Ĵ����ṹ���塣��ַƫ����:0x1950����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS2_AFFINITY_NEXT_LO_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_AFFINITY_NEXT_HI_UNION
 �ṹ˵��  : JS2_AFFINITY_NEXT_HI �Ĵ����ṹ���塣��ַƫ����:0x1954����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next core affinity mask for job slot register */
    } reg;
} SOC_G3D_JS2_AFFINITY_NEXT_HI_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_CONFIG_NEXT_UNION
 �ṹ˵��  : JS2_CONFIG_NEXT �Ĵ����ṹ���塣��ַƫ����:0x1958����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  address_space : 4;  /* bit[0-3]  : Selects which of the address spaces to use for jobs in
                                                         this slot. The address space configuration values are
                                                         read from the ASn registers. */
        unsigned int  reserved_0    : 4;  /* bit[4-7]  : Reserved, write as zero, read undefined. */
        unsigned int  start_flush   : 2;  /* bit[8-9]  : Cache flush action on job chain start. Specifies what
                                                         action the caches must take before starting the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches except the tiler
                                                         cache. */
        unsigned int  start_mmu     : 1;  /* bit[10]   : MMU action on job chain start. Causes the Job Manager
                                                         to issue an MMU update before the job chain is started. */
        unsigned int  reserved_1    : 1;  /* bit[11]   : Reserved, write as zero, read undefined. */
        unsigned int  end_flush     : 2;  /* bit[12-13]: Cache flush action on job end chain. Specifies what
                                                         action the caches must take after finishing the job chain.
                                                         0 No flush
                                                         1 Clean
                                                         2 Reserved
                                                         3 Clean and invalidate.
                                                         The selected action applies to all caches including the
                                                         tiler cache. */
        unsigned int  reserved_2    : 18; /* bit[14-31]: Next configuration setting for job slot register
                                                         The JSn_CONFIG_NEXT register is an identical register used to construct job chains one ahead
                                                         so maintaining throughput. The values in the register are loaded into the JSn_CONFIG register
                                                         when the current job chain completes */
    } reg;
} SOC_G3D_JS2_CONFIG_NEXT_UNION;
#endif
#define SOC_G3D_JS2_CONFIG_NEXT_address_space_START  (0)
#define SOC_G3D_JS2_CONFIG_NEXT_address_space_END    (3)
#define SOC_G3D_JS2_CONFIG_NEXT_start_flush_START    (8)
#define SOC_G3D_JS2_CONFIG_NEXT_start_flush_END      (9)
#define SOC_G3D_JS2_CONFIG_NEXT_start_mmu_START      (10)
#define SOC_G3D_JS2_CONFIG_NEXT_start_mmu_END        (10)
#define SOC_G3D_JS2_CONFIG_NEXT_end_flush_START      (12)
#define SOC_G3D_JS2_CONFIG_NEXT_end_flush_END        (13)


/*****************************************************************************
 �ṹ��    : SOC_G3D_JS2_COMMAND_NEXT_UNION
 �ṹ˵��  : JS2_COMMAND_NEXT �Ĵ����ṹ���塣��ַƫ����:0x1960����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: Next command for job slot register */
    } reg;
} SOC_G3D_JS2_COMMAND_NEXT_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_G3D_MMU_IRQ_RAWSTAT_UNION
 �ṹ˵��  : MMU_IRQ_RAWSTAT �Ĵ����ṹ���塣��ַƫ����:0x2000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  page_fault : 4;  /* bit[0-3]  : Page error for job slot n. */
        unsigned int  reserved_0 : 12; /* bit[4-15] : Reserved, write as zero, read undefined. */
        unsigned int  bus_error  : 4;  /* bit[16-19]: Bus error when reading page tables. */
        unsigned int  reserved_1 : 12; /* bit[20-31]: Raw interrupt status register:Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_MMU_IRQ_RAWSTAT_UNION;
#endif
#define SOC_G3D_MMU_IRQ_RAWSTAT_page_fault_START  (0)
#define SOC_G3D_MMU_IRQ_RAWSTAT_page_fault_END    (3)
#define SOC_G3D_MMU_IRQ_RAWSTAT_bus_error_START   (16)
#define SOC_G3D_MMU_IRQ_RAWSTAT_bus_error_END     (19)


/*****************************************************************************
 �ṹ��    : SOC_G3D_MMU_IRQ_CLEAR_UNION
 �ṹ˵��  : MMU_IRQ_CLEAR �Ĵ����ṹ���塣��ַƫ����:0x2004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  page_fault : 4;  /* bit[0-3]  : Writing a 1 to this register bit enables the
                                                      corresponding interrupt source. Writing a 0 to this
                                                      register bit disables the corresponding interrupt source. */
        unsigned int  reserved_0 : 12; /* bit[4-15] : Reserved, write as zero, read undefined */
        unsigned int  bus_error  : 4;  /* bit[16-19]: Writing a 1 to this register bit enables the
                                                      corresponding interrupt source. Writing a 0 to this
                                                      register bit disables the corresponding interrupt source. */
        unsigned int  reserved_1 : 12; /* bit[20-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_MMU_IRQ_CLEAR_UNION;
#endif
#define SOC_G3D_MMU_IRQ_CLEAR_page_fault_START  (0)
#define SOC_G3D_MMU_IRQ_CLEAR_page_fault_END    (3)
#define SOC_G3D_MMU_IRQ_CLEAR_bus_error_START   (16)
#define SOC_G3D_MMU_IRQ_CLEAR_bus_error_END     (19)


/*****************************************************************************
 �ṹ��    : SOC_G3D_MMU_IRQ_MASK_UNION
 �ṹ˵��  : MMU_IRQ_MASK �Ĵ����ṹ���塣��ַƫ����:0x2008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  page_fault            : 8;  /* bit[0-7]  : Writing a 1 to this register bit enables the
                                                                 corresponding interrupt source. Writing a 0 to this
                                                                 register bit disables the corresponding interrupt source. */
        unsigned int  reserved              : 8;  /* bit[8-15] : reserved */
        unsigned int  bus_error             : 8;  /* bit[16-23]: Writing a 1 to this register bit enables the
                                                                 corresponding interrupt source. Writing a 0 to this
                                                                 register bit disables the corresponding interrupt source. */
        unsigned int  interruptmaskregister : 8;  /* bit[24-31]: interruptmaskregister */
    } reg;
} SOC_G3D_MMU_IRQ_MASK_UNION;
#endif
#define SOC_G3D_MMU_IRQ_MASK_page_fault_START             (0)
#define SOC_G3D_MMU_IRQ_MASK_page_fault_END               (7)
#define SOC_G3D_MMU_IRQ_MASK_bus_error_START              (16)
#define SOC_G3D_MMU_IRQ_MASK_bus_error_END                (23)
#define SOC_G3D_MMU_IRQ_MASK_interruptmaskregister_START  (24)
#define SOC_G3D_MMU_IRQ_MASK_interruptmaskregister_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_MMU_IRQ_STATUS_UNION
 �ṹ˵��  : MMU_IRQ_STATUS �Ĵ����ṹ���塣��ַƫ����:0x200C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  page_fault     : 8;  /* bit[0-7]  : Writing a 1 to this register bit enables the
                                                          corresponding interrupt source. Writing a 0 to this
                                                          register bit disables the corresponding interrupt source. */
        unsigned int  reserved       : 8;  /* bit[8-15] : Reserved, write as zero, read undefined */
        unsigned int  bus_error      : 8;  /* bit[16-23]: Writing a 1 to this register bit enables the
                                                          corresponding interrupt source. Writing a 0 to this
                                                          register bit disables the corresponding interrupt source. */
        unsigned int  mmu_irq_status : 8;  /* bit[24-31]: Interrupt mask status register:Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_MMU_IRQ_STATUS_UNION;
#endif
#define SOC_G3D_MMU_IRQ_STATUS_page_fault_START      (0)
#define SOC_G3D_MMU_IRQ_STATUS_page_fault_END        (7)
#define SOC_G3D_MMU_IRQ_STATUS_bus_error_START       (16)
#define SOC_G3D_MMU_IRQ_STATUS_bus_error_END         (23)
#define SOC_G3D_MMU_IRQ_STATUS_mmu_irq_status_START  (24)
#define SOC_G3D_MMU_IRQ_STATUS_mmu_irq_status_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS0_TRANSTAB_LO_UNION
 �ṹ˵��  : AS0_TRANSTAB_LO �Ĵ����ṹ���塣��ַƫ����:0x2400����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  transtab_adrmode    : 2;  /* bit[0-1]  : Address space mode can have the values shown in this
                                                               field. */
        unsigned int  transtab_read_inner : 1;  /* bit[2]    : Read allocation flag for inner coherence domain.
                                                               Sets the cache policy when reading items from the
                                                               translation table, for the inner coherence domain.
                                                               0 Do not allocate
                                                               1 Allocate */
        unsigned int  reserved_0          : 1;  /* bit[3]    : Reserved, write as zero, read undefined */
        unsigned int  share_out           : 1;  /* bit[4]    : Set the cache coherency policy when reading items
                                                               from the translation table. Indicates if accesses to the
                                                               outer coherency domain should be treated as shareable
                                                               or not.
                                                               1 Access is shareable
                                                               0 Access is not shareable */
        unsigned int  reserved_1          : 7;  /* bit[5-11] : Reserved, write as zero, read undefined */
        unsigned int  as0_transtab_lo     : 20; /* bit[12-31]: Translation table base address. The unused high bits
                                                               must be zero. */
    } reg;
} SOC_G3D_AS0_TRANSTAB_LO_UNION;
#endif
#define SOC_G3D_AS0_TRANSTAB_LO_transtab_adrmode_START     (0)
#define SOC_G3D_AS0_TRANSTAB_LO_transtab_adrmode_END       (1)
#define SOC_G3D_AS0_TRANSTAB_LO_transtab_read_inner_START  (2)
#define SOC_G3D_AS0_TRANSTAB_LO_transtab_read_inner_END    (2)
#define SOC_G3D_AS0_TRANSTAB_LO_share_out_START            (4)
#define SOC_G3D_AS0_TRANSTAB_LO_share_out_END              (4)
#define SOC_G3D_AS0_TRANSTAB_LO_as0_transtab_lo_START      (12)
#define SOC_G3D_AS0_TRANSTAB_LO_as0_transtab_lo_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS0_TRANSTAB_HI_UNION
 �ṹ˵��  : AS0_TRANSTAB_HI �Ĵ����ṹ���塣��ַƫ����:0x2404����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as0_transtab_hi : 8;  /* bit[0-7] : Translation table base address. The unused high bits
                                                          must be zero. */
        unsigned int  reserved        : 24; /* bit[8-31]: Translation table base address registers */
    } reg;
} SOC_G3D_AS0_TRANSTAB_HI_UNION;
#endif
#define SOC_G3D_AS0_TRANSTAB_HI_as0_transtab_hi_START  (0)
#define SOC_G3D_AS0_TRANSTAB_HI_as0_transtab_hi_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS0_MEMATTR_LO_UNION
 �ṹ˵��  : AS0_MEMATTR_LO �Ĵ����ṹ���塣��ַƫ����:0x2408����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as0_memattr_l3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 0 */
        unsigned int  as0_memattr_l2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 1 */
        unsigned int  as0_memattr_l1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 2 */
        unsigned int  as0_memattr_l0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 3 */
    } reg;
} SOC_G3D_AS0_MEMATTR_LO_UNION;
#endif
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l3_START  (0)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l3_END    (7)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l2_START  (8)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l2_END    (15)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l1_START  (16)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l1_END    (23)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l0_START  (24)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS0_MEMATTR_HI_UNION
 �ṹ˵��  : AS0_MEMATTR_HI �Ĵ����ṹ���塣��ַƫ����:0x240C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as0_memattr_h3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 4 */
        unsigned int  as0_memattr_h2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 5 */
        unsigned int  as0_memattr_h1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 6 */
        unsigned int  as0_memattr_h0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 7 */
    } reg;
} SOC_G3D_AS0_MEMATTR_HI_UNION;
#endif
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h3_START  (0)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h3_END    (7)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h2_START  (8)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h2_END    (15)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h1_START  (16)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h1_END    (23)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h0_START  (24)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS0_LOCKADDR_LO_UNION
 �ṹ˵��  : AS0_LOCKADDR_LO �Ĵ����ṹ���塣��ַƫ����:0x2410����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lockaddr_size   : 6;  /* bit[0-5]  : Locked region size.
                                                           The region size field contains the log2 of the size of the
                                                           region to lock, minus 1. Only values in the range 11 to
                                                           63 are valid region sizes. Values in the range 0 to 10 are
                                                           undefined and must not be used. */
        unsigned int  reserved        : 6;  /* bit[6-11] : Reserved, write as zero, read undefined. */
        unsigned int  as0_lockaddr_l0 : 20; /* bit[12-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS0_LOCKADDR_LO_UNION;
#endif
#define SOC_G3D_AS0_LOCKADDR_LO_lockaddr_size_START    (0)
#define SOC_G3D_AS0_LOCKADDR_LO_lockaddr_size_END      (5)
#define SOC_G3D_AS0_LOCKADDR_LO_as0_lockaddr_l0_START  (12)
#define SOC_G3D_AS0_LOCKADDR_LO_as0_lockaddr_l0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS0_LOCKADDR_HI_UNION
 �ṹ˵��  : AS0_LOCKADDR_HI �Ĵ����ṹ���塣��ַƫ����:0x2414����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as0_lockaddr_hi : 16; /* bit[0-15] : The base address field contains the lowest address in the
                                                           region to be locked. The address is a virtual address in
                                                           this address space. Only the upper bits of the address are
                                                           used. */
        unsigned int  reserved        : 16; /* bit[16-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS0_LOCKADDR_HI_UNION;
#endif
#define SOC_G3D_AS0_LOCKADDR_HI_as0_lockaddr_hi_START  (0)
#define SOC_G3D_AS0_LOCKADDR_HI_as0_lockaddr_hi_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS0_COMMAND_UNION
 �ṹ˵��  : AS0_COMMAND �Ĵ����ṹ���塣��ַƫ����:0x2418����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nop       : 1;  /* bit[0]   : No operation, nothing happens */
        unsigned int  update    : 1;  /* bit[1]   : Broadcast the values in ASn_TRANSTAB and
                                                    ASn_MEMATTR to all MMUs.
                                                    Use this after changing the content of these registers.
                                                    This also reverts the effect of a LOCK set in the updated
                                                    address space. */
        unsigned int  lock      : 1;  /* bit[2]   : Issue a lock region command to all MMUs, using the
                                                    address and size set in the ASn_LOCKADDR register.
                                                    Use this before changing an in-memory page table.
                                                    Use a FLUSH command to unlock a memory region. */
        unsigned int  unlock    : 1;  /* bit[3]   : Issue an unlock region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_pt  : 1;  /* bit[4]   : First flush all Level 2 caches.
                                                    Then issue a flush region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region also reverts the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_mem : 1;  /* bit[5]   : Wait until all memory accesses to a region locked by a
                                                    preceding LOCK command have completed and have
                                                    reached the nearest cache.
                                                    Flush the L1 cache in all shader cores forcing dirty data
                                                    for locked regions to be pushed out to the L2 cache.
                                                    Then flush all L2 caches forcing all dirty data for locked
                                                    regions to be written back to memory and page tables to
                                                    be invalidated.
                                                    Then issue an unlock region command to all MMUs,
                                                    using the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing or removing entries in
                                                    an in-memory page table. */
        unsigned int  reserved  : 26; /* bit[6-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_AS0_COMMAND_UNION;
#endif
#define SOC_G3D_AS0_COMMAND_nop_START        (0)
#define SOC_G3D_AS0_COMMAND_nop_END          (0)
#define SOC_G3D_AS0_COMMAND_update_START     (1)
#define SOC_G3D_AS0_COMMAND_update_END       (1)
#define SOC_G3D_AS0_COMMAND_lock_START       (2)
#define SOC_G3D_AS0_COMMAND_lock_END         (2)
#define SOC_G3D_AS0_COMMAND_unlock_START     (3)
#define SOC_G3D_AS0_COMMAND_unlock_END       (3)
#define SOC_G3D_AS0_COMMAND_flush_pt_START   (4)
#define SOC_G3D_AS0_COMMAND_flush_pt_END     (4)
#define SOC_G3D_AS0_COMMAND_flush_mem_START  (5)
#define SOC_G3D_AS0_COMMAND_flush_mem_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS0_FAULTSTATUS_UNION
 �ṹ˵��  : AS0_FAULTSTATUS �Ĵ����ṹ���塣��ַƫ����:0x241C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exception_type : 8;  /* bit[0-7]  : Type of exception that caused the fault. */
        unsigned int  access_type    : 2;  /* bit[8-9]  : Access type that triggered the fault */
        unsigned int  reserved       : 6;  /* bit[10-15]: Reserved, write as zero, read undefined. */
        unsigned int  source_id      : 16; /* bit[16-31]: ID of source that triggered the fault */
    } reg;
} SOC_G3D_AS0_FAULTSTATUS_UNION;
#endif
#define SOC_G3D_AS0_FAULTSTATUS_exception_type_START  (0)
#define SOC_G3D_AS0_FAULTSTATUS_exception_type_END    (7)
#define SOC_G3D_AS0_FAULTSTATUS_access_type_START     (8)
#define SOC_G3D_AS0_FAULTSTATUS_access_type_END       (9)
#define SOC_G3D_AS0_FAULTSTATUS_source_id_START       (16)
#define SOC_G3D_AS0_FAULTSTATUS_source_id_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS0_FAULTADDRESS_LO_UNION
 �ṹ˵��  : AS0_FAULTADDRESS_LO �Ĵ����ṹ���塣��ַƫ����:0x2420����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as0_faultaddress_lo : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS0_FAULTADDRESS_LO_UNION;
#endif
#define SOC_G3D_AS0_FAULTADDRESS_LO_as0_faultaddress_lo_START  (0)
#define SOC_G3D_AS0_FAULTADDRESS_LO_as0_faultaddress_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS0_FAULTADDRESS_HI_UNION
 �ṹ˵��  : AS0_FAULTADDRESS_HI �Ĵ����ṹ���塣��ַƫ����:0x2424����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as0_faultaddress_hi : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS0_FAULTADDRESS_HI_UNION;
#endif
#define SOC_G3D_AS0_FAULTADDRESS_HI_as0_faultaddress_hi_START  (0)
#define SOC_G3D_AS0_FAULTADDRESS_HI_as0_faultaddress_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS0_STATUS_UNION
 �ṹ˵��  : AS0_STATUS �Ĵ����ṹ���塣��ַƫ����:0x2428����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mmu_flush_active : 1;  /* bit[0]   : MMU flush command is active */
        unsigned int  reserved         : 31; /* bit[1-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_AS0_STATUS_UNION;
#endif
#define SOC_G3D_AS0_STATUS_mmu_flush_active_START  (0)
#define SOC_G3D_AS0_STATUS_mmu_flush_active_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS1_TRANSTAB_LO_UNION
 �ṹ˵��  : AS1_TRANSTAB_LO �Ĵ����ṹ���塣��ַƫ����:0x2440����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  transtab_adrmode    : 2;  /* bit[0-1]  : Address space mode can have the values shown in this
                                                               field. */
        unsigned int  transtab_read_inner : 1;  /* bit[2]    : Read allocation flag for inner coherence domain.
                                                               Sets the cache policy when reading items from the
                                                               translation table, for the inner coherence domain.
                                                               0 Do not allocate
                                                               1 Allocate */
        unsigned int  reserved_0          : 1;  /* bit[3]    : Reserved, write as zero, read undefined */
        unsigned int  share_out           : 1;  /* bit[4]    : Set the cache coherency policy when reading items
                                                               from the translation table. Indicates if accesses to the
                                                               outer coherency domain should be treated as shareable
                                                               or not.
                                                               1 Access is shareable
                                                               0 Access is not shareable */
        unsigned int  reserved_1          : 7;  /* bit[5-11] : Reserved, write as zero, read undefined */
        unsigned int  as1_transtab_lo     : 20; /* bit[12-31]: Translation table base address. The unused high bits
                                                               must be zero. */
    } reg;
} SOC_G3D_AS1_TRANSTAB_LO_UNION;
#endif
#define SOC_G3D_AS1_TRANSTAB_LO_transtab_adrmode_START     (0)
#define SOC_G3D_AS1_TRANSTAB_LO_transtab_adrmode_END       (1)
#define SOC_G3D_AS1_TRANSTAB_LO_transtab_read_inner_START  (2)
#define SOC_G3D_AS1_TRANSTAB_LO_transtab_read_inner_END    (2)
#define SOC_G3D_AS1_TRANSTAB_LO_share_out_START            (4)
#define SOC_G3D_AS1_TRANSTAB_LO_share_out_END              (4)
#define SOC_G3D_AS1_TRANSTAB_LO_as1_transtab_lo_START      (12)
#define SOC_G3D_AS1_TRANSTAB_LO_as1_transtab_lo_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS1_TRANSTAB_HI_UNION
 �ṹ˵��  : AS1_TRANSTAB_HI �Ĵ����ṹ���塣��ַƫ����:0x2444����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as1_transtab_hi : 8;  /* bit[0-7] : Translation table base address. The unused high bits
                                                          must be zero. */
        unsigned int  reserved        : 24; /* bit[8-31]: Translation table base address registers */
    } reg;
} SOC_G3D_AS1_TRANSTAB_HI_UNION;
#endif
#define SOC_G3D_AS1_TRANSTAB_HI_as1_transtab_hi_START  (0)
#define SOC_G3D_AS1_TRANSTAB_HI_as1_transtab_hi_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS1_MEMATTR_LO_UNION
 �ṹ˵��  : AS1_MEMATTR_LO �Ĵ����ṹ���塣��ַƫ����:0x2448����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as1_memattr_l3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 0 */
        unsigned int  as1_memattr_l2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 1 */
        unsigned int  as1_memattr_l1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 2 */
        unsigned int  as1_memattr_l0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 3 */
    } reg;
} SOC_G3D_AS1_MEMATTR_LO_UNION;
#endif
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l3_START  (0)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l3_END    (7)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l2_START  (8)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l2_END    (15)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l1_START  (16)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l1_END    (23)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l0_START  (24)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS1_MEMATTR_HI_UNION
 �ṹ˵��  : AS1_MEMATTR_HI �Ĵ����ṹ���塣��ַƫ����:0x244C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as1_memattr_h3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 4 */
        unsigned int  as1_memattr_h2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 5 */
        unsigned int  as1_memattr_h1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 6 */
        unsigned int  as1_memattr_h0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 7 */
    } reg;
} SOC_G3D_AS1_MEMATTR_HI_UNION;
#endif
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h3_START  (0)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h3_END    (7)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h2_START  (8)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h2_END    (15)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h1_START  (16)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h1_END    (23)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h0_START  (24)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS1_LOCKADDR_LO_UNION
 �ṹ˵��  : AS1_LOCKADDR_LO �Ĵ����ṹ���塣��ַƫ����:0x2450����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lockaddr_size   : 6;  /* bit[0-5]  : Locked region size.
                                                           The region size field contains the log2 of the size of the
                                                           region to lock, minus 1. Only values in the range 11 to
                                                           63 are valid region sizes. Values in the range 0 to 10 are
                                                           undefined and must not be used. */
        unsigned int  reserved        : 6;  /* bit[6-11] : Reserved, write as zero, read undefined. */
        unsigned int  as1_lockaddr_l0 : 20; /* bit[12-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS1_LOCKADDR_LO_UNION;
#endif
#define SOC_G3D_AS1_LOCKADDR_LO_lockaddr_size_START    (0)
#define SOC_G3D_AS1_LOCKADDR_LO_lockaddr_size_END      (5)
#define SOC_G3D_AS1_LOCKADDR_LO_as1_lockaddr_l0_START  (12)
#define SOC_G3D_AS1_LOCKADDR_LO_as1_lockaddr_l0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS1_LOCKADDR_HI_UNION
 �ṹ˵��  : AS1_LOCKADDR_HI �Ĵ����ṹ���塣��ַƫ����:0x2454����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as1_lockaddr_hi : 16; /* bit[0-15] : The base address field contains the lowest address in the
                                                           region to be locked. The address is a virtual address in
                                                           this address space. Only the upper bits of the address are
                                                           used. */
        unsigned int  reserved        : 16; /* bit[16-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS1_LOCKADDR_HI_UNION;
#endif
#define SOC_G3D_AS1_LOCKADDR_HI_as1_lockaddr_hi_START  (0)
#define SOC_G3D_AS1_LOCKADDR_HI_as1_lockaddr_hi_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS1_COMMAND_UNION
 �ṹ˵��  : AS1_COMMAND �Ĵ����ṹ���塣��ַƫ����:0x2458����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nop       : 1;  /* bit[0]   : No operation, nothing happens */
        unsigned int  update    : 1;  /* bit[1]   : Broadcast the values in ASn_TRANSTAB and
                                                    ASn_MEMATTR to all MMUs.
                                                    Use this after changing the content of these registers.
                                                    This also reverts the effect of a LOCK set in the updated
                                                    address space. */
        unsigned int  lock      : 1;  /* bit[2]   : Issue a lock region command to all MMUs, using the
                                                    address and size set in the ASn_LOCKADDR register.
                                                    Use this before changing an in-memory page table.
                                                    Use a FLUSH command to unlock a memory region. */
        unsigned int  unlock    : 1;  /* bit[3]   : Issue an unlock region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_pt  : 1;  /* bit[4]   : First flush all Level 2 caches.
                                                    Then issue a flush region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region also reverts the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_mem : 1;  /* bit[5]   : Wait until all memory accesses to a region locked by a
                                                    preceding LOCK command have completed and have
                                                    reached the nearest cache.
                                                    Flush the L1 cache in all shader cores forcing dirty data
                                                    for locked regions to be pushed out to the L2 cache.
                                                    Then flush all L2 caches forcing all dirty data for locked
                                                    regions to be written back to memory and page tables to
                                                    be invalidated.
                                                    Then issue an unlock region command to all MMUs,
                                                    using the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing or removing entries in
                                                    an in-memory page table. */
        unsigned int  reserved  : 26; /* bit[6-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_AS1_COMMAND_UNION;
#endif
#define SOC_G3D_AS1_COMMAND_nop_START        (0)
#define SOC_G3D_AS1_COMMAND_nop_END          (0)
#define SOC_G3D_AS1_COMMAND_update_START     (1)
#define SOC_G3D_AS1_COMMAND_update_END       (1)
#define SOC_G3D_AS1_COMMAND_lock_START       (2)
#define SOC_G3D_AS1_COMMAND_lock_END         (2)
#define SOC_G3D_AS1_COMMAND_unlock_START     (3)
#define SOC_G3D_AS1_COMMAND_unlock_END       (3)
#define SOC_G3D_AS1_COMMAND_flush_pt_START   (4)
#define SOC_G3D_AS1_COMMAND_flush_pt_END     (4)
#define SOC_G3D_AS1_COMMAND_flush_mem_START  (5)
#define SOC_G3D_AS1_COMMAND_flush_mem_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS1_FAULTSTATUS_UNION
 �ṹ˵��  : AS1_FAULTSTATUS �Ĵ����ṹ���塣��ַƫ����:0x245C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exception_type : 8;  /* bit[0-7]  : Type of exception that caused the fault. */
        unsigned int  access_type    : 2;  /* bit[8-9]  : Access type that triggered the fault */
        unsigned int  reserved       : 6;  /* bit[10-15]: Reserved, write as zero, read undefined. */
        unsigned int  source_id      : 16; /* bit[16-31]: ID of source that triggered the fault */
    } reg;
} SOC_G3D_AS1_FAULTSTATUS_UNION;
#endif
#define SOC_G3D_AS1_FAULTSTATUS_exception_type_START  (0)
#define SOC_G3D_AS1_FAULTSTATUS_exception_type_END    (7)
#define SOC_G3D_AS1_FAULTSTATUS_access_type_START     (8)
#define SOC_G3D_AS1_FAULTSTATUS_access_type_END       (9)
#define SOC_G3D_AS1_FAULTSTATUS_source_id_START       (16)
#define SOC_G3D_AS1_FAULTSTATUS_source_id_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS1_FAULTADDRESS_LO_UNION
 �ṹ˵��  : AS1_FAULTADDRESS_LO �Ĵ����ṹ���塣��ַƫ����:0x2460����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as1_faultaddress_lo : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS1_FAULTADDRESS_LO_UNION;
#endif
#define SOC_G3D_AS1_FAULTADDRESS_LO_as1_faultaddress_lo_START  (0)
#define SOC_G3D_AS1_FAULTADDRESS_LO_as1_faultaddress_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS1_FAULTADDRESS_HI_UNION
 �ṹ˵��  : AS1_FAULTADDRESS_HI �Ĵ����ṹ���塣��ַƫ����:0x2464����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as0_faultaddress_hi : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS1_FAULTADDRESS_HI_UNION;
#endif
#define SOC_G3D_AS1_FAULTADDRESS_HI_as0_faultaddress_hi_START  (0)
#define SOC_G3D_AS1_FAULTADDRESS_HI_as0_faultaddress_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS1_STATUS_UNION
 �ṹ˵��  : AS1_STATUS �Ĵ����ṹ���塣��ַƫ����:0x2468����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mmu_flush_active : 1;  /* bit[0]   : MMU flush command is active
                                                           1:active
                                                           0:not active */
        unsigned int  reserved         : 31; /* bit[1-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_AS1_STATUS_UNION;
#endif
#define SOC_G3D_AS1_STATUS_mmu_flush_active_START  (0)
#define SOC_G3D_AS1_STATUS_mmu_flush_active_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS2_TRANSTAB_LO_UNION
 �ṹ˵��  : AS2_TRANSTAB_LO �Ĵ����ṹ���塣��ַƫ����:0x2480����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  transtab_adrmode    : 2;  /* bit[0-1]  : Address space mode can have the values shown in this
                                                               field. */
        unsigned int  transtab_read_inner : 1;  /* bit[2]    : Read allocation flag for inner coherence domain.
                                                               Sets the cache policy when reading items from the
                                                               translation table, for the inner coherence domain.
                                                               0 Do not allocate
                                                               1 Allocate */
        unsigned int  reserved_0          : 1;  /* bit[3]    : Reserved, write as zero, read undefined */
        unsigned int  share_out           : 1;  /* bit[4]    : Set the cache coherency policy when reading items
                                                               from the translation table. Indicates if accesses to the
                                                               outer coherency domain should be treated as shareable
                                                               or not.
                                                               1 Access is shareable
                                                               0 Access is not shareable */
        unsigned int  reserved_1          : 7;  /* bit[5-11] : Reserved, write as zero, read undefined */
        unsigned int  as2_transtab_lo     : 20; /* bit[12-31]: Translation table base address. The unused high bits
                                                               must be zero. */
    } reg;
} SOC_G3D_AS2_TRANSTAB_LO_UNION;
#endif
#define SOC_G3D_AS2_TRANSTAB_LO_transtab_adrmode_START     (0)
#define SOC_G3D_AS2_TRANSTAB_LO_transtab_adrmode_END       (1)
#define SOC_G3D_AS2_TRANSTAB_LO_transtab_read_inner_START  (2)
#define SOC_G3D_AS2_TRANSTAB_LO_transtab_read_inner_END    (2)
#define SOC_G3D_AS2_TRANSTAB_LO_share_out_START            (4)
#define SOC_G3D_AS2_TRANSTAB_LO_share_out_END              (4)
#define SOC_G3D_AS2_TRANSTAB_LO_as2_transtab_lo_START      (12)
#define SOC_G3D_AS2_TRANSTAB_LO_as2_transtab_lo_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS2_TRANSTAB_HI_UNION
 �ṹ˵��  : AS2_TRANSTAB_HI �Ĵ����ṹ���塣��ַƫ����:0x2484����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as2_transtab_hi : 8;  /* bit[0-7] : Translation table base address. The unused high bits
                                                          must be zero. */
        unsigned int  reserved        : 24; /* bit[8-31]: Translation table base address registers */
    } reg;
} SOC_G3D_AS2_TRANSTAB_HI_UNION;
#endif
#define SOC_G3D_AS2_TRANSTAB_HI_as2_transtab_hi_START  (0)
#define SOC_G3D_AS2_TRANSTAB_HI_as2_transtab_hi_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS2_MEMATTR_LO_UNION
 �ṹ˵��  : AS2_MEMATTR_LO �Ĵ����ṹ���塣��ַƫ����:0x2488����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as2_memattr_l3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 0 */
        unsigned int  as2_memattr_l2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 1 */
        unsigned int  as2_memattr_l1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 2 */
        unsigned int  as2_memattr_l0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 3 */
    } reg;
} SOC_G3D_AS2_MEMATTR_LO_UNION;
#endif
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l3_START  (0)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l3_END    (7)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l2_START  (8)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l2_END    (15)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l1_START  (16)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l1_END    (23)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l0_START  (24)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS2_MEMATTR_HI_UNION
 �ṹ˵��  : AS2_MEMATTR_HI �Ĵ����ṹ���塣��ַƫ����:0x248C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as2_memattr_h3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 4 */
        unsigned int  as2_memattr_h2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 5 */
        unsigned int  as2_memattr_h1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 6 */
        unsigned int  as2_memattr_h0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 7 */
    } reg;
} SOC_G3D_AS2_MEMATTR_HI_UNION;
#endif
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h3_START  (0)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h3_END    (7)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h2_START  (8)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h2_END    (15)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h1_START  (16)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h1_END    (23)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h0_START  (24)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS2_LOCKADDR_LO_UNION
 �ṹ˵��  : AS2_LOCKADDR_LO �Ĵ����ṹ���塣��ַƫ����:0x2490����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lockaddr_size   : 6;  /* bit[0-5]  : Locked region size.
                                                           The region size field contains the log2 of the size of the
                                                           region to lock, minus 1. Only values in the range 11 to
                                                           63 are valid region sizes. Values in the range 0 to 10 are
                                                           undefined and must not be used. */
        unsigned int  reserved        : 6;  /* bit[6-11] : Reserved, write as zero, read undefined. */
        unsigned int  as2_lockaddr_l0 : 20; /* bit[12-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS2_LOCKADDR_LO_UNION;
#endif
#define SOC_G3D_AS2_LOCKADDR_LO_lockaddr_size_START    (0)
#define SOC_G3D_AS2_LOCKADDR_LO_lockaddr_size_END      (5)
#define SOC_G3D_AS2_LOCKADDR_LO_as2_lockaddr_l0_START  (12)
#define SOC_G3D_AS2_LOCKADDR_LO_as2_lockaddr_l0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS2_LOCKADDR_HI_UNION
 �ṹ˵��  : AS2_LOCKADDR_HI �Ĵ����ṹ���塣��ַƫ����:0x2494����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as2_lockaddr_hi : 16; /* bit[0-15] : The base address field contains the lowest address in the
                                                           region to be locked. The address is a virtual address in
                                                           this address space. Only the upper bits of the address are
                                                           used. */
        unsigned int  reserved        : 16; /* bit[16-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS2_LOCKADDR_HI_UNION;
#endif
#define SOC_G3D_AS2_LOCKADDR_HI_as2_lockaddr_hi_START  (0)
#define SOC_G3D_AS2_LOCKADDR_HI_as2_lockaddr_hi_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS2_COMMAND_UNION
 �ṹ˵��  : AS2_COMMAND �Ĵ����ṹ���塣��ַƫ����:0x2498����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nop       : 1;  /* bit[0]   : No operation, nothing happens */
        unsigned int  update    : 1;  /* bit[1]   : Broadcast the values in ASn_TRANSTAB and
                                                    ASn_MEMATTR to all MMUs.
                                                    Use this after changing the content of these registers.
                                                    This also reverts the effect of a LOCK set in the updated
                                                    address space. */
        unsigned int  lock      : 1;  /* bit[2]   : Issue a lock region command to all MMUs, using the
                                                    address and size set in the ASn_LOCKADDR register.
                                                    Use this before changing an in-memory page table.
                                                    Use a FLUSH command to unlock a memory region. */
        unsigned int  unlock    : 1;  /* bit[3]   : Issue an unlock region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_pt  : 1;  /* bit[4]   : First flush all Level 2 caches.
                                                    Then issue a flush region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region also reverts the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_mem : 1;  /* bit[5]   : Wait until all memory accesses to a region locked by a
                                                    preceding LOCK command have completed and have
                                                    reached the nearest cache.
                                                    Flush the L1 cache in all shader cores forcing dirty data
                                                    for locked regions to be pushed out to the L2 cache.
                                                    Then flush all L2 caches forcing all dirty data for locked
                                                    regions to be written back to memory and page tables to
                                                    be invalidated.
                                                    Then issue an unlock region command to all MMUs,
                                                    using the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing or removing entries in
                                                    an in-memory page table. */
        unsigned int  reserved  : 26; /* bit[6-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_AS2_COMMAND_UNION;
#endif
#define SOC_G3D_AS2_COMMAND_nop_START        (0)
#define SOC_G3D_AS2_COMMAND_nop_END          (0)
#define SOC_G3D_AS2_COMMAND_update_START     (1)
#define SOC_G3D_AS2_COMMAND_update_END       (1)
#define SOC_G3D_AS2_COMMAND_lock_START       (2)
#define SOC_G3D_AS2_COMMAND_lock_END         (2)
#define SOC_G3D_AS2_COMMAND_unlock_START     (3)
#define SOC_G3D_AS2_COMMAND_unlock_END       (3)
#define SOC_G3D_AS2_COMMAND_flush_pt_START   (4)
#define SOC_G3D_AS2_COMMAND_flush_pt_END     (4)
#define SOC_G3D_AS2_COMMAND_flush_mem_START  (5)
#define SOC_G3D_AS2_COMMAND_flush_mem_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS2_FAULTSTATUS_UNION
 �ṹ˵��  : AS2_FAULTSTATUS �Ĵ����ṹ���塣��ַƫ����:0x249C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exception_type : 8;  /* bit[0-7]  : Type of exception that caused the fault. */
        unsigned int  access_type    : 2;  /* bit[8-9]  : Access type that triggered the fault */
        unsigned int  reserved       : 6;  /* bit[10-15]: Reserved, write as zero, read undefined. */
        unsigned int  source_id      : 16; /* bit[16-31]: ID of source that triggered the fault */
    } reg;
} SOC_G3D_AS2_FAULTSTATUS_UNION;
#endif
#define SOC_G3D_AS2_FAULTSTATUS_exception_type_START  (0)
#define SOC_G3D_AS2_FAULTSTATUS_exception_type_END    (7)
#define SOC_G3D_AS2_FAULTSTATUS_access_type_START     (8)
#define SOC_G3D_AS2_FAULTSTATUS_access_type_END       (9)
#define SOC_G3D_AS2_FAULTSTATUS_source_id_START       (16)
#define SOC_G3D_AS2_FAULTSTATUS_source_id_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS2_FAULTADDRESS_LO_UNION
 �ṹ˵��  : AS2_FAULTADDRESS_LO �Ĵ����ṹ���塣��ַƫ����:0x24A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as2_faultaddress_lo : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS2_FAULTADDRESS_LO_UNION;
#endif
#define SOC_G3D_AS2_FAULTADDRESS_LO_as2_faultaddress_lo_START  (0)
#define SOC_G3D_AS2_FAULTADDRESS_LO_as2_faultaddress_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS2_FAULTADDRESS_HI_UNION
 �ṹ˵��  : AS2_FAULTADDRESS_HI �Ĵ����ṹ���塣��ַƫ����:0x24A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as2_faultaddress_hi : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS2_FAULTADDRESS_HI_UNION;
#endif
#define SOC_G3D_AS2_FAULTADDRESS_HI_as2_faultaddress_hi_START  (0)
#define SOC_G3D_AS2_FAULTADDRESS_HI_as2_faultaddress_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS2_STATUS_UNION
 �ṹ˵��  : AS2_STATUS �Ĵ����ṹ���塣��ַƫ����:0x24A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mmu_flush_active : 1;  /* bit[0]   : MMU flush command is active */
        unsigned int  reserved         : 31; /* bit[1-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_AS2_STATUS_UNION;
#endif
#define SOC_G3D_AS2_STATUS_mmu_flush_active_START  (0)
#define SOC_G3D_AS2_STATUS_mmu_flush_active_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS3_TRANSTAB_LO_UNION
 �ṹ˵��  : AS3_TRANSTAB_LO �Ĵ����ṹ���塣��ַƫ����:0x24C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  transtab_adrmode    : 2;  /* bit[0-1]  : Address space mode can have the values shown in this
                                                               field. */
        unsigned int  transtab_read_inner : 1;  /* bit[2]    : Read allocation flag for inner coherence domain.
                                                               Sets the cache policy when reading items from the
                                                               translation table, for the inner coherence domain.
                                                               0 Do not allocate
                                                               1 Allocate */
        unsigned int  reserved_0          : 1;  /* bit[3]    : Reserved, write as zero, read undefined */
        unsigned int  share_out           : 1;  /* bit[4]    : Set the cache coherency policy when reading items
                                                               from the translation table. Indicates if accesses to the
                                                               outer coherency domain should be treated as shareable
                                                               or not.
                                                               1 Access is shareable
                                                               0 Access is not shareable */
        unsigned int  reserved_1          : 7;  /* bit[5-11] : Reserved, write as zero, read undefined */
        unsigned int  as3_transtab_lo     : 20; /* bit[12-31]: Translation table base address. The unused high bits
                                                               must be zero. */
    } reg;
} SOC_G3D_AS3_TRANSTAB_LO_UNION;
#endif
#define SOC_G3D_AS3_TRANSTAB_LO_transtab_adrmode_START     (0)
#define SOC_G3D_AS3_TRANSTAB_LO_transtab_adrmode_END       (1)
#define SOC_G3D_AS3_TRANSTAB_LO_transtab_read_inner_START  (2)
#define SOC_G3D_AS3_TRANSTAB_LO_transtab_read_inner_END    (2)
#define SOC_G3D_AS3_TRANSTAB_LO_share_out_START            (4)
#define SOC_G3D_AS3_TRANSTAB_LO_share_out_END              (4)
#define SOC_G3D_AS3_TRANSTAB_LO_as3_transtab_lo_START      (12)
#define SOC_G3D_AS3_TRANSTAB_LO_as3_transtab_lo_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS3_TRANSTAB_HI_UNION
 �ṹ˵��  : AS3_TRANSTAB_HI �Ĵ����ṹ���塣��ַƫ����:0x24C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as3_transtab_hi : 8;  /* bit[0-7] : Translation table base address. The unused high bits
                                                          must be zero. */
        unsigned int  reserved        : 24; /* bit[8-31]: Translation table base address registers */
    } reg;
} SOC_G3D_AS3_TRANSTAB_HI_UNION;
#endif
#define SOC_G3D_AS3_TRANSTAB_HI_as3_transtab_hi_START  (0)
#define SOC_G3D_AS3_TRANSTAB_HI_as3_transtab_hi_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS3_MEMATTR_LO_UNION
 �ṹ˵��  : AS3_MEMATTR_LO �Ĵ����ṹ���塣��ַƫ����:0x24C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as3_memattr_l3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 0 */
        unsigned int  as3_memattr_l2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 1 */
        unsigned int  as3_memattr_l1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 2 */
        unsigned int  as3_memattr_l0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 3 */
    } reg;
} SOC_G3D_AS3_MEMATTR_LO_UNION;
#endif
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l3_START  (0)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l3_END    (7)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l2_START  (8)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l2_END    (15)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l1_START  (16)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l1_END    (23)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l0_START  (24)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS3_MEMATTR_HI_UNION
 �ṹ˵��  : AS3_MEMATTR_HI �Ĵ����ṹ���塣��ַƫ����:0x24CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as3_memattr_h3 : 8;  /* bit[0-7]  : Contains ATT attribute values for index 4 */
        unsigned int  as3_memattr_h2 : 8;  /* bit[8-15] : Contains ATT attribute values for index 5 */
        unsigned int  as3_memattr_h1 : 8;  /* bit[16-23]: Contains ATT attribute values for index 6 */
        unsigned int  as3_memattr_h0 : 8;  /* bit[24-31]: Contains ATT attribute values for index 7 */
    } reg;
} SOC_G3D_AS3_MEMATTR_HI_UNION;
#endif
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h3_START  (0)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h3_END    (7)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h2_START  (8)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h2_END    (15)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h1_START  (16)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h1_END    (23)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h0_START  (24)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS3_LOCKADDR_LO_UNION
 �ṹ˵��  : AS3_LOCKADDR_LO �Ĵ����ṹ���塣��ַƫ����:0x24D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lockaddr_size   : 6;  /* bit[0-5]  : Locked region size.
                                                           The region size field contains the log2 of the size of the
                                                           region to lock, minus 1. Only values in the range 11 to
                                                           63 are valid region sizes. Values in the range 0 to 10 are
                                                           undefined and must not be used. */
        unsigned int  reserved        : 6;  /* bit[6-11] : Reserved, write as zero, read undefined. */
        unsigned int  as3_lockaddr_l0 : 20; /* bit[12-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS3_LOCKADDR_LO_UNION;
#endif
#define SOC_G3D_AS3_LOCKADDR_LO_lockaddr_size_START    (0)
#define SOC_G3D_AS3_LOCKADDR_LO_lockaddr_size_END      (5)
#define SOC_G3D_AS3_LOCKADDR_LO_as3_lockaddr_l0_START  (12)
#define SOC_G3D_AS3_LOCKADDR_LO_as3_lockaddr_l0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS3_LOCKADDR_HI_UNION
 �ṹ˵��  : AS3_LOCKADDR_HI �Ĵ����ṹ���塣��ַƫ����:0x24D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as3_lockaddr_hi : 16; /* bit[0-15] : The base address field contains the lowest address in the
                                                           region to be locked. The address is a virtual address in
                                                           this address space. Only the upper bits of the address are
                                                           used. */
        unsigned int  reserved        : 16; /* bit[16-31]: Lock region address for address space registers  */
    } reg;
} SOC_G3D_AS3_LOCKADDR_HI_UNION;
#endif
#define SOC_G3D_AS3_LOCKADDR_HI_as3_lockaddr_hi_START  (0)
#define SOC_G3D_AS3_LOCKADDR_HI_as3_lockaddr_hi_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS3_COMMAND_UNION
 �ṹ˵��  : AS3_COMMAND �Ĵ����ṹ���塣��ַƫ����:0x24D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nop       : 1;  /* bit[0]   : No operation, nothing happens */
        unsigned int  update    : 1;  /* bit[1]   : Broadcast the values in ASn_TRANSTAB and
                                                    ASn_MEMATTR to all MMUs.
                                                    Use this after changing the content of these registers.
                                                    This also reverts the effect of a LOCK set in the updated
                                                    address space. */
        unsigned int  lock      : 1;  /* bit[2]   : Issue a lock region command to all MMUs, using the
                                                    address and size set in the ASn_LOCKADDR register.
                                                    Use this before changing an in-memory page table.
                                                    Use a FLUSH command to unlock a memory region. */
        unsigned int  unlock    : 1;  /* bit[3]   : Issue an unlock region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_pt  : 1;  /* bit[4]   : First flush all Level 2 caches.
                                                    Then issue a flush region command to all MMUs, using
                                                    the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region also reverts the effect of any
                                                    LOCKs.
                                                    Use this when finished changing an in-memory page
                                                    table, except if the page table can be cached in the L2
                                                    cache, in which case, a FLUSH_MEM command must
                                                    be issued instead. */
        unsigned int  flush_mem : 1;  /* bit[5]   : Wait until all memory accesses to a region locked by a
                                                    preceding LOCK command have completed and have
                                                    reached the nearest cache.
                                                    Flush the L1 cache in all shader cores forcing dirty data
                                                    for locked regions to be pushed out to the L2 cache.
                                                    Then flush all L2 caches forcing all dirty data for locked
                                                    regions to be written back to memory and page tables to
                                                    be invalidated.
                                                    Then issue an unlock region command to all MMUs,
                                                    using the address and size set in the ASn_LOCKADDR
                                                    register.
                                                    Unlocking a region will also revert the effect of any
                                                    LOCKs.
                                                    Use this when finished changing or removing entries in
                                                    an in-memory page table. */
        unsigned int  reserved  : 26; /* bit[6-31]: Reserved, write as zero, read undefined. */
    } reg;
} SOC_G3D_AS3_COMMAND_UNION;
#endif
#define SOC_G3D_AS3_COMMAND_nop_START        (0)
#define SOC_G3D_AS3_COMMAND_nop_END          (0)
#define SOC_G3D_AS3_COMMAND_update_START     (1)
#define SOC_G3D_AS3_COMMAND_update_END       (1)
#define SOC_G3D_AS3_COMMAND_lock_START       (2)
#define SOC_G3D_AS3_COMMAND_lock_END         (2)
#define SOC_G3D_AS3_COMMAND_unlock_START     (3)
#define SOC_G3D_AS3_COMMAND_unlock_END       (3)
#define SOC_G3D_AS3_COMMAND_flush_pt_START   (4)
#define SOC_G3D_AS3_COMMAND_flush_pt_END     (4)
#define SOC_G3D_AS3_COMMAND_flush_mem_START  (5)
#define SOC_G3D_AS3_COMMAND_flush_mem_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS3_FAULTSTATUS_UNION
 �ṹ˵��  : AS3_FAULTSTATUS �Ĵ����ṹ���塣��ַƫ����:0x24DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  exception_type : 8;  /* bit[0-7]  : Type of exception that caused the fault. */
        unsigned int  access_type    : 2;  /* bit[8-9]  : Access type that triggered the fault */
        unsigned int  reserved       : 6;  /* bit[10-15]: Reserved, write as zero, read undefined. */
        unsigned int  source_id      : 16; /* bit[16-31]: ID of source that triggered the fault */
    } reg;
} SOC_G3D_AS3_FAULTSTATUS_UNION;
#endif
#define SOC_G3D_AS3_FAULTSTATUS_exception_type_START  (0)
#define SOC_G3D_AS3_FAULTSTATUS_exception_type_END    (7)
#define SOC_G3D_AS3_FAULTSTATUS_access_type_START     (8)
#define SOC_G3D_AS3_FAULTSTATUS_access_type_END       (9)
#define SOC_G3D_AS3_FAULTSTATUS_source_id_START       (16)
#define SOC_G3D_AS3_FAULTSTATUS_source_id_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS3_FAULTADDRESS_LO_UNION
 �ṹ˵��  : AS3_FAULTADDRESS_LO �Ĵ����ṹ���塣��ַƫ����:0x24E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as3_faultaddress_lo : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS3_FAULTADDRESS_LO_UNION;
#endif
#define SOC_G3D_AS3_FAULTADDRESS_LO_as3_faultaddress_lo_START  (0)
#define SOC_G3D_AS3_FAULTADDRESS_LO_as3_faultaddress_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS3_FAULTADDRESS_HI_UNION
 �ṹ˵��  : AS3_FAULTADDRESS_HI �Ĵ����ṹ���塣��ַƫ����:0x24E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  as3_faultaddress_hi : 32; /* bit[0-31]: Fault address for address space registers  */
    } reg;
} SOC_G3D_AS3_FAULTADDRESS_HI_UNION;
#endif
#define SOC_G3D_AS3_FAULTADDRESS_HI_as3_faultaddress_hi_START  (0)
#define SOC_G3D_AS3_FAULTADDRESS_HI_as3_faultaddress_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_G3D_AS3_STATUS_UNION
 �ṹ˵��  : AS3_STATUS �Ĵ����ṹ���塣��ַƫ����:0x24E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mmu_flush_active : 1;  /* bit[0]   : MMU flush command is active
                                                           1:active
                                                           0:not active */
        unsigned int  reserved         : 31; /* bit[1-31]: Reserved, write as zero, read undefined */
    } reg;
} SOC_G3D_AS3_STATUS_UNION;
#endif
#define SOC_G3D_AS3_STATUS_mmu_flush_active_START  (0)
#define SOC_G3D_AS3_STATUS_mmu_flush_active_END    (0)






/*****************************************************************************
  8 OTHERS����
*****************************************************************************/



/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of soc_g3d_interface.h */
