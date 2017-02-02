/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_dss_ov6_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:20:15
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_DSS_OV6.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_DSS_OV6_INTERFACE_H__
#define __SOC_DSS_OV6_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_OV6
 ****************************************************************************/
/* �Ĵ���˵����overlayͼ���С
   λ����UNION�ṹ:  SOC_DSS_OV6_OV_SIZE_UNION */
#define SOC_DSS_OV6_OV_SIZE_ADDR(base)                ((base) + (0x0000))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_OV_BG_COLOR_UNION */
#define SOC_DSS_OV6_OV_BG_COLOR_ADDR(base)            ((base) + (0x4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_DST_STARTPOS_UNION */
#define SOC_DSS_OV6_DST_STARTPOS_ADDR(base)           ((base) + (0x8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_DST_ENDPOS_UNION */
#define SOC_DSS_OV6_DST_ENDPOS_ADDR(base)             ((base) + (0xC))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_OV_GCFG_UNION */
#define SOC_DSS_OV6_OV_GCFG_ADDR(base)                ((base) + (0x10))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER0_POS_UNION */
#define SOC_DSS_OV6_LAYER0_POS_ADDR(base)             ((base) + (0x14))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER0_SIZE_UNION */
#define SOC_DSS_OV6_LAYER0_SIZE_ADDR(base)            ((base) + (0x18))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER0_SRCLOKEY_UNION */
#define SOC_DSS_OV6_LAYER0_SRCLOKEY_ADDR(base)        ((base) + (0x1C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER0_SRCHIKEY_UNION */
#define SOC_DSS_OV6_LAYER0_SRCHIKEY_ADDR(base)        ((base) + (0x20))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER0_DSTLOKEY_UNION */
#define SOC_DSS_OV6_LAYER0_DSTLOKEY_ADDR(base)        ((base) + (0x24))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER0_DSTHIKEY_UNION */
#define SOC_DSS_OV6_LAYER0_DSTHIKEY_ADDR(base)        ((base) + (0x28))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER0_PATTERN_UNION */
#define SOC_DSS_OV6_LAYER0_PATTERN_ADDR(base)         ((base) + (0x2C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER0_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER0_ALPHA_ADDR(base)           ((base) + (0x30))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER0_CFG_UNION */
#define SOC_DSS_OV6_LAYER0_CFG_ADDR(base)             ((base) + (0x34))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER0_PSPOS_UNION */
#define SOC_DSS_OV6_LAYER0_PSPOS_ADDR(base)           ((base) + (0x38))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER0_PEPOS_UNION */
#define SOC_DSS_OV6_LAYER0_PEPOS_ADDR(base)           ((base) + (0x3C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER0_INFO_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_ADDR(base)      ((base) + (0x40))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_UNION */
#define SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_ADDR(base)   ((base) + (0x44))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER0_ST_INFO_UNION */
#define SOC_DSS_OV6_LAYER0_ST_INFO_ADDR(base)         ((base) + (0x48))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER0_IST_INFO_UNION */
#define SOC_DSS_OV6_LAYER0_IST_INFO_ADDR(base)        ((base) + (0x4C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER1_POS_UNION */
#define SOC_DSS_OV6_LAYER1_POS_ADDR(base)             ((base) + (0x50))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER1_SIZE_UNION */
#define SOC_DSS_OV6_LAYER1_SIZE_ADDR(base)            ((base) + (0x54))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER1_SRCLOKEY_UNION */
#define SOC_DSS_OV6_LAYER1_SRCLOKEY_ADDR(base)        ((base) + (0x58))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER1_SRCHIKEY_UNION */
#define SOC_DSS_OV6_LAYER1_SRCHIKEY_ADDR(base)        ((base) + (0x5C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER1_DSTLOKEY_UNION */
#define SOC_DSS_OV6_LAYER1_DSTLOKEY_ADDR(base)        ((base) + (0x60))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER1_DSTHIKEY_UNION */
#define SOC_DSS_OV6_LAYER1_DSTHIKEY_ADDR(base)        ((base) + (0x64))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER1_PATTERN_UNION */
#define SOC_DSS_OV6_LAYER1_PATTERN_ADDR(base)         ((base) + (0x68))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER1_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER1_ALPHA_ADDR(base)           ((base) + (0x6C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER1_CFG_UNION */
#define SOC_DSS_OV6_LAYER1_CFG_ADDR(base)             ((base) + (0x70))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER1_PSPOS_UNION */
#define SOC_DSS_OV6_LAYER1_PSPOS_ADDR(base)           ((base) + (0x74))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER1_PEPOS_UNION */
#define SOC_DSS_OV6_LAYER1_PEPOS_ADDR(base)           ((base) + (0x78))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER1_INFO_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_ADDR(base)      ((base) + (0x7C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_UNION */
#define SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_ADDR(base)   ((base) + (0x80))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER1_ST_INFO_UNION */
#define SOC_DSS_OV6_LAYER1_ST_INFO_ADDR(base)         ((base) + (0x84))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER1_IST_INFO_UNION */
#define SOC_DSS_OV6_LAYER1_IST_INFO_ADDR(base)        ((base) + (0x88))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER2_POS_UNION */
#define SOC_DSS_OV6_LAYER2_POS_ADDR(base)             ((base) + (0x8C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER2_SIZE_UNION */
#define SOC_DSS_OV6_LAYER2_SIZE_ADDR(base)            ((base) + (0x90))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER2_SRCLOKEY_UNION */
#define SOC_DSS_OV6_LAYER2_SRCLOKEY_ADDR(base)        ((base) + (0x94))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER2_SRCHIKEY_UNION */
#define SOC_DSS_OV6_LAYER2_SRCHIKEY_ADDR(base)        ((base) + (0x98))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER2_DSTLOKEY_UNION */
#define SOC_DSS_OV6_LAYER2_DSTLOKEY_ADDR(base)        ((base) + (0x9C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER2_DSTHIKEY_UNION */
#define SOC_DSS_OV6_LAYER2_DSTHIKEY_ADDR(base)        ((base) + (0xA0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER2_PATTERN_UNION */
#define SOC_DSS_OV6_LAYER2_PATTERN_ADDR(base)         ((base) + (0xA4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER2_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER2_ALPHA_ADDR(base)           ((base) + (0xA8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER2_CFG_UNION */
#define SOC_DSS_OV6_LAYER2_CFG_ADDR(base)             ((base) + (0xAC))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER2_PSPOS_UNION */
#define SOC_DSS_OV6_LAYER2_PSPOS_ADDR(base)           ((base) + (0xB0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER2_PEPOS_UNION */
#define SOC_DSS_OV6_LAYER2_PEPOS_ADDR(base)           ((base) + (0xB4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER2_INFO_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_ADDR(base)      ((base) + (0xB8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_UNION */
#define SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_ADDR(base)   ((base) + (0xBC))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER2_ST_INFO_UNION */
#define SOC_DSS_OV6_LAYER2_ST_INFO_ADDR(base)         ((base) + (0xC0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER2_IST_INFO_UNION */
#define SOC_DSS_OV6_LAYER2_IST_INFO_ADDR(base)        ((base) + (0xC4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER3_POS_UNION */
#define SOC_DSS_OV6_LAYER3_POS_ADDR(base)             ((base) + (0xC8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER3_SIZE_UNION */
#define SOC_DSS_OV6_LAYER3_SIZE_ADDR(base)            ((base) + (0xCC))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER3_SRCLOKEY_UNION */
#define SOC_DSS_OV6_LAYER3_SRCLOKEY_ADDR(base)        ((base) + (0xD0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER3_SRCHIKEY_UNION */
#define SOC_DSS_OV6_LAYER3_SRCHIKEY_ADDR(base)        ((base) + (0xD4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER3_DSTLOKEY_UNION */
#define SOC_DSS_OV6_LAYER3_DSTLOKEY_ADDR(base)        ((base) + (0xD8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER3_DSTHIKEY_UNION */
#define SOC_DSS_OV6_LAYER3_DSTHIKEY_ADDR(base)        ((base) + (0xDC))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER3_PATTERN_UNION */
#define SOC_DSS_OV6_LAYER3_PATTERN_ADDR(base)         ((base) + (0xE0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER3_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER3_ALPHA_ADDR(base)           ((base) + (0xE4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER3_CFG_UNION */
#define SOC_DSS_OV6_LAYER3_CFG_ADDR(base)             ((base) + (0xE8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER3_PSPOS_UNION */
#define SOC_DSS_OV6_LAYER3_PSPOS_ADDR(base)           ((base) + (0xEC))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER3_PEPOS_UNION */
#define SOC_DSS_OV6_LAYER3_PEPOS_ADDR(base)           ((base) + (0xF0))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER3_INFO_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_ADDR(base)      ((base) + (0xF4))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_UNION */
#define SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_ADDR(base)   ((base) + (0xF8))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER3_ST_INFO_UNION */
#define SOC_DSS_OV6_LAYER3_ST_INFO_ADDR(base)         ((base) + (0xFC))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER3_IST_INFO_UNION */
#define SOC_DSS_OV6_LAYER3_IST_INFO_ADDR(base)        ((base) + (0x100))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER4_POS_UNION */
#define SOC_DSS_OV6_LAYER4_POS_ADDR(base)             ((base) + (0x104))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER4_SIZE_UNION */
#define SOC_DSS_OV6_LAYER4_SIZE_ADDR(base)            ((base) + (0x108))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER4_SRCLOKEY_UNION */
#define SOC_DSS_OV6_LAYER4_SRCLOKEY_ADDR(base)        ((base) + (0x10C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER4_SRCHIKEY_UNION */
#define SOC_DSS_OV6_LAYER4_SRCHIKEY_ADDR(base)        ((base) + (0x110))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER4_DSTLOKEY_UNION */
#define SOC_DSS_OV6_LAYER4_DSTLOKEY_ADDR(base)        ((base) + (0x114))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER4_DSTHIKEY_UNION */
#define SOC_DSS_OV6_LAYER4_DSTHIKEY_ADDR(base)        ((base) + (0x118))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER4_PATTERN_UNION */
#define SOC_DSS_OV6_LAYER4_PATTERN_ADDR(base)         ((base) + (0x11C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER4_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER4_ALPHA_ADDR(base)           ((base) + (0x120))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER4_CFG_UNION */
#define SOC_DSS_OV6_LAYER4_CFG_ADDR(base)             ((base) + (0x124))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER4_PSPOS_UNION */
#define SOC_DSS_OV6_LAYER4_PSPOS_ADDR(base)           ((base) + (0x128))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER4_PEPOS_UNION */
#define SOC_DSS_OV6_LAYER4_PEPOS_ADDR(base)           ((base) + (0x12C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER4_INFO_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_ADDR(base)      ((base) + (0x130))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_UNION */
#define SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_ADDR(base)   ((base) + (0x134))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER4_ST_INFO_UNION */
#define SOC_DSS_OV6_LAYER4_ST_INFO_ADDR(base)         ((base) + (0x138))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER4_IST_INFO_UNION */
#define SOC_DSS_OV6_LAYER4_IST_INFO_ADDR(base)        ((base) + (0x13C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER5_POS_UNION */
#define SOC_DSS_OV6_LAYER5_POS_ADDR(base)             ((base) + (0x140))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER5_SIZE_UNION */
#define SOC_DSS_OV6_LAYER5_SIZE_ADDR(base)            ((base) + (0x144))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER5_SRCLOKEY_UNION */
#define SOC_DSS_OV6_LAYER5_SRCLOKEY_ADDR(base)        ((base) + (0x148))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER5_SRCHIKEY_UNION */
#define SOC_DSS_OV6_LAYER5_SRCHIKEY_ADDR(base)        ((base) + (0x14C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER5_DSTLOKEY_UNION */
#define SOC_DSS_OV6_LAYER5_DSTLOKEY_ADDR(base)        ((base) + (0x150))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER5_DSTHIKEY_UNION */
#define SOC_DSS_OV6_LAYER5_DSTHIKEY_ADDR(base)        ((base) + (0x154))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER5_PATTERN_UNION */
#define SOC_DSS_OV6_LAYER5_PATTERN_ADDR(base)         ((base) + (0x158))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER5_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER5_ALPHA_ADDR(base)           ((base) + (0x15C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER5_CFG_UNION */
#define SOC_DSS_OV6_LAYER5_CFG_ADDR(base)             ((base) + (0x160))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER5_PSPOS_UNION */
#define SOC_DSS_OV6_LAYER5_PSPOS_ADDR(base)           ((base) + (0x164))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER5_PEPOS_UNION */
#define SOC_DSS_OV6_LAYER5_PEPOS_ADDR(base)           ((base) + (0x168))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER5_INFO_ALPHA_UNION */
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_ADDR(base)      ((base) + (0x16C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_UNION */
#define SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_ADDR(base)   ((base) + (0x170))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER5_ST_INFO_UNION */
#define SOC_DSS_OV6_LAYER5_ST_INFO_ADDR(base)         ((base) + (0x174))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_LAYER5_IST_INFO_UNION */
#define SOC_DSS_OV6_LAYER5_IST_INFO_ADDR(base)        ((base) + (0x178))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_BASE_ST_INFO_UNION */
#define SOC_DSS_OV6_BASE_ST_INFO_ADDR(base)           ((base) + (0x17C))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_BASE_IST_INFO_UNION */
#define SOC_DSS_OV6_BASE_IST_INFO_ADDR(base)          ((base) + (0x180))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_GATE_CTRL_UNION */
#define SOC_DSS_OV6_GATE_CTRL_ADDR(base)              ((base) + (0x184))

/* �Ĵ���˵����
   λ����UNION�ṹ:  SOC_DSS_OV6_OV_RD_SHADOW_SEL_UNION */
#define SOC_DSS_OV6_OV_RD_SHADOW_SEL_ADDR(base)       ((base) + (0x188))

/* �Ĵ���˵����һ��ģ��ʱ��ѡ���ź�
   λ����UNION�ṹ:  SOC_DSS_OV6_OV_CLK_SEL_UNION */
#define SOC_DSS_OV6_OV_CLK_SEL_ADDR(base)             ((base) + (0x018C))

/* �Ĵ���˵����һ��ģ��ʱ��ʹ���ź�
   λ����UNION�ṹ:  SOC_DSS_OV6_OV_CLK_EN_UNION */
#define SOC_DSS_OV6_OV_CLK_EN_ADDR(base)              ((base) + (0x0190))

/* �Ĵ���˵����Block��ͼ��߶�
   λ����UNION�ṹ:  SOC_DSS_OV6_BLOCK_SIZE_UNION */
#define SOC_DSS_OV6_BLOCK_SIZE_ADDR(base)             ((base) + (0x01A0))

/* �Ĵ���˵�����ֿ��ν�ɲ�Ĵ�
   λ����UNION�ṹ:  SOC_DSS_OV6_BLOCK_DBG_UNION */
#define SOC_DSS_OV6_BLOCK_DBG_ADDR(base)              ((base) + (0x01A4))

/* �Ĵ���˵����ģ��Ӱ�ӼĴ����ָ���Ĭ��ֵ
   λ����UNION�ṹ:  SOC_DSS_OV6_REG_DEFAULT_UNION */
#define SOC_DSS_OV6_REG_DEFAULT_ADDR(base)            ((base) + (0x01A8))





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
                     (1/1) reg_OV6
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_OV_SIZE_UNION
 �ṹ˵��  : OV_SIZE �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: overlayͼ���С
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  img_width  : 15; /* bit[0-14] : overlay�������ͼ����-1��������Ϊ��λ */
        unsigned int  reserved_0 : 1;  /* bit[15]   : ���� */
        unsigned int  img_height : 15; /* bit[16-30]: overlay�������ͼ��߶�-1 */
        unsigned int  reserved_1 : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_OV_SIZE_UNION;
#endif
#define SOC_DSS_OV6_OV_SIZE_img_width_START   (0)
#define SOC_DSS_OV6_OV_SIZE_img_width_END     (14)
#define SOC_DSS_OV6_OV_SIZE_img_height_START  (16)
#define SOC_DSS_OV6_OV_SIZE_img_height_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_OV_BG_COLOR_UNION
 �ṹ˵��  : OV_BG_COLOR �Ĵ����ṹ���塣��ַƫ����:0x4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bg_color : 32; /* bit[0-31]: overlay ������ɫ����ײ㣬��ʽΪargb8888 */
    } reg;
} SOC_DSS_OV6_OV_BG_COLOR_UNION;
#endif
#define SOC_DSS_OV6_OV_BG_COLOR_bg_color_START  (0)
#define SOC_DSS_OV6_OV_BG_COLOR_bg_color_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_DST_STARTPOS_UNION
 �ṹ˵��  : DST_STARTPOS �Ĵ����ṹ���塣��ַƫ����:0x8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  blayer_startx : 15; /* bit[0-14] : baselayer ��������������ʼ��x���� */
        unsigned int  reserved_0    : 1;  /* bit[15]   : ���� */
        unsigned int  blayer_starty : 15; /* bit[16-30]: baselayer ��������������ʼ��y���� */
        unsigned int  reserved_1    : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_DST_STARTPOS_UNION;
#endif
#define SOC_DSS_OV6_DST_STARTPOS_blayer_startx_START  (0)
#define SOC_DSS_OV6_DST_STARTPOS_blayer_startx_END    (14)
#define SOC_DSS_OV6_DST_STARTPOS_blayer_starty_START  (16)
#define SOC_DSS_OV6_DST_STARTPOS_blayer_starty_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_DST_ENDPOS_UNION
 �ṹ˵��  : DST_ENDPOS �Ĵ����ṹ���塣��ַƫ����:0xC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  blayer_endx : 15; /* bit[0-14] : baselayer ���������������x���� */
        unsigned int  reserved_0  : 1;  /* bit[15]   : ���� */
        unsigned int  blayer_endy : 15; /* bit[16-30]: baselayer ���������������y���� */
        unsigned int  reserved_1  : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_DST_ENDPOS_UNION;
#endif
#define SOC_DSS_OV6_DST_ENDPOS_blayer_endx_START  (0)
#define SOC_DSS_OV6_DST_ENDPOS_blayer_endx_END    (14)
#define SOC_DSS_OV6_DST_ENDPOS_blayer_endy_START  (16)
#define SOC_DSS_OV6_DST_ENDPOS_blayer_endy_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_OV_GCFG_UNION
 �ṹ˵��  : OV_GCFG �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  overlay_enable    : 1;  /* bit[0]    : overlay enable */
        unsigned int  reserved_0        : 7;  /* bit[1-7]  : ���� */
        unsigned int  reserved_1        : 3;  /* bit[8-10] : ���� */
        unsigned int  reserved_2        : 3;  /* bit[11-13]: ���� */
        unsigned int  reserved_3        : 2;  /* bit[14-15]: ���� */
        unsigned int  blayer_bgcolor_en : 1;  /* bit[16]   : 0: choose src0
                                                             1: only ouput constant color argb8888 format */
        unsigned int  reserved_4        : 3;  /* bit[17-19]: ���� */
        unsigned int  p3fmt             : 2;  /* bit[20-21]: 00: half line by line
                                                             01: column by column
                                                             10: quincunx */
        unsigned int  reserved_5        : 2;  /* bit[22-23]: ���� */
        unsigned int  p3fmt_enable      : 1;  /* bit[24]   : 3D format enable  */
        unsigned int  reserved_6        : 7;  /* bit[25-31]: ���� */
    } reg;
} SOC_DSS_OV6_OV_GCFG_UNION;
#endif
#define SOC_DSS_OV6_OV_GCFG_overlay_enable_START     (0)
#define SOC_DSS_OV6_OV_GCFG_overlay_enable_END       (0)
#define SOC_DSS_OV6_OV_GCFG_blayer_bgcolor_en_START  (16)
#define SOC_DSS_OV6_OV_GCFG_blayer_bgcolor_en_END    (16)
#define SOC_DSS_OV6_OV_GCFG_p3fmt_START              (20)
#define SOC_DSS_OV6_OV_GCFG_p3fmt_END                (21)
#define SOC_DSS_OV6_OV_GCFG_p3fmt_enable_START       (24)
#define SOC_DSS_OV6_OV_GCFG_p3fmt_enable_END         (24)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER0_POS_UNION
 �ṹ˵��  : LAYER0_POS �Ĵ����ṹ���塣��ַƫ����:0x14����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_startx : 15; /* bit[0-14] : layer 0 ��������������ʼ��x��� */
        unsigned int  reserved_0    : 1;  /* bit[15]   : ���� */
        unsigned int  layer0_starty : 15; /* bit[16-30]: layer 0 ��������������ʼ��y���� */
        unsigned int  reserved_1    : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER0_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_POS_layer0_startx_START  (0)
#define SOC_DSS_OV6_LAYER0_POS_layer0_startx_END    (14)
#define SOC_DSS_OV6_LAYER0_POS_layer0_starty_START  (16)
#define SOC_DSS_OV6_LAYER0_POS_layer0_starty_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER0_SIZE_UNION
 �ṹ˵��  : LAYER0_SIZE �Ĵ����ṹ���塣��ַƫ����:0x18����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_endx : 15; /* bit[0-14] : layer 0 ���������������x���� */
        unsigned int  reserved_0  : 1;  /* bit[15]   : ���� */
        unsigned int  layer0_endy : 15; /* bit[16-30]: layer 0 ���������������y���� */
        unsigned int  reserved_1  : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER0_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_SIZE_layer0_endx_START  (0)
#define SOC_DSS_OV6_LAYER0_SIZE_layer0_endx_END    (14)
#define SOC_DSS_OV6_LAYER0_SIZE_layer0_endy_START  (16)
#define SOC_DSS_OV6_LAYER0_SIZE_layer0_endy_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER0_SRCLOKEY_UNION
 �ṹ˵��  : LAYER0_SRCLOKEY �Ĵ����ṹ���塣��ַƫ����:0x1C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_src_locolorkey : 24; /* bit[0-23] : layer 0 source low color key */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER0_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_SRCLOKEY_layer0_src_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER0_SRCLOKEY_layer0_src_locolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER0_SRCHIKEY_UNION
 �ṹ˵��  : LAYER0_SRCHIKEY �Ĵ����ṹ���塣��ַƫ����:0x20����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_src_hicolorkey : 24; /* bit[0-23] : layer 0 source high color key */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER0_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_SRCHIKEY_layer0_src_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER0_SRCHIKEY_layer0_src_hicolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER0_DSTLOKEY_UNION
 �ṹ˵��  : LAYER0_DSTLOKEY �Ĵ����ṹ���塣��ַƫ����:0x24����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_dst_locolorkey : 24; /* bit[0-23] : layer 0 destination low color key */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER0_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_DSTLOKEY_layer0_dst_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER0_DSTLOKEY_layer0_dst_locolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER0_DSTHIKEY_UNION
 �ṹ˵��  : LAYER0_DSTHIKEY �Ĵ����ṹ���塣��ַƫ����:0x28����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_dst_hicolorkey : 24; /* bit[0-23] : layer 0 destination high color key */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER0_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_DSTHIKEY_layer0_dst_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER0_DSTHIKEY_layer0_dst_hicolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER0_PATTERN_UNION
 �ṹ˵��  : LAYER0_PATTERN �Ĵ����ṹ���塣��ַƫ����:0x2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_pattern : 32; /* bit[0-31]: layer 0 ɫ�ʳ�ֵ��argb8888��ʽ */
    } reg;
} SOC_DSS_OV6_LAYER0_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_PATTERN_layer0_pattern_START  (0)
#define SOC_DSS_OV6_LAYER0_PATTERN_layer0_pattern_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER0_ALPHA_UNION
 �ṹ˵��  : LAYER0_ALPHA �Ĵ����ṹ���塣��ַƫ����:0x30����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_dst_global_alpha : 8;  /* bit[0-7]  : layer 0 destination ȫ��alpha */
        unsigned int  layer0_fix_mode         : 1;  /* bit[8]    : layer 0 destination pixel alpha ѡ��
                                                                   0:destination pixel alpha
                                                                   1: source pixel alpha  */
        unsigned int  layer0_dst_pmode        : 1;  /* bit[9]    : layer 0 destination pixel alpha�����Ϊpmode_alpha
                                                                   0:pixel alpha
                                                                   1:1-pixel alpha */
        unsigned int  layer0_alpha_offdst     : 2;  /* bit[10-11]:  */
        unsigned int  layer0_dst_gmode        : 2;  /* bit[12-13]: layer 0 destination pmode_alpha�����Ϊgmode_alpha
                                                                   00: pmode_alpha
                                                                   01: pmode_alpha*dst_global_alpha
                                                                   10: dst_global_alpha */
        unsigned int  layer0_dst_amode        : 2;  /* bit[14-15]: layer 0 destination gmode_alpha�����Ϊamode_alpha
                                                                   00: 0
                                                                   01: 1
                                                                   10: 1-gmode_alpha
                                                                   11: gmode_alpha */
        unsigned int  layer0_src_global_alpha : 8;  /* bit[16-23]: layer 0 source ȫ��alpha */
        unsigned int  layer0_alpha_smode      : 1;  /* bit[24]   :  */
        unsigned int  layer0_src_pmode        : 1;  /* bit[25]   : layer 0 source pixel alpha�����Ϊpmode_alpha
                                                                   0��pixel alpha
                                                                   1��1-pixel alpha */
        unsigned int  layer0_src_lmode        : 1;  /* bit[26]   : 0: src_global_alpha
                                                                   1: dst pixel alpha */
        unsigned int  layer0_alpha_offsrc     : 1;  /* bit[27]   :  */
        unsigned int  layer0_src_gmode        : 2;  /* bit[28-29]: layer 0 source pmode_alpha�����Ϊgmode_alpha
                                                                   00: pmode_alpha
                                                                   01: pmode_alpha*src_global_alpha
                                                                   10: src_global_alpha */
        unsigned int  layer0_src_amode        : 2;  /* bit[30-31]: layer 0 source gmode_alpha�����Ϊamode_alpha
                                                                   00: 0
                                                                   01: 1
                                                                   10: 1-gmode_alpha
                                                                   11: gmode_alpha */
    } reg;
} SOC_DSS_OV6_LAYER0_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_global_alpha_START  (0)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_global_alpha_END    (7)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_fix_mode_START          (8)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_fix_mode_END            (8)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_pmode_START         (9)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_pmode_END           (9)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_offdst_START      (10)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_offdst_END        (11)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_gmode_START         (12)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_gmode_END           (13)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_amode_START         (14)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_amode_END           (15)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_global_alpha_START  (16)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_global_alpha_END    (23)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_smode_START       (24)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_smode_END         (24)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_pmode_START         (25)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_pmode_END           (25)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_lmode_START         (26)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_lmode_END           (26)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_offsrc_START      (27)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_offsrc_END        (27)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_gmode_START         (28)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_gmode_END           (29)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_amode_START         (30)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_amode_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER0_CFG_UNION
 �ṹ˵��  : LAYER0_CFG �Ĵ����ṹ���塣��ַƫ����:0x34����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_enable     : 1;  /* bit[0]    : 0: layer 0 disable
                                                             1: layer 0 enable
                                                             ��disableʱ����ǰ�����������ڵ�ǰ������� */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : ���� */
        unsigned int  layer0_trop_en    : 1;  /* bit[4]    : 0: transparent function disable
                                                             1: transparent function enable */
        unsigned int  layer0_rop_en     : 1;  /* bit[5]    : 0: alphablend function enable
                                                             1: rop function enable */
        unsigned int  reserved_1        : 2;  /* bit[6-7]  : ���� */
        unsigned int  layer0_src_cfg    : 1;  /* bit[8]    : 0: select source from layer0_src_sel
                                                             1: select source from layer0_pattern */
        unsigned int  reserved_2        : 3;  /* bit[9-11] : ���� */
        unsigned int  reserved_3        : 3;  /* bit[12-14]: ���� */
        unsigned int  reserved_4        : 1;  /* bit[15]   : ���� */
        unsigned int  layer0_auto_nosrc : 1;  /* bit[16]   : 0:�˲�̶���Ҫ 
                                                             1:�Զ��ж��Ƿ���Ҫ�˲��source, �˲�layer��need�źŲ������� */
        unsigned int  reserved_5        : 3;  /* bit[17-19]: ���� */
        unsigned int  layer0_trop_code  : 4;  /* bit[20-23]: [3:0] transparent code */
        unsigned int  layer0_rop_code   : 8;  /* bit[24-31]: [7:0] rop code */
    } reg;
} SOC_DSS_OV6_LAYER0_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_CFG_layer0_enable_START      (0)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_enable_END        (0)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_trop_en_START     (4)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_trop_en_END       (4)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_rop_en_START      (5)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_rop_en_END        (5)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_src_cfg_START     (8)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_src_cfg_END       (8)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_auto_nosrc_START  (16)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_auto_nosrc_END    (16)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_trop_code_START   (20)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_trop_code_END     (23)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_rop_code_START    (24)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_rop_code_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER0_PSPOS_UNION
 �ṹ˵��  : LAYER0_PSPOS �Ĵ����ṹ���塣��ַƫ����:0x38����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_pstartx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0     : 1;  /* bit[15]   : ���� */
        unsigned int  layer0_pstarty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1     : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER0_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_PSPOS_layer0_pstartx_START  (0)
#define SOC_DSS_OV6_LAYER0_PSPOS_layer0_pstartx_END    (14)
#define SOC_DSS_OV6_LAYER0_PSPOS_layer0_pstarty_START  (16)
#define SOC_DSS_OV6_LAYER0_PSPOS_layer0_pstarty_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER0_PEPOS_UNION
 �ṹ˵��  : LAYER0_PEPOS �Ĵ����ṹ���塣��ַƫ����:0x3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_pendx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0   : 1;  /* bit[15]   : ���� */
        unsigned int  layer0_pendy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1   : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER0_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_PEPOS_layer0_pendx_START  (0)
#define SOC_DSS_OV6_LAYER0_PEPOS_layer0_pendx_END    (14)
#define SOC_DSS_OV6_LAYER0_PEPOS_layer0_pendy_START  (16)
#define SOC_DSS_OV6_LAYER0_PEPOS_layer0_pendy_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER0_INFO_ALPHA_UNION
 �ṹ˵��  : LAYER0_INFO_ALPHA �Ĵ����ṹ���塣��ַƫ����:0x40����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_frame_end     : 1;  /* bit[0]    :  */
        unsigned int  layer0_nosrc         : 1;  /* bit[1]    :  */
        unsigned int  layer0_dstalpha_flag : 1;  /* bit[2]    :  */
        unsigned int  layer0_srcalpha_flag : 1;  /* bit[3]    :  */
        unsigned int  reserved_0           : 4;  /* bit[4-7]  : ���� */
        unsigned int  layer0_dstalpha_info : 8;  /* bit[8-15] :  */
        unsigned int  layer0_srcalpha_info : 8;  /* bit[16-23]:  */
        unsigned int  reserved_1           : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER0_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_frame_end_START      (0)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_frame_end_END        (0)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_nosrc_START          (1)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_nosrc_END            (1)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_dstalpha_flag_START  (2)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_dstalpha_flag_END    (2)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_srcalpha_flag_START  (3)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_srcalpha_flag_END    (3)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_dstalpha_info_START  (8)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_dstalpha_info_END    (15)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_srcalpha_info_START  (16)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_srcalpha_info_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_UNION
 �ṹ˵��  : LAYER0_INFO_SRCCOLOR �Ĵ����ṹ���塣��ַƫ����:0x44����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_srccolor_flag : 1;  /* bit[0]   :  */
        unsigned int  reserved             : 7;  /* bit[1-7] : ���� */
        unsigned int  layer0_srccolor_info : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_layer0_srccolor_flag_START  (0)
#define SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_layer0_srccolor_flag_END    (0)
#define SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_layer0_srccolor_info_START  (8)
#define SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_layer0_srccolor_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER0_ST_INFO_UNION
 �ṹ˵��  : LAYER0_ST_INFO �Ĵ����ṹ���塣��ַƫ����:0x48����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_stall_info : 32; /* bit[0-31]: ��һ֡dss_clear ���³�istall_infoֵ */
    } reg;
} SOC_DSS_OV6_LAYER0_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_ST_INFO_layer0_stall_info_START  (0)
#define SOC_DSS_OV6_LAYER0_ST_INFO_layer0_stall_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER0_IST_INFO_UNION
 �ṹ˵��  : LAYER0_IST_INFO �Ĵ����ṹ���塣��ַƫ����:0x4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer0_istall_info : 32; /* bit[0-31]: ��stall_info_en��Ч������һ֡�ڼ�(ov_dneed=1&&src_drdy=0)��������
                                                             ��dss_clear��Чʱ���� */
    } reg;
} SOC_DSS_OV6_LAYER0_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_IST_INFO_layer0_istall_info_START  (0)
#define SOC_DSS_OV6_LAYER0_IST_INFO_layer0_istall_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER1_POS_UNION
 �ṹ˵��  : LAYER1_POS �Ĵ����ṹ���塣��ַƫ����:0x50����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_startx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0    : 1;  /* bit[15]   : ���� */
        unsigned int  layer1_starty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1    : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER1_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_POS_layer1_startx_START  (0)
#define SOC_DSS_OV6_LAYER1_POS_layer1_startx_END    (14)
#define SOC_DSS_OV6_LAYER1_POS_layer1_starty_START  (16)
#define SOC_DSS_OV6_LAYER1_POS_layer1_starty_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER1_SIZE_UNION
 �ṹ˵��  : LAYER1_SIZE �Ĵ����ṹ���塣��ַƫ����:0x54����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_endx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0  : 1;  /* bit[15]   : ���� */
        unsigned int  layer1_endy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1  : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER1_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_SIZE_layer1_endx_START  (0)
#define SOC_DSS_OV6_LAYER1_SIZE_layer1_endx_END    (14)
#define SOC_DSS_OV6_LAYER1_SIZE_layer1_endy_START  (16)
#define SOC_DSS_OV6_LAYER1_SIZE_layer1_endy_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER1_SRCLOKEY_UNION
 �ṹ˵��  : LAYER1_SRCLOKEY �Ĵ����ṹ���塣��ַƫ����:0x58����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_src_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER1_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_SRCLOKEY_layer1_src_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER1_SRCLOKEY_layer1_src_locolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER1_SRCHIKEY_UNION
 �ṹ˵��  : LAYER1_SRCHIKEY �Ĵ����ṹ���塣��ַƫ����:0x5C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_src_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER1_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_SRCHIKEY_layer1_src_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER1_SRCHIKEY_layer1_src_hicolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER1_DSTLOKEY_UNION
 �ṹ˵��  : LAYER1_DSTLOKEY �Ĵ����ṹ���塣��ַƫ����:0x60����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_dst_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER1_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_DSTLOKEY_layer1_dst_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER1_DSTLOKEY_layer1_dst_locolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER1_DSTHIKEY_UNION
 �ṹ˵��  : LAYER1_DSTHIKEY �Ĵ����ṹ���塣��ַƫ����:0x64����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_dst_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER1_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_DSTHIKEY_layer1_dst_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER1_DSTHIKEY_layer1_dst_hicolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER1_PATTERN_UNION
 �ṹ˵��  : LAYER1_PATTERN �Ĵ����ṹ���塣��ַƫ����:0x68����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_pattern : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER1_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_PATTERN_layer1_pattern_START  (0)
#define SOC_DSS_OV6_LAYER1_PATTERN_layer1_pattern_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER1_ALPHA_UNION
 �ṹ˵��  : LAYER1_ALPHA �Ĵ����ṹ���塣��ַƫ����:0x6C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_dst_global_alpha : 8;  /* bit[0-7]  :  */
        unsigned int  layer1_fix_mode         : 1;  /* bit[8]    :  */
        unsigned int  layer1_dst_pmode        : 1;  /* bit[9]    :  */
        unsigned int  layer1_off_dst          : 2;  /* bit[10-11]:  */
        unsigned int  layer1_dst_gmode        : 2;  /* bit[12-13]:  */
        unsigned int  layer1_dst_amode        : 2;  /* bit[14-15]:  */
        unsigned int  layer1_src_global_alpha : 8;  /* bit[16-23]:  */
        unsigned int  layer1_alpha_smode      : 1;  /* bit[24]   :  */
        unsigned int  layer1_src_pmode        : 1;  /* bit[25]   :  */
        unsigned int  layer1_src_lmode        : 1;  /* bit[26]   :  */
        unsigned int  layer1_off_src          : 1;  /* bit[27]   :  */
        unsigned int  layer1_src_gmode        : 2;  /* bit[28-29]:  */
        unsigned int  layer1_src_amode        : 2;  /* bit[30-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER1_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_global_alpha_START  (0)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_global_alpha_END    (7)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_fix_mode_START          (8)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_fix_mode_END            (8)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_pmode_START         (9)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_pmode_END           (9)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_off_dst_START           (10)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_off_dst_END             (11)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_gmode_START         (12)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_gmode_END           (13)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_amode_START         (14)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_amode_END           (15)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_global_alpha_START  (16)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_global_alpha_END    (23)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_alpha_smode_START       (24)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_alpha_smode_END         (24)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_pmode_START         (25)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_pmode_END           (25)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_lmode_START         (26)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_lmode_END           (26)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_off_src_START           (27)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_off_src_END             (27)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_gmode_START         (28)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_gmode_END           (29)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_amode_START         (30)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_amode_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER1_CFG_UNION
 �ṹ˵��  : LAYER1_CFG �Ĵ����ṹ���塣��ַƫ����:0x70����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_enable     : 1;  /* bit[0]    :  */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : ���� */
        unsigned int  layer1_trop_en    : 1;  /* bit[4]    :  */
        unsigned int  layer1_rop_en     : 1;  /* bit[5]    :  */
        unsigned int  reserved_1        : 2;  /* bit[6-7]  : ���� */
        unsigned int  layer1_src_cfg    : 1;  /* bit[8]    :  */
        unsigned int  reserved_2        : 3;  /* bit[9-11] : ���� */
        unsigned int  reserved_3        : 3;  /* bit[12-14]:  */
        unsigned int  reserved_4        : 1;  /* bit[15]   : ���� */
        unsigned int  layer1_auto_nosrc : 1;  /* bit[16]   :  */
        unsigned int  reserved_5        : 3;  /* bit[17-19]: ���� */
        unsigned int  layer1_trop_code  : 4;  /* bit[20-23]:  */
        unsigned int  layer1_rop_code   : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER1_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_CFG_layer1_enable_START      (0)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_enable_END        (0)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_trop_en_START     (4)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_trop_en_END       (4)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_rop_en_START      (5)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_rop_en_END        (5)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_src_cfg_START     (8)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_src_cfg_END       (8)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_auto_nosrc_START  (16)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_auto_nosrc_END    (16)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_trop_code_START   (20)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_trop_code_END     (23)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_rop_code_START    (24)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_rop_code_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER1_PSPOS_UNION
 �ṹ˵��  : LAYER1_PSPOS �Ĵ����ṹ���塣��ַƫ����:0x74����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_pstartx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0     : 1;  /* bit[15]   : ���� */
        unsigned int  layer1_pstarty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1     : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER1_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_PSPOS_layer1_pstartx_START  (0)
#define SOC_DSS_OV6_LAYER1_PSPOS_layer1_pstartx_END    (14)
#define SOC_DSS_OV6_LAYER1_PSPOS_layer1_pstarty_START  (16)
#define SOC_DSS_OV6_LAYER1_PSPOS_layer1_pstarty_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER1_PEPOS_UNION
 �ṹ˵��  : LAYER1_PEPOS �Ĵ����ṹ���塣��ַƫ����:0x78����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_pendx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0   : 1;  /* bit[15]   : ���� */
        unsigned int  layer1_pendy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1   : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER1_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_PEPOS_layer1_pendx_START  (0)
#define SOC_DSS_OV6_LAYER1_PEPOS_layer1_pendx_END    (14)
#define SOC_DSS_OV6_LAYER1_PEPOS_layer1_pendy_START  (16)
#define SOC_DSS_OV6_LAYER1_PEPOS_layer1_pendy_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER1_INFO_ALPHA_UNION
 �ṹ˵��  : LAYER1_INFO_ALPHA �Ĵ����ṹ���塣��ַƫ����:0x7C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_frame_end     : 1;  /* bit[0]    :  */
        unsigned int  layer1_nosrc         : 1;  /* bit[1]    :  */
        unsigned int  layer1_dstalpha_flag : 1;  /* bit[2]    :  */
        unsigned int  layer1_srcalpha_flag : 1;  /* bit[3]    :  */
        unsigned int  reserved_0           : 4;  /* bit[4-7]  : ���� */
        unsigned int  layer1_dstalpha_info : 8;  /* bit[8-15] :  */
        unsigned int  layer1_srcalpha_info : 8;  /* bit[16-23]:  */
        unsigned int  reserved_1           : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER1_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_frame_end_START      (0)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_frame_end_END        (0)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_nosrc_START          (1)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_nosrc_END            (1)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_dstalpha_flag_START  (2)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_dstalpha_flag_END    (2)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_srcalpha_flag_START  (3)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_srcalpha_flag_END    (3)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_dstalpha_info_START  (8)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_dstalpha_info_END    (15)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_srcalpha_info_START  (16)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_srcalpha_info_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_UNION
 �ṹ˵��  : LAYER1_INFO_SRCCOLOR �Ĵ����ṹ���塣��ַƫ����:0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_srccolor_flag : 1;  /* bit[0]   :  */
        unsigned int  reserved             : 7;  /* bit[1-7] : ���� */
        unsigned int  layer1_srccolor_info : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_layer1_srccolor_flag_START  (0)
#define SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_layer1_srccolor_flag_END    (0)
#define SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_layer1_srccolor_info_START  (8)
#define SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_layer1_srccolor_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER1_ST_INFO_UNION
 �ṹ˵��  : LAYER1_ST_INFO �Ĵ����ṹ���塣��ַƫ����:0x84����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_stall_info : 32; /* bit[0-31]: ��һ֡dss_clear ���³�istall_infoֵ */
    } reg;
} SOC_DSS_OV6_LAYER1_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_ST_INFO_layer1_stall_info_START  (0)
#define SOC_DSS_OV6_LAYER1_ST_INFO_layer1_stall_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER1_IST_INFO_UNION
 �ṹ˵��  : LAYER1_IST_INFO �Ĵ����ṹ���塣��ַƫ����:0x88����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer1_istall_info : 32; /* bit[0-31]: ��stall_info_en��Ч������һ֡�ڼ�(ov_dneed=1&&src_drdy=0)��������
                                                             ��dss_clear��Чʱ���� */
    } reg;
} SOC_DSS_OV6_LAYER1_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_IST_INFO_layer1_istall_info_START  (0)
#define SOC_DSS_OV6_LAYER1_IST_INFO_layer1_istall_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER2_POS_UNION
 �ṹ˵��  : LAYER2_POS �Ĵ����ṹ���塣��ַƫ����:0x8C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_startx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0    : 1;  /* bit[15]   : ���� */
        unsigned int  layer2_starty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1    : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER2_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_POS_layer2_startx_START  (0)
#define SOC_DSS_OV6_LAYER2_POS_layer2_startx_END    (14)
#define SOC_DSS_OV6_LAYER2_POS_layer2_starty_START  (16)
#define SOC_DSS_OV6_LAYER2_POS_layer2_starty_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER2_SIZE_UNION
 �ṹ˵��  : LAYER2_SIZE �Ĵ����ṹ���塣��ַƫ����:0x90����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_endx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0  : 1;  /* bit[15]   : ���� */
        unsigned int  layer2_endy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1  : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER2_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_SIZE_layer2_endx_START  (0)
#define SOC_DSS_OV6_LAYER2_SIZE_layer2_endx_END    (14)
#define SOC_DSS_OV6_LAYER2_SIZE_layer2_endy_START  (16)
#define SOC_DSS_OV6_LAYER2_SIZE_layer2_endy_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER2_SRCLOKEY_UNION
 �ṹ˵��  : LAYER2_SRCLOKEY �Ĵ����ṹ���塣��ַƫ����:0x94����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_src_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER2_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_SRCLOKEY_layer2_src_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER2_SRCLOKEY_layer2_src_locolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER2_SRCHIKEY_UNION
 �ṹ˵��  : LAYER2_SRCHIKEY �Ĵ����ṹ���塣��ַƫ����:0x98����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_src_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER2_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_SRCHIKEY_layer2_src_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER2_SRCHIKEY_layer2_src_hicolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER2_DSTLOKEY_UNION
 �ṹ˵��  : LAYER2_DSTLOKEY �Ĵ����ṹ���塣��ַƫ����:0x9C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_dst_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER2_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_DSTLOKEY_layer2_dst_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER2_DSTLOKEY_layer2_dst_locolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER2_DSTHIKEY_UNION
 �ṹ˵��  : LAYER2_DSTHIKEY �Ĵ����ṹ���塣��ַƫ����:0xA0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_dst_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER2_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_DSTHIKEY_layer2_dst_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER2_DSTHIKEY_layer2_dst_hicolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER2_PATTERN_UNION
 �ṹ˵��  : LAYER2_PATTERN �Ĵ����ṹ���塣��ַƫ����:0xA4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_pattern : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER2_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_PATTERN_layer2_pattern_START  (0)
#define SOC_DSS_OV6_LAYER2_PATTERN_layer2_pattern_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER2_ALPHA_UNION
 �ṹ˵��  : LAYER2_ALPHA �Ĵ����ṹ���塣��ַƫ����:0xA8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_dst_global_alpha : 8;  /* bit[0-7]  :  */
        unsigned int  layer2_fix_mode         : 1;  /* bit[8]    :  */
        unsigned int  layer2_dst_pmode        : 1;  /* bit[9]    :  */
        unsigned int  layer2_off_dst          : 2;  /* bit[10-11]:  */
        unsigned int  layer2_dst_gmode        : 2;  /* bit[12-13]:  */
        unsigned int  layer2_dst_amode        : 2;  /* bit[14-15]:  */
        unsigned int  layer2_src_global_alpha : 8;  /* bit[16-23]:  */
        unsigned int  layer2_alpha_smode      : 1;  /* bit[24]   :  */
        unsigned int  layer2_src_pmode        : 1;  /* bit[25]   :  */
        unsigned int  layer2_src_lmode        : 1;  /* bit[26]   :  */
        unsigned int  layer2_off_src          : 1;  /* bit[27]   :  */
        unsigned int  layer2_src_gmode        : 2;  /* bit[28-29]:  */
        unsigned int  layer2_src_amode        : 2;  /* bit[30-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER2_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_global_alpha_START  (0)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_global_alpha_END    (7)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_fix_mode_START          (8)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_fix_mode_END            (8)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_pmode_START         (9)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_pmode_END           (9)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_off_dst_START           (10)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_off_dst_END             (11)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_gmode_START         (12)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_gmode_END           (13)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_amode_START         (14)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_amode_END           (15)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_global_alpha_START  (16)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_global_alpha_END    (23)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_alpha_smode_START       (24)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_alpha_smode_END         (24)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_pmode_START         (25)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_pmode_END           (25)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_lmode_START         (26)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_lmode_END           (26)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_off_src_START           (27)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_off_src_END             (27)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_gmode_START         (28)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_gmode_END           (29)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_amode_START         (30)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_amode_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER2_CFG_UNION
 �ṹ˵��  : LAYER2_CFG �Ĵ����ṹ���塣��ַƫ����:0xAC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_enable     : 1;  /* bit[0]    :  */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : ���� */
        unsigned int  layer2_trop_en    : 1;  /* bit[4]    :  */
        unsigned int  layer2_rop_en     : 1;  /* bit[5]    :  */
        unsigned int  reserved_1        : 2;  /* bit[6-7]  : ���� */
        unsigned int  layer2_src_cfg    : 1;  /* bit[8]    :  */
        unsigned int  reserved_2        : 3;  /* bit[9-11] : ���� */
        unsigned int  reserved_3        : 3;  /* bit[12-14]:  */
        unsigned int  reserved_4        : 1;  /* bit[15]   : ���� */
        unsigned int  layer2_auto_nosrc : 1;  /* bit[16]   :  */
        unsigned int  reserved_5        : 3;  /* bit[17-19]: ���� */
        unsigned int  layer2_trop_code  : 4;  /* bit[20-23]:  */
        unsigned int  layer2_rop_code   : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER2_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_CFG_layer2_enable_START      (0)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_enable_END        (0)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_trop_en_START     (4)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_trop_en_END       (4)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_rop_en_START      (5)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_rop_en_END        (5)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_src_cfg_START     (8)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_src_cfg_END       (8)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_auto_nosrc_START  (16)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_auto_nosrc_END    (16)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_trop_code_START   (20)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_trop_code_END     (23)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_rop_code_START    (24)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_rop_code_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER2_PSPOS_UNION
 �ṹ˵��  : LAYER2_PSPOS �Ĵ����ṹ���塣��ַƫ����:0xB0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_pstartx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0     : 1;  /* bit[15]   : ���� */
        unsigned int  layer2_pstarty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1     : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER2_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_PSPOS_layer2_pstartx_START  (0)
#define SOC_DSS_OV6_LAYER2_PSPOS_layer2_pstartx_END    (14)
#define SOC_DSS_OV6_LAYER2_PSPOS_layer2_pstarty_START  (16)
#define SOC_DSS_OV6_LAYER2_PSPOS_layer2_pstarty_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER2_PEPOS_UNION
 �ṹ˵��  : LAYER2_PEPOS �Ĵ����ṹ���塣��ַƫ����:0xB4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_pendx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0   : 1;  /* bit[15]   : ���� */
        unsigned int  layer2_pendy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1   : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER2_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_PEPOS_layer2_pendx_START  (0)
#define SOC_DSS_OV6_LAYER2_PEPOS_layer2_pendx_END    (14)
#define SOC_DSS_OV6_LAYER2_PEPOS_layer2_pendy_START  (16)
#define SOC_DSS_OV6_LAYER2_PEPOS_layer2_pendy_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER2_INFO_ALPHA_UNION
 �ṹ˵��  : LAYER2_INFO_ALPHA �Ĵ����ṹ���塣��ַƫ����:0xB8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_frame_end     : 1;  /* bit[0]    :  */
        unsigned int  layer2_nosrc         : 1;  /* bit[1]    :  */
        unsigned int  layer2_dstalpha_flag : 1;  /* bit[2]    :  */
        unsigned int  layer2_srcalpha_flag : 1;  /* bit[3]    :  */
        unsigned int  reserved_0           : 4;  /* bit[4-7]  : ���� */
        unsigned int  layer2_dstalpha_info : 8;  /* bit[8-15] :  */
        unsigned int  layer2_srcalpha_info : 8;  /* bit[16-23]:  */
        unsigned int  reserved_1           : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER2_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_frame_end_START      (0)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_frame_end_END        (0)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_nosrc_START          (1)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_nosrc_END            (1)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_dstalpha_flag_START  (2)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_dstalpha_flag_END    (2)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_srcalpha_flag_START  (3)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_srcalpha_flag_END    (3)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_dstalpha_info_START  (8)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_dstalpha_info_END    (15)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_srcalpha_info_START  (16)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_srcalpha_info_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_UNION
 �ṹ˵��  : LAYER2_INFO_SRCCOLOR �Ĵ����ṹ���塣��ַƫ����:0xBC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_srccolor_flag : 1;  /* bit[0]   :  */
        unsigned int  reserved             : 7;  /* bit[1-7] : ���� */
        unsigned int  layer2_srccolor_info : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_layer2_srccolor_flag_START  (0)
#define SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_layer2_srccolor_flag_END    (0)
#define SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_layer2_srccolor_info_START  (8)
#define SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_layer2_srccolor_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER2_ST_INFO_UNION
 �ṹ˵��  : LAYER2_ST_INFO �Ĵ����ṹ���塣��ַƫ����:0xC0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_stall_info : 32; /* bit[0-31]: ��һ֡dss_clear ���³�istall_infoֵ */
    } reg;
} SOC_DSS_OV6_LAYER2_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_ST_INFO_layer2_stall_info_START  (0)
#define SOC_DSS_OV6_LAYER2_ST_INFO_layer2_stall_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER2_IST_INFO_UNION
 �ṹ˵��  : LAYER2_IST_INFO �Ĵ����ṹ���塣��ַƫ����:0xC4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer2_istall_info : 32; /* bit[0-31]: ��stall_info_en��Ч������һ֡�ڼ�(ov_dneed=1&&src_drdy=0)��������
                                                             ��dss_clear��Чʱ���� */
    } reg;
} SOC_DSS_OV6_LAYER2_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_IST_INFO_layer2_istall_info_START  (0)
#define SOC_DSS_OV6_LAYER2_IST_INFO_layer2_istall_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER3_POS_UNION
 �ṹ˵��  : LAYER3_POS �Ĵ����ṹ���塣��ַƫ����:0xC8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_startx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0    : 1;  /* bit[15]   : ���� */
        unsigned int  layer3_starty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1    : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER3_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_POS_layer3_startx_START  (0)
#define SOC_DSS_OV6_LAYER3_POS_layer3_startx_END    (14)
#define SOC_DSS_OV6_LAYER3_POS_layer3_starty_START  (16)
#define SOC_DSS_OV6_LAYER3_POS_layer3_starty_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER3_SIZE_UNION
 �ṹ˵��  : LAYER3_SIZE �Ĵ����ṹ���塣��ַƫ����:0xCC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_endx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0  : 1;  /* bit[15]   : ���� */
        unsigned int  layer3_endy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1  : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER3_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_SIZE_layer3_endx_START  (0)
#define SOC_DSS_OV6_LAYER3_SIZE_layer3_endx_END    (14)
#define SOC_DSS_OV6_LAYER3_SIZE_layer3_endy_START  (16)
#define SOC_DSS_OV6_LAYER3_SIZE_layer3_endy_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER3_SRCLOKEY_UNION
 �ṹ˵��  : LAYER3_SRCLOKEY �Ĵ����ṹ���塣��ַƫ����:0xD0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_src_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER3_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_SRCLOKEY_layer3_src_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER3_SRCLOKEY_layer3_src_locolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER3_SRCHIKEY_UNION
 �ṹ˵��  : LAYER3_SRCHIKEY �Ĵ����ṹ���塣��ַƫ����:0xD4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_src_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER3_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_SRCHIKEY_layer3_src_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER3_SRCHIKEY_layer3_src_hicolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER3_DSTLOKEY_UNION
 �ṹ˵��  : LAYER3_DSTLOKEY �Ĵ����ṹ���塣��ַƫ����:0xD8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_dst_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER3_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_DSTLOKEY_layer3_dst_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER3_DSTLOKEY_layer3_dst_locolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER3_DSTHIKEY_UNION
 �ṹ˵��  : LAYER3_DSTHIKEY �Ĵ����ṹ���塣��ַƫ����:0xDC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_dst_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER3_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_DSTHIKEY_layer3_dst_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER3_DSTHIKEY_layer3_dst_hicolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER3_PATTERN_UNION
 �ṹ˵��  : LAYER3_PATTERN �Ĵ����ṹ���塣��ַƫ����:0xE0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_pattern : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER3_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_PATTERN_layer3_pattern_START  (0)
#define SOC_DSS_OV6_LAYER3_PATTERN_layer3_pattern_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER3_ALPHA_UNION
 �ṹ˵��  : LAYER3_ALPHA �Ĵ����ṹ���塣��ַƫ����:0xE4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_dst_global_alpha : 8;  /* bit[0-7]  :  */
        unsigned int  layer3_fix_mode         : 1;  /* bit[8]    :  */
        unsigned int  layer3_dst_pmode        : 1;  /* bit[9]    :  */
        unsigned int  layer3_off_dst          : 2;  /* bit[10-11]:  */
        unsigned int  layer3_dst_gmode        : 2;  /* bit[12-13]:  */
        unsigned int  layer3_dst_amode        : 2;  /* bit[14-15]:  */
        unsigned int  layer3_src_global_alpha : 8;  /* bit[16-23]:  */
        unsigned int  layer3_alpha_smode      : 1;  /* bit[24]   :  */
        unsigned int  layer3_src_pmode        : 1;  /* bit[25]   :  */
        unsigned int  layer3_src_lmode        : 1;  /* bit[26]   :  */
        unsigned int  layer3_off_src          : 1;  /* bit[27]   :  */
        unsigned int  layer3_src_gmode        : 2;  /* bit[28-29]:  */
        unsigned int  layer3_src_amode        : 2;  /* bit[30-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER3_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_global_alpha_START  (0)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_global_alpha_END    (7)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_fix_mode_START          (8)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_fix_mode_END            (8)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_pmode_START         (9)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_pmode_END           (9)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_off_dst_START           (10)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_off_dst_END             (11)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_gmode_START         (12)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_gmode_END           (13)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_amode_START         (14)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_amode_END           (15)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_global_alpha_START  (16)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_global_alpha_END    (23)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_alpha_smode_START       (24)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_alpha_smode_END         (24)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_pmode_START         (25)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_pmode_END           (25)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_lmode_START         (26)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_lmode_END           (26)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_off_src_START           (27)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_off_src_END             (27)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_gmode_START         (28)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_gmode_END           (29)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_amode_START         (30)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_amode_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER3_CFG_UNION
 �ṹ˵��  : LAYER3_CFG �Ĵ����ṹ���塣��ַƫ����:0xE8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_enable     : 1;  /* bit[0]    :  */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : ���� */
        unsigned int  layer3_trop_en    : 1;  /* bit[4]    :  */
        unsigned int  layer3_rop_en     : 1;  /* bit[5]    :  */
        unsigned int  reserved_1        : 2;  /* bit[6-7]  : ���� */
        unsigned int  layer3_src_cfg    : 1;  /* bit[8]    :  */
        unsigned int  reserved_2        : 3;  /* bit[9-11] : ���� */
        unsigned int  reserved_3        : 3;  /* bit[12-14]:  */
        unsigned int  reserved_4        : 1;  /* bit[15]   : ���� */
        unsigned int  layer3_auto_nosrc : 1;  /* bit[16]   :  */
        unsigned int  reserved_5        : 3;  /* bit[17-19]: ���� */
        unsigned int  layer3_trop_code  : 4;  /* bit[20-23]:  */
        unsigned int  layer3_rop_code   : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER3_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_CFG_layer3_enable_START      (0)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_enable_END        (0)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_trop_en_START     (4)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_trop_en_END       (4)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_rop_en_START      (5)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_rop_en_END        (5)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_src_cfg_START     (8)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_src_cfg_END       (8)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_auto_nosrc_START  (16)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_auto_nosrc_END    (16)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_trop_code_START   (20)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_trop_code_END     (23)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_rop_code_START    (24)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_rop_code_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER3_PSPOS_UNION
 �ṹ˵��  : LAYER3_PSPOS �Ĵ����ṹ���塣��ַƫ����:0xEC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_pstartx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0     : 1;  /* bit[15]   : ���� */
        unsigned int  layer3_pstarty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1     : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER3_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_PSPOS_layer3_pstartx_START  (0)
#define SOC_DSS_OV6_LAYER3_PSPOS_layer3_pstartx_END    (14)
#define SOC_DSS_OV6_LAYER3_PSPOS_layer3_pstarty_START  (16)
#define SOC_DSS_OV6_LAYER3_PSPOS_layer3_pstarty_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER3_PEPOS_UNION
 �ṹ˵��  : LAYER3_PEPOS �Ĵ����ṹ���塣��ַƫ����:0xF0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_pendx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0   : 1;  /* bit[15]   : ���� */
        unsigned int  layer3_pendy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1   : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER3_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_PEPOS_layer3_pendx_START  (0)
#define SOC_DSS_OV6_LAYER3_PEPOS_layer3_pendx_END    (14)
#define SOC_DSS_OV6_LAYER3_PEPOS_layer3_pendy_START  (16)
#define SOC_DSS_OV6_LAYER3_PEPOS_layer3_pendy_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER3_INFO_ALPHA_UNION
 �ṹ˵��  : LAYER3_INFO_ALPHA �Ĵ����ṹ���塣��ַƫ����:0xF4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_frame_end     : 1;  /* bit[0]    :  */
        unsigned int  layer3_nosrc         : 1;  /* bit[1]    :  */
        unsigned int  layer3_dstalpha_flag : 1;  /* bit[2]    :  */
        unsigned int  layer3_srcalpha_flag : 1;  /* bit[3]    :  */
        unsigned int  reserved_0           : 4;  /* bit[4-7]  : ���� */
        unsigned int  layer3_dstalpha_info : 8;  /* bit[8-15] :  */
        unsigned int  layer3_srcalpha_info : 8;  /* bit[16-23]:  */
        unsigned int  reserved_1           : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER3_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_frame_end_START      (0)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_frame_end_END        (0)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_nosrc_START          (1)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_nosrc_END            (1)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_dstalpha_flag_START  (2)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_dstalpha_flag_END    (2)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_srcalpha_flag_START  (3)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_srcalpha_flag_END    (3)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_dstalpha_info_START  (8)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_dstalpha_info_END    (15)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_srcalpha_info_START  (16)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_srcalpha_info_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_UNION
 �ṹ˵��  : LAYER3_INFO_SRCCOLOR �Ĵ����ṹ���塣��ַƫ����:0xF8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_srccolor_flag : 1;  /* bit[0]   :  */
        unsigned int  reserved             : 7;  /* bit[1-7] : ���� */
        unsigned int  layer3_srccolor_info : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_layer3_srccolor_flag_START  (0)
#define SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_layer3_srccolor_flag_END    (0)
#define SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_layer3_srccolor_info_START  (8)
#define SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_layer3_srccolor_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER3_ST_INFO_UNION
 �ṹ˵��  : LAYER3_ST_INFO �Ĵ����ṹ���塣��ַƫ����:0xFC����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_stall_info : 32; /* bit[0-31]: ��һ֡dss_clear ���³�istall_infoֵ */
    } reg;
} SOC_DSS_OV6_LAYER3_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_ST_INFO_layer3_stall_info_START  (0)
#define SOC_DSS_OV6_LAYER3_ST_INFO_layer3_stall_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER3_IST_INFO_UNION
 �ṹ˵��  : LAYER3_IST_INFO �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer3_istall_info : 32; /* bit[0-31]: ��stall_info_en��Ч������һ֡�ڼ�(ov_dneed=1&&src_drdy=0)��������
                                                             ��dss_clear��Чʱ���� */
    } reg;
} SOC_DSS_OV6_LAYER3_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_IST_INFO_layer3_istall_info_START  (0)
#define SOC_DSS_OV6_LAYER3_IST_INFO_layer3_istall_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER4_POS_UNION
 �ṹ˵��  : LAYER4_POS �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_startx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0    : 1;  /* bit[15]   : ���� */
        unsigned int  layer4_starty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1    : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER4_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_POS_layer4_startx_START  (0)
#define SOC_DSS_OV6_LAYER4_POS_layer4_startx_END    (14)
#define SOC_DSS_OV6_LAYER4_POS_layer4_starty_START  (16)
#define SOC_DSS_OV6_LAYER4_POS_layer4_starty_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER4_SIZE_UNION
 �ṹ˵��  : LAYER4_SIZE �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_endx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0  : 1;  /* bit[15]   : ���� */
        unsigned int  layer4_endy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1  : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER4_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_SIZE_layer4_endx_START  (0)
#define SOC_DSS_OV6_LAYER4_SIZE_layer4_endx_END    (14)
#define SOC_DSS_OV6_LAYER4_SIZE_layer4_endy_START  (16)
#define SOC_DSS_OV6_LAYER4_SIZE_layer4_endy_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER4_SRCLOKEY_UNION
 �ṹ˵��  : LAYER4_SRCLOKEY �Ĵ����ṹ���塣��ַƫ����:0x10C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_src_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER4_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_SRCLOKEY_layer4_src_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER4_SRCLOKEY_layer4_src_locolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER4_SRCHIKEY_UNION
 �ṹ˵��  : LAYER4_SRCHIKEY �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_src_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER4_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_SRCHIKEY_layer4_src_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER4_SRCHIKEY_layer4_src_hicolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER4_DSTLOKEY_UNION
 �ṹ˵��  : LAYER4_DSTLOKEY �Ĵ����ṹ���塣��ַƫ����:0x114����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_dst_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER4_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_DSTLOKEY_layer4_dst_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER4_DSTLOKEY_layer4_dst_locolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER4_DSTHIKEY_UNION
 �ṹ˵��  : LAYER4_DSTHIKEY �Ĵ����ṹ���塣��ַƫ����:0x118����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_dst_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER4_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_DSTHIKEY_layer4_dst_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER4_DSTHIKEY_layer4_dst_hicolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER4_PATTERN_UNION
 �ṹ˵��  : LAYER4_PATTERN �Ĵ����ṹ���塣��ַƫ����:0x11C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_pattern : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER4_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_PATTERN_layer4_pattern_START  (0)
#define SOC_DSS_OV6_LAYER4_PATTERN_layer4_pattern_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER4_ALPHA_UNION
 �ṹ˵��  : LAYER4_ALPHA �Ĵ����ṹ���塣��ַƫ����:0x120����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_dst_global_alpha : 8;  /* bit[0-7]  :  */
        unsigned int  layer4_fix_mode         : 1;  /* bit[8]    :  */
        unsigned int  layer4_dst_pmode        : 1;  /* bit[9]    :  */
        unsigned int  layer4_off_dst          : 2;  /* bit[10-11]:  */
        unsigned int  layer4_dst_gmode        : 2;  /* bit[12-13]:  */
        unsigned int  layer4_dst_amode        : 2;  /* bit[14-15]:  */
        unsigned int  layer4_src_global_alpha : 8;  /* bit[16-23]:  */
        unsigned int  layer4_alpha_smode      : 1;  /* bit[24]   :  */
        unsigned int  layer4_src_pmode        : 1;  /* bit[25]   :  */
        unsigned int  layer4_src_lmode        : 1;  /* bit[26]   :  */
        unsigned int  layer4_off_src          : 1;  /* bit[27]   :  */
        unsigned int  layer4_src_gmode        : 2;  /* bit[28-29]:  */
        unsigned int  layer4_src_amode        : 2;  /* bit[30-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER4_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_global_alpha_START  (0)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_global_alpha_END    (7)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_fix_mode_START          (8)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_fix_mode_END            (8)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_pmode_START         (9)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_pmode_END           (9)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_off_dst_START           (10)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_off_dst_END             (11)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_gmode_START         (12)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_gmode_END           (13)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_amode_START         (14)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_amode_END           (15)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_global_alpha_START  (16)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_global_alpha_END    (23)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_alpha_smode_START       (24)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_alpha_smode_END         (24)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_pmode_START         (25)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_pmode_END           (25)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_lmode_START         (26)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_lmode_END           (26)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_off_src_START           (27)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_off_src_END             (27)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_gmode_START         (28)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_gmode_END           (29)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_amode_START         (30)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_amode_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER4_CFG_UNION
 �ṹ˵��  : LAYER4_CFG �Ĵ����ṹ���塣��ַƫ����:0x124����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_enable     : 1;  /* bit[0]    :  */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : ���� */
        unsigned int  layer4_trop_en    : 1;  /* bit[4]    :  */
        unsigned int  layer4_rop_en     : 1;  /* bit[5]    :  */
        unsigned int  reserved_1        : 2;  /* bit[6-7]  : ���� */
        unsigned int  layer4_src_cfg    : 1;  /* bit[8]    :  */
        unsigned int  reserved_2        : 3;  /* bit[9-11] : ���� */
        unsigned int  reserved_3        : 3;  /* bit[12-14]:  */
        unsigned int  reserved_4        : 1;  /* bit[15]   : ���� */
        unsigned int  layer4_auto_nosrc : 1;  /* bit[16]   :  */
        unsigned int  reserved_5        : 3;  /* bit[17-19]: ���� */
        unsigned int  layer4_trop_code  : 4;  /* bit[20-23]:  */
        unsigned int  layer4_rop_code   : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER4_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_CFG_layer4_enable_START      (0)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_enable_END        (0)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_trop_en_START     (4)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_trop_en_END       (4)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_rop_en_START      (5)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_rop_en_END        (5)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_src_cfg_START     (8)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_src_cfg_END       (8)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_auto_nosrc_START  (16)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_auto_nosrc_END    (16)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_trop_code_START   (20)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_trop_code_END     (23)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_rop_code_START    (24)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_rop_code_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER4_PSPOS_UNION
 �ṹ˵��  : LAYER4_PSPOS �Ĵ����ṹ���塣��ַƫ����:0x128����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_pstartx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0     : 1;  /* bit[15]   : ���� */
        unsigned int  layer4_pstarty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1     : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER4_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_PSPOS_layer4_pstartx_START  (0)
#define SOC_DSS_OV6_LAYER4_PSPOS_layer4_pstartx_END    (14)
#define SOC_DSS_OV6_LAYER4_PSPOS_layer4_pstarty_START  (16)
#define SOC_DSS_OV6_LAYER4_PSPOS_layer4_pstarty_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER4_PEPOS_UNION
 �ṹ˵��  : LAYER4_PEPOS �Ĵ����ṹ���塣��ַƫ����:0x12C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_pendx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0   : 1;  /* bit[15]   : ���� */
        unsigned int  layer4_pendy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1   : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER4_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_PEPOS_layer4_pendx_START  (0)
#define SOC_DSS_OV6_LAYER4_PEPOS_layer4_pendx_END    (14)
#define SOC_DSS_OV6_LAYER4_PEPOS_layer4_pendy_START  (16)
#define SOC_DSS_OV6_LAYER4_PEPOS_layer4_pendy_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER4_INFO_ALPHA_UNION
 �ṹ˵��  : LAYER4_INFO_ALPHA �Ĵ����ṹ���塣��ַƫ����:0x130����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_frame_end     : 1;  /* bit[0]    :  */
        unsigned int  layer4_nosrc         : 1;  /* bit[1]    :  */
        unsigned int  layer4_dstalpha_flag : 1;  /* bit[2]    :  */
        unsigned int  layer4_srcalpha_flag : 1;  /* bit[3]    :  */
        unsigned int  reserved_0           : 4;  /* bit[4-7]  : ���� */
        unsigned int  layer4_dstalpha_info : 8;  /* bit[8-15] :  */
        unsigned int  layer4_srcalpha_info : 8;  /* bit[16-23]:  */
        unsigned int  reserved_1           : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER4_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_frame_end_START      (0)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_frame_end_END        (0)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_nosrc_START          (1)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_nosrc_END            (1)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_dstalpha_flag_START  (2)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_dstalpha_flag_END    (2)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_srcalpha_flag_START  (3)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_srcalpha_flag_END    (3)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_dstalpha_info_START  (8)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_dstalpha_info_END    (15)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_srcalpha_info_START  (16)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_srcalpha_info_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_UNION
 �ṹ˵��  : LAYER4_INFO_SRCCOLOR �Ĵ����ṹ���塣��ַƫ����:0x134����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_srccolor_flag : 1;  /* bit[0]   :  */
        unsigned int  reserved             : 7;  /* bit[1-7] : ���� */
        unsigned int  layer4_srccolor_info : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_layer4_srccolor_flag_START  (0)
#define SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_layer4_srccolor_flag_END    (0)
#define SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_layer4_srccolor_info_START  (8)
#define SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_layer4_srccolor_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER4_ST_INFO_UNION
 �ṹ˵��  : LAYER4_ST_INFO �Ĵ����ṹ���塣��ַƫ����:0x138����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_stall_info : 32; /* bit[0-31]: ��һ֡dss_clear ���³�istall_infoֵ */
    } reg;
} SOC_DSS_OV6_LAYER4_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_ST_INFO_layer4_stall_info_START  (0)
#define SOC_DSS_OV6_LAYER4_ST_INFO_layer4_stall_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER4_IST_INFO_UNION
 �ṹ˵��  : LAYER4_IST_INFO �Ĵ����ṹ���塣��ַƫ����:0x13C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer4_istall_info : 32; /* bit[0-31]: ��stall_info_en��Ч������һ֡�ڼ�(ov_dneed=1&&src_drdy=0)��������
                                                             ��dss_clear��Чʱ���� */
    } reg;
} SOC_DSS_OV6_LAYER4_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_IST_INFO_layer4_istall_info_START  (0)
#define SOC_DSS_OV6_LAYER4_IST_INFO_layer4_istall_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER5_POS_UNION
 �ṹ˵��  : LAYER5_POS �Ĵ����ṹ���塣��ַƫ����:0x140����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_startx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0    : 1;  /* bit[15]   : ���� */
        unsigned int  layer5_starty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1    : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER5_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_POS_layer5_startx_START  (0)
#define SOC_DSS_OV6_LAYER5_POS_layer5_startx_END    (14)
#define SOC_DSS_OV6_LAYER5_POS_layer5_starty_START  (16)
#define SOC_DSS_OV6_LAYER5_POS_layer5_starty_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER5_SIZE_UNION
 �ṹ˵��  : LAYER5_SIZE �Ĵ����ṹ���塣��ַƫ����:0x144����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_endx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0  : 1;  /* bit[15]   : ���� */
        unsigned int  layer5_endy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1  : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER5_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_SIZE_layer5_endx_START  (0)
#define SOC_DSS_OV6_LAYER5_SIZE_layer5_endx_END    (14)
#define SOC_DSS_OV6_LAYER5_SIZE_layer5_endy_START  (16)
#define SOC_DSS_OV6_LAYER5_SIZE_layer5_endy_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER5_SRCLOKEY_UNION
 �ṹ˵��  : LAYER5_SRCLOKEY �Ĵ����ṹ���塣��ַƫ����:0x148����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_src_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER5_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_SRCLOKEY_layer5_src_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER5_SRCLOKEY_layer5_src_locolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER5_SRCHIKEY_UNION
 �ṹ˵��  : LAYER5_SRCHIKEY �Ĵ����ṹ���塣��ַƫ����:0x14C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_src_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER5_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_SRCHIKEY_layer5_src_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER5_SRCHIKEY_layer5_src_hicolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER5_DSTLOKEY_UNION
 �ṹ˵��  : LAYER5_DSTLOKEY �Ĵ����ṹ���塣��ַƫ����:0x150����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_dst_locolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER5_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_DSTLOKEY_layer5_dst_locolorkey_START  (0)
#define SOC_DSS_OV6_LAYER5_DSTLOKEY_layer5_dst_locolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER5_DSTHIKEY_UNION
 �ṹ˵��  : LAYER5_DSTHIKEY �Ĵ����ṹ���塣��ַƫ����:0x154����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_dst_hicolorkey : 24; /* bit[0-23] :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER5_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_DSTHIKEY_layer5_dst_hicolorkey_START  (0)
#define SOC_DSS_OV6_LAYER5_DSTHIKEY_layer5_dst_hicolorkey_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER5_PATTERN_UNION
 �ṹ˵��  : LAYER5_PATTERN �Ĵ����ṹ���塣��ַƫ����:0x158����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_pattern : 32; /* bit[0-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER5_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_PATTERN_layer5_pattern_START  (0)
#define SOC_DSS_OV6_LAYER5_PATTERN_layer5_pattern_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER5_ALPHA_UNION
 �ṹ˵��  : LAYER5_ALPHA �Ĵ����ṹ���塣��ַƫ����:0x15C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_dst_global_alpha : 8;  /* bit[0-7]  :  */
        unsigned int  layer5_fix_mode         : 1;  /* bit[8]    :  */
        unsigned int  layer5_dst_pmode        : 1;  /* bit[9]    :  */
        unsigned int  layer5_off_dst          : 2;  /* bit[10-11]:  */
        unsigned int  layer5_dst_gmode        : 2;  /* bit[12-13]:  */
        unsigned int  layer5_dst_amode        : 2;  /* bit[14-15]:  */
        unsigned int  layer5_src_global_alpha : 8;  /* bit[16-23]:  */
        unsigned int  layer5_alpha_smode      : 1;  /* bit[24]   :  */
        unsigned int  layer5_src_pmode        : 1;  /* bit[25]   :  */
        unsigned int  layer5_src_lmode        : 1;  /* bit[26]   :  */
        unsigned int  layer5_off_src          : 1;  /* bit[27]   :  */
        unsigned int  layer5_src_gmode        : 2;  /* bit[28-29]:  */
        unsigned int  layer5_src_amode        : 2;  /* bit[30-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER5_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_global_alpha_START  (0)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_global_alpha_END    (7)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_fix_mode_START          (8)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_fix_mode_END            (8)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_pmode_START         (9)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_pmode_END           (9)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_off_dst_START           (10)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_off_dst_END             (11)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_gmode_START         (12)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_gmode_END           (13)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_amode_START         (14)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_amode_END           (15)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_global_alpha_START  (16)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_global_alpha_END    (23)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_alpha_smode_START       (24)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_alpha_smode_END         (24)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_pmode_START         (25)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_pmode_END           (25)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_lmode_START         (26)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_lmode_END           (26)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_off_src_START           (27)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_off_src_END             (27)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_gmode_START         (28)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_gmode_END           (29)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_amode_START         (30)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_amode_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER5_CFG_UNION
 �ṹ˵��  : LAYER5_CFG �Ĵ����ṹ���塣��ַƫ����:0x160����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_enable     : 1;  /* bit[0]    :  */
        unsigned int  reserved_0        : 3;  /* bit[1-3]  : ���� */
        unsigned int  layer5_trop_en    : 1;  /* bit[4]    :  */
        unsigned int  layer5_rop_en     : 1;  /* bit[5]    :  */
        unsigned int  reserved_1        : 2;  /* bit[6-7]  : ���� */
        unsigned int  layer5_src_cfg    : 1;  /* bit[8]    :  */
        unsigned int  reserved_2        : 3;  /* bit[9-11] : ���� */
        unsigned int  reserved_3        : 3;  /* bit[12-14]:  */
        unsigned int  reserved_4        : 1;  /* bit[15]   : ���� */
        unsigned int  layer5_auto_nosrc : 1;  /* bit[16]   :  */
        unsigned int  reserved_5        : 3;  /* bit[17-19]: ���� */
        unsigned int  layer5_trop_code  : 4;  /* bit[20-23]:  */
        unsigned int  layer5_rop_code   : 8;  /* bit[24-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER5_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_CFG_layer5_enable_START      (0)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_enable_END        (0)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_trop_en_START     (4)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_trop_en_END       (4)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_rop_en_START      (5)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_rop_en_END        (5)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_src_cfg_START     (8)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_src_cfg_END       (8)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_auto_nosrc_START  (16)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_auto_nosrc_END    (16)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_trop_code_START   (20)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_trop_code_END     (23)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_rop_code_START    (24)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_rop_code_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER5_PSPOS_UNION
 �ṹ˵��  : LAYER5_PSPOS �Ĵ����ṹ���塣��ַƫ����:0x164����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_pstartx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0     : 1;  /* bit[15]   : ���� */
        unsigned int  layer5_pstarty : 15; /* bit[16-30]:  */
        unsigned int  reserved_1     : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER5_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_PSPOS_layer5_pstartx_START  (0)
#define SOC_DSS_OV6_LAYER5_PSPOS_layer5_pstartx_END    (14)
#define SOC_DSS_OV6_LAYER5_PSPOS_layer5_pstarty_START  (16)
#define SOC_DSS_OV6_LAYER5_PSPOS_layer5_pstarty_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER5_PEPOS_UNION
 �ṹ˵��  : LAYER5_PEPOS �Ĵ����ṹ���塣��ַƫ����:0x168����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_pendx : 15; /* bit[0-14] :  */
        unsigned int  reserved_0   : 1;  /* bit[15]   : ���� */
        unsigned int  layer5_pendy : 15; /* bit[16-30]:  */
        unsigned int  reserved_1   : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_LAYER5_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_PEPOS_layer5_pendx_START  (0)
#define SOC_DSS_OV6_LAYER5_PEPOS_layer5_pendx_END    (14)
#define SOC_DSS_OV6_LAYER5_PEPOS_layer5_pendy_START  (16)
#define SOC_DSS_OV6_LAYER5_PEPOS_layer5_pendy_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER5_INFO_ALPHA_UNION
 �ṹ˵��  : LAYER5_INFO_ALPHA �Ĵ����ṹ���塣��ַƫ����:0x16C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_frame_end     : 1;  /* bit[0]    :  */
        unsigned int  layer5_nosrc         : 1;  /* bit[1]    :  */
        unsigned int  layer5_dstalpha_flag : 1;  /* bit[2]    :  */
        unsigned int  layer5_srcalpha_flag : 1;  /* bit[3]    :  */
        unsigned int  reserved_0           : 4;  /* bit[4-7]  : ���� */
        unsigned int  layer5_dstalpha_info : 8;  /* bit[8-15] :  */
        unsigned int  layer5_srcalpha_info : 8;  /* bit[16-23]:  */
        unsigned int  reserved_1           : 8;  /* bit[24-31]: ���� */
    } reg;
} SOC_DSS_OV6_LAYER5_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_frame_end_START      (0)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_frame_end_END        (0)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_nosrc_START          (1)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_nosrc_END            (1)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_dstalpha_flag_START  (2)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_dstalpha_flag_END    (2)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_srcalpha_flag_START  (3)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_srcalpha_flag_END    (3)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_dstalpha_info_START  (8)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_dstalpha_info_END    (15)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_srcalpha_info_START  (16)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_srcalpha_info_END    (23)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_UNION
 �ṹ˵��  : LAYER5_INFO_SRCCOLOR �Ĵ����ṹ���塣��ַƫ����:0x170����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_srccolor_flag : 1;  /* bit[0]   :  */
        unsigned int  reserved             : 7;  /* bit[1-7] : ���� */
        unsigned int  layer5_srccolor_info : 24; /* bit[8-31]:  */
    } reg;
} SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_layer5_srccolor_flag_START  (0)
#define SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_layer5_srccolor_flag_END    (0)
#define SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_layer5_srccolor_info_START  (8)
#define SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_layer5_srccolor_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER5_ST_INFO_UNION
 �ṹ˵��  : LAYER5_ST_INFO �Ĵ����ṹ���塣��ַƫ����:0x174����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_stall_info : 32; /* bit[0-31]: ��һ֡dss_clear ���³�istall_infoֵ */
    } reg;
} SOC_DSS_OV6_LAYER5_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_ST_INFO_layer5_stall_info_START  (0)
#define SOC_DSS_OV6_LAYER5_ST_INFO_layer5_stall_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_LAYER5_IST_INFO_UNION
 �ṹ˵��  : LAYER5_IST_INFO �Ĵ����ṹ���塣��ַƫ����:0x178����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  layer5_istall_info : 32; /* bit[0-31]: ��stall_info_en��Ч������һ֡�ڼ�(ov_dneed=1&&src_drdy=0)��������
                                                             ��dss_clear��Чʱ���� */
    } reg;
} SOC_DSS_OV6_LAYER5_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_IST_INFO_layer5_istall_info_START  (0)
#define SOC_DSS_OV6_LAYER5_IST_INFO_layer5_istall_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_BASE_ST_INFO_UNION
 �ṹ˵��  : BASE_ST_INFO �Ĵ����ṹ���塣��ַƫ����:0x17C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bs_stall_info : 32; /* bit[0-31]: ��һ֡dss_clear ���³�istall_infoֵ */
    } reg;
} SOC_DSS_OV6_BASE_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_BASE_ST_INFO_bs_stall_info_START  (0)
#define SOC_DSS_OV6_BASE_ST_INFO_bs_stall_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_BASE_IST_INFO_UNION
 �ṹ˵��  : BASE_IST_INFO �Ĵ����ṹ���塣��ַƫ����:0x180����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bs_istall_info : 32; /* bit[0-31]: ��stall_info_en��Ч������һ֡�ڼ�(ov_dneed=1&&src_drdy=0)��������
                                                         ��dss_clear��Чʱ���� */
    } reg;
} SOC_DSS_OV6_BASE_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_BASE_IST_INFO_bs_istall_info_START  (0)
#define SOC_DSS_OV6_BASE_IST_INFO_bs_istall_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_GATE_CTRL_UNION
 �ṹ˵��  : GATE_CTRL �Ĵ����ṹ���塣��ַƫ����:0x184����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov_core_gt    : 2;  /* bit[0-1] : [1]��1'b1 ��ʾ����ģ��Ĺ���ʱ��������ſ� 1'b0 ��ʾ����ģ��Ĺ���ʱ����Ӳ���Զ����� [0]��1'b0 ��ʾ������ʱ������ 1'b1 ��ʾ������ʱ�ӹر� */
        unsigned int  reserved_0    : 2;  /* bit[2-3] : ���� */
        unsigned int  stall_info_en : 1;  /* bit[4]   : 1:ʹ��ov����dneed���ߣ�drdyδ���ߵ�cycle��istall_info. */
        unsigned int  reserved_1    : 27; /* bit[5-31]: ���� */
    } reg;
} SOC_DSS_OV6_GATE_CTRL_UNION;
#endif
#define SOC_DSS_OV6_GATE_CTRL_ov_core_gt_START     (0)
#define SOC_DSS_OV6_GATE_CTRL_ov_core_gt_END       (1)
#define SOC_DSS_OV6_GATE_CTRL_stall_info_en_START  (4)
#define SOC_DSS_OV6_GATE_CTRL_stall_info_en_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_OV_RD_SHADOW_SEL_UNION
 �ṹ˵��  : OV_RD_SHADOW_SEL �Ĵ����ṹ���塣��ַƫ����:0x188����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov_rd_shadow_sel : 1;  /* bit[0]   : 1:��Ӱ�ӼĴ���
                                                           0���������Ĵ��� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} SOC_DSS_OV6_OV_RD_SHADOW_SEL_UNION;
#endif
#define SOC_DSS_OV6_OV_RD_SHADOW_SEL_ov_rd_shadow_sel_START  (0)
#define SOC_DSS_OV6_OV_RD_SHADOW_SEL_ov_rd_shadow_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_OV_CLK_SEL_UNION
 �ṹ˵��  : OV_CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x018C����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ѡ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov_clk_sel : 32; /* bit[0-31]: ��һ��ģ���ʱ��ѡ���źţ�
                                                     1����ʾǿ�ƴ�ʱ�ӡ�
                                                     0����ʾ��Ҫ���������Ӳ����ʱ��ʹ����������ر�ʱ��
                                                     bit31������abp��regģ��
                                                     ����λ���� */
    } reg;
} SOC_DSS_OV6_OV_CLK_SEL_UNION;
#endif
#define SOC_DSS_OV6_OV_CLK_SEL_ov_clk_sel_START  (0)
#define SOC_DSS_OV6_OV_CLK_SEL_ov_clk_sel_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_OV_CLK_EN_UNION
 �ṹ˵��  : OV_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x0190����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: һ��ģ��ʱ��ʹ���ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ov_clk_en : 32; /* bit[0-31]: ��һ��ģ������ʱ��ʹ���ź�
                                                    1����ʾ���ʱ��ʹ����Ч������Ӳ������
                                                    0����ʾ���ʱ��ʹ����Ч����ֹӲ������
                                                    ���� */
    } reg;
} SOC_DSS_OV6_OV_CLK_EN_UNION;
#endif
#define SOC_DSS_OV6_OV_CLK_EN_ov_clk_en_START  (0)
#define SOC_DSS_OV6_OV_CLK_EN_ov_clk_en_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_BLOCK_SIZE_UNION
 �ṹ˵��  : BLOCK_SIZE �Ĵ����ṹ���塣��ַƫ����:0x01A0����ֵ:0x7FFF0000�����:32
 �Ĵ���˵��: Block��ͼ��߶�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 16; /* bit[0-15] : ���� */
        unsigned int  block_height : 15; /* bit[16-30]: overlay �ֿ�ͼ����±�������ڻ������ص�����ֵ����������㿪ʼ�� */
        unsigned int  reserved_1   : 1;  /* bit[31]   : ���� */
    } reg;
} SOC_DSS_OV6_BLOCK_SIZE_UNION;
#endif
#define SOC_DSS_OV6_BLOCK_SIZE_block_height_START  (16)
#define SOC_DSS_OV6_BLOCK_SIZE_block_height_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_BLOCK_DBG_UNION
 �ṹ˵��  : BLOCK_DBG �Ĵ����ṹ���塣��ַƫ����:0x01A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ֿ��ν�ɲ�Ĵ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  block_dbg : 32; /* bit[0-31]: bit[0] block_disable
                                                    1'b1 ����֧�ַֿ�
                                                    1'b0 �� ֧�ַֿ� */
    } reg;
} SOC_DSS_OV6_BLOCK_DBG_UNION;
#endif
#define SOC_DSS_OV6_BLOCK_DBG_block_dbg_START  (0)
#define SOC_DSS_OV6_BLOCK_DBG_block_dbg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_DSS_OV6_REG_DEFAULT_UNION
 �ṹ˵��  : REG_DEFAULT �Ĵ����ṹ���塣��ַƫ����:0x01A8����ֵ:0x00000000�����:32
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
} SOC_DSS_OV6_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_OV6_REG_DEFAULT_reg_default_START  (0)
#define SOC_DSS_OV6_REG_DEFAULT_reg_default_END    (0)






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

#endif /* end of soc_dss_ov6_interface.h */
