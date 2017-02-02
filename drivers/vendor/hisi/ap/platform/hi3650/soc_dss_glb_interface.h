/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_glb_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:06
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_GLB.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_GLB_INTERFACE_H__
#define __SOC_DSS_GLB_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_GLB
 ****************************************************************************/
/* �Ĵ���˵����dss�汾��
   λ����UNION�ṹ:  SOC_DSS_GLB_DSS_TAG_UNION */
#define SOC_DSS_GLB_DSS_TAG_ADDR(base)                ((base) + (0x0000))

/* �Ĵ���˵�������ÿ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_GLB_APB_CTL_UNION */
#define SOC_DSS_GLB_APB_CTL_ADDR(base)                ((base) + (0x0004))

/* �Ĵ���˵��������0��2��Ƶʱ���ſ�ʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_PXL0_DIV2_GT_EN_UNION */
#define SOC_DSS_GLB_PXL0_DIV2_GT_EN_ADDR(base)        ((base) + (0x0100))

/* �Ĵ���˵��������0��4��Ƶʱ���ſ�ʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_PXL0_DIV4_GT_EN_UNION */
#define SOC_DSS_GLB_PXL0_DIV4_GT_EN_ADDR(base)        ((base) + (0x104))

/* �Ĵ���˵��������0��ʱ���ſ�ʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_PXL0_GT_EN_UNION */
#define SOC_DSS_GLB_PXL0_GT_EN_ADDR(base)             ((base) + (0x108))

/* �Ĵ���˵����DSIʱ�Ӷ�Ӧ��dsiʱ���ſ��ź�
   λ����UNION�ṹ:  SOC_DSS_GLB_PXL0_DSI_GT_EN_UNION */
#define SOC_DSS_GLB_PXL0_DSI_GT_EN_ADDR(base)         ((base) + (0x10C))

/* �Ĵ���˵��������0�ļ���Ƶ������
   λ����UNION�ṹ:  SOC_DSS_GLB_PXL0_DIVXCFG_UNION */
#define SOC_DSS_GLB_PXL0_DIVXCFG_ADDR(base)           ((base) + (0x110))

/* �Ĵ���˵����DSI1��ʱ��ѡ��
   λ����UNION�ṹ:  SOC_DSS_GLB_DSI1_CLK_SEL_UNION */
#define SOC_DSS_GLB_DSI1_CLK_SEL_ADDR(base)           ((base) + (0x114))

/* �Ĵ���˵����axi����ʱ������λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_DSS_AXI_RST_EN_UNION */
#define SOC_DSS_GLB_DSS_AXI_RST_EN_ADDR(base)         ((base) + (0x118))

/* �Ĵ���˵����apb����ʱ������λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_DSS_APB_RST_EN_UNION */
#define SOC_DSS_GLB_DSS_APB_RST_EN_ADDR(base)         ((base) + (0x11C))

/* �Ĵ���˵����coreʱ������λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_DSS_CORE_RST_EN_UNION */
#define SOC_DSS_GLB_DSS_CORE_RST_EN_ADDR(base)        ((base) + (0x120))

/* �Ĵ���˵��������0��2��Ƶʱ������λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_PXL0_DIV2_RST_EN_UNION */
#define SOC_DSS_GLB_PXL0_DIV2_RST_EN_ADDR(base)       ((base) + (0x124))

/* �Ĵ���˵��������0��4��Ƶʱ������λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_PXL0_DIV4_RST_EN_UNION */
#define SOC_DSS_GLB_PXL0_DIV4_RST_EN_ADDR(base)       ((base) + (0x128))

/* �Ĵ���˵��������0ʱ�������λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_PXL0_RST_EN_UNION */
#define SOC_DSS_GLB_PXL0_RST_EN_ADDR(base)            ((base) + (0x12C))

/* �Ĵ���˵��������0��Ӧ��DSIʱ������λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_PXL0_DSI_RST_EN_UNION */
#define SOC_DSS_GLB_PXL0_DSI_RST_EN_ADDR(base)        ((base) + (0x130))

/* �Ĵ���˵��������1ʱ������λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_DSS_PXL1_RST_EN_UNION */
#define SOC_DSS_GLB_DSS_PXL1_RST_EN_ADDR(base)        ((base) + (0x134))

/* �Ĵ���˵����DSI1�ĸ�λѡ��
   λ����UNION�ṹ:  SOC_DSS_GLB_DSI1_RST_SEL_UNION */
#define SOC_DSS_GLB_DSI1_RST_SEL_ADDR(base)           ((base) + (0x138))

/* �Ĵ���˵����MMBUF axi����ʱ������λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_MM_AXI_CLK_RST_EN_UNION */
#define SOC_DSS_GLB_MM_AXI_CLK_RST_EN_ADDR(base)      ((base) + (0x13C))

/* �Ĵ���˵����AFBCD IP��λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_AFBCD0_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD0_IP_RST_EN_ADDR(base)       ((base) + (0x140))

/* �Ĵ���˵����AFBCD IP��λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_AFBCD1_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD1_IP_RST_EN_ADDR(base)       ((base) + (0x144))

/* �Ĵ���˵����AFBCD IP��λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_AFBCD2_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD2_IP_RST_EN_ADDR(base)       ((base) + (0x148))

/* �Ĵ���˵����AFBCD IP��λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_AFBCD3_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD3_IP_RST_EN_ADDR(base)       ((base) + (0x14C))

/* �Ĵ���˵����AFBCD IP��λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_AFBCD4_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD4_IP_RST_EN_ADDR(base)       ((base) + (0x150))

/* �Ĵ���˵����AFBCD IP��λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_AFBCD5_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD5_IP_RST_EN_ADDR(base)       ((base) + (0x154))

/* �Ĵ���˵����AFBCD IP��λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_AFBCD6_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD6_IP_RST_EN_ADDR(base)       ((base) + (0x158))

/* �Ĵ���˵����AFBCD IP��λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_AFBCD7_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCD7_IP_RST_EN_ADDR(base)       ((base) + (0x15C))

/* �Ĵ���˵����AFBCE IP��λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_AFBCE0_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCE0_IP_RST_EN_ADDR(base)       ((base) + (0x160))

/* �Ĵ���˵����AFBCE IP��λʹ��
   λ����UNION�ṹ:  SOC_DSS_GLB_AFBCE1_IP_RST_EN_UNION */
#define SOC_DSS_GLB_AFBCE1_IP_RST_EN_ADDR(base)       ((base) + (0x164))

/* �Ĵ���˵����MCU����0�ж�ָʾ
   λ����UNION�ṹ:  SOC_DSS_GLB_MCU_ITF0_INTS_UNION */
#define SOC_DSS_GLB_MCU_ITF0_INTS_ADDR(base)          ((base) + (0x0170))

/* �Ĵ���˵����MCU����0�ж�����
   λ����UNION�ṹ:  SOC_DSS_GLB_MCU_ITF0_INT_MSK_UNION */
#define SOC_DSS_GLB_MCU_ITF0_INT_MSK_ADDR(base)       ((base) + (0x0174))

/* �Ĵ���˵����MCU����1�ж�ָʾ
   λ����UNION�ṹ:  SOC_DSS_GLB_MCU_ITF1_INTS_UNION */
#define SOC_DSS_GLB_MCU_ITF1_INTS_ADDR(base)          ((base) + (0x0178))

/* �Ĵ���˵����MCU����1�ж�����
   λ����UNION�ṹ:  SOC_DSS_GLB_MCU_ITF1_INT_MSK_UNION */
#define SOC_DSS_GLB_MCU_ITF1_INT_MSK_ADDR(base)       ((base) + (0x017C))

/* �Ĵ���˵����CPU����0�ж�ָʾ
   λ����UNION�ṹ:  SOC_DSS_GLB_CPU_ITF0_INTS_UNION */
#define SOC_DSS_GLB_CPU_ITF0_INTS_ADDR(base)          ((base) + (0x0180))

/* �Ĵ���˵����CPU����0�ж�����
   λ����UNION�ṹ:  SOC_DSS_GLB_CPU_ITF0_INT_MSK_UNION */
#define SOC_DSS_GLB_CPU_ITF0_INT_MSK_ADDR(base)       ((base) + (0x0184))

/* �Ĵ���˵����CPU����1�ж�ָʾ
   λ����UNION�ṹ:  SOC_DSS_GLB_CPU_ITF1_INTS_UNION */
#define SOC_DSS_GLB_CPU_ITF1_INTS_ADDR(base)          ((base) + (0x0188))

/* �Ĵ���˵����CPU����1�ж�����
   λ����UNION�ṹ:  SOC_DSS_GLB_CPU_ITF1_INT_MSK_UNION */
#define SOC_DSS_GLB_CPU_ITF1_INT_MSK_ADDR(base)       ((base) + (0x018C))

/* �Ĵ���˵����CPU��Ӧ��DPP�ж�ָʾ
   λ����UNION�ṹ:  SOC_DSS_GLB_DPP_INTS_UNION */
#define SOC_DSS_GLB_DPP_INTS_ADDR(base)               ((base) + (0x0190))

/* �Ĵ���˵����CPU��Ӧ��DPP�ж�����
   λ����UNION�ṹ:  SOC_DSS_GLB_DPP_INT_MSK_UNION */
#define SOC_DSS_GLB_DPP_INT_MSK_ADDR(base)            ((base) + (0x0194))

/* �Ĵ���˵����CPU��Ӧ��RCH CE�ж�ָʾ
   λ����UNION�ṹ:  SOC_DSS_GLB_RCH_CE_INTS_UNION */
#define SOC_DSS_GLB_RCH_CE_INTS_ADDR(base)            ((base) + (0x198))

/* �Ĵ���˵����CPU��Ӧ��RCH CE�ж�����
   λ����UNION�ṹ:  SOC_DSS_GLB_RCH_CE_INT_MSK_UNION */
#define SOC_DSS_GLB_RCH_CE_INT_MSK_ADDR(base)         ((base) + (0x19C))

/* �Ĵ���˵����MCU�����ж�ָʾ
   λ����UNION�ṹ:  SOC_DSS_GLB_MCU_PDP_INTS_UNION */
#define SOC_DSS_GLB_MCU_PDP_INTS_ADDR(base)           ((base) + (0x20C))

/* �Ĵ���˵����MCU�����ж�����
   λ����UNION�ṹ:  SOC_DSS_GLB_MCU_PDP_INT_MSK_UNION */
#define SOC_DSS_GLB_MCU_PDP_INT_MSK_ADDR(base)        ((base) + (0x210))

/* �Ĵ���˵����MCU�����ж�ָʾ
   λ����UNION�ṹ:  SOC_DSS_GLB_MCU_SDP_INTS_UNION */
#define SOC_DSS_GLB_MCU_SDP_INTS_ADDR(base)           ((base) + (0x214))

/* �Ĵ���˵����MCU�����ж�����
   λ����UNION�ṹ:  SOC_DSS_GLB_MCU_SDP_INT_MSK_UNION */
#define SOC_DSS_GLB_MCU_SDP_INT_MSK_ADDR(base)        ((base) + (0x218))

/* �Ĵ���˵����MCU�����ж�ָʾ
   λ����UNION�ṹ:  SOC_DSS_GLB_MCU_OFF_INTS_UNION */
#define SOC_DSS_GLB_MCU_OFF_INTS_ADDR(base)           ((base) + (0x21C))

/* �Ĵ���˵����MCU�����ж�����
   λ����UNION�ṹ:  SOC_DSS_GLB_MCU_OFF_INT_MSK_UNION */
#define SOC_DSS_GLB_MCU_OFF_INT_MSK_ADDR(base)        ((base) + (0x220))

/* �Ĵ���˵����CPU�����ж�ָʾ
   λ����UNION�ṹ:  SOC_DSS_GLB_CPU_PDP_INTS_UNION */
#define SOC_DSS_GLB_CPU_PDP_INTS_ADDR(base)           ((base) + (0x224))

/* �Ĵ���˵����CPU�����ж�����
   λ����UNION�ṹ:  SOC_DSS_GLB_CPU_PDP_INT_MSK_UNION */
#define SOC_DSS_GLB_CPU_PDP_INT_MSK_ADDR(base)        ((base) + (0x228))

/* �Ĵ���˵����CPU�����ж�ָʾ
   λ����UNION�ṹ:  SOC_DSS_GLB_CPU_SDP_INTS_UNION */
#define SOC_DSS_GLB_CPU_SDP_INTS_ADDR(base)           ((base) + (0x22C))

/* �Ĵ���˵����CPU�����ж�����
   λ����UNION�ṹ:  SOC_DSS_GLB_CPU_SDP_INT_MSK_UNION */
#define SOC_DSS_GLB_CPU_SDP_INT_MSK_ADDR(base)        ((base) + (0x230))

/* �Ĵ���˵����CPU�����ж�ָʾ
   λ����UNION�ṹ:  SOC_DSS_GLB_CPU_OFF_INTS_UNION */
#define SOC_DSS_GLB_CPU_OFF_INTS_ADDR(base)           ((base) + (0x234))

/* �Ĵ���˵����CPU�����ж�����
   λ����UNION�ṹ:  SOC_DSS_GLB_CPU_OFF_INT_MSK_UNION */
#define SOC_DSS_GLB_CPU_OFF_INT_MSK_ADDR(base)        ((base) + (0x238))

/* �Ĵ���˵���������ж�ָʾ
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_MCTL_INTS_UNION */
#define SOC_DSS_GLB_DBG_MCTL_INTS_ADDR(base)          ((base) + (0x23C))

/* �Ĵ���˵���������ж�����
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_MCTL_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_MCTL_INT_MSK_ADDR(base)       ((base) + (0x240))

/* �Ĵ���˵����дͨ��0�ж�ָʾ�������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_WCH0_INTS_UNION */
#define SOC_DSS_GLB_DBG_WCH0_INTS_ADDR(base)          ((base) + (0x244))

/* �Ĵ���˵����дͨ��0�ж����Σ������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_WCH0_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_WCH0_INT_MSK_ADDR(base)       ((base) + (0x248))

/* �Ĵ���˵����дͨ��1�ж�ָʾ�������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_WCH1_INTS_UNION */
#define SOC_DSS_GLB_DBG_WCH1_INTS_ADDR(base)          ((base) + (0x24C))

/* �Ĵ���˵����дͨ��1�ж����Σ������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_WCH1_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_WCH1_INT_MSK_ADDR(base)       ((base) + (0x250))

/* �Ĵ���˵������ͨ��0�ж�ָʾ�������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH0_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH0_INTS_ADDR(base)          ((base) + (0x254))

/* �Ĵ���˵������ͨ��0�ж����Σ������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH0_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH0_INT_MSK_ADDR(base)       ((base) + (0x258))

/* �Ĵ���˵������ͨ��1�ж�ָʾ�������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH1_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH1_INTS_ADDR(base)          ((base) + (0x25C))

/* �Ĵ���˵������ͨ��1�ж����Σ������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH1_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH1_INT_MSK_ADDR(base)       ((base) + (0x260))

/* �Ĵ���˵������ͨ��2�ж�ָʾ�������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH2_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH2_INTS_ADDR(base)          ((base) + (0x264))

/* �Ĵ���˵������ͨ��2�ж����Σ������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH2_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH2_INT_MSK_ADDR(base)       ((base) + (0x268))

/* �Ĵ���˵������ͨ��3�ж�ָʾ�������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH3_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH3_INTS_ADDR(base)          ((base) + (0x26C))

/* �Ĵ���˵������ͨ��3�ж����Σ������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH3_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH3_INT_MSK_ADDR(base)       ((base) + (0x270))

/* �Ĵ���˵������ͨ��4�ж�ָʾ�������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH4_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH4_INTS_ADDR(base)          ((base) + (0x274))

/* �Ĵ���˵������ͨ��4�ж����Σ������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH4_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH4_INT_MSK_ADDR(base)       ((base) + (0x278))

/* �Ĵ���˵������ͨ��5�ж�ָʾ�������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH5_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH5_INTS_ADDR(base)          ((base) + (0x27C))

/* �Ĵ���˵������ͨ��5�ж����Σ������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH5_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH5_INT_MSK_ADDR(base)       ((base) + (0x280))

/* �Ĵ���˵������ͨ��6�ж�ָʾ�������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH6_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH6_INTS_ADDR(base)          ((base) + (0x284))

/* �Ĵ���˵������ͨ��6�ж����Σ������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH6_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH6_INT_MSK_ADDR(base)       ((base) + (0x288))

/* �Ĵ���˵������ͨ��7�ж�ָʾ�������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH7_INTS_UNION */
#define SOC_DSS_GLB_DBG_RCH7_INTS_ADDR(base)          ((base) + (0x28C))

/* �Ĵ���˵������ͨ��7�ж����Σ������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_RCH7_INT_MSK_UNION */
#define SOC_DSS_GLB_DBG_RCH7_INT_MSK_ADDR(base)       ((base) + (0x290))

/* �Ĵ���˵����GLB�жϣ������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_INTS_UNION */
#define SOC_DSS_GLB_INTS_ADDR(base)                   ((base) + (0x294))

/* �Ĵ���˵����GLB�жϣ������ã�
   λ����UNION�ṹ:  SOC_DSS_GLB_INT_MSK_UNION */
#define SOC_DSS_GLB_INT_MSK_ADDR(base)                ((base) + (0x298))

/* �Ĵ���˵����һ��ģ�����ʱ��ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_GLB_MODULE_CLK_SEL_UNION */
#define SOC_DSS_GLB_MODULE_CLK_SEL_ADDR(base)         ((base) + (0x0300))

/* �Ĵ���˵����һ��ģ�����ʱ��ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_GLB_MODULE_CLK_EN_UNION */
#define SOC_DSS_GLB_MODULE_CLK_EN_ADDR(base)          ((base) + (0x304))

/* �Ĵ���˵����һ��ģ�����ʱ��ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_GLB_MODULE1_CLK_SEL_UNION */
#define SOC_DSS_GLB_MODULE1_CLK_SEL_ADDR(base)        ((base) + (0x308))

/* �Ĵ���˵����һ��ģ�����ʱ��ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_GLB_MODULE1_CLK_EN_UNION */
#define SOC_DSS_GLB_MODULE1_CLK_EN_ADDR(base)         ((base) + (0x30C))

/* �Ĵ���˵�������ԼĴ���
   λ����UNION�ṹ:  SOC_DSS_GLB_GLB0_DBG_SEL_UNION */
#define SOC_DSS_GLB_GLB0_DBG_SEL_ADDR(base)           ((base) + (0x310))

/* �Ĵ���˵�������ԼĴ���
   λ����UNION�ṹ:  SOC_DSS_GLB_GLB1_DBG_SEL_UNION */
#define SOC_DSS_GLB_GLB1_DBG_SEL_ADDR(base)           ((base) + (0x314))

/* �Ĵ���˵����CPU�жϵ��ԼĴ���
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_IRQ_CPU_UNION */
#define SOC_DSS_GLB_DBG_IRQ_CPU_ADDR(base)            ((base) + (0x320))

/* �Ĵ���˵����MCU�жϵ��ԼĴ���
   λ����UNION�ṹ:  SOC_DSS_GLB_DBG_IRQ_MCU_UNION */
#define SOC_DSS_GLB_DBG_IRQ_MCU_ADDR(base)            ((base) + (0x324))

/* �Ĵ���˵����TPѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_GLB_TP_SEL_UNION */
#define SOC_DSS_GLB_TP_SEL_ADDR(base)                 ((base) + (0x0400))

/* �Ĵ���˵����LDI0��crcУ����
   λ����UNION�ṹ:  SOC_DSS_GLB_CRC_DBG_LDI0_UNION */
#define SOC_DSS_GLB_CRC_DBG_LDI0_ADDR(base)           ((base) + (0x0404))

/* �Ĵ���˵����LDI1��crcУ����
   λ����UNION�ṹ:  SOC_DSS_GLB_CRC_DBG_LDI1_UNION */
#define SOC_DSS_GLB_CRC_DBG_LDI1_ADDR(base)           ((base) + (0x0408))

/* �Ĵ���˵����LDI0��CRC����ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_GLB_CRC_LDI0_EN_UNION */
#define SOC_DSS_GLB_CRC_LDI0_EN_ADDR(base)            ((base) + (0x040C))

/* �Ĵ���˵����LDI0�ϱ���CRCУ���֡��
   λ����UNION�ṹ:  SOC_DSS_GLB_CRC_LDI0_FRM_UNION */
#define SOC_DSS_GLB_CRC_LDI0_FRM_ADDR(base)           ((base) + (0x0410))

/* �Ĵ���˵����LDI1��CRC����ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_GLB_CRC_LDI1_EN_UNION */
#define SOC_DSS_GLB_CRC_LDI1_EN_ADDR(base)            ((base) + (0x0414))

/* �Ĵ���˵����LDI1�ϱ���CRCУ���֡��
   λ����UNION�ṹ:  SOC_DSS_GLB_CRC_LDI1_FRM_UNION */
#define SOC_DSS_GLB_CRC_LDI1_FRM_ADDR(base)           ((base) + (0x0418))

/* �Ĵ���˵����CPU��дmemoryʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_DSS_GLB_DSS_MEM_CTRL_UNION */
#define SOC_DSS_GLB_DSS_MEM_CTRL_ADDR(base)           ((base) + (0x0600))

/* �Ĵ���˵����MEM�͹��Ŀ��ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_GLB_DSS_PM_CTRL_UNION */
#define SOC_DSS_GLB_DSS_PM_CTRL_ADDR(base)            ((base) + (0x0604))





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
                     (1/1) reg_GLB
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DSS_TAG_UNION
 �ṹ˵��  : DSS_TAG �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x14100703�����:32
 �Ĵ���˵��: dss�汾��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_tag : 32; /* bit[0-31]: dss�汾�� */
    } reg;
} SOC_DSS_GLB_DSS_TAG_UNION;
#endif
#define SOC_DSS_GLB_DSS_TAG_dss_tag_START  (0)
#define SOC_DSS_GLB_DSS_TAG_dss_tag_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_APB_CTL_UNION
 �ṹ˵��  : APB_CTL �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ÿ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apb_cpu_force : 1;  /* bit[0]   : 1:ǿ��ѡ��CPU����DSS�Ĵ���
                                                        0:��DSS�Զ��ٲ�ѡ������CPU����command list���üĴ��� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_APB_CTL_UNION;
#endif
#define SOC_DSS_GLB_APB_CTL_apb_cpu_force_START  (0)
#define SOC_DSS_GLB_APB_CTL_apb_cpu_force_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_PXL0_DIV2_GT_EN_UNION
 �ṹ˵��  : PXL0_DIV2_GT_EN �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����0��2��Ƶʱ���ſ�ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_div2_gt_en : 1;  /* bit[0-0] : 1������pxl0��2��Ƶʱ��
                                                          0���ر�pxl0��2��Ƶʱ�� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_PXL0_DIV2_GT_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DIV2_GT_EN_pxl0_div2_gt_en_START  (0)
#define SOC_DSS_GLB_PXL0_DIV2_GT_EN_pxl0_div2_gt_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_PXL0_DIV4_GT_EN_UNION
 �ṹ˵��  : PXL0_DIV4_GT_EN �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����0��4��Ƶʱ���ſ�ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_div4_gt_en : 1;  /* bit[0-0] : 1������pxl0��4��Ƶʱ��
                                                          0���ر�pxl0��4��Ƶʱ�� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_PXL0_DIV4_GT_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DIV4_GT_EN_pxl0_div4_gt_en_START  (0)
#define SOC_DSS_GLB_PXL0_DIV4_GT_EN_pxl0_div4_gt_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_PXL0_GT_EN_UNION
 �ṹ˵��  : PXL0_GT_EN �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����0��ʱ���ſ�ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_gt_en : 1;  /* bit[0-0] : 1������pxl0��ʱ��
                                                     0���ر�pxl0��ʱ�� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_PXL0_GT_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_GT_EN_pxl0_gt_en_START  (0)
#define SOC_DSS_GLB_PXL0_GT_EN_pxl0_gt_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_PXL0_DSI_GT_EN_UNION
 �ṹ˵��  : PXL0_DSI_GT_EN �Ĵ����ṹ���塣��ַƫ����:0x10C����ֵ:0x00000001�����:32
 �Ĵ���˵��: DSIʱ�Ӷ�Ӧ��dsiʱ���ſ��ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_dsi_gt_en : 2;  /* bit[0-1] : 2��bx0���ر�pxl0���ɵ�dsiʱ��
                                                         2��b01������pxl0���ɵ�dsiʱ�ӣ�ѡͨû�з�Ƶ��ʱ�ӡ�
                                                         2��b11����ʼpxl0���ɵ�dsiʱ�ӣ�ѡͨ1~8��Ƶ��ʱ�ӡ� */
        unsigned int  reserved       : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_GLB_PXL0_DSI_GT_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DSI_GT_EN_pxl0_dsi_gt_en_START  (0)
#define SOC_DSS_GLB_PXL0_DSI_GT_EN_pxl0_dsi_gt_en_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_PXL0_DIVXCFG_UNION
 �ṹ˵��  : PXL0_DIVXCFG �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����0�ļ���Ƶ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_divxcfg : 3;  /* bit[0-2] : ������pxl0ʱ��ʱ�ӽ��з�Ƶ���á�
                                                       1����ʾ2��Ƶ
                                                       2����ʾ3��Ƶ
                                                       3����ʾ4��Ƶ
                                                       4����ʾ5��Ƶ
                                                       5����ʾ6��Ƶ
                                                       6����ʾ7��Ƶ
                                                       7����ʾ8��Ƶ */
        unsigned int  reserved     : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_DSS_GLB_PXL0_DIVXCFG_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DIVXCFG_pxl0_divxcfg_START  (0)
#define SOC_DSS_GLB_PXL0_DIVXCFG_pxl0_divxcfg_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DSI1_CLK_SEL_UNION
 �ṹ˵��  : DSI1_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x114����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSI1��ʱ��ѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi1_clk_sel : 1;  /* bit[0]   : 0����ʾѡ��pxl0��ʱ��
                                                       1����ʾѡ��pxl1��ʱ�� */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_DSI1_CLK_SEL_UNION;
#endif
#define SOC_DSS_GLB_DSI1_CLK_SEL_dsi1_clk_sel_START  (0)
#define SOC_DSS_GLB_DSI1_CLK_SEL_dsi1_clk_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DSS_AXI_RST_EN_UNION
 �ṹ˵��  : DSS_AXI_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x118����ֵ:0x00000000�����:32
 �Ĵ���˵��: axi����ʱ������λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_axi_rst_en : 1;  /* bit[0-0] : 1�������λaxi����
                                                         0������⸴λaxi���� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_DSS_AXI_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_DSS_AXI_RST_EN_dss_axi_rst_en_START  (0)
#define SOC_DSS_GLB_DSS_AXI_RST_EN_dss_axi_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DSS_APB_RST_EN_UNION
 �ṹ˵��  : DSS_APB_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x11C����ֵ:0x00000000�����:32
 �Ĵ���˵��: apb����ʱ������λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_apb_rst_en : 1;  /* bit[0-0] : 1�������λapb����
                                                         0������⸴λapb���� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_DSS_APB_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_DSS_APB_RST_EN_dss_apb_rst_en_START  (0)
#define SOC_DSS_GLB_DSS_APB_RST_EN_dss_apb_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DSS_CORE_RST_EN_UNION
 �ṹ˵��  : DSS_CORE_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x120����ֵ:0x00000000�����:32
 �Ĵ���˵��: coreʱ������λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_core_rst_en : 1;  /* bit[0-0] : 1�������λdss coreʱ����
                                                          0������⸴λdss coreʱ���� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_DSS_CORE_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_DSS_CORE_RST_EN_dss_core_rst_en_START  (0)
#define SOC_DSS_GLB_DSS_CORE_RST_EN_dss_core_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_PXL0_DIV2_RST_EN_UNION
 �ṹ˵��  : PXL0_DIV2_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x124����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����0��2��Ƶʱ������λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_div2_rst_en : 1;  /* bit[0-0] : 1�������λpxl0 2��Ƶʱ����
                                                           0������⸴λpxl0 2��Ƶʱ���� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_PXL0_DIV2_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DIV2_RST_EN_pxl0_div2_rst_en_START  (0)
#define SOC_DSS_GLB_PXL0_DIV2_RST_EN_pxl0_div2_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_PXL0_DIV4_RST_EN_UNION
 �ṹ˵��  : PXL0_DIV4_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x128����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����0��4��Ƶʱ������λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_div4_rst_en : 1;  /* bit[0-0] : 1�������λpxl0 4��Ƶʱ����
                                                           0������⸴λpxl0 4��Ƶʱ���� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_PXL0_DIV4_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DIV4_RST_EN_pxl0_div4_rst_en_START  (0)
#define SOC_DSS_GLB_PXL0_DIV4_RST_EN_pxl0_div4_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_PXL0_RST_EN_UNION
 �ṹ˵��  : PXL0_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x12C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����0ʱ�������λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_rst_en : 1;  /* bit[0-0] : 1�������λpxl0ʱ����
                                                      0������⸴λpxl0ʱ���� */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_PXL0_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_RST_EN_pxl0_rst_en_START  (0)
#define SOC_DSS_GLB_PXL0_RST_EN_pxl0_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_PXL0_DSI_RST_EN_UNION
 �ṹ˵��  : PXL0_DSI_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x130����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����0��Ӧ��DSIʱ������λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pxl0_dsi_rst_en : 1;  /* bit[0]   : 1�������λdsi��Ƶʱ����
                                                          0������⸴λdsi��Ƶʱ���� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_PXL0_DSI_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_PXL0_DSI_RST_EN_pxl0_dsi_rst_en_START  (0)
#define SOC_DSS_GLB_PXL0_DSI_RST_EN_pxl0_dsi_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DSS_PXL1_RST_EN_UNION
 �ṹ˵��  : DSS_PXL1_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x134����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����1ʱ������λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_pxl1_rst_en : 1;  /* bit[0-0] : 1�������pxl1ʱ�������ɵĸ�λ�ź�Ϊ�첽��λͬ�����롣
                                                          0������⸴λpxl1ʱ���� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_DSS_PXL1_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_DSS_PXL1_RST_EN_dss_pxl1_rst_en_START  (0)
#define SOC_DSS_GLB_DSS_PXL1_RST_EN_dss_pxl1_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DSI1_RST_SEL_UNION
 �ṹ˵��  : DSI1_RST_SEL �Ĵ����ṹ���塣��ַƫ����:0x138����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSI1�ĸ�λѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi1_rst_sel : 1;  /* bit[0]   : 0����ʾѡ��pxl0�ĸ�λ�ź�
                                                       1����ʾѡ��pxl1�ĸ�λ�ź� */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_DSI1_RST_SEL_UNION;
#endif
#define SOC_DSS_GLB_DSI1_RST_SEL_dsi1_rst_sel_START  (0)
#define SOC_DSS_GLB_DSI1_RST_SEL_dsi1_rst_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_MM_AXI_CLK_RST_EN_UNION
 �ṹ˵��  : MM_AXI_CLK_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x13C����ֵ:0x00000000�����:32
 �Ĵ���˵��: MMBUF axi����ʱ������λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mm_axi_clk_rst_en : 1;  /* bit[0-0] : 1�������λmmbuf��axi����
                                                            0������⸴λmmbuf��axi���� */
        unsigned int  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_MM_AXI_CLK_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_MM_AXI_CLK_RST_EN_mm_axi_clk_rst_en_START  (0)
#define SOC_DSS_GLB_MM_AXI_CLK_RST_EN_mm_axi_clk_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_AFBCD0_IP_RST_EN_UNION
 �ṹ˵��  : AFBCD0_IP_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x140����ֵ:0x00000000�����:32
 �Ĵ���˵��: AFBCD IP��λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd0_ip_rst_en : 1;  /* bit[0-0] : 1�������λafbcd mali ip
                                                           0������⸴λafbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_AFBCD0_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD0_IP_RST_EN_afbcd0_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD0_IP_RST_EN_afbcd0_ip_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_AFBCD1_IP_RST_EN_UNION
 �ṹ˵��  : AFBCD1_IP_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x144����ֵ:0x00000000�����:32
 �Ĵ���˵��: AFBCD IP��λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd1_ip_rst_en : 1;  /* bit[0-0] : 1�������λafbcd mali ip
                                                           0������⸴λafbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_AFBCD1_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD1_IP_RST_EN_afbcd1_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD1_IP_RST_EN_afbcd1_ip_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_AFBCD2_IP_RST_EN_UNION
 �ṹ˵��  : AFBCD2_IP_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x148����ֵ:0x00000000�����:32
 �Ĵ���˵��: AFBCD IP��λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd2_ip_rst_en : 1;  /* bit[0-0] : 1�������λafbcd mali ip
                                                           0������⸴λafbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_AFBCD2_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD2_IP_RST_EN_afbcd2_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD2_IP_RST_EN_afbcd2_ip_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_AFBCD3_IP_RST_EN_UNION
 �ṹ˵��  : AFBCD3_IP_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x14C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AFBCD IP��λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd3_ip_rst_en : 1;  /* bit[0-0] : 1�������λafbcd mali ip
                                                           0������⸴λafbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_AFBCD3_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD3_IP_RST_EN_afbcd3_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD3_IP_RST_EN_afbcd3_ip_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_AFBCD4_IP_RST_EN_UNION
 �ṹ˵��  : AFBCD4_IP_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x150����ֵ:0x00000000�����:32
 �Ĵ���˵��: AFBCD IP��λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd4_ip_rst_en : 1;  /* bit[0-0] : 1�������λafbcd mali ip
                                                           0������⸴λafbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_AFBCD4_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD4_IP_RST_EN_afbcd4_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD4_IP_RST_EN_afbcd4_ip_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_AFBCD5_IP_RST_EN_UNION
 �ṹ˵��  : AFBCD5_IP_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x154����ֵ:0x00000000�����:32
 �Ĵ���˵��: AFBCD IP��λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd5_ip_rst_en : 1;  /* bit[0-0] : 1�������λafbcd mali ip
                                                           0������⸴λafbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_AFBCD5_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD5_IP_RST_EN_afbcd5_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD5_IP_RST_EN_afbcd5_ip_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_AFBCD6_IP_RST_EN_UNION
 �ṹ˵��  : AFBCD6_IP_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x158����ֵ:0x00000000�����:32
 �Ĵ���˵��: AFBCD IP��λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd6_ip_rst_en : 1;  /* bit[0-0] : 1�������λafbcd mali ip
                                                           0������⸴λafbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_AFBCD6_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD6_IP_RST_EN_afbcd6_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD6_IP_RST_EN_afbcd6_ip_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_AFBCD7_IP_RST_EN_UNION
 �ṹ˵��  : AFBCD7_IP_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x15C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AFBCD IP��λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbcd7_ip_rst_en : 1;  /* bit[0-0] : 1�������λafbcd mali ip
                                                           0������⸴λafbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_AFBCD7_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCD7_IP_RST_EN_afbcd7_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCD7_IP_RST_EN_afbcd7_ip_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_AFBCE0_IP_RST_EN_UNION
 �ṹ˵��  : AFBCE0_IP_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x160����ֵ:0x00000000�����:32
 �Ĵ���˵��: AFBCE IP��λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce0_ip_rst_en : 1;  /* bit[0-0] : 1�������λafbce mali ip
                                                           0������⸴λafbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_AFBCE0_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCE0_IP_RST_EN_afbce0_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCE0_IP_RST_EN_afbce0_ip_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_AFBCE1_IP_RST_EN_UNION
 �ṹ˵��  : AFBCE1_IP_RST_EN �Ĵ����ṹ���塣��ַƫ����:0x164����ֵ:0x00000000�����:32
 �Ĵ���˵��: AFBCE IP��λʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce1_ip_rst_en : 1;  /* bit[0-0] : 1�������λafbce mali ip
                                                           0������⸴λafbcd mali ip */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_AFBCE1_IP_RST_EN_UNION;
#endif
#define SOC_DSS_GLB_AFBCE1_IP_RST_EN_afbce1_ip_rst_en_START  (0)
#define SOC_DSS_GLB_AFBCE1_IP_RST_EN_afbce1_ip_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_MCU_ITF0_INTS_UNION
 �ṹ˵��  : MCU_ITF0_INTS �Ĵ����ṹ���塣��ַƫ����:0x0170����ֵ:0x00000000�����:32
 �Ĵ���˵��: MCU����0�ж�ָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_itf0_ints : 14; /* bit[0-13] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                         bit13:dsi_te_tri_ints
                                                         bit12:lcd_te0_pin_ints
                                                         bit11:lcd_te1_pin_ints
                                                         bit10:vactive1_end_ints
                                                         bit9:vactive1_start_ints
                                                         bit8:vactive0_end_ints
                                                         bit7:vactive0_start_ints
                                                         bit6:vfrontporch_ints
                                                         bit5:vbackporch_ints
                                                         bit4:vsync_ints
                                                         bit3:vfrontporch_end_ints
                                                         bit2:ldi_unflow_ints
                                                         bit1:frm_end_ints
                                                         bit0:frm_start_ints */
        unsigned int  reserved      : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_GLB_MCU_ITF0_INTS_UNION;
#endif
#define SOC_DSS_GLB_MCU_ITF0_INTS_mcu_itf0_ints_START  (0)
#define SOC_DSS_GLB_MCU_ITF0_INTS_mcu_itf0_ints_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_MCU_ITF0_INT_MSK_UNION
 �ṹ˵��  : MCU_ITF0_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x0174����ֵ:0x00000000�����:32
 �Ĵ���˵��: MCU����0�ж�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_itf0_int_msk : 14; /* bit[0-13] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                            bit13:dsi_te_tri_ints
                                                            bit12:lcd_te0_pin_ints
                                                            bit11:lcd_te1_pin_ints
                                                            bit10:vactive1_end_ints
                                                            bit9:vactive1_start_ints
                                                            bit8:vactive0_end_ints
                                                            bit7:vactive0_start_ints
                                                            bit6:vfrontporch_ints
                                                            bit5:vbackporch_ints
                                                            bit4:vsync_ints
                                                            bit3:vfrontporch_end_ints
                                                            bit2:ldi_unflow_ints
                                                            bit1:frm_end_ints
                                                            bit0:frm_start_ints */
        unsigned int  reserved         : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_GLB_MCU_ITF0_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_MCU_ITF0_INT_MSK_mcu_itf0_int_msk_START  (0)
#define SOC_DSS_GLB_MCU_ITF0_INT_MSK_mcu_itf0_int_msk_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_MCU_ITF1_INTS_UNION
 �ṹ˵��  : MCU_ITF1_INTS �Ĵ����ṹ���塣��ַƫ����:0x0178����ֵ:0x00000000�����:32
 �Ĵ���˵��: MCU����1�ж�ָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_itf1_ints : 14; /* bit[0-13] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                         bit13:dsi_te_tri_ints
                                                         bit12:lcd_te0_pin_ints
                                                         bit11:lcd_te1_pin_ints
                                                         bit10:vactive1_end_ints
                                                         bit9:vactive1_start_ints
                                                         bit8:vactive0_end_ints
                                                         bit7:vactive0_start_ints
                                                         bit6:vfrontporch_ints
                                                         bit5:vbackporch_ints
                                                         bit4:vsync_ints
                                                         bit3:vfrontporch_end_ints
                                                         bit2:ldi_unflow_ints
                                                         bit1:frm_end_ints
                                                         bit0:frm_start_ints */
        unsigned int  reserved      : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_GLB_MCU_ITF1_INTS_UNION;
#endif
#define SOC_DSS_GLB_MCU_ITF1_INTS_mcu_itf1_ints_START  (0)
#define SOC_DSS_GLB_MCU_ITF1_INTS_mcu_itf1_ints_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_MCU_ITF1_INT_MSK_UNION
 �ṹ˵��  : MCU_ITF1_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x017C����ֵ:0x00000000�����:32
 �Ĵ���˵��: MCU����1�ж�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_itf1_int_msk : 14; /* bit[0-13] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                            bit13:dsi_te_tri_ints
                                                            bit12:lcd_te0_pin_ints
                                                            bit11:lcd_te1_pin_ints
                                                            bit10:vactive1_end_ints
                                                            bit9:vactive1_start_ints
                                                            bit8:vactive0_end_ints
                                                            bit7:vactive0_start_ints
                                                            bit6:vfrontporch_ints
                                                            bit5:vbackporch_ints
                                                            bit4:vsync_ints
                                                            bit3:vfrontporch_end_ints
                                                            bit2:ldi_unflow_ints
                                                            bit1:frm_end_ints
                                                            bit0:frm_start_ints */
        unsigned int  reserved         : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_GLB_MCU_ITF1_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_MCU_ITF1_INT_MSK_mcu_itf1_int_msk_START  (0)
#define SOC_DSS_GLB_MCU_ITF1_INT_MSK_mcu_itf1_int_msk_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CPU_ITF0_INTS_UNION
 �ṹ˵��  : CPU_ITF0_INTS �Ĵ����ṹ���塣��ַƫ����:0x0180����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU����0�ж�ָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_itf0_ints : 14; /* bit[0-13] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                         bit13:dsi_te_tri_ints
                                                         bit12:lcd_te0_pin_ints
                                                         bit11:lcd_te1_pin_ints
                                                         bit10:vactive1_end_ints
                                                         bit9:vactive1_start_ints
                                                         bit8:vactive0_end_ints
                                                         bit7:vactive0_start_ints
                                                         bit6:vfrontporch_ints
                                                         bit5:vbackporch_ints
                                                         bit4:vsync_ints
                                                         bit3:vfrontporch_end_ints
                                                         bit2:ldi_unflow_ints
                                                         bit1:frm_end_ints
                                                         bit0:frm_start_ints */
        unsigned int  reserved      : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_GLB_CPU_ITF0_INTS_UNION;
#endif
#define SOC_DSS_GLB_CPU_ITF0_INTS_cpu_itf0_ints_START  (0)
#define SOC_DSS_GLB_CPU_ITF0_INTS_cpu_itf0_ints_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CPU_ITF0_INT_MSK_UNION
 �ṹ˵��  : CPU_ITF0_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x0184����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU����0�ж�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_itf0_int_msk : 14; /* bit[0-13] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                            bit13:dsi_te_tri_ints
                                                            bit12:lcd_te0_pin_ints
                                                            bit11:lcd_te1_pin_ints
                                                            bit10:vactive1_end_ints
                                                            bit9:vactive1_start_ints
                                                            bit8:vactive0_end_ints
                                                            bit7:vactive0_start_ints
                                                            bit6:vfrontporch_ints
                                                            bit5:vbackporch_ints
                                                            bit4:vsync_ints
                                                            bit3:vfrontporch_end_ints
                                                            bit2:ldi_unflow_ints
                                                            bit1:frm_end_ints
                                                            bit0:frm_start_ints */
        unsigned int  reserved         : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_GLB_CPU_ITF0_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_CPU_ITF0_INT_MSK_cpu_itf0_int_msk_START  (0)
#define SOC_DSS_GLB_CPU_ITF0_INT_MSK_cpu_itf0_int_msk_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CPU_ITF1_INTS_UNION
 �ṹ˵��  : CPU_ITF1_INTS �Ĵ����ṹ���塣��ַƫ����:0x0188����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU����1�ж�ָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_itf1_ints : 14; /* bit[0-13] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                         bit13:dsi_te_tri_ints
                                                         bit12:lcd_te0_pin_ints
                                                         bit11:lcd_te1_pin_ints
                                                         bit10:vactive1_end_ints
                                                         bit9:vactive1_start_ints
                                                         bit8:vactive0_end_ints
                                                         bit7:vactive0_start_ints
                                                         bit6:vfrontporch_ints
                                                         bit5:vbackporch_ints
                                                         bit4:vsync_ints
                                                         bit3:vfrontporch_end_ints
                                                         bit2:ldi_unflow_ints
                                                         bit1:frm_end_ints
                                                         bit0:frm_start_ints */
        unsigned int  reserved      : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_GLB_CPU_ITF1_INTS_UNION;
#endif
#define SOC_DSS_GLB_CPU_ITF1_INTS_cpu_itf1_ints_START  (0)
#define SOC_DSS_GLB_CPU_ITF1_INTS_cpu_itf1_ints_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CPU_ITF1_INT_MSK_UNION
 �ṹ˵��  : CPU_ITF1_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x018C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU����1�ж�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_itf1_int_msk : 14; /* bit[0-13] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                            bit13:dsi_te_tri_ints
                                                            bit12:lcd_te0_pin_ints
                                                            bit11:lcd_te1_pin_ints
                                                            bit10:vactive1_end_ints
                                                            bit9:vactive1_start_ints
                                                            bit8:vactive0_end_ints
                                                            bit7:vactive0_start_ints
                                                            bit6:vfrontporch_ints
                                                            bit5:vbackporch_ints
                                                            bit4:vsync_ints
                                                            bit3:vfrontporch_end_ints
                                                            bit2:ldi_unflow_ints
                                                            bit1:frm_end_ints
                                                            bit0:frm_start_ints */
        unsigned int  reserved         : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_GLB_CPU_ITF1_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_CPU_ITF1_INT_MSK_cpu_itf1_int_msk_START  (0)
#define SOC_DSS_GLB_CPU_ITF1_INT_MSK_cpu_itf1_int_msk_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DPP_INTS_UNION
 �ṹ˵��  : DPP_INTS �Ĵ����ṹ���塣��ַƫ����:0x0190����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU��Ӧ��DPP�ж�ָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp_ints : 8;  /* bit[0-7] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                   bit7: strength_intp, SBL����ǿ���жϣ���SBL����ǿ�ȷ����仯ʱ��1
                                                   bit6: backlight_intp, SBL����ǿ���жϣ���SBL����ı�����ֵ�����仯ʱ��1
                                                   bit5: ce_end_ind, ACM_CEͳ������ж�
                                                   bit4: ce_cancel_ind, ACM_CEȡ��ͳ���ж�
                                                   bit3: ce_lut1_rw_collide_ind, ACM_CE LUT1��д��ͻ
                                                   bit2: ce_lut0_rw_collide_ind, ACM_CE LUT0��д��ͻ
                                                   bit1: ce_hist1_rw_collide_ind, ACM_CE ֱ��ͼmemory1��д��ͻ
                                                   bit0: ce_hist0_rw_collide_ind, ACM_CE ֱ��ͼmemory0��д��ͻ */
        unsigned int  reserved : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_GLB_DPP_INTS_UNION;
#endif
#define SOC_DSS_GLB_DPP_INTS_dpp_ints_START  (0)
#define SOC_DSS_GLB_DPP_INTS_dpp_ints_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DPP_INT_MSK_UNION
 �ṹ˵��  : DPP_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x0194����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU��Ӧ��DPP�ж�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dpp_int_msk : 8;  /* bit[0-7] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                      bit7: strength_intp, SBL����ǿ���жϣ���SBL����ǿ�ȷ����仯ʱ��1
                                                      bit6: backlight_intp, SBL����ǿ���жϣ���SBL����ı�����ֵ�����仯ʱ��1
                                                      bit5: ce_end_ind, ACM_CEͳ������ж�
                                                      bit4: ce_cancel_ind, ACM_CEȡ��ͳ���ж�
                                                      bit3: ce_lut1_rw_collide_ind, ACM_CE LUT1��д��ͻ
                                                      bit2: ce_lut0_rw_collide_ind, ACM_CE LUT0��д��ͻ
                                                      bit1: ce_hist1_rw_collide_ind, ACM_CE ֱ��ͼmemory1��д��ͻ
                                                      bit0: ce_hist0_rw_collide_ind, ACM_CE ֱ��ͼmemory0��д��ͻ */
        unsigned int  reserved    : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_GLB_DPP_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DPP_INT_MSK_dpp_int_msk_START  (0)
#define SOC_DSS_GLB_DPP_INT_MSK_dpp_int_msk_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_RCH_CE_INTS_UNION
 �ṹ˵��  : RCH_CE_INTS �Ĵ����ṹ���塣��ַƫ����:0x198����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU��Ӧ��RCH CE�ж�ָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch_ce_ints : 4;  /* bit[0-3] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                      bit3:RCH4��ce_end
                                                      bit2:RCH4��ce_cancle
                                                      bit1:RCH2��ce_end
                                                      bit0:RCH2��ce_cancle */
        unsigned int  reserved    : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_GLB_RCH_CE_INTS_UNION;
#endif
#define SOC_DSS_GLB_RCH_CE_INTS_rch_ce_ints_START  (0)
#define SOC_DSS_GLB_RCH_CE_INTS_rch_ce_ints_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_RCH_CE_INT_MSK_UNION
 �ṹ˵��  : RCH_CE_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x19C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU��Ӧ��RCH CE�ж�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch_ce_int_msk : 4;  /* bit[0-3] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                         bit3:RCH4��ce_end
                                                         bit2:RCH4��ce_cancle
                                                         bit1:RCH2��ce_end
                                                         bit0:RCH2��ce_cancle */
        unsigned int  reserved       : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_GLB_RCH_CE_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_RCH_CE_INT_MSK_rch_ce_int_msk_START  (0)
#define SOC_DSS_GLB_RCH_CE_INT_MSK_rch_ce_int_msk_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_MCU_PDP_INTS_UNION
 �ṹ˵��  : MCU_PDP_INTS �Ĵ����ṹ���塣��ַƫ����:0x20C����ֵ:0x00000000�����:32
 �Ĵ���˵��: MCU�����ж�ָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_pdp_ints : 31; /* bit[0-30]: �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                       bit30:dss_glb_ints�ж�
                                                       bit29:mmu_irpt_s,mmu��ȫ�ж�
                                                       bit28:mmu_irpt_ns,mmu�ǰ�ȫ�ж�
                                                       bit27:dbg_mctl_ints
                                                       bit26:dbg_wch1_ints
                                                       bit25:dbg_wch0_ints
                                                       bit24:dbg_rch7_ints
                                                       bit23:dbg_rch6_ints
                                                       bit22:dbg_rch5_ints
                                                       bit21:dbg_rch4_ints
                                                       bit20:dbg_rch3_ints
                                                       bit19:dbg_rch2_ints
                                                       bit18:dbg_rch1_ints
                                                       bit17:dbg_rch0_ints
                                                       bit16:itf0_ints
                                                       bit15:dpp_ints
                                                       bit14:cmdlist��13ͨ�����ж�
                                                       bit13:cmdlist��12ͨ�����ж�
                                                       bit12:cmdlist��11ͨ�����ж�
                                                       bit11:cmdlist��10ͨ�����ж�
                                                       bit10:cmdlist��9ͨ�����ж�
                                                       bit9:cmdlist��8ͨ�����ж�
                                                       bit8:cmdlist��7ͨ�����ж�
                                                       bit7:cmdlist��6ͨ�����ж�
                                                       bit6:cmdlist��5ͨ�����ж�
                                                       bit5:cmdlist��4ͨ�����ж�
                                                       bit4:cmdlist��3ͨ�����ж�
                                                       bit3:cmdlist��2ͨ�����ж�
                                                       bit2:cmdlist��1ͨ�����ж�
                                                       bit1:cmdlist��0ͨ�����ж�
                                                       bit0:rch_ce_ints */
        unsigned int  reserved     : 1;  /* bit[31]  : ���� */
    } reg;
} SOC_DSS_GLB_MCU_PDP_INTS_UNION;
#endif
#define SOC_DSS_GLB_MCU_PDP_INTS_mcu_pdp_ints_START  (0)
#define SOC_DSS_GLB_MCU_PDP_INTS_mcu_pdp_ints_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_MCU_PDP_INT_MSK_UNION
 �ṹ˵��  : MCU_PDP_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x210����ֵ:0x00000000�����:32
 �Ĵ���˵��: MCU�����ж�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_pdp_int_msk : 31; /* bit[0-30]: �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                          bit30:dss_glb_ints�ж�
                                                          bit29:mmu_irpt_s,mmu��ȫ�ж�
                                                          bit28:mmu_irpt_ns,mmu�ǰ�ȫ�ж�
                                                          bit27:dbg_mctl_ints
                                                          bit26:dbg_wch1_ints
                                                          bit25:dbg_wch0_ints
                                                          bit24:dbg_rch7_ints
                                                          bit23:dbg_rch6_ints
                                                          bit22:dbg_rch5_ints
                                                          bit21:dbg_rch4_ints
                                                          bit20:dbg_rch3_ints
                                                          bit19:dbg_rch2_ints
                                                          bit18:dbg_rch1_ints
                                                          bit17:dbg_rch0_ints
                                                          bit16:itf0_ints
                                                          bit15:dpp_ints
                                                          bit14:cmdlist��13ͨ�����ж�
                                                          bit13:cmdlist��12ͨ�����ж�
                                                          bit12:cmdlist��11ͨ�����ж�
                                                          bit11:cmdlist��10ͨ�����ж�
                                                          bit10:cmdlist��9ͨ�����ж�
                                                          bit9:cmdlist��8ͨ�����ж�
                                                          bit8:cmdlist��7ͨ�����ж�
                                                          bit7:cmdlist��6ͨ�����ж�
                                                          bit6:cmdlist��5ͨ�����ж�
                                                          bit5:cmdlist��4ͨ�����ж�
                                                          bit4:cmdlist��3ͨ�����ж�
                                                          bit3:cmdlist��2ͨ�����ж�
                                                          bit2:cmdlist��1ͨ�����ж�
                                                          bit1:cmdlist��0ͨ�����ж�
                                                          bit0:rch_ce_ints */
        unsigned int  reserved        : 1;  /* bit[31]  : ���� */
    } reg;
} SOC_DSS_GLB_MCU_PDP_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_MCU_PDP_INT_MSK_mcu_pdp_int_msk_START  (0)
#define SOC_DSS_GLB_MCU_PDP_INT_MSK_mcu_pdp_int_msk_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_MCU_SDP_INTS_UNION
 �ṹ˵��  : MCU_SDP_INTS �Ĵ����ṹ���塣��ַƫ����:0x214����ֵ:0x00000000�����:32
 �Ĵ���˵��: MCU�����ж�ָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_sdp_ints : 30; /* bit[0-29] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                        bit29:dss_glb_ints�ж�
                                                        bit28:mmu_irpt_s,mmu��ȫ�ж�
                                                        bit27:mmu_irpt_ns,mmu�ǰ�ȫ�ж�
                                                        bit26:dbg_mctl_ints
                                                        bit25:dbg_wch1_ints
                                                        bit24:dbg_wch0_ints
                                                        bit23:dbg_rch7_ints
                                                        bit22:dbg_rch6_ints
                                                        bit21:dbg_rch5_ints
                                                        bit20:dbg_rch4_ints
                                                        bit19:dbg_rch3_ints
                                                        bit18:dbg_rch2_ints
                                                        bit17:dbg_rch1_ints
                                                        bit16:dbg_rch0_ints
                                                        bit15:itf1_ints
                                                        bit14:cmdlist��13ͨ�����ж�
                                                        bit13:cmdlist��12ͨ�����ж�
                                                        bit12:cmdlist��11ͨ�����ж�
                                                        bit11:cmdlist��10ͨ�����ж�
                                                        bit10:cmdlist��9ͨ�����ж�
                                                        bit9:cmdlist��8ͨ�����ж�
                                                        bit8:cmdlist��7ͨ�����ж�
                                                        bit7:cmdlist��6ͨ�����ж�
                                                        bit6:cmdlist��5ͨ�����ж�
                                                        bit5:cmdlist��4ͨ�����ж�
                                                        bit4:cmdlist��3ͨ�����ж�
                                                        bit3:cmdlist��2ͨ�����ж�
                                                        bit2:cmdlist��1ͨ�����ж�
                                                        bit1:cmdlist��0ͨ�����ж�
                                                        bit0:rch_ce_ints */
        unsigned int  reserved     : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_MCU_SDP_INTS_UNION;
#endif
#define SOC_DSS_GLB_MCU_SDP_INTS_mcu_sdp_ints_START  (0)
#define SOC_DSS_GLB_MCU_SDP_INTS_mcu_sdp_ints_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_MCU_SDP_INT_MSK_UNION
 �ṹ˵��  : MCU_SDP_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x218����ֵ:0x00000000�����:32
 �Ĵ���˵��: MCU�����ж�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_sdp_int_msk : 30; /* bit[0-29] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                           bit29:dss_glb_ints�ж�
                                                           bit28:mmu_irpt_s,mmu��ȫ�ж�
                                                           bit27:mmu_irpt_ns,mmu�ǰ�ȫ�ж�
                                                           bit26:dbg_mctl_ints
                                                           bit25:dbg_wch1_ints
                                                           bit24:dbg_wch0_ints
                                                           bit23:dbg_rch7_ints
                                                           bit22:dbg_rch6_ints
                                                           bit21:dbg_rch5_ints
                                                           bit20:dbg_rch4_ints
                                                           bit19:dbg_rch3_ints
                                                           bit18:dbg_rch2_ints
                                                           bit17:dbg_rch1_ints
                                                           bit16:dbg_rch0_ints
                                                           bit15:itf1_ints
                                                           bit14:cmdlist��13ͨ�����ж�
                                                           bit13:cmdlist��12ͨ�����ж�
                                                           bit12:cmdlist��11ͨ�����ж�
                                                           bit11:cmdlist��10ͨ�����ж�
                                                           bit10:cmdlist��9ͨ�����ж�
                                                           bit9:cmdlist��8ͨ�����ж�
                                                           bit8:cmdlist��7ͨ�����ж�
                                                           bit7:cmdlist��6ͨ�����ж�
                                                           bit6:cmdlist��5ͨ�����ж�
                                                           bit5:cmdlist��4ͨ�����ж�
                                                           bit4:cmdlist��3ͨ�����ж�
                                                           bit3:cmdlist��2ͨ�����ж�
                                                           bit2:cmdlist��1ͨ�����ж�
                                                           bit1:cmdlist��0ͨ�����ж�
                                                           bit0:rch_ce_ints */
        unsigned int  reserved        : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_MCU_SDP_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_MCU_SDP_INT_MSK_mcu_sdp_int_msk_START  (0)
#define SOC_DSS_GLB_MCU_SDP_INT_MSK_mcu_sdp_int_msk_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_MCU_OFF_INTS_UNION
 �ṹ˵��  : MCU_OFF_INTS �Ĵ����ṹ���塣��ַƫ����:0x21C����ֵ:0x00000000�����:32
 �Ĵ���˵��: MCU�����ж�ָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_off_ints : 32; /* bit[0-31]: �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                       bit31:dss_glb_ints�ж�
                                                       bit30:mmu_irpt_s,mmu��ȫ�ж�
                                                       bit29:mmu_irpt_ns,mmu�ǰ�ȫ�ж�
                                                       bit28:dbg_mctl_ints
                                                       bit27:dbg_wch1_ints
                                                       bit26:dbg_wch0_ints
                                                       bit25:dbg_rch7_ints
                                                       bit24:dbg_rch6_ints
                                                       bit23:dbg_rch5_ints
                                                       bit22:dbg_rch4_ints
                                                       bit21:dbg_rch3_ints
                                                       bit10:dbg_rch2_ints
                                                       bit19:dbg_rch1_ints
                                                       bit18:dbg_rch0_ints
                                                       bit17:wch1_ints wch1��frm_end�ж�
                                                       bit16:wch0_ints wch0��frm_end�ж�
                                                       bit15:wch0��wch1ͬʱfrm_endʱ�������ж�
                                                       bit14:cmdlist��13ͨ�����ж�
                                                       bit13:cmdlist��12ͨ�����ж�
                                                       bit12:cmdlist��11ͨ�����ж�
                                                       bit11:cmdlist��10ͨ�����ж�
                                                       bit10:cmdlist��9ͨ�����ж�
                                                       bit9:cmdlist��8ͨ�����ж�
                                                       bit8:cmdlist��7ͨ�����ж�
                                                       bit7:cmdlist��6ͨ�����ж�
                                                       bit6:cmdlist��5ͨ�����ж�
                                                       bit5:cmdlist��4ͨ�����ж�
                                                       bit4:cmdlist��3ͨ�����ж�
                                                       bit3:cmdlist��2ͨ�����ж�
                                                       bit2:cmdlist��1ͨ�����ж�
                                                       bit1:cmdlist��0ͨ�����ж�
                                                       bit0:rch_ce_ints */
    } reg;
} SOC_DSS_GLB_MCU_OFF_INTS_UNION;
#endif
#define SOC_DSS_GLB_MCU_OFF_INTS_mcu_off_ints_START  (0)
#define SOC_DSS_GLB_MCU_OFF_INTS_mcu_off_ints_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_MCU_OFF_INT_MSK_UNION
 �ṹ˵��  : MCU_OFF_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x220����ֵ:0x00000000�����:32
 �Ĵ���˵��: MCU�����ж�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mcu_off_int_msk : 32; /* bit[0-31]: �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                          bit31:dss_glb_ints�ж�
                                                          bit30:mmu_irpt_s,mmu��ȫ�ж�
                                                          bit29:mmu_irpt_ns,mmu�ǰ�ȫ�ж�
                                                          bit28:dbg_mctl_ints
                                                          bit27:dbg_wch1_ints
                                                          bit26:dbg_wch0_ints
                                                          bit25:dbg_rch7_ints
                                                          bit24:dbg_rch6_ints
                                                          bit23:dbg_rch5_ints
                                                          bit22:dbg_rch4_ints
                                                          bit21:dbg_rch3_ints
                                                          bit10:dbg_rch2_ints
                                                          bit19:dbg_rch1_ints
                                                          bit18:dbg_rch0_ints
                                                          bit17:wch1_ints wch1��frm_end�ж�
                                                          bit16:wch0_ints wch0��frm_end�ж�
                                                          bit15:wch0��wch1ͬʱfrm_endʱ�������ж�
                                                          bit14:cmdlist��13ͨ�����ж�
                                                          bit13:cmdlist��12ͨ�����ж�
                                                          bit12:cmdlist��11ͨ�����ж�
                                                          bit11:cmdlist��10ͨ�����ж�
                                                          bit10:cmdlist��9ͨ�����ж�
                                                          bit9:cmdlist��8ͨ�����ж�
                                                          bit8:cmdlist��7ͨ�����ж�
                                                          bit7:cmdlist��6ͨ�����ж�
                                                          bit6:cmdlist��5ͨ�����ж�
                                                          bit5:cmdlist��4ͨ�����ж�
                                                          bit4:cmdlist��3ͨ�����ж�
                                                          bit3:cmdlist��2ͨ�����ж�
                                                          bit2:cmdlist��1ͨ�����ж�
                                                          bit1:cmdlist��0ͨ�����ж�
                                                          bit0:rch_ce_ints */
    } reg;
} SOC_DSS_GLB_MCU_OFF_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_MCU_OFF_INT_MSK_mcu_off_int_msk_START  (0)
#define SOC_DSS_GLB_MCU_OFF_INT_MSK_mcu_off_int_msk_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CPU_PDP_INTS_UNION
 �ṹ˵��  : CPU_PDP_INTS �Ĵ����ṹ���塣��ַƫ����:0x224����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU�����ж�ָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_pdp_ints : 31; /* bit[0-30]: �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                       bit30:dss_glb_ints�ж�
                                                       bit29:mmu_irpt_s,mmu��ȫ�ж�
                                                       bit28:mmu_irpt_ns,mmu�ǰ�ȫ�ж�
                                                       bit27:dbg_mctl_ints
                                                       bit26:dbg_wch1_ints
                                                       bit25:dbg_wch0_ints
                                                       bit24:dbg_rch7_ints
                                                       bit23:dbg_rch6_ints
                                                       bit22:dbg_rch5_ints
                                                       bit21:dbg_rch4_ints
                                                       bit20:dbg_rch3_ints
                                                       bit19:dbg_rch2_ints
                                                       bit18:dbg_rch1_ints
                                                       bit17:dbg_rch0_ints
                                                       bit16:itf0_ints
                                                       bit15:dpp_ints
                                                       bit14:cmdlist��13ͨ�����ж�
                                                       bit13:cmdlist��12ͨ�����ж�
                                                       bit12:cmdlist��11ͨ�����ж�
                                                       bit11:cmdlist��10ͨ�����ж�
                                                       bit10:cmdlist��9ͨ�����ж�
                                                       bit9:cmdlist��8ͨ�����ж�
                                                       bit8:cmdlist��7ͨ�����ж�
                                                       bit7:cmdlist��6ͨ�����ж�
                                                       bit6:cmdlist��5ͨ�����ж�
                                                       bit5:cmdlist��4ͨ�����ж�
                                                       bit4:cmdlist��3ͨ�����ж�
                                                       bit3:cmdlist��2ͨ�����ж�
                                                       bit2:cmdlist��1ͨ�����ж�
                                                       bit1:cmdlist��0ͨ�����ж�
                                                       bit0:rch_ce_ints */
        unsigned int  reserved     : 1;  /* bit[31]  : ���� */
    } reg;
} SOC_DSS_GLB_CPU_PDP_INTS_UNION;
#endif
#define SOC_DSS_GLB_CPU_PDP_INTS_cpu_pdp_ints_START  (0)
#define SOC_DSS_GLB_CPU_PDP_INTS_cpu_pdp_ints_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CPU_PDP_INT_MSK_UNION
 �ṹ˵��  : CPU_PDP_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x228����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU�����ж�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_pdp_int_msk : 31; /* bit[0-30]: �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                          bit30:dss_glb_ints�ж�
                                                          bit29:mmu_irpt_s,mmu��ȫ�ж�
                                                          bit28:mmu_irpt_ns,mmu�ǰ�ȫ�ж�
                                                          bit27:dbg_mctl_ints
                                                          bit26:dbg_wch1_ints
                                                          bit25:dbg_wch0_ints
                                                          bit24:dbg_rch7_ints
                                                          bit23:dbg_rch6_ints
                                                          bit22:dbg_rch5_ints
                                                          bit21:dbg_rch4_ints
                                                          bit20:dbg_rch3_ints
                                                          bit19:dbg_rch2_ints
                                                          bit18:dbg_rch1_ints
                                                          bit17:dbg_rch0_ints
                                                          bit16:itf0_ints
                                                          bit15:dpp_ints
                                                          bit14:cmdlist��13ͨ�����ж�
                                                          bit13:cmdlist��12ͨ�����ж�
                                                          bit12:cmdlist��11ͨ�����ж�
                                                          bit11:cmdlist��10ͨ�����ж�
                                                          bit10:cmdlist��9ͨ�����ж�
                                                          bit9:cmdlist��8ͨ�����ж�
                                                          bit8:cmdlist��7ͨ�����ж�
                                                          bit7:cmdlist��6ͨ�����ж�
                                                          bit6:cmdlist��5ͨ�����ж�
                                                          bit5:cmdlist��4ͨ�����ж�
                                                          bit4:cmdlist��3ͨ�����ж�
                                                          bit3:cmdlist��2ͨ�����ж�
                                                          bit2:cmdlist��1ͨ�����ж�
                                                          bit1:cmdlist��0ͨ�����ж�
                                                          bit0:rch_ce_ints */
        unsigned int  reserved        : 1;  /* bit[31]  : ���� */
    } reg;
} SOC_DSS_GLB_CPU_PDP_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_CPU_PDP_INT_MSK_cpu_pdp_int_msk_START  (0)
#define SOC_DSS_GLB_CPU_PDP_INT_MSK_cpu_pdp_int_msk_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CPU_SDP_INTS_UNION
 �ṹ˵��  : CPU_SDP_INTS �Ĵ����ṹ���塣��ַƫ����:0x22C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU�����ж�ָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_sdp_ints : 30; /* bit[0-29] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                        bit29:dss_glb_ints�ж�
                                                        bit28:mmu_irpt_s,mmu��ȫ�ж�
                                                        bit27:mmu_irpt_ns,mmu�ǰ�ȫ�ж�
                                                        bit26:dbg_mctl_ints
                                                        bit25:dbg_wch1_ints
                                                        bit24:dbg_wch0_ints
                                                        bit23:dbg_rch7_ints
                                                        bit22:dbg_rch6_ints
                                                        bit21:dbg_rch5_ints
                                                        bit20:dbg_rch4_ints
                                                        bit19:dbg_rch3_ints
                                                        bit18:dbg_rch2_ints
                                                        bit17:dbg_rch1_ints
                                                        bit16:dbg_rch0_ints
                                                        bit15:itf1_ints
                                                        bit14:cmdlist��13ͨ�����ж�
                                                        bit13:cmdlist��12ͨ�����ж�
                                                        bit12:cmdlist��11ͨ�����ж�
                                                        bit11:cmdlist��10ͨ�����ж�
                                                        bit10:cmdlist��9ͨ�����ж�
                                                        bit9:cmdlist��8ͨ�����ж�
                                                        bit8:cmdlist��7ͨ�����ж�
                                                        bit7:cmdlist��6ͨ�����ж�
                                                        bit6:cmdlist��5ͨ�����ж�
                                                        bit5:cmdlist��4ͨ�����ж�
                                                        bit4:cmdlist��3ͨ�����ж�
                                                        bit3:cmdlist��2ͨ�����ж�
                                                        bit2:cmdlist��1ͨ�����ж�
                                                        bit1:cmdlist��0ͨ�����ж�
                                                        bit0:rch_ce_ints */
        unsigned int  reserved     : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_CPU_SDP_INTS_UNION;
#endif
#define SOC_DSS_GLB_CPU_SDP_INTS_cpu_sdp_ints_START  (0)
#define SOC_DSS_GLB_CPU_SDP_INTS_cpu_sdp_ints_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CPU_SDP_INT_MSK_UNION
 �ṹ˵��  : CPU_SDP_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x230����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU�����ж�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_sdp_int_msk : 30; /* bit[0-29] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                           bit29:dss_glb_ints�ж�
                                                           bit28:mmu_irpt_s,mmu��ȫ�ж�
                                                           bit27:mmu_irpt_ns,mmu�ǰ�ȫ�ж�
                                                           bit26:dbg_mctl_ints
                                                           bit25:dbg_wch1_ints
                                                           bit24:dbg_wch0_ints
                                                           bit23:dbg_rch7_ints
                                                           bit22:dbg_rch6_ints
                                                           bit21:dbg_rch5_ints
                                                           bit20:dbg_rch4_ints
                                                           bit19:dbg_rch3_ints
                                                           bit18:dbg_rch2_ints
                                                           bit17:dbg_rch1_ints
                                                           bit16:dbg_rch0_ints
                                                           bit15:itf1_ints
                                                           bit14:cmdlist��13ͨ�����ж�
                                                           bit13:cmdlist��12ͨ�����ж�
                                                           bit12:cmdlist��11ͨ�����ж�
                                                           bit11:cmdlist��10ͨ�����ж�
                                                           bit10:cmdlist��9ͨ�����ж�
                                                           bit9:cmdlist��8ͨ�����ж�
                                                           bit8:cmdlist��7ͨ�����ж�
                                                           bit7:cmdlist��6ͨ�����ж�
                                                           bit6:cmdlist��5ͨ�����ж�
                                                           bit5:cmdlist��4ͨ�����ж�
                                                           bit4:cmdlist��3ͨ�����ж�
                                                           bit3:cmdlist��2ͨ�����ж�
                                                           bit2:cmdlist��1ͨ�����ж�
                                                           bit1:cmdlist��0ͨ�����ж�
                                                           bit0:rch_ce_ints */
        unsigned int  reserved        : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_CPU_SDP_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_CPU_SDP_INT_MSK_cpu_sdp_int_msk_START  (0)
#define SOC_DSS_GLB_CPU_SDP_INT_MSK_cpu_sdp_int_msk_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CPU_OFF_INTS_UNION
 �ṹ˵��  : CPU_OFF_INTS �Ĵ����ṹ���塣��ַƫ����:0x234����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU�����ж�ָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_off_ints : 32; /* bit[0-31]: �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                       bit31:dss_glb_ints�ж�
                                                       bit30:mmu_irpt_s,mmu��ȫ�ж�
                                                       bit29:mmu_irpt_ns,mmu�ǰ�ȫ�ж�
                                                       bit28:dbg_mctl_ints
                                                       bit27:dbg_wch1_ints
                                                       bit26:dbg_wch0_ints
                                                       bit25:dbg_rch7_ints
                                                       bit24:dbg_rch6_ints
                                                       bit23:dbg_rch5_ints
                                                       bit22:dbg_rch4_ints
                                                       bit21:dbg_rch3_ints
                                                       bit10:dbg_rch2_ints
                                                       bit19:dbg_rch1_ints
                                                       bit18:dbg_rch0_ints
                                                       bit17:wch1_ints wch1��frm_end�ж�
                                                       bit16:wch0_ints wch0��frm_end�ж�
                                                       bit15:wch0��wch1ͬʱfrm_endʱ�������ж�
                                                       bit14:cmdlist��13ͨ�����ж�
                                                       bit13:cmdlist��12ͨ�����ж�
                                                       bit12:cmdlist��11ͨ�����ж�
                                                       bit11:cmdlist��10ͨ�����ж�
                                                       bit10:cmdlist��9ͨ�����ж�
                                                       bit9:cmdlist��8ͨ�����ж�
                                                       bit8:cmdlist��7ͨ�����ж�
                                                       bit7:cmdlist��6ͨ�����ж�
                                                       bit6:cmdlist��5ͨ�����ж�
                                                       bit5:cmdlist��4ͨ�����ж�
                                                       bit4:cmdlist��3ͨ�����ж�
                                                       bit3:cmdlist��2ͨ�����ж�
                                                       bit2:cmdlist��1ͨ�����ж�
                                                       bit1:cmdlist��0ͨ�����ж�
                                                       bit0:rch_ce_ints */
    } reg;
} SOC_DSS_GLB_CPU_OFF_INTS_UNION;
#endif
#define SOC_DSS_GLB_CPU_OFF_INTS_cpu_off_ints_START  (0)
#define SOC_DSS_GLB_CPU_OFF_INTS_cpu_off_ints_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CPU_OFF_INT_MSK_UNION
 �ṹ˵��  : CPU_OFF_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x238����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU�����ж�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cpu_off_int_msk : 32; /* bit[0-31]: �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                          bit31:dss_glb_ints�ж�
                                                          bit30:mmu_irpt_s,mmu��ȫ�ж�
                                                          bit29:mmu_irpt_ns,mmu�ǰ�ȫ�ж�
                                                          bit28:dbg_mctl_ints
                                                          bit27:dbg_wch1_ints
                                                          bit26:dbg_wch0_ints
                                                          bit25:dbg_rch7_ints
                                                          bit24:dbg_rch6_ints
                                                          bit23:dbg_rch5_ints
                                                          bit22:dbg_rch4_ints
                                                          bit21:dbg_rch3_ints
                                                          bit10:dbg_rch2_ints
                                                          bit19:dbg_rch1_ints
                                                          bit18:dbg_rch0_ints
                                                          bit17:wch1_ints wch1��frm_end�ж�
                                                          bit16:wch0_ints wch0��frm_end�ж�
                                                          bit15:wch0��wch1ͬʱfrm_endʱ�������ж�
                                                          bit14:cmdlist��13ͨ�����ж�
                                                          bit13:cmdlist��12ͨ�����ж�
                                                          bit12:cmdlist��11ͨ�����ж�
                                                          bit11:cmdlist��10ͨ�����ж�
                                                          bit10:cmdlist��9ͨ�����ж�
                                                          bit9:cmdlist��8ͨ�����ж�
                                                          bit8:cmdlist��7ͨ�����ж�
                                                          bit7:cmdlist��6ͨ�����ж�
                                                          bit6:cmdlist��5ͨ�����ж�
                                                          bit5:cmdlist��4ͨ�����ж�
                                                          bit4:cmdlist��3ͨ�����ж�
                                                          bit3:cmdlist��2ͨ�����ж�
                                                          bit2:cmdlist��1ͨ�����ж�
                                                          bit1:cmdlist��0ͨ�����ж�
                                                          bit0:rch_ce_ints */
    } reg;
} SOC_DSS_GLB_CPU_OFF_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_CPU_OFF_INT_MSK_cpu_off_int_msk_START  (0)
#define SOC_DSS_GLB_CPU_OFF_INT_MSK_cpu_off_int_msk_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_MCTL_INTS_UNION
 �ṹ˵��  : DBG_MCTL_INTS �Ĵ����ṹ���塣��ַƫ����:0x23C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ж�ָʾ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_mctl_ints : 8;  /* bit[0-7] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                        bti7:ctl7_start
                                                        bti6:ctl6_start
                                                        bti5:ctl5_start
                                                        bti4:ctl4_start
                                                        bti3:ctl3_start
                                                        bti2:ctl2_start
                                                        bti1:ctl1_start
                                                        bti0:ctl0_start */
        unsigned int  reserved      : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_MCTL_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_MCTL_INTS_dbg_mctl_ints_START  (0)
#define SOC_DSS_GLB_DBG_MCTL_INTS_dbg_mctl_ints_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_MCTL_INT_MSK_UNION
 �ṹ˵��  : DBG_MCTL_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x240����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ж�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_mctl_int_msk : 8;  /* bit[0-7] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                           bti7:ctl7_start
                                                           bti6:ctl6_start
                                                           bti5:ctl5_start
                                                           bti4:ctl4_start
                                                           bti3:ctl3_start
                                                           bti2:ctl2_start
                                                           bti1:ctl1_start
                                                           bti0:ctl0_start */
        unsigned int  reserved         : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_MCTL_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_MCTL_INT_MSK_dbg_mctl_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_MCTL_INT_MSK_dbg_mctl_int_msk_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_WCH0_INTS_UNION
 �ṹ˵��  : DBG_WCH0_INTS �Ĵ����ṹ���塣��ַƫ����:0x244����ֵ:0x00000000�����:32
 �Ĵ���˵��: дͨ��0�ж�ָʾ�������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_wch0_ints : 14; /* bit[0-13] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                         bit13: wch������ж�
                                                         bit12~2: reserve
                                                         bit1: dma֡�����ж�
                                                         bit0: afbce��resp_err�ж��ϱ� */
        unsigned int  reserved      : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_WCH0_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_WCH0_INTS_dbg_wch0_ints_START  (0)
#define SOC_DSS_GLB_DBG_WCH0_INTS_dbg_wch0_ints_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_WCH0_INT_MSK_UNION
 �ṹ˵��  : DBG_WCH0_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x248����ֵ:0x00000000�����:32
 �Ĵ���˵��: дͨ��0�ж����Σ������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_wch0_int_msk : 14; /* bit[0-13] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                            bit13: wch������ж�
                                                            bit12~2: reserve
                                                            bit1: dma֡�����ж�
                                                            bit0: afbce��resp_err�ж��ϱ� */
        unsigned int  reserved         : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_WCH0_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_WCH0_INT_MSK_dbg_wch0_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_WCH0_INT_MSK_dbg_wch0_int_msk_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_WCH1_INTS_UNION
 �ṹ˵��  : DBG_WCH1_INTS �Ĵ����ṹ���塣��ַƫ����:0x24C����ֵ:0x00000000�����:32
 �Ĵ���˵��: дͨ��1�ж�ָʾ�������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_wch1_ints : 14; /* bit[0-13] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                         bit13: wch������ж�
                                                         bit12~2: reserve
                                                         bit1: dma֡�����ж�
                                                         bit0: afbce��resp_err�ж��ϱ� */
        unsigned int  reserved      : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_WCH1_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_WCH1_INTS_dbg_wch1_ints_START  (0)
#define SOC_DSS_GLB_DBG_WCH1_INTS_dbg_wch1_ints_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_WCH1_INT_MSK_UNION
 �ṹ˵��  : DBG_WCH1_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x250����ֵ:0x00000000�����:32
 �Ĵ���˵��: дͨ��1�ж����Σ������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_wch1_int_msk : 14; /* bit[0-13] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                            bit13: wch������ж�
                                                            bit12~2: reserve
                                                            bit1: dma֡�����ж�
                                                            bit0: afbce��resp_err�ж��ϱ� */
        unsigned int  reserved         : 18; /* bit[14-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_WCH1_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_WCH1_INT_MSK_dbg_wch1_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_WCH1_INT_MSK_dbg_wch1_int_msk_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH0_INTS_UNION
 �ṹ˵��  : DBG_RCH0_INTS �Ĵ����ṹ���塣��ַƫ����:0x254����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��0�ж�ָʾ�������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch0_ints : 30; /* bit[0-29] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                         bit14~29: reserve
                                                         bit13: CE LUT1��д��ͻ
                                                         bit12: CE LUT0��д��ͻ
                                                         bit11: CE ֱ��ͼ1��д��ͻ
                                                         bit10: CE ֱ��ͼ0��д��ͻ
                                                         bit9: rdma֡�����ж�
                                                         bit8: rch֡�����ж�
                                                         bit5~7:rdma�ڲ�err�ж�
                                                         bit4: rdma��resp_err�ж�
                                                         bit0~3:afbcd���ж� */
        unsigned int  reserved      : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH0_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH0_INTS_dbg_rch0_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH0_INTS_dbg_rch0_ints_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH0_INT_MSK_UNION
 �ṹ˵��  : DBG_RCH0_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x258����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��0�ж����Σ������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch0_int_msk : 30; /* bit[0-29] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                            bit14~29: reserve
                                                            bit13: CE LUT1��д��ͻ
                                                            bit12: CE LUT0��д��ͻ
                                                            bit11: CE ֱ��ͼ1��д��ͻ
                                                            bit10: CE ֱ��ͼ0��д��ͻ
                                                            bit9: rdma֡�����ж�
                                                            bit8: rch֡�����ж�
                                                            bit5~7:rdma�ڲ�err�ж�
                                                            bit4: rdma��resp_err�ж�
                                                            bit0~3:afbcd���ж� */
        unsigned int  reserved         : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH0_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH0_INT_MSK_dbg_rch0_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH0_INT_MSK_dbg_rch0_int_msk_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH1_INTS_UNION
 �ṹ˵��  : DBG_RCH1_INTS �Ĵ����ṹ���塣��ַƫ����:0x25C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��1�ж�ָʾ�������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch1_ints : 30; /* bit[0-29] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                         bit14~29: reserve
                                                         bit13: CE LUT1��д��ͻ
                                                         bit12: CE LUT0��д��ͻ
                                                         bit11: CE ֱ��ͼ1��д��ͻ
                                                         bit10: CE ֱ��ͼ0��д��ͻ
                                                         bit9: rdma֡�����ж�
                                                         bit8: rch֡�����ж�
                                                         bit5~7:rdma�ڲ�err�ж�
                                                         bit4: rdma��resp_err�ж�
                                                         bit0~3:afbcd���ж� */
        unsigned int  reserved      : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH1_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH1_INTS_dbg_rch1_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH1_INTS_dbg_rch1_ints_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH1_INT_MSK_UNION
 �ṹ˵��  : DBG_RCH1_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x260����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��1�ж����Σ������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch1_int_msk : 30; /* bit[0-29] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                            bit14~29: reserve
                                                            bit13: CE LUT1��д��ͻ
                                                            bit12: CE LUT0��д��ͻ
                                                            bit11: CE ֱ��ͼ1��д��ͻ
                                                            bit10: CE ֱ��ͼ0��д��ͻ
                                                            bit9: rdma֡�����ж�
                                                            bit8: rch֡�����ж�
                                                            bit5~7:rdma�ڲ�err�ж�
                                                            bit4: rdma��resp_err�ж�
                                                            bit0~3:afbcd���ж� */
        unsigned int  reserved         : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH1_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH1_INT_MSK_dbg_rch1_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH1_INT_MSK_dbg_rch1_int_msk_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH2_INTS_UNION
 �ṹ˵��  : DBG_RCH2_INTS �Ĵ����ṹ���塣��ַƫ����:0x264����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��2�ж�ָʾ�������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch2_ints : 30; /* bit[0-29] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                         bit14~29: reserve
                                                         bit13: CE LUT1��д��ͻ
                                                         bit12: CE LUT0��д��ͻ
                                                         bit11: CE ֱ��ͼ1��д��ͻ
                                                         bit10: CE ֱ��ͼ0��д��ͻ
                                                         bit9: rdma֡�����ж�
                                                         bit8: rch֡�����ж�
                                                         bit5~7:rdma�ڲ�err�ж�
                                                         bit4: rdma��resp_err�ж�
                                                         bit0~3:afbcd���ж� */
        unsigned int  reserved      : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH2_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH2_INTS_dbg_rch2_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH2_INTS_dbg_rch2_ints_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH2_INT_MSK_UNION
 �ṹ˵��  : DBG_RCH2_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x268����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��2�ж����Σ������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch2_int_msk : 30; /* bit[0-29] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                            bit14~29: reserve
                                                            bit13: CE LUT1��д��ͻ
                                                            bit12: CE LUT0��д��ͻ
                                                            bit11: CE ֱ��ͼ1��д��ͻ
                                                            bit10: CE ֱ��ͼ0��д��ͻ
                                                            bit9: rdma֡�����ж�
                                                            bit8: rch֡�����ж�
                                                            bit5~7:rdma�ڲ�err�ж�
                                                            bit4: rdma��resp_err�ж�
                                                            bit0~3:afbcd���ж� */
        unsigned int  reserved         : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH2_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH2_INT_MSK_dbg_rch2_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH2_INT_MSK_dbg_rch2_int_msk_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH3_INTS_UNION
 �ṹ˵��  : DBG_RCH3_INTS �Ĵ����ṹ���塣��ַƫ����:0x26C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��3�ж�ָʾ�������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch3_ints : 30; /* bit[0-29] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                         bit14~29: reserve
                                                         bit13: CE LUT1��д��ͻ
                                                         bit12: CE LUT0��д��ͻ
                                                         bit11: CE ֱ��ͼ1��д��ͻ
                                                         bit10: CE ֱ��ͼ0��д��ͻ
                                                         bit9: rdma֡�����ж�
                                                         bit8: rch֡�����ж�
                                                         bit5~7:rdma�ڲ�err�ж�
                                                         bit4: rdma��resp_err�ж�
                                                         bit0~3:afbcd���ж� */
        unsigned int  reserved      : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH3_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH3_INTS_dbg_rch3_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH3_INTS_dbg_rch3_ints_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH3_INT_MSK_UNION
 �ṹ˵��  : DBG_RCH3_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x270����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��3�ж����Σ������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch3_int_msk : 30; /* bit[0-29] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                            bit14~29: reserve
                                                            bit13: CE LUT1��д��ͻ
                                                            bit12: CE LUT0��д��ͻ
                                                            bit11: CE ֱ��ͼ1��д��ͻ
                                                            bit10: CE ֱ��ͼ0��д��ͻ
                                                            bit9: rdma֡�����ж�
                                                            bit8: rch֡�����ж�
                                                            bit5~7:rdma�ڲ�err�ж�
                                                            bit4: rdma��resp_err�ж�
                                                            bit0~3:afbcd���ж� */
        unsigned int  reserved         : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH3_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH3_INT_MSK_dbg_rch3_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH3_INT_MSK_dbg_rch3_int_msk_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH4_INTS_UNION
 �ṹ˵��  : DBG_RCH4_INTS �Ĵ����ṹ���塣��ַƫ����:0x274����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��4�ж�ָʾ�������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch4_ints : 30; /* bit[0-29] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                         bit14~29: reserve
                                                         bit13: CE LUT1��д��ͻ
                                                         bit12: CE LUT0��д��ͻ
                                                         bit11: CE ֱ��ͼ1��д��ͻ
                                                         bit10: CE ֱ��ͼ0��д��ͻ
                                                         bit9: rdma֡�����ж�
                                                         bit8: rch֡�����ж�
                                                         bit5~7:rdma�ڲ�err�ж�
                                                         bit4: rdma��resp_err�ж�
                                                         bit0~3:afbcd���ж� */
        unsigned int  reserved      : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH4_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH4_INTS_dbg_rch4_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH4_INTS_dbg_rch4_ints_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH4_INT_MSK_UNION
 �ṹ˵��  : DBG_RCH4_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x278����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��4�ж����Σ������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch4_int_msk : 30; /* bit[0-29] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                            bit14~29: reserve
                                                            bit13: CE LUT1��д��ͻ
                                                            bit12: CE LUT0��д��ͻ
                                                            bit11: CE ֱ��ͼ1��д��ͻ
                                                            bit10: CE ֱ��ͼ0��д��ͻ
                                                            bit9: rdma֡�����ж�
                                                            bit8: rch֡�����ж�
                                                            bit5~7:rdma�ڲ�err�ж�
                                                            bit4: rdma��resp_err�ж�
                                                            bit0~3:afbcd���ж� */
        unsigned int  reserved         : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH4_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH4_INT_MSK_dbg_rch4_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH4_INT_MSK_dbg_rch4_int_msk_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH5_INTS_UNION
 �ṹ˵��  : DBG_RCH5_INTS �Ĵ����ṹ���塣��ַƫ����:0x27C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��5�ж�ָʾ�������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch5_ints : 30; /* bit[0-29] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                         bit14~29: reserve
                                                         bit13: CE LUT1��д��ͻ
                                                         bit12: CE LUT0��д��ͻ
                                                         bit11: CE ֱ��ͼ1��д��ͻ
                                                         bit10: CE ֱ��ͼ0��д��ͻ
                                                         bit9: rdma֡�����ж�
                                                         bit8: rch֡�����ж�
                                                         bit5~7:rdma�ڲ�err�ж�
                                                         bit4: rdma��resp_err�ж�
                                                         bit0~3:afbcd���ж� */
        unsigned int  reserved      : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH5_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH5_INTS_dbg_rch5_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH5_INTS_dbg_rch5_ints_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH5_INT_MSK_UNION
 �ṹ˵��  : DBG_RCH5_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x280����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��5�ж����Σ������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch5_int_msk : 30; /* bit[0-29] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                            bit14~29: reserve
                                                            bit13: CE LUT1��д��ͻ
                                                            bit12: CE LUT0��д��ͻ
                                                            bit11: CE ֱ��ͼ1��д��ͻ
                                                            bit10: CE ֱ��ͼ0��д��ͻ
                                                            bit9: rdma֡�����ж�
                                                            bit8: rch֡�����ж�
                                                            bit5~7:rdma�ڲ�err�ж�
                                                            bit4: rdma��resp_err�ж�
                                                            bit0~3:afbcd���ж� */
        unsigned int  reserved         : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH5_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH5_INT_MSK_dbg_rch5_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH5_INT_MSK_dbg_rch5_int_msk_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH6_INTS_UNION
 �ṹ˵��  : DBG_RCH6_INTS �Ĵ����ṹ���塣��ַƫ����:0x284����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��6�ж�ָʾ�������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch6_ints : 30; /* bit[0-29] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                         bit14~29: reserve
                                                         bit13: CE LUT1��д��ͻ
                                                         bit12: CE LUT0��д��ͻ
                                                         bit11: CE ֱ��ͼ1��д��ͻ
                                                         bit10: CE ֱ��ͼ0��д��ͻ
                                                         bit9: rdma֡�����ж�
                                                         bit8: rch֡�����ж�
                                                         bit5~7:rdma�ڲ�err�ж�
                                                         bit4: rdma��resp_err�ж�
                                                         bit0~3:afbcd���ж� */
        unsigned int  reserved      : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH6_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH6_INTS_dbg_rch6_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH6_INTS_dbg_rch6_ints_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH6_INT_MSK_UNION
 �ṹ˵��  : DBG_RCH6_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x288����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��6�ж����Σ������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch6_int_msk : 30; /* bit[0-29] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                            bit14~29: reserve
                                                            bit13: CE LUT1��д��ͻ
                                                            bit12: CE LUT0��д��ͻ
                                                            bit11: CE ֱ��ͼ1��д��ͻ
                                                            bit10: CE ֱ��ͼ0��д��ͻ
                                                            bit9: rdma֡�����ж�
                                                            bit8: rch֡�����ж�
                                                            bit5~7:rdma�ڲ�err�ж�
                                                            bit4: rdma��resp_err�ж�
                                                            bit0~3:afbcd���ж� */
        unsigned int  reserved         : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH6_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH6_INT_MSK_dbg_rch6_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH6_INT_MSK_dbg_rch6_int_msk_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH7_INTS_UNION
 �ṹ˵��  : DBG_RCH7_INTS �Ĵ����ṹ���塣��ַƫ����:0x28C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��7�ж�ָʾ�������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch7_ints : 30; /* bit[0-29] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                         bit14~29: reserve
                                                         bit13: CE LUT1��д��ͻ
                                                         bit12: CE LUT0��д��ͻ
                                                         bit11: CE ֱ��ͼ1��д��ͻ
                                                         bit10: CE ֱ��ͼ0��д��ͻ
                                                         bit9: rdma֡�����ж�
                                                         bit8: rch֡�����ж�
                                                         bit5~7:rdma�ڲ�err�ж�
                                                         bit4: rdma��resp_err�ж�
                                                         bit0~3:afbcd���ж� */
        unsigned int  reserved      : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH7_INTS_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH7_INTS_dbg_rch7_ints_START  (0)
#define SOC_DSS_GLB_DBG_RCH7_INTS_dbg_rch7_ints_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_RCH7_INT_MSK_UNION
 �ṹ˵��  : DBG_RCH7_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x290����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ͨ��7�ж����Σ������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_rch7_int_msk : 30; /* bit[0-29] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                            bit14~29: reserve
                                                            bit13: CE LUT1��д��ͻ
                                                            bit12: CE LUT0��д��ͻ
                                                            bit11: CE ֱ��ͼ1��д��ͻ
                                                            bit10: CE ֱ��ͼ0��д��ͻ
                                                            bit9: rdma֡�����ж�
                                                            bit8: rch֡�����ж�
                                                            bit5~7:rdma�ڲ�err�ж�
                                                            bit4: rdma��resp_err�ж�
                                                            bit0~3:afbcd���ж� */
        unsigned int  reserved         : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_RCH7_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_DBG_RCH7_INT_MSK_dbg_rch7_int_msk_START  (0)
#define SOC_DSS_GLB_DBG_RCH7_INT_MSK_dbg_rch7_int_msk_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_INTS_UNION
 �ṹ˵��  : INTS �Ĵ����ṹ���塣��ַƫ����:0x294����ֵ:0x00000000�����:32
 �Ĵ���˵��: GLB�жϣ������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_glb_ints : 6;  /* bit[0-5] : �ж�״̬�Ĵ�����1��ʾ���жϣ�0��ʾû���ж�
                                                       bit5:bus_dbg_int GLB�ڲ���BUS_DBGģ���ж�
                                                       bit4:crc_sum_int GLB�ڲ���CRCģ���ж�
                                                       bit3:crc_itf1_int GLB�ڲ���CRCģ���ж�
                                                       bit2:crc_itf0_int GLB�ڲ���CRCģ���ж�
                                                       bit1:crc_ov1_int GLB�ڲ���CRCģ���ж�
                                                       bit0:crc_ov0_int GLB�ڲ���CRCģ���ж� */
        unsigned int  reserved     : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_GLB_INTS_UNION;
#endif
#define SOC_DSS_GLB_INTS_dss_glb_ints_START  (0)
#define SOC_DSS_GLB_INTS_dss_glb_ints_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_INT_MSK_UNION
 �ṹ˵��  : INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x298����ֵ:0x00000000�����:32
 �Ĵ���˵��: GLB�жϣ������ã�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_glb_int_msk : 6;  /* bit[0-5] : �ж����μĴ�����1��ʾ�����жϣ�0��ʾ�������ж�
                                                          bit5:bus_dbg_int GLB�ڲ���BUS_DBGģ���ж�
                                                          bit4:crc_sum_int GLB�ڲ���CRCģ���ж�
                                                          bit3:crc_itf1_int GLB�ڲ���CRCģ���ж�
                                                          bit2:crc_itf0_int GLB�ڲ���CRCģ���ж�
                                                          bit1:crc_ov1_int GLB�ڲ���CRCģ���ж�
                                                          bit0:crc_ov0_int GLB�ڲ���CRCģ���ж� */
        unsigned int  reserved        : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_GLB_INT_MSK_UNION;
#endif
#define SOC_DSS_GLB_INT_MSK_dss_glb_int_msk_START  (0)
#define SOC_DSS_GLB_INT_MSK_dss_glb_int_msk_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_MODULE_CLK_SEL_UNION
 �ṹ˵��  : MODULE_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0300����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ�����ʱ��ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  module_clk_sel : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                         1����ʾǿ�ƴ�ʱ�ӡ�
                                                         0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ��
                                                         bit0: cmdlistģ���axiʱ����
                                                         bit1��vbifģ���coreʱ����
                                                         bit2��vbifģ���axiʱ����
                                                         bit3��apbģ���pclkʱ����
                                                         bit4��apbģ���pxl0ʱ����
                                                         bit5��apbģ���axiʱ����
                                                         bit6��apbģ���pxl1ʱ����
                                                         bit7��apbģ���coreʱ����
                                                         bit8��rch0ģ���coreʱ����
                                                         bit9��rch1ģ���coreʱ����
                                                         bit10��rch2ģ���coreʱ����
                                                         bit11��rch3ģ���coreʱ����
                                                         bit12��rch4ģ���coreʱ����
                                                         bit13��rch5ģ���coreʱ����
                                                         bit14��rch6ģ���coreʱ����
                                                         bit15��rch7ģ���coreʱ����
                                                         bit16��wch0ģ���coreʱ����
                                                         bit17��wch1ģ���coreʱ����
                                                         bit18��mctlģ���coreʱ����
                                                         bit19��sw0ģ���coreʱ����
                                                         bit20��sw1ģ���coreʱ����
                                                         bit21��ov0ģ���coreʱ����
                                                         bit22��ov1ģ���coreʱ����
                                                         bit23��ov2ģ���coreʱ����
                                                         bit24��ov3ģ���coreʱ����
                                                         bit25��vbif1ģ���axiʱ����
                                                         bit26��vbif1ģ���coreʱ����
                                                         bit27��dbgģ���core/axi/apbʱ����
                                                         bit28~31��reserve */
    } reg;
} SOC_DSS_GLB_MODULE_CLK_SEL_UNION;
#endif
#define SOC_DSS_GLB_MODULE_CLK_SEL_module_clk_sel_START  (0)
#define SOC_DSS_GLB_MODULE_CLK_SEL_module_clk_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_MODULE_CLK_EN_UNION
 �ṹ˵��  : MODULE_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x304����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ�����ʱ��ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  module_clk_en : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                        1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                        0����ʾ���ʱ��ʹ����Ч����ֹӲ������
                                                        bit0: cmdlistģ���axiʱ����
                                                        bit1��vbifģ���coreʱ����
                                                        bit2��vbifģ���axiʱ����
                                                        bit3��apbģ���pclkʱ����
                                                        bit4��apbģ���pxl0ʱ����
                                                        bit5��apbģ���axiʱ����
                                                        bit6��apbģ���pxl1ʱ����
                                                        bit7��apbģ���coreʱ����
                                                        bit8��rch0ģ���coreʱ����
                                                        bit9��rch1ģ���coreʱ����
                                                        bit10��rch2ģ���coreʱ����
                                                        bit11��rch3ģ���coreʱ����
                                                        bit12��rch4ģ���coreʱ����
                                                        bit13��rch5ģ���coreʱ����
                                                        bit14��rch6ģ���coreʱ����
                                                        bit15��rch7ģ���coreʱ����
                                                        bit16��wch0ģ���coreʱ����
                                                        bit17��wch1ģ���coreʱ����
                                                        bit18��mctlģ���coreʱ����
                                                        bit19��sw0ģ���coreʱ����
                                                        bit20��sw1ģ���coreʱ����
                                                        bit21��ov0ģ���coreʱ����
                                                        bit22��ov1ģ���coreʱ����
                                                        bit23��ov2ģ���coreʱ����
                                                        bit24��ov3ģ���coreʱ����
                                                        bit25��vbif1ģ���axiʱ����
                                                        bit26��vbif1ģ���coreʱ����
                                                        bit27��dbgģ���core/axi/apbʱ����
                                                        bit28~31��reserve */
    } reg;
} SOC_DSS_GLB_MODULE_CLK_EN_UNION;
#endif
#define SOC_DSS_GLB_MODULE_CLK_EN_module_clk_en_START  (0)
#define SOC_DSS_GLB_MODULE_CLK_EN_module_clk_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_MODULE1_CLK_SEL_UNION
 �ṹ˵��  : MODULE1_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x308����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ�����ʱ��ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  module1_clk_sel : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                          1����ʾǿ�ƴ�ʱ�ӡ�
                                                          0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ��
                                                          bit0~bit1������
                                                          bit2��vscfģ���coreʱ����
                                                          bit3��dbuf0ģ���coreʱ����
                                                          bit4��dbuf1ģ���coreʱ����
                                                          bit5��dbuf0ģ���pxl0ʱ����
                                                          bit6��dppģ���pxl0ʱ����
                                                          bit7��ifbcģ���pxl0ʱ����
                                                          bit8��ifbcģ���pxl0 2��Ƶʱ����
                                                          bit9��ifbcģ���pxl0 4��Ƶʱ����
                                                          bit10��dbufģ���pxl1ʱ����
                                                          bit11��dbgģ���pxl0/pxl1ʱ���� */
    } reg;
} SOC_DSS_GLB_MODULE1_CLK_SEL_UNION;
#endif
#define SOC_DSS_GLB_MODULE1_CLK_SEL_module1_clk_sel_START  (0)
#define SOC_DSS_GLB_MODULE1_CLK_SEL_module1_clk_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_MODULE1_CLK_EN_UNION
 �ṹ˵��  : MODULE1_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x30C����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ�����ʱ��ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  module1_clk_en : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                         1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                         0����ʾ���ʱ��ʹ����Ч����ֹӲ������
                                                         bit0~bit1������
                                                         bit2��vscfģ���coreʱ����
                                                         bit3��dbuf0ģ���coreʱ����
                                                         bit4��dbuf1ģ���coreʱ����
                                                         bit5��dbuf0ģ���pxl0ʱ����
                                                         bit6��dppģ���pxl0ʱ����
                                                         bit7��ifbcģ���pxl0ʱ����
                                                         bit8��ifbcģ���pxl0 2��Ƶʱ����
                                                         bit9��ifbcģ���pxl0 4��Ƶʱ����
                                                         bit10��dbufģ���pxl1ʱ����
                                                         bit11��dbgģ���pxl0/pxl1ʱ���� */
    } reg;
} SOC_DSS_GLB_MODULE1_CLK_EN_UNION;
#endif
#define SOC_DSS_GLB_MODULE1_CLK_EN_module1_clk_en_START  (0)
#define SOC_DSS_GLB_MODULE1_CLK_EN_module1_clk_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_GLB0_DBG_SEL_UNION
 �ṹ˵��  : GLB0_DBG_SEL �Ĵ����ṹ���塣��ַƫ����:0x310����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ԼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  glb0_core_dbg_sel : 4;  /* bit[0-3]  : coreʱ����debug�ź�ѡ��
                                                             0��ѡ��ov2 dbg���
                                                             1��ѡ��ov3 dbg���
                                                             2��ѡ��rch0 dbg���
                                                             3��ѡ��rch1 dbg���
                                                             4��ѡ��rch2 dbg���
                                                             5��ѡ��rch3 dbg���
                                                             6��ѡ��rch4 dbg���
                                                             7��ѡ��rch5 dbg���
                                                             8��ѡ��rch6 dbg���
                                                             9��ѡ��rch7 dbg���
                                                             10��ѡ��wch0 dbg���
                                                             11��ѡ��wch1 dbg���
                                                             12��ѡ��ov2 dbg���
                                                             13��ѡ��ov3 dbg���
                                                             14��ѡ��vbif coreʱ����dbg���
                                                             ������ѡ��vbif1 coreʱ����dbg��� */
        unsigned int  dss_sum_dbg_sel   : 2;  /* bit[4-5]  : ��ʱ�����ٺ�DISP�����disp_dbgһ�����debug�ź�ѡ��
                                                             0��coreʱ����dbg���
                                                             1��axiʱ����dbg���
                                                             2��axi_mmʱ����dbg���
                                                             ������disp��dbg��� */
        unsigned int  reserved_0        : 2;  /* bit[6-7]  : ���� */
        unsigned int  glb0_axi_dbg_sel  : 2;  /* bit[8-9]  : axiʱ����debug�ź�ѡ��
                                                             0��ѡ��vbif axiʱ����dbg���
                                                             ������ѡ��cmdlist dbg��� */
        unsigned int  reserved_1        : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_DSS_GLB_GLB0_DBG_SEL_UNION;
#endif
#define SOC_DSS_GLB_GLB0_DBG_SEL_glb0_core_dbg_sel_START  (0)
#define SOC_DSS_GLB_GLB0_DBG_SEL_glb0_core_dbg_sel_END    (3)
#define SOC_DSS_GLB_GLB0_DBG_SEL_dss_sum_dbg_sel_START    (4)
#define SOC_DSS_GLB_GLB0_DBG_SEL_dss_sum_dbg_sel_END      (5)
#define SOC_DSS_GLB_GLB0_DBG_SEL_glb0_axi_dbg_sel_START   (8)
#define SOC_DSS_GLB_GLB0_DBG_SEL_glb0_axi_dbg_sel_END     (9)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_GLB1_DBG_SEL_UNION
 �ṹ˵��  : GLB1_DBG_SEL �Ĵ����ṹ���塣��ַƫ����:0x314����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ԼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  glb1_core_dbg_sel : 2;  /* bit[0-1]  : coreʱ����debug�ź�ѡ��
                                                             0��ѡ��scf dbg���
                                                             1��ѡ��dbuf0 dbg���
                                                             ������ѡ��dbuf1 dbg��� */
        unsigned int  glb1_clk_dbg_sel  : 2;  /* bit[2-3]  : ��ʱ�������debug�ź�ѡ��
                                                             0��coreʱ����dbg���
                                                             1��pxl0ʱ����dbg���
                                                             ������pxl1ʱ����dbg��� */
        unsigned int  reserved_0        : 4;  /* bit[4-7]  : ���� */
        unsigned int  glb1_pxl0_dbg_sel : 2;  /* bit[8-9]  : pxl0ʱ����debug�ź�ѡ��
                                                             0��ѡ��dpp dbg���
                                                             1��ѡ��ifbc dbg���
                                                             ������ѡ��itf1 dbg��� */
        unsigned int  reserved_1        : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_DSS_GLB_GLB1_DBG_SEL_UNION;
#endif
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_core_dbg_sel_START  (0)
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_core_dbg_sel_END    (1)
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_clk_dbg_sel_START   (2)
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_clk_dbg_sel_END     (3)
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_pxl0_dbg_sel_START  (8)
#define SOC_DSS_GLB_GLB1_DBG_SEL_glb1_pxl0_dbg_sel_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_IRQ_CPU_UNION
 �ṹ˵��  : DBG_IRQ_CPU �Ĵ����ṹ���塣��ַƫ����:0x320����ֵ:0x00000000�����:32
 �Ĵ���˵��: CPU�жϵ��ԼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_irq_cpu : 3;  /* bit[0-2] : bit0:dbg_cpu_pdp;
                                                      bit1:dbg_cpu_sdp;
                                                      bit2:dbg_cpu_offline; */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_IRQ_CPU_UNION;
#endif
#define SOC_DSS_GLB_DBG_IRQ_CPU_dbg_irq_cpu_START  (0)
#define SOC_DSS_GLB_DBG_IRQ_CPU_dbg_irq_cpu_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DBG_IRQ_MCU_UNION
 �ṹ˵��  : DBG_IRQ_MCU �Ĵ����ṹ���塣��ַƫ����:0x324����ֵ:0x00000000�����:32
 �Ĵ���˵��: MCU�жϵ��ԼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_irq_mcu : 3;  /* bit[0-2] : bit0:dbg_mcu_pdp;
                                                      bit1:dbg_mcu_sdp;
                                                      bit2:dbg_mcu_offline; */
        unsigned int  reserved    : 29; /* bit[3-31]: ���� */
    } reg;
} SOC_DSS_GLB_DBG_IRQ_MCU_UNION;
#endif
#define SOC_DSS_GLB_DBG_IRQ_MCU_dbg_irq_mcu_START  (0)
#define SOC_DSS_GLB_DBG_IRQ_MCU_dbg_irq_mcu_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_TP_SEL_UNION
 �ṹ˵��  : TP_SEL �Ĵ����ṹ���塣��ַƫ����:0x0400����ֵ:0x00000000�����:32
 �Ĵ���˵��: TPѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tp_sel   : 2;  /* bit[0-1] : 0����ʾ��ѡͨ�������
                                                   1����ʾѡͨdsi1������
                                                   2����ʾѡͨdsi0������ */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_GLB_TP_SEL_UNION;
#endif
#define SOC_DSS_GLB_TP_SEL_tp_sel_START    (0)
#define SOC_DSS_GLB_TP_SEL_tp_sel_END      (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CRC_DBG_LDI0_UNION
 �ṹ˵��  : CRC_DBG_LDI0 �Ĵ����ṹ���塣��ַƫ����:0x0404����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI0��crcУ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_dbg_ldi0 : 32; /* bit[0-31]: ���� */
    } reg;
} SOC_DSS_GLB_CRC_DBG_LDI0_UNION;
#endif
#define SOC_DSS_GLB_CRC_DBG_LDI0_crc_dbg_ldi0_START  (0)
#define SOC_DSS_GLB_CRC_DBG_LDI0_crc_dbg_ldi0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CRC_DBG_LDI1_UNION
 �ṹ˵��  : CRC_DBG_LDI1 �Ĵ����ṹ���塣��ַƫ����:0x0408����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI1��crcУ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_dbg_ldi1 : 32; /* bit[0-31]: ���� */
    } reg;
} SOC_DSS_GLB_CRC_DBG_LDI1_UNION;
#endif
#define SOC_DSS_GLB_CRC_DBG_LDI1_crc_dbg_ldi1_START  (0)
#define SOC_DSS_GLB_CRC_DBG_LDI1_crc_dbg_ldi1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CRC_LDI0_EN_UNION
 �ṹ˵��  : CRC_LDI0_EN �Ĵ����ṹ���塣��ַƫ����:0x040C����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI0��CRC����ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ldi0_en : 1;  /* bit[0-0] : ���� */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_CRC_LDI0_EN_UNION;
#endif
#define SOC_DSS_GLB_CRC_LDI0_EN_crc_ldi0_en_START  (0)
#define SOC_DSS_GLB_CRC_LDI0_EN_crc_ldi0_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CRC_LDI0_FRM_UNION
 �ṹ˵��  : CRC_LDI0_FRM �Ĵ����ṹ���塣��ַƫ����:0x0410����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI0�ϱ���CRCУ���֡��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ldi0_frm : 32; /* bit[0-31]: ���� */
    } reg;
} SOC_DSS_GLB_CRC_LDI0_FRM_UNION;
#endif
#define SOC_DSS_GLB_CRC_LDI0_FRM_crc_ldi0_frm_START  (0)
#define SOC_DSS_GLB_CRC_LDI0_FRM_crc_ldi0_frm_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CRC_LDI1_EN_UNION
 �ṹ˵��  : CRC_LDI1_EN �Ĵ����ṹ���塣��ַƫ����:0x0414����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI1��CRC����ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ldi1_en : 1;  /* bit[0-0] : ���� */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_GLB_CRC_LDI1_EN_UNION;
#endif
#define SOC_DSS_GLB_CRC_LDI1_EN_crc_ldi1_en_START  (0)
#define SOC_DSS_GLB_CRC_LDI1_EN_crc_ldi1_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_CRC_LDI1_FRM_UNION
 �ṹ˵��  : CRC_LDI1_FRM �Ĵ����ṹ���塣��ַƫ����:0x0418����ֵ:0x00000000�����:32
 �Ĵ���˵��: LDI1�ϱ���CRCУ���֡��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  crc_ldi1_frm : 32; /* bit[0-31]: ���� */
    } reg;
} SOC_DSS_GLB_CRC_LDI1_FRM_UNION;
#endif
#define SOC_DSS_GLB_CRC_LDI1_FRM_crc_ldi1_frm_START  (0)
#define SOC_DSS_GLB_CRC_LDI1_FRM_crc_ldi1_frm_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DSS_MEM_CTRL_UNION
 �ṹ˵��  : DSS_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0600����ֵ:0x01A800A8�����:32
 �Ĵ���˵��: CPU��дmemoryʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_spram_ctrl : 16; /* bit[0-15] : �����üĴ���
                                                          Single Port����MEM�͹���������ã�
                                                          [15:11]:reserved;
                                                          [10:9]:SPMB_WTSEL��Ĭ��Ϊ2'b00;
                                                          [8:7]: SPMB_RTSEL��Ĭ��Ϊ2'b01;
                                                          [6:5]: SPSB WTSEL,Ĭ��Ϊ2'b01;
                                                          [4:3]: SPSB RTSEL,Ĭ��Ϊ2'b01;
                                                          [2:0]: reserved; */
        unsigned int  dss_tpram_ctrl : 16; /* bit[16-31]: �����üĴ���
                                                          Two Port����MEM�͹���������ã�
                                                          [15:10]:reserved;
                                                          [9:7]: KP,Ĭ��Ϊ3'b011;
                                                          [6:5]: WCT,Ĭ��Ϊ2'b01;
                                                          [4:3]: RCT,Ĭ��Ϊ2'b01;
                                                          [2:0]: reserved; */
    } reg;
} SOC_DSS_GLB_DSS_MEM_CTRL_UNION;
#endif
#define SOC_DSS_GLB_DSS_MEM_CTRL_dss_spram_ctrl_START  (0)
#define SOC_DSS_GLB_DSS_MEM_CTRL_dss_spram_ctrl_END    (15)
#define SOC_DSS_GLB_DSS_MEM_CTRL_dss_tpram_ctrl_START  (16)
#define SOC_DSS_GLB_DSS_MEM_CTRL_dss_tpram_ctrl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_GLB_DSS_PM_CTRL_UNION
 �ṹ˵��  : DSS_PM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0604����ֵ:0x00002009�����:32
 �Ĵ���˵��: MEM�͹��Ŀ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dss_pm_ctrl : 31; /* bit[0-30]: �����üĴ���
                                                      [30] slp_mode ģʽѡ��1 slpģʽ��0 dslpģʽ
                                                      [29:26]:reserved;
                                                      [25:23] SLP/DSLPģʽt(d)slp��ʱ�Ĵ������ο�����Ϊ0��1��cycle�� 
                                                      [22:20] SLP/DSLPģʽt(d)slpx��ʱ�Ĵ������ο�����Ϊ0��1��cycle�� 
                                                      [19:17] SLP/DSLPģʽtx(d)slp��ʱ�Ĵ������ο�����Ϊ0��1��cycle�� 
                                                      [16:13] SLP/DSLPģʽt(d)slpwk��ʱ�Ĵ������ο�����Ϊ1��2��cycle�� 
                                                      [12:10] SDģʽtsd��ʱ�Ĵ������ο�����Ϊ0��1��cycle�� 
                                                      [9:7] SDģʽtsdx��ʱ�Ĵ������ο�����Ϊ0 ��1��cycle�� 
                                                      [6:4] SDģʽtxsd��ʱ�Ĵ������ο�����Ϊ0 ��1��cycle�� 
                                                      [3:0] SDģʽtsdwk��ʱ�Ĵ������ο�����Ϊ9��10��cycle��  */
        unsigned int  reserved    : 1;  /* bit[31]  : ���� */
    } reg;
} SOC_DSS_GLB_DSS_PM_CTRL_UNION;
#endif
#define SOC_DSS_GLB_DSS_PM_CTRL_dss_pm_ctrl_START  (0)
#define SOC_DSS_GLB_DSS_PM_CTRL_dss_pm_ctrl_END    (30)






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

#endif /* end of soc_dss_glb_interface.h */
