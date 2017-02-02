/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_mctl_sys_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:11
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_MCTL_SYS.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_MCTL_SYS_INTERFACE_H__
#define __SOC_DSS_MCTL_SYS_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_MCTL_SYS
 ****************************************************************************/
/* �Ĵ���˵������ȫ���üĴ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_CTL_SECU_CFG_UNION */
#define SOC_DSS_MCTL_SYS_CTL_SECU_CFG_ADDR(base)      ((base) + (0x0000))

/* �Ĵ���˵������ģ��Ĵ���ˢ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_ADDR(base) ((base) + (0x0018))

/* �Ĵ���˵������ȫ��ֹͨ·����
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_UNION */
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ADDR(base)    ((base) + (0x0080))

/* �Ĵ���˵������ȫ��ֹͨ·����
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_UNION */
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ADDR(base)    ((base) + (0x0084))

/* �Ĵ���˵������ȫ��ֹͨ·����
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_UNION */
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_ADDR(base)    ((base) + (0x0088))

/* �Ĵ���˵������ȫ��ֹͨ·����
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_UNION */
#define SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_ADDR(base)  ((base) + (0x00A0))

/* �Ĵ���˵������ȫ��ֹͨ·����
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_UNION */
#define SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_ADDR(base)  ((base) + (0x00A4))

/* �Ĵ���˵������ģ��Ĵ���ˢ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_ADDR(base)     ((base) + (0x0100))

/* �Ĵ���˵������ģ��Ĵ���ˢ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_ADDR(base)     ((base) + (0x0104))

/* �Ĵ���˵������ģ��Ĵ���ˢ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_ADDR(base)     ((base) + (0x0108))

/* �Ĵ���˵������ģ��Ĵ���ˢ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_ADDR(base)     ((base) + (0x010C))

/* �Ĵ���˵������ģ��Ĵ���ˢ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_ADDR(base)     ((base) + (0x0110))

/* �Ĵ���˵������ģ��Ĵ���ˢ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_ADDR(base)     ((base) + (0x0114))

/* �Ĵ���˵������ģ��Ĵ���ˢ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_ADDR(base)     ((base) + (0x0118))

/* �Ĵ���˵������ģ��Ĵ���ˢ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_ADDR(base)     ((base) + (0x011C))

/* �Ĵ���˵������ģ��Ĵ���ˢ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_ADDR(base)     ((base) + (0x0120))

/* �Ĵ���˵������ģ��Ĵ���ˢ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_ADDR(base)     ((base) + (0x0124))

/* �Ĵ���˵������ģ��Ĵ���ˢ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_ADDR(base)      ((base) + (0x0128))

/* �Ĵ���˵������ģ��Ĵ���ˢ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_ADDR(base)      ((base) + (0x012C))

/* �Ĵ���˵������ģ��Ĵ���ˢ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_ADDR(base)      ((base) + (0x0130))

/* �Ĵ���˵������ģ��Ĵ���ˢ��ʹ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_UNION */
#define SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_ADDR(base)      ((base) + (0x0134))

/* �Ĵ���˵����RCH��ӦOV��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH0_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH0_OV_OEN_ADDR(base)       ((base) + (0x0160))

/* �Ĵ���˵����RCH��ӦOV��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH1_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH1_OV_OEN_ADDR(base)       ((base) + (0x0164))

/* �Ĵ���˵����RCH��ӦOV��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH2_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH2_OV_OEN_ADDR(base)       ((base) + (0x0168))

/* �Ĵ���˵����RCH��ӦOV��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH3_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH3_OV_OEN_ADDR(base)       ((base) + (0x016C))

/* �Ĵ���˵����RCH��ӦOV��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH4_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH4_OV_OEN_ADDR(base)       ((base) + (0x0170))

/* �Ĵ���˵����RCH��ӦOV��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH5_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH5_OV_OEN_ADDR(base)       ((base) + (0x0174))

/* �Ĵ���˵����RCH��ӦOV��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH6_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH6_OV_OEN_ADDR(base)       ((base) + (0x0178))

/* �Ĵ���˵����RCH��ӦOV��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH7_OV_OEN_UNION */
#define SOC_DSS_MCTL_SYS_RCH7_OV_OEN_ADDR(base)       ((base) + (0x017C))

/* �Ĵ���˵����RCH��ӦOV0��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH_OV0_SEL_UNION */
#define SOC_DSS_MCTL_SYS_RCH_OV0_SEL_ADDR(base)       ((base) + (0x0180))

/* �Ĵ���˵����RCH��ӦOV1��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH_OV1_SEL_UNION */
#define SOC_DSS_MCTL_SYS_RCH_OV1_SEL_ADDR(base)       ((base) + (0x0184))

/* �Ĵ���˵����RCH��ӦOV2��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH_OV2_SEL_UNION */
#define SOC_DSS_MCTL_SYS_RCH_OV2_SEL_ADDR(base)       ((base) + (0x0188))

/* �Ĵ���˵����RCH��ӦOV3��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH_OV3_SEL_UNION */
#define SOC_DSS_MCTL_SYS_RCH_OV3_SEL_ADDR(base)       ((base) + (0x018C))

/* �Ĵ���˵����RCH��ӦOV��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_WCH0_OV_IEN_UNION */
#define SOC_DSS_MCTL_SYS_WCH0_OV_IEN_ADDR(base)       ((base) + (0x01A0))

/* �Ĵ���˵����RCH��ӦOV��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_WCH1_OV_IEN_UNION */
#define SOC_DSS_MCTL_SYS_WCH1_OV_IEN_ADDR(base)       ((base) + (0x01A4))

/* �Ĵ���˵����RCH��ӦOV��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_WCH_OV2_SEL_UNION */
#define SOC_DSS_MCTL_SYS_WCH_OV2_SEL_ADDR(base)       ((base) + (0x01A8))

/* �Ĵ���˵����RCH��ӦOV��layerѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_WCH_OV3_SEL_UNION */
#define SOC_DSS_MCTL_SYS_WCH_OV3_SEL_ADDR(base)       ((base) + (0x01AC))

/* �Ĵ���˵���������ENC��wchѡ��
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_WB_ENC_SEL_UNION */
#define SOC_DSS_MCTL_SYS_WB_ENC_SEL_ADDR(base)        ((base) + (0x01B0))

/* �Ĵ���˵����DSI_MUXѡ��Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_DSI_MUX_SEL_UNION */
#define SOC_DSS_MCTL_SYS_DSI_MUX_SEL_ADDR(base)       ((base) + (0x01B4))

/* �Ĵ���˵����RCH��ӦY����
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH0_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH0_STARTY_ADDR(base)       ((base) + (0x01C0))

/* �Ĵ���˵����RCH��ӦY����
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH1_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH1_STARTY_ADDR(base)       ((base) + (0x01C4))

/* �Ĵ���˵����RCH��ӦY����
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH2_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH2_STARTY_ADDR(base)       ((base) + (0x01C8))

/* �Ĵ���˵����RCH��ӦY����
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH3_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH3_STARTY_ADDR(base)       ((base) + (0x01CC))

/* �Ĵ���˵����RCH��ӦY����
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH4_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH4_STARTY_ADDR(base)       ((base) + (0x01D0))

/* �Ĵ���˵����RCH��ӦY����
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH5_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH5_STARTY_ADDR(base)       ((base) + (0x01D4))

/* �Ĵ���˵����RCH��ӦY����
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH6_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH6_STARTY_ADDR(base)       ((base) + (0x01D8))

/* �Ĵ���˵����RCH��ӦY����
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_RCH7_STARTY_UNION */
#define SOC_DSS_MCTL_SYS_RCH7_STARTY_ADDR(base)       ((base) + (0x01DC))

/* �Ĵ���˵����һ��ģ��ʱ��ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_UNION */
#define SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_ADDR(base)      ((base) + (0x01F0))

/* �Ĵ���˵����һ��ģ��ʱ��ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MCTL_CLK_EN_UNION */
#define SOC_DSS_MCTL_SYS_MCTL_CLK_EN_ADDR(base)       ((base) + (0x01F4))

/* �Ĵ���˵����һ��ģ��ʱ��ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD_CLK_SEL_UNION */
#define SOC_DSS_MCTL_SYS_MOD_CLK_SEL_ADDR(base)       ((base) + (0x01F8))

/* �Ĵ���˵����һ��ģ��ʱ��ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD_CLK_EN_UNION */
#define SOC_DSS_MCTL_SYS_MOD_CLK_EN_ADDR(base)        ((base) + (0x01FC))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD0_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD0_DBG_ADDR(base)          ((base) + (0x0200))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD1_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD1_DBG_ADDR(base)          ((base) + (0x0204))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD2_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD2_DBG_ADDR(base)          ((base) + (0x0208))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD3_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD3_DBG_ADDR(base)          ((base) + (0x020C))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD4_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD4_DBG_ADDR(base)          ((base) + (0x0210))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD5_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD5_DBG_ADDR(base)          ((base) + (0x0214))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD6_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD6_DBG_ADDR(base)          ((base) + (0x0218))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD7_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD7_DBG_ADDR(base)          ((base) + (0x021C))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD8_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD8_DBG_ADDR(base)          ((base) + (0x0220))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD9_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD9_DBG_ADDR(base)          ((base) + (0x0224))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD10_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD10_DBG_ADDR(base)         ((base) + (0x0228))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD11_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD11_DBG_ADDR(base)         ((base) + (0x022C))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD12_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD12_DBG_ADDR(base)         ((base) + (0x0230))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD13_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD13_DBG_ADDR(base)         ((base) + (0x0234))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD14_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD14_DBG_ADDR(base)         ((base) + (0x0238))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD15_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD15_DBG_ADDR(base)         ((base) + (0x023C))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD16_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD16_DBG_ADDR(base)         ((base) + (0x0240))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD17_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD17_DBG_ADDR(base)         ((base) + (0x0244))

/* �Ĵ���˵����module��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD18_DBG_UNION */
#define SOC_DSS_MCTL_SYS_MOD18_DBG_ADDR(base)         ((base) + (0x0248))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD0_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD0_STATUS_ADDR(base)       ((base) + (0x0250))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD1_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD1_STATUS_ADDR(base)       ((base) + (0x0254))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD2_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD2_STATUS_ADDR(base)       ((base) + (0x0258))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD3_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD3_STATUS_ADDR(base)       ((base) + (0x025C))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD4_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD4_STATUS_ADDR(base)       ((base) + (0x0260))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD5_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD5_STATUS_ADDR(base)       ((base) + (0x0264))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD6_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD6_STATUS_ADDR(base)       ((base) + (0x0268))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD7_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD7_STATUS_ADDR(base)       ((base) + (0x026C))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD8_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD8_STATUS_ADDR(base)       ((base) + (0x0270))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD9_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD9_STATUS_ADDR(base)       ((base) + (0x0274))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD10_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD10_STATUS_ADDR(base)      ((base) + (0x0278))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD11_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD11_STATUS_ADDR(base)      ((base) + (0x027C))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD12_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD12_STATUS_ADDR(base)      ((base) + (0x0280))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD13_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD13_STATUS_ADDR(base)      ((base) + (0x0284))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD14_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD14_STATUS_ADDR(base)      ((base) + (0x0288))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD15_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD15_STATUS_ADDR(base)      ((base) + (0x028C))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD16_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD16_STATUS_ADDR(base)      ((base) + (0x0290))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD17_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD17_STATUS_ADDR(base)      ((base) + (0x0294))

/* �Ĵ���˵����module״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_MOD18_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_MOD18_STATUS_ADDR(base)      ((base) + (0x0298))

/* �Ĵ���˵����SW��ν�ɲ�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_SW_DBG_UNION */
#define SOC_DSS_MCTL_SYS_SW_DBG_ADDR(base)            ((base) + (0x02B0))

/* �Ĵ���˵����SW0״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_SW0_STATUS0_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS0_ADDR(base)       ((base) + (0x02B4))

/* �Ĵ���˵����SW0״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_SW0_STATUS1_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS1_ADDR(base)       ((base) + (0x02B8))

/* �Ĵ���˵����SW0״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_SW0_STATUS2_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS2_ADDR(base)       ((base) + (0x02BC))

/* �Ĵ���˵����SW0״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_SW0_STATUS3_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS3_ADDR(base)       ((base) + (0x02C0))

/* �Ĵ���˵����SW0״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_SW0_STATUS4_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS4_ADDR(base)       ((base) + (0x02C4))

/* �Ĵ���˵����SW0״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_SW0_STATUS5_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS5_ADDR(base)       ((base) + (0x02C8))

/* �Ĵ���˵����SW0״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_SW0_STATUS6_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS6_ADDR(base)       ((base) + (0x02D0))

/* �Ĵ���˵����SW0״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_SW0_STATUS7_UNION */
#define SOC_DSS_MCTL_SYS_SW0_STATUS7_ADDR(base)       ((base) + (0x02D4))

/* �Ĵ���˵����SW1״̬�Ĵ���
   λ����UNION�ṹ:  SOC_DSS_MCTL_SYS_SW1_STATUS_UNION */
#define SOC_DSS_MCTL_SYS_SW1_STATUS_ADDR(base)        ((base) + (0x02D8))





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
                     (1/1) reg_MCTL_SYS
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_CTL_SECU_CFG_UNION
 �ṹ˵��  : CTL_SECU_CFG �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȫ���üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 4;  /* bit[0-3] : ���� */
        unsigned int  pay_secu : 1;  /* bit[4]   : 1'b1:
                                                    OV0 top layer �Ĵ�����ȫ����ʹ�ܣ�
                                                    vig0 channel ���мĴ�����ȫ����ʹ�ܣ�
                                                   1'b0 : normal
                                                   ��λֵ��1'b0 */
        unsigned int  reserved_1: 27; /* bit[5-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_CTL_SECU_CFG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_CTL_SECU_CFG_pay_secu_START  (4)
#define SOC_DSS_MCTL_SYS_CTL_SECU_CFG_pay_secu_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_UNION
 �ṹ˵��  : PAY_SECU_FLUSH_EN �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ģ��Ĵ���ˢ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pay_secu_flush_en : 1;  /* bit[0]   : ��ȫ֧���Ĵ���ˢ��ʹ��
                                                            ��λֵ��0x0 */
        unsigned int  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_pay_secu_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_PAY_SECU_FLUSH_EN_pay_secu_flush_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_UNION
 �ṹ˵��  : CTL_SECU_GATE0 �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȫ��ֹͨ·����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_rch0_secu_gate : 6;  /* bit[0-5]  : ѡ��RCH��ֹ���õ�Ŀ�ض�
                                                              [5]: 1'b1 ��ֹRCH���õ�WCH1��1'b0��Ч
                                                              [4]: 1'b1 ��ֹRCH���õ�WCH0��1'b0��Ч
                                                              [3]: 1'b1 ��ֹRCH���õ�OV3��1'b0��Ч
                                                              [2]: 1'b1 ��ֹRCH���õ�OV2��1'b0��Ч
                                                              [1]: 1'b1 ��ֹRCH���õ�OV1��1'b0��Ч
                                                              [0]: 1'b1 ��ֹRCH���õ�OV0��1'b0��Ч */
        unsigned int  reserved_0         : 2;  /* bit[6-7]  : ���� */
        unsigned int  ctl_rch1_secu_gate : 6;  /* bit[8-13] : ѡ��RCH��ֹ���õ�Ŀ�ض�
                                                              [5]: 1'b1 ��ֹRCH���õ�WCH1��1'b0��Ч
                                                              [4]: 1'b1 ��ֹRCH���õ�WCH0��1'b0��Ч
                                                              [3]: 1'b1 ��ֹRCH���õ�OV3��1'b0��Ч
                                                              [2]: 1'b1 ��ֹRCH���õ�OV2��1'b0��Ч
                                                              [1]: 1'b1 ��ֹRCH���õ�OV1��1'b0��Ч
                                                              [0]: 1'b1 ��ֹRCH���õ�OV0��1'b0��Ч */
        unsigned int  reserved_1         : 2;  /* bit[14-15]: ���� */
        unsigned int  ctl_rch2_secu_gate : 6;  /* bit[16-21]: ѡ��RCH��ֹ���õ�Ŀ�ض�
                                                              [5]: 1'b1 ��ֹRCH���õ�WCH1��1'b0��Ч
                                                              [4]: 1'b1 ��ֹRCH���õ�WCH0��1'b0��Ч
                                                              [3]: 1'b1 ��ֹRCH���õ�OV3��1'b0��Ч
                                                              [2]: 1'b1 ��ֹRCH���õ�OV2��1'b0��Ч
                                                              [1]: 1'b1 ��ֹRCH���õ�OV1��1'b0��Ч
                                                              [0]: 1'b1 ��ֹRCH���õ�OV0��1'b0��Ч */
        unsigned int  reserved_2         : 2;  /* bit[22-23]: ���� */
        unsigned int  ctl_rch3_secu_gate : 6;  /* bit[24-29]: ѡ��RCH��ֹ���õ�Ŀ�ض�
                                                              [5]: 1'b1 ��ֹRCH���õ�WCH1��1'b0��Ч
                                                              [4]: 1'b1 ��ֹRCH���õ�WCH0��1'b0��Ч
                                                              [3]: 1'b1 ��ֹRCH���õ�OV3��1'b0��Ч
                                                              [2]: 1'b1 ��ֹRCH���õ�OV2��1'b0��Ч
                                                              [1]: 1'b1 ��ֹRCH���õ�OV1��1'b0��Ч
                                                              [0]: 1'b1 ��ֹRCH���õ�OV0��1'b0��Ч */
        unsigned int  reserved_3         : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_UNION;
#endif
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch0_secu_gate_START  (0)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch0_secu_gate_END    (5)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch1_secu_gate_START  (8)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch1_secu_gate_END    (13)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch2_secu_gate_START  (16)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch2_secu_gate_END    (21)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch3_secu_gate_START  (24)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE0_ctl_rch3_secu_gate_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_UNION
 �ṹ˵��  : CTL_SECU_GATE1 �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȫ��ֹͨ·����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ctl_rch4_secu_gate : 6;  /* bit[0-5]  : ѡ��RCH��ֹ���õ�Ŀ�ض�
                                                              [5]: 1'b1 ��ֹRCH���õ�WCH1��1'b0��Ч
                                                              [4]: 1'b1 ��ֹRCH���õ�WCH0��1'b0��Ч
                                                              [3]: 1'b1 ��ֹRCH���õ�OV3��1'b0��Ч
                                                              [2]: 1'b1 ��ֹRCH���õ�OV2��1'b0��Ч
                                                              [1]: 1'b1 ��ֹRCH���õ�OV1��1'b0��Ч
                                                              [0]: 1'b1 ��ֹRCH���õ�OV0��1'b0��Ч */
        unsigned int  reserved_0         : 2;  /* bit[6-7]  : ���� */
        unsigned int  ctl_rch5_secu_gate : 6;  /* bit[8-13] : ѡ��RCH��ֹ���õ�Ŀ�ض�
                                                              [5]: 1'b1 ��ֹRCH���õ�WCH1��1'b0��Ч
                                                              [4]: 1'b1 ��ֹRCH���õ�WCH0��1'b0��Ч
                                                              [3]: 1'b1 ��ֹRCH���õ�OV3��1'b0��Ч
                                                              [2]: 1'b1 ��ֹRCH���õ�OV2��1'b0��Ч
                                                              [1]: 1'b1 ��ֹRCH���õ�OV1��1'b0��Ч
                                                              [0]: 1'b1 ��ֹRCH���õ�OV0��1'b0��Ч */
        unsigned int  reserved_1         : 2;  /* bit[14-15]: ���� */
        unsigned int  ctl_rch6_secu_gate : 6;  /* bit[16-21]: ѡ��RCH��ֹ���õ�Ŀ�ض�
                                                              [5]: 1'b1 ��ֹRCH���õ�WCH1��1'b0��Ч
                                                              [4]: 1'b1 ��ֹRCH���õ�WCH0��1'b0��Ч
                                                              [3]: 1'b1 ��ֹRCH���õ�OV3��1'b0��Ч
                                                              [2]: 1'b1 ��ֹRCH���õ�OV2��1'b0��Ч
                                                              [1]: 1'b1 ��ֹRCH���õ�OV1��1'b0��Ч
                                                              [0]: 1'b1 ��ֹRCH���õ�OV0��1'b0��Ч */
        unsigned int  reserved_2         : 2;  /* bit[22-23]: ���� */
        unsigned int  ctl_rch7_secu_gate : 6;  /* bit[24-29]: ѡ��RCH��ֹ���õ�Ŀ�ض�
                                                              [5]: 1'b1 ��ֹRCH���õ�WCH1��1'b0��Ч
                                                              [4]: 1'b1 ��ֹRCH���õ�WCH0��1'b0��Ч
                                                              [3]: 1'b1 ��ֹRCH���õ�OV3��1'b0��Ч
                                                              [2]: 1'b1 ��ֹRCH���õ�OV2��1'b0��Ч
                                                              [1]: 1'b1 ��ֹRCH���õ�OV1��1'b0��Ч
                                                              [0]: 1'b1 ��ֹRCH���õ�OV0��1'b0��Ч */
        unsigned int  reserved_3         : 2;  /* bit[30-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_UNION;
#endif
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch4_secu_gate_START  (0)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch4_secu_gate_END    (5)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch5_secu_gate_START  (8)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch5_secu_gate_END    (13)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch6_secu_gate_START  (16)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch6_secu_gate_END    (21)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch7_secu_gate_START  (24)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE1_ctl_rch7_secu_gate_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_UNION
 �ṹ˵��  : CTL_SECU_GATE2 �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȫ��ֹͨ·����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 4;  /* bit[0-3] : ���� */
        unsigned int  ctl_ov2_secu_gate : 2;  /* bit[4-5] : ѡ��OV��ֹ���õ�Ŀ�ض�
                                                            [1]: 1'b1 ��ֹOV2���õ�WCH1��1'b0��Ч
                                                            [0]: 1'b1 ��ֹOV2���õ�WCH0��1'b0��Ч */
        unsigned int  ctl_ov3_secu_gate : 2;  /* bit[6-7] : ѡ��OV��ֹ���õ�Ŀ�ض�
                                                            [1]: 1'b1 ��ֹOV3���õ�WCH1��1'b0��Ч
                                                            [0]: 1'b1 ��ֹOV3���õ�WCH0��1'b0��Ч */
        unsigned int  reserved_1        : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_UNION;
#endif
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_ctl_ov2_secu_gate_START  (4)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_ctl_ov2_secu_gate_END    (5)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_ctl_ov3_secu_gate_START  (6)
#define SOC_DSS_MCTL_SYS_CTL_SECU_GATE2_ctl_ov3_secu_gate_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_UNION
 �ṹ˵��  : DSI0_SECU_CFG_EN �Ĵ����ṹ���塣��ַƫ����:0x00A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȫ��ֹͨ·����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi0_secu_cfg_en : 1;  /* bit[0]   : �������ɰ�ȫOS����
                                                           1����ȫ
                                                           0����Ч
                                                           DSI0 ��ַ6c��70Ϊ��ȫOS���� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_dsi0_secu_cfg_en_START  (0)
#define SOC_DSS_MCTL_SYS_DSI0_SECU_CFG_EN_dsi0_secu_cfg_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_UNION
 �ṹ˵��  : DSI1_SECU_CFG_EN �Ĵ����ṹ���塣��ַƫ����:0x00A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȫ��ֹͨ·����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi1_secu_cfg_en : 1;  /* bit[0]   : �������ɰ�ȫOS����
                                                           1����ȫ
                                                           0����Ч
                                                           DSI0 ��ַ6c��70Ϊ��ȫOS���� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_dsi1_secu_cfg_en_START  (0)
#define SOC_DSS_MCTL_SYS_DSI1_SECU_CFG_EN_dsi1_secu_cfg_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_UNION
 �ṹ˵��  : RCH0_FLUSH_EN �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ģ��Ĵ���ˢ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch0_flush_en : 1;  /* bit[0]   : rch0�Ĵ���ˢ��ʹ��
                                                        ��λֵ��0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_rch0_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH0_FLUSH_EN_rch0_flush_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_UNION
 �ṹ˵��  : RCH1_FLUSH_EN �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ģ��Ĵ���ˢ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch1_flush_en : 1;  /* bit[0]   : rch1�Ĵ���ˢ��ʹ��
                                                        ��λֵ��0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_rch1_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH1_FLUSH_EN_rch1_flush_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_UNION
 �ṹ˵��  : RCH2_FLUSH_EN �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ģ��Ĵ���ˢ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch2_flush_en : 1;  /* bit[0]   : rch2�Ĵ���ˢ��ʹ��
                                                        ��λֵ��0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_rch2_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH2_FLUSH_EN_rch2_flush_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_UNION
 �ṹ˵��  : RCH3_FLUSH_EN �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ģ��Ĵ���ˢ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch3_flush_en : 1;  /* bit[0]   : rch3�Ĵ���ˢ��ʹ��
                                                        ��λֵ��0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_rch3_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH3_FLUSH_EN_rch3_flush_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_UNION
 �ṹ˵��  : RCH4_FLUSH_EN �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ģ��Ĵ���ˢ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch4_flush_en : 1;  /* bit[0]   : rch4�Ĵ���ˢ��ʹ��
                                                        ��λֵ��0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_rch4_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH4_FLUSH_EN_rch4_flush_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_UNION
 �ṹ˵��  : RCH5_FLUSH_EN �Ĵ����ṹ���塣��ַƫ����:0x0114����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ģ��Ĵ���ˢ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch5_flush_en : 1;  /* bit[0]   : rch5�Ĵ���ˢ��ʹ��
                                                        ��λֵ��0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_rch5_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH5_FLUSH_EN_rch5_flush_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_UNION
 �ṹ˵��  : RCH6_FLUSH_EN �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ģ��Ĵ���ˢ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch6_flush_en : 1;  /* bit[0]   : rch6�Ĵ���ˢ��ʹ��
                                                        ��λֵ��0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_rch6_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH6_FLUSH_EN_rch6_flush_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_UNION
 �ṹ˵��  : RCH7_FLUSH_EN �Ĵ����ṹ���塣��ַƫ����:0x011C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ģ��Ĵ���ˢ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch7_flush_en : 1;  /* bit[0]   : rch7�Ĵ���ˢ��ʹ��
                                                        ��λֵ��0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_rch7_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_RCH7_FLUSH_EN_rch7_flush_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_UNION
 �ṹ˵��  : WCH0_FLUSH_EN �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ģ��Ĵ���ˢ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch0_flush_en : 1;  /* bit[0]   : wch0�Ĵ���ˢ��ʹ��
                                                        ��λֵ��0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_wch0_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_WCH0_FLUSH_EN_wch0_flush_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_UNION
 �ṹ˵��  : WCH1_FLUSH_EN �Ĵ����ṹ���塣��ַƫ����:0x0124����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ģ��Ĵ���ˢ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch1_flush_en : 1;  /* bit[0]   : wch1�Ĵ���ˢ��ʹ��
                                                        ��λֵ��0x0 */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_wch1_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_WCH1_FLUSH_EN_wch1_flush_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_UNION
 �ṹ˵��  : OV0_FLUSH_EN �Ĵ����ṹ���塣��ַƫ����:0x0128����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ģ��Ĵ���ˢ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov0_flush_en   : 1;  /* bit[0]   : ov0�Ĵ���ˢ��ʹ��
                                                         ��λֵ��0x0 */
        unsigned int  scf_flush_en   : 1;  /* bit[1]   : scf�Ĵ���ˢ��ʹ��
                                                         ��λֵ��0x0 */
        unsigned int  dbuf0_flush_en : 1;  /* bit[2]   : dbuf0�Ĵ���ˢ��ʹ��
                                                         ��λֵ��0x0 */
        unsigned int  itf0_flush_en  : 1;  /* bit[3]   : dpp_itf0�Ĵ���ˢ��ʹ��
                                                         ��λֵ��0x0 */
        unsigned int  reserved       : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_ov0_flush_en_START    (0)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_ov0_flush_en_END      (0)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_scf_flush_en_START    (1)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_scf_flush_en_END      (1)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_dbuf0_flush_en_START  (2)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_dbuf0_flush_en_END    (2)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_itf0_flush_en_START   (3)
#define SOC_DSS_MCTL_SYS_OV0_FLUSH_EN_itf0_flush_en_END     (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_UNION
 �ṹ˵��  : OV1_FLUSH_EN �Ĵ����ṹ���塣��ַƫ����:0x012C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ģ��Ĵ���ˢ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov1_flush_en   : 1;  /* bit[0]   : ov1�Ĵ���ˢ��ʹ��
                                                         ��λֵ��0x0 */
        unsigned int  reserved_0     : 1;  /* bit[1]   : ���� */
        unsigned int  dbuf1_flush_en : 1;  /* bit[2]   : dbuf1�Ĵ���ˢ��ʹ��
                                                         ��λֵ��0x0 */
        unsigned int  itf1_flush_en  : 1;  /* bit[3]   : itf1�Ĵ���ˢ��ʹ��
                                                         ��λֵ��0x0 */
        unsigned int  reserved_1     : 28; /* bit[4-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_ov1_flush_en_START    (0)
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_ov1_flush_en_END      (0)
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_dbuf1_flush_en_START  (2)
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_dbuf1_flush_en_END    (2)
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_itf1_flush_en_START   (3)
#define SOC_DSS_MCTL_SYS_OV1_FLUSH_EN_itf1_flush_en_END     (3)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_UNION
 �ṹ˵��  : OV2_FLUSH_EN �Ĵ����ṹ���塣��ַƫ����:0x0130����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ģ��Ĵ���ˢ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov2_flush_en : 1;  /* bit[0]   : ov2�Ĵ���ˢ��ʹ��
                                                       ��λֵ��0x0 */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_ov2_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_OV2_FLUSH_EN_ov2_flush_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_UNION
 �ṹ˵��  : OV3_FLUSH_EN �Ĵ����ṹ���塣��ַƫ����:0x0134����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ģ��Ĵ���ˢ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov3_flush_en : 1;  /* bit[0]   : ov3�Ĵ���ˢ��ʹ��
                                                       ��λֵ��0x0 */
        unsigned int  reserved     : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_ov3_flush_en_START  (0)
#define SOC_DSS_MCTL_SYS_OV3_FLUSH_EN_ov3_flush_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH0_OV_OEN_UNION
 �ṹ˵��  : RCH0_OV_OEN �Ĵ����ṹ���塣��ַƫ����:0x0160����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH��ӦOV��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch0_ov_oen : 12; /* bit[0-11] : rch0ͨ·���ѡ��
                                                       [7:0]��reserved
                                                       [8]��1'b1: OV0
                                                       [9]��1'b1: OV1
                                                       [10]��1'b1: OV2
                                                       [11]��1'b1: OV3
                                                       ��λֵ��0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH0_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH0_OV_OEN_rch0_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH0_OV_OEN_rch0_ov_oen_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH1_OV_OEN_UNION
 �ṹ˵��  : RCH1_OV_OEN �Ĵ����ṹ���塣��ַƫ����:0x0164����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH��ӦOV��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch1_ov_oen : 12; /* bit[0-11] : rch1ͨ·���ѡ��
                                                       [7:0]��reserved
                                                       [8]��1'b1: OV0
                                                       [9]��1'b1: OV1
                                                       [10]��1'b1: OV2
                                                       [11]��1'b1: OV3
                                                       ��λֵ��0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH1_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH1_OV_OEN_rch1_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH1_OV_OEN_rch1_ov_oen_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH2_OV_OEN_UNION
 �ṹ˵��  : RCH2_OV_OEN �Ĵ����ṹ���塣��ַƫ����:0x0168����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH��ӦOV��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch2_ov_oen : 12; /* bit[0-11] : rch2ͨ·���ѡ��
                                                       [7:0]��reserved
                                                       [8]��1'b1: OV0
                                                       [9]��1'b1: OV1
                                                       [10]��1'b1: OV2
                                                       [11]��1'b1: OV3
                                                       ��λֵ��0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH2_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH2_OV_OEN_rch2_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH2_OV_OEN_rch2_ov_oen_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH3_OV_OEN_UNION
 �ṹ˵��  : RCH3_OV_OEN �Ĵ����ṹ���塣��ַƫ����:0x016C����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH��ӦOV��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch3_ov_oen : 12; /* bit[0-11] : rch3ͨ·���ѡ��
                                                       [7:0]��reserved
                                                       [8]��1'b1: OV0
                                                       [9]��1'b1: OV1
                                                       [10]��1'b1: OV2
                                                       [11]��1'b1: OV3
                                                       ��λֵ��0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH3_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH3_OV_OEN_rch3_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH3_OV_OEN_rch3_ov_oen_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH4_OV_OEN_UNION
 �ṹ˵��  : RCH4_OV_OEN �Ĵ����ṹ���塣��ַƫ����:0x0170����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH��ӦOV��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch4_ov_oen : 12; /* bit[0-11] : rch4ͨ·���ѡ��
                                                       [7:0]��reserved
                                                       [8]��1'b1: OV0
                                                       [9]��1'b1: OV1
                                                       [10]��1'b1: OV2
                                                       [11]��1'b1: OV3
                                                       ��λֵ��0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH4_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH4_OV_OEN_rch4_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH4_OV_OEN_rch4_ov_oen_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH5_OV_OEN_UNION
 �ṹ˵��  : RCH5_OV_OEN �Ĵ����ṹ���塣��ַƫ����:0x0174����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH��ӦOV��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch5_ov_oen : 12; /* bit[0-11] : rch5ͨ·���ѡ��
                                                       [7:0]��reserved
                                                       [8]��1'b1: OV0
                                                       [9]��1'b1: OV1
                                                       [10]��1'b1: OV2
                                                       [11]��1'b1: OV3
                                                       ��λֵ��0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH5_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH5_OV_OEN_rch5_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH5_OV_OEN_rch5_ov_oen_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH6_OV_OEN_UNION
 �ṹ˵��  : RCH6_OV_OEN �Ĵ����ṹ���塣��ַƫ����:0x0178����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH��ӦOV��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch6_ov_oen : 12; /* bit[0-11] : rch6ͨ·���ѡ��
                                                       [7:0]��reserved
                                                       [8]��1'b1: OV0
                                                       [9]��1'b1: OV1
                                                       [10]��1'b1: OV2
                                                       [11]��1'b1: OV3
                                                       ��λֵ��0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH6_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH6_OV_OEN_rch6_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH6_OV_OEN_rch6_ov_oen_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH7_OV_OEN_UNION
 �ṹ˵��  : RCH7_OV_OEN �Ĵ����ṹ���塣��ַƫ����:0x017C����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH��ӦOV��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch7_ov_oen : 12; /* bit[0-11] : rch7ͨ·���ѡ��
                                                       [7:0]��reserved
                                                       [8]��1'b1: OV0
                                                       [9]��1'b1: OV1
                                                       [10]��1'b1: OV2
                                                       [11]��1'b1: OV3
                                                       ��λֵ��0x0 */
        unsigned int  reserved    : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH7_OV_OEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH7_OV_OEN_rch7_ov_oen_START  (0)
#define SOC_DSS_MCTL_SYS_RCH7_OV_OEN_rch7_ov_oen_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH_OV0_SEL_UNION
 �ṹ˵��  : RCH_OV0_SEL �Ĵ����ṹ���塣��ַƫ����:0x0180����ֵ:0x0FFFFFFF�����:32
 �Ĵ���˵��: RCH��ӦOV0��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch_ov0_sel : 28; /* bit[0-27] : ov0 layer����ѡ��
                                                       [27:24] layer5
                                                       [23:20] layer4
                                                       [19:16] layer3
                                                       [15:12] layer2
                                                       [11:8] layer1
                                                       [7:4] layer0
                                                       [3:0] base layerv
                                                       4'h0:rch0; 4'h1:rch1
                                                       4'h2:rch2; 4'h3:rch3
                                                       4'h4:rch4; 4'h5:rch5
                                                       4'h6:rch6; 4'h7:rch7
                                                       4'h8:pattern
                                                       other:reserved,no layer 
                                                       ��λֵ��0xFFFFFFF */
        unsigned int  reserved    : 4;  /* bit[28-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH_OV0_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH_OV0_SEL_rch_ov0_sel_START  (0)
#define SOC_DSS_MCTL_SYS_RCH_OV0_SEL_rch_ov0_sel_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH_OV1_SEL_UNION
 �ṹ˵��  : RCH_OV1_SEL �Ĵ����ṹ���塣��ַƫ����:0x0184����ֵ:0x00000FFF�����:32
 �Ĵ���˵��: RCH��ӦOV1��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch_ov1_sel : 12; /* bit[0-11] : ov1 layer����ѡ��
                                                       [11:8] layer1
                                                       [7:4] layer0
                                                       [3:0] base layerv
                                                       4'h0:rch0; 4'h1:rch1
                                                       4'h2:rch2; 4'h3:rch3
                                                       4'h4:rch4; 4'h5:rch5
                                                       4'h6:rch6; 4'h7:rch7
                                                       4'h8:pattern
                                                       other:reserved,no layer 
                                                       ��λֵ��0xFFF */
        unsigned int  reserved    : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH_OV1_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH_OV1_SEL_rch_ov1_sel_START  (0)
#define SOC_DSS_MCTL_SYS_RCH_OV1_SEL_rch_ov1_sel_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH_OV2_SEL_UNION
 �ṹ˵��  : RCH_OV2_SEL �Ĵ����ṹ���塣��ַƫ����:0x0188����ֵ:0x0FFFFFFF�����:32
 �Ĵ���˵��: RCH��ӦOV2��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch_ov2_sel : 28; /* bit[0-27] : ov2 layer����ѡ��
                                                       [27:24] layer5
                                                       [23:20] layer4
                                                       [19:16] layer3
                                                       [15:12] layer2
                                                       [11:8] layer1
                                                       [7:4] layer0
                                                       [3:0] base layerv
                                                       4'h0:rch0; 4'h1:rch1
                                                       4'h2:rch2; 4'h3:rch3
                                                       4'h4:rch4; 4'h5:rch5
                                                       4'h6:rch6; 4'h7:rch7
                                                       4'h8:pattern
                                                       other:reserved,no layer 
                                                       ��λֵ��0xFFFFFFF */
        unsigned int  reserved    : 4;  /* bit[28-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH_OV2_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH_OV2_SEL_rch_ov2_sel_START  (0)
#define SOC_DSS_MCTL_SYS_RCH_OV2_SEL_rch_ov2_sel_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH_OV3_SEL_UNION
 �ṹ˵��  : RCH_OV3_SEL �Ĵ����ṹ���塣��ַƫ����:0x018C����ֵ:0x00000FFF�����:32
 �Ĵ���˵��: RCH��ӦOV3��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch_ov3_sel : 12; /* bit[0-11] : ov3 layer����ѡ��
                                                       [11:8] layer1
                                                       [7:4] layer0
                                                       [3:0] base layer
                                                       4'h0:rch0; 4'h1:rch1
                                                       4'h2:rch2; 4'h3:rch3
                                                       4'h4:rch4; 4'h5:rch5
                                                       4'h6:rch6; 4'h7:rch7
                                                       4'h8:pattern
                                                       other:reserved,no layer 
                                                       ��λֵ��0xFFF */
        unsigned int  reserved    : 20; /* bit[12-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH_OV3_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH_OV3_SEL_rch_ov3_sel_START  (0)
#define SOC_DSS_MCTL_SYS_RCH_OV3_SEL_rch_ov3_sel_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_WCH0_OV_IEN_UNION
 �ṹ˵��  : WCH0_OV_IEN �Ĵ����ṹ���塣��ַƫ����:0x01A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH��ӦOV��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch0_ov_ien : 2;  /* bit[0-1] : wch0ͨ·����ѡ��
                                                      2'b01: OV2
                                                      2'b10: OV3
                                                      2'b00,2'b11:reserved
                                                      ��λֵ��0x0 */
        unsigned int  reserved    : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_WCH0_OV_IEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH0_OV_IEN_wch0_ov_ien_START  (0)
#define SOC_DSS_MCTL_SYS_WCH0_OV_IEN_wch0_ov_ien_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_WCH1_OV_IEN_UNION
 �ṹ˵��  : WCH1_OV_IEN �Ĵ����ṹ���塣��ַƫ����:0x01A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH��ӦOV��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch1_ov_ien : 2;  /* bit[0-1] : wch1ͨ·����ѡ��
                                                      2'b01: OV2
                                                      2'b10: OV3
                                                      2'b00,2'b11:reserved
                                                      ��λֵ��0x0 */
        unsigned int  reserved    : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_WCH1_OV_IEN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH1_OV_IEN_wch1_ov_ien_START  (0)
#define SOC_DSS_MCTL_SYS_WCH1_OV_IEN_wch1_ov_ien_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_WCH_OV2_SEL_UNION
 �ṹ˵��  : WCH_OV2_SEL �Ĵ����ṹ���塣��ַƫ����:0x01A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH��ӦOV��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch_ov2_sel : 2;  /* bit[0-1] : OV2ͨ·����ѡ��
                                                      2'b01: ѡ��wch0
                                                      2'b10: ѡ��wch1
                                                      2'b11: ѡ��wch0,wch1
                                                      2��b00��reserved
                                                      ��λֵ��0x0 */
        unsigned int  reserved    : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_WCH_OV2_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH_OV2_SEL_wch_ov2_sel_START  (0)
#define SOC_DSS_MCTL_SYS_WCH_OV2_SEL_wch_ov2_sel_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_WCH_OV3_SEL_UNION
 �ṹ˵��  : WCH_OV3_SEL �Ĵ����ṹ���塣��ַƫ����:0x01AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH��ӦOV��layerѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch_ov3_sel : 2;  /* bit[0-1] : OV3ͨ·����ѡ��
                                                      2'b01: ѡ��wch0
                                                      2'b10: ѡ��wch1
                                                      2'b11: ѡ��wch0,wch1
                                                      2��b00��reserved
                                                      ��λֵ��0x0 */
        unsigned int  reserved    : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_WCH_OV3_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WCH_OV3_SEL_wch_ov3_sel_START  (0)
#define SOC_DSS_MCTL_SYS_WCH_OV3_SEL_wch_ov3_sel_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_WB_ENC_SEL_UNION
 �ṹ˵��  : WB_ENC_SEL �Ĵ����ṹ���塣��ַƫ����:0x01B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ENC��wchѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wb_enc_sel : 2;  /* bit[0-1] : ѡ�������enc�Ļ�дͨ·
                                                     2'b01:ѡ��wch0��Ϊ�����encoder�Ļ�дͨ·
                                                     2'b10:ѡ��wch1��Ϊ�����encoder�Ļ�дͨ·
                                                     2'b11,2'b00: �������encoder�Ļ�дͨ·
                                                     ��λֵ2'b00 */
        unsigned int  reserved   : 30; /* bit[2-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_WB_ENC_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_WB_ENC_SEL_wb_enc_sel_START  (0)
#define SOC_DSS_MCTL_SYS_WB_ENC_SEL_wb_enc_sel_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_DSI_MUX_SEL_UNION
 �ṹ˵��  : DSI_MUX_SEL �Ĵ����ṹ���塣��ַƫ����:0x01B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: DSI_MUXѡ��Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dsi_mux_sel : 1;  /* bit[0]   : DSI_MUX����ѡ��Ĵ���
                                                      1'b0 : ѡ��LDI0 DPI1 ��DSI1���
                                                      1'b1 : ѡ��LDI1 DPI0 ��DSI1��� */
        unsigned int  reserved    : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_DSI_MUX_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_DSI_MUX_SEL_dsi_mux_sel_START  (0)
#define SOC_DSS_MCTL_SYS_DSI_MUX_SEL_dsi_mux_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH0_STARTY_UNION
 �ṹ˵��  : RCH0_STARTY �Ĵ����ṹ���塣��ַƫ����:0x01C0����ֵ:0x00080000�����:32
 �Ĵ���˵��: RCH��ӦY����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch0_starty : 15; /* bit[0-14] : RCH��Ӧ��ͼ����ʼy���� */
        unsigned int  reserved_0  : 1;  /* bit[15]   : ���� */
        unsigned int  rch0_thld   : 15; /* bit[16-30]: Ԥ����������ֵ */
        unsigned int  reserved_1  : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH0_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH0_STARTY_rch0_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH0_STARTY_rch0_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH0_STARTY_rch0_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH0_STARTY_rch0_thld_END      (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH1_STARTY_UNION
 �ṹ˵��  : RCH1_STARTY �Ĵ����ṹ���塣��ַƫ����:0x01C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH��ӦY����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch1_starty : 15; /* bit[0-14] : RCH��Ӧ��ͼ����ʼy���� */
        unsigned int  reserved_0  : 1;  /* bit[15]   : ���� */
        unsigned int  rch1_thld   : 15; /* bit[16-30]: Ԥ����������ֵ */
        unsigned int  reserved_1  : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH1_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH1_STARTY_rch1_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH1_STARTY_rch1_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH1_STARTY_rch1_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH1_STARTY_rch1_thld_END      (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH2_STARTY_UNION
 �ṹ˵��  : RCH2_STARTY �Ĵ����ṹ���塣��ַƫ����:0x01C8����ֵ:0x000C0000�����:32
 �Ĵ���˵��: RCH��ӦY����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch2_starty : 15; /* bit[0-14] : RCH��Ӧ��ͼ����ʼy���� */
        unsigned int  reserved_0  : 1;  /* bit[15]   : ���� */
        unsigned int  rch2_thld   : 15; /* bit[16-30]: Ԥ����������ֵ */
        unsigned int  reserved_1  : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH2_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH2_STARTY_rch2_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH2_STARTY_rch2_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH2_STARTY_rch2_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH2_STARTY_rch2_thld_END      (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH3_STARTY_UNION
 �ṹ˵��  : RCH3_STARTY �Ĵ����ṹ���塣��ַƫ����:0x01CC����ֵ:0x00090000�����:32
 �Ĵ���˵��: RCH��ӦY����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch3_starty : 15; /* bit[0-14] : RCH��Ӧ��ͼ����ʼy���� */
        unsigned int  reserved_0  : 1;  /* bit[15]   : ���� */
        unsigned int  rch3_thld   : 15; /* bit[16-30]: Ԥ����������ֵ */
        unsigned int  reserved_1  : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH3_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH3_STARTY_rch3_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH3_STARTY_rch3_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH3_STARTY_rch3_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH3_STARTY_rch3_thld_END      (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH4_STARTY_UNION
 �ṹ˵��  : RCH4_STARTY �Ĵ����ṹ���塣��ַƫ����:0x01D0����ֵ:0x000A0000�����:32
 �Ĵ���˵��: RCH��ӦY����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch4_starty : 15; /* bit[0-14] : RCH��Ӧ��ͼ����ʼy���� */
        unsigned int  reserved_0  : 1;  /* bit[15]   : ���� */
        unsigned int  rch4_thld   : 15; /* bit[16-30]: Ԥ����������ֵ */
        unsigned int  reserved_1  : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH4_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH4_STARTY_rch4_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH4_STARTY_rch4_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH4_STARTY_rch4_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH4_STARTY_rch4_thld_END      (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH5_STARTY_UNION
 �ṹ˵��  : RCH5_STARTY �Ĵ����ṹ���塣��ַƫ����:0x01D4����ֵ:0x00090000�����:32
 �Ĵ���˵��: RCH��ӦY����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch5_starty : 15; /* bit[0-14] : RCH��Ӧ��ͼ����ʼy���� */
        unsigned int  reserved_0  : 1;  /* bit[15]   : ���� */
        unsigned int  rch5_thld   : 15; /* bit[16-30]: Ԥ����������ֵ */
        unsigned int  reserved_1  : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH5_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH5_STARTY_rch5_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH5_STARTY_rch5_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH5_STARTY_rch5_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH5_STARTY_rch5_thld_END      (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH6_STARTY_UNION
 �ṹ˵��  : RCH6_STARTY �Ĵ����ṹ���塣��ַƫ����:0x01D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH��ӦY����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch6_starty : 15; /* bit[0-14] : RCH��Ӧ��ͼ����ʼy���� */
        unsigned int  reserved_0  : 1;  /* bit[15]   : ���� */
        unsigned int  rch6_thld   : 15; /* bit[16-30]: Ԥ����������ֵ */
        unsigned int  reserved_1  : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH6_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH6_STARTY_rch6_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH6_STARTY_rch6_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH6_STARTY_rch6_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH6_STARTY_rch6_thld_END      (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_RCH7_STARTY_UNION
 �ṹ˵��  : RCH7_STARTY �Ĵ����ṹ���塣��ַƫ����:0x01DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: RCH��ӦY����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch7_starty : 15; /* bit[0-14] : RCH��Ӧ��ͼ����ʼy���� */
        unsigned int  reserved_0  : 1;  /* bit[15]   : ���� */
        unsigned int  rch7_thld   : 15; /* bit[16-30]: Ԥ����������ֵ */
        unsigned int  reserved_1  : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_MCTL_SYS_RCH7_STARTY_UNION;
#endif
#define SOC_DSS_MCTL_SYS_RCH7_STARTY_rch7_starty_START  (0)
#define SOC_DSS_MCTL_SYS_RCH7_STARTY_rch7_starty_END    (14)
#define SOC_DSS_MCTL_SYS_RCH7_STARTY_rch7_thld_START    (16)
#define SOC_DSS_MCTL_SYS_RCH7_STARTY_rch7_thld_END      (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_UNION
 �ṹ˵��  : MCTL_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x01F0����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mctl_clk_sel : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                       1����ʾǿ�ƴ�ʱ�ӡ�
                                                       0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ��
                                                       [7:0]������ctl_mutex0~7��
                                                       [30:8]��reserved
                                                       [31]������apb�� */
    } reg;
} SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_mctl_clk_sel_START  (0)
#define SOC_DSS_MCTL_SYS_MCTL_CLK_SEL_mctl_clk_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MCTL_CLK_EN_UNION
 �ṹ˵��  : MCTL_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x01F4����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mctl_clk_en : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                      1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                      0����ʾ���ʱ��ʹ����Ч����ֹӲ������
                                                      [7:0]������mctl_mutex0~7��
                                                      [31:8]��reserved */
    } reg;
} SOC_DSS_MCTL_SYS_MCTL_CLK_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MCTL_CLK_EN_mctl_clk_en_START  (0)
#define SOC_DSS_MCTL_SYS_MCTL_CLK_EN_mctl_clk_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD_CLK_SEL_UNION
 �ṹ˵��  : MOD_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x01F8����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mod_clk_sel : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                      1����ʾǿ�ƴ�ʱ�ӡ�
                                                      0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ��
                                                      [7:0] rch0~7
                                                      [9:8] wch0~1
                                                      [13:10] ov0~3
                                                      [14] scf
                                                      [16:15] dbuf0~1
                                                      [18:17] itf0~1
                                                      [31:19] reserved */
    } reg;
} SOC_DSS_MCTL_SYS_MOD_CLK_SEL_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD_CLK_SEL_mod_clk_sel_START  (0)
#define SOC_DSS_MCTL_SYS_MOD_CLK_SEL_mod_clk_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD_CLK_EN_UNION
 �ṹ˵��  : MOD_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x01FC����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mod_clk_en : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                     1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                     0����ʾ���ʱ��ʹ����Ч����ֹӲ������
                                                     [7:0] rch0~7
                                                     [9:8] wch0~1
                                                     [13:10] ov0~3
                                                     [14] scf
                                                     [16:15] dbuf0~1
                                                     [18:17] itf0~1
                                                     [31:19] reserved */
    } reg;
} SOC_DSS_MCTL_SYS_MOD_CLK_EN_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD_CLK_EN_mod_clk_en_START  (0)
#define SOC_DSS_MCTL_SYS_MOD_CLK_EN_mod_clk_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD0_DBG_UNION
 �ṹ˵��  : MOD0_DBG �Ĵ����ṹ���塣��ַƫ����:0x0200����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch0_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD0_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD0_DBG_rch0_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD0_DBG_rch0_dbg_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD1_DBG_UNION
 �ṹ˵��  : MOD1_DBG �Ĵ����ṹ���塣��ַƫ����:0x0204����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch1_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD1_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD1_DBG_rch1_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD1_DBG_rch1_dbg_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD2_DBG_UNION
 �ṹ˵��  : MOD2_DBG �Ĵ����ṹ���塣��ַƫ����:0x0208����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch2_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD2_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD2_DBG_rch2_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD2_DBG_rch2_dbg_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD3_DBG_UNION
 �ṹ˵��  : MOD3_DBG �Ĵ����ṹ���塣��ַƫ����:0x020C����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch3_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD3_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD3_DBG_rch3_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD3_DBG_rch3_dbg_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD4_DBG_UNION
 �ṹ˵��  : MOD4_DBG �Ĵ����ṹ���塣��ַƫ����:0x0210����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch4_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD4_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD4_DBG_rch4_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD4_DBG_rch4_dbg_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD5_DBG_UNION
 �ṹ˵��  : MOD5_DBG �Ĵ����ṹ���塣��ַƫ����:0x0214����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch5_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD5_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD5_DBG_rch5_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD5_DBG_rch5_dbg_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD6_DBG_UNION
 �ṹ˵��  : MOD6_DBG �Ĵ����ṹ���塣��ַƫ����:0x0218����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch6_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD6_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD6_DBG_rch6_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD6_DBG_rch6_dbg_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD7_DBG_UNION
 �ṹ˵��  : MOD7_DBG �Ĵ����ṹ���塣��ַƫ����:0x021C����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch7_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD7_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD7_DBG_rch7_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD7_DBG_rch7_dbg_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD8_DBG_UNION
 �ṹ˵��  : MOD8_DBG �Ĵ����ṹ���塣��ַƫ����:0x0220����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch0_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD8_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD8_DBG_wch0_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD8_DBG_wch0_dbg_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD9_DBG_UNION
 �ṹ˵��  : MOD9_DBG �Ĵ����ṹ���塣��ַƫ����:0x0224����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch1_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD9_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD9_DBG_wch1_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD9_DBG_wch1_dbg_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD10_DBG_UNION
 �ṹ˵��  : MOD10_DBG �Ĵ����ṹ���塣��ַƫ����:0x0228����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov0_dbg  : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD10_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD10_DBG_ov0_dbg_START   (0)
#define SOC_DSS_MCTL_SYS_MOD10_DBG_ov0_dbg_END     (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD11_DBG_UNION
 �ṹ˵��  : MOD11_DBG �Ĵ����ṹ���塣��ַƫ����:0x022C����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov1_dbg  : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD11_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD11_DBG_ov1_dbg_START   (0)
#define SOC_DSS_MCTL_SYS_MOD11_DBG_ov1_dbg_END     (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD12_DBG_UNION
 �ṹ˵��  : MOD12_DBG �Ĵ����ṹ���塣��ַƫ����:0x0230����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov2_dbg  : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD12_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD12_DBG_ov2_dbg_START   (0)
#define SOC_DSS_MCTL_SYS_MOD12_DBG_ov2_dbg_END     (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD13_DBG_UNION
 �ṹ˵��  : MOD13_DBG �Ĵ����ṹ���塣��ַƫ����:0x0234����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov3_dbg  : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD13_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD13_DBG_ov3_dbg_START   (0)
#define SOC_DSS_MCTL_SYS_MOD13_DBG_ov3_dbg_END     (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD14_DBG_UNION
 �ṹ˵��  : MOD14_DBG �Ĵ����ṹ���塣��ַƫ����:0x0238����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_dbg  : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD14_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD14_DBG_scf_dbg_START   (0)
#define SOC_DSS_MCTL_SYS_MOD14_DBG_scf_dbg_END     (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD15_DBG_UNION
 �ṹ˵��  : MOD15_DBG �Ĵ����ṹ���塣��ַƫ����:0x023C����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf0_dbg : 24; /* bit[0-23] : [23:22] 
                                                     2'b11 ������ã���mod ����clear
                                                     2'b10 ������ã���mod����clear
                                                     2'b0* Ӳ���Զ���ctl��clear
                                                     [21:20] 
                                                     2'b11 ������ã�ǿ�ƻָ�idle̬
                                                     2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                     2'b0* Ӳ���ж��Ƿ�idle̬
                                                     [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                     [17:16] mod end�ź���ʱ����
                                                     [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                     [7] ����starty
                                                     [6��5] reserved
                                                     [4]no flush_en press:
                                                     1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                     1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                     [3] �����¼������dbg��reload״̬�����mod_status����
                                                     [2] �����¼������dbgstart״̬�����mod_status����
                                                     [1] no start
                                                     1'b1:������reload����start����
                                                     ���ú�������Ч
                                                     [0] bypass starty */
        unsigned int  reserved  : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD15_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD15_DBG_dbuf0_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD15_DBG_dbuf0_dbg_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD16_DBG_UNION
 �ṹ˵��  : MOD16_DBG �Ĵ����ṹ���塣��ַƫ����:0x0240����ֵ:0x00020000�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf1_dbg : 24; /* bit[0-23] : [23:22] 
                                                     2'b11 ������ã���mod ����clear
                                                     2'b10 ������ã���mod����clear
                                                     2'b0* Ӳ���Զ���ctl��clear
                                                     [21:20] 
                                                     2'b11 ������ã�ǿ�ƻָ�idle̬
                                                     2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                     2'b0* Ӳ���ж��Ƿ�idle̬
                                                     [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                     [17:16] mod end�ź���ʱ����
                                                     [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                     [7] ����starty
                                                     [6��5] reserved
                                                     [4]no flush_en press:
                                                     1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                     1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                     [3] �����¼������dbg��reload״̬�����mod_status����
                                                     [2] �����¼������dbgstart״̬�����mod_status����
                                                     [1] no start
                                                     1'b1:������reload����start����
                                                     ���ú�������Ч
                                                     [0] bypass starty */
        unsigned int  reserved  : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD16_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD16_DBG_dbuf1_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD16_DBG_dbuf1_dbg_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD17_DBG_UNION
 �ṹ˵��  : MOD17_DBG �Ĵ����ṹ���塣��ַƫ����:0x0244����ֵ:0x00020F00�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itf0_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD17_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD17_DBG_itf0_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD17_DBG_itf0_dbg_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD18_DBG_UNION
 �ṹ˵��  : MOD18_DBG �Ĵ����ṹ���塣��ַƫ����:0x0248����ֵ:0x00020F00�����:32
 �Ĵ���˵��: module��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itf1_dbg : 24; /* bit[0-23] : [23:22] 
                                                    2'b11 ������ã���mod ����clear
                                                    2'b10 ������ã���mod����clear
                                                    2'b0* Ӳ���Զ���ctl��clear
                                                    [21:20] 
                                                    2'b11 ������ã�ǿ�ƻָ�idle̬
                                                    2'b10 ������ã�����ǿ�ƻָ�idle̬
                                                    2'b0* Ӳ���ж��Ƿ�idle̬
                                                    [19] 1'b1 �����ǰ�Ѿ����õ�flush_en��cpuģʽ��Ҫ���ã�cmdlistģʽ��Ҫ���ã�
                                                    [17:16] mod end�ź���ʱ����
                                                    [15:8]ctl_st_idly ����ģ�����start״̬����Ҫ�ӳٵ�ʱ��
                                                    [7] ����starty
                                                    [6��5] reserved
                                                    [4]no flush_en press:
                                                    1'b1:module flush_en��֧�ָ���ov ycnt�Զ���ѹ
                                                    1'b0:module flush_en֧�ָ���ov ycnt�Զ���ѹ
                                                    [3] �����¼������dbg��reload״̬�����mod_status����
                                                    [2] �����¼������dbgstart״̬�����mod_status����
                                                    [1] no start
                                                    1'b1:������reload����start����
                                                    ���ú�������Ч
                                                    [0] bypass starty */
        unsigned int  reserved : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD18_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD18_DBG_itf1_dbg_START  (0)
#define SOC_DSS_MCTL_SYS_MOD18_DBG_itf1_dbg_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD0_STATUS_UNION
 �ṹ˵��  : MOD0_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0250����ֵ:0x00000016�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch0_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD0_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD0_STATUS_rch0_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD0_STATUS_rch0_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD1_STATUS_UNION
 �ṹ˵��  : MOD1_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0254����ֵ:0x00000016�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch1_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD1_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD1_STATUS_rch1_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD1_STATUS_rch1_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD2_STATUS_UNION
 �ṹ˵��  : MOD2_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0258����ֵ:0x00000016�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch2_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD2_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD2_STATUS_rch2_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD2_STATUS_rch2_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD3_STATUS_UNION
 �ṹ˵��  : MOD3_STATUS �Ĵ����ṹ���塣��ַƫ����:0x025C����ֵ:0x00000016�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch3_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD3_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD3_STATUS_rch3_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD3_STATUS_rch3_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD4_STATUS_UNION
 �ṹ˵��  : MOD4_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0260����ֵ:0x00000016�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch4_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD4_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD4_STATUS_rch4_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD4_STATUS_rch4_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD5_STATUS_UNION
 �ṹ˵��  : MOD5_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0264����ֵ:0x00000016�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch5_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD5_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD5_STATUS_rch5_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD5_STATUS_rch5_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD6_STATUS_UNION
 �ṹ˵��  : MOD6_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0268����ֵ:0x00000016�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch6_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD6_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD6_STATUS_rch6_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD6_STATUS_rch6_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD7_STATUS_UNION
 �ṹ˵��  : MOD7_STATUS �Ĵ����ṹ���塣��ַƫ����:0x026C����ֵ:0x00000016�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rch7_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD7_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD7_STATUS_rch7_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD7_STATUS_rch7_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD8_STATUS_UNION
 �ṹ˵��  : MOD8_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0270����ֵ:0x00000016�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch0_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD8_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD8_STATUS_wch0_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD8_STATUS_wch0_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD9_STATUS_UNION
 �ṹ˵��  : MOD9_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0274����ֵ:0x00000016�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  wch1_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD9_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD9_STATUS_wch1_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD9_STATUS_wch1_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD10_STATUS_UNION
 �ṹ˵��  : MOD10_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0278����ֵ:0x00000036�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov1_status : 6;  /* bit[0-5] : [0] reload status
                                                     [1] flush status
                                                     [2] activey
                                                     [3] start status
                                                     [4] idle
                                                     [5] clear ack */
        unsigned int  reserved   : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD10_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD10_STATUS_ov1_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD10_STATUS_ov1_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD11_STATUS_UNION
 �ṹ˵��  : MOD11_STATUS �Ĵ����ṹ���塣��ַƫ����:0x027C����ֵ:0x00000036�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov2_status : 6;  /* bit[0-5] : [0] reload status
                                                     [1] flush status
                                                     [2] activey
                                                     [3] start status
                                                     [4] idle
                                                     [5] clear ack */
        unsigned int  reserved   : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD11_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD11_STATUS_ov2_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD11_STATUS_ov2_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD12_STATUS_UNION
 �ṹ˵��  : MOD12_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0280����ֵ:0x00000036�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov3_status : 6;  /* bit[0-5] : [0] reload status
                                                     [1] flush status
                                                     [2] activey
                                                     [3] start status
                                                     [4] idle
                                                     [5] clear ack */
        unsigned int  reserved   : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD12_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD12_STATUS_ov3_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD12_STATUS_ov3_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD13_STATUS_UNION
 �ṹ˵��  : MOD13_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0284����ֵ:0x00000036�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scf_status : 6;  /* bit[0-5] : [0] reload status
                                                     [1] flush status
                                                     [2] activey
                                                     [3] start status
                                                     [4] idle
                                                     [5] clear ack */
        unsigned int  reserved   : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD13_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD13_STATUS_scf_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD13_STATUS_scf_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD14_STATUS_UNION
 �ṹ˵��  : MOD14_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0288����ֵ:0x00000036�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov0_status : 6;  /* bit[0-5] : [0] reload status
                                                     [1] flush status
                                                     [2] activey
                                                     [3] start status
                                                     [4] idle
                                                     [5] clear ack */
        unsigned int  reserved   : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD14_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD14_STATUS_ov0_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD14_STATUS_ov0_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD15_STATUS_UNION
 �ṹ˵��  : MOD15_STATUS �Ĵ����ṹ���塣��ַƫ����:0x028C����ֵ:0x00000036�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf0_status : 6;  /* bit[0-5] : [0] reload status
                                                       [1] flush status
                                                       [2] activey
                                                       [3] start status
                                                       [4] idle
                                                       [5] clear ack */
        unsigned int  reserved     : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD15_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD15_STATUS_dbuf0_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD15_STATUS_dbuf0_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD16_STATUS_UNION
 �ṹ˵��  : MOD16_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0290����ֵ:0x00000036�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbuf1_status : 6;  /* bit[0-5] : [0] reload status
                                                       [1] flush status
                                                       [2] activey
                                                       [3] start status
                                                       [4] idle
                                                       [5] clear ack */
        unsigned int  reserved     : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD16_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD16_STATUS_dbuf1_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD16_STATUS_dbuf1_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD17_STATUS_UNION
 �ṹ˵��  : MOD17_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0294����ֵ:0x00000036�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itf0_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD17_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD17_STATUS_itf0_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD17_STATUS_itf0_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_MOD18_STATUS_UNION
 �ṹ˵��  : MOD18_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0298����ֵ:0x00000036�����:32
 �Ĵ���˵��: module״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  itf1_status : 6;  /* bit[0-5] : [0] reload status
                                                      [1] flush status
                                                      [2] activey
                                                      [3] start status
                                                      [4] idle
                                                      [5] clear ack */
        unsigned int  reserved    : 26; /* bit[6-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_MOD18_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_MOD18_STATUS_itf1_status_START  (0)
#define SOC_DSS_MCTL_SYS_MOD18_STATUS_itf1_status_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_SW_DBG_UNION
 �ṹ˵��  : SW_DBG �Ĵ����ṹ���塣��ַƫ����:0x02B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW��ν�ɲ�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw_dbg   : 16; /* bit[0-15] : [0]:apb_secu_enʹ�ܣ�Ϊ1��ʾ��ȫ���ã�Ϊ0��ʾ�ǰ�ȫ����
                                                    [15:1]:reserved�� */
        unsigned int  reserved : 16; /* bit[16-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_SW_DBG_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW_DBG_sw_dbg_START    (0)
#define SOC_DSS_MCTL_SYS_SW_DBG_sw_dbg_END      (15)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_SW0_STATUS0_UNION
 �ṹ˵��  : SW0_STATUS0 �Ĵ����ṹ���塣��ַƫ����:0x02B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW0״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status0 : 32; /* bit[0-31]: sw0�˿�rch output enable״̬
                                                      [7] rch7_oen
                                                      [6] rch6_oen
                                                      [5] rch5_oen
                                                      [4] rch4_oen
                                                      [3] rch3_oen
                                                      [2] rch2_oen
                                                      [1] rch1_oen
                                                      [0] rch0_oen */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS0_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS0_sw0_status0_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS0_sw0_status0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_SW0_STATUS1_UNION
 �ṹ˵��  : SW0_STATUS1 �Ĵ����ṹ���塣��ַƫ����:0x02B8����ֵ:0x0FFFFFFF�����:32
 �Ĵ���˵��: SW0״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status1 : 32; /* bit[0-31]: sw0�˿�overlay select״̬
                                                      [27:0]ov_sel */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS1_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS1_sw0_status1_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS1_sw0_status1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_SW0_STATUS2_UNION
 �ṹ˵��  : SW0_STATUS2 �Ĵ����ṹ���塣��ַƫ����:0x02BC����ֵ:0x00000FFF�����:32
 �Ĵ���˵��: SW0״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status2 : 32; /* bit[0-31]: sw0�˿�overlay select״̬
                                                      [11:0]ov_sel */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS2_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS2_sw0_status2_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS2_sw0_status2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_SW0_STATUS3_UNION
 �ṹ˵��  : SW0_STATUS3 �Ĵ����ṹ���塣��ַƫ����:0x02C0����ֵ:0x0FFFFFFF�����:32
 �Ĵ���˵��: SW0״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status3 : 32; /* bit[0-31]: sw0�˿�overlay select״̬
                                                      [27:0]ov_sel */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS3_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS3_sw0_status3_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS3_sw0_status3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_SW0_STATUS4_UNION
 �ṹ˵��  : SW0_STATUS4 �Ĵ����ṹ���塣��ַƫ����:0x02C4����ֵ:0x00000FFF�����:32
 �Ĵ���˵��: SW0״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status4 : 32; /* bit[0-31]: sw0�˿�overlay select״̬
                                                      [11:0]ov_sel */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS4_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS4_sw0_status4_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS4_sw0_status4_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_SW0_STATUS5_UNION
 �ṹ˵��  : SW0_STATUS5 �Ĵ����ṹ���塣��ַƫ����:0x02C8����ֵ:0x0007C000�����:32
 �Ĵ���˵��: SW0״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status5 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS5_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS5_sw0_status5_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS5_sw0_status5_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_SW0_STATUS6_UNION
 �ṹ˵��  : SW0_STATUS6 �Ĵ����ṹ���塣��ַƫ����:0x02D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW0״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status6 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS6_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS6_sw0_status6_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS6_sw0_status6_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_SW0_STATUS7_UNION
 �ṹ˵��  : SW0_STATUS7 �Ĵ����ṹ���塣��ַƫ����:0x02D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW0״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw0_status7 : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_MCTL_SYS_SW0_STATUS7_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW0_STATUS7_sw0_status7_START  (0)
#define SOC_DSS_MCTL_SYS_SW0_STATUS7_sw0_status7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_MCTL_SYS_SW1_STATUS_UNION
 �ṹ˵��  : SW1_STATUS �Ĵ����ṹ���塣��ַƫ����:0x02D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: SW1״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw1_status : 8;  /* bit[0-7] : [7:6] wch0_ien
                                                     [5:4] wch1_ien
                                                     [3:2] ov2_wchѡ��״̬
                                                     [1:0] ov3_wchѡ��״̬ */
        unsigned int  reserved   : 24; /* bit[8-31]: ���� */
    } reg;
} SOC_DSS_MCTL_SYS_SW1_STATUS_UNION;
#endif
#define SOC_DSS_MCTL_SYS_SW1_STATUS_sw1_status_START  (0)
#define SOC_DSS_MCTL_SYS_SW1_STATUS_sw1_status_END    (7)






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

#endif /* end of soc_dss_mctl_sys_interface.h */
