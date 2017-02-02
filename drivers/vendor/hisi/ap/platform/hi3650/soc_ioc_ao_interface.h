/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_ioc_ao_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-03-10 11:21:17
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��10��
    ��    ��   : fWX220878
    �޸�����   : �ӡ�Hi3650V100 SOC�Ĵ����ֲ�_IOC_AO.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_IOC_AO_INTERFACE_H__
#define __SOC_IOC_AO_INTERFACE_H__

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
/* �Ĵ���˵����SYSCLK_EN�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_000_UNION */
#define SOC_IOC_AO_IOMG_000_ADDR(base)                ((base) + (0x000))

/* �Ĵ���˵����CLK_OUT0�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_001_UNION */
#define SOC_IOC_AO_IOMG_001_ADDR(base)                ((base) + (0x004))

/* �Ĵ���˵����CLK_OUT1�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_002_UNION */
#define SOC_IOC_AO_IOMG_002_ADDR(base)                ((base) + (0x008))

/* �Ĵ���˵����BLPWM_CABC�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_003_UNION */
#define SOC_IOC_AO_IOMG_003_ADDR(base)                ((base) + (0x00C))

/* �Ĵ���˵����BLPWM_BL�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_004_UNION */
#define SOC_IOC_AO_IOMG_004_ADDR(base)                ((base) + (0x010))

/* �Ĵ���˵����I2C0_SCL�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_005_UNION */
#define SOC_IOC_AO_IOMG_005_ADDR(base)                ((base) + (0x014))

/* �Ĵ���˵����I2C0_SDA�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_006_UNION */
#define SOC_IOC_AO_IOMG_006_ADDR(base)                ((base) + (0x018))

/* �Ĵ���˵����I2C1_SCL�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_007_UNION */
#define SOC_IOC_AO_IOMG_007_ADDR(base)                ((base) + (0x01C))

/* �Ĵ���˵����I2C1_SDA�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_008_UNION */
#define SOC_IOC_AO_IOMG_008_ADDR(base)                ((base) + (0x020))

/* �Ĵ���˵����I2C2_SCL�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_009_UNION */
#define SOC_IOC_AO_IOMG_009_ADDR(base)                ((base) + (0x024))

/* �Ĵ���˵����I2C2_SDA�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_010_UNION */
#define SOC_IOC_AO_IOMG_010_ADDR(base)                ((base) + (0x028))

/* �Ĵ���˵����SLIMBUS_CLK�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_011_UNION */
#define SOC_IOC_AO_IOMG_011_ADDR(base)                ((base) + (0x02C))

/* �Ĵ���˵����SLIMBUS_DATA�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_012_UNION */
#define SOC_IOC_AO_IOMG_012_ADDR(base)                ((base) + (0x030))

/* �Ĵ���˵����GPIO_192�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_013_UNION */
#define SOC_IOC_AO_IOMG_013_ADDR(base)                ((base) + (0x034))

/* �Ĵ���˵����GPIO_193�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_014_UNION */
#define SOC_IOC_AO_IOMG_014_ADDR(base)                ((base) + (0x038))

/* �Ĵ���˵����GPIO_194�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_015_UNION */
#define SOC_IOC_AO_IOMG_015_ADDR(base)                ((base) + (0x03C))

/* �Ĵ���˵����GPIO_195�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_016_UNION */
#define SOC_IOC_AO_IOMG_016_ADDR(base)                ((base) + (0x040))

/* �Ĵ���˵����GPIO_196�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_017_UNION */
#define SOC_IOC_AO_IOMG_017_ADDR(base)                ((base) + (0x044))

/* �Ĵ���˵����GPIO_197�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_018_UNION */
#define SOC_IOC_AO_IOMG_018_ADDR(base)                ((base) + (0x048))

/* �Ĵ���˵����GPIO_198�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_019_UNION */
#define SOC_IOC_AO_IOMG_019_ADDR(base)                ((base) + (0x04C))

/* �Ĵ���˵����GPIO_199�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_020_UNION */
#define SOC_IOC_AO_IOMG_020_ADDR(base)                ((base) + (0x050))

/* �Ĵ���˵����GPIO_200�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_021_UNION */
#define SOC_IOC_AO_IOMG_021_ADDR(base)                ((base) + (0x054))

/* �Ĵ���˵����GPIO_201�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_022_UNION */
#define SOC_IOC_AO_IOMG_022_ADDR(base)                ((base) + (0x058))

/* �Ĵ���˵����GPIO_202�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_023_UNION */
#define SOC_IOC_AO_IOMG_023_ADDR(base)                ((base) + (0x05C))

/* �Ĵ���˵����GPIO_203�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_024_UNION */
#define SOC_IOC_AO_IOMG_024_ADDR(base)                ((base) + (0x060))

/* �Ĵ���˵����GPIO_205�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_025_UNION */
#define SOC_IOC_AO_IOMG_025_ADDR(base)                ((base) + (0x064))

/* �Ĵ���˵����GPIO_206�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_026_UNION */
#define SOC_IOC_AO_IOMG_026_ADDR(base)                ((base) + (0x068))

/* �Ĵ���˵����GPIO_207�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_027_UNION */
#define SOC_IOC_AO_IOMG_027_ADDR(base)                ((base) + (0x06C))

/* �Ĵ���˵����GPIO_208�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_028_UNION */
#define SOC_IOC_AO_IOMG_028_ADDR(base)                ((base) + (0x070))

/* �Ĵ���˵����GPIO_209�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_029_UNION */
#define SOC_IOC_AO_IOMG_029_ADDR(base)                ((base) + (0x074))

/* �Ĵ���˵����GPIO_210�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_030_UNION */
#define SOC_IOC_AO_IOMG_030_ADDR(base)                ((base) + (0x078))

/* �Ĵ���˵����GPIO_211�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_031_UNION */
#define SOC_IOC_AO_IOMG_031_ADDR(base)                ((base) + (0x07C))

/* �Ĵ���˵����GPIO_212�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_032_UNION */
#define SOC_IOC_AO_IOMG_032_ADDR(base)                ((base) + (0x080))

/* �Ĵ���˵����GPIO_213�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_033_UNION */
#define SOC_IOC_AO_IOMG_033_ADDR(base)                ((base) + (0x084))

/* �Ĵ���˵����GPIO_214�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_034_UNION */
#define SOC_IOC_AO_IOMG_034_ADDR(base)                ((base) + (0x088))

/* �Ĵ���˵����ISP_GPIO03_PRTRB�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_035_UNION */
#define SOC_IOC_AO_IOMG_035_ADDR(base)                ((base) + (0x08C))

/* �Ĵ���˵����ISP_GPIO04_FTPWM�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_036_UNION */
#define SOC_IOC_AO_IOMG_036_ADDR(base)                ((base) + (0x090))

/* �Ĵ���˵����ISP_GPIO05_BKPWM�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_037_UNION */
#define SOC_IOC_AO_IOMG_037_ADDR(base)                ((base) + (0x094))

/* �Ĵ���˵����ISP_GPIO09_ENC�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_038_UNION */
#define SOC_IOC_AO_IOMG_038_ADDR(base)                ((base) + (0x098))

/* �Ĵ���˵����ISP_GPIO07_ENA�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_039_UNION */
#define SOC_IOC_AO_IOMG_039_ADDR(base)                ((base) + (0x09C))

/* �Ĵ���˵����ISP_GPIO08_ENB�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_040_UNION */
#define SOC_IOC_AO_IOMG_040_ADDR(base)                ((base) + (0x0A0))

/* �Ĵ���˵����ISP_GPIO11�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_041_UNION */
#define SOC_IOC_AO_IOMG_041_ADDR(base)                ((base) + (0x0A4))

/* �Ĵ���˵����ISP_GPIO12�ܽŸ��ÿ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOMG_042_UNION */
#define SOC_IOC_AO_IOMG_042_ADDR(base)                ((base) + (0x0A8))

/* �Ĵ���˵����GPIO_176���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_000_UNION */
#define SOC_IOC_AO_IOCG_000_ADDR(base)                ((base) + (0x800))

/* �Ĵ���˵����GPIO_177���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_001_UNION */
#define SOC_IOC_AO_IOCG_001_ADDR(base)                ((base) + (0x804))

/* �Ĵ���˵����SYSCLK_EN���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_002_UNION */
#define SOC_IOC_AO_IOCG_002_ADDR(base)                ((base) + (0x808))

/* �Ĵ���˵����CLK_OUT0���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_003_UNION */
#define SOC_IOC_AO_IOCG_003_ADDR(base)                ((base) + (0x80C))

/* �Ĵ���˵����CLK_OUT1���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_004_UNION */
#define SOC_IOC_AO_IOCG_004_ADDR(base)                ((base) + (0x810))

/* �Ĵ���˵����BLPWM_CABC���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_005_UNION */
#define SOC_IOC_AO_IOCG_005_ADDR(base)                ((base) + (0x814))

/* �Ĵ���˵����BLPWM_BL���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_006_UNION */
#define SOC_IOC_AO_IOCG_006_ADDR(base)                ((base) + (0x818))

/* �Ĵ���˵����I2C0_SCL���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_007_UNION */
#define SOC_IOC_AO_IOCG_007_ADDR(base)                ((base) + (0x81C))

/* �Ĵ���˵����I2C0_SDA���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_008_UNION */
#define SOC_IOC_AO_IOCG_008_ADDR(base)                ((base) + (0x820))

/* �Ĵ���˵����I2C1_SCL���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_009_UNION */
#define SOC_IOC_AO_IOCG_009_ADDR(base)                ((base) + (0x824))

/* �Ĵ���˵����I2C1_SDA���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_010_UNION */
#define SOC_IOC_AO_IOCG_010_ADDR(base)                ((base) + (0x828))

/* �Ĵ���˵����I2C2_SCL���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_011_UNION */
#define SOC_IOC_AO_IOCG_011_ADDR(base)                ((base) + (0x82C))

/* �Ĵ���˵����I2C2_SDA���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_012_UNION */
#define SOC_IOC_AO_IOCG_012_ADDR(base)                ((base) + (0x830))

/* �Ĵ���˵����SLIMBUS_CLK���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_013_UNION */
#define SOC_IOC_AO_IOCG_013_ADDR(base)                ((base) + (0x834))

/* �Ĵ���˵����SLIMBUS_DATA���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_014_UNION */
#define SOC_IOC_AO_IOCG_014_ADDR(base)                ((base) + (0x838))

/* �Ĵ���˵����GPIO_191���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_015_UNION */
#define SOC_IOC_AO_IOCG_015_ADDR(base)                ((base) + (0x83C))

/* �Ĵ���˵����GPIO_192���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_016_UNION */
#define SOC_IOC_AO_IOCG_016_ADDR(base)                ((base) + (0x840))

/* �Ĵ���˵����GPIO_193���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_017_UNION */
#define SOC_IOC_AO_IOCG_017_ADDR(base)                ((base) + (0x844))

/* �Ĵ���˵����GPIO_194���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_018_UNION */
#define SOC_IOC_AO_IOCG_018_ADDR(base)                ((base) + (0x848))

/* �Ĵ���˵����GPIO_195���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_019_UNION */
#define SOC_IOC_AO_IOCG_019_ADDR(base)                ((base) + (0x84C))

/* �Ĵ���˵����GPIO_196���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_020_UNION */
#define SOC_IOC_AO_IOCG_020_ADDR(base)                ((base) + (0x850))

/* �Ĵ���˵����GPIO_197���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_021_UNION */
#define SOC_IOC_AO_IOCG_021_ADDR(base)                ((base) + (0x854))

/* �Ĵ���˵����GPIO_198���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_022_UNION */
#define SOC_IOC_AO_IOCG_022_ADDR(base)                ((base) + (0x858))

/* �Ĵ���˵����GPIO_199���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_023_UNION */
#define SOC_IOC_AO_IOCG_023_ADDR(base)                ((base) + (0x85C))

/* �Ĵ���˵����GPIO_200���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_024_UNION */
#define SOC_IOC_AO_IOCG_024_ADDR(base)                ((base) + (0x860))

/* �Ĵ���˵����GPIO_201���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_025_UNION */
#define SOC_IOC_AO_IOCG_025_ADDR(base)                ((base) + (0x864))

/* �Ĵ���˵����GPIO_202���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_026_UNION */
#define SOC_IOC_AO_IOCG_026_ADDR(base)                ((base) + (0x868))

/* �Ĵ���˵����GPIO_203���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_027_UNION */
#define SOC_IOC_AO_IOCG_027_ADDR(base)                ((base) + (0x86C))

/* �Ĵ���˵����GPIO_204���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_028_UNION */
#define SOC_IOC_AO_IOCG_028_ADDR(base)                ((base) + (0x870))

/* �Ĵ���˵����GPIO_205���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_029_UNION */
#define SOC_IOC_AO_IOCG_029_ADDR(base)                ((base) + (0x874))

/* �Ĵ���˵����GPIO_206���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_030_UNION */
#define SOC_IOC_AO_IOCG_030_ADDR(base)                ((base) + (0x878))

/* �Ĵ���˵����GPIO_207���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_031_UNION */
#define SOC_IOC_AO_IOCG_031_ADDR(base)                ((base) + (0x87C))

/* �Ĵ���˵����GPIO_208���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_032_UNION */
#define SOC_IOC_AO_IOCG_032_ADDR(base)                ((base) + (0x880))

/* �Ĵ���˵����GPIO_209���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_033_UNION */
#define SOC_IOC_AO_IOCG_033_ADDR(base)                ((base) + (0x884))

/* �Ĵ���˵����GPIO_210���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_034_UNION */
#define SOC_IOC_AO_IOCG_034_ADDR(base)                ((base) + (0x888))

/* �Ĵ���˵����GPIO_211���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_035_UNION */
#define SOC_IOC_AO_IOCG_035_ADDR(base)                ((base) + (0x88C))

/* �Ĵ���˵����GPIO_212���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_036_UNION */
#define SOC_IOC_AO_IOCG_036_ADDR(base)                ((base) + (0x890))

/* �Ĵ���˵����GPIO_213���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_037_UNION */
#define SOC_IOC_AO_IOCG_037_ADDR(base)                ((base) + (0x894))

/* �Ĵ���˵����GPIO_214���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_038_UNION */
#define SOC_IOC_AO_IOCG_038_ADDR(base)                ((base) + (0x898))

/* �Ĵ���˵����ISP_GPIO03_PRTRB���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_039_UNION */
#define SOC_IOC_AO_IOCG_039_ADDR(base)                ((base) + (0x89C))

/* �Ĵ���˵����ISP_GPIO04_FTPWM���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_040_UNION */
#define SOC_IOC_AO_IOCG_040_ADDR(base)                ((base) + (0x8A0))

/* �Ĵ���˵����ISP_GPIO05_BKPWM���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_041_UNION */
#define SOC_IOC_AO_IOCG_041_ADDR(base)                ((base) + (0x8A4))

/* �Ĵ���˵����ISP_GPIO09_ENC���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_042_UNION */
#define SOC_IOC_AO_IOCG_042_ADDR(base)                ((base) + (0x8A8))

/* �Ĵ���˵����ISP_GPIO07_ENA���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_043_UNION */
#define SOC_IOC_AO_IOCG_043_ADDR(base)                ((base) + (0x8AC))

/* �Ĵ���˵����ISP_GPIO08_ENB���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_044_UNION */
#define SOC_IOC_AO_IOCG_044_ADDR(base)                ((base) + (0x8B0))

/* �Ĵ���˵����ISP_GPIO11���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_045_UNION */
#define SOC_IOC_AO_IOCG_045_ADDR(base)                ((base) + (0x8B4))

/* �Ĵ���˵����ISP_GPIO12���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_046_UNION */
#define SOC_IOC_AO_IOCG_046_ADDR(base)                ((base) + (0x8B8))

/* �Ĵ���˵����GPIO_223���ܹܽſ��ƼĴ�����&#13;
   λ����UNION�ṹ:  SOC_IOC_AO_IOCG_047_UNION */
#define SOC_IOC_AO_IOCG_047_ADDR(base)                ((base) + (0x8BC))





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
 �ṹ��    : SOC_IOC_AO_IOMG_000_UNION
 �ṹ˵��  : IOMG_000 �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000001�����:32
 �Ĵ���˵��: SYSCLK_EN�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_000 : 1;  /* bit[0]   : SYSCLK_EN�ܽŵľ��帴�������
                                                   0��GPIO_178��
                                                   1��SYSCLK_EN�� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_000_UNION;
#endif
#define SOC_IOC_AO_IOMG_000_iomg_000_START  (0)
#define SOC_IOC_AO_IOMG_000_iomg_000_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_001_UNION
 �ṹ˵��  : IOMG_001 �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLK_OUT0�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_001 : 1;  /* bit[0]   : CLK_OUT0�ܽŵľ��帴�������
                                                   0��GPIO_179��
                                                   1��CLK_OUT0�� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_001_UNION;
#endif
#define SOC_IOC_AO_IOMG_001_iomg_001_START  (0)
#define SOC_IOC_AO_IOMG_001_iomg_001_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_002_UNION
 �ṹ˵��  : IOMG_002 �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLK_OUT1�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_002 : 2;  /* bit[0-1] : CLK_OUT1�ܽŵľ��帴�������
                                                   00��GPIO_180��
                                                   01��CLK_OUT1��
                                                   10��GPIO_000_SH��
                                                   ������������ */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_002_UNION;
#endif
#define SOC_IOC_AO_IOMG_002_iomg_002_START  (0)
#define SOC_IOC_AO_IOMG_002_iomg_002_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_003_UNION
 �ṹ˵��  : IOMG_003 �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: BLPWM_CABC�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_003 : 2;  /* bit[0-1] : BLPWM_CABC�ܽŵľ��帴�������
                                                   00��GPIO_181��
                                                   01��BLPWM_CABC��
                                                   10��GPIO_000_SH��
                                                   ������������ */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_003_UNION;
#endif
#define SOC_IOC_AO_IOMG_003_iomg_003_START  (0)
#define SOC_IOC_AO_IOMG_003_iomg_003_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_004_UNION
 �ṹ˵��  : IOMG_004 �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: BLPWM_BL�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_004 : 2;  /* bit[0-1] : BLPWM_BL�ܽŵľ��帴�������
                                                   00��GPIO_182��
                                                   01��BLPWM_BL��
                                                   10��GPIO_001_SH��
                                                   11��PWM_OUT0�� */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_004_UNION;
#endif
#define SOC_IOC_AO_IOMG_004_iomg_004_START  (0)
#define SOC_IOC_AO_IOMG_004_iomg_004_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_005_UNION
 �ṹ˵��  : IOMG_005 �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2C0_SCL�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_005 : 1;  /* bit[0]   : I2C0_SCL�ܽŵľ��帴�������
                                                   0��GPIO_183��
                                                   1��I2C0_SCL�� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_005_UNION;
#endif
#define SOC_IOC_AO_IOMG_005_iomg_005_START  (0)
#define SOC_IOC_AO_IOMG_005_iomg_005_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_006_UNION
 �ṹ˵��  : IOMG_006 �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2C0_SDA�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_006 : 1;  /* bit[0]   : I2C0_SDA�ܽŵľ��帴�������
                                                   0��GPIO_184��
                                                   1��I2C0_SDA�� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_006_UNION;
#endif
#define SOC_IOC_AO_IOMG_006_iomg_006_START  (0)
#define SOC_IOC_AO_IOMG_006_iomg_006_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_007_UNION
 �ṹ˵��  : IOMG_007 �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2C1_SCL�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_007 : 2;  /* bit[0-1] : I2C1_SCL�ܽŵľ��帴�������
                                                   00��GPIO_185��
                                                   01��I2C1_SCL��
                                                   10��GPIO_001_SH��
                                                   ������������ */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_007_UNION;
#endif
#define SOC_IOC_AO_IOMG_007_iomg_007_START  (0)
#define SOC_IOC_AO_IOMG_007_iomg_007_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_008_UNION
 �ṹ˵��  : IOMG_008 �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2C1_SDA�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_008 : 2;  /* bit[0-1] : I2C1_SDA�ܽŵľ��帴�������
                                                   00��GPIO_186��
                                                   01��I2C1_SDA��
                                                   11��CODEC_SSI��
                                                   ������������ */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_008_UNION;
#endif
#define SOC_IOC_AO_IOMG_008_iomg_008_START  (0)
#define SOC_IOC_AO_IOMG_008_iomg_008_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_009_UNION
 �ṹ˵��  : IOMG_009 �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2C2_SCL�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_009 : 1;  /* bit[0]   : I2C2_SCL�ܽŵľ��帴�������
                                                   0��GPIO_187��
                                                   1��I2C2_SCL�� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_009_UNION;
#endif
#define SOC_IOC_AO_IOMG_009_iomg_009_START  (0)
#define SOC_IOC_AO_IOMG_009_iomg_009_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_010_UNION
 �ṹ˵��  : IOMG_010 �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2C2_SDA�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_010 : 1;  /* bit[0]   : I2C2_SDA�ܽŵľ��帴�������
                                                   0��GPIO_188��
                                                   1��I2C2_SDA�� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_010_UNION;
#endif
#define SOC_IOC_AO_IOMG_010_iomg_010_START  (0)
#define SOC_IOC_AO_IOMG_010_iomg_010_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_011_UNION
 �ṹ˵��  : IOMG_011 �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SLIMBUS_CLK�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_011 : 3;  /* bit[0-2] : SLIMBUS_CLK�ܽŵľ��帴�������
                                                   000��GPIO_189��
                                                   001��SLIMBUS_CLK��
                                                   011��I2S0_DI��
                                                   100��UART7_RXD��
                                                   ������������ */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_011_UNION;
#endif
#define SOC_IOC_AO_IOMG_011_iomg_011_START  (0)
#define SOC_IOC_AO_IOMG_011_iomg_011_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_012_UNION
 �ṹ˵��  : IOMG_012 �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: SLIMBUS_DATA�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_012 : 3;  /* bit[0-2] : SLIMBUS_DATA�ܽŵľ��帴�������
                                                   000��GPIO_190��
                                                   001��SLIMBUS_DATA��
                                                   011��I2S0_DO��
                                                   100��UART7_TXD��
                                                   ������������ */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_012_UNION;
#endif
#define SOC_IOC_AO_IOMG_012_iomg_012_START  (0)
#define SOC_IOC_AO_IOMG_012_iomg_012_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_013_UNION
 �ṹ˵��  : IOMG_013 �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_192�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_013 : 2;  /* bit[0-1] : GPIO_192�ܽŵľ��帴�������
                                                   00��GPIO_192��
                                                   01��I2S0_XCLK��
                                                   10��GPIO_002_SH��
                                                   ������������ */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_013_UNION;
#endif
#define SOC_IOC_AO_IOMG_013_iomg_013_START  (0)
#define SOC_IOC_AO_IOMG_013_iomg_013_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_014_UNION
 �ṹ˵��  : IOMG_014 �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_193�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_014 : 2;  /* bit[0-1] : GPIO_193�ܽŵľ��帴�������
                                                   00��GPIO_193��
                                                   01��I2S0_XFS��
                                                   10��GPIO_003_SH��
                                                   ������������ */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_014_UNION;
#endif
#define SOC_IOC_AO_IOMG_014_iomg_014_START  (0)
#define SOC_IOC_AO_IOMG_014_iomg_014_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_015_UNION
 �ṹ˵��  : IOMG_015 �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_194�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_015 : 1;  /* bit[0]   : GPIO_194�ܽŵľ��帴�������
                                                   0��GPIO_194��
                                                   1��I2S2_DI�� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_015_UNION;
#endif
#define SOC_IOC_AO_IOMG_015_iomg_015_START  (0)
#define SOC_IOC_AO_IOMG_015_iomg_015_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_016_UNION
 �ṹ˵��  : IOMG_016 �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_195�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_016 : 1;  /* bit[0]   : GPIO_195�ܽŵľ��帴�������
                                                   0��GPIO_195��
                                                   1��I2S2_DO�� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_016_UNION;
#endif
#define SOC_IOC_AO_IOMG_016_iomg_016_START  (0)
#define SOC_IOC_AO_IOMG_016_iomg_016_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_017_UNION
 �ṹ˵��  : IOMG_017 �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_196�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_017 : 1;  /* bit[0]   : GPIO_196�ܽŵľ��帴�������
                                                   0��GPIO_196��
                                                   1��I2S2_XCLK�� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_017_UNION;
#endif
#define SOC_IOC_AO_IOMG_017_iomg_017_START  (0)
#define SOC_IOC_AO_IOMG_017_iomg_017_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_018_UNION
 �ṹ˵��  : IOMG_018 �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_197�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_018 : 1;  /* bit[0]   : GPIO_197�ܽŵľ��帴�������
                                                   0��GPIO_197��
                                                   1��I2S2_XFS�� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_018_UNION;
#endif
#define SOC_IOC_AO_IOMG_018_iomg_018_START  (0)
#define SOC_IOC_AO_IOMG_018_iomg_018_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_019_UNION
 �ṹ˵��  : IOMG_019 �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_198�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_019 : 2;  /* bit[0-1] : GPIO_198�ܽŵľ��帴�������
                                                   00��GPIO_198��
                                                   10��GPIO_004_SH��
                                                   ������������ */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_019_UNION;
#endif
#define SOC_IOC_AO_IOMG_019_iomg_019_START  (0)
#define SOC_IOC_AO_IOMG_019_iomg_019_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_020_UNION
 �ṹ˵��  : IOMG_020 �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_199�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_020 : 2;  /* bit[0-1] : GPIO_199�ܽŵľ��帴�������
                                                   00��GPIO_199��
                                                   10��GPIO_005_SH��
                                                   ������������ */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_020_UNION;
#endif
#define SOC_IOC_AO_IOMG_020_iomg_020_START  (0)
#define SOC_IOC_AO_IOMG_020_iomg_020_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_021_UNION
 �ṹ˵��  : IOMG_021 �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_200�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_021 : 2;  /* bit[0-1] : GPIO_200�ܽŵľ��帴�������
                                                   00��GPIO_200��
                                                   10��GPIO_006_SH��
                                                   ������������ */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_021_UNION;
#endif
#define SOC_IOC_AO_IOMG_021_iomg_021_START  (0)
#define SOC_IOC_AO_IOMG_021_iomg_021_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_022_UNION
 �ṹ˵��  : IOMG_022 �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_201�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_022 : 2;  /* bit[0-1] : GPIO_201�ܽŵľ��帴�������
                                                   00��GPIO_201��
                                                   10��GPIO_007_SH��
                                                   ������������ */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_022_UNION;
#endif
#define SOC_IOC_AO_IOMG_022_iomg_022_START  (0)
#define SOC_IOC_AO_IOMG_022_iomg_022_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_023_UNION
 �ṹ˵��  : IOMG_023 �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_202�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_023 : 2;  /* bit[0-1] : GPIO_202�ܽŵľ��帴�������
                                                   00��GPIO_202��
                                                   10��GPIO_008_SH��
                                                   ������������ */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_023_UNION;
#endif
#define SOC_IOC_AO_IOMG_023_iomg_023_START  (0)
#define SOC_IOC_AO_IOMG_023_iomg_023_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_024_UNION
 �ṹ˵��  : IOMG_024 �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x00000001�����:32
 �Ĵ���˵��: GPIO_203�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_024 : 2;  /* bit[0-1] : GPIO_203�ܽŵľ��帴�������
                                                   00��GPIO_203��
                                                   01��CLKIN_AUX��
                                                   10��GPIO_009_SH��
                                                   ������������ */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_024_UNION;
#endif
#define SOC_IOC_AO_IOMG_024_iomg_024_START  (0)
#define SOC_IOC_AO_IOMG_024_iomg_024_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_025_UNION
 �ṹ˵��  : IOMG_025 �Ĵ����ṹ���塣��ַƫ����:0x064����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_205�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_025 : 3;  /* bit[0-2] : GPIO_205�ܽŵľ��帴�������
                                                   000��GPIO_205��
                                                   001��I2S3_DI��
                                                   010��GPIO_010_SH��
                                                   110��FAC_TEST16��
                                                   111��FAC_TEST16��
                                                   ������������ */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_025_UNION;
#endif
#define SOC_IOC_AO_IOMG_025_iomg_025_START  (0)
#define SOC_IOC_AO_IOMG_025_iomg_025_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_026_UNION
 �ṹ˵��  : IOMG_026 �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_206�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_026 : 3;  /* bit[0-2] : GPIO_206�ܽŵľ��帴�������
                                                   000��GPIO_206��
                                                   001��I2S3_DO��
                                                   010��GPIO_011_SH��
                                                   110��FAC_TEST17��
                                                   111��FAC_TEST17��
                                                   ������������ */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_026_UNION;
#endif
#define SOC_IOC_AO_IOMG_026_iomg_026_START  (0)
#define SOC_IOC_AO_IOMG_026_iomg_026_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_027_UNION
 �ṹ˵��  : IOMG_027 �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_207�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_027 : 3;  /* bit[0-2] : GPIO_207�ܽŵľ��帴�������
                                                   000��GPIO_207��
                                                   001��I2S3_XCLK��
                                                   010��GPIO_012_SH��
                                                   110��FAC_TEST18��
                                                   111��FAC_TEST18��
                                                   ������������ */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_027_UNION;
#endif
#define SOC_IOC_AO_IOMG_027_iomg_027_START  (0)
#define SOC_IOC_AO_IOMG_027_iomg_027_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_028_UNION
 �ṹ˵��  : IOMG_028 �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_208�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_028 : 3;  /* bit[0-2] : GPIO_208�ܽŵľ��帴�������
                                                   000��GPIO_208��
                                                   001��I2S3_XFS��
                                                   010��GPIO_013_SH��
                                                   110��FAC_TEST19��
                                                   111��FAC_TEST19��
                                                   ������������ */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_028_UNION;
#endif
#define SOC_IOC_AO_IOMG_028_iomg_028_START  (0)
#define SOC_IOC_AO_IOMG_028_iomg_028_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_029_UNION
 �ṹ˵��  : IOMG_029 �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_209�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_029 : 3;  /* bit[0-2] : GPIO_209�ܽŵľ��帴�������
                                                   000��GPIO_209��
                                                   001��GPIO_ASP1��
                                                   010��GPIO_014_SH��
                                                   110��FAC_TEST20��
                                                   111��FAC_TEST20��
                                                   ������������ */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_029_UNION;
#endif
#define SOC_IOC_AO_IOMG_029_iomg_029_START  (0)
#define SOC_IOC_AO_IOMG_029_iomg_029_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_030_UNION
 �ṹ˵��  : IOMG_030 �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_210�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_030 : 3;  /* bit[0-2] : GPIO_210�ܽŵľ��帴�������
                                                   000��GPIO_210��
                                                   001��GPIO_ASP2��
                                                   010��GPIO_015_SH��
                                                   110��FAC_TEST21��
                                                   111��FAC_TEST21��
                                                   ������������ */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_030_UNION;
#endif
#define SOC_IOC_AO_IOMG_030_iomg_030_START  (0)
#define SOC_IOC_AO_IOMG_030_iomg_030_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_031_UNION
 �ṹ˵��  : IOMG_031 �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_211�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_031 : 3;  /* bit[0-2] : GPIO_211�ܽŵľ��帴�������
                                                   000��GPIO_211��
                                                   001��GPIO_ASP0��
                                                   010��GPIO_016_SH��
                                                   110��FAC_TEST22��
                                                   111��FAC_TEST22��
                                                   ������������ */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_031_UNION;
#endif
#define SOC_IOC_AO_IOMG_031_iomg_031_START  (0)
#define SOC_IOC_AO_IOMG_031_iomg_031_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_032_UNION
 �ṹ˵��  : IOMG_032 �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_212�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_032 : 3;  /* bit[0-2] : GPIO_212�ܽŵľ��帴�������
                                                   000��GPIO_212��
                                                   001��GPIO_ASP3��
                                                   010��GPIO_017_SH��
                                                   110��FAC_TEST23��
                                                   111��FAC_TEST23��
                                                   ������������ */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_032_UNION;
#endif
#define SOC_IOC_AO_IOMG_032_iomg_032_START  (0)
#define SOC_IOC_AO_IOMG_032_iomg_032_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_033_UNION
 �ṹ˵��  : IOMG_033 �Ĵ����ṹ���塣��ַƫ����:0x084����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_213�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_033 : 3;  /* bit[0-2] : GPIO_213�ܽŵľ��帴�������
                                                   000��GPIO_213��
                                                   001��GPIO_ASP4��
                                                   010��GPIO_018_SH��
                                                   110��FAC_TEST24��
                                                   111��FAC_TEST24��
                                                   ������������ */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_033_UNION;
#endif
#define SOC_IOC_AO_IOMG_033_iomg_033_START  (0)
#define SOC_IOC_AO_IOMG_033_iomg_033_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_034_UNION
 �ṹ˵��  : IOMG_034 �Ĵ����ṹ���塣��ַƫ����:0x088����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_214�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_034 : 3;  /* bit[0-2] : GPIO_214�ܽŵľ��帴�������
                                                   000��GPIO_214��
                                                   010��GPIO_019_SH��
                                                   110��FAC_TEST25��
                                                   111��FAC_TEST25��
                                                   ������������ */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_034_UNION;
#endif
#define SOC_IOC_AO_IOMG_034_iomg_034_START  (0)
#define SOC_IOC_AO_IOMG_034_iomg_034_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_035_UNION
 �ṹ˵��  : IOMG_035 �Ĵ����ṹ���塣��ַƫ����:0x08C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ISP_GPIO03_PRTRB�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_035 : 2;  /* bit[0-1] : ISP_GPIO03_PRTRB�ܽŵľ��帴�������
                                                   00��GPIO_215��
                                                   01��SPI2_CLK��
                                                   10��GPIO_020_SH��
                                                   11��ISP_GPIO03_PRTRB�� */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_035_UNION;
#endif
#define SOC_IOC_AO_IOMG_035_iomg_035_START  (0)
#define SOC_IOC_AO_IOMG_035_iomg_035_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_036_UNION
 �ṹ˵��  : IOMG_036 �Ĵ����ṹ���塣��ַƫ����:0x090����ֵ:0x00000000�����:32
 �Ĵ���˵��: ISP_GPIO04_FTPWM�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_036 : 2;  /* bit[0-1] : ISP_GPIO04_FTPWM�ܽŵľ��帴�������
                                                   00��GPIO_216��
                                                   01��SPI2_DI��
                                                   10��GPIO_021_SH��
                                                   11��ISP_GPIO04_FTPWM�� */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_036_UNION;
#endif
#define SOC_IOC_AO_IOMG_036_iomg_036_START  (0)
#define SOC_IOC_AO_IOMG_036_iomg_036_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_037_UNION
 �ṹ˵��  : IOMG_037 �Ĵ����ṹ���塣��ַƫ����:0x094����ֵ:0x00000000�����:32
 �Ĵ���˵��: ISP_GPIO05_BKPWM�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_037 : 2;  /* bit[0-1] : ISP_GPIO05_BKPWM�ܽŵľ��帴�������
                                                   00��GPIO_217��
                                                   01��SPI2_DO��
                                                   10��GPIO_022_SH��
                                                   11��ISP_GPIO05_BKPWM�� */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_037_UNION;
#endif
#define SOC_IOC_AO_IOMG_037_iomg_037_START  (0)
#define SOC_IOC_AO_IOMG_037_iomg_037_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_038_UNION
 �ṹ˵��  : IOMG_038 �Ĵ����ṹ���塣��ַƫ����:0x098����ֵ:0x00000000�����:32
 �Ĵ���˵��: ISP_GPIO09_ENC�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_038 : 2;  /* bit[0-1] : ISP_GPIO09_ENC�ܽŵľ��帴�������
                                                   00��GPIO_218��
                                                   01��SPI2_CS_N��
                                                   10��GPIO_023_SH��
                                                   11��ISP_GPIO09_ENC�� */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_038_UNION;
#endif
#define SOC_IOC_AO_IOMG_038_iomg_038_START  (0)
#define SOC_IOC_AO_IOMG_038_iomg_038_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_039_UNION
 �ṹ˵��  : IOMG_039 �Ĵ����ṹ���塣��ַƫ����:0x09C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ISP_GPIO07_ENA�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_039 : 3;  /* bit[0-2] : ISP_GPIO07_ENA�ܽŵľ��帴�������
                                                   000��GPIO_219��
                                                   001��UART8_CTS_N��
                                                   010��GPIO_024_SH��
                                                   011��ISP_GPIO07_ENA��
                                                   100��I2C6_SDA��
                                                   ������������ */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_039_UNION;
#endif
#define SOC_IOC_AO_IOMG_039_iomg_039_START  (0)
#define SOC_IOC_AO_IOMG_039_iomg_039_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_040_UNION
 �ṹ˵��  : IOMG_040 �Ĵ����ṹ���塣��ַƫ����:0x0A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ISP_GPIO08_ENB�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_040 : 3;  /* bit[0-2] : ISP_GPIO08_ENB�ܽŵľ��帴�������
                                                   000��GPIO_220��
                                                   001��UART8_RTS_N��
                                                   010��GPIO_025_SH��
                                                   011��ISP_GPIO08_ENB��
                                                   100��I2C6_SCL��
                                                   ������������ */
        unsigned int  reserved : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_040_UNION;
#endif
#define SOC_IOC_AO_IOMG_040_iomg_040_START  (0)
#define SOC_IOC_AO_IOMG_040_iomg_040_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_041_UNION
 �ṹ˵��  : IOMG_041 �Ĵ����ṹ���塣��ַƫ����:0x0A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ISP_GPIO11�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_041 : 2;  /* bit[0-1] : ISP_GPIO11�ܽŵľ��帴�������
                                                   00��GPIO_221��
                                                   01��UART8_RXD��
                                                   10��GPIO_026_SH��
                                                   11��ISP_GPIO11�� */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_041_UNION;
#endif
#define SOC_IOC_AO_IOMG_041_iomg_041_START  (0)
#define SOC_IOC_AO_IOMG_041_iomg_041_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOMG_042_UNION
 �ṹ˵��  : IOMG_042 �Ĵ����ṹ���塣��ַƫ����:0x0A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ISP_GPIO12�ܽŸ��ÿ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iomg_042 : 2;  /* bit[0-1] : ISP_GPIO12�ܽŵľ��帴�������
                                                   00��GPIO_222��
                                                   01��UART8_TXD��
                                                   10��GPIO_027_SH��
                                                   11��ISP_GPIO12�� */
        unsigned int  reserved : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOMG_042_UNION;
#endif
#define SOC_IOC_AO_IOMG_042_iomg_042_START  (0)
#define SOC_IOC_AO_IOMG_042_iomg_042_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_000_UNION
 �ṹ˵��  : IOCG_000 �Ĵ����ṹ���塣��ַƫ����:0x800����ֵ:0x00000002�����:32
 �Ĵ���˵��: GPIO_176���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_000_pu : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_000_pd : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved    : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_000_UNION;
#endif
#define SOC_IOC_AO_IOCG_000_iocg_000_pu_START  (0)
#define SOC_IOC_AO_IOCG_000_iocg_000_pu_END    (0)
#define SOC_IOC_AO_IOCG_000_iocg_000_pd_START  (1)
#define SOC_IOC_AO_IOCG_000_iocg_000_pd_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_001_UNION
 �ṹ˵��  : IOCG_001 �Ĵ����ṹ���塣��ַƫ����:0x804����ֵ:0x00000001�����:32
 �Ĵ���˵��: GPIO_177���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_001_pu : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_001_pd : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved    : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_001_UNION;
#endif
#define SOC_IOC_AO_IOCG_001_iocg_001_pu_START  (0)
#define SOC_IOC_AO_IOCG_001_iocg_001_pu_END    (0)
#define SOC_IOC_AO_IOCG_001_iocg_001_pd_START  (1)
#define SOC_IOC_AO_IOCG_001_iocg_001_pd_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_002_UNION
 �ṹ˵��  : IOCG_002 �Ĵ����ṹ���塣��ַƫ����:0x808����ֵ:0x00000010�����:32
 �Ĵ���˵��: SYSCLK_EN���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_002_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_002_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_002_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_002_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_002_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_002_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_002_UNION;
#endif
#define SOC_IOC_AO_IOCG_002_iocg_002_pu_START   (0)
#define SOC_IOC_AO_IOCG_002_iocg_002_pu_END     (0)
#define SOC_IOC_AO_IOCG_002_iocg_002_pd_START   (1)
#define SOC_IOC_AO_IOCG_002_iocg_002_pd_END     (1)
#define SOC_IOC_AO_IOCG_002_iocg_002_ds0_START  (4)
#define SOC_IOC_AO_IOCG_002_iocg_002_ds0_END    (4)
#define SOC_IOC_AO_IOCG_002_iocg_002_ds1_START  (5)
#define SOC_IOC_AO_IOCG_002_iocg_002_ds1_END    (5)
#define SOC_IOC_AO_IOCG_002_iocg_002_ds2_START  (6)
#define SOC_IOC_AO_IOCG_002_iocg_002_ds2_END    (6)
#define SOC_IOC_AO_IOCG_002_iocg_002_sr_START   (7)
#define SOC_IOC_AO_IOCG_002_iocg_002_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_003_UNION
 �ṹ˵��  : IOCG_003 �Ĵ����ṹ���塣��ַƫ����:0x80C����ֵ:0x00000012�����:32
 �Ĵ���˵��: CLK_OUT0���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_003_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_003_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_003_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_003_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_003_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_003_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_003_UNION;
#endif
#define SOC_IOC_AO_IOCG_003_iocg_003_pu_START   (0)
#define SOC_IOC_AO_IOCG_003_iocg_003_pu_END     (0)
#define SOC_IOC_AO_IOCG_003_iocg_003_pd_START   (1)
#define SOC_IOC_AO_IOCG_003_iocg_003_pd_END     (1)
#define SOC_IOC_AO_IOCG_003_iocg_003_ds0_START  (4)
#define SOC_IOC_AO_IOCG_003_iocg_003_ds0_END    (4)
#define SOC_IOC_AO_IOCG_003_iocg_003_ds1_START  (5)
#define SOC_IOC_AO_IOCG_003_iocg_003_ds1_END    (5)
#define SOC_IOC_AO_IOCG_003_iocg_003_ds2_START  (6)
#define SOC_IOC_AO_IOCG_003_iocg_003_ds2_END    (6)
#define SOC_IOC_AO_IOCG_003_iocg_003_sr_START   (7)
#define SOC_IOC_AO_IOCG_003_iocg_003_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_004_UNION
 �ṹ˵��  : IOCG_004 �Ĵ����ṹ���塣��ַƫ����:0x810����ֵ:0x00000012�����:32
 �Ĵ���˵��: CLK_OUT1���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_004_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_004_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_004_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_004_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_004_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_004_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_004_UNION;
#endif
#define SOC_IOC_AO_IOCG_004_iocg_004_pu_START   (0)
#define SOC_IOC_AO_IOCG_004_iocg_004_pu_END     (0)
#define SOC_IOC_AO_IOCG_004_iocg_004_pd_START   (1)
#define SOC_IOC_AO_IOCG_004_iocg_004_pd_END     (1)
#define SOC_IOC_AO_IOCG_004_iocg_004_ds0_START  (4)
#define SOC_IOC_AO_IOCG_004_iocg_004_ds0_END    (4)
#define SOC_IOC_AO_IOCG_004_iocg_004_ds1_START  (5)
#define SOC_IOC_AO_IOCG_004_iocg_004_ds1_END    (5)
#define SOC_IOC_AO_IOCG_004_iocg_004_ds2_START  (6)
#define SOC_IOC_AO_IOCG_004_iocg_004_ds2_END    (6)
#define SOC_IOC_AO_IOCG_004_iocg_004_sr_START   (7)
#define SOC_IOC_AO_IOCG_004_iocg_004_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_005_UNION
 �ṹ˵��  : IOCG_005 �Ĵ����ṹ���塣��ַƫ����:0x814����ֵ:0x00000012�����:32
 �Ĵ���˵��: BLPWM_CABC���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_005_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_005_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_005_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_005_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_005_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_005_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_005_UNION;
#endif
#define SOC_IOC_AO_IOCG_005_iocg_005_pu_START   (0)
#define SOC_IOC_AO_IOCG_005_iocg_005_pu_END     (0)
#define SOC_IOC_AO_IOCG_005_iocg_005_pd_START   (1)
#define SOC_IOC_AO_IOCG_005_iocg_005_pd_END     (1)
#define SOC_IOC_AO_IOCG_005_iocg_005_ds0_START  (4)
#define SOC_IOC_AO_IOCG_005_iocg_005_ds0_END    (4)
#define SOC_IOC_AO_IOCG_005_iocg_005_ds1_START  (5)
#define SOC_IOC_AO_IOCG_005_iocg_005_ds1_END    (5)
#define SOC_IOC_AO_IOCG_005_iocg_005_ds2_START  (6)
#define SOC_IOC_AO_IOCG_005_iocg_005_ds2_END    (6)
#define SOC_IOC_AO_IOCG_005_iocg_005_sr_START   (7)
#define SOC_IOC_AO_IOCG_005_iocg_005_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_006_UNION
 �ṹ˵��  : IOCG_006 �Ĵ����ṹ���塣��ַƫ����:0x818����ֵ:0x00000012�����:32
 �Ĵ���˵��: BLPWM_BL���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_006_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_006_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_006_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_006_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_006_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_006_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_006_UNION;
#endif
#define SOC_IOC_AO_IOCG_006_iocg_006_pu_START   (0)
#define SOC_IOC_AO_IOCG_006_iocg_006_pu_END     (0)
#define SOC_IOC_AO_IOCG_006_iocg_006_pd_START   (1)
#define SOC_IOC_AO_IOCG_006_iocg_006_pd_END     (1)
#define SOC_IOC_AO_IOCG_006_iocg_006_ds0_START  (4)
#define SOC_IOC_AO_IOCG_006_iocg_006_ds0_END    (4)
#define SOC_IOC_AO_IOCG_006_iocg_006_ds1_START  (5)
#define SOC_IOC_AO_IOCG_006_iocg_006_ds1_END    (5)
#define SOC_IOC_AO_IOCG_006_iocg_006_ds2_START  (6)
#define SOC_IOC_AO_IOCG_006_iocg_006_ds2_END    (6)
#define SOC_IOC_AO_IOCG_006_iocg_006_sr_START   (7)
#define SOC_IOC_AO_IOCG_006_iocg_006_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_007_UNION
 �ṹ˵��  : IOCG_007 �Ĵ����ṹ���塣��ַƫ����:0x81C����ֵ:0x00000012�����:32
 �Ĵ���˵��: I2C0_SCL���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_007_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_007_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_007_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_007_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_007_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_007_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_007_UNION;
#endif
#define SOC_IOC_AO_IOCG_007_iocg_007_pu_START   (0)
#define SOC_IOC_AO_IOCG_007_iocg_007_pu_END     (0)
#define SOC_IOC_AO_IOCG_007_iocg_007_pd_START   (1)
#define SOC_IOC_AO_IOCG_007_iocg_007_pd_END     (1)
#define SOC_IOC_AO_IOCG_007_iocg_007_ds0_START  (4)
#define SOC_IOC_AO_IOCG_007_iocg_007_ds0_END    (4)
#define SOC_IOC_AO_IOCG_007_iocg_007_ds1_START  (5)
#define SOC_IOC_AO_IOCG_007_iocg_007_ds1_END    (5)
#define SOC_IOC_AO_IOCG_007_iocg_007_ds2_START  (6)
#define SOC_IOC_AO_IOCG_007_iocg_007_ds2_END    (6)
#define SOC_IOC_AO_IOCG_007_iocg_007_sr_START   (7)
#define SOC_IOC_AO_IOCG_007_iocg_007_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_008_UNION
 �ṹ˵��  : IOCG_008 �Ĵ����ṹ���塣��ַƫ����:0x820����ֵ:0x00000012�����:32
 �Ĵ���˵��: I2C0_SDA���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_008_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_008_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_008_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_008_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_008_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_008_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_008_UNION;
#endif
#define SOC_IOC_AO_IOCG_008_iocg_008_pu_START   (0)
#define SOC_IOC_AO_IOCG_008_iocg_008_pu_END     (0)
#define SOC_IOC_AO_IOCG_008_iocg_008_pd_START   (1)
#define SOC_IOC_AO_IOCG_008_iocg_008_pd_END     (1)
#define SOC_IOC_AO_IOCG_008_iocg_008_ds0_START  (4)
#define SOC_IOC_AO_IOCG_008_iocg_008_ds0_END    (4)
#define SOC_IOC_AO_IOCG_008_iocg_008_ds1_START  (5)
#define SOC_IOC_AO_IOCG_008_iocg_008_ds1_END    (5)
#define SOC_IOC_AO_IOCG_008_iocg_008_ds2_START  (6)
#define SOC_IOC_AO_IOCG_008_iocg_008_ds2_END    (6)
#define SOC_IOC_AO_IOCG_008_iocg_008_sr_START   (7)
#define SOC_IOC_AO_IOCG_008_iocg_008_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_009_UNION
 �ṹ˵��  : IOCG_009 �Ĵ����ṹ���塣��ַƫ����:0x824����ֵ:0x00000012�����:32
 �Ĵ���˵��: I2C1_SCL���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_009_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_009_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_009_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_009_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_009_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_009_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_009_UNION;
#endif
#define SOC_IOC_AO_IOCG_009_iocg_009_pu_START   (0)
#define SOC_IOC_AO_IOCG_009_iocg_009_pu_END     (0)
#define SOC_IOC_AO_IOCG_009_iocg_009_pd_START   (1)
#define SOC_IOC_AO_IOCG_009_iocg_009_pd_END     (1)
#define SOC_IOC_AO_IOCG_009_iocg_009_ds0_START  (4)
#define SOC_IOC_AO_IOCG_009_iocg_009_ds0_END    (4)
#define SOC_IOC_AO_IOCG_009_iocg_009_ds1_START  (5)
#define SOC_IOC_AO_IOCG_009_iocg_009_ds1_END    (5)
#define SOC_IOC_AO_IOCG_009_iocg_009_ds2_START  (6)
#define SOC_IOC_AO_IOCG_009_iocg_009_ds2_END    (6)
#define SOC_IOC_AO_IOCG_009_iocg_009_sr_START   (7)
#define SOC_IOC_AO_IOCG_009_iocg_009_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_010_UNION
 �ṹ˵��  : IOCG_010 �Ĵ����ṹ���塣��ַƫ����:0x828����ֵ:0x00000012�����:32
 �Ĵ���˵��: I2C1_SDA���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_010_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_010_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_010_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_010_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_010_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_010_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_010_UNION;
#endif
#define SOC_IOC_AO_IOCG_010_iocg_010_pu_START   (0)
#define SOC_IOC_AO_IOCG_010_iocg_010_pu_END     (0)
#define SOC_IOC_AO_IOCG_010_iocg_010_pd_START   (1)
#define SOC_IOC_AO_IOCG_010_iocg_010_pd_END     (1)
#define SOC_IOC_AO_IOCG_010_iocg_010_ds0_START  (4)
#define SOC_IOC_AO_IOCG_010_iocg_010_ds0_END    (4)
#define SOC_IOC_AO_IOCG_010_iocg_010_ds1_START  (5)
#define SOC_IOC_AO_IOCG_010_iocg_010_ds1_END    (5)
#define SOC_IOC_AO_IOCG_010_iocg_010_ds2_START  (6)
#define SOC_IOC_AO_IOCG_010_iocg_010_ds2_END    (6)
#define SOC_IOC_AO_IOCG_010_iocg_010_sr_START   (7)
#define SOC_IOC_AO_IOCG_010_iocg_010_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_011_UNION
 �ṹ˵��  : IOCG_011 �Ĵ����ṹ���塣��ַƫ����:0x82C����ֵ:0x00000012�����:32
 �Ĵ���˵��: I2C2_SCL���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_011_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_011_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_011_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_011_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_011_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_011_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_011_UNION;
#endif
#define SOC_IOC_AO_IOCG_011_iocg_011_pu_START   (0)
#define SOC_IOC_AO_IOCG_011_iocg_011_pu_END     (0)
#define SOC_IOC_AO_IOCG_011_iocg_011_pd_START   (1)
#define SOC_IOC_AO_IOCG_011_iocg_011_pd_END     (1)
#define SOC_IOC_AO_IOCG_011_iocg_011_ds0_START  (4)
#define SOC_IOC_AO_IOCG_011_iocg_011_ds0_END    (4)
#define SOC_IOC_AO_IOCG_011_iocg_011_ds1_START  (5)
#define SOC_IOC_AO_IOCG_011_iocg_011_ds1_END    (5)
#define SOC_IOC_AO_IOCG_011_iocg_011_ds2_START  (6)
#define SOC_IOC_AO_IOCG_011_iocg_011_ds2_END    (6)
#define SOC_IOC_AO_IOCG_011_iocg_011_sr_START   (7)
#define SOC_IOC_AO_IOCG_011_iocg_011_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_012_UNION
 �ṹ˵��  : IOCG_012 �Ĵ����ṹ���塣��ַƫ����:0x830����ֵ:0x00000012�����:32
 �Ĵ���˵��: I2C2_SDA���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_012_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_012_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_012_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_012_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_012_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_012_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_012_UNION;
#endif
#define SOC_IOC_AO_IOCG_012_iocg_012_pu_START   (0)
#define SOC_IOC_AO_IOCG_012_iocg_012_pu_END     (0)
#define SOC_IOC_AO_IOCG_012_iocg_012_pd_START   (1)
#define SOC_IOC_AO_IOCG_012_iocg_012_pd_END     (1)
#define SOC_IOC_AO_IOCG_012_iocg_012_ds0_START  (4)
#define SOC_IOC_AO_IOCG_012_iocg_012_ds0_END    (4)
#define SOC_IOC_AO_IOCG_012_iocg_012_ds1_START  (5)
#define SOC_IOC_AO_IOCG_012_iocg_012_ds1_END    (5)
#define SOC_IOC_AO_IOCG_012_iocg_012_ds2_START  (6)
#define SOC_IOC_AO_IOCG_012_iocg_012_ds2_END    (6)
#define SOC_IOC_AO_IOCG_012_iocg_012_sr_START   (7)
#define SOC_IOC_AO_IOCG_012_iocg_012_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_013_UNION
 �ṹ˵��  : IOCG_013 �Ĵ����ṹ���塣��ַƫ����:0x834����ֵ:0x00000012�����:32
 �Ĵ���˵��: SLIMBUS_CLK���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_013_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_013_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_013_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_013_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_013_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_013_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_013_UNION;
#endif
#define SOC_IOC_AO_IOCG_013_iocg_013_pu_START   (0)
#define SOC_IOC_AO_IOCG_013_iocg_013_pu_END     (0)
#define SOC_IOC_AO_IOCG_013_iocg_013_pd_START   (1)
#define SOC_IOC_AO_IOCG_013_iocg_013_pd_END     (1)
#define SOC_IOC_AO_IOCG_013_iocg_013_ds0_START  (4)
#define SOC_IOC_AO_IOCG_013_iocg_013_ds0_END    (4)
#define SOC_IOC_AO_IOCG_013_iocg_013_ds1_START  (5)
#define SOC_IOC_AO_IOCG_013_iocg_013_ds1_END    (5)
#define SOC_IOC_AO_IOCG_013_iocg_013_ds2_START  (6)
#define SOC_IOC_AO_IOCG_013_iocg_013_ds2_END    (6)
#define SOC_IOC_AO_IOCG_013_iocg_013_sr_START   (7)
#define SOC_IOC_AO_IOCG_013_iocg_013_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_014_UNION
 �ṹ˵��  : IOCG_014 �Ĵ����ṹ���塣��ַƫ����:0x838����ֵ:0x00000012�����:32
 �Ĵ���˵��: SLIMBUS_DATA���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_014_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_014_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_014_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_014_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_014_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_014_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_014_UNION;
#endif
#define SOC_IOC_AO_IOCG_014_iocg_014_pu_START   (0)
#define SOC_IOC_AO_IOCG_014_iocg_014_pu_END     (0)
#define SOC_IOC_AO_IOCG_014_iocg_014_pd_START   (1)
#define SOC_IOC_AO_IOCG_014_iocg_014_pd_END     (1)
#define SOC_IOC_AO_IOCG_014_iocg_014_ds0_START  (4)
#define SOC_IOC_AO_IOCG_014_iocg_014_ds0_END    (4)
#define SOC_IOC_AO_IOCG_014_iocg_014_ds1_START  (5)
#define SOC_IOC_AO_IOCG_014_iocg_014_ds1_END    (5)
#define SOC_IOC_AO_IOCG_014_iocg_014_ds2_START  (6)
#define SOC_IOC_AO_IOCG_014_iocg_014_ds2_END    (6)
#define SOC_IOC_AO_IOCG_014_iocg_014_sr_START   (7)
#define SOC_IOC_AO_IOCG_014_iocg_014_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_015_UNION
 �ṹ˵��  : IOCG_015 �Ĵ����ṹ���塣��ַƫ����:0x83C����ֵ:0x00000011�����:32
 �Ĵ���˵��: GPIO_191���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_015_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_015_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_015_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_015_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_015_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_015_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_015_UNION;
#endif
#define SOC_IOC_AO_IOCG_015_iocg_015_pu_START   (0)
#define SOC_IOC_AO_IOCG_015_iocg_015_pu_END     (0)
#define SOC_IOC_AO_IOCG_015_iocg_015_pd_START   (1)
#define SOC_IOC_AO_IOCG_015_iocg_015_pd_END     (1)
#define SOC_IOC_AO_IOCG_015_iocg_015_ds0_START  (4)
#define SOC_IOC_AO_IOCG_015_iocg_015_ds0_END    (4)
#define SOC_IOC_AO_IOCG_015_iocg_015_ds1_START  (5)
#define SOC_IOC_AO_IOCG_015_iocg_015_ds1_END    (5)
#define SOC_IOC_AO_IOCG_015_iocg_015_ds2_START  (6)
#define SOC_IOC_AO_IOCG_015_iocg_015_ds2_END    (6)
#define SOC_IOC_AO_IOCG_015_iocg_015_sr_START   (7)
#define SOC_IOC_AO_IOCG_015_iocg_015_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_016_UNION
 �ṹ˵��  : IOCG_016 �Ĵ����ṹ���塣��ַƫ����:0x840����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_192���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_016_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_016_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_016_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_016_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_016_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_016_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_016_UNION;
#endif
#define SOC_IOC_AO_IOCG_016_iocg_016_pu_START   (0)
#define SOC_IOC_AO_IOCG_016_iocg_016_pu_END     (0)
#define SOC_IOC_AO_IOCG_016_iocg_016_pd_START   (1)
#define SOC_IOC_AO_IOCG_016_iocg_016_pd_END     (1)
#define SOC_IOC_AO_IOCG_016_iocg_016_ds0_START  (4)
#define SOC_IOC_AO_IOCG_016_iocg_016_ds0_END    (4)
#define SOC_IOC_AO_IOCG_016_iocg_016_ds1_START  (5)
#define SOC_IOC_AO_IOCG_016_iocg_016_ds1_END    (5)
#define SOC_IOC_AO_IOCG_016_iocg_016_ds2_START  (6)
#define SOC_IOC_AO_IOCG_016_iocg_016_ds2_END    (6)
#define SOC_IOC_AO_IOCG_016_iocg_016_sr_START   (7)
#define SOC_IOC_AO_IOCG_016_iocg_016_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_017_UNION
 �ṹ˵��  : IOCG_017 �Ĵ����ṹ���塣��ַƫ����:0x844����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_193���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_017_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_017_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_017_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_017_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_017_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_017_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_017_UNION;
#endif
#define SOC_IOC_AO_IOCG_017_iocg_017_pu_START   (0)
#define SOC_IOC_AO_IOCG_017_iocg_017_pu_END     (0)
#define SOC_IOC_AO_IOCG_017_iocg_017_pd_START   (1)
#define SOC_IOC_AO_IOCG_017_iocg_017_pd_END     (1)
#define SOC_IOC_AO_IOCG_017_iocg_017_ds0_START  (4)
#define SOC_IOC_AO_IOCG_017_iocg_017_ds0_END    (4)
#define SOC_IOC_AO_IOCG_017_iocg_017_ds1_START  (5)
#define SOC_IOC_AO_IOCG_017_iocg_017_ds1_END    (5)
#define SOC_IOC_AO_IOCG_017_iocg_017_ds2_START  (6)
#define SOC_IOC_AO_IOCG_017_iocg_017_ds2_END    (6)
#define SOC_IOC_AO_IOCG_017_iocg_017_sr_START   (7)
#define SOC_IOC_AO_IOCG_017_iocg_017_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_018_UNION
 �ṹ˵��  : IOCG_018 �Ĵ����ṹ���塣��ַƫ����:0x848����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_194���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_018_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_018_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_018_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_018_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_018_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_018_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_018_UNION;
#endif
#define SOC_IOC_AO_IOCG_018_iocg_018_pu_START   (0)
#define SOC_IOC_AO_IOCG_018_iocg_018_pu_END     (0)
#define SOC_IOC_AO_IOCG_018_iocg_018_pd_START   (1)
#define SOC_IOC_AO_IOCG_018_iocg_018_pd_END     (1)
#define SOC_IOC_AO_IOCG_018_iocg_018_ds0_START  (4)
#define SOC_IOC_AO_IOCG_018_iocg_018_ds0_END    (4)
#define SOC_IOC_AO_IOCG_018_iocg_018_ds1_START  (5)
#define SOC_IOC_AO_IOCG_018_iocg_018_ds1_END    (5)
#define SOC_IOC_AO_IOCG_018_iocg_018_ds2_START  (6)
#define SOC_IOC_AO_IOCG_018_iocg_018_ds2_END    (6)
#define SOC_IOC_AO_IOCG_018_iocg_018_sr_START   (7)
#define SOC_IOC_AO_IOCG_018_iocg_018_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_019_UNION
 �ṹ˵��  : IOCG_019 �Ĵ����ṹ���塣��ַƫ����:0x84C����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_195���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_019_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_019_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_019_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_019_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_019_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_019_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_019_UNION;
#endif
#define SOC_IOC_AO_IOCG_019_iocg_019_pu_START   (0)
#define SOC_IOC_AO_IOCG_019_iocg_019_pu_END     (0)
#define SOC_IOC_AO_IOCG_019_iocg_019_pd_START   (1)
#define SOC_IOC_AO_IOCG_019_iocg_019_pd_END     (1)
#define SOC_IOC_AO_IOCG_019_iocg_019_ds0_START  (4)
#define SOC_IOC_AO_IOCG_019_iocg_019_ds0_END    (4)
#define SOC_IOC_AO_IOCG_019_iocg_019_ds1_START  (5)
#define SOC_IOC_AO_IOCG_019_iocg_019_ds1_END    (5)
#define SOC_IOC_AO_IOCG_019_iocg_019_ds2_START  (6)
#define SOC_IOC_AO_IOCG_019_iocg_019_ds2_END    (6)
#define SOC_IOC_AO_IOCG_019_iocg_019_sr_START   (7)
#define SOC_IOC_AO_IOCG_019_iocg_019_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_020_UNION
 �ṹ˵��  : IOCG_020 �Ĵ����ṹ���塣��ַƫ����:0x850����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_196���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_020_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_020_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_020_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_020_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_020_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_020_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_020_UNION;
#endif
#define SOC_IOC_AO_IOCG_020_iocg_020_pu_START   (0)
#define SOC_IOC_AO_IOCG_020_iocg_020_pu_END     (0)
#define SOC_IOC_AO_IOCG_020_iocg_020_pd_START   (1)
#define SOC_IOC_AO_IOCG_020_iocg_020_pd_END     (1)
#define SOC_IOC_AO_IOCG_020_iocg_020_ds0_START  (4)
#define SOC_IOC_AO_IOCG_020_iocg_020_ds0_END    (4)
#define SOC_IOC_AO_IOCG_020_iocg_020_ds1_START  (5)
#define SOC_IOC_AO_IOCG_020_iocg_020_ds1_END    (5)
#define SOC_IOC_AO_IOCG_020_iocg_020_ds2_START  (6)
#define SOC_IOC_AO_IOCG_020_iocg_020_ds2_END    (6)
#define SOC_IOC_AO_IOCG_020_iocg_020_sr_START   (7)
#define SOC_IOC_AO_IOCG_020_iocg_020_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_021_UNION
 �ṹ˵��  : IOCG_021 �Ĵ����ṹ���塣��ַƫ����:0x854����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_197���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_021_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_021_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_021_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_021_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_021_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_021_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_021_UNION;
#endif
#define SOC_IOC_AO_IOCG_021_iocg_021_pu_START   (0)
#define SOC_IOC_AO_IOCG_021_iocg_021_pu_END     (0)
#define SOC_IOC_AO_IOCG_021_iocg_021_pd_START   (1)
#define SOC_IOC_AO_IOCG_021_iocg_021_pd_END     (1)
#define SOC_IOC_AO_IOCG_021_iocg_021_ds0_START  (4)
#define SOC_IOC_AO_IOCG_021_iocg_021_ds0_END    (4)
#define SOC_IOC_AO_IOCG_021_iocg_021_ds1_START  (5)
#define SOC_IOC_AO_IOCG_021_iocg_021_ds1_END    (5)
#define SOC_IOC_AO_IOCG_021_iocg_021_ds2_START  (6)
#define SOC_IOC_AO_IOCG_021_iocg_021_ds2_END    (6)
#define SOC_IOC_AO_IOCG_021_iocg_021_sr_START   (7)
#define SOC_IOC_AO_IOCG_021_iocg_021_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_022_UNION
 �ṹ˵��  : IOCG_022 �Ĵ����ṹ���塣��ַƫ����:0x858����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_198���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_022_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_022_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_022_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_022_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_022_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_022_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_022_UNION;
#endif
#define SOC_IOC_AO_IOCG_022_iocg_022_pu_START   (0)
#define SOC_IOC_AO_IOCG_022_iocg_022_pu_END     (0)
#define SOC_IOC_AO_IOCG_022_iocg_022_pd_START   (1)
#define SOC_IOC_AO_IOCG_022_iocg_022_pd_END     (1)
#define SOC_IOC_AO_IOCG_022_iocg_022_ds0_START  (4)
#define SOC_IOC_AO_IOCG_022_iocg_022_ds0_END    (4)
#define SOC_IOC_AO_IOCG_022_iocg_022_ds1_START  (5)
#define SOC_IOC_AO_IOCG_022_iocg_022_ds1_END    (5)
#define SOC_IOC_AO_IOCG_022_iocg_022_ds2_START  (6)
#define SOC_IOC_AO_IOCG_022_iocg_022_ds2_END    (6)
#define SOC_IOC_AO_IOCG_022_iocg_022_sr_START   (7)
#define SOC_IOC_AO_IOCG_022_iocg_022_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_023_UNION
 �ṹ˵��  : IOCG_023 �Ĵ����ṹ���塣��ַƫ����:0x85C����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_199���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_023_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_023_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_023_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_023_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_023_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_023_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_023_UNION;
#endif
#define SOC_IOC_AO_IOCG_023_iocg_023_pu_START   (0)
#define SOC_IOC_AO_IOCG_023_iocg_023_pu_END     (0)
#define SOC_IOC_AO_IOCG_023_iocg_023_pd_START   (1)
#define SOC_IOC_AO_IOCG_023_iocg_023_pd_END     (1)
#define SOC_IOC_AO_IOCG_023_iocg_023_ds0_START  (4)
#define SOC_IOC_AO_IOCG_023_iocg_023_ds0_END    (4)
#define SOC_IOC_AO_IOCG_023_iocg_023_ds1_START  (5)
#define SOC_IOC_AO_IOCG_023_iocg_023_ds1_END    (5)
#define SOC_IOC_AO_IOCG_023_iocg_023_ds2_START  (6)
#define SOC_IOC_AO_IOCG_023_iocg_023_ds2_END    (6)
#define SOC_IOC_AO_IOCG_023_iocg_023_sr_START   (7)
#define SOC_IOC_AO_IOCG_023_iocg_023_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_024_UNION
 �ṹ˵��  : IOCG_024 �Ĵ����ṹ���塣��ַƫ����:0x860����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_200���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_024_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_024_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_024_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_024_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_024_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_024_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_024_UNION;
#endif
#define SOC_IOC_AO_IOCG_024_iocg_024_pu_START   (0)
#define SOC_IOC_AO_IOCG_024_iocg_024_pu_END     (0)
#define SOC_IOC_AO_IOCG_024_iocg_024_pd_START   (1)
#define SOC_IOC_AO_IOCG_024_iocg_024_pd_END     (1)
#define SOC_IOC_AO_IOCG_024_iocg_024_ds0_START  (4)
#define SOC_IOC_AO_IOCG_024_iocg_024_ds0_END    (4)
#define SOC_IOC_AO_IOCG_024_iocg_024_ds1_START  (5)
#define SOC_IOC_AO_IOCG_024_iocg_024_ds1_END    (5)
#define SOC_IOC_AO_IOCG_024_iocg_024_ds2_START  (6)
#define SOC_IOC_AO_IOCG_024_iocg_024_ds2_END    (6)
#define SOC_IOC_AO_IOCG_024_iocg_024_sr_START   (7)
#define SOC_IOC_AO_IOCG_024_iocg_024_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_025_UNION
 �ṹ˵��  : IOCG_025 �Ĵ����ṹ���塣��ַƫ����:0x864����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_201���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_025_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_025_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_025_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_025_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_025_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_025_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_025_UNION;
#endif
#define SOC_IOC_AO_IOCG_025_iocg_025_pu_START   (0)
#define SOC_IOC_AO_IOCG_025_iocg_025_pu_END     (0)
#define SOC_IOC_AO_IOCG_025_iocg_025_pd_START   (1)
#define SOC_IOC_AO_IOCG_025_iocg_025_pd_END     (1)
#define SOC_IOC_AO_IOCG_025_iocg_025_ds0_START  (4)
#define SOC_IOC_AO_IOCG_025_iocg_025_ds0_END    (4)
#define SOC_IOC_AO_IOCG_025_iocg_025_ds1_START  (5)
#define SOC_IOC_AO_IOCG_025_iocg_025_ds1_END    (5)
#define SOC_IOC_AO_IOCG_025_iocg_025_ds2_START  (6)
#define SOC_IOC_AO_IOCG_025_iocg_025_ds2_END    (6)
#define SOC_IOC_AO_IOCG_025_iocg_025_sr_START   (7)
#define SOC_IOC_AO_IOCG_025_iocg_025_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_026_UNION
 �ṹ˵��  : IOCG_026 �Ĵ����ṹ���塣��ַƫ����:0x868����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_202���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_026_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_026_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_026_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_026_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_026_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_026_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_026_UNION;
#endif
#define SOC_IOC_AO_IOCG_026_iocg_026_pu_START   (0)
#define SOC_IOC_AO_IOCG_026_iocg_026_pu_END     (0)
#define SOC_IOC_AO_IOCG_026_iocg_026_pd_START   (1)
#define SOC_IOC_AO_IOCG_026_iocg_026_pd_END     (1)
#define SOC_IOC_AO_IOCG_026_iocg_026_ds0_START  (4)
#define SOC_IOC_AO_IOCG_026_iocg_026_ds0_END    (4)
#define SOC_IOC_AO_IOCG_026_iocg_026_ds1_START  (5)
#define SOC_IOC_AO_IOCG_026_iocg_026_ds1_END    (5)
#define SOC_IOC_AO_IOCG_026_iocg_026_ds2_START  (6)
#define SOC_IOC_AO_IOCG_026_iocg_026_ds2_END    (6)
#define SOC_IOC_AO_IOCG_026_iocg_026_sr_START   (7)
#define SOC_IOC_AO_IOCG_026_iocg_026_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_027_UNION
 �ṹ˵��  : IOCG_027 �Ĵ����ṹ���塣��ַƫ����:0x86C����ֵ:0x00000000�����:32
 �Ĵ���˵��: GPIO_203���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_027_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_027_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_027_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_027_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_027_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_027_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_027_UNION;
#endif
#define SOC_IOC_AO_IOCG_027_iocg_027_pu_START   (0)
#define SOC_IOC_AO_IOCG_027_iocg_027_pu_END     (0)
#define SOC_IOC_AO_IOCG_027_iocg_027_pd_START   (1)
#define SOC_IOC_AO_IOCG_027_iocg_027_pd_END     (1)
#define SOC_IOC_AO_IOCG_027_iocg_027_ds0_START  (4)
#define SOC_IOC_AO_IOCG_027_iocg_027_ds0_END    (4)
#define SOC_IOC_AO_IOCG_027_iocg_027_ds1_START  (5)
#define SOC_IOC_AO_IOCG_027_iocg_027_ds1_END    (5)
#define SOC_IOC_AO_IOCG_027_iocg_027_ds2_START  (6)
#define SOC_IOC_AO_IOCG_027_iocg_027_ds2_END    (6)
#define SOC_IOC_AO_IOCG_027_iocg_027_sr_START   (7)
#define SOC_IOC_AO_IOCG_027_iocg_027_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_028_UNION
 �ṹ˵��  : IOCG_028 �Ĵ����ṹ���塣��ַƫ����:0x870����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_204���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_028_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_028_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_028_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_028_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_028_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_028_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_028_UNION;
#endif
#define SOC_IOC_AO_IOCG_028_iocg_028_pu_START   (0)
#define SOC_IOC_AO_IOCG_028_iocg_028_pu_END     (0)
#define SOC_IOC_AO_IOCG_028_iocg_028_pd_START   (1)
#define SOC_IOC_AO_IOCG_028_iocg_028_pd_END     (1)
#define SOC_IOC_AO_IOCG_028_iocg_028_ds0_START  (4)
#define SOC_IOC_AO_IOCG_028_iocg_028_ds0_END    (4)
#define SOC_IOC_AO_IOCG_028_iocg_028_ds1_START  (5)
#define SOC_IOC_AO_IOCG_028_iocg_028_ds1_END    (5)
#define SOC_IOC_AO_IOCG_028_iocg_028_ds2_START  (6)
#define SOC_IOC_AO_IOCG_028_iocg_028_ds2_END    (6)
#define SOC_IOC_AO_IOCG_028_iocg_028_sr_START   (7)
#define SOC_IOC_AO_IOCG_028_iocg_028_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_029_UNION
 �ṹ˵��  : IOCG_029 �Ĵ����ṹ���塣��ַƫ����:0x874����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_205���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_029_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_029_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_029_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_029_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_029_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_029_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_029_UNION;
#endif
#define SOC_IOC_AO_IOCG_029_iocg_029_pu_START   (0)
#define SOC_IOC_AO_IOCG_029_iocg_029_pu_END     (0)
#define SOC_IOC_AO_IOCG_029_iocg_029_pd_START   (1)
#define SOC_IOC_AO_IOCG_029_iocg_029_pd_END     (1)
#define SOC_IOC_AO_IOCG_029_iocg_029_ds0_START  (4)
#define SOC_IOC_AO_IOCG_029_iocg_029_ds0_END    (4)
#define SOC_IOC_AO_IOCG_029_iocg_029_ds1_START  (5)
#define SOC_IOC_AO_IOCG_029_iocg_029_ds1_END    (5)
#define SOC_IOC_AO_IOCG_029_iocg_029_ds2_START  (6)
#define SOC_IOC_AO_IOCG_029_iocg_029_ds2_END    (6)
#define SOC_IOC_AO_IOCG_029_iocg_029_sr_START   (7)
#define SOC_IOC_AO_IOCG_029_iocg_029_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_030_UNION
 �ṹ˵��  : IOCG_030 �Ĵ����ṹ���塣��ַƫ����:0x878����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_206���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_030_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_030_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_030_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_030_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_030_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_030_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_030_UNION;
#endif
#define SOC_IOC_AO_IOCG_030_iocg_030_pu_START   (0)
#define SOC_IOC_AO_IOCG_030_iocg_030_pu_END     (0)
#define SOC_IOC_AO_IOCG_030_iocg_030_pd_START   (1)
#define SOC_IOC_AO_IOCG_030_iocg_030_pd_END     (1)
#define SOC_IOC_AO_IOCG_030_iocg_030_ds0_START  (4)
#define SOC_IOC_AO_IOCG_030_iocg_030_ds0_END    (4)
#define SOC_IOC_AO_IOCG_030_iocg_030_ds1_START  (5)
#define SOC_IOC_AO_IOCG_030_iocg_030_ds1_END    (5)
#define SOC_IOC_AO_IOCG_030_iocg_030_ds2_START  (6)
#define SOC_IOC_AO_IOCG_030_iocg_030_ds2_END    (6)
#define SOC_IOC_AO_IOCG_030_iocg_030_sr_START   (7)
#define SOC_IOC_AO_IOCG_030_iocg_030_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_031_UNION
 �ṹ˵��  : IOCG_031 �Ĵ����ṹ���塣��ַƫ����:0x87C����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_207���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_031_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_031_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_031_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_031_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_031_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_031_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_031_UNION;
#endif
#define SOC_IOC_AO_IOCG_031_iocg_031_pu_START   (0)
#define SOC_IOC_AO_IOCG_031_iocg_031_pu_END     (0)
#define SOC_IOC_AO_IOCG_031_iocg_031_pd_START   (1)
#define SOC_IOC_AO_IOCG_031_iocg_031_pd_END     (1)
#define SOC_IOC_AO_IOCG_031_iocg_031_ds0_START  (4)
#define SOC_IOC_AO_IOCG_031_iocg_031_ds0_END    (4)
#define SOC_IOC_AO_IOCG_031_iocg_031_ds1_START  (5)
#define SOC_IOC_AO_IOCG_031_iocg_031_ds1_END    (5)
#define SOC_IOC_AO_IOCG_031_iocg_031_ds2_START  (6)
#define SOC_IOC_AO_IOCG_031_iocg_031_ds2_END    (6)
#define SOC_IOC_AO_IOCG_031_iocg_031_sr_START   (7)
#define SOC_IOC_AO_IOCG_031_iocg_031_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_032_UNION
 �ṹ˵��  : IOCG_032 �Ĵ����ṹ���塣��ַƫ����:0x880����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_208���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_032_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_032_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_032_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_032_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_032_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_032_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_032_UNION;
#endif
#define SOC_IOC_AO_IOCG_032_iocg_032_pu_START   (0)
#define SOC_IOC_AO_IOCG_032_iocg_032_pu_END     (0)
#define SOC_IOC_AO_IOCG_032_iocg_032_pd_START   (1)
#define SOC_IOC_AO_IOCG_032_iocg_032_pd_END     (1)
#define SOC_IOC_AO_IOCG_032_iocg_032_ds0_START  (4)
#define SOC_IOC_AO_IOCG_032_iocg_032_ds0_END    (4)
#define SOC_IOC_AO_IOCG_032_iocg_032_ds1_START  (5)
#define SOC_IOC_AO_IOCG_032_iocg_032_ds1_END    (5)
#define SOC_IOC_AO_IOCG_032_iocg_032_ds2_START  (6)
#define SOC_IOC_AO_IOCG_032_iocg_032_ds2_END    (6)
#define SOC_IOC_AO_IOCG_032_iocg_032_sr_START   (7)
#define SOC_IOC_AO_IOCG_032_iocg_032_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_033_UNION
 �ṹ˵��  : IOCG_033 �Ĵ����ṹ���塣��ַƫ����:0x884����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_209���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_033_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_033_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_033_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_033_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_033_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_033_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_033_UNION;
#endif
#define SOC_IOC_AO_IOCG_033_iocg_033_pu_START   (0)
#define SOC_IOC_AO_IOCG_033_iocg_033_pu_END     (0)
#define SOC_IOC_AO_IOCG_033_iocg_033_pd_START   (1)
#define SOC_IOC_AO_IOCG_033_iocg_033_pd_END     (1)
#define SOC_IOC_AO_IOCG_033_iocg_033_ds0_START  (4)
#define SOC_IOC_AO_IOCG_033_iocg_033_ds0_END    (4)
#define SOC_IOC_AO_IOCG_033_iocg_033_ds1_START  (5)
#define SOC_IOC_AO_IOCG_033_iocg_033_ds1_END    (5)
#define SOC_IOC_AO_IOCG_033_iocg_033_ds2_START  (6)
#define SOC_IOC_AO_IOCG_033_iocg_033_ds2_END    (6)
#define SOC_IOC_AO_IOCG_033_iocg_033_sr_START   (7)
#define SOC_IOC_AO_IOCG_033_iocg_033_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_034_UNION
 �ṹ˵��  : IOCG_034 �Ĵ����ṹ���塣��ַƫ����:0x888����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_210���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_034_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_034_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_034_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_034_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_034_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_034_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_034_UNION;
#endif
#define SOC_IOC_AO_IOCG_034_iocg_034_pu_START   (0)
#define SOC_IOC_AO_IOCG_034_iocg_034_pu_END     (0)
#define SOC_IOC_AO_IOCG_034_iocg_034_pd_START   (1)
#define SOC_IOC_AO_IOCG_034_iocg_034_pd_END     (1)
#define SOC_IOC_AO_IOCG_034_iocg_034_ds0_START  (4)
#define SOC_IOC_AO_IOCG_034_iocg_034_ds0_END    (4)
#define SOC_IOC_AO_IOCG_034_iocg_034_ds1_START  (5)
#define SOC_IOC_AO_IOCG_034_iocg_034_ds1_END    (5)
#define SOC_IOC_AO_IOCG_034_iocg_034_ds2_START  (6)
#define SOC_IOC_AO_IOCG_034_iocg_034_ds2_END    (6)
#define SOC_IOC_AO_IOCG_034_iocg_034_sr_START   (7)
#define SOC_IOC_AO_IOCG_034_iocg_034_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_035_UNION
 �ṹ˵��  : IOCG_035 �Ĵ����ṹ���塣��ַƫ����:0x88C����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_211���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_035_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_035_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_035_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_035_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_035_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_035_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_035_UNION;
#endif
#define SOC_IOC_AO_IOCG_035_iocg_035_pu_START   (0)
#define SOC_IOC_AO_IOCG_035_iocg_035_pu_END     (0)
#define SOC_IOC_AO_IOCG_035_iocg_035_pd_START   (1)
#define SOC_IOC_AO_IOCG_035_iocg_035_pd_END     (1)
#define SOC_IOC_AO_IOCG_035_iocg_035_ds0_START  (4)
#define SOC_IOC_AO_IOCG_035_iocg_035_ds0_END    (4)
#define SOC_IOC_AO_IOCG_035_iocg_035_ds1_START  (5)
#define SOC_IOC_AO_IOCG_035_iocg_035_ds1_END    (5)
#define SOC_IOC_AO_IOCG_035_iocg_035_ds2_START  (6)
#define SOC_IOC_AO_IOCG_035_iocg_035_ds2_END    (6)
#define SOC_IOC_AO_IOCG_035_iocg_035_sr_START   (7)
#define SOC_IOC_AO_IOCG_035_iocg_035_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_036_UNION
 �ṹ˵��  : IOCG_036 �Ĵ����ṹ���塣��ַƫ����:0x890����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_212���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_036_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_036_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_036_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_036_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_036_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_036_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_036_UNION;
#endif
#define SOC_IOC_AO_IOCG_036_iocg_036_pu_START   (0)
#define SOC_IOC_AO_IOCG_036_iocg_036_pu_END     (0)
#define SOC_IOC_AO_IOCG_036_iocg_036_pd_START   (1)
#define SOC_IOC_AO_IOCG_036_iocg_036_pd_END     (1)
#define SOC_IOC_AO_IOCG_036_iocg_036_ds0_START  (4)
#define SOC_IOC_AO_IOCG_036_iocg_036_ds0_END    (4)
#define SOC_IOC_AO_IOCG_036_iocg_036_ds1_START  (5)
#define SOC_IOC_AO_IOCG_036_iocg_036_ds1_END    (5)
#define SOC_IOC_AO_IOCG_036_iocg_036_ds2_START  (6)
#define SOC_IOC_AO_IOCG_036_iocg_036_ds2_END    (6)
#define SOC_IOC_AO_IOCG_036_iocg_036_sr_START   (7)
#define SOC_IOC_AO_IOCG_036_iocg_036_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_037_UNION
 �ṹ˵��  : IOCG_037 �Ĵ����ṹ���塣��ַƫ����:0x894����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_213���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_037_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_037_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_037_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_037_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_037_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_037_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_037_UNION;
#endif
#define SOC_IOC_AO_IOCG_037_iocg_037_pu_START   (0)
#define SOC_IOC_AO_IOCG_037_iocg_037_pu_END     (0)
#define SOC_IOC_AO_IOCG_037_iocg_037_pd_START   (1)
#define SOC_IOC_AO_IOCG_037_iocg_037_pd_END     (1)
#define SOC_IOC_AO_IOCG_037_iocg_037_ds0_START  (4)
#define SOC_IOC_AO_IOCG_037_iocg_037_ds0_END    (4)
#define SOC_IOC_AO_IOCG_037_iocg_037_ds1_START  (5)
#define SOC_IOC_AO_IOCG_037_iocg_037_ds1_END    (5)
#define SOC_IOC_AO_IOCG_037_iocg_037_ds2_START  (6)
#define SOC_IOC_AO_IOCG_037_iocg_037_ds2_END    (6)
#define SOC_IOC_AO_IOCG_037_iocg_037_sr_START   (7)
#define SOC_IOC_AO_IOCG_037_iocg_037_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_038_UNION
 �ṹ˵��  : IOCG_038 �Ĵ����ṹ���塣��ַƫ����:0x898����ֵ:0x00000012�����:32
 �Ĵ���˵��: GPIO_214���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_038_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_038_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_038_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_038_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_038_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_038_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_038_UNION;
#endif
#define SOC_IOC_AO_IOCG_038_iocg_038_pu_START   (0)
#define SOC_IOC_AO_IOCG_038_iocg_038_pu_END     (0)
#define SOC_IOC_AO_IOCG_038_iocg_038_pd_START   (1)
#define SOC_IOC_AO_IOCG_038_iocg_038_pd_END     (1)
#define SOC_IOC_AO_IOCG_038_iocg_038_ds0_START  (4)
#define SOC_IOC_AO_IOCG_038_iocg_038_ds0_END    (4)
#define SOC_IOC_AO_IOCG_038_iocg_038_ds1_START  (5)
#define SOC_IOC_AO_IOCG_038_iocg_038_ds1_END    (5)
#define SOC_IOC_AO_IOCG_038_iocg_038_ds2_START  (6)
#define SOC_IOC_AO_IOCG_038_iocg_038_ds2_END    (6)
#define SOC_IOC_AO_IOCG_038_iocg_038_sr_START   (7)
#define SOC_IOC_AO_IOCG_038_iocg_038_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_039_UNION
 �ṹ˵��  : IOCG_039 �Ĵ����ṹ���塣��ַƫ����:0x89C����ֵ:0x00000002�����:32
 �Ĵ���˵��: ISP_GPIO03_PRTRB���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_039_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_039_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_039_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_039_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_039_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_039_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_039_UNION;
#endif
#define SOC_IOC_AO_IOCG_039_iocg_039_pu_START   (0)
#define SOC_IOC_AO_IOCG_039_iocg_039_pu_END     (0)
#define SOC_IOC_AO_IOCG_039_iocg_039_pd_START   (1)
#define SOC_IOC_AO_IOCG_039_iocg_039_pd_END     (1)
#define SOC_IOC_AO_IOCG_039_iocg_039_ds0_START  (4)
#define SOC_IOC_AO_IOCG_039_iocg_039_ds0_END    (4)
#define SOC_IOC_AO_IOCG_039_iocg_039_ds1_START  (5)
#define SOC_IOC_AO_IOCG_039_iocg_039_ds1_END    (5)
#define SOC_IOC_AO_IOCG_039_iocg_039_ds2_START  (6)
#define SOC_IOC_AO_IOCG_039_iocg_039_ds2_END    (6)
#define SOC_IOC_AO_IOCG_039_iocg_039_sr_START   (7)
#define SOC_IOC_AO_IOCG_039_iocg_039_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_040_UNION
 �ṹ˵��  : IOCG_040 �Ĵ����ṹ���塣��ַƫ����:0x8A0����ֵ:0x00000002�����:32
 �Ĵ���˵��: ISP_GPIO04_FTPWM���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_040_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_040_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_040_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_040_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_040_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_040_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_040_UNION;
#endif
#define SOC_IOC_AO_IOCG_040_iocg_040_pu_START   (0)
#define SOC_IOC_AO_IOCG_040_iocg_040_pu_END     (0)
#define SOC_IOC_AO_IOCG_040_iocg_040_pd_START   (1)
#define SOC_IOC_AO_IOCG_040_iocg_040_pd_END     (1)
#define SOC_IOC_AO_IOCG_040_iocg_040_ds0_START  (4)
#define SOC_IOC_AO_IOCG_040_iocg_040_ds0_END    (4)
#define SOC_IOC_AO_IOCG_040_iocg_040_ds1_START  (5)
#define SOC_IOC_AO_IOCG_040_iocg_040_ds1_END    (5)
#define SOC_IOC_AO_IOCG_040_iocg_040_ds2_START  (6)
#define SOC_IOC_AO_IOCG_040_iocg_040_ds2_END    (6)
#define SOC_IOC_AO_IOCG_040_iocg_040_sr_START   (7)
#define SOC_IOC_AO_IOCG_040_iocg_040_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_041_UNION
 �ṹ˵��  : IOCG_041 �Ĵ����ṹ���塣��ַƫ����:0x8A4����ֵ:0x00000002�����:32
 �Ĵ���˵��: ISP_GPIO05_BKPWM���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_041_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_041_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_041_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_041_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_041_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_041_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_041_UNION;
#endif
#define SOC_IOC_AO_IOCG_041_iocg_041_pu_START   (0)
#define SOC_IOC_AO_IOCG_041_iocg_041_pu_END     (0)
#define SOC_IOC_AO_IOCG_041_iocg_041_pd_START   (1)
#define SOC_IOC_AO_IOCG_041_iocg_041_pd_END     (1)
#define SOC_IOC_AO_IOCG_041_iocg_041_ds0_START  (4)
#define SOC_IOC_AO_IOCG_041_iocg_041_ds0_END    (4)
#define SOC_IOC_AO_IOCG_041_iocg_041_ds1_START  (5)
#define SOC_IOC_AO_IOCG_041_iocg_041_ds1_END    (5)
#define SOC_IOC_AO_IOCG_041_iocg_041_ds2_START  (6)
#define SOC_IOC_AO_IOCG_041_iocg_041_ds2_END    (6)
#define SOC_IOC_AO_IOCG_041_iocg_041_sr_START   (7)
#define SOC_IOC_AO_IOCG_041_iocg_041_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_042_UNION
 �ṹ˵��  : IOCG_042 �Ĵ����ṹ���塣��ַƫ����:0x8A8����ֵ:0x00000002�����:32
 �Ĵ���˵��: ISP_GPIO09_ENC���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_042_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_042_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_042_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_042_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_042_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_042_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_042_UNION;
#endif
#define SOC_IOC_AO_IOCG_042_iocg_042_pu_START   (0)
#define SOC_IOC_AO_IOCG_042_iocg_042_pu_END     (0)
#define SOC_IOC_AO_IOCG_042_iocg_042_pd_START   (1)
#define SOC_IOC_AO_IOCG_042_iocg_042_pd_END     (1)
#define SOC_IOC_AO_IOCG_042_iocg_042_ds0_START  (4)
#define SOC_IOC_AO_IOCG_042_iocg_042_ds0_END    (4)
#define SOC_IOC_AO_IOCG_042_iocg_042_ds1_START  (5)
#define SOC_IOC_AO_IOCG_042_iocg_042_ds1_END    (5)
#define SOC_IOC_AO_IOCG_042_iocg_042_ds2_START  (6)
#define SOC_IOC_AO_IOCG_042_iocg_042_ds2_END    (6)
#define SOC_IOC_AO_IOCG_042_iocg_042_sr_START   (7)
#define SOC_IOC_AO_IOCG_042_iocg_042_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_043_UNION
 �ṹ˵��  : IOCG_043 �Ĵ����ṹ���塣��ַƫ����:0x8AC����ֵ:0x00000002�����:32
 �Ĵ���˵��: ISP_GPIO07_ENA���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_043_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_043_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_043_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_043_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_043_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_043_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_043_UNION;
#endif
#define SOC_IOC_AO_IOCG_043_iocg_043_pu_START   (0)
#define SOC_IOC_AO_IOCG_043_iocg_043_pu_END     (0)
#define SOC_IOC_AO_IOCG_043_iocg_043_pd_START   (1)
#define SOC_IOC_AO_IOCG_043_iocg_043_pd_END     (1)
#define SOC_IOC_AO_IOCG_043_iocg_043_ds0_START  (4)
#define SOC_IOC_AO_IOCG_043_iocg_043_ds0_END    (4)
#define SOC_IOC_AO_IOCG_043_iocg_043_ds1_START  (5)
#define SOC_IOC_AO_IOCG_043_iocg_043_ds1_END    (5)
#define SOC_IOC_AO_IOCG_043_iocg_043_ds2_START  (6)
#define SOC_IOC_AO_IOCG_043_iocg_043_ds2_END    (6)
#define SOC_IOC_AO_IOCG_043_iocg_043_sr_START   (7)
#define SOC_IOC_AO_IOCG_043_iocg_043_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_044_UNION
 �ṹ˵��  : IOCG_044 �Ĵ����ṹ���塣��ַƫ����:0x8B0����ֵ:0x00000002�����:32
 �Ĵ���˵��: ISP_GPIO08_ENB���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_044_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_044_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_044_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_044_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_044_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_044_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_044_UNION;
#endif
#define SOC_IOC_AO_IOCG_044_iocg_044_pu_START   (0)
#define SOC_IOC_AO_IOCG_044_iocg_044_pu_END     (0)
#define SOC_IOC_AO_IOCG_044_iocg_044_pd_START   (1)
#define SOC_IOC_AO_IOCG_044_iocg_044_pd_END     (1)
#define SOC_IOC_AO_IOCG_044_iocg_044_ds0_START  (4)
#define SOC_IOC_AO_IOCG_044_iocg_044_ds0_END    (4)
#define SOC_IOC_AO_IOCG_044_iocg_044_ds1_START  (5)
#define SOC_IOC_AO_IOCG_044_iocg_044_ds1_END    (5)
#define SOC_IOC_AO_IOCG_044_iocg_044_ds2_START  (6)
#define SOC_IOC_AO_IOCG_044_iocg_044_ds2_END    (6)
#define SOC_IOC_AO_IOCG_044_iocg_044_sr_START   (7)
#define SOC_IOC_AO_IOCG_044_iocg_044_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_045_UNION
 �ṹ˵��  : IOCG_045 �Ĵ����ṹ���塣��ַƫ����:0x8B4����ֵ:0x00000002�����:32
 �Ĵ���˵��: ISP_GPIO11���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_045_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_045_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_045_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_045_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_045_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_045_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_045_UNION;
#endif
#define SOC_IOC_AO_IOCG_045_iocg_045_pu_START   (0)
#define SOC_IOC_AO_IOCG_045_iocg_045_pu_END     (0)
#define SOC_IOC_AO_IOCG_045_iocg_045_pd_START   (1)
#define SOC_IOC_AO_IOCG_045_iocg_045_pd_END     (1)
#define SOC_IOC_AO_IOCG_045_iocg_045_ds0_START  (4)
#define SOC_IOC_AO_IOCG_045_iocg_045_ds0_END    (4)
#define SOC_IOC_AO_IOCG_045_iocg_045_ds1_START  (5)
#define SOC_IOC_AO_IOCG_045_iocg_045_ds1_END    (5)
#define SOC_IOC_AO_IOCG_045_iocg_045_ds2_START  (6)
#define SOC_IOC_AO_IOCG_045_iocg_045_ds2_END    (6)
#define SOC_IOC_AO_IOCG_045_iocg_045_sr_START   (7)
#define SOC_IOC_AO_IOCG_045_iocg_045_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_046_UNION
 �ṹ˵��  : IOCG_046 �Ĵ����ṹ���塣��ַƫ����:0x8B8����ֵ:0x00000002�����:32
 �Ĵ���˵��: ISP_GPIO12���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_046_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_046_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_046_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_046_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_046_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_046_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_046_UNION;
#endif
#define SOC_IOC_AO_IOCG_046_iocg_046_pu_START   (0)
#define SOC_IOC_AO_IOCG_046_iocg_046_pu_END     (0)
#define SOC_IOC_AO_IOCG_046_iocg_046_pd_START   (1)
#define SOC_IOC_AO_IOCG_046_iocg_046_pd_END     (1)
#define SOC_IOC_AO_IOCG_046_iocg_046_ds0_START  (4)
#define SOC_IOC_AO_IOCG_046_iocg_046_ds0_END    (4)
#define SOC_IOC_AO_IOCG_046_iocg_046_ds1_START  (5)
#define SOC_IOC_AO_IOCG_046_iocg_046_ds1_END    (5)
#define SOC_IOC_AO_IOCG_046_iocg_046_ds2_START  (6)
#define SOC_IOC_AO_IOCG_046_iocg_046_ds2_END    (6)
#define SOC_IOC_AO_IOCG_046_iocg_046_sr_START   (7)
#define SOC_IOC_AO_IOCG_046_iocg_046_sr_END     (7)


/*****************************************************************************
 �ṹ��    : SOC_IOC_AO_IOCG_047_UNION
 �ṹ˵��  : IOCG_047 �Ĵ����ṹ���塣��ַƫ����:0x8BC����ֵ:0x00000002�����:32
 �Ĵ���˵��: GPIO_223���ܹܽſ��ƼĴ�����&#13;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  iocg_047_pu  : 1;  /* bit[0]   : �����������ƣ�����Ч */
        unsigned int  iocg_047_pd  : 1;  /* bit[1]   : �����������ƣ�����Ч */
        unsigned int  reserved_0   : 2;  /* bit[2-3] : ������ */
        unsigned int  iocg_047_ds0 : 1;  /* bit[4]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_047_ds1 : 1;  /* bit[5]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_047_ds2 : 1;  /* bit[6]   : DS1,DS0������������000-2mA��001-4mA��010-6mA��011-8mA��100-10mA��101-12mA��110-14mA��111-16mA */
        unsigned int  iocg_047_sr  : 1;  /* bit[7]   : SRew rate����ʹ�ܣ�0������ģʽ��1������������ź������½�ʱ�� */
        unsigned int  reserved_1   : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_IOC_AO_IOCG_047_UNION;
#endif
#define SOC_IOC_AO_IOCG_047_iocg_047_pu_START   (0)
#define SOC_IOC_AO_IOCG_047_iocg_047_pu_END     (0)
#define SOC_IOC_AO_IOCG_047_iocg_047_pd_START   (1)
#define SOC_IOC_AO_IOCG_047_iocg_047_pd_END     (1)
#define SOC_IOC_AO_IOCG_047_iocg_047_ds0_START  (4)
#define SOC_IOC_AO_IOCG_047_iocg_047_ds0_END    (4)
#define SOC_IOC_AO_IOCG_047_iocg_047_ds1_START  (5)
#define SOC_IOC_AO_IOCG_047_iocg_047_ds1_END    (5)
#define SOC_IOC_AO_IOCG_047_iocg_047_ds2_START  (6)
#define SOC_IOC_AO_IOCG_047_iocg_047_ds2_END    (6)
#define SOC_IOC_AO_IOCG_047_iocg_047_sr_START   (7)
#define SOC_IOC_AO_IOCG_047_iocg_047_sr_END     (7)






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

#endif /* end of soc_ioc_ao_interface.h */
