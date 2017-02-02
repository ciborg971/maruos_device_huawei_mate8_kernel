/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_asp_cfg_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:18:05
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_ASP_CFG.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ASP_CFG_INTERFACE_H__
#define __SOC_ASP_CFG_INTERFACE_H__

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
/* �Ĵ���˵����������λʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_RST_CTRLEN_UNION */
#define SOC_ASP_CFG_R_RST_CTRLEN_ADDR(base)           ((base) + (0x0000))

/* �Ĵ���˵����������λ����Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_RST_CTRLDIS_UNION */
#define SOC_ASP_CFG_R_RST_CTRLDIS_ADDR(base)          ((base) + (0x0004))

/* �Ĵ���˵����������λ״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_RST_CTRLSTAT_UNION */
#define SOC_ASP_CFG_R_RST_CTRLSTAT_ADDR(base)         ((base) + (0x0008))

/* �Ĵ���˵����ʱ��ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_GATE_EN_UNION */
#define SOC_ASP_CFG_R_GATE_EN_ADDR(base)              ((base) + (0x000C))

/* �Ĵ���˵����ʱ�ӽ�ֹ�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_GATE_DIS_UNION */
#define SOC_ASP_CFG_R_GATE_DIS_ADDR(base)             ((base) + (0x0010))

/* �Ĵ���˵����ʱ��ʹ��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_GATE_CLKEN_UNION */
#define SOC_ASP_CFG_R_GATE_CLKEN_ADDR(base)           ((base) + (0x0014))

/* �Ĵ���˵����ʱ������״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_GATE_CLKSTAT_UNION */
#define SOC_ASP_CFG_R_GATE_CLKSTAT_ADDR(base)         ((base) + (0x0018))

/* �Ĵ���˵����ʱ�ӷ�Ƶ���ſ�ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_GATE_CLKDIV_EN_UNION */
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_ADDR(base)       ((base) + (0x001C))

/* �Ĵ���˵������Ƶ�ȿ��ƼĴ���1
   λ����UNION�ṹ:  SOC_ASP_CFG_R_CLK1_DIV_UNION */
#define SOC_ASP_CFG_R_CLK1_DIV_ADDR(base)             ((base) + (0x0020))

/* �Ĵ���˵������Ƶ�ȿ��ƼĴ���2
   λ����UNION�ṹ:  SOC_ASP_CFG_R_CLK2_DIV_UNION */
#define SOC_ASP_CFG_R_CLK2_DIV_ADDR(base)             ((base) + (0x0024))

/* �Ĵ���˵������Ƶ�ȿ��ƼĴ���3
   λ����UNION�ṹ:  SOC_ASP_CFG_R_CLK3_DIV_UNION */
#define SOC_ASP_CFG_R_CLK3_DIV_ADDR(base)             ((base) + (0x0028))

/* �Ĵ���˵������Ƶ�ȿ��ƼĴ���4
   λ����UNION�ṹ:  SOC_ASP_CFG_R_CLK4_DIV_UNION */
#define SOC_ASP_CFG_R_CLK4_DIV_ADDR(base)             ((base) + (0x002C))

/* �Ĵ���˵������Ƶ�ȿ��ƼĴ���5
   λ����UNION�ṹ:  SOC_ASP_CFG_R_CLK5_DIV_UNION */
#define SOC_ASP_CFG_R_CLK5_DIV_ADDR(base)             ((base) + (0x0030))

/* �Ĵ���˵������Ƶ�ȿ��ƼĴ���6
   λ����UNION�ṹ:  SOC_ASP_CFG_R_CLK6_DIV_UNION */
#define SOC_ASP_CFG_R_CLK6_DIV_ADDR(base)             ((base) + (0x0034))

/* �Ĵ���˵����ʱ��ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_CLK_SEL_UNION */
#define SOC_ASP_CFG_R_CLK_SEL_ADDR(base)              ((base) + (0x0038))

/* �Ĵ���˵����DSP NMI�жϲ����Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DSP_NMI_UNION */
#define SOC_ASP_CFG_R_DSP_NMI_ADDR(base)              ((base) + (0x003C))

/* �Ĵ���˵����DSP PRID���üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DSP_PRID_UNION */
#define SOC_ASP_CFG_R_DSP_PRID_ADDR(base)             ((base) + (0x0040))

/* �Ĵ���˵����DSP RUNSTALL���üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DSP_RUNSTALL_UNION */
#define SOC_ASP_CFG_R_DSP_RUNSTALL_ADDR(base)         ((base) + (0x0044))

/* �Ĵ���˵����DSP STATVECTORSEL���üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DSP_STATVECTORSEL_UNION */
#define SOC_ASP_CFG_R_DSP_STATVECTORSEL_ADDR(base)    ((base) + (0x0048))

/* �Ĵ���˵����DSP OCDHALTONRESET���üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DSP_OCDHALTONRESET_UNION */
#define SOC_ASP_CFG_R_DSP_OCDHALTONRESET_ADDR(base)   ((base) + (0x004C))

/* �Ĵ���˵����DSP ״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DSP_STATUS_UNION */
#define SOC_ASP_CFG_R_DSP_STATUS_ADDR(base)           ((base) + (0x0050))

/* �Ĵ���˵����DMACͨ��ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DMAC_SEL_UNION */
#define SOC_ASP_CFG_R_DMAC_SEL_ADDR(base)             ((base) + (0x0054))

/* �Ĵ���˵�����������ȼ����üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_BUS_PRIORITY_UNION */
#define SOC_ASP_CFG_R_BUS_PRIORITY_ADDR(base)         ((base) + (0x0058))

/* �Ĵ���˵�����Զ��ſ�ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_CG_EN_UNION */
#define SOC_ASP_CFG_R_CG_EN_ADDR(base)                ((base) + (0x005C))

/* �Ĵ���˵����ocram�͹������üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_OCRAM_RET_UNION */
#define SOC_ASP_CFG_R_OCRAM_RET_ADDR(base)            ((base) + (0x0060))

/* �Ĵ���˵�����ǰ�ȫ�ж�ԭʼ״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_INTR_NS_INI_UNION */
#define SOC_ASP_CFG_R_INTR_NS_INI_ADDR(base)          ((base) + (0x0064))

/* �Ĵ���˵�����ǰ�ȫ�ж�ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_INTR_NS_EN_UNION */
#define SOC_ASP_CFG_R_INTR_NS_EN_ADDR(base)           ((base) + (0x0068))

/* �Ĵ���˵�����ǰ�ȫ�ж����κ�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_INTR_NS_MASK_UNION */
#define SOC_ASP_CFG_R_INTR_NS_MASK_ADDR(base)         ((base) + (0x006C))

/* �Ĵ���˵������ǿ��DBG�ź����üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DBG_SET_AHB2AXI_UNION */
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_ADDR(base)      ((base) + (0x0070))

/* �Ĵ���˵������ǿ��DBG�ź�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_UNION */
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_ADDR(base)   ((base) + (0x0074))

/* �Ĵ���˵�������߷�����bypass�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DLOCK_BP_UNION */
#define SOC_ASP_CFG_R_DLOCK_BP_ADDR(base)             ((base) + (0x0078))

/* �Ĵ���˵�����ϱ���hifi dsp���ж��ź�ֻ���Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DSP_BINTERRUPT_UNION */
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_ADDR(base)       ((base) + (0x007C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DSP_RAM_RET_UNION */
#define SOC_ASP_CFG_R_DSP_RAM_RET_ADDR(base)          ((base) + (0x0084))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_CFG_R_TZ_SECURE_N_UNION */
#define SOC_ASP_CFG_R_TZ_SECURE_N_ADDR(base)          ((base) + (0x0100))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_CFG_R_OCRAM_R0SIZE_UNION */
#define SOC_ASP_CFG_R_OCRAM_R0SIZE_ADDR(base)         ((base) + (0x0104))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_UNION */
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_ADDR(base)    ((base) + (0x0108))

/* �Ĵ���˵������ȫ�ж�ԭʼ״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_INTR_S_INI_UNION */
#define SOC_ASP_CFG_R_INTR_S_INI_ADDR(base)           ((base) + (0x010C))

/* �Ĵ���˵������ȫ�ж�ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_INTR_S_EN_UNION */
#define SOC_ASP_CFG_R_INTR_S_EN_ADDR(base)            ((base) + (0x0110))

/* �Ĵ���˵������ȫ�ж����κ�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_INTR_S_MASK_UNION */
#define SOC_ASP_CFG_R_INTR_S_MASK_ADDR(base)          ((base) + (0x0114))

/* �Ĵ���˵����dsp��ַ��ӳ��ʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DSP_REMAPPING_EN_UNION */
#define SOC_ASP_CFG_R_DSP_REMAPPING_EN_ADDR(base)     ((base) + (0x0118))

/* �Ĵ���˵����DSP ��ַ��ӳ��Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DSP_REMAPPING_SRC_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DSP_REMAPPING_SRC_BASE_ADDR_ADDR(base) ((base) + (0x011C))

/* �Ĵ���˵����DSP ��ַ��ӳ��Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DSP_REMAPPING_DES_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DSP_REMAPPING_DES_BASE_ADDR_ADDR(base) ((base) + (0x0120))

/* �Ĵ���˵����DDR��Harq Memory remap���ƼĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_UNION */
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_ADDR(base)    ((base) + (0x124))

/* �Ĵ���˵����DDR��Harq Memory remapԴ����ַ�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DDR_HARQ_REMAP_SRC_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_SRC_BASE_ADDR_ADDR(base) ((base) + (0x128))

/* �Ĵ���˵����DDR��Harq Memory remapĿ�����ַ�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DDR_HARQ_REMAP_DES_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_DES_BASE_ADDR_ADDR(base) ((base) + (0x12C))

/* �Ĵ���˵����DDR��MMBUF remap���ƼĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_UNION */
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_ADDR(base)   ((base) + (0x130))

/* �Ĵ���˵����DDR��MMBUF remapԴ����ַ�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DDR_MMBUF_REMAP_SRC_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_SRC_BASE_ADDR_ADDR(base) ((base) + (0x134))

/* �Ĵ���˵����DDR��MMBUF remapĿ�����ַ�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DDR_MMBUF_REMAP_DES_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_DES_BASE_ADDR_ADDR(base) ((base) + (0x138))

/* �Ĵ���˵����DDR��OCRAM remap���ƼĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_UNION */
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_ADDR(base)   ((base) + (0x13C))

/* �Ĵ���˵����DDR��OCRAM remapԴ����ַ�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DDR_OCRAM_REMAP_SRC_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_SRC_BASE_ADDR_ADDR(base) ((base) + (0x140))

/* �Ĵ���˵����DDR��OCRAM remapĿ�����ַ�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_DDR_OCRAM_REMAP_DES_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_DES_BASE_ADDR_ADDR(base) ((base) + (0x144))

/* �Ĵ���˵����MMBUF CTRL���üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_MMBUF_CTRL_UNION */
#define SOC_ASP_CFG_R_MMBUF_CTRL_ADDR(base)           ((base) + (0x0148))

/* �Ĵ���˵����HIFIDSPʱ��Ƶ���Զ���Ƶ���üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_UNION */
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_ADDR(base) ((base) + (0x014C))

/* �Ĵ���˵����Ƶƫ��¼ģ�����üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_UNION */
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_ADDR(base) ((base) + (0x0150))

/* �Ĵ���˵�����ڴ���ģ��ʹ�����üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_ADDR(base) ((base) + (0x0160))

/* �Ĵ���˵�����ڴ���ģ���ж��������üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR_ADDR(base) ((base) + (0x0164))

/* �Ĵ���˵�����ڴ���ģ���ж�ʹ�����üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_ADDR(base) ((base) + (0x0168))

/* �Ĵ���˵�����ڴ���ģ���ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_ADDR(base) ((base) + (0x016C))

/* �Ĵ���˵�����ڴ���ģ��0����ַ���üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_BASE_ADDR_ADDR(base) ((base) + (0x0170))

/* �Ĵ���˵�����ڴ���ģ��0��ַ�������üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_LEN_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_LEN_ADDR_ADDR(base) ((base) + (0x0174))

/* �Ĵ���˵�����ڴ���ģ��0Խ���д��ַ��¼�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_AWADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_AWADDR_ADDR(base) ((base) + (0x0178))

/* �Ĵ���˵�����ڴ���ģ��0Խ��Ķ���ַ��¼�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_ARADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_ARADDR_ADDR(base) ((base) + (0x017C))

/* �Ĵ���˵�����ڴ���ģ��1����ַ���üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_BASE_ADDR_ADDR(base) ((base) + (0x0180))

/* �Ĵ���˵�����ڴ���ģ��1��ַ�������üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_LEN_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_LEN_ADDR_ADDR(base) ((base) + (0x0184))

/* �Ĵ���˵�����ڴ���ģ��1Խ���д��ַ��¼�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_AWADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_AWADDR_ADDR(base) ((base) + (0x0188))

/* �Ĵ���˵�����ڴ���ģ��1Խ��Ķ���ַ��¼�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_ARADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_ARADDR_ADDR(base) ((base) + (0x018C))

/* �Ĵ���˵�����ڴ���ģ��2����ַ���üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_BASE_ADDR_ADDR(base) ((base) + (0x0190))

/* �Ĵ���˵�����ڴ���ģ��2��ַ�������üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_LEN_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_LEN_ADDR_ADDR(base) ((base) + (0x0194))

/* �Ĵ���˵�����ڴ���ģ��2Խ���д��ַ��¼�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_AWADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_AWADDR_ADDR(base) ((base) + (0x0198))

/* �Ĵ���˵�����ڴ���ģ��2Խ��Ķ���ַ��¼�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_ARADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_ARADDR_ADDR(base) ((base) + (0x019C))

/* �Ĵ���˵�����ڴ���ģ��3����ַ���üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_BASE_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_BASE_ADDR_ADDR(base) ((base) + (0x01A0))

/* �Ĵ���˵�����ڴ���ģ��3��ַ�������üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_LEN_ADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_LEN_ADDR_ADDR(base) ((base) + (0x01A4))

/* �Ĵ���˵�����ڴ���ģ��3Խ���д��ַ��¼�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_AWADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_AWADDR_ADDR(base) ((base) + (0x01A8))

/* �Ĵ���˵�����ڴ���ģ��3Խ��Ķ���ַ��¼�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_ARADDR_UNION */
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_ARADDR_ADDR(base) ((base) + (0x01AC))

/* �Ĵ���˵����memory�������üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_MEMORY_CTRL_UNION */
#define SOC_ASP_CFG_R_MEMORY_CTRL_ADDR(base)          ((base) + (0x01B0))

/* �Ĵ���˵����slimbus primary���üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_SLIMBUS_PRIMARY_ADDR_UNION */
#define SOC_ASP_CFG_R_SLIMBUS_PRIMARY_ADDR_ADDR(base) ((base) + (0x01B4))

/* �Ĵ���˵����slimbus id���üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_SLIMBUS_ID_ADDR_UNION */
#define SOC_ASP_CFG_R_SLIMBUS_ID_ADDR_ADDR(base)      ((base) + (0x01B8))

/* �Ĵ���˵����slimbus���ݸ�ʽ���üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_UNION */
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_ADDR(base)     ((base) + (0x01BC))

/* �Ĵ���˵����slimbus����ͨ�����üĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_UNION */
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_ADDR(base)    ((base) + (0x01C0))

/* �Ĵ���˵������Ƶ�ȿ��ƼĴ���0
   λ����UNION�ṹ:  SOC_ASP_CFG_R_CLK0_DIV_UNION */
#define SOC_ASP_CFG_R_CLK0_DIV_ADDR(base)             ((base) + (0x01D0))

/* �Ĵ���˵������ȫ�������Կ��ƼĴ���
   λ����UNION�ṹ:  SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_UNION */
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_ADDR(base)  ((base) + (0x0200))





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
 �ṹ��    : SOC_ASP_CFG_R_RST_CTRLEN_UNION
 �ṹ˵��  : R_RST_CTRLEN �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_sio_audio_n     : 1;  /* bit[0]    : sio_audioģ����λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  rst_sio_voice_n     : 1;  /* bit[1]    : sio_voiceģ����λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  rst_sio_bt_n        : 1;  /* bit[2]    : sio_btģ����λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  rst_sio_modem_n     : 1;  /* bit[3]    : sio_modemģ����λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  rst_dsp_n           : 1;  /* bit[4]    : hifi dspģ����λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  rst_dsp_debug_n     : 1;  /* bit[5]    : hifi dspģ���debug��λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  rst_ipc_n           : 1;  /* bit[6]    : asp_ipcģ����λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  rst_asp_hdmi_n      : 1;  /* bit[7]    : asp_hdmiģ����λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  rst_dmac_n          : 1;  /* bit[8]    : asp_dmacģ����λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  reserved_0          : 1;  /* bit[9]    :  */
        unsigned int  reserved_1          : 1;  /* bit[10]   :  */
        unsigned int  rst_ocram_n         : 1;  /* bit[11]   : ocramģ����λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  rst_watchdog_n      : 1;  /* bit[12]   : watch dogģ����λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  rst_slimbus_base_n  : 1;  /* bit[13]   : slimbusģ��baseʱ������λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  rst_slimbus_n       : 1;  /* bit[14]   : slimbusģ������ʱ������λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  rst_asp_h2x_n       : 1;  /* bit[15]   : ��ǿ��h2xģ����λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  rst_gpio_n          : 1;  /* bit[16]   : gpioģ����λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  rst_timer0_n        : 1;  /* bit[17]   : timer0ģ����λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  rst_timer1_n        : 1;  /* bit[18]   : timer1ģ����λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  dsp_preset_req_n    : 1;  /* bit[19]   : DSP APB�ӿ���λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  dsp_jtag_srst_req_n : 1;  /* bit[20]   : DSP JTAG�ӿ���λʹ�ܣ�
                                                               0����λʹ��״̬���䣻
                                                               1����λʹ�ܡ� */
        unsigned int  reserved_2          : 1;  /* bit[21]   : ���� */
        unsigned int  reserved_3          : 10; /* bit[22-31]: ���� */
    } reg;
} SOC_ASP_CFG_R_RST_CTRLEN_UNION;
#endif
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_audio_n_START      (0)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_audio_n_END        (0)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_voice_n_START      (1)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_voice_n_END        (1)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_bt_n_START         (2)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_bt_n_END           (2)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_modem_n_START      (3)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_sio_modem_n_END        (3)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_dsp_n_START            (4)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_dsp_n_END              (4)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_dsp_debug_n_START      (5)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_dsp_debug_n_END        (5)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_ipc_n_START            (6)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_ipc_n_END              (6)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_asp_hdmi_n_START       (7)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_asp_hdmi_n_END         (7)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_dmac_n_START           (8)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_dmac_n_END             (8)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_ocram_n_START          (11)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_ocram_n_END            (11)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_watchdog_n_START       (12)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_watchdog_n_END         (12)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_slimbus_base_n_START   (13)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_slimbus_base_n_END     (13)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_slimbus_n_START        (14)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_slimbus_n_END          (14)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_asp_h2x_n_START        (15)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_asp_h2x_n_END          (15)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_gpio_n_START           (16)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_gpio_n_END             (16)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_timer0_n_START         (17)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_timer0_n_END           (17)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_timer1_n_START         (18)
#define SOC_ASP_CFG_R_RST_CTRLEN_rst_timer1_n_END           (18)
#define SOC_ASP_CFG_R_RST_CTRLEN_dsp_preset_req_n_START     (19)
#define SOC_ASP_CFG_R_RST_CTRLEN_dsp_preset_req_n_END       (19)
#define SOC_ASP_CFG_R_RST_CTRLEN_dsp_jtag_srst_req_n_START  (20)
#define SOC_ASP_CFG_R_RST_CTRLEN_dsp_jtag_srst_req_n_END    (20)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_RST_CTRLDIS_UNION
 �ṹ˵��  : R_RST_CTRLDIS �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λ����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_sio_audio       : 1;  /* bit[0]    : sio_audioģ����λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  rst_sio_voice_n     : 1;  /* bit[1]    : sio_voiceģ����λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  rst_sio_bt_n        : 1;  /* bit[2]    : sio_btģ����λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  rst_sio_modem_n     : 1;  /* bit[3]    : sio_modemģ����λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  rst_dsp_n           : 1;  /* bit[4]    : hifi dspģ����λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  rst_dsp_debug_n     : 1;  /* bit[5]    : hifi dspģ���debug��λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  rst_ipc_n           : 1;  /* bit[6]    : asp_ipcģ����λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  rst_asp_hdmi_n      : 1;  /* bit[7]    : asp_hdmiģ����λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  rst_dmac_n          : 1;  /* bit[8]    : asp_dmacģ����λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  reserved_0          : 1;  /* bit[9]    :  */
        unsigned int  reserved_1          : 1;  /* bit[10]   :  */
        unsigned int  rst_ocram_n         : 1;  /* bit[11]   : ocramģ����λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  rst_watchdog_n      : 1;  /* bit[12]   : watch dogģ����λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  rst_slimbus_base_n  : 1;  /* bit[13]   : slimbusģ��baseʱ������λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  rst_slimbus_n       : 1;  /* bit[14]   : slimbusģ������ʱ������λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  rst_asp_h2x_n       : 1;  /* bit[15]   : ��ǿ��h2xģ����λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  rst_gpio_n          : 1;  /* bit[16]   : gpioģ����λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  rst_timer0_n        : 1;  /* bit[17]   : timer0ģ����λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  rst_timer1_n        : 1;  /* bit[18]   : timer1ģ����λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  dsp_preset_req_n    : 1;  /* bit[19]   : DSP APB�ӿ���λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  dsp_jtag_srst_req_n : 1;  /* bit[20]   : DSP JTAG�ӿ���λ���룺
                                                               0����λʹ��״̬���䣻
                                                               1����λ���롣 */
        unsigned int  reserved_2          : 1;  /* bit[21]   : ���� */
        unsigned int  reserved_3          : 10; /* bit[22-31]: ���� */
    } reg;
} SOC_ASP_CFG_R_RST_CTRLDIS_UNION;
#endif
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_audio_START        (0)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_audio_END          (0)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_voice_n_START      (1)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_voice_n_END        (1)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_bt_n_START         (2)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_bt_n_END           (2)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_modem_n_START      (3)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_sio_modem_n_END        (3)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_dsp_n_START            (4)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_dsp_n_END              (4)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_dsp_debug_n_START      (5)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_dsp_debug_n_END        (5)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_ipc_n_START            (6)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_ipc_n_END              (6)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_asp_hdmi_n_START       (7)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_asp_hdmi_n_END         (7)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_dmac_n_START           (8)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_dmac_n_END             (8)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_ocram_n_START          (11)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_ocram_n_END            (11)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_watchdog_n_START       (12)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_watchdog_n_END         (12)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_slimbus_base_n_START   (13)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_slimbus_base_n_END     (13)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_slimbus_n_START        (14)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_slimbus_n_END          (14)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_asp_h2x_n_START        (15)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_asp_h2x_n_END          (15)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_gpio_n_START           (16)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_gpio_n_END             (16)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_timer0_n_START         (17)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_timer0_n_END           (17)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_timer1_n_START         (18)
#define SOC_ASP_CFG_R_RST_CTRLDIS_rst_timer1_n_END           (18)
#define SOC_ASP_CFG_R_RST_CTRLDIS_dsp_preset_req_n_START     (19)
#define SOC_ASP_CFG_R_RST_CTRLDIS_dsp_preset_req_n_END       (19)
#define SOC_ASP_CFG_R_RST_CTRLDIS_dsp_jtag_srst_req_n_START  (20)
#define SOC_ASP_CFG_R_RST_CTRLDIS_dsp_jtag_srst_req_n_END    (20)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_RST_CTRLSTAT_UNION
 �ṹ˵��  : R_RST_CTRLSTAT �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x001FFFFF�����:32
 �Ĵ���˵��: ������λ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rst_sio_audio_n     : 1;  /* bit[0]    : sio_audioģ����λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  rst_sio_voice_n     : 1;  /* bit[1]    : sio_voiceģ����λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  rst_sio_bt_n        : 1;  /* bit[2]    : sio_btģ����λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  rst_sio_modem_n     : 1;  /* bit[3]    : sio_modemģ����λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  rst_dsp_n           : 1;  /* bit[4]    : hifi dspģ����λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  rst_dsp_debug_n     : 1;  /* bit[5]    : hifi dspģ���debug��λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  rst_ipc_n           : 1;  /* bit[6]    : asp_ipcģ����λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  rst_asp_hdmi_n      : 1;  /* bit[7]    : asp_hdmiģ����λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  rst_dmac_n          : 1;  /* bit[8]    : asp_dmacģ����λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  reserved_0          : 1;  /* bit[9]    :  */
        unsigned int  reserved_1          : 1;  /* bit[10]   :  */
        unsigned int  rst_ocram_n         : 1;  /* bit[11]   : ocramģ����λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  rst_watchdog_n      : 1;  /* bit[12]   : watch dogģ����λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  rst_slimbus_base_n  : 1;  /* bit[13]   : slimbusģ��baseʱ������λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  rst_slimbus_n       : 1;  /* bit[14]   : slimbusģ������ʱ������λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  rst_asp_h2x_n       : 1;  /* bit[15]   : ��ǿ��h2xģ����λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  rst_gpio_n          : 1;  /* bit[16]   : gpioģ����λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  rst_timer0_n        : 1;  /* bit[17]   : timer0ģ����λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  rst_timer1_n        : 1;  /* bit[18]   : timer1ģ����λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  dsp_preset_req_n    : 1;  /* bit[19]   : DSP APB�ӿ���λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  dsp_jtag_srst_req_n : 1;  /* bit[20]   : DSP JTAG�ӿ���λʹ��״̬��
                                                               0����λʹ�ܳ�����
                                                               1����λʹ�ܡ� */
        unsigned int  reserved_2          : 1;  /* bit[21]   : ���� */
        unsigned int  reserved_3          : 10; /* bit[22-31]: ���� */
    } reg;
} SOC_ASP_CFG_R_RST_CTRLSTAT_UNION;
#endif
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_audio_n_START      (0)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_audio_n_END        (0)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_voice_n_START      (1)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_voice_n_END        (1)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_bt_n_START         (2)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_bt_n_END           (2)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_modem_n_START      (3)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_sio_modem_n_END        (3)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_dsp_n_START            (4)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_dsp_n_END              (4)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_dsp_debug_n_START      (5)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_dsp_debug_n_END        (5)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_ipc_n_START            (6)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_ipc_n_END              (6)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_asp_hdmi_n_START       (7)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_asp_hdmi_n_END         (7)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_dmac_n_START           (8)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_dmac_n_END             (8)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_ocram_n_START          (11)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_ocram_n_END            (11)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_watchdog_n_START       (12)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_watchdog_n_END         (12)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_slimbus_base_n_START   (13)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_slimbus_base_n_END     (13)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_slimbus_n_START        (14)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_slimbus_n_END          (14)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_asp_h2x_n_START        (15)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_asp_h2x_n_END          (15)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_gpio_n_START           (16)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_gpio_n_END             (16)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_timer0_n_START         (17)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_timer0_n_END           (17)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_timer1_n_START         (18)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_rst_timer1_n_END           (18)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_dsp_preset_req_n_START     (19)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_dsp_preset_req_n_END       (19)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_dsp_jtag_srst_req_n_START  (20)
#define SOC_ASP_CFG_R_RST_CTRLSTAT_dsp_jtag_srst_req_n_END    (20)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_GATE_EN_UNION
 �ṹ˵��  : R_GATE_EN �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ʱ��ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_hifidspclk        : 1;  /* bit[0]    : dspʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_audiobclk_out     : 1;  /* bit[1]    : sio_audio bclk���ʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_sioaudio          : 1;  /* bit[2]    : sio_audioʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_voicebclk_out     : 1;  /* bit[3]    : sio_voice bclk���ʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_siovoice          : 1;  /* bit[4]    : sio_voiceʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_btbclk_out        : 1;  /* bit[5]    : sio_bt bclk���ʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_siobt             : 1;  /* bit[6]    : sio_btʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_modembclk_out     : 1;  /* bit[7]    : sio_modem bclk���ʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_siomodem          : 1;  /* bit[8]    : sio_modemʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_ipchclk           : 1;  /* bit[9]    : ipcʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_hdmihclk          : 1;  /* bit[10]   : asp_hdmi hclkʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_dmachclk          : 1;  /* bit[11]   : asp_dmacʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  reserved_0           : 1;  /* bit[12]   :  */
        unsigned int  reserved_1           : 1;  /* bit[13]   :  */
        unsigned int  gt_ocramhclk         : 1;  /* bit[14]   : ocramʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_wdhclk            : 1;  /* bit[15]   : watch dogʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_slimbushclk       : 1;  /* bit[16]   : slimbus hclkʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_slimbus_base_clk  : 1;  /* bit[17]   : slimbus base clkʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_hdmimclk          : 1;  /* bit[18]   : hdmi mclkʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_spdifclk          : 1;  /* bit[19]   : asp_hdmiģ��spdifclkʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_hdmibclk          : 1;  /* bit[20]   : asp_hdmiģ��bclkʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_gpiohclk          : 1;  /* bit[21]   : gpioʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_timer0hclk        : 1;  /* bit[22]   : timer0ʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_timer1hclk        : 1;  /* bit[23]   : timer1ʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_ppll0_slimbus : 1;  /* bit[24]   : �͸�AOCRG��Ӳ�߿����źţ������͸�audio_subsys��slimbusʱ�ӷ�Ƶ��clk_ppll0ʱ���ſأ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  reserved_2           : 7;  /* bit[25-31]:  */
    } reg;
} SOC_ASP_CFG_R_GATE_EN_UNION;
#endif
#define SOC_ASP_CFG_R_GATE_EN_gt_hifidspclk_START         (0)
#define SOC_ASP_CFG_R_GATE_EN_gt_hifidspclk_END           (0)
#define SOC_ASP_CFG_R_GATE_EN_gt_audiobclk_out_START      (1)
#define SOC_ASP_CFG_R_GATE_EN_gt_audiobclk_out_END        (1)
#define SOC_ASP_CFG_R_GATE_EN_gt_sioaudio_START           (2)
#define SOC_ASP_CFG_R_GATE_EN_gt_sioaudio_END             (2)
#define SOC_ASP_CFG_R_GATE_EN_gt_voicebclk_out_START      (3)
#define SOC_ASP_CFG_R_GATE_EN_gt_voicebclk_out_END        (3)
#define SOC_ASP_CFG_R_GATE_EN_gt_siovoice_START           (4)
#define SOC_ASP_CFG_R_GATE_EN_gt_siovoice_END             (4)
#define SOC_ASP_CFG_R_GATE_EN_gt_btbclk_out_START         (5)
#define SOC_ASP_CFG_R_GATE_EN_gt_btbclk_out_END           (5)
#define SOC_ASP_CFG_R_GATE_EN_gt_siobt_START              (6)
#define SOC_ASP_CFG_R_GATE_EN_gt_siobt_END                (6)
#define SOC_ASP_CFG_R_GATE_EN_gt_modembclk_out_START      (7)
#define SOC_ASP_CFG_R_GATE_EN_gt_modembclk_out_END        (7)
#define SOC_ASP_CFG_R_GATE_EN_gt_siomodem_START           (8)
#define SOC_ASP_CFG_R_GATE_EN_gt_siomodem_END             (8)
#define SOC_ASP_CFG_R_GATE_EN_gt_ipchclk_START            (9)
#define SOC_ASP_CFG_R_GATE_EN_gt_ipchclk_END              (9)
#define SOC_ASP_CFG_R_GATE_EN_gt_hdmihclk_START           (10)
#define SOC_ASP_CFG_R_GATE_EN_gt_hdmihclk_END             (10)
#define SOC_ASP_CFG_R_GATE_EN_gt_dmachclk_START           (11)
#define SOC_ASP_CFG_R_GATE_EN_gt_dmachclk_END             (11)
#define SOC_ASP_CFG_R_GATE_EN_gt_ocramhclk_START          (14)
#define SOC_ASP_CFG_R_GATE_EN_gt_ocramhclk_END            (14)
#define SOC_ASP_CFG_R_GATE_EN_gt_wdhclk_START             (15)
#define SOC_ASP_CFG_R_GATE_EN_gt_wdhclk_END               (15)
#define SOC_ASP_CFG_R_GATE_EN_gt_slimbushclk_START        (16)
#define SOC_ASP_CFG_R_GATE_EN_gt_slimbushclk_END          (16)
#define SOC_ASP_CFG_R_GATE_EN_gt_slimbus_base_clk_START   (17)
#define SOC_ASP_CFG_R_GATE_EN_gt_slimbus_base_clk_END     (17)
#define SOC_ASP_CFG_R_GATE_EN_gt_hdmimclk_START           (18)
#define SOC_ASP_CFG_R_GATE_EN_gt_hdmimclk_END             (18)
#define SOC_ASP_CFG_R_GATE_EN_gt_spdifclk_START           (19)
#define SOC_ASP_CFG_R_GATE_EN_gt_spdifclk_END             (19)
#define SOC_ASP_CFG_R_GATE_EN_gt_hdmibclk_START           (20)
#define SOC_ASP_CFG_R_GATE_EN_gt_hdmibclk_END             (20)
#define SOC_ASP_CFG_R_GATE_EN_gt_gpiohclk_START           (21)
#define SOC_ASP_CFG_R_GATE_EN_gt_gpiohclk_END             (21)
#define SOC_ASP_CFG_R_GATE_EN_gt_timer0hclk_START         (22)
#define SOC_ASP_CFG_R_GATE_EN_gt_timer0hclk_END           (22)
#define SOC_ASP_CFG_R_GATE_EN_gt_timer1hclk_START         (23)
#define SOC_ASP_CFG_R_GATE_EN_gt_timer1hclk_END           (23)
#define SOC_ASP_CFG_R_GATE_EN_gt_clk_ppll0_slimbus_START  (24)
#define SOC_ASP_CFG_R_GATE_EN_gt_clk_ppll0_slimbus_END    (24)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_GATE_DIS_UNION
 �ṹ˵��  : R_GATE_DIS �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: ʱ�ӽ�ֹ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_hifidspclk        : 1;  /* bit[0]    : dspʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_audiobclk_out     : 1;  /* bit[1]    : sio_audio bclk���ʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_sioaudio          : 1;  /* bit[2]    : sio_audioʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_voicebclk_out     : 1;  /* bit[3]    : sio_voice bclk���ʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_siovoice          : 1;  /* bit[4]    : sio_voiceʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_btbclk_out        : 1;  /* bit[5]    : sio_bt bclk���ʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_siobt             : 1;  /* bit[6]    : sio_btʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_modembclk_out     : 1;  /* bit[7]    : sio_modem bclk���ʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_siomodem          : 1;  /* bit[8]    : sio_modemʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_ipchclk           : 1;  /* bit[9]    : ipcʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_hdmihclk          : 1;  /* bit[10]   : asp_hdmi hclkʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_dmachclk          : 1;  /* bit[11]   : asp_dmacʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  reserved_0           : 1;  /* bit[12]   :  */
        unsigned int  reserved_1           : 1;  /* bit[13]   :  */
        unsigned int  gt_ocramhclk         : 1;  /* bit[14]   : ocramʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_wdhclk            : 1;  /* bit[15]   : watch dogʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_slimbushclk       : 1;  /* bit[16]   : slimbus hclkʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_slimbus_base_clk  : 1;  /* bit[17]   : slimbus base clkʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_hdmimclk          : 1;  /* bit[18]   : hdmi mclkʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_spdifclk          : 1;  /* bit[19]   : asp_hdmiģ��spdifclkʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_hdmibclk          : 1;  /* bit[20]   : asp_hdmiģ��bclkʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_gpiohclk          : 1;  /* bit[21]   : gpioʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_timer0hclk        : 1;  /* bit[22]   : timer0ʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_timer1hclk        : 1;  /* bit[23]   : timer1ʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_ppll0_slimbus : 1;  /* bit[24]   : �͸�AOCRG��Ӳ�߿����źţ������͸�audio_subsys��slimbusʱ�ӷ�Ƶ��clk_ppll0ʱ���ſأ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  reserved_2           : 7;  /* bit[25-31]:  */
    } reg;
} SOC_ASP_CFG_R_GATE_DIS_UNION;
#endif
#define SOC_ASP_CFG_R_GATE_DIS_gt_hifidspclk_START         (0)
#define SOC_ASP_CFG_R_GATE_DIS_gt_hifidspclk_END           (0)
#define SOC_ASP_CFG_R_GATE_DIS_gt_audiobclk_out_START      (1)
#define SOC_ASP_CFG_R_GATE_DIS_gt_audiobclk_out_END        (1)
#define SOC_ASP_CFG_R_GATE_DIS_gt_sioaudio_START           (2)
#define SOC_ASP_CFG_R_GATE_DIS_gt_sioaudio_END             (2)
#define SOC_ASP_CFG_R_GATE_DIS_gt_voicebclk_out_START      (3)
#define SOC_ASP_CFG_R_GATE_DIS_gt_voicebclk_out_END        (3)
#define SOC_ASP_CFG_R_GATE_DIS_gt_siovoice_START           (4)
#define SOC_ASP_CFG_R_GATE_DIS_gt_siovoice_END             (4)
#define SOC_ASP_CFG_R_GATE_DIS_gt_btbclk_out_START         (5)
#define SOC_ASP_CFG_R_GATE_DIS_gt_btbclk_out_END           (5)
#define SOC_ASP_CFG_R_GATE_DIS_gt_siobt_START              (6)
#define SOC_ASP_CFG_R_GATE_DIS_gt_siobt_END                (6)
#define SOC_ASP_CFG_R_GATE_DIS_gt_modembclk_out_START      (7)
#define SOC_ASP_CFG_R_GATE_DIS_gt_modembclk_out_END        (7)
#define SOC_ASP_CFG_R_GATE_DIS_gt_siomodem_START           (8)
#define SOC_ASP_CFG_R_GATE_DIS_gt_siomodem_END             (8)
#define SOC_ASP_CFG_R_GATE_DIS_gt_ipchclk_START            (9)
#define SOC_ASP_CFG_R_GATE_DIS_gt_ipchclk_END              (9)
#define SOC_ASP_CFG_R_GATE_DIS_gt_hdmihclk_START           (10)
#define SOC_ASP_CFG_R_GATE_DIS_gt_hdmihclk_END             (10)
#define SOC_ASP_CFG_R_GATE_DIS_gt_dmachclk_START           (11)
#define SOC_ASP_CFG_R_GATE_DIS_gt_dmachclk_END             (11)
#define SOC_ASP_CFG_R_GATE_DIS_gt_ocramhclk_START          (14)
#define SOC_ASP_CFG_R_GATE_DIS_gt_ocramhclk_END            (14)
#define SOC_ASP_CFG_R_GATE_DIS_gt_wdhclk_START             (15)
#define SOC_ASP_CFG_R_GATE_DIS_gt_wdhclk_END               (15)
#define SOC_ASP_CFG_R_GATE_DIS_gt_slimbushclk_START        (16)
#define SOC_ASP_CFG_R_GATE_DIS_gt_slimbushclk_END          (16)
#define SOC_ASP_CFG_R_GATE_DIS_gt_slimbus_base_clk_START   (17)
#define SOC_ASP_CFG_R_GATE_DIS_gt_slimbus_base_clk_END     (17)
#define SOC_ASP_CFG_R_GATE_DIS_gt_hdmimclk_START           (18)
#define SOC_ASP_CFG_R_GATE_DIS_gt_hdmimclk_END             (18)
#define SOC_ASP_CFG_R_GATE_DIS_gt_spdifclk_START           (19)
#define SOC_ASP_CFG_R_GATE_DIS_gt_spdifclk_END             (19)
#define SOC_ASP_CFG_R_GATE_DIS_gt_hdmibclk_START           (20)
#define SOC_ASP_CFG_R_GATE_DIS_gt_hdmibclk_END             (20)
#define SOC_ASP_CFG_R_GATE_DIS_gt_gpiohclk_START           (21)
#define SOC_ASP_CFG_R_GATE_DIS_gt_gpiohclk_END             (21)
#define SOC_ASP_CFG_R_GATE_DIS_gt_timer0hclk_START         (22)
#define SOC_ASP_CFG_R_GATE_DIS_gt_timer0hclk_END           (22)
#define SOC_ASP_CFG_R_GATE_DIS_gt_timer1hclk_START         (23)
#define SOC_ASP_CFG_R_GATE_DIS_gt_timer1hclk_END           (23)
#define SOC_ASP_CFG_R_GATE_DIS_gt_clk_ppll0_slimbus_START  (24)
#define SOC_ASP_CFG_R_GATE_DIS_gt_clk_ppll0_slimbus_END    (24)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_GATE_CLKEN_UNION
 �ṹ˵��  : R_GATE_CLKEN �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: ʱ��ʹ��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_hifidspclk        : 1;  /* bit[0]    : dspʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_audiobclk_out     : 1;  /* bit[1]    : sio_audio bclk���ʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_sioaudio          : 1;  /* bit[2]    : sio_audioʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_voicebclk_out     : 1;  /* bit[3]    : sio_voice bclk���ʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_siovoice          : 1;  /* bit[4]    : sio_voiceʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_btbclk_out        : 1;  /* bit[5]    : sio_bt bclk���ʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_siobt             : 1;  /* bit[6]    : sio_btʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_modembclk_out     : 1;  /* bit[7]    : sio_modem bclk���ʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_siomodem          : 1;  /* bit[8]    : sio_modemʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_ipchclk           : 1;  /* bit[9]    : ipcʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_hdmihclk          : 1;  /* bit[10]   : asp_hdmi hclkʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_dmachclk          : 1;  /* bit[11]   : asp_dmacʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  reserved_0           : 1;  /* bit[12]   :  */
        unsigned int  reserved_1           : 1;  /* bit[13]   :  */
        unsigned int  gt_ocramhclk         : 1;  /* bit[14]   : ocramʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_wdhclk            : 1;  /* bit[15]   : watch dogʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_slimbushclk       : 1;  /* bit[16]   : slimbus hclkʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_slimbus_base_clk  : 1;  /* bit[17]   : slimbus base clkʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_hdmimclk          : 1;  /* bit[18]   : hdmi mclkʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_spdifclk          : 1;  /* bit[19]   : asp_hdmiģ��spdifclkʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_hdmibclk          : 1;  /* bit[20]   : asp_hdmiģ��bclkʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_gpiohclk          : 1;  /* bit[21]   : gpioʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_timer0hclk        : 1;  /* bit[22]   : timer0ʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_timer1hclk        : 1;  /* bit[23]   : timer1ʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_ppll0_slimbus : 1;  /* bit[24]   : �͸�AOCRG��Ӳ�߿����źţ������͸�audio_subsys��slimbusʱ�ӷ�Ƶ��clk_ppll0ʱ���ſأ�
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  reserved_2           : 7;  /* bit[25-31]:  */
    } reg;
} SOC_ASP_CFG_R_GATE_CLKEN_UNION;
#endif
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hifidspclk_START         (0)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hifidspclk_END           (0)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_audiobclk_out_START      (1)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_audiobclk_out_END        (1)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_sioaudio_START           (2)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_sioaudio_END             (2)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_voicebclk_out_START      (3)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_voicebclk_out_END        (3)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_siovoice_START           (4)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_siovoice_END             (4)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_btbclk_out_START         (5)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_btbclk_out_END           (5)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_siobt_START              (6)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_siobt_END                (6)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_modembclk_out_START      (7)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_modembclk_out_END        (7)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_siomodem_START           (8)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_siomodem_END             (8)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_ipchclk_START            (9)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_ipchclk_END              (9)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hdmihclk_START           (10)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hdmihclk_END             (10)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_dmachclk_START           (11)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_dmachclk_END             (11)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_ocramhclk_START          (14)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_ocramhclk_END            (14)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_wdhclk_START             (15)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_wdhclk_END               (15)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_slimbushclk_START        (16)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_slimbushclk_END          (16)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_slimbus_base_clk_START   (17)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_slimbus_base_clk_END     (17)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hdmimclk_START           (18)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hdmimclk_END             (18)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_spdifclk_START           (19)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_spdifclk_END             (19)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hdmibclk_START           (20)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_hdmibclk_END             (20)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_gpiohclk_START           (21)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_gpiohclk_END             (21)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_timer0hclk_START         (22)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_timer0hclk_END           (22)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_timer1hclk_START         (23)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_timer1hclk_END           (23)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_clk_ppll0_slimbus_START  (24)
#define SOC_ASP_CFG_R_GATE_CLKEN_gt_clk_ppll0_slimbus_END    (24)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_GATE_CLKSTAT_UNION
 �ṹ˵��  : R_GATE_CLKSTAT �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: ʱ������״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  st_hifidspclk       : 1;  /* bit[0] : dspʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_audiobclk_out    : 1;  /* bit[1] : sio_audio bclk���ʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_audiobclk        : 1;  /* bit[2] : sio_audio bclkʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_voicebclk_out    : 1;  /* bit[3] : sio_voice bclk���ʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_siovoice         : 1;  /* bit[4] : sio_voice bclkʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_btbclk_out       : 1;  /* bit[5] : sio_bt bclk���ʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_siobt            : 1;  /* bit[6] : sio_bt bclkʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_modembclk_out    : 1;  /* bit[7] : sio_modem bclk���ʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_siomodem         : 1;  /* bit[8] : sio_modem bclkʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_ipchclk          : 1;  /* bit[9] : ipcʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_hdmihclk         : 1;  /* bit[10]: asp_hdmi hclkʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_dmachclk0        : 1;  /* bit[11]: asp_dmac hclk0ʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_dmachclk1        : 1;  /* bit[12]: asp_dmac hclk1ʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  reserved_0          : 1;  /* bit[13]:  */
        unsigned int  reserved_1          : 1;  /* bit[14]:  */
        unsigned int  st_ocramhclk        : 1;  /* bit[15]: ocramʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_wdhclk           : 1;  /* bit[16]: watch dogʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_slimbushclk      : 1;  /* bit[17]: slimbus hclkʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_slimbus_base_clk : 1;  /* bit[18]: slimbus base clkʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_hdmimclk         : 1;  /* bit[19]: hdmi mclkʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_spdifclk         : 1;  /* bit[20]: asp_hdmiģ��spdifclkʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_hdmiref          : 1;  /* bit[21]: asp_hdmiģ��refclkʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_asp_h2x          : 1;  /* bit[22]: ��ǿ��h2xʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_audiohclk        : 1;  /* bit[23]: sio_audio hclkʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_voicehclk        : 1;  /* bit[24]: sio_voice hclkʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_bthclk           : 1;  /* bit[25]: sio_bt hclkʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_modemhclk        : 1;  /* bit[26]: sio_modem hclkʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_gpiohclk         : 1;  /* bit[27]: gpioʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_timer0hclk       : 1;  /* bit[28]: timer0ʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_timer1hclk       : 1;  /* bit[29]: timer1ʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  st_hdmibclk         : 1;  /* bit[30]: hdmi bclkʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  reserved_2          : 1;  /* bit[31]: �����Ĵ����ĸ�λֵ��asp_cfg������ʱ������״̬�źŵĸ�λֵ������ */
    } reg;
} SOC_ASP_CFG_R_GATE_CLKSTAT_UNION;
#endif
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hifidspclk_START        (0)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hifidspclk_END          (0)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_audiobclk_out_START     (1)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_audiobclk_out_END       (1)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_audiobclk_START         (2)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_audiobclk_END           (2)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_voicebclk_out_START     (3)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_voicebclk_out_END       (3)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_siovoice_START          (4)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_siovoice_END            (4)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_btbclk_out_START        (5)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_btbclk_out_END          (5)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_siobt_START             (6)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_siobt_END               (6)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_modembclk_out_START     (7)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_modembclk_out_END       (7)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_siomodem_START          (8)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_gt_siomodem_END            (8)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_ipchclk_START           (9)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_ipchclk_END             (9)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmihclk_START          (10)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmihclk_END            (10)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_dmachclk0_START         (11)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_dmachclk0_END           (11)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_dmachclk1_START         (12)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_dmachclk1_END           (12)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_ocramhclk_START         (15)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_ocramhclk_END           (15)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_wdhclk_START            (16)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_wdhclk_END              (16)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_slimbushclk_START       (17)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_slimbushclk_END         (17)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_slimbus_base_clk_START  (18)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_slimbus_base_clk_END    (18)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmimclk_START          (19)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmimclk_END            (19)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_spdifclk_START          (20)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_spdifclk_END            (20)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmiref_START           (21)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmiref_END             (21)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_asp_h2x_START           (22)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_asp_h2x_END             (22)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_audiohclk_START         (23)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_audiohclk_END           (23)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_voicehclk_START         (24)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_voicehclk_END           (24)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_bthclk_START            (25)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_bthclk_END              (25)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_modemhclk_START         (26)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_modemhclk_END           (26)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_gpiohclk_START          (27)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_gpiohclk_END            (27)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_timer0hclk_START        (28)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_timer0hclk_END          (28)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_timer1hclk_START        (29)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_timer1hclk_END          (29)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmibclk_START          (30)
#define SOC_ASP_CFG_R_GATE_CLKSTAT_st_hdmibclk_END            (30)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_GATE_CLKDIV_EN_UNION
 �ṹ˵��  : R_GATE_CLKDIV_EN �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x000001FF�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ���ſ�ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_hdmimclk_div       : 1;  /* bit[0]   : hdmi mclkС����Ƶ��ʱ��ʹ�ܣ�С����Ƶ����μ�R_CLK2_DIV�Ĵ�����˵������
                                                                0��IPʱ�ӽ�ֹ��
                                                                1��IPʱ��ʹ�ܡ�
                                                                ���Ҫ��asp_hdmi������������spdif������Ƕ�����i2s�����������Ҫʹ�ܴ�ʱ�ӡ� */
        unsigned int  gt_hdmiref_div        : 1;  /* bit[1]   : hdmi refclk 2��Ƶ��ʱ��ʹ�ܣ�
                                                                0��IPʱ�ӽ�ֹ��
                                                                1��IPʱ��ʹ�ܡ�
                                                                ���Ҫ��asp_hdmi�ڶ�����i2s�������¹���������Ҫʹ�ܴ�ʱ�ӡ� */
        unsigned int  gt_siobclk_div        : 1;  /* bit[2]   : С����Ƶ��siobclk_div������ʱ��ʹ�ܣ�С����Ƶ����μ�R_CLK1_DIV�Ĵ�����˵������
                                                                0��IPʱ�ӽ�ֹ��
                                                                1��IPʱ��ʹ�ܡ�
                                                                ���Ҫ��sio_audio��sio_voice��sio_bt��sio_modem�е�����һ����masterģʽ�¹���������Ҫʹ�ܴ�ʱ�ӣ�
                                                                ���Ҫ��slimbus base clkѡ��С����Ƶ��siobclk_div�����ʱ�ӣ�����Ҫʹ�ܴ˼Ĵ����� */
        unsigned int  gt_sio_audio_bclk_div : 1;  /* bit[3]   : sio_audio bclk ������Ƶ��ʱ��ʹ�ܣ�������Ƶ����μ�R_CLK3_DIV�Ĵ�����div_sio_audio_bclkλ����
                                                                0��IPʱ�ӽ�ֹ��
                                                                1��IPʱ��ʹ�ܡ�
                                                                �����Ҫ��sio_audio��masterģʽ�¹���������Ҫʹ�ܴ�ʱ�ӡ� */
        unsigned int  gt_sio_voice_bclk_div : 1;  /* bit[4]   : sio_voice bclk ������Ƶ��ʱ��ʹ�ܣ�������Ƶ����μ�R_CLK3_DIV�Ĵ�����div_sio_audio_bclkλ����
                                                                0��IPʱ�ӽ�ֹ��
                                                                1��IPʱ��ʹ�ܡ�
                                                                �����Ҫ��sio_audio��masterģʽ�¹���������Ҫʹ�ܴ�ʱ�ӡ� */
        unsigned int  gt_sio_bt_bclk_div    : 1;  /* bit[5]   : sio_bt bclk ������Ƶ��ʱ��ʹ�ܣ�������Ƶ����μ�R_CLK3_DIV�Ĵ�����div_sio_audio_bclkλ����
                                                                0��IPʱ�ӽ�ֹ��
                                                                1��IPʱ��ʹ�ܡ�
                                                                �����Ҫ��sio_audio��masterģʽ�¹���������Ҫʹ�ܴ�ʱ�ӡ� */
        unsigned int  gt_sio_modem_bclk_div : 1;  /* bit[6]   : sio_modem bclk ������Ƶ��ʱ��ʹ�ܣ�������Ƶ����μ�R_CLK3_DIV�Ĵ�����div_sio_audio_bclkλ����
                                                                0��IPʱ�ӽ�ֹ��
                                                                1��IPʱ��ʹ�ܡ�
                                                                �����Ҫ��sio_audio��masterģʽ�¹���������Ҫʹ�ܴ�ʱ�ӡ� */
        unsigned int  gt_asp_tcxo_div       : 1;  /* bit[7]   : ����19.2Mʱ�ӵĹ̶�4��Ƶ��ʱ��ʹ�ܣ�
                                                                0��IPʱ�ӽ�ֹ��
                                                                1��IPʱ��ʹ�ܡ�
                                                                ���Ҫ��asp��timer��4.8MƵ���¹���������Ҫʹ�ܴ�ʱ�ӡ� */
        unsigned int  gt_slimbus_clk_div    : 1;  /* bit[8]   : ppll0С����Ƶ��ʱ��ʹ�ܣ�
                                                                0��IPʱ�ӽ�ֹ��
                                                                1��IPʱ��ʹ�ܡ�
                                                                ���Ҫ��asp��slimbusʱ�Ӵ�ppll0С����Ƶ�õ�������Ҫʹ�ܴ�ʱ�ӡ� */
        unsigned int  reserved              : 23; /* bit[9-31]:  */
    } reg;
} SOC_ASP_CFG_R_GATE_CLKDIV_EN_UNION;
#endif
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_hdmimclk_div_START        (0)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_hdmimclk_div_END          (0)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_hdmiref_div_START         (1)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_hdmiref_div_END           (1)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_siobclk_div_START         (2)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_siobclk_div_END           (2)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_audio_bclk_div_START  (3)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_audio_bclk_div_END    (3)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_voice_bclk_div_START  (4)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_voice_bclk_div_END    (4)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_bt_bclk_div_START     (5)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_bt_bclk_div_END       (5)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_modem_bclk_div_START  (6)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_sio_modem_bclk_div_END    (6)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_asp_tcxo_div_START        (7)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_asp_tcxo_div_END          (7)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_slimbus_clk_div_START     (8)
#define SOC_ASP_CFG_R_GATE_CLKDIV_EN_gt_slimbus_clk_div_END       (8)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_CLK1_DIV_UNION
 �ṹ˵��  : R_CLK1_DIV �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x0147AE14�����:32
 �Ĵ���˵��: ��Ƶ�ȿ��ƼĴ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_siobclk : 27; /* bit[0-26] : С����Ƶϵ��div_siobclk[26:0]�����ڲ���siobclk_div��
                                                       ��Ƶʱ��Ƶ��=div_siobclk[26:0]/2^27*Դʱ��Ƶ�ʣ�
                                                       Դʱ����19.2M����480M����ѡ����μ�R_CLK_SEL�Ĵ�����siobclk_selλ��
                                                       Դʱ�ӿ��Ա�R_GATE_CLKDIV_EN�Ĵ�����gt_siobclk_divλ�ſأ� */
        unsigned int  reserved    : 5;  /* bit[27-31]:  */
    } reg;
} SOC_ASP_CFG_R_CLK1_DIV_UNION;
#endif
#define SOC_ASP_CFG_R_CLK1_DIV_div_siobclk_START  (0)
#define SOC_ASP_CFG_R_CLK1_DIV_div_siobclk_END    (26)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_CLK2_DIV_UNION
 �ṹ˵��  : R_CLK2_DIV �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x01179EC9�����:32
 �Ĵ���˵��: ��Ƶ�ȿ��ƼĴ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_hdmimclk : 27; /* bit[0-26] : С����Ƶϵ��div_hdmimclk[26:0]�����ڲ���hdmimclk_in
                                                        ��Ƶʱ��Ƶ��=div_hdmimclk[26:0]/2^27*Դʱ��Ƶ�ʣ�
                                                        Դʱ����480M��
                                                        Դʱ�ӿ��Ա�R_GATE_CLKDIV_EN�Ĵ�����gt_hdmimclk_divλ�ſأ� */
        unsigned int  reserved     : 5;  /* bit[27-31]:  */
    } reg;
} SOC_ASP_CFG_R_CLK2_DIV_UNION;
#endif
#define SOC_ASP_CFG_R_CLK2_DIV_div_hdmimclk_START  (0)
#define SOC_ASP_CFG_R_CLK2_DIV_div_hdmimclk_END    (26)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_CLK3_DIV_UNION
 �ṹ˵��  : R_CLK3_DIV �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00001707�����:32
 �Ĵ���˵��: ��Ƶ�ȿ��ƼĴ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_sio_audio_bclk : 8;  /* bit[0-7]  : ������Ƶϵ��div_sio_audio_bclk�����ڲ���masterģʽ�µ�sio_audio_bclk��
                                                              8'h0:1��
                                                              8'h1:2��
                                                              8'h2:3��
                                                              ��
                                                              8'hFE:255��
                                                              8'hFF:256��
                                                              Դʱ����siobclk_div��siobclk_div��μ�R_CLK1_DIV�Ĵ�����˵����
                                                              Դʱ�ӿ��Ա�R_GATE_CLKDIV_EN�Ĵ�����gt_sio_audio_bclk_divλ�ſأ� */
        unsigned int  div_sio_voice_bclk : 8;  /* bit[8-15] : ������Ƶϵ��div_sio_voice_bclk�����ڲ���masterģʽ�µ�sio_voice_bclk��
                                                              8'h0:1��
                                                              8'h1:2��
                                                              8'h2:3��
                                                              ��
                                                              8'hFE:255��
                                                              8'hFF:256��
                                                              Դʱ����siobclk_div��siobclk_div��μ�R_CLK1_DIV�Ĵ�����˵����
                                                              Դʱ�ӿ��Ա�R_GATE_CLKDIV_EN�Ĵ�����gt_sio_voice_bclk_divλ�ſأ� */
        unsigned int  write_en           : 16; /* bit[16-31]: R_CLK3_DIVÿ������λ��дʹ��λ��
                                                              ֻ�е�write_en��Ӧ�ı���λΪ1'b1����R_CLK3_DIV��Ӧ�ı���λ��д�����������á�write_en[0]����R_CLK3_DIV[0]��дʹ��λ��д1��Ч�� */
    } reg;
} SOC_ASP_CFG_R_CLK3_DIV_UNION;
#endif
#define SOC_ASP_CFG_R_CLK3_DIV_div_sio_audio_bclk_START  (0)
#define SOC_ASP_CFG_R_CLK3_DIV_div_sio_audio_bclk_END    (7)
#define SOC_ASP_CFG_R_CLK3_DIV_div_sio_voice_bclk_START  (8)
#define SOC_ASP_CFG_R_CLK3_DIV_div_sio_voice_bclk_END    (15)
#define SOC_ASP_CFG_R_CLK3_DIV_write_en_START            (16)
#define SOC_ASP_CFG_R_CLK3_DIV_write_en_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_CLK4_DIV_UNION
 �ṹ˵��  : R_CLK4_DIV �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00001717�����:32
 �Ĵ���˵��: ��Ƶ�ȿ��ƼĴ���4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_sio_bt_bclk    : 8;  /* bit[0-7]  : ������Ƶϵ��div_sio_bt_bclk�����ڲ���masterģʽ�µ�sio_bt_bclk��
                                                              8'h0:1��
                                                              8'h1:2��
                                                              8'h2:3��
                                                              ��
                                                              8'hFE:255��
                                                              8'hFF:256��
                                                              Դʱ����siobclk_div��siobclk_div��μ�R_CLK1_DIV�Ĵ�����˵����
                                                              Դʱ�ӿ��Ա�R_GATE_CLKDIV_EN�Ĵ�����gt_sio_bt_bclk_divλ�ſأ� */
        unsigned int  div_sio_modem_bclk : 8;  /* bit[8-15] : ������Ƶϵ��div_sio_modem_bclk�����ڲ���masterģʽ�µ�sio_modem_bclk��
                                                              8'h0:1��
                                                              8'h1:2��
                                                              8'h2:3��
                                                              ��
                                                              8'hFE:255��
                                                              8'hFF:256��
                                                              Դʱ����siobclk_div��siobclk_div��μ�R_CLK1_DIV�Ĵ�����˵����
                                                              Դʱ�ӿ��Ա�R_GATE_CLKDIV_EN�Ĵ�����gt_sio_modem_bclk_divλ�ſأ� */
        unsigned int  write_en           : 16; /* bit[16-31]: R_CLK4_DIVÿ������λ��дʹ��λ��
                                                              ֻ�е�write_en��Ӧ�ı���λΪ1'b1����R_CLK4_DIV��Ӧ�ı���λ��д�����������á�write_en[0]����R_CLK4_DIV[0]��дʹ��λ��д1��Ч�� */
    } reg;
} SOC_ASP_CFG_R_CLK4_DIV_UNION;
#endif
#define SOC_ASP_CFG_R_CLK4_DIV_div_sio_bt_bclk_START     (0)
#define SOC_ASP_CFG_R_CLK4_DIV_div_sio_bt_bclk_END       (7)
#define SOC_ASP_CFG_R_CLK4_DIV_div_sio_modem_bclk_START  (8)
#define SOC_ASP_CFG_R_CLK4_DIV_div_sio_modem_bclk_END    (15)
#define SOC_ASP_CFG_R_CLK4_DIV_write_en_START            (16)
#define SOC_ASP_CFG_R_CLK4_DIV_write_en_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_CLK5_DIV_UNION
 �ṹ˵��  : R_CLK5_DIV �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00003F3F�����:32
 �Ĵ���˵��: ��Ƶ�ȿ��ƼĴ���5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_sio_audio_adws : 8;  /* bit[0-7]  : ������Ƶϵ��div_sio_audio_adws�����ڲ���masterģʽ�µ�sio_audio_adws
                                                              8'h0:1��
                                                              8'h1:2��
                                                              8'h2:3��
                                                              ��
                                                              8'hFE:255��
                                                              8'hFF:256��
                                                              Դʱ����sio_audio_bclk��sio_audio_bclk��μ�R_CLK3_DIV�Ĵ���div_sio_audio_bclkλ��˵���� */
        unsigned int  div_sio_voice_adws : 8;  /* bit[8-15] : ������Ƶϵ��div_sio_voice_adws�����ڲ���masterģʽ�µ�sio_voice_adws
                                                              8'h0:1��
                                                              8'h1:2��
                                                              8'h2:3��
                                                              ��
                                                              8'hFE:255��
                                                              8'hFF:256��
                                                              Դʱ����sio_voice_bclk��sio_voice_bclk��μ�R_CLK3_DIV�Ĵ���div_sio_voice_bclkλ��˵���� */
        unsigned int  write_en           : 16; /* bit[16-31]: R_CLK5_DIVÿ������λ��дʹ��λ��
                                                              ֻ�е�write_en��Ӧ�ı���λΪ1'b1����R_CLK5_DIV��Ӧ�ı���λ��д�����������á�write_en[0]����R_CLK5_DIV[0]��дʹ��λ��д1��Ч�� */
    } reg;
} SOC_ASP_CFG_R_CLK5_DIV_UNION;
#endif
#define SOC_ASP_CFG_R_CLK5_DIV_div_sio_audio_adws_START  (0)
#define SOC_ASP_CFG_R_CLK5_DIV_div_sio_audio_adws_END    (7)
#define SOC_ASP_CFG_R_CLK5_DIV_div_sio_voice_adws_START  (8)
#define SOC_ASP_CFG_R_CLK5_DIV_div_sio_voice_adws_END    (15)
#define SOC_ASP_CFG_R_CLK5_DIV_write_en_START            (16)
#define SOC_ASP_CFG_R_CLK5_DIV_write_en_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_CLK6_DIV_UNION
 �ṹ˵��  : R_CLK6_DIV �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00003F3F�����:32
 �Ĵ���˵��: ��Ƶ�ȿ��ƼĴ���6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_sio_bt_adws    : 8;  /* bit[0-7]  : ������Ƶϵ��div_sio_bt_adws�����ڲ���masterģʽ�µ�sio_bt_adws
                                                              8'h0:1��
                                                              8'h1:2��
                                                              8'h2:3��
                                                              ��
                                                              8'hFE:255��
                                                              8'hFF:256��
                                                              Դʱ����sio_bt_bclk��sio_bt_bclk��μ�R_CLK4_DIV�Ĵ���div_sio_bt_bclkλ��˵���� */
        unsigned int  div_sio_modem_adws : 8;  /* bit[8-15] : ������Ƶϵ��div_sio_modem_adws�����ڲ���masterģʽ�µ�sio_modem_adws
                                                              8'h0:1��
                                                              8'h1:2��
                                                              8'h2:3��
                                                              ��
                                                              8'hFE:255��
                                                              8'hFF:256��
                                                              Դʱ����sio_modem_bclk��sio_modem_bclk��μ�R_CLK4_DIV�Ĵ���div_sio_modem_bclkλ��˵���� */
        unsigned int  write_en           : 16; /* bit[16-31]: R_CLK6_DIVÿ������λ��дʹ��λ��
                                                              ֻ�е�write_en��Ӧ�ı���λΪ1'b1����R_CLK6_DIV��Ӧ�ı���λ��д�����������á�write_en[0]����R_CLK6_DIV[0]��дʹ��λ��д1��Ч�� */
    } reg;
} SOC_ASP_CFG_R_CLK6_DIV_UNION;
#endif
#define SOC_ASP_CFG_R_CLK6_DIV_div_sio_bt_adws_START     (0)
#define SOC_ASP_CFG_R_CLK6_DIV_div_sio_bt_adws_END       (7)
#define SOC_ASP_CFG_R_CLK6_DIV_div_sio_modem_adws_START  (8)
#define SOC_ASP_CFG_R_CLK6_DIV_div_sio_modem_adws_END    (15)
#define SOC_ASP_CFG_R_CLK6_DIV_write_en_START            (16)
#define SOC_ASP_CFG_R_CLK6_DIV_write_en_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_CLK_SEL_UNION
 �ṹ˵��  : R_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x0000000F�����:32
 �Ĵ���˵��: ʱ��ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio_audio_slave_en   : 1;  /* bit[0]    : sio audio��master��slaveģʽѡ��Ĵ�����
                                                                0��masterģʽ��
                                                                1��slaveģʽ��
                                                                �˼Ĵ���ͬʱҲ��sio audio��ص�˫��IO�ܽ�I2S_XCLK��I2S_XFS����������ѡ��
                                                                0�����ģʽ��
                                                                1������ģʽ�� */
        unsigned int  sio_voice_slave_en   : 1;  /* bit[1]    : sio voice��master��slaveģʽѡ��Ĵ�����
                                                                0��masterģʽ��
                                                                1��slaveģʽ��
                                                                �˼Ĵ���ͬʱҲ��sio voice��ص�˫��IO�ܽ�I2S_XCLK��I2S_XFS����������ѡ��
                                                                0�����ģʽ��
                                                                1������ģʽ�� */
        unsigned int  sio_bt_slave_en      : 1;  /* bit[2]    : sio bt��master��slaveģʽѡ��Ĵ�����
                                                                0��masterģʽ��
                                                                1��slaveģʽ��
                                                                �˼Ĵ���ͬʱҲ��sio bt��ص�˫��IO�ܽ�I2S_XCLK��I2S_XFS����������ѡ��
                                                                0�����ģʽ��
                                                                1������ģʽ�� */
        unsigned int  sio_modem_slave_en   : 1;  /* bit[3]    : sio modem��master��slaveģʽѡ��Ĵ�����
                                                                0��masterģʽ��
                                                                1��slaveģʽ��
                                                                �˼Ĵ���ͬʱҲ��sio modem��ص�˫��IO�ܽ�I2S_XCLK��I2S_XFS����������ѡ��
                                                                0�����ģʽ��
                                                                1������ģʽ�� */
        unsigned int  siobclk_sel          : 1;  /* bit[4]    : С����Ƶ��siobclk_div������Դʱ��Ƶ��ѡ��Ĵ�����
                                                                0��19.2M��
                                                                1��480M��
                                                                ��С����Ƶ��siobclk_div��ؽ��ܻ��ɲο�R_CLK1_DIV�Ĵ����Ľ��ܣ� */
        unsigned int  slimbus_base_clk_sel : 2;  /* bit[5-6]  : slimbus base clk��ʱ���ź�ѡ��Ĵ�����
                                                                0������19.2MHz��
                                                                1������������crg��clk_slimbus�źţ����ź�Ϊ49.152MHz\24.576MHz��
                                                                2��3��С����Ƶ��siobclk_div�������С����Ƶ��siobclk_div��ؽ��ܻ��ɲο�R_CLK1_DIV�Ĵ����Ľ��ܣ� */
        unsigned int  watchdog_clken_sel   : 1;  /* bit[7]    : watchdog��ʱ��ʹ���ź�Ƶ��ѡ��Ĵ�����
                                                                0��32kHz��
                                                                1����Ϊ1�� */
        unsigned int  timer0_1_clken_sel   : 1;  /* bit[8]    : timer0_1��ʱ��ʹ���ź�Ƶ��ѡ��Ĵ�����
                                                                0��32kHz��
                                                                1��4.8MHZ�� */
        unsigned int  timer0_2_clken_sel   : 1;  /* bit[9]    : timer0_2��ʱ��ʹ���ź�Ƶ��ѡ��Ĵ�����
                                                                0��32kHz��
                                                                1��4.8MHZ�� */
        unsigned int  timer1_1_clken_sel   : 1;  /* bit[10]   : timer1_1��ʱ��ʹ���ź�Ƶ��ѡ��Ĵ�����
                                                                0��32kHz��
                                                                1��4.8MHZ�� */
        unsigned int  timer1_2_clken_sel   : 1;  /* bit[11]   : timer1_2��ʱ��ʹ���ź�Ƶ��ѡ��Ĵ�����
                                                                0��32kHz��
                                                                1��4.8MHZ�� */
        unsigned int  reserved_0           : 1;  /* bit[12]   :  */
        unsigned int  reserved_1           : 1;  /* bit[13]   :  */
        unsigned int  hifidsp_clk_sel      : 1;  /* bit[14]   : ������Ƶ��hifidsp_clk_div������Դʱ��Ƶ��ѡ��Ĵ�����
                                                                0��19.2M��
                                                                1��480M��
                                                                ��������Ƶ��hifidsp_clk_div�����ʱ�Ӽ���hifidsp��coreʱ�ӣ� */
        unsigned int  slimbus_clk_sel      : 1;  /* bit[15]   : slimbusʱ��ѡ��Ĵ�����
                                                                0��ppll0С����Ƶ�õ���slimbus clk(49.152MHz\24.576MHz)��
                                                                1��peri crg�����slimbus clk(49.152MHz\24.576MHz)�� */
        unsigned int  write_en             : 16; /* bit[16-31]: R_CLK_SELÿ������λ��дʹ��λ��
                                                                ֻ�е�write_en��Ӧ�ı���λΪ1'b1����R_CLK_SEL��Ӧ�ı���λ��д�����������á�write_en[0]����R_CLK_SEL[0]��дʹ��λ��д1��Ч�� */
    } reg;
} SOC_ASP_CFG_R_CLK_SEL_UNION;
#endif
#define SOC_ASP_CFG_R_CLK_SEL_sio_audio_slave_en_START    (0)
#define SOC_ASP_CFG_R_CLK_SEL_sio_audio_slave_en_END      (0)
#define SOC_ASP_CFG_R_CLK_SEL_sio_voice_slave_en_START    (1)
#define SOC_ASP_CFG_R_CLK_SEL_sio_voice_slave_en_END      (1)
#define SOC_ASP_CFG_R_CLK_SEL_sio_bt_slave_en_START       (2)
#define SOC_ASP_CFG_R_CLK_SEL_sio_bt_slave_en_END         (2)
#define SOC_ASP_CFG_R_CLK_SEL_sio_modem_slave_en_START    (3)
#define SOC_ASP_CFG_R_CLK_SEL_sio_modem_slave_en_END      (3)
#define SOC_ASP_CFG_R_CLK_SEL_siobclk_sel_START           (4)
#define SOC_ASP_CFG_R_CLK_SEL_siobclk_sel_END             (4)
#define SOC_ASP_CFG_R_CLK_SEL_slimbus_base_clk_sel_START  (5)
#define SOC_ASP_CFG_R_CLK_SEL_slimbus_base_clk_sel_END    (6)
#define SOC_ASP_CFG_R_CLK_SEL_watchdog_clken_sel_START    (7)
#define SOC_ASP_CFG_R_CLK_SEL_watchdog_clken_sel_END      (7)
#define SOC_ASP_CFG_R_CLK_SEL_timer0_1_clken_sel_START    (8)
#define SOC_ASP_CFG_R_CLK_SEL_timer0_1_clken_sel_END      (8)
#define SOC_ASP_CFG_R_CLK_SEL_timer0_2_clken_sel_START    (9)
#define SOC_ASP_CFG_R_CLK_SEL_timer0_2_clken_sel_END      (9)
#define SOC_ASP_CFG_R_CLK_SEL_timer1_1_clken_sel_START    (10)
#define SOC_ASP_CFG_R_CLK_SEL_timer1_1_clken_sel_END      (10)
#define SOC_ASP_CFG_R_CLK_SEL_timer1_2_clken_sel_START    (11)
#define SOC_ASP_CFG_R_CLK_SEL_timer1_2_clken_sel_END      (11)
#define SOC_ASP_CFG_R_CLK_SEL_hifidsp_clk_sel_START       (14)
#define SOC_ASP_CFG_R_CLK_SEL_hifidsp_clk_sel_END         (14)
#define SOC_ASP_CFG_R_CLK_SEL_slimbus_clk_sel_START       (15)
#define SOC_ASP_CFG_R_CLK_SEL_slimbus_clk_sel_END         (15)
#define SOC_ASP_CFG_R_CLK_SEL_write_en_START              (16)
#define SOC_ASP_CFG_R_CLK_SEL_write_en_END                (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DSP_NMI_UNION
 �ṹ˵��  : R_DSP_NMI �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSP NMI�жϲ����Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  r_dsp_nmi : 16; /* bit[0-15] : �˼Ĵ���16������λ�򣬲�������dsp��nmi�ж� */
        unsigned int  reserved  : 16; /* bit[16-31]:  */
    } reg;
} SOC_ASP_CFG_R_DSP_NMI_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_NMI_r_dsp_nmi_START  (0)
#define SOC_ASP_CFG_R_DSP_NMI_r_dsp_nmi_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DSP_PRID_UNION
 �ṹ˵��  : R_DSP_PRID �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSP PRID���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_prid : 16; /* bit[0-15] : dsp processor id��ʾ�����ڶ�˵ĳ����� */
        unsigned int  reserved : 16; /* bit[16-31]:  */
    } reg;
} SOC_ASP_CFG_R_DSP_PRID_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_PRID_dsp_prid_START  (0)
#define SOC_ASP_CFG_R_DSP_PRID_dsp_prid_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DSP_RUNSTALL_UNION
 �ṹ˵��  : R_DSP_RUNSTALL �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000001�����:32
 �Ĵ���˵��: DSP RUNSTALL���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_runstall : 1;  /* bit[0]   : runstall=1��ֹͣdsp ��pipeline���ɹص������ڲ��߼������͹��ģ�
                                                       Runstall=0��dsp�ָ�pipeline������ִ�У� */
        unsigned int  reserved     : 31; /* bit[1-31]:  */
    } reg;
} SOC_ASP_CFG_R_DSP_RUNSTALL_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_RUNSTALL_dsp_runstall_START  (0)
#define SOC_ASP_CFG_R_DSP_RUNSTALL_dsp_runstall_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DSP_STATVECTORSEL_UNION
 �ṹ˵��  : R_DSP_STATVECTORSEL �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSP STATVECTORSEL���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_statvectorsel : 1;  /* bit[0]   : dsp������ַѡ��
                                                            dsp_statvectorsel=0��dsp��ITCM������
                                                            dsp_statvectorsel=1��dsp��DDR������ */
        unsigned int  reserved          : 31; /* bit[1-31]:  */
    } reg;
} SOC_ASP_CFG_R_DSP_STATVECTORSEL_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_STATVECTORSEL_dsp_statvectorsel_START  (0)
#define SOC_ASP_CFG_R_DSP_STATVECTORSEL_dsp_statvectorsel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DSP_OCDHALTONRESET_UNION
 �ṹ˵��  : R_DSP_OCDHALTONRESET �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSP OCDHALTONRESET���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_ocdhaltonreset : 1;  /* bit[0]   : Ocdhaltonreset=1��ǿ��dsp����OCDHaltMode��
                                                             Ocdhaltonreset=0��dsp������������ģʽ�� */
        unsigned int  reserved           : 31; /* bit[1-31]:  */
    } reg;
} SOC_ASP_CFG_R_DSP_OCDHALTONRESET_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_OCDHALTONRESET_dsp_ocdhaltonreset_START  (0)
#define SOC_ASP_CFG_R_DSP_OCDHALTONRESET_dsp_ocdhaltonreset_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DSP_STATUS_UNION
 �ṹ˵��  : R_DSP_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSP ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_xocdmode  : 1;  /* bit[0]   : xocdmode=0��dspû�д���OCD halt ģʽ��
                                                        xocdmode=1��dsp����OCD halt ģʽ�� */
        unsigned int  dsp_pwaitmode : 1;  /* bit[1]   : pwaitmode=0��dspû�д���sleep modeģʽ��
                                                        pwaitmode=1��dsp����sleep modeģʽ�� */
        unsigned int  reserved      : 30; /* bit[2-31]: �����Ĵ����ĸ�λֵ��asp_cfg������dsp״̬�źŵĸ�λֵ������ */
    } reg;
} SOC_ASP_CFG_R_DSP_STATUS_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_STATUS_dsp_xocdmode_START   (0)
#define SOC_ASP_CFG_R_DSP_STATUS_dsp_xocdmode_END     (0)
#define SOC_ASP_CFG_R_DSP_STATUS_dsp_pwaitmode_START  (1)
#define SOC_ASP_CFG_R_DSP_STATUS_dsp_pwaitmode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DMAC_SEL_UNION
 �ṹ˵��  : R_DMAC_SEL �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMACͨ��ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0]    :  */
        unsigned int  reserved_1: 1;  /* bit[1]    :  */
        unsigned int  reserved_2: 1;  /* bit[2]    :  */
        unsigned int  reserved_3: 1;  /* bit[3]    :  */
        unsigned int  reserved_4: 1;  /* bit[4]    :  */
        unsigned int  reserved_5: 1;  /* bit[5]    :  */
        unsigned int  reserved_6: 1;  /* bit[6]    :  */
        unsigned int  reserved_7: 1;  /* bit[7]    :  */
        unsigned int  reserved_8: 2;  /* bit[8-9]  :  */
        unsigned int  reserved_9: 6;  /* bit[10-15]:  */
        unsigned int  write_en : 16; /* bit[16-31]: R_DMAC_SELÿ������λ��дʹ��λ��
                                                    ֻ�е�write_en��Ӧ�ı���λΪ1'b1����R_DMAC_SEL��Ӧ�ı���λ��д�����������á�write_en[0]����R_DMAC_SEL[0]��дʹ��λ��д1��Ч�� */
    } reg;
} SOC_ASP_CFG_R_DMAC_SEL_UNION;
#endif
#define SOC_ASP_CFG_R_DMAC_SEL_write_en_START  (16)
#define SOC_ASP_CFG_R_DMAC_SEL_write_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_BUS_PRIORITY_UNION
 �ṹ˵��  : R_BUS_PRIORITY �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x853E4000�����:32
 �Ĵ���˵��: �������ȼ����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsp_ar_qos       : 2;  /* bit[0-1]  : dsp��axi master��arͨ����qos�źţ� */
        unsigned int  dsp_aw_qos       : 2;  /* bit[2-3]  : dsp��axi master��awͨ����qos�źţ� */
        unsigned int  dma_ar_qos       : 2;  /* bit[4-5]  : asp dmac��axi master��arͨ����qos�źţ� */
        unsigned int  dma_aw_qos       : 2;  /* bit[6-7]  : asp dmac��axi master��awͨ����qos�źţ� */
        unsigned int  ahb2axi_ar_qos   : 2;  /* bit[8-9]  : ��ǿ��axi master��arͨ����qos�źţ� */
        unsigned int  ahb2axi_aw_qos   : 2;  /* bit[10-11]: ��ǿ��axi master��awͨ����qos�źţ� */
        unsigned int  asp_slv_priority : 2;  /* bit[12-13]: NOC����asp�Ķ˿���dw_axi�����ϵ����ȼ��źţ�
                                                            ֵԽ�������ȼ�Խ�ߣ� */
        unsigned int  dsp_mst_priority : 2;  /* bit[14-15]: dsp��master����dw_axi�����ϵ����ȼ��źţ�
                                                            ֵԽ�������ȼ�Խ�ߣ� */
        unsigned int  dmac_priority    : 2;  /* bit[16-17]: dmac��master����dw_axi�����ϵ����ȼ��źţ�
                                                            ֵԽ�������ȼ�Խ�ߣ� */
        unsigned int  ahb2axi_priority : 2;  /* bit[18-19]: ��ǿ�ŵ�master����dw_axi�����ϵ����ȼ��źţ�
                                                            ֵԽ�������ȼ�Խ�ߣ� */
        unsigned int  asp_mst_priority : 3;  /* bit[20-22]: asp����NOC�Ķ˿���dw_axi�����ϵ����ȼ��źţ�
                                                            ֵԽ�������ȼ�Խ�ߣ� */
        unsigned int  dsp_slv_priority : 3;  /* bit[23-25]: dsp��slave����dw_axi�����ϵ����ȼ��źţ�
                                                            ֵԽ�������ȼ�Խ�ߣ� */
        unsigned int  ocram_priority   : 3;  /* bit[26-28]: ocram��slave����dw_axi�����ϵ����ȼ��źţ�
                                                            ֵԽ�������ȼ�Խ�ߣ� */
        unsigned int  x2h_priority     : 3;  /* bit[29-31]: x2h�ŵ�slave����dw_axi�����ϵ����ȼ��źţ�
                                                            ֵԽ�������ȼ�Խ�ߣ� */
    } reg;
} SOC_ASP_CFG_R_BUS_PRIORITY_UNION;
#endif
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_ar_qos_START        (0)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_ar_qos_END          (1)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_aw_qos_START        (2)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_aw_qos_END          (3)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dma_ar_qos_START        (4)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dma_ar_qos_END          (5)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dma_aw_qos_START        (6)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dma_aw_qos_END          (7)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ahb2axi_ar_qos_START    (8)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ahb2axi_ar_qos_END      (9)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ahb2axi_aw_qos_START    (10)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ahb2axi_aw_qos_END      (11)
#define SOC_ASP_CFG_R_BUS_PRIORITY_asp_slv_priority_START  (12)
#define SOC_ASP_CFG_R_BUS_PRIORITY_asp_slv_priority_END    (13)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_mst_priority_START  (14)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_mst_priority_END    (15)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dmac_priority_START     (16)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dmac_priority_END       (17)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ahb2axi_priority_START  (18)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ahb2axi_priority_END    (19)
#define SOC_ASP_CFG_R_BUS_PRIORITY_asp_mst_priority_START  (20)
#define SOC_ASP_CFG_R_BUS_PRIORITY_asp_mst_priority_END    (22)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_slv_priority_START  (23)
#define SOC_ASP_CFG_R_BUS_PRIORITY_dsp_slv_priority_END    (25)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ocram_priority_START    (26)
#define SOC_ASP_CFG_R_BUS_PRIORITY_ocram_priority_END      (28)
#define SOC_ASP_CFG_R_BUS_PRIORITY_x2h_priority_START      (29)
#define SOC_ASP_CFG_R_BUS_PRIORITY_x2h_priority_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_CG_EN_UNION
 �ṹ˵��  : R_CG_EN �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Զ��ſ�ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dw_axi_m1_cg_en  : 1;  /* bit[0]    : dw_axi master1�ڣ�NOC����asp�Ķ˿ڣ����Զ��ſ�ʹ�ܣ�
                                                            0���Զ��ſز�ʹ�ܣ�
                                                            1���Զ��ſ�ʹ�ܡ� */
        unsigned int  dw_axi_m2_cg_en  : 1;  /* bit[1]    : dw_axi master2�ڣ��Խ�dsp master�ڣ����Զ��ſ�ʹ�ܣ�
                                                            0���Զ��ſز�ʹ�ܣ�
                                                            1���Զ��ſ�ʹ�ܡ� */
        unsigned int  dw_axi_m3_cg_en  : 1;  /* bit[2]    : dw_axi master3�ڣ��Խ�asp dmac master�ڣ����Զ��ſ�ʹ�ܣ�
                                                            0���Զ��ſز�ʹ�ܣ�
                                                            1���Զ��ſ�ʹ�ܡ� */
        unsigned int  dw_axi_m4_cg_en  : 1;  /* bit[3]    : dw_axi master4�ڣ��ԽӸ�ǿ��master�ڣ����Զ��ſ�ʹ�ܣ�
                                                            0���Զ��ſز�ʹ�ܣ�
                                                            1���Զ��ſ�ʹ�ܡ� */
        unsigned int  dw_axi_s1_cg_en  : 1;  /* bit[4]    : dw_axi slave1�ڣ�asp����NOC�Ķ˿ڣ����Զ��ſ�ʹ�ܣ�
                                                            0���Զ��ſز�ʹ�ܣ�
                                                            1���Զ��ſ�ʹ�ܡ� */
        unsigned int  dw_axi_s2_cg_en  : 1;  /* bit[5]    : dw_axi slave2�ڣ��Խ�dsp slave�ڣ����Զ��ſ�ʹ�ܣ�
                                                            0���Զ��ſز�ʹ�ܣ�
                                                            1���Զ��ſ�ʹ�ܡ� */
        unsigned int  dw_axi_s3_cg_en  : 1;  /* bit[6]    : dw_axi slave3�ڣ��Խ�ocram slave�ڣ����Զ��ſ�ʹ�ܣ�
                                                            0���Զ��ſز�ʹ�ܣ�
                                                            1���Զ��ſ�ʹ�ܡ� */
        unsigned int  dw_axi_s4_cg_en  : 1;  /* bit[7]    : dw_axi slave4�ڣ��Խ�x2h��slave�ڣ����Զ��ſ�ʹ�ܣ�
                                                            0���Զ��ſز�ʹ�ܣ�
                                                            1���Զ��ſ�ʹ�ܡ� */
        unsigned int  dw_axi_s0_cg_en  : 1;  /* bit[8]    : dw_axi slave0�ڵ��Զ��ſ�ʹ�ܣ�
                                                            0���Զ��ſز�ʹ�ܣ�
                                                            1���Զ��ſ�ʹ�ܡ� */
        unsigned int  reserved_0       : 1;  /* bit[9]    : ������ */
        unsigned int  dmac_hclk0_cg_en : 1;  /* bit[10]   : dmac hclk0ģ���Զ��ſ�ʹ�ܣ�
                                                            0���Զ��ſز�ʹ�ܣ�
                                                            1���Զ��ſ�ʹ�ܡ� */
        unsigned int  dmac_hclk1_cg_en : 1;  /* bit[11]   : dmac hclk1ģ���Զ��ſ�ʹ�ܣ�
                                                            0���Զ��ſز�ʹ�ܣ�
                                                            1���Զ��ſ�ʹ�ܡ� */
        unsigned int  reserved_1       : 1;  /* bit[12]   :  */
        unsigned int  reserved_2       : 3;  /* bit[13-15]:  */
        unsigned int  write_en         : 16; /* bit[16-31]: R_CG_ENÿ������λ��дʹ��λ��
                                                            ֻ�е�write_en��Ӧ�ı���λΪ1'b1����R_CG_EN��Ӧ�ı���λ��д�����������á�write_en[0]����R_CG_EN[0]��дʹ��λ��д1��Ч�� */
    } reg;
} SOC_ASP_CFG_R_CG_EN_UNION;
#endif
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m1_cg_en_START   (0)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m1_cg_en_END     (0)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m2_cg_en_START   (1)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m2_cg_en_END     (1)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m3_cg_en_START   (2)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m3_cg_en_END     (2)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m4_cg_en_START   (3)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_m4_cg_en_END     (3)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s1_cg_en_START   (4)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s1_cg_en_END     (4)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s2_cg_en_START   (5)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s2_cg_en_END     (5)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s3_cg_en_START   (6)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s3_cg_en_END     (6)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s4_cg_en_START   (7)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s4_cg_en_END     (7)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s0_cg_en_START   (8)
#define SOC_ASP_CFG_R_CG_EN_dw_axi_s0_cg_en_END     (8)
#define SOC_ASP_CFG_R_CG_EN_dmac_hclk0_cg_en_START  (10)
#define SOC_ASP_CFG_R_CG_EN_dmac_hclk0_cg_en_END    (10)
#define SOC_ASP_CFG_R_CG_EN_dmac_hclk1_cg_en_START  (11)
#define SOC_ASP_CFG_R_CG_EN_dmac_hclk1_cg_en_END    (11)
#define SOC_ASP_CFG_R_CG_EN_write_en_START          (16)
#define SOC_ASP_CFG_R_CG_EN_write_en_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_OCRAM_RET_UNION
 �ṹ˵��  : R_OCRAM_RET �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: ocram�͹������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slp      : 3;  /* bit[0-2]  : OCRAMÿƬRAMͨ��3���źţ�SD��DSLP��SLP�������书��ģʽ��
                                                    Ĭ��ΪNormal Mode(SD=0��DSLP=0��SLP=0)
                                                    ���ĳƬRAM�ڲ���Ҫʹ�õ�ʱ�򣬿���ͨ��������ð���ģʽ�л�ʱ�����Power Downģʽ(SD=1��DSLP=0��SLP=0)���Խ�ʡ���ġ�
                                                    
                                                    SLP: OCRAM Power Gating�����ź�SLP��
                                                    bit[2]������OCRAM Ƭѡ2��128KB-192KB����SLP��Ĭ��Ϊ1'b0
                                                    bit[1]������OCRAM Ƭѡ1��64KB-128KB����SLP��Ĭ��Ϊ1'b0
                                                    bit[0]������OCRAM Ƭѡ0��0-64KB����SLP��Ĭ��Ϊ1'b0 */
        unsigned int  reserved_0: 1;  /* bit[3]    : ������ */
        unsigned int  dslp     : 3;  /* bit[4-6]  : OCRAMÿƬRAMͨ��3���źţ�SD��DSLP��SLP�������书��ģʽ��
                                                    Ĭ��ΪNormal Mode(SD=0��DSLP=0��SLP=0)
                                                    ���ĳƬRAM�ڲ���Ҫʹ�õ�ʱ�򣬿���ͨ��������ð���ģʽ�л�ʱ�����Power Downģʽ(SD=1��DSLP=0��SLP=0)���Խ�ʡ���ġ�
                                                    
                                                    DSLP: OCRAM Power Gating�����ź�DSLP��
                                                    bit[2]������OCRAM Ƭѡ2��128KB-192KB����DSLP��Ĭ��Ϊ1'b0
                                                    bit[1]������OCRAM Ƭѡ1��64KB-128KB����DSLP��Ĭ��Ϊ1'b0
                                                    bit[0]������OCRAM Ƭѡ0��0-64KB����DSLP��Ĭ��Ϊ1'b0 */
        unsigned int  reserved_1: 1;  /* bit[7]    : ������ */
        unsigned int  sd       : 3;  /* bit[8-10] : OCRAMÿƬRAMͨ��3���źţ�SD��DSLP��SLP�������书��ģʽ��
                                                    Ĭ��ΪNormal Mode(SD=0��DSLP=0��SLP=0)
                                                    ���ĳƬRAM�ڲ���Ҫʹ�õ�ʱ�򣬿���ͨ��������ð���ģʽ�л�ʱ�����Power Downģʽ(SD=1��DSLP=0��SLP=0)���Խ�ʡ���ġ�
                                                    
                                                    SD: OCRAM Power Gating�����ź�SD��
                                                    bit[2]������OCRAM Ƭѡ2��128KB-192KB����SD��Ĭ��Ϊ1'b0
                                                    bit[1]������OCRAM Ƭѡ1��64KB-128KB����SD��Ĭ��Ϊ1'b0
                                                    bit[0]������OCRAM Ƭѡ0��0-64KB����SD��Ĭ��Ϊ1'b0 */
        unsigned int  reserved_2: 1;  /* bit[11]   : ������ */
        unsigned int  reserved_3: 4;  /* bit[12-15]: ������ */
        unsigned int  write_en : 16; /* bit[16-31]: R_OCRAM_RETÿ������λ��дʹ��λ��
                                                    ֻ�е�write_en��Ӧ�ı���λΪ1'b1����R_OCRAM_RET��Ӧ�ı���λ��д�����������á�write_en[0]����R_OCRAM_RET[0]��дʹ��λ��д1��Ч�� */
    } reg;
} SOC_ASP_CFG_R_OCRAM_RET_UNION;
#endif
#define SOC_ASP_CFG_R_OCRAM_RET_slp_START       (0)
#define SOC_ASP_CFG_R_OCRAM_RET_slp_END         (2)
#define SOC_ASP_CFG_R_OCRAM_RET_dslp_START      (4)
#define SOC_ASP_CFG_R_OCRAM_RET_dslp_END        (6)
#define SOC_ASP_CFG_R_OCRAM_RET_sd_START        (8)
#define SOC_ASP_CFG_R_OCRAM_RET_sd_END          (10)
#define SOC_ASP_CFG_R_OCRAM_RET_write_en_START  (16)
#define SOC_ASP_CFG_R_OCRAM_RET_write_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_INTR_NS_INI_UNION
 �ṹ˵��  : R_INTR_NS_INI �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ǰ�ȫ�ж�ԭʼ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_hdmi_int : 1;  /* bit[0]   : asp_hdmiԭʼ�ǰ�ȫ�жϡ�
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  reserved_0   : 1;  /* bit[1]   :  */
        unsigned int  reserved_1   : 1;  /* bit[2]   :  */
        unsigned int  slimbus_intr : 1;  /* bit[3]   : slimbusԭʼ�ǰ�ȫ�жϡ�
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  reserved_2   : 28; /* bit[4-31]:  */
    } reg;
} SOC_ASP_CFG_R_INTR_NS_INI_UNION;
#endif
#define SOC_ASP_CFG_R_INTR_NS_INI_asp_hdmi_int_START  (0)
#define SOC_ASP_CFG_R_INTR_NS_INI_asp_hdmi_int_END    (0)
#define SOC_ASP_CFG_R_INTR_NS_INI_slimbus_intr_START  (3)
#define SOC_ASP_CFG_R_INTR_NS_INI_slimbus_intr_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_INTR_NS_EN_UNION
 �ṹ˵��  : R_INTR_NS_EN �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ǰ�ȫ�ж�ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_hdmi_int_en : 1;  /* bit[0]   : asp_hdmi�ǰ�ȫ�ж�ʹ�ܡ�
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  reserved_0      : 1;  /* bit[1]   :  */
        unsigned int  reserved_1      : 1;  /* bit[2]   :  */
        unsigned int  slimbus_intr_en : 1;  /* bit[3]   : slimbus�ǰ�ȫ�ж�ʹ�ܡ�
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  reserved_2      : 28; /* bit[4-31]:  */
    } reg;
} SOC_ASP_CFG_R_INTR_NS_EN_UNION;
#endif
#define SOC_ASP_CFG_R_INTR_NS_EN_asp_hdmi_int_en_START  (0)
#define SOC_ASP_CFG_R_INTR_NS_EN_asp_hdmi_int_en_END    (0)
#define SOC_ASP_CFG_R_INTR_NS_EN_slimbus_intr_en_START  (3)
#define SOC_ASP_CFG_R_INTR_NS_EN_slimbus_intr_en_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_INTR_NS_MASK_UNION
 �ṹ˵��  : R_INTR_NS_MASK �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ǰ�ȫ�ж����κ�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_hdmi_int_mask : 1;  /* bit[0]   : asp_hdmi���κ�ǰ�ȫ�жϡ�
                                                            0�����жϣ�
                                                            1�����жϡ� */
        unsigned int  reserved_0        : 1;  /* bit[1]   :  */
        unsigned int  reserved_1        : 1;  /* bit[2]   :  */
        unsigned int  slimbus_intr_mask : 1;  /* bit[3]   : slimbus���κ�ǰ�ȫ�жϡ�
                                                            0�����жϣ�
                                                            1�����жϡ� */
        unsigned int  reserved_2        : 28; /* bit[4-31]:  */
    } reg;
} SOC_ASP_CFG_R_INTR_NS_MASK_UNION;
#endif
#define SOC_ASP_CFG_R_INTR_NS_MASK_asp_hdmi_int_mask_START  (0)
#define SOC_ASP_CFG_R_INTR_NS_MASK_asp_hdmi_int_mask_END    (0)
#define SOC_ASP_CFG_R_INTR_NS_MASK_slimbus_intr_mask_START  (3)
#define SOC_ASP_CFG_R_INTR_NS_MASK_slimbus_intr_mask_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DBG_SET_AHB2AXI_UNION
 �ṹ˵��  : R_DBG_SET_AHB2AXI �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x01011111�����:32
 �Ĵ���˵��: ��ǿ��DBG�ź����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_wfq_weight_port2 : 4;  /* bit[0-3]  :  */
        unsigned int  dbg_wfq_weight_port1 : 4;  /* bit[4-7]  :  */
        unsigned int  dbg_wfq_weight_port0 : 4;  /* bit[8-11] : �˿ڵ��Ȳ��õ���WFQ�㷨��dbg_wfq_weight_port0~dbg_wfq_weight_port2�ź���������3��AHB�˿ڵ�Ȩ�أ���������ֵ��
                                                                a���������˿ڵ�Ȩ��ֵȫΪ0x0�������SP�㷨�����ϸ����ȼ����ȣ�0�˿����ȼ���ߣ�һ��3�˿����ȼ���ͣ�
                                                                b���������˿ڵ�Ȩ��ֵ����Ҳ�Ϊ0�������RR�㷨���˿���ѯ���ȣ�
                                                                c���������˿ڵ�Ȩ��ֵ���ȣ���Ȩ��ֵ��С�����ȼ���� */
        unsigned int  dbg_rd_outstd        : 4;  /* bit[12-15]: �������ö�������outstanding��ȣ�֧�ֶ�̬����  */
        unsigned int  dbg_wr_outstd        : 4;  /* bit[16-19]: ��������д������outstanding��ȣ�֧�ֶ�̬����  */
        unsigned int  dbg_port_sel         : 4;  /* bit[20-23]: h2x�˿�״̬ѡ������ѡ��dbg_status�ӿ�����ĸ��˿ڵ�ֵ��dbg_port_sel=x�������x�˿ڵ�״ֵ̬�� */
        unsigned int  dbg_incr_spen        : 1;  /* bit[24]   : INCR������ʹ�ܣ�����Чʱ����ʹ�ܽ�AHB�˿ڵ�INCR����burst���ΪAXI�˿ڵ�INCR����burst������ߴ�����֮�������֡� */
        unsigned int  dbg_h2x_sel          : 1;  /* bit[25]   : h2x״̬Ƭѡ */
        unsigned int  dbg_stat_clr         : 1;  /* bit[26]   : debug״̬���ʹ�� */
        unsigned int  reserved             : 5;  /* bit[27-31]:  */
    } reg;
} SOC_ASP_CFG_R_DBG_SET_AHB2AXI_UNION;
#endif
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wfq_weight_port2_START  (0)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wfq_weight_port2_END    (3)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wfq_weight_port1_START  (4)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wfq_weight_port1_END    (7)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wfq_weight_port0_START  (8)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wfq_weight_port0_END    (11)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_rd_outstd_START         (12)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_rd_outstd_END           (15)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wr_outstd_START         (16)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_wr_outstd_END           (19)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_port_sel_START          (20)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_port_sel_END            (23)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_incr_spen_START         (24)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_incr_spen_END           (24)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_h2x_sel_START           (25)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_h2x_sel_END             (25)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_stat_clr_START          (26)
#define SOC_ASP_CFG_R_DBG_SET_AHB2AXI_dbg_stat_clr_END            (26)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_UNION
 �ṹ˵��  : R_DBG_STATUS_AHB2AXI �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ǿ��DBG�ź�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rlast_bresp_err : 1;  /* bit[0]    : AXI���߶����ݻ���rlast�������
                                                           0��û�з��Ͷ����ݴ������
                                                           1��AHB�ӿ�û�з��Ͷ������״̬�£����յ������߷��صĶ����ݣ�bresp����AHBû�з���д�����״̬�£����յ������߷��ص�rlast�źţ�
                                                           ��port_sel8ʱ��Ϊ��ʾд�������ݳ�ʱ״̬��Ŀǰ����Ϊ16'hffffΪ��ʱʱ��
                                                           0��û�з�������ʱ��
                                                           1�������˳�ʱ��
                                                           ��״̬���Ա�stat_clr��� */
        unsigned int  rdata_err       : 1;  /* bit[1]    : AXI���߶����ݻ���bresp�������
                                                           0��û�з��Ͷ����ݴ������
                                                           1��AHB�ӿ�û�з��Ͷ������״̬�£����յ������߷��صĶ����ݣ�bresp����AHBû�з���д�����״̬�£����յ������߷��ص�bresp�źţ�
                                                           ��port_sel8ʱ��Ϊ��ʾд�������ݳ�ʱ״̬��Ŀǰ����Ϊ16'hffffΪ��ʱʱ��
                                                           0��û�з�������ʱ��
                                                           1�������˳�ʱ��
                                                           ��״̬���Ա�stat_clr��� */
        unsigned int  rdcmd_gnt       : 1;  /* bit[2]    : AHB��������״̬
                                                           0��û�л��AXI���ߣ�
                                                           1�����AXI���ߣ����Է�������
                                                           ��port_selΪ8ʱ����ʾд�������ʱ״̬��Ŀǰ����Ϊ16'hffffΪ��ʱʱ��
                                                           0��û�з��ͳ�ʱ��
                                                           1�������˳�ʱ��
                                                           ��״̬�����Ա�stat_clr��� */
        unsigned int  rdcmd_rearb     : 1;  /* bit[3]    : AHB�ڲ����������ٲ�ʹ��
                                                           0�������������ٲã�
                                                           1�����������ٲã�
                                                           ��״̬�����Ա�stat_clr��� */
        unsigned int  wrcmd_nt        : 1;  /* bit[4]    : AHB��������״̬
                                                           0��û�л��AXI���ߣ�
                                                           1�����AXI���ߣ����Է�������
                                                           ��״̬�����Ա�stat_clr��� */
        unsigned int  wrcmd_rearb     : 1;  /* bit[5]    : AHB�ڲ����������ٲ�ʹ��
                                                           0�������������ٲã�
                                                           1�����������ٲã�
                                                           ��״̬�����Ա�stat_clr��� */
        unsigned int  cmd_arrdy       : 1;  /* bit[6]    : AHB�ڲ��ӿ�״̬
                                                           0��cmdbufģ���ж��������ڴ���
                                                           1��cmdbufģ�鴦��IDLE״̬��
                                                           ��״̬�����Ա�stat_clr��� */
        unsigned int  cmd_awrdy       : 1;  /* bit[7]    : AHB�ڲ��ӿ�״̬
                                                           0��cmdbufģ����д�������ڴ���
                                                           1��cmdbufģ�鴦��IDLE״̬��
                                                           ��״̬�����Ա�stat_clr��� */
        unsigned int  rdfifo_full     : 1;  /* bit[8]    : AHB�ӿ�rdfifo��״̬
                                                           0��rdfifo������
                                                           1��rdfifo����
                                                           ��״̬�����Ա�stat_clr��� */
        unsigned int  rdfifo_empty    : 1;  /* bit[9]    : AHB�ӿ�rdfifo��״̬
                                                           0��wrfifo�ǿգ�
                                                           1��wrfifo�գ��޻������ݡ�
                                                           ��״̬�����Ա�stat_clr��� */
        unsigned int  wrfifo_alfull   : 1;  /* bit[10]   : AHB�ӿ�wrfifo����״̬
                                                           0��wrfifo�ǽ�����
                                                           1��wrfifo�ﵽ����״̬��
                                                           ��״̬�����Ա�stat_clr��� */
        unsigned int  wrfifo_empty    : 1;  /* bit[11]   : AHB�ӿ�wrfifo��״̬
                                                           0��wrfifo�ǿգ�
                                                           1��wrfifo�գ��޻������ݣ�
                                                           ��״̬�����Ա�stat_clr��� */
        unsigned int  rdfifo_rerr     : 1;  /* bit[12]   : AHB�ӿ�rdfifo�Ķ�����ָʾ
                                                           0����ʾû�з���������
                                                           1����ʾ������rdfifo�յ�����£���rdfifoд�ĳ���
                                                           ��״̬���Ա�stat_clr��� */
        unsigned int  rdfifo_werr     : 1;  /* bit[13]   : AHB�ӿ�rdfifo��д����ָʾ
                                                           0����ʾû�з���д����
                                                           1����ʾ������rdfifo��������£���rdfifoд�ĳ���
                                                           ��״̬���Ա�stat_clr��� */
        unsigned int  wrfifo_rerr     : 1;  /* bit[14]   : AHB�ӿ�wrfifo�Ķ�����ָʾ
                                                           0����ʾû�з���������
                                                           1����ʾ������rdfifo��������£���rdfifoд�ĳ���
                                                           ��״̬���Ա�stat_clr��� */
        unsigned int  wrfifo_werr     : 1;  /* bit[15]   : AHB�ӿ�wrfifo��д����ָʾ
                                                           0������û�з���д����
                                                           1����ʾ������wrfifo��������£���wrfifoд�ĳ�����
                                                           ��״̬���Ա�stat_clr��� */
        unsigned int  rdcmd_cnt       : 4;  /* bit[16-19]: AHB�ӿڷ��Ͷ������Ӧ�Ķ����ݸ���
                                                           0x0~0xf:����n������������״̬���ܱ�stat_clr��� */
        unsigned int  rddata_cnt      : 4;  /* bit[20-23]: AHB�ӿڶ����ݸ���
                                                           0x0~0xf:����n�������ݣ���״̬���ܱ�stat_clr��� */
        unsigned int  wrcmd_cnt       : 4;  /* bit[24-27]: AHB�ӿڷ��͵�д�����Ӧ��д���ݸ���
                                                           0x0~0xf:����n������������״̬���ܱ�stat_clr��� */
        unsigned int  wrdata_cnt      : 4;  /* bit[28-31]: AHB�ӿ�д���ݸ���������
                                                           0x0~0xf:��ʾn���������ݡ�
                                                           ��״̬���ܱ�stat_clr��� */
    } reg;
} SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_UNION;
#endif
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rlast_bresp_err_START  (0)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rlast_bresp_err_END    (0)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdata_err_START        (1)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdata_err_END          (1)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdcmd_gnt_START        (2)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdcmd_gnt_END          (2)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdcmd_rearb_START      (3)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdcmd_rearb_END        (3)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrcmd_nt_START         (4)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrcmd_nt_END           (4)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrcmd_rearb_START      (5)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrcmd_rearb_END        (5)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_cmd_arrdy_START        (6)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_cmd_arrdy_END          (6)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_cmd_awrdy_START        (7)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_cmd_awrdy_END          (7)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_full_START      (8)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_full_END        (8)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_empty_START     (9)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_empty_END       (9)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_alfull_START    (10)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_alfull_END      (10)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_empty_START     (11)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_empty_END       (11)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_rerr_START      (12)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_rerr_END        (12)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_werr_START      (13)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdfifo_werr_END        (13)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_rerr_START      (14)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_rerr_END        (14)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_werr_START      (15)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrfifo_werr_END        (15)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdcmd_cnt_START        (16)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rdcmd_cnt_END          (19)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rddata_cnt_START       (20)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_rddata_cnt_END         (23)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrcmd_cnt_START        (24)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrcmd_cnt_END          (27)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrdata_cnt_START       (28)
#define SOC_ASP_CFG_R_DBG_STATUS_AHB2AXI_wrdata_cnt_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DLOCK_BP_UNION
 �ṹ˵��  : R_DLOCK_BP �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���߷�����bypass�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 1;  /* bit[0]    :  */
        unsigned int  reserved_1        : 1;  /* bit[1]    :  */
        unsigned int  dlock_bp_h2p      : 1;  /* bit[2]    : h2p�ŷ�����bypass�Ĵ�����
                                                             0��������������Ч��
                                                             1�����������ܱ�bypass�� */
        unsigned int  dlock_bp_asphdmi  : 1;  /* bit[3]    : asp_hdmiģ�������bypass�Ĵ�����
                                                             0��������������Ч��
                                                             1�����������ܱ�bypass�� */
        unsigned int  dlock_bp_sioaudio : 1;  /* bit[4]    : sioaudioģ�������bypass�Ĵ�����
                                                             0��������������Ч��
                                                             1�����������ܱ�bypass�� */
        unsigned int  dlock_bp_siovoice : 1;  /* bit[5]    : siovoiceģ�������bypass�Ĵ�����
                                                             0��������������Ч��
                                                             1�����������ܱ�bypass�� */
        unsigned int  dlock_bp_siobt    : 1;  /* bit[6]    : siobtģ�������bypass�Ĵ�����
                                                             0��������������Ч��
                                                             1�����������ܱ�bypass�� */
        unsigned int  dlock_bp_siomodem : 1;  /* bit[7]    : siomodemģ�������bypass�Ĵ�����
                                                             0��������������Ч��
                                                             1�����������ܱ�bypass�� */
        unsigned int  dlock_bp_slimbus  : 1;  /* bit[8]    : slimbusģ�������bypass�Ĵ�����
                                                             0��������������Ч��
                                                             1�����������ܱ�bypass�� */
        unsigned int  dlock_bp_edmac    : 1;  /* bit[9]    : asp dmacģ�������bypass�Ĵ�����
                                                             0��������������Ч��
                                                             1�����������ܱ�bypass�� */
        unsigned int  dlock_bp_ipc      : 1;  /* bit[10]   : asp ipcģ�������bypass�Ĵ�����
                                                             0��������������Ч��
                                                             1�����������ܱ�bypass�� */
        unsigned int  dlock_bp_watchdog : 1;  /* bit[11]   : watchdogģ�������bypass�Ĵ�����
                                                             0��������������Ч��
                                                             1�����������ܱ�bypass�� */
        unsigned int  dlock_bp_cfg      : 1;  /* bit[12]   : asp_cfgģ�������bypass�Ĵ�����
                                                             0��������������Ч��
                                                             1�����������ܱ�bypass�� */
        unsigned int  dlock_bp_gpio     : 1;  /* bit[13]   : gpioģ�������bypass�Ĵ�����
                                                             0��������������Ч��
                                                             1�����������ܱ�bypass�� */
        unsigned int  dlock_bp_timer0   : 1;  /* bit[14]   : timer0ģ�������bypass�Ĵ�����
                                                             0��������������Ч��
                                                             1�����������ܱ�bypass�� */
        unsigned int  dlock_bp_timer1   : 1;  /* bit[15]   : timer1ģ�������bypass�Ĵ�����
                                                             0��������������Ч��
                                                             1�����������ܱ�bypass�� */
        unsigned int  write_en          : 16; /* bit[16-31]: R_DLOCK_BPÿ������λ��дʹ��λ��
                                                             ֻ�е�write_en��Ӧ�ı���λΪ1'b1����R_DLOCK_BP��Ӧ�ı���λ��д�����������á�write_en[0]����R_DLOCK_BP[0]��дʹ��λ��д1��Ч�� */
    } reg;
} SOC_ASP_CFG_R_DLOCK_BP_UNION;
#endif
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_h2p_START       (2)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_h2p_END         (2)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_asphdmi_START   (3)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_asphdmi_END     (3)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_sioaudio_START  (4)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_sioaudio_END    (4)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_siovoice_START  (5)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_siovoice_END    (5)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_siobt_START     (6)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_siobt_END       (6)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_siomodem_START  (7)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_siomodem_END    (7)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_slimbus_START   (8)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_slimbus_END     (8)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_edmac_START     (9)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_edmac_END       (9)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_ipc_START       (10)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_ipc_END         (10)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_watchdog_START  (11)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_watchdog_END    (11)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_cfg_START       (12)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_cfg_END         (12)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_gpio_START      (13)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_gpio_END        (13)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_timer0_START    (14)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_timer0_END      (14)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_timer1_START    (15)
#define SOC_ASP_CFG_R_DLOCK_BP_dlock_bp_timer1_END      (15)
#define SOC_ASP_CFG_R_DLOCK_BP_write_en_START           (16)
#define SOC_ASP_CFG_R_DLOCK_BP_write_en_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DSP_BINTERRUPT_UNION
 �ṹ˵��  : R_DSP_BINTERRUPT �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ϱ���hifi dsp���ж��ź�ֻ���Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_dsp_nmi          : 1;  /* bit[0]    : dsp nmi�ж� */
        unsigned int  intr0_nonsecure_ipc   : 1;  /* bit[1]    : ϵͳ�ǰ�ȫIPC��hifi��IPC_NS_int4�ж� */
        unsigned int  intr1_nonsecure_ipc   : 1;  /* bit[2]    : ϵͳ�ǰ�ȫIPC��hifi��IPC_NS_mbx18�ж� */
        unsigned int  intr0_secure_ipc      : 1;  /* bit[3]    : ϵͳ��ȫIPC��hifi��IPC_S_int4�ж� */
        unsigned int  intr1_secure_ipc      : 1;  /* bit[4]    : ϵͳ��ȫIPC��hifi��IPC_S_mbx18�ж� */
        unsigned int  intr_asp_timer0_0     : 1;  /* bit[5]    : asp timer0ģ���hifi�ĵ�0���ж� */
        unsigned int  intr_asp_timer0_1     : 1;  /* bit[6]    : asp timer0ģ���hifi�ĵ�1���ж� */
        unsigned int  intr_asp_timer1_0     : 1;  /* bit[7]    : asp timer1ģ���hifi�ĵ�0���ж� */
        unsigned int  intr_asp_timer1_1     : 1;  /* bit[8]    : asp timer1ģ���hifi�ĵ�1���ж� */
        unsigned int  intr_sio_audio        : 1;  /* bit[9]    : sio_audioģ���hifi���ж� */
        unsigned int  intr_sio_voice        : 1;  /* bit[10]   : sio_voiceģ���hifi���ж� */
        unsigned int  intr_sio_bt           : 1;  /* bit[11]   : sio_btģ���hifi���ж� */
        unsigned int  intr_sio_modem        : 1;  /* bit[12]   : sio_modemģ���hifi���ж� */
        unsigned int  asp_hdmi_int          : 1;  /* bit[13]   : asp_hdmiģ���hifi���жϣ�����˰�ȫ��ǰ�ȫ�ж� */
        unsigned int  dma_intr              : 1;  /* bit[14]   : asp dmacģ���hifi�İ�ȫ�ж� */
        unsigned int  dma_intr_ns           : 1;  /* bit[15]   : asp dmacģ���hifi�ķǰ�ȫ�ж� */
        unsigned int  ldrx2hifi_time_int    : 1;  /* bit[16]   : ldrx2hifi�Ķ�ʱ�ж� */
        unsigned int  intr_addr_monitor     : 1;  /* bit[17]   : �ڴ汣��ģ���ϱ���hifi���ж� */
        unsigned int  intr_watch_dog        : 1;  /* bit[18]   : asp watch dogģ���hifi���ж� */
        unsigned int  ipc_int               : 1;  /* bit[19]   : asp ipcģ���hifi���ж� */
        unsigned int  slimbus_intr          : 1;  /* bit[20]   : slimbusģ���hifi���ж� */
        unsigned int  mcpu_hifi_intr        : 1;  /* bit[21]   : modem cpuģ���hifi���ж� */
        unsigned int  bbe16_hifi_intr       : 1;  /* bit[22]   : bbe16ģ���hifi���ж� */
        unsigned int  i2c_hifi_intr         : 1;  /* bit[23]   : i2c4ģ���hifi���ж� */
        unsigned int  intr_gpio_hifi        : 1;  /* bit[24]   : asp gpioģ���hifi���ж� */
        unsigned int  tds_hifi_intr         : 1;  /* bit[25]   : tdscdmaģ���hifi���ж� */
        unsigned int  intr_freq_offset      : 1;  /* bit[26]   : Ƶƫ��¼ģ���hifi���ж� */
        unsigned int  freq_offset_intr_flag : 1;  /* bit[27]   : Ƶƫ��¼ģ���hifi���ж�ָʾ�ź�
                                                                 1'b1����ʾSoc��- modem��>=��ֵ����ʾ���мӵ㡢���м��㣩
                                                                 1'b0����ʾmodem��-Soc��>=��ֵ����ʾ���мӵ㡢���м��㣩 */
        unsigned int  reserved              : 4;  /* bit[28-31]:  */
    } reg;
} SOC_ASP_CFG_R_DSP_BINTERRUPT_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_dsp_nmi_START           (0)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_dsp_nmi_END             (0)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr0_nonsecure_ipc_START    (1)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr0_nonsecure_ipc_END      (1)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr1_nonsecure_ipc_START    (2)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr1_nonsecure_ipc_END      (2)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr0_secure_ipc_START       (3)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr0_secure_ipc_END         (3)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr1_secure_ipc_START       (4)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr1_secure_ipc_END         (4)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer0_0_START      (5)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer0_0_END        (5)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer0_1_START      (6)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer0_1_END        (6)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer1_0_START      (7)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer1_0_END        (7)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer1_1_START      (8)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_asp_timer1_1_END        (8)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_audio_START         (9)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_audio_END           (9)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_voice_START         (10)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_voice_END           (10)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_bt_START            (11)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_bt_END              (11)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_modem_START         (12)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_sio_modem_END           (12)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_asp_hdmi_int_START           (13)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_asp_hdmi_int_END             (13)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_dma_intr_START               (14)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_dma_intr_END                 (14)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_dma_intr_ns_START            (15)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_dma_intr_ns_END              (15)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_ldrx2hifi_time_int_START     (16)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_ldrx2hifi_time_int_END       (16)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_addr_monitor_START      (17)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_addr_monitor_END        (17)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_watch_dog_START         (18)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_watch_dog_END           (18)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_ipc_int_START                (19)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_ipc_int_END                  (19)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_slimbus_intr_START           (20)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_slimbus_intr_END             (20)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_mcpu_hifi_intr_START         (21)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_mcpu_hifi_intr_END           (21)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_bbe16_hifi_intr_START        (22)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_bbe16_hifi_intr_END          (22)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_i2c_hifi_intr_START          (23)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_i2c_hifi_intr_END            (23)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_gpio_hifi_START         (24)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_gpio_hifi_END           (24)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_tds_hifi_intr_START          (25)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_tds_hifi_intr_END            (25)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_freq_offset_START       (26)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_intr_freq_offset_END         (26)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_freq_offset_intr_flag_START  (27)
#define SOC_ASP_CFG_R_DSP_BINTERRUPT_freq_offset_intr_flag_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DSP_RAM_RET_UNION
 �ṹ˵��  : R_DSP_RAM_RET �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dram0_pgt_ctrl : 3;  /* bit[0-2]  : DSP DRAM0ͨ��3���źţ�SD��DSLP��SLP�������书��ģʽ��
                                                          Ĭ��ΪNormal Mode(SD=0��DSLP=0��SLP=0)
                                                          ���ĳƬRAM�ڲ���Ҫʹ�õ�ʱ�򣬿���ͨ��������ð���ģʽ�л�ʱ�����Power Downģʽ(SD=1��DSLP=0��SLP=0)���Խ�ʡ���ġ�
                                                          bit[2]:SD
                                                          bit[1]:DSLP
                                                          bit[0]:SLP */
        unsigned int  dram1_pgt_ctrl : 3;  /* bit[3-5]  : DSP DRAM1ͨ��3���źţ�SD��DSLP��SLP�������书��ģʽ��
                                                          Ĭ��ΪNormal Mode(SD=0��DSLP=0��SLP=0)
                                                          ���ĳƬRAM�ڲ���Ҫʹ�õ�ʱ�򣬿���ͨ��������ð���ģʽ�л�ʱ�����Power Downģʽ(SD=1��DSLP=0��SLP=0)���Խ�ʡ���ġ�
                                                          bit[5]:SD
                                                          bit[4]:DSLP
                                                          bit[3]:SLP */
        unsigned int  iram0_pgt_ctrl : 3;  /* bit[6-8]  : DSP IRAM0ͨ��3���źţ�SD��DSLP��SLP�������书��ģʽ��
                                                          Ĭ��ΪNormal Mode(SD=0��DSLP=0��SLP=0)
                                                          ���ĳƬRAM�ڲ���Ҫʹ�õ�ʱ�򣬿���ͨ��������ð���ģʽ�л�ʱ�����Power Downģʽ(SD=1��DSLP=0��SLP=0)���Խ�ʡ���ġ�
                                                          bit[8]:SD
                                                          bit[7]:DSLP
                                                          bit[6]:SLP */
        unsigned int  reserved       : 7;  /* bit[9-15] : ������ */
        unsigned int  write_en       : 16; /* bit[16-31]: R_DSP_RAM_RETÿ������λ��дʹ��λ��
                                                          ֻ�е�write_en��Ӧ�ı���λΪ1'b1����R_DSP_RAM_RET��Ӧ�ı���λ��д�����������á�write_en[0]����R_DSP_RAM_RET[0]��дʹ��λ��д1��Ч�� */
    } reg;
} SOC_ASP_CFG_R_DSP_RAM_RET_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_RAM_RET_dram0_pgt_ctrl_START  (0)
#define SOC_ASP_CFG_R_DSP_RAM_RET_dram0_pgt_ctrl_END    (2)
#define SOC_ASP_CFG_R_DSP_RAM_RET_dram1_pgt_ctrl_START  (3)
#define SOC_ASP_CFG_R_DSP_RAM_RET_dram1_pgt_ctrl_END    (5)
#define SOC_ASP_CFG_R_DSP_RAM_RET_iram0_pgt_ctrl_START  (6)
#define SOC_ASP_CFG_R_DSP_RAM_RET_iram0_pgt_ctrl_END    (8)
#define SOC_ASP_CFG_R_DSP_RAM_RET_write_en_START        (16)
#define SOC_ASP_CFG_R_DSP_RAM_RET_write_en_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_TZ_SECURE_N_UNION
 �ṹ˵��  : R_TZ_SECURE_N �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 1;  /* bit[0]    :  */
        unsigned int  reserved_1           : 1;  /* bit[1]    :  */
        unsigned int  tz_secure_asphdmi_n  : 1;  /* bit[2]    : asp hdmiģ��İ�ȫ���ԣ�
                                                                0��asp hdmiֻ�ܱ���ȫ���ã�
                                                                1��asp hdmi���Ա��ǰ�ȫ���ã�
                                                                �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  tz_secure_sioaudio_n : 1;  /* bit[3]    : asp sio_audioģ��İ�ȫ���ԣ�
                                                                0��asp sio_audioֻ�ܱ���ȫ���ã�
                                                                1��asp sio_audio���Ա��ǰ�ȫ���ã�
                                                                �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  tz_secure_siovoice_n : 1;  /* bit[4]    : asp sio_voiceģ��İ�ȫ���ԣ�
                                                                0��asp sio_voiceֻ�ܱ���ȫ���ã�
                                                                1��asp sio_voice���Ա��ǰ�ȫ���ã�
                                                                �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  tz_secure_siobt_n    : 1;  /* bit[5]    : asp sio_btģ��İ�ȫ���ԣ�
                                                                0��asp sio_btֻ�ܱ���ȫ���ã�
                                                                1��asp sio_bt���Ա��ǰ�ȫ���ã�
                                                                �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  tz_secure_siomodem_n : 1;  /* bit[6]    : asp sio_modemģ��İ�ȫ���ԣ�
                                                                0��asp sio_modemֻ�ܱ���ȫ���ã�
                                                                1��asp sio_modem���Ա��ǰ�ȫ���ã�
                                                                �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  tz_secure_slimbus_n  : 1;  /* bit[7]    : asp slimbusģ��İ�ȫ���ԣ�
                                                                0��asp slimbusֻ�ܱ���ȫ���ã�
                                                                1��asp slimbus���Ա��ǰ�ȫ���ã�
                                                                �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  tz_secure_edamc_n    : 1;  /* bit[8]    : asp dmacģ��İ�ȫ���ԣ�
                                                                0��asp dmacֻ�ܱ���ȫ���ã�
                                                                1��asp dmac���Ա��ǰ�ȫ���ã�
                                                                �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  tz_secure_ipc_n      : 1;  /* bit[9]    : asp ipcģ��İ�ȫ���ԣ�
                                                                0��asp ipcֻ�ܱ���ȫ���ã�
                                                                1��asp ipc���Ա��ǰ�ȫ���ã�
                                                                �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  tz_secure_watchdog_n : 1;  /* bit[10]   : asp watchdogģ��İ�ȫ���ԣ�
                                                                0��asp watchdogֻ�ܱ���ȫ���ã�
                                                                1��asp watchdog���Ա��ǰ�ȫ���ã�
                                                                �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  tz_secure_dsp_n      : 1;  /* bit[11]   : dspģ��slave�˿ڣ���ITCM/DTCM���İ�ȫ���ԣ�
                                                                0��dspģ��slave�˿�ֻ�ܱ���ȫ���ã�
                                                                1��dspģ��slave�˿ڿ��Ա��ǰ�ȫ���ã�
                                                                �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  tz_secure_gpio_n     : 1;  /* bit[12]   : asp gpioģ��İ�ȫ���ԣ�
                                                                0��asp gpioֻ�ܱ���ȫ���ã�
                                                                1��asp gpio���Ա��ǰ�ȫ���ã�
                                                                �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  tz_secure_timer0_n   : 1;  /* bit[13]   : asp timer0ģ��İ�ȫ���ԣ�
                                                                0��asp timer0ֻ�ܱ���ȫ���ã�
                                                                1��asp timer0���Ա��ǰ�ȫ���ã�
                                                                �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  tz_secure_timer1_n   : 1;  /* bit[14]   : asp timer1ģ��İ�ȫ���ԣ�
                                                                0��asp timer1ֻ�ܱ���ȫ���ã�
                                                                1��asp timer1���Ա��ǰ�ȫ���ã�
                                                                �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  dsp_mst_secure_n     : 1;  /* bit[15]   : dspģ��master�˿ڵİ�ȫ���ԣ�
                                                                0��dspģ��master�˿ڷ����Ĳ����ǰ�ȫ�ģ�
                                                                1��dspģ��master�˿ڷ����Ĳ����Ƿǰ�ȫ�ģ�
                                                                �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  write_en             : 16; /* bit[16-31]: R_TZ_SECURE_Nÿ������λ��дʹ��λ��
                                                                ֻ�е�write_en��Ӧ�ı���λΪ1'b1����R_TZ_SECURE_��Ӧ�ı���λ��д�����������á�write_en[0]����R_TZ_SECURE_[0]��дʹ��λ��д1��Ч�� */
    } reg;
} SOC_ASP_CFG_R_TZ_SECURE_N_UNION;
#endif
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_asphdmi_n_START   (2)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_asphdmi_n_END     (2)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_sioaudio_n_START  (3)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_sioaudio_n_END    (3)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_siovoice_n_START  (4)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_siovoice_n_END    (4)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_siobt_n_START     (5)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_siobt_n_END       (5)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_siomodem_n_START  (6)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_siomodem_n_END    (6)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_slimbus_n_START   (7)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_slimbus_n_END     (7)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_edamc_n_START     (8)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_edamc_n_END       (8)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_ipc_n_START       (9)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_ipc_n_END         (9)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_watchdog_n_START  (10)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_watchdog_n_END    (10)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_dsp_n_START       (11)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_dsp_n_END         (11)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_gpio_n_START      (12)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_gpio_n_END        (12)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_timer0_n_START    (13)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_timer0_n_END      (13)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_timer1_n_START    (14)
#define SOC_ASP_CFG_R_TZ_SECURE_N_tz_secure_timer1_n_END      (14)
#define SOC_ASP_CFG_R_TZ_SECURE_N_dsp_mst_secure_n_START      (15)
#define SOC_ASP_CFG_R_TZ_SECURE_N_dsp_mst_secure_n_END        (15)
#define SOC_ASP_CFG_R_TZ_SECURE_N_write_en_START              (16)
#define SOC_ASP_CFG_R_TZ_SECURE_N_write_en_END                (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_OCRAM_R0SIZE_UNION
 �ṹ˵��  : R_OCRAM_R0SIZE �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x000003FF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ocram_r0size : 10; /* bit[0-9]  : OCRAM��ȫ�����������4KBΪ��λ��r0size[9]=1'b1������OCRAMΪ��ȫ��r0size[9]=1'b0ʱ����ȫ����Ĵ�СΪ4KB*r0size[8:0]��
                                                        �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  reserved     : 22; /* bit[10-31]:  */
    } reg;
} SOC_ASP_CFG_R_OCRAM_R0SIZE_UNION;
#endif
#define SOC_ASP_CFG_R_OCRAM_R0SIZE_ocram_r0size_START  (0)
#define SOC_ASP_CFG_R_OCRAM_R0SIZE_ocram_r0size_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_UNION
 �ṹ˵��  : R_SIO_LOOP_SECURE_N �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio_audio_loop_secure_n : 1;  /* bit[0]   : sio audio��loopʹ�ܼĴ����İ�ȫ���ԣ�
                                                                  0��sio audio��loopʹ�ܼĴ���ֻ�ܱ���ȫ���ã�
                                                                  1��sio audio��loopʹ�ܼĴ������Ա��ǰ�ȫ���ã�
                                                                  �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  sio_voice_loop_secure_n : 1;  /* bit[1]   : sio voice��loopʹ�ܼĴ����İ�ȫ���ԣ�
                                                                  0��sio voice��loopʹ�ܼĴ���ֻ�ܱ���ȫ���ã�
                                                                  1��sio voice��loopʹ�ܼĴ������Ա��ǰ�ȫ���ã�
                                                                  �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  sio_bt_loop_secure_n    : 1;  /* bit[2]   : sio bt��loopʹ�ܼĴ����İ�ȫ���ԣ�
                                                                  0��sio bt��loopʹ�ܼĴ���ֻ�ܱ���ȫ���ã�
                                                                  1��sio bt��loopʹ�ܼĴ������Ա��ǰ�ȫ���ã�
                                                                  �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  sio_modem_loop_secure_n : 1;  /* bit[3]   : sio modem��loopʹ�ܼĴ����İ�ȫ���ԣ�
                                                                  0��sio modem��loopʹ�ܼĴ���ֻ�ܱ���ȫ���ã�
                                                                  1��sio modem��loopʹ�ܼĴ������Ա��ǰ�ȫ���ã�
                                                                  �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  reserved                : 28; /* bit[4-31]:  */
    } reg;
} SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_UNION;
#endif
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_audio_loop_secure_n_START  (0)
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_audio_loop_secure_n_END    (0)
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_voice_loop_secure_n_START  (1)
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_voice_loop_secure_n_END    (1)
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_bt_loop_secure_n_START     (2)
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_bt_loop_secure_n_END       (2)
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_modem_loop_secure_n_START  (3)
#define SOC_ASP_CFG_R_SIO_LOOP_SECURE_N_sio_modem_loop_secure_n_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_INTR_S_INI_UNION
 �ṹ˵��  : R_INTR_S_INI �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȫ�ж�ԭʼ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_hdmi_int_secure : 1;  /* bit[0]   : asp_hdmiԭʼ��ȫ�жϡ�
                                                              0�����жϣ�
                                                              1�����жϡ� */
        unsigned int  reserved_0          : 1;  /* bit[1]   :  */
        unsigned int  reserved_1          : 1;  /* bit[2]   :  */
        unsigned int  reserved_2          : 29; /* bit[3-31]:  */
    } reg;
} SOC_ASP_CFG_R_INTR_S_INI_UNION;
#endif
#define SOC_ASP_CFG_R_INTR_S_INI_asp_hdmi_int_secure_START  (0)
#define SOC_ASP_CFG_R_INTR_S_INI_asp_hdmi_int_secure_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_INTR_S_EN_UNION
 �ṹ˵��  : R_INTR_S_EN �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȫ�ж�ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_hdmi_int_secure_en : 1;  /* bit[0]   : asp_hdmi��ȫ�ж�ʹ�ܡ�
                                                                 0����ʹ�ܣ�
                                                                 1��ʹ�ܡ�
                                                                 �˼Ĵ���ֻ�а�ȫ���䣻 */
        unsigned int  reserved_0             : 1;  /* bit[1]   :  */
        unsigned int  reserved_1             : 1;  /* bit[2]   :  */
        unsigned int  reserved_2             : 29; /* bit[3-31]:  */
    } reg;
} SOC_ASP_CFG_R_INTR_S_EN_UNION;
#endif
#define SOC_ASP_CFG_R_INTR_S_EN_asp_hdmi_int_secure_en_START  (0)
#define SOC_ASP_CFG_R_INTR_S_EN_asp_hdmi_int_secure_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_INTR_S_MASK_UNION
 �ṹ˵��  : R_INTR_S_MASK �Ĵ����ṹ���塣��ַƫ����:0x0114����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȫ�ж����κ�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  asp_hdmi_int_secure_mask : 1;  /* bit[0]   : asp_hdmi���κ�ȫ�жϡ�
                                                                   0�����жϣ�
                                                                   1�����жϡ� */
        unsigned int  reserved_0               : 1;  /* bit[1]   :  */
        unsigned int  reserved_1               : 1;  /* bit[2]   :  */
        unsigned int  reserved_2               : 29; /* bit[3-31]:  */
    } reg;
} SOC_ASP_CFG_R_INTR_S_MASK_UNION;
#endif
#define SOC_ASP_CFG_R_INTR_S_MASK_asp_hdmi_int_secure_mask_START  (0)
#define SOC_ASP_CFG_R_INTR_S_MASK_asp_hdmi_int_secure_mask_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DSP_REMAPPING_EN_UNION
 �ṹ˵��  : R_DSP_REMAPPING_EN �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x00000000�����:32
 �Ĵ���˵��: dsp��ַ��ӳ��ʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remap_length          : 8;  /* bit[0-7] : remaping ��ַ���ȣ���ַ��ΧΪ1MB *�� remap_length+1��
                                                                �˼Ĵ�����ȫ���Կ��䣻 */
        unsigned int  dsp_addr_remapping_en : 1;  /* bit[8]   : dsp address remapping enable
                                                                0��disable address remapping��
                                                                1��enable address remapping��
                                                                �˼Ĵ�����ȫ���Կ��䣻 */
        unsigned int  reserved              : 23; /* bit[9-31]:  */
    } reg;
} SOC_ASP_CFG_R_DSP_REMAPPING_EN_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_REMAPPING_EN_remap_length_START           (0)
#define SOC_ASP_CFG_R_DSP_REMAPPING_EN_remap_length_END             (7)
#define SOC_ASP_CFG_R_DSP_REMAPPING_EN_dsp_addr_remapping_en_START  (8)
#define SOC_ASP_CFG_R_DSP_REMAPPING_EN_dsp_addr_remapping_en_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DSP_REMAPPING_SRC_BASE_ADDR_UNION
 �ṹ˵��  : R_DSP_REMAPPING_SRC_BASE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x011C����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSP ��ַ��ӳ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved                : 20; /* bit[0-19] : ���� */
        unsigned int  asp_reserved_start_addr : 12; /* bit[20-31]: asp Ԥ����remapping��ʼ��ַ��
                                                                   �˼Ĵ�����ȫ���Կ��䣻 */
    } reg;
} SOC_ASP_CFG_R_DSP_REMAPPING_SRC_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_REMAPPING_SRC_BASE_ADDR_asp_reserved_start_addr_START  (20)
#define SOC_ASP_CFG_R_DSP_REMAPPING_SRC_BASE_ADDR_asp_reserved_start_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DSP_REMAPPING_DES_BASE_ADDR_UNION
 �ṹ˵��  : R_DSP_REMAPPING_DES_BASE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSP ��ַ��ӳ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved       : 20; /* bit[0-19] : ���� */
        unsigned int  ddr_start_addr : 12; /* bit[20-31]: remappingĿ���ַ����ʼ��ַ��
                                                          �˼Ĵ�����ȫ���Կ��䣻 */
    } reg;
} SOC_ASP_CFG_R_DSP_REMAPPING_DES_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DSP_REMAPPING_DES_BASE_ADDR_ddr_start_addr_START  (20)
#define SOC_ASP_CFG_R_DSP_REMAPPING_DES_BASE_ADDR_ddr_start_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_UNION
 �ṹ˵��  : R_DDR_HARQ_REMAP_EN �Ĵ����ṹ���塣��ַƫ����:0x124����ֵ:0x00000000�����:32
 �Ĵ���˵��: DDR��Harq Memory remap���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remap_length : 9;  /* bit[0-8]  : DDR��Harq Memory remap��ַ��Χ���ã���ַ��ΧΪ4kB * remap_length
                                                        �˼Ĵ�����ȫ���Կ��䣻 */
        unsigned int  remap_en     : 1;  /* bit[9]    : ��DSP���ӽǣ�DDR��Harq Memory remapʹ�ܿ���
                                                        1��ʹ��
                                                        0����ʹ��
                                                        �˼Ĵ�����ȫ���Կ��䣻 */
        unsigned int  reserved     : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_remap_length_START  (0)
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_remap_length_END    (8)
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_remap_en_START      (9)
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_EN_remap_en_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DDR_HARQ_REMAP_SRC_BASE_ADDR_UNION
 �ṹ˵��  : R_DDR_HARQ_REMAP_SRC_BASE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x128����ֵ:0x00000000�����:32
 �Ĵ���˵��: DDR��Harq Memory remapԴ����ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 12; /* bit[0-11] : ���� */
        unsigned int  src_base_addr : 20; /* bit[12-31]: DDR��Harq Memory remapԴ����ַ��ʵ�ʵĵ�ַΪ��4kB * src_base_addr
                                                         �˼Ĵ�����ȫ���Կ��䣻 */
    } reg;
} SOC_ASP_CFG_R_DDR_HARQ_REMAP_SRC_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_SRC_BASE_ADDR_src_base_addr_START  (12)
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_SRC_BASE_ADDR_src_base_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DDR_HARQ_REMAP_DES_BASE_ADDR_UNION
 �ṹ˵��  : R_DDR_HARQ_REMAP_DES_BASE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x12C����ֵ:0x00000000�����:32
 �Ĵ���˵��: DDR��Harq Memory remapĿ�����ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 12; /* bit[0-11] :  */
        unsigned int  des_base_addr : 20; /* bit[12-31]: DDR��Harq Memory remapĿ�����ַ��ʵ�ʵĵ�ַΪ��4kB * des_base_addr
                                                         �˼Ĵ�����ȫ���Կ��䣻 */
    } reg;
} SOC_ASP_CFG_R_DDR_HARQ_REMAP_DES_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_DES_BASE_ADDR_des_base_addr_START  (12)
#define SOC_ASP_CFG_R_DDR_HARQ_REMAP_DES_BASE_ADDR_des_base_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_UNION
 �ṹ˵��  : R_DDR_MMBUF_REMAP_EN �Ĵ����ṹ���塣��ַƫ����:0x130����ֵ:0x00000000�����:32
 �Ĵ���˵��: DDR��MMBUF remap���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remap_length : 9;  /* bit[0-8]  : DDR��MMBUF remap��ַ��Χ���ã���ַ��ΧΪ4kB * remap_length
                                                        �˼Ĵ�����ȫ���Կ��䣻 */
        unsigned int  remap_en     : 1;  /* bit[9]    : ��DSP���ӽǣ�DDR��MMBUF remapʹ�ܿ���
                                                        1��ʹ��
                                                        0����ʹ��
                                                        �˼Ĵ�����ȫ���Կ��䣻 */
        unsigned int  reserved     : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_remap_length_START  (0)
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_remap_length_END    (8)
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_remap_en_START      (9)
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_EN_remap_en_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DDR_MMBUF_REMAP_SRC_BASE_ADDR_UNION
 �ṹ˵��  : R_DDR_MMBUF_REMAP_SRC_BASE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x134����ֵ:0x00000000�����:32
 �Ĵ���˵��: DDR��MMBUF remapԴ����ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 12; /* bit[0-11] : ���� */
        unsigned int  src_base_addr : 20; /* bit[12-31]: DDR��MMBUF remapԴ����ַ��ʵ�ʵĵ�ַΪ��4kB * src_base_addr
                                                         �˼Ĵ�����ȫ���Կ��䣻 */
    } reg;
} SOC_ASP_CFG_R_DDR_MMBUF_REMAP_SRC_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_SRC_BASE_ADDR_src_base_addr_START  (12)
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_SRC_BASE_ADDR_src_base_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DDR_MMBUF_REMAP_DES_BASE_ADDR_UNION
 �ṹ˵��  : R_DDR_MMBUF_REMAP_DES_BASE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x138����ֵ:0x00000000�����:32
 �Ĵ���˵��: DDR��MMBUF remapĿ�����ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 12; /* bit[0-11] :  */
        unsigned int  des_base_addr : 20; /* bit[12-31]: DDR��MMBUF remapĿ�����ַ��ʵ�ʵĵ�ַΪ��4kB * des_base_addr
                                                         �˼Ĵ�����ȫ���Կ��䣻 */
    } reg;
} SOC_ASP_CFG_R_DDR_MMBUF_REMAP_DES_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_DES_BASE_ADDR_des_base_addr_START  (12)
#define SOC_ASP_CFG_R_DDR_MMBUF_REMAP_DES_BASE_ADDR_des_base_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_UNION
 �ṹ˵��  : R_DDR_OCRAM_REMAP_EN �Ĵ����ṹ���塣��ַƫ����:0x13C����ֵ:0x00000000�����:32
 �Ĵ���˵��: DDR��OCRAM remap���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  remap_length : 9;  /* bit[0-8]  : DDR��OCRAM remap��ַ��Χ���ã���ַ��ΧΪ4kB * remap_length
                                                        �˼Ĵ�����ȫ���Կ��䣻 */
        unsigned int  remap_en     : 1;  /* bit[9]    : ��DSP���ӽǣ�DDR��OCRAM remapʹ�ܿ���
                                                        1��ʹ��
                                                        0����ʹ��
                                                        �˼Ĵ�����ȫ���Կ��䣻 */
        unsigned int  reserved     : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_remap_length_START  (0)
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_remap_length_END    (8)
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_remap_en_START      (9)
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_EN_remap_en_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DDR_OCRAM_REMAP_SRC_BASE_ADDR_UNION
 �ṹ˵��  : R_DDR_OCRAM_REMAP_SRC_BASE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x140����ֵ:0x00000000�����:32
 �Ĵ���˵��: DDR��OCRAM remapԴ����ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 12; /* bit[0-11] : ���� */
        unsigned int  src_base_addr : 20; /* bit[12-31]: DDR��OCRAM remapԴ����ַ��ʵ�ʵĵ�ַΪ��4kB * src_base_addr
                                                         �˼Ĵ�����ȫ���Կ��䣻 */
    } reg;
} SOC_ASP_CFG_R_DDR_OCRAM_REMAP_SRC_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_SRC_BASE_ADDR_src_base_addr_START  (12)
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_SRC_BASE_ADDR_src_base_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_DDR_OCRAM_REMAP_DES_BASE_ADDR_UNION
 �ṹ˵��  : R_DDR_OCRAM_REMAP_DES_BASE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x144����ֵ:0x00000000�����:32
 �Ĵ���˵��: DDR��OCRAM remapĿ�����ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 12; /* bit[0-11] :  */
        unsigned int  des_base_addr : 20; /* bit[12-31]: DDR��OCRAM remapĿ�����ַ��ʵ�ʵĵ�ַΪ��4kB * des_base_addr
                                                         �˼Ĵ�����ȫ���Կ��䣻 */
    } reg;
} SOC_ASP_CFG_R_DDR_OCRAM_REMAP_DES_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_DES_BASE_ADDR_des_base_addr_START  (12)
#define SOC_ASP_CFG_R_DDR_OCRAM_REMAP_DES_BASE_ADDR_des_base_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_MMBUF_CTRL_UNION
 �ṹ˵��  : R_MMBUF_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0148����ֵ:0x000000FD�����:32
 �Ĵ���˵��: MMBUF CTRL���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll0_en      : 1;  /* bit[0]    : PPLl0���ؿ��ƣ�
                                                         1���� 0���ر� */
        unsigned int  fll_en        : 1;  /* bit[1]    : FLL���ؿ��ƣ�
                                                         1���� 0���ر� */
        unsigned int  mmbuf_clk_en  : 1;  /* bit[2]    : MMBUFʱ���ſأ�
                                                         1���� 0���ر� */
        unsigned int  aobus_clk_en  : 1;  /* bit[3]    : AOBUSʱ���ſأ�
                                                         1���� 0���ر� */
        unsigned int  mmbuf_clk_sel : 2;  /* bit[4-5]  : MMBUFʱ��ѡ��
                                                         1X��ppll0 
                                                         01��fll
                                                         00��tcxo */
        unsigned int  aobus_clk_sel : 2;  /* bit[6-7]  : AOBUSʱ��ѡ��
                                                         11��ppll0 
                                                         10��ddrpll 
                                                         01��fll
                                                         00��tcxo */
        unsigned int  reserved      : 8;  /* bit[8-15] : ������ */
        unsigned int  write_en      : 16; /* bit[16-31]: R_MMBUF_CTRLÿ������λ��дʹ��λ��
                                                         ֻ�е�write_en��Ӧ�ı���λΪ1'b1����R_MMBUF_CTRL��Ӧ�ı���λ��д�����������á�write_en[0]����R_MMBUF_CTRL[0]��дʹ��λ��д1��Ч�� */
    } reg;
} SOC_ASP_CFG_R_MMBUF_CTRL_UNION;
#endif
#define SOC_ASP_CFG_R_MMBUF_CTRL_ppll0_en_START       (0)
#define SOC_ASP_CFG_R_MMBUF_CTRL_ppll0_en_END         (0)
#define SOC_ASP_CFG_R_MMBUF_CTRL_fll_en_START         (1)
#define SOC_ASP_CFG_R_MMBUF_CTRL_fll_en_END           (1)
#define SOC_ASP_CFG_R_MMBUF_CTRL_mmbuf_clk_en_START   (2)
#define SOC_ASP_CFG_R_MMBUF_CTRL_mmbuf_clk_en_END     (2)
#define SOC_ASP_CFG_R_MMBUF_CTRL_aobus_clk_en_START   (3)
#define SOC_ASP_CFG_R_MMBUF_CTRL_aobus_clk_en_END     (3)
#define SOC_ASP_CFG_R_MMBUF_CTRL_mmbuf_clk_sel_START  (4)
#define SOC_ASP_CFG_R_MMBUF_CTRL_mmbuf_clk_sel_END    (5)
#define SOC_ASP_CFG_R_MMBUF_CTRL_aobus_clk_sel_START  (6)
#define SOC_ASP_CFG_R_MMBUF_CTRL_aobus_clk_sel_END    (7)
#define SOC_ASP_CFG_R_MMBUF_CTRL_write_en_START       (16)
#define SOC_ASP_CFG_R_MMBUF_CTRL_write_en_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_UNION
 �ṹ˵��  : R_HIFIDSP_CLK_DIV_AUTO �Ĵ����ṹ���塣��ַƫ����:0x014C����ֵ:0x00000000�����:32
 �Ĵ���˵��: HIFIDSPʱ��Ƶ���Զ���Ƶ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  hifidsp_idle_time_cfgcnt : 8;  /* bit[0-7]  : 
                                                                    HIFIDSP WFI�ź���Ч֮��ȴ��������ã���ʵ�ʵȴ����ڴ��ڵ�����������֮��Ӳ����ʼ�Զ���Ƶ��
                                                                    �ȴ�����0~255���䣻 */
        unsigned int  div_hifidsp_clk_auto     : 3;  /* bit[8-10] : HIFIDSP COREʱ�ӽ�Ƶ���ã�����ʱ�ӻ���COREʱ��һ��Ƶ
                                                                    0������Ƶ,DIVΪ�������ֵ��
                                                                    1��DIV��Ϊ�������Ƶ�ʵ�1/2��
                                                                    2��DIV��Ϊ�������Ƶ�ʵ�1/4��
                                                                    3��DIV��Ϊ�������Ƶ�ʵ�1/8��
                                                                    4��DIV��Ϊ�������Ƶ�ʵ�1/16��
                                                                    5��DIV��Ϊ�������Ƶ�ʵ�1/32��
                                                                    6��7��DIV��Ϊ6'h3F��
                                                                    ע���Զ���Ƶ֮�����ֻ��ΪԴʱ�ӵ�1/64;����������div�����Զ���Ƶ����֮�󳬹�1/64����Ĭ�Ͻ���1/64�� */
        unsigned int  reserved_0               : 1;  /* bit[11]   : ���� */
        unsigned int  reserved_1               : 1;  /* bit[12]   : ���� */
        unsigned int  reserved_2               : 1;  /* bit[13]   : ���� */
        unsigned int  dsp_pwaitmode_bypass     : 1;  /* bit[14]   : dsp pwaitmode״̬bypass����
                                                                    0��bypass��Ч
                                                                    1��bypass��Ч */
        unsigned int  dw_axi_m1_st_bypass      : 1;  /* bit[15]   : dw_axi����mst1�ӿ�״̬bypass����
                                                                    0��bypass��Ч
                                                                    1��bypass��Ч */
        unsigned int  dw_axi_m2_st_bypass      : 1;  /* bit[16]   : dw_axi����mst2�ӿ�״̬bypass����
                                                                    0��bypass��Ч
                                                                    1��bypass��Ч */
        unsigned int  dw_axi_m3_st_bypass      : 1;  /* bit[17]   : dw_axi����mst3�ӿ�״̬bypass����
                                                                    0��bypass��Ч
                                                                    1��bypass��Ч */
        unsigned int  dw_axi_m4_st_bypass      : 1;  /* bit[18]   : dw_axi����mst4�ӿ�״̬bypass����
                                                                    0��bypass��Ч
                                                                    1��bypass��Ч */
        unsigned int  reserved_3               : 13; /* bit[19-31]:  */
    } reg;
} SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_UNION;
#endif
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_hifidsp_idle_time_cfgcnt_START  (0)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_hifidsp_idle_time_cfgcnt_END    (7)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_div_hifidsp_clk_auto_START      (8)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_div_hifidsp_clk_auto_END        (10)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dsp_pwaitmode_bypass_START      (14)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dsp_pwaitmode_bypass_END        (14)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m1_st_bypass_START       (15)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m1_st_bypass_END         (15)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m2_st_bypass_START       (16)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m2_st_bypass_END         (16)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m3_st_bypass_START       (17)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m3_st_bypass_END         (17)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m4_st_bypass_START       (18)
#define SOC_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_dw_axi_m4_st_bypass_END         (18)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_UNION
 �ṹ˵��  : R_INTR_FREQ_OFFSET_CFG �Ĵ����ṹ���塣��ַƫ����:0x0150����ֵ:0x00000110�����:32
 �Ĵ���˵��: Ƶƫ��¼ģ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  freq_offset_en       : 1;  /* bit[0]    : Ƶƫ��¼ģ��ʹ�ܣ�
                                                                0����ʹ�ܣ�
                                                                1��ʹ�ܣ� */
        unsigned int  freq_offset_cnt_freq : 2;  /* bit[1-2]  : Ƶƫ��¼ģ�����Ƶ�����ã�
                                                                0����8KHz������
                                                                1����16KHz������
                                                                2����32KHz������
                                                                3����48KHz������ */
        unsigned int  intr_freq_offset_clr : 1;  /* bit[3]    : Ƶƫ��¼ģ���ж�д�壬������������жϣ�
                                                                0����Ч��
                                                                1���ж����㣻 */
        unsigned int  intr_freq_offset_msk : 1;  /* bit[4]    : Ƶƫ��¼ģ���ж����Σ�
                                                                0��������Ч��
                                                                1��������Ч�� */
        unsigned int  reserved_0           : 3;  /* bit[5-7]  : ������ */
        unsigned int  freq_offset_limen    : 8;  /* bit[8-15] : Ƶƫ��¼ģ����ֵ�������á�����ֵ>=��ֵʱ���ϱ��жϡ���������0��
                                                                ���÷�Χ1~255�� */
        unsigned int  reserved_1           : 16; /* bit[16-31]:  */
    } reg;
} SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_UNION;
#endif
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_freq_offset_en_START        (0)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_freq_offset_en_END          (0)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_freq_offset_cnt_freq_START  (1)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_freq_offset_cnt_freq_END    (2)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_intr_freq_offset_clr_START  (3)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_intr_freq_offset_clr_END    (3)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_intr_freq_offset_msk_START  (4)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_intr_freq_offset_msk_END    (4)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_freq_offset_limen_START     (8)
#define SOC_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_freq_offset_limen_END       (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR_EN_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0160����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��ʹ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor0_en : 1;  /* bit[0]   : �ڴ���ʹ�ܣ�
                                                           0����ʹ�ܣ�
                                                           1��ʹ�ܣ� */
        unsigned int  addr_monitor1_en : 1;  /* bit[1]   : �ڴ���ʹ�ܣ�
                                                           0����ʹ�ܣ�
                                                           1��ʹ�ܣ� */
        unsigned int  addr_monitor2_en : 1;  /* bit[2]   : �ڴ���ʹ�ܣ�
                                                           0����ʹ�ܣ�
                                                           1��ʹ�ܣ� */
        unsigned int  addr_monitor3_en : 1;  /* bit[3]   : �ڴ���ʹ�ܣ�
                                                           0����ʹ�ܣ�
                                                           1��ʹ�ܣ� */
        unsigned int  reserved         : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor0_en_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor0_en_END    (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor1_en_START  (1)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor1_en_END    (1)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor2_en_START  (2)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor2_en_END    (2)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor3_en_START  (3)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_addr_monitor3_en_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0164����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ���ж��������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor_intr_clr : 1;  /* bit[0]   : �ڴ����ж����㣺
                                                                0����Ч��
                                                                1�����㣻 */
        unsigned int  reserved              : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR_addr_monitor_intr_clr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR_addr_monitor_intr_clr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0168����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ���ж�ʹ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor0_intr_en : 1;  /* bit[0]   : �ڴ����ж�ʹ�ܣ�
                                                                0����ʹ�ܣ�
                                                                1��ʹ�ܣ� */
        unsigned int  addr_monitor1_intr_en : 1;  /* bit[1]   : �ڴ����ж�ʹ�ܣ�
                                                                0����ʹ�ܣ�
                                                                1��ʹ�ܣ� */
        unsigned int  addr_monitor2_intr_en : 1;  /* bit[2]   : �ڴ����ж�ʹ�ܣ�
                                                                0����ʹ�ܣ�
                                                                1��ʹ�ܣ� */
        unsigned int  addr_monitor3_intr_en : 1;  /* bit[3]   : �ڴ����ж�ʹ�ܣ�
                                                                0����ʹ�ܣ�
                                                                1��ʹ�ܣ� */
        unsigned int  reserved              : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor0_intr_en_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor0_intr_en_END    (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor1_intr_en_START  (1)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor1_intr_en_END    (1)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor2_intr_en_START  (2)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor2_intr_en_END    (2)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor3_intr_en_START  (3)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_addr_monitor3_intr_en_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR �Ĵ����ṹ���塣��ַƫ����:0x016C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ���ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor0_arhit_intr_stat : 1;  /* bit[0]   : �ڴ����ж�ԭʼ״̬��
                                                                        0���ж���Ч��
                                                                        1���ж���Ч�� */
        unsigned int  addr_monitor0_awhit_intr_stat : 1;  /* bit[1]   : �ڴ����ж�ԭʼ״̬��
                                                                        0���ж���Ч��
                                                                        1���ж���Ч�� */
        unsigned int  addr_monitor1_arhit_intr_stat : 1;  /* bit[2]   : �ڴ����ж�ԭʼ״̬��
                                                                        0���ж���Ч��
                                                                        1���ж���Ч�� */
        unsigned int  addr_monitor1_awhit_intr_stat : 1;  /* bit[3]   : �ڴ����ж�ԭʼ״̬��
                                                                        0���ж���Ч��
                                                                        1���ж���Ч�� */
        unsigned int  addr_monitor2_arhit_intr_stat : 1;  /* bit[4]   : �ڴ����ж�ԭʼ״̬��
                                                                        0���ж���Ч��
                                                                        1���ж���Ч�� */
        unsigned int  addr_monitor2_awhit_intr_stat : 1;  /* bit[5]   : �ڴ����ж�ԭʼ״̬��
                                                                        0���ж���Ч��
                                                                        1���ж���Ч�� */
        unsigned int  addr_monitor3_arhit_intr_stat : 1;  /* bit[6]   : �ڴ����ж�ԭʼ״̬��
                                                                        0���ж���Ч��
                                                                        1���ж���Ч�� */
        unsigned int  addr_monitor3_awhit_intr_stat : 1;  /* bit[7]   : �ڴ����ж�ԭʼ״̬��
                                                                        0���ж���Ч��
                                                                        1���ж���Ч�� */
        unsigned int  reserved                      : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor0_arhit_intr_stat_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor0_arhit_intr_stat_END    (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor0_awhit_intr_stat_START  (1)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor0_awhit_intr_stat_END    (1)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor1_arhit_intr_stat_START  (2)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor1_arhit_intr_stat_END    (2)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor1_awhit_intr_stat_START  (3)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor1_awhit_intr_stat_END    (3)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor2_arhit_intr_stat_START  (4)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor2_arhit_intr_stat_END    (4)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor2_awhit_intr_stat_START  (5)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor2_awhit_intr_stat_END    (5)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor3_arhit_intr_stat_START  (6)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor3_arhit_intr_stat_END    (6)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor3_awhit_intr_stat_START  (7)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_addr_monitor3_awhit_intr_stat_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_BASE_ADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR0_BASE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0170����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��0����ַ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved           : 12; /* bit[0-11] : ���� */
        unsigned int  addr_monitor0_base : 20; /* bit[12-31]: �ڴ���ģ��0����ַ��ʵ�ʵĵ�ַΪ��4kB * base_addr */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_BASE_ADDR_addr_monitor0_base_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_BASE_ADDR_addr_monitor0_base_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_LEN_ADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR0_LEN_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0174����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��0��ַ�������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved          : 12; /* bit[0-11] : ���� */
        unsigned int  addr_monitor0_len : 20; /* bit[12-31]: �ڴ���ģ��0��ַ���ȣ�ʵ��Ϊ��4kB * base_len */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_LEN_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_LEN_ADDR_addr_monitor0_len_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_LEN_ADDR_addr_monitor0_len_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_AWADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR0_HIT_AWADDR �Ĵ����ṹ���塣��ַƫ����:0x0178����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��0Խ���д��ַ��¼�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor0_hit_awaddr : 32; /* bit[0-31]: �ڴ���ģ��0Խ���д��ַ */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_AWADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_AWADDR_addr_monitor0_hit_awaddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_AWADDR_addr_monitor0_hit_awaddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_ARADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR0_HIT_ARADDR �Ĵ����ṹ���塣��ַƫ����:0x017C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��0Խ��Ķ���ַ��¼�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor0_hit_araddr : 32; /* bit[0-31]: �ڴ���ģ��0Խ��Ķ���ַ */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_ARADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_ARADDR_addr_monitor0_hit_araddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_ARADDR_addr_monitor0_hit_araddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_BASE_ADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR1_BASE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0180����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��1����ַ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved           : 12; /* bit[0-11] : ���� */
        unsigned int  addr_monitor1_base : 20; /* bit[12-31]: �ڴ���ģ��1����ַ��ʵ�ʵĵ�ַΪ��4kB * base_addr */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_BASE_ADDR_addr_monitor1_base_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_BASE_ADDR_addr_monitor1_base_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_LEN_ADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR1_LEN_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0184����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��1��ַ�������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved          : 12; /* bit[0-11] : ���� */
        unsigned int  addr_monitor1_len : 20; /* bit[12-31]: �ڴ���ģ��1��ַ���ȣ�ʵ��Ϊ��4kB * base_len */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_LEN_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_LEN_ADDR_addr_monitor1_len_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_LEN_ADDR_addr_monitor1_len_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_AWADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR1_HIT_AWADDR �Ĵ����ṹ���塣��ַƫ����:0x0188����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��1Խ���д��ַ��¼�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor1_hit_awaddr : 32; /* bit[0-31]: �ڴ���ģ��1Խ���д��ַ */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_AWADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_AWADDR_addr_monitor1_hit_awaddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_AWADDR_addr_monitor1_hit_awaddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_ARADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR1_HIT_ARADDR �Ĵ����ṹ���塣��ַƫ����:0x018C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��1Խ��Ķ���ַ��¼�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor1_hit_araddr : 32; /* bit[0-31]: �ڴ���ģ��1Խ��Ķ���ַ */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_ARADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_ARADDR_addr_monitor1_hit_araddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_ARADDR_addr_monitor1_hit_araddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_BASE_ADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR2_BASE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0190����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��2����ַ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved           : 12; /* bit[0-11] : ���� */
        unsigned int  addr_monitor2_base : 20; /* bit[12-31]: �ڴ���ģ��2����ַ��ʵ�ʵĵ�ַΪ��4kB * base_addr */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_BASE_ADDR_addr_monitor2_base_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_BASE_ADDR_addr_monitor2_base_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_LEN_ADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR2_LEN_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0194����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��2��ַ�������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved          : 12; /* bit[0-11] : ���� */
        unsigned int  addr_monitor2_len : 20; /* bit[12-31]: �ڴ���ģ��2��ַ���ȣ�ʵ��Ϊ��4kB * base_len */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_LEN_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_LEN_ADDR_addr_monitor2_len_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_LEN_ADDR_addr_monitor2_len_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_AWADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR2_HIT_AWADDR �Ĵ����ṹ���塣��ַƫ����:0x0198����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��2Խ���д��ַ��¼�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor2_hit_awaddr : 32; /* bit[0-31]: �ڴ���ģ��2Խ���д��ַ */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_AWADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_AWADDR_addr_monitor2_hit_awaddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_AWADDR_addr_monitor2_hit_awaddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_ARADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR2_HIT_ARADDR �Ĵ����ṹ���塣��ַƫ����:0x019C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��2Խ��Ķ���ַ��¼�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor2_hit_araddr : 32; /* bit[0-31]: �ڴ���ģ��2Խ��Ķ���ַ */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_ARADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_ARADDR_addr_monitor2_hit_araddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_ARADDR_addr_monitor2_hit_araddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_BASE_ADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR3_BASE_ADDR �Ĵ����ṹ���塣��ַƫ����:0x01A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��3����ַ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved           : 12; /* bit[0-11] : ���� */
        unsigned int  addr_monitor3_base : 20; /* bit[12-31]: �ڴ���ģ��3����ַ��ʵ�ʵĵ�ַΪ��4kB * base_addr */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_BASE_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_BASE_ADDR_addr_monitor3_base_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_BASE_ADDR_addr_monitor3_base_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_LEN_ADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR3_LEN_ADDR �Ĵ����ṹ���塣��ַƫ����:0x01A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��3��ַ�������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved          : 12; /* bit[0-11] : ���� */
        unsigned int  addr_monitor3_len : 20; /* bit[12-31]: �ڴ���ģ��3��ַ���ȣ�ʵ��Ϊ��4kB * base_len */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_LEN_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_LEN_ADDR_addr_monitor3_len_START  (12)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_LEN_ADDR_addr_monitor3_len_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_AWADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR3_HIT_AWADDR �Ĵ����ṹ���塣��ַƫ����:0x01A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��3Խ���д��ַ��¼�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor3_hit_awaddr : 32; /* bit[0-31]: �ڴ���ģ��3Խ���д��ַ */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_AWADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_AWADDR_addr_monitor3_hit_awaddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_AWADDR_addr_monitor3_hit_awaddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_ARADDR_UNION
 �ṹ˵��  : R_ACCESS_ADDR_MONITOR3_HIT_ARADDR �Ĵ����ṹ���塣��ַƫ����:0x01AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ڴ���ģ��3Խ��Ķ���ַ��¼�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  addr_monitor3_hit_araddr : 32; /* bit[0-31]: �ڴ���ģ��3Խ��Ķ���ַ */
    } reg;
} SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_ARADDR_UNION;
#endif
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_ARADDR_addr_monitor3_hit_araddr_START  (0)
#define SOC_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_ARADDR_addr_monitor3_hit_araddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_MEMORY_CTRL_UNION
 �ṹ˵��  : R_MEMORY_CTRL �Ĵ����ṹ���塣��ַƫ����:0x01B0����ֵ:0x01A800A8�����:32
 �Ĵ���˵��: memory�������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_ctrl_s  : 16; /* bit[0-15] : sram���ƼĴ���[15:0] 
                                                       ��ע����OCRAM��DSP�и���3ƬRAM�Ƿֱ���R_OCRAM_RET��R_DSP_RAM_RET�Ĵ������ƣ�����memory���ƾ��ɸüĴ������ƣ�
                                                       [0]:slp
                                                       [1]:dslp
                                                       [2]:sd
                                                       [4:3]:rtsel(SPSB RAM)
                                                       [6:5]:wtsel(SPSB RAM)
                                                       [8:7]:rtsel(SPMB RAM)
                                                       [10:9]:wtsel(SPMB RAM)
                                                       [15:11]:reserved */
        unsigned int  mem_ctrl_tp : 16; /* bit[16-31]: tpram���ƼĴ���[15:0]
                                                       ��ע����OCRAM��DSP�и���3ƬRAM�Ƿֱ���R_OCRAM_RET��R_DSP_RAM_RET�Ĵ������ƣ�����memory���ƾ��ɸüĴ������ƣ�
                                                       [0]:slp
                                                       [1]:dslp
                                                       [2]:sd
                                                       [4:3]:rct
                                                       [6:5]:wct
                                                       [8:7]:kp
                                                       [15:10]:reserved */
    } reg;
} SOC_ASP_CFG_R_MEMORY_CTRL_UNION;
#endif
#define SOC_ASP_CFG_R_MEMORY_CTRL_mem_ctrl_s_START   (0)
#define SOC_ASP_CFG_R_MEMORY_CTRL_mem_ctrl_s_END     (15)
#define SOC_ASP_CFG_R_MEMORY_CTRL_mem_ctrl_tp_START  (16)
#define SOC_ASP_CFG_R_MEMORY_CTRL_mem_ctrl_tp_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_SLIMBUS_PRIMARY_ADDR_UNION
 �ṹ˵��  : R_SLIMBUS_PRIMARY_ADDR �Ĵ����ṹ���塣��ַƫ����:0x01B4����ֵ:0x00000001�����:32
 �Ĵ���˵��: slimbus primary���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slimbus_primary : 1;  /* bit[0]   : �������ϵ縴λ��ʱ����framer���slimbusʱ�� */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_ASP_CFG_R_SLIMBUS_PRIMARY_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_SLIMBUS_PRIMARY_ADDR_slimbus_primary_START  (0)
#define SOC_ASP_CFG_R_SLIMBUS_PRIMARY_ADDR_slimbus_primary_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_SLIMBUS_ID_ADDR_UNION
 �ṹ˵��  : R_SLIMBUS_ID_ADDR �Ĵ����ṹ���塣��ַƫ����:0x01B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: slimbus id���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slimbus_id : 16; /* bit[0-15] : ����ʶ�������̣���slimbus��֯���䣬ÿ�����̵�ֵ��ͬ */
        unsigned int  reserved   : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_ASP_CFG_R_SLIMBUS_ID_ADDR_UNION;
#endif
#define SOC_ASP_CFG_R_SLIMBUS_ID_ADDR_slimbus_id_START  (0)
#define SOC_ASP_CFG_R_SLIMBUS_ID_ADDR_slimbus_id_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_UNION
 �ṹ˵��  : R_SLIM_DAT_FMT_CFG �Ĵ����ṹ���塣��ַƫ����:0x01BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: slimbus���ݸ�ʽ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dat_fmt_cfg_0 : 2;  /* bit[0-1]  : ����DPORT1��DPORT0�����ݸ�ʽ
                                                         00:������ͨ��AHB���䣬�������ݴ���
                                                         01: Data format1��
                                                         10: Data format2��
                                                         11: Data format3���ø�ʽҲΪSLIMbus֧�ֵ����ݸ�ʽ�����������ݸ�ʽת���� */
        unsigned int  dat_fmt_cfg_1 : 2;  /* bit[2-3]  : ����DPORT3��DPORT2�����ݸ�ʽ
                                                         00:������ͨ��AHB���䣬�������ݴ���
                                                         01: Data format1��
                                                         10: Data format2��
                                                         11: Data format3���ø�ʽҲΪSLIMbus֧�ֵ����ݸ�ʽ�����������ݸ�ʽת���� */
        unsigned int  dat_fmt_cfg_2 : 2;  /* bit[4-5]  : ����DPORT5��DPORT4�����ݸ�ʽ
                                                         00:������ͨ��AHB���䣬�������ݴ���
                                                         01: Data format1��
                                                         10: Data format2��
                                                         11: Data format3���ø�ʽҲΪSLIMbus֧�ֵ����ݸ�ʽ�����������ݸ�ʽת���� */
        unsigned int  dat_fmt_cfg_3 : 2;  /* bit[6-7]  : ����DPORT7��DPORT6�����ݸ�ʽ
                                                         00:������ͨ��AHB���䣬�������ݴ���
                                                         01: Data format1��
                                                         10: Data format2��
                                                         11: Data format3���ø�ʽҲΪSLIMbus֧�ֵ����ݸ�ʽ�����������ݸ�ʽת���� */
        unsigned int  dat_fmt_cfg_4 : 2;  /* bit[8-9]  : ����DPORT9��DPORT8�����ݸ�ʽ
                                                         00:������ͨ��AHB���䣬�������ݴ���
                                                         01: Data format1��
                                                         10: Data format2��
                                                         11: Data format3���ø�ʽҲΪSLIMbus֧�ֵ����ݸ�ʽ�����������ݸ�ʽת���� */
        unsigned int  dat_fmt_cfg_5 : 2;  /* bit[10-11]: ����DPORT11��DPORT10�����ݸ�ʽ
                                                         00:������ͨ��AHB���䣬�������ݴ���
                                                         01: Data format1��
                                                         10: Data format2��
                                                         11: Data format3���ø�ʽҲΪSLIMbus֧�ֵ����ݸ�ʽ�����������ݸ�ʽת���� */
        unsigned int  dat_fmt_cfg_6 : 2;  /* bit[12-13]: ����DPORT13��DPORT12�����ݸ�ʽ
                                                         00:������ͨ��AHB���䣬�������ݴ���
                                                         01: Data format1��
                                                         10: Data format2��
                                                         11: Data format3���ø�ʽҲΪSLIMbus֧�ֵ����ݸ�ʽ�����������ݸ�ʽת���� */
        unsigned int  dat_fmt_cfg_7 : 2;  /* bit[14-15]: ����DPORT15��DPORT14�����ݸ�ʽ
                                                         00:������ͨ��AHB���䣬�������ݴ���
                                                         01: Data format1��
                                                         10: Data format2��
                                                         11: Data format3���ø�ʽҲΪSLIMbus֧�ֵ����ݸ�ʽ�����������ݸ�ʽת���� */
        unsigned int  dma_mask_clr  : 8;  /* bit[16-23]: ״̬����Ĵ���������16��DPROT��ÿһ��DPORT������bitΪ1ʱ���������һ��DPORT��Mask�źŵ�״̬���ڲ�ͬ�������л�ʱ���øüĴ������г�ʼ��������dat_fmt_cfg [23]����DPORT15��DPROT14�����ã�dat_chnl_cfg [16]����DPORT1��DPROT0������
                                                         1�����������ӦDPORT��mask�źŵ�״̬��
                                                         0������������ */
        unsigned int  reserved      : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_UNION;
#endif
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_0_START  (0)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_0_END    (1)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_1_START  (2)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_1_END    (3)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_2_START  (4)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_2_END    (5)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_3_START  (6)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_3_END    (7)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_4_START  (8)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_4_END    (9)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_5_START  (10)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_5_END    (11)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_6_START  (12)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_6_END    (13)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_7_START  (14)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dat_fmt_cfg_7_END    (15)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dma_mask_clr_START   (16)
#define SOC_ASP_CFG_R_SLIM_DAT_FMT_CFG_dma_mask_clr_END     (23)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_UNION
 �ṹ˵��  : R_SLIM_DAT_CHNL_CFG �Ĵ����ṹ���塣��ַƫ����:0x01C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: slimbus����ͨ�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass       : 1;  /* bit[0]    : bypass���ܣ��Ƿ�ʹ�����ݸ�ʽת��ģ��
                                                        1'b0:ʹ������ת��ģ�飻
                                                        1'b1:bypass����ת��ģ�飬���ݲ���ת���� */
        unsigned int  reserved     : 7;  /* bit[1-7]  : ������ */
        unsigned int  chl_rght_fst : 8;  /* bit[8-15] : ����16��DPROT��ÿһ��DPORT����������λ�á�����chl_rght_fst [7]����DPORT15��DPROT14�����ã��������ƣ�chl_rght_fst [0]����DPORT1��DPROT0�����ã�ÿbit�ĺ������£�
                                                        1������ż��DPORTΪ��������
                                                        0����������DPORTΪ�������� */
        unsigned int  dat_rght_msb : 8;  /* bit[16-23]: �����ݸ�ʽΪ16bit��֯ʱ������16��DPROT��ÿһ��DPORT�������ݵ�����������ʽ������dat_rght_msb [7]����DPORT15��DPROT14�����ã��������ƣ�dat_rght_msb [0]����DPORT1��DPROT0�����ã�ÿbit�ĺ������£�
                                                        1������������������AHB����32bitλ���������ݵ�[31:16]��
                                                        0������������������AHB����32bitλ���������ݵ�[15:0]�� */
        unsigned int  dat_rght_fst : 8;  /* bit[24-31]: �����ݸ�ʽΪ24bit���ݽ�֯ʱ������16��DPROT��ÿһ��DPORT���������������ݵ�˳������dat_rght_fst [7]����DPORT15��DPROT14�����ã��Դ�����dat_rght_fst [0]����DPORT1��DPROT0�����ã�ÿbit�ĺ������£�
                                                        1�����������������������ݣ�
                                                        0�����������������������ݣ� */
    } reg;
} SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_UNION;
#endif
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_bypass_START        (0)
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_bypass_END          (0)
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_chl_rght_fst_START  (8)
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_chl_rght_fst_END    (15)
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_dat_rght_msb_START  (16)
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_dat_rght_msb_END    (23)
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_dat_rght_fst_START  (24)
#define SOC_ASP_CFG_R_SLIM_DAT_CHNL_CFG_dat_rght_fst_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_CLK0_DIV_UNION
 �ṹ˵��  : R_CLK0_DIV �Ĵ����ṹ���塣��ַƫ����:0x01D0����ֵ:0x0045E7B2�����:32
 �Ĵ���˵��: ��Ƶ�ȿ��ƼĴ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_slimbus_clk : 27; /* bit[0-26] : С����Ƶϵdiv_slimbus_clk[26:0]�����ڲ���slimbus_clk_div��
                                                           ��Ƶʱ��Ƶ��=div_slimbus_clk[26:0]/2^27*Դʱ��Ƶ�ʣ�
                                                           Դʱ����1440M����ѡ����μ�R_CLK_SEL�Ĵ�����slimbus_clk_selλ��
                                                           Դʱ�ӿ��Ա�R_GATE_CLKDIV_EN�Ĵ�����gt_slimbus_clk_divλ�ſأ� */
        unsigned int  reserved        : 5;  /* bit[27-31]:  */
    } reg;
} SOC_ASP_CFG_R_CLK0_DIV_UNION;
#endif
#define SOC_ASP_CFG_R_CLK0_DIV_div_slimbus_clk_START  (0)
#define SOC_ASP_CFG_R_CLK0_DIV_div_slimbus_clk_END    (26)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_UNION
 �ṹ˵��  : R_SECURE_AUTHORITY_EN �Ĵ����ṹ���塣��ַƫ����:0x0200����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȫ�������Կ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  secure_en_ddr_remap       : 1;  /* bit[0]   : dsp ddr remap��ؼĴ����İ�ȫ�������Կ���
                                                                    1'b0:����ǰ�ȫ�������� ddr remap��ؼĴ���
                                                                    1'b1:ֻ����ȫ�������� ddr remap��ؼĴ��� */
        unsigned int  secure_en_ddr_harq_remap  : 1;  /* bit[1]   : dsp ddr harqp remap��ؼĴ����İ�ȫ�������Կ���
                                                                    1'b0:����ǰ�ȫ�������� ddr harq remap��ؼĴ���
                                                                    1'b1:ֻ����ȫ�������� ddr harq remap��ؼĴ��� */
        unsigned int  secure_en_ddr_mmbuf_remap : 1;  /* bit[2]   : dsp ddr mmbuf remap��ؼĴ����İ�ȫ�������Կ���
                                                                    1'b0:����ǰ�ȫ�������� ddr mmbuf remap��ؼĴ���
                                                                    1'b1:ֻ����ȫ�������� ddr mmbuf remap��ؼĴ��� */
        unsigned int  secure_en_ddr_ocram_remap : 1;  /* bit[3]   : dsp ddr ocram remap��ؼĴ����İ�ȫ�������Կ���
                                                                    1'b0:����ǰ�ȫ�������� ddr ocram remap��ؼĴ���
                                                                    1'b1:ֻ����ȫ�������� ddr ocram remap��ؼĴ��� */
        unsigned int  reserved                  : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_UNION;
#endif
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_remap_START        (0)
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_remap_END          (0)
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_harq_remap_START   (1)
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_harq_remap_END     (1)
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_mmbuf_remap_START  (2)
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_mmbuf_remap_END    (2)
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_ocram_remap_START  (3)
#define SOC_ASP_CFG_R_SECURE_AUTHORITY_EN_secure_en_ddr_ocram_remap_END    (3)






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

#endif /* end of soc_asp_cfg_interface.h */
