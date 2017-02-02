/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_wch_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:25
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_WCH.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_WCH_INTERFACE_H__
#define __SOC_DSS_WCH_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_WCH
 ****************************************************************************/
/* �Ĵ���˵����RDMA����ͼ���WDMAд��ͼ�����Ͻ������buffer��ˮƽƫ��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_OFT_X0_UNION */
#define SOC_DSS_WCH_DMA_OFT_X0_ADDR(base)             ((base) + (0x0000))

/* �Ĵ���˵����RDMA����ͼ���WDMAд��ͼ�����Ͻ������buffer�Ĵ�ֱƫ��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_OFT_Y0_UNION */
#define SOC_DSS_WCH_DMA_OFT_Y0_ADDR(base)             ((base) + (0x0004))

/* �Ĵ���˵��������ͼ�����½������buffer��ˮƽƫ��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_OFT_X1_UNION */
#define SOC_DSS_WCH_DMA_OFT_X1_ADDR(base)             ((base) + (0x0008))

/* �Ĵ���˵��������ͼ�����½������buffer�Ĵ�ֱƫ��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_OFT_Y1_UNION */
#define SOC_DSS_WCH_DMA_OFT_Y1_ADDR(base)             ((base) + (0x000C))

/* �Ĵ���˵����RDMA��Mask���Ͻ�����
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_MASK0_UNION */
#define SOC_DSS_WCH_DMA_MASK0_ADDR(base)              ((base) + (0x0010))

/* �Ĵ���˵����RDMA��Mask���½�����
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_MASK1_UNION */
#define SOC_DSS_WCH_DMA_MASK1_ADDR(base)              ((base) + (0x0014))

/* �Ĵ���˵����Yƽ��RDMA��ֱStretch֮��ĸ߶�-1
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_UNION */
#define SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_ADDR(base)   ((base) + (0x0018))

/* �Ĵ���˵����RDMA����
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_CTRL_UNION */
#define SOC_DSS_WCH_DMA_CTRL_ADDR(base)               ((base) + (0x001C))

/* �Ĵ���˵����tile��ʽ��ַ��֯ʹ��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_TILE_SCRAM_UNION */
#define SOC_DSS_WCH_DMA_TILE_SCRAM_ADDR(base)         ((base) + (0x0020))

/* �Ĵ���˵����1PULSE�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_PULSE_UNION */
#define SOC_DSS_WCH_DMA_PULSE_ADDR(base)              ((base) + (0x0028))

/* �Ĵ���˵��������
   λ����UNION�ṹ:  SOC_DSS_WCH_RWCH_CFG0_UNION */
#define SOC_DSS_WCH_RWCH_CFG0_ADDR(base)              ((base) + (0x0030))

/* �Ĵ���˵����WDMA���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_FIFO_CLR_UNION */
#define SOC_DSS_WCH_DMA_FIFO_CLR_ADDR(base)           ((base) + (0x0034))

/* �Ĵ���˵����WDMA���counter_inc��counter_rst���ԼĴ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_COUNTER_DGB_UNION */
#define SOC_DSS_WCH_DMA_COUNTER_DGB_ADDR(base)        ((base) + (0x003C))

/* �Ĵ���˵����WDMA��תʱ��BURST Length�����üĴ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_ROT_BURST4_UNION */
#define SOC_DSS_WCH_DMA_ROT_BURST4_ADDR(base)         ((base) + (0x0040))

/* �Ĵ���˵����WDMA����1�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_RSV1_UNION */
#define SOC_DSS_WCH_DMA_RSV1_ADDR(base)               ((base) + (0x0044))

/* �Ĵ���˵����WDMA����2�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_RSV2_UNION */
#define SOC_DSS_WCH_DMA_RSV2_ADDR(base)               ((base) + (0x0048))

/* �Ĵ���˵����WDMA���MASKʹ�ܼĴ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_SW_MASK_EN_UNION */
#define SOC_DSS_WCH_DMA_SW_MASK_EN_ADDR(base)         ((base) + (0x004C))

/* �Ĵ���˵����WDMA���ͼ������MASK0�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_START_MASK0_UNION */
#define SOC_DSS_WCH_DMA_START_MASK0_ADDR(base)        ((base) + (0x0050))

/* �Ĵ���˵����WDMA���ͼ����βMASK0�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_END_MASK0_UNION */
#define SOC_DSS_WCH_DMA_END_MASK0_ADDR(base)          ((base) + (0x0054))

/* �Ĵ���˵����WDMA���ͼ������MASK1�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_START_MASK1_UNION */
#define SOC_DSS_WCH_DMA_START_MASK1_ADDR(base)        ((base) + (0x0058))

/* �Ĵ���˵����WDMA���ͼ����βMASK1�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_END_MASK1_UNION */
#define SOC_DSS_WCH_DMA_END_MASK1_ADDR(base)          ((base) + (0x005C))

/* �Ĵ���˵����RDMA����ͼ���WDMAд��ͼ���Yƽ��Data����ַ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_DATA_ADDR0_UNION */
#define SOC_DSS_WCH_DMA_DATA_ADDR0_ADDR(base)         ((base) + (0x0060))

/* �Ĵ���˵����RDMA����ͼ���WDMAд��ͼ���ԭͼY�е�ַƫ��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_STRIDE0_UNION */
#define SOC_DSS_WCH_DMA_STRIDE0_ADDR(base)            ((base) + (0x0064))

/* �Ĵ���˵����Yƽ������֮��Ķ�Ӧ��stride
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_STRETCH_STRIDE0_UNION */
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE0_ADDR(base)    ((base) + (0x0068))

/* �Ĵ���˵����RDMA��WDMA���ͼ��Yƽ�����128bit���ݵĸ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_DATA_NUM0_UNION */
#define SOC_DSS_WCH_DMA_DATA_NUM0_ADDR(base)          ((base) + (0x006C))

/* �Ĵ���˵������ά�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_TEST0_UNION */
#define SOC_DSS_WCH_DMA_TEST0_ADDR(base)              ((base) + (0x0070))

/* �Ĵ���˵������ά�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_TEST1_UNION */
#define SOC_DSS_WCH_DMA_TEST1_ADDR(base)              ((base) + (0x0074))

/* �Ĵ���˵������ά�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_TEST3_UNION */
#define SOC_DSS_WCH_DMA_TEST3_ADDR(base)              ((base) + (0x0078))

/* �Ĵ���˵������ά�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_TEST4_UNION */
#define SOC_DSS_WCH_DMA_TEST4_ADDR(base)              ((base) + (0x007C))

/* �Ĵ���˵����״̬�ϱ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_STATUS_Y_UNION */
#define SOC_DSS_WCH_DMA_STATUS_Y_ADDR(base)           ((base) + (0x0080))

/* �Ĵ���˵����RDMA����ͼ���WDMAд��ͼ���Uƽ��Data����ַ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_DATA_ADDR1_UNION */
#define SOC_DSS_WCH_DMA_DATA_ADDR1_ADDR(base)         ((base) + (0x0084))

/* �Ĵ���˵����RDMA����ͼ���WDMAд��ͼ���ԭͼUƽ���е�ַƫ�ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_STRIDE1_UNION */
#define SOC_DSS_WCH_DMA_STRIDE1_ADDR(base)            ((base) + (0x0088))

/* �Ĵ���˵����Uƽ������֮��Ķ�Ӧ��stride
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_STRETCH_STRIDE1_UNION */
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE1_ADDR(base)    ((base) + (0x008C))

/* �Ĵ���˵����RDMA��WDMA���ͼ��Uƽ�����128bit���ݵĸ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_DATA_NUM1_UNION */
#define SOC_DSS_WCH_DMA_DATA_NUM1_ADDR(base)          ((base) + (0x0090))

/* �Ĵ���˵������ά�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_TEST0_U_UNION */
#define SOC_DSS_WCH_DMA_TEST0_U_ADDR(base)            ((base) + (0x0094))

/* �Ĵ���˵������ά�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_TEST1_U_UNION */
#define SOC_DSS_WCH_DMA_TEST1_U_ADDR(base)            ((base) + (0x0098))

/* �Ĵ���˵������ά�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_TEST3_U_UNION */
#define SOC_DSS_WCH_DMA_TEST3_U_ADDR(base)            ((base) + (0x009C))

/* �Ĵ���˵������ά�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_TEST4_U_UNION */
#define SOC_DSS_WCH_DMA_TEST4_U_ADDR(base)            ((base) + (0x00A0))

/* �Ĵ���˵����״̬�ϱ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_STATUS_U_UNION */
#define SOC_DSS_WCH_DMA_STATUS_U_ADDR(base)           ((base) + (0x00A4))

/* �Ĵ���˵�������Ĵ���ѡ��
   λ����UNION�ṹ:  SOC_DSS_WCH_CH_RD_SHADOW_UNION */
#define SOC_DSS_WCH_CH_RD_SHADOW_ADDR(base)           ((base) + (0x00D0))

/* �Ĵ���˵����ͨ�����ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_WCH_CH_CTL_UNION */
#define SOC_DSS_WCH_CH_CTL_ADDR(base)                 ((base) + (0x00D4))

/* �Ĵ���˵����ͨ����ȫʹ��
   λ����UNION�ṹ:  SOC_DSS_WCH_CH_SECU_EN_UNION */
#define SOC_DSS_WCH_CH_SECU_EN_ADDR(base)             ((base) + (0x00D8))

/* �Ĵ���˵��������峡�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_CH_SW_END_REQ_UNION */
#define SOC_DSS_WCH_CH_SW_END_REQ_ADDR(base)          ((base) + (0x00DC))

/* �Ĵ���˵����һ��ģ��ʱ��ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_WCH_CH_CLK_SEL_UNION */
#define SOC_DSS_WCH_CH_CLK_SEL_ADDR(base)             ((base) + (0x00E0))

/* �Ĵ���˵����һ��ģ��ʱ��ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_WCH_CH_CLK_EN_UNION */
#define SOC_DSS_WCH_CH_CLK_EN_ADDR(base)              ((base) + (0x00E4))

/* �Ĵ���˵����ͼ���С
   λ����UNION�ṹ:  SOC_DSS_WCH_DFC_DISP_SIZE_UNION */
#define SOC_DSS_WCH_DFC_DISP_SIZE_ADDR(base)          ((base) + (0x0100))

/* �Ĵ���˵�����������������
   λ����UNION�ṹ:  SOC_DSS_WCH_DFC_PIX_IN_NUM_UNION */
#define SOC_DSS_WCH_DFC_PIX_IN_NUM_ADDR(base)         ((base) + (0x0104))

/* �Ĵ���˵����͸��������
   λ����UNION�ṹ:  SOC_DSS_WCH_DFC_GLB_ALPHA_UNION */
#define SOC_DSS_WCH_DFC_GLB_ALPHA_ADDR(base)          ((base) + (0x0108))

/* �Ĵ���˵������ʾ��ʽ
   λ����UNION�ṹ:  SOC_DSS_WCH_DFC_DISP_FMT_UNION */
#define SOC_DSS_WCH_DFC_DISP_FMT_ADDR(base)           ((base) + (0x010C))

/* �Ĵ���˵����ˮƽ�ü�����
   λ����UNION�ṹ:  SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_UNION */
#define SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_ADDR(base)       ((base) + (0x0110))

/* �Ĵ���˵������ֱ�ü�����
   λ����UNION�ṹ:  SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_UNION */
#define SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_ADDR(base)       ((base) + (0x0114))

/* �Ĵ���˵����ͼ�����ʹ��
   λ����UNION�ṹ:  SOC_DSS_WCH_DFC_CTL_CLIP_EN_UNION */
#define SOC_DSS_WCH_DFC_CTL_CLIP_EN_ADDR(base)        ((base) + (0x0118))

/* �Ĵ���˵����ʱ���ſ�ģʽ
   λ����UNION�ṹ:  SOC_DSS_WCH_DFC_ICG_MODULE_UNION */
#define SOC_DSS_WCH_DFC_ICG_MODULE_ADDR(base)         ((base) + (0x011C))

/* �Ĵ���˵������������ʹ��
   λ����UNION�ṹ:  SOC_DSS_WCH_DFC_DITHER_ENABLE_UNION */
#define SOC_DSS_WCH_DFC_DITHER_ENABLE_ADDR(base)      ((base) + (0x0120))

/* �Ĵ���˵�����������ؿ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DFC_PADDING_CTL_UNION */
#define SOC_DSS_WCH_DFC_PADDING_CTL_ADDR(base)        ((base) + (0x0124))

/* �Ĵ���˵����ɫ�ʿռ�ת������ֱ�������Ĵ�����Ϊ��ʱ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_CSC_IDC_UNION */
#define SOC_DSS_WCH_CSC_IDC_ADDR(base)                ((base) + (0x0500))

/* �Ĵ���˵����ɫ�ʿռ�ת�����ֱ�������Ĵ�����Ϊ��ʱ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_CSC_ODC_UNION */
#define SOC_DSS_WCH_CSC_ODC_ADDR(base)                ((base) + (0x0504))

/* �Ĵ���˵����ɫ�ʿռ�ת������0��Ϊ��ʱ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_CSC_P0_UNION */
#define SOC_DSS_WCH_CSC_P0_ADDR(base)                 ((base) + (0x0508))

/* �Ĵ���˵����ɫ�ʿռ�ת������0��Ϊ��ʱ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_CSC_P1_UNION */
#define SOC_DSS_WCH_CSC_P1_ADDR(base)                 ((base) + (0x050C))

/* �Ĵ���˵����ɫ�ʿռ�ת������0��Ϊ��ʱ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_CSC_P2_UNION */
#define SOC_DSS_WCH_CSC_P2_ADDR(base)                 ((base) + (0x0510))

/* �Ĵ���˵����ɫ�ʿռ�ת������0��Ϊ��ʱ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_CSC_P3_UNION */
#define SOC_DSS_WCH_CSC_P3_ADDR(base)                 ((base) + (0x0514))

/* �Ĵ���˵����ɫ�ʿռ�ת������0��Ϊ��ʱ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_CSC_P4_UNION */
#define SOC_DSS_WCH_CSC_P4_ADDR(base)                 ((base) + (0x0518))

/* �Ĵ���˵����ʱ���ſ�ģʽ
   λ����UNION�ṹ:  SOC_DSS_WCH_CSC_ICG_MODULE_UNION */
#define SOC_DSS_WCH_CSC_ICG_MODULE_ADDR(base)         ((base) + (0x051C))

/* �Ĵ���˵������ת�׿������Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_FIRST_LNS_UNION */
#define SOC_DSS_WCH_ROT_FIRST_LNS_ADDR(base)          ((base) + (0x0530))

/* �Ĵ���˵����ROT״̬
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_STATE_UNION */
#define SOC_DSS_WCH_ROT_STATE_ADDR(base)              ((base) + (0x0534))

/* �Ĵ���˵����ROT �͹��Ŀ���
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_MEM_CTRL_UNION */
#define SOC_DSS_WCH_ROT_MEM_CTRL_ADDR(base)           ((base) + (0x0538))

/* �Ĵ���˵����ͼ���С
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_SIZE_UNION */
#define SOC_DSS_WCH_ROT_SIZE_ADDR(base)               ((base) + (0x053C))

/* �Ĵ���˵����ROT ����ѡ��Ĵ���0��
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_CPU_CTL0_UNION */
#define SOC_DSS_WCH_ROT_CPU_CTL0_ADDR(base)           ((base) + (0x0540))

/* �Ĵ���˵����ROT ���������Ĵ���0��
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_CPU_START0_UNION */
#define SOC_DSS_WCH_ROT_CPU_START0_ADDR(base)         ((base) + (0x0544))

/* �Ĵ���˵����ROT ��ַ�Ĵ���0��
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_CPU_ADDR0_UNION */
#define SOC_DSS_WCH_ROT_CPU_ADDR0_ADDR(base)          ((base) + (0x0548))

/* �Ĵ���˵����ROT �����ݶ˿ڼĴ���0��
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_CPU_RDATA0_UNION */
#define SOC_DSS_WCH_ROT_CPU_RDATA0_ADDR(base)         ((base) + (0x054C))

/* �Ĵ���˵����ROT �����ݶ˿ڼĴ���1��
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_CPU_RDATA1_UNION */
#define SOC_DSS_WCH_ROT_CPU_RDATA1_ADDR(base)         ((base) + (0x0550))

/* �Ĵ���˵����ROT д���ݶ˿ڼĴ���0��
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_CPU_WDATA0_UNION */
#define SOC_DSS_WCH_ROT_CPU_WDATA0_ADDR(base)         ((base) + (0x0554))

/* �Ĵ���˵����ROT д���ݶ˿ڼĴ���1��
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_CPU_WDATA1_UNION */
#define SOC_DSS_WCH_ROT_CPU_WDATA1_ADDR(base)         ((base) + (0x0558))

/* �Ĵ���˵����ROT ����ѡ��Ĵ���1��
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_CPU_CTL1_UNION */
#define SOC_DSS_WCH_ROT_CPU_CTL1_ADDR(base)           ((base) + (0x055C))

/* �Ĵ���˵����ROT ���������Ĵ���1��
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_CPU_START1_UNION */
#define SOC_DSS_WCH_ROT_CPU_START1_ADDR(base)         ((base) + (0x0560))

/* �Ĵ���˵����ROT ��ַ�Ĵ���1��
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_CPU_ADDR1_UNION */
#define SOC_DSS_WCH_ROT_CPU_ADDR1_ADDR(base)          ((base) + (0x0564))

/* �Ĵ���˵����ROT �����ݶ˿ڼĴ���2��
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_CPU_RDATA2_UNION */
#define SOC_DSS_WCH_ROT_CPU_RDATA2_ADDR(base)         ((base) + (0x0568))

/* �Ĵ���˵����ROT �����ݶ˿ڼĴ���3��
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_CPU_RDATA3_UNION */
#define SOC_DSS_WCH_ROT_CPU_RDATA3_ADDR(base)         ((base) + (0x056C))

/* �Ĵ���˵����ROT д���ݶ˿ڼĴ�����
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_CPU_WDATA2_UNION */
#define SOC_DSS_WCH_ROT_CPU_WDATA2_ADDR(base)         ((base) + (0x0570))

/* �Ĵ���˵����ROT д���ݶ˿ڼĴ���3��
   λ����UNION�ṹ:  SOC_DSS_WCH_ROT_CPU_WDATA3_UNION */
#define SOC_DSS_WCH_ROT_CPU_WDATA3_ADDR(base)         ((base) + (0x0574))

/* �Ĵ���˵��������ѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_CH_DEBUG_SEL_UNION */
#define SOC_DSS_WCH_CH_DEBUG_SEL_ADDR(base)           ((base) + (0x600))

/* �Ĵ���˵����DMA_BUF���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_CTRL_UNION */
#define SOC_DSS_WCH_DMA_BUF_CTRL_ADDR(base)           ((base) + (0x0800))

/* �Ĵ���˵����DMA_BUF ����ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_CPU_CTL_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_CTL_ADDR(base)        ((base) + (0x0804))

/* �Ĵ���˵����DMA_BUF ���������Ĵ�����
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_CPU_START_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_START_ADDR(base)      ((base) + (0x0808))

/* �Ĵ���˵����DMA_BUF ��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_CPU_ADDR_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_ADDR_ADDR(base)       ((base) + (0x080C))

/* �Ĵ���˵����DMA_BUF �����ݶ˿ڼĴ���0��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_ADDR(base)     ((base) + (0x0810))

/* �Ĵ���˵����DMA_BUF �����ݶ˿ڼĴ���1��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_ADDR(base)     ((base) + (0x814))

/* �Ĵ���˵����DMA_BUF �����ݶ˿ڼĴ���2��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_ADDR(base)     ((base) + (0x818))

/* �Ĵ���˵����DMA_BUF �����ݶ˿ڼĴ���3��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_ADDR(base)     ((base) + (0x81C))

/* �Ĵ���˵����DMA_BUF д���ݶ˿ڼĴ���0��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_ADDR(base)     ((base) + (0x820))

/* �Ĵ���˵����DMA_BUF д���ݶ˿ڼĴ���1��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_ADDR(base)     ((base) + (0x824))

/* �Ĵ���˵����DMA_BUF д���ݶ˿ڼĴ���2��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_ADDR(base)     ((base) + (0x828))

/* �Ĵ���˵����DMA_BUF д���ݶ˿ڼĴ���3��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_UNION */
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_ADDR(base)     ((base) + (0x82C))

/* �Ĵ���˵����MMU TLB �����ݶ˿ڼĴ���0��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_REQ_END_UNION */
#define SOC_DSS_WCH_DMA_REQ_END_ADDR(base)            ((base) + (0x830))

/* �Ĵ���˵����DMA_BUF ���ԼĴ���
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_DBGCFG_UNION */
#define SOC_DSS_WCH_DMA_BUF_DBGCFG_ADDR(base)         ((base) + (0x834))

/* �Ĵ���˵����DMA_BUF����ֻ���Ĵ���0
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_DBG0_UNION */
#define SOC_DSS_WCH_DMA_BUF_DBG0_ADDR(base)           ((base) + (0x838))

/* �Ĵ���˵����DMA_BUF����ֻ���Ĵ���1
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_DBG1_UNION */
#define SOC_DSS_WCH_DMA_BUF_DBG1_ADDR(base)           ((base) + (0x83C))

/* �Ĵ���˵����DMA_BUF����ֻ���Ĵ���0
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_DBG2_UNION */
#define SOC_DSS_WCH_DMA_BUF_DBG2_ADDR(base)           ((base) + (0x840))

/* �Ĵ���˵����DMA_BUF����ֻ���Ĵ���1
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_DBG3_UNION */
#define SOC_DSS_WCH_DMA_BUF_DBG3_ADDR(base)           ((base) + (0x844))

/* �Ĵ���˵����DMA_BUF����ֻ���Ĵ���0
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_DBG4_UNION */
#define SOC_DSS_WCH_DMA_BUF_DBG4_ADDR(base)           ((base) + (0x848))

/* �Ĵ���˵����DMA_BUF����ֻ���Ĵ���1
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_DBG5_UNION */
#define SOC_DSS_WCH_DMA_BUF_DBG5_ADDR(base)           ((base) + (0x84C))

/* �Ĵ���˵����ͼ���С
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_SIZE_UNION */
#define SOC_DSS_WCH_DMA_BUF_SIZE_ADDR(base)           ((base) + (0x850))

/* �Ĵ���˵����DMA_BUF SRAM���ƼĴ�����TP��
   λ����UNION�ṹ:  SOC_DSS_WCH_DMA_BUF_MEM_CTRL_UNION */
#define SOC_DSS_WCH_DMA_BUF_MEM_CTRL_ADDR(base)       ((base) + (0x0854))

/* �Ĵ���˵����ͼ��16x16�����
   λ����UNION�ṹ:  SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_UNION */
#define SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_ADDR(base)    ((base) + (0x0900))

/* �Ĵ���˵����ͼ���ʽ
   λ����UNION�ṹ:  SOC_DSS_WCH_AFBCE_HREG_FORMAT_UNION */
#define SOC_DSS_WCH_AFBCE_HREG_FORMAT_ADDR(base)      ((base) + (0x0904))

/* �Ĵ���˵����ѹ��Header��ʼ��ַ��λ
   λ����UNION�ṹ:  SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_UNION */
#define SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_ADDR(base)  ((base) + (0x0908))

/* �Ĵ���˵����ѹ��Payload��ʼ��ַ��λ
   λ����UNION�ṹ:  SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_UNION */
#define SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_ADDR(base)  ((base) + (0x090C))

/* �Ĵ���˵��������ͼ��ߴ�
   λ����UNION�ṹ:  SOC_DSS_WCH_PICTURE_SIZE_UNION */
#define SOC_DSS_WCH_PICTURE_SIZE_ADDR(base)           ((base) + (0x0910))

/* �Ĵ���˵��������
   λ����UNION�ṹ:  SOC_DSS_WCH_AFBCE_CTL_UNION */
#define SOC_DSS_WCH_AFBCE_CTL_ADDR(base)              ((base) + (0x0914))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_WCH_HEADER_SRTIDE_UNION */
#define SOC_DSS_WCH_HEADER_SRTIDE_ADDR(base)          ((base) + (0x0918))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_WCH_PAYLOAD_STRIDE_UNION */
#define SOC_DSS_WCH_PAYLOAD_STRIDE_ADDR(base)         ((base) + (0x091C))

/* �Ĵ���˵����OUSTANDING CFG
   λ����UNION�ṹ:  SOC_DSS_WCH_ENC_OS_CFG_UNION */
#define SOC_DSS_WCH_ENC_OS_CFG_ADDR(base)             ((base) + (0x0920))

/* �Ĵ���˵����AFBCE SRAM���ƼĴ���
   λ����UNION�ṹ:  SOC_DSS_WCH_AFBCE_MEM_CTRL_UNION */
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_ADDR(base)         ((base) + (0x0924))

/* �Ĵ���˵����OUSTANDING CFG
   λ����UNION�ṹ:  SOC_DSS_WCH_AFBCE_QOS_CFG_UNION */
#define SOC_DSS_WCH_AFBCE_QOS_CFG_ADDR(base)          ((base) + (0x0928))

/* �Ĵ���˵�������������ˮ�߼Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_AFBCE_THRESHOLD_UNION */
#define SOC_DSS_WCH_AFBCE_THRESHOLD_ADDR(base)        ((base) + (0x092C))

/* �Ĵ���˵������ַ��֯ģʽ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_UNION */
#define SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_ADDR(base)    ((base) + (0x0930))

/* �Ĵ���˵����ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
   λ����UNION�ṹ:  SOC_DSS_WCH_REG_DEFAULT_UNION */
#define SOC_DSS_WCH_REG_DEFAULT_ADDR(base)            ((base) + (0x0A00))





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
                     (1/1) reg_WCH
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_OFT_X0_UNION
 �ṹ˵��  : DMA_OFT_X0 �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: RDMA����ͼ���WDMAд��ͼ�����Ͻ������buffer��ˮƽƫ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_oft_x0 : 12; /* bit[0-11] : RDMA����ͼ���WDMAд��ͼ����Yƽ������Ͻ�x���꣨������Ϊ�����buffer�����Ͻǵ����꣬1����128bit��(0,0)�����Ӧ��buffer�����Ͻǣ���
                                                      dma_oft_x0_y = dma_oft_x0;
                                                      dma_oft_x0_u/v = planar?dma_oft_x0:dma_oft_x0/2;
                                                      (
                                                      eg.�����ͼ��ߴ�Ϊ320*480���Ҷ���ͼ�����Ͻ���buffer�����Ͻǡ���������������Ϊp0 = 0���յ������Ϊp1 = 319����
                                                       1. ���������ꡱ�򡰶������ꡱ�ο����㹫ʽ��
                                                       RGB32bpp�� x0 = int[p0/4] = 0 ��
                                                       x1 = int[p1/4] = 79��
                                                       YUV422pkt��x0 = int[p0/8] = 0 ��
                                                       x1 = int[p1/8] = 39��
                                                       2. ���������ꡱ��á�ͼ�����ؿ�ȡ���
                                                       RGB32bpp��ʽ�£� pix_wid=(x1-x0+1)*4��
                                                       YUV422pkt��ʽ�£�pix_wid=(x1-x0+1)*8��
                                                      )
                                                      Լ��������
                                                      1. ��x1-x0����[0,2047]
                                                      ע:buffer�����ϽǼ�Ϊ����ԭ��,buffer����ʼ�洢��ַ��Լ��Ϊ:
                                                       Linear��ʽ128bit���룬����С���õ�λΪ 1��
                                                       Tile��ʽ 4KByte���룬����С���õ�λ��4KByte/128bit = 256)��
                                                      2. ��planar 420��planar 422��ʽʱ��y������dma_oft_x0�������Ϊż����dma_oft_x1�������Ϊ����������x1-x0+1Ϊż���� */
        unsigned int  reserved   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_OFT_X0_UNION;
#endif
#define SOC_DSS_WCH_DMA_OFT_X0_dma_oft_x0_START  (0)
#define SOC_DSS_WCH_DMA_OFT_X0_dma_oft_x0_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_OFT_Y0_UNION
 �ṹ˵��  : DMA_OFT_Y0 �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: RDMA����ͼ���WDMAд��ͼ�����Ͻ������buffer�Ĵ�ֱƫ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_oft_y0 : 16; /* bit[0-15] : RDMA����ͼ���WDMAд��ͼ����Yƽ������Ͻ�y���꣨������Ϊ�����buffer�����Ͻǵ����꣬(0,0)�����Ӧ��buffer�����Ͻǣ�
                                                      dma_oft_y0_y = dma_oft_y0;
                                                      dma_oft_y0_u/v = 420?dma_oft_y0:dma_oft_y0/2;
                                                      (
                                                      eg.�����ͼ��ߴ�Ϊ320*480���Ҷ���ͼ�����Ͻ���buffer�����Ͻǡ���y0=0,y1=479
                                                      )
                                                      Լ��������
                                                      1. ����תʱ��y1-y0����[0,8191]��
                                                       ������תʱ��y1-y0����[0,2559]��
                                                       ������תʱ��y1-y0����[0,259]��
                                                      2. ��semi planar 420/planar 420��ʽʱ��y������dma_oft_y0�������Ϊż����dma_oft_y1�������Ϊ����������y1-y0+1Ϊż���� */
        unsigned int  reserved   : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_OFT_Y0_UNION;
#endif
#define SOC_DSS_WCH_DMA_OFT_Y0_dma_oft_y0_START  (0)
#define SOC_DSS_WCH_DMA_OFT_Y0_dma_oft_y0_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_OFT_X1_UNION
 �ṹ˵��  : DMA_OFT_X1 �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͼ�����½������buffer��ˮƽƫ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_oft_x1 : 12; /* bit[0-11] : Yƽ��RDMA����ͼ���WDMAд��ͼ�����½�x���꣨������Ϊ�����buffer�����Ͻǵ����꣬1����128bit��(0,0)�����Ӧ��buffer�����Ͻǣ���
                                                      dma_oft_x1_y = dma_oft_x1;
                                                      dma_oft_x1_u/v = planar?dma_oft_x1:dma_oft_x1/2;
                                                      (
                                                      eg.�����ͼ��ߴ�Ϊ320*480���Ҷ���ͼ�����Ͻ���buffer�����Ͻǡ���������������Ϊp0 = 0���յ������Ϊp1 = 319����
                                                       1. ���������ꡱ�򡰶������ꡱ�ο����㹫ʽ��
                                                       RGB32bpp�� x0 = int[p0/4] = 0 ��
                                                       x1 = int[p1/4] = 79��
                                                       YUV422pkt��x0 = int[p0/8] = 0 ��
                                                       x1 = int[p1/8] = 39��
                                                       2. ���������ꡱ��á�ͼ�����ؿ�ȡ���
                                                       RGB32bpp��ʽ�£� pix_wid=(x1-x0+1)*4��
                                                       YUV422pkt��ʽ�£�pix_wid=(x1-x0+1)*8��
                                                      )
                                                      Լ��������
                                                      1. ��x1-x0����[0,2047]
                                                      ע:buffer�����ϽǼ�Ϊ����ԭ��,buffer����ʼ�洢��ַ��Լ��Ϊ:
                                                       Linear��ʽ128bit���룬����С���õ�λΪ 1��
                                                       Tile��ʽ 4KByte���룬����С���õ�λ��4KByte/128bit = 256)��
                                                      2. ��planar 420��planar 422��ʽʱ��y������dma_oft_x0�������Ϊż����dma_oft_x1�������Ϊ����������x1-x0+1Ϊż���� */
        unsigned int  reserved   : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_OFT_X1_UNION;
#endif
#define SOC_DSS_WCH_DMA_OFT_X1_dma_oft_x1_START  (0)
#define SOC_DSS_WCH_DMA_OFT_X1_dma_oft_x1_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_OFT_Y1_UNION
 �ṹ˵��  : DMA_OFT_Y1 �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͼ�����½������buffer�Ĵ�ֱƫ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_oft_y1 : 16; /* bit[0-15] : RDMA����ͼ���WDMAд��ͼ����Yƽ������Ͻ�y���꣨������Ϊ�����buffer�����Ͻǵ����꣬(0,0)�����Ӧ��buffer�����Ͻǣ�
                                                      dma_oft_y1_y = dma_oft_y1;
                                                      dma_oft_y1_u/v = 420?dma_oft_y1:dma_oft_y1/2;
                                                      (
                                                      eg.�����ͼ��ߴ�Ϊ320*480���Ҷ���ͼ�����Ͻ���buffer�����Ͻǡ���y0=0,y1=479
                                                      )
                                                      Լ��������
                                                      1. ����תʱ��y1-y0����[0,8191]��
                                                       ������תʱ��y1-y0����[0,2559]��
                                                       ������תʱ��y1-y0����[0,259]��
                                                      2. ��semi planar 420/planar 420��ʽʱ��y������dma_oft_y0�������Ϊż����dma_oft_y1�������Ϊ����������y1-y0+1Ϊż���� */
        unsigned int  reserved   : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_OFT_Y1_UNION;
#endif
#define SOC_DSS_WCH_DMA_OFT_Y1_dma_oft_y1_START  (0)
#define SOC_DSS_WCH_DMA_OFT_Y1_dma_oft_y1_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_MASK0_UNION
 �ṹ˵��  : DMA_MASK0 �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: RDMA��Mask���Ͻ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_mask_y0 : 16; /* bit[0-15] : RDMA��mask�����������Ͻ�y���꣨�����buffer�����Ͻǣ�����Ϊ��λ��
                                                       RDMA����ͼ���Yƽ���mask������������Ͻ��ڴ�ֱ�������������
                                                       ע��
                                                       1��WDMA����ע����
                                                       Լ������semi planar 420/planar 420��ʽʱ��y������dma_oft_y0�������Ϊż����dma_oft_y1�������Ϊ����������y1-y0+1Ϊż���� */
        unsigned int  dma_mask_x0 : 12; /* bit[16-27]: RDMA��mask�����������Ͻ�x���꣨�����buffer�����Ͻǣ�1����128bit����(0,0)�����Ӧ��buffer�����Ͻǣ�
                                                       ���128bitȡ������.
                                                       ��תǰԭʼͼ���Mask�������Ͻǡ�
                                                       RDMA����ͼ���Yƽ���mask������������Ͻ���ˮƽ�������������
                                                       ע��
                                                       1��WDMA����ע����
                                                       ע1�����õ�Mask��������ͼ����
                                                       ע2��Mask���������С������������
                                                       
                                                       Լ������planar 420��planar 422��ʽʱ��y������dma_mask_x0�������Ϊż����dma_mask_x1�������Ϊ����������x1-x0+1Ϊż���� */
        unsigned int  reserved    : 4;  /* bit[28-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_MASK0_UNION;
#endif
#define SOC_DSS_WCH_DMA_MASK0_dma_mask_y0_START  (0)
#define SOC_DSS_WCH_DMA_MASK0_dma_mask_y0_END    (15)
#define SOC_DSS_WCH_DMA_MASK0_dma_mask_x0_START  (16)
#define SOC_DSS_WCH_DMA_MASK0_dma_mask_x0_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_MASK1_UNION
 �ṹ˵��  : DMA_MASK1 �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: RDMA��Mask���½�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_mask_y1 : 16; /* bit[0-15] : RDMA��mask�����������½�y���꣨�����buffer�����Ͻǣ�����Ϊ��λ��
                                                       ע��
                                                       1��WDMA����ע����
                                                       Լ������semi planar 420/planar 420��ʽʱ��y������dma_oft_y0�������Ϊż����dma_oft_y1�������Ϊ����������y1-y0+1Ϊż���� */
        unsigned int  dma_mask_x1 : 12; /* bit[16-27]: RDMA��mask�����������½�x���꣨�����buffer�����Ͻǣ�1����128bit��
                                                       ��С��128bitȡ������.
                                                       ��תǰԭʼͼ���Mask�������½ǡ�
                                                       ע��
                                                       1��WDMA����ע����
                                                       ע1�����õ�Mask��������ͼ����
                                                       ע2��Mask���������С������������
                                                       
                                                       Լ������planar 420��planar 422��ʽʱ��y������dma_mask_x0�������Ϊż����dma_mask_x1�������Ϊ����������x1-x0+1Ϊż���� */
        unsigned int  reserved    : 4;  /* bit[28-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_MASK1_UNION;
#endif
#define SOC_DSS_WCH_DMA_MASK1_dma_mask_y1_START  (0)
#define SOC_DSS_WCH_DMA_MASK1_dma_mask_y1_END    (15)
#define SOC_DSS_WCH_DMA_MASK1_dma_mask_x1_START  (16)
#define SOC_DSS_WCH_DMA_MASK1_dma_mask_x1_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_UNION
 �ṹ˵��  : DMA_STRETCH_SIZE_VRT �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: Yƽ��RDMA��ֱStretch֮��ĸ߶�-1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_stretch_size_vrt : 13; /* bit[0-12] : Yƽ��RDMA������߶�-1�������Ƿ�ʹ��stretch����Ҫ���øüĴ�������ʽ����
                                                                dma_stretch_size_vrt=
                                                                dma_stretch_en?(����ȡ��((dma_oft_y1-dma_oft_y0+1)/dma_line_skip_step)-1)
                                                                 :(dma_oft_y1 - dma_oft_y0��
                                                                ע��
                                                                1��WDMA����ע���� */
        unsigned int  dma_line_skip_step   : 6;  /* bit[13-18]: Yƽ�洹ֱ��������6λ������ʽ��
                                                                ע��
                                                                6'd0. 0Ϊ�Ƿ�ֵ��
                                                                6'd1. ����Ϊ1ʱ����������y��y+1��y+1*2��y+1*3��
                                                                6'd2. ����Ϊ2ʱ����������y��y+2��y+2*2��y+2*3��
                                                                ... . ��������
                                                                Լ������semi planar 420/planar 420��ʽʱ��y������dma_line_skip_step������Ϊż����
                                                                
                                                                dma_line_skip_step_u/v = 420?dma_line_skip_step/2:dma_line_skip_step
                                                                ע��
                                                                1��WDMA����ע���� */
        unsigned int  reserved             : 13; /* bit[19-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_UNION;
#endif
#define SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_dma_stretch_size_vrt_START  (0)
#define SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_dma_stretch_size_vrt_END    (12)
#define SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_dma_line_skip_step_START    (13)
#define SOC_DSS_WCH_DMA_STRETCH_SIZE_VRT_dma_line_skip_step_END      (18)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_CTRL_UNION
 �ṹ˵��  : DMA_CTRL �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: RDMA����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_page_8k         : 1;  /* bit[0]    : �洢�ռ�ҳ��С��
                                                               0: 4K Byte����ͨ��32bit DDR��
                                                               1: 8K byte (˫ͨ��32bit DDR�� */
        unsigned int  dma_tile_en         : 1;  /* bit[1]    : RDMA����ͼ���WDMA����洢��ʽ��
                                                               0��Linear��ʽ
                                                               1��Tile��ʽ */
        unsigned int  reserved_0          : 1;  /* bit[2]    : ���� */
        unsigned int  dma_pix_fmt         : 5;  /* bit[3-7]  : RDMA����ͼ���WDMAд��ͼ������ظ�ʽ��
                                                               0000��RGB565
                                                               0001��ARGB4444
                                                               0010��XRGB4444
                                                               0011��ARGB1555
                                                               0100��XRGB1555
                                                               0101��ARGB8888
                                                               0110��XRGB8888
                                                               0111��reserved
                                                               1000��YUYV Packet
                                                               1001��YUV420 Semi Planar HP
                                                               1010��YUV420 Planar HP
                                                               1011��YUV422 Semi Planar HP
                                                               1100��YUV422 Planar HP
                                                               1101��AYUV444
                                                               others��illegal reserved 
                                                               ע��
                                                               1��planar��ʽֻ������RDMA
                                                               
                                                               RDMA���������ظ�ʽ��
                                                               0_0000�� RGB16bpp
                                                               0_0001�� RGB32bpp��YUV32bpp
                                                               0_0010�� YUV 422 Packet
                                                               0_0011�� YUV 422 Semi-Planar HP Y
                                                               0_0100�� YUV 422 Semi-Planar HP UV
                                                               0_0101�� YUV 422 Semi-Planar VP Y (��֧��) 
                                                               0_0110�� YUV 422 Semi-Planar VP UV(��֧��) 
                                                               0_0111�� YUV 420 Semi-Planar Y
                                                               0_1000�� YUV 420 Semi-Planar UV
                                                               0_1001�� YUV 422 Planar HP Y
                                                               0_1010�� YUV 422 Planar HP U
                                                               0_1011�� YUV 422 Planar HP V
                                                               0_1100�� YUV 422 Planar VP Y(��֧��) 
                                                               0_1101�� YUV 422 Planar VP U(��֧��) 
                                                               0_1110�� YUV 422 Planar VP V(��֧��) 
                                                               0_1111�� YUV 420 Planar Y
                                                               1_0000�� YUV 420 Planar U
                                                               1_0001�� YUV 420 Planar V
                                                               ע��ѹ������£��̶�����Ϊ0_0001��RGB32bpp */
        unsigned int  dma_va_en           : 1;  /* bit[8]    : RDMA��WDMAʹ�������ַʹ�ܣ�
                                                               0��RDMAֱ��ʹ�������ַ��
                                                               1��RDMAʹ�������ַ����ͨ��MMUת���������ַ */
        unsigned int  dma_mirror_hrz_en   : 1;  /* bit[9]    : ˮƽ����ʹ�ܱ�־��
                                                               0������
                                                               1��ʹ�� */
        unsigned int  dma_mirror_vrt_en   : 1;  /* bit[10]   : ��ֱ����ʹ�ܱ�־��
                                                               0������
                                                               1��ʹ�� */
        unsigned int  dma_rot             : 1;  /* bit[11]   : rotģ��ʹ�ܱ�־��
                                                               0���ر�
                                                               1����
                                                               ע��
                                                               1������WDMA������ֱ����ʹ����rotģ��ʹ��ͬʱ��ʱ����Ӧ˳ʱ����ת270�㣻��ˮƽ����ʹ����rotģ��ʹ��ͬʱ��ʱ����Ӧ˳ʱ����ת90��
                                                               
                                                               �Ӿ�Ч����������õ�������Ӧ��ϵ���£�
                                                               �Ӿ�Ч������ת�޾��� : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b000;
                                                               �Ӿ�Ч����ֱ���� : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b010;
                                                               �Ӿ�Ч��ˮƽ���� : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b001;
                                                               �Ӿ�Ч��˳ʱ����ת90�� : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b101;
                                                               �Ӿ�Ч��˳ʱ����ת180�� : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b011;
                                                               �Ӿ�Ч��˳ʱ����ת270�� : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b110;
                                                               �Ӿ�Ч��˳ʱ����ת90����ˮƽ���� : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b100;
                                                               �Ӿ�Ч��˳ʱ����ת270����ˮƽ���� ��
                                                               �Ӿ�Ч��˳ʱ����ת90���Ҵ�ֱ���� : {dma_rot,dma_mirror_vrt_en, dma_mirror_hrz_en}==3'b111;
                                                               
                                                               2��RDMA����ע���� */
        unsigned int  dma_stretch_en      : 1;  /* bit[12]   : stretchʹ�ܱ�־
                                                               0: ����
                                                               1: ʹ��
                                                               ע��
                                                               1��WDMA����ע���� */
        unsigned int  reserved_1          : 4;  /* bit[13-16]: ���� */
        unsigned int  dma_mask_en         : 1;  /* bit[17]   : RDMA��maskʹ�ܱ�־
                                                               0: ����
                                                               1: ʹ��
                                                               ע��
                                                               1��WDMA����ע���� */
        unsigned int  dma_phy_scrambl_4   : 1;  /* bit[18]   : ����reserve�ռ�Linear��ʽ�µ������ַ��֯��ʽ4��
                                                               [27:4],addr_4_3,[2:0]���н�֯������addr_4_3 = addr[4]^addr[3]
                                                               ע��
                                                               1��WDMA����ע���� */
        unsigned int  dma_phy_scrambl_3   : 1;  /* bit[19]   : ����reserve�ռ�Linear��ʽ�µ������ַ��֯��ʽ3��
                                                               28λ��ַ����[27:16],[11:4],[15:12],addr_4_3,[2:0]���н�֯������addr_4_3 = addr[4]^addr[3]
                                                               ע��
                                                               1��WDMA����ע���� */
        unsigned int  dma_phy_scrambl_2   : 1;  /* bit[20]   : ����reserve�ռ�Linear��ʽ�µ������ַ��֯��ʽ2��
                                                               28λ��ַ����[27:15],[10:4],[14:11],addr_4_3,[2:0]���н�֯������addr_4_3 = addr[4]^addr[3]
                                                               ע��
                                                               1��WDMA����ע���� */
        unsigned int  dma_phy_scrambl_1   : 1;  /* bit[21]   : ����reserve�ռ�Linear��ʽ�µ������ַ��֯��ʽ1:
                                                               28λ��ַ����[27:14],[9:4],[13:10],addr_4_3,[2:0]���н�֯������addr_4_3 = addr[4]^addr[3]
                                                               ע��
                                                               1��WDMA����ע���� */
        unsigned int  reserved_2          : 1;  /* bit[22]   : ���� */
        unsigned int  dma_cross_128       : 1;  /* bit[23]   : ��ά�ɲ� */
        unsigned int  dma_tile_128byte_en : 1;  /* bit[24]   : ��ά�ɲ� */
        unsigned int  reserved_3          : 1;  /* bit[25]   : ���� */
        unsigned int  reserved_4          : 6;  /* bit[26-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_CTRL_UNION;
#endif
#define SOC_DSS_WCH_DMA_CTRL_dma_page_8k_START          (0)
#define SOC_DSS_WCH_DMA_CTRL_dma_page_8k_END            (0)
#define SOC_DSS_WCH_DMA_CTRL_dma_tile_en_START          (1)
#define SOC_DSS_WCH_DMA_CTRL_dma_tile_en_END            (1)
#define SOC_DSS_WCH_DMA_CTRL_dma_pix_fmt_START          (3)
#define SOC_DSS_WCH_DMA_CTRL_dma_pix_fmt_END            (7)
#define SOC_DSS_WCH_DMA_CTRL_dma_va_en_START            (8)
#define SOC_DSS_WCH_DMA_CTRL_dma_va_en_END              (8)
#define SOC_DSS_WCH_DMA_CTRL_dma_mirror_hrz_en_START    (9)
#define SOC_DSS_WCH_DMA_CTRL_dma_mirror_hrz_en_END      (9)
#define SOC_DSS_WCH_DMA_CTRL_dma_mirror_vrt_en_START    (10)
#define SOC_DSS_WCH_DMA_CTRL_dma_mirror_vrt_en_END      (10)
#define SOC_DSS_WCH_DMA_CTRL_dma_rot_START              (11)
#define SOC_DSS_WCH_DMA_CTRL_dma_rot_END                (11)
#define SOC_DSS_WCH_DMA_CTRL_dma_stretch_en_START       (12)
#define SOC_DSS_WCH_DMA_CTRL_dma_stretch_en_END         (12)
#define SOC_DSS_WCH_DMA_CTRL_dma_mask_en_START          (17)
#define SOC_DSS_WCH_DMA_CTRL_dma_mask_en_END            (17)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_4_START    (18)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_4_END      (18)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_3_START    (19)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_3_END      (19)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_2_START    (20)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_2_END      (20)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_1_START    (21)
#define SOC_DSS_WCH_DMA_CTRL_dma_phy_scrambl_1_END      (21)
#define SOC_DSS_WCH_DMA_CTRL_dma_cross_128_START        (23)
#define SOC_DSS_WCH_DMA_CTRL_dma_cross_128_END          (23)
#define SOC_DSS_WCH_DMA_CTRL_dma_tile_128byte_en_START  (24)
#define SOC_DSS_WCH_DMA_CTRL_dma_tile_128byte_en_END    (24)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_TILE_SCRAM_UNION
 �ṹ˵��  : DMA_TILE_SCRAM �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: tile��ʽ��ַ��֯ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_tile_scrambling_en : 1;  /* bit[0]   : tileģʽ�µ�ַ��֯(����28bit��ַ����������4,3��֯)ʹ�ܣ�
                                                                 1��ʹ��
                                                                 0������ */
        unsigned int  reserved               : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_TILE_SCRAM_UNION;
#endif
#define SOC_DSS_WCH_DMA_TILE_SCRAM_dma_tile_scrambling_en_START  (0)
#define SOC_DSS_WCH_DMA_TILE_SCRAM_dma_tile_scrambling_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_PULSE_UNION
 �ṹ˵��  : DMA_PULSE �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 1PULSE�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_pulse : 1;  /* bit[0]   : ��ά�ɲ�Ĵ����������壺
                                                    1'b1�����¿�ά�ɲ�Ĵ���
                                                    1'b0�����ֿ�ά�ɲ�Ĵ��� */
        unsigned int  reserved  : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_PULSE_UNION;
#endif
#define SOC_DSS_WCH_DMA_PULSE_dma_pulse_START  (0)
#define SOC_DSS_WCH_DMA_PULSE_dma_pulse_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_RWCH_CFG0_UNION
 �ṹ˵��  : RWCH_CFG0 �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rwch_cfg0 : 32; /* bit[0-31]: ������
                                                    31: ����Ϊ1ʱ��ʵȡģ��ʱ���ſ�bypass
                                                    30: ����Ϊ1ʱ��Ԥȡģ��ʱ���ſ�bypass
                                                    29: ����Ϊ1ʱ������ģ��ʱ���ſ�bypass
                                                    1: ����Ϊ1ʱ��dma_inte_err�жϿ�ˢ��
                                                    0: ����Ϊ1ʱ��monitor ʱ���ſ�ǿ����Ч */
    } reg;
} SOC_DSS_WCH_RWCH_CFG0_UNION;
#endif
#define SOC_DSS_WCH_RWCH_CFG0_rwch_cfg0_START  (0)
#define SOC_DSS_WCH_RWCH_CFG0_rwch_cfg0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_FIFO_CLR_UNION
 �ṹ˵��  : DMA_FIFO_CLR �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: WDMA���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_fifo_clr : 1;  /* bit[0]   : ������ */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_FIFO_CLR_UNION;
#endif
#define SOC_DSS_WCH_DMA_FIFO_CLR_dma_fifo_clr_START  (0)
#define SOC_DSS_WCH_DMA_FIFO_CLR_dma_fifo_clr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_COUNTER_DGB_UNION
 �ṹ˵��  : DMA_COUNTER_DGB �Ĵ����ṹ���塣��ַƫ����:0x003C����ֵ:0x00000001�����:32
 �Ĵ���˵��: WDMA���counter_inc��counter_rst���ԼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_counter_en       : 1;  /* bit[0]    : WDMA���counter_inc����ʾһ������ȫд��dram����counter_rst����ʾһ֡����ȫд��dram����ʹ�ܱ�־��
                                                                0���ر�
                                                                1��ʹ��
                                                                ע��
                                                                1��RDMA����ע���� */
        unsigned int  dma_counter_inc_cnum : 4;  /* bit[1-4]  : WDMA���counter_inc����ʾһ������ȫд��dram�����ߵ�cycle����Ϊʵ��ֵ-1
                                                                ע��
                                                                1��RDMA����ע���� */
        unsigned int  dma_counter_rst_cnum : 4;  /* bit[5-8]  : WDMA���counter_rst����ʾһ֡����ȫд��dram�����ߵ�cycle����Ϊʵ��ֵ-1
                                                                ע��
                                                                1��RDMA����ע���� */
        unsigned int  wch_enc_slice_h      : 8;  /* bit[9-16] : WDMA���slice�߶ȣ�Ϊʵ��ֵ-1��ÿ�����üĴ���ָ�������������dma_counter_inc�����enc����ʾһ��slice�����ϡ�
                                                                ע��
                                                                1��RDMA����ע���� */
        unsigned int  wch_enc_space        : 4;  /* bit[17-20]: WDMA���counter_inc�ź�֮�����С��࣬��cycleΪ��λ��Ϊʵ��ֵ-1
                                                                ע��
                                                                1��RDMA����ע���� */
        unsigned int  reserved             : 11; /* bit[21-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_COUNTER_DGB_UNION;
#endif
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_en_START        (0)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_en_END          (0)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_inc_cnum_START  (1)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_inc_cnum_END    (4)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_rst_cnum_START  (5)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_dma_counter_rst_cnum_END    (8)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_wch_enc_slice_h_START       (9)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_wch_enc_slice_h_END         (16)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_wch_enc_space_START         (17)
#define SOC_DSS_WCH_DMA_COUNTER_DGB_wch_enc_space_END           (20)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_ROT_BURST4_UNION
 �ṹ˵��  : DMA_ROT_BURST4 �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000001�����:32
 �Ĵ���˵��: WDMA��תʱ��BURST Length�����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_rot_burst4 : 1;  /* bit[0]   : ������ */
        unsigned int  reserved       : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_ROT_BURST4_UNION;
#endif
#define SOC_DSS_WCH_DMA_ROT_BURST4_dma_rot_burst4_START  (0)
#define SOC_DSS_WCH_DMA_ROT_BURST4_dma_rot_burst4_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_RSV1_UNION
 �ṹ˵��  : DMA_RSV1 �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: WDMA����1�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_reload_rsv1_reg : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_RSV1_UNION;
#endif
#define SOC_DSS_WCH_DMA_RSV1_dma_reload_rsv1_reg_START  (0)
#define SOC_DSS_WCH_DMA_RSV1_dma_reload_rsv1_reg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_RSV2_UNION
 �ṹ˵��  : DMA_RSV2 �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: WDMA����2�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_rsv2_reg : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_RSV2_UNION;
#endif
#define SOC_DSS_WCH_DMA_RSV2_dma_rsv2_reg_START  (0)
#define SOC_DSS_WCH_DMA_RSV2_dma_rsv2_reg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_SW_MASK_EN_UNION
 �ṹ˵��  : DMA_SW_MASK_EN �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: WDMA���MASKʹ�ܼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_sw_mask_en : 1;  /* bit[0]   : WDMAд��ͼ�����׻���βʹ�����MASK����
                                                         0���ر�
                                                         1����
                                                         ע��
                                                         1��RDMA����ע���� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_SW_MASK_EN_UNION;
#endif
#define SOC_DSS_WCH_DMA_SW_MASK_EN_dma_sw_mask_en_START  (0)
#define SOC_DSS_WCH_DMA_SW_MASK_EN_dma_sw_mask_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_START_MASK0_UNION
 �ṹ˵��  : DMA_START_MASK0 �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: WDMA���ͼ������MASK0�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_start_mask0 : 32; /* bit[0-31]: WDMA���ͼ��������ʼMASK0
                                                          [15:0]���׵�һ��128bit���ݵ�mask
                                                          [31:16]���׵ڶ���128bit���ݵ�mask��������תʱ��Ч������תʱ������FFFF��
                                                          ע��
                                                          1��1��bit��Ӧ1��byte
                                                          2��ÿ��bit��1'b0��ʾmask��Ч��1'b1��ʾmask��Ч */
    } reg;
} SOC_DSS_WCH_DMA_START_MASK0_UNION;
#endif
#define SOC_DSS_WCH_DMA_START_MASK0_dma_start_mask0_START  (0)
#define SOC_DSS_WCH_DMA_START_MASK0_dma_start_mask0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_END_MASK0_UNION
 �ṹ˵��  : DMA_END_MASK0 �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: WDMA���ͼ����βMASK0�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_end_mask0 : 32; /* bit[0-31]: WDMA���ͼ����β��βMASK0
                                                        [31:16]��β������һ��128bit���ݵ�mask
                                                        [15:0]��β�����ڶ���128bit���ݵ�mask��������תʱ��Ч������תʱ������FFFF��
                                                        ע��
                                                        1��1��bit��Ӧ1��byte
                                                        2��ÿ��bit��1'b0��ʾmask��Ч��1'b1��ʾmask��Ч */
    } reg;
} SOC_DSS_WCH_DMA_END_MASK0_UNION;
#endif
#define SOC_DSS_WCH_DMA_END_MASK0_dma_end_mask0_START  (0)
#define SOC_DSS_WCH_DMA_END_MASK0_dma_end_mask0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_START_MASK1_UNION
 �ṹ˵��  : DMA_START_MASK1 �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: WDMA���ͼ������MASK1�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_start_mask1 : 32; /* bit[0-31]: WDMA���ͼ������MASK1
                                                          [15:0]���׵�����128bit���ݵ�mask��������תʱ��Ч������תʱ������FFFF��
                                                          [31:16]���׵��ĸ�128bit���ݵ�mask��������תʱ��Ч������תʱ������FFFF��
                                                          ע��
                                                          1��1��bit��Ӧ1��byte
                                                          2��ÿ��bit��1'b0��ʾmask��Ч��1'b1��ʾmask��Ч */
    } reg;
} SOC_DSS_WCH_DMA_START_MASK1_UNION;
#endif
#define SOC_DSS_WCH_DMA_START_MASK1_dma_start_mask1_START  (0)
#define SOC_DSS_WCH_DMA_START_MASK1_dma_start_mask1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_END_MASK1_UNION
 �ṹ˵��  : DMA_END_MASK1 �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: WDMA���ͼ����βMASK1�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_end_mask1 : 32; /* bit[0-31]: WDMA���ͼ����βMASK1
                                                        [31:16]��β����������128bit���ݵ�mask��������תʱ��Ч������תʱ������FFFF��
                                                        [15:0]��β�������ĸ�128bit���ݵ�mask��������תʱ��Ч������תʱ������FFFF��
                                                        ע��
                                                        1��1��bit��Ӧ1��byte
                                                        2��ÿ��bit��1'b0��ʾmask��Ч��1'b1��ʾmask��Ч */
    } reg;
} SOC_DSS_WCH_DMA_END_MASK1_UNION;
#endif
#define SOC_DSS_WCH_DMA_END_MASK1_dma_end_mask1_START  (0)
#define SOC_DSS_WCH_DMA_END_MASK1_dma_end_mask1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_DATA_ADDR0_UNION
 �ṹ˵��  : DMA_DATA_ADDR0 �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: RDMA����ͼ���WDMAд��ͼ���Yƽ��Data����ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_addr0 : 32; /* bit[0-31]: RDMA����ͼ���WDMAд��ͼ���Yƽ�����ڴ��еĴ洢��ʼ��Byte��ַ:
                                                    1. �޾������Ͻ�Byte��ַ
                                                    2. ˮƽ�������Ͻ�Byte��ַ
                                                    3. ��ֱ�����½�Byte��ַ
                                                    4. ˮƽ��ֱ�����½�Byte��ַ
                                                    
                                                    ע��RDMA��16Byte���룬��4bitʼ����0��WDMA��Լ�� */
    } reg;
} SOC_DSS_WCH_DMA_DATA_ADDR0_UNION;
#endif
#define SOC_DSS_WCH_DMA_DATA_ADDR0_dma_addr0_START  (0)
#define SOC_DSS_WCH_DMA_DATA_ADDR0_dma_addr0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_STRIDE0_UNION
 �ṹ˵��  : DMA_STRIDE0 �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000000�����:32
 �Ĵ���˵��: RDMA����ͼ���WDMAд��ͼ���ԭͼY�е�ַƫ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_stride0           : 13; /* bit[0-12] : RDMA����ͼ���WDMAд��ͼ���Yƽ���е�ַƫ�������е�ַƫ����Ϊͼ�����ڴ����������������ش洢��ַ֮���1����128bit��
                                                                 Linear��ʽStride��128bit���룬����С����ֵΪ1����ʾStrideΪ128bit��
                                                                 Tile��ʽStride��2���ݴη�Byte���룬��С256Byte������С����ֵ��256Byte/128bit = 16 = 10000�� */
        unsigned int  reserved_0            : 3;  /* bit[13-15]: ���� */
        unsigned int  dma_l2t_interleave_n0 : 4;  /* bit[16-19]: Video Tile: Linear VAתTile VAʱ��֯��λ�ţ�
                                                                 CPU Tile��Linear PAתTile PA ��֯��λ�ţ�
                                                                 ���㷽���ǣ�l2t_interleave_n=7 + log2(Stride/256)���Ϸ���Χ�ǣ�7~15��
                                                                 ����Ҫע����ǣ���Stride=256Byteʱ����ͼ���Ⱦ���һ��tile�Ŀ�ȣ���ʱn=7��Linear��ַ��Tile��ַʵ����һ�µģ�������Ҫת���� */
        unsigned int  reserved_1            : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_STRIDE0_UNION;
#endif
#define SOC_DSS_WCH_DMA_STRIDE0_dma_stride0_START            (0)
#define SOC_DSS_WCH_DMA_STRIDE0_dma_stride0_END              (12)
#define SOC_DSS_WCH_DMA_STRIDE0_dma_l2t_interleave_n0_START  (16)
#define SOC_DSS_WCH_DMA_STRIDE0_dma_l2t_interleave_n0_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_STRETCH_STRIDE0_UNION
 �ṹ˵��  : DMA_STRETCH_STRIDE0 �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000000�����:32
 �Ĵ���˵��: Yƽ������֮��Ķ�Ӧ��stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_stretch_stride0 : 19; /* bit[0-18] : Yƽ������֮���stride������dma_stretch_line_num0 * dma_stride0 */
        unsigned int  reserved            : 13; /* bit[19-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_STRETCH_STRIDE0_UNION;
#endif
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE0_dma_stretch_stride0_START  (0)
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE0_dma_stretch_stride0_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_DATA_NUM0_UNION
 �ṹ˵��  : DMA_DATA_NUM0 �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: RDMA��WDMA���ͼ��Yƽ�����128bit���ݵĸ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_data_num0 : 30; /* bit[0-29] : RDMA����ͼ���WDMAд��ͼ��Yƽ�����128bit���ݵĸ��������㹫ʽ���£�
                                                         1.�ڷ�yuv_semi/planar_420ʱ��
                                                         data_num = strech?( (stretch_size_vrt+1)*(oftx1-oftx0+1) ) :((oftx1-oftx0+1)*(ofty1-ofty0+1))
                                                         2.��yuv_semi/planar_420 u/vʱ����������ʽ�ٳ���2������
                                                         data_num = strech?( (stretch_size_vrt+1)*(oftx1-oftx0+1)*2) :((oftx1-oftx0+1)*(ofty1-ofty0+1)*2)
                                                         ע��
                                                         1. RDMA������ */
        unsigned int  reserved      : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_DATA_NUM0_UNION;
#endif
#define SOC_DSS_WCH_DMA_DATA_NUM0_dma_data_num0_START  (0)
#define SOC_DSS_WCH_DMA_DATA_NUM0_dma_data_num0_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_TEST0_UNION
 �ṹ˵��  : DMA_TEST0 �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test0_y : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_TEST0_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST0_dma_test0_y_START  (0)
#define SOC_DSS_WCH_DMA_TEST0_dma_test0_y_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_TEST1_UNION
 �ṹ˵��  : DMA_TEST1 �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test1_y : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_TEST1_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST1_dma_test1_y_START  (0)
#define SOC_DSS_WCH_DMA_TEST1_dma_test1_y_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_TEST3_UNION
 �ṹ˵��  : DMA_TEST3 �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test3_y : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_TEST3_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST3_dma_test3_y_START  (0)
#define SOC_DSS_WCH_DMA_TEST3_dma_test3_y_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_TEST4_UNION
 �ṹ˵��  : DMA_TEST4 �Ĵ����ṹ���塣��ַƫ����:0x007C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test4_y : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_TEST4_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST4_dma_test4_y_START  (0)
#define SOC_DSS_WCH_DMA_TEST4_dma_test4_y_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_STATUS_Y_UNION
 �ṹ˵��  : DMA_STATUS_Y �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: ״̬�ϱ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_status_y : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_STATUS_Y_UNION;
#endif
#define SOC_DSS_WCH_DMA_STATUS_Y_dma_status_y_START  (0)
#define SOC_DSS_WCH_DMA_STATUS_Y_dma_status_y_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_DATA_ADDR1_UNION
 �ṹ˵��  : DMA_DATA_ADDR1 �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: RDMA����ͼ���WDMAд��ͼ���Uƽ��Data����ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_addr1 : 32; /* bit[0-31]: RDMA����ͼ���WDMAд��ͼ���Uƽ�����ڴ��еĴ洢��ʼ��Byte��ַ:
                                                    1. �޾������Ͻ�Byte��ַ
                                                    2. ˮƽ�������Ͻ�Byte��ַ
                                                    3. ��ֱ�����½�Byte��ַ
                                                    4. ˮƽ��ֱ�����½�Byte��ַ
                                                    
                                                    ע��RDMA��16Byte���룬��4bitʼ����0��WDMA��Լ�� */
    } reg;
} SOC_DSS_WCH_DMA_DATA_ADDR1_UNION;
#endif
#define SOC_DSS_WCH_DMA_DATA_ADDR1_dma_addr1_START  (0)
#define SOC_DSS_WCH_DMA_DATA_ADDR1_dma_addr1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_STRIDE1_UNION
 �ṹ˵��  : DMA_STRIDE1 �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: RDMA����ͼ���WDMAд��ͼ���ԭͼUƽ���е�ַƫ�ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_stride1           : 13; /* bit[0-12] : RDMA����ͼ���WDMAд��ͼ���Uƽ���е�ַƫ�������е�ַƫ����Ϊͼ�����ڴ����������������ش洢��ַ֮���1����128bit��
                                                                 Linear��ʽStride��128bit���룬����С����ֵΪ1����ʾStrideΪ128bit��
                                                                 Tile��ʽStride��2���ݴη�Byte���룬��С256Byte������С����ֵ��256Byte/128bit = 16 = 10000��
                                                                 ע��
                                                                 1����ƽ���ʽ����ע���� */
        unsigned int  reserved_0            : 3;  /* bit[13-15]: ���� */
        unsigned int  dma_l2t_interleave_n1 : 4;  /* bit[16-19]: Video Tile: Linear VAתTile VAʱ��֯��λ�ţ�
                                                                 CPU Tile��Linear PAתTile PA ��֯��λ�ţ�
                                                                 ���㷽���ǣ�l2t_interleave_n=7 + log2(Stride/256)���Ϸ���Χ�ǣ�7~15��
                                                                 ����Ҫע����ǣ���Stride=256Byteʱ����ͼ���Ⱦ���һ��tile�Ŀ�ȣ���ʱn=7��Linear��ַ��Tile��ַʵ����һ�µģ�������Ҫת���� */
        unsigned int  reserved_1            : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_STRIDE1_UNION;
#endif
#define SOC_DSS_WCH_DMA_STRIDE1_dma_stride1_START            (0)
#define SOC_DSS_WCH_DMA_STRIDE1_dma_stride1_END              (12)
#define SOC_DSS_WCH_DMA_STRIDE1_dma_l2t_interleave_n1_START  (16)
#define SOC_DSS_WCH_DMA_STRIDE1_dma_l2t_interleave_n1_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_STRETCH_STRIDE1_UNION
 �ṹ˵��  : DMA_STRETCH_STRIDE1 �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Uƽ������֮��Ķ�Ӧ��stride
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_stretch_stride1 : 19; /* bit[0-18] : Uƽ������֮���Ӧ��stride */
        unsigned int  reserved            : 13; /* bit[19-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_STRETCH_STRIDE1_UNION;
#endif
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE1_dma_stretch_stride1_START  (0)
#define SOC_DSS_WCH_DMA_STRETCH_STRIDE1_dma_stretch_stride1_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_DATA_NUM1_UNION
 �ṹ˵��  : DMA_DATA_NUM1 �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00000000�����:32
 �Ĵ���˵��: RDMA��WDMA���ͼ��Uƽ�����128bit���ݵĸ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_data_num1 : 30; /* bit[0-29] : RDMA����ͼ���WDMAд��ͼ��Uƽ�����128bit���ݵĸ��������㹫ʽ���£�
                                                         1.�ڷ�yuv_semi/planar_420ʱ��
                                                         data_num = strech?( (stretch_size_vrt+1)*(oftx1-oftx0+1) ) :((oftx1-oftx0+1)*(ofty1-ofty0+1))
                                                         2.��yuv_semi/planar_420 u/vʱ����������ʽ�ٳ���2������
                                                         data_num = strech?( (stretch_size_vrt+1)*(oftx1-oftx0+1)*2) :((oftx1-oftx0+1)*(ofty1-ofty0+1)*2)
                                                         ע��
                                                         1. RDMA������ */
        unsigned int  reserved      : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_DATA_NUM1_UNION;
#endif
#define SOC_DSS_WCH_DMA_DATA_NUM1_dma_data_num1_START  (0)
#define SOC_DSS_WCH_DMA_DATA_NUM1_dma_data_num1_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_TEST0_U_UNION
 �ṹ˵��  : DMA_TEST0_U �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test0_u : 32; /* bit[0-31]: ��ά�ɲ�Ĵ�������dma_pulse��Чʱ���£���
                                                      [31:4]: real.dma_addr;
                                                       [3:0]: real.dma_arlen; */
    } reg;
} SOC_DSS_WCH_DMA_TEST0_U_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST0_U_dma_test0_u_START  (0)
#define SOC_DSS_WCH_DMA_TEST0_U_dma_test0_u_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_TEST1_U_UNION
 �ṹ˵��  : DMA_TEST1_U �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test1_u : 32; /* bit[0-31]: ��ά�ɲ�Ĵ�������dma_pulse��Чʱ���£���
                                                      31 : real.rbrg_dma_cneed;
                                                      30 : real.dma_rbrg_crdy;
                                                      29 : real.pref_va_drdy;
                                                      28 : real.pa_drdy;
                                                      [27:16]: real.pix_axis_cnt;
                                                      [15:0] : real.line_axis_cnt; */
    } reg;
} SOC_DSS_WCH_DMA_TEST1_U_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST1_U_dma_test1_u_START  (0)
#define SOC_DSS_WCH_DMA_TEST1_U_dma_test1_u_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_TEST3_U_UNION
 �ṹ˵��  : DMA_TEST3_U �Ĵ����ṹ���塣��ַƫ����:0x009C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test3_u : 32; /* bit[0-31]: ��ά�ɲ�Ĵ�������dma_pulse��Чʱ���£���
                                                      [31:16]: monitor.rbrg_dma_cneed_cnt;
                                                      [15:0]: monitor.dma_dbg_cnt[23:8]; */
    } reg;
} SOC_DSS_WCH_DMA_TEST3_U_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST3_U_dma_test3_u_START  (0)
#define SOC_DSS_WCH_DMA_TEST3_U_dma_test3_u_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_TEST4_U_UNION
 �ṹ˵��  : DMA_TEST4_U �Ĵ����ṹ���塣��ַƫ����:0x00A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_test4_u : 32; /* bit[0-31]: ��ά�ɲ�Ĵ�������dma_pulse��Чʱ���£���
                                                      [31:16]: monitor.rbrg_dma_drdy_cnt;
                                                      [15:0]: monitor.dma_dbg_cnt[23:8]; */
    } reg;
} SOC_DSS_WCH_DMA_TEST4_U_UNION;
#endif
#define SOC_DSS_WCH_DMA_TEST4_U_dma_test4_u_START  (0)
#define SOC_DSS_WCH_DMA_TEST4_U_dma_test4_u_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_STATUS_U_UNION
 �ṹ˵��  : DMA_STATUS_U �Ĵ����ṹ���塣��ַƫ����:0x00A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ״̬�ϱ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_status_u : 32; /* bit[0-31]: ״̬�ϱ��Ĵ������ڲ�����ĳЩ�쳣ʱ���£���
                                                       24~31: ����
                                                       23��pre.block_dma_req_idle
                                                       22��pre.pipeline_en
                                                       21��pre.block_end
                                                       20��pre.line_end
                                                       19��pre.inte_err_3
                                                       18��pre.inte_err_2
                                                       17��pre.inte_err_1
                                                       16��pre.inte_err_0
                                                       8~15: ����
                                                       7��real.block_dma_req_idle
                                                       6��real.pipeline_en
                                                       5��real.block_end
                                                       4��real.line_end
                                                       3��real.inte_err_3
                                                       2��real.inte_err_2
                                                       1��real.inte_err_1
                                                       0��real.inte_err_0 */
    } reg;
} SOC_DSS_WCH_DMA_STATUS_U_UNION;
#endif
#define SOC_DSS_WCH_DMA_STATUS_U_dma_status_u_START  (0)
#define SOC_DSS_WCH_DMA_STATUS_U_dma_status_u_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_CH_RD_SHADOW_UNION
 �ṹ˵��  : CH_RD_SHADOW �Ĵ����ṹ���塣��ַƫ����:0x00D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���Ĵ���ѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rwch_rd_shadow : 1;  /* bit[0]   : ���Ĵ���ѡ��
                                                         0�������Ĵ���
                                                         1��Ӱ�ӼĴ��� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_CH_RD_SHADOW_UNION;
#endif
#define SOC_DSS_WCH_CH_RD_SHADOW_rwch_rd_shadow_START  (0)
#define SOC_DSS_WCH_CH_RD_SHADOW_rwch_rd_shadow_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_CH_CTL_UNION
 �ṹ˵��  : CH_CTL �Ĵ����ṹ���塣��ַƫ����:0x00D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ�����ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_en          : 1;  /* bit[0]   : RCH��WCHʹ�� */
        unsigned int  ch_version_sel : 1;  /* bit[1]   : 0��K3V3ԭ���ܰ汾��
                                                         1������ */
        unsigned int  ch_afbce_en    : 1;  /* bit[2]   : 0���ر�ѹ������
                                                         1������ѹ������ */
        unsigned int  ch_block_en    : 1;  /* bit[3]   : 0���ر�block����
                                                         1������block���� */
        unsigned int  ch_last_block  : 1;  /* bit[4]   : 0����ʾ��ǰ֡�����һ��
                                                         1����ʾ��ǰ֡���һ�� */
        unsigned int  reserved       : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_DSS_WCH_CH_CTL_UNION;
#endif
#define SOC_DSS_WCH_CH_CTL_ch_en_START           (0)
#define SOC_DSS_WCH_CH_CTL_ch_en_END             (0)
#define SOC_DSS_WCH_CH_CTL_ch_version_sel_START  (1)
#define SOC_DSS_WCH_CH_CTL_ch_version_sel_END    (1)
#define SOC_DSS_WCH_CH_CTL_ch_afbce_en_START     (2)
#define SOC_DSS_WCH_CH_CTL_ch_afbce_en_END       (2)
#define SOC_DSS_WCH_CH_CTL_ch_block_en_START     (3)
#define SOC_DSS_WCH_CH_CTL_ch_block_en_END       (3)
#define SOC_DSS_WCH_CH_CTL_ch_last_block_START   (4)
#define SOC_DSS_WCH_CH_CTL_ch_last_block_END     (4)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_CH_SECU_EN_UNION
 �ṹ˵��  : CH_SECU_EN �Ĵ����ṹ���塣��ַƫ����:0x00D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ����ȫʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_secu_en : 1;  /* bit[0]   : 0���ǰ�ȫ
                                                     1����ȫ */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_CH_SECU_EN_UNION;
#endif
#define SOC_DSS_WCH_CH_SECU_EN_ch_secu_en_START  (0)
#define SOC_DSS_WCH_CH_SECU_EN_ch_secu_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_CH_SW_END_REQ_UNION
 �ṹ˵��  : CH_SW_END_REQ �Ĵ����ṹ���塣��ַƫ����:0x00DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����峡�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_sw_end_req : 1;  /* bit[0]   : ���д1�����峡��������ɺ��λ�Զ����㡣 */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_CH_SW_END_REQ_UNION;
#endif
#define SOC_DSS_WCH_CH_SW_END_REQ_ch_sw_end_req_START  (0)
#define SOC_DSS_WCH_CH_SW_END_REQ_ch_sw_end_req_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_CH_CLK_SEL_UNION
 �ṹ˵��  : CH_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x00E0����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_clk_sel : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                     1����ʾǿ�ƴ�ʱ�ӡ�
                                                     0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ��
                                                     bit0������apb��
                                                     bit1������ch_ctl��
                                                     bit2������reg��
                                                     bit3������dma��
                                                     bit4������dfc��
                                                     bit5������vscf_v��
                                                     bit6������vscf_h��
                                                     bit7������sharp��
                                                     bit8������ce��
                                                     bit9������csc��
                                                     bit10������rot��
                                                     bit11������vpp��
                                                     bit12������gscf�� */
    } reg;
} SOC_DSS_WCH_CH_CLK_SEL_UNION;
#endif
#define SOC_DSS_WCH_CH_CLK_SEL_ch_clk_sel_START  (0)
#define SOC_DSS_WCH_CH_CLK_SEL_ch_clk_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_CH_CLK_EN_UNION
 �ṹ˵��  : CH_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x00E4����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_clk_en : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                    1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                    0����ʾ���ʱ��ʹ����Ч����ֹӲ������
                                                    bit0������apb��
                                                    bit1������ch_ctl��
                                                    bit2������reg��
                                                    bit3������dma��
                                                    bit4������dfc��
                                                    bit5������scf��
                                                    bit6��������
                                                    bit7������sharp��
                                                    bit8������ce��
                                                    bit9������csc��
                                                    bit10������rot��
                                                    bit11������vpp��
                                                    bit12������gscf�� */
    } reg;
} SOC_DSS_WCH_CH_CLK_EN_UNION;
#endif
#define SOC_DSS_WCH_CH_CLK_EN_ch_clk_en_START  (0)
#define SOC_DSS_WCH_CH_CLK_EN_ch_clk_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DFC_DISP_SIZE_UNION
 �ṹ˵��  : DFC_DISP_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͼ���С
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_size_vrt : 13; /* bit[0-12] : ����DFC��ͼ��Ĵ�ֱ�߶�-1 */
        unsigned int  reserved_0   : 3;  /* bit[13-15]: ���� */
        unsigned int  dfc_size_hrz : 13; /* bit[16-28]: ����DFC��ͼ��ÿ�д����������-1��������2pixel������4pxiel���䣬����SIZE_HRZ+1����Ϊ2����4�ı����� */
        unsigned int  reserved_1   : 3;  /* bit[29-31]: ���� */
    } reg;
} SOC_DSS_WCH_DFC_DISP_SIZE_UNION;
#endif
#define SOC_DSS_WCH_DFC_DISP_SIZE_dfc_size_vrt_START  (0)
#define SOC_DSS_WCH_DFC_DISP_SIZE_dfc_size_vrt_END    (12)
#define SOC_DSS_WCH_DFC_DISP_SIZE_dfc_size_hrz_START  (16)
#define SOC_DSS_WCH_DFC_DISP_SIZE_dfc_size_hrz_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DFC_PIX_IN_NUM_UNION
 �ṹ˵��  : DFC_PIX_IN_NUM �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_pix_in_num : 1;  /* bit[0]   : DFC��ͨ���������дͨ�������������Ŀ
                                                         0:2pixel (RDMA�������ÿ����Ϊ32bit����24bit���� ��RGB888,YUV444)
                                                         1:4pixel (RDMA�������ÿ����Ϊ16bit���� ��RGB565,XRGB1555,XRGB4444��YUV422)
                                                         ע�� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_DFC_PIX_IN_NUM_UNION;
#endif
#define SOC_DSS_WCH_DFC_PIX_IN_NUM_dfc_pix_in_num_START  (0)
#define SOC_DSS_WCH_DFC_PIX_IN_NUM_dfc_pix_in_num_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DFC_GLB_ALPHA_UNION
 �ṹ˵��  : DFC_GLB_ALPHA �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͸��������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_glb_alpha1 : 8;  /* bit[0-7]  : ��ARGB1555 AΪ1ʱѡ���͸�������� */
        unsigned int  dfc_glb_alpha0 : 8;  /* bit[8-15] : ��ARGB1555 AΪ0ʱѡ���͸�������� */
        unsigned int  reserved       : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DSS_WCH_DFC_GLB_ALPHA_UNION;
#endif
#define SOC_DSS_WCH_DFC_GLB_ALPHA_dfc_glb_alpha1_START  (0)
#define SOC_DSS_WCH_DFC_GLB_ALPHA_dfc_glb_alpha1_END    (7)
#define SOC_DSS_WCH_DFC_GLB_ALPHA_dfc_glb_alpha0_START  (8)
#define SOC_DSS_WCH_DFC_GLB_ALPHA_dfc_glb_alpha0_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DFC_DISP_FMT_UNION
 �ṹ˵��  : DFC_DISP_FMT �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ʾ��ʽ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_ax_swap : 1;  /* bit[0]   : AX �ߵ�λ�л�(RGBA->ARGB YUVA->AYUV)
                                                      0��������
                                                      1������ */
        unsigned int  dfc_img_fmt : 5;  /* bit[1-5] : ����ʱ�����ʽ/д�������ʽ
                                                      00000:RGB565
                                                      00001:XRGB4444(WDFC��֧��)
                                                      00010:ARGB4444(WDFC��֧��)
                                                      00011:XRGB1555(WDFC��֧��)
                                                      00100:ARGB1555(WDFC��֧��)
                                                      00101:XRGB8888
                                                      00110:ARGB8888
                                                      00111:BGR565
                                                      01000:XBGR4444
                                                      01001:ABGR4444
                                                      01010:XBGR1555
                                                      01011:ABGR1555
                                                      01100:XBGR8888
                                                      01101:ABGR8888
                                                      01110:YUV444
                                                      01111:YVU444
                                                      10000:YUYV422
                                                      10001:YVYU422
                                                      10010:VYUY422
                                                      10011:UYVY422 */
        unsigned int  dfc_uv_swap : 1;  /* bit[6]   : U��V������־��
                                                      0��������
                                                      1������ */
        unsigned int  dfc_rb_swap : 1;  /* bit[7]   : R��B������־��
                                                      0��������
                                                      1������ */
        unsigned int  reserved    : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_WCH_DFC_DISP_FMT_UNION;
#endif
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_ax_swap_START  (0)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_ax_swap_END    (0)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_img_fmt_START  (1)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_img_fmt_END    (5)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_uv_swap_START  (6)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_uv_swap_END    (6)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_rb_swap_START  (7)
#define SOC_DSS_WCH_DFC_DISP_FMT_dfc_rb_swap_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_UNION
 �ṹ˵��  : DFC_CLIP_CTL_HRZ �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0x00000000�����:32
 �Ĵ���˵��: ˮƽ�ü�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_right_clip : 6;  /* bit[0-5]  : ͼ���ұ߽���CLIP��������������dma_pix_fmt��32bpp�֧࣬��0~3��16bpp�֧࣬��0~7��8bpp��֧��0~15�� */
        unsigned int  reserved_0     : 10; /* bit[6-15] : ���� */
        unsigned int  dfc_left_clip  : 6;  /* bit[16-21]: ͼ����߽���CLIP������������ROT��ʹ��ʱ��CLIP��ΧΪ0~15�� */
        unsigned int  reserved_1     : 10; /* bit[22-31]: ���� */
    } reg;
} SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_UNION;
#endif
#define SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_dfc_right_clip_START  (0)
#define SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_dfc_right_clip_END    (5)
#define SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_dfc_left_clip_START   (16)
#define SOC_DSS_WCH_DFC_CLIP_CTL_HRZ_dfc_left_clip_END     (21)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_UNION
 �ṹ˵��  : DFC_CLIP_CTL_VRZ �Ĵ����ṹ���塣��ַƫ����:0x0114����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ֱ�ü�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_bot_clip : 6;  /* bit[0-5]  : ͼ��ױ߽���CLIP������������ROTʹ��ʱ��CLIP��ΧΪ0~15�� */
        unsigned int  reserved_0   : 10; /* bit[6-15] : ���� */
        unsigned int  dfc_top_clip : 6;  /* bit[16-21]: ͼ�񶥱߽���CLIP������������ROTʹ��ʱ��CLIP��ΧΪ0~15�� */
        unsigned int  reserved_1   : 10; /* bit[22-31]: ���� */
    } reg;
} SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_UNION;
#endif
#define SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_dfc_bot_clip_START  (0)
#define SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_dfc_bot_clip_END    (5)
#define SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_dfc_top_clip_START  (16)
#define SOC_DSS_WCH_DFC_CLIP_CTL_VRZ_dfc_top_clip_END    (21)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DFC_CTL_CLIP_EN_UNION
 �ṹ˵��  : DFC_CTL_CLIP_EN �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͼ�����ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_ctl_clip_enable : 1;  /* bit[0]   : ͼ�����ʹ�� */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_DFC_CTL_CLIP_EN_UNION;
#endif
#define SOC_DSS_WCH_DFC_CTL_CLIP_EN_dfc_ctl_clip_enable_START  (0)
#define SOC_DSS_WCH_DFC_CTL_CLIP_EN_dfc_ctl_clip_enable_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DFC_ICG_MODULE_UNION
 �ṹ˵��  : DFC_ICG_MODULE �Ĵ����ṹ���塣��ַƫ����:0x011C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ʱ���ſ�ģʽ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_module_en : 1;  /* bit[0]   : 1'b1:��ģ��enable
                                                        1'b0:��ģ��disable */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_DFC_ICG_MODULE_UNION;
#endif
#define SOC_DSS_WCH_DFC_ICG_MODULE_dfc_module_en_START  (0)
#define SOC_DSS_WCH_DFC_ICG_MODULE_dfc_module_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DFC_DITHER_ENABLE_UNION
 �ṹ˵��  : DFC_DITHER_ENABLE �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��������ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_dither_en : 1;  /* bit[0]   : 
                                                        ��������ʹ�� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_DFC_DITHER_ENABLE_UNION;
#endif
#define SOC_DSS_WCH_DFC_DITHER_ENABLE_dfc_dither_en_START  (0)
#define SOC_DSS_WCH_DFC_DITHER_ENABLE_dfc_dither_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DFC_PADDING_CTL_UNION
 �ṹ˵��  : DFC_PADDING_CTL �Ĵ����ṹ���塣��ַƫ����:0x0124����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������ؿ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dfc_left_pad       : 5;  /* bit[0-4]  : ��߽����������� */
        unsigned int  reserved_0         : 3;  /* bit[5-7]  : ���� */
        unsigned int  dfc_right_pad      : 5;  /* bit[8-12] : �ұ߽����������� */
        unsigned int  reserved_1         : 3;  /* bit[13-15]: ���� */
        unsigned int  dfc_top_pad        : 5;  /* bit[16-20]: �ϱ߽����������� */
        unsigned int  reserved_2         : 3;  /* bit[21-23]: ���� */
        unsigned int  dfc_bot_pad        : 5;  /* bit[24-28]: �±߽����������� */
        unsigned int  reserved_3         : 2;  /* bit[29-30]: ���� */
        unsigned int  dfc_ctl_pad_enable : 1;  /* bit[31]   : ��������ʹ�� */
    } reg;
} SOC_DSS_WCH_DFC_PADDING_CTL_UNION;
#endif
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_left_pad_START        (0)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_left_pad_END          (4)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_right_pad_START       (8)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_right_pad_END         (12)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_top_pad_START         (16)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_top_pad_END           (20)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_bot_pad_START         (24)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_bot_pad_END           (28)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_ctl_pad_enable_START  (31)
#define SOC_DSS_WCH_DFC_PADDING_CTL_dfc_ctl_pad_enable_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_CSC_IDC_UNION
 �ṹ˵��  : CSC_IDC �Ĵ����ṹ���塣��ַƫ����:0x0500����ֵ:0x00000000�����:32
 �Ĵ���˵��: ɫ�ʿռ�ת������ֱ�������Ĵ�����Ϊ��ʱ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_idc0 : 9;  /* bit[0-8]  : �������0ֱ��������MSBΪ����λ�������ʾ�� */
        unsigned int  csc_idc1 : 9;  /* bit[9-17] : �������1ֱ��������MSBΪ����λ�������ʾ�� */
        unsigned int  csc_idc2 : 9;  /* bit[18-26]: �������2ֱ��������MSBΪ����λ�������ʾ�� */
        unsigned int  reserved : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_DSS_WCH_CSC_IDC_UNION;
#endif
#define SOC_DSS_WCH_CSC_IDC_csc_idc0_START  (0)
#define SOC_DSS_WCH_CSC_IDC_csc_idc0_END    (8)
#define SOC_DSS_WCH_CSC_IDC_csc_idc1_START  (9)
#define SOC_DSS_WCH_CSC_IDC_csc_idc1_END    (17)
#define SOC_DSS_WCH_CSC_IDC_csc_idc2_START  (18)
#define SOC_DSS_WCH_CSC_IDC_csc_idc2_END    (26)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_CSC_ODC_UNION
 �ṹ˵��  : CSC_ODC �Ĵ����ṹ���塣��ַƫ����:0x0504����ֵ:0x00000000�����:32
 �Ĵ���˵��: ɫ�ʿռ�ת�����ֱ�������Ĵ�����Ϊ��ʱ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_odc0 : 9;  /* bit[0-8]  : �������0ֱ��������MSBΪ����λ�������ʾ�� */
        unsigned int  csc_odc1 : 9;  /* bit[9-17] : �������1ֱ��������MSBΪ����λ�������ʾ�� */
        unsigned int  csc_odc2 : 9;  /* bit[18-26]: �������2ֱ��������MSBΪ����λ�������ʾ�� */
        unsigned int  reserved : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_DSS_WCH_CSC_ODC_UNION;
#endif
#define SOC_DSS_WCH_CSC_ODC_csc_odc0_START  (0)
#define SOC_DSS_WCH_CSC_ODC_csc_odc0_END    (8)
#define SOC_DSS_WCH_CSC_ODC_csc_odc1_START  (9)
#define SOC_DSS_WCH_CSC_ODC_csc_odc1_END    (17)
#define SOC_DSS_WCH_CSC_ODC_csc_odc2_START  (18)
#define SOC_DSS_WCH_CSC_ODC_csc_odc2_END    (26)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_CSC_P0_UNION
 �ṹ˵��  : CSC_P0 �Ĵ����ṹ���塣��ַƫ����:0x0508����ֵ:0x00000000�����:32
 �Ĵ���˵��: ɫ�ʿռ�ת������0��Ϊ��ʱ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_p00  : 11; /* bit[0-10] : 3.8���ݸ�ʽ��1bit����λ��2bit����λ��8bitС��λ�������ʾ */
        unsigned int  reserved_0: 5;  /* bit[11-15]: ���� */
        unsigned int  csc_p01  : 11; /* bit[16-26]: 3.8���ݸ�ʽ��1bit����λ��2bit����λ��8bitС��λ�������ʾ */
        unsigned int  reserved_1: 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_DSS_WCH_CSC_P0_UNION;
#endif
#define SOC_DSS_WCH_CSC_P0_csc_p00_START   (0)
#define SOC_DSS_WCH_CSC_P0_csc_p00_END     (10)
#define SOC_DSS_WCH_CSC_P0_csc_p01_START   (16)
#define SOC_DSS_WCH_CSC_P0_csc_p01_END     (26)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_CSC_P1_UNION
 �ṹ˵��  : CSC_P1 �Ĵ����ṹ���塣��ַƫ����:0x050C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ɫ�ʿռ�ת������0��Ϊ��ʱ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_p02  : 11; /* bit[0-10] : 3.8���ݸ�ʽ��1bit����λ��2bit����λ��8bitС��λ�������ʾ */
        unsigned int  reserved_0: 5;  /* bit[11-15]: ���� */
        unsigned int  csc_p10  : 11; /* bit[16-26]: 3.8���ݸ�ʽ��1bit����λ��2bit����λ��8bitС��λ�������ʾ */
        unsigned int  reserved_1: 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_DSS_WCH_CSC_P1_UNION;
#endif
#define SOC_DSS_WCH_CSC_P1_csc_p02_START   (0)
#define SOC_DSS_WCH_CSC_P1_csc_p02_END     (10)
#define SOC_DSS_WCH_CSC_P1_csc_p10_START   (16)
#define SOC_DSS_WCH_CSC_P1_csc_p10_END     (26)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_CSC_P2_UNION
 �ṹ˵��  : CSC_P2 �Ĵ����ṹ���塣��ַƫ����:0x0510����ֵ:0x00000000�����:32
 �Ĵ���˵��: ɫ�ʿռ�ת������0��Ϊ��ʱ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_p11  : 11; /* bit[0-10] : 3.8���ݸ�ʽ��1bit����λ��2bit����λ��8bitС��λ�������ʾ */
        unsigned int  reserved_0: 5;  /* bit[11-15]: ���� */
        unsigned int  csc_p12  : 11; /* bit[16-26]: 3.8���ݸ�ʽ��1bit����λ��2bit����λ��8bitС��λ�������ʾ */
        unsigned int  reserved_1: 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_DSS_WCH_CSC_P2_UNION;
#endif
#define SOC_DSS_WCH_CSC_P2_csc_p11_START   (0)
#define SOC_DSS_WCH_CSC_P2_csc_p11_END     (10)
#define SOC_DSS_WCH_CSC_P2_csc_p12_START   (16)
#define SOC_DSS_WCH_CSC_P2_csc_p12_END     (26)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_CSC_P3_UNION
 �ṹ˵��  : CSC_P3 �Ĵ����ṹ���塣��ַƫ����:0x0514����ֵ:0x00000000�����:32
 �Ĵ���˵��: ɫ�ʿռ�ת������0��Ϊ��ʱ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_p20  : 11; /* bit[0-10] : 3.8���ݸ�ʽ��1bit����λ��2bit����λ��8bitС��λ�������ʾ */
        unsigned int  reserved_0: 5;  /* bit[11-15]: ���� */
        unsigned int  csc_p21  : 11; /* bit[16-26]: 3.8���ݸ�ʽ��1bit����λ��2bit����λ��8bitС��λ�������ʾ */
        unsigned int  reserved_1: 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_DSS_WCH_CSC_P3_UNION;
#endif
#define SOC_DSS_WCH_CSC_P3_csc_p20_START   (0)
#define SOC_DSS_WCH_CSC_P3_csc_p20_END     (10)
#define SOC_DSS_WCH_CSC_P3_csc_p21_START   (16)
#define SOC_DSS_WCH_CSC_P3_csc_p21_END     (26)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_CSC_P4_UNION
 �ṹ˵��  : CSC_P4 �Ĵ����ṹ���塣��ַƫ����:0x0518����ֵ:0x00000000�����:32
 �Ĵ���˵��: ɫ�ʿռ�ת������0��Ϊ��ʱ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_p22  : 11; /* bit[0-10] : 3.8���ݸ�ʽ��1bit����λ��2bit����λ��8bitС��λ�������ʾ */
        unsigned int  reserved : 21; /* bit[11-31]: ���� */
    } reg;
} SOC_DSS_WCH_CSC_P4_UNION;
#endif
#define SOC_DSS_WCH_CSC_P4_csc_p22_START   (0)
#define SOC_DSS_WCH_CSC_P4_csc_p22_END     (10)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_CSC_ICG_MODULE_UNION
 �ṹ˵��  : CSC_ICG_MODULE �Ĵ����ṹ���塣��ַƫ����:0x051C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ʱ���ſ�ģʽ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csc_module_en : 1;  /* bit[0]   : ICGģʽʹ��
                                                        1'b1:��ģ��enable
                                                        1'b1:��ģ��disable */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_CSC_ICG_MODULE_UNION;
#endif
#define SOC_DSS_WCH_CSC_ICG_MODULE_csc_module_en_START  (0)
#define SOC_DSS_WCH_CSC_ICG_MODULE_csc_module_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_FIRST_LNS_UNION
 �ṹ˵��  : ROT_FIRST_LNS �Ĵ����ṹ���塣��ַƫ����:0x0530����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ת�׿������Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_first_lns_en : 1;  /* bit[0]   : ��ֻ��תʱ��ԭʼͼ���ϲ�paddingʹ���ź� */
        unsigned int  rot_first_lns    : 5;  /* bit[1-5] : ��ֻ��תʱ��ԭʼͼ���ϲ�padding��������
                                                           ��16bppʱ����Сpadding1�У����padding31�У�
                                                           ��32bppʱ����Сpadding1�У����padding15�С� */
        unsigned int  reserved         : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_WCH_ROT_FIRST_LNS_UNION;
#endif
#define SOC_DSS_WCH_ROT_FIRST_LNS_rot_first_lns_en_START  (0)
#define SOC_DSS_WCH_ROT_FIRST_LNS_rot_first_lns_en_END    (0)
#define SOC_DSS_WCH_ROT_FIRST_LNS_rot_first_lns_START     (1)
#define SOC_DSS_WCH_ROT_FIRST_LNS_rot_first_lns_END       (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_STATE_UNION
 �ṹ˵��  : ROT_STATE �Ĵ����ṹ���塣��ַƫ����:0x0534����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_state : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_ROT_STATE_UNION;
#endif
#define SOC_DSS_WCH_ROT_STATE_rot_state_START  (0)
#define SOC_DSS_WCH_ROT_STATE_rot_state_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_MEM_CTRL_UNION
 �ṹ˵��  : ROT_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0538����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT �͹��Ŀ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_mem_ctrl : 4;  /* bit[0-3] : �����üĴ�����ROT memory�͹����������
                                                       [3] mem_ctrl_auto_en , �Զ�ģʽ���������ģʽѡ��,0�Զ�ģʽ��1�������ģʽ 
                                                       [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                       [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                       [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved     : 28; /* bit[4-31]: reserved */
    } reg;
} SOC_DSS_WCH_ROT_MEM_CTRL_UNION;
#endif
#define SOC_DSS_WCH_ROT_MEM_CTRL_rot_mem_ctrl_START  (0)
#define SOC_DSS_WCH_ROT_MEM_CTRL_rot_mem_ctrl_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_SIZE_UNION
 �ṹ˵��  : ROT_SIZE �Ĵ����ṹ���塣��ַƫ����:0x053C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͼ���С
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_img_width  : 13; /* bit[0-12] : ����ROT����Чͼ���ȣ�������Ϊ��λ����һ���á�
                                                          ��ת��ѹ��ʱ��YUV422��ʽ����СΪ2�����أ����512��pixcel��
                                                           16RGB��ʽ����С1�����أ����512��pixcel��
                                                           32RGB/YUV444��ʽ����С1�����أ����512��pixcel��
                                                          ��תѹ��ʱ�� YUV422��ʽ����СΪ2�����أ����1024��pixcel��
                                                           16RGB��ʽ����С1�����أ����1024��pixcel��
                                                           32RGB/YUV444��ʽ����С1�����أ����512��pixcel�� */
        unsigned int  reserved_0     : 3;  /* bit[13-15]: ���� */
        unsigned int  rot_img_height : 13; /* bit[16-28]: ����ROT����Чͼ��߶ȣ�����Ϊ��λ����һ���á�
                                                          Yuv422��ʽ����СΪ2�У����4096�У�
                                                          ������ʽ����СΪ1�У����4096�С� */
        unsigned int  reserved_1     : 3;  /* bit[29-31]: ���� */
    } reg;
} SOC_DSS_WCH_ROT_SIZE_UNION;
#endif
#define SOC_DSS_WCH_ROT_SIZE_rot_img_width_START   (0)
#define SOC_DSS_WCH_ROT_SIZE_rot_img_width_END     (12)
#define SOC_DSS_WCH_ROT_SIZE_rot_img_height_START  (16)
#define SOC_DSS_WCH_ROT_SIZE_rot_img_height_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_CPU_CTL0_UNION
 �ṹ˵��  : ROT_CPU_CTL0 �Ĵ����ṹ���塣��ַƫ����:0x0540����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT ����ѡ��Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_ctl0 : 1;  /* bit[0]   : ������ */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_ROT_CPU_CTL0_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_CTL0_rot_cpu_ctl0_START  (0)
#define SOC_DSS_WCH_ROT_CPU_CTL0_rot_cpu_ctl0_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_CPU_START0_UNION
 �ṹ˵��  : ROT_CPU_START0 �Ĵ����ṹ���塣��ַƫ����:0x0544����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT ���������Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_start0 : 1;  /* bit[0]   : ������ */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_ROT_CPU_START0_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_START0_rot_cpu_start0_START  (0)
#define SOC_DSS_WCH_ROT_CPU_START0_rot_cpu_start0_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_CPU_ADDR0_UNION
 �ṹ˵��  : ROT_CPU_ADDR0 �Ĵ����ṹ���塣��ַƫ����:0x0548����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT ��ַ�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_addr0 : 12; /* bit[0-11] : ������ */
        unsigned int  reserved      : 19; /* bit[12-30]: ���� */
        unsigned int  rot_cpu_rw0   : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_DSS_WCH_ROT_CPU_ADDR0_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_ADDR0_rot_cpu_addr0_START  (0)
#define SOC_DSS_WCH_ROT_CPU_ADDR0_rot_cpu_addr0_END    (11)
#define SOC_DSS_WCH_ROT_CPU_ADDR0_rot_cpu_rw0_START    (31)
#define SOC_DSS_WCH_ROT_CPU_ADDR0_rot_cpu_rw0_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_CPU_RDATA0_UNION
 �ṹ˵��  : ROT_CPU_RDATA0 �Ĵ����ṹ���塣��ַƫ����:0x054C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT �����ݶ˿ڼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_rdata0 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_ROT_CPU_RDATA0_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_RDATA0_rot_cpu_rdata0_START  (0)
#define SOC_DSS_WCH_ROT_CPU_RDATA0_rot_cpu_rdata0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_CPU_RDATA1_UNION
 �ṹ˵��  : ROT_CPU_RDATA1 �Ĵ����ṹ���塣��ַƫ����:0x0550����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT �����ݶ˿ڼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_rdata1 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_ROT_CPU_RDATA1_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_RDATA1_rot_cpu_rdata1_START  (0)
#define SOC_DSS_WCH_ROT_CPU_RDATA1_rot_cpu_rdata1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_CPU_WDATA0_UNION
 �ṹ˵��  : ROT_CPU_WDATA0 �Ĵ����ṹ���塣��ַƫ����:0x0554����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT д���ݶ˿ڼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_wdata0 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_ROT_CPU_WDATA0_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_WDATA0_rot_cpu_wdata0_START  (0)
#define SOC_DSS_WCH_ROT_CPU_WDATA0_rot_cpu_wdata0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_CPU_WDATA1_UNION
 �ṹ˵��  : ROT_CPU_WDATA1 �Ĵ����ṹ���塣��ַƫ����:0x0558����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT д���ݶ˿ڼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_wdata1 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_ROT_CPU_WDATA1_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_WDATA1_rot_cpu_wdata1_START  (0)
#define SOC_DSS_WCH_ROT_CPU_WDATA1_rot_cpu_wdata1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_CPU_CTL1_UNION
 �ṹ˵��  : ROT_CPU_CTL1 �Ĵ����ṹ���塣��ַƫ����:0x055C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT ����ѡ��Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_ctl1 : 1;  /* bit[0]   : ������ */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_ROT_CPU_CTL1_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_CTL1_rot_cpu_ctl1_START  (0)
#define SOC_DSS_WCH_ROT_CPU_CTL1_rot_cpu_ctl1_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_CPU_START1_UNION
 �ṹ˵��  : ROT_CPU_START1 �Ĵ����ṹ���塣��ַƫ����:0x0560����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT ���������Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_start1 : 1;  /* bit[0]   : ������ */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_ROT_CPU_START1_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_START1_rot_cpu_start1_START  (0)
#define SOC_DSS_WCH_ROT_CPU_START1_rot_cpu_start1_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_CPU_ADDR1_UNION
 �ṹ˵��  : ROT_CPU_ADDR1 �Ĵ����ṹ���塣��ַƫ����:0x0564����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT ��ַ�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_addr1 : 12; /* bit[0-11] : ������ */
        unsigned int  reserved      : 19; /* bit[12-30]: ���� */
        unsigned int  rot_cpu_rw1   : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_DSS_WCH_ROT_CPU_ADDR1_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_ADDR1_rot_cpu_addr1_START  (0)
#define SOC_DSS_WCH_ROT_CPU_ADDR1_rot_cpu_addr1_END    (11)
#define SOC_DSS_WCH_ROT_CPU_ADDR1_rot_cpu_rw1_START    (31)
#define SOC_DSS_WCH_ROT_CPU_ADDR1_rot_cpu_rw1_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_CPU_RDATA2_UNION
 �ṹ˵��  : ROT_CPU_RDATA2 �Ĵ����ṹ���塣��ַƫ����:0x0568����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT �����ݶ˿ڼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_rdata2 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_ROT_CPU_RDATA2_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_RDATA2_rot_cpu_rdata2_START  (0)
#define SOC_DSS_WCH_ROT_CPU_RDATA2_rot_cpu_rdata2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_CPU_RDATA3_UNION
 �ṹ˵��  : ROT_CPU_RDATA3 �Ĵ����ṹ���塣��ַƫ����:0x056C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT �����ݶ˿ڼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_rdata3 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_ROT_CPU_RDATA3_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_RDATA3_rot_cpu_rdata3_START  (0)
#define SOC_DSS_WCH_ROT_CPU_RDATA3_rot_cpu_rdata3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_CPU_WDATA2_UNION
 �ṹ˵��  : ROT_CPU_WDATA2 �Ĵ����ṹ���塣��ַƫ����:0x0570����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT д���ݶ˿ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_wdata2 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_ROT_CPU_WDATA2_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_WDATA2_rot_cpu_wdata2_START  (0)
#define SOC_DSS_WCH_ROT_CPU_WDATA2_rot_cpu_wdata2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ROT_CPU_WDATA3_UNION
 �ṹ˵��  : ROT_CPU_WDATA3 �Ĵ����ṹ���塣��ַƫ����:0x0574����ֵ:0x00000000�����:32
 �Ĵ���˵��: ROT д���ݶ˿ڼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rot_cpu_wdata3 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_ROT_CPU_WDATA3_UNION;
#endif
#define SOC_DSS_WCH_ROT_CPU_WDATA3_rot_cpu_wdata3_START  (0)
#define SOC_DSS_WCH_ROT_CPU_WDATA3_rot_cpu_wdata3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_CH_DEBUG_SEL_UNION
 �ṹ˵��  : CH_DEBUG_SEL �Ĵ����ṹ���塣��ַƫ����:0x600����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_debug_sel : 4;  /* bit[0-3] : ����ģ���module_debug��ch_debug�����ѡ���ź�, ����ֵΪ��
                                                       'b0000:dma_y_debug
                                                       'b0001:dma_u_debug
                                                       'b0010:dma_v_debug
                                                       'b0011:rot_debug
                                                       'b0100:dfc_debug
                                                       'b0101:scf_debug
                                                       'b0110:sharp_debug
                                                       'b0111:ce_debug
                                                       'b1000:csc_debug */
        unsigned int  reserved     : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_WCH_CH_DEBUG_SEL_UNION;
#endif
#define SOC_DSS_WCH_CH_DEBUG_SEL_ch_debug_sel_START  (0)
#define SOC_DSS_WCH_CH_DEBUG_SEL_ch_debug_sel_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_CTRL_UNION
 �ṹ˵��  : DMA_BUF_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0800����ֵ:0x00000008�����:32
 �Ĵ���˵��: DMA_BUF���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_os_cfg    : 6;  /* bit[0-5]  : dma_buf�������ƼĴ�����
                                                             1. ����rdma_buf����ʾʹ�õ�bufռ��buf�ı�������������Ϊ1~8����AΪ����ֵ��
                                                             ��ƽ���ʽʱʹ�õ�bufռ��buf�ı���ΪA/8��
                                                             ˫ƽ���ʽʱʹ�õ�bufռ��buf�ı���Ϊint[(A+1)/2]*2/8��
                                                             ��ƽ���ʽʱʹ�õ�bufռ��buf�ı���Ϊint[(A+3)/4]*4/8��
                                                             2. ����wdma_buf���������ص�yͨ�����������ˮ��ֵ����������Ϊ0~15����AΪ����ֵ��
                                                             ������ˮ��ֵΪ(A+1)* 8 * 16B��package��ʽ��
                                                             ������ˮ��ֵΪ(A+1)* 4 * 16B����package��ʽ�� */
        unsigned int  reserved_0        : 2;  /* bit[6-7]  : ���� */
        unsigned int  dma_buf_qos_mask  : 1;  /* bit[8]    : �ⲿqos��Ϣ���μĴ���
                                                             0���ⲿqos��Ϣ��Ч����
                                                             1���ⲿqos��Ϣ���δ���
                                                             ע��
                                                             1��wdma_buf����ע���� */
        unsigned int  dma_buf_cont_mask : 1;  /* bit[9]    : ��βcont���͹������μĴ���
                                                             0����βcont����ʹ��
                                                             1����βcont��������
                                                             ע��
                                                             1��wdma_buf����ע���� */
        unsigned int  dma_buf_l_e_mask  : 1;  /* bit[10]   : ��βbuf��ת�������μĴ���
                                                             0����βbuf��תʹ��
                                                             1����βbuf��ת����
                                                             ע��
                                                             1��wdma_buf����ע���� */
        unsigned int  reserved_1        : 21; /* bit[11-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CTRL_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_os_cfg_START     (0)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_os_cfg_END       (5)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_qos_mask_START   (8)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_qos_mask_END     (8)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_cont_mask_START  (9)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_cont_mask_END    (9)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_l_e_mask_START   (10)
#define SOC_DSS_WCH_DMA_BUF_CTRL_dma_buf_l_e_mask_END     (10)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_CPU_CTL_UNION
 �ṹ˵��  : DMA_BUF_CPU_CTL �Ĵ����ṹ���塣��ַƫ����:0x0804����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF ����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_ctl : 1;  /* bit[0]   : ������ */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_CTL_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_CTL_dma_buf_cpu_ctl_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_CTL_dma_buf_cpu_ctl_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_CPU_START_UNION
 �ṹ˵��  : DMA_BUF_CPU_START �Ĵ����ṹ���塣��ַƫ����:0x0808����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF ���������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_start : 1;  /* bit[0]   : ������ */
        unsigned int  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_START_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_START_dma_buf_cpu_start_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_START_dma_buf_cpu_start_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_CPU_ADDR_UNION
 �ṹ˵��  : DMA_BUF_CPU_ADDR �Ĵ����ṹ���塣��ַƫ����:0x080C����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF ��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_addr : 9;  /* bit[0-8] : ������ */
        unsigned int  reserved         : 22; /* bit[9-30]: ���� */
        unsigned int  dma_buf_cpu_rw   : 1;  /* bit[31]  : ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_ADDR_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_ADDR_dma_buf_cpu_addr_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_ADDR_dma_buf_cpu_addr_END    (8)
#define SOC_DSS_WCH_DMA_BUF_CPU_ADDR_dma_buf_cpu_rw_START    (31)
#define SOC_DSS_WCH_DMA_BUF_CPU_ADDR_dma_buf_cpu_rw_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_UNION
 �ṹ˵��  : DMA_BUF_CPU_RDATA0 �Ĵ����ṹ���塣��ַƫ����:0x0810����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF �����ݶ˿ڼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_rdata0 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_dma_buf_cpu_rdata0_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA0_dma_buf_cpu_rdata0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_UNION
 �ṹ˵��  : DMA_BUF_CPU_RDATA1 �Ĵ����ṹ���塣��ַƫ����:0x814����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF �����ݶ˿ڼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_rdata1 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_dma_buf_cpu_rdata1_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA1_dma_buf_cpu_rdata1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_UNION
 �ṹ˵��  : DMA_BUF_CPU_RDATA2 �Ĵ����ṹ���塣��ַƫ����:0x818����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF �����ݶ˿ڼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_rdata2 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_dma_buf_cpu_rdata2_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA2_dma_buf_cpu_rdata2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_UNION
 �ṹ˵��  : DMA_BUF_CPU_RDATA3 �Ĵ����ṹ���塣��ַƫ����:0x81C����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF �����ݶ˿ڼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_rdata3 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_dma_buf_cpu_rdata3_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_RDATA3_dma_buf_cpu_rdata3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_UNION
 �ṹ˵��  : DMA_BUF_CPU_WDATA0 �Ĵ����ṹ���塣��ַƫ����:0x820����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF д���ݶ˿ڼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_wdata0 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_dma_buf_cpu_wdata0_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA0_dma_buf_cpu_wdata0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_UNION
 �ṹ˵��  : DMA_BUF_CPU_WDATA1 �Ĵ����ṹ���塣��ַƫ����:0x824����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF д���ݶ˿ڼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_wdata1 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_dma_buf_cpu_wdata1_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA1_dma_buf_cpu_wdata1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_UNION
 �ṹ˵��  : DMA_BUF_CPU_WDATA2 �Ĵ����ṹ���塣��ַƫ����:0x828����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF д���ݶ˿ڼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_wdata2 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_dma_buf_cpu_wdata2_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA2_dma_buf_cpu_wdata2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_UNION
 �ṹ˵��  : DMA_BUF_CPU_WDATA3 �Ĵ����ṹ���塣��ַƫ����:0x82C����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF д���ݶ˿ڼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_cpu_wdata3 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_dma_buf_cpu_wdata3_START  (0)
#define SOC_DSS_WCH_DMA_BUF_CPU_WDATA3_dma_buf_cpu_wdata3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_REQ_END_UNION
 �ṹ˵��  : DMA_REQ_END �Ĵ����ṹ���塣��ַƫ����:0x830����ֵ:0x00000000�����:32
 �Ĵ���˵��: MMU TLB �����ݶ˿ڼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_req_end : 1;  /* bit[0]   : ������ */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_REQ_END_UNION;
#endif
#define SOC_DSS_WCH_DMA_REQ_END_dma_req_end_START  (0)
#define SOC_DSS_WCH_DMA_REQ_END_dma_req_end_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_DBGCFG_UNION
 �ṹ˵��  : DMA_BUF_DBGCFG �Ĵ����ṹ���塣��ַƫ����:0x834����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF ���ԼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_dbgcfg : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBGCFG_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBGCFG_dma_buf_dbgcfg_START  (0)
#define SOC_DSS_WCH_DMA_BUF_DBGCFG_dma_buf_dbgcfg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_DBG0_UNION
 �ṹ˵��  : DMA_BUF_DBG0 �Ĵ����ṹ���塣��ַƫ����:0x838����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF����ֻ���Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_dbg0 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG0_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG0_dma_buf_dbg0_START  (0)
#define SOC_DSS_WCH_DMA_BUF_DBG0_dma_buf_dbg0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_DBG1_UNION
 �ṹ˵��  : DMA_BUF_DBG1 �Ĵ����ṹ���塣��ַƫ����:0x83C����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF����ֻ���Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_dbg1 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG1_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG1_dma_buf_dbg1_START  (0)
#define SOC_DSS_WCH_DMA_BUF_DBG1_dma_buf_dbg1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_DBG2_UNION
 �ṹ˵��  : DMA_BUF_DBG2 �Ĵ����ṹ���塣��ַƫ����:0x840����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF����ֻ���Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_dbg2 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG2_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG2_dma_buf_dbg2_START  (0)
#define SOC_DSS_WCH_DMA_BUF_DBG2_dma_buf_dbg2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_DBG3_UNION
 �ṹ˵��  : DMA_BUF_DBG3 �Ĵ����ṹ���塣��ַƫ����:0x844����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF����ֻ���Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_dbg3 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG3_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG3_dma_buf_dbg3_START  (0)
#define SOC_DSS_WCH_DMA_BUF_DBG3_dma_buf_dbg3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_DBG4_UNION
 �ṹ˵��  : DMA_BUF_DBG4 �Ĵ����ṹ���塣��ַƫ����:0x848����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF����ֻ���Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_dbg4 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG4_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG4_dma_buf_dbg4_START  (0)
#define SOC_DSS_WCH_DMA_BUF_DBG4_dma_buf_dbg4_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_DBG5_UNION
 �ṹ˵��  : DMA_BUF_DBG5 �Ĵ����ṹ���塣��ַƫ����:0x84C����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF����ֻ���Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_dbg5 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_DSS_WCH_DMA_BUF_DBG5_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_DBG5_dma_buf_dbg5_START  (0)
#define SOC_DSS_WCH_DMA_BUF_DBG5_dma_buf_dbg5_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_SIZE_UNION
 �ṹ˵��  : DMA_BUF_SIZE �Ĵ����ṹ���塣��ַƫ����:0x850����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͼ���С
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_img_width  : 13; /* bit[0-12] : WDMA_BUF�������Чͼ���ȣ�������Ϊ��λ����һ���á� */
        unsigned int  reserved_0         : 3;  /* bit[13-15]: ���� */
        unsigned int  dma_buf_img_height : 13; /* bit[16-28]: WDMA_BUF�������Чͼ��߶ȣ�����Ϊ��λ����һ���á� */
        unsigned int  reserved_1         : 3;  /* bit[29-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_BUF_SIZE_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_SIZE_dma_buf_img_width_START   (0)
#define SOC_DSS_WCH_DMA_BUF_SIZE_dma_buf_img_width_END     (12)
#define SOC_DSS_WCH_DMA_BUF_SIZE_dma_buf_img_height_START  (16)
#define SOC_DSS_WCH_DMA_BUF_SIZE_dma_buf_img_height_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_DMA_BUF_MEM_CTRL_UNION
 �ṹ˵��  : DMA_BUF_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0854����ֵ:0x00000000�����:32
 �Ĵ���˵��: DMA_BUF SRAM���ƼĴ�����TP��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_buf_mem_ctrl : 4;  /* bit[0-3] : �����üĴ���
                                                           [3] mem_ctrl_auto_en , �Զ�ģʽ���������ģʽѡ��,0�Զ�ģʽ��1�������ģʽ 
                                                           [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                           [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                           [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved         : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_WCH_DMA_BUF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_WCH_DMA_BUF_MEM_CTRL_dma_buf_mem_ctrl_START  (0)
#define SOC_DSS_WCH_DMA_BUF_MEM_CTRL_dma_buf_mem_ctrl_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_UNION
 �ṹ˵��  : AFBCE_HREG_PIC_BLKS �Ĵ����ṹ���塣��ַƫ����:0x0900����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͼ��16x16�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_pic_blks : 24; /* bit[0-23] : ͼ��16x16����-1����0��ʾ1��16x16�� */
        unsigned int  reserved       : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_afbce_pic_blks_START  (0)
#define SOC_DSS_WCH_AFBCE_HREG_PIC_BLKS_afbce_pic_blks_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_AFBCE_HREG_FORMAT_UNION
 �ṹ˵��  : AFBCE_HREG_FORMAT �Ĵ����ṹ���塣��ַƫ����:0x0904����ֵ:0x00050000�����:32
 �Ĵ���˵��: ͼ���ʽ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0            : 16; /* bit[0-15] : ���� */
        unsigned int  reserved_1            : 5;  /* bit[16-20]: bit[20] color transform, 1-enable, 0-disable��
                                                                 bit[19:16] pixel format
                                                                 0x0: R5G6B5
                                                                 0x1: R5G5B5A1
                                                                 0x2: R10G10B10A2
                                                                 0x3: reserved
                                                                 0x4: R8G8B8
                                                                 0x5: R8G8B8A8
                                                                 0x6: R4G4B4A4
                                                                 0x7: R8, ��֧��color transform
                                                                 0x8: R8G8, ��֧��color transform
                                                                 0x9: YUV420,��֧��color transform
                                                                 0xA: reserved
                                                                 0xB: YUV422,��֧��color transform
                                                                 0xC~0xF: reserved
                                                                 ע�������YUV422��ʽ����Ҫ���ó�0x8��������R8G8��ʽ��ѹ
                                                                 ��ʽ����ֵ��ο�0x1C, dma_pix_fmt�Ĵ��� */
        unsigned int  afbce_color_transform : 1;  /* bit[21]   : color transform, 1-enable, 0-disable�� */
        unsigned int  reserved_2            : 10; /* bit[22-31]: ���� */
    } reg;
} SOC_DSS_WCH_AFBCE_HREG_FORMAT_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_HREG_FORMAT_afbce_color_transform_START  (21)
#define SOC_DSS_WCH_AFBCE_HREG_FORMAT_afbce_color_transform_END    (21)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_UNION
 �ṹ˵��  : AFBCE_HREG_HDR_PTR_LO �Ĵ����ṹ���塣��ַƫ����:0x0908����ֵ:0x00000000�����:32
 �Ĵ���˵��: ѹ��Header��ʼ��ַ��λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_hdr_ptr_lo : 32; /* bit[0-31]: ѹ��Header��ʼ��ַ[31:0]����ַ64Byte���� */
    } reg;
} SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_afbce_hdr_ptr_lo_START  (0)
#define SOC_DSS_WCH_AFBCE_HREG_HDR_PTR_LO_afbce_hdr_ptr_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_UNION
 �ṹ˵��  : AFBCE_HREG_PLD_PTR_LO �Ĵ����ṹ���塣��ַƫ����:0x090C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ѹ��Payload��ʼ��ַ��λ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_payload_ptr_lo : 32; /* bit[0-31]: ѹ��Payload��ʼ��ַ[31:0]��32���ظ�ʽ��ʱ��Ϊ1024Byte����������16���ظ�ʽ��ʱ��512Byte�������� */
    } reg;
} SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_afbce_payload_ptr_lo_START  (0)
#define SOC_DSS_WCH_AFBCE_HREG_PLD_PTR_LO_afbce_payload_ptr_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_PICTURE_SIZE_UNION
 �ṹ˵��  : PICTURE_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0910����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͼ��ߴ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_block_height : 16; /* bit[0-15] : ��ѹ��ͼ��߶ȣ�ʵ����������1 */
        unsigned int  afbce_block_width  : 10; /* bit[16-25]: ��ѹ��ͼ���ȣ�ʵ����������1 */
        unsigned int  reserved           : 6;  /* bit[26-31]: ���� */
    } reg;
} SOC_DSS_WCH_PICTURE_SIZE_UNION;
#endif
#define SOC_DSS_WCH_PICTURE_SIZE_afbce_block_height_START  (0)
#define SOC_DSS_WCH_PICTURE_SIZE_afbce_block_height_END    (15)
#define SOC_DSS_WCH_PICTURE_SIZE_afbce_block_width_START   (16)
#define SOC_DSS_WCH_PICTURE_SIZE_afbce_block_width_END     (25)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_AFBCE_CTL_UNION
 �ṹ˵��  : AFBCE_CTL �Ĵ����ṹ���塣��ַƫ����:0x0914����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 1;  /* bit[0-0] : �ϲ���ch_afbce_en */
        unsigned int  reserved_1: 1;  /* bit[1-1] : �ϲ���ch_afbce_en */
        unsigned int  reserved_2: 1;  /* bit[2-2] : �ϲ���dma_rot */
        unsigned int  reserved_3: 29; /* bit[3-31]: ���� */
    } reg;
} SOC_DSS_WCH_AFBCE_CTL_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_HEADER_SRTIDE_UNION
 �ṹ˵��  : HEADER_SRTIDE �Ĵ����ṹ���塣��ַƫ����:0x0918����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_header_stride    : 14; /* bit[0-13] : can be used for decoding a sub picture of a full picture
                                                                  ������64byte�ı��� */
        unsigned int  afbce_header_start_pos : 2;  /* bit[14-15]: valid header in first burst
                                                                  2��b00����1����ʼ��Ч
                                                                  2��b01����2����ʼ��Ч
                                                                  2��b10����3����ʼ��Ч
                                                                  2��b11����4����ʼ��Ч */
        unsigned int  reserved               : 16; /* bit[16-31]:  */
    } reg;
} SOC_DSS_WCH_HEADER_SRTIDE_UNION;
#endif
#define SOC_DSS_WCH_HEADER_SRTIDE_afbce_header_stride_START     (0)
#define SOC_DSS_WCH_HEADER_SRTIDE_afbce_header_stride_END       (13)
#define SOC_DSS_WCH_HEADER_SRTIDE_afbce_header_start_pos_START  (14)
#define SOC_DSS_WCH_HEADER_SRTIDE_afbce_header_start_pos_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_PAYLOAD_STRIDE_UNION
 �ṹ˵��  : PAYLOAD_STRIDE �Ĵ����ṹ���塣��ַƫ����:0x091C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_payload_stride : 20; /* bit[0-19] : payload�Ļ��еĿ�� */
        unsigned int  reserved             : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_DSS_WCH_PAYLOAD_STRIDE_UNION;
#endif
#define SOC_DSS_WCH_PAYLOAD_STRIDE_afbce_payload_stride_START  (0)
#define SOC_DSS_WCH_PAYLOAD_STRIDE_afbce_payload_stride_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_ENC_OS_CFG_UNION
 �ṹ˵��  : ENC_OS_CFG �Ĵ����ṹ���塣��ַƫ����:0x0920����ֵ:0x00000007�����:32
 �Ĵ���˵��: OUSTANDING CFG
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_ddrw_os : 3;  /* bit[0-2] : VBIF MM���ӿڵ�outstanding���ã���ֵ+1Ϊʵ��outstandingֵ�����ֵ0x7 */
        unsigned int  reserved      : 29; /* bit[3-31]:  */
    } reg;
} SOC_DSS_WCH_ENC_OS_CFG_UNION;
#endif
#define SOC_DSS_WCH_ENC_OS_CFG_afbce_ddrw_os_START  (0)
#define SOC_DSS_WCH_ENC_OS_CFG_afbce_ddrw_os_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_AFBCE_MEM_CTRL_UNION
 �ṹ˵��  : AFBCE_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0924����ֵ:0x00000000�����:32
 �Ĵ���˵��: AFBCE SRAM���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_mem_ctrl_0 : 4;  /* bit[0-3]  : �����üĴ���,afbce input sp memory�͹����������
                                                            [3] mem_ctrl_auto_en , �Զ�ģʽ���������ģʽѡ��,0�Զ�ģʽ��1�������ģʽ 
                                                            [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                            [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                            [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  afbce_mem_ctrl_1 : 4;  /* bit[4-7]  : �����üĴ���,afbce payload sp memory�͹����������
                                                            [3] mem_ctrl_auto_en , �Զ�ģʽ���������ģʽѡ��,0�Զ�ģʽ��1�������ģʽ 
                                                            [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                            [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                            [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  afbce_mem_ctrl_2 : 4;  /* bit[8-11] : �����üĴ���,afbce header tp memory�͹����������
                                                            [3] mem_ctrl_auto_en , �Զ�ģʽ���������ģʽѡ��,0�Զ�ģʽ��1�������ģʽ 
                                                            [2]: �������ģʽ����Ч��Ϊ1��ʾ����Shut Downģʽ
                                                            [1]: �������ģʽ����Ч��Ϊ1��ʾ����Deep Sleepģʽ
                                                            [0]: �������ģʽ����Ч��Ϊ1��ʾ����Sleepģʽ */
        unsigned int  reserved         : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DSS_WCH_AFBCE_MEM_CTRL_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_0_START  (0)
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_0_END    (3)
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_1_START  (4)
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_1_END    (7)
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_2_START  (8)
#define SOC_DSS_WCH_AFBCE_MEM_CTRL_afbce_mem_ctrl_2_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_AFBCE_QOS_CFG_UNION
 �ṹ˵��  : AFBCE_QOS_CFG �Ĵ����ṹ���塣��ַƫ����:0x0928����ֵ:0x00000000�����:32
 �Ĵ���˵��: OUSTANDING CFG
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_qos_cfg : 3;  /* bit[0-2] : afbce��qos���üĴ��� */
        unsigned int  reserved      : 29; /* bit[3-31]:  */
    } reg;
} SOC_DSS_WCH_AFBCE_QOS_CFG_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_QOS_CFG_afbce_qos_cfg_START  (0)
#define SOC_DSS_WCH_AFBCE_QOS_CFG_afbce_qos_cfg_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_AFBCE_THRESHOLD_UNION
 �ṹ˵��  : AFBCE_THRESHOLD �Ĵ����ṹ���塣��ַƫ����:0x092C����ֵ:0x00000002�����:32
 �Ĵ���˵��: ���������ˮ�߼Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_threshold : 3;  /* bit[0-2] : afbce���������ˮ�߼Ĵ��� */
        unsigned int  reserved        : 29; /* bit[3-31]:  */
    } reg;
} SOC_DSS_WCH_AFBCE_THRESHOLD_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_THRESHOLD_afbce_threshold_START  (0)
#define SOC_DSS_WCH_AFBCE_THRESHOLD_afbce_threshold_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_UNION
 �ṹ˵��  : AFBCE_SCRAMBLE_MODE �Ĵ����ṹ���塣��ַƫ����:0x0930����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ַ��֯ģʽ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  afbce_scramble_mode : 2;  /* bit[0-1] : afbce��ַ��֯�Ĵ���
                                                              2'b00 ��scramble ����֮ǰ�Ĺ���
                                                              2'b01 scramble mode 1
                                                              2'b10 scramble mode 2
                                                              2'b11 reserved */
        unsigned int  reserved            : 30; /* bit[2-31]:  */
    } reg;
} SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_UNION;
#endif
#define SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_afbce_scramble_mode_START  (0)
#define SOC_DSS_WCH_AFBCE_SCRAMBLE_MODE_afbce_scramble_mode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_WCH_REG_DEFAULT_UNION
 �ṹ˵��  : REG_DEFAULT �Ĵ����ṹ���塣��ַƫ����:0x0A00����ֵ:0x00000000�����:32
 �Ĵ���˵��: ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reg_default : 1;  /* bit[0]   :  */
        unsigned int  reserved    : 31; /* bit[1-31]:  */
    } reg;
} SOC_DSS_WCH_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_WCH_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_WCH_REG_DEFAULT_reg_default_END    (0)






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

#endif /* end of soc_dss_wch_interface.h */
