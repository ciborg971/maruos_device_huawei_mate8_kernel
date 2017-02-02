/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_crgperiph_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-04-08 11:44:11
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��4��8��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_CRGPERIPH.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_CRGPERIPH_INTERFACE_H__
#define __SOC_CRGPERIPH_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_CRGPERIPH
 ****************************************************************************/
/* �Ĵ���˵��������ʱ��ʹ�ܼĴ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PEREN0_UNION */
#define SOC_CRGPERIPH_PEREN0_ADDR(base)               ((base) + (0x000))

/* �Ĵ���˵��������ʱ�ӽ�ֹ�Ĵ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERDIS0_UNION */
#define SOC_CRGPERIPH_PERDIS0_ADDR(base)              ((base) + (0x004))

/* �Ĵ���˵��������ʱ��ʹ��״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERCLKEN0_UNION */
#define SOC_CRGPERIPH_PERCLKEN0_ADDR(base)            ((base) + (0x008))

/* �Ĵ���˵��������ʱ������״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERSTAT0_UNION */
#define SOC_CRGPERIPH_PERSTAT0_ADDR(base)             ((base) + (0x00C))

/* �Ĵ���˵��������ʱ��ʹ�ܼĴ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PEREN1_UNION */
#define SOC_CRGPERIPH_PEREN1_ADDR(base)               ((base) + (0x010))

/* �Ĵ���˵��������ʱ�ӽ�ֹ�Ĵ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERDIS1_UNION */
#define SOC_CRGPERIPH_PERDIS1_ADDR(base)              ((base) + (0x014))

/* �Ĵ���˵��������ʱ��ʹ��״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERCLKEN1_UNION */
#define SOC_CRGPERIPH_PERCLKEN1_ADDR(base)            ((base) + (0x018))

/* �Ĵ���˵��������ʱ������״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERSTAT1_UNION */
#define SOC_CRGPERIPH_PERSTAT1_ADDR(base)             ((base) + (0x01C))

/* �Ĵ���˵��������ʱ��ʹ�ܼĴ���2��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PEREN2_UNION */
#define SOC_CRGPERIPH_PEREN2_ADDR(base)               ((base) + (0x020))

/* �Ĵ���˵��������ʱ�ӽ�ֹ�Ĵ���2��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERDIS2_UNION */
#define SOC_CRGPERIPH_PERDIS2_ADDR(base)              ((base) + (0x024))

/* �Ĵ���˵��������ʱ��ʹ��״̬�Ĵ���2��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERCLKEN2_UNION */
#define SOC_CRGPERIPH_PERCLKEN2_ADDR(base)            ((base) + (0x028))

/* �Ĵ���˵��������ʱ������״̬�Ĵ���2��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERSTAT2_UNION */
#define SOC_CRGPERIPH_PERSTAT2_ADDR(base)             ((base) + (0x02C))

/* �Ĵ���˵��������ʱ��ʹ�ܼĴ���3��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PEREN3_UNION */
#define SOC_CRGPERIPH_PEREN3_ADDR(base)               ((base) + (0x030))

/* �Ĵ���˵��������ʱ�ӽ�ֹ�Ĵ���3��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERDIS3_UNION */
#define SOC_CRGPERIPH_PERDIS3_ADDR(base)              ((base) + (0x034))

/* �Ĵ���˵��������ʱ��ʹ��״̬�Ĵ���3��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERCLKEN3_UNION */
#define SOC_CRGPERIPH_PERCLKEN3_ADDR(base)            ((base) + (0x038))

/* �Ĵ���˵��������ʱ������״̬�Ĵ���3��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERSTAT3_UNION */
#define SOC_CRGPERIPH_PERSTAT3_ADDR(base)             ((base) + (0x03C))

/* �Ĵ���˵��������ʱ��ʹ�ܼĴ���4��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PEREN4_UNION */
#define SOC_CRGPERIPH_PEREN4_ADDR(base)               ((base) + (0x040))

/* �Ĵ���˵��������ʱ�ӽ�ֹ�Ĵ���4��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERDIS4_UNION */
#define SOC_CRGPERIPH_PERDIS4_ADDR(base)              ((base) + (0x044))

/* �Ĵ���˵��������ʱ��ʹ��״̬�Ĵ���4��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERCLKEN4_UNION */
#define SOC_CRGPERIPH_PERCLKEN4_ADDR(base)            ((base) + (0x048))

/* �Ĵ���˵��������ʱ������״̬�Ĵ���4��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERSTAT4_UNION */
#define SOC_CRGPERIPH_PERSTAT4_ADDR(base)             ((base) + (0x04C))

/* �Ĵ���˵��������ʱ��ʹ�ܼĴ���5��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PEREN5_UNION */
#define SOC_CRGPERIPH_PEREN5_ADDR(base)               ((base) + (0x050))

/* �Ĵ���˵��������ʱ�ӽ�ֹ�Ĵ���5��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERDIS5_UNION */
#define SOC_CRGPERIPH_PERDIS5_ADDR(base)              ((base) + (0x054))

/* �Ĵ���˵��������ʱ��ʹ��״̬�Ĵ���5��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERCLKEN5_UNION */
#define SOC_CRGPERIPH_PERCLKEN5_ADDR(base)            ((base) + (0x058))

/* �Ĵ���˵��������ʱ������״̬�Ĵ���5��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERSTAT5_UNION */
#define SOC_CRGPERIPH_PERSTAT5_ADDR(base)             ((base) + (0x05C))

/* �Ĵ���˵����������λʹ�ܼĴ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTEN0_UNION */
#define SOC_CRGPERIPH_PERRSTEN0_ADDR(base)            ((base) + (0x060))

/* �Ĵ���˵����������λ����Ĵ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTDIS0_UNION */
#define SOC_CRGPERIPH_PERRSTDIS0_ADDR(base)           ((base) + (0x064))

/* �Ĵ���˵����������λ״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTSTAT0_UNION */
#define SOC_CRGPERIPH_PERRSTSTAT0_ADDR(base)          ((base) + (0x068))

/* �Ĵ���˵����������λʹ�ܼĴ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTEN1_UNION */
#define SOC_CRGPERIPH_PERRSTEN1_ADDR(base)            ((base) + (0x06C))

/* �Ĵ���˵����������λ����Ĵ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTDIS1_UNION */
#define SOC_CRGPERIPH_PERRSTDIS1_ADDR(base)           ((base) + (0x070))

/* �Ĵ���˵����������λ״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTSTAT1_UNION */
#define SOC_CRGPERIPH_PERRSTSTAT1_ADDR(base)          ((base) + (0x074))

/* �Ĵ���˵����������λʹ�ܼĴ���2��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTEN2_UNION */
#define SOC_CRGPERIPH_PERRSTEN2_ADDR(base)            ((base) + (0x078))

/* �Ĵ���˵����������λ����Ĵ���2��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTDIS2_UNION */
#define SOC_CRGPERIPH_PERRSTDIS2_ADDR(base)           ((base) + (0x07C))

/* �Ĵ���˵����������λ״̬�Ĵ���2��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTSTAT2_UNION */
#define SOC_CRGPERIPH_PERRSTSTAT2_ADDR(base)          ((base) + (0x080))

/* �Ĵ���˵����������λʹ�ܼĴ���3��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTEN3_UNION */
#define SOC_CRGPERIPH_PERRSTEN3_ADDR(base)            ((base) + (0x084))

/* �Ĵ���˵����������λ����Ĵ���3��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTDIS3_UNION */
#define SOC_CRGPERIPH_PERRSTDIS3_ADDR(base)           ((base) + (0x088))

/* �Ĵ���˵����������λ״̬�Ĵ���3��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTSTAT3_UNION */
#define SOC_CRGPERIPH_PERRSTSTAT3_ADDR(base)          ((base) + (0x008C))

/* �Ĵ���˵����������λʹ�ܼĴ���4��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTEN4_UNION */
#define SOC_CRGPERIPH_PERRSTEN4_ADDR(base)            ((base) + (0x090))

/* �Ĵ���˵����������λ����Ĵ���4��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTDIS4_UNION */
#define SOC_CRGPERIPH_PERRSTDIS4_ADDR(base)           ((base) + (0x094))

/* �Ĵ���˵����������λ״̬�Ĵ���4��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTSTAT4_UNION */
#define SOC_CRGPERIPH_PERRSTSTAT4_ADDR(base)          ((base) + (0x098))

/* �Ĵ���˵����������λʹ�ܼĴ���5��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTEN5_UNION */
#define SOC_CRGPERIPH_PERRSTEN5_ADDR(base)            ((base) + (0x09C))

/* �Ĵ���˵����������λ����Ĵ���5��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTDIS5_UNION */
#define SOC_CRGPERIPH_PERRSTDIS5_ADDR(base)           ((base) + (0x0A0))

/* �Ĵ���˵����������λ״̬�Ĵ���5��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERRSTSTAT5_UNION */
#define SOC_CRGPERIPH_PERRSTSTAT5_ADDR(base)          ((base) + (0x0A4))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV0_UNION */
#define SOC_CRGPERIPH_CLKDIV0_ADDR(base)              ((base) + (0x0A8))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV1_UNION */
#define SOC_CRGPERIPH_CLKDIV1_ADDR(base)              ((base) + (0x0AC))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���2��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV2_UNION */
#define SOC_CRGPERIPH_CLKDIV2_ADDR(base)              ((base) + (0x0B0))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���3��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV3_UNION */
#define SOC_CRGPERIPH_CLKDIV3_ADDR(base)              ((base) + (0x0B4))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���4��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV4_UNION */
#define SOC_CRGPERIPH_CLKDIV4_ADDR(base)              ((base) + (0x0B8))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���5��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV5_UNION */
#define SOC_CRGPERIPH_CLKDIV5_ADDR(base)              ((base) + (0x0BC))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���6��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV6_UNION */
#define SOC_CRGPERIPH_CLKDIV6_ADDR(base)              ((base) + (0x0C0))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���7��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV7_UNION */
#define SOC_CRGPERIPH_CLKDIV7_ADDR(base)              ((base) + (0x0C4))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���8��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV8_UNION */
#define SOC_CRGPERIPH_CLKDIV8_ADDR(base)              ((base) + (0x0C8))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���9��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV9_UNION */
#define SOC_CRGPERIPH_CLKDIV9_ADDR(base)              ((base) + (0x0CC))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���10��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV10_UNION */
#define SOC_CRGPERIPH_CLKDIV10_ADDR(base)             ((base) + (0x0D0))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���11��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV11_UNION */
#define SOC_CRGPERIPH_CLKDIV11_ADDR(base)             ((base) + (0x0D4))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���12��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV12_UNION */
#define SOC_CRGPERIPH_CLKDIV12_ADDR(base)             ((base) + (0x0D8))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���13��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV13_UNION */
#define SOC_CRGPERIPH_CLKDIV13_ADDR(base)             ((base) + (0x0DC))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���14��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV14_UNION */
#define SOC_CRGPERIPH_CLKDIV14_ADDR(base)             ((base) + (0x0E0))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���15��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV15_UNION */
#define SOC_CRGPERIPH_CLKDIV15_ADDR(base)             ((base) + (0x0E4))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���16��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV16_UNION */
#define SOC_CRGPERIPH_CLKDIV16_ADDR(base)             ((base) + (0x0E8))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���17��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV17_UNION */
#define SOC_CRGPERIPH_CLKDIV17_ADDR(base)             ((base) + (0x0EC))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���18��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV18_UNION */
#define SOC_CRGPERIPH_CLKDIV18_ADDR(base)             ((base) + (0x0F0))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���19��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV19_UNION */
#define SOC_CRGPERIPH_CLKDIV19_ADDR(base)             ((base) + (0x0F4))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���20��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV20_UNION */
#define SOC_CRGPERIPH_CLKDIV20_ADDR(base)             ((base) + (0x0F8))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���21��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV21_UNION */
#define SOC_CRGPERIPH_CLKDIV21_ADDR(base)             ((base) + (0x0FC))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���22��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV22_UNION */
#define SOC_CRGPERIPH_CLKDIV22_ADDR(base)             ((base) + (0x100))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���23��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV23_UNION */
#define SOC_CRGPERIPH_CLKDIV23_ADDR(base)             ((base) + (0x104))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���24��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV24_UNION */
#define SOC_CRGPERIPH_CLKDIV24_ADDR(base)             ((base) + (0x108))

/* �Ĵ���˵����ʱ�ӷ�Ƶ�ȿ��ƼĴ���25��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CLKDIV25_UNION */
#define SOC_CRGPERIPH_CLKDIV25_ADDR(base)             ((base) + (0x10C))

/* �Ĵ���˵��������״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PER_STAT0_UNION */
#define SOC_CRGPERIPH_PER_STAT0_ADDR(base)            ((base) + (0x110))

/* �Ĵ���˵��������״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PER_STAT1_UNION */
#define SOC_CRGPERIPH_PER_STAT1_ADDR(base)            ((base) + (0x114))

/* �Ĵ���˵��������״̬�Ĵ���2��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PER_STAT2_UNION */
#define SOC_CRGPERIPH_PER_STAT2_ADDR(base)            ((base) + (0x118))

/* �Ĵ���˵��������״̬�Ĵ���3��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PER_STAT3_UNION */
#define SOC_CRGPERIPH_PER_STAT3_ADDR(base)            ((base) + (0x11C))

/* �Ĵ���˵����������ƼĴ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERCTRL0_UNION */
#define SOC_CRGPERIPH_PERCTRL0_ADDR(base)             ((base) + (0x120))

/* �Ĵ���˵����������ƼĴ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERCTRL1_UNION */
#define SOC_CRGPERIPH_PERCTRL1_ADDR(base)             ((base) + (0x124))

/* �Ĵ���˵����������ƼĴ���2��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERCTRL2_UNION */
#define SOC_CRGPERIPH_PERCTRL2_ADDR(base)             ((base) + (0x128))

/* �Ĵ���˵����������ƼĴ���3��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERCTRL3_UNION */
#define SOC_CRGPERIPH_PERCTRL3_ADDR(base)             ((base) + (0x12C))

/* �Ĵ���˵����������ƼĴ���4��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERCTRL4_UNION */
#define SOC_CRGPERIPH_PERCTRL4_ADDR(base)             ((base) + (0x130))

/* �Ĵ���˵����������ƼĴ���5��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERCTRL5_UNION */
#define SOC_CRGPERIPH_PERCTRL5_ADDR(base)             ((base) + (0x134))

/* �Ĵ���˵����������ƼĴ���6��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERCTRL6_UNION */
#define SOC_CRGPERIPH_PERCTRL6_ADDR(base)             ((base) + (0x138))

/* �Ĵ���˵��������TIME���ƼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERTIMECTRL_UNION */
#define SOC_CRGPERIPH_PERTIMECTRL_ADDR(base)          ((base) + (0x140))

/* �Ĵ���˵����������ϵͳISOʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_ISOEN_UNION */
#define SOC_CRGPERIPH_ISOEN_ADDR(base)                ((base) + (0x144))

/* �Ĵ���˵����������ϵͳISOʹ�ܳ����Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_ISODIS_UNION */
#define SOC_CRGPERIPH_ISODIS_ADDR(base)               ((base) + (0x148))

/* �Ĵ���˵����������ϵͳISOʹ��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_ISOSTAT_UNION */
#define SOC_CRGPERIPH_ISOSTAT_ADDR(base)              ((base) + (0x14C))

/* �Ĵ���˵����������ϵͳ��Դʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERPWREN_UNION */
#define SOC_CRGPERIPH_PERPWREN_ADDR(base)             ((base) + (0x150))

/* �Ĵ���˵����������ϵͳ��Դʹ�ܳ����Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERPWRDIS_UNION */
#define SOC_CRGPERIPH_PERPWRDIS_ADDR(base)            ((base) + (0x154))

/* �Ĵ���˵����������ϵͳ��Դʹ��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERPWRSTAT_UNION */
#define SOC_CRGPERIPH_PERPWRSTAT_ADDR(base)           ((base) + (0x158))

/* �Ĵ���˵����������ϵͳ���յ�Դ״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERPWRACK_UNION */
#define SOC_CRGPERIPH_PERPWRACK_ADDR(base)            ((base) + (0x15C))

/* �Ĵ���˵����A53 CLUSTER��ϵͳʱ��ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_CLKEN_UNION */
#define SOC_CRGPERIPH_A53_CLKEN_ADDR(base)            ((base) + (0x160))

/* �Ĵ���˵����A53 CLUSTER��ϵͳ��λʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_RSTEN_UNION */
#define SOC_CRGPERIPH_A53_RSTEN_ADDR(base)            ((base) + (0x164))

/* �Ĵ���˵����A53 CLUSTER��ϵͳ��λ����Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_RSTDIS_UNION */
#define SOC_CRGPERIPH_A53_RSTDIS_ADDR(base)           ((base) + (0x168))

/* �Ĵ���˵����A53 CLUSTER��ϵͳ��λʹ��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_RSTSTAT_UNION */
#define SOC_CRGPERIPH_A53_RSTSTAT_ADDR(base)          ((base) + (0x16C))

/* �Ĵ���˵����A53 CLUSTER ADB�͹��ļĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_ADBLPSTAT_UNION */
#define SOC_CRGPERIPH_A53_ADBLPSTAT_ADDR(base)        ((base) + (0x174))

/* �Ĵ���˵����A53 CLUSTER�������üĴ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_CTRL0_UNION */
#define SOC_CRGPERIPH_A53_CTRL0_ADDR(base)            ((base) + (0x178))

/* �Ĵ���˵����A53 CLUSTER�������üĴ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_CTRL1_UNION */
#define SOC_CRGPERIPH_A53_CTRL1_ADDR(base)            ((base) + (0x17C))

/* �Ĵ���˵����A53 CLUSTER�������üĴ���2��
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_CTRL2_UNION */
#define SOC_CRGPERIPH_A53_CTRL2_ADDR(base)            ((base) + (0x180))

/* �Ĵ���˵����A53 CLUSTER״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_STAT_UNION */
#define SOC_CRGPERIPH_A53_STAT_ADDR(base)             ((base) + (0x194))

/* �Ĵ���˵����A57 CLUSTER��ϵͳʱ��ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_CLKEN_UNION */
#define SOC_CRGPERIPH_MAIA_CLKEN_ADDR(base)           ((base) + (0x1C0))

/* �Ĵ���˵����A57 CLUSTER��ϵͳ��λʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_RSTEN_UNION */
#define SOC_CRGPERIPH_MAIA_RSTEN_ADDR(base)           ((base) + (0x1C4))

/* �Ĵ���˵����A57 CLUSTER��ϵͳ��λ����Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_RSTDIS_UNION */
#define SOC_CRGPERIPH_MAIA_RSTDIS_ADDR(base)          ((base) + (0x1C8))

/* �Ĵ���˵����A57 CLUSTER��ϵͳ��λʹ��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_RSTSTAT_UNION */
#define SOC_CRGPERIPH_MAIA_RSTSTAT_ADDR(base)         ((base) + (0x1CC))

/* �Ĵ���˵����A57 CLUSTER ADB�͹��ļĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_ADBLPSTAT_UNION */
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_ADDR(base)       ((base) + (0x1D4))

/* �Ĵ���˵����A57 CLUSTER�������üĴ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_CTRL0_UNION */
#define SOC_CRGPERIPH_MAIA_CTRL0_ADDR(base)           ((base) + (0x1D8))

/* �Ĵ���˵����A57 CLUSTER�������üĴ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_CTRL1_UNION */
#define SOC_CRGPERIPH_MAIA_CTRL1_ADDR(base)           ((base) + (0x1DC))

/* �Ĵ���˵����A57 CLUSTER�������üĴ���2��
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_CTRL2_UNION */
#define SOC_CRGPERIPH_MAIA_CTRL2_ADDR(base)           ((base) + (0x1E0))

/* �Ĵ���˵����A57 CLUSTER״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_STAT_UNION */
#define SOC_CRGPERIPH_MAIA_STAT_ADDR(base)            ((base) + (0x1F4))

/* �Ĵ���˵����A57 CLUSTER״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_STAT_1_UNION */
#define SOC_CRGPERIPH_MAIA_STAT_1_ADDR(base)          ((base) + (0x1F8))

/* �Ĵ���˵����core sight״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_CORESIGHTSTAT_UNION */
#define SOC_CRGPERIPH_CORESIGHTSTAT_ADDR(base)        ((base) + (0x200))

/* �Ĵ���˵����core sight�͹��ļĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_CORESIGHTLPSTAT_UNION */
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_ADDR(base)      ((base) + (0x204))

/* �Ĵ���˵����core sight�������üĴ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CORESIGHTCTRL0_UNION */
#define SOC_CRGPERIPH_CORESIGHTCTRL0_ADDR(base)       ((base) + (0x208))

/* �Ĵ���˵����core sight ETF�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_CORESIGHTETFINT_UNION */
#define SOC_CRGPERIPH_CORESIGHTETFINT_ADDR(base)      ((base) + (0x20C))

/* �Ĵ���˵����core sight ETR�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_CORESIGHTETRINT_UNION */
#define SOC_CRGPERIPH_CORESIGHTETRINT_ADDR(base)      ((base) + (0x210))

/* �Ĵ���˵����CCI400״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CCI400STAT1_UNION */
#define SOC_CRGPERIPH_CCI400STAT1_ADDR(base)          ((base) + (0x21C))

/* �Ĵ���˵����ADB400״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_ADB400STAT_UNION */
#define SOC_CRGPERIPH_ADB400STAT_ADDR(base)           ((base) + (0x220))

/* �Ĵ���˵����CCI400�������üĴ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CCI400CTRL0_UNION */
#define SOC_CRGPERIPH_CCI400CTRL0_ADDR(base)          ((base) + (0x228))

/* �Ĵ���˵����CCI400�������üĴ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_CCI400CTRL1_UNION */
#define SOC_CRGPERIPH_CCI400CTRL1_ADDR(base)          ((base) + (0x22C))

/* �Ĵ���˵����CCI400״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_CCI400STAT_UNION */
#define SOC_CRGPERIPH_CCI400STAT_ADDR(base)           ((base) + (0x230))

/* �Ĵ���˵����G3D ADB0�͹��ļĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_G3D_0_ADBLPSTAT_UNION */
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_ADDR(base)      ((base) + (0x234))

/* �Ĵ���˵����G3D ADB1�͹��ļĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_G3D_1_ADBLPSTAT_UNION */
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_ADDR(base)      ((base) + (0x238))

/* �Ĵ���˵��������IP����������byapss���ƼĴ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_IPCLKRST_BYPASS0_UNION */
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_ADDR(base)     ((base) + (0x240))

/* �Ĵ���˵��������IP����������byapss���ƼĴ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_IPCLKRST_BYPASS1_UNION */
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ADDR(base)     ((base) + (0x244))

/* �Ĵ���˵��������IP����������byapss���ƼĴ���2��
   λ����UNION�ṹ:  SOC_CRGPERIPH_IPCLKRST_BYPASS2_UNION */
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_ADDR(base)     ((base) + (0x248))

/* �Ĵ���˵����A53���µ�״̬��ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_PDCEN_UNION */
#define SOC_CRGPERIPH_A53_PDCEN_ADDR(base)            ((base) + (0x260))

/* �Ĵ���˵����A53�Ӻ����µ�����ж�ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_COREPWRINTEN_UNION */
#define SOC_CRGPERIPH_A53_COREPWRINTEN_ADDR(base)     ((base) + (0x264))

/* �Ĵ���˵����A53�Ӻ����µ�����ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_COREPWRINTSTAT_UNION */
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_ADDR(base)   ((base) + (0x268))

/* �Ĵ���˵����A53�Ӻ�GIC�ж����μĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_COREGICMASK_UNION */
#define SOC_CRGPERIPH_A53_COREGICMASK_ADDR(base)      ((base) + (0x26C))

/* �Ĵ���˵����A53�Ӻ��ϵ�����Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_COREPOWERUP_UNION */
#define SOC_CRGPERIPH_A53_COREPOWERUP_ADDR(base)      ((base) + (0x270))

/* �Ĵ���˵����A53�Ӻ��µ�����Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_COREPOWERDN_UNION */
#define SOC_CRGPERIPH_A53_COREPOWERDN_ADDR(base)      ((base) + (0x274))

/* �Ĵ���˵����A53�Ӻ�״̬��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_COREPOWERSTAT_UNION */
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_ADDR(base)    ((base) + (0x278))

/* �Ĵ���˵����A53�Ӻ��ϵ�ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_COREPWRUPTIME_UNION */
#define SOC_CRGPERIPH_A53_COREPWRUPTIME_ADDR(base)    ((base) + (0x27C))

/* �Ĵ���˵����A53�Ӻ��µ�ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_COREPWRDNTIME_UNION */
#define SOC_CRGPERIPH_A53_COREPWRDNTIME_ADDR(base)    ((base) + (0x280))

/* �Ĵ���˵����A53�Ӻ�ǯλ����ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_COREISOTIME_UNION */
#define SOC_CRGPERIPH_A53_COREISOTIME_ADDR(base)      ((base) + (0x284))

/* �Ĵ���˵����A53�Ӻ�DBG����ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_COREDBGTIME_UNION */
#define SOC_CRGPERIPH_A53_COREDBGTIME_ADDR(base)      ((base) + (0x288))

/* �Ĵ���˵����A53�Ӻ˸�λʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_CORERSTTIME_UNION */
#define SOC_CRGPERIPH_A53_CORERSTTIME_ADDR(base)      ((base) + (0x28C))

/* �Ĵ���˵����A53�Ӻ˽⸴λʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_COREURSTTIME_UNION */
#define SOC_CRGPERIPH_A53_COREURSTTIME_ADDR(base)     ((base) + (0x290))

/* �Ĵ���˵����MAIA���µ�״̬��ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_PDCEN_UNION */
#define SOC_CRGPERIPH_MAIA_PDCEN_ADDR(base)           ((base) + (0x300))

/* �Ĵ���˵����MAIA_�Ӻ����µ�����ж�ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_COREPWRINTEN_UNION */
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_ADDR(base)    ((base) + (0x304))

/* �Ĵ���˵����MAIA�Ӻ����µ�����ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_UNION */
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_ADDR(base)  ((base) + (0x308))

/* �Ĵ���˵����MAIA�Ӻ�GIC�ж����μĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_COREGICMASK_UNION */
#define SOC_CRGPERIPH_MAIA_COREGICMASK_ADDR(base)     ((base) + (0x30C))

/* �Ĵ���˵����MAIA�Ӻ��ϵ�����Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_COREPOWERUP_UNION */
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_ADDR(base)     ((base) + (0x310))

/* �Ĵ���˵����MAIA�Ӻ��µ�����Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_COREPOWERDN_UNION */
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_ADDR(base)     ((base) + (0x314))

/* �Ĵ���˵����MAIA�Ӻ�״̬��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_COREPOWERSTAT_UNION */
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_ADDR(base)   ((base) + (0x318))

/* �Ĵ���˵����MAIA�Ӻ��ϵ�ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_COREPWRUPTIME_UNION */
#define SOC_CRGPERIPH_MAIA_COREPWRUPTIME_ADDR(base)   ((base) + (0x31C))

/* �Ĵ���˵����MAIA�Ӻ��µ�ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_COREPWRDNTIME_UNION */
#define SOC_CRGPERIPH_MAIA_COREPWRDNTIME_ADDR(base)   ((base) + (0x320))

/* �Ĵ���˵����MAIA�Ӻ�ǯλ����ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_COREISOTIME_UNION */
#define SOC_CRGPERIPH_MAIA_COREISOTIME_ADDR(base)     ((base) + (0x324))

/* �Ĵ���˵����MAIA�Ӻ�DBG����ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_COREDBGTIME_UNION */
#define SOC_CRGPERIPH_MAIA_COREDBGTIME_ADDR(base)     ((base) + (0x328))

/* �Ĵ���˵����MAIA�Ӻ˸�λʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_CORERSTTIME_UNION */
#define SOC_CRGPERIPH_MAIA_CORERSTTIME_ADDR(base)     ((base) + (0x32C))

/* �Ĵ���˵����MAIA�Ӻ˽⸴λʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_COREURSTTIME_UNION */
#define SOC_CRGPERIPH_MAIA_COREURSTTIME_ADDR(base)    ((base) + (0x330))

/* �Ĵ���˵����ISPA7��ϵͳʱ��ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_ISPA7_CLKEN_UNION */
#define SOC_CRGPERIPH_ISPA7_CLKEN_ADDR(base)          ((base) + (0x340))

/* �Ĵ���˵����ISPA7��ϵͳ��λʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_ISPA7_RSTEN_UNION */
#define SOC_CRGPERIPH_ISPA7_RSTEN_ADDR(base)          ((base) + (0x344))

/* �Ĵ���˵����ISPA7��ϵͳ��λ����Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_ISPA7_RSTDIS_UNION */
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ADDR(base)         ((base) + (0x348))

/* �Ĵ���˵����ISPA7��ϵͳ��λʹ��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_ISPA7_RSTSTAT_UNION */
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ADDR(base)        ((base) + (0x34C))

/* �Ĵ���˵����ISPA7״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_ISPA7_STAT_UNION */
#define SOC_CRGPERIPH_ISPA7_STAT_ADDR(base)           ((base) + (0x354))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV0_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV0_ADDR(base)        ((base) + (0x360))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���1��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV1_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV1_ADDR(base)        ((base) + (0x364))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���2��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV2_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV2_ADDR(base)        ((base) + (0x368))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���3��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV3_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV3_ADDR(base)        ((base) + (0x36C))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���4��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV4_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV4_ADDR(base)        ((base) + (0x370))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���5��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV5_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV5_ADDR(base)        ((base) + (0x374))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���6��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV6_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV6_ADDR(base)        ((base) + (0x378))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���7��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV7_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV7_ADDR(base)        ((base) + (0x37C))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���8��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV8_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV8_ADDR(base)        ((base) + (0x380))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���9��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV9_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV9_ADDR(base)        ((base) + (0x384))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���10��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV10_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV10_ADDR(base)       ((base) + (0x388))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���11��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV11_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV11_ADDR(base)       ((base) + (0x38C))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���12��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV12_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV12_ADDR(base)       ((base) + (0x390))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���13��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV13_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV13_ADDR(base)       ((base) + (0x394))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���14��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV14_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV14_ADDR(base)       ((base) + (0x398))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���15��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV15_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV15_ADDR(base)       ((base) + (0x39C))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���ACPU��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV_ACPU_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_ADDR(base)    ((base) + (0x404))

/* �Ĵ���˵���������Զ���Ƶ���ƼĴ���MCPU��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERI_AUTODIV_MCPU_UNION */
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_ADDR(base)    ((base) + (0x408))

/* �Ĵ���˵��������ʱ��ʹ�ܼĴ���6��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PEREN6_UNION */
#define SOC_CRGPERIPH_PEREN6_ADDR(base)               ((base) + (0x410))

/* �Ĵ���˵��������ʱ�ӽ�ֹ�Ĵ���6��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERDIS6_UNION */
#define SOC_CRGPERIPH_PERDIS6_ADDR(base)              ((base) + (0x414))

/* �Ĵ���˵��������ʱ��ʹ��״̬�Ĵ���6��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERCLKEN6_UNION */
#define SOC_CRGPERIPH_PERCLKEN6_ADDR(base)            ((base) + (0x418))

/* �Ĵ���˵��������ʱ������״̬�Ĵ���6��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERSTAT6_UNION */
#define SOC_CRGPERIPH_PERSTAT6_ADDR(base)             ((base) + (0x41C))

/* �Ĵ���˵��������ʱ��ʹ�ܼĴ���7��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PEREN7_UNION */
#define SOC_CRGPERIPH_PEREN7_ADDR(base)               ((base) + (0x420))

/* �Ĵ���˵��������ʱ�ӽ�ֹ�Ĵ���7��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERDIS7_UNION */
#define SOC_CRGPERIPH_PERDIS7_ADDR(base)              ((base) + (0x424))

/* �Ĵ���˵��������ʱ��ʹ��״̬�Ĵ���7��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERCLKEN7_UNION */
#define SOC_CRGPERIPH_PERCLKEN7_ADDR(base)            ((base) + (0x428))

/* �Ĵ���˵��������ʱ������״̬�Ĵ���7��
   λ����UNION�ṹ:  SOC_CRGPERIPH_PERSTAT7_UNION */
#define SOC_CRGPERIPH_PERSTAT7_ADDR(base)             ((base) + (0x42C))

/* �Ĵ���˵����IVP��ȫ��λʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_IVP_SEC_RSTEN_UNION */
#define SOC_CRGPERIPH_IVP_SEC_RSTEN_ADDR(base)        ((base) + (0xC00))

/* �Ĵ���˵����IVP��ȫ��λ����Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_IVP_SEC_RSTDIS_UNION */
#define SOC_CRGPERIPH_IVP_SEC_RSTDIS_ADDR(base)       ((base) + (0xC04))

/* �Ĵ���˵����IVP��ȫ��λʹ��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_IVP_SEC_RSTSTAT_UNION */
#define SOC_CRGPERIPH_IVP_SEC_RSTSTAT_ADDR(base)      ((base) + (0xC08))

/* �Ĵ���˵����ISP��ȫ��λʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_ISP_SEC_RSTEN_UNION */
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ADDR(base)        ((base) + (0xC80))

/* �Ĵ���˵����ISP��ȫ��λ����Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_ISP_SEC_RSTDIS_UNION */
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ADDR(base)       ((base) + (0xC84))

/* �Ĵ���˵����ISP��ȫ��λ״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_ISP_SEC_RSTSTAT_UNION */
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ADDR(base)      ((base) + (0xC88))

/* �Ĵ���˵����ISPA7�������üĴ���0��
   λ����UNION�ṹ:  SOC_CRGPERIPH_ISPA7_CTRL0_UNION */
#define SOC_CRGPERIPH_ISPA7_CTRL0_ADDR(base)          ((base) + (0xC90))

/* �Ĵ���˵����MODEM��ȫ��λʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MDM_SEC_RSTEN_UNION */
#define SOC_CRGPERIPH_MDM_SEC_RSTEN_ADDR(base)        ((base) + (0xD00))

/* �Ĵ���˵����MODEM��ȫ��λ����Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MDM_SEC_RSTDIS_UNION */
#define SOC_CRGPERIPH_MDM_SEC_RSTDIS_ADDR(base)       ((base) + (0xD04))

/* �Ĵ���˵����MODEM��ȫ��λʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_MDM_SEC_RSTSTAT_UNION */
#define SOC_CRGPERIPH_MDM_SEC_RSTSTAT_ADDR(base)      ((base) + (0xD08))

/* �Ĵ���˵����A53 CLUSTER�������üĴ���3��
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_CTRL3_UNION */
#define SOC_CRGPERIPH_A53_CTRL3_ADDR(base)            ((base) + (0xE00))

/* �Ĵ���˵����A53 CLUSTER�������üĴ���4����
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_CTRL4_UNION */
#define SOC_CRGPERIPH_A53_CTRL4_ADDR(base)            ((base) + (0xE04))

/* �Ĵ���˵����A53 CLUSTER�������üĴ���5��
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_CTRL5_UNION */
#define SOC_CRGPERIPH_A53_CTRL5_ADDR(base)            ((base) + (0xE08))

/* �Ĵ���˵����A53 CLUSTER�������üĴ���6��
   λ����UNION�ṹ:  SOC_CRGPERIPH_A53_CTRL6_UNION */
#define SOC_CRGPERIPH_A53_CTRL6_ADDR(base)            ((base) + (0xE0C))

/* �Ĵ���˵����A57 CLUSTER�������üĴ���3��
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_CTRL3_UNION */
#define SOC_CRGPERIPH_MAIA_CTRL3_ADDR(base)           ((base) + (0xE10))

/* �Ĵ���˵����A57 CLUSTER�������üĴ���4��
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_CTRL4_UNION */
#define SOC_CRGPERIPH_MAIA_CTRL4_ADDR(base)           ((base) + (0xE14))

/* �Ĵ���˵����A57 CLUSTER�������üĴ���5��
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_CTRL5_UNION */
#define SOC_CRGPERIPH_MAIA_CTRL5_ADDR(base)           ((base) + (0xE18))

/* �Ĵ���˵����A57 CLUSTER�������üĴ���6��
   λ����UNION�ṹ:  SOC_CRGPERIPH_MAIA_CTRL6_UNION */
#define SOC_CRGPERIPH_MAIA_CTRL6_ADDR(base)           ((base) + (0xE1C))

/* �Ĵ���˵����ͨ�ð�ȫ��λʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_GENERAL_SEC_RSTEN_UNION */
#define SOC_CRGPERIPH_GENERAL_SEC_RSTEN_ADDR(base)    ((base) + (0xE20))

/* �Ĵ���˵����ͨ�ð�ȫ��λ����Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_UNION */
#define SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_ADDR(base)   ((base) + (0xE24))

/* �Ĵ���˵����ͨ�ð�ȫ��λʹ��״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_UNION */
#define SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_ADDR(base)  ((base) + (0xE28))





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
                     (1/1) register_CRGPERIPH
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PEREN0_UNION
 �ṹ˵��  : PEREN0 �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��ʹ�ܼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_b          : 1;  /* bit[0] : ����ʱ��ʹ�ܿ��ƣ�
                                                                 0��д0��Ч����
                                                                 1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_ddrbyp_ckp0       : 1;  /* bit[1] :  */
        unsigned int  gt_clk_ddrc              : 1;  /* bit[2] :  */
        unsigned int  reserved_0               : 1;  /* bit[3] :  */
        unsigned int  gt_clk_ddrphy_ref        : 1;  /* bit[4] :  */
        unsigned int  gt_clk_vcodeccfg         : 1;  /* bit[5] :  */
        unsigned int  gt_clk_vcodecbus         : 1;  /* bit[6] :  */
        unsigned int  reserved_1               : 1;  /* bit[7] : ������ */
        unsigned int  reserved_2               : 1;  /* bit[8] : ������ */
        unsigned int  gt_clk_sysbus            : 1;  /* bit[9] :  */
        unsigned int  gt_clk_cfgbus            : 1;  /* bit[10]:  */
        unsigned int  gt_clk_sys2cfgbus        : 1;  /* bit[11]:  */
        unsigned int  gt_clk_vivobus2ddrc      : 1;  /* bit[12]:  */
        unsigned int  gt_hclk_emmc0            : 1;  /* bit[13]:  */
        unsigned int  gt_clk_mmc1peri2sysbus   : 1;  /* bit[14]:  */
        unsigned int  gt_clk_mmc1_peribus      : 1;  /* bit[15]:  */
        unsigned int  gt_hclk_emmc1            : 1;  /* bit[16]:  */
        unsigned int  gt_clk_mmc0peri2sysbus   : 1;  /* bit[17]:  */
        unsigned int  gt_clk_mmc0_peribus      : 1;  /* bit[18]:  */
        unsigned int  gt_hclk_sdio0            : 1;  /* bit[19]:  */
        unsigned int  gt_clk_lpm32cfgbus       : 1;  /* bit[20]:  */
        unsigned int  gt_hclk_sdio1            : 1;  /* bit[21]:  */
        unsigned int  gt_clk_dmabus            : 1;  /* bit[22]:  */
        unsigned int  gt_clk_dma2cfgbus        : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hclk_memrep       : 1;  /* bit[24]:  */
        unsigned int  gt_clk_dbgsechsicbus     : 1;  /* bit[25]:  */
        unsigned int  gt_clk_dbgsechsic2sysbus : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ddrphy_a          : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ddrphy_c          : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ddrphy_d          : 1;  /* bit[29]:  */
        unsigned int  gt_hclk_sd               : 1;  /* bit[30]:  */
        unsigned int  gt_clk_aomm              : 1;  /* bit[31]: ����ʱ��ʹ�ܿ��ƣ�
                                                                 0��д0��Ч����
                                                                 1��ʹ��IPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PEREN0_UNION;
#endif
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_b_START           (0)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_b_END             (0)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrbyp_ckp0_START        (1)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrbyp_ckp0_END          (1)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrc_START               (2)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrc_END                 (2)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_ref_START         (4)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_ref_END           (4)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vcodeccfg_START          (5)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vcodeccfg_END            (5)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vcodecbus_START          (6)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vcodecbus_END            (6)
#define SOC_CRGPERIPH_PEREN0_gt_clk_sysbus_START             (9)
#define SOC_CRGPERIPH_PEREN0_gt_clk_sysbus_END               (9)
#define SOC_CRGPERIPH_PEREN0_gt_clk_cfgbus_START             (10)
#define SOC_CRGPERIPH_PEREN0_gt_clk_cfgbus_END               (10)
#define SOC_CRGPERIPH_PEREN0_gt_clk_sys2cfgbus_START         (11)
#define SOC_CRGPERIPH_PEREN0_gt_clk_sys2cfgbus_END           (11)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vivobus2ddrc_START       (12)
#define SOC_CRGPERIPH_PEREN0_gt_clk_vivobus2ddrc_END         (12)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_emmc0_START             (13)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_emmc0_END               (13)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc1peri2sysbus_START    (14)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc1peri2sysbus_END      (14)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc1_peribus_START       (15)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc1_peribus_END         (15)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_emmc1_START             (16)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_emmc1_END               (16)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc0peri2sysbus_START    (17)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc0peri2sysbus_END      (17)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc0_peribus_START       (18)
#define SOC_CRGPERIPH_PEREN0_gt_clk_mmc0_peribus_END         (18)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sdio0_START             (19)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sdio0_END               (19)
#define SOC_CRGPERIPH_PEREN0_gt_clk_lpm32cfgbus_START        (20)
#define SOC_CRGPERIPH_PEREN0_gt_clk_lpm32cfgbus_END          (20)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sdio1_START             (21)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sdio1_END               (21)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dmabus_START             (22)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dmabus_END               (22)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dma2cfgbus_START         (23)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dma2cfgbus_END           (23)
#define SOC_CRGPERIPH_PEREN0_gt_clk_hclk_memrep_START        (24)
#define SOC_CRGPERIPH_PEREN0_gt_clk_hclk_memrep_END          (24)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dbgsechsicbus_START      (25)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dbgsechsicbus_END        (25)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dbgsechsic2sysbus_START  (26)
#define SOC_CRGPERIPH_PEREN0_gt_clk_dbgsechsic2sysbus_END    (26)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_a_START           (27)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_a_END             (27)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_c_START           (28)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_c_END             (28)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_d_START           (29)
#define SOC_CRGPERIPH_PEREN0_gt_clk_ddrphy_d_END             (29)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sd_START                (30)
#define SOC_CRGPERIPH_PEREN0_gt_hclk_sd_END                  (30)
#define SOC_CRGPERIPH_PEREN0_gt_clk_aomm_START               (31)
#define SOC_CRGPERIPH_PEREN0_gt_clk_aomm_END                 (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERDIS0_UNION
 �ṹ˵��  : PERDIS0 �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ�ӽ�ֹ�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_b          : 1;  /* bit[0] : ����ʱ�ӽ�ֹ���ƣ�
                                                                 0��д0��Ч����
                                                                 1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_ddrbyp_ckp0       : 1;  /* bit[1] :  */
        unsigned int  gt_clk_ddrc              : 1;  /* bit[2] :  */
        unsigned int  reserved_0               : 1;  /* bit[3] :  */
        unsigned int  gt_clk_ddrphy_ref        : 1;  /* bit[4] :  */
        unsigned int  gt_clk_vcodeccfg         : 1;  /* bit[5] :  */
        unsigned int  gt_clk_vcodecbus         : 1;  /* bit[6] :  */
        unsigned int  reserved_1               : 1;  /* bit[7] : ������ */
        unsigned int  reserved_2               : 1;  /* bit[8] : ������ */
        unsigned int  gt_clk_sysbus            : 1;  /* bit[9] :  */
        unsigned int  gt_clk_cfgbus            : 1;  /* bit[10]:  */
        unsigned int  gt_clk_sys2cfgbus        : 1;  /* bit[11]:  */
        unsigned int  gt_clk_vivobus2ddrc      : 1;  /* bit[12]:  */
        unsigned int  gt_hclk_emmc0            : 1;  /* bit[13]:  */
        unsigned int  gt_clk_mmc1peri2sysbus   : 1;  /* bit[14]:  */
        unsigned int  gt_clk_mmc1_peribus      : 1;  /* bit[15]:  */
        unsigned int  gt_hclk_emmc1            : 1;  /* bit[16]:  */
        unsigned int  gt_clk_mmc0peri2sysbus   : 1;  /* bit[17]:  */
        unsigned int  gt_clk_mmc0_peribus      : 1;  /* bit[18]:  */
        unsigned int  gt_hclk_sdio0            : 1;  /* bit[19]:  */
        unsigned int  gt_clk_lpm32cfgbus       : 1;  /* bit[20]:  */
        unsigned int  gt_hclk_sdio1            : 1;  /* bit[21]:  */
        unsigned int  gt_clk_dmabus            : 1;  /* bit[22]:  */
        unsigned int  gt_clk_dma2cfgbus        : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hclk_memrep       : 1;  /* bit[24]:  */
        unsigned int  gt_clk_dbgsechsicbus     : 1;  /* bit[25]:  */
        unsigned int  gt_clk_dbgsechsic2sysbus : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ddrphy_a          : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ddrphy_c          : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ddrphy_d          : 1;  /* bit[29]:  */
        unsigned int  gt_hclk_sd               : 1;  /* bit[30]:  */
        unsigned int  gt_clk_aomm              : 1;  /* bit[31]: ����ʱ�ӽ�ֹ���ƣ�
                                                                 0��д0��Ч����
                                                                 1����ֹIPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PERDIS0_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_b_START           (0)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_b_END             (0)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrbyp_ckp0_START        (1)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrbyp_ckp0_END          (1)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrc_START               (2)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrc_END                 (2)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_ref_START         (4)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_ref_END           (4)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vcodeccfg_START          (5)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vcodeccfg_END            (5)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vcodecbus_START          (6)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vcodecbus_END            (6)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_sysbus_START             (9)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_sysbus_END               (9)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_cfgbus_START             (10)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_cfgbus_END               (10)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_sys2cfgbus_START         (11)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_sys2cfgbus_END           (11)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vivobus2ddrc_START       (12)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_vivobus2ddrc_END         (12)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_emmc0_START             (13)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_emmc0_END               (13)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc1peri2sysbus_START    (14)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc1peri2sysbus_END      (14)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc1_peribus_START       (15)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc1_peribus_END         (15)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_emmc1_START             (16)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_emmc1_END               (16)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc0peri2sysbus_START    (17)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc0peri2sysbus_END      (17)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc0_peribus_START       (18)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_mmc0_peribus_END         (18)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sdio0_START             (19)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sdio0_END               (19)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_lpm32cfgbus_START        (20)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_lpm32cfgbus_END          (20)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sdio1_START             (21)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sdio1_END               (21)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dmabus_START             (22)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dmabus_END               (22)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dma2cfgbus_START         (23)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dma2cfgbus_END           (23)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_hclk_memrep_START        (24)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_hclk_memrep_END          (24)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dbgsechsicbus_START      (25)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dbgsechsicbus_END        (25)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dbgsechsic2sysbus_START  (26)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_dbgsechsic2sysbus_END    (26)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_a_START           (27)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_a_END             (27)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_c_START           (28)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_c_END             (28)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_d_START           (29)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_ddrphy_d_END             (29)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sd_START                (30)
#define SOC_CRGPERIPH_PERDIS0_gt_hclk_sd_END                  (30)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_aomm_START               (31)
#define SOC_CRGPERIPH_PERDIS0_gt_clk_aomm_END                 (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERCLKEN0_UNION
 �ṹ˵��  : PERCLKEN0 �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x7EFFEF9F�����:32
 �Ĵ���˵��: ����ʱ��ʹ��״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_b          : 1;  /* bit[0] : ����ʱ��ʹ��״̬��
                                                                 0��IPʱ��ʹ�ܳ���״̬��
                                                                 1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_ddrbyp_ckp0       : 1;  /* bit[1] :  */
        unsigned int  gt_clk_ddrc              : 1;  /* bit[2] :  */
        unsigned int  reserved_0               : 1;  /* bit[3] :  */
        unsigned int  gt_clk_ddrphy_ref        : 1;  /* bit[4] :  */
        unsigned int  gt_clk_vcodeccfg         : 1;  /* bit[5] :  */
        unsigned int  gt_clk_vcodecbus         : 1;  /* bit[6] :  */
        unsigned int  reserved_1               : 1;  /* bit[7] : ������ */
        unsigned int  reserved_2               : 1;  /* bit[8] : ������ */
        unsigned int  gt_clk_sysbus            : 1;  /* bit[9] :  */
        unsigned int  gt_clk_cfgbus            : 1;  /* bit[10]:  */
        unsigned int  gt_clk_sys2cfgbus        : 1;  /* bit[11]:  */
        unsigned int  gt_clk_vivobus2ddrc      : 1;  /* bit[12]:  */
        unsigned int  gt_hclk_emmc0            : 1;  /* bit[13]:  */
        unsigned int  gt_clk_mmc1peri2sysbus   : 1;  /* bit[14]:  */
        unsigned int  gt_clk_mmc1_peribus      : 1;  /* bit[15]:  */
        unsigned int  gt_hclk_emmc1            : 1;  /* bit[16]:  */
        unsigned int  gt_clk_mmc0peri2sysbus   : 1;  /* bit[17]:  */
        unsigned int  gt_clk_mmc0_peribus      : 1;  /* bit[18]:  */
        unsigned int  gt_hclk_sdio0            : 1;  /* bit[19]:  */
        unsigned int  gt_clk_lpm32cfgbus       : 1;  /* bit[20]:  */
        unsigned int  gt_hclk_sdio1            : 1;  /* bit[21]:  */
        unsigned int  gt_clk_dmabus            : 1;  /* bit[22]:  */
        unsigned int  gt_clk_dma2cfgbus        : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hclk_memrep       : 1;  /* bit[24]:  */
        unsigned int  gt_clk_dbgsechsicbus     : 1;  /* bit[25]:  */
        unsigned int  gt_clk_dbgsechsic2sysbus : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ddrphy_a          : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ddrphy_c          : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ddrphy_d          : 1;  /* bit[29]:  */
        unsigned int  gt_hclk_sd               : 1;  /* bit[30]:  */
        unsigned int  gt_clk_aomm              : 1;  /* bit[31]: ����ʱ��ʹ��״̬��
                                                                 0��IPʱ��ʹ�ܳ���״̬��
                                                                 1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERCLKEN0_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_b_START           (0)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_b_END             (0)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrbyp_ckp0_START        (1)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrbyp_ckp0_END          (1)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrc_START               (2)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrc_END                 (2)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_ref_START         (4)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_ref_END           (4)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vcodeccfg_START          (5)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vcodeccfg_END            (5)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vcodecbus_START          (6)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vcodecbus_END            (6)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_sysbus_START             (9)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_sysbus_END               (9)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_cfgbus_START             (10)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_cfgbus_END               (10)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_sys2cfgbus_START         (11)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_sys2cfgbus_END           (11)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vivobus2ddrc_START       (12)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_vivobus2ddrc_END         (12)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_emmc0_START             (13)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_emmc0_END               (13)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc1peri2sysbus_START    (14)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc1peri2sysbus_END      (14)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc1_peribus_START       (15)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc1_peribus_END         (15)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_emmc1_START             (16)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_emmc1_END               (16)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc0peri2sysbus_START    (17)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc0peri2sysbus_END      (17)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc0_peribus_START       (18)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_mmc0_peribus_END         (18)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sdio0_START             (19)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sdio0_END               (19)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_lpm32cfgbus_START        (20)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_lpm32cfgbus_END          (20)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sdio1_START             (21)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sdio1_END               (21)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dmabus_START             (22)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dmabus_END               (22)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dma2cfgbus_START         (23)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dma2cfgbus_END           (23)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_hclk_memrep_START        (24)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_hclk_memrep_END          (24)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dbgsechsicbus_START      (25)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dbgsechsicbus_END        (25)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dbgsechsic2sysbus_START  (26)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_dbgsechsic2sysbus_END    (26)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_a_START           (27)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_a_END             (27)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_c_START           (28)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_c_END             (28)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_d_START           (29)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_ddrphy_d_END             (29)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sd_START                (30)
#define SOC_CRGPERIPH_PERCLKEN0_gt_hclk_sd_END                  (30)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_aomm_START               (31)
#define SOC_CRGPERIPH_PERCLKEN0_gt_clk_aomm_END                 (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERSTAT0_UNION
 �ṹ˵��  : PERSTAT0 �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x7EFFEF9F�����:32
 �Ĵ���˵��: ����ʱ������״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_b          : 1;  /* bit[0] : ����ʱ������״̬��
                                                                 0��IPʱ�ӽ�ֹ״̬��
                                                                 1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_ddrbyp_ckp0       : 1;  /* bit[1] :  */
        unsigned int  gt_clk_ddrc              : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ddrcfg            : 1;  /* bit[3] :  */
        unsigned int  gt_clk_ddrphy_ref        : 1;  /* bit[4] :  */
        unsigned int  gt_clk_vcodeccfg         : 1;  /* bit[5] :  */
        unsigned int  gt_clk_vcodecbus         : 1;  /* bit[6] :  */
        unsigned int  gt_clk_ddrsys_noc        : 1;  /* bit[7] :  */
        unsigned int  gt_clk_ddrsys_ao         : 1;  /* bit[8] :  */
        unsigned int  gt_clk_sysbus            : 1;  /* bit[9] :  */
        unsigned int  gt_clk_cfgbus            : 1;  /* bit[10]:  */
        unsigned int  gt_clk_sys2cfgbus        : 1;  /* bit[11]:  */
        unsigned int  gt_clk_vivobus2ddrc      : 1;  /* bit[12]:  */
        unsigned int  gt_hclk_emmc0            : 1;  /* bit[13]:  */
        unsigned int  gt_clk_mmc1peri2sysbus   : 1;  /* bit[14]:  */
        unsigned int  gt_clk_mmc1_peribus      : 1;  /* bit[15]:  */
        unsigned int  gt_hclk_emmc1            : 1;  /* bit[16]:  */
        unsigned int  gt_clk_mmc0peri2sysbus   : 1;  /* bit[17]:  */
        unsigned int  gt_clk_mmc0_peribus      : 1;  /* bit[18]:  */
        unsigned int  gt_hclk_sdio0            : 1;  /* bit[19]:  */
        unsigned int  gt_clk_lpm32cfgbus       : 1;  /* bit[20]:  */
        unsigned int  gt_hclk_sdio1            : 1;  /* bit[21]:  */
        unsigned int  gt_clk_dmabus            : 1;  /* bit[22]:  */
        unsigned int  gt_clk_dma2cfgbus        : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hclk_memrep       : 1;  /* bit[24]:  */
        unsigned int  gt_clk_dbgsechsicbus     : 1;  /* bit[25]:  */
        unsigned int  gt_clk_dbgsechsic2sysbus : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ddrphy_a          : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ddrphy_c          : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ddrphy_d          : 1;  /* bit[29]:  */
        unsigned int  gt_hclk_sd               : 1;  /* bit[30]:  */
        unsigned int  gt_clk_aomm              : 1;  /* bit[31]: ����ʱ������״̬��
                                                                 0��IPʱ�ӽ�ֹ״̬��
                                                                 1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERSTAT0_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_b_START           (0)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_b_END             (0)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrbyp_ckp0_START        (1)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrbyp_ckp0_END          (1)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrc_START               (2)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrc_END                 (2)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrcfg_START             (3)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrcfg_END               (3)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_ref_START         (4)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_ref_END           (4)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vcodeccfg_START          (5)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vcodeccfg_END            (5)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vcodecbus_START          (6)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vcodecbus_END            (6)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrsys_noc_START         (7)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrsys_noc_END           (7)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrsys_ao_START          (8)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrsys_ao_END            (8)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_sysbus_START             (9)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_sysbus_END               (9)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_cfgbus_START             (10)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_cfgbus_END               (10)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_sys2cfgbus_START         (11)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_sys2cfgbus_END           (11)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vivobus2ddrc_START       (12)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_vivobus2ddrc_END         (12)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_emmc0_START             (13)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_emmc0_END               (13)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc1peri2sysbus_START    (14)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc1peri2sysbus_END      (14)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc1_peribus_START       (15)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc1_peribus_END         (15)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_emmc1_START             (16)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_emmc1_END               (16)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc0peri2sysbus_START    (17)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc0peri2sysbus_END      (17)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc0_peribus_START       (18)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_mmc0_peribus_END         (18)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sdio0_START             (19)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sdio0_END               (19)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_lpm32cfgbus_START        (20)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_lpm32cfgbus_END          (20)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sdio1_START             (21)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sdio1_END               (21)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dmabus_START             (22)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dmabus_END               (22)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dma2cfgbus_START         (23)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dma2cfgbus_END           (23)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_hclk_memrep_START        (24)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_hclk_memrep_END          (24)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dbgsechsicbus_START      (25)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dbgsechsicbus_END        (25)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dbgsechsic2sysbus_START  (26)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_dbgsechsic2sysbus_END    (26)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_a_START           (27)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_a_END             (27)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_c_START           (28)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_c_END             (28)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_d_START           (29)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_ddrphy_d_END             (29)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sd_START                (30)
#define SOC_CRGPERIPH_PERSTAT0_gt_hclk_sd_END                  (30)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_aomm_START               (31)
#define SOC_CRGPERIPH_PERSTAT0_gt_clk_aomm_END                 (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PEREN1_UNION
 �ṹ˵��  : PEREN1 �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��ʹ�ܼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_gpio0    : 1;  /* bit[0] : ����ʱ��ʹ�ܿ��ƣ�
                                                         0��д0��Ч����
                                                         1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_pclk_gpio1    : 1;  /* bit[1] :  */
        unsigned int  gt_pclk_gpio2    : 1;  /* bit[2] :  */
        unsigned int  gt_pclk_gpio3    : 1;  /* bit[3] :  */
        unsigned int  gt_pclk_gpio4    : 1;  /* bit[4] :  */
        unsigned int  gt_pclk_gpio5    : 1;  /* bit[5] :  */
        unsigned int  gt_pclk_gpio6    : 1;  /* bit[6] :  */
        unsigned int  gt_pclk_gpio7    : 1;  /* bit[7] :  */
        unsigned int  gt_pclk_gpio8    : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_gpio9    : 1;  /* bit[9] :  */
        unsigned int  gt_pclk_gpio10   : 1;  /* bit[10]:  */
        unsigned int  gt_pclk_gpio11   : 1;  /* bit[11]:  */
        unsigned int  gt_pclk_gpio12   : 1;  /* bit[12]:  */
        unsigned int  gt_pclk_gpio13   : 1;  /* bit[13]:  */
        unsigned int  gt_pclk_gpio14   : 1;  /* bit[14]:  */
        unsigned int  gt_pclk_gpio15   : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_gpio16   : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_gpio17   : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_gpio18   : 1;  /* bit[18]:  */
        unsigned int  gt_pclk_gpio19   : 1;  /* bit[19]:  */
        unsigned int  gt_pclk_gpio20   : 1;  /* bit[20]:  */
        unsigned int  gt_pclk_gpio21   : 1;  /* bit[21]:  */
        unsigned int  gt_pclk_timer9   : 1;  /* bit[22]:  */
        unsigned int  gt_pclk_timer10  : 1;  /* bit[23]:  */
        unsigned int  gt_pclk_timer11  : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_timer12  : 1;  /* bit[25]:  */
        unsigned int  gt_clk_socp_lpm3 : 1;  /* bit[26]:  */
        unsigned int  gt_clk_djtag     : 1;  /* bit[27]:  */
        unsigned int  gt_clk_socp_acpu : 1;  /* bit[28]:  */
        unsigned int  gt_clk_socp_mcpu : 1;  /* bit[29]:  */
        unsigned int  reserved_0       : 1;  /* bit[30]:  */
        unsigned int  reserved_1       : 1;  /* bit[31]: ����ʱ��ʹ�ܿ��ƣ�
                                                         0��д0��Ч����
                                                         1��ʹ��IPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PEREN1_UNION;
#endif
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio0_START     (0)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio0_END       (0)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio1_START     (1)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio1_END       (1)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio2_START     (2)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio2_END       (2)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio3_START     (3)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio3_END       (3)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio4_START     (4)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio4_END       (4)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio5_START     (5)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio5_END       (5)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio6_START     (6)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio6_END       (6)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio7_START     (7)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio7_END       (7)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio8_START     (8)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio8_END       (8)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio9_START     (9)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio9_END       (9)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio10_START    (10)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio10_END      (10)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio11_START    (11)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio11_END      (11)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio12_START    (12)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio12_END      (12)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio13_START    (13)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio13_END      (13)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio14_START    (14)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio14_END      (14)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio15_START    (15)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio15_END      (15)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio16_START    (16)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio16_END      (16)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio17_START    (17)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio17_END      (17)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio18_START    (18)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio18_END      (18)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio19_START    (19)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio19_END      (19)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio20_START    (20)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio20_END      (20)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio21_START    (21)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_gpio21_END      (21)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer9_START    (22)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer9_END      (22)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer10_START   (23)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer10_END     (23)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer11_START   (24)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer11_END     (24)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer12_START   (25)
#define SOC_CRGPERIPH_PEREN1_gt_pclk_timer12_END     (25)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_lpm3_START  (26)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_lpm3_END    (26)
#define SOC_CRGPERIPH_PEREN1_gt_clk_djtag_START      (27)
#define SOC_CRGPERIPH_PEREN1_gt_clk_djtag_END        (27)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_acpu_START  (28)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_acpu_END    (28)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_mcpu_START  (29)
#define SOC_CRGPERIPH_PEREN1_gt_clk_socp_mcpu_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERDIS1_UNION
 �ṹ˵��  : PERDIS1 �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ�ӽ�ֹ�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_gpio0    : 1;  /* bit[0] : ����ʱ�ӽ�ֹ���ƣ�
                                                         0��д0��Ч����
                                                         1����ֹIPʱ�ӡ� */
        unsigned int  gt_pclk_gpio1    : 1;  /* bit[1] :  */
        unsigned int  gt_pclk_gpio2    : 1;  /* bit[2] :  */
        unsigned int  gt_pclk_gpio3    : 1;  /* bit[3] :  */
        unsigned int  gt_pclk_gpio4    : 1;  /* bit[4] :  */
        unsigned int  gt_pclk_gpio5    : 1;  /* bit[5] :  */
        unsigned int  gt_pclk_gpio6    : 1;  /* bit[6] :  */
        unsigned int  gt_pclk_gpio7    : 1;  /* bit[7] :  */
        unsigned int  gt_pclk_gpio8    : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_gpio9    : 1;  /* bit[9] :  */
        unsigned int  gt_pclk_gpio10   : 1;  /* bit[10]:  */
        unsigned int  gt_pclk_gpio11   : 1;  /* bit[11]:  */
        unsigned int  gt_pclk_gpio12   : 1;  /* bit[12]:  */
        unsigned int  gt_pclk_gpio13   : 1;  /* bit[13]:  */
        unsigned int  gt_pclk_gpio14   : 1;  /* bit[14]:  */
        unsigned int  gt_pclk_gpio15   : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_gpio16   : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_gpio17   : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_gpio18   : 1;  /* bit[18]:  */
        unsigned int  gt_pclk_gpio19   : 1;  /* bit[19]:  */
        unsigned int  gt_pclk_gpio20   : 1;  /* bit[20]:  */
        unsigned int  gt_pclk_gpio21   : 1;  /* bit[21]:  */
        unsigned int  gt_pclk_timer9   : 1;  /* bit[22]:  */
        unsigned int  gt_pclk_timer10  : 1;  /* bit[23]:  */
        unsigned int  gt_pclk_timer11  : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_timer12  : 1;  /* bit[25]:  */
        unsigned int  gt_clk_socp_lpm3 : 1;  /* bit[26]:  */
        unsigned int  gt_clk_djtag     : 1;  /* bit[27]:  */
        unsigned int  gt_clk_socp_acpu : 1;  /* bit[28]:  */
        unsigned int  gt_clk_socp_mcpu : 1;  /* bit[29]:  */
        unsigned int  reserved_0       : 1;  /* bit[30]:  */
        unsigned int  reserved_1       : 1;  /* bit[31]: ����ʱ�ӽ�ֹ���ƣ�
                                                         0��д0��Ч����
                                                         1����ֹIPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PERDIS1_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio0_START     (0)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio0_END       (0)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio1_START     (1)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio1_END       (1)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio2_START     (2)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio2_END       (2)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio3_START     (3)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio3_END       (3)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio4_START     (4)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio4_END       (4)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio5_START     (5)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio5_END       (5)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio6_START     (6)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio6_END       (6)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio7_START     (7)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio7_END       (7)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio8_START     (8)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio8_END       (8)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio9_START     (9)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio9_END       (9)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio10_START    (10)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio10_END      (10)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio11_START    (11)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio11_END      (11)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio12_START    (12)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio12_END      (12)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio13_START    (13)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio13_END      (13)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio14_START    (14)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio14_END      (14)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio15_START    (15)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio15_END      (15)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio16_START    (16)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio16_END      (16)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio17_START    (17)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio17_END      (17)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio18_START    (18)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio18_END      (18)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio19_START    (19)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio19_END      (19)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio20_START    (20)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio20_END      (20)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio21_START    (21)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_gpio21_END      (21)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer9_START    (22)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer9_END      (22)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer10_START   (23)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer10_END     (23)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer11_START   (24)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer11_END     (24)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer12_START   (25)
#define SOC_CRGPERIPH_PERDIS1_gt_pclk_timer12_END     (25)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_lpm3_START  (26)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_lpm3_END    (26)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_djtag_START      (27)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_djtag_END        (27)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_acpu_START  (28)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_acpu_END    (28)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_mcpu_START  (29)
#define SOC_CRGPERIPH_PERDIS1_gt_clk_socp_mcpu_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERCLKEN1_UNION
 �ṹ˵��  : PERCLKEN1 �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: ����ʱ��ʹ��״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_gpio0    : 1;  /* bit[0] : ����ʱ��ʹ��״̬��
                                                         0��IPʱ��ʹ�ܳ���״̬��
                                                         1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_gpio1    : 1;  /* bit[1] :  */
        unsigned int  gt_pclk_gpio2    : 1;  /* bit[2] :  */
        unsigned int  gt_pclk_gpio3    : 1;  /* bit[3] :  */
        unsigned int  gt_pclk_gpio4    : 1;  /* bit[4] :  */
        unsigned int  gt_pclk_gpio5    : 1;  /* bit[5] :  */
        unsigned int  gt_pclk_gpio6    : 1;  /* bit[6] :  */
        unsigned int  gt_pclk_gpio7    : 1;  /* bit[7] :  */
        unsigned int  gt_pclk_gpio8    : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_gpio9    : 1;  /* bit[9] :  */
        unsigned int  gt_pclk_gpio10   : 1;  /* bit[10]:  */
        unsigned int  gt_pclk_gpio11   : 1;  /* bit[11]:  */
        unsigned int  gt_pclk_gpio12   : 1;  /* bit[12]:  */
        unsigned int  gt_pclk_gpio13   : 1;  /* bit[13]:  */
        unsigned int  gt_pclk_gpio14   : 1;  /* bit[14]:  */
        unsigned int  gt_pclk_gpio15   : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_gpio16   : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_gpio17   : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_gpio18   : 1;  /* bit[18]:  */
        unsigned int  gt_pclk_gpio19   : 1;  /* bit[19]:  */
        unsigned int  gt_pclk_gpio20   : 1;  /* bit[20]:  */
        unsigned int  gt_pclk_gpio21   : 1;  /* bit[21]:  */
        unsigned int  gt_pclk_timer9   : 1;  /* bit[22]:  */
        unsigned int  gt_pclk_timer10  : 1;  /* bit[23]:  */
        unsigned int  gt_pclk_timer11  : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_timer12  : 1;  /* bit[25]:  */
        unsigned int  gt_clk_socp_lpm3 : 1;  /* bit[26]:  */
        unsigned int  gt_clk_djtag     : 1;  /* bit[27]:  */
        unsigned int  gt_clk_socp_acpu : 1;  /* bit[28]:  */
        unsigned int  gt_clk_socp_mcpu : 1;  /* bit[29]:  */
        unsigned int  reserved_0       : 1;  /* bit[30]:  */
        unsigned int  reserved_1       : 1;  /* bit[31]: ����ʱ��ʹ��״̬��
                                                         0��IPʱ��ʹ�ܳ���״̬��
                                                         1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERCLKEN1_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio0_START     (0)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio0_END       (0)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio1_START     (1)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio1_END       (1)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio2_START     (2)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio2_END       (2)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio3_START     (3)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio3_END       (3)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio4_START     (4)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio4_END       (4)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio5_START     (5)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio5_END       (5)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio6_START     (6)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio6_END       (6)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio7_START     (7)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio7_END       (7)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio8_START     (8)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio8_END       (8)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio9_START     (9)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio9_END       (9)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio10_START    (10)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio10_END      (10)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio11_START    (11)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio11_END      (11)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio12_START    (12)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio12_END      (12)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio13_START    (13)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio13_END      (13)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio14_START    (14)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio14_END      (14)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio15_START    (15)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio15_END      (15)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio16_START    (16)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio16_END      (16)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio17_START    (17)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio17_END      (17)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio18_START    (18)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio18_END      (18)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio19_START    (19)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio19_END      (19)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio20_START    (20)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio20_END      (20)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio21_START    (21)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_gpio21_END      (21)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer9_START    (22)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer9_END      (22)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer10_START   (23)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer10_END     (23)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer11_START   (24)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer11_END     (24)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer12_START   (25)
#define SOC_CRGPERIPH_PERCLKEN1_gt_pclk_timer12_END     (25)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_lpm3_START  (26)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_lpm3_END    (26)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_djtag_START      (27)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_djtag_END        (27)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_acpu_START  (28)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_acpu_END    (28)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_mcpu_START  (29)
#define SOC_CRGPERIPH_PERCLKEN1_gt_clk_socp_mcpu_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERSTAT1_UNION
 �ṹ˵��  : PERSTAT1 �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: ����ʱ������״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_pclk_gpio0   : 1;  /* bit[0] : ����ʱ������״̬��
                                                        0��IPʱ�ӽ�ֹ״̬��
                                                        1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_pclk_gpio1   : 1;  /* bit[1] :  */
        unsigned int  gt_pclk_gpio2   : 1;  /* bit[2] :  */
        unsigned int  gt_pclk_gpio3   : 1;  /* bit[3] :  */
        unsigned int  gt_pclk_gpio4   : 1;  /* bit[4] :  */
        unsigned int  gt_pclk_gpio5   : 1;  /* bit[5] :  */
        unsigned int  gt_pclk_gpio6   : 1;  /* bit[6] :  */
        unsigned int  gt_pclk_gpio7   : 1;  /* bit[7] :  */
        unsigned int  gt_pclk_gpio8   : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_gpio9   : 1;  /* bit[9] :  */
        unsigned int  gt_pclk_gpio10  : 1;  /* bit[10]:  */
        unsigned int  gt_pclk_gpio11  : 1;  /* bit[11]:  */
        unsigned int  gt_pclk_gpio12  : 1;  /* bit[12]:  */
        unsigned int  gt_pclk_gpio13  : 1;  /* bit[13]:  */
        unsigned int  gt_pclk_gpio14  : 1;  /* bit[14]:  */
        unsigned int  gt_pclk_gpio15  : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_gpio16  : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_gpio17  : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_gpio18  : 1;  /* bit[18]:  */
        unsigned int  gt_pclk_gpio19  : 1;  /* bit[19]:  */
        unsigned int  gt_pclk_gpio20  : 1;  /* bit[20]:  */
        unsigned int  gt_pclk_gpio21  : 1;  /* bit[21]:  */
        unsigned int  gt_pclk_timer9  : 1;  /* bit[22]:  */
        unsigned int  gt_pclk_timer10 : 1;  /* bit[23]:  */
        unsigned int  gt_pclk_timer11 : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_timer12 : 1;  /* bit[25]:  */
        unsigned int  gt_clk_socp     : 1;  /* bit[26]: socpʱ������״̬��gt_clk_socp_lpm3\gt_clk_socp_acpu\gt_clk_socp_mcpu�κ�һ��Ϊ1'b1��ʱ�ӿ�����ȫ��Ϊ0ʱʱ�ӹرա� */
        unsigned int  gt_clk_djtag    : 1;  /* bit[27]:  */
        unsigned int  reserved_0      : 1;  /* bit[28]: ������ */
        unsigned int  reserved_1      : 1;  /* bit[29]: ������ */
        unsigned int  reserved_2      : 1;  /* bit[30]:  */
        unsigned int  reserved_3      : 1;  /* bit[31]: ����ʱ������״̬��
                                                        0��IPʱ�ӽ�ֹ״̬��
                                                        1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERSTAT1_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio0_START    (0)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio0_END      (0)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio1_START    (1)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio1_END      (1)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio2_START    (2)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio2_END      (2)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio3_START    (3)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio3_END      (3)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio4_START    (4)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio4_END      (4)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio5_START    (5)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio5_END      (5)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio6_START    (6)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio6_END      (6)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio7_START    (7)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio7_END      (7)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio8_START    (8)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio8_END      (8)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio9_START    (9)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio9_END      (9)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio10_START   (10)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio10_END     (10)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio11_START   (11)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio11_END     (11)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio12_START   (12)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio12_END     (12)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio13_START   (13)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio13_END     (13)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio14_START   (14)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio14_END     (14)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio15_START   (15)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio15_END     (15)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio16_START   (16)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio16_END     (16)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio17_START   (17)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio17_END     (17)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio18_START   (18)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio18_END     (18)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio19_START   (19)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio19_END     (19)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio20_START   (20)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio20_END     (20)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio21_START   (21)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_gpio21_END     (21)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer9_START   (22)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer9_END     (22)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer10_START  (23)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer10_END    (23)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer11_START  (24)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer11_END    (24)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer12_START  (25)
#define SOC_CRGPERIPH_PERSTAT1_gt_pclk_timer12_END    (25)
#define SOC_CRGPERIPH_PERSTAT1_gt_clk_socp_START      (26)
#define SOC_CRGPERIPH_PERSTAT1_gt_clk_socp_END        (26)
#define SOC_CRGPERIPH_PERSTAT1_gt_clk_djtag_START     (27)
#define SOC_CRGPERIPH_PERSTAT1_gt_clk_djtag_END       (27)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PEREN2_UNION
 �ṹ˵��  : PEREN2 �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��ʹ�ܼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_pwm         : 1;  /* bit[0] : ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
        unsigned int  reserved_0         : 1;  /* bit[1] : ������ */
        unsigned int  gt_clk_ipc0        : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ipc1        : 1;  /* bit[3] :  */
        unsigned int  reserved_1         : 1;  /* bit[4] : ������ */
        unsigned int  reserved_2         : 1;  /* bit[5] : ������ */
        unsigned int  reserved_3         : 1;  /* bit[6] : ������ */
        unsigned int  gt_clk_i2c3        : 1;  /* bit[7] :  */
        unsigned int  reserved_4         : 1;  /* bit[8] : ������ */
        unsigned int  gt_clk_spi1        : 1;  /* bit[9] :  */
        unsigned int  gt_clk_uart0       : 1;  /* bit[10]:  */
        unsigned int  gt_clk_uart1       : 1;  /* bit[11]:  */
        unsigned int  gt_clk_uart2       : 1;  /* bit[12]:  */
        unsigned int  reserved_5         : 1;  /* bit[13]: ������ */
        unsigned int  gt_clk_uart4       : 1;  /* bit[14]:  */
        unsigned int  gt_clk_uart5       : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_wd0        : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_wd1        : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_tzpc       : 1;  /* bit[18]:  */
        unsigned int  reserved_6         : 1;  /* bit[19]:  */
        unsigned int  gt_pclk_ipc_mdm    : 1;  /* bit[20]:  */
        unsigned int  gt_clk_adb_mst_a53 : 1;  /* bit[21]:  */
        unsigned int  gt_clk_adb_mst_a57 : 1;  /* bit[22]:  */
        unsigned int  gt_clk_gic         : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hkadcssi    : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_ioc        : 1;  /* bit[25]:  */
        unsigned int  gt_clk_codecssi    : 1;  /* bit[26]:  */
        unsigned int  gt_clk_i2c4        : 1;  /* bit[27]:  */
        unsigned int  reserved_7         : 1;  /* bit[28]: ������ */
        unsigned int  reserved_8         : 1;  /* bit[29]: ������ */
        unsigned int  reserved_9         : 1;  /* bit[30]: ������ */
        unsigned int  gt_pclk_pctrl      : 1;  /* bit[31]: ����ʱ��ʹ�ܿ��ƣ�
                                                           0��д0��Ч����
                                                           1��ʹ��IPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PEREN2_UNION;
#endif
#define SOC_CRGPERIPH_PEREN2_gt_clk_pwm_START          (0)
#define SOC_CRGPERIPH_PEREN2_gt_clk_pwm_END            (0)
#define SOC_CRGPERIPH_PEREN2_gt_clk_ipc0_START         (2)
#define SOC_CRGPERIPH_PEREN2_gt_clk_ipc0_END           (2)
#define SOC_CRGPERIPH_PEREN2_gt_clk_ipc1_START         (3)
#define SOC_CRGPERIPH_PEREN2_gt_clk_ipc1_END           (3)
#define SOC_CRGPERIPH_PEREN2_gt_clk_i2c3_START         (7)
#define SOC_CRGPERIPH_PEREN2_gt_clk_i2c3_END           (7)
#define SOC_CRGPERIPH_PEREN2_gt_clk_spi1_START         (9)
#define SOC_CRGPERIPH_PEREN2_gt_clk_spi1_END           (9)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart0_START        (10)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart0_END          (10)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart1_START        (11)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart1_END          (11)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart2_START        (12)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart2_END          (12)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart4_START        (14)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart4_END          (14)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart5_START        (15)
#define SOC_CRGPERIPH_PEREN2_gt_clk_uart5_END          (15)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_wd0_START         (16)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_wd0_END           (16)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_wd1_START         (17)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_wd1_END           (17)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_tzpc_START        (18)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_tzpc_END          (18)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_ipc_mdm_START     (20)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_ipc_mdm_END       (20)
#define SOC_CRGPERIPH_PEREN2_gt_clk_adb_mst_a53_START  (21)
#define SOC_CRGPERIPH_PEREN2_gt_clk_adb_mst_a53_END    (21)
#define SOC_CRGPERIPH_PEREN2_gt_clk_adb_mst_a57_START  (22)
#define SOC_CRGPERIPH_PEREN2_gt_clk_adb_mst_a57_END    (22)
#define SOC_CRGPERIPH_PEREN2_gt_clk_gic_START          (23)
#define SOC_CRGPERIPH_PEREN2_gt_clk_gic_END            (23)
#define SOC_CRGPERIPH_PEREN2_gt_clk_hkadcssi_START     (24)
#define SOC_CRGPERIPH_PEREN2_gt_clk_hkadcssi_END       (24)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_ioc_START         (25)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_ioc_END           (25)
#define SOC_CRGPERIPH_PEREN2_gt_clk_codecssi_START     (26)
#define SOC_CRGPERIPH_PEREN2_gt_clk_codecssi_END       (26)
#define SOC_CRGPERIPH_PEREN2_gt_clk_i2c4_START         (27)
#define SOC_CRGPERIPH_PEREN2_gt_clk_i2c4_END           (27)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_pctrl_START       (31)
#define SOC_CRGPERIPH_PEREN2_gt_pclk_pctrl_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERDIS2_UNION
 �ṹ˵��  : PERDIS2 �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ�ӽ�ֹ�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_pwm         : 1;  /* bit[0] : ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
        unsigned int  reserved_0         : 1;  /* bit[1] : ������ */
        unsigned int  gt_clk_ipc0        : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ipc1        : 1;  /* bit[3] :  */
        unsigned int  reserved_1         : 1;  /* bit[4] : ������ */
        unsigned int  reserved_2         : 1;  /* bit[5] : ������ */
        unsigned int  reserved_3         : 1;  /* bit[6] : ������ */
        unsigned int  gt_clk_i2c3        : 1;  /* bit[7] :  */
        unsigned int  reserved_4         : 1;  /* bit[8] : ������ */
        unsigned int  gt_clk_spi1        : 1;  /* bit[9] :  */
        unsigned int  gt_clk_uart0       : 1;  /* bit[10]:  */
        unsigned int  gt_clk_uart1       : 1;  /* bit[11]:  */
        unsigned int  gt_clk_uart2       : 1;  /* bit[12]:  */
        unsigned int  reserved_5         : 1;  /* bit[13]: ������ */
        unsigned int  gt_clk_uart4       : 1;  /* bit[14]:  */
        unsigned int  gt_clk_uart5       : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_wd0        : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_wd1        : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_tzpc       : 1;  /* bit[18]:  */
        unsigned int  reserved_6         : 1;  /* bit[19]:  */
        unsigned int  gt_pclk_ipc_mdm    : 1;  /* bit[20]:  */
        unsigned int  gt_clk_adb_mst_a53 : 1;  /* bit[21]:  */
        unsigned int  gt_clk_adb_mst_a57 : 1;  /* bit[22]:  */
        unsigned int  gt_clk_gic         : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hkadcssi    : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_ioc        : 1;  /* bit[25]:  */
        unsigned int  gt_clk_codecssi    : 1;  /* bit[26]:  */
        unsigned int  gt_clk_i2c4        : 1;  /* bit[27]:  */
        unsigned int  reserved_7         : 1;  /* bit[28]: ������ */
        unsigned int  reserved_8         : 1;  /* bit[29]: ������ */
        unsigned int  reserved_9         : 1;  /* bit[30]: ������ */
        unsigned int  gt_pclk_pctrl      : 1;  /* bit[31]: ����ʱ�ӽ�ֹ���ƣ�
                                                           0��д0��Ч����
                                                           1����ֹIPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PERDIS2_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS2_gt_clk_pwm_START          (0)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_pwm_END            (0)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_ipc0_START         (2)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_ipc0_END           (2)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_ipc1_START         (3)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_ipc1_END           (3)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_i2c3_START         (7)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_i2c3_END           (7)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_spi1_START         (9)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_spi1_END           (9)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart0_START        (10)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart0_END          (10)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart1_START        (11)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart1_END          (11)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart2_START        (12)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart2_END          (12)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart4_START        (14)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart4_END          (14)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart5_START        (15)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_uart5_END          (15)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_wd0_START         (16)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_wd0_END           (16)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_wd1_START         (17)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_wd1_END           (17)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_tzpc_START        (18)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_tzpc_END          (18)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_ipc_mdm_START     (20)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_ipc_mdm_END       (20)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_adb_mst_a53_START  (21)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_adb_mst_a53_END    (21)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_adb_mst_a57_START  (22)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_adb_mst_a57_END    (22)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_gic_START          (23)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_gic_END            (23)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_hkadcssi_START     (24)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_hkadcssi_END       (24)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_ioc_START         (25)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_ioc_END           (25)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_codecssi_START     (26)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_codecssi_END       (26)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_i2c4_START         (27)
#define SOC_CRGPERIPH_PERDIS2_gt_clk_i2c4_END           (27)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_pctrl_START       (31)
#define SOC_CRGPERIPH_PERDIS2_gt_pclk_pctrl_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERCLKEN2_UNION
 �ṹ˵��  : PERCLKEN2 �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0xFF9FFFFF�����:32
 �Ĵ���˵��: ����ʱ��ʹ��״̬�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_pwm         : 1;  /* bit[0] : ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  reserved_0         : 1;  /* bit[1] : ������ */
        unsigned int  gt_clk_ipc0        : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ipc1        : 1;  /* bit[3] :  */
        unsigned int  reserved_1         : 1;  /* bit[4] : ������ */
        unsigned int  reserved_2         : 1;  /* bit[5] : ������ */
        unsigned int  reserved_3         : 1;  /* bit[6] : ������ */
        unsigned int  gt_clk_i2c3        : 1;  /* bit[7] :  */
        unsigned int  reserved_4         : 1;  /* bit[8] : ������ */
        unsigned int  gt_clk_spi1        : 1;  /* bit[9] :  */
        unsigned int  gt_clk_uart0       : 1;  /* bit[10]:  */
        unsigned int  gt_clk_uart1       : 1;  /* bit[11]:  */
        unsigned int  gt_clk_uart2       : 1;  /* bit[12]:  */
        unsigned int  reserved_5         : 1;  /* bit[13]: ������ */
        unsigned int  gt_clk_uart4       : 1;  /* bit[14]:  */
        unsigned int  gt_clk_uart5       : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_wd0        : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_wd1        : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_tzpc       : 1;  /* bit[18]:  */
        unsigned int  reserved_6         : 1;  /* bit[19]: ������ */
        unsigned int  gt_pclk_ipc_mdm    : 1;  /* bit[20]:  */
        unsigned int  gt_clk_adb_mst_a53 : 1;  /* bit[21]:  */
        unsigned int  gt_clk_adb_mst_a57 : 1;  /* bit[22]:  */
        unsigned int  gt_clk_gic         : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hkadcssi    : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_ioc        : 1;  /* bit[25]:  */
        unsigned int  gt_clk_codecssi    : 1;  /* bit[26]:  */
        unsigned int  gt_clk_i2c4        : 1;  /* bit[27]:  */
        unsigned int  reserved_7         : 1;  /* bit[28]: ������ */
        unsigned int  reserved_8         : 1;  /* bit[29]: ������ */
        unsigned int  reserved_9         : 1;  /* bit[30]: ������ */
        unsigned int  gt_pclk_pctrl      : 1;  /* bit[31]: ����ʱ��ʹ��״̬��
                                                           0��IPʱ��ʹ�ܳ���״̬��
                                                           1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERCLKEN2_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_pwm_START          (0)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_pwm_END            (0)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_ipc0_START         (2)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_ipc0_END           (2)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_ipc1_START         (3)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_ipc1_END           (3)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_i2c3_START         (7)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_i2c3_END           (7)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_spi1_START         (9)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_spi1_END           (9)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart0_START        (10)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart0_END          (10)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart1_START        (11)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart1_END          (11)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart2_START        (12)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart2_END          (12)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart4_START        (14)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart4_END          (14)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart5_START        (15)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_uart5_END          (15)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_wd0_START         (16)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_wd0_END           (16)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_wd1_START         (17)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_wd1_END           (17)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_tzpc_START        (18)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_tzpc_END          (18)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_ipc_mdm_START     (20)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_ipc_mdm_END       (20)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_adb_mst_a53_START  (21)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_adb_mst_a53_END    (21)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_adb_mst_a57_START  (22)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_adb_mst_a57_END    (22)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_gic_START          (23)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_gic_END            (23)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_hkadcssi_START     (24)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_hkadcssi_END       (24)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_ioc_START         (25)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_ioc_END           (25)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_codecssi_START     (26)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_codecssi_END       (26)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_i2c4_START         (27)
#define SOC_CRGPERIPH_PERCLKEN2_gt_clk_i2c4_END           (27)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_pctrl_START       (31)
#define SOC_CRGPERIPH_PERCLKEN2_gt_pclk_pctrl_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERSTAT2_UNION
 �ṹ˵��  : PERSTAT2 �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0xFF9FFFFF�����:32
 �Ĵ���˵��: ����ʱ������״̬�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_pwm         : 1;  /* bit[0] : ����ʱ������״̬��
                                                           0��IPʱ�ӽ�ֹ״̬��
                                                           1��IPʱ��ʹ��״̬�� */
        unsigned int  reserved_0         : 1;  /* bit[1] : ������ */
        unsigned int  gt_clk_ipc0        : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ipc1        : 1;  /* bit[3] :  */
        unsigned int  reserved_1         : 1;  /* bit[4] : ������ */
        unsigned int  reserved_2         : 1;  /* bit[5] : ������ */
        unsigned int  reserved_3         : 1;  /* bit[6] : ������ */
        unsigned int  gt_clk_i2c3        : 1;  /* bit[7] :  */
        unsigned int  reserved_4         : 1;  /* bit[8] : ������ */
        unsigned int  gt_clk_spi1        : 1;  /* bit[9] :  */
        unsigned int  gt_clk_uart0       : 1;  /* bit[10]:  */
        unsigned int  gt_clk_uart1       : 1;  /* bit[11]:  */
        unsigned int  gt_clk_uart2       : 1;  /* bit[12]:  */
        unsigned int  reserved_5         : 1;  /* bit[13]: ������ */
        unsigned int  gt_clk_uart4       : 1;  /* bit[14]:  */
        unsigned int  gt_clk_uart5       : 1;  /* bit[15]:  */
        unsigned int  gt_pclk_wd0        : 1;  /* bit[16]:  */
        unsigned int  gt_pclk_wd1        : 1;  /* bit[17]:  */
        unsigned int  gt_pclk_tzpc       : 1;  /* bit[18]:  */
        unsigned int  reserved_6         : 1;  /* bit[19]: ������ */
        unsigned int  gt_pclk_ipc_mdm    : 1;  /* bit[20]:  */
        unsigned int  gt_clk_adb_mst_a53 : 1;  /* bit[21]:  */
        unsigned int  gt_clk_adb_mst_a57 : 1;  /* bit[22]:  */
        unsigned int  gt_clk_gic         : 1;  /* bit[23]:  */
        unsigned int  gt_clk_hkadcssi    : 1;  /* bit[24]:  */
        unsigned int  gt_pclk_ioc        : 1;  /* bit[25]:  */
        unsigned int  gt_clk_codecssi    : 1;  /* bit[26]:  */
        unsigned int  gt_clk_i2c4        : 1;  /* bit[27]:  */
        unsigned int  reserved_7         : 1;  /* bit[28]: ������ */
        unsigned int  reserved_8         : 1;  /* bit[29]: ������ */
        unsigned int  reserved_9         : 1;  /* bit[30]: ������ */
        unsigned int  gt_pclk_pctrl      : 1;  /* bit[31]: ����ʱ������״̬��
                                                           0��IPʱ�ӽ�ֹ״̬��
                                                           1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERSTAT2_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_pwm_START          (0)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_pwm_END            (0)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_ipc0_START         (2)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_ipc0_END           (2)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_ipc1_START         (3)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_ipc1_END           (3)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_i2c3_START         (7)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_i2c3_END           (7)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_spi1_START         (9)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_spi1_END           (9)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart0_START        (10)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart0_END          (10)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart1_START        (11)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart1_END          (11)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart2_START        (12)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart2_END          (12)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart4_START        (14)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart4_END          (14)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart5_START        (15)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_uart5_END          (15)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_wd0_START         (16)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_wd0_END           (16)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_wd1_START         (17)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_wd1_END           (17)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_tzpc_START        (18)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_tzpc_END          (18)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_ipc_mdm_START     (20)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_ipc_mdm_END       (20)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_adb_mst_a53_START  (21)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_adb_mst_a53_END    (21)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_adb_mst_a57_START  (22)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_adb_mst_a57_END    (22)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_gic_START          (23)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_gic_END            (23)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_hkadcssi_START     (24)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_hkadcssi_END       (24)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_ioc_START         (25)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_ioc_END           (25)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_codecssi_START     (26)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_codecssi_END       (26)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_i2c4_START         (27)
#define SOC_CRGPERIPH_PERSTAT2_gt_clk_i2c4_END           (27)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_pctrl_START       (31)
#define SOC_CRGPERIPH_PERSTAT2_gt_pclk_pctrl_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PEREN3_UNION
 �ṹ˵��  : PEREN3 �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��ʹ�ܼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_dmac_lpm3       : 1;  /* bit[0]  : ����ʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_dmac_acpu       : 1;  /* bit[1]  :  */
        unsigned int  gt_clk_dmac_mcpu       : 1;  /* bit[2]  :  */
        unsigned int  gt_pclk_g3d            : 1;  /* bit[3]  :  */
        unsigned int  gt_clk_g3dmt           : 1;  /* bit[4]  :  */
        unsigned int  gt_clk_g3d             : 1;  /* bit[5]  :  */
        unsigned int  sc_abb_pll_gps_en      : 2;  /* bit[6-7]:  */
        unsigned int  sc_abb_pll_audio_en    : 2;  /* bit[8-9]:  */
        unsigned int  gt_clk_venc            : 1;  /* bit[10] :  */
        unsigned int  gt_clk_vdec            : 1;  /* bit[11] :  */
        unsigned int  gt_pclk_dss            : 1;  /* bit[12] :  */
        unsigned int  gt_aclk_dss            : 1;  /* bit[13] :  */
        unsigned int  gt_clk_ldi1            : 1;  /* bit[14] :  */
        unsigned int  gt_clk_ldi0            : 1;  /* bit[15] :  */
        unsigned int  reserved_0             : 1;  /* bit[16] : ������ */
        unsigned int  gt_clk_edc0            : 1;  /* bit[17] :  */
        unsigned int  sc_abb_pll_gps_gt_en   : 1;  /* bit[18] :  */
        unsigned int  sc_abb_pll_audio_gt_en : 1;  /* bit[19] :  */
        unsigned int  gt_clk_rxdphy0_cfg     : 1;  /* bit[20] :  */
        unsigned int  gt_clk_rxdphy1_cfg     : 1;  /* bit[21] :  */
        unsigned int  gt_clk_rxdphy2_cfg     : 1;  /* bit[22] :  */
        unsigned int  gt_aclk_isp            : 1;  /* bit[23] :  */
        unsigned int  gt_hclk_isp            : 1;  /* bit[24] :  */
        unsigned int  gt_clk_ispfunc         : 1;  /* bit[25] :  */
        unsigned int  reserved_1             : 1;  /* bit[26] :  */
        unsigned int  gt_clk_ispa7cfg        : 1;  /* bit[27] :  */
        unsigned int  gt_clk_txdphy0_cfg     : 1;  /* bit[28] :  */
        unsigned int  gt_clk_txdphy0_ref     : 1;  /* bit[29] :  */
        unsigned int  gt_clk_txdphy1_cfg     : 1;  /* bit[30] :  */
        unsigned int  gt_clk_txdphy1_ref     : 1;  /* bit[31] : ����ʱ��ʹ�ܿ��ƣ�
                                                                0��д0��Ч����
                                                                1��ʹ��IPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PEREN3_UNION;
#endif
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_lpm3_START        (0)
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_lpm3_END          (0)
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_acpu_START        (1)
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_acpu_END          (1)
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_mcpu_START        (2)
#define SOC_CRGPERIPH_PEREN3_gt_clk_dmac_mcpu_END          (2)
#define SOC_CRGPERIPH_PEREN3_gt_pclk_g3d_START             (3)
#define SOC_CRGPERIPH_PEREN3_gt_pclk_g3d_END               (3)
#define SOC_CRGPERIPH_PEREN3_gt_clk_g3dmt_START            (4)
#define SOC_CRGPERIPH_PEREN3_gt_clk_g3dmt_END              (4)
#define SOC_CRGPERIPH_PEREN3_gt_clk_g3d_START              (5)
#define SOC_CRGPERIPH_PEREN3_gt_clk_g3d_END                (5)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_gps_en_START       (6)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_gps_en_END         (7)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_audio_en_START     (8)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_audio_en_END       (9)
#define SOC_CRGPERIPH_PEREN3_gt_clk_venc_START             (10)
#define SOC_CRGPERIPH_PEREN3_gt_clk_venc_END               (10)
#define SOC_CRGPERIPH_PEREN3_gt_clk_vdec_START             (11)
#define SOC_CRGPERIPH_PEREN3_gt_clk_vdec_END               (11)
#define SOC_CRGPERIPH_PEREN3_gt_pclk_dss_START             (12)
#define SOC_CRGPERIPH_PEREN3_gt_pclk_dss_END               (12)
#define SOC_CRGPERIPH_PEREN3_gt_aclk_dss_START             (13)
#define SOC_CRGPERIPH_PEREN3_gt_aclk_dss_END               (13)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ldi1_START             (14)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ldi1_END               (14)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ldi0_START             (15)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ldi0_END               (15)
#define SOC_CRGPERIPH_PEREN3_gt_clk_edc0_START             (17)
#define SOC_CRGPERIPH_PEREN3_gt_clk_edc0_END               (17)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_gps_gt_en_START    (18)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_gps_gt_en_END      (18)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_audio_gt_en_START  (19)
#define SOC_CRGPERIPH_PEREN3_sc_abb_pll_audio_gt_en_END    (19)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy0_cfg_START      (20)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy0_cfg_END        (20)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy1_cfg_START      (21)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy1_cfg_END        (21)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy2_cfg_START      (22)
#define SOC_CRGPERIPH_PEREN3_gt_clk_rxdphy2_cfg_END        (22)
#define SOC_CRGPERIPH_PEREN3_gt_aclk_isp_START             (23)
#define SOC_CRGPERIPH_PEREN3_gt_aclk_isp_END               (23)
#define SOC_CRGPERIPH_PEREN3_gt_hclk_isp_START             (24)
#define SOC_CRGPERIPH_PEREN3_gt_hclk_isp_END               (24)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ispfunc_START          (25)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ispfunc_END            (25)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ispa7cfg_START         (27)
#define SOC_CRGPERIPH_PEREN3_gt_clk_ispa7cfg_END           (27)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy0_cfg_START      (28)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy0_cfg_END        (28)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy0_ref_START      (29)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy0_ref_END        (29)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy1_cfg_START      (30)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy1_cfg_END        (30)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy1_ref_START      (31)
#define SOC_CRGPERIPH_PEREN3_gt_clk_txdphy1_ref_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERDIS3_UNION
 �ṹ˵��  : PERDIS3 �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ�ӽ�ֹ�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_dmac_lpm3       : 1;  /* bit[0]  : ����ʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_dmac_acpu       : 1;  /* bit[1]  :  */
        unsigned int  gt_clk_dmac_mcpu       : 1;  /* bit[2]  :  */
        unsigned int  gt_pclk_g3d            : 1;  /* bit[3]  :  */
        unsigned int  gt_clk_g3dmt           : 1;  /* bit[4]  :  */
        unsigned int  gt_clk_g3d             : 1;  /* bit[5]  :  */
        unsigned int  sc_abb_pll_gps_en      : 2;  /* bit[6-7]:  */
        unsigned int  sc_abb_pll_audio_en    : 2;  /* bit[8-9]: ������ */
        unsigned int  gt_clk_venc            : 1;  /* bit[10] :  */
        unsigned int  gt_clk_vdec            : 1;  /* bit[11] :  */
        unsigned int  gt_pclk_dss            : 1;  /* bit[12] :  */
        unsigned int  gt_aclk_dss            : 1;  /* bit[13] :  */
        unsigned int  gt_clk_ldi1            : 1;  /* bit[14] :  */
        unsigned int  gt_clk_ldi0            : 1;  /* bit[15] :  */
        unsigned int  reserved_0             : 1;  /* bit[16] : ������ */
        unsigned int  gt_clk_edc0            : 1;  /* bit[17] :  */
        unsigned int  sc_abb_pll_gps_gt_en   : 1;  /* bit[18] :  */
        unsigned int  sc_abb_pll_audio_gt_en : 1;  /* bit[19] :  */
        unsigned int  gt_clk_rxdphy0_cfg     : 1;  /* bit[20] :  */
        unsigned int  gt_clk_rxdphy1_cfg     : 1;  /* bit[21] :  */
        unsigned int  gt_clk_rxdphy2_cfg     : 1;  /* bit[22] :  */
        unsigned int  gt_aclk_isp            : 1;  /* bit[23] :  */
        unsigned int  gt_hclk_isp            : 1;  /* bit[24] :  */
        unsigned int  gt_clk_ispfunc         : 1;  /* bit[25] :  */
        unsigned int  reserved_1             : 1;  /* bit[26] :  */
        unsigned int  gt_clk_ispa7cfg        : 1;  /* bit[27] :  */
        unsigned int  gt_clk_txdphy0_cfg     : 1;  /* bit[28] :  */
        unsigned int  gt_clk_txdphy0_ref     : 1;  /* bit[29] :  */
        unsigned int  gt_clk_txdphy1_cfg     : 1;  /* bit[30] :  */
        unsigned int  gt_clk_txdphy1_ref     : 1;  /* bit[31] : ����ʱ�ӽ�ֹ���ƣ�
                                                                0��д0��Ч����
                                                                1����ֹIPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PERDIS3_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_lpm3_START        (0)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_lpm3_END          (0)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_acpu_START        (1)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_acpu_END          (1)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_mcpu_START        (2)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_dmac_mcpu_END          (2)
#define SOC_CRGPERIPH_PERDIS3_gt_pclk_g3d_START             (3)
#define SOC_CRGPERIPH_PERDIS3_gt_pclk_g3d_END               (3)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_g3dmt_START            (4)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_g3dmt_END              (4)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_g3d_START              (5)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_g3d_END                (5)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_gps_en_START       (6)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_gps_en_END         (7)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_audio_en_START     (8)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_audio_en_END       (9)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_venc_START             (10)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_venc_END               (10)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_vdec_START             (11)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_vdec_END               (11)
#define SOC_CRGPERIPH_PERDIS3_gt_pclk_dss_START             (12)
#define SOC_CRGPERIPH_PERDIS3_gt_pclk_dss_END               (12)
#define SOC_CRGPERIPH_PERDIS3_gt_aclk_dss_START             (13)
#define SOC_CRGPERIPH_PERDIS3_gt_aclk_dss_END               (13)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ldi1_START             (14)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ldi1_END               (14)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ldi0_START             (15)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ldi0_END               (15)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_edc0_START             (17)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_edc0_END               (17)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_gps_gt_en_START    (18)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_gps_gt_en_END      (18)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_audio_gt_en_START  (19)
#define SOC_CRGPERIPH_PERDIS3_sc_abb_pll_audio_gt_en_END    (19)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy0_cfg_START      (20)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy0_cfg_END        (20)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy1_cfg_START      (21)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy1_cfg_END        (21)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy2_cfg_START      (22)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_rxdphy2_cfg_END        (22)
#define SOC_CRGPERIPH_PERDIS3_gt_aclk_isp_START             (23)
#define SOC_CRGPERIPH_PERDIS3_gt_aclk_isp_END               (23)
#define SOC_CRGPERIPH_PERDIS3_gt_hclk_isp_START             (24)
#define SOC_CRGPERIPH_PERDIS3_gt_hclk_isp_END               (24)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ispfunc_START          (25)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ispfunc_END            (25)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ispa7cfg_START         (27)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_ispa7cfg_END           (27)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy0_cfg_START      (28)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy0_cfg_END        (28)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy0_ref_START      (29)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy0_ref_END        (29)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy1_cfg_START      (30)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy1_cfg_END        (30)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy1_ref_START      (31)
#define SOC_CRGPERIPH_PERDIS3_gt_clk_txdphy1_ref_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERCLKEN3_UNION
 �ṹ˵��  : PERCLKEN3 �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x04010007�����:32
 �Ĵ���˵��: ����ʱ��ʹ��״̬�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_dmac_lpm3       : 1;  /* bit[0]  : ����ʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_dmac_acpu       : 1;  /* bit[1]  :  */
        unsigned int  gt_clk_dmac_mcpu       : 1;  /* bit[2]  :  */
        unsigned int  gt_pclk_g3d            : 1;  /* bit[3]  :  */
        unsigned int  gt_clk_g3dmt           : 1;  /* bit[4]  :  */
        unsigned int  gt_clk_g3d             : 1;  /* bit[5]  :  */
        unsigned int  sc_abb_pll_gps_en      : 2;  /* bit[6-7]:  */
        unsigned int  sc_abb_pll_audio_en    : 2;  /* bit[8-9]: ������ */
        unsigned int  gt_clk_venc            : 1;  /* bit[10] :  */
        unsigned int  gt_clk_vdec            : 1;  /* bit[11] :  */
        unsigned int  gt_pclk_dss            : 1;  /* bit[12] :  */
        unsigned int  gt_aclk_dss            : 1;  /* bit[13] :  */
        unsigned int  gt_clk_ldi1            : 1;  /* bit[14] :  */
        unsigned int  gt_clk_ldi0            : 1;  /* bit[15] :  */
        unsigned int  reserved_0             : 1;  /* bit[16] : ������ */
        unsigned int  gt_clk_edc0            : 1;  /* bit[17] :  */
        unsigned int  sc_abb_pll_gps_gt_en   : 1;  /* bit[18] :  */
        unsigned int  sc_abb_pll_audio_gt_en : 1;  /* bit[19] :  */
        unsigned int  gt_clk_rxdphy0_cfg     : 1;  /* bit[20] :  */
        unsigned int  gt_clk_rxdphy1_cfg     : 1;  /* bit[21] :  */
        unsigned int  gt_clk_rxdphy2_cfg     : 1;  /* bit[22] :  */
        unsigned int  gt_aclk_isp            : 1;  /* bit[23] :  */
        unsigned int  gt_hclk_isp            : 1;  /* bit[24] :  */
        unsigned int  gt_clk_ispfunc         : 1;  /* bit[25] :  */
        unsigned int  reserved_1             : 1;  /* bit[26] :  */
        unsigned int  gt_clk_ispa7cfg        : 1;  /* bit[27] :  */
        unsigned int  gt_clk_txdphy0_cfg     : 1;  /* bit[28] :  */
        unsigned int  gt_clk_txdphy0_ref     : 1;  /* bit[29] :  */
        unsigned int  gt_clk_txdphy1_cfg     : 1;  /* bit[30] :  */
        unsigned int  gt_clk_txdphy1_ref     : 1;  /* bit[31] : ����ʱ��ʹ��״̬��
                                                                0��IPʱ��ʹ�ܳ���״̬��
                                                                1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERCLKEN3_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_lpm3_START        (0)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_lpm3_END          (0)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_acpu_START        (1)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_acpu_END          (1)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_mcpu_START        (2)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_dmac_mcpu_END          (2)
#define SOC_CRGPERIPH_PERCLKEN3_gt_pclk_g3d_START             (3)
#define SOC_CRGPERIPH_PERCLKEN3_gt_pclk_g3d_END               (3)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_g3dmt_START            (4)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_g3dmt_END              (4)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_g3d_START              (5)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_g3d_END                (5)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_gps_en_START       (6)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_gps_en_END         (7)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_audio_en_START     (8)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_audio_en_END       (9)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_venc_START             (10)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_venc_END               (10)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_vdec_START             (11)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_vdec_END               (11)
#define SOC_CRGPERIPH_PERCLKEN3_gt_pclk_dss_START             (12)
#define SOC_CRGPERIPH_PERCLKEN3_gt_pclk_dss_END               (12)
#define SOC_CRGPERIPH_PERCLKEN3_gt_aclk_dss_START             (13)
#define SOC_CRGPERIPH_PERCLKEN3_gt_aclk_dss_END               (13)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ldi1_START             (14)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ldi1_END               (14)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ldi0_START             (15)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ldi0_END               (15)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_edc0_START             (17)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_edc0_END               (17)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_gps_gt_en_START    (18)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_gps_gt_en_END      (18)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_audio_gt_en_START  (19)
#define SOC_CRGPERIPH_PERCLKEN3_sc_abb_pll_audio_gt_en_END    (19)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy0_cfg_START      (20)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy0_cfg_END        (20)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy1_cfg_START      (21)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy1_cfg_END        (21)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy2_cfg_START      (22)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_rxdphy2_cfg_END        (22)
#define SOC_CRGPERIPH_PERCLKEN3_gt_aclk_isp_START             (23)
#define SOC_CRGPERIPH_PERCLKEN3_gt_aclk_isp_END               (23)
#define SOC_CRGPERIPH_PERCLKEN3_gt_hclk_isp_START             (24)
#define SOC_CRGPERIPH_PERCLKEN3_gt_hclk_isp_END               (24)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ispfunc_START          (25)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ispfunc_END            (25)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ispa7cfg_START         (27)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_ispa7cfg_END           (27)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy0_cfg_START      (28)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy0_cfg_END        (28)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy0_ref_START      (29)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy0_ref_END        (29)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy1_cfg_START      (30)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy1_cfg_END        (30)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy1_ref_START      (31)
#define SOC_CRGPERIPH_PERCLKEN3_gt_clk_txdphy1_ref_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERSTAT3_UNION
 �ṹ˵��  : PERSTAT3 �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x040D03C7�����:32
 �Ĵ���˵��: ����ʱ������״̬�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_dmac0       : 1;  /* bit[0] : DMACʱ��״̬��̬�仯 */
        unsigned int  gt_clk_dmac1       : 1;  /* bit[1] : DMACʱ��״̬��̬�仯 */
        unsigned int  reserved_0         : 1;  /* bit[2] : ������ */
        unsigned int  gt_pclk_g3d        : 1;  /* bit[3] :  */
        unsigned int  gt_clk_g3dmt       : 1;  /* bit[4] :  */
        unsigned int  gt_clk_g3d         : 1;  /* bit[5] :  */
        unsigned int  reserved_1         : 1;  /* bit[6] : ������ */
        unsigned int  reserved_2         : 1;  /* bit[7] : ������ */
        unsigned int  reserved_3         : 1;  /* bit[8] : ������ */
        unsigned int  reserved_4         : 1;  /* bit[9] :  */
        unsigned int  gt_clk_venc        : 1;  /* bit[10]:  */
        unsigned int  gt_clk_vdec        : 1;  /* bit[11]:  */
        unsigned int  gt_pclk_dss        : 1;  /* bit[12]:  */
        unsigned int  gt_aclk_dss        : 1;  /* bit[13]:  */
        unsigned int  gt_clk_ldi1        : 1;  /* bit[14]:  */
        unsigned int  gt_clk_ldi0        : 1;  /* bit[15]:  */
        unsigned int  reserved_5         : 1;  /* bit[16]: ������ */
        unsigned int  gt_clk_edc0        : 1;  /* bit[17]:  */
        unsigned int  reserved_6         : 1;  /* bit[18]: ������ */
        unsigned int  reserved_7         : 1;  /* bit[19]: ������ */
        unsigned int  gt_clk_rxdphy0_cfg : 1;  /* bit[20]:  */
        unsigned int  gt_clk_rxdphy1_cfg : 1;  /* bit[21]:  */
        unsigned int  gt_clk_rxdphy2_cfg : 1;  /* bit[22]:  */
        unsigned int  gt_aclk_isp        : 1;  /* bit[23]:  */
        unsigned int  gt_hclk_isp        : 1;  /* bit[24]:  */
        unsigned int  gt_clk_ispfunc     : 1;  /* bit[25]:  */
        unsigned int  reserved_8         : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ispa7cfg    : 1;  /* bit[27]:  */
        unsigned int  gt_clk_txdphy0_cfg : 1;  /* bit[28]:  */
        unsigned int  gt_clk_txdphy0_ref : 1;  /* bit[29]:  */
        unsigned int  gt_clk_txdphy1_cfg : 1;  /* bit[30]:  */
        unsigned int  gt_clk_txdphy1_ref : 1;  /* bit[31]: ����ʱ������״̬��
                                                           0��IPʱ�ӽ�ֹ״̬��
                                                           1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERSTAT3_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_dmac0_START        (0)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_dmac0_END          (0)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_dmac1_START        (1)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_dmac1_END          (1)
#define SOC_CRGPERIPH_PERSTAT3_gt_pclk_g3d_START         (3)
#define SOC_CRGPERIPH_PERSTAT3_gt_pclk_g3d_END           (3)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_g3dmt_START        (4)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_g3dmt_END          (4)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_g3d_START          (5)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_g3d_END            (5)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_venc_START         (10)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_venc_END           (10)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_vdec_START         (11)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_vdec_END           (11)
#define SOC_CRGPERIPH_PERSTAT3_gt_pclk_dss_START         (12)
#define SOC_CRGPERIPH_PERSTAT3_gt_pclk_dss_END           (12)
#define SOC_CRGPERIPH_PERSTAT3_gt_aclk_dss_START         (13)
#define SOC_CRGPERIPH_PERSTAT3_gt_aclk_dss_END           (13)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ldi1_START         (14)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ldi1_END           (14)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ldi0_START         (15)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ldi0_END           (15)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_edc0_START         (17)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_edc0_END           (17)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy0_cfg_START  (20)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy0_cfg_END    (20)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy1_cfg_START  (21)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy1_cfg_END    (21)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy2_cfg_START  (22)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_rxdphy2_cfg_END    (22)
#define SOC_CRGPERIPH_PERSTAT3_gt_aclk_isp_START         (23)
#define SOC_CRGPERIPH_PERSTAT3_gt_aclk_isp_END           (23)
#define SOC_CRGPERIPH_PERSTAT3_gt_hclk_isp_START         (24)
#define SOC_CRGPERIPH_PERSTAT3_gt_hclk_isp_END           (24)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ispfunc_START      (25)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ispfunc_END        (25)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ispa7cfg_START     (27)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_ispa7cfg_END       (27)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy0_cfg_START  (28)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy0_cfg_END    (28)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy0_ref_START  (29)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy0_ref_END    (29)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy1_cfg_START  (30)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy1_cfg_END    (30)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy1_ref_START  (31)
#define SOC_CRGPERIPH_PERSTAT3_gt_clk_txdphy1_ref_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PEREN4_UNION
 �ṹ˵��  : PEREN4 �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��ʹ�ܼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_usb3otg_ref     : 1;  /* bit[0] : ����ʱ��ʹ�ܿ��ƣ�
                                                               0��д0��Ч����
                                                               1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_aclk_usb3otg        : 1;  /* bit[1] :  */
        unsigned int  gt_clk_usb3phy_ref     : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ivp32dsp_core   : 1;  /* bit[3] :  */
        unsigned int  reserved_0             : 1;  /* bit[4] :  */
        unsigned int  gt_clk_ivp32dsp_sysbus : 1;  /* bit[5] :  */
        unsigned int  gt_clk_usb3phy_ref_pll : 1;  /* bit[6] :  */
        unsigned int  gt_clk_ivp32dsp_tcxo   : 1;  /* bit[7] :  */
        unsigned int  gt_clk_perf_stat       : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_perf_stat      : 1;  /* bit[9] :  */
        unsigned int  gt_aclk_perf_stat      : 1;  /* bit[10]:  */
        unsigned int  reserved_1             : 1;  /* bit[11]: ������ */
        unsigned int  gt_clk_secp            : 1;  /* bit[12]:  */
        unsigned int  reserved_2             : 1;  /* bit[13]: ������ */
        unsigned int  gt_clk_emmc1_3p2m      : 1;  /* bit[14]:  */
        unsigned int  gt_clk_emmc0           : 1;  /* bit[15]:  */
        unsigned int  gt_clk_emmc1           : 1;  /* bit[16]:  */
        unsigned int  gt_clk_sd              : 1;  /* bit[17]:  */
        unsigned int  gt_clk_sdio0           : 1;  /* bit[18]:  */
        unsigned int  gt_clk_sdio1           : 1;  /* bit[19]:  */
        unsigned int  reserved_3             : 1;  /* bit[20]: ������ */
        unsigned int  gt_clk_a57_tsensor     : 1;  /* bit[21]:  */
        unsigned int  gt_clk_a53_tsensor     : 1;  /* bit[22]:  */
        unsigned int  gt_clk_apll0_sscg      : 1;  /* bit[23]:  */
        unsigned int  gt_clk_apll1_sscg      : 1;  /* bit[24]:  */
        unsigned int  gt_clk_apll2_sscg      : 1;  /* bit[25]:  */
        unsigned int  gt_clk_ppll1_sscg      : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ppll2_sscg      : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ppll3_sscg      : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ppll4_sscg      : 1;  /* bit[29]:  */
        unsigned int  gt_clk_ppll5_sscg      : 1;  /* bit[30]:  */
        unsigned int  gt_clk_a53_tp          : 1;  /* bit[31]: ����ʱ��ʹ�ܿ��ƣ�maya_svdf 64��Ƶ����ʱ�ӣ���
                                                               0��д0��Ч����
                                                               1��ʹ��IPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PEREN4_UNION;
#endif
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3otg_ref_START      (0)
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3otg_ref_END        (0)
#define SOC_CRGPERIPH_PEREN4_gt_aclk_usb3otg_START         (1)
#define SOC_CRGPERIPH_PEREN4_gt_aclk_usb3otg_END           (1)
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3phy_ref_START      (2)
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3phy_ref_END        (2)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_core_START    (3)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_core_END      (3)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_sysbus_START  (5)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_sysbus_END    (5)
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3phy_ref_pll_START  (6)
#define SOC_CRGPERIPH_PEREN4_gt_clk_usb3phy_ref_pll_END    (6)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_tcxo_START    (7)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ivp32dsp_tcxo_END      (7)
#define SOC_CRGPERIPH_PEREN4_gt_clk_perf_stat_START        (8)
#define SOC_CRGPERIPH_PEREN4_gt_clk_perf_stat_END          (8)
#define SOC_CRGPERIPH_PEREN4_gt_pclk_perf_stat_START       (9)
#define SOC_CRGPERIPH_PEREN4_gt_pclk_perf_stat_END         (9)
#define SOC_CRGPERIPH_PEREN4_gt_aclk_perf_stat_START       (10)
#define SOC_CRGPERIPH_PEREN4_gt_aclk_perf_stat_END         (10)
#define SOC_CRGPERIPH_PEREN4_gt_clk_secp_START             (12)
#define SOC_CRGPERIPH_PEREN4_gt_clk_secp_END               (12)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc1_3p2m_START       (14)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc1_3p2m_END         (14)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc0_START            (15)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc0_END              (15)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc1_START            (16)
#define SOC_CRGPERIPH_PEREN4_gt_clk_emmc1_END              (16)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sd_START               (17)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sd_END                 (17)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sdio0_START            (18)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sdio0_END              (18)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sdio1_START            (19)
#define SOC_CRGPERIPH_PEREN4_gt_clk_sdio1_END              (19)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a57_tsensor_START      (21)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a57_tsensor_END        (21)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a53_tsensor_START      (22)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a53_tsensor_END        (22)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll0_sscg_START       (23)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll0_sscg_END         (23)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll1_sscg_START       (24)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll1_sscg_END         (24)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll2_sscg_START       (25)
#define SOC_CRGPERIPH_PEREN4_gt_clk_apll2_sscg_END         (25)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll1_sscg_START       (26)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll1_sscg_END         (26)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll2_sscg_START       (27)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll2_sscg_END         (27)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll3_sscg_START       (28)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll3_sscg_END         (28)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll4_sscg_START       (29)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll4_sscg_END         (29)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll5_sscg_START       (30)
#define SOC_CRGPERIPH_PEREN4_gt_clk_ppll5_sscg_END         (30)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a53_tp_START           (31)
#define SOC_CRGPERIPH_PEREN4_gt_clk_a53_tp_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERDIS4_UNION
 �ṹ˵��  : PERDIS4 �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ�ӽ�ֹ�Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_usb3otg_ref     : 1;  /* bit[0] : ����ʱ�ӽ�ֹ���ƣ�
                                                               0��д0��Ч����
                                                               1����ֹIPʱ�ӡ� */
        unsigned int  gt_aclk_usb3otg        : 1;  /* bit[1] :  */
        unsigned int  gt_clk_usb3phy_ref     : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ivp32dsp_core   : 1;  /* bit[3] :  */
        unsigned int  reserved_0             : 1;  /* bit[4] :  */
        unsigned int  gt_clk_ivp32dsp_sysbus : 1;  /* bit[5] :  */
        unsigned int  gt_clk_usb3phy_ref_pll : 1;  /* bit[6] :  */
        unsigned int  gt_clk_ivp32dsp_tcxo   : 1;  /* bit[7] :  */
        unsigned int  gt_clk_perf_stat       : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_perf_stat      : 1;  /* bit[9] :  */
        unsigned int  gt_aclk_perf_stat      : 1;  /* bit[10]:  */
        unsigned int  reserved_1             : 1;  /* bit[11]: ������ */
        unsigned int  gt_clk_secp            : 1;  /* bit[12]:  */
        unsigned int  reserved_2             : 1;  /* bit[13]: ������ */
        unsigned int  gt_clk_emmc1_3p2m      : 1;  /* bit[14]:  */
        unsigned int  gt_clk_emmc0           : 1;  /* bit[15]:  */
        unsigned int  gt_clk_emmc1           : 1;  /* bit[16]:  */
        unsigned int  gt_clk_sd              : 1;  /* bit[17]:  */
        unsigned int  gt_clk_sdio0           : 1;  /* bit[18]:  */
        unsigned int  gt_clk_sdio1           : 1;  /* bit[19]: ������ */
        unsigned int  reserved_3             : 1;  /* bit[20]: ������ */
        unsigned int  gt_clk_a57_tsensor     : 1;  /* bit[21]:  */
        unsigned int  gt_clk_a53_tsensor     : 1;  /* bit[22]:  */
        unsigned int  gt_clk_apll0_sscg      : 1;  /* bit[23]:  */
        unsigned int  gt_clk_apll1_sscg      : 1;  /* bit[24]:  */
        unsigned int  gt_clk_apll2_sscg      : 1;  /* bit[25]:  */
        unsigned int  gt_clk_ppll1_sscg      : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ppll2_sscg      : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ppll3_sscg      : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ppll4_sscg      : 1;  /* bit[29]:  */
        unsigned int  gt_clk_ppll5_sscg      : 1;  /* bit[30]:  */
        unsigned int  gt_clk_a53_tp          : 1;  /* bit[31]: ����ʱ�ӽ�ֹ���ƣ�maya_svdf 64��Ƶ����ʱ�ӣ���
                                                               0��д0��Ч����
                                                               1����ֹIPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PERDIS4_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3otg_ref_START      (0)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3otg_ref_END        (0)
#define SOC_CRGPERIPH_PERDIS4_gt_aclk_usb3otg_START         (1)
#define SOC_CRGPERIPH_PERDIS4_gt_aclk_usb3otg_END           (1)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3phy_ref_START      (2)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3phy_ref_END        (2)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_core_START    (3)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_core_END      (3)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_sysbus_START  (5)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_sysbus_END    (5)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3phy_ref_pll_START  (6)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_usb3phy_ref_pll_END    (6)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_tcxo_START    (7)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ivp32dsp_tcxo_END      (7)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_perf_stat_START        (8)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_perf_stat_END          (8)
#define SOC_CRGPERIPH_PERDIS4_gt_pclk_perf_stat_START       (9)
#define SOC_CRGPERIPH_PERDIS4_gt_pclk_perf_stat_END         (9)
#define SOC_CRGPERIPH_PERDIS4_gt_aclk_perf_stat_START       (10)
#define SOC_CRGPERIPH_PERDIS4_gt_aclk_perf_stat_END         (10)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_secp_START             (12)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_secp_END               (12)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc1_3p2m_START       (14)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc1_3p2m_END         (14)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc0_START            (15)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc0_END              (15)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc1_START            (16)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_emmc1_END              (16)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sd_START               (17)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sd_END                 (17)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sdio0_START            (18)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sdio0_END              (18)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sdio1_START            (19)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_sdio1_END              (19)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a57_tsensor_START      (21)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a57_tsensor_END        (21)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a53_tsensor_START      (22)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a53_tsensor_END        (22)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll0_sscg_START       (23)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll0_sscg_END         (23)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll1_sscg_START       (24)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll1_sscg_END         (24)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll2_sscg_START       (25)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_apll2_sscg_END         (25)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll1_sscg_START       (26)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll1_sscg_END         (26)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll2_sscg_START       (27)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll2_sscg_END         (27)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll3_sscg_START       (28)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll3_sscg_END         (28)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll4_sscg_START       (29)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll4_sscg_END         (29)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll5_sscg_START       (30)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_ppll5_sscg_END         (30)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a53_tp_START           (31)
#define SOC_CRGPERIPH_PERDIS4_gt_clk_a53_tp_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERCLKEN4_UNION
 �ṹ˵��  : PERCLKEN4 �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x7FF078D7�����:32
 �Ĵ���˵��: ����ʱ��ʹ��״̬�Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_usb3otg_ref     : 1;  /* bit[0] : ����ʱ��ʹ��״̬��
                                                               0��IPʱ��ʹ�ܳ���״̬��
                                                               1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_aclk_usb3otg        : 1;  /* bit[1] :  */
        unsigned int  gt_clk_usb3phy_ref     : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ivp32dsp_core   : 1;  /* bit[3] :  */
        unsigned int  reserved_0             : 1;  /* bit[4] : ������ */
        unsigned int  gt_clk_ivp32dsp_sysbus : 1;  /* bit[5] :  */
        unsigned int  gt_clk_usb3phy_ref_pll : 1;  /* bit[6] :  */
        unsigned int  gt_clk_ivp32dsp_tcxo   : 1;  /* bit[7] :  */
        unsigned int  gt_clk_perf_stat       : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_perf_stat      : 1;  /* bit[9] :  */
        unsigned int  gt_aclk_perf_stat      : 1;  /* bit[10]:  */
        unsigned int  reserved_1             : 1;  /* bit[11]: ������ */
        unsigned int  gt_clk_secp            : 1;  /* bit[12]:  */
        unsigned int  reserved_2             : 1;  /* bit[13]: ������ */
        unsigned int  gt_clk_emmc1_3p2m      : 1;  /* bit[14]:  */
        unsigned int  gt_clk_emmc0           : 1;  /* bit[15]:  */
        unsigned int  gt_clk_emmc1           : 1;  /* bit[16]:  */
        unsigned int  gt_clk_sd              : 1;  /* bit[17]:  */
        unsigned int  gt_clk_sdio0           : 1;  /* bit[18]:  */
        unsigned int  gt_clk_sdio1           : 1;  /* bit[19]:  */
        unsigned int  reserved_3             : 1;  /* bit[20]: ������ */
        unsigned int  gt_clk_a57_tsensor     : 1;  /* bit[21]:  */
        unsigned int  gt_clk_a53_tsensor     : 1;  /* bit[22]:  */
        unsigned int  gt_clk_apll0_sscg      : 1;  /* bit[23]:  */
        unsigned int  gt_clk_apll1_sscg      : 1;  /* bit[24]:  */
        unsigned int  gt_clk_apll2_sscg      : 1;  /* bit[25]:  */
        unsigned int  gt_clk_ppll1_sscg      : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ppll2_sscg      : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ppll3_sscg      : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ppll4_sscg      : 1;  /* bit[29]:  */
        unsigned int  gt_clk_ppll5_sscg      : 1;  /* bit[30]:  */
        unsigned int  gt_clk_a53_tp          : 1;  /* bit[31]: ����ʱ��ʹ��״̬��maya_svdf 64��Ƶ����ʱ�ӣ���
                                                               0��IPʱ��ʹ�ܳ���״̬��
                                                               1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERCLKEN4_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3otg_ref_START      (0)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3otg_ref_END        (0)
#define SOC_CRGPERIPH_PERCLKEN4_gt_aclk_usb3otg_START         (1)
#define SOC_CRGPERIPH_PERCLKEN4_gt_aclk_usb3otg_END           (1)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3phy_ref_START      (2)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3phy_ref_END        (2)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_core_START    (3)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_core_END      (3)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_sysbus_START  (5)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_sysbus_END    (5)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3phy_ref_pll_START  (6)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_usb3phy_ref_pll_END    (6)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_tcxo_START    (7)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ivp32dsp_tcxo_END      (7)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_perf_stat_START        (8)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_perf_stat_END          (8)
#define SOC_CRGPERIPH_PERCLKEN4_gt_pclk_perf_stat_START       (9)
#define SOC_CRGPERIPH_PERCLKEN4_gt_pclk_perf_stat_END         (9)
#define SOC_CRGPERIPH_PERCLKEN4_gt_aclk_perf_stat_START       (10)
#define SOC_CRGPERIPH_PERCLKEN4_gt_aclk_perf_stat_END         (10)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_secp_START             (12)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_secp_END               (12)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc1_3p2m_START       (14)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc1_3p2m_END         (14)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc0_START            (15)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc0_END              (15)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc1_START            (16)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_emmc1_END              (16)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sd_START               (17)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sd_END                 (17)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sdio0_START            (18)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sdio0_END              (18)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sdio1_START            (19)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_sdio1_END              (19)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a57_tsensor_START      (21)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a57_tsensor_END        (21)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a53_tsensor_START      (22)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a53_tsensor_END        (22)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll0_sscg_START       (23)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll0_sscg_END         (23)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll1_sscg_START       (24)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll1_sscg_END         (24)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll2_sscg_START       (25)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_apll2_sscg_END         (25)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll1_sscg_START       (26)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll1_sscg_END         (26)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll2_sscg_START       (27)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll2_sscg_END         (27)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll3_sscg_START       (28)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll3_sscg_END         (28)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll4_sscg_START       (29)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll4_sscg_END         (29)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll5_sscg_START       (30)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_ppll5_sscg_END         (30)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a53_tp_START           (31)
#define SOC_CRGPERIPH_PERCLKEN4_gt_clk_a53_tp_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERSTAT4_UNION
 �ṹ˵��  : PERSTAT4 �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x7FF078D7�����:32
 �Ĵ���˵��: ����ʱ������״̬�Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_usb3otg_ref     : 1;  /* bit[0] : ����ʱ������״̬��
                                                               0��IPʱ�ӽ�ֹ״̬��
                                                               1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_aclk_usb3otg        : 1;  /* bit[1] :  */
        unsigned int  gt_clk_usb3phy_ref     : 1;  /* bit[2] :  */
        unsigned int  gt_clk_ivp32dsp_core   : 1;  /* bit[3] :  */
        unsigned int  reserved_0             : 1;  /* bit[4] : ������ */
        unsigned int  gt_clk_ivp32dsp_sysbus : 1;  /* bit[5] :  */
        unsigned int  gt_clk_usb3phy_ref_pll : 1;  /* bit[6] :  */
        unsigned int  gt_clk_ivp32dsp_tcxo   : 1;  /* bit[7] :  */
        unsigned int  gt_clk_perf_stat       : 1;  /* bit[8] :  */
        unsigned int  gt_pclk_perf_stat      : 1;  /* bit[9] :  */
        unsigned int  gt_aclk_perf_stat      : 1;  /* bit[10]:  */
        unsigned int  gt_clk_secs            : 1;  /* bit[11]:  */
        unsigned int  gt_clk_secp            : 1;  /* bit[12]:  */
        unsigned int  reserved_1             : 1;  /* bit[13]: ������ */
        unsigned int  gt_clk_emmc1_3p2m      : 1;  /* bit[14]:  */
        unsigned int  gt_clk_emmc0           : 1;  /* bit[15]:  */
        unsigned int  gt_clk_emmc1           : 1;  /* bit[16]:  */
        unsigned int  gt_clk_sd              : 1;  /* bit[17]:  */
        unsigned int  gt_clk_sdio0           : 1;  /* bit[18]:  */
        unsigned int  gt_clk_sdio1           : 1;  /* bit[19]:  */
        unsigned int  reserved_2             : 1;  /* bit[20]: ������ */
        unsigned int  gt_clk_a57_tsensor     : 1;  /* bit[21]:  */
        unsigned int  gt_clk_a53_tsensor     : 1;  /* bit[22]:  */
        unsigned int  gt_clk_apll0_sscg      : 1;  /* bit[23]:  */
        unsigned int  gt_clk_apll1_sscg      : 1;  /* bit[24]:  */
        unsigned int  gt_clk_apll2_sscg      : 1;  /* bit[25]:  */
        unsigned int  gt_clk_ppll1_sscg      : 1;  /* bit[26]:  */
        unsigned int  gt_clk_ppll2_sscg      : 1;  /* bit[27]:  */
        unsigned int  gt_clk_ppll3_sscg      : 1;  /* bit[28]:  */
        unsigned int  gt_clk_ppll4_sscg      : 1;  /* bit[29]:  */
        unsigned int  gt_clk_ppll5_sscg      : 1;  /* bit[30]:  */
        unsigned int  gt_clk_a53_tp          : 1;  /* bit[31]: ����ʱ������״̬��maya_svdf 64��Ƶ����ʱ�ӣ���
                                                               0��IPʱ�ӽ�ֹ״̬��
                                                               1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERSTAT4_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3otg_ref_START      (0)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3otg_ref_END        (0)
#define SOC_CRGPERIPH_PERSTAT4_gt_aclk_usb3otg_START         (1)
#define SOC_CRGPERIPH_PERSTAT4_gt_aclk_usb3otg_END           (1)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3phy_ref_START      (2)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3phy_ref_END        (2)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_core_START    (3)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_core_END      (3)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_sysbus_START  (5)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_sysbus_END    (5)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3phy_ref_pll_START  (6)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_usb3phy_ref_pll_END    (6)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_tcxo_START    (7)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ivp32dsp_tcxo_END      (7)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_perf_stat_START        (8)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_perf_stat_END          (8)
#define SOC_CRGPERIPH_PERSTAT4_gt_pclk_perf_stat_START       (9)
#define SOC_CRGPERIPH_PERSTAT4_gt_pclk_perf_stat_END         (9)
#define SOC_CRGPERIPH_PERSTAT4_gt_aclk_perf_stat_START       (10)
#define SOC_CRGPERIPH_PERSTAT4_gt_aclk_perf_stat_END         (10)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_secs_START             (11)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_secs_END               (11)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_secp_START             (12)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_secp_END               (12)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc1_3p2m_START       (14)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc1_3p2m_END         (14)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc0_START            (15)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc0_END              (15)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc1_START            (16)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_emmc1_END              (16)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sd_START               (17)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sd_END                 (17)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sdio0_START            (18)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sdio0_END              (18)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sdio1_START            (19)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_sdio1_END              (19)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a57_tsensor_START      (21)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a57_tsensor_END        (21)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a53_tsensor_START      (22)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a53_tsensor_END        (22)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll0_sscg_START       (23)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll0_sscg_END         (23)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll1_sscg_START       (24)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll1_sscg_END         (24)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll2_sscg_START       (25)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_apll2_sscg_END         (25)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll1_sscg_START       (26)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll1_sscg_END         (26)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll2_sscg_START       (27)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll2_sscg_END         (27)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll3_sscg_START       (28)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll3_sscg_END         (28)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll4_sscg_START       (29)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll4_sscg_END         (29)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll5_sscg_START       (30)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_ppll5_sscg_END         (30)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a53_tp_START           (31)
#define SOC_CRGPERIPH_PERSTAT4_gt_clk_a53_tp_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PEREN5_UNION
 �ṹ˵��  : PEREN5 �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��ʹ�ܼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_sysbus2hkmem       : 1;  /* bit[0]    : ����ʱ��ʹ�ܿ��ƣ�
                                                                     0��д0��Ч����
                                                                     1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_modem_sys          : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_modem_subsys       : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_noc_timeout_extref : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_ispa7              : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_g3d_tsensor        : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_modem_tsensor      : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_slimbus            : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_lpmcu              : 1;  /* bit[8]    : LPM3��ϵͳʱ��ʹ�ܿ��ƣ�
                                                                     0��д0��Ч����
                                                                     1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_a57_hpm            : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_cci2sysbus_asyn    : 1;  /* bit[10]   : CCI2SYSBUS�첽�ŵ��ſؿ��ơ� */
        unsigned int  gt_clk_ao_hpm             : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_peri_hpm           : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_a53_hpm            : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_cci400             : 1;  /* bit[14]   :  */
        unsigned int  gt_clk_gpu_hpm            : 1;  /* bit[15]   :  */
        unsigned int  gt_clk_isp_snclk          : 3;  /* bit[16-18]:  */
        unsigned int  reserved_0                : 1;  /* bit[19]   : ������ */
        unsigned int  reserved_1                : 1;  /* bit[20]   : ������ */
        unsigned int  reserved_2                : 1;  /* bit[21]   : ������ */
        unsigned int  reserved_3                : 1;  /* bit[22]   : ������ */
        unsigned int  gt_clk_modem_mcpu_tp      : 1;  /* bit[23]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_c   : 1;  /* bit[24]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_d   : 1;  /* bit[25]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_b   : 1;  /* bit[26]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_a   : 1;  /* bit[27]   :  */
        unsigned int  gt_pclk_dsi0              : 1;  /* bit[28]   :  */
        unsigned int  gt_pclk_dsi1              : 1;  /* bit[29]   : 1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_lpmcu_tp           : 1;  /* bit[30]   : 0��д0��Ч���� */
        unsigned int  gt_clk_sysbus_tp          : 1;  /* bit[31]   : ����ʱ��ʹ�ܿ��ƣ�
                                                                     0��д0��Ч����
                                                                     1��ʹ��IPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PEREN5_UNION;
#endif
#define SOC_CRGPERIPH_PEREN5_gt_clk_sysbus2hkmem_START        (0)
#define SOC_CRGPERIPH_PEREN5_gt_clk_sysbus2hkmem_END          (0)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_sys_START           (1)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_sys_END             (1)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_subsys_START        (2)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_subsys_END          (2)
#define SOC_CRGPERIPH_PEREN5_gt_clk_noc_timeout_extref_START  (3)
#define SOC_CRGPERIPH_PEREN5_gt_clk_noc_timeout_extref_END    (3)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ispa7_START               (4)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ispa7_END                 (4)
#define SOC_CRGPERIPH_PEREN5_gt_clk_g3d_tsensor_START         (5)
#define SOC_CRGPERIPH_PEREN5_gt_clk_g3d_tsensor_END           (5)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_tsensor_START       (6)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_tsensor_END         (6)
#define SOC_CRGPERIPH_PEREN5_gt_clk_slimbus_START             (7)
#define SOC_CRGPERIPH_PEREN5_gt_clk_slimbus_END               (7)
#define SOC_CRGPERIPH_PEREN5_gt_clk_lpmcu_START               (8)
#define SOC_CRGPERIPH_PEREN5_gt_clk_lpmcu_END                 (8)
#define SOC_CRGPERIPH_PEREN5_gt_clk_a57_hpm_START             (9)
#define SOC_CRGPERIPH_PEREN5_gt_clk_a57_hpm_END               (9)
#define SOC_CRGPERIPH_PEREN5_gt_clk_cci2sysbus_asyn_START     (10)
#define SOC_CRGPERIPH_PEREN5_gt_clk_cci2sysbus_asyn_END       (10)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ao_hpm_START              (11)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ao_hpm_END                (11)
#define SOC_CRGPERIPH_PEREN5_gt_clk_peri_hpm_START            (12)
#define SOC_CRGPERIPH_PEREN5_gt_clk_peri_hpm_END              (12)
#define SOC_CRGPERIPH_PEREN5_gt_clk_a53_hpm_START             (13)
#define SOC_CRGPERIPH_PEREN5_gt_clk_a53_hpm_END               (13)
#define SOC_CRGPERIPH_PEREN5_gt_clk_cci400_START              (14)
#define SOC_CRGPERIPH_PEREN5_gt_clk_cci400_END                (14)
#define SOC_CRGPERIPH_PEREN5_gt_clk_gpu_hpm_START             (15)
#define SOC_CRGPERIPH_PEREN5_gt_clk_gpu_hpm_END               (15)
#define SOC_CRGPERIPH_PEREN5_gt_clk_isp_snclk_START           (16)
#define SOC_CRGPERIPH_PEREN5_gt_clk_isp_snclk_END             (18)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_mcpu_tp_START       (23)
#define SOC_CRGPERIPH_PEREN5_gt_clk_modem_mcpu_tp_END         (23)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_c_START    (24)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_c_END      (24)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_d_START    (25)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_d_END      (25)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_b_START    (26)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_b_END      (26)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_a_START    (27)
#define SOC_CRGPERIPH_PEREN5_gt_clk_ddrphy_apb_dfi_a_END      (27)
#define SOC_CRGPERIPH_PEREN5_gt_pclk_dsi0_START               (28)
#define SOC_CRGPERIPH_PEREN5_gt_pclk_dsi0_END                 (28)
#define SOC_CRGPERIPH_PEREN5_gt_pclk_dsi1_START               (29)
#define SOC_CRGPERIPH_PEREN5_gt_pclk_dsi1_END                 (29)
#define SOC_CRGPERIPH_PEREN5_gt_clk_lpmcu_tp_START            (30)
#define SOC_CRGPERIPH_PEREN5_gt_clk_lpmcu_tp_END              (30)
#define SOC_CRGPERIPH_PEREN5_gt_clk_sysbus_tp_START           (31)
#define SOC_CRGPERIPH_PEREN5_gt_clk_sysbus_tp_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERDIS5_UNION
 �ṹ˵��  : PERDIS5 �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ�ӽ�ֹ�Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_sysbus2hkmem       : 1;  /* bit[0]    : ����ʱ�ӽ�ֹ���ƣ�
                                                                     0��д0��Ч����
                                                                     1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_modem_sys          : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_modem_subsys       : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_noc_timeout_extref : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_ispa7              : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_g3d_tsensor        : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_modem_tsensor      : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_slimbus            : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_lpmcu              : 1;  /* bit[8]    : LPM3��ϵͳʱ��ʹ�ܿ��ƣ�
                                                                     0��д0��Ч����
                                                                     1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_a57_hpm            : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_cci2sysbus_asyn    : 1;  /* bit[10]   : CCI2SYSBUS�첽�ŵ��ſؿ��ơ� */
        unsigned int  gt_clk_ao_hpm             : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_peri_hpm           : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_a53_hpm            : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_cci400             : 1;  /* bit[14]   :  */
        unsigned int  gt_clk_gpu_hpm            : 1;  /* bit[15]   :  */
        unsigned int  gt_clk_isp_snclk          : 3;  /* bit[16-18]:  */
        unsigned int  reserved_0                : 1;  /* bit[19]   : ������ */
        unsigned int  reserved_1                : 1;  /* bit[20]   : ������ */
        unsigned int  reserved_2                : 1;  /* bit[21]   : ������ */
        unsigned int  reserved_3                : 1;  /* bit[22]   : ������ */
        unsigned int  gt_clk_modem_mcpu_tp      : 1;  /* bit[23]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_c   : 1;  /* bit[24]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_d   : 1;  /* bit[25]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_b   : 1;  /* bit[26]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_a   : 1;  /* bit[27]   :  */
        unsigned int  gt_pclk_dsi0              : 1;  /* bit[28]   :  */
        unsigned int  gt_pclk_dsi1              : 1;  /* bit[29]   :  */
        unsigned int  gt_clk_lpmcu_tp           : 1;  /* bit[30]   :  */
        unsigned int  gt_clk_sysbus_tp          : 1;  /* bit[31]   : ����ʱ�ӽ�ֹ���ƣ�
                                                                     0��д0��Ч����
                                                                     1����ֹIPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PERDIS5_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS5_gt_clk_sysbus2hkmem_START        (0)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_sysbus2hkmem_END          (0)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_sys_START           (1)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_sys_END             (1)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_subsys_START        (2)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_subsys_END          (2)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_noc_timeout_extref_START  (3)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_noc_timeout_extref_END    (3)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ispa7_START               (4)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ispa7_END                 (4)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_g3d_tsensor_START         (5)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_g3d_tsensor_END           (5)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_tsensor_START       (6)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_tsensor_END         (6)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_slimbus_START             (7)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_slimbus_END               (7)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_lpmcu_START               (8)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_lpmcu_END                 (8)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_a57_hpm_START             (9)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_a57_hpm_END               (9)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_cci2sysbus_asyn_START     (10)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_cci2sysbus_asyn_END       (10)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ao_hpm_START              (11)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ao_hpm_END                (11)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_peri_hpm_START            (12)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_peri_hpm_END              (12)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_a53_hpm_START             (13)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_a53_hpm_END               (13)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_cci400_START              (14)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_cci400_END                (14)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_gpu_hpm_START             (15)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_gpu_hpm_END               (15)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_isp_snclk_START           (16)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_isp_snclk_END             (18)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_mcpu_tp_START       (23)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_modem_mcpu_tp_END         (23)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_c_START    (24)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_c_END      (24)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_d_START    (25)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_d_END      (25)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_b_START    (26)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_b_END      (26)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_a_START    (27)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_ddrphy_apb_dfi_a_END      (27)
#define SOC_CRGPERIPH_PERDIS5_gt_pclk_dsi0_START               (28)
#define SOC_CRGPERIPH_PERDIS5_gt_pclk_dsi0_END                 (28)
#define SOC_CRGPERIPH_PERDIS5_gt_pclk_dsi1_START               (29)
#define SOC_CRGPERIPH_PERDIS5_gt_pclk_dsi1_END                 (29)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_lpmcu_tp_START            (30)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_lpmcu_tp_END              (30)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_sysbus_tp_START           (31)
#define SOC_CRGPERIPH_PERDIS5_gt_clk_sysbus_tp_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERCLKEN5_UNION
 �ṹ˵��  : PERCLKEN5 �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0xFF78BB6B�����:32
 �Ĵ���˵��: ����ʱ��ʹ��״̬�Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_sysbus2hkmem       : 1;  /* bit[0]    : ����ʱ��ʹ��״̬��
                                                                     0��IPʱ��ʹ�ܳ���״̬��
                                                                     1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_modem_sys          : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_modem_subsys       : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_noc_timeout_extref : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_ispa7              : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_g3d_tsensor        : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_modem_tsensor      : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_slimbus            : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_lpmcu              : 1;  /* bit[8]    :  */
        unsigned int  gt_clk_a57_hpm            : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_cci2sysbus_asyn    : 1;  /* bit[10]   : CCI2SYSBUS�첽�ŵ��ſؿ��ơ� */
        unsigned int  gt_clk_ao_hpm             : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_peri_hpm           : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_a53_hpm            : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_cci400             : 1;  /* bit[14]   :  */
        unsigned int  gt_clk_gpu_hpm            : 1;  /* bit[15]   :  */
        unsigned int  gt_clk_isp_snclk          : 3;  /* bit[16-18]:  */
        unsigned int  reserved_0                : 1;  /* bit[19]   : ������ */
        unsigned int  reserved_1                : 1;  /* bit[20]   : ������ */
        unsigned int  reserved_2                : 1;  /* bit[21]   : ������ */
        unsigned int  reserved_3                : 1;  /* bit[22]   : ������ */
        unsigned int  gt_clk_modem_mcpu_tp      : 1;  /* bit[23]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_c   : 1;  /* bit[24]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_d   : 1;  /* bit[25]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_b   : 1;  /* bit[26]   :  */
        unsigned int  gt_clk_ddrphy_apb_dfi_a   : 1;  /* bit[27]   :  */
        unsigned int  gt_pclk_dsi0              : 1;  /* bit[28]   :  */
        unsigned int  gt_pclk_dsi1              : 1;  /* bit[29]   :  */
        unsigned int  gt_clk_lpmcu_tp           : 1;  /* bit[30]   :  */
        unsigned int  gt_clk_sysbus_tp          : 1;  /* bit[31]   : ����ʱ��ʹ��״̬��SYSBUS����ʱ�ӣ���
                                                                     0��IPʱ��ʹ�ܳ���״̬��
                                                                     1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERCLKEN5_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_sysbus2hkmem_START        (0)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_sysbus2hkmem_END          (0)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_sys_START           (1)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_sys_END             (1)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_subsys_START        (2)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_subsys_END          (2)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_noc_timeout_extref_START  (3)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_noc_timeout_extref_END    (3)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ispa7_START               (4)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ispa7_END                 (4)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_g3d_tsensor_START         (5)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_g3d_tsensor_END           (5)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_tsensor_START       (6)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_tsensor_END         (6)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_slimbus_START             (7)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_slimbus_END               (7)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_lpmcu_START               (8)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_lpmcu_END                 (8)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_a57_hpm_START             (9)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_a57_hpm_END               (9)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_cci2sysbus_asyn_START     (10)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_cci2sysbus_asyn_END       (10)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ao_hpm_START              (11)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ao_hpm_END                (11)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_peri_hpm_START            (12)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_peri_hpm_END              (12)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_a53_hpm_START             (13)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_a53_hpm_END               (13)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_cci400_START              (14)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_cci400_END                (14)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_gpu_hpm_START             (15)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_gpu_hpm_END               (15)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_isp_snclk_START           (16)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_isp_snclk_END             (18)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_mcpu_tp_START       (23)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_modem_mcpu_tp_END         (23)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_c_START    (24)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_c_END      (24)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_d_START    (25)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_d_END      (25)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_b_START    (26)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_b_END      (26)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_a_START    (27)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_ddrphy_apb_dfi_a_END      (27)
#define SOC_CRGPERIPH_PERCLKEN5_gt_pclk_dsi0_START               (28)
#define SOC_CRGPERIPH_PERCLKEN5_gt_pclk_dsi0_END                 (28)
#define SOC_CRGPERIPH_PERCLKEN5_gt_pclk_dsi1_START               (29)
#define SOC_CRGPERIPH_PERCLKEN5_gt_pclk_dsi1_END                 (29)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_lpmcu_tp_START            (30)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_lpmcu_tp_END              (30)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_sysbus_tp_START           (31)
#define SOC_CRGPERIPH_PERCLKEN5_gt_clk_sysbus_tp_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERSTAT5_UNION
 �ṹ˵��  : PERSTAT5 �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x3FF8BB6B�����:32
 �Ĵ���˵��: ����ʱ������״̬�Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_sysbus2hkmem       : 1;  /* bit[0]    : ����ʱ������״̬��modem hkmemʱ�ӣ���
                                                                     0��IPʱ�ӽ�ֹ״̬��
                                                                     1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_modem_sys          : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_modem_subsys       : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_noc_timeout_extref : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_ispa7              : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_g3d_tsensor        : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_modem_tsensor      : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_slimbus            : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_lpmcu              : 1;  /* bit[8]    :  */
        unsigned int  gt_clk_a57_hpm            : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_cci2sysbus_asyn    : 1;  /* bit[10]   : CCI2SYSBUS�첽�ŵ�ʱ������״̬�� */
        unsigned int  gt_clk_ao_hpm             : 1;  /* bit[11]   : ͬ�� */
        unsigned int  gt_clk_peri_hpm           : 1;  /* bit[12]   : ͬ�� */
        unsigned int  gt_clk_a53_hpm            : 1;  /* bit[13]   : ͬ�� */
        unsigned int  gt_clk_cci400             : 1;  /* bit[14]   : ͬ�� */
        unsigned int  gt_clk_gpu_hpm            : 1;  /* bit[15]   : ͬ�� */
        unsigned int  gt_clk_isp_snclk          : 3;  /* bit[16-18]: clk_isp_snclk_0/1/2 ʱ������״̬�� */
        unsigned int  reserved_0                : 1;  /* bit[19]   : ������ */
        unsigned int  reserved_1                : 1;  /* bit[20]   : ������ */
        unsigned int  reserved_2                : 1;  /* bit[21]   : ������ */
        unsigned int  reserved_3                : 1;  /* bit[22]   : ������ */
        unsigned int  reserved_4                : 1;  /* bit[23]   : ������ */
        unsigned int  gt_clk_ddrphy_apb_dfi_c   : 1;  /* bit[24]   : ͬ�� */
        unsigned int  gt_clk_ddrphy_apb_dfi_d   : 1;  /* bit[25]   : ͬ�� */
        unsigned int  gt_clk_ddrphy_apb_dfi_b   : 1;  /* bit[26]   : ͬ�� */
        unsigned int  gt_clk_ddrphy_apb_dfi_a   : 1;  /* bit[27]   : ͬ�� */
        unsigned int  gt_pclk_dsi0              : 1;  /* bit[28]   : ͬ�� */
        unsigned int  gt_pclk_dsi1              : 1;  /* bit[29]   : ͬ�� */
        unsigned int  gt_clk_ace0_mst_g3d       : 1;  /* bit[30]   : ͬ�� */
        unsigned int  gt_clk_ace1_mst_g3d       : 1;  /* bit[31]   : ����ʱ������״̬��G3D ACE1ʱ�ӣ���
                                                                     0��IPʱ�ӽ�ֹ״̬��
                                                                     1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERSTAT5_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_sysbus2hkmem_START        (0)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_sysbus2hkmem_END          (0)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_sys_START           (1)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_sys_END             (1)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_subsys_START        (2)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_subsys_END          (2)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_noc_timeout_extref_START  (3)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_noc_timeout_extref_END    (3)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ispa7_START               (4)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ispa7_END                 (4)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_g3d_tsensor_START         (5)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_g3d_tsensor_END           (5)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_tsensor_START       (6)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_modem_tsensor_END         (6)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_slimbus_START             (7)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_slimbus_END               (7)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_lpmcu_START               (8)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_lpmcu_END                 (8)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_a57_hpm_START             (9)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_a57_hpm_END               (9)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_cci2sysbus_asyn_START     (10)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_cci2sysbus_asyn_END       (10)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ao_hpm_START              (11)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ao_hpm_END                (11)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_peri_hpm_START            (12)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_peri_hpm_END              (12)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_a53_hpm_START             (13)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_a53_hpm_END               (13)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_cci400_START              (14)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_cci400_END                (14)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_gpu_hpm_START             (15)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_gpu_hpm_END               (15)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_isp_snclk_START           (16)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_isp_snclk_END             (18)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_c_START    (24)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_c_END      (24)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_d_START    (25)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_d_END      (25)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_b_START    (26)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_b_END      (26)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_a_START    (27)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ddrphy_apb_dfi_a_END      (27)
#define SOC_CRGPERIPH_PERSTAT5_gt_pclk_dsi0_START               (28)
#define SOC_CRGPERIPH_PERSTAT5_gt_pclk_dsi0_END                 (28)
#define SOC_CRGPERIPH_PERSTAT5_gt_pclk_dsi1_START               (29)
#define SOC_CRGPERIPH_PERSTAT5_gt_pclk_dsi1_END                 (29)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ace0_mst_g3d_START        (30)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ace0_mst_g3d_END          (30)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ace1_mst_g3d_START        (31)
#define SOC_CRGPERIPH_PERSTAT5_gt_clk_ace1_mst_g3d_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTEN0_UNION
 �ṹ˵��  : PERRSTEN0 �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λʹ�ܼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_ddrc          : 1;  /* bit[0]    : IP��λʹ�ܣ�
                                                                0��IP��λʹ��״̬���䣻
                                                                1��IP��λʹ�ܡ� */
        unsigned int  ip_rst_sysbus2ddrc   : 1;  /* bit[1]    :  */
        unsigned int  ip_rst_ddr_exmbist   : 1;  /* bit[2]    :  */
        unsigned int  ip_rst_vcodeccfg     : 1;  /* bit[3]    :  */
        unsigned int  ip_rst_vcodecbus     : 1;  /* bit[4]    :  */
        unsigned int  reserved_0           : 1;  /* bit[5]    : ������ */
        unsigned int  ip_rst_vivobus       : 1;  /* bit[6]    :  */
        unsigned int  ip_rst_sysbus        : 1;  /* bit[7]    :  */
        unsigned int  ip_rst_cfgbus        : 1;  /* bit[8]    :  */
        unsigned int  ip_rst_timerperi     : 1;  /* bit[9]    :  */
        unsigned int  reserved_1           : 1;  /* bit[10]   : ������ */
        unsigned int  ip_rst_mmc1pericfg   : 1;  /* bit[11]   :  */
        unsigned int  ip_rst_mmc0pericfg   : 1;  /* bit[12]   :  */
        unsigned int  reserved_2           : 1;  /* bit[13]   :  */
        unsigned int  reserved_3           : 1;  /* bit[14]   :  */
        unsigned int  reserved_4           : 1;  /* bit[15]   :  */
        unsigned int  reserved_5           : 1;  /* bit[16]   : ������ */
        unsigned int  reserved_6           : 1;  /* bit[17]   : ������ */
        unsigned int  ip_rst_perf_stat     : 1;  /* bit[18]   :  */
        unsigned int  ip_rst_dbgsechsicbus : 1;  /* bit[19]   :  */
        unsigned int  ip_rst_lpm32cfgbus   : 1;  /* bit[20]   :  */
        unsigned int  ip_rst_noc_dmabus    : 1;  /* bit[21]   :  */
        unsigned int  ip_rst_memrep        : 1;  /* bit[22]   :  */
        unsigned int  ip_rst_vdm_gpu       : 1;  /* bit[23]   :  */
        unsigned int  ip_rst_vdm_acg2      : 1;  /* bit[24]   :  */
        unsigned int  reserved_7           : 1;  /* bit[25]   : ������ */
        unsigned int  reserved_8           : 1;  /* bit[26]   :  */
        unsigned int  reserved_9           : 1;  /* bit[27]   : ������ */
        unsigned int  ip_rst_mbus2bus      : 1;  /* bit[28]   :  */
        unsigned int  reserved_10          : 1;  /* bit[29]   :  */
        unsigned int  reserved_11          : 2;  /* bit[30-31]: IP��λʹ�ܣ�
                                                                0��IP��λʹ��״̬���䣻
                                                                1��IP��λʹ�ܡ� */
    } reg;
} SOC_CRGPERIPH_PERRSTEN0_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_ddrc_START           (0)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_ddrc_END             (0)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_sysbus2ddrc_START    (1)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_sysbus2ddrc_END      (1)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_ddr_exmbist_START    (2)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_ddr_exmbist_END      (2)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vcodeccfg_START      (3)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vcodeccfg_END        (3)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vcodecbus_START      (4)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vcodecbus_END        (4)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vivobus_START        (6)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vivobus_END          (6)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_sysbus_START         (7)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_sysbus_END           (7)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_cfgbus_START         (8)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_cfgbus_END           (8)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_timerperi_START      (9)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_timerperi_END        (9)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mmc1pericfg_START    (11)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mmc1pericfg_END      (11)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mmc0pericfg_START    (12)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mmc0pericfg_END      (12)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_perf_stat_START      (18)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_perf_stat_END        (18)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_dbgsechsicbus_START  (19)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_dbgsechsicbus_END    (19)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_lpm32cfgbus_START    (20)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_lpm32cfgbus_END      (20)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_noc_dmabus_START     (21)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_noc_dmabus_END       (21)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_memrep_START         (22)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_memrep_END           (22)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vdm_gpu_START        (23)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vdm_gpu_END          (23)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vdm_acg2_START       (24)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_vdm_acg2_END         (24)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mbus2bus_START       (28)
#define SOC_CRGPERIPH_PERRSTEN0_ip_rst_mbus2bus_END         (28)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTDIS0_UNION
 �ṹ˵��  : PERRSTDIS0 �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λ����Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_ddrc          : 1;  /* bit[0]    : IP��λ���룺
                                                                0��IP��λʹ��״̬���䣻
                                                                1��IP��λ���롣 */
        unsigned int  ip_rst_sysbus2ddrc   : 1;  /* bit[1]    :  */
        unsigned int  ip_rst_ddr_exmbist   : 1;  /* bit[2]    :  */
        unsigned int  ip_rst_vcodeccfg     : 1;  /* bit[3]    :  */
        unsigned int  ip_rst_vcodecbus     : 1;  /* bit[4]    :  */
        unsigned int  reserved_0           : 1;  /* bit[5]    : ������ */
        unsigned int  ip_rst_vivobus       : 1;  /* bit[6]    :  */
        unsigned int  ip_rst_sysbus        : 1;  /* bit[7]    :  */
        unsigned int  ip_rst_cfgbus        : 1;  /* bit[8]    :  */
        unsigned int  ip_rst_timerperi     : 1;  /* bit[9]    :  */
        unsigned int  reserved_1           : 1;  /* bit[10]   : ������ */
        unsigned int  ip_rst_mmc1pericfg   : 1;  /* bit[11]   :  */
        unsigned int  ip_rst_mmc0pericfg   : 1;  /* bit[12]   :  */
        unsigned int  reserved_2           : 1;  /* bit[13]   :  */
        unsigned int  reserved_3           : 1;  /* bit[14]   :  */
        unsigned int  reserved_4           : 1;  /* bit[15]   :  */
        unsigned int  reserved_5           : 1;  /* bit[16]   : ������ */
        unsigned int  reserved_6           : 1;  /* bit[17]   : ������ */
        unsigned int  ip_rst_perf_stat     : 1;  /* bit[18]   :  */
        unsigned int  ip_rst_dbgsechsicbus : 1;  /* bit[19]   :  */
        unsigned int  ip_rst_lpm32cfgbus   : 1;  /* bit[20]   :  */
        unsigned int  ip_rst_noc_dmabus    : 1;  /* bit[21]   :  */
        unsigned int  ip_rst_memrep        : 1;  /* bit[22]   :  */
        unsigned int  ip_rst_vdm_gpu       : 1;  /* bit[23]   :  */
        unsigned int  ip_rst_vdm_acg2      : 1;  /* bit[24]   :  */
        unsigned int  reserved_7           : 1;  /* bit[25]   : ������ */
        unsigned int  reserved_8           : 1;  /* bit[26]   :  */
        unsigned int  reserved_9           : 1;  /* bit[27]   : ������ */
        unsigned int  ip_rst_mbus2bus      : 1;  /* bit[28]   :  */
        unsigned int  reserved_10          : 1;  /* bit[29]   :  */
        unsigned int  reserved_11          : 2;  /* bit[30-31]: IP��λ���룺
                                                                0��IP��λʹ��״̬���䣻
                                                                1��IP��λ���롣 */
    } reg;
} SOC_CRGPERIPH_PERRSTDIS0_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_ddrc_START           (0)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_ddrc_END             (0)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_sysbus2ddrc_START    (1)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_sysbus2ddrc_END      (1)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_ddr_exmbist_START    (2)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_ddr_exmbist_END      (2)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vcodeccfg_START      (3)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vcodeccfg_END        (3)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vcodecbus_START      (4)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vcodecbus_END        (4)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vivobus_START        (6)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vivobus_END          (6)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_sysbus_START         (7)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_sysbus_END           (7)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_cfgbus_START         (8)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_cfgbus_END           (8)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_timerperi_START      (9)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_timerperi_END        (9)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mmc1pericfg_START    (11)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mmc1pericfg_END      (11)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mmc0pericfg_START    (12)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mmc0pericfg_END      (12)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_perf_stat_START      (18)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_perf_stat_END        (18)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_dbgsechsicbus_START  (19)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_dbgsechsicbus_END    (19)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_lpm32cfgbus_START    (20)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_lpm32cfgbus_END      (20)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_noc_dmabus_START     (21)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_noc_dmabus_END       (21)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_memrep_START         (22)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_memrep_END           (22)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vdm_gpu_START        (23)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vdm_gpu_END          (23)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vdm_acg2_START       (24)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_vdm_acg2_END         (24)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mbus2bus_START       (28)
#define SOC_CRGPERIPH_PERRSTDIS0_ip_rst_mbus2bus_END         (28)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTSTAT0_UNION
 �ṹ˵��  : PERRSTSTAT0 �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x11C40058�����:32
 �Ĵ���˵��: ������λ״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_ddrc          : 1;  /* bit[0]    : ������λʹ��״̬��
                                                                0��IP��λʹ�ܳ�����
                                                                1��IP��λʹ�ܣ� */
        unsigned int  ip_rst_sysbus2ddrc   : 1;  /* bit[1]    :  */
        unsigned int  ip_rst_ddr_exmbist   : 1;  /* bit[2]    :  */
        unsigned int  ip_rst_vcodeccfg     : 1;  /* bit[3]    : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_vcodecbus     : 1;  /* bit[4]    : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  reserved_0           : 1;  /* bit[5]    : ������ */
        unsigned int  ip_rst_vivobus       : 1;  /* bit[6]    :  */
        unsigned int  ip_rst_sysbus        : 1;  /* bit[7]    :  */
        unsigned int  ip_rst_cfgbus        : 1;  /* bit[8]    :  */
        unsigned int  ip_rst_timerperi     : 1;  /* bit[9]    :  */
        unsigned int  reserved_1           : 1;  /* bit[10]   : ������ */
        unsigned int  ip_rst_mmc1pericfg   : 1;  /* bit[11]   :  */
        unsigned int  ip_rst_mmc0pericfg   : 1;  /* bit[12]   :  */
        unsigned int  reserved_2           : 1;  /* bit[13]   : ������ */
        unsigned int  reserved_3           : 1;  /* bit[14]   : ������ */
        unsigned int  reserved_4           : 1;  /* bit[15]   : ������ */
        unsigned int  reserved_5           : 1;  /* bit[16]   : ������ */
        unsigned int  reserved_6           : 1;  /* bit[17]   : ������ */
        unsigned int  ip_rst_perf_stat     : 1;  /* bit[18]   : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_dbgsechsicbus : 1;  /* bit[19]   :  */
        unsigned int  ip_rst_lpm32cfgbus   : 1;  /* bit[20]   :  */
        unsigned int  ip_rst_noc_dmabus    : 1;  /* bit[21]   :  */
        unsigned int  ip_rst_memrep        : 1;  /* bit[22]   : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_vdm_gpu       : 1;  /* bit[23]   : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_vdm_acg2      : 1;  /* bit[24]   : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  reserved_7           : 1;  /* bit[25]   : ������ */
        unsigned int  reserved_8           : 1;  /* bit[26]   : ������ */
        unsigned int  reserved_9           : 1;  /* bit[27]   : ������ */
        unsigned int  ip_rst_mbus2bus      : 1;  /* bit[28]   : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  reserved_10          : 1;  /* bit[29]   : ������ */
        unsigned int  reserved_11          : 2;  /* bit[30-31]: IP��λʹ��״̬��
                                                                0��IP���ڸ�λ����״̬��
                                                                1��IP������λʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT0_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_ddrc_START           (0)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_ddrc_END             (0)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_sysbus2ddrc_START    (1)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_sysbus2ddrc_END      (1)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_ddr_exmbist_START    (2)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_ddr_exmbist_END      (2)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vcodeccfg_START      (3)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vcodeccfg_END        (3)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vcodecbus_START      (4)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vcodecbus_END        (4)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vivobus_START        (6)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vivobus_END          (6)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_sysbus_START         (7)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_sysbus_END           (7)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_cfgbus_START         (8)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_cfgbus_END           (8)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_timerperi_START      (9)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_timerperi_END        (9)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mmc1pericfg_START    (11)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mmc1pericfg_END      (11)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mmc0pericfg_START    (12)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mmc0pericfg_END      (12)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_perf_stat_START      (18)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_perf_stat_END        (18)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_dbgsechsicbus_START  (19)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_dbgsechsicbus_END    (19)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_lpm32cfgbus_START    (20)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_lpm32cfgbus_END      (20)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_noc_dmabus_START     (21)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_noc_dmabus_END       (21)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_memrep_START         (22)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_memrep_END           (22)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vdm_gpu_START        (23)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vdm_gpu_END          (23)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vdm_acg2_START       (24)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_vdm_acg2_END         (24)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mbus2bus_START       (28)
#define SOC_CRGPERIPH_PERRSTSTAT0_ip_rst_mbus2bus_END         (28)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTEN1_UNION
 �ṹ˵��  : PERRSTEN1 �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λʹ�ܼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_gpio0    : 1;  /* bit[0] : IP��λʹ�ܣ�
                                                        0��IP��λʹ��״̬���䣻
                                                        1��IP��λʹ�ܡ� */
        unsigned int  ip_rst_gpio1    : 1;  /* bit[1] :  */
        unsigned int  ip_rst_gpio2    : 1;  /* bit[2] :  */
        unsigned int  ip_rst_gpio3    : 1;  /* bit[3] :  */
        unsigned int  ip_rst_gpio4    : 1;  /* bit[4] :  */
        unsigned int  ip_rst_gpio5    : 1;  /* bit[5] :  */
        unsigned int  ip_rst_gpio6    : 1;  /* bit[6] :  */
        unsigned int  ip_rst_gpio7    : 1;  /* bit[7] :  */
        unsigned int  ip_rst_gpio8    : 1;  /* bit[8] :  */
        unsigned int  ip_rst_gpio9    : 1;  /* bit[9] :  */
        unsigned int  ip_rst_gpio10   : 1;  /* bit[10]:  */
        unsigned int  ip_rst_gpio11   : 1;  /* bit[11]:  */
        unsigned int  ip_rst_gpio12   : 1;  /* bit[12]:  */
        unsigned int  ip_rst_gpio13   : 1;  /* bit[13]:  */
        unsigned int  ip_rst_gpio14   : 1;  /* bit[14]:  */
        unsigned int  ip_rst_gpio15   : 1;  /* bit[15]:  */
        unsigned int  ip_rst_gpio16   : 1;  /* bit[16]:  */
        unsigned int  ip_rst_gpio17   : 1;  /* bit[17]:  */
        unsigned int  ip_rst_gpio18   : 1;  /* bit[18]:  */
        unsigned int  ip_rst_gpio19   : 1;  /* bit[19]:  */
        unsigned int  ip_rst_gpio20   : 1;  /* bit[20]:  */
        unsigned int  ip_rst_gpio21   : 1;  /* bit[21]:  */
        unsigned int  ip_rst_timer9   : 1;  /* bit[22]:  */
        unsigned int  ip_rst_timer10  : 1;  /* bit[23]:  */
        unsigned int  ip_rst_timer11  : 1;  /* bit[24]:  */
        unsigned int  ip_rst_timer12  : 1;  /* bit[25]:  */
        unsigned int  ip_rst_socp     : 1;  /* bit[26]:  */
        unsigned int  ip_rst_djtag    : 1;  /* bit[27]:  */
        unsigned int  ip_rst_vdm_maya : 1;  /* bit[28]:  */
        unsigned int  ip_rst_vdm_a53  : 1;  /* bit[29]:  */
        unsigned int  ip_rst_vdm_acg0 : 1;  /* bit[30]:  */
        unsigned int  ip_rst_vdm_acg1 : 1;  /* bit[31]: IP��λʹ�ܣ�vdm_acg1����
                                                        0��IP��λʹ��״̬���䣻
                                                        1��IP��λʹ�ܡ� */
    } reg;
} SOC_CRGPERIPH_PERRSTEN1_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio0_START     (0)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio0_END       (0)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio1_START     (1)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio1_END       (1)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio2_START     (2)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio2_END       (2)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio3_START     (3)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio3_END       (3)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio4_START     (4)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio4_END       (4)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio5_START     (5)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio5_END       (5)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio6_START     (6)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio6_END       (6)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio7_START     (7)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio7_END       (7)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio8_START     (8)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio8_END       (8)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio9_START     (9)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio9_END       (9)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio10_START    (10)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio10_END      (10)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio11_START    (11)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio11_END      (11)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio12_START    (12)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio12_END      (12)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio13_START    (13)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio13_END      (13)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio14_START    (14)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio14_END      (14)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio15_START    (15)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio15_END      (15)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio16_START    (16)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio16_END      (16)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio17_START    (17)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio17_END      (17)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio18_START    (18)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio18_END      (18)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio19_START    (19)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio19_END      (19)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio20_START    (20)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio20_END      (20)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio21_START    (21)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_gpio21_END      (21)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer9_START    (22)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer9_END      (22)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer10_START   (23)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer10_END     (23)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer11_START   (24)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer11_END     (24)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer12_START   (25)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_timer12_END     (25)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_socp_START      (26)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_socp_END        (26)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_djtag_START     (27)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_djtag_END       (27)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_maya_START  (28)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_maya_END    (28)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_a53_START   (29)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_a53_END     (29)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_acg0_START  (30)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_acg0_END    (30)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_acg1_START  (31)
#define SOC_CRGPERIPH_PERRSTEN1_ip_rst_vdm_acg1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTDIS1_UNION
 �ṹ˵��  : PERRSTDIS1 �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λ����Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_gpio0    : 1;  /* bit[0] : IP��λ���룺
                                                        0��IP��λʹ��״̬���䣻
                                                        1��IP��λ���롣 */
        unsigned int  ip_rst_gpio1    : 1;  /* bit[1] :  */
        unsigned int  ip_rst_gpio2    : 1;  /* bit[2] :  */
        unsigned int  ip_rst_gpio3    : 1;  /* bit[3] :  */
        unsigned int  ip_rst_gpio4    : 1;  /* bit[4] :  */
        unsigned int  ip_rst_gpio5    : 1;  /* bit[5] :  */
        unsigned int  ip_rst_gpio6    : 1;  /* bit[6] :  */
        unsigned int  ip_rst_gpio7    : 1;  /* bit[7] :  */
        unsigned int  ip_rst_gpio8    : 1;  /* bit[8] :  */
        unsigned int  ip_rst_gpio9    : 1;  /* bit[9] :  */
        unsigned int  ip_rst_gpio10   : 1;  /* bit[10]:  */
        unsigned int  ip_rst_gpio11   : 1;  /* bit[11]:  */
        unsigned int  ip_rst_gpio12   : 1;  /* bit[12]:  */
        unsigned int  ip_rst_gpio13   : 1;  /* bit[13]:  */
        unsigned int  ip_rst_gpio14   : 1;  /* bit[14]:  */
        unsigned int  ip_rst_gpio15   : 1;  /* bit[15]:  */
        unsigned int  ip_rst_gpio16   : 1;  /* bit[16]:  */
        unsigned int  ip_rst_gpio17   : 1;  /* bit[17]:  */
        unsigned int  ip_rst_gpio18   : 1;  /* bit[18]:  */
        unsigned int  ip_rst_gpio19   : 1;  /* bit[19]:  */
        unsigned int  ip_rst_gpio20   : 1;  /* bit[20]:  */
        unsigned int  ip_rst_gpio21   : 1;  /* bit[21]:  */
        unsigned int  ip_rst_timer9   : 1;  /* bit[22]:  */
        unsigned int  ip_rst_timer10  : 1;  /* bit[23]:  */
        unsigned int  ip_rst_timer11  : 1;  /* bit[24]:  */
        unsigned int  ip_rst_timer12  : 1;  /* bit[25]:  */
        unsigned int  ip_rst_socp     : 1;  /* bit[26]:  */
        unsigned int  ip_rst_djtag    : 1;  /* bit[27]:  */
        unsigned int  ip_rst_vdm_maya : 1;  /* bit[28]:  */
        unsigned int  ip_rst_vdm_a53  : 1;  /* bit[29]:  */
        unsigned int  ip_rst_vdm_acg0 : 1;  /* bit[30]:  */
        unsigned int  ip_rst_vdm_acg1 : 1;  /* bit[31]: IP��λ���루vdm_acg1����
                                                        0��IP��λʹ��״̬���䣻
                                                        1��IP��λ���롣 */
    } reg;
} SOC_CRGPERIPH_PERRSTDIS1_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio0_START     (0)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio0_END       (0)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio1_START     (1)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio1_END       (1)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio2_START     (2)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio2_END       (2)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio3_START     (3)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio3_END       (3)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio4_START     (4)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio4_END       (4)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio5_START     (5)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio5_END       (5)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio6_START     (6)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio6_END       (6)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio7_START     (7)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio7_END       (7)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio8_START     (8)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio8_END       (8)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio9_START     (9)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio9_END       (9)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio10_START    (10)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio10_END      (10)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio11_START    (11)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio11_END      (11)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio12_START    (12)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio12_END      (12)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio13_START    (13)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio13_END      (13)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio14_START    (14)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio14_END      (14)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio15_START    (15)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio15_END      (15)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio16_START    (16)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio16_END      (16)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio17_START    (17)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio17_END      (17)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio18_START    (18)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio18_END      (18)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio19_START    (19)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio19_END      (19)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio20_START    (20)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio20_END      (20)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio21_START    (21)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_gpio21_END      (21)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer9_START    (22)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer9_END      (22)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer10_START   (23)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer10_END     (23)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer11_START   (24)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer11_END     (24)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer12_START   (25)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_timer12_END     (25)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_socp_START      (26)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_socp_END        (26)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_djtag_START     (27)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_djtag_END       (27)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_maya_START  (28)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_maya_END    (28)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_a53_START   (29)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_a53_END     (29)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_acg0_START  (30)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_acg0_END    (30)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_acg1_START  (31)
#define SOC_CRGPERIPH_PERRSTDIS1_ip_rst_vdm_acg1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTSTAT1_UNION
 �ṹ˵��  : PERRSTSTAT1 �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0xF0000000�����:32
 �Ĵ���˵��: ������λ״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_gpio0    : 1;  /* bit[0] : ������λʹ��״̬��
                                                        0��IP��λʹ�ܳ�����
                                                        1��IP��λʹ�ܣ� */
        unsigned int  ip_rst_gpio1    : 1;  /* bit[1] :  */
        unsigned int  ip_rst_gpio2    : 1;  /* bit[2] :  */
        unsigned int  ip_rst_gpio3    : 1;  /* bit[3] :  */
        unsigned int  ip_rst_gpio4    : 1;  /* bit[4] :  */
        unsigned int  ip_rst_gpio5    : 1;  /* bit[5] :  */
        unsigned int  ip_rst_gpio6    : 1;  /* bit[6] :  */
        unsigned int  ip_rst_gpio7    : 1;  /* bit[7] :  */
        unsigned int  ip_rst_gpio8    : 1;  /* bit[8] :  */
        unsigned int  ip_rst_gpio9    : 1;  /* bit[9] :  */
        unsigned int  ip_rst_gpio10   : 1;  /* bit[10]:  */
        unsigned int  ip_rst_gpio11   : 1;  /* bit[11]:  */
        unsigned int  ip_rst_gpio12   : 1;  /* bit[12]:  */
        unsigned int  ip_rst_gpio13   : 1;  /* bit[13]:  */
        unsigned int  ip_rst_gpio14   : 1;  /* bit[14]:  */
        unsigned int  ip_rst_gpio15   : 1;  /* bit[15]:  */
        unsigned int  ip_rst_gpio16   : 1;  /* bit[16]:  */
        unsigned int  ip_rst_gpio17   : 1;  /* bit[17]:  */
        unsigned int  ip_rst_gpio18   : 1;  /* bit[18]:  */
        unsigned int  ip_rst_gpio19   : 1;  /* bit[19]:  */
        unsigned int  ip_rst_gpio20   : 1;  /* bit[20]:  */
        unsigned int  ip_rst_gpio21   : 1;  /* bit[21]:  */
        unsigned int  ip_rst_timer9   : 1;  /* bit[22]:  */
        unsigned int  ip_rst_timer10  : 1;  /* bit[23]:  */
        unsigned int  ip_rst_timer11  : 1;  /* bit[24]:  */
        unsigned int  ip_rst_timer12  : 1;  /* bit[25]:  */
        unsigned int  ip_rst_socp     : 1;  /* bit[26]:  */
        unsigned int  ip_rst_djtag    : 1;  /* bit[27]:  */
        unsigned int  ip_rst_vdm_maya : 1;  /* bit[28]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_vdm_a53  : 1;  /* bit[29]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_vdm_acg0 : 1;  /* bit[30]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_vdm_acg1 : 1;  /* bit[31]: IP��λʹ��״̬��vdm_acg1����
                                                        0��IP���ڸ�λ����״̬��
                                                        1��IP������λʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT1_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio0_START     (0)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio0_END       (0)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio1_START     (1)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio1_END       (1)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio2_START     (2)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio2_END       (2)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio3_START     (3)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio3_END       (3)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio4_START     (4)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio4_END       (4)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio5_START     (5)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio5_END       (5)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio6_START     (6)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio6_END       (6)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio7_START     (7)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio7_END       (7)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio8_START     (8)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio8_END       (8)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio9_START     (9)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio9_END       (9)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio10_START    (10)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio10_END      (10)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio11_START    (11)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio11_END      (11)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio12_START    (12)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio12_END      (12)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio13_START    (13)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio13_END      (13)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio14_START    (14)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio14_END      (14)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio15_START    (15)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio15_END      (15)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio16_START    (16)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio16_END      (16)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio17_START    (17)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio17_END      (17)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio18_START    (18)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio18_END      (18)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio19_START    (19)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio19_END      (19)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio20_START    (20)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio20_END      (20)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio21_START    (21)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_gpio21_END      (21)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer9_START    (22)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer9_END      (22)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer10_START   (23)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer10_END     (23)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer11_START   (24)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer11_END     (24)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer12_START   (25)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_timer12_END     (25)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_socp_START      (26)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_socp_END        (26)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_djtag_START     (27)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_djtag_END       (27)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_maya_START  (28)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_maya_END    (28)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_a53_START   (29)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_a53_END     (29)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_acg0_START  (30)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_acg0_END    (30)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_acg1_START  (31)
#define SOC_CRGPERIPH_PERRSTSTAT1_ip_rst_vdm_acg1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTEN2_UNION
 �ṹ˵��  : PERRSTEN2 �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λʹ�ܼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_pwm      : 1;  /* bit[0] : IP��λʹ�ܣ�
                                                        0��IP��λʹ��״̬���䣻
                                                        1��IP��λʹ�ܡ� */
        unsigned int  reserved_0      : 1;  /* bit[1] : ������ */
        unsigned int  ip_rst_ipc0     : 1;  /* bit[2] :  */
        unsigned int  ip_rst_ipc1     : 1;  /* bit[3] :  */
        unsigned int  reserved_1      : 1;  /* bit[4] : ������ */
        unsigned int  reserved_2      : 1;  /* bit[5] : ������ */
        unsigned int  reserved_3      : 1;  /* bit[6] : ������ */
        unsigned int  ip_rst_i2c3     : 1;  /* bit[7] :  */
        unsigned int  reserved_4      : 1;  /* bit[8] : ������ */
        unsigned int  ip_rst_spi1     : 1;  /* bit[9] :  */
        unsigned int  ip_rst_uart0    : 1;  /* bit[10]:  */
        unsigned int  ip_rst_uart1    : 1;  /* bit[11]:  */
        unsigned int  ip_rst_uart2    : 1;  /* bit[12]:  */
        unsigned int  reserved_5      : 1;  /* bit[13]: ������ */
        unsigned int  ip_rst_uart4    : 1;  /* bit[14]:  */
        unsigned int  ip_rst_uart5    : 1;  /* bit[15]:  */
        unsigned int  ip_rst_tzpc     : 1;  /* bit[16]:  */
        unsigned int  reserved_6      : 1;  /* bit[17]:  */
        unsigned int  reserved_7      : 1;  /* bit[18]:  */
        unsigned int  reserved_8      : 1;  /* bit[19]: ������ */
        unsigned int  ip_prst_ipc_mdm : 1;  /* bit[20]:  */
        unsigned int  ip_rst_adb_a53  : 1;  /* bit[21]:  */
        unsigned int  ip_rst_adb_a57  : 1;  /* bit[22]:  */
        unsigned int  ip_rst_gic      : 1;  /* bit[23]:  */
        unsigned int  ip_rst_hkadcssi : 1;  /* bit[24]:  */
        unsigned int  ip_rst_ioc      : 1;  /* bit[25]:  */
        unsigned int  ip_rst_codecssi : 1;  /* bit[26]:  */
        unsigned int  ip_rst_i2c4     : 1;  /* bit[27]:  */
        unsigned int  reserved_9      : 1;  /* bit[28]: ������ */
        unsigned int  reserved_10     : 1;  /* bit[29]: ������ */
        unsigned int  reserved_11     : 1;  /* bit[30]: ������ */
        unsigned int  ip_rst_pctrl    : 1;  /* bit[31]: IP��λʹ�ܣ�pctrl����
                                                        0��IP��λʹ��״̬���䣻
                                                        1��IP��λʹ�ܡ� */
    } reg;
} SOC_CRGPERIPH_PERRSTEN2_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_pwm_START       (0)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_pwm_END         (0)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ipc0_START      (2)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ipc0_END        (2)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ipc1_START      (3)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ipc1_END        (3)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_i2c3_START      (7)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_i2c3_END        (7)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_spi1_START      (9)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_spi1_END        (9)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart0_START     (10)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart0_END       (10)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart1_START     (11)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart1_END       (11)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart2_START     (12)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart2_END       (12)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart4_START     (14)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart4_END       (14)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart5_START     (15)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_uart5_END       (15)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_tzpc_START      (16)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_tzpc_END        (16)
#define SOC_CRGPERIPH_PERRSTEN2_ip_prst_ipc_mdm_START  (20)
#define SOC_CRGPERIPH_PERRSTEN2_ip_prst_ipc_mdm_END    (20)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_adb_a53_START   (21)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_adb_a53_END     (21)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_adb_a57_START   (22)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_adb_a57_END     (22)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_gic_START       (23)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_gic_END         (23)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_hkadcssi_START  (24)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_hkadcssi_END    (24)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ioc_START       (25)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_ioc_END         (25)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_codecssi_START  (26)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_codecssi_END    (26)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_i2c4_START      (27)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_i2c4_END        (27)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_pctrl_START     (31)
#define SOC_CRGPERIPH_PERRSTEN2_ip_rst_pctrl_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTDIS2_UNION
 �ṹ˵��  : PERRSTDIS2 �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λ����Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_pwm      : 1;  /* bit[0] : IP��λ���룺
                                                        0��IP��λʹ��״̬���䣻
                                                        1��IP��λ���롣 */
        unsigned int  reserved_0      : 1;  /* bit[1] : ������ */
        unsigned int  ip_rst_ipc0     : 1;  /* bit[2] :  */
        unsigned int  ip_rst_ipc1     : 1;  /* bit[3] :  */
        unsigned int  reserved_1      : 1;  /* bit[4] : ������ */
        unsigned int  reserved_2      : 1;  /* bit[5] : ������ */
        unsigned int  reserved_3      : 1;  /* bit[6] : ������ */
        unsigned int  ip_rst_i2c3     : 1;  /* bit[7] :  */
        unsigned int  reserved_4      : 1;  /* bit[8] : ������ */
        unsigned int  ip_rst_spi1     : 1;  /* bit[9] :  */
        unsigned int  ip_rst_uart0    : 1;  /* bit[10]:  */
        unsigned int  ip_rst_uart1    : 1;  /* bit[11]:  */
        unsigned int  ip_rst_uart2    : 1;  /* bit[12]:  */
        unsigned int  reserved_5      : 1;  /* bit[13]: ������ */
        unsigned int  ip_rst_uart4    : 1;  /* bit[14]:  */
        unsigned int  ip_rst_uart5    : 1;  /* bit[15]:  */
        unsigned int  ip_rst_tzpc     : 1;  /* bit[16]:  */
        unsigned int  reserved_6      : 1;  /* bit[17]:  */
        unsigned int  reserved_7      : 1;  /* bit[18]:  */
        unsigned int  reserved_8      : 1;  /* bit[19]: ������ */
        unsigned int  ip_prst_ipc_mdm : 1;  /* bit[20]:  */
        unsigned int  ip_rst_adb_a53  : 1;  /* bit[21]:  */
        unsigned int  ip_rst_adb_a57  : 1;  /* bit[22]:  */
        unsigned int  ip_rst_gic      : 1;  /* bit[23]:  */
        unsigned int  ip_rst_hkadcssi : 1;  /* bit[24]:  */
        unsigned int  ip_rst_ioc      : 1;  /* bit[25]:  */
        unsigned int  ip_rst_codecssi : 1;  /* bit[26]:  */
        unsigned int  ip_rst_i2c4     : 1;  /* bit[27]:  */
        unsigned int  reserved_9      : 1;  /* bit[28]: ������ */
        unsigned int  reserved_10     : 1;  /* bit[29]: ������ */
        unsigned int  reserved_11     : 1;  /* bit[30]: ������ */
        unsigned int  ip_rst_pctrl    : 1;  /* bit[31]: IP��λ���루pctrl����
                                                        0��IP��λʹ��״̬���䣻
                                                        1��IP��λ���롣 */
    } reg;
} SOC_CRGPERIPH_PERRSTDIS2_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_pwm_START       (0)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_pwm_END         (0)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ipc0_START      (2)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ipc0_END        (2)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ipc1_START      (3)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ipc1_END        (3)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_i2c3_START      (7)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_i2c3_END        (7)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_spi1_START      (9)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_spi1_END        (9)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart0_START     (10)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart0_END       (10)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart1_START     (11)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart1_END       (11)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart2_START     (12)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart2_END       (12)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart4_START     (14)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart4_END       (14)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart5_START     (15)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_uart5_END       (15)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_tzpc_START      (16)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_tzpc_END        (16)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_prst_ipc_mdm_START  (20)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_prst_ipc_mdm_END    (20)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_adb_a53_START   (21)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_adb_a53_END     (21)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_adb_a57_START   (22)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_adb_a57_END     (22)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_gic_START       (23)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_gic_END         (23)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_hkadcssi_START  (24)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_hkadcssi_END    (24)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ioc_START       (25)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_ioc_END         (25)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_codecssi_START  (26)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_codecssi_END    (26)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_i2c4_START      (27)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_i2c4_END        (27)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_pctrl_START     (31)
#define SOC_CRGPERIPH_PERRSTDIS2_ip_rst_pctrl_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTSTAT2_UNION
 �ṹ˵��  : PERRSTSTAT2 �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0x00600000�����:32
 �Ĵ���˵��: ������λ״̬�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_pwm      : 1;  /* bit[0] : IP��λʹ��״̬��
                                                        0��IP���ڸ�λ����״̬��
                                                        1��IP������λʹ��״̬�� */
        unsigned int  reserved_0      : 1;  /* bit[1] : ������ */
        unsigned int  ip_rst_ipc0     : 1;  /* bit[2] :  */
        unsigned int  ip_rst_ipc1     : 1;  /* bit[3] :  */
        unsigned int  reserved_1      : 1;  /* bit[4] : ������ */
        unsigned int  reserved_2      : 1;  /* bit[5] : ������ */
        unsigned int  reserved_3      : 1;  /* bit[6] : ������ */
        unsigned int  ip_rst_i2c3     : 1;  /* bit[7] :  */
        unsigned int  reserved_4      : 1;  /* bit[8] : ������ */
        unsigned int  ip_rst_spi1     : 1;  /* bit[9] :  */
        unsigned int  ip_rst_uart0    : 1;  /* bit[10]:  */
        unsigned int  ip_rst_uart1    : 1;  /* bit[11]:  */
        unsigned int  ip_rst_uart2    : 1;  /* bit[12]:  */
        unsigned int  reserved_5      : 1;  /* bit[13]: ������ */
        unsigned int  ip_rst_uart4    : 1;  /* bit[14]:  */
        unsigned int  ip_rst_uart5    : 1;  /* bit[15]:  */
        unsigned int  ip_rst_tzpc     : 1;  /* bit[16]:  */
        unsigned int  reserved_6      : 1;  /* bit[17]:  */
        unsigned int  reserved_7      : 1;  /* bit[18]:  */
        unsigned int  reserved_8      : 1;  /* bit[19]: ������ */
        unsigned int  ip_prst_ipc_mdm : 1;  /* bit[20]:  */
        unsigned int  ip_rst_adb_a53  : 1;  /* bit[21]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_adb_a57  : 1;  /* bit[22]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_gic      : 1;  /* bit[23]:  */
        unsigned int  ip_rst_hkadcssi : 1;  /* bit[24]:  */
        unsigned int  ip_rst_ioc      : 1;  /* bit[25]:  */
        unsigned int  ip_rst_codecssi : 1;  /* bit[26]:  */
        unsigned int  ip_rst_i2c4     : 1;  /* bit[27]:  */
        unsigned int  reserved_9      : 1;  /* bit[28]: ������ */
        unsigned int  reserved_10     : 1;  /* bit[29]: ������ */
        unsigned int  reserved_11     : 1;  /* bit[30]: ������ */
        unsigned int  ip_rst_pctrl    : 1;  /* bit[31]: IP��λʹ��״̬��pctrl����
                                                        0��IP���ڸ�λ����״̬��
                                                        1��IP������λʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT2_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_pwm_START       (0)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_pwm_END         (0)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ipc0_START      (2)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ipc0_END        (2)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ipc1_START      (3)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ipc1_END        (3)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_i2c3_START      (7)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_i2c3_END        (7)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_spi1_START      (9)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_spi1_END        (9)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart0_START     (10)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart0_END       (10)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart1_START     (11)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart1_END       (11)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart2_START     (12)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart2_END       (12)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart4_START     (14)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart4_END       (14)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart5_START     (15)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_uart5_END       (15)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_tzpc_START      (16)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_tzpc_END        (16)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_prst_ipc_mdm_START  (20)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_prst_ipc_mdm_END    (20)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_adb_a53_START   (21)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_adb_a53_END     (21)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_adb_a57_START   (22)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_adb_a57_END     (22)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_gic_START       (23)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_gic_END         (23)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_hkadcssi_START  (24)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_hkadcssi_END    (24)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ioc_START       (25)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_ioc_END         (25)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_codecssi_START  (26)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_codecssi_END    (26)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_i2c4_START      (27)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_i2c4_END        (27)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_pctrl_START     (31)
#define SOC_CRGPERIPH_PERRSTSTAT2_ip_rst_pctrl_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTEN3_UNION
 �ṹ˵��  : PERRSTEN3 �Ĵ����ṹ���塣��ַƫ����:0x084����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λʹ�ܼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_dmac      : 1;  /* bit[0] : IP��λʹ�ܣ�
                                                         0��IP��λʹ��״̬���䣻
                                                         1��IP��λʹ�ܡ� */
        unsigned int  reserved_0       : 1;  /* bit[1] : ������ */
        unsigned int  ip_prst_g3d      : 1;  /* bit[2] :  */
        unsigned int  ip_rst_g3d       : 1;  /* bit[3] :  */
        unsigned int  ip_rst_g3dmt     : 1;  /* bit[4] :  */
        unsigned int  reserved_1       : 1;  /* bit[5] : ������ */
        unsigned int  reserved_2       : 1;  /* bit[6] : ������ */
        unsigned int  reserved_3       : 1;  /* bit[7] : ������ */
        unsigned int  ip_rst_venc      : 1;  /* bit[8] :  */
        unsigned int  ip_rst_vdec      : 1;  /* bit[9] :  */
        unsigned int  ip_rst_dss       : 1;  /* bit[10]:  */
        unsigned int  ip_prst_dss      : 1;  /* bit[11]:  */
        unsigned int  reserved_4       : 1;  /* bit[12]: ������ */
        unsigned int  reserved_5       : 1;  /* bit[13]: ������ */
        unsigned int  reserved_6       : 1;  /* bit[14]: ������ */
        unsigned int  reserved_7       : 1;  /* bit[15]: ������ */
        unsigned int  ip_rst_g3ds_hpm5 : 1;  /* bit[16]:  */
        unsigned int  ip_rst_g3ds_hpm4 : 1;  /* bit[17]:  */
        unsigned int  ip_rst_g3ds_hpm3 : 1;  /* bit[18]:  */
        unsigned int  ip_rst_g3ds_hpm2 : 1;  /* bit[19]:  */
        unsigned int  ip_rst_g3ds_hpm1 : 1;  /* bit[20]:  */
        unsigned int  ip_rst_g3ds_hpm0 : 1;  /* bit[21]:  */
        unsigned int  ip_rst_g3dg_hpm  : 1;  /* bit[22]:  */
        unsigned int  ip_rst_peri_hpm  : 1;  /* bit[23]:  */
        unsigned int  ip_rst_ao_hpm    : 1;  /* bit[24]:  */
        unsigned int  reserved_8       : 1;  /* bit[25]: ������ */
        unsigned int  reserved_9       : 1;  /* bit[26]: ������ */
        unsigned int  reserved_10      : 1;  /* bit[27]: ������ */
        unsigned int  ip_rst_dsi0      : 1;  /* bit[28]:  */
        unsigned int  ip_rst_dsi1      : 1;  /* bit[29]:  */
        unsigned int  reserved_11      : 1;  /* bit[30]: ������ */
        unsigned int  reserved_12      : 1;  /* bit[31]: IP��λʹ�ܣ�
                                                         0��IP��λʹ��״̬���䣻
                                                         1��IP��λʹ�ܡ� */
    } reg;
} SOC_CRGPERIPH_PERRSTEN3_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dmac_START       (0)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dmac_END         (0)
#define SOC_CRGPERIPH_PERRSTEN3_ip_prst_g3d_START       (2)
#define SOC_CRGPERIPH_PERRSTEN3_ip_prst_g3d_END         (2)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3d_START        (3)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3d_END          (3)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3dmt_START      (4)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3dmt_END        (4)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_venc_START       (8)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_venc_END         (8)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_vdec_START       (9)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_vdec_END         (9)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dss_START        (10)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dss_END          (10)
#define SOC_CRGPERIPH_PERRSTEN3_ip_prst_dss_START       (11)
#define SOC_CRGPERIPH_PERRSTEN3_ip_prst_dss_END         (11)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm5_START  (16)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm5_END    (16)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm4_START  (17)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm4_END    (17)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm3_START  (18)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm3_END    (18)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm2_START  (19)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm2_END    (19)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm1_START  (20)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm1_END    (20)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm0_START  (21)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3ds_hpm0_END    (21)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3dg_hpm_START   (22)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_g3dg_hpm_END     (22)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_peri_hpm_START   (23)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_peri_hpm_END     (23)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_ao_hpm_START     (24)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_ao_hpm_END       (24)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dsi0_START       (28)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dsi0_END         (28)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dsi1_START       (29)
#define SOC_CRGPERIPH_PERRSTEN3_ip_rst_dsi1_END         (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTDIS3_UNION
 �ṹ˵��  : PERRSTDIS3 �Ĵ����ṹ���塣��ַƫ����:0x088����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λ����Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_dmac      : 1;  /* bit[0] : IP��λ���룺
                                                         0��IP��λʹ��״̬���䣻
                                                         1��IP��λ���롣 */
        unsigned int  reserved_0       : 1;  /* bit[1] : ������ */
        unsigned int  ip_prst_g3d      : 1;  /* bit[2] :  */
        unsigned int  ip_rst_g3d       : 1;  /* bit[3] :  */
        unsigned int  ip_rst_g3dmt     : 1;  /* bit[4] :  */
        unsigned int  reserved_1       : 1;  /* bit[5] : ������ */
        unsigned int  reserved_2       : 1;  /* bit[6] : ������ */
        unsigned int  reserved_3       : 1;  /* bit[7] : ������ */
        unsigned int  ip_rst_venc      : 1;  /* bit[8] :  */
        unsigned int  ip_rst_vdec      : 1;  /* bit[9] :  */
        unsigned int  ip_rst_dss       : 1;  /* bit[10]:  */
        unsigned int  ip_prst_dss      : 1;  /* bit[11]:  */
        unsigned int  reserved_4       : 1;  /* bit[12]: ������ */
        unsigned int  reserved_5       : 1;  /* bit[13]: ������ */
        unsigned int  reserved_6       : 1;  /* bit[14]: ������ */
        unsigned int  reserved_7       : 1;  /* bit[15]: ������ */
        unsigned int  ip_rst_g3ds_hpm5 : 1;  /* bit[16]:  */
        unsigned int  ip_rst_g3ds_hpm4 : 1;  /* bit[17]:  */
        unsigned int  ip_rst_g3ds_hpm3 : 1;  /* bit[18]:  */
        unsigned int  ip_rst_g3ds_hpm2 : 1;  /* bit[19]:  */
        unsigned int  ip_rst_g3ds_hpm1 : 1;  /* bit[20]:  */
        unsigned int  ip_rst_g3ds_hpm0 : 1;  /* bit[21]:  */
        unsigned int  ip_rst_g3dg_hpm  : 1;  /* bit[22]:  */
        unsigned int  ip_rst_peri_hpm  : 1;  /* bit[23]:  */
        unsigned int  ip_rst_ao_hpm    : 1;  /* bit[24]:  */
        unsigned int  reserved_8       : 1;  /* bit[25]: ������ */
        unsigned int  reserved_9       : 1;  /* bit[26]: ������ */
        unsigned int  reserved_10      : 1;  /* bit[27]: ������ */
        unsigned int  ip_rst_dsi0      : 1;  /* bit[28]:  */
        unsigned int  ip_rst_dsi1      : 1;  /* bit[29]:  */
        unsigned int  reserved_11      : 1;  /* bit[30]: ������ */
        unsigned int  reserved_12      : 1;  /* bit[31]: IP��λ���룺
                                                         0��IP��λʹ��״̬���䣻
                                                         1��IP��λ���롣 */
    } reg;
} SOC_CRGPERIPH_PERRSTDIS3_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dmac_START       (0)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dmac_END         (0)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_prst_g3d_START       (2)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_prst_g3d_END         (2)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3d_START        (3)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3d_END          (3)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3dmt_START      (4)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3dmt_END        (4)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_venc_START       (8)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_venc_END         (8)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_vdec_START       (9)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_vdec_END         (9)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dss_START        (10)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dss_END          (10)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_prst_dss_START       (11)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_prst_dss_END         (11)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm5_START  (16)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm5_END    (16)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm4_START  (17)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm4_END    (17)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm3_START  (18)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm3_END    (18)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm2_START  (19)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm2_END    (19)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm1_START  (20)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm1_END    (20)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm0_START  (21)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3ds_hpm0_END    (21)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3dg_hpm_START   (22)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_g3dg_hpm_END     (22)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_peri_hpm_START   (23)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_peri_hpm_END     (23)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_ao_hpm_START     (24)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_ao_hpm_END       (24)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dsi0_START       (28)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dsi0_END         (28)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dsi1_START       (29)
#define SOC_CRGPERIPH_PERRSTDIS3_ip_rst_dsi1_END         (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTSTAT3_UNION
 �ṹ˵��  : PERRSTSTAT3 �Ĵ����ṹ���塣��ַƫ����:0x008C����ֵ:0x71FF5F1C�����:32
 �Ĵ���˵��: ������λ״̬�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_dmac      : 1;  /* bit[0] : IP��λʹ��״̬��
                                                         0��IP���ڸ�λ����״̬��
                                                         1��IP������λʹ��״̬�� */
        unsigned int  reserved_0       : 1;  /* bit[1] : ������ */
        unsigned int  ip_prst_g3d      : 1;  /* bit[2] : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_g3d       : 1;  /* bit[3] : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_g3dmt     : 1;  /* bit[4] : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  reserved_1       : 1;  /* bit[5] : ������ */
        unsigned int  reserved_2       : 1;  /* bit[6] : ������ */
        unsigned int  reserved_3       : 1;  /* bit[7] : ������ */
        unsigned int  ip_rst_venc      : 1;  /* bit[8] : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_vdec      : 1;  /* bit[9] : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_dss       : 1;  /* bit[10]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_prst_dss      : 1;  /* bit[11]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  reserved_4       : 1;  /* bit[12]: ������ */
        unsigned int  reserved_5       : 1;  /* bit[13]: ������ */
        unsigned int  reserved_6       : 1;  /* bit[14]: ������ */
        unsigned int  reserved_7       : 1;  /* bit[15]: ������ */
        unsigned int  ip_rst_g3ds_hpm5 : 1;  /* bit[16]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_g3ds_hpm4 : 1;  /* bit[17]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_g3ds_hpm3 : 1;  /* bit[18]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_g3ds_hpm2 : 1;  /* bit[19]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_g3ds_hpm1 : 1;  /* bit[20]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_g3ds_hpm0 : 1;  /* bit[21]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_g3dg_hpm  : 1;  /* bit[22]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_peri_hpm  : 1;  /* bit[23]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_ao_hpm    : 1;  /* bit[24]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  reserved_8       : 1;  /* bit[25]: ������ */
        unsigned int  reserved_9       : 1;  /* bit[26]: ������ */
        unsigned int  reserved_10      : 1;  /* bit[27]: ������ */
        unsigned int  ip_rst_dsi0      : 1;  /* bit[28]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_dsi1      : 1;  /* bit[29]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  reserved_11      : 1;  /* bit[30]: ������ */
        unsigned int  reserved_12      : 1;  /* bit[31]: IP��λʹ��״̬��
                                                         0��IP���ڸ�λ����״̬��
                                                         1��IP������λʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT3_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dmac_START       (0)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dmac_END         (0)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_prst_g3d_START       (2)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_prst_g3d_END         (2)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3d_START        (3)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3d_END          (3)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3dmt_START      (4)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3dmt_END        (4)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_venc_START       (8)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_venc_END         (8)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_vdec_START       (9)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_vdec_END         (9)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dss_START        (10)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dss_END          (10)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_prst_dss_START       (11)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_prst_dss_END         (11)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm5_START  (16)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm5_END    (16)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm4_START  (17)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm4_END    (17)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm3_START  (18)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm3_END    (18)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm2_START  (19)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm2_END    (19)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm1_START  (20)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm1_END    (20)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm0_START  (21)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3ds_hpm0_END    (21)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3dg_hpm_START   (22)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_g3dg_hpm_END     (22)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_peri_hpm_START   (23)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_peri_hpm_END     (23)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_ao_hpm_START     (24)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_ao_hpm_END       (24)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dsi0_START       (28)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dsi0_END         (28)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dsi1_START       (29)
#define SOC_CRGPERIPH_PERRSTSTAT3_ip_rst_dsi1_END         (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTEN4_UNION
 �ṹ˵��  : PERRSTEN4 �Ĵ����ṹ���塣��ַƫ����:0x090����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λʹ�ܼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_dbgsechsic_subsys_crg : 1;  /* bit[0] : IP��λʹ�ܣ�
                                                                     0��IP��λʹ��״̬���䣻
                                                                     1��IP��λʹ�ܡ� */
        unsigned int  reserved_0                   : 1;  /* bit[1] : ������ */
        unsigned int  reserved_1                   : 1;  /* bit[2] : ������ */
        unsigned int  ip_rst_usb3otgphy_por        : 1;  /* bit[3] :  */
        unsigned int  reserved_2                   : 1;  /* bit[4] : ������ */
        unsigned int  ip_rst_usb3otg               : 1;  /* bit[5] :  */
        unsigned int  ip_rst_usb3otg_32k           : 1;  /* bit[6] :  */
        unsigned int  ip_rst_usb3otg_ahbif         : 1;  /* bit[7] :  */
        unsigned int  ip_rst_usb3otg_mux           : 1;  /* bit[8] :  */
        unsigned int  reserved_3                   : 1;  /* bit[9] : ������ */
        unsigned int  reserved_4                   : 1;  /* bit[10]: ������ */
        unsigned int  reserved_5                   : 1;  /* bit[11]: ������ */
        unsigned int  reserved_6                   : 1;  /* bit[12]: ������ */
        unsigned int  reserved_7                   : 1;  /* bit[13]: ������ */
        unsigned int  reserved_8                   : 1;  /* bit[14]:  */
        unsigned int  ip_rst_secp                  : 1;  /* bit[15]:  */
        unsigned int  ip_rst_emmc0                 : 1;  /* bit[16]:  */
        unsigned int  ip_rst_emmc1                 : 1;  /* bit[17]:  */
        unsigned int  ip_rst_sd                    : 1;  /* bit[18]:  */
        unsigned int  ip_rst_sdio0                 : 1;  /* bit[19]:  */
        unsigned int  ip_rst_sdio1                 : 1;  /* bit[20]:  */
        unsigned int  ip_rst_cci400                : 1;  /* bit[21]:  */
        unsigned int  ip_rst_emmc0_m               : 1;  /* bit[22]:  */
        unsigned int  ip_rst_emmc1_m               : 1;  /* bit[23]:  */
        unsigned int  ip_rst_sd_m                  : 1;  /* bit[24]:  */
        unsigned int  ip_rst_sdio0_m               : 1;  /* bit[25]:  */
        unsigned int  ip_rst_sdio1_m               : 1;  /* bit[26]:  */
        unsigned int  reserved_9                   : 1;  /* bit[27]: ������ */
        unsigned int  ip_rst_lpmcu                 : 1;  /* bit[28]: ����LPM3��ϵͳ�ĸ�λʹ�ܣ�
                                                                     0����λʹ��״̬���䣻
                                                                     1����λʹ�ܡ�
                                                                     ���������ʹ�ã�һ�����ûᵼ��ϵͳ������ */
        unsigned int  ip_rst_sysbus2hkmem          : 1;  /* bit[29]:  */
        unsigned int  reserved_10                  : 1;  /* bit[30]: ������ */
        unsigned int  reserved_11                  : 1;  /* bit[31]: IP��λʹ�ܣ�
                                                                     0��IP��λʹ��״̬���䣻
                                                                     1��IP��λʹ�ܡ� */
    } reg;
} SOC_CRGPERIPH_PERRSTEN4_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_dbgsechsic_subsys_crg_START  (0)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_dbgsechsic_subsys_crg_END    (0)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otgphy_por_START         (3)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otgphy_por_END           (3)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_START                (5)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_END                  (5)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_32k_START            (6)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_32k_END              (6)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_ahbif_START          (7)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_ahbif_END            (7)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_mux_START            (8)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_usb3otg_mux_END              (8)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_secp_START                   (15)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_secp_END                     (15)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc0_START                  (16)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc0_END                    (16)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc1_START                  (17)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc1_END                    (17)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sd_START                     (18)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sd_END                       (18)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio0_START                  (19)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio0_END                    (19)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio1_START                  (20)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio1_END                    (20)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_cci400_START                 (21)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_cci400_END                   (21)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc0_m_START                (22)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc0_m_END                  (22)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc1_m_START                (23)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_emmc1_m_END                  (23)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sd_m_START                   (24)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sd_m_END                     (24)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio0_m_START                (25)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio0_m_END                  (25)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio1_m_START                (26)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sdio1_m_END                  (26)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_lpmcu_START                  (28)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_lpmcu_END                    (28)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sysbus2hkmem_START           (29)
#define SOC_CRGPERIPH_PERRSTEN4_ip_rst_sysbus2hkmem_END             (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTDIS4_UNION
 �ṹ˵��  : PERRSTDIS4 �Ĵ����ṹ���塣��ַƫ����:0x094����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λ����Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_dbgsechsic_subsys_crg : 1;  /* bit[0] : IP��λ���룺
                                                                     0��IP��λʹ��״̬���䣻
                                                                     1��IP��λ���롣 */
        unsigned int  reserved_0                   : 1;  /* bit[1] : ������ */
        unsigned int  reserved_1                   : 1;  /* bit[2] : ������ */
        unsigned int  ip_rst_usb3otgphy_por        : 1;  /* bit[3] :  */
        unsigned int  reserved_2                   : 1;  /* bit[4] : ������ */
        unsigned int  ip_rst_usb3otg               : 1;  /* bit[5] :  */
        unsigned int  ip_rst_usb3otg_32k           : 1;  /* bit[6] :  */
        unsigned int  ip_rst_usb3otg_ahbif         : 1;  /* bit[7] :  */
        unsigned int  ip_rst_usb3otg_mux           : 1;  /* bit[8] :  */
        unsigned int  reserved_3                   : 1;  /* bit[9] : ������ */
        unsigned int  reserved_4                   : 1;  /* bit[10]: ������ */
        unsigned int  reserved_5                   : 1;  /* bit[11]: ������ */
        unsigned int  reserved_6                   : 1;  /* bit[12]: ������ */
        unsigned int  reserved_7                   : 1;  /* bit[13]: ������ */
        unsigned int  reserved_8                   : 1;  /* bit[14]:  */
        unsigned int  ip_rst_secp                  : 1;  /* bit[15]:  */
        unsigned int  ip_rst_emmc0                 : 1;  /* bit[16]: ������ */
        unsigned int  ip_rst_emmc1                 : 1;  /* bit[17]:  */
        unsigned int  ip_rst_sd                    : 1;  /* bit[18]:  */
        unsigned int  ip_rst_sdio0                 : 1;  /* bit[19]:  */
        unsigned int  ip_rst_sdio1                 : 1;  /* bit[20]:  */
        unsigned int  ip_rst_cci400                : 1;  /* bit[21]:  */
        unsigned int  ip_rst_emmc0_m               : 1;  /* bit[22]:  */
        unsigned int  ip_rst_emmc1_m               : 1;  /* bit[23]:  */
        unsigned int  ip_rst_sd_m                  : 1;  /* bit[24]: ������ */
        unsigned int  ip_rst_sdio0_m               : 1;  /* bit[25]: ������ */
        unsigned int  ip_rst_sdio1_m               : 1;  /* bit[26]: ������ */
        unsigned int  reserved_9                   : 1;  /* bit[27]: ������ */
        unsigned int  ip_rst_lpmcu                 : 1;  /* bit[28]: ����LPM3��ϵͳ�ĸ�λʹ�ܣ�
                                                                     0����λʹ��״̬���䣻
                                                                     1����λ���롣 */
        unsigned int  ip_rst_sysbus2hkmem          : 1;  /* bit[29]:  */
        unsigned int  reserved_10                  : 1;  /* bit[30]: ������ */
        unsigned int  reserved_11                  : 1;  /* bit[31]: IP��λ���룺
                                                                     0��IP��λʹ��״̬���䣻
                                                                     1��IP��λ���롣 */
    } reg;
} SOC_CRGPERIPH_PERRSTDIS4_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_dbgsechsic_subsys_crg_START  (0)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_dbgsechsic_subsys_crg_END    (0)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otgphy_por_START         (3)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otgphy_por_END           (3)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_START                (5)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_END                  (5)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_32k_START            (6)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_32k_END              (6)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_ahbif_START          (7)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_ahbif_END            (7)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_mux_START            (8)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_usb3otg_mux_END              (8)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_secp_START                   (15)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_secp_END                     (15)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc0_START                  (16)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc0_END                    (16)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc1_START                  (17)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc1_END                    (17)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sd_START                     (18)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sd_END                       (18)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio0_START                  (19)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio0_END                    (19)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio1_START                  (20)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio1_END                    (20)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_cci400_START                 (21)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_cci400_END                   (21)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc0_m_START                (22)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc0_m_END                  (22)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc1_m_START                (23)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_emmc1_m_END                  (23)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sd_m_START                   (24)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sd_m_END                     (24)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio0_m_START                (25)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio0_m_END                  (25)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio1_m_START                (26)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sdio1_m_END                  (26)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_lpmcu_START                  (28)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_lpmcu_END                    (28)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sysbus2hkmem_START           (29)
#define SOC_CRGPERIPH_PERRSTDIS4_ip_rst_sysbus2hkmem_END             (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTSTAT4_UNION
 �ṹ˵��  : PERRSTSTAT4 �Ĵ����ṹ���塣��ַƫ����:0x098����ֵ:0x003F41E1�����:32
 �Ĵ���˵��: ������λ״̬�Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_dbgsechsic_subsys_crg : 1;  /* bit[0] : IP��λʹ��״̬��
                                                                     0��IP���ڸ�λ����״̬��
                                                                     1��IP������λʹ��״̬�� */
        unsigned int  reserved_0                   : 1;  /* bit[1] : ������ */
        unsigned int  reserved_1                   : 1;  /* bit[2] : ������ */
        unsigned int  ip_rst_usb3otgphy_por        : 1;  /* bit[3] :  */
        unsigned int  reserved_2                   : 1;  /* bit[4] : ������ */
        unsigned int  ip_rst_usb3otg               : 1;  /* bit[5] : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_usb3otg_32k           : 1;  /* bit[6] : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_usb3otg_ahbif         : 1;  /* bit[7] : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_usb3otg_mux           : 1;  /* bit[8] : �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  reserved_3                   : 1;  /* bit[9] : ������ */
        unsigned int  reserved_4                   : 1;  /* bit[10]: ������ */
        unsigned int  reserved_5                   : 1;  /* bit[11]: ������ */
        unsigned int  reserved_6                   : 1;  /* bit[12]: ������ */
        unsigned int  reserved_7                   : 1;  /* bit[13]: ������ */
        unsigned int  reserved_8                   : 1;  /* bit[14]: ������ */
        unsigned int  ip_rst_secp                  : 1;  /* bit[15]:  */
        unsigned int  ip_rst_emmc0                 : 1;  /* bit[16]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_emmc1                 : 1;  /* bit[17]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_sd                    : 1;  /* bit[18]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_sdio0                 : 1;  /* bit[19]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_sdio1                 : 1;  /* bit[20]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_cci400                : 1;  /* bit[21]: �ϵ�Ĭ�ϴ��ڸ�λ״̬�� */
        unsigned int  ip_rst_emmc0_m               : 1;  /* bit[22]:  */
        unsigned int  ip_rst_emmc1_m               : 1;  /* bit[23]:  */
        unsigned int  ip_rst_sd_m                  : 1;  /* bit[24]:  */
        unsigned int  ip_rst_sdio0_m               : 1;  /* bit[25]:  */
        unsigned int  ip_rst_sdio1_m               : 1;  /* bit[26]:  */
        unsigned int  reserved_9                   : 1;  /* bit[27]:  */
        unsigned int  ip_rst_lpmcu                 : 1;  /* bit[28]: LPM3��ϵͳ�ϵ�Ĭ�ϴ��ڸ�λ����״̬�� */
        unsigned int  ip_rst_sysbus2hkmem          : 1;  /* bit[29]:  */
        unsigned int  reserved_10                  : 1;  /* bit[30]: ������ */
        unsigned int  reserved_11                  : 1;  /* bit[31]: IP��λʹ��״̬��
                                                                     0��IP���ڸ�λ����״̬��
                                                                     1��IP������λʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT4_UNION;
#endif
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_dbgsechsic_subsys_crg_START  (0)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_dbgsechsic_subsys_crg_END    (0)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otgphy_por_START         (3)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otgphy_por_END           (3)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_START                (5)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_END                  (5)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_32k_START            (6)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_32k_END              (6)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_ahbif_START          (7)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_ahbif_END            (7)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_mux_START            (8)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_usb3otg_mux_END              (8)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_secp_START                   (15)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_secp_END                     (15)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc0_START                  (16)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc0_END                    (16)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc1_START                  (17)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc1_END                    (17)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sd_START                     (18)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sd_END                       (18)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio0_START                  (19)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio0_END                    (19)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio1_START                  (20)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio1_END                    (20)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_cci400_START                 (21)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_cci400_END                   (21)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc0_m_START                (22)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc0_m_END                  (22)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc1_m_START                (23)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_emmc1_m_END                  (23)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sd_m_START                   (24)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sd_m_END                     (24)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio0_m_START                (25)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio0_m_END                  (25)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio1_m_START                (26)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sdio1_m_END                  (26)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_lpmcu_START                  (28)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_lpmcu_END                    (28)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sysbus2hkmem_START           (29)
#define SOC_CRGPERIPH_PERRSTSTAT4_ip_rst_sysbus2hkmem_END             (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTEN5_UNION
 �ṹ˵��  : PERRSTEN5 �Ĵ����ṹ���塣��ַƫ����:0x09C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λʹ�ܼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: IP��λʹ�ܣ�
                                                   0��IP��λʹ��״̬���䣻
                                                   1��IP��λʹ�ܡ� */
    } reg;
} SOC_CRGPERIPH_PERRSTEN5_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTDIS5_UNION
 �ṹ˵��  : PERRSTDIS5 �Ĵ����ṹ���塣��ַƫ����:0x0A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λ����Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: IP��λ���룺
                                                   0��IP��λʹ��״̬���䣻
                                                   1��IP��λ���롣 */
    } reg;
} SOC_CRGPERIPH_PERRSTDIS5_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERRSTSTAT5_UNION
 �ṹ˵��  : PERRSTSTAT5 �Ĵ����ṹ���塣��ַƫ����:0x0A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������λ״̬�Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: IP��λʹ��״̬��
                                                   0��IP���ڸ�λ����״̬��
                                                   1��IP������λʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERRSTSTAT5_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV0_UNION
 �ṹ˵��  : CLKDIV0 �Ĵ����ṹ���塣��ַƫ����:0x0A8����ֵ:0x00000CE5�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_sysbus        : 5;  /* bit[0-4]  : SYSBUS����ʱ�ӷ�Ƶ�ȡ�����ѡPPLL0\PPLL1��Ƶ�����Ƽ�sel_sysbus��
                                                                5'h0:1��
                                                                5'h1:2��
                                                                5'h2:3��
                                                                ��
                                                                5'h1E:31��
                                                                5'h1F:32�� */
        unsigned int  sc_div_lpmcu         : 5;  /* bit[5-9]  : LPMCU����ʱ�ӷ�Ƶ�ȡ�����ѡPPLL0\PPLL1��Ƶ�����Ƽ�sel_lpmcu��
                                                                5'h0:1��
                                                                5'h1:2��
                                                                5'h2:3��
                                                                ��
                                                                5'h1E:31��
                                                                5'h1F:32�� */
        unsigned int  sc_div_ivp32dsp_core : 4;  /* bit[10-13]: IVP32DSP COREʱ�ӷ�Ƶ�ȡ�����ѡPPLL0\PPLL1\PPLL2\PPLL3��Ƶ�����Ƽ�sel_ivp32dsp_core��
                                                                4'h0:1��
                                                                4'h1:2��
                                                                4'h2:3��
                                                                ��
                                                                4'hE:15��
                                                                4'hF:16�� */
        unsigned int  sel_ivp32dsp_core    : 2;  /* bit[14-15]: IVP32DSP COREʱ��Դѡ�񡣣���ѡPPLL0\PPLL1\PPLL2\PPLL3��
                                                                00:PPLL0��
                                                                01:PPLL1��
                                                                10:PPLL2��
                                                                11:PPLL3; */
        unsigned int  clkdivmasken         : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                                ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV0_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV0_sc_div_sysbus_START         (0)
#define SOC_CRGPERIPH_CLKDIV0_sc_div_sysbus_END           (4)
#define SOC_CRGPERIPH_CLKDIV0_sc_div_lpmcu_START          (5)
#define SOC_CRGPERIPH_CLKDIV0_sc_div_lpmcu_END            (9)
#define SOC_CRGPERIPH_CLKDIV0_sc_div_ivp32dsp_core_START  (10)
#define SOC_CRGPERIPH_CLKDIV0_sc_div_ivp32dsp_core_END    (13)
#define SOC_CRGPERIPH_CLKDIV0_sel_ivp32dsp_core_START     (14)
#define SOC_CRGPERIPH_CLKDIV0_sel_ivp32dsp_core_END       (15)
#define SOC_CRGPERIPH_CLKDIV0_clkdivmasken_START          (16)
#define SOC_CRGPERIPH_CLKDIV0_clkdivmasken_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV1_UNION
 �ṹ˵��  : CLKDIV1 �Ĵ����ṹ���塣��ַƫ����:0x0AC����ֵ:0x00002000�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sel_sysbus            : 1;  /* bit[0]    : SYSBUS PLLԴѡ��
                                                                 0��PPLL1��
                                                                 1��PPLL0�� */
        unsigned int  sel_lpmcu             : 1;  /* bit[1]    : LPMCU PLLԴѡ��
                                                                 0��PPLL1��
                                                                 1��PPLL0�� */
        unsigned int  sel_uartl             : 1;  /* bit[2]    : UART0/UART2/UART5����ʱ��Դѡ��
                                                                 0��19.2MHzʱ�ӣ�
                                                                 1����clk_a53hpm(480MHzʱ�ӷ�Ƶ����)�� */
        unsigned int  sel_uarth             : 1;  /* bit[3]    : UART1/UART4����ʱ��Դѡ��
                                                                 0��19.2MHzʱ�ӣ�
                                                                 1����clk_a53hpm(480MHzʱ�ӷ�Ƶ����)�� */
        unsigned int  reserved_0            : 1;  /* bit[4]    : ������ */
        unsigned int  reserved_1            : 1;  /* bit[5]    : ������ */
        unsigned int  reserved_2            : 1;  /* bit[6]    : ������ */
        unsigned int  reserved_3            : 1;  /* bit[7]    : ������ */
        unsigned int  sel_spi               : 1;  /* bit[8]    : SPI1����ʱ��Դѡ��
                                                                 0��19.2MHzʱ�ӣ�
                                                                 1����clk_a53hpm(480MHzʱ�ӷ�Ƶ����)�� */
        unsigned int  lpmcu_clk_sw_req_cfg  : 2;  /* bit[9-10] : ϵͳ������NORMALģʽʱ���������LPMCUʱ���л����ã�ʵ�����õ�bit��Ч��
                                                                 2'bx1:LPMCUʱ���л���19.2MHz����ʱ�ӣ�
                                                                 2'bx0:LPMCUʱ��ԴΪPLLʱ�ӣ� */
        unsigned int  reserved_4            : 1;  /* bit[11]   : ������ */
        unsigned int  reserved_5            : 1;  /* bit[12]   : ������ */
        unsigned int  sel_i2c               : 1;  /* bit[13]   : I2C3/I2C4����ʱ��Դѡ��
                                                                 0��19.2MHzʱ�ӣ�
                                                                 1����clk_a53hpm(480MHzʱ�ӷ�Ƶ����)�� */
        unsigned int  sysbus_clk_sw_req_cfg : 2;  /* bit[14-15]: ϵͳ������NORMALģʽʱ���������sysbusʱ���л����ã�ʵ�����õ�bit��Ч��
                                                                 2'bx1:sysbusʱ���л���19.2MHz����ʱ�ӣ�
                                                                 2'bx0:sysbusʱ��ԴΪPLLʱ�ӣ� */
        unsigned int  clkdivmasken          : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                                 ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV1_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV1_sel_sysbus_START             (0)
#define SOC_CRGPERIPH_CLKDIV1_sel_sysbus_END               (0)
#define SOC_CRGPERIPH_CLKDIV1_sel_lpmcu_START              (1)
#define SOC_CRGPERIPH_CLKDIV1_sel_lpmcu_END                (1)
#define SOC_CRGPERIPH_CLKDIV1_sel_uartl_START              (2)
#define SOC_CRGPERIPH_CLKDIV1_sel_uartl_END                (2)
#define SOC_CRGPERIPH_CLKDIV1_sel_uarth_START              (3)
#define SOC_CRGPERIPH_CLKDIV1_sel_uarth_END                (3)
#define SOC_CRGPERIPH_CLKDIV1_sel_spi_START                (8)
#define SOC_CRGPERIPH_CLKDIV1_sel_spi_END                  (8)
#define SOC_CRGPERIPH_CLKDIV1_lpmcu_clk_sw_req_cfg_START   (9)
#define SOC_CRGPERIPH_CLKDIV1_lpmcu_clk_sw_req_cfg_END     (10)
#define SOC_CRGPERIPH_CLKDIV1_sel_i2c_START                (13)
#define SOC_CRGPERIPH_CLKDIV1_sel_i2c_END                  (13)
#define SOC_CRGPERIPH_CLKDIV1_sysbus_clk_sw_req_cfg_START  (14)
#define SOC_CRGPERIPH_CLKDIV1_sysbus_clk_sw_req_cfg_END    (15)
#define SOC_CRGPERIPH_CLKDIV1_clkdivmasken_START           (16)
#define SOC_CRGPERIPH_CLKDIV1_clkdivmasken_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV2_UNION
 �ṹ˵��  : CLKDIV2 �Ĵ����ṹ���塣��ַƫ����:0x0B0����ֵ:0x00002200�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0   : 7;  /* bit[0-6]  : ������ */
        unsigned int  sc_div_uarth : 4;  /* bit[7-10] : uart1\uart4ʱ�ӷ�Ƶ��ѡ��(��clk_a53hpm 480MHzʱ�ӷ�Ƶ����)
                                                        4'h0:1��
                                                        4'h1:2��
                                                        4'h2:3��
                                                        ��
                                                        4'hE:15��
                                                        4'hF:16�� */
        unsigned int  sc_div_uartl : 4;  /* bit[11-14]: uart0\uart2\uaart5ʱ�ӷ�Ƶ��ѡ��(��clk_a53hpm 480MHzʱ�ӷ�Ƶ����)
                                                        4'h0:1��
                                                        4'h1:2��
                                                        4'h2:3��
                                                        ��
                                                        4'hE:15��
                                                        4'hF:16�� */
        unsigned int  reserved_1   : 1;  /* bit[15]   : ������ */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                        ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV2_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV2_sc_div_uarth_START  (7)
#define SOC_CRGPERIPH_CLKDIV2_sc_div_uarth_END    (10)
#define SOC_CRGPERIPH_CLKDIV2_sc_div_uartl_START  (11)
#define SOC_CRGPERIPH_CLKDIV2_sc_div_uartl_END    (14)
#define SOC_CRGPERIPH_CLKDIV2_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV2_clkdivmasken_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV3_UNION
 �ṹ˵��  : CLKDIV3 �Ĵ����ṹ���塣��ַƫ����:0x0B4����ֵ:0x00000038�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_sel_emmc  : 3;  /* bit[0-2]  : EMMC0/EMMC1ʱ��Դѡ��
                                                        0xx:3.2M��
                                                        1x0:PPLL0��
                                                        1x1:PPLL3�� */
        unsigned int  sc_div_emmc  : 4;  /* bit[3-6]  : EMMC0/EMMC1ʱ�ӷ�Ƶ��ѡ��
                                                        4'h0:1��
                                                        4'h1:2��
                                                        4'h2:3��
                                                        ��
                                                        4'hE:15��
                                                        4'hF:16�� */
        unsigned int  reserved     : 7;  /* bit[7-13] : ������ */
        unsigned int  sc_div_ldi0  : 2;  /* bit[14-15]: LDI0ʱ�ӵ�PLLʱ��Դѡ��ĸ�2bit */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                        ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV3_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV3_sc_sel_emmc_START   (0)
#define SOC_CRGPERIPH_CLKDIV3_sc_sel_emmc_END     (2)
#define SOC_CRGPERIPH_CLKDIV3_sc_div_emmc_START   (3)
#define SOC_CRGPERIPH_CLKDIV3_sc_div_emmc_END     (6)
#define SOC_CRGPERIPH_CLKDIV3_sc_div_ldi0_START   (14)
#define SOC_CRGPERIPH_CLKDIV3_sc_div_ldi0_END     (15)
#define SOC_CRGPERIPH_CLKDIV3_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV3_clkdivmasken_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV4_UNION
 �ṹ˵��  : CLKDIV4 �Ĵ����ṹ���塣��ַƫ����:0x0B8����ֵ:0x00000306�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_sd    : 4;  /* bit[0-3]  : SDʱ�ӷ�Ƶ��ѡ��
                                                        4'h0:1��
                                                        4'h1:2��
                                                        4'h2:3��
                                                        ��
                                                        4'hE:15��
                                                        4'hF:16�� */
        unsigned int  sc_sel_sd    : 3;  /* bit[4-6]  : SDʱ��Դѡ��
                                                        0xx:3.2M��
                                                        100:PPLL0��
                                                        101:PPLL1��
                                                        11x:PPLL3; */
        unsigned int  sc_div_sdio0 : 4;  /* bit[7-10] : SDIO0ʱ�ӷ�Ƶ��ѡ��
                                                        4'h0:1��
                                                        4'h1:2��
                                                        4'h2:3��
                                                        ��
                                                        4'hE:15��
                                                        4'hF:16�� */
        unsigned int  sc_sel_sdio0 : 3;  /* bit[11-13]: SDIO0ʱ��Դѡ��
                                                        0xx:3.2M��
                                                        100:PPLL0��
                                                        101:PPLL1��
                                                        11x:PPLL3; */
        unsigned int  sc_div_ldi1  : 2;  /* bit[14-15]: LDI1ʱ�ӵ�PLLʱ��Դѡ��ĸ�2bit */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                        ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV4_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV4_sc_div_sd_START     (0)
#define SOC_CRGPERIPH_CLKDIV4_sc_div_sd_END       (3)
#define SOC_CRGPERIPH_CLKDIV4_sc_sel_sd_START     (4)
#define SOC_CRGPERIPH_CLKDIV4_sc_sel_sd_END       (6)
#define SOC_CRGPERIPH_CLKDIV4_sc_div_sdio0_START  (7)
#define SOC_CRGPERIPH_CLKDIV4_sc_div_sdio0_END    (10)
#define SOC_CRGPERIPH_CLKDIV4_sc_sel_sdio0_START  (11)
#define SOC_CRGPERIPH_CLKDIV4_sc_sel_sdio0_END    (13)
#define SOC_CRGPERIPH_CLKDIV4_sc_div_ldi1_START   (14)
#define SOC_CRGPERIPH_CLKDIV4_sc_div_ldi1_END     (15)
#define SOC_CRGPERIPH_CLKDIV4_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV4_clkdivmasken_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV5_UNION
 �ṹ˵��  : CLKDIV5 �Ĵ����ṹ���塣��ַƫ����:0x0BC����ֵ:0x00004303�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_edc0  : 6;  /* bit[0-5]  : EDC0ʱ�ӷ�Ƶ��ѡ��
                                                        6'h0:1��
                                                        6'h1:2��
                                                        6'h2:3��
                                                        ��
                                                        6'h3E:63��
                                                        6'h3F:64�� */
        unsigned int  sel_edc0_pll : 2;  /* bit[6-7]  : EDC0��PLLʱ��Դѡ��
                                                        2'b00:PPLL0��
                                                        2'b01:PPLL1��
                                                        2'b10:PPLL2��
                                                        2'b11:PPLL3�� */
        unsigned int  sc_div_ldi0  : 6;  /* bit[8-13] : LDI0ʱ�ӷ�Ƶ��ѡ��
                                                        6'h0:1��
                                                        6'h1:2��
                                                        6'h2:3��
                                                        ��
                                                        6'h3E:63��
                                                        6'h3F:64�� */
        unsigned int  sel_ldi0_pll : 2;  /* bit[14-15]: LDI0ʱ�ӵ�PLLʱ��Դѡ��ĵ�2bit����2bit��CLKDIV3[15:14]��
                                                        4'b0001:PPLL0��
                                                        4'b0010:PPLL2��
                                                        4'b0100:PPLL1��
                                                        4'b1000:PPLL3��
                                                        ����ֵ��Ч�� */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                        ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV5_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV5_sc_div_edc0_START   (0)
#define SOC_CRGPERIPH_CLKDIV5_sc_div_edc0_END     (5)
#define SOC_CRGPERIPH_CLKDIV5_sel_edc0_pll_START  (6)
#define SOC_CRGPERIPH_CLKDIV5_sel_edc0_pll_END    (7)
#define SOC_CRGPERIPH_CLKDIV5_sc_div_ldi0_START   (8)
#define SOC_CRGPERIPH_CLKDIV5_sc_div_ldi0_END     (13)
#define SOC_CRGPERIPH_CLKDIV5_sel_ldi0_pll_START  (14)
#define SOC_CRGPERIPH_CLKDIV5_sel_ldi0_pll_END    (15)
#define SOC_CRGPERIPH_CLKDIV5_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV5_clkdivmasken_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV6_UNION
 �ṹ˵��  : CLKDIV6 �Ĵ����ṹ���塣��ַƫ����:0x0C0����ֵ:0x00004406�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_sdio1 : 4;  /* bit[0-3]  : SDIO1ʱ�ӷ�Ƶ��ѡ��
                                                        4'h0:1��
                                                        4'h1:2��
                                                        4'h2:3��
                                                        ��
                                                        4'hE:15��
                                                        4'hF:16�� */
        unsigned int  sc_sel_sdio1 : 3;  /* bit[4-6]  : SDIO1ʱ��Դѡ��
                                                        0xx:3.2M��
                                                        100:PPLL0��
                                                        101:PPLL1��
                                                        11x:PPLL3; */
        unsigned int  reserved     : 1;  /* bit[7]    : ������ */
        unsigned int  sc_div_ldi1  : 6;  /* bit[8-13] : LDI1ʱ�ӷ�Ƶ��ѡ��
                                                        6'h0:1��
                                                        6'h1:2��
                                                        6'h2:3��
                                                        ��
                                                        6'h3E:63��
                                                        6'h3F:64�� */
        unsigned int  sel_ldi1_pll : 2;  /* bit[14-15]: LDI1ʱ�ӵ�PLLʱ��Դѡ��ĵ�2bit����2bit��CLKDIV4[15:14]��
                                                        4'b0001:PPLL0��
                                                        4'b0010:PPLL2��
                                                        4'b0100:PPLL1��
                                                        4'b1000:PPLL3��
                                                        ����ֵ��Ч�� */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                        ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV6_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV6_sc_div_sdio1_START  (0)
#define SOC_CRGPERIPH_CLKDIV6_sc_div_sdio1_END    (3)
#define SOC_CRGPERIPH_CLKDIV6_sc_sel_sdio1_START  (4)
#define SOC_CRGPERIPH_CLKDIV6_sc_sel_sdio1_END    (6)
#define SOC_CRGPERIPH_CLKDIV6_sc_div_ldi1_START   (8)
#define SOC_CRGPERIPH_CLKDIV6_sc_div_ldi1_END     (13)
#define SOC_CRGPERIPH_CLKDIV6_sel_ldi1_pll_START  (14)
#define SOC_CRGPERIPH_CLKDIV6_sel_ldi1_pll_END    (15)
#define SOC_CRGPERIPH_CLKDIV6_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV6_clkdivmasken_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV7_UNION
 �ṹ˵��  : CLKDIV7 �Ĵ����ṹ���塣��ַƫ����:0x0C4����ֵ:0x00005043�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_ispfunc1              : 5;  /* bit[0-4]  : ISPFUNC1 ʱ�ӷ�Ƶ�ȣ�
                                                                        5'h0:1��
                                                                        5'h1:2��
                                                                        5'h2:3��
                                                                        ��
                                                                        5'h1E:31��
                                                                        5'h1F:32�� */
        unsigned int  sel_ispfunc1                 : 2;  /* bit[5-6]  : ISPFUNC1 PLLʱ��Դѡ��
                                                                        2'h00��PPLL0��
                                                                        2'h01��PPLL1��
                                                                        2'h1x��PPLL3�� */
        unsigned int  sc_isp_func_clk_sel_ispfunc1 : 1;  /* bit[7]    : ISPFUNC ʱ��Դѡ��
                                                                        1'h0��clk_ispfunc2��
                                                                        1'h1��clk_ispfunc1�� */
        unsigned int  sc_sel_clk_rxdpbhy_cfg       : 1;  /* bit[8]    : RXDPHYCFG ʱ��Դѡ��
                                                                        1'h0��clk_rxdphy_fix_div��
                                                                        1'h1��clk_sys�� */
        unsigned int  reserved                     : 3;  /* bit[9-11] :  */
        unsigned int  div_clk_spi                  : 4;  /* bit[12-15]: SPIʱ�ӷ�Ƶ�ȣ�Դʱ����clk_a53hpm_div(Ĭ��480M���ɵ������÷�Ƶ��)����
                                                                        4'h0:1��
                                                                        4'h1:2��
                                                                        4'h2:3��
                                                                        ��
                                                                        4'hE:15��
                                                                        4'hF:16�� */
        unsigned int  clkdivmasken                 : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                                        ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV7_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV7_sc_div_ispfunc1_START               (0)
#define SOC_CRGPERIPH_CLKDIV7_sc_div_ispfunc1_END                 (4)
#define SOC_CRGPERIPH_CLKDIV7_sel_ispfunc1_START                  (5)
#define SOC_CRGPERIPH_CLKDIV7_sel_ispfunc1_END                    (6)
#define SOC_CRGPERIPH_CLKDIV7_sc_isp_func_clk_sel_ispfunc1_START  (7)
#define SOC_CRGPERIPH_CLKDIV7_sc_isp_func_clk_sel_ispfunc1_END    (7)
#define SOC_CRGPERIPH_CLKDIV7_sc_sel_clk_rxdpbhy_cfg_START        (8)
#define SOC_CRGPERIPH_CLKDIV7_sc_sel_clk_rxdpbhy_cfg_END          (8)
#define SOC_CRGPERIPH_CLKDIV7_div_clk_spi_START                   (12)
#define SOC_CRGPERIPH_CLKDIV7_div_clk_spi_END                     (15)
#define SOC_CRGPERIPH_CLKDIV7_clkdivmasken_START                  (16)
#define SOC_CRGPERIPH_CLKDIV7_clkdivmasken_END                    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV8_UNION
 �ṹ˵��  : CLKDIV8 �Ĵ����ṹ���塣��ַƫ����:0x0C8����ֵ:0x000010C3�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_ispfunc2 : 5;  /* bit[0-4]  : ISPFUNC2 ʱ�ӷ�Ƶ�ȣ�
                                                           5'h0:1��
                                                           5'h1:2��
                                                           5'h2:3��
                                                           ��
                                                           5'h1E:31��
                                                           5'h1F:32�� */
        unsigned int  sel_ispfunc2    : 1;  /* bit[5]    : ISPFUNC2 PLLʱ��Դѡ��
                                                           0��PPLL0��
                                                           1��PPLL1�� */
        unsigned int  sc_div_venc     : 5;  /* bit[6-10] : VENCʱ�ӷ�Ƶ�ȣ�
                                                           5'h0:1��
                                                           5'h1:2��
                                                           5'h2:3��
                                                           ��
                                                           5'h1E:31��
                                                           5'h1F:32�� */
        unsigned int  sel_venc        : 2;  /* bit[11-12]: VENC PLLʱ��Դѡ��
                                                           2'b00��PPLL0��
                                                           2'b01��PPLL1��
                                                           2'b1x��PPLL3�� */
        unsigned int  reserved        : 3;  /* bit[13-15]: ������ */
        unsigned int  clkdivmasken    : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                           ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV8_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV8_sc_div_ispfunc2_START  (0)
#define SOC_CRGPERIPH_CLKDIV8_sc_div_ispfunc2_END    (4)
#define SOC_CRGPERIPH_CLKDIV8_sel_ispfunc2_START     (5)
#define SOC_CRGPERIPH_CLKDIV8_sel_ispfunc2_END       (5)
#define SOC_CRGPERIPH_CLKDIV8_sc_div_venc_START      (6)
#define SOC_CRGPERIPH_CLKDIV8_sc_div_venc_END        (10)
#define SOC_CRGPERIPH_CLKDIV8_sel_venc_START         (11)
#define SOC_CRGPERIPH_CLKDIV8_sel_venc_END           (12)
#define SOC_CRGPERIPH_CLKDIV8_clkdivmasken_START     (16)
#define SOC_CRGPERIPH_CLKDIV8_clkdivmasken_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV9_UNION
 �ṹ˵��  : CLKDIV9 �Ĵ����ṹ���塣��ַƫ����:0x0CC����ֵ:0x00000043�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���9��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_vdec  : 5;  /* bit[0-4]  : VDECʱ�ӷ�Ƶ��ѡ��
                                                        5'h0:1��
                                                        5'h1:2��
                                                        5'h2:3��
                                                        ��
                                                        5'h1E:31��
                                                        5'h1F:32�� */
        unsigned int  sel_vdec     : 2;  /* bit[5-6]  : VDEC PLLʱ��Դѡ��
                                                        2'b00��PPLL0��
                                                        2'b01��PPLL1��
                                                        2'b10��PPLL2��
                                                        2'b11��PPLL3�� */
        unsigned int  reserved     : 9;  /* bit[7-15] : ������ */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                        ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV9_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV9_sc_div_vdec_START   (0)
#define SOC_CRGPERIPH_CLKDIV9_sc_div_vdec_END     (4)
#define SOC_CRGPERIPH_CLKDIV9_sel_vdec_START      (5)
#define SOC_CRGPERIPH_CLKDIV9_sel_vdec_END        (6)
#define SOC_CRGPERIPH_CLKDIV9_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV9_clkdivmasken_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV10_UNION
 �ṹ˵��  : CLKDIV10 �Ĵ����ṹ���塣��ַƫ����:0x0D0����ֵ:0x0000E142�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���10��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_vcodecbus : 5;  /* bit[0-4]  : VCODECBUS ʱ�ӷ�Ƶ�ȣ�
                                                            5'h0:1��
                                                            5'h1:2��
                                                            ��
                                                            5'h1E:31��
                                                            5'h1F:32�� */
        unsigned int  sc_sel_vcodecbus : 2;  /* bit[5-6]  : VCODECBUS PLLʱ��Դѡ��
                                                            2'b00:PPLL0��
                                                            2'b01:PPLL1��
                                                            2'b10:PPLL2��
                                                            2'b11:PPLL3�� */
        unsigned int  sc_div_vivobus   : 5;  /* bit[7-11] : VIVOBUS ʱ�ӷ�Ƶ�ȣ�
                                                            5'h0:1��
                                                            5'h1:2��
                                                            ��
                                                            5'h1E:31��
                                                            5'h1F:32�� */
        unsigned int  sc_sel_vivobus   : 2;  /* bit[12-13]: VIVOBUS PLLʱ��Դѡ��
                                                            2'b00:PPLL0��
                                                            2'b01:PPLL1��
                                                            2'b10:PPLL2��
                                                            2'b11:PPLL3�� */
        unsigned int  sc_div_perf_stat : 2;  /* bit[14-15]: CLK_PERF_STAT ʱ�ӷ�Ƶ�ȣ�
                                                            2'h0:1��
                                                            2'h1:2��
                                                            2'h2:3��
                                                            2'h3:4�� */
        unsigned int  clkdivmasken     : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                            ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV10_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV10_sc_div_vcodecbus_START  (0)
#define SOC_CRGPERIPH_CLKDIV10_sc_div_vcodecbus_END    (4)
#define SOC_CRGPERIPH_CLKDIV10_sc_sel_vcodecbus_START  (5)
#define SOC_CRGPERIPH_CLKDIV10_sc_sel_vcodecbus_END    (6)
#define SOC_CRGPERIPH_CLKDIV10_sc_div_vivobus_START    (7)
#define SOC_CRGPERIPH_CLKDIV10_sc_div_vivobus_END      (11)
#define SOC_CRGPERIPH_CLKDIV10_sc_sel_vivobus_START    (12)
#define SOC_CRGPERIPH_CLKDIV10_sc_sel_vivobus_END      (13)
#define SOC_CRGPERIPH_CLKDIV10_sc_div_perf_stat_START  (14)
#define SOC_CRGPERIPH_CLKDIV10_sc_div_perf_stat_END    (15)
#define SOC_CRGPERIPH_CLKDIV10_clkdivmasken_START      (16)
#define SOC_CRGPERIPH_CLKDIV10_clkdivmasken_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV11_UNION
 �ṹ˵��  : CLKDIV11 �Ĵ����ṹ���塣��ַƫ����:0x0D4����ֵ:0x00000141�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���11��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_ispa7  : 5;  /* bit[0-4]  : ISPA7 ʱ�ӷ�Ƶ�ȣ�
                                                         5'h0:1��
                                                         5'h1:2��
                                                         5'h2:3��
                                                         ��
                                                         5'h1E:31��
                                                         5'h1F:32�� */
        unsigned int  sel_ispa7     : 2;  /* bit[5-6]  : ISPA7 PLLʱ��Դѡ��
                                                         2'b00:PPLL0��
                                                         2'b01:PPLL1��
                                                         2'b1x:PPLL3�� */
        unsigned int  sc_div_a53hpm : 2;  /* bit[7-8]  : A53HPMʱ�ӷ�Ƶ�ȣ�
                                                         2'h0:1��
                                                         2'h1:2��
                                                         2'h2:3��
                                                         2'h3:4�� */
        unsigned int  sel_a53hpm    : 1;  /* bit[9]    : A53HPM PLLʱ��Դѡ��
                                                         0��PPLL0��
                                                         1��PPLL1�� */
        unsigned int  reserved      : 6;  /* bit[10-15]: ������ */
        unsigned int  clkdivmasken  : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                         ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV11_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV11_sc_div_ispa7_START   (0)
#define SOC_CRGPERIPH_CLKDIV11_sc_div_ispa7_END     (4)
#define SOC_CRGPERIPH_CLKDIV11_sel_ispa7_START      (5)
#define SOC_CRGPERIPH_CLKDIV11_sel_ispa7_END        (6)
#define SOC_CRGPERIPH_CLKDIV11_sc_div_a53hpm_START  (7)
#define SOC_CRGPERIPH_CLKDIV11_sc_div_a53hpm_END    (8)
#define SOC_CRGPERIPH_CLKDIV11_sel_a53hpm_START     (9)
#define SOC_CRGPERIPH_CLKDIV11_sel_a53hpm_END       (9)
#define SOC_CRGPERIPH_CLKDIV11_clkdivmasken_START   (16)
#define SOC_CRGPERIPH_CLKDIV11_clkdivmasken_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV12_UNION
 �ṹ˵��  : CLKDIV12 �Ĵ����ṹ���塣��ַƫ����:0x0D8����ֵ:0x000007E0�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���12��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_modem_bbe16 : 2;  /* bit[0-1]  : MODEM BBE16 PLLʱ��Դѡ��ĸ�2bit */
        unsigned int  sc_div_modem_mcpu  : 2;  /* bit[2-3]  : MODEM MCPU PLLʱ��Դѡ��ĸ�2bit */
        unsigned int  reserved_0         : 1;  /* bit[4]    : ������ */
        unsigned int  sc_div_slimbus     : 6;  /* bit[5-10] : SLIMBUSʱ�ӷ�Ƶ��(��Դʱ����PPLL1/2/3)��
                                                              6'h0:1��
                                                              6'h1:2��
                                                              6'h2:3��
                                                              ��
                                                              6'h3E:63��
                                                              6'h3F:64�� */
        unsigned int  sc_sel_slimbus     : 2;  /* bit[11-12]: SLIMBUSʱ��Դѡ��
                                                              2'b00:PPLL1��
                                                              2'b01:PPLL2��
                                                              2'b1x:PPLL3�� */
        unsigned int  reserved_1         : 3;  /* bit[13-15]: ������ */
        unsigned int  clkdivmasken       : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                              ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV12_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV12_sc_div_modem_bbe16_START  (0)
#define SOC_CRGPERIPH_CLKDIV12_sc_div_modem_bbe16_END    (1)
#define SOC_CRGPERIPH_CLKDIV12_sc_div_modem_mcpu_START   (2)
#define SOC_CRGPERIPH_CLKDIV12_sc_div_modem_mcpu_END     (3)
#define SOC_CRGPERIPH_CLKDIV12_sc_div_slimbus_START      (5)
#define SOC_CRGPERIPH_CLKDIV12_sc_div_slimbus_END        (10)
#define SOC_CRGPERIPH_CLKDIV12_sc_sel_slimbus_START      (11)
#define SOC_CRGPERIPH_CLKDIV12_sc_sel_slimbus_END        (12)
#define SOC_CRGPERIPH_CLKDIV12_clkdivmasken_START        (16)
#define SOC_CRGPERIPH_CLKDIV12_clkdivmasken_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV13_UNION
 �ṹ˵��  : CLKDIV13 �Ĵ����ṹ���塣��ַƫ����:0x0DC����ֵ:0x00003420�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���13��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_modem_bbe16 : 4;  /* bit[0-3]  : MODEM BBE16ʱ�ӷ�Ƶ��ѡ��
                                                           4'h0:1��
                                                           4'h1:2��
                                                           4'h2:3��
                                                           ��
                                                           4'hE:15��
                                                           4'hF:16�� */
        unsigned int  sel_modem_bbe16 : 2;  /* bit[4-5]  : MODEM BBE16 PLLʱ��Դѡ��ĵ�2bit����2bit��CLKDIV12[1:0]��
                                                           4'b0001��PPLL4��
                                                           4'b0010��PPLL5��
                                                           4'b0100��PPLL0��
                                                           4'b1000��PPLL3��
                                                           ����ֵ��Ч�� */
        unsigned int  div_modem_mcpu  : 4;  /* bit[6-9]  : MODEM MCPUʱ�ӷ�Ƶ��ѡ��
                                                           4'h0:1��
                                                           4'h1:2��
                                                           4'h2:3��
                                                           ��
                                                           4'hE:15��
                                                           4'hF:16�� */
        unsigned int  sel_modem_mcpu  : 2;  /* bit[10-11]: MODEM MCPU PLLʱ��Դѡ��ĵ�2bit����2bit��CLKDIV12[3:2]��
                                                           4'b0001��PPLL4��
                                                           4'b0010��PPLL5��
                                                           4'b0100��PPLL0��
                                                           4'b1000��PPLL3��
                                                           ����ֵ��Ч�� */
        unsigned int  div_ptp         : 4;  /* bit[12-15]: PWM/TIMER/PCTRL PCLKʱ�ӷ�Ƶ��ѡ��
                                                           4'h0:1��
                                                           4'h1:2��
                                                           4'h2:3��
                                                           ��
                                                           4'hE:15��
                                                           4'hF:16�� */
        unsigned int  clkdivmasken    : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                           ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV13_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV13_div_modem_bbe16_START  (0)
#define SOC_CRGPERIPH_CLKDIV13_div_modem_bbe16_END    (3)
#define SOC_CRGPERIPH_CLKDIV13_sel_modem_bbe16_START  (4)
#define SOC_CRGPERIPH_CLKDIV13_sel_modem_bbe16_END    (5)
#define SOC_CRGPERIPH_CLKDIV13_div_modem_mcpu_START   (6)
#define SOC_CRGPERIPH_CLKDIV13_div_modem_mcpu_END     (9)
#define SOC_CRGPERIPH_CLKDIV13_sel_modem_mcpu_START   (10)
#define SOC_CRGPERIPH_CLKDIV13_sel_modem_mcpu_END     (11)
#define SOC_CRGPERIPH_CLKDIV13_div_ptp_START          (12)
#define SOC_CRGPERIPH_CLKDIV13_div_ptp_END            (15)
#define SOC_CRGPERIPH_CLKDIV13_clkdivmasken_START     (16)
#define SOC_CRGPERIPH_CLKDIV13_clkdivmasken_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV14_UNION
 �ṹ˵��  : CLKDIV14 �Ĵ����ṹ���塣��ַƫ����:0x0E0����ֵ:0x0000EBA0�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���14��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_sel_clk_usb3phy_ref : 1;  /* bit[0]    : PERI_CRG �͸�USB3PHY �ο�ʱ�ӵ�ʱ��Դѡ��
                                                                  0:19.2M clk_usb3phy_ref;
                                                                  1:PLL0 clk_usb2phy_pll */
        unsigned int  reserved               : 3;  /* bit[1-3]  : ������ */
        unsigned int  div_clkout0_pll        : 6;  /* bit[4-9]  : clkout0 PLLʱ�ӷ�Ƶ��ѡ��(Դʱ��ΪPPLL3)
                                                                  6'h0:1��
                                                                  6'h1:2��
                                                                  6'h2:3��
                                                                  ��
                                                                  6'h3E:63��
                                                                  6'h3F:64�� */
        unsigned int  div_clkout1_pll        : 6;  /* bit[10-15]: clkout1 PLLʱ�ӷ�Ƶ��ѡ��(Դʱ��ΪPPLL3)
                                                                  6'h0:1��
                                                                  6'h1:2��
                                                                  6'h2:3��
                                                                  ��
                                                                  6'h3E:63��
                                                                  6'h3F:64�� */
        unsigned int  clkdivmasken           : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                                  ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV14_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV14_sc_sel_clk_usb3phy_ref_START  (0)
#define SOC_CRGPERIPH_CLKDIV14_sc_sel_clk_usb3phy_ref_END    (0)
#define SOC_CRGPERIPH_CLKDIV14_div_clkout0_pll_START         (4)
#define SOC_CRGPERIPH_CLKDIV14_div_clkout0_pll_END           (9)
#define SOC_CRGPERIPH_CLKDIV14_div_clkout1_pll_START         (10)
#define SOC_CRGPERIPH_CLKDIV14_div_clkout1_pll_END           (15)
#define SOC_CRGPERIPH_CLKDIV14_clkdivmasken_START            (16)
#define SOC_CRGPERIPH_CLKDIV14_clkdivmasken_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV15_UNION
 �ṹ˵��  : CLKDIV15 �Ĵ����ṹ���塣��ַƫ����:0x0E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���15��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_avstrig  : 16; /* bit[0-15] : AVS�����źŵķ�Ƶ�����õĵ�16λ��Դʱ����˯��ʱ�ӣ� */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                        ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV15_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV15_div_avstrig_START   (0)
#define SOC_CRGPERIPH_CLKDIV15_div_avstrig_END     (15)
#define SOC_CRGPERIPH_CLKDIV15_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV15_clkdivmasken_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV16_UNION
 �ṹ˵��  : CLKDIV16 �Ĵ����ṹ���塣��ַƫ����:0x0E8����ֵ:0x00000130�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���16��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_avstrig         : 4;  /* bit[0-3]  : AVS�����źŵķ�Ƶ�����õĸ�4λ��Դʱ����˯��ʱ�ӣ� */
        unsigned int  sc_div_i2c          : 4;  /* bit[4-7]  : I2C3\I2C4ʱ�ӷ�Ƶ��ѡ�񣺣�Դʱ����clk_a53hpm_div(Ĭ��480M���ɵ������÷�Ƶ��)��
                                                               4'h0:1��
                                                               4'h1:2��
                                                               4'h2:3��
                                                               ��
                                                               4'hE:15��
                                                               4'hF:16�� */
        unsigned int  ddrcpll_sw          : 4;  /* bit[8-11] : DDRCʱ��ѡ���ĸ�PLL��
                                                               0001:PPLL0;
                                                               0010:PPLL1;
                                                               0100:PPLl2;
                                                               1000:PPLL3; */
        unsigned int  ddrc_clk_sw_req_cfg : 2;  /* bit[12-13]: ϵͳ������NORMALģʽʱ���������DDRCʱ���л����ã�ʵ�����õ�bit��Ч��
                                                               2'bx1:DDRCʱ���л���19.2MHz����ʱ�ӣ�
                                                               2'bx0:DDRCʱ��ԴΪPLLʱ�ӣ� */
        unsigned int  reserved            : 2;  /* bit[14-15]: ������ */
        unsigned int  clkdivmasken        : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                               ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV16_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV16_div_avstrig_START          (0)
#define SOC_CRGPERIPH_CLKDIV16_div_avstrig_END            (3)
#define SOC_CRGPERIPH_CLKDIV16_sc_div_i2c_START           (4)
#define SOC_CRGPERIPH_CLKDIV16_sc_div_i2c_END             (7)
#define SOC_CRGPERIPH_CLKDIV16_ddrcpll_sw_START           (8)
#define SOC_CRGPERIPH_CLKDIV16_ddrcpll_sw_END             (11)
#define SOC_CRGPERIPH_CLKDIV16_ddrc_clk_sw_req_cfg_START  (12)
#define SOC_CRGPERIPH_CLKDIV16_ddrc_clk_sw_req_cfg_END    (13)
#define SOC_CRGPERIPH_CLKDIV16_clkdivmasken_START         (16)
#define SOC_CRGPERIPH_CLKDIV16_clkdivmasken_END           (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV17_UNION
 �ṹ˵��  : CLKDIV17 �Ĵ����ṹ���塣��ַƫ����:0x0EC����ֵ:0x0000B42D�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���17��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sc_div_cfgbus         : 2;  /* bit[0-1]  : config BUSʱ�ӷ�Ƶ�ȡ�(Դʱ����clk_sysbus��Ĭ��240MHz����Ƶ��������)
                                                                 2'h0:1��
                                                                 2'h1:2��
                                                                 2'h2:3��
                                                                 2'h3:4�� */
        unsigned int  sc_div_mmc0_peribus   : 1;  /* bit[2]    : MMC0 PERIBUSʱ�ӷ�Ƶ�ȡ�(Դʱ����clk_sysbus��Ĭ��240MHz����Ƶ��������)
                                                                 1'b0:1��
                                                                 1'b1:2�� */
        unsigned int  sc_div_mmc1_peribus   : 1;  /* bit[3]    : MMC1 PERIBUSʱ�ӷ�Ƶ�ȡ�(Դʱ����clk_sysbus��Ĭ��240MHz����Ƶ��������)
                                                                 1'b0:1��
                                                                 1'b1:2�� */
        unsigned int  div_modem_bbe16_tdl   : 4;  /* bit[4-7]  : MODEM BBE16ʱ�ӷ�Ƶ��ѡ��
                                                                 4'h0:1��
                                                                 4'h1:2��
                                                                 4'h2:3��
                                                                 ��
                                                                 4'hE:15��
                                                                 4'hF:16�� */
        unsigned int  sel_modem_bbe16_tdl   : 4;  /* bit[8-11] : MODEM BBE16 PLLʱ��Դѡ��
                                                                 4'b0001��PPLL4��
                                                                 4'b0010��PPLL5��
                                                                 4'b0100��PPLL0��
                                                                 4'b1000��PPLL3��
                                                                 ����ֵ��Ч�� */
        unsigned int  sc_div_dbgsechsic_bus : 1;  /* bit[12]   : DBGSECHSIC BUSʱ�ӷ�Ƶ�ȡ�(Դʱ����clk_sysbus��Ĭ��240MHz����Ƶ��������)
                                                                 1'b0:1��
                                                                 1'b1:2�� */
        unsigned int  sc_div_cssysdbg       : 1;  /* bit[13]   : CSSYS DEBUGʱ�ӷ�Ƶ�ȡ�(Դʱ����clk_sysbus��Ĭ��240MHz����Ƶ��������)
                                                                 1'b0:1��
                                                                 1'b1:2�� */
        unsigned int  reserved              : 1;  /* bit[14]   : ������ */
        unsigned int  sc_div_dmabus         : 1;  /* bit[15]   : DMA BUSʱ�ӷ�Ƶ�ȡ�(Դʱ����clk_sysbus��Ĭ��240MHz����Ƶ��������)
                                                                 1'b0:1��
                                                                 1'b1:2�� */
        unsigned int  clkdivmasken          : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                                 ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV17_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV17_sc_div_cfgbus_START          (0)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_cfgbus_END            (1)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_mmc0_peribus_START    (2)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_mmc0_peribus_END      (2)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_mmc1_peribus_START    (3)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_mmc1_peribus_END      (3)
#define SOC_CRGPERIPH_CLKDIV17_div_modem_bbe16_tdl_START    (4)
#define SOC_CRGPERIPH_CLKDIV17_div_modem_bbe16_tdl_END      (7)
#define SOC_CRGPERIPH_CLKDIV17_sel_modem_bbe16_tdl_START    (8)
#define SOC_CRGPERIPH_CLKDIV17_sel_modem_bbe16_tdl_END      (11)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_dbgsechsic_bus_START  (12)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_dbgsechsic_bus_END    (12)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_cssysdbg_START        (13)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_cssysdbg_END          (13)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_dmabus_START          (15)
#define SOC_CRGPERIPH_CLKDIV17_sc_div_dmabus_END            (15)
#define SOC_CRGPERIPH_CLKDIV17_clkdivmasken_START           (16)
#define SOC_CRGPERIPH_CLKDIV17_clkdivmasken_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV18_UNION
 �ṹ˵��  : CLKDIV18 �Ĵ����ṹ���塣��ַƫ����:0x0F0����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���18��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_g3daxi0    : 1;  /* bit[0]    : 1��ʱ�ӿ����� 0��ʱ�ӹر� */
        unsigned int  gt_clk_g3daxi1    : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_ddrc       : 1;  /* bit[2]    :  */
        unsigned int  reserved_0        : 1;  /* bit[3]    : ������ */
        unsigned int  gt_clk_lpmcu      : 1;  /* bit[4]    :  */
        unsigned int  reserved_1        : 1;  /* bit[5]    : ������ */
        unsigned int  gt_clk_ldi0       : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_ldi1       : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_edc0       : 1;  /* bit[8]    :  */
        unsigned int  reserved_2        : 1;  /* bit[9]    : ������ */
        unsigned int  gt_clk_out0       : 1;  /* bit[10]   :  */
        unsigned int  gt_clk_out1       : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_rxdphy_cfg : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_ispfunc1   : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_ispfunc2   : 1;  /* bit[14]   :  */
        unsigned int  gt_clk_vdec       : 1;  /* bit[15]   :  */
        unsigned int  clkdivmasken      : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                             ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV18_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_g3daxi0_START     (0)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_g3daxi0_END       (0)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_g3daxi1_START     (1)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_g3daxi1_END       (1)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ddrc_START        (2)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ddrc_END          (2)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_lpmcu_START       (4)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_lpmcu_END         (4)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ldi0_START        (6)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ldi0_END          (6)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ldi1_START        (7)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ldi1_END          (7)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_edc0_START        (8)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_edc0_END          (8)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_out0_START        (10)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_out0_END          (10)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_out1_START        (11)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_out1_END          (11)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_rxdphy_cfg_START  (12)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_rxdphy_cfg_END    (12)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ispfunc1_START    (13)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ispfunc1_END      (13)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ispfunc2_START    (14)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_ispfunc2_END      (14)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_vdec_START        (15)
#define SOC_CRGPERIPH_CLKDIV18_gt_clk_vdec_END          (15)
#define SOC_CRGPERIPH_CLKDIV18_clkdivmasken_START       (16)
#define SOC_CRGPERIPH_CLKDIV18_clkdivmasken_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV19_UNION
 �ṹ˵��  : CLKDIV19 �Ĵ����ṹ���塣��ַƫ����:0x0F4����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���19��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_venc    : 1;  /* bit[0]    : 1��ʱ�ӿ����� 0��ʱ�ӹر� */
        unsigned int  reserved_0     : 1;  /* bit[1]    : ������ */
        unsigned int  gt_clk_emmc0   : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_sd      : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_sdio0   : 1;  /* bit[4]    :  */
        unsigned int  reserved_1     : 1;  /* bit[5]    : ������ */
        unsigned int  reserved_2     : 1;  /* bit[6]    : ������ */
        unsigned int  gt_clk_a53hpm  : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_sdio1   : 1;  /* bit[8]    :  */
        unsigned int  reserved_3     : 1;  /* bit[9]    : ������ */
        unsigned int  reserved_4     : 1;  /* bit[10]   : ������ */
        unsigned int  gt_clk_uarth   : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_uartl   : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_spi     : 1;  /* bit[13]   :  */
        unsigned int  reserved_5     : 1;  /* bit[14]   : ������ */
        unsigned int  gt_clk_slimbus : 1;  /* bit[15]   :  */
        unsigned int  clkdivmasken   : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                          ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV19_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_venc_START     (0)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_venc_END       (0)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_emmc0_START    (2)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_emmc0_END      (2)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sd_START       (3)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sd_END         (3)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sdio0_START    (4)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sdio0_END      (4)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_a53hpm_START   (7)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_a53hpm_END     (7)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sdio1_START    (8)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_sdio1_END      (8)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_uarth_START    (11)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_uarth_END      (11)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_uartl_START    (12)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_uartl_END      (12)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_spi_START      (13)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_spi_END        (13)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_slimbus_START  (15)
#define SOC_CRGPERIPH_CLKDIV19_gt_clk_slimbus_END    (15)
#define SOC_CRGPERIPH_CLKDIV19_clkdivmasken_START    (16)
#define SOC_CRGPERIPH_CLKDIV19_clkdivmasken_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV20_UNION
 �ṹ˵��  : CLKDIV20 �Ĵ����ṹ���塣��ַƫ����:0x0F8����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���20��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_i2c             : 1;  /* bit[0]    : 1��ʱ�ӿ����� 0��ʱ�ӹر� */
        unsigned int  gt_clk_vivobus         : 1;  /* bit[1]    : ������ */
        unsigned int  gt_clk_vcodecbus       : 1;  /* bit[2]    : ������ */
        unsigned int  gt_clk_aomm            : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_ispa7           : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_ptp             : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_modem_mcpu      : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_modem_bbe16     : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_modem_bbe16_tdl : 1;  /* bit[8]    :  */
        unsigned int  gt_clk_ivp32dsp_core   : 1;  /* bit[9]    :  */
        unsigned int  reserved_0             : 1;  /* bit[10]   :  */
        unsigned int  gt_clk_ddrphy_ref_a    : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_ddrphy_ref_b    : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_ddrphy_ref_c    : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_ddrphy_ref_d    : 1;  /* bit[14]   :  */
        unsigned int  reserved_1             : 1;  /* bit[15]   : ������ */
        unsigned int  clkdivmasken           : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                                  ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV20_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_i2c_START              (0)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_i2c_END                (0)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_vivobus_START          (1)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_vivobus_END            (1)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_vcodecbus_START        (2)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_vcodecbus_END          (2)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_aomm_START             (3)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_aomm_END               (3)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ispa7_START            (4)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ispa7_END              (4)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ptp_START              (5)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ptp_END                (5)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_mcpu_START       (6)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_mcpu_END         (6)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_bbe16_START      (7)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_bbe16_END        (7)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_bbe16_tdl_START  (8)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_modem_bbe16_tdl_END    (8)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ivp32dsp_core_START    (9)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ivp32dsp_core_END      (9)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_a_START     (11)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_a_END       (11)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_b_START     (12)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_b_END       (12)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_c_START     (13)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_c_END       (13)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_d_START     (14)
#define SOC_CRGPERIPH_CLKDIV20_gt_clk_ddrphy_ref_d_END       (14)
#define SOC_CRGPERIPH_CLKDIV20_clkdivmasken_START            (16)
#define SOC_CRGPERIPH_CLKDIV20_clkdivmasken_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV21_UNION
 �ṹ˵��  : CLKDIV21 �Ĵ����ṹ���塣��ַƫ����:0x0FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���21��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved     : 16; /* bit[0-15] : ������ */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                        ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV21_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV21_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV21_clkdivmasken_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV22_UNION
 �ṹ˵��  : CLKDIV22 �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x00007980�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���22��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0         : 7;  /* bit[0-6]  :  */
        unsigned int  sc_div_aomm        : 4;  /* bit[7-10] : AONOMMBUF 400M����ʱ�ӷ�Ƶϵ�� */
        unsigned int  div_clk_sys_ddr    : 2;  /* bit[11-12]: DDR SW sysclk ��Ƶϵ�� */
        unsigned int  div_clk_sys_sysbus : 2;  /* bit[13-14]: SYSBUS SW sysclk ��Ƶϵ�� */
        unsigned int  reserved_1         : 1;  /* bit[15]   : ������ */
        unsigned int  clkdivmasken       : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                              ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV22_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV22_sc_div_aomm_START         (7)
#define SOC_CRGPERIPH_CLKDIV22_sc_div_aomm_END           (10)
#define SOC_CRGPERIPH_CLKDIV22_div_clk_sys_ddr_START     (11)
#define SOC_CRGPERIPH_CLKDIV22_div_clk_sys_ddr_END       (12)
#define SOC_CRGPERIPH_CLKDIV22_div_clk_sys_sysbus_START  (13)
#define SOC_CRGPERIPH_CLKDIV22_div_clk_sys_sysbus_END    (14)
#define SOC_CRGPERIPH_CLKDIV22_clkdivmasken_START        (16)
#define SOC_CRGPERIPH_CLKDIV22_clkdivmasken_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV23_UNION
 �ṹ˵��  : CLKDIV23 �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x000036A5�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���23��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_clk_ddrc          : 5;  /* bit[0-4]  : DDRCԴʱ�ӷ�Ƶѡ��
                                                                 5'h00:1��
                                                                 5'h01:2��
                                                                 5'h02:3��
                                                                 ��
                                                                 5'h1E:15��
                                                                 5'h1F:32�� */
        unsigned int  div_clk_ddrcfg        : 2;  /* bit[5-6]  : DDRCFGʱ�ӷ�Ƶѡ��
                                                                 2'h0:1��
                                                                 2'h1:2��
                                                                 2'h2:3��
                                                                 2'h3:4�� */
        unsigned int  gt_clk_ddrcfg         : 1;  /* bit[7]    : clk_ddrcfg�ſ�ʹ���źţ�
                                                                 0��ʱ�ӹرգ�
                                                                 1��ʱ��ʹ�ܣ� */
        unsigned int  div_clk_ddrphy_ref    : 1;  /* bit[8]    : ddrphy refclk��Ƶѡ��
                                                                 1'h0��1��
                                                                 1'h1��2�� */
        unsigned int  div_clk_ddrphy_ref_en : 1;  /* bit[9]    : ddrphy refclk��Ƶʹ�ܣ�
                                                                 0����Ƶʹ�ܳ�����
                                                                 1��ʱ��ʹ����Ч�� */
        unsigned int  div_clk_ddrsys        : 2;  /* bit[10-11]: DDRSYSʱ�ӷ�Ƶѡ��
                                                                 2'h0:1��
                                                                 2'h1:2��
                                                                 2'h2:3��
                                                                 2'h3:4�� */
        unsigned int  gt_div_ddrsys_noc     : 1;  /* bit[12]   : clk_ddrsys_nocʱ���ſ�ʹ���źţ�
                                                                 0��ʱ�ӹرգ�
                                                                 1��ʱ��ʹ�ܣ� */
        unsigned int  gt_clk_ddrc_sw        : 1;  /* bit[13]   : ddrc OCC_ROOT֮ǰ�ſ�ʹ���ź� */
        unsigned int  reserved              : 2;  /* bit[14-15]: ������ */
        unsigned int  clkdivmasken          : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                                 ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV23_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrc_START           (0)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrc_END             (4)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrcfg_START         (5)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrcfg_END           (6)
#define SOC_CRGPERIPH_CLKDIV23_gt_clk_ddrcfg_START          (7)
#define SOC_CRGPERIPH_CLKDIV23_gt_clk_ddrcfg_END            (7)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrphy_ref_START     (8)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrphy_ref_END       (8)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrphy_ref_en_START  (9)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrphy_ref_en_END    (9)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrsys_START         (10)
#define SOC_CRGPERIPH_CLKDIV23_div_clk_ddrsys_END           (11)
#define SOC_CRGPERIPH_CLKDIV23_gt_div_ddrsys_noc_START      (12)
#define SOC_CRGPERIPH_CLKDIV23_gt_div_ddrsys_noc_END        (12)
#define SOC_CRGPERIPH_CLKDIV23_gt_clk_ddrc_sw_START         (13)
#define SOC_CRGPERIPH_CLKDIV23_gt_clk_ddrc_sw_END           (13)
#define SOC_CRGPERIPH_CLKDIV23_clkdivmasken_START           (16)
#define SOC_CRGPERIPH_CLKDIV23_clkdivmasken_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV24_UNION
 �ṹ˵��  : CLKDIV24 �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x00000007�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���24��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  div_isp_snclk     : 2;  /* bit[0-1]  : clk_isp_snclk ��Ƶѡ��
                                                             2'h0:1��Ƶ��48M��
                                                             2'h1:2��Ƶ��24M��
                                                             2'h2:3��Ƶ��16M��
                                                             2'h3:4��Ƶ��12M�� */
        unsigned int  gt_clk_isp_snclk  : 1;  /* bit[2]    : clk_isp_snclk ��Ƶ�ſ�ʹ���źţ�
                                                             0��ʱ�ӹرգ�
                                                             1��ʱ��ʹ�ܣ� */
        unsigned int  sel_clk_isp_snclk : 1;  /* bit[3]    : clk_isp_snclk_sys ʱ��ѡ���źţ�
                                                             0��clk_isp_snclk_sys��
                                                             1��clk_isp_snclk_div�� */
        unsigned int  reserved          : 12; /* bit[4-15] : ������ */
        unsigned int  clkdivmasken      : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                             ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV24_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV24_div_isp_snclk_START      (0)
#define SOC_CRGPERIPH_CLKDIV24_div_isp_snclk_END        (1)
#define SOC_CRGPERIPH_CLKDIV24_gt_clk_isp_snclk_START   (2)
#define SOC_CRGPERIPH_CLKDIV24_gt_clk_isp_snclk_END     (2)
#define SOC_CRGPERIPH_CLKDIV24_sel_clk_isp_snclk_START  (3)
#define SOC_CRGPERIPH_CLKDIV24_sel_clk_isp_snclk_END    (3)
#define SOC_CRGPERIPH_CLKDIV24_clkdivmasken_START       (16)
#define SOC_CRGPERIPH_CLKDIV24_clkdivmasken_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CLKDIV25_UNION
 �ṹ˵��  : CLKDIV25 �Ĵ����ṹ���塣��ַƫ����:0x10C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ʱ�ӷ�Ƶ�ȿ��ƼĴ���25��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved     : 16; /* bit[0-15] : ������ */
        unsigned int  clkdivmasken : 16; /* bit[16-31]: clkdivÿ������λ��ʹ��λ��
                                                        ֻ�е�clkdivmasken��Ӧ�ı���λΪ1'b1��clkdiv��Ӧ�ı���λ�������á�Clkdivmasken[0]����clkdiv[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_CLKDIV25_UNION;
#endif
#define SOC_CRGPERIPH_CLKDIV25_clkdivmasken_START  (16)
#define SOC_CRGPERIPH_CLKDIV25_clkdivmasken_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PER_STAT0_UNION
 �ṹ˵��  : PER_STAT0 �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PER_STAT0_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PER_STAT1_UNION
 �ṹ˵��  : PER_STAT1 �Ĵ����ṹ���塣��ַƫ����:0x114����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bootmode               : 2;  /* bit[0-1] : ����ģʽ����λ����bit���ɹ̶���0����
                                                                 2'bx0��bootrom����-USB���أ�
                                                                 2'bx1������bootrom����-eMMC������ */
        unsigned int  sc_noc_aobus_idle_flag : 1;  /* bit[2]   : aobus idle ָʾ�źţ�
                                                                 0��busy��
                                                                 1��idle�� */
        unsigned int  isp_to_ddrc_dfs_en     : 1;  /* bit[3]   : ISP�Ƿ�ͬ��DDRC�л�Ƶ��,ÿ��DDR��Ҫ��Ƶʱ��LPM3���ѯ���ź�״̬�������Ƿ�ִ�б���DDR��Ƶ��
                                                                 1:ͬ��;
                                                                 0:��ͬ��. */
        unsigned int  reserved               : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PER_STAT1_UNION;
#endif
#define SOC_CRGPERIPH_PER_STAT1_bootmode_START                (0)
#define SOC_CRGPERIPH_PER_STAT1_bootmode_END                  (1)
#define SOC_CRGPERIPH_PER_STAT1_sc_noc_aobus_idle_flag_START  (2)
#define SOC_CRGPERIPH_PER_STAT1_sc_noc_aobus_idle_flag_END    (2)
#define SOC_CRGPERIPH_PER_STAT1_isp_to_ddrc_dfs_en_START      (3)
#define SOC_CRGPERIPH_PER_STAT1_isp_to_ddrc_dfs_en_END        (3)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PER_STAT2_UNION
 �ṹ˵��  : PER_STAT2 �Ĵ����ṹ���塣��ַƫ����:0x118����ֵ:0x00004000�����:32
 �Ĵ���˵��: ����״̬�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  swdone_clk_aclk_ddrc       : 1;  /* bit[0]    :  */
        unsigned int  swdone_clk_sysbus_div      : 1;  /* bit[1]    : DIV��Ƶ���л��Ƿ����ָʾ�źţ�
                                                                      0��δ��ɣ�
                                                                      1����ɣ� */
        unsigned int  swdone_clk_lpmcu_div       : 1;  /* bit[2]    :  */
        unsigned int  swdone_clk_vcodecbus_div   : 1;  /* bit[3]    :  */
        unsigned int  swdone_clk_vivobus_div     : 1;  /* bit[4]    :  */
        unsigned int  swdone_clk_ddrcfg          : 1;  /* bit[5]    :  */
        unsigned int  swdone_clk_ldi0_div        : 1;  /* bit[6]    :  */
        unsigned int  swdone_clk_ldi1_div        : 1;  /* bit[7]    :  */
        unsigned int  swdone_clk_edc0_div        : 1;  /* bit[8]    :  */
        unsigned int  swdone_clk_ddrsys          : 1;  /* bit[9]    :  */
        unsigned int  swdone_clk_ispfunc1_div    : 1;  /* bit[10]   :  */
        unsigned int  swdone_clk_ispfunc2_div    : 1;  /* bit[11]   :  */
        unsigned int  swdone_clk_vdec_div        : 1;  /* bit[12]   :  */
        unsigned int  swdone_clk_venc_div        : 1;  /* bit[13]   :  */
        unsigned int  ddr_pll_sw_ack             : 4;  /* bit[14-17]: ddr pllʱ��Դ�л�ack�źţ� 
                                                                      4'b0001:PPLL0��
                                                                      4'b0010:PPLL1��
                                                                      4'b0100:PPLL2��
                                                                      4'b1000:PPLL3�� */
        unsigned int  swdone_clk_sd_div          : 1;  /* bit[18]   :  */
        unsigned int  swdone_clk_sdio0_div       : 1;  /* bit[19]   :  */
        unsigned int  swdone_clk_sdio1_div       : 1;  /* bit[20]   :  */
        unsigned int  swdone_clk_a53hpm_div      : 1;  /* bit[21]   :  */
        unsigned int  swdone_clk_emmc0_div       : 1;  /* bit[22]   :  */
        unsigned int  swdone_clk_aomm_div        : 1;  /* bit[23]   :  */
        unsigned int  swdone_clk_isp_snclk_div   : 1;  /* bit[24]   :  */
        unsigned int  swdone_clk_uarth_div       : 1;  /* bit[25]   :  */
        unsigned int  swdone_clk_uartl_div       : 1;  /* bit[26]   :  */
        unsigned int  swdone_clk_spi_div         : 1;  /* bit[27]   :  */
        unsigned int  swdone_clk_i2c_div         : 1;  /* bit[28]   :  */
        unsigned int  swdone_clk_modem_mcpu_div  : 1;  /* bit[29]   :  */
        unsigned int  swdone_clk_modem_bbe16_div : 1;  /* bit[30]   :  */
        unsigned int  swdone_clk_out0_div1       : 1;  /* bit[31]   :  */
    } reg;
} SOC_CRGPERIPH_PER_STAT2_UNION;
#endif
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_aclk_ddrc_START        (0)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_aclk_ddrc_END          (0)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sysbus_div_START       (1)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sysbus_div_END         (1)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_lpmcu_div_START        (2)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_lpmcu_div_END          (2)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vcodecbus_div_START    (3)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vcodecbus_div_END      (3)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vivobus_div_START      (4)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vivobus_div_END        (4)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ddrcfg_START           (5)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ddrcfg_END             (5)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ldi0_div_START         (6)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ldi0_div_END           (6)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ldi1_div_START         (7)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ldi1_div_END           (7)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_edc0_div_START         (8)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_edc0_div_END           (8)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ddrsys_START           (9)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ddrsys_END             (9)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ispfunc1_div_START     (10)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ispfunc1_div_END       (10)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ispfunc2_div_START     (11)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_ispfunc2_div_END       (11)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vdec_div_START         (12)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_vdec_div_END           (12)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_venc_div_START         (13)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_venc_div_END           (13)
#define SOC_CRGPERIPH_PER_STAT2_ddr_pll_sw_ack_START              (14)
#define SOC_CRGPERIPH_PER_STAT2_ddr_pll_sw_ack_END                (17)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sd_div_START           (18)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sd_div_END             (18)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sdio0_div_START        (19)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sdio0_div_END          (19)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sdio1_div_START        (20)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_sdio1_div_END          (20)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_a53hpm_div_START       (21)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_a53hpm_div_END         (21)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_emmc0_div_START        (22)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_emmc0_div_END          (22)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_aomm_div_START         (23)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_aomm_div_END           (23)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_isp_snclk_div_START    (24)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_isp_snclk_div_END      (24)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_uarth_div_START        (25)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_uarth_div_END          (25)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_uartl_div_START        (26)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_uartl_div_END          (26)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_spi_div_START          (27)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_spi_div_END            (27)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_i2c_div_START          (28)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_i2c_div_END            (28)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_modem_mcpu_div_START   (29)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_modem_mcpu_div_END     (29)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_modem_bbe16_div_START  (30)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_modem_bbe16_div_END    (30)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_out0_div1_START        (31)
#define SOC_CRGPERIPH_PER_STAT2_swdone_clk_out0_div1_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PER_STAT3_UNION
 �ṹ˵��  : PER_STAT3 �Ĵ����ṹ���塣��ַƫ����:0x11C����ֵ:0x15211100�����:32
 �Ĵ���˵��: ����״̬�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  swdone_clk_out1_div1           : 1;  /* bit[0]    : DIV��Ƶ���л��Ƿ����ָʾ�źţ�
                                                                          0��δ��ɣ�
                                                                          1����ɣ� */
        unsigned int  swdone_clk_cfgbus_div          : 1;  /* bit[1]    : DIV��Ƶ���л��Ƿ����ָʾ�źţ�
                                                                          0��δ��ɣ�
                                                                          1����ɣ� */
        unsigned int  swdone_clk_dbgsechsic_bus_div  : 1;  /* bit[2]    : DIV��Ƶ���л��Ƿ����ָʾ�źţ�
                                                                          0��δ��ɣ�
                                                                          1����ɣ� */
        unsigned int  swdone_clk_modem_bbe16_tdl_div : 1;  /* bit[3]    : DIV��Ƶ���л��Ƿ����ָʾ�źţ�
                                                                          0��δ��ɣ�
                                                                          1����ɣ� */
        unsigned int  swdone_clk_dmabus_div          : 1;  /* bit[4]    : DIV��Ƶ���л��Ƿ����ָʾ�źţ�
                                                                          0��δ��ɣ�
                                                                          1����ɣ� */
        unsigned int  swdone_clk_ispfunc             : 1;  /* bit[5]    : clk_ispfunc �л�ʱ��Դָʾ�źţ�
                                                                          0���л���clk_isp_func2(480/360)��
                                                                          1���л���clk_isp_func1(400/320)�� */
        unsigned int  swdone_clk_slimbus_div         : 1;  /* bit[6]    : DIV��Ƶ���л��Ƿ����ָʾ�źţ�
                                                                          0��δ��ɣ�
                                                                          1����ɣ� */
        unsigned int  swdone_clk_ispa7_div           : 1;  /* bit[7]    : DIV��Ƶ���л��Ƿ����ָʾ�źţ�
                                                                          0��δ��ɣ�
                                                                          1����ɣ� */
        unsigned int  ldi0_pll_sw_ack                : 4;  /* bit[8-11] : ldi0 pllʱ��Դ�л�ack�źţ� 
                                                                          4'b0001:PPLL0��
                                                                          4'b0010:PPLL2��
                                                                          4'b0100:PPLL1��
                                                                          4'b1000:PPLL3�� */
        unsigned int  ldi1_pll_sw_ack                : 4;  /* bit[12-15]: ldi1 pllʱ��Դ�л�ack�źţ� 
                                                                          4'b0001:PPLL0��
                                                                          4'b0010:PPLL2��
                                                                          4'b0100:PPLL1��
                                                                          4'b1000:PPLL3�� */
        unsigned int  mcpu_pll_sw_ack                : 4;  /* bit[16-19]: modem cpu pllʱ��Դ�л�ack�źţ� 
                                                                          4'b0001��PPLL4��
                                                                          4'b0010��PPLL5��
                                                                          4'b0100��PPLL0��
                                                                          4'b1000��PPLL3�� */
        unsigned int  bbe16_pll_sw_ack               : 4;  /* bit[20-23]: modem bbe16 pllʱ��Դ�л�ack�źţ� 
                                                                          4'b0001��PPLL4��
                                                                          4'b0010��PPLL5��
                                                                          4'b0100��PPLL0��
                                                                          4'b1000��PPLL3�� */
        unsigned int  ddrclksw2sys                   : 1;  /* bit[24]   : ddrc clk�л�������ʱ��ָʾ������Ч�� */
        unsigned int  ddrclksw2pll                   : 1;  /* bit[25]   : ddrc clk�л���PLLʱ��ָʾ������Ч�� */
        unsigned int  sysbusclksw2sys                : 1;  /* bit[26]   : sysbus clk�л�������ʱ��ָʾ������Ч�� */
        unsigned int  sysbusclksw2pll                : 1;  /* bit[27]   : sysbus clk�л���PLLʱ��ָʾ������Ч�� */
        unsigned int  lpmcuclksw2sys                 : 1;  /* bit[28]   : lpmcu clk�л�������ʱ��ָʾ������Ч�� */
        unsigned int  lpmcuclksw2pll                 : 1;  /* bit[29]   : lpmcu clk�л���PLLʱ��ָʾ������Ч�� */
        unsigned int  swdone_clk_cssysdbg_div        : 1;  /* bit[30]   : DIV��Ƶ���л��Ƿ����ָʾ�źţ�
                                                                          0��δ��ɣ�
                                                                          1����ɣ� */
        unsigned int  swdone_clk_ivp32dsp_core_div   : 1;  /* bit[31]   : DIV��Ƶ���л��Ƿ����ָʾ�źţ�
                                                                          0��δ��ɣ�
                                                                          1����ɣ� */
    } reg;
} SOC_CRGPERIPH_PER_STAT3_UNION;
#endif
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_out1_div1_START            (0)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_out1_div1_END              (0)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_cfgbus_div_START           (1)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_cfgbus_div_END             (1)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_dbgsechsic_bus_div_START   (2)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_dbgsechsic_bus_div_END     (2)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_modem_bbe16_tdl_div_START  (3)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_modem_bbe16_tdl_div_END    (3)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_dmabus_div_START           (4)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_dmabus_div_END             (4)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ispfunc_START              (5)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ispfunc_END                (5)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_slimbus_div_START          (6)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_slimbus_div_END            (6)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ispa7_div_START            (7)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ispa7_div_END              (7)
#define SOC_CRGPERIPH_PER_STAT3_ldi0_pll_sw_ack_START                 (8)
#define SOC_CRGPERIPH_PER_STAT3_ldi0_pll_sw_ack_END                   (11)
#define SOC_CRGPERIPH_PER_STAT3_ldi1_pll_sw_ack_START                 (12)
#define SOC_CRGPERIPH_PER_STAT3_ldi1_pll_sw_ack_END                   (15)
#define SOC_CRGPERIPH_PER_STAT3_mcpu_pll_sw_ack_START                 (16)
#define SOC_CRGPERIPH_PER_STAT3_mcpu_pll_sw_ack_END                   (19)
#define SOC_CRGPERIPH_PER_STAT3_bbe16_pll_sw_ack_START                (20)
#define SOC_CRGPERIPH_PER_STAT3_bbe16_pll_sw_ack_END                  (23)
#define SOC_CRGPERIPH_PER_STAT3_ddrclksw2sys_START                    (24)
#define SOC_CRGPERIPH_PER_STAT3_ddrclksw2sys_END                      (24)
#define SOC_CRGPERIPH_PER_STAT3_ddrclksw2pll_START                    (25)
#define SOC_CRGPERIPH_PER_STAT3_ddrclksw2pll_END                      (25)
#define SOC_CRGPERIPH_PER_STAT3_sysbusclksw2sys_START                 (26)
#define SOC_CRGPERIPH_PER_STAT3_sysbusclksw2sys_END                   (26)
#define SOC_CRGPERIPH_PER_STAT3_sysbusclksw2pll_START                 (27)
#define SOC_CRGPERIPH_PER_STAT3_sysbusclksw2pll_END                   (27)
#define SOC_CRGPERIPH_PER_STAT3_lpmcuclksw2sys_START                  (28)
#define SOC_CRGPERIPH_PER_STAT3_lpmcuclksw2sys_END                    (28)
#define SOC_CRGPERIPH_PER_STAT3_lpmcuclksw2pll_START                  (29)
#define SOC_CRGPERIPH_PER_STAT3_lpmcuclksw2pll_END                    (29)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_cssysdbg_div_START         (30)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_cssysdbg_div_END           (30)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ivp32dsp_core_div_START    (31)
#define SOC_CRGPERIPH_PER_STAT3_swdone_clk_ivp32dsp_core_div_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERCTRL0_UNION
 �ṹ˵��  : PERCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x120����ֵ:0x000001FF�����:32
 �Ĵ���˵��: ������ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cactive_cci400_cfgcnt : 8;  /* bit[0-7] : CCI-400Ӳ���Զ��ſصȴ�ʱ���������� */
        unsigned int  gt_clk_cci400_bypass  : 1;  /* bit[8]   : CCI-400ʱ���ſ�bypass���ƣ�
                                                                0��bypass��Ч��ʱ�ӿ�ͨ��Ӳ���Զ��ſأ�
                                                                1��bypass��Ч��ʱ�Ӳ��ſأ� */
        unsigned int  reserved              : 23; /* bit[9-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERCTRL0_UNION;
#endif
#define SOC_CRGPERIPH_PERCTRL0_cactive_cci400_cfgcnt_START  (0)
#define SOC_CRGPERIPH_PERCTRL0_cactive_cci400_cfgcnt_END    (7)
#define SOC_CRGPERIPH_PERCTRL0_gt_clk_cci400_bypass_START   (8)
#define SOC_CRGPERIPH_PERCTRL0_gt_clk_cci400_bypass_END     (8)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERCTRL1_UNION
 �ṹ˵��  : PERCTRL1 �Ĵ����ṹ���塣��ַƫ����:0x124����ֵ:0x0000000F�����:32
 �Ĵ���˵��: ������ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_auto_clk_cci2sysbus_async_bypass : 1;  /* bit[0]   : �Ƿ�bypass cci2sysbus�첽��S��ʱ���Զ��ſأ�
                                                                              0����bypass��
                                                                              1��bypass */
        unsigned int  gt_auto_clk_i2c34_bypass            : 1;  /* bit[1]   : �Ƿ�bypass I2C34�첽��S��ʱ���Զ��ſأ�
                                                                              0����bypass��
                                                                              1��bypass */
        unsigned int  gt_auto_clk_uart025_bypass          : 1;  /* bit[2]   : �Ƿ�bypass UART025�첽��S��ʱ���Զ��ſأ�
                                                                              0����bypass��
                                                                              1��bypass */
        unsigned int  gt_auto_clk_uart14_bypass           : 1;  /* bit[3]   : �Ƿ�bypass UART14�첽��S��ʱ���Զ��ſأ�
                                                                              0����bypass��
                                                                              1��bypass */
        unsigned int  reserved                            : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERCTRL1_UNION;
#endif
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_cci2sysbus_async_bypass_START  (0)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_cci2sysbus_async_bypass_END    (0)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_i2c34_bypass_START             (1)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_i2c34_bypass_END               (1)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_uart025_bypass_START           (2)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_uart025_bypass_END             (2)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_uart14_bypass_START            (3)
#define SOC_CRGPERIPH_PERCTRL1_gt_auto_clk_uart14_bypass_END              (3)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERCTRL2_UNION
 �ṹ˵��  : PERCTRL2 �Ĵ����ṹ���塣��ַƫ����:0x128����ֵ:0x7FE337FE�����:32
 �Ĵ���˵��: ������ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pclkdbg_sel                    : 1;  /* bit[0]    : debug APB����ʱ��Ƶ�ʱ�ѡ���źţ������debugAPB_trace_clk����Ĭ��1:2��
                                                                          0��1:2
                                                                          1��1:4  */
        unsigned int  pclkdbg_clkoff_sys             : 1;  /* bit[1]    : top_cssys �ڲ�ʹ�õ�PCLKDBGʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ1 ��
                                                                          0���ر�PCLKDBG
                                                                          1����PCLKDBG */
        unsigned int  pclkdbg_to_a53cfg_clkoff_sys_0 : 1;  /* bit[2]    : �͸�A53 cluster0 CRG��pclkdbgʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ1 ��
                                                                          0���ر�PCLKDBG_TO_A53CRG
                                                                          1����PCLKDBG_TO_A53CRG */
        unsigned int  pclkdbg_to_a53cfg_clkoff_sys_1 : 1;  /* bit[3]    : �͸�A53 cluster1 CRG��pclkdbgʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ1 ��
                                                                          0���ر�PCLKDBG_TO_A57CRG
                                                                          1����PCLKDBG_TO_A57CRG */
        unsigned int  pclkdbg_to_iomcu_clkoff_sys    : 1;  /* bit[4]    : �͸�IOMCU��pclkdbgʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ1 ��
                                                                          0���ر�PCLKDBG_TO_IOMCU
                                                                          1����PCLKDBG_TO_IOMCU */
        unsigned int  pclkdbg_to_lpmcu_clkoff_sys    : 1;  /* bit[5]    : �͸�LPMCU��pclkdbgʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ1 ��
                                                                          0���ر�PCLKDBG_TO_LPMCU
                                                                          1����PCLKDBG_TO_LPMCU */
        unsigned int  traceclkin_clkoff_sys          : 1;  /* bit[6]    : TRACECLKINʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ1 ��
                                                                          0���ر�TRACECLKIN
                                                                          1����TRACELKIN */
        unsigned int  atclkoff_sys                   : 1;  /* bit[7]    : ATCLKʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ1��
                                                                          0���ر�ATCLK
                                                                          1����ATCLK */
        unsigned int  atclk_to_iomcu_clkoff_sys      : 1;  /* bit[8]    : ATCLK_TO_IOMCU Gʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ1 ��
                                                                          0���ر�ATCLK_TO_IOMCU
                                                                          1����ATCLK_TO_IOMCU */
        unsigned int  atclk_to_a53crg_clkoff_sys_0   : 1;  /* bit[9]    : ATCLK_TO_A53 cluster0 CRGʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ1 ��
                                                                          0���ر�ATCLK_TO_A57CRG
                                                                          1����ATCLK_TO_A57CRG */
        unsigned int  atclk_to_a53crg_clkoff_sys_1   : 1;  /* bit[10]   : ATCLK_TO_A53 cluster1 CRGʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ1 ��
                                                                          0���ر�ATCLK_TO_A53CRG
                                                                          1����ATCLK_TO_A53CRG */
        unsigned int  cs_soft_rst_req                : 1;  /* bit[11]   : top_cssys�����λ���󣬸�λ�������ʱ������16��PCLKDBGʱ�����ڡ�
                                                                          0��������Ч��
                                                                          1��������Ч�� */
        unsigned int  traceclkin_sel                 : 2;  /* bit[12-13]: trace port����ʱ��Ƶ�ʱ�ѡ���źţ������debugAPB_trace_clk����Ĭ��1:4����ʹ�ó����̶�Ϊ1:4��
                                                                          00��1:1
                                                                          01��1:2
                                                                          10��1:3
                                                                          11��1:4 */
        unsigned int  reserved                       : 1;  /* bit[14]   : ������ */
        unsigned int  cs_cssys_rst_req               : 1;  /* bit[15]   : �͸���top_cssys ��λ�����źţ��ϵ�Ĭ��Ϊ0 ��
                                                                          0��������Ч��
                                                                          1��������Ч�� */
        unsigned int  atclk_to_modem_clkoff_sys      : 1;  /* bit[16]   : ATCLK_TO_MODEMCRGʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ1 ��
                                                                          0���ر�ATCLK_TO_MODEMCRG
                                                                          1����ATCLK_TO_MODEMCRG */
        unsigned int  pclkdbg_to_modem_clkoff_sys    : 1;  /* bit[17]   : �͸�MODEMCRG��pclkdbgʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ1 ��
                                                                          0���ر�PCLKDBG_TO_MODEMCRG
                                                                          1����PCLKDBG_TO_MODEMCRG */
        unsigned int  modem_cssys_rst_req            : 1;  /* bit[18]   : �͸�MODEM��cssys ��λ�����źţ��ϵ�Ĭ��Ϊ0 ��
                                                                          0��������Ч��
                                                                          1��������Ч�� */
        unsigned int  asp_cssys_rst_req              : 1;  /* bit[19]   : �͸�ASP��cssys ��λ�����źţ��ϵ�Ĭ��Ϊ0 ��
                                                                          0��������Ч��
                                                                          1��������Ч�� */
        unsigned int  atclk_to_asp_clkoff_sys        : 1;  /* bit[20]   : �͸�ASPCRG ��ATCLK_TO_ASPCRGʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ0(Austin ASP 20140825ɾ��trace����) ��
                                                                          0���ر�ATCLK_TO_ASPCRG
                                                                          1����ATCLK_TO_ASPCRG */
        unsigned int  pclkdbg_to_asp_clkoff_sys      : 1;  /* bit[21]   : �͸�ASPCRG��pclkdbgʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ1 ��
                                                                          0���ر�PCLKDBG_TO_ASPCRG
                                                                          1����PCLKDBG_TO_ASPCRG */
        unsigned int  time_stamp_clk_sel             : 3;  /* bit[22-24]: ��Ƶ�����ã�(�������4��Ƶ)
                                                                          3'h0:2��Ƶ��
                                                                          3'h1:4��Ƶ��
                                                                          3'h2:6��Ƶ��
                                                                          3'h3:8��Ƶ��
                                                                          3'h4:10��Ƶ��
                                                                          3'h5:12��Ƶ��
                                                                          3'h6:14��Ƶ��
                                                                          3'h7:16��Ƶ�� */
        unsigned int  gt_clk_cssys_atclk             : 1;  /* bit[25]   : cssys ATB internal��atclkʱ���ſ�
                                                                          0��ʱ�ӹر�
                                                                          1��ʱ�ӿ��� */
        unsigned int  ip_rst_cssys_atclk             : 1;  /* bit[26]   : cssys ATB internal��atclkʱ�Ӷ�Ӧ�ĸ�λ����
                                                                          0����λ��Ч
                                                                          1����λ���� */
        unsigned int  gt_clk_time_stamp              : 1;  /* bit[27]   : time stamp��ʱ���ſ�
                                                                          0��ʱ�ӹر�
                                                                          1��ʱ�ӿ��� */
        unsigned int  ip_rst_time_stamp              : 1;  /* bit[28]   : time stamp�ĸ�λ����
                                                                          0����λ��Ч
                                                                          1����λ���� */
        unsigned int  atclk_to_iapa7_clkoff_sys      : 1;  /* bit[29]   : ATCLK_TO_ISPA7ʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ1 ��
                                                                          0���ر�ATCLK_TO_IAPA7
                                                                          1����ATCLK_TO_IAPA7 */
        unsigned int  pclkdbg_to_iapa7_clkoff_sys    : 1;  /* bit[30]   : PCLKDBG_TO_ISPA7ʱ��ʹ��ϵͳ���ƣ��ϵ�Ĭ��Ϊ1 ��
                                                                          0���ر�PCLKDBG_TO_ISPA7
                                                                          1����PCLKDBG_TO_ISPA7 */
        unsigned int  ispa7_mask                     : 1;  /* bit[31]   : ISPA7 ��ʹ��λ��
                                                                          ����bitΪ1'b1��[30:29]��ֵ���ܱ���д��ͬʱ[28:0]��ֵ���ܱ���д������bitΪ1'b0��[30:29]��ֵ���ܱ���д��ͬʱ[28:0]��ֵ�ܱ���д�� */
    } reg;
} SOC_CRGPERIPH_PERCTRL2_UNION;
#endif
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_sel_START                     (0)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_sel_END                       (0)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_clkoff_sys_START              (1)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_clkoff_sys_END                (1)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_a53cfg_clkoff_sys_0_START  (2)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_a53cfg_clkoff_sys_0_END    (2)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_a53cfg_clkoff_sys_1_START  (3)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_a53cfg_clkoff_sys_1_END    (3)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_iomcu_clkoff_sys_START     (4)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_iomcu_clkoff_sys_END       (4)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_lpmcu_clkoff_sys_START     (5)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_lpmcu_clkoff_sys_END       (5)
#define SOC_CRGPERIPH_PERCTRL2_traceclkin_clkoff_sys_START           (6)
#define SOC_CRGPERIPH_PERCTRL2_traceclkin_clkoff_sys_END             (6)
#define SOC_CRGPERIPH_PERCTRL2_atclkoff_sys_START                    (7)
#define SOC_CRGPERIPH_PERCTRL2_atclkoff_sys_END                      (7)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_iomcu_clkoff_sys_START       (8)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_iomcu_clkoff_sys_END         (8)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_a53crg_clkoff_sys_0_START    (9)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_a53crg_clkoff_sys_0_END      (9)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_a53crg_clkoff_sys_1_START    (10)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_a53crg_clkoff_sys_1_END      (10)
#define SOC_CRGPERIPH_PERCTRL2_cs_soft_rst_req_START                 (11)
#define SOC_CRGPERIPH_PERCTRL2_cs_soft_rst_req_END                   (11)
#define SOC_CRGPERIPH_PERCTRL2_traceclkin_sel_START                  (12)
#define SOC_CRGPERIPH_PERCTRL2_traceclkin_sel_END                    (13)
#define SOC_CRGPERIPH_PERCTRL2_cs_cssys_rst_req_START                (15)
#define SOC_CRGPERIPH_PERCTRL2_cs_cssys_rst_req_END                  (15)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_modem_clkoff_sys_START       (16)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_modem_clkoff_sys_END         (16)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_modem_clkoff_sys_START     (17)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_modem_clkoff_sys_END       (17)
#define SOC_CRGPERIPH_PERCTRL2_modem_cssys_rst_req_START             (18)
#define SOC_CRGPERIPH_PERCTRL2_modem_cssys_rst_req_END               (18)
#define SOC_CRGPERIPH_PERCTRL2_asp_cssys_rst_req_START               (19)
#define SOC_CRGPERIPH_PERCTRL2_asp_cssys_rst_req_END                 (19)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_asp_clkoff_sys_START         (20)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_asp_clkoff_sys_END           (20)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_asp_clkoff_sys_START       (21)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_asp_clkoff_sys_END         (21)
#define SOC_CRGPERIPH_PERCTRL2_time_stamp_clk_sel_START              (22)
#define SOC_CRGPERIPH_PERCTRL2_time_stamp_clk_sel_END                (24)
#define SOC_CRGPERIPH_PERCTRL2_gt_clk_cssys_atclk_START              (25)
#define SOC_CRGPERIPH_PERCTRL2_gt_clk_cssys_atclk_END                (25)
#define SOC_CRGPERIPH_PERCTRL2_ip_rst_cssys_atclk_START              (26)
#define SOC_CRGPERIPH_PERCTRL2_ip_rst_cssys_atclk_END                (26)
#define SOC_CRGPERIPH_PERCTRL2_gt_clk_time_stamp_START               (27)
#define SOC_CRGPERIPH_PERCTRL2_gt_clk_time_stamp_END                 (27)
#define SOC_CRGPERIPH_PERCTRL2_ip_rst_time_stamp_START               (28)
#define SOC_CRGPERIPH_PERCTRL2_ip_rst_time_stamp_END                 (28)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_iapa7_clkoff_sys_START       (29)
#define SOC_CRGPERIPH_PERCTRL2_atclk_to_iapa7_clkoff_sys_END         (29)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_iapa7_clkoff_sys_START     (30)
#define SOC_CRGPERIPH_PERCTRL2_pclkdbg_to_iapa7_clkoff_sys_END       (30)
#define SOC_CRGPERIPH_PERCTRL2_ispa7_mask_START                      (31)
#define SOC_CRGPERIPH_PERCTRL2_ispa7_mask_END                        (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERCTRL3_UNION
 �ṹ˵��  : PERCTRL3 �Ĵ����ṹ���塣��ַƫ����:0x12C����ֵ:0x00001001�����:32
 �Ĵ���˵��: ������ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  noc_timeout_en    : 1;  /* bit[0]    : NOC timeout counterʹ�ܿ��ƣ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned int  reserved_0        : 5;  /* bit[1-5]  : ������ */
        unsigned int  mem_ctrl_pgt_lpm3 : 6;  /* bit[6-11] : LP_RAM��memory�͹��Ŀ����źš�ÿ3-bitΪһ�飬����Ӧ16KB RAM���Ӹ�λ����λ�ֱ��Ӧ��SD��DSLP��SLP��
                                                             bit[5:3]:tcm_ram1��Ĭ��ֵ3'b000;
                                                             bit[2:0]:tcm_ram0��Ĭ��ֵ3'b000; */
        unsigned int  mcpu_fiq_n        : 1;  /* bit[12]   : MCPU FIQ �жϣ�����Ч�� */
        unsigned int  reserved_1        : 19; /* bit[13-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERCTRL3_UNION;
#endif
#define SOC_CRGPERIPH_PERCTRL3_noc_timeout_en_START     (0)
#define SOC_CRGPERIPH_PERCTRL3_noc_timeout_en_END       (0)
#define SOC_CRGPERIPH_PERCTRL3_mem_ctrl_pgt_lpm3_START  (6)
#define SOC_CRGPERIPH_PERCTRL3_mem_ctrl_pgt_lpm3_END    (11)
#define SOC_CRGPERIPH_PERCTRL3_mcpu_fiq_n_START         (12)
#define SOC_CRGPERIPH_PERCTRL3_mcpu_fiq_n_END           (12)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERCTRL4_UNION
 �ṹ˵��  : PERCTRL4 �Ĵ����ṹ���塣��ַƫ����:0x130����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  acpu_ipf_clk_en : 1;  /* bit[0]   : modem��IPF�ſؿ����ź� */
        unsigned int  reserved        : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERCTRL4_UNION;
#endif
#define SOC_CRGPERIPH_PERCTRL4_acpu_ipf_clk_en_START  (0)
#define SOC_CRGPERIPH_PERCTRL4_acpu_ipf_clk_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERCTRL5_UNION
 �ṹ˵��  : PERCTRL5 �Ĵ����ṹ���塣��ַƫ����:0x134����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERCTRL5_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERCTRL6_UNION
 �ṹ˵��  : PERCTRL6 �Ĵ����ṹ���塣��ַƫ����:0x138����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ƼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERCTRL6_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERTIMECTRL_UNION
 �ṹ˵��  : PERTIMECTRL �Ĵ����ṹ���塣��ַƫ����:0x140����ֵ:0x000C0000�����:32
 �Ĵ���˵��: ����TIME���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timeren18sel   : 1;  /* bit[0]    : Timer18ʱ��ʹ�ܲο�ʱ��ѡ��
                                                          0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                          1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren18ov    : 1;  /* bit[1]    : Timer18ʱ��ʹ�ܿ��ơ�
                                                          0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren18sel]ָ����
                                                          1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren19sel   : 1;  /* bit[2]    : Timer19ʱ��ʹ�ܲο�ʱ��ѡ��
                                                          0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                          1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren19ov    : 1;  /* bit[3]    : Timer19ʱ��ʹ�ܿ��ơ�
                                                          0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren19sel]ָ����
                                                          1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren20sel   : 1;  /* bit[4]    : Timer20ʱ��ʹ�ܲο�ʱ��ѡ��
                                                          0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                          1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren20ov    : 1;  /* bit[5]    : Timer20ʱ��ʹ�ܿ��ơ�
                                                          0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren10sel]ָ����
                                                          1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren21sel   : 1;  /* bit[6]    : Timer21ʱ��ʹ�ܲο�ʱ��ѡ��
                                                          0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                          1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren21ov    : 1;  /* bit[7]    : Timer21ʱ��ʹ�ܿ��ơ�
                                                          0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren21sel]ָ����
                                                          1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren22sel   : 1;  /* bit[8]    : Timer22ʱ��ʹ�ܲο�ʱ��ѡ��
                                                          0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                          1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren22ov    : 1;  /* bit[9]    : Timer22ʱ��ʹ�ܿ��ơ�
                                                          0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren12sel]ָ����
                                                          1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren23sel   : 1;  /* bit[10]   : Timer23ʱ��ʹ�ܲο�ʱ��ѡ��
                                                          0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                          1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren23ov    : 1;  /* bit[11]   : Timer23ʱ��ʹ�ܿ��ơ�
                                                          0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren23sel]ָ����
                                                          1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren24sel   : 1;  /* bit[12]   : Timer24ʱ��ʹ�ܲο�ʱ��ѡ��
                                                          0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                          1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren24ov    : 1;  /* bit[13]   : Timer24ʱ��ʹ�ܿ��ơ�
                                                          0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren24sel]ָ����
                                                          1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  timeren25sel   : 1;  /* bit[14]   : Timer25ʱ��ʹ�ܲο�ʱ��ѡ��
                                                          0��ѡ��32.768kHz˯��ʱ����Ϊ�ο�ʱ�Ӽ�����
                                                          1��ѡ��TCXOʱ�ӵ�4��Ƶʱ����Ϊ�ο�ʱ�Ӽ����� */
        unsigned int  timeren25ov    : 1;  /* bit[15]   : Timer25ʱ��ʹ�ܿ��ơ�
                                                          0��ʹ���ź�ͨ�������ο�ʱ�ӵõ����ο�ʱ�ӵ�ѡ����[timeren25sel]ָ����
                                                          1��ʹ���źű�ǿ�����ߡ� */
        unsigned int  wdog1enov      : 1;  /* bit[16]   : ���Ź�ʱ��ʹ�ܿ��ơ�
                                                          0��ʹ���ɲ���32.768kHzʱ�Ӳ�����
                                                          1��ʹ�ܱ�ǿ�����ߡ� */
        unsigned int  wdog0enov      : 1;  /* bit[17]   : ���Ź�ʱ��ʹ�ܿ��ơ�
                                                          0��ʹ���ɲ���32.768kHzʱ�Ӳ�����
                                                          1��ʹ�ܱ�ǿ�����ߡ� */
        unsigned int  wd0_dbgack_byp : 1;  /* bit[18]   : 0��bypass��Ч��
                                                          1��bypass��Ч�� */
        unsigned int  wd1_dbgack_byp : 1;  /* bit[19]   : 0��bypass��Ч��
                                                          1��bypass��Ч�� */
        unsigned int  reserved       : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERTIMECTRL_UNION;
#endif
#define SOC_CRGPERIPH_PERTIMECTRL_timeren18sel_START    (0)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren18sel_END      (0)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren18ov_START     (1)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren18ov_END       (1)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren19sel_START    (2)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren19sel_END      (2)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren19ov_START     (3)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren19ov_END       (3)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren20sel_START    (4)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren20sel_END      (4)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren20ov_START     (5)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren20ov_END       (5)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren21sel_START    (6)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren21sel_END      (6)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren21ov_START     (7)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren21ov_END       (7)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren22sel_START    (8)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren22sel_END      (8)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren22ov_START     (9)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren22ov_END       (9)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren23sel_START    (10)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren23sel_END      (10)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren23ov_START     (11)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren23ov_END       (11)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren24sel_START    (12)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren24sel_END      (12)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren24ov_START     (13)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren24ov_END       (13)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren25sel_START    (14)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren25sel_END      (14)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren25ov_START     (15)
#define SOC_CRGPERIPH_PERTIMECTRL_timeren25ov_END       (15)
#define SOC_CRGPERIPH_PERTIMECTRL_wdog1enov_START       (16)
#define SOC_CRGPERIPH_PERTIMECTRL_wdog1enov_END         (16)
#define SOC_CRGPERIPH_PERTIMECTRL_wdog0enov_START       (17)
#define SOC_CRGPERIPH_PERTIMECTRL_wdog0enov_END         (17)
#define SOC_CRGPERIPH_PERTIMECTRL_wd0_dbgack_byp_START  (18)
#define SOC_CRGPERIPH_PERTIMECTRL_wd0_dbgack_byp_END    (18)
#define SOC_CRGPERIPH_PERTIMECTRL_wd1_dbgack_byp_START  (19)
#define SOC_CRGPERIPH_PERTIMECTRL_wd1_dbgack_byp_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_ISOEN_UNION
 �ṹ˵��  : ISOEN �Ĵ����ṹ���塣��ַƫ����:0x144����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ϵͳISOʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispisoen         : 1;  /* bit[0]    : ISP��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  vencisoen        : 1;  /* bit[1]    : VENC��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  vdecisoen        : 1;  /* bit[2]    : VDEC��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  reserved_0       : 1;  /* bit[3]    : ������ */
        unsigned int  modemsubsysisoen : 1;  /* bit[4]    : MODEM��ϵͳ ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  g3disoen         : 1;  /* bit[5]    : G3D��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  dsssubsysisoen   : 1;  /* bit[6]    : DSS SUBSYS ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  reserved_1       : 1;  /* bit[7]    : ������ */
        unsigned int  reserved_2       : 1;  /* bit[8]    : ������ */
        unsigned int  reserved_3       : 1;  /* bit[9]    : ������ */
        unsigned int  reserved_4       : 1;  /* bit[10]   : ������ */
        unsigned int  reserved_5       : 1;  /* bit[11]   : ������ */
        unsigned int  a53_0_cor0isoen  : 1;  /* bit[12]   : A53 cluster0��ϵͳCORE0 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  a53_0_cor1isoen  : 1;  /* bit[13]   : A53 cluster0��ϵͳCORE1 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  a53_0_cor2isoen  : 1;  /* bit[14]   : A53 cluster0��ϵͳCORE2 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  a53_0_cor3isoen  : 1;  /* bit[15]   : A53 cluster0��ϵͳCORE3 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  a53isoen         : 1;  /* bit[16]   : A53��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  a53_1_cor0isoen  : 1;  /* bit[17]   : A57 cluster��ϵͳCORE0 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  a53_1_cor1isoen  : 1;  /* bit[18]   : A57 cluster��ϵͳCORE1 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  a53_1_cor2isoen  : 1;  /* bit[19]   : A57 cluster��ϵͳCORE2 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  a53_1_cor3isoen  : 1;  /* bit[20]   : A57 cluster��ϵͳCORE3 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  a57isoen         : 1;  /* bit[21]   : A57 cluster��ϵͳ ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  modemperiisoen   : 1;  /* bit[22]   : MODEM��ϵͳPERI ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  modemirmisoen    : 1;  /* bit[23]   : MODEM��ϵͳIRM ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  ivp32dspisoen    : 1;  /* bit[24]   : IVP32DSP��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܲ����� */
        unsigned int  reserved_6       : 7;  /* bit[25-31]: ������ */
    } reg;
} SOC_CRGPERIPH_ISOEN_UNION;
#endif
#define SOC_CRGPERIPH_ISOEN_ispisoen_START          (0)
#define SOC_CRGPERIPH_ISOEN_ispisoen_END            (0)
#define SOC_CRGPERIPH_ISOEN_vencisoen_START         (1)
#define SOC_CRGPERIPH_ISOEN_vencisoen_END           (1)
#define SOC_CRGPERIPH_ISOEN_vdecisoen_START         (2)
#define SOC_CRGPERIPH_ISOEN_vdecisoen_END           (2)
#define SOC_CRGPERIPH_ISOEN_modemsubsysisoen_START  (4)
#define SOC_CRGPERIPH_ISOEN_modemsubsysisoen_END    (4)
#define SOC_CRGPERIPH_ISOEN_g3disoen_START          (5)
#define SOC_CRGPERIPH_ISOEN_g3disoen_END            (5)
#define SOC_CRGPERIPH_ISOEN_dsssubsysisoen_START    (6)
#define SOC_CRGPERIPH_ISOEN_dsssubsysisoen_END      (6)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor0isoen_START   (12)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor0isoen_END     (12)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor1isoen_START   (13)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor1isoen_END     (13)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor2isoen_START   (14)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor2isoen_END     (14)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor3isoen_START   (15)
#define SOC_CRGPERIPH_ISOEN_a53_0_cor3isoen_END     (15)
#define SOC_CRGPERIPH_ISOEN_a53isoen_START          (16)
#define SOC_CRGPERIPH_ISOEN_a53isoen_END            (16)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor0isoen_START   (17)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor0isoen_END     (17)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor1isoen_START   (18)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor1isoen_END     (18)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor2isoen_START   (19)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor2isoen_END     (19)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor3isoen_START   (20)
#define SOC_CRGPERIPH_ISOEN_a53_1_cor3isoen_END     (20)
#define SOC_CRGPERIPH_ISOEN_a57isoen_START          (21)
#define SOC_CRGPERIPH_ISOEN_a57isoen_END            (21)
#define SOC_CRGPERIPH_ISOEN_modemperiisoen_START    (22)
#define SOC_CRGPERIPH_ISOEN_modemperiisoen_END      (22)
#define SOC_CRGPERIPH_ISOEN_modemirmisoen_START     (23)
#define SOC_CRGPERIPH_ISOEN_modemirmisoen_END       (23)
#define SOC_CRGPERIPH_ISOEN_ivp32dspisoen_START     (24)
#define SOC_CRGPERIPH_ISOEN_ivp32dspisoen_END       (24)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_ISODIS_UNION
 �ṹ˵��  : ISODIS �Ĵ����ṹ���塣��ַƫ����:0x148����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ϵͳISOʹ�ܳ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispisoen         : 1;  /* bit[0]    : ISP��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  vencisoen        : 1;  /* bit[1]    : VENC��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  vdecisoen        : 1;  /* bit[2]    : VDEC��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  reserved_0       : 1;  /* bit[3]    : ������ */
        unsigned int  modemsubsysisoen : 1;  /* bit[4]    : MODEM��ϵͳ ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  g3disoen         : 1;  /* bit[5]    : G3D��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  dsssubsysisoen   : 1;  /* bit[6]    : DSS SUBSYS ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  reserved_1       : 1;  /* bit[7]    : ������ */
        unsigned int  reserved_2       : 1;  /* bit[8]    : ������ */
        unsigned int  reserved_3       : 1;  /* bit[9]    : ������ */
        unsigned int  reserved_4       : 1;  /* bit[10]   : ������ */
        unsigned int  reserved_5       : 1;  /* bit[11]   : ������ */
        unsigned int  a53_0_cor0isoen  : 1;  /* bit[12]   : A53 cluster0��ϵͳCORE0 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  a53_0_cor1isoen  : 1;  /* bit[13]   : A53 cluster0��ϵͳCORE1 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  a53_0_cor2isoen  : 1;  /* bit[14]   : A53 cluster0��ϵͳCORE2 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  a53_0_cor3isoen  : 1;  /* bit[15]   : A53 cluster0��ϵͳCORE3 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  a53isoen         : 1;  /* bit[16]   : A53��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  a53_1_cor0isoen  : 1;  /* bit[17]   : A57 cluster��ϵͳCORE0 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  a53_1_cor1isoen  : 1;  /* bit[18]   : A57 cluster��ϵͳCORE1 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  a53_1_cor2isoen  : 1;  /* bit[19]   : A57 cluster��ϵͳCORE2 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  a53_1_cor3isoen  : 1;  /* bit[20]   : A57 cluster��ϵͳCORE3 ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  a57isoen         : 1;  /* bit[21]   : A57��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  modemperiisoen   : 1;  /* bit[22]   : MODEM��ϵͳPERI ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  modemirmisoen    : 1;  /* bit[23]   : MODEM��ϵͳIRM ISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  ivp32dspisoen    : 1;  /* bit[24]   : IVP32DSP��ϵͳISO��Ԫʹ�ܿ��ƣ�д1ִ��ISOʹ�ܳ��������� */
        unsigned int  reserved_6       : 7;  /* bit[25-31]: ������ */
    } reg;
} SOC_CRGPERIPH_ISODIS_UNION;
#endif
#define SOC_CRGPERIPH_ISODIS_ispisoen_START          (0)
#define SOC_CRGPERIPH_ISODIS_ispisoen_END            (0)
#define SOC_CRGPERIPH_ISODIS_vencisoen_START         (1)
#define SOC_CRGPERIPH_ISODIS_vencisoen_END           (1)
#define SOC_CRGPERIPH_ISODIS_vdecisoen_START         (2)
#define SOC_CRGPERIPH_ISODIS_vdecisoen_END           (2)
#define SOC_CRGPERIPH_ISODIS_modemsubsysisoen_START  (4)
#define SOC_CRGPERIPH_ISODIS_modemsubsysisoen_END    (4)
#define SOC_CRGPERIPH_ISODIS_g3disoen_START          (5)
#define SOC_CRGPERIPH_ISODIS_g3disoen_END            (5)
#define SOC_CRGPERIPH_ISODIS_dsssubsysisoen_START    (6)
#define SOC_CRGPERIPH_ISODIS_dsssubsysisoen_END      (6)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor0isoen_START   (12)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor0isoen_END     (12)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor1isoen_START   (13)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor1isoen_END     (13)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor2isoen_START   (14)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor2isoen_END     (14)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor3isoen_START   (15)
#define SOC_CRGPERIPH_ISODIS_a53_0_cor3isoen_END     (15)
#define SOC_CRGPERIPH_ISODIS_a53isoen_START          (16)
#define SOC_CRGPERIPH_ISODIS_a53isoen_END            (16)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor0isoen_START   (17)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor0isoen_END     (17)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor1isoen_START   (18)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor1isoen_END     (18)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor2isoen_START   (19)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor2isoen_END     (19)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor3isoen_START   (20)
#define SOC_CRGPERIPH_ISODIS_a53_1_cor3isoen_END     (20)
#define SOC_CRGPERIPH_ISODIS_a57isoen_START          (21)
#define SOC_CRGPERIPH_ISODIS_a57isoen_END            (21)
#define SOC_CRGPERIPH_ISODIS_modemperiisoen_START    (22)
#define SOC_CRGPERIPH_ISODIS_modemperiisoen_END      (22)
#define SOC_CRGPERIPH_ISODIS_modemirmisoen_START     (23)
#define SOC_CRGPERIPH_ISODIS_modemirmisoen_END       (23)
#define SOC_CRGPERIPH_ISODIS_ivp32dspisoen_START     (24)
#define SOC_CRGPERIPH_ISODIS_ivp32dspisoen_END       (24)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_ISOSTAT_UNION
 �ṹ˵��  : ISOSTAT �Ĵ����ṹ���塣��ַƫ����:0x14C����ֵ:0x01FFFFFF�����:32
 �Ĵ���˵��: ������ϵͳISOʹ��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispisoen         : 1;  /* bit[0]    : ISP��ϵͳISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  vencisoen        : 1;  /* bit[1]    : VENC��ϵͳISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  vdecisoen        : 1;  /* bit[2]    : VDEC��ϵͳISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  reserved_0       : 1;  /* bit[3]    : ������ */
        unsigned int  modemsubsysisoen : 1;  /* bit[4]    : MODEM��ϵͳ ISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  g3disoen         : 1;  /* bit[5]    : G3D��ϵͳISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  dsssubsysisoen   : 1;  /* bit[6]    : DSS SUBSYS ISOO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  reserved_1       : 1;  /* bit[7]    : ������ */
        unsigned int  reserved_2       : 1;  /* bit[8]    : ������ */
        unsigned int  reserved_3       : 1;  /* bit[9]    : ������ */
        unsigned int  reserved_4       : 1;  /* bit[10]   : ������ */
        unsigned int  reserved_5       : 1;  /* bit[11]   : ������ */
        unsigned int  a53_0_cor0isoen  : 1;  /* bit[12]   : A53 cluster0 CPU0��ϵͳISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  a53_0_cor1isoen  : 1;  /* bit[13]   : A53 cluster0 CPU1��ϵͳISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  a53_0_cor2isoen  : 1;  /* bit[14]   : A53 cluster0 CPU2��ϵͳISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  a53_0_cor3isoen  : 1;  /* bit[15]   : A53 cluster0 CPU3��ϵͳISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  a53isoen         : 1;  /* bit[16]   : A53 ��ϵͳISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  a53_1_cor0isoen  : 1;  /* bit[17]   : A57 cluster CPU0��ϵͳISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  a53_1_cor1isoen  : 1;  /* bit[18]   : A57 cluster CPU1��ϵͳISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  a53_1_cor2isoen  : 1;  /* bit[19]   : A57 cluster CPU2��ϵͳISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  a53_1_cor3isoen  : 1;  /* bit[20]   : A57 cluster CPU3��ϵͳISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  a57isoen         : 1;  /* bit[21]   : A57 ��ϵͳISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  modemperiisoen   : 1;  /* bit[22]   : MODEM��ϵͳPERI ISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  modemirmisoen    : 1;  /* bit[23]   : MODEM��ϵͳIRM ISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  ivp32dspisoen    : 1;  /* bit[24]   : IVP32DSP��ϵͳISO��Ԫʹ��״̬��0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int  reserved_6       : 7;  /* bit[25-31]: ������ */
    } reg;
} SOC_CRGPERIPH_ISOSTAT_UNION;
#endif
#define SOC_CRGPERIPH_ISOSTAT_ispisoen_START          (0)
#define SOC_CRGPERIPH_ISOSTAT_ispisoen_END            (0)
#define SOC_CRGPERIPH_ISOSTAT_vencisoen_START         (1)
#define SOC_CRGPERIPH_ISOSTAT_vencisoen_END           (1)
#define SOC_CRGPERIPH_ISOSTAT_vdecisoen_START         (2)
#define SOC_CRGPERIPH_ISOSTAT_vdecisoen_END           (2)
#define SOC_CRGPERIPH_ISOSTAT_modemsubsysisoen_START  (4)
#define SOC_CRGPERIPH_ISOSTAT_modemsubsysisoen_END    (4)
#define SOC_CRGPERIPH_ISOSTAT_g3disoen_START          (5)
#define SOC_CRGPERIPH_ISOSTAT_g3disoen_END            (5)
#define SOC_CRGPERIPH_ISOSTAT_dsssubsysisoen_START    (6)
#define SOC_CRGPERIPH_ISOSTAT_dsssubsysisoen_END      (6)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor0isoen_START   (12)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor0isoen_END     (12)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor1isoen_START   (13)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor1isoen_END     (13)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor2isoen_START   (14)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor2isoen_END     (14)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor3isoen_START   (15)
#define SOC_CRGPERIPH_ISOSTAT_a53_0_cor3isoen_END     (15)
#define SOC_CRGPERIPH_ISOSTAT_a53isoen_START          (16)
#define SOC_CRGPERIPH_ISOSTAT_a53isoen_END            (16)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor0isoen_START   (17)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor0isoen_END     (17)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor1isoen_START   (18)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor1isoen_END     (18)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor2isoen_START   (19)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor2isoen_END     (19)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor3isoen_START   (20)
#define SOC_CRGPERIPH_ISOSTAT_a53_1_cor3isoen_END     (20)
#define SOC_CRGPERIPH_ISOSTAT_a57isoen_START          (21)
#define SOC_CRGPERIPH_ISOSTAT_a57isoen_END            (21)
#define SOC_CRGPERIPH_ISOSTAT_modemperiisoen_START    (22)
#define SOC_CRGPERIPH_ISOSTAT_modemperiisoen_END      (22)
#define SOC_CRGPERIPH_ISOSTAT_modemirmisoen_START     (23)
#define SOC_CRGPERIPH_ISOSTAT_modemirmisoen_END       (23)
#define SOC_CRGPERIPH_ISOSTAT_ivp32dspisoen_START     (24)
#define SOC_CRGPERIPH_ISOSTAT_ivp32dspisoen_END       (24)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERPWREN_UNION
 �ṹ˵��  : PERPWREN �Ĵ����ṹ���塣��ַƫ����:0x150����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ϵͳ��Դʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isppwren        : 1;  /* bit[0]    : ISP��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  vencpwren       : 1;  /* bit[1]    : VENC��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  vdecpwren       : 1;  /* bit[2]    : VDEC��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  reserved_0      : 1;  /* bit[3]    : ������ */
        unsigned int  reserved_1      : 1;  /* bit[4]    : ������ */
        unsigned int  dsssubsyspwren  : 1;  /* bit[5]    : DSS SUBSYS��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  reserved_2      : 1;  /* bit[6]    : ������ */
        unsigned int  reserved_3      : 1;  /* bit[7]    : ������ */
        unsigned int  reserved_4      : 1;  /* bit[8]    : ������ */
        unsigned int  reserved_5      : 1;  /* bit[9]    : ������ */
        unsigned int  reserved_6      : 1;  /* bit[10]   : ������ */
        unsigned int  a53_0_cor0pwren : 1;  /* bit[11]   : A53 cluster0 CORE0��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  a53_0_cor1pwren : 1;  /* bit[12]   : A53 cluster0 CORE1��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  a53_0_cor2pwren : 1;  /* bit[13]   : A53 cluster0 CORE2��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  a53_0_cor3pwren : 1;  /* bit[14]   : A53 cluster0 CORE3��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  a53_1_cor0pwren : 1;  /* bit[15]   : A53 cluster1 CORE0��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  a53_1_cor1pwren : 1;  /* bit[16]   : A53 cluster1 CORE1��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  a53_1_cor2pwren : 1;  /* bit[17]   : A53 cluster1 CORE2��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  a53_1_cor3pwren : 1;  /* bit[18]   : A53 cluster1 CORE3��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  modemperipwren  : 1;  /* bit[19]   : MODEM��ϵͳPERI��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  modemirmpwren   : 1;  /* bit[20]   : MODEM��ϵͳIRM��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  ivp32dsppwren   : 1;  /* bit[21]   : IVP32DSP��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܲ����� */
        unsigned int  reserved_7      : 10; /* bit[22-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERPWREN_UNION;
#endif
#define SOC_CRGPERIPH_PERPWREN_isppwren_START         (0)
#define SOC_CRGPERIPH_PERPWREN_isppwren_END           (0)
#define SOC_CRGPERIPH_PERPWREN_vencpwren_START        (1)
#define SOC_CRGPERIPH_PERPWREN_vencpwren_END          (1)
#define SOC_CRGPERIPH_PERPWREN_vdecpwren_START        (2)
#define SOC_CRGPERIPH_PERPWREN_vdecpwren_END          (2)
#define SOC_CRGPERIPH_PERPWREN_dsssubsyspwren_START   (5)
#define SOC_CRGPERIPH_PERPWREN_dsssubsyspwren_END     (5)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor0pwren_START  (11)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor0pwren_END    (11)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor1pwren_START  (12)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor1pwren_END    (12)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor2pwren_START  (13)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor2pwren_END    (13)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor3pwren_START  (14)
#define SOC_CRGPERIPH_PERPWREN_a53_0_cor3pwren_END    (14)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor0pwren_START  (15)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor0pwren_END    (15)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor1pwren_START  (16)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor1pwren_END    (16)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor2pwren_START  (17)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor2pwren_END    (17)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor3pwren_START  (18)
#define SOC_CRGPERIPH_PERPWREN_a53_1_cor3pwren_END    (18)
#define SOC_CRGPERIPH_PERPWREN_modemperipwren_START   (19)
#define SOC_CRGPERIPH_PERPWREN_modemperipwren_END     (19)
#define SOC_CRGPERIPH_PERPWREN_modemirmpwren_START    (20)
#define SOC_CRGPERIPH_PERPWREN_modemirmpwren_END      (20)
#define SOC_CRGPERIPH_PERPWREN_ivp32dsppwren_START    (21)
#define SOC_CRGPERIPH_PERPWREN_ivp32dsppwren_END      (21)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERPWRDIS_UNION
 �ṹ˵��  : PERPWRDIS �Ĵ����ṹ���塣��ַƫ����:0x154����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ϵͳ��Դʹ�ܳ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isppwrdis        : 1;  /* bit[0]    : ISP��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  vencpwrdis       : 1;  /* bit[1]    : VENC��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  vdecpwrdis       : 1;  /* bit[2]    : VDEC��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  reserved_0       : 1;  /* bit[3]    : ������ */
        unsigned int  reserved_1       : 1;  /* bit[4]    : ������ */
        unsigned int  dsssubsyspwrdis  : 1;  /* bit[5]    : DSS SUBSYS��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  reserved_2       : 1;  /* bit[6]    : ������ */
        unsigned int  reserved_3       : 1;  /* bit[7]    : ������ */
        unsigned int  reserved_4       : 1;  /* bit[8]    : ������ */
        unsigned int  reserved_5       : 1;  /* bit[9]    : ������ */
        unsigned int  reserved_6       : 1;  /* bit[10]   : ������ */
        unsigned int  a53_0_cor0pwrdis : 1;  /* bit[11]   : A53 cluster0 CORE0��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  a53_0_cor1pwrdis : 1;  /* bit[12]   : A53 cluster0 CORE1��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  a53_0_cor2pwrdis : 1;  /* bit[13]   : A53 cluster0 CORE2��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  a53_0_cor3pwrdis : 1;  /* bit[14]   : A53 cluster0 CORE3��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  a53_1_cor0pwrdis : 1;  /* bit[15]   : A53 cluster1 CORE0��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  a53_1_cor1pwrdis : 1;  /* bit[16]   : A53 cluster1 CORE1��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  a53_1_cor2pwrdis : 1;  /* bit[17]   : A53 cluster1 CORE2��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  a53_1_cor3pwrdis : 1;  /* bit[18]   : A53 cluster1 CORE3��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  modemperipwrdis  : 1;  /* bit[19]   : MODEM��ϵͳPERI��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  modemirmpwrdis   : 1;  /* bit[20]   : MODEM��ϵͳIRM��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  ivp32dsppwrdis   : 1;  /* bit[21]   : IVP32DSP��ϵͳ��Դʹ�ܿ��ƣ�д1ִ�е�Դʹ�ܳ��������� */
        unsigned int  reserved_7       : 10; /* bit[22-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERPWRDIS_UNION;
#endif
#define SOC_CRGPERIPH_PERPWRDIS_isppwrdis_START         (0)
#define SOC_CRGPERIPH_PERPWRDIS_isppwrdis_END           (0)
#define SOC_CRGPERIPH_PERPWRDIS_vencpwrdis_START        (1)
#define SOC_CRGPERIPH_PERPWRDIS_vencpwrdis_END          (1)
#define SOC_CRGPERIPH_PERPWRDIS_vdecpwrdis_START        (2)
#define SOC_CRGPERIPH_PERPWRDIS_vdecpwrdis_END          (2)
#define SOC_CRGPERIPH_PERPWRDIS_dsssubsyspwrdis_START   (5)
#define SOC_CRGPERIPH_PERPWRDIS_dsssubsyspwrdis_END     (5)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor0pwrdis_START  (11)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor0pwrdis_END    (11)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor1pwrdis_START  (12)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor1pwrdis_END    (12)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor2pwrdis_START  (13)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor2pwrdis_END    (13)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor3pwrdis_START  (14)
#define SOC_CRGPERIPH_PERPWRDIS_a53_0_cor3pwrdis_END    (14)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor0pwrdis_START  (15)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor0pwrdis_END    (15)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor1pwrdis_START  (16)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor1pwrdis_END    (16)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor2pwrdis_START  (17)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor2pwrdis_END    (17)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor3pwrdis_START  (18)
#define SOC_CRGPERIPH_PERPWRDIS_a53_1_cor3pwrdis_END    (18)
#define SOC_CRGPERIPH_PERPWRDIS_modemperipwrdis_START   (19)
#define SOC_CRGPERIPH_PERPWRDIS_modemperipwrdis_END     (19)
#define SOC_CRGPERIPH_PERPWRDIS_modemirmpwrdis_START    (20)
#define SOC_CRGPERIPH_PERPWRDIS_modemirmpwrdis_END      (20)
#define SOC_CRGPERIPH_PERPWRDIS_ivp32dsppwrdis_START    (21)
#define SOC_CRGPERIPH_PERPWRDIS_ivp32dsppwrdis_END      (21)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERPWRSTAT_UNION
 �ṹ˵��  : PERPWRSTAT �Ĵ����ṹ���塣��ַƫ����:0x158����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ϵͳ��Դʹ��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isppwrstat        : 1;  /* bit[0]    : ISP��Դʹ��״̬��
                                                             0��ISP��Դʹ�ܳ�����
                                                             1��ISP��Դʹ�ܡ� */
        unsigned int  vencpwrstat       : 1;  /* bit[1]    : VENC��Դʹ��״̬��
                                                             0��VENC��Դʹ�ܳ�����
                                                             1��VENC��Դʹ�ܡ� */
        unsigned int  vdecpwrstat       : 1;  /* bit[2]    : VDEC��Դʹ��״̬��
                                                             0��VDEC��Դʹ�ܳ�����
                                                             1��VDEC��Դʹ�ܡ� */
        unsigned int  reserved_0        : 1;  /* bit[3]    : ������ */
        unsigned int  reserved_1        : 1;  /* bit[4]    : ������ */
        unsigned int  dsssubsyspwrstat  : 1;  /* bit[5]    : DSS SUBSYS��Դʹ��״̬��
                                                             0��DSS SUBSYS��Դʹ�ܳ�����
                                                             1��DSS SUBSYS��Դʹ�ܡ� */
        unsigned int  reserved_2        : 1;  /* bit[6]    : ������ */
        unsigned int  reserved_3        : 1;  /* bit[7]    : ������ */
        unsigned int  reserved_4        : 1;  /* bit[8]    : ������ */
        unsigned int  reserved_5        : 1;  /* bit[9]    : ������ */
        unsigned int  reserved_6        : 1;  /* bit[10]   : ������ */
        unsigned int  a53_0_cor0pwrstat : 1;  /* bit[11]   : A53 cluster0 CORE0��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster0 CORE0��ϵͳ��Դʹ�ܳ�����
                                                             1��A53 cluster0 CORE0��ϵͳ��Դʹ�ܡ� */
        unsigned int  a53_0_cor1pwrstat : 1;  /* bit[12]   : A53 cluster0 CORE1��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster0 CORE1��ϵͳ��Դʹ�ܳ�����
                                                             1��A53 cluster0 CORE1��ϵͳ��Դʹ�ܡ� */
        unsigned int  a53_0_cor2pwrstat : 1;  /* bit[13]   : A53 cluster0 CORE2��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster0 CORE2��ϵͳ��Դʹ�ܳ�����
                                                             1��A53 cluster0 CORE2��ϵͳ��Դʹ�ܡ� */
        unsigned int  a53_0_cor3pwrstat : 1;  /* bit[14]   : A53 cluster0 CORE3��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster0 CORE3��ϵͳ��Դʹ�ܳ�����
                                                             1��A53 cluster0 CORE3��ϵͳ��Դʹ�ܡ� */
        unsigned int  a53_1_cor0pwrstat : 1;  /* bit[15]   : A53 cluster1 CORE0��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster1 CORE0��ϵͳ��Դʹ�ܳ�����
                                                             1��A53 cluster1 CORE0��ϵͳ��Դʹ�ܡ� */
        unsigned int  a53_1_cor1pwrstat : 1;  /* bit[16]   : A53 cluster1 CORE1��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster1 CORE1��ϵͳ��Դʹ�ܳ�����
                                                             1��A53 cluster1 CORE1��ϵͳ��Դʹ�ܡ� */
        unsigned int  a53_1_cor2pwrstat : 1;  /* bit[17]   : A53 cluster1 CORE2��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster1 CORE2��ϵͳ��Դʹ�ܳ�����
                                                             1��A53 cluster1 CORE2��ϵͳ��Դʹ�ܡ� */
        unsigned int  a53_1_cor3pwrstat : 1;  /* bit[18]   : A53 cluster1 CORE3��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster1 CORE3��ϵͳ��Դʹ�ܳ�����
                                                             1��A53 cluster1 CORE3��ϵͳ��Դʹ�ܡ� */
        unsigned int  modemperipwrstat  : 1;  /* bit[19]   : MODEM��ϵͳPERI��Դʹ��״̬��
                                                             0��MODEM��ϵͳPERI��Դʹ�ܳ�����
                                                             1��MODEM��ϵͳPERI��Դʹ�ܡ� */
        unsigned int  modemirmpwrstat   : 1;  /* bit[20]   : MODEM��ϵͳIRM��Դʹ��״̬��
                                                             0��MODEM��ϵͳIRM��Դʹ�ܳ�����
                                                             1��MODEM��ϵͳIRM��Դʹ�ܡ� */
        unsigned int  ivp32dsppwrstat   : 1;  /* bit[21]   : IVP32DSP��ϵͳ��Դʹ��״̬��
                                                             0��IVP32DSP��ϵͳ��Դʹ�ܳ�����
                                                             1��IVP32DSP��ϵͳ��Դʹ�ܡ� */
        unsigned int  reserved_7        : 10; /* bit[22-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERPWRSTAT_UNION;
#endif
#define SOC_CRGPERIPH_PERPWRSTAT_isppwrstat_START         (0)
#define SOC_CRGPERIPH_PERPWRSTAT_isppwrstat_END           (0)
#define SOC_CRGPERIPH_PERPWRSTAT_vencpwrstat_START        (1)
#define SOC_CRGPERIPH_PERPWRSTAT_vencpwrstat_END          (1)
#define SOC_CRGPERIPH_PERPWRSTAT_vdecpwrstat_START        (2)
#define SOC_CRGPERIPH_PERPWRSTAT_vdecpwrstat_END          (2)
#define SOC_CRGPERIPH_PERPWRSTAT_dsssubsyspwrstat_START   (5)
#define SOC_CRGPERIPH_PERPWRSTAT_dsssubsyspwrstat_END     (5)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor0pwrstat_START  (11)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor0pwrstat_END    (11)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor1pwrstat_START  (12)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor1pwrstat_END    (12)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor2pwrstat_START  (13)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor2pwrstat_END    (13)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor3pwrstat_START  (14)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_0_cor3pwrstat_END    (14)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor0pwrstat_START  (15)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor0pwrstat_END    (15)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor1pwrstat_START  (16)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor1pwrstat_END    (16)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor2pwrstat_START  (17)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor2pwrstat_END    (17)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor3pwrstat_START  (18)
#define SOC_CRGPERIPH_PERPWRSTAT_a53_1_cor3pwrstat_END    (18)
#define SOC_CRGPERIPH_PERPWRSTAT_modemperipwrstat_START   (19)
#define SOC_CRGPERIPH_PERPWRSTAT_modemperipwrstat_END     (19)
#define SOC_CRGPERIPH_PERPWRSTAT_modemirmpwrstat_START    (20)
#define SOC_CRGPERIPH_PERPWRSTAT_modemirmpwrstat_END      (20)
#define SOC_CRGPERIPH_PERPWRSTAT_ivp32dsppwrstat_START    (21)
#define SOC_CRGPERIPH_PERPWRSTAT_ivp32dsppwrstat_END      (21)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERPWRACK_UNION
 �ṹ˵��  : PERPWRACK �Ĵ����ṹ���塣��ַƫ����:0x15C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������ϵͳ���յ�Դ״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isppwrack         : 1;  /* bit[0]    : ISP��Դ״̬��
                                                             0��ISP��Դ�ж�״̬��
                                                             1��ISP��Դ����״̬�� */
        unsigned int  vencpwrack        : 1;  /* bit[1]    : VENC��Դ״̬��
                                                             0��VENC��Դ�ж�״̬��
                                                             1��VENC��Դ����״̬�� */
        unsigned int  vdecpwrack        : 1;  /* bit[2]    : VDEC��Դ״̬��
                                                             0��VDEC��Դ�ж�״̬��
                                                             1��VDEC��Դ����״̬�� */
        unsigned int  reserved_0        : 1;  /* bit[3]    : ������ */
        unsigned int  reserved_1        : 1;  /* bit[4]    : ������ */
        unsigned int  dsssubsyspwrack   : 1;  /* bit[5]    : DSS SUBSYS��Դʹ��״̬��
                                                             0��DSS SUBSYS��Դ�ж�״̬��
                                                             1��DSS SUBSYS��Դ����״̬�� */
        unsigned int  reserved_2        : 1;  /* bit[6]    : ������ */
        unsigned int  reserved_3        : 1;  /* bit[7]    : ������ */
        unsigned int  reserved_4        : 1;  /* bit[8]    : ������ */
        unsigned int  reserved_5        : 1;  /* bit[9]    : ������ */
        unsigned int  reserved_6        : 1;  /* bit[10]   : ������ */
        unsigned int  a53_0_core0pwrack : 1;  /* bit[11]   : A53 cluster0CORE0��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster0CORE0��ϵͳ��Դ�ж�״̬��
                                                             1��A53 cluster0CORE0��ϵͳ��Դ����״̬�� */
        unsigned int  a53_0_core1pwrack : 1;  /* bit[12]   : A53 cluster0CORE1��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster0CORE1��ϵͳ��Դ�ж�״̬��
                                                             1��A53 cluster0CORE1��ϵͳ��Դ����״̬�� */
        unsigned int  a53_0_core2pwrack : 1;  /* bit[13]   : A53 cluster0CORE2��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster0CORE2��ϵͳ��Դ�ж�״̬��
                                                             1��A53 cluster0CORE2��ϵͳ��Դ����״̬�� */
        unsigned int  a53_0_core3pwrack : 1;  /* bit[14]   : A53 cluster0 CORE3��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster0CORE3��ϵͳ��Դ�ж�״̬��
                                                             1��A53 cluster0CORE3��ϵͳ��Դ����״̬�� */
        unsigned int  a53_1_core0pwrack : 1;  /* bit[15]   : A53 cluster1 CORE0��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster1 CORE0��ϵͳ��Դ�ж�״̬��
                                                             1��A53 cluster1 CORE0��ϵͳ��Դ����״̬�� */
        unsigned int  a53_1_core1pwrack : 1;  /* bit[16]   : A53 cluster1 CORE1��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster1 CORE1��ϵͳ��Դ�ж�״̬��
                                                             1��A53 cluster1 CORE1��ϵͳ��Դ����״̬�� */
        unsigned int  a53_1_core2pwrack : 1;  /* bit[17]   : A53 cluster1 CORE2��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster1 CORE2��ϵͳ��Դ�ж�״̬��
                                                             1��A53 cluster1 CORE2��ϵͳ��Դ����״̬�� */
        unsigned int  a53_1_core3pwrack : 1;  /* bit[18]   : A53 cluster1 CORE3��ϵͳ��Դʹ��״̬��
                                                             0��A53 cluster1 CORE3��ϵͳ��Դ�ж�״̬��
                                                             1��A53 cluster1 CORE3��ϵͳ��Դ����״̬�� */
        unsigned int  reserved_7        : 1;  /* bit[19]   : ������ */
        unsigned int  g3dshpwrack0      : 1;  /* bit[20]   : G3D shader mtcmos0��Դʹ��״̬��
                                                             0��G3D shader mtcmos0��Դ�ж�״̬
                                                             1��G3D shader mtcmos0��Դ����״̬ */
        unsigned int  g3dshpwrack1      : 1;  /* bit[21]   : G3D shader mtcmos1��Դʹ��״̬��
                                                             0��G3D shader mtcmos1��Դ�ж�״̬
                                                             1��G3D shader mtcmos1��Դ����״̬ */
        unsigned int  g3dshpwrack2      : 1;  /* bit[22]   : G3D shader mtcmos2��Դʹ��״̬��
                                                             0��G3D shader mtcmos2��Դ�ж�״̬
                                                             1��G3D shader mtcmos2��Դ����״̬ */
        unsigned int  g3dshpwrack3      : 1;  /* bit[23]   : G3D shader mtcmos3��Դʹ��״̬��
                                                             0��G3D shader mtcmos3��Դ�ж�״̬
                                                             1��G3D shader mtcmos3��Դ����״̬ */
        unsigned int  g3dshpwrack4      : 1;  /* bit[24]   : G3D shader mtcmos4��Դʹ��״̬��
                                                             0��G3D shader mtcmos4��Դ�ж�״̬
                                                             1��G3D shader mtcmos4��Դ����״̬ */
        unsigned int  g3dshpwrack5      : 1;  /* bit[25]   : G3D shader mtcmos5��Դʹ��״̬��
                                                             0��G3D shader mtcmos5��Դ�ж�״̬
                                                             1��G3D shader mtcmos5��Դ����״̬ */
        unsigned int  g3dcg0en          : 1;  /* bit[26]   : ָʾG3D�ڲ�core group0����ģʽ
                                                             0�������prechargeģʽ
                                                             1����������ģʽ */
        unsigned int  modemperipwrack   : 1;  /* bit[27]   : MODEM��ϵͳPERI��Դʹ��״̬��
                                                             0��MODEM��ϵͳPERI��Դ�ж�״̬
                                                             1��MODEM��ϵͳPERI��Դ����״̬ */
        unsigned int  modemirmpwrack    : 1;  /* bit[28]   : MODEM��ϵͳIRM��Դʹ��״̬��
                                                             0��MODEM��ϵͳIRM��Դ�ж�״̬
                                                             1��MODEM��ϵͳIRM��Դ����״̬ */
        unsigned int  ivp32dsppwrack    : 1;  /* bit[29]   : IVP32DSP��ϵͳ��Դʹ��״̬��
                                                             0��IVP32DSP��ϵͳ��Դ�ж�״̬
                                                             1��IVP32DSP��ϵͳ��Դ����״̬ */
        unsigned int  reserved_8        : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERPWRACK_UNION;
#endif
#define SOC_CRGPERIPH_PERPWRACK_isppwrack_START          (0)
#define SOC_CRGPERIPH_PERPWRACK_isppwrack_END            (0)
#define SOC_CRGPERIPH_PERPWRACK_vencpwrack_START         (1)
#define SOC_CRGPERIPH_PERPWRACK_vencpwrack_END           (1)
#define SOC_CRGPERIPH_PERPWRACK_vdecpwrack_START         (2)
#define SOC_CRGPERIPH_PERPWRACK_vdecpwrack_END           (2)
#define SOC_CRGPERIPH_PERPWRACK_dsssubsyspwrack_START    (5)
#define SOC_CRGPERIPH_PERPWRACK_dsssubsyspwrack_END      (5)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core0pwrack_START  (11)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core0pwrack_END    (11)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core1pwrack_START  (12)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core1pwrack_END    (12)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core2pwrack_START  (13)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core2pwrack_END    (13)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core3pwrack_START  (14)
#define SOC_CRGPERIPH_PERPWRACK_a53_0_core3pwrack_END    (14)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core0pwrack_START  (15)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core0pwrack_END    (15)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core1pwrack_START  (16)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core1pwrack_END    (16)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core2pwrack_START  (17)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core2pwrack_END    (17)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core3pwrack_START  (18)
#define SOC_CRGPERIPH_PERPWRACK_a53_1_core3pwrack_END    (18)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack0_START       (20)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack0_END         (20)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack1_START       (21)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack1_END         (21)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack2_START       (22)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack2_END         (22)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack3_START       (23)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack3_END         (23)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack4_START       (24)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack4_END         (24)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack5_START       (25)
#define SOC_CRGPERIPH_PERPWRACK_g3dshpwrack5_END         (25)
#define SOC_CRGPERIPH_PERPWRACK_g3dcg0en_START           (26)
#define SOC_CRGPERIPH_PERPWRACK_g3dcg0en_END             (26)
#define SOC_CRGPERIPH_PERPWRACK_modemperipwrack_START    (27)
#define SOC_CRGPERIPH_PERPWRACK_modemperipwrack_END      (27)
#define SOC_CRGPERIPH_PERPWRACK_modemirmpwrack_START     (28)
#define SOC_CRGPERIPH_PERPWRACK_modemirmpwrack_END       (28)
#define SOC_CRGPERIPH_PERPWRACK_ivp32dsppwrack_START     (29)
#define SOC_CRGPERIPH_PERPWRACK_ivp32dsppwrack_END       (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_CLKEN_UNION
 �ṹ˵��  : A53_CLKEN �Ĵ����ṹ���塣��ַƫ����:0x160����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: A53 CLUSTER��ϵͳʱ��ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_clkinen_sys                          : 1;  /* bit[0]    : CPUʱ��ʹ��ϵͳ���ƣ�
                                                                                    0���ر�ʱ��
                                                                                    1������ʱ�� */
        unsigned int  a53_atclkoff_sys_n                       : 1;  /* bit[1]    : ATCLKʱ���ſ�ϵͳ���ƣ�
                                                                                    0���ر�ʱ��
                                                                                    1������ʱ�� */
        unsigned int  a53_pclkdbg_to_a53_asyn_bri_clkoff_sys_n : 1;  /* bit[2]    : PCLKDBG_TO_A53_ASYN_BRIʱ��ʹ��ϵͳ���ƣ�
                                                                                    0���ر�ʱ��
                                                                                    1������ʱ�� */
        unsigned int  a53_atclk_to_asyn_bri_clkoff_sys_n       : 1;  /* bit[3]    : ATCLK_TO_ASYN_BRIʱ��ʹ��ϵͳ���ƣ�
                                                                                    0���ر�ʱ��
                                                                                    1������ʱ�� */
        unsigned int  a53_pclkdbg_to_a53_cs_clkoff_sys_n       : 1;  /* bit[4]    : PCLKDBG_TO_A53_CSʱ��ʹ��ϵͳ���ƣ�
                                                                                    0���ر�ʱ��
                                                                                    1������ʱ�� */
        unsigned int  reserved                                 : 10; /* bit[5-14] : ������ */
        unsigned int  a53_clkoff_sys                           : 1;  /* bit[15]   : A53��ϵͳ����ʱ�ӹض�ʹ�ܣ�
                                                                                    0��ʱ��ά�֣�
                                                                                    1��ʱ�ӹضϡ� */
        unsigned int  clkmasken                                : 16; /* bit[16-31]: clkenÿ������λ��ʹ��λ��
                                                                                    ֻ�е�clkmasken��Ӧ�ı���λΪ1'b1��clken��Ӧ�ı���λ�������á�clkmasken[0]����clken[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_A53_CLKEN_UNION;
#endif
#define SOC_CRGPERIPH_A53_CLKEN_a53_clkinen_sys_START                           (0)
#define SOC_CRGPERIPH_A53_CLKEN_a53_clkinen_sys_END                             (0)
#define SOC_CRGPERIPH_A53_CLKEN_a53_atclkoff_sys_n_START                        (1)
#define SOC_CRGPERIPH_A53_CLKEN_a53_atclkoff_sys_n_END                          (1)
#define SOC_CRGPERIPH_A53_CLKEN_a53_pclkdbg_to_a53_asyn_bri_clkoff_sys_n_START  (2)
#define SOC_CRGPERIPH_A53_CLKEN_a53_pclkdbg_to_a53_asyn_bri_clkoff_sys_n_END    (2)
#define SOC_CRGPERIPH_A53_CLKEN_a53_atclk_to_asyn_bri_clkoff_sys_n_START        (3)
#define SOC_CRGPERIPH_A53_CLKEN_a53_atclk_to_asyn_bri_clkoff_sys_n_END          (3)
#define SOC_CRGPERIPH_A53_CLKEN_a53_pclkdbg_to_a53_cs_clkoff_sys_n_START        (4)
#define SOC_CRGPERIPH_A53_CLKEN_a53_pclkdbg_to_a53_cs_clkoff_sys_n_END          (4)
#define SOC_CRGPERIPH_A53_CLKEN_a53_clkoff_sys_START                            (15)
#define SOC_CRGPERIPH_A53_CLKEN_a53_clkoff_sys_END                              (15)
#define SOC_CRGPERIPH_A53_CLKEN_clkmasken_START                                 (16)
#define SOC_CRGPERIPH_A53_CLKEN_clkmasken_END                                   (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_RSTEN_UNION
 �ṹ˵��  : A53_RSTEN �Ĵ����ṹ���塣��ַƫ����:0x164����ֵ:0x00000000�����:32
 �Ĵ���˵��: A53 CLUSTER��ϵͳ��λʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_coresight_soft_rst_req : 1;  /* bit[0]    : A53 cluster�ڲ�coresight ϵͳ��λ���󣬸���Ч */
        unsigned int  a53_adb_asyn_bri_rst_req   : 1;  /* bit[1]    : A53 ADB�첽��ϵͳ��λ���󣬸���Ч */
        unsigned int  a53_npresetdbg_rst_req     : 1;  /* bit[2]    : Debug APB��CTI��CTM��λ���󣬵�ƽ��λ������Ч����Чʱ���ḴλPCLKDBGʱ�����debug�߼��� */
        unsigned int  reserved_0                 : 4;  /* bit[3-6]  : ������ */
        unsigned int  reserved_1                 : 4;  /* bit[7-10] : ������ */
        unsigned int  a53_core_rst_software_req  : 4;  /* bit[11-14]: ������λ���󣬵�ƽ��λ������Ч����Чʱ���Ḵλ�������߼�������core��NEON��VFP�� */
        unsigned int  a53_rst_software_req       : 1;  /* bit[15]   : A53MP������λ���󣬵�ƽ��λ������Ч */
        unsigned int  a53_core_por_rst_req       : 4;  /* bit[16-19]: �����ϵ縴λ���󣬵�ƽ��λ������Ч����Чʱ���Ḵλ���еĴ������߼�������core��NEON��VFP��debug��PTM��breakpoint��watchpoint��CLKʱ�����ȫ���߼��� */
        unsigned int  a53_hpm_cpu_rst_req        : 4;  /* bit[20-23]: cpu hpm�ϵ縴λ���󣬵�ƽ��λ������Ч */
        unsigned int  a53_hpm_scu_rst_req        : 1;  /* bit[24]   : scu hpm�ϵ縴λ���󣬵�ƽ��λ������Ч */
        unsigned int  reserved_2                 : 6;  /* bit[25-30]: ������ */
        unsigned int  a53_srst_req_en            : 1;  /* bit[31]   : CPU��ϵͳ������λʹ�ܣ�
                                                                      0����Ч����
                                                                      1����λʹ�ܣ� */
    } reg;
} SOC_CRGPERIPH_A53_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_A53_RSTEN_a53_coresight_soft_rst_req_START  (0)
#define SOC_CRGPERIPH_A53_RSTEN_a53_coresight_soft_rst_req_END    (0)
#define SOC_CRGPERIPH_A53_RSTEN_a53_adb_asyn_bri_rst_req_START    (1)
#define SOC_CRGPERIPH_A53_RSTEN_a53_adb_asyn_bri_rst_req_END      (1)
#define SOC_CRGPERIPH_A53_RSTEN_a53_npresetdbg_rst_req_START      (2)
#define SOC_CRGPERIPH_A53_RSTEN_a53_npresetdbg_rst_req_END        (2)
#define SOC_CRGPERIPH_A53_RSTEN_a53_core_rst_software_req_START   (11)
#define SOC_CRGPERIPH_A53_RSTEN_a53_core_rst_software_req_END     (14)
#define SOC_CRGPERIPH_A53_RSTEN_a53_rst_software_req_START        (15)
#define SOC_CRGPERIPH_A53_RSTEN_a53_rst_software_req_END          (15)
#define SOC_CRGPERIPH_A53_RSTEN_a53_core_por_rst_req_START        (16)
#define SOC_CRGPERIPH_A53_RSTEN_a53_core_por_rst_req_END          (19)
#define SOC_CRGPERIPH_A53_RSTEN_a53_hpm_cpu_rst_req_START         (20)
#define SOC_CRGPERIPH_A53_RSTEN_a53_hpm_cpu_rst_req_END           (23)
#define SOC_CRGPERIPH_A53_RSTEN_a53_hpm_scu_rst_req_START         (24)
#define SOC_CRGPERIPH_A53_RSTEN_a53_hpm_scu_rst_req_END           (24)
#define SOC_CRGPERIPH_A53_RSTEN_a53_srst_req_en_START             (31)
#define SOC_CRGPERIPH_A53_RSTEN_a53_srst_req_en_END               (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_RSTDIS_UNION
 �ṹ˵��  : A53_RSTDIS �Ĵ����ṹ���塣��ַƫ����:0x168����ֵ:0x00000000�����:32
 �Ĵ���˵��: A53 CLUSTER��ϵͳ��λ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_coresight_soft_rst_req : 1;  /* bit[0]    : A53 cluster�ڲ�coresight ϵͳ��λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  a53_adb_asyn_bri_rst_req   : 1;  /* bit[1]    : A53 ADB�첽��ϵͳ��λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  a53_npresetdbg_rst_req     : 1;  /* bit[2]    : Debug APB��CTI��CTM��λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  reserved_0                 : 4;  /* bit[3-6]  : ������ */
        unsigned int  reserved_1                 : 4;  /* bit[7-10] : ������ */
        unsigned int  a53_core_rst_software_req  : 4;  /* bit[11-14]: ������λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  a53_rst_software_req       : 1;  /* bit[15]   : A53MP������λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  a53_core_por_rst_req       : 4;  /* bit[16-19]: �����ϵ縴λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  a53_hpm_cpu_rst_req        : 4;  /* bit[20-23]: cpu hpm�ϵ縴λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  a53_hpm_scu_rst_req        : 1;  /* bit[24]   : scu hpm�ϵ縴λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  reserved_2                 : 6;  /* bit[25-30]: ������ */
        unsigned int  a53_srst_req_en            : 1;  /* bit[31]   : CPU��ϵͳ������λ������
                                                                      0����Ч����
                                                                      1����λ������ */
    } reg;
} SOC_CRGPERIPH_A53_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_A53_RSTDIS_a53_coresight_soft_rst_req_START  (0)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_coresight_soft_rst_req_END    (0)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_adb_asyn_bri_rst_req_START    (1)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_adb_asyn_bri_rst_req_END      (1)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_npresetdbg_rst_req_START      (2)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_npresetdbg_rst_req_END        (2)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_core_rst_software_req_START   (11)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_core_rst_software_req_END     (14)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_rst_software_req_START        (15)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_rst_software_req_END          (15)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_core_por_rst_req_START        (16)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_core_por_rst_req_END          (19)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_hpm_cpu_rst_req_START         (20)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_hpm_cpu_rst_req_END           (23)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_hpm_scu_rst_req_START         (24)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_hpm_scu_rst_req_END           (24)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_srst_req_en_START             (31)
#define SOC_CRGPERIPH_A53_RSTDIS_a53_srst_req_en_END               (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_RSTSTAT_UNION
 �ṹ˵��  : A53_RSTSTAT �Ĵ����ṹ���塣��ַƫ����:0x16C����ֵ:0x800F0002�����:32
 �Ĵ���˵��: A53 CLUSTER��ϵͳ��λʹ��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_coresight_soft_rst_req : 1;  /* bit[0]    : A53 cluster�ڲ�coresight ϵͳ��λ״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  a53_adb_asyn_bri_rst_req   : 1;  /* bit[1]    : A53 ADB�첽��ϵͳ��λ״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  a53_npresetdbg_rst_req     : 1;  /* bit[2]    : Debug APB��CTI��CTM��λ״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  reserved_0                 : 4;  /* bit[3-6]  : ������ */
        unsigned int  reserved_1                 : 4;  /* bit[7-10] : ������ */
        unsigned int  a53_core_rst_software_req  : 4;  /* bit[11-14]: ������λʹ��״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  a53_rst_software_req       : 1;  /* bit[15]   : A53MP������λ״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  a53_core_por_rst_req       : 4;  /* bit[16-19]: �����ϵ縴λʹ��״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  a53_hpm_cpu_rst_req        : 4;  /* bit[20-23]: cpu hpm�ϵ縴λʹ��״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  a53_hpm_scu_rst_req        : 1;  /* bit[24]   : scu hpm�ϵ縴λʹ��״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  reserved_2                 : 6;  /* bit[25-30]: ������ */
        unsigned int  a53_srst_req_en            : 1;  /* bit[31]   : CPU��ϵͳ������λʹ��״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
    } reg;
} SOC_CRGPERIPH_A53_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_coresight_soft_rst_req_START  (0)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_coresight_soft_rst_req_END    (0)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_adb_asyn_bri_rst_req_START    (1)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_adb_asyn_bri_rst_req_END      (1)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_npresetdbg_rst_req_START      (2)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_npresetdbg_rst_req_END        (2)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_core_rst_software_req_START   (11)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_core_rst_software_req_END     (14)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_rst_software_req_START        (15)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_rst_software_req_END          (15)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_core_por_rst_req_START        (16)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_core_por_rst_req_END          (19)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_hpm_cpu_rst_req_START         (20)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_hpm_cpu_rst_req_END           (23)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_hpm_scu_rst_req_START         (24)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_hpm_scu_rst_req_END           (24)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_srst_req_en_START             (31)
#define SOC_CRGPERIPH_A53_RSTSTAT_a53_srst_req_en_END               (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_ADBLPSTAT_UNION
 �ṹ˵��  : A53_ADBLPSTAT �Ĵ����ṹ���塣��ַƫ����:0x174����ֵ:0x00000000�����:32
 �Ĵ���˵��: A53 CLUSTER ADB�͹��ļĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_d_pwrdnreqn : 1;  /* bit[0]   : ADB-400�첽���µ�����Ӧ���źţ�����Ч */
        unsigned int  a53_d_pwrdnackn : 1;  /* bit[1]   : ADB-400�첽���µ�����Ӧ���źţ�����Ч */
        unsigned int  a53_d_cactives  : 1;  /* bit[2]   : ָʾADB-400�첽�����Ƿ����л��transaction��
                                                          0���첽��������transaction�������
                                                          1���첽�����д��ڻ��transaction */
        unsigned int  reserved        : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_CRGPERIPH_A53_ADBLPSTAT_UNION;
#endif
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_pwrdnreqn_START  (0)
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_pwrdnreqn_END    (0)
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_pwrdnackn_START  (1)
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_pwrdnackn_END    (1)
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_cactives_START   (2)
#define SOC_CRGPERIPH_A53_ADBLPSTAT_a53_d_cactives_END     (2)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_CTRL0_UNION
 �ṹ˵��  : A53_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x178����ֵ:0xFFF0F000�����:32
 �Ĵ���˵��: A53 CLUSTER�������üĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_pd_detect_clr       : 1;  /* bit[0]    : A53����̽��״̬���ָʾ�ź� */
        unsigned int  a53_pd_detect_start     : 1;  /* bit[1]    : A53����̽�⿪ʼָʾ�ź� */
        unsigned int  a53_set_acinactm_low    : 1;  /* bit[2]    : ACINACTM�����߼�bypass�ź� */
        unsigned int  a53_set_acinactm_high   : 1;  /* bit[3]    : ACINACTM�����߼�bypass�ź� */
        unsigned int  a53_dbgpwrdup           : 4;  /* bit[4-7]  : CPU���ϵ�ָʾ�ź� */
        unsigned int  a53_l2rstdisable        : 1;  /* bit[8]    : ��λ�׶ν�ֹL2 cache�Զ�invalidate�ź� */
        unsigned int  a53_l1rstdisable        : 1;  /* bit[9]    : ��λ�׶ν�ֹL1 cache�Զ�invalidate�ź� */
        unsigned int  reserved                : 2;  /* bit[10-11]: ������ */
        unsigned int  a53_broadcastcachemaint : 1;  /* bit[12]   : ʹ��cacheһ���Բ����Ƿ��㲥������cache��
                                                                   0��һ���Բ�������㲥������cache
                                                                   1��һ���Բ�����㲥������cache */
        unsigned int  a53_broadcastouter      : 1;  /* bit[13]   : �Ƿ�ʹ���ⲿshareable�����Ĺ㲥
                                                                   0��outer shareable�������㲥
                                                                   1��outer shareable������㲥 */
        unsigned int  a53_broadcastinner      : 1;  /* bit[14]   : �Ƿ�ʹ���ڲ�shareable�����Ĺ㲥
                                                                   0��inner shareable�������㲥
                                                                   1��inner shareable������㲥 */
        unsigned int  a53_sysbardisable       : 1;  /* bit[15]   : barriers�����Ƿ�㲥��ϵͳ����
                                                                   0��barriers������㲥��ϵͳ����
                                                                   1��barriers��������㲥��ϵͳ���� */
        unsigned int  a53_vinithi             : 4;  /* bit[16-19]: A53������ʽѡ��ÿbit��Ӧһ��core��
                                                                   0���ӵ�λ��ַ��0x00000000������
                                                                   1���Ӹ�λ��ַ��0xFFFF0000������ */
        unsigned int  a53_sei_n               : 4;  /* bit[20-23]: ����system error�ж������źţ���������Ч�� */
        unsigned int  a53_rei_n               : 4;  /* bit[24-27]: ����RAM error�ж������źţ���������Ч�� */
        unsigned int  a53_vsei_n              : 4;  /* bit[28-31]: ��������system error�ж������źţ���������Ч�� */
    } reg;
} SOC_CRGPERIPH_A53_CTRL0_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL0_a53_pd_detect_clr_START        (0)
#define SOC_CRGPERIPH_A53_CTRL0_a53_pd_detect_clr_END          (0)
#define SOC_CRGPERIPH_A53_CTRL0_a53_pd_detect_start_START      (1)
#define SOC_CRGPERIPH_A53_CTRL0_a53_pd_detect_start_END        (1)
#define SOC_CRGPERIPH_A53_CTRL0_a53_set_acinactm_low_START     (2)
#define SOC_CRGPERIPH_A53_CTRL0_a53_set_acinactm_low_END       (2)
#define SOC_CRGPERIPH_A53_CTRL0_a53_set_acinactm_high_START    (3)
#define SOC_CRGPERIPH_A53_CTRL0_a53_set_acinactm_high_END      (3)
#define SOC_CRGPERIPH_A53_CTRL0_a53_dbgpwrdup_START            (4)
#define SOC_CRGPERIPH_A53_CTRL0_a53_dbgpwrdup_END              (7)
#define SOC_CRGPERIPH_A53_CTRL0_a53_l2rstdisable_START         (8)
#define SOC_CRGPERIPH_A53_CTRL0_a53_l2rstdisable_END           (8)
#define SOC_CRGPERIPH_A53_CTRL0_a53_l1rstdisable_START         (9)
#define SOC_CRGPERIPH_A53_CTRL0_a53_l1rstdisable_END           (9)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastcachemaint_START  (12)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastcachemaint_END    (12)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastouter_START       (13)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastouter_END         (13)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastinner_START       (14)
#define SOC_CRGPERIPH_A53_CTRL0_a53_broadcastinner_END         (14)
#define SOC_CRGPERIPH_A53_CTRL0_a53_sysbardisable_START        (15)
#define SOC_CRGPERIPH_A53_CTRL0_a53_sysbardisable_END          (15)
#define SOC_CRGPERIPH_A53_CTRL0_a53_vinithi_START              (16)
#define SOC_CRGPERIPH_A53_CTRL0_a53_vinithi_END                (19)
#define SOC_CRGPERIPH_A53_CTRL0_a53_sei_n_START                (20)
#define SOC_CRGPERIPH_A53_CTRL0_a53_sei_n_END                  (23)
#define SOC_CRGPERIPH_A53_CTRL0_a53_rei_n_START                (24)
#define SOC_CRGPERIPH_A53_CTRL0_a53_rei_n_END                  (27)
#define SOC_CRGPERIPH_A53_CTRL0_a53_vsei_n_START               (28)
#define SOC_CRGPERIPH_A53_CTRL0_a53_vsei_n_END                 (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_CTRL1_UNION
 �ṹ˵��  : A53_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x17C����ֵ:0x00000013�����:32
 �Ĵ���˵��: A53 CLUSTER�������üĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_ctrl_cpu     : 16; /* bit[0-15] : a53 CPU memory���� */
        unsigned int  mem_ctrl_s_a53cs : 16; /* bit[16-31]: a53 ETF ram�����źţ�ʹ��TSMC memory��bit�������£�
                                                            bit[0]��SLP
                                                            bit[1]��DSLP
                                                            bit[2]��SD
                                                            bit[15:3]��unused */
    } reg;
} SOC_CRGPERIPH_A53_CTRL1_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL1_mem_ctrl_cpu_START      (0)
#define SOC_CRGPERIPH_A53_CTRL1_mem_ctrl_cpu_END        (15)
#define SOC_CRGPERIPH_A53_CTRL1_mem_ctrl_s_a53cs_START  (16)
#define SOC_CRGPERIPH_A53_CTRL1_mem_ctrl_s_a53cs_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_CTRL2_UNION
 �ṹ˵��  : A53_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x180����ֵ:0x09F1C020�����:32
 �Ĵ���˵��: A53 CLUSTER�������üĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_aa64naa32           : 4;  /* bit[0-3]  : ���˼Ĵ���λ����λʱ������
                                                                   0��AArch32��
                                                                   1��AArch64�� */
        unsigned int  a53_ret_ctrl_ret        : 3;  /* bit[4-6]  : A53MP noncpu������������ģʽ��memory�����źš�Bit�������£�
                                                                   bit[0]��SLP
                                                                   bit[1]��DSLP
                                                                   bit[2]��unused */
        unsigned int  a53_ret_ctrl_norm       : 3;  /* bit[7-9]  : A53MP noncpu������������ģʽ��memory�����źš�Bit�������£�
                                                                   bit[0]��SLP
                                                                   bit[1]��DSLP
                                                                   bit[2]��unused */
        unsigned int  a53_wfe_ret_en_l2       : 1;  /* bit[10]   : A53MP noncpu����WFE״̬���Զ�retentionʹ�� */
        unsigned int  a53_wfi_ret_en_l2       : 1;  /* bit[11]   : A53MP noncpu����WFI״̬���Զ�retentionʹ�� */
        unsigned int  a53_dyn_ret_en_l2       : 1;  /* bit[12]   : A53MP noncpu���ֶ�̬retentionȫ��ʹ�� */
        unsigned int  a53_l2flushreq          : 1;  /* bit[13]   : L2Ӳ��flush���� */
        unsigned int  a53_sys_cnt_en_dly      : 6;  /* bit[14-19]: A53 sysconter ����en�ӳ� */
        unsigned int  a53_ret_wait_cycle      : 6;  /* bit[20-25]: A53 L2 RAM�˳�ret״̬�ӳ� */
        unsigned int  a53_ret_wait_cycle_chg  : 1;  /* bit[26]   : ��̬�޸ĵȴ�����ʱ�������Ĳ���ʹ���ź� */
        unsigned int  a53_l2_input_lat_sel    : 1;  /* bit[27]   : L2 RAM�����ӳ����� */
        unsigned int  a53_l2_output_lat_sel   : 1;  /* bit[28]   : L2 RAM����ӳ����� */
        unsigned int  a53_stretch_l2ramclk_en : 1;  /* bit[29]   : L2 RAMʱ����չʹ�� */
        unsigned int  reserved                : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_CRGPERIPH_A53_CTRL2_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL2_a53_aa64naa32_START            (0)
#define SOC_CRGPERIPH_A53_CTRL2_a53_aa64naa32_END              (3)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_ctrl_ret_START         (4)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_ctrl_ret_END           (6)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_ctrl_norm_START        (7)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_ctrl_norm_END          (9)
#define SOC_CRGPERIPH_A53_CTRL2_a53_wfe_ret_en_l2_START        (10)
#define SOC_CRGPERIPH_A53_CTRL2_a53_wfe_ret_en_l2_END          (10)
#define SOC_CRGPERIPH_A53_CTRL2_a53_wfi_ret_en_l2_START        (11)
#define SOC_CRGPERIPH_A53_CTRL2_a53_wfi_ret_en_l2_END          (11)
#define SOC_CRGPERIPH_A53_CTRL2_a53_dyn_ret_en_l2_START        (12)
#define SOC_CRGPERIPH_A53_CTRL2_a53_dyn_ret_en_l2_END          (12)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2flushreq_START           (13)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2flushreq_END             (13)
#define SOC_CRGPERIPH_A53_CTRL2_a53_sys_cnt_en_dly_START       (14)
#define SOC_CRGPERIPH_A53_CTRL2_a53_sys_cnt_en_dly_END         (19)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_wait_cycle_START       (20)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_wait_cycle_END         (25)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_wait_cycle_chg_START   (26)
#define SOC_CRGPERIPH_A53_CTRL2_a53_ret_wait_cycle_chg_END     (26)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2_input_lat_sel_START     (27)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2_input_lat_sel_END       (27)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2_output_lat_sel_START    (28)
#define SOC_CRGPERIPH_A53_CTRL2_a53_l2_output_lat_sel_END      (28)
#define SOC_CRGPERIPH_A53_CTRL2_a53_stretch_l2ramclk_en_START  (29)
#define SOC_CRGPERIPH_A53_CTRL2_a53_stretch_l2ramclk_en_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_STAT_UNION
 �ṹ˵��  : A53_STAT �Ĵ����ṹ���塣��ַƫ����:0x194����ֵ:0x0000100F�����:32
 �Ĵ���˵��: A53 CLUSTER״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_standbywfi   : 4;  /* bit[0-3]  : ָʾCPU�Ƿ���WFI״̬ */
        unsigned int  a53_standbywfe   : 4;  /* bit[4-7]  : ָʾCPU�Ƿ���WFE״̬ */
        unsigned int  a53_smpen        : 4;  /* bit[8-11] : 0��Disables receiving of instruction cache and TLB maintenance operations. This is the reset 
                                                            value
                                                            1��Enables receiving of instruction cache and TLB maintenance operations */
        unsigned int  a53_standbywfil2 : 1;  /* bit[12]   : ָʾL2�Ƿ���WFI״̬ */
        unsigned int  a53_dbgack       : 1;  /* bit[13]   : A53 core����debug״̬���״ָ̬ʾ������Ч������һcore����debug״̬ʱ�����ź���Ч */
        unsigned int  a53_l2flushdone  : 1;  /* bit[14]   : L2Ӳ��flush����ɡ� */
        unsigned int  a53_idle_flag    : 1;  /* bit[15]   : a53idleָʾ״̬��Ϊ1��ʾidle��������tcxo */
        unsigned int  a53_sbgpwrupreq  : 4;  /* bit[16-19]: Processor powerup request:
                                                            0: No request for processor power up.
                                                            1: Request for processor power up. */
        unsigned int  a53_dbgnopwrdwn  : 4;  /* bit[20-23]: No powerdown request. On a powerdown request:
                                                            0: The SoC power controller powers down the processor.
                                                            1: The SoC power controller does not power down the processor */
        unsigned int  a53_snoop_cnt    : 6;  /* bit[24-29]: A53 snoop counter����ֵ */
        unsigned int  reserved         : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_CRGPERIPH_A53_STAT_UNION;
#endif
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfi_START    (0)
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfi_END      (3)
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfe_START    (4)
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfe_END      (7)
#define SOC_CRGPERIPH_A53_STAT_a53_smpen_START         (8)
#define SOC_CRGPERIPH_A53_STAT_a53_smpen_END           (11)
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfil2_START  (12)
#define SOC_CRGPERIPH_A53_STAT_a53_standbywfil2_END    (12)
#define SOC_CRGPERIPH_A53_STAT_a53_dbgack_START        (13)
#define SOC_CRGPERIPH_A53_STAT_a53_dbgack_END          (13)
#define SOC_CRGPERIPH_A53_STAT_a53_l2flushdone_START   (14)
#define SOC_CRGPERIPH_A53_STAT_a53_l2flushdone_END     (14)
#define SOC_CRGPERIPH_A53_STAT_a53_idle_flag_START     (15)
#define SOC_CRGPERIPH_A53_STAT_a53_idle_flag_END       (15)
#define SOC_CRGPERIPH_A53_STAT_a53_sbgpwrupreq_START   (16)
#define SOC_CRGPERIPH_A53_STAT_a53_sbgpwrupreq_END     (19)
#define SOC_CRGPERIPH_A53_STAT_a53_dbgnopwrdwn_START   (20)
#define SOC_CRGPERIPH_A53_STAT_a53_dbgnopwrdwn_END     (23)
#define SOC_CRGPERIPH_A53_STAT_a53_snoop_cnt_START     (24)
#define SOC_CRGPERIPH_A53_STAT_a53_snoop_cnt_END       (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_CLKEN_UNION
 �ṹ˵��  : MAIA_CLKEN �Ĵ����ṹ���塣��ַƫ����:0x1C0����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: A57 CLUSTER��ϵͳʱ��ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_clkinen_sys                          : 1;  /* bit[0]    : CPUʱ��ʹ��ϵͳ���ƣ�
                                                                                    0���ر�ʱ��
                                                                                    1������ʱ�� */
        unsigned int  a57_atclkoff_sys_n                       : 1;  /* bit[1]    : ATCLKʱ���ſ�ϵͳ���ƣ�
                                                                                    0���ر�ʱ��
                                                                                    1������ʱ�� */
        unsigned int  a57_pclkdbg_to_a53_asyn_bri_clkoff_sys_n : 1;  /* bit[2]    : PCLKDBG_TO_A53_ASYN_BRIʱ��ʹ��ϵͳ���ƣ�
                                                                                    0���ر�ʱ��
                                                                                    1������ʱ�� */
        unsigned int  a57_atclk_to_asyn_bri_clkoff_sys_n       : 1;  /* bit[3]    : ATCLK_TO_ASYN_BRIʱ��ʹ��ϵͳ���ƣ�
                                                                                    0���ر�ʱ��
                                                                                    1������ʱ�� */
        unsigned int  reserved                                 : 11; /* bit[4-14] : ������ */
        unsigned int  a57_clkoff_sys                           : 1;  /* bit[15]   : A57��ϵͳ����ʱ�ӹض�ʹ�ܣ�
                                                                                    0��ʱ��ά�֣�
                                                                                    1��ʱ�ӹضϡ� */
        unsigned int  clkmasken                                : 16; /* bit[16-31]: clkenÿ������λ��ʹ��λ��
                                                                                    ֻ�е�clkmasken��Ӧ�ı���λΪ1'b1��clken��Ӧ�ı���λ�������á�clkmasken[0]����clken[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_MAIA_CLKEN_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_clkinen_sys_START                           (0)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_clkinen_sys_END                             (0)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_atclkoff_sys_n_START                        (1)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_atclkoff_sys_n_END                          (1)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_pclkdbg_to_a53_asyn_bri_clkoff_sys_n_START  (2)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_pclkdbg_to_a53_asyn_bri_clkoff_sys_n_END    (2)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_atclk_to_asyn_bri_clkoff_sys_n_START        (3)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_atclk_to_asyn_bri_clkoff_sys_n_END          (3)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_clkoff_sys_START                            (15)
#define SOC_CRGPERIPH_MAIA_CLKEN_a57_clkoff_sys_END                              (15)
#define SOC_CRGPERIPH_MAIA_CLKEN_clkmasken_START                                 (16)
#define SOC_CRGPERIPH_MAIA_CLKEN_clkmasken_END                                   (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_RSTEN_UNION
 �ṹ˵��  : MAIA_RSTEN �Ĵ����ṹ���塣��ַƫ����:0x1C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: A57 CLUSTER��ϵͳ��λʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_coresight_soft_rst_req : 1;  /* bit[0]    : A53 cluster�ڲ�coresight ϵͳ��λ���󣬸���Ч */
        unsigned int  a57_adb_asyn_bri_rst_req   : 1;  /* bit[1]    : A53 ADB�첽��ϵͳ��λ���󣬸���Ч */
        unsigned int  a57_npresetdbg_rst_req     : 1;  /* bit[2]    : Debug APB��CTI��CTM��λ���󣬵�ƽ��λ������Ч����Чʱ���ḴλPCLKDBGʱ�����debug�߼��� */
        unsigned int  reserved_0                 : 4;  /* bit[3-6]  : ������ */
        unsigned int  reserved_1                 : 4;  /* bit[7-10] : ������ */
        unsigned int  a57_core_rst_software_req  : 4;  /* bit[11-14]: ������λ���󣬵�ƽ��λ������Ч����Чʱ���Ḵλ�������߼�������core��NEON��VFP�� */
        unsigned int  a57_rst_software_req       : 1;  /* bit[15]   : A53MP������λ���󣬵�ƽ��λ������Ч */
        unsigned int  a57_core_por_rst_req       : 4;  /* bit[16-19]: �����ϵ縴λ���󣬵�ƽ��λ������Ч����Чʱ���Ḵλ���еĴ������߼�������core��NEON��VFP��debug��PTM��breakpoint��watchpoint��CLKʱ�����ȫ���߼��� */
        unsigned int  a57_hpm_cpu_rst_req        : 4;  /* bit[20-23]: cpu hpm�ϵ縴λ���󣬵�ƽ��λ������Ч */
        unsigned int  a57_hpm_scu_rst_req        : 1;  /* bit[24]   : scu hpm�ϵ縴λ���󣬵�ƽ��λ������Ч */
        unsigned int  reserved_2                 : 6;  /* bit[25-30]: ������ */
        unsigned int  a57_srst_req_en            : 1;  /* bit[31]   : CPU��ϵͳ������λ������
                                                                      0����Ч����
                                                                      1����λ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_coresight_soft_rst_req_START  (0)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_coresight_soft_rst_req_END    (0)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_adb_asyn_bri_rst_req_START    (1)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_adb_asyn_bri_rst_req_END      (1)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_npresetdbg_rst_req_START      (2)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_npresetdbg_rst_req_END        (2)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_core_rst_software_req_START   (11)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_core_rst_software_req_END     (14)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_rst_software_req_START        (15)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_rst_software_req_END          (15)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_core_por_rst_req_START        (16)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_core_por_rst_req_END          (19)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_hpm_cpu_rst_req_START         (20)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_hpm_cpu_rst_req_END           (23)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_hpm_scu_rst_req_START         (24)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_hpm_scu_rst_req_END           (24)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_srst_req_en_START             (31)
#define SOC_CRGPERIPH_MAIA_RSTEN_a57_srst_req_en_END               (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_RSTDIS_UNION
 �ṹ˵��  : MAIA_RSTDIS �Ĵ����ṹ���塣��ַƫ����:0x1C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: A57 CLUSTER��ϵͳ��λ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_coresight_soft_rst_req : 1;  /* bit[0]    : A57 cluster�ڲ�coresight ϵͳ��λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  a57_adb_asyn_bri_rst_req   : 1;  /* bit[1]    : A57 ADB�첽��ϵͳ��λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  a57_npresetdbg_rst_req     : 1;  /* bit[2]    : Debug APB��CTI��CTM��λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  reserved_0                 : 4;  /* bit[3-6]  : ������ */
        unsigned int  reserved_1                 : 4;  /* bit[7-10] : ������ */
        unsigned int  a57_core_rst_software_req  : 4;  /* bit[11-14]: ������λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  a57_rst_software_req       : 1;  /* bit[15]   : A53MP������λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  a57_core_por_rst_req       : 4;  /* bit[16-19]: �����ϵ縴λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  a57_hpm_cpu_rst_req        : 4;  /* bit[20-23]: cpu hpm�ϵ縴λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  a57_hpm_scu_rst_req        : 1;  /* bit[24]   : scu hpm�ϵ縴λ������
                                                                      0����Ч����
                                                                      1����λ������ */
        unsigned int  reserved_2                 : 6;  /* bit[25-30]: ������ */
        unsigned int  a57_srst_req_en            : 1;  /* bit[31]   : CPU��ϵͳ������λ������
                                                                      0����Ч����
                                                                      1����λ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_coresight_soft_rst_req_START  (0)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_coresight_soft_rst_req_END    (0)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_adb_asyn_bri_rst_req_START    (1)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_adb_asyn_bri_rst_req_END      (1)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_npresetdbg_rst_req_START      (2)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_npresetdbg_rst_req_END        (2)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_core_rst_software_req_START   (11)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_core_rst_software_req_END     (14)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_rst_software_req_START        (15)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_rst_software_req_END          (15)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_core_por_rst_req_START        (16)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_core_por_rst_req_END          (19)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_hpm_cpu_rst_req_START         (20)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_hpm_cpu_rst_req_END           (23)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_hpm_scu_rst_req_START         (24)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_hpm_scu_rst_req_END           (24)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_srst_req_en_START             (31)
#define SOC_CRGPERIPH_MAIA_RSTDIS_a57_srst_req_en_END               (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_RSTSTAT_UNION
 �ṹ˵��  : MAIA_RSTSTAT �Ĵ����ṹ���塣��ַƫ����:0x1CC����ֵ:0x800F0002�����:32
 �Ĵ���˵��: A57 CLUSTER��ϵͳ��λʹ��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_coresight_soft_rst_req : 1;  /* bit[0]    : A57 cluster�ڲ�coresight ϵͳ��λ״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  a57_adb_asyn_bri_rst_req   : 1;  /* bit[1]    : A57 ADB�첽��ϵͳ��λ״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  a57_npresetdbg_rst_req     : 1;  /* bit[2]    : Debug APB��CTI��CTM��λ״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  reserved_0                 : 4;  /* bit[3-6]  : ������ */
        unsigned int  reserved_1                 : 4;  /* bit[7-10] : ������ */
        unsigned int  a57_core_rst_software_req  : 4;  /* bit[11-14]: ������λʹ��״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  a57_rst_software_req       : 1;  /* bit[15]   : A53MP������λ״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  a57_core_por_rst_req       : 4;  /* bit[16-19]: �����ϵ縴λʹ��״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  a57_hpm_cpu_rst_req        : 4;  /* bit[20-23]: cpu hpm�ϵ縴λʹ��״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  a57_hpm_scu_rst_req        : 1;  /* bit[24]   : scu hpm�ϵ縴λʹ��״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
        unsigned int  reserved_2                 : 6;  /* bit[25-30]: ������ */
        unsigned int  a57_srst_req_en            : 1;  /* bit[31]   : CPU��ϵͳ������λʹ��״̬��
                                                                      0����λ��ʹ�ܣ�
                                                                      1����λʹ�ܣ� */
    } reg;
} SOC_CRGPERIPH_MAIA_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_coresight_soft_rst_req_START  (0)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_coresight_soft_rst_req_END    (0)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_adb_asyn_bri_rst_req_START    (1)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_adb_asyn_bri_rst_req_END      (1)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_npresetdbg_rst_req_START      (2)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_npresetdbg_rst_req_END        (2)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_core_rst_software_req_START   (11)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_core_rst_software_req_END     (14)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_rst_software_req_START        (15)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_rst_software_req_END          (15)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_core_por_rst_req_START        (16)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_core_por_rst_req_END          (19)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_hpm_cpu_rst_req_START         (20)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_hpm_cpu_rst_req_END           (23)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_hpm_scu_rst_req_START         (24)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_hpm_scu_rst_req_END           (24)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_srst_req_en_START             (31)
#define SOC_CRGPERIPH_MAIA_RSTSTAT_a57_srst_req_en_END               (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_ADBLPSTAT_UNION
 �ṹ˵��  : MAIA_ADBLPSTAT �Ĵ����ṹ���塣��ַƫ����:0x1D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: A57 CLUSTER ADB�͹��ļĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_d_pwrdnreqn : 1;  /* bit[0]   : ADB-400�첽���µ�����Ӧ���źţ�����Ч */
        unsigned int  a57_d_pwrdnackn : 1;  /* bit[1]   : ADB-400�첽���µ�����Ӧ���źţ�����Ч */
        unsigned int  a57_d_cactives  : 1;  /* bit[2]   : ָʾADB-400�첽�����Ƿ����л��transaction��
                                                          0���첽��������transaction�������
                                                          1���첽�����д��ڻ��transaction */
        unsigned int  reserved        : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_ADBLPSTAT_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_pwrdnreqn_START  (0)
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_pwrdnreqn_END    (0)
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_pwrdnackn_START  (1)
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_pwrdnackn_END    (1)
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_cactives_START   (2)
#define SOC_CRGPERIPH_MAIA_ADBLPSTAT_a57_d_cactives_END     (2)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_CTRL0_UNION
 �ṹ˵��  : MAIA_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x1D8����ֵ:0xFFF0F000�����:32
 �Ĵ���˵��: A57 CLUSTER�������üĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_pd_detect_clr       : 1;  /* bit[0]    : A57����̽��״̬���ָʾ�ź� */
        unsigned int  a57_pd_detect_start     : 1;  /* bit[1]    : A57����̽�⿪ʼָʾ�ź� */
        unsigned int  a57_set_acinactm_low    : 1;  /* bit[2]    : ACINACTM�����߼�bypass�ź� */
        unsigned int  a57_set_acinactm_high   : 1;  /* bit[3]    : ACINACTM�����߼�bypass�ź� */
        unsigned int  a57_dbgpwrdup           : 4;  /* bit[4-7]  : CPU���ϵ�ָʾ�ź� */
        unsigned int  a57_l2rstdisable        : 1;  /* bit[8]    : ��λ�׶ν�ֹL2 cache�Զ�invalidate�ź� */
        unsigned int  a57_l1rstdisable        : 1;  /* bit[9]    : ��λ�׶ν�ֹL1 cache�Զ�invalidate�ź� */
        unsigned int  reserved                : 2;  /* bit[10-11]: ������ */
        unsigned int  a57_broadcastcachemaint : 1;  /* bit[12]   : ʹ��cacheһ���Բ����Ƿ��㲥������cache��
                                                                   0��һ���Բ�������㲥������cache
                                                                   1��һ���Բ�����㲥������cache */
        unsigned int  a57_broadcastouter      : 1;  /* bit[13]   : �Ƿ�ʹ���ⲿshareable�����Ĺ㲥
                                                                   0��outer shareable�������㲥
                                                                   1��outer shareable������㲥 */
        unsigned int  a57_broadcastinner      : 1;  /* bit[14]   : �Ƿ�ʹ���ڲ�shareable�����Ĺ㲥
                                                                   0��inner shareable�������㲥
                                                                   1��inner shareable������㲥 */
        unsigned int  a57_sysbardisable       : 1;  /* bit[15]   : barriers�����Ƿ�㲥��ϵͳ����
                                                                   0��barriers������㲥��ϵͳ����
                                                                   1��barriers��������㲥��ϵͳ���� */
        unsigned int  a57_vinithi             : 4;  /* bit[16-19]: A53������ʽѡ��ÿbit��Ӧһ��core��
                                                                   0���ӵ�λ��ַ��0x00000000������
                                                                   1���Ӹ�λ��ַ��0xFFFF0000������ */
        unsigned int  a57_sei_n               : 4;  /* bit[20-23]: ����system error�ж������źţ���������Ч�� */
        unsigned int  a57_rei_n               : 4;  /* bit[24-27]: ����RAM error�ж������źţ���������Ч�� */
        unsigned int  a57_vsei_n              : 4;  /* bit[28-31]: ��������system error�ж������źţ���������Ч�� */
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL0_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_pd_detect_clr_START        (0)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_pd_detect_clr_END          (0)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_pd_detect_start_START      (1)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_pd_detect_start_END        (1)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_set_acinactm_low_START     (2)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_set_acinactm_low_END       (2)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_set_acinactm_high_START    (3)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_set_acinactm_high_END      (3)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_dbgpwrdup_START            (4)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_dbgpwrdup_END              (7)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_l2rstdisable_START         (8)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_l2rstdisable_END           (8)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_l1rstdisable_START         (9)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_l1rstdisable_END           (9)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastcachemaint_START  (12)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastcachemaint_END    (12)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastouter_START       (13)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastouter_END         (13)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastinner_START       (14)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_broadcastinner_END         (14)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_sysbardisable_START        (15)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_sysbardisable_END          (15)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_vinithi_START              (16)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_vinithi_END                (19)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_sei_n_START                (20)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_sei_n_END                  (23)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_rei_n_START                (24)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_rei_n_END                  (27)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_vsei_n_START               (28)
#define SOC_CRGPERIPH_MAIA_CTRL0_a57_vsei_n_END                 (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_CTRL1_UNION
 �ṹ˵��  : MAIA_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x1DC����ֵ:0x0000000B�����:32
 �Ĵ���˵��: A57 CLUSTER�������üĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_ctrl_apu     : 16; /* bit[0-15] : a57 CPU memory���� */
        unsigned int  mem_ctrl_s_a53cs : 16; /* bit[16-31]: a57 ETF ram�����źţ�ʹ��TSMC memory��bit�������£�
                                                            bit[0]��SLP
                                                            bit[1]��DSLP
                                                            bit[2]��SD
                                                            bit[15:3]��unused */
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL1_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL1_mem_ctrl_apu_START      (0)
#define SOC_CRGPERIPH_MAIA_CTRL1_mem_ctrl_apu_END        (15)
#define SOC_CRGPERIPH_MAIA_CTRL1_mem_ctrl_s_a53cs_START  (16)
#define SOC_CRGPERIPH_MAIA_CTRL1_mem_ctrl_s_a53cs_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_CTRL2_UNION
 �ṹ˵��  : MAIA_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x1E0����ֵ:0x01F1C020�����:32
 �Ĵ���˵��: A57 CLUSTER�������üĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_aa64naa32          : 4;  /* bit[0-3]  : ���˼Ĵ���λ����λʱ������
                                                                  0��AArch32��
                                                                  1��AArch64�� */
        unsigned int  a57_ret_ctrl_ret       : 3;  /* bit[4-6]  : A57MP noncpu������������ģʽ��memory�����źš�Bit�������£�
                                                                  bit[0]��SLP
                                                                  bit[1]��DSLP
                                                                  bit[2]��unused */
        unsigned int  a57_ret_ctrl_norm      : 3;  /* bit[7-9]  : A57MP noncpu������������ģʽ��memory�����źš�Bit�������£�
                                                                  bit[0]��SLP
                                                                  bit[1]��DSLP
                                                                  bit[2]��unused */
        unsigned int  a57_wfe_ret_en_l2      : 1;  /* bit[10]   : A57MP noncpu����WFE״̬���Զ�retentionʹ�� */
        unsigned int  a57_wfi_ret_en_l2      : 1;  /* bit[11]   : A57MP noncpu����WFI״̬���Զ�retentionʹ�� */
        unsigned int  a57_dyn_ret_en_l2      : 1;  /* bit[12]   : A57MP noncpu���ֶ�̬retentionȫ��ʹ�� */
        unsigned int  a57_l2flushreq         : 1;  /* bit[13]   : L2Ӳ��flush���� */
        unsigned int  a57_sys_cnt_en_dly     : 6;  /* bit[14-19]: A57 sysconter ����en�ӳ� */
        unsigned int  a57_ret_wait_cycle     : 6;  /* bit[20-25]: A57 L2 RAM�˳�ret״̬�ӳ� */
        unsigned int  a57_ret_wait_cycle_chg : 1;  /* bit[26]   : ��̬�޸ĵȴ�����ʱ�������Ĳ���ʹ���ź� */
        unsigned int  reserved               : 1;  /* bit[27]   : ������ */
        unsigned int  a57_pmusnapshotreq     : 4;  /* bit[28-31]: pmubug���� */
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL2_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_aa64naa32_START           (0)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_aa64naa32_END             (3)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_ctrl_ret_START        (4)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_ctrl_ret_END          (6)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_ctrl_norm_START       (7)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_ctrl_norm_END         (9)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_wfe_ret_en_l2_START       (10)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_wfe_ret_en_l2_END         (10)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_wfi_ret_en_l2_START       (11)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_wfi_ret_en_l2_END         (11)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_dyn_ret_en_l2_START       (12)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_dyn_ret_en_l2_END         (12)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_l2flushreq_START          (13)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_l2flushreq_END            (13)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_sys_cnt_en_dly_START      (14)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_sys_cnt_en_dly_END        (19)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_wait_cycle_START      (20)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_wait_cycle_END        (25)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_wait_cycle_chg_START  (26)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_ret_wait_cycle_chg_END    (26)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_pmusnapshotreq_START      (28)
#define SOC_CRGPERIPH_MAIA_CTRL2_a57_pmusnapshotreq_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_STAT_UNION
 �ṹ˵��  : MAIA_STAT �Ĵ����ṹ���塣��ַƫ����:0x1F4����ֵ:0x0000100F�����:32
 �Ĵ���˵��: A57 CLUSTER״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_standbywfi   : 4;  /* bit[0-3]  : ָʾCPU�Ƿ���WFI״̬ */
        unsigned int  a57_standbywfe   : 4;  /* bit[4-7]  : ָʾCPU�Ƿ���WFE״̬ */
        unsigned int  a57_smpen        : 4;  /* bit[8-11] : 0��Disables receiving of instruction cache and TLB maintenance operations. This is the reset 
                                                            value
                                                            1��Enables receiving of instruction cache and TLB maintenance operations */
        unsigned int  a57_standbywfil2 : 1;  /* bit[12]   : ָʾL2�Ƿ���WFI״̬ */
        unsigned int  a57_dbgack       : 1;  /* bit[13]   : A53 core����debug״̬���״ָ̬ʾ������Ч������һcore����debug״̬ʱ�����ź���Ч */
        unsigned int  a57_l2flushdone  : 1;  /* bit[14]   : L2Ӳ��flush����ɡ� */
        unsigned int  a57_idle_flag    : 1;  /* bit[15]   : a57idleָʾ״̬��Ϊ1��ʾidle��������tcxo */
        unsigned int  a57_sbgpwrupreq  : 4;  /* bit[16-19]: Processor powerup request:
                                                            0: No request for processor power up.
                                                            1: Request for processor power up. */
        unsigned int  a57_dbgnopwrdwn  : 4;  /* bit[20-23]: No powerdown request. On a powerdown request:
                                                            0: The SoC power controller powers down the processor.
                                                            1: The SoC power controller does not power down the processor */
        unsigned int  a57_snoop_cnt    : 6;  /* bit[24-29]: A53 snoop counter����ֵ */
        unsigned int  reserved         : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_STAT_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfi_START    (0)
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfi_END      (3)
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfe_START    (4)
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfe_END      (7)
#define SOC_CRGPERIPH_MAIA_STAT_a57_smpen_START         (8)
#define SOC_CRGPERIPH_MAIA_STAT_a57_smpen_END           (11)
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfil2_START  (12)
#define SOC_CRGPERIPH_MAIA_STAT_a57_standbywfil2_END    (12)
#define SOC_CRGPERIPH_MAIA_STAT_a57_dbgack_START        (13)
#define SOC_CRGPERIPH_MAIA_STAT_a57_dbgack_END          (13)
#define SOC_CRGPERIPH_MAIA_STAT_a57_l2flushdone_START   (14)
#define SOC_CRGPERIPH_MAIA_STAT_a57_l2flushdone_END     (14)
#define SOC_CRGPERIPH_MAIA_STAT_a57_idle_flag_START     (15)
#define SOC_CRGPERIPH_MAIA_STAT_a57_idle_flag_END       (15)
#define SOC_CRGPERIPH_MAIA_STAT_a57_sbgpwrupreq_START   (16)
#define SOC_CRGPERIPH_MAIA_STAT_a57_sbgpwrupreq_END     (19)
#define SOC_CRGPERIPH_MAIA_STAT_a57_dbgnopwrdwn_START   (20)
#define SOC_CRGPERIPH_MAIA_STAT_a57_dbgnopwrdwn_END     (23)
#define SOC_CRGPERIPH_MAIA_STAT_a57_snoop_cnt_START     (24)
#define SOC_CRGPERIPH_MAIA_STAT_a57_snoop_cnt_END       (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_STAT_1_UNION
 �ṹ˵��  : MAIA_STAT_1 �Ĵ����ṹ���塣��ַƫ����:0x1F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: A57 CLUSTER״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_pmusnapshotack : 4;  /* bit[0-3] : a57 pmusnapshotack */
        unsigned int  reserved           : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_STAT_1_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_STAT_1_a57_pmusnapshotack_START  (0)
#define SOC_CRGPERIPH_MAIA_STAT_1_a57_pmusnapshotack_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CORESIGHTSTAT_UNION
 �ṹ˵��  : CORESIGHTSTAT �Ĵ����ṹ���塣��ַƫ����:0x200����ֵ:0x00000000�����:32
 �Ĵ���˵��: core sight״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_CRGPERIPH_CORESIGHTSTAT_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CORESIGHTLPSTAT_UNION
 �ṹ˵��  : CORESIGHTLPSTAT �Ĵ����ṹ���塣��ַƫ����:0x204����ֵ:0x00000003�����:32
 �Ĵ���˵��: core sight�͹��ļĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  csysreq_etr_lpi : 1;  /* bit[0]   : ETR AXI master�ӿ�ֹͣ���󣬵���Ч */
        unsigned int  csysack_etr_lpi : 1;  /* bit[1]   : ETR AXI master�ӿ�ֹͣӦ�𣬵���Ч */
        unsigned int  cactive_etr_lpi : 1;  /* bit[2]   : ʼ��Ϊ�ͣ�ָʾ�͹������󱻽��� */
        unsigned int  reserved        : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_CRGPERIPH_CORESIGHTLPSTAT_UNION;
#endif
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_csysreq_etr_lpi_START  (0)
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_csysreq_etr_lpi_END    (0)
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_csysack_etr_lpi_START  (1)
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_csysack_etr_lpi_END    (1)
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_cactive_etr_lpi_START  (2)
#define SOC_CRGPERIPH_CORESIGHTLPSTAT_cactive_etr_lpi_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CORESIGHTCTRL0_UNION
 �ṹ˵��  : CORESIGHTCTRL0 �Ĵ����ṹ���塣��ַƫ����:0x208����ֵ:0x00000000�����:32
 �Ĵ���˵��: core sight�������üĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_ctrl_s_cssys : 16; /* bit[0-15] : ETF ram�����źţ�ʹ��TSMC memory��bit�������£�
                                                            bit[0]��SLP
                                                            bit[1]��DSLP
                                                            bit[2]��SD
                                                            bit[15:3]��unused */
        unsigned int  reserved         : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_CRGPERIPH_CORESIGHTCTRL0_UNION;
#endif
#define SOC_CRGPERIPH_CORESIGHTCTRL0_mem_ctrl_s_cssys_START  (0)
#define SOC_CRGPERIPH_CORESIGHTCTRL0_mem_ctrl_s_cssys_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CORESIGHTETFINT_UNION
 �ṹ˵��  : CORESIGHTETFINT �Ĵ����ṹ���塣��ַƫ����:0x20C����ֵ:0x00000000�����:32
 �Ĵ���˵��: core sight ETF�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  etf_a53_1_full : 1;  /* bit[0]   : ETF A53 CLUSTER1 FULLָʾ������Ч�� */
        unsigned int  etf_a53_0_full : 1;  /* bit[1]   : ETF A53 CLUSTER0 FULLָʾ������Ч�� */
        unsigned int  etf_top_full   : 1;  /* bit[2]   : ETF TOP FULLָʾ������Ч�� */
        unsigned int  reserved       : 29; /* bit[3-31]: ��������etf_top_full��etf_a53_0_full��etf_a53_1_full�������ж�intr_etf_full����ͨ��д�üĴ���д�塣 */
    } reg;
} SOC_CRGPERIPH_CORESIGHTETFINT_UNION;
#endif
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_a53_1_full_START  (0)
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_a53_1_full_END    (0)
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_a53_0_full_START  (1)
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_a53_0_full_END    (1)
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_top_full_START    (2)
#define SOC_CRGPERIPH_CORESIGHTETFINT_etf_top_full_END      (2)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CORESIGHTETRINT_UNION
 �ṹ˵��  : CORESIGHTETRINT �Ĵ����ṹ���塣��ַƫ����:0x210����ֵ:0x00000000�����:32
 �Ĵ���˵��: core sight ETR�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  etr_top_full         : 1;  /* bit[0]   : ETR FULLָʾ������Ч�� */
        unsigned int  intr_a53_0_core0_gic : 1;  /* bit[1]   : a53_0_core0 ԭʼgic�жϼĴ� */
        unsigned int  intr_a53_0_core1_gic : 1;  /* bit[2]   : a53_0_core1 ԭʼgic�жϼĴ� */
        unsigned int  intr_a53_0_core2_gic : 1;  /* bit[3]   : a53_0_core2 ԭʼgic�жϼĴ� */
        unsigned int  intr_a53_0_core3_gic : 1;  /* bit[4]   : a53_0_core3 ԭʼgic�жϼĴ� */
        unsigned int  intr_a53_1_core0_gic : 1;  /* bit[5]   : a53_1_core0 ԭʼgic�жϼĴ� */
        unsigned int  intr_a53_1_core1_gic : 1;  /* bit[6]   : a53_1_core1 ԭʼgic�жϼĴ� */
        unsigned int  intr_a53_1_core2_gic : 1;  /* bit[7]   : a53_1_core2 ԭʼgic�жϼĴ� */
        unsigned int  intr_a53_1_core3_gic : 1;  /* bit[8]   : a53_1_core3 ԭʼgic�жϼĴ� */
        unsigned int  reserved             : 23; /* bit[9-31]: ��������etr_top_full�������ж�intr_etr_full��д�塣 */
    } reg;
} SOC_CRGPERIPH_CORESIGHTETRINT_UNION;
#endif
#define SOC_CRGPERIPH_CORESIGHTETRINT_etr_top_full_START          (0)
#define SOC_CRGPERIPH_CORESIGHTETRINT_etr_top_full_END            (0)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core0_gic_START  (1)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core0_gic_END    (1)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core1_gic_START  (2)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core1_gic_END    (2)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core2_gic_START  (3)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core2_gic_END    (3)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core3_gic_START  (4)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_0_core3_gic_END    (4)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core0_gic_START  (5)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core0_gic_END    (5)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core1_gic_START  (6)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core1_gic_END    (6)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core2_gic_START  (7)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core2_gic_END    (7)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core3_gic_START  (8)
#define SOC_CRGPERIPH_CORESIGHTETRINT_intr_a53_1_core3_gic_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CCI400STAT1_UNION
 �ṹ˵��  : CCI400STAT1 �Ĵ����ṹ���塣��ַƫ����:0x21C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CCI400״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rs_awvalid_s3        : 1;  /* bit[0]    : S3�ӿڵ�awvalid״̬��
                                                                0��awvalid��Ч��
                                                                1��awvalid��Ч�� */
        unsigned int  rs_arvalid_s3        : 1;  /* bit[1]    : S3�ӿڵ�arvalid״̬��
                                                                0��arvalid��Ч��
                                                                1��arvalid��Ч�� */
        unsigned int  rs_awvalid_s4        : 1;  /* bit[2]    : S4�ӿڵ�awvalid״̬��
                                                                0��awvalid��Ч��
                                                                1��awvalid��Ч�� */
        unsigned int  rs_arvalid_s4        : 1;  /* bit[3]    : S4�ӿڵ�arvalid״̬��
                                                                0��arvalid��Ч��
                                                                1��arvalid��Ч�� */
        unsigned int  cactive_asi_s3       : 1;  /* bit[4]    : S3��ASIģ���Ƿ��в����ڴ���
                                                                0���в�����
                                                                1���޲����� */
        unsigned int  cactive_asi_s4       : 1;  /* bit[5]    : S4��ASIģ���Ƿ��в����ڴ���
                                                                0���в�����
                                                                1���޲����� */
        unsigned int  dvm_complete_expect1 : 2;  /* bit[6-7]  : ��һ��dvm complete��master��Ϣ������dvm complete������ע��dvm complete��ɺ����Ϣ�������
                                                                0������״̬���޷���dvm complete��master��Ϣ��
                                                                1��dvm complete������A53��
                                                                2��dvm complete������MAIA��
                                                                3��������  */
        unsigned int  dvm_complete_expect2 : 2;  /* bit[8-9]  : �ڶ���dvm complete��master��Ϣ������dvm complete������ע��dvm complete��ɺ����Ϣ�������
                                                                0������״̬���޷���dvm complete��master��Ϣ��
                                                                1��dvm complete������A53��
                                                                2��dvm complete������MAIA��
                                                                3��������  */
        unsigned int  dvm_complete_expect3 : 2;  /* bit[10-11]: ������dvm complete��master��Ϣ������dvm complete������ע��dvm complete��ɺ����Ϣ�������
                                                                0������״̬���޷���dvm complete��master��Ϣ��
                                                                1��dvm complete������A53��
                                                                2��dvm complete������MAIA��
                                                                3��������  */
        unsigned int  dvm_complete_expect4 : 2;  /* bit[12-13]: ������dvm complete��master��Ϣ������dvm complete������ע��dvm complete��ɺ����Ϣ�������
                                                                0������״̬���޷���dvm complete��master��Ϣ��
                                                                1��dvm complete������A53��
                                                                2��dvm complete������MAIA��
                                                                3�������� */
        unsigned int  dvm_complete_expect5 : 2;  /* bit[14-15]: ������dvm complete��master��Ϣ������dvm complete������ע��dvm complete��ɺ����Ϣ�������
                                                                0������״̬���޷���dvm complete��master��Ϣ��
                                                                1��dvm complete������A53��
                                                                2��dvm complete������MAIA��
                                                                3��������  */
        unsigned int  srb_entry_expect_cr3 : 1;  /* bit[16]   : A53��CRͨ�����Ƿ���δ��ɵ����
                                                                0����δ��ɵ����
                                                                1����δ��ɵ����  */
        unsigned int  srb_entry_expect_cd3 : 1;  /* bit[17]   : A53��CDͨ�����Ƿ���δ��ɵ����
                                                                0����δ��ɵ����
                                                                1����δ��ɵ���� */
        unsigned int  srb_entry_expect_cr4 : 1;  /* bit[18]   : MAIA��CRͨ�����Ƿ���δ��ɵ����
                                                                0����δ��ɵ����
                                                                1����δ��ɵ���� */
        unsigned int  srb_entry_expect_cd4 : 1;  /* bit[19]   : MAIA��CDͨ�����Ƿ���δ��ɵ����
                                                                0����δ��ɵ����
                                                                1����δ��ɵ���� */
        unsigned int  dvm_scoreboard1      : 2;  /* bit[20-21]: ��һ��dvm sync�������״ָ̬ʾ������dvm sync������
                                                                0��A53��MAIA����δ��ɵ�dvm sync��
                                                                1��A53��δ��ɵ�dvm sync��
                                                                2��MAIA��δ��ɵ�dvm sync��
                                                                3��A53��MAIA����δ��ɵ�dvm sync�� */
        unsigned int  dvm_scoreboard2      : 2;  /* bit[22-23]: �ڶ���dvm sync�������״ָ̬ʾ������dvm sync������
                                                                0��A53��MAIA����δ��ɵ�dvm sync��
                                                                1��A53��δ��ɵ�dvm sync��
                                                                2��MAIA��δ��ɵ�dvm sync��
                                                                3��A53��MAIA����δ��ɵ�dvm sync�� */
        unsigned int  dvm_scoreboard3      : 2;  /* bit[24-25]: ������dvm sync�������״ָ̬ʾ������dvm sync������
                                                                0��A53��MAIA����δ��ɵ�dvm sync��
                                                                1��A53��δ��ɵ�dvm sync��
                                                                2��MAIA��δ��ɵ�dvm sync��
                                                                3��A53��MAIA����δ��ɵ�dvm sync�� */
        unsigned int  dvm_scoreboard4      : 2;  /* bit[26-27]: ������dvm sync�������״ָ̬ʾ������dvm sync������
                                                                0��A53��MAIA����δ��ɵ�dvm sync��
                                                                1��A53��δ��ɵ�dvm sync��
                                                                2��MAIA��δ��ɵ�dvm sync��
                                                                3��A53��MAIA����δ��ɵ�dvm sync�� */
        unsigned int  dvm_scoreboard5      : 2;  /* bit[28-29]: ������dvm sync�������״ָ̬ʾ������dvm sync������
                                                                0��A53��MAIA����δ��ɵ�dvm sync��
                                                                1��A53��δ��ɵ�dvm sync��
                                                                2��MAIA��δ��ɵ�dvm sync��
                                                                3��A53��MAIA����δ��ɵ�dvm sync�� */
        unsigned int  reserved             : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_CRGPERIPH_CCI400STAT1_UNION;
#endif
#define SOC_CRGPERIPH_CCI400STAT1_rs_awvalid_s3_START         (0)
#define SOC_CRGPERIPH_CCI400STAT1_rs_awvalid_s3_END           (0)
#define SOC_CRGPERIPH_CCI400STAT1_rs_arvalid_s3_START         (1)
#define SOC_CRGPERIPH_CCI400STAT1_rs_arvalid_s3_END           (1)
#define SOC_CRGPERIPH_CCI400STAT1_rs_awvalid_s4_START         (2)
#define SOC_CRGPERIPH_CCI400STAT1_rs_awvalid_s4_END           (2)
#define SOC_CRGPERIPH_CCI400STAT1_rs_arvalid_s4_START         (3)
#define SOC_CRGPERIPH_CCI400STAT1_rs_arvalid_s4_END           (3)
#define SOC_CRGPERIPH_CCI400STAT1_cactive_asi_s3_START        (4)
#define SOC_CRGPERIPH_CCI400STAT1_cactive_asi_s3_END          (4)
#define SOC_CRGPERIPH_CCI400STAT1_cactive_asi_s4_START        (5)
#define SOC_CRGPERIPH_CCI400STAT1_cactive_asi_s4_END          (5)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect1_START  (6)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect1_END    (7)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect2_START  (8)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect2_END    (9)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect3_START  (10)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect3_END    (11)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect4_START  (12)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect4_END    (13)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect5_START  (14)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_complete_expect5_END    (15)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cr3_START  (16)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cr3_END    (16)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cd3_START  (17)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cd3_END    (17)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cr4_START  (18)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cr4_END    (18)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cd4_START  (19)
#define SOC_CRGPERIPH_CCI400STAT1_srb_entry_expect_cd4_END    (19)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard1_START       (20)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard1_END         (21)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard2_START       (22)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard2_END         (23)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard3_START       (24)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard3_END         (25)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard4_START       (26)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard4_END         (27)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard5_START       (28)
#define SOC_CRGPERIPH_CCI400STAT1_dvm_scoreboard5_END         (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_ADB400STAT_UNION
 �ṹ˵��  : ADB400STAT �Ĵ����ṹ���塣��ַƫ����:0x220����ֵ:0x00000000�����:32
 �Ĵ���˵��: ADB400״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cactivem_adb400_a53_0 : 1;  /* bit[0]   : indicates if there is still an transaction in the bridge */
        unsigned int  cactivem_adb400_a53_1 : 1;  /* bit[1]   : indicates if there is still an transaction in the bridge */
        unsigned int  cactivem_adb400_g3d_0 : 1;  /* bit[2]   : indicates if there is still an transaction in the bridge */
        unsigned int  cactivem_adb400_g3d_1 : 1;  /* bit[3]   : indicates if there is still an transaction in the bridge */
        unsigned int  reserved              : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_CRGPERIPH_ADB400STAT_UNION;
#endif
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_a53_0_START  (0)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_a53_0_END    (0)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_a53_1_START  (1)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_a53_1_END    (1)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_g3d_0_START  (2)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_g3d_0_END    (2)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_g3d_1_START  (3)
#define SOC_CRGPERIPH_ADB400STAT_cactivem_adb400_g3d_1_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CCI400CTRL0_UNION
 �ṹ˵��  : CCI400CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x228����ֵ:0x0000E000�����:32
 �Ĵ���˵��: CCI400�������üĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0         : 10; /* bit[0-9]  : ������ */
        unsigned int  bufferableoverride : 3;  /* bit[10-12]: ���� AWCACHE[0]��ARCACHE[0] �����Ϊnon-bufferable��һ��bit��Ӧһ��master�ӿ� */
        unsigned int  barrierterminate   : 3;  /* bit[13-15]: barrier������terminate���ͻ��Ǵ������ͣ�һ��bit��Ӧһ��master�ӿ� */
        unsigned int  reserved_1         : 13; /* bit[16-28]: ������ */
        unsigned int  striping_granule   : 3;  /* bit[29-31]: ����cci��֯���� */
    } reg;
} SOC_CRGPERIPH_CCI400CTRL0_UNION;
#endif
#define SOC_CRGPERIPH_CCI400CTRL0_bufferableoverride_START  (10)
#define SOC_CRGPERIPH_CCI400CTRL0_bufferableoverride_END    (12)
#define SOC_CRGPERIPH_CCI400CTRL0_barrierterminate_START    (13)
#define SOC_CRGPERIPH_CCI400CTRL0_barrierterminate_END      (15)
#define SOC_CRGPERIPH_CCI400CTRL0_striping_granule_START    (29)
#define SOC_CRGPERIPH_CCI400CTRL0_striping_granule_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CCI400CTRL1_UNION
 �ṹ˵��  : CCI400CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x22C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CCI400�������üĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0           : 26; /* bit[0-25] : ������ */
        unsigned int  cci_status_sample_en : 1;  /* bit[26]   : CCI�ڲ��źŹ۲��Ƿ�ʹ�ܣ�1Ϊʹ�� */
        unsigned int  ecorevnum            : 4;  /* bit[27-30]: ����ECOʱ��CCI�ڲ��Ĵ�������ECO�汾���м�¼�� */
        unsigned int  reserved_1           : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_CRGPERIPH_CCI400CTRL1_UNION;
#endif
#define SOC_CRGPERIPH_CCI400CTRL1_cci_status_sample_en_START  (26)
#define SOC_CRGPERIPH_CCI400CTRL1_cci_status_sample_en_END    (26)
#define SOC_CRGPERIPH_CCI400CTRL1_ecorevnum_START             (27)
#define SOC_CRGPERIPH_CCI400CTRL1_ecorevnum_END               (30)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_CCI400STAT_UNION
 �ṹ˵��  : CCI400STAT �Ĵ����ṹ���塣��ַƫ����:0x230����ֵ:0x00000000�����:32
 �Ĵ���˵��: CCI400״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  activem0 : 1;  /* bit[0]   : clock gating�����������ⲿ״̬�����������͹��Ŀ���ʹ�� */
        unsigned int  activem1 : 1;  /* bit[1]   : clock gating�����������ⲿ״̬�����������͹��Ŀ���ʹ�� */
        unsigned int  activem2 : 1;  /* bit[2]   : clock gating�����������ⲿ״̬�����������͹��Ŀ���ʹ�� */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_CRGPERIPH_CCI400STAT_UNION;
#endif
#define SOC_CRGPERIPH_CCI400STAT_activem0_START  (0)
#define SOC_CRGPERIPH_CCI400STAT_activem0_END    (0)
#define SOC_CRGPERIPH_CCI400STAT_activem1_START  (1)
#define SOC_CRGPERIPH_CCI400STAT_activem1_END    (1)
#define SOC_CRGPERIPH_CCI400STAT_activem2_START  (2)
#define SOC_CRGPERIPH_CCI400STAT_activem2_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_G3D_0_ADBLPSTAT_UNION
 �ṹ˵��  : G3D_0_ADBLPSTAT �Ĵ����ṹ���塣��ַƫ����:0x234����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D ADB0�͹��ļĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_d_pwrdnreqn : 1;  /* bit[0]   : ADB-400�첽���µ�����Ӧ���źţ�����Ч */
        unsigned int  g3d_d_pwrdnackn : 1;  /* bit[1]   : ADB-400�첽���µ�����Ӧ���źţ�����Ч */
        unsigned int  g3d_d_cactives  : 1;  /* bit[2]   : ָʾADB-400�첽�����Ƿ����л��transaction��
                                                          0���첽��������transaction�������
                                                          1���첽�����д��ڻ��transaction */
        unsigned int  reserved        : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_CRGPERIPH_G3D_0_ADBLPSTAT_UNION;
#endif
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_pwrdnreqn_START  (0)
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_pwrdnreqn_END    (0)
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_pwrdnackn_START  (1)
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_pwrdnackn_END    (1)
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_cactives_START   (2)
#define SOC_CRGPERIPH_G3D_0_ADBLPSTAT_g3d_d_cactives_END     (2)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_G3D_1_ADBLPSTAT_UNION
 �ṹ˵��  : G3D_1_ADBLPSTAT �Ĵ����ṹ���塣��ַƫ����:0x238����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D ADB1�͹��ļĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_d_pwrdnreqn : 1;  /* bit[0]   : ADB-400�첽���µ�����Ӧ���źţ�����Ч */
        unsigned int  g3d_d_pwrdnackn : 1;  /* bit[1]   : ADB-400�첽���µ�����Ӧ���źţ�����Ч */
        unsigned int  g3d_d_cactives  : 1;  /* bit[2]   : ָʾADB-400�첽�����Ƿ����л��transaction��
                                                          0���첽��������transaction�������
                                                          1���첽�����д��ڻ��transaction */
        unsigned int  reserved        : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_CRGPERIPH_G3D_1_ADBLPSTAT_UNION;
#endif
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_pwrdnreqn_START  (0)
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_pwrdnreqn_END    (0)
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_pwrdnackn_START  (1)
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_pwrdnackn_END    (1)
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_cactives_START   (2)
#define SOC_CRGPERIPH_G3D_1_ADBLPSTAT_g3d_d_cactives_END     (2)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_IPCLKRST_BYPASS0_UNION
 �ṹ˵��  : IPCLKRST_BYPASS0 �Ĵ����ṹ���塣��ַƫ����:0x240����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����IP����������byapss���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vcodec_clkrst_bypass  : 1;  /* bit[0] : ����������byapss���ƣ�
                                                              0��bypass��Ч��
                                                              1��bypass��Ч�� */
        unsigned int  pctrl_clkrst_bypass   : 1;  /* bit[1] :  */
        unsigned int  pwm_clkrst_bypass     : 1;  /* bit[2] :  */
        unsigned int  reserved              : 1;  /* bit[3] : ������ */
        unsigned int  wd0_clkrst_bypass     : 1;  /* bit[4] :  */
        unsigned int  wd1_clkrst_bypass     : 1;  /* bit[5] :  */
        unsigned int  gpio0_clkrst_bypass   : 1;  /* bit[6] :  */
        unsigned int  gpio1_clkrst_bypass   : 1;  /* bit[7] :  */
        unsigned int  gpio2_clkrst_bypass   : 1;  /* bit[8] :  */
        unsigned int  gpio3_clkrst_bypass   : 1;  /* bit[9] :  */
        unsigned int  gpio4_clkrst_bypass   : 1;  /* bit[10]:  */
        unsigned int  gpio5_clkrst_bypass   : 1;  /* bit[11]:  */
        unsigned int  gpio6_clkrst_bypass   : 1;  /* bit[12]:  */
        unsigned int  gpio7_clkrst_bypass   : 1;  /* bit[13]:  */
        unsigned int  gpio8_clkrst_bypass   : 1;  /* bit[14]:  */
        unsigned int  gpio9_clkrst_bypass   : 1;  /* bit[15]:  */
        unsigned int  gpio10_clkrst_bypass  : 1;  /* bit[16]:  */
        unsigned int  gpio11_clkrst_bypass  : 1;  /* bit[17]:  */
        unsigned int  gpio12_clkrst_bypass  : 1;  /* bit[18]:  */
        unsigned int  gpio13_clkrst_bypass  : 1;  /* bit[19]:  */
        unsigned int  gpio14_clkrst_bypass  : 1;  /* bit[20]:  */
        unsigned int  gpio15_clkrst_bypass  : 1;  /* bit[21]:  */
        unsigned int  gpio16_clkrst_bypass  : 1;  /* bit[22]:  */
        unsigned int  gpio17_clkrst_bypass  : 1;  /* bit[23]:  */
        unsigned int  gpio18_clkrst_bypass  : 1;  /* bit[24]:  */
        unsigned int  gpio19_clkrst_bypass  : 1;  /* bit[25]:  */
        unsigned int  gpio20_clkrst_bypass  : 1;  /* bit[26]:  */
        unsigned int  gpio21_clkrst_bypass  : 1;  /* bit[27]:  */
        unsigned int  timer9_clkrst_bypass  : 1;  /* bit[28]:  */
        unsigned int  timer10_clkrst_bypass : 1;  /* bit[29]:  */
        unsigned int  timer11_clkrst_bypass : 1;  /* bit[30]:  */
        unsigned int  timer12_clkrst_bypass : 1;  /* bit[31]:  */
    } reg;
} SOC_CRGPERIPH_IPCLKRST_BYPASS0_UNION;
#endif
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_vcodec_clkrst_bypass_START   (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_vcodec_clkrst_bypass_END     (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_pctrl_clkrst_bypass_START    (1)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_pctrl_clkrst_bypass_END      (1)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_pwm_clkrst_bypass_START      (2)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_pwm_clkrst_bypass_END        (2)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_wd0_clkrst_bypass_START      (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_wd0_clkrst_bypass_END        (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_wd1_clkrst_bypass_START      (5)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_wd1_clkrst_bypass_END        (5)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio0_clkrst_bypass_START    (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio0_clkrst_bypass_END      (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio1_clkrst_bypass_START    (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio1_clkrst_bypass_END      (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio2_clkrst_bypass_START    (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio2_clkrst_bypass_END      (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio3_clkrst_bypass_START    (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio3_clkrst_bypass_END      (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio4_clkrst_bypass_START    (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio4_clkrst_bypass_END      (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio5_clkrst_bypass_START    (11)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio5_clkrst_bypass_END      (11)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio6_clkrst_bypass_START    (12)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio6_clkrst_bypass_END      (12)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio7_clkrst_bypass_START    (13)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio7_clkrst_bypass_END      (13)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio8_clkrst_bypass_START    (14)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio8_clkrst_bypass_END      (14)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio9_clkrst_bypass_START    (15)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio9_clkrst_bypass_END      (15)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio10_clkrst_bypass_START   (16)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio10_clkrst_bypass_END     (16)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio11_clkrst_bypass_START   (17)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio11_clkrst_bypass_END     (17)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio12_clkrst_bypass_START   (18)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio12_clkrst_bypass_END     (18)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio13_clkrst_bypass_START   (19)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio13_clkrst_bypass_END     (19)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio14_clkrst_bypass_START   (20)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio14_clkrst_bypass_END     (20)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio15_clkrst_bypass_START   (21)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio15_clkrst_bypass_END     (21)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio16_clkrst_bypass_START   (22)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio16_clkrst_bypass_END     (22)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio17_clkrst_bypass_START   (23)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio17_clkrst_bypass_END     (23)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio18_clkrst_bypass_START   (24)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio18_clkrst_bypass_END     (24)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio19_clkrst_bypass_START   (25)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio19_clkrst_bypass_END     (25)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio20_clkrst_bypass_START   (26)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio20_clkrst_bypass_END     (26)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio21_clkrst_bypass_START   (27)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_gpio21_clkrst_bypass_END     (27)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer9_clkrst_bypass_START   (28)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer9_clkrst_bypass_END     (28)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer10_clkrst_bypass_START  (29)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer10_clkrst_bypass_END    (29)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer11_clkrst_bypass_START  (30)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer11_clkrst_bypass_END    (30)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer12_clkrst_bypass_START  (31)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS0_timer12_clkrst_bypass_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_IPCLKRST_BYPASS1_UNION
 �ṹ˵��  : IPCLKRST_BYPASS1 �Ĵ����ṹ���塣��ַƫ����:0x244����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����IP����������byapss���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tzpc_clkrst_bypass     : 1;  /* bit[0] : ����������byapss���ƣ�
                                                               0��bypass��Ч��
                                                               1��bypass��Ч�� */
        unsigned int  ipc0_clkrst_bypass     : 1;  /* bit[1] :  */
        unsigned int  ipc1_clkrst_bypass     : 1;  /* bit[2] :  */
        unsigned int  ioc_clkrst_bypass      : 1;  /* bit[3] :  */
        unsigned int  codecssi_clkrst_bypass : 1;  /* bit[4] :  */
        unsigned int  hkadcssi_clkrst_bypass : 1;  /* bit[5] :  */
        unsigned int  memrep_clkrst_bypass   : 1;  /* bit[6] :  */
        unsigned int  ipc_mdm_clkrst_bypass  : 1;  /* bit[7] :  */
        unsigned int  uart0_clkrst_bypass    : 1;  /* bit[8] :  */
        unsigned int  uart1_clkrst_bypass    : 1;  /* bit[9] :  */
        unsigned int  uart2_clkrst_bypass    : 1;  /* bit[10]:  */
        unsigned int  reserved_0             : 1;  /* bit[11]: ������ */
        unsigned int  uart4_clkrst_bypass    : 1;  /* bit[12]:  */
        unsigned int  uart5_clkrst_bypass    : 1;  /* bit[13]:  */
        unsigned int  reserved_1             : 1;  /* bit[14]: ������ */
        unsigned int  spi1_clkrst_bypass     : 1;  /* bit[15]:  */
        unsigned int  reserved_2             : 1;  /* bit[16]: ������ */
        unsigned int  reserved_3             : 1;  /* bit[17]: ������ */
        unsigned int  reserved_4             : 1;  /* bit[18]: ������ */
        unsigned int  i2c3_clkrst_bypass     : 1;  /* bit[19]:  */
        unsigned int  i2c4_clkrst_bypass     : 1;  /* bit[20]:  */
        unsigned int  dmac_clkrst_bypass     : 1;  /* bit[21]:  */
        unsigned int  emmc0_clkrst_bypass    : 1;  /* bit[22]:  */
        unsigned int  emmc1_clkrst_bypass    : 1;  /* bit[23]:  */
        unsigned int  sd_clkrst_bypass       : 1;  /* bit[24]:  */
        unsigned int  sdio0_clkrst_bypass    : 1;  /* bit[25]:  */
        unsigned int  socp_clkrst_bypass     : 1;  /* bit[26]:  */
        unsigned int  usb3otg_clkrst_bypass  : 1;  /* bit[27]:  */
        unsigned int  isp_clkrst_bypass      : 1;  /* bit[28]:  */
        unsigned int  dss_clkrst_bypass      : 1;  /* bit[29]:  */
        unsigned int  reserved_5             : 1;  /* bit[30]: ������ */
        unsigned int  reserved_6             : 1;  /* bit[31]: ������ */
    } reg;
} SOC_CRGPERIPH_IPCLKRST_BYPASS1_UNION;
#endif
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_tzpc_clkrst_bypass_START      (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_tzpc_clkrst_bypass_END        (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc0_clkrst_bypass_START      (1)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc0_clkrst_bypass_END        (1)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc1_clkrst_bypass_START      (2)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc1_clkrst_bypass_END        (2)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ioc_clkrst_bypass_START       (3)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ioc_clkrst_bypass_END         (3)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_codecssi_clkrst_bypass_START  (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_codecssi_clkrst_bypass_END    (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_hkadcssi_clkrst_bypass_START  (5)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_hkadcssi_clkrst_bypass_END    (5)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_memrep_clkrst_bypass_START    (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_memrep_clkrst_bypass_END      (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc_mdm_clkrst_bypass_START   (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_ipc_mdm_clkrst_bypass_END     (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart0_clkrst_bypass_START     (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart0_clkrst_bypass_END       (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart1_clkrst_bypass_START     (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart1_clkrst_bypass_END       (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart2_clkrst_bypass_START     (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart2_clkrst_bypass_END       (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart4_clkrst_bypass_START     (12)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart4_clkrst_bypass_END       (12)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart5_clkrst_bypass_START     (13)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_uart5_clkrst_bypass_END       (13)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_spi1_clkrst_bypass_START      (15)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_spi1_clkrst_bypass_END        (15)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_i2c3_clkrst_bypass_START      (19)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_i2c3_clkrst_bypass_END        (19)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_i2c4_clkrst_bypass_START      (20)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_i2c4_clkrst_bypass_END        (20)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_dmac_clkrst_bypass_START      (21)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_dmac_clkrst_bypass_END        (21)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_emmc0_clkrst_bypass_START     (22)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_emmc0_clkrst_bypass_END       (22)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_emmc1_clkrst_bypass_START     (23)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_emmc1_clkrst_bypass_END       (23)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_sd_clkrst_bypass_START        (24)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_sd_clkrst_bypass_END          (24)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_sdio0_clkrst_bypass_START     (25)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_sdio0_clkrst_bypass_END       (25)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_socp_clkrst_bypass_START      (26)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_socp_clkrst_bypass_END        (26)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_usb3otg_clkrst_bypass_START   (27)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_usb3otg_clkrst_bypass_END     (27)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_isp_clkrst_bypass_START       (28)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_isp_clkrst_bypass_END         (28)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_dss_clkrst_bypass_START       (29)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS1_dss_clkrst_bypass_END         (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_IPCLKRST_BYPASS2_UNION
 �ṹ˵��  : IPCLKRST_BYPASS2 �Ĵ����ṹ���塣��ַƫ����:0x248����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����IP����������byapss���ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_clkrst_bypass           : 1;  /* bit[0]    : ����������byapss���ƣ�
                                                                       0��bypass��Ч��
                                                                       1��bypass��Ч�� */
        unsigned int  reserved_0                  : 1;  /* bit[1]    : ������ */
        unsigned int  reserved_1                  : 1;  /* bit[2]    : ������ */
        unsigned int  usb3otg_mux_clkrst_bypass   : 1;  /* bit[3]    :  */
        unsigned int  usb3otg_ahbif_clkrst_bypass : 1;  /* bit[4]    :  */
        unsigned int  reserved_2                  : 1;  /* bit[5]    : ������ */
        unsigned int  dsi0_clkrst_bypass          : 1;  /* bit[6]    :  */
        unsigned int  dsi1_clkrst_bypass          : 1;  /* bit[7]    :  */
        unsigned int  sdio1_clkrst_bypass         : 1;  /* bit[8]    :  */
        unsigned int  perf_clkrst_bypass          : 1;  /* bit[9]    :  */
        unsigned int  secs_clkrst_bypass          : 1;  /* bit[10]   :  */
        unsigned int  secp_clkrst_bypass          : 1;  /* bit[11]   :  */
        unsigned int  reserved_3                  : 20; /* bit[12-31]: ������ */
    } reg;
} SOC_CRGPERIPH_IPCLKRST_BYPASS2_UNION;
#endif
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_g3d_clkrst_bypass_START            (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_g3d_clkrst_bypass_END              (0)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_usb3otg_mux_clkrst_bypass_START    (3)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_usb3otg_mux_clkrst_bypass_END      (3)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_usb3otg_ahbif_clkrst_bypass_START  (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_usb3otg_ahbif_clkrst_bypass_END    (4)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_dsi0_clkrst_bypass_START           (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_dsi0_clkrst_bypass_END             (6)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_dsi1_clkrst_bypass_START           (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_dsi1_clkrst_bypass_END             (7)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_sdio1_clkrst_bypass_START          (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_sdio1_clkrst_bypass_END            (8)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_perf_clkrst_bypass_START           (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_perf_clkrst_bypass_END             (9)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_secs_clkrst_bypass_START           (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_secs_clkrst_bypass_END             (10)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_secp_clkrst_bypass_START           (11)
#define SOC_CRGPERIPH_IPCLKRST_BYPASS2_secp_clkrst_bypass_END             (11)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_PDCEN_UNION
 �ṹ˵��  : A53_PDCEN �Ĵ����ṹ���塣��ַƫ����:0x260����ֵ:0x00000000�����:32
 �Ĵ���˵��: A53���µ�״̬��ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_pdc_en : 1;  /* bit[0]   : A53_0���µ�״̬��ʹ�ܼĴ���
                                                       0��״̬����ʹ��
                                                       1��״̬��ʹ�� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_CRGPERIPH_A53_PDCEN_UNION;
#endif
#define SOC_CRGPERIPH_A53_PDCEN_a53_0_pdc_en_START  (0)
#define SOC_CRGPERIPH_A53_PDCEN_a53_0_pdc_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_COREPWRINTEN_UNION
 �ṹ˵��  : A53_COREPWRINTEN �Ĵ����ṹ���塣��ַƫ����:0x264����ֵ:0x00000000�����:32
 �Ĵ���˵��: A53�Ӻ����µ�����ж�ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_a53_0_core0_pwr_en : 1;  /* bit[0]    : A53_0 CORE0���µ�����ж�ʹ��
                                                                   0����ʹ��
                                                                   1��ʹ�� */
        unsigned int  intr_a53_0_core1_pwr_en : 1;  /* bit[1]    : A53_0 CORE1���µ�����ж�ʹ��
                                                                   0����ʹ��
                                                                   1��ʹ�� */
        unsigned int  intr_a53_0_core2_pwr_en : 1;  /* bit[2]    : A53_0 CORE2���µ�����ж�ʹ��
                                                                   0����ʹ��
                                                                   1��ʹ�� */
        unsigned int  intr_a53_0_core3_pwr_en : 1;  /* bit[3]    : A53_0 CORE3���µ�����ж�ʹ��
                                                                   0����ʹ��
                                                                   1��ʹ�� */
        unsigned int  reserved                : 12; /* bit[4-15] : ������ */
        unsigned int  corepwrintenmasken      : 16; /* bit[16-31]: COREPWRINTENÿ������λ��ʹ��λ��
                                                                   ֻ�е�corepwrintenmasken��Ӧ�ı���λΪ1'b1��core_pwr_en��Ӧ�ı���λ�������á�corepwrintenmasken[0]����core_pwr_en[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_A53_COREPWRINTEN_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core0_pwr_en_START  (0)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core0_pwr_en_END    (0)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core1_pwr_en_START  (1)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core1_pwr_en_END    (1)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core2_pwr_en_START  (2)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core2_pwr_en_END    (2)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core3_pwr_en_START  (3)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_intr_a53_0_core3_pwr_en_END    (3)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_corepwrintenmasken_START       (16)
#define SOC_CRGPERIPH_A53_COREPWRINTEN_corepwrintenmasken_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_COREPWRINTSTAT_UNION
 �ṹ˵��  : A53_COREPWRINTSTAT �Ĵ����ṹ���塣��ַƫ����:0x268����ֵ:0x00000000�����:32
 �Ĵ���˵��: A53�Ӻ����µ�����ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_a53_0_core0_pwr_stat : 1;  /* bit[0]   : A53_0 CORE0���µ�����ж�״̬��д1����ж�״̬
                                                                    0�����µ�û�����
                                                                    1�����µ���� */
        unsigned int  intr_a53_0_core1_pwr_stat : 1;  /* bit[1]   : A53_0 CORE1���µ�����ж�״̬��д1����ж�״̬
                                                                    0�����µ�û�����
                                                                    1�����µ���� */
        unsigned int  intr_a53_0_core2_pwr_stat : 1;  /* bit[2]   : A53_0 CORE2���µ�����ж�״̬��д1����ж�״̬
                                                                    0�����µ�û�����
                                                                    1�����µ���� */
        unsigned int  intr_a53_0_core3_pwr_stat : 1;  /* bit[3]   : A53_0 CORE3���µ�����ж�״̬��д1����ж�״̬
                                                                    0�����µ�û�����
                                                                    1�����µ���� */
        unsigned int  reserved                  : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_CRGPERIPH_A53_COREPWRINTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core0_pwr_stat_START  (0)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core0_pwr_stat_END    (0)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core1_pwr_stat_START  (1)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core1_pwr_stat_END    (1)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core2_pwr_stat_START  (2)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core2_pwr_stat_END    (2)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core3_pwr_stat_START  (3)
#define SOC_CRGPERIPH_A53_COREPWRINTSTAT_intr_a53_0_core3_pwr_stat_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_COREGICMASK_UNION
 �ṹ˵��  : A53_COREGICMASK �Ĵ����ṹ���塣��ַƫ����:0x26C����ֵ:0x00000000�����:32
 �Ĵ���˵��: A53�Ӻ�GIC�ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_a53_0_core0_gic_mask : 1;  /* bit[0]   : A53_0 CORE0 GIC�ж�����
                                                                    0��״̬����Ӧgic�жϣ��Զ��ϵ�
                                                                    1��״̬������Ӧgic�ж� */
        unsigned int  intr_a53_0_core1_gic_mask : 1;  /* bit[1]   : A53_0 CORE1 GIC�ж�����
                                                                    0��״̬����Ӧgic�жϣ��Զ��ϵ�
                                                                    0��״̬������Ӧgic�ж� */
        unsigned int  intr_a53_0_core2_gic_mask : 1;  /* bit[2]   : A53_0 CORE2 GIC�ж�����
                                                                    0��״̬����Ӧgic�жϣ��Զ��ϵ�
                                                                    1��״̬������Ӧgic�ж� */
        unsigned int  intr_a53_0_core3_gic_mask : 1;  /* bit[3]   : A53_0 CORE3 GIC�ж�����
                                                                    0��״̬����Ӧgic�жϣ��Զ��ϵ�
                                                                    1��״̬������Ӧgic�ж� */
        unsigned int  reserved                  : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_CRGPERIPH_A53_COREGICMASK_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core0_gic_mask_START  (0)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core0_gic_mask_END    (0)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core1_gic_mask_START  (1)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core1_gic_mask_END    (1)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core2_gic_mask_START  (2)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core2_gic_mask_END    (2)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core3_gic_mask_START  (3)
#define SOC_CRGPERIPH_A53_COREGICMASK_intr_a53_0_core3_gic_mask_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_COREPOWERUP_UNION
 �ṹ˵��  : A53_COREPOWERUP �Ĵ����ṹ���塣��ַƫ����:0x270����ֵ:0x00000000�����:32
 �Ĵ���˵��: A53�Ӻ��ϵ�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core0_pwrup_req : 1;  /* bit[0]   : A53_0 CORE0 �ϵ�����д1�����ϵ� */
        unsigned int  a53_0_core1_pwrup_req : 1;  /* bit[1]   : A53_0 CORE1 �ϵ�����д1�����ϵ� */
        unsigned int  a53_0_core2_pwrup_req : 1;  /* bit[2]   : A53_0 CORE2 �ϵ�����д1�����ϵ� */
        unsigned int  a53_0_core3_pwrup_req : 1;  /* bit[3]   : A53_0 CORE3 �ϵ�����д1�����ϵ� */
        unsigned int  reserved              : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_CRGPERIPH_A53_COREPOWERUP_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core0_pwrup_req_START  (0)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core0_pwrup_req_END    (0)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core1_pwrup_req_START  (1)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core1_pwrup_req_END    (1)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core2_pwrup_req_START  (2)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core2_pwrup_req_END    (2)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core3_pwrup_req_START  (3)
#define SOC_CRGPERIPH_A53_COREPOWERUP_a53_0_core3_pwrup_req_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_COREPOWERDN_UNION
 �ṹ˵��  : A53_COREPOWERDN �Ĵ����ṹ���塣��ַƫ����:0x274����ֵ:0x00000000�����:32
 �Ĵ���˵��: A53�Ӻ��µ�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core0_pwrdn_req : 1;  /* bit[0]   : A53_0 CORE0 �µ�����д1�����µ� */
        unsigned int  a53_0_core1_pwrdn_req : 1;  /* bit[1]   : A53_0 CORE1 �µ�����д1�����µ� */
        unsigned int  a53_0_core2_pwrdn_req : 1;  /* bit[2]   : A53_0 CORE2 �µ�����д1�����µ� */
        unsigned int  a53_0_core3_pwrdn_req : 1;  /* bit[3]   : A53_0 CORE3 �µ�����д1�����µ� */
        unsigned int  reserved              : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_CRGPERIPH_A53_COREPOWERDN_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core0_pwrdn_req_START  (0)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core0_pwrdn_req_END    (0)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core1_pwrdn_req_START  (1)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core1_pwrdn_req_END    (1)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core2_pwrdn_req_START  (2)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core2_pwrdn_req_END    (2)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core3_pwrdn_req_START  (3)
#define SOC_CRGPERIPH_A53_COREPOWERDN_a53_0_core3_pwrdn_req_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_COREPOWERSTAT_UNION
 �ṹ˵��  : A53_COREPOWERSTAT �Ĵ����ṹ���塣��ַƫ����:0x278����ֵ:0x00000000�����:32
 �Ĵ���˵��: A53�Ӻ�״̬��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core0_pwr_stat : 4;  /* bit[0-3]  : A53_0 CORE0 ״̬��״̬
                                                                0000��ST_PWRDN
                                                                0001��ST_UP_RESET
                                                                0010��ST_UP_POWER
                                                                0011��ST_UP_ISO
                                                                0100��ST_UP_URESET
                                                                0101��ST_UP_DBGPWR
                                                                0110��ST_PWRON
                                                                0111��ST_DN_WFI
                                                                1000��ST_DN_DBGPWR
                                                                1001��ST_DN_ISO
                                                                1010��ST_DN_POWER */
        unsigned int  a53_0_core1_pwr_stat : 4;  /* bit[4-7]  : A53_0 CORE1 ״̬��״̬
                                                                0000��ST_PWRDN
                                                                0001��ST_UP_RESET
                                                                0010��ST_UP_POWER
                                                                0011��ST_UP_ISO
                                                                0100��ST_UP_URESET
                                                                0101��ST_UP_DBGPWR
                                                                0110��ST_PWRON
                                                                0111��ST_DN_WFI
                                                                1000��ST_DN_DBGPWR
                                                                1001��ST_DN_ISO
                                                                1010��ST_DN_POWER */
        unsigned int  a53_0_core2_pwr_stat : 4;  /* bit[8-11] : A53_0 CORE2 ״̬��״̬
                                                                0000��ST_PWRDN
                                                                0010��ST_UP_POWER
                                                                0011��ST_UP_ISO
                                                                0100��ST_UP_URESET
                                                                0101��ST_UP_DBGPWR
                                                                0110��ST_PWRON
                                                                0111��ST_DN_WFI
                                                                1000��ST_DN_DBGPWR
                                                                1001��ST_DN_ISO
                                                                1010��ST_DN_POWER */
        unsigned int  a53_0_core3_pwr_stat : 4;  /* bit[12-15]: A53_0 CORE3 ״̬��״̬
                                                                0000��ST_PWRDN
                                                                0001��ST_UP_RESET
                                                                0010��ST_UP_POWER
                                                                0011��ST_UP_ISO
                                                                0100��ST_UP_URESET
                                                                0101��ST_UP_DBGPWR
                                                                0110��ST_PWRON
                                                                0111��ST_DN_WFI
                                                                1000��ST_DN_DBGPWR
                                                                1001��ST_DN_ISO
                                                                1010��ST_DN_POWER */
        unsigned int  reserved             : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_CRGPERIPH_A53_COREPOWERSTAT_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core0_pwr_stat_START  (0)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core0_pwr_stat_END    (3)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core1_pwr_stat_START  (4)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core1_pwr_stat_END    (7)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core2_pwr_stat_START  (8)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core2_pwr_stat_END    (11)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core3_pwr_stat_START  (12)
#define SOC_CRGPERIPH_A53_COREPOWERSTAT_a53_0_core3_pwr_stat_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_COREPWRUPTIME_UNION
 �ṹ˵��  : A53_COREPWRUPTIME �Ĵ����ṹ���塣��ַƫ����:0x27C����ֵ:0x000030D4�����:32
 �Ĵ���˵��: A53�Ӻ��ϵ�ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core_pwrup_time : 16; /* bit[0-15] : A53_0�Ӻ��ϵ�ʱ�䣬Ĭ��100us */
        unsigned int  reserved              : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_CRGPERIPH_A53_COREPWRUPTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPWRUPTIME_a53_0_core_pwrup_time_START  (0)
#define SOC_CRGPERIPH_A53_COREPWRUPTIME_a53_0_core_pwrup_time_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_COREPWRDNTIME_UNION
 �ṹ˵��  : A53_COREPWRDNTIME �Ĵ����ṹ���塣��ַƫ����:0x280����ֵ:0x000004E2�����:32
 �Ĵ���˵��: A53�Ӻ��µ�ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core_pwrdn_time : 16; /* bit[0-15] : A53_0�Ӻ��µ�ʱ�䣬Ĭ��10us */
        unsigned int  reserved              : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_CRGPERIPH_A53_COREPWRDNTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREPWRDNTIME_a53_0_core_pwrdn_time_START  (0)
#define SOC_CRGPERIPH_A53_COREPWRDNTIME_a53_0_core_pwrdn_time_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_COREISOTIME_UNION
 �ṹ˵��  : A53_COREISOTIME �Ĵ����ṹ���塣��ַƫ����:0x284����ֵ:0x0000000F�����:32
 �Ĵ���˵��: A53�Ӻ�ǯλ����ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core_iso_time : 5;  /* bit[0-4] : A53_0�Ӻ�ǯλ�ͽ�ǯλʱ�䣬Ĭ��16��pclk */
        unsigned int  reserved            : 27; /* bit[5-31]: ������ */
    } reg;
} SOC_CRGPERIPH_A53_COREISOTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREISOTIME_a53_0_core_iso_time_START  (0)
#define SOC_CRGPERIPH_A53_COREISOTIME_a53_0_core_iso_time_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_COREDBGTIME_UNION
 �ṹ˵��  : A53_COREDBGTIME �Ĵ����ṹ���塣��ַƫ����:0x288����ֵ:0x00000007�����:32
 �Ĵ���˵��: A53�Ӻ�DBG����ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core_dbg_time : 4;  /* bit[0-3] : A53_0�Ӻ�DBG�ź�����ʱ�䣬Ĭ��8��pclk */
        unsigned int  reserved            : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_CRGPERIPH_A53_COREDBGTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREDBGTIME_a53_0_core_dbg_time_START  (0)
#define SOC_CRGPERIPH_A53_COREDBGTIME_a53_0_core_dbg_time_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_CORERSTTIME_UNION
 �ṹ˵��  : A53_CORERSTTIME �Ĵ����ṹ���塣��ַƫ����:0x28C����ֵ:0x00000007�����:32
 �Ĵ���˵��: A53�Ӻ˸�λʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core_rst_time : 3;  /* bit[0-2] : A53_0�Ӻ˸�λʱ�䣬Ĭ��8��pclk */
        unsigned int  reserved            : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_CRGPERIPH_A53_CORERSTTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_CORERSTTIME_a53_0_core_rst_time_START  (0)
#define SOC_CRGPERIPH_A53_CORERSTTIME_a53_0_core_rst_time_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_COREURSTTIME_UNION
 �ṹ˵��  : A53_COREURSTTIME �Ĵ����ṹ���塣��ַƫ����:0x290����ֵ:0x0000000F�����:32
 �Ĵ���˵��: A53�Ӻ˽⸴λʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_0_core_urst_time : 6;  /* bit[0-5] : A53_0�Ӻ˽⸴λʱ�䣬Ĭ��16��pclk */
        unsigned int  reserved             : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_CRGPERIPH_A53_COREURSTTIME_UNION;
#endif
#define SOC_CRGPERIPH_A53_COREURSTTIME_a53_0_core_urst_time_START  (0)
#define SOC_CRGPERIPH_A53_COREURSTTIME_a53_0_core_urst_time_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_PDCEN_UNION
 �ṹ˵��  : MAIA_PDCEN �Ĵ����ṹ���塣��ַƫ����:0x300����ֵ:0x00000000�����:32
 �Ĵ���˵��: MAIA���µ�״̬��ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_1_pdc_en : 1;  /* bit[0]   : A53_1���µ�״̬��ʹ�ܼĴ���
                                                       0��״̬����ʹ��
                                                       1��״̬��ʹ�� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_PDCEN_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_PDCEN_a57_1_pdc_en_START  (0)
#define SOC_CRGPERIPH_MAIA_PDCEN_a57_1_pdc_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_COREPWRINTEN_UNION
 �ṹ˵��  : MAIA_COREPWRINTEN �Ĵ����ṹ���塣��ַƫ����:0x304����ֵ:0x00000000�����:32
 �Ĵ���˵��: MAIA_�Ӻ����µ�����ж�ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_a53_1_core0_pwr_en : 1;  /* bit[0]    : A53_1 CORE0���µ�����ж�ʹ��
                                                                   0����ʹ��
                                                                   1��ʹ�� */
        unsigned int  intr_a53_1_core1_pwr_en : 1;  /* bit[1]    : A53_1 CORE1���µ�����ж�ʹ��
                                                                   0����ʹ��
                                                                   1��ʹ�� */
        unsigned int  intr_a53_1_core2_pwr_en : 1;  /* bit[2]    : A53_1 CORE2���µ�����ж�ʹ��
                                                                   0����ʹ��
                                                                   1��ʹ�� */
        unsigned int  intr_a53_1_core3_pwr_en : 1;  /* bit[3]    : A53_1 CORE3���µ�����ж�ʹ��
                                                                   0����ʹ��
                                                                   1��ʹ�� */
        unsigned int  reserved                : 12; /* bit[4-15] : ������ */
        unsigned int  corepwrintenmasken      : 16; /* bit[16-31]: COREPWRINTENÿ������λ��ʹ��λ��
                                                                   ֻ�е�corepwrintenmasken��Ӧ�ı���λΪ1'b1��core_pwr_en��Ӧ�ı���λ�������á�corepwrintenmasken[0]����core_pwr_en[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_MAIA_COREPWRINTEN_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core0_pwr_en_START  (0)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core0_pwr_en_END    (0)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core1_pwr_en_START  (1)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core1_pwr_en_END    (1)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core2_pwr_en_START  (2)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core2_pwr_en_END    (2)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core3_pwr_en_START  (3)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_intr_a53_1_core3_pwr_en_END    (3)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_corepwrintenmasken_START       (16)
#define SOC_CRGPERIPH_MAIA_COREPWRINTEN_corepwrintenmasken_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_UNION
 �ṹ˵��  : MAIA_COREPWRINTSTAT �Ĵ����ṹ���塣��ַƫ����:0x308����ֵ:0x00000000�����:32
 �Ĵ���˵��: MAIA�Ӻ����µ�����ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_a53_1_core0_pwr_stat : 1;  /* bit[0]   : A53_1 CORE0���µ�����ж�״̬��д1����ж�״̬
                                                                    0�����µ�û�����
                                                                    1�����µ���� */
        unsigned int  intr_a53_1_core1_pwr_stat : 1;  /* bit[1]   : A53_1 CORE1���µ�����ж�״̬��д1����ж�״̬
                                                                    0�����µ�û�����
                                                                    1�����µ���� */
        unsigned int  intr_a53_1_core2_pwr_stat : 1;  /* bit[2]   : A53_1 CORE2���µ�����ж�״̬��д1����ж�״̬
                                                                    0�����µ�û�����
                                                                    1�����µ���� */
        unsigned int  intr_a53_1_core3_pwr_stat : 1;  /* bit[3]   : A53_1 CORE3���µ�����ж�״̬��д1����ж�״̬
                                                                    0�����µ�û�����
                                                                    1�����µ���� */
        unsigned int  reserved                  : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core0_pwr_stat_START  (0)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core0_pwr_stat_END    (0)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core1_pwr_stat_START  (1)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core1_pwr_stat_END    (1)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core2_pwr_stat_START  (2)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core2_pwr_stat_END    (2)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core3_pwr_stat_START  (3)
#define SOC_CRGPERIPH_MAIA_COREPWRINTSTAT_intr_a53_1_core3_pwr_stat_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_COREGICMASK_UNION
 �ṹ˵��  : MAIA_COREGICMASK �Ĵ����ṹ���塣��ַƫ����:0x30C����ֵ:0x00000000�����:32
 �Ĵ���˵��: MAIA�Ӻ�GIC�ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_a53_1_core0_gic_mask : 1;  /* bit[0]   : A53_1 CORE0 GIC�ж�����
                                                                    0��״̬����Ӧgic�жϣ��Զ��ϵ�
                                                                    1��״̬������Ӧgic�ж� */
        unsigned int  intr_a53_1_core1_gic_mask : 1;  /* bit[1]   : A53_1 CORE1 GIC�ж�����
                                                                    0��״̬����Ӧgic�жϣ��Զ��ϵ�
                                                                    0��״̬������Ӧgic�ж� */
        unsigned int  intr_a53_1_core2_gic_mask : 1;  /* bit[2]   : A53_1 CORE2 GIC�ж�����
                                                                    0��״̬����Ӧgic�жϣ��Զ��ϵ�
                                                                    1��״̬������Ӧgic�ж� */
        unsigned int  intr_a53_1_core3_gic_mask : 1;  /* bit[3]   : A53_1 CORE3 GIC�ж�����
                                                                    0��״̬����Ӧgic�жϣ��Զ��ϵ�
                                                                    1��״̬������Ӧgic�ж� */
        unsigned int  reserved                  : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_COREGICMASK_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core0_gic_mask_START  (0)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core0_gic_mask_END    (0)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core1_gic_mask_START  (1)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core1_gic_mask_END    (1)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core2_gic_mask_START  (2)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core2_gic_mask_END    (2)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core3_gic_mask_START  (3)
#define SOC_CRGPERIPH_MAIA_COREGICMASK_intr_a53_1_core3_gic_mask_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_COREPOWERUP_UNION
 �ṹ˵��  : MAIA_COREPOWERUP �Ĵ����ṹ���塣��ַƫ����:0x310����ֵ:0x00000000�����:32
 �Ĵ���˵��: MAIA�Ӻ��ϵ�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core0_pwrup_req : 1;  /* bit[0]   : A53_1 CORE0 �ϵ�����д1�����ϵ� */
        unsigned int  a53_1_core1_pwrup_req : 1;  /* bit[1]   : A53_1 CORE1 �ϵ�����д1�����ϵ� */
        unsigned int  a53_1_core2_pwrup_req : 1;  /* bit[2]   : A53_1 CORE2 �ϵ�����д1�����ϵ� */
        unsigned int  a53_1_core3_pwrup_req : 1;  /* bit[3]   : A53_1 CORE3 �ϵ�����д1�����ϵ� */
        unsigned int  reserved              : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_COREPOWERUP_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core0_pwrup_req_START  (0)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core0_pwrup_req_END    (0)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core1_pwrup_req_START  (1)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core1_pwrup_req_END    (1)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core2_pwrup_req_START  (2)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core2_pwrup_req_END    (2)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core3_pwrup_req_START  (3)
#define SOC_CRGPERIPH_MAIA_COREPOWERUP_a53_1_core3_pwrup_req_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_COREPOWERDN_UNION
 �ṹ˵��  : MAIA_COREPOWERDN �Ĵ����ṹ���塣��ַƫ����:0x314����ֵ:0x00000000�����:32
 �Ĵ���˵��: MAIA�Ӻ��µ�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core0_pwrdn_req : 1;  /* bit[0]   : A53_1 CORE0 �µ�����д1�����µ� */
        unsigned int  a53_1_core1_pwrdn_req : 1;  /* bit[1]   : A53_1 CORE1 �µ�����д1�����µ� */
        unsigned int  a53_1_core2_pwrdn_req : 1;  /* bit[2]   : A53_1 CORE2 �µ�����д1�����µ� */
        unsigned int  a53_1_core3_pwrdn_req : 1;  /* bit[3]   : A53_1 CORE3 �µ�����д1�����µ� */
        unsigned int  reserved              : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_COREPOWERDN_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core0_pwrdn_req_START  (0)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core0_pwrdn_req_END    (0)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core1_pwrdn_req_START  (1)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core1_pwrdn_req_END    (1)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core2_pwrdn_req_START  (2)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core2_pwrdn_req_END    (2)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core3_pwrdn_req_START  (3)
#define SOC_CRGPERIPH_MAIA_COREPOWERDN_a53_1_core3_pwrdn_req_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_COREPOWERSTAT_UNION
 �ṹ˵��  : MAIA_COREPOWERSTAT �Ĵ����ṹ���塣��ַƫ����:0x318����ֵ:0x00000000�����:32
 �Ĵ���˵��: MAIA�Ӻ�״̬��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core0_pwr_stat : 4;  /* bit[0-3]  : A53_1 CORE0 ״̬��״̬
                                                                0000��ST_PWRDN
                                                                0001��ST_UP_RESET
                                                                0010��ST_UP_POWER
                                                                0011��ST_UP_ISO
                                                                0100��ST_UP_URESET
                                                                0101��ST_UP_DBGPWR
                                                                0110��ST_PWRON
                                                                0111��ST_DN_WFI
                                                                1000��ST_DN_DBGPWR
                                                                1001��ST_DN_ISO
                                                                1010��ST_DN_POWER */
        unsigned int  a53_1_core1_pwr_stat : 4;  /* bit[4-7]  : A53_1 CORE1 ״̬��״̬
                                                                0000��ST_PWRDN
                                                                0001��ST_UP_RESET
                                                                0010��ST_UP_POWER
                                                                0011��ST_UP_ISO
                                                                0100��ST_UP_URESET
                                                                0101��ST_UP_DBGPWR
                                                                0110��ST_PWRON
                                                                0111��ST_DN_WFI
                                                                1000��ST_DN_DBGPWR
                                                                1001��ST_DN_ISO
                                                                1010��ST_DN_POWER */
        unsigned int  a53_1_core2_pwr_stat : 4;  /* bit[8-11] : A53_1 CORE2 ״̬��״̬
                                                                0000��ST_PWRDN
                                                                0001��ST_UP_RESET
                                                                0010��ST_UP_POWER
                                                                0011��ST_UP_ISO
                                                                0100��ST_UP_URESET
                                                                0101��ST_UP_DBGPWR
                                                                0110��ST_PWRON
                                                                0111��ST_DN_WFI
                                                                1000��ST_DN_DBGPWR
                                                                1001��ST_DN_ISO
                                                                1010��ST_DN_POWER */
        unsigned int  a53_1_core3_pwr_stat : 4;  /* bit[12-15]: A53_1 CORE3 ״̬��״̬
                                                                0000��ST_PWRDN
                                                                0001��ST_UP_RESET
                                                                0010��ST_UP_POWER
                                                                0011��ST_UP_ISO
                                                                0100��ST_UP_URESET
                                                                0101��ST_UP_DBGPWR
                                                                0110��ST_PWRON
                                                                0111��ST_DN_WFI
                                                                1000��ST_DN_DBGPWR
                                                                1001��ST_DN_ISO
                                                                1010��ST_DN_POWER */
        unsigned int  reserved             : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_COREPOWERSTAT_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core0_pwr_stat_START  (0)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core0_pwr_stat_END    (3)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core1_pwr_stat_START  (4)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core1_pwr_stat_END    (7)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core2_pwr_stat_START  (8)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core2_pwr_stat_END    (11)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core3_pwr_stat_START  (12)
#define SOC_CRGPERIPH_MAIA_COREPOWERSTAT_a53_1_core3_pwr_stat_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_COREPWRUPTIME_UNION
 �ṹ˵��  : MAIA_COREPWRUPTIME �Ĵ����ṹ���塣��ַƫ����:0x31C����ֵ:0x000030D4�����:32
 �Ĵ���˵��: MAIA�Ӻ��ϵ�ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core_pwrup_time : 16; /* bit[0-15] : A53_1�Ӻ��ϵ�ʱ�䣬Ĭ��100us */
        unsigned int  reserved              : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_COREPWRUPTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPWRUPTIME_a53_1_core_pwrup_time_START  (0)
#define SOC_CRGPERIPH_MAIA_COREPWRUPTIME_a53_1_core_pwrup_time_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_COREPWRDNTIME_UNION
 �ṹ˵��  : MAIA_COREPWRDNTIME �Ĵ����ṹ���塣��ַƫ����:0x320����ֵ:0x000004E2�����:32
 �Ĵ���˵��: MAIA�Ӻ��µ�ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core_pwrdn_time : 16; /* bit[0-15] : A53_1�Ӻ��µ�ʱ�䣬Ĭ��10us */
        unsigned int  reserved              : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_COREPWRDNTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREPWRDNTIME_a53_1_core_pwrdn_time_START  (0)
#define SOC_CRGPERIPH_MAIA_COREPWRDNTIME_a53_1_core_pwrdn_time_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_COREISOTIME_UNION
 �ṹ˵��  : MAIA_COREISOTIME �Ĵ����ṹ���塣��ַƫ����:0x324����ֵ:0x0000000F�����:32
 �Ĵ���˵��: MAIA�Ӻ�ǯλ����ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core_iso_time : 5;  /* bit[0-4] : A53_1�Ӻ�ǯλ�ͽ�ǯλʱ�䣬Ĭ��16��pclk */
        unsigned int  reserved            : 27; /* bit[5-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_COREISOTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREISOTIME_a53_1_core_iso_time_START  (0)
#define SOC_CRGPERIPH_MAIA_COREISOTIME_a53_1_core_iso_time_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_COREDBGTIME_UNION
 �ṹ˵��  : MAIA_COREDBGTIME �Ĵ����ṹ���塣��ַƫ����:0x328����ֵ:0x00000007�����:32
 �Ĵ���˵��: MAIA�Ӻ�DBG����ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core_dbg_time : 4;  /* bit[0-3] : A53_1�Ӻ�DBG�ź�����ʱ�䣬Ĭ��8��pclk */
        unsigned int  reserved            : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_COREDBGTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREDBGTIME_a53_1_core_dbg_time_START  (0)
#define SOC_CRGPERIPH_MAIA_COREDBGTIME_a53_1_core_dbg_time_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_CORERSTTIME_UNION
 �ṹ˵��  : MAIA_CORERSTTIME �Ĵ����ṹ���塣��ַƫ����:0x32C����ֵ:0x00000007�����:32
 �Ĵ���˵��: MAIA�Ӻ˸�λʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core_rst_time : 3;  /* bit[0-2] : A53_1�Ӻ˸�λʱ�䣬Ĭ��8��pclk */
        unsigned int  reserved            : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_CORERSTTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CORERSTTIME_a53_1_core_rst_time_START  (0)
#define SOC_CRGPERIPH_MAIA_CORERSTTIME_a53_1_core_rst_time_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_COREURSTTIME_UNION
 �ṹ˵��  : MAIA_COREURSTTIME �Ĵ����ṹ���塣��ַƫ����:0x330����ֵ:0x0000000F�����:32
 �Ĵ���˵��: MAIA�Ӻ˽⸴λʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_1_core_urst_time : 6;  /* bit[0-5] : A53_1�Ӻ˽⸴λʱ�䣬Ĭ��16��pclk */
        unsigned int  reserved             : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MAIA_COREURSTTIME_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_COREURSTTIME_a53_1_core_urst_time_START  (0)
#define SOC_CRGPERIPH_MAIA_COREURSTTIME_a53_1_core_urst_time_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_ISPA7_CLKEN_UNION
 �ṹ˵��  : ISPA7_CLKEN �Ĵ����ṹ���塣��ַƫ����:0x340����ֵ:0x0000017F�����:32
 �Ĵ���˵��: ISPA7��ϵͳʱ��ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispa7_clkinen                    : 1;  /* bit[0]    : CPUʱ��ʹ��ϵͳ���ƣ�
                                                                            0���ر�ʱ��
                                                                            1������ʱ�� */
        unsigned int  ispa7_atclkoff_n                 : 1;  /* bit[1]    : ATCLKʱ���ſ�ϵͳ���ƣ�
                                                                            0���ر�ʱ��
                                                                            1������ʱ�� */
        unsigned int  pclkdbg_to_asyn_bri_clkoff_n     : 1;  /* bit[2]    : PCLKDBG_TO_A7_ASYN_BRIʱ��ʹ��ϵͳ���ƣ�
                                                                            0���ر�ʱ��
                                                                            1������ʱ�� */
        unsigned int  ispa7_atclk_to_asyn_bri_clkoff_n : 1;  /* bit[3]    : ATCLK_TO_ASYN_BRIʱ��ʹ��ϵͳ���ƣ�
                                                                            0���ر�ʱ�ӣ�
                                                                            1������ʱ�� */
        unsigned int  ispa7_pclkdbg_to_cs_clkoff_n     : 1;  /* bit[4]    : PCLKDBG_TO_A7_CSʱ��ʹ��ϵͳ���ƣ�
                                                                            0���ر�ʱ��
                                                                            1������ʱ�� */
        unsigned int  ispa7_aclkenm_sel                : 1;  /* bit[5]    : A7 ACE master�ӿ�ʱ��Ƶ�ʱ�ѡ��
                                                                            0��1:1
                                                                            1��1:2 */
        unsigned int  ispa7_sys_cnt_en_dly             : 4;  /* bit[6-9]  : system counter����ʹ���ź���ʱ�趨 */
        unsigned int  reserved                         : 6;  /* bit[10-15]: ������ */
        unsigned int  clkmasken                        : 16; /* bit[16-31]: clkenÿ������λ��ʹ��λ��
                                                                            ֻ�е�clkmasken��Ӧ�ı���λΪ1'b1��clken��Ӧ�ı���λ�������á�clkmasken[0]����clken[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_ISPA7_CLKEN_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_clkinen_START                     (0)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_clkinen_END                       (0)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_atclkoff_n_START                  (1)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_atclkoff_n_END                    (1)
#define SOC_CRGPERIPH_ISPA7_CLKEN_pclkdbg_to_asyn_bri_clkoff_n_START      (2)
#define SOC_CRGPERIPH_ISPA7_CLKEN_pclkdbg_to_asyn_bri_clkoff_n_END        (2)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_atclk_to_asyn_bri_clkoff_n_START  (3)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_atclk_to_asyn_bri_clkoff_n_END    (3)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_pclkdbg_to_cs_clkoff_n_START      (4)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_pclkdbg_to_cs_clkoff_n_END        (4)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_aclkenm_sel_START                 (5)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_aclkenm_sel_END                   (5)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_sys_cnt_en_dly_START              (6)
#define SOC_CRGPERIPH_ISPA7_CLKEN_ispa7_sys_cnt_en_dly_END                (9)
#define SOC_CRGPERIPH_ISPA7_CLKEN_clkmasken_START                         (16)
#define SOC_CRGPERIPH_ISPA7_CLKEN_clkmasken_END                           (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_ISPA7_RSTEN_UNION
 �ṹ˵��  : ISPA7_RSTEN �Ĵ����ṹ���塣��ַƫ����:0x344����ֵ:0x00000000�����:32
 �Ĵ���˵��: ISPA7��ϵͳ��λʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispa7_core_por_rst_req       : 1;  /* bit[0]   : �����ϵ縴λ���󣬵�ƽ��λ������Ч */
        unsigned int  ispa7_rst_software_req       : 1;  /* bit[1]   : A7���к���λ���󣬵�ƽ��λ������Ч */
        unsigned int  ispa7_core_rst_software_req  : 1;  /* bit[2]   : ������λ���󣬵�ƽ��λ������Ч */
        unsigned int  ispa7_debug_all_rst_req      : 1;  /* bit[3]   : Debug �߼��ܸ�λ���󣬵�ƽ��λ������Ч */
        unsigned int  ispa7_core_debug_rst_req     : 1;  /* bit[4]   : ����debug�߼���λ���󣬵�ƽ��λ������Ч */
        unsigned int  ispa7_coresight_soft_rst_req : 1;  /* bit[5]   : Coresight ϵͳ��λ���󣬸���Ч */
        unsigned int  ispa7_dbgrstreq              : 1;  /* bit[6]   : ��Debug APB��CTI��CTM�������߼���λ���󣬵�ƽ��λ������Ч */
        unsigned int  reserved                     : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_CRGPERIPH_ISPA7_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_por_rst_req_START        (0)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_por_rst_req_END          (0)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_rst_software_req_START        (1)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_rst_software_req_END          (1)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_rst_software_req_START   (2)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_rst_software_req_END     (2)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_debug_all_rst_req_START       (3)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_debug_all_rst_req_END         (3)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_debug_rst_req_START      (4)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_core_debug_rst_req_END        (4)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_coresight_soft_rst_req_START  (5)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_coresight_soft_rst_req_END    (5)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_dbgrstreq_START               (6)
#define SOC_CRGPERIPH_ISPA7_RSTEN_ispa7_dbgrstreq_END                 (6)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_ISPA7_RSTDIS_UNION
 �ṹ˵��  : ISPA7_RSTDIS �Ĵ����ṹ���塣��ַƫ����:0x348����ֵ:0x00000000�����:32
 �Ĵ���˵��: ISPA7��ϵͳ��λ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispa7_core_por_rst_req       : 1;  /* bit[0]   : �����ϵ縴λ���󣬵�ƽ��λ������Ч */
        unsigned int  ispa7_rst_software_req       : 1;  /* bit[1]   : A7���к���λ���󣬵�ƽ��λ������Ч */
        unsigned int  ispa7_core_rst_software_req  : 1;  /* bit[2]   : ������λ���󣬵�ƽ��λ������Ч */
        unsigned int  ispa7_debug_all_rst_req      : 1;  /* bit[3]   : Debug �߼��ܸ�λ���󣬵�ƽ��λ������Ч */
        unsigned int  ispa7_core_debug_rst_req     : 1;  /* bit[4]   : ����debug�߼���λ���󣬵�ƽ��λ������Ч */
        unsigned int  ispa7_coresight_soft_rst_req : 1;  /* bit[5]   : Coresight ϵͳ��λ���󣬸���Ч */
        unsigned int  ispa7_dbgrstreq              : 1;  /* bit[6]   : ��Debug APB��CTI��CTM�������߼���λ���󣬵�ƽ��λ������Ч */
        unsigned int  reserved                     : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_CRGPERIPH_ISPA7_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_por_rst_req_START        (0)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_por_rst_req_END          (0)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_rst_software_req_START        (1)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_rst_software_req_END          (1)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_rst_software_req_START   (2)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_rst_software_req_END     (2)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_debug_all_rst_req_START       (3)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_debug_all_rst_req_END         (3)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_debug_rst_req_START      (4)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_core_debug_rst_req_END        (4)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_coresight_soft_rst_req_START  (5)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_coresight_soft_rst_req_END    (5)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_dbgrstreq_START               (6)
#define SOC_CRGPERIPH_ISPA7_RSTDIS_ispa7_dbgrstreq_END                 (6)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_ISPA7_RSTSTAT_UNION
 �ṹ˵��  : ISPA7_RSTSTAT �Ĵ����ṹ���塣��ַƫ����:0x34C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ISPA7��ϵͳ��λʹ��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispa7_core_por_rst_req       : 1;  /* bit[0]   : �����ϵ縴λ���󣬵�ƽ��λ������Ч */
        unsigned int  ispa7_rst_software_req       : 1;  /* bit[1]   : A7���к���λ���󣬵�ƽ��λ������Ч */
        unsigned int  ispa7_core_rst_software_req  : 1;  /* bit[2]   : ������λ���󣬵�ƽ��λ������Ч */
        unsigned int  ispa7_debug_all_rst_req      : 1;  /* bit[3]   : Debug �߼��ܸ�λ���󣬵�ƽ��λ������Ч */
        unsigned int  ispa7_core_debug_rst_req     : 1;  /* bit[4]   : ����debug�߼���λ���󣬵�ƽ��λ������Ч */
        unsigned int  ispa7_coresight_soft_rst_req : 1;  /* bit[5]   : Coresight ϵͳ��λ���󣬸���Ч */
        unsigned int  ispa7_dbgrstreq              : 1;  /* bit[6]   : ��Debug APB��CTI��CTM�������߼���λ���󣬵�ƽ��λ������Ч */
        unsigned int  reserved                     : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_CRGPERIPH_ISPA7_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_por_rst_req_START        (0)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_por_rst_req_END          (0)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_rst_software_req_START        (1)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_rst_software_req_END          (1)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_rst_software_req_START   (2)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_rst_software_req_END     (2)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_debug_all_rst_req_START       (3)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_debug_all_rst_req_END         (3)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_debug_rst_req_START      (4)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_core_debug_rst_req_END        (4)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_coresight_soft_rst_req_START  (5)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_coresight_soft_rst_req_END    (5)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_dbgrstreq_START               (6)
#define SOC_CRGPERIPH_ISPA7_RSTSTAT_ispa7_dbgrstreq_END                 (6)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_ISPA7_STAT_UNION
 �ṹ˵��  : ISPA7_STAT �Ĵ����ṹ���塣��ַƫ����:0x354����ֵ:0x00000000�����:32
 �Ĵ���˵��: ISPA7״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispa7_standbywfi   : 1;  /* bit[0]   : ָʾCPU�Ƿ���WFI״̬ */
        unsigned int  ispa7_standbywfe   : 1;  /* bit[1]   : ָʾCPU�Ƿ���WFE״̬ */
        unsigned int  ispa7_smpnamp      : 1;  /* bit[2]   : ָʾCPU�˴���SMP��AMPģʽ */
        unsigned int  ispa7_standbywfil2 : 1;  /* bit[3]   : ָʾL2�Ƿ���WFI״̬ */
        unsigned int  ispa7_dbgack       : 1;  /* bit[4]   : A7 core����debug״̬���״ָ̬ʾ������Ч������һcore����debug״̬ʱ�����ź���Ч */
        unsigned int  reserved           : 27; /* bit[5-31]: ������ */
    } reg;
} SOC_CRGPERIPH_ISPA7_STAT_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfi_START    (0)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfi_END      (0)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfe_START    (1)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfe_END      (1)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_smpnamp_START       (2)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_smpnamp_END         (2)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfil2_START  (3)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_standbywfil2_END    (3)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_dbgack_START        (4)
#define SOC_CRGPERIPH_ISPA7_STAT_ispa7_dbgack_END          (4)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV0_UNION
 �ṹ˵��  : PERI_AUTODIV0 �Ĵ����ṹ���塣��ַƫ����:0x360����ֵ:0x03E07BFF�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ivp_div_auto_reduce_bypass : 1;  /* bit[0]    : Ӳ���Զ���Ƶ����bypass���ã�
                                                                      0����bypass��
                                                                      1��bypass�� */
        unsigned int  ivp_auto_waitcfg_in        : 10; /* bit[1-10] : Ӳ�������Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  ivp_auto_waitcfg_out       : 10; /* bit[11-20]: Ӳ���˳��Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  ivp_div_auto_cfg           : 6;  /* bit[21-26]: Ӳ���Զ���Ƶ��������
                                                                      6'h00:1��
                                                                      6'h01:2��
                                                                      ��
                                                                      6'h3F:64�� */
        unsigned int  ivp_pwaitmode_bypass       : 1;  /* bit[27]   : dw_axi_m1_st �Ƿ�����Զ���Ƶ�ж�������
                                                                      1'h0:���룻
                                                                      1'h1:�����룻 */
        unsigned int  ivp_dw_axi_m1_st_bypass    : 1;  /* bit[28]   : dw_axi_m1_st �Ƿ�����Զ���Ƶ�ж�������
                                                                      1'h0:���룻
                                                                      1'h1:�����룻 */
        unsigned int  ivp_dw_axi_m2_st_bypass    : 1;  /* bit[29]   : dw_axi_m2_st �Ƿ�����Զ���Ƶ�ж�������
                                                                      1'h0:���룻
                                                                      1'h1:�����룻 */
        unsigned int  reserved                   : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV0_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_div_auto_reduce_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_div_auto_reduce_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_auto_waitcfg_in_START         (1)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_auto_waitcfg_in_END           (10)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_auto_waitcfg_out_START        (11)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_auto_waitcfg_out_END          (20)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_div_auto_cfg_START            (21)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_div_auto_cfg_END              (26)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_pwaitmode_bypass_START        (27)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_pwaitmode_bypass_END          (27)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_dw_axi_m1_st_bypass_START     (28)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_dw_axi_m1_st_bypass_END       (28)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_dw_axi_m2_st_bypass_START     (29)
#define SOC_CRGPERIPH_PERI_AUTODIV0_ivp_dw_axi_m2_st_bypass_END       (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV1_UNION
 �ṹ˵��  : PERI_AUTODIV1 �Ĵ����ṹ���塣��ַƫ����:0x364����ֵ:0x03E07BFF�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispa7_div_auto_reduce_bypass : 1;  /* bit[0]    : Ӳ���Զ���Ƶ����bypass���ã�
                                                                        0����bypass��
                                                                        1��bypass�� */
        unsigned int  ispa7_auto_waitcfg_in        : 10; /* bit[1-10] : Ӳ�������Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  ispa7_auto_waitcfg_out       : 10; /* bit[11-20]: Ӳ���˳��Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  ispa7_div_auto_cfg           : 6;  /* bit[21-26]: Ӳ���Զ���Ƶ��������
                                                                        6'h00:1��
                                                                        6'h01:2��
                                                                        ��
                                                                        6'h3F:64�� */
        unsigned int  reserved                     : 5;  /* bit[27-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV1_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_div_auto_reduce_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_div_auto_reduce_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_auto_waitcfg_in_START         (1)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_auto_waitcfg_in_END           (10)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_auto_waitcfg_out_START        (11)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_auto_waitcfg_out_END          (20)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_div_auto_cfg_START            (21)
#define SOC_CRGPERIPH_PERI_AUTODIV1_ispa7_div_auto_cfg_END              (26)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV2_UNION
 �ṹ˵��  : PERI_AUTODIV2 �Ĵ����ṹ���塣��ַƫ����:0x368����ֵ:0x0BE07BFF�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  venc_div_auto_reduce_bypass : 1;  /* bit[0]    : Ӳ���Զ���Ƶ����bypass���ã�
                                                                       0����bypass��
                                                                       1��bypass�� */
        unsigned int  venc_auto_waitcfg_in        : 10; /* bit[1-10] : Ӳ�������Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  venc_auto_waitcfg_out       : 10; /* bit[11-20]: Ӳ���˳��Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  venc_div_auto_cfg           : 6;  /* bit[21-26]: Ӳ���Զ���Ƶ��������
                                                                       6'h00:1��
                                                                       6'h01:2��
                                                                       ��
                                                                       6'h3F:64�� */
        unsigned int  venc_vcodecbus_cfg_bypass   : 1;  /* bit[27]   : cfg �Ƿ�����Զ���Ƶ�ж�������
                                                                       1'h0:���룻
                                                                       1'h1:�����룻 */
        unsigned int  reserved                    : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV2_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_div_auto_reduce_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_div_auto_reduce_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_auto_waitcfg_in_START         (1)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_auto_waitcfg_in_END           (10)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_auto_waitcfg_out_START        (11)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_auto_waitcfg_out_END          (20)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_div_auto_cfg_START            (21)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_div_auto_cfg_END              (26)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_vcodecbus_cfg_bypass_START    (27)
#define SOC_CRGPERIPH_PERI_AUTODIV2_venc_vcodecbus_cfg_bypass_END      (27)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV3_UNION
 �ṹ˵��  : PERI_AUTODIV3 �Ĵ����ṹ���塣��ַƫ����:0x36C����ֵ:0x03E07BFF�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vdec_div_auto_reduce_bypass : 1;  /* bit[0]    : Ӳ���Զ���Ƶ����bypass���ã�
                                                                       0����bypass��
                                                                       1��bypass�� */
        unsigned int  vdec_auto_waitcfg_in        : 10; /* bit[1-10] : Ӳ�������Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  vdec_auto_waitcfg_out       : 10; /* bit[11-20]: Ӳ���˳��Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  vdec_div_auto_cfg           : 6;  /* bit[21-26]: Ӳ���Զ���Ƶ��������
                                                                       6'h00:1��
                                                                       6'h01:2��
                                                                       ��
                                                                       6'h3F:64�� */
        unsigned int  vdec_vcodecbus_cfg_bypass   : 1;  /* bit[27]   : cfg �Ƿ�����Զ���Ƶ�ж�������
                                                                       1'h0:���룻
                                                                       1'h1:�����룻 */
        unsigned int  reserved                    : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV3_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_div_auto_reduce_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_div_auto_reduce_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_auto_waitcfg_in_START         (1)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_auto_waitcfg_in_END           (10)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_auto_waitcfg_out_START        (11)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_auto_waitcfg_out_END          (20)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_div_auto_cfg_START            (21)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_div_auto_cfg_END              (26)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_vcodecbus_cfg_bypass_START    (27)
#define SOC_CRGPERIPH_PERI_AUTODIV3_vdec_vcodecbus_cfg_bypass_END      (27)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV4_UNION
 �ṹ˵��  : PERI_AUTODIV4 �Ĵ����ṹ���塣��ַƫ����:0x370����ֵ:0x03E07BFF�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vivobus_div_auto_reduce_bypass : 1;  /* bit[0]    : Ӳ���Զ���Ƶ����bypass���ã�
                                                                          0����bypass��
                                                                          1��bypass�� */
        unsigned int  vivobus_auto_waitcfg_in        : 10; /* bit[1-10] : Ӳ�������Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  vivobus_auto_waitcfg_out       : 9;  /* bit[11-19]: Ӳ���˳��Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  vivobus_ispa7_wfi_bypass       : 1;  /* bit[20]   : ispa7_wfi �Ƿ����vivobus�Զ���Ƶ�ж�������
                                                                          1'h0:���룻
                                                                          1'h1:�����룻 */
        unsigned int  vivobus_div_auto_cfg           : 6;  /* bit[21-26]: Ӳ���Զ���Ƶ��������
                                                                          6'h00:1��
                                                                          6'h01:2��
                                                                          ��
                                                                          6'h3F:64�� */
        unsigned int  vivobus_vivo_cfg_bypass        : 1;  /* bit[27]   : cfg �Ƿ�����Զ���Ƶ�ж�������
                                                                          1'h0:���룻
                                                                          1'h1:�����룻 */
        unsigned int  vivobus_dss0_bypass            : 1;  /* bit[28]   : dss0 �Ƿ�����Զ���Ƶ�ж������� */
        unsigned int  vivobus_dss1_bypass            : 1;  /* bit[29]   : dss1 �Ƿ�����Զ���Ƶ�ж������� */
        unsigned int  vivobus_isp_bypass             : 1;  /* bit[30]   : isp �Ƿ�����Զ���Ƶ�ж������� */
        unsigned int  vivobus_ispa7_bypass           : 1;  /* bit[31]   : iaps7״̬�Ƿ�����Զ���Ƶ�ж�������
                                                                          1'h0:���룻
                                                                          1'h1:�����룻 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV4_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_div_auto_reduce_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_div_auto_reduce_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_auto_waitcfg_in_START         (1)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_auto_waitcfg_in_END           (10)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_auto_waitcfg_out_START        (11)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_auto_waitcfg_out_END          (19)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_ispa7_wfi_bypass_START        (20)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_ispa7_wfi_bypass_END          (20)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_div_auto_cfg_START            (21)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_div_auto_cfg_END              (26)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_vivo_cfg_bypass_START         (27)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_vivo_cfg_bypass_END           (27)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_dss0_bypass_START             (28)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_dss0_bypass_END               (28)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_dss1_bypass_START             (29)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_dss1_bypass_END               (29)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_isp_bypass_START              (30)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_isp_bypass_END                (30)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_ispa7_bypass_START            (31)
#define SOC_CRGPERIPH_PERI_AUTODIV4_vivobus_ispa7_bypass_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV5_UNION
 �ṹ˵��  : PERI_AUTODIV5 �Ĵ����ṹ���塣��ַƫ����:0x374����ֵ:0x03E07BFF�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vcodecbus_div_auto_reduce_bypass : 1;  /* bit[0]    : Ӳ���Զ���Ƶ����bypass���ã�
                                                                            0����bypass��
                                                                            1��bypass�� */
        unsigned int  vcodecbus_auto_waitcfg_in        : 10; /* bit[1-10] : Ӳ�������Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  vcodecbus_auto_waitcfg_out       : 10; /* bit[11-20]: Ӳ���˳��Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  vcodecbus_div_auto_cfg           : 6;  /* bit[21-26]: Ӳ���Զ���Ƶ��������
                                                                            6'h00:1��
                                                                            6'h01:2��
                                                                            ��
                                                                            6'h3F:64�� */
        unsigned int  vcodecbus_vcodec_cfg_bypass      : 1;  /* bit[27]   : cfg �Ƿ�����Զ���Ƶ�ж�������
                                                                            1'h0:���룻
                                                                            1'h1:�����룻 */
        unsigned int  reserved_0                       : 1;  /* bit[28]   : ������ */
        unsigned int  reserved_1                       : 1;  /* bit[29]   : ������ */
        unsigned int  vcodecbus_venc_bypass            : 1;  /* bit[30]   : venc �Ƿ�����Զ���Ƶ�ж������� */
        unsigned int  vcodecbus_vdec_bypass            : 1;  /* bit[31]   : vdec״̬�Ƿ�����Զ���Ƶ�ж�������
                                                                            1'h0:���룻
                                                                            1'h1:�����룻 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV5_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_div_auto_reduce_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_div_auto_reduce_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_auto_waitcfg_in_START         (1)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_auto_waitcfg_in_END           (10)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_auto_waitcfg_out_START        (11)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_auto_waitcfg_out_END          (20)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_div_auto_cfg_START            (21)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_div_auto_cfg_END              (26)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_vcodec_cfg_bypass_START       (27)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_vcodec_cfg_bypass_END         (27)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_venc_bypass_START             (30)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_venc_bypass_END               (30)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_vdec_bypass_START             (31)
#define SOC_CRGPERIPH_PERI_AUTODIV5_vcodecbus_vdec_bypass_END               (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV6_UNION
 �ṹ˵��  : PERI_AUTODIV6 �Ĵ����ṹ���塣��ַƫ����:0x378����ֵ:0x03E07BFF�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sysbus_div_auto_reduce_bypass_lpm3 : 1;  /* bit[0]    : Ӳ���Զ���Ƶ����bypass���ã�
                                                                              0����bypass��
                                                                              1��bypass�� */
        unsigned int  sysbus_auto_waitcfg_in             : 10; /* bit[1-10] : Ӳ�������Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  sysbus_auto_waitcfg_out            : 10; /* bit[11-20]: Ӳ���˳��Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  sysbus_div_auto_cfg                : 6;  /* bit[21-26]: Ӳ���Զ���Ƶ��������
                                                                              6'h00:1��
                                                                              6'h01:2��
                                                                              ��
                                                                              6'h3F:64�� */
        unsigned int  reserved                           : 5;  /* bit[27-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV6_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_div_auto_reduce_bypass_lpm3_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_div_auto_reduce_bypass_lpm3_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_auto_waitcfg_in_START              (1)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_auto_waitcfg_in_END                (10)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_auto_waitcfg_out_START             (11)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_auto_waitcfg_out_END               (20)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_div_auto_cfg_START                 (21)
#define SOC_CRGPERIPH_PERI_AUTODIV6_sysbus_div_auto_cfg_END                   (26)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV7_UNION
 �ṹ˵��  : PERI_AUTODIV7 �Ĵ����ṹ���塣��ַƫ����:0x37C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sysbus_aobus_bypass         : 1;  /* bit[0]    : aobus �Ƿ�����Զ���Ƶ�ж�������
                                                                       1'h0:���룻
                                                                       1'h1:�����룻 */
        unsigned int  sysbus_top_cssys_bypass     : 1;  /* bit[1]    :  */
        unsigned int  sysbus_perf_stat_bypass     : 1;  /* bit[2]    :  */
        unsigned int  sysbus_usb3_bypass          : 1;  /* bit[3]    :  */
        unsigned int  sysbus_secp_bypass          : 1;  /* bit[4]    :  */
        unsigned int  sysbus_secs_bypass          : 1;  /* bit[5]    :  */
        unsigned int  sysbus_socp_bypass          : 1;  /* bit[6]    :  */
        unsigned int  sysbus_dmac_mst_bypass      : 1;  /* bit[7]    :  */
        unsigned int  sysbus_emmc0_bypass         : 1;  /* bit[8]    :  */
        unsigned int  sysbus_emmc1_bypass         : 1;  /* bit[9]    :  */
        unsigned int  sysbus_mmc1bus_bypass       : 1;  /* bit[10]   :  */
        unsigned int  reserved_0                  : 1;  /* bit[11]   :  */
        unsigned int  sysbus_cci2sysbus_bypass    : 1;  /* bit[12]   :  */
        unsigned int  sysbus_modem_mst_bypass     : 1;  /* bit[13]   :  */
        unsigned int  reserved_1                  : 1;  /* bit[14]   :  */
        unsigned int  sysbus_djtag_mst_bypass     : 1;  /* bit[15]   :  */
        unsigned int  sysbus_lpm3_mst_bypass      : 1;  /* bit[16]   :  */
        unsigned int  sysbus_a72cfg_bypass        : 1;  /* bit[17]   :  */
        unsigned int  sysbus_ivp32_mst_bypass     : 1;  /* bit[18]   :  */
        unsigned int  sysbus_mmc0bus_sdio0_bypass : 1;  /* bit[19]   :  */
        unsigned int  reserved_2                  : 6;  /* bit[20-25]:  */
        unsigned int  cfgbus_vivo_cfg_bypass      : 1;  /* bit[26]   :  */
        unsigned int  cfgbus_vcodec_cfg_bypass    : 1;  /* bit[27]   :  */
        unsigned int  reserved_3                  : 1;  /* bit[28]   :  */
        unsigned int  cfgbus_djtag_mst_bypass     : 1;  /* bit[29]   :  */
        unsigned int  cfgbus_lpm3_mst_bypass      : 1;  /* bit[30]   :  */
        unsigned int  cfgbus_a7tocfg_bypass       : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV7_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_aobus_bypass_START          (0)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_aobus_bypass_END            (0)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_top_cssys_bypass_START      (1)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_top_cssys_bypass_END        (1)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_perf_stat_bypass_START      (2)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_perf_stat_bypass_END        (2)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_usb3_bypass_START           (3)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_usb3_bypass_END             (3)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_secp_bypass_START           (4)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_secp_bypass_END             (4)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_secs_bypass_START           (5)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_secs_bypass_END             (5)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_socp_bypass_START           (6)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_socp_bypass_END             (6)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_dmac_mst_bypass_START       (7)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_dmac_mst_bypass_END         (7)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_emmc0_bypass_START          (8)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_emmc0_bypass_END            (8)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_emmc1_bypass_START          (9)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_emmc1_bypass_END            (9)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_mmc1bus_bypass_START        (10)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_mmc1bus_bypass_END          (10)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_cci2sysbus_bypass_START     (12)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_cci2sysbus_bypass_END       (12)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_modem_mst_bypass_START      (13)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_modem_mst_bypass_END        (13)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_djtag_mst_bypass_START      (15)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_djtag_mst_bypass_END        (15)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_lpm3_mst_bypass_START       (16)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_lpm3_mst_bypass_END         (16)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_a72cfg_bypass_START         (17)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_a72cfg_bypass_END           (17)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_ivp32_mst_bypass_START      (18)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_ivp32_mst_bypass_END        (18)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_mmc0bus_sdio0_bypass_START  (19)
#define SOC_CRGPERIPH_PERI_AUTODIV7_sysbus_mmc0bus_sdio0_bypass_END    (19)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_vivo_cfg_bypass_START       (26)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_vivo_cfg_bypass_END         (26)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_vcodec_cfg_bypass_START     (27)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_vcodec_cfg_bypass_END       (27)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_djtag_mst_bypass_START      (29)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_djtag_mst_bypass_END        (29)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_lpm3_mst_bypass_START       (30)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_lpm3_mst_bypass_END         (30)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_a7tocfg_bypass_START        (31)
#define SOC_CRGPERIPH_PERI_AUTODIV7_cfgbus_a7tocfg_bypass_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV8_UNION
 �ṹ˵��  : PERI_AUTODIV8 �Ĵ����ṹ���塣��ַƫ����:0x380����ֵ:0x03E07BFF�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���8��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfgbus_div_auto_reduce_bypass_lpm3      : 1;  /* bit[0]    : Ӳ���Զ���Ƶ����bypass���ã�
                                                                                   0����bypass��
                                                                                   1��bypass�� */
        unsigned int  cfgbus_auto_waitcfg_in                  : 10; /* bit[1-10] : Ӳ�������Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  cfgbus_auto_waitcfg_out                 : 10; /* bit[11-20]: Ӳ���˳��Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  cfgbus_div_auto_cfg                     : 6;  /* bit[21-26]: Ӳ���Զ���Ƶ��������
                                                                                   6'h00:1��
                                                                                   6'h01:2��
                                                                                   ��
                                                                                   6'h3F:64�� */
        unsigned int  cfgbus_sysbus_relate_auto_reduce_bypass : 1;  /* bit[27]   : sysbus��Ƶʱcfgbus�Ƿ��Զ��˳��Զ���Ƶbypass���ƣ�sysbus�Զ���Ƶʱcfgbus�Ƿ��Զ��˳��Զ���Ƶ����
                                                                                   1'h0:��bypass���˳�����
                                                                                   1'h1:bypass�����˳����� */
        unsigned int  reserved                                : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV8_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_div_auto_reduce_bypass_lpm3_START       (0)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_div_auto_reduce_bypass_lpm3_END         (0)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_auto_waitcfg_in_START                   (1)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_auto_waitcfg_in_END                     (10)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_auto_waitcfg_out_START                  (11)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_auto_waitcfg_out_END                    (20)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_div_auto_cfg_START                      (21)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_div_auto_cfg_END                        (26)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_sysbus_relate_auto_reduce_bypass_START  (27)
#define SOC_CRGPERIPH_PERI_AUTODIV8_cfgbus_sysbus_relate_auto_reduce_bypass_END    (27)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV9_UNION
 �ṹ˵��  : PERI_AUTODIV9 �Ĵ����ṹ���塣��ַƫ����:0x384����ֵ:0x03E07BFF�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���9��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmabus_div_auto_reduce_bypass_lpm3      : 1;  /* bit[0]    : Ӳ���Զ���Ƶ����bypass���ã�
                                                                                   0����bypass��
                                                                                   1��bypass�� */
        unsigned int  dmabus_auto_waitcfg_in                  : 10; /* bit[1-10] : Ӳ�������Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  dmabus_auto_waitcfg_out                 : 10; /* bit[11-20]: Ӳ���˳��Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  dmabus_div_auto_cfg                     : 6;  /* bit[21-26]: Ӳ���Զ���Ƶ��������
                                                                                   6'h00:1��
                                                                                   6'h01:2��
                                                                                   ��
                                                                                   6'h3F:64�� */
        unsigned int  dmabus_dmac_mst_bypass                  : 1;  /* bit[27]   : dma_mst �Ƿ�����Զ���Ƶ�ж�������
                                                                                   1'h0:���룻
                                                                                   1'h1:�����룻 */
        unsigned int  dmabus_sysbus_relate_auto_reduce_bypass : 1;  /* bit[28]   : sysbus��Ƶʱdmabus�Ƿ��Զ��˳��Զ���Ƶbypass���ƣ�sysbus�Զ���Ƶʱdmabus�Ƿ��Զ��˳��Զ���Ƶ����
                                                                                   1'h0:��bypass���˳�����
                                                                                   1'h1:bypass�����˳����� */
        unsigned int  reserved                                : 3;  /* bit[29-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV9_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_div_auto_reduce_bypass_lpm3_START       (0)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_div_auto_reduce_bypass_lpm3_END         (0)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_auto_waitcfg_in_START                   (1)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_auto_waitcfg_in_END                     (10)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_auto_waitcfg_out_START                  (11)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_auto_waitcfg_out_END                    (20)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_div_auto_cfg_START                      (21)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_div_auto_cfg_END                        (26)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_dmac_mst_bypass_START                   (27)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_dmac_mst_bypass_END                     (27)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_sysbus_relate_auto_reduce_bypass_START  (28)
#define SOC_CRGPERIPH_PERI_AUTODIV9_dmabus_sysbus_relate_auto_reduce_bypass_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV10_UNION
 �ṹ˵��  : PERI_AUTODIV10 �Ĵ����ṹ���塣��ַƫ����:0x388����ֵ:0x01F07BFF�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���10��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbgbus_div_auto_reduce_bypass_lpm3      : 1;  /* bit[0]    : Ӳ���Զ���Ƶ����bypass���ã�
                                                                                   0����bypass��
                                                                                   1��bypass�� */
        unsigned int  dbgbus_auto_waitcfg_in                  : 10; /* bit[1-10] : Ӳ�������Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  dbgbus_auto_waitcfg_out                 : 8;  /* bit[11-18]: Ӳ���˳��Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  dbgbus_sysbus_relate_auto_reduce_bypass : 1;  /* bit[19]   : sysbus��Ƶʱdbgbus�Ƿ��Զ��˳��Զ���Ƶbypass���ƣ�sysbus�Զ���Ƶʱdbgbus�Ƿ��Զ��˳��Զ���Ƶ����
                                                                                   1'h0:��bypass���˳�����
                                                                                   1'h1:bypass�����˳����� */
        unsigned int  dbgbus_div_auto_cfg                     : 6;  /* bit[20-25]: Ӳ���Զ���Ƶ��������
                                                                                   6'h00:1��
                                                                                   6'h01:2��
                                                                                   ��
                                                                                   6'h3F:64�� */
        unsigned int  dbgbus_socp_bypass                      : 1;  /* bit[26]   : socp�Ƿ�����Զ���Ƶ�ж�������
                                                                                   1'h0:���룻
                                                                                   1'h1:�����룻 */
        unsigned int  dbgbus_secp_bypass                      : 1;  /* bit[27]   : secp�Ƿ�����Զ���Ƶ�ж�������
                                                                                   1'h0:���룻
                                                                                   1'h1:�����룻 */
        unsigned int  dbgbus_secs_bypass                      : 1;  /* bit[28]   : secs�Ƿ�����Զ���Ƶ�ж�������
                                                                                   1'h0:���룻
                                                                                   1'h1:�����룻 */
        unsigned int  dbgbus_usb3_bypass                      : 1;  /* bit[29]   : usb3�Ƿ�����Զ���Ƶ�ж�������
                                                                                   1'h0:���룻
                                                                                   1'h1:�����룻 */
        unsigned int  dbgbus_perf_stat_bypass                 : 1;  /* bit[30]   : perf_stat�Ƿ�����Զ���Ƶ�ж�������
                                                                                   1'h0:���룻
                                                                                   1'h1:�����룻 */
        unsigned int  dbgbus_top_cssys_bypass                 : 1;  /* bit[31]   : top_cssys״̬�Ƿ�����Զ���Ƶ�ж�������
                                                                                   1'h0:���룻
                                                                                   1'h1:�����룻 */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV10_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_div_auto_reduce_bypass_lpm3_START       (0)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_div_auto_reduce_bypass_lpm3_END         (0)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_auto_waitcfg_in_START                   (1)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_auto_waitcfg_in_END                     (10)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_auto_waitcfg_out_START                  (11)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_auto_waitcfg_out_END                    (18)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_sysbus_relate_auto_reduce_bypass_START  (19)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_sysbus_relate_auto_reduce_bypass_END    (19)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_div_auto_cfg_START                      (20)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_div_auto_cfg_END                        (25)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_socp_bypass_START                       (26)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_socp_bypass_END                         (26)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_secp_bypass_START                       (27)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_secp_bypass_END                         (27)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_secs_bypass_START                       (28)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_secs_bypass_END                         (28)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_usb3_bypass_START                       (29)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_usb3_bypass_END                         (29)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_perf_stat_bypass_START                  (30)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_perf_stat_bypass_END                    (30)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_top_cssys_bypass_START                  (31)
#define SOC_CRGPERIPH_PERI_AUTODIV10_dbgbus_top_cssys_bypass_END                    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV11_UNION
 �ṹ˵��  : PERI_AUTODIV11 �Ĵ����ṹ���塣��ַƫ����:0x38C����ֵ:0x03E07BFF�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���11��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emmc0bus_div_auto_reduce_bypass_lpm3      : 1;  /* bit[0]    : Ӳ���Զ���Ƶ����bypass���ã�
                                                                                     0����bypass��
                                                                                     1��bypass�� */
        unsigned int  emmc0bus_auto_waitcfg_in                  : 10; /* bit[1-10] : Ӳ�������Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  emmc0bus_auto_waitcfg_out                 : 10; /* bit[11-20]: Ӳ���˳��Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  emmc0bus_div_auto_cfg                     : 6;  /* bit[21-26]: Ӳ���Զ���Ƶ��������
                                                                                     6'h00:1��
                                                                                     6'h01:2��
                                                                                     ��
                                                                                     6'h3F:64�� */
        unsigned int  emmc0bus_emm0_bypass                      : 1;  /* bit[27]   : emm0 �Ƿ�����Զ���Ƶ�ж�������
                                                                                     1'h0:���룻
                                                                                     1'h1:�����룻 */
        unsigned int  emmc0bus_emm1_bypass                      : 1;  /* bit[28]   : emm1 �Ƿ�����Զ���Ƶ�ж�������
                                                                                     1'h0:���룻
                                                                                     1'h1:�����룻 */
        unsigned int  emmc0bus_sdio_bypass                      : 1;  /* bit[29]   : sdio0 �Ƿ�����Զ���Ƶ�ж�������
                                                                                     1'h0:���룻
                                                                                     1'h1:�����룻 */
        unsigned int  emmc0bus_sysbus_relate_auto_reduce_bypass : 1;  /* bit[30]   : sysbus��Ƶʱemmc0bus�Ƿ��Զ��˳��Զ���Ƶbypass���ƣ�sysbus�Զ���Ƶʱemmc0bus�Ƿ��Զ��˳��Զ���Ƶ����
                                                                                     1'h0:��bypass���˳�����
                                                                                     1'h1:bypass�����˳����� */
        unsigned int  reserved                                  : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV11_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_div_auto_reduce_bypass_lpm3_START       (0)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_div_auto_reduce_bypass_lpm3_END         (0)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_auto_waitcfg_in_START                   (1)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_auto_waitcfg_in_END                     (10)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_auto_waitcfg_out_START                  (11)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_auto_waitcfg_out_END                    (20)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_div_auto_cfg_START                      (21)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_div_auto_cfg_END                        (26)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_emm0_bypass_START                       (27)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_emm0_bypass_END                         (27)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_emm1_bypass_START                       (28)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_emm1_bypass_END                         (28)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_sdio_bypass_START                       (29)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_sdio_bypass_END                         (29)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_sysbus_relate_auto_reduce_bypass_START  (30)
#define SOC_CRGPERIPH_PERI_AUTODIV11_emmc0bus_sysbus_relate_auto_reduce_bypass_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV12_UNION
 �ṹ˵��  : PERI_AUTODIV12 �Ĵ����ṹ���塣��ַƫ����:0x390����ֵ:0x03E07BFF�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���12��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emmc1bus_div_auto_reduce_bypass_lpm3      : 1;  /* bit[0]    : Ӳ���Զ���Ƶ����bypass���ã�
                                                                                     0����bypass��
                                                                                     1��bypass�� */
        unsigned int  emmc1bus_auto_waitcfg_in                  : 10; /* bit[1-10] : Ӳ�������Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  emmc1bus_auto_waitcfg_out                 : 10; /* bit[11-20]: Ӳ���˳��Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  emmc1bus_div_auto_cfg                     : 6;  /* bit[21-26]: Ӳ���Զ���Ƶ��������
                                                                                     6'h00:1��
                                                                                     6'h01:2��
                                                                                     ��
                                                                                     6'h3F:64�� */
        unsigned int  emmc1bus_other_bypass                     : 1;  /* bit[27]   : emmc1bus �Ƿ�����Զ���Ƶ�ж�������
                                                                                     1'h0:���룻
                                                                                     1'h1:�����룻 */
        unsigned int  emmc1bus_sysbus_relate_auto_reduce_bypass : 1;  /* bit[28]   : sysbus��Ƶʱemmc1bus�Ƿ��Զ��˳��Զ���Ƶbypass���ƣ�sysbus�Զ���Ƶʱemmc1bus�Ƿ��Զ��˳��Զ���Ƶ����
                                                                                     1'h0:��bypass���˳�����
                                                                                     1'h1:bypass�����˳����� */
        unsigned int  reserved                                  : 3;  /* bit[29-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV12_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_div_auto_reduce_bypass_lpm3_START       (0)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_div_auto_reduce_bypass_lpm3_END         (0)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_auto_waitcfg_in_START                   (1)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_auto_waitcfg_in_END                     (10)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_auto_waitcfg_out_START                  (11)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_auto_waitcfg_out_END                    (20)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_div_auto_cfg_START                      (21)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_div_auto_cfg_END                        (26)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_other_bypass_START                      (27)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_other_bypass_END                        (27)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_sysbus_relate_auto_reduce_bypass_START  (28)
#define SOC_CRGPERIPH_PERI_AUTODIV12_emmc1bus_sysbus_relate_auto_reduce_bypass_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV13_UNION
 �ṹ˵��  : PERI_AUTODIV13 �Ĵ����ṹ���塣��ַƫ����:0x394����ֵ:0x03E07BFF�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���13��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpmcu_div_auto_reduce_bypass : 1;  /* bit[0]    : Ӳ���Զ���Ƶ����bypass���ã�
                                                                        0����bypass��
                                                                        1��bypass�� */
        unsigned int  lpmcu_auto_waitcfg_in        : 10; /* bit[1-10] : Ӳ�������Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  lpmcu_auto_waitcfg_out       : 10; /* bit[11-20]: Ӳ���˳��Զ���ƵIDLE�ȴ�ʱ���������� */
        unsigned int  lpmcu_div_auto_cfg           : 6;  /* bit[21-26]: Ӳ���Զ���Ƶ��������
                                                                        6'h00:1��
                                                                        6'h01:2��
                                                                        ��
                                                                        6'h3F:64�� */
        unsigned int  reserved                     : 5;  /* bit[27-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV13_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_div_auto_reduce_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_div_auto_reduce_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_auto_waitcfg_in_START         (1)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_auto_waitcfg_in_END           (10)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_auto_waitcfg_out_START        (11)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_auto_waitcfg_out_END          (20)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_div_auto_cfg_START            (21)
#define SOC_CRGPERIPH_PERI_AUTODIV13_lpmcu_div_auto_cfg_END              (26)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV14_UNION
 �ṹ˵��  : PERI_AUTODIV14 �Ĵ����ṹ���塣��ַƫ����:0x398����ֵ:0x00007BFF�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���14��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_auto_swtotcxo_bypass : 1;  /* bit[0]    : Ӳ���Զ��л�tcxo����bypass���ã�
                                                                    0����bypass��
                                                                    1��bypass�� */
        unsigned int  a57_auto_waitcfg_in      : 10; /* bit[1-10] : Ӳ�������Զ��л�tcxo�ȴ�ʱ���������� */
        unsigned int  a57_auto_waitcfg_out     : 10; /* bit[11-20]: Ӳ���˳��Զ��л�tcxo�ȴ�ʱ���������� */
        unsigned int  reserved                 : 11; /* bit[21-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV14_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_swtotcxo_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_swtotcxo_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_waitcfg_in_START       (1)
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_waitcfg_in_END         (10)
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_waitcfg_out_START      (11)
#define SOC_CRGPERIPH_PERI_AUTODIV14_a57_auto_waitcfg_out_END        (20)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV15_UNION
 �ṹ˵��  : PERI_AUTODIV15 �Ĵ����ṹ���塣��ַƫ����:0x39C����ֵ:0x00007BFF�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���15��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_auto_swtotcxo_bypass : 1;  /* bit[0]    : Ӳ���Զ��л�tcxo����bypass���ã�
                                                                    0����bypass��
                                                                    1��bypass�� */
        unsigned int  a53_auto_waitcfg_in      : 10; /* bit[1-10] : Ӳ�������Զ��л�tcxo�ȴ�ʱ���������� */
        unsigned int  a53_auto_waitcfg_out     : 10; /* bit[11-20]: Ӳ���˳��Զ��л�tcxo�ȴ�ʱ���������� */
        unsigned int  reserved                 : 11; /* bit[21-31]: ������ */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV15_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_swtotcxo_bypass_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_swtotcxo_bypass_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_waitcfg_in_START       (1)
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_waitcfg_in_END         (10)
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_waitcfg_out_START      (11)
#define SOC_CRGPERIPH_PERI_AUTODIV15_a53_auto_waitcfg_out_END        (20)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV_ACPU_UNION
 �ṹ˵��  : PERI_AUTODIV_ACPU �Ĵ����ṹ���塣��ַƫ����:0x404����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���ACPU��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emmc1bus_div_auto_reduce_bypass_acpu : 1;  /* bit[0]    : acpu����ͶƱ�Ƿ�bypass �����Զ���Ƶ */
        unsigned int  emmc0bus_div_auto_reduce_bypass_acpu : 1;  /* bit[1]    :  */
        unsigned int  dbgbus_div_auto_reduce_bypass_acpu   : 1;  /* bit[2]    :  */
        unsigned int  dmabus_div_auto_reduce_bypass_acpu   : 1;  /* bit[3]    :  */
        unsigned int  cfgbus_div_auto_reduce_bypass_acpu   : 1;  /* bit[4]    :  */
        unsigned int  sysbus_div_auto_reduce_bypass_acpu   : 1;  /* bit[5]    :  */
        unsigned int  reserved                             : 10; /* bit[6-15] : ������ */
        unsigned int  autodivmasken                        : 16; /* bit[16-31]: peri_autodiv_acpuÿ������λ��ʹ��λ��
                                                                                ֻ�е�autodivmasken��Ӧ�ı���λΪ1'b1��peri_autodiv_acpu��Ӧ�ı���λ�������á�autodivmasken[0]����peri_autodiv_acpu[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV_ACPU_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_emmc1bus_div_auto_reduce_bypass_acpu_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_emmc1bus_div_auto_reduce_bypass_acpu_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_emmc0bus_div_auto_reduce_bypass_acpu_START  (1)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_emmc0bus_div_auto_reduce_bypass_acpu_END    (1)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_dbgbus_div_auto_reduce_bypass_acpu_START    (2)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_dbgbus_div_auto_reduce_bypass_acpu_END      (2)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_dmabus_div_auto_reduce_bypass_acpu_START    (3)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_dmabus_div_auto_reduce_bypass_acpu_END      (3)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_cfgbus_div_auto_reduce_bypass_acpu_START    (4)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_cfgbus_div_auto_reduce_bypass_acpu_END      (4)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_sysbus_div_auto_reduce_bypass_acpu_START    (5)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_sysbus_div_auto_reduce_bypass_acpu_END      (5)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_autodivmasken_START                         (16)
#define SOC_CRGPERIPH_PERI_AUTODIV_ACPU_autodivmasken_END                           (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERI_AUTODIV_MCPU_UNION
 �ṹ˵��  : PERI_AUTODIV_MCPU �Ĵ����ṹ���塣��ַƫ����:0x408����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����Զ���Ƶ���ƼĴ���MCPU��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  emmc1bus_div_auto_reduce_bypass_mcpu : 1;  /* bit[0]    : mcpu����ͶƱ�Ƿ�bypass �����Զ���Ƶ */
        unsigned int  emmc0bus_div_auto_reduce_bypass_mcpu : 1;  /* bit[1]    :  */
        unsigned int  dbgbus_div_auto_reduce_bypass_mcpu   : 1;  /* bit[2]    :  */
        unsigned int  dmabus_div_auto_reduce_bypass_mcpu   : 1;  /* bit[3]    :  */
        unsigned int  cfgbus_div_auto_reduce_bypass_mcpu   : 1;  /* bit[4]    :  */
        unsigned int  sysbus_div_auto_reduce_bypass_mcpu   : 1;  /* bit[5]    :  */
        unsigned int  reserved                             : 10; /* bit[6-15] :  */
        unsigned int  autodivmasken                        : 16; /* bit[16-31]: peri_autodiv_mcpuÿ������λ��ʹ��λ��
                                                                                ֻ�е�autodivmasken��Ӧ�ı���λΪ1'b1��peri_autodiv_mcpu��Ӧ�ı���λ�������á�autodivmasken[0]����peri_autodiv_mcpu[0]��maskʹ��λ��д1��Ч�� */
    } reg;
} SOC_CRGPERIPH_PERI_AUTODIV_MCPU_UNION;
#endif
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_emmc1bus_div_auto_reduce_bypass_mcpu_START  (0)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_emmc1bus_div_auto_reduce_bypass_mcpu_END    (0)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_emmc0bus_div_auto_reduce_bypass_mcpu_START  (1)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_emmc0bus_div_auto_reduce_bypass_mcpu_END    (1)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_dbgbus_div_auto_reduce_bypass_mcpu_START    (2)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_dbgbus_div_auto_reduce_bypass_mcpu_END      (2)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_dmabus_div_auto_reduce_bypass_mcpu_START    (3)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_dmabus_div_auto_reduce_bypass_mcpu_END      (3)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_cfgbus_div_auto_reduce_bypass_mcpu_START    (4)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_cfgbus_div_auto_reduce_bypass_mcpu_END      (4)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_sysbus_div_auto_reduce_bypass_mcpu_START    (5)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_sysbus_div_auto_reduce_bypass_mcpu_END      (5)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_autodivmasken_START                         (16)
#define SOC_CRGPERIPH_PERI_AUTODIV_MCPU_autodivmasken_END                           (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PEREN6_UNION
 �ṹ˵��  : PEREN6 �Ĵ����ṹ���塣��ַƫ����:0x410����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��ʹ�ܼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_autodiv_ivp       : 1;  /* bit[0]    : ����ʱ��ʹ�ܿ��ƣ�
                                                                    0��д0��Ч����
                                                                    1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_autodiv_ispa7     : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_autodiv_venc      : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_autodiv_vdec      : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_autodiv_vivobus   : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_autodiv_vcodecbus : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_autodiv_sysbus    : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_autodiv_cfgbus    : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_autodiv_dmabus    : 1;  /* bit[8]    :  */
        unsigned int  gt_clk_autodiv_dbgbus    : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_autodiv_emmc0bus  : 1;  /* bit[10]   :  */
        unsigned int  gt_clk_autodiv_emmc1bus  : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_autodiv_lpmcu     : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_autodiv_a57       : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_autodiv_a53       : 1;  /* bit[14]   :  */
        unsigned int  reserved                 : 17; /* bit[15-31]: ����ʱ��ʹ�ܿ��ƣ�
                                                                    0��д0��Ч����
                                                                    1��ʹ��IPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PEREN6_UNION;
#endif
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_ivp_START        (0)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_ivp_END          (0)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_ispa7_START      (1)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_ispa7_END        (1)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_venc_START       (2)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_venc_END         (2)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vdec_START       (3)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vdec_END         (3)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vivobus_START    (4)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vivobus_END      (4)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vcodecbus_START  (5)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_vcodecbus_END    (5)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_sysbus_START     (6)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_sysbus_END       (6)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_cfgbus_START     (7)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_cfgbus_END       (7)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_dmabus_START     (8)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_dmabus_END       (8)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_dbgbus_START     (9)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_dbgbus_END       (9)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_emmc0bus_START   (10)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_emmc0bus_END     (10)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_emmc1bus_START   (11)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_emmc1bus_END     (11)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_lpmcu_START      (12)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_lpmcu_END        (12)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_a57_START        (13)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_a57_END          (13)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_a53_START        (14)
#define SOC_CRGPERIPH_PEREN6_gt_clk_autodiv_a53_END          (14)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERDIS6_UNION
 �ṹ˵��  : PERDIS6 �Ĵ����ṹ���塣��ַƫ����:0x414����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ�ӽ�ֹ�Ĵ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_autodiv_ivp       : 1;  /* bit[0]    : ����ʱ�ӽ�ֹ���ƣ�
                                                                    0��д0��Ч����
                                                                    1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_autodiv_ispa7     : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_autodiv_venc      : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_autodiv_vdec      : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_autodiv_vivobus   : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_autodiv_vcodecbus : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_autodiv_sysbus    : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_autodiv_cfgbus    : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_autodiv_dmabus    : 1;  /* bit[8]    :  */
        unsigned int  gt_clk_autodiv_dbgbus    : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_autodiv_emmc0bus  : 1;  /* bit[10]   :  */
        unsigned int  gt_clk_autodiv_emmc1bus  : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_autodiv_lpmcu     : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_autodiv_a57       : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_autodiv_a53       : 1;  /* bit[14]   :  */
        unsigned int  reserved                 : 17; /* bit[15-31]: ����ʱ�ӽ�ֹ���ƣ�
                                                                    0��д0��Ч����
                                                                    1����ֹIPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PERDIS6_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_ivp_START        (0)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_ivp_END          (0)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_ispa7_START      (1)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_ispa7_END        (1)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_venc_START       (2)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_venc_END         (2)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vdec_START       (3)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vdec_END         (3)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vivobus_START    (4)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vivobus_END      (4)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vcodecbus_START  (5)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_vcodecbus_END    (5)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_sysbus_START     (6)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_sysbus_END       (6)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_cfgbus_START     (7)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_cfgbus_END       (7)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_dmabus_START     (8)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_dmabus_END       (8)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_dbgbus_START     (9)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_dbgbus_END       (9)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_emmc0bus_START   (10)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_emmc0bus_END     (10)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_emmc1bus_START   (11)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_emmc1bus_END     (11)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_lpmcu_START      (12)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_lpmcu_END        (12)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_a57_START        (13)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_a57_END          (13)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_a53_START        (14)
#define SOC_CRGPERIPH_PERDIS6_gt_clk_autodiv_a53_END          (14)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERCLKEN6_UNION
 �ṹ˵��  : PERCLKEN6 �Ĵ����ṹ���塣��ַƫ����:0x418����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��ʹ��״̬�Ĵ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_autodiv_ivp       : 1;  /* bit[0]    : ����ʱ��ʹ��״̬��
                                                                    0��IPʱ��ʹ�ܳ���״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_autodiv_ispa7     : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_autodiv_venc      : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_autodiv_vdec      : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_autodiv_vivobus   : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_autodiv_vcodecbus : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_autodiv_sysbus    : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_autodiv_cfgbus    : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_autodiv_dmabus    : 1;  /* bit[8]    :  */
        unsigned int  gt_clk_autodiv_dbgbus    : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_autodiv_emmc0bus  : 1;  /* bit[10]   :  */
        unsigned int  gt_clk_autodiv_emmc1bus  : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_autodiv_lpmcu     : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_autodiv_a57       : 1;  /* bit[13]   :  */
        unsigned int  gt_clk_autodiv_a53       : 1;  /* bit[14]   :  */
        unsigned int  reserved                 : 17; /* bit[15-31]: ����ʱ��ʹ��״̬��
                                                                    0��IPʱ��ʹ�ܳ���״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERCLKEN6_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_ivp_START        (0)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_ivp_END          (0)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_ispa7_START      (1)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_ispa7_END        (1)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_venc_START       (2)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_venc_END         (2)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vdec_START       (3)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vdec_END         (3)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vivobus_START    (4)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vivobus_END      (4)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vcodecbus_START  (5)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_vcodecbus_END    (5)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_sysbus_START     (6)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_sysbus_END       (6)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_cfgbus_START     (7)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_cfgbus_END       (7)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_dmabus_START     (8)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_dmabus_END       (8)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_dbgbus_START     (9)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_dbgbus_END       (9)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_emmc0bus_START   (10)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_emmc0bus_END     (10)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_emmc1bus_START   (11)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_emmc1bus_END     (11)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_lpmcu_START      (12)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_lpmcu_END        (12)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_a57_START        (13)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_a57_END          (13)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_a53_START        (14)
#define SOC_CRGPERIPH_PERCLKEN6_gt_clk_autodiv_a53_END          (14)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERSTAT6_UNION
 �ṹ˵��  : PERSTAT6 �Ĵ����ṹ���塣��ַƫ����:0x41C����ֵ:0xFFFF8000�����:32
 �Ĵ���˵��: ����ʱ������״̬�Ĵ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_autodiv_ivp       : 1;  /* bit[0]    : ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_autodiv_ispa7     : 1;  /* bit[1]    :  */
        unsigned int  gt_clk_autodiv_venc      : 1;  /* bit[2]    :  */
        unsigned int  gt_clk_autodiv_vdec      : 1;  /* bit[3]    :  */
        unsigned int  gt_clk_autodiv_vivobus   : 1;  /* bit[4]    :  */
        unsigned int  gt_clk_autodiv_vcodecbus : 1;  /* bit[5]    :  */
        unsigned int  gt_clk_autodiv_sysbus    : 1;  /* bit[6]    :  */
        unsigned int  gt_clk_autodiv_cfgbus    : 1;  /* bit[7]    :  */
        unsigned int  gt_clk_autodiv_dmabus    : 1;  /* bit[8]    :  */
        unsigned int  gt_clk_autodiv_dbgbus    : 1;  /* bit[9]    :  */
        unsigned int  gt_clk_autodiv_emmc0bus  : 1;  /* bit[10]   :  */
        unsigned int  gt_clk_autodiv_emmc1bus  : 1;  /* bit[11]   :  */
        unsigned int  gt_clk_autodiv_lpmcu     : 1;  /* bit[12]   :  */
        unsigned int  gt_clk_autodiv_a57       : 1;  /* bit[13]   : 1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_autodiv_a53       : 1;  /* bit[14]   : 0��IPʱ�ӽ�ֹ״̬�� */
        unsigned int  reserved                 : 17; /* bit[15-31]: ����ʱ������״̬��
                                                                    0��IPʱ�ӽ�ֹ״̬��
                                                                    1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERSTAT6_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_ivp_START        (0)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_ivp_END          (0)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_ispa7_START      (1)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_ispa7_END        (1)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_venc_START       (2)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_venc_END         (2)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vdec_START       (3)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vdec_END         (3)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vivobus_START    (4)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vivobus_END      (4)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vcodecbus_START  (5)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_vcodecbus_END    (5)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_sysbus_START     (6)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_sysbus_END       (6)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_cfgbus_START     (7)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_cfgbus_END       (7)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_dmabus_START     (8)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_dmabus_END       (8)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_dbgbus_START     (9)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_dbgbus_END       (9)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_emmc0bus_START   (10)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_emmc0bus_END     (10)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_emmc1bus_START   (11)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_emmc1bus_END     (11)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_lpmcu_START      (12)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_lpmcu_END        (12)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_a57_START        (13)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_a57_END          (13)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_a53_START        (14)
#define SOC_CRGPERIPH_PERSTAT6_gt_clk_autodiv_a53_END          (14)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PEREN7_UNION
 �ṹ˵��  : PEREN7 �Ĵ����ṹ���塣��ַƫ����:0x420����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ��ʹ�ܼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_rs0   : 1;  /* bit[0]   : ����ʱ��ʹ�ܿ��ƣ�
                                                              0��д0��Ч����
                                                              1��ʹ��IPʱ�ӡ� */
        unsigned int  gt_clk_ddrphy_rs1   : 1;  /* bit[1]   :  */
        unsigned int  gt_clk_ddrphy_rs2   : 1;  /* bit[2]   :  */
        unsigned int  gt_clk_ddrphy_rs3   : 1;  /* bit[3]   :  */
        unsigned int  gt_clk_ddrphy_gt    : 1;  /* bit[4]   : ddrphy rs/phy ���ʱ�����ſ� */
        unsigned int  reserved_0          : 1;  /* bit[5]   :  */
        unsigned int  gt_clk_ddrphy_rsadd : 1;  /* bit[6]   :  */
        unsigned int  reserved_1          : 25; /* bit[7-31]: ����ʱ��ʹ�ܿ��ƣ�
                                                              0��д0��Ч����
                                                              1��ʹ��IPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PEREN7_UNION;
#endif
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs0_START    (0)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs0_END      (0)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs1_START    (1)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs1_END      (1)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs2_START    (2)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs2_END      (2)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs3_START    (3)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rs3_END      (3)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_gt_START     (4)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_gt_END       (4)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rsadd_START  (6)
#define SOC_CRGPERIPH_PEREN7_gt_clk_ddrphy_rsadd_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERDIS7_UNION
 �ṹ˵��  : PERDIS7 �Ĵ����ṹ���塣��ַƫ����:0x424����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʱ�ӽ�ֹ�Ĵ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_rs0   : 1;  /* bit[0]   : ����ʱ�ӽ�ֹ���ƣ�
                                                              0��д0��Ч����
                                                              1����ֹIPʱ�ӡ� */
        unsigned int  gt_clk_ddrphy_rs1   : 1;  /* bit[1]   :  */
        unsigned int  gt_clk_ddrphy_rs2   : 1;  /* bit[2]   :  */
        unsigned int  gt_clk_ddrphy_rs3   : 1;  /* bit[3]   :  */
        unsigned int  gt_clk_ddrphy_gt    : 1;  /* bit[4]   : ddrphy rs/phy ���ʱ�����ſ� */
        unsigned int  reserved_0          : 1;  /* bit[5]   :  */
        unsigned int  gt_clk_ddrphy_rsadd : 1;  /* bit[6]   :  */
        unsigned int  reserved_1          : 25; /* bit[7-31]: ����ʱ�ӽ�ֹ���ƣ�
                                                              0��д0��Ч����
                                                              1����ֹIPʱ�ӡ� */
    } reg;
} SOC_CRGPERIPH_PERDIS7_UNION;
#endif
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs0_START    (0)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs0_END      (0)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs1_START    (1)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs1_END      (1)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs2_START    (2)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs2_END      (2)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs3_START    (3)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rs3_END      (3)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_gt_START     (4)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_gt_END       (4)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rsadd_START  (6)
#define SOC_CRGPERIPH_PERDIS7_gt_clk_ddrphy_rsadd_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERCLKEN7_UNION
 �ṹ˵��  : PERCLKEN7 �Ĵ����ṹ���塣��ַƫ����:0x428����ֵ:0x0000001F�����:32
 �Ĵ���˵��: ����ʱ��ʹ��״̬�Ĵ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_rs0   : 1;  /* bit[0]   : ����ʱ��ʹ��״̬��
                                                              0��IPʱ��ʹ�ܳ���״̬��
                                                              1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_ddrphy_rs1   : 1;  /* bit[1]   :  */
        unsigned int  gt_clk_ddrphy_rs2   : 1;  /* bit[2]   :  */
        unsigned int  gt_clk_ddrphy_rs3   : 1;  /* bit[3]   :  */
        unsigned int  gt_clk_ddrphy_gt    : 1;  /* bit[4]   : ddrphy rs/phy ���ʱ�����ſ� */
        unsigned int  reserved_0          : 1;  /* bit[5]   :  */
        unsigned int  gt_clk_ddrphy_rsadd : 1;  /* bit[6]   :  */
        unsigned int  reserved_1          : 25; /* bit[7-31]: ����ʱ��ʹ��״̬��
                                                              0��IPʱ��ʹ�ܳ���״̬��
                                                              1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERCLKEN7_UNION;
#endif
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs0_START    (0)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs0_END      (0)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs1_START    (1)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs1_END      (1)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs2_START    (2)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs2_END      (2)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs3_START    (3)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rs3_END      (3)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_gt_START     (4)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_gt_END       (4)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rsadd_START  (6)
#define SOC_CRGPERIPH_PERCLKEN7_gt_clk_ddrphy_rsadd_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_PERSTAT7_UNION
 �ṹ˵��  : PERSTAT7 �Ĵ����ṹ���塣��ַƫ����:0x42C����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: ����ʱ������״̬�Ĵ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  gt_clk_ddrphy_rs0 : 1;  /* bit[0]   : ����ʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
        unsigned int  gt_clk_ddrphy_rs1 : 1;  /* bit[1]   :  */
        unsigned int  gt_clk_ddrphy_rs2 : 1;  /* bit[2]   :  */
        unsigned int  gt_clk_ddrphy_rs3 : 1;  /* bit[3]   :  */
        unsigned int  gt_clk_ddrphy_gt  : 1;  /* bit[4]   : ddrphy rs/phy ���ʱ�����ſ� */
        unsigned int  reserved          : 27; /* bit[5-31]: ����ʱ������״̬��
                                                            0��IPʱ�ӽ�ֹ״̬��
                                                            1��IPʱ��ʹ��״̬�� */
    } reg;
} SOC_CRGPERIPH_PERSTAT7_UNION;
#endif
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs0_START  (0)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs0_END    (0)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs1_START  (1)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs1_END    (1)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs2_START  (2)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs2_END    (2)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs3_START  (3)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_rs3_END    (3)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_gt_START   (4)
#define SOC_CRGPERIPH_PERSTAT7_gt_clk_ddrphy_gt_END     (4)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_IVP_SEC_RSTEN_UNION
 �ṹ˵��  : IVP_SEC_RSTEN �Ĵ����ṹ���塣��ַƫ����:0xC00����ֵ:0x00000000�����:32
 �Ĵ���˵��: IVP��ȫ��λʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_ivp32dsp_subsys_crg : 1;  /* bit[0]   : IP��λʹ�ܣ�
                                                                     0��IP��λʹ��״̬���䣻
                                                                     1��IP��λʹ�ܡ� */
        unsigned int  ip_rst_ivp32dsp_subsys     : 1;  /* bit[1]   :  */
        unsigned int  reserved                   : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_CRGPERIPH_IVP_SEC_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_IVP_SEC_RSTEN_ip_rst_ivp32dsp_subsys_crg_START  (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTEN_ip_rst_ivp32dsp_subsys_crg_END    (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTEN_ip_rst_ivp32dsp_subsys_START      (1)
#define SOC_CRGPERIPH_IVP_SEC_RSTEN_ip_rst_ivp32dsp_subsys_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_IVP_SEC_RSTDIS_UNION
 �ṹ˵��  : IVP_SEC_RSTDIS �Ĵ����ṹ���塣��ַƫ����:0xC04����ֵ:0x00000000�����:32
 �Ĵ���˵��: IVP��ȫ��λ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_ivp32dsp_subsys_crg : 1;  /* bit[0]   : IP��λ���룺
                                                                     0��IP��λʹ��״̬���䣻
                                                                     1��IP��λ���롣 */
        unsigned int  ip_rst_ivp32dsp_subsys     : 1;  /* bit[1]   :  */
        unsigned int  reserved                   : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_CRGPERIPH_IVP_SEC_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_IVP_SEC_RSTDIS_ip_rst_ivp32dsp_subsys_crg_START  (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTDIS_ip_rst_ivp32dsp_subsys_crg_END    (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTDIS_ip_rst_ivp32dsp_subsys_START      (1)
#define SOC_CRGPERIPH_IVP_SEC_RSTDIS_ip_rst_ivp32dsp_subsys_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_IVP_SEC_RSTSTAT_UNION
 �ṹ˵��  : IVP_SEC_RSTSTAT �Ĵ����ṹ���塣��ַƫ����:0xC08����ֵ:0x00000003�����:32
 �Ĵ���˵��: IVP��ȫ��λʹ��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_ivp32dsp_subsys_crg : 1;  /* bit[0]   : IP��λʹ��״̬��
                                                                     0��IP���ڸ�λ����״̬��
                                                                     1��IP������λʹ��״̬�� */
        unsigned int  ip_rst_ivp32dsp_subsys     : 1;  /* bit[1]   :  */
        unsigned int  reserved                   : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_CRGPERIPH_IVP_SEC_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_IVP_SEC_RSTSTAT_ip_rst_ivp32dsp_subsys_crg_START  (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTSTAT_ip_rst_ivp32dsp_subsys_crg_END    (0)
#define SOC_CRGPERIPH_IVP_SEC_RSTSTAT_ip_rst_ivp32dsp_subsys_START      (1)
#define SOC_CRGPERIPH_IVP_SEC_RSTSTAT_ip_rst_ivp32dsp_subsys_END        (1)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_ISP_SEC_RSTEN_UNION
 �ṹ˵��  : ISP_SEC_RSTEN �Ĵ����ṹ���塣��ַƫ����:0xC80����ֵ:0x00000000�����:32
 �Ĵ���˵��: ISP��ȫ��λʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_isp      : 1;  /* bit[0]   : IP��λʹ�ܣ�
                                                          0��IP��λʹ��״̬���䣻
                                                          1��IP��λʹ�ܡ� */
        unsigned int  ip_arst_isp     : 1;  /* bit[1]   :  */
        unsigned int  ip_hrst_isp     : 1;  /* bit[2]   :  */
        unsigned int  ip_rst_ispa7cfg : 1;  /* bit[3]   :  */
        unsigned int  ip_rst_ispa7    : 1;  /* bit[4]   :  */
        unsigned int  reserved        : 27; /* bit[5-31]: ������ */
    } reg;
} SOC_CRGPERIPH_ISP_SEC_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_isp_START       (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_isp_END         (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_arst_isp_START      (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_arst_isp_END        (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_hrst_isp_START      (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_hrst_isp_END        (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_ispa7cfg_START  (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_ispa7cfg_END    (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_ispa7_START     (4)
#define SOC_CRGPERIPH_ISP_SEC_RSTEN_ip_rst_ispa7_END       (4)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_ISP_SEC_RSTDIS_UNION
 �ṹ˵��  : ISP_SEC_RSTDIS �Ĵ����ṹ���塣��ַƫ����:0xC84����ֵ:0x00000000�����:32
 �Ĵ���˵��: ISP��ȫ��λ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_isp      : 1;  /* bit[0]   : IP��λ���룺
                                                          0��IP��λʹ��״̬���䣻
                                                          1��IP��λ���롣 */
        unsigned int  ip_arst_isp     : 1;  /* bit[1]   :  */
        unsigned int  ip_hrst_isp     : 1;  /* bit[2]   :  */
        unsigned int  ip_rst_ispa7cfg : 1;  /* bit[3]   :  */
        unsigned int  ip_rst_ispa7    : 1;  /* bit[4]   :  */
        unsigned int  reserved        : 27; /* bit[5-31]: ������ */
    } reg;
} SOC_CRGPERIPH_ISP_SEC_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_isp_START       (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_isp_END         (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_arst_isp_START      (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_arst_isp_END        (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_hrst_isp_START      (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_hrst_isp_END        (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_ispa7cfg_START  (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_ispa7cfg_END    (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_ispa7_START     (4)
#define SOC_CRGPERIPH_ISP_SEC_RSTDIS_ip_rst_ispa7_END       (4)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_ISP_SEC_RSTSTAT_UNION
 �ṹ˵��  : ISP_SEC_RSTSTAT �Ĵ����ṹ���塣��ַƫ����:0xC88����ֵ:0x0000001F�����:32
 �Ĵ���˵��: ISP��ȫ��λ״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_isp      : 1;  /* bit[0]   : IP��λʹ��״̬��
                                                          0��IP���ڸ�λ����״̬��
                                                          1��IP������λʹ��״̬�� */
        unsigned int  ip_arst_isp     : 1;  /* bit[1]   :  */
        unsigned int  ip_hrst_isp     : 1;  /* bit[2]   :  */
        unsigned int  ip_rst_ispa7cfg : 1;  /* bit[3]   :  */
        unsigned int  ip_rst_ispa7    : 1;  /* bit[4]   :  */
        unsigned int  reserved        : 27; /* bit[5-31]: ������ */
    } reg;
} SOC_CRGPERIPH_ISP_SEC_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_isp_START       (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_isp_END         (0)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_arst_isp_START      (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_arst_isp_END        (1)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_hrst_isp_START      (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_hrst_isp_END        (2)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_ispa7cfg_START  (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_ispa7cfg_END    (3)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_ispa7_START     (4)
#define SOC_CRGPERIPH_ISP_SEC_RSTSTAT_ip_rst_ispa7_END       (4)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_ISPA7_CTRL0_UNION
 �ṹ˵��  : ISPA7_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0xC90����ֵ:0x00000284�����:32
 �Ĵ���˵��: ISPA7�������üĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ispa7_cfgend       : 1;  /* bit[0]    : A7��С������:
                                                              0:С��
                                                              1:��� */
        unsigned int  ispa7_vinithi      : 1;  /* bit[1]    : A7������ʽѡ��ÿbit��Ӧһ��core��
                                                              0���ӵ�λ��ַ��0x00000000������
                                                              1���Ӹ�λ��ַ��0xFFFF0000������ */
        unsigned int  ispa7_dbgpwrdup    : 1;  /* bit[2]    : CPU���Ƿ��ϵ�ļ���ź� */
        unsigned int  ispa7_l2rstdisable : 1;  /* bit[3]    : ��λ�׶ν�ֹL2 cache�Զ�invalidate�ź� */
        unsigned int  ispa7_l1rstdisable : 1;  /* bit[4]    : ��λ�׶ν�ֹL1 cache�Զ�invalidate�ź� */
        unsigned int  reserved_0         : 2;  /* bit[5-6]  : ������ */
        unsigned int  ispa7_tsel_a7      : 4;  /* bit[7-10] : A7 cpu�ڲ�memory�ٶȵ����ź� */
        unsigned int  ispa7_remap_enable : 1;  /* bit[11]   : A7 AXI master�ӿڵ�ַ��ӳ��ʹ���ź� */
        unsigned int  ispa7_remap_offset : 18; /* bit[12-29]: A7 AXI master�ӿڵ�ַ��ӳ��offset���� */
        unsigned int  reserved_1         : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_CRGPERIPH_ISPA7_CTRL0_UNION;
#endif
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_cfgend_START        (0)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_cfgend_END          (0)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_vinithi_START       (1)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_vinithi_END         (1)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_dbgpwrdup_START     (2)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_dbgpwrdup_END       (2)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_l2rstdisable_START  (3)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_l2rstdisable_END    (3)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_l1rstdisable_START  (4)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_l1rstdisable_END    (4)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_tsel_a7_START       (7)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_tsel_a7_END         (10)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_remap_enable_START  (11)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_remap_enable_END    (11)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_remap_offset_START  (12)
#define SOC_CRGPERIPH_ISPA7_CTRL0_ispa7_remap_offset_END    (29)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MDM_SEC_RSTEN_UNION
 �ṹ˵��  : MDM_SEC_RSTEN �Ĵ����ṹ���塣��ַƫ����:0xD00����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEM��ȫ��λʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_modem : 1;  /* bit[0]   : IP��λʹ�ܣ�
                                                       0��IP��λʹ��״̬���䣻
                                                       1��IP��λʹ�ܡ� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MDM_SEC_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_MDM_SEC_RSTEN_ip_rst_modem_START  (0)
#define SOC_CRGPERIPH_MDM_SEC_RSTEN_ip_rst_modem_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MDM_SEC_RSTDIS_UNION
 �ṹ˵��  : MDM_SEC_RSTDIS �Ĵ����ṹ���塣��ַƫ����:0xD04����ֵ:0x00000000�����:32
 �Ĵ���˵��: MODEM��ȫ��λ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_modem : 1;  /* bit[0]   : IP��λ���룺
                                                       0��IP��λʹ��״̬���䣻
                                                       1��IP��λ���롣 */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MDM_SEC_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_MDM_SEC_RSTDIS_ip_rst_modem_START  (0)
#define SOC_CRGPERIPH_MDM_SEC_RSTDIS_ip_rst_modem_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MDM_SEC_RSTSTAT_UNION
 �ṹ˵��  : MDM_SEC_RSTSTAT �Ĵ����ṹ���塣��ַƫ����:0xD08����ֵ:0x00000001�����:32
 �Ĵ���˵��: MODEM��ȫ��λʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_modem : 1;  /* bit[0]   : IP��λʹ��״̬��
                                                       0��IP���ڸ�λ����״̬��
                                                       1��IP������λʹ��״̬�� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_CRGPERIPH_MDM_SEC_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_MDM_SEC_RSTSTAT_ip_rst_modem_START  (0)
#define SOC_CRGPERIPH_MDM_SEC_RSTSTAT_ip_rst_modem_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_CTRL3_UNION
 �ṹ˵��  : A53_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0xE00����ֵ:0x00000000�����:32
 �Ĵ���˵��: A53 CLUSTER�������üĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_rvbaraddr0 : 32; /* bit[0-31]: AArch64ģʽ�º�0�����������ַ�� */
    } reg;
} SOC_CRGPERIPH_A53_CTRL3_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL3_a53_rvbaraddr0_START  (0)
#define SOC_CRGPERIPH_A53_CTRL3_a53_rvbaraddr0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_CTRL4_UNION
 �ṹ˵��  : A53_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0xE04����ֵ:0x00000000�����:32
 �Ĵ���˵��: A53 CLUSTER�������üĴ���4����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_rvbaraddr1 : 32; /* bit[0-31]: AArch64ģʽ�º�1�����������ַ�� */
    } reg;
} SOC_CRGPERIPH_A53_CTRL4_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL4_a53_rvbaraddr1_START  (0)
#define SOC_CRGPERIPH_A53_CTRL4_a53_rvbaraddr1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_CTRL5_UNION
 �ṹ˵��  : A53_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0xE08����ֵ:0x00000000�����:32
 �Ĵ���˵��: A53 CLUSTER�������üĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_rvbaraddr2 : 32; /* bit[0-31]: AArch64ģʽ�º�2�����������ַ�� */
    } reg;
} SOC_CRGPERIPH_A53_CTRL5_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL5_a53_rvbaraddr2_START  (0)
#define SOC_CRGPERIPH_A53_CTRL5_a53_rvbaraddr2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_A53_CTRL6_UNION
 �ṹ˵��  : A53_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0xE0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: A53 CLUSTER�������üĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a53_rvbaraddr3 : 32; /* bit[0-31]: AArch64ģʽ�º�3�����������ַ�� */
    } reg;
} SOC_CRGPERIPH_A53_CTRL6_UNION;
#endif
#define SOC_CRGPERIPH_A53_CTRL6_a53_rvbaraddr3_START  (0)
#define SOC_CRGPERIPH_A53_CTRL6_a53_rvbaraddr3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_CTRL3_UNION
 �ṹ˵��  : MAIA_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0xE10����ֵ:0x00000000�����:32
 �Ĵ���˵��: A57 CLUSTER�������üĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_rvbaraddr0 : 32; /* bit[0-31]: AArch64ģʽ�º�0�����������ַ�� */
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL3_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL3_a57_rvbaraddr0_START  (0)
#define SOC_CRGPERIPH_MAIA_CTRL3_a57_rvbaraddr0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_CTRL4_UNION
 �ṹ˵��  : MAIA_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0xE14����ֵ:0x00000000�����:32
 �Ĵ���˵��: A57 CLUSTER�������üĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_rvbaraddr1 : 32; /* bit[0-31]: AArch64ģʽ�º�1�����������ַ�� */
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL4_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL4_a57_rvbaraddr1_START  (0)
#define SOC_CRGPERIPH_MAIA_CTRL4_a57_rvbaraddr1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_CTRL5_UNION
 �ṹ˵��  : MAIA_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0xE1C����ֵ:0x00000000�����:32
 �Ĵ���˵��: A57 CLUSTER�������üĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_rvbaraddr2 : 32; /* bit[0-31]: AArch64ģʽ�º�2�����������ַ�� */
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL5_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL5_a57_rvbaraddr2_START  (0)
#define SOC_CRGPERIPH_MAIA_CTRL5_a57_rvbaraddr2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_MAIA_CTRL6_UNION
 �ṹ˵��  : MAIA_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0xE18����ֵ:0x00000000�����:32
 �Ĵ���˵��: A57 CLUSTER�������üĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  a57_rvbaraddr3 : 32; /* bit[0-31]: AArch64ģʽ�º�3�����������ַ�� */
    } reg;
} SOC_CRGPERIPH_MAIA_CTRL6_UNION;
#endif
#define SOC_CRGPERIPH_MAIA_CTRL6_a57_rvbaraddr3_START  (0)
#define SOC_CRGPERIPH_MAIA_CTRL6_a57_rvbaraddr3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_GENERAL_SEC_RSTEN_UNION
 �ṹ˵��  : GENERAL_SEC_RSTEN �Ĵ����ṹ���塣��ַƫ����:0xE20����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ�ð�ȫ��λʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_secs : 1;  /* bit[0]   : IP��λʹ�ܣ�
                                                      0��IP��λʹ��״̬���䣻
                                                      1��IP��λʹ�ܡ� */
        unsigned int  reserved    : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_CRGPERIPH_GENERAL_SEC_RSTEN_UNION;
#endif
#define SOC_CRGPERIPH_GENERAL_SEC_RSTEN_ip_rst_secs_START  (0)
#define SOC_CRGPERIPH_GENERAL_SEC_RSTEN_ip_rst_secs_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_UNION
 �ṹ˵��  : GENERAL_SEC_RSTDIS �Ĵ����ṹ���塣��ַƫ����:0xE24����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ�ð�ȫ��λ����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_secs : 1;  /* bit[0]   : IP��λ���룺
                                                      0��IP��λʹ��״̬���䣻
                                                      1��IP��λ���롣 */
        unsigned int  reserved    : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_UNION;
#endif
#define SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_ip_rst_secs_START  (0)
#define SOC_CRGPERIPH_GENERAL_SEC_RSTDIS_ip_rst_secs_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_UNION
 �ṹ˵��  : GENERAL_SEC_RSTSTAT �Ĵ����ṹ���塣��ַƫ����:0xE28����ֵ:0x00000001�����:32
 �Ĵ���˵��: ͨ�ð�ȫ��λʹ��״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ip_rst_secs : 1;  /* bit[0]   : IP��λʹ��״̬��
                                                      0��IP���ڸ�λ����״̬��
                                                      1��IP������λʹ��״̬�� */
        unsigned int  reserved    : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_UNION;
#endif
#define SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_ip_rst_secs_START  (0)
#define SOC_CRGPERIPH_GENERAL_SEC_RSTSTAT_ip_rst_secs_END    (0)






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

#endif /* end of soc_crgperiph_interface.h */
