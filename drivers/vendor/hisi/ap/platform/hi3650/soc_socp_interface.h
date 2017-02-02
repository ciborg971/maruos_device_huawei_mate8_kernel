/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_socp_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:23:09
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_SOCP.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_SOCP_INTERFACE_H__
#define __SOC_SOCP_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) SOCP
 ****************************************************************************/
/* �Ĵ���˵����SOCPȫ����λ���ƼĴ���
   λ����UNION�ṹ:  SOC_SOCP_GLOBAL_CTRL_UNION */
#define SOC_SOCP_GLOBAL_CTRL_ADDR(base)               ((base) + (0x000))

/* �Ĵ���˵��������ͨ����λ���ƼĴ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_SRST_CTRL_UNION */
#define SOC_SOCP_ENC_SRST_CTRL_ADDR(base)             ((base) + (0x004))

/* �Ĵ���˵��������ͨ����λ���ƼĴ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_SRST_CTRL_UNION */
#define SOC_SOCP_DEC_SRST_CTRL_ADDR(base)             ((base) + (0x008))

/* �Ĵ���˵��������ͨ��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CH_STATUS_UNION */
#define SOC_SOCP_ENC_CH_STATUS_ADDR(base)             ((base) + (0x00C))

/* �Ĵ���˵��������ͨ��״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_CH_STATUS_UNION */
#define SOC_SOCP_DEC_CH_STATUS_ADDR(base)             ((base) + (0x010))

/* �Ĵ���˵�����Զ�ʱ���ſؿ��ƼĴ���
   λ����UNION�ṹ:  SOC_SOCP_CLK_CTRL_UNION */
#define SOC_SOCP_CLK_CTRL_ADDR(base)                  ((base) + (0x014))

/* �Ĵ���˵�������ȼ����üĴ���
   λ����UNION�ṹ:  SOC_SOCP_PRIOR_CFG_UNION */
#define SOC_SOCP_PRIOR_CFG_ADDR(base)                 ((base) + (0x018))

/* �Ĵ���˵���������жϳ�ʱ���üĴ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_INT_TIMEOUT_UNION */
#define SOC_SOCP_DEC_INT_TIMEOUT_ADDR(base)           ((base) + (0x020))

/* �Ĵ���˵����������жϳ�ʱ���üĴ���
   λ����UNION�ṹ:  SOC_SOCP_INT_TIMEOUT_UNION */
#define SOC_SOCP_INT_TIMEOUT_ADDR(base)               ((base) + (0x024))

/* �Ĵ���˵����BUFFER�����ʱ���üĴ���
   λ����UNION�ṹ:  SOC_SOCP_BUFFER_TIMEOUT_UNION */
#define SOC_SOCP_BUFFER_TIMEOUT_ADDR(base)            ((base) + (0x028))

/* �Ĵ���˵��������ͨ·���������üĴ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_PKT_LEN_CFG_UNION */
#define SOC_SOCP_DEC_PKT_LEN_CFG_ADDR(base)           ((base) + (0x02C))

/* �Ĵ���˵��������Դͨ����ȫ���ƼĴ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_SRCCH_SECCTRL_UNION */
#define SOC_SOCP_ENC_SRCCH_SECCTRL_ADDR(base)         ((base) + (0x030))

/* �Ĵ���˵��������Ŀ��ͨ����ȫ���ƼĴ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_DSTCH_SECCTRL_UNION */
#define SOC_SOCP_ENC_DSTCH_SECCTRL_ADDR(base)         ((base) + (0x034))

/* �Ĵ���˵��������Դͨ����ȫ���ƼĴ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_SRCCH_SECCTRL_UNION */
#define SOC_SOCP_DEC_SRCCH_SECCTRL_ADDR(base)         ((base) + (0x038))

/* �Ĵ���˵��������Ŀ��ͨ����ȫ���ƼĴ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_DSTCH_SECCTRL_UNION */
#define SOC_SOCP_DEC_DSTCH_SECCTRL_ADDR(base)         ((base) + (0x03C))

/* �Ĵ���˵����ȫ�ּĴ�����ȫ���ƼĴ���
   λ����UNION�ṹ:  SOC_SOCP_GLB_REG_SECCTRL_UNION */
#define SOC_SOCP_GLB_REG_SECCTRL_ADDR(base)           ((base) + (0x040))

/* �Ĵ���˵����ȫ���ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_GLOBAL_INT_STATUS_UNION */
#define SOC_SOCP_GLOBAL_INT_STATUS_ADDR(base)         ((base) + (0x050))

/* �Ĵ���˵����CORE0���봫���ж����μĴ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE0_MASK0_UNION */
#define SOC_SOCP_ENC_CORE0_MASK0_ADDR(base)           ((base) + (0x054))

/* �Ĵ���˵����CORE0���봫���ж�ԭʼ״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE0_RAWINT0_UNION */
#define SOC_SOCP_ENC_CORE0_RAWINT0_ADDR(base)         ((base) + (0x058))

/* �Ĵ���˵����CORE0���봫���ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE0_INT0_UNION */
#define SOC_SOCP_ENC_CORE0_INT0_ADDR(base)            ((base) + (0x05C))

/* �Ĵ���˵����CORE0����ͷ��־���ж����μĴ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE0_MASK1_UNION */
#define SOC_SOCP_ENC_CORE0_MASK1_ADDR(base)           ((base) + (0x060))

/* �Ĵ���˵����CORE1����ͷ��־���ж����μĴ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE1_MASK1_UNION */
#define SOC_SOCP_ENC_CORE1_MASK1_ADDR(base)           ((base) + (0x064))

/* �Ĵ���˵��������ͨ��ͷ��־���ж�ԭʼ״̬�Ĵ���1
   λ����UNION�ṹ:  SOC_SOCP_ENC_RAWINT1_UNION */
#define SOC_SOCP_ENC_RAWINT1_ADDR(base)               ((base) + (0x068))

/* �Ĵ���˵����CORE0����ͨ��ͷ��־���ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE0_INT1_UNION */
#define SOC_SOCP_ENC_CORE0_INT1_ADDR(base)            ((base) + (0x06C))

/* �Ĵ���˵����CORE1����ͨ��ͷ��־���ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE1_INT1_UNION */
#define SOC_SOCP_ENC_CORE1_INT1_ADDR(base)            ((base) + (0x070))

/* �Ĵ���˵����CORE0����Ŀ��buffer�����ж����μĴ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE0_MASK2_UNION */
#define SOC_SOCP_ENC_CORE0_MASK2_ADDR(base)           ((base) + (0x074))

/* �Ĵ���˵��������Ŀ��buffer����ԭʼ�ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE0_RAWINT2_UNION */
#define SOC_SOCP_ENC_CORE0_RAWINT2_ADDR(base)         ((base) + (0x078))

/* �Ĵ���˵����CORE0����Ŀ��buffer�����ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE0_INT2_UNION */
#define SOC_SOCP_ENC_CORE0_INT2_ADDR(base)            ((base) + (0x07C))

/* �Ĵ���˵����CORE0����RD�ж����μĴ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE0_MASK3_UNION */
#define SOC_SOCP_ENC_CORE0_MASK3_ADDR(base)           ((base) + (0x080))

/* �Ĵ���˵����CORE1����RD�ж����μĴ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE1_MASK3_UNION */
#define SOC_SOCP_ENC_CORE1_MASK3_ADDR(base)           ((base) + (0x084))

/* �Ĵ���˵��������ͨ��RDԭʼ�ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_RAWINT3_UNION */
#define SOC_SOCP_ENC_RAWINT3_ADDR(base)               ((base) + (0x088))

/* �Ĵ���˵����CORE0����RD�ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE0_INT3_UNION */
#define SOC_SOCP_ENC_CORE0_INT3_ADDR(base)            ((base) + (0x08C))

/* �Ĵ���˵����CORE1����RD�ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE1_INT3_UNION */
#define SOC_SOCP_ENC_CORE1_INT3_ADDR(base)            ((base) + (0x090))

/* �Ĵ���˵����CORE0����ͨ�������ж����μĴ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_CORE0_MASK0_UNION */
#define SOC_SOCP_DEC_CORE0_MASK0_ADDR(base)           ((base) + (0x0A8))

/* �Ĵ���˵����CORE1����ͨ�������ж����μĴ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_CORE1_MASK0_UNION */
#define SOC_SOCP_DEC_CORE1_MASK0_ADDR(base)           ((base) + (0x0AC))

/* �Ĵ���˵��������ͨ���ж�ԭʼ״̬�Ĵ���0
   λ����UNION�ṹ:  SOC_SOCP_DEC_RAWINT0_UNION */
#define SOC_SOCP_DEC_RAWINT0_ADDR(base)               ((base) + (0x0B0))

/* �Ĵ���˵����CORE0����ͨ�������ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_CORE0_INT0_UNION */
#define SOC_SOCP_DEC_CORE0_INT0_ADDR(base)            ((base) + (0x0B4))

/* �Ĵ���˵����CORE1����ͨ�������ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_CORE1_INT0_UNION */
#define SOC_SOCP_DEC_CORE1_INT0_ADDR(base)            ((base) + (0x0B8))

/* �Ĵ���˵����CORE0����ͨ���쳣�ж����μĴ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_CORE0_MASK1_UNION */
#define SOC_SOCP_DEC_CORE0_MASK1_ADDR(base)           ((base) + (0x0BC))

/* �Ĵ���˵��������ͨ���쳣�ж�ԭʼ״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_CORE0_RAWINT1_UNION */
#define SOC_SOCP_DEC_CORE0_RAWINT1_ADDR(base)         ((base) + (0x0C0))

/* �Ĵ���˵����CORE0����ͨ���쳣�ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_CORE0_INT1_UNION */
#define SOC_SOCP_DEC_CORE0_INT1_ADDR(base)            ((base) + (0x0C4))

/* �Ĵ���˵����CORE0����ͨ��Ŀ��buffer����ж����μĴ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_CORE0_MASK2_UNION */
#define SOC_SOCP_DEC_CORE0_MASK2_ADDR(base)           ((base) + (0x0C8))

/* �Ĵ���˵����CORE1����ͨ��Ŀ��buffer����ж����μĴ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_CORE1NOTE_MASK2_UNION */
#define SOC_SOCP_DEC_CORE1NOTE_MASK2_ADDR(base)       ((base) + (0x0CC))

/* �Ĵ���˵��������ͨ��Ŀ��buffer����ж�ԭʼ״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_RAWINT2_UNION */
#define SOC_SOCP_DEC_RAWINT2_ADDR(base)               ((base) + (0x0D0))

/* �Ĵ���˵����CORE0����ͨ��Ŀ��buffer����ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_CORE0NOTE_NT2_UNION */
#define SOC_SOCP_DEC_CORE0NOTE_NT2_ADDR(base)         ((base) + (0x0D4))

/* �Ĵ���˵����CORE1����ͨ��Ŀ��buffer����ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_CORE1NOTE_INT2_UNION */
#define SOC_SOCP_DEC_CORE1NOTE_INT2_ADDR(base)        ((base) + (0x0D8))

/* �Ĵ���˵����CORE1���봫���ж����μĴ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE1_MASK0_UNION */
#define SOC_SOCP_ENC_CORE1_MASK0_ADDR(base)           ((base) + (0xDC))

/* �Ĵ���˵����CORE1���봫���ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE1_INT0_UNION */
#define SOC_SOCP_ENC_CORE1_INT0_ADDR(base)            ((base) + (0x0E0))

/* �Ĵ���˵����CORE1����Ŀ��buffer�����ж����μĴ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE1_MASK2_UNION */
#define SOC_SOCP_ENC_CORE1_MASK2_ADDR(base)           ((base) + (0x0E4))

/* �Ĵ���˵����CORE1����Ŀ��buffer�����ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_CORE1_INT2_UNION */
#define SOC_SOCP_ENC_CORE1_INT2_ADDR(base)            ((base) + (0x0E8))

/* �Ĵ���˵����CORE1����ͨ���쳣�ж����μĴ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_CORE1_MASK1_UNION */
#define SOC_SOCP_DEC_CORE1_MASK1_ADDR(base)           ((base) + (0x0EC))

/* �Ĵ���˵����CORE1����ͨ���쳣�ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_CORE1_INT1_UNION */
#define SOC_SOCP_DEC_CORE1_INT1_ADDR(base)            ((base) + (0x0F0))

/* �Ĵ���˵���������쳣�ж����μĴ���
   λ����UNION�ṹ:  SOC_SOCP_BUS_ERROR_MASK_UNION */
#define SOC_SOCP_BUS_ERROR_MASK_ADDR(base)            ((base) + (0x0F4))

/* �Ĵ���˵���������쳣ԭʼ�ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_BUS_ERROR_RAWINT_UNION */
#define SOC_SOCP_BUS_ERROR_RAWINT_ADDR(base)          ((base) + (0x0F8))

/* �Ĵ���˵���������쳣���κ��жϼĴ���
   λ����UNION�ṹ:  SOC_SOCP_BUS_ERROR_INT_UNION */
#define SOC_SOCP_BUS_ERROR_INT_ADDR(base)             ((base) + (0x0FC))

/* �Ĵ���˵��������ͨ·Դbuffermдָ��Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_SRC_BUFM_WPTR_UNION */
#define SOC_SOCP_ENC_SRC_BUFM_WPTR_ADDR(base, m)      ((base) + (0x100+0x40*(m)))

/* �Ĵ���˵��������ͨ·Դbufferm��ָ��Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_SRC_BUFM_RPTR_UNION */
#define SOC_SOCP_ENC_SRC_BUFM_RPTR_ADDR(base, m)      ((base) + (0x104+0x40*(m)))

/* �Ĵ���˵��������ͨ·Դbufferm��ʼ��ַ�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_SRC_BUFM_ADDR_UNION */
#define SOC_SOCP_ENC_SRC_BUFM_ADDR_ADDR(base, m)      ((base) + (0x108+0x40*(m)))

/* �Ĵ���˵��������ͨ·Դbufferm��ȼĴ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_SRC_BUFM_DEPTH_UNION */
#define SOC_SOCP_ENC_SRC_BUFM_DEPTH_ADDR(base, m)     ((base) + (0x10C+0x40*(m)))

/* �Ĵ���˵��������ͨ·Դbufferm���üĴ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_SRC_BUFM_CFG_UNION */
#define SOC_SOCP_ENC_SRC_BUFM_CFG_ADDR(base, m)       ((base) + (0x110+0x40*(m)))

/* �Ĵ���˵��������ͨ·RD����bufferдָ��Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_SRC_RDQ_WPTR_UNION */
#define SOC_SOCP_ENC_SRC_RDQ_WPTR_ADDR(base, m)       ((base) + (0x114+0x40*(m)))

/* �Ĵ���˵��������ͨ·RD����bufferдָ��Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_SRC_RDQ_RPTR_UNION */
#define SOC_SOCP_ENC_SRC_RDQ_RPTR_ADDR(base, m)       ((base) + (0x118+0x40*(m)))

/* �Ĵ���˵��������ͨ·RD����buffer��ʼ��ַ�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_SRC_RDQ_BADDR_UNION */
#define SOC_SOCP_ENC_SRC_RDQ_BADDR_ADDR(base, m)      ((base) + (0x11C+0x40*(m)))

/* �Ĵ���˵��������ͨ·RD����buffer���üĴ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_SRC_RDQ_CFG_UNION */
#define SOC_SOCP_ENC_SRC_RDQ_CFG_ADDR(base, m)        ((base) + (0x120+0x40*(m)))

/* �Ĵ���˵��������ͨ·Ŀ��bufferдָ��Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_DEST_BUFN_WPTR_UNION */
#define SOC_SOCP_ENC_DEST_BUFN_WPTR_ADDR(base, n)     ((base) + (0x900+0x20*(n)))

/* �Ĵ���˵��������ͨ·Ŀ��buffer��ָ��Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_DEST_BUFN_RPTR_UNION */
#define SOC_SOCP_ENC_DEST_BUFN_RPTR_ADDR(base, n)     ((base) + (0x904+0x20*(n)))

/* �Ĵ���˵��������ͨ·Ŀ��buffer��ʼ��ַ�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_DEST_BUFN_ADDR_UNION */
#define SOC_SOCP_ENC_DEST_BUFN_ADDR_ADDR(base, n)     ((base) + (0x908+0x20*(n)))

/* �Ĵ���˵��������ͨ·Ŀ��buffer��ȼĴ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_DEST_BUFN_DEPTH_UNION */
#define SOC_SOCP_ENC_DEST_BUFN_DEPTH_ADDR(base, n)    ((base) + (0x90C+0x20*(n)))

/* �Ĵ���˵��������ͨ·Ŀ��buffer����ж���ֵ�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_DEST_BUFN_THRH_UNION */
#define SOC_SOCP_ENC_DEST_BUFN_THRH_ADDR(base, n)     ((base) + (0x910+0x20*(n)))

/* �Ĵ���˵��������ͨ·�����ж���ֵ�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_ENC_INT_THRESHOLD_UNION */
#define SOC_SOCP_ENC_INT_THRESHOLD_ADDR(base, n)      ((base) + (0x914+0x20*(n)))

/* �Ĵ���˵��������ͨ·Դbufferxдָ��Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_SRC_BUFX_WPTR_UNION */
#define SOC_SOCP_DEC_SRC_BUFX_WPTR_ADDR(base, j)      ((base) + (0xA00+0x40*(j)))

/* �Ĵ���˵��������ͨ·Դbufferx��ָ��Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_SRC_BUFX_RPTR_UNION */
#define SOC_SOCP_DEC_SRC_BUFX_RPTR_ADDR(base, j)      ((base) + (0xA04+0x40*(j)))

/* �Ĵ���˵��������ͨ·Դbufferx��ʼ��ַ�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_SRC_BUFX_ADDR_UNION */
#define SOC_SOCP_DEC_SRC_BUFX_ADDR_ADDR(base, j)      ((base) + (0xA08+0x40*(j)))

/* �Ĵ���˵��������ͨ·Դbufferx���üĴ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_SRC_BUFX_CFG0_UNION */
#define SOC_SOCP_DEC_SRC_BUFX_CFG0_ADDR(base, j)      ((base) + (0xA0C+0x40*(j)))

/* �Ĵ���˵��������ͨ·״̬�Ĵ���0
   λ����UNION�ṹ:  SOC_SOCP_DEC_BUFX_STATUS0_UNION */
#define SOC_SOCP_DEC_BUFX_STATUS0_ADDR(base, j)       ((base) + (0xA20+0x40*(j)))

/* �Ĵ���˵��������ͨ·״̬�Ĵ���1
   λ����UNION�ṹ:  SOC_SOCP_DEC_BUFX_STATUS1_UNION */
#define SOC_SOCP_DEC_BUFX_STATUS1_ADDR(base, j)       ((base) + (0xA24+0x40*(j)))

/* �Ĵ���˵��������ͨ·Ŀ��bufferyдָ��Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_DEST_BUFY_WPTR_UNION */
#define SOC_SOCP_DEC_DEST_BUFY_WPTR_ADDR(base, y)     ((base) + (0xC00+0x10*(y)))

/* �Ĵ���˵��������ͨ·Ŀ��buffery��ָ��Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_DEST_BUFY_RPTR_UNION */
#define SOC_SOCP_DEC_DEST_BUFY_RPTR_ADDR(base, y)     ((base) + (0xC04+0x10*(y)))

/* �Ĵ���˵��������ͨ·Ŀ��buffery��ʼ��ַ�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_DEST_BUFY_ADDR_UNION */
#define SOC_SOCP_DEC_DEST_BUFY_ADDR_ADDR(base, y)     ((base) + (0xC08+0x10*(y)))

/* �Ĵ���˵��������ͨ·Ŀ��buffery���üĴ���
   λ����UNION�ṹ:  SOC_SOCP_DEC_DEST_BUFY_CFG0_UNION */
#define SOC_SOCP_DEC_DEST_BUFY_CFG0_ADDR(base, y)     ((base) + (0xC0C+0x10*(y)))

/* �Ĵ���˵��������CD debug�Ĵ���0
   λ����UNION�ṹ:  SOC_SOCP_ENC_CD_DBG0_UNION */
#define SOC_SOCP_ENC_CD_DBG0_ADDR(base)               ((base) + (0xE00))

/* �Ĵ���˵��������CD debug�Ĵ���1
   λ����UNION�ṹ:  SOC_SOCP_ENC_CD_DBG1_UNION */
#define SOC_SOCP_ENC_CD_DBG1_ADDR(base)               ((base) + (0xE04))

/* �Ĵ���˵��������Դ��debug�Ĵ���0
   λ����UNION�ṹ:  SOC_SOCP_ENC_IBUF_DBG0_UNION */
#define SOC_SOCP_ENC_IBUF_DBG0_ADDR(base)             ((base) + (0xE08))

/* �Ĵ���˵��������Դ��debug�Ĵ���1
   λ����UNION�ṹ:  SOC_SOCP_ENC_IBUF_DBG1_UNION */
#define SOC_SOCP_ENC_IBUF_DBG1_ADDR(base)             ((base) + (0xE0C))

/* �Ĵ���˵��������Դ��debug�Ĵ���2
   λ����UNION�ṹ:  SOC_SOCP_ENC_IBUF_DBG2_UNION */
#define SOC_SOCP_ENC_IBUF_DBG2_ADDR(base)             ((base) + (0xE10))

/* �Ĵ���˵��������Դ��debug�Ĵ���3
   λ����UNION�ṹ:  SOC_SOCP_ENC_IBUF_DBG3_UNION */
#define SOC_SOCP_ENC_IBUF_DBG3_ADDR(base)             ((base) + (0xE14))

/* �Ĵ���˵��������Ŀ�Ķ�debug�Ĵ���0
   λ����UNION�ṹ:  SOC_SOCP_ENC_OBUF_DBG0_UNION */
#define SOC_SOCP_ENC_OBUF_DBG0_ADDR(base)             ((base) + (0xE18))

/* �Ĵ���˵��������Ŀ�Ķ�debug�Ĵ���1
   λ����UNION�ṹ:  SOC_SOCP_ENC_OBUF_DBG1_UNION */
#define SOC_SOCP_ENC_OBUF_DBG1_ADDR(base)             ((base) + (0xE1C))

/* �Ĵ���˵��������Ŀ�Ķ�debug�Ĵ���2
   λ����UNION�ṹ:  SOC_SOCP_ENC_OBUF_DBG2_UNION */
#define SOC_SOCP_ENC_OBUF_DBG2_ADDR(base)             ((base) + (0xE20))

/* �Ĵ���˵��������Ŀ�Ķ�debug�Ĵ���3
   λ����UNION�ṹ:  SOC_SOCP_ENC_OBUF_DBG3_UNION */
#define SOC_SOCP_ENC_OBUF_DBG3_ADDR(base)             ((base) + (0xE24))

/* �Ĵ���˵��������Դ��debug�Ĵ���0
   λ����UNION�ṹ:  SOC_SOCP_DEC_IBUF_DBG0_UNION */
#define SOC_SOCP_DEC_IBUF_DBG0_ADDR(base)             ((base) + (0xE28))

/* �Ĵ���˵��������Դ��debug�Ĵ���1
   λ����UNION�ṹ:  SOC_SOCP_DEC_IBUF_DBG1_UNION */
#define SOC_SOCP_DEC_IBUF_DBG1_ADDR(base)             ((base) + (0xE2C))

/* �Ĵ���˵��������Դ��debug�Ĵ���2
   λ����UNION�ṹ:  SOC_SOCP_DEC_IBUF_DBG2_UNION */
#define SOC_SOCP_DEC_IBUF_DBG2_ADDR(base)             ((base) + (0xE30))

/* �Ĵ���˵��������Դ��debug�Ĵ���3
   λ����UNION�ṹ:  SOC_SOCP_DEC_IBUF_DBG3_UNION */
#define SOC_SOCP_DEC_IBUF_DBG3_ADDR(base)             ((base) + (0xE34))

/* �Ĵ���˵��������Ŀ�Ķ�debug�Ĵ���0
   λ����UNION�ṹ:  SOC_SOCP_DEC_OBUF_DBG0_UNION */
#define SOC_SOCP_DEC_OBUF_DBG0_ADDR(base)             ((base) + (0xE38))

/* �Ĵ���˵��������Ŀ�Ķ�debug�Ĵ���1
   λ����UNION�ṹ:  SOC_SOCP_DEC_OBUF_DBG1_UNION */
#define SOC_SOCP_DEC_OBUF_DBG1_ADDR(base)             ((base) + (0xE3C))

/* �Ĵ���˵��������Ŀ�Ķ�debug�Ĵ���2
   λ����UNION�ṹ:  SOC_SOCP_DEC_OBUF_DBG2_UNION */
#define SOC_SOCP_DEC_OBUF_DBG2_ADDR(base)             ((base) + (0xE40))

/* �Ĵ���˵��������Ŀ�Ķ�debug�Ĵ���3
   λ����UNION�ṹ:  SOC_SOCP_DEC_OBUF_DBG3_UNION */
#define SOC_SOCP_DEC_OBUF_DBG3_ADDR(base)             ((base) + (0xE44))

/* �Ĵ���˵�����汾ָʾ�Ĵ���
   λ����UNION�ṹ:  SOC_SOCP_VERSION_UNION */
#define SOC_SOCP_VERSION_ADDR(base)                   ((base) + (0xFFC))





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
                     (1/1) SOCP
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_SOCP_GLOBAL_CTRL_UNION
 �ṹ˵��  : GLOBAL_CTRL �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: SOCPȫ����λ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  global_srst         : 1;  /* bit[0]    : SOCPģ��ȫ����λ���ƣ��Զ����㡣
                                                               1������λ
                                                               0��������λ */
        unsigned int  int_timeout_cfg_sel : 1;  /* bit[1]    : ������жϳ�ʱ���üĴ���ѡ��
                                                               1 - ����ͨ������INT_TIMEOUT(0x024)������ͨ������DEC_INT_TIMEOUT(0x20);
                                                               0 - �����ͨ��������INT_TIMEOUT(0x024) */
        unsigned int  reserved_0          : 14; /* bit[2-15] : ���� */
        unsigned int  ch_halt             : 1;  /* bit[16]   : SOCP�����ͨ��ֹͣ����λ��
                                                               1 - �����ͨ��ֹͣ����
                                                               0 - �����ͨ����������
                                                               ��bit��Ҫ���ڵ͹���ģʽ�� */
        unsigned int  reserved_1          : 15; /* bit[17-31]: ������ */
    } reg;
} SOC_SOCP_GLOBAL_CTRL_UNION;
#endif
#define SOC_SOCP_GLOBAL_CTRL_global_srst_START          (0)
#define SOC_SOCP_GLOBAL_CTRL_global_srst_END            (0)
#define SOC_SOCP_GLOBAL_CTRL_int_timeout_cfg_sel_START  (1)
#define SOC_SOCP_GLOBAL_CTRL_int_timeout_cfg_sel_END    (1)
#define SOC_SOCP_GLOBAL_CTRL_ch_halt_START              (16)
#define SOC_SOCP_GLOBAL_CTRL_ch_halt_END                (16)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_SRST_CTRL_UNION
 �ṹ˵��  : ENC_SRST_CTRL �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ����λ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_chm_srst : 32; /* bit[0-31]: ����ͨ·ͨ����λ���ƣ��Զ����㡣
                                                       1������λ
                                                       0��������λ */
    } reg;
} SOC_SOCP_ENC_SRST_CTRL_UNION;
#endif
#define SOC_SOCP_ENC_SRST_CTRL_enc_chm_srst_START  (0)
#define SOC_SOCP_ENC_SRST_CTRL_enc_chm_srst_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_SRST_CTRL_UNION
 �ṹ˵��  : DEC_SRST_CTRL �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ����λ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_chx_srst : 4;  /* bit[0-3] : ����ͨ·ͨ����λ���ƣ��Զ����㡣
                                                       1������λ
                                                       0��������λ */
        unsigned int  reserved     : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_SOCP_DEC_SRST_CTRL_UNION;
#endif
#define SOC_SOCP_DEC_SRST_CTRL_dec_chx_srst_START  (0)
#define SOC_SOCP_DEC_SRST_CTRL_dec_chx_srst_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CH_STATUS_UNION
 �ṹ˵��  : ENC_CH_STATUS �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_chm_busy : 32; /* bit[0-31]: ����ͨ·ͨ��æָʾ��
                                                       1��æ
                                                       0������ */
    } reg;
} SOC_SOCP_ENC_CH_STATUS_UNION;
#endif
#define SOC_SOCP_ENC_CH_STATUS_enc_chm_busy_START  (0)
#define SOC_SOCP_ENC_CH_STATUS_enc_chm_busy_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_CH_STATUS_UNION
 �ṹ˵��  : DEC_CH_STATUS �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_chx_busy : 4;  /* bit[0-3] : ����ͨ·ͨ��æָʾ��
                                                       1��æ
                                                       0������ */
        unsigned int  reserved     : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_SOCP_DEC_CH_STATUS_UNION;
#endif
#define SOC_SOCP_DEC_CH_STATUS_dec_chx_busy_START  (0)
#define SOC_SOCP_DEC_CH_STATUS_dec_chx_busy_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_CLK_CTRL_UNION
 �ṹ˵��  : CLK_CTRL �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Զ�ʱ���ſؿ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_gclk_en : 1;  /* bit[0]   : ����ͨ���Զ��ſؿ��ơ�
                                                      1������ʱ��ʱ���Զ��ر�
                                                      0��ʱ��һֱ�� */
        unsigned int  dec_gclk_en : 1;  /* bit[1]   : ����ͨ���Զ��ſؿ��ơ�
                                                      1������ʱ��ʱ���Զ��ر�
                                                      0��ʱ��һֱ�� */
        unsigned int  reg_clk_en  : 1;  /* bit[2]   : �Ĵ����Զ��ſؿ��ơ�
                                                      1������ʱ��ʱ���Զ��ر�
                                                      0��ʱ��һֱ�� */
        unsigned int  reserved_0  : 1;  /* bit[3]   : ������ */
        unsigned int  ram_gclk_en : 1;  /* bit[4]   : RAM�Զ��ſؿ��ơ�
                                                      1������ʱ��ʱ���Զ��ر�
                                                      0��ʱ��һֱ�� */
        unsigned int  reserved_1  : 27; /* bit[5-31]: ������ */
    } reg;
} SOC_SOCP_CLK_CTRL_UNION;
#endif
#define SOC_SOCP_CLK_CTRL_enc_gclk_en_START  (0)
#define SOC_SOCP_CLK_CTRL_enc_gclk_en_END    (0)
#define SOC_SOCP_CLK_CTRL_dec_gclk_en_START  (1)
#define SOC_SOCP_CLK_CTRL_dec_gclk_en_END    (1)
#define SOC_SOCP_CLK_CTRL_reg_clk_en_START   (2)
#define SOC_SOCP_CLK_CTRL_reg_clk_en_END     (2)
#define SOC_SOCP_CLK_CTRL_ram_gclk_en_START  (4)
#define SOC_SOCP_CLK_CTRL_ram_gclk_en_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_PRIOR_CFG_UNION
 �ṹ˵��  : PRIOR_CFG �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ȼ����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_prior_cfg : 1;  /* bit[0]   : ����ͨ�����ȼ�����
                                                        1�������ȼ�
                                                        0�������ȼ� */
        unsigned int  dec_prior_cfg : 1;  /* bit[1]   : ����ͨ�����ȼ����ã������ͨ��������ͬʱ���ȼ����ڱ���ͨ����
                                                        1�������ȼ�
                                                        0�������ȼ� */
        unsigned int  reserved      : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_SOCP_PRIOR_CFG_UNION;
#endif
#define SOC_SOCP_PRIOR_CFG_enc_prior_cfg_START  (0)
#define SOC_SOCP_PRIOR_CFG_enc_prior_cfg_END    (0)
#define SOC_SOCP_PRIOR_CFG_dec_prior_cfg_START  (1)
#define SOC_SOCP_PRIOR_CFG_dec_prior_cfg_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_INT_TIMEOUT_UNION
 �ṹ˵��  : DEC_INT_TIMEOUT �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����жϳ�ʱ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_int_timeout_cfg : 32; /* bit[0-31]: ��ʱ�����жϳ�ʱ���á�
                                                              �ﵽ��ʱ�������ϱ���ʱ�жϡ�
                                                              ����ȫ0ʱ����ʾ�޳�ʱ�����жϡ�
                                                              ��������λΪ0xFFFF��ʱ�����ڣ���150MhzƵ����ԼΪ436.9us��
                                                              
                                                              ��GLOBAL_CTRL[1]=0, �üĴ�����ʹ�á�
                                                              ��GLOBAL_CTRL[1]=1, bit[15:0]��Ч */
    } reg;
} SOC_SOCP_DEC_INT_TIMEOUT_UNION;
#endif
#define SOC_SOCP_DEC_INT_TIMEOUT_dec_int_timeout_cfg_START  (0)
#define SOC_SOCP_DEC_INT_TIMEOUT_dec_int_timeout_cfg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_INT_TIMEOUT_UNION
 �ṹ˵��  : INT_TIMEOUT �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������жϳ�ʱ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_timeout0_cfg : 32; /* bit[0-31]: ��ʱ�����жϳ�ʱ���á�
                                                           �ﵽ��ʱ�������ϱ���ʱ�жϡ�
                                                           ����ȫ0ʱ����ʾ�޳�ʱ�����жϡ�
                                                           ��������λΪ0xFFFF��ʱ�����ڣ���150MhzƵ����ԼΪ436.9us��
                                                           
                                                           ��GLOBAL_CTRL[1]=0, bit[7:0]��Ч
                                                           ��GLOBAL_CTRL[1]=1, bit[31:0]��Ч */
    } reg;
} SOC_SOCP_INT_TIMEOUT_UNION;
#endif
#define SOC_SOCP_INT_TIMEOUT_int_timeout0_cfg_START  (0)
#define SOC_SOCP_INT_TIMEOUT_int_timeout0_cfg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_BUFFER_TIMEOUT_UNION
 �ṹ˵��  : BUFFER_TIMEOUT �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: BUFFER�����ʱ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  buffer_timeout_cfg : 16; /* bit[0-15] : ԴĿ��buffer�����ʱ���á�
                                                              Buffer��������ҵ��ﳬʱ������ֹͣ�����ϱ��жϡ���������λΪ0xFFFF��ʱ�����ڣ���150MhzƵ����ԼΪ436.9us�� */
        unsigned int  reserved           : 15; /* bit[16-30]: ���� */
        unsigned int  buffer_timeout_en  : 1;  /* bit[31]   : ԴĿ��buffer�����ʱ�ж϶���ʹ�ܡ�
                                                              1��Դ/Ŀ��buffer������ﵽ��ʱ�����󣬶�����ǰ��
                                                              0��Դ/Ŀ��buffer������ﵽ��ʱ�����󣬵ȴ� */
    } reg;
} SOC_SOCP_BUFFER_TIMEOUT_UNION;
#endif
#define SOC_SOCP_BUFFER_TIMEOUT_buffer_timeout_cfg_START  (0)
#define SOC_SOCP_BUFFER_TIMEOUT_buffer_timeout_cfg_END    (15)
#define SOC_SOCP_BUFFER_TIMEOUT_buffer_timeout_en_START   (31)
#define SOC_SOCP_BUFFER_TIMEOUT_buffer_timeout_en_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_PKT_LEN_CFG_UNION
 �ṹ˵��  : DEC_PKT_LEN_CFG �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000002�����:32
 �Ĵ���˵��: ����ͨ·���������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_max_pkt_len : 12; /* bit[0-11] : �����������ݰ���С����KBΪ��λ��
                                                           Ĭ��Ϊ2KB�� */
        unsigned int  dec_min_pkt_len : 5;  /* bit[12-16]: �������С���ݰ���С���ֽ�Ϊ��λ�� */
        unsigned int  reserved        : 15; /* bit[17-31]: ������ */
    } reg;
} SOC_SOCP_DEC_PKT_LEN_CFG_UNION;
#endif
#define SOC_SOCP_DEC_PKT_LEN_CFG_dec_max_pkt_len_START  (0)
#define SOC_SOCP_DEC_PKT_LEN_CFG_dec_max_pkt_len_END    (11)
#define SOC_SOCP_DEC_PKT_LEN_CFG_dec_min_pkt_len_START  (12)
#define SOC_SOCP_DEC_PKT_LEN_CFG_dec_min_pkt_len_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_SRCCH_SECCTRL_UNION
 �ṹ˵��  : ENC_SRCCH_SECCTRL �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Դͨ����ȫ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_srcch_secctrl : 32; /* bit[0-31]: ����Դͨ����ȫ���ơ�
                                                            1 - ͨ��NΪ��ȫͨ����
                                                            0 - ͨ��NΪ�ǰ�ȫͨ����
                                                            
                                                            �üĴ���ֻ�ܰ�ȫ���ʡ��ǰ�ȫ���ʻ���������쳣�ж�,д�������ԣ�����������0���μ�0x0F4~0x0FC */
    } reg;
} SOC_SOCP_ENC_SRCCH_SECCTRL_UNION;
#endif
#define SOC_SOCP_ENC_SRCCH_SECCTRL_enc_srcch_secctrl_START  (0)
#define SOC_SOCP_ENC_SRCCH_SECCTRL_enc_srcch_secctrl_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_DSTCH_SECCTRL_UNION
 �ṹ˵��  : ENC_DSTCH_SECCTRL �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Ŀ��ͨ����ȫ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_dstch_secctrl : 7;  /* bit[0-6] : ����Ŀ��ͨ����ȫ���ơ�
                                                            1 - ͨ��NΪ��ȫͨ����
                                                            0 - ͨ��NΪ�ǰ�ȫͨ����
                                                            
                                                            �üĴ���ֻ�ܰ�ȫ���ʡ��ǰ�ȫ���ʻ���������쳣�ж�,д�������ԣ�����������0���μ�0x0F4~0x0FC */
        unsigned int  reserved          : 25; /* bit[7-31]: ���� */
    } reg;
} SOC_SOCP_ENC_DSTCH_SECCTRL_UNION;
#endif
#define SOC_SOCP_ENC_DSTCH_SECCTRL_enc_dstch_secctrl_START  (0)
#define SOC_SOCP_ENC_DSTCH_SECCTRL_enc_dstch_secctrl_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_SRCCH_SECCTRL_UNION
 �ṹ˵��  : DEC_SRCCH_SECCTRL �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Դͨ����ȫ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_srcch_secctrl : 4;  /* bit[0-3] : ����Դ��ͨ����ȫ���ơ�
                                                            1 - ͨ��NΪ��ȫͨ����
                                                            0 - ͨ��NΪ�ǰ�ȫͨ����
                                                            
                                                            �üĴ���ֻ�ܰ�ȫ���ʡ��ǰ�ȫ���ʻ���������쳣�ж�,д�������ԣ�����������0���μ�0x0F4~0x0FC */
        unsigned int  reserved          : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_SOCP_DEC_SRCCH_SECCTRL_UNION;
#endif
#define SOC_SOCP_DEC_SRCCH_SECCTRL_dec_srcch_secctrl_START  (0)
#define SOC_SOCP_DEC_SRCCH_SECCTRL_dec_srcch_secctrl_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_DSTCH_SECCTRL_UNION
 �ṹ˵��  : DEC_DSTCH_SECCTRL �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Ŀ��ͨ����ȫ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_dstch_secctrl : 16; /* bit[0-15] : ����Ŀ�ĵ�ͨ����ȫ���ơ�
                                                             1 - ͨ��NΪ��ȫͨ����
                                                             0 - ͨ��NΪ�ǰ�ȫͨ����
                                                             
                                                             �üĴ���ֻ�ܰ�ȫ���ʡ��ǰ�ȫ���ʻ���������쳣�ж�,д�������ԣ�����������0���μ�0x0F4~0x0FC */
        unsigned int  reserved          : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SOCP_DEC_DSTCH_SECCTRL_UNION;
#endif
#define SOC_SOCP_DEC_DSTCH_SECCTRL_dec_dstch_secctrl_START  (0)
#define SOC_SOCP_DEC_DSTCH_SECCTRL_dec_dstch_secctrl_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_GLB_REG_SECCTRL_UNION
 �ṹ˵��  : GLB_REG_SECCTRL �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: ȫ�ּĴ�����ȫ���ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  glb_reg_secctrl : 1;  /* bit[0]   : ȫ�ּĴ������ʿ��ƼĴ������ơ���bitֻ����д������
                                                          1 - ֻ�ܰ�ȫ���ʣ�
                                                          0 - ���в������ɷ���
                                                          
                                                          �μ�0x0F4~0x0FC */
        unsigned int  reserved        : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_SOCP_GLB_REG_SECCTRL_UNION;
#endif
#define SOC_SOCP_GLB_REG_SECCTRL_glb_reg_secctrl_START  (0)
#define SOC_SOCP_GLB_REG_SECCTRL_glb_reg_secctrl_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_GLOBAL_INT_STATUS_UNION
 �ṹ˵��  : GLOBAL_INT_STATUS �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: ȫ���ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core0_dec_obuf_ovf_int : 1;  /* bit[0]    : core0����ͨ��Ŀ��buffer���ȫ���ж�״̬
                                                                  1�����ж�
                                                                  0�����ж� */
        unsigned int  core0_dec_err_int      : 1;  /* bit[1]    : core0����ͨ���쳣ȫ���ж�״̬
                                                                  1�����ж�
                                                                  0�����ж� */
        unsigned int  core0_dec_tfr_int      : 1;  /* bit[2]    : core0����ͨ������ȫ���ж�״̬
                                                                  1�����ж�
                                                                  0�����ж� */
        unsigned int  core1_dec_tfr_int      : 1;  /* bit[3]    : core1����ͨ������ȫ���ж�״̬
                                                                  1�����ж�
                                                                  0�����ж� */
        unsigned int  core1_dec_obuf_ovf_int : 1;  /* bit[4]    : core1����ͨ��Ŀ��buffer���ȫ���ж�״̬
                                                                  1�����ж�
                                                                  0�����ж� */
        unsigned int  core1_dec_err_int      : 1;  /* bit[5]    : core1����ͨ���쳣ȫ���ж�״̬
                                                                  1�����ж�
                                                                  0�����ж� */
        unsigned int  reserved_0             : 4;  /* bit[6-9]  : ������ */
        unsigned int  core1_enc_rdq_int      : 1;  /* bit[10]   : ��MODEM-CPU��ѯ����ͨ��Rd���ȫ���ж�״̬
                                                                  1�����ж�
                                                                  0�����ж� */
        unsigned int  core0_enc_rdq_int      : 1;  /* bit[11]   : ��APP-CPU��ѯ����ͨ��Rd���ȫ���ж�״̬
                                                                  1�����ж�
                                                                  0�����ж� */
        unsigned int  core0_enc_obuf_ovf_int : 1;  /* bit[12]   : core0����ͨ��Ŀ��buffer���ȫ���ж�״̬
                                                                  1�����ж�
                                                                  0�����ж� */
        unsigned int  core1_enc_flag_err_int : 1;  /* bit[13]   : ��MODEM-CPU��ѯ��ͷ����ȫ���ж�״̬
                                                                  1�����ж�
                                                                  0�����ж� */
        unsigned int  core0_enc_flag_err_int : 1;  /* bit[14]   : ��APP-CPU��ѯ��ͷ����ȫ���ж�״̬
                                                                  1�����ж�
                                                                  0�����ж� */
        unsigned int  core0_enc_tfr_int      : 1;  /* bit[15]   : core0����ͨ������ȫ���ж�״̬
                                                                  1�����ж�
                                                                  0�����ж� */
        unsigned int  core1_enc_obuf_ovf_int : 1;  /* bit[16]   : core1����ͨ��Ŀ��buffer���ȫ���ж�״̬
                                                                  1�����ж�
                                                                  0�����ж� */
        unsigned int  core1_enc_tfr_int      : 1;  /* bit[17]   : core1����ͨ������ȫ���ж�״̬
                                                                  1�����ж�
                                                                  0�����ж� */
        unsigned int  bus_err_int            : 1;  /* bit[18]   : �����쳣ȫ���ж�״̬
                                                                  1�����ж�
                                                                  0�����ж� */
        unsigned int  reserved_1             : 13; /* bit[19-31]: ������ */
    } reg;
} SOC_SOCP_GLOBAL_INT_STATUS_UNION;
#endif
#define SOC_SOCP_GLOBAL_INT_STATUS_core0_dec_obuf_ovf_int_START  (0)
#define SOC_SOCP_GLOBAL_INT_STATUS_core0_dec_obuf_ovf_int_END    (0)
#define SOC_SOCP_GLOBAL_INT_STATUS_core0_dec_err_int_START       (1)
#define SOC_SOCP_GLOBAL_INT_STATUS_core0_dec_err_int_END         (1)
#define SOC_SOCP_GLOBAL_INT_STATUS_core0_dec_tfr_int_START       (2)
#define SOC_SOCP_GLOBAL_INT_STATUS_core0_dec_tfr_int_END         (2)
#define SOC_SOCP_GLOBAL_INT_STATUS_core1_dec_tfr_int_START       (3)
#define SOC_SOCP_GLOBAL_INT_STATUS_core1_dec_tfr_int_END         (3)
#define SOC_SOCP_GLOBAL_INT_STATUS_core1_dec_obuf_ovf_int_START  (4)
#define SOC_SOCP_GLOBAL_INT_STATUS_core1_dec_obuf_ovf_int_END    (4)
#define SOC_SOCP_GLOBAL_INT_STATUS_core1_dec_err_int_START       (5)
#define SOC_SOCP_GLOBAL_INT_STATUS_core1_dec_err_int_END         (5)
#define SOC_SOCP_GLOBAL_INT_STATUS_core1_enc_rdq_int_START       (10)
#define SOC_SOCP_GLOBAL_INT_STATUS_core1_enc_rdq_int_END         (10)
#define SOC_SOCP_GLOBAL_INT_STATUS_core0_enc_rdq_int_START       (11)
#define SOC_SOCP_GLOBAL_INT_STATUS_core0_enc_rdq_int_END         (11)
#define SOC_SOCP_GLOBAL_INT_STATUS_core0_enc_obuf_ovf_int_START  (12)
#define SOC_SOCP_GLOBAL_INT_STATUS_core0_enc_obuf_ovf_int_END    (12)
#define SOC_SOCP_GLOBAL_INT_STATUS_core1_enc_flag_err_int_START  (13)
#define SOC_SOCP_GLOBAL_INT_STATUS_core1_enc_flag_err_int_END    (13)
#define SOC_SOCP_GLOBAL_INT_STATUS_core0_enc_flag_err_int_START  (14)
#define SOC_SOCP_GLOBAL_INT_STATUS_core0_enc_flag_err_int_END    (14)
#define SOC_SOCP_GLOBAL_INT_STATUS_core0_enc_tfr_int_START       (15)
#define SOC_SOCP_GLOBAL_INT_STATUS_core0_enc_tfr_int_END         (15)
#define SOC_SOCP_GLOBAL_INT_STATUS_core1_enc_obuf_ovf_int_START  (16)
#define SOC_SOCP_GLOBAL_INT_STATUS_core1_enc_obuf_ovf_int_END    (16)
#define SOC_SOCP_GLOBAL_INT_STATUS_core1_enc_tfr_int_START       (17)
#define SOC_SOCP_GLOBAL_INT_STATUS_core1_enc_tfr_int_END         (17)
#define SOC_SOCP_GLOBAL_INT_STATUS_bus_err_int_START             (18)
#define SOC_SOCP_GLOBAL_INT_STATUS_bus_err_int_END               (18)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE0_MASK0_UNION
 �ṹ˵��  : ENC_CORE0_MASK0 �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x0000007F�����:32
 �Ĵ���˵��: CORE0���봫���ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core0_enc_tfr_mask : 7;  /* bit[0-6] : core0����ͨ·�����ж����ο���λ��ÿ��bit��Ӧһ��Ŀ��buffer��Bit0��ӦĿ��buffer0�� 
                                                             1�������ж�
                                                             0���������ж� */
        unsigned int  reserved           : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_SOCP_ENC_CORE0_MASK0_UNION;
#endif
#define SOC_SOCP_ENC_CORE0_MASK0_core0_enc_tfr_mask_START  (0)
#define SOC_SOCP_ENC_CORE0_MASK0_core0_enc_tfr_mask_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE0_RAWINT0_UNION
 �ṹ˵��  : ENC_CORE0_RAWINT0 �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00000000�����:32
 �Ĵ���˵��: CORE0���봫���ж�ԭʼ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_tfr_rawint : 7;  /* bit[0-6] : ����ͨ·ԭʼ�����ж�״̬,д1�塣ÿ��bit��Ӧһ��Ŀ��buffer��Bit0��ӦĿ��buffer0��
                                                         1�����ж�
                                                         0�����ж� */
        unsigned int  reserved       : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_SOCP_ENC_CORE0_RAWINT0_UNION;
#endif
#define SOC_SOCP_ENC_CORE0_RAWINT0_enc_tfr_rawint_START  (0)
#define SOC_SOCP_ENC_CORE0_RAWINT0_enc_tfr_rawint_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE0_INT0_UNION
 �ṹ˵��  : ENC_CORE0_INT0 �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CORE0���봫���ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core0_enc_tfr_maskint : 7;  /* bit[0-6] : core0����ͨ·���κ����ж�״̬��ÿ��bit��Ӧһ��Ŀ��buffer��Bit0��ӦĿ��buffer0��
                                                                1�����ж�
                                                                0�����ж� */
        unsigned int  reserved              : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_SOCP_ENC_CORE0_INT0_UNION;
#endif
#define SOC_SOCP_ENC_CORE0_INT0_core0_enc_tfr_maskint_START  (0)
#define SOC_SOCP_ENC_CORE0_INT0_core0_enc_tfr_maskint_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE0_MASK1_UNION
 �ṹ˵��  : ENC_CORE0_MASK1 �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: CORE0����ͷ��־���ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ����ͨ·Դ���ݰ�ͷ�����ж����ο���λ��APP-cpu���ã�ÿ��bit��Ӧһ���߼�ͨ����Bit0��Ӧ�߼�ͨ��0
                                                   1�������ж�
                                                   0���������ж� */
    } reg;
} SOC_SOCP_ENC_CORE0_MASK1_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE1_MASK1_UNION
 �ṹ˵��  : ENC_CORE1_MASK1 �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: CORE1����ͷ��־���ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ����ͨ·Դ���ݰ�ͷ�����ж����ο���λ��MODEM-cpu���ã�ÿ��bit��Ӧһ���߼�ͨ����Bit0��Ӧ�߼�ͨ��0
                                                   1�������ж�
                                                   0���������ж� */
    } reg;
} SOC_SOCP_ENC_CORE1_MASK1_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_RAWINT1_UNION
 �ṹ˵��  : ENC_RAWINT1 �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��ͷ��־���ж�ԭʼ״̬�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_flag_err_rawint : 32; /* bit[0-31]: ����ͨ·Դ���ݰ�ͷ��ԭʼ�ж�״̬λ,д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                              1�����ж�
                                                              0�����ж� */
    } reg;
} SOC_SOCP_ENC_RAWINT1_UNION;
#endif
#define SOC_SOCP_ENC_RAWINT1_enc_flag_err_rawint_START  (0)
#define SOC_SOCP_ENC_RAWINT1_enc_flag_err_rawint_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE0_INT1_UNION
 �ṹ˵��  : ENC_CORE0_INT1 �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CORE0����ͨ��ͷ��־���ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_flag_err_app_maskint : 32; /* bit[0-31]: ����ͨ·Դ���ݰ�ͷ�������ж�״̬λ(��APP-cpu��ѯ)ÿ��bit��Ӧһ���߼�ͨ��
                                                                   1�����ж�
                                                                   0�����ж� */
    } reg;
} SOC_SOCP_ENC_CORE0_INT1_UNION;
#endif
#define SOC_SOCP_ENC_CORE0_INT1_enc_flag_err_app_maskint_START  (0)
#define SOC_SOCP_ENC_CORE0_INT1_enc_flag_err_app_maskint_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE1_INT1_UNION
 �ṹ˵��  : ENC_CORE1_INT1 �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00000000�����:32
 �Ĵ���˵��: CORE1����ͨ��ͷ��־���ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_flag_err_modem_maskint : 32; /* bit[0-31]: ����ͨ·Դ���ݰ�ͷ�������ж�״̬λ(��MODEM-cpu��ѯ)ÿ��bit��Ӧһ���߼�ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
    } reg;
} SOC_SOCP_ENC_CORE1_INT1_UNION;
#endif
#define SOC_SOCP_ENC_CORE1_INT1_enc_flag_err_modem_maskint_START  (0)
#define SOC_SOCP_ENC_CORE1_INT1_enc_flag_err_modem_maskint_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE0_MASK2_UNION
 �ṹ˵��  : ENC_CORE0_MASK2 �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x007F007F�����:32
 �Ĵ���˵��: CORE0����Ŀ��buffer�����ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core0_enc_obuf_ovf_mask      : 7;  /* bit[0-6]  : core0����Ŀ��bufferʣ��ռ䲻��һ��dma����ʱ�����ж����ο��ƣ�ÿ��bit��Ӧһ��Ŀ��buffer
                                                                        1�������ж�
                                                                        0���������ж� */
        unsigned int  reserved_0                   : 9;  /* bit[7-15] : ������ */
        unsigned int  core0_enc_obuf_thrh_ovf_mask : 7;  /* bit[16-22]: core0��Ŀ��bufferʣ��ռ�С�����õ���ֵʱ�����ж����ο��ƣ�ÿ��bit��Ӧһ��Ŀ��buffer
                                                                        1�������ж�
                                                                        0���������ж� */
        unsigned int  reserved_1                   : 9;  /* bit[23-31]: ������ */
    } reg;
} SOC_SOCP_ENC_CORE0_MASK2_UNION;
#endif
#define SOC_SOCP_ENC_CORE0_MASK2_core0_enc_obuf_ovf_mask_START       (0)
#define SOC_SOCP_ENC_CORE0_MASK2_core0_enc_obuf_ovf_mask_END         (6)
#define SOC_SOCP_ENC_CORE0_MASK2_core0_enc_obuf_thrh_ovf_mask_START  (16)
#define SOC_SOCP_ENC_CORE0_MASK2_core0_enc_obuf_thrh_ovf_mask_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE0_RAWINT2_UNION
 �ṹ˵��  : ENC_CORE0_RAWINT2 �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Ŀ��buffer����ԭʼ�ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_obuf_ovf_rawint      : 7;  /* bit[0-6]  : ����Ŀ��bufferʣ��ռ䲻��һ��dma����ʱ����ԭʼ�ж�״̬,д1�壬ÿ��bit��Ӧһ��Ŀ��buffer
                                                                    1�����ж�
                                                                    0�����ж� */
        unsigned int  reserved_0               : 9;  /* bit[7-15] : ������ */
        unsigned int  enc_obuf_thrh_ovf_rawint : 7;  /* bit[16-22]: ��Ŀ��bufferʣ��ռ�С�����õ���ֵʱ����ԭʼ�ж�״̬��д1�壬ÿ��bit��Ӧһ��Ŀ��buffer
                                                                    1�����ж�
                                                                    0�����ж� */
        unsigned int  reserved_1               : 9;  /* bit[23-31]: ������ */
    } reg;
} SOC_SOCP_ENC_CORE0_RAWINT2_UNION;
#endif
#define SOC_SOCP_ENC_CORE0_RAWINT2_enc_obuf_ovf_rawint_START       (0)
#define SOC_SOCP_ENC_CORE0_RAWINT2_enc_obuf_ovf_rawint_END         (6)
#define SOC_SOCP_ENC_CORE0_RAWINT2_enc_obuf_thrh_ovf_rawint_START  (16)
#define SOC_SOCP_ENC_CORE0_RAWINT2_enc_obuf_thrh_ovf_rawint_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE0_INT2_UNION
 �ṹ˵��  : ENC_CORE0_INT2 �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CORE0����Ŀ��buffer�����ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core0_enc_obuf_ovf_maskint      : 7;  /* bit[0-6]  : core0����Ŀ��bufferʣ��ռ䲻��һ��dma����ʱ�������κ��ж�״̬��ÿ��bit��Ӧһ��Ŀ��buffer
                                                                           1�����ж�
                                                                           0�����ж� */
        unsigned int  reserved_0                      : 9;  /* bit[7-15] : ������ */
        unsigned int  core0_enc_obuf_thrh_ovf_maskint : 7;  /* bit[16-22]: core0����Ŀ��bufferʣ��ռ�С�����õ���ֵʱ�������κ��ж�״̬��ÿ��bit��Ӧһ��Ŀ��buffer
                                                                           1�����ж�
                                                                           0�����ж� */
        unsigned int  reserved_1                      : 9;  /* bit[23-31]: ������ */
    } reg;
} SOC_SOCP_ENC_CORE0_INT2_UNION;
#endif
#define SOC_SOCP_ENC_CORE0_INT2_core0_enc_obuf_ovf_maskint_START       (0)
#define SOC_SOCP_ENC_CORE0_INT2_core0_enc_obuf_ovf_maskint_END         (6)
#define SOC_SOCP_ENC_CORE0_INT2_core0_enc_obuf_thrh_ovf_maskint_START  (16)
#define SOC_SOCP_ENC_CORE0_INT2_core0_enc_obuf_thrh_ovf_maskint_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE0_MASK3_UNION
 �ṹ˵��  : ENC_CORE0_MASK3 �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: CORE0����RD�ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core0_enc_rdq_done_mask : 32; /* bit[0-31]: CORE0����ͨ·RD��������ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                  1�������ж�
                                                                  0���������ж� */
    } reg;
} SOC_SOCP_ENC_CORE0_MASK3_UNION;
#endif
#define SOC_SOCP_ENC_CORE0_MASK3_core0_enc_rdq_done_mask_START  (0)
#define SOC_SOCP_ENC_CORE0_MASK3_core0_enc_rdq_done_mask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE1_MASK3_UNION
 �ṹ˵��  : ENC_CORE1_MASK3 �Ĵ����ṹ���塣��ַƫ����:0x084����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: CORE1����RD�ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core0_enc_rdq_done_mask : 32; /* bit[0-31]: CORE1����ͨ·RD��������ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                  1�������ж�
                                                                  0���������ж� */
    } reg;
} SOC_SOCP_ENC_CORE1_MASK3_UNION;
#endif
#define SOC_SOCP_ENC_CORE1_MASK3_core0_enc_rdq_done_mask_START  (0)
#define SOC_SOCP_ENC_CORE1_MASK3_core0_enc_rdq_done_mask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_RAWINT3_UNION
 �ṹ˵��  : ENC_RAWINT3 �Ĵ����ṹ���塣��ַƫ����:0x088����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��RDԭʼ�ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_rdq_done_rawint : 32; /* bit[0-31]: ����ͨ·RD�������ԭʼ�ж�״̬,д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                              1�����ж�
                                                              0�����ж� */
    } reg;
} SOC_SOCP_ENC_RAWINT3_UNION;
#endif
#define SOC_SOCP_ENC_RAWINT3_enc_rdq_done_rawint_START  (0)
#define SOC_SOCP_ENC_RAWINT3_enc_rdq_done_rawint_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE0_INT3_UNION
 �ṹ˵��  : ENC_CORE0_INT3 �Ĵ����ṹ���塣��ַƫ����:0x08C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CORE0����RD�ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core0_enc_rdq_done_int : 32; /* bit[0-31]: CORE0����ͨ·RD����������κ��ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                 1�����ж�
                                                                 0�����ж� */
    } reg;
} SOC_SOCP_ENC_CORE0_INT3_UNION;
#endif
#define SOC_SOCP_ENC_CORE0_INT3_core0_enc_rdq_done_int_START  (0)
#define SOC_SOCP_ENC_CORE0_INT3_core0_enc_rdq_done_int_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE1_INT3_UNION
 �ṹ˵��  : ENC_CORE1_INT3 �Ĵ����ṹ���塣��ַƫ����:0x090����ֵ:0x00000000�����:32
 �Ĵ���˵��: CORE1����RD�ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core1_enc_rdq_done_int : 32; /* bit[0-31]: CORE1����ͨ·RD����������κ��ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                 1�����ж�
                                                                 0�����ж� */
    } reg;
} SOC_SOCP_ENC_CORE1_INT3_UNION;
#endif
#define SOC_SOCP_ENC_CORE1_INT3_core1_enc_rdq_done_int_START  (0)
#define SOC_SOCP_ENC_CORE1_INT3_core1_enc_rdq_done_int_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_CORE0_MASK0_UNION
 �ṹ˵��  : DEC_CORE0_MASK0 �Ĵ����ṹ���塣��ַƫ����:0x0A8����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: CORE0����ͨ�������ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core0_dtype0_tfr_int_mask0 : 4;  /* bit[0-3]  : core0����ͨ·DATA-TYPE0�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                      1�������ж�
                                                                      0���������ж� */
        unsigned int  core0_dtype1_tfr_int_mask1 : 4;  /* bit[4-7]  : core0����ͨ·DATA-TYPE1�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                      1�������ж�
                                                                      0���������ж� */
        unsigned int  core0_dtype2_tfr_int_mask2 : 4;  /* bit[8-11] : core0����ͨ·DATA-TYPE2�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                      1�������ж�
                                                                      0���������ж� */
        unsigned int  core0_dtype3_tfr_int_mask3 : 4;  /* bit[12-15]: core0����ͨ·DATA-TYPE3�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                      1�������ж�
                                                                      0���������ж� */
        unsigned int  reserved                   : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SOCP_DEC_CORE0_MASK0_UNION;
#endif
#define SOC_SOCP_DEC_CORE0_MASK0_core0_dtype0_tfr_int_mask0_START  (0)
#define SOC_SOCP_DEC_CORE0_MASK0_core0_dtype0_tfr_int_mask0_END    (3)
#define SOC_SOCP_DEC_CORE0_MASK0_core0_dtype1_tfr_int_mask1_START  (4)
#define SOC_SOCP_DEC_CORE0_MASK0_core0_dtype1_tfr_int_mask1_END    (7)
#define SOC_SOCP_DEC_CORE0_MASK0_core0_dtype2_tfr_int_mask2_START  (8)
#define SOC_SOCP_DEC_CORE0_MASK0_core0_dtype2_tfr_int_mask2_END    (11)
#define SOC_SOCP_DEC_CORE0_MASK0_core0_dtype3_tfr_int_mask3_START  (12)
#define SOC_SOCP_DEC_CORE0_MASK0_core0_dtype3_tfr_int_mask3_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_CORE1_MASK0_UNION
 �ṹ˵��  : DEC_CORE1_MASK0 �Ĵ����ṹ���塣��ַƫ����:0x0AC����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: CORE1����ͨ�������ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core1_dtype0_tfr_int_mask0 : 4;  /* bit[0-3]  : core1����ͨ·DATA-TYPE0�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                      1�������ж�
                                                                      0���������ж� */
        unsigned int  core1_dtype1_tfr_int_mask1 : 4;  /* bit[4-7]  : core1����ͨ·DATA-TYPE1�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                      1�������ж�
                                                                      0���������ж� */
        unsigned int  core1_dtype2_tfr_int_mask2 : 4;  /* bit[8-11] : core1����ͨ·DATA-TYPE2�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                      1�������ж�
                                                                      0���������ж� */
        unsigned int  core1_dtype3_tfr_int_mask3 : 4;  /* bit[12-15]: core1����ͨ·DATA-TYPE3�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                      1�������ж�
                                                                      0���������ж� */
        unsigned int  reserved                   : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SOCP_DEC_CORE1_MASK0_UNION;
#endif
#define SOC_SOCP_DEC_CORE1_MASK0_core1_dtype0_tfr_int_mask0_START  (0)
#define SOC_SOCP_DEC_CORE1_MASK0_core1_dtype0_tfr_int_mask0_END    (3)
#define SOC_SOCP_DEC_CORE1_MASK0_core1_dtype1_tfr_int_mask1_START  (4)
#define SOC_SOCP_DEC_CORE1_MASK0_core1_dtype1_tfr_int_mask1_END    (7)
#define SOC_SOCP_DEC_CORE1_MASK0_core1_dtype2_tfr_int_mask2_START  (8)
#define SOC_SOCP_DEC_CORE1_MASK0_core1_dtype2_tfr_int_mask2_END    (11)
#define SOC_SOCP_DEC_CORE1_MASK0_core1_dtype3_tfr_int_mask3_START  (12)
#define SOC_SOCP_DEC_CORE1_MASK0_core1_dtype3_tfr_int_mask3_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_RAWINT0_UNION
 �ṹ˵��  : DEC_RAWINT0 �Ĵ����ṹ���塣��ַƫ����:0x0B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ���ж�ԭʼ״̬�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dtype0_tfr_rawint0 : 4;  /* bit[0-3]  : ����ͨ·DATA-TYPE0ԭʼ�����ж�״̬,д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                              1�����ж�
                                                              0�����ж� */
        unsigned int  dtype1_tfr_rawint1 : 4;  /* bit[4-7]  : ����ͨ·DATA-TYPE1ԭʼ�����ж�״̬,д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                              1�����ж�
                                                              0�����ж� */
        unsigned int  dtype2_tfr_rawint2 : 4;  /* bit[8-11] : ����ͨ·DATA-TYPE2ԭʼ�����ж�״̬,д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                              1�����ж�
                                                              0�����ж� */
        unsigned int  dtype3_tfr_rawint3 : 4;  /* bit[12-15]: ����ͨ·DATA-TYPE3ԭʼ�����ж�״̬,д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                              1�����ж�
                                                              0�����ж� */
        unsigned int  reserved           : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SOCP_DEC_RAWINT0_UNION;
#endif
#define SOC_SOCP_DEC_RAWINT0_dtype0_tfr_rawint0_START  (0)
#define SOC_SOCP_DEC_RAWINT0_dtype0_tfr_rawint0_END    (3)
#define SOC_SOCP_DEC_RAWINT0_dtype1_tfr_rawint1_START  (4)
#define SOC_SOCP_DEC_RAWINT0_dtype1_tfr_rawint1_END    (7)
#define SOC_SOCP_DEC_RAWINT0_dtype2_tfr_rawint2_START  (8)
#define SOC_SOCP_DEC_RAWINT0_dtype2_tfr_rawint2_END    (11)
#define SOC_SOCP_DEC_RAWINT0_dtype3_tfr_rawint3_START  (12)
#define SOC_SOCP_DEC_RAWINT0_dtype3_tfr_rawint3_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_CORE0_INT0_UNION
 �ṹ˵��  : DEC_CORE0_INT0 �Ĵ����ṹ���塣��ַƫ����:0x0B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: CORE0����ͨ�������ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core0_dtype0_tfr_maskint0 : 4;  /* bit[0-3]  : core0����ͨ·DATA-TYPE0���κ����ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  core0_dtype1_tfr_maskint1 : 4;  /* bit[4-7]  : core0����ͨ·DATA-TYPE1���κ����ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  core0_dtype2_tfr_maskint2 : 4;  /* bit[8-11] : core0����ͨ·DATA-TYPE2���κ����ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  core0_dtype3_tfr_maskint3 : 4;  /* bit[12-15]: core0����ͨ·DATA-TYPE3���κ����ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  reserved                  : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SOCP_DEC_CORE0_INT0_UNION;
#endif
#define SOC_SOCP_DEC_CORE0_INT0_core0_dtype0_tfr_maskint0_START  (0)
#define SOC_SOCP_DEC_CORE0_INT0_core0_dtype0_tfr_maskint0_END    (3)
#define SOC_SOCP_DEC_CORE0_INT0_core0_dtype1_tfr_maskint1_START  (4)
#define SOC_SOCP_DEC_CORE0_INT0_core0_dtype1_tfr_maskint1_END    (7)
#define SOC_SOCP_DEC_CORE0_INT0_core0_dtype2_tfr_maskint2_START  (8)
#define SOC_SOCP_DEC_CORE0_INT0_core0_dtype2_tfr_maskint2_END    (11)
#define SOC_SOCP_DEC_CORE0_INT0_core0_dtype3_tfr_maskint3_START  (12)
#define SOC_SOCP_DEC_CORE0_INT0_core0_dtype3_tfr_maskint3_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_CORE1_INT0_UNION
 �ṹ˵��  : DEC_CORE1_INT0 �Ĵ����ṹ���塣��ַƫ����:0x0B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: CORE1����ͨ�������ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core1_dtype0_tfr_maskint0 : 4;  /* bit[0-3]  : core1����ͨ·DATA-TYPE0���κ����ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  core1_dtype1_tfr_maskint1 : 4;  /* bit[4-7]  : core1����ͨ·DATA-TYPE1���κ����ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  core1_dtype2_tfr_maskint2 : 4;  /* bit[8-11] : core1����ͨ·DATA-TYPE2���κ����ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  core1_dtype3_tfr_maskint3 : 4;  /* bit[12-15]: core1����ͨ·DATA-TYPE3���κ����ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  reserved                  : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SOCP_DEC_CORE1_INT0_UNION;
#endif
#define SOC_SOCP_DEC_CORE1_INT0_core1_dtype0_tfr_maskint0_START  (0)
#define SOC_SOCP_DEC_CORE1_INT0_core1_dtype0_tfr_maskint0_END    (3)
#define SOC_SOCP_DEC_CORE1_INT0_core1_dtype1_tfr_maskint1_START  (4)
#define SOC_SOCP_DEC_CORE1_INT0_core1_dtype1_tfr_maskint1_END    (7)
#define SOC_SOCP_DEC_CORE1_INT0_core1_dtype2_tfr_maskint2_START  (8)
#define SOC_SOCP_DEC_CORE1_INT0_core1_dtype2_tfr_maskint2_END    (11)
#define SOC_SOCP_DEC_CORE1_INT0_core1_dtype3_tfr_maskint3_START  (12)
#define SOC_SOCP_DEC_CORE1_INT0_core1_dtype3_tfr_maskint3_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_CORE0_MASK1_UNION
 �ṹ˵��  : DEC_CORE0_MASK1 �Ĵ����ṹ���塣��ַƫ����:0x0BC����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: CORE0����ͨ���쳣�ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                    : 4;  /* bit[0-3]  : ���� */
        unsigned int  core0_dec_ibuf_underflow_mask : 4;  /* bit[4-7]  : core0����Դbuffer�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                         1�������ж�
                                                                         0���������ж� */
        unsigned int  core0_dec_flag_unmatch_mask   : 4;  /* bit[8-11] : core0�����־(0x7E)��ƥ���ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                         1�������ж�
                                                                         0���������ж� */
        unsigned int  core0_dec_dtype_unmatch_mask  : 4;  /* bit[12-15]: core0����Ŀ��bufferID��ƥ���ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                         1�������ж�
                                                                         0���������ж� */
        unsigned int  core0_dec_crc_err_mask        : 4;  /* bit[16-19]: core0����ͨ·CRC���ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                         1�������ж�
                                                                         0���������ж� */
        unsigned int  core0_dec_len_err_mask        : 4;  /* bit[20-23]: core0����ͨ·�����ȴ��ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                         1�������ж�
                                                                         0���������ж� */
        unsigned int  core0_dec_7d_err_mask         : 4;  /* bit[24-27]: core0����ͨ·7D�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                         1�������ж�
                                                                         0���������ж� */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_SOCP_DEC_CORE0_MASK1_UNION;
#endif
#define SOC_SOCP_DEC_CORE0_MASK1_core0_dec_ibuf_underflow_mask_START  (4)
#define SOC_SOCP_DEC_CORE0_MASK1_core0_dec_ibuf_underflow_mask_END    (7)
#define SOC_SOCP_DEC_CORE0_MASK1_core0_dec_flag_unmatch_mask_START    (8)
#define SOC_SOCP_DEC_CORE0_MASK1_core0_dec_flag_unmatch_mask_END      (11)
#define SOC_SOCP_DEC_CORE0_MASK1_core0_dec_dtype_unmatch_mask_START   (12)
#define SOC_SOCP_DEC_CORE0_MASK1_core0_dec_dtype_unmatch_mask_END     (15)
#define SOC_SOCP_DEC_CORE0_MASK1_core0_dec_crc_err_mask_START         (16)
#define SOC_SOCP_DEC_CORE0_MASK1_core0_dec_crc_err_mask_END           (19)
#define SOC_SOCP_DEC_CORE0_MASK1_core0_dec_len_err_mask_START         (20)
#define SOC_SOCP_DEC_CORE0_MASK1_core0_dec_len_err_mask_END           (23)
#define SOC_SOCP_DEC_CORE0_MASK1_core0_dec_7d_err_mask_START          (24)
#define SOC_SOCP_DEC_CORE0_MASK1_core0_dec_7d_err_mask_END            (27)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_CORE0_RAWINT1_UNION
 �ṹ˵��  : DEC_CORE0_RAWINT1 �Ĵ����ṹ���塣��ַƫ����:0x0C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ���쳣�ж�ԭʼ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                 : 4;  /* bit[0-3]  : ���� */
        unsigned int  dec_ibuf_underflow_rawint  : 4;  /* bit[4-7]  : ����Դbuffer����ԭʼ�ж�״̬,д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                                      1�����ж�
                                                                      0�����ж� */
        unsigned int  dec_flag_unmatch_rawint    : 4;  /* bit[8-11] : �����־(0x7E)��ƥ��ԭʼ�ж�״̬,д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                                      1�����ж�
                                                                      0�����ж� */
        unsigned int  dec_obuf_id_unmatch_rawint : 4;  /* bit[12-15]: ����Ŀ��bufferID��ƥ��ԭʼ�ж�״̬,д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                                      1�����ж�
                                                                      0�����ж� */
        unsigned int  dec_crc_err_rawint         : 4;  /* bit[16-19]: ����ͨ·CRC��ԭʼ�ж�״̬,д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                                      1�����ж�
                                                                      0�����ж� */
        unsigned int  dec_len_err_rawint         : 4;  /* bit[20-23]: ����ͨ·�����ȴ�ԭʼ�ж�״̬,д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                                      1�����ж�
                                                                      0�����ж� */
        unsigned int  dec_7d_err_rawint          : 4;  /* bit[24-27]: ����ͨ·7D����ԭʼ�ж�״̬��д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                                      1�����ж�
                                                                      0�����ж� */
        unsigned int  reserved_1                 : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_SOCP_DEC_CORE0_RAWINT1_UNION;
#endif
#define SOC_SOCP_DEC_CORE0_RAWINT1_dec_ibuf_underflow_rawint_START   (4)
#define SOC_SOCP_DEC_CORE0_RAWINT1_dec_ibuf_underflow_rawint_END     (7)
#define SOC_SOCP_DEC_CORE0_RAWINT1_dec_flag_unmatch_rawint_START     (8)
#define SOC_SOCP_DEC_CORE0_RAWINT1_dec_flag_unmatch_rawint_END       (11)
#define SOC_SOCP_DEC_CORE0_RAWINT1_dec_obuf_id_unmatch_rawint_START  (12)
#define SOC_SOCP_DEC_CORE0_RAWINT1_dec_obuf_id_unmatch_rawint_END    (15)
#define SOC_SOCP_DEC_CORE0_RAWINT1_dec_crc_err_rawint_START          (16)
#define SOC_SOCP_DEC_CORE0_RAWINT1_dec_crc_err_rawint_END            (19)
#define SOC_SOCP_DEC_CORE0_RAWINT1_dec_len_err_rawint_START          (20)
#define SOC_SOCP_DEC_CORE0_RAWINT1_dec_len_err_rawint_END            (23)
#define SOC_SOCP_DEC_CORE0_RAWINT1_dec_7d_err_rawint_START           (24)
#define SOC_SOCP_DEC_CORE0_RAWINT1_dec_7d_err_rawint_END             (27)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_CORE0_INT1_UNION
 �ṹ˵��  : DEC_CORE0_INT1 �Ĵ����ṹ���塣��ַƫ����:0x0C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: CORE0����ͨ���쳣�ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                        : 4;  /* bit[0-3]  : ���� */
        unsigned int  core0_dec_ibuf_underflow_maskint  : 4;  /* bit[4-7]  : core0����Դbuffer�����ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                             1�����ж�
                                                                             0�����ж� */
        unsigned int  core0_dec_flag_unmatch_maskint    : 4;  /* bit[8-11] : core0�����־(0x7E)��ƥ���ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                             1�����ж�
                                                                             0�����ж� */
        unsigned int  core0_dec_obuf_id_unmatch_maskint : 4;  /* bit[12-15]: core0����ID��ƥ���ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                             1�����ж�
                                                                             0�����ж� */
        unsigned int  core0_dec_crc_err_maskint         : 4;  /* bit[16-19]: core0����ͨ·CRC���ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                             1�����ж�
                                                                             0�����ж� */
        unsigned int  core0_dec_len_err_maskint         : 4;  /* bit[20-23]: core0����ͨ·�����ȴ��ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                             1�����ж�
                                                                             0�����ж� */
        unsigned int  core0_dec_7d_err_maskint          : 4;  /* bit[24-27]: core0����ͨ·7D�����ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                             1�����ж�
                                                                             0�����ж� */
        unsigned int  reserved_1                        : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_SOCP_DEC_CORE0_INT1_UNION;
#endif
#define SOC_SOCP_DEC_CORE0_INT1_core0_dec_ibuf_underflow_maskint_START   (4)
#define SOC_SOCP_DEC_CORE0_INT1_core0_dec_ibuf_underflow_maskint_END     (7)
#define SOC_SOCP_DEC_CORE0_INT1_core0_dec_flag_unmatch_maskint_START     (8)
#define SOC_SOCP_DEC_CORE0_INT1_core0_dec_flag_unmatch_maskint_END       (11)
#define SOC_SOCP_DEC_CORE0_INT1_core0_dec_obuf_id_unmatch_maskint_START  (12)
#define SOC_SOCP_DEC_CORE0_INT1_core0_dec_obuf_id_unmatch_maskint_END    (15)
#define SOC_SOCP_DEC_CORE0_INT1_core0_dec_crc_err_maskint_START          (16)
#define SOC_SOCP_DEC_CORE0_INT1_core0_dec_crc_err_maskint_END            (19)
#define SOC_SOCP_DEC_CORE0_INT1_core0_dec_len_err_maskint_START          (20)
#define SOC_SOCP_DEC_CORE0_INT1_core0_dec_len_err_maskint_END            (23)
#define SOC_SOCP_DEC_CORE0_INT1_core0_dec_7d_err_maskint_START           (24)
#define SOC_SOCP_DEC_CORE0_INT1_core0_dec_7d_err_maskint_END             (27)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_CORE0_MASK2_UNION
 �ṹ˵��  : DEC_CORE0_MASK2 �Ĵ����ṹ���塣��ַƫ����:0x0C8����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: CORE0����ͨ��Ŀ��buffer����ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core0_dtype0_obuf_ovf_mask0 : 4;  /* bit[0-3]  : core0����DATA-TYPE0Ŀ��buffer�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                       1�������ж�
                                                                       0���������ж� */
        unsigned int  core0_dtype1_obuf_ovf_mask1 : 4;  /* bit[4-7]  : core0����DATA-TYPE1Ŀ��buffer�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                       1�������ж�
                                                                       0���������ж� */
        unsigned int  core0_dtype2_obuf_ovf_mask2 : 4;  /* bit[8-11] : core0����DATA-TYPE2Ŀ��buffer�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                       1�������ж�
                                                                       0���������ж� */
        unsigned int  core0_dtype3_obuf_ovf_mask3 : 4;  /* bit[12-15]: core0����DATA-TYPE3Ŀ��buffer�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                       1�������ж�
                                                                       0���������ж� */
        unsigned int  reserved                    : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SOCP_DEC_CORE0_MASK2_UNION;
#endif
#define SOC_SOCP_DEC_CORE0_MASK2_core0_dtype0_obuf_ovf_mask0_START  (0)
#define SOC_SOCP_DEC_CORE0_MASK2_core0_dtype0_obuf_ovf_mask0_END    (3)
#define SOC_SOCP_DEC_CORE0_MASK2_core0_dtype1_obuf_ovf_mask1_START  (4)
#define SOC_SOCP_DEC_CORE0_MASK2_core0_dtype1_obuf_ovf_mask1_END    (7)
#define SOC_SOCP_DEC_CORE0_MASK2_core0_dtype2_obuf_ovf_mask2_START  (8)
#define SOC_SOCP_DEC_CORE0_MASK2_core0_dtype2_obuf_ovf_mask2_END    (11)
#define SOC_SOCP_DEC_CORE0_MASK2_core0_dtype3_obuf_ovf_mask3_START  (12)
#define SOC_SOCP_DEC_CORE0_MASK2_core0_dtype3_obuf_ovf_mask3_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_CORE1NOTE_MASK2_UNION
 �ṹ˵��  : DEC_CORE1NOTE_MASK2 �Ĵ����ṹ���塣��ַƫ����:0x0CC����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: CORE1����ͨ��Ŀ��buffer����ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core1_dtype0_obuf_ovf_mask0 : 4;  /* bit[0-3]  : core1����DATA-TYPE0Ŀ��buffer�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                       1�������ж�
                                                                       0���������ж� */
        unsigned int  core1_dtype1_obuf_ovf_mask1 : 4;  /* bit[4-7]  : core1����DATA-TYPE1Ŀ��buffer�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                       1�������ж�
                                                                       0���������ж� */
        unsigned int  core1_dtype2_obuf_ovf_mask2 : 4;  /* bit[8-11] : core1����DATA-TYPE2Ŀ��buffer�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                       1�������ж�
                                                                       0���������ж� */
        unsigned int  core1_dtype3_obuf_ovf_mask3 : 4;  /* bit[12-15]: core1����DATA-TYPE3Ŀ��buffer�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                       1�������ж�
                                                                       0���������ж� */
        unsigned int  reserved                    : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SOCP_DEC_CORE1NOTE_MASK2_UNION;
#endif
#define SOC_SOCP_DEC_CORE1NOTE_MASK2_core1_dtype0_obuf_ovf_mask0_START  (0)
#define SOC_SOCP_DEC_CORE1NOTE_MASK2_core1_dtype0_obuf_ovf_mask0_END    (3)
#define SOC_SOCP_DEC_CORE1NOTE_MASK2_core1_dtype1_obuf_ovf_mask1_START  (4)
#define SOC_SOCP_DEC_CORE1NOTE_MASK2_core1_dtype1_obuf_ovf_mask1_END    (7)
#define SOC_SOCP_DEC_CORE1NOTE_MASK2_core1_dtype2_obuf_ovf_mask2_START  (8)
#define SOC_SOCP_DEC_CORE1NOTE_MASK2_core1_dtype2_obuf_ovf_mask2_END    (11)
#define SOC_SOCP_DEC_CORE1NOTE_MASK2_core1_dtype3_obuf_ovf_mask3_START  (12)
#define SOC_SOCP_DEC_CORE1NOTE_MASK2_core1_dtype3_obuf_ovf_mask3_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_RAWINT2_UNION
 �ṹ˵��  : DEC_RAWINT2 �Ĵ����ṹ���塣��ַƫ����:0x0D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��Ŀ��buffer����ж�ԭʼ״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dtype0_obuf_ovf_rawint0 : 4;  /* bit[0-3]  : ����DATA-TYPE0Ŀ��buffer����ԭʼ�ж�״̬,д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                                   1�����ж�
                                                                   0�����ж� */
        unsigned int  dtype1_obuf_ovf_rawint1 : 4;  /* bit[4-7]  : ����DATA-TYPE1Ŀ��buffer����ԭʼ�ж�״̬,д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                                   1�����ж�
                                                                   0�����ж� */
        unsigned int  dtype2_obuf_ovf_rawint2 : 4;  /* bit[8-11] : ����DATA-TYPE2Ŀ��buffer����ԭʼ�ж�״̬,д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                                   1�����ж�
                                                                   0�����ж� */
        unsigned int  dtype3_obuf_ovf_rawint3 : 4;  /* bit[12-15]: ����DATA-TYPE3Ŀ��buffer����ԭʼ�ж�״̬,д1�壬ÿ��bit��Ӧһ���߼�ͨ��
                                                                   1�����ж�
                                                                   0�����ж� */
        unsigned int  reserved                : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SOCP_DEC_RAWINT2_UNION;
#endif
#define SOC_SOCP_DEC_RAWINT2_dtype0_obuf_ovf_rawint0_START  (0)
#define SOC_SOCP_DEC_RAWINT2_dtype0_obuf_ovf_rawint0_END    (3)
#define SOC_SOCP_DEC_RAWINT2_dtype1_obuf_ovf_rawint1_START  (4)
#define SOC_SOCP_DEC_RAWINT2_dtype1_obuf_ovf_rawint1_END    (7)
#define SOC_SOCP_DEC_RAWINT2_dtype2_obuf_ovf_rawint2_START  (8)
#define SOC_SOCP_DEC_RAWINT2_dtype2_obuf_ovf_rawint2_END    (11)
#define SOC_SOCP_DEC_RAWINT2_dtype3_obuf_ovf_rawint3_START  (12)
#define SOC_SOCP_DEC_RAWINT2_dtype3_obuf_ovf_rawint3_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_CORE0NOTE_NT2_UNION
 �ṹ˵��  : DEC_CORE0NOTE_NT2 �Ĵ����ṹ���塣��ַƫ����:0x0D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: CORE0����ͨ��Ŀ��buffer����ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core0_dtype0_obuf_ovf_int : 4;  /* bit[0-3]  : core0����DATA-TYPE0Ŀ��buffer�������κ��ж�״̬
                                                                     ÿ��bit��Ӧһ������ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  core0_dtype1_obuf_ovf_int : 4;  /* bit[4-7]  : core0����DATA-TYPE1Ŀ��buffer�������κ��ж�״̬
                                                                     ÿ��bit��Ӧһ������ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  core0_dtype2_obuf_ovf_int : 4;  /* bit[8-11] : core0����DATA-TYPE2Ŀ��buffer�������κ��ж�״̬
                                                                     ÿ��bit��Ӧһ������ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  core0_dtype3_obuf_ovf_int : 4;  /* bit[12-15]: core0����DATA-TYPE3Ŀ��buffer�������κ��ж�״̬
                                                                     ÿ��bit��Ӧһ������ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  reserved                  : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SOCP_DEC_CORE0NOTE_NT2_UNION;
#endif
#define SOC_SOCP_DEC_CORE0NOTE_NT2_core0_dtype0_obuf_ovf_int_START  (0)
#define SOC_SOCP_DEC_CORE0NOTE_NT2_core0_dtype0_obuf_ovf_int_END    (3)
#define SOC_SOCP_DEC_CORE0NOTE_NT2_core0_dtype1_obuf_ovf_int_START  (4)
#define SOC_SOCP_DEC_CORE0NOTE_NT2_core0_dtype1_obuf_ovf_int_END    (7)
#define SOC_SOCP_DEC_CORE0NOTE_NT2_core0_dtype2_obuf_ovf_int_START  (8)
#define SOC_SOCP_DEC_CORE0NOTE_NT2_core0_dtype2_obuf_ovf_int_END    (11)
#define SOC_SOCP_DEC_CORE0NOTE_NT2_core0_dtype3_obuf_ovf_int_START  (12)
#define SOC_SOCP_DEC_CORE0NOTE_NT2_core0_dtype3_obuf_ovf_int_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_CORE1NOTE_INT2_UNION
 �ṹ˵��  : DEC_CORE1NOTE_INT2 �Ĵ����ṹ���塣��ַƫ����:0x0D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: CORE1����ͨ��Ŀ��buffer����ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core1_dtype0_obuf_ovf_int : 4;  /* bit[0-3]  : core1����DATA-TYPE0Ŀ��buffer�������κ��ж�״̬
                                                                     ÿ��bit��Ӧһ������ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  core1_dtype1_obuf_ovf_int : 4;  /* bit[4-7]  : core1����DATA-TYPE1Ŀ��buffer�������κ��ж�״̬
                                                                     ÿ��bit��Ӧһ������ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  core1_dtype2_obuf_ovf_int : 4;  /* bit[8-11] : core1����DATA-TYPE2Ŀ��buffer�������κ��ж�״̬
                                                                     ÿ��bit��Ӧһ������ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  core1_dtype3_obuf_ovf_int : 4;  /* bit[12-15]: core1����DATA-TYPE3Ŀ��buffer�������κ��ж�״̬
                                                                     ÿ��bit��Ӧһ������ͨ��
                                                                     1�����ж�
                                                                     0�����ж� */
        unsigned int  reserved                  : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SOCP_DEC_CORE1NOTE_INT2_UNION;
#endif
#define SOC_SOCP_DEC_CORE1NOTE_INT2_core1_dtype0_obuf_ovf_int_START  (0)
#define SOC_SOCP_DEC_CORE1NOTE_INT2_core1_dtype0_obuf_ovf_int_END    (3)
#define SOC_SOCP_DEC_CORE1NOTE_INT2_core1_dtype1_obuf_ovf_int_START  (4)
#define SOC_SOCP_DEC_CORE1NOTE_INT2_core1_dtype1_obuf_ovf_int_END    (7)
#define SOC_SOCP_DEC_CORE1NOTE_INT2_core1_dtype2_obuf_ovf_int_START  (8)
#define SOC_SOCP_DEC_CORE1NOTE_INT2_core1_dtype2_obuf_ovf_int_END    (11)
#define SOC_SOCP_DEC_CORE1NOTE_INT2_core1_dtype3_obuf_ovf_int_START  (12)
#define SOC_SOCP_DEC_CORE1NOTE_INT2_core1_dtype3_obuf_ovf_int_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE1_MASK0_UNION
 �ṹ˵��  : ENC_CORE1_MASK0 �Ĵ����ṹ���塣��ַƫ����:0xDC����ֵ:0x0000007F�����:32
 �Ĵ���˵��: CORE1���봫���ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core1_enc_tfr_mask : 7;  /* bit[0-6] : core1����ͨ·�����ж����ο���λ��ÿ��bit��Ӧһ��Ŀ��buffer��Bit0��ӦĿ��buffer0�� 
                                                             1�������ж�
                                                             0���������ж� */
        unsigned int  reserved           : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_SOCP_ENC_CORE1_MASK0_UNION;
#endif
#define SOC_SOCP_ENC_CORE1_MASK0_core1_enc_tfr_mask_START  (0)
#define SOC_SOCP_ENC_CORE1_MASK0_core1_enc_tfr_mask_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE1_INT0_UNION
 �ṹ˵��  : ENC_CORE1_INT0 �Ĵ����ṹ���塣��ַƫ����:0x0E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: CORE1���봫���ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core1_enc_tfr_maskint : 7;  /* bit[0-6] : core1����ͨ·���κ����ж�״̬��ÿ��bit��Ӧһ��Ŀ��buffer��Bit0��ӦĿ��buffer0��
                                                                1�����ж�
                                                                0�����ж� */
        unsigned int  reserved              : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_SOCP_ENC_CORE1_INT0_UNION;
#endif
#define SOC_SOCP_ENC_CORE1_INT0_core1_enc_tfr_maskint_START  (0)
#define SOC_SOCP_ENC_CORE1_INT0_core1_enc_tfr_maskint_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE1_MASK2_UNION
 �ṹ˵��  : ENC_CORE1_MASK2 �Ĵ����ṹ���塣��ַƫ����:0x0E4����ֵ:0x007F007F�����:32
 �Ĵ���˵��: CORE1����Ŀ��buffer�����ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core1_enc_obuf_ovf_mask      : 7;  /* bit[0-6]  : core1����Ŀ��bufferʣ��ռ䲻��һ��dma����ʱ�����ж����ο��ƣ�ÿ��bit��Ӧһ��Ŀ��buffer
                                                                        1�������ж�
                                                                        0���������ж� */
        unsigned int  reserved_0                   : 9;  /* bit[7-15] : ������ */
        unsigned int  core1_enc_obuf_thrh_ovf_mask : 7;  /* bit[16-22]: core1����Ŀ��bufferʣ��ռ�С�����õ���ֵʱ�����ж����ο��ƣ�ÿ��bit��Ӧһ��Ŀ��buffer
                                                                        1�������ж�
                                                                        0���������ж� */
        unsigned int  reserved_1                   : 9;  /* bit[23-31]: ������ */
    } reg;
} SOC_SOCP_ENC_CORE1_MASK2_UNION;
#endif
#define SOC_SOCP_ENC_CORE1_MASK2_core1_enc_obuf_ovf_mask_START       (0)
#define SOC_SOCP_ENC_CORE1_MASK2_core1_enc_obuf_ovf_mask_END         (6)
#define SOC_SOCP_ENC_CORE1_MASK2_core1_enc_obuf_thrh_ovf_mask_START  (16)
#define SOC_SOCP_ENC_CORE1_MASK2_core1_enc_obuf_thrh_ovf_mask_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CORE1_INT2_UNION
 �ṹ˵��  : ENC_CORE1_INT2 �Ĵ����ṹ���塣��ַƫ����:0x0E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: CORE1����Ŀ��buffer�����ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  core1_enc_obuf_ovf_maskint      : 7;  /* bit[0-6]  : core1����Ŀ��bufferʣ��ռ䲻��һ��dma����ʱ�������κ��ж�״̬��ÿ��bit��Ӧһ��Ŀ��buffer
                                                                           1�����ж�
                                                                           0�����ж� */
        unsigned int  reserved_0                      : 9;  /* bit[7-15] : ������ */
        unsigned int  core1_enc_obuf_thrh_ovf_maskint : 7;  /* bit[16-22]: core1����Ŀ��bufferʣ��ռ�С�����õ���ֵʱ�������κ��ж�״̬��ÿ��bit��Ӧһ��Ŀ��buffer
                                                                           1�����ж�
                                                                           0�����ж� */
        unsigned int  reserved_1                      : 9;  /* bit[23-31]: ������ */
    } reg;
} SOC_SOCP_ENC_CORE1_INT2_UNION;
#endif
#define SOC_SOCP_ENC_CORE1_INT2_core1_enc_obuf_ovf_maskint_START       (0)
#define SOC_SOCP_ENC_CORE1_INT2_core1_enc_obuf_ovf_maskint_END         (6)
#define SOC_SOCP_ENC_CORE1_INT2_core1_enc_obuf_thrh_ovf_maskint_START  (16)
#define SOC_SOCP_ENC_CORE1_INT2_core1_enc_obuf_thrh_ovf_maskint_END    (22)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_CORE1_MASK1_UNION
 �ṹ˵��  : DEC_CORE1_MASK1 �Ĵ����ṹ���塣��ַƫ����:0x0EC����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: CORE1����ͨ���쳣�ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                    : 4;  /* bit[0-3]  : ���� */
        unsigned int  core1_dec_ibuf_underflow_mask : 4;  /* bit[4-7]  : core1����Դbuffer�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                         1�������ж�
                                                                         0���������ж� */
        unsigned int  core1_dec_flag_unmatch_mask   : 4;  /* bit[8-11] : core1�����־(0x7E)��ƥ���ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                         1�������ж�
                                                                         0���������ж� */
        unsigned int  core1_dec_dtype_unmatch_mask  : 4;  /* bit[12-15]: core1����Ŀ��bufferID��ƥ���ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                         1�������ж�
                                                                         0���������ж� */
        unsigned int  core1_dec_crc_err_mask        : 4;  /* bit[16-19]: core1����ͨ·CRC���ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                         1�������ж�
                                                                         0���������ж� */
        unsigned int  core1_dec_len_err_mask        : 4;  /* bit[20-23]: core1����ͨ·�����ȴ��ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                         1�������ж�
                                                                         0���������ж� */
        unsigned int  core1_dec_7d_err_mask         : 4;  /* bit[24-27]: core1����ͨ·7D�����ж����ο���λ��ÿ��bit��Ӧһ���߼�ͨ��
                                                                         1�������ж�
                                                                         0���������ж� */
        unsigned int  reserved_1                    : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_SOCP_DEC_CORE1_MASK1_UNION;
#endif
#define SOC_SOCP_DEC_CORE1_MASK1_core1_dec_ibuf_underflow_mask_START  (4)
#define SOC_SOCP_DEC_CORE1_MASK1_core1_dec_ibuf_underflow_mask_END    (7)
#define SOC_SOCP_DEC_CORE1_MASK1_core1_dec_flag_unmatch_mask_START    (8)
#define SOC_SOCP_DEC_CORE1_MASK1_core1_dec_flag_unmatch_mask_END      (11)
#define SOC_SOCP_DEC_CORE1_MASK1_core1_dec_dtype_unmatch_mask_START   (12)
#define SOC_SOCP_DEC_CORE1_MASK1_core1_dec_dtype_unmatch_mask_END     (15)
#define SOC_SOCP_DEC_CORE1_MASK1_core1_dec_crc_err_mask_START         (16)
#define SOC_SOCP_DEC_CORE1_MASK1_core1_dec_crc_err_mask_END           (19)
#define SOC_SOCP_DEC_CORE1_MASK1_core1_dec_len_err_mask_START         (20)
#define SOC_SOCP_DEC_CORE1_MASK1_core1_dec_len_err_mask_END           (23)
#define SOC_SOCP_DEC_CORE1_MASK1_core1_dec_7d_err_mask_START          (24)
#define SOC_SOCP_DEC_CORE1_MASK1_core1_dec_7d_err_mask_END            (27)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_CORE1_INT1_UNION
 �ṹ˵��  : DEC_CORE1_INT1 �Ĵ����ṹ���塣��ַƫ����:0x0F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: CORE1����ͨ���쳣�ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                        : 4;  /* bit[0-3]  : ���� */
        unsigned int  core1_dec_ibuf_underflow_maskint  : 4;  /* bit[4-7]  : core1����Դbuffer�����ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                             1�����ж�
                                                                             0�����ж� */
        unsigned int  core1_dec_flag_unmatch_maskint    : 4;  /* bit[8-11] : core1�����־(0x7E)��ƥ���ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                             1�����ж�
                                                                             0�����ж� */
        unsigned int  core1_dec_obuf_id_unmatch_maskint : 4;  /* bit[12-15]: core1����ID��ƥ���ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                             1�����ж�
                                                                             0�����ж� */
        unsigned int  core1_dec_crc_err_maskint         : 4;  /* bit[16-19]: core1����ͨ·CRC���ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                             1�����ж�
                                                                             0�����ж� */
        unsigned int  core1_dec_len_err_maskint         : 4;  /* bit[20-23]: core1����ͨ·�����ȴ��ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                             1�����ж�
                                                                             0�����ж� */
        unsigned int  core1_dec_7d_err_maskint          : 4;  /* bit[24-27]: core1����ͨ·7D�����ж�״̬��ÿ��bit��Ӧһ���߼�ͨ��
                                                                             1�����ж�
                                                                             0�����ж� */
        unsigned int  reserved_1                        : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_SOCP_DEC_CORE1_INT1_UNION;
#endif
#define SOC_SOCP_DEC_CORE1_INT1_core1_dec_ibuf_underflow_maskint_START   (4)
#define SOC_SOCP_DEC_CORE1_INT1_core1_dec_ibuf_underflow_maskint_END     (7)
#define SOC_SOCP_DEC_CORE1_INT1_core1_dec_flag_unmatch_maskint_START     (8)
#define SOC_SOCP_DEC_CORE1_INT1_core1_dec_flag_unmatch_maskint_END       (11)
#define SOC_SOCP_DEC_CORE1_INT1_core1_dec_obuf_id_unmatch_maskint_START  (12)
#define SOC_SOCP_DEC_CORE1_INT1_core1_dec_obuf_id_unmatch_maskint_END    (15)
#define SOC_SOCP_DEC_CORE1_INT1_core1_dec_crc_err_maskint_START          (16)
#define SOC_SOCP_DEC_CORE1_INT1_core1_dec_crc_err_maskint_END            (19)
#define SOC_SOCP_DEC_CORE1_INT1_core1_dec_len_err_maskint_START          (20)
#define SOC_SOCP_DEC_CORE1_INT1_core1_dec_len_err_maskint_END            (23)
#define SOC_SOCP_DEC_CORE1_INT1_core1_dec_7d_err_maskint_START           (24)
#define SOC_SOCP_DEC_CORE1_INT1_core1_dec_7d_err_maskint_END             (27)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_BUS_ERROR_MASK_UNION
 �ṹ˵��  : BUS_ERROR_MASK �Ĵ����ṹ���塣��ַƫ����:0x0F4����ֵ:0x000F001F�����:32
 �Ĵ���˵��: �����쳣�ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_srcch_err_mask  : 1;  /* bit[0]    : ����Դͨ�����ýӿ������쳣�ж����ο��ơ�
                                                               1 - �����жϣ�
                                                               0 - �������ж� */
        unsigned int  enc_dstch_err_mask  : 1;  /* bit[1]    : ����Ŀ��ͨ�����ýӿ������쳣�ж����ο��ơ�
                                                               1 - �����жϣ�
                                                               0 - �������ж� */
        unsigned int  dec_srcch_err_mask  : 1;  /* bit[2]    : ����Դͨ�����ýӿ������쳣�ж����ο��ơ�
                                                               1 - �����жϣ�
                                                               0 - �������ж� */
        unsigned int  dec_dstch_err_mask  : 1;  /* bit[3]    : ����Ŀ��ͨ�����ýӿ������쳣�ж����ο��ơ�
                                                               1 - �����жϣ�
                                                               0 - �������ж� */
        unsigned int  glb_reg_err_mask    : 1;  /* bit[4]    : ȫ�ּĴ������߷����쳣�ж����ο��ơ�
                                                               1 - �����жϣ�
                                                               0 - �������ж�
                                                               
                                                               ȫ�ּĴ���������0x0~0x24 */
        unsigned int  reserved_0          : 11; /* bit[5-15] : ������ */
        unsigned int  enc_mst_wr_err_mask : 1;  /* bit[16]   : ����ͨ��Master�ӿ�д�����쳣�ж����ο��ơ�
                                                               1 - �����жϣ�
                                                               0 - �������ж� */
        unsigned int  enc_mst_rd_err_mask : 1;  /* bit[17]   : ����ͨ��Master�ӿڶ������쳣�ж����ο��ơ�
                                                               1 - �����жϣ�
                                                               0 - �������ж� */
        unsigned int  dec_mst_wr_err_mask : 1;  /* bit[18]   : ����ͨ��Master�ӿ�д�����쳣�ж����ο��ơ�
                                                               1 - �����жϣ�
                                                               0 - �������ж� */
        unsigned int  dec_mst_rd_err_mask : 1;  /* bit[19]   : ����ͨ��Master�ӿڶ������쳣�ж����ο��ơ�
                                                               1 - �����жϣ�
                                                               0 - �������ж� */
        unsigned int  reserved_1          : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_SOCP_BUS_ERROR_MASK_UNION;
#endif
#define SOC_SOCP_BUS_ERROR_MASK_enc_srcch_err_mask_START   (0)
#define SOC_SOCP_BUS_ERROR_MASK_enc_srcch_err_mask_END     (0)
#define SOC_SOCP_BUS_ERROR_MASK_enc_dstch_err_mask_START   (1)
#define SOC_SOCP_BUS_ERROR_MASK_enc_dstch_err_mask_END     (1)
#define SOC_SOCP_BUS_ERROR_MASK_dec_srcch_err_mask_START   (2)
#define SOC_SOCP_BUS_ERROR_MASK_dec_srcch_err_mask_END     (2)
#define SOC_SOCP_BUS_ERROR_MASK_dec_dstch_err_mask_START   (3)
#define SOC_SOCP_BUS_ERROR_MASK_dec_dstch_err_mask_END     (3)
#define SOC_SOCP_BUS_ERROR_MASK_glb_reg_err_mask_START     (4)
#define SOC_SOCP_BUS_ERROR_MASK_glb_reg_err_mask_END       (4)
#define SOC_SOCP_BUS_ERROR_MASK_enc_mst_wr_err_mask_START  (16)
#define SOC_SOCP_BUS_ERROR_MASK_enc_mst_wr_err_mask_END    (16)
#define SOC_SOCP_BUS_ERROR_MASK_enc_mst_rd_err_mask_START  (17)
#define SOC_SOCP_BUS_ERROR_MASK_enc_mst_rd_err_mask_END    (17)
#define SOC_SOCP_BUS_ERROR_MASK_dec_mst_wr_err_mask_START  (18)
#define SOC_SOCP_BUS_ERROR_MASK_dec_mst_wr_err_mask_END    (18)
#define SOC_SOCP_BUS_ERROR_MASK_dec_mst_rd_err_mask_START  (19)
#define SOC_SOCP_BUS_ERROR_MASK_dec_mst_rd_err_mask_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_BUS_ERROR_RAWINT_UNION
 �ṹ˵��  : BUS_ERROR_RAWINT �Ĵ����ṹ���塣��ַƫ����:0x0F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����쳣ԭʼ�ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_srcch_err_rawint  : 1;  /* bit[0]    : ����Դͨ�����ýӿ������쳣�쳣ԭʼ�ж�״ָ̬ʾ��
                                                                 1 - �ж���Ч��
                                                                 0 - �ж���Ч��
                                                                 
                                                                 ���ж�д1��0�� */
        unsigned int  enc_dstch_err_rawint  : 1;  /* bit[1]    : ����Ŀ��ͨ�����ýӿ������쳣�쳣ԭʼ�ж�״ָ̬ʾ��
                                                                 1 - �ж���Ч��
                                                                 0 - �ж���Ч��
                                                                 
                                                                 ���ж�д1��0�� */
        unsigned int  dec_srcch_err_rawint  : 1;  /* bit[2]    : ����Դͨ�����ýӿ������쳣�쳣ԭʼ�ж�״ָ̬ʾ��
                                                                 1 - �ж���Ч��
                                                                 0 - �ж���Ч��
                                                                 
                                                                 ���ж�д1��0�� */
        unsigned int  dec_dstch_err_rawint  : 1;  /* bit[3]    : ����Ŀ��ͨ�����ýӿ������쳣�ж����ο��ơ�
                                                                 1 - �����жϣ�
                                                                 0 - �������ж� */
        unsigned int  glb_reg_err_rawint    : 1;  /* bit[4]    : ȫ�ּĴ������߷����쳣�쳣ԭʼ�ж�״ָ̬ʾ��
                                                                 1 - �ж���Ч��
                                                                 0 - �ж���Ч��
                                                                 
                                                                 ���ж�д1��0��
                                                                 ȫ�ּĴ���������0x0~0x24 */
        unsigned int  reserved_0            : 11; /* bit[5-15] : ������ */
        unsigned int  enc_mst_wr_err_rawint : 1;  /* bit[16]   : ����ͨ��Master�ӿ�д�����쳣�쳣ԭʼ�ж�״ָ̬ʾ��
                                                                 1 - �ж���Ч��
                                                                 0 - �ж���Ч��
                                                                 
                                                                 ���ж�д1��0�� */
        unsigned int  enc_mst_rd_err_rawint : 1;  /* bit[17]   : ����ͨ��Master�ӿڶ������쳣�쳣ԭʼ�ж�״ָ̬ʾ��
                                                                 1 - �ж���Ч��
                                                                 0 - �ж���Ч��
                                                                 
                                                                 ���ж�д1��0�� */
        unsigned int  dec_mst_wr_err_rawint : 1;  /* bit[18]   : ����ͨ��Master�ӿ�д�����쳣�쳣ԭʼ�ж�״ָ̬ʾ��
                                                                 1 - �ж���Ч��
                                                                 0 - �ж���Ч��
                                                                 
                                                                 ���ж�д1��0�� */
        unsigned int  dec_mst_rd_err_rawint : 1;  /* bit[19]   : ����ͨ��Master�ӿڶ������쳣ԭʼ�ж�״ָ̬ʾ��
                                                                 1 - �ж���Ч��
                                                                 0 - �ж���Ч��
                                                                 
                                                                 ���ж�д1��0�� */
        unsigned int  reserved_1            : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_SOCP_BUS_ERROR_RAWINT_UNION;
#endif
#define SOC_SOCP_BUS_ERROR_RAWINT_enc_srcch_err_rawint_START   (0)
#define SOC_SOCP_BUS_ERROR_RAWINT_enc_srcch_err_rawint_END     (0)
#define SOC_SOCP_BUS_ERROR_RAWINT_enc_dstch_err_rawint_START   (1)
#define SOC_SOCP_BUS_ERROR_RAWINT_enc_dstch_err_rawint_END     (1)
#define SOC_SOCP_BUS_ERROR_RAWINT_dec_srcch_err_rawint_START   (2)
#define SOC_SOCP_BUS_ERROR_RAWINT_dec_srcch_err_rawint_END     (2)
#define SOC_SOCP_BUS_ERROR_RAWINT_dec_dstch_err_rawint_START   (3)
#define SOC_SOCP_BUS_ERROR_RAWINT_dec_dstch_err_rawint_END     (3)
#define SOC_SOCP_BUS_ERROR_RAWINT_glb_reg_err_rawint_START     (4)
#define SOC_SOCP_BUS_ERROR_RAWINT_glb_reg_err_rawint_END       (4)
#define SOC_SOCP_BUS_ERROR_RAWINT_enc_mst_wr_err_rawint_START  (16)
#define SOC_SOCP_BUS_ERROR_RAWINT_enc_mst_wr_err_rawint_END    (16)
#define SOC_SOCP_BUS_ERROR_RAWINT_enc_mst_rd_err_rawint_START  (17)
#define SOC_SOCP_BUS_ERROR_RAWINT_enc_mst_rd_err_rawint_END    (17)
#define SOC_SOCP_BUS_ERROR_RAWINT_dec_mst_wr_err_rawint_START  (18)
#define SOC_SOCP_BUS_ERROR_RAWINT_dec_mst_wr_err_rawint_END    (18)
#define SOC_SOCP_BUS_ERROR_RAWINT_dec_mst_rd_err_rawint_START  (19)
#define SOC_SOCP_BUS_ERROR_RAWINT_dec_mst_rd_err_rawint_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_BUS_ERROR_INT_UNION
 �ṹ˵��  : BUS_ERROR_INT �Ĵ����ṹ���塣��ַƫ����:0x0FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����쳣���κ��жϼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_srcch_err_int  : 1;  /* bit[0]    : ����Դͨ�����ýӿ������쳣���κ��ж�״ָ̬ʾ��
                                                              1 - �ж���Ч��
                                                              0 - �ж���Ч�� */
        unsigned int  enc_dstch_err_int  : 1;  /* bit[1]    : ����Ŀ��ͨ�����ýӿ������쳣���κ��ж�״ָ̬ʾ��
                                                              1 - �ж���Ч��
                                                              0 - �ж���Ч�� */
        unsigned int  dec_srcch_err_int  : 1;  /* bit[2]    : ����Դͨ�����ýӿ������쳣���κ��ж�״ָ̬ʾ��
                                                              1 - �ж���Ч��
                                                              0 - �ж���Ч�� */
        unsigned int  dec_dstch_err_int  : 1;  /* bit[3]    : ����Ŀ��ͨ�����ýӿ������쳣���κ��ж�״ָ̬ʾ��
                                                              1 - �ж���Ч��
                                                              0 - �ж���Ч�� */
        unsigned int  glb_reg_err_int    : 1;  /* bit[4]    : ȫ�ּĴ������߷����쳣���κ��ж�״ָ̬ʾ��
                                                              1 - �ж���Ч��
                                                              0 - �ж���Ч��
                                                              
                                                              ȫ�ּĴ���������0x0~0x24 */
        unsigned int  reserved_0         : 11; /* bit[5-15] : ������ */
        unsigned int  enc_mst_wr_err_int : 1;  /* bit[16]   : ����ͨ��Master�ӿ�д�����쳣���κ��ж�״ָ̬ʾ��
                                                              1 - �ж���Ч��
                                                              0 - �ж���Ч�� */
        unsigned int  enc_mst_rd_err_int : 1;  /* bit[17]   : ����ͨ��Master�ӿڶ������쳣���κ��ж�״ָ̬ʾ��
                                                              1 - �ж���Ч��
                                                              0 - �ж���Ч�� */
        unsigned int  dec_mst_wr_err_int : 1;  /* bit[18]   : ����ͨ��Master�ӿ�д�����쳣���κ��ж�״ָ̬ʾ��
                                                              1 - �ж���Ч��
                                                              0 - �ж���Ч�� */
        unsigned int  dec_mst_rd_err_int : 1;  /* bit[19]   : ����ͨ��Master�ӿڶ������쳣���κ��ж�״ָ̬ʾ��
                                                              1 - �ж���Ч��
                                                              0 - �ж���Ч�� */
        unsigned int  reserved_1         : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_SOCP_BUS_ERROR_INT_UNION;
#endif
#define SOC_SOCP_BUS_ERROR_INT_enc_srcch_err_int_START   (0)
#define SOC_SOCP_BUS_ERROR_INT_enc_srcch_err_int_END     (0)
#define SOC_SOCP_BUS_ERROR_INT_enc_dstch_err_int_START   (1)
#define SOC_SOCP_BUS_ERROR_INT_enc_dstch_err_int_END     (1)
#define SOC_SOCP_BUS_ERROR_INT_dec_srcch_err_int_START   (2)
#define SOC_SOCP_BUS_ERROR_INT_dec_srcch_err_int_END     (2)
#define SOC_SOCP_BUS_ERROR_INT_dec_dstch_err_int_START   (3)
#define SOC_SOCP_BUS_ERROR_INT_dec_dstch_err_int_END     (3)
#define SOC_SOCP_BUS_ERROR_INT_glb_reg_err_int_START     (4)
#define SOC_SOCP_BUS_ERROR_INT_glb_reg_err_int_END       (4)
#define SOC_SOCP_BUS_ERROR_INT_enc_mst_wr_err_int_START  (16)
#define SOC_SOCP_BUS_ERROR_INT_enc_mst_wr_err_int_END    (16)
#define SOC_SOCP_BUS_ERROR_INT_enc_mst_rd_err_int_START  (17)
#define SOC_SOCP_BUS_ERROR_INT_enc_mst_rd_err_int_END    (17)
#define SOC_SOCP_BUS_ERROR_INT_dec_mst_wr_err_int_START  (18)
#define SOC_SOCP_BUS_ERROR_INT_dec_mst_wr_err_int_END    (18)
#define SOC_SOCP_BUS_ERROR_INT_dec_mst_rd_err_int_START  (19)
#define SOC_SOCP_BUS_ERROR_INT_dec_mst_rd_err_int_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_SRC_BUFM_WPTR_UNION
 �ṹ˵��  : ENC_SRC_BUFM_WPTR �Ĵ����ṹ���塣��ַƫ����:0x100+0x40*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Դbuffermдָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_src_bufm_wptr : 32; /* bit[0-31]: ����ͨ��Դbuffermдָ�룬���Ե�ַ�����ֽ�Ϊ��λ */
    } reg;
} SOC_SOCP_ENC_SRC_BUFM_WPTR_UNION;
#endif
#define SOC_SOCP_ENC_SRC_BUFM_WPTR_enc_src_bufm_wptr_START  (0)
#define SOC_SOCP_ENC_SRC_BUFM_WPTR_enc_src_bufm_wptr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_SRC_BUFM_RPTR_UNION
 �ṹ˵��  : ENC_SRC_BUFM_RPTR �Ĵ����ṹ���塣��ַƫ����:0x104+0x40*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Դbufferm��ָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_src_bufm_rptr : 32; /* bit[0-31]: ����ͨ��Դbufferm��ָ�룬���Ե�ַ�����ֽ�Ϊ��λ */
    } reg;
} SOC_SOCP_ENC_SRC_BUFM_RPTR_UNION;
#endif
#define SOC_SOCP_ENC_SRC_BUFM_RPTR_enc_src_bufm_rptr_START  (0)
#define SOC_SOCP_ENC_SRC_BUFM_RPTR_enc_src_bufm_rptr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_SRC_BUFM_ADDR_UNION
 �ṹ˵��  : ENC_SRC_BUFM_ADDR �Ĵ����ṹ���塣��ַƫ����:0x108+0x40*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Դbufferm��ʼ��ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_src_bufm_addr : 32; /* bit[0-31]: fs */
    } reg;
} SOC_SOCP_ENC_SRC_BUFM_ADDR_UNION;
#endif
#define SOC_SOCP_ENC_SRC_BUFM_ADDR_enc_src_bufm_addr_START  (0)
#define SOC_SOCP_ENC_SRC_BUFM_ADDR_enc_src_bufm_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_SRC_BUFM_DEPTH_UNION
 �ṹ˵��  : ENC_SRC_BUFM_DEPTH �Ĵ����ṹ���塣��ַƫ����:0x10C+0x40*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Դbufferm��ȼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_src_bufm_size : 32; /* bit[0-31]: ����ͨ·Դbufferm buffer��С�����ֽ�Ϊ��λ
                                                            BBP����ͨ·buffer�ռ�Ϊ20.2MB���ϡ�
                                                            ע�⣬SOCP������Ѱַλ��Ϊ32bits��ʵ��ʹ��ʱ��ȷ��bufferĩβ��ַ����buffer��ʼ��ַ��buffer��ȣ���32bits��ַ��Χ�ڡ� */
    } reg;
} SOC_SOCP_ENC_SRC_BUFM_DEPTH_UNION;
#endif
#define SOC_SOCP_ENC_SRC_BUFM_DEPTH_enc_src_bufm_size_START  (0)
#define SOC_SOCP_ENC_SRC_BUFM_DEPTH_enc_src_bufm_size_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_SRC_BUFM_CFG_UNION
 �ṹ˵��  : ENC_SRC_BUFM_CFG �Ĵ����ṹ���塣��ַƫ����:0x110+0x40*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Դbufferm���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_chm_en          : 1;  /* bit[0]    : ͨ��ʹ�ܿ��ơ�
                                                               1�� ͨ��ʹ�ܣ�
                                                               0 ��ͨ����ʹ�� */
        unsigned int  enc_chm_mode        : 2;  /* bit[1-2]  : Դbuffer���ݽṹ��
                                                               1������ṹ��
                                                               01������ͨ·�̶��������ݰ��ṹ
                                                               00�������洢���ݰ��ṹ */
        unsigned int  reserved_0          : 1;  /* bit[3]    : ������ */
        unsigned int  enc_chm_dest_buf_id : 4;  /* bit[4-7]  : Ŀ��bufferID��
                                                               Ŀǰ֧��7��Ŀ��buffer�����÷�Χ0~6�� */
        unsigned int  enc_chm_prior_id    : 2;  /* bit[8-9]  : �ߵ����ȼ��������á�
                                                               11��������ȼ����У�
                                                               10���θ����ȼ����У�
                                                               01���ε����ȼ����У� 
                                                               00��������ȼ����С� */
        unsigned int  bypass_en           : 1;  /* bit[10]   : ����ͨ·bypassʹ���ź�
                                                               1��ͨ��bypassʹ��
                                                               0��ͨ��bypass��ʹ�� */
        unsigned int  no_data_type        : 1;  /* bit[11]   : ����ͨ·data_type�ֶ�����
                                                               1�����䲻����data_type�ֶ�
                                                               0���������data_type�ֶ� */
        unsigned int  reserved_1          : 4;  /* bit[12-15]: ���� */
        unsigned int  data_type           : 8;  /* bit[16-23]: ��ģ����ָʾ��Ŀǰʹ��3��ģ����0��ʾLTEģ��TDSģ����1��ʾGUģ�� */
        unsigned int  reserved_2          : 7;  /* bit[24-30]: ���� */
        unsigned int  enc_debug           : 1;  /* bit[31]   : ��debugģʽ��Чʱ�������֡�HISI����ͷУ��������ٸ���Դbuffer�Ķ�ָ�룬����������á�ע�⣺�������ʱ���������ΰ�ͷ���жϺ�Ҫ����жϣ���������ͨ���㲻�ٲ����ٲã������ٴ��ٲõ�����ͨ��ʱ������ϱ���ͷ�����жϡ�
                                                               �踴λ��ͨ������ʹ�á�
                                                               1��debug ģʽ
                                                               0������ģʽ */
    } reg;
} SOC_SOCP_ENC_SRC_BUFM_CFG_UNION;
#endif
#define SOC_SOCP_ENC_SRC_BUFM_CFG_enc_chm_en_START           (0)
#define SOC_SOCP_ENC_SRC_BUFM_CFG_enc_chm_en_END             (0)
#define SOC_SOCP_ENC_SRC_BUFM_CFG_enc_chm_mode_START         (1)
#define SOC_SOCP_ENC_SRC_BUFM_CFG_enc_chm_mode_END           (2)
#define SOC_SOCP_ENC_SRC_BUFM_CFG_enc_chm_dest_buf_id_START  (4)
#define SOC_SOCP_ENC_SRC_BUFM_CFG_enc_chm_dest_buf_id_END    (7)
#define SOC_SOCP_ENC_SRC_BUFM_CFG_enc_chm_prior_id_START     (8)
#define SOC_SOCP_ENC_SRC_BUFM_CFG_enc_chm_prior_id_END       (9)
#define SOC_SOCP_ENC_SRC_BUFM_CFG_bypass_en_START            (10)
#define SOC_SOCP_ENC_SRC_BUFM_CFG_bypass_en_END              (10)
#define SOC_SOCP_ENC_SRC_BUFM_CFG_no_data_type_START         (11)
#define SOC_SOCP_ENC_SRC_BUFM_CFG_no_data_type_END           (11)
#define SOC_SOCP_ENC_SRC_BUFM_CFG_data_type_START            (16)
#define SOC_SOCP_ENC_SRC_BUFM_CFG_data_type_END              (23)
#define SOC_SOCP_ENC_SRC_BUFM_CFG_enc_debug_START            (31)
#define SOC_SOCP_ENC_SRC_BUFM_CFG_enc_debug_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_SRC_RDQ_WPTR_UNION
 �ṹ˵��  : ENC_SRC_RDQ_WPTR �Ĵ����ṹ���塣��ַƫ����:0x114+0x40*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·RD����bufferдָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_bufm_rdq_wptr : 32; /* bit[0-31]: ����ͨ·Rd����bufferдָ�룬���Ե�ַ�����ֽ�Ϊ��λ */
    } reg;
} SOC_SOCP_ENC_SRC_RDQ_WPTR_UNION;
#endif
#define SOC_SOCP_ENC_SRC_RDQ_WPTR_enc_bufm_rdq_wptr_START  (0)
#define SOC_SOCP_ENC_SRC_RDQ_WPTR_enc_bufm_rdq_wptr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_SRC_RDQ_RPTR_UNION
 �ṹ˵��  : ENC_SRC_RDQ_RPTR �Ĵ����ṹ���塣��ַƫ����:0x118+0x40*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·RD����bufferдָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_bufm_rdq_rptr : 32; /* bit[0-31]: ����ͨ·Rd����buffer��ָ�룬���Ե�ַ�����ֽ�Ϊ��λ */
    } reg;
} SOC_SOCP_ENC_SRC_RDQ_RPTR_UNION;
#endif
#define SOC_SOCP_ENC_SRC_RDQ_RPTR_enc_bufm_rdq_rptr_START  (0)
#define SOC_SOCP_ENC_SRC_RDQ_RPTR_enc_bufm_rdq_rptr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_SRC_RDQ_BADDR_UNION
 �ṹ˵��  : ENC_SRC_RDQ_BADDR �Ĵ����ṹ���塣��ַƫ����:0x11C+0x40*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·RD����buffer��ʼ��ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_bufm_rdq_baddr : 32; /* bit[0-31]: ����ͨ·Rd����buffer��ʼ��ַ��8�ֽڶ��� */
    } reg;
} SOC_SOCP_ENC_SRC_RDQ_BADDR_UNION;
#endif
#define SOC_SOCP_ENC_SRC_RDQ_BADDR_enc_bufm_rdq_baddr_START  (0)
#define SOC_SOCP_ENC_SRC_RDQ_BADDR_enc_bufm_rdq_baddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_SRC_RDQ_CFG_UNION
 �ṹ˵��  : ENC_SRC_RDQ_CFG �Ĵ����ṹ���塣��ַƫ����:0x120+0x40*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·RD����buffer���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_bufm_rdq_size : 16; /* bit[0-15] : Rd����buffer��С�����ֽ�Ϊ��λ */
        unsigned int  reserved          : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SOCP_ENC_SRC_RDQ_CFG_UNION;
#endif
#define SOC_SOCP_ENC_SRC_RDQ_CFG_enc_bufm_rdq_size_START  (0)
#define SOC_SOCP_ENC_SRC_RDQ_CFG_enc_bufm_rdq_size_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_DEST_BUFN_WPTR_UNION
 �ṹ˵��  : ENC_DEST_BUFN_WPTR �Ĵ����ṹ���塣��ַƫ����:0x900+0x20*(n)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Ŀ��bufferдָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_dest_bufn_wptr : 32; /* bit[0-31]: ����ͨ·Ŀ��buffernдָ�룬���Ե�ַ�����ֽ�Ϊ��λ */
    } reg;
} SOC_SOCP_ENC_DEST_BUFN_WPTR_UNION;
#endif
#define SOC_SOCP_ENC_DEST_BUFN_WPTR_enc_dest_bufn_wptr_START  (0)
#define SOC_SOCP_ENC_DEST_BUFN_WPTR_enc_dest_bufn_wptr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_DEST_BUFN_RPTR_UNION
 �ṹ˵��  : ENC_DEST_BUFN_RPTR �Ĵ����ṹ���塣��ַƫ����:0x904+0x20*(n)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Ŀ��buffer��ָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_dest_bufn_rptr : 32; /* bit[0-31]: ����ͨ·Ŀ��buffern��ָ�룬���Ե�ַ�����ֽ�Ϊ��λ */
    } reg;
} SOC_SOCP_ENC_DEST_BUFN_RPTR_UNION;
#endif
#define SOC_SOCP_ENC_DEST_BUFN_RPTR_enc_dest_bufn_rptr_START  (0)
#define SOC_SOCP_ENC_DEST_BUFN_RPTR_enc_dest_bufn_rptr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_DEST_BUFN_ADDR_UNION
 �ṹ˵��  : ENC_DEST_BUFN_ADDR �Ĵ����ṹ���塣��ַƫ����:0x908+0x20*(n)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Ŀ��buffer��ʼ��ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_dest_bufn_addr : 32; /* bit[0-31]: ����ͨ·Ŀ��buffern��ʼ��ַ��8�ֽڶ��� */
    } reg;
} SOC_SOCP_ENC_DEST_BUFN_ADDR_UNION;
#endif
#define SOC_SOCP_ENC_DEST_BUFN_ADDR_enc_dest_bufn_addr_START  (0)
#define SOC_SOCP_ENC_DEST_BUFN_ADDR_enc_dest_bufn_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_DEST_BUFN_DEPTH_UNION
 �ṹ˵��  : ENC_DEST_BUFN_DEPTH �Ĵ����ṹ���塣��ַƫ����:0x90C+0x20*(n)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Ŀ��buffer��ȼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_dest_bufn_size : 32; /* bit[0-31]: ����ͨ·Ŀ��buffern��С�����ֽ�Ϊ��λ
                                                             ֧��buffer�ռ����Ϊ4G�ֽڡ�
                                                             ע�⣬SOCP������Ѱַλ��Ϊ32bits��ʵ��ʹ��ʱ��ȷ��bufferĩβ��ַ����buffer��ʼ��ַ��buffer��ȣ���32bits��ַ��Χ�ڡ� */
    } reg;
} SOC_SOCP_ENC_DEST_BUFN_DEPTH_UNION;
#endif
#define SOC_SOCP_ENC_DEST_BUFN_DEPTH_enc_dest_bufn_size_START  (0)
#define SOC_SOCP_ENC_DEST_BUFN_DEPTH_enc_dest_bufn_size_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_DEST_BUFN_THRH_UNION
 �ṹ˵��  : ENC_DEST_BUFN_THRH �Ĵ����ṹ���塣��ַƫ����:0x910+0x20*(n)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Ŀ��buffer����ж���ֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_dest_bufn_thrh : 32; /* bit[0-31]: ����Ŀ��buffer�����ֵ���á���ʣ��ռ���ڴ���ֵ����Ŀ��buffer��Ӧ�ı���ͨ�������ٲã����򲻲����ٲã���������ֵ����жϡ� */
    } reg;
} SOC_SOCP_ENC_DEST_BUFN_THRH_UNION;
#endif
#define SOC_SOCP_ENC_DEST_BUFN_THRH_enc_dest_bufn_thrh_START  (0)
#define SOC_SOCP_ENC_DEST_BUFN_THRH_enc_dest_bufn_thrh_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_INT_THRESHOLD_UNION
 �ṹ˵��  : ENC_INT_THRESHOLD �Ĵ����ṹ���塣��ַƫ����:0x914+0x20*(n)����ֵ:0x0000�����:32
 �Ĵ���˵��: ����ͨ·�����ж���ֵ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  enc_int_threshold : 32; /* bit[0-31]: ����ͨ·�����ж��ϱ���ֵ���ޣ����ֽ�Ϊ��λ */
    } reg;
} SOC_SOCP_ENC_INT_THRESHOLD_UNION;
#endif
#define SOC_SOCP_ENC_INT_THRESHOLD_enc_int_threshold_START  (0)
#define SOC_SOCP_ENC_INT_THRESHOLD_enc_int_threshold_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_SRC_BUFX_WPTR_UNION
 �ṹ˵��  : DEC_SRC_BUFX_WPTR �Ĵ����ṹ���塣��ַƫ����:0(x)A00+0(x)40*(x)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Դbufferxдָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_src_bufx_wptr : 32; /* bit[0-31]: ����ͨ·Դbufferxдָ�룬���ֽ�Ϊ��λ.
                                                            Ŀǰ֧��4������ͨ· */
    } reg;
} SOC_SOCP_DEC_SRC_BUFX_WPTR_UNION;
#endif
#define SOC_SOCP_DEC_SRC_BUFX_WPTR_dec_src_bufx_wptr_START  (0)
#define SOC_SOCP_DEC_SRC_BUFX_WPTR_dec_src_bufx_wptr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_SRC_BUFX_RPTR_UNION
 �ṹ˵��  : DEC_SRC_BUFX_RPTR �Ĵ����ṹ���塣��ַƫ����:0(x)A04+0(x)40*(x)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Դbufferx��ָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_src_bufx_rptr : 32; /* bit[0-31]: ����ͨ·Դbufferx��ָ�룬���ֽ�Ϊ��λ.
                                                            Ŀǰ֧��4������ͨ· */
    } reg;
} SOC_SOCP_DEC_SRC_BUFX_RPTR_UNION;
#endif
#define SOC_SOCP_DEC_SRC_BUFX_RPTR_dec_src_bufx_rptr_START  (0)
#define SOC_SOCP_DEC_SRC_BUFX_RPTR_dec_src_bufx_rptr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_SRC_BUFX_ADDR_UNION
 �ṹ˵��  : DEC_SRC_BUFX_ADDR �Ĵ����ṹ���塣��ַƫ����:0(x)A08+0(x)40*(x)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Դbufferx��ʼ��ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_src_bufx_addr : 32; /* bit[0-31]: ����ͨ·Դbuffer��ʼ��ַ��
                                                            8�ֽڶ��� */
    } reg;
} SOC_SOCP_DEC_SRC_BUFX_ADDR_UNION;
#endif
#define SOC_SOCP_DEC_SRC_BUFX_ADDR_dec_src_bufx_addr_START  (0)
#define SOC_SOCP_DEC_SRC_BUFX_ADDR_dec_src_bufx_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_SRC_BUFX_CFG0_UNION
 �ṹ˵��  : DEC_SRC_BUFX_CFG0 �Ĵ����ṹ���塣��ַƫ����:0(x)A0C+0(x)40*(x)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Դbufferx���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_src_bufx_size : 16; /* bit[0-15] : ����ͨ·Դbuffer��С�����ֽ�Ϊ��λ�� */
        unsigned int  reserved_0        : 10; /* bit[16-25]: ���� */
        unsigned int  no_data_type_sel  : 2;  /* bit[26-27]: ����Դ���ݲ���data-type�ֶ�ʱ��Ӧ��Ŀ��buffer����
                                                             11����������ݴ���data-typeΪ3������ģ����Ŀ��buffer��
                                                             10����������ݴ���data-typeΪ2������ģ����Ŀ��buffer��
                                                             01����������ݴ���data-typeΪ1��GUģ����Ŀ��buffer��
                                                             00����������ݴ���data-typeΪ0��LTEģ��TDSģ����Ŀ��buffer�� */
        unsigned int  reserved_1        : 1;  /* bit[28]   : ���� */
        unsigned int  dec_debug         : 1;  /* bit[29]   : debug�������á�
                                                             1������ʹ�ܡ���ͨ���쳣���ϱ��쳣�жϣ���ֹͣ�����ͨ����ֱ���쳣�ָ����߸�λ��
                                                             0�����Բ�ʹ�ܡ�ͨ���쳣ʱ���ϱ��쳣�жϣ����������ͨ���� */
        unsigned int  dec_chx_en        : 1;  /* bit[30]   : ͨ��ʹ�����á�
                                                             1��ʹ�ܣ�
                                                             0����ʹ�� */
        unsigned int  no_data_type      : 1;  /* bit[31]   : ����ͨ·data_type�ֶ�����
                                                             1���������ݲ�����data_type�ֶ�
                                                             0���������ݴ���data_type�ֶ�
                                                             ע�����������ݲ�����data_type�ֶΣ��򽫽�������ݷ���no_data_type_sel���ö�Ӧ��Ŀ��buffer */
    } reg;
} SOC_SOCP_DEC_SRC_BUFX_CFG0_UNION;
#endif
#define SOC_SOCP_DEC_SRC_BUFX_CFG0_dec_src_bufx_size_START  (0)
#define SOC_SOCP_DEC_SRC_BUFX_CFG0_dec_src_bufx_size_END    (15)
#define SOC_SOCP_DEC_SRC_BUFX_CFG0_no_data_type_sel_START   (26)
#define SOC_SOCP_DEC_SRC_BUFX_CFG0_no_data_type_sel_END     (27)
#define SOC_SOCP_DEC_SRC_BUFX_CFG0_dec_debug_START          (29)
#define SOC_SOCP_DEC_SRC_BUFX_CFG0_dec_debug_END            (29)
#define SOC_SOCP_DEC_SRC_BUFX_CFG0_dec_chx_en_START         (30)
#define SOC_SOCP_DEC_SRC_BUFX_CFG0_dec_chx_en_END           (30)
#define SOC_SOCP_DEC_SRC_BUFX_CFG0_no_data_type_START       (31)
#define SOC_SOCP_DEC_SRC_BUFX_CFG0_no_data_type_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_BUFX_STATUS0_UNION
 �ṹ˵��  : DEC_BUFX_STATUS0 �Ĵ����ṹ���塣��ַƫ����:0(x)A20+0(x)40*(x)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·״̬�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_crc_err_cnt : 16; /* bit[0-15] : ����ͨ·x CRC�����ݰ����� */
        unsigned int  dec_len_err_cnt : 16; /* bit[16-31]: ����ͨ·�����ȴ����ݰ�������
                                                           �����İ���>��������<��С����
                                                           ���������������ֽ�δ���ְ�ͷ7E�� */
    } reg;
} SOC_SOCP_DEC_BUFX_STATUS0_UNION;
#endif
#define SOC_SOCP_DEC_BUFX_STATUS0_dec_crc_err_cnt_START  (0)
#define SOC_SOCP_DEC_BUFX_STATUS0_dec_crc_err_cnt_END    (15)
#define SOC_SOCP_DEC_BUFX_STATUS0_dec_len_err_cnt_START  (16)
#define SOC_SOCP_DEC_BUFX_STATUS0_dec_len_err_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_BUFX_STATUS1_UNION
 �ṹ˵��  : DEC_BUFX_STATUS1 �Ĵ����ṹ���塣��ַƫ����:0(x)A24+0(x)40*(x)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·״̬�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_start_err_cnt : 16; /* bit[0-15] : �����쳣��������һ����β7E�͵�ǰ����ͷ7E��ƥ�䣩 */
        unsigned int  data_type_err_cnt : 16; /* bit[16-31]: data_type ����ͳ�Ƽ��� */
    } reg;
} SOC_SOCP_DEC_BUFX_STATUS1_UNION;
#endif
#define SOC_SOCP_DEC_BUFX_STATUS1_dec_start_err_cnt_START  (0)
#define SOC_SOCP_DEC_BUFX_STATUS1_dec_start_err_cnt_END    (15)
#define SOC_SOCP_DEC_BUFX_STATUS1_data_type_err_cnt_START  (16)
#define SOC_SOCP_DEC_BUFX_STATUS1_data_type_err_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_DEST_BUFY_WPTR_UNION
 �ṹ˵��  : DEC_DEST_BUFY_WPTR �Ĵ����ṹ���塣��ַƫ����:0xC00+0x10*(y)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Ŀ��bufferyдָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_dest_bufy_wptr : 32; /* bit[0-31]: ����ͨ·Ŀ��bufferyдָ�룬���Ե�ַ�����ֽ�Ϊ��λ.
                                                             Ŀǰ֧��4*4������ͨ· */
    } reg;
} SOC_SOCP_DEC_DEST_BUFY_WPTR_UNION;
#endif
#define SOC_SOCP_DEC_DEST_BUFY_WPTR_dec_dest_bufy_wptr_START  (0)
#define SOC_SOCP_DEC_DEST_BUFY_WPTR_dec_dest_bufy_wptr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_DEST_BUFY_RPTR_UNION
 �ṹ˵��  : DEC_DEST_BUFY_RPTR �Ĵ����ṹ���塣��ַƫ����:0xC04+0x10*(y)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Ŀ��buffery��ָ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_dest_bufy_rptr : 32; /* bit[0-31]: ����ͨ·Ŀ��buffery��ָ�룬���Ե�ַ�����ֽ�Ϊ��λ.
                                                             Ŀǰ֧��4*4������ͨ· */
    } reg;
} SOC_SOCP_DEC_DEST_BUFY_RPTR_UNION;
#endif
#define SOC_SOCP_DEC_DEST_BUFY_RPTR_dec_dest_bufy_rptr_START  (0)
#define SOC_SOCP_DEC_DEST_BUFY_RPTR_dec_dest_bufy_rptr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_DEST_BUFY_ADDR_UNION
 �ṹ˵��  : DEC_DEST_BUFY_ADDR �Ĵ����ṹ���塣��ַƫ����:0xC08+0x10*(y)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·Ŀ��buffery��ʼ��ַ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_dest_bufy_addr : 32; /* bit[0-31]: ����ͨ·Ŀ��buffery��ʼ��ַ��8�ֽڶ��� */
    } reg;
} SOC_SOCP_DEC_DEST_BUFY_ADDR_UNION;
#endif
#define SOC_SOCP_DEC_DEST_BUFY_ADDR_dec_dest_bufy_addr_START  (0)
#define SOC_SOCP_DEC_DEST_BUFY_ADDR_dec_dest_bufy_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_DEST_BUFY_CFG0_UNION
 �ṹ˵��  : DEC_DEST_BUFY_CFG0 �Ĵ����ṹ���塣��ַƫ����:0xC0C+0x10*(y)����ֵ:0xFF010000�����:32
 �Ĵ���˵��: ����ͨ·Ŀ��buffery���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dec_dest_bufy_size : 16; /* bit[0-15] : ����ͨ·Ŀ��buffery��С�Ĵ������ֽ�Ϊ��λ��8�ֽڵ������� */
        unsigned int  dec_int_threshold  : 8;  /* bit[16-23]: ����ͨ·�ж��ϱ���ֵ���ޣ������ݰ�Ϊ��λ�� */
        unsigned int  data_type          : 8;  /* bit[24-31]: ����Ŀ��buffer�Ķ�ģ����ָʾ��Ŀǰʹ��3��ģ����0��ʾLTE��TDSģ��Ӧ��Ŀ��buffer����1��ʾGUģ��Ӧ��Ŀ��buffer�� */
    } reg;
} SOC_SOCP_DEC_DEST_BUFY_CFG0_UNION;
#endif
#define SOC_SOCP_DEC_DEST_BUFY_CFG0_dec_dest_bufy_size_START  (0)
#define SOC_SOCP_DEC_DEST_BUFY_CFG0_dec_dest_bufy_size_END    (15)
#define SOC_SOCP_DEC_DEST_BUFY_CFG0_dec_int_threshold_START   (16)
#define SOC_SOCP_DEC_DEST_BUFY_CFG0_dec_int_threshold_END     (23)
#define SOC_SOCP_DEC_DEST_BUFY_CFG0_data_type_START           (24)
#define SOC_SOCP_DEC_DEST_BUFY_CFG0_data_type_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CD_DBG0_UNION
 �ṹ˵��  : ENC_CD_DBG0 �Ĵ����ṹ���塣��ַƫ����:0xE00����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����CD debug�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cd_buf_baddr : 32; /* bit[0-31]: CD��ϢƬbuffer��ʼ��ַ */
    } reg;
} SOC_SOCP_ENC_CD_DBG0_UNION;
#endif
#define SOC_SOCP_ENC_CD_DBG0_cd_buf_baddr_START  (0)
#define SOC_SOCP_ENC_CD_DBG0_cd_buf_baddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_CD_DBG1_UNION
 �ṹ˵��  : ENC_CD_DBG1 �Ĵ����ṹ���塣��ַƫ����:0xE04����ֵ:0x00020000�����:32
 �Ĵ���˵��: ����CD debug�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cd_blk_len   : 16; /* bit[0-15] : CD��ϢƬ���ݰ���С */
        unsigned int  cd_last_flag : 1;  /* bit[16]   : ���һ��CD��ϢƬ
                                                        1�����һ��
                                                        0���������һ�� */
        unsigned int  cd_idle      : 1;  /* bit[17]   : cd_ctrlģ�鴦�ڿ���״̬
                                                        1������
                                                        0�������� */
        unsigned int  reserved     : 14; /* bit[18-31]: ���� */
    } reg;
} SOC_SOCP_ENC_CD_DBG1_UNION;
#endif
#define SOC_SOCP_ENC_CD_DBG1_cd_blk_len_START    (0)
#define SOC_SOCP_ENC_CD_DBG1_cd_blk_len_END      (15)
#define SOC_SOCP_ENC_CD_DBG1_cd_last_flag_START  (16)
#define SOC_SOCP_ENC_CD_DBG1_cd_last_flag_END    (16)
#define SOC_SOCP_ENC_CD_DBG1_cd_idle_START       (17)
#define SOC_SOCP_ENC_CD_DBG1_cd_idle_END         (17)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_IBUF_DBG0_UNION
 �ṹ˵��  : ENC_IBUF_DBG0 �Ĵ����ṹ���塣��ַƫ����:0xE08����ֵ:0x00000080�����:32
 �Ĵ���˵��: ����Դ��debug�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ibuf_fsm_state : 3;  /* bit[0-2]  : ibuf_ctrl״̬��״̬
                                                          3'b000��IDLE
                                                          3'b001��REQ_HEAD
                                                          3'b011��XFER_HEAD
                                                          3;b100��REQ_DATA
                                                          3'b110��XFER_DATA
                                                          3'b111��WAIT_IFIFO_RDY */
        unsigned int  reserved_0     : 1;  /* bit[3]    : ���� */
        unsigned int  eop            : 1;  /* bit[4]    : ��βָʾ�ź�
                                                          1����β
                                                          0���ǰ�β */
        unsigned int  sop            : 1;  /* bit[5]    : ��ͷָʾ�ź�
                                                          1����ͷ
                                                          0���ǰ�ͷ */
        unsigned int  fifo_full      : 1;  /* bit[6]    : fifo��ָʾ
                                                          1��fifo��
                                                          0��fifo���� */
        unsigned int  fifo_empty     : 1;  /* bit[7]    : fifo��ָʾ
                                                          1��fifo��
                                                          0��fifo���� */
        unsigned int  reserved_1     : 8;  /* bit[8-15] : ���� */
        unsigned int  remain_blk_cnt : 16; /* bit[16-31]: ���ݰ���������ֽ��� */
    } reg;
} SOC_SOCP_ENC_IBUF_DBG0_UNION;
#endif
#define SOC_SOCP_ENC_IBUF_DBG0_ibuf_fsm_state_START  (0)
#define SOC_SOCP_ENC_IBUF_DBG0_ibuf_fsm_state_END    (2)
#define SOC_SOCP_ENC_IBUF_DBG0_eop_START             (4)
#define SOC_SOCP_ENC_IBUF_DBG0_eop_END               (4)
#define SOC_SOCP_ENC_IBUF_DBG0_sop_START             (5)
#define SOC_SOCP_ENC_IBUF_DBG0_sop_END               (5)
#define SOC_SOCP_ENC_IBUF_DBG0_fifo_full_START       (6)
#define SOC_SOCP_ENC_IBUF_DBG0_fifo_full_END         (6)
#define SOC_SOCP_ENC_IBUF_DBG0_fifo_empty_START      (7)
#define SOC_SOCP_ENC_IBUF_DBG0_fifo_empty_END        (7)
#define SOC_SOCP_ENC_IBUF_DBG0_remain_blk_cnt_START  (16)
#define SOC_SOCP_ENC_IBUF_DBG0_remain_blk_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_IBUF_DBG1_UNION
 �ṹ˵��  : ENC_IBUF_DBG1 �Ĵ����ṹ���塣��ַƫ����:0xE0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Դ��debug�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_addr : 32; /* bit[0-31]: ��ǰ����ĵ�ַ */
    } reg;
} SOC_SOCP_ENC_IBUF_DBG1_UNION;
#endif
#define SOC_SOCP_ENC_IBUF_DBG1_dma_addr_START  (0)
#define SOC_SOCP_ENC_IBUF_DBG1_dma_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_IBUF_DBG2_UNION
 �ṹ˵��  : ENC_IBUF_DBG2 �Ĵ����ṹ���塣��ַƫ����:0xE10����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Դ��debug�Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ibuf_fifo_dout_lo : 32; /* bit[0-31]: FIFO�����ĵ�ǰ����bit[31:0] */
    } reg;
} SOC_SOCP_ENC_IBUF_DBG2_UNION;
#endif
#define SOC_SOCP_ENC_IBUF_DBG2_ibuf_fifo_dout_lo_START  (0)
#define SOC_SOCP_ENC_IBUF_DBG2_ibuf_fifo_dout_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_IBUF_DBG3_UNION
 �ṹ˵��  : ENC_IBUF_DBG3 �Ĵ����ṹ���塣��ַƫ����:0xE14����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Դ��debug�Ĵ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ibuf_fifo_dout_hi : 32; /* bit[0-31]: FIFO�����ĵ�ǰ����bit[63:32] */
    } reg;
} SOC_SOCP_ENC_IBUF_DBG3_UNION;
#endif
#define SOC_SOCP_ENC_IBUF_DBG3_ibuf_fifo_dout_hi_START  (0)
#define SOC_SOCP_ENC_IBUF_DBG3_ibuf_fifo_dout_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_OBUF_DBG0_UNION
 �ṹ˵��  : ENC_OBUF_DBG0 �Ĵ����ṹ���塣��ַƫ����:0xE18����ֵ:0x00000380�����:32
 �Ĵ���˵��: ����Ŀ�Ķ�debug�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  obuf_fsm_state : 3;  /* bit[0-2]  : obuf_ctrl״̬��״̬
                                                          3'b000:IDLE
                                                          3'b001:REQ_DATA
                                                          3'b011:XFER_DATA
                                                          3'b111:REQ_FLAG
                                                          3'b101:XFER_FLAG
                                                          3'b010:WAIT_DMA_RDY
                                                          3'b100:WAIT_RESP_DONE */
        unsigned int  reserved_0     : 2;  /* bit[3-4]  : ���� */
        unsigned int  fifo_afull     : 1;  /* bit[5]    : fifo����ָʾ
                                                          1��fifo����
                                                          0��fifo�ǽ��� */
        unsigned int  fifo_full      : 1;  /* bit[6]    : fifo��ָʾ
                                                          1��fifo��
                                                          0��fifo���� */
        unsigned int  fifo_empty     : 1;  /* bit[7]    : fifo��ָʾ
                                                          1��fifo��
                                                          0��fifo���� */
        unsigned int  eop            : 1;  /* bit[8]    : ��βָʾ�ź�
                                                          1����β
                                                          0���ǰ�β */
        unsigned int  sop            : 1;  /* bit[9]    : ��ͷָʾ�ź�
                                                          1����β
                                                          0���ǰ�β */
        unsigned int  reserved_1     : 6;  /* bit[10-15]: ���� */
        unsigned int  pkt_in_cnt     : 16; /* bit[16-31]: ��������������ֽ��� */
    } reg;
} SOC_SOCP_ENC_OBUF_DBG0_UNION;
#endif
#define SOC_SOCP_ENC_OBUF_DBG0_obuf_fsm_state_START  (0)
#define SOC_SOCP_ENC_OBUF_DBG0_obuf_fsm_state_END    (2)
#define SOC_SOCP_ENC_OBUF_DBG0_fifo_afull_START      (5)
#define SOC_SOCP_ENC_OBUF_DBG0_fifo_afull_END        (5)
#define SOC_SOCP_ENC_OBUF_DBG0_fifo_full_START       (6)
#define SOC_SOCP_ENC_OBUF_DBG0_fifo_full_END         (6)
#define SOC_SOCP_ENC_OBUF_DBG0_fifo_empty_START      (7)
#define SOC_SOCP_ENC_OBUF_DBG0_fifo_empty_END        (7)
#define SOC_SOCP_ENC_OBUF_DBG0_eop_START             (8)
#define SOC_SOCP_ENC_OBUF_DBG0_eop_END               (8)
#define SOC_SOCP_ENC_OBUF_DBG0_sop_START             (9)
#define SOC_SOCP_ENC_OBUF_DBG0_sop_END               (9)
#define SOC_SOCP_ENC_OBUF_DBG0_pkt_in_cnt_START      (16)
#define SOC_SOCP_ENC_OBUF_DBG0_pkt_in_cnt_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_OBUF_DBG1_UNION
 �ṹ˵��  : ENC_OBUF_DBG1 �Ĵ����ṹ���塣��ַƫ����:0xE1C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Ŀ�Ķ�debug�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pkt_out_cnt : 16; /* bit[0-15] : ��ǰ������ֽ��� */
        unsigned int  reserved    : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SOCP_ENC_OBUF_DBG1_UNION;
#endif
#define SOC_SOCP_ENC_OBUF_DBG1_pkt_out_cnt_START  (0)
#define SOC_SOCP_ENC_OBUF_DBG1_pkt_out_cnt_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_OBUF_DBG2_UNION
 �ṹ˵��  : ENC_OBUF_DBG2 �Ĵ����ṹ���塣��ַƫ����:0xE20����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Ŀ�Ķ�debug�Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nxt_dma_addr : 32; /* bit[0-31]: �����ַ */
    } reg;
} SOC_SOCP_ENC_OBUF_DBG2_UNION;
#endif
#define SOC_SOCP_ENC_OBUF_DBG2_nxt_dma_addr_START  (0)
#define SOC_SOCP_ENC_OBUF_DBG2_nxt_dma_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_ENC_OBUF_DBG3_UNION
 �ṹ˵��  : ENC_OBUF_DBG3 �Ĵ����ṹ���塣��ַƫ����:0xE24����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Ŀ�Ķ�debug�Ĵ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  obuf_fifo_dout_lo : 32; /* bit[0-31]: FIFO�����ĵ�ǰ����bit[31:0] */
    } reg;
} SOC_SOCP_ENC_OBUF_DBG3_UNION;
#endif
#define SOC_SOCP_ENC_OBUF_DBG3_obuf_fifo_dout_lo_START  (0)
#define SOC_SOCP_ENC_OBUF_DBG3_obuf_fifo_dout_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_IBUF_DBG0_UNION
 �ṹ˵��  : DEC_IBUF_DBG0 �Ĵ����ṹ���塣��ַƫ����:0xE28����ֵ:0x000000A0�����:32
 �Ĵ���˵��: ����Դ��debug�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ibuf_fsm_state : 4;  /* bit[0-3]  : ibuf_ctrl״̬��״̬
                                                          3'b000��IDLE
                                                          3;b100��REQ_DATA
                                                          3'b110��XFER_DATA
                                                          3'b010��WAIT_IFIFO_RDY
                                                          3'b011��WAIT_BUF_RDY */
        unsigned int  ibuf_rdy       : 1;  /* bit[4]    : ����buffer����׼����ָʾ�ź�
                                                          1������׼����
                                                          0������δ׼���� */
        unsigned int  dec_end        : 1;  /* bit[5]    : �������ָʾ�źš�
                                                          1���������
                                                          0������δ��� */
        unsigned int  fifo_full      : 1;  /* bit[6]    : fifo��ָʾ
                                                          1��fifo��
                                                          0��fifo���� */
        unsigned int  fifo_empty     : 1;  /* bit[7]    : fifo��ָʾ
                                                          1��fifo��
                                                          0��fifo���� */
        unsigned int  reserved       : 8;  /* bit[8-15] : ���� */
        unsigned int  remain_blk_cnt : 16; /* bit[16-31]: ���ݰ���������ֽ��� */
    } reg;
} SOC_SOCP_DEC_IBUF_DBG0_UNION;
#endif
#define SOC_SOCP_DEC_IBUF_DBG0_ibuf_fsm_state_START  (0)
#define SOC_SOCP_DEC_IBUF_DBG0_ibuf_fsm_state_END    (3)
#define SOC_SOCP_DEC_IBUF_DBG0_ibuf_rdy_START        (4)
#define SOC_SOCP_DEC_IBUF_DBG0_ibuf_rdy_END          (4)
#define SOC_SOCP_DEC_IBUF_DBG0_dec_end_START         (5)
#define SOC_SOCP_DEC_IBUF_DBG0_dec_end_END           (5)
#define SOC_SOCP_DEC_IBUF_DBG0_fifo_full_START       (6)
#define SOC_SOCP_DEC_IBUF_DBG0_fifo_full_END         (6)
#define SOC_SOCP_DEC_IBUF_DBG0_fifo_empty_START      (7)
#define SOC_SOCP_DEC_IBUF_DBG0_fifo_empty_END        (7)
#define SOC_SOCP_DEC_IBUF_DBG0_remain_blk_cnt_START  (16)
#define SOC_SOCP_DEC_IBUF_DBG0_remain_blk_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_IBUF_DBG1_UNION
 �ṹ˵��  : DEC_IBUF_DBG1 �Ĵ����ṹ���塣��ַƫ����:0xE2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Դ��debug�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dma_addr : 32; /* bit[0-31]: ��ǰ����ĵ�ַ */
    } reg;
} SOC_SOCP_DEC_IBUF_DBG1_UNION;
#endif
#define SOC_SOCP_DEC_IBUF_DBG1_dma_addr_START  (0)
#define SOC_SOCP_DEC_IBUF_DBG1_dma_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_IBUF_DBG2_UNION
 �ṹ˵��  : DEC_IBUF_DBG2 �Ĵ����ṹ���塣��ַƫ����:0xE30����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Դ��debug�Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ibuf_fifo_dout_lo : 32; /* bit[0-31]: FIFO�����ĵ�ǰ����bit[31:0] */
    } reg;
} SOC_SOCP_DEC_IBUF_DBG2_UNION;
#endif
#define SOC_SOCP_DEC_IBUF_DBG2_ibuf_fifo_dout_lo_START  (0)
#define SOC_SOCP_DEC_IBUF_DBG2_ibuf_fifo_dout_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_IBUF_DBG3_UNION
 �ṹ˵��  : DEC_IBUF_DBG3 �Ĵ����ṹ���塣��ַƫ����:0xE34����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Դ��debug�Ĵ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ibuf_fifo_dout_hi : 32; /* bit[0-31]: FIFO�����ĵ�ǰ����bit[63:32] */
    } reg;
} SOC_SOCP_DEC_IBUF_DBG3_UNION;
#endif
#define SOC_SOCP_DEC_IBUF_DBG3_ibuf_fifo_dout_hi_START  (0)
#define SOC_SOCP_DEC_IBUF_DBG3_ibuf_fifo_dout_hi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_OBUF_DBG0_UNION
 �ṹ˵��  : DEC_OBUF_DBG0 �Ĵ����ṹ���塣��ַƫ����:0xE38����ֵ:0x00000080�����:32
 �Ĵ���˵��: ����Ŀ�Ķ�debug�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  obuf_fsm_state : 3;  /* bit[0-2]  : obuf_ctrl״̬��״̬
                                                          3'b000:IDLE
                                                          3'b001:REQ_DATA
                                                          3'b011:XFER_DATA
                                                          3'b111:REQ_FLAG
                                                          3'b101:XFER_FLAG
                                                          3'b010:WAIT_DMA_RDY
                                                          3'b100:WAIT_RESP_DONE */
        unsigned int  reserved_0     : 2;  /* bit[3-4]  : ���� */
        unsigned int  fifo_afull     : 1;  /* bit[5]    : fifo����ָʾ
                                                          1��fifo����
                                                          0��fifo�ǽ��� */
        unsigned int  fifo_full      : 1;  /* bit[6]    : fifo��ָʾ
                                                          1��fifo��
                                                          0��fifo���� */
        unsigned int  fifo_empty     : 1;  /* bit[7]    : fifo��ָʾ
                                                          1��fifo��
                                                          0��fifo���� */
        unsigned int  eop            : 1;  /* bit[8]    : ��βָʾ�ź�
                                                          1����β
                                                          0���ǰ�β */
        unsigned int  sop            : 1;  /* bit[9]    : ��ͷָʾ�ź�
                                                          1����ͷ
                                                          0���ǰ�ͷ */
        unsigned int  reserved_1     : 6;  /* bit[10-15]: ���� */
        unsigned int  pkt_in_cnt     : 16; /* bit[16-31]: ��������������ֽ��� */
    } reg;
} SOC_SOCP_DEC_OBUF_DBG0_UNION;
#endif
#define SOC_SOCP_DEC_OBUF_DBG0_obuf_fsm_state_START  (0)
#define SOC_SOCP_DEC_OBUF_DBG0_obuf_fsm_state_END    (2)
#define SOC_SOCP_DEC_OBUF_DBG0_fifo_afull_START      (5)
#define SOC_SOCP_DEC_OBUF_DBG0_fifo_afull_END        (5)
#define SOC_SOCP_DEC_OBUF_DBG0_fifo_full_START       (6)
#define SOC_SOCP_DEC_OBUF_DBG0_fifo_full_END         (6)
#define SOC_SOCP_DEC_OBUF_DBG0_fifo_empty_START      (7)
#define SOC_SOCP_DEC_OBUF_DBG0_fifo_empty_END        (7)
#define SOC_SOCP_DEC_OBUF_DBG0_eop_START             (8)
#define SOC_SOCP_DEC_OBUF_DBG0_eop_END               (8)
#define SOC_SOCP_DEC_OBUF_DBG0_sop_START             (9)
#define SOC_SOCP_DEC_OBUF_DBG0_sop_END               (9)
#define SOC_SOCP_DEC_OBUF_DBG0_pkt_in_cnt_START      (16)
#define SOC_SOCP_DEC_OBUF_DBG0_pkt_in_cnt_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_OBUF_DBG1_UNION
 �ṹ˵��  : DEC_OBUF_DBG1 �Ĵ����ṹ���塣��ַƫ����:0xE3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Ŀ�Ķ�debug�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pkt_out_cnt : 16; /* bit[0-15] : ��ǰ������ֽ��� */
        unsigned int  reserved    : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_SOCP_DEC_OBUF_DBG1_UNION;
#endif
#define SOC_SOCP_DEC_OBUF_DBG1_pkt_out_cnt_START  (0)
#define SOC_SOCP_DEC_OBUF_DBG1_pkt_out_cnt_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_OBUF_DBG2_UNION
 �ṹ˵��  : DEC_OBUF_DBG2 �Ĵ����ṹ���塣��ַƫ����:0xE40����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Ŀ�Ķ�debug�Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nxt_dma_addr : 32; /* bit[0-31]: dma�����ַ */
    } reg;
} SOC_SOCP_DEC_OBUF_DBG2_UNION;
#endif
#define SOC_SOCP_DEC_OBUF_DBG2_nxt_dma_addr_START  (0)
#define SOC_SOCP_DEC_OBUF_DBG2_nxt_dma_addr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_DEC_OBUF_DBG3_UNION
 �ṹ˵��  : DEC_OBUF_DBG3 �Ĵ����ṹ���塣��ַƫ����:0xE44����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Ŀ�Ķ�debug�Ĵ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  obuf_fifo_dout_lo : 32; /* bit[0-31]: FIFO�����ĵ�ǰ����bit[31:0] */
    } reg;
} SOC_SOCP_DEC_OBUF_DBG3_UNION;
#endif
#define SOC_SOCP_DEC_OBUF_DBG3_obuf_fifo_dout_lo_START  (0)
#define SOC_SOCP_DEC_OBUF_DBG3_obuf_fifo_dout_lo_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SOCP_VERSION_UNION
 �ṹ˵��  : VERSION �Ĵ����ṹ���塣��ַƫ����:0xFFC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �汾ָʾ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  socp_version : 32; /* bit[0-31]: ָʾ��ǰSOCP�������汾�� */
    } reg;
} SOC_SOCP_VERSION_UNION;
#endif
#define SOC_SOCP_VERSION_socp_version_START  (0)
#define SOC_SOCP_VERSION_socp_version_END    (31)






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

#endif /* end of soc_socp_interface.h */
