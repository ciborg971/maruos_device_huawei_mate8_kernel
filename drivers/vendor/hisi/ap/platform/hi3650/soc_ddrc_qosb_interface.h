/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_ddrc_qosb_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:19:52
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DDRC_QOSB.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DDRC_QOSB_INTERFACE_H__
#define __SOC_DDRC_QOSB_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_DDRC_QOSB
 ****************************************************************************/
/* �Ĵ���˵����QOS_PUSH_CTRL������QosBuf Push���ܵļĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_PUSH_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_ADDR(base)       ((base) + (0x000))

/* �Ĵ���˵����QOS_ADPT_CTRL������QosBuf��adpt���ܡ�
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_ADPT_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_ADPT_CTRL_ADDR(base)       ((base) + (0x004))

/* �Ĵ���˵����QOS_FLUX_ID��QosBuf������ƥ��ID��
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_FLUX_ID_UNION */
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_ADDR(base, fids)   ((base) + (0x008+0x4*(fids)))

/* �Ĵ���˵����QOS_FLUX_ID_MASK��QosBuf������ͳ�Ƶ�ID��Mask�Ĵ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_UNION */
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_ADDR(base, fids)  ((base) + (0x024+0x4*(fids)))

/* �Ĵ���˵����QOS_FLUX_PRD��QosBuf������ͳ�����ڼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_FLUX_BDW_UNION */
#define SOC_DDRC_QOSB_QOSB_FLUX_BDW_ADDR(base, fgps)  ((base) + (0x040+0x4*(fgps)))

/* �Ĵ���˵����QOS_FLUX_LVL��QosBuf������ͳ��ˮ�ߡ�
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_FLUX_LVL_UNION */
#define SOC_DDRC_QOSB_QOSB_FLUX_LVL_ADDR(base)        ((base) + (0x060))

/* �Ĵ���˵����QOS_FLUX_EN��QosBuf������ͳ�ƹ���ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_FLUX_EN_UNION */
#define SOC_DDRC_QOSB_QOSB_FLUX_EN_ADDR(base)         ((base) + (0x064))

/* �Ĵ���˵����QOS_BANK_CTRL��QosBuf��bank rotating���ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_BANK_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_BANK_CTRL_ADDR(base, chans)  ((base) + (0x068+0x4*(chans)))

/* �Ĵ���˵����QOS_GREEN_CTRL��QosBuf����ɫͨ�����ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_GREEN_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_GREEN_CTRL_ADDR(base, chans)  ((base) + (0x078+0x4*(chans)))

/* �Ĵ���˵����QOS_BUF_BYP��QosBuf��bypass���ܿ��ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_BUF_BYP_UNION */
#define SOC_DDRC_QOSB_QOSB_BUF_BYP_ADDR(base)         ((base) + (0x088))

/* �Ĵ���˵����QOS_WBUF_CTRL��QosBuf��д�������ȼ��������ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_WBUF_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_ADDR(base, chans)  ((base) + (0x08C+0x4*(chans)))

/* �Ĵ���˵����QOSB_WRTOUT��QosBuf��д����timeout���üĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_WRTOUT0_UNION */
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_ADDR(base)         ((base) + (0x09C))

/* �Ĵ���˵����QOSB_WRTOUT��QosBuf��д����timeout���üĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_WRTOUT1_UNION */
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_ADDR(base)         ((base) + (0x0A0))

/* �Ĵ���˵����QOSB_WRTOUT��QosBuf��д����timeout���üĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_WRTOUT2_UNION */
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_ADDR(base)         ((base) + (0x0A4))

/* �Ĵ���˵����QOSB_WRTOUT��QosBuf��д����timeout���üĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_WRTOUT3_UNION */
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_ADDR(base)         ((base) + (0x0A8))

/* �Ĵ���˵����QOSB_RDTOUT��QosBuf�Ķ�����timeout���üĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_RDTOUT0_UNION */
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_ADDR(base)         ((base) + (0x0AC))

/* �Ĵ���˵����QOSB_RDTOUT��QosBuf�Ķ�����timeout���üĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_RDTOUT1_UNION */
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_ADDR(base)         ((base) + (0x0B0))

/* �Ĵ���˵����QOSB_RDTOUT��QosBuf�Ķ�����timeout���üĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_RDTOUT2_UNION */
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_ADDR(base)         ((base) + (0x0B4))

/* �Ĵ���˵����QOSB_RDTOUT��QosBuf�Ķ�����timeout���üĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_RDTOUT3_UNION */
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_ADDR(base)         ((base) + (0x0B8))

/* �Ĵ���˵����QOSB_WRTOUT��QosBuf��д����timeoutӳ����ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_UNION */
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_ADDR(base)      ((base) + (0x0BC))

/* �Ĵ���˵����QOSB_RDTOUT��QosBuf�Ķ�����timeoutӳ����ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_UNION */
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_ADDR(base)      ((base) + (0x0D0))

/* �Ĵ���˵����QOSB_WRTAGE��QosBuf��д����aging���üĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_WRAGE0_UNION */
#define SOC_DDRC_QOSB_QOSB_WRAGE0_ADDR(base)          ((base) + (0x0D4))

/* �Ĵ���˵����QOSB_WRTAGE��QosBuf��д����aging���üĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_WRAGE1_UNION */
#define SOC_DDRC_QOSB_QOSB_WRAGE1_ADDR(base)          ((base) + (0x0D8))

/* �Ĵ���˵����QOSB_WRTAGE��QosBuf�Ķ�����aging���üĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_RDAGE0_UNION */
#define SOC_DDRC_QOSB_QOSB_RDAGE0_ADDR(base)          ((base) + (0x0DC))

/* �Ĵ���˵����QOSB_WRTAGE��QosBuf�Ķ�����aging���üĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_RDAGE1_UNION */
#define SOC_DDRC_QOSB_QOSB_RDAGE1_ADDR(base)          ((base) + (0x0E0))

/* �Ĵ���˵����QOSB_WRAGE_MAP��QosBuf��д����agingӳ����ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_WRAGE_MAP_UNION */
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_ADDR(base)       ((base) + (0x0E4))

/* �Ĵ���˵����QOSB_RDAGE_MAP��QosBuf�Ķ�����agingӳ����ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_RDAGE_MAP_UNION */
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_ADDR(base)       ((base) + (0x0E8))

/* �Ĵ���˵����QOSB_ROWHIT_PRILVL��QosBuf��row hit���ȼ�ˮ�߼Ĵ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_UNION */
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ADDR(base)   ((base) + (0x0EC))

/* �Ĵ���˵����QOSB_ROWHIT_PRI��QosBuf��row hit���ȼ����ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_UNION */
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ADDR(base)      ((base) + (0x0F0))

/* �Ĵ���˵����QOS_ROWHIT_CTRL��QosBuf��row hit��ʹ�ܿ��ơ�
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ADDR(base)     ((base) + (0x0F4))

/* �Ĵ���˵����QOS_WRAM_CTRL��QosBuf��write buf��ram���ơ�
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_WRAM_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ADDR(base)       ((base) + (0x0F8))

/* �Ĵ���˵����QOS_CRAM_CTRL��QosBuf CID��RAM���ơ�
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_CRAM_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_ADDR(base)       ((base) + (0x0FC))

/* �Ĵ���˵����QOS_RDRRAM_CTRL��QosBuf��write buf��ram���ơ�
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ADDR(base)     ((base) + (0x100))

/* �Ĵ���˵����QOS_RAM_TMOD��QosBuf/RDR��RAM�Ķ˿������źżĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_RAM_TMOD_UNION */
#define SOC_DDRC_QOSB_QOSB_RAM_TMOD_ADDR(base)        ((base) + (0x104))

/* �Ĵ���˵����QOS_CKG_CFG��QosBuf��ʱ�ӿ��ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_CKG_CFG_UNION */
#define SOC_DDRC_QOSB_QOSB_CKG_CFG_ADDR(base)         ((base) + (0x108))

/* �Ĵ���˵����QOSB_DMC_LVL��QosBuf�Ľ���DMC��������߿��ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_DMC_LVL_UNION */
#define SOC_DDRC_QOSB_QOSB_DMC_LVL_ADDR(base, chans)  ((base) + (0x10C+0x4*(chans)))

/* �Ĵ���˵����QOSB_CFG_PERF��QosBuf����ͳ�Ƶ�ģʽ���üĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_CFG_PERF_UNION */
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_ADDR(base)        ((base) + (0x120))

/* �Ĵ���˵����QOSB_CMD_SUM��QosBuf����������ۻ��Ĵ���
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_CMD_SUM_UNION */
#define SOC_DDRC_QOSB_QOSB_CMD_SUM_ADDR(base)         ((base) + (0x124))

/* �Ĵ���˵����QOSB_SLOT_STAT0��QosBuf��queue��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_SLOT_STAT0_UNION */
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT0_ADDR(base)      ((base) + (0x128))

/* �Ĵ���˵����QOSB_SLOT_STAT0��QosBuf��queue��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_SLOT_STAT1_UNION */
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT1_ADDR(base)      ((base) + (0x12C))

/* �Ĵ���˵����QOSB_SLOT_STAT0��QosBuf��queue��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_SLOT_STAT2_UNION */
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT2_ADDR(base)      ((base) + (0x130))

/* �Ĵ���˵����QOSB_SLOT_STAT0��QosBuf��queue��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_SLOT_STAT3_UNION */
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT3_ADDR(base)      ((base) + (0x134))

/* �Ĵ���˵����QOSB_WBUF_STAT0��QosBuf��дbuf״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_WBUF_STAT0_UNION */
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT0_ADDR(base, chans)  ((base) + (0x140+0x4*(chans)))

/* �Ĵ���˵����QOSB_WBUF_STAT1��QosBuf��дbuf״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_WBUF_STAT1_UNION */
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT1_ADDR(base, chans)  ((base) + (0x150+0x4*(chans)))

/* �Ĵ���˵����QOSB_RDRBUF_STAT��Reorderģ���buf״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_UNION */
#define SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_ADDR(base, chans)  ((base) + (0x160+0x4*(chans)))

/* �Ĵ���˵����QOSB_INTMSK��QosBuf�ж����μĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_INTMSK_UNION */
#define SOC_DDRC_QOSB_QOSB_INTMSK_ADDR(base)          ((base) + (0x170))

/* �Ĵ���˵����QOSB_RINT��QosBufԭʼ�жϼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_RINT_UNION */
#define SOC_DDRC_QOSB_QOSB_RINT_ADDR(base)            ((base) + (0x174))

/* �Ĵ���˵����QOSB_INTSTS��QOSBUF�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_INTSTS_UNION */
#define SOC_DDRC_QOSB_QOSB_INTSTS_ADDR(base)          ((base) + (0x178))

/* �Ĵ���˵����QOSB_CMD_CNT��QOSBUF�е�ǰ�ж��������ͳ�ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_CMD_CNT_UNION */
#define SOC_DDRC_QOSB_QOSB_CMD_CNT_ADDR(base)         ((base) + (0x180))

/* �Ĵ���˵����QOSB_RNK_CNT��QOSBUF�е�ǰÿ��rank���ж��������ͳ�ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_RNK_CNT_UNION */
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_ADDR(base, chans)  ((base) + (0x190+0x4*(chans)))

/* �Ĵ���˵����QOSB_BNK_CNT0��QOSBUF�е�ǰÿ��Bank�ж��������ͳ�ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_BNK_CNT0_UNION */
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_ADDR(base, chans)  ((base) + (0x1A0+0x4*(chans)))

/* �Ĵ���˵����QOSB_BNK_CNT1��QOSBUF�е�ǰÿ��Bank�ж��������ͳ�ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_BNK_CNT1_UNION */
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_ADDR(base, chans)  ((base) + (0x1B0+0x4*(chans)))

/* �Ĵ���˵����QOSB_BNK_CNT2��QOSBUF�е�ǰÿ��Bank�ж��������ͳ�ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_BNK_CNT2_UNION */
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_ADDR(base, chans)  ((base) + (0x1C0+0x4*(chans)))

/* �Ĵ���˵����QOSB_BNK_CNT3��QOSBUF�е�ǰÿ��Bank�ж��������ͳ�ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_BNK_CNT3_UNION */
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_ADDR(base, chans)  ((base) + (0x1D0+0x4*(chans)))

/* �Ĵ���˵����QOSB_OSTD_CNT��QOSBUF�е�ǰÿ��ͨ���ж���Oustanding�����ͳ�ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_OSTD_CNT_UNION */
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ADDR(base)        ((base) + (0x1E0))

/* �Ĵ���˵����QOSB_CMD_SUM��QosBufд����������ۻ��Ĵ���
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_UNION */
#define SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_ADDR(base)      ((base) + (0x1E4))

/* �Ĵ���˵����QOSB_CMD_SUM��QosBuf������������ۻ��Ĵ���
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_UNION */
#define SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_ADDR(base)      ((base) + (0x1E8))

/* �Ĵ���˵����QOSB_GRT_FIFO_STATUS��д���ݻ��MUX��Ӧ��grant fifo��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_UNION */
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_ADDR(base) ((base) + (0x1EC))

/* �Ĵ���˵����QOSB_TIMEOUT_MODE��QOSBUF��timeoutģʽѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_UNION */
#define SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_ADDR(base)    ((base) + (0x1F0))

/* �Ĵ���˵����QOSB_WBUF_PRI_CTRL��QOSBUF��дwbuf���ȼ��������ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_ADDR(base)   ((base) + (0x1F4))

/* �Ĵ���˵����QOSB_RHIT_CTRL��QOSBUF��rowhit���ȼ��������ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_RHIT_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_RHIT_CTRL_ADDR(base)       ((base) + (0x1F8))

/* �Ĵ���˵����QOSB_WBUF_MERG_CTRL��QOSBUF˫ͨ��дbuf�ϲ����ƼĴ�����
   λ����UNION�ṹ:  SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_UNION */
#define SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_ADDR(base)  ((base) + (0x1FC))





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
                     (1/1) register_DDRC_QOSB
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_PUSH_CTRL_UNION
 �ṹ˵��  : QOSB_PUSH_CTRL �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOS_PUSH_CTRL������QosBuf Push���ܵļĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  id_push_en   : 1;  /* bit[0]   : ͬID��pushʹ�ܡ�
                                                       0��push���ܹرգ�
                                                       1��push����ʹ�ܡ� */
        unsigned int  addr_push_en : 1;  /* bit[1]   : ͬ��ַ��pushʹ�ܡ�
                                                       0��push���ܹرգ�
                                                       1��push����ʹ�ܡ� */
        unsigned int  mid_push_en  : 1;  /* bit[2]   : ͬmid��pushʹ�ܡ�
                                                       0��push���ܹرգ�
                                                       1��push����ʹ�ܡ� */
        unsigned int  reserved     : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_PUSH_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_id_push_en_START    (0)
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_id_push_en_END      (0)
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_addr_push_en_START  (1)
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_addr_push_en_END    (1)
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_mid_push_en_START   (2)
#define SOC_DDRC_QOSB_QOSB_PUSH_CTRL_mid_push_en_END     (2)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_ADPT_CTRL_UNION
 �ṹ˵��  : QOSB_ADPT_CTRL �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000FF0�����:32
 �Ĵ���˵��: QOS_ADPT_CTRL������QosBuf��adpt���ܡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  adpt_en        : 1;  /* bit[0]    : Adapt����ʹ�ܿ��ơ�
                                                          0��adapt���ܹرգ�
                                                          1��adapt���ܴ򿪡� */
        unsigned int  reserved_0     : 3;  /* bit[1-3]  : ������ */
        unsigned int  adpt_share_cnt : 16; /* bit[4-19] : Adapt���ܵĵ�λ��������������ü������ݼ�Ϊ0ʱ��ÿ��cmd��Ӧ�ĸ�λ��������1�� */
        unsigned int  reserved_1     : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_ADPT_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_ADPT_CTRL_adpt_en_START         (0)
#define SOC_DDRC_QOSB_QOSB_ADPT_CTRL_adpt_en_END           (0)
#define SOC_DDRC_QOSB_QOSB_ADPT_CTRL_adpt_share_cnt_START  (4)
#define SOC_DDRC_QOSB_QOSB_ADPT_CTRL_adpt_share_cnt_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_FLUX_ID_UNION
 �ṹ˵��  : QOSB_FLUX_ID �Ĵ����ṹ���塣��ַƫ����:0x008+0x4*(fids)����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOS_FLUX_ID��QosBuf������ƥ��ID��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_id : 32; /* bit[0-31]: ��������ͳ�Ƶ�ƥ��ID��һ����0~6��ID��ÿ��ID��Ӧһ��ͳ���飻�������7��ID������ͬ������������Ĭ�ϵ�һ�顣 */
    } reg;
} SOC_DDRC_QOSB_QOSB_FLUX_ID_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_flux_id_START  (0)
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_flux_id_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_UNION
 �ṹ˵��  : QOSB_FLUX_ID_MASK �Ĵ����ṹ���塣��ַƫ����:0x024+0x4*(fids)����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOS_FLUX_ID_MASK��QosBuf������ͳ�Ƶ�ID��Mask�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_id_mask : 32; /* bit[0-31]: ��QOS_FLUX_ID�Ĵ�����Ӧ������ID��MASK��
                                                       0����ʾ��Ӧ��ID��bit�����ԣ�
                                                       1����ʾ��Ӧ��ID��bit����Ƚϡ� */
    } reg;
} SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_flux_id_mask_START  (0)
#define SOC_DDRC_QOSB_QOSB_FLUX_ID_MASK_flux_id_mask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_FLUX_BDW_UNION
 �ṹ˵��  : QOSB_FLUX_BDW �Ĵ����ṹ���塣��ַƫ����:0x040+0x4*(fgps)����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOS_FLUX_PRD��QosBuf������ͳ�����ڼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_bandwidth : 9;  /* bit[0-8] : ����ƽ������
                                                         ����ֵ=����ƽ������(Beats/Hz)*256=�������(MB/DMC_WIDTH/s)/����Ƶ�ʣ�MHz��*256
                                                         ���磺����Ƶ��Ϊ400MHz����ǰ�˿ڵ��������Ϊ1400MB/s��DMC_WIDTH=16byte�����������ֵΪ1400/16/400*256=56=0x38
                                                         ˵����
                                                         1.��256��Ŀ���Ǳ�������ƽ������ĸ�8λС����
                                                         2.���ƺ��˲ʱ������ܻᳬ��������������ķ�Χȡ���ڴ������޵����ã�
                                                         3.���ƺ�ĳ�ʱ��ƽ������С�ڵ�������ƽ������ */
        unsigned int  reserved       : 23; /* bit[9-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_FLUX_BDW_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_FLUX_BDW_flux_bandwidth_START  (0)
#define SOC_DDRC_QOSB_QOSB_FLUX_BDW_flux_bandwidth_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_FLUX_LVL_UNION
 �ṹ˵��  : QOSB_FLUX_LVL �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOS_FLUX_LVL��QosBuf������ͳ��ˮ�ߡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_lvl : 20; /* bit[0-19] : �������ޣ�
                                                    ����ֵ=��������(Beats)��
                                                    ˵����
                                                    ���Խ���������Ʒ�ʽ��Ч�ɻ��ڻ������ڵ��������ƣ��������޾����˻�������Լ������ڵ�������������������(Beats)/����ƽ������(Beats/Hz)=������ȣ�cycle�����������õ�����ƽ������̶�������£���������Խ�󣬻���Խ���Կ���ǰ��˲ʱ����仯Խ�����У���ʱ����ƺ��ƽ������ҲԽ�ӽ����õ�����ƽ�����������ƺ��˲ʱ����ı仯Ҳ���ܻ�Խ���ҡ�
                                                    ������ͳ�Ƽ��������ڴ�������ʱ������Ӧ����������ȼ���Ϊ��ͣ���С�ڴ������ʱ�������ȼ�ά�ֲ��䡣 */
        unsigned int  reserved : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_FLUX_LVL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_FLUX_LVL_flux_lvl_START  (0)
#define SOC_DDRC_QOSB_QOSB_FLUX_LVL_flux_lvl_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_FLUX_EN_UNION
 �ṹ˵��  : QOSB_FLUX_EN �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOS_FLUX_EN��QosBuf������ͳ�ƹ���ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  flux_en  : 1;  /* bit[0]   : ����ͳ�ƹ���ʹ�ܡ�
                                                   0����ʾ����ͳ�ƹ��ܹرգ�
                                                   1����ʾ����ͳ�ƹ���ʹ�ܡ� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_FLUX_EN_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_FLUX_EN_flux_en_START   (0)
#define SOC_DDRC_QOSB_QOSB_FLUX_EN_flux_en_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_BANK_CTRL_UNION
 �ṹ˵��  : QOSB_BANK_CTRL �Ĵ����ṹ���塣��ַƫ����:0x068+0x4*(chans)����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOS_BANK_CTRL��QosBuf��bank rotating���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ba_intleav_en : 1;  /* bit[0]   : QosBuf��bank rotatingʹ�ܿ��ơ�
                                                        0��Bank rotating���ܹر�
                                                        1��Bank rotating����ʹ�� */
        unsigned int  reserved_0    : 3;  /* bit[1-3] :  */
        unsigned int  ba_cnt_lvl    : 4;  /* bit[4-7] : Bank��ͻˮ�����ã���ÿ��bank��������ڸ�ˮ��ʱ����Ϊ��bank��ͻ��������Ϊû��bank��ͻ�� */
        unsigned int  reserved_1    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_BANK_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BANK_CTRL_ba_intleav_en_START  (0)
#define SOC_DDRC_QOSB_QOSB_BANK_CTRL_ba_intleav_en_END    (0)
#define SOC_DDRC_QOSB_QOSB_BANK_CTRL_ba_cnt_lvl_START     (4)
#define SOC_DDRC_QOSB_QOSB_BANK_CTRL_ba_cnt_lvl_END       (7)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_GREEN_CTRL_UNION
 �ṹ˵��  : QOSB_GREEN_CTRL �Ĵ����ṹ���塣��ַƫ����:0x078+0x4*(chans)����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOS_GREEN_CTRL��QosBuf����ɫͨ�����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  green_en  : 1;  /* bit[0]   : ��ɫͨ������ʹ�ܡ���ע�⣬����û�н�ͨ���ֿ����ƣ�������Ҫ�Ż���
                                                    0����ʾ�ù��ܹرգ�
                                                    1����ʾ�ù���ʹ�ܡ� */
        unsigned int  reserved_0: 3;  /* bit[1-3] : ������ */
        unsigned int  green_lvl : 4;  /* bit[4-7] : ��ɫͨ��ˮ�ߡ����ڸ�ˮ�����ϵĿ�λ����ɫͨ��Ԥ������dmc��queueΪ12��ˮ����Ϊ9����10��11Ϊ��ɫͨ��Ԥ����
                                                    ע�⣺������ˮ�����⣬������ΪNʱ��ʵ��ͨ�����������ΪN+1�����⣬�üĴ��������ڷ��ʹ����н��ж�̬���á� */
        unsigned int  reserved_1: 24; /* bit[8-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_GREEN_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_GREEN_CTRL_green_en_START   (0)
#define SOC_DDRC_QOSB_QOSB_GREEN_CTRL_green_en_END     (0)
#define SOC_DDRC_QOSB_QOSB_GREEN_CTRL_green_lvl_START  (4)
#define SOC_DDRC_QOSB_QOSB_GREEN_CTRL_green_lvl_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_BUF_BYP_UNION
 �ṹ˵��  : QOSB_BUF_BYP �Ĵ����ṹ���塣��ַƫ����:0x088����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOS_BUF_BYP��QosBuf��bypass���ܿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_buf_byp : 2;  /* bit[0-1] : Qos buf��bypass���ơ�
                                                      X0����ʾǿ�Ʒ�bypass�������00��10ʱ���������Ҫ����qosbuf��
                                                      01����ʾ����dmc��queue��״̬���Զ������Ƿ�bypass��
                                                      11����ʾǿ��byapss���������������qosbuf
                                                      ��ע�⣺��Щģʽ�ڷ��ʿ�ʼ֮ǰ����Ҫ���ã��������ڷ��ʹ����н��ж�̬���ã� */
        unsigned int  reserved    : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_BUF_BYP_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BUF_BYP_qos_buf_byp_START  (0)
#define SOC_DDRC_QOSB_QOSB_BUF_BYP_qos_buf_byp_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_WBUF_CTRL_UNION
 �ṹ˵��  : QOSB_WBUF_CTRL �Ĵ����ṹ���塣��ַƫ����:0x08C+0x4*(chans)����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOS_WBUF_CTRL��QosBuf��д�������ȼ��������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wbuf_lvl0    : 8;  /* bit[0-7]  : wbuf��ˮ��0��������ĸ����������´�����ˮ��ʱ������д��������ȼ����ᱻ��Ϊ��͡���ע�⣬���ˮ�߲��ܶ�̬���ã�������ܵ���дbuf����Ӧ����ʧЧ�� */
        unsigned int  wbuf_lvl1    : 8;  /* bit[8-15] : wbuf��ˮ��1��������ĸ����������ϴ�����ˮ�ߣ����������´�����ˮ�ߣ�������д��������ȼ��������wbuf_pri1����������Ϊwbuf_pri1���������wbuf_pri1�������ȼ��ָ�����ע�⣬���ˮ�߲��ܶ�̬���ã�������ܵ���дbuf����Ӧ����ʧЧ�� */
        unsigned int  wbuf_pri1    : 3;  /* bit[16-18]: wbuf��ˮ��1��Ӧ�����ȼ��� */
        unsigned int  reserved     : 1;  /* bit[19]   : ������ */
        unsigned int  wbuf_lvl2    : 8;  /* bit[20-27]: wbuf��ˮ��2��������ĸ����������ϴ�����ˮ�ߣ�������д��������ȼ��������wbuf_pri2����������Ϊwbuf_pri2���������wbuf_pri2�������ȼ��ָ�����ע�⣬���ˮ�߲��ܶ�̬���ã�������ܵ���дbuf����Ӧ����ʧЧ�� */
        unsigned int  wbuf_pri2    : 3;  /* bit[28-30]: wbuf��ˮ��2��Ӧ�����ȼ��� */
        unsigned int  wbuf_ptun_en : 1;  /* bit[31]   : д�ŵ�������ʹ�ܡ�
                                                        0����ʾ�ù��ܹرգ�
                                                        1����ʾ�ù���ʹ�ܡ� */
    } reg;
} SOC_DDRC_QOSB_QOSB_WBUF_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl0_START     (0)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl0_END       (7)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl1_START     (8)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl1_END       (15)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_pri1_START     (16)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_pri1_END       (18)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl2_START     (20)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_lvl2_END       (27)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_pri2_START     (28)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_pri2_END       (30)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_ptun_en_START  (31)
#define SOC_DDRC_QOSB_QOSB_WBUF_CTRL_wbuf_ptun_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_WRTOUT0_UNION
 �ṹ˵��  : QOSB_WRTOUT0 �Ĵ����ṹ���塣��ַƫ����:0x09C����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_WRTOUT��QosBuf��д����timeout���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_tout0 : 8;  /* bit[0-7]  : д����timeout���ã���λ0����
                                                    0x0����ֹtimeout���ܣ�
                                                    0x1��0xFF��n*4��ʱ�����ڣ�
                                                    ע�⣺
                                                    timeout����Ϊ8bits����ʵ�ʼ���Ϊ10bits��������λ�̶�Ϊ�㡣 */
        unsigned int  wr_tout1 : 8;  /* bit[8-15] : д����timeout���ã���λ1����
                                                    ���÷�ʽͬwr_tout0�� */
        unsigned int  wr_tout2 : 8;  /* bit[16-23]: д����timeout���ã���λ2����
                                                    ���÷�ʽͬwr_tout0�� */
        unsigned int  wr_tout3 : 8;  /* bit[24-31]: д����timeout���ã���λ3����
                                                    ���÷�ʽͬwr_tout0�� */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRTOUT0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout0_START  (0)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout0_END    (7)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout1_START  (8)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout1_END    (15)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout2_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout2_END    (23)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout3_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRTOUT0_wr_tout3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_WRTOUT1_UNION
 �ṹ˵��  : QOSB_WRTOUT1 �Ĵ����ṹ���塣��ַƫ����:0x0A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_WRTOUT��QosBuf��д����timeout���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_tout4 : 8;  /* bit[0-7]  : д����timeout���ã���λ4����
                                                    ���÷�ʽͬwr_tout0�� */
        unsigned int  wr_tout5 : 8;  /* bit[8-15] : д����timeout���ã���λ5����
                                                    ���÷�ʽͬwr_tout0�� */
        unsigned int  wr_tout6 : 8;  /* bit[16-23]: д����timeout���ã���λ6����
                                                    ���÷�ʽͬwr_tout0�� */
        unsigned int  wr_tout7 : 8;  /* bit[24-31]: д����timeout���ã���λ7����
                                                    ���÷�ʽͬwr_tout0�� */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRTOUT1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout4_START  (0)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout4_END    (7)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout5_START  (8)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout5_END    (15)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout6_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout6_END    (23)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout7_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRTOUT1_wr_tout7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_WRTOUT2_UNION
 �ṹ˵��  : QOSB_WRTOUT2 �Ĵ����ṹ���塣��ַƫ����:0x0A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_WRTOUT��QosBuf��д����timeout���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_tout8  : 8;  /* bit[0-7]  : д����timeout���ã���λ8����
                                                     ���÷�ʽͬwr_tout0�� */
        unsigned int  wr_tout9  : 8;  /* bit[8-15] : д����timeout���ã���λ9����
                                                     ���÷�ʽͬwr_tout0�� */
        unsigned int  wr_tout10 : 8;  /* bit[16-23]: д����timeout���ã���λ10����
                                                     ���÷�ʽͬwr_tout0�� */
        unsigned int  wr_tout11 : 8;  /* bit[24-31]: д����timeout���ã���λ11����
                                                     ���÷�ʽͬwr_tout0�� */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRTOUT2_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout8_START   (0)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout8_END     (7)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout9_START   (8)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout9_END     (15)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout10_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout10_END    (23)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout11_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRTOUT2_wr_tout11_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_WRTOUT3_UNION
 �ṹ˵��  : QOSB_WRTOUT3 �Ĵ����ṹ���塣��ַƫ����:0x0A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_WRTOUT��QosBuf��д����timeout���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_tout12 : 8;  /* bit[0-7]  : д����timeout���ã���λ12����
                                                     ���÷�ʽͬwr_tout0�� */
        unsigned int  wr_tout13 : 8;  /* bit[8-15] : д����timeout���ã���λ13����
                                                     ���÷�ʽͬwr_tout0�� */
        unsigned int  wr_tout14 : 8;  /* bit[16-23]: д����timeout���ã���λ14����
                                                     ���÷�ʽͬwr_tout0�� */
        unsigned int  wr_tout15 : 8;  /* bit[24-31]: д����timeout���ã���λ15����
                                                     ���÷�ʽͬwr_tout0�� */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRTOUT3_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout12_START  (0)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout12_END    (7)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout13_START  (8)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout13_END    (15)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout14_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout14_END    (23)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout15_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRTOUT3_wr_tout15_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_RDTOUT0_UNION
 �ṹ˵��  : QOSB_RDTOUT0 �Ĵ����ṹ���塣��ַƫ����:0x0AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_RDTOUT��QosBuf�Ķ�����timeout���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_tout0 : 8;  /* bit[0-7]  : ������timeout���ã���λ0����
                                                    0x0����ֹtimeout���ܣ�
                                                    0x1��0xFF��n*4��ʱ�����ڣ�
                                                    ע�⣺
                                                    timeout����Ϊ8bits����ʵ�ʼ���Ϊ10bits��������λ�̶�Ϊ�㡣 */
        unsigned int  rd_tout1 : 8;  /* bit[8-15] : ������timeout���ã���λ1����
                                                    ���÷�ʽͬrd_tout0�� */
        unsigned int  rd_tout2 : 8;  /* bit[16-23]: ������timeout���ã���λ2����
                                                    ���÷�ʽͬrd_tout0�� */
        unsigned int  rd_tout3 : 8;  /* bit[24-31]: ������timeout���ã���λ3����
                                                    ���÷�ʽͬrd_tout0�� */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDTOUT0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout0_START  (0)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout0_END    (7)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout1_START  (8)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout1_END    (15)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout2_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout2_END    (23)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout3_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDTOUT0_rd_tout3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_RDTOUT1_UNION
 �ṹ˵��  : QOSB_RDTOUT1 �Ĵ����ṹ���塣��ַƫ����:0x0B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_RDTOUT��QosBuf�Ķ�����timeout���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_tout4 : 8;  /* bit[0-7]  : ������timeout���ã���λ4����
                                                    ���÷�ʽͬrd_tout0�� */
        unsigned int  rd_tout5 : 8;  /* bit[8-15] : ������timeout���ã���λ5����
                                                    ���÷�ʽͬrd_tout0�� */
        unsigned int  rd_tout6 : 8;  /* bit[16-23]: ������timeout���ã���λ6����
                                                    ���÷�ʽͬrd_tout0�� */
        unsigned int  rd_tout7 : 8;  /* bit[24-31]: ������timeout���ã���λ7����
                                                    ���÷�ʽͬrd_tout0�� */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDTOUT1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout4_START  (0)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout4_END    (7)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout5_START  (8)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout5_END    (15)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout6_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout6_END    (23)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout7_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDTOUT1_rd_tout7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_RDTOUT2_UNION
 �ṹ˵��  : QOSB_RDTOUT2 �Ĵ����ṹ���塣��ַƫ����:0x0B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_RDTOUT��QosBuf�Ķ�����timeout���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_tout8  : 8;  /* bit[0-7]  : ������timeout���ã���λ8����
                                                     ���÷�ʽͬrd_tout0�� */
        unsigned int  rd_tout9  : 8;  /* bit[8-15] : ������timeout���ã���λ9����
                                                     ���÷�ʽͬrd_tout0�� */
        unsigned int  rd_tout10 : 8;  /* bit[16-23]: ������timeout���ã���λ10����
                                                     ���÷�ʽͬrd_tout0�� */
        unsigned int  rd_tout11 : 8;  /* bit[24-31]: ������timeout���ã���λ11����
                                                     ���÷�ʽͬrd_tout0�� */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDTOUT2_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout8_START   (0)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout8_END     (7)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout9_START   (8)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout9_END     (15)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout10_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout10_END    (23)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout11_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDTOUT2_rd_tout11_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_RDTOUT3_UNION
 �ṹ˵��  : QOSB_RDTOUT3 �Ĵ����ṹ���塣��ַƫ����:0x0B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_RDTOUT��QosBuf�Ķ�����timeout���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_tout12 : 8;  /* bit[0-7]  : ������timeout���ã���λ12����
                                                     ���÷�ʽͬrd_tout0�� */
        unsigned int  rd_tout13 : 8;  /* bit[8-15] : ������timeout���ã���λ13����
                                                     ���÷�ʽͬrd_tout0�� */
        unsigned int  rd_tout14 : 8;  /* bit[16-23]: ������timeout���ã���λ14����
                                                     ���÷�ʽͬrd_tout0�� */
        unsigned int  rd_tout15 : 8;  /* bit[24-31]: ������timeout���ã���λ15����
                                                     ���÷�ʽͬrd_tout0�� */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDTOUT3_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout12_START  (0)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout12_END    (7)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout13_START  (8)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout13_END    (15)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout14_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout14_END    (23)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout15_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDTOUT3_rd_tout15_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_UNION
 �ṹ˵��  : QOSB_WRTOUT_MAP �Ĵ����ṹ���塣��ַƫ����:0x0BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_WRTOUT��QosBuf��д����timeoutӳ����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wrtout_map0 : 5;  /* bit[0-4]  : timeoutһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��wrtout_map0��ʾҪѡ���bit0��������ID�е�λ�á� */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  : ������ */
        unsigned int  wrtout_map1 : 5;  /* bit[8-12] : timeoutһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��wrtout_map1��ʾҪѡ���bit1��������ID�е�λ�á� */
        unsigned int  reserved_1  : 3;  /* bit[13-15]: ������ */
        unsigned int  wrtout_map2 : 5;  /* bit[16-20]: timeoutһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��wrtout_map2��ʾҪѡ���bit2��������ID�е�λ�á� */
        unsigned int  reserved_2  : 3;  /* bit[21-23]: ������ */
        unsigned int  wrtout_map3 : 5;  /* bit[24-28]: timeoutһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��wrtout_map3��ʾҪѡ���bit3��������ID�е�λ�á� */
        unsigned int  reserved_3  : 3;  /* bit[29-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map0_START  (0)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map0_END    (4)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map1_START  (8)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map1_END    (12)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map2_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map2_END    (20)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map3_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRTOUT_MAP_wrtout_map3_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_UNION
 �ṹ˵��  : QOSB_RDTOUT_MAP �Ĵ����ṹ���塣��ַƫ����:0x0D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_RDTOUT��QosBuf�Ķ�����timeoutӳ����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdtout_map0 : 5;  /* bit[0-4]  : timeoutһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��rdtout_map0��ʾҪѡ���bit0��������ID�е�λ�á� */
        unsigned int  reserved_0  : 3;  /* bit[5-7]  : ������ */
        unsigned int  rdtout_map1 : 5;  /* bit[8-12] : timeoutһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��rdtout_map1��ʾҪѡ���bit1��������ID�е�λ�á� */
        unsigned int  reserved_1  : 3;  /* bit[13-15]: ������ */
        unsigned int  rdtout_map2 : 5;  /* bit[16-20]: timeoutһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��rdtout_map2��ʾҪѡ���bit2��������ID�е�λ�á� */
        unsigned int  reserved_2  : 3;  /* bit[21-23]: ������ */
        unsigned int  rdtout_map3 : 5;  /* bit[24-28]: timeoutһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��rdtout_map3��ʾҪѡ���bit3��������ID�е�λ�á� */
        unsigned int  reserved_3  : 3;  /* bit[29-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map0_START  (0)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map0_END    (4)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map1_START  (8)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map1_END    (12)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map2_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map2_END    (20)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map3_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDTOUT_MAP_rdtout_map3_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_WRAGE0_UNION
 �ṹ˵��  : QOSB_WRAGE0 �Ĵ����ṹ���塣��ַƫ����:0x0D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_WRTAGE��QosBuf��д����aging���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_age_prd0 : 4;  /* bit[0-3]  : д�����ϻ�ʱ�����ã���λ0����
                                                       0x0����ֹAging���ܣ�
                                                       0x1��0xF��N��16��ʱ�����ڡ� */
        unsigned int  wr_age_prd1 : 4;  /* bit[4-7]  : д�����ϻ�ʱ�����ã���λ1����
                                                       ����˵����wr_age_prd0�� */
        unsigned int  wr_age_prd2 : 4;  /* bit[8-11] : д�����ϻ�ʱ�����ã���λ2����
                                                       ����˵����wr_age_prd0�� */
        unsigned int  wr_age_prd3 : 4;  /* bit[12-15]: д�����ϻ�ʱ�����ã���λ3����
                                                       ����˵����wr_age_prd0�� */
        unsigned int  wr_age_prd4 : 4;  /* bit[16-19]: д�����ϻ�ʱ�����ã���λ4����
                                                       ����˵����wr_age_prd0�� */
        unsigned int  wr_age_prd5 : 4;  /* bit[20-23]: д�����ϻ�ʱ�����ã���λ5����
                                                       ����˵����wr_age_prd0�� */
        unsigned int  wr_age_prd6 : 4;  /* bit[24-27]: д�����ϻ�ʱ�����ã���λ6����
                                                       ����˵����wr_age_prd0�� */
        unsigned int  wr_age_prd7 : 4;  /* bit[28-31]: д�����ϻ�ʱ�����ã���λ7����
                                                       ����˵����wr_age_prd0�� */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRAGE0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd0_START  (0)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd0_END    (3)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd1_START  (4)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd1_END    (7)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd2_START  (8)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd2_END    (11)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd3_START  (12)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd3_END    (15)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd4_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd4_END    (19)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd5_START  (20)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd5_END    (23)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd6_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd6_END    (27)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd7_START  (28)
#define SOC_DDRC_QOSB_QOSB_WRAGE0_wr_age_prd7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_WRAGE1_UNION
 �ṹ˵��  : QOSB_WRAGE1 �Ĵ����ṹ���塣��ַƫ����:0x0D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_WRTAGE��QosBuf��д����aging���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wr_age_prd8  : 4;  /* bit[0-3]  : д�����ϻ�ʱ�����ã���λ8����
                                                        ����˵����wr_age_prd0�� */
        unsigned int  wr_age_prd9  : 4;  /* bit[4-7]  : д�����ϻ�ʱ�����ã���λ9����
                                                        ����˵����wr_age_prd0�� */
        unsigned int  wr_age_prd10 : 4;  /* bit[8-11] : д�����ϻ�ʱ�����ã���λ10����
                                                        ����˵����wr_age_prd0�� */
        unsigned int  wr_age_prd11 : 4;  /* bit[12-15]: д�����ϻ�ʱ�����ã���λ11����
                                                        ����˵����wr_age_prd0�� */
        unsigned int  wr_age_prd12 : 4;  /* bit[16-19]: д�����ϻ�ʱ�����ã���λ12����
                                                        ����˵����wr_age_prd0�� */
        unsigned int  wr_age_prd13 : 4;  /* bit[20-23]: д�����ϻ�ʱ�����ã���λ13����
                                                        ����˵����wr_age_prd0�� */
        unsigned int  wr_age_prd14 : 4;  /* bit[24-27]: д�����ϻ�ʱ�����ã���λ14����
                                                        ����˵����wr_age_prd0�� */
        unsigned int  wr_age_prd15 : 4;  /* bit[28-31]: д�����ϻ�ʱ�����ã���λ15����
                                                        ����˵����wr_age_prd0�� */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRAGE1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd8_START   (0)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd8_END     (3)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd9_START   (4)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd9_END     (7)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd10_START  (8)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd10_END    (11)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd11_START  (12)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd11_END    (15)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd12_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd12_END    (19)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd13_START  (20)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd13_END    (23)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd14_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd14_END    (27)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd15_START  (28)
#define SOC_DDRC_QOSB_QOSB_WRAGE1_wr_age_prd15_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_RDAGE0_UNION
 �ṹ˵��  : QOSB_RDAGE0 �Ĵ����ṹ���塣��ַƫ����:0x0DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_WRTAGE��QosBuf�Ķ�����aging���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_age_prd0 : 4;  /* bit[0-3]  : �������ϻ�ʱ�����ã���λ0����
                                                       0x0����ֹAging���ܣ�
                                                       0x1��0xF��N��16��ʱ�����ڡ� */
        unsigned int  rd_age_prd1 : 4;  /* bit[4-7]  : �������ϻ�ʱ�����ã���λ1����
                                                       ����˵����rd_age_prd0�� */
        unsigned int  rd_age_prd2 : 4;  /* bit[8-11] : �������ϻ�ʱ�����ã���λ2����
                                                       ����˵����rd_age_prd0�� */
        unsigned int  rd_age_prd3 : 4;  /* bit[12-15]: �������ϻ�ʱ�����ã���λ3����
                                                       ����˵����rd_age_prd0�� */
        unsigned int  rd_age_prd4 : 4;  /* bit[16-19]: �������ϻ�ʱ�����ã���λ4����
                                                       ����˵����rd_age_prd0�� */
        unsigned int  rd_age_prd5 : 4;  /* bit[20-23]: �������ϻ�ʱ�����ã���λ5����
                                                       ����˵����rd_age_prd0�� */
        unsigned int  rd_age_prd6 : 4;  /* bit[24-27]: �������ϻ�ʱ�����ã���λ6����
                                                       ����˵����rd_age_prd0�� */
        unsigned int  rd_age_prd7 : 4;  /* bit[28-31]: �������ϻ�ʱ�����ã���λ7����
                                                       ����˵����rd_age_prd0�� */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDAGE0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd0_START  (0)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd0_END    (3)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd1_START  (4)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd1_END    (7)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd2_START  (8)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd2_END    (11)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd3_START  (12)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd3_END    (15)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd4_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd4_END    (19)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd5_START  (20)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd5_END    (23)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd6_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd6_END    (27)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd7_START  (28)
#define SOC_DDRC_QOSB_QOSB_RDAGE0_rd_age_prd7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_RDAGE1_UNION
 �ṹ˵��  : QOSB_RDAGE1 �Ĵ����ṹ���塣��ַƫ����:0x0E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_WRTAGE��QosBuf�Ķ�����aging���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rd_age_prd8  : 4;  /* bit[0-3]  : �������ϻ�ʱ�����ã���λ8����
                                                        ����˵����rd_age_prd0�� */
        unsigned int  rd_age_prd9  : 4;  /* bit[4-7]  : �������ϻ�ʱ�����ã���λ9����
                                                        ����˵����rd_age_prd0�� */
        unsigned int  rd_age_prd10 : 4;  /* bit[8-11] : �������ϻ�ʱ�����ã���λ10����
                                                        ����˵����rd_age_prd0�� */
        unsigned int  rd_age_prd11 : 4;  /* bit[12-15]: �������ϻ�ʱ�����ã���λ11����
                                                        ����˵����rd_age_prd0�� */
        unsigned int  rd_age_prd12 : 4;  /* bit[16-19]: �������ϻ�ʱ�����ã���λ12����
                                                        ����˵����rd_age_prd0�� */
        unsigned int  rd_age_prd13 : 4;  /* bit[20-23]: �������ϻ�ʱ�����ã���λ13����
                                                        ����˵����rd_age_prd0�� */
        unsigned int  rd_age_prd14 : 4;  /* bit[24-27]: �������ϻ�ʱ�����ã���λ14����
                                                        ����˵����rd_age_prd0�� */
        unsigned int  rd_age_prd15 : 4;  /* bit[28-31]: �������ϻ�ʱ�����ã���λ15����
                                                        ����˵����rd_age_prd0�� */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDAGE1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd8_START   (0)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd8_END     (3)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd9_START   (4)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd9_END     (7)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd10_START  (8)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd10_END    (11)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd11_START  (12)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd11_END    (15)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd12_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd12_END    (19)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd13_START  (20)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd13_END    (23)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd14_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd14_END    (27)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd15_START  (28)
#define SOC_DDRC_QOSB_QOSB_RDAGE1_rd_age_prd15_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_WRAGE_MAP_UNION
 �ṹ˵��  : QOSB_WRAGE_MAP �Ĵ����ṹ���塣��ַƫ����:0x0E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_WRAGE_MAP��QosBuf��д����agingӳ����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wrage_map0 : 5;  /* bit[0-4]  : agingһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��wrage_map0��ʾҪѡ���bit0��������ID�е�λ�á� */
        unsigned int  reserved_0 : 3;  /* bit[5-7]  : ������ */
        unsigned int  wrage_map1 : 5;  /* bit[8-12] : agingһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��wrage_map1��ʾҪѡ���bit1��������ID�е�λ�á� */
        unsigned int  reserved_1 : 3;  /* bit[13-15]: ������ */
        unsigned int  wrage_map2 : 5;  /* bit[16-20]: agingһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��wrage_map2��ʾҪѡ���bit2��������ID�е�λ�á� */
        unsigned int  reserved_2 : 3;  /* bit[21-23]: ������ */
        unsigned int  wrage_map3 : 5;  /* bit[24-28]: agingһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��wrage_map3��ʾҪѡ���bit3��������ID�е�λ�á� */
        unsigned int  reserved_3 : 3;  /* bit[29-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRAGE_MAP_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map0_START  (0)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map0_END    (4)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map1_START  (8)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map1_END    (12)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map2_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map2_END    (20)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map3_START  (24)
#define SOC_DDRC_QOSB_QOSB_WRAGE_MAP_wrage_map3_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_RDAGE_MAP_UNION
 �ṹ˵��  : QOSB_RDAGE_MAP �Ĵ����ṹ���塣��ַƫ����:0x0E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_RDAGE_MAP��QosBuf�Ķ�����agingӳ����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rdage_map0 : 5;  /* bit[0-4]  : agingһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��rdage_map0��ʾҪѡ���bit0��������ID�е�λ�á� */
        unsigned int  reserved_0 : 3;  /* bit[5-7]  : ������ */
        unsigned int  rdage_map1 : 5;  /* bit[8-12] : agingһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��rdage_map1��ʾҪѡ���bit1��������ID�е�λ�á� */
        unsigned int  reserved_1 : 3;  /* bit[13-15]: ������ */
        unsigned int  rdage_map2 : 5;  /* bit[16-20]: agingһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��rdage_map2��ʾҪѡ���bit2��������ID�е�λ�á� */
        unsigned int  reserved_2 : 3;  /* bit[21-23]: ������ */
        unsigned int  rdage_map3 : 5;  /* bit[24-28]: agingһ����Ϊ16����λ����ӳ�䷽����ID(������MID+ID+PORT_ID,�Ӹߵ���������MID,ID,PORT_ID)��ѡ��4bit����������4bit��ֵѡ���Ӧ�ĵ�λ��rdage_map3��ʾҪѡ���bit3��������ID�е�λ�á� */
        unsigned int  reserved_3 : 3;  /* bit[29-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDAGE_MAP_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map0_START  (0)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map0_END    (4)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map1_START  (8)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map1_END    (12)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map2_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map2_END    (20)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map3_START  (24)
#define SOC_DDRC_QOSB_QOSB_RDAGE_MAP_rdage_map3_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_UNION
 �ṹ˵��  : QOSB_ROWHIT_PRILVL �Ĵ����ṹ���塣��ַƫ����:0x0EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_ROWHIT_PRILVL��QosBuf��row hit���ȼ�ˮ�߼Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch0_rowhit_pri_lvl : 3;  /* bit[0-2]  : ͨ��0���ȼ�ˮ�ߣ�
                                                              ��ǰ���ȼ�����ch0_rohit_pri_lvlʱ�������ȼ��ᵽch0_rowhit_pri1��
                                                              ��ǰ���ȼ�����ch0_rohit_pri_lvlʱ�������ȼ��ᵽch0_rowhit_pri0�� */
        unsigned int  reserved_0         : 1;  /* bit[3]    : ������ */
        unsigned int  ch1_rowhit_pri_lvl : 3;  /* bit[4-6]  : ͨ��1���ȼ�ˮ�ߣ�
                                                              ��ǰ���ȼ�����ch1_rohit_pri_lvlʱ�������ȼ��ᵽch1_rowhit_pri1��
                                                              ��ǰ���ȼ�����ch1_rohit_pri_lvlʱ�������ȼ��ᵽch1_rowhit_pri0�� */
        unsigned int  reserved_1         : 1;  /* bit[7]    : ������ */
        unsigned int  ch2_rowhit_pri_lvl : 3;  /* bit[8-10] : ͨ��2���ȼ�ˮ�ߣ�
                                                              ��ǰ���ȼ�����ch2_rohit_pri_lvlʱ�������ȼ��ᵽch2_rowhit_pri1��
                                                              ��ǰ���ȼ�����ch2_rohit_pri_lvlʱ�������ȼ��ᵽch2_rowhit_pri0�� */
        unsigned int  reserved_2         : 1;  /* bit[11]   : ������ */
        unsigned int  ch3_rowhit_pri_lvl : 3;  /* bit[12-14]: ͨ��3���ȼ�ˮ�ߣ�
                                                              ��ǰ���ȼ�����ch3_rohit_pri_lvlʱ�������ȼ��ᵽch3_rowhit_pri1��
                                                              ��ǰ���ȼ�����ch3_rohit_pri_lvlʱ�������ȼ��ᵽch3_rowhit_pri0�� */
        unsigned int  reserved_3         : 17; /* bit[15-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch0_rowhit_pri_lvl_START  (0)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch0_rowhit_pri_lvl_END    (2)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch1_rowhit_pri_lvl_START  (4)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch1_rowhit_pri_lvl_END    (6)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch2_rowhit_pri_lvl_START  (8)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch2_rowhit_pri_lvl_END    (10)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch3_rowhit_pri_lvl_START  (12)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRILVL_ch3_rowhit_pri_lvl_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_UNION
 �ṹ˵��  : QOSB_ROWHIT_PRI �Ĵ����ṹ���塣��ַƫ����:0x0F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_ROWHIT_PRI��QosBuf��row hit���ȼ����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch0_rowhit_pri0 : 3;  /* bit[0-2]  : ���ch0_rowhit_pri_lvl��˵���� */
        unsigned int  reserved_0      : 1;  /* bit[3]    : ������ */
        unsigned int  ch0_rowhit_pri1 : 3;  /* bit[4-6]  : ���ch0_rowhit_pri_lvl��˵���� */
        unsigned int  reserved_1      : 1;  /* bit[7]    : ������ */
        unsigned int  ch1_rowhit_pri0 : 3;  /* bit[8-10] : ���ch1_rowhit_pri_lvl��˵���� */
        unsigned int  reserved_2      : 1;  /* bit[11]   : ������ */
        unsigned int  ch1_rowhit_pri1 : 3;  /* bit[12-14]: ���ch1_rowhit_pri_lvl��˵���� */
        unsigned int  reserved_3      : 1;  /* bit[15]   : ������ */
        unsigned int  ch2_rowhit_pri0 : 3;  /* bit[16-18]: ���ch2_rowhit_pri_lvl��˵���� */
        unsigned int  reserved_4      : 1;  /* bit[19]   : ������ */
        unsigned int  ch2_rowhit_pri1 : 3;  /* bit[20-22]: ���ch2_rowhit_pri_lvl��˵���� */
        unsigned int  reserved_5      : 1;  /* bit[23]   : ������ */
        unsigned int  ch3_rowhit_pri0 : 3;  /* bit[24-26]: ���ch3_rowhit_pri_lvl��˵���� */
        unsigned int  reserved_6      : 1;  /* bit[27]   : ������ */
        unsigned int  ch3_rowhit_pri1 : 3;  /* bit[28-30]: ���ch3_rowhit_pri_lvl��˵���� */
        unsigned int  reserved_7      : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch0_rowhit_pri0_START  (0)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch0_rowhit_pri0_END    (2)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch0_rowhit_pri1_START  (4)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch0_rowhit_pri1_END    (6)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch1_rowhit_pri0_START  (8)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch1_rowhit_pri0_END    (10)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch1_rowhit_pri1_START  (12)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch1_rowhit_pri1_END    (14)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch2_rowhit_pri0_START  (16)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch2_rowhit_pri0_END    (18)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch2_rowhit_pri1_START  (20)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch2_rowhit_pri1_END    (22)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch3_rowhit_pri0_START  (24)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch3_rowhit_pri0_END    (26)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch3_rowhit_pri1_START  (28)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_PRI_ch3_rowhit_pri1_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_UNION
 �ṹ˵��  : QOSB_ROWHIT_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOS_ROWHIT_CTRL��QosBuf��row hit��ʹ�ܿ��ơ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch0_row_hit_en   : 1;  /* bit[0]   : channel0 row hitʹ�ܿ��ƣ�
                                                           0��rowhit���ܹرգ�
                                                           1��rowhit���ܴ򿪣� */
        unsigned int  ch1_row_hit_en   : 1;  /* bit[1]   : channel1 row hitʹ�ܿ��ƣ�
                                                           0��rowhit���ܹرգ�
                                                           1��rowhit���ܴ򿪣� */
        unsigned int  ch2_row_hit_en   : 1;  /* bit[2]   : channel2 row hitʹ�ܿ��ƣ�
                                                           0��rowhit���ܹرգ�
                                                           1��rowhit���ܴ򿪣� */
        unsigned int  ch3_row_hit_en   : 1;  /* bit[3]   : channel3 row hitʹ�ܿ��ƣ�
                                                           0��rowhit���ܹرգ�
                                                           1��rowhit���ܴ򿪣� */
        unsigned int  ch0_dual_flow_en : 1;  /* bit[4]   : channel0��row hit��˫��ʹ�ܿ��ƣ�
                                                           0��˫�����ܹرգ�
                                                           1��˫�����ܴ򿪡� */
        unsigned int  ch1_dual_flow_en : 1;  /* bit[5]   : channel1��row hit��˫��ʹ�ܿ��ƣ�
                                                           0��˫�����ܹرգ�
                                                           1��˫�����ܴ򿪡� */
        unsigned int  ch2_dual_flow_en : 1;  /* bit[6]   : channel2��row hit��˫��ʹ�ܿ��ƣ�
                                                           0��˫�����ܹرգ�
                                                           1��˫�����ܴ򿪡� */
        unsigned int  ch3_dual_flow_en : 1;  /* bit[7]   : channel3��row hit��˫��ʹ�ܿ��ƣ�
                                                           0��˫�����ܹرգ�
                                                           1��˫�����ܴ򿪡� */
        unsigned int  reserved         : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch0_row_hit_en_START    (0)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch0_row_hit_en_END      (0)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch1_row_hit_en_START    (1)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch1_row_hit_en_END      (1)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch2_row_hit_en_START    (2)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch2_row_hit_en_END      (2)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch3_row_hit_en_START    (3)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch3_row_hit_en_END      (3)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch0_dual_flow_en_START  (4)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch0_dual_flow_en_END    (4)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch1_dual_flow_en_START  (5)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch1_dual_flow_en_END    (5)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch2_dual_flow_en_START  (6)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch2_dual_flow_en_END    (6)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch3_dual_flow_en_START  (7)
#define SOC_DDRC_QOSB_QOSB_ROWHIT_CTRL_ch3_dual_flow_en_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_WRAM_CTRL_UNION
 �ṹ˵��  : QOSB_WRAM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOS_WRAM_CTRL��QosBuf��write buf��ram���ơ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch0wramerrinj        : 2;  /* bit[0-1]  : channel0��write buf��ram�Ĵ���ע�롣 */
        unsigned int  ch1wramerrinj        : 2;  /* bit[2-3]  : channel1��write buf��ram�Ĵ���ע�롣 */
        unsigned int  ch2wramerrinj        : 2;  /* bit[4-5]  : channel2��write buf��ram�Ĵ���ע�롣 */
        unsigned int  ch3wramerrinj        : 2;  /* bit[6-7]  : channel3��write buf��ram�Ĵ���ע�롣 */
        unsigned int  reserved_0           : 8;  /* bit[8-15] : ������ */
        unsigned int  ch0_wbuf_one_bit_err : 1;  /* bit[16]   : channel0��write buf��ram��1bit ECC�����־�� */
        unsigned int  ch0_wbuf_two_bit_err : 1;  /* bit[17]   : channel0��write buf��ram��2bit ECC�����־�� */
        unsigned int  ch1_wbuf_one_bit_err : 1;  /* bit[18]   : channel1��write buf��ram��1bit ECC�����־�� */
        unsigned int  ch1_wbuf_two_bit_err : 1;  /* bit[19]   : channel1��write buf��ram��2bit ECC�����־�� */
        unsigned int  ch2_wbuf_one_bit_err : 1;  /* bit[20]   : channel2��write buf��ram��1bit ECC�����־�� */
        unsigned int  ch2_wbuf_two_bit_err : 1;  /* bit[21]   : channel2��write buf��ram��2bit ECC�����־�� */
        unsigned int  ch3_wbuf_one_bit_err : 1;  /* bit[22]   : channel3��write buf��ram��1bit ECC�����־�� */
        unsigned int  ch3_wbuf_two_bit_err : 1;  /* bit[23]   : channel3��write buf��ram��2bit ECC�����־�� */
        unsigned int  reserved_1           : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_WRAM_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0wramerrinj_START         (0)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0wramerrinj_END           (1)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1wramerrinj_START         (2)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1wramerrinj_END           (3)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2wramerrinj_START         (4)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2wramerrinj_END           (5)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3wramerrinj_START         (6)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3wramerrinj_END           (7)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0_wbuf_one_bit_err_START  (16)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0_wbuf_one_bit_err_END    (16)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0_wbuf_two_bit_err_START  (17)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch0_wbuf_two_bit_err_END    (17)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1_wbuf_one_bit_err_START  (18)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1_wbuf_one_bit_err_END    (18)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1_wbuf_two_bit_err_START  (19)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch1_wbuf_two_bit_err_END    (19)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2_wbuf_one_bit_err_START  (20)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2_wbuf_one_bit_err_END    (20)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2_wbuf_two_bit_err_START  (21)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch2_wbuf_two_bit_err_END    (21)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3_wbuf_one_bit_err_START  (22)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3_wbuf_one_bit_err_END    (22)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3_wbuf_two_bit_err_START  (23)
#define SOC_DDRC_QOSB_QOSB_WRAM_CTRL_ch3_wbuf_two_bit_err_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_CRAM_CTRL_UNION
 �ṹ˵��  : QOSB_CRAM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOS_CRAM_CTRL��QosBuf CID��RAM���ơ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cramerrinj       : 2;  /* bit[0-1] : cid ram�Ĵ���ע�롣 */
        unsigned int  reserved_0       : 2;  /* bit[2-3] : ������ */
        unsigned int  cram_one_bit_err : 1;  /* bit[4]   : cid ram��ram��1bit ECC�����־�� */
        unsigned int  cram_two_bit_err : 1;  /* bit[5]   : cid ram��ram��2bit ECC�����־�� */
        unsigned int  reserved_1       : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_CRAM_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cramerrinj_START        (0)
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cramerrinj_END          (1)
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cram_one_bit_err_START  (4)
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cram_one_bit_err_END    (4)
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cram_two_bit_err_START  (5)
#define SOC_DDRC_QOSB_QOSB_CRAM_CTRL_cram_two_bit_err_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_UNION
 �ṹ˵��  : QOSB_RDRRAM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOS_RDRRAM_CTRL��QosBuf��write buf��ram���ơ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch0_rdr_err_inj     : 2;  /* bit[0-1]  : channel0��rdr buf��ram�Ĵ���ע�롣 */
        unsigned int  ch1_rdr_err_inj     : 2;  /* bit[2-3]  : channel1��rdr buf��ram�Ĵ���ע�롣 */
        unsigned int  ch2_rdr_err_inj     : 2;  /* bit[4-5]  : channel2��rdr buf��ram�Ĵ���ע�롣 */
        unsigned int  ch3_rdr_err_inj     : 2;  /* bit[6-7]  : channel3��rdr buf��ram�Ĵ���ע�롣 */
        unsigned int  reserved_0          : 8;  /* bit[8-15] : ������ */
        unsigned int  ch0_rdr_one_bit_err : 1;  /* bit[16]   : channel0��rdr buf��ram��1bit ECC�����־�� */
        unsigned int  ch0_rdr_two_bit_err : 1;  /* bit[17]   : channel0��rdr buf��ram��2bit ECC�����־�� */
        unsigned int  ch1_rdr_one_bit_err : 1;  /* bit[18]   : channel1��rdr buf��ram��1bit ECC�����־�� */
        unsigned int  ch1_rdr_two_bit_err : 1;  /* bit[19]   : channel1��rdr buf��ram��2bit ECC�����־�� */
        unsigned int  ch2_rdr_one_bit_err : 1;  /* bit[20]   : channel2��rdr buf��ram��1bit ECC�����־�� */
        unsigned int  ch2_rdr_two_bit_err : 1;  /* bit[21]   : channel2��rdr buf��ram��2bit ECC�����־�� */
        unsigned int  ch3_rdr_one_bit_err : 1;  /* bit[22]   : channel3��rdr buf��ram��1bit ECC�����־�� */
        unsigned int  ch3_rdr_two_bit_err : 1;  /* bit[23]   : channel3��rdr buf��ram��2bit ECC�����־�� */
        unsigned int  reserved_1          : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_err_inj_START      (0)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_err_inj_END        (1)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_err_inj_START      (2)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_err_inj_END        (3)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_err_inj_START      (4)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_err_inj_END        (5)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_err_inj_START      (6)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_err_inj_END        (7)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_one_bit_err_START  (16)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_one_bit_err_END    (16)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_two_bit_err_START  (17)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch0_rdr_two_bit_err_END    (17)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_one_bit_err_START  (18)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_one_bit_err_END    (18)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_two_bit_err_START  (19)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch1_rdr_two_bit_err_END    (19)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_one_bit_err_START  (20)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_one_bit_err_END    (20)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_two_bit_err_START  (21)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch2_rdr_two_bit_err_END    (21)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_one_bit_err_START  (22)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_one_bit_err_END    (22)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_two_bit_err_START  (23)
#define SOC_DDRC_QOSB_QOSB_RDRRAM_CTRL_ch3_rdr_two_bit_err_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_RAM_TMOD_UNION
 �ṹ˵��  : QOSB_RAM_TMOD �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x000001A8�����:32
 �Ĵ���˵��: QOS_RAM_TMOD��QosBuf/RDR��RAM�Ķ˿������źżĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ram_tmod : 32; /* bit[0-31]: ���ݲ�ͬ�Ĺ������ã��ɺ궨�������ֵ�� */
    } reg;
} SOC_DDRC_QOSB_QOSB_RAM_TMOD_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RAM_TMOD_ram_tmod_START  (0)
#define SOC_DDRC_QOSB_QOSB_RAM_TMOD_ram_tmod_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_CKG_CFG_UNION
 �ṹ˵��  : QOSB_CKG_CFG �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x00000001�����:32
 �Ĵ���˵��: QOS_CKG_CFG��QosBuf��ʱ�ӿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dyn_ck_gate : 1;  /* bit[0]   : Qosbufģ��Ķ�̬ʱ���ſء�
                                                      0��ʱ�ӳ�����
                                                      1��ģ�����ʱ��ʱ���Զ��ſء� */
        unsigned int  reserved    : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_CKG_CFG_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_CKG_CFG_dyn_ck_gate_START  (0)
#define SOC_DDRC_QOSB_QOSB_CKG_CFG_dyn_ck_gate_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_DMC_LVL_UNION
 �ṹ˵��  : QOSB_DMC_LVL �Ĵ����ṹ���塣��ַƫ����:0x10C+0x4*(chans)����ֵ:0x0000000F�����:32
 �Ĵ���˵��: QOSB_DMC_LVL��QosBuf�Ľ���DMC��������߿��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_cmd_full_lvl : 5;  /* bit[0-4] : qos buf����dmc������ĸ��������ﵽ���ˮ�ߣ���ʾdmc��queue�Ѿ�����
                                                           ע�⣺������ˮ�����⣬������ΪNʱ��ʵ��ͨ�����������ΪN+1�����⣬�üĴ��������ڷ��ʹ����н��ж�̬���á� */
        unsigned int  reserved         : 27; /* bit[5-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_DMC_LVL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_DMC_LVL_dmc_cmd_full_lvl_START  (0)
#define SOC_DDRC_QOSB_QOSB_DMC_LVL_dmc_cmd_full_lvl_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_CFG_PERF_UNION
 �ṹ˵��  : QOSB_CFG_PERF �Ĵ����ṹ���塣��ַƫ����:0x120����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_CFG_PERF��QosBuf����ͳ�Ƶ�ģʽ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  perf_prd  : 28; /* bit[0-27] : ����ͳ�����ڡ�
                                                     0x0����Ч���á�
                                                     0x1��0xFFFFFFF��ͳ�����ڡ�
                                                     ʵ��ͳ������Ϊperf_prd*16*tclk��TclkΪDDRC����ʱ�����ڣ���
                                                     ע�⣺������ֻ��perf_mode=1ʱ��Ч����perf_mode=0������ͳ��ģʽ�£�����ͳ����ؼ�������һֱ������ */
        unsigned int  perf_mode : 1;  /* bit[28]   : ����ͳ��ģʽ��
                                                     0����������ģʽ������ͳ����ؼ����������������ɱ�֤������ͳ��ģʽ�£�1s��ͳ�Ʋ������1GHZMHz����
                                                     1�����δ���ģʽ������ͳ��ʱ�����perf_prd��ͳ�ƽ�����֣���ֹͣͳ�ơ�
                                                     ע�⣺��ͳ��ֵ����󱣳֡� */
        unsigned int  perf_en   : 1;  /* bit[29]   : ����ͳ��ʹ�ܼĴ�����
                                                     1��ʹ�ܣ�
                                                     0����ֹ��
                                                      ע�⣺��perf_mode=0ʱ����λʹ�ܱ�ʾ����ͳ�ƼĴ�������ʼѭ����������perf_mode=1ʱ�����һ��ͳ��֮�󣬸�λ�Զ����� */
        unsigned int  reserved  : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_CFG_PERF_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_prd_START   (0)
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_prd_END     (27)
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_mode_START  (28)
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_mode_END    (28)
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_en_START    (29)
#define SOC_DDRC_QOSB_QOSB_CFG_PERF_perf_en_END      (29)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_CMD_SUM_UNION
 �ṹ˵��  : QOSB_CMD_SUM �Ĵ����ṹ���塣��ַƫ����:0x124����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_CMD_SUM��QosBuf����������ۻ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_cmd_sum : 32; /* bit[0-31]: ��ǰQosBuf�ݴ������ֵ�������ۻ���������� */
    } reg;
} SOC_DDRC_QOSB_QOSB_CMD_SUM_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_CMD_SUM_qos_cmd_sum_START  (0)
#define SOC_DDRC_QOSB_QOSB_CMD_SUM_qos_cmd_sum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_SLOT_STAT0_UNION
 �ṹ˵��  : QOSB_SLOT_STAT0 �Ĵ����ṹ���塣��ַƫ����:0x128����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_SLOT_STAT0��QosBuf��queue��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  grp_cmd_valid_l : 32; /* bit[0-31]: QosBuf��cmd queue��0~31��״̬����Ӧ��λΪ1��ʾ��slot�д����������Ϊ�ա� */
    } reg;
} SOC_DDRC_QOSB_QOSB_SLOT_STAT0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT0_grp_cmd_valid_l_START  (0)
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT0_grp_cmd_valid_l_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_SLOT_STAT1_UNION
 �ṹ˵��  : QOSB_SLOT_STAT1 �Ĵ����ṹ���塣��ַƫ����:0x12C����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_SLOT_STAT0��QosBuf��queue��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  grp_cmd_valid_m0 : 32; /* bit[0-31]: QosBuf��cmd queue��32~63��״̬����Ӧ��λΪ1��ʾ��slot�д����������Ϊ�ա� */
    } reg;
} SOC_DDRC_QOSB_QOSB_SLOT_STAT1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT1_grp_cmd_valid_m0_START  (0)
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT1_grp_cmd_valid_m0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_SLOT_STAT2_UNION
 �ṹ˵��  : QOSB_SLOT_STAT2 �Ĵ����ṹ���塣��ַƫ����:0x130����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_SLOT_STAT0��QosBuf��queue��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  grp_cmd_valid_m1 : 32; /* bit[0-31]: QosBuf��cmd queue��64~95��״̬����Ӧ��λΪ1��ʾ��slot�д����������Ϊ�ա� */
    } reg;
} SOC_DDRC_QOSB_QOSB_SLOT_STAT2_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT2_grp_cmd_valid_m1_START  (0)
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT2_grp_cmd_valid_m1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_SLOT_STAT3_UNION
 �ṹ˵��  : QOSB_SLOT_STAT3 �Ĵ����ṹ���塣��ַƫ����:0x134����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_SLOT_STAT0��QosBuf��queue��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  grp_cmd_valid_h : 32; /* bit[0-31]: QosBuf��cmd queue��96~127��״̬����Ӧ��λΪ1��ʾ��slot�д����������Ϊ�ա� */
    } reg;
} SOC_DDRC_QOSB_QOSB_SLOT_STAT3_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT3_grp_cmd_valid_h_START  (0)
#define SOC_DDRC_QOSB_QOSB_SLOT_STAT3_grp_cmd_valid_h_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_WBUF_STAT0_UNION
 �ṹ˵��  : QOSB_WBUF_STAT0 �Ĵ����ṹ���塣��ַƫ����:0x140+0x4*(chans)����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_WBUF_STAT0��QosBuf��дbuf״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buf_ldata_valid_l : 32; /* bit[0-31]: QosBuf��дbuf��0~31��״̬����Ӧ��λΪ1��ʾ��buf�д���һ��burst�����ݣ��������ݲ���һ��burst��Ϊ�ա� */
    } reg;
} SOC_DDRC_QOSB_QOSB_WBUF_STAT0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT0_buf_ldata_valid_l_START  (0)
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT0_buf_ldata_valid_l_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_WBUF_STAT1_UNION
 �ṹ˵��  : QOSB_WBUF_STAT1 �Ĵ����ṹ���塣��ַƫ����:0x150+0x4*(chans)����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_WBUF_STAT1��QosBuf��дbuf״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buf_ldata_valid_h : 32; /* bit[0-31]: QosBuf��дbuf��31~63��״̬����Ӧ��λΪ1��ʾ��buf�д���һ��burst�����ݣ��������ݲ���һ��burst��Ϊ�ա� */
    } reg;
} SOC_DDRC_QOSB_QOSB_WBUF_STAT1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT1_buf_ldata_valid_h_START  (0)
#define SOC_DDRC_QOSB_QOSB_WBUF_STAT1_buf_ldata_valid_h_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_UNION
 �ṹ˵��  : QOSB_RDRBUF_STAT �Ĵ����ṹ���塣��ַƫ����:0x160+0x4*(chans)����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_RDRBUF_STAT��Reorderģ���buf״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  e_vld : 32; /* bit[0-31]: Reorder��reorder buf��0~31��״̬����Ӧ��λΪ1��ʾ��buf�д���һ��burst�����ݣ��������ݲ���һ��burst��Ϊ�ա� */
    } reg;
} SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_e_vld_START  (0)
#define SOC_DDRC_QOSB_QOSB_RDRBUF_STAT_e_vld_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_INTMSK_UNION
 �ṹ˵��  : QOSB_INTMSK �Ĵ����ṹ���塣��ַƫ����:0x170����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_INTMSK��QosBuf�ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_stat_int_mask    : 1;  /* bit[0]   : QOS Buf����ͳ���ж�����ʹ�ܡ�
                                                               1�������жϣ�
                                                               0��ʹ���жϡ� */
        unsigned int  rdrbuf_serr_int_mask : 1;  /* bit[1]   : RDR BUF(RAM)��ECC��bit�����ж�����ʹ��
                                                               1�������жϣ�
                                                               0��ʹ���жϣ� */
        unsigned int  rdrbuf_derr_int_mask : 1;  /* bit[2]   : RDR BUF(RAM)��ECC˫bit�����ж�����ʹ��
                                                               1�������жϣ�
                                                               0��ʹ���жϣ� */
        unsigned int  qosbuf_serr_int_mask : 1;  /* bit[3]   : QosBuf дbuf��bit�����ж�����ʹ�ܡ�
                                                               1�������жϣ�
                                                               0��ʹ���жϡ� */
        unsigned int  qosbuf_derr_int_mask : 1;  /* bit[4]   : QosBuf дbuf˫bit�����ж�����ʹ�ܡ�
                                                               1�������жϣ�
                                                               0��ʹ���жϡ� */
        unsigned int  qoscid_serr_int_mask : 1;  /* bit[5]   : QosBuf cid ram��bit�����ж�����ʹ�ܡ�
                                                               1�������жϣ�
                                                               0��ʹ���жϡ� */
        unsigned int  qoscid_derr_int_mask : 1;  /* bit[6]   : QosBuf cid ram˫bit�����ж�����ʹ�ܡ�
                                                               1�������жϣ�
                                                               0��ʹ���жϡ� */
        unsigned int  reserved             : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_INTMSK_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_INTMSK_qos_stat_int_mask_START     (0)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qos_stat_int_mask_END       (0)
#define SOC_DDRC_QOSB_QOSB_INTMSK_rdrbuf_serr_int_mask_START  (1)
#define SOC_DDRC_QOSB_QOSB_INTMSK_rdrbuf_serr_int_mask_END    (1)
#define SOC_DDRC_QOSB_QOSB_INTMSK_rdrbuf_derr_int_mask_START  (2)
#define SOC_DDRC_QOSB_QOSB_INTMSK_rdrbuf_derr_int_mask_END    (2)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qosbuf_serr_int_mask_START  (3)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qosbuf_serr_int_mask_END    (3)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qosbuf_derr_int_mask_START  (4)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qosbuf_derr_int_mask_END    (4)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qoscid_serr_int_mask_START  (5)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qoscid_serr_int_mask_END    (5)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qoscid_derr_int_mask_START  (6)
#define SOC_DDRC_QOSB_QOSB_INTMSK_qoscid_derr_int_mask_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_RINT_UNION
 �ṹ˵��  : QOSB_RINT �Ĵ����ṹ���塣��ַƫ����:0x174����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_RINT��QosBufԭʼ�жϼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_stat_rint    : 1;  /* bit[0]   : QOS Buf����ͳ���жϡ�д1�ж���� */
        unsigned int  rdrbuf_serr_rint : 1;  /* bit[1]   : RDR BUF(RAM)��ECC��bit�����жϡ�д1�ж������ */
        unsigned int  rdrbuf_derr_rint : 1;  /* bit[2]   : RDR BUF(RAM)��ECC˫bit�����жϡ�д1�ж������ */
        unsigned int  qosbuf_serr_rint : 1;  /* bit[3]   : QosBuf дbuf��bit�����жϡ�д1�ж���� */
        unsigned int  qosbuf_derr_rint : 1;  /* bit[4]   : QosBuf дbuf˫bit�����жϡ�д1�ж������ */
        unsigned int  qoscid_serr_rint : 1;  /* bit[5]   : QosBuf cid ram��bit�����жϡ�д1�ж������ */
        unsigned int  qoscid_derr_rint : 1;  /* bit[6]   : QosBuf cid ram˫bit�����жϡ�д1�ж������ */
        unsigned int  reserved         : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_RINT_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RINT_qos_stat_rint_START     (0)
#define SOC_DDRC_QOSB_QOSB_RINT_qos_stat_rint_END       (0)
#define SOC_DDRC_QOSB_QOSB_RINT_rdrbuf_serr_rint_START  (1)
#define SOC_DDRC_QOSB_QOSB_RINT_rdrbuf_serr_rint_END    (1)
#define SOC_DDRC_QOSB_QOSB_RINT_rdrbuf_derr_rint_START  (2)
#define SOC_DDRC_QOSB_QOSB_RINT_rdrbuf_derr_rint_END    (2)
#define SOC_DDRC_QOSB_QOSB_RINT_qosbuf_serr_rint_START  (3)
#define SOC_DDRC_QOSB_QOSB_RINT_qosbuf_serr_rint_END    (3)
#define SOC_DDRC_QOSB_QOSB_RINT_qosbuf_derr_rint_START  (4)
#define SOC_DDRC_QOSB_QOSB_RINT_qosbuf_derr_rint_END    (4)
#define SOC_DDRC_QOSB_QOSB_RINT_qoscid_serr_rint_START  (5)
#define SOC_DDRC_QOSB_QOSB_RINT_qoscid_serr_rint_END    (5)
#define SOC_DDRC_QOSB_QOSB_RINT_qoscid_derr_rint_START  (6)
#define SOC_DDRC_QOSB_QOSB_RINT_qoscid_derr_rint_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_INTSTS_UNION
 �ṹ˵��  : QOSB_INTSTS �Ĵ����ṹ���塣��ַƫ����:0x178����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_INTSTS��QOSBUF�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_stat_intsts    : 1;  /* bit[0]   : QOS Buf����ͳ���жϡ� */
        unsigned int  rdrbuf_serr_intsts : 1;  /* bit[1]   : RDR BUF(RAM)��ECC��bit�����жϡ� */
        unsigned int  rdrbuf_derr_intsts : 1;  /* bit[2]   : RDR BUF(RAM)��ECC˫bit�����жϡ��� */
        unsigned int  qosbuf_serr_intsts : 1;  /* bit[3]   : QosBuf дbuf��bit�����жϡ� */
        unsigned int  qosbuf_derr_intsts : 1;  /* bit[4]   : QosBuf дbuf˫bit�����жϡ� */
        unsigned int  qoscid_serr_intsts : 1;  /* bit[5]   : QosBuf cid ram��bit�����жϡ� */
        unsigned int  qoscid_derr_intsts : 1;  /* bit[6]   : QosBuf cid ram˫bit�����жϡ� */
        unsigned int  reserved           : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_INTSTS_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_INTSTS_qos_stat_intsts_START     (0)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qos_stat_intsts_END       (0)
#define SOC_DDRC_QOSB_QOSB_INTSTS_rdrbuf_serr_intsts_START  (1)
#define SOC_DDRC_QOSB_QOSB_INTSTS_rdrbuf_serr_intsts_END    (1)
#define SOC_DDRC_QOSB_QOSB_INTSTS_rdrbuf_derr_intsts_START  (2)
#define SOC_DDRC_QOSB_QOSB_INTSTS_rdrbuf_derr_intsts_END    (2)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qosbuf_serr_intsts_START  (3)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qosbuf_serr_intsts_END    (3)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qosbuf_derr_intsts_START  (4)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qosbuf_derr_intsts_END    (4)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qoscid_serr_intsts_START  (5)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qoscid_serr_intsts_END    (5)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qoscid_derr_intsts_START  (6)
#define SOC_DDRC_QOSB_QOSB_INTSTS_qoscid_derr_intsts_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_CMD_CNT_UNION
 �ṹ˵��  : QOSB_CMD_CNT �Ĵ����ṹ���塣��ַƫ����:0x180����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_CMD_CNT��QOSBUF�е�ǰ�ж��������ͳ�ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_cmd_cnt : 8;  /* bit[0-7] : QosBuf��ǰ����ĸ�����������ˮ���ϵ���� */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_CMD_CNT_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_CMD_CNT_qos_cmd_cnt_START  (0)
#define SOC_DDRC_QOSB_QOSB_CMD_CNT_qos_cmd_cnt_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_RNK_CNT_UNION
 �ṹ˵��  : QOSB_RNK_CNT �Ĵ����ṹ���塣��ַƫ����:0x190+0x4*(chans)����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_RNK_CNT��QOSBUF�е�ǰÿ��rank���ж��������ͳ�ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rnk0_cmd_cnt : 8;  /* bit[0-7]  : QosBuf�е�ǰͨ������rank0��������� */
        unsigned int  rnk1_cmd_cnt : 8;  /* bit[8-15] : QosBuf�е�ǰͨ������rank1��������� */
        unsigned int  rnk2_cmd_cnt : 8;  /* bit[16-23]: QosBuf�е�ǰͨ������rank2��������� */
        unsigned int  rnk3_cmd_cnt : 8;  /* bit[24-31]: QosBuf�е�ǰͨ������rank3��������� */
    } reg;
} SOC_DDRC_QOSB_QOSB_RNK_CNT_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk0_cmd_cnt_START  (0)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk0_cmd_cnt_END    (7)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk1_cmd_cnt_START  (8)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk1_cmd_cnt_END    (15)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk2_cmd_cnt_START  (16)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk2_cmd_cnt_END    (23)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk3_cmd_cnt_START  (24)
#define SOC_DDRC_QOSB_QOSB_RNK_CNT_rnk3_cmd_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_BNK_CNT0_UNION
 �ṹ˵��  : QOSB_BNK_CNT0 �Ĵ����ṹ���塣��ַƫ����:0x1A0+0x4*(chans)����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_BNK_CNT0��QOSBUF�е�ǰÿ��Bank�ж��������ͳ�ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bnk0_cmd_cnt : 8;  /* bit[0-7]  : ͳ��DMC�е�ǰͨ������bank0��������� */
        unsigned int  bnk1_cmd_cnt : 8;  /* bit[8-15] : ͳ��DMC�е�ǰͨ������bank1��������� */
        unsigned int  bnk2_cmd_cnt : 8;  /* bit[16-23]: ͳ��DMC�е�ǰͨ������bank2��������� */
        unsigned int  bnk3_cmd_cnt : 8;  /* bit[24-31]: ͳ��DMC�е�ǰͨ������bank3��������� */
    } reg;
} SOC_DDRC_QOSB_QOSB_BNK_CNT0_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk0_cmd_cnt_START  (0)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk0_cmd_cnt_END    (7)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk1_cmd_cnt_START  (8)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk1_cmd_cnt_END    (15)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk2_cmd_cnt_START  (16)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk2_cmd_cnt_END    (23)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk3_cmd_cnt_START  (24)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT0_bnk3_cmd_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_BNK_CNT1_UNION
 �ṹ˵��  : QOSB_BNK_CNT1 �Ĵ����ṹ���塣��ַƫ����:0x1B0+0x4*(chans)����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_BNK_CNT1��QOSBUF�е�ǰÿ��Bank�ж��������ͳ�ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bnk4_cmd_cnt : 8;  /* bit[0-7]  : ͳ��DMC�е�ǰͨ������bank4��������� */
        unsigned int  bnk5_cmd_cnt : 8;  /* bit[8-15] : ͳ��DMC�е�ǰͨ������bank5��������� */
        unsigned int  bnk6_cmd_cnt : 8;  /* bit[16-23]: ͳ��DMC�е�ǰͨ������bank6��������� */
        unsigned int  bnk7_cmd_cnt : 8;  /* bit[24-31]: ͳ��DMC�е�ǰͨ������bank7��������� */
    } reg;
} SOC_DDRC_QOSB_QOSB_BNK_CNT1_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk4_cmd_cnt_START  (0)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk4_cmd_cnt_END    (7)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk5_cmd_cnt_START  (8)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk5_cmd_cnt_END    (15)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk6_cmd_cnt_START  (16)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk6_cmd_cnt_END    (23)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk7_cmd_cnt_START  (24)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT1_bnk7_cmd_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_BNK_CNT2_UNION
 �ṹ˵��  : QOSB_BNK_CNT2 �Ĵ����ṹ���塣��ַƫ����:0x1C0+0x4*(chans)����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_BNK_CNT2��QOSBUF�е�ǰÿ��Bank�ж��������ͳ�ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bnk8_cmd_cnt  : 8;  /* bit[0-7]  : ͳ��DMC�е�ǰͨ������bank8��������� */
        unsigned int  bnk9_cmd_cnt  : 8;  /* bit[8-15] : ͳ��DMC�е�ǰͨ������bank9��������� */
        unsigned int  bnk10_cmd_cnt : 8;  /* bit[16-23]: ͳ��DMC�е�ǰͨ������bank10��������� */
        unsigned int  bnk11_cmd_cnt : 8;  /* bit[24-31]: ͳ��DMC�е�ǰͨ������bank11��������� */
    } reg;
} SOC_DDRC_QOSB_QOSB_BNK_CNT2_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk8_cmd_cnt_START   (0)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk8_cmd_cnt_END     (7)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk9_cmd_cnt_START   (8)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk9_cmd_cnt_END     (15)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk10_cmd_cnt_START  (16)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk10_cmd_cnt_END    (23)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk11_cmd_cnt_START  (24)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT2_bnk11_cmd_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_BNK_CNT3_UNION
 �ṹ˵��  : QOSB_BNK_CNT3 �Ĵ����ṹ���塣��ַƫ����:0x1D0+0x4*(chans)����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_BNK_CNT3��QOSBUF�е�ǰÿ��Bank�ж��������ͳ�ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bnk12_cmd_cnt : 8;  /* bit[0-7]  : ͳ��DMC�е�ǰͨ������bank12��������� */
        unsigned int  bnk13_cmd_cnt : 8;  /* bit[8-15] : ͳ��DMC�е�ǰͨ������bank13��������� */
        unsigned int  bnk14_cmd_cnt : 8;  /* bit[16-23]: ͳ��DMC�е�ǰͨ������bank14��������� */
        unsigned int  bnk15_cmd_cnt : 8;  /* bit[24-31]: ͳ��DMC�е�ǰͨ������bank15��������� */
    } reg;
} SOC_DDRC_QOSB_QOSB_BNK_CNT3_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk12_cmd_cnt_START  (0)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk12_cmd_cnt_END    (7)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk13_cmd_cnt_START  (8)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk13_cmd_cnt_END    (15)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk14_cmd_cnt_START  (16)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk14_cmd_cnt_END    (23)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk15_cmd_cnt_START  (24)
#define SOC_DDRC_QOSB_QOSB_BNK_CNT3_bnk15_cmd_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_OSTD_CNT_UNION
 �ṹ˵��  : QOSB_OSTD_CNT �Ĵ����ṹ���塣��ַƫ����:0x1E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_OSTD_CNT��QOSBUF�е�ǰÿ��ͨ���ж���Oustanding�����ͳ�ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch0_cmd_ostd : 8;  /* bit[0-7]  : QosBuf�е�ǰͨ������channel0��Outanding������� */
        unsigned int  ch1_cmd_ostd : 8;  /* bit[8-15] : QosBuf�е�ǰͨ������channel1��Outanding������� */
        unsigned int  ch2_cmd_ostd : 8;  /* bit[16-23]: QosBuf�е�ǰͨ������channel2��Outanding������� */
        unsigned int  ch3_cmd_ostd : 8;  /* bit[24-31]: QosBuf�е�ǰͨ������channel3��Outanding������� */
    } reg;
} SOC_DDRC_QOSB_QOSB_OSTD_CNT_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch0_cmd_ostd_START  (0)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch0_cmd_ostd_END    (7)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch1_cmd_ostd_START  (8)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch1_cmd_ostd_END    (15)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch2_cmd_ostd_START  (16)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch2_cmd_ostd_END    (23)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch3_cmd_ostd_START  (24)
#define SOC_DDRC_QOSB_QOSB_OSTD_CNT_ch3_cmd_ostd_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_UNION
 �ṹ˵��  : QOSB_WR_CMD_SUM �Ĵ����ṹ���塣��ַƫ����:0x1E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_CMD_SUM��QosBufд����������ۻ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_wr_cmd_sum : 32; /* bit[0-31]: ��ǰQosBuf�ݴ�д�����ֵ�������ۻ���������� */
    } reg;
} SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_qos_wr_cmd_sum_START  (0)
#define SOC_DDRC_QOSB_QOSB_WR_CMD_SUM_qos_wr_cmd_sum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_UNION
 �ṹ˵��  : QOSB_RD_CMD_SUM �Ĵ����ṹ���塣��ַƫ����:0x1E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_CMD_SUM��QosBuf������������ۻ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  qos_rd_cmd_sum : 32; /* bit[0-31]: ��ǰQosBuf�ݴ�������ֵ�������ۻ���������� */
    } reg;
} SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_qos_rd_cmd_sum_START  (0)
#define SOC_DDRC_QOSB_QOSB_RD_CMD_SUM_qos_rd_cmd_sum_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_UNION
 �ṹ˵��  : QOSB_GRT_FIFO_STATUS �Ĵ����ṹ���塣��ַƫ����:0x1EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_GRT_FIFO_STATUS��д���ݻ��MUX��Ӧ��grant fifo��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  grt_fifo_vld_0 : 1;  /* bit[0]    : ͨ��0��Ӧ��grant fifo��״̬��
                                                          0����ʾ�գ�
                                                          1����ʾ�ǿա� */
        unsigned int  grt_fifo_pid_0 : 7;  /* bit[1-7]  : ͨ��0��Ӧ��grant fifo�е�port id�� */
        unsigned int  grt_fifo_vld_1 : 1;  /* bit[8]    : ͨ��1��Ӧ��grant fifo��״̬��
                                                          0����ʾ�գ�
                                                          1����ʾ�ǿա� */
        unsigned int  grt_fifo_pid_1 : 7;  /* bit[9-15] : ͨ��1��Ӧ��grant fifo�е�port id�� */
        unsigned int  grt_fifo_vld_2 : 1;  /* bit[16]   : ͨ��2��Ӧ��grant fifo��״̬��
                                                          0����ʾ�գ�
                                                          1����ʾ�ǿա� */
        unsigned int  grt_fifo_pid_2 : 7;  /* bit[17-23]: ͨ��2��Ӧ��grant fifo�е�port id�� */
        unsigned int  grt_fifo_vld_3 : 1;  /* bit[24]   : ͨ��3��Ӧ��grant fifo��״̬��
                                                          0����ʾ�գ�
                                                          1����ʾ�ǿա� */
        unsigned int  grt_fifo_pid_3 : 7;  /* bit[25-31]: ͨ��3��Ӧ��grant fifo�е�port id�� */
    } reg;
} SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_0_START  (0)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_0_END    (0)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_0_START  (1)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_0_END    (7)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_1_START  (8)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_1_END    (8)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_1_START  (9)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_1_END    (15)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_2_START  (16)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_2_END    (16)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_2_START  (17)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_2_END    (23)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_3_START  (24)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_vld_3_END    (24)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_3_START  (25)
#define SOC_DDRC_QOSB_QOSB_GRT_FIFO_STATUS_grt_fifo_pid_3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_UNION
 �ṹ˵��  : QOSB_TIMEOUT_MODE �Ĵ����ṹ���塣��ַƫ����:0x1F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_TIMEOUT_MODE��QOSBUF��timeoutģʽѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeout_mode : 1;  /* bit[0]   : Timeoutģʽѡ��Ĵ���
                                                       0����ʾͨ��ID��ӳ�䣬��16��
                                                       1����ʾͨ�����ȼ���ӳ�䣬��8��������ӳ�����ID��ӳ���ĵ�8����ͬ�� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_timeout_mode_START  (0)
#define SOC_DDRC_QOSB_QOSB_TIMEOUT_MODE_timeout_mode_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_UNION
 �ṹ˵��  : QOSB_WBUF_PRI_CTRL �Ĵ����ṹ���塣��ַƫ����:0x1F4����ֵ:0x00200000�����:32
 �Ĵ���˵��: QOSB_WBUF_PRI_CTRL��QOSBUF��дwbuf���ȼ��������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wbuf_lcnt : 16; /* bit[0-15] : ��дwbuf�ﵽlvl2ˮ��ʱ�Ż������á��ü�������ʾ�ڸ�ʱ��������дbuf�Ὣ��д��������ȼ�����pri1.����ü�����Ϊ0����ʾ��һֱʹ��pri2�����ȼ���
                                                     ��ע�⣺�����pri1ָwbuf��lvl1���϶�Ӧ�����ȼ��� */
        unsigned int  wbuf_hcnt : 16; /* bit[16-31]: ��дwbuf�ﵽlvl2ˮ��ʱ�Ż������á��ü�������ʾ�ڸ�ʱ��������дbuf�Ὣ��д��������ȼ�����pri2.
                                                     ��ע�⣺�����pri2ָwbuf��lvl2���϶�Ӧ�����ȼ��� */
    } reg;
} SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_wbuf_lcnt_START  (0)
#define SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_wbuf_lcnt_END    (15)
#define SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_wbuf_hcnt_START  (16)
#define SOC_DDRC_QOSB_QOSB_WBUF_PRI_CTRL_wbuf_hcnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_RHIT_CTRL_UNION
 �ṹ˵��  : QOSB_RHIT_CTRL �Ĵ����ṹ���塣��ַƫ����:0x1F8����ֵ:0x00FF000F�����:32
 �Ĵ���˵��: QOSB_RHIT_CTRL��QOSBUF��rowhit���ȼ��������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rhit_lcnt : 16; /* bit[0-15] : ��rowhit�����ﵽ�üĴ������õ�ֵ�󣬾ͻ�ǿ�н���Ͽ���Ȼ�����rhit_lcnt��ʱ�䣬���������½���rowhit�� */
        unsigned int  rhit_hcnt : 16; /* bit[16-31]: ��rowhit�����ﵽ�üĴ������õ�ֵ�󣬾ͻ�ǿ�н���Ͽ���Ȼ�����rhit_lcnt��ʱ�䣬���������½���rowhit�� */
    } reg;
} SOC_DDRC_QOSB_QOSB_RHIT_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_RHIT_CTRL_rhit_lcnt_START  (0)
#define SOC_DDRC_QOSB_QOSB_RHIT_CTRL_rhit_lcnt_END    (15)
#define SOC_DDRC_QOSB_QOSB_RHIT_CTRL_rhit_hcnt_START  (16)
#define SOC_DDRC_QOSB_QOSB_RHIT_CTRL_rhit_hcnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_UNION
 �ṹ˵��  : QOSB_WBUF_MERG_CTRL �Ĵ����ṹ���塣��ַƫ����:0x1FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: QOSB_WBUF_MERG_CTRL��QOSBUF˫ͨ��дbuf�ϲ����ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ch_merge : 1;  /* bit[0]   : ��˫ͨ��ģʽ���Ƿ�ͨ��1��wbuf�ϵ�ͨ��0��
                                                   0����ʾ����ͨ����wbuf���ϲ���
                                                   1����ʾ��ͨ��1��wbuf��ͨ��0��wbuf�ϲ���
                                                   
                                                   ע�⣺�ںϲ�ģʽ��ֻ��֧��ͨ��0������ͨ��1���ܹ����� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_UNION;
#endif
#define SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_ch_merge_START  (0)
#define SOC_DDRC_QOSB_QOSB_WBUF_MERG_CTRL_ch_merge_END    (0)






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

#endif /* end of soc_ddrc_qosb_interface.h */
